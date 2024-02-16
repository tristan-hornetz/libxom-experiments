#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include "libxom.h"
#include "benchmark.h"
#include "modxom.h"

extern int32_t xomfd;

#define mmap_benchmark(NUM_PAGES)                                       \
benchmark(mmap##NUM_PAGES) {                                            \
    return internal_benchmark_mmap_n (fp, name, timer_, NUM_PAGES);     \
}

#define lock_benchmark(NUM_PAGES)                                       \
benchmark(lock##NUM_PAGES) {                                            \
    return internal_benchmark_lock_n (fp, name, timer_, NUM_PAGES);     \
}

#define free_benchmark(NUM_PAGES)                                       \
benchmark(free##NUM_PAGES) {                                            \
    return internal_benchmark_free_n (fp, name, timer_, NUM_PAGES);     \
}

static int internal_benchmark_mmap_n (FILE *restrict fp,
    const char *const restrict name, uint64_t timer_, const unsigned num_pages) {
    const static unsigned num_repetitions = 0x4000;
    unsigned i;
    uint64_t timer;
    uint64_t times[num_repetitions];
    void* buffer;
    struct xombuf* xbuf;

    for(i = 0; i < num_repetitions; i++) {
        START_TIMER;
        buffer = mmap(NULL, PAGE_SIZE * num_pages, PROT_READ | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        TIME_ELAPSED(timer);
        times[i] = timer;
        munmap(buffer, PAGE_SIZE * num_pages);
    }

    fprintf(fp, "mmap%u_times_noxom = ", num_pages);
    write_list(fp, times, countof(times), '\n');

    for(i = 0; i < num_repetitions; i++) {
        START_TIMER;
        xbuf = xom_alloc(PAGE_SIZE * num_pages);
        TIME_ELAPSED(timer);
        times[i] = timer;

        if(!xbuf)
            return -1;

        xom_free(xbuf);
    }
    fprintf(fp, "mmap%u_times_xom = ", num_pages);
    write_list(fp, times, countof(times), '\n');

    return 0;
}

static int internal_benchmark_lock_n (FILE *restrict fp,
    const char *const restrict name, uint64_t timer_, const unsigned num_pages) {
    const static unsigned num_repetitions = 0x4000;
    unsigned i;
    uint64_t timer;
    uint64_t times[num_repetitions];
    struct xombuf* xbuf;

    if (xomfd < 0) {
        fprintf(fp, "# Error: This benchmark requires SLAT-based XOM.\n"
            "# Make sure that your hypervisor setup works, and that modxom is loadad.\n\n");
        return -1;
    }

    for(i = 0; i < num_repetitions; i++) {
        xbuf = xom_alloc(PAGE_SIZE * num_pages);

        if(!xbuf)
            return -1;

        START_TIMER;
        xom_lock(xbuf);
        TIME_ELAPSED(timer);
        times[i] = timer;

        xom_free(xbuf);
    }
    fprintf(fp, "lock%u_times_slat = ", num_pages);
    write_list(fp, times, countof(times), '\n');

    return 0;
}

static int internal_benchmark_free_n (FILE *restrict fp,
    const char *const restrict name, uint64_t timer_, const unsigned num_pages) {
    const static unsigned num_repetitions = 0x4000;
    unsigned i;
    uint64_t timer;
    uint64_t times[num_repetitions];
    void* buffer;
    modxom_cmd cmd = {
        .cmd = MODXOM_CMD_FREE,
        .num_pages = num_pages,
        .base_addr = 0
    };

    for(i = 0; i < num_repetitions; i++) {
        buffer = mmap(NULL, PAGE_SIZE * num_pages, PROT_READ | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

        START_TIMER;
        munmap(buffer, PAGE_SIZE * num_pages);
        TIME_ELAPSED(timer);
        times[i] = timer;
    }

    fprintf(fp, "free%u_times_noxom = ", num_pages);
    write_list(fp, times, countof(times), '\n');

    for(i = 0; i < num_repetitions; i++) {
        if (xomfd < 0)
            buffer = mmap(NULL, PAGE_SIZE * num_pages, PROT_READ | PROT_WRITE| PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        else
            buffer = mmap(NULL, PAGE_SIZE * num_pages, PROT_READ | PROT_WRITE, MAP_PRIVATE, xomfd, 0);
        cmd.base_addr = (uintptr_t) buffer;

        if(!buffer || ~(uintptr_t)buffer)
            return -1;

        memset(buffer, 0xab, PAGE_SIZE * num_pages);
        if(xomfd >= 0) {
            cmd.cmd = MODXOM_CMD_LOCK;
            write(xomfd, &cmd, sizeof(cmd));
        }

        START_TIMER;
        if(xomfd >= 0) {
            cmd.cmd = MODXOM_CMD_FREE;
            cmd.base_addr = (uintptr_t) buffer;
            write(xomfd, &cmd, sizeof(cmd));
        }
        munmap(buffer, PAGE_SIZE * num_pages);
        TIME_ELAPSED(timer);
        times[i] = timer;
    }
    fprintf(fp, "free%u_times_xom = ", num_pages);
    write_list(fp, times, countof(times), '\n');

    return 0;
}

powers2(mmap_benchmark)
powers2(lock_benchmark)
powers2(free_benchmark)

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
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
    const static unsigned num_repetitions = 1000;
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
        if (xomfd < 0)
            buffer = mmap(NULL, PAGE_SIZE * num_pages, PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        else
            buffer = mmap(NULL, PAGE_SIZE * num_pages, PROT_EXEC, MAP_PRIVATE, xomfd, 0);
        TIME_ELAPSED(timer);
        times[i] = timer;

        if(xomfd >= 0) {
            cmd.base_addr = (uintptr_t) buffer;
            write(xomfd, &cmd, sizeof(cmd));
        }

        munmap(buffer, PAGE_SIZE * num_pages);
    }
    fprintf(fp, "mmap%u_times_xom = ", num_pages);
    write_list(fp, times, countof(times), '\n');

    return 0;
}

static int internal_benchmark_lock_n (FILE *restrict fp,
    const char *const restrict name, uint64_t timer_, const unsigned num_pages) {
    const static unsigned num_repetitions = 1000;
    unsigned i;
    uint64_t timer;
    uint64_t times[num_repetitions];
    void* buffer;
    modxom_cmd cmd = {
        .cmd = MODXOM_CMD_FREE,
        .num_pages = num_pages,
        .base_addr = 0
    };

    if (xomfd < 0) {
        fprintf(fp, "# Error: This benchmark requires SLAT-based XOM.\n"
            "# Make sure that your hypervisor setup works, and that modxom is loadad.\n\n");
        return -1;
    }

    for(i = 0; i < num_repetitions; i++) {
        buffer = mmap(NULL, PAGE_SIZE * num_pages, PROT_EXEC, MAP_PRIVATE, xomfd, 0);
        cmd.base_addr = (uintptr_t) buffer;
        cmd.cmd = MODXOM_CMD_LOCK;

        START_TIMER;
        write(xomfd, &cmd, sizeof(cmd));
        TIME_ELAPSED(timer);
        times[i] = timer;

        cmd.cmd = MODXOM_CMD_FREE;
        write(xomfd, &cmd, sizeof(cmd));
        munmap(buffer, PAGE_SIZE * num_pages);
    }
    fprintf(fp, "lock%u_times_slat = ", num_pages);
    write_list(fp, times, countof(times), '\n');

    return 0;
}

static int internal_benchmark_free_n (FILE *restrict fp,
    const char *const restrict name, uint64_t timer_, const unsigned num_pages) {
    const static unsigned num_repetitions = 1000;
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
            buffer = mmap(NULL, PAGE_SIZE * num_pages, PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        else
            buffer = mmap(NULL, PAGE_SIZE * num_pages, PROT_EXEC, MAP_PRIVATE, xomfd, 0);

        START_TIMER;
        if(xomfd >= 0) {
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

mmap_benchmark(1)
mmap_benchmark(2)
mmap_benchmark(4)
mmap_benchmark(8)
mmap_benchmark(16)
mmap_benchmark(32)
mmap_benchmark(64)
mmap_benchmark(128)
mmap_benchmark(256)
mmap_benchmark(512)
mmap_benchmark(1024)
mmap_benchmark(2048)
mmap_benchmark(4096)

lock_benchmark(1)
lock_benchmark(2)
lock_benchmark(4)
lock_benchmark(8)
lock_benchmark(16)
lock_benchmark(32)
lock_benchmark(64)
lock_benchmark(128)
lock_benchmark(256)
lock_benchmark(512)
lock_benchmark(1024)
lock_benchmark(2048)
lock_benchmark(4096)

free_benchmark(1)
free_benchmark(2)
free_benchmark(4)
free_benchmark(8)
free_benchmark(16)
free_benchmark(32)
free_benchmark(64)
free_benchmark(128)
free_benchmark(256)
free_benchmark(512)
free_benchmark(1024)
free_benchmark(2048)
free_benchmark(4096)

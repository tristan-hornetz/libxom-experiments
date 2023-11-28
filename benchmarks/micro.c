#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sched.h>
#include <math.h>
#include "benchmark.h"
#include "libxom.h"

#ifndef PAGE_SIZE
#define PAGE_SIZE 0x1000
#endif

#define NUM_PRIMES 1000000
#define MAX_PRIME 15485863

static uint32_t primes_[NUM_PRIMES];

static inline __attribute__((always_inline)) int is_prime(const uint32_t n, double (*sqrt_)(double)){
    uint32_t upper_bound = (uint32_t) n < 2 ? 0 : (uint32_t) sqrt_(n), i = 2;
    while(i <= upper_bound){
        if(!(n % i))
            return 0;
        i++;
    }
    return 1;
}

static inline __attribute__((always_inline)) uint32_t next_prime(uint32_t last, double (*sqrt_)(double)){
    while(!is_prime(++last, sqrt_));
    return last;
}

static __attribute__((aligned(PAGE_SIZE))) void get_primes(uint32_t primes[NUM_PRIMES], double (*sqrt_)(double)){
    uint32_t cur = 1, n = 0;
    while (n < NUM_PRIMES){
        cur = next_prime(cur, sqrt_);
        primes[n] = cur;
        n++;
    }
    printf("\n%lu is the %lu-th prime!\n", cur, n);
}

benchmark(primes){
    const static unsigned num_repetitions = 10;
    unsigned i;
    uint64_t timer;
    void (*get_primes_xom)(uint32_t primes[], double (*)(double));
    struct xombuf* primes_xom_buf = xom_alloc_pages(PAGE_SIZE);
    unsigned times[num_repetitions];


    xom_write(primes_xom_buf, get_primes, PAGE_SIZE);
    get_primes_xom = xom_lock(primes_xom_buf);

    for(i = 0; i < num_repetitions; i++) {
        START_TIMER;
        get_primes(primes_, sqrt);
        (void) primes_;
        TIME_ELAPSED(timer);
        times[i] = timer;
    }

    fprintf(fp, "prime_times_noxom = ");
    write_list(fp, times, countof(times), '\n');

    for(i = 0; i < num_repetitions; i++) {
        START_TIMER;
        get_primes_xom(primes_, sqrt);
        (void) primes_;
        TIME_ELAPSED(timer);
        times[i] = timer;
    }

    fprintf(fp, "prime_times_xom = ");
    write_list(fp, times, countof(times), '\n');

    return 0;
}

benchmark(nop_slide) {
    uint64_t timer;
    const static unsigned num_repetitions = 1000, num_rounds = 100;
    unsigned i, j;
    char *nop_slide = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    struct xombuf* nop_slide_xom = xom_alloc_pages(PAGE_SIZE);
    void (*nop_slide_fun)(void) = ((void (*)(void))nop_slide);
    void (*nop_slide_xom_fun)(void);
    unsigned times[num_repetitions];


    memset(nop_slide, NOP, PAGE_SIZE);
    nop_slide[PAGE_SIZE - 1] = RET;
    xom_write(nop_slide_xom, nop_slide, PAGE_SIZE);
    nop_slide_xom_fun = (void (*)(void)) xom_lock(nop_slide_xom);

    fprintf(fp, "nop_slide_times_noxom = [\n");
    for(j = 0; j < num_rounds; j++) {
        for(i = 0; i< num_repetitions; i++) {
            START_TIMER;
            nop_slide_fun();
            TIME_ELAPSED(timer);
            times[i] = timer;
        }
        write_list(fp, times, sizeof(times)/sizeof(*times), ',');
        sched_yield();
    }
    fprintf(fp, "]\n\nnop_slide_times_xom = [");
    fflush(fp);
    for(j = 0; j < num_rounds; j++) {
        for(i = 0; i< num_repetitions; i++){
            START_TIMER;
            nop_slide_xom_fun();
            TIME_ELAPSED(timer);
            times[i] = timer;
        }
        write_list(fp, times, countof(times), ',');
        sched_yield();
    }
    fprintf(fp, "]\n");
    munmap(nop_slide, PAGE_SIZE);
    xom_free(nop_slide_xom);
    return 0;
}



int main(int argc, char* argv[]){
    if(argc > 1)
        output_directory = argv[1];

    if(!is_xom_supported())
        fprintf(stderr, STR_FAIL "XOM is not supported! The benchmarks will likely cause a segmentation fault!\n");

    if(init_utils() < 0)
        return 1;

    run_benchmark(nop_slide);
    run_benchmark(primes);

    exit_utils();
    return 0;
}

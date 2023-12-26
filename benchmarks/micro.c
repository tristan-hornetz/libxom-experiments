#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sched.h>
#include <math.h>
#include "libxom-aes-gcm.h"
#include "benchmark.h"
#include "libxom.h"

#define NUM_PRIMES 1000000
#define MAX_PRIME 15485863

extern void jumper_link(void);
extern void jumper_fun(void* base_address, uint16_t seed, uintptr_t num_jumps);

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

static __attribute__((aligned(PAGE_SIZE))) volatile void get_primes(uint32_t primes[NUM_PRIMES], double (*sqrt_)(double)){
    uint32_t cur = 1, n = 0;
    while (n < NUM_PRIMES){
        cur = next_prime(cur, sqrt_);
        primes[n] = cur;
        n++;
    }
}

// Compute the first 1,000,000 primes
benchmark(primes){
    const static unsigned num_repetitions = 3;
    unsigned i;
    uint64_t timer;
    volatile void (*get_primes_xom)(uint32_t primes[], double (*)(double));
    struct xombuf* primes_xom_buf = xom_alloc_pages(PAGE_SIZE);
    uint64_t times[num_repetitions];
    volatile void (*get_primes_noxom)(uint32_t primes[], double (*)(double)) =
            mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    memcpy(get_primes_noxom, get_primes, PAGE_SIZE);
    xom_write(primes_xom_buf, get_primes, PAGE_SIZE);
    get_primes_xom = xom_lock(primes_xom_buf);

    for(i = 0; i < num_repetitions; i++) {
        memset(primes_, 0, sizeof(primes_));
        START_TIMER;
        get_primes_xom(primes_, sqrt);
        (void) primes_;
        TIME_ELAPSED(timer);
        times[i] = timer;
    }

    fprintf(fp, "prime_times_xom = ");
    write_list(fp, times, countof(times), '\n');

    for(i = 0; i < num_repetitions; i++) {
        memset(primes_, 0, sizeof(primes_));
        START_TIMER;
        get_primes_noxom(primes_, sqrt);
        (void) primes_;
        TIME_ELAPSED(timer);
        times[i] = timer;
    }

    fprintf(fp, "prime_times_noxom = ");
    write_list(fp, times, countof(times), '\n');

    xom_free(primes_xom_buf);
    munmap(get_primes_noxom, PAGE_SIZE);
    return 0;
}

// Execute a single-page nop slide
benchmark(nop_slide) {
    uint64_t timer;
    const static unsigned num_repetitions = 1000, num_rounds = 100;
    unsigned i, j;
    char *nop_slide = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    struct xombuf* nop_slide_xom = xom_alloc_pages(PAGE_SIZE);
    void (*nop_slide_fun)(void) = ((void (*)(void))nop_slide);
    void (*nop_slide_xom_fun)(void);
    uint64_t times[num_repetitions];


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

// Randomly jump between pages
benchmark(jumper) {
    const static size_t segment_size = (1 << 12) * PAGE_SIZE;
    const static unsigned num_repetitions = 1000;
    uint64_t timer;
    uint64_t times[num_repetitions];
    uint8_t* jumper_segment = mmap(NULL, segment_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    struct xombuf* xom_pages =  xom_alloc_pages(segment_size);
    void* base_address;
    unsigned i;

    for(i = 0; i < segment_size >> PAGE_SHIFT; i++)
        memcpy(&jumper_segment[PAGE_SIZE * i], jumper_link, 0x100);

    xom_write(xom_pages, jumper_segment, segment_size);
    base_address = xom_lock(xom_pages);

    if(!base_address) {
        munmap(jumper_segment, segment_size);
        xom_free(xom_pages);
        return -1;
    }

    fprintf(fp, "jumper_times_noxom = ");
    for(i = 0; i< num_repetitions; i++){
        START_TIMER;
        jumper_fun(jumper_segment, (0xcafe + i) & 0xfff, 0x1000);
        TIME_ELAPSED(timer);
        times[i] = timer;
    }
    write_list(fp, times, countof(times), '\n');

    fprintf(fp, "jumper_times_xom = ");
    for(i = 0; i< num_repetitions; i++){
        START_TIMER;
        jumper_fun(base_address, (0xcafe + i) & 0xfff, 0x1000);
        TIME_ELAPSED(timer);
        times[i] = timer;
    }
    write_list(fp, times, countof(times), '\n');

    munmap(jumper_segment, segment_size);
    xom_free(xom_pages);
    return 0;
}

// Encrypt data using AES
benchmark(aes) {
    const static unsigned num_repetitions = 1000;
    uint64_t timer;
    uint64_t times[num_repetitions];
    aes_uint128 iv = {.u64 = {0xcafe, 0xbabe}}, key = {.u64 = {0xdead, 0xbeef}}, tag = {.u64 = {0, 0}};
    gctr_fun aes_noxom = (void*) mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    gctr_fun aes_xom;
    struct xombuf* xom_pages =  xom_alloc_pages(PAGE_SIZE);
    char* enc_target = aligned_alloc(PAGE_SIZE, 2 * PAGE_SIZE);
    unsigned i;
    aes_gcm_context context = {
        .gctr = (void*)aes_noxom,
        .plaintext = enc_target,
        .ciphertext = enc_target + PAGE_SIZE,
        .aad = NULL,
        .aad_size = 0,
        .iv = (void*)&iv,
        .iv_len = sizeof(iv),
        .tag = (void*) &tag,
        .num_blocks = PAGE_SIZE / GCM_BLOCK_BYTES,
    };

    init_counter_mode_function((void*)aes_noxom, &key);
    xom_write(xom_pages, aes_noxom, PAGE_SIZE);
    aes_xom = xom_lock(xom_pages);
    if(!aes_xom) {
        xom_free(xom_pages);
        munmap(aes_noxom, PAGE_SIZE);
        free(enc_target);
        return -1;
    }

    fprintf(fp, "aes_times_noxom = ");
    for(i = 0; i < num_repetitions; i++){
        memset(enc_target, i & 0xff, 2 * PAGE_SIZE);
        flush_all(enc_target, 2 * PAGE_SIZE);
        START_TIMER;
        aes_gcm_encrypt(&context);
        TIME_ELAPSED(timer);
        times[i] = timer;
    }
    write_list(fp, times, countof(times), '\n');

    context.gctr = aes_xom;
    fprintf(fp, "aes_times_xom = ");
    for(i = 0; i < num_repetitions; i++){
        memset(enc_target, i & 0xff, 2 * PAGE_SIZE);
        flush_all(enc_target, 2 * PAGE_SIZE);
        START_TIMER;
        aes_gcm_encrypt(&context);
        TIME_ELAPSED(timer);
        times[i] = timer;
    }
    write_list(fp, times, countof(times), '\n');

    xom_free(xom_pages);
    munmap(aes_noxom, PAGE_SIZE);
    free(enc_target);
    return 0;
}

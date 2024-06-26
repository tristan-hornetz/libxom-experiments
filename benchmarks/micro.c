#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sched.h>
#include <math.h>
#include "libxom-aes-gcm.h"
#include "benchmark.h"
#include "libxom.h"

#define NUM_PRIMES 100000
#define num_repetitions (1 << 17)

extern void jumper_link(void);
extern void jumper_fun(void* base_address, uint16_t seed, uintptr_t num_jumps);

static uint32_t primes_[NUM_PRIMES];

static inline __attribute__((always_inline)) int is_prime(const uint32_t n, double (*sqrt_)(double)){
    const uint32_t upper_bound = (uint32_t) n < 2 ? 0 : (uint32_t) sqrt_(n);
    uint32_t i = 2;
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
    const static unsigned prime_num_repetitions = 3;
    unsigned i;
    uint64_t timer;
    volatile void (*get_primes_xom)(uint32_t primes[], double (*)(double));
    struct xombuf* primes_xom_buf = xom_alloc(PAGE_SIZE);
    uint64_t times[prime_num_repetitions];
    volatile void (*get_primes_noxom)(uint32_t primes[], double (*)(double)) =
            mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    memcpy(get_primes_noxom, get_primes, PAGE_SIZE);
    xom_write(primes_xom_buf, get_primes, PAGE_SIZE, 0);
    get_primes_xom = xom_lock(primes_xom_buf);

    for(i = 0; i < prime_num_repetitions; i++) {
        memset(primes_, 0, sizeof(primes_));
        START_TIMER;
        get_primes_xom(primes_, sqrt);
        (void) primes_;
        TIME_ELAPSED(timer);
        times[i] = timer;
    }

    fprintf(fp, "prime_times_xom = ");
    write_list(fp, times, countof(times), '\n');

    for(i = 0; i < prime_num_repetitions; i++) {
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

// Call a function containing only a RET instruction
benchmark(access) {
    uint64_t timer;
    const static unsigned num_rounds = 1;
    unsigned i, j;
    char *nop_slide = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    struct xombuf* nop_slide_xom = xom_alloc(PAGE_SIZE);
    void (*access_fun)(void) = ((void (*)(void))nop_slide);
    void (*access_xom_fun)(void);
    uint64_t times[num_repetitions];


    nop_slide[0] = RET;
    xom_write(nop_slide_xom, nop_slide, PAGE_SIZE, 0);
    access_xom_fun = (void (*)(void)) xom_lock(nop_slide_xom);

     for(j = 0; j < num_rounds; j++) {
         for (i = 0; i < num_repetitions; i++) {
             access_fun();
         }
     }
    
    fprintf(fp, "access_times_noxom = [\n");
    for(j = 0; j < num_rounds; j++) {
        for(i = 0; i< num_repetitions; i++) {
            START_TIMER;
            access_fun();
            TIME_ELAPSED(timer);
            times[i] = timer;
        }
        write_list(fp, times, sizeof(times)/sizeof(*times), ',');
    }
    fprintf(fp, "]\n\naccess_times_xom = [");
    fflush(fp);
    for(j = 0; j < num_rounds; j++) {
        for(i = 0; i< num_repetitions; i++){
            START_TIMER;
            access_xom_fun();
            TIME_ELAPSED(timer);
            times[i] = timer;
        }
        write_list(fp, times, countof(times), ',');
    }
    fprintf(fp, "]\n");
    munmap(nop_slide, PAGE_SIZE);
    xom_free(nop_slide_xom);
    return 0;
}

// Call a function containing only a RET instruction
benchmark(access_flush) {
    uint64_t timer;
    const static unsigned num_rounds = 1;
    unsigned i, j;
    char *nop_slide = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    struct xombuf* nop_slide_xom[num_repetitions];
    void (*access_fun)(void) = ((void (*)(void))nop_slide);
    void (*access_xom_fun)(void);
    uint64_t times[num_repetitions];

    for(i = 0; i < num_repetitions; i++)
        nop_slide_xom[i] = xom_alloc(PAGE_SIZE);


    nop_slide[0] = RET;

    fprintf(fp, "access_times_noxom = [\n");
    for(j = 0; j < num_rounds; j++) {
        for(i = 0; i< num_repetitions; i++) {
            asm volatile("clflush (%0)\nmfence" :: "r"(access_fun));
            START_TIMER;
            access_fun();
            TIME_ELAPSED(timer);
            times[i] = timer;
        }
        write_list(fp, times, sizeof(times)/sizeof(*times), ',');
    }
    fprintf(fp, "]\n\naccess_times_xom = [");
    fflush(fp);
    for(j = 0; j < num_rounds; j++) {
        for(i = 0; i < (num_repetitions / 2) + 1; i++){
            xom_write(nop_slide_xom[i], nop_slide, 16, 0);
            asm volatile("clflush (%0)\nmfence" :: "r"(*(void**)(nop_slide_xom[i])));
            access_xom_fun = (void (*)(void)) xom_lock(nop_slide_xom[i]);
            START_TIMER;
            access_xom_fun();
            TIME_ELAPSED(timer);
            times[i] = timer;
        }
        write_list(fp, times, countof(times), ',');
    }
    fprintf(fp, "]\n");
    munmap(nop_slide, PAGE_SIZE);
    for(i = 0; i < num_repetitions; i++)
        xom_free(nop_slide_xom[i]);
    return 0;
}

// Execute a single-page nop slide
benchmark(nop_slide) {
    uint64_t timer;
    const static unsigned num_rounds = 1;
    unsigned i, j;
    char *nop_slide = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    struct xombuf* nop_slide_xom = xom_alloc(PAGE_SIZE);
    void (*nop_slide_fun)(void) = ((void (*)(void))nop_slide);
    void (*nop_slide_xom_fun)(void);
    uint64_t times[num_repetitions];


    memset(nop_slide, NOP, PAGE_SIZE);
    nop_slide[PAGE_SIZE - 1] = RET;
    xom_write(nop_slide_xom, nop_slide, PAGE_SIZE, 0);
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
        
    }
    fprintf(fp, "]\n");
    munmap(nop_slide, PAGE_SIZE);
    xom_free(nop_slide_xom);
    return 0;
}

#define CHAIN_SCALE 12
benchmark(chain) {
    uint64_t timer;
    const static unsigned num_rounds = 1;
    const static unsigned char jmp_next_page[] = {0xe9, 0xfb, 0x0f, 0x00, 0x00, 0x90};
    unsigned int i, j;
    char *jmp_chain = mmap(NULL, PAGE_SIZE * (1 << CHAIN_SCALE), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    struct xombuf* jmp_chain_xom = xom_alloc(PAGE_SIZE * (1 << CHAIN_SCALE));
    void (*jmp_chain_fun)(void) = ((void (*)(void))jmp_chain);
    void (*jmp_chain_xom_fun)(void);
    uint64_t times[num_repetitions];

    for(i = 0; i < (1 << CHAIN_SCALE); i++)
        memcpy(jmp_chain + (i << PAGE_SHIFT), jmp_next_page, sizeof(jmp_next_page));
    (jmp_chain + (((1 << CHAIN_SCALE) - 1) << PAGE_SHIFT))[0] = RET;
    xom_write(jmp_chain_xom, jmp_chain, PAGE_SIZE * (1 << CHAIN_SCALE), 0);
    jmp_chain_xom_fun = (void (*)(void)) xom_lock(jmp_chain_xom);

    fprintf(fp, "chain_times_noxom = [\n");
    for(j = 0; j < num_rounds; j++) {
        for(i = 0; i< num_repetitions; i++) {
            START_TIMER;
            jmp_chain_fun();
            TIME_ELAPSED(timer);
            times[i] = timer;
        }
        write_list(fp, times, sizeof(times)/sizeof(*times), ',');

    }
    fprintf(fp, "]\n\nchain_times_xom = [");
    fflush(fp);
    for(j = 0; j < num_rounds; j++) {
        for(i = 0; i< num_repetitions; i++){
            START_TIMER;
            jmp_chain_xom_fun();
            TIME_ELAPSED(timer);
            times[i] = timer;
        }
        write_list(fp, times, countof(times), ',');

    }
    fprintf(fp, "]\n");
    munmap(jmp_chain, PAGE_SIZE);
    xom_free(jmp_chain_xom);
    return 0;
}

// Randomly jump between pages
benchmark(jumper) {
    const static size_t segment_size = (1 << 12) * PAGE_SIZE;
    uint64_t timer;
    uint64_t times[num_repetitions];
    uint8_t* jumper_segment = mmap(NULL, segment_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    struct xombuf* xom_pages = xom_alloc(segment_size);
    void* base_address;
    unsigned i;

    for(i = 0; i < segment_size >> PAGE_SHIFT; i++)
        memcpy(&jumper_segment[PAGE_SIZE * i], jumper_link, 0x100);

    xom_write(xom_pages, jumper_segment, segment_size, 0);
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
    uint64_t timer;
    uint64_t times[num_repetitions];
    aes_uint128 iv = {.u64 = {0xcafe, 0xbabe}}, key = {.u64 = {0xdead, 0xbeef}}, tag = {.u64 = {0, 0}};
    gctr_fun aes_noxom = (void*) mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    gctr_fun aes_xom;
    struct xombuf* xom_pages = xom_alloc(PAGE_SIZE);
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
    xom_write(xom_pages, aes_noxom, PAGE_SIZE, 0);
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

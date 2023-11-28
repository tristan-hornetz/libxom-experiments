#ifndef XOM_BENCHMARKS_H
#define XOM_BENCHMARKS_H

#include <stdint.h>
#include <cpuid.h>

#ifdef __cplusplus
#ifndef restrict
#define restrict
#endif
#endif

// Opcodes
#define NOP 0x90
#define RET 0xc3
#define PROLOGUE 0x55, 0x48, 0x89, 0xe5,
#define EPILOGUE 0xc9, 0xc3,
#define CPUID 0x0f, 0xa2,
#define RTDSCP 0x0f, 0x01, 0xf9,
#define RTDSC  0x0f, 0x31,
#define MFENCE 0x0f, 0xae, 0xf0,

#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define YLL "\033[33m"
#define CRESET "\e[0m"
#define STR_WARN "[" YLL "WARNING" CRESET "] "
#define STR_OK "[" GRN "+" CRESET "] "
#define STR_PEND "[" CYN "*" CRESET "] "
#define STR_FAIL "[" RED "-" CRESET "] "

#ifdef __GNUC__
#define COMPILER_NAME   "GCC"
#define COMPILER_MAJOR  __GNUC__
#define COMPILER_MINOR  __GNUC_MINOR__
#define COMPILER_PATCH  __GNUC_PATCHLEVEL__
#else
#ifdef __clang__
#define COMPILER_NAME   "Clang"
#define COMPILER_MAJOR  __clang_major__
#define COMPILER_MINOR  __clang_minor__
#define COMPILER_PATCH  __clang_patchlevel__
#else
#define COMPILER_NAME   "Unknown compiler"
#define COMPILER_MAJOR  0
#define COMPILER_MINOR  0
#define COMPILER_PATCH  0
#endif
#endif

#define DEFAULT_OUTPUT_DIRECTORY "./benchmark_results"

#define countof(x) (sizeof(x)/sizeof(*(x)))

#ifndef str
#define str(x) #x
#endif
#define run_benchmark(name) (benchmark_##name())
#define benchmark(name_)                                                 \
static int internal_benchmark_##name_(FILE *restrict fp,                \
    const char *const restrict name, uint64_t timer_);                  \
                                                                        \
static int benchmark_##name_ (void) {                                    \
    FILE* fp = open_benchmark_file(str(name_) ".py");                    \
    int ret;                                                            \
                                                                        \
    if(!fp)                                                             \
        return -1;                                                      \
                                                                        \
    printf(STR_PEND "Running benchmark '%s'... ", str(name_));           \
    ret = internal_benchmark_##name_(fp, str(name_), 0);                  \
    if(ret < 0)                                                         \
        printf("\r" STR_FAIL "Running benchmark '%s'... Failed! "       \
        "See %s/%s for details\n",                                      \
        str(name_), output_directory, str(name_) ".py");                  \
    else                                                                \
        printf("\r"STR_OK"Running benchmark '%s'... OK\n", str(name_));  \
    fclose(fp);                                                         \
    return ret;                                                         \
}                                                                       \
static int internal_benchmark_##name_(FILE *restrict fp,                \
    const char* const restrict name, uint64_t timer_)


static inline __attribute__((always_inline)) void mfence() {asm volatile("mfence");}
static inline __attribute__((always_inline)) void clflushp(void* p) {asm volatile("clflushopt (%0)" :: "r"(p));}
static inline __attribute__((always_inline)) void clflushi(uintptr_t p) {asm volatile("clflushopt (%0)" :: "r"(p));}

static inline uint64_t rdtscp_(){
    uint64_t a, d;
    asm volatile ("rdtscp" : "=a"(a), "=d"(d) :: "rcx");
    return (d << 32) | a;
}

static inline uint64_t rdtsc_(){
    uint64_t a, d;
    asm volatile ("rdtsc" : "=a"(a), "=d"(d));
    return (d << 32) | a;
}

static inline unsigned is_rdtscp_supported(void){
    uintptr_t a, b, c, d;
    __cpuid(0x80000001, a, b, c, d);
    return (unsigned) (d >> 27) & 1;
}

extern unsigned use_rdtscp;
extern unsigned cache_line_size;
extern char* output_directory;

static inline uint64_t hwtime(){
    return use_rdtscp ? rdtscp_() : rdtsc_();
}

#define START_TIMER mfence(); timer_ = hwtime(); mfence();
#define TIME_ELAPSED(d) mfence(); d = (hwtime() - timer_);

FILE* open_benchmark_file(const char* restrict name);
int init_utils(void);
int exit_utils(void);
void flush_all(void* p, size_t size);
void write_list(FILE*restrict fp, unsigned * data, size_t len, const char end_separator);

#endif
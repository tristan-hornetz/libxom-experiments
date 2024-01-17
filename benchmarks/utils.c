#define _GNU_SOURCE
#include <libxom.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sched.h>
#include <unistd.h>
#include "benchmark.h"

static char* str_unknown = "Unknown";
static size_t od_len = 0;
static char* os_version = NULL;
static char cpu_ident[49] = {0, };
unsigned use_rdtscp, cache_line_size;
char* output_directory = DEFAULT_OUTPUT_DIRECTORY;

static uint32_t tsc_denominator = 0, tsc_numerator = 0, tsc_crystal_frequency = 0;

static void get_cpu_ident(char o[49]){
    uint64_t a, b, c, d;
    uint32_t* out = (uint32_t*) o;
    unsigned i;

    for(i = 0; i < 3; i++) {
        __cpuid(0x80000002ul + i, a, b, c, d);
        out[i * 4] = a;
        out[i * 4 + 1] = b;
        out[i * 4 + 2] = c;
        out[i * 4 + 3] = d;
    }

    o[48] = 0;
}

static unsigned get_cache_line_size(void){
    uint64_t a, b, c, d;

    __cpuid(1, a, b, c, d);

    return ((b >> 8) & 0xff) << 3;
}

static void get_linux_version(char* *restrict out){
    size_t len;
    FILE* fp = fopen("/proc/version", "r");
    char* newline;
    if(!fp)
        return;
    *out = NULL;

    getline(out, &len, fp);
    while((newline = strstr(*out, "\n")))
        *newline = 0;
    fclose(fp);
}

static int check_clock_resolution(void){
    struct timespec t;
    int ret = clock_getres(CLOCK_MONOTONIC, &t);
    if(ret < 0)
        return ret;
    if(t.tv_sec > 10)
        return -1;
    return 0;
}

static void prepare_output_dir(){
    if (!access(output_directory, F_OK))
        return;
    mkdir(output_directory, 0777);
}

FILE* open_benchmark_file(const char* restrict name) {
    const size_t nlen = strlen(name);
    char* fpath = malloc(od_len + 2 + nlen);

    FILE* ret;

    if(!fpath)
        return NULL;

    snprintf(fpath, od_len + 2 + nlen, "%s/%s", output_directory, name);
    ret = fopen(fpath, "w");
    free(fpath);

    if(ret){
        if(!os_version)
            os_version = str_unknown;
        fprintf(ret, "_TIMESTAMP = %lu\n", time(NULL));
        fprintf(ret, "_COMPILER = \"%s %d.%d.%d\"\n", COMPILER_NAME, COMPILER_MAJOR, COMPILER_MINOR, COMPILER_PATCH);
        fprintf(ret, "_CPU = \"%s\"\n", cpu_ident);
        fprintf(ret, "_OS = \"%s\"\n", os_version);
        fprintf(ret, "_XOM_MODE = %u\n", get_xom_mode());
        fprintf(ret, "_TSC_DENOMINATOR = 0x%x\n", tsc_denominator);
        fprintf(ret, "_TSC_NUMERATOR= 0x%x\n", tsc_numerator);
        fprintf(ret, "_TSC_CRYSTAL_FREQUENCY = 0x%x\n", tsc_crystal_frequency);

        fprintf(ret, "\n");
    }

    return ret;
}

static void set_processor_affinity(void) {
    cpu_set_t  mask;
    CPU_ZERO(&mask);
    CPU_SET(1, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);
}

int init_utils(void){
    uintptr_t _d;

    od_len = strlen(output_directory);
    use_rdtscp = is_rdtscp_supported();
    cache_line_size = get_cache_line_size();
    get_cpu_ident(cpu_ident);
    get_linux_version(&os_version);
    prepare_output_dir();
    set_processor_affinity();

    // Get TSC information so that we can durations in seconds
    __cpuid(0x15, tsc_denominator, tsc_numerator, tsc_crystal_frequency, _d);

    if(!use_rdtscp)
        printf(STR_WARN "RDTSCP is not supported on this system!\n");
    if(check_clock_resolution() < 0){
        fprintf(stderr, STR_FAIL "Precise clock unavailable! Aborting...\n");
        return -1;
    }
}

int exit_utils(void){
    if(os_version && os_version != str_unknown)
        free(os_version);
}

void write_list(FILE*restrict fp, uint64_t * data, size_t len, const char end_separator){
    size_t i;

    fprintf(fp, "[");
    for(i = 0; i < len; i++){
        fprintf(fp, "0x%lx, ", data[i]);
        if(!((i + 1) % 50)) fprintf(fp, "\n");
    }
    fprintf(fp, "]%c\n",end_separator);
}

void flush_all(void* p, size_t size){
    size_t i;
    uintptr_t d = (uintptr_t) p;
    for(i = 0; i < size; i += cache_line_size)
        clflushi(d + i);
    asm volatile ("sfence");
}
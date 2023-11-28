#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sched.h>
#include "benchmark.h"
#include "libxom.h"

#ifndef PAGE_SIZE
#define PAGE_SIZE 0x1000
#endif


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

    exit_utils();
    return 0;
}

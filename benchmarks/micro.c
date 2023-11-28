#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include "benchmark.h"
#include "libxom.h"

#ifndef PAGE_SIZE
#define PAGE_SIZE 0x1000
#endif

benchmark(nop_slide) {
    uint64_t timer, sum = 0;
    unsigned i = 1000;
    char *nop_slide = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    struct xombuf* nop_slide_xom = xom_alloc_pages(PAGE_SIZE);
    void (*nop_slide_fun)(void) = ((void (*)(void))nop_slide);
    void (*nop_slide_xom_fun)(void);


    memset(nop_slide, 0x90, PAGE_SIZE);
    nop_slide[PAGE_SIZE - 1] = RET;
    xom_write(nop_slide_xom, nop_slide, PAGE_SIZE);
    nop_slide_xom_fun = (void (*)(void)) xom_lock(nop_slide_xom);

    while(i--){
        START_TIMER;
        nop_slide_fun();
        TIME_ELAPSED(timer);
    }

    i = 1000;
    while(i--){
        START_TIMER;
        nop_slide_xom_fun();
        TIME_ELAPSED(timer)
    }

    // TODO: Write results to file

    munmap(nop_slide, PAGE_SIZE);
    xom_free(nop_slide_xom);
    return 0;
}



int main(int argc, char* argv[]){
    if(argc > 1)
        output_directory = argv[1];

    if(init_utils() < 0)
        return 1;

    printf("CL Size: %u\n", cache_line_size);

    run_benchmark(nop_slide);

    exit_utils();
    return 0;
}

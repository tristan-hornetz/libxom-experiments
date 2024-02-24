#include <stdio.h>
#include "libxom.h"
#include "benchmark.h"

#define extern_mmap_benchmark(X) extern_benchmark(mmap##X);
#define extern_lock_benchmark(X) extern_benchmark(lock##X);
#define extern_free_benchmark(X) extern_benchmark(free##X);
#define run_mmap_benchmark(X) run_benchmark(mmap##X);
#define run_lock_benchmark(X) run_benchmark(lock##X);
#define run_free_benchmark(X) run_benchmark(free##X);

// Micro
extern_benchmark(access);
extern_benchmark(access_flush);
extern_benchmark(nop_slide);
extern_benchmark(nop_slide_2_8);
extern_benchmark(primes);
extern_benchmark(jumper);
extern_benchmark(aes);


powers2(extern_mmap_benchmark)
powers2(extern_lock_benchmark)
powers2(extern_free_benchmark)


int main(int argc, char* argv[]){
    const int xom_mode = get_xom_mode();
    if(argc > 1)
        output_directory = argv[1];

    if(!get_xom_mode()){
        fprintf(stderr, STR_FAIL "XOM is not supported! Quit...\n");
        return 1;
    }
    if(xom_mode == XOM_MODE_PKU)
        puts(STR_WARN "SLAT XOM is not supported (did you load modxom?). Using insecure PKU XOM instead ...");

    if(init_utils() < 0)
        return 1;

    run_benchmark(access);
    run_benchmark(access_flush);
    run_benchmark(nop_slide);
    run_benchmark(nop_slide_2_8);
    run_benchmark(primes);
    run_benchmark(jumper);
    run_benchmark(aes);

    //powers2(run_mmap_benchmark)
    //powers2(run_lock_benchmark)
    powers2(run_free_benchmark)

    exit_utils();
    return 0;
}
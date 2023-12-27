#include <stdio.h>
#include "libxom.h"
#include "benchmark.h"

// Micro
extern_benchmark(access);
extern_benchmark(nop_slide);
extern_benchmark(primes);
extern_benchmark(jumper);
extern_benchmark(aes);

// Allocation
extern_benchmark(mmap1);
extern_benchmark(mmap2);
extern_benchmark(mmap4);
extern_benchmark(mmap8);
extern_benchmark(mmap16);
extern_benchmark(mmap32);
extern_benchmark(mmap64);
extern_benchmark(mmap128);
extern_benchmark(mmap256);
extern_benchmark(mmap512);
extern_benchmark(mmap1024);
extern_benchmark(mmap2048);
extern_benchmark(mmap4096);

extern_benchmark(lock1);
extern_benchmark(lock2);
extern_benchmark(lock4);
extern_benchmark(lock8);
extern_benchmark(lock16);
extern_benchmark(lock32);
extern_benchmark(lock64);
extern_benchmark(lock128);
extern_benchmark(lock256);
extern_benchmark(lock512);
extern_benchmark(lock1024);
extern_benchmark(lock2048);
extern_benchmark(lock4096);

extern_benchmark(free1);
extern_benchmark(free2);
extern_benchmark(free4);
extern_benchmark(free8);
extern_benchmark(free16);
extern_benchmark(free32);
extern_benchmark(free64);
extern_benchmark(free128);
extern_benchmark(free256);
extern_benchmark(free512);
extern_benchmark(free1024);
extern_benchmark(free2048);
extern_benchmark(free4096);

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
    run_benchmark(nop_slide);
    run_benchmark(primes);
    run_benchmark(jumper);
    run_benchmark(aes);

    run_benchmark(mmap1);
    run_benchmark(mmap2);
    run_benchmark(mmap4);
    run_benchmark(mmap8);
    run_benchmark(mmap16);
    run_benchmark(mmap32);
    run_benchmark(mmap64);
    run_benchmark(mmap128);
    run_benchmark(mmap256);
    run_benchmark(mmap512);
    run_benchmark(mmap1024);
    run_benchmark(mmap2048);
    run_benchmark(mmap4096);

    run_benchmark(lock1);
    run_benchmark(lock2);
    run_benchmark(lock4);
    run_benchmark(lock8);
    run_benchmark(lock16);
    run_benchmark(lock32);
    run_benchmark(lock64);
    run_benchmark(lock128);
    run_benchmark(lock256);
    run_benchmark(lock512);
    run_benchmark(lock1024);
    run_benchmark(lock2048);
    run_benchmark(lock4096);

    run_benchmark(free1);
    run_benchmark(free2);
    run_benchmark(free4);
    run_benchmark(free8);
    run_benchmark(free16);
    run_benchmark(free32);
    run_benchmark(free64);
    run_benchmark(free128);
    run_benchmark(free256);
    run_benchmark(free512);
    run_benchmark(free1024);
    run_benchmark(free2048);
    run_benchmark(free4096);

    exit_utils();
    return 0;
}
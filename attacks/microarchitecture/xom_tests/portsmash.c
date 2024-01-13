#define _GNU_SOURCE
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/prctl.h>
#include <unistd.h>
#include <wait.h>
#include <sys/mman.h>

#include "cacheutils.h"
#include "microarchitecture.h"
#include "libxom.h"


#define TIMES2(X) X X
#define TIMES4(X) TIMES2(TIMES2(X))
#define countof(x) (sizeof(x)/sizeof(*(x)))


static uint32_t get_sibling_cores(){
    const static size_t max_cpu_cores = 0x100;
    const static char mpath[] = "/proc/cpuinfo";
    char *line = NULL;
    unsigned int corenum;
    int parsed, count = 0, i, j;
    size_t len = 0;
    FILE* info;
    uint8_t cpu_cores[max_cpu_cores];

    info = fopen(mpath, "r");
    if(!info)
        return 1 << 16;

    // Get amount of executable memory regions
    while (getline(&line, &len, info) > 0 && count < max_cpu_cores) {
        parsed = sscanf(line, "core id\t\t: %u", &corenum);
        free(line);
        line = NULL;
        if(parsed <= 0)
            continue;
        cpu_cores[count++] = (uint8_t) corenum;
    }

    fclose(info);

    for(i = count - 1; i >= 0; i--) {
        for(j = i - 1; j >= 0; j--) {
            if(cpu_cores[i] == cpu_cores[j])
                return (((uint32_t) i) << 16) | (uint32_t) j;
        }
    }

    return 1 << 16;
}


static inline uint32_t avg (const uint32_t* v, const uint32_t n){
    uint32_t r = 0;

    for(uint32_t i = 0; i < n; i++)
        r += v[i];

    return r / n;
}

static void __attribute__((aligned(PAGE_SIZE))) port1_victim(size_t num_repetitions){
    asm volatile(
            "lea (%%rip), %%r11\n"
            TIMES4(TIMES4(TIMES4(TIMES4("crc32 %%r8, %%r8\ncrc32 %%r9, %%r9\ncrc32 %%r10, %%r10\n"))))
            "sfence\n"
            "dec %0\n"
            "jz port1_victim_leave\n"
            "jmp *%%r11\n"
            "port1_victim_leave:"
            :: "r"(num_repetitions)
            : "r8", "r9", "r10", "r11"
    );

    asm volatile("port1_victim_end:");
}

extern void port1_victim_end(void);

static void __attribute__((aligned(PAGE_SIZE))) port5_victim(size_t num_repetitions){
    asm volatile(
            "port5_victim_start:\n"
            TIMES4(TIMES4(TIMES4(TIMES4("vpermd %%ymm0, %%ymm1, %%ymm0\n"
                                               "vpermd %%ymm2, %%ymm3, %%ymm2\n"
                                               "vpermd %%ymm4, %%ymm5, %%ymm4\n"))))
            "sfence\n"
            "dec %0\n"
            "jnz port5_victim_start"
            :: "r"(num_repetitions)
            : "ymm0", "ymm1", "ymm2", "ymm3", "ymm4", "ymm5"
    );
}

uint8_t portsmash_generic(uint32_t num_samples, uint8_t xom){
    const uint32_t cores = get_sibling_cores();
    void (*port1_victim_ptr)(size_t num_repetitions) = port1_victim;
    size_t num_pages = (((char*)port1_victim_end - (char*)port1_victim) / PAGE_SIZE) + 1;
    struct xombuf* xbuf = NULL;


    uint32_t start_time, port1_base, port5_base, port1_avg, port5_avg, i;
    uint32_t port1_samples[0x10000], port5_samples[countof(port1_samples)];


    printf("Running on cores %u and %u\n", (cores & 0xffff), (cores >> 16));


    xbuf = xom_alloc_pages(num_pages * PAGE_SIZE);
    xom_write(xbuf, port1_victim, num_pages * PAGE_SIZE, 0);
    port1_victim_ptr = xbuf->address;
    if(xom)
        (void) xom_lock(xbuf);
    else
        mprotect(port1_victim_ptr, num_pages * PAGE_SIZE, PROT_READ | PROT_EXEC);


    asm volatile ("enter_ptrr:");
    port1_victim_ptr(10);
    port5_victim(10);

    for(i = 0; i < countof(port1_samples); i++){
        start_time = rdtsc();
        port1_victim(1);
        port1_samples[i] = rdtsc() - start_time;
        start_time = rdtsc();
        port5_victim(1);
        port5_samples[i] = rdtsc() - start_time;
    }
    port1_base = avg(port1_samples,countof(port1_samples));
    port5_base = avg(port5_samples,countof(port1_samples));

    pid_t pid = fork();
    set_processor_affinity(pid ? (int)(cores & 0xffff) : (int)(cores >> 16));

    if(!pid){
        prctl(PR_SET_PDEATHSIG, SIGHUP);

        port1_victim_ptr(num_samples);
        exit(0);
    }

    printf("Average Port1 time without contention: %u\n"
           "Average Port5 time without contention: %u\n",
           port1_base, port5_base);
    usleep(10000);

    for(i = 0; i < countof(port1_samples); i++){
        start_time = rdtsc();
        port1_victim(1);
        port1_samples[i] = rdtsc() - start_time;
        start_time = rdtsc();
        port5_victim(1);
        port5_samples[i] = rdtsc() - start_time;
    }

    port1_avg = avg(port1_samples, countof(port1_samples));
    port5_avg = avg(port5_samples, countof(port5_samples));


    printf("Average Port1 time with contention: %u\n"
           "Average Port5 time with contention: %u\n",
           port1_avg, port5_avg);

    wait(NULL);
    xom_free(xbuf);

    return (port1_avg > port1_base * 1.4 && port5_avg < port5_base * 1.4) ? 1 : 0;
}

attack_status portsmash_c(uint32_t __attribute__((unused)) success_fraction, uint32_t num_samples) {
  const uint8_t noxom = portsmash_generic(num_samples, 0),
    xom = portsmash_generic(num_samples, 1);

  if(!~noxom || !~xom)
    return (attack_status){{0, 0, 1}};
  return (attack_status){{noxom, xom, 0}};
}

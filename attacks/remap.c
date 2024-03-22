#define _GNU_SOURCE
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/prctl.h>
#include <sys/mman.h>
#include <pthread.h>
#include "libxom.h"

volatile unsigned char check = 0;

static void set_processor_affinity(unsigned int core_id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    pthread_t current_thread = pthread_self();
    pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset);
}

static uint32_t get_sibling_cores(){
    const static size_t max_cpu_cores = 0x100;
    char *line = NULL;
    unsigned int corenum;
    int parsed, count = 0, i, j;
    size_t len = 0;
    FILE* info;
    uint8_t cpu_cores[max_cpu_cores];

    info = fopen( "/proc/cpuinfo", "r");
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

uint32_t sibling_cores;

void __attribute__((aligned(PAGE_SIZE))) loop_asm(void){
    asm volatile(".L1: nop\njmp .L1");
}

void* victim(void (*loop_ptr)(void)){
    prctl(PR_SET_PDEATHSIG, SIGHUP);
    //set_processor_affinity(sibling_cores & 0xffff);
    check = 1;
    asm volatile("call *%0" :: "r"(loop_ptr));
    puts("returned!");
    return NULL;
}

int main() {
    pthread_t thread;
    struct xombuf* xbuf;
    void* victim_loop;
    uint8_t* attack_page;

    int fd;

    sibling_cores = get_sibling_cores();

    xbuf = xom_alloc(PAGE_SIZE);
    xom_write(xbuf, loop_asm, PAGE_SIZE, 0);
    victim_loop = xom_lock(xbuf);
    if(!victim_loop)
        return 1;

    pthread_create(&thread, NULL, (void *(*)(void *)) victim, victim_loop);
    //set_processor_affinity(sibling_cores >> 16);
    while(!check);

    attack_page = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE | MAP_NORESERVE, -1, 0);
    if(!~(uintptr_t)attack_page)
        return 1;

    system("rm -f ./retfile");
    fd = open("./retfile", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    memset(attack_page, 0xc3, PAGE_SIZE);
    write(fd, attack_page, PAGE_SIZE);
    lseek(fd, 0, SEEK_SET);
    munmap(attack_page, PAGE_SIZE);
    //close(fd);
    //fd = open("./retfile",O_RDONLY);

    attack_page = mmap(victim_loop, PAGE_SIZE, PROT_READ | PROT_EXEC, MAP_PRIVATE | MAP_FIXED | MAP_POPULATE, fd, 0);
    if(!~(uintptr_t)attack_page || attack_page != victim_loop){
        printf("Could not remap! Error %d - %d\n", errno, fd);
        return 1;
    }
    ((void(*)(void))victim_loop)();
    puts("Attacker good");

    pthread_join(thread, NULL);
    close(fd);

    return 0;
}
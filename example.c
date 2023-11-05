#include <stdio.h>
#include <errno.h>
#include <setjmp.h>
#include <signal.h>
#include "libxom.h"

typedef void (*pfun)(const char*, size_t);

jmp_buf longjmp_buf;
const char msg[] = "Hello from asm\n";
void __attribute__((aligned(4096))) print_something(const char* pmsg, size_t len){
    asm volatile(   "mov $1, %%rdi\n"
                    "mov %1, %%rsi\n"
                    "mov %2, %%rdx\n"
                    "syscall"
                    :: "a"(1), "g"(pmsg), "g"(len)
                    : "rdi", "rsi", "rdx");
}

static void unblock_signal(int signum) {
    sigset_t sigs;
    sigemptyset(&sigs);
    sigaddset(&sigs, signum);
    sigprocmask(SIG_UNBLOCK, &sigs, NULL);
}

static void segfault_handler(int signum) {
    unblock_signal(signum);
    longjmp(longjmp_buf, 1);
}

int main(){
    int status; 
    pfun print_protected;
    struct xombuf* buf;

    if (signal(SIGSEGV, segfault_handler) == SIG_ERR){
        printf("Could not set up signal handler\n");
        return 1;
    }

    buf = xomalloc(1 << 10);
    if(!buf){
        printf("Could not allocate xom buffer, errno is %d\n", errno);
        return 1;
    }

    status = xom_write(buf, print_something, 48);
    if(status < 0){
        printf("Could not write to xom buffer, errno is %d\n", errno);
        return 1;
    }
    
    print_protected = xom_lock(buf);
    if(!print_protected){
        printf("Could not lock xom buffer, errno is %d\n", errno);
        return 1;
    }

    printf("Attempting to print something: ");
    fflush(stdout);
    if(!setjmp(longjmp_buf))
        print_protected(msg, sizeof(msg));
    else
        printf("Error, got segfault!\n");
    
    printf("Attempting to read from protected memory... ");
    if(!setjmp(longjmp_buf))
        printf("Successfully read %p. This is bad.\n", *(void**)print_protected);
    else 
        printf("caused a segfault, XOM is working!\n");

    xom_free(buf);
    return 0;
}
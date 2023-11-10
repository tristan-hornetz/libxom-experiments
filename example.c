#include <stdio.h>
#include <errno.h>
#include <setjmp.h>
#include <signal.h>
#include "libxom.h"

typedef void (*pfun)(const char *restrict, int(*printf_address)(const char *restrict, ...));

jmp_buf longjmp_buf;
const char msg_format[] = "print_something is located at %p, and was called from %p\n";

void print_something(const char *restrict msg, int(*printf_address)(const char *restrict, ...)) {
    void** rbp;

    asm volatile ("mov %%rbp, %0" : "=r"(rbp));

    // We only copy this function into XOM, not the GOT or PLT.
    // If we want to reloacte this code, we have to give it absolute
    // pointers to everything it needs to access, including printf
    // and the format string

    // Print the address of this function, and the address of the caller
    printf_address(msg, &print_something, rbp[1]);
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

    status = xom_migrate_shared_libraries();
    if(status < 0)
        printf("Could not migrate code! Errno: %d\n", errno);
    else
        printf("Sucessfully migrated all code into XOM!\n");

    if (signal(SIGSEGV, segfault_handler) == SIG_ERR){
        printf("Could not set up signal handler\n");
        return 1;
    }

    buf = xom_alloc(1 << 10);
    if(!buf){
        printf("Could not allocate xom buffer, errno is %d\n", errno);
        return 1;
    }

    status = xom_write(buf, print_something, 0x100);
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
        print_protected(msg_format, printf);
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
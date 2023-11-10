#include <errno.h>
#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include "libxom.h"

#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define CRESET "\e[0m"
#define STR_OK "[" GRN "+" CRESET "] "
#define STR_PEND "[" CYN "*" CRESET "] "
#define STR_FAIL "[" RED "-" CRESET "] "

typedef int(*printf_type)(const char *restrict, ...);
typedef void (*pprint_something)(const char *restrict, printf_type printf_address);

jmp_buf longjmp_buf;
char code_backup[0x100] = {0, };
const char msg_format[] = STR_OK "print_something is located at %p, and was called from %p\n\n";

void print_something(const char *restrict msg, printf_type printf_address) {
    void** rbp;

    asm volatile ("mov %%rbp, %0" : "=r"(rbp));

    // We only copy this function into XOM, not the GOT, PLT or 
    // any data that is stored in a location relative to it.
    // Therefore, once we relocate this code, we have to give it absolute
    // pointers to everything it needs to access, including printf
    // and the format string

    // Print the address of this function, and the address of the caller
    printf_address(msg, &print_something, rbp[1]);
}

// Signal handler code

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

int main(int argc, char* argv[]){
    int status; 
    pprint_something print_protected;
    struct xombuf* buf;
    __sighandler_t old_handler;

    // Copy test function code before we migrate the .text
    // section into XOM
    memcpy(code_backup, print_something, sizeof(code_backup));

    // Migrate all code into XOM, including the code of shared libraries
    printf(STR_PEND "Attempting to migrate code into XOM...\n");
    status = xom_migrate_all_code();
    if(status < 0)
        printf(STR_FAIL "Could not migrate code! Errno: %d\n\n", errno);
    else
        printf(STR_OK "Sucessfully migrated all code into XOM!\n\n");

    // Allocate XOM buffer
    buf = xom_alloc(sizeof(code_backup));
    if(!buf){
        printf(STR_FAIL "Could not allocate xom buffer, errno is %d\n", errno);
        return 1;
    }

    // Write into XOM buffer
    status = xom_write(buf, code_backup, sizeof(code_backup));
    if(status < 0){
        printf(STR_FAIL "Could not write to xom buffer, errno is %d\n", errno);
        return 1;
    }

    // Delete code backup
    memset(code_backup, 0, sizeof(code_backup));
    
    // Lock XOM buffer, obtain pointer to XOM memory region
    print_protected = xom_lock(buf);
    if(!print_protected){
        printf(STR_FAIL "Could not lock xom buffer, errno is %d\n", errno);
        return 1;
    }

    // Set up a signal handler to recover from segfaults
    old_handler = signal(SIGSEGV, segfault_handler);
    if (old_handler == SIG_ERR){
        printf(STR_FAIL "Could not set up signal handler\n");
        return 1;
    }

    // Call the protected code, and recover from segfault if necessary
    printf(STR_PEND "Attempting to print something: \n");
    if(!setjmp(longjmp_buf))
        print_protected(msg_format, printf);
    else
        printf(STR_FAIL "Error, got segfault!\n\n");
    
    // Attempt to read from XOM memory. A segfault is expected here
    printf(STR_PEND "Attempting to read from protected memory...\n");
    if(!setjmp(longjmp_buf))
        printf(STR_FAIL  "Successfully read %p. This is bad.\n", *(void**)print_protected);
    else 
        printf(STR_OK "Caused a segfault, XOM is working!\n");

    // Restore segfault handler
    signal(SIGSEGV, old_handler);

    // Free XOM buffer
    xom_free(buf);
    return 0;
}
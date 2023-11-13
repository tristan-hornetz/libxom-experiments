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

#define try_segv if (!setjmp(longjmp_buf))
#define catch_segv else

typedef int (*printf_type) (const char *restrict, ...);
typedef void (*pprint_something) (const char *restrict, printf_type printf_address);

jmp_buf longjmp_buf;
const char msg_format[] = STR_OK "I am located at %p, and was called from %p\n\n";
char code_backup[0x100] = {0, };


// We only copy this function into XOM, not the GOT, PLT or 
// any data that is stored in a location relative to it.
// Therefore, once we relocate this code, we have to give it absolute
// pointers to everything it needs to access. In our case, this is 
// printf and the format string
void print_something(const char *restrict msg, printf_type printf_address) {
    void** rbp;

    asm volatile ("mov %%rbp, %0" : "=r"(rbp));

    // Print the address of this function, and the address of the caller
    printf_address(msg, &print_something, rbp[1]);
}

// Signal handler stuff
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

static void test_code_migration(){
    int status;

    printf(STR_PEND "==== Testing Code Migration ====\n");

    // Migrate all code into XOM, including the code of shared libraries
    printf(STR_PEND "Attempting to migrate code into XOM...\n");

    // This is where the magic happens
    status = xom_migrate_all_code();
    
    if(status < 0)
        printf(STR_FAIL "Could not migrate code! Errno: %d\n\n", errno);
    else
        printf(STR_OK "Sucessfully migrated all code into XOM!\n\n");

    
    // Attempt to read the code of the main function
    // This should result a segfault
    printf(STR_PEND "Attempting to read our own code:\n");

    try_segv {
        printf(STR_FAIL  "Successfully read %p. This is bad.\n\n", *(void**)test_code_migration);
    } catch_segv { 
        printf(STR_OK "Caused a segfault, XOM is working!\n\n");
    }
}

static void test_subpage_xom(){
    pprint_something print_protected;
    struct xom_subpages* subpages;
    printf(STR_PEND "==== Testing Subpage XOM ====\n");

    subpages = xom_alloc_subpages(4 * PAGE_SIZE);
    if(!subpages){
        printf(STR_FAIL "Could not allocate subpages! Errno: %d\n\n", errno);
        return;
    }

    print_protected = (pprint_something) xom_fill_and_lock_subpages(subpages, sizeof(code_backup), code_backup);
    if(!print_protected){
        printf(STR_FAIL "Could not fill subpages! Errno: %d\n\n", errno);
        goto exit;
    }

    printf(STR_PEND "Attempting to call print_something in subpage-level XOM buffer:\n");
    try_segv {
        print_protected(msg_format, printf);
    } catch_segv {
        printf(STR_FAIL "Error, got segfault!\n\n");
    }
    
    // Attempt to read from XOM memory. A segfault is expected here
    printf(STR_PEND "Attempting to read from subpage-level XOM buffer...\n");
    try_segv {
        printf(STR_FAIL "Successfully read %p. This is bad.\n", *(void**)print_protected);
    } catch_segv { 
        printf(STR_OK "Caused a segfault, XOM is working!\n");
    }

    exit:
    xom_free_subpages(subpages);
}

static void test_xom_buffers(){
    int status;
    pprint_something print_protected;
    struct xombuf* buf;

    printf("\n" STR_PEND "==== Testing XOM Buffers ====\n");

    // Allocate XOM buffer
    buf = xom_alloc_pages(sizeof(code_backup));

    if(!buf){
        printf(STR_FAIL "Could not allocate XOM buffer, errno is %d\n", errno);
        return;
    }

    // Write into XOM buffer
    status = xom_write(buf, code_backup, sizeof(code_backup));

    if(status < 0){
        printf(STR_FAIL "Could not write to XOM buffer, errno is %d\n", errno);
        return;
    }

    // Delete code backup
    memset(code_backup, 0, sizeof(code_backup));
    
    // Lock XOM buffer, obtain pointer to XOM memory region
    print_protected = xom_lock(buf);

    if(!print_protected){
        printf(STR_FAIL "Could not lock XOM buffer, errno is %d\n", errno);
        return;
    }

    // Call the protected code, and recover from segfault if necessary
    printf(STR_PEND "Attempting to call print_something in XOM buffer:\n");
    
    try_segv {
        print_protected(msg_format, printf);
    } catch_segv {
        printf(STR_FAIL "Error, got segfault!\n\n");
    }
    
    // Attempt to read from XOM memory. A segfault is expected here
    printf(STR_PEND "Attempting to read from XOM buffer...\n");
    try_segv {
        printf(STR_FAIL "Successfully read %p. This is bad.\n", *(void**)print_protected);
    } catch_segv { 
        printf(STR_OK "Caused a segfault, XOM is working!\n");
    }

    // Free XOM buffer
    xom_free(buf);
}

int main(int argc, char* argv[]){
    __sighandler_t old_handler;

    // Copy test function code before we migrate the .text
    // section into XOM. Afterwards, reading the code will no
    // longer be possible
    memcpy(code_backup, print_something, sizeof(code_backup));

    // Set up a signal handler to recover from segfaults
    old_handler = signal(SIGSEGV, segfault_handler);
    if (old_handler == SIG_ERR){
        printf(STR_FAIL "Could not set up signal handler\n");
        return 1;
    }

    // Migrate all code to XOM, and test whether it is working
    test_code_migration();

    // Test XOM buffer feature
    test_xom_buffers();

    // Test subpage-level XOM
    test_subpage_xom();

    // Restore segfault handler
    signal(SIGSEGV, old_handler);

    return 0;
}
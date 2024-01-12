#define _GNU_SOURCE
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

// Define this code as an array so that we can access it at runtime
const uint8_t cause_gp_fault[] = {
    0x48, 0x31, 0xc0,   // xor    %rax,%rax
    0x48, 0x8b, 0x00,   // mov    (%rax),%rax
};

jmp_buf longjmp_buf;
const char msg_format[] = STR_OK "I am located at %p, and was called from %p\n";
char code_backup[0x100] = {0, };


// We only copy this function into XOM, not the GOT, PLT or 
// any data that is stored in a location relative to it.
// Therefore, once we relocate this code, we have to give it absolute
// pointers to everything it needs to access. In our case, this is 
// printf and the format string
void print_something(const char *restrict msg, printf_type printf_address) {
    void** rbp;
    // r15 may be cleared by the hypervisor on interrupt, so tell the compiler to back it up
    volatile register void* r15 asm("r15") = 0;

    asm volatile ("mov %%rbp, %0" : "=r"(rbp));

    // Print the address of this function, and the address of the caller
    printf_address(msg, &print_something, rbp[1]);

    asm volatile("" ::: "r15");
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
        printf(STR_FAIL "Could not migrate code! Errno: %d\n", errno);
    else
        printf(STR_OK "Sucessfully migrated all code into XOM!\n");

    
    // Attempt to read the code of the main function
    // This should result a segfault
    printf(STR_PEND "Attempting to read our own code:\n");

    try_segv {
        printf(STR_FAIL  "Successfully read %p. This is bad.\n", *(void**)test_code_migration);
    } catch_segv { 
        printf(STR_OK "Caused a segfault, XOM is working!\n");
    }
}

static void test_xom_buffers(){
    int status;
    pprint_something print_protected;
    struct xombuf* buf;

    printf(STR_PEND "==== Testing XOM Buffers ====\n");

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
        printf(STR_FAIL "Error, got segfault!\n");
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


static void test_subpage_xom(){
    unsigned i;
    pprint_something print_protected;
    struct xom_subpages* subpages;
    printf(STR_PEND "==== Testing Subpage XOM ====\n");

    subpages = xom_alloc_subpages(4 * PAGE_SIZE);
    if(!subpages){
        printf(STR_FAIL "Could not allocate subpages! Errno: %d\n", errno);
        return;
    }

    print_protected = (pprint_something) xom_fill_and_lock_subpages(subpages, sizeof(code_backup), code_backup);
    if(!print_protected){
        printf(STR_FAIL "Could not fill subpages! Errno: %d\n", errno);
        goto exit;
    }

    printf(STR_PEND "Attempting to call print_something in subpage-level XOM buffer:\n", (void*) print_protected);
    try_segv {
        print_protected(msg_format, printf);
    } catch_segv {
        printf(STR_FAIL "Error, got segfault!\n");
    }
    
    // Attempt to read from XOM memory. A segfault is expected here
    printf(STR_PEND "Attempting to read from subpage-level XOM buffer...\n");
    try_segv {
        printf(STR_FAIL "Successfully read %p. This is bad.\n", *(void**)print_protected);
    } catch_segv { 
        printf(STR_OK "Caused a segfault, XOM is working!\n");
    }

    printf(STR_PEND "Attempting to fill other subpages:\n");
    for(i = 0; i < 20; i++){
        print_protected = (pprint_something) xom_fill_and_lock_subpages(subpages, 2 * SUBPAGE_SIZE + 1, code_backup);
        if(!print_protected){
            printf(STR_FAIL "Could not fill subpages! Errno: %d\n", errno);
            goto exit;
        }
        try_segv {
            asm volatile ("movq %%rax, %%xmm0" :: "a"(0xbabababa));
            print_protected(msg_format, printf);
        } catch_segv {
            printf(STR_FAIL "Error, got segfault!\n");
        }
    }


    exit:
    xom_free_all_subpages(subpages);
}

int test_secret_page(){
    void (*secret_aes_fun)(void *icb, void* x, void *y, unsigned int num_blocks) = NULL;
    struct xombuf* xbuf;
    char X[16] = {0, }, Y[16], ICB[16] = {1, 2, 3 , 4, 5, 6, 7, 8, 0, };

    printf(STR_PEND "==== Testing Secret Page ====\n");

    xbuf = xom_alloc_pages(PAGE_SIZE);
    if(!xbuf){
        printf(STR_FAIL "Could not allocate XOM buffer! Errno: %d\n", errno);
        return -1;
    }
    secret_aes_fun = xom_get_secret_page(xbuf);
    if(!secret_aes_fun){
        printf(STR_FAIL "Could get secret page! Errno: %d\n", errno);
        return -1;
    }

    printf(STR_PEND "Attempting to read secret page directly:\n");
    try_segv {
        printf(STR_FAIL "Successfully read %p. This is bad.\n", *(void**)secret_aes_fun);
    } catch_segv {
        printf(STR_OK "Caused a segfault, XOM is working!\n");
    }

    printf(STR_PEND "Attempting to call secret function...\n");
    try_segv {
        secret_aes_fun(ICB, X, Y, 1);
        printf(STR_OK "OK!\n");
    } catch_segv {
        printf(STR_FAIL "Caused a segfault! This is bad.\n");
    }

    xom_free(xbuf);
    return 0;
}

// Invoked by the reg_clear test
static void clear_reg_handler(int signum, siginfo_t * siginfo, ucontext_t * context) {
    const static uint64_t r15_vector_cleared_state = 0xbabababababababa;
    const static uint64_t r15_all_cleared_state = 0xdadadadadadadada;
    uint64_t r15 = context->uc_mcontext.gregs[REG_R15];
    uint64_t r12 = context->uc_mcontext.gregs[REG_R12];
    uint64_t rip = context->uc_mcontext.gregs[REG_RIP];
    uint64_t __attribute__((aligned(16))) xmm0[2] = {0, 0};

    unblock_signal(signum);

    // Restore state of Vector registers
    asm volatile ("xrstor (%0)" :: "r"(context->uc_mcontext.fpregs), "a"(7), "d"(0) );

    // Load XMM10, which we primed earlier
    asm volatile ("movaps %%xmm10, %0" : "=m"(xmm0));

    // These register values should be the same as when the fault was triggered
    // If they differ from this state, the hypervisor has intervened, which is what we want

    if(xmm0[0] || xmm0[1]){
        printf(STR_FAIL "xmm10 is (0x%lx, 0x%lx), but should be zero!\n", xmm0[0], xmm0[1]);
    } else {
        printf(STR_OK "xmm10 was cleared by the Hypervisor!\n");
    }

    if(r15 == r15_vector_cleared_state){
        printf(STR_OK "r15 was cleared by the Hypervisor!\n");
        if(r12)
            printf(STR_OK "r12 was not modified!\n");
        else
            printf(STR_FAIL "r12 was cleared, but should not been!\n");
        if(rip)
            printf(STR_OK "rip was not modified\n");
        else
            printf(STR_FAIL "rip was cleared, but should not been!\n");
    }
    else if(r15 == r15_all_cleared_state){
        printf(STR_OK "r15 was cleared by the Hypervisor!\n");
        if(!r12)
            printf(STR_OK "r12 was cleared by the Hypervisor!\n");
        else
            printf(STR_FAIL "r12 is 0x%lx, but should be zero!\n", r12);
        if(!rip)
            printf(STR_OK "rip was cleared by the Hypervisor!\n");
        else
            printf(STR_FAIL "rip is 0x%lx, but should be zero!\n", r12);
    }
    else 
         printf(STR_FAIL "r15 is 0x%lx, but should be 0x%lx or 0x%lx!\n", r15, r15_vector_cleared_state, r15_all_cleared_state);

    longjmp(longjmp_buf, 1);
}

// We must set up a different fault handler for the register-clear test,
// since we need access to the xsave block
static void setup_reg_clear_fault_handler(){
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = (void*) clear_reg_handler;
    sigaction(SIGSEGV, &sa, NULL);
}


int test_vector_reg_clear(void){
    int status;
    uint64_t r15;
    uint64_t __attribute__((aligned(16))) xmm0[2] = {0xabc, 0xdef};
    struct xom_subpages* subpages;
    size_t (*gp_fault)(void) = NULL;

    // Tell the compiler to back up r15
    volatile register uint64_t __r15 asm("r15") = 0x123;

    printf(STR_PEND "==== Testing Vector Register Clear ====\n");

    subpages = xom_alloc_subpages(PAGE_SIZE);
    if(!subpages){
        printf(STR_FAIL "Could not allocate subpages! Errno: %d\n", errno);
        return -1;
    }

    gp_fault = xom_fill_and_lock_subpages(subpages, sizeof(cause_gp_fault), cause_gp_fault);
    if(!gp_fault)
        return -1;

    status = xom_mark_register_clear_subpage(subpages, 0, 0);
    if(status < 0){
        printf(STR_FAIL "Could not mark page for register clearing! Errno: %d\n", -status);
        return -1;
    }


    // Fill the registers with non-standard values
    asm volatile(   "mov $0x123456, %%r15\n"
                    "movaps (%0), %%xmm10\n" 
                ::  "r"(xmm0)
            );

    printf(STR_PEND "Primed registers with non-standard values. Causing interrupt...\n");


    try_segv {
        // Trigger a fault while inside a marked XOM subpage.
        // This will be handled by the hypervisor, which will
        // overwrite the r15 register and sse/avx registers
        gp_fault();
    } catch_segv {;}

    xom_free_subpages(subpages, gp_fault);

    // Tell the compiler that the value in %r15 is still required, so it should not be touched
    asm volatile("" ::: "r15");
    return 0;
}

int test_full_reg_clear(void){
    int status;
    uint64_t r15;
    uint64_t __attribute__((aligned(16))) xmm0[2] = {0xabc, 0xdef};
    struct xom_subpages* subpages;
    size_t (*gp_fault)(void) = NULL;

    // Push callee-saved registers RBX, RDI, RSI, R12, R13, R14, and R15 to stack
    volatile register uint64_t __rbx asm("rbx") = 0xabc;
    volatile register uint64_t __rdi asm("rdi") = 0xabc;
    volatile register uint64_t __rsi asm("rsi") = 0xabc;
    volatile register uint64_t __r12 asm("r12") = 0xabc;
    volatile register uint64_t __r13 asm("r13") = 0xabc;
    volatile register uint64_t __r14 asm("r14") = 0xabc;
    volatile register uint64_t __r15 asm("r15") = 0xabc;

    printf(STR_PEND "==== Testing Full Register Clear ====\n");

    subpages = xom_alloc_subpages(PAGE_SIZE);
    if(!subpages){
        printf(STR_FAIL "Could not allocate subpages! Errno: %d\n", errno);
        return -1;
    }

    gp_fault = xom_fill_and_lock_subpages(subpages, sizeof(cause_gp_fault), cause_gp_fault);
    if(!gp_fault)
        return -1;

    status = xom_mark_register_clear_subpage(subpages, 1, 0);
    if(status < 0){
        printf(STR_FAIL "Could not mark page for register clearing! Errno: %d\n", -status);
        return -1;
    }


    // Fill the registers with non-standard values
    asm volatile(   "mov $0x123456, %%r15\n"
                    "mov $0x123456, %%r12\n"
                    "movaps (%0), %%xmm10\n"
                ::  "r"(xmm0)
            );

    printf(STR_PEND "Primed registers with non-standard values. Causing interrupt...\n");

    try_segv {
        // Trigger a fault while inside a XOM subpage.
        // This will be handled by the hypervisor, which will
        // overwrite the r15 register and sse/avx registers
        gp_fault();
    } catch_segv {;}

    xom_free_subpages(subpages, gp_fault);

    asm volatile("" ::: "r15");
    return 0;
}


int main(int argc, char* argv[]){
    __sighandler_t old_handler;

    // Copy test function code before we migrate the .text
    // section into XOM. Afterward, reading the code will no
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
    printf("\n\n");

    // Test XOM buffer feature
    test_xom_buffers();
    printf("\n\n");

    // Test subpage-level XOM
    test_subpage_xom();
    printf("\n\n");

    // Test secret page
    test_secret_page();
    printf("\n\n");

    setup_reg_clear_fault_handler();

    // Test hypervisor-based vector register clearing on interrupt
    test_vector_reg_clear();
    printf("\n\n");

    test_full_reg_clear();
    printf("\n\n");

    // Restore segfault handler
    signal(SIGSEGV, old_handler);

    printf("Done!\n");

    return 0;
}
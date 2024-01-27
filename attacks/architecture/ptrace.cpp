#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>
#include <sys/ptrace.h>
#include <sys/prctl.h>
#include <sys/user.h>
#include <sys/wait.h>
#include "libxom.h"
#include <array>
#include <unordered_map>

#define FIB_MAX 5
#define NUM_ITERATIONS 500

// Victim function
extern "C" size_t get_fibonacci(size_t n, size_t* accumulator);

jmp_buf longjmp_buf;

struct processor_state{
    user_regs_struct regs;
    user_fpregs_struct fpregs;
    std::unordered_map<uintptr_t, uintptr_t> memory;
};

[[noreturn]] static void victim(size_t (*get_fibonacci_xom)(size_t, size_t*)){
    size_t buf[FIB_MAX + 1];
    // Terminate when parent terminates
    prctl(PR_SET_PDEATHSIG, SIGHUP);
    for(;;)
        get_fibonacci_xom(FIB_MAX, buf);
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

static void recover_memory_state_child(const pid_t child_pid, processor_state& state){
    unsigned char dest;
    uintptr_t n;
    const auto& regs = state.regs;
    const std::array<uintptr_t, 16> reg_values = {regs.r15, regs.r14, regs.r13, regs.r12, regs.r11, regs.r10, regs.r9,
                                           regs.r8, regs.rax, regs.rbx, regs.rcx, regs.rdx, regs.rdi, regs.rsi,
                                           regs.rbp, regs.rsp};

    for (auto v: reg_values) {
        state.memory[v] = ptrace(PTRACE_PEEKDATA, child_pid, v, 0);
    }
}

static void debug_cycle(const pid_t child_pid) {
    int status = 0;
    size_t num_iterations = NUM_ITERATIONS;
    processor_state pre, post;

    while (num_iterations--) {
        do {
            waitpid(child_pid, &status, 0);
        } while(!WIFSTOPPED(status));

        memcpy(&pre.regs, &post.regs, sizeof(post.regs));
        memcpy(&pre.fpregs, &post.fpregs, sizeof(post.fpregs));
        pre.memory = std::move(post.memory);
        post.memory = std::unordered_map<uintptr_t, uintptr_t>();


        if (ptrace(PTRACE_GETREGS, child_pid, NULL, &post.regs) < 0){
            printf("Ptrace get user regs failed - errno %d\n", errno);
            break;
        }
        printf("%llx\n", post.regs.rip);

        if (ptrace(PTRACE_GETFPREGS, child_pid, NULL, &post.fpregs) < 0){
            printf("Ptrace get user fpregs failed - errno %d\n", errno);
            break;
        }
        recover_memory_state_child(child_pid, post);

        if (ptrace(PTRACE_SINGLESTEP, child_pid, NULL, NULL) < 0){
            printf("Ptrace single step failed - errno %d\n", errno);
            break;
        }
    }
}

pid_t _child_pid;

int main(){
    size_t buf[FIB_MAX + 1];
    size_t (*get_fibonacci_xom)(size_t, size_t*);
    pid_t child_pid;
    struct xombuf* xbuf = xom_alloc(PAGE_SIZE);

    fclose(stderr);

    if(!xbuf){
        puts("Could allocate XOM buffer!");
    }
    xom_write(xbuf, reinterpret_cast<const void *>(get_fibonacci), PAGE_SIZE, 0);

    get_fibonacci_xom = reinterpret_cast<size_t (*)(size_t, size_t*)>(xom_lock(xbuf));
    if(!get_fibonacci_xom){
        puts("Could not lock XOM buffer!");
        return 1;
    }

    child_pid = _child_pid = fork();
    if(!child_pid)
        victim(get_fibonacci_xom);

    usleep(500);


    if (ptrace(PTRACE_ATTACH, child_pid, NULL, NULL) < 0) {
        printf("Ptrace attach failed - errno %d\n", errno);
        return 1;
    }

    debug_cycle(child_pid);

    ptrace(PTRACE_DETACH, child_pid, NULL, NULL);


    return 0;
}
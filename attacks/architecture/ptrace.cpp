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
#include "instructions.h"
#include <array>

#define FIB_MAX 5
#define NUM_ITERATIONS 500

// Victim function
extern "C" size_t get_fibonacci(size_t n, size_t* accumulator);



jmp_buf longjmp_buf;

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

extern "C" void emu_hook(uc_engine *uc, uint32_t intno, void *user_data) {
    uintptr_t rip;
    if(!uc)
        return;
    uc_reg_read(uc, UC_X86_REG_RIP, &rip);
    //if((crip & 0xff) == 0x10  && (rip & 0xff) == 0x13) printf("HOOK\n");
    if(rip != crip)
        uc_emu_stop(uc);
}


static void recover_memory_state_child(const pid_t child_pid, uc_engine* uc, processor_state& state){
    unsigned char dest;
    uintptr_t n;
    const auto& regs = state.regs;
    const std::array<uintptr_t, 16> reg_values = {regs.r15, regs.r14, regs.r13, regs.r12, regs.r11, regs.r10, regs.r9,
                                           regs.r8, regs.rax, regs.rbx, regs.rcx, regs.rdx, regs.rdi, regs.rsi,
                                           regs.rbp, regs.rsp};
    for (auto v: reg_values){
        if(uc_mem_read(uc, v, &dest, sizeof(dest)) == UC_ERR_OK){

            state.memory[v] = ptrace(PTRACE_PEEKDATA, child_pid, v, 0);
            //printf("%lx\n", state.memory[v]);
        }
    }
}

static void debug_cycle(const pid_t child_pid, uc_engine* uc, ks_engine* ks) {
    int status = 0, check = 1;
    size_t num_iterations = NUM_ITERATIONS;
    processor_state pre, post;
    uc_context* context_backup;
    uc_context_alloc(uc, &context_backup);

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
        recover_memory_state_child(child_pid, uc, post);

        if(check){
            check = 0;
            uc_context_save(uc, context_backup);
        } else {
            process_instruction(uc, context_backup, ks, pre, post);
        }

        if (ptrace(PTRACE_SINGLESTEP, child_pid, NULL, NULL) < 0){
            printf("Ptrace single step failed - errno %d\n", errno);
            break;
        }
    }

    uc_context_free(context_backup);
}

static int copy_address_space_into_emulator(uc_engine* uc){
    const static char mpath[] = "/proc/self/maps";
    char perms[3] = {0,};
    char *line = NULL;
    int status;
    size_t start, end, len = 0;
    FILE *maps;


    maps = fopen(mpath, "r");
    if (!maps)
        return -1;

    // Get amount of executable memory regions
    while (getline(&line, &len, maps) > 0) {
        status = sscanf(line, "%lx-%lx %c%c%c", &start, &end, &perms[0], &perms[1], &perms[2]);
        free(line);
        line = NULL;
        if (status != 5)
            continue;

        uc_mem_map(uc, start, end - start, UC_PROT_ALL);
        if(perms[0] != 'r')
            continue;

        if(!setjmp(longjmp_buf))
            uc_mem_write(uc, start, reinterpret_cast<void*>(start), end - start);
    }

    fclose(maps);
    return 0;
}

pid_t _child_pid;

void ddetach(){
    ptrace(PTRACE_DETACH, _child_pid, NULL, NULL);
}

int main(){
    uc_engine *uc;
    uc_err err;
    ks_engine* ks;
    ks_err kerr;
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



    err = uc_open(UC_ARCH_X86, UC_MODE_64, &uc);
    if (err != UC_ERR_OK) {
        printf("uc_open() failed\n");
        return -1;
    }

    if (ptrace(PTRACE_ATTACH, child_pid, NULL, NULL) < 0) {
        printf("Ptrace attach failed - errno %d\n", errno);
        return 1;
    }

    kerr = ks_open(KS_ARCH_X86, KS_MODE_64, &ks);
    if (kerr != KS_ERR_OK) {
      printf("ks_open failed \n");
      return -1;
    }
    kerr = ks_option(ks, KS_OPT_SYNTAX, KS_OPT_SYNTAX_ATT);
    if (kerr != KS_ERR_OK) {
      printf("ks_option failed \n");
      return -1;
    }

    auto old_sigbus_handler = signal(SIGBUS, segfault_handler);
    auto old_sigsegv_handler = signal(SIGSEGV, segfault_handler);
    if(copy_address_space_into_emulator(uc) < 0)
        return 1;

    signal(SIGBUS, old_sigbus_handler);
    signal(SIGSEGV, old_sigsegv_handler);

    debug_cycle(child_pid, uc, ks);

    ptrace(PTRACE_DETACH, child_pid, NULL, NULL);

    for(const auto& r: reconstruction_state){
        printf("%lx: %lu\n", r.first, r.second.size());
    }

    return 0;
}
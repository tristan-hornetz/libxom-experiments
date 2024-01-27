#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <sys/stat.h>
#include <sys/ptrace.h>
#include <sys/prctl.h>
#include <sys/user.h>
#include <sys/wait.h>
#include "libxom.h"
#include <array>
#include <vector>
#include <unordered_map>

#define FIB_MAX 5
#define NUM_ITERATIONS 500

// Victim function
extern "C" size_t get_fibonacci(size_t n, size_t* accumulator);

static std::vector<std::pair<uintptr_t, uintptr_t>> maps;

const static char processor_state_def[] =
        "class ProcessorState:\n"
        "    def __init__(self, regs: dict, fpregs: dict, memory: dict) -> None:\n"
        "        self.regs = regs\n"
        "        self.fpregs = fpregs\n"
        "        self.memory = memory";

static void print_registers(FILE* f, const user_regs_struct& regs) {
    fprintf(f, "    {\n");
    fprintf(f, "        \"r15\": 0x%llx,\n", regs.r15);
    fprintf(f, "        \"r14\": 0x%llx,\n", regs.r14);
    fprintf(f, "        \"r13\": 0x%llx,\n", regs.r13);
    fprintf(f, "        \"r12\": 0x%llx,\n", regs.r12);
    fprintf(f, "        \"rbp\": 0x%llx,\n", regs.rbp);
    fprintf(f, "        \"rbx\": 0x%llx,\n", regs.rbx);
    fprintf(f, "        \"r11\": 0x%llx,\n", regs.r11);
    fprintf(f, "        \"r10\": 0x%llx,\n", regs.r10);
    fprintf(f, "        \"r9\": 0x%llx,\n", regs.r9);
    fprintf(f, "        \"r8\": 0x%llx,\n", regs.r8);
    fprintf(f, "        \"rax\": 0x%llx,\n", regs.rax);
    fprintf(f, "        \"rcx\": 0x%llx,\n", regs.rcx);
    fprintf(f, "        \"rdx\": 0x%llx,\n", regs.rdx);
    fprintf(f, "        \"rsi\": 0x%llx,\n", regs.rsi);
    fprintf(f, "        \"rdi\": 0x%llx,\n", regs.rdi);
    fprintf(f, "        \"orig_rax\": 0x%llx,\n", regs.orig_rax);
    fprintf(f, "        \"rip\": 0x%llx,\n", regs.rip);
    fprintf(f, "        \"cs\": 0x%llx,\n", regs.cs);
    fprintf(f, "        \"eflags\": 0x%llx,\n", regs.eflags);
    fprintf(f, "        \"rsp\": 0x%llx,\n", regs.rsp);
    fprintf(f, "        \"ss\": 0x%llx,\n", regs.ss);
    fprintf(f, "        \"fs_base\": 0x%llx,\n", regs.fs_base);
    fprintf(f, "        \"gs_base\": 0x%llx,\n", regs.gs_base);
    fprintf(f, "        \"ds\": 0x%llx,\n", regs.ds);
    fprintf(f, "        \"es\": 0x%llx,\n", regs.es);
    fprintf(f, "        \"fs\": 0x%llx,\n", regs.fs);
    fprintf(f, "        \"gs\": 0x%llx,\n", regs.gs);
    fprintf(f, "    },");
}

static void print_memory(FILE* f, const std::unordered_map<uintptr_t, uintptr_t> & memory){
    fprintf(f, "    {\n");
    for(const auto& p: memory)
        fprintf(f, "0x%lx: 0x%lx, \n", p.first, p.second);
    fprintf(f, "    },");
}

struct processor_state {
    user_regs_struct regs;
    user_fpregs_struct fpregs;
    std::unordered_map<uintptr_t, uintptr_t> memory;

    inline processor_state() : regs(), fpregs() {
        memset(&regs, 0, sizeof(regs));
        memset(&fpregs, 0, sizeof(fpregs));
    }

    void print(FILE* f) const {
        fprintf(f, "ProcessorState(\n");
        print_registers(f, regs);
        fprintf(f, " {}, ");
        print_memory(f, memory);
        fprintf(f, "),\n");
    }
};

static int get_maps() {
    const static char mpath[] = "/proc/self/maps";
    char perms[3] = {0,};
    char *line = NULL;
    int status;
    uintptr_t start, end, len = 0;
    FILE *mapsf;

    mapsf = fopen(mpath, "r");
    if (!mapsf)
        return -1;

    while (getline(&line, &len, mapsf) > 0) {
        status = sscanf(line, "%lx-%lx %c%c%c", &start, &end, &perms[0], &perms[1], &perms[2]);
        free(line);
        line = NULL;
        if (status != 5)
            continue;
        maps.emplace_back(start, end);
    }

    fclose(mapsf);
    return 0;
}

[[noreturn]] static void victim(size_t (*get_fibonacci_xom)(size_t, size_t*)){
    size_t buf[FIB_MAX + 1];
    // Terminate when parent terminates
    prctl(PR_SET_PDEATHSIG, SIGHUP);
    for(;;)
        get_fibonacci_xom(FIB_MAX, buf);
}

static void prepare_output_dir(const char* output_directory){
    if (!access(output_directory, F_OK))
        return;
    mkdir(output_directory, 0777);
}

static void recover_memory_state_child(const pid_t child_pid, processor_state& state){
    unsigned char dest;
    uintptr_t n;
    const auto& regs = state.regs;
    const std::array<uintptr_t, 16> reg_values = {regs.r15, regs.r14, regs.r13, regs.r12, regs.r11, regs.r10, regs.r9,
                                           regs.r8, regs.rax, regs.rbx, regs.rcx, regs.rdx, regs.rdi, regs.rsi,
                                           regs.rbp, regs.rsp};

    // Retrieve memory to which a pointer exists in registers
    for (auto v: reg_values) {
        for (const auto& p: maps){
            if(v >= p.first && v < p.second){
                state.memory[v] = ptrace(PTRACE_PEEKDATA, child_pid, v, 0);
                break;
            }
        }
    }

    for(uintptr_t p = regs.rsp; p <= regs.rbp; p+=sizeof(p)){
        state.memory[p] = ptrace(PTRACE_PEEKDATA, child_pid, p, 0);
    }
}

static void debug_cycle(const pid_t child_pid, const char* output_directory) {
    int status = 0;
    size_t num_iterations = NUM_ITERATIONS;
    processor_state state;
    char outfile[0x400];

    snprintf(outfile, sizeof(outfile), "%s/trace.py", output_directory);

    auto f = fopen(outfile, "w");
    if(!f)
        return;

    fprintf(f, "%s\n\nvictim_register_trace = [\n", processor_state_def);

    while (num_iterations--) {
        do {
            waitpid(child_pid, &status, 0);
        } while(!WIFSTOPPED(status));


        state.memory = std::unordered_map<uintptr_t, uintptr_t>();


        if (ptrace(PTRACE_GETREGS, child_pid, NULL, &state.regs) < 0){
            printf("Ptrace get user regs failed - errno %d\n", errno);
            break;
        }
        printf("%llx\n", state.regs.rip);

        if (ptrace(PTRACE_GETFPREGS, child_pid, NULL, &state.fpregs) < 0){
            printf("Ptrace get user fpregs failed - errno %d\n", errno);
            break;
        }
        recover_memory_state_child(child_pid, state);

        state.print(f);

        if (ptrace(PTRACE_SINGLESTEP, child_pid, NULL, NULL) < 0){
            printf("Ptrace single step failed - errno %d\n", errno);
            break;
        }
    }

    fprintf(f, "]\n");

    fclose(f);
}

int main(int argc, char* argv[]){
    size_t buf[FIB_MAX + 1];
    size_t (*get_fibonacci_xom)(size_t, size_t*);
    pid_t child_pid;
    struct xombuf* xbuf = xom_alloc(PAGE_SIZE);
    const char* output_directory = ".";

    if(argc > 1){
        output_directory = argv[1];
        prepare_output_dir(output_directory);
    }

    get_maps();

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

    child_pid = fork();
    if(!child_pid)
        victim(get_fibonacci_xom);

    usleep(500);


    if (ptrace(PTRACE_ATTACH, child_pid, NULL, NULL) < 0) {
        printf("Ptrace attach failed - errno %d\n", errno);
        return 1;
    }

    debug_cycle(child_pid, output_directory);

    ptrace(PTRACE_DETACH, child_pid, NULL, NULL);


    return 0;
}
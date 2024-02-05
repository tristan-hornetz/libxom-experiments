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
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <set>

#define FIB_MAX 5
#define NUM_ITERATIONS 5000

// Victim function
extern "C" size_t get_fibonacci(size_t n, size_t* accumulator);

static std::vector<std::pair<uintptr_t, uintptr_t>> maps;
static std::set<uintptr_t> instructions_covered;

const static char processor_state_def[] =
        "class ProcessorState:\n"
        "    def __init__(self, regs: dict, fpregs: dict, memory: dict, pre: bool) -> None:\n"
        "        self.regs = regs\n"
        "        self.fpregs = fpregs\n"
        "        self.memory = memory\n"
        "        self.pre = pre\n";

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

static void print_memory(FILE* f, const std::unordered_map<uintptr_t, unsigned long long int> & memory){
    fprintf(f, "    {\n");
    for(const auto& p: memory)
        fprintf(f, "0x%lx: 0x%llx, \n", p.first, p.second);
    fprintf(f, "    },");
}

struct processor_state {
    user_regs_struct regs;
    user_fpregs_struct fpregs;
    std::unordered_map<uintptr_t, unsigned long long int> memory;

    inline processor_state() : regs(), fpregs(){
        memset(&regs, 0, sizeof(regs));
        memset(&fpregs, 0, sizeof(fpregs));
    }

    processor_state(const processor_state& other) : regs(other.regs), fpregs(other.fpregs),
        memory( std::unordered_map<uintptr_t, unsigned long long int>(other.memory)) {}

    void print(FILE* f, bool pre) const {
        fprintf(f, "ProcessorState(\n");
        print_registers(f, regs);
        fprintf(f, " {}, ");
        print_memory(f, memory);
        fprintf(f, " %s),\n", pre ? "True" : "False");
    }

    auto operator== (const processor_state& other) const -> bool {
        if (memcmp(&regs, &other.regs, sizeof(regs)) != 0)
            return false;
        if (memcmp(&fpregs, &other.fpregs, sizeof(fpregs)) != 0)
            return false;
        return std::ranges::all_of(memory, [&other](const auto& p){
            const auto& e = other.memory.find(p.first);
            if (e == other.memory.end())
                return true;
            if (e->second != p.second)
                return false;
            return true;
        });
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


static void victim (size_t (*get_fibonacci_xom)(size_t, size_t*)){
    size_t buf[FIB_MAX + 1];
    volatile size_t padding = 0;
    // Terminate when parent terminates
    prctl(PR_SET_PDEATHSIG, SIGHUP);
    for(;;) {
        memset(buf, 0xcd, sizeof(buf));
        get_fibonacci_xom(FIB_MAX, buf);
    }
}

static void prepare_output_dir(const char* output_directory){
    if (!access(output_directory, F_OK))
        return;
    mkdir(output_directory, 0777);
}

static void recover_memory_state_child(const pid_t child_pid, processor_state& state){
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

    for(uintptr_t p = regs.rsp; p <= regs.rbp && p - regs.rsp < 0x100; p+=sizeof(p)){
        state.memory[p] = ptrace(PTRACE_PEEKDATA, child_pid, p, 0);
    }
}

static int retrieve_child_state(const pid_t child_pid, processor_state& state){
    state.memory = std::unordered_map<uintptr_t, unsigned long long int>();
    // Recover registers and memory state
    if (ptrace(PTRACE_GETREGS, child_pid, NULL, &state.regs) < 0){
        printf("Ptrace get user regs failed - errno %d\n", errno);
        return -1;
    }
    if (ptrace(PTRACE_GETFPREGS, child_pid, NULL, &state.fpregs) < 0){
        printf("Ptrace get user fpregs failed - errno %d\n", errno);
        return -1;
    }

    recover_memory_state_child(child_pid, state);

    return 0;
}

static int restore_child_state(const pid_t child_pid, const processor_state& state){
    if (ptrace(PTRACE_SETREGS, child_pid, NULL, &state.regs) < 0){
        printf("Ptrace set regs failed - errno %d\n", errno);
        return -1;
    }
    if (ptrace(PTRACE_SETFPREGS, child_pid, NULL, &state.fpregs) < 0){
        printf("Ptrace set fpregs failed - errno %d\n", errno);
        return -1;
    }
    for (const auto& p: state.memory){
        if(ptrace(PTRACE_POKEDATA, child_pid, p.first, p.second) < 0){
            printf("Ptrace poke data failed - errno %d\n", errno);
            return -1;
        }
    }
    return 0;
}

static int record_execution(FILE* f, const pid_t child_pid, const siginfo_t& siginfo, unsigned long sigset,
                            const processor_state& pre_state_, const processor_state& expected_post,
                            processor_state& post) {
    int status;
    siginfo_t post_siginfo;

    processor_state pre_state;
    restore_child_state(child_pid, pre_state_);
    retrieve_child_state(child_pid, pre_state);

    if (ptrace(PTRACE_SINGLESTEP, child_pid, NULL, NULL) < 0) {
        printf("Ptrace single step failed - errno %d\n", errno);
        return -1;
    }

    do { waitpid(child_pid, &status, 0); } while(!WIFSTOPPED(status));

    retrieve_child_state(child_pid, post);

    if (ptrace(PTRACE_GETSIGINFO, child_pid, NULL, &post_siginfo) < 0){
        printf("Ptrace get siginfo failed - errno %d\n", errno);
        return -1;
    }

    if((post != expected_post && post_siginfo.si_signo == siginfo.si_signo) || expected_post.memory.empty()) {
        pre_state.print(f, true);
        post.print(f, false);
        status = 1;
    } else
        status = 0;

    if (ptrace(PTRACE_SETSIGINFO, child_pid, NULL, &siginfo) < 0){
        printf("Ptrace set siginfo failed - errno %d\n", errno);
        return -1;
    }
    if (ptrace(PTRACE_SETSIGMASK, child_pid, sizeof(sigset), &sigset) < 0){
        printf("Ptrace set sigmask failed - errno %d\n", errno);
        return -1;
    }

    return status;
}

static int fuzz_instruction(FILE* f, pid_t child_pid, processor_state& state, processor_state& expected_post,
                             unsigned long long int& d1, unsigned long long int& d2,
                             const siginfo_t& siginfo, unsigned long sigset){
    int status = 0;
    auto backup = std::make_pair(d1, d2);
    processor_state post;

    // Test a 64-bit integer
    d1 = d2 = 0xabababababababab;
    status += record_execution(f, child_pid, siginfo, sigset, state, expected_post, post);

    // Test a known valid data address
    if(backup.first == state.regs.rsp)
        d1 = d2 = state.regs.rbp;
    else
        d1 = d2 = state.regs.rsp;
    status += record_execution(f, child_pid, siginfo, sigset, state, expected_post, post);

    // Test a known valid code address
    d1 = d2 = state.regs.rip;
    status += record_execution(f, child_pid, siginfo, sigset, state, expected_post, post);

    d1 = backup.first;
    d2 = backup.second;
    restore_child_state(child_pid, state);
    return status;
}

static int fuzz_eflags(FILE* f, pid_t child_pid, processor_state& state, processor_state& expected_post,
                             const siginfo_t& siginfo, unsigned long sigset){
    int status = 0;
    auto& d1 = state.regs.eflags, &d2 = expected_post.regs.eflags;
    auto backup = std::make_pair(d1, d2);
    processor_state post;

    for (auto n : {0, 2, 4, 6, 7, 11}){
        d1 = d2 = backup.first ^ (1 << n);
        status += record_execution(f, child_pid, siginfo, sigset, state, expected_post, post);
    }

    d1 = backup.first;
    d2 = backup.second;
    restore_child_state(child_pid, state);
    return status;
}

static void debug_cycle(const pid_t child_pid, const char* output_directory) {
    int status = 0;
    size_t num_iterations = NUM_ITERATIONS, counter;
    processor_state state, post_normal;
    siginfo_t siginfo;
    unsigned long sigset;
    char outfile[0x400];

    snprintf(outfile, sizeof(outfile), "%s/trace.py", output_directory);

    auto f = fopen(outfile, "w");
    if(!f)
        return;

    fprintf(f, "%s\n\nvictim_register_trace = [\n", processor_state_def);

    while(num_iterations) {
        counter = 1;
        do {
            waitpid(child_pid, &status, 0);
        } while(!WIFSTOPPED(status));

        retrieve_child_state(child_pid, state);

        // Only fuzz instructions in XOM
        if(state.regs.rip >= 0x430000000000)
            goto next_instruction;

        num_iterations--;
        if (instructions_covered.contains(state.regs.rip))
            goto next_instruction;

        // Backup signal info so we can restore it when we hit a segfault
        if (ptrace(PTRACE_GETSIGINFO, child_pid, NULL, &siginfo) < 0){
            printf("Ptrace get siginfo failed - errno %d\n", errno);
            break;
        }
        if (ptrace(PTRACE_GETSIGMASK, child_pid, sizeof(sigset), &sigset) < 0){
            printf("Ptrace get sigmask failed - errno %d\n", errno);
            break;
        }

        // Test normal execution as it occurs in the program
        record_execution(f, child_pid, siginfo, sigset, state, processor_state(), post_normal);
        restore_child_state(child_pid, state);

        for (const auto& d: {
            std::make_pair(&state.regs.r15, &post_normal.regs.r15),
            std::make_pair(&state.regs.r14, &post_normal.regs.r14),
            std::make_pair(&state.regs.r13, &post_normal.regs.r13),
            std::make_pair(&state.regs.r12, &post_normal.regs.r12),
            std::make_pair(&state.regs.r11, &post_normal.regs.r11),
            std::make_pair(&state.regs.r10, &post_normal.regs.r10),
            std::make_pair(&state.regs.r9, &post_normal.regs.r9),
            std::make_pair(&state.regs.r8, &post_normal.regs.r8),
            std::make_pair(&state.regs.rax, &post_normal.regs.rax),
            std::make_pair(&state.regs.rcx, &post_normal.regs.rcx),
            std::make_pair(&state.regs.rdx, &post_normal.regs.rdx),
            std::make_pair(&state.regs.rsi, &post_normal.regs.rsi),
            std::make_pair(&state.regs.rdi, &post_normal.regs.rdi),
            std::make_pair(&state.regs.rsp, &post_normal.regs.rsp),
            std::make_pair(&state.regs.rbx, &post_normal.regs.rbx),
            std::make_pair(&state.regs.rbp, &post_normal.regs.rbp),
        }) {
            counter += fuzz_instruction(f, child_pid, state, post_normal, *d.first, *d.second, siginfo, sigset);
        }

        for(auto& p: state.memory) {
            // Don't change code
            if(p.first >= 0x420000000000 && p.first < 0x430000000000)
                continue;
            auto e = post_normal.memory.find(p.first);
            if(e == post_normal.memory.end())
                continue;
            counter += fuzz_instruction(f, child_pid, state, post_normal, p.second, e->second, siginfo, sigset);
        }

        counter += fuzz_eflags(f, child_pid, state, post_normal, siginfo, sigset);

        instructions_covered.emplace(state.regs.rip);
        printf("Instr. @ 0x%llx: Recorded %lu Executions\n", state.regs.rip, counter);

    next_instruction:
        if (ptrace(PTRACE_SINGLESTEP, child_pid, NULL, NULL) < 0) {
            printf("Ptrace single step failed - errno %d\n", errno);
            break;
        }
    }

    fprintf(f, "]\n");

    fclose(f);
}

int main(int argc, char* argv[]){
    size_t (*get_fibonacci_xom)(size_t, size_t*);
    pid_t child_pid;
    struct xombuf* xbuf = xom_alloc(PAGE_SIZE);
    const char* output_directory = ".";

    // Give user option to specify output directory
    if(argc > 1){
        output_directory = argv[1];
        prepare_output_dir(output_directory);
    }

    // Get mapped memory regions
    get_maps();

    // Put victim code into XOM
    if(!xbuf){
        puts("Could allocate XOM buffer!");
    }
    xom_write(xbuf, reinterpret_cast<const void *>(get_fibonacci), PAGE_SIZE, 0);

    get_fibonacci_xom = reinterpret_cast<size_t (*)(size_t, size_t*)>(xom_lock(xbuf));
    if(!get_fibonacci_xom){
        puts("Could not lock XOM buffer!");
        return 1;
    }

    // Fork into attacker / victim
    child_pid = fork();
    if(!child_pid)
        victim(get_fibonacci_xom);

    usleep(500);

    // Ptrace the victim process
    if (ptrace(PTRACE_ATTACH, child_pid, NULL, NULL) < 0) {
        printf("Ptrace attach failed - errno %d\n", errno);
        return 1;
    }

    puts("Attached to victim. Recording trace...");

    // Single-step through program, save registers and parts of the memory state after every instruction
    debug_cycle(child_pid, output_directory);

    printf("Done! Saved trace to '%s/trace.py'\n", output_directory);

    ptrace(PTRACE_DETACH, child_pid, NULL, NULL);

    return 0;
}
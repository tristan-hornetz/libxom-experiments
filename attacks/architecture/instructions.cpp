#include <array>
#include <vector>
#include <string>
#include <cstring>
#include <unordered_map>
#include <pthread.h>
#include <csignal>
#include <setjmp.h>
#include <sys/user.h>
#include "instructions.h"
#include "instruction_encodings.h"

#include <mutex>

std::vector<instruction> legal_instrs;
std::unordered_map<uintptr_t, std::vector<InstructionInstance>> reconstruction_state;

std::mutex vec_mutex;

const processor_state* _pre = NULL;
const processor_state* _post = NULL;

static std::vector<std::pair<uintptr_t, uintptr_t>> maps;

static int get_maps(){
    const static char mpath[] = "/proc/self/maps";
    char perms[3] = {0,};
    char *line = NULL;
    int status;
    uintptr_t start, end, len = 0;
    FILE *mapsf;


    mapsf = fopen(mpath, "r");
    if (!mapsf)
        return -1;

    // Get amount of executable memory regions
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

constexpr const char* get_sample_string(parameter_type type){
    switch (type) {
        case parameter_type::GP_REGISTER_QWORD:
            return "%rax";
        case parameter_type::GP_REGISTER_DWORD:
            return "%eax";
        case parameter_type::GP_REGISTER_WORD:
            return "%ax";
        case parameter_type::GP_REGISTER_HWORD:
            return "%al";
        case parameter_type::SSE_REGISTER:
            return "%xmm0";
        case parameter_type::AVX_REGISTER:
            return "%ymm0";
        case parameter_type::AVX512_REGISTER:
            return "%zmm0";
        case parameter_type::AVX512_BITMASK:
            return "%k0";
        case parameter_type::IMMEDIATE8:
            return "0xff";
        case parameter_type::IMMEDIATE16:
            return "0xffff";
        case parameter_type::IMMEDIATE32:
            return "0xffffffff";
        case parameter_type::IMMEDIATE64:
            return "0xffffffffffffffff";
        case parameter_type::INTEGER:
            return "2";
        default:;
    }
    return "";
}


static void print_instruction_stringify(const instruction& instr, char dest[128]){
    char format[128];

    if(!instr.num_parameters){
        strcpy(dest, instr.mnemonic);
        return;
    }

    snprintf(format, sizeof(format), "%s %s", instr.mnemonic, instr.encoding);
    std::vector<const char*> params;
    for(const auto& t: instr.parameter_types)
        params.emplace_back(get_sample_string(t));

    snprintf(dest, 128, format, params[0], params[1], params[2], params[3]);
}

static int assemble(const InstructionInstance& i, ks_engine* ks, ks_err& err, unsigned char**encode, size_t* size, const uintptr_t rip) {
    const static char* empty = "";
    char instruction_asm[128];
    char format[128];
    size_t count;
    const auto& instr = i.instr;
    const auto& parameters= i.parameters;

    snprintf(format, sizeof(format), "%s %s", instr.mnemonic, instr.encoding);

    snprintf(instruction_asm, sizeof(instruction_asm), format,
             instr.num_parameters > 0 ? parameters[0]->c_str() : empty,
             instr.num_parameters > 1 ? parameters[1]->c_str() : empty,
             instr.num_parameters > 2 ? parameters[2]->c_str() : empty,
             instr.num_parameters > 3 ? parameters[3]->c_str() : empty
    );

    auto res = ks_asm(ks, instruction_asm, rip, encode, size, &count);
    if(res < 0) {
        if(*encode)
            ks_free(*encode);
        err = ks_errno(ks);
        *encode = nullptr;
        *size = 0;
        return -1;
    }

    return 0;
}



static bool test_illegal(uc_engine * uc, uc_context* context_backup, ks_engine* ks,
                        const user_regs_struct& user_regs_pre, const instruction& instr){
    char asm_instr[128];
    size_t count, size;
    uc_err uc_result;
    unsigned char *encode;
    print_instruction_stringify(instr, asm_instr);
    bool rc = true;

    if(ks_asm(ks, asm_instr, user_regs_pre.rip, &encode, &size, &count) != KS_ERR_OK)
        return false;

    if(uc_mem_write(uc, user_regs_pre.rip, encode, size) != UC_ERR_OK) {
        rc = false;
        goto exit;
    }

    uc_result = uc_emu_start(uc, user_regs_pre.rip, user_regs_pre.rip + 0x10, 0, 1);

    switch (uc_result) {
        case UC_ERR_INSN_INVALID:
        case UC_ERR_EXCEPTION:
            rc = false;
        default:;
    }

exit:
    uc_context_restore(uc, context_backup);
    ks_free(encode);
    return rc;
}

static void recover_memory_state_emu(uc_engine *uc, processor_state& state){
    uintptr_t dest;
    uc_err err;
    const auto& regs = state.regs;
    const std::array<uintptr_t, 16> reg_values = {regs.r15, regs.r14, regs.r13, regs.r12, regs.r11, regs.r10, regs.r9,
                                           regs.r8, regs.rax, regs.rbx, regs.rcx, regs.rdx, regs.rdi, regs.rsi,
                                           regs.rbp, regs.rsp};
    for (auto v: reg_values){
        if(uc_mem_read(uc, v, &dest, 2) == UC_ERR_OK){
            state.memory[v] = 0;
            for(unsigned i = 0; i < 4; i++) {
                err = uc_mem_read(uc, v, &dest, sizeof(unsigned short));
                if (err != UC_ERR_OK)
                    break;
                state.memory[v] |= (dest & 0xf) << (16*i);
            }
        }
    }
}

static void recover_register_state(uc_engine *uc, user_regs_struct* regs, user_fpregs_struct* fpregs) {
    // Base x64 regs
    uc_reg_read(uc, UC_X86_REG_RIP, &regs->rip);
    uc_reg_read(uc, UC_X86_REG_R15, &regs->r15);
    uc_reg_read(uc, UC_X86_REG_R14, &regs->r14);
    uc_reg_read(uc, UC_X86_REG_R13, &regs->r13);
    uc_reg_read(uc, UC_X86_REG_R12, &regs->r12);
    uc_reg_read(uc, UC_X86_REG_R11, &regs->r11);
    uc_reg_read(uc, UC_X86_REG_R10, &regs->r10);
    uc_reg_read(uc, UC_X86_REG_R9, &regs->r9);
    uc_reg_read(uc, UC_X86_REG_R8, &regs->r8);
    uc_reg_read(uc, UC_X86_REG_RAX, &regs->rax);
    uc_reg_read(uc, UC_X86_REG_RBX, &regs->rbx);
    uc_reg_read(uc, UC_X86_REG_RCX, &regs->rcx);
    uc_reg_read(uc, UC_X86_REG_RDX, &regs->rdx);
    uc_reg_read(uc, UC_X86_REG_RDI, &regs->rdi);
    uc_reg_read(uc, UC_X86_REG_RSI, &regs->rsi);
    uc_reg_read(uc, UC_X86_REG_EFLAGS, &regs->eflags);
    uc_reg_read(uc, UC_X86_REG_RSP, &regs->rsp);
    uc_reg_read(uc, UC_X86_REG_RBP, &regs->rbp);
    uc_reg_read(uc, UC_X86_REG_SS, &regs->ss);
    uc_reg_read(uc, UC_X86_REG_DS, &regs->ds);
    uc_reg_read(uc, UC_X86_REG_ES, &regs->es);
    uc_reg_read(uc, UC_X86_REG_FS, &regs->fs);
    uc_reg_read(uc, UC_X86_REG_GS, &regs->gs);
    uc_reg_read(uc, UC_X86_REG_CS, &regs->cs);
    uc_reg_read(uc, UC_X86_REG_FS_BASE, &regs->fs_base);
    uc_reg_read(uc, UC_X86_REG_GS_BASE, &regs->cs);

    // SSE regs
    for(unsigned i = UC_X86_REG_XMM0; i <= UC_X86_REG_XMM15; i++)
        uc_reg_read(uc, static_cast<int>(i), &fpregs->xmm_space[4*(i-UC_X86_REG_XMM0)]);

    // ST regs
    for(unsigned i = UC_X86_REG_ST0; i <= UC_X86_REG_ST7; i++)
        uc_reg_read(uc, static_cast<int>(i), &fpregs->st_space[4*(i-UC_X86_REG_ST0)]);
}

static const bool regs_eq(const processor_state& a, const processor_state& b){
    if (a.regs.rip != b.regs.rip) return false;
    /*if (a.regs.eflags != b.regs.eflags) return false;
    if (a.regs.r15 != b.regs.r15) return false;
    if (a.regs.r14 != b.regs.r14) return false;
    if (a.regs.r13 != b.regs.r13) return false;
    if (a.regs.r12 != b.regs.r12) return false;
    if (a.regs.r11 != b.regs.r11) return false;
    if (a.regs.r10 != b.regs.r10) return false;
    if (a.regs.r9 != b.regs.r9) return false;
    if (a.regs.r8 != b.regs.r8) return false;
    if (a.regs.rax != b.regs.rax) return false;
    if (a.regs.rbx != b.regs.rbx) return false;
    if (a.regs.rcx != b.regs.rcx) return false;
    if (a.regs.rdx != b.regs.rdx) return false;
    if (a.regs.rdi != b.regs.rdi) return false;
    if (a.regs.rsi != b.regs.rsi) return false;
    if (a.regs.rbp != b.regs.rbp) return false;
    if (a.regs.rsp != b.regs.rsp) return false;*/
    // Don't check segment registers for now

    return true;
}

size_t crip = 0;
uc_hook uh_trap;

std::mutex rwmutex;

static void unblock_signal(int signum) {
    sigset_t sigs;
    sigemptyset(&sigs);
    sigaddset(&sigs, signum);
    sigprocmask(SIG_UNBLOCK, &sigs, NULL);
}

static jmp_buf longjmp_buf;

static void segfault_handler(int signum) {
    unblock_signal(signum);
    ddetach();
    printf("SEGFAULT! %d\n", getpid());
    longjmp(longjmp_buf, 1);
}

static void uc_fixup_registers(uc_engine* uc, const user_regs_struct& regs, const user_fpregs_struct& fpregs) {
    // Base x64 regs
    uc_reg_write(uc, UC_X86_REG_RIP, &regs.rip);
    uc_reg_write(uc, UC_X86_REG_R15, &regs.r15);
    uc_reg_write(uc, UC_X86_REG_R14, &regs.r14);
    uc_reg_write(uc, UC_X86_REG_R13, &regs.r13);
    uc_reg_write(uc, UC_X86_REG_R12, &regs.r12);
    uc_reg_write(uc, UC_X86_REG_R11, &regs.r11);
    uc_reg_write(uc, UC_X86_REG_R10, &regs.r10);
    uc_reg_write(uc, UC_X86_REG_R9, &regs.r9);
    uc_reg_write(uc, UC_X86_REG_R8, &regs.r8);
    uc_reg_write(uc, UC_X86_REG_RAX, &regs.rax);
    uc_reg_write(uc, UC_X86_REG_RBX, &regs.rbx);
    uc_reg_write(uc, UC_X86_REG_RCX, &regs.rcx);
    uc_reg_write(uc, UC_X86_REG_RDX, &regs.rdx);
    uc_reg_write(uc, UC_X86_REG_RDI, &regs.rdi);
    uc_reg_write(uc, UC_X86_REG_RSI, &regs.rsi);
    uc_reg_write(uc, UC_X86_REG_EFLAGS, &regs.eflags);
    uc_reg_write(uc, UC_X86_REG_RSP, &regs.rsp);
    uc_reg_write(uc, UC_X86_REG_RBP, &regs.rbp);
    uc_reg_write(uc, UC_X86_REG_SS, &regs.ss);
    uc_reg_write(uc, UC_X86_REG_DS, &regs.ds);
    uc_reg_write(uc, UC_X86_REG_ES, &regs.es);
    uc_reg_write(uc, UC_X86_REG_FS, &regs.fs);
    uc_reg_write(uc, UC_X86_REG_GS, &regs.gs);
    uc_reg_write(uc, UC_X86_REG_CS, &regs.cs);
    uc_reg_write(uc, UC_X86_REG_FS_BASE, &regs.fs_base);
    uc_reg_write(uc, UC_X86_REG_GS_BASE, &regs.cs);

    // SSE regs
    for(unsigned i = UC_X86_REG_XMM0; i <= UC_X86_REG_XMM15; i++)
        uc_reg_write(uc, static_cast<int>(i), &fpregs.xmm_space[4*(i-UC_X86_REG_XMM0)]);

    // ST regs
    for(unsigned i = UC_X86_REG_ST0; i <= UC_X86_REG_ST7; i++)
        uc_reg_write(uc, static_cast<int>(i), &fpregs.st_space[4*(i-UC_X86_REG_ST0)]);

}

static void uc_fixup_memory(uc_engine* uc, const processor_state& state) {
    for(const auto& p: state.memory)
        uc_mem_write(uc, p.first, &p.second, sizeof(p.second));
}

static void copy_state_to_emulator(uc_engine* uc, const processor_state& state) {
    uc_fixup_memory(uc, state);
    uc_fixup_registers(uc, state.regs, state.fpregs);
}

static unsigned int ninces = 0;
static int inc_counter = 0;

static bool test_instance_emu(uc_engine* uc, uc_err& err, ks_engine* ks, ks_err& kerr, const processor_state& pre,
                          const processor_state& post, const InstructionInstance& instance) {
    bool rc = false;

    const static unsigned char nop[] = {0x90,0x90,0x90, 0x90, 0x90 };
    processor_state emulated;
    unsigned char* encode;
    size_t size;
    uc_hook uh_trap2;



    inc_counter++;

    // Assemble instruction
    assemble(instance, ks, kerr, &encode, &size, pre.regs.rip);
    if(!encode) {
        return false;
    }

    uc_reg_write(uc, UC_X86_REG_RIP, &pre.regs.rip);
    //uc_context_save(uc, context_backup);

    // Initialize emulated state
    memcpy(&emulated.regs, &pre.regs, sizeof(pre.regs));
    memcpy(&emulated.fpregs, &pre.fpregs, sizeof(pre.fpregs));
    emulated.memory = std::unordered_map<uintptr_t, uintptr_t>(pre.memory.cbegin(), pre.memory.cend());

    copy_state_to_emulator(uc, pre);

    // Write instruction instance to emulator memory
    if(uc_mem_write(uc, pre.regs.rip, encode, size) != UC_ERR_OK)
        goto exit;
    if(uc_mem_write(uc, pre.regs.rip + size, nop, sizeof(nop)) != UC_ERR_OK)
        goto exit;



    /*if((pre.regs.rip & 0xff) == 0x10){
        if(strcmp(instance.instr.mnemonic,"DEC") == 0 && strcmp(instance.parameters[0]->c_str(),"%rdi") == 0) {
            uintptr_t rrip;
            printf("HIT\n");
            printf("%02x %02x %02x\n", encode[0], encode[1], encode[2]);
            uc_reg_write(uc, UC_X86_REG_RIP, &pre.regs.rip);

            //uc_hook_add(uc, &uh_trap2, UC_HOOK_CODE, reinterpret_cast<void *>(emu_hook), NULL, 0, ~0ul);
            //uc_hook_add(uc, &uh_trap, UC_HOOK_INTR, reinterpret_cast<void *>(hook_intr), NULL, 0, ~0ul);
            err = uc_emu_start(uc, pre.regs.rip, ~0ul, 0, 0);
            printf("%d\n", err);
            recover_register_state(uc, &emulated.regs, &emulated.fpregs);
            recover_memory_state_emu(uc, emulated);
            uc_reg_read(uc, UC_X86_REG_RIP, &rrip);
            if(regs_eq(emulated, post))
                printf("regs good!\n");
            else
                printf("%llx, %llx, %llx, %llx\n", pre.regs.rip, post.regs.rip, emulated.regs.rip, rrip);

            exit(0);
        }
    }*/

    

    // Start emulation
    err = uc_emu_start(uc, pre.regs.rip, ~0ul, 0, 0);
    /*size = 0;
    uc_mem_regions(uc, &regions, reinterpret_cast<uint32_t *>(&size));
    printf("rip: %llx\n", pre.regs.rip);
    printf("rsp: %llx\n", pre.regs.rsp);
    for(unsigned  i = 0; i < size; i++)
        printf("%lx-%lx-%x\n", regions[i].begin, regions[i].end, regions[i].perms);

    exit(0);
    printf("%d\n", err);
    */

    // Something's up if we fail to execute the instruction


    // Get the state post-execution from the emulator
    recover_register_state(uc, &emulated.regs, &emulated.fpregs);
    recover_memory_state_emu(uc, emulated);

    /*if(uc_mem_write(uc, pre.regs.rip, nop, sizeof(nop)) != UC_ERR_OK)
        goto exit;
    uc_reg_write(uc, UC_X86_REG_RIP, &pre.regs.rip);
    err = uc_emu_start(uc, pre.regs.rip, ~0ul, 0, 0);
    if(err == 6) {
        printf("NOP failed after %s %s - %d, %d\n", instance.instr.mnemonic, instance.instr.encoding, inc_counter, err);
        exit(1);
    }*/
    //printf("\r%s %s: %d / %u                      ", instance.instr.mnemonic, instance.instr.encoding, inc_counter, ninces);

    if(err != UC_ERR_OK) {
        goto exit;
    }

    // Compare to what actually happened on hardware
    if(!regs_eq(emulated, post))
        goto exit;

    /*if(memcmp(&post.regs, &emulated.regs, sizeof(emulated.regs)) != 0)
        goto exit;*/

    /*if(memcmp(&post.fpregs, &emulated.fpregs, sizeof(emulated.fpregs)) != 0)
        goto exit;



    for (const auto &p: post.memory){
        if(emulated.memory.find(p.first) == emulated.memory.end())
            goto exit;
        if(emulated.memory[p.first] != p.second)
            goto exit;
    }*/

    // If we pass all these tests, the instruction instance could have been executed
    rc = true;
exit:
    if(encode)
        ks_free(encode);
    return rc;
}


static constexpr std::array<const char*, 17> qword_regs = {
    "%r15",
    "%r14",
    "%r13",
    "%r12",
    "%r11",
    "%r10",
    "%r9",
    "%r8",
    "%rax",
    "%rbx",
    "%rcx",
    "%rdx",
    "%rsi",
    "%rdi",
    "%rsi",
    "%rsp",
    "%rbp",
};

static constexpr std::array<const char*, 17> dword_regs = {
    "%r15d",
    "%r14d",
    "%r13d",
    "%r12d",
    "%r11d",
    "%r10d",
    "%r9d",
    "%r8d",
    "%eax",
    "%ebx",
    "%ecx",
    "%edx",
    "%esi",
    "%edi",
    "%esi",
    "%esp",
    "%ebp",
};

static constexpr std::array<const char*, 17> word_regs = {
    "%r15w",
    "%r14w",
    "%r13w",
    "%r12w",
    "%r11w",
    "%r10w",
    "%r9w",
    "%r8w",
    "%ax",
    "%bx",
    "%cx",
    "%dx",
    "%si",
    "%di",
    "%si",
    "%sp",
    "%bp",
};

static constexpr std::array<const char*, 17> hword_regs ={
    "%r15b",
    "%r14b",
    "%r13b",
    "%r12b",
    "%r11b",
    "%r10b",
    "%r9b",
    "%r8b",
    "%al",
    "%bl",
    "%cl",
    "%dl",
    //"%ah",
    //"%bh",
    //"%ch",
    //"%dh",
    "%sil",
    "%dil",
    "%sil",
    "%spl",
    "%bpl",
};


template <typename T>
static std::vector<std::shared_ptr<std::string>> get_immediate(const processor_state& pre, const processor_state& post) {
    auto ret = std::vector<std::shared_ptr<std::string>>();
    auto vals = std::vector<T>();
    const std::array<std::pair<T, T>, 17> reg_values = {
        std::make_pair(static_cast<T>(pre.regs.r15), static_cast<T>(post.regs.r15)),
        std::make_pair(static_cast<T>(pre.regs.r14), static_cast<T>(post.regs.r14)),
        std::make_pair(static_cast<T>(pre.regs.r13), static_cast<T>(post.regs.r13)),
        std::make_pair(static_cast<T>(pre.regs.r12), static_cast<T>(post.regs.r12)),
        std::make_pair(static_cast<T>(pre.regs.r11), static_cast<T>(post.regs.r11)),
        std::make_pair(static_cast<T>(pre.regs.r10), static_cast<T>(post.regs.r10)),
        std::make_pair(static_cast<T>(pre.regs.r9), static_cast<T>(post.regs.r9)),
        std::make_pair(static_cast<T>(pre.regs.r8), static_cast<T>(post.regs.r8)),
        std::make_pair(static_cast<T>(pre.regs.rax), static_cast<T>(post.regs.rax)),
        std::make_pair(static_cast<T>(pre.regs.rbx), static_cast<T>(post.regs.rbx)),
        std::make_pair(static_cast<T>(pre.regs.rcx), static_cast<T>(post.regs.rcx)),
        std::make_pair(static_cast<T>(pre.regs.rdx), static_cast<T>(post.regs.rdx)),
        std::make_pair(static_cast<T>(pre.regs.rdi), static_cast<T>(post.regs.rdi)),
        std::make_pair(static_cast<T>(pre.regs.rsi), static_cast<T>(post.regs.rsi)),
        std::make_pair(static_cast<T>(pre.regs.rbp), static_cast<T>(post.regs.rbp)),
        std::make_pair(static_cast<T>(pre.regs.rsp), static_cast<T>(post.regs.rsp)),
        std::make_pair(static_cast<T>(pre.regs.rip), static_cast<T>(post.regs.rip))
    };

    for(const auto& p : reg_values){
        if(p.first == p.second) continue;
        // Arithmetics
        vals.push_back(p.first - p.second);
        vals.push_back(p.second - p.first);
        vals.push_back(p.first ^ p.second);
        vals.push_back(p.second);
        for(unsigned i = 0; i < 8*sizeof(p.first); i++) {
            if(p.second == p.first << i)
                vals.push_back(i);
            if(p.second == p.first >> i)
                vals.push_back(i);
        }

        // Load
        for(const auto& pm : pre.memory){
            if(p.second == pm.second)
                vals.push_back(static_cast<T>(pm.first));
        }
    }

    // Store
    for(const auto& pm : pre.memory){
        if(post.memory.find(pm.first) == post.memory.end())
            continue;
        if(post.memory.at(pm.first) == pm.second)
            continue;
        vals.push_back(static_cast<T>(post.memory.at(pm.first)));
    }

    for(const auto v : vals){
        char d[40];
        snprintf(d, sizeof(d), "0x%lx", static_cast<unsigned long>(v));
        ret.push_back(std::make_shared<std::string>(std::string(d)));
    }

    return ret;
}


static constexpr bool is_guaranteed_branch(const processor_state& pre, const processor_state& post){
    if (post.regs.rip < pre.regs.rip)
        return true;
    if (post.regs.rip > pre.regs.rip + 11)
        return true;

    return false;
}

static constexpr bool is_instr_branch(const instruction& instr){
    if(instr.mnemonic[0] == 'J')
        return true;
    if(strlen(instr.mnemonic) < 3)
        return false;
    if(strcmp(instr.mnemonic, "RET") == 0)
        return true;
    if(strcmp(instr.mnemonic, "CALL") == 0)
        return true;
    return false;
}


static constexpr std::vector<const char*> get_register_names(const parameter_type t){
    switch (t) {
        case parameter_type::GP_REGISTER_QWORD:
            return std::vector<const char*>(qword_regs.cbegin(), qword_regs.cend());
        case parameter_type::GP_REGISTER_DWORD:
            return std::vector<const char*>(dword_regs.cbegin(), dword_regs.cend());
        case parameter_type::GP_REGISTER_WORD:
            return std::vector<const char*>(word_regs.cbegin(), word_regs.cend());
        case parameter_type::GP_REGISTER_HWORD:
            return std::vector<const char*>(hword_regs.cbegin(), hword_regs.cend());
        default:;
    }
    return {};
}


static std::vector<std::shared_ptr<std::string>> get_plausible_parameters(const processor_state& pre,
                                                             const processor_state& post, const parameter_type t) {
    std::vector<std::shared_ptr<std::string>> ret;

    switch (t) {
        case parameter_type::GP_REGISTER_QWORD:
        case parameter_type::GP_REGISTER_DWORD:
        case parameter_type::GP_REGISTER_WORD:
        case parameter_type::GP_REGISTER_HWORD:
            for(const auto n: get_register_names(t))
                ret.push_back(std::make_shared<std::string>(std::string(n)));
            break;
        case parameter_type::IMMEDIATE8:
            return get_immediate<uint8_t>(pre, post);
        case parameter_type::IMMEDIATE16:
            return get_immediate<uint16_t>(pre, post);
        case parameter_type::IMMEDIATE32:
            return get_immediate<uint32_t>(pre, post);
        case parameter_type::IMMEDIATE64:
            return get_immediate<uint8_t>(pre, post);
        default:;
    }

    return ret;
}

static std::vector<InstructionInstance> instantiate(const processor_state& pre,
                                                const processor_state& post, const instruction& instr){
    if(!instr.num_parameters || instr.num_parameters > 4)
        return std::vector<InstructionInstance>({InstructionInstance(instr, {})});

    std::array<std::vector<std::shared_ptr<std::string>>, 4> plausible_parameters = {};
    std::vector<InstructionInstance> ret;

    for(unsigned i = 0; i < instr.num_parameters; i++)
        plausible_parameters[i] = get_plausible_parameters(pre, post, instr.parameter_types[i]);

    // Get all permutations of possible parameters
    // I hate this
    for (const auto& p1: plausible_parameters[0]){
        if(instr.num_parameters == 1) {
            ret.push_back(InstructionInstance(instr, {p1,}));
            continue;
        }
        for (const auto& p2: plausible_parameters[1]){
            if(instr.num_parameters == 2) {
                ret.push_back(InstructionInstance(instr, {p1, p2,}));
                continue;
            }
            for (const auto& p3: plausible_parameters[2]){
                if(instr.num_parameters == 3) {
                    ret.push_back(InstructionInstance(instr, {p1, p2, p3}));
                    continue;
                }
                for (const auto& p4: plausible_parameters[3])
                    ret.push_back(InstructionInstance(instr, {p1, p2, p3, p4}));
            }
        }
    }
    return ret;
}

static bool test_instruction(uc_engine* uc, uc_err& err, ks_engine* ks, ks_err& kerr,
                        const processor_state& pre, const processor_state& post, const InstructionInstance& instr){
    // If the instruction does not actively change rip, filter based on instruction length
    if(is_guaranteed_branch(pre, post)){
        if(!is_instr_branch(instr.instr))
            return false;
    }

    return test_instance_emu(uc, err, ks, kerr, pre, post, instr);
}

std::vector<InstructionInstance> instances;
std::vector<InstructionInstance> plausible_instances;


void* test_instruction_thread(void*){
    const auto& pre = *_pre;
    const auto& post = *_post;

    uc_engine* uc = NULL;
    uc_hook ltrap;
    uc_err err = UC_ERR_OK;
    ks_err kerr = KS_ERR_OK;

    ks_engine* ks;
    kerr = ks_open(KS_ARCH_X86, KS_MODE_64, &ks);
    if(kerr != KS_ERR_OK){
        printf("ks_open\n");
        return NULL;
    }
    kerr = ks_option(ks, KS_OPT_SYNTAX, KS_OPT_SYNTAX_ATT);
    if(kerr != KS_ERR_OK){
        printf("ks_option\n");
        return NULL;
    }

    while(true) {
        vec_mutex.lock();
        if (instances.empty()) {
            vec_mutex.unlock();
            return NULL;
        }
        auto instr = std::move(instances[instances.size() - 1]);
        instances.pop_back();
        vec_mutex.unlock();

        if(!uc){
            uc_open(UC_ARCH_X86, UC_MODE_64, &uc);
            for(const auto& m: maps)
                uc_mem_map(uc, m.first, m.second - m.first, UC_PROT_ALL);
            uc_hook_add(uc, &ltrap, UC_HOOK_CODE, reinterpret_cast<void *>(emu_hook), NULL, 0, ~0ul);
        }

        auto plausible = test_instruction(uc, err, ks, kerr, pre, post, instr);

        /*if(kerr == KS_ERR_ASM_FIXUP_INVALID)  {
            ks_close(ks);
            ks = NULL;
            printf("REBUILDING\n");
            kerr = ks_open(KS_ARCH_X86, KS_MODE_64, &ks);
            if(kerr != KS_ERR_OK){
                printf("ks_open\n");
                return NULL;
            }
            kerr = ks_option(ks, KS_OPT_SYNTAX, KS_OPT_SYNTAX_ATT);
            if(kerr != KS_ERR_OK){
                printf("ks_option\n");
                return NULL;
            }
        }*/

        if(err != UC_ERR_OK){
            uc_close(uc);
            uc = NULL;
            err = UC_ERR_OK;
        }

        if(plausible){
            vec_mutex.lock();
            plausible_instances.push_back(instr);
            vec_mutex.unlock();
        }
    }

}

std::unordered_map<uintptr_t, uintptr_t> cm;
uint co = 0;

int process_instruction(uc_engine * uc, uc_context* context_backup, ks_engine* ks,
                        const processor_state& pre, const processor_state& post) noexcept {
    const auto current_instr = pre.regs.rip;

    uc_err err;

    if(maps.empty())
        get_maps();

    if(legal_instrs.empty()){
        for(const auto& i: instruction_encodings){
            if(test_illegal(uc, context_backup, ks, pre.regs, i))
                legal_instrs.emplace_back(i);
        }
    }

    _pre = &pre;
    _post = &post;

    crip = pre.regs.rip;

    if(reconstruction_state.find(current_instr) == reconstruction_state.end()){
        reconstruction_state[current_instr] = std::vector<InstructionInstance>();
        for(const auto& templte: legal_instrs){
            const auto instantiated = instantiate(pre, post, templte);
             ninces = instantiated.size();
             inc_counter = 0;
            for(const auto& instance: instantiated){

                /*if(test_instruction(uc, err, ks, pre, post, instance))
                    plausible_instances.push_back(instance);*/
                instances.push_back(instance);
            }
        }

    } else {
        for(const auto& instance: reconstruction_state[current_instr]){
            /*if(test_instruction(uc, err, ks, pre, post, instance))
                    plausible_instances.push_back(instance);*/
            instances.push_back(instance);
        }
    }

    ninces = instances .size();
    inc_counter = 0;

    test_instruction_thread(ks);

    reconstruction_state[current_instr] = std::vector<InstructionInstance>(plausible_instances);
    plausible_instances.clear();

    printf("Got %zu plausible instructions\n", reconstruction_state[current_instr].size());

    return 0;
}



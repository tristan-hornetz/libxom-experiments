#ifndef ATTACKS_INSTRUCTIONS_H
#define ATTACKS_INSTRUCTIONS_H
#ifdef __cplusplus

#include <stdint.h>
#include <unordered_map>
#include <vector>
#include <array>
#include <memory>
#include <sys/user.h>
#include <keystone/keystone.h>
#include <unicorn/unicorn.h>

enum class parameter_type {
    GP_REGISTER_QWORD,
    GP_REGISTER_DWORD,
    GP_REGISTER_WORD,
    GP_REGISTER_HWORD,
    SSE_REGISTER,
    AVX_REGISTER,
    AVX512_REGISTER,
    AVX512_BITMASK,
    IMMEDIATE8,
    IMMEDIATE16,
    IMMEDIATE32,
    IMMEDIATE64,
    INTEGER,
};

struct instruction{
    const char* mnemonic;
    const char* encoding;
    unsigned char num_parameters;
    std::array<parameter_type, 4> parameter_types;
    unsigned int instruction_length;

    constexpr inline instruction(const char* mn, const char* en, unsigned char np, std::array<parameter_type, 4> pt, unsigned int il) :
        mnemonic(mn), encoding(en), num_parameters(np), parameter_types(pt), instruction_length(il) {}

    inline bool operator==(const instruction& other) const {
        if(strcmp(mnemonic, other.mnemonic) != 0)
            return false;
        if(strcmp(encoding, other.encoding) != 0)
            return false;

        return parameter_types == other.parameter_types;
    }
};

struct processor_state {
    user_regs_struct regs;
    user_fpregs_struct fpregs;
    std::unordered_map<uintptr_t, uintptr_t> memory;
};

struct InstructionInstance {
    std::array<std::shared_ptr<const std::string>, 4> parameters;
    const instruction instr;

    InstructionInstance(const instruction& i, const std::array<std::shared_ptr<const std::string>, 4> & p) : instr(i),
                                                                                                             parameters(p) {}
};

extern size_t crip;
extern uc_hook uh_trap;
extern void ddetach();
extern "C" void emu_hook(uc_engine *uc, uint32_t intno, void *user_data);
extern std::unordered_map<uintptr_t, std::vector<InstructionInstance>> reconstruction_state;

int process_instruction(uc_engine * uc, uc_context* context_backup, ks_engine* ks,
                        const processor_state& pre, const processor_state& post) noexcept;


#endif
#endif //ATTACKS_INSTRUCTIONS_H

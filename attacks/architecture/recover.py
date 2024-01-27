from z3 import *


class ProcessorState:
    def __init__(self, regs: dict, fpregs: dict, memory: dict) -> None:
        self.regs = regs
        self.fpregs = fpregs
        self.memory = memory


states = [
    ProcessorState({"rax": 0, "rbx": 0}, {"xmm0": [0, 0]}, {0: 0, 1: 0}),
]


def init_registers(s: Solver, id) -> dict:
    # define registers
    regs = {
        # QWORD
        "r15": BitVec(f"{id}_r15", 64),
        "r14": BitVec(f"{id}_r14", 64),
        "r13": BitVec(f"{id}_r13", 64),
        "r12": BitVec(f"{id}_r12", 64),
        "rbp": BitVec(f"{id}_rbp", 64),
        "rbx": BitVec(f"{id}_rbx", 64),
        "r11": BitVec(f"{id}_r11", 64),
        "r10": BitVec(f"{id}_r10", 64),
        "r9": BitVec(f"{id}_r9", 64),
        "r8": BitVec(f"{id}_r8", 64),
        "rax": BitVec(f"{id}_rax", 64),
        "rcx": BitVec(f"{id}_rcx", 64),
        "rdx": BitVec(f"{id}_rdx", 64),
        "rsi": BitVec(f"{id}_rsi", 64),
        "rdi": BitVec(f"{id}_rdi", 64),
        "rip": BitVec(f"{id}_rip", 64),
        "rsp": BitVec(f"{id}_rsp", 64),
        # FLAGS
        "eflags": BitVec(f"{id}_eflags", 32),
        "cf": BitVec(f"{id}_cf", 1),
        "pf": BitVec(f"{id}_pf", 1),
        "af": BitVec(f"{id}_af", 1),
        "zf": BitVec(f"{id}_zf", 1),
        "sf": BitVec(f"{id}_sf", 1),
        "tf": BitVec(f"{id}_tf", 1),
        "if": BitVec(f"{id}_if", 1),
        "df": BitVec(f"{id}_df", 1),
        "of": BitVec(f"{id}_of", 1),
        "id": BitVec(f"{id}_id", 1),
        # Omit other flags for now

        # DWORD
        "r15d": BitVec(f"{id}_r15d", 32),
        "r14d": BitVec(f"{id}_r14d", 32),
        "r13d": BitVec(f"{id}_r13d", 32),
        "r12d": BitVec(f"{id}_r12d", 32),
        "ebp": BitVec(f"{id}_ebp", 32),
        "ebx": BitVec(f"{id}_ebx", 32),
        "r11d": BitVec(f"{id}_r11d", 32),
        "r10d": BitVec(f"{id}_r10d", 32),
        "r9d": BitVec(f"{id}_r9d", 32),
        "r8d": BitVec(f"{id}_r8d", 32),
        "eax": BitVec(f"{id}_eax", 32),
        "ecx": BitVec(f"{id}_ecx", 32),
        "edx": BitVec(f"{id}_edx", 32),
        "esi": BitVec(f"{id}_esi", 32),
        "edi": BitVec(f"{id}_edi", 32),
        "eip": BitVec(f"{id}_eip", 32),
        "esp": BitVec(f"{id}_esp", 32),

        # WORD
        "r15w": BitVec(f"{id}_r15w", 16),
        "r14w": BitVec(f"{id}_r14w", 16),
        "r13w": BitVec(f"{id}_r13w", 16),
        "r12w": BitVec(f"{id}_r12w", 16),
        "bp": BitVec(f"{id}_bp", 16),
        "bx": BitVec(f"{id}_bx", 16),
        "r11w": BitVec(f"{id}_r11w", 16),
        "r10w": BitVec(f"{id}_r10w", 16),
        "r9w": BitVec(f"{id}_r9w", 16),
        "r8w": BitVec(f"{id}_r8w", 16),
        "ax": BitVec(f"{id}_ax", 16),
        "cx": BitVec(f"{id}_cx", 16),
        "dx": BitVec(f"{id}_dx", 16),
        "si": BitVec(f"{id}_si", 16),
        "di": BitVec(f"{id}_di", 16),
        "ip": BitVec(f"{id}_ip", 16),
        "sp": BitVec(f"{id}_sp", 16),

        # HWORD
        "r15b": BitVec(f"{id}_r15b", 8),
        "r14b": BitVec(f"{id}_r14b", 8),
        "r13b": BitVec(f"{id}_r13b", 8),
        "r12b": BitVec(f"{id}_r12b", 8),
        "bpl": BitVec(f"{id}_bpl", 8),
        "bl": BitVec(f"{id}_bl", 8),
        "r11b": BitVec(f"{id}_r11b", 8),
        "r10b": BitVec(f"{id}_r10b", 8),
        "r9b": BitVec(f"{id}_r9b", 8),
        "r8b": BitVec(f"{id}_r8b", 8),
        "al": BitVec(f"{id}_al", 8),
        "cl": BitVec(f"{id}_cl", 8),
        "dl": BitVec(f"{id}_dl", 8),
        "ah": BitVec(f"{id}_ah", 8),
        "bh": BitVec(f"{id}_bh", 8),
        "ch": BitVec(f"{id}_ch", 8),
        "dh": BitVec(f"{id}_dh", 8),
        "sil": BitVec(f"{id}_sil", 8),
        "dil": BitVec(f"{id}_dil", 8),
        "spl": BitVec(f"{id}_spl", 8),
    }

    # express relations
    s.add((regs["r15"] & 0xffffffff) == ZeroExt(32, regs["r15d"]), (regs["r15"] & 0xffff) == ZeroExt(48, regs["r15w"]),
          (regs["r15"] & 0xff) == ZeroExt(56, regs["r15b"]))
    s.add((regs["r14"] & 0xffffffff) == ZeroExt(32, regs["r14d"]), (regs["r14"] & 0xffff) == ZeroExt(48, regs["r14w"]),
          (regs["r14"] & 0xff) == ZeroExt(56, regs["r14b"]))
    s.add((regs["r13"] & 0xffffffff) == ZeroExt(32, regs["r13d"]), (regs["r13"] & 0xffff) == ZeroExt(48, regs["r13w"]),
          (regs["r13"] & 0xff) == ZeroExt(56, regs["r13b"]))
    s.add((regs["r12"] & 0xffffffff) == ZeroExt(32, regs["r12d"]), (regs["r12"] & 0xffff) == ZeroExt(48, regs["r12w"]),
          (regs["r12"] & 0xff) == ZeroExt(56, regs["r12b"]))
    s.add((regs["r11"] & 0xffffffff) == ZeroExt(32, regs["r11d"]), (regs["r11"] & 0xffff) == ZeroExt(48, regs["r11w"]),
          (regs["r11"] & 0xff) == ZeroExt(56, regs["r11b"]))
    s.add((regs["r10"] & 0xffffffff) == ZeroExt(32, regs["r10d"]), (regs["r10"] & 0xffff) == ZeroExt(48, regs["r10w"]),
          (regs["r10"] & 0xff) == ZeroExt(56, regs["r10b"]))
    s.add((regs["r9"] & 0xffffffff) == ZeroExt(32, regs["r9d"]), (regs["r9"] & 0xffff) == ZeroExt(48, regs["r9w"]),
          (regs["r9"] & 0xff) == ZeroExt(56, regs["r9b"]))
    s.add((regs["r8"] & 0xffffffff) == ZeroExt(32, regs["r8d"]), (regs["r8"] & 0xffff) == ZeroExt(48, regs["r8w"]),
          (regs["r8"] & 0xff) == ZeroExt(56, regs["r8b"]))
    s.add((regs["rbp"] & 0xffffffff) == ZeroExt(32, regs["ebp"]), (regs["rbp"] & 0xffff) == ZeroExt(48, regs["bp"]),
          (regs["rbp"] & 0xff) == ZeroExt(56, regs["bpl"]))
    s.add((regs["rax"] & 0xffffffff) == ZeroExt(32, regs["eax"]), (regs["rax"] & 0xffff) == ZeroExt(48, regs["ax"]),
          (regs["rax"] & 0xff) == ZeroExt(56, regs["al"]), ((regs["rax"] & 0xff00) >> 8) == ZeroExt(56, regs["ah"]))
    s.add((regs["rbx"] & 0xffffffff) == ZeroExt(32, regs["ebx"]), (regs["rbx"] & 0xffff) == ZeroExt(48, regs["bx"]),
          (regs["rbx"] & 0xff) == ZeroExt(56, regs["bl"]), ((regs["rbx"] & 0xff00) >> 8) == ZeroExt(56, regs["bh"]))
    s.add((regs["rcx"] & 0xffffffff) == ZeroExt(32, regs["ecx"]), (regs["rcx"] & 0xffff) == ZeroExt(48, regs["cx"]),
          (regs["rcx"] & 0xff) == ZeroExt(56, regs["cl"]), ((regs["rcx"] & 0xff00) >> 8) == ZeroExt(56, regs["ch"]))
    s.add((regs["rdx"] & 0xffffffff) == ZeroExt(32, regs["edx"]), (regs["rdx"] & 0xffff) == ZeroExt(48, regs["dx"]),
          (regs["rdx"] & 0xff) == ZeroExt(56, regs["dl"]), ((regs["rdx"] & 0xff00) >> 8) == ZeroExt(56, regs["dh"]))
    s.add((regs["rdi"] & 0xffffffff) == ZeroExt(32, regs["edi"]), (regs["rdi"] & 0xffff) == ZeroExt(48, regs["di"]),
          (regs["rdi"] & 0xff) == ZeroExt(56, regs["dil"]))
    s.add((regs["rsi"] & 0xffffffff) == ZeroExt(32, regs["esi"]), (regs["rsi"] & 0xffff) == ZeroExt(48, regs["si"]),
          (regs["rsi"] & 0xff) == ZeroExt(56, regs["sil"]))
    s.add((regs["rsp"] & 0xffffffff) == ZeroExt(32, regs["esp"]), (regs["rsp"] & 0xffff) == ZeroExt(48, regs["sp"]),
          (regs["rsp"] & 0xff) == ZeroExt(56, regs["spl"]))

    s.add((regs["eflags"] & 1) == ZeroExt(31, regs["cf"]))
    s.add(((regs["eflags"] >> 2) & 1) == ZeroExt(31, regs["pf"]))
    s.add(((regs["eflags"] >> 4) & 1) == ZeroExt(31, regs["af"]))
    s.add(((regs["eflags"] >> 6) & 1) == ZeroExt(31, regs["zf"]))
    s.add(((regs["eflags"] >> 7) & 1) == ZeroExt(31, regs["sf"]))
    s.add(((regs["eflags"] >> 8) & 1) == ZeroExt(31, regs["tf"]))
    s.add(((regs["eflags"] >> 9) & 1) == ZeroExt(31, regs["if"]))
    s.add(((regs["eflags"] >> 10) & 1) == ZeroExt(31, regs["df"]))
    s.add(((regs["eflags"] >> 11) & 1) == ZeroExt(31, regs["of"]))
    s.add(((regs["eflags"] >> 21) & 1) == ZeroExt(31, regs["if"]))

    return regs


def init_solver():
    solver = Solver()
    init_registers(solver, "")


if __name__ == "__main__":
    init_solver()

from z3 import *


class ProcessorState:
    def __init__(self, regs: dict, fpregs: dict, memory: dict) -> None:
        self.regs = regs
        self.fpregs = fpregs
        self.memory = memory


class ProcessorConstraints:
    def __init__(self, regs: dict, fpregs: dict, memory: dict) -> None:
        self.regs = regs
        self.fpregs = fpregs
        self.memory = memory


states_and = [
    ProcessorState(
        {
            "r15": 0x7ffe0e8bcef5,
            "r14": 0x7ffe0e8bcef8,
            "r13": 0x7ffe0e8bcf10,
            "r12": 0x42a5ebfd3000,
            "rbp": 0x7ffe0e8bcf70,
            "rbx": 0x0,
            "r11": 0x246,
            "r10": 0x0,
            "r9": 0x7f6eef8d1440,
            "r8": 0x0,
            "rax": 0x1,
            "rcx": 0x7ffe0e8bcf11,
            "rdx": 0x0,
            "rsi": 0x7ffe0e8bcf10,
            "rdi": 0x1,
            "orig_rax": 0xffffffffffffffff,
            "rip": 0x42a5ebfd301c,
            "cs": 0x33,
            "eflags": 0x206,
            "rsp": 0x7ffe0e8bce80,
            "ss": 0x2b,
            "fs_base": 0x7f6eef8d1440,
            "gs_base": 0x0,
            "ds": 0x0,
            "es": 0x0,
            "fs": 0x0,
            "gs": 0x0,
        }, {}, {
            0x7ffe0e8bcf68: 0x7f6eef957000,
            0x7ffe0e8bcf60: 0x55e1cdbeedb8,
            0x7ffe0e8bcf58: 0x7ffe0e8bd0b8,
            0x7ffe0e8bcf50: 0x0,
            0x7ffe0e8bcf48: 0x7ffe0e8bcfa0,
            0x7ffe0e8bcf40: 0x7ffe0e8bd06b,
            0x7ffe0e8bce98: 0x55e1cdbe9498,
            0x7ffe0e8bce88: 0x42a5ebfd3018,
            0x7ffe0e8bcf70: 0x1,
            0x7ffe0e8bcea0: 0x0,
            0x7ffe0e8bcf11: 0x7900000000000000,
            0x7ffe0e8bce80: 0x42a5ebfd3018,
            0x7f6eef8d1440: 0x7f6eef8d1440,
            0x7ffe0e8bcee0: 0x55e1cf7182b0,
            0x42a5ebfd3000: 0xff834801fe4c8d48,
            0x7ffe0e8bcf08: 0x7ffe0e8ed000,
            0x7ffe0e8bcea8: 0x0,
            0x7ffe0e8bcf10: 0x78,
            0x7ffe0e8bce90: 0x42a5ebfd3018,
            0x7ffe0e8bcef8: 0x55e1cf7184b0,
            0x7ffe0e8bced8: 0x55e1cdbed2e4,
            0x7ffe0e8bceb0: 0x55e1cf719490,
            0x7ffe0e8bceb8: 0x55e1cf7196a0,
            0x7ffe0e8bcec0: 0x2,
            0x7ffe0e8bcec8: 0x40,
            0x7ffe0e8bced0: 0x55e1cf719490,
            0x7ffe0e8bcee8: 0x7ffe0e8bcef6,
            0x7ffe0e8bcef0: 0x782d720000000000,
            0x7ffe0e8bcf00: 0x7ffe0e8eb000,
            0x7ffe0e8bcf18: 0x179,
            0x7ffe0e8bcf20: 0x100,
            0x7ffe0e8bcf28: 0x279,
            0x7ffe0e8bcef5: 0xe1cf7184b0782d72,
            0x7ffe0e8bcf30: 0x379,
            0x7ffe0e8bcf38: 0x5f2,
        }, ),
    ProcessorState(
        {
            "r15": 0x7ffe0e8bcef5,
            "r14": 0x7ffe0e8bcef8,
            "r13": 0x7ffe0e8bcf10,
            "r12": 0x42a5ebfd3000,
            "rbp": 0x7ffe0e8bcf70,
            "rbx": 0x0,
            "r11": 0x246,
            "r10": 0x0,
            "r9": 0x7f6eef8d1440,
            "r8": 0x0,
            "rax": 0x7900000000000001,
            "rcx": 0x7ffe0e8bcf11,
            "rdx": 0x0,
            "rsi": 0x7ffe0e8bcf10,
            "rdi": 0x1,
            "orig_rax": 0xffffffffffffffff,
            "rip": 0x42a5ebfd301f,
            "cs": 0x33,
            "eflags": 0x202,
            "rsp": 0x7ffe0e8bce80,
            "ss": 0x2b,
            "fs_base": 0x7f6eef8d1440,
            "gs_base": 0x0,
            "ds": 0x0,
            "es": 0x0,
            "fs": 0x0,
            "gs": 0x0,
        }, {}, {
            0x7ffe0e8bcf68: 0x7f6eef957000,
            0x7ffe0e8bcf60: 0x55e1cdbeedb8,
            0x7ffe0e8bcf58: 0x7ffe0e8bd0b8,
            0x7ffe0e8bcf50: 0x0,
            0x7ffe0e8bcf48: 0x7ffe0e8bcfa0,
            0x7ffe0e8bcf40: 0x7ffe0e8bd06b,
            0x7ffe0e8bce98: 0x55e1cdbe9498,
            0x7ffe0e8bce88: 0x42a5ebfd3018,
            0x7ffe0e8bcf70: 0x1,
            0x7ffe0e8bcea0: 0x0,
            0x7ffe0e8bcf11: 0x7900000000000000,
            0x7ffe0e8bce80: 0x42a5ebfd3018,
            0x7f6eef8d1440: 0x7f6eef8d1440,
            0x7ffe0e8bcee0: 0x55e1cf7182b0,
            0x42a5ebfd3000: 0xff834801fe4c8d48,
            0x7ffe0e8bcf08: 0x7ffe0e8ed000,
            0x7ffe0e8bcea8: 0x0,
            0x7ffe0e8bcf10: 0x78,
            0x7ffe0e8bce90: 0x42a5ebfd3018,
            0x7ffe0e8bcef8: 0x55e1cf7184b0,
            0x7ffe0e8bced8: 0x55e1cdbed2e4,
            0x7ffe0e8bceb0: 0x55e1cf719490,
            0x7ffe0e8bceb8: 0x55e1cf7196a0,
            0x7ffe0e8bcec0: 0x2,
            0x7ffe0e8bcec8: 0x40,
            0x7ffe0e8bced0: 0x55e1cf719490,
            0x7ffe0e8bcee8: 0x7ffe0e8bcef6,
            0x7ffe0e8bcef0: 0x782d720000000000,
            0x7ffe0e8bcf00: 0x7ffe0e8eb000,
            0x7ffe0e8bcf18: 0x179,
            0x7ffe0e8bcf20: 0x100,
            0x7ffe0e8bcf28: 0x279,
            0x7ffe0e8bcef5: 0xe1cf7184b0782d72,
            0x7ffe0e8bcf30: 0x379,
            0x7ffe0e8bcf38: 0x5f2,
        }, )
]

states_ret = [
ProcessorState(
        {
            "r15": 0x7ffe0e8bcef5,
            "r14": 0x7ffe0e8bcef8,
            "r13": 0x7ffe0e8bcf10,
            "r12": 0x42a5ebfd3000,
            "rbp": 0x7ffe0e8bcf70,
            "rbx": 0x0,
            "r11": 0x246,
            "r10": 0x0,
            "r9": 0x7f6eef8d1440,
            "r8": 0x0,
            "rax": 0x7900000000000001,
            "rcx": 0x7ffe0e8bcf21,
            "rdx": 0x0,
            "rsi": 0x7ffe0e8bcf10,
            "rdi": 0x1,
            "orig_rax": 0xffffffffffffffff,
            "rip": 0x42a5ebfd3026,
            "cs": 0x33,
            "eflags": 0x206,
            "rsp": 0x7ffe0e8bce80,
            "ss": 0x2b,
            "fs_base": 0x7f6eef8d1440,
            "gs_base": 0x0,
            "ds": 0x0,
            "es": 0x0,
            "fs": 0x0,
            "gs": 0x0,
        }, {}, {
            0x7ffe0e8bcf68: 0x7f6eef957000,
            0x7ffe0e8bcf60: 0x55e1cdbeedb8,
            0x7ffe0e8bcf58: 0x7ffe0e8bd0b8,
            0x7ffe0e8bcf50: 0x0,
            0x7ffe0e8bcf48: 0x7ffe0e8bcfa0,
            0x7ffe0e8bcf40: 0x7ffe0e8bd06b,
            0x7ffe0e8bce98: 0x55e1cdbe9498,
            0x7ffe0e8bce88: 0x42a5ebfd3018,
            0x7ffe0e8bcf70: 0x1,
            0x7ffe0e8bcea0: 0x0,
            0x7ffe0e8bcf21: 0x7900000000000001,
            0x7ffe0e8bce90: 0x42a5ebfd3018,
            0x7f6eef8d1440: 0x7f6eef8d1440,
            0x7ffe0e8bcee0: 0x55e1cf7182b0,
            0x42a5ebfd3000: 0xff834801fe4c8d48,
            0x7ffe0e8bcf08: 0x7ffe0e8ed000,
            0x7ffe0e8bcea8: 0x0,
            0x7ffe0e8bcf10: 0x78,
            0x7ffe0e8bcef8: 0x55e1cf7184b0,
            0x7ffe0e8bce80: 0x42a5ebfd3018,
            0x7ffe0e8bced8: 0x55e1cdbed2e4,
            0x7ffe0e8bceb0: 0x55e1cf719490,
            0x7ffe0e8bceb8: 0x55e1cf7196a0,
            0x7ffe0e8bcec0: 0x2,
            0x7ffe0e8bcec8: 0x40,
            0x7ffe0e8bced0: 0x55e1cf719490,
            0x7ffe0e8bcee8: 0x7ffe0e8bcef6,
            0x7ffe0e8bcef0: 0x782d720000000000,
            0x7ffe0e8bcf00: 0x7ffe0e8eb000,
            0x7ffe0e8bcf18: 0x179,
            0x7ffe0e8bcf20: 0x100,
            0x7ffe0e8bcf28: 0x279,
            0x7ffe0e8bcef5: 0xe1cf7184b0782d72,
            0x7ffe0e8bcf30: 0x379,
            0x7ffe0e8bcf38: 0x5f2,
        }, ),
    ProcessorState(
        {
            "r15": 0x7ffe0e8bcef5,
            "r14": 0x7ffe0e8bcef8,
            "r13": 0x7ffe0e8bcf10,
            "r12": 0x42a5ebfd3000,
            "rbp": 0x7ffe0e8bcf70,
            "rbx": 0x0,
            "r11": 0x246,
            "r10": 0x0,
            "r9": 0x7f6eef8d1440,
            "r8": 0x0,
            "rax": 0x7900000000000001,
            "rcx": 0x7ffe0e8bcf21,
            "rdx": 0x0,
            "rsi": 0x7ffe0e8bcf10,
            "rdi": 0x1,
            "orig_rax": 0xffffffffffffffff,
            "rip": 0x42a5ebfd3018,
            "cs": 0x33,
            "eflags": 0x206,
            "rsp": 0x7ffe0e8bce88,
            "ss": 0x2b,
            "fs_base": 0x7f6eef8d1440,
            "gs_base": 0x0,
            "ds": 0x0,
            "es": 0x0,
            "fs": 0x0,
            "gs": 0x0,
        }, {}, {
            0x7ffe0e8bcf68: 0x7f6eef957000,
            0x7ffe0e8bcf60: 0x55e1cdbeedb8,
            0x7ffe0e8bcf58: 0x7ffe0e8bd0b8,
            0x7ffe0e8bcf50: 0x0,
            0x7ffe0e8bcf48: 0x7ffe0e8bcfa0,
            0x7ffe0e8bceb0: 0x55e1cf719490,
            0x7ffe0e8bce98: 0x55e1cdbe9498,
            0x7ffe0e8bce88: 0x42a5ebfd3018,
            0x7ffe0e8bcf70: 0x1,
            0x7ffe0e8bcea0: 0x0,
            0x7ffe0e8bcf21: 0x7900000000000001,
            0x7ffe0e8bce90: 0x42a5ebfd3018,
            0x7f6eef8d1440: 0x7f6eef8d1440,
            0x7ffe0e8bcee0: 0x55e1cf7182b0,
            0x42a5ebfd3000: 0xff834801fe4c8d48,
            0x7ffe0e8bcf08: 0x7ffe0e8ed000,
            0x7ffe0e8bcea8: 0x0,
            0x7ffe0e8bcf10: 0x78,
            0x7ffe0e8bcef8: 0x55e1cf7184b0,
            0x7ffe0e8bced8: 0x55e1cdbed2e4,
            0x7ffe0e8bceb8: 0x55e1cf7196a0,
            0x7ffe0e8bcec0: 0x2,
            0x7ffe0e8bcec8: 0x40,
            0x7ffe0e8bced0: 0x55e1cf719490,
            0x7ffe0e8bcee8: 0x7ffe0e8bcef6,
            0x7ffe0e8bcef0: 0x782d720000000000,
            0x7ffe0e8bcf00: 0x7ffe0e8eb000,
            0x7ffe0e8bcf18: 0x179,
            0x7ffe0e8bcf20: 0x100,
            0x7ffe0e8bcf28: 0x279,
            0x7ffe0e8bcef5: 0xe1cf7184b0782d72,
            0x7ffe0e8bcf30: 0x379,
            0x7ffe0e8bcf38: 0x5f2,
            0x7ffe0e8bcf40: 0x7ffe0e8bd06b,
        }, )
]

qword_reg_names = [
    "r15",
    "r14",
    "r13",
    "r12",
    "rbp",
    "rbx",
    "r11",
    "r10",
    "r9",
    "r8",
    "rax",
    "rcx",
    "rdx",
    "rsi",
    "rdi",
    "rip",
    "rsp"
]

def init_registers(s: Solver, processor_state: ProcessorState, id) -> ProcessorConstraints:
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
    s.add(((regs["eflags"] >> 21) & 1) == ZeroExt(31, regs["id"]))

    for name, v in regs.items():
        if name not in processor_state.regs.keys():
            continue
        s.add(v == processor_state.regs[name])

    memory = dict()

    for address, value in processor_state.memory.items():
        b = False
        # Don't model overlapping addresses
        for address2, _ in processor_state.memory.items():
            if address < address2 < (address + 8):
                b = True
                break
        if b:
            continue
        b = BitVec(f"{id}_{hex(address)}", 64)
        memory[address] = b
        s.add(b == value)

    return ProcessorConstraints(regs, {}, memory)

'''    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "ADD",
        "%s, %s",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "ADD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        2
    },
    (instruction) {
        "ADD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_WORD, },
        3
    },
    (instruction) {
        "ADD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "ADD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_WORD, },
        4
    },
    (instruction) {
        "ADD",
        "(%s), %s",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_DWORD, },
        4
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_QWORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::GP_REGISTER_HWORD, },
        2
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_DWORD, parameter_type::INTEGER, },
        6
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::GP_REGISTER_HWORD, },
        3
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::SSE_REGISTER, },
        3
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX_REGISTER, },
        3
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_REGISTER, },
        3
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::AVX512_BITMASK, },
        3
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE8, },
        7
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE16, },
        7
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE32, },
        8
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::IMMEDIATE64, },
        8
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_WORD, parameter_type::INTEGER, },
        7
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::SSE_REGISTER, },
        2
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX_REGISTER, },
        2
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_REGISTER, },
        2
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::AVX512_BITMASK, },
        2
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE8, },
        6
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE16, },
        6
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE32, },
        7
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::IMMEDIATE64, },
        7
    },
    (instruction) {
        "ADD",
        "%s, (%s)",
        2,
        {parameter_type::GP_REGISTER_HWORD, parameter_type::INTEGER, },
        6
    },
'''

mnemonics = [
    "AND",
    "RET",
]


def build_operand():
    pass

def model_add(s: Solver, mnemonic, instruction_size, pre_regs: dict, post_regs:dict, pre_absolute, post_absolute):
    s.add(Implies(mnemonic == "AND", And(instruction_size > 2, instruction_size <= 8, instruction_size != 5)))



# The ret instruction
def model_ret(s: Solver, mnemonic, instruction_size, pre: ProcessorConstraints, post: ProcessorConstraints, pre_absolute, post_absolute):
    if post_absolute.regs["rip"] in pre_absolute.memory.values() and pre_absolute.regs["rsp"] in pre.memory.keys():
        # New %rip must be old (%rsp)
        s.add(Implies(mnemonic == "RET", post.regs["rip"] == pre.memory[pre_absolute.regs["rsp"]]))
        # New %rsp must be increased by register size
        s.add(Implies(mnemonic == "RET", post.regs["rsp"] == pre.regs["rsp"] + 8))
        # All remaining registers, including eflags, must stay the same
        for n in qword_reg_names + ["eflags"]:
            if n not in ["rsp", "rip"]:
                s.add(Implies(mnemonic == "RET", post.regs[n] == pre.regs[n]))
        # There must be no changes to memory
        for address, value in pre.memory.items():
            if address in post.memory.keys():
                s.add(Implies(mnemonic == "RET", post.memory[address] == value))
    else:
        s.add(mnemonic != "RET")



states = states_and

def init_solver():
    solver = Solver()
    pre = init_registers(solver, states[0], "pre")
    post = init_registers(solver, states[1], "post")

    mnemonic = String('mnemonic')
    solver.add(Or(*([mnemonic == m for m in mnemonics])))
    instruction_size = BitVec('instrucion_size', 64)
    solver.add(instruction_size == post.regs["rip"] - pre.regs["rip"])

    model_add(solver, mnemonic, instruction_size, pre, post, states[0], states[1])
    model_ret(solver, mnemonic, instruction_size, pre, post, states[0], states[1])

    if solver.check() == sat:
        print(solver.model()[mnemonic])
    else:
        print("unsat")


if __name__ == "__main__":
    init_solver()


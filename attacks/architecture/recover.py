from z3 import *

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

dword_reg_names = [
    "r15d",
    "r14d",
    "r13d",
    "r12d",
    "ebp",
    "ebx",
    "r11d",
    "r10d",
    "r9d",
    "r8d",
    "eax",
    "ecx",
    "edx",
    "esi",
    "edi",
    "eip",
    "esp"
]

word_reg_names = [
    "r15w",
    "r14w",
    "r13w",
    "r12w",
    "bp",
    "bx",
    "r11w",
    "r10w",
    "r9w",
    "r8w",
    "ax",
    "cx",
    "dx",
    "si",
    "di",
    "ip",
    "sp",
]

hword_reg_names = [
    "r15b",
    "r14b",
    "r13b",
    "r12b",
    "bpl",
    "bl",
    "r11b",
    "r10b",
    "r9b",
    "r8b",
    "al",
    "cl",
    "dl",
    "ah",
    "bh",
    "ch",
    "dh",
    "sil",
    "dil",
    "spl",
]

parameter_types = [
    "GP_REGISTER_QWORD",
    "GP_REGISTER_DWORD",
    "GP_REGISTER_WORD",
    "GP_REGISTER_HWORD",
    "IMMEDIATE64",
    "IMMEDIATE32",
    "IMMEDIATE16",
    "IMMEDIATE8",
]


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


class Operand:
    def __init__(self, s: Solver, id):
        self.type = String(f"{id}_type")
        s.add(Or(*(self.type == t for t in parameter_types)))
        self.immediate = BitVec(f"{id}_immediate", 64)
        self.register = String(f"{id}_register")
        self.memory = Bool(f"{id}_memory")
        self.used = Bool(f"{id}_used")

        # Constrain width of immediates
        s.add(Implies(self.type == "IMMEDIATE8", self.immediate < 0x100))
        s.add(Implies(self.type == "IMMEDIATE16", And(self.immediate < 0x10000)))
        s.add(Implies(self.type == "IMMEDIATE32", And(self.immediate < 0x100000000)))

        # Constrain register names
        s.add(Implies(self.type == "GP_REGISTER_QWORD", Or(*(self.register == r for r in qword_reg_names))))
        s.add(Implies(self.type == "GP_REGISTER_DWORD", Or(*(self.register == r for r in dword_reg_names))))
        s.add(Implies(self.type == "GP_REGISTER_WORD", Or(*(self.register == r for r in word_reg_names))))
        s.add(Implies(self.type == "GP_REGISTER_HWORD", Or(*(self.register == r for r in hword_reg_names))))

        # ...

        s.add(Implies(Or(*(self.type == r for r in ["IMMEDIATE8", "IMMEDIATE16", "IMMEDIATE32", "IMMEDIATE64"])),
                      self.register == "rax"))

        s.add(Implies(Or(*(self.type == r for r in
                           ["GP_REGISTER_QWORD", "GP_REGISTER_DWORD", "GP_REGISTER_WORD", "GP_REGISTER_HWORD"])),
                      self.immediate == 0))


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

states_call = [
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
            "rax": 0x6b00000000000005,
            "rcx": 0x7ffe0e8bcf39,
            "rdx": 0x0,
            "rsi": 0x7ffe0e8bcf10,
            "rdi": 0x4,
            "orig_rax": 0xffffffffffffffff,
            "rip": 0x42a5ebfd3013,
            "cs": 0x33,
            "eflags": 0x202,
            "rsp": 0x7ffe0e8bce98,
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
            0x7ffe0e8bcec0: 0x2,
            0x7ffe0e8bceb8: 0x55e1cf7196a0,
            0x7ffe0e8bceb0: 0x55e1cf719490,
            0x7ffe0e8bce98: 0x55e1cdbe9498,
            0x7ffe0e8bcea0: 0x0,
            0x7ffe0e8bcf70: 0x1,
            0x7f6eef8d1440: 0x7f6eef8d1440,
            0x7ffe0e8bcee0: 0x55e1cf7182b0,
            0x42a5ebfd3000: 0xff834801fe4c8d48,
            0x7ffe0e8bcf08: 0x7ffe0e8ed000,
            0x7ffe0e8bcea8: 0x0,
            0x7ffe0e8bcf39: 0x6b00000000000005,
            0x7ffe0e8bcf10: 0x78,
            0x7ffe0e8bcef8: 0x55e1cf7184b0,
            0x7ffe0e8bced8: 0x55e1cdbed2e4,
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
            0x7ffe0e8bcf48: 0x7ffe0e8bcfa0,
            0x7ffe0e8bcf50: 0x0,
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
            "rax": 0x6b00000000000005,
            "rcx": 0x7ffe0e8bcf39,
            "rdx": 0x0,
            "rsi": 0x7ffe0e8bcf10,
            "rdi": 0x4,
            "orig_rax": 0xffffffffffffffff,
            "rip": 0x42a5ebfd3000,
            "cs": 0x33,
            "eflags": 0x202,
            "rsp": 0x7ffe0e8bce90,
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
            0x7ffe0e8bceb8: 0x55e1cf7196a0,
            0x7ffe0e8bceb0: 0x55e1cf719490,
            0x7ffe0e8bce98: 0x55e1cdbe9498,
            0x7ffe0e8bcea0: 0x0,
            0x7ffe0e8bcf70: 0x1,
            0x7f6eef8d1440: 0x7f6eef8d1440,
            0x7ffe0e8bcee0: 0x55e1cf7182b0,
            0x42a5ebfd3000: 0xff834801fe4c8d48,
            0x7ffe0e8bcf08: 0x7ffe0e8ed000,
            0x7ffe0e8bcea8: 0x0,
            0x7ffe0e8bcf39: 0x6b00000000000005,
            0x7ffe0e8bcf10: 0x78,
            0x7ffe0e8bce90: 0x42a5ebfd3018,
            0x7ffe0e8bcef8: 0x55e1cf7184b0,
            0x7ffe0e8bced8: 0x55e1cdbed2e4,
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
            0x7ffe0e8bcf48: 0x7ffe0e8bcfa0,
        }, ),
]


def init_registers(s: Solver, processor_state: ProcessorState, id) -> ProcessorConstraints:
    regs = {
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
    }

    for n in qword_reg_names:
        regs[n] = BitVec(f"{id}_{n}", 64)

    for n in dword_reg_names:
        regs[n] = BitVec(f"{id}_{n}", 32)

    for n in word_reg_names:
        regs[n] = BitVec(f"{id}_{n}", 16)

    for n in hword_reg_names:
        regs[n] = BitVec(f"{id}_{n}", 8)

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


mnemonics = [
    "ADD",
    "RET",
    "CALL",
]


def build_operand():
    pass


class InstructionParameters:
    def __init__(self, s: Solver, id, pre: ProcessorState, post: ProcessorState):
        self.s: Solver = s
        self.id = f"{id}"
        self.pre_absolute: ProcessorState = pre
        self.post_absolute: ProcessorState = post
        self.pre: ProcessorConstraints = init_registers(s, states[0], f"{id}_pre")
        self.post: ProcessorConstraints = init_registers(s, states[1], f"{id}_post")
        self.mnemonic = mnemonic = String(f"{id}_mnemonic")
        s.add(Or(*([mnemonic == m for m in mnemonics])))
        self.instruction_size = BitVec(f"{id}_instrucion_size", 64)
        s.add(self.instruction_size == self.post.regs["rip"] - self.pre.regs["rip"])
        self.operands: list[Operand] = [Operand(s, f"{n}_{id}") for n in range(4)]


def model_add(p: InstructionParameters):
    # Does not consider memory operands with displacement
    # Does not consider variations where 32-bit immediate is sign-extended

    p.s.add(Implies(p.mnemonic == "ADD", And(p.instruction_size > 2, p.instruction_size <= 8, p.instruction_size != 5)))
    p.s.add(Implies(p.mnemonic == "ADD", And(p.operands[0].used, p.operands[1].used, Not(p.operands[2].used), p.operands[3].used)))

    # Constrain operand types
    p.s.add(Implies(p.mnemonic == "ADD", Or(
        p.operands[1].type == "GP_REGISTER_QWORD",
        p.operands[1].type == "GP_REGISTER_DWORD",
        p.operands[1].type == "GP_REGISTER_WORD",
        p.operands[1].type == "GP_REGISTER_HWORD",

    )))
    p.s.add(Implies(p.mnemonic == "ADD", Not(p.operands[0].type == "IMMEDIATE64")))

    # Destination is register
    p.s.add(Implies(p.mnemonic == "ADD", Not(p.operands[1].memory)), And(

        # Source is immediate
        Implies(p.operands[0].type == "IMMEDIATE32", Or(*(
            Extract(31, 0, p.post.regs[s] ) == Extract(31, 0, p.pre.regs[s]) + Extract(31, 0,p.operands[0].immediate)
            for s in dword_reg_names
        ))),
    ))


    add_destination_in_memory = Bool(f"{id}_add_destination_in_memory")




# The ret instruction
def model_ret(p: InstructionParameters):
    if p.post_absolute.regs["rip"] in p.pre_absolute.memory.values() and p.pre_absolute.regs[
        "rsp"] in p.pre.memory.keys():
        # New %rip must be old (%rsp)
        p.s.add(Implies(p.mnemonic == "RET", p.post.regs["rip"] == p.pre.memory[p.pre_absolute.regs["rsp"]]))
        # New %rsp must be increased by register size
        p.s.add(Implies(p.mnemonic == "RET", p.post.regs["rsp"] == p.pre.regs["rsp"] + 8))
        # All remaining registers, including eflags, must stay the same
        for n in qword_reg_names + ["eflags"]:
            if n not in ["rsp", "rip"]:
                p.s.add(Implies(p.mnemonic == "RET", p.post.regs[n] == p.pre.regs[n]))
        # There must be no changes to memory
        for address, value in p.pre.memory.items():
            if address in p.post.memory.keys():
                p.s.add(Implies(p.mnemonic == "RET", p.post.memory[address] == value))
        # There are no parameters
        for o in p.operands:
            p.s.add(Implies(p.mnemonic == "RET", Not(o.used)))
    else:
        p.s.add(p.mnemonic != "RET")


def model_call(p: InstructionParameters):
    call_instruction_size = BitVec(f"{p.id}_call_instruction_size", 64)

    p.s.add(Implies(p.mnemonic == "CALL", p.operands[0].used))
    for o in p.operands[2:]:
        p.s.add(Implies(p.mnemonic == "CALL", Not(o.used)))

    # New %rsp must be decreased by register size
    p.s.add(Implies(p.mnemonic == "CALL", p.post.regs["rsp"] == p.pre.regs["rsp"] - 8))

    # All except for rsp and rip registers, including eflags, must stay the same
    for n in qword_reg_names + ["eflags"]:
        if n not in ["rsp", "rip"]:
            p.s.add(Implies(p.mnemonic == "CALL", p.post.regs[n] == p.pre.regs[n]))

    p.s.add(Implies(p.mnemonic == "CALL",
                    Or(p.operands[0].type == "IMMEDIATE32", p.operands[0].type == "GP_REGISTER_QWORD")))

    # rsp must have been saved during trace
    if p.post_absolute.regs["rsp"] not in p.post_absolute.memory:
        p.s.add(p.mnemonic != "CALL")
        return

    # Return address must have been saved
    p.s.add(p.post_absolute.memory[p.post_absolute.regs["rsp"]] == p.pre_absolute.regs["rip"] + call_instruction_size)

    # Near relative call
    p.s.add(Implies(And(p.mnemonic == "CALL", p.operands[0].type == "IMMEDIATE32"), And(
        call_instruction_size == 5,
        p.post_absolute.regs["rip"] == (p.pre_absolute.regs["rip"] + call_instruction_size + SignExt(32, Extract(31, 0,
                                                                                                                 p.operands[
                                                                                                                     0].immediate))),
        Not(p.operands[0].memory),
        Not(p.operands[1].used)
    )))

    p.s.add(Implies(And(p.mnemonic == "CALL", p.operands[0].type == "GP_REGISTER_QWORD", Not(p.operands[1].used)), And(
        Or(call_instruction_size == 2, call_instruction_size == 3)
    )))

    p.s.add(Implies(And(p.mnemonic == "CALL", p.operands[0].type == "GP_REGISTER_QWORD", p.operands[1].used), And(
        Or(call_instruction_size == 6, call_instruction_size == 7)
    )))

    # Absolute address in register
    p.s.add(
        Implies(And(p.mnemonic == "CALL", p.operands[0].type == "GP_REGISTER_QWORD", Not(p.operands[0].memory)), And(
            Or(*(
                And(p.operands[0].register == s, p.post_absolute.regs["rip"] == p.pre_absolute.regs[s])
                for s in qword_reg_names
            )),
            Not(p.operands[1].used)
        )))

    # Absolute address in memory, no displacement
    p.s.add(Implies(And(p.mnemonic == "CALL", p.operands[0].type == "GP_REGISTER_QWORD", p.operands[0].memory,
                        Not(p.operands[1].used)),
                    Or(*(
                        And(p.operands[0].register == s,
                            (p.post_absolute.regs["rip"] == p.pre_absolute.memory[p.pre_absolute.regs[s]])) if
                        p.pre_absolute.regs[s] in p.pre_absolute.memory else False
                        for s in qword_reg_names
                    ))
                    ))

    p.s.add(Implies(And(p.mnemonic == "CALL", p.operands[0].type == "GP_REGISTER_QWORD", p.operands[0].memory,
                         p.operands[1].used), And(
        p.operands[1].type == "IMMEDIATE32",
        Not(p.operands[1].memory),
        Or(*(And(p.operands[0].register == s,
                 (SignExt(32, Extract(31, 0, p.operands[1].immediate)) + p.pre_absolute.memory[
                     p.pre_absolute.regs[s]] == p.post_absolute.regs["rip"])
                 if p.pre_absolute.regs[s] in p.pre_absolute.memory else False)
             for s in qword_reg_names
             ))
    )))


states = states_ret


def init_solver():
    solver = Solver()

    p = InstructionParameters(solver, "1", states[0], states[1])

    model_add(p)
    model_ret(p)
    model_call(p)

    if solver.check() == sat:
        print(solver.model()[p.mnemonic])
        print(hex(int(f"{solver.model()[p.operands[0].immediate]}")))
        print(solver.model()[p.operands[0].register])
        print(solver.model()[p.operands[0].type])
        print(solver.model()[p.operands[0].memory])
    else:
        print("unsat")


if __name__ == "__main__":
    init_solver()

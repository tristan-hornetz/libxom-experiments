from z3 import *
from trace import ProcessorState

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

# Only instruction with these mnemonics are modeled
# Any other instruction will result in 'unsat', unless its behavior can be modeled with one of the model
mnemonics = [
    "ADD",
    "RET",
    "CALL",
    "SUB",
    "DEC",
    "INC",
    "MOV",
    "JMP",
    "JG",
    "CMP",
    "LEA",
    "XCHG",
]

qword_reg_names_norip = list(filter(lambda r: r != "rip", qword_reg_names))
dword_reg_names_noeip = list(filter(lambda r: r != "eip", dword_reg_names))
word_reg_names_noip = list(filter(lambda r: r != "ip", word_reg_names))


class ProcessorConstraints:
    def __init__(self, regs: dict, fpregs: dict, memory: dict) -> None:
        self.regs = regs
        self.fpregs = fpregs
        self.memory = memory


class Operand:
    def __init__(self, s: Solver, id):
        self.type = String(f"{id}_type")
        self.immediate = BitVec(f"{id}_immediate", 64)
        self.register = String(f"{id}_register")
        self.memory = Bool(f"{id}_memory")
        self.used = Bool(f"{id}_used")
        self.is_immediate = Bool(f"{id}_is_immediate")
        self.bit_length = BitVec(f"{id}_bitsize", 16)
        self.index_register = String(f"{id}_index_register")
        self.scale_factor = BitVec(f"{id}_scale_factor", 2)
        self.displacement = BitVec(f"{id}_displacement", 32)

        s.add(Or(*(self.type == t for t in parameter_types)))

        # Constrain width of immediates
        s.add(Implies(self.type == "IMMEDIATE8", self.immediate == ZeroExt(56, Extract(7, 0, self.immediate))))
        s.add(Implies(self.type == "IMMEDIATE16", self.immediate == ZeroExt(48, Extract(15, 0, self.immediate))))
        s.add(Implies(self.type == "IMMEDIATE32", self.immediate == ZeroExt(32, Extract(31, 0, self.immediate))))

        # Constrain register names
        s.add(Implies(self.type == "GP_REGISTER_QWORD", Or(*(self.register == r for r in qword_reg_names))))
        s.add(Implies(self.type == "GP_REGISTER_DWORD", Or(*(self.register == r for r in dword_reg_names))))
        s.add(Implies(self.type == "GP_REGISTER_WORD", Or(*(self.register == r for r in word_reg_names))))
        s.add(Implies(self.type == "GP_REGISTER_HWORD", Or(*(self.register == r for r in hword_reg_names))))

        s.add(Or(*(self.bit_length == n for n in [8, 16, 32, 64])))

        s.add(Implies(Or(And(Not(self.memory), self.type == "GP_REGISTER_QWORD"), self.type == "IMMEDIATE64"),
                      self.bit_length == 64))
        s.add(Implies(Or(And(Not(self.memory), self.type == "GP_REGISTER_DWORD"), self.type == "IMMEDIATE32"),
                      self.bit_length == 32))
        s.add(Implies(Or(And(Not(self.memory), self.type == "GP_REGISTER_WORD"), self.type == "IMMEDIATE16"),
                      self.bit_length == 16))
        s.add(Implies(Or(And(Not(self.memory), self.type == "GP_REGISTER_HWORD"), self.type == "IMMEDIATE8"),
                      self.bit_length == 8))

        # ...

        s.add(Implies(Or(*(self.type == r for r in ["IMMEDIATE8", "IMMEDIATE16", "IMMEDIATE32", "IMMEDIATE64"])),
                      And(self.register == "rax", self.is_immediate)))

        s.add(Implies(Or(*(self.type == r for r in
                           ["GP_REGISTER_QWORD", "GP_REGISTER_DWORD", "GP_REGISTER_WORD", "GP_REGISTER_HWORD"])),
                      And(self.immediate == 0, Not(self.is_immediate))))

        s.add(Or(*(self.index_register == r for r in qword_reg_names)))


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
        b = BitVec(f"{id}_{hex(address)}", 64)
        memory[address] = b
        s.add(b == value)

    return ProcessorConstraints(regs, {}, memory)


class InstructionParameters:
    def __init__(self, s: Solver, id, pre: ProcessorState, post: ProcessorState, mnemonic, operands, next_instruction, is_last_instruction):
        self.s: Solver = s
        self.id = f"{id}"
        self.pre_absolute: ProcessorState = pre
        self.post_absolute: ProcessorState = post
        self.pre: ProcessorConstraints = init_registers(s, pre, f"{id}_pre")
        self.post: ProcessorConstraints = init_registers(s, post, f"{id}_post")
        self.next_instruction = next_instruction
        self.is_last_instruction = is_last_instruction
        self.mnemonic = mnemonic
        s.add(Or(*([mnemonic == m for m in mnemonics])))
        self.delta_rip = BitVec(f"{id}_instrucion_size", 64)
        s.add(self.delta_rip == self.post_absolute.regs["rip"] - self.pre_absolute.regs["rip"])
        self.operands: list[Operand] = operands

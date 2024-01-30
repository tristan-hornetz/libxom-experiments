from typing import Any, Callable

from z3 import *
from trace import *

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
        self.is_immediate = Bool(f"{id}_is_immediate")
        self.bit_length = BitVec(f"{id}_bitsize", 16)

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
        s.add(Implies(Or(And(Not(self.memory), self.type == "GP_REGISTER_HWORD"), self.type == "IMMEDIATE64"),
                      self.bit_length == 8))

        # ...

        s.add(Implies(Or(*(self.type == r for r in ["IMMEDIATE8", "IMMEDIATE16", "IMMEDIATE32", "IMMEDIATE64"])),
                      And(self.register == "rax", self.is_immediate)))

        s.add(Implies(Or(*(self.type == r for r in
                           ["GP_REGISTER_QWORD", "GP_REGISTER_DWORD", "GP_REGISTER_WORD", "GP_REGISTER_HWORD"])),
                      And(self.immediate == 0, Not(self.is_immediate))))


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
        # for address2, _ in processor_state.memory.items():
        #    if address < address2 < (address + 8):
        #        b = True
        #        break
        # if b:
        #    continue
        b = BitVec(f"{id}_{hex(address)}", 64)
        memory[address] = b
        s.add(b == value)

    return ProcessorConstraints(regs, {}, memory)


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
]


class InstructionParameters:
    def __init__(self, s: Solver, id, pre: ProcessorState, post: ProcessorState, mnemonic, operands):
        self.s: Solver = s
        self.id = f"{id}"
        self.pre_absolute: ProcessorState = pre
        self.post_absolute: ProcessorState = post
        self.pre: ProcessorConstraints = init_registers(s, pre, f"{id}_pre")
        self.post: ProcessorConstraints = init_registers(s, post, f"{id}_post")
        self.mnemonic = mnemonic
        s.add(Or(*([mnemonic == m for m in mnemonics])))
        self.instruction_size = BitVec(f"{id}_instrucion_size", 64)
        s.add(self.instruction_size == self.post.regs["rip"] - self.pre.regs["rip"])
        self.operands: list[Operand] = operands


operation_sub = lambda dest, src: dest - src


def model_flag_adjustment(p: InstructionParameters, o_dest, o_src, width_dest, width_src, operation):
    o_src_ext = SignExt(width_dest - width_src, o_src)
    return And(
        (p.post.regs["zf"] == 1) == (operation(o_dest, o_src_ext) == 0),
        (p.post.regs["sf"] == 1) == ((operation(o_dest, o_src_ext) & (1 << (width_dest - 1))) > 0)
    )
    # Other flags are not modeled for now



def model_mov(p: InstructionParameters):
    # Does not consider memory operands with displacement
    p.s.add(Implies(p.mnemonic == "MOV",
                    And(p.operands[0].used, p.operands[1].used, Not(p.operands[2].used), p.operands[3].used)))

    p.s.add(Implies(And(p.mnemonic == "MOV", p.operands[0].is_immediate),
                    p.instruction_size >= ZeroExt(48, (p.operands[0].bit_length >> 3) + 2)))

    # Constrain operand types
    p.s.add(Implies(p.mnemonic == "MOV", Not(p.operands[1].is_immediate)))

    # Destination is register
    p.s.add(Implies(And(p.mnemonic == "MOV", Not(p.operands[1].memory)), And(
        # Source is immediate
        And(*(
            Implies(p.operands[0].type == f"IMMEDIATE{width}", Or(*(
                And(p.post.regs[s] == Extract(width - 1, 0, p.operands[0].immediate),
                    p.pre.regs[s] != p.post.regs[s],  # TODO Remove
                    p.operands[1].register == s)
                for s in filter(lambda n: n != ip, names)
            )))
            for width, names, ip in [
            (64, qword_reg_names, "rip"),
            (32, dword_reg_names, "eip"),
            (16, word_reg_names, "ip"),
            (8, hword_reg_names, ""),
        ])),

        # Source is a register
        And(*(Implies(And(p.operands[0].type == reg_type, Not(p.operands[0].memory)), And(
            p.operands[1].type == reg_type,
            Or(*(
                Or(*(
                    And(
                        p.post.regs[dest] == p.pre.regs[src],
                        p.post.regs[dest] != p.pre.regs[dest],  # Todo: remove
                        p.operands[0].register == src,
                        p.operands[1].register == dest,
                    )
                    for src in filter(lambda r: r != "rip", names)
                ))
                for dest in filter(lambda r: r != "rip", names)
            ))
        )) for reg_type, names in [
                  ("GP_REGISTER_QWORD", list(filter(lambda r: r != "rip", qword_reg_names))),
                  ("GP_REGISTER_DWORD", list(filter(lambda r: r != "eip", dword_reg_names))),
                  ("GP_REGISTER_WORD", list(filter(lambda r: r != "ip", word_reg_names))),
                  ("GP_REGISTER_HWORD", hword_reg_names),
              ]
              )),

        # Source is in memory
        Implies(p.operands[0].memory, p.operands[0].type == "GP_REGISTER_QWORD"),
        And(*(Implies(And(p.operands[1].type == reg_type, p.operands[0].memory), And(
            p.operands[0].type == "GP_REGISTER_QWORD",
            Or(*(
                Or(*(
                    And(
                        src != dest,  # Todo: remove
                        (p.post.regs[dest] == Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[src]])) if
                        p.pre_absolute.regs[src] in p.pre.memory else False,
                        p.post.regs[dest] != p.pre.regs[dest],  # Todo: remove
                        p.operands[0].bit_length == width,
                        p.operands[0].register == src,
                        p.operands[1].register == dest,
                    )
                    for src in list(filter(lambda r: r != "rip", qword_reg_names))
                ))
                for dest in names
            ))
        )) for reg_type, width, names in [
                  ("GP_REGISTER_QWORD", 64, list(filter(lambda r: r != "rip", qword_reg_names))),
                  ("GP_REGISTER_DWORD", 32, list(filter(lambda r: r != "eip", dword_reg_names))),
                  ("GP_REGISTER_WORD", 16, list(filter(lambda r: r != "ip", word_reg_names))),
                  ("GP_REGISTER_HWORD", 8, hword_reg_names),
              ]
              )),
    )))

    # Destination is memory
    p.s.add(Implies(And(p.mnemonic == "MOV", p.operands[1].memory), And(
        # Source cannot be memory, destination is indicated by a qword register
        Not(p.operands[0].memory),
        p.operands[1].type == "GP_REGISTER_QWORD",

        # Source is immediate
        And(*(
            Implies(p.operands[0].type == f"IMMEDIATE{width}",
                    Or(*(
                        And(
                            p.operands[1].register == register,
                            p.operands[1].bit_length == width,
                            Extract(width - 1, 0, p.post.memory[address]) != Extract(width - 1, 0,
                                                                                     p.pre.memory[address]),
                            # TODO Remove
                            Extract(width - 1, 0, p.post.memory[address]) == Extract(width - 1, 0,
                                                                                     p.operands[0].immediate)
                        )
                        for register, address in list(filter(
                        lambda item: item[1] in p.pre.memory.keys() and item[1] in p.post.memory.keys() and item[
                            0] != "rip",
                        p.pre_absolute.regs.items()))
                    )))
            for width in [8, 16, 32, 64]
        )),

        # Source is register
        And(*(Implies(p.operands[0].type == reg_type,
                      Or(*(
                          Or(*(
                              And(
                                  (p.pre.regs[src] == Extract(width - 1, 0, p.post.memory[p.pre_absolute.regs[dest]]) if
                                   p.pre_absolute.regs[dest] in p.post.memory else False),
                                  (((Extract(width - 1, 0, p.post.memory[p.pre_absolute.regs[dest]]))
                                    != Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[dest]])) if
                                   p.pre_absolute.regs[dest] in p.post.memory and p.pre_absolute.regs[
                                       dest] in p.pre.memory
                                   else False),  # Todo: remove
                                  (Extract(63, width, p.pre.memory[p.pre_absolute.regs[dest]]) == Extract(63, width,
                                                                                                          p.post.memory[
                                                                                                              p.pre_absolute.regs[
                                                                                                                  dest]]) if
                                   p.pre_absolute.regs[dest] in p.post.memory else False) if width < 64 else True,
                                  (p.pre.regs[src] == (p.post_absolute.memory[p.post_absolute.regs[dest]]) if
                                   p.post_absolute.regs[dest] in p.post.memory else False),

                                  p.operands[1].bit_length == width,
                                  p.operands[0].register == src,
                                  p.operands[1].register == dest,

                              )
                              for src in names
                          )) for dest in list(filter(lambda r: r != "rip", qword_reg_names))
                      ))
                      ) for reg_type, width, names in [
                  ("GP_REGISTER_QWORD", 64, list(filter(lambda r: r != "rip", qword_reg_names))),
                  ("GP_REGISTER_DWORD", 32, list(filter(lambda r: r != "eip", dword_reg_names))),
                  ("GP_REGISTER_WORD", 16, list(filter(lambda r: r != "ip", word_reg_names))),
                  ("GP_REGISTER_HWORD", 8, hword_reg_names)
              ]
              )),
    )))

    # All registers that are not the destination register must stay the same
    for n in filter(lambda r: r != "rip", qword_reg_names + ["eflags"]):
        p.s.add(Implies(p.mnemonic == "MOV",
                        Implies(Not(And(p.operands[1].register == n, Not(p.operands[1].memory))),
                                p.post.regs[n] == p.pre.regs[n])
                        ))


def model_add(p: InstructionParameters):
    # Does not consider memory operands with displacement
    # We do not consider add operations with 0, as this does not constrain the model enough. We handle this case in NOP

    # Does not consider memory operands with displacement
    # We do not consider add operations with 0, as this does not constrain the model enough. We handle this case in NOP

    p.s.add(Implies(p.mnemonic == "ADD", And(p.instruction_size > 2, p.instruction_size <= 8, p.instruction_size != 5)))
    p.s.add(Implies(p.mnemonic == "ADD",
                    And(p.operands[0].used, p.operands[1].used, Not(p.operands[2].used), p.operands[3].used)))

    p.s.add(Implies(And(p.mnemonic == "ADD", p.operands[0].is_immediate),
                    p.instruction_size >= ZeroExt(48, (p.operands[0].bit_length >> 3) + 2)))

    # Constrain operand types
    p.s.add(
        Implies(p.mnemonic == "ADD", And(Not(p.operands[0].type == "IMMEDIATE64"), Not(p.operands[1].is_immediate))))

    # Destination is register
    p.s.add(Implies(And(p.mnemonic == "ADD", Not(p.operands[1].memory)), And(
        # Source is immediate
        Implies(p.operands[0].type == "IMMEDIATE32", Or(
            Or(*(
                And(p.post.regs[s] == p.pre.regs[s] + Extract(31, 0, p.operands[0].immediate),
                    p.operands[0].immediate != 0,
                    p.operands[1].register == s,
                    model_flag_adjustment(p, p.pre.regs[s], Extract(31, 0, p.operands[0].immediate), 32, 32,
                                          lambda dest, src: dest + src)
                    )
                for s in filter(lambda n: n != "eip", dword_reg_names))),
            Or(*(
                And(p.post.regs[s] == p.pre.regs[s] + p.operands[0].immediate,
                    p.operands[0].immediate != 0,
                    p.operands[1].register == s,
                    model_flag_adjustment(p, p.pre.regs[s], p.operands[0].immediate, 64, 64,
                                          lambda dest, src: dest + src)
                    )
                for s in filter(lambda n: n != "rip", qword_reg_names)))
        )),
        Implies(p.operands[0].type == "IMMEDIATE16", Or(*(
            And(p.post.regs[s] == p.pre.regs[s] + Extract(15, 0, p.operands[0].immediate),
                Extract(15, 0, p.operands[0].immediate) != 0,
                p.operands[1].register == s,
                model_flag_adjustment(p, p.pre.regs[s], Extract(15, 0, p.operands[0].immediate), 16, 16,
                                      lambda dest, src: dest + src)
                )
            for s in filter(lambda n: n != "ip", word_reg_names)
        ))),
        Implies(p.operands[0].type == "IMMEDIATE8", Or(
            Or(*(
                And(p.post.regs[s] == p.pre.regs[s] + Extract(7, 0, p.operands[0].immediate),
                    Extract(7, 0, p.operands[0].immediate) != 0,
                    p.operands[1].register == s,
                    model_flag_adjustment(p, p.pre.regs[s], Extract(7, 0, p.operands[0].immediate), 8, 8,
                                          lambda dest, src: dest + src)
                    )
                for s in hword_reg_names)),
            Or(*(
                And(p.post.regs[s] == p.pre.regs[s] + p.operands[0].immediate,
                    p.operands[0].immediate != 0,
                    p.operands[1].register == s,
                    model_flag_adjustment(p, p.pre.regs[s], p.operands[0].immediate, 64, 64,
                                          lambda dest, src: dest + src)
                    )
                for s in filter(lambda n: n != "rip", qword_reg_names)))
        )),

        # Source is a register
        And(*(Implies(And(p.operands[0].type == reg_type, Not(p.operands[0].memory)), And(
            p.operands[1].type == reg_type,
            Or(*(
                Or(*(
                    And(
                        p.post.regs[dest] == p.pre.regs[dest] + p.pre.regs[src],
                        p.post.regs[dest] != p.pre.regs[dest],  # Todo: remove
                        p.operands[0].register == src,
                        p.operands[1].register == dest,
                        model_flag_adjustment(p, p.pre.regs[dest], p.pre.regs[src], width, width,
                                              lambda dest, src: dest + src),
                    )
                    for src in filter(lambda r: r != "rip", names)
                ))
                for dest in filter(lambda r: r != "rip", names)
            ))
        )) for reg_type, width, names in [
                  ("GP_REGISTER_QWORD", 64, list(filter(lambda r: r != "rip", qword_reg_names))),
                  ("GP_REGISTER_DWORD", 32, list(filter(lambda r: r != "eip", dword_reg_names))),
                  ("GP_REGISTER_WORD", 16, list(filter(lambda r: r != "ip", word_reg_names))),
                  ("GP_REGISTER_HWORD", 8, hword_reg_names),
              ]
              )),

        # Source is in memory
        Implies(p.operands[0].memory, p.operands[0].type == "GP_REGISTER_QWORD"),
        And(*(Implies(And(p.operands[1].type == reg_type, p.operands[0].memory), And(
            p.operands[0].type == "GP_REGISTER_QWORD",
            Or(*(
                Or(*(
                    And(
                        src != dest,  # Todo: remove
                        (p.post.regs[dest] == p.pre.regs[dest] + Extract(width - 1, 0,
                                                                         p.pre.memory[p.pre_absolute.regs[src]])) if
                        p.pre_absolute.regs[src] in p.pre.memory else False,
                        p.post.regs[dest] != p.pre.regs[dest],  # Todo: remove
                        p.operands[0].bit_length == width,
                        p.operands[0].register == src,
                        p.operands[1].register == dest,
                        model_flag_adjustment(p, p.pre.regs[dest],
                                              Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[src]]), width,
                                              width,
                                              lambda dest, src: dest + src)
                        if p.pre_absolute.regs[src] in p.pre.memory else False
                    )
                    for src in list(filter(lambda r: r != "rip", qword_reg_names))
                ))
                for dest in names
            ))
        )) for reg_type, width, names in [
                  ("GP_REGISTER_QWORD", 64, list(filter(lambda r: r != "rip", qword_reg_names))),
                  ("GP_REGISTER_DWORD", 32, list(filter(lambda r: r != "eip", dword_reg_names))),
                  ("GP_REGISTER_WORD", 16, list(filter(lambda r: r != "ip", word_reg_names))),
                  ("GP_REGISTER_HWORD", 8, hword_reg_names),
              ]
              )),
    )))

    # Destination is memory
    p.s.add(Implies(And(p.mnemonic == "ADD", p.operands[1].memory), And(
        # Source cannot be memory, destination is indicated by a qword register
        Not(p.operands[0].memory),
        p.operands[1].type == "GP_REGISTER_QWORD",

        # Source is immediate
        And(*(
            Implies(p.operands[0].type == f"IMMEDIATE{width}",
                    Or(*(
                        And(
                            p.operands[1].register == register,
                            p.operands[1].bit_length == width,
                            Extract(width - 1, 0, p.post.memory[address]) != Extract(width - 1, 0,
                                                                                     p.pre.memory[address]),
                            # TODO Remove
                            Extract(width - 1, 0, p.post.memory[address])
                            == Extract(width - 1, 0, p.pre.memory[address]) + Extract(width - 1, 0,
                                                                                      p.operands[0].immediate),
                            model_flag_adjustment(p, Extract(width - 1, 0, p.pre.memory[address]),
                                                  Extract(width - 1, 0, p.operands[0].immediate), width, width,
                                                  lambda dest, src: dest + src),
                        )
                        for register, address in list(filter(
                        lambda item: item[1] in p.pre.memory.keys() and item[1] in p.post.memory.keys() and item[
                            0] != "rip",
                        p.pre_absolute.regs.items()))
                    )))
            for width in [8, 16, 32, 64]
        )),

        # Source is register
        And(*(Implies(p.operands[0].type == reg_type,
                      Or(*(
                          Or(*(
                              And(
                                  (Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[dest]])
                                   + p.pre.regs[src] == Extract(width - 1, 0,
                                                                p.post.memory[p.pre_absolute.regs[dest]]) if
                                   p.pre_absolute.regs[dest] in p.post.memory else False),
                                  (((Extract(width - 1, 0, p.post.memory[p.pre_absolute.regs[dest]]))
                                    != Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[dest]])) if
                                   p.pre_absolute.regs[dest] in p.post.memory and p.pre_absolute.regs[
                                       dest] in p.pre.memory
                                   else False),  # Todo: remove
                                  (Extract(63, width, p.pre.memory[p.pre_absolute.regs[dest]]) == Extract(63, width,
                                                                                                          p.post.memory[
                                                                                                              p.pre_absolute.regs[
                                                                                                                  dest]]) if
                                   p.pre_absolute.regs[dest] in p.post.memory else False) if width < 64 else True,
                                  (p.pre.regs[src] == (p.post_absolute.memory[p.post_absolute.regs[dest]]) if
                                   p.post_absolute.regs[dest] in p.post.memory else False),

                                  p.operands[1].bit_length == width,
                                  p.operands[0].register == src,
                                  p.operands[1].register == dest,

                                  model_flag_adjustment(p,
                                                        Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[dest]]),
                                                        p.pre.regs[src], width, width, lambda dest, src: dest + src) if
                                  p.pre_absolute.regs[dest] in p.post.memory and p.pre_absolute.regs[
                                      dest] in p.pre.memory else False,
                              )
                              for src in names
                          )) for dest in list(filter(lambda r: r != "rip", qword_reg_names))
                      ))
                      ) for reg_type, width, names in [
                  ("GP_REGISTER_QWORD", 64, list(filter(lambda r: r != "rip", qword_reg_names))),
                  ("GP_REGISTER_DWORD", 32, list(filter(lambda r: r != "eip", dword_reg_names))),
                  ("GP_REGISTER_WORD", 16, list(filter(lambda r: r != "ip", word_reg_names))),
                  ("GP_REGISTER_HWORD", 8, hword_reg_names)
              ]
              )),
    )))

    # All registers that are not the destination register must stay the same
    for n in list(filter(lambda r: r != "rip", qword_reg_names)):
        p.s.add(Implies(p.mnemonic == "ADD",
                        Implies(Not(And(p.operands[1].register == n, Not(p.operands[1].memory))),
                                p.post.regs[n] == p.pre.regs[n])
                        ))

    # TODO: Model Flags


def model_sub(p: InstructionParameters):
    # Does not consider memory operands with displacement
    # We do not consider add operations with 0, as this does not constrain the model enough. We handle this case in NOP

    p.s.add(Implies(p.mnemonic == "SUB", And(p.instruction_size > 2, p.instruction_size <= 8, p.instruction_size != 5)))
    p.s.add(Implies(p.mnemonic == "SUB",
                    And(p.operands[0].used, p.operands[1].used, Not(p.operands[2].used), p.operands[3].used)))

    p.s.add(Implies(And(p.mnemonic == "SUB", p.operands[0].is_immediate),
                    p.instruction_size >= ZeroExt(48, (p.operands[0].bit_length >> 3) + 2)))

    # Constrain operand types
    p.s.add(
        Implies(p.mnemonic == "SUB", And(Not(p.operands[0].type == "IMMEDIATE64"), Not(p.operands[1].is_immediate))))

    # Destination is register
    p.s.add(Implies(And(p.mnemonic == "SUB", Not(p.operands[1].memory)), And(
        # Source is immediate
        Implies(p.operands[0].type == "IMMEDIATE32", Or(
            Or(*(
                And(p.post.regs[s] == p.pre.regs[s] - Extract(31, 0, p.operands[0].immediate),
                    p.operands[0].immediate != 0,
                    p.operands[1].register == s,
                    model_flag_adjustment(p, p.pre.regs[s], Extract(31, 0, p.operands[0].immediate), 32, 32,
                                          lambda dest, src: dest - src)
                    )
                for s in filter(lambda n: n != "eip", dword_reg_names))),
            Or(*(
                And(p.post.regs[s] == p.pre.regs[s] - p.operands[0].immediate,
                    p.operands[0].immediate != 0,
                    p.operands[1].register == s,
                    model_flag_adjustment(p, p.pre.regs[s], p.operands[0].immediate, 64, 64,
                                          lambda dest, src: dest - src)
                    )
                for s in filter(lambda n: n != "rip", qword_reg_names)))
        )),
        Implies(p.operands[0].type == "IMMEDIATE16", Or(*(
            And(p.post.regs[s] == p.pre.regs[s] - Extract(15, 0, p.operands[0].immediate),
                Extract(15, 0, p.operands[0].immediate) != 0,
                p.operands[1].register == s,
                model_flag_adjustment(p, p.pre.regs[s], Extract(15, 0, p.operands[0].immediate), 16, 16,
                                      lambda dest, src: dest - src)
                )
            for s in filter(lambda n: n != "ip", word_reg_names)
        ))),
        Implies(p.operands[0].type == "IMMEDIATE8", Or(
            Or(*(
                And(p.post.regs[s] == p.pre.regs[s] - Extract(7, 0, p.operands[0].immediate),
                    Extract(7, 0, p.operands[0].immediate) != 0,
                    p.operands[1].register == s,
                    model_flag_adjustment(p, p.pre.regs[s], Extract(7, 0, p.operands[0].immediate), 8, 8,
                                          lambda dest, src: dest - src)
                    )
                for s in hword_reg_names)),
            Or(*(
                And(p.post.regs[s] == p.pre.regs[s] - p.operands[0].immediate,
                    p.operands[0].immediate != 0,
                    p.operands[1].register == s,
                    model_flag_adjustment(p, p.pre.regs[s], p.operands[0].immediate, 64, 64,
                                          lambda dest, src: dest - src)
                    )
                for s in filter(lambda n: n != "rip", qword_reg_names)))
        )),

        # Source is a register
        And(*(Implies(And(p.operands[0].type == reg_type, Not(p.operands[0].memory)), And(
            p.operands[1].type == reg_type,
            Or(*(
                Or(*(
                    And(
                        p.post.regs[dest] == p.pre.regs[dest] - p.pre.regs[src],
                        p.post.regs[dest] != p.pre.regs[dest],  # Todo: remove
                        p.operands[0].register == src,
                        p.operands[1].register == dest,
                        model_flag_adjustment(p, p.pre.regs[dest], p.pre.regs[src], width, width,
                                              lambda dest, src: dest - src),
                    )
                    for src in filter(lambda r: r != "rip", names)
                ))
                for dest in filter(lambda r: r != "rip", names)
            ))
        )) for reg_type, width, names in [
                  ("GP_REGISTER_QWORD", 64, list(filter(lambda r: r != "rip", qword_reg_names))),
                  ("GP_REGISTER_DWORD", 32, list(filter(lambda r: r != "eip", dword_reg_names))),
                  ("GP_REGISTER_WORD", 16, list(filter(lambda r: r != "ip", word_reg_names))),
                  ("GP_REGISTER_HWORD", 8, hword_reg_names),
              ]
        )),

        # Source is in memory
        Implies(p.operands[0].memory, p.operands[0].type == "GP_REGISTER_QWORD"),
        And(*(Implies(And(p.operands[1].type == reg_type, p.operands[0].memory), And(
            p.operands[0].type == "GP_REGISTER_QWORD",
            Or(*(
                Or(*(
                    And(
                        src != dest,  # Todo: remove
                        (p.post.regs[dest] == p.pre.regs[dest] - Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[src]])) if
                        p.pre_absolute.regs[src] in p.pre.memory else False,
                        p.post.regs[dest] != p.pre.regs[dest],  # Todo: remove
                        p.operands[0].bit_length == width,
                        p.operands[0].register == src,
                        p.operands[1].register == dest,
                        model_flag_adjustment(p, p.pre.regs[dest], Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[src]]), width, width,
                                              lambda dest, src: dest - src)
                        if p.pre_absolute.regs[src] in p.pre.memory else False
                    )
                    for src in list(filter(lambda r: r != "rip", qword_reg_names))
                ))
                for dest in names
            ))
        )) for reg_type, width, names in [
                  ("GP_REGISTER_QWORD", 64, list(filter(lambda r: r != "rip", qword_reg_names))),
                  ("GP_REGISTER_DWORD", 32, list(filter(lambda r: r != "eip", dword_reg_names))),
                  ("GP_REGISTER_WORD", 16, list(filter(lambda r: r != "ip", word_reg_names))),
                  ("GP_REGISTER_HWORD", 8, hword_reg_names),
              ]
        )),
    )))

    # Destination is memory
    p.s.add(Implies(And(p.mnemonic == "SUB", p.operands[1].memory), And(
        # Source cannot be memory, destination is indicated by a qword register
        Not(p.operands[0].memory),
        p.operands[1].type == "GP_REGISTER_QWORD",

        # Source is immediate
        And(*(
            Implies(p.operands[0].type == f"IMMEDIATE{width}",
                    Or(*(
                        And(
                            p.operands[1].register == register,
                            p.operands[1].bit_length == width,
                            Extract(width - 1, 0, p.post.memory[address]) != Extract(width - 1, 0,
                                                                                     p.pre.memory[address]),
                            # TODO Remove
                            Extract(width - 1, 0, p.post.memory[address])
                            == Extract(width - 1, 0, p.pre.memory[address]) - Extract(width - 1, 0,
                                                                                      p.operands[0].immediate),
                            model_flag_adjustment(p, Extract(width - 1, 0, p.pre.memory[address]),
                                                  Extract(width - 1, 0, p.operands[0].immediate), width, width,
                                                  lambda dest, src: dest - src),
                        )
                        for register, address in list(filter(
                        lambda item: item[1] in p.pre.memory.keys() and item[1] in p.post.memory.keys() and item[
                            0] != "rip",
                        p.pre_absolute.regs.items()))
                    )))
            for width in [8, 16, 32, 64]
        )),

        # Source is register
        And(*(Implies(p.operands[0].type == reg_type,
                  Or(*(
                      Or(*(
                          And(
                              (Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[dest]])
                               - p.pre.regs[src] == Extract(width - 1, 0, p.post.memory[p.pre_absolute.regs[dest]]) if
                               p.pre_absolute.regs[dest] in p.post.memory else False),
                              (((Extract(width - 1, 0, p.post.memory[p.pre_absolute.regs[dest]]))
                                != Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[dest]])) if
                               p.pre_absolute.regs[dest] in p.post.memory and p.pre_absolute.regs[
                                   dest] in p.pre.memory
                               else False),  # Todo: remove
                              (Extract(63, width, p.pre.memory[p.pre_absolute.regs[dest]]) == Extract(63, width,
                                                                                                      p.post.memory[
                                                                                                          p.pre_absolute.regs[
                                                                                                              dest]]) if
                               p.pre_absolute.regs[dest] in p.post.memory else False) if width < 64 else True,
                              (p.pre.regs[src] == (p.post_absolute.memory[p.post_absolute.regs[dest]]) if
                               p.post_absolute.regs[dest] in p.post.memory else False),

                              p.operands[1].bit_length == width,
                              p.operands[0].register == src,
                              p.operands[1].register == dest,

                              model_flag_adjustment(p, Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[dest]]),
                                                               p.pre.regs[src], width, width, lambda dest, src: dest - src) if
                               p.pre_absolute.regs[dest] in p.post.memory and p.pre_absolute.regs[
                                   dest] in p.pre.memory else False,
                          )
                          for src in names
                      )) for dest in list(filter(lambda r: r != "rip", qword_reg_names))
                  ))
                  ) for reg_type, width, names in [
              ("GP_REGISTER_QWORD", 64, list(filter(lambda r: r != "rip", qword_reg_names))),
              ("GP_REGISTER_DWORD", 32, list(filter(lambda r: r != "eip", dword_reg_names))),
              ("GP_REGISTER_WORD", 16, list(filter(lambda r: r != "ip", word_reg_names))),
              ("GP_REGISTER_HWORD", 8, hword_reg_names)
          ]
        )),
    )))

    # All registers that are not the destination register must stay the same
    for n in list(filter(lambda r: r != "rip", qword_reg_names)):
        p.s.add(Implies(p.mnemonic == "SUB",
                        Implies(Not(And(p.operands[1].register == n, Not(p.operands[1].memory))),
                                p.post.regs[n] == p.pre.regs[n])
                        ))


def model_cmp(p: InstructionParameters):
    # Does not consider memory operands with displacement
    # We do not consider add operations with 0, as this does not constrain the model enough. We handle this case in NOP

    p.s.add(Implies(p.mnemonic == "CMP", And(p.instruction_size > 2, p.instruction_size <= 8, p.instruction_size != 5)))
    p.s.add(Implies(p.mnemonic == "CMP",
                    And(p.operands[0].used, p.operands[1].used, Not(p.operands[2].used), p.operands[3].used)))

    p.s.add(Implies(And(p.mnemonic == "CMP", p.operands[0].is_immediate),
                    p.instruction_size >= ZeroExt(48, (p.operands[0].bit_length >> 3) + 2)))

    # Constrain operand types
    p.s.add(
        Implies(p.mnemonic == "CMP", And(Not(p.operands[0].type == "IMMEDIATE64"), Not(p.operands[1].is_immediate))))

    # Destination is register
    p.s.add(Implies(And(p.mnemonic == "CMP", Not(p.operands[1].memory)), And(
        # Source is immediate
        Implies(p.operands[0].type == "IMMEDIATE32", Or(
            Or(*(
                And(
                    p.operands[1].register == s,
                    model_flag_adjustment(p, p.pre.regs[s], Extract(31, 0, p.operands[0].immediate), 32, 32,
                                          lambda dest, src: dest - src)
                    )
                for s in filter(lambda n: n != "eip", dword_reg_names))),
            Or(*(
                And(
                    p.operands[1].register == s,
                    model_flag_adjustment(p, p.pre.regs[s], p.operands[0].immediate, 64, 64,
                                          lambda dest, src: dest - src)
                    )
                for s in filter(lambda n: n != "rip", qword_reg_names)))
        )),
        Implies(p.operands[0].type == "IMMEDIATE16", Or(*(
            And(
                p.operands[1].register == s,
                model_flag_adjustment(p, p.pre.regs[s], Extract(15, 0, p.operands[0].immediate), 16, 16,
                                      lambda dest, src: dest - src)
                )
            for s in filter(lambda n: n != "ip", word_reg_names)
        ))),
        Implies(p.operands[0].type == "IMMEDIATE8", Or(
            Or(*(
                And(
                    p.operands[1].register == s,
                    model_flag_adjustment(p, p.pre.regs[s], Extract(7, 0, p.operands[0].immediate), 8, 8,
                                          lambda dest, src: dest - src)
                    )
                for s in hword_reg_names)),
            Or(*(
                And(
                    p.operands[1].register == s,
                    model_flag_adjustment(p, p.pre.regs[s], p.operands[0].immediate, 64, 64,
                                          lambda dest, src: dest - src)
                    )
                for s in filter(lambda n: n != "rip", qword_reg_names)))
        )),

        # Source is a register
        And(*(Implies(And(p.operands[0].type == reg_type, Not(p.operands[0].memory)), And(
            p.operands[1].type == reg_type,
            Or(*(
                Or(*(
                    And(
                        p.operands[0].register == src,
                        p.operands[1].register == dest,
                        model_flag_adjustment(p, p.pre.regs[dest], p.pre.regs[src], width, width,
                                              lambda dest, src: dest - src),
                    )
                    for src in filter(lambda r: r != "rip", names)
                ))
                for dest in filter(lambda r: r != "rip", names)
            ))
        )) for reg_type, width, names in [
                  ("GP_REGISTER_QWORD", 64, list(filter(lambda r: r != "rip", qword_reg_names))),
                  ("GP_REGISTER_DWORD", 32, list(filter(lambda r: r != "eip", dword_reg_names))),
                  ("GP_REGISTER_WORD", 16, list(filter(lambda r: r != "ip", word_reg_names))),
                  ("GP_REGISTER_HWORD", 8, hword_reg_names),
              ]
        )),

        # Source is in memory
        Implies(p.operands[0].memory, p.operands[0].type == "GP_REGISTER_QWORD"),
        And(*(Implies(And(p.operands[1].type == reg_type, p.operands[0].memory), And(
            p.operands[0].type == "GP_REGISTER_QWORD",
            Or(*(
                Or(*(
                    And(
                        p.operands[0].bit_length == width,
                        p.operands[0].register == src,
                        p.operands[1].register == dest,
                        model_flag_adjustment(p, p.pre.regs[dest], Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[src]]), width, width,
                                              lambda dest, src: dest - src)
                        if p.pre_absolute.regs[src] in p.pre.memory else False
                    )
                    for src in list(filter(lambda r: r != "rip", qword_reg_names))
                ))
                for dest in names
            ))
        )) for reg_type, width, names in [
                  ("GP_REGISTER_QWORD", 64, list(filter(lambda r: r != "rip", qword_reg_names))),
                  ("GP_REGISTER_DWORD", 32, list(filter(lambda r: r != "eip", dword_reg_names))),
                  ("GP_REGISTER_WORD", 16, list(filter(lambda r: r != "ip", word_reg_names))),
                  ("GP_REGISTER_HWORD", 8, hword_reg_names),
              ]
        )),
    )))

    # Destination is memory
    p.s.add(Implies(And(p.mnemonic == "CMP", p.operands[1].memory), And(
        # Source cannot be memory, destination is indicated by a qword register
        Not(p.operands[0].memory),
        p.operands[1].type == "GP_REGISTER_QWORD",

        # Source is immediate
        And(*(
            Implies(p.operands[0].type == f"IMMEDIATE{width}",
                    Or(*(
                        And(
                            p.operands[1].register == register,
                            model_flag_adjustment(p, Extract(width - 1, 0, p.pre.memory[address]),
                                                  Extract(width - 1, 0, p.operands[0].immediate), width, width,
                                                  lambda dest, src: dest - src),
                        )
                        for register, address in list(filter(
                        lambda item: item[1] in p.pre.memory.keys() and item[1] in p.post.memory.keys() and item[
                            0] != "rip",
                        p.pre_absolute.regs.items()))
                    )))
            for width in [8, 16, 32, 64]
        )),

        # Source is register
        And(*(Implies(p.operands[0].type == reg_type,
                  Or(*(
                      Or(*(
                          And(
                              p.operands[1].bit_length == width,
                              p.operands[0].register == src,
                              p.operands[1].register == dest,

                              model_flag_adjustment(p, Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[dest]]),
                                                               p.pre.regs[src], width, width, lambda dest, src: dest - src) if
                               p.pre_absolute.regs[dest] in p.post.memory and p.pre_absolute.regs[
                                   dest] in p.pre.memory else False,
                          )
                          for src in names
                      )) for dest in list(filter(lambda r: r != "rip", qword_reg_names))
                  ))
                  ) for reg_type, width, names in [
              ("GP_REGISTER_QWORD", 64, list(filter(lambda r: r != "rip", qword_reg_names))),
              ("GP_REGISTER_DWORD", 32, list(filter(lambda r: r != "eip", dword_reg_names))),
              ("GP_REGISTER_WORD", 16, list(filter(lambda r: r != "ip", word_reg_names))),
              ("GP_REGISTER_HWORD", 8, hword_reg_names)
          ]
        )),
    )))

    # All registers except for eflags must stay the same
    for n in list(filter(lambda r: r != "rip", qword_reg_names)):
        p.s.add(Implies(p.mnemonic == "CMP", p.post_absolute.regs[n] == p.pre_absolute.regs[n]))

    for address, value in p.pre_absolute.memory.items():
        if address in p.post_absolute.memory.keys():
            p.s.add(Implies(p.mnemonic == "CMP", value == p.post_absolute.memory[address]))


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


_one = BitVec("__one", 8)


def model_dec(p: InstructionParameters):
    p.s.add(Implies(p.mnemonic == "DEC", And(p.operands[0].used, Not(p.operands[0].is_immediate))))
    for o in p.operands[1:]:
        p.s.add(Implies(p.mnemonic == "DEC", Not(o.used)))
    p.s.add(Implies(p.mnemonic == "DEC", p.instruction_size <= 3))

    # Destination is a register
    p.s.add(Implies(And(p.mnemonic == "DEC", Not(p.operands[0].memory)),
        And(*(
            Implies(p.operands[0].type == type_name,
                    Or(*(
                        And(p.post.regs[dest] == p.pre.regs[dest] - 1,
                            p.operands[0].register == dest,
                            model_flag_adjustment(p, p.pre.regs[dest], _one,
                                                  width, 8,
                                                  lambda dest, src: dest - src)
                            )
                        for dest in name_list
                    ))
                    ) for type_name, width, name_list in [
            ("GP_REGISTER_QWORD", 64, list(filter(lambda n: n != "rip", qword_reg_names))),
            ("GP_REGISTER_DWORD", 32, list(filter(lambda n: n != "eip", dword_reg_names))),
            ("GP_REGISTER_WORD", 16, list(filter(lambda n: n != "ip", word_reg_names))),
            ("GP_REGISTER_HWORD", 8, hword_reg_names)]
        ))
    ))

    # Destination is in memory
    p.s.add(Implies(And(p.mnemonic == "DEC", p.operands[0].memory), And(
        p.operands[0].type == "GP_REGISTER_QWORD",
        And(*(
            Implies(p.operands[0].bit_length == width,
                    Or(*(
                        And(
                            p.operands[0].register == register,
                            Extract(width - 1, 0, p.post.memory[address]) == Extract(width - 1, 0,
                                                                                     p.pre.memory[address]) - 1,
                            model_flag_adjustment(p, Extract(width - 1, 0, p.pre.memory[address]), _one, width, 8,
                                                  lambda dest, src: dest - src)
                        )
                        for register, address in list(filter(
                        lambda item: item[1] in p.pre.memory.keys() and item[1] in p.post.memory.keys() and item[
                            0] != "rip",
                        p.pre_absolute.regs.items()))
                    )))
            for width in [8, 16, 32, 64]
        )),
    )))

    # All registers that are not the destination register must stay the same
    for n in list(filter(lambda r: r != "rip", qword_reg_names)):
        p.s.add(Implies(p.mnemonic == "DEC",
                        Implies(Not(And(p.operands[0].register == n, Not(p.operands[0].memory))),
                                p.post.regs[n] == p.pre.regs[n])))


def model_inc(p: InstructionParameters):
    p.s.add(Implies(p.mnemonic == "INC", And(p.operands[0].used, Not(p.operands[0].is_immediate))))
    for o in p.operands[1:]:
        p.s.add(Implies(p.mnemonic == "INC", Not(o.used)))
    p.s.add(Implies(p.mnemonic == "INC", p.instruction_size <= 3))

    # Destination is a register
    p.s.add(Implies(And(p.mnemonic == "INC", Not(p.operands[0].memory)),
        And(*(
            Implies(p.operands[0].type == type_name,
                    Or(*(
                        And(p.post.regs[dest] == p.pre.regs[dest] + 1,
                            p.operands[0].register == dest,
                            model_flag_adjustment(p, p.pre.regs[dest], _one,
                                                  width, 8,
                                                  lambda dest, src: dest + src)
                            )
                        for dest in name_list
                    ))
                    ) for type_name, width, name_list in [
            ("GP_REGISTER_QWORD", 64, list(filter(lambda n: n != "rip", qword_reg_names))),
            ("GP_REGISTER_DWORD", 32, list(filter(lambda n: n != "eip", dword_reg_names))),
            ("GP_REGISTER_WORD", 16, list(filter(lambda n: n != "ip", word_reg_names))),
            ("GP_REGISTER_HWORD", 8, hword_reg_names)]
        ))
    ))

    # Destination is in memory
    p.s.add(Implies(And(p.mnemonic == "INC", p.operands[0].memory), And(
        p.operands[0].type == "GP_REGISTER_QWORD",
        And(*(
            Implies(p.operands[0].bit_length == width,
                    Or(*(
                        And(
                            p.operands[0].register == register,
                            Extract(width - 1, 0, p.post.memory[address]) == Extract(width - 1, 0,
                                                                                     p.pre.memory[address]) + 1,
                            model_flag_adjustment(p, Extract(width - 1, 0, p.pre.memory[address]), _one, width, 8,
                                                  lambda dest, src: dest + src)
                        )
                        for register, address in list(filter(
                        lambda item: item[1] in p.pre.memory.keys() and item[1] in p.post.memory.keys() and item[
                            0] != "rip",
                        p.pre_absolute.regs.items()))
                    )))
            for width in [8, 16, 32, 64]
        )),
    )))

    # All registers that are not the destination register must stay the same
    for n in list(filter(lambda r: r != "rip", qword_reg_names)):
        p.s.add(Implies(p.mnemonic == "INC",
                        Implies(Not(And(p.operands[0].register == n, Not(p.operands[0].memory))),
                                p.post.regs[n] == p.pre.regs[n])))


def model_jump(p: InstructionParameters, mn: str, taken):

    p.s.add(Implies(p.mnemonic == mn, p.operands[0].used))
    for o in p.operands[2:]:
        p.s.add(Implies(p.mnemonic == mn, Not(o.used)))

    # All registers, including eflags, must stay the same
    for n in qword_reg_names + ["eflags"]:
        if n not in ["rip"]:
            p.s.add(Implies(p.mnemonic == mn, p.post.regs[n] == p.pre.regs[n]))

    # Memory remains unchanged
    for address, value in p.pre_absolute.memory.items():
        if address in p.post_absolute.memory.keys():
            p.s.add(Implies(p.mnemonic == mn, value == p.post_absolute.memory[address]))


    p.s.add(Implies(p.mnemonic == mn,
                    Or(p.operands[0].type == "IMMEDIATE32", p.operands[0].type == "GP_REGISTER_QWORD")))


    # Near relative call
    p.s.add(Implies(And(p.mnemonic == mn, p.operands[0].type == "IMMEDIATE32", taken), And(
        p.post_absolute.regs["rip"] == (p.pre_absolute.regs["rip"] + SignExt(32, Extract(31, 0,
                                                                                                                 p.operands[
                                                                                                                     0].immediate))),
        Not(p.operands[0].memory),
        Not(p.operands[1].used)
    )))


    # Absolute address in register
    p.s.add(
        Implies(And(p.mnemonic == mn, p.operands[0].type == "GP_REGISTER_QWORD", Not(p.operands[0].memory), taken), And(
            Or(*(
                And(p.operands[0].register == s, p.post_absolute.regs["rip"] == p.pre_absolute.regs[s])
                for s in qword_reg_names
            )),
            Not(p.operands[1].used)
        )))

    # Absolute address in memory, no displacement
    p.s.add(Implies(And(p.mnemonic == mn, p.operands[0].type == "GP_REGISTER_QWORD", p.operands[0].memory,
                        Not(p.operands[1].used), taken),
                    Or(*(
                        And(p.operands[0].register == s,
                            (p.post_absolute.regs["rip"] == p.pre_absolute.memory[p.pre_absolute.regs[s]])) if
                        p.pre_absolute.regs[s] in p.pre_absolute.memory else False
                        for s in qword_reg_names
                    ))
                    ))

    p.s.add(Implies(And(p.mnemonic == mn, p.operands[0].type == "GP_REGISTER_QWORD", p.operands[0].memory,
                        p.operands[1].used, taken), And(
        p.operands[1].type == "IMMEDIATE32",
        Not(p.operands[1].memory),
        Or(*(And(p.operands[0].register == s,
                 (SignExt(32, Extract(31, 0, p.operands[1].immediate)) + p.pre_absolute.memory[
                     p.pre_absolute.regs[s]] == p.post_absolute.regs["rip"])
                 if p.pre_absolute.regs[s] in p.pre_absolute.memory else False)
             for s in qword_reg_names
             ))
    )))

    p.s.add(Implies(And(p.mnemonic == mn, Not(taken)), And(
        p.post.regs["rip"] > p.pre.regs["rip"],
        p.instruction_size <= 6,
    )))

def model_jmp(p: InstructionParameters):
    model_jump(p, "JMP", True)

def model_jg(p: InstructionParameters):
    jg_taken = Bool(f"{p.id}_jg_taken")
    p.s.add(jg_taken == And(p.pre.regs["zf"] == 0 and p.pre.regs["sf"] == 0))
    model_jump(p, "JG", jg_taken)

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


def init_solver(instruction_address):
    plausible = list()
    for mnemonic_str, model in [
        ("ADD", model_add),
        ("RET", model_ret),
        ("CALL", model_call),
        ("SUB", model_sub),
        ("DEC",  model_dec),
        ("INC", model_inc),
        ("MOV", model_mov),
        ("JMP", model_jmp),
        ("JG", model_jg),
        ("CMP", model_cmp),
    ]:
        solver = Solver()

        solver.add(_one == 1)

        instruction_mnemonic = String(f"{instruction_address}_mnemonic")
        instruction_operands = [Operand(solver, f"{instruction_address}_operand_{n}") for n in range(4)]

        solver.add(instruction_mnemonic == mnemonic_str)

        for i in range(100):
            if victim_register_trace[i].regs["rip"] != instruction_address:
                continue
            p = InstructionParameters(solver, i, victim_register_trace[i], victim_register_trace[i+1],
                                      instruction_mnemonic, instruction_operands)
            model(p)
            if i % 50 == 0:
                if solver.check() == unsat:
                    break

        if solver.check() == sat:
            instr = f"{solver.model()[instruction_mnemonic]}".replace("\"", "")
            op_strs = list()
            for i in range(4):
                if not solver.model()[instruction_operands[i].used]:
                    break
                if solver.model()[instruction_operands[i].is_immediate]:
                    op_strs.append(str(hex(int(f"{solver.model()[instruction_operands[i].immediate]}"))))
                else:
                    op_strs.append(f"{solver.model()[instruction_operands[i].register]}".replace("\"", ""))
                if solver.model()[instruction_operands[i].memory]:
                    op_strs[i] = f"({op_strs[i]})"
            plausible.append(f"{instr} {','.join(op_strs)}")

    if len(plausible) > 0:
        print(f"{hex(instruction_address)}: {plausible[0]}        (one of {len(plausible)} alternatives)")
    else:
        print(f"{hex(instruction_address)}: unsat")

if __name__ == "__main__":
    instruction_addresses = set()
    for state in victim_register_trace:
        instruction_addresses.add(state.regs["rip"])
    for addr in sorted(instruction_addresses):
        if addr >= 0x550000000000:
            break
        init_solver(addr)

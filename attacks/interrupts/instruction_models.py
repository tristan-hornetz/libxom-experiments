from z3 import *
from execution_environment import *

one_ = BitVec("__one", 8)
operation_sub = lambda dest, src: dest - src

def model_flag_adjustment(p: InstructionParameters, o_dest, o_src, width_dest, width_src, operation):
    o_src_ext = SignExt(width_dest - width_src, o_src)

    of_src = ZeroExt(1, o_src_ext)
    of_dest = ZeroExt(1, o_dest)

    return And(
        (p.post.regs["zf"] == 1) == (operation(o_dest, o_src_ext) == 0),
        p.post.regs["sf"] == Extract(width_dest - 1, width_dest - 1, operation(o_dest, o_src_ext)),
        p.post.regs["of"] == Extract(0, 0,
                                     ((of_src ^ operation(of_dest, of_src)) & (of_dest ^ operation(of_dest, of_src))) >> width_dest
                                     ),
    )
    # Only these flags are modeled for now, as these are the only flags with an impact on jg
    # The others could be useful for add/sub, but the current model has sufficient information to tell
    # them apart in the POC code


def model_lea(p: InstructionParameters):
    p.s.add(Implies(p.mnemonic == "LEA",
                    And(*(o.used for o in p.operands))))

    # Constrain operand types
    p.s.add(Implies(p.mnemonic == "LEA", And(Not(p.operands[0].is_immediate), p.operands[0].memory,
                                             Not(p.operands[1].is_immediate), Not(p.operands[1].memory))))

    p.s.add(Implies(p.mnemonic == "LEA", And(p.pre.regs["rip"] < p.post.regs["rip"],
                                             p.delta_rip <= 0xc)))
    if not p.is_last_instruction:
         p.s.add(Implies(p.mnemonic == "LEA", p.delta_rip == p.next_instruction - p.pre_absolute.regs["rip"]))

    p.s.add(Implies(p.mnemonic == "LEA", p.delta_rip >= 4))
    p.s.add(Implies(And(p.mnemonic == "LEA",
                        p.operands[0].displacement > 0x100, p.operands[0].displacement < 0xffffff00), p.delta_rip >= 8))
    
    p.s.add(Implies(p.mnemonic == "LEA", Or(*(
        Or(*(
           Or(*(
               Or(*(
                   And(
                       p.post_absolute.regs[dest_register] ==
                        p.pre_absolute.regs[base_register] + (p.pre_absolute.regs[index_register] * (2**scale))
                        + SignExt(32, p.operands[0].displacement),
                       p.operands[0].index_register == index_register,
                       p.operands[0].scale_factor == scale,
                       p.operands[0].register == base_register,
                       p.operands[1].register == dest_register
                   ) for dest_register in qword_reg_names_norip
               )) for base_register in qword_reg_names_norip
           )) for scale in range(4)
        )) for index_register in qword_reg_names_norip
    ))))

    # All registers that are not the destination register must stay the same
    for n in filter(lambda r: r != "rip", qword_reg_names + ["eflags"]):
        p.s.add(Implies(p.mnemonic == "LEA",
                        Implies(Not(And(p.operands[1].register == n, Not(p.operands[1].memory))),
                                p.post_absolute.regs[n] == p.pre_absolute.regs[n])
                        ))

    # All memory locations that are not the destination remain unchanged
    for address in p.post_absolute.memory.keys():
        if address not in p.pre_absolute.memory.keys():
            continue
        for r in qword_reg_names_norip:
            p.s.add(Implies(p.mnemonic == "LEA", Or(
                And(p.operands[1].memory, p.operands[1].register == r, p.pre_absolute.regs[r] == address),
                (p.pre_absolute.memory[address] == p.post_absolute.memory[address])
            )))


def model_mov(p: InstructionParameters):
    # Does not consider memory operands with displacement or scale factors
    p.s.add(Implies(p.mnemonic == "MOV",
                    And(p.operands[0].used, p.operands[1].used)))

    p.s.add(Implies(p.mnemonic == "MOV",
                    And(*(Not(o.used) for o in p.operands[2:]))))

    # Constrain operand types
    p.s.add(Implies(p.mnemonic == "MOV", Not(p.operands[1].is_immediate)))

    p.s.add(Implies(p.mnemonic == "MOV", Or(*(
        (p.operands[1].register == n)
         for n in qword_reg_names_norip + dword_reg_names_noeip + word_reg_names_noip + hword_reg_names
    ))))

    p.s.add(Implies(p.mnemonic == "MOV", And(p.pre.regs["rip"] < p.post.regs["rip"],
                                             p.delta_rip <= 0xc)))
    if not p.is_last_instruction:
         p.s.add(Implies(p.mnemonic == "MOV", p.delta_rip == p.next_instruction - p.pre_absolute.regs["rip"]))
    

    # Destination is register
    p.s.add(Implies(And(p.mnemonic == "MOV", Not(p.operands[1].memory)), And(
        # Source is immediate
        And(*(
            Implies(p.operands[0].type == f"IMMEDIATE{width}", Or(*(
                And(p.post.regs[s] == Extract(width - 1, 0, p.operands[0].immediate),
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
            p.delta_rip <= 4,
            Or(*(
                Or(*(
                    And(
                        p.post.regs[dest] == p.pre.regs[src],
                        p.operands[0].register == src,
                        p.operands[1].register == dest,
                    )
                    for src in names
                ))
                for dest in names
            ))
        )) for reg_type, names in [
                  ("GP_REGISTER_QWORD", qword_reg_names_norip),
                  ("GP_REGISTER_DWORD", dword_reg_names_noeip),
                  ("GP_REGISTER_WORD", word_reg_names_noip),
                  ("GP_REGISTER_HWORD", hword_reg_names),
              ]
              )),

        # Source is in memory
        Implies(p.operands[0].memory, p.operands[0].type == "GP_REGISTER_QWORD"),
        And(*(Implies(And(p.operands[1].type == reg_type, p.operands[0].memory), And(
            p.operands[0].type == "GP_REGISTER_QWORD",
            p.delta_rip <= 4,
            Or(*(
                Or(*(
                    And(
                        (p.post.regs[dest] == Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[src]])) if
                        p.pre_absolute.regs[src] in p.pre.memory else False,
                        p.operands[0].bit_length == width,
                        p.operands[0].register == src,
                        p.operands[1].register == dest,
                    )
                    for src in qword_reg_names_norip
                ))
                for dest in names
            ))
        )) for reg_type, width, names in [
                  ("GP_REGISTER_QWORD", 64, qword_reg_names_norip),
                  ("GP_REGISTER_DWORD", 32, dword_reg_names_noeip),
                  ("GP_REGISTER_WORD", 16, word_reg_names_noip),
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
                            Extract(width - 1, 0, p.post.memory[p.pre_absolute.regs[register]]) ==
                            Extract(width - 1, 0, p.operands[0].immediate),
                            (Extract(63, width, p.pre.memory[p.pre_absolute.regs[register]]) ==
                            Extract(63, width, p.post.memory[p.pre_absolute.regs[register]]))
                            if width < 64 else True,
                        )
                        for register in list(filter(
                            lambda r: p.pre_absolute.regs[r] in p.pre_absolute.memory.keys()
                                and p.pre_absolute.regs[r] in p.post_absolute.memory.keys(),
                            qword_reg_names_norip
                        ))
                    )))
            for width in [64, 32, 16, 8]
        )),

        # Source is register
        And(*(Implies(p.operands[0].type == reg_type, And(
            p.delta_rip <= 4,
            Or(*(
                Or(*(
                    And(
                        p.pre.regs[src] == Extract(width - 1, 0, p.post.memory[p.pre_absolute.regs[dest]]),
                        (Extract(63, width, p.pre.memory[p.pre_absolute.regs[dest]]) ==
                            Extract(63, width, p.post.memory[p.pre_absolute.regs[dest]])) if width < 64 else True,
                        p.operands[1].bit_length == width,
                        p.operands[0].register == src,
                        p.operands[1].register == dest,
                    )
                    for src in names
                )) for dest in list(filter(lambda d: p.pre_absolute.regs[d] in p.pre_absolute.memory.keys()
                                           and p.pre_absolute.regs[d] in p.post_absolute.memory.keys(), qword_reg_names_norip))
            )))
                      ) for reg_type, width, names in [
                  ("GP_REGISTER_QWORD", 64, qword_reg_names_norip),
                  ("GP_REGISTER_DWORD", 32, dword_reg_names_noeip),
                  ("GP_REGISTER_WORD", 16, word_reg_names_noip),
                  ("GP_REGISTER_HWORD", 8, hword_reg_names)
              ]
              )),
    )))

    # All registers that are not the destination register must stay the same
    p.s.add(Implies(p.mnemonic == "MOV", And(*(
        Or(
            And(Not(p.operands[1].memory), p.operands[1].register == n),
            p.pre_absolute.regs[n] == p.post_absolute.regs[n]
        )
        for n in qword_reg_names_norip + ["eflags"]
    ))))

    # All memory locations that are not the destination remain unchanged
    for address in p.post_absolute.memory.keys():
        if address not in p.pre_absolute.memory.keys():
            continue

        p.s.add(Implies(p.mnemonic == "MOV", Or(*(Or(
            And(p.operands[1].memory, p.operands[1].register == r, abs(address - p.pre_absolute.regs[r]) <= 16),
            p.pre_absolute.memory[address] == p.post_absolute.memory[address],
        ) for r in qword_reg_names_norip
    ))))


def model_add(p: InstructionParameters):
    # Does not consider memory operands with displacement or scale factors
    # We do not consider add operations with 0, as this does not constrain the model enough. We handle this case in NOP

    # Does not consider memory operands with displacement or scale factors
    # We do not consider add operations with 0, as this does not constrain the model enough. We handle this case in NOP

    p.s.add(Implies(p.mnemonic == "ADD", And(p.delta_rip > 2, p.delta_rip <= 8, p.delta_rip != 5)))
    p.s.add(Implies(p.mnemonic == "ADD",
                    And(p.operands[0].used, p.operands[1].used)))
    p.s.add(Implies(p.mnemonic == "ADD",
                    And(*(Not(o.used) for o in p.operands[2:]))))

    p.s.add(Implies(And(p.mnemonic == "ADD", p.operands[0].is_immediate),
                    p.delta_rip >= ZeroExt(48, (p.operands[0].bit_length >> 3) + 2)))

    p.s.add(Implies(p.mnemonic == "ADD", And(p.pre.regs["rip"] < p.post.regs["rip"],
                                             p.delta_rip <= 0xc)))
    if not p.is_last_instruction:
         p.s.add(Implies(p.mnemonic == "ADD", p.delta_rip == p.next_instruction - p.pre_absolute.regs["rip"]))

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
                        Extract(width - 1, 0, p.post.regs[dest]) == Extract(width - 1, 0,
                                                                            p.pre.regs[dest] + p.pre.regs[src]),
                        p.operands[0].register == src,
                        p.operands[1].register == dest,
                        model_flag_adjustment(p, p.pre.regs[dest], p.pre.regs[src], width, width,
                                              lambda dest, src: dest + src),
                    )
                    for src in names
                ))
                for dest in names
            ))
        )) for reg_type, width, names in [
                  ("GP_REGISTER_QWORD", 64, qword_reg_names_norip),
                  ("GP_REGISTER_DWORD", 32, dword_reg_names_noeip),
                  ("GP_REGISTER_WORD", 16, word_reg_names_noip),
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
                        (p.post.regs[dest] == p.pre.regs[dest] + Extract(width - 1, 0,
                                                                         p.pre.memory[p.pre_absolute.regs[src]])),
                        p.operands[0].bit_length == width,
                        p.operands[0].register == src,
                        p.operands[1].register == dest,
                        model_flag_adjustment(p, p.pre.regs[dest],
                                              Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[src]]), width,
                                              width,
                                              lambda dest, src: dest + src)

                    )
                    for src in
                list(filter(lambda s: p.pre_absolute.regs[s] in p.pre.memory.keys(), qword_reg_names_norip))
                ))
                for dest in names
            ))
        )) for reg_type, width, names in [
                  ("GP_REGISTER_QWORD", 64, qword_reg_names_norip),
                  ("GP_REGISTER_DWORD", 32, dword_reg_names_noeip),
                  ("GP_REGISTER_WORD", 16, word_reg_names_noip),
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
                                  Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[dest]]) + p.pre.regs[src]
                                  == Extract(width - 1, 0, p.post.memory[p.pre_absolute.regs[dest]]),
                                  Extract(63, width, p.pre.memory[p.pre_absolute.regs[dest]]) ==
                                  Extract(63, width, p.post.memory[p.pre_absolute.regs[dest]])
                                  if width < 64 else True,
                                  p.operands[1].bit_length == width,
                                  p.operands[0].register == src,
                                  p.operands[1].register == dest,

                                  model_flag_adjustment(p,
                                                        Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[dest]]),
                                                        p.pre.regs[src], width, width, lambda dest, src: dest + src),
                              )
                              for src in names
                          )) for dest in list(filter(lambda s: p.pre_absolute.regs[s] in p.post.memory.keys() and
                                                               p.pre_absolute.regs[s] in p.pre.memory.keys(),
                                                     qword_reg_names_norip))
                      ))
                      ) for reg_type, width, names in [
                  ("GP_REGISTER_QWORD", 64, qword_reg_names_norip),
                  ("GP_REGISTER_DWORD", 32, dword_reg_names_noeip),
                  ("GP_REGISTER_WORD", 16, word_reg_names_noip),
                  ("GP_REGISTER_HWORD", 8, hword_reg_names)
              ]
              )),
    )))

    # All registers that are not the destination register must stay the same
    p.s.add(Implies(p.mnemonic == "ADD", And(*(
        Or(
            And(Not(p.operands[1].memory), p.operands[1].register == n),
            p.pre_absolute.regs[n] == p.post_absolute.regs[n]
        )
        for n in qword_reg_names_norip
    ))))

    # All memory locations that are not the destination remain unchanged
    for address in p.post_absolute.memory.keys():
        if address not in p.pre_absolute.memory.keys():
            continue

        p.s.add(Implies(p.mnemonic == "ADD", Or(*(Or(
            And(p.operands[1].memory, p.operands[1].register == r, abs(address - p.pre_absolute.regs[r]) < 8),
            p.pre_absolute.memory[address] == p.post_absolute.memory[address],
        ) for r in qword_reg_names_norip
        ))))


def model_sub(p: InstructionParameters):
    # Does not consider memory operands with displacement or scale factors
    # We do not consider add operations with 0, as this does not constrain the model enough. We handle this case in NOP

    p.s.add(Implies(p.mnemonic == "SUB", And(p.delta_rip > 2, p.delta_rip <= 8, p.delta_rip != 5)))
    p.s.add(Implies(p.mnemonic == "SUB",
                    And(p.operands[0].used, p.operands[1].used)))
    p.s.add(Implies(p.mnemonic == "SUB",
                    And(*(Not(o.used) for o in p.operands[2:]))))

    p.s.add(Implies(And(p.mnemonic == "SUB", p.operands[0].is_immediate),
                    p.delta_rip >= ZeroExt(48, (p.operands[0].bit_length >> 3) + 2)))

    p.s.add(Implies(p.mnemonic == "SUB", And(p.pre.regs["rip"] < p.post.regs["rip"],
                                             p.delta_rip <= 0xc)))
    if not p.is_last_instruction:
         p.s.add(Implies(p.mnemonic == "SUB", p.delta_rip == p.next_instruction - p.pre_absolute.regs["rip"]))

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
                for s in qword_reg_names_norip))
        )),

        # Source is a register
        And(*(Implies(And(p.operands[0].type == reg_type, Not(p.operands[0].memory)), And(
            p.operands[1].type == reg_type,
            Or(*(
                Or(*(
                    And(
                        p.post.regs[dest] == p.pre.regs[dest] - p.pre.regs[src],
                        p.operands[0].register == src,
                        p.operands[1].register == dest,
                        model_flag_adjustment(p, p.pre.regs[dest], p.pre.regs[src], width, width,
                                              lambda dest, src: dest - src),
                    )
                    for src in names
                ))
                for dest in names
            ))
        )) for reg_type, width, names in [
                  ("GP_REGISTER_QWORD", 64, qword_reg_names_norip),
                  ("GP_REGISTER_DWORD", 32, dword_reg_names_noeip),
                  ("GP_REGISTER_WORD", 16, word_reg_names_noip),
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
                        (p.post.regs[dest] == p.pre.regs[dest] - Extract(width - 1, 0,
                                                                         p.pre.memory[p.pre_absolute.regs[src]])) if
                        p.pre_absolute.regs[src] in p.pre.memory else False,
                        p.operands[0].bit_length == width,
                        p.operands[0].register == src,
                        p.operands[1].register == dest,
                        model_flag_adjustment(p, p.pre.regs[dest],
                                              Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[src]]), width,
                                              width,
                                              lambda dest, src: dest - src)
                        if p.pre_absolute.regs[src] in p.pre.memory else False
                    )
                    for src in qword_reg_names_norip
                ))
                for dest in names
            ))
        )) for reg_type, width, names in [
                  ("GP_REGISTER_QWORD", 64, qword_reg_names_norip),
                  ("GP_REGISTER_DWORD", 32, dword_reg_names_noeip),
                  ("GP_REGISTER_WORD", 16, word_reg_names_noip),
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
                                  Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[dest]])
                                   - p.pre.regs[src] == Extract(width - 1, 0,
                                                                p.post.memory[p.pre_absolute.regs[dest]]),
                                  (Extract(63, width, p.pre.memory[p.pre_absolute.regs[dest]]) ==
                                   Extract(63, width,p.post.memory[p.pre_absolute.regs[dest]]))
                                  if width < 64 else True,
                                  p.pre.regs[src] == (p.post_absolute.memory[p.pre_absolute.regs[dest]]),

                                  p.operands[1].bit_length == width,
                                  p.operands[0].register == src,
                                  p.operands[1].register == dest,

                                  model_flag_adjustment(p, Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[dest]]),
                                                        p.pre.regs[src], width, width, lambda dest, src: dest - src),
                              )
                              for src in names
                          )) for dest in list(filter(lambda s: p.pre_absolute.regs[s] in p.post.memory.keys() and
                                                               p.pre_absolute.regs[s] in p.pre.memory.keys(),
                                                     qword_reg_names_norip))
                      ))
                      ) for reg_type, width, names in [
                  ("GP_REGISTER_QWORD", 64, qword_reg_names_norip),
                  ("GP_REGISTER_DWORD", 32, dword_reg_names_noeip),
                  ("GP_REGISTER_WORD", 16, word_reg_names_noip),
                  ("GP_REGISTER_HWORD", 8, hword_reg_names)
              ]
              )),
    )))

    # All registers that are not the destination register must stay the same
    p.s.add(Implies(p.mnemonic == "SUB", And(*(
        Or(
            And(Not(p.operands[1].memory), p.operands[1].register == n),
            p.pre_absolute.regs[n] == p.post_absolute.regs[n]
        )
        for n in qword_reg_names_norip
    ))))

    # All memory locations that are not the destination remain unchanged
    for address in p.post_absolute.memory.keys():
        if address not in p.pre_absolute.memory.keys():
            continue

        p.s.add(Implies(p.mnemonic == "SUB", Or(*(Or(
            And(p.operands[1].memory, p.operands[1].register == r, abs(address - p.pre_absolute.regs[r]) < 8),
            p.pre_absolute.memory[address] == p.post_absolute.memory[address],
        ) for r in qword_reg_names_norip
        ))))


def model_cmp(p: InstructionParameters):
    # Does not consider memory operands with displacement or scale factors
    # We do not consider add operations with 0, as this does not constrain the model enough. We handle this case in NOP

    p.s.add(Implies(p.mnemonic == "CMP", And(p.delta_rip > 2, p.delta_rip <= 8, p.delta_rip != 5)))
    p.s.add(Implies(p.mnemonic == "CMP",
                    And(p.operands[0].used, p.operands[1].used)))
    p.s.add(Implies(p.mnemonic == "CMP",
                    And(*(Not(o.used) for o in p.operands[2:]))))

    p.s.add(Implies(And(p.mnemonic == "CMP", p.operands[0].is_immediate),
                    p.delta_rip >= ZeroExt(48, (p.operands[0].bit_length >> 3) + 2)))

    p.s.add(Implies(p.mnemonic == "CMP", And(p.pre.regs["rip"] < p.post.regs["rip"],
                                             p.delta_rip <= 0xc)))
    if not p.is_last_instruction:
         p.s.add(Implies(p.mnemonic == "CMP", p.delta_rip == p.next_instruction - p.pre_absolute.regs["rip"]))

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
                for s in dword_reg_names_noeip)),
            Or(*(
                And(
                    p.operands[1].register == s,
                    model_flag_adjustment(p, p.pre.regs[s], p.operands[0].immediate, 64, 64,
                                          lambda dest, src: dest - src)
                )
                for s in qword_reg_names_norip))
        )),
        Implies(p.operands[0].type == "IMMEDIATE16", Or(*(
            And(
                p.operands[1].register == s,
                model_flag_adjustment(p, p.pre.regs[s], Extract(15, 0, p.operands[0].immediate), 16, 16,
                                      lambda dest, src: dest - src)
            )
            for s in word_reg_names_noip
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
                for s in qword_reg_names_norip))
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
                    for src in names
                ))
                for dest in names
            ))
        )) for reg_type, width, names in [
                  ("GP_REGISTER_QWORD", 64, qword_reg_names_norip),
                  ("GP_REGISTER_DWORD", 32, dword_reg_names_noeip),
                  ("GP_REGISTER_WORD", 16, word_reg_names_noip),
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
                        model_flag_adjustment(p, p.pre.regs[dest],
                                              Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[src]]), width,
                                              width,
                                              lambda dest, src: dest - src)
                        if p.pre_absolute.regs[src] in p.pre.memory else False
                    )
                    for src in qword_reg_names_norip
                ))
                for dest in names
            ))
        )) for reg_type, width, names in [
                  ("GP_REGISTER_QWORD", 64, qword_reg_names_norip),
                  ("GP_REGISTER_DWORD", 32, dword_reg_names_noeip),
                  ("GP_REGISTER_WORD", 16, word_reg_names_noip),
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

                                  model_flag_adjustment(p,
                                                        Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[dest]]),
                                                        p.pre.regs[src], width, width, lambda dest, src: dest - src) if
                                  p.pre_absolute.regs[dest] in p.post.memory and p.pre_absolute.regs[
                                      dest] in p.pre.memory else False,
                              )
                              for src in names
                          )) for dest in qword_reg_names_norip
                      ))
                      ) for reg_type, width, names in [
                  ("GP_REGISTER_QWORD", 64, qword_reg_names_norip),
                  ("GP_REGISTER_DWORD", 32, dword_reg_names_noeip),
                  ("GP_REGISTER_WORD", 16, word_reg_names_noip),
                  ("GP_REGISTER_HWORD", 8, hword_reg_names)
              ]
              )),
    )))

    # All registers except for eflags must stay the same
    for n in qword_reg_names_norip:
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

def model_dec(p: InstructionParameters):
    p.s.add(Implies(p.mnemonic == "DEC", And(p.operands[0].used, Not(p.operands[0].is_immediate))))
    for o in p.operands[1:]:
        p.s.add(Implies(p.mnemonic == "DEC", Not(o.used)))
    p.s.add(Implies(p.mnemonic == "DEC", p.delta_rip <= 3))

    p.s.add(Implies(p.mnemonic == "DEC", And(p.pre.regs["rip"] < p.post.regs["rip"],
                                             p.delta_rip <= 0xc)))
    if not p.is_last_instruction:
         p.s.add(Implies(p.mnemonic == "DEC", p.delta_rip == p.next_instruction - p.pre_absolute.regs["rip"]))

    # Destination is a register
    p.s.add(Implies(And(p.mnemonic == "DEC", Not(p.operands[0].memory)),
                    And(*(
                        Implies(p.operands[0].type == type_name,
                                Or(*(
                                    And(p.post.regs[dest] == p.pre.regs[dest] - 1,
                                        p.operands[0].register == dest,
                                        model_flag_adjustment(p, p.pre.regs[dest], one_,
                                                              width, 8,
                                                              lambda dest, src: dest - src)
                                        )
                                    for dest in name_list
                                ))
                                ) for type_name, width, name_list in [
                        ("GP_REGISTER_QWORD", 64, qword_reg_names_norip),
                        ("GP_REGISTER_DWORD", 32, dword_reg_names_noeip),
                        ("GP_REGISTER_WORD", 16, word_reg_names_noip),
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
                            model_flag_adjustment(p, Extract(width - 1, 0, p.pre.memory[address]), one_, width, 8,
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
    p.s.add(Implies(p.mnemonic == "DEC", And(*(
        Or(
            And(Not(p.operands[0].memory), p.operands[0].register == n),
            p.pre_absolute.regs[n] == p.post_absolute.regs[n]
        )
        for n in qword_reg_names_norip
    ))))

    # All memory locations that are not the destination remain unchanged
    for address in p.post_absolute.memory.keys():
        if address not in p.pre_absolute.memory.keys():
            continue

        p.s.add(Implies(p.mnemonic == "DEC", Or(*(Or(
            And(p.operands[0].memory, p.operands[0].register == r, abs(address - p.pre_absolute.regs[r]) < 8),
            p.pre_absolute.memory[address] == p.post_absolute.memory[address],
        ) for r in qword_reg_names_norip
        ))))


def model_inc(p: InstructionParameters):
    p.s.add(Implies(p.mnemonic == "INC", And(p.operands[0].used, Not(p.operands[0].is_immediate))))
    for o in p.operands[1:]:
        p.s.add(Implies(p.mnemonic == "INC", Not(o.used)))
    p.s.add(Implies(p.mnemonic == "INC", p.delta_rip <= 3))

    p.s.add(Implies(p.mnemonic == "INC", And(p.pre.regs["rip"] < p.post.regs["rip"],
                                             p.delta_rip <= 0xc)))
    if not p.is_last_instruction:
         p.s.add(Implies(p.mnemonic == "INC", p.delta_rip == p.next_instruction - p.pre_absolute.regs["rip"]))

    # Destination is a register
    p.s.add(Implies(And(p.mnemonic == "INC", Not(p.operands[0].memory)),
                    And(*(
                        Implies(p.operands[0].type == type_name,
                                Or(*(
                                    And(p.post.regs[dest] == p.pre.regs[dest] + 1,
                                        p.operands[0].register == dest,
                                        model_flag_adjustment(p, p.pre.regs[dest], one_,
                                                              width, 8,
                                                              lambda dest, src: dest + src)
                                        )
                                    for dest in name_list
                                ))
                                ) for type_name, width, name_list in [
                        ("GP_REGISTER_QWORD", 64, qword_reg_names_norip),
                        ("GP_REGISTER_DWORD", 32, dword_reg_names_noeip),
                        ("GP_REGISTER_WORD", 16, word_reg_names_noip),
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
                            model_flag_adjustment(p, Extract(width - 1, 0, p.pre.memory[address]), one_, width, 8,
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
    p.s.add(Implies(p.mnemonic == "INC", And(*(
        Or(
            And(Not(p.operands[0].memory), p.operands[0].register == n),
            p.pre_absolute.regs[n] == p.post_absolute.regs[n]
        )
        for n in qword_reg_names_norip
    ))))

    # All memory locations that are not the destination remain unchanged
    for address in p.post_absolute.memory.keys():
        if address not in p.pre_absolute.memory.keys():
            continue

    p.s.add(Implies(p.mnemonic == "INC", Or(*(Or(
        And(p.operands[0].memory, p.operands[0].register == r, abs(address - p.pre_absolute.regs[r]) < 8),
        p.pre_absolute.memory[address] == p.post_absolute.memory[address],
    ) for r in qword_reg_names_norip
    ))))


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

    p.s.add(Implies(And(p.mnemonic == mn, p.operands[0].memory), p.operands[0].bit_length == 64))

    # Near relative call
    p.s.add(Implies(And(p.mnemonic == mn, p.operands[0].type == "IMMEDIATE32", taken), And(
        p.post_absolute.regs["rip"] == (p.pre_absolute.regs["rip"]
                                        + ((p.next_instruction - p.pre_absolute.regs["rip"])
                                            if not p.is_last_instruction else 0)
                                        + SignExt(32, Extract(31, 0, p.operands[0].immediate))),
        p.operands[0].immediate != 0,
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
        (p.next_instruction - p.pre_absolute.regs["rip"] >= 3) if not p.is_last_instruction else True,
        Or(*(And(p.operands[0].register == s,
                 (SignExt(32, Extract(31, 0, p.operands[1].immediate)) + p.pre_absolute.memory[
                     p.pre_absolute.regs[s]] == p.post_absolute.regs["rip"])
                 if p.pre_absolute.regs[s] in p.pre_absolute.memory else False)
             for s in qword_reg_names
             ))
    )))

    p.s.add(Implies(And(p.mnemonic == mn, Not(taken)), And(
        p.post.regs["rip"] > p.pre.regs["rip"],
        p.delta_rip <= 6,
    )))
    if not p.is_last_instruction:
        p.s.add(Implies(And(p.mnemonic == mn, Not(taken)),
                        p.delta_rip == p.next_instruction - p.pre_absolute.regs["rip"]
                        ))


def model_jmp(p: InstructionParameters):
    model_jump(p, "JMP", True)


def model_jg(p: InstructionParameters):
    jg_taken = Bool(f"{p.id}_jg_taken")
    p.s.add(jg_taken == And(p.pre.regs["zf"] == 0, p.pre.regs["sf"] == p.pre.regs["of"]))
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

def model_xchg(p: InstructionParameters):
    # Does not consider memory operands with displacement or scale factors
    p.s.add(Implies(p.mnemonic == "XCHG",
                    And(p.operands[0].used, p.operands[1].used)))

    p.s.add(Implies(p.mnemonic == "XCHG",
                    And(*(Not(o.used) for o in p.operands[2:]))))

    # Constrain operand types
    p.s.add(Implies(p.mnemonic == "XCHG", And(
        Not(p.operands[0].is_immediate),
            Not(p.operands[1].is_immediate),
            Not(p.operands[0].memory)
    )))

    p.s.add(Implies(p.mnemonic == "XCHG", Not(Or(*(
        Or(o.register == "rip",
        o.register == "eip",
        o.register == "ip")
        for o in p.operands
    )))))

    p.s.add(Implies(p.mnemonic == "XCHG", And(p.pre.regs["rip"] < p.post.regs["rip"],
                                             p.delta_rip <= 0xc)))
    if not p.is_last_instruction:
         p.s.add(Implies(p.mnemonic == "XCHG", p.delta_rip == p.next_instruction - p.pre_absolute.regs["rip"]))

    # Destination is register
    p.s.add(Implies(And(p.mnemonic == "XCHG", Not(p.operands[1].memory)), And(
        # Source is a register
        And(*(Implies(And(p.operands[0].type == reg_type, Not(p.operands[0].memory)), And(
            p.operands[1].type == reg_type,
            p.delta_rip <= 4,
            Or(*(
                Or(*(
                    And(
                        p.post.regs[src] == p.pre.regs[dest],
                        p.post.regs[dest] == p.pre.regs[src],
                        p.operands[0].register == src,
                        p.operands[1].register == dest,
                    )
                    for src in names
                ))
                for dest in names
            ))
        )) for reg_type, names in [
                  ("GP_REGISTER_QWORD", qword_reg_names_norip),
                  ("GP_REGISTER_DWORD", dword_reg_names_noeip),
                  ("GP_REGISTER_WORD", word_reg_names_noip),
                  ("GP_REGISTER_HWORD", hword_reg_names),
              ]
              )),
    )))

    # Destination is memory
    p.s.add(Implies(And(p.mnemonic == "XCHG", p.operands[1].memory), And(
        p.operands[1].type == "GP_REGISTER_QWORD",
        # Source is register
        And(*(Implies(p.operands[0].type == reg_type, And(
            p.delta_rip <= 4,
            Or(*(
                Or(*(
                    And(
                        p.pre.regs[src] == Extract(width - 1, 0, p.post.memory[p.pre_absolute.regs[dest]]),
                        p.post.regs[src] == Extract(width - 1, 0, p.pre.memory[p.pre_absolute.regs[dest]]),
                        (Extract(63, width, p.pre.memory[p.pre_absolute.regs[dest]]) ==
                            Extract(63, width, p.post.memory[p.pre_absolute.regs[dest]])) if width < 64 else True,
                        p.operands[1].bit_length == width,
                        p.operands[0].register == src,
                        p.operands[1].register == dest,
                    )
                    for src in names
                )) for dest in list(filter(lambda d: p.pre_absolute.regs[d] in p.pre_absolute.memory.keys()
                                           and p.pre_absolute.regs[d] in p.post_absolute.memory.keys(), qword_reg_names_norip))
            )))
                      ) for reg_type, width, names in [
                  ("GP_REGISTER_QWORD", 64, qword_reg_names_norip),
                  ("GP_REGISTER_DWORD", 32, dword_reg_names_noeip),
                  ("GP_REGISTER_WORD", 16, word_reg_names_noip),
                  ("GP_REGISTER_HWORD", 8, hword_reg_names)
              ]
              )),
    )))

    # All registers that are not the destination register must stay the same
    p.s.add(Implies(p.mnemonic == "XCHG", And(*(
        Or(
            p.operands[0].register == n,
            And(Not(p.operands[1].memory), p.operands[1].register == n),
            p.pre_absolute.regs[n] == p.post_absolute.regs[n]
        )
        for n in qword_reg_names_norip + ["eflags"]
    ))))

    # All memory locations that are not the destination remain unchanged
    for address in p.post_absolute.memory.keys():
        if address not in p.pre_absolute.memory.keys():
            continue

        p.s.add(Implies(p.mnemonic == "XCHG", Or(*(Or(
            And(p.operands[1].memory, p.operands[1].register == r, abs(address - p.pre_absolute.regs[r]) < 8),
            p.pre_absolute.memory[address] == p.post_absolute.memory[address],
        ) for r in qword_reg_names_norip
        ))))
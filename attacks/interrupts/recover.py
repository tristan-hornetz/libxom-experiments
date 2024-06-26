from z3 import *
from trace import *
from instruction_models import *

output_file = "./.recover_from_trace.txt"


def bitlen_to_word(l):
    if l == 64:
        return "qword"
    if l == 32:
        return "dword"
    if l == 16:
        return "word"
    else:
        return "byte"


def run_solver(instruction_address, max_occurrences, next_instruction, is_last_instruction):
    plausible = set()
    for mnemonic_str, model in [
        ("ADD", model_add),
        ("RET", model_ret),
        ("CALL", model_call),
        ("SUB", model_sub),
        ("DEC", model_dec),
        ("INC", model_inc),
        ("MOV", model_mov),
        ("JMP", model_jmp),
        ("JG", model_jg),
        ("CMP", model_cmp),
        ("LEA", model_lea),
        ("XCHG", model_xchg),
    ]:
        solver = Solver()

        solver.add(one_ == 1)

        instruction_mnemonic = String(f"{instruction_address}_mnemonic")
        instruction_operands = [Operand(solver, f"{instruction_address}_operand_{n}") for n in range(2)]

        solver.add(instruction_mnemonic == mnemonic_str)

        occurrences_modeled = 0
        for i in range(len(victim_register_trace) - 1):
            if victim_register_trace[i].regs["rip"] != instruction_address or not victim_register_trace[i].pre:
                continue
            p = InstructionParameters(solver, i, victim_register_trace[i], victim_register_trace[i + 1],
                                      instruction_mnemonic, instruction_operands, next_instruction, is_last_instruction)
            model(p)
            occurrences_modeled += 1
            if occurrences_modeled >= max_occurrences:
                break
            if i % 50 or i in {2, 5, 10} == 0:
                if solver.check() == unsat:
                    break

        num_solutions = 0
        while solver.check() == sat and num_solutions < 10 and occurrences_modeled > 0:
            instr = f"{solver.model()[instruction_mnemonic]}".replace("\"", "").lower()
            op_strs = list()
            num_solutions += 1
            if instr == "lea":
                instr += (f" {hex(int(str(solver.model()[instruction_operands[0].displacement])))} "
                          f"(%{solver.model()[instruction_operands[0].register]}, "
                          f"%{solver.model()[instruction_operands[0].index_register]}, "
                          f"{2 ** int(str(solver.model()[instruction_operands[0].scale_factor]))}), "
                          f"%{solver.model()[instruction_operands[1].register]}")
                plausible.add(instr.replace("\"", ""))
                solver.add(instruction_operands[0].register != solver.model()[instruction_operands[0].register])
                continue
            for i in range(len(instruction_operands)):
                if not solver.model()[instruction_operands[i].used]:
                    break
                if solver.model()[instruction_operands[i].is_immediate]:
                    op_strs.append(str(hex(int(f"{solver.model()[instruction_operands[i].immediate]}"))))
                else:
                    op_strs.append(f"%{solver.model()[instruction_operands[i].register]}".replace("\"", ""))
                if solver.model()[instruction_operands[i].memory]:
                    op_strs[i] = f"[{bitlen_to_word(solver.model()[instruction_operands[i].bit_length])}]({op_strs[i]})"
            plausible.add(f"{instr} {', '.join(op_strs)}")
            if not solver.model()[instruction_operands[0].used]:
                break
            solver.add(Not(And(
                instruction_operands[0].type == solver.model()[instruction_operands[0].type],
                instruction_operands[0].bit_length == solver.model()[instruction_operands[0].bit_length],
                (instruction_operands[0].register == solver.model()[instruction_operands[0].register])
                if not solver.model()[instruction_operands[0].immediate] == True else
                (instruction_operands[0].immediate == solver.model()[instruction_operands[0].immediate]),
                And(
                    instruction_operands[1].type == solver.model()[instruction_operands[1].type],
                    instruction_operands[1].bit_length == solver.model()[instruction_operands[1].bit_length],
                    (instruction_operands[1].register == solver.model()[instruction_operands[1].register])
                    if not solver.model()[instruction_operands[1].immediate] == True else
                    (instruction_operands[1].immediate == solver.model()[instruction_operands[1].immediate])
                ) if solver.model()[instruction_operands[1].used] else True
            )))

    return plausible


if __name__ == "__main__":
    from sys import argv, stdout, stderr

    if len(argv) > 3:
        plausible = run_solver(int(argv[2]), int(argv[1]), int(argv[3]), int(argv[3]) == 0)
        with open(output_file, "at") as f:
            for p in plausible:
                f.write(f"{hex(int(argv[2]))}: {p}\n")
            if len(plausible) == 0:
                f.write(f"{hex(int(argv[2]))}: unsat\n")
        exit(0)

    import subprocess
    import os

    num_occurrences = 0x100
    if len(argv) > 1:
        num_occurrences = int(argv[1])

    if os.path.exists(output_file):
        os.remove(output_file)
    instruction_addresses = set()
    for state in filter(lambda s: s.pre, victim_register_trace):
        instruction_addresses.add(state.regs["rip"])

    print(list(sorted(hex(i) for i in instruction_addresses)))
    print("Running constraint solver. This may take a minute...")

    processes = list()
    instruction_addresses = list(sorted(instruction_addresses))
    for i in range(len(instruction_addresses)):
        addr = instruction_addresses[i]
        next_addr = 0
        if i < len(instruction_addresses) - 1:
            next_addr = instruction_addresses[i + 1]
        if addr >= 0x550000000000:
            break
        while len(processes) >= os.cpu_count():
            p_running = list()
            for p in processes:
                try:
                    p.wait(timeout=0.01)
                except subprocess.TimeoutExpired:
                    p_running.append(p)
            processes = p_running
        command = ['python', argv[0], f"{num_occurrences}", f"{addr}", f"{next_addr}"]
        # print(command)
        processes.append(subprocess.Popen(command, stdout=stdout, stderr=stderr))

    for p in processes:
        p.wait()

    with open(output_file, "rt") as f:
        output = f.read()

    print("The following is a list of plausible instructions for each given %rip. Note that this list"
          "should be viewed as an 'upper bound' for the possible instructions, as certain aspects "
          "about the instruction set are not modeled. Also, in cases where a large number of instructions is"
          "plausible, only a small subset is printed here.\n"
          "For branch instructions, displacements to memory operands are printed AFTER the memory operand itself,"
          "so 'jmp 0x80(%rax)' becomes 'jmp [qword](%rax), 0x80'.")

    os.remove(output_file)
    for l in sorted(set(output.split("\n"))):
        print(l)

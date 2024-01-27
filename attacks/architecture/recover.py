from z3 import *

class ProcessorState:
    def __init__(self, regs: dict, fpregs: dict, memory: dict) -> None:
        self.regs = regs
        self.fpregs = fpregs
        self.memory = memory


states = [
    ProcessorState({"rax": 0, "rbx": 0}, {"xmm0": [0, 0]}, {0: 0, 1: 0}),
]



def init_registers(solver: Solver) -> None:
    regs= {
        # QWORD
        'r15': BitVec('r15', 64),
        'r14': BitVec('r14', 64),
        'r13': BitVec('r13', 64),
        'r12': BitVec('r12', 64),
        'rbp': BitVec('rbp', 64),
        'rbx': BitVec('rbx', 64),
        'r11': BitVec('r11', 64),
        'r10': BitVec('r10', 64),
        'r9': BitVec('r9', 64),
        'r8': BitVec('r8', 64),
        'rax': BitVec('rax', 64),
        'rcx': BitVec('rcx', 64),
        'rdx': BitVec('rdx', 64),
        'rsi': BitVec('rsi', 64),
        'rdi': BitVec('rdi', 64),
        'rip': BitVec('rip', 64),
        'rsp': BitVec('rsp', 64),
        # FLAGS
        'eflags': BitVec('eflags', 32),
        'cf': BitVec('cf', 1),
        'pf': BitVec('pf', 1),
        'af': BitVec('af', 1),
        'zf': BitVec('zf', 1),
        'sf': BitVec('sf', 1),
        'tf': BitVec('tf', 1),
        'if': BitVec('if', 1),
        'df': BitVec('df', 1),
        'of': BitVec('of', 1),
        'id': BitVec('id', 1),
        # Omit other flags for now

        # DWORD
        'r15d': BitVec('r15', 64),
        'r14d': BitVec('r14', 64),
        'r13d': BitVec('r13', 64),
        'r12d': BitVec('r12', 64),
        'rbp': BitVec('rbp', 64),
        'rbx': BitVec('rbx', 64),
        'r11': BitVec('r11', 64),
        'r10': BitVec('r10', 64),
        'r9': BitVec('r9', 64),
        'r8': BitVec('r8', 64),
        'rax': BitVec('rax', 64),
        'rcx': BitVec('rcx', 64),
        'rdx': BitVec('rdx', 64),
        'rsi': BitVec('rsi', 64),
        'rdi': BitVec('rdi', 64),
        'rip': BitVec('rip', 64),
        'rsp': BitVec('rsp', 64),
    }
def init_solver():
    solver = Solver()

if __name__ == "__main__":
    init_solver()

.file "victim_code.s"
.text
.align 4096
// Get the nth Fibonacci number
// %rdi: n
// %rsi: accumulator (size must be >= 8*n)
.globl get_fibonacci
get_fibonacci:
    movq $0, (%rsi)
_1:
    cmp $1, %rdi
    jg _2
    lea (%rsi, %rdi, 8), %rcx
    mov %rdi, %rax
    dec %rdi
    jmp _3
_2:
    dec %rdi
    call _1
    xchg %rax, %rdi
    add %rdi, %rax
    add $0x8, %rcx
_3:
    mov %rax, (%rcx)
    ret

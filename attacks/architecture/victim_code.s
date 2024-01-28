.file "victim_code.s"
.text
.align 4096
// Get the nth Fibonacci number
// %rdi: n
// %rsi: accumulator (size must be >= 8*n)
.globl get_fibonacci
get_fibonacci:
    lea 1(%rsi, %rdi, 8), %rcx
    // Case n <= 1
    cmp $1, %rdi
    jg get_fibonacci2
    mov %rdi, %rax
    jmp get_fibonacci3
get_fibonacci2:
    // Case n > 1
    dec %rdi
    call get_fibonacci
    sub $0x8, %rcx
    add (%rcx), %rax
    add $0x10, %rcx
get_fibonacci3:
    // Epilogue
    mov %rax, (%rcx)
    ret
    call 0x80(%rip)

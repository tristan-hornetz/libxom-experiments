.file "jumper.s"

.align 0x100
.globl jumper_link
jumper_link:
    dec %rcx
    jnz jumper_link_continue
    ret
jumper_link_continue:
    // Compute next target page with 16-bit linear-feedback shift register
    mov %ax, %r8w
    and $0x2d, %r8w
    popcnt %r8w, %r8w
    shr $0x1, %ax
    shl $0xf, %r8w
    or %r8w, %ax

    // Compute new target address
    xor %rdx, %rdx
    mov %ax, %dx
    and $0xfff, %dx
    shl $0xc, %edx
    add %rdi, %rdx

    // Jump to next link
    jmp *%rdx


// base_address: %rdi
// seed: %rsi
// num_jumps: %rdx

.globl jumper_fun
jumper_fun:
    mov %rdx, %rcx
    mov %rsi, %rax
    jmp *%rdi

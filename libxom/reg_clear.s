.file "libxom/reg_clear.s"

.text

load_reg_clear_magic:
    push %rbp
    mov %rsp, %rbp
    sub $0x10, %rsp
    and $0xfffffffffffffff0, %rsp

    mov $0x002121657361656c, %rax
    push %rax
    mov $0x50654d7261656c43, %rax
    push %rax

    movaps (%rsp), %xmm14

    leave
    ret

.globl reg_clear_area_begin
reg_clear_area_begin:
    push %rbp
    mov %rsp, %rbp
    sub $0x10, %rsp
    and $0xfffffffffffffff0, %rsp

    mov $0x002121657361656c, %rax
    push %rax
    mov $0x50654d7261656c43, %rax
    push %rax

    movaps (%rsp), %xmm15

    leave
    ret

.globl reg_clear_area_leave
reg_clear_area_leave:
    pxor %xmm15, %xmm15
    ret

.globl check_reg_clear_magic
check_reg_clear_magic:
    // Load clear-reg magic into xmm14, and compare with xmm15
    // If they are not the same, we were interrupted duing encryption,
    // and our results are garbage because the SSE registers were overwritten
    call load_reg_clear_magic

    // Check if xmm14 and xmm15 are the same
    // Return 0 if they are equal, -1 otherwise
    xor %rax, %rax
    pxor %xmm15, %xmm14
    ptest %xmm14, %xmm14
    jz check_reg_clear_magic_exit
    not %rax
check_reg_clear_magic_exit:
    ret

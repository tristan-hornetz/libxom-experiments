.file "xom_tests/spectre_victim.s"

.data
.globl dmem
dmem: .long 0

.text
.align 4096
.globl perform_encryption
perform_encryption:
    xor %rdx, %rdi
    mov %rdi, %rax
    ret

.globl victim
victim:
    mov $0xdeadbeefdeadbeef, %rdx
    call *%rsi
    xor %rdx, %rdx
    ret

.align 1024
.globl leak_to_cache
leak_to_cache:
    mov dmem(%rip), %r8
    and $0xff, %rdx
    shl $0xc, %rdx
    mov (%r8, %rdx, 1), %rax
    ret

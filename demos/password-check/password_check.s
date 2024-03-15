.file "password_check.s"

.data
.align 0x1000

// %rdi: password_quad1
// %rsi: password_quad2
// %rdx: password_quad3
// %rcx: password_quad4

.globl check_password
check_password:
mov $1, %rax
xor %r8, %r8

.globl q1_lo
q1_lo:
cmp $0x12345678, %edi
cmovne %r8, %rax
shr $32, %rdi
.globl q1_hi
q1_hi:
cmp $0x90abcdef, %edi
cmovne %r8, %rax

.globl q2_lo
q2_lo:
cmp $0x12345678, %esi
cmovne %r8, %rax
shr $32, %rsi
.globl q2_hi
q2_hi:
cmp $0x90abcdef, %esi
cmovne %r8, %rax

.globl q3_lo
q3_lo:
cmp $0x12345678, %edx
cmovne %r8, %rax
shr $32, %rdx
.globl q3_hi
q3_hi:
cmp $0x90abcdef, %edx
cmovne %r8, %rax

.globl q4_lo
q4_lo:
cmp $0x12345678, %ecx
cmovne %r8, %rax
shr $32, %rcx

.globl q4_hi
q4_hi:
cmp $0x90abcdef, %ecx
cmovne %r8, %rax

ret

.globl check_password_end
check_password_end:
ret

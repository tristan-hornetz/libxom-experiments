.file "port_profile.s"

.text

// For all: output_buffer in %rdi, num_entries in %rsi

.globl contend_p0
contend_p0:
mfence
rdtsc
mfence
.rept 48
aesenc %xmm7, %xmm2
aesenc %xmm3, %xmm5
aesenc %xmm6, %xmm8
.endr
shl $0x20, %r11
or %r11, %rax
mov %eax, %r11d
dec %rsi
mov %rax, (%rdi, %rsi, 8)
jnz contend_p0
ret

.globl contend_p1
contend_p1:
mfence
rdtsc
mfence
.rept 64
crc32 %r8, %r8
crc32 %r9, %r9
crc32 %r10, %r10
.endr
shl $0x20, %r11
or %r11, %rax
mov %eax, %r11d
dec %rsi
mov %rax, (%rdi, %rsi, 8)
jnz contend_p1
ret

.globl contend_p5
contend_p5:
mfence
rdtsc
mfence
.rept 64
vpermd %ymm0, %ymm1, %ymm0
vpermd %ymm2, %ymm3, %ymm2
vpermd %ymm4, %ymm5, %ymm4
.endr
shl $0x20, %r11
or %r11, %rax
mov %eax, %r11d
dec %rsi
mov %rax, (%rdi, %rsi, 8)
jnz contend_p5
ret

.globl contend_p06
contend_p06:
mfence
rdtsc
mfence
.rept 188
ror $2, %rdx
ror $2, %rcx
.endr
shl $0x20, %r11
or %r11, %rax
mov %eax, %r11d
dec %rsi
mov %rax, (%rdi, %rsi, 8)
jnz contend_p06
ret


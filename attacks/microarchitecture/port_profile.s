.file "port_profile.s"

.text

// For all: output_buffer in %rdi, num_entries in %rsi

.globl contend_p0
contend_p0:
mfence
rdtsc
mfence
mov %rax, %r11
.rept 48
aesenc %xmm7, %xmm2
aesenc %xmm3, %xmm5
aesenc %xmm6, %xmm8
.endr
mfence
rdtsc
shl $0x20, %r11
or %r11, %rax 
dec %rsi
jnz contend_p0_next
ret
contend_p0_next:
mov %rax, (%rdi, %rsi, 8)
jmp contend_p0

.globl contend_p1
contend_p1:
mfence
rdtsc
mfence
mov %rax, %r11
.rept 48
crc32 %r8, %r8
crc32 %r9, %r9
crc32 %r10, %r10
.endr
mfence
rdtsc
shl $0x20, %r11
or %r11, %rax 
dec %rsi
jnz contend_p1_next
ret
contend_p1_next:
mov %rax, (%rdi, %rsi, 8)
jmp contend_p1

.globl contend_p5
contend_p5:
mfence
rdtsc
mfence
mov %rax, %r11
.rept 64
vpermd %ymm0, %ymm1, %ymm0
vpermd %ymm2, %ymm3, %ymm2
vpermd %ymm4, %ymm5, %ymm4
.endr
mfence
rdtsc
shl $0x20, %r11
or %r11, %rax 
dec %rsi
jnz contend_p5_next
ret
contend_p5_next:
mov %rax, (%rdi, %rsi, 8)
jmp contend_p5

.globl contend_p06
contend_p06:
mfence
rdtsc
mfence
mov %rax, %r11
.rept 256
ror $2, %rdx
ror $2, %rax
.endr
mfence
rdtsc
shl $0x20, %r11
or %r11, %rax 
dec %rsi
jnz contend_p06_next
ret
contend_p06_next:
mov %rax, (%rdi, %rsi, 8)
jmp contend_p06


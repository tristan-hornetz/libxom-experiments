.file "src/aes-vaes.s"
.data

// This version of the AES implementation uses the VAES extensions for better performance

.align 0x100

// void aes_gctr_linear(void *icb, void* x, void *y, unsigned int num_blocks)
// icb: %rdi
// x: %rsi
// y: %rdx
// num_blocks: %rcx
.global aes_gctr_linear
aes_gctr_linear:
    // Backup callee-saved register
    push %r15

    // Load key from immediates
.global aes_key_lo
aes_key_lo:
    movq $0x1234567890abcdef,%r15
    movq   %r15,%xmm0
.global aes_key_hi
aes_key_hi:
    movq $0x1234567890abcdef,%r15
    movq   %r15,%xmm1
    movlhps	%xmm1,%xmm0
    xor %r15b, %r15b

    // Prepare for round key generation
    movaps %xmm0, %xmm1
    movaps %xmm0, %xmm4

    aeskeygenassist $1, %xmm1, %xmm2
    mov $1, %al
    jmp .Laes_gctr_linear_prepare_roundkey_128
.Laeskeygenret1:
    movdqa %xmm1, %xmm5
    aeskeygenassist $2, %xmm1, %xmm2
    inc %al
    jmp .Laes_gctr_linear_prepare_roundkey_128
.Laeskeygenret2:
    movdqa %xmm1, %xmm6
    aeskeygenassist $4, %xmm1, %xmm2
    inc %al
    jmp .Laes_gctr_linear_prepare_roundkey_128
.Laeskeygenret3:
    movdqa %xmm1, %xmm7
    aeskeygenassist $8, %xmm1, %xmm2
    inc %al
    jmp .Laes_gctr_linear_prepare_roundkey_128
.Laeskeygenret4:
    movdqa %xmm1, %xmm8
    aeskeygenassist $16, %xmm1, %xmm2
    inc %al
    jmp .Laes_gctr_linear_prepare_roundkey_128
.Laeskeygenret5:
    movdqa %xmm1, %xmm9
    aeskeygenassist $32, %xmm1, %xmm2
    inc %al
    jmp .Laes_gctr_linear_prepare_roundkey_128
.Laeskeygenret6:
    movdqa %xmm1, %xmm10
    aeskeygenassist $64, %xmm1, %xmm2
    inc %al
    jmp .Laes_gctr_linear_prepare_roundkey_128
.Laeskeygenret7:
    movdqa %xmm1, %xmm11
    aeskeygenassist $0x80, %xmm1, %xmm2
    inc %al
    jmp .Laes_gctr_linear_prepare_roundkey_128
.Laeskeygenret8:
    movdqa %xmm1, %xmm12
    aeskeygenassist $0x1b, %xmm1, %xmm2
    inc %al
    jmp .Laes_gctr_linear_prepare_roundkey_128
.Laeskeygenret9:
    movdqa %xmm1, %xmm13
    aeskeygenassist $0x36, %xmm1, %xmm2
    inc %al
    jmp .Laes_gctr_linear_prepare_roundkey_128
.Laeskeygenret10:
    movdqa %xmm1, %xmm14

    // Load initial counter block
    movdqa (%rdi), %xmm3
    movdqa %xmm3, %xmm15
    movq $1, %r8
    movq %r8, %xmm2
    paddq %xmm2, %xmm15
    vinserti128 $1, %xmm15, %ymm3, %ymm3
    vpermq $0x44, %ymm2, %ymm2

    jmp .Laes_gctr_expand_round_keys

.Laes_gctr_linear_prepare_roundkey_128:
    pshufd $255, %xmm2, %xmm2
    movdqa %xmm1, %xmm3
    pslldq $4, %xmm3
    pxor %xmm3, %xmm1
    pslldq $4, %xmm3
    pxor %xmm3, %xmm1
    pslldq $4, %xmm3
    pxor %xmm3, %xmm1
    pxor %xmm2, %xmm1

    mov %al, %r8b
    dec %r8b
    jz .Laeskeygenret1
    dec %r8b
    jz .Laeskeygenret2
    dec %r8b
    jz .Laeskeygenret3
    dec %r8b
    jz .Laeskeygenret4
    dec %r8b
    jz .Laeskeygenret5
    dec %r8b
    jz .Laeskeygenret6
    dec %r8b
    jz .Laeskeygenret7
    dec %r8b
    jz .Laeskeygenret8
    dec %r8b
    jz .Laeskeygenret9
    jmp .Laeskeygenret10

.Laes_gctr_expand_round_keys:

    vpermq $0x44, %ymm4, %ymm4
    vpermq $0x44, %ymm5, %ymm5
    vpermq $0x44, %ymm6, %ymm6
    vpermq $0x44, %ymm7, %ymm7
    vpermq $0x44, %ymm8, %ymm8
    vpermq $0x44, %ymm9, %ymm9
    vpermq $0x44, %ymm10, %ymm10
    vpermq $0x44, %ymm11, %ymm11
    vpermq $0x44, %ymm12, %ymm12
    vpermq $0x44, %ymm13, %ymm13
    vpermq $0x44, %ymm14, %ymm14

    // ceil(%rcx / 2)
    inc %rcx
    shr $1, %rcx

.Laes_gctr_linear_enc_block:

    // Load counter block into xmm0
    vmovaps %ymm3, %ymm0

    // Encrypt the block
    vpxor      %ymm4, %ymm0, %ymm0
    vaesenc     %ymm5, %ymm0, %ymm0
    vaesenc     %ymm6, %ymm0, %ymm0
    vaesenc     %ymm7, %ymm0, %ymm0
    vaesenc     %ymm8, %ymm0, %ymm0
    vaesenc     %ymm9, %ymm0, %ymm0
    vaesenc     %ymm10, %ymm0, %ymm0
    vaesenc     %ymm11, %ymm0, %ymm0
    vaesenc     %ymm12, %ymm0, %ymm0
    vaesenc     %ymm13, %ymm0, %ymm0
    vaesenclast %ymm14, %ymm0, %ymm0

    // Load plain text block
    vmovdqa (%rsi), %ymm1
    // XOR with encrypted counter
    vpxor %xmm1, %xmm0, %xmm0

    // Store to output buffer
    vmovdqa %ymm0, (%rdx)

    // Were our registers cleared?
    // If so, abort and tell caller where to restart
    cmp $0xba, %r15b
    je .Laes_gctr_linear_enc_done

    // Decrement counter
    dec %rcx
    jz .Laes_gctr_linear_enc_done

    // Increment counter block
    vpaddd %xmm2, %xmm3, %xmm3

    // Increment input and output pointers
    add $0x20, %rdx
    add $0x20, %rsi

    jmp .Laes_gctr_linear_enc_block

.Laes_gctr_linear_enc_done:
    // Clear AVX registers before returning
    vzeroall

    // Return the amount of remaining blocks
    mov %rcx, %rax

    // Restore callee-saved register
    pop %r15
    ret

.global aes_gctr_linear_end
aes_gctr_linear_end:
    ret

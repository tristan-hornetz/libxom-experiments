.file "src/aes.s"
.data
    
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
    
    // Generate round keys for encryption, put into xmm[4-14]
    // Note that we cannot call .Laes_gctr_linear_prepare_roundkey_128,
    // since another thread could overwrite the return address while
    // the round keys are still in the SSE registers, thus
    // hijacking the control flow and gaining access to the key.
    // Therefore, the return address must not be stored in memory.
    // However, if we store it in a register, an attacker must
    // trigger an interrupt to modify the return value, which
    // causes the hypervisor to clear the SSE registers before
    // the attacker can gain control.

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
    movaps (%rdi), %xmm3
    movq $1, %r8
    movq %r8, %xmm2
    jmp .Laes_gctr_linear_enc_block

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


.Laes_gctr_linear_enc_block:

    // Load counter block into xmm0
    movaps %xmm3, %xmm0

    // Encrypt the block
    pxor       %xmm4,  %xmm0
    aesenc     %xmm5,  %xmm0
    aesenc     %xmm6,  %xmm0
    aesenc     %xmm7,  %xmm0
    aesenc     %xmm8,  %xmm0
    aesenc     %xmm9,  %xmm0
    aesenc     %xmm10, %xmm0
    aesenc     %xmm11, %xmm0
    aesenc     %xmm12, %xmm0
    aesenc     %xmm13, %xmm0
    aesenclast %xmm14, %xmm0

    // Load plain text block
    movaps (%rsi), %xmm1
    // XOR with encrypted counter
    pxor %xmm1, %xmm0

    // Store to output buffer
    mov %rdx, (%rdx)
    sfence
    movaps %xmm0, (%rdx)

    // Were our registers cleared?
    // If so, abort and tell caller where to restart
    cmp $0xba, %r15b
    je .Laes_gctr_linear_enc_done

    // Decrement counter
    dec %rcx
    jz .Laes_gctr_linear_enc_done

    // Increment counter block
    paddd %xmm2, %xmm3

    // Increment input and output pointers
    add $0x10, %rdx
    add $0x10, %rsi

    jmp .Laes_gctr_linear_enc_block

.Laes_gctr_linear_enc_done:
    // Clear SSE registers before returning
    pxor   %xmm0, %xmm0
    movaps %xmm0, %xmm1
    // xmm2 contains 0x1
    movaps %xmm0, %xmm3
    movaps %xmm0, %xmm4
    movaps %xmm0, %xmm5
    movaps %xmm0, %xmm6
    movaps %xmm0, %xmm7
    movaps %xmm0, %xmm8
    movaps %xmm0, %xmm9
    movaps %xmm0, %xmm10
    movaps %xmm0, %xmm11
    movaps %xmm0, %xmm12
    movaps %xmm0, %xmm13
    movaps %xmm0, %xmm14
    // xmm15 is not used
    
    // Return the amount of remaining blocks
    mov %rcx, %rax

    // Restore callee-saved register
    pop %r15
    ret

.global aes_gctr_linear_end
aes_gctr_linear_end:
    ret

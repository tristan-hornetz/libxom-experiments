// Based on the sample code from "Intel Advanced Encryption Standard
// (AES) New Instructions Set" white paper, Gueron, 2014

.text

.globl clear_sse_regs
clear_sse_regs:
    pxor   %xmm0, %xmm0
    pxor   %xmm1, %xmm1
    pxor   %xmm2, %xmm2
    pxor   %xmm3, %xmm3
    pxor   %xmm4, %xmm4
    pxor   %xmm5, %xmm5
    pxor   %xmm6, %xmm6
    pxor   %xmm7, %xmm7
    pxor   %xmm8, %xmm8
    pxor   %xmm9, %xmm9
    pxor   %xmm10, %xmm10
    pxor   %xmm11, %xmm11
    pxor   %xmm12, %xmm12
    pxor   %xmm13, %xmm13
    pxor   %xmm14, %xmm14
    pxor   %xmm15, %xmm15
    ret

PREPARE_ROUNDKEY_128:
    pshufd $255, %xmm2, %xmm2
    movdqa %xmm1, %xmm3
    pslldq $4, %xmm3
    pxor %xmm3, %xmm1
    pslldq $4, %xmm3
    pxor %xmm3, %xmm1
    pslldq $4, %xmm3
    pxor %xmm3, %xmm1
    pxor %xmm2, %xmm1
    ret

AES_128_Key_ExpansionEnc:
    // expect user key in xmm1
    aeskeygenassist $1, %xmm1, %xmm2
    call PREPARE_ROUNDKEY_128
    movdqa %xmm1, %xmm5
    aeskeygenassist $2, %xmm1, %xmm2
    call PREPARE_ROUNDKEY_128
    movdqa %xmm1, %xmm6
    aeskeygenassist $4, %xmm1, %xmm2
    call PREPARE_ROUNDKEY_128
    movdqa %xmm1, %xmm7
    aeskeygenassist $8, %xmm1, %xmm2
    call PREPARE_ROUNDKEY_128
    movdqa %xmm1, %xmm8
    aeskeygenassist $16, %xmm1, %xmm2
    call PREPARE_ROUNDKEY_128
    movdqa %xmm1, %xmm9
    aeskeygenassist $32, %xmm1, %xmm2
    call PREPARE_ROUNDKEY_128
    movdqa %xmm1, %xmm10
    aeskeygenassist $64, %xmm1, %xmm2
    call PREPARE_ROUNDKEY_128
    movdqa %xmm1, %xmm11
    aeskeygenassist $0x80, %xmm1, %xmm2
    call PREPARE_ROUNDKEY_128
    movdqa %xmm1, %xmm12
    aeskeygenassist $0x1b, %xmm1, %xmm2
    call PREPARE_ROUNDKEY_128
    movdqa %xmm1, %xmm13
    aeskeygenassist $0x36, %xmm1, %xmm2
    call PREPARE_ROUNDKEY_128
    movdqa %xmm1, %xmm14
    ret

AES_128_Key_ExpansionDec:
    // expect user key in xmm1
    aeskeygenassist $1, %xmm1, %xmm2
    call PREPARE_ROUNDKEY_128
    aesimc %xmm1, %xmm5
    aeskeygenassist $2, %xmm1, %xmm2
    call PREPARE_ROUNDKEY_128
    aesimc  %xmm1, %xmm6
    aeskeygenassist $4, %xmm1, %xmm2
    call PREPARE_ROUNDKEY_128
    aesimc  %xmm1, %xmm7
    aeskeygenassist $8, %xmm1, %xmm2
    call PREPARE_ROUNDKEY_128
    aesimc %xmm1, %xmm8
    aeskeygenassist $16, %xmm1, %xmm2
    call PREPARE_ROUNDKEY_128
    aesimc  %xmm1, %xmm9
    aeskeygenassist $32, %xmm1, %xmm2
    call PREPARE_ROUNDKEY_128
    aesimc %xmm1, %xmm10
    aeskeygenassist $64, %xmm1, %xmm2
    call PREPARE_ROUNDKEY_128
    aesimc %xmm1, %xmm11
    aeskeygenassist $128, %xmm1, %xmm2
    call PREPARE_ROUNDKEY_128
    aesimc %xmm1, %xmm12
    aeskeygenassist $27, %xmm1, %xmm2
    call PREPARE_ROUNDKEY_128
    aesimc %xmm1, %xmm13
    aeskeygenassist $54, %xmm1, %xmm2
    call PREPARE_ROUNDKEY_128
    movdqa %xmm1, %xmm14
    ret

// void aes_encrypt(struct key_prime_fun *key, const void *cleartext_block, void *ciphertext_block);
.global aes_encrypt
aes_encrypt:
    // Prologue
    push %rbp
    mov %rsp, %rbp
    push %rdx
    push %rsi

    // Put lower 64 bits of key in %xmm0[0:64] and upper 64 bits of key in %xmm1[0:64]
    jmp *%rdi

.globl __aes_encrypt_key_prime_return
__aes_encrypt_key_prime_return:

    // Move lower half of xmm1 into upper half of xmm0, full key is now in xmm0
    movlhps	%xmm1, %xmm0

    // Put key into xmm1 and xmm4 as well
    movaps %xmm0, %xmm1
    movaps %xmm0, %xmm4

    // Clear xmm2 for aeskeygenassist
    pxor   %xmm2, %xmm2

    // Generate round keys for encryption, put into xmm[4-14]
    call AES_128_Key_ExpansionEnc

    // Load plain text block into xmm0
    pop %rax
    movaps (%rax), %xmm0

    // Encrypt the block
    pxor       %xmm4,  %xmm0
    aesenc     %xmm5,  %xmm0
    aesenc     %xmm6,  %xmm0
    aesenc     %xmm7,  %xmm0
    aesenc     %xmm8,  %xmm0
    aesenc     %xmm9, %xmm0
    aesenc     %xmm10, %xmm0
    aesenc     %xmm11, %xmm0
    aesenc     %xmm12, %xmm0
    aesenc     %xmm13, %xmm0
    aesenclast %xmm14, %xmm0

    // Store encrypted block into output buffer
    pop %rax
    movaps %xmm0, (%rax)

    call clear_sse_regs
    leave
    ret

// void aes_decrypt(struct key_prime_fun *key, const void *ciphertext_block, void *cleartext_block);
.global aes_decrypt
aes_decrypt:
    // Prologue
    push %rbp
    mov %rsp, %rbp
    push %rdx
    push %rsi

    // Put lower 64 bits of key in %xmm0[0:64] and upper 64 bits of key in %xmm1[0:64]
    jmp *%rdi

.globl __aes_decrypt_key_prime_return
__aes_decrypt_key_prime_return:

    // Move lower half of xmm1 into upper half of xmm0, full key is now in xmm0
    movlhps	%xmm1, %xmm0

    // Put key into xmm1 and xmm4 as well
    movaps %xmm0, %xmm1
    movaps %xmm0, %xmm4

    // Clear xmm2 for aeskeygenassist
    pxor   %xmm2, %xmm2

    // Generate round keys for decryption, put into xmm[4-14]
    call AES_128_Key_ExpansionDec

    // Load cipher text block into xmm0
    pop %rax
    movaps (%rax), %xmm0

    # Decrypt the block.
    pxor       %xmm14, %xmm0
    aesdec     %xmm13, %xmm0
    aesdec     %xmm12, %xmm0
    aesdec     %xmm11, %xmm0
    aesdec     %xmm10, %xmm0
    aesdec     %xmm9, %xmm0
    aesdec     %xmm8,  %xmm0
    aesdec     %xmm7,  %xmm0
    aesdec     %xmm6,  %xmm0
    aesdec     %xmm5,  %xmm0
    aesdeclast %xmm4,  %xmm0

    // Store plain text into output buffer
    pop %rax
    movaps %xmm0, (%rax)

    call clear_sse_regs

    leave
    ret


// key: %rdi
// icb: %rsi
// x: %rdx,
// y: %rcx,
// num_blocks: %r8
// void aes_encrypt_counter(struct key_prime_fun *key, void *icb, void* x, void *y, unsigned int num_blocks)
.global aes_encrypt_counter
aes_encrypt_counter:
    // Prologue
    push %rbp
    mov %rsp, %rbp

    push %rcx
    // Put lower 64 bits of key in %xmm0[0:64] and upper 64 bits of key in %xmm1[0:64]
    jmp *%rdi

.global __aes_encrypt_counter_key_prime_return
__aes_encrypt_counter_key_prime_return:

    // Move lower half of xmm1 into upper half of xmm0, full key is now in xmm0
    movlhps	%xmm1, %xmm0

    // Put key into xmm1 and xmm4 as well
    movaps %xmm0, %xmm1
    movaps %xmm0, %xmm4

    // Clear xmm2 for aeskeygenassist
    pxor   %xmm2, %xmm2

    // Generate round keys for encryption, put into xmm[4-14]
    call AES_128_Key_ExpansionEnc

    // Load initial counter block
    movaps (%rsi), %xmm15

aes_encrypt_counter_enc_block:

    // Load counter block into xmm0
    movaps %xmm15, %xmm0

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
    movaps (%rdx), %xmm1
    // XOR with encrypted counter
    pxor %xmm1, %xmm0

    // Store to output buffer
    movaps %xmm0, (%rcx)

    // Decrement counter
    dec %r8
    jz aes_encrypt_counter_enc_exit

    // Increment counter block
    pcmpeqw %xmm1, %xmm1
    psrldq $12, %xmm1
    psubd %xmm1, %xmm15

    // Increment block pointers
    add $0x10, %rcx
    add $0x10, %rdx

    jmp aes_encrypt_counter_enc_block
aes_encrypt_counter_enc_exit:
    call clear_sse_regs
    leave
    ret

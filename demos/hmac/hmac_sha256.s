.file "hmac_sha256.s"

// SHA code is based on "Intel SHA Extensions - New Instructions Supporting the Secure
// Hash Algorithm on Intel Architecture Processors" by Gulley et al., 2013

////////////////////////
// Register assignments
////////////////////////

.set msg, %xmm0
.set state_lo, %xmm6
.set state_hi, %xmm7
.set ishuf_mask, %xmm8
.set state_backup, %ymm9
.set state_backup_lo, %xmm9
.set tmsg0, %xmm5
.set tmsg1, %xmm10
.set tmsg2, %xmm11
.set tmsg3, %xmm12
.set tmsg4, %xmm13
.set block_lo, %ymm14
.set block_hi, %ymm15
.set freeusexmm0, %xmm3
.set freeusexmm1, %xmm4
.set freeuseymm0, %ymm3
.set inner_hash_backup, %ymm1
.set inner_hash_backup_lo, %xmm1


////////////////////////
// Macros
////////////////////////

.macro load_128bit_constant, quad0, quad1, dest
    mov $\quad0, %r14
    movq %r14, %xmm2
    mov $\quad1, %r14
    movq %r14, %xmm3
    movlhps	%xmm3, %xmm2
    movdqa %xmm2, \dest
.endm

.macro load_256bit_constant_xmm, quad0, quad1, quad2, quad3, dest_lo, dest_hi
    mov $\quad0, %r14
    movq %r14, %xmm2
    mov $\quad1, %r14
    movq %r14, %xmm3
    movlhps	%xmm3, %xmm2
    movdqa %xmm2, \dest_lo
    mov $\quad2, %r14
    movq %r14, %xmm4
    mov $\quad3, %r14
    movq %r14, %xmm5
    movlhps	%xmm5,%xmm4
    movdqa %xmm4, \dest_hi
.endm

.macro load_256bit_constant, quad0, quad1, quad2, quad3, dest, name
    .globl quad0_\name
    quad0_\name:
    mov $\quad0, %r14
    movq %r14, %xmm2
    .globl quad1_\name
    quad1_\name:
    mov $\quad1, %r14
    movq %r14, %xmm3
    movlhps	%xmm3, %xmm2
    .globl quad2_\name
    quad2_\name:
    mov $\quad2, %r14
    movq %r14, %xmm4
    .globl quad3_\name
    quad3_\name:
    mov $\quad3, %r14
    movq %r14, %xmm5
    movlhps	%xmm5,%xmm4
    vinserti128    $1, %xmm4, %ymm2, \dest
    xor %r14, %r14
.endm

.macro roundconst_get, c_lolo, c_lohi, c_hilo, c_hihi, end_sym
    movq $0x\c_lohi\c_lolo, %r10
    movq $0x\c_hihi\c_hilo, %r11
    jmp \end_sym
.endm


// Place code into .data section, so that we can overwrite the keys
.data
.align 0x1000

// This symbol only indicates the start of the memory range to be copied into XOM. Do not call.
.globl hmac256_start
hmac256_start:


////////////////////////
// Memory encryption code
////////////////////////

// ymm0-5 remain unaffected
.Lprime_memory_encryption:
    // Load key from immediates
    .globl memenc_key_lo
    memenc_key_lo:
    movq $0x123456789abcdef,%r14
    movq   %r14,%xmm9
    .globl memenc_key_hi
    memenc_key_hi:
    movq $0x123456789abcdef,%r14
    movq   %r14,%xmm8
    movlhps	%xmm8,%xmm9

    // Prepare for round key generation
    movaps %xmm9, %xmm8
    vinserti128 $1, %xmm9, %ymm10, %ymm10

    aeskeygenassist $1, %xmm8, %xmm7
    mov $1, %al
    jmp .Laes_gctr_linear_prepare_roundkey_128
.Laespkeyr1:
    vinserti128 $1, %xmm8, %ymm11, %ymm11
    aeskeygenassist $2, %xmm8, %xmm7
    inc %al
    jmp .Laes_gctr_linear_prepare_roundkey_128
.Laespkeyr2:
    vinserti128 $1, %xmm8, %ymm12, %ymm12
    aeskeygenassist $4, %xmm8, %xmm7
    inc %al
    jmp .Laes_gctr_linear_prepare_roundkey_128
.Laespkeyr3:
    vinserti128 $1, %xmm8, %ymm13, %ymm13
    aeskeygenassist $8, %xmm8, %xmm7
    inc %al
    jmp .Laes_gctr_linear_prepare_roundkey_128
.Laespkeyr4:
    vinserti128 $1, %xmm8, %ymm14, %ymm14
    aeskeygenassist $16, %xmm8, %xmm7
    inc %al
    jmp .Laes_gctr_linear_prepare_roundkey_128
.Laespkeyr5:
    movdqa %xmm8, %xmm10
    aeskeygenassist $32, %xmm8, %xmm7
    inc %al
    jmp .Laes_gctr_linear_prepare_roundkey_128
.Laespkeyr6:
    movdqa %xmm8, %xmm11
    aeskeygenassist $64, %xmm8, %xmm7
    inc %al
    jmp .Laes_gctr_linear_prepare_roundkey_128
.Laespkeyr7:
    movdqa %xmm8, %xmm12
    aeskeygenassist $0x80, %xmm8, %xmm7
    inc %al
    jmp .Laes_gctr_linear_prepare_roundkey_128
.Laespkeyr8:
    movdqa %xmm8, %xmm13
    aeskeygenassist $0x1b, %xmm8, %xmm7
    inc %al
    jmp .Laes_gctr_linear_prepare_roundkey_128
.Laespkeyr9:
    movdqa %xmm8, %xmm14
    aeskeygenassist $0x36, %xmm8, %xmm7
    inc %al
    jmp .Laes_gctr_linear_prepare_roundkey_128
.Laespkeyr10:
    movdqa %xmm8, %xmm15

    test %r8, %r8
    jz .Lbackup_internal_state_primed
    jmp .Lrestore_internal_state_primed


.Laes_gctr_linear_prepare_roundkey_128:
    pshufd $255, %xmm7, %xmm7
    movdqa %xmm8, %xmm6
    pslldq $4, %xmm6
    pxor %xmm6, %xmm8
    pslldq $4, %xmm6
    pxor %xmm6, %xmm8
    pslldq $4, %xmm6
    pxor %xmm6, %xmm8
    pxor %xmm7, %xmm8
    mov %al, %cl
    dec %cl
    jz .Laespkeyr1
    dec %cl
    jz .Laespkeyr2
    dec %cl
    jz .Laespkeyr3
    dec %cl
    jz .Laespkeyr4
    dec %cl
    jz .Laespkeyr5
    dec %cl
    jz .Laespkeyr6
    dec %cl
    jz .Laespkeyr7
    dec %cl
    jz .Laespkeyr8
    dec %cl
    jz .Laespkeyr9
    dec %cl
    jz .Laespkeyr10

// dest addr: %rdi
// For save: ymm0-2 remain unaffected
// For load: ymm2 remains unaffected
.Lsave_ymm0_unpack:
    xor %r8, %r8
    jmp .Lunpack_round_keys
.Lload_ymm0_unpack:
    mov $1, %r8

.Lunpack_round_keys:
    vpxor %ymm3, %ymm3, %ymm3
    vmovdqa %ymm3, %ymm4
    vpermq $0xee, %ymm10, %ymm5
    vpermq $0xee, %ymm11, %ymm6
    vpermq $0xee, %ymm12, %ymm7
    vpermq $0xee, %ymm13, %ymm8
    vpermq $0xee, %ymm14, %ymm9
    vpermq $0x44, %ymm10, %ymm10
    vpermq $0x44, %ymm11, %ymm11
    vpermq $0x44, %ymm12, %ymm12
    vpermq $0x44, %ymm13, %ymm13
    vpermq $0x44, %ymm14, %ymm14
    vpermq $0x44, %ymm14, %ymm15
    test %r8, %r8
    jnz .Lload_ymm0

.Lsave_ymm0:
    // Generate new IV
    xor %r8, %r8
    jmp .Lencrypt_counter_block

.Lload_ymm0:
    // Load old IV
    mov $1, %r8
    movq (%r13), %r12
.Lencrypt_counter_block:
    // Encrypt the counter block

    movq %r12, %xmm3
    movlhps %xmm3, %xmm4

    movq %rdx, %xmm3
    paddq %xmm3, %xmm4
    vpermq $0x14, %ymm4, %ymm4

    vpxor   %ymm5, %ymm4, %ymm4
    vaesenc %ymm6, %ymm4, %ymm4
    vaesenc %ymm7, %ymm4, %ymm4
    vaesenc %ymm8, %ymm4, %ymm4
    vaesenc %ymm9, %ymm4, %ymm4
    vaesenc %ymm10, %ymm4, %ymm4
    vaesenc %ymm11, %ymm4, %ymm4
    vaesenc %ymm12, %ymm4, %ymm4
    vaesenc %ymm13, %ymm4, %ymm4
    vaesenc %ymm14, %ymm4, %ymm4
    vaesenclast %ymm15, %ymm4, %ymm4
    test %r8, %r8
    jnz .Lload_ymm0_memaccess

.Lsave_ymm0_memaccess:
    vpxor %ymm4, %ymm0, %ymm4

    // Check if we were interrupted in the meantime
    // If so, this is out last chance to restore the state
    test %r15, %r15
    jz .Lsave_ymm0_memaccess_store_critical
    mov $2, %r9
    movdqa %xmm0, state_lo
    vextracti128 $1, %ymm0, state_hi
    jmp restore_internal_state

.Lsave_ymm0_memaccess_store_critical:
    mov %rdi, 8(%rsp)
    mov %rsi, (%rsp)
    mov %r12, (%r13)
    vmovdqa %ymm4, (%rdx)
    jmp .Lymm0_crypt_return
.Lload_ymm0_memaccess:
    vmovdqa (%rdx), %ymm0
    vpxor %ymm4, %ymm0, %ymm0

.Lymm0_crypt_return:
    mfence
    dec %al
    jz .Lbackup_internal_state_store_done
    jmp .Lrestore_internal_state_loaded


////////////////////////
// HMAC/SHA256 Code
////////////////////////

// Load and pad HMAC key
// if %r8 == 0 then ipad else opad
load_key:
    load_256bit_constant 0x1234567890abdef,0x1234567890abdef,0x1234567890abdef,0x1234567890abdef, block_lo, key_lo
    load_256bit_constant 0x1234567890abdef,0x1234567890abdef,0x1234567890abdef,0x1234567890abdef, block_hi, key_hi
    test %r8, %r8
    jz .Lload_key_ipad
    mov $0x5c5c5c5c5c5c5c5c, %r9
    jmp .Lload_key_pad
.Lload_key_ipad:
    mov $0x3636363636363636, %r9
.Lload_key_pad:
    movq %r9, freeusexmm0
    vbroadcastss freeusexmm0, freeuseymm0
    vpxor freeuseymm0, block_lo, block_lo
    vpxor freeuseymm0, block_hi, block_hi
    test %r8, %r8
    jz .Lhmac_compress_key
    jmp .Lhmac_compress_outer_key


// Get the next round constant
.Lrcget_0:
    roundconst_get 428a2f98,71374491,b5c0fbcf,e9b5dba5,.Ladd_Kt_leave
.Lrcget_1:
    roundconst_get 3956c25b,59f111f1,923f82a4,ab1c5ed5,.Ladd_Kt_leave
.Lrcget_2:
    roundconst_get d807aa98,12835b01,243185be,550c7dc3,.Ladd_Kt_leave
.Lrcget_3:
    roundconst_get 72be5d74,80deb1fe,9bdc06a7,c19bf174,.Ladd_Kt_leave
.Lrcget_4:
    roundconst_get e49b69c1,efbe4786,0fc19dc6,240ca1cc,.Ladd_Kt_leave
.Lrcget_5:
    roundconst_get 2de92c6f,4a7484aa,5cb0a9dc,76f988da,.Ladd_Kt_leave
.Lrcget_6:
    roundconst_get 983e5152,a831c66d,b00327c8,bf597fc7,.Ladd_Kt_leave
.Lrcget_7:
    roundconst_get c6e00bf3,d5a79147,06ca6351,14292967,.Ladd_Kt_leave
.Lrcget_8:
    roundconst_get 27b70a85,2e1b2138,4d2c6dfc,53380d13,.Ladd_Kt_leave
.Lrcget_9:
    roundconst_get 650a7354,766a0abb,81c2c92e,92722c85,.Ladd_Kt_leave
.Lrcget_a:
    roundconst_get a2bfe8a1,a81a664b,c24b8b70,c76c51a3,.Ladd_Kt_leave
.Lrcget_b:
    roundconst_get d192e819,d6990624,f40e3585,106aa070,.Ladd_Kt_leave
.Lrcget_c:
    roundconst_get 19a4c116,1e376c08,2748774c,34b0bcb5,.Ladd_Kt_leave
.Lrcget_d:
    roundconst_get 391c0cb3,4ed8aa4a,5b9cca4f,682e6ff3,.Ladd_Kt_leave
.Lrcget_e:
    roundconst_get 748f82ee,78a5636f,84c87814,8cc70208,.Ladd_Kt_leave
.Lrcget_f:
    roundconst_get 90befffa,a4506ceb,bef9a3f7,c67178f2,.Ladd_Kt_leave
.Ladd_Kt_leave:
    movq %r10, freeusexmm0
    movq %r11, freeusexmm1
    movlhps freeusexmm1,freeusexmm0
    paddd freeusexmm0, msg
    inc %rcx
    mov %cl, %r8b
    dec %r8b
    jz .Lloadroundconst0
    dec %r8b
    jz .Lloadroundconst1
    dec %r8b
    jz .Lloadroundconst2
    dec %r8b
    jz .Lloadroundconst3
    dec %r8b
    jz .LloadroundconstU1
    dec %r8b
    jz .LloadroundconstU2
    dec %r8b
    jz .LloadroundconstU3
    dec %r8b
    jz .LloadroundconstU4
    dec %r8b
    jz .LloadroundconstU1
    dec %r8b
    jz .LloadroundconstU2
    dec %r8b
    jz .LloadroundconstU3
    dec %r8b
    jz .LloadroundconstU4
    dec %r8b
    jz .LloadroundconstF1
    dec %r8b
    jz .LloadroundconstF2
    dec %r8b
    jz .LloadroundconstF3
    jmp .LloadroundconstF4



// Compress a single 512-bit block
sha256_compress_block:
    xor %rcx, %rcx
    vinserti128 $0, state_lo, state_backup, state_backup
    vinserti128 $1, state_hi, state_backup, state_backup

    /* Rounds 0-3 */
    vextracti128 $0, block_lo, msg
    pshufb ishuf_mask, msg
    movdqa msg, tmsg0
    jmp .Lrcget_0
.Lloadroundconst0:
    sha256rnds2	state_lo, state_hi
    pshufd $0x0e, msg, msg
    sha256rnds2	state_hi, state_lo

    /* Rounds 4-7 */
    vextracti128 $1, block_lo, msg
    pshufb ishuf_mask, msg
    movdqa msg, tmsg1
    jmp .Lrcget_1
.Lloadroundconst1:
    sha256rnds2	state_lo, state_hi
    pshufd 		$0x0e, msg, msg
    sha256rnds2	state_hi, state_lo
    sha256msg1	tmsg1, tmsg0

    /* Rounds 8-11 */
    vextracti128 $0, block_hi, msg
    pshufb ishuf_mask, msg
    movdqa msg, tmsg2
    jmp .Lrcget_2
.Lloadroundconst2:
    sha256rnds2	state_lo, state_hi
    pshufd 		$0x0e, msg, msg
    sha256rnds2	state_hi, state_lo
    sha256msg1	tmsg2, tmsg1

    /* Rounds 12-15 */
    vextracti128 $1, block_hi, msg
    pshufb ishuf_mask, msg
    movdqa msg, tmsg3
    jmp .Lrcget_3
.Lloadroundconst3:
    sha256rnds2	state_lo, state_hi
    movdqa tmsg3, tmsg4
    palignr $0x4, tmsg2, tmsg4
    paddd tmsg4, tmsg0
    sha256msg2 tmsg3, tmsg0
    pshufd 		$0x0e, msg, msg
    sha256rnds2	state_hi, state_lo
    sha256msg1 tmsg3, tmsg2

    mov $2, %r9b
.Lloop_upper_rounds:
    dec %r9b

    /* Rounds 16-19 */
    /* Rounds 32-35 */
    movdqa tmsg0, msg
    test %r9b, %r9b
    jnz .Lrcget_4
    jmp .Lrcget_8
.LloadroundconstU1:
    sha256rnds2	state_lo, state_hi
    movdqa tmsg0, tmsg4
	palignr	$0x04, tmsg3, tmsg4
	paddd tmsg4, tmsg1
	sha256msg2	tmsg0, tmsg1
	pshufd $0x0e, msg, msg
	sha256rnds2	state_hi, state_lo
	sha256msg1 tmsg0, tmsg3

    /* Rounds 20-23 */
    /* Rounds 36-39 */
    movdqa tmsg1, msg
    test %r9b, %r9b
    jnz .Lrcget_5
    jmp .Lrcget_9
.LloadroundconstU2:
    sha256rnds2	state_lo, state_hi
	movdqa tmsg1, tmsg4
	palignr $4, tmsg0, tmsg4
	paddd tmsg4, tmsg2
	sha256msg2 tmsg1, tmsg2
    pshufd $0x0e, msg, msg
    sha256rnds2	state_hi, state_lo
	sha256msg1 tmsg1, tmsg0

    /* Rounds 24-27 */
    /* Rounds 40-43 */
    movdqa tmsg2, msg
    test %r9b, %r9b
    jnz .Lrcget_6
    jmp .Lrcget_a
.LloadroundconstU3:
    sha256rnds2	state_lo, state_hi
	movdqa tmsg2, tmsg4
	palignr	$0x04, tmsg1, tmsg4
	paddd tmsg4, tmsg3
	sha256msg2 tmsg2, tmsg3
    pshufd $0x0e, msg, msg
    sha256rnds2	state_hi, state_lo
	sha256msg1	tmsg2, tmsg1

    /* Rounds 28-31 */
    /* Rounds 44-47 */
    movdqa tmsg3, msg
    test %r9b, %r9b
    jnz .Lrcget_7
    jmp .Lrcget_b
.LloadroundconstU4:
    sha256rnds2	state_lo, state_hi
	movdqa tmsg3, tmsg4
	palignr	$0x04, tmsg2, tmsg4
	paddd tmsg4, tmsg0
	sha256msg2 tmsg3, tmsg0
	pshufd $0x0e, msg, msg
	sha256rnds2	state_hi, state_lo
	sha256msg1 tmsg3, tmsg2

    test %r9b, %r9b
    jnz .Lloop_upper_rounds


    /* Rounds 48-51 */
    movdqa tmsg0, msg
   jmp .Lrcget_c
.LloadroundconstF1:
    sha256rnds2	state_lo, state_hi
	movdqa tmsg0, tmsg4
	palignr $0x04, tmsg3, tmsg4
	paddd tmsg4, tmsg1
	sha256msg2 tmsg0, tmsg1
	pshufd $0x0e, msg, msg
	sha256rnds2	state_hi, state_lo
	sha256msg1 tmsg0, tmsg3

	/* Rounds 52-55 */
	movdqa tmsg1, msg
    jmp .Lrcget_d
.LloadroundconstF2:
    sha256rnds2 state_lo, state_hi
	movdqa tmsg1, tmsg4
	palignr $0x04, tmsg0, tmsg4
	paddd tmsg4, tmsg2
	sha256msg2 tmsg1, tmsg2
    pshufd  $0x0e, msg, msg
    sha256rnds2	state_hi, state_lo

    /* Rounds 56-59 */
	movdqa tmsg2, msg
    jmp .Lrcget_e
.LloadroundconstF3:
    sha256rnds2	state_lo, state_hi
	movdqa tmsg2, tmsg4
	palignr	$0x04, tmsg1, tmsg4
	paddd tmsg4, tmsg3
	sha256msg2 tmsg2, tmsg3
    pshufd $0x0e, msg, msg
    sha256rnds2	state_hi, state_lo

    /* Rounds 60-63 */
    movdqa tmsg3, msg
    jmp .Lrcget_f
.LloadroundconstF4:
    sha256rnds2	state_lo, state_hi
    pshufd $0x0e, msg, msg
    sha256rnds2	state_hi, state_lo

    /* Add to hash state */
    vextracti128 $1, state_backup, freeusexmm0
    paddd state_backup_lo, state_lo
    paddd freeusexmm0, state_hi

    dec %al
    jz .Lhmac_inner_key_compressed
    dec %al
    jz .Lhmac_compression_done
    dec %al
    jz .Lhmac_compress_outer_key_done
    jmp .Lhmac_leave


backup_internal_state:
    // Move state into %ymm0
    movdqa state_lo, %xmm0
    vinserti128 $1, state_hi, %ymm0, %ymm0

    // Load round keys
    xor %r8, %r8
    jmp .Lprime_memory_encryption
.Lbackup_internal_state_primed:

    // Save %ymm0 and address of current message block to memory
.Lbackup_internal_state_begin_store:
    // Saving the block counter to memory is okay, because it is not secret and
    // any modifications to it can at worst modify the length of the authenticated message,
    // something which the user can do anyway

    mov $1, %al
    jmp .Lsave_ymm0_unpack
.Lbackup_internal_state_store_done:

    // If we were not interrupted during the store operation, all is good and we can continue
    test %r15, %r15
    jz .Lrestore_sha_registers

    // If we were interrupted, we cannot recover, so return -1
    vzeroall
    add $0x10, %rsp
    xor %rax, %rax
    not %rax
    pop %r13
    pop %r14
    pop %r15
    leave
    ret


restore_internal_state:
    // Generate IV
    // We have to do this here, as the rdrand instruction often causes VM exits
    xor %r15, %r15
    rdrand %r12
    jae restore_internal_state
    test %r15, %r15
    jnz restore_internal_state

    // Restore address of message
    mov 8(%rsp), %rdi
    mov (%rsp), %rsi

    // Reset %r15
    xor %r15, %r15

    // Load round keys
    xor %r8, %r8
    inc %r8
    jmp .Lprime_memory_encryption
.Lrestore_internal_state_primed:

    // Load ymm0 from memory
    mov $2, %al
    jmp .Lload_ymm0_unpack

.Lrestore_internal_state_loaded:

    // If we were interrupted, we have to load the value again
    test %r15, %r15
    jnz restore_internal_state

.Lrestore_sha_registers:
    vextracti128 $1, %ymm0, state_hi
    movdqa %xmm0, state_lo
    load_128bit_constant 0x0405060700010203, 0x0c0d0e0f08090a0b, ishuf_mask

    dec %r9b
    jz .Lhmac_compression_next_round
    dec %r9b
    jz .Lhmac_compression_start
    dec %r9b
    jz .Lhmac_start_outer_hash
    jmp .Lhmac_start_outer_hash


// Main HMAC function
// msg: %rdi (0x20 aligned, already padded)
// num_block: %rsi
// out: %rdx
.globl hmac256
hmac256:
    push %rbp
    mov %rsp, %rbp
    sub $0x20, %rsp
    shr $5, %rsp
    shl $5, %rsp
    push %r15
    push %r14
    push %r13
    push %rdi
    push %rsi
    lea 0x28(%rsp), %r13
.Lhmac_start:
    xor %r15, %r15
    rdrand %r12
    jae .Lhmac_start
    test %r15, %r15
    jnz .Lhmac_start
    vzeroall

    // Load initial hash state and shuffle mask
    load_128bit_constant 0x0405060700010203, 0x0c0d0e0f08090a0b, ishuf_mask
    load_256bit_constant_xmm 0xbb67ae856a09e667, 0xa54ff53a3c6ef372, 0x9b05688c510e527f, 0x5be0cd191f83d9ab, state_lo, state_hi
    pshufd		$0xb1, state_lo, state_lo
	pshufd		$0x1b, state_hi, state_hi
    movdqa		state_lo, tmsg4
	palignr		$0x08, state_hi, state_lo
	pblendw		$0xf0, tmsg4, state_hi

    // Compress inner key
	xor %r8, %r8
	jmp load_key
.Lhmac_compress_key:
	mov $1, %al
	jmp sha256_compress_block

.Lhmac_inner_key_compressed:
    test %r15, %r15
    jnz .Lhmac_start

    // Backup state after compressing inner key
    mov $2, %r9b
    jmp backup_internal_state

    // Compress message
.Lhmac_compression_start:
    vmovdqa (%rdi), block_lo
    vmovdqa 0x20(%rdi), block_hi

    mov $2, %al
    jmp sha256_compress_block
.Lhmac_compression_done:

    // If we were interrupted, restore state
    mov $2, %r9b
    test %r15, %r15
    jnz restore_internal_state

    add $0x40, %rdi
    dec %rsi

    // Backup hash state every 256 blocks
    cmp $2, %sil
    jne .Lhmac_compression_next_round

    mov $1, %r9b
    jmp backup_internal_state

.Lhmac_compression_next_round:
    test %rsi, %rsi
    jnz .Lhmac_compression_start

    // Bring hash bytes into correct order
    pshufd $0x1b, state_lo, state_lo
	pshufd $0xb1, state_hi, state_hi
	movdqa state_lo, tmsg4
	pblendw	$0xf0, state_hi, state_lo
	palignr	$0x08, tmsg4, state_hi

    pshufb ishuf_mask, state_lo
    pshufb ishuf_mask, state_hi

.Lhmac_start_outer_hash:

    // Backup inner hash
	movdqa state_lo, inner_hash_backup_lo
	vinserti128 $1, state_hi, inner_hash_backup, inner_hash_backup

    // Load initial hash state for outer hash
    load_256bit_constant_xmm 0xbb67ae856a09e667, 0xa54ff53a3c6ef372, 0x9b05688c510e527f, 0x5be0cd191f83d9ab, state_lo, state_hi
    pshufd		$0xb1, state_lo, state_lo
	pshufd		$0x1b, state_hi, state_hi
    movdqa		state_lo, tmsg4
	palignr		$0x08, state_hi, state_lo
	pblendw		$0xf0, tmsg4, state_hi

	// Compress outer key
	xor %r8, %r8
	inc %r8
	jmp load_key
.Lhmac_compress_outer_key:

	mov $3, %al
	jmp sha256_compress_block

.Lhmac_compress_outer_key_done:
	vmovdqa inner_hash_backup, block_lo
	// Padding
	load_256bit_constant   0x0000000000000080, 0x0, 0x0, 0x0003000000000000 block_hi

    mov $4, %al
	jmp sha256_compress_block

.Lhmac_leave:
    // Bring hash bytes into correct order
    pshufd		$0xb1, state_lo, state_lo
	pshufd		$0x1b, state_hi, state_hi
    movdqa		state_lo, tmsg4
	palignr		$0x08, state_hi, state_lo
	pblendw		$0xf0, tmsg4, state_hi

	pshufb ishuf_mask, state_lo
    pshufb ishuf_mask, state_hi
    pshufd $0x4e, state_lo, state_lo
    pshufd $0x4e, state_hi, state_hi

    // If we were interrupted while computing the outer hash, we have to start again
    mov $2, %r9
    test %r15, %r15
    jnz restore_internal_state

    // Save HMAC
    mov %rdx, (%rdx)
    sfence
    movdqa state_hi, (%rdx)
    movdqa state_lo, 0x10(%rdx)

.Lexit:
    vzeroall
    add $0x10, %rsp
    mov %r15, %rax
    pop %r13
    pop %r14
    pop %r15
    leave
    ret


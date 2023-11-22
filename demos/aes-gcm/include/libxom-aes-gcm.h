#ifndef AES_IMMEDIATE_LIBXOM_AES_GCM_H
#define AES_IMMEDIATE_LIBXOM_AES_GCM_H
#include <immintrin.h>
#include <emmintrin.h>
#include <stdint.h>

#define GCM_BLOCK_SIZE 128 // bits, not bytes !!!
#define GCM_BLOCK_BYTES (GCM_BLOCK_SIZE >> 3)

#ifdef __cplusplus
extern "C" {
#endif

const static unsigned char _text_prime_key[] = {
    0x48, 0xb8, 0xef, 0xcd, 0xab, 0x89, 0x67,       // movabs $0x123456789abcdef,%rax
    0x45, 0x23, 0x01, 
    0x66, 0x48, 0x0f, 0x6e, 0xc0,                   // movq   %rax,%xmm0
    0x48, 0xb8, 0xef, 0xcd, 0xab, 0x89, 0x67,       // movabs $0x123456789abcdef,%rax
    0x45, 0x23, 0x01, 
    0x66, 0x48, 0x0f, 0x6e, 0xc8,                   // movq   %rax,%xmm1
    0x48, 0x31, 0xc0,                               // xor    %rax,%rax
    0xc3                                            // ret
};

struct key_prime_fun {
    uint8_t _text0[2];
    uint64_t key_lo;
    uint8_t _text1[7];
    uint64_t key_hi;
    uint8_t _text3[9];
} __attribute__((packed)) typedef key_prime_fun;

const static key_prime_fun* empty_key = (key_prime_fun*) _text_prime_key;

struct aes_gcm_context {
    struct key_prime_fun *key;
    unsigned char *restrict plaintext;
    unsigned char *restrict ciphertext;
    size_t num_blocks;
    char *restrict aad;
    size_t aad_size;
    char *restrict tag;
    char *restrict iv;
    size_t iv_len;
} typedef aes_gcm_context;

int aes_gcm_encrypt(aes_gcm_context *restrict c);
int aes_gcm_decrypt(aes_gcm_context *restrict c);

#ifdef __cplusplus
}
static_assert(sizeof(_text_prime_key) == sizeof(key_prime_fun), "Prime function buffer size does not align with code");
#else
_Static_assert(sizeof(_text_prime_key) == sizeof(key_prime_fun), "Prime function buffer size does not align with code");
#endif
#endif //AES_IMMEDIATE_LIBXOM_AES_GCM_H

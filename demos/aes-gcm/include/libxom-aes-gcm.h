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

extern void __aes_encrypt_counter_key_prime_return(void);
extern void __aes_encrypt_key_prime_return(void);
extern void __aes_decrypt_key_prime_return(void);

#define AES_KEY_TYPE_ENCRYPT            1
#define AES_KEY_TYPE_DECRYPT            2
#define AES_KEY_TYPE_ENCRYPT_COUNTER    3

const static unsigned char _text_prime_key[] = {
    0x48, 0xb8, 0xef, 0xcd, 0xab, 0x89, 0x67,       // movabs $0x123456789abcdef,%rax
    0x45, 0x23, 0x01, 
    0x66, 0x48, 0x0f, 0x6e, 0xc0,                   // movq   %rax,%xmm0
    0x48, 0xb8, 0xef, 0xcd, 0xab, 0x89, 0x67,       // movabs $0x123456789abcdef,%rax
    0x45, 0x23, 0x01, 
    0x66, 0x48, 0x0f, 0x6e, 0xc8,                   // movq   %rax,%xmm1
    0x48, 0xb8, 0xef, 0xbd, 0x0a, 0x89, 0x67,       // movabs $0x1234567890abdef,%rax
    0x45, 0x23, 0x01,
    0xff, 0xe0                                      // jmp    *%rax
};

struct key_prime_fun {
    uint8_t _text0[2];
    uint64_t key_lo;
    uint8_t _text1[7];
    uint64_t key_hi;
    uint8_t _text3[7];
    uint64_t return_addr;
    uint8_t _text4[2];
} __attribute__((packed)) typedef key_prime_fun;

const static key_prime_fun* empty_key = (key_prime_fun*) _text_prime_key;

union {
    uint64_t u64[2];
    __m128i u128;
} typedef aes_uint128;

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
    unsigned int key_type;
} typedef aes_gcm_context;

static inline void init_encrypt_key(struct key_prime_fun* key_dest, aes_uint128* key_src) {
    key_dest->key_lo = key_src->u64[0];
    key_dest->key_hi = key_src->u64[1];
    key_dest->return_addr = (uint64_t) __aes_encrypt_key_prime_return;
    memset(key_src, 0, sizeof(*key_src));
}

static inline void init_decrypt_key(struct key_prime_fun* key_dest, aes_uint128* key_src) {
    key_dest->key_lo = key_src->u64[0];
    key_dest->key_hi = key_src->u64[1];
    key_dest->return_addr = (uint64_t) __aes_decrypt_key_prime_return;
    memset(key_src, 0, sizeof(*key_src));
}

static inline void init_counter_mode_key(struct key_prime_fun* key_dest, aes_uint128* key_src) {
    key_dest->key_lo = key_src->u64[0];
    key_dest->key_hi = key_src->u64[1];
    key_dest->return_addr = (uint64_t) __aes_encrypt_counter_key_prime_return;
    memset(key_src, 0, sizeof(*key_src));
}

int aes_gcm_encrypt(aes_gcm_context *restrict c);
int aes_gcm_decrypt(aes_gcm_context *restrict c);

#ifdef __cplusplus
}
static_assert(sizeof(_text_prime_key) == sizeof(key_prime_fun), "Prime function buffer size does not align with code");
#else
_Static_assert(sizeof(_text_prime_key) == sizeof(key_prime_fun), "Prime function buffer size does not align with code");
#endif
#endif //AES_IMMEDIATE_LIBXOM_AES_GCM_H

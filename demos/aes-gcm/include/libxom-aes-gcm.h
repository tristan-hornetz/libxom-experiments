#ifndef AES_IMMEDIATE_LIBXOM_AES_GCM_H
#define AES_IMMEDIATE_LIBXOM_AES_GCM_H
#include <immintrin.h>
#include <emmintrin.h>
#include <stdint.h>
#include "aes.h"

#define GCM_BLOCK_SIZE 128 // bits, not bytes !!!
#define GCM_BLOCK_BYTES (GCM_BLOCK_SIZE >> 3)

#ifdef __cplusplus
extern "C" {
#endif

union {
    uint64_t u64[2];
    __m128i u128;
} typedef aes_uint128;

struct aes_gcm_context {
    gctr_fun gctr;
    unsigned char *restrict plaintext;
    unsigned char *restrict ciphertext;
    size_t num_blocks;
    char *restrict aad;
    size_t aad_size;
    char *restrict tag;
    char *restrict iv;
    size_t iv_len;
} typedef aes_gcm_context;

void init_counter_mode_function(aes_fun_code* const dest_code, aes_uint128* key_src);

int aes_gcm_encrypt(aes_gcm_context *restrict c);
int aes_gcm_decrypt(aes_gcm_context *restrict c);

#ifdef __cplusplus
}
#endif
#endif //AES_IMMEDIATE_LIBXOM_AES_GCM_H

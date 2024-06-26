#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sched.h>
#include "libxom-aes-gcm.h"
#include "aes.h"

// Naming convention follows NIST Special Publication 800-38D: "Recommendation for Block
// Cipher Modes of Operation: Galois/Counter Mode (GCM) and GMAC", Morris Dworkin, 2007

#define inc32(q) (*(uint32_t*)&(q))++
#define add32(q, n) (*(uint32_t*)&(q))+=n

const static uint64_t __attribute__((aligned(16))) zeroes_16[2] = {0, 0};
extern void gfmul(__m128i a, __m128i b, __m128i* res);

static inline void add32_be(__m128i* q, uint32_t n){
    *(uint32_t*)q += n;
}

static __m128i ghash(const __m128i H, void *restrict in, const size_t num_blocks){
    size_t i;
    __m128i *restrict Xi = in;
    __m128i X, Y = _mm_set_epi64x(0ll, 0ll);

    for(i = 0; i < num_blocks; i++) {
        X = Xi[i];
        X = _mm_xor_si128(X, Y);
        gfmul(X, H, &Y);
    }

    return Y;
}

static inline uintptr_t gctr(gctr_fun gctr_instance, __m128i *restrict X, __m128i *restrict Y, const __m128i IPB, const size_t num_blocks) {
    uintptr_t ret;
    sched_yield();
    // Backup r14, r15 and vector registers before calling, as any of them could be overwritten without
    // warning while executing the function
    asm volatile ("call *%1" : "=a"(ret) : "r"(gctr_instance), "D"(&IPB), "S"(X), "d"(Y), "c"(num_blocks) : "r14", "r15",
            "xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7", "xmm8", "xmm9", "xmm10", "xmm11", "xmm12",
            "xmm13", "xmm14", "xmm15");
    return ret;
}

static __m128i getJ0(aes_gcm_context *restrict c, const __m128i H){
    __m128i J0;
    size_t s;
    unsigned char* restrict tbuf;
    if(c->iv_len == (96 >> 3)){
        memset(&J0, 0, sizeof(J0));
        memcpy(&J0, c->iv, c->iv_len);
    } else {
        s = (GCM_BLOCK_SIZE * (((c->iv_len << 3) / GCM_BLOCK_SIZE) + (((c->iv_len << 3) % GCM_BLOCK_SIZE) ? 1 : 0 ))) - (c->iv_len << 3);
        tbuf = malloc(c->iv_len + ((64 + s) >> 3) + sizeof(uint64_t) + 16);
        if(!tbuf)
            exit(-ENOMEM);
        memset(tbuf, 0, c->iv_len + ((64 + s) >> 3) + sizeof(uint64_t) + 16);
        memcpy(tbuf, c->iv, c->iv_len);
        *(uint64_t*)(tbuf + (c->iv_len + ((64 + s) >> 3))) = c->iv_len;
        s = (c->iv_len + ((64 + s) >> 3) + sizeof(uint64_t));
        J0 = ghash(H, tbuf, s / (GCM_BLOCK_SIZE >> 3) + ((s % (GCM_BLOCK_SIZE >> 3)) ? 1 : 0));
        free(tbuf);
        tbuf = NULL;
    }
    return J0;
}

int aes_gcm_encrypt(aes_gcm_context *restrict c){
    __m128i H, J0, J1, S, zero128 = _mm_set_epi32(0, 0, 0, 0);
    size_t s, u, v;
    unsigned char *restrict tbuf;
    uintptr_t remaining = c->num_blocks;

    // Get H for gfmul
    while(gctr(c->gctr, (void*) zeroes_16, &H, zero128, 1));

    // Get initial counter block J0
    J0 = getJ0(c, H);

    // Encrypt in counter mode
    do {
        J1 = J0;
        add32_be(&J1, ((c->num_blocks - remaining) + 1));
        remaining = gctr(c->gctr, &(((__m128i *restrict)c->plaintext)[c->num_blocks - remaining]), 
                                &(((__m128i *restrict)c->ciphertext)[c->num_blocks - remaining]),
                                J1, remaining);
    } while(remaining);


    // Get required size s and 0-padding lengths u and v for auth tag generation
    u = (128 * c->num_blocks - c->num_blocks * GCM_BLOCK_SIZE) >> 3;
    v = (128 * ((c->aad_size << 3) / 128 + ((c->aad_size << 3) % 128 ? 1 : 0)) - (c->aad_size << 3)) >> 3;
    s = c->aad_size + v + (c->num_blocks * GCM_BLOCK_BYTES) + u + (2 * sizeof(uint64_t));

    tbuf = malloc(s);
    if(!tbuf)
        return -ENOMEM;
    memset(tbuf, 0, s);

    // Fill input buffer for auth tag generation
    if(c->aad)
        memcpy(tbuf, c->aad, c->aad_size);
    memcpy(&tbuf[c->aad_size + v], c->ciphertext, c->num_blocks * GCM_BLOCK_BYTES);
    *((uint64_t*) &tbuf[c->aad_size + v + (c->num_blocks * GCM_BLOCK_BYTES)]) = c->aad_size << 3;
    *((uint64_t*) &tbuf[c->aad_size + v + (c->num_blocks * GCM_BLOCK_BYTES) + sizeof(uint64_t)]) = c->num_blocks * GCM_BLOCK_SIZE;

    // Hash the input buffer
    S = ghash(H, tbuf, s / (GCM_BLOCK_SIZE >> 3) + (((s % (GCM_BLOCK_SIZE >> 3)) ? 1 : 0)));
    free(tbuf);

    // Encrypt hash block to obtain auth tag
    while(c->gctr( &J0, &S, (__m128i*)c->tag, 1));

    return 0;
}

int aes_gcm_decrypt(aes_gcm_context *restrict c){
    __m128i H, J0, J1, S;
    size_t s, u, v;
    unsigned char *restrict tbuf;
    unsigned char tag_reconstructed[GCM_BLOCK_BYTES] = {0, };
    uintptr_t remaining = c->num_blocks;

    // Get H for gfmul
    while(c->gctr((void*) zeroes_16, (void*)zeroes_16, &H, 1));

    // Get initial counter block J0
    J0 = getJ0(c, H);

    // Encrypt in counter mode
    do {
        J1 = J0;
        add32_be(&J1, ((c->num_blocks - remaining) + 1));
        remaining = gctr(c->gctr, &(((__m128i *restrict)c->ciphertext)[c->num_blocks - remaining]), 
                                &(((__m128i *restrict)c->plaintext)[c->num_blocks - remaining]),
                                J1, remaining);
    } while(remaining);

    // Get required size s and 0-padding lengths u and v for auth tag generation
    u = (128 * c->num_blocks - c->num_blocks * GCM_BLOCK_SIZE) >> 3;
    v = (128 * ((c->aad_size << 3) / 128 + ((c->aad_size << 3) % 128 ? 1 : 0)) - (c->aad_size << 3)) >> 3;
    s = c->aad_size + v + (c->num_blocks * GCM_BLOCK_BYTES) + u + (2 * sizeof(uint64_t));

    tbuf = malloc(s);
    if(!tbuf)
        return -ENOMEM;
    memset(tbuf, 0, s);

    // Fill input buffer for auth tag generation
    if(c->aad)
        memcpy(tbuf, c->aad, c->aad_size);
    memcpy(&tbuf[c->aad_size + v], c->ciphertext, c->num_blocks * GCM_BLOCK_BYTES);
    *((uint64_t*) &tbuf[c->aad_size + v + (c->num_blocks * GCM_BLOCK_BYTES)]) = c->aad_size << 3;
    *((uint64_t*) &tbuf[c->aad_size + v + (c->num_blocks * GCM_BLOCK_BYTES) + sizeof(uint64_t)]) = c->num_blocks * GCM_BLOCK_SIZE;

    // Hash the input buffer
    S = ghash(H, tbuf, s / (GCM_BLOCK_SIZE >> 3) + ((s % (GCM_BLOCK_SIZE >> 3)) ? 1 : 0));
    free(tbuf);

    // Encrypt hash block to obtain auth tag
    while(c->gctr(&J0, &S, (__m128i*)tag_reconstructed, 1));

    if(memcmp(c->tag, tag_reconstructed, sizeof(tag_reconstructed)))
        return -2;

    return 0;
}
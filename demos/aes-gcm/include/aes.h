#ifndef AES_IMMEDIATE_AES_H
#define AES_IMMEDIATE_AES_H

struct key_prime_fun;

// Encrypt block array X in counter mode, starting with initial counter block ICB
extern void aes_encrypt_counter(struct key_prime_fun *key, void *ICB, void* X, void *Y, unsigned int num_blocks);

// Encrypt single 128-bit block
extern void aes_encrypt(struct key_prime_fun *key, const void *cleartext_block, void *ciphertext_block);
// Decrypt single 128-bit block
extern void aes_decrypt(struct key_prime_fun *key, const void *ciphertext_block, void *cleartext_block);


#endif //AES_IMMEDIATE_AES_H

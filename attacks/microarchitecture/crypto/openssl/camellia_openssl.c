/*
 * Copyright 2006-2020 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

/*
 * Camellia low level APIs are deprecated for public use, but still ok for
 * internal use.
 */

#include <stdint.h>
#include <openssl/camellia.h>

int Camellia_Ekeygen(int keyBitLength, const uint8_t *rawKey,
                     KEY_TABLE_TYPE keyTable);
void Camellia_EncryptBlock_Rounds(int grandRounds, const uint8_t plaintext[],
                                  const KEY_TABLE_TYPE keyTable,
                                  uint8_t ciphertext[]);
void Camellia_DecryptBlock_Rounds(int grandRounds, const uint8_t ciphertext[],
                                  const KEY_TABLE_TYPE keyTable,
                                  uint8_t plaintext[]);
void Camellia_EncryptBlock(int keyBitLength, const uint8_t plaintext[],
                           const KEY_TABLE_TYPE keyTable, uint8_t ciphertext[]);
void Camellia_DecryptBlock(int keyBitLength, const uint8_t ciphertext[],
                           const KEY_TABLE_TYPE keyTable, uint8_t plaintext[]);

int Camellia_set_key(const unsigned char *userKey, const int bits,
                     CAMELLIA_KEY *key)
{
    if (!userKey || !key)
        return -1;
    if (bits != 128 && bits != 192 && bits != 256)
        return -2;
    key->grand_rounds = Camellia_Ekeygen(bits, userKey, key->u.rd_key);
    return 0;
}

void Camellia_encrypt(const unsigned char *in, unsigned char *out,
                      const CAMELLIA_KEY *key)
{
    Camellia_EncryptBlock_Rounds(key->grand_rounds, in, key->u.rd_key, out);
}

void Camellia_decrypt(const unsigned char *in, unsigned char *out,
                      const CAMELLIA_KEY *key)
{
    Camellia_DecryptBlock_Rounds(key->grand_rounds, in, key->u.rd_key, out);
}

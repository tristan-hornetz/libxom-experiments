#ifndef AES_IMMEDIATE_AES_H
#define AES_IMMEDIATE_AES_H

#include <stdint.h>

#define AES_FUN_SIZE 0x1bf
typedef uint8_t aes_fun_code[AES_FUN_SIZE];
typedef uintptr_t (*gctr_fun)(void *icb, void* x, void *y, unsigned int num_blocks);

#endif //AES_IMMEDIATE_AES_H

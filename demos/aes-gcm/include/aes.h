#ifndef AES_IMMEDIATE_AES_H
#define AES_IMMEDIATE_AES_H

#include <stdint.h>

#define AES_FUN_SIZE 0x200
typedef uintptr_t (*gctr_fun)(void *icb, void* x, void *y, unsigned int num_blocks);

#endif //AES_IMMEDIATE_AES_H

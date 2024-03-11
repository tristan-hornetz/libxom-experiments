#include <string.h>
#include "libxom-aes-gcm.h"

extern size_t __attribute__((section(".data"))) aes_gctr_linear(void*, void*, void*, size_t);
extern size_t __attribute__((section(".data"))) aes_gctr_linear_end(void);
extern uint8_t aes_key_lo;
extern uint8_t aes_key_hi;

#define key_offset(x) ((((uint8_t*)&(x)) + 2) - ((uint8_t*)aes_gctr_linear))


void init_counter_mode_function(void* const dest_code, aes_uint128* key_src) {
    size_t key_offsets[] = {key_offset(aes_key_lo), key_offset(aes_key_hi)};
    size_t aes_fun_size = (uint8_t*)aes_gctr_linear_end - (uint8_t*)aes_gctr_linear;
    unsigned i;

    if(aes_fun_size > AES_FUN_SIZE)
        return;

    memcpy(dest_code, aes_gctr_linear, aes_fun_size);

    for (i = 0; i < sizeof(uint64_t); i++) {
        (((uint8_t*)dest_code) + key_offsets[0])[i] = ((uint8_t*)&(key_src->u64[0]))[i];
        (((uint8_t*)dest_code) + key_offsets[1])[i] = ((uint8_t*)&(key_src->u64[1]))[i];
    }

    memset(key_src, 0, sizeof(*key_src));
}

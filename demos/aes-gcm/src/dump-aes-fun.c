#include "aes.h"
#include <stdlib.h>
#include <stdio.h>

extern size_t aes_gctr_linear(void *icb, void* x, void *y, unsigned int num_blocks); 

int main(){
    aes_fun_code* code = (aes_fun_code*) aes_gctr_linear;

    printf("const uint8_t aes_gctr_linear_empty[] = {\n");
    for(unsigned i = 0; i < AES_FUN_SIZE; i+=0x10){
        for (unsigned j = 0; j < 0x10 && (i + j) < AES_FUN_SIZE; j++){
            printf("0x%02x, ", (*code)[i + j]);
        }
        printf("\n");
    }
    printf("};\n");
    return 0;
}
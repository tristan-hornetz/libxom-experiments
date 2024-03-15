#include <stdint.h>
#include <stdlib.h>
#include <gcrypt.h>
#include "libxom.h"

extern uint32_t q1_lo;
extern uint32_t q1_hi;
extern uint32_t q2_lo;
extern uint32_t q2_hi;
extern uint32_t q3_lo;
extern uint32_t q3_hi;
extern uint32_t q4_lo;
extern uint32_t q4_hi;

#define key_ptr(x) *((uint32_t*)(((uint8_t*)&(x)) + 2))

extern size_t __attribute__((section(".data"))) check_password(size_t quad1, size_t quad2, size_t quad3, size_t quad4);
extern void __attribute__((section(".data"))) check_password_end(void);
static char* password = "unpwnable";

void setup_check_function(struct xombuf* xbuf) {
    gcry_error_t error;
    gcry_md_hd_t md;
    uint32_t hash[8];

    gcry_md_open(&md, GCRY_MD_SHA256, 0);
    gcry_md_write(md, password, strlen(password));
    memcpy(hash, gcry_md_read(md, GCRY_MD_SHA256), 0x20);
    gcry_md_close(md);

    key_ptr(q1_lo) = hash[0];
    key_ptr(q1_hi) = hash[1];
    key_ptr(q2_lo) = hash[2];
    key_ptr(q2_hi) = hash[3];
    key_ptr(q3_lo) = hash[4];
    key_ptr(q3_hi) = hash[5];
    key_ptr(q4_lo) = hash[6];
    key_ptr(q4_hi) = hash[7];

    xom_write(xbuf, check_password, (uint8_t*)check_password_end - (uint8_t*)check_password, 0);

    key_ptr(q1_lo) = 0;
    key_ptr(q1_hi) = 0;
    key_ptr(q2_lo) = 0;
    key_ptr(q2_hi) = 0;
    key_ptr(q3_lo) = 0;
    key_ptr(q3_hi) = 0;
    key_ptr(q4_lo) = 0;
    key_ptr(q4_hi) = 0;
}

int main(int argc, char* argv[]){
    struct xombuf* xbuf = xom_alloc(0x1000);
    size_t (*check_password_xom)(size_t quad1, size_t quad2, size_t quad3, size_t quad4) = NULL;
    gcry_check_version(GCRYPT_VERSION);
    gcry_control(GCRYCTL_SUSPEND_SECMEM_WARN);
    gcry_control(GCRYCTL_INIT_SECMEM, 0x1000, 0);
    gcry_control (GCRYCTL_INITIALIZATION_FINISHED, 0);
    uint64_t pw_hash[4] = {0, };
    gcry_md_hd_t md;

    if(argc < 2){
        printf("Error: Must enter a password!\n");
        return 1;
    }

    if(!xbuf)
        return 1;

    setup_check_function(xbuf);
    check_password_xom = xom_lock(xbuf);
    if(!check_password_xom)
        return 1;

    gcry_md_open(&md, GCRY_MD_SHA256, 0);
    gcry_md_write(md, argv[1], strlen(argv[1]));
    memcpy(pw_hash, gcry_md_read(md, GCRY_MD_SHA256), 0x20);
    gcry_md_close(md);

    asm volatile("enterr:");
    if(check_password_xom(pw_hash[0], pw_hash[1], pw_hash[2], pw_hash[3]))
        puts("Password OK!");
    else
        puts("Wrong Password!");

    return 0;
}
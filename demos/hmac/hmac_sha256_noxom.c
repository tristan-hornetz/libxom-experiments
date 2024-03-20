#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <immintrin.h>
#include <sys/mman.h>

#define RED "\e[0;31m"
#define YLL "\033[33m"
#define CRESET "\e[0m"
#define STR_WARN "[" YLL "WARNING" CRESET "] "
#define STR_ERR "[" RED "ERROR" CRESET "] "

// The function is located in the .data section, so we can overwrite
// the immediate values of "mov" instructions
extern size_t __attribute__((section(".data"))) hmac256(
        void *__attribute__((aligned(0x20))) padded_msg,
        size_t block_count,
        void *__attribute__((aligned(0x20))) out);

extern void __attribute__((section(".data"))) hmac256_start();

// Memory encryption key
extern uint8_t memenc_key_lo;
extern uint8_t memenc_key_hi;

// Memory encryption IV
extern uint8_t memenc_iv_lo;
extern uint8_t memenc_iv_hi;

// HMAC key
extern uint8_t quad0_key_lo;
extern uint8_t quad1_key_lo;
extern uint8_t quad2_key_lo;
extern uint8_t quad3_key_lo;

extern uint8_t quad0_key_hi;
extern uint8_t quad1_key_hi;
extern uint8_t quad2_key_hi;
extern uint8_t quad3_key_hi;

#define min(x, y) ((x) < (y) ? (x) : (y))
#define countof(x) (sizeof(x) / sizeof(*(x)))
#define keytype uint8_t
#define keyptr(x) ((keytype*)(((uint8_t*)&(x)) + 2))
static keytype *const hmac_key_ptrs[] = {
        keyptr(quad0_key_lo), keyptr(quad1_key_lo), keyptr(quad2_key_lo), keyptr(quad3_key_lo),
        keyptr(quad0_key_hi), keyptr(quad1_key_hi), keyptr(quad2_key_hi), keyptr(quad3_key_hi),
};

static keytype *const aes_key_ptrs[] = {};

#undef keyptr

// Add padding for SHA256
static size_t pad_message_alloc(const void *orig, void **padded_dest, size_t len) {
    uint64_t L = len << 3;
    size_t K = (448 - (((size_t) L + 1) & 0x1ff)) & 0x1ff;
    size_t length_padded = (L + 1 + K + 64) >> 3;
    uint8_t *padded = aligned_alloc(0x20, length_padded);
    unsigned i;

    memcpy(padded, orig, len);
    memset(padded + len, 0, length_padded - len);

    // Add key length for HMAC
    L += 0x200;

    for (i = 0; i < sizeof(L); i++)
        padded[length_padded - 1 - i] = ((uint8_t *) &L)[i];
    padded[len] |= 0x80;

    *padded_dest = padded;
    return length_padded >> 6;
}

static void set_hmac_key(const uint8_t *key) {
    unsigned i, j;

    for (i = 0; i < countof(hmac_key_ptrs); i++) {
        for (j = 0; j < sizeof(uint64_t); j++) {
            hmac_key_ptrs[i][j] = key[sizeof(uint64_t) * i + j];
        }
    }
}

static void generate_memenc_keys(void) {
    unsigned i;

    for (i = 0; i < countof(aes_key_ptrs); i++)
        _rdrand64_step((unsigned long long*) aes_key_ptrs[i]);
}

static void clear_keys() {
    unsigned i;

    for (i = 0; i < countof(hmac_key_ptrs); i++)
        memset(hmac_key_ptrs[i], 0, sizeof(uint64_t));
    for (i = 0; i < countof(aes_key_ptrs); i++)
        memset(hmac_key_ptrs[i], 0, sizeof(uint64_t));
}


int main(int argc, char *argv[]) {
    uint8_t __attribute__((aligned(0x20))) hmac_dest[0x20] = {0,};
    uint8_t *padded_msg = NULL;
    uint8_t key[64];
    size_t block_count, msg_size;
    char *unpadded;
    FILE* src_file;

    size_t (*hmac256_xom)(void *padded_msg, size_t block_count, void *out) = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    unsigned i;


    if (argc <= 2) {
        puts("Usage: hmac_sha256 KEY MESSAGE\n"
             "Note: The key cannot be longer than 64 bytes. "
             "If it is longer, the remaining bytes are discarded.");
        return 0;
    }

    unpadded = argv[2];
    msg_size = strlen(unpadded);
    if(!strcmp(unpadded, "-f")){
        if(argc <= 3){
            puts("Missing file path!");
            return 1;
        }

        src_file = fopen(argv[3], "r");
        if(!src_file || !~(uintptr_t)src_file) {
            puts("Could not open source file path!");
            return 1;
        }

        fseek(src_file, 0, SEEK_END);
        msg_size = ftell(src_file);
        rewind(src_file);

        unpadded = malloc(msg_size);

        if(fread(unpadded, msg_size, 1, src_file) != 1){
            puts("Could not read source file!");
            return 1;
        }

        fclose(src_file);
    }

    // Pad input for SHA256
    block_count = pad_message_alloc(unpadded, (void **) &padded_msg, msg_size);
    if (!padded_msg)
        return 1;

    puts("Successfully loaded input file!");

    // Encode key into immediate instructions
    memset(key, 0, sizeof(key));
    memcpy(key, argv[1], min(strlen(argv[1]), sizeof(key)));
    set_hmac_key(key);

    // Generate random keys for memory encryption
    generate_memenc_keys();

    // Fill buffer with code
    memcpy(hmac256_xom, hmac256_start, 0x1000);
    clear_keys();

    // Get function pointer

    hmac256_xom = (void *) ((uint8_t *) hmac256_xom + ((uint8_t*)hmac256 - (uint8_t*)hmac256_start));
    if (!hmac256_xom)
        return 1;

    // Compute HMAC
    printf("Enter ASM @ %p\n", hmac256_xom);
    asm volatile("enterr:");
    if(hmac256_xom(padded_msg, block_count, hmac_dest)){
        puts("Failed!\n");
    }

    // Print HMAC
    for (i = 0; i < sizeof(hmac_dest); i++) {
        printf("%02x", hmac_dest[i]);
    }
    puts("");

    // Cleanup
    if(unpadded != argv[2])
        free(unpadded);
    free(padded_msg);
    return 0;
}

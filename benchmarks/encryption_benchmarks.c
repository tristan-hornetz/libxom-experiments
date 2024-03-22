#include <cpuid.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gcrypt.h>
#include "libxom.h"

#define countof(x) (sizeof(x)/sizeof(*(x)))

#define NUM_REPETITIONS 0x100
#define OUT_FILE "./encryption_benchmarks.py"

#define KEY "unpwnable"
#define IV "pwnable"
#define URANDOM "/dev/urandom"
#define DATA_SIZE (1 << 29)

#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define YLL "\033[33m"
#define CRESET "\e[0m"
#define STR_WARN "[" YLL "WARNING" CRESET "] "
#define STR_OK "[" GRN "+" CRESET "] "
#define STR_PEND "[" CYN "*" CRESET "] "
#define STR_FAIL "[" RED "-" CRESET "] "

#define HMAC_SHA256_BLOCK_SIZE (1 << 6)

// Intel i5 13600kf
#define TSC_PROCESSOR "Intel Core i5 13600kf"
#define TSC_DENOMINATOR 0x2
#define TSC_NUMERATOR 0xb6
#define TSC_CRYSTAL_FREQUENCY 0x249f000

extern void __attribute__((section(".data"))) hmac256_start();
extern size_t __attribute__((section(".data"))) hmac256(
        void *__attribute__((aligned(0x20))) padded_msg,
        size_t block_count,
        void *__attribute__((aligned(0x20))) out);

extern size_t __attribute__((section(".data"))) aes_gctr_linear(void*, void*, void*, size_t);
extern size_t __attribute__((section(".data"))) aes_gctr_linear_end(void);

static uint8_t* random_data = NULL;
static uint8_t* encryption_dest = NULL;
static uint32_t tsc_denominator = 0, tsc_numerator = 0, tsc_crystal_frequency = 0;
static uint64_t timer;

#define tsc_to_seconds(x) (tsc_numerator && tsc_numerator && tsc_crystal_frequency ? (              \
    (double)(x) / ((double)tsc_crystal_frequency * ((double)tsc_numerator/(double)tsc_denominator)) \
    ) : 0.0)

static uint64_t rdtsc(void) {
    uint64_t a, d;
    asm volatile("mfence\nrdtsc" : "=a"(a), "=d"(d));
    return a | (d << 32);
}

static void get_tsc_freq(void) {
    uint32_t _d;
    __cpuid(0x15, tsc_denominator, tsc_numerator, tsc_crystal_frequency, _d);

    if (tsc_numerator && tsc_numerator && tsc_crystal_frequency)
        return;

    puts(STR_WARN "Could not determine TSC frequency. Resorting to predefined values for the " TSC_PROCESSOR);
    tsc_numerator = TSC_NUMERATOR;
    tsc_denominator = TSC_DENOMINATOR;
    tsc_crystal_frequency = TSC_CRYSTAL_FREQUENCY;
}

static int alloc_random_data(void) {
    int status = -1;
    FILE* rand = fopen(URANDOM, "r");

    if(!rand || !~(uintptr_t)rand)
        return -1;

    random_data = aligned_alloc(PAGE_SIZE, DATA_SIZE);
    if(!random_data)
        goto exit;

    encryption_dest = aligned_alloc(PAGE_SIZE, DATA_SIZE);
    if(!encryption_dest)
        goto exit;

    if (fread(random_data, DATA_SIZE, 1, rand) != 1)
        goto exit;

    status = 0;
exit:
    fclose(rand);
    return status;
}

void hmac_gcrypt (void) {
    gcry_error_t error;
    gcry_md_hd_t hd = NULL;
    unsigned char *digest;

    digest = malloc(gcry_md_get_algo_dlen(GCRY_MD_SHA256));
    if(!digest)
        goto exit;

    error = gcry_md_open(&hd, GCRY_MD_SHA256, GCRY_MD_FLAG_HMAC);
    if(error)
        goto exit;

    error = gcry_md_setkey(hd, KEY, strlen(KEY));
    if(error)
        goto exit;

    timer = rdtsc();
    gcry_md_write(hd, random_data, DATA_SIZE);
    memcpy(digest, gcry_md_read(hd, GCRY_MD_SHA256), gcry_md_get_algo_dlen(GCRY_MD_SHA256));
    timer = rdtsc() - timer;

exit:
    if(hd)
        gcry_md_close(hd);
    if(digest)
        free(digest);
}

void hmac_xom() {
    struct xombuf* xbuf = xom_alloc(PAGE_SIZE);
    size_t (*hmac256_xom) (
        void *__attribute__((aligned(0x20))) padded_msg,
        size_t block_count,
        void *__attribute__((aligned(0x20))) out);

    if(!xbuf)
        return;

    // We don't adjust the keys for this benchmark

    xom_write(xbuf, hmac256_start, PAGE_SIZE, 0);
    hmac256_xom = xom_lock(xbuf);

    if(!hmac256_xom)
        goto exit;

    // Add function offset within page
    hmac256_xom += (uint8_t*)hmac256 - (uint8_t*)hmac256_start;

    if (get_xom_mode() == XOM_MODE_SLAT) {
        if (xom_mark_register_clear(xbuf, 0, 0)) {
            printf(STR_FAIL "Could not mark XOM for register clearing. Aborting...\n");
            goto exit;
        }
    }

    timer = rdtsc();
    while(hmac256_xom(random_data, (DATA_SIZE / HMAC_SHA256_BLOCK_SIZE) - 1, encryption_dest));
    timer = rdtsc() - timer;

exit:
    xom_free(xbuf);
}

void enc_checksum(void){
    gcry_md_hd_t md;
    uint32_t hash[8];
    unsigned i;

    gcry_md_open(&md, GCRY_MD_SHA256, 0);
    gcry_md_write(md, encryption_dest, DATA_SIZE);
    memcpy(hash, gcry_md_read(md, GCRY_MD_SHA256), 0x20);
    gcry_md_close(md);

    for (i = 0; i < sizeof(hash); i++){
        printf("%02x", ((uint8_t*)hash)[i]);
    }
    puts("");
}

void aes_gcrypt(void){
    gcry_error_t error;
    gcry_cipher_hd_t hd;
    const uint64_t key[] = {0x1234567890abcdef, 0x1234567890abcdef};
    const char* iv = IV;

    error = gcry_cipher_open(&hd, GCRY_CIPHER_AES128, GCRY_CIPHER_MODE_CTR, 0);
    if(error)
        goto exit;


    error = gcry_cipher_setkey(hd, key, 128 >> 3);
    if(error)
        goto exit;

    error = gcry_cipher_setiv(hd, iv, 128 >> 3);
    if(error)
        goto exit;

    timer = rdtsc();
    gcry_cipher_encrypt(hd, encryption_dest, DATA_SIZE, random_data, DATA_SIZE);
    timer = rdtsc() - timer;

exit:
    if(hd)
        gcry_cipher_close(hd);
}

void aes_xom(void) {
    struct xombuf* xbuf = xom_alloc(PAGE_SIZE);
    const size_t aes_fun_size = (uint8_t*)aes_gctr_linear_end - (uint8_t*)aes_gctr_linear;
    size_t (*aes_xom_ptr)(void *icb, void* x, void *y, unsigned int num_blocks) = NULL;
    uint8_t __attribute__((aligned(0x20))) icb[16];
    size_t remaining = DATA_SIZE / (128 >> 3), rdiff;

    if(!xbuf)
        return;

    memset(icb, 0, sizeof(icb));
    memcpy(icb, IV, sizeof(IV));

    // We don't adjust the keys for this benchmark

    if (xom_write(xbuf, aes_gctr_linear, aes_fun_size, 0) != aes_fun_size)
        goto exit;

    aes_xom_ptr = xom_lock(xbuf);

#define write_offset(x) (DATA_SIZE - (x)*(128 >> 3))
    timer = rdtsc();
    while (remaining) {
        remaining = aes_xom_ptr(icb, random_data + write_offset(remaining), encryption_dest + write_offset(remaining), (DATA_SIZE -
                write_offset(remaining)) / (128 >> 3));
        rdiff = remaining - rdiff;
    }
    timer = rdtsc() - timer;
#undef write_offset


exit:
    xom_free(xbuf);
}

const static struct {
    void(*fn)(void);
    const char* name;
    const char* cname;
} benchmarks[] = {
        {.fn = hmac_gcrypt, .name = "HMAC-SHA256 (libgcrypt)", .cname = "hmac_lgcrypt"},
        {.fn = hmac_xom, .name = "HMAC-SHA256 (XOM)", .cname = "hmac_xom"},
        {.fn = aes_gcrypt, .name = "AES-128-CTR (libgcrypt)", .cname = "aes_gcrypt"},
        {.fn = aes_xom, .name = "AES-128-CTR (XOM)", .cname = "aes_xom"},
};

static void benchmark(FILE* f, const char* cname, void(*fn)(void)){
    unsigned i;

    fprintf(f, "times_%s = [", cname);
    for(i = 0; i < NUM_REPETITIONS; i++){
        printf("\r%s: %03u/%u       ", cname, i, NUM_REPETITIONS);
        fflush(stdout);
        asm volatile ("call *%0" :: "r"(fn) :
        "rax", "rbx", "rcx", "rdx", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15",
        "ymm0", "ymm1", "ymm2", "ymm3", "ymm4", "ymm5", "ymm6", "ymm7", "ymm8", "ymm9", "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15");
        fprintf(f, "0x%lx, ", timer);
        fflush(f);
    }
    fprintf(f, "]\n\n");
    printf("\r");
}

int main() {
    int status = 1;
    unsigned int i;
    FILE* f = NULL;

     switch (get_xom_mode()) {
        case XOM_MODE_UNSUPPORTED:
            printf(STR_FAIL "XOM is not supported on this system. Aborting...\n");
            return 1;
        case XOM_MODE_PKU:
            printf(STR_WARN "SLAT-based XOM is not supported on this system! Resorting to PKU, "
                            "which is insecure\n");
        default:;
    }

    if (!gcry_check_version(GCRYPT_VERSION))
        goto exit;
    gcry_control(GCRYCTL_DISABLE_SECMEM, 0);
    gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);

    get_tsc_freq();

    if(alloc_random_data() < 0)
        goto exit;

    if(!access(OUT_FILE, F_OK))
        remove(OUT_FILE);

    f = fopen(OUT_FILE, "w");
    if(!f || !~(uintptr_t)f)
        goto exit;

    printf("TSC_DENOMINATOR = 0x%x\n", tsc_denominator);
    printf("TSC_NUMERATOR = 0x%x\n", tsc_numerator);
    printf("TSC_CRYSTAL_FREQUENCY = 0x%x\n\n", tsc_crystal_frequency);

    for (i = 0; i < countof(benchmarks); i++){
        timer = ~0ull;
        benchmark(f, benchmarks[i].cname, benchmarks[i].fn);
        printf("%s: 0x%lx, (%lf seconds, %lf GB/s)\n",
               benchmarks[i].name, timer, tsc_to_seconds(timer),
               1.0 / (tsc_to_seconds(timer) * ((double)(1 << 30) / DATA_SIZE)));
    }

    status = 0;
exit:
    if(f && ~(uintptr_t)f)
        fclose(f);
    if(random_data)
        free(random_data);
    if(encryption_dest)
        free(encryption_dest);
    if(status)
        puts("Error!");
    return status;
}
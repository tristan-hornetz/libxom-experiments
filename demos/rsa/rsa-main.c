#include <stdio.h>
#include <gmp.h>
#include <openssl/x509.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#define LIPSUM  "Lorem ipsum dolor sit amet, consetetur sadipscing elitr," \
                " sed diam nonumy eirmod tempor invidunt ut labore et dol" \
                "ore magna aliquyam erat, sed diam voluptua. At vero eos " \
                "et accusam et justo duo dolores et ea rebum. Stet clita " \
                "kasd gubergren, no sea takimata"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

struct rsa_st {
    /*
     * #legacy
     * The first field is used to pickup errors where this is passed
     * instead of an EVP_PKEY.  It is always zero.
     * THIS MUST REMAIN THE FIRST FIELD.
     */
    int dummy_zero;

    OSSL_LIB_CTX *libctx;
    int32_t version;
    const RSA_METHOD *meth;
    /* functional reference if 'meth' is ENGINE-provided */
    ENGINE *engine;
    BIGNUM *n;
    BIGNUM *e;
    BIGNUM *d;
    BIGNUM *p;
    BIGNUM *q;
    BIGNUM *dmp1;
    BIGNUM *dmq1;
    BIGNUM *iqmp;

    /*
     * If a PSS only key this contains the parameter restrictions.
     * There are two structures for the same thing, used in different cases.
     */
    /* This is used uniquely by OpenSSL provider implementations. */
    //RSA_PSS_PARAMS_30 pss_params;

#if defined(FIPS_MODULE) && !defined(OPENSSL_NO_ACVP_TESTS)
    RSA_ACVP_TEST *acvp_test;
#endif

#ifndef FIPS_MODULE
    /* This is used uniquely by rsa_ameth.c and rsa_pmeth.c. */
    RSA_PSS_PARAMS *pss;
    /* for multi-prime RSA, defined in RFC 8017 */
    STACK_OF(RSA_PRIME_INFO) *prime_infos;
    /* Be careful using this if the RSA structure is shared */
    CRYPTO_EX_DATA ex_data;
#endif
    //CRYPTO_REF_COUNT references;
    int flags;
    /* Used to cache montgomery values */
    BN_MONT_CTX *_method_mod_n;
    BN_MONT_CTX *_method_mod_p;
    BN_MONT_CTX *_method_mod_q;
    BN_BLINDING *blinding;
    BN_BLINDING *mt_blinding;
    CRYPTO_RWLOCK *lock;

    int dirty_cnt;
};

void bn_to_mpz(const BIGNUM *bn, mpz_t mpz) {
    unsigned char* b = malloc(BN_num_bytes(bn));
    BN_bn2bin(bn, b);
    mpz_import(mpz, BN_num_bytes(bn), 1, 1, 0, 0, b);
    free(b);
}

// RSA encryption
static inline void encrypt(mpz_t encrypted,
             const mpz_t message,
             const mpz_t e,
             const mpz_t n) {
    mpz_powm(encrypted, message, e, n);
}

// RSA decryption
static inline void decrypt(mpz_t original,
             const mpz_t encrypted,
             const mpz_t d,
             const mpz_t n) {
    mpz_powm(original, encrypted, d, n);
}

static int digest_message(const unsigned char *message, size_t message_len, unsigned char **digest, unsigned int *digest_len) {
	int status = -1;
    EVP_MD_CTX *mdctx;

	if((mdctx = EVP_MD_CTX_new()) == NULL)
		return -1;

	if(1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL))
		goto out;

	if(1 != EVP_DigestUpdate(mdctx, message, message_len))
		goto out;

	if((*digest = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sha256()))) == NULL)
		goto out;

	if(1 != EVP_DigestFinal_ex(mdctx, *digest, digest_len))
		goto out;

    status = 0;
out:
	EVP_MD_CTX_free(mdctx);
    return status;
}

int parsePrivateKey(const char* keyFile) {
    FILE* file = fopen(keyFile, "rb");
    unsigned int digest_len, siglen = 0;
    unsigned char* digest = NULL, *padded_digest;
    uint8_t* sigret = NULL;

    if (!file) {
        perror("Error opening key file");
        return 1;
    }

    RSA* rsa = PEM_read_RSAPrivateKey(file, NULL, NULL, NULL);

    if (!rsa) {
        ERR_print_errors_fp(stderr);
        return 1;
    }

    if(digest_message((const unsigned char*) LIPSUM, sizeof(LIPSUM), &digest, &digest_len) < 0)
        goto out;

    padded_digest = malloc(RSA_size(rsa));
    for(unsigned i = 0; i < RSA_size(rsa); i += digest_len){
        memcpy(padded_digest + i, digest, digest_len);
    }

    sigret = malloc(RSA_size(rsa));
    const BIGNUM* modulus, *privateExponent, *publicExponent;
    BIGNUM *token = BN_new();
    RSA_get0_key(rsa, &modulus, &publicExponent, &privateExponent);

    printf("Modulus: %s\n\n", BN_bn2hex(modulus));
    printf("Private Exponent: %s\n\n", BN_bn2hex(privateExponent));

    printf("%p\n", *(void**)rsa->d);

    asm volatile("rsaa_begin:");
    RSA_sign(NID_sha256, padded_digest, digest_len, sigret, &siglen, rsa);

    BN_bin2bn(sigret, (int) siglen, token);

    printf("siglen: %u\n\n", siglen);
    printf("Token: %s\n\n", BN_bn2hex(token));


    mpz_t n, e, d, enc, dec, msg;
    mpz_init(n);
    mpz_init(e);
    mpz_init(d);
    mpz_init(enc);
    mpz_init(dec);
    mpz_init(msg);
    bn_to_mpz(modulus, n);
    bn_to_mpz(publicExponent, e);
    bn_to_mpz(privateExponent, d);
    bn_to_mpz(token, msg);
    encrypt(enc, msg, e, n);
    decrypt(dec, enc, d, n);
    printf("Decrypted: %s\n", mpz_get_str(NULL, 16, dec));
    printf("Modulus-GMP: %s\n", mpz_get_str(NULL, 16, n));
    mpz_clear(n);
    mpz_clear(e);
    mpz_clear(d);
    mpz_clear(enc);
    mpz_clear(dec);
    mpz_clear(msg);

    out:
    RSA_free(rsa);
    if(digest)
        free(digest);
    if(padded_digest)
        free(padded_digest);
    if(sigret)
        free(sigret);
    return 0;
}

int main(int argc, char* argv[]) {
    char* keyfile = argc < 2 ? "./key.pem" : argv[1];
    parsePrivateKey(keyfile);
    return 0;
}

#pragma GCC diagnostic pop
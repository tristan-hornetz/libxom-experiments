#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <emmintrin.h>
#include <sys/mman.h>
#include <unistd.h>
#include "libxom.h"
#include "libxom-aes-gcm.h"

#define RED "\e[0;31m"
#define YLL "\033[33m"
#define CRESET "\e[0m"
#define STR_WARN "[" YLL "WARNING" CRESET "] "
#define STR_ERR "[" RED "ERROR" CRESET "] "

#define block_align(s) ((s) + (((s) % GCM_BLOCK_BYTES) ? (GCM_BLOCK_BYTES - (s) % GCM_BLOCK_BYTES) : 0))

_Static_assert(sizeof(aes_uint128) == sizeof(__m128i), "Size of aes_uint128 does not align!");

static struct xom_subpages* subpages = NULL;
static char *infile = NULL, *outfile = NULL, *iv_str = NULL, *tag_str = NULL, *key_str = NULL;
static int enc = 0, dec = 0;
static aes_uint128 key, iv, tag = {.u64 = {0, 0}};

const static struct option long_options[] = {
        {"encrypt", no_argument,       &enc, 1},
        {"decrypt", no_argument,       &dec, 1},
        {"input",   required_argument, 0,    'i'},
        {"output",  required_argument, 0,    'o'},
        {"iv",      required_argument, 0,    'v'},
        {"tag",     required_argument, 0,    't'},
        {"key",     required_argument, 0,    'k'},
        {0, 0,                         0,    0}
};

static int parse_u128(const char* restrict in, aes_uint128 *restrict out){
    int i;
    size_t slen;
    char padded_input[2 * sizeof(aes_uint128) + 1] = {0}, b1[17] = {0};

    memset(out, 0, sizeof(*out));

    slen = strlen(in);

    if(slen > 2 * sizeof(aes_uint128))
        return -1;

    strncpy(&padded_input[2 * sizeof(aes_uint128) - slen] , in, slen);

    for(i = 0; i < 16; i++){
        b1[i] = padded_input[i] ? padded_input[i] : '0';
    }
    out->u64[1] = strtoul(b1, NULL, 16);
    for(i = 0; i < 16; i++){
        b1[i] = padded_input[16 + i] ? padded_input[16 + i] : '0';
    }
    out->u64[0] = strtoul(b1, NULL, 16);

    return 0;
}

static int parse_args(const int argc, char *argv[]) {
    int c, option_index, status = 0;

    while (1) {
        option_index = 0;
        c = getopt_long(argc, argv, "dei:o:v:t:k:",
                        long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
            case 0:
                break;
            case 'd':
                dec = 1;
                break;
            case 'e':
                enc = 1;
                break;
            case 'i':
                infile = optarg;
                break;
            case 'o':
                outfile = optarg;
                break;
            case 'v':
                iv_str = optarg;
                break;
            case 't':
                tag_str = optarg;
                break;
            case 'k':
                key_str = optarg;
                break;
            case '?':
                break;
            default:
                return -1;
        }
    }

    if (optind < argc && !outfile)
        outfile = argv[optind];

    if (enc == dec) {
        fprintf(stderr, STR_ERR "You must choose either decrypt or encrypt!\n");
        status = -1;
    }
    if (!infile) {
        fprintf(stderr, STR_ERR "No input file specified!\n");
        status = -1;
    }
    if (!outfile) {
        fprintf(stderr, STR_ERR "No output file specified!\n");
        status = -1;
    }
    if (!key_str) {
        fprintf(stderr, STR_ERR "You must specify a key!\n");
        status = -1;
    }
    if (dec && !iv_str) {
        fprintf(stderr, STR_ERR "You must specify an IV for decryption!\n");
        status = -1;
    }
    if (enc && tag_str)
        fprintf(stderr, STR_WARN "Tag specified for encrypt operation, ignoring argument\n");

    if(status)
        return status;

    if(parse_u128(key_str, &key)){
        fprintf(stderr, STR_ERR "Wrong key format!\n");
        status = -1;
    }

    if(parse_u128(iv_str, &iv)){
        fprintf(stderr, STR_ERR "Wrong IV format!\n");
        status = -1;
    }

    if(tag_str)
        if(parse_u128(tag_str, &tag)){
            fprintf(stderr, STR_ERR "Wrong tag format!\n");
            status = -1;
        }

    return status;
}

static ssize_t read_input_file(char** input){
    ssize_t status = -1;
    FILE* fp;
    size_t file_size, bytes_read;

    fp = fopen(infile, "r");
    if(!fp)
        return -1;

    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    if(!file_size)
        goto exit;
    fseek(fp, 0, SEEK_SET);

    *input = malloc(block_align(file_size));
    if(!*input)
        goto exit;

    bytes_read = fread(*input, 1, file_size, fp);
    if(bytes_read == file_size)
        status = file_size;
    else {
        free(*input);
        *input = NULL;
        goto exit;
    }

    if(block_align(file_size) > file_size)
        memset(&((*input)[file_size]), 0, block_align(file_size) - file_size);

exit:
    fclose(fp);

    return status;
}

static int write_output(const ssize_t size, const char* restrict output){
    int status = 0;
    FILE* fp;
    size_t bytes_written;

    fp = fopen(outfile, "w");
    if(!fp)
        return -1;
    bytes_written = fwrite(output,1, size, fp);
    if(bytes_written != size)
        status = -1;
    fclose(fp);
    return status;
}

static aes_fun_code* allocate_key_fun_noslat(){
    aes_fun_code*  ret;

    ret = (aes_fun_code*) mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if(!ret || !~(uintptr_t)ret)
        return NULL;

    init_counter_mode_function(ret, &key);
    mprotect(ret, getpagesize(), PROT_EXEC | PROT_READ);

    return ret;

}

static aes_fun_code* allocate_key_fun(){
    aes_fun_code fun_buf, *ret;
    const int xom_mode = get_xom_mode();

    if(!xom_mode){
        fprintf(stderr, STR_ERR "XOM is not supported on this system!\n");
        return NULL;
    }

    if(xom_mode == XOM_MODE_PKU){
        printf(STR_WARN "SLAT-based XOM is not supported on this system! Resorting to PKU, which is insecure...\n");
        return allocate_key_fun_noslat();
    }

    init_counter_mode_function(&fun_buf, &key);
    subpages = xom_alloc_subpages(getpagesize());
    ret = (aes_fun_code*) xom_fill_and_lock_subpages(subpages, sizeof(fun_buf), &fun_buf);
    if (xom_mark_register_clear_subpage(subpages, 0, 0)){
        printf(STR_WARN "Could not mark AES for register clearing.\n");
        xom_free_all_subpages(subpages);
        return NULL;
    }
    memset(&fun_buf, 0, sizeof (fun_buf));

    return ret;
}

int main(int argc, char *argv[]) {
    int status;
    char* input = NULL, *output = NULL;
    ssize_t input_size;
    aes_gcm_context context;
    aes_fun_code* key_fun;

    status = parse_args(argc, argv);
    if (status < 0)
        return -1;

    input_size = read_input_file(&input);
    if(input_size < 0)
        return -1;

    output = malloc(block_align(input_size));
    if(!output)
        goto exit;
    if(block_align(input_size) != input_size)
        memset(&output[input_size], 0, block_align(input_size) - input_size);

    key_fun = allocate_key_fun();
    if(!key_fun){
        fprintf(stderr, STR_ERR "Could not allocate key prime function!\n");
        goto exit;
    }

    context = (aes_gcm_context) {
        .gctr = (gctr_fun) key_fun,
        .plaintext = (unsigned char *restrict) (enc ? input : output),
        .ciphertext = (unsigned char *restrict) (enc ? output : input),
        .num_blocks = block_align(input_size) / GCM_BLOCK_BYTES,
        .aad = NULL,
        .aad_size = 0,
        .tag = (char *restrict) &tag,
        .iv = (char *restrict) &iv,
        .iv_len = sizeof (iv),
    };

    if(enc)
        status = aes_gcm_encrypt(&context);
    else
        status = aes_gcm_decrypt(&context);

    if(status == -2){
        fprintf(stderr, STR_ERR "Tag mismatch! Your input may have been forged by a third party!\n");
        goto exit;
    }
    if(status < 0){
        fprintf(stderr, STR_ERR "Could not perform operation!\n");
        goto exit;
    }
    if(dec)
        printf("Auth tag matches! Input is likely genuine.\n");

    status = write_output(block_align(input_size), output);
    if(status < 0){
        fprintf(stderr, STR_ERR "Could not write output!\n");
        goto exit;
    }

    printf("Successfully wrote output to %s!\n", outfile);
    if(enc) {
        printf("\nTag: %016lx%016lx\n", tag.u64[1], tag.u64[0]);
        printf("IV : %016lx%016lx\n", iv.u64[1], iv.u64[0]);
    }
    status = 0;

exit:
    if(subpages)
        xom_free_all_subpages(subpages);
    if(output)
        free(output);
    if(input)
        free(input);
    return status;
}
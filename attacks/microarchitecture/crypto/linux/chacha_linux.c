#include <stdint.h>

#define le32_to_cpu __le32_to_cpu

#define CHACHA_IV_SIZE		16

#define CHACHA_KEY_SIZE		32
#define CHACHA_BLOCK_SIZE	64
#define CHACHAPOLY_IV_SIZE	12

#define SZ_4K				0x00001000

#define CHACHA_STATE_WORDS	(CHACHA_BLOCK_SIZE / sizeof(uint32_t))

/* 192-bit nonce, then 64-bit stream position */
#define XCHACHA_IV_SIZE		32

#define __round_mask(x, y) ((__typeof__(x))((y)-1))
#define round_up(x, y) ((((x)-1) | __round_mask(x, y))+1)


#define min(x, y) ((x) < (y) ? (x) : (y))

extern void chacha_block_xor_ssse3(uint32_t *state, uint8_t *dst, const uint8_t *src,
				       unsigned int len, int nrounds);
extern void chacha_4block_xor_ssse3(uint32_t *state, uint8_t *dst, const uint8_t *src,
					unsigned int len, int nrounds);

static unsigned int chacha_advance(unsigned int len, unsigned int maxblocks)
{
	len = min(len, maxblocks * CHACHA_BLOCK_SIZE);
	return round_up(len, CHACHA_BLOCK_SIZE) / CHACHA_BLOCK_SIZE;
}

static void chacha_dosimd(uint32_t *state, uint8_t *dst, const uint8_t *src,
			  unsigned int bytes, int nrounds)
{
	while (bytes >= CHACHA_BLOCK_SIZE * 4) {
		chacha_4block_xor_ssse3(state, dst, src, bytes, nrounds);
		bytes -= CHACHA_BLOCK_SIZE * 4;
		src += CHACHA_BLOCK_SIZE * 4;
		dst += CHACHA_BLOCK_SIZE * 4;
		state[12] += 4;
	}
	if (bytes > CHACHA_BLOCK_SIZE) {
		chacha_4block_xor_ssse3(state, dst, src, bytes, nrounds);
		state[12] += chacha_advance(bytes, 4);
		return;
	}
	if (bytes) {
		chacha_block_xor_ssse3(state, dst, src, bytes, nrounds);
		state[12]++;
	}
}

enum chacha_constants { /* expand 32-byte k */
	CHACHA_CONSTANT_EXPA = 0x61707865U,
	CHACHA_CONSTANT_ND_3 = 0x3320646eU,
	CHACHA_CONSTANT_2_BY = 0x79622d32U,
	CHACHA_CONSTANT_TE_K = 0x6b206574U
};

static inline void chacha_init_consts(uint32_t *state)
{
	state[0]  = CHACHA_CONSTANT_EXPA;
	state[1]  = CHACHA_CONSTANT_ND_3;
	state[2]  = CHACHA_CONSTANT_2_BY;
	state[3]  = CHACHA_CONSTANT_TE_K;
}

static inline void chacha_init_generic(uint32_t *state, const uint32_t *key, const uint8_t *iv)
{
	chacha_init_consts(state);
	state[4]  = key[0];
	state[5]  = key[1];
	state[6]  = key[2];
	state[7]  = key[3];
	state[8]  = key[4];
	state[9]  = key[5];
	state[10] = key[6];
	state[11] = key[7];
	state[12] = *(uint32_t*)(iv +  0);
	state[13] = *(uint32_t*)(iv +  4);
	state[14] = *(uint32_t*)(iv +  8);
	state[15] = *(uint32_t*)(iv +  12);
}

void chacha_init_arch(uint32_t *state, const uint32_t *key, const uint8_t *iv)
{
	chacha_init_generic(state, key, iv);
}

void chacha_crypt_arch(uint32_t *state, uint8_t *dst, const uint8_t *src, unsigned int bytes,
		       int nrounds)
{

	do {
		unsigned int todo = min(bytes, SZ_4K);

		chacha_dosimd(state, dst, src, todo, nrounds);

		bytes -= todo;
		src += todo;
		dst += todo;
	} while (bytes);
}
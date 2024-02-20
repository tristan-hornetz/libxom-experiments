/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _UAPI_LINUX_BYTEORDER_LITTLE_ENDIAN_H
#define _UAPI_LINUX_BYTEORDER_LITTLE_ENDIAN_H

#define __force

#ifndef __LITTLE_ENDIAN
#define __LITTLE_ENDIAN 1234
#endif
#ifndef __LITTLE_ENDIAN_BITFIELD
#define __LITTLE_ENDIAN_BITFIELD
#endif

#include <stdint.h>
#include <linux/stddef.h>
#include <linux/types.h>
#include <linux/swab.h>

#define __constant_htonl(x) ((__force __be32)___constant_swab32((x)))
#define __constant_ntohl(x) ___constant_swab32((__force __be32)(x))
#define __constant_htons(x) ((__force __be16)___constant_swab16((x)))
#define __constant_ntohs(x) ___constant_swab16((__force __be16)(x))
#define __constant_cpu_to_le64(x) ((__force __le64)(uint64_t)(x))
#define __constant_le64_to_cpu(x) ((__force uint64_t)(__le64)(x))
#define __constant_cpu_to_le32(x) ((__force __le32)(__uint32_t)(x))
#define __constant_le32_to_cpu(x) ((__force __uint32_t)(__le32)(x))
#define __constant_cpu_to_le16(x) ((__force __le16)(__u16)(x))
#define __constant_le16_to_cpu(x) ((__force __u16)(__le16)(x))
#define __constant_cpu_to_be64(x) ((__force __be64)___constant_swab64((x)))
#define __constant_be64_to_cpu(x) ___constant_swab64((__force uint64_t)(__be64)(x))
#define __constant_cpu_to_be32(x) ((__force __be32)___constant_swab32((x)))
#define __constant_be32_to_cpu(x) ___constant_swab32((__force __uint32_t)(__be32)(x))
#define __constant_cpu_to_be16(x) ((__force __be16)___constant_swab16((x)))
#define __constant_be16_to_cpu(x) ___constant_swab16((__force __u16)(__be16)(x))
#define __cpu_to_le64(x) ((__force __le64)(uint64_t)(x))
#define __le64_to_cpu(x) ((__force uint64_t)(__le64)(x))
#define __cpu_to_le32(x) ((__force __le32)(__uint32_t)(x))
#define __le32_to_cpu(x) ((__force __uint32_t)(__le32)(x))
#define __cpu_to_le16(x) ((__force __le16)(__u16)(x))
#define __le16_to_cpu(x) ((__force __u16)(__le16)(x))
#define __cpu_to_be64(x) ((__force __be64)__swab64((x)))
#define __be64_to_cpu(x) __swab64((__force uint64_t)(__be64)(x))
#define __cpu_to_be32(x) ((__force __be32)__swab32((x)))
#define __be32_to_cpu(x) __swab32((__force __uint32_t)(__be32)(x))
#define __cpu_to_be16(x) ((__force __be16)__swab16((x)))
#define __be16_to_cpu(x) __swab16((__force __u16)(__be16)(x))

static __always_inline __le64 __cpu_to_le64p(const uint64_t *p)
{
	return (__force __le64)*p;
}
static __always_inline uint64_t __le64_to_cpup(const __le64 *p)
{
	return (__force uint64_t)*p;
}
static __always_inline __le32 __cpu_to_le32p(const __uint32_t *p)
{
	return (__force __le32)*p;
}
static __always_inline uint32_t __le32_to_cpup(const __le32 *p)
{
	return (__force uint32_t)*p;
}
static __always_inline __le16 __cpu_to_le16p(const __u16 *p)
{
	return (__force __le16)*p;
}
static __always_inline __u16 __le16_to_cpup(const __le16 *p)
{
	return (__force __u16)*p;
}
static __always_inline __be64 __cpu_to_be64p(const uint64_t *p)
{
	return (__force __be64)__swab64p((const __u64 *)p);
}
static __always_inline uint64_t __be64_to_cpup(const __be64 *p)
{
	return __swab64p((const __u64 *)p);
}
static __always_inline __be32 __cpu_to_be32p(const __uint32_t *p)
{
	return (__force __be32)__swab32p(p);
}
static __always_inline __uint32_t __be32_to_cpup(const __be32 *p)
{
	return __swab32p((__uint32_t *)p);
}
static __always_inline __be16 __cpu_to_be16p(const __u16 *p)
{
	return (__force __be16)__swab16p(p);
}
static __always_inline __u16 __be16_to_cpup(const __be16 *p)
{
	return __swab16p((__u16 *)p);
}
#define __cpu_to_le64s(x) do { (void)(x); } while (0)
#define __le64_to_cpus(x) do { (void)(x); } while (0)
#define __cpu_to_le32s(x) do { (void)(x); } while (0)
#define __le32_to_cpus(x) do { (void)(x); } while (0)
#define __cpu_to_le16s(x) do { (void)(x); } while (0)
#define __le16_to_cpus(x) do { (void)(x); } while (0)
#define __cpu_to_be64s(x) __swab64s((x))
#define __be64_to_cpus(x) __swab64s((x))
#define __cpu_to_be32s(x) __swab32s((x))
#define __be32_to_cpus(x) __swab32s((x))
#define __cpu_to_be16s(x) __swab16s((x))
#define __be16_to_cpus(x) __swab16s((x))


#endif /* _UAPI_LINUX_BYTEORDER_LITTLE_ENDIAN_H */


// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Cryptographic API.
 *
 * ARIA Cipher Algorithm.
 *
 * Documentation of ARIA can be found in RFC 5794.
 * Copyright (c) 2022 Taehee Yoo <ap420073@gmail.com>
 *
 * Information for ARIA
 *     http://210.104.33.10/ARIA/index-e.html (English)
 *     http://seed.kisa.or.kr/ (Korean)
 *
 * Public domain version is distributed above.
 */

#include <stdint.h>
#include <errno.h>
#include <stdlib.h>
#include <linux/types.h>

/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_BYTEORDER_GENERIC_H
#define _LINUX_BYTEORDER_GENERIC_H

/*
 * linux/byteorder/generic.h
 * Generic Byte-reordering support
 *
 * The "... p" macros, like le64_to_cpup, can be used with pointers
 * to unaligned data, but there will be a performance penalty on
 * some architectures.  Use get_unaligned for unaligned data.
 *
 * Francois-Rene Rideau <fare@tunes.org> 19970707
 *    gathered all the good ideas from all asm-foo/byteorder.h into one file,
 *    cleaned them up.
 *    I hope it is compliant with non-GCC compilers.
 *    I decided to put __BYTEORDER_HAS_uint64_t__ in byteorder.h,
 *    because I wasn't sure it would be ok to put it in types.h
 *    Upgraded it to 2.1.43
 * Francois-Rene Rideau <fare@tunes.org> 19971012
 *    Upgraded it to 2.1.57
 *    to please Linus T., replaced huge #ifdef's between little/big endian
 *    by nestedly #include'd files.
 * Francois-Rene Rideau <fare@tunes.org> 19971205
 *    Made it to 2.1.71; now a facelift:
 *    Put files under include/linux/byteorder/
 *    Split swab from generic support.
 *
 * TODO:
 *   = Regular kernel maintainers could also replace all these manual
 *    byteswap macros that remain, disseminated among drivers,
 *    after some grep or the sources...
 *   = Linus might want to rename all these macros and files to fit his taste,
 *    to fit his personal naming scheme.
 *   = it seems that a few drivers would also appreciate
 *    nybble swapping support...
 *   = every architecture could add their byteswap macro in asm/byteorder.h
 *    see how some architectures already do (i386, alpha, ppc, etc)
 *   = cpu_to_beXX and beXX_to_cpu might some day need to be well
 *    distinguished throughout the kernel. This is not the case currently,
 *    since little endian, big endian, and pdp endian machines needn't it.
 *    But this might be the case for, say, a port of Linux to 20/21 bit
 *    architectures (and F21 Linux addict around?).
 */

/*
 * The following macros are to be defined by <asm/byteorder.h>:
 *
 * Conversion of long and short int between network and host format
 *	ntohl(__uint32_t x)
 *	ntohs(__u16 x)
 *	htonl(__uint32_t x)
 *	htons(__u16 x)
 * It seems that some programs (which? where? or perhaps a standard? POSIX?)
 * might like the above to be functions, not macros (why?).
 * if that's true, then detect them, and take measures.
 * Anyway, the measure is: define only ___ntohl as a macro instead,
 * and in a separate file, have
 * unsigned long inline ntohl(x){return ___ntohl(x);}
 *
 * The same for constant arguments
 *	__constant_ntohl(__uint32_t x)
 *	__constant_ntohs(__u16 x)
 *	__constant_htonl(__uint32_t x)
 *	__constant_htons(__u16 x)
 *
 * Conversion of XX-bit integers (16- 32- or 64-)
 * between native CPU format and little/big endian format
 * 64-bit stuff only defined for proper architectures
 *	cpu_to_[bl]eXX(__uXX x)
 *	[bl]eXX_to_cpu(__uXX x)
 *
 * The same, but takes a pointer to the value to convert
 *	cpu_to_[bl]eXXp(__uXX x)
 *	[bl]eXX_to_cpup(__uXX x)
 *
 * The same, but change in situ
 *	cpu_to_[bl]eXXs(__uXX x)
 *	[bl]eXX_to_cpus(__uXX x)
 *
 * See asm-foo/byteorder.h for examples of how to provide
 * architecture-optimized versions
 *
 */

#define cpu_to_le64 __cpu_to_le64
#define le64_to_cpu __le64_to_cpu
#define cpu_to_le32 __cpu_to_le32
#define le32_to_cpu __le32_to_cpu
#define cpu_to_le16 __cpu_to_le16
#define le16_to_cpu __le16_to_cpu
#define cpu_to_be64 __cpu_to_be64
#define be64_to_cpu __be64_to_cpu
#define cpu_to_be32 __cpu_to_be32
#define be32_to_cpu __be32_to_cpu
#define cpu_to_be16 __cpu_to_be16
#define be16_to_cpu __be16_to_cpu
#define cpu_to_le64p __cpu_to_le64p
#define le64_to_cpup __le64_to_cpup
#define cpu_to_le32p __cpu_to_le32p
#define le32_to_cpup __le32_to_cpup
#define cpu_to_le16p __cpu_to_le16p
#define le16_to_cpup __le16_to_cpup
#define cpu_to_be64p __cpu_to_be64p
#define be64_to_cpup __be64_to_cpup
#define cpu_to_be32p __cpu_to_be32p
#define be32_to_cpup __be32_to_cpup
#define cpu_to_be16p __cpu_to_be16p
#define be16_to_cpup __be16_to_cpup
#define cpu_to_le64s __cpu_to_le64s
#define le64_to_cpus __le64_to_cpus
#define cpu_to_le32s __cpu_to_le32s
#define le32_to_cpus __le32_to_cpus
#define cpu_to_le16s __cpu_to_le16s
#define le16_to_cpus __le16_to_cpus
#define cpu_to_be64s __cpu_to_be64s
#define be64_to_cpus __be64_to_cpus
#define cpu_to_be32s __cpu_to_be32s
#define be32_to_cpus __be32_to_cpus
#define cpu_to_be16s __cpu_to_be16s
#define be16_to_cpus __be16_to_cpus

/*
 * They have to be macros in order to do the constant folding
 * correctly - if the argument passed into a inline function
 * it is no longer constant according to gcc..
 */

#undef ntohl
#undef ntohs
#undef htonl
#undef htons

#define ___htonl(x) __cpu_to_be32(x)
#define ___htons(x) __cpu_to_be16(x)
#define ___ntohl(x) __be32_to_cpu(x)
#define ___ntohs(x) __be16_to_cpu(x)

#define htonl(x) ___htonl(x)
#define ntohl(x) ___ntohl(x)
#define htons(x) ___htons(x)
#define ntohs(x) ___ntohs(x)

static inline void le32_add_cpu(__le32 *var, uint32_t val)
{
	*var = cpu_to_le32(le32_to_cpu(*var) + val);
}

static inline void le64_add_cpu(__le64 *var, uint64_t val)
{
	*var = cpu_to_le64(le64_to_cpu(*var) + val);
}

/* XXX: this stuff can be optimized */
static inline void le32_to_cpu_array(uint32_t *buf, unsigned int words)
{
	while (words--) {
		__le32_to_cpus(buf);
		buf++;
	}
}

static inline void cpu_to_le32_array(uint32_t *buf, unsigned int words)
{
	while (words--) {
		__cpu_to_le32s(buf);
		buf++;
	}
}

static inline void be32_add_cpu(__be32 *var, uint32_t val)
{
	*var = cpu_to_be32(be32_to_cpu(*var) + val);
}

static inline void be64_add_cpu(__be64 *var, uint64_t val)
{
	*var = cpu_to_be64(be64_to_cpu(*var) + val);
}

static inline void cpu_to_be32_array(__be32 *dst, const uint32_t *src, size_t len)
{
	size_t i;

	for (i = 0; i < len; i++)
		dst[i] = cpu_to_be32(src[i]);
}

static inline void be32_to_cpu_array(uint32_t *dst, const __be32 *src, size_t len)
{
	size_t i;

	for (i = 0; i < len; i++)
		dst[i] = be32_to_cpu(src[i]);
}

#endif /* _LINUX_BYTEORDER_GENERIC_H */
/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Cryptographic API for algorithms (i.e., low-level API).
 *
 * Copyright (c) 2006 Herbert Xu <herbert@gondor.apana.org.au>
 */
#ifndef _CRYPTO_ALGAPI_H
#define _CRYPTO_ALGAPI_H

#define ARCH_KMALLOC_MINALIGN __alignof__(unsigned long long)
#define CRYPTO_MINALIGN ARCH_KMALLOC_MINALIGN
#define CRYPTO_MINALIGN_ATTR __attribute__ ((__aligned__(CRYPTO_MINALIGN)))

typedef struct {
	int counter;
} atomic_t;

typedef struct refcount_struct {
	atomic_t refs;
} refcount_t;

struct crypto_tfm {
	refcount_t refcnt;

	uint32_t crt_flags;

	int node;

	void (*exit)(struct crypto_tfm *tfm);

	struct crypto_alg *__crt_alg;

	void *__crt_ctx[] CRYPTO_MINALIGN_ATTR;
};

/*
 * Maximum values for blocksize and alignmask, used to allocate
 * static buffers that are big enough for any combination of
 * algs and architectures. Ciphers have a lower maximum size.
 */
#define MAX_ALGAPI_BLOCKSIZE		160
#define MAX_ALGAPI_ALIGNMASK		127
#define MAX_CIPHER_BLOCKSIZE		16
#define MAX_CIPHER_ALIGNMASK		15

#ifdef ARCH_DMA_MINALIGN
#define CRYPTO_DMA_ALIGN ARCH_DMA_MINALIGN
#else
#define CRYPTO_DMA_ALIGN CRYPTO_MINALIGN
#endif

#define CRYPTO_DMA_PADDING ((CRYPTO_DMA_ALIGN - 1) & ~(CRYPTO_MINALIGN - 1))

/*
 * Autoloaded crypto modules should only use a prefixed name to avoid allowing
 * arbitrary modules to be loaded. Loading from userspace may still need the
 * unprefixed names, so retains those aliases as well.
 * This uses __MODULE_INFO directly instead of MODULE_ALIAS because pre-4.3
 * gcc (e.g. avr32 toolchain) uses __LINE__ for uniqueness, and this macro
 * expands twice on the same line. Instead, use a separate base name for the
 * alias.
 */
#define MODULE_ALIAS_CRYPTO(name)	\
		__MODULE_INFO(alias, alias_userspace, name);	\
		__MODULE_INFO(alias, alias_crypto, "crypto-" name)

struct crypto_aead;
struct crypto_instance;
struct module;
struct notifier_block;
struct rtattr;
struct scatterlist;
struct seq_file;
struct sk_buff;

struct crypto_type {
	unsigned int (*ctxsize)(struct crypto_alg *alg, uint32_t type, uint32_t mask);
	unsigned int (*extsize)(struct crypto_alg *alg);
	int (*init_tfm)(struct crypto_tfm *tfm);
	void (*show)(struct seq_file *m, struct crypto_alg *alg);
	int (*report)(struct sk_buff *skb, struct crypto_alg *alg);
	void (*free)(struct crypto_instance *inst);
#ifdef CONFIG_CRYPTO_STATS
	int (*report_stat)(struct sk_buff *skb, struct crypto_alg *alg);
#endif

	unsigned int type;
	unsigned int maskclear;
	unsigned int maskset;
	unsigned int tfmsize;
};


static inline void *crypto_tfm_ctx(struct crypto_tfm *tfm)
{
	return tfm->__crt_ctx;
}



/*
 * When an algorithm uses another algorithm (e.g., if it's an instance of a
 * template), these are the flags that should always be set on the "outer"
 * algorithm if any "inner" algorithm has them set.
 */
#define CRYPTO_ALG_INHERITED_FLAGS	\
	(CRYPTO_ALG_ASYNC | CRYPTO_ALG_NEED_FALLBACK |	\
	 CRYPTO_ALG_ALLOCATES_MEMORY)

int crypto_register_notifier(struct notifier_block *nb);
int crypto_unregister_notifier(struct notifier_block *nb);

/* Crypto notification events. */
enum {
	CRYPTO_MSG_ALG_REQUEST,
	CRYPTO_MSG_ALG_REGISTER,
	CRYPTO_MSG_ALG_LOADED,
};
#endif	/* _CRYPTO_ALGAPI_H */



#define ARIA_MIN_KEY_SIZE	16
#define ARIA_MAX_KEY_SIZE	32
#define ARIA_BLOCK_SIZE		16
#define ARIA_MAX_RD_KEYS	17
#define ARIA_RD_KEY_WORDS	(ARIA_BLOCK_SIZE / sizeof(uint32_t))

struct aria_ctx {
	uint32_t enc_key[ARIA_MAX_RD_KEYS][ARIA_RD_KEY_WORDS];
	uint32_t dec_key[ARIA_MAX_RD_KEYS][ARIA_RD_KEY_WORDS];
	int rounds;
	int key_length;
};

static const uint32_t s1[256] = {
	0x00636363, 0x007c7c7c, 0x00777777, 0x007b7b7b,
	0x00f2f2f2, 0x006b6b6b, 0x006f6f6f, 0x00c5c5c5,
	0x00303030, 0x00010101, 0x00676767, 0x002b2b2b,
	0x00fefefe, 0x00d7d7d7, 0x00ababab, 0x00767676,
	0x00cacaca, 0x00828282, 0x00c9c9c9, 0x007d7d7d,
	0x00fafafa, 0x00595959, 0x00474747, 0x00f0f0f0,
	0x00adadad, 0x00d4d4d4, 0x00a2a2a2, 0x00afafaf,
	0x009c9c9c, 0x00a4a4a4, 0x00727272, 0x00c0c0c0,
	0x00b7b7b7, 0x00fdfdfd, 0x00939393, 0x00262626,
	0x00363636, 0x003f3f3f, 0x00f7f7f7, 0x00cccccc,
	0x00343434, 0x00a5a5a5, 0x00e5e5e5, 0x00f1f1f1,
	0x00717171, 0x00d8d8d8, 0x00313131, 0x00151515,
	0x00040404, 0x00c7c7c7, 0x00232323, 0x00c3c3c3,
	0x00181818, 0x00969696, 0x00050505, 0x009a9a9a,
	0x00070707, 0x00121212, 0x00808080, 0x00e2e2e2,
	0x00ebebeb, 0x00272727, 0x00b2b2b2, 0x00757575,
	0x00090909, 0x00838383, 0x002c2c2c, 0x001a1a1a,
	0x001b1b1b, 0x006e6e6e, 0x005a5a5a, 0x00a0a0a0,
	0x00525252, 0x003b3b3b, 0x00d6d6d6, 0x00b3b3b3,
	0x00292929, 0x00e3e3e3, 0x002f2f2f, 0x00848484,
	0x00535353, 0x00d1d1d1, 0x00000000, 0x00ededed,
	0x00202020, 0x00fcfcfc, 0x00b1b1b1, 0x005b5b5b,
	0x006a6a6a, 0x00cbcbcb, 0x00bebebe, 0x00393939,
	0x004a4a4a, 0x004c4c4c, 0x00585858, 0x00cfcfcf,
	0x00d0d0d0, 0x00efefef, 0x00aaaaaa, 0x00fbfbfb,
	0x00434343, 0x004d4d4d, 0x00333333, 0x00858585,
	0x00454545, 0x00f9f9f9, 0x00020202, 0x007f7f7f,
	0x00505050, 0x003c3c3c, 0x009f9f9f, 0x00a8a8a8,
	0x00515151, 0x00a3a3a3, 0x00404040, 0x008f8f8f,
	0x00929292, 0x009d9d9d, 0x00383838, 0x00f5f5f5,
	0x00bcbcbc, 0x00b6b6b6, 0x00dadada, 0x00212121,
	0x00101010, 0x00ffffff, 0x00f3f3f3, 0x00d2d2d2,
	0x00cdcdcd, 0x000c0c0c, 0x00131313, 0x00ececec,
	0x005f5f5f, 0x00979797, 0x00444444, 0x00171717,
	0x00c4c4c4, 0x00a7a7a7, 0x007e7e7e, 0x003d3d3d,
	0x00646464, 0x005d5d5d, 0x00191919, 0x00737373,
	0x00606060, 0x00818181, 0x004f4f4f, 0x00dcdcdc,
	0x00222222, 0x002a2a2a, 0x00909090, 0x00888888,
	0x00464646, 0x00eeeeee, 0x00b8b8b8, 0x00141414,
	0x00dedede, 0x005e5e5e, 0x000b0b0b, 0x00dbdbdb,
	0x00e0e0e0, 0x00323232, 0x003a3a3a, 0x000a0a0a,
	0x00494949, 0x00060606, 0x00242424, 0x005c5c5c,
	0x00c2c2c2, 0x00d3d3d3, 0x00acacac, 0x00626262,
	0x00919191, 0x00959595, 0x00e4e4e4, 0x00797979,
	0x00e7e7e7, 0x00c8c8c8, 0x00373737, 0x006d6d6d,
	0x008d8d8d, 0x00d5d5d5, 0x004e4e4e, 0x00a9a9a9,
	0x006c6c6c, 0x00565656, 0x00f4f4f4, 0x00eaeaea,
	0x00656565, 0x007a7a7a, 0x00aeaeae, 0x00080808,
	0x00bababa, 0x00787878, 0x00252525, 0x002e2e2e,
	0x001c1c1c, 0x00a6a6a6, 0x00b4b4b4, 0x00c6c6c6,
	0x00e8e8e8, 0x00dddddd, 0x00747474, 0x001f1f1f,
	0x004b4b4b, 0x00bdbdbd, 0x008b8b8b, 0x008a8a8a,
	0x00707070, 0x003e3e3e, 0x00b5b5b5, 0x00666666,
	0x00484848, 0x00030303, 0x00f6f6f6, 0x000e0e0e,
	0x00616161, 0x00353535, 0x00575757, 0x00b9b9b9,
	0x00868686, 0x00c1c1c1, 0x001d1d1d, 0x009e9e9e,
	0x00e1e1e1, 0x00f8f8f8, 0x00989898, 0x00111111,
	0x00696969, 0x00d9d9d9, 0x008e8e8e, 0x00949494,
	0x009b9b9b, 0x001e1e1e, 0x00878787, 0x00e9e9e9,
	0x00cecece, 0x00555555, 0x00282828, 0x00dfdfdf,
	0x008c8c8c, 0x00a1a1a1, 0x00898989, 0x000d0d0d,
	0x00bfbfbf, 0x00e6e6e6, 0x00424242, 0x00686868,
	0x00414141, 0x00999999, 0x002d2d2d, 0x000f0f0f,
	0x00b0b0b0, 0x00545454, 0x00bbbbbb, 0x00161616
};

static const uint32_t s2[256] = {
	0xe200e2e2, 0x4e004e4e, 0x54005454, 0xfc00fcfc,
	0x94009494, 0xc200c2c2, 0x4a004a4a, 0xcc00cccc,
	0x62006262, 0x0d000d0d, 0x6a006a6a, 0x46004646,
	0x3c003c3c, 0x4d004d4d, 0x8b008b8b, 0xd100d1d1,
	0x5e005e5e, 0xfa00fafa, 0x64006464, 0xcb00cbcb,
	0xb400b4b4, 0x97009797, 0xbe00bebe, 0x2b002b2b,
	0xbc00bcbc, 0x77007777, 0x2e002e2e, 0x03000303,
	0xd300d3d3, 0x19001919, 0x59005959, 0xc100c1c1,
	0x1d001d1d, 0x06000606, 0x41004141, 0x6b006b6b,
	0x55005555, 0xf000f0f0, 0x99009999, 0x69006969,
	0xea00eaea, 0x9c009c9c, 0x18001818, 0xae00aeae,
	0x63006363, 0xdf00dfdf, 0xe700e7e7, 0xbb00bbbb,
	0x00000000, 0x73007373, 0x66006666, 0xfb00fbfb,
	0x96009696, 0x4c004c4c, 0x85008585, 0xe400e4e4,
	0x3a003a3a, 0x09000909, 0x45004545, 0xaa00aaaa,
	0x0f000f0f, 0xee00eeee, 0x10001010, 0xeb00ebeb,
	0x2d002d2d, 0x7f007f7f, 0xf400f4f4, 0x29002929,
	0xac00acac, 0xcf00cfcf, 0xad00adad, 0x91009191,
	0x8d008d8d, 0x78007878, 0xc800c8c8, 0x95009595,
	0xf900f9f9, 0x2f002f2f, 0xce00cece, 0xcd00cdcd,
	0x08000808, 0x7a007a7a, 0x88008888, 0x38003838,
	0x5c005c5c, 0x83008383, 0x2a002a2a, 0x28002828,
	0x47004747, 0xdb00dbdb, 0xb800b8b8, 0xc700c7c7,
	0x93009393, 0xa400a4a4, 0x12001212, 0x53005353,
	0xff00ffff, 0x87008787, 0x0e000e0e, 0x31003131,
	0x36003636, 0x21002121, 0x58005858, 0x48004848,
	0x01000101, 0x8e008e8e, 0x37003737, 0x74007474,
	0x32003232, 0xca00caca, 0xe900e9e9, 0xb100b1b1,
	0xb700b7b7, 0xab00abab, 0x0c000c0c, 0xd700d7d7,
	0xc400c4c4, 0x56005656, 0x42004242, 0x26002626,
	0x07000707, 0x98009898, 0x60006060, 0xd900d9d9,
	0xb600b6b6, 0xb900b9b9, 0x11001111, 0x40004040,
	0xec00ecec, 0x20002020, 0x8c008c8c, 0xbd00bdbd,
	0xa000a0a0, 0xc900c9c9, 0x84008484, 0x04000404,
	0x49004949, 0x23002323, 0xf100f1f1, 0x4f004f4f,
	0x50005050, 0x1f001f1f, 0x13001313, 0xdc00dcdc,
	0xd800d8d8, 0xc000c0c0, 0x9e009e9e, 0x57005757,
	0xe300e3e3, 0xc300c3c3, 0x7b007b7b, 0x65006565,
	0x3b003b3b, 0x02000202, 0x8f008f8f, 0x3e003e3e,
	0xe800e8e8, 0x25002525, 0x92009292, 0xe500e5e5,
	0x15001515, 0xdd00dddd, 0xfd00fdfd, 0x17001717,
	0xa900a9a9, 0xbf00bfbf, 0xd400d4d4, 0x9a009a9a,
	0x7e007e7e, 0xc500c5c5, 0x39003939, 0x67006767,
	0xfe00fefe, 0x76007676, 0x9d009d9d, 0x43004343,
	0xa700a7a7, 0xe100e1e1, 0xd000d0d0, 0xf500f5f5,
	0x68006868, 0xf200f2f2, 0x1b001b1b, 0x34003434,
	0x70007070, 0x05000505, 0xa300a3a3, 0x8a008a8a,
	0xd500d5d5, 0x79007979, 0x86008686, 0xa800a8a8,
	0x30003030, 0xc600c6c6, 0x51005151, 0x4b004b4b,
	0x1e001e1e, 0xa600a6a6, 0x27002727, 0xf600f6f6,
	0x35003535, 0xd200d2d2, 0x6e006e6e, 0x24002424,
	0x16001616, 0x82008282, 0x5f005f5f, 0xda00dada,
	0xe600e6e6, 0x75007575, 0xa200a2a2, 0xef00efef,
	0x2c002c2c, 0xb200b2b2, 0x1c001c1c, 0x9f009f9f,
	0x5d005d5d, 0x6f006f6f, 0x80008080, 0x0a000a0a,
	0x72007272, 0x44004444, 0x9b009b9b, 0x6c006c6c,
	0x90009090, 0x0b000b0b, 0x5b005b5b, 0x33003333,
	0x7d007d7d, 0x5a005a5a, 0x52005252, 0xf300f3f3,
	0x61006161, 0xa100a1a1, 0xf700f7f7, 0xb000b0b0,
	0xd600d6d6, 0x3f003f3f, 0x7c007c7c, 0x6d006d6d,
	0xed00eded, 0x14001414, 0xe000e0e0, 0xa500a5a5,
	0x3d003d3d, 0x22002222, 0xb300b3b3, 0xf800f8f8,
	0x89008989, 0xde00dede, 0x71007171, 0x1a001a1a,
	0xaf00afaf, 0xba00baba, 0xb500b5b5, 0x81008181
};

static const uint32_t x1[256] = {
	0x52520052, 0x09090009, 0x6a6a006a, 0xd5d500d5,
	0x30300030, 0x36360036, 0xa5a500a5, 0x38380038,
	0xbfbf00bf, 0x40400040, 0xa3a300a3, 0x9e9e009e,
	0x81810081, 0xf3f300f3, 0xd7d700d7, 0xfbfb00fb,
	0x7c7c007c, 0xe3e300e3, 0x39390039, 0x82820082,
	0x9b9b009b, 0x2f2f002f, 0xffff00ff, 0x87870087,
	0x34340034, 0x8e8e008e, 0x43430043, 0x44440044,
	0xc4c400c4, 0xdede00de, 0xe9e900e9, 0xcbcb00cb,
	0x54540054, 0x7b7b007b, 0x94940094, 0x32320032,
	0xa6a600a6, 0xc2c200c2, 0x23230023, 0x3d3d003d,
	0xeeee00ee, 0x4c4c004c, 0x95950095, 0x0b0b000b,
	0x42420042, 0xfafa00fa, 0xc3c300c3, 0x4e4e004e,
	0x08080008, 0x2e2e002e, 0xa1a100a1, 0x66660066,
	0x28280028, 0xd9d900d9, 0x24240024, 0xb2b200b2,
	0x76760076, 0x5b5b005b, 0xa2a200a2, 0x49490049,
	0x6d6d006d, 0x8b8b008b, 0xd1d100d1, 0x25250025,
	0x72720072, 0xf8f800f8, 0xf6f600f6, 0x64640064,
	0x86860086, 0x68680068, 0x98980098, 0x16160016,
	0xd4d400d4, 0xa4a400a4, 0x5c5c005c, 0xcccc00cc,
	0x5d5d005d, 0x65650065, 0xb6b600b6, 0x92920092,
	0x6c6c006c, 0x70700070, 0x48480048, 0x50500050,
	0xfdfd00fd, 0xeded00ed, 0xb9b900b9, 0xdada00da,
	0x5e5e005e, 0x15150015, 0x46460046, 0x57570057,
	0xa7a700a7, 0x8d8d008d, 0x9d9d009d, 0x84840084,
	0x90900090, 0xd8d800d8, 0xabab00ab, 0x00000000,
	0x8c8c008c, 0xbcbc00bc, 0xd3d300d3, 0x0a0a000a,
	0xf7f700f7, 0xe4e400e4, 0x58580058, 0x05050005,
	0xb8b800b8, 0xb3b300b3, 0x45450045, 0x06060006,
	0xd0d000d0, 0x2c2c002c, 0x1e1e001e, 0x8f8f008f,
	0xcaca00ca, 0x3f3f003f, 0x0f0f000f, 0x02020002,
	0xc1c100c1, 0xafaf00af, 0xbdbd00bd, 0x03030003,
	0x01010001, 0x13130013, 0x8a8a008a, 0x6b6b006b,
	0x3a3a003a, 0x91910091, 0x11110011, 0x41410041,
	0x4f4f004f, 0x67670067, 0xdcdc00dc, 0xeaea00ea,
	0x97970097, 0xf2f200f2, 0xcfcf00cf, 0xcece00ce,
	0xf0f000f0, 0xb4b400b4, 0xe6e600e6, 0x73730073,
	0x96960096, 0xacac00ac, 0x74740074, 0x22220022,
	0xe7e700e7, 0xadad00ad, 0x35350035, 0x85850085,
	0xe2e200e2, 0xf9f900f9, 0x37370037, 0xe8e800e8,
	0x1c1c001c, 0x75750075, 0xdfdf00df, 0x6e6e006e,
	0x47470047, 0xf1f100f1, 0x1a1a001a, 0x71710071,
	0x1d1d001d, 0x29290029, 0xc5c500c5, 0x89890089,
	0x6f6f006f, 0xb7b700b7, 0x62620062, 0x0e0e000e,
	0xaaaa00aa, 0x18180018, 0xbebe00be, 0x1b1b001b,
	0xfcfc00fc, 0x56560056, 0x3e3e003e, 0x4b4b004b,
	0xc6c600c6, 0xd2d200d2, 0x79790079, 0x20200020,
	0x9a9a009a, 0xdbdb00db, 0xc0c000c0, 0xfefe00fe,
	0x78780078, 0xcdcd00cd, 0x5a5a005a, 0xf4f400f4,
	0x1f1f001f, 0xdddd00dd, 0xa8a800a8, 0x33330033,
	0x88880088, 0x07070007, 0xc7c700c7, 0x31310031,
	0xb1b100b1, 0x12120012, 0x10100010, 0x59590059,
	0x27270027, 0x80800080, 0xecec00ec, 0x5f5f005f,
	0x60600060, 0x51510051, 0x7f7f007f, 0xa9a900a9,
	0x19190019, 0xb5b500b5, 0x4a4a004a, 0x0d0d000d,
	0x2d2d002d, 0xe5e500e5, 0x7a7a007a, 0x9f9f009f,
	0x93930093, 0xc9c900c9, 0x9c9c009c, 0xefef00ef,
	0xa0a000a0, 0xe0e000e0, 0x3b3b003b, 0x4d4d004d,
	0xaeae00ae, 0x2a2a002a, 0xf5f500f5, 0xb0b000b0,
	0xc8c800c8, 0xebeb00eb, 0xbbbb00bb, 0x3c3c003c,
	0x83830083, 0x53530053, 0x99990099, 0x61610061,
	0x17170017, 0x2b2b002b, 0x04040004, 0x7e7e007e,
	0xbaba00ba, 0x77770077, 0xd6d600d6, 0x26260026,
	0xe1e100e1, 0x69690069, 0x14140014, 0x63630063,
	0x55550055, 0x21210021, 0x0c0c000c, 0x7d7d007d
};

static const uint32_t x2[256] = {
	0x30303000, 0x68686800, 0x99999900, 0x1b1b1b00,
	0x87878700, 0xb9b9b900, 0x21212100, 0x78787800,
	0x50505000, 0x39393900, 0xdbdbdb00, 0xe1e1e100,
	0x72727200, 0x09090900, 0x62626200, 0x3c3c3c00,
	0x3e3e3e00, 0x7e7e7e00, 0x5e5e5e00, 0x8e8e8e00,
	0xf1f1f100, 0xa0a0a000, 0xcccccc00, 0xa3a3a300,
	0x2a2a2a00, 0x1d1d1d00, 0xfbfbfb00, 0xb6b6b600,
	0xd6d6d600, 0x20202000, 0xc4c4c400, 0x8d8d8d00,
	0x81818100, 0x65656500, 0xf5f5f500, 0x89898900,
	0xcbcbcb00, 0x9d9d9d00, 0x77777700, 0xc6c6c600,
	0x57575700, 0x43434300, 0x56565600, 0x17171700,
	0xd4d4d400, 0x40404000, 0x1a1a1a00, 0x4d4d4d00,
	0xc0c0c000, 0x63636300, 0x6c6c6c00, 0xe3e3e300,
	0xb7b7b700, 0xc8c8c800, 0x64646400, 0x6a6a6a00,
	0x53535300, 0xaaaaaa00, 0x38383800, 0x98989800,
	0x0c0c0c00, 0xf4f4f400, 0x9b9b9b00, 0xededed00,
	0x7f7f7f00, 0x22222200, 0x76767600, 0xafafaf00,
	0xdddddd00, 0x3a3a3a00, 0x0b0b0b00, 0x58585800,
	0x67676700, 0x88888800, 0x06060600, 0xc3c3c300,
	0x35353500, 0x0d0d0d00, 0x01010100, 0x8b8b8b00,
	0x8c8c8c00, 0xc2c2c200, 0xe6e6e600, 0x5f5f5f00,
	0x02020200, 0x24242400, 0x75757500, 0x93939300,
	0x66666600, 0x1e1e1e00, 0xe5e5e500, 0xe2e2e200,
	0x54545400, 0xd8d8d800, 0x10101000, 0xcecece00,
	0x7a7a7a00, 0xe8e8e800, 0x08080800, 0x2c2c2c00,
	0x12121200, 0x97979700, 0x32323200, 0xababab00,
	0xb4b4b400, 0x27272700, 0x0a0a0a00, 0x23232300,
	0xdfdfdf00, 0xefefef00, 0xcacaca00, 0xd9d9d900,
	0xb8b8b800, 0xfafafa00, 0xdcdcdc00, 0x31313100,
	0x6b6b6b00, 0xd1d1d100, 0xadadad00, 0x19191900,
	0x49494900, 0xbdbdbd00, 0x51515100, 0x96969600,
	0xeeeeee00, 0xe4e4e400, 0xa8a8a800, 0x41414100,
	0xdadada00, 0xffffff00, 0xcdcdcd00, 0x55555500,
	0x86868600, 0x36363600, 0xbebebe00, 0x61616100,
	0x52525200, 0xf8f8f800, 0xbbbbbb00, 0x0e0e0e00,
	0x82828200, 0x48484800, 0x69696900, 0x9a9a9a00,
	0xe0e0e000, 0x47474700, 0x9e9e9e00, 0x5c5c5c00,
	0x04040400, 0x4b4b4b00, 0x34343400, 0x15151500,
	0x79797900, 0x26262600, 0xa7a7a700, 0xdedede00,
	0x29292900, 0xaeaeae00, 0x92929200, 0xd7d7d700,
	0x84848400, 0xe9e9e900, 0xd2d2d200, 0xbababa00,
	0x5d5d5d00, 0xf3f3f300, 0xc5c5c500, 0xb0b0b000,
	0xbfbfbf00, 0xa4a4a400, 0x3b3b3b00, 0x71717100,
	0x44444400, 0x46464600, 0x2b2b2b00, 0xfcfcfc00,
	0xebebeb00, 0x6f6f6f00, 0xd5d5d500, 0xf6f6f600,
	0x14141400, 0xfefefe00, 0x7c7c7c00, 0x70707000,
	0x5a5a5a00, 0x7d7d7d00, 0xfdfdfd00, 0x2f2f2f00,
	0x18181800, 0x83838300, 0x16161600, 0xa5a5a500,
	0x91919100, 0x1f1f1f00, 0x05050500, 0x95959500,
	0x74747400, 0xa9a9a900, 0xc1c1c100, 0x5b5b5b00,
	0x4a4a4a00, 0x85858500, 0x6d6d6d00, 0x13131300,
	0x07070700, 0x4f4f4f00, 0x4e4e4e00, 0x45454500,
	0xb2b2b200, 0x0f0f0f00, 0xc9c9c900, 0x1c1c1c00,
	0xa6a6a600, 0xbcbcbc00, 0xececec00, 0x73737300,
	0x90909000, 0x7b7b7b00, 0xcfcfcf00, 0x59595900,
	0x8f8f8f00, 0xa1a1a100, 0xf9f9f900, 0x2d2d2d00,
	0xf2f2f200, 0xb1b1b100, 0x00000000, 0x94949400,
	0x37373700, 0x9f9f9f00, 0xd0d0d000, 0x2e2e2e00,
	0x9c9c9c00, 0x6e6e6e00, 0x28282800, 0x3f3f3f00,
	0x80808000, 0xf0f0f000, 0x3d3d3d00, 0xd3d3d300,
	0x25252500, 0x8a8a8a00, 0xb5b5b500, 0xe7e7e700,
	0x42424200, 0xb3b3b300, 0xc7c7c700, 0xeaeaea00,
	0xf7f7f700, 0x4c4c4c00, 0x11111100, 0x33333300,
	0x03030300, 0xa2a2a200, 0xacacac00, 0x60606000
};

static inline uint32_t rotl32(uint32_t v, uint32_t r)
{
	return ((v << r) | (v >> (32 - r)));
}

static inline uint32_t rotr32(uint32_t v, uint32_t r)
{
	return ((v >> r) | (v << (32 - r)));
}

static inline uint32_t bswap32(uint32_t v)
{
	return ((v << 24) ^
		(v >> 24) ^
		((v & 0x0000ff00) << 8) ^
		((v & 0x00ff0000) >> 8));
}

static inline uint8_t get_uint8_t(uint32_t x, uint32_t y)
{
	return (x >> ((3 - y) * 8));
}

static inline uint32_t make_uint32_t(uint8_t v0, uint8_t v1, uint8_t v2, uint8_t v3)
{
	return ((uint32_t)v0 << 24) | ((uint32_t)v1 << 16) | ((uint32_t)v2 <<  8) | ((uint32_t)v3);
}

static inline uint32_t aria_m(uint32_t t0)
{
	return rotr32(t0, 8) ^ rotr32(t0 ^ rotr32(t0, 8), 16);
}

/* S-Box Layer 1 + M */
static inline void aria_sbox_layer1_with_pre_diff(uint32_t *t0, uint32_t *t1, uint32_t *t2,
						  uint32_t *t3)
{
	*t0 = s1[get_uint8_t(*t0, 0)] ^
	      s2[get_uint8_t(*t0, 1)] ^
	      x1[get_uint8_t(*t0, 2)] ^
	      x2[get_uint8_t(*t0, 3)];
	*t1 = s1[get_uint8_t(*t1, 0)] ^
	      s2[get_uint8_t(*t1, 1)] ^
	      x1[get_uint8_t(*t1, 2)] ^
	      x2[get_uint8_t(*t1, 3)];
	*t2 = s1[get_uint8_t(*t2, 0)] ^
	      s2[get_uint8_t(*t2, 1)] ^
	      x1[get_uint8_t(*t2, 2)] ^
	      x2[get_uint8_t(*t2, 3)];
	*t3 = s1[get_uint8_t(*t3, 0)] ^
	      s2[get_uint8_t(*t3, 1)] ^
	      x1[get_uint8_t(*t3, 2)] ^
	      x2[get_uint8_t(*t3, 3)];
}

/* S-Box Layer 2 + M */
static inline void aria_sbox_layer2_with_pre_diff(uint32_t *t0, uint32_t *t1, uint32_t *t2,
						  uint32_t *t3)
{
	*t0 = x1[get_uint8_t(*t0, 0)] ^
	      x2[get_uint8_t(*t0, 1)] ^
	      s1[get_uint8_t(*t0, 2)] ^
	      s2[get_uint8_t(*t0, 3)];
	*t1 = x1[get_uint8_t(*t1, 0)] ^
	      x2[get_uint8_t(*t1, 1)] ^
	      s1[get_uint8_t(*t1, 2)] ^
	      s2[get_uint8_t(*t1, 3)];
	*t2 = x1[get_uint8_t(*t2, 0)] ^
	      x2[get_uint8_t(*t2, 1)] ^
	      s1[get_uint8_t(*t2, 2)] ^
	      s2[get_uint8_t(*t2, 3)];
	*t3 = x1[get_uint8_t(*t3, 0)] ^
	      x2[get_uint8_t(*t3, 1)] ^
	      s1[get_uint8_t(*t3, 2)] ^
	      s2[get_uint8_t(*t3, 3)];
}

/* Word-level diffusion */
static inline void aria_diff_word(uint32_t *t0, uint32_t *t1, uint32_t *t2, uint32_t *t3)
{
	*t1 ^= *t2;
	*t2 ^= *t3;
	*t0 ^= *t1;

	*t3 ^= *t1;
	*t2 ^= *t0;
	*t1 ^= *t2;
}

/* Byte-level diffusion */
static inline void aria_diff_byte(uint32_t *t1, uint32_t *t2, uint32_t *t3)
{
	*t1 = ((*t1 << 8) & 0xff00ff00) ^ ((*t1 >> 8) & 0x00ff00ff);
	*t2 = rotr32(*t2, 16);
	*t3 = bswap32(*t3);
}

/* Key XOR Layer */
static inline void aria_add_round_key(uint32_t *rk, uint32_t *t0, uint32_t *t1, uint32_t *t2,
				      uint32_t *t3)
{
	*t0 ^= rk[0];
	*t1 ^= rk[1];
	*t2 ^= rk[2];
	*t3 ^= rk[3];
}
/* Odd round Substitution & Diffusion */
static inline void aria_subst_diff_odd(uint32_t *t0, uint32_t *t1, uint32_t *t2, uint32_t *t3)
{
	aria_sbox_layer1_with_pre_diff(t0, t1, t2, t3);
	aria_diff_word(t0, t1, t2, t3);
	aria_diff_byte(t1, t2, t3);
	aria_diff_word(t0, t1, t2, t3);
}

/* Even round Substitution & Diffusion */
static inline void aria_subst_diff_even(uint32_t *t0, uint32_t *t1, uint32_t *t2, uint32_t *t3)
{
	aria_sbox_layer2_with_pre_diff(t0, t1, t2, t3);
	aria_diff_word(t0, t1, t2, t3);
	aria_diff_byte(t3, t0, t1);
	aria_diff_word(t0, t1, t2, t3);
}

/* Q, R Macro expanded ARIA GSRK */
static inline void aria_gsrk(uint32_t *rk, uint32_t *x, uint32_t *y, uint32_t n)
{
	int q = 4 - (n / 32);
	int r = n % 32;

	rk[0] = (x[0]) ^
		((y[q % 4]) >> r) ^
		((y[(q + 3) % 4]) << (32 - r));
	rk[1] = (x[1]) ^
		((y[(q + 1) % 4]) >> r) ^
		((y[q % 4]) << (32 - r));
	rk[2] = (x[2]) ^
		((y[(q + 2) % 4]) >> r) ^
		((y[(q + 1) % 4]) << (32 - r));
	rk[3] =	(x[3]) ^
		((y[(q + 3) % 4]) >> r) ^
		((y[(q + 2) % 4]) << (32 - r));
}

static const uint32_t key_rc[20] = {
	0x517cc1b7, 0x27220a94, 0xfe13abe8, 0xfa9a6ee0,
	0x6db14acc, 0x9e21c820, 0xff28b1d5, 0xef5de2b0,
	0xdb92371d, 0x2126e970, 0x03249775, 0x04e8c90e,
	0x517cc1b7, 0x27220a94, 0xfe13abe8, 0xfa9a6ee0,
	0x6db14acc, 0x9e21c820, 0xff28b1d5, 0xef5de2b0
};

void aria_set_encrypt_key(struct aria_ctx *ctx, const uint8_t *in_key,
				 unsigned int key_len)
{
	const __be32 *key = (const __be32 *)in_key;
	uint32_t w0[4], w1[4], w2[4], w3[4];
	uint32_t reg0, reg1, reg2, reg3;
	const uint32_t *ck;
	int rkidx = 0;

    ctx->key_length = key_len;
	ctx->rounds = (key_len + 32) / 4;

	ck = &key_rc[(key_len - 16) / 2];

	w0[0] = be32_to_cpu(key[0]);
	w0[1] = be32_to_cpu(key[1]);
	w0[2] = be32_to_cpu(key[2]);
	w0[3] = be32_to_cpu(key[3]);

	reg0 = w0[0] ^ ck[0];
	reg1 = w0[1] ^ ck[1];
	reg2 = w0[2] ^ ck[2];
	reg3 = w0[3] ^ ck[3];

	aria_subst_diff_odd(&reg0, &reg1, &reg2, &reg3);

	if (key_len > 16) {
		w1[0] = be32_to_cpu(key[4]);
		w1[1] = be32_to_cpu(key[5]);
		if (key_len > 24) {
			w1[2] = be32_to_cpu(key[6]);
			w1[3] = be32_to_cpu(key[7]);
		} else {
			w1[2] = 0;
			w1[3] = 0;
		}
	} else {
		w1[0] = 0;
		w1[1] = 0;
		w1[2] = 0;
		w1[3] = 0;
	}

	w1[0] ^= reg0;
	w1[1] ^= reg1;
	w1[2] ^= reg2;
	w1[3] ^= reg3;

	reg0 = w1[0];
	reg1 = w1[1];
	reg2 = w1[2];
	reg3 = w1[3];

	reg0 ^= ck[4];
	reg1 ^= ck[5];
	reg2 ^= ck[6];
	reg3 ^= ck[7];

	aria_subst_diff_even(&reg0, &reg1, &reg2, &reg3);

	reg0 ^= w0[0];
	reg1 ^= w0[1];
	reg2 ^= w0[2];
	reg3 ^= w0[3];

	w2[0] = reg0;
	w2[1] = reg1;
	w2[2] = reg2;
	w2[3] = reg3;

	reg0 ^= ck[8];
	reg1 ^= ck[9];
	reg2 ^= ck[10];
	reg3 ^= ck[11];

	aria_subst_diff_odd(&reg0, &reg1, &reg2, &reg3);

	w3[0] = reg0 ^ w1[0];
	w3[1] = reg1 ^ w1[1];
	w3[2] = reg2 ^ w1[2];
	w3[3] = reg3 ^ w1[3];

	aria_gsrk(ctx->enc_key[rkidx], w0, w1, 19);
	rkidx++;
	aria_gsrk(ctx->enc_key[rkidx], w1, w2, 19);
	rkidx++;
	aria_gsrk(ctx->enc_key[rkidx], w2, w3, 19);
	rkidx++;
	aria_gsrk(ctx->enc_key[rkidx], w3, w0, 19);

	rkidx++;
	aria_gsrk(ctx->enc_key[rkidx], w0, w1, 31);
	rkidx++;
	aria_gsrk(ctx->enc_key[rkidx], w1, w2, 31);
	rkidx++;
	aria_gsrk(ctx->enc_key[rkidx], w2, w3, 31);
	rkidx++;
	aria_gsrk(ctx->enc_key[rkidx], w3, w0, 31);

	rkidx++;
	aria_gsrk(ctx->enc_key[rkidx], w0, w1, 67);
	rkidx++;
	aria_gsrk(ctx->enc_key[rkidx], w1, w2, 67);
	rkidx++;
	aria_gsrk(ctx->enc_key[rkidx], w2, w3, 67);
	rkidx++;
	aria_gsrk(ctx->enc_key[rkidx], w3, w0, 67);

	rkidx++;
	aria_gsrk(ctx->enc_key[rkidx], w0, w1, 97);
	if (key_len > 16) {
		rkidx++;
		aria_gsrk(ctx->enc_key[rkidx], w1, w2, 97);
		rkidx++;
		aria_gsrk(ctx->enc_key[rkidx], w2, w3, 97);

		if (key_len > 24) {
			rkidx++;
			aria_gsrk(ctx->enc_key[rkidx], w3, w0, 97);

			rkidx++;
			aria_gsrk(ctx->enc_key[rkidx], w0, w1, 109);
		}
	}
}

static void aria_set_decrypt_key(struct aria_ctx *ctx)
{
	int i;

	for (i = 0; i < 4; i++) {
		ctx->dec_key[0][i] = ctx->enc_key[ctx->rounds][i];
		ctx->dec_key[ctx->rounds][i] = ctx->enc_key[0][i];
	}

	for (i = 1; i < ctx->rounds; i++) {
		ctx->dec_key[i][0] = aria_m(ctx->enc_key[ctx->rounds - i][0]);
		ctx->dec_key[i][1] = aria_m(ctx->enc_key[ctx->rounds - i][1]);
		ctx->dec_key[i][2] = aria_m(ctx->enc_key[ctx->rounds - i][2]);
		ctx->dec_key[i][3] = aria_m(ctx->enc_key[ctx->rounds - i][3]);

		aria_diff_word(&ctx->dec_key[i][0], &ctx->dec_key[i][1],
			       &ctx->dec_key[i][2], &ctx->dec_key[i][3]);
		aria_diff_byte(&ctx->dec_key[i][1],
			       &ctx->dec_key[i][2], &ctx->dec_key[i][3]);
		aria_diff_word(&ctx->dec_key[i][0], &ctx->dec_key[i][1],
			       &ctx->dec_key[i][2], &ctx->dec_key[i][3]);
	}
}

int aria_set_key(struct crypto_tfm *tfm, const uint8_t *in_key, unsigned int key_len)
{
	struct aria_ctx *ctx = crypto_tfm_ctx(tfm);

	if (key_len != 16 && key_len != 24 && key_len != 32)
		return -EINVAL;

	ctx->key_length = key_len;
	ctx->rounds = (key_len + 32) / 4;

	aria_set_encrypt_key(ctx, in_key, key_len);
	aria_set_decrypt_key(ctx);

	return 0;
}

static void __aria_crypt(struct aria_ctx *ctx, uint8_t *out, const uint8_t *in,
			 uint32_t key[][ARIA_RD_KEY_WORDS])
{
	const __be32 *src = (const __be32 *)in;
	__be32 *dst = (__be32 *)out;
	uint32_t reg0, reg1, reg2, reg3;
	int rounds, rkidx = 0;

	rounds = ctx->rounds;

	reg0 = be32_to_cpu(src[0]);
	reg1 = be32_to_cpu(src[1]);
	reg2 = be32_to_cpu(src[2]);
	reg3 = be32_to_cpu(src[3]);

	aria_add_round_key(key[rkidx], &reg0, &reg1, &reg2, &reg3);
	rkidx++;

	aria_subst_diff_odd(&reg0, &reg1, &reg2, &reg3);
	aria_add_round_key(key[rkidx], &reg0, &reg1, &reg2, &reg3);
	rkidx++;

	while ((rounds -= 2) > 0) {
		aria_subst_diff_even(&reg0, &reg1, &reg2, &reg3);
		aria_add_round_key(key[rkidx], &reg0, &reg1, &reg2, &reg3);
		rkidx++;

		aria_subst_diff_odd(&reg0, &reg1, &reg2, &reg3);
		aria_add_round_key(key[rkidx], &reg0, &reg1, &reg2, &reg3);
		rkidx++;
	}

	reg0 = key[rkidx][0] ^ make_uint32_t((uint8_t)(x1[get_uint8_t(reg0, 0)]),
					(uint8_t)(x2[get_uint8_t(reg0, 1)] >> 8),
					(uint8_t)(s1[get_uint8_t(reg0, 2)]),
					(uint8_t)(s2[get_uint8_t(reg0, 3)]));
	reg1 = key[rkidx][1] ^ make_uint32_t((uint8_t)(x1[get_uint8_t(reg1, 0)]),
					(uint8_t)(x2[get_uint8_t(reg1, 1)] >> 8),
					(uint8_t)(s1[get_uint8_t(reg1, 2)]),
					(uint8_t)(s2[get_uint8_t(reg1, 3)]));
	reg2 = key[rkidx][2] ^ make_uint32_t((uint8_t)(x1[get_uint8_t(reg2, 0)]),
					(uint8_t)(x2[get_uint8_t(reg2, 1)] >> 8),
					(uint8_t)(s1[get_uint8_t(reg2, 2)]),
					(uint8_t)(s2[get_uint8_t(reg2, 3)]));
	reg3 = key[rkidx][3] ^ make_uint32_t((uint8_t)(x1[get_uint8_t(reg3, 0)]),
					(uint8_t)(x2[get_uint8_t(reg3, 1)] >> 8),
					(uint8_t)(s1[get_uint8_t(reg3, 2)]),
					(uint8_t)(s2[get_uint8_t(reg3, 3)]));

	dst[0] = cpu_to_be32(reg0);
	dst[1] = cpu_to_be32(reg1);
	dst[2] = cpu_to_be32(reg2);
	dst[3] = cpu_to_be32(reg3);
}

void aria_encrypt(void *_ctx, uint8_t *out, const uint8_t *in)
{
	struct aria_ctx *ctx = (struct aria_ctx *)_ctx;

	__aria_crypt(ctx, out, in, ctx->enc_key);
}

void aria_decrypt(void *_ctx, uint8_t *out, const uint8_t *in)
{
	struct aria_ctx *ctx = (struct aria_ctx *)_ctx;

	__aria_crypt(ctx, out, in, ctx->dec_key);
}

static inline void increment_uint128(uint32_t num[4]) {
    int carry = 1;
    for (int i = 3; i >= 0; i--) {
        uint64_t temp = (uint64_t)num[i] + carry;
        num[i] = (uint32_t)temp;
        carry = temp >> 32;
    }
}

void aria_ctr_encrypt(void *_ctx, uint8_t *out, const uint8_t *in, size_t _len, void* icb) {
    struct aria_ctx *ctx = (struct aria_ctx *)_ctx;
    ssize_t len = (ssize_t) _len;
    size_t counter = 0;

    while ((len -= 0x10) > 0) {
        aria_encrypt(ctx, out + (counter*0x10), in + (counter*0x10));
        increment_uint128(icb);
        counter++;
    }
}



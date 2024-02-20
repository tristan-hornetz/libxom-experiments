/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Camellia Cipher Algorithm (x86_64)
 *
 * Copyright (C) 2012 Jussi Kivilinna <jussi.kivilinna@mbnet.fi>
 */
/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_X86_FRAME_H
#define _ASM_X86_FRAME_H

#define CONFIG_FUNCTION_ALIGNMENT 128

/*
 * These are stack frame creation macros.  They should be used by every
 * callable non-leaf asm function to make kernel stack traces more reliable.
 */

#ifdef CONFIG_FRAME_POINTER

#ifdef __ASSEMBLY__

.macro FRAME_BEGIN
	push %_ASM_BP
	_ASM_MOV %_ASM_SP, %_ASM_BP
.endm

.macro FRAME_END
	pop %_ASM_BP
.endm

#ifdef CONFIG_X86_64
/*
 * This is a sneaky trick to help the unwinder find pt_regs on the stack.  The
 * frame pointer is replaced with an encoded pointer to pt_regs.  The encoding
 * is just setting the LSB, which makes it an invalid stack address and is also
 * a signal to the unwinder that it's a pt_regs pointer in disguise.
 *
 * NOTE: This macro must be used *after* PUSH_AND_CLEAR_REGS because it corrupts
 * the original rbp.
 */
.macro ENCODE_FRAME_POINTER ptregs_offset=0
	leaq 1+\ptregs_offset(%rsp), %rbp
.endm
#else /* !CONFIG_X86_64 */
/*
 * This is a sneaky trick to help the unwinder find pt_regs on the stack.  The
 * frame pointer is replaced with an encoded pointer to pt_regs.  The encoding
 * is just clearing the MSB, which makes it an invalid stack address and is also
 * a signal to the unwinder that it's a pt_regs pointer in disguise.
 *
 * NOTE: This macro must be used *after* SAVE_ALL because it corrupts the
 * original ebp.
 */
.macro ENCODE_FRAME_POINTER
	mov %esp, %ebp
	andl $0x7fffffff, %ebp
.endm
#endif /* CONFIG_X86_64 */

#else /* !__ASSEMBLY__ */

#define FRAME_BEGIN				\
	"push %" _ASM_BP "\n"			\
	_ASM_MOV "%" _ASM_SP ", %" _ASM_BP "\n"

#define FRAME_END "pop %" _ASM_BP "\n"

#ifdef CONFIG_X86_64

#define ENCODE_FRAME_POINTER			\
	"lea 1(%rsp), %rbp\n\t"

static inline unsigned long encode_frame_pointer(struct pt_regs *regs)
{
	return (unsigned long)regs + 1;
}

#else /* !CONFIG_X86_64 */

#define ENCODE_FRAME_POINTER			\
	"movl %esp, %ebp\n\t"			\
	"andl $0x7fffffff, %ebp\n\t"

static inline unsigned long encode_frame_pointer(struct pt_regs *regs)
{
	return (unsigned long)regs & 0x7fffffff;
}

#endif /* CONFIG_X86_64 */

#endif /* __ASSEMBLY__ */

#define FRAME_OFFSET __ASM_SEL(4, 8)

#else /* !CONFIG_FRAME_POINTER */


.macro ENCODE_FRAME_POINTER ptregs_offset=0
.endm


#define FRAME_BEGIN
#define FRAME_END
#define FRAME_OFFSET 0

#endif /* CONFIG_FRAME_POINTER */

#endif /* _ASM_X86_FRAME_H */

/* SPDX-License-Identifier: GPL-2.0 */

#define ENDBR endbr64

#ifndef _ASM_X86_NOSPEC_BRANCH_H_
#define _ASM_X86_NOSPEC_BRANCH_H_


/*
 * Call depth tracking for Intel SKL CPUs to address the RSB underflow
 * issue in software.
 *
 * The tracking does not use a counter. It uses uses arithmetic shift
 * right on call entry and logical shift left on return.
 *
 * The depth tracking variable is initialized to 0x8000.... when the call
 * depth is zero. The arithmetic shift right sign extends the MSB and
 * saturates after the 12th call. The shift count is 5 for both directions
 * so the tracking covers 12 nested calls.
 *
 *  Call
 *  0: 0x8000000000000000	0x0000000000000000
 *  1: 0xfc00000000000000	0xf000000000000000
 * ...
 * 11: 0xfffffffffffffff8	0xfffffffffffffc00
 * 12: 0xffffffffffffffff	0xffffffffffffffe0
 *
 * After a return buffer fill the depth is credited 12 calls before the
 * next stuffing has to take place.
 *
 * There is a inaccuracy for situations like this:
 *
 *  10 calls
 *   5 returns
 *   3 calls
 *   4 returns
 *   3 calls
 *   ....
 *
 * The shift count might cause this to be off by one in either direction,
 * but there is still a cushion vs. the RSB depth. The algorithm does not
 * claim to be perfect and it can be speculated around by the CPU, but it
 * is considered that it obfuscates the problem enough to make exploitation
 * extremely difficult.
 */
#define RET_DEPTH_SHIFT			5
#define RSB_RET_STUFF_LOOPS		16
#define RET_DEPTH_INIT			0x8000000000000000ULL
#define RET_DEPTH_INIT_FROM_CALL	0xfc00000000000000ULL
#define RET_DEPTH_CREDIT		0xffffffffffffffffULL

#ifdef CONFIG_CALL_THUNKS_DEBUG
# define CALL_THUNKS_DEBUG_INC_CALLS				\
	incq	%gs:__x86_call_count;
# define CALL_THUNKS_DEBUG_INC_RETS				\
	incq	%gs:__x86_ret_count;
# define CALL_THUNKS_DEBUG_INC_STUFFS				\
	incq	%gs:__x86_stuffs_count;
# define CALL_THUNKS_DEBUG_INC_CTXSW				\
	incq	%gs:__x86_ctxsw_count;
#else
# define CALL_THUNKS_DEBUG_INC_CALLS
# define CALL_THUNKS_DEBUG_INC_RETS
# define CALL_THUNKS_DEBUG_INC_STUFFS
# define CALL_THUNKS_DEBUG_INC_CTXSW
#endif

#if defined(CONFIG_CALL_DEPTH_TRACKING) && !defined(COMPILE_OFFSETS)

#include <asm/asm-offsets.h>

#define CREDIT_CALL_DEPTH					\
	movq	$-1, PER_CPU_VAR(pcpu_hot + X86_call_depth);

#define ASM_CREDIT_CALL_DEPTH					\
	movq	$-1, PER_CPU_VAR(pcpu_hot + X86_call_depth);

#define RESET_CALL_DEPTH					\
	xor	%eax, %eax;					\
	bts	$63, %rax;					\
	movq	%rax, PER_CPU_VAR(pcpu_hot + X86_call_depth);

#define RESET_CALL_DEPTH_FROM_CALL				\
	movb	$0xfc, %al;					\
	shl	$56, %rax;					\
	movq	%rax, PER_CPU_VAR(pcpu_hot + X86_call_depth);	\
	CALL_THUNKS_DEBUG_INC_CALLS

#define INCREMENT_CALL_DEPTH					\
	sarq	$5, %gs:pcpu_hot + X86_call_depth;		\
	CALL_THUNKS_DEBUG_INC_CALLS

#define ASM_INCREMENT_CALL_DEPTH				\
	sarq	$5, PER_CPU_VAR(pcpu_hot + X86_call_depth);	\
	CALL_THUNKS_DEBUG_INC_CALLS

#else
#define CREDIT_CALL_DEPTH
#define ASM_CREDIT_CALL_DEPTH
#define RESET_CALL_DEPTH
#define INCREMENT_CALL_DEPTH
#define ASM_INCREMENT_CALL_DEPTH
#define RESET_CALL_DEPTH_FROM_CALL
#endif

/*
 * Fill the CPU return stack buffer.
 *
 * Each entry in the RSB, if used for a speculative 'ret', contains an
 * infinite 'pause; lfence; jmp' loop to capture speculative execution.
 *
 * This is required in various cases for retpoline and IBRS-based
 * mitigations for the Spectre variant 2 vulnerability. Sometimes to
 * eliminate potentially bogus entries from the RSB, and sometimes
 * purely to ensure that it doesn't get empty, which on some CPUs would
 * allow predictions from other (unwanted!) sources to be used.
 *
 * We define a CPP macro such that it can be used from both .S files and
 * inline assembly. It's possible to do a .macro and then include that
 * from C via asm(".include <asm/nospec-branch.h>") but let's not go there.
 */

#define RETPOLINE_THUNK_SIZE	32
#define RSB_CLEAR_LOOPS		32	/* To forcibly overwrite all entries */

/*
 * Common helper for __FILL_RETURN_BUFFER and __FILL_ONE_RETURN.
 */
#define __FILL_RETURN_SLOT			\
	ANNOTATE_INTRA_FUNCTION_CALL;		\
	call	772f;				\
	int3;					\
772:

/*
 * Stuff the entire RSB.
 *
 * Google experimented with loop-unrolling and this turned out to be
 * the optimal version - two calls, each with their own speculation
 * trap should their return address end up getting used, in a loop.
 */
#ifdef CONFIG_X86_64
#define __FILL_RETURN_BUFFER(reg, nr)			\
	mov	$(nr/2), reg;				\
771:							\
	__FILL_RETURN_SLOT				\
	__FILL_RETURN_SLOT				\
	add	$(BITS_PER_LONG/8) * 2, %_ASM_SP;	\
	dec	reg;					\
	jnz	771b;					\
	/* barrier for jnz misprediction */		\
	lfence;						\
	ASM_CREDIT_CALL_DEPTH				\
	CALL_THUNKS_DEBUG_INC_CTXSW
#else
/*
 * i386 doesn't unconditionally have LFENCE, as such it can't
 * do a loop.
 */
#define __FILL_RETURN_BUFFER(reg, nr)			\
	.rept nr;					\
	__FILL_RETURN_SLOT;				\
	.endr;						\
	add	$(BITS_PER_LONG/8) * nr, %_ASM_SP;
#endif

/*
 * Stuff a single RSB slot.
 *
 * To mitigate Post-Barrier RSB speculation, one CALL instruction must be
 * forced to retire before letting a RET instruction execute.
 *
 * On PBRSB-vulnerable CPUs, it is not safe for a RET to be executed
 * before this point.
 */
#define __FILL_ONE_RETURN				\
	__FILL_RETURN_SLOT				\
	add	$(BITS_PER_LONG/8), %_ASM_SP;		\
	lfence;


/*
 * This should be used immediately before an indirect jump/call. It tells
 * objtool the subsequent indirect jump/call is vouched safe for retpoline
 * builds.
 */
.macro ANNOTATE_RETPOLINE_SAFE
.Lhere_\@:
	.pushsection .discard.retpoline_safe
	.long .Lhere_\@
	.popsection
.endm

/*
 * (ab)use RETPOLINE_SAFE on RET to annotate away 'bare' RET instructions
 * vs RETBleed validation.
 */
#define ANNOTATE_UNRET_SAFE ANNOTATE_RETPOLINE_SAFE

/*
 * Abuse ANNOTATE_RETPOLINE_SAFE on a NOP to indicate UNRET_END, should
 * eventually turn into its own annotation.
 */
.macro VALIDATE_UNRET_END
#if defined(CONFIG_NOINSTR_VALIDATION) && \
	(defined(CONFIG_CPU_UNRET_ENTRY) || defined(CONFIG_CPU_SRSO))
	ANNOTATE_RETPOLINE_SAFE
	nop
#endif
.endm

/*
 * Equivalent to -mindirect-branch-cs-prefix; emit the 5 byte jmp/call
 * to the retpoline thunk with a CS prefix when the register requires
 * a RAX prefix byte to encode. Also see apply_retpolines().
 */
.macro __CS_PREFIX reg:req
	.irp rs,r8,r9,r10,r11,r12,r13,r14,r15
	.ifc \reg,\rs
	.byte 0x2e
	.endif
	.endr
.endm

/*
 * JMP_NOSPEC and CALL_NOSPEC macros can be used instead of a simple
 * indirect jmp/call which may be susceptible to the Spectre variant 2
 * attack.
 *
 * NOTE: these do not take kCFI into account and are thus not comparable to C
 * indirect calls, take care when using. The target of these should be an ENDBR
 * instruction irrespective of kCFI.
 */
.macro JMP_NOSPEC reg:req
#ifdef CONFIG_RETPOLINE
	__CS_PREFIX \reg
	jmp	__x86_indirect_thunk_\reg
#else
	jmp	*%\reg
	int3
#endif
.endm

.macro CALL_NOSPEC reg:req
#ifdef CONFIG_RETPOLINE
	__CS_PREFIX \reg
	call	__x86_indirect_thunk_\reg
#else
	call	*%\reg
#endif
.endm

 /*
  * A simpler FILL_RETURN_BUFFER macro. Don't make people use the CPP
  * monstrosity above, manually.
  */
.macro FILL_RETURN_BUFFER reg:req nr:req ftr:req ftr2=ALT_NOT(X86_FEATURE_ALWAYS)
	ALTERNATIVE_2 "jmp .Lskip_rsb_\@", \
		__stringify(__FILL_RETURN_BUFFER(\reg,\nr)), \ftr, \
		__stringify(nop;nop;__FILL_ONE_RETURN), \ftr2

.Lskip_rsb_\@:
.endm

#if defined(CONFIG_CPU_UNRET_ENTRY) || defined(CONFIG_CPU_SRSO)
#define CALL_UNTRAIN_RET	"call entry_untrain_ret"
#else
#define CALL_UNTRAIN_RET	""
#endif

/*
 * Mitigate RETBleed for AMD/Hygon Zen uarch. Requires KERNEL CR3 because the
 * return thunk isn't mapped into the userspace tables (then again, AMD
 * typically has NO_MELTDOWN).
 *
 * While retbleed_untrain_ret() doesn't clobber anything but requires stack,
 * entry_ibpb() will clobber AX, CX, DX.
 *
 * As such, this must be placed after every *SWITCH_TO_KERNEL_CR3 at a point
 * where we have a stack but before any RET instruction.
 */
.macro __UNTRAIN_RET ibpb_feature, call_depth_insns
#if defined(CONFIG_RETHUNK) || defined(CONFIG_CPU_IBPB_ENTRY)
	VALIDATE_UNRET_END
	ALTERNATIVE_3 "",						\
		      CALL_UNTRAIN_RET, X86_FEATURE_UNRET,		\
		      "call entry_ibpb", \ibpb_feature,			\
		     __stringify(\call_depth_insns), X86_FEATURE_CALL_DEPTH
#endif
.endm

#define UNTRAIN_RET \
	__UNTRAIN_RET X86_FEATURE_ENTRY_IBPB, __stringify(RESET_CALL_DEPTH)

#define UNTRAIN_RET_VM \
	__UNTRAIN_RET X86_FEATURE_IBPB_ON_VMEXIT, __stringify(RESET_CALL_DEPTH)

#define UNTRAIN_RET_FROM_CALL \
	__UNTRAIN_RET X86_FEATURE_ENTRY_IBPB, __stringify(RESET_CALL_DEPTH_FROM_CALL)


.macro CALL_DEPTH_ACCOUNT
#ifdef CONFIG_CALL_DEPTH_TRACKING
	ALTERNATIVE "",							\
		    __stringify(ASM_INCREMENT_CALL_DEPTH), X86_FEATURE_CALL_DEPTH
#endif
.endm

#endif /* _ASM_X86_NOSPEC_BRANCH_H_ */

/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_X86_LINKAGE_H
#define _ASM_X86_LINKAGE_H


#undef notrace
#define notrace __attribute__((no_instrument_function))

#ifdef CONFIG_64BIT
/*
 * The generic version tends to create spurious ENDBR instructions under
 * certain conditions.
 */
#define _THIS_IP_ ({ unsigned long __here; asm ("lea 0(%%rip), %0" : "=r" (__here)); __here; })
#endif

#ifdef CONFIG_X86_32
#define asmlinkage CPP_ASMLINKAGE __attribute__((regparm(0)))
#endif /* CONFIG_X86_32 */

#define __ALIGN		.balign CONFIG_FUNCTION_ALIGNMENT, 0x90;
#define __ALIGN_STR	__stringify(__ALIGN)

#if defined(CONFIG_CALL_PADDING) && !defined(__DISABLE_EXPORTS) && !defined(BUILD_VDSO)
#define FUNCTION_PADDING	.skip CONFIG_FUNCTION_ALIGNMENT, 0x90;
#else
#define FUNCTION_PADDING
#endif

#if (CONFIG_FUNCTION_ALIGNMENT > 8) && !defined(__DISABLE_EXPORTS) && !defined(BUILD_VDSO)
# define __FUNC_ALIGN		__ALIGN; FUNCTION_PADDING
#else
# define __FUNC_ALIGN		__ALIGN
#endif

#define ASM_FUNC_ALIGN		__stringify(__FUNC_ALIGN)
#define SYM_F_ALIGN		__FUNC_ALIGN

#ifdef __ASSEMBLY__

#if defined(CONFIG_RETHUNK) && !defined(__DISABLE_EXPORTS) && !defined(BUILD_VDSO)
#define RET	jmp __x86_return_thunk
#else /* CONFIG_RETPOLINE */
#ifdef CONFIG_SLS
#define RET	ret; int3
#else
#define RET	ret
#endif
#endif /* CONFIG_RETPOLINE */

#else /* __ASSEMBLY__ */

#if defined(CONFIG_RETHUNK) && !defined(__DISABLE_EXPORTS) && !defined(BUILD_VDSO)
#define ASM_RET	"jmp __x86_return_thunk\n\t"
#else /* CONFIG_RETPOLINE */
#ifdef CONFIG_SLS
#define ASM_RET	"ret; int3\n\t"
#else
#define ASM_RET	"ret\n\t"
#endif
#endif /* CONFIG_RETPOLINE */

#endif /* __ASSEMBLY__ */

/*
 * Depending on -fpatchable-function-entry=N,N usage (CONFIG_CALL_PADDING) the
 * CFI symbol layout changes.
 *
 * Without CALL_THUNKS:
 *
 * 	.align	FUNCTION_ALIGNMENT
 * __cfi_##name:
 * 	.skip	FUNCTION_PADDING, 0x90
 * 	.byte   0xb8
 * 	.long	__kcfi_typeid_##name
 * name:
 *
 * With CALL_THUNKS:
 *
 * 	.align FUNCTION_ALIGNMENT
 * __cfi_##name:
 * 	.byte	0xb8
 * 	.long	__kcfi_typeid_##name
 * 	.skip	FUNCTION_PADDING, 0x90
 * name:
 *
 * In both cases the whole thing is FUNCTION_ALIGNMENT aligned and sized.
 */

#ifdef CONFIG_CALL_PADDING
#define CFI_PRE_PADDING
#define CFI_POST_PADDING	.skip	CONFIG_FUNCTION_PADDING_BYTES, 0x90;
#else
#define CFI_PRE_PADDING		.skip	CONFIG_FUNCTION_PADDING_BYTES, 0x90;
#define CFI_POST_PADDING
#endif

#define __CFI_TYPE(name)					\
	SYM_START(__cfi_##name, SYM_L_LOCAL, SYM_A_NONE)	\
	CFI_PRE_PADDING						\
	.byte 0xb8 ASM_NL					\
	.long __kcfi_typeid_##name ASM_NL			\
	CFI_POST_PADDING					\
	SYM_FUNC_END(__cfi_##name)

/* UML needs to be able to override memcpy() and friends for KASAN. */
#ifdef CONFIG_UML
# define SYM_FUNC_ALIAS_MEMFUNC	SYM_FUNC_ALIAS_WEAK
#else
# define SYM_FUNC_ALIAS_MEMFUNC	SYM_FUNC_ALIAS
#endif

/* SYM_TYPED_FUNC_START -- use for indirectly called globals, w/ CFI type */
#define SYM_TYPED_FUNC_START(name)				\
	SYM_TYPED_START(name, SYM_L_GLOBAL, SYM_F_ALIGN)	\
	ENDBR

/* SYM_FUNC_START -- use for global functions */
#define SYM_FUNC_START(name)				\
	SYM_START(name, SYM_L_GLOBAL, SYM_F_ALIGN)	\
	ENDBR

/* SYM_FUNC_START_NOALIGN -- use for global functions, w/o alignment */
#define SYM_FUNC_START_NOALIGN(name)			\
	SYM_START(name, SYM_L_GLOBAL, SYM_A_NONE)	\
	ENDBR

/* SYM_FUNC_START_LOCAL -- use for local functions */
#define SYM_FUNC_START_LOCAL(name)			\
	SYM_START(name, SYM_L_LOCAL, SYM_F_ALIGN)	\
	ENDBR

/* SYM_FUNC_START_LOCAL_NOALIGN -- use for local functions, w/o alignment */
#define SYM_FUNC_START_LOCAL_NOALIGN(name)		\
	SYM_START(name, SYM_L_LOCAL, SYM_A_NONE)	\
	ENDBR

/* SYM_FUNC_START_WEAK -- use for weak functions */
#define SYM_FUNC_START_WEAK(name)			\
	SYM_START(name, SYM_L_WEAK, SYM_F_ALIGN)	\
	ENDBR

/* SYM_FUNC_START_WEAK_NOALIGN -- use for weak functions, w/o alignment */
#define SYM_FUNC_START_WEAK_NOALIGN(name)		\
	SYM_START(name, SYM_L_WEAK, SYM_A_NONE)		\
	ENDBR

#endif /* _ASM_X86_LINKAGE_H */

/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Implement AES algorithm in Intel AES-NI instructions.
 *
 * The white paper of AES-NI instructions can be downloaded from:
 *   http://softwarecommunity.intel.com/isn/downloads/intelavx/AES-Instructions-Set_WP.pdf
 *
 * Copyright (C) 2008, Intel Corp.
 *    Author: Huang Ying <ying.huang@intel.com>
 *            Vinodh Gopal <vinodh.gopal@intel.com>
 *            Kahraman Akdemir
 *
 * Added RFC4106 AES-GCM support for 128-bit keys under the AEAD
 * interface for 64-bit kernels.
 *    Authors: Erdinc Ozturk (erdinc.ozturk@intel.com)
 *             Aidan O'Mahony (aidan.o.mahony@intel.com)
 *             Adrian Hoban <adrian.hoban@intel.com>
 *             James Guilford (james.guilford@intel.com)
 *             Gabriele Paoloni <gabriele.paoloni@intel.com>
 *             Tadeusz Struk (tadeusz.struk@intel.com)
 *             Wajdi Feghali (wajdi.k.feghali@intel.com)
 *    Copyright (c) 2010, Intel Corporation.
 *
 * Ported x86_64 version to x86:
 *    Author: Mathias Krause <minipli@googlemail.com>
 */

//#include <linux/linkage.h>
//#include <asm/frame.h>
//#include <asm/nospec-branch.h>

/*
 * The following macros are used to move an (un)aligned 16 byte value to/from
 * an XMM register.  This can done for either FP or integer values, for FP use
 * movaps (move aligned packed single) or integer use movdqa (move double quad
 * aligned).  It doesn't make a performance difference which instruction is used
 * since Nehalem (original Core i7) was released.  However, the movaps is a byte
 * shorter, so that is the one we'll use for now. (same for unaligned).
 */
#define MOVADQ	movaps
#define MOVUDQ	movups

/* Some toolchains use other characters (e.g. '`') to mark new line in macro */
#ifndef ASM_NL
#define ASM_NL		 ;
#endif

#ifdef __cplusplus
#define CPP_ASMLINKAGE extern "C"
#else
#define CPP_ASMLINKAGE
#endif

#ifndef asmlinkage
#define asmlinkage CPP_ASMLINKAGE
#endif

#ifndef cond_syscall
#define cond_syscall(x)	asm(				\
	".weak " __stringify(x) "\n\t"			\
	".set  " __stringify(x) ","			\
		 __stringify(sys_ni_syscall))
#endif

#ifndef SYSCALL_ALIAS
#define SYSCALL_ALIAS(alias, name) asm(			\
	".globl " __stringify(alias) "\n\t"		\
	".set   " __stringify(alias) ","		\
		  __stringify(name))
#endif

#define __page_aligned_data	__section(".data..page_aligned") __aligned(PAGE_SIZE)
#define __page_aligned_bss	__section(".bss..page_aligned") __aligned(PAGE_SIZE)

/*
 * For assembly routines.
 *
 * Note when using these that you must specify the appropriate
 * alignment directives yourself
 */
#define __PAGE_ALIGNED_DATA	.section ".data..page_aligned", "aw"
#define __PAGE_ALIGNED_BSS	.section ".bss..page_aligned", "aw"

/*
 * This is used by architectures to keep arguments on the stack
 * untouched by the compiler by keeping them live until the end.
 * The argument stack may be owned by the assembly-language
 * caller, not the callee, and gcc doesn't always understand
 * that.
 *
 * We have the return value, and a maximum of six arguments.
 *
 * This should always be followed by a "return ret" for the
 * protection to work (ie no more work that the compiler might
 * end up needing stack temporaries for).
 */
/* Assembly files may be compiled with -traditional .. */
#ifndef __ASSEMBLY__
#ifndef asmlinkage_protect
# define asmlinkage_protect(n, ret, args...)	do { } while (0)
#endif
#endif

#ifndef __ALIGN
#define __ALIGN			.balign CONFIG_FUNCTION_ALIGNMENT
#define __ALIGN_STR		__stringify(__ALIGN)
#endif


/* SYM_T_FUNC -- type used by assembler to mark functions */
#ifndef SYM_T_FUNC
#define SYM_T_FUNC				STT_FUNC
#endif

/* SYM_T_OBJECT -- type used by assembler to mark data */
#ifndef SYM_T_OBJECT
#define SYM_T_OBJECT				STT_OBJECT
#endif

/* SYM_T_NONE -- type used by assembler to mark entries of unknown type */
#ifndef SYM_T_NONE
#define SYM_T_NONE				STT_NOTYPE
#endif

/* SYM_A_* -- align the symbol? */
#define SYM_A_ALIGN				ALIGN
#define SYM_A_NONE				/* nothing */

/* SYM_L_* -- linkage of symbols */
#define SYM_L_GLOBAL(name)			.globl name
#define SYM_L_WEAK(name)			.weak name
#define SYM_L_LOCAL(name)			/* nothing */


#ifndef LINKER_SCRIPT
#define ALIGN __ALIGN
#define ALIGN_STR __ALIGN_STR

/* === DEPRECATED annotations === */

#ifndef CONFIG_ARCH_USE_SYM_ANNOTATIONS
#ifndef GLOBAL
/* deprecated, use SYM_DATA*, SYM_ENTRY, or similar */
#define GLOBAL(name) \
	.globl name ASM_NL \
	name:
#endif

#ifndef ENTRY
/* deprecated, use SYM_FUNC_START */
#define ENTRY(name) \
	SYM_FUNC_START(name)
#endif
#endif /* CONFIG_ARCH_USE_SYM_ANNOTATIONS */
#endif /* LINKER_SCRIPT */

/* SYM_ENTRY -- use only if you have to for non-paired symbols */
#ifndef SYM_ENTRY
#define SYM_ENTRY(name, linkage, align...)		\
	linkage(name) ASM_NL				\
	align ASM_NL					\
	name:
#endif

/* SYM_START -- use only if you have to */
#ifndef SYM_START
#define SYM_START(name, linkage, align...)		\
	SYM_ENTRY(name, linkage, align)
#endif

/* SYM_END -- use only if you have to */
#ifndef SYM_END
#define SYM_END(name, sym_type)				\
	.type name sym_type ASM_NL			\
	.set .L__sym_size_##name, .-name ASM_NL		\
	.size name, .L__sym_size_##name
#endif

/* SYM_ALIAS -- use only if you have to */
#ifndef SYM_ALIAS
#define SYM_ALIAS(alias, name, linkage)			\
	linkage(alias) ASM_NL				\
	.set alias, name ASM_NL
#endif

#ifndef SYM_FUNC_START
#define SYM_FUNC_START(name)				\
	SYM_START(name, SYM_L_GLOBAL, SYM_A_ALIGN)
#endif

#ifndef SYM_FUNC_END
#define SYM_FUNC_END(name)				\
	SYM_END(name, SYM_T_FUNC)
#endif

#ifndef SYM_FUNC_ALIAS_LOCAL
#define SYM_FUNC_ALIAS_LOCAL(alias, name)				\
	SYM_ALIAS(alias, name, SYM_L_LOCAL)
#endif

.file "camellia-x86_64-asm_64.S"
.text

.extern camellia_sp10011110;
.extern camellia_sp22000222;
.extern camellia_sp03303033;
.extern camellia_sp00444404;
.extern camellia_sp02220222;
.extern camellia_sp30333033;
.extern camellia_sp44044404;
.extern camellia_sp11101110;

#define sp10011110 camellia_sp10011110
#define sp22000222 camellia_sp22000222
#define sp03303033 camellia_sp03303033
#define sp00444404 camellia_sp00444404
#define sp02220222 camellia_sp02220222
#define sp30333033 camellia_sp30333033
#define sp44044404 camellia_sp44044404
#define sp11101110 camellia_sp11101110

#define CAMELLIA_TABLE_BYTE_LEN 272

/* struct camellia_ctx: */
#define key_table 0
#define key_length CAMELLIA_TABLE_BYTE_LEN

/* register macros */
#define CTX %rdi
#define RIO %rsi
#define RIOd %esi

#define RAB0 %rax
#define RCD0 %rcx
#define RAB1 %rbx
#define RCD1 %rdx

#define RAB0d %eax
#define RCD0d %ecx
#define RAB1d %ebx
#define RCD1d %edx

#define RAB0bl %al
#define RCD0bl %cl
#define RAB1bl %bl
#define RCD1bl %dl

#define RAB0bh %ah
#define RCD0bh %ch
#define RAB1bh %bh
#define RCD1bh %dh

#define RT0 %rsi
#define RT1 %r12
#define RT2 %r8

#define RT0d %esi
#define RT1d %r12d
#define RT2d %r8d

#define RT2bl %r8b

#define RXOR %r9
#define RR12 %r10
#define RDST %r11

#define RXORd %r9d
#define RXORbl %r9b

#define xor2ror16(T0, T1, tmp1, tmp2, ab, dst) \
	leaq T0(%rip), 			tmp1; \
	movzbl ab ## bl,		tmp2 ## d; \
	xorq (tmp1, tmp2, 8),		dst; \
	leaq T1(%rip), 			tmp2; \
	movzbl ab ## bh,		tmp1 ## d; \
	rorq $16,			ab; \
	xorq (tmp2, tmp1, 8),		dst;

/**********************************************************************
  1-way camellia
 **********************************************************************/
#define roundsm(ab, subkey, cd) \
	movq (key_table + ((subkey) * 2) * 4)(CTX),	RT2; \
	\
	xor2ror16(sp00444404, sp03303033, RT0, RT1, ab ## 0, cd ## 0); \
	xor2ror16(sp22000222, sp10011110, RT0, RT1, ab ## 0, RT2); \
	xor2ror16(sp11101110, sp44044404, RT0, RT1, ab ## 0, cd ## 0); \
	xor2ror16(sp30333033, sp02220222, RT0, RT1, ab ## 0, RT2); \
	\
	xorq RT2,					cd ## 0;

#define fls(l, r, kl, kr) \
	movl (key_table + ((kl) * 2) * 4)(CTX),		RT0d; \
	andl l ## 0d,					RT0d; \
	roll $1,					RT0d; \
	shlq $32,					RT0; \
	xorq RT0,					l ## 0; \
	movq (key_table + ((kr) * 2) * 4)(CTX),		RT1; \
	orq r ## 0,					RT1; \
	shrq $32,					RT1; \
	xorq RT1,					r ## 0; \
	\
	movq (key_table + ((kl) * 2) * 4)(CTX),		RT2; \
	orq l ## 0,					RT2; \
	shrq $32,					RT2; \
	xorq RT2,					l ## 0; \
	movl (key_table + ((kr) * 2) * 4)(CTX),		RT0d; \
	andl r ## 0d,					RT0d; \
	roll $1,					RT0d; \
	shlq $32,					RT0; \
	xorq RT0,					r ## 0;

#define enc_rounds(i) \
	roundsm(RAB, i + 2, RCD); \
	roundsm(RCD, i + 3, RAB); \
	roundsm(RAB, i + 4, RCD); \
	roundsm(RCD, i + 5, RAB); \
	roundsm(RAB, i + 6, RCD); \
	roundsm(RCD, i + 7, RAB);

#define enc_fls(i) \
	fls(RAB, RCD, i + 0, i + 1);

#define enc_inpack() \
	movq (RIO),			RAB0; \
	bswapq				RAB0; \
	rolq $32,			RAB0; \
	movq 4*2(RIO),			RCD0; \
	bswapq				RCD0; \
	rorq $32,			RCD0; \
	xorq key_table(CTX),		RAB0;

#define enc_outunpack(op, max) \
	xorq key_table(CTX, max, 8),	RCD0; \
	rorq $32,			RCD0; \
	bswapq				RCD0; \
	op ## q RCD0,			(RIO); \
	rolq $32,			RAB0; \
	bswapq				RAB0; \
	op ## q RAB0,			4*2(RIO);

#define dec_rounds(i) \
	roundsm(RAB, i + 7, RCD); \
	roundsm(RCD, i + 6, RAB); \
	roundsm(RAB, i + 5, RCD); \
	roundsm(RCD, i + 4, RAB); \
	roundsm(RAB, i + 3, RCD); \
	roundsm(RCD, i + 2, RAB);

#define dec_fls(i) \
	fls(RAB, RCD, i + 1, i + 0);

#define dec_inpack(max) \
	movq (RIO),			RAB0; \
	bswapq				RAB0; \
	rolq $32,			RAB0; \
	movq 4*2(RIO),			RCD0; \
	bswapq				RCD0; \
	rorq $32,			RCD0; \
	xorq key_table(CTX, max, 8),	RAB0;

#define dec_outunpack() \
	xorq key_table(CTX),		RCD0; \
	rorq $32,			RCD0; \
	bswapq				RCD0; \
	movq RCD0,			(RIO); \
	rolq $32,			RAB0; \
	bswapq				RAB0; \
	movq RAB0,			4*2(RIO);

SYM_FUNC_START(__camellia_enc_blk)
	/* input:
	 *	%rdi: ctx, CTX
	 *	%rsi: dst
	 *	%rdx: src
	 *	%rcx: bool xor
	 */
	movq %r12, RR12;

	movq %rcx, RXOR;
	movq %rsi, RDST;
	movq %rdx, RIO;

	enc_inpack();

	enc_rounds(0);
	enc_fls(8);
	enc_rounds(8);
	enc_fls(16);
	enc_rounds(16);
	movl $24, RT1d; /* max */

	cmpb $16, key_length(CTX);
	je .L__enc_done;

	enc_fls(24);
	enc_rounds(24);
	movl $32, RT1d; /* max */

.L__enc_done:
	testb RXORbl, RXORbl;
	movq RDST, RIO;

	jnz .L__enc_xor;

	enc_outunpack(mov, RT1);

	movq RR12, %r12;
	RET;

.L__enc_xor:
	enc_outunpack(xor, RT1);

	movq RR12, %r12;
	RET;
SYM_FUNC_END(__camellia_enc_blk)

SYM_FUNC_START(camellia_dec_blk)
	/* input:
	 *	%rdi: ctx, CTX
	 *	%rsi: dst
	 *	%rdx: src
	 */
	cmpl $16, key_length(CTX);
	movl $32, RT2d;
	movl $24, RXORd;
	cmovel RXORd, RT2d; /* max */

	movq %r12, RR12;
	movq %rsi, RDST;
	movq %rdx, RIO;

	dec_inpack(RT2);

	cmpb $24, RT2bl;
	je .L__dec_rounds16;

	dec_rounds(24);
	dec_fls(24);

.L__dec_rounds16:
	dec_rounds(16);
	dec_fls(16);
	dec_rounds(8);
	dec_fls(8);
	dec_rounds(0);

	movq RDST, RIO;

	dec_outunpack();

	movq RR12, %r12;
	RET;
SYM_FUNC_END(camellia_dec_blk)

/**********************************************************************
  2-way camellia
 **********************************************************************/
#define roundsm2(ab, subkey, cd) \
	movq (key_table + ((subkey) * 2) * 4)(CTX),	RT2; \
	xorq RT2,					cd ## 1; \
	\
	xor2ror16(sp00444404, sp03303033, RT0, RT1, ab ## 0, cd ## 0); \
	xor2ror16(sp22000222, sp10011110, RT0, RT1, ab ## 0, RT2); \
	xor2ror16(sp11101110, sp44044404, RT0, RT1, ab ## 0, cd ## 0); \
	xor2ror16(sp30333033, sp02220222, RT0, RT1, ab ## 0, RT2); \
	\
		xor2ror16(sp00444404, sp03303033, RT0, RT1, ab ## 1, cd ## 1); \
		xorq RT2,					cd ## 0; \
		xor2ror16(sp22000222, sp10011110, RT0, RT1, ab ## 1, cd ## 1); \
		xor2ror16(sp11101110, sp44044404, RT0, RT1, ab ## 1, cd ## 1); \
		xor2ror16(sp30333033, sp02220222, RT0, RT1, ab ## 1, cd ## 1);

#define fls2(l, r, kl, kr) \
	movl (key_table + ((kl) * 2) * 4)(CTX),		RT0d; \
	andl l ## 0d,					RT0d; \
	roll $1,					RT0d; \
	shlq $32,					RT0; \
	xorq RT0,					l ## 0; \
	movq (key_table + ((kr) * 2) * 4)(CTX),		RT1; \
	orq r ## 0,					RT1; \
	shrq $32,					RT1; \
	xorq RT1,					r ## 0; \
	\
		movl (key_table + ((kl) * 2) * 4)(CTX),		RT2d; \
		andl l ## 1d,					RT2d; \
		roll $1,					RT2d; \
		shlq $32,					RT2; \
		xorq RT2,					l ## 1; \
		movq (key_table + ((kr) * 2) * 4)(CTX),		RT0; \
		orq r ## 1,					RT0; \
		shrq $32,					RT0; \
		xorq RT0,					r ## 1; \
	\
	movq (key_table + ((kl) * 2) * 4)(CTX),		RT1; \
	orq l ## 0,					RT1; \
	shrq $32,					RT1; \
	xorq RT1,					l ## 0; \
	movl (key_table + ((kr) * 2) * 4)(CTX),		RT2d; \
	andl r ## 0d,					RT2d; \
	roll $1,					RT2d; \
	shlq $32,					RT2; \
	xorq RT2,					r ## 0; \
	\
		movq (key_table + ((kl) * 2) * 4)(CTX),		RT0; \
		orq l ## 1,					RT0; \
		shrq $32,					RT0; \
		xorq RT0,					l ## 1; \
		movl (key_table + ((kr) * 2) * 4)(CTX),		RT1d; \
		andl r ## 1d,					RT1d; \
		roll $1,					RT1d; \
		shlq $32,					RT1; \
		xorq RT1,					r ## 1;

#define enc_rounds2(i) \
	roundsm2(RAB, i + 2, RCD); \
	roundsm2(RCD, i + 3, RAB); \
	roundsm2(RAB, i + 4, RCD); \
	roundsm2(RCD, i + 5, RAB); \
	roundsm2(RAB, i + 6, RCD); \
	roundsm2(RCD, i + 7, RAB);

#define enc_fls2(i) \
	fls2(RAB, RCD, i + 0, i + 1);

#define enc_inpack2() \
	movq (RIO),			RAB0; \
	bswapq				RAB0; \
	rorq $32,			RAB0; \
	movq 4*2(RIO),			RCD0; \
	bswapq				RCD0; \
	rolq $32,			RCD0; \
	xorq key_table(CTX),		RAB0; \
	\
		movq 8*2(RIO),			RAB1; \
		bswapq				RAB1; \
		rorq $32,			RAB1; \
		movq 12*2(RIO),			RCD1; \
		bswapq				RCD1; \
		rolq $32,			RCD1; \
		xorq key_table(CTX),		RAB1;

#define enc_outunpack2(op, max) \
	xorq key_table(CTX, max, 8),	RCD0; \
	rolq $32,			RCD0; \
	bswapq				RCD0; \
	op ## q RCD0,			(RIO); \
	rorq $32,			RAB0; \
	bswapq				RAB0; \
	op ## q RAB0,			4*2(RIO); \
	\
		xorq key_table(CTX, max, 8),	RCD1; \
		rolq $32,			RCD1; \
		bswapq				RCD1; \
		op ## q RCD1,			8*2(RIO); \
		rorq $32,			RAB1; \
		bswapq				RAB1; \
		op ## q RAB1,			12*2(RIO);

#define dec_rounds2(i) \
	roundsm2(RAB, i + 7, RCD); \
	roundsm2(RCD, i + 6, RAB); \
	roundsm2(RAB, i + 5, RCD); \
	roundsm2(RCD, i + 4, RAB); \
	roundsm2(RAB, i + 3, RCD); \
	roundsm2(RCD, i + 2, RAB);

#define dec_fls2(i) \
	fls2(RAB, RCD, i + 1, i + 0);

#define dec_inpack2(max) \
	movq (RIO),			RAB0; \
	bswapq				RAB0; \
	rorq $32,			RAB0; \
	movq 4*2(RIO),			RCD0; \
	bswapq				RCD0; \
	rolq $32,			RCD0; \
	xorq key_table(CTX, max, 8),	RAB0; \
	\
		movq 8*2(RIO),			RAB1; \
		bswapq				RAB1; \
		rorq $32,			RAB1; \
		movq 12*2(RIO),			RCD1; \
		bswapq				RCD1; \
		rolq $32,			RCD1; \
		xorq key_table(CTX, max, 8),	RAB1;

#define dec_outunpack2() \
	xorq key_table(CTX),		RCD0; \
	rolq $32,			RCD0; \
	bswapq				RCD0; \
	movq RCD0,			(RIO); \
	rorq $32,			RAB0; \
	bswapq				RAB0; \
	movq RAB0,			4*2(RIO); \
	\
		xorq key_table(CTX),		RCD1; \
		rolq $32,			RCD1; \
		bswapq				RCD1; \
		movq RCD1,			8*2(RIO); \
		rorq $32,			RAB1; \
		bswapq				RAB1; \
		movq RAB1,			12*2(RIO);

SYM_FUNC_START(__camellia_enc_blk_2way)
	/* input:
	 *	%rdi: ctx, CTX
	 *	%rsi: dst
	 *	%rdx: src
	 *	%rcx: bool xor
	 */
	pushq %rbx;

	movq %r12, RR12;
	movq %rcx, RXOR;
	movq %rsi, RDST;
	movq %rdx, RIO;

	enc_inpack2();

	enc_rounds2(0);
	enc_fls2(8);
	enc_rounds2(8);
	enc_fls2(16);
	enc_rounds2(16);
	movl $24, RT2d; /* max */

	cmpb $16, key_length(CTX);
	je .L__enc2_done;

	enc_fls2(24);
	enc_rounds2(24);
	movl $32, RT2d; /* max */

.L__enc2_done:
	test RXORbl, RXORbl;
	movq RDST, RIO;
	jnz .L__enc2_xor;

	enc_outunpack2(mov, RT2);

	movq RR12, %r12;
	popq %rbx;
	RET;

.L__enc2_xor:
	enc_outunpack2(xor, RT2);

	movq RR12, %r12;
	popq %rbx;
	RET;
SYM_FUNC_END(__camellia_enc_blk_2way)

SYM_FUNC_START(camellia_dec_blk_2way)
	/* input:
	 *	%rdi: ctx, CTX
	 *	%rsi: dst
	 *	%rdx: src
	 */
	cmpl $16, key_length(CTX);
	movl $32, RT2d;
	movl $24, RXORd;
	cmovel RXORd, RT2d; /* max */

	movq %rbx, RXOR;
	movq %r12, RR12;
	movq %rsi, RDST;
	movq %rdx, RIO;

	dec_inpack2(RT2);

	cmpb $24, RT2bl;
	je .L__dec2_rounds16;

	dec_rounds2(24);
	dec_fls2(24);

.L__dec2_rounds16:
	dec_rounds2(16);
	dec_fls2(16);
	dec_rounds2(8);
	dec_fls2(8);
	dec_rounds2(0);

	movq RDST, RIO;

	dec_outunpack2();

	movq RR12, %r12;
	movq RXOR, %rbx;
	RET;
SYM_FUNC_END(camellia_dec_blk_2way)
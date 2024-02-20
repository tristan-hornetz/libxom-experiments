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

#ifndef __x86_64__
#define __x86_64__
#endif

# constants in mergeable sections, linker can reorder and merge
.section	.rodata.cst16.POLY, "aM", @progbits, 16
.align 16
POLY:   .octa 0xC2000000000000000000000000000001
.section	.rodata.cst16.TWOONE, "aM", @progbits, 16
.align 16
TWOONE: .octa 0x00000001000000000000000000000001

.section	.rodata.cst16.SHUF_MASK, "aM", @progbits, 16
.align 16
SHUF_MASK:  .octa 0x000102030405060708090A0B0C0D0E0F
.section	.rodata.cst16.MASK1, "aM", @progbits, 16
.align 16
MASK1:      .octa 0x0000000000000000ffffffffffffffff
.section	.rodata.cst16.MASK2, "aM", @progbits, 16
.align 16
MASK2:      .octa 0xffffffffffffffff0000000000000000
.section	.rodata.cst16.ONE, "aM", @progbits, 16
.align 16
ONE:        .octa 0x00000000000000000000000000000001
.section	.rodata.cst16.F_MIN_MASK, "aM", @progbits, 16
.align 16
F_MIN_MASK: .octa 0xf1f2f3f4f5f6f7f8f9fafbfcfdfeff0
.section	.rodata.cst16.dec, "aM", @progbits, 16
.align 16
dec:        .octa 0x1
.section	.rodata.cst16.enc, "aM", @progbits, 16
.align 16
enc:        .octa 0x2
/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * ChaCha 256-bit cipher algorithm, x64 SSSE3 functions
 *
 * Copyright (C) 2015 Martin Willi
 */


.section	.rodata.cst16.ROT8, "aM", @progbits, 16
.align 16
ROT8:	.octa 0x0e0d0c0f0a09080b0605040702010003
.section	.rodata.cst16.ROT16, "aM", @progbits, 16
.align 16
ROT16:	.octa 0x0d0c0f0e09080b0a0504070601000302
.section	.rodata.cst16.CTRINC, "aM", @progbits, 16
.align 16
CTRINC:	.octa 0x00000003000000020000000100000000

.text

/*
 * chacha_permute - permute one block
 *
 * Permute one 64-byte block where the state matrix is in %xmm0-%xmm3.  This
 * function performs matrix operations on four words in parallel, but requires
 * shuffling to rearrange the words after each round.  8/16-bit word rotation is
 * done with the slightly better performing SSSE3 byte shuffling, 7/12-bit word
 * rotation uses traditional shift+OR.
 *
 * The round count is given in %r8d.
 *
 * Clobbers: %r8d, %xmm4-%xmm7
 */
SYM_FUNC_START_LOCAL(chacha_permute)

	movdqa		ROT8(%rip),%xmm4
	movdqa		ROT16(%rip),%xmm5

.Ldoubleround:
	# x0 += x1, x3 = rotl32(x3 ^ x0, 16)
	paddd		%xmm1,%xmm0
	pxor		%xmm0,%xmm3
	pshufb		%xmm5,%xmm3

	# x2 += x3, x1 = rotl32(x1 ^ x2, 12)
	paddd		%xmm3,%xmm2
	pxor		%xmm2,%xmm1
	movdqa		%xmm1,%xmm6
	pslld		$12,%xmm6
	psrld		$20,%xmm1
	por		%xmm6,%xmm1

	# x0 += x1, x3 = rotl32(x3 ^ x0, 8)
	paddd		%xmm1,%xmm0
	pxor		%xmm0,%xmm3
	pshufb		%xmm4,%xmm3

	# x2 += x3, x1 = rotl32(x1 ^ x2, 7)
	paddd		%xmm3,%xmm2
	pxor		%xmm2,%xmm1
	movdqa		%xmm1,%xmm7
	pslld		$7,%xmm7
	psrld		$25,%xmm1
	por		%xmm7,%xmm1

	# x1 = shuffle32(x1, MASK(0, 3, 2, 1))
	pshufd		$0x39,%xmm1,%xmm1
	# x2 = shuffle32(x2, MASK(1, 0, 3, 2))
	pshufd		$0x4e,%xmm2,%xmm2
	# x3 = shuffle32(x3, MASK(2, 1, 0, 3))
	pshufd		$0x93,%xmm3,%xmm3

	# x0 += x1, x3 = rotl32(x3 ^ x0, 16)
	paddd		%xmm1,%xmm0
	pxor		%xmm0,%xmm3
	pshufb		%xmm5,%xmm3

	# x2 += x3, x1 = rotl32(x1 ^ x2, 12)
	paddd		%xmm3,%xmm2
	pxor		%xmm2,%xmm1
	movdqa		%xmm1,%xmm6
	pslld		$12,%xmm6
	psrld		$20,%xmm1
	por		%xmm6,%xmm1

	# x0 += x1, x3 = rotl32(x3 ^ x0, 8)
	paddd		%xmm1,%xmm0
	pxor		%xmm0,%xmm3
	pshufb		%xmm4,%xmm3

	# x2 += x3, x1 = rotl32(x1 ^ x2, 7)
	paddd		%xmm3,%xmm2
	pxor		%xmm2,%xmm1
	movdqa		%xmm1,%xmm7
	pslld		$7,%xmm7
	psrld		$25,%xmm1
	por		%xmm7,%xmm1

	# x1 = shuffle32(x1, MASK(2, 1, 0, 3))
	pshufd		$0x93,%xmm1,%xmm1
	# x2 = shuffle32(x2, MASK(1, 0, 3, 2))
	pshufd		$0x4e,%xmm2,%xmm2
	# x3 = shuffle32(x3, MASK(0, 3, 2, 1))
	pshufd		$0x39,%xmm3,%xmm3

	sub		$2,%r8d
	jnz		.Ldoubleround

	RET
SYM_FUNC_END(chacha_permute)

SYM_FUNC_START(chacha_block_xor_ssse3)
	# %rdi: Input state matrix, s
	# %rsi: up to 1 data block output, o
	# %rdx: up to 1 data block input, i
	# %rcx: input/output length in bytes
	# %r8d: nrounds
	FRAME_BEGIN

	# x0..3 = s0..3
	movdqu		0x00(%rdi),%xmm0
	movdqu		0x10(%rdi),%xmm1
	movdqu		0x20(%rdi),%xmm2
	movdqu		0x30(%rdi),%xmm3
	movdqa		%xmm0,%xmm8
	movdqa		%xmm1,%xmm9
	movdqa		%xmm2,%xmm10
	movdqa		%xmm3,%xmm11

	mov		%rcx,%rax
	call		chacha_permute

	# o0 = i0 ^ (x0 + s0)
	paddd		%xmm8,%xmm0
	cmp		$0x10,%rax
	jl		.Lxorpart
	movdqu		0x00(%rdx),%xmm4
	pxor		%xmm4,%xmm0
	movdqu		%xmm0,0x00(%rsi)
	# o1 = i1 ^ (x1 + s1)
	paddd		%xmm9,%xmm1
	movdqa		%xmm1,%xmm0
	cmp		$0x20,%rax
	jl		.Lxorpart
	movdqu		0x10(%rdx),%xmm0
	pxor		%xmm1,%xmm0
	movdqu		%xmm0,0x10(%rsi)
	# o2 = i2 ^ (x2 + s2)
	paddd		%xmm10,%xmm2
	movdqa		%xmm2,%xmm0
	cmp		$0x30,%rax
	jl		.Lxorpart
	movdqu		0x20(%rdx),%xmm0
	pxor		%xmm2,%xmm0
	movdqu		%xmm0,0x20(%rsi)
	# o3 = i3 ^ (x3 + s3)
	paddd		%xmm11,%xmm3
	movdqa		%xmm3,%xmm0
	cmp		$0x40,%rax
	jl		.Lxorpart
	movdqu		0x30(%rdx),%xmm0
	pxor		%xmm3,%xmm0
	movdqu		%xmm0,0x30(%rsi)

.Ldone:
	FRAME_END
	RET

.Lxorpart:
	# xor remaining bytes from partial register into output
	mov		%rax,%r9
	and		$0x0f,%r9
	jz		.Ldone
	and		$~0x0f,%rax

	mov		%rsi,%r11

	lea		8(%rsp),%r10
	sub		$0x10,%rsp
	and		$~31,%rsp

	lea		(%rdx,%rax),%rsi
	mov		%rsp,%rdi
	mov		%r9,%rcx
	rep movsb

	pxor		0x00(%rsp),%xmm0
	movdqa		%xmm0,0x00(%rsp)

	mov		%rsp,%rsi
	lea		(%r11,%rax),%rdi
	mov		%r9,%rcx
	rep movsb

	lea		-8(%r10),%rsp
	jmp		.Ldone

SYM_FUNC_END(chacha_block_xor_ssse3)

SYM_FUNC_START(hchacha_block_ssse3)
	# %rdi: Input state matrix, s
	# %rsi: output (8 32-bit words)
	# %edx: nrounds
	FRAME_BEGIN

	movdqu		0x00(%rdi),%xmm0
	movdqu		0x10(%rdi),%xmm1
	movdqu		0x20(%rdi),%xmm2
	movdqu		0x30(%rdi),%xmm3

	mov		%edx,%r8d
	call		chacha_permute

	movdqu		%xmm0,0x00(%rsi)
	movdqu		%xmm3,0x10(%rsi)

	FRAME_END
	RET
SYM_FUNC_END(hchacha_block_ssse3)

SYM_FUNC_START(chacha_4block_xor_ssse3)
	# %rdi: Input state matrix, s
	# %rsi: up to 4 data blocks output, o
	# %rdx: up to 4 data blocks input, i
	# %rcx: input/output length in bytes
	# %r8d: nrounds

	# This function encrypts four consecutive ChaCha blocks by loading the
	# the state matrix in SSE registers four times. As we need some scratch
	# registers, we save the first four registers on the stack. The
	# algorithm performs each operation on the corresponding word of each
	# state matrix, hence requires no word shuffling. For final XORing step
	# we transpose the matrix by interleaving 32- and then 64-bit words,
	# which allows us to do XOR in SSE registers. 8/16-bit word rotation is
	# done with the slightly better performing SSSE3 byte shuffling,
	# 7/12-bit word rotation uses traditional shift+OR.

	lea		8(%rsp),%r10
	sub		$0x80,%rsp
	and		$~63,%rsp
	mov		%rcx,%rax

	# x0..15[0-3] = s0..3[0..3]
	movq		0x00(%rdi),%xmm1
	pshufd		$0x00,%xmm1,%xmm0
	pshufd		$0x55,%xmm1,%xmm1
	movq		0x08(%rdi),%xmm3
	pshufd		$0x00,%xmm3,%xmm2
	pshufd		$0x55,%xmm3,%xmm3
	movq		0x10(%rdi),%xmm5
	pshufd		$0x00,%xmm5,%xmm4
	pshufd		$0x55,%xmm5,%xmm5
	movq		0x18(%rdi),%xmm7
	pshufd		$0x00,%xmm7,%xmm6
	pshufd		$0x55,%xmm7,%xmm7
	movq		0x20(%rdi),%xmm9
	pshufd		$0x00,%xmm9,%xmm8
	pshufd		$0x55,%xmm9,%xmm9
	movq		0x28(%rdi),%xmm11
	pshufd		$0x00,%xmm11,%xmm10
	pshufd		$0x55,%xmm11,%xmm11
	movq		0x30(%rdi),%xmm13
	pshufd		$0x00,%xmm13,%xmm12
	pshufd		$0x55,%xmm13,%xmm13
	movq		0x38(%rdi),%xmm15
	pshufd		$0x00,%xmm15,%xmm14
	pshufd		$0x55,%xmm15,%xmm15
	# x0..3 on stack
	movdqa		%xmm0,0x00(%rsp)
	movdqa		%xmm1,0x10(%rsp)
	movdqa		%xmm2,0x20(%rsp)
	movdqa		%xmm3,0x30(%rsp)

	movdqa		CTRINC(%rip),%xmm1
	movdqa		ROT8(%rip),%xmm2
	movdqa		ROT16(%rip),%xmm3

	# x12 += counter values 0-3
	paddd		%xmm1,%xmm12

.Ldoubleround4:
	# x0 += x4, x12 = rotl32(x12 ^ x0, 16)
	movdqa		0x00(%rsp),%xmm0
	paddd		%xmm4,%xmm0
	movdqa		%xmm0,0x00(%rsp)
	pxor		%xmm0,%xmm12
	pshufb		%xmm3,%xmm12
	# x1 += x5, x13 = rotl32(x13 ^ x1, 16)
	movdqa		0x10(%rsp),%xmm0
	paddd		%xmm5,%xmm0
	movdqa		%xmm0,0x10(%rsp)
	pxor		%xmm0,%xmm13
	pshufb		%xmm3,%xmm13
	# x2 += x6, x14 = rotl32(x14 ^ x2, 16)
	movdqa		0x20(%rsp),%xmm0
	paddd		%xmm6,%xmm0
	movdqa		%xmm0,0x20(%rsp)
	pxor		%xmm0,%xmm14
	pshufb		%xmm3,%xmm14
	# x3 += x7, x15 = rotl32(x15 ^ x3, 16)
	movdqa		0x30(%rsp),%xmm0
	paddd		%xmm7,%xmm0
	movdqa		%xmm0,0x30(%rsp)
	pxor		%xmm0,%xmm15
	pshufb		%xmm3,%xmm15

	# x8 += x12, x4 = rotl32(x4 ^ x8, 12)
	paddd		%xmm12,%xmm8
	pxor		%xmm8,%xmm4
	movdqa		%xmm4,%xmm0
	pslld		$12,%xmm0
	psrld		$20,%xmm4
	por		%xmm0,%xmm4
	# x9 += x13, x5 = rotl32(x5 ^ x9, 12)
	paddd		%xmm13,%xmm9
	pxor		%xmm9,%xmm5
	movdqa		%xmm5,%xmm0
	pslld		$12,%xmm0
	psrld		$20,%xmm5
	por		%xmm0,%xmm5
	# x10 += x14, x6 = rotl32(x6 ^ x10, 12)
	paddd		%xmm14,%xmm10
	pxor		%xmm10,%xmm6
	movdqa		%xmm6,%xmm0
	pslld		$12,%xmm0
	psrld		$20,%xmm6
	por		%xmm0,%xmm6
	# x11 += x15, x7 = rotl32(x7 ^ x11, 12)
	paddd		%xmm15,%xmm11
	pxor		%xmm11,%xmm7
	movdqa		%xmm7,%xmm0
	pslld		$12,%xmm0
	psrld		$20,%xmm7
	por		%xmm0,%xmm7

	# x0 += x4, x12 = rotl32(x12 ^ x0, 8)
	movdqa		0x00(%rsp),%xmm0
	paddd		%xmm4,%xmm0
	movdqa		%xmm0,0x00(%rsp)
	pxor		%xmm0,%xmm12
	pshufb		%xmm2,%xmm12
	# x1 += x5, x13 = rotl32(x13 ^ x1, 8)
	movdqa		0x10(%rsp),%xmm0
	paddd		%xmm5,%xmm0
	movdqa		%xmm0,0x10(%rsp)
	pxor		%xmm0,%xmm13
	pshufb		%xmm2,%xmm13
	# x2 += x6, x14 = rotl32(x14 ^ x2, 8)
	movdqa		0x20(%rsp),%xmm0
	paddd		%xmm6,%xmm0
	movdqa		%xmm0,0x20(%rsp)
	pxor		%xmm0,%xmm14
	pshufb		%xmm2,%xmm14
	# x3 += x7, x15 = rotl32(x15 ^ x3, 8)
	movdqa		0x30(%rsp),%xmm0
	paddd		%xmm7,%xmm0
	movdqa		%xmm0,0x30(%rsp)
	pxor		%xmm0,%xmm15
	pshufb		%xmm2,%xmm15

	# x8 += x12, x4 = rotl32(x4 ^ x8, 7)
	paddd		%xmm12,%xmm8
	pxor		%xmm8,%xmm4
	movdqa		%xmm4,%xmm0
	pslld		$7,%xmm0
	psrld		$25,%xmm4
	por		%xmm0,%xmm4
	# x9 += x13, x5 = rotl32(x5 ^ x9, 7)
	paddd		%xmm13,%xmm9
	pxor		%xmm9,%xmm5
	movdqa		%xmm5,%xmm0
	pslld		$7,%xmm0
	psrld		$25,%xmm5
	por		%xmm0,%xmm5
	# x10 += x14, x6 = rotl32(x6 ^ x10, 7)
	paddd		%xmm14,%xmm10
	pxor		%xmm10,%xmm6
	movdqa		%xmm6,%xmm0
	pslld		$7,%xmm0
	psrld		$25,%xmm6
	por		%xmm0,%xmm6
	# x11 += x15, x7 = rotl32(x7 ^ x11, 7)
	paddd		%xmm15,%xmm11
	pxor		%xmm11,%xmm7
	movdqa		%xmm7,%xmm0
	pslld		$7,%xmm0
	psrld		$25,%xmm7
	por		%xmm0,%xmm7

	# x0 += x5, x15 = rotl32(x15 ^ x0, 16)
	movdqa		0x00(%rsp),%xmm0
	paddd		%xmm5,%xmm0
	movdqa		%xmm0,0x00(%rsp)
	pxor		%xmm0,%xmm15
	pshufb		%xmm3,%xmm15
	# x1 += x6, x12 = rotl32(x12 ^ x1, 16)
	movdqa		0x10(%rsp),%xmm0
	paddd		%xmm6,%xmm0
	movdqa		%xmm0,0x10(%rsp)
	pxor		%xmm0,%xmm12
	pshufb		%xmm3,%xmm12
	# x2 += x7, x13 = rotl32(x13 ^ x2, 16)
	movdqa		0x20(%rsp),%xmm0
	paddd		%xmm7,%xmm0
	movdqa		%xmm0,0x20(%rsp)
	pxor		%xmm0,%xmm13
	pshufb		%xmm3,%xmm13
	# x3 += x4, x14 = rotl32(x14 ^ x3, 16)
	movdqa		0x30(%rsp),%xmm0
	paddd		%xmm4,%xmm0
	movdqa		%xmm0,0x30(%rsp)
	pxor		%xmm0,%xmm14
	pshufb		%xmm3,%xmm14

	# x10 += x15, x5 = rotl32(x5 ^ x10, 12)
	paddd		%xmm15,%xmm10
	pxor		%xmm10,%xmm5
	movdqa		%xmm5,%xmm0
	pslld		$12,%xmm0
	psrld		$20,%xmm5
	por		%xmm0,%xmm5
	# x11 += x12, x6 = rotl32(x6 ^ x11, 12)
	paddd		%xmm12,%xmm11
	pxor		%xmm11,%xmm6
	movdqa		%xmm6,%xmm0
	pslld		$12,%xmm0
	psrld		$20,%xmm6
	por		%xmm0,%xmm6
	# x8 += x13, x7 = rotl32(x7 ^ x8, 12)
	paddd		%xmm13,%xmm8
	pxor		%xmm8,%xmm7
	movdqa		%xmm7,%xmm0
	pslld		$12,%xmm0
	psrld		$20,%xmm7
	por		%xmm0,%xmm7
	# x9 += x14, x4 = rotl32(x4 ^ x9, 12)
	paddd		%xmm14,%xmm9
	pxor		%xmm9,%xmm4
	movdqa		%xmm4,%xmm0
	pslld		$12,%xmm0
	psrld		$20,%xmm4
	por		%xmm0,%xmm4

	# x0 += x5, x15 = rotl32(x15 ^ x0, 8)
	movdqa		0x00(%rsp),%xmm0
	paddd		%xmm5,%xmm0
	movdqa		%xmm0,0x00(%rsp)
	pxor		%xmm0,%xmm15
	pshufb		%xmm2,%xmm15
	# x1 += x6, x12 = rotl32(x12 ^ x1, 8)
	movdqa		0x10(%rsp),%xmm0
	paddd		%xmm6,%xmm0
	movdqa		%xmm0,0x10(%rsp)
	pxor		%xmm0,%xmm12
	pshufb		%xmm2,%xmm12
	# x2 += x7, x13 = rotl32(x13 ^ x2, 8)
	movdqa		0x20(%rsp),%xmm0
	paddd		%xmm7,%xmm0
	movdqa		%xmm0,0x20(%rsp)
	pxor		%xmm0,%xmm13
	pshufb		%xmm2,%xmm13
	# x3 += x4, x14 = rotl32(x14 ^ x3, 8)
	movdqa		0x30(%rsp),%xmm0
	paddd		%xmm4,%xmm0
	movdqa		%xmm0,0x30(%rsp)
	pxor		%xmm0,%xmm14
	pshufb		%xmm2,%xmm14

	# x10 += x15, x5 = rotl32(x5 ^ x10, 7)
	paddd		%xmm15,%xmm10
	pxor		%xmm10,%xmm5
	movdqa		%xmm5,%xmm0
	pslld		$7,%xmm0
	psrld		$25,%xmm5
	por		%xmm0,%xmm5
	# x11 += x12, x6 = rotl32(x6 ^ x11, 7)
	paddd		%xmm12,%xmm11
	pxor		%xmm11,%xmm6
	movdqa		%xmm6,%xmm0
	pslld		$7,%xmm0
	psrld		$25,%xmm6
	por		%xmm0,%xmm6
	# x8 += x13, x7 = rotl32(x7 ^ x8, 7)
	paddd		%xmm13,%xmm8
	pxor		%xmm8,%xmm7
	movdqa		%xmm7,%xmm0
	pslld		$7,%xmm0
	psrld		$25,%xmm7
	por		%xmm0,%xmm7
	# x9 += x14, x4 = rotl32(x4 ^ x9, 7)
	paddd		%xmm14,%xmm9
	pxor		%xmm9,%xmm4
	movdqa		%xmm4,%xmm0
	pslld		$7,%xmm0
	psrld		$25,%xmm4
	por		%xmm0,%xmm4

	sub		$2,%r8d
	jnz		.Ldoubleround4

	# x0[0-3] += s0[0]
	# x1[0-3] += s0[1]
	movq		0x00(%rdi),%xmm3
	pshufd		$0x00,%xmm3,%xmm2
	pshufd		$0x55,%xmm3,%xmm3
	paddd		0x00(%rsp),%xmm2
	movdqa		%xmm2,0x00(%rsp)
	paddd		0x10(%rsp),%xmm3
	movdqa		%xmm3,0x10(%rsp)
	# x2[0-3] += s0[2]
	# x3[0-3] += s0[3]
	movq		0x08(%rdi),%xmm3
	pshufd		$0x00,%xmm3,%xmm2
	pshufd		$0x55,%xmm3,%xmm3
	paddd		0x20(%rsp),%xmm2
	movdqa		%xmm2,0x20(%rsp)
	paddd		0x30(%rsp),%xmm3
	movdqa		%xmm3,0x30(%rsp)

	# x4[0-3] += s1[0]
	# x5[0-3] += s1[1]
	movq		0x10(%rdi),%xmm3
	pshufd		$0x00,%xmm3,%xmm2
	pshufd		$0x55,%xmm3,%xmm3
	paddd		%xmm2,%xmm4
	paddd		%xmm3,%xmm5
	# x6[0-3] += s1[2]
	# x7[0-3] += s1[3]
	movq		0x18(%rdi),%xmm3
	pshufd		$0x00,%xmm3,%xmm2
	pshufd		$0x55,%xmm3,%xmm3
	paddd		%xmm2,%xmm6
	paddd		%xmm3,%xmm7

	# x8[0-3] += s2[0]
	# x9[0-3] += s2[1]
	movq		0x20(%rdi),%xmm3
	pshufd		$0x00,%xmm3,%xmm2
	pshufd		$0x55,%xmm3,%xmm3
	paddd		%xmm2,%xmm8
	paddd		%xmm3,%xmm9
	# x10[0-3] += s2[2]
	# x11[0-3] += s2[3]
	movq		0x28(%rdi),%xmm3
	pshufd		$0x00,%xmm3,%xmm2
	pshufd		$0x55,%xmm3,%xmm3
	paddd		%xmm2,%xmm10
	paddd		%xmm3,%xmm11

	# x12[0-3] += s3[0]
	# x13[0-3] += s3[1]
	movq		0x30(%rdi),%xmm3
	pshufd		$0x00,%xmm3,%xmm2
	pshufd		$0x55,%xmm3,%xmm3
	paddd		%xmm2,%xmm12
	paddd		%xmm3,%xmm13
	# x14[0-3] += s3[2]
	# x15[0-3] += s3[3]
	movq		0x38(%rdi),%xmm3
	pshufd		$0x00,%xmm3,%xmm2
	pshufd		$0x55,%xmm3,%xmm3
	paddd		%xmm2,%xmm14
	paddd		%xmm3,%xmm15

	# x12 += counter values 0-3
	paddd		%xmm1,%xmm12

	# interleave 32-bit words in state n, n+1
	movdqa		0x00(%rsp),%xmm0
	movdqa		0x10(%rsp),%xmm1
	movdqa		%xmm0,%xmm2
	punpckldq	%xmm1,%xmm2
	punpckhdq	%xmm1,%xmm0
	movdqa		%xmm2,0x00(%rsp)
	movdqa		%xmm0,0x10(%rsp)
	movdqa		0x20(%rsp),%xmm0
	movdqa		0x30(%rsp),%xmm1
	movdqa		%xmm0,%xmm2
	punpckldq	%xmm1,%xmm2
	punpckhdq	%xmm1,%xmm0
	movdqa		%xmm2,0x20(%rsp)
	movdqa		%xmm0,0x30(%rsp)
	movdqa		%xmm4,%xmm0
	punpckldq	%xmm5,%xmm4
	punpckhdq	%xmm5,%xmm0
	movdqa		%xmm0,%xmm5
	movdqa		%xmm6,%xmm0
	punpckldq	%xmm7,%xmm6
	punpckhdq	%xmm7,%xmm0
	movdqa		%xmm0,%xmm7
	movdqa		%xmm8,%xmm0
	punpckldq	%xmm9,%xmm8
	punpckhdq	%xmm9,%xmm0
	movdqa		%xmm0,%xmm9
	movdqa		%xmm10,%xmm0
	punpckldq	%xmm11,%xmm10
	punpckhdq	%xmm11,%xmm0
	movdqa		%xmm0,%xmm11
	movdqa		%xmm12,%xmm0
	punpckldq	%xmm13,%xmm12
	punpckhdq	%xmm13,%xmm0
	movdqa		%xmm0,%xmm13
	movdqa		%xmm14,%xmm0
	punpckldq	%xmm15,%xmm14
	punpckhdq	%xmm15,%xmm0
	movdqa		%xmm0,%xmm15

	# interleave 64-bit words in state n, n+2
	movdqa		0x00(%rsp),%xmm0
	movdqa		0x20(%rsp),%xmm1
	movdqa		%xmm0,%xmm2
	punpcklqdq	%xmm1,%xmm2
	punpckhqdq	%xmm1,%xmm0
	movdqa		%xmm2,0x00(%rsp)
	movdqa		%xmm0,0x20(%rsp)
	movdqa		0x10(%rsp),%xmm0
	movdqa		0x30(%rsp),%xmm1
	movdqa		%xmm0,%xmm2
	punpcklqdq	%xmm1,%xmm2
	punpckhqdq	%xmm1,%xmm0
	movdqa		%xmm2,0x10(%rsp)
	movdqa		%xmm0,0x30(%rsp)
	movdqa		%xmm4,%xmm0
	punpcklqdq	%xmm6,%xmm4
	punpckhqdq	%xmm6,%xmm0
	movdqa		%xmm0,%xmm6
	movdqa		%xmm5,%xmm0
	punpcklqdq	%xmm7,%xmm5
	punpckhqdq	%xmm7,%xmm0
	movdqa		%xmm0,%xmm7
	movdqa		%xmm8,%xmm0
	punpcklqdq	%xmm10,%xmm8
	punpckhqdq	%xmm10,%xmm0
	movdqa		%xmm0,%xmm10
	movdqa		%xmm9,%xmm0
	punpcklqdq	%xmm11,%xmm9
	punpckhqdq	%xmm11,%xmm0
	movdqa		%xmm0,%xmm11
	movdqa		%xmm12,%xmm0
	punpcklqdq	%xmm14,%xmm12
	punpckhqdq	%xmm14,%xmm0
	movdqa		%xmm0,%xmm14
	movdqa		%xmm13,%xmm0
	punpcklqdq	%xmm15,%xmm13
	punpckhqdq	%xmm15,%xmm0
	movdqa		%xmm0,%xmm15

	# xor with corresponding input, write to output
	movdqa		0x00(%rsp),%xmm0
	cmp		$0x10,%rax
	jl		.Lxorpart4
	movdqu		0x00(%rdx),%xmm1
	pxor		%xmm1,%xmm0
	movdqu		%xmm0,0x00(%rsi)

	movdqu		%xmm4,%xmm0
	cmp		$0x20,%rax
	jl		.Lxorpart4
	movdqu		0x10(%rdx),%xmm1
	pxor		%xmm1,%xmm0
	movdqu		%xmm0,0x10(%rsi)

	movdqu		%xmm8,%xmm0
	cmp		$0x30,%rax
	jl		.Lxorpart4
	movdqu		0x20(%rdx),%xmm1
	pxor		%xmm1,%xmm0
	movdqu		%xmm0,0x20(%rsi)

	movdqu		%xmm12,%xmm0
	cmp		$0x40,%rax
	jl		.Lxorpart4
	movdqu		0x30(%rdx),%xmm1
	pxor		%xmm1,%xmm0
	movdqu		%xmm0,0x30(%rsi)

	movdqa		0x20(%rsp),%xmm0
	cmp		$0x50,%rax
	jl		.Lxorpart4
	movdqu		0x40(%rdx),%xmm1
	pxor		%xmm1,%xmm0
	movdqu		%xmm0,0x40(%rsi)

	movdqu		%xmm6,%xmm0
	cmp		$0x60,%rax
	jl		.Lxorpart4
	movdqu		0x50(%rdx),%xmm1
	pxor		%xmm1,%xmm0
	movdqu		%xmm0,0x50(%rsi)

	movdqu		%xmm10,%xmm0
	cmp		$0x70,%rax
	jl		.Lxorpart4
	movdqu		0x60(%rdx),%xmm1
	pxor		%xmm1,%xmm0
	movdqu		%xmm0,0x60(%rsi)

	movdqu		%xmm14,%xmm0
	cmp		$0x80,%rax
	jl		.Lxorpart4
	movdqu		0x70(%rdx),%xmm1
	pxor		%xmm1,%xmm0
	movdqu		%xmm0,0x70(%rsi)

	movdqa		0x10(%rsp),%xmm0
	cmp		$0x90,%rax
	jl		.Lxorpart4
	movdqu		0x80(%rdx),%xmm1
	pxor		%xmm1,%xmm0
	movdqu		%xmm0,0x80(%rsi)

	movdqu		%xmm5,%xmm0
	cmp		$0xa0,%rax
	jl		.Lxorpart4
	movdqu		0x90(%rdx),%xmm1
	pxor		%xmm1,%xmm0
	movdqu		%xmm0,0x90(%rsi)

	movdqu		%xmm9,%xmm0
	cmp		$0xb0,%rax
	jl		.Lxorpart4
	movdqu		0xa0(%rdx),%xmm1
	pxor		%xmm1,%xmm0
	movdqu		%xmm0,0xa0(%rsi)

	movdqu		%xmm13,%xmm0
	cmp		$0xc0,%rax
	jl		.Lxorpart4
	movdqu		0xb0(%rdx),%xmm1
	pxor		%xmm1,%xmm0
	movdqu		%xmm0,0xb0(%rsi)

	movdqa		0x30(%rsp),%xmm0
	cmp		$0xd0,%rax
	jl		.Lxorpart4
	movdqu		0xc0(%rdx),%xmm1
	pxor		%xmm1,%xmm0
	movdqu		%xmm0,0xc0(%rsi)

	movdqu		%xmm7,%xmm0
	cmp		$0xe0,%rax
	jl		.Lxorpart4
	movdqu		0xd0(%rdx),%xmm1
	pxor		%xmm1,%xmm0
	movdqu		%xmm0,0xd0(%rsi)

	movdqu		%xmm11,%xmm0
	cmp		$0xf0,%rax
	jl		.Lxorpart4
	movdqu		0xe0(%rdx),%xmm1
	pxor		%xmm1,%xmm0
	movdqu		%xmm0,0xe0(%rsi)

	movdqu		%xmm15,%xmm0
	cmp		$0x100,%rax
	jl		.Lxorpart4
	movdqu		0xf0(%rdx),%xmm1
	pxor		%xmm1,%xmm0
	movdqu		%xmm0,0xf0(%rsi)

.Ldone4:
	lea		-8(%r10),%rsp
	RET

.Lxorpart4:
	# xor remaining bytes from partial register into output
	mov		%rax,%r9
	and		$0x0f,%r9
	jz		.Ldone4
	and		$~0x0f,%rax

	mov		%rsi,%r11

	lea		(%rdx,%rax),%rsi
	mov		%rsp,%rdi
	mov		%r9,%rcx
	rep movsb

	pxor		0x00(%rsp),%xmm0
	movdqa		%xmm0,0x00(%rsp)

	mov		%rsp,%rsi
	lea		(%r11,%rax),%rdi
	mov		%r9,%rcx
	rep movsb

	jmp		.Ldone4

SYM_FUNC_END(chacha_4block_xor_ssse3)

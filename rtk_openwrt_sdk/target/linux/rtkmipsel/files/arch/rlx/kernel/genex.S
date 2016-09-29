/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1994 - 2000, 2001, 2003 Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 * Copyright (C) 2002, 2007  Maciej W. Rozycki
 * Copyright (C) 2001, 2012 MIPS Technologies, Inc.  All rights reserved.
 *
 * Modified for RLX processors
 * Copyright (C) 2008-2013 Tony Wu (tonywu@realtek.com)
 */
#include <linux/init.h>

#include <asm/asm.h>
#include <asm/asmmacro.h>
#include <asm/cacheops.h>
#include <asm/irqflags.h>
#include <asm/regdef.h>
#include <asm/rlxregs.h>
#include <asm/stackframe.h>
#include <asm/thread_info.h>

#ifdef CONFIG_MIPS_MT_SMTC
#define PANIC_PIC(msg)					\
		.set	push;				\
		.set	nomicromips;			\
		.set	reorder;			\
		PTR_LA	a0,8f;				\
		.set	noat;				\
		PTR_LA	AT, panic;			\
		jr	AT;				\
9:		b	9b;				\
		.set	pop;				\
		TEXT(msg)
#endif

	__INIT

/*
 * rlx_trap_dispatch: exception vector for all RLX CPUs
 *
 * Be careful when changing this, it has to be at most 128 bytes
 * to fit into space reserved for the exception handler.
 */
NESTED(rlx_trap_dispatch, 0, sp)
	.set	push
	.set	noat
	mfc0	k1, CP0_CAUSE
	andi	k1, k1, 0x7c
	PTR_L	k0, exception_handlers(k1)
	jr	k0
	.set	pop
	END(rlx_trap_dispatch)

	__FINIT

	.align	5
NESTED(handle_int, PT_SIZE, sp)
#ifdef CONFIG_TRACE_IRQFLAGS
	/*
	 * Check to see if the interrupted code has just disabled
	 * interrupts and ignore this interrupt for now if so.
	 *
	 * local_irq_disable() disables interrupts and then calls
	 * trace_hardirqs_off() to track the state. If an interrupt is taken
	 * after interrupts are disabled but before the state is updated
	 * it will appear to restore_all that it is incorrectly returning with
	 * interrupts disabled
	 */
	.set	push
	.set	noat
	mfc0	k0, CP0_STATUS
	and	k0, ST0_IEP
	bnez	k0, 1f

	mfc0	k0, CP0_EPC
	.set	noreorder
	j	k0
	rfe
1:
	.set pop
#endif
	SAVE_ALL
	CLI
	TRACE_IRQS_OFF

	LONG_L	s0, TI_REGS($28)
	LONG_S	sp, TI_REGS($28)
	PTR_LA	ra, ret_from_irq
	PTR_LA  v0, bsp_irq_dispatch
	jr	v0
	END(handle_int)

	.align	6
NESTED(handle_vec, PT_SIZE, sp)
	.set push
	.set noreorder
	b     0f
	 nop
	b     1f
	 nop
	b     2f
	 nop
	b     3f
	 nop
	b     4f
	 nop
	b     5f
	 nop
	b     6f
	 nop
	b     7f
	 nop

0:	SAVE_SP
	b    9f
	 li  k1, 0

1:	SAVE_SP
	b    9f
	 li  k1, 1

2:	SAVE_SP
	b    9f
	 li  k1, 2

3:	SAVE_SP
	b    9f
	 li  k1, 3

4:	SAVE_SP
	b    9f
	 li  k1, 4

5:	SAVE_SP
	b    9f
	 li  k1, 5

6:	SAVE_SP
	b    9f
	 li  k1, 6

7:	SAVE_SP
	li  k1, 7
	.set pop

9:	SAVE_ALL_BUT_SP
	CLI
	TRACE_IRQS_OFF

	LONG_L  s0, TI_REGS($28)
	LONG_S  sp, TI_REGS($28)
	PTR_LA  ra, ret_from_irq
	move    a0, k1
	j       rlx_do_lopi_IRQ
	END(handle_vec)

	.macro	__build_clear_none
	.endm

	.macro	__build_clear_sti
	TRACE_IRQS_ON
	STI
	.endm

	.macro	__build_clear_cli
	CLI
	TRACE_IRQS_OFF
	.endm

#ifdef CONFIG_CPU_HAS_FPU
	.macro	__build_clear_fpe
	.set	push
	cfc1	a1, fcr31
	li	a2, ~(0x3f << 12)
	and	a2, a1
	ctc1	a2, fcr31
	.set	pop
	TRACE_IRQS_ON
	STI
	.endm
#endif

	.macro	__build_clear_ade
	MFC0	t0, CP0_BADVADDR
	PTR_S	t0, PT_BVADDR(sp)
	KMODE
	.endm

	.macro	__BUILD_silent exception
	.endm

	/* Gas tries to parse the PRINT argument as a string containing
	   string escapes and emits bogus warnings if it believes to
	   recognize an unknown escape code.  So make the arguments
	   start with an n and gas will believe \n is ok ...  */
	.macro	__BUILD_verbose nexception
	LONG_L	a1, PT_EPC(sp)
	PRINT("Got \nexception at %08lx\012")
	.endm

	.macro	__BUILD_count exception
	LONG_L	t0,exception_count_\exception
	LONG_ADDIU t0, 1
	LONG_S	t0,exception_count_\exception
	.comm	exception_count\exception, 8, 8
	.endm

	.macro	__BUILD_HANDLER exception handler clear verbose ext
	.align	5
	NESTED(handle_\exception, PT_SIZE, sp)
	.set	noat
	SAVE_ALL
	FEXPORT(handle_\exception\ext)
	__BUILD_clear_\clear
	.set	at
	__BUILD_\verbose \exception
	move	a0, sp
	PTR_LA	ra, ret_from_exception
	j	do_\handler
	END(handle_\exception)
	.endm

	.macro	BUILD_HANDLER exception handler clear verbose
	__BUILD_HANDLER \exception \handler \clear \verbose _int
	.endm

	BUILD_HANDLER adel ade ade silent		/* #4  */
	BUILD_HANDLER ades ade ade silent		/* #5  */
#ifdef CONFIG_CPU_HAS_BUS_ERROR
	BUILD_HANDLER ibe be cli silent			/* #6  */
	BUILD_HANDLER dbe be cli silent			/* #7  */
#endif
	BUILD_HANDLER bp bp sti silent			/* #9  */
	BUILD_HANDLER ri ri sti silent			/* #10 */
	BUILD_HANDLER cpu cpu sti silent		/* #11 */
	BUILD_HANDLER ov ov sti silent			/* #12 */
#ifdef CONFIG_CPU_HAS_FPU
	BUILD_HANDLER fpe fpe fpe silent		/* #15 */
#endif
#ifdef CONFIG_CPU_HAS_WMPU
	/*
	 * For watch, interrupts will be enabled after the watch
	 * registers are read.
	 */
	BUILD_HANDLER watch watch cli silent		/* #23 */
#endif
	BUILD_HANDLER reserved reserved sti verbose	/* others */

/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1994, 95, 96, 97, 98, 99, 2000 by Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 */
#ifndef _ASM_PTRACE_H
#define _ASM_PTRACE_H


#include <linux/compiler.h>
#include <linux/linkage.h>
#include <linux/types.h>
#include <asm/isadep.h>
#include <uapi/asm/ptrace.h>

/*
 * This struct defines the way the registers are stored on the stack during a
 * system call/exception. As usual the registers k0/k1 aren't being saved.
 */
struct pt_regs {
#ifdef CONFIG_32BIT
	/* Pad bytes for argument save space on the stack. */
	unsigned long pad0[6];
#endif

	/* Saved main processor registers. */
	unsigned long regs[32];

	/* Saved special registers. */
	unsigned long cp0_status;
	unsigned long hi;
	unsigned long lo;
	unsigned long cp0_badvaddr;
	unsigned long cp0_cause;
	unsigned long cp0_epc;
} __aligned(8);

struct task_struct;

extern int ptrace_getregs(struct task_struct *child, __s64 __user *data);
extern int ptrace_setregs(struct task_struct *child, __s64 __user *data);

extern int ptrace_getfpregs(struct task_struct *child, __u32 __user *data);
extern int ptrace_setfpregs(struct task_struct *child, __u32 __user *data);

#ifdef CONFIG_CPU_HAS_WMPU
extern int ptrace_get_watch_regs(struct task_struct *child,
	struct pt_watch_regs __user *addr);
extern int ptrace_set_watch_regs(struct task_struct *child,
	struct pt_watch_regs __user *addr);

/* Set wmpu */
#define WMPU_DW 0x1
#define WMPU_DR 0x2
#define WMPU_IX 0x4
#define MODE_MP 0x1
#define MODE_WP 0x0

extern int ptrace_wmpu_set(unsigned long, unsigned long,
			   unsigned char, unsigned char);
extern void ptrace_wmpu_clear(int);
#endif

/*
 * Does the process account for user or for system time?
 */
#define user_mode(regs) (((regs)->cp0_status & KU_MASK) == KU_USER)

static inline int is_syscall_success(struct pt_regs *regs)
{
	return !regs->regs[7];
}

static inline long regs_return_value(struct pt_regs *regs)
{
	if (is_syscall_success(regs))
		return regs->regs[2];
	else
		return -regs->regs[2];
}

#define instruction_pointer(regs) ((regs)->cp0_epc)
#define profile_pc(regs) instruction_pointer(regs)
#define user_stack_pointer(r) ((r)->regs[29])

extern asmlinkage void syscall_trace_enter(struct pt_regs *regs);
extern asmlinkage void syscall_trace_leave(struct pt_regs *regs);

extern void die(const char *, struct pt_regs *) __noreturn;

static inline void die_if_kernel(const char *str, struct pt_regs *regs)
{
	if (unlikely(!user_mode(regs)))
		die(str, regs);
}

#define current_pt_regs()						\
({									\
	unsigned long sp = (unsigned long)__builtin_frame_address(0);	\
	(struct pt_regs *)((sp | (THREAD_SIZE - 1)) + 1 - 32) - 1;	\
})

#endif /* _ASM_PTRACE_H */

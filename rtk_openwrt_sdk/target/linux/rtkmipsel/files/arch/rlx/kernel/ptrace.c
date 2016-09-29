/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1992 Ross Biro
 * Copyright (C) Linus Torvalds
 * Copyright (C) 1994, 95, 96, 97, 98, 2000 Ralf Baechle
 * Copyright (C) 1996 David S. Miller
 * Kevin D. Kissell, kevink@mips.com and Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 1999 MIPS Technologies, Inc.
 * Copyright (C) 2000 Ulf Carlsson
 *
 * At this time Linux/MIPS64 only supports syscall tracing, even for 32-bit
 * binaries.
 */
#include <linux/compiler.h>
#include <linux/context_tracking.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/errno.h>
#include <linux/ptrace.h>
#include <linux/smp.h>
#include <linux/user.h>
#include <linux/security.h>
#include <linux/audit.h>
#include <linux/seccomp.h>

#include <asm/byteorder.h>
#include <asm/cpu.h>
#include <asm/fpu.h>
#include <asm/rlxregs.h>
#include <asm/pgtable.h>
#include <asm/page.h>
#include <asm/uaccess.h>
#include <asm/bootinfo.h>
#include <asm/reg.h>

#ifdef CONFIG_CPU_HAS_WMPU
struct mips3264_watch_reg_state kwatch;

static int ptrace_wmpu_find_slot(void)
{
	struct cpuinfo_mips *c = &current_cpu_data;
	unsigned long wmpctl;
	unsigned long mask = 0x10;
	int num;

	wmpctl = read_lxc0_wmpctl();
	wmpctl = wmpctl >> 16;

	/* Return a usable register index in kernel space */
	for (num = c->watch_reg_use_cnt; num < c->watch_reg_count; num++) {
		if ((wmpctl & mask) == 0x0) {
			return num;
		}
		mask = mask << 1;
	}

	return -1;
}

static int ptrace_wmpu_calc_mask(unsigned long start, unsigned long end,
				 int *wmpuhi, int *wmpxmask)
{
	unsigned long boundary = end;
	unsigned int mask_bit = 0x1;
	int size;
	int shift = 1;

	if (start > end)
		return -EIO;

	size = end - start;
	size = size >> 3;

	/* Set shift = 0 if size < 8 bytes */
	if (mask_bit > size)
		shift = 0;
	else {
		while (mask_bit <= size) {
			mask_bit = mask_bit << 1;
			shift++;
		}
	}

	/* Make sure that wmpu can cover all the range */
	boundary = boundary | (mask_bit -1);
	if (boundary < end)
		shift++;

	if (shift <= 9)
		*wmpuhi = *wmpuhi | (mask_bit - 1);
	else {
		*wmpuhi = 0xff8;
		*wmpxmask |= ((mask_bit << 3) - 1);
	}

	return 0;
}

int ptrace_wmpu_set(unsigned long start, unsigned long end,
		    unsigned char attr, unsigned char mode)
{
	struct cpuinfo_mips *c = &current_cpu_data;
	unsigned int wmpuhi = 0x000;
	unsigned int wmpxmask = 0x00000000;
	unsigned int wmpctl = 0x0;
	int err, slot, idx;

	slot = ptrace_wmpu_find_slot();
	if (slot < 0) {
		printk(KERN_ERR "wmpu: unable to find free slot!\n");
		BUG();
	}

	err = ptrace_wmpu_calc_mask(start, end, &wmpuhi, &wmpxmask);
	if (err !=0) {
		printk(KERN_ERR "wmpu: unable to set mask!\n");
		BUG();
	}

	/*
	 * Set lo, hi, and wmpxmask register
	 *
	 * wmpu entries are either 0, 4, or 8.
	 *
	 * We assume half of the wmpu entries are reserved for kernel, so there
	 * are at most 4 entries reserved for kernel, and we use a global kwatch
	 * to hold those kernel wmpu entries.
	 *
	 * The mapping is tricky, but straightforward:
	 *
	 * if wmpu entries == 4: kwatch[0,1] => slot 2 and 3
	 * if wmpu entries == 8: kwatch[0,1,2,3] => slot 4, 5, 6 and 7
	 */

	idx = slot % (c->watch_reg_use_cnt);

	kwatch.watchhi[idx] = wmpuhi << 3;
	kwatch.watchlo[idx] = (start & 0xfffffff8) | attr;
	kwatch.wmpxmask[idx] = wmpxmask;

	switch (slot) {
	case 2:
		write_c0_watchlo2(kwatch.watchlo[0]);
		write_c0_watchhi2(0x40000000 | kwatch.watchhi[0]);
		write_lxc0_wmpxmask2(wmpxmask);
		break;
	case 3:
		write_c0_watchlo3(kwatch.watchlo[1]);
		write_c0_watchhi3(0x40000000 | kwatch.watchhi[1]);
		write_lxc0_wmpxmask3(wmpxmask);
		break;
	case 4:
		write_c0_watchlo4(kwatch.watchlo[0]);
		write_c0_watchhi4(0x40000000 | kwatch.watchhi[0]);
		write_lxc0_wmpxmask4(wmpxmask);
		break;
	case 5:
		write_c0_watchlo5(kwatch.watchlo[1]);
		write_c0_watchhi5(0x40000000 | kwatch.watchhi[1]);
		write_lxc0_wmpxmask5(wmpxmask);
		break;
	case 6:
		write_c0_watchlo6(kwatch.watchlo[2]);
		write_c0_watchhi6(0x40000000 | kwatch.watchhi[2]);
		write_lxc0_wmpxmask6(wmpxmask);
		break;
	case 7:
		write_c0_watchlo7(kwatch.watchlo[3]);
		write_c0_watchhi7(0x40000000 | kwatch.watchhi[3]);
		write_lxc0_wmpxmask7(wmpxmask);
		break;
	default:
		BUG();
		break;
	}

	/* Set wmpu ctrl register */
	wmpctl |= (0x1 << (slot + 16)) | 0x2 | mode;
	set_lxc0_wmpctl(wmpctl);
	return slot;
}

void ptrace_wmpu_clear(int slot)
{
	switch (slot) {
	case 2:
		write_c0_watchlo2(0);
		write_c0_watchhi2(0);
		write_lxc0_wmpxmask2(0);
		clear_lxc0_wmpctl(WMPCTLF_EE2);
		break;
	case 3:
		write_c0_watchlo3(0);
		write_c0_watchhi3(0);
		write_lxc0_wmpxmask3(0);
		clear_lxc0_wmpctl(WMPCTLF_EE3);
		break;
	case 4:
		write_c0_watchlo4(0);
		write_c0_watchhi4(0);
		write_lxc0_wmpxmask4(0);
		clear_lxc0_wmpctl(WMPCTLF_EE4);
		break;
	case 5:
		write_c0_watchlo5(0);
		write_c0_watchhi5(0);
		write_lxc0_wmpxmask5(0);
		clear_lxc0_wmpctl(WMPCTLF_EE5);
		break;
	case 6:
		write_c0_watchlo6(0);
		write_c0_watchhi6(0);
		write_lxc0_wmpxmask6(0);
		clear_lxc0_wmpctl(WMPCTLF_EE6);
		break;
	case 7:
		write_c0_watchlo7(0);
		write_c0_watchhi7(0);
		write_lxc0_wmpxmask7(0);
		clear_lxc0_wmpctl(WMPCTLF_EE7);
		break;
	default:
		printk(KERN_ERR "wmpu: clear wmpu fail!\n");
		BUG();
		break;
	}
}
#endif

/*
 * Called by kernel/ptrace.c when detaching..
 *
 * Make sure single step bits etc are not set.
 */
void ptrace_disable(struct task_struct *child)
{
	/* Don't load the watchpoint registers for the ex-child. */
#ifdef CONFIG_CPU_HAS_WMPU
	clear_tsk_thread_flag(child, TIF_LOAD_WATCH);
#endif
}

/*
 * Read a general register set.	 We always use the 64-bit format, even
 * for 32-bit kernels and for 32-bit processes on a 64-bit kernel.
 * Registers are sign extended to fill the available space.
 */
int ptrace_getregs(struct task_struct *child, __s64 __user *data)
{
	struct pt_regs *regs;
	int i;

	if (!access_ok(VERIFY_WRITE, data, 38 * 8))
		return -EIO;

	regs = task_pt_regs(child);

	for (i = 0; i < 32; i++)
		__put_user((long)regs->regs[i], data + i);
	__put_user((long)regs->lo, data + EF_LO - EF_R0);
	__put_user((long)regs->hi, data + EF_HI - EF_R0);
	__put_user((long)regs->cp0_epc, data + EF_CP0_EPC - EF_R0);
	__put_user((long)regs->cp0_badvaddr, data + EF_CP0_BADVADDR - EF_R0);
	__put_user((long)regs->cp0_status, data + EF_CP0_STATUS - EF_R0);
	__put_user((long)regs->cp0_cause, data + EF_CP0_CAUSE - EF_R0);

	return 0;
}

/*
 * Write a general register set.  As for PTRACE_GETREGS, we always use
 * the 64-bit format.  On a 32-bit kernel only the lower order half
 * (according to endianness) will be used.
 */
int ptrace_setregs(struct task_struct *child, __s64 __user *data)
{
	struct pt_regs *regs;
	int i;

	if (!access_ok(VERIFY_READ, data, 38 * 8))
		return -EIO;

	regs = task_pt_regs(child);

	for (i = 0; i < 32; i++)
		__get_user(regs->regs[i], data + i);
	__get_user(regs->lo, data + EF_LO - EF_R0);
	__get_user(regs->hi, data + EF_HI - EF_R0);
	__get_user(regs->cp0_epc, data + EF_CP0_EPC - EF_R0);

	/* badvaddr, status, and cause may not be written.  */

	return 0;
}

#ifdef CONFIG_CPU_HAS_FPU
int ptrace_getfpregs(struct task_struct *child, __u32 __user *data)
{
	int i;
	unsigned int tmp;

	if (!access_ok(VERIFY_WRITE, data, 33 * 8))
		return -EIO;

	if (tsk_used_math(child)) {
		fpureg_t *fregs = get_fpu_regs(child);
		for (i = 0; i < 32; i++)
			__put_user(fregs[i], i + (__u64 __user *) data);
	} else {
		for (i = 0; i < 32; i++)
			__put_user((__u64) -1, i + (__u64 __user *) data);
	}

	__put_user(child->thread.fpu.fcr31, data + 64);

	preempt_disable();
	if (cpu_has_fpu) {
		unsigned int flags;

		flags = read_c0_status();
		__enable_fpu();
		__asm__ __volatile__("cfc1\t%0,$0" : "=r" (tmp));
		write_c0_status(flags);
	} else {
		tmp = 0;
	}
	preempt_enable();
	__put_user(tmp, data + 65);

	return 0;
}

int ptrace_setfpregs(struct task_struct *child, __u32 __user *data)
{
	fpureg_t *fregs;
	int i;

	if (!access_ok(VERIFY_READ, data, 33 * 8))
		return -EIO;

	fregs = get_fpu_regs(child);

	for (i = 0; i < 32; i++)
		__get_user(fregs[i], i + (__u64 __user *) data);

	__get_user(child->thread.fpu.fcr31, data + 64);

	/* FIR may not be written.  */

	return 0;
}
#else
int ptrace_getfpregs(struct task_struct *child, __u32 __user *data)
{
	int i;

	if (!access_ok(VERIFY_WRITE, data, 33 * 8))
		return -EIO;

	for (i = 0; i < 32; i++)
		__put_user((__u64) -1, i + (__u64 __user *) data);

	__put_user(0, data + 64);
	__put_user(0, data + 65);

	return 0;
}

int ptrace_setfpregs(struct task_struct *child, __u32 __user *data)
{
	if (!access_ok(VERIFY_READ, data, 33 * 8))
		return -EIO;

	return 0;
}
#endif

#ifdef CONFIG_CPU_HAS_WMPU
int ptrace_get_watch_regs(struct task_struct *child,
			  struct pt_watch_regs __user *addr)
{
	enum pt_watch_style style;
	int i;

	if (!cpu_has_watch || current_cpu_data.watch_reg_use_cnt == 0)
		return -EIO;
	if (!access_ok(VERIFY_WRITE, addr, sizeof(struct pt_watch_regs)))
		return -EIO;

#ifdef CONFIG_32BIT
	style = pt_watch_style_mips32;
#define WATCH_STYLE mips32
#else
	style = pt_watch_style_mips64;
#define WATCH_STYLE mips64
#endif

	__put_user(style, &addr->style);
	__put_user(current_cpu_data.watch_reg_use_cnt,
		   &addr->WATCH_STYLE.num_valid);
	for (i = 0; i < current_cpu_data.watch_reg_use_cnt; i++) {
		__put_user(child->thread.watch.mips3264.watchlo[i],
			   &addr->WATCH_STYLE.watchlo[i]);
		__put_user(child->thread.watch.mips3264.watchhi[i] & 0xfff,
			   &addr->WATCH_STYLE.watchhi[i]);
		__put_user(current_cpu_data.watch_reg_masks[i],
			   &addr->WATCH_STYLE.watch_masks[i]);
	}
	for (; i < 8; i++) {
		__put_user(0, &addr->WATCH_STYLE.watchlo[i]);
		__put_user(0, &addr->WATCH_STYLE.watchhi[i]);
		__put_user(0, &addr->WATCH_STYLE.watch_masks[i]);
	}

	return 0;
}

int ptrace_set_watch_regs(struct task_struct *child,
			  struct pt_watch_regs __user *addr)
{
	int i;
	int watch_active = 0;
	unsigned long lt[NUM_WATCH_REGS];
	u16 ht[NUM_WATCH_REGS];

	if (!cpu_has_watch || current_cpu_data.watch_reg_use_cnt == 0)
		return -EIO;
	if (!access_ok(VERIFY_READ, addr, sizeof(struct pt_watch_regs)))
		return -EIO;
	/* Check the values. */
	for (i = 0; i < current_cpu_data.watch_reg_use_cnt; i++) {
		__get_user(lt[i], &addr->WATCH_STYLE.watchlo[i]);
#ifdef CONFIG_32BIT
		if (lt[i] & __UA_LIMIT)
			return -EINVAL;
#else
		if (test_tsk_thread_flag(child, TIF_32BIT_ADDR)) {
			if (lt[i] & 0xffffffff80000000UL)
				return -EINVAL;
		} else {
			if (lt[i] & __UA_LIMIT)
				return -EINVAL;
		}
#endif
		__get_user(ht[i], &addr->WATCH_STYLE.watchhi[i]);
		if (ht[i] & ~0xff8)
			return -EINVAL;
	}
	/* Install them. */
	for (i = 0; i < current_cpu_data.watch_reg_use_cnt; i++) {
		if (lt[i] & 7)
			watch_active = 1;
		child->thread.watch.mips3264.watchlo[i] = lt[i];
		/* Set the G bit. */
		child->thread.watch.mips3264.watchhi[i] = ht[i];
	}

	if (watch_active)
		set_tsk_thread_flag(child, TIF_LOAD_WATCH);
	else
		clear_tsk_thread_flag(child, TIF_LOAD_WATCH);

	return 0;
}
#endif

long arch_ptrace(struct task_struct *child, long request,
		 unsigned long addr, unsigned long data)
{
	int ret;
#ifdef CONFIG_CPU_HAS_WMPU
	void __user *addrp = (void __user *) addr;
#endif
	void __user *datavp = (void __user *) data;
	unsigned long __user *datalp = (void __user *) data;

	switch (request) {
	/* when I and D space are separate, these will need to be fixed. */
	case PTRACE_PEEKTEXT: /* read word at location addr. */
	case PTRACE_PEEKDATA:
		ret = generic_ptrace_peekdata(child, addr, data);
		break;

	/* Read the word at location addr in the USER area. */
	case PTRACE_PEEKUSR: {
		struct pt_regs *regs;
		unsigned long tmp = 0;

		regs = task_pt_regs(child);
		ret = 0;  /* Default return value. */

		switch (addr) {
		case 0 ... 31:
			tmp = regs->regs[addr];
			break;
		case FPR_BASE ... FPR_BASE + 31:
#ifdef CONFIG_CPU_HAS_FPU
			if (tsk_used_math(child)) {
				fpureg_t *fregs = get_fpu_regs(child);

				/*
				 * The odd registers are actually the high
				 * order bits of the values stored in the even
				 * registers - unless we're using r2k_switch.S.
				 */
				if (addr & 1)
					tmp = (unsigned long) (fregs[((addr & ~1) - 32)] >> 32);
				else
					tmp = (unsigned long) (fregs[(addr - 32)] & 0xffffffff);
			} else {
				tmp = -1;	/* FP not yet used  */
			}
#else
			tmp = -1;	/* FP not yet used  */
#endif
			break;
		case PC:
			tmp = regs->cp0_epc;
			break;
		case CAUSE:
			tmp = regs->cp0_cause;
			break;
		case BADVADDR:
			tmp = regs->cp0_badvaddr;
			break;
		case MMHI:
			tmp = regs->hi;
			break;
		case MMLO:
			tmp = regs->lo;
			break;
		case FPC_CSR:
#ifdef CONFIG_CPU_HAS_FPU
			tmp = child->thread.fpu.fcr31;
#else
			tmp = 0;
#endif
			break;
		case FPC_EIR: {	/* implementation / version register */
#ifdef CONFIG_CPU_HAS_FPU
		      unsigned int flags;

		      preempt_disable();
		      if (!cpu_has_fpu) {
			      preempt_enable();
			      break;
		      }
		      flags = read_c0_status();
		      __enable_fpu();
		      __asm__ __volatile__("cfc1\t%0,$0": "=r" (tmp));
		      write_c0_status(flags);
		      preempt_enable();
#endif
		      break;
		}
		default:
			tmp = 0;
			ret = -EIO;
			goto out;
		}
		ret = put_user(tmp, datalp);
		break;
	}

	/* when I and D space are separate, this will have to be fixed. */
	case PTRACE_POKETEXT: /* write the word at location addr. */
	case PTRACE_POKEDATA:
		ret = generic_ptrace_pokedata(child, addr, data);
		break;

	case PTRACE_POKEUSR: {
		struct pt_regs *regs;
		ret = 0;
		regs = task_pt_regs(child);

		switch (addr) {
		case 0 ... 31:
			regs->regs[addr] = data;
			break;
		case FPR_BASE ... FPR_BASE + 31: {
#ifdef CONFIG_CPU_HAS_FPU
			fpureg_t *fregs = get_fpu_regs(child);

			if (!tsk_used_math(child)) {
				/* FP not yet used  */
				memset(&child->thread.fpu, ~0,
				       sizeof(child->thread.fpu));
				child->thread.fpu.fcr31 = 0;
			}
			/*
			 * The odd registers are actually the high order bits
			 * of the values stored in the even registers - unless
			 * we're using r2k_switch.S.
			 */
			if (addr & 1) {
				fregs[(addr & ~1) - FPR_BASE] &= 0xffffffff;
				fregs[(addr & ~1) - FPR_BASE] |= ((unsigned long long) data) << 32;
			} else {
				fregs[addr - FPR_BASE] &= ~0xffffffffLL;
				fregs[addr - FPR_BASE] |= data;
			}
#endif
			break;
		}
		case PC:
			regs->cp0_epc = data;
			break;
		case MMHI:
			regs->hi = data;
			break;
		case MMLO:
			regs->lo = data;
			break;
		case FPC_CSR:
#ifdef CONFIG_CPU_HAS_FPU
			child->thread.fpu.fcr31 = data;
#endif
			break;
		default:
			/* The rest are not allowed. */
			ret = -EIO;
			break;
		}
		break;
	}

	case PTRACE_GETREGS:
		ret = ptrace_getregs(child, datavp);
		break;

	case PTRACE_SETREGS:
		ret = ptrace_setregs(child, datavp);
		break;

	case PTRACE_GETFPREGS:
		ret = ptrace_getfpregs(child, datavp);
		break;

	case PTRACE_SETFPREGS:
		ret = ptrace_setfpregs(child, datavp);
		break;

	case PTRACE_GET_THREAD_AREA:
		ret = put_user(task_thread_info(child)->tp_value, datalp);
		break;

#ifdef CONFIG_CPU_HAS_WMPU
	case PTRACE_GET_WATCH_REGS:
		ret = ptrace_get_watch_regs(child, addrp);
		break;

	case PTRACE_SET_WATCH_REGS:
		if (read_lxc0_wmpctl() & 0x1) {
			ret = -EIO;
			goto out;
		}
		ret = ptrace_set_watch_regs(child, addrp);
		break;
#endif

	default:
		ret = ptrace_request(child, request, addr, data);
		break;
	}
 out:
	return ret;
}

static inline int audit_arch(void)
{
	int arch = EM_MIPS;
#ifdef CONFIG_CPU_LITTLE_ENDIAN
	arch |=  __AUDIT_ARCH_LE;
#endif
	return arch;
}

/*
 * Notification of system call entry/exit
 * - triggered by current->work.syscall_trace
 */
asmlinkage void syscall_trace_enter(struct pt_regs *regs)
{
	user_exit();

	/* do the secure computing check first */
	secure_computing_strict(regs->regs[2]);

	if (!(current->ptrace & PT_PTRACED))
		goto out;

	if (!test_thread_flag(TIF_SYSCALL_TRACE))
		goto out;

	/* The 0x80 provides a way for the tracing parent to distinguish
	   between a syscall stop and SIGTRAP delivery */
	ptrace_notify(SIGTRAP | ((current->ptrace & PT_TRACESYSGOOD) ?
				 0x80 : 0));

	/*
	 * this isn't the same as continuing with a signal, but it will do
	 * for normal use.  strace only continues with a signal if the
	 * stopping signal is not SIGTRAP.  -brl
	 */
	if (current->exit_code) {
		send_sig(current->exit_code, current, 1);
		current->exit_code = 0;
	}

out:
	audit_syscall_entry(audit_arch(), regs->regs[2],
			    regs->regs[4], regs->regs[5],
			    regs->regs[6], regs->regs[7]);
}

/*
 * Notification of system call entry/exit
 * - triggered by current->work.syscall_trace
 */
asmlinkage void syscall_trace_leave(struct pt_regs *regs)
{
        /*
	 * We may come here right after calling schedule_user()
	 * or do_notify_resume(), in which case we can be in RCU
	 * user mode.
	 */
	user_exit();

	audit_syscall_exit(regs);

	if (!(current->ptrace & PT_PTRACED))
		return;

	if (!test_thread_flag(TIF_SYSCALL_TRACE))
		return;

	/* The 0x80 provides a way for the tracing parent to distinguish
	   between a syscall stop and SIGTRAP delivery */
	ptrace_notify(SIGTRAP | ((current->ptrace & PT_TRACESYSGOOD) ?
				 0x80 : 0));

	/*
	 * this isn't the same as continuing with a signal, but it will do
	 * for normal use.  strace only continues with a signal if the
	 * stopping signal is not SIGTRAP.  -brl
	 */
	if (current->exit_code) {
		send_sig(current->exit_code, current, 1);
		current->exit_code = 0;
	}

	user_enter();
}

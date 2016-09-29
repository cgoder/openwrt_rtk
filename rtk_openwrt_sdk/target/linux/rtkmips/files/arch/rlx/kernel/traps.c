/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1994 - 1999, 2000, 01, 06 Ralf Baechle
 * Copyright (C) 1995, 1996 Paul M. Antoine
 * Copyright (C) 1998 Ulf Carlsson
 * Copyright (C) 1999 Silicon Graphics, Inc.
 * Kevin D. Kissell, kevink@mips.com and Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 2002, 2003, 2004, 2005, 2007  Maciej W. Rozycki
 * Copyright (C) 2000, 2001, 2012 MIPS Technologies, Inc.  All rights reserved.
 *
 * Modified for RLX Linux for RLX
 * Copyright (C) 2008-2013 Tony Wu (tonywu@realtek.com)
 */
#include <linux/bug.h>
#include <linux/compiler.h>
#include <linux/context_tracking.h>
#include <linux/kexec.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/spinlock.h>
#include <linux/kallsyms.h>
#include <linux/bootmem.h>
#include <linux/interrupt.h>
#include <linux/ptrace.h>
#include <linux/kgdb.h>
#include <linux/kdebug.h>
#include <linux/kprobes.h>
#include <linux/notifier.h>
#include <linux/kdb.h>
#include <linux/irq.h>
#include <linux/perf_event.h>

#include <asm/bootinfo.h>
#include <asm/branch.h>
#include <asm/break.h>
#include <asm/cpu.h>
#include <asm/fpu.h>
#include <asm/idle.h>
#include <asm/rlxregs.h>
#include <asm/module.h>
#include <asm/pgtable.h>
#include <asm/ptrace.h>
#include <asm/sections.h>
#include <asm/tlbdebug.h>
#include <asm/traps.h>
#include <asm/uaccess.h>
#include <asm/watch.h>
#include <asm/mmu_context.h>
#include <asm/types.h>
#include <asm/stacktrace.h>
#include <asm/uasm.h>

extern asmlinkage void handle_int(void);
extern u32 handle_tlbl[];
extern u32 handle_tlbs[];
extern u32 handle_tlbm[];
extern asmlinkage void handle_adel(void);
extern asmlinkage void handle_ades(void);
#ifdef CONFIG_CPU_HAS_BUS_ERROR
extern asmlinkage void handle_ibe(void);
extern asmlinkage void handle_dbe(void);
#endif
extern asmlinkage void handle_sys(void);
extern asmlinkage void handle_bp(void);
extern asmlinkage void handle_ri(void);
extern asmlinkage void handle_cpu(void);
extern asmlinkage void handle_ov(void);
extern asmlinkage void handle_fpe(void);
#if defined(CONFIG_CPU_HAS_WMPU)
extern asmlinkage void handle_watch(void);
#endif
extern asmlinkage void handle_reserved(void);

#ifdef CONFIG_CPU_HAS_BUS_ERROR
void (*board_be_init)(void);
int (*board_be_handler)(struct pt_regs *regs, int is_fixup);
#endif

static void show_raw_backtrace(unsigned long reg29)
{
	unsigned long *sp = (unsigned long *)(reg29 & ~3);
	unsigned long addr;

	printk("Call Trace:");
#ifdef CONFIG_KALLSYMS
	printk("\n");
#endif
	while (!kstack_end(sp)) {
		unsigned long __user *p =
			(unsigned long __user *)(unsigned long)sp++;
		if (__get_user(addr, p)) {
			printk(" (Bad stack address)");
			break;
		}
		if (__kernel_text_address(addr))
			print_ip_sym(addr);
	}
	printk("\n");
}

#ifdef CONFIG_KALLSYMS
int raw_show_trace;
static int __init set_raw_show_trace(char *str)
{
	raw_show_trace = 1;
	return 1;
}
__setup("raw_show_trace", set_raw_show_trace);
#endif

static void show_backtrace(struct task_struct *task, const struct pt_regs *regs)
{
	unsigned long sp = regs->regs[29];
	unsigned long ra = regs->regs[31];
	unsigned long pc = regs->cp0_epc;

	if (!task)
		task = current;

	if (raw_show_trace || !__kernel_text_address(pc)) {
		show_raw_backtrace(sp);
		return;
	}
	printk("Call Trace:\n");
	do {
		print_ip_sym(pc);
		pc = unwind_stack(task, &sp, pc, &ra);
	} while (pc);
	printk("\n");
}

/*
 * This routine abuses get_user()/put_user() to reference pointers
 * with at least a bit of error checking ...
 */
static void show_stacktrace(struct task_struct *task,
	const struct pt_regs *regs)
{
	const int field = 2 * sizeof(unsigned long);
	long stackdata;
	int i;
	unsigned long __user *sp = (unsigned long __user *)regs->regs[29];

	printk("Stack :");
	i = 0;
	while ((unsigned long) sp & (PAGE_SIZE - 1)) {
		if (i && ((i % (64 / field)) == 0))
			printk("\n	 ");
		if (i > 39) {
			printk(" ...");
			break;
		}

		if (__get_user(stackdata, sp++)) {
			printk(" (Bad stack address)");
			break;
		}

		printk(" %0*lx", field, stackdata);
		i++;
	}
	printk("\n");
	show_backtrace(task, regs);
}

void show_stack(struct task_struct *task, unsigned long *sp)
{
	struct pt_regs regs;
	if (sp) {
		regs.regs[29] = (unsigned long)sp;
		regs.regs[31] = 0;
		regs.cp0_epc = 0;
	} else {
		if (task && task != current) {
			regs.regs[29] = task->thread.reg29;
			regs.regs[31] = 0;
			regs.cp0_epc = task->thread.reg31;
#ifdef CONFIG_KGDB_KDB
		} else if (atomic_read(&kgdb_active) != -1 &&
			   kdb_current_regs) {
			memcpy(&regs, kdb_current_regs, sizeof(regs));
#endif /* CONFIG_KGDB_KDB */
		} else {
			prepare_frametrace(&regs);
		}
	}
	show_stacktrace(task, &regs);
}

static void show_code(unsigned int __user *pc)
{
	long i;
	unsigned short __user *pc16 = NULL;

	printk("\nCode:");

	if ((unsigned long)pc & 1)
		pc16 = (unsigned short __user *)((unsigned long)pc & ~1);
	for(i = -3 ; i < 6 ; i++) {
		unsigned int insn;
		if (pc16 ? __get_user(insn, pc16 + i) : __get_user(insn, pc + i)) {
			printk(" (Bad address in epc)\n");
			break;
		}
		printk("%c%0*x%c", (i?' ':'<'), pc16 ? 4 : 8, insn, (i?' ':'>'));
	}
}

#ifdef CONFIG_CPU_HAS_RADIAX
static void __show_radiax(struct task_struct *tsk)
{
	struct mips_radiax_struct *regs = &tsk->thread.radiax;

	printk("CBS0  : %08x\n", (uint32_t)regs->radiaxr[0]);
	printk("CBS1  : %08x\n", (uint32_t)regs->radiaxr[1]);
	printk("CBS2  : %08x\n", (uint32_t)regs->radiaxr[2]);
	printk("CBE0  : %08x\n", (uint32_t)regs->radiaxr[3]);
	printk("CBE1  : %08x\n", (uint32_t)regs->radiaxr[4]);
	printk("CBE2  : %08x\n", (uint32_t)regs->radiaxr[5]);
	printk("LPS0  : %08x\n", (uint32_t)regs->radiaxr[6]);
	printk("LPE0  : %08x\n", (uint32_t)regs->radiaxr[7]);
	printk("LPC0  : %08x\n", (uint32_t)regs->radiaxr[8]);
	printk("MMD   : %08x\n", (uint32_t)regs->radiaxr[9]);
	printk("M0LL  : %08x\n", (uint32_t)regs->radiaxr[10]);
	printk("M0LH  : %08x\n", (uint32_t)regs->radiaxr[11]);
	printk("M0HL  : %08x\n", (uint32_t)regs->radiaxr[12]);
	printk("M0HH  : %08x\n", (uint32_t)regs->radiaxr[13]);
	printk("M1LL  : %08x\n", (uint32_t)regs->radiaxr[14]);
	printk("M1LH  : %08x\n", (uint32_t)regs->radiaxr[15]);
	printk("M1HL  : %08x\n", (uint32_t)regs->radiaxr[16]);
	printk("M1HH  : %08x\n", (uint32_t)regs->radiaxr[17]);
	printk("M2LL  : %08x\n", (uint32_t)regs->radiaxr[18]);
	printk("M2LH  : %08x\n", (uint32_t)regs->radiaxr[19]);
	printk("M2HL  : %08x\n", (uint32_t)regs->radiaxr[20]);
	printk("M2HH  : %08x\n", (uint32_t)regs->radiaxr[21]);
	printk("M3LL  : %08x\n", (uint32_t)regs->radiaxr[22]);
	printk("M3LH  : %08x\n", (uint32_t)regs->radiaxr[23]);
	printk("M3HL  : %08x\n", (uint32_t)regs->radiaxr[24]);
	printk("N3HH  : %08x\n", (uint32_t)regs->radiaxr[25]);
}
#endif

static void __show_regs(const struct pt_regs *regs)
{
	const int field = 2 * sizeof(unsigned long);
	unsigned int cause = regs->cp0_cause;
	int i;

	show_regs_print_info(KERN_DEFAULT);

	/*
	 * Saved main processor registers
	 */
	for (i = 0; i < 32; ) {
		if ((i % 4) == 0)
			printk("$%2d   :", i);
		if (i == 0)
			printk(" %0*lx", field, 0UL);
		else if (i == 26 || i == 27)
			printk(" %*s", field, "");
		else
			printk(" %0*lx", field, regs->regs[i]);

		i++;
		if ((i % 4) == 0)
			printk("\n");
	}

	printk("Hi    : %0*lx\n", field, regs->hi);
	printk("Lo    : %0*lx\n", field, regs->lo);

	/*
	 * Saved cp0 registers
	 */
	printk("epc   : %0*lx %pS\n", field, regs->cp0_epc,
	       (void *) regs->cp0_epc);
	printk("    %s\n", print_tainted());
	printk("ra    : %0*lx %pS\n", field, regs->regs[31],
	       (void *) regs->regs[31]);

	printk("Status: %08x	", (uint32_t) regs->cp0_status);

	if (regs->cp0_status & ST0_KUO) printk("KUo ");
	if (regs->cp0_status & ST0_IEO) printk("IEo ");
	if (regs->cp0_status & ST0_KUP) printk("KUp ");
	if (regs->cp0_status & ST0_IEP) printk("IEp ");
	if (regs->cp0_status & ST0_KUC) printk("KUc ");
	if (regs->cp0_status & ST0_IEC) printk("IEc ");

	printk("\n");
	printk("Cause : %08x\n", cause);

	cause = (cause & CAUSEF_EXCCODE) >> CAUSEB_EXCCODE;
	if (1 <= cause && cause <= 5)
		printk("BadVA : %0*lx\n", field, regs->cp0_badvaddr);

	printk("PrId  : %08x\n", read_c0_prid());

#ifdef CONFIG_CPU_HAS_RADIAX
	__show_radiax(current);
#endif
}

/*
 * FIXME: really the generic show_regs should take a const pointer argument.
 */
void show_regs(struct pt_regs *regs)
{
	__show_regs((struct pt_regs *)regs);
}

void show_registers(struct pt_regs *regs)
{
	const int field = 2 * sizeof(unsigned long);

	__show_regs(regs);
	print_modules();
	printk("Process %s (pid: %d, threadinfo=%p, task=%p, tls=%0*lx)\n",
	       current->comm, current->pid, current_thread_info(), current,
	      field, current_thread_info()->tp_value);
	if (cpu_has_userlocal) {
		unsigned long tls;

		tls = read_lxc0_userlocal();
		if (tls != current_thread_info()->tp_value)
			printk("*HwTLS: %0*lx\n", field, tls);
	}

#ifdef CONFIG_CPU_HAS_TLS
    {
        unsigned long tls;

        tls = read_lxc0_userlocal();
        if (tls != current_thread_info()->tp_value)
            printk("*HwTLS: %0*lx\n", field, tls);
    }
#endif
	show_stacktrace(current, regs);
	show_code((unsigned int __user *) regs->cp0_epc);
	printk("\n");
}

static int regs_to_trapnr(struct pt_regs *regs)
{
	return (regs->cp0_cause >> 2) & 0x1f;
}

static DEFINE_RAW_SPINLOCK(die_lock);

void __noreturn die(const char *str, struct pt_regs *regs)
{
	static int die_counter;
	int sig = SIGSEGV;

	oops_enter();

	if (notify_die(DIE_OOPS, str, regs, 0, regs_to_trapnr(regs), SIGSEGV) == NOTIFY_STOP)
		sig = 0;

	console_verbose();
	raw_spin_lock_irq(&die_lock);
	bust_spinlocks(1);

	printk("%s[#%d]:\n", str, ++die_counter);
	show_registers(regs);
	add_taint(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);
	raw_spin_unlock_irq(&die_lock);

	oops_exit();

	if (in_interrupt())
		panic("Fatal exception in interrupt");

	if (panic_on_oops) {
		printk(KERN_EMERG "Fatal exception: panic in 5 seconds");
		ssleep(5);
		panic("Fatal exception");
	}

	if (regs && kexec_should_crash(current))
		crash_kexec(regs);

	do_exit(sig);
}

#ifdef CONFIG_CPU_HAS_BUS_ERROR
extern struct exception_table_entry __start___dbe_table[];
extern struct exception_table_entry __stop___dbe_table[];

__asm__(
"	.section	__dbe_table, \"a\"\n"
"	.previous			\n");

/* Given an address, look for it in the exception tables. */
static const struct exception_table_entry *search_dbe_tables(unsigned long addr)
{
	const struct exception_table_entry *e;

	e = search_extable(__start___dbe_table, __stop___dbe_table - 1, addr);
	if (!e)
		e = search_module_dbetables(addr);
	return e;
}

asmlinkage void do_be(struct pt_regs *regs)
{
	const int field = 2 * sizeof(unsigned long);
	const struct exception_table_entry *fixup = NULL;
	int data = regs->cp0_cause & 4;
	int action = MIPS_BE_FATAL;
	enum ctx_state prev_state;

	prev_state = exception_enter();
	/* XXX For now.	 Fixme, this searches the wrong table ...  */
	if (data && !user_mode(regs))
		fixup = search_dbe_tables(exception_epc(regs));

	if (fixup)
		action = MIPS_BE_FIXUP;

	if (board_be_handler)
		action = board_be_handler(regs, fixup != NULL);

	switch (action) {
	case MIPS_BE_DISCARD:
		goto out;
	case MIPS_BE_FIXUP:
		if (fixup) {
			regs->cp0_epc = fixup->nextinsn;
			goto out;
		}
		break;
	default:
		break;
	}

	/*
	 * Assume it would be too dangerous to continue ...
	 */
	printk(KERN_ALERT "%s bus error, epc == %0*lx, ra == %0*lx\n",
	       data ? "Data" : "Instruction",
	       field, regs->cp0_epc, field, regs->regs[31]);
	if (notify_die(DIE_OOPS, "bus error", regs, 0, regs_to_trapnr(regs), SIGBUS)
	    == NOTIFY_STOP)
		goto out;

	die_if_kernel("Oops", regs);
	force_sig(SIGBUS, current);

out:
	exception_exit(prev_state);
}
#endif

/*
 * ll/sc, rdhwr, sync emulation
 */

#define OPCODE 0xfc000000
#define BASE   0x03e00000
#define RT     0x001f0000
#define OFFSET 0x0000ffff
#define LL     0xc0000000
#define SC     0xe0000000
#define SPEC0  0x00000000
#define SPEC3  0x7c000000
#define RD     0x0000f800
#define FUNC   0x0000003f
#define SYNC   0x0000000f
#define RDHWR  0x0000003b

/*  MIPS16m definitions   */
#define MM_POOL32A_FUNC 0xfc00ffff
#define MM_RDHWR        0x00006b3c
#define MM_RS           0x001f0000
#define MM_RT           0x03e00000

/*
 * The ll_bit is cleared by r*_switch.S
 */

#ifndef CONFIG_CPU_HAS_LLSC
unsigned int ll_bit;
struct task_struct *ll_task;

static inline int simulate_ll(struct pt_regs *regs, unsigned int opcode)
{
	unsigned long value, __user *vaddr;
	long offset;

	/*
	 * analyse the ll instruction that just caused a ri exception
	 * and put the referenced address to addr.
	 */

	/* sign extend offset */
	offset = opcode & OFFSET;
	offset <<= 16;
	offset >>= 16;

	vaddr = (unsigned long __user *)
		((unsigned long)(regs->regs[(opcode & BASE) >> 21]) + offset);

	if ((unsigned long)vaddr & 3)
		return SIGBUS;
	if (get_user(value, vaddr))
		return SIGSEGV;

	preempt_disable();

	if (ll_task == NULL || ll_task == current) {
		ll_bit = 1;
	} else {
		ll_bit = 0;
	}
	ll_task = current;

	preempt_enable();

	regs->regs[(opcode & RT) >> 16] = value;

	return 0;
}

static inline int simulate_sc(struct pt_regs *regs, unsigned int opcode)
{
	unsigned long __user *vaddr;
	unsigned long reg;
	long offset;

	/*
	 * analyse the sc instruction that just caused a ri exception
	 * and put the referenced address to addr.
	 */

	/* sign extend offset */
	offset = opcode & OFFSET;
	offset <<= 16;
	offset >>= 16;

	vaddr = (unsigned long __user *)
		((unsigned long)(regs->regs[(opcode & BASE) >> 21]) + offset);
	reg = (opcode & RT) >> 16;

	if ((unsigned long)vaddr & 3)
		return SIGBUS;

	preempt_disable();

	if (ll_bit == 0 || ll_task != current) {
		regs->regs[reg] = 0;
		preempt_enable();
		return 0;
	}

	preempt_enable();

	if (put_user(regs->regs[reg], vaddr))
		return SIGSEGV;

	regs->regs[reg] = 1;

	return 0;
}

/*
 * ll uses the opcode of lwc0 and sc uses the opcode of swc0.  That is both
 * opcodes are supposed to result in coprocessor unusable exceptions if
 * executed on ll/sc-less processors.  That's the theory.  In practice a
 * few processors such as NEC's VR4100 throw reserved instruction exceptions
 * instead, so we're doing the emulation thing in both exception handlers.
 */
static int simulate_llsc(struct pt_regs *regs, unsigned int opcode)
{
	if ((opcode & OPCODE) == LL) {
		perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS,
				1, regs, 0);
		return simulate_ll(regs, opcode);
	}
	if ((opcode & OPCODE) == SC) {
		perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS,
				1, regs, 0);
		return simulate_sc(regs, opcode);
	}

	return -1;			/* Must be something else ... */
}
#endif

#ifndef CONFIG_CPU_HAS_SYNC
static int simulate_sync(struct pt_regs *regs, unsigned int opcode)
{
	if ((opcode & OPCODE) == SPEC0 && (opcode & FUNC) == SYNC) {
		perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS,
				1, regs, 0);
		return 0;
	}

	return -1;			/* Must be something else ... */
}
#endif

asmlinkage void do_ov(struct pt_regs *regs)
{
	enum ctx_state prev_state;
	siginfo_t info;

	prev_state = exception_enter();
	die_if_kernel("Integer overflow", regs);

	info.si_code = FPE_INTOVF;
	info.si_signo = SIGFPE;
	info.si_errno = 0;
	info.si_addr = (void __user *) regs->cp0_epc;
	force_sig_info(SIGFPE, &info, current);
	exception_exit(prev_state);
}

/*
 * XXX Delayed fp exceptions when doing a lazy ctx switch XXX
 */
#ifdef CONFIG_CPU_HAS_FPU
asmlinkage void do_fpe(struct pt_regs *regs, unsigned long fcr31)
{
	enum ctx_state prev_state;
	siginfo_t info = {0};

	prev_state = exception_enter();
	if (notify_die(DIE_FP, "FP exception", regs, 0, regs_to_trapnr(regs), SIGFPE)
	    == NOTIFY_STOP)
		goto out;
	die_if_kernel("FP exception in kernel code", regs);

	if (fcr31 & FPU_CSR_INV_X)
		info.si_code = FPE_FLTINV;
	else if (fcr31 & FPU_CSR_DIV_X)
		info.si_code = FPE_FLTDIV;
	else if (fcr31 & FPU_CSR_OVF_X)
		info.si_code = FPE_FLTOVF;
	else if (fcr31 & FPU_CSR_UDF_X)
		info.si_code = FPE_FLTUND;
	else if (fcr31 & FPU_CSR_INE_X)
		info.si_code = FPE_FLTRES;
	else
		info.si_code = __SI_FAULT;
	info.si_signo = SIGFPE;
	info.si_errno = 0;
	info.si_addr = (void __user *) regs->cp0_epc;
	force_sig_info(SIGFPE, &info, current);

out:
	exception_exit(prev_state);
}
#endif

static void do_trap_or_bp(struct pt_regs *regs, unsigned int code,
	const char *str)
{
	siginfo_t info;
	char b[40];

#ifdef CONFIG_KGDB_LOW_LEVEL_TRAP
	if (kgdb_ll_trap(DIE_TRAP, str, regs, code, regs_to_trapnr(regs), SIGTRAP) == NOTIFY_STOP)
		return;
#endif /* CONFIG_KGDB_LOW_LEVEL_TRAP */

	if (notify_die(DIE_TRAP, str, regs, code, regs_to_trapnr(regs), SIGTRAP) == NOTIFY_STOP)
		return;

	/*
	 * A short test says that IRIX 5.3 sends SIGTRAP for all trap
	 * insns, even for trap and break codes that indicate arithmetic
	 * failures.  Weird ...
	 * But should we continue the brokenness???  --macro
	 */
	switch (code) {
	case BRK_OVERFLOW:
	case BRK_DIVZERO:
		scnprintf(b, sizeof(b), "%s instruction in kernel code", str);
		die_if_kernel(b, regs);
		if (code == BRK_DIVZERO)
			info.si_code = FPE_INTDIV;
		else
			info.si_code = FPE_INTOVF;
		info.si_signo = SIGFPE;
		info.si_errno = 0;
		info.si_addr = (void __user *) regs->cp0_epc;
		force_sig_info(SIGFPE, &info, current);
		break;
	case BRK_BUG:
		die_if_kernel("Kernel bug detected", regs);
		force_sig(SIGTRAP, current);
		break;
	default:
		scnprintf(b, sizeof(b), "%s instruction in kernel code", str);
		die_if_kernel(b, regs);
		force_sig(SIGTRAP, current);
	}
}

asmlinkage void do_bp(struct pt_regs *regs)
{
	unsigned int opcode, bcode;
	enum ctx_state prev_state;
	unsigned long epc;
	u16 instr[2];

	prev_state = exception_enter();
	if (get_isa16_mode(regs->cp0_epc)) {
		/* Calculate EPC. */
		epc = exception_epc(regs);
		if (cpu_has_mmips) {
			if ((__get_user(instr[0], (u16 __user *)msk_isa16_mode(epc)) ||
			    (__get_user(instr[1], (u16 __user *)msk_isa16_mode(epc + 2)))))
				goto out_sigsegv;
			opcode = (instr[0] << 16) | instr[1];
		} else {
			/* MIPS16e mode */
			if (__get_user(instr[0], (u16 __user *)msk_isa16_mode(epc)))
				goto out_sigsegv;
			bcode = (instr[0] >> 6) & 0x3f;
			do_trap_or_bp(regs, bcode, "Break");
			goto out;
		}
	} else {
		if (__get_user(opcode, (unsigned int __user *) exception_epc(regs)))
			goto out_sigsegv;
	}

	/*
	 * There is the ancient bug in the MIPS assemblers that the break
	 * code starts left to bit 16 instead to bit 6 in the opcode.
	 * Gas is bug-compatible, but not always, grrr...
	 * We handle both cases with a simple heuristics.  --macro
	 */
	bcode = ((opcode >> 6) & ((1 << 20) - 1));
	if (bcode >= (1 << 10))
		bcode >>= 10;

	/*
	 * notify the kprobe handlers, if instruction is likely to
	 * pertain to them.
	 */
	switch (bcode) {
	case BRK_KPROBE_BP:
		if (notify_die(DIE_BREAK, "debug", regs, bcode, regs_to_trapnr(regs), SIGTRAP) == NOTIFY_STOP)
			goto out;
		else
			break;
	case BRK_KPROBE_SSTEPBP:
		if (notify_die(DIE_SSTEPBP, "single_step", regs, bcode, regs_to_trapnr(regs), SIGTRAP) == NOTIFY_STOP)
			goto out;
		else
			break;
	default:
		break;
	}

	do_trap_or_bp(regs, bcode, "Break");

out:
	exception_exit(prev_state);
	return;

out_sigsegv:
	force_sig(SIGSEGV, current);
	goto out;
}

asmlinkage void do_ri(struct pt_regs *regs)
{
	unsigned int __user *epc = (unsigned int __user *)exception_epc(regs);
	unsigned long old_epc = regs->cp0_epc;
	unsigned long old31 = regs->regs[31];
	enum ctx_state prev_state;
	unsigned int opcode = 0;
	int status = -1;

	prev_state = exception_enter();
	if (notify_die(DIE_RI, "RI Fault", regs, 0, regs_to_trapnr(regs), SIGILL)
	    == NOTIFY_STOP)
		goto out;

	die_if_kernel("Reserved instruction in kernel code", regs);

	if (unlikely(compute_return_epc(regs) < 0))
		goto out;

	if (unlikely(get_user(opcode, epc) < 0))
		status = SIGSEGV;

#ifndef CONFIG_CPU_HAS_LLSC
	if (status < 0)
		status = simulate_llsc(regs, opcode);
#endif

#ifndef CONFIG_CPU_HAS_SYNC
	if (status < 0)
		status = simulate_sync(regs, opcode);
#endif

	if (status < 0)
		status = SIGILL;

	if (unlikely(status > 0)) {
		regs->cp0_epc = old_epc;		/* Undo skip-over.  */
		regs->regs[31] = old31;
		force_sig(status, current);
	}

out:
	exception_exit(prev_state);
}

asmlinkage void do_cpu(struct pt_regs *regs)
{
	enum ctx_state prev_state;
	unsigned int __user *epc;
	unsigned long old_epc, old31;
	unsigned int opcode;
	unsigned int cpid;
	int status;
	unsigned long __maybe_unused flags;

	prev_state = exception_enter();
	die_if_kernel("do_cpu invoked from kernel context!", regs);

	cpid = (regs->cp0_cause >> CAUSEB_CE) & 3;

	switch (cpid) {
	case 0:
		epc = (unsigned int __user *)exception_epc(regs);
		old_epc = regs->cp0_epc;
		old31 = regs->regs[31];
		opcode = 0;
		status = -1;

		if (unlikely(compute_return_epc(regs) < 0))
			goto out;

		if (unlikely(get_user(opcode, epc) < 0))
			status = SIGSEGV;

#ifndef CONFIG_CPU_HAS_LLSC
		if (status < 0)
			status = simulate_llsc(regs, opcode);
#endif
		if (status < 0)
			status = SIGILL;

		if (unlikely(status > 0)) {
			regs->cp0_epc = old_epc;	/* Undo skip-over.  */
			regs->regs[31] = old31;
			force_sig(status, current);
		}

		goto out;

	case 3:
		/*
		 * Old (MIPS I and MIPS II) processors will set this code
		 * for COP1X opcode instructions that replaced the original
		 * COP3 space.	We don't limit COP1 space instructions in
		 * the emulator according to the CPU ISA, so we want to
		 * treat COP1X instructions consistently regardless of which
		 * code the CPU chose.	Therefore we redirect this trap to
		 * the FP emulator too.
		 *
		 * Then some newer FPU-less processors use this code
		 * erroneously too, so they are covered by this choice
		 * as well.
		 */
		if (raw_cpu_has_fpu)
			break;
		/* Fall through.  */

	case 1:
#ifdef CONFIG_CPU_HAS_FPU
		if (used_math())	/* Using the FPU again.  */
			own_fpu(1);
		else {			/* First time FPU user.	 */
			init_fpu();
			set_used_math();
		}
		goto out;
#endif
	case 2:
		goto out;
	}

	force_sig(SIGILL, current);

out:
	exception_exit(prev_state);
}

/*
 * Called with interrupts disabled.
 */
#ifdef CONFIG_CPU_HAS_WMPU
asmlinkage void do_watch(struct pt_regs *regs)
{
	enum ctx_state prev_state;
	unsigned int wmpvaddr;
	unsigned int wmpstatus;
	unsigned char entry, attr;
	unsigned int regnum;
	struct cpuinfo_mips *c = &current_cpu_data;

	prev_state = exception_enter();
	/*
	 * If exception came from MPU, disable it and print out message.
	 */
	wmpvaddr = read_lxc0_wmpvaddr();
	wmpstatus = read_lxc0_wmpstatus();
	entry = wmpstatus >> 16;
	attr = wmpstatus & 0x7;
	regnum = 0x1 << c->watch_reg_use_cnt;

	if (entry >= regnum) {
		clear_lxc0_wmpctl(entry << 16);
		switch (attr) {
		case WMPU_DW:
			printk("WMPU: data write exception at 0x%x\n", wmpvaddr);
			break;
		case WMPU_DR:
			printk("WMPU: data read exception at 0x%x\n", wmpvaddr);
			break;
		case WMPU_IX:
			printk("WMPU: instruction execute exception at 0x%x\n", wmpvaddr);
			break;
		}
		show_regs(regs);
		panic("WMPU: Caught exception !");
	}

	/*
	 * If the current thread has the watch registers loaded, save
	 * their values and send SIGTRAP.  Otherwise another thread
	 * left the registers set, clear them and continue.
	 */
	if (test_tsk_thread_flag(current, TIF_LOAD_WATCH)) {
		rlx_read_watch_registers();
		local_irq_enable();
		force_sig(SIGTRAP, current);
	} else {
		rlx_clear_watch_registers();
		local_irq_enable();
	}
	exception_exit(prev_state);
}
#endif

asmlinkage void do_reserved(struct pt_regs *regs)
{
	/*
	 * Game over - no way to handle this if it ever occurs.	 Most probably
	 * caused by a new unknown cpu type or after another deadly
	 * hard/software error.
	 */
	show_regs(regs);
	panic("Caught reserved exception %ld - should not happen.",
	      (regs->cp0_cause & 0x7f) >> 2);
}

unsigned long exception_handlers[32];

void __init *set_except_vector(int n, void *addr)
{
	unsigned long handler = (unsigned long) addr;
	unsigned long old_handler;

	old_handler = xchg(&exception_handlers[n], handler);

	exception_handlers[n] = handler;
	return (void *)old_handler;
}

extern void tlb_init(void);

void __cpuinit per_cpu_trap_init(bool is_boot_cpu)
{
	unsigned int cpu = smp_processor_id();
	unsigned int status_set = ST0_CU0;

	/* clear CU* and BEV, enable CU0 */
	change_c0_status(ST0_CU|ST0_BEV, status_set);

	if (!cpu_data[cpu].asid_cache)
		cpu_data[cpu].asid_cache = ASID_FIRST_VERSION;

	atomic_inc(&init_mm.mm_count);
	current->active_mm = &init_mm;
	BUG_ON(current->mm);
	enter_lazy_tlb(&init_mm, current);

	if (!is_boot_cpu)
		cpu_cache_init();
	tlb_init();
	TLBMISS_HANDLER_SETUP();
}

#define RLX_TRAP_VEC_BASE  0x80000080
#define RLX_TRAP_VEC_SIZE  0x80

void __init trap_init(void)
{
	extern char rlx_trap_dispatch;
	unsigned long i;

#if defined(CONFIG_KGDB)
	if (kgdb_early_setup)
		return; /* Already done */
#endif

	per_cpu_trap_init(true);

	/*
	 * Setup default vectors
	 */
	for (i = 0; i <= 31; i++)
		set_except_vector(i, handle_reserved);

	set_except_vector(0, handle_int);
	set_except_vector(1, handle_tlbm);
	set_except_vector(2, handle_tlbl);
	set_except_vector(3, handle_tlbs);

	set_except_vector(4, handle_adel);
	set_except_vector(5, handle_ades);

#ifdef CONFIG_CPU_HAS_BUS_ERROR
	set_except_vector(6, handle_ibe);
	set_except_vector(7, handle_dbe);
#endif

	set_except_vector(8, handle_sys);
	set_except_vector(9, handle_bp);
	set_except_vector(10, handle_ri);
	set_except_vector(11, handle_cpu);
	set_except_vector(12, handle_ov);

#ifdef CONFIG_CPU_HAS_FPU
	set_except_vector(15, handle_fpe);
#endif

	/*
	 * Only some CPUs have the watch exceptions.
	 */
#ifdef CONFIG_CPU_HAS_WMPU
	set_except_vector(23, handle_watch);
#endif

	memcpy((void *) (RLX_TRAP_VEC_BASE), &rlx_trap_dispatch, RLX_TRAP_VEC_SIZE);

	local_flush_icache_range(RLX_TRAP_VEC_BASE, RLX_TRAP_VEC_BASE+RLX_TRAP_VEC_SIZE);

#ifdef CONFIG_CPU_HAS_BUS_ERROR
	sort_extable(__start___dbe_table, __stop___dbe_table);
#endif
}

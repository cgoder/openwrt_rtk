/*
 * tlb-rlx.c: RLX specific mmu/cache code.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 *
 * with a lot of changes to make this thing work for R3000s
 * Tx39XX R4k style caches added. HK
 * Copyright (C) 1998, 1999, 2000 Harald Koerfgen
 * Copyright (C) 1998 Gleb Raiko & Vladimir Roganov
 * Copyright (C) 2002  Ralf Baechle
 * Copyright (C) 2002  Maciej W. Rozycki
 *
 * Modified for RLX processors
 * Copyright (C) 2008-2011 Tony Wu (tonywu@realtek.com)
 */
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/smp.h>
#include <linux/mm.h>

#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/mmu_context.h>
#include <asm/tlbmisc.h>
#include <asm/isadep.h>
#include <asm/io.h>
#include <asm/bootinfo.h>
#include <asm/cpu.h>

#undef DEBUG_TLB

extern void build_tlb_refill_handler(void);

/* CP0 hazard avoidance. */
#define BARRIER		__asm__ __volatile__("" ::: "memory");

#define UNIQUE_ENTRYHI(idx)	(CKSEG0 + ((idx) << PAGE_SHIFT))
#define ENTER_CRITICAL(flags)	local_irq_save(flags)
#define EXIT_CRITICAL(flags)	local_irq_restore(flags)

#define FLUSH_ITLB
#define FLUSH_ITLB_VM(vma)

/* TLB operations. */
void local_flush_tlb_all(void)
{
	unsigned long flags;
	unsigned long old_ctx;
	int entry;

#ifdef DEBUG_TLB
	printk("[tlball]");
#endif

	ENTER_CRITICAL(flags);
	old_ctx = read_c0_entryhi() & ASID_MASK;
	write_c0_entrylo(0);
	entry = read_c0_wired();
	for (; entry < current_cpu_data.tlbsize; entry++) {
		write_c0_index(entry << 8);
		/* Make sure all entries differ. */
		write_c0_entryhi(UNIQUE_ENTRYHI(entry));
		BARRIER;
		tlb_write_indexed();
	}
	write_c0_entryhi(old_ctx);
	EXIT_CRITICAL(flags);
}

void local_flush_tlb_mm(struct mm_struct *mm)
{
	int cpu = smp_processor_id();

	if (cpu_context(cpu, mm) != 0) {
#ifdef DEBUG_TLB
		printk("[tlbmm<%lu>]", (unsigned long)cpu_context(cpu, mm));
#endif
		drop_mmu_context(mm, cpu);
	}
}

void local_flush_tlb_range(struct vm_area_struct *vma, unsigned long start,
			   unsigned long end)
{
	struct mm_struct *mm = vma->vm_mm;
	int cpu = smp_processor_id();

	if (cpu_context(cpu, mm) != 0) {
		unsigned long size, flags;

#ifdef DEBUG_TLB
		printk("[tlbrange<%lu,0x%08lx,0x%08lx>]",
			cpu_context(cpu, mm) & ASID_MASK, start, end);
#endif
		ENTER_CRITICAL(flags);
		size = (end - start + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
		if (size <= current_cpu_data.tlbsize) {
			int oldpid = read_c0_entryhi() & ASID_MASK;
			int newpid = cpu_context(cpu, mm) & ASID_MASK;

			start &= PAGE_MASK;
			end += PAGE_SIZE - 1;
			end &= PAGE_MASK;
			while (start < end) {
				int idx;

				write_c0_entryhi(start | newpid);
				start += PAGE_SIZE;	/* BARRIER */
				tlb_probe();
				idx = read_c0_index();
				write_c0_entrylo(0);
				if (idx < 0)		/* BARRIER */
					continue;
				/* Make sure all entries differ. */
				write_c0_entryhi(UNIQUE_ENTRYHI(idx));
				tlb_write_indexed();
			}
			write_c0_entryhi(oldpid);
		} else {
			drop_mmu_context(mm, cpu);
		}
		EXIT_CRITICAL(flags);
	}
}

void local_flush_tlb_kernel_range(unsigned long start, unsigned long end)
{
	unsigned long size, flags;

#ifdef DEBUG_TLB
	printk("[tlbrange<%lu,0x%08lx,0x%08lx>]", start, end);
#endif
	ENTER_CRITICAL(flags);
	size = (end - start + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
	if (size <= current_cpu_data.tlbsize) {
		int pid = read_c0_entryhi();

		start &= PAGE_MASK;
		end += PAGE_SIZE - 1;
		end &= PAGE_MASK;

		while (start < end) {
			int idx;

			write_c0_entryhi(start);
			start += PAGE_SIZE;		/* BARRIER */
			tlb_probe();
			idx = read_c0_index();
			write_c0_entrylo(0);
			if (idx < 0)			/* BARRIER */
				continue;
			/* Make sure all entries differ. */
			write_c0_entryhi(UNIQUE_ENTRYHI(idx));
			tlb_write_indexed();
		}
		write_c0_entryhi(pid);
	} else {
		local_flush_tlb_all();
	}
	EXIT_CRITICAL(flags);
}

void local_flush_tlb_page(struct vm_area_struct *vma, unsigned long page)
{
	int cpu = smp_processor_id();

	if (!vma || cpu_context(cpu, vma->vm_mm) != 0) {
		unsigned long flags;
		int oldpid, newpid, idx;

#ifdef DEBUG_TLB
		printk("[tlbpage<%lu,0x%08lx>]", cpu_context(cpu, vma->vm_mm), page);
#endif
		newpid = cpu_context(cpu, vma->vm_mm) & ASID_MASK;
		page &= PAGE_MASK;
		ENTER_CRITICAL(flags);
		oldpid = read_c0_entryhi() & ASID_MASK;
		write_c0_entryhi(page | newpid);
		BARRIER;
		tlb_probe();
		idx = read_c0_index();
		write_c0_entrylo(0);
		if (idx < 0)				/* BARRIER */
			goto finish;
		/* Make sure all entries differ. */
		write_c0_entryhi(UNIQUE_ENTRYHI(idx));
		tlb_write_indexed();

finish:
		write_c0_entryhi(oldpid);
		EXIT_CRITICAL(flags);
	}
}

/*
 * This one is only used for pages with the global bit set so we don't care
 * much about the ASID.
 */
void local_flush_tlb_one(unsigned long page)
{
	unsigned long flags;
	int oldpid, idx;

	ENTER_CRITICAL(flags);
	oldpid = read_c0_entryhi();
	page &= (PAGE_MASK << 1);
	write_c0_entryhi(page);
	tlb_probe();
	idx = read_c0_index();
	write_c0_entrylo(0);
	if (idx >= 0) {
		/* Make sure all entries differ. */
		write_c0_entryhi(UNIQUE_ENTRYHI(idx));
		tlb_write_indexed();
	}

	write_c0_entryhi(oldpid);
	FLUSH_ITLB;
	EXIT_CRITICAL(flags);
}

void __update_tlb(struct vm_area_struct *vma, unsigned long address, pte_t pte)
{
	unsigned long flags;
	int idx, pid;

	/*
	 * Handle debugger faulting in for debugee.
	 */
	if (current->active_mm != vma->vm_mm)
		return;

	ENTER_CRITICAL(flags);

	pid = read_c0_entryhi() & ASID_MASK;
#ifdef DEBUG_TLB
	if ((pid != (cpu_context(cpu, vma->vm_mm) & ASID_MASK))
	    || (cpu_context(cpu, vma->vm_mm) == 0)) {
		printk("update_mmu_cache: Wheee, bogus tlbpid mmpid=%lu tlbpid=%d\n",
		       (cpu_context(cpu, vma->vm_mm)), pid);
	}
#endif
	address &= PAGE_MASK;
	write_c0_entryhi(address | pid);
	BARRIER;
	tlb_probe();
	idx = read_c0_index();
	write_c0_entrylo(pte_val(pte));
	write_c0_entryhi(address | pid);
	if (idx < 0) {					/* BARRIER */
		tlb_write_random();
	} else {
		tlb_write_indexed();
	}
	write_c0_entryhi(pid);
	EXIT_CRITICAL(flags);
}

void __init add_wired_entry(unsigned long entrylo, unsigned long entryhi)
{
	unsigned long flags;
	unsigned long old_ctx;

	unsigned long w;

#ifdef DEBUG_TLB
	printk("[tlbwired<entry lo %8x, hi %8x\n>]\n",
	       entrylo, entryhi);
#endif

	ENTER_CRITICAL(flags);
	/* Save old context and create impossible VPN2 value */
	old_ctx = read_c0_entryhi() & ASID_MASK;
	w = read_c0_wired();
	write_c0_wired(w + 1);
	write_c0_index(w << 8);
	write_c0_entryhi(entryhi);
	write_c0_entrylo(entrylo);
	BARRIER;
	tlb_write_indexed();

	write_c0_entryhi(old_ctx);
	local_flush_tlb_all();
	EXIT_CRITICAL(flags);
}

void __cpuinit tlb_init(void)
{
	local_flush_tlb_all();

	build_tlb_refill_handler();
}

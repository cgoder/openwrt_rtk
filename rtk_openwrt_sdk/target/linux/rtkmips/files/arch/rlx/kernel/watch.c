/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2008 David Daney
 *
 * Modified for RLX Linux for RLX
 * Copyright (C) 2011-2012 Jethro Hsu (jethro@realtek.com)
 * Copyright (C) 2011-2012 Tony Wu (tonywu@realtek.com)
 */

#ifdef CONFIG_CPU_HAS_WMPU
#include <linux/sched.h>

#include <asm/processor.h>
#include <asm/watch.h>

/*
 * Install the watch registers for the current thread.	A maximum of
 * four registers are installed although the machine may have more.
 */
void rlx_install_watch_registers(void)
{
	struct mips3264_watch_reg_state *watches =
		&current->thread.watch.mips3264;
	unsigned int ctrl;
	switch (current_cpu_data.watch_reg_use_cnt) {
	default:
		BUG();
	case 4:
		write_c0_watchlo3(watches->watchlo[3]);
		write_c0_watchhi3(0x40000000 | watches->watchhi[3]);
		write_lxc0_wmpxmask3(watches->wmpxmask[3]);
		set_lxc0_wmpctl(WMPCTLF_EE3);
	case 3:
		write_c0_watchlo2(watches->watchlo[2]);
		write_c0_watchhi2(0x40000000 | watches->watchhi[2]);
		write_lxc0_wmpxmask2(watches->wmpxmask[2]);
		set_lxc0_wmpctl(WMPCTLF_EE2);
	case 2:
		write_c0_watchlo1(watches->watchlo[1]);
		write_c0_watchhi1(0x40000000 | watches->watchhi[1]);
		write_lxc0_wmpxmask1(watches->wmpxmask[1]);
		set_lxc0_wmpctl(WMPCTLF_EE1);
	case 1:
		write_c0_watchlo0(watches->watchlo[0]);
		write_c0_watchhi0(0x40000000 | watches->watchhi[0]);
		write_lxc0_wmpxmask0(watches->wmpxmask[0]);
		set_lxc0_wmpctl(WMPCTLF_EE0);
	}

	/*
	 * set WMPCTL register
	 */
	ctrl = read_lxc0_wmpctl();
	if (current_cpu_data.watch_mode)
		ctrl &= WMPCTLF_MS;

	if (current_cpu_data.watch_kernel)
		ctrl &= WMPCTLF_KE;
	write_lxc0_wmpctl(ctrl);
}

/*
 * Read back the watchhi registers so the user space debugger has
 * access to the I, R, and W bits.  A maximum of four registers are
 * read although the machine may have more.
 */
void rlx_read_watch_registers(void)
{
	struct mips3264_watch_reg_state *watches =
		&current->thread.watch.mips3264;
	unsigned int wmpstatus = read_lxc0_wmpstatus();

	switch (current_cpu_data.watch_reg_use_cnt) {
	default:
		BUG();
	case 4:
		watches->watchhi[3] = (read_c0_watchhi3() & 0x0fff);
		if (wmpstatus & WMPSTATUSF_EM3)
			watches->watchhi[3] |= (wmpstatus & 0x7);
	case 3:
		watches->watchhi[2] = (read_c0_watchhi2() & 0x0fff);
		if (wmpstatus & WMPSTATUSF_EM2)
			watches->watchhi[2] |= (wmpstatus & 0x7);
	case 2:
		watches->watchhi[1] = (read_c0_watchhi1() & 0x0fff);
		if (wmpstatus & WMPSTATUSF_EM1)
			watches->watchhi[1] |= (wmpstatus & 0x7);
	case 1:
		watches->watchhi[0] = (read_c0_watchhi0() & 0x0fff);
		if (wmpstatus & WMPSTATUSF_EM0)
			watches->watchhi[0] |= (wmpstatus & 0x7);
	}

	/* read badvaddr that caused watch or mpu exception */
	watches->wmpvaddr = read_lxc0_wmpvaddr();
 }

/*
 * Disable all watch registers.	 Although only four registers are
 * installed, all are cleared to eliminate the possibility of endless
 * looping in the watch handler.
 */
void rlx_clear_watch_registers(void)
{
	switch (current_cpu_data.watch_reg_count) {
	default:
		BUG();
	case 4:
		write_c0_watchlo3(0);
		clear_lxc0_wmpctl(WMPCTLF_EE3);
	case 3:
		write_c0_watchlo2(0);
		clear_lxc0_wmpctl(WMPCTLF_EE2);
	case 2:
		write_c0_watchlo1(0);
		clear_lxc0_wmpctl(WMPCTLF_EE1);
	case 1:
		write_c0_watchlo0(0);
		clear_lxc0_wmpctl(WMPCTLF_EE0);
	}
}

void __cpuinit rlx_probe_watch_registers(struct cpuinfo_mips *c)
{
	unsigned int t;

	if ((c->options & MIPS_CPU_WATCH) == 0)
		return;

	/* Taroko supports 0, 4, or 8 entries. */
	t = read_c0_watchhi3();
	if ((t & 0x80000000) == 0) {
		c->watch_reg_count = 4;
		c->watch_reg_use_cnt = 4;
	} else {
		c->watch_reg_count = 8;
		c->watch_reg_use_cnt = 8;
	}

	for (t = 0; t < c->watch_reg_count; t++)
		c->watch_reg_masks[t] = 0xfff;
}
#endif

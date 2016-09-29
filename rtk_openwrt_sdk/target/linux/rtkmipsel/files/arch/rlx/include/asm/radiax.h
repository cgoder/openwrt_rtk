/*
 * Realtek Semiconductor Corp.
 *
 * Radiax Register Definitions
 *
 * Copyright (C) 2012  Viller Hsiao (villerhsiao@realtek.com)
 */

#ifndef _ASM_RADIAX_H_
#define _ASM_RADIAX_H_

#ifdef CONFIG_CPU_HAS_RADIAX
#include <asm/cpu.h>
#include <asm/cpu-features.h>
#include <asm/rlxregs.h>

extern void _init_radiax(void);
extern void _save_radiax(struct task_struct *);
extern void _restore_radiax(struct task_struct *);

static inline void init_radiax(void)
{
	_init_radiax();
}

static inline void save_radiax(struct task_struct *tsk)
{
	_save_radiax(tsk);
}

static inline void restore_radiax(struct task_struct *tsk)
{
	_restore_radiax(tsk);
}

static inline radiaxreg_t *get_radiax_regs(struct task_struct *tsk)
{
	if (tsk == current)
		_save_radiax(current);

	return tsk->thread.radiax.radiaxr;
}
#endif

#endif /* _ASM_RADIAX_H_ */

#ifndef __ASM_IDLE_H
#define __ASM_IDLE_H

#include <linux/linkage.h>

#ifdef CONFIG_CPU_HAS_SLEEP
#define cpu_wait()			\
	__asm__ __volatile__(		\
		".set push	\n"	\
		".set noreorder \n"	\
		".set noat	\n"	\
		"mfc0 $1, $12	\n"	\
		"ori $1, 0x1f   \n"	\
		"xori $1, 0x1e  \n"	\
		"mtc0 $1, $12   \n"	\
		"sleep		\n"	\
		".set pop	\n"	\
	)
#else
#define cpu_wait()			\
	__asm__ __volatile__(		\
		".set push	\n"	\
		".set noreorder \n"	\
		".set noat	\n"	\
		"mfc0 $1, $12	\n"	\
		"ori $1, 0x1f   \n"	\
		"xori $1, 0x1e  \n"	\
		"mtc0 $1, $12   \n"	\
		".set pop	\n"	\
	)
#endif

#endif /* __ASM_IDLE_H  */

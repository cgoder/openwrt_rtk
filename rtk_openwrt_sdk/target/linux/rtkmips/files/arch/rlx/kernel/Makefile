#
# Makefile for the Linux/MIPS kernel.
#

extra-y		:= head.o

obj-y		+= cpu-probe.o branch.o entry.o genex.o idle.o irq.o process.o \
		   prom.o ptrace.o reset.o setup.o signal.o syscall.o \
		   time.o topology.o traps.o unaligned.o watch.o vdso.o

ifdef CONFIG_FUNCTION_TRACER
CFLAGS_REMOVE_ftrace.o = -pg
CFLAGS_REMOVE_early_printk.o = -pg
CFLAGS_REMOVE_perf_event.o = -pg
CFLAGS_REMOVE_perf_event_mipsxx.o = -pg
endif

obj-$(CONFIG_CEVT_RLX)		+= cevt-rlx.o
obj-$(CONFIG_CEVT_GIC)		+= cevt-gic.o
obj-$(CONFIG_CEVT_EXT)		+= cevt-ext.o
obj-$(CONFIG_CSRC_RLX)		+= csrc-rlx.o
obj-$(CONFIG_CSRC_GIC)		+= csrc-gic.o
obj-$(CONFIG_SYNC_RLX)		+= sync-rlx.o

obj-$(CONFIG_STACKTRACE)	+= stacktrace.o
obj-$(CONFIG_MODULES)		+= mips_ksyms.o module.o
obj-$(CONFIG_MODULES_USE_ELF_RELA) += module-rela.o

obj-$(CONFIG_FUNCTION_TRACER)	+= mcount.o ftrace.o

obj-y				+= rlx-switch.o
obj-$(CONFIG_CPU_HAS_FPU)	+= rlx-fpu.o

obj-$(CONFIG_SMP)		+= smp.o smp-amon.o
obj-$(CONFIG_SMP_UP)		+= smp-up.o
obj-$(CONFIG_SMP_CMP)		+= smp-cmp.o mmcr.o

obj-$(CONFIG_IRQ_CPU)		+= irq-cpu.o
obj-$(CONFIG_IRQ_VEC)		+= irq-vec.o
obj-$(CONFIG_IRQ_GIC)		+= irq-gic.o

obj-$(CONFIG_KPROBES)		+= kprobes.o
obj-$(CONFIG_32BIT)		+= scall32-o32.o

obj-$(CONFIG_KGDB)		+= kgdb.o
obj-$(CONFIG_PROC_FS)		+= proc.o

obj-$(CONFIG_KEXEC)		+= machine_kexec.o relocate_kernel.o crash.o
obj-$(CONFIG_CRASH_DUMP)	+= crash_dump.o
obj-$(CONFIG_EARLY_PRINTK)	+= early_printk.o
obj-$(CONFIG_SPINLOCK_TEST)	+= spinlock_test.o
obj-$(CONFIG_MIPS_MACHINE)	+= mips_machine.o

obj-$(CONFIG_PERF_EVENTS)	+= perf_event.o
obj-$(CONFIG_HW_PERF_EVENTS)	+= perf_event_mipsxx.o

obj-$(CONFIG_JUMP_LABEL)	+= jump_label.o

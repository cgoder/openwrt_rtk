#
# Makefile for the Linux/MIPS-specific parts of the memory manager.
#
# Modified for RLX processors
# Copyright (C) 2008-2011 Tony Wu (tonywu@realtek.com)
#

obj-y				+= cache.o dma-default.o extable.o fault.o \
				   gup.o init.o mmap.o page.o page-funcs.o \
				   tlbex.o tlbex-fault.o uasm-mips.o

obj-$(CONFIG_32BIT)		+= ioremap.o pgtable-32.o
obj-$(CONFIG_HIGHMEM)		+= highmem.o
obj-$(CONFIG_HUGETLB_PAGE)	+= hugetlbpage.o

obj-y				+= c-rlx.o tlb-rlx.o

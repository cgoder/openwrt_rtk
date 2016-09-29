	.file	1 "filter.c"
	.section .mdebug.abi32
	.previous
	.gnu_attribute 4, 3
	.text
	.align	2
	.set	nomips16
	.ent	dos_pkt_locate
	.type	dos_pkt_locate, @function
dos_pkt_locate:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	lw	$2,12($4)
	lui	$3,%hi(ConnectedIp)
	addiu	$3,$3,%lo(ConnectedIp)
	andi	$5,$2,0xff
	andi	$4,$2,0x3ff
	sll	$5,$5,2
	addu	$5,$5,$3
	sll	$3,$4,3
	sll	$4,$4,5
	lw	$5,0($5)
	addu	$4,$3,$4
	lui	$3,%hi(dos_pkt)
	addiu	$3,$3,%lo(dos_pkt)
	addu	$3,$3,$4
	lw	$4,28($3)
	bne	$2,$5,$L2
	nop

	bne	$2,$4,$L3
	nop

	sb	$0,0($3)
	j	$31
	move	$2,$0

$L2:
	beq	$2,$4,$L5
	nop

$L3:
	lb	$4,0($3)
	bne	$4,$0,$L6
	li	$4,1			# 0x1

	sb	$4,0($3)
	lui	$4,%hi(cur_p_pkt)
	sw	$2,28($3)
	li	$2,1			# 0x1
	j	$31
	sw	$3,%lo(cur_p_pkt)($4)

$L5:
	lb	$4,0($3)
	li	$2,1			# 0x1
	bne	$4,$2,$L7
	lui	$4,%hi(cur_p_pkt)

	j	$31
	sw	$3,%lo(cur_p_pkt)($4)

$L6:
	j	$31
	move	$2,$0

$L7:
	j	$31
	move	$2,$0

	.set	macro
	.set	reorder
	.end	dos_pkt_locate
	.size	dos_pkt_locate, .-dos_pkt_locate
	.align	2
	.set	nomips16
	.ent	dos_single_open
	.type	dos_single_open, @function
dos_single_open:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	move	$4,$5
	lui	$25,%hi(single_open)
	lui	$5,%hi(dos_read_proc)
	move	$6,$0
	addiu	$5,$5,%lo(dos_read_proc)
	addiu	$25,$25,%lo(single_open)
	jr	$25
	nop

	.set	macro
	.set	reorder
	.end	dos_single_open
	.size	dos_single_open, .-dos_single_open
	.align	2
	.globl	filter_table_single_open
	.set	nomips16
	.ent	filter_table_single_open
	.type	filter_table_single_open, @function
filter_table_single_open:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	move	$4,$5
	lui	$25,%hi(single_open)
	lui	$5,%hi(filter_table_read_proc)
	move	$6,$0
	addiu	$5,$5,%lo(filter_table_read_proc)
	addiu	$25,$25,%lo(single_open)
	jr	$25
	nop

	.set	macro
	.set	reorder
	.end	filter_table_single_open
	.size	filter_table_single_open, .-filter_table_single_open
	.align	2
	.set	nomips16
	.ent	rtl_schedule_filter_fastpath
	.type	rtl_schedule_filter_fastpath, @function
rtl_schedule_filter_fastpath:
	.frame	$sp,32,$31		# vars= 8, regs= 2/0, args= 16, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$16,24($sp)
	lui	$2,%hi(do_gettimeofday)
	addiu	$4,$sp,16
	addiu	$2,$2,%lo(do_gettimeofday)
	jalr	$2
	move	$16,$5

	lw	$2,16($sp)
	li	$3,-1037172736			# 0xffffffffc22e0000
	addiu	$3,$3,17671
	li	$6,-1840709632			# 0xffffffff92490000
	mult	$2,$3
	sra	$4,$2,31
	addiu	$6,$6,9363
	lw	$5,8($16)
	mfhi	$3
	addu	$3,$3,$2
	sra	$3,$3,16
	subu	$3,$3,$4
	addiu	$3,$3,4
	mult	$3,$6
	sra	$7,$3,31
	mfhi	$6
	addu	$6,$6,$3
	sra	$6,$6,2
	subu	$6,$6,$7
	sll	$7,$6,3
	subu	$6,$7,$6
	subu	$3,$3,$6
	li	$6,1			# 0x1
	sll	$3,$6,$3
	ori	$3,$3,0x80
	and	$5,$3,$5
	beq	$5,$0,$L17
	li	$3,-1851654144			# 0xffffffff91a20000

	li	$5,-2004353024			# 0xffffffff88880000
	ori	$3,$3,0xb3c5
	lw	$6,0($16)
	mult	$2,$3
	ori	$5,$5,0x8889
	mfhi	$3
	mult	$2,$5
	addu	$3,$3,$2
	sra	$3,$3,11
	subu	$3,$3,$4
	mfhi	$7
	addu	$2,$7,$2
	li	$7,715784192			# 0x2aaa0000
	ori	$7,$7,0xaaab
	mult	$3,$7
	sra	$2,$2,5
	subu	$2,$2,$4
	sra	$4,$3,31
	sra	$8,$2,31
	mfhi	$7
	mult	$2,$5
	sra	$7,$7,2
	subu	$4,$7,$4
	sll	$9,$4,3
	sll	$4,$4,5
	mfhi	$5
	subu	$4,$4,$9
	addu	$5,$5,$2
	subu	$3,$3,$4
	sra	$5,$5,5
	subu	$5,$5,$8
	sll	$7,$3,2
	sll	$4,$5,2
	sll	$5,$5,6
	subu	$5,$5,$4
	sll	$3,$3,6
	subu	$2,$2,$5
	subu	$3,$3,$7
	bne	$6,$0,$L13
	addu	$2,$3,$2

	lw	$3,4($16)
	bne	$3,$0,$L14
	nop

	j	$L12
	li	$2,1			# 0x1

$L13:
	sltu	$6,$2,$6
	bne	$6,$0,$L17
	nop

	lw	$3,4($16)
$L14:
	sltu	$2,$3,$2
	j	$L12
	xori	$2,$2,0x1

$L17:
	move	$2,$0
$L12:
	lw	$31,28($sp)
	lw	$16,24($sp)
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
	.end	rtl_schedule_filter_fastpath
	.size	rtl_schedule_filter_fastpath, .-rtl_schedule_filter_fastpath
	.align	2
	.set	nomips16
	.ent	rtl_ip_range_filter_fastpath
	.type	rtl_ip_range_filter_fastpath, @function
rtl_ip_range_filter_fastpath:
	.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	sw	$16,16($sp)
	lui	$2,%hi(rtl_ip_hdr)
	addiu	$2,$2,%lo(rtl_ip_hdr)
	jalr	$2
	move	$16,$5

	lw	$2,12($2)
	lw	$3,0($16)
	sltu	$3,$2,$3
	bne	$3,$0,$L22
	nop

	lw	$3,4($16)
	sltu	$2,$3,$2
	j	$L21
	xori	$2,$2,0x1

$L22:
	move	$2,$0
$L21:
	lw	$31,20($sp)
	lw	$16,16($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	rtl_ip_range_filter_fastpath
	.size	rtl_ip_range_filter_fastpath, .-rtl_ip_range_filter_fastpath
	.align	2
	.set	nomips16
	.ent	dos_timer_fn
	.type	dos_timer_fn, @function
dos_timer_fn:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	lui	$13,%hi(item)
	lw	$12,%lo(item)($13)
	bne	$12,$0,$L54
	lui	$14,%hi(block)

	j	$L24
	lui	$3,%hi(jiffies)

$L54:
	li	$2,1			# 0x1
	lw	$3,%lo(block)($14)
	bne	$3,$2,$L25
	lui	$24,%hi(block_count)

	lw	$2,%lo(block_count)($24)
	addiu	$2,$2,1
	sw	$2,%lo(block_count)($24)
$L25:
	andi	$2,$12,0x1e
	bne	$2,$0,$L56
	move	$7,$0

	lui	$2,%hi(dos_pkt)
	lui	$15,%hi(dos_pkt+40960)
	addiu	$2,$2,%lo(dos_pkt)
	addiu	$15,$15,%lo(dos_pkt+40960)
	j	$L26
	lui	$3,%hi(LogFlag)

$L56:
	lui	$2,%hi(dos_pkt)
	li	$15,40960			# 0xa000
	addiu	$2,$2,%lo(dos_pkt)
	addu	$15,$2,$15
	move	$8,$0
	move	$6,$15
	li	$5,1			# 0x1
	move	$3,$2
	andi	$10,$12,0x2
	andi	$9,$12,0x4
$L31:
	lb	$4,0($3)
	bne	$4,$5,$L27
	nop

	beq	$10,$0,$L28
	nop

	lw	$4,4($3)
	addu	$11,$8,$4
	slt	$4,$0,$4
	j	$L28
	movn	$8,$11,$4

$L42:
	lw	$4,8($3)
	addu	$11,$7,$4
	slt	$4,$0,$4
	movn	$7,$11,$4
$L27:
	addiu	$3,$3,40
$L62:
	bne	$3,$6,$L31
	nop

	lui	$3,%hi(whole_syn_threshold)
	lw	$3,%lo(whole_syn_threshold)($3)
	slt	$8,$3,$8
	beq	$8,$0,$L61
	andi	$12,$12,0x2

	beq	$12,$0,$L61
	nop

	bgtz	$3,$L59
	nop

$L61:
	j	$L32
	lui	$3,%hi(LogFlag)

$L59:
	lui	$3,%hi(LogFlag)
	lw	$4,%lo(LogFlag)($3)
	ori	$4,$4,0x2
	sw	$4,%lo(LogFlag)($3)
$L32:
	lui	$4,%hi(whole_fin_threshold)
	lw	$4,%lo(whole_fin_threshold)($4)
	slt	$7,$4,$7
	beq	$7,$0,$L26
	nop

	lw	$5,%lo(item)($13)
	andi	$5,$5,0x4
	beq	$5,$0,$L26
	nop

	blez	$4,$L26
	nop

	lw	$4,%lo(LogFlag)($3)
	ori	$4,$4,0x4
	sw	$4,%lo(LogFlag)($3)
$L26:
	sw	$0,%lo(LogFlag)($3)
	move	$3,$15
$L35:
	sb	$0,0($2)
	sw	$0,28($2)
	sw	$0,4($2)
	sw	$0,8($2)
	sw	$0,12($2)
	sw	$0,16($2)
	sw	$0,24($2)
	addiu	$2,$2,40
	bne	$2,$3,$L35
	nop

	lui	$2,%hi(block_time)
	lw	$3,%lo(block_count)($24)
	lw	$2,%lo(block_time)($2)
	slt	$2,$3,$2
	bne	$2,$0,$L36
	lui	$3,%hi(block_count)

	lui	$7,%hi(attack_saddr)
	lui	$6,%hi(attack_daddr)
	addiu	$7,$7,%lo(attack_saddr)
	sw	$0,%lo(block)($14)
	addiu	$6,$6,%lo(attack_daddr)
	sw	$0,%lo(block_count)($3)
	li	$5,108			# 0x6c
$L37:
	addu	$4,$7,$2
	addu	$3,$6,$2
	addiu	$2,$2,4
	sw	$0,0($4)
	bne	$2,$5,$L37
	sw	$0,0($3)

$L36:
	lui	$2,%hi(icmp_echo_request_time)
	lui	$3,%hi(jiffies)
	lw	$2,%lo(icmp_echo_request_time)($2)
	lw	$4,%lo(jiffies)($3)
	addiu	$2,$2,100
	subu	$2,$2,$4
	bgez	$2,$L63
	lui	$2,%hi(none_dos_drop_pkt_cnt)

	lui	$2,%hi(icmp_echo_request)
	sw	$0,%lo(icmp_echo_request)($2)
$L24:
	lui	$2,%hi(none_dos_drop_pkt_cnt)
$L63:
	lw	$4,%lo(none_dos_drop_pkt_cnt)($2)
	sltu	$5,$4,3001
	bne	$5,$0,$L38
	lui	$5,%hi(item_backup)

	lw	$4,%lo(item)($13)
	beq	$4,$0,$L44
	nop

	sw	$4,%lo(item_backup)($5)
	lui	$4,%hi(item)
	j	$L44
	sw	$0,%lo(item)($4)

$L38:
	lw	$6,%lo(item_backup)($5)
	beq	$6,$0,$L40
	nop

	sw	$6,%lo(item)($13)
	sw	$0,%lo(item_backup)($5)
$L40:
	beq	$4,$0,$L41
	nop

$L44:
	sw	$0,%lo(none_dos_drop_pkt_cnt)($2)
$L41:
	lw	$5,%lo(jiffies)($3)
	lui	$4,%hi(dos_timer)
	lui	$25,%hi(mod_timer)
	addiu	$4,$4,%lo(dos_timer)
	addiu	$5,$5,100
	addiu	$25,$25,%lo(mod_timer)
	jr	$25
	nop

$L28:
	bne	$9,$0,$L42
	nop

	j	$L62
	addiu	$3,$3,40

	.set	macro
	.set	reorder
	.end	dos_timer_fn
	.size	dos_timer_fn, .-dos_timer_fn
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
$LC0:
	.ascii	"br-lan\000"
	.text
	.align	2
	.set	nomips16
	.ent	GenerateTCPENDACK
	.type	GenerateTCPENDACK, @function
GenerateTCPENDACK:
	.frame	$sp,112,$31		# vars= 56, regs= 10/0, args= 16, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-112
	sw	$31,108($sp)
	sw	$fp,104($sp)
	sw	$23,100($sp)
	sw	$22,96($sp)
	sw	$21,92($sp)
	sw	$20,88($sp)
	sw	$19,84($sp)
	sw	$18,80($sp)
	sw	$17,76($sp)
	sw	$16,72($sp)
	lui	$2,%hi(rtl_get_dev_by_name)
	move	$20,$4
	lui	$4,%hi($LC0)
	addiu	$4,$4,%lo($LC0)
	addiu	$2,$2,%lo(rtl_get_dev_by_name)
	.set	noreorder
	.set	nomacro
	jalr	$2
	lui	$19,%hi(rtl_ip_hdr)
	.set	macro
	.set	reorder

	addiu	$19,$19,%lo(rtl_ip_hdr)
	move	$4,$20
	.set	noreorder
	.set	nomacro
	jalr	$19
	move	$16,$2
	.set	macro
	.set	reorder

	lbu	$18,0($2)
	move	$17,$2
	lui	$2,%hi(endStateClientPort)
	andi	$18,$18,0xf
	lhu	$2,%lo(endStateClientPort)($2)
	sll	$18,$18,2
	addu	$18,$17,$18
	lhu	$3,0($18)
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L65
	lui	$2,%hi(endStateClientSeq)
	.set	macro
	.set	reorder

	lw	$3,4($18)
	lw	$2,%lo(endStateClientSeq)($2)
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L65
	lui	$2,%hi(rtl_neigh_lookup)
	.set	macro
	.set	reorder

	addiu	$4,$17,12
	addiu	$2,$2,%lo(rtl_neigh_lookup)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$5,$16
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L65
	move	$21,$2
	.set	macro
	.set	reorder

	lui	$16,%hi(rtl_get_hh_from_neigh)
	addiu	$16,$16,%lo(rtl_get_hh_from_neigh)
	.set	noreorder
	.set	nomacro
	jalr	$16
	move	$4,$2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L89
	lui	$2,%hi(skb_copy_expand)
	.set	macro
	.set	reorder

	move	$4,$20
	li	$5,128			# 0x80
	move	$6,$0
	addiu	$2,$2,%lo(skb_copy_expand)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$7,32			# 0x20
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L68
	move	$22,$2
	.set	macro
	.set	reorder

$L89:
 #APP
 # 176 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/atomic.h" 1
			

 # 0 "" 2
 #NO_APP
	lui	$2,%hi(arch_local_irq_save)
	addiu	$2,$2,%lo(arch_local_irq_save)
	jalr	$2
	lw	$16,20($21)
	move	$4,$2
	lui	$2,%hi(arch_local_irq_restore)
	addiu	$16,$16,-1
	addiu	$2,$2,%lo(arch_local_irq_restore)
	.set	noreorder
	.set	nomacro
	jalr	$2
	sw	$16,20($21)
	.set	macro
	.set	reorder

 #APP
 # 215 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/atomic.h" 1
			

 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	bne	$16,$0,$L65
	lui	$2,%hi(neigh_destroy)
	.set	macro
	.set	reorder

	addiu	$2,$2,%lo(neigh_destroy)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$21
	.set	macro
	.set	reorder

	j	$L65
$L68:
	move	$4,$2
	.set	noreorder
	.set	nomacro
	jalr	$19
	lui	$fp,%hi(rtl_get_skb_data)
	.set	macro
	.set	reorder

	move	$4,$22
	lbu	$5,0($2)
	lui	$2,%hi(skb_trim)
	addiu	$2,$2,%lo(skb_trim)
	lui	$23,%hi(memcpy)
	andi	$5,$5,0xf
	addiu	$fp,$fp,%lo(rtl_get_skb_data)
	addiu	$5,$5,5
	addiu	$23,$23,%lo(memcpy)
	.set	noreorder
	.set	nomacro
	jalr	$2
	sll	$5,$5,2
	.set	macro
	.set	reorder

	lui	$2,%hi(skb_put)
	move	$4,$22
	addiu	$2,$2,%lo(skb_put)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$5,$0
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jalr	$16
	move	$4,$21
	.set	macro
	.set	reorder

	move	$19,$2
$L84:
	lw	$2,4($19)
	sw	$2,64($sp)
	andi	$2,$2,0x1
	bne	$2,$0,$L84
	.set	noreorder
	.set	nomacro
	jalr	$fp
	move	$4,$22
	.set	macro
	.set	reorder

	lui	$3,%hi(rtl_get_data_from_hh)
	move	$4,$19
	addiu	$3,$3,%lo(rtl_get_data_from_hh)
	.set	noreorder
	.set	nomacro
	jalr	$3
	move	$16,$2
	.set	macro
	.set	reorder

	move	$5,$2
	addiu	$4,$16,-16
	.set	noreorder
	.set	nomacro
	jalr	$23
	li	$6,16			# 0x10
	.set	macro
	.set	reorder

	lw	$2,4($19)
	lw	$5,64($sp)
	.set	noreorder
	.set	nomacro
	bne	$5,$2,$L84
	lui	$2,%hi(rtl_get_len_from_hh)
	.set	macro
	.set	reorder

	addiu	$2,$2,%lo(rtl_get_len_from_hh)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$19
	.set	macro
	.set	reorder

	move	$5,$2
	lui	$2,%hi(skb_push)
	addiu	$2,$2,%lo(skb_push)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$22
	.set	macro
	.set	reorder

 #APP
 # 176 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/atomic.h" 1
			

 # 0 "" 2
 #NO_APP
	lui	$2,%hi(arch_local_irq_save)
	addiu	$2,$2,%lo(arch_local_irq_save)
	jalr	$2
	lw	$16,20($21)
	move	$4,$2
	lui	$2,%hi(arch_local_irq_restore)
	addiu	$16,$16,-1
	addiu	$2,$2,%lo(arch_local_irq_restore)
	.set	noreorder
	.set	nomacro
	jalr	$2
	sw	$16,20($21)
	.set	macro
	.set	reorder

 #APP
 # 215 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/atomic.h" 1
			

 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	bne	$16,$0,$L91
	lui	$2,%hi(rtl_set_skb_nfct)
	.set	macro
	.set	reorder

	lui	$2,%hi(neigh_destroy)
	addiu	$2,$2,%lo(neigh_destroy)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$21
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_set_skb_nfct)
$L91:
	move	$4,$22
	addiu	$2,$2,%lo(rtl_set_skb_nfct)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$5,$0
	.set	macro
	.set	reorder

	li	$2,268369920			# 0xfff0000
	lhu	$4,2($18)
	ori	$2,$2,0xffff
	lw	$3,36($sp)
	li	$7,-327680			# 0xfffffffffffb0000
	sh	$4,24($sp)
	li	$4,1342177280			# 0x50000000
	and	$2,$3,$2
	lhu	$6,0($18)
	or	$2,$2,$4
	lw	$3,4($18)
	lw	$5,8($18)
	ori	$7,$7,0xffff
	sw	$2,36($sp)
	li	$4,1048576			# 0x100000
	sb	$0,37($sp)
	lui	$21,%hi(url_cache)
	lw	$2,36($sp)
	addiu	$19,$21,%lo(url_cache)
	addiu	$3,$3,1
	li	$16,20			# 0x14
	and	$7,$2,$7
	lhu	$2,12($19)
	or	$7,$7,$4
	li	$4,-131072			# 0xfffffffffffe0000
	ori	$4,$4,0xffff
	sw	$3,32($sp)
	and	$7,$7,$4
	sh	$6,26($sp)
	sw	$7,36($sp)
	move	$4,$22
	sh	$2,38($sp)
	lui	$2,%hi(rtl_get_skb_len)
	sw	$5,28($sp)
	addiu	$2,$2,%lo(rtl_get_skb_len)
	.set	noreorder
	.set	nomacro
	jalr	$2
	sh	$0,42($sp)
	.set	macro
	.set	reorder

	li	$3,8			# 0x8
	lw	$4,12($18)
	addiu	$18,$2,-34
	srl	$4,$4,28
	.set	noreorder
	.set	nomacro
	j	$L86
	sll	$4,$4,2
	.set	macro
	.set	reorder

$L78:
	lbu	$5,0($2)
	sltu	$6,$5,2
	.set	noreorder
	.set	nomacro
	beq	$6,$0,$L74
	addiu	$7,$16,2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L86
	addiu	$16,$16,1
	.set	macro
	.set	reorder

$L74:
	lbu	$2,1($2)
	.set	noreorder
	.set	nomacro
	bne	$5,$3,$L86
	addu	$16,$16,$2
	.set	macro
	.set	reorder

	subu	$16,$16,$2
	addiu	$2,$sp,24
	addiu	$4,$sp,20
	addu	$2,$2,$7
	li	$6,4			# 0x4
	move	$5,$2
	sw	$2,64($sp)
	.set	noreorder
	.set	nomacro
	jalr	$23
	addiu	$16,$16,6
	.set	macro
	.set	reorder

	addiu	$3,$sp,24
	addu	$16,$3,$16
	addiu	$4,$sp,16
	move	$5,$16
	.set	noreorder
	.set	nomacro
	jalr	$23
	li	$6,4			# 0x4
	.set	macro
	.set	reorder

	addiu	$5,$sp,16
	lw	$4,64($sp)
	.set	noreorder
	.set	nomacro
	jalr	$23
	li	$6,4			# 0x4
	.set	macro
	.set	reorder

	move	$4,$16
	addiu	$5,$sp,20
	.set	noreorder
	.set	nomacro
	jalr	$23
	li	$6,4			# 0x4
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L90
	sh	$0,40($sp)
	.set	macro
	.set	reorder

$L86:
	addiu	$5,$sp,24
	addu	$2,$5,$16
	sltu	$5,$16,$4
	bne	$5,$0,$L78
	sh	$0,40($sp)
$L90:
	move	$5,$18
	lw	$2,12($17)
	move	$6,$0
	addiu	$4,$sp,24
	andi	$18,$18,0xffff
	sw	$2,64($sp)
	lui	$2,%hi(csum_partial)
	addiu	$2,$2,%lo(csum_partial)
	lw	$16,16($17)
	.set	noreorder
	.set	nomacro
	jalr	$2
	addiu	$18,$18,6
	.set	macro
	.set	reorder

	move	$4,$22
	lw	$3,64($sp)
 #APP
 # 136 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/checksum.h" 1
		.set	push		# csum_tcpudp_nofold
	.set	noat		
	addu	$16, $3		
	sltu	$1, $16, $3	
	addu	$16, $1		
	addu	$16, $18		
	sltu	$1, $16, $18	
	addu	$16, $1		
	addu	$16, $2		
	sltu	$1, $16, $2	
	addu	$16, $1		
	.set	pop
 # 0 "" 2
 # 78 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/checksum.h" 1
		.set	push		# csum_fold
	.set	noat		
	sll	$1, $16, 16	
	addu	$16, $1		
	sltu	$1, $16, $1	
	srl	$16, $16, 16	
	addu	$16, $1		
	xori	$16, 0xffff	
	.set	pop
 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	jalr	$fp
	sh	$16,40($sp)
	.set	macro
	.set	reorder

	addiu	$5,$sp,24
	addiu	$4,$2,34
	.set	noreorder
	.set	nomacro
	jalr	$23
	li	$6,20			# 0x14
	.set	macro
	.set	reorder

	li	$3,268369920			# 0xfff0000
	lw	$2,44($sp)
	ori	$3,$3,0xffff
	li	$4,-251723776			# 0xfffffffff0ff0000
	li	$6,6			# 0x6
	and	$3,$2,$3
	li	$2,1073741824			# 0x40000000
	or	$3,$3,$2
	lbu	$2,14($19)
	ori	$4,$4,0xffff
	move	$5,$0
	and	$3,$3,$4
	li	$4,83886080			# 0x5000000
	or	$3,$3,$4
	sb	$2,52($sp)
	sw	$3,44($sp)
	lui	$2,%hi(rtl_set_skb_ip_summed)
	lw	$3,12($17)
	move	$4,$20
	sb	$6,53($sp)
	addiu	$2,$2,%lo(rtl_set_skb_ip_summed)
	sw	$3,60($sp)
	lw	$3,16($17)
	sh	$0,50($sp)
	sw	$3,56($sp)
	.set	noreorder
	.set	nomacro
	jalr	$2
	sb	$0,45($sp)
	.set	macro
	.set	reorder

	li	$4,40			# 0x28
	lhu	$2,%lo(url_cache)($21)
	addiu	$3,$sp,60
	sh	$4,46($sp)
	addiu	$2,$2,1
	sh	$2,48($sp)
	lw	$7,48($sp)
	lw	$2,44($sp)
	sh	$0,54($sp)
	lw	$4,52($sp)
	srl	$5,$2,22
	addu	$2,$7,$2
	andi	$5,$5,0x3c
	lw	$6,56($sp)
	sltu	$7,$2,$7
	addu	$2,$2,$4
	addu	$7,$2,$7
	addiu	$2,$sp,44
	sltu	$4,$7,$4
	addu	$7,$7,$6
	addu	$4,$7,$4
	addu	$5,$2,$5
	sltu	$2,$4,$6
	addu	$2,$2,$4
$L79:
	lw	$4,0($3)
	addiu	$3,$3,4
	addu	$2,$4,$2
	sltu	$4,$2,$4
	.set	noreorder
	.set	nomacro
	bne	$5,$3,$L79
	addu	$2,$4,$2
	.set	macro
	.set	reorder

	move	$4,$22
 #APP
 # 78 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/checksum.h" 1
		.set	push		# csum_fold
	.set	noat		
	sll	$1, $2, 16	
	addu	$2, $1		
	sltu	$1, $2, $1	
	srl	$2, $2, 16	
	addu	$2, $1		
	xori	$2, 0xffff	
	.set	pop
 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	jalr	$fp
	sh	$2,54($sp)
	.set	macro
	.set	reorder

	addiu	$5,$sp,44
	addiu	$4,$2,14
	.set	noreorder
	.set	nomacro
	jalr	$23
	li	$6,20			# 0x14
	.set	macro
	.set	reorder

	lui	$2,%hi(dev_queue_xmit)
	move	$4,$22
	addiu	$2,$2,%lo(dev_queue_xmit)
	.set	noreorder
	.set	nomacro
	jalr	$2
	sb	$0,16($19)
	.set	macro
	.set	reorder

$L65:
	lw	$31,108($sp)
	move	$2,$0
	lw	$fp,104($sp)
	lw	$23,100($sp)
	lw	$22,96($sp)
	lw	$21,92($sp)
	lw	$20,88($sp)
	lw	$19,84($sp)
	lw	$18,80($sp)
	lw	$17,76($sp)
	lw	$16,72($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,112
	.set	macro
	.set	reorder

	.end	GenerateTCPENDACK
	.size	GenerateTCPENDACK, .-GenerateTCPENDACK
	.align	2
	.set	nomips16
	.ent	GenerateTCPFINACK
	.type	GenerateTCPFINACK, @function
GenerateTCPFINACK:
	.frame	$sp,112,$31		# vars= 56, regs= 10/0, args= 16, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-112
	sw	$31,108($sp)
	sw	$fp,104($sp)
	sw	$23,100($sp)
	sw	$22,96($sp)
	sw	$21,92($sp)
	sw	$20,88($sp)
	sw	$19,84($sp)
	sw	$18,80($sp)
	sw	$17,76($sp)
	sw	$16,72($sp)
	lui	$2,%hi(rtl_get_dev_by_name)
	move	$20,$4
	lui	$4,%hi($LC0)
	addiu	$4,$4,%lo($LC0)
	addiu	$2,$2,%lo(rtl_get_dev_by_name)
	.set	noreorder
	.set	nomacro
	jalr	$2
	lui	$19,%hi(rtl_ip_hdr)
	.set	macro
	.set	reorder

	addiu	$19,$19,%lo(rtl_ip_hdr)
	move	$4,$20
	.set	noreorder
	.set	nomacro
	jalr	$19
	move	$16,$2
	.set	macro
	.set	reorder

	lbu	$18,0($2)
	move	$17,$2
	lui	$2,%hi(finStateClientPort)
	andi	$18,$18,0xf
	lhu	$2,%lo(finStateClientPort)($2)
	sll	$18,$18,2
	addu	$18,$17,$18
	lhu	$3,0($18)
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L93
	lui	$2,%hi(finStateClientSeq)
	.set	macro
	.set	reorder

	lw	$3,4($18)
	lw	$2,%lo(finStateClientSeq)($2)
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L93
	lui	$2,%hi(rtl_neigh_lookup)
	.set	macro
	.set	reorder

	addiu	$4,$17,12
	addiu	$2,$2,%lo(rtl_neigh_lookup)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$5,$16
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L93
	move	$21,$2
	.set	macro
	.set	reorder

	lui	$16,%hi(rtl_get_hh_from_neigh)
	addiu	$16,$16,%lo(rtl_get_hh_from_neigh)
	.set	noreorder
	.set	nomacro
	jalr	$16
	move	$4,$2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L117
	lui	$2,%hi(skb_copy_expand)
	.set	macro
	.set	reorder

	move	$4,$20
	li	$5,128			# 0x80
	move	$6,$0
	addiu	$2,$2,%lo(skb_copy_expand)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$7,32			# 0x20
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L96
	move	$22,$2
	.set	macro
	.set	reorder

$L117:
 #APP
 # 176 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/atomic.h" 1
			

 # 0 "" 2
 #NO_APP
	lui	$2,%hi(arch_local_irq_save)
	addiu	$2,$2,%lo(arch_local_irq_save)
	jalr	$2
	lw	$16,20($21)
	move	$4,$2
	lui	$2,%hi(arch_local_irq_restore)
	addiu	$16,$16,-1
	addiu	$2,$2,%lo(arch_local_irq_restore)
	.set	noreorder
	.set	nomacro
	jalr	$2
	sw	$16,20($21)
	.set	macro
	.set	reorder

 #APP
 # 215 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/atomic.h" 1
			

 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	bne	$16,$0,$L93
	lui	$2,%hi(neigh_destroy)
	.set	macro
	.set	reorder

	addiu	$2,$2,%lo(neigh_destroy)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$21
	.set	macro
	.set	reorder

	j	$L93
$L96:
	move	$4,$2
	.set	noreorder
	.set	nomacro
	jalr	$19
	lui	$fp,%hi(rtl_get_skb_data)
	.set	macro
	.set	reorder

	move	$4,$22
	lbu	$5,0($2)
	lui	$2,%hi(skb_trim)
	addiu	$2,$2,%lo(skb_trim)
	lui	$23,%hi(memcpy)
	andi	$5,$5,0xf
	addiu	$fp,$fp,%lo(rtl_get_skb_data)
	addiu	$5,$5,5
	addiu	$23,$23,%lo(memcpy)
	.set	noreorder
	.set	nomacro
	jalr	$2
	sll	$5,$5,2
	.set	macro
	.set	reorder

	lui	$2,%hi(skb_put)
	move	$4,$22
	addiu	$2,$2,%lo(skb_put)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$5,$0
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jalr	$16
	move	$4,$21
	.set	macro
	.set	reorder

	move	$19,$2
$L112:
	lw	$2,4($19)
	sw	$2,64($sp)
	andi	$2,$2,0x1
	bne	$2,$0,$L112
	.set	noreorder
	.set	nomacro
	jalr	$fp
	move	$4,$22
	.set	macro
	.set	reorder

	lui	$3,%hi(rtl_get_data_from_hh)
	move	$4,$19
	addiu	$3,$3,%lo(rtl_get_data_from_hh)
	.set	noreorder
	.set	nomacro
	jalr	$3
	move	$16,$2
	.set	macro
	.set	reorder

	move	$5,$2
	addiu	$4,$16,-16
	.set	noreorder
	.set	nomacro
	jalr	$23
	li	$6,16			# 0x10
	.set	macro
	.set	reorder

	lw	$2,4($19)
	lw	$5,64($sp)
	.set	noreorder
	.set	nomacro
	bne	$5,$2,$L112
	lui	$2,%hi(rtl_get_len_from_hh)
	.set	macro
	.set	reorder

	addiu	$2,$2,%lo(rtl_get_len_from_hh)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$19
	.set	macro
	.set	reorder

	move	$5,$2
	lui	$2,%hi(skb_push)
	addiu	$2,$2,%lo(skb_push)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$22
	.set	macro
	.set	reorder

 #APP
 # 176 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/atomic.h" 1
			

 # 0 "" 2
 #NO_APP
	lui	$2,%hi(arch_local_irq_save)
	addiu	$2,$2,%lo(arch_local_irq_save)
	jalr	$2
	lw	$16,20($21)
	move	$4,$2
	lui	$2,%hi(arch_local_irq_restore)
	addiu	$16,$16,-1
	addiu	$2,$2,%lo(arch_local_irq_restore)
	.set	noreorder
	.set	nomacro
	jalr	$2
	sw	$16,20($21)
	.set	macro
	.set	reorder

 #APP
 # 215 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/atomic.h" 1
			

 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	bne	$16,$0,$L119
	lui	$2,%hi(rtl_set_skb_nfct)
	.set	macro
	.set	reorder

	lui	$2,%hi(neigh_destroy)
	addiu	$2,$2,%lo(neigh_destroy)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$21
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_set_skb_nfct)
$L119:
	move	$4,$22
	addiu	$2,$2,%lo(rtl_set_skb_nfct)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$5,$0
	.set	macro
	.set	reorder

	li	$2,268369920			# 0xfff0000
	lhu	$4,2($18)
	ori	$2,$2,0xffff
	lw	$3,36($sp)
	lui	$21,%hi(url_cache)
	sh	$4,24($sp)
	li	$4,1342177280			# 0x50000000
	and	$2,$3,$2
	lw	$5,8($18)
	or	$2,$2,$4
	lw	$3,4($18)
	lhu	$4,0($18)
	li	$6,-327680			# 0xfffffffffffb0000
	sw	$2,36($sp)
	addiu	$19,$21,%lo(url_cache)
	sb	$0,37($sp)
	ori	$6,$6,0xffff
	lw	$7,36($sp)
	li	$16,20			# 0x14
	lhu	$2,12($19)
	and	$6,$7,$6
	li	$7,1114112			# 0x110000
	or	$6,$6,$7
	sh	$4,26($sp)
	sw	$6,36($sp)
	move	$4,$22
	sh	$2,38($sp)
	lui	$2,%hi(rtl_get_skb_len)
	sw	$3,32($sp)
	addiu	$2,$2,%lo(rtl_get_skb_len)
	sw	$5,28($sp)
	.set	noreorder
	.set	nomacro
	jalr	$2
	sh	$0,42($sp)
	.set	macro
	.set	reorder

	li	$3,8			# 0x8
	lw	$4,12($18)
	addiu	$18,$2,-34
	srl	$4,$4,28
	.set	noreorder
	.set	nomacro
	j	$L114
	sll	$4,$4,2
	.set	macro
	.set	reorder

$L106:
	lbu	$5,0($2)
	sltu	$6,$5,2
	.set	noreorder
	.set	nomacro
	beq	$6,$0,$L102
	addiu	$7,$16,2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L114
	addiu	$16,$16,1
	.set	macro
	.set	reorder

$L102:
	lbu	$2,1($2)
	.set	noreorder
	.set	nomacro
	bne	$5,$3,$L114
	addu	$16,$16,$2
	.set	macro
	.set	reorder

	subu	$16,$16,$2
	addiu	$2,$sp,24
	addiu	$4,$sp,20
	addu	$2,$2,$7
	li	$6,4			# 0x4
	move	$5,$2
	sw	$2,64($sp)
	.set	noreorder
	.set	nomacro
	jalr	$23
	addiu	$16,$16,6
	.set	macro
	.set	reorder

	addiu	$3,$sp,24
	addu	$16,$3,$16
	addiu	$4,$sp,16
	move	$5,$16
	.set	noreorder
	.set	nomacro
	jalr	$23
	li	$6,4			# 0x4
	.set	macro
	.set	reorder

	addiu	$5,$sp,16
	lw	$4,64($sp)
	.set	noreorder
	.set	nomacro
	jalr	$23
	li	$6,4			# 0x4
	.set	macro
	.set	reorder

	move	$4,$16
	addiu	$5,$sp,20
	.set	noreorder
	.set	nomacro
	jalr	$23
	li	$6,4			# 0x4
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L118
	sh	$0,40($sp)
	.set	macro
	.set	reorder

$L114:
	addiu	$5,$sp,24
	addu	$2,$5,$16
	sltu	$5,$16,$4
	bne	$5,$0,$L106
	sh	$0,40($sp)
$L118:
	move	$5,$18
	lw	$2,12($17)
	move	$6,$0
	lhu	$3,26($sp)
	addiu	$4,$sp,24
	sw	$2,64($sp)
	lui	$2,%hi(endStateClientPort)
	sh	$3,%lo(endStateClientPort)($2)
	lui	$2,%hi(endStateClientSeq)
	lw	$3,32($sp)
	andi	$18,$18,0xffff
	lw	$16,16($17)
	sw	$3,%lo(endStateClientSeq)($2)
	lui	$2,%hi(csum_partial)
	addiu	$2,$2,%lo(csum_partial)
	.set	noreorder
	.set	nomacro
	jalr	$2
	addiu	$18,$18,6
	.set	macro
	.set	reorder

	move	$4,$22
	lw	$3,64($sp)
 #APP
 # 136 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/checksum.h" 1
		.set	push		# csum_tcpudp_nofold
	.set	noat		
	addu	$16, $3		
	sltu	$1, $16, $3	
	addu	$16, $1		
	addu	$16, $18		
	sltu	$1, $16, $18	
	addu	$16, $1		
	addu	$16, $2		
	sltu	$1, $16, $2	
	addu	$16, $1		
	.set	pop
 # 0 "" 2
 # 78 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/checksum.h" 1
		.set	push		# csum_fold
	.set	noat		
	sll	$1, $16, 16	
	addu	$16, $1		
	sltu	$1, $16, $1	
	srl	$16, $16, 16	
	addu	$16, $1		
	xori	$16, 0xffff	
	.set	pop
 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	jalr	$fp
	sh	$16,40($sp)
	.set	macro
	.set	reorder

	addiu	$5,$sp,24
	addiu	$4,$2,34
	.set	noreorder
	.set	nomacro
	jalr	$23
	li	$6,20			# 0x14
	.set	macro
	.set	reorder

	li	$3,268369920			# 0xfff0000
	lw	$2,44($sp)
	ori	$3,$3,0xffff
	li	$4,-251723776			# 0xfffffffff0ff0000
	li	$6,6			# 0x6
	and	$3,$2,$3
	li	$2,1073741824			# 0x40000000
	or	$3,$3,$2
	lbu	$2,14($19)
	ori	$4,$4,0xffff
	move	$5,$0
	and	$3,$3,$4
	li	$4,83886080			# 0x5000000
	or	$3,$3,$4
	sb	$2,52($sp)
	sw	$3,44($sp)
	lui	$2,%hi(rtl_set_skb_ip_summed)
	lw	$3,12($17)
	move	$4,$20
	sb	$6,53($sp)
	addiu	$2,$2,%lo(rtl_set_skb_ip_summed)
	sw	$3,60($sp)
	lw	$3,16($17)
	sh	$0,50($sp)
	sw	$3,56($sp)
	.set	noreorder
	.set	nomacro
	jalr	$2
	sb	$0,45($sp)
	.set	macro
	.set	reorder

	li	$4,40			# 0x28
	lhu	$2,%lo(url_cache)($21)
	addiu	$3,$sp,60
	sh	$4,46($sp)
	addiu	$2,$2,1
	sh	$2,48($sp)
	lw	$7,48($sp)
	lw	$2,44($sp)
	sh	$0,54($sp)
	lw	$4,52($sp)
	srl	$5,$2,22
	addu	$2,$7,$2
	andi	$5,$5,0x3c
	lw	$6,56($sp)
	sltu	$7,$2,$7
	addu	$2,$2,$4
	addu	$7,$2,$7
	addiu	$2,$sp,44
	sltu	$4,$7,$4
	addu	$7,$7,$6
	addu	$4,$7,$4
	addu	$5,$2,$5
	sltu	$2,$4,$6
	addu	$2,$2,$4
$L107:
	lw	$4,0($3)
	addiu	$3,$3,4
	addu	$2,$4,$2
	sltu	$4,$2,$4
	.set	noreorder
	.set	nomacro
	bne	$5,$3,$L107
	addu	$2,$4,$2
	.set	macro
	.set	reorder

	move	$4,$22
 #APP
 # 78 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/checksum.h" 1
		.set	push		# csum_fold
	.set	noat		
	sll	$1, $2, 16	
	addu	$2, $1		
	sltu	$1, $2, $1	
	srl	$2, $2, 16	
	addu	$2, $1		
	xori	$2, 0xffff	
	.set	pop
 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	jalr	$fp
	sh	$2,54($sp)
	.set	macro
	.set	reorder

	addiu	$5,$sp,44
	addiu	$4,$2,14
	.set	noreorder
	.set	nomacro
	jalr	$23
	li	$6,20			# 0x14
	.set	macro
	.set	reorder

	li	$2,1			# 0x1
	sb	$2,16($19)
	lui	$2,%hi(dev_queue_xmit)
	move	$4,$22
	addiu	$2,$2,%lo(dev_queue_xmit)
	.set	noreorder
	.set	nomacro
	jalr	$2
	sb	$0,15($19)
	.set	macro
	.set	reorder

$L93:
	lw	$31,108($sp)
	move	$2,$0
	lw	$fp,104($sp)
	lw	$23,100($sp)
	lw	$22,96($sp)
	lw	$21,92($sp)
	lw	$20,88($sp)
	lw	$19,84($sp)
	lw	$18,80($sp)
	lw	$17,76($sp)
	lw	$16,72($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,112
	.set	macro
	.set	reorder

	.end	GenerateTCPFINACK
	.size	GenerateTCPFINACK, .-GenerateTCPFINACK
	.section	.rodata.str1.4
	.align	2
$LC1:
	.ascii	"HTTP/1.1 401 The web site is blocked by administrator\015"
	.ascii	"\012Server: Embedded HTTP Server 2.00\015\012Connection:"
	.ascii	" close\015\012\015\012<HTML><HEAD><TITLE>401 The web sit"
	.ascii	"e is blocked by administrator</TITLE></HEAD>\012<BODY BG"
	.ascii	"COLOR=\"#ffffff\"><H4>401 The web site is blocked by adm"
	.ascii	"inistrator</H4></BODY></HTML>\012\000"
	.text
	.align	2
	.globl	GenerateHTTP401
	.set	nomips16
	.ent	GenerateHTTP401
	.type	GenerateHTTP401, @function
GenerateHTTP401:
	.frame	$sp,176,$31		# vars= 120, regs= 10/0, args= 16, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-176
	sw	$31,172($sp)
	sw	$fp,168($sp)
	sw	$23,164($sp)
	sw	$22,160($sp)
	sw	$21,156($sp)
	sw	$20,152($sp)
	sw	$19,148($sp)
	sw	$18,144($sp)
	sw	$17,140($sp)
	sw	$16,136($sp)
	lui	$2,%hi(rtl_get_dev_by_name)
	move	$21,$4
	lui	$4,%hi($LC0)
	addiu	$4,$4,%lo($LC0)
	addiu	$2,$2,%lo(rtl_get_dev_by_name)
	.set	noreorder
	.set	nomacro
	jalr	$2
	lui	$18,%hi(rtl_ip_hdr)
	.set	macro
	.set	reorder

	addiu	$18,$18,%lo(rtl_ip_hdr)
	move	$4,$21
	.set	noreorder
	.set	nomacro
	jalr	$18
	move	$16,$2
	.set	macro
	.set	reorder

	addiu	$4,$2,12
	lui	$2,%hi(rtl_neigh_lookup)
	addiu	$2,$2,%lo(rtl_neigh_lookup)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$5,$16
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L121
	move	$17,$2
	.set	macro
	.set	reorder

	lui	$16,%hi(rtl_get_hh_from_neigh)
	addiu	$16,$16,%lo(rtl_get_hh_from_neigh)
	.set	noreorder
	.set	nomacro
	jalr	$16
	move	$4,$2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L153
	lui	$23,%hi(block_message)
	.set	macro
	.set	reorder

	lw	$4,%lo(block_message)($23)
	.set	noreorder
	.set	nomacro
	bne	$4,$0,$L149
	lui	$fp,%hi(strlen)
	.set	macro
	.set	reorder

	lui	$4,%hi($LC1)
	addiu	$4,$4,%lo($LC1)
$L149:
	addiu	$fp,$fp,%lo(strlen)
	jalr	$fp
	move	$4,$21
	move	$6,$2
	lui	$2,%hi(skb_copy_expand)
	li	$5,128			# 0x80
	addiu	$2,$2,%lo(skb_copy_expand)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$7,32			# 0x20
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L126
	move	$20,$2
	.set	macro
	.set	reorder

$L153:
 #APP
 # 176 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/atomic.h" 1
			

 # 0 "" 2
 #NO_APP
	lui	$2,%hi(arch_local_irq_save)
	addiu	$2,$2,%lo(arch_local_irq_save)
	jalr	$2
	lw	$16,20($17)
	move	$4,$2
	lui	$2,%hi(arch_local_irq_restore)
	addiu	$16,$16,-1
	addiu	$2,$2,%lo(arch_local_irq_restore)
	.set	noreorder
	.set	nomacro
	jalr	$2
	sw	$16,20($17)
	.set	macro
	.set	reorder

 #APP
 # 215 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/atomic.h" 1
			

 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	bne	$16,$0,$L121
	lui	$2,%hi(neigh_destroy)
	.set	macro
	.set	reorder

	addiu	$2,$2,%lo(neigh_destroy)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$17
	.set	macro
	.set	reorder

	j	$L121
$L126:
	.set	noreorder
	.set	nomacro
	jalr	$18
	move	$4,$2
	.set	macro
	.set	reorder

	move	$19,$2
	lbu	$2,0($2)
	andi	$2,$2,0xf
	sll	$3,$2,2
	addu	$3,$19,$3
	sw	$3,128($sp)
	lw	$3,12($3)
	srl	$3,$3,28
	addu	$2,$2,$3
	sll	$5,$2,2
	lui	$2,%hi(skb_trim)
	addiu	$2,$2,%lo(skb_trim)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$20
	.set	macro
	.set	reorder

	lw	$4,%lo(block_message)($23)
	bne	$4,$0,$L150
	lui	$4,%hi($LC1)
	addiu	$4,$4,%lo($LC1)
$L150:
	.set	noreorder
	.set	nomacro
	jalr	$fp
	lui	$22,%hi(memcpy)
	.set	macro
	.set	reorder

	move	$5,$2
	lui	$2,%hi(skb_put)
	addiu	$2,$2,%lo(skb_put)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$20
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jalr	$16
	move	$4,$17
	.set	macro
	.set	reorder

	addiu	$22,$22,%lo(memcpy)
	move	$18,$2
$L146:
	lw	$2,4($18)
	sw	$2,132($sp)
	andi	$2,$2,0x1
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L146
	lui	$3,%hi(rtl_get_skb_data)
	.set	macro
	.set	reorder

	addiu	$3,$3,%lo(rtl_get_skb_data)
	.set	noreorder
	.set	nomacro
	jalr	$3
	move	$4,$20
	.set	macro
	.set	reorder

	lui	$5,%hi(rtl_get_data_from_hh)
	move	$4,$18
	addiu	$5,$5,%lo(rtl_get_data_from_hh)
	.set	noreorder
	.set	nomacro
	jalr	$5
	move	$16,$2
	.set	macro
	.set	reorder

	move	$5,$2
	addiu	$4,$16,-16
	.set	noreorder
	.set	nomacro
	jalr	$22
	li	$6,16			# 0x10
	.set	macro
	.set	reorder

	lw	$2,4($18)
	lw	$3,132($sp)
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L146
	lui	$2,%hi(rtl_get_len_from_hh)
	.set	macro
	.set	reorder

	addiu	$2,$2,%lo(rtl_get_len_from_hh)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	move	$5,$2
	lui	$2,%hi(skb_push)
	addiu	$2,$2,%lo(skb_push)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$20
	.set	macro
	.set	reorder

 #APP
 # 176 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/atomic.h" 1
			

 # 0 "" 2
 #NO_APP
	lui	$2,%hi(arch_local_irq_save)
	addiu	$2,$2,%lo(arch_local_irq_save)
	jalr	$2
	lw	$16,20($17)
	move	$4,$2
	lui	$2,%hi(arch_local_irq_restore)
	addiu	$16,$16,-1
	addiu	$2,$2,%lo(arch_local_irq_restore)
	.set	noreorder
	.set	nomacro
	jalr	$2
	sw	$16,20($17)
	.set	macro
	.set	reorder

 #APP
 # 215 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/atomic.h" 1
			

 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	bne	$16,$0,$L155
	lui	$2,%hi(rtl_set_skb_nfct)
	.set	macro
	.set	reorder

	lui	$2,%hi(neigh_destroy)
	addiu	$2,$2,%lo(neigh_destroy)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$17
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_set_skb_nfct)
$L155:
	move	$4,$20
	addiu	$2,$2,%lo(rtl_set_skb_nfct)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$5,$0
	.set	macro
	.set	reorder

	lbu	$18,0($19)
	lw	$3,12($19)
	lw	$2,16($19)
	andi	$18,$18,0xf
	sll	$18,$18,2
	sw	$3,16($19)
	addu	$18,$19,$18
	sw	$2,12($19)
	lw	$16,12($18)
	lhu	$2,0($18)
	lhu	$3,2($18)
	srl	$16,$16,28
	lw	$17,%lo(block_message)($23)
	sll	$16,$16,2
	addu	$16,$18,$16
	sh	$3,0($18)
	.set	noreorder
	.set	nomacro
	beq	$17,$0,$L133
	sh	$2,2($18)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jalr	$fp
	move	$4,$17
	.set	macro
	.set	reorder

	move	$4,$16
	move	$5,$17
	.set	noreorder
	.set	nomacro
	jalr	$22
	addiu	$6,$2,1
	.set	macro
	.set	reorder

	j	$L134
$L133:
	lui	$17,%hi($LC1)
	.set	noreorder
	.set	nomacro
	jalr	$fp
	addiu	$4,$17,%lo($LC1)
	.set	macro
	.set	reorder

	move	$4,$16
	addiu	$5,$17,%lo($LC1)
	.set	noreorder
	.set	nomacro
	jalr	$22
	move	$6,$2
	.set	macro
	.set	reorder

$L134:
	lw	$2,8($18)
	move	$4,$21
	lui	$21,%hi(rtl_get_skb_len)
	lui	$fp,%hi(url_cache)
	lw	$16,4($18)
	addiu	$21,$21,%lo(rtl_get_skb_len)
	sw	$2,4($18)
	.set	noreorder
	.set	nomacro
	jalr	$21
	addiu	$17,$fp,%lo(url_cache)
	.set	macro
	.set	reorder

	lw	$3,128($sp)
	lhu	$5,12($17)
	lw	$4,12($3)
	lbu	$3,0($19)
	srl	$4,$4,28
	sh	$5,14($18)
	andi	$3,$3,0xf
	sb	$0,13($18)
	addu	$4,$4,$3
	li	$3,-327680			# 0xfffffffffffb0000
	lw	$5,12($18)
	sll	$4,$4,2
	subu	$16,$16,$4
	ori	$3,$3,0xffff
	and	$3,$5,$3
	addu	$16,$16,$2
	li	$4,1572864			# 0x180000
	li	$2,-131072			# 0xfffffffffffe0000
	or	$3,$3,$4
	sw	$16,8($18)
	ori	$2,$2,0xffff
	sh	$0,18($18)
	and	$3,$3,$2
	li	$16,20			# 0x14
	sw	$3,12($18)
	.set	noreorder
	.set	nomacro
	jalr	$21
	move	$4,$20
	.set	macro
	.set	reorder

	li	$4,8			# 0x8
	lbu	$23,0($19)
	lw	$5,128($sp)
	andi	$23,$23,0xf
	lw	$3,12($5)
	subu	$23,$0,$23
	sll	$23,$23,2
	srl	$3,$3,28
	addiu	$23,$23,-14
	sll	$3,$3,2
	.set	noreorder
	.set	nomacro
	j	$L148
	addu	$23,$23,$2
	.set	macro
	.set	reorder

$L140:
	lbu	$5,0($2)
	sltu	$6,$5,2
	.set	noreorder
	.set	nomacro
	beq	$6,$0,$L136
	addiu	$7,$16,2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L148
	addiu	$16,$16,1
	.set	macro
	.set	reorder

$L136:
	lbu	$2,1($2)
	.set	noreorder
	.set	nomacro
	bne	$5,$4,$L148
	addu	$16,$16,$2
	.set	macro
	.set	reorder

	subu	$16,$16,$2
	addu	$7,$18,$7
	addiu	$16,$16,6
	move	$5,$7
	addiu	$4,$sp,20
	addu	$16,$18,$16
	li	$6,4			# 0x4
	.set	noreorder
	.set	nomacro
	jalr	$22
	sw	$7,128($sp)
	.set	macro
	.set	reorder

	addiu	$4,$sp,16
	move	$5,$16
	.set	noreorder
	.set	nomacro
	jalr	$22
	li	$6,4			# 0x4
	.set	macro
	.set	reorder

	addiu	$5,$sp,16
	lw	$4,128($sp)
	.set	noreorder
	.set	nomacro
	jalr	$22
	li	$6,4			# 0x4
	.set	macro
	.set	reorder

	move	$4,$16
	addiu	$5,$sp,20
	.set	noreorder
	.set	nomacro
	jalr	$22
	li	$6,4			# 0x4
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L154
	sh	$0,16($18)
	.set	macro
	.set	reorder

$L148:
	sltu	$5,$16,$3
	.set	noreorder
	.set	nomacro
	bne	$5,$0,$L140
	addu	$2,$18,$16
	.set	macro
	.set	reorder

	sh	$0,16($18)
$L154:
	move	$5,$23
	lw	$2,12($19)
	move	$6,$0
	move	$4,$18
	lw	$16,16($19)
	sw	$2,128($sp)
	lui	$2,%hi(csum_partial)
	addiu	$2,$2,%lo(csum_partial)
	.set	noreorder
	.set	nomacro
	jalr	$2
	andi	$23,$23,0xffff
	.set	macro
	.set	reorder

	addiu	$23,$23,6
	lw	$3,128($sp)
	move	$4,$20
 #APP
 # 136 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/checksum.h" 1
		.set	push		# csum_tcpudp_nofold
	.set	noat		
	addu	$16, $3		
	sltu	$1, $16, $3	
	addu	$16, $1		
	addu	$16, $23		
	sltu	$1, $16, $23	
	addu	$16, $1		
	addu	$16, $2		
	sltu	$1, $16, $2	
	addu	$16, $1		
	.set	pop
 # 0 "" 2
 # 78 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/checksum.h" 1
		.set	push		# csum_fold
	.set	noat		
	sll	$1, $16, 16	
	addu	$16, $1		
	sltu	$1, $16, $1	
	srl	$16, $16, 16	
	addu	$16, $1		
	xori	$16, 0xffff	
	.set	pop
 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	jalr	$21
	sh	$16,16($18)
	.set	macro
	.set	reorder

	addiu	$3,$19,16
	lhu	$4,%lo(url_cache)($fp)
	addiu	$2,$2,-14
	lbu	$5,14($17)
	addiu	$4,$4,2
	sh	$4,4($19)
	sh	$2,2($19)
	sh	$0,6($19)
	lw	$2,0($19)
	lw	$7,4($19)
	sb	$5,8($19)
	srl	$5,$2,22
	sh	$0,10($19)
	addu	$2,$7,$2
	lw	$4,8($19)
	sltu	$7,$2,$7
	lw	$6,12($19)
	andi	$5,$5,0x3c
	addu	$2,$2,$4
	addu	$5,$19,$5
	addu	$7,$2,$7
	sltu	$4,$7,$4
	addu	$7,$7,$6
	addu	$4,$7,$4
	sltu	$2,$4,$6
	addu	$2,$2,$4
$L141:
	lw	$4,0($3)
	addiu	$3,$3,4
	addu	$2,$4,$2
	sltu	$4,$2,$4
	.set	noreorder
	.set	nomacro
	bne	$5,$3,$L141
	addu	$2,$4,$2
	.set	macro
	.set	reorder

 #APP
 # 78 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/checksum.h" 1
		.set	push		# csum_fold
	.set	noat		
	sll	$1, $2, 16	
	addu	$2, $1		
	sltu	$1, $2, $1	
	srl	$2, $2, 16	
	addu	$2, $1		
	xori	$2, 0xffff	
	.set	pop
 # 0 "" 2
 #NO_APP
	lui	$5,%hi(rtl_get_skb_data)
	move	$4,$20
	sh	$2,10($19)
	li	$2,1			# 0x1
	addiu	$5,$5,%lo(rtl_get_skb_data)
	.set	noreorder
	.set	nomacro
	jalr	$5
	sb	$2,15($17)
	.set	macro
	.set	reorder

	addiu	$4,$sp,24
	move	$5,$2
	.set	noreorder
	.set	nomacro
	jalr	$22
	li	$6,54			# 0x36
	.set	macro
	.set	reorder

	lui	$2,%hi(finStateClientPort)
	lhu	$5,2($18)
	lw	$3,8($18)
	sh	$5,%lo(finStateClientPort)($2)
	lui	$2,%hi(finStateClientSeq)
	sw	$3,%lo(finStateClientSeq)($2)
	lui	$2,%hi(dev_queue_xmit)
	addiu	$2,$2,%lo(dev_queue_xmit)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$20
	.set	macro
	.set	reorder

$L121:
	lw	$31,172($sp)
	move	$2,$0
	lw	$fp,168($sp)
	lw	$23,164($sp)
	lw	$22,160($sp)
	lw	$21,156($sp)
	lw	$20,152($sp)
	lw	$19,148($sp)
	lw	$18,144($sp)
	lw	$17,140($sp)
	lw	$16,136($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,176
	.set	macro
	.set	reorder

	.end	GenerateHTTP401
	.size	GenerateHTTP401, .-GenerateHTTP401
	.section	.rodata.str1.4
	.align	2
$LC2:
	.ascii	"type=%d num=%d\012\000"
	.align	2
$LC3:
	.ascii	"index=%d\011\000"
	.align	2
$LC4:
	.ascii	"mac=%02x:%02x:%02x:%02x:%02x:%02x\012\000"
	.align	2
$LC5:
	.ascii	"index=%d\011\011\000"
	.align	2
$LC6:
	.ascii	"url=%s\012\000"
	.align	2
$LC7:
	.ascii	"start=%x\011\000"
	.align	2
$LC8:
	.ascii	"end=%x\011\000"
	.align	2
$LC9:
	.ascii	"day=%x\012\000"
	.align	2
$LC10:
	.ascii	"unknow table type\012\000"
	.align	2
$LC11:
	.ascii	"Mode:%d %s\012\000"
	.text
	.align	2
	.set	nomips16
	.ent	filter_table_read_proc
	.type	filter_table_read_proc, @function
filter_table_read_proc:
	.frame	$sp,72,$31		# vars= 0, regs= 10/0, args= 32, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-72
	sw	$31,68($sp)
	sw	$fp,64($sp)
	sw	$23,60($sp)
	sw	$22,56($sp)
	sw	$21,52($sp)
	sw	$20,48($sp)
	sw	$19,44($sp)
	sw	$18,40($sp)
	sw	$17,36($sp)
	sw	$16,32($sp)
	lui	$16,%hi(kmalloc_caches)
	addiu	$16,$16,%lo(kmalloc_caches)
	lui	$17,%hi(kmem_cache_alloc)
	sw	$4,72($sp)
	lw	$4,36($16)
	addiu	$17,$17,%lo(kmem_cache_alloc)
	jalr	$17
	li	$5,208			# 0xd0

	beq	$2,$0,$L157
	move	$18,$2

	lui	$19,%hi(memset)
	move	$4,$2
	move	$5,$0
	addiu	$19,$19,%lo(memset)
	jalr	$19
	li	$6,512			# 0x200

	lw	$4,32($16)
	jalr	$17
	li	$5,208			# 0xd0

	bne	$2,$0,$L158
	move	$17,$2

	lui	$2,%hi(kfree)
	addiu	$2,$2,%lo(kfree)
	jalr	$2
	move	$4,$18

	j	$L157
	nop

$L158:
	move	$4,$2
	move	$5,$0
	li	$6,256			# 0x100
	jalr	$19
	lui	$23,%hi(strcat)

	lui	$2,%hi(table_list_head)
	lui	$19,%hi(sprintf)
	lw	$22,%lo(table_list_head)($2)
	j	$L173
	addiu	$19,$19,%lo(sprintf)

$L171:
	lw	$7,24($22)
	lw	$6,16($22)
	move	$4,$18
	addiu	$5,$2,%lo($LC2)
	jalr	$19
	addiu	$7,$7,-1

	li	$3,3			# 0x3
	lw	$2,16($22)
	beq	$2,$3,$L162
	li	$3,4			# 0x4

	beq	$2,$3,$L163
	li	$3,2			# 0x2

	bne	$2,$3,$L172
	move	$4,$17

	lui	$fp,%hi($LC3)
	addiu	$21,$22,8
	lw	$16,8($22)
	j	$L174
	addiu	$fp,$fp,%lo($LC3)

$L165:
	lw	$6,20($16)
	jalr	$19
	nop

	move	$4,$18
	jalr	$20
	move	$5,$17

	lui	$5,%hi($LC4)
	lbu	$2,30($16)
	move	$4,$17
	lbu	$6,28($16)
	addiu	$5,$5,%lo($LC4)
	lbu	$7,29($16)
	sw	$2,16($sp)
	lbu	$2,31($16)
	sw	$2,20($sp)
	lbu	$2,32($16)
	sw	$2,24($sp)
	lbu	$2,33($16)
	jalr	$19
	sw	$2,28($sp)

	move	$4,$18
	jalr	$20
	move	$5,$17

	lw	$16,0($16)
	move	$4,$17
$L174:
	addiu	$20,$23,%lo(strcat)
	bne	$16,$21,$L165
	move	$5,$fp

	j	$L166
	nop

$L162:
	lw	$20,8($22)
	j	$L167
	addiu	$21,$22,8

$L168:
	lw	$6,20($20)
	jalr	$19
	nop

	move	$4,$18
	jalr	$16
	move	$5,$17

	lui	$5,%hi($LC6)
	addiu	$6,$20,28
	move	$4,$17
	jalr	$19
	addiu	$5,$5,%lo($LC6)

	move	$4,$18
	jalr	$16
	move	$5,$17

	lw	$20,0($20)
$L167:
	lui	$5,%hi($LC5)
	move	$4,$17
	addiu	$16,$23,%lo(strcat)
	bne	$20,$21,$L168
	addiu	$5,$5,%lo($LC5)

	j	$L166
	nop

$L163:
	lui	$fp,%hi($LC3)
	addiu	$21,$22,8
	lw	$20,8($22)
	j	$L169
	addiu	$fp,$fp,%lo($LC3)

$L170:
	lw	$6,20($20)
	jalr	$19
	nop

	move	$4,$18
	jalr	$16
	move	$5,$17

	lui	$5,%hi($LC7)
	lw	$6,28($20)
	move	$4,$17
	jalr	$19
	addiu	$5,$5,%lo($LC7)

	move	$4,$18
	jalr	$16
	move	$5,$17

	lui	$5,%hi($LC8)
	lw	$6,32($20)
	move	$4,$17
	jalr	$19
	addiu	$5,$5,%lo($LC8)

	move	$4,$18
	jalr	$16
	move	$5,$17

	lui	$2,%hi($LC9)
	lw	$6,36($20)
	move	$4,$17
	jalr	$19
	addiu	$5,$2,%lo($LC9)

	move	$4,$18
	jalr	$16
	move	$5,$17

	lw	$20,0($20)
$L169:
	move	$4,$17
	addiu	$16,$23,%lo(strcat)
	bne	$20,$21,$L170
	move	$5,$fp

	j	$L166
	nop

$L172:
	lui	$5,%hi($LC10)
	jalr	$19
	addiu	$5,$5,%lo($LC10)

	move	$4,$18
	addiu	$2,$23,%lo(strcat)
	jalr	$2
	move	$5,$17

$L166:
	lw	$22,0($22)
	lui	$2,%hi(table_list_head)
$L173:
	addiu	$2,$2,%lo(table_list_head)
	bne	$22,$2,$L171
	lui	$2,%hi($LC2)

	lui	$2,%hi(url_filter_mode)
	lui	$5,%hi($LC11)
	lw	$6,%lo(url_filter_mode)($2)
	lui	$2,%hi(seq_printf)
	lw	$4,72($sp)
	addiu	$5,$5,%lo($LC11)
	move	$7,$18
	addiu	$2,$2,%lo(seq_printf)
	jalr	$2
	lui	$16,%hi(kfree)

	addiu	$16,$16,%lo(kfree)
	jalr	$16
	move	$4,$18

	jalr	$16
	move	$4,$17

$L157:
	lw	$31,68($sp)
	move	$2,$0
	lw	$fp,64($sp)
	lw	$23,60($sp)
	lw	$22,56($sp)
	lw	$21,52($sp)
	lw	$20,48($sp)
	lw	$19,44($sp)
	lw	$18,40($sp)
	lw	$17,36($sp)
	lw	$16,32($sp)
	j	$31
	addiu	$sp,$sp,72

	.set	macro
	.set	reorder
	.end	filter_table_read_proc
	.size	filter_table_read_proc, .-filter_table_read_proc
	.align	2
	.globl	rtl_mac_filter_fastpath
	.set	nomips16
	.ent	rtl_mac_filter_fastpath
	.type	rtl_mac_filter_fastpath, @function
rtl_mac_filter_fastpath:
	.frame	$sp,48,$31		# vars= 0, regs= 7/0, args= 16, gp= 0
	.mask	0x803f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-48
	sw	$31,44($sp)
	sw	$21,40($sp)
	sw	$20,36($sp)
	sw	$19,32($sp)
	sw	$18,28($sp)
	sw	$17,24($sp)
	sw	$16,20($sp)
	lui	$20,%hi(rtl_skb_mac_header)
	move	$18,$4
	li	$16,6			# 0x6
	move	$19,$5
	addiu	$20,$20,%lo(rtl_skb_mac_header)
	li	$21,12			# 0xc
$L177:
	addu	$2,$19,$16
	lbu	$17,-6($2)
	jalr	$20
	move	$4,$18

	addu	$2,$2,$16
	lbu	$2,0($2)
	bne	$17,$2,$L178
	addiu	$16,$16,1

	bne	$16,$21,$L177
	li	$2,1			# 0x1

	j	$L176
	nop

$L178:
	move	$2,$0
$L176:
	lw	$31,44($sp)
	lw	$21,40($sp)
	lw	$20,36($sp)
	lw	$19,32($sp)
	lw	$18,28($sp)
	lw	$17,24($sp)
	lw	$16,20($sp)
	j	$31
	addiu	$sp,$sp,48

	.set	macro
	.set	reorder
	.end	rtl_mac_filter_fastpath
	.size	rtl_mac_filter_fastpath, .-rtl_mac_filter_fastpath
	.align	2
	.set	nomips16
	.ent	find_pattern.constprop.8
	.type	find_pattern.constprop.8, @function
find_pattern.constprop.8:
	.frame	$sp,64,$31		# vars= 8, regs= 10/0, args= 16, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-64
	sw	$31,60($sp)
	sw	$fp,56($sp)
	sw	$23,52($sp)
	sw	$22,48($sp)
	sw	$21,44($sp)
	sw	$20,40($sp)
	sw	$19,36($sp)
	sw	$18,32($sp)
	sw	$17,28($sp)
	sw	$16,24($sp)
	move	$20,$0
	lw	$2,84($sp)
	move	$17,$4
	lw	$3,80($sp)
	move	$16,$5
	sw	$0,0($2)
	subu	$2,$5,$7
	move	$19,$7
	sw	$0,0($3)
	move	$23,$6
	move	$21,$0
	move	$18,$4
	li	$22,13			# 0xd
	lui	$fp,%hi(memcmp)
	sw	$2,16($sp)
$L186:
	lb	$2,0($18)
	bne	$2,$22,$L181
	li	$3,10			# 0xa

	andi	$2,$20,0x1
	bne	$2,$0,$L191
	addiu	$20,$20,1

	j	$L198
	slt	$2,$20,4

$L181:
	bne	$2,$3,$L191
	andi	$2,$20,0x1

	beq	$2,$0,$L191
	addiu	$20,$20,1

	slt	$2,$20,4
$L198:
	bne	$2,$0,$L197
	move	$4,$18

	j	$L184
	move	$2,$0

$L191:
	move	$20,$0
	move	$4,$18
$L197:
	addiu	$2,$fp,%lo(memcmp)
	move	$5,$23
	jalr	$2
	move	$6,$19

	beq	$2,$0,$L185
	move	$3,$0

	lw	$3,16($sp)
	addiu	$21,$21,1
	sltu	$2,$3,$21
	beq	$2,$0,$L186
	addiu	$18,$18,1

	j	$L184
	move	$2,$0

$L185:
	lw	$2,80($sp)
	addu	$19,$21,$19
	li	$5,13			# 0xd
	j	$L187
	sw	$19,0($2)

$L188:
	bne	$4,$0,$L193
	addiu	$3,$3,1

$L187:
	addu	$2,$17,$19
	sltu	$4,$16,$19
	lb	$2,0($2)
	bne	$2,$5,$L188
	addiu	$19,$19,1

	lw	$2,84($sp)
	sw	$3,0($2)
	j	$L184
	li	$2,1			# 0x1

$L193:
	move	$2,$0
$L184:
	lw	$31,60($sp)
	lw	$fp,56($sp)
	lw	$23,52($sp)
	lw	$22,48($sp)
	lw	$21,44($sp)
	lw	$20,40($sp)
	lw	$19,36($sp)
	lw	$18,32($sp)
	lw	$17,28($sp)
	lw	$16,24($sp)
	j	$31
	addiu	$sp,$sp,64

	.set	macro
	.set	reorder
	.end	find_pattern.constprop.8
	.size	find_pattern.constprop.8, .-find_pattern.constprop.8
	.section	.rodata.str1.4
	.align	2
$LC12:
	.ascii	"GET \000"
	.align	2
$LC13:
	.ascii	"Host: \000"
	.align	2
$LC14:
	.ascii	"%s\000"
	.text
	.align	2
	.globl	rtl_url_filter_fastpath
	.set	nomips16
	.ent	rtl_url_filter_fastpath
	.type	rtl_url_filter_fastpath, @function
rtl_url_filter_fastpath:
	.frame	$sp,80,$31		# vars= 16, regs= 10/0, args= 24, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-80
	sw	$31,76($sp)
	sw	$fp,72($sp)
	sw	$23,68($sp)
	sw	$22,64($sp)
	sw	$21,60($sp)
	sw	$20,56($sp)
	sw	$19,52($sp)
	sw	$18,48($sp)
	sw	$17,44($sp)
	sw	$16,40($sp)
	lui	$17,%hi(strlen)
	move	$16,$4
	addiu	$17,$17,%lo(strlen)
	move	$4,$5
	.set	noreorder
	.set	nomacro
	jalr	$17
	move	$18,$5
	.set	macro
	.set	reorder

	sltu	$2,$2,2
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L211
	lui	$2,%hi(rtl_ip_hdr)
	.set	macro
	.set	reorder

	addiu	$2,$2,%lo(rtl_ip_hdr)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$16
	.set	macro
	.set	reorder

	lbu	$3,9($2)
	move	$16,$2
	li	$2,6			# 0x6
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L211
	lui	$2,%hi(kmalloc_caches+44)
	.set	macro
	.set	reorder

	lbu	$20,0($16)
	lw	$4,%lo(kmalloc_caches+44)($2)
	lui	$2,%hi(kmem_cache_alloc)
	andi	$20,$20,0xf
	sll	$20,$20,2
	addiu	$2,$2,%lo(kmem_cache_alloc)
	addu	$20,$16,$20
	lw	$21,12($20)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$5,208			# 0xd0
	.set	macro
	.set	reorder

	srl	$21,$21,28
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L211
	move	$19,$2
	.set	macro
	.set	reorder

	sll	$21,$21,2
	lbu	$fp,0($16)
	addu	$20,$20,$21
	lui	$22,%hi(memcmp)
	lui	$21,%hi($LC12)
	move	$4,$20
	addiu	$5,$21,%lo($LC12)
	li	$6,4			# 0x4
	addiu	$22,$22,%lo(memcmp)
	lhu	$23,2($16)
	.set	noreorder
	.set	nomacro
	jalr	$22
	andi	$fp,$fp,0xf
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L205
	sll	$16,$fp,3
	.set	macro
	.set	reorder

	addiu	$2,$sp,32
	subu	$16,$23,$16
	lui	$6,%hi($LC13)
	lui	$23,%hi(find_pattern.constprop.8)
	move	$4,$20
	sw	$2,16($sp)
	addiu	$2,$sp,28
	addiu	$6,$6,%lo($LC13)
	move	$5,$16
	li	$7,6			# 0x6
	addiu	$23,$23,%lo(find_pattern.constprop.8)
	.set	noreorder
	.set	nomacro
	jalr	$23
	sw	$2,20($sp)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L221
	lui	$2,%hi(kfree)
	.set	macro
	.set	reorder

	lw	$2,28($sp)
	lw	$4,32($sp)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L214
	addu	$4,$20,$4
	.set	macro
	.set	reorder

	move	$3,$19
 #APP
 # 55 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
1:	lbu	$1,($4)
	subu	$2,1
	sb	$1,($3)
	beqz	$1,2f
	addiu	$3,1
	bnez	$2,1b
	addiu	$4,1
2:
	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
	lw	$2,28($sp)
	.set	noreorder
	.set	nomacro
	j	$L219
	addu	$2,$19,$2
	.set	macro
	.set	reorder

$L214:
	move	$2,$0
	addu	$2,$19,$2
$L219:
	move	$4,$20
	sb	$0,0($2)
	addiu	$2,$sp,32
	sw	$2,16($sp)
	addiu	$2,$sp,24
	move	$5,$16
	addiu	$6,$21,%lo($LC12)
	li	$7,4			# 0x4
	.set	noreorder
	.set	nomacro
	jalr	$23
	sw	$2,20($sp)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L221
	lui	$2,%hi(kfree)
	.set	macro
	.set	reorder

	lw	$2,24($sp)
	addiu	$2,$2,-9
	.set	noreorder
	.set	nomacro
	bgtz	$2,$L206
	sw	$2,24($sp)
	.set	macro
	.set	reorder

$L205:
	lui	$2,%hi(kfree)
$L221:
	move	$4,$19
	addiu	$2,$2,%lo(kfree)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$16,$0
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L220
	move	$2,$16
	.set	macro
	.set	reorder

$L206:
	lw	$3,28($sp)
	lw	$4,32($sp)
	addu	$3,$19,$3
	addu	$20,$20,$4
 #APP
 # 55 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
1:	lbu	$1,($20)
	subu	$2,1
	sb	$1,($3)
	beqz	$1,2f
	addiu	$3,1
	bnez	$2,1b
	addiu	$20,1
2:
	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
	lw	$2,24($sp)
	move	$4,$19
	lw	$3,28($sp)
	addu	$2,$19,$2
	addu	$3,$2,$3
	.set	noreorder
	.set	nomacro
	jalr	$17
	sb	$0,0($3)
	.set	macro
	.set	reorder

	move	$4,$18
	.set	noreorder
	.set	nomacro
	jalr	$17
	move	$20,$2
	.set	macro
	.set	reorder

	sltu	$20,$20,$2
	.set	noreorder
	.set	nomacro
	bne	$20,$0,$L215
	move	$16,$2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L209
	move	$17,$19
	.set	macro
	.set	reorder

$L210:
	jalr	$22
	beq	$2,$0,$L216
$L209:
	addu	$2,$17,$16
	move	$4,$17
	lb	$2,0($2)
	move	$5,$18
	move	$6,$16
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L210
	addiu	$17,$17,1
	.set	macro
	.set	reorder

$L215:
	.set	noreorder
	.set	nomacro
	j	$L208
	move	$16,$0
	.set	macro
	.set	reorder

$L216:
	li	$16,1			# 0x1
$L208:
	lui	$6,%hi($LC14)
	lui	$4,%hi(log_info)
	lui	$2,%hi(snprintf)
	li	$5,32			# 0x20
	addiu	$6,$6,%lo($LC14)
	move	$7,$19
	addiu	$2,$2,%lo(snprintf)
	.set	noreorder
	.set	nomacro
	jalr	$2
	addiu	$4,$4,%lo(log_info)
	.set	macro
	.set	reorder

	lui	$2,%hi(kfree)
	addiu	$2,$2,%lo(kfree)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$19
	.set	macro
	.set	reorder

	lui	$2,%hi(url_filter_mode)
	lw	$2,%lo(url_filter_mode)($2)
	li	$3,1			# 0x1
	bne	$2,$3,$L200
	.set	noreorder
	.set	nomacro
	bne	$16,$0,$L217
	lui	$3,%hi(url_filter_flag)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L200
	sw	$2,%lo(url_filter_flag)($3)
	.set	macro
	.set	reorder

$L217:
	.set	noreorder
	.set	nomacro
	j	$L200
	li	$16,1			# 0x1
	.set	macro
	.set	reorder

$L211:
	move	$16,$0
$L200:
	move	$2,$16
$L220:
	lw	$31,76($sp)
	lw	$fp,72($sp)
	lw	$23,68($sp)
	lw	$22,64($sp)
	lw	$21,60($sp)
	lw	$20,56($sp)
	lw	$19,52($sp)
	lw	$18,48($sp)
	lw	$17,44($sp)
	lw	$16,40($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,80
	.set	macro
	.set	reorder

	.end	rtl_url_filter_fastpath
	.size	rtl_url_filter_fastpath, .-rtl_url_filter_fastpath
	.section	.rodata.str1.4
	.align	2
$LC15:
	.ascii	"ppp0\000"
	.align	2
$LC16:
	.ascii	"eth1\000"
	.align	2
$LC17:
	.ascii	"wlan0\000"
	.text
	.align	2
	.globl	need_filter
	.set	nomips16
	.ent	need_filter
	.type	need_filter, @function
need_filter:
	.frame	$sp,32,$31		# vars= 0, regs= 4/0, args= 16, gp= 0
	.mask	0x80070000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$18,24($sp)
	sw	$17,20($sp)
	sw	$16,16($sp)
	lui	$2,%hi(rtl_ip_hdr)
	lui	$17,%hi($LC0)
	addiu	$2,$2,%lo(rtl_ip_hdr)
	.set	noreorder
	.set	nomacro
	jalr	$2
	lui	$16,%hi(rtl_get_dev_by_name)
	.set	macro
	.set	reorder

	addiu	$16,$16,%lo(rtl_get_dev_by_name)
	addiu	$4,$17,%lo($LC0)
	.set	noreorder
	.set	nomacro
	jalr	$16
	move	$18,$2
	.set	macro
	.set	reorder

	beq	$2,$0,$L223
	lw	$4,372($2)
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L223
	addiu	$4,$4,12
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L224
	addiu	$17,$17,%lo($LC0)
	.set	macro
	.set	reorder

$L226:
 #APP
 # 80 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
	lbu	$5,($2)
1:	lbu	$1,($3)
	addiu	$2,1
	bne	$1,$5,2f
	addiu	$3,1
	bnez	$5,1b
	lbu	$5,($2)
	move	$5,$1
2:	subu	$5,$1
3:	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
	beq	$5,$0,$L225
	addiu	$4,$4,8
$L224:
	lw	$4,0($4)
	move	$2,$17
	.set	noreorder
	.set	nomacro
	bne	$4,$0,$L226
	addiu	$3,$4,43
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L244
	lui	$17,%hi($LC15)
	.set	macro
	.set	reorder

$L225:
	lw	$3,16($18)
	lw	$2,28($4)
	.set	noreorder
	.set	nomacro
	beq	$3,$2,$L227
	move	$2,$0
	.set	macro
	.set	reorder

$L223:
	lui	$17,%hi($LC15)
$L244:
	.set	noreorder
	.set	nomacro
	jalr	$16
	addiu	$4,$17,%lo($LC15)
	.set	macro
	.set	reorder

	beq	$2,$0,$L228
	lw	$4,372($2)
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L243
	addiu	$4,$4,12
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L229
	addiu	$17,$17,%lo($LC15)
	.set	macro
	.set	reorder

$L231:
 #APP
 # 80 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
	lbu	$5,($2)
1:	lbu	$1,($3)
	addiu	$2,1
	bne	$1,$5,2f
	addiu	$3,1
	bnez	$5,1b
	lbu	$5,($2)
	move	$5,$1
2:	subu	$5,$1
3:	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
	beq	$5,$0,$L230
	addiu	$4,$4,8
$L229:
	lw	$4,0($4)
	move	$2,$17
	.set	noreorder
	.set	nomacro
	bne	$4,$0,$L231
	addiu	$3,$4,43
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L227
	li	$2,1			# 0x1
	.set	macro
	.set	reorder

$L230:
	lw	$3,16($18)
	lw	$2,24($4)
	xor	$2,$3,$2
	.set	noreorder
	.set	nomacro
	j	$L227
	sltu	$2,$0,$2
	.set	macro
	.set	reorder

$L228:
	lui	$17,%hi($LC16)
	.set	noreorder
	.set	nomacro
	jalr	$16
	addiu	$4,$17,%lo($LC16)
	.set	macro
	.set	reorder

	beq	$2,$0,$L232
	lw	$4,372($2)
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L243
	addiu	$4,$4,12
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L233
	addiu	$17,$17,%lo($LC16)
	.set	macro
	.set	reorder

$L235:
 #APP
 # 80 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
	lbu	$5,($2)
1:	lbu	$1,($3)
	addiu	$2,1
	bne	$1,$5,2f
	addiu	$3,1
	bnez	$5,1b
	lbu	$5,($2)
	move	$5,$1
2:	subu	$5,$1
3:	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
	beq	$5,$0,$L237
	addiu	$4,$4,8
$L233:
	lw	$4,0($4)
	move	$2,$17
	.set	noreorder
	.set	nomacro
	bne	$4,$0,$L235
	addiu	$3,$4,43
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L227
	li	$2,1			# 0x1
	.set	macro
	.set	reorder

$L232:
	lui	$17,%hi($LC17)
	.set	noreorder
	.set	nomacro
	jalr	$16
	addiu	$4,$17,%lo($LC17)
	.set	macro
	.set	reorder

	beq	$2,$0,$L243
	lw	$4,372($2)
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L243
	addiu	$4,$4,12
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L236
	addiu	$17,$17,%lo($LC17)
	.set	macro
	.set	reorder

$L238:
 #APP
 # 80 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
	lbu	$5,($2)
1:	lbu	$1,($3)
	addiu	$2,1
	bne	$1,$5,2f
	addiu	$3,1
	bnez	$5,1b
	lbu	$5,($2)
	move	$5,$1
2:	subu	$5,$1
3:	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
	beq	$5,$0,$L237
	addiu	$4,$4,8
$L236:
	lw	$4,0($4)
	move	$2,$17
	.set	noreorder
	.set	nomacro
	bne	$4,$0,$L238
	addiu	$3,$4,43
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L227
	li	$2,1			# 0x1
	.set	macro
	.set	reorder

$L237:
	lw	$3,16($18)
	lw	$2,28($4)
	xor	$2,$3,$2
	.set	noreorder
	.set	nomacro
	j	$L227
	sltu	$2,$0,$2
	.set	macro
	.set	reorder

$L243:
	li	$2,1			# 0x1
$L227:
	lw	$31,28($sp)
	lw	$18,24($sp)
	lw	$17,20($sp)
	lw	$16,16($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,32
	.set	macro
	.set	reorder

	.end	need_filter
	.size	need_filter, .-need_filter
	.align	2
	.globl	str2hexnum
	.set	nomips16
	.ent	str2hexnum
	.type	str2hexnum, @function
str2hexnum:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	j	$L246
	move	$2,$0

$L250:
	bne	$6,$0,$L247
	sltu	$7,$7,6

	addiu	$6,$3,-65
	addiu	$5,$3,-87
	bne	$7,$0,$L247
	sltu	$6,$6,6

	beq	$6,$0,$L251
	nop

	addiu	$5,$3,-55
$L247:
	sll	$2,$2,4
	addiu	$4,$4,1
	addu	$2,$5,$2
$L246:
	lbu	$3,0($4)
	addiu	$5,$3,-48
	addiu	$7,$3,-97
	bne	$3,$0,$L250
	sltu	$6,$5,10

	j	$31
	nop

$L251:
	j	$31
	li	$2,-1			# 0xffffffffffffffff

	.set	macro
	.set	reorder
	.end	str2hexnum
	.size	str2hexnum, .-str2hexnum
	.align	2
	.globl	filter_table_head_init
	.set	nomips16
	.ent	filter_table_head_init
	.type	filter_table_head_init, @function
filter_table_head_init:
	.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	sw	$16,16($sp)
	lui	$16,%hi(table_list_head)
	lui	$2,%hi(memset)
	addiu	$4,$16,%lo(table_list_head)
	move	$5,$0
	addiu	$2,$2,%lo(memset)
	jalr	$2
	li	$6,32			# 0x20

	addiu	$3,$16,%lo(table_list_head)
	lui	$4,%hi(table_list_head+8)
	move	$2,$0
	addiu	$4,$4,%lo(table_list_head+8)
	sw	$3,%lo(table_list_head)($16)
	lw	$31,20($sp)
	lw	$16,16($sp)
	sw	$4,8($3)
	sw	$4,12($3)
	li	$4,1			# 0x1
	sw	$3,4($3)
	sw	$0,16($3)
	sw	$0,20($3)
	sw	$0,28($3)
	sw	$4,24($3)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	filter_table_head_init
	.size	filter_table_head_init, .-filter_table_head_init
	.align	2
	.globl	filter_table_regist
	.set	nomips16
	.ent	filter_table_regist
	.type	filter_table_regist, @function
filter_table_regist:
	.frame	$sp,40,$31		# vars= 0, regs= 5/0, args= 16, gp= 0
	.mask	0x800f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$19,32($sp)
	sw	$18,28($sp)
	sw	$17,24($sp)
	sw	$16,20($sp)
	lui	$17,%hi(table_list_head)
	addiu	$16,$17,%lo(table_list_head)
	move	$18,$4
	lw	$2,24($16)
	bne	$2,$0,$L254
	move	$19,$5

	lui	$2,%hi(filter_table_head_init)
	addiu	$2,$2,%lo(filter_table_head_init)
	jalr	$2
	nop

$L254:
	lui	$2,%hi(kmalloc_caches+20)
	lw	$4,%lo(kmalloc_caches+20)($2)
	lui	$2,%hi(kmem_cache_alloc)
	addiu	$2,$2,%lo(kmem_cache_alloc)
	jalr	$2
	li	$5,208			# 0xd0

	li	$6,1			# 0x1
	move	$3,$2
	addiu	$5,$2,8
	sw	$2,0($3)
	lw	$4,%lo(table_list_head)($17)
	sw	$18,16($2)
	move	$2,$0
	sw	$0,20($3)
	sw	$6,24($3)
	sw	$5,8($3)
	sw	$5,12($3)
	sw	$19,28($3)
	sw	$3,4($4)
	sw	$4,0($3)
	sw	$16,4($3)
	lw	$4,24($16)
	sw	$3,%lo(table_list_head)($17)
	addiu	$3,$4,1
	sw	$3,24($16)
	lw	$31,36($sp)
	lw	$19,32($sp)
	lw	$18,28($sp)
	lw	$17,24($sp)
	lw	$16,20($sp)
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
	.end	filter_table_regist
	.size	filter_table_regist, .-filter_table_regist
	.align	2
	.globl	filter_table_flush
	.set	nomips16
	.ent	filter_table_flush
	.type	filter_table_flush, @function
filter_table_flush:
	.frame	$sp,56,$31		# vars= 0, regs= 10/0, args= 16, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-56
	sw	$31,52($sp)
	sw	$fp,48($sp)
	sw	$23,44($sp)
	sw	$22,40($sp)
	sw	$21,36($sp)
	sw	$20,32($sp)
	sw	$19,28($sp)
	sw	$18,24($sp)
	sw	$17,20($sp)
	sw	$16,16($sp)
	lui	$22,%hi(table_list_head)
	lw	$16,%lo(table_list_head)($22)
	li	$20,1048576			# 0x100000
	addiu	$22,$22,%lo(table_list_head)
	addiu	$20,$20,256
	lw	$23,0($16)
	j	$L256
	li	$fp,2097152			# 0x200000

$L260:
	lw	$2,8($16)
	addiu	$19,$3,%lo(kfree)
	addiu	$18,$16,8
	lw	$17,0($2)
	j	$L257
	addiu	$21,$fp,512

$L258:
	lw	$3,4($2)
	lw	$5,0($2)
	sw	$3,4($5)
	sw	$5,0($3)
	sw	$20,0($2)
	jalr	$19
	sw	$21,4($2)

	move	$2,$17
	lw	$3,24($16)
	addiu	$3,$3,-1
	sw	$3,24($16)
	lw	$17,0($17)
$L257:
	bne	$2,$18,$L258
	move	$4,$2

	lw	$3,16($16)
	li	$2,3			# 0x3
	bne	$3,$2,$L259
	li	$2,1			# 0x1

	lw	$3,24($16)
	bne	$3,$2,$L259
	lui	$3,%hi(Del_Pattern_ACL_For_ContentFilter)

	addiu	$2,$3,%lo(Del_Pattern_ACL_For_ContentFilter)
	jalr	$2
	nop

$L259:
	lw	$2,4($16)
	addiu	$5,$fp,512
	lw	$3,0($16)
	move	$4,$16
	sw	$2,4($3)
	sw	$3,0($2)
	sw	$20,0($16)
	sw	$5,4($16)
	jalr	$19
	move	$16,$23

	lw	$2,24($22)
	addiu	$2,$2,-1
	sw	$2,24($22)
	lw	$23,0($23)
$L256:
	bne	$16,$22,$L260
	lui	$3,%hi(kfree)

	li	$3,1			# 0x1
	lui	$2,%hi(filter_rule_num)
	sw	$3,%lo(filter_rule_num)($2)
	lui	$3,%hi(log_enable)
	lw	$31,52($sp)
	move	$2,$0
	lw	$fp,48($sp)
	lw	$23,44($sp)
	lw	$22,40($sp)
	lw	$21,36($sp)
	lw	$20,32($sp)
	lw	$19,28($sp)
	lw	$18,24($sp)
	lw	$17,20($sp)
	lw	$16,16($sp)
	sw	$0,%lo(log_enable)($3)
	lui	$3,%hi(url_filter_mode)
	sw	$0,%lo(url_filter_mode)($3)
	j	$31
	addiu	$sp,$sp,56

	.set	macro
	.set	reorder
	.end	filter_table_flush
	.size	filter_table_flush, .-filter_table_flush
	.align	2
	.globl	filter_item_regist
	.set	nomips16
	.ent	filter_item_regist
	.type	filter_item_regist, @function
filter_item_regist:
	.frame	$sp,24,$31		# vars= 0, regs= 1/0, args= 16, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	lui	$2,%hi(table_list_head)
	lw	$3,%lo(table_list_head)($2)
	j	$L262
	addiu	$2,$2,%lo(table_list_head)

$L265:
	lw	$6,16($3)
	bne	$6,$4,$L263
	addiu	$6,$3,8

	lw	$2,8($3)
	sw	$5,4($2)
	sw	$2,0($5)
	sw	$6,4($5)
	lw	$2,24($3)
	sw	$5,8($3)
	addiu	$2,$2,1
	sw	$2,24($3)
	li	$3,3			# 0x3
	bne	$4,$3,$L267
	li	$3,2			# 0x2

	bne	$2,$3,$L267
	lui	$2,%hi(Add_Pattern_ACL_For_ContentFilter)

	addiu	$2,$2,%lo(Add_Pattern_ACL_For_ContentFilter)
	jalr	$2
	nop

	j	$L264
	move	$2,$0

$L263:
	lw	$3,0($3)
$L262:
	bne	$3,$2,$L265
	nop

	j	$L264
	li	$2,-1			# 0xffffffffffffffff

$L267:
	move	$2,$0
$L264:
	lw	$31,20($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	filter_item_regist
	.size	filter_item_regist, .-filter_item_regist
	.align	2
	.globl	check_esc_end
	.set	nomips16
	.ent	check_esc_end
	.type	check_esc_end, @function
check_esc_end:
	.frame	$sp,32,$31		# vars= 0, regs= 3/0, args= 16, gp= 0
	.mask	0x80030000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$17,24($sp)
	sw	$16,20($sp)
	lui	$2,%hi(strlen)
	addiu	$2,$2,%lo(strlen)
	sll	$17,$5,24
	jalr	$2
	move	$16,$4

	sra	$17,$17,24
	move	$3,$0
	j	$L269
	addiu	$2,$2,-1

$L271:
	lb	$4,0($4)
	bne	$4,$17,$L270
	addiu	$2,$2,-1

	addiu	$3,$3,1
$L269:
	bgez	$2,$L271
	addu	$4,$16,$2

$L270:
	li	$2,-2147483648			# 0xffffffff80000000
	addiu	$2,$2,1
	and	$2,$3,$2
	bgez	$2,$L272
	li	$3,-2			# 0xfffffffffffffffe

	addiu	$2,$2,-1
	or	$2,$2,$3
	addiu	$2,$2,1
$L272:
	lw	$31,28($sp)
	lw	$17,24($sp)
	lw	$16,20($sp)
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
	.end	check_esc_end
	.size	check_esc_end, .-check_esc_end
	.section	.rodata.str1.4
	.align	2
$LC18:
	.ascii	"init\000"
	.align	2
$LC19:
	.ascii	" \000"
	.align	2
$LC20:
	.ascii	"flush\000"
	.align	2
$LC21:
	.ascii	"enable_log\000"
	.align	2
$LC22:
	.ascii	"white\000"
	.align	2
$LC23:
	.ascii	"black\000"
	.align	2
$LC24:
	.ascii	"add:\000"
	.align	2
$LC25:
	.ascii	"#\000"
	.align	2
$LC26:
	.ascii	";\000"
	.text
	.align	2
	.set	nomips16
	.ent	filter_table_single_write
	.type	filter_table_single_write, @function
filter_table_single_write:
	.frame	$sp,72,$31		# vars= 16, regs= 10/0, args= 16, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-72
	sw	$31,68($sp)
	sw	$fp,64($sp)
	sw	$23,60($sp)
	sw	$22,56($sp)
	sw	$21,52($sp)
	sw	$20,48($sp)
	sw	$19,44($sp)
	sw	$18,40($sp)
	sw	$17,36($sp)
	sw	$16,32($sp)
	lui	$2,%hi(kmalloc_caches)
	addiu	$2,$2,%lo(kmalloc_caches)
	lui	$fp,%hi(kmem_cache_alloc)
	lw	$4,40($2)
	move	$16,$5
	addiu	$fp,$fp,%lo(kmem_cache_alloc)
	li	$5,208			# 0xd0
	.set	noreorder
	.set	nomacro
	jalr	$fp
	move	$17,$6
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L300
	move	$19,$2
	.set	macro
	.set	reorder

	lui	$21,%hi(memset)
	move	$5,$0
	li	$6,1024			# 0x400
	move	$4,$2
	lui	$18,%hi(get_info_from_usr_space)
	addiu	$21,$21,%lo(memset)
	.set	noreorder
	.set	nomacro
	jalr	$21
	lui	$20,%hi(strlen)
	.set	macro
	.set	reorder

	addiu	$20,$20,%lo(strlen)
	addiu	$4,$18,%lo(get_info_from_usr_space)
	.set	noreorder
	.set	nomacro
	jalr	$20
	sw	$19,16($sp)
	.set	macro
	.set	reorder

	addiu	$4,$18,%lo(get_info_from_usr_space)
	move	$5,$0
	.set	noreorder
	.set	nomacro
	jalr	$21
	move	$6,$2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$16,$0,$L275
	or	$3,$16,$17
	.set	macro
	.set	reorder

	addu	$2,$16,$17
	or	$2,$3,$2
	lw	$3,24($28)
	and	$2,$2,$3
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L301
	move	$23,$17
	.set	macro
	.set	reorder

	addiu	$4,$18,%lo(get_info_from_usr_space)
	move	$5,$16
	move	$6,$17
 #APP
 # 709 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/fastpath-0.1/filter_v2.c" 1
	.set	noreorder
	.set	noat
	la	$1, __copy_user
	jalr	$1
	.set	at
	.set	noat
	addu	$1, $5, $6
	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
	j	$L276
$L301:
	move	$6,$17
$L276:
	.set	noreorder
	.set	nomacro
	bne	$6,$0,$L310
	lui	$2,%hi(kfree)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$17,$0,$L277
	addiu	$3,$18,%lo(get_info_from_usr_space)
	.set	macro
	.set	reorder

	move	$2,$19
 #APP
 # 55 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
1:	lbu	$1,($3)
	subu	$17,1
	sb	$1,($2)
	beqz	$1,2f
	addiu	$2,1
	bnez	$17,1b
	addiu	$3,1
2:
	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
$L277:
	addiu	$4,$18,%lo(get_info_from_usr_space)
	.set	noreorder
	.set	nomacro
	jalr	$20
	lui	$17,%hi($LC18)
	.set	macro
	.set	reorder

	addu	$2,$19,$2
	sb	$0,-1($2)
	lw	$16,16($sp)
	.set	noreorder
	.set	nomacro
	jalr	$20
	addiu	$4,$17,%lo($LC18)
	.set	macro
	.set	reorder

	addiu	$5,$17,%lo($LC18)
	move	$4,$16
	lui	$16,%hi(memcmp)
	addiu	$16,$16,%lo(memcmp)
	.set	noreorder
	.set	nomacro
	jalr	$16
	move	$6,$2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L278
	lui	$17,%hi($LC20)
	.set	macro
	.set	reorder

	lui	$3,%hi($LC19)
	addiu	$21,$sp,16
	lui	$17,%hi(strsep)
	move	$4,$21
	sw	$3,24($sp)
	addiu	$17,$17,%lo(strsep)
	.set	noreorder
	.set	nomacro
	jalr	$17
	addiu	$5,$3,%lo($LC19)
	.set	macro
	.set	reorder

	lw	$2,16($sp)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L275
	lui	$22,%hi(str2hexnum)
	.set	macro
	.set	reorder

	lw	$4,24($sp)
	lui	$16,%hi(filter_tlb)
	lui	$18,%hi(filter_table_regist)
	addiu	$22,$22,%lo(str2hexnum)
	addiu	$16,$16,%lo(filter_tlb)
	addiu	$18,$18,%lo(filter_table_regist)
	addiu	$20,$4,%lo($LC19)
	move	$5,$20
$L313:
	.set	noreorder
	.set	nomacro
	jalr	$17
	move	$4,$21
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jalr	$22
	move	$4,$2
	.set	macro
	.set	reorder

	sll	$3,$2,3
	addu	$3,$16,$3
	lw	$5,4($3)
	.set	noreorder
	.set	nomacro
	jalr	$18
	move	$4,$2
	.set	macro
	.set	reorder

	lw	$2,16($sp)
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L313
	move	$5,$20
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L309
	lui	$2,%hi(kfree)
	.set	macro
	.set	reorder

$L278:
	lw	$18,16($sp)
	.set	noreorder
	.set	nomacro
	jalr	$20
	addiu	$4,$17,%lo($LC20)
	.set	macro
	.set	reorder

	addiu	$5,$17,%lo($LC20)
	move	$4,$18
	.set	noreorder
	.set	nomacro
	jalr	$16
	move	$6,$2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L281
	lui	$17,%hi($LC21)
	.set	macro
	.set	reorder

	lui	$2,%hi(filter_table_flush)
	addiu	$2,$2,%lo(filter_table_flush)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$0
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L309
	lui	$2,%hi(kfree)
	.set	macro
	.set	reorder

$L281:
	lw	$18,16($sp)
	.set	noreorder
	.set	nomacro
	jalr	$20
	addiu	$4,$17,%lo($LC21)
	.set	macro
	.set	reorder

	addiu	$5,$17,%lo($LC21)
	move	$4,$18
	.set	noreorder
	.set	nomacro
	jalr	$16
	move	$6,$2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L282
	li	$3,1			# 0x1
	.set	macro
	.set	reorder

	lui	$2,%hi(log_enable)
	.set	noreorder
	.set	nomacro
	j	$L280
	sw	$3,%lo(log_enable)($2)
	.set	macro
	.set	reorder

$L282:
	lui	$17,%hi($LC22)
	lw	$18,16($sp)
	.set	noreorder
	.set	nomacro
	jalr	$20
	addiu	$4,$17,%lo($LC22)
	.set	macro
	.set	reorder

	addiu	$5,$17,%lo($LC22)
	move	$4,$18
	.set	noreorder
	.set	nomacro
	jalr	$16
	move	$6,$2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L283
	li	$3,1			# 0x1
	.set	macro
	.set	reorder

	lui	$2,%hi(url_filter_mode)
	.set	noreorder
	.set	nomacro
	j	$L280
	sw	$3,%lo(url_filter_mode)($2)
	.set	macro
	.set	reorder

$L283:
	lui	$17,%hi($LC23)
	lw	$18,16($sp)
	.set	noreorder
	.set	nomacro
	jalr	$20
	addiu	$4,$17,%lo($LC23)
	.set	macro
	.set	reorder

	addiu	$5,$17,%lo($LC23)
	move	$4,$18
	.set	noreorder
	.set	nomacro
	jalr	$16
	move	$6,$2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L284
	lui	$2,%hi(url_filter_mode)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L280
	sw	$0,%lo(url_filter_mode)($2)
	.set	macro
	.set	reorder

$L284:
	lui	$17,%hi($LC24)
	lw	$18,16($sp)
	.set	noreorder
	.set	nomacro
	jalr	$20
	addiu	$4,$17,%lo($LC24)
	.set	macro
	.set	reorder

	addiu	$5,$17,%lo($LC24)
	move	$4,$18
	.set	noreorder
	.set	nomacro
	jalr	$16
	move	$6,$2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L309
	lui	$2,%hi(kfree)
	.set	macro
	.set	reorder

	lw	$16,16($sp)
	.set	noreorder
	.set	nomacro
	jalr	$20
	addiu	$4,$17,%lo($LC24)
	.set	macro
	.set	reorder

	addu	$2,$16,$2
	sw	$2,16($sp)
	lb	$2,0($2)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L275
	addiu	$21,$sp,16
	.set	macro
	.set	reorder

	lui	$17,%hi(strsep)
	lui	$5,%hi($LC25)
	move	$4,$21
	addiu	$17,$17,%lo(strsep)
	.set	noreorder
	.set	nomacro
	jalr	$17
	addiu	$5,$5,%lo($LC25)
	.set	macro
	.set	reorder

	lw	$3,16($sp)
	.set	noreorder
	.set	nomacro
	beq	$3,$0,$L275
	lui	$22,%hi(str2hexnum)
	.set	macro
	.set	reorder

	addiu	$22,$22,%lo(str2hexnum)
	.set	noreorder
	.set	nomacro
	jalr	$22
	move	$4,$2
	.set	macro
	.set	reorder

	li	$3,-1			# 0xffffffffffffffff
	.set	noreorder
	.set	nomacro
	beq	$2,$3,$L275
	move	$4,$21
	.set	macro
	.set	reorder

	lui	$2,%hi($LC19)
	sw	$2,24($sp)
	.set	noreorder
	.set	nomacro
	jalr	$17
	addiu	$5,$2,%lo($LC19)
	.set	macro
	.set	reorder

	lw	$3,16($sp)
	.set	noreorder
	.set	nomacro
	beq	$3,$0,$L275
	move	$4,$2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jalr	$22
	li	$16,-1			# 0xffffffffffffffff
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$16,$L275
	move	$4,$21
	.set	macro
	.set	reorder

	lw	$3,24($sp)
	.set	noreorder
	.set	nomacro
	jalr	$17
	addiu	$5,$3,%lo($LC19)
	.set	macro
	.set	reorder

	lw	$3,16($sp)
	beq	$3,$0,$L275
	.set	noreorder
	.set	nomacro
	jalr	$22
	move	$4,$2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$16,$L275
	sw	$2,28($sp)
	.set	macro
	.set	reorder

	lui	$18,%hi(check_esc_end)
	addiu	$18,$18,%lo(check_esc_end)
	lui	$5,%hi($LC26)
$L315:
	move	$4,$21
	.set	noreorder
	.set	nomacro
	jalr	$17
	addiu	$5,$5,%lo($LC26)
	.set	macro
	.set	reorder

	move	$4,$2
	.set	noreorder
	.set	nomacro
	j	$L285
	sw	$2,20($sp)
	.set	macro
	.set	reorder

$L287:
	lw	$16,20($sp)
	.set	noreorder
	.set	nomacro
	jalr	$20
	move	$4,$16
	.set	macro
	.set	reorder

	li	$3,59			# 0x3b
	addu	$2,$16,$2
	lui	$5,%hi($LC26)
	move	$4,$21
	addiu	$5,$5,%lo($LC26)
	.set	noreorder
	.set	nomacro
	jalr	$17
	sb	$3,0($2)
	.set	macro
	.set	reorder

	lw	$2,16($sp)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L314
	lui	$5,%hi($LC19)
	.set	macro
	.set	reorder

	lw	$4,20($sp)
$L285:
	.set	noreorder
	.set	nomacro
	jalr	$18
	li	$5,92			# 0x5c
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L287
	lui	$5,%hi($LC19)
	.set	macro
	.set	reorder

$L314:
	addiu	$4,$sp,20
	.set	noreorder
	.set	nomacro
	jalr	$17
	addiu	$5,$5,%lo($LC19)
	.set	macro
	.set	reorder

	move	$16,$2
	lw	$2,20($sp)
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L305
	li	$22,32			# 0x20
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L310
	lui	$2,%hi(kfree)
	.set	macro
	.set	reorder

$L289:
	jalr	$20
	lui	$5,%hi($LC19)
	addu	$2,$16,$2
	addiu	$4,$sp,20
	addiu	$5,$5,%lo($LC19)
	.set	noreorder
	.set	nomacro
	jalr	$17
	sb	$22,0($2)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L311
	move	$4,$16
	.set	macro
	.set	reorder

$L305:
	move	$4,$16
$L311:
	.set	noreorder
	.set	nomacro
	jalr	$18
	li	$5,92			# 0x5c
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L289
	move	$4,$16
	.set	macro
	.set	reorder

	move	$5,$16
	move	$6,$0
	.set	noreorder
	.set	nomacro
	j	$L290
	li	$7,92			# 0x5c
	.set	macro
	.set	reorder

$L294:
	.set	noreorder
	.set	nomacro
	bne	$2,$7,$L292
	move	$2,$5
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L308
	move	$4,$6
	.set	macro
	.set	reorder

$L293:
	sb	$3,0($2)
	addiu	$4,$4,1
	addiu	$2,$2,1
$L308:
	lb	$3,1($2)
	bne	$3,$0,$L293
	addu	$4,$16,$4
	sb	$0,0($4)
$L292:
	addiu	$6,$6,1
	addiu	$5,$5,1
$L290:
	lb	$2,0($5)
	bne	$2,$0,$L294
	lui	$2,%hi(kmalloc_caches)
	addiu	$2,$2,%lo(kmalloc_caches)
	lw	$4,4($2)
	.set	noreorder
	.set	nomacro
	jalr	$fp
	li	$5,208			# 0xd0
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L280
	move	$22,$2
	.set	macro
	.set	reorder

	addiu	$2,$2,8
	lui	$4,%hi(filter_rule_num)
	lw	$3,%lo(filter_rule_num)($4)
	move	$4,$16
	sw	$2,8($22)
	sw	$2,12($22)
	lw	$2,28($sp)
	sw	$22,0($22)
	sw	$22,4($22)
	sw	$0,24($22)
	sw	$3,20($22)
	.set	noreorder
	.set	nomacro
	jalr	$20
	sw	$2,16($22)
	.set	macro
	.set	reorder

	sltu	$2,$2,41
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L296
	addiu	$4,$22,28
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jalr	$20
	move	$4,$16
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L297
	move	$3,$2
	.set	macro
	.set	reorder

	addiu	$4,$22,28
$L299:
 #APP
 # 55 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
1:	lbu	$1,($16)
	subu	$2,1
	sb	$1,($4)
	beqz	$1,2f
	addiu	$4,1
	bnez	$2,1b
	addiu	$16,1
2:
	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
$L297:
	addu	$2,$22,$3
	lui	$3,%hi(filter_item_regist)
	li	$4,3			# 0x3
	sb	$0,28($2)
	addiu	$2,$3,%lo(filter_item_regist)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$5,$22
	.set	macro
	.set	reorder

	lui	$4,%hi(filter_rule_num)
	lw	$3,%lo(filter_rule_num)($4)
	lw	$2,16($sp)
	addiu	$3,$3,1
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L280
	sw	$3,%lo(filter_rule_num)($4)
	.set	macro
	.set	reorder

	lb	$2,0($2)
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L315
	lui	$5,%hi($LC26)
	.set	macro
	.set	reorder

$L280:
	lui	$2,%hi(kfree)
$L309:
	addiu	$2,$2,%lo(kfree)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$19
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L312
	move	$2,$23
	.set	macro
	.set	reorder

$L275:
	lui	$2,%hi(kfree)
$L310:
	move	$4,$19
	addiu	$2,$2,%lo(kfree)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$23,-14			# 0xfffffffffffffff2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L312
	move	$2,$23
	.set	macro
	.set	reorder

$L300:
	li	$23,-14			# 0xfffffffffffffff2
	move	$2,$23
$L312:
	lw	$31,68($sp)
	lw	$fp,64($sp)
	lw	$23,60($sp)
	lw	$22,56($sp)
	lw	$21,52($sp)
	lw	$20,48($sp)
	lw	$19,44($sp)
	lw	$18,40($sp)
	lw	$17,36($sp)
	lw	$16,32($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,72
	.set	macro
	.set	reorder

$L296:
	li	$2,39			# 0x27
	.set	noreorder
	.set	nomacro
	j	$L299
	li	$3,39			# 0x27
	.set	macro
	.set	reorder

	.end	filter_table_single_write
	.size	filter_table_single_write, .-filter_table_single_write
	.align	2
	.globl	scan_table
	.set	nomips16
	.ent	scan_table
	.type	scan_table, @function
scan_table:
	.frame	$sp,56,$31		# vars= 0, regs= 9/0, args= 16, gp= 0
	.mask	0x80ff0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-56
	sw	$31,52($sp)
	sw	$23,48($sp)
	sw	$22,44($sp)
	sw	$21,40($sp)
	sw	$20,36($sp)
	sw	$19,32($sp)
	sw	$18,28($sp)
	sw	$17,24($sp)
	sw	$16,20($sp)
	lui	$22,%hi(url_filter_flag)
	move	$17,$6
	sw	$0,%lo(url_filter_flag)($22)
	move	$18,$4
	move	$20,$5
	beq	$6,$0,$L334
	move	$19,$7

	lw	$2,28($6)
	beq	$2,$0,$L317
	li	$2,-1			# 0xffffffffffffffff

	lw	$2,24($6)
	sltu	$2,$2,2
	bne	$2,$0,$L318
	addiu	$21,$6,8

	lw	$16,8($6)
	bne	$21,$16,$L339
	lui	$23,%hi(scan_table)

	j	$L343
	lui	$2,%hi(url_filter_mode)

$L335:
	move	$16,$2
$L339:
	lw	$2,16($16)
	andi	$3,$2,0x1
	bne	$3,$0,$L344
	andi	$3,$2,0x200

	lw	$3,20($16)
	bne	$20,$3,$L320
	andi	$3,$2,0x200

$L344:
	beq	$3,$0,$L321
	nop

	andi	$2,$2,0x2
	lw	$6,0($19)
	beq	$2,$0,$L320
	nop

	beq	$6,$0,$L334
	move	$4,$18

	lw	$5,20($16)
	addiu	$2,$23,%lo(scan_table)
	jalr	$2
	move	$7,$6

	bne	$2,$0,$L317
	li	$2,1			# 0x1

	j	$L320
	nop

$L321:
	andi	$3,$2,0x100
	bne	$3,$0,$L345
	andi	$3,$2,0x2

	lw	$2,28($17)
	move	$4,$18
	jalr	$2
	addiu	$5,$16,28

	beq	$2,$0,$L320
	nop

	lw	$2,16($16)
	andi	$3,$2,0x2
$L345:
	bne	$3,$0,$L323
	andi	$3,$2,0x1

	beq	$3,$0,$L337
	nop

	andi	$2,$2,0x8
	j	$L317
	sltu	$2,$2,1

$L323:
	lw	$6,0($19)
	beq	$6,$0,$L334
	move	$4,$18

	lw	$5,20($16)
	addiu	$2,$23,%lo(scan_table)
	jalr	$2
	move	$7,$6

	beq	$2,$0,$L320
	nop

	lw	$2,16($16)
	andi	$3,$2,0x1
	beq	$3,$0,$L324
	lui	$3,%hi(url_filter_mode)

	lw	$3,%lo(url_filter_mode)($3)
	beq	$3,$0,$L342
	andi	$2,$2,0x8

	j	$L317
	sltu	$2,$0,$2

$L324:
	lui	$2,%hi(url_filter_mode)
	lw	$2,%lo(url_filter_mode)($2)
$L342:
	j	$L317
	sltu	$2,$2,1

$L320:
	lw	$2,0($16)
	bne	$21,$2,$L335
	nop

$L327 = .
	bne	$16,$0,$L328
	nop

$L318:
	lui	$2,%hi(url_filter_mode)
$L343:
	li	$3,-1			# 0xffffffffffffffff
	lw	$4,%lo(url_filter_mode)($2)
	li	$2,1			# 0x1
	j	$L317
	movz	$2,$3,$4

$L328:
	lw	$2,%lo(url_filter_flag)($22)
	bne	$2,$0,$L317
	li	$2,1			# 0x1

	lw	$2,16($16)
	andi	$3,$2,0x1
	beq	$3,$0,$L338
	andi	$2,$2,0x8

	j	$L317
	sltu	$2,$0,$2

$L334:
	j	$L317
	li	$2,-1			# 0xffffffffffffffff

$L337:
	j	$L317
	li	$2,1			# 0x1

$L338:
	move	$2,$0
$L317:
	lw	$31,52($sp)
	lw	$23,48($sp)
	lw	$22,44($sp)
	lw	$21,40($sp)
	lw	$20,36($sp)
	lw	$19,32($sp)
	lw	$18,28($sp)
	lw	$17,24($sp)
	lw	$16,20($sp)
	j	$31
	addiu	$sp,$sp,56

	.set	macro
	.set	reorder
	.end	scan_table
	.size	scan_table, .-scan_table
	.section	.rodata.str1.4
	.align	2
$LC27:
	.ascii	"Unkown Type [Blocked]\012\000"
	.text
	.align	2
	.globl	log_fastFilter
	.set	nomips16
	.ent	log_fastFilter
	.type	log_fastFilter, @function
log_fastFilter:
	.frame	$sp,40,$31		# vars= 8, regs= 3/0, args= 16, gp= 0
	.mask	0x80030000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$17,32($sp)
	sw	$16,28($sp)
	lui	$2,%hi(do_gettimeofday)
	move	$17,$4
	addiu	$2,$2,%lo(do_gettimeofday)
	addiu	$4,$sp,16
	jalr	$2
	move	$16,$5

	lui	$2,%hi(rtl_ip_hdr)
	addiu	$2,$2,%lo(rtl_ip_hdr)
	jalr	$2
	move	$4,$16

	addiu	$17,$17,-1
	lui	$2,%hi(rtl_eth_hdr)
	move	$4,$16
	addiu	$2,$2,%lo(rtl_eth_hdr)
	jalr	$2
	sltu	$17,$17,4

	bne	$17,$0,$L348
	lui	$2,%hi(printk)

	lui	$4,%hi($LC27)
	addiu	$2,$2,%lo(printk)
	jalr	$2
	addiu	$4,$4,%lo($LC27)

$L348:
	lw	$31,36($sp)
	move	$2,$0
	lw	$17,32($sp)
	lw	$16,28($sp)
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
	.end	log_fastFilter
	.size	log_fastFilter, .-log_fastFilter
	.align	2
	.globl	do_filter
	.set	nomips16
	.ent	do_filter
	.type	do_filter, @function
do_filter:
	.frame	$sp,48,$31		# vars= 0, regs= 7/0, args= 16, gp= 0
	.mask	0x803f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-48
	sw	$31,44($sp)
	sw	$21,40($sp)
	sw	$20,36($sp)
	sw	$19,32($sp)
	sw	$18,28($sp)
	sw	$17,24($sp)
	sw	$16,20($sp)
	lui	$18,%hi(table_list_head)
	lw	$16,%lo(table_list_head)($18)
	move	$17,$4
	addiu	$18,$18,%lo(table_list_head)
	lui	$19,%hi(scan_table)
	li	$20,-1			# 0xffffffffffffffff
	j	$L350
	li	$21,1			# 0x1

$L353:
	jalr	$2
	nop

	beq	$2,$20,$L354
	nop

	bne	$2,$21,$L352
	lui	$2,%hi(log_enable)

	lw	$2,%lo(log_enable)($2)
	beq	$2,$0,$L355
	lui	$2,%hi(log_fastFilter)

	lw	$4,16($16)
	addiu	$2,$2,%lo(log_fastFilter)
	jalr	$2
	move	$5,$17

	j	$L351
	li	$2,1			# 0x1

$L352:
	lw	$16,0($16)
$L350:
	move	$6,$16
	move	$5,$0
	move	$7,$16
	addiu	$2,$19,%lo(scan_table)
	bne	$16,$18,$L353
	move	$4,$17

$L354:
	j	$L351
	move	$2,$0

$L355:
	li	$2,1			# 0x1
$L351:
	lw	$31,44($sp)
	lw	$21,40($sp)
	lw	$20,36($sp)
	lw	$19,32($sp)
	lw	$18,28($sp)
	lw	$17,24($sp)
	lw	$16,20($sp)
	j	$31
	addiu	$sp,$sp,48

	.set	macro
	.set	reorder
	.end	do_filter
	.size	do_filter, .-do_filter
	.align	2
	.globl	FilterWeb_v2
	.set	nomips16
	.ent	FilterWeb_v2
	.type	FilterWeb_v2, @function
FilterWeb_v2:
	.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	sw	$16,16($sp)
	lui	$2,%hi(rtl_ip_hdr)
	addiu	$2,$2,%lo(rtl_ip_hdr)
	jalr	$2
	move	$16,$4

	lui	$2,%hi(need_filter)
	addiu	$2,$2,%lo(need_filter)
	jalr	$2
	move	$4,$16

	beq	$2,$0,$L357
	move	$4,$16

	lui	$25,%hi(do_filter)
	lw	$31,20($sp)
	addiu	$25,$25,%lo(do_filter)
	lw	$16,16($sp)
	jr	$25
	addiu	$sp,$sp,24

$L357:
	lw	$31,20($sp)
	lw	$16,16($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	FilterWeb_v2
	.size	FilterWeb_v2, .-FilterWeb_v2
	.section	.rodata.str1.4
	.align	2
$LC28:
	.ascii	"filter_table\000"
	.text
	.align	2
	.globl	filter_table_init
	.set	nomips16
	.ent	filter_table_init
	.type	filter_table_init, @function
filter_table_init:
	.frame	$sp,32,$31		# vars= 0, regs= 1/0, args= 24, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	lui	$2,%hi(filter_table_head_init)
	addiu	$2,$2,%lo(filter_table_head_init)
	jalr	$2
	nop

	lui	$4,%hi($LC28)
	lui	$6,%hi(proc_root)
	lui	$7,%hi(filter_table_proc_fops)
	lui	$2,%hi(proc_create_data)
	addiu	$4,$4,%lo($LC28)
	move	$5,$0
	addiu	$6,$6,%lo(proc_root)
	addiu	$7,$7,%lo(filter_table_proc_fops)
	addiu	$2,$2,%lo(proc_create_data)
	jalr	$2
	sw	$0,16($sp)

	lui	$3,%hi(res12)
	lw	$31,28($sp)
	sw	$2,%lo(res12)($3)
	move	$2,$0
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
	.end	filter_table_init
	.size	filter_table_init, .-filter_table_init
	.align	2
	.globl	filter_init_fastpath
	.set	nomips16
	.ent	filter_init_fastpath
	.type	filter_init_fastpath, @function
filter_init_fastpath:
	.frame	$sp,24,$31		# vars= 0, regs= 1/0, args= 16, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	li	$3,1			# 0x1
	lui	$2,%hi(filter_rule_num)
	sw	$3,%lo(filter_rule_num)($2)
	lui	$2,%hi(filter_table_init)
	addiu	$2,$2,%lo(filter_table_init)
	jalr	$2
	nop

	move	$2,$0
	lw	$31,20($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	filter_init_fastpath
	.size	filter_init_fastpath, .-filter_init_fastpath
	.align	2
	.globl	filter_exit_fastpath
	.set	nomips16
	.ent	filter_exit_fastpath
	.type	filter_exit_fastpath, @function
filter_exit_fastpath:
	.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	sw	$16,16($sp)
	lui	$16,%hi(res12)
	lw	$2,%lo(res12)($16)
	beq	$2,$0,$L361
	lui	$4,%hi($LC28)

	lui	$5,%hi(proc_root)
	lui	$2,%hi(remove_proc_entry)
	addiu	$4,$4,%lo($LC28)
	addiu	$2,$2,%lo(remove_proc_entry)
	jalr	$2
	addiu	$5,$5,%lo(proc_root)

	sw	$0,%lo(res12)($16)
$L361:
	lw	$31,20($sp)
	move	$2,$0
	lw	$16,16($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	filter_exit_fastpath
	.size	filter_exit_fastpath, .-filter_exit_fastpath
	.align	2
	.globl	strtoint
	.set	nomips16
	.ent	strtoint
	.type	strtoint, @function
strtoint:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	j	$L363
	move	$2,$0

$L365:
	beq	$8,$0,$L366
	nop

	addu	$2,$6,$5
$L363:
	lb	$3,0($4)
	sll	$7,$2,1
	sll	$6,$2,3
	addiu	$4,$4,1
	addiu	$5,$3,-48
	addu	$6,$7,$6
	bne	$3,$0,$L365
	sltu	$8,$5,10

$L366:
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	strtoint
	.size	strtoint, .-strtoint
	.align	2
	.globl	clear_attack_address
	.set	nomips16
	.ent	clear_attack_address
	.type	clear_attack_address, @function
clear_attack_address:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	lui	$7,%hi(attack_saddr)
	lui	$6,%hi(attack_daddr)
	move	$2,$0
	addiu	$7,$7,%lo(attack_saddr)
	addiu	$6,$6,%lo(attack_daddr)
	li	$5,108			# 0x6c
$L368:
	addu	$4,$7,$2
	addu	$3,$6,$2
	addiu	$2,$2,4
	sw	$0,0($4)
	bne	$2,$5,$L368
	sw	$0,0($3)

	j	$31
	nop

	.set	macro
	.set	reorder
	.end	clear_attack_address
	.size	clear_attack_address, .-clear_attack_address
	.align	2
	.globl	strtok
	.set	nomips16
	.ent	strtok
	.type	strtok, @function
strtok:
	.frame	$sp,32,$31		# vars= 0, regs= 4/0, args= 16, gp= 0
	.mask	0x80070000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$18,24($sp)
	sw	$17,20($sp)
	sw	$16,16($sp)
	bne	$4,$0,$L375
	move	$16,$5

	lui	$18,%hi(___strtok)
	lw	$17,%lo(___strtok)($18)
	bne	$17,$0,$L371
	move	$2,$17

	j	$L376
	nop

$L375:
	move	$17,$4
	lui	$18,%hi(___strtok)
$L371:
	lui	$2,%hi(strspn)
	move	$4,$17
	addiu	$2,$2,%lo(strspn)
	jalr	$2
	move	$5,$16

	addu	$17,$17,$2
	lb	$2,0($17)
	bne	$2,$0,$L373
	lui	$2,%hi(strpbrk)

	sw	$0,%lo(___strtok)($18)
	j	$L372
	move	$17,$0

$L373:
	move	$4,$17
	addiu	$2,$2,%lo(strpbrk)
	jalr	$2
	move	$5,$16

	beq	$2,$0,$L374
	nop

	lb	$3,0($2)
	beq	$3,$0,$L374
	nop

	sb	$0,0($2)
	addiu	$2,$2,1
$L374:
	sw	$2,%lo(___strtok)($18)
$L372:
	move	$2,$17
$L376:
	lw	$31,28($sp)
	lw	$18,24($sp)
	lw	$17,20($sp)
	lw	$16,16($sp)
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
	.end	strtok
	.size	strtok, .-strtok
	.align	2
	.set	nomips16
	.ent	dos_single_write
	.type	dos_single_write, @function
dos_single_write:
	.frame	$sp,136,$31		# vars= 80, regs= 10/0, args= 16, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-136
	sw	$31,132($sp)
	sw	$fp,128($sp)
	sw	$23,124($sp)
	sw	$22,120($sp)
	sw	$21,116($sp)
	sw	$20,112($sp)
	sw	$19,108($sp)
	sw	$18,104($sp)
	sw	$17,100($sp)
	sw	$16,96($sp)
	sltu	$3,$6,2
	.set	noreorder
	.set	nomacro
	bne	$3,$0,$L400
	move	$23,$6
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$5,$0,$L400
	or	$3,$5,$6
	.set	macro
	.set	reorder

	addu	$2,$5,$6
	or	$2,$3,$2
	lw	$3,24($28)
	and	$2,$2,$3
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L400
	lui	$2,%hi(dos_flag)
	.set	macro
	.set	reorder

	addiu	$4,$2,%lo(dos_flag)
 #APP
 # 3475 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/fastpath-0.1/filter.c" 1
	.set	noreorder
	.set	noat
	la	$1, __copy_user
	jalr	$1
	.set	at
	.set	noat
	addu	$1, $5, $6
	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	bne	$6,$0,$L400
	addiu	$2,$2,%lo(dos_flag)
	.set	macro
	.set	reorder

	addiu	$3,$sp,16
	li	$4,80			# 0x50
 #APP
 # 55 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
1:	lbu	$1,($2)
	subu	$4,1
	sb	$1,($3)
	beqz	$1,2f
	addiu	$3,1
	bnez	$4,1b
	addiu	$2,1
2:
	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
	lui	$20,%hi(strtok)
	lui	$22,%hi($L395)
	li	$17,1			# 0x1
	addiu	$4,$sp,16
	lui	$19,%hi($LC19)
	addiu	$20,$20,%lo(strtok)
	lui	$21,%hi(simple_strtol)
	addiu	$22,$22,%lo($L395)
	.set	noreorder
	.set	nomacro
	j	$L379
	lui	$fp,%hi(item_0)
	.set	macro
	.set	reorder

$L396:
	move	$4,$16
	move	$5,$0
	addiu	$18,$21,%lo(simple_strtol)
	.set	noreorder
	.set	nomacro
	jalr	$18
	move	$6,$0
	.set	macro
	.set	reorder

	sltu	$3,$17,15
	.set	noreorder
	.set	nomacro
	beq	$3,$0,$L380
	sll	$3,$17,2
	.set	macro
	.set	reorder

	addu	$3,$22,$3
	lw	$3,0($3)
	j	$3
	.rdata
	.align	2
	.align	2
$L395:
	.word	$L380
	.word	$L381
	.word	$L382
	.word	$L383
	.word	$L384
	.word	$L385
	.word	$L386
	.word	$L387
	.word	$L388
	.word	$L389
	.word	$L390
	.word	$L391
	.word	$L392
	.word	$L393
	.word	$L394
	.text
$L381:
	lui	$3,%hi(op_mode)
	.set	noreorder
	.set	nomacro
	j	$L380
	sb	$2,%lo(op_mode)($3)
	.set	macro
	.set	reorder

$L382:
	move	$4,$16
	move	$5,$0
	.set	noreorder
	.set	nomacro
	jalr	$18
	li	$6,16			# 0x10
	.set	macro
	.set	reorder

	lui	$3,%hi(lan_addr)
	.set	noreorder
	.set	nomacro
	j	$L380
	sw	$2,%lo(lan_addr)($3)
	.set	macro
	.set	reorder

$L383:
	move	$4,$16
	move	$5,$0
	.set	noreorder
	.set	nomacro
	jalr	$18
	li	$6,16			# 0x10
	.set	macro
	.set	reorder

	lui	$3,%hi(lan_mask)
	.set	noreorder
	.set	nomacro
	j	$L380
	sw	$2,%lo(lan_mask)($3)
	.set	macro
	.set	reorder

$L384:
	lui	$3,%hi(item)
	sw	$2,%lo(item)($3)
	lui	$2,%hi(item_backup)
	.set	noreorder
	.set	nomacro
	j	$L380
	sw	$0,%lo(item_backup)($2)
	.set	macro
	.set	reorder

$L385:
	lui	$3,%hi(whole_syn_threshold)
	.set	noreorder
	.set	nomacro
	j	$L380
	sw	$2,%lo(whole_syn_threshold)($3)
	.set	macro
	.set	reorder

$L386:
	lui	$3,%hi(whole_fin_threshold)
	.set	noreorder
	.set	nomacro
	j	$L380
	sw	$2,%lo(whole_fin_threshold)($3)
	.set	macro
	.set	reorder

$L387:
	lui	$3,%hi(whole_udp_threshold)
	.set	noreorder
	.set	nomacro
	j	$L380
	sw	$2,%lo(whole_udp_threshold)($3)
	.set	macro
	.set	reorder

$L388:
	lui	$3,%hi(whole_icmp_threshold)
	.set	noreorder
	.set	nomacro
	j	$L380
	sw	$2,%lo(whole_icmp_threshold)($3)
	.set	macro
	.set	reorder

$L389:
	lui	$3,%hi(per_syn_threshold)
	.set	noreorder
	.set	nomacro
	j	$L380
	sw	$2,%lo(per_syn_threshold)($3)
	.set	macro
	.set	reorder

$L390:
	lui	$3,%hi(per_fin_threshold)
	.set	noreorder
	.set	nomacro
	j	$L380
	sw	$2,%lo(per_fin_threshold)($3)
	.set	macro
	.set	reorder

$L391:
	lui	$3,%hi(per_udp_threshold)
	.set	noreorder
	.set	nomacro
	j	$L380
	sw	$2,%lo(per_udp_threshold)($3)
	.set	macro
	.set	reorder

$L392:
	lui	$3,%hi(per_icmp_threshold)
	.set	noreorder
	.set	nomacro
	j	$L380
	sw	$2,%lo(per_icmp_threshold)($3)
	.set	macro
	.set	reorder

$L393:
	lui	$3,%hi(block_time)
	.set	noreorder
	.set	nomacro
	j	$L380
	sw	$2,%lo(block_time)($3)
	.set	macro
	.set	reorder

$L394:
	sw	$2,%lo(item_0)($fp)
$L380:
	addiu	$17,$17,1
	move	$4,$0
	andi	$17,$17,0x00ff
$L379:
	.set	noreorder
	.set	nomacro
	jalr	$20
	addiu	$5,$19,%lo($LC19)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L396
	move	$16,$2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L401
	move	$2,$23
	.set	macro
	.set	reorder

$L400:
	li	$23,-14			# 0xfffffffffffffff2
	move	$2,$23
$L401:
	lw	$31,132($sp)
	lw	$fp,128($sp)
	lw	$23,124($sp)
	lw	$22,120($sp)
	lw	$21,116($sp)
	lw	$20,112($sp)
	lw	$19,108($sp)
	lw	$18,104($sp)
	lw	$17,100($sp)
	lw	$16,96($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,136
	.set	macro
	.set	reorder

	.end	dos_single_write
	.size	dos_single_write, .-dos_single_write
	.section	.rodata.str1.4
	.align	2
$LC29:
	.ascii	"%u.%u.%u.%u\000"
	.text
	.align	2
	.globl	IP2NAME
	.set	nomips16
	.ent	IP2NAME
	.type	IP2NAME, @function
IP2NAME:
	.frame	$sp,32,$31		# vars= 0, regs= 2/0, args= 24, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$16,24($sp)
	lui	$2,%hi(memset)
	move	$16,$5
	sw	$4,32($sp)
	move	$5,$0
	move	$4,$16
	addiu	$2,$2,%lo(memset)
	jalr	$2
	li	$6,16			# 0x10

	lui	$5,%hi($LC29)
	lbu	$2,35($sp)
	move	$4,$16
	lbu	$3,34($sp)
	addiu	$5,$5,%lo($LC29)
	sw	$2,20($sp)
	lui	$2,%hi(sprintf)
	lbu	$6,32($sp)
	addiu	$2,$2,%lo(sprintf)
	lbu	$7,33($sp)
	jalr	$2
	sw	$3,16($sp)

	move	$2,$16
	lw	$31,28($sp)
	lw	$16,24($sp)
	j	$31
	addiu	$sp,$sp,32

	.set	macro
	.set	reorder
	.end	IP2NAME
	.size	IP2NAME, .-IP2NAME
	.section	.rodata.str1.4
	.align	2
$LC30:
	.ascii	"%s\012\000"
	.align	2
$LC31:
	.ascii	"connectip = %s\012\000"
	.align	2
$LC32:
	.ascii	"pkt---IP:%s, syn_cnt:%d, fin_cnt:%d, udp_nct:%d, icmp_cn"
	.ascii	"t:%d, scan_cnt:%d\012\000"
	.align	2
$LC33:
	.ascii	"attack_saddr[%s]=%s,attack_daddr[%s]=%s\012\000"
	.align	2
$LC34:
	.ascii	"op_mode = %d, lan_addr = %s, lan_mask = %s, item = 0x%x,"
	.ascii	"item_0 = 0x%x\012\000"
	.text
	.align	2
	.set	nomips16
	.ent	dos_read_proc
	.type	dos_read_proc, @function
dos_read_proc:
	.frame	$sp,72,$31		# vars= 0, regs= 10/0, args= 32, gp= 0
	.mask	0xc0ff0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-72
	sw	$31,68($sp)
	sw	$fp,64($sp)
	sw	$23,60($sp)
	sw	$22,56($sp)
	sw	$21,52($sp)
	sw	$20,48($sp)
	sw	$19,44($sp)
	sw	$18,40($sp)
	sw	$17,36($sp)
	sw	$16,32($sp)
	lui	$5,%hi($LC30)
	lui	$6,%hi(dos_flag)
	lui	$21,%hi(seq_printf)
	addiu	$5,$5,%lo($LC30)
	addiu	$6,$6,%lo(dos_flag)
	addiu	$21,$21,%lo(seq_printf)
	lui	$16,%hi(ConnectedIp)
	move	$22,$4
	jalr	$21
	addiu	$16,$16,%lo(ConnectedIp)

	lui	$20,%hi(IP2NAME)
	lui	$2,%hi(ip_name0)
	lui	$19,%hi($LC31)
	addiu	$17,$16,1024
	addiu	$20,$20,%lo(IP2NAME)
	addiu	$18,$2,%lo(ip_name0)
	addiu	$19,$19,%lo($LC31)
$L405:
	lw	$4,0($16)
	beq	$4,$0,$L404
	addiu	$16,$16,4

	jalr	$20
	move	$5,$18

	move	$4,$22
	move	$5,$19
	jalr	$21
	move	$6,$2

$L404:
	bne	$16,$17,$L405
	lui	$2,%hi(ip_name0)

	lui	$16,%hi(dos_pkt)
	addiu	$19,$2,%lo(ip_name0)
	lui	$2,%hi(local_bh_disable)
	addiu	$2,$2,%lo(local_bh_disable)
	addiu	$16,$16,%lo(dos_pkt)
	li	$18,40960			# 0xa000
	lui	$23,%hi($LC32)
	li	$17,1			# 0x1
	jalr	$2
	addu	$18,$16,$18

	addiu	$23,$23,%lo($LC32)
$L407:
	lb	$2,0($16)
	bne	$2,$17,$L406
	nop

	lw	$4,28($16)
	jalr	$20
	move	$5,$19

	move	$4,$22
	lw	$7,4($16)
	move	$6,$2
	lw	$3,8($16)
	move	$5,$23
	lw	$9,12($16)
	lw	$8,16($16)
	lw	$2,24($16)
	sw	$3,16($sp)
	sw	$9,20($sp)
	sw	$8,24($sp)
	jalr	$21
	sw	$2,28($sp)

$L406:
	addiu	$16,$16,40
	bne	$16,$18,$L407
	nop

	lui	$16,%hi(attack_daddr)
	lui	$17,%hi(attack_saddr)
	addiu	$16,$16,%lo(attack_daddr)
	lui	$18,%hi(rtl_dos_name)
	addiu	$17,$17,%lo(attack_saddr)
	addiu	$18,$18,%lo(rtl_dos_name)
	addiu	$fp,$16,108
$L411:
	lw	$2,0($16)
	lw	$4,0($17)
	bne	$2,$0,$L415
	lui	$5,%hi(ip_name0)

	beq	$4,$0,$L410
	nop

$L415:
	jalr	$20
	addiu	$5,$5,%lo(ip_name0)

	lui	$5,%hi(ip_name1)
	lw	$4,0($16)
	addiu	$5,$5,%lo(ip_name1)
	lw	$19,0($18)
	jalr	$20
	move	$23,$2

	lui	$5,%hi($LC33)
	move	$4,$22
	addiu	$5,$5,%lo($LC33)
	move	$6,$19
	sw	$19,16($sp)
	move	$7,$23
	jalr	$21
	sw	$2,20($sp)

$L410:
	addiu	$16,$16,4
	addiu	$17,$17,4
	bne	$16,$fp,$L411
	addiu	$18,$18,4

	lui	$2,%hi(local_bh_enable)
	addiu	$2,$2,%lo(local_bh_enable)
	jalr	$2
	nop

	lui	$2,%hi(lan_addr)
	lw	$4,%lo(lan_addr)($2)
	lui	$2,%hi(ip_name0)
	addiu	$5,$2,%lo(ip_name0)
	lui	$2,%hi(op_mode)
	lb	$16,%lo(op_mode)($2)
	jalr	$20
	nop

	move	$17,$2
	lui	$2,%hi(ip_name1)
	addiu	$5,$2,%lo(ip_name1)
	lui	$2,%hi(lan_mask)
	lw	$4,%lo(lan_mask)($2)
	jalr	$20
	nop

	lui	$3,%hi(item)
	lw	$8,%lo(item)($3)
	lui	$3,%hi(item_0)
	lw	$3,%lo(item_0)($3)
	lui	$5,%hi($LC34)
	move	$4,$22
	addiu	$5,$5,%lo($LC34)
	move	$6,$16
	sw	$2,16($sp)
	move	$7,$17
	sw	$8,20($sp)
	jalr	$21
	sw	$3,24($sp)

	move	$2,$0
	lw	$31,68($sp)
	lw	$fp,64($sp)
	lw	$23,60($sp)
	lw	$22,56($sp)
	lw	$21,52($sp)
	lw	$20,48($sp)
	lw	$19,44($sp)
	lw	$18,40($sp)
	lw	$17,36($sp)
	lw	$16,32($sp)
	j	$31
	addiu	$sp,$sp,72

	.set	macro
	.set	reorder
	.end	dos_read_proc
	.size	dos_read_proc, .-dos_read_proc
	.align	2
	.globl	filter_addconnect
	.set	nomips16
	.ent	filter_addconnect
	.type	filter_addconnect, @function
filter_addconnect:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	andi	$3,$4,0xff
	lui	$2,%hi(ConnectedIp)
	sll	$3,$3,2
	addiu	$2,$2,%lo(ConnectedIp)
	addu	$2,$3,$2
	j	$31
	sw	$4,0($2)

	.set	macro
	.set	reorder
	.end	filter_addconnect
	.size	filter_addconnect, .-filter_addconnect
	.align	2
	.globl	filter_delconnect
	.set	nomips16
	.ent	filter_delconnect
	.type	filter_delconnect, @function
filter_delconnect:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	andi	$4,$4,0x00ff
	lui	$2,%hi(ConnectedIp)
	sll	$4,$4,2
	addiu	$2,$2,%lo(ConnectedIp)
	addu	$4,$4,$2
	j	$31
	sw	$0,0($4)

	.set	macro
	.set	reorder
	.end	filter_delconnect
	.size	filter_delconnect, .-filter_delconnect
	.align	2
	.globl	filter_checkConnect
	.set	nomips16
	.ent	filter_checkConnect
	.type	filter_checkConnect, @function
filter_checkConnect:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	andi	$3,$4,0xff
	lui	$2,%hi(ConnectedIp)
	sll	$3,$3,2
	addiu	$2,$2,%lo(ConnectedIp)
	addu	$2,$3,$2
	lw	$2,0($2)
	beq	$2,$0,$L420
	nop

	xor	$2,$4,$2
	j	$31
	sltu	$2,$0,$2

$L420:
	j	$31
	li	$2,1			# 0x1

	.set	macro
	.set	reorder
	.end	filter_checkConnect
	.size	filter_checkConnect, .-filter_checkConnect
	.align	2
	.globl	unregister_customRspStr
	.set	nomips16
	.ent	unregister_customRspStr
	.type	unregister_customRspStr, @function
unregister_customRspStr:
	.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	sw	$16,16($sp)
	lui	$16,%hi(block_message)
	lw	$4,%lo(block_message)($16)
	beq	$4,$0,$L421
	lui	$2,%hi(kfree)

	addiu	$2,$2,%lo(kfree)
	jalr	$2
	nop

	sw	$0,%lo(block_message)($16)
$L421:
	lw	$31,20($sp)
	lw	$16,16($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	unregister_customRspStr
	.size	unregister_customRspStr, .-unregister_customRspStr
	.align	2
	.globl	register_customRspStr
	.set	nomips16
	.ent	register_customRspStr
	.type	register_customRspStr, @function
register_customRspStr:
	.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	sw	$16,16($sp)
	lui	$2,%hi(unregister_customRspStr)
	addiu	$2,$2,%lo(unregister_customRspStr)
	jalr	$2
	move	$16,$4

	beq	$16,$0,$L424
	lui	$2,%hi(strlen)

	addiu	$2,$2,%lo(strlen)
	jalr	$2
	move	$4,$16

	addiu	$4,$2,1
	lui	$2,%hi(__kmalloc)
	addiu	$2,$2,%lo(__kmalloc)
	jalr	$2
	li	$5,208			# 0xd0

	lui	$3,%hi(block_message)
	beq	$2,$0,$L423
	sw	$2,%lo(block_message)($3)

	lui	$5,%hi($LC14)
	move	$4,$2
	addiu	$5,$5,%lo($LC14)
	j	$L426
	move	$6,$16

$L424:
	lui	$16,%hi($LC1)
	addiu	$2,$2,%lo(strlen)
	jalr	$2
	addiu	$4,$16,%lo($LC1)

	move	$4,$2
	lui	$2,%hi(__kmalloc)
	addiu	$2,$2,%lo(__kmalloc)
	jalr	$2
	li	$5,208			# 0xd0

	lui	$3,%hi(block_message)
	beq	$2,$0,$L423
	sw	$2,%lo(block_message)($3)

	lui	$5,%hi($LC14)
	move	$4,$2
	addiu	$5,$5,%lo($LC14)
	addiu	$6,$16,%lo($LC1)
$L426:
	lui	$25,%hi(sprintf)
	lw	$31,20($sp)
	addiu	$25,$25,%lo(sprintf)
	lw	$16,16($sp)
	jr	$25
	addiu	$sp,$sp,24

$L423:
	lw	$31,20($sp)
	lw	$16,16($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	register_customRspStr
	.size	register_customRspStr, .-register_customRspStr
	.align	2
	.globl	register_customRspHook
	.set	nomips16
	.ent	register_customRspHook
	.type	register_customRspHook, @function
register_customRspHook:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L428
	lui	$2,%hi(fast_path_cusRsp401_func)

	j	$L429
	sw	$4,%lo(fast_path_cusRsp401_func)($2)

$L428:
	lui	$3,%hi(GenerateHTTP401)
	addiu	$3,$3,%lo(GenerateHTTP401)
	sw	$3,%lo(fast_path_cusRsp401_func)($2)
$L429:
	beq	$5,$0,$L430
	lui	$2,%hi(fast_path_cusRspTCPFinAck_func)

	j	$L431
	sw	$5,%lo(fast_path_cusRspTCPFinAck_func)($2)

$L430:
	lui	$3,%hi(GenerateTCPFINACK)
	addiu	$3,$3,%lo(GenerateTCPFINACK)
	sw	$3,%lo(fast_path_cusRspTCPFinAck_func)($2)
$L431:
	beq	$6,$0,$L432
	lui	$2,%hi(fast_path_cusRspTCPEndAck_func)

	j	$31
	sw	$6,%lo(fast_path_cusRspTCPEndAck_func)($2)

$L432:
	lui	$3,%hi(GenerateTCPENDACK)
	addiu	$3,$3,%lo(GenerateTCPENDACK)
	j	$31
	sw	$3,%lo(fast_path_cusRspTCPEndAck_func)($2)

	.set	macro
	.set	reorder
	.end	register_customRspHook
	.size	register_customRspHook, .-register_customRspHook
	.align	2
	.globl	unregister_customRspHook
	.set	nomips16
	.ent	unregister_customRspHook
	.type	unregister_customRspHook, @function
unregister_customRspHook:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	lui	$2,%hi(fast_path_cusRsp401_func)
	sw	$0,%lo(fast_path_cusRsp401_func)($2)
	lui	$2,%hi(fast_path_cusRspTCPFinAck_func)
	sw	$0,%lo(fast_path_cusRspTCPFinAck_func)($2)
	lui	$2,%hi(fast_path_cusRspTCPEndAck_func)
	j	$31
	sw	$0,%lo(fast_path_cusRspTCPEndAck_func)($2)

	.set	macro
	.set	reorder
	.end	unregister_customRspHook
	.size	unregister_customRspHook, .-unregister_customRspHook
	.align	2
	.globl	filter_enter
	.set	nomips16
	.ent	filter_enter
	.type	filter_enter, @function
filter_enter:
	.frame	$sp,56,$31		# vars= 0, regs= 9/0, args= 16, gp= 0
	.mask	0x80ff0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-56
	sw	$31,52($sp)
	sw	$23,48($sp)
	sw	$22,44($sp)
	sw	$21,40($sp)
	sw	$20,36($sp)
	sw	$19,32($sp)
	sw	$18,28($sp)
	sw	$17,24($sp)
	sw	$16,20($sp)
	lui	$17,%hi(item)
	lw	$2,%lo(item)($17)
	bne	$2,$0,$L436
	move	$16,$4

	lui	$2,%hi(table_list_head+24)
	lw	$2,%lo(table_list_head+24)($2)
	sltu	$2,$2,2
	beq	$2,$0,$L436
	lui	$3,%hi(none_dos_drop_pkt_cnt)

	li	$2,1			# 0x1
	lw	$4,%lo(none_dos_drop_pkt_cnt)($3)
	addiu	$4,$4,1
	j	$L437
	sw	$4,%lo(none_dos_drop_pkt_cnt)($3)

$L436:
	lui	$2,%hi(rtl_get_skb_type)
	addiu	$2,$2,%lo(rtl_get_skb_type)
	jalr	$2
	move	$4,$16

	bne	$2,$0,$L437
	li	$2,4			# 0x4

	lui	$2,%hi(rtl_get_skb_protocol)
	addiu	$2,$2,%lo(rtl_get_skb_protocol)
	jalr	$2
	move	$4,$16

	li	$3,2048			# 0x800
	bne	$2,$3,$L437
	li	$2,4			# 0x4

	lui	$2,%hi(table_list_head+24)
	lw	$2,%lo(table_list_head+24)($2)
	sltu	$2,$2,2
	bne	$2,$0,$L438
	lui	$2,%hi(FilterWeb_v2)

	addiu	$2,$2,%lo(FilterWeb_v2)
	jalr	$2
	move	$4,$16

	beq	$2,$0,$L439
	lui	$2,%hi(fast_path_cusRsp401_func)

	lw	$2,%lo(fast_path_cusRsp401_func)($2)
	bne	$2,$0,$L632
	nop

	j	$L437
	move	$2,$0

$L439:
	lw	$2,%lo(fast_path_cusRsp401_func)($2)
	beq	$2,$0,$L438
	lui	$3,%hi(url_cache)

	li	$2,1			# 0x1
	addiu	$3,$3,%lo(url_cache)
	lbu	$4,15($3)
	bne	$4,$2,$L440
	nop

	lui	$2,%hi(fast_path_cusRspTCPFinAck_func)
	lw	$2,%lo(fast_path_cusRspTCPFinAck_func)($2)
	bne	$2,$0,$L632
	nop

	j	$L437
	move	$2,$0

$L440:
	lbu	$3,16($3)
	bne	$3,$2,$L438
	lui	$2,%hi(fast_path_cusRspTCPEndAck_func)

	lw	$2,%lo(fast_path_cusRspTCPEndAck_func)($2)
	beq	$2,$0,$L620
	nop

$L632:
	jalr	$2
	move	$4,$16

	j	$L437
	move	$2,$0

$L438:
	lw	$2,%lo(item)($17)
	andi	$2,$2,0x1
	bne	$2,$0,$L625
	move	$4,$16

	lui	$20,%hi(rtl_ip_hdr)
	j	$L441
	addiu	$20,$20,%lo(rtl_ip_hdr)

$L625:
	lui	$20,%hi(rtl_ip_hdr)
	addiu	$20,$20,%lo(rtl_ip_hdr)
	jalr	$20
	lui	$19,%hi(rtl_get_dev_by_name)

	lui	$4,%hi($LC15)
	addiu	$19,$19,%lo(rtl_get_dev_by_name)
	addiu	$4,$4,%lo($LC15)
	lbu	$23,0($2)
	lui	$22,%hi(wan_ppp_dev)
	jalr	$19
	move	$18,$2

	lui	$4,%hi($LC16)
	lui	$21,%hi(wan_dev)
	addiu	$4,$4,%lo($LC16)
	andi	$23,$23,0xf
	jalr	$19
	sw	$2,%lo(wan_ppp_dev)($22)

	lui	$19,%hi(rtl_get_skb_dev)
	move	$4,$16
	addiu	$19,$19,%lo(rtl_get_skb_dev)
	jalr	$19
	sw	$2,%lo(wan_dev)($21)

	beq	$2,$0,$L441
	nop

	jalr	$19
	move	$4,$16

	lw	$3,%lo(wan_dev)($21)
	beq	$3,$2,$L443
	nop

	jalr	$19
	move	$4,$16

	lw	$3,%lo(wan_ppp_dev)($22)
	bne	$3,$2,$L441
	nop

$L443:
	lw	$22,%lo(item)($17)
	sll	$21,$23,2
	andi	$2,$22,0x3fe
	beq	$2,$0,$L544
	addu	$21,$18,$21

	lui	$2,%hi(dos_pkt_locate)
	addiu	$2,$2,%lo(dos_pkt_locate)
	jalr	$2
	move	$4,$18

	beq	$2,$0,$L444
	move	$19,$0

	andi	$2,$22,0x22
	beq	$2,$0,$L635
	andi	$2,$22,0x44

	lui	$2,%hi(cur_p_pkt)
	lbu	$3,9($18)
	lw	$4,%lo(cur_p_pkt)($2)
	li	$2,6			# 0x6
	bne	$3,$2,$L635
	andi	$2,$22,0x44

	lbu	$3,13($21)
	li	$2,2			# 0x2
	andi	$3,$3,0x3f
	bne	$3,$2,$L635
	andi	$2,$22,0x44

	lui	$2,%hi(block)
	li	$3,1			# 0x1
	lw	$5,%lo(block)($2)
	bne	$5,$3,$L446
	lui	$3,%hi(attack_saddr+4)

	lw	$5,%lo(attack_saddr+4)($3)
	lw	$3,12($18)
	beq	$5,$3,$L548
	nop

$L446:
	lw	$5,4($4)
	lui	$3,%hi(per_syn_threshold)
	lw	$3,%lo(per_syn_threshold)($3)
	addiu	$5,$5,1
	slt	$6,$3,$5
	beq	$6,$0,$L551
	sw	$5,4($4)

	andi	$4,$22,0x20
	beq	$4,$0,$L445
	move	$19,$0

	blez	$3,$L445
	lui	$3,%hi(LogFlag)

	lw	$6,12($18)
	lui	$5,%hi(attack_saddr+4)
	move	$19,$0
	lw	$4,%lo(LogFlag)($3)
	sw	$6,%lo(attack_saddr+4)($5)
	li	$6,1			# 0x1
	lw	$5,16($18)
	ori	$4,$4,0x20
	sw	$6,%lo(block)($2)
	lui	$2,%hi(attack_daddr+4)
	sw	$5,%lo(attack_daddr+4)($2)
	j	$L445
	sw	$4,%lo(LogFlag)($3)

$L548:
	j	$L445
	li	$19,-1			# 0xffffffffffffffff

$L551:
	move	$19,$0
$L445:
	andi	$2,$22,0x44
$L635:
	beq	$2,$0,$L447
	lui	$2,%hi(cur_p_pkt)

	lbu	$3,9($18)
	lw	$4,%lo(cur_p_pkt)($2)
	li	$2,6			# 0x6
	bne	$3,$2,$L448
	move	$3,$0

	lbu	$3,13($21)
	li	$2,1			# 0x1
	andi	$3,$3,0x3f
	bne	$3,$2,$L557
	lui	$2,%hi(block)

	lw	$5,%lo(block)($2)
	bne	$5,$3,$L449
	lui	$3,%hi(attack_saddr+8)

	lw	$5,%lo(attack_saddr+8)($3)
	lw	$3,12($18)
	beq	$5,$3,$L448
	li	$3,-1			# 0xffffffffffffffff

$L449:
	lw	$5,8($4)
	lui	$3,%hi(per_fin_threshold)
	lw	$3,%lo(per_fin_threshold)($3)
	addiu	$5,$5,1
	slt	$6,$3,$5
	beq	$6,$0,$L557
	sw	$5,8($4)

	andi	$22,$22,0x40
	beq	$22,$0,$L557
	nop

	blez	$3,$L557
	lui	$4,%hi(LogFlag)

	lw	$6,12($18)
	lui	$3,%hi(attack_saddr+8)
	li	$7,1			# 0x1
	lw	$5,%lo(LogFlag)($4)
	sw	$6,%lo(attack_saddr+8)($3)
	move	$3,$0
	lw	$6,16($18)
	ori	$5,$5,0x40
	sw	$7,%lo(block)($2)
	lui	$2,%hi(attack_daddr+8)
	sw	$6,%lo(attack_daddr+8)($2)
	j	$L448
	sw	$5,%lo(LogFlag)($4)

$L557:
	move	$3,$0
$L448:
	or	$19,$19,$3
$L447:
	lw	$4,%lo(item)($17)
	andi	$2,$4,0x88
	beq	$2,$0,$L636
	andi	$2,$4,0x110

	lui	$2,%hi(cur_p_pkt)
	lbu	$3,9($18)
	lw	$5,%lo(cur_p_pkt)($2)
	li	$2,17			# 0x11
	bne	$3,$2,$L451
	move	$3,$0

	lui	$2,%hi(block)
	li	$3,1			# 0x1
	lw	$6,%lo(block)($2)
	bne	$6,$3,$L452
	lui	$3,%hi(attack_saddr+12)

	lw	$6,%lo(attack_saddr+12)($3)
	lw	$3,12($18)
	beq	$6,$3,$L451
	li	$3,-1			# 0xffffffffffffffff

$L452:
	lw	$6,12($5)
	lui	$3,%hi(per_udp_threshold)
	lw	$3,%lo(per_udp_threshold)($3)
	addiu	$6,$6,1
	slt	$7,$3,$6
	beq	$7,$0,$L562
	sw	$6,12($5)

	andi	$4,$4,0x80
	beq	$4,$0,$L562
	nop

	blez	$3,$L562
	lui	$4,%hi(LogFlag)

	lw	$6,12($18)
	lui	$3,%hi(attack_saddr+12)
	li	$7,1			# 0x1
	lw	$5,%lo(LogFlag)($4)
	sw	$6,%lo(attack_saddr+12)($3)
	move	$3,$0
	lw	$6,16($18)
	ori	$5,$5,0x80
	sw	$7,%lo(block)($2)
	lui	$2,%hi(attack_daddr+12)
	sw	$6,%lo(attack_daddr+12)($2)
	j	$L451
	sw	$5,%lo(LogFlag)($4)

$L562:
	move	$3,$0
$L451:
	or	$19,$19,$3
	lw	$4,%lo(item)($17)
	andi	$2,$4,0x110
$L636:
	beq	$2,$0,$L453
	lui	$2,%hi(cur_p_pkt)

	lbu	$3,9($18)
	lw	$5,%lo(cur_p_pkt)($2)
	li	$2,1			# 0x1
	bne	$3,$2,$L567
	lui	$2,%hi(block)

	lw	$6,%lo(block)($2)
	bne	$6,$3,$L455
	lui	$3,%hi(attack_saddr+16)

	lw	$6,%lo(attack_saddr+16)($3)
	lw	$3,12($18)
	beq	$6,$3,$L454
	li	$3,-1			# 0xffffffffffffffff

$L455:
	lw	$6,16($5)
	lui	$3,%hi(per_icmp_threshold)
	lw	$3,%lo(per_icmp_threshold)($3)
	addiu	$6,$6,1
	slt	$7,$3,$6
	beq	$7,$0,$L567
	sw	$6,16($5)

	andi	$4,$4,0x100
	beq	$4,$0,$L567
	nop

	blez	$3,$L567
	lui	$4,%hi(LogFlag)

	lw	$6,12($18)
	lui	$3,%hi(attack_saddr+16)
	li	$7,1			# 0x1
	lw	$5,%lo(LogFlag)($4)
	sw	$6,%lo(attack_saddr+16)($3)
	move	$3,$0
	lw	$6,16($18)
	ori	$5,$5,0x100
	sw	$7,%lo(block)($2)
	lui	$2,%hi(attack_daddr+16)
	sw	$6,%lo(attack_daddr+16)($2)
	j	$L454
	sw	$5,%lo(LogFlag)($4)

$L567:
	move	$3,$0
$L454:
	or	$19,$19,$3
$L453:
	lw	$2,%lo(item)($17)
	li	$3,3145728			# 0x300000
	and	$2,$3,$2
	beq	$2,$0,$L456
	lui	$3,%hi(cur_p_pkt)

	lbu	$2,0($18)
	lbu	$5,9($18)
	li	$4,1			# 0x1
	lw	$3,%lo(cur_p_pkt)($3)
	bne	$5,$4,$L569
	andi	$2,$2,0xf

	sll	$2,$2,2
	li	$4,8			# 0x8
	addu	$2,$18,$2
	lbu	$2,0($2)
	beq	$2,$4,$L458
	nop

	bne	$2,$0,$L457
	move	$2,$0

$L458:
	lui	$2,%hi(block)
	lw	$4,%lo(block)($2)
	li	$2,1			# 0x1
	bne	$4,$2,$L459
	nop

	lui	$2,%hi(attack_saddr+20)
	lw	$4,%lo(attack_saddr+20)($2)
	lw	$2,12($18)
	beq	$4,$2,$L570
	nop

$L459:
	lw	$4,20($3)
	move	$2,$0
	addiu	$4,$4,1
	j	$L457
	sw	$4,20($3)

$L569:
	j	$L457
	move	$2,$0

$L570:
	li	$2,-1			# 0xffffffffffffffff
$L457:
	or	$19,$19,$2
$L456:
	lw	$2,%lo(item)($17)
	andi	$2,$2,0x200
	beq	$2,$0,$L460
	lui	$2,%hi(cur_p_pkt)

	lbu	$4,9($18)
	lw	$3,%lo(cur_p_pkt)($2)
	li	$2,6			# 0x6
	bne	$4,$2,$L629
	nop

	lhu	$2,36($3)
	beq	$2,$0,$L462
	li	$5,17			# 0x11

	lhu	$5,2($21)
	bne	$5,$2,$L627
	nop

$L629:
	lw	$2,24($3)
	j	$L633
	li	$5,17			# 0x11

$L627:
	lw	$2,24($3)
	addiu	$2,$2,1
	sw	$2,24($3)
	lbu	$4,9($18)
	j	$L633
	li	$5,17			# 0x11

$L462:
	lhu	$4,2($21)
	lw	$2,24($3)
	sh	$4,36($3)
	lbu	$4,9($18)
$L633:
	bne	$4,$5,$L464
	nop

	lhu	$4,36($3)
	beq	$4,$0,$L465
	nop

	lhu	$5,2($21)
	beq	$5,$4,$L464
	nop

	addiu	$2,$2,1
	j	$L464
	sw	$2,24($3)

$L465:
	lhu	$4,2($21)
	sh	$4,36($3)
$L464:
	lw	$3,%lo(item)($17)
	li	$4,8388608			# 0x800000
	and	$3,$4,$3
	beq	$3,$0,$L467
	nop

	slt	$2,$2,11
	bne	$2,$0,$L460
	lui	$2,%hi(LogFlag)

	j	$L647
	lui	$3,%hi(attack_saddr+24)

$L467:
	slt	$2,$2,201
	bne	$2,$0,$L460
	lui	$2,%hi(LogFlag)

	lui	$3,%hi(attack_saddr+24)
$L647:
	lw	$5,12($18)
	lw	$4,%lo(LogFlag)($2)
	sw	$5,%lo(attack_saddr+24)($3)
	lw	$3,16($18)
	ori	$4,$4,0x200
	sw	$4,%lo(LogFlag)($2)
	lui	$2,%hi(attack_daddr+24)
	sw	$3,%lo(attack_daddr+24)($2)
$L460:
	lw	$2,%lo(item)($17)
	li	$3,4194304			# 0x400000
	and	$2,$3,$2
	j	$L444
	movz	$19,$0,$2

$L544:
	move	$19,$0
$L444:
	lui	$2,%hi(item_0)
	lw	$4,%lo(item_0)($2)
	andi	$2,$4,0x1
	beq	$2,$0,$L468
	li	$2,6			# 0x6

	lbu	$3,9($18)
	bne	$3,$2,$L469
	move	$2,$0

	lbu	$2,0($18)
	andi	$2,$2,0xf
	sll	$2,$2,2
	addu	$2,$18,$2
	lbu	$5,12($2)
	andi	$5,$5,0xf0
	sra	$5,$5,2
	sltu	$3,$5,21
	bne	$3,$0,$L573
	addiu	$2,$2,20

	lui	$10,%hi($L477)
	move	$3,$0
	addiu	$5,$5,-20
	addiu	$10,$10,%lo($L477)
	li	$9,10			# 0xa
	li	$8,3			# 0x3
	j	$L628
	li	$7,4			# 0x4

$L482:
	lbu	$6,0($2)
	sltu	$11,$6,9
	beq	$11,$0,$L471
	sll	$6,$6,2

	addu	$6,$10,$6
	lw	$6,0($6)
	j	$6
	nop

	.rdata
	.align	2
	.align	2
$L477:
	.word	$L473
	.word	$L473
	.word	$L474
	.word	$L475
	.word	$L471
	.word	$L471
	.word	$L471
	.word	$L471
	.word	$L476
	.text
$L473:
	addiu	$2,$2,1
	j	$L628
	addiu	$3,$3,1

$L474:
	lbu	$6,1($2)
	bne	$6,$7,$L471
	addiu	$3,$3,4

	j	$L628
	addiu	$2,$2,4

$L475:
	lbu	$6,1($2)
	bne	$6,$8,$L471
	addiu	$3,$3,3

	j	$L628
	addiu	$2,$2,3

$L476:
	lbu	$6,1($2)
	bne	$6,$9,$L471
	addiu	$3,$3,10

	j	$L628
	addiu	$2,$2,10

$L471:
	lw	$5,12($18)
	lui	$3,%hi(attack_saddr+100)
	li	$2,-1			# 0xffffffffffffffff
	sw	$5,%lo(attack_saddr+100)($3)
	lui	$3,%hi(attack_daddr+100)
	lw	$5,16($18)
	j	$L469
	sw	$5,%lo(attack_daddr+100)($3)

$L628:
	sltu	$6,$3,$5
	bne	$6,$0,$L482
	nop

$L573:
	move	$2,$0
$L469:
	or	$19,$19,$2
$L468:
	andi	$4,$4,0x2
	beq	$4,$0,$L483
	li	$3,17			# 0x11

	lbu	$2,9($18)
	beq	$2,$3,$L484
	li	$3,6			# 0x6

	bne	$2,$3,$L485
	move	$2,$0

$L484:
	lhu	$2,2($21)
	li	$5,7			# 0x7
	beq	$2,$5,$L486
	li	$4,17			# 0x11

	beq	$2,$4,$L486
	li	$3,19			# 0x13

	beq	$2,$3,$L486
	nop

	lhu	$2,0($21)
	beq	$2,$5,$L486
	nop

	beq	$2,$4,$L486
	nop

	bne	$2,$3,$L485
	move	$2,$0

$L486:
	lw	$2,12($18)
	lw	$3,16($18)
	bne	$2,$3,$L576
	lui	$3,%hi(attack_saddr+104)

	sw	$2,%lo(attack_saddr+104)($3)
	lui	$3,%hi(attack_daddr+104)
	lw	$4,16($18)
	li	$2,-1			# 0xffffffffffffffff
	j	$L485
	sw	$4,%lo(attack_daddr+104)($3)

$L576:
	move	$2,$0
$L485:
	or	$19,$19,$2
$L483:
	lw	$2,%lo(item)($17)
	li	$4,536870912			# 0x20000000
	and	$3,$2,$4
	beq	$3,$0,$L637
	li	$3,1073741824			# 0x40000000

	lbu	$3,9($18)
	li	$5,1			# 0x1
	bne	$3,$5,$L488
	nop

	lhu	$3,6($18)
	andi	$3,$3,0x3fff
	bne	$3,$0,$L489
	move	$3,$0

	lbu	$3,0($18)
	lhu	$5,2($18)
	andi	$3,$3,0xf
	sll	$3,$3,2
	subu	$3,$5,$3
	slt	$3,$3,4
	beq	$3,$0,$L579
	lui	$5,%hi(LogFlag)

	lw	$8,12($18)
	lw	$7,%lo(LogFlag)($5)
	lui	$6,%hi(attack_saddr+88)
	sw	$8,%lo(attack_saddr+88)($6)
	li	$3,-1			# 0xffffffffffffffff
	or	$4,$7,$4
	lw	$6,16($18)
	sw	$4,%lo(LogFlag)($5)
	lui	$4,%hi(attack_daddr+88)
	j	$L489
	sw	$6,%lo(attack_daddr+88)($4)

$L488:
	li	$4,17			# 0x11
	beq	$3,$4,$L490
	li	$4,6			# 0x6

	beq	$3,$4,$L491
	li	$4,20			# 0x14

	j	$L489
	move	$3,$0

$L490:
	lbu	$3,0($18)
	li	$4,8			# 0x8
	lhu	$5,2($18)
	andi	$3,$3,0xf
	sll	$3,$3,2
	subu	$3,$5,$3
$L537:
	slt	$3,$3,$4
	beq	$3,$0,$L579
	lui	$4,%hi(LogFlag)

	lw	$5,12($18)
	lw	$7,%lo(LogFlag)($4)
	lui	$3,%hi(attack_saddr+88)
	sw	$5,%lo(attack_saddr+88)($3)
	li	$6,536870912			# 0x20000000
	lw	$5,16($18)
	or	$6,$7,$6
	sw	$6,%lo(LogFlag)($4)
	lui	$4,%hi(attack_daddr+88)
	li	$3,-1			# 0xffffffffffffffff
	j	$L489
	sw	$5,%lo(attack_daddr+88)($4)

$L579:
	move	$3,$0
$L489:
	or	$19,$19,$3
	li	$3,1073741824			# 0x40000000
$L637:
	and	$4,$2,$3
	beq	$4,$0,$L492
	li	$5,1			# 0x1

	lbu	$4,0($18)
	lbu	$6,9($18)
	bne	$6,$5,$L581
	andi	$4,$4,0xf

	sll	$4,$4,2
	addu	$4,$18,$4
	lbu	$5,0($4)
	li	$4,8			# 0x8
	bne	$5,$4,$L581
	lui	$5,%hi(LogFlag)

	lw	$8,12($18)
	lw	$7,%lo(LogFlag)($5)
	lui	$6,%hi(attack_saddr+92)
	sw	$8,%lo(attack_saddr+92)($6)
	li	$4,-1			# 0xffffffffffffffff
	or	$3,$7,$3
	lw	$6,16($18)
	sw	$3,%lo(LogFlag)($5)
	lui	$3,%hi(attack_daddr+92)
	j	$L493
	sw	$6,%lo(attack_daddr+92)($3)

$L581:
	move	$4,$0
$L493:
	or	$19,$19,$4
$L492:
	bgez	$2,$L494
	li	$4,1			# 0x1

	lbu	$3,0($18)
	lbu	$5,9($18)
	bne	$5,$4,$L584
	andi	$3,$3,0xf

	sll	$3,$3,2
	addu	$3,$18,$3
	lbu	$3,0($3)
	bne	$3,$0,$L495
	move	$3,$0

	lui	$3,%hi(icmp_echo_request)
	lw	$3,%lo(icmp_echo_request)($3)
	bne	$3,$0,$L584
	lui	$4,%hi(LogFlag)

	lw	$5,12($18)
	lw	$7,%lo(LogFlag)($4)
	lui	$3,%hi(attack_saddr+96)
	sw	$5,%lo(attack_saddr+96)($3)
	li	$6,-2147483648			# 0xffffffff80000000
	lw	$5,16($18)
	or	$6,$7,$6
	sw	$6,%lo(LogFlag)($4)
	lui	$4,%hi(attack_daddr+96)
	li	$3,-1			# 0xffffffffffffffff
	j	$L495
	sw	$5,%lo(attack_daddr+96)($4)

$L584:
	move	$3,$0
$L495:
	or	$19,$19,$3
$L494:
	andi	$3,$2,0x8000
	beq	$3,$0,$L638
	li	$4,65536			# 0x10000

	lbu	$4,9($18)
	li	$3,6			# 0x6
	bne	$4,$3,$L497
	move	$3,$0

	lbu	$4,13($21)
	lui	$3,%hi(_tcpDosScanBitmap)
	addiu	$3,$3,%lo(_tcpDosScanBitmap)
	andi	$4,$4,0x3f
	addu	$3,$4,$3
	lb	$3,0($3)
	beq	$3,$0,$L586
	lui	$4,%hi(LogFlag)

	lui	$5,%hi(attack_saddr+48)
	lw	$7,12($18)
	li	$3,-1			# 0xffffffffffffffff
	lw	$6,%lo(LogFlag)($4)
	sw	$7,%lo(attack_saddr+48)($5)
	lw	$5,16($18)
	ori	$6,$6,0x8000
	sw	$6,%lo(LogFlag)($4)
	lui	$4,%hi(attack_daddr+48)
	j	$L497
	sw	$5,%lo(attack_daddr+48)($4)

$L586:
	move	$3,$0
$L497:
	or	$19,$19,$3
	li	$4,65536			# 0x10000
$L638:
	and	$3,$2,$4
	beq	$3,$0,$L639
	andi	$3,$2,0x800

	lbu	$5,9($18)
	li	$3,6			# 0x6
	bne	$5,$3,$L499
	move	$3,$0

	lbu	$5,13($21)
	li	$3,2			# 0x2
	andi	$5,$5,0x3f
	bne	$5,$3,$L499
	move	$3,$0

	lbu	$5,0($18)
	lw	$3,12($21)
	lhu	$6,2($18)
	andi	$5,$5,0xf
	sll	$5,$5,2
	srl	$3,$3,28
	subu	$5,$6,$5
	sll	$3,$3,2
	bne	$5,$3,$L631
	nop

	lhu	$3,6($18)
	andi	$3,$3,0x2000
	beq	$3,$0,$L589
	nop

$L631:
	lw	$8,12($18)
	lui	$5,%hi(LogFlag)
	lw	$7,%lo(LogFlag)($5)
	lui	$6,%hi(attack_saddr+52)
	sw	$8,%lo(attack_saddr+52)($6)
	li	$3,-1			# 0xffffffffffffffff
	or	$4,$7,$4
	lw	$6,16($18)
	sw	$4,%lo(LogFlag)($5)
	lui	$4,%hi(attack_daddr+52)
	j	$L499
	sw	$6,%lo(attack_daddr+52)($4)

$L589:
	move	$3,$0
$L499:
	or	$19,$19,$3
	andi	$3,$2,0x800
$L639:
	beq	$3,$0,$L640
	li	$3,262144			# 0x40000

	lw	$3,12($18)
	lw	$4,16($18)
	bne	$3,$4,$L590
	lui	$4,%hi(LogFlag)

	lui	$5,%hi(attack_saddr+32)
	lw	$6,%lo(LogFlag)($4)
	sw	$3,%lo(attack_saddr+32)($5)
	li	$3,-1			# 0xffffffffffffffff
	lw	$5,16($18)
	ori	$6,$6,0x800
	sw	$6,%lo(LogFlag)($4)
	lui	$4,%hi(attack_daddr+32)
	j	$L502
	sw	$5,%lo(attack_daddr+32)($4)

$L590:
	move	$3,$0
$L502:
	or	$19,$19,$3
	li	$3,262144			# 0x40000
$L640:
	and	$3,$2,$3
	beq	$3,$0,$L641
	li	$4,131072			# 0x20000

	lbu	$4,9($18)
	li	$3,17			# 0x11
	bne	$4,$3,$L504
	move	$3,$0

	lhu	$3,2($21)
	li	$6,7			# 0x7
	beq	$3,$6,$L505
	nop

	beq	$3,$4,$L505
	li	$5,19			# 0x13

	beq	$3,$5,$L505
	nop

	lhu	$3,0($21)
	beq	$3,$6,$L505
	nop

	beq	$3,$4,$L505
	nop

	bne	$3,$5,$L592
	nop

$L505:
	lw	$5,12($18)
	lui	$4,%hi(LogFlag)
	lw	$7,%lo(LogFlag)($4)
	lui	$3,%hi(attack_saddr+60)
	sw	$5,%lo(attack_saddr+60)($3)
	li	$6,262144			# 0x40000
	lw	$5,16($18)
	or	$6,$7,$6
	sw	$6,%lo(LogFlag)($4)
	lui	$4,%hi(attack_daddr+60)
	li	$3,-1			# 0xffffffffffffffff
	j	$L504
	sw	$5,%lo(attack_daddr+60)($4)

$L592:
	move	$3,$0
$L504:
	or	$19,$19,$3
	li	$4,131072			# 0x20000
$L641:
	and	$3,$2,$4
	beq	$3,$0,$L642
	andi	$3,$2,0x4000

	lbu	$5,9($18)
	li	$3,17			# 0x11
	bne	$5,$3,$L507
	move	$3,$0

	lhu	$3,6($18)
	andi	$3,$3,0x3fff
	bne	$3,$0,$L507
	move	$3,$0

	lbu	$3,0($18)
	lhu	$6,2($18)
	andi	$3,$3,0xf
	lhu	$5,4($21)
	sll	$3,$3,2
	subu	$3,$6,$3
	slt	$3,$5,$3
	beq	$3,$0,$L595
	lui	$5,%hi(LogFlag)

	lw	$8,12($18)
	lw	$7,%lo(LogFlag)($5)
	lui	$6,%hi(attack_saddr+56)
	sw	$8,%lo(attack_saddr+56)($6)
	li	$3,-1			# 0xffffffffffffffff
	or	$4,$7,$4
	lw	$6,16($18)
	sw	$4,%lo(LogFlag)($5)
	lui	$4,%hi(attack_daddr+56)
	j	$L507
	sw	$6,%lo(attack_daddr+56)($4)

$L595:
	move	$3,$0
$L507:
	or	$19,$19,$3
	andi	$3,$2,0x4000
$L642:
	beq	$3,$0,$L643
	andi	$3,$2,0x400

	lhu	$3,6($18)
	andi	$4,$3,0x2000
	bne	$4,$0,$L598
	andi	$3,$3,0x1fff

	beq	$3,$0,$L598
	sll	$3,$3,3

	lbu	$4,0($18)
	lhu	$5,2($18)
	andi	$4,$4,0xf
	addu	$3,$3,$5
	sll	$4,$4,2
	subu	$4,$3,$4
	li	$3,65536			# 0x10000
	sltu	$3,$4,$3
	bne	$3,$0,$L598
	lui	$4,%hi(LogFlag)

	lui	$5,%hi(attack_saddr+44)
	lw	$7,12($18)
	li	$3,-1			# 0xffffffffffffffff
	lw	$6,%lo(LogFlag)($4)
	sw	$7,%lo(attack_saddr+44)($5)
	lw	$5,16($18)
	ori	$6,$6,0x4000
	sw	$6,%lo(LogFlag)($4)
	lui	$4,%hi(attack_daddr+44)
	j	$L509
	sw	$5,%lo(attack_daddr+44)($4)

$L598:
	move	$3,$0
$L509:
	or	$19,$19,$3
	andi	$3,$2,0x400
$L643:
	beq	$3,$0,$L510
	li	$4,1			# 0x1

	lbu	$3,0($18)
	lbu	$5,9($18)
	bne	$5,$4,$L601
	andi	$3,$3,0xf

	sll	$3,$3,2
	addu	$3,$18,$3
	lbu	$4,0($3)
	li	$3,8			# 0x8
	bne	$4,$3,$L511
	move	$3,$0

	lui	$4,%hi(lan_addr)
	lui	$5,%hi(lan_mask)
	lw	$3,12($18)
	lw	$4,%lo(lan_addr)($4)
	lw	$5,%lo(lan_mask)($5)
	xor	$4,$3,$4
	and	$4,$4,$5
	bne	$4,$0,$L601
	lui	$4,%hi(LogFlag)

	lui	$5,%hi(attack_saddr+28)
	lw	$6,%lo(LogFlag)($4)
	sw	$3,%lo(attack_saddr+28)($5)
	li	$3,-1			# 0xffffffffffffffff
	lw	$5,16($18)
	ori	$6,$6,0x400
	sw	$6,%lo(LogFlag)($4)
	lui	$4,%hi(attack_daddr+28)
	j	$L511
	sw	$5,%lo(attack_daddr+28)($4)

$L601:
	move	$3,$0
$L511:
	or	$19,$19,$3
$L510:
	li	$3,524288			# 0x80000
	and	$4,$2,$3
	beq	$4,$0,$L512
	li	$4,17			# 0x11

	lbu	$5,9($18)
	bne	$5,$4,$L513
	move	$4,$0

	lui	$5,%hi(lan_addr)
	lui	$6,%hi(lan_mask)
	lw	$4,12($18)
	lw	$5,%lo(lan_addr)($5)
	lw	$6,%lo(lan_mask)($6)
	xor	$5,$4,$5
	and	$5,$5,$6
	bne	$5,$0,$L603
	lui	$5,%hi(LogFlag)

	lui	$6,%hi(attack_saddr+64)
	lw	$7,%lo(LogFlag)($5)
	sw	$4,%lo(attack_saddr+64)($6)
	li	$4,-1			# 0xffffffffffffffff
	or	$3,$7,$3
	lw	$6,16($18)
	sw	$3,%lo(LogFlag)($5)
	lui	$3,%hi(attack_daddr+64)
	j	$L513
	sw	$6,%lo(attack_daddr+64)($3)

$L603:
	move	$4,$0
$L513:
	or	$19,$19,$4
$L512:
	li	$3,16777216			# 0x1000000
	and	$3,$2,$3
	beq	$3,$0,$L514
	li	$4,1			# 0x1

	lbu	$3,0($18)
	lbu	$5,9($18)
	bne	$5,$4,$L606
	andi	$3,$3,0xf

	sll	$3,$3,2
	li	$4,8			# 0x8
	addu	$3,$18,$3
	lbu	$3,0($3)
	beq	$3,$4,$L516
	nop

	bne	$3,$0,$L515
	move	$3,$0

$L516:
	lw	$3,12($18)
	li	$5,-268435456			# 0xfffffffff0000000
	li	$4,-536870912			# 0xffffffffe0000000
	and	$5,$3,$5
	beq	$5,$4,$L517
	li	$4,-1			# 0xffffffffffffffff

	beq	$3,$4,$L517
	andi	$4,$3,0x1

	beq	$4,$0,$L606
	nop

$L517:
	lui	$4,%hi(LogFlag)
	lui	$5,%hi(attack_saddr+68)
	lw	$6,%lo(LogFlag)($4)
	sw	$3,%lo(attack_saddr+68)($5)
	li	$3,16777216			# 0x1000000
	or	$3,$6,$3
	lw	$5,16($18)
	sw	$3,%lo(LogFlag)($4)
	lui	$4,%hi(attack_daddr+68)
	li	$3,-1			# 0xffffffffffffffff
	j	$L515
	sw	$5,%lo(attack_daddr+68)($4)

$L606:
	move	$3,$0
$L515:
	or	$19,$19,$3
$L514:
	li	$3,33554432			# 0x2000000
	and	$3,$2,$3
	beq	$3,$0,$L644
	li	$3,67108864			# 0x4000000

	lbu	$4,9($18)
	li	$3,17			# 0x11
	bne	$4,$3,$L519
	move	$3,$0

	lhu	$3,0($21)
	li	$4,7			# 0x7
	beq	$3,$4,$L520
	li	$4,19			# 0x13

	beq	$3,$4,$L520
	li	$4,135			# 0x87

	bne	$3,$4,$L519
	move	$3,$0

$L520:
	lhu	$4,2($21)
	li	$3,135			# 0x87
	bne	$4,$3,$L609
	lui	$4,%hi(LogFlag)

	lw	$5,12($18)
	lw	$7,%lo(LogFlag)($4)
	lui	$3,%hi(attack_saddr+72)
	sw	$5,%lo(attack_saddr+72)($3)
	li	$6,33554432			# 0x2000000
	lw	$5,16($18)
	or	$6,$7,$6
	sw	$6,%lo(LogFlag)($4)
	lui	$4,%hi(attack_daddr+72)
	li	$3,-1			# 0xffffffffffffffff
	j	$L519
	sw	$5,%lo(attack_daddr+72)($4)

$L609:
	move	$3,$0
$L519:
	or	$19,$19,$3
	li	$3,67108864			# 0x4000000
$L644:
	and	$3,$2,$3
	beq	$3,$0,$L645
	li	$3,134217728			# 0x8000000

	lbu	$4,9($18)
	li	$3,6			# 0x6
	bne	$4,$3,$L522
	move	$3,$0

	lbu	$3,13($21)
	andi	$4,$3,0x17
	beq	$4,$0,$L523
	andi	$5,$3,0x3

	li	$4,3			# 0x3
	beq	$5,$4,$L523
	li	$4,1			# 0x1

	andi	$3,$3,0x11
	bne	$3,$4,$L611
	nop

$L523:
	lw	$5,12($18)
	lui	$4,%hi(LogFlag)
	lw	$7,%lo(LogFlag)($4)
	lui	$3,%hi(attack_saddr+76)
	sw	$5,%lo(attack_saddr+76)($3)
	li	$6,67108864			# 0x4000000
	lw	$5,16($18)
	or	$6,$7,$6
	sw	$6,%lo(LogFlag)($4)
	lui	$4,%hi(attack_daddr+76)
	li	$3,-1			# 0xffffffffffffffff
	j	$L522
	sw	$5,%lo(attack_daddr+76)($4)

$L611:
	move	$3,$0
$L522:
	or	$19,$19,$3
	li	$3,134217728			# 0x8000000
$L645:
	and	$4,$2,$3
	beq	$4,$0,$L524
	li	$4,6			# 0x6

	lbu	$5,9($18)
	bne	$5,$4,$L525
	move	$4,$0

	lbu	$4,13($21)
	andi	$4,$4,0x1
	beq	$4,$0,$L613
	lui	$5,%hi(LogFlag)

	lw	$8,12($18)
	lw	$7,%lo(LogFlag)($5)
	lui	$6,%hi(attack_saddr+80)
	sw	$8,%lo(attack_saddr+80)($6)
	li	$4,-1			# 0xffffffffffffffff
	or	$3,$7,$3
	lw	$6,16($18)
	sw	$3,%lo(LogFlag)($5)
	lui	$3,%hi(attack_daddr+80)
	j	$L525
	sw	$6,%lo(attack_daddr+80)($3)

$L613:
	move	$4,$0
$L525:
	or	$19,$19,$4
$L524:
	li	$3,268435456			# 0x10000000
	and	$3,$2,$3
	beq	$3,$0,$L646
	andi	$3,$2,0x1000

	lw	$3,12($18)
	li	$5,-268435456			# 0xfffffffff0000000
	li	$4,-536870912			# 0xffffffffe0000000
	and	$5,$3,$5
	beq	$5,$4,$L527
	li	$4,-1			# 0xffffffffffffffff

	beq	$3,$4,$L527
	andi	$4,$3,0x1

	beq	$4,$0,$L614
	nop

$L527:
	lui	$4,%hi(LogFlag)
	lui	$5,%hi(attack_saddr+84)
	lw	$6,%lo(LogFlag)($4)
	sw	$3,%lo(attack_saddr+84)($5)
	li	$3,268435456			# 0x10000000
	or	$3,$6,$3
	lw	$5,16($18)
	sw	$3,%lo(LogFlag)($4)
	lui	$4,%hi(attack_daddr+84)
	li	$3,-1			# 0xffffffffffffffff
	j	$L528
	sw	$5,%lo(attack_daddr+84)($4)

$L614:
	move	$3,$0
$L528:
	or	$19,$19,$3
	andi	$3,$2,0x1000
$L646:
	beq	$3,$0,$L529
	lui	$4,%hi(lan_addr)

	lui	$5,%hi(lan_mask)
	lw	$3,12($18)
	lw	$4,%lo(lan_addr)($4)
	lw	$5,%lo(lan_mask)($5)
	xor	$4,$3,$4
	and	$4,$4,$5
	bne	$4,$0,$L616
	li	$4,1			# 0x1

	lbu	$5,9($18)
	beq	$5,$4,$L616
	lui	$4,%hi(LogFlag)

	lui	$5,%hi(attack_saddr+36)
	lw	$6,%lo(LogFlag)($4)
	sw	$3,%lo(attack_saddr+36)($5)
	li	$3,-1			# 0xffffffffffffffff
	lw	$5,16($18)
	ori	$6,$6,0x1000
	sw	$6,%lo(LogFlag)($4)
	lui	$4,%hi(attack_daddr+36)
	j	$L530
	sw	$5,%lo(attack_daddr+36)($4)

$L616:
	move	$3,$0
$L530:
	or	$19,$19,$3
$L529:
	andi	$2,$2,0x2000
	beq	$2,$0,$L531
	lui	$2,%hi(dos_pkt_locate)

	addiu	$2,$2,%lo(dos_pkt_locate)
	jalr	$2
	move	$4,$18

	beq	$2,$0,$L619
	lui	$2,%hi(cur_p_pkt)

	lw	$3,%lo(cur_p_pkt)($2)
	lhu	$5,4($18)
	lhu	$2,32($3)
	beq	$5,$2,$L533
	nop

	bne	$2,$0,$L532
	move	$2,$0

$L533:
	lhu	$2,6($18)
	andi	$4,$2,0x3fff
	beq	$4,$0,$L619
	sll	$6,$2,3

	lhu	$4,34($3)
	andi	$6,$6,0xffff
	slt	$6,$6,$4
	bne	$6,$0,$L534
	nop

	andi	$2,$2,0x2000
	bne	$2,$0,$L535
	nop

	sh	$0,32($3)
	j	$L532
	sh	$0,34($3)

$L535:
	sh	$5,32($3)
	move	$2,$0
	lbu	$5,0($18)
	lhu	$6,2($18)
	andi	$5,$5,0xf
	addu	$4,$4,$6
	sll	$5,$5,2
	subu	$4,$4,$5
	j	$L532
	sh	$4,34($3)

$L534:
	lui	$3,%hi(LogFlag)
	lui	$4,%hi(attack_saddr+40)
	lw	$6,12($18)
	li	$2,-1			# 0xffffffffffffffff
	lw	$5,%lo(LogFlag)($3)
	sw	$6,%lo(attack_saddr+40)($4)
	lw	$4,16($18)
	ori	$5,$5,0x2000
	sw	$5,%lo(LogFlag)($3)
	lui	$3,%hi(attack_daddr+40)
	j	$L532
	sw	$4,%lo(attack_daddr+40)($3)

$L619:
	move	$2,$0
$L532:
	or	$19,$19,$2
$L531:
	bne	$19,$0,$L437
	move	$2,$0

$L441:
	jalr	$20
	move	$4,$16

	lbu	$3,9($2)
	li	$2,1			# 0x1
	beq	$3,$2,$L621
	lui	$3,%hi(none_dos_drop_pkt_cnt)

	lw	$4,%lo(none_dos_drop_pkt_cnt)($3)
	addiu	$4,$4,1
	j	$L437
	sw	$4,%lo(none_dos_drop_pkt_cnt)($3)

$L620:
	j	$L437
	move	$2,$0

$L621:
	li	$2,4			# 0x4
$L437:
	lw	$31,52($sp)
	lw	$23,48($sp)
	lw	$22,44($sp)
	lw	$21,40($sp)
	lw	$20,36($sp)
	lw	$19,32($sp)
	lw	$18,28($sp)
	lw	$17,24($sp)
	lw	$16,20($sp)
	j	$31
	addiu	$sp,$sp,56

$L491:
	lbu	$3,0($18)
	lhu	$5,2($18)
	andi	$3,$3,0xf
	sll	$3,$3,2
	j	$L537
	subu	$3,$5,$3

	.set	macro
	.set	reorder
	.end	filter_enter
	.size	filter_enter, .-filter_enter
	.align	2
	.globl	filter_out
	.set	nomips16
	.ent	filter_out
	.type	filter_out, @function
filter_out:
	.frame	$sp,24,$31		# vars= 0, regs= 1/0, args= 16, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	lui	$2,%hi(rtl_ip_hdr)
	addiu	$2,$2,%lo(rtl_ip_hdr)
	jalr	$2
	nop

	lbu	$4,0($2)
	lbu	$3,9($2)
	andi	$5,$4,0xf
	li	$4,1			# 0x1
	bne	$3,$4,$L649
	sll	$5,$5,2

	addu	$2,$2,$5
	lbu	$4,0($2)
	li	$2,8			# 0x8
	bne	$4,$2,$L649
	lui	$2,%hi(jiffies)

	lw	$4,%lo(jiffies)($2)
	lui	$2,%hi(icmp_echo_request)
	sw	$3,%lo(icmp_echo_request)($2)
	lui	$2,%hi(icmp_echo_request_time)
	sw	$4,%lo(icmp_echo_request_time)($2)
$L649:
	lw	$31,20($sp)
	move	$2,$0
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	filter_out
	.size	filter_out, .-filter_out
	.section	.rodata.str1.4
	.align	2
$LC35:
	.ascii	"enable_dos\000"
	.section	.init.text,"ax",@progbits
	.align	2
	.globl	filter_init
	.set	nomips16
	.ent	filter_init
	.type	filter_init, @function
filter_init:
	.frame	$sp,40,$31		# vars= 0, regs= 3/0, args= 24, gp= 0
	.mask	0x80030000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$17,32($sp)
	sw	$16,28($sp)
	lui	$2,%hi(item)
	sw	$0,%lo(item)($2)
	lui	$2,%hi(none_dos_drop_pkt_cnt)
	sw	$0,%lo(none_dos_drop_pkt_cnt)($2)
	lui	$2,%hi(url_count)
	sb	$0,%lo(url_count)($2)
	lui	$4,%hi($LC35)
	lui	$6,%hi(proc_root)
	lui	$7,%hi(dos_proc_fops)
	lui	$2,%hi(proc_create_data)
	addiu	$4,$4,%lo($LC35)
	move	$5,$0
	addiu	$6,$6,%lo(proc_root)
	addiu	$7,$7,%lo(dos_proc_fops)
	addiu	$2,$2,%lo(proc_create_data)
	sw	$0,16($sp)
	jalr	$2
	lui	$17,%hi(dos_timer)

	lui	$3,%hi(res3)
	sw	$2,%lo(res3)($3)
	lui	$2,%hi(init_timer_key)
	move	$7,$0
	move	$6,$0
	addiu	$4,$17,%lo(dos_timer)
	move	$5,$0
	addiu	$2,$2,%lo(init_timer_key)
	jalr	$2
	addiu	$17,$17,%lo(dos_timer)

	lui	$3,%hi(jiffies)
	lw	$2,%lo(jiffies)($3)
	move	$4,$17
	lw	$5,%lo(jiffies)($3)
	lui	$16,%hi(_tcpDosScanBitmap)
	addiu	$2,$2,100
	sw	$2,8($17)
	lui	$2,%hi(dos_timer_fn)
	addiu	$2,$2,%lo(dos_timer_fn)
	addiu	$5,$5,100
	sw	$2,16($17)
	lui	$2,%hi(mod_timer)
	addiu	$2,$2,%lo(mod_timer)
	jalr	$2
	sw	$0,20($17)

	lui	$2,%hi(memset)
	addiu	$4,$16,%lo(_tcpDosScanBitmap)
	move	$5,$0
	addiu	$2,$2,%lo(memset)
	jalr	$2
	li	$6,64			# 0x40

	addiu	$3,$16,%lo(_tcpDosScanBitmap)
	li	$2,1			# 0x1
	sb	$2,63($3)
	sb	$2,58($3)
	sb	$2,41($3)
	sb	$2,40($3)
	sb	$2,33($3)
	sb	$2,32($3)
	sb	$2,9($3)
	sb	$2,8($3)
	sb	$2,3($3)
	sb	$2,%lo(_tcpDosScanBitmap)($16)
	lui	$2,%hi(filter_init_fastpath)
	addiu	$2,$2,%lo(filter_init_fastpath)
	jalr	$2
	nop

	lui	$2,%hi(igmp_delete_init_netlink)
	addiu	$2,$2,%lo(igmp_delete_init_netlink)
	jalr	$2
	nop

	move	$2,$0
	lw	$31,36($sp)
	lw	$17,32($sp)
	lw	$16,28($sp)
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
	.end	filter_init
	.size	filter_init, .-filter_init
	.section	.exit.text,"ax",@progbits
	.align	2
	.globl	filter_exit
	.set	nomips16
	.ent	filter_exit
	.type	filter_exit, @function
filter_exit:
	.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	sw	$16,16($sp)
	lui	$16,%hi(res3)
	lw	$5,%lo(res3)($16)
	beq	$5,$0,$L652
	lui	$4,%hi($LC35)

	lui	$2,%hi(remove_proc_entry)
	addiu	$2,$2,%lo(remove_proc_entry)
	jalr	$2
	addiu	$4,$4,%lo($LC35)

	sw	$0,%lo(res3)($16)
$L652:
	lui	$4,%hi(dos_timer)
	lui	$2,%hi(del_timer)
	addiu	$2,$2,%lo(del_timer)
	jalr	$2
	addiu	$4,$4,%lo(dos_timer)

	lui	$25,%hi(filter_exit_fastpath)
	lw	$31,20($sp)
	addiu	$25,$25,%lo(filter_exit_fastpath)
	lw	$16,16($sp)
	jr	$25
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	filter_exit
	.size	filter_exit, .-filter_exit
	.globl	fast_path_cusRspTCPEndAck_func
	.section	.bss,"aw",@nobits
	.align	2
	.type	fast_path_cusRspTCPEndAck_func, @object
	.size	fast_path_cusRspTCPEndAck_func, 4
fast_path_cusRspTCPEndAck_func:
	.space	4
	.globl	fast_path_cusRspTCPFinAck_func
	.align	2
	.type	fast_path_cusRspTCPFinAck_func, @object
	.size	fast_path_cusRspTCPFinAck_func, 4
fast_path_cusRspTCPFinAck_func:
	.space	4
	.globl	fast_path_cusRsp401_func
	.align	2
	.type	fast_path_cusRsp401_func, @object
	.size	fast_path_cusRsp401_func, 4
fast_path_cusRsp401_func:
	.space	4
	.globl	dos_proc_fops
	.data
	.align	2
	.type	dos_proc_fops, @object
	.size	dos_proc_fops, 108
dos_proc_fops:
	.space	4
	.word	seq_lseek
	.word	seq_read
	.word	dos_single_write
	.space	28
	.word	dos_single_open
	.space	4
	.word	single_release
	.space	52
	.globl	___strtok
	.section	.bss
	.align	2
	.type	___strtok, @object
	.size	___strtok, 4
___strtok:
	.space	4
	.globl	wan_ppp_dev
	.align	2
	.type	wan_ppp_dev, @object
	.size	wan_ppp_dev, 4
wan_ppp_dev:
	.space	4
	.globl	wan_dev
	.align	2
	.type	wan_dev, @object
	.size	wan_dev, 4
wan_dev:
	.space	4
	.globl	filter_table_proc_fops
	.data
	.align	2
	.type	filter_table_proc_fops, @object
	.size	filter_table_proc_fops, 108
filter_table_proc_fops:
	.space	4
	.word	seq_lseek
	.word	seq_read
	.word	filter_table_single_write
	.space	28
	.word	filter_table_single_open
	.space	4
	.word	single_release
	.space	52
	.globl	table_list_head
	.section	.bss
	.align	2
	.type	table_list_head, @object
	.size	table_list_head, 32
table_list_head:
	.space	32
	.globl	filter_tlb
	.data
	.align	2
	.type	filter_tlb, @object
	.size	filter_tlb, 40
filter_tlb:
	.word	0
	.word	0
	.word	1
	.word	rtl_ip_range_filter_fastpath
	.word	2
	.word	rtl_mac_filter_fastpath
	.word	3
	.word	rtl_url_filter_fastpath
	.word	4
	.word	rtl_schedule_filter_fastpath
	.local	get_info_from_usr_space
	.comm	get_info_from_usr_space,1024,4
	.local	log_enable
	.comm	log_enable,4,4
	.local	url_filter_mode
	.comm	url_filter_mode,4,4
	.local	filter_rule_num
	.comm	filter_rule_num,4,4
	.local	dos_flag
	.comm	dos_flag,80,4
	.local	ConnectedIp
	.comm	ConnectedIp,1024,4
	.local	ip_name0
	.comm	ip_name0,16,4
	.local	dos_pkt
	.comm	dos_pkt,40960,4
	.local	attack_daddr
	.comm	attack_daddr,108,4
	.local	attack_saddr
	.comm	attack_saddr,108,4
	.section	.rodata.str1.4
	.align	2
$LC36:
	.ascii	"NULL\000"
	.align	2
$LC37:
	.ascii	"PerSynFlood\000"
	.align	2
$LC38:
	.ascii	"PerFinFlood\000"
	.align	2
$LC39:
	.ascii	"PerUdpFlood\000"
	.align	2
$LC40:
	.ascii	"PerIcmpFlood\000"
	.align	2
$LC41:
	.ascii	"PerPingFlood\000"
	.align	2
$LC42:
	.ascii	"TcpUdpPortScan\000"
	.align	2
$LC43:
	.ascii	"IcmpSmurf\000"
	.align	2
$LC44:
	.ascii	"IpLand\000"
	.align	2
$LC45:
	.ascii	"IpSpoof\000"
	.align	2
$LC46:
	.ascii	"TearDrop\000"
	.align	2
$LC47:
	.ascii	"PingOfDeath\000"
	.align	2
$LC48:
	.ascii	"TcpScan\000"
	.align	2
$LC49:
	.ascii	"TcpSynWithData\000"
	.align	2
$LC50:
	.ascii	"UdpBomb\000"
	.align	2
$LC51:
	.ascii	"UdpEchoChargen\000"
	.align	2
$LC52:
	.ascii	"UdpFraggle\000"
	.align	2
$LC53:
	.ascii	"IcmpEchoStorm\000"
	.align	2
$LC54:
	.ascii	"UdpSnorkAttack\000"
	.align	2
$LC55:
	.ascii	"TcpInvalidFlags\000"
	.align	2
$LC56:
	.ascii	"TcpRstAttack\000"
	.align	2
$LC57:
	.ascii	"BcMcSrcIpAttack\000"
	.align	2
$LC58:
	.ascii	"ShortIpPkt\000"
	.align	2
$LC59:
	.ascii	"IcmpPingSweep\000"
	.align	2
$LC60:
	.ascii	"IcmpEchoWithoutReply\000"
	.align	2
$LC61:
	.ascii	"TcpInvalidOptions\000"
	.align	2
$LC62:
	.ascii	"LoopBackEchoChargen\000"
	.align	2
$LC63:
	.ascii	"MaxDosType\000"
	.rdata
	.align	2
	.type	rtl_dos_name, @object
	.size	rtl_dos_name, 112
rtl_dos_name:
	.word	$LC36
	.word	$LC37
	.word	$LC38
	.word	$LC39
	.word	$LC40
	.word	$LC41
	.word	$LC42
	.word	$LC43
	.word	$LC44
	.word	$LC45
	.word	$LC46
	.word	$LC47
	.word	$LC48
	.word	$LC49
	.word	$LC50
	.word	$LC51
	.word	$LC52
	.word	$LC53
	.word	$LC54
	.word	$LC55
	.word	$LC56
	.word	$LC57
	.word	$LC58
	.word	$LC59
	.word	$LC60
	.word	$LC61
	.word	$LC62
	.word	$LC63
	.local	ip_name1
	.comm	ip_name1,16,4
	.local	op_mode
	.comm	op_mode,1,1
	.local	lan_addr
	.comm	lan_addr,4,4
	.local	lan_mask
	.comm	lan_mask,4,4
	.section	.dram-l34-fwd,"aw",@progbits
	.align	2
	.type	item, @object
	.size	item, 4
item:
	.space	4
	.align	2
	.type	item_0, @object
	.size	item_0, 4
item_0:
	.space	4
	.local	item_backup
	.comm	item_backup,4,4
	.local	whole_syn_threshold
	.comm	whole_syn_threshold,4,4
	.local	whole_fin_threshold
	.comm	whole_fin_threshold,4,4
	.local	whole_udp_threshold
	.comm	whole_udp_threshold,4,4
	.local	whole_icmp_threshold
	.comm	whole_icmp_threshold,4,4
	.local	per_syn_threshold
	.comm	per_syn_threshold,4,4
	.local	per_fin_threshold
	.comm	per_fin_threshold,4,4
	.local	per_udp_threshold
	.comm	per_udp_threshold,4,4
	.local	per_icmp_threshold
	.comm	per_icmp_threshold,4,4
	.local	block_time
	.comm	block_time,4,4
	.local	log_info
	.comm	log_info,32,4
	.local	url_filter_flag
	.comm	url_filter_flag,4,4
	.local	res12
	.comm	res12,4,4
	.local	block_message
	.comm	block_message,4,4
	.local	url_cache
	.comm	url_cache,20,4
	.local	finStateClientPort
	.comm	finStateClientPort,2,2
	.local	finStateClientSeq
	.comm	finStateClientSeq,4,4
	.local	endStateClientPort
	.comm	endStateClientPort,2,2
	.local	endStateClientSeq
	.comm	endStateClientSeq,4,4
	.align	2
	.type	none_dos_drop_pkt_cnt, @object
	.size	none_dos_drop_pkt_cnt, 4
none_dos_drop_pkt_cnt:
	.space	4
	.local	cur_p_pkt
	.comm	cur_p_pkt,4,4
	.local	block
	.comm	block,4,4
	.local	LogFlag
	.comm	LogFlag,4,4
	.local	icmp_echo_request
	.comm	icmp_echo_request,4,4
	.local	_tcpDosScanBitmap
	.comm	_tcpDosScanBitmap,64,4
	.local	icmp_echo_request_time
	.comm	icmp_echo_request_time,4,4
	.type	url_count, @object
	.size	url_count, 1
url_count:
	.space	1
	.local	res3
	.comm	res3,4,4
	.local	dos_timer
	.comm	dos_timer,28,4
	.local	block_count
	.comm	block_count,4,4
	.ident	"GCC: (Realtek RSDK-4.6.4 Build 2002) 4.6.4"

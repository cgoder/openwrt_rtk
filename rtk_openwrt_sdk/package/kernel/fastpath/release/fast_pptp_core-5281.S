	.file	1 "fast_pptp_core.c"
	.section .mdebug.abi32
	.previous
	.gnu_attribute 4, 3
	.text
	.align	2
	.globl	pptp_conn_single_open
	.set	nomips16
	.ent	pptp_conn_single_open
	.type	pptp_conn_single_open, @function
pptp_conn_single_open:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	move	$4,$5
	lui	$25,%hi(single_open)
	lui	$5,%hi(pptpconn_read_proc)
	move	$6,$0
	addiu	$5,$5,%lo(pptpconn_read_proc)
	addiu	$25,$25,%lo(single_open)
	jr	$25
	nop

	.set	macro
	.set	reorder
	.end	pptp_conn_single_open
	.size	pptp_conn_single_open, .-pptp_conn_single_open
	.align	2
	.globl	fastpath_pptp_single_open
	.set	nomips16
	.ent	fastpath_pptp_single_open
	.type	fastpath_pptp_single_open, @function
fastpath_pptp_single_open:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	move	$4,$5
	lui	$25,%hi(single_open)
	lui	$5,%hi(ppfw_read_proc)
	move	$6,$0
	addiu	$5,$5,%lo(ppfw_read_proc)
	addiu	$25,$25,%lo(single_open)
	jr	$25
	nop

	.set	macro
	.set	reorder
	.end	fastpath_pptp_single_open
	.size	fastpath_pptp_single_open, .-fastpath_pptp_single_open
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
$LC0:
	.ascii	"%d\012\000"
	.text
	.align	2
	.globl	pptpconn_read_proc
	.set	nomips16
	.ent	pptpconn_read_proc
	.type	pptpconn_read_proc, @function
pptpconn_read_proc:
	.frame	$sp,24,$31		# vars= 0, regs= 1/0, args= 16, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	lui	$2,%hi(pptp_conn_check)
	lw	$6,%lo(pptp_conn_check)($2)
	lui	$5,%hi($LC0)
	lui	$2,%hi(seq_printf)
	addiu	$2,$2,%lo(seq_printf)
	jalr	$2
	addiu	$5,$5,%lo($LC0)

	move	$2,$0
	lw	$31,20($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	pptpconn_read_proc
	.size	pptpconn_read_proc, .-pptpconn_read_proc
	.align	2
	.globl	ppfw_read_proc
	.set	nomips16
	.ent	ppfw_read_proc
	.type	ppfw_read_proc, @function
ppfw_read_proc:
	.frame	$sp,24,$31		# vars= 0, regs= 1/0, args= 16, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	lui	$2,%hi(fast_pptp_fw)
	lw	$6,%lo(fast_pptp_fw)($2)
	lui	$5,%hi($LC0)
	lui	$2,%hi(seq_printf)
	addiu	$2,$2,%lo(seq_printf)
	jalr	$2
	addiu	$5,$5,%lo($LC0)

	move	$2,$0
	lw	$31,20($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	ppfw_read_proc
	.size	ppfw_read_proc, .-ppfw_read_proc
	.align	2
	.globl	sync_tx_pptp_gre_seqno
	.set	nomips16
	.ent	sync_tx_pptp_gre_seqno
	.type	sync_tx_pptp_gre_seqno, @function
sync_tx_pptp_gre_seqno:
	.frame	$sp,48,$31		# vars= 8, regs= 5/0, args= 16, gp= 0
	.mask	0x800f0000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-48
	sw	$31,44($sp)
	sw	$19,40($sp)
	sw	$18,36($sp)
	sw	$17,32($sp)
	sw	$16,28($sp)
	lui	$18,%hi(rtl_get_skb_data)
	addiu	$18,$18,%lo(rtl_get_skb_data)
	.set	noreorder
	.set	nomacro
	jalr	$18
	move	$19,$4
	.set	macro
	.set	reorder

	move	$16,$2
	lui	$2,%hi(fast_pptp_fw)
	lw	$2,%lo(fast_pptp_fw)($2)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L5
	lui	$2,%hi(arch_local_irq_save)
	.set	macro
	.set	reorder

	addiu	$2,$2,%lo(arch_local_irq_save)
	jalr	$2
	lbu	$3,23($16)
	move	$17,$2
	li	$2,47			# 0x2f
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L18
	move	$4,$17
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_get_skb_len)
	addiu	$2,$2,%lo(rtl_get_skb_len)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$19
	.set	macro
	.set	reorder

	sltu	$2,$2,35
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L18
	move	$4,$17
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jalr	$18
	move	$4,$19
	.set	macro
	.set	reorder

	lbu	$3,14($16)
	andi	$3,$3,0xf
	sll	$3,$3,2
	addiu	$3,$3,14
	addu	$2,$2,$3
	lbu	$3,3($2)
	lbu	$4,1($2)
	lbu	$5,2($2)
	sb	$3,17($sp)
	andi	$4,$4,0x7
	li	$3,1			# 0x1
	.set	noreorder
	.set	nomacro
	bne	$4,$3,$L7
	sb	$5,16($sp)
	.set	macro
	.set	reorder

	lhu	$4,16($sp)
	li	$3,34827			# 0x880b
	.set	noreorder
	.set	nomacro
	bne	$4,$3,$L18
	move	$4,$17
	.set	macro
	.set	reorder

	lbu	$3,0($2)
	andi	$3,$3,0x10
	.set	noreorder
	.set	nomacro
	beq	$3,$0,$L8
	move	$5,$0
	.set	macro
	.set	reorder

	lui	$3,%hi(pptpAccInfo)
	addiu	$3,$3,%lo(pptpAccInfo)
	lhu	$5,18($16)
	lhu	$4,46($3)
	.set	noreorder
	.set	nomacro
	beq	$5,$4,$L8
	li	$5,1			# 0x1
	.set	macro
	.set	reorder

	lhu	$5,6($2)
	lhu	$4,18($3)
	.set	noreorder
	.set	nomacro
	bne	$5,$4,$L8
	li	$5,1			# 0x1
	.set	macro
	.set	reorder

	lw	$5,32($3)
	lw	$4,30($16)
	.set	noreorder
	.set	nomacro
	bne	$5,$4,$L15
	move	$5,$0
	.set	macro
	.set	reorder

	lw	$6,8($2)
	lw	$4,36($3)
	sb	$6,51($3)
	srl	$8,$6,24
	srl	$7,$6,16
	sb	$8,48($3)
	srl	$6,$6,8
	sb	$7,49($3)
	sb	$6,50($3)
	addiu	$9,$4,1
	srl	$8,$4,24
	sw	$9,36($3)
	srl	$7,$4,16
	sw	$4,20($sp)
	srl	$6,$4,8
	sb	$8,8($2)
	sb	$7,9($2)
	sb	$6,10($2)
	.set	noreorder
	.set	nomacro
	j	$L8
	sb	$4,11($2)
	.set	macro
	.set	reorder

$L15:
	li	$5,1			# 0x1
$L8:
	lb	$3,1($2)
	.set	noreorder
	.set	nomacro
	bgez	$3,$L9
	lui	$3,%hi(pptpAccInfo)
	.set	macro
	.set	reorder

	addiu	$3,$3,%lo(pptpAccInfo)
	lhu	$6,6($2)
	lhu	$4,18($3)
	.set	noreorder
	.set	nomacro
	bne	$6,$4,$L18
	move	$4,$17
	.set	macro
	.set	reorder

	lw	$6,32($3)
	lw	$4,30($16)
	.set	noreorder
	.set	nomacro
	bne	$6,$4,$L18
	move	$4,$17
	.set	macro
	.set	reorder

	lw	$3,40($3)
	srl	$4,$3,24
	sw	$3,20($sp)
	srl	$6,$3,16
	sb	$4,12($2)
	srl	$4,$3,8
	sb	$6,13($2)
	sb	$4,14($2)
	sb	$3,15($2)
$L9:
	.set	noreorder
	.set	nomacro
	bne	$5,$0,$L7
	lui	$4,%hi(pptpAccInfo)
	.set	macro
	.set	reorder

	addiu	$8,$16,14
	addiu	$4,$4,%lo(pptpAccInfo)
	addiu	$2,$16,30
	lhu	$3,44($4)
	addiu	$3,$3,1
	andi	$3,$3,0xffff
	sh	$3,44($4)
	sh	$3,18($16)
	lw	$7,18($16)
	lw	$3,14($16)
	sh	$0,24($16)
	lw	$4,22($16)
	srl	$5,$3,22
	addu	$3,$7,$3
	andi	$5,$5,0x3c
	lw	$6,26($16)
	sltu	$7,$3,$7
	addu	$3,$3,$4
	addu	$5,$8,$5
	addu	$7,$3,$7
	sltu	$4,$7,$4
	addu	$7,$7,$6
	addu	$4,$7,$4
	sltu	$3,$4,$6
	addu	$3,$3,$4
$L10:
	lw	$4,0($2)
	addiu	$2,$2,4
	addu	$3,$4,$3
	sltu	$4,$3,$4
	.set	noreorder
	.set	nomacro
	bne	$5,$2,$L10
	addu	$3,$4,$3
	.set	macro
	.set	reorder

 #APP
 # 78 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/checksum.h" 1
		.set	push		# csum_fold
	.set	noat		
	sll	$1, $3, 16	
	addu	$3, $1		
	sltu	$1, $3, $1	
	srl	$3, $3, 16	
	addu	$3, $1		
	xori	$3, 0xffff	
	.set	pop
 # 0 "" 2
 #NO_APP
	sh	$3,24($16)
$L7:
	move	$4,$17
$L18:
	lui	$25,%hi(arch_local_irq_restore)
	lw	$31,44($sp)
	addiu	$25,$25,%lo(arch_local_irq_restore)
	lw	$19,40($sp)
	lw	$18,36($sp)
	lw	$17,32($sp)
	lw	$16,28($sp)
	.set	noreorder
	.set	nomacro
	jr	$25
	addiu	$sp,$sp,48
	.set	macro
	.set	reorder

$L5:
	lw	$31,44($sp)
	lw	$19,40($sp)
	lw	$18,36($sp)
	lw	$17,32($sp)
	lw	$16,28($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,48
	.set	macro
	.set	reorder

	.end	sync_tx_pptp_gre_seqno
	.size	sync_tx_pptp_gre_seqno, .-sync_tx_pptp_gre_seqno
	.align	2
	.set	nomips16
	.ent	get_fastpptp_lastxmit
	.type	get_fastpptp_lastxmit, @function
get_fastpptp_lastxmit:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	lui	$2,%hi(fast_pptp_fw)
	lw	$2,%lo(fast_pptp_fw)($2)
	beq	$2,$0,$L22
	nop

	lui	$2,%hi(pptpAccInfo)
	addiu	$3,$2,%lo(pptpAccInfo)
	lw	$4,4($3)
	li	$3,1			# 0x1
	bne	$4,$3,$L23
	nop

	lw	$2,%lo(pptpAccInfo)($2)
	j	$31
	nop

$L23:
	j	$31
	move	$2,$0

$L22:
	j	$31
	move	$2,$0

	.set	macro
	.set	reorder
	.end	get_fastpptp_lastxmit
	.size	get_fastpptp_lastxmit, .-get_fastpptp_lastxmit
	.align	2
	.set	nomips16
	.ent	set_pptp_device
	.type	set_pptp_device, @function
set_pptp_device:
	.frame	$sp,24,$31		# vars= 0, regs= 1/0, args= 16, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	lui	$2,%hi(fast_pptp_fw)
	lw	$2,%lo(fast_pptp_fw)($2)
	beq	$2,$0,$L24
	lui	$2,%hi(rtl_get_dev_by_name)

	addiu	$2,$2,%lo(rtl_get_dev_by_name)
	jalr	$2
	nop

	lui	$3,%hi(pptpAccInfo+56)
	sw	$2,%lo(pptpAccInfo+56)($3)
$L24:
	lw	$31,20($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	set_pptp_device
	.size	set_pptp_device, .-set_pptp_device
	.align	2
	.globl	Get_fast_pptp_fw
	.set	nomips16
	.ent	Get_fast_pptp_fw
	.type	Get_fast_pptp_fw, @function
Get_fast_pptp_fw:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	lui	$2,%hi(fast_pptp_fw)
	lw	$2,%lo(fast_pptp_fw)($2)
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	Get_fast_pptp_fw
	.size	Get_fast_pptp_fw, .-Get_fast_pptp_fw
	.align	2
	.globl	is_pptp_device
	.set	nomips16
	.ent	is_pptp_device
	.type	is_pptp_device, @function
is_pptp_device:
	.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	sw	$16,16($sp)
	lui	$2,%hi(pptpAccInfo+56)
	move	$16,$4
	lw	$4,%lo(pptpAccInfo+56)($2)
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L29
	lui	$2,%hi(rtl_get_ppp_dev_name)
	.set	macro
	.set	reorder

	addiu	$2,$2,%lo(rtl_get_ppp_dev_name)
	jalr	$2
 #APP
 # 80 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
	lbu	$3,($2)
1:	lbu	$1,($16)
	addiu	$2,1
	bne	$1,$3,2f
	addiu	$16,1
	bnez	$3,1b
	lbu	$3,($2)
	move	$3,$1
2:	subu	$3,$1
3:	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	j	$L28
	sltu	$2,$3,1
	.set	macro
	.set	reorder

$L29:
	move	$2,$0
$L28:
	lw	$31,20($sp)
	lw	$16,16($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,24
	.set	macro
	.set	reorder

	.end	is_pptp_device
	.size	is_pptp_device, .-is_pptp_device
	.align	2
	.globl	Check_GRE_rx_net_device
	.set	nomips16
	.ent	Check_GRE_rx_net_device
	.type	Check_GRE_rx_net_device, @function
Check_GRE_rx_net_device:
	.frame	$sp,40,$31		# vars= 0, regs= 6/0, args= 16, gp= 0
	.mask	0x801f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$20,32($sp)
	sw	$19,28($sp)
	sw	$18,24($sp)
	sw	$17,20($sp)
	sw	$16,16($sp)
	lui	$2,%hi(rtl_ip_hdr)
	addiu	$2,$2,%lo(rtl_ip_hdr)
	jalr	$2
	move	$16,$4

	lui	$19,%hi(pptpAccInfo)
	move	$17,$2
	lui	$2,%hi(rtl_get_skb_data)
	move	$4,$16
	addiu	$2,$2,%lo(rtl_get_skb_data)
	jalr	$2
	addiu	$19,$19,%lo(pptpAccInfo)

	lbu	$20,0($17)
	move	$18,$2
	lw	$17,8($19)
	beq	$17,$0,$L33
	andi	$20,$20,0xf

	lui	$2,%hi(rtl_get_skb_dev)
	addiu	$2,$2,%lo(rtl_get_skb_dev)
	jalr	$2
	move	$4,$16

	bne	$17,$2,$L33
	sll	$20,$20,2

	lhu	$2,30($19)
	addu	$18,$18,$20
	lhu	$3,6($18)
	xor	$2,$3,$2
	j	$L31
	sltu	$2,$2,1

$L33:
	move	$2,$0
$L31:
	lw	$31,36($sp)
	lw	$20,32($sp)
	lw	$19,28($sp)
	lw	$18,24($sp)
	lw	$17,20($sp)
	lw	$16,16($sp)
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
	.end	Check_GRE_rx_net_device
	.size	Check_GRE_rx_net_device, .-Check_GRE_rx_net_device
	.align	2
	.globl	fast_pptp_filter
	.set	nomips16
	.ent	fast_pptp_filter
	.type	fast_pptp_filter, @function
fast_pptp_filter:
	.frame	$sp,40,$31		# vars= 0, regs= 6/0, args= 16, gp= 0
	.mask	0x801f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$20,32($sp)
	sw	$19,28($sp)
	sw	$18,24($sp)
	sw	$17,20($sp)
	sw	$16,16($sp)
	lui	$2,%hi(rtl_ip_hdr)
	addiu	$2,$2,%lo(rtl_ip_hdr)
	jalr	$2
	move	$17,$4

	move	$16,$2
	lui	$2,%hi(rtl_get_skb_len)
	addiu	$2,$2,%lo(rtl_get_skb_len)
	jalr	$2
	move	$4,$17

	sltu	$2,$2,56
	bne	$2,$0,$L34
	nop

	lbu	$2,0($16)
	lbu	$3,9($16)
	andi	$4,$2,0xf
	li	$2,6			# 0x6
	bne	$3,$2,$L34
	sll	$4,$4,2

	li	$2,1723			# 0x6bb
	addu	$4,$16,$4
	lhu	$3,0($4)
	bne	$3,$2,$L34
	li	$3,1			# 0x1

	lw	$2,12($4)
	srl	$2,$2,28
	sll	$2,$2,2
	addu	$4,$4,$2
	lhu	$2,2($4)
	bne	$2,$3,$L34
	li	$5,8			# 0x8

	lhu	$3,8($4)
	bne	$3,$5,$L36
	nop

	lbu	$3,16($4)
	bne	$3,$2,$L34
	lui	$18,%hi(pptpAccInfo)

	addiu	$18,$18,%lo(pptpAccInfo)
	lw	$2,36($18)
	beq	$2,$0,$L46
	nop

	lw	$2,20($18)
	beq	$2,$0,$L46
	nop

	lw	$2,32($18)
	bne	$2,$0,$L44
	nop

$L46:
	lhu	$2,12($4)
	j	$L47
	sh	$2,18($18)

$L44:
	lhu	$3,18($18)
	lhu	$2,12($4)
	bne	$3,$2,$L34
	nop

	lhu	$5,30($18)
	lhu	$3,14($4)
	bne	$5,$3,$L34
	nop

	sh	$2,18($18)
$L47:
	lui	$3,%hi(pptp_tcp_finished)
	lhu	$2,14($4)
	li	$19,1			# 0x1
	sw	$19,%lo(pptp_tcp_finished)($3)
	move	$4,$17
	sh	$2,30($18)
	lui	$20,%hi(memcpy)
	lw	$2,16($16)
	addiu	$20,$20,%lo(memcpy)
	sw	$2,20($18)
	lw	$2,12($16)
	lui	$16,%hi(rtl_get_skb_data)
	sw	$19,36($18)
	sw	$2,32($18)
	lui	$2,%hi(rtl_get_skb_dev)
	addiu	$2,$2,%lo(rtl_get_skb_dev)
	jalr	$2
	addiu	$16,$16,%lo(rtl_get_skb_data)

	move	$4,$17
	jalr	$16
	sw	$2,8($18)

	lui	$4,%hi(pptpAccInfo+24)
	addiu	$5,$2,-8
	li	$6,6			# 0x6
	jalr	$20
	addiu	$4,$4,%lo(pptpAccInfo+24)

	jalr	$16
	move	$4,$17

	lui	$4,%hi(pptpAccInfo+12)
	addiu	$4,$4,%lo(pptpAccInfo+12)
	addiu	$5,$2,-14
	jalr	$20
	li	$6,6			# 0x6

	j	$L34
	sw	$19,4($18)

$L36:
	li	$2,13			# 0xd
	bne	$3,$2,$L34
	lui	$18,%hi(pptpAccInfo)

	addiu	$18,$18,%lo(pptpAccInfo)
	lw	$2,36($18)
	beq	$2,$0,$L48
	lui	$2,%hi(pptp_tcp_finished)

	lw	$2,20($18)
	beq	$2,$0,$L48
	lui	$2,%hi(pptp_tcp_finished)

	lw	$2,32($18)
	beq	$2,$0,$L48
	lui	$2,%hi(pptp_tcp_finished)

	lhu	$3,18($18)
	lhu	$2,12($4)
	bne	$3,$2,$L34
	lui	$2,%hi(pptp_tcp_finished)

$L48:
	sw	$0,%lo(pptp_tcp_finished)($2)
	sw	$0,4($18)
$L34:
	lw	$31,36($sp)
	lw	$20,32($sp)
	lw	$19,28($sp)
	lw	$18,24($sp)
	lw	$17,20($sp)
	lw	$16,16($sp)
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
	.end	fast_pptp_filter
	.size	fast_pptp_filter, .-fast_pptp_filter
	.align	2
	.globl	fast_pptp_to_lan
	.set	nomips16
	.ent	fast_pptp_to_lan
	.type	fast_pptp_to_lan, @function
fast_pptp_to_lan:
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
	lui	$2,%hi(rtl_get_skb_dev)
	lw	$18,0($4)
	lui	$17,%hi(pptpAccInfo)
	move	$16,$4
	addiu	$2,$2,%lo(rtl_get_skb_dev)
	move	$4,$18
	jalr	$2
	addiu	$17,$17,%lo(pptpAccInfo)

	lw	$3,8($17)
	bne	$3,$2,$L50
	move	$2,$0

	lui	$19,%hi(rtl_ip_hdr)
	addiu	$19,$19,%lo(rtl_ip_hdr)
	jalr	$19
	move	$4,$18

	lbu	$3,9($2)
	li	$2,47			# 0x2f
	bne	$3,$2,$L50
	move	$2,$0

	lui	$20,%hi(rtl_get_skb_len)
	addiu	$20,$20,%lo(rtl_get_skb_len)
	jalr	$20
	move	$4,$18

	sltu	$2,$2,20
	bne	$2,$0,$L50
	move	$2,$0

	move	$4,$18
	jalr	$19
	lui	$21,%hi(rtl_get_skb_data)

	addiu	$21,$21,%lo(rtl_get_skb_data)
	move	$19,$2
	jalr	$21
	move	$4,$18

	lbu	$3,0($19)
	andi	$3,$3,0xf
	sll	$3,$3,2
	addu	$2,$2,$3
	li	$3,1			# 0x1
	lbu	$4,1($2)
	andi	$4,$4,0x7
	bne	$4,$3,$L75
	li	$3,34827			# 0x880b

	lhu	$4,2($2)
	bne	$4,$3,$L75
	nop

	lhu	$4,6($2)
	lhu	$3,30($17)
	bne	$4,$3,$L75
	nop

	lbu	$3,0($2)
	andi	$3,$3,0x10
	beq	$3,$0,$L68
	nop

	lw	$3,8($2)
	li	$22,12			# 0xc
	j	$L51
	sw	$3,40($17)

$L68:
	li	$22,8			# 0x8
$L51:
	lb	$5,1($2)
	addiu	$4,$22,4
	lhu	$3,4($2)
	slt	$5,$5,0
	beq	$3,$0,$L75
	movn	$22,$4,$5

	addu	$2,$2,$22
	lbu	$3,0($2)
	bne	$3,$0,$L53
	li	$23,1			# 0x1

	j	$L54
	addiu	$2,$2,1

$L53:
	li	$4,255			# 0xff
	bne	$3,$4,$L54
	move	$23,$0

	lbu	$4,1($2)
	li	$3,3			# 0x3
	bne	$4,$3,$L71
	nop

	lbu	$3,2($2)
	beq	$3,$0,$L55
	nop

	addiu	$2,$2,2
	j	$L54
	li	$23,2			# 0x2

$L55:
	addiu	$2,$2,3
	li	$23,3			# 0x3
$L71:
$L54:
	lbu	$2,0($2)
	li	$3,33			# 0x21
	beq	$2,$3,$L56
	li	$3,253			# 0xfd

	bne	$2,$3,$L50
	move	$2,$0

	j	$L77
	nop

$L56:
	lbu	$2,0($19)
	addiu	$5,$23,1
	move	$4,$18
	move	$23,$0
	andi	$2,$2,0xf
	sll	$2,$2,2
	addu	$22,$2,$22
	lui	$2,%hi(skb_pull)
	addiu	$2,$2,%lo(skb_pull)
	jalr	$2
	addu	$5,$5,$22

	j	$L58
	nop

$L76:
	lui	$19,%hi(rtl_get_ppp_dev_priv)
	addiu	$19,$19,%lo(rtl_get_ppp_dev_priv)
	jalr	$19
	nop

	beq	$2,$0,$L75
	sll	$5,$fp,2

	lui	$2,%hi(skb_pull)
	addu	$5,$5,$22
	move	$4,$18
	addu	$5,$23,$5
	addiu	$2,$2,%lo(skb_pull)
	jalr	$2
	addiu	$5,$5,-1

	jalr	$21
	move	$4,$18

	li	$3,-3			# 0xfffffffffffffffd
	sb	$3,1($2)
	sb	$0,0($2)
	lw	$4,56($17)
	jalr	$19
	nop

	move	$5,$18
	move	$4,$2
	lui	$2,%hi(rtl_ppp_receive_nonmp_frame)
	addiu	$2,$2,%lo(rtl_ppp_receive_nonmp_frame)
	jalr	$2
	li	$6,1			# 0x1

	beq	$2,$0,$L73
	move	$18,$2

	sw	$2,0($16)
	li	$23,1			# 0x1
$L58:
	jalr	$21
	move	$4,$18

	andi	$16,$2,0x3
	beq	$16,$0,$L78
	lui	$2,%hi(rtl_skb_reset_network_header)

	lui	$2,%hi(rtl_skb_headroom)
	addiu	$2,$2,%lo(rtl_skb_headroom)
	jalr	$2
	move	$4,$18

	sltu	$2,$2,$16
	bne	$2,$0,$L78
	lui	$2,%hi(rtl_skb_reset_network_header)

	jalr	$21
	move	$4,$18

	move	$4,$18
	jalr	$21
	subu	$19,$2,$16

	move	$4,$18
	jalr	$20
	move	$21,$2

	move	$6,$2
	lui	$2,%hi(memmove)
	move	$4,$19
	addiu	$2,$2,%lo(memmove)
	jalr	$2
	move	$5,$21

	lui	$2,%hi(rtl_set_skb_data)
	move	$4,$18
	li	$6,1			# 0x1
	addiu	$2,$2,%lo(rtl_set_skb_data)
	jalr	$2
	move	$5,$16

	lui	$2,%hi(rtl_set_skb_tail)
	move	$4,$18
	li	$6,1			# 0x1
	addiu	$2,$2,%lo(rtl_set_skb_tail)
	jalr	$2
	move	$5,$16

	lui	$2,%hi(rtl_skb_reset_network_header)
$L78:
	addiu	$2,$2,%lo(rtl_skb_reset_network_header)
	jalr	$2
	move	$4,$18

	lui	$2,%hi(rtl_skb_reset_transport_header)
	addiu	$2,$2,%lo(rtl_skb_reset_transport_header)
	jalr	$2
	move	$4,$18

	lw	$4,56($17)
	beq	$4,$0,$L50
	move	$2,$0

	bne	$23,$0,$L60
	lui	$16,%hi(rtl_get_ppp_dev_priv)

	addiu	$16,$16,%lo(rtl_get_ppp_dev_priv)
	jalr	$16
	nop

	beq	$2,$0,$L60
	nop

	lw	$4,56($17)
	jalr	$16
	nop

	move	$4,$18
	jalr	$20
	move	$16,$2

	addiu	$6,$2,-2
	lui	$2,%hi(rtl_inc_ppp_stats)
	move	$4,$16
	addiu	$2,$2,%lo(rtl_inc_ppp_stats)
	jalr	$2
	move	$5,$0

$L60:
	lw	$5,56($17)
	lui	$2,%hi(rtl_set_skb_dev)
	addiu	$2,$2,%lo(rtl_set_skb_dev)
	jalr	$2
	move	$4,$18

	j	$L50
	li	$2,1			# 0x1

$L73:
	j	$L50
	li	$2,-2			# 0xfffffffffffffffe

$L75:
	move	$2,$0
$L50:
	lw	$31,52($sp)
	lw	$fp,48($sp)
	lw	$23,44($sp)
	lw	$22,40($sp)
	lw	$21,36($sp)
	lw	$20,32($sp)
	lw	$19,28($sp)
	lw	$18,24($sp)
	lw	$17,20($sp)
	lw	$16,16($sp)
	j	$31
	addiu	$sp,$sp,56

$L77:
	lbu	$fp,0($19)
	lw	$4,56($17)
	bne	$4,$0,$L76
	andi	$fp,$fp,0xf

	j	$L50
	move	$2,$0

	.set	macro
	.set	reorder
	.end	fast_pptp_to_lan
	.size	fast_pptp_to_lan, .-fast_pptp_to_lan
	.section	.rodata.str1.4
	.align	2
$LC1:
	.ascii	"ppp0\000"
	.align	2
$LC2:
	.ascii	"RTL\000"
	.align	2
$LC3:
	.ascii	"pptpInfo.ppp0_dev == NULL\012\000"
	.align	2
$LC4:
	.ascii	"pptpInfo.ppp0_dev->priv == NULL\012\000"
	.text
	.align	2
	.globl	fast_pptp_to_wan
	.set	nomips16
	.ent	fast_pptp_to_wan
	.type	fast_pptp_to_wan, @function
fast_pptp_to_wan:
	.frame	$sp,88,$31		# vars= 40, regs= 7/0, args= 16, gp= 0
	.mask	0x803f0000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-88
	sw	$31,84($sp)
	sw	$21,80($sp)
	sw	$20,76($sp)
	sw	$19,72($sp)
	sw	$18,68($sp)
	sw	$17,64($sp)
	sw	$16,60($sp)
	lui	$18,%hi(rtl_ip_hdr)
	addiu	$18,$18,%lo(rtl_ip_hdr)
	.set	noreorder
	.set	nomacro
	jalr	$18
	move	$19,$4
	.set	macro
	.set	reorder

	move	$4,$19
	lw	$16,12($2)
	li	$2,-16777216			# 0xffffffffff000000
	.set	noreorder
	.set	nomacro
	jalr	$18
	and	$16,$16,$2
	.set	macro
	.set	reorder

	lw	$17,12($2)
	.set	noreorder
	.set	nomacro
	jalr	$18
	move	$4,$19
	.set	macro
	.set	reorder

	lw	$3,12($2)
	li	$2,167772160			# 0xa000000
	.set	noreorder
	.set	nomacro
	bne	$16,$2,$L80
	li	$2,16711680			# 0xff0000
	.set	macro
	.set	reorder

	and	$17,$17,$2
	li	$2,4194304			# 0x400000
	.set	noreorder
	.set	nomacro
	bne	$17,$2,$L80
	andi	$3,$3,0xff00
	.set	macro
	.set	reorder

	li	$2,16384			# 0x4000
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L98
	lui	$20,%hi(pptpAccInfo)
	.set	macro
	.set	reorder

	lui	$2,%hi(pptp_conn_check)
	lw	$3,%lo(pptp_conn_check)($2)
	li	$2,3			# 0x3
	.set	noreorder
	.set	nomacro
	beq	$3,$2,$L81
	move	$2,$0
	.set	macro
	.set	reorder

$L80:
	lui	$20,%hi(pptpAccInfo)
$L98:
	addiu	$17,$20,%lo(pptpAccInfo)
	lw	$4,56($17)
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L96
	lui	$16,%hi(rtl_get_ppp_dev_name)
	.set	macro
	.set	reorder

	addiu	$16,$16,%lo(rtl_get_ppp_dev_name)
	jalr	$16
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L81
	move	$2,$0
	.set	macro
	.set	reorder

	lw	$4,56($17)
	jalr	$16
	lui	$3,%hi($LC1)
	addiu	$3,$3,%lo($LC1)
 #APP
 # 80 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/linux-3.10.49/arch/rlx/include/asm/string.h" 1
	.set	noreorder
	.set	noat
	lbu	$4,($2)
1:	lbu	$1,($3)
	addiu	$2,1
	bne	$1,$4,2f
	addiu	$3,1
	bnez	$4,1b
	lbu	$4,($2)
	move	$4,$1
2:	subu	$4,$1
3:	.set	at
	.set	reorder
 # 0 "" 2
 #NO_APP
	.set	noreorder
	.set	nomacro
	bne	$4,$0,$L81
	move	$2,$0
	.set	macro
	.set	reorder

	lw	$2,4($17)
	beq	$2,$0,$L82
	lw	$4,56($17)
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L83
	lui	$16,%hi(rtl_get_ppp_dev_priv)
	.set	macro
	.set	reorder

	addiu	$16,$16,%lo(rtl_get_ppp_dev_priv)
	jalr	$16
	beq	$2,$0,$L82
	lw	$4,56($17)
	jalr	$16
	move	$4,$2
	move	$16,$2
	lui	$2,%hi(rtl_ppp_vj_check)
	addiu	$2,$2,%lo(rtl_ppp_vj_check)
	jalr	$2
	li	$3,1			# 0x1
	.set	noreorder
	.set	nomacro
	beq	$2,$3,$L81
	move	$2,$0
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jalr	$18
	move	$4,$19
	.set	macro
	.set	reorder

	lui	$18,%hi(rtl_get_ppp_xmit_pending)
	addiu	$18,$18,%lo(rtl_get_ppp_xmit_pending)
	lbu	$21,1($2)
	.set	noreorder
	.set	nomacro
	jalr	$18
	move	$4,$16
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L81
	move	$2,$0
	.set	macro
	.set	reorder

	lui	$5,%hi($LC2)
	lui	$2,%hi(rtl_set_skb_cb)
	addiu	$5,$5,%lo($LC2)
	li	$6,3			# 0x3
	addiu	$2,$2,%lo(rtl_set_skb_cb)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$19
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_ppp_start_xmit)
	lw	$5,56($17)
	addiu	$2,$2,%lo(rtl_ppp_start_xmit)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$19
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jalr	$18
	move	$4,$16
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L81
	li	$2,1			# 0x1
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jalr	$18
	move	$4,$16
	.set	macro
	.set	reorder

	move	$4,$16
	move	$18,$2
	lui	$2,%hi(rtl_set_ppp_xmit_pending)
	addiu	$2,$2,%lo(rtl_set_ppp_xmit_pending)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$5,$0
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_skb_headroom)
	addiu	$2,$2,%lo(rtl_skb_headroom)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	sltu	$2,$2,50
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L99
	lui	$2,%hi(skb_realloc_headroom)
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_skb_cloned)
	addiu	$2,$2,%lo(rtl_skb_cloned)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L99
	lui	$2,%hi(skb_realloc_headroom)
	.set	macro
	.set	reorder

	lui	$2,%hi(rtl_skb_shared)
	addiu	$2,$2,%lo(rtl_skb_shared)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L100
	lui	$2,%hi(skb_push)
	.set	macro
	.set	reorder

	lui	$2,%hi(skb_realloc_headroom)
$L99:
	move	$4,$18
	addiu	$2,$2,%lo(skb_realloc_headroom)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$5,50			# 0x32
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L86
	move	$4,$18
	.set	macro
	.set	reorder

	lui	$2,%hi(consume_skb)
	addiu	$2,$2,%lo(consume_skb)
	jalr	$2
	.set	noreorder
	.set	nomacro
	j	$L81
	li	$2,1			# 0x1
	.set	macro
	.set	reorder

$L86:
	move	$18,$2
	lui	$2,%hi(consume_skb)
	addiu	$2,$2,%lo(consume_skb)
	jalr	$2
	lui	$2,%hi(skb_push)
$L100:
	li	$5,50			# 0x32
	addiu	$2,$2,%lo(skb_push)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	lui	$19,%hi(memcpy)
	lui	$5,%hi(pptpAccInfo+24)
	move	$4,$2
	addiu	$5,$5,%lo(pptpAccInfo+24)
	li	$6,6			# 0x6
	addiu	$19,$19,%lo(memcpy)
	.set	noreorder
	.set	nomacro
	jalr	$19
	move	$16,$2
	.set	macro
	.set	reorder

	lui	$5,%hi(pptpAccInfo+12)
	addiu	$4,$16,6
	li	$6,6			# 0x6
	.set	noreorder
	.set	nomacro
	jalr	$19
	addiu	$5,$5,%lo(pptpAccInfo+12)
	.set	macro
	.set	reorder

	li	$2,8			# 0x8
	sb	$2,12($16)
	li	$2,268369920			# 0xfff0000
	sb	$0,13($16)
	ori	$2,$2,0xffff
	lw	$6,32($sp)
	li	$4,-251723776			# 0xfffffffff0ff0000
	ori	$4,$4,0xffff
	lw	$3,32($17)
	and	$6,$6,$2
	li	$2,1073741824			# 0x40000000
	or	$6,$6,$2
	lw	$2,20($17)
	and	$6,$6,$4
	li	$4,83886080			# 0x5000000
	or	$6,$6,$4
	sw	$2,44($sp)
	sw	$6,32($sp)
	li	$2,64			# 0x40
	li	$6,16384			# 0x4000
	move	$5,$0
	sh	$6,38($sp)
	li	$6,47			# 0x2f
	sb	$2,40($sp)
	lui	$2,%hi(rtl_set_skb_ip_summed)
	sb	$6,41($sp)
	move	$4,$18
	sw	$3,48($sp)
	addiu	$2,$2,%lo(rtl_set_skb_ip_summed)
	sb	$21,33($sp)
	.set	noreorder
	.set	nomacro
	jalr	$2
	lui	$16,%hi(rtl_get_skb_len)
	.set	macro
	.set	reorder

	addiu	$16,$16,%lo(rtl_get_skb_len)
	.set	noreorder
	.set	nomacro
	jalr	$16
	move	$4,$18
	.set	macro
	.set	reorder

	addiu	$9,$sp,32
	lhu	$5,44($17)
	addiu	$2,$2,-14
	sh	$2,34($sp)
	addiu	$3,$sp,48
	addiu	$5,$5,1
	andi	$5,$5,0xffff
	lw	$2,32($sp)
	sh	$5,36($sp)
	lw	$8,36($sp)
	srl	$6,$2,22
	sh	$0,42($sp)
	andi	$6,$6,0x3c
	lw	$4,40($sp)
	addu	$2,$8,$2
	lw	$7,44($sp)
	sltu	$8,$2,$8
	addu	$2,$2,$4
	addu	$6,$9,$6
	addu	$8,$2,$8
	sltu	$4,$8,$4
	addu	$8,$8,$7
	addu	$4,$8,$4
	sltu	$2,$4,$7
	sh	$5,44($17)
	addu	$2,$2,$4
$L87:
	lw	$4,0($3)
	addiu	$3,$3,4
	addu	$2,$4,$2
	sltu	$4,$2,$4
	.set	noreorder
	.set	nomacro
	bne	$6,$3,$L87
	addu	$2,$4,$2
	.set	macro
	.set	reorder

	lui	$21,%hi(rtl_get_skb_data)
	move	$4,$18
	addiu	$21,$21,%lo(rtl_get_skb_data)
	sh	$5,46($17)
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
	jalr	$21
	sh	$2,42($sp)
	.set	macro
	.set	reorder

	addiu	$5,$sp,32
	li	$6,20			# 0x14
	.set	noreorder
	.set	nomacro
	jalr	$19
	addiu	$4,$2,14
	.set	macro
	.set	reorder

	li	$2,48			# 0x30
	sb	$2,16($sp)
	li	$2,-127			# 0xffffffffffffff81
	sb	$2,17($sp)
	li	$2,-30709			# 0xffffffffffff880b
	move	$4,$18
	.set	noreorder
	.set	nomacro
	jalr	$16
	sh	$2,18($sp)
	.set	macro
	.set	reorder

	move	$4,$18
	lw	$3,36($17)
	addiu	$2,$2,-50
	lhu	$7,18($17)
	lw	$5,40($17)
	addiu	$6,$3,1
	sh	$7,22($sp)
	sw	$3,24($sp)
	sw	$6,36($17)
	sw	$5,28($sp)
	.set	noreorder
	.set	nomacro
	jalr	$21
	sh	$2,20($sp)
	.set	macro
	.set	reorder

	li	$6,16			# 0x10
	addiu	$4,$2,34
	.set	noreorder
	.set	nomacro
	jalr	$19
	addiu	$5,$sp,16
	.set	macro
	.set	reorder

	lui	$2,%hi(jiffies)
	lw	$2,%lo(jiffies)($2)
	lw	$5,8($17)
	sw	$2,%lo(pptpAccInfo)($20)
	lui	$2,%hi(rtl_set_skb_dev)
	addiu	$2,$2,%lo(rtl_set_skb_dev)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	lui	$2,%hi(dev_queue_xmit)
	addiu	$2,$2,%lo(dev_queue_xmit)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$18
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L81
	li	$2,1			# 0x1
	.set	macro
	.set	reorder

$L82:
	lw	$4,56($17)
	bne	$4,$0,$L88
$L83:
	lui	$4,%hi($LC3)
	lui	$2,%hi(printk)
	addiu	$2,$2,%lo(printk)
	.set	noreorder
	.set	nomacro
	jalr	$2
	addiu	$4,$4,%lo($LC3)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L81
	move	$2,$0
	.set	macro
	.set	reorder

$L88:
	lui	$2,%hi(rtl_get_ppp_dev_priv)
	addiu	$2,$2,%lo(rtl_get_ppp_dev_priv)
	jalr	$2
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L96
	lui	$4,%hi($LC4)
	.set	macro
	.set	reorder

	lui	$2,%hi(printk)
	addiu	$2,$2,%lo(printk)
	.set	noreorder
	.set	nomacro
	jalr	$2
	addiu	$4,$4,%lo($LC4)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L81
	move	$2,$0
	.set	macro
	.set	reorder

$L96:
	move	$2,$0
$L81:
	lw	$31,84($sp)
	lw	$21,80($sp)
	lw	$20,76($sp)
	lw	$19,72($sp)
	lw	$18,68($sp)
	lw	$17,64($sp)
	lw	$16,60($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,88
	.set	macro
	.set	reorder

	.end	fast_pptp_to_wan
	.size	fast_pptp_to_wan, .-fast_pptp_to_wan
	.align	2
	.globl	fast_pptp_sync_rx_seq
	.set	nomips16
	.ent	fast_pptp_sync_rx_seq
	.type	fast_pptp_sync_rx_seq, @function
fast_pptp_sync_rx_seq:
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

	li	$4,1			# 0x1
	lbu	$3,21($2)
	andi	$5,$3,0x7
	bne	$5,$4,$L101
	li	$4,34827			# 0x880b

	lhu	$5,22($2)
	bne	$5,$4,$L101
	nop

	lbu	$4,20($2)
	andi	$4,$4,0x10
	beq	$4,$0,$L104
	sll	$3,$3,24

	lui	$3,%hi(pptpAccInfo)
	addiu	$3,$3,%lo(pptpAccInfo)
	lw	$4,52($3)
	addiu	$5,$4,1
	sw	$4,28($2)
	sw	$5,52($3)
	lbu	$3,21($2)
	sll	$3,$3,24
$L104:
	sra	$3,$3,24
	bgez	$3,$L101
	lui	$3,%hi(pptpAccInfo+48)

	lw	$3,%lo(pptpAccInfo+48)($3)
	sw	$3,32($2)
$L101:
	lw	$31,20($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	fast_pptp_sync_rx_seq
	.size	fast_pptp_sync_rx_seq, .-fast_pptp_sync_rx_seq
	.align	2
	.globl	pptpconn_write_proc
	.set	nomips16
	.ent	pptpconn_write_proc
	.type	pptpconn_write_proc, @function
pptpconn_write_proc:
	.frame	$sp,208,$31		# vars= 200, regs= 1/0, args= 0, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-208
	sw	$31,204($sp)
	sltu	$4,$6,2
	bne	$4,$0,$L106
	.set	noreorder
	.set	nomacro
	beq	$5,$0,$L106
	addu	$2,$5,$6
	.set	macro
	.set	reorder

	or	$4,$5,$6
	or	$2,$4,$2
	lw	$4,24($28)
	and	$2,$2,$4
	bne	$2,$0,$L106
	move	$4,$sp
 #APP
 # 916 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/fastpath-0.1/fast_pptp_core.c" 1
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
	beq	$6,$0,$L109
	move	$2,$0
	.set	macro
	.set	reorder

	j	$L106
$L108:
	.set	noreorder
	.set	nomacro
	j	$L107
	addu	$2,$6,$4
	.set	macro
	.set	reorder

$L109:
	move	$3,$sp
$L107:
	lb	$4,0($3)
	sll	$7,$2,1
	sll	$6,$2,3
	addiu	$3,$3,1
	addiu	$5,$4,-48
	addu	$6,$7,$6
	andi	$5,$5,0x00ff
	sltu	$5,$5,10
	.set	noreorder
	.set	nomacro
	bne	$5,$0,$L108
	addiu	$6,$6,-48
	.set	macro
	.set	reorder

	lui	$3,%hi(pptp_conn_check)
	sw	$2,%lo(pptp_conn_check)($3)
$L106:
	lw	$31,204($sp)
	li	$2,-14			# 0xfffffffffffffff2
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,208
	.set	macro
	.set	reorder

	.end	pptpconn_write_proc
	.size	pptpconn_write_proc, .-pptpconn_write_proc
	.align	2
	.set	nomips16
	.ent	pptp_conn_single_write
	.type	pptp_conn_single_write, @function
pptp_conn_single_write:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	lui	$25,%hi(pptpconn_write_proc)
	addiu	$25,$25,%lo(pptpconn_write_proc)
	jr	$25
	nop

	.set	macro
	.set	reorder
	.end	pptp_conn_single_write
	.size	pptp_conn_single_write, .-pptp_conn_single_write
	.align	2
	.globl	ppfw_write_proc
	.set	nomips16
	.ent	ppfw_write_proc
	.type	ppfw_write_proc, @function
ppfw_write_proc:
	.frame	$sp,32,$31		# vars= 0, regs= 4/0, args= 16, gp= 0
	.mask	0x80070000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$18,24($sp)
	sw	$17,20($sp)
	sw	$16,16($sp)
	sltu	$2,$6,2
	move	$18,$6
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L118
	move	$16,$5
	.set	macro
	.set	reorder

	lui	$2,%hi(__kmalloc)
	addiu	$4,$6,32
	addiu	$2,$2,%lo(__kmalloc)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$5,32			# 0x20
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L118
	move	$17,$2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$16,$0,$L113
	or	$3,$16,$18
	.set	macro
	.set	reorder

	addu	$2,$16,$18
	or	$2,$3,$2
	lw	$3,24($28)
	and	$2,$2,$3
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L113
	move	$4,$17
	.set	macro
	.set	reorder

	move	$5,$16
	move	$6,$18
 #APP
 # 942 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips-rlx5281-linux/linux-realtek_rtl8881a/fastpath-0.1/fast_pptp_core.c" 1
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
	beq	$6,$0,$L119
	move	$3,$17
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L121
	lui	$2,%hi(kfree)
	.set	macro
	.set	reorder

$L115:
	.set	noreorder
	.set	nomacro
	j	$L114
	addu	$2,$6,$4
	.set	macro
	.set	reorder

$L119:
	move	$2,$0
$L114:
	lb	$4,0($3)
	sll	$7,$2,1
	sll	$6,$2,3
	addiu	$3,$3,1
	addiu	$5,$4,-48
	addu	$6,$7,$6
	andi	$5,$5,0x00ff
	sltu	$5,$5,10
	.set	noreorder
	.set	nomacro
	bne	$5,$0,$L115
	addiu	$6,$6,-48
	.set	macro
	.set	reorder

	lui	$16,%hi(fast_pptp_fw)
	lui	$4,%hi(pptpAccInfo)
	sw	$2,%lo(fast_pptp_fw)($16)
	lui	$2,%hi(memset)
	addiu	$4,$4,%lo(pptpAccInfo)
	addiu	$2,$2,%lo(memset)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$6,64			# 0x40
	.set	macro
	.set	reorder

	lw	$2,%lo(fast_pptp_fw)($16)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L120
	lui	$3,%hi(sync_tx_pptp_gre_seqno)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L116
	addiu	$3,$3,%lo(sync_tx_pptp_gre_seqno)
	.set	macro
	.set	reorder

$L120:
	move	$3,$0
$L116:
	lui	$2,%hi(sync_tx_pptp_gre_seqno_hook)
	sw	$3,%lo(sync_tx_pptp_gre_seqno_hook)($2)
	lui	$2,%hi(kfree)
	addiu	$2,$2,%lo(kfree)
	.set	noreorder
	.set	nomacro
	jalr	$2
	move	$4,$17
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L122
	move	$2,$18
	.set	macro
	.set	reorder

$L113:
	lui	$2,%hi(kfree)
$L121:
	move	$4,$17
	addiu	$2,$2,%lo(kfree)
	.set	noreorder
	.set	nomacro
	jalr	$2
	li	$18,-14			# 0xfffffffffffffff2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L122
	move	$2,$18
	.set	macro
	.set	reorder

$L118:
	li	$18,-14			# 0xfffffffffffffff2
	move	$2,$18
$L122:
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

	.end	ppfw_write_proc
	.size	ppfw_write_proc, .-ppfw_write_proc
	.align	2
	.set	nomips16
	.ent	fastpath_pptp_single_write
	.type	fastpath_pptp_single_write, @function
fastpath_pptp_single_write:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	lui	$25,%hi(ppfw_write_proc)
	addiu	$25,$25,%lo(ppfw_write_proc)
	jr	$25
	nop

	.set	macro
	.set	reorder
	.end	fastpath_pptp_single_write
	.size	fastpath_pptp_single_write, .-fastpath_pptp_single_write
	.section	.rodata.str1.4
	.align	2
$LC5:
	.ascii	"fast_pptp\000"
	.align	2
$LC6:
	.ascii	"pptp_conn_ck\000"
	.section	.init.text,"ax",@progbits
	.align	2
	.globl	fast_pptp_init
	.set	nomips16
	.ent	fast_pptp_init
	.type	fast_pptp_init, @function
fast_pptp_init:
	.frame	$sp,40,$31		# vars= 0, regs= 3/0, args= 24, gp= 0
	.mask	0x80030000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$17,32($sp)
	sw	$16,28($sp)
	lui	$3,%hi(set_pptp_device)
	addiu	$3,$3,%lo(set_pptp_device)
	lui	$2,%hi(set_pptp_device_fphook)
	lui	$16,%hi(proc_root)
	lui	$4,%hi($LC5)
	sw	$3,%lo(set_pptp_device_fphook)($2)
	lui	$7,%hi(fastpath_pptp_proc_fops)
	lui	$17,%hi(proc_create_data)
	lui	$3,%hi(get_fastpptp_lastxmit)
	addiu	$6,$16,%lo(proc_root)
	addiu	$17,$17,%lo(proc_create_data)
	addiu	$3,$3,%lo(get_fastpptp_lastxmit)
	addiu	$4,$4,%lo($LC5)
	move	$5,$0
	addiu	$7,$7,%lo(fastpath_pptp_proc_fops)
	lui	$2,%hi(get_fastpptp_lastxmit_fphook)
	sw	$3,%lo(get_fastpptp_lastxmit_fphook)($2)
	jalr	$17
	sw	$0,16($sp)

	lui	$4,%hi($LC6)
	lui	$7,%hi(pptp_conn_proc_fops)
	addiu	$6,$16,%lo(proc_root)
	addiu	$7,$7,%lo(pptp_conn_proc_fops)
	lui	$3,%hi(res1)
	addiu	$4,$4,%lo($LC6)
	move	$5,$0
	sw	$2,%lo(res1)($3)
	jalr	$17
	sw	$0,16($sp)

	lui	$3,%hi(res_check_pptp)
	sw	$2,%lo(res_check_pptp)($3)
	lui	$4,%hi(pptpAccInfo)
	lui	$2,%hi(memset)
	addiu	$4,$4,%lo(pptpAccInfo)
	move	$5,$0
	addiu	$2,$2,%lo(memset)
	jalr	$2
	li	$6,64			# 0x40

	move	$2,$0
	lw	$31,36($sp)
	lw	$17,32($sp)
	lw	$16,28($sp)
	j	$31
	addiu	$sp,$sp,40

	.set	macro
	.set	reorder
	.end	fast_pptp_init
	.size	fast_pptp_init, .-fast_pptp_init
	.section	.exit.text,"ax",@progbits
	.align	2
	.globl	fast_pptp_exit
	.set	nomips16
	.ent	fast_pptp_exit
	.type	fast_pptp_exit, @function
fast_pptp_exit:
	.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	sw	$16,16($sp)
	lui	$3,%hi(set_pptp_device_fphook)
	lui	$16,%hi(res1)
	sw	$0,%lo(set_pptp_device_fphook)($3)
	lui	$3,%hi(get_fastpptp_lastxmit_fphook)
	lw	$2,%lo(res1)($16)
	sw	$0,%lo(get_fastpptp_lastxmit_fphook)($3)
	lui	$3,%hi(fast_pptp_fw)
	beq	$2,$0,$L126
	sw	$0,%lo(fast_pptp_fw)($3)

	lui	$4,%hi($LC5)
	lui	$5,%hi(proc_root)
	lui	$2,%hi(remove_proc_entry)
	addiu	$4,$4,%lo($LC5)
	addiu	$2,$2,%lo(remove_proc_entry)
	jalr	$2
	addiu	$5,$5,%lo(proc_root)

	sw	$0,%lo(res1)($16)
$L126:
	lui	$16,%hi(res_check_pptp)
	lw	$2,%lo(res_check_pptp)($16)
	beq	$2,$0,$L125
	lui	$4,%hi($LC6)

	lui	$5,%hi(proc_root)
	lui	$2,%hi(remove_proc_entry)
	addiu	$4,$4,%lo($LC6)
	addiu	$2,$2,%lo(remove_proc_entry)
	jalr	$2
	addiu	$5,$5,%lo(proc_root)

	sw	$0,%lo(res_check_pptp)($16)
$L125:
	lw	$31,20($sp)
	lw	$16,16($sp)
	j	$31
	addiu	$sp,$sp,24

	.set	macro
	.set	reorder
	.end	fast_pptp_exit
	.size	fast_pptp_exit, .-fast_pptp_exit
	.globl	pptp_conn_proc_fops
	.data
	.align	2
	.type	pptp_conn_proc_fops, @object
	.size	pptp_conn_proc_fops, 108
pptp_conn_proc_fops:
	.space	4
	.word	seq_lseek
	.word	seq_read
	.word	pptp_conn_single_write
	.space	28
	.word	pptp_conn_single_open
	.space	4
	.word	single_release
	.space	52
	.globl	fastpath_pptp_proc_fops
	.align	2
	.type	fastpath_pptp_proc_fops, @object
	.size	fastpath_pptp_proc_fops, 108
fastpath_pptp_proc_fops:
	.space	4
	.word	seq_lseek
	.word	seq_read
	.word	fastpath_pptp_single_write
	.space	28
	.word	fastpath_pptp_single_open
	.space	4
	.word	single_release
	.space	52
	.globl	pptp_tcp_finished
	.section	.bss,"aw",@nobits
	.align	2
	.type	pptp_tcp_finished, @object
	.size	pptp_tcp_finished, 4
pptp_tcp_finished:
	.space	4
	.local	pptpAccInfo
	.comm	pptpAccInfo,64,4
	.local	pptp_conn_check
	.comm	pptp_conn_check,4,4
	.local	res1
	.comm	res1,4,4
	.local	res_check_pptp
	.comm	res_check_pptp,4,4
	.ident	"GCC: (Realtek RSDK-4.6.4 Build 2002) 4.6.4"

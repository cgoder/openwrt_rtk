	.section .mdebug.abi32
	.previous
	.gnu_attribute 4, 3
	.text
$Ltext0:
	.cfi_sections	.debug_frame
	.align	2
	.globl	sync_tx_pptp_gre_seqno
$LFB3076 = .
	.file 1 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/fastpath-0.1/fast_pptp_core.c"
	.loc 1 801 0
	.cfi_startproc
	.set	nomips16
	.ent	sync_tx_pptp_gre_seqno
	.type	sync_tx_pptp_gre_seqno, @function
sync_tx_pptp_gre_seqno:
	.frame	$sp,40,$31		# vars= 8, regs= 4/0, args= 16, gp= 0
	.mask	0x80070000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-40
	.cfi_def_cfa_offset 40
	sw	$18,32($sp)
	sw	$31,36($sp)
	sw	$17,28($sp)
	sw	$16,24($sp)
	.cfi_offset 18, -8
	.cfi_offset 31, -4
	.cfi_offset 17, -12
	.cfi_offset 16, -16
	.loc 1 802 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_data
	move	$18,$4
	.set	macro
	.set	reorder

	.loc 1 808 0
	lui	$3,%hi(fast_pptp_fw)
	lw	$3,%lo(fast_pptp_fw)($3)
	.set	noreorder
	.set	nomacro
	beq	$3,$0,$L1
	move	$17,$2
	.set	macro
	.set	reorder

$LBB129 = .
$LBB130 = .
	.file 2 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/linux-3.10.49/arch/mips/include/asm/irqflags.h"
	.loc 2 39 0
#APP
 # 39 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/linux-3.10.49/arch/mips/include/asm/irqflags.h" 1
		.set	push						
	.set	reorder						
	.set	noat						
	di	$16					
	andi	$16, 1					
	sll $0, $0, 3			
	.set	pop						

 # 0 "" 2
#NO_APP
$LBE130 = .
$LBE129 = .
	.loc 1 813 0
	lbu	$3,23($2)
	li	$2,47			# 0x2f
	bne	$3,$2,$L4
	.loc 1 813 0 is_stmt 0 discriminator 1
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_len
	move	$4,$18
	.set	macro
	.set	reorder

	sltu	$2,$2,35
	bne	$2,$0,$L4
$LBB131 = .
	.loc 1 821 0 is_stmt 1
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_data
	move	$4,$18
	.set	macro
	.set	reorder

	lw	$3,14($17)
	ext	$3,$3,24,4
	sll	$3,$3,2
	addiu	$3,$3,14
	addu	$2,$2,$3
$LBB132 = .
$LBB133 = .
	.loc 1 93 0
	lbu	$4,3($2)
$LBE133 = .
$LBE132 = .
	.loc 1 824 0
	lbu	$3,1($2)
$LBB135 = .
$LBB134 = .
	.loc 1 93 0
	lbu	$6,2($2)
	sb	$4,21($sp)
$LBE134 = .
$LBE135 = .
	.loc 1 824 0
	andi	$5,$3,0x7
	li	$4,1			# 0x1
	.set	noreorder
	.set	nomacro
	bne	$5,$4,$L4
	sb	$6,20($sp)
	.set	macro
	.set	reorder

	.loc 1 824 0 is_stmt 0 discriminator 1
	lhu	$5,20($sp)
	li	$4,34827			# 0x880b
	bne	$5,$4,$L4
	.loc 1 861 0 is_stmt 1
	lbu	$4,0($2)
	andi	$4,$4,0x10
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L9
	move	$5,$0
	.set	macro
	.set	reorder

	.loc 1 862 0
	lui	$4,%hi(pptpAccInfo)
	addiu	$4,$4,%lo(pptpAccInfo)
	lhu	$6,18($17)
	lhu	$5,46($4)
	beq	$6,$5,$L17
	.loc 1 863 0
	lhu	$7,6($2)
	lhu	$6,18($4)
	.set	noreorder
	.set	nomacro
	bne	$7,$6,$L9
	li	$5,1			# 0x1
	.set	macro
	.set	reorder

	.loc 1 863 0 is_stmt 0 discriminator 1
	lw	$7,32($4)
	lw	$6,30($17)
	bne	$7,$6,$L9
	.loc 1 866 0 is_stmt 1
	lw	$6,8($2)
	.loc 1 868 0
	lw	$3,36($4)
	.loc 1 815 0
	move	$5,$0
$LBB136 = .
$LBB137 = .
	.loc 1 93 0
	srl	$10,$6,24
$LBE137 = .
$LBE136 = .
	.loc 1 868 0
	addiu	$7,$3,1
$LBB140 = .
$LBB138 = .
	.loc 1 93 0
	srl	$9,$6,16
	srl	$8,$6,8
	sb	$6,51($4)
$LBE138 = .
$LBE140 = .
	.loc 1 868 0
	sw	$7,36($4)
$LBB141 = .
$LBB139 = .
	.loc 1 93 0
	sb	$10,48($4)
	sb	$9,49($4)
	sb	$8,50($4)
$LBE139 = .
$LBE141 = .
$LBB142 = .
$LBB143 = .
	srl	$7,$3,24
	srl	$6,$3,16
	srl	$4,$3,8
$LBE143 = .
$LBE142 = .
	.loc 1 868 0
	sw	$3,16($sp)
$LBB145 = .
$LBB144 = .
	.loc 1 93 0
	sb	$3,11($2)
	sb	$7,8($2)
	sb	$6,9($2)
	sb	$4,10($2)
	.set	noreorder
	.set	nomacro
	j	$L9
	lbu	$3,1($2)
	.set	macro
	.set	reorder

$L17:
$LBE144 = .
$LBE145 = .
	.loc 1 873 0
	li	$5,1			# 0x1
$L9:
	.loc 1 875 0
	seb	$3,$3
	.set	noreorder
	.set	nomacro
	bltz	$3,$L10
	lui	$3,%hi(pptpAccInfo)
	.set	macro
	.set	reorder

$L12:
	.loc 1 884 0
	.set	noreorder
	.set	nomacro
	beq	$5,$0,$L11
	addiu	$8,$17,14
	.set	macro
	.set	reorder

	j	$L4
$L10:
	.loc 1 876 0
	addiu	$3,$3,%lo(pptpAccInfo)
	lhu	$6,6($2)
	lhu	$4,18($3)
	bne	$6,$4,$L4
	.loc 1 876 0 is_stmt 0 discriminator 1
	lw	$6,32($3)
	lw	$4,30($17)
	bne	$6,$4,$L4
	.loc 1 879 0 is_stmt 1
	lw	$3,40($3)
$LBB146 = .
$LBB147 = .
	.loc 1 93 0
	srl	$7,$3,24
	srl	$6,$3,16
	srl	$4,$3,8
$LBE147 = .
$LBE146 = .
	.loc 1 879 0
	sw	$3,16($sp)
$LBB149 = .
$LBB148 = .
	.loc 1 93 0
	sb	$7,12($2)
	sb	$6,13($2)
	sb	$4,14($2)
$LBE148 = .
$LBE149 = .
$LBE131 = .
	.set	noreorder
	.set	nomacro
	j	$L12
	sb	$3,15($2)
	.set	macro
	.set	reorder

$L11:
$LBB160 = .
	.loc 1 885 0
	lui	$4,%hi(pptpAccInfo)
	addiu	$4,$4,%lo(pptpAccInfo)
	lhu	$3,44($4)
$LBB150 = .
$LBB151 = .
	.file 3 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/linux-3.10.49/arch/mips/include/asm/checksum.h"
	.loc 3 121 0
	addiu	$2,$17,30
$LBE151 = .
$LBE150 = .
	.loc 1 885 0
	addiu	$3,$3,1
	andi	$3,$3,0xffff
	sh	$3,44($4)
	sh	$3,18($17)
	.loc 1 887 0
	lw	$5,14($17)
$LBB157 = .
$LBB154 = .
	.loc 3 109 0
	lw	$6,18($17)
$LBE154 = .
$LBE157 = .
	.loc 1 886 0
	sh	$0,24($17)
$LBB158 = .
$LBB155 = .
	.loc 3 113 0
	lw	$3,22($17)
	.loc 3 109 0
	addu	$7,$6,$5
	.loc 3 117 0
	lw	$4,26($17)
	.loc 3 110 0
	sltu	$6,$7,$6
	.loc 3 111 0
	addu	$7,$7,$3
	.loc 3 113 0
	addu	$6,$7,$6
	.loc 3 114 0
	sltu	$3,$6,$3
	.loc 3 115 0
	addu	$6,$6,$4
	.loc 3 117 0
	addu	$3,$6,$3
$LBE155 = .
$LBE158 = .
	.loc 1 887 0
	ext	$5,$5,24,4
$LBB159 = .
$LBB156 = .
	.loc 3 104 0
	sll	$5,$5,2
	.loc 3 118 0
	sltu	$4,$3,$4
	.loc 3 104 0
	addu	$5,$8,$5
	.loc 3 119 0
	addu	$3,$4,$3
$L14:
	.loc 3 123 0
	lw	$4,0($2)
	.loc 3 126 0
	addiu	$2,$2,4
	.loc 3 123 0
	addu	$3,$3,$4
	.loc 3 124 0
	sltu	$4,$3,$4
	.loc 3 127 0
	.set	noreorder
	.set	nomacro
	bne	$5,$2,$L14
	addu	$3,$4,$3
	.set	macro
	.set	reorder

$LBB152 = .
$LBB153 = .
	.loc 3 78 0
#APP
 # 78 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/linux-3.10.49/arch/mips/include/asm/checksum.h" 1
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
	.loc 3 91 0
#NO_APP
	sh	$3,24($17)
$L4:
$LBE153 = .
$LBE152 = .
$LBE156 = .
$LBE159 = .
$LBE160 = .
$LBB161 = .
$LBB162 = .
	.loc 2 58 0
#APP
 # 58 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/linux-3.10.49/arch/mips/include/asm/irqflags.h" 1
		.set	push						
	.set	noreorder					
	.set	noat						
	beqz	$16, 1f					
	di							
	ei							
1:								
	sll $0, $0, 3			
	.set	pop						

 # 0 "" 2
#NO_APP
$L1:
$LBE162 = .
$LBE161 = .
	.loc 1 894 0
	lw	$31,36($sp)
	lw	$18,32($sp)
	lw	$17,28($sp)
	lw	$16,24($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,40
	.set	macro
	.set	reorder

	.cfi_def_cfa_offset 0
	.cfi_restore 16
	.cfi_restore 17
	.cfi_restore 18
	.cfi_restore 31
	.end	sync_tx_pptp_gre_seqno
	.cfi_endproc
$LFE3076:
	.size	sync_tx_pptp_gre_seqno, .-sync_tx_pptp_gre_seqno
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
$LC0:
	.ascii	"%d\012\000"
	.text
	.align	2
	.globl	ppfw_read_proc
$LFB3080 = .
	.loc 1 993 0
	.cfi_startproc
	.set	nomips16
	.ent	ppfw_read_proc
	.type	ppfw_read_proc, @function
ppfw_read_proc:
	.frame	$sp,24,$31		# vars= 0, regs= 1/0, args= 16, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.loc 1 994 0
	lui	$2,%hi(fast_pptp_fw)
	lw	$6,%lo(fast_pptp_fw)($2)
	lui	$5,%hi($LC0)
	.loc 1 993 0
	addiu	$sp,$sp,-24
	.cfi_def_cfa_offset 24
	sw	$31,20($sp)
	.cfi_offset 31, -4
	.loc 1 994 0
	jal	seq_printf
	addiu	$5,$5,%lo($LC0)

	.loc 1 997 0
	lw	$31,20($sp)
	move	$2,$0
	j	$31
	addiu	$sp,$sp,24

	.cfi_def_cfa_offset 0
	.cfi_restore 31
	.set	macro
	.set	reorder
	.end	ppfw_read_proc
	.cfi_endproc
$LFE3080:
	.size	ppfw_read_proc, .-ppfw_read_proc
	.align	2
	.globl	pptpconn_read_proc
$LFB3081 = .
	.loc 1 1000 0
	.cfi_startproc
	.set	nomips16
	.ent	pptpconn_read_proc
	.type	pptpconn_read_proc, @function
pptpconn_read_proc:
	.frame	$sp,24,$31		# vars= 0, regs= 1/0, args= 16, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.loc 1 1001 0
	lui	$2,%hi(pptp_conn_check)
	lw	$6,%lo(pptp_conn_check)($2)
	lui	$5,%hi($LC0)
	.loc 1 1000 0
	addiu	$sp,$sp,-24
	.cfi_def_cfa_offset 24
	sw	$31,20($sp)
	.cfi_offset 31, -4
	.loc 1 1001 0
	jal	seq_printf
	addiu	$5,$5,%lo($LC0)

	.loc 1 1004 0
	lw	$31,20($sp)
	move	$2,$0
	j	$31
	addiu	$sp,$sp,24

	.cfi_def_cfa_offset 0
	.cfi_restore 31
	.set	macro
	.set	reorder
	.end	pptpconn_read_proc
	.cfi_endproc
$LFE3081:
	.size	pptpconn_read_proc, .-pptpconn_read_proc
	.align	2
	.globl	fastpath_pptp_single_open
$LFB3082 = .
	.loc 1 1007 0
	.cfi_startproc
	.set	nomips16
	.ent	fastpath_pptp_single_open
	.type	fastpath_pptp_single_open, @function
fastpath_pptp_single_open:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.loc 1 1008 0
	move	$4,$5
	lui	$5,%hi(ppfw_read_proc)
	move	$6,$0
	j	single_open
	addiu	$5,$5,%lo(ppfw_read_proc)

	.set	macro
	.set	reorder
	.end	fastpath_pptp_single_open
	.cfi_endproc
$LFE3082:
	.size	fastpath_pptp_single_open, .-fastpath_pptp_single_open
	.align	2
	.globl	pptp_conn_single_open
$LFB3084 = .
	.loc 1 1027 0
	.cfi_startproc
	.set	nomips16
	.ent	pptp_conn_single_open
	.type	pptp_conn_single_open, @function
pptp_conn_single_open:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.loc 1 1028 0
	move	$4,$5
	lui	$5,%hi(pptpconn_read_proc)
	move	$6,$0
	j	single_open
	addiu	$5,$5,%lo(pptpconn_read_proc)

	.set	macro
	.set	reorder
	.end	pptp_conn_single_open
	.cfi_endproc
$LFE3084:
	.size	pptp_conn_single_open, .-pptp_conn_single_open
	.align	2
$LFB3073 = .
	.loc 1 646 0
	.cfi_startproc
	.set	nomips16
	.ent	get_fastpptp_lastxmit
	.type	get_fastpptp_lastxmit, @function
get_fastpptp_lastxmit:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.loc 1 647 0
	lui	$2,%hi(fast_pptp_fw)
	lw	$3,%lo(fast_pptp_fw)($2)
	beq	$3,$0,$L38
	move	$2,$0

$LBB165 = .
$LBB166 = .
	lui	$3,%hi(pptpAccInfo)
	addiu	$2,$3,%lo(pptpAccInfo)
	lw	$2,4($2)
	.loc 1 648 0
	lw	$3,%lo(pptpAccInfo)($3)
	xori	$2,$2,0x1
	movn	$3,$0,$2
	move	$2,$3
$L38:
$LBE166 = .
$LBE165 = .
	.loc 1 651 0
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	get_fastpptp_lastxmit
	.cfi_endproc
$LFE3073:
	.size	get_fastpptp_lastxmit, .-get_fastpptp_lastxmit
	.align	2
$LFB3068 = .
	.loc 1 81 0
	.cfi_startproc
	.set	nomips16
	.ent	set_pptp_device
	.type	set_pptp_device, @function
set_pptp_device:
	.frame	$sp,24,$31		# vars= 0, regs= 1/0, args= 16, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.loc 1 82 0
	lui	$2,%hi(fast_pptp_fw)
	lw	$2,%lo(fast_pptp_fw)($2)
	beq	$2,$0,$L46
	nop

	.loc 1 81 0
	addiu	$sp,$sp,-24
	.cfi_def_cfa_offset 24
	sw	$31,20($sp)
	.cfi_offset 31, -4
$LBB169 = .
$LBB170 = .
	.loc 1 85 0
	jal	rtl_get_dev_by_name
	nop

	lui	$3,%hi(pptpAccInfo+56)
$LBE170 = .
$LBE169 = .
	.loc 1 87 0
	lw	$31,20($sp)
$LBB172 = .
$LBB171 = .
	.loc 1 85 0
	sw	$2,%lo(pptpAccInfo+56)($3)
$LBE171 = .
$LBE172 = .
	.loc 1 87 0
	addiu	$sp,$sp,24
	.cfi_restore 31
	.cfi_def_cfa_offset 0
$L46:
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	set_pptp_device
	.cfi_endproc
$LFE3068:
	.size	set_pptp_device, .-set_pptp_device
	.align	2
	.globl	Get_fast_pptp_fw
$LFB3066 = .
	.loc 1 57 0
	.cfi_startproc
	.set	nomips16
	.ent	Get_fast_pptp_fw
	.type	Get_fast_pptp_fw, @function
Get_fast_pptp_fw:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.loc 1 58 0
	lui	$2,%hi(fast_pptp_fw)
	.loc 1 60 0
	j	$31
	lw	$2,%lo(fast_pptp_fw)($2)

	.set	macro
	.set	reorder
	.end	Get_fast_pptp_fw
	.cfi_endproc
$LFE3066:
	.size	Get_fast_pptp_fw, .-Get_fast_pptp_fw
	.align	2
	.globl	is_pptp_device
$LFB3067 = .
	.loc 1 71 0
	.cfi_startproc
	.set	nomips16
	.ent	is_pptp_device
	.type	is_pptp_device, @function
is_pptp_device:
	.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.loc 1 72 0
	lui	$2,%hi(pptpAccInfo+56)
	lw	$2,%lo(pptpAccInfo+56)($2)
	beq	$2,$0,$L50
	.loc 1 71 0 discriminator 1
	addiu	$sp,$sp,-24
	.cfi_def_cfa_offset 24
	sw	$16,16($sp)
	.cfi_offset 16, -8
	move	$16,$4
	sw	$31,20($sp)
	.cfi_offset 31, -4
	.loc 1 72 0 discriminator 1
	.set	noreorder
	.set	nomacro
	jal	rtl_get_ppp_dev_name
	move	$4,$2
	.set	macro
	.set	reorder

$LBB173 = .
$LBB174 = .
	.file 4 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/linux-3.10.49/arch/mips/include/asm/string.h"
	.loc 4 77 0 discriminator 1
	move	$4,$16
#APP
 # 77 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/linux-3.10.49/arch/mips/include/asm/string.h" 1
	.set	noreorder
	.set	noat
	lbu	$3,($2)
1:	lbu	$1,($4)
	addiu	$2,1
	bne	$1,$3,2f
	addiu	$4,1
	bnez	$3,1b
	lbu	$3,($2)
	move	$3,$1
2:	subu	$3,$1
3:	.set	at
	.set	reorder
 # 0 "" 2
#NO_APP
$LBE174 = .
$LBE173 = .
	.loc 1 72 0 discriminator 1
	sltu	$2,$3,1
	.loc 1 78 0 discriminator 1
	lw	$31,20($sp)
	lw	$16,16($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,24
	.set	macro
	.set	reorder

	.cfi_def_cfa_offset 0
	.cfi_restore 16
	.cfi_restore 31
$L50:
	.loc 1 77 0
	.set	noreorder
	.set	nomacro
	j	$31
	move	$2,$0
	.set	macro
	.set	reorder

	.end	is_pptp_device
	.cfi_endproc
$LFE3067:
	.size	is_pptp_device, .-is_pptp_device
	.align	2
	.globl	Check_GRE_rx_net_device
$LFB3070 = .
	.loc 1 97 0
	.cfi_startproc
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
	.cfi_def_cfa_offset 40
	sw	$31,36($sp)
	sw	$20,32($sp)
	sw	$18,24($sp)
	sw	$17,20($sp)
	sw	$16,16($sp)
	.cfi_offset 31, -4
	.cfi_offset 20, -8
	.cfi_offset 18, -16
	.cfi_offset 17, -20
	.cfi_offset 16, -24
	move	$17,$4
	sw	$19,28($sp)
	.cfi_offset 19, -12
	.loc 1 100 0
	jal	rtl_ip_hdr
	lui	$18,%hi(pptpAccInfo)

	move	$16,$2
	.loc 1 101 0
	move	$4,$17
	jal	rtl_get_skb_data
	addiu	$18,$18,%lo(pptpAccInfo)

	lw	$3,0($16)
	.loc 1 103 0
	lw	$16,8($18)
	beq	$16,$0,$L55
	ext	$20,$3,24,4

	.loc 1 106 0
	move	$4,$17
	jal	rtl_get_skb_dev
	move	$19,$2

	bne	$16,$2,$L54
	move	$3,$0

	.loc 1 106 0 is_stmt 0 discriminator 1
	sll	$20,$20,2
	addu	$19,$19,$20
	lhu	$3,6($19)
	lhu	$2,30($18)
	xor	$3,$3,$2
	j	$L54
	sltu	$3,$3,1

$L55:
	.loc 1 111 0 is_stmt 1
	move	$3,$0
$L54:
	.loc 1 112 0
	lw	$31,36($sp)
	lw	$20,32($sp)
	lw	$19,28($sp)
	lw	$18,24($sp)
	lw	$17,20($sp)
	lw	$16,16($sp)
	move	$2,$3
	j	$31
	addiu	$sp,$sp,40

	.cfi_def_cfa_offset 0
	.cfi_restore 16
	.cfi_restore 17
	.cfi_restore 18
	.cfi_restore 19
	.cfi_restore 20
	.cfi_restore 31
	.set	macro
	.set	reorder
	.end	Check_GRE_rx_net_device
	.cfi_endproc
$LFE3070:
	.size	Check_GRE_rx_net_device, .-Check_GRE_rx_net_device
	.align	2
	.globl	fast_pptp_filter
$LFB3071 = .
	.loc 1 116 0
	.cfi_startproc
	.set	nomips16
	.ent	fast_pptp_filter
	.type	fast_pptp_filter, @function
fast_pptp_filter:
	.frame	$sp,40,$31		# vars= 0, regs= 5/0, args= 16, gp= 0
	.mask	0x800f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-40
	.cfi_def_cfa_offset 40
	sw	$17,24($sp)
	.cfi_offset 17, -16
	move	$17,$4
	sw	$31,36($sp)
	sw	$16,20($sp)
	sw	$19,32($sp)
	.cfi_offset 31, -4
	.cfi_offset 16, -20
	.cfi_offset 19, -8
	.cfi_offset 18, -12
	.loc 1 124 0
	jal	rtl_ip_hdr
	sw	$18,28($sp)

	.loc 1 126 0
	move	$4,$17
	jal	rtl_get_skb_len
	move	$16,$2

	sltu	$2,$2,56
	bne	$2,$0,$L84
	lw	$31,36($sp)

$LBB175 = .
	.loc 1 127 0
	lw	$2,0($16)
	.loc 1 129 0
	lbu	$3,9($16)
	.loc 1 127 0
	ext	$4,$2,24,4
	.loc 1 129 0
	li	$2,6			# 0x6
	bne	$3,$2,$L84
	sll	$4,$4,2

	.loc 1 127 0 discriminator 1
	addu	$4,$16,$4
	.loc 1 129 0 discriminator 1
	lhu	$3,0($4)
	li	$2,1723			# 0x6bb
	bne	$3,$2,$L84
	li	$3,1			# 0x1

	.loc 1 130 0
	lw	$2,12($4)
	srl	$2,$2,28
	sll	$2,$2,2
	addu	$4,$4,$2
	.loc 1 134 0
	lhu	$2,2($4)
	bne	$2,$3,$L84
	li	$5,8			# 0x8

	.loc 1 135 0 discriminator 1
	lhu	$3,8($4)
	.loc 1 134 0 discriminator 1
	bne	$3,$5,$L60
	nop

	.loc 1 135 0
	lbu	$3,16($4)
	bne	$3,$2,$L84
	lui	$18,%hi(pptpAccInfo)

	.loc 1 143 0
	addiu	$18,$18,%lo(pptpAccInfo)
	lw	$2,36($18)
	beq	$2,$0,$L83
	nop

	.loc 1 143 0 is_stmt 0 discriminator 1
	lw	$2,20($18)
	beq	$2,$0,$L83
	nop

	lw	$2,32($18)
	bne	$2,$0,$L80
	nop

$L83:
	j	$L61
	lhu	$2,12($4)

$L80:
	.loc 1 144 0 is_stmt 1
	lhu	$3,18($18)
	lhu	$2,12($4)
	bne	$3,$2,$L84
	lw	$31,36($sp)

	.loc 1 144 0 is_stmt 0 discriminator 1
	lhu	$5,30($18)
	lhu	$3,14($4)
	bne	$5,$3,$L85
	lw	$19,32($sp)

$L61:
	.loc 1 151 0 is_stmt 1
	sh	$2,18($18)
	.loc 1 152 0
	lhu	$2,14($4)
	.loc 1 150 0
	lui	$3,%hi(pptp_tcp_finished)
	li	$19,1			# 0x1
	.loc 1 152 0
	sh	$2,30($18)
	.loc 1 156 0
	lw	$2,16($16)
	.loc 1 159 0
	move	$4,$17
	.loc 1 150 0
	sw	$19,%lo(pptp_tcp_finished)($3)
	.loc 1 156 0
	sw	$2,20($18)
	.loc 1 157 0
	lw	$2,12($16)
	.loc 1 158 0
	sw	$19,36($18)
	.loc 1 159 0
	jal	rtl_get_skb_dev
	sw	$2,32($18)

$LBB176 = .
	.loc 1 162 0
	move	$4,$17
	jal	rtl_get_skb_data
	sw	$2,8($18)

	addiu	$2,$2,-8
	lwl	$3,0($2)
	lui	$6,%hi(pptpAccInfo+24)
	addiu	$5,$6,%lo(pptpAccInfo+24)
	lwr	$3,3($2)
$LBE176 = .
$LBB177 = .
	.loc 1 163 0
	move	$4,$17
$LBE177 = .
$LBB178 = .
	.loc 1 162 0
	sw	$3,%lo(pptpAccInfo+24)($6)
	lbu	$3,4($2)
	sb	$3,4($5)
	lbu	$2,5($2)
$LBE178 = .
$LBB179 = .
	.loc 1 163 0
	jal	rtl_get_skb_data
	sb	$2,5($5)

	addiu	$2,$2,-14
	lwl	$3,0($2)
	lui	$5,%hi(pptpAccInfo+12)
	addiu	$4,$5,%lo(pptpAccInfo+12)
	lwr	$3,3($2)
	sw	$3,%lo(pptpAccInfo+12)($5)
	lbu	$3,4($2)
	sb	$3,4($4)
	lbu	$2,5($2)
$LBE179 = .
	.loc 1 182 0
	sw	$19,4($18)
	j	$L58
	sb	$2,5($4)

$L60:
	.loc 1 189 0 discriminator 1
	li	$2,13			# 0xd
	bne	$3,$2,$L84
	lw	$31,36($sp)

	.loc 1 195 0
	lui	$18,%hi(pptpAccInfo)
	addiu	$18,$18,%lo(pptpAccInfo)
	lw	$2,36($18)
	beq	$2,$0,$L86
	lui	$2,%hi(pptp_tcp_finished)

	.loc 1 195 0 is_stmt 0 discriminator 1
	lw	$2,20($18)
	beq	$2,$0,$L86
	lui	$2,%hi(pptp_tcp_finished)

	lw	$2,32($18)
	beq	$2,$0,$L86
	lui	$2,%hi(pptp_tcp_finished)

	.loc 1 196 0 is_stmt 1
	lhu	$3,18($18)
	lhu	$2,12($4)
	bne	$3,$2,$L85
	lw	$19,32($sp)

	.loc 1 201 0
	lui	$2,%hi(pptp_tcp_finished)
$L86:
	sw	$0,%lo(pptp_tcp_finished)($2)
	.loc 1 202 0
	sw	$0,4($18)
$L58:
$LBE175 = .
	.loc 1 293 0
	lw	$31,36($sp)
$L84:
	lw	$19,32($sp)
$L85:
	lw	$18,28($sp)
	lw	$17,24($sp)
	lw	$16,20($sp)
	j	$31
	addiu	$sp,$sp,40

	.cfi_def_cfa_offset 0
	.cfi_restore 16
	.cfi_restore 17
	.cfi_restore 18
	.cfi_restore 19
	.cfi_restore 31
	.set	macro
	.set	reorder
	.end	fast_pptp_filter
	.cfi_endproc
$LFE3071:
	.size	fast_pptp_filter, .-fast_pptp_filter
	.align	2
	.globl	fast_pptp_to_lan
$LFB3072 = .
	.loc 1 469 0
	.cfi_startproc
	.set	nomips16
	.ent	fast_pptp_to_lan
	.type	fast_pptp_to_lan, @function
fast_pptp_to_lan:
	.frame	$sp,48,$31		# vars= 0, regs= 7/0, args= 16, gp= 0
	.mask	0x803f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-48
	.cfi_def_cfa_offset 48
	sw	$18,28($sp)
	sw	$17,24($sp)
	sw	$31,44($sp)
	sw	$21,40($sp)
	sw	$20,36($sp)
	sw	$19,32($sp)
	sw	$16,20($sp)
	.cfi_offset 18, -20
	.cfi_offset 17, -24
	.cfi_offset 31, -4
	.cfi_offset 21, -8
	.cfi_offset 20, -12
	.cfi_offset 19, -16
	.cfi_offset 16, -28
	.loc 1 474 0
	lw	$16,0($4)
	.loc 1 483 0
	lui	$17,%hi(pptpAccInfo)
	.loc 1 469 0
	move	$18,$4
	.loc 1 483 0
	addiu	$17,$17,%lo(pptpAccInfo)
	jal	rtl_get_skb_dev
	move	$4,$16

	lw	$3,8($17)
	beq	$3,$2,$L88
	nop

$L90:
	.loc 1 484 0
	j	$L125
	move	$2,$0

$L88:
	.loc 1 483 0 discriminator 1
	jal	rtl_ip_hdr
	move	$4,$16

	lbu	$3,9($2)
	li	$2,47			# 0x2f
	bne	$3,$2,$L125
	move	$2,$0

	jal	rtl_get_skb_len
	move	$4,$16

	sltu	$2,$2,20
	bne	$2,$0,$L125
	move	$2,$0

	.loc 1 486 0
	jal	rtl_ip_hdr
	move	$4,$16

	move	$19,$2
	.loc 1 487 0
	jal	rtl_get_skb_data
	move	$4,$16

	.loc 1 488 0
	lw	$3,0($19)
	ext	$3,$3,24,4
	sll	$3,$3,2
	addu	$3,$2,$3
	.loc 1 490 0
	lbu	$4,1($3)
	li	$2,1			# 0x1
	andi	$4,$4,0x7
	bne	$4,$2,$L125
	move	$2,$0

	.loc 1 490 0 is_stmt 0 discriminator 1
	lhu	$4,2($3)
	li	$2,34827			# 0x880b
	bne	$4,$2,$L125
	move	$2,$0

$LBB180 = .
	.loc 1 496 0 is_stmt 1
	lhu	$4,6($3)
	lhu	$2,30($17)
	bne	$4,$2,$L90
	nop

	.loc 1 501 0
	lbu	$4,0($3)
	andi	$4,$4,0x10
	beq	$4,$0,$L91
	li	$2,8			# 0x8

	.loc 1 502 0
	lw	$4,8($3)
	.loc 1 503 0
	li	$2,12			# 0xc
	.loc 1 502 0
	sw	$4,40($17)
$L91:
	.loc 1 506 0
	lb	$6,1($3)
	.loc 1 512 0
	lhu	$4,4($3)
	.loc 1 507 0
	addiu	$5,$2,4
	slt	$6,$6,0
	.loc 1 512 0
	beq	$4,$0,$L90
	movn	$2,$5,$6

	.loc 1 509 0
	addu	$3,$3,$2
	.loc 1 540 0
	lbu	$4,0($3)
	bne	$4,$0,$L93
	nop

	.loc 1 542 0
	addiu	$3,$3,1
	j	$L94
	li	$5,1			# 0x1

$L93:
	.loc 1 544 0
	li	$6,255			# 0xff
	bne	$4,$6,$L94
	move	$5,$0

	.loc 1 544 0 is_stmt 0 discriminator 1
	lbu	$5,1($3)
	li	$4,3			# 0x3
	bne	$5,$4,$L90
	nop

	.loc 1 547 0 is_stmt 1
	lbu	$5,2($3)
	bne	$5,$0,$L107
	addiu	$4,$3,2

	.loc 1 549 0
	addiu	$3,$3,3
$LBE180 = .
	.loc 1 548 0
	j	$L94
	li	$5,3			# 0x3

$L107:
$LBB182 = .
	.loc 1 546 0
	move	$3,$4
	.loc 1 545 0
	li	$5,2			# 0x2
$L94:
	.loc 1 552 0
	lbu	$3,0($3)
	li	$4,33			# 0x21
	beq	$3,$4,$L95
	move	$4,$16

	.loc 1 552 0 is_stmt 0 discriminator 1
	li	$4,253			# 0xfd
	bne	$3,$4,$L90
	nop

$LBE182 = .
	.loc 1 563 0 is_stmt 1
	j	$L128
	lw	$3,0($19)

$L126:
$LBB183 = .
	.loc 1 566 0 discriminator 1
	jal	rtl_get_ppp_dev_priv
	nop

	beq	$2,$0,$L90
	addiu	$5,$19,-2

	.loc 1 569 0
	jal	skb_pull
	move	$4,$16

	.loc 1 570 0
	jal	rtl_get_skb_data
	move	$4,$16

	.loc 1 572 0
	li	$3,-3			# 0xfffffffffffffffd
	sb	$3,1($2)
	.loc 1 571 0
	sb	$0,0($2)
	.loc 1 573 0
	jal	rtl_get_ppp_dev_priv
	lw	$4,56($17)

	.loc 1 575 0
	move	$4,$2
	move	$5,$16
	jal	rtl_ppp_receive_nonmp_frame
	li	$6,1			# 0x1

	.loc 1 576 0
	beq	$2,$0,$L108
	move	$16,$2

	.loc 1 580 0
	sw	$2,0($18)
	.loc 1 582 0
	li	$19,1			# 0x1
$L104:
	.loc 1 593 0
	jal	rtl_get_skb_data
	move	$4,$16

	andi	$18,$2,0x3
	.loc 1 594 0
	beq	$18,$0,$L98
	nop

	.loc 1 595 0
	jal	rtl_skb_headroom
	move	$4,$16

	sltu	$2,$2,$18
	bne	$2,$0,$L98
	nop

$LBB181 = .
	.loc 1 597 0
	jal	rtl_get_skb_len
	move	$4,$16

	move	$4,$16
	jal	rtl_get_skb_data
	move	$20,$2

	move	$4,$16
	jal	rtl_get_skb_data
	subu	$21,$2,$18

	move	$5,$2
	move	$4,$21
	jal	memmove
	move	$6,$20

$LBE181 = .
	.loc 1 598 0
	move	$4,$16
	move	$5,$18
	jal	rtl_set_skb_data
	li	$6,1			# 0x1

	.loc 1 599 0
	move	$4,$16
	move	$5,$18
	jal	rtl_set_skb_tail
	li	$6,1			# 0x1

$L98:
	.loc 1 605 0
	jal	rtl_skb_reset_network_header
	move	$4,$16

	.loc 1 606 0
	jal	rtl_skb_reset_transport_header
	move	$4,$16

	.loc 1 612 0
	lw	$4,56($17)
	beq	$4,$0,$L125
	move	$2,$0

	.loc 1 614 0
	bne	$19,$0,$L101
	nop

	.loc 1 615 0
	jal	rtl_get_ppp_dev_priv
	nop

	beq	$2,$0,$L101
	nop

	.loc 1 616 0
	jal	rtl_get_ppp_dev_priv
	lw	$4,56($17)

	.loc 1 617 0
	move	$4,$16
	jal	rtl_get_skb_len
	move	$18,$2

	addiu	$6,$2,-2
	move	$4,$18
	jal	rtl_inc_ppp_stats
	move	$5,$0

$L101:
	.loc 1 625 0
	lw	$5,56($17)
	jal	rtl_set_skb_dev
	move	$4,$16

	.loc 1 626 0
	j	$L125
	li	$2,1			# 0x1

$L108:
$LBE183 = .
	.loc 1 578 0
	j	$L125
	li	$2,-2			# 0xfffffffffffffffe

$L128:
$LBB184 = .
	.loc 1 566 0
	lw	$4,56($17)
	.loc 1 553 0
	addiu	$5,$5,1
	.loc 1 563 0
	ext	$3,$3,24,4
	sll	$3,$3,2
	addu	$2,$3,$2
	.loc 1 566 0
	bne	$4,$0,$L126
	addu	$19,$5,$2

	j	$L125
	move	$2,$0

$L95:
	.loc 1 563 0
	lw	$3,0($19)
	.loc 1 553 0
	addiu	$5,$5,1
	.loc 1 563 0
	ext	$3,$3,24,4
	sll	$3,$3,2
	addu	$2,$3,$2
	.loc 1 586 0
	jal	skb_pull
	addu	$5,$5,$2

$LBE184 = .
	.loc 1 477 0
	j	$L104
	move	$19,$0

$L125:
	.loc 1 643 0
	lw	$31,44($sp)
	lw	$21,40($sp)
	lw	$20,36($sp)
	lw	$19,32($sp)
	lw	$18,28($sp)
	lw	$17,24($sp)
	lw	$16,20($sp)
	j	$31
	addiu	$sp,$sp,48

	.cfi_def_cfa_offset 0
	.cfi_restore 16
	.cfi_restore 17
	.cfi_restore 18
	.cfi_restore 19
	.cfi_restore 20
	.cfi_restore 21
	.cfi_restore 31
	.set	macro
	.set	reorder
	.end	fast_pptp_to_lan
	.cfi_endproc
$LFE3072:
	.size	fast_pptp_to_lan, .-fast_pptp_to_lan
	.section	.rodata.str1.4
	.align	2
$LC1:
	.ascii	"ppp0\000"
	.align	2
$LC2:
	.ascii	"pptpInfo.ppp0_dev == NULL\012\000"
	.align	2
$LC3:
	.ascii	"RTL\000"
	.align	2
$LC4:
	.ascii	"pptpInfo.ppp0_dev->priv == NULL\012\000"
	.text
	.align	2
	.globl	fast_pptp_to_wan
$LFB3074 = .
	.loc 1 656 0
	.cfi_startproc
	.set	nomips16
	.ent	fast_pptp_to_wan
	.type	fast_pptp_to_wan, @function
fast_pptp_to_wan:
	.frame	$sp,88,$31		# vars= 40, regs= 7/0, args= 16, gp= 0
	.mask	0x803f0000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-88
	.cfi_def_cfa_offset 88
	sw	$31,84($sp)
	sw	$18,68($sp)
	sw	$17,64($sp)
	sw	$16,60($sp)
	.cfi_offset 31, -4
	.cfi_offset 18, -20
	.cfi_offset 17, -24
	.cfi_offset 16, -28
	move	$17,$4
	sw	$21,80($sp)
	sw	$20,76($sp)
	.cfi_offset 21, -8
	.cfi_offset 20, -12
	.cfi_offset 19, -16
	.loc 1 665 0
	.set	noreorder
	.set	nomacro
	jal	rtl_ip_hdr
	sw	$19,72($sp)
	.set	macro
	.set	reorder

	lw	$16,12($2)
	.loc 1 666 0
	move	$4,$17
	.loc 1 665 0
	li	$2,-16777216			# 0xffffffffff000000
	.loc 1 666 0
	.set	noreorder
	.set	nomacro
	jal	rtl_ip_hdr
	and	$16,$16,$2
	.set	macro
	.set	reorder

	.loc 1 667 0
	move	$4,$17
	.set	noreorder
	.set	nomacro
	jal	rtl_ip_hdr
	lw	$18,12($2)
	.set	macro
	.set	reorder

	lw	$3,12($2)
	.loc 1 668 0
	li	$2,167772160			# 0xa000000
	.set	noreorder
	.set	nomacro
	bne	$16,$2,$L130
	li	$2,16711680			# 0xff0000
	.set	macro
	.set	reorder

	.loc 1 666 0 discriminator 1
	and	$18,$18,$2
	.loc 1 668 0 discriminator 1
	li	$2,4194304			# 0x400000
	.set	noreorder
	.set	nomacro
	bne	$18,$2,$L130
	andi	$3,$3,0xff00
	.set	macro
	.set	reorder

	li	$2,16384			# 0x4000
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L162
	lui	$18,%hi(pptpAccInfo)
	.set	macro
	.set	reorder

	lui	$2,%hi(pptp_conn_check)
	lw	$3,%lo(pptp_conn_check)($2)
	li	$2,3			# 0x3
	.set	noreorder
	.set	nomacro
	beq	$3,$2,$L131
	move	$2,$0
	.set	macro
	.set	reorder

$L130:
	.loc 1 674 0
	lui	$18,%hi(pptpAccInfo)
$L162:
	addiu	$16,$18,%lo(pptpAccInfo)
	lw	$4,56($16)
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L131
	move	$2,$0
	.set	macro
	.set	reorder

	.loc 1 674 0 is_stmt 0 discriminator 1
	jal	rtl_get_ppp_dev_name
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L131
	move	$2,$0
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jal	rtl_get_ppp_dev_name
	lw	$4,56($16)
	.set	macro
	.set	reorder

$LBB185 = .
$LBB186 = .
	.loc 4 77 0 is_stmt 1 discriminator 1
	lui	$3,%hi($LC1)
	addiu	$3,$3,%lo($LC1)
#APP
 # 77 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/linux-3.10.49/arch/mips/include/asm/string.h" 1
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
$LBE186 = .
$LBE185 = .
	.loc 1 674 0 discriminator 1
	.set	noreorder
	.set	nomacro
	bne	$4,$0,$L131
	move	$2,$0
	.set	macro
	.set	reorder

	.loc 1 677 0
	lw	$2,4($16)
	beq	$2,$0,$L133
	.loc 1 677 0 is_stmt 0 discriminator 1
	lw	$4,56($16)
	bne	$4,$0,$L134
$L140:
	.loc 1 762 0 is_stmt 1
	lui	$4,%hi($LC2)
	.set	noreorder
	.set	nomacro
	jal	printk
	addiu	$4,$4,%lo($LC2)
	.set	macro
	.set	reorder

$L159:
	.set	noreorder
	.set	nomacro
	j	$L131
	move	$2,$0
	.set	macro
	.set	reorder

$L134:
	.loc 1 677 0 discriminator 1
	jal	rtl_get_ppp_dev_priv
	beq	$2,$0,$L133
$LBB187 = .
	.loc 1 680 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_ppp_dev_priv
	lw	$4,56($16)
	.set	macro
	.set	reorder

	.loc 1 683 0
	move	$4,$2
	.set	noreorder
	.set	nomacro
	jal	rtl_ppp_vj_check
	move	$19,$2
	.set	macro
	.set	reorder

	li	$3,1			# 0x1
	.set	noreorder
	.set	nomacro
	beq	$2,$3,$L131
	move	$2,$0
	.set	macro
	.set	reorder

	.loc 1 688 0
	.set	noreorder
	.set	nomacro
	jal	rtl_ip_hdr
	move	$4,$17
	.set	macro
	.set	reorder

	.loc 1 690 0
	move	$4,$19
	.set	noreorder
	.set	nomacro
	jal	rtl_get_ppp_xmit_pending
	lbu	$20,1($2)
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L131
	move	$2,$0
	.set	macro
	.set	reorder

	.loc 1 694 0
	lui	$5,%hi($LC3)
	move	$4,$17
	addiu	$5,$5,%lo($LC3)
	.set	noreorder
	.set	nomacro
	jal	rtl_set_skb_cb
	li	$6,3			# 0x3
	.set	macro
	.set	reorder

	.loc 1 695 0
	lw	$5,56($16)
	.set	noreorder
	.set	nomacro
	jal	rtl_ppp_start_xmit
	move	$4,$17
	.set	macro
	.set	reorder

	.loc 1 696 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_ppp_xmit_pending
	move	$4,$19
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L141
	li	$2,1			# 0x1
	.set	macro
	.set	reorder

	.loc 1 701 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_ppp_xmit_pending
	move	$4,$19
	.set	macro
	.set	reorder

	move	$21,$2
	.loc 1 703 0
	move	$4,$19
	.set	noreorder
	.set	nomacro
	jal	rtl_set_ppp_xmit_pending
	move	$5,$0
	.set	macro
	.set	reorder

	.loc 1 706 0
	.set	noreorder
	.set	nomacro
	jal	rtl_skb_headroom
	move	$4,$21
	.set	macro
	.set	reorder

	sltu	$2,$2,50
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L135
	move	$4,$21
	.set	macro
	.set	reorder

$L161:
$LBB188 = .
	.loc 1 707 0
	.set	noreorder
	.set	nomacro
	jal	skb_realloc_headroom
	li	$5,50			# 0x32
	.set	macro
	.set	reorder

	.loc 1 708 0
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L157
	move	$17,$2
	.set	macro
	.set	reorder

	j	$L160
$L135:
$LBE188 = .
	.loc 1 706 0 discriminator 1
	.set	noreorder
	.set	nomacro
	jal	rtl_skb_cloned
	move	$4,$21
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L161
	move	$4,$21
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jal	rtl_skb_shared
	move	$4,$21
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L139
	move	$17,$21
	.set	macro
	.set	reorder

$LBE187 = .
	.loc 1 707 0
	.set	noreorder
	.set	nomacro
	j	$L161
	move	$4,$21
	.set	macro
	.set	reorder

$L160:
$LBB215 = .
$LBB189 = .
	.loc 1 710 0
	.set	noreorder
	.set	nomacro
	jal	consume_skb
	move	$4,$21
	.set	macro
	.set	reorder

	.loc 1 711 0
	.set	noreorder
	.set	nomacro
	j	$L131
	li	$2,1			# 0x1
	.set	macro
	.set	reorder

$L157:
	.loc 1 713 0
	.set	noreorder
	.set	nomacro
	jal	consume_skb
	move	$4,$21
	.set	macro
	.set	reorder

$L139:
$LBE189 = .
	.loc 1 719 0
	move	$4,$17
	.set	noreorder
	.set	nomacro
	jal	skb_push
	li	$5,50			# 0x32
	.set	macro
	.set	reorder

$LBB190 = .
	.loc 1 720 0
	lw	$4,24($16)
$LBE190 = .
	.loc 1 726 0
	lbu	$3,16($sp)
	li	$5,4			# 0x4
$LBB191 = .
	.loc 1 720 0
	swl	$4,0($2)
	swr	$4,3($2)
	lbu	$4,28($16)
$LBE191 = .
	.loc 1 726 0
	ins	$3,$5,4,4
	.loc 1 722 0
	li	$6,8			# 0x8
$LBB192 = .
	.loc 1 720 0
	sb	$4,4($2)
	lbu	$4,29($16)
$LBE192 = .
	.loc 1 730 0
	sb	$20,17($sp)
$LBB193 = .
	.loc 1 720 0
	sb	$4,5($2)
$LBE193 = .
$LBB194 = .
	.loc 1 721 0
	lw	$4,12($16)
	swl	$4,6($2)
	swr	$4,9($2)
	lbu	$5,16($16)
$LBE194 = .
	.loc 1 734 0
	move	$4,$17
$LBB195 = .
	.loc 1 721 0
	sb	$5,10($2)
	lbu	$5,17($16)
$LBE195 = .
	.loc 1 722 0
	sb	$6,12($2)
	sb	$0,13($2)
$LBB196 = .
	.loc 1 721 0
	sb	$5,11($2)
$LBE196 = .
	.loc 1 727 0
	li	$2,5			# 0x5
	ins	$3,$2,0,4
	.loc 1 731 0
	lw	$19,32($16)
	.loc 1 732 0
	lw	$21,20($16)
	.loc 1 728 0
	li	$2,16384			# 0x4000
	sh	$2,22($sp)
	.loc 1 729 0
	li	$2,47			# 0x2f
	.loc 1 734 0
	move	$5,$0
	.loc 1 729 0
	sb	$2,25($sp)
	.loc 1 733 0
	li	$2,64			# 0x40
	.loc 1 727 0
	sb	$3,16($sp)
	.loc 1 731 0
	sw	$19,32($sp)
	.loc 1 732 0
	sw	$21,28($sp)
	.loc 1 734 0
	.set	noreorder
	.set	nomacro
	jal	rtl_set_skb_ip_summed
	sb	$2,24($sp)
	.set	macro
	.set	reorder

	.loc 1 735 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_len
	move	$4,$17
	.set	macro
	.set	reorder

	.loc 1 736 0
	lhu	$3,44($16)
	.loc 1 735 0
	addiu	$2,$2,-14
	sh	$2,18($sp)
	.loc 1 736 0
	addiu	$3,$3,1
	andi	$3,$3,0xffff
	sh	$3,20($sp)
$LBB197 = .
$LBB198 = .
	.loc 3 109 0
	lw	$2,20($sp)
$LBE198 = .
$LBE197 = .
	.loc 1 737 0
	sh	$0,26($sp)
$LBB205 = .
$LBB201 = .
	.loc 3 109 0
	lw	$5,16($sp)
	.loc 3 113 0
	lw	$4,24($sp)
$LBE201 = .
$LBE205 = .
	.loc 1 736 0
	sh	$3,44($16)
$LBB206 = .
$LBB202 = .
	.loc 3 109 0
	addu	$5,$2,$5
	.loc 3 110 0
	sltu	$2,$5,$2
	.loc 3 111 0
	addu	$5,$5,$4
	.loc 3 113 0
	addu	$2,$5,$2
	.loc 3 114 0
	sltu	$4,$2,$4
	.loc 3 115 0
	addu	$2,$2,$21
	.loc 3 117 0
	addu	$4,$2,$4
	.loc 3 119 0
	addu	$2,$4,$19
	.loc 3 118 0
	sltu	$21,$4,$21
	.loc 3 123 0
	addu	$2,$2,$21
$LBE202 = .
$LBE206 = .
$LBB207 = .
	.loc 1 740 0
	move	$4,$17
$LBE207 = .
$LBB208 = .
$LBB203 = .
	.loc 3 124 0
	sltu	$19,$2,$19
$LBE203 = .
$LBE208 = .
	.loc 1 739 0
	sh	$3,46($16)
$LBB209 = .
$LBB204 = .
	.loc 3 125 0
	addu	$2,$19,$2
$LBB199 = .
$LBB200 = .
	.loc 3 78 0
#APP
 # 78 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/linux-3.10.49/arch/mips/include/asm/checksum.h" 1
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
$LBE200 = .
$LBE199 = .
$LBE204 = .
$LBE209 = .
$LBB210 = .
	.loc 1 740 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_data
	sh	$2,26($sp)
	.set	macro
	.set	reorder

	lw	$5,16($sp)
	lw	$4,20($sp)
	addiu	$3,$2,14
	swl	$5,14($2)
	swr	$5,3($3)
	lw	$5,24($sp)
	swl	$4,4($3)
	swr	$4,7($3)
	lw	$4,28($sp)
	swl	$5,8($3)
	swr	$5,11($3)
	lw	$2,32($sp)
	swl	$4,12($3)
	swr	$4,15($3)
	swl	$2,16($3)
	swr	$2,19($3)
$LBE210 = .
	.loc 1 744 0
	li	$2,48			# 0x30
	sb	$2,36($sp)
	.loc 1 745 0
	li	$2,-127			# 0xffffffffffffff81
	.loc 1 748 0
	move	$4,$17
	.loc 1 745 0
	sb	$2,37($sp)
	.loc 1 746 0
	li	$2,-30709			# 0xffffffffffff880b
	.loc 1 748 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_len
	sh	$2,38($sp)
	.set	macro
	.set	reorder

	.loc 1 750 0
	lw	$3,36($16)
	.loc 1 749 0
	lhu	$6,18($16)
	.loc 1 751 0
	lw	$5,40($16)
	.loc 1 750 0
	addiu	$7,$3,1
$LBB211 = .
	.loc 1 752 0
	move	$4,$17
$LBE211 = .
	.loc 1 748 0
	addiu	$2,$2,-50
	.loc 1 750 0
	sw	$7,36($16)
	.loc 1 749 0
	sh	$6,42($sp)
	.loc 1 750 0
	sw	$3,44($sp)
	.loc 1 751 0
	sw	$5,48($sp)
$LBB212 = .
	.loc 1 752 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_data
	sh	$2,40($sp)
	.set	macro
	.set	reorder

	lw	$5,36($sp)
	lw	$4,40($sp)
	addiu	$3,$2,34
	swl	$5,34($2)
	swr	$5,3($3)
	lw	$5,44($sp)
	swl	$4,4($3)
	swr	$4,7($3)
	swl	$5,8($3)
	lw	$2,48($sp)
	swr	$5,11($3)
$LBE212 = .
	.loc 1 753 0
	lui	$4,%hi(jiffies)
	lw	$6,%lo(jiffies)($4)
	.loc 1 756 0
	lw	$5,8($16)
$LBB213 = .
	.loc 1 752 0
	swl	$2,12($3)
$LBE213 = .
	.loc 1 756 0
	move	$4,$17
$LBB214 = .
	.loc 1 752 0
	swr	$2,15($3)
$LBE214 = .
	.loc 1 756 0
	.set	noreorder
	.set	nomacro
	jal	rtl_set_skb_dev
	sw	$6,%lo(pptpAccInfo)($18)
	.set	macro
	.set	reorder

	.loc 1 757 0
	.set	noreorder
	.set	nomacro
	jal	dev_queue_xmit
	move	$4,$17
	.set	macro
	.set	reorder

	.loc 1 758 0
	.set	noreorder
	.set	nomacro
	j	$L131
	li	$2,1			# 0x1
	.set	macro
	.set	reorder

$L133:
$LBE215 = .
	.loc 1 761 0
	lw	$4,56($16)
	beq	$4,$0,$L140
	.loc 1 763 0
	jal	rtl_get_ppp_dev_priv
	bne	$2,$0,$L159
	.loc 1 764 0
	lui	$4,%hi($LC4)
	.set	noreorder
	.set	nomacro
	jal	printk
	addiu	$4,$4,%lo($LC4)
	.set	macro
	.set	reorder

	move	$2,$0
$L141:
$L131:
	.loc 1 768 0
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

	.cfi_def_cfa_offset 0
	.cfi_restore 16
	.cfi_restore 17
	.cfi_restore 18
	.cfi_restore 19
	.cfi_restore 20
	.cfi_restore 21
	.cfi_restore 31
	.end	fast_pptp_to_wan
	.cfi_endproc
$LFE3074:
	.size	fast_pptp_to_wan, .-fast_pptp_to_wan
	.align	2
	.globl	fast_pptp_sync_rx_seq
$LFB3075 = .
	.loc 1 773 0
	.cfi_startproc
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
	.cfi_def_cfa_offset 24
	sw	$31,20($sp)
	.cfi_offset 31, -4
	.loc 1 775 0
	jal	rtl_ip_hdr
	nop

	.loc 1 779 0
	lbu	$3,21($2)
	li	$4,1			# 0x1
	andi	$5,$3,0x7
	bne	$5,$4,$L172
	lw	$31,20($sp)

	.loc 1 779 0 is_stmt 0 discriminator 1
	lhu	$5,22($2)
	li	$4,34827			# 0x880b
	bne	$5,$4,$L172
	nop

	.loc 1 785 0 is_stmt 1
	lbu	$4,20($2)
	andi	$4,$4,0x10
	beq	$4,$0,$L173
	seb	$3,$3

	.loc 1 787 0
	lui	$3,%hi(pptpAccInfo)
	addiu	$3,$3,%lo(pptpAccInfo)
	lw	$4,52($3)
	addiu	$5,$4,1
	sw	$5,52($3)
	lbu	$3,21($2)
	sw	$4,28($2)
	.loc 1 789 0
	seb	$3,$3
$L173:
	bgez	$3,$L172
	lw	$31,20($sp)

	.loc 1 791 0
	lui	$3,%hi(pptpAccInfo+48)
	lw	$3,%lo(pptpAccInfo+48)($3)
	sw	$3,32($2)
	.loc 1 795 0
	lw	$31,20($sp)
$L172:
	j	$31
	addiu	$sp,$sp,24

	.cfi_def_cfa_offset 0
	.cfi_restore 31
	.set	macro
	.set	reorder
	.end	fast_pptp_sync_rx_seq
	.cfi_endproc
$LFE3075:
	.size	fast_pptp_sync_rx_seq, .-fast_pptp_sync_rx_seq
	.align	2
	.globl	pptpconn_write_proc
$LFB3078 = .
	.loc 1 910 0
	.cfi_startproc
	.set	nomips16
	.ent	pptpconn_write_proc
	.type	pptpconn_write_proc, @function
pptpconn_write_proc:
	.frame	$sp,208,$31		# vars= 200, regs= 1/0, args= 0, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	.loc 1 913 0
	sltu	$4,$6,2
	bne	$4,$0,$L184
	.loc 1 916 0
	.set	noreorder
	.set	nomacro
	beq	$5,$0,$L184
	or	$4,$6,$5
	.set	macro
	.set	reorder

	.loc 1 910 0 discriminator 1
	addiu	$sp,$sp,-208
	.cfi_def_cfa_offset 208
$LBB216 = .
$LBB217 = .
	.loc 1 916 0 discriminator 1
	addu	$2,$6,$5
$LBE217 = .
$LBE216 = .
	.loc 1 910 0 discriminator 1
	sw	$31,204($sp)
	.cfi_offset 31, -4
$LBB220 = .
$LBB218 = .
	.loc 1 916 0 discriminator 1
	or	$2,$4,$2
	lw	$4,24($28)
	and	$2,$2,$4
$LBE218 = .
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L185
	lw	$31,204($sp)
	.set	macro
	.set	reorder

$LBB219 = .
	move	$4,$sp
#APP
 # 916 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/fastpath-0.1/fast_pptp_core.c" 1
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
$LBE219 = .
$LBE220 = .
	.set	noreorder
	.set	nomacro
	beq	$6,$0,$L178
	move	$3,$sp
	.set	macro
	.set	reorder

	.loc 1 920 0
	.set	noreorder
	.set	nomacro
	j	$L185
	lw	$31,204($sp)
	.set	macro
	.set	reorder

$L179:
$LBB221 = .
$LBB222 = .
	.loc 1 902 0
	addu	$2,$6,$4
	.loc 1 903 0
	addiu	$3,$3,1
$L178:
	.loc 1 901 0
	lb	$4,0($3)
	.loc 1 902 0
	sll	$7,$2,1
	sll	$6,$2,3
	.loc 1 901 0
	addiu	$5,$4,-48
	andi	$5,$5,0x00ff
	.loc 1 902 0
	addu	$6,$7,$6
	.loc 1 901 0
	sltu	$5,$5,10
	.set	noreorder
	.set	nomacro
	bne	$5,$0,$L179
	addiu	$6,$6,-48
	.set	macro
	.set	reorder

$LBE222 = .
$LBE221 = .
	.loc 1 917 0
	lui	$3,%hi(pptp_conn_check)
	sw	$2,%lo(pptp_conn_check)($3)
	.loc 1 920 0
	lw	$31,204($sp)
$L185:
	li	$2,-14			# 0xfffffffffffffff2
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,208
	.set	macro
	.set	reorder

	.cfi_def_cfa_offset 0
	.cfi_restore 31
$L184:
	.set	noreorder
	.set	nomacro
	j	$31
	li	$2,-14			# 0xfffffffffffffff2
	.set	macro
	.set	reorder

	.end	pptpconn_write_proc
	.cfi_endproc
$LFE3078:
	.size	pptpconn_write_proc, .-pptpconn_write_proc
	.align	2
$LFB3085 = .
	.loc 1 1033 0
	.cfi_startproc
	.set	nomips16
	.ent	pptp_conn_single_write
	.type	pptp_conn_single_write, @function
pptp_conn_single_write:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.loc 1 1034 0
	j	pptpconn_write_proc
	nop

	.set	macro
	.set	reorder
	.end	pptp_conn_single_write
	.cfi_endproc
$LFE3085:
	.size	pptp_conn_single_write, .-pptp_conn_single_write
	.align	2
	.globl	ppfw_write_proc
$LFB3079 = .
	.loc 1 924 0
	.cfi_startproc
	.set	nomips16
	.ent	ppfw_write_proc
	.type	ppfw_write_proc, @function
ppfw_write_proc:
	.frame	$sp,32,$31		# vars= 0, regs= 4/0, args= 16, gp= 0
	.mask	0x80070000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-32
	.cfi_def_cfa_offset 32
	.loc 1 935 0
	sltu	$2,$6,2
	.loc 1 924 0
	sw	$16,16($sp)
	sw	$31,28($sp)
	sw	$18,24($sp)
	sw	$17,20($sp)
	.cfi_offset 16, -16
	.cfi_offset 31, -4
	.cfi_offset 18, -8
	.cfi_offset 17, -12
	.loc 1 935 0
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L203
	move	$16,$6
	.set	macro
	.set	reorder

	move	$18,$5
$LBB223 = .
$LBB224 = .
	.file 5 "include/linux/slub_def.h"
	.loc 5 174 0
	addiu	$4,$6,32
	.set	noreorder
	.set	nomacro
	jal	__kmalloc
	li	$5,32			# 0x20
	.set	macro
	.set	reorder

$LBE224 = .
$LBE223 = .
	.loc 1 939 0
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L203
	move	$17,$2
	.set	macro
	.set	reorder

	.loc 1 942 0
	.set	noreorder
	.set	nomacro
	beq	$18,$0,$L191
	or	$3,$18,$16
	.set	macro
	.set	reorder

$LBB225 = .
$LBB226 = .
	.loc 1 942 0 is_stmt 0 discriminator 1
	addu	$2,$18,$16
	or	$2,$3,$2
	lw	$3,24($28)
	and	$2,$2,$3
$LBE226 = .
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L191
	move	$4,$17
	.set	macro
	.set	reorder

$LBB227 = .
	move	$5,$18
	move	$6,$16
#APP
 # 942 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/fastpath-0.1/fast_pptp_core.c" 1
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
$LBE227 = .
$LBE225 = .
	.set	noreorder
	.set	nomacro
	bne	$6,$0,$L191
	move	$5,$17
	.set	macro
	.set	reorder

	.loc 1 942 0
	.set	noreorder
	.set	nomacro
	j	$L192
	move	$3,$0
	.set	macro
	.set	reorder

$L193:
$LBB228 = .
$LBB229 = .
	.loc 1 902 0 is_stmt 1
	addu	$3,$9,$7
	.loc 1 903 0
	addiu	$5,$5,1
$L192:
	.loc 1 901 0
	lb	$7,0($5)
	.loc 1 902 0
	sll	$2,$3,1
	sll	$9,$3,3
	.loc 1 901 0
	addiu	$8,$7,-48
	andi	$8,$8,0x00ff
	.loc 1 902 0
	addu	$9,$2,$9
	.loc 1 901 0
	sltu	$8,$8,10
	.set	noreorder
	.set	nomacro
	bne	$8,$0,$L193
	addiu	$9,$9,-48
	.set	macro
	.set	reorder

$LBE229 = .
$LBE228 = .
$LBB230 = .
	.loc 1 946 0
	lui	$4,%hi(pptpAccInfo)
$LBE230 = .
	.loc 1 943 0
	lui	$18,%hi(fast_pptp_fw)
$LBB231 = .
	.loc 1 946 0
	addiu	$4,$4,%lo(pptpAccInfo)
	move	$5,$0
	li	$6,64			# 0x40
	.set	noreorder
	.set	nomacro
	jal	memset
	sw	$3,%lo(fast_pptp_fw)($18)
	.set	macro
	.set	reorder

$LBE231 = .
	.loc 1 973 0
	lw	$2,%lo(fast_pptp_fw)($18)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L194
	lui	$3,%hi(sync_tx_pptp_gre_seqno)
	.set	macro
	.set	reorder

	.loc 1 975 0
	addiu	$3,$3,%lo(sync_tx_pptp_gre_seqno)
	lui	$2,%hi(sync_tx_pptp_gre_seqno_hook)
	.set	noreorder
	.set	nomacro
	j	$L195
	sw	$3,%lo(sync_tx_pptp_gre_seqno_hook)($2)
	.set	macro
	.set	reorder

$L194:
	.loc 1 979 0
	lui	$2,%hi(sync_tx_pptp_gre_seqno_hook)
	sw	$0,%lo(sync_tx_pptp_gre_seqno_hook)($2)
$L195:
	.loc 1 982 0
	.set	noreorder
	.set	nomacro
	jal	kfree
	move	$4,$17
	.set	macro
	.set	reorder

	.loc 1 983 0
	.set	noreorder
	.set	nomacro
	j	$L189
	move	$2,$16
	.set	macro
	.set	reorder

$L191:
	.loc 1 986 0
	.set	noreorder
	.set	nomacro
	jal	kfree
	move	$4,$17
	.set	macro
	.set	reorder

$L203:
	.loc 1 987 0
	li	$2,-14			# 0xfffffffffffffff2
$L189:
	.loc 1 988 0
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

	.cfi_def_cfa_offset 0
	.cfi_restore 16
	.cfi_restore 17
	.cfi_restore 18
	.cfi_restore 31
	.end	ppfw_write_proc
	.cfi_endproc
$LFE3079:
	.size	ppfw_write_proc, .-ppfw_write_proc
	.align	2
$LFB3083 = .
	.loc 1 1013 0
	.cfi_startproc
	.set	nomips16
	.ent	fastpath_pptp_single_write
	.type	fastpath_pptp_single_write, @function
fastpath_pptp_single_write:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.loc 1 1014 0
	j	ppfw_write_proc
	nop

	.set	macro
	.set	reorder
	.end	fastpath_pptp_single_write
	.cfi_endproc
$LFE3083:
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
$LFB3086 = .
	.loc 1 1087 0
	.cfi_startproc
	.set	nomips16
	.ent	fast_pptp_init
	.type	fast_pptp_init, @function
fast_pptp_init:
	.frame	$sp,32,$31		# vars= 0, regs= 2/0, args= 24, gp= 0
	.mask	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.loc 1 1088 0
	lui	$3,%hi(set_pptp_device)
	.loc 1 1087 0
	addiu	$sp,$sp,-32
	.cfi_def_cfa_offset 32
	.loc 1 1088 0
	addiu	$3,$3,%lo(set_pptp_device)
	lui	$2,%hi(set_pptp_device_fphook)
	sw	$3,%lo(set_pptp_device_fphook)($2)
	.loc 1 1087 0
	sw	$16,24($sp)
	.loc 1 1093 0
	lui	$4,%hi($LC5)
	.cfi_offset 16, -8
	lui	$16,%hi(proc_root)
	lui	$7,%hi(fastpath_pptp_proc_fops)
	.loc 1 1089 0
	lui	$3,%hi(get_fastpptp_lastxmit)
	.loc 1 1093 0
	addiu	$6,$16,%lo(proc_root)
	.loc 1 1089 0
	addiu	$3,$3,%lo(get_fastpptp_lastxmit)
	.loc 1 1093 0
	addiu	$4,$4,%lo($LC5)
	move	$5,$0
	addiu	$7,$7,%lo(fastpath_pptp_proc_fops)
	sw	$0,16($sp)
	.loc 1 1089 0
	lui	$2,%hi(get_fastpptp_lastxmit_fphook)
	.loc 1 1087 0
	sw	$31,28($sp)
	.cfi_offset 31, -4
	.loc 1 1093 0
	jal	proc_create_data
	sw	$3,%lo(get_fastpptp_lastxmit_fphook)($2)

	.loc 1 1096 0
	lui	$4,%hi($LC6)
	lui	$7,%hi(pptp_conn_proc_fops)
	addiu	$6,$16,%lo(proc_root)
	.loc 1 1093 0
	lui	$3,%hi(res1)
	.loc 1 1096 0
	addiu	$4,$4,%lo($LC6)
	move	$5,$0
	addiu	$7,$7,%lo(pptp_conn_proc_fops)
	sw	$0,16($sp)
	jal	proc_create_data
	sw	$2,%lo(res1)($3)

$LBB232 = .
	.loc 1 1113 0
	lui	$4,%hi(pptpAccInfo)
$LBE232 = .
	.loc 1 1096 0
	lui	$3,%hi(res_check_pptp)
$LBB233 = .
	.loc 1 1113 0
	addiu	$4,$4,%lo(pptpAccInfo)
	move	$5,$0
	li	$6,64			# 0x40
	jal	memset
	sw	$2,%lo(res_check_pptp)($3)

$LBE233 = .
	.loc 1 1115 0
	lw	$31,28($sp)
	lw	$16,24($sp)
	move	$2,$0
	j	$31
	addiu	$sp,$sp,32

	.cfi_def_cfa_offset 0
	.cfi_restore 16
	.cfi_restore 31
	.set	macro
	.set	reorder
	.end	fast_pptp_init
	.cfi_endproc
$LFE3086:
	.size	fast_pptp_init, .-fast_pptp_init
	.section	.exit.text,"ax",@progbits
	.align	2
	.globl	fast_pptp_exit
$LFB3087 = .
	.loc 1 1122 0
	.cfi_startproc
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
	.cfi_def_cfa_offset 24
	sw	$16,16($sp)
	.cfi_offset 16, -8
	.loc 1 1127 0
	lui	$16,%hi(res1)
	.loc 1 1123 0
	lui	$3,%hi(set_pptp_device_fphook)
	.loc 1 1127 0
	lw	$2,%lo(res1)($16)
	.loc 1 1123 0
	sw	$0,%lo(set_pptp_device_fphook)($3)
	.loc 1 1124 0
	lui	$3,%hi(get_fastpptp_lastxmit_fphook)
	sw	$0,%lo(get_fastpptp_lastxmit_fphook)($3)
	.loc 1 1125 0
	lui	$3,%hi(fast_pptp_fw)
	.loc 1 1122 0
	sw	$31,20($sp)
	.cfi_offset 31, -4
	.loc 1 1127 0
	beq	$2,$0,$L208
	sw	$0,%lo(fast_pptp_fw)($3)

	.loc 1 1129 0
	lui	$4,%hi($LC5)
	lui	$5,%hi(proc_root)
	addiu	$4,$4,%lo($LC5)
	jal	remove_proc_entry
	addiu	$5,$5,%lo(proc_root)

	.loc 1 1133 0
	sw	$0,%lo(res1)($16)
$L208:
	.loc 1 1136 0
	lui	$16,%hi(res_check_pptp)
	lw	$2,%lo(res_check_pptp)($16)
	beq	$2,$0,$L207
	lui	$4,%hi($LC6)

	.loc 1 1138 0
	lui	$5,%hi(proc_root)
	addiu	$4,$4,%lo($LC6)
	jal	remove_proc_entry
	addiu	$5,$5,%lo(proc_root)

	.loc 1 1142 0
	sw	$0,%lo(res_check_pptp)($16)
$L207:
	.loc 1 1145 0
	lw	$31,20($sp)
	lw	$16,16($sp)
	j	$31
	addiu	$sp,$sp,24

	.cfi_def_cfa_offset 0
	.cfi_restore 16
	.cfi_restore 31
	.set	macro
	.set	reorder
	.end	fast_pptp_exit
	.cfi_endproc
$LFE3087:
	.size	fast_pptp_exit, .-fast_pptp_exit
	.local	res_check_pptp
	.comm	res_check_pptp,4,4
	.local	res1
	.comm	res1,4,4
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
	.local	pptp_conn_check
	.comm	pptp_conn_check,4,4
	.globl	pptp_tcp_finished
	.section	.bss,"aw",@nobits
	.align	2
	.type	pptp_tcp_finished, @object
	.size	pptp_tcp_finished, 4
pptp_tcp_finished:
	.space	4
	.local	pptpAccInfo
	.comm	pptpAccInfo,64,4
	.text
$Letext0:
	.file 6 "include/uapi/asm-generic/int-ll64.h"
	.file 7 "include/asm-generic/int-ll64.h"
	.file 8 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/linux-3.10.49/include/uapi/asm-generic/posix_types.h"
	.file 9 "include/uapi/linux/types.h"
	.file 10 "include/linux/types.h"
	.file 11 "include/asm-generic/atomic-long.h"
	.file 12 "include/linux/seqlock.h"
	.file 13 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/linux-3.10.49/arch/mips/include/asm/page.h"
	.file 14 "include/uapi/linux/in.h"
	.file 15 "include/uapi/linux/if_link.h"
	.file 16 "include/uapi/linux/rtnetlink.h"
	.file 17 "include/net/ndisc.h"
	.file 18 "include/linux/inetdevice.h"
	.file 19 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/linux-3.10.49/arch/mips/include/asm/bitops.h"
	.file 20 "include/linux/kmemleak.h"
	.file 21 "include/linux/log2.h"
	.file 22 "include/asm-generic/getorder.h"
	.file 23 "include/linux/slab.h"
	.file 24 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/linux-3.10.49/arch/mips/include/asm/thread_info.h"
	.file 25 "include/net/inet_frag.h"
	.file 26 "include/linux/etherdevice.h"
	.file 27 "include/linux/export.h"
	.file 28 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/linux-3.10.49/arch/mips/include/asm/cpu-info.h"
	.file 29 "include/linux/printk.h"
	.file 30 "include/linux/kernel.h"
	.file 31 "include/linux/cpumask.h"
	.file 32 "include/linux/time.h"
	.file 33 "include/linux/highuid.h"
	.file 34 "include/linux/seq_file.h"
	.file 35 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/linux-3.10.49/arch/mips/include/asm/io.h"
	.file 36 "include/linux/mm.h"
	.file 37 "include/linux/mmzone.h"
	.file 38 "include/linux/jiffies.h"
	.file 39 "include/linux/workqueue.h"
	.file 40 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/linux-3.10.49/arch/mips/include/asm/smp.h"
	.file 41 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/linux-3.10.49/arch/mips/include/asm/smp-ops.h"
	.file 42 "include/asm-generic/percpu.h"
	.file 43 "include/linux/sched.h"
	.file 44 "include/linux/percpu_counter.h"
	.file 45 "include/linux/quota.h"
	.file 46 "include/linux/interrupt.h"
	.file 47 "include/linux/kernel_stat.h"
	.file 48 "include/linux/ioport.h"
	.file 49 "include/linux/debug_locks.h"
	.file 50 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/linux-3.10.49/arch/mips/include/asm/pgtable-32.h"
	.file 51 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/linux-3.10.49/arch/mips/include/asm/pgtable.h"
	.file 52 "include/asm-generic/pgtable.h"
	.file 53 "include/linux/vmstat.h"
	.file 54 "include/linux/netfilter.h"
	.file 55 "include/net/net_namespace.h"
	.file 56 "include/linux/netdevice.h"
	.file 57 "include/net/sock.h"
	.file 58 "include/net/inet_sock.h"
	.file 59 "include/net/ip.h"
	.file 60 "include/net/inet_connection_sock.h"
	.file 61 "include/net/route.h"
	.file 62 "include/net/arp.h"
	.file 63 "include/linux/netfilter/x_tables.h"
	.file 64 "include/net/rtl/fastpath/fastpath_core.h"
	.file 65 "include/uapi/linux/netfilter.h"
	.file 66 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/linux-rtkmips_rtl8198c/linux-3.10.49/arch/mips/include/asm/bug.h"
	.section	.debug_info,"",@progbits
$Ldebug_info0:
	.4byte	0x18f1
	.2byte	0x4
	.4byte	$Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	$LASF349
	.byte	0x1
	.4byte	$LASF350
	.4byte	$LASF351
	.4byte	$Ldebug_ranges0+0x260
	.4byte	0
	.4byte	$Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	$LASF0
	.uleb128 0x3
	.4byte	$LASF3
	.byte	0x6
	.byte	0x14
	.4byte	0x37
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	$LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	$LASF2
	.uleb128 0x3
	.4byte	$LASF4
	.byte	0x6
	.byte	0x17
	.4byte	0x50
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	$LASF5
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x3
	.4byte	$LASF6
	.byte	0x6
	.byte	0x1a
	.4byte	0x69
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	$LASF7
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	$LASF8
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	$LASF9
	.uleb128 0x5
	.ascii	"u8\000"
	.byte	0x7
	.byte	0x10
	.4byte	0x37
	.uleb128 0x5
	.ascii	"u16\000"
	.byte	0x7
	.byte	0x13
	.4byte	0x50
	.uleb128 0x5
	.ascii	"u32\000"
	.byte	0x7
	.byte	0x16
	.4byte	0x69
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	$LASF10
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	$LASF11
	.uleb128 0x3
	.4byte	$LASF12
	.byte	0x8
	.byte	0x43
	.4byte	0x69
	.uleb128 0x3
	.4byte	$LASF13
	.byte	0x8
	.byte	0x44
	.4byte	0x57
	.uleb128 0x3
	.4byte	$LASF14
	.byte	0x8
	.byte	0x57
	.4byte	0x70
	.uleb128 0x6
	.byte	0x4
	.4byte	0xd3
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	$LASF15
	.uleb128 0x3
	.4byte	$LASF16
	.byte	0x9
	.byte	0x21
	.4byte	0x45
	.uleb128 0x3
	.4byte	$LASF17
	.byte	0x9
	.byte	0x23
	.4byte	0x5e
	.uleb128 0x3
	.4byte	$LASF18
	.byte	0x9
	.byte	0x27
	.4byte	0x45
	.uleb128 0x3
	.4byte	$LASF19
	.byte	0x9
	.byte	0x28
	.4byte	0x5e
	.uleb128 0x3
	.4byte	$LASF20
	.byte	0xa
	.byte	0x1d
	.4byte	0x111
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.4byte	$LASF21
	.uleb128 0x3
	.4byte	$LASF22
	.byte	0xa
	.byte	0x2d
	.4byte	0xc2
	.uleb128 0x3
	.4byte	$LASF23
	.byte	0xa
	.byte	0x36
	.4byte	0xac
	.uleb128 0x3
	.4byte	$LASF24
	.byte	0xa
	.byte	0x3b
	.4byte	0xb7
	.uleb128 0x3
	.4byte	$LASF25
	.byte	0xa
	.byte	0x9d
	.4byte	0x69
	.uleb128 0x7
	.uleb128 0x3
	.4byte	$LASF26
	.byte	0xa
	.byte	0xb1
	.4byte	0x144
	.uleb128 0x8
	.4byte	$LASF27
	.uleb128 0x8
	.4byte	$LASF28
	.uleb128 0x8
	.4byte	$LASF29
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	$LASF30
	.uleb128 0x8
	.4byte	$LASF31
	.uleb128 0x3
	.4byte	$LASF32
	.byte	0xb
	.byte	0x8d
	.4byte	0x145
	.uleb128 0x8
	.4byte	$LASF33
	.uleb128 0x3
	.4byte	$LASF34
	.byte	0xc
	.byte	0x29
	.4byte	0x176
	.uleb128 0x9
	.byte	0x4
	.uleb128 0x7
	.uleb128 0x3
	.4byte	$LASF35
	.byte	0xd
	.byte	0x69
	.4byte	0x188
	.uleb128 0x6
	.byte	0x4
	.4byte	0x19a
	.uleb128 0x8
	.4byte	$LASF36
	.uleb128 0x8
	.4byte	$LASF37
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1aa
	.uleb128 0xa
	.4byte	0x1b5
	.uleb128 0xb
	.4byte	0x186
	.byte	0
	.uleb128 0x8
	.4byte	$LASF38
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1c0
	.uleb128 0xa
	.4byte	0x1cb
	.uleb128 0xb
	.4byte	0x9e
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x118
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.4byte	$LASF39
	.uleb128 0x8
	.4byte	$LASF40
	.uleb128 0x8
	.4byte	$LASF41
	.uleb128 0xc
	.ascii	"pid\000"
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1ed
	.uleb128 0x8
	.4byte	$LASF42
	.uleb128 0x8
	.4byte	$LASF43
	.uleb128 0x8
	.4byte	$LASF44
	.uleb128 0x6
	.byte	0x4
	.4byte	0x202
	.uleb128 0xd
	.4byte	0xd3
	.uleb128 0x8
	.4byte	$LASF45
	.uleb128 0x8
	.4byte	$LASF46
	.uleb128 0x8
	.4byte	$LASF47
	.uleb128 0x8
	.4byte	$LASF48
	.uleb128 0x8
	.4byte	$LASF49
	.uleb128 0x6
	.byte	0x4
	.4byte	0x37
	.uleb128 0x8
	.4byte	$LASF50
	.uleb128 0x8
	.4byte	$LASF51
	.uleb128 0xe
	.byte	0x4
	.byte	0xe
	.byte	0x19
	.4byte	0x2c4
	.uleb128 0xf
	.4byte	$LASF52
	.sleb128 0
	.uleb128 0xf
	.4byte	$LASF53
	.sleb128 1
	.uleb128 0xf
	.4byte	$LASF54
	.sleb128 2
	.uleb128 0xf
	.4byte	$LASF55
	.sleb128 4
	.uleb128 0xf
	.4byte	$LASF56
	.sleb128 6
	.uleb128 0xf
	.4byte	$LASF57
	.sleb128 8
	.uleb128 0xf
	.4byte	$LASF58
	.sleb128 12
	.uleb128 0xf
	.4byte	$LASF59
	.sleb128 17
	.uleb128 0xf
	.4byte	$LASF60
	.sleb128 22
	.uleb128 0xf
	.4byte	$LASF61
	.sleb128 33
	.uleb128 0xf
	.4byte	$LASF62
	.sleb128 46
	.uleb128 0xf
	.4byte	$LASF63
	.sleb128 47
	.uleb128 0xf
	.4byte	$LASF64
	.sleb128 41
	.uleb128 0xf
	.4byte	$LASF65
	.sleb128 50
	.uleb128 0xf
	.4byte	$LASF66
	.sleb128 51
	.uleb128 0xf
	.4byte	$LASF67
	.sleb128 94
	.uleb128 0xf
	.4byte	$LASF68
	.sleb128 103
	.uleb128 0xf
	.4byte	$LASF69
	.sleb128 108
	.uleb128 0xf
	.4byte	$LASF70
	.sleb128 132
	.uleb128 0xf
	.4byte	$LASF71
	.sleb128 136
	.uleb128 0xf
	.4byte	$LASF72
	.sleb128 255
	.uleb128 0xf
	.4byte	$LASF73
	.sleb128 256
	.byte	0
	.uleb128 0x10
	.4byte	$LASF352
	.byte	0x4
	.byte	0x41
	.byte	0x2d
	.4byte	0x2f5
	.uleb128 0xf
	.4byte	$LASF74
	.sleb128 0
	.uleb128 0xf
	.4byte	$LASF75
	.sleb128 1
	.uleb128 0xf
	.4byte	$LASF76
	.sleb128 2
	.uleb128 0xf
	.4byte	$LASF77
	.sleb128 3
	.uleb128 0xf
	.4byte	$LASF78
	.sleb128 4
	.uleb128 0xf
	.4byte	$LASF79
	.sleb128 5
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x226
	.uleb128 0x8
	.4byte	$LASF80
	.uleb128 0x8
	.4byte	$LASF81
	.uleb128 0xc
	.ascii	"net\000"
	.uleb128 0x8
	.4byte	$LASF82
	.uleb128 0xe
	.byte	0x4
	.byte	0xf
	.byte	0x65
	.4byte	0x3ea
	.uleb128 0xf
	.4byte	$LASF83
	.sleb128 0
	.uleb128 0xf
	.4byte	$LASF84
	.sleb128 1
	.uleb128 0xf
	.4byte	$LASF85
	.sleb128 2
	.uleb128 0xf
	.4byte	$LASF86
	.sleb128 3
	.uleb128 0xf
	.4byte	$LASF87
	.sleb128 4
	.uleb128 0xf
	.4byte	$LASF88
	.sleb128 5
	.uleb128 0xf
	.4byte	$LASF89
	.sleb128 6
	.uleb128 0xf
	.4byte	$LASF90
	.sleb128 7
	.uleb128 0xf
	.4byte	$LASF91
	.sleb128 8
	.uleb128 0xf
	.4byte	$LASF92
	.sleb128 9
	.uleb128 0xf
	.4byte	$LASF93
	.sleb128 10
	.uleb128 0xf
	.4byte	$LASF94
	.sleb128 11
	.uleb128 0xf
	.4byte	$LASF95
	.sleb128 12
	.uleb128 0xf
	.4byte	$LASF96
	.sleb128 13
	.uleb128 0xf
	.4byte	$LASF97
	.sleb128 14
	.uleb128 0xf
	.4byte	$LASF98
	.sleb128 15
	.uleb128 0xf
	.4byte	$LASF99
	.sleb128 16
	.uleb128 0xf
	.4byte	$LASF100
	.sleb128 17
	.uleb128 0xf
	.4byte	$LASF101
	.sleb128 18
	.uleb128 0xf
	.4byte	$LASF102
	.sleb128 19
	.uleb128 0xf
	.4byte	$LASF103
	.sleb128 20
	.uleb128 0xf
	.4byte	$LASF104
	.sleb128 21
	.uleb128 0xf
	.4byte	$LASF105
	.sleb128 22
	.uleb128 0xf
	.4byte	$LASF106
	.sleb128 23
	.uleb128 0xf
	.4byte	$LASF107
	.sleb128 24
	.uleb128 0xf
	.4byte	$LASF108
	.sleb128 25
	.uleb128 0xf
	.4byte	$LASF109
	.sleb128 26
	.uleb128 0xf
	.4byte	$LASF110
	.sleb128 27
	.uleb128 0xf
	.4byte	$LASF111
	.sleb128 28
	.uleb128 0xf
	.4byte	$LASF112
	.sleb128 29
	.uleb128 0xf
	.4byte	$LASF113
	.sleb128 30
	.uleb128 0xf
	.4byte	$LASF114
	.sleb128 31
	.uleb128 0xf
	.4byte	$LASF115
	.sleb128 32
	.uleb128 0xf
	.4byte	$LASF116
	.sleb128 33
	.uleb128 0xf
	.4byte	$LASF117
	.sleb128 34
	.byte	0
	.uleb128 0x8
	.4byte	$LASF118
	.uleb128 0x8
	.4byte	$LASF119
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1f7
	.uleb128 0x11
	.byte	0x4
	.byte	0x10
	.2byte	0x167
	.4byte	0x464
	.uleb128 0xf
	.4byte	$LASF120
	.sleb128 0
	.uleb128 0xf
	.4byte	$LASF121
	.sleb128 1
	.uleb128 0xf
	.4byte	$LASF122
	.sleb128 2
	.uleb128 0xf
	.4byte	$LASF123
	.sleb128 3
	.uleb128 0xf
	.4byte	$LASF124
	.sleb128 4
	.uleb128 0xf
	.4byte	$LASF125
	.sleb128 5
	.uleb128 0xf
	.4byte	$LASF126
	.sleb128 6
	.uleb128 0xf
	.4byte	$LASF127
	.sleb128 7
	.uleb128 0xf
	.4byte	$LASF128
	.sleb128 8
	.uleb128 0xf
	.4byte	$LASF129
	.sleb128 9
	.uleb128 0xf
	.4byte	$LASF130
	.sleb128 10
	.uleb128 0xf
	.4byte	$LASF131
	.sleb128 11
	.uleb128 0xf
	.4byte	$LASF132
	.sleb128 12
	.uleb128 0xf
	.4byte	$LASF133
	.sleb128 13
	.uleb128 0xf
	.4byte	$LASF134
	.sleb128 14
	.uleb128 0xf
	.4byte	$LASF135
	.sleb128 15
	.byte	0
	.uleb128 0x8
	.4byte	$LASF136
	.uleb128 0x8
	.4byte	$LASF137
	.uleb128 0xe
	.byte	0x4
	.byte	0x11
	.byte	0x1b
	.4byte	0x4b9
	.uleb128 0xf
	.4byte	$LASF138
	.sleb128 0
	.uleb128 0xf
	.4byte	$LASF139
	.sleb128 1
	.uleb128 0xf
	.4byte	$LASF140
	.sleb128 2
	.uleb128 0xf
	.4byte	$LASF141
	.sleb128 3
	.uleb128 0xf
	.4byte	$LASF142
	.sleb128 4
	.uleb128 0xf
	.4byte	$LASF143
	.sleb128 5
	.uleb128 0xf
	.4byte	$LASF144
	.sleb128 6
	.uleb128 0xf
	.4byte	$LASF145
	.sleb128 24
	.uleb128 0xf
	.4byte	$LASF146
	.sleb128 25
	.uleb128 0xf
	.4byte	$LASF147
	.sleb128 31
	.uleb128 0xf
	.4byte	$LASF148
	.sleb128 32
	.byte	0
	.uleb128 0x8
	.4byte	$LASF149
	.uleb128 0x8
	.4byte	$LASF150
	.uleb128 0x8
	.4byte	$LASF151
	.uleb128 0x8
	.4byte	$LASF152
	.uleb128 0x8
	.4byte	$LASF153
	.uleb128 0x8
	.4byte	$LASF154
	.uleb128 0x8
	.4byte	$LASF155
	.uleb128 0x8
	.4byte	$LASF156
	.uleb128 0xe
	.byte	0x4
	.byte	0x12
	.byte	0xf
	.4byte	0x58c
	.uleb128 0xf
	.4byte	$LASF157
	.sleb128 1
	.uleb128 0xf
	.4byte	$LASF158
	.sleb128 2
	.uleb128 0xf
	.4byte	$LASF159
	.sleb128 3
	.uleb128 0xf
	.4byte	$LASF160
	.sleb128 4
	.uleb128 0xf
	.4byte	$LASF161
	.sleb128 5
	.uleb128 0xf
	.4byte	$LASF162
	.sleb128 6
	.uleb128 0xf
	.4byte	$LASF163
	.sleb128 7
	.uleb128 0xf
	.4byte	$LASF164
	.sleb128 8
	.uleb128 0xf
	.4byte	$LASF165
	.sleb128 9
	.uleb128 0xf
	.4byte	$LASF166
	.sleb128 10
	.uleb128 0xf
	.4byte	$LASF167
	.sleb128 11
	.uleb128 0xf
	.4byte	$LASF168
	.sleb128 12
	.uleb128 0xf
	.4byte	$LASF169
	.sleb128 13
	.uleb128 0xf
	.4byte	$LASF170
	.sleb128 14
	.uleb128 0xf
	.4byte	$LASF171
	.sleb128 15
	.uleb128 0xf
	.4byte	$LASF172
	.sleb128 16
	.uleb128 0xf
	.4byte	$LASF173
	.sleb128 17
	.uleb128 0xf
	.4byte	$LASF174
	.sleb128 18
	.uleb128 0xf
	.4byte	$LASF175
	.sleb128 19
	.uleb128 0xf
	.4byte	$LASF176
	.sleb128 20
	.uleb128 0xf
	.4byte	$LASF177
	.sleb128 21
	.uleb128 0xf
	.4byte	$LASF178
	.sleb128 22
	.uleb128 0xf
	.4byte	$LASF179
	.sleb128 23
	.uleb128 0xf
	.4byte	$LASF180
	.sleb128 24
	.uleb128 0xf
	.4byte	$LASF181
	.sleb128 25
	.uleb128 0xf
	.4byte	$LASF182
	.sleb128 26
	.uleb128 0xf
	.4byte	$LASF183
	.sleb128 27
	.byte	0
	.uleb128 0x12
	.ascii	"fls\000"
	.byte	0x13
	.2byte	0x234
	.4byte	0x57
	.byte	0x3
	.4byte	0x5b2
	.uleb128 0x13
	.ascii	"x\000"
	.byte	0x13
	.2byte	0x234
	.4byte	0x57
	.uleb128 0x14
	.ascii	"r\000"
	.byte	0x13
	.2byte	0x236
	.4byte	0x57
	.byte	0
	.uleb128 0x15
	.ascii	"BUG\000"
	.byte	0x42
	.byte	0xb
	.byte	0x3
	.uleb128 0x16
	.4byte	$LASF198
	.byte	0x14
	.byte	0x40
	.byte	0x3
	.4byte	0x5f3
	.uleb128 0x17
	.ascii	"ptr\000"
	.byte	0x14
	.byte	0x40
	.4byte	0x5f3
	.uleb128 0x18
	.4byte	$LASF184
	.byte	0x14
	.byte	0x40
	.4byte	0x123
	.uleb128 0x18
	.4byte	$LASF185
	.byte	0x14
	.byte	0x40
	.4byte	0x57
	.uleb128 0x17
	.ascii	"gfp\000"
	.byte	0x14
	.byte	0x41
	.4byte	0x139
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x5f9
	.uleb128 0x19
	.uleb128 0x1a
	.4byte	$LASF186
	.byte	0x5
	.byte	0x6f
	.4byte	0x186
	.byte	0x3
	.4byte	0x637
	.uleb128 0x18
	.4byte	$LASF184
	.byte	0x5
	.byte	0x6f
	.4byte	0x123
	.uleb128 0x18
	.4byte	$LASF187
	.byte	0x5
	.byte	0x6f
	.4byte	0x139
	.uleb128 0x18
	.4byte	$LASF188
	.byte	0x5
	.byte	0x6f
	.4byte	0x69
	.uleb128 0x1b
	.ascii	"ret\000"
	.byte	0x5
	.byte	0x71
	.4byte	0x186
	.byte	0
	.uleb128 0x1a
	.4byte	$LASF189
	.byte	0x5
	.byte	0x8c
	.4byte	0x186
	.byte	0x3
	.4byte	0x667
	.uleb128 0x17
	.ascii	"s\000"
	.byte	0x5
	.byte	0x8c
	.4byte	0x667
	.uleb128 0x18
	.4byte	$LASF190
	.byte	0x5
	.byte	0x8c
	.4byte	0x139
	.uleb128 0x18
	.4byte	$LASF184
	.byte	0x5
	.byte	0x8c
	.4byte	0x123
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x216
	.uleb128 0x1a
	.4byte	$LASF191
	.byte	0x5
	.byte	0x92
	.4byte	0x186
	.byte	0x3
	.4byte	0x69f
	.uleb128 0x18
	.4byte	$LASF184
	.byte	0x5
	.byte	0x92
	.4byte	0x123
	.uleb128 0x18
	.4byte	$LASF187
	.byte	0x5
	.byte	0x92
	.4byte	0x139
	.uleb128 0x18
	.4byte	$LASF188
	.byte	0x5
	.byte	0x92
	.4byte	0x69
	.byte	0
	.uleb128 0x1a
	.4byte	$LASF192
	.byte	0x15
	.byte	0x20
	.4byte	0x57
	.byte	0x3
	.4byte	0x6b9
	.uleb128 0x17
	.ascii	"n\000"
	.byte	0x15
	.byte	0x20
	.4byte	0x93
	.byte	0
	.uleb128 0x1a
	.4byte	$LASF193
	.byte	0x16
	.byte	0xd
	.4byte	0x57
	.byte	0x3
	.4byte	0x6e0
	.uleb128 0x18
	.4byte	$LASF184
	.byte	0x16
	.byte	0xd
	.4byte	0x9e
	.uleb128 0x1c
	.4byte	$LASF188
	.byte	0x16
	.byte	0xf
	.4byte	0x57
	.byte	0
	.uleb128 0x1a
	.4byte	$LASF194
	.byte	0x5
	.byte	0x98
	.4byte	0x186
	.byte	0x3
	.4byte	0x712
	.uleb128 0x18
	.4byte	$LASF184
	.byte	0x5
	.byte	0x98
	.4byte	0x123
	.uleb128 0x18
	.4byte	$LASF187
	.byte	0x5
	.byte	0x98
	.4byte	0x139
	.uleb128 0x1c
	.4byte	$LASF188
	.byte	0x5
	.byte	0x9a
	.4byte	0x69
	.byte	0
	.uleb128 0x1a
	.4byte	$LASF195
	.byte	0x17
	.byte	0xed
	.4byte	0x57
	.byte	0x3
	.4byte	0x72e
	.uleb128 0x18
	.4byte	$LASF184
	.byte	0x17
	.byte	0xed
	.4byte	0x123
	.byte	0
	.uleb128 0x1a
	.4byte	$LASF196
	.byte	0x3
	.byte	0x4c
	.4byte	0xf0
	.byte	0x3
	.4byte	0x74a
	.uleb128 0x17
	.ascii	"sum\000"
	.byte	0x3
	.byte	0x4c
	.4byte	0xfb
	.byte	0
	.uleb128 0x1d
	.4byte	$LASF353
	.byte	0x1
	.2byte	0x285
	.4byte	0x9e
	.byte	0x1
	.uleb128 0x1a
	.4byte	$LASF197
	.byte	0x2
	.byte	0x23
	.4byte	0x9e
	.byte	0x3
	.4byte	0x773
	.uleb128 0x1c
	.4byte	$LASF187
	.byte	0x2
	.byte	0x25
	.4byte	0x9e
	.byte	0
	.uleb128 0x16
	.4byte	$LASF199
	.byte	0x1
	.byte	0x5a
	.byte	0x3
	.4byte	0x7aa
	.uleb128 0x17
	.ascii	"dst\000"
	.byte	0x1
	.byte	0x5a
	.4byte	0x220
	.uleb128 0x17
	.ascii	"src\000"
	.byte	0x1
	.byte	0x5a
	.4byte	0x220
	.uleb128 0x17
	.ascii	"len\000"
	.byte	0x1
	.byte	0x5a
	.4byte	0x57
	.uleb128 0x1b
	.ascii	"i\000"
	.byte	0x1
	.byte	0x5b
	.4byte	0x57
	.byte	0
	.uleb128 0x1a
	.4byte	$LASF200
	.byte	0x3
	.byte	0x65
	.4byte	0xf0
	.byte	0x3
	.4byte	0x7fd
	.uleb128 0x17
	.ascii	"iph\000"
	.byte	0x3
	.byte	0x65
	.4byte	0x5f3
	.uleb128 0x17
	.ascii	"ihl\000"
	.byte	0x3
	.byte	0x65
	.4byte	0x69
	.uleb128 0x1c
	.4byte	$LASF201
	.byte	0x3
	.byte	0x67
	.4byte	0x7fd
	.uleb128 0x1c
	.4byte	$LASF202
	.byte	0x3
	.byte	0x68
	.4byte	0x7fd
	.uleb128 0x1c
	.4byte	$LASF203
	.byte	0x3
	.byte	0x69
	.4byte	0x69
	.uleb128 0x1c
	.4byte	$LASF204
	.byte	0x3
	.byte	0x6a
	.4byte	0x57
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x803
	.uleb128 0xd
	.4byte	0x69
	.uleb128 0x1a
	.4byte	$LASF205
	.byte	0x2
	.byte	0xb2
	.4byte	0x57
	.byte	0x3
	.4byte	0x824
	.uleb128 0x18
	.4byte	$LASF187
	.byte	0x2
	.byte	0xb2
	.4byte	0x9e
	.byte	0
	.uleb128 0x16
	.4byte	$LASF206
	.byte	0x2
	.byte	0x36
	.byte	0x3
	.4byte	0x847
	.uleb128 0x18
	.4byte	$LASF187
	.byte	0x2
	.byte	0x36
	.4byte	0x9e
	.uleb128 0x1c
	.4byte	$LASF207
	.byte	0x2
	.byte	0x38
	.4byte	0x9e
	.byte	0
	.uleb128 0x16
	.4byte	$LASF208
	.byte	0x1
	.byte	0x50
	.byte	0x1
	.4byte	0x85f
	.uleb128 0x18
	.4byte	$LASF209
	.byte	0x1
	.byte	0x50
	.4byte	0xcd
	.byte	0
	.uleb128 0x1a
	.4byte	$LASF210
	.byte	0x4
	.byte	0x49
	.4byte	0x57
	.byte	0x3
	.4byte	0x891
	.uleb128 0x18
	.4byte	$LASF211
	.byte	0x4
	.byte	0x49
	.4byte	0x1fc
	.uleb128 0x18
	.4byte	$LASF212
	.byte	0x4
	.byte	0x49
	.4byte	0x1fc
	.uleb128 0x1c
	.4byte	$LASF213
	.byte	0x4
	.byte	0x4b
	.4byte	0x57
	.byte	0
	.uleb128 0x1a
	.4byte	$LASF214
	.byte	0x18
	.byte	0x3d
	.4byte	0x8ad
	.byte	0x3
	.4byte	0x8ad
	.uleb128 0x1c
	.4byte	$LASF215
	.byte	0x18
	.byte	0x3f
	.4byte	0x8ad
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x166
	.uleb128 0x1e
	.4byte	$LASF216
	.byte	0x1e
	.byte	0xc7
	.byte	0x3
	.uleb128 0x1f
	.4byte	$LASF217
	.byte	0x1
	.2byte	0x380
	.4byte	0x9e
	.byte	0x1
	.4byte	0x8e1
	.uleb128 0x13
	.ascii	"s\000"
	.byte	0x1
	.2byte	0x380
	.4byte	0xcd
	.uleb128 0x14
	.ascii	"k\000"
	.byte	0x1
	.2byte	0x382
	.4byte	0x9e
	.byte	0
	.uleb128 0x1a
	.4byte	$LASF218
	.byte	0x5
	.byte	0x9e
	.4byte	0x186
	.byte	0x3
	.4byte	0x915
	.uleb128 0x18
	.4byte	$LASF184
	.byte	0x5
	.byte	0x9e
	.4byte	0x123
	.uleb128 0x18
	.4byte	$LASF187
	.byte	0x5
	.byte	0x9e
	.4byte	0x139
	.uleb128 0x20
	.uleb128 0x1c
	.4byte	$LASF219
	.byte	0x5
	.byte	0xa5
	.4byte	0x57
	.byte	0
	.byte	0
	.uleb128 0x21
	.4byte	$LASF226
	.byte	0x1
	.2byte	0x320
	.4byte	$LFB3076
	.4byte	$LFE3076-$LFB3076
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xaf2
	.uleb128 0x22
	.ascii	"skb\000"
	.byte	0x1
	.2byte	0x320
	.4byte	0x186
	.uleb128 0x1
	.byte	0x62
	.uleb128 0x14
	.ascii	"iph\000"
	.byte	0x1
	.2byte	0x322
	.4byte	0xaf2
	.uleb128 0x14
	.ascii	"x\000"
	.byte	0x1
	.2byte	0x323
	.4byte	0x9e
	.uleb128 0x23
	.4byte	0x757
	.4byte	$LBB129
	.4byte	$LBE129-$LBB129
	.byte	0x1
	.2byte	0x32b
	.4byte	0x973
	.uleb128 0x24
	.4byte	$LBB130
	.4byte	$LBE130-$LBB130
	.uleb128 0x25
	.4byte	0x767
	.byte	0
	.byte	0
	.uleb128 0x26
	.4byte	$Ldebug_ranges0+0
	.4byte	0xacc
	.uleb128 0x27
	.4byte	$LASF220
	.byte	0x1
	.2byte	0x32e
	.4byte	0xaf8
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x27
	.4byte	$LASF221
	.byte	0x1
	.2byte	0x32f
	.4byte	0x57
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x28
	.ascii	"lv\000"
	.byte	0x1
	.2byte	0x330
	.4byte	0x69
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x27
	.4byte	$LASF222
	.byte	0x1
	.2byte	0x331
	.4byte	0x50
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x29
	.4byte	$LASF223
	.byte	0x1
	.2byte	0x333
	.4byte	0x57
	.uleb128 0x2a
	.4byte	0x773
	.4byte	$LBB132
	.4byte	$Ldebug_ranges0+0x18
	.byte	0x1
	.2byte	0x336
	.4byte	0x9f0
	.uleb128 0x2b
	.4byte	0x795
	.uleb128 0x2b
	.4byte	0x78a
	.uleb128 0x2b
	.4byte	0x77f
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0x18
	.uleb128 0x25
	.4byte	0x7a0
	.byte	0
	.byte	0
	.uleb128 0x2a
	.4byte	0x773
	.4byte	$LBB136
	.4byte	$Ldebug_ranges0+0x30
	.byte	0x1
	.2byte	0x363
	.4byte	0xa1f
	.uleb128 0x2b
	.4byte	0x795
	.uleb128 0x2b
	.4byte	0x78a
	.uleb128 0x2b
	.4byte	0x77f
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0x30
	.uleb128 0x25
	.4byte	0x7a0
	.byte	0
	.byte	0
	.uleb128 0x2a
	.4byte	0x773
	.4byte	$LBB142
	.4byte	$Ldebug_ranges0+0x50
	.byte	0x1
	.2byte	0x365
	.4byte	0xa4e
	.uleb128 0x2b
	.4byte	0x795
	.uleb128 0x2b
	.4byte	0x78a
	.uleb128 0x2b
	.4byte	0x77f
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0x50
	.uleb128 0x25
	.4byte	0x7a0
	.byte	0
	.byte	0
	.uleb128 0x2a
	.4byte	0x773
	.4byte	$LBB146
	.4byte	$Ldebug_ranges0+0x68
	.byte	0x1
	.2byte	0x370
	.4byte	0xa7d
	.uleb128 0x2b
	.4byte	0x795
	.uleb128 0x2b
	.4byte	0x78a
	.uleb128 0x2b
	.4byte	0x77f
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0x68
	.uleb128 0x25
	.4byte	0x7a0
	.byte	0
	.byte	0
	.uleb128 0x2d
	.4byte	0x7aa
	.4byte	$LBB150
	.4byte	$Ldebug_ranges0+0x80
	.byte	0x1
	.2byte	0x377
	.uleb128 0x2b
	.4byte	0x7c5
	.uleb128 0x2b
	.4byte	0x7ba
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0x80
	.uleb128 0x2e
	.4byte	0x7d0
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2e
	.4byte	0x7db
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x25
	.4byte	0x7e6
	.uleb128 0x25
	.4byte	0x7f1
	.uleb128 0x2f
	.4byte	0x72e
	.4byte	$LBB152
	.4byte	$LBE152-$LBB152
	.byte	0x3
	.byte	0x81
	.uleb128 0x2b
	.4byte	0x73e
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x30
	.4byte	0x824
	.4byte	$LBB161
	.4byte	$LBE161-$LBB161
	.byte	0x1
	.2byte	0x37d
	.uleb128 0x2b
	.4byte	0x830
	.uleb128 0x24
	.4byte	$LBB162
	.4byte	$LBE162-$LBB162
	.uleb128 0x25
	.4byte	0x83b
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x3ef
	.uleb128 0x6
	.byte	0x4
	.4byte	0x4b9
	.uleb128 0x31
	.4byte	$LASF224
	.byte	0x1
	.2byte	0x3e0
	.4byte	0x57
	.4byte	$LFB3080
	.4byte	$LFE3080-$LFB3080
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xb31
	.uleb128 0x22
	.ascii	"s\000"
	.byte	0x1
	.2byte	0x3e0
	.4byte	0xb31
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x22
	.ascii	"v\000"
	.byte	0x1
	.2byte	0x3e0
	.4byte	0x186
	.uleb128 0x1
	.byte	0x55
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x30a
	.uleb128 0x31
	.4byte	$LASF225
	.byte	0x1
	.2byte	0x3e7
	.4byte	0x57
	.4byte	$LFB3081
	.4byte	$LFE3081-$LFB3081
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xb6a
	.uleb128 0x22
	.ascii	"s\000"
	.byte	0x1
	.2byte	0x3e7
	.4byte	0xb31
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x22
	.ascii	"v\000"
	.byte	0x1
	.2byte	0x3e7
	.4byte	0x186
	.uleb128 0x1
	.byte	0x55
	.byte	0
	.uleb128 0x32
	.4byte	$LASF227
	.byte	0x1
	.2byte	0x3ee
	.4byte	0x57
	.4byte	$LFB3082
	.4byte	$LFE3082-$LFB3082
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xba1
	.uleb128 0x33
	.4byte	$LASF42
	.byte	0x1
	.2byte	0x3ee
	.4byte	0x1e7
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x33
	.4byte	$LASF44
	.byte	0x1
	.2byte	0x3ee
	.4byte	0x3f4
	.uleb128 0x1
	.byte	0x55
	.byte	0
	.uleb128 0x32
	.4byte	$LASF228
	.byte	0x1
	.2byte	0x402
	.4byte	0x57
	.4byte	$LFB3084
	.4byte	$LFE3084-$LFB3084
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xbd8
	.uleb128 0x33
	.4byte	$LASF42
	.byte	0x1
	.2byte	0x402
	.4byte	0x1e7
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x33
	.4byte	$LASF44
	.byte	0x1
	.2byte	0x402
	.4byte	0x3f4
	.uleb128 0x1
	.byte	0x55
	.byte	0
	.uleb128 0x34
	.4byte	0x74a
	.4byte	$LFB3073
	.4byte	$LFE3073-$LFB3073
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x35
	.4byte	0x847
	.4byte	$LFB3068
	.4byte	$LFE3068-$LFB3068
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xc0d
	.uleb128 0x36
	.4byte	0x853
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0xa8
	.uleb128 0x2b
	.4byte	0x853
	.byte	0
	.byte	0
	.uleb128 0x37
	.4byte	$LASF354
	.byte	0x1
	.byte	0x38
	.4byte	0x57
	.4byte	$LFB3066
	.4byte	$LFE3066-$LFB3066
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x38
	.4byte	$LASF229
	.byte	0x1
	.byte	0x46
	.4byte	0x57
	.4byte	$LFB3067
	.4byte	$LFE3067-$LFB3067
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xc72
	.uleb128 0x39
	.4byte	$LASF209
	.byte	0x1
	.byte	0x46
	.4byte	0xcd
	.uleb128 0x1
	.byte	0x60
	.uleb128 0x2f
	.4byte	0x85f
	.4byte	$LBB173
	.4byte	$LBE173-$LBB173
	.byte	0x1
	.byte	0x48
	.uleb128 0x2b
	.4byte	0x87a
	.uleb128 0x2b
	.4byte	0x86f
	.uleb128 0x24
	.4byte	$LBB174
	.4byte	$LBE174-$LBB174
	.uleb128 0x25
	.4byte	0x885
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x38
	.4byte	$LASF230
	.byte	0x1
	.byte	0x60
	.4byte	0x57
	.4byte	$LFB3070
	.4byte	$LFE3070-$LFB3070
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xcb1
	.uleb128 0x3a
	.ascii	"skb\000"
	.byte	0x1
	.byte	0x60
	.4byte	0x186
	.uleb128 0x1
	.byte	0x61
	.uleb128 0x3b
	.ascii	"iph\000"
	.byte	0x1
	.byte	0x62
	.4byte	0xaf2
	.uleb128 0x1
	.byte	0x60
	.uleb128 0x1c
	.4byte	$LASF220
	.byte	0x1
	.byte	0x63
	.4byte	0xaf8
	.byte	0
	.uleb128 0x3c
	.4byte	$LASF231
	.byte	0x1
	.byte	0x73
	.4byte	$LFB3071
	.4byte	$LFE3071-$LFB3071
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xd77
	.uleb128 0x3a
	.ascii	"skb\000"
	.byte	0x1
	.byte	0x73
	.4byte	0x186
	.uleb128 0x1
	.byte	0x61
	.uleb128 0x3d
	.4byte	$LASF232
	.byte	0x1
	.byte	0x75
	.4byte	0xd77
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x1c
	.4byte	$LASF233
	.byte	0x1
	.byte	0x76
	.4byte	0xd7d
	.uleb128 0x1c
	.4byte	$LASF234
	.byte	0x1
	.byte	0x77
	.4byte	0xd83
	.uleb128 0x1c
	.4byte	$LASF235
	.byte	0x1
	.byte	0x78
	.4byte	0xd89
	.uleb128 0x1c
	.4byte	$LASF236
	.byte	0x1
	.byte	0x79
	.4byte	0xd8f
	.uleb128 0x1c
	.4byte	$LASF237
	.byte	0x1
	.byte	0x7a
	.4byte	0xd95
	.uleb128 0x3b
	.ascii	"iph\000"
	.byte	0x1
	.byte	0x7b
	.4byte	0xaf2
	.uleb128 0x1
	.byte	0x60
	.uleb128 0x24
	.4byte	$LBB175
	.4byte	$LBE175-$LBB175
	.uleb128 0x3b
	.ascii	"th\000"
	.byte	0x1
	.byte	0x7f
	.4byte	0xd9b
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x26
	.4byte	$Ldebug_ranges0+0xc0
	.4byte	0xd59
	.uleb128 0x1c
	.4byte	$LASF238
	.byte	0x1
	.byte	0xa2
	.4byte	0x123
	.uleb128 0x1c
	.4byte	$LASF239
	.byte	0x1
	.byte	0xa2
	.4byte	0x186
	.byte	0
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0xd8
	.uleb128 0x1c
	.4byte	$LASF238
	.byte	0x1
	.byte	0xa3
	.4byte	0x123
	.uleb128 0x1c
	.4byte	$LASF239
	.byte	0x1
	.byte	0xa3
	.4byte	0x186
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x4be
	.uleb128 0x6
	.byte	0x4
	.4byte	0x4c3
	.uleb128 0x6
	.byte	0x4
	.4byte	0x4cd
	.uleb128 0x6
	.byte	0x4
	.4byte	0x4c8
	.uleb128 0x6
	.byte	0x4
	.4byte	0x4d7
	.uleb128 0x6
	.byte	0x4
	.4byte	0x4d2
	.uleb128 0x6
	.byte	0x4
	.4byte	0x469
	.uleb128 0x31
	.4byte	$LASF240
	.byte	0x1
	.2byte	0x1d4
	.4byte	0x57
	.4byte	$LFB3072
	.4byte	$LFE3072-$LFB3072
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xe82
	.uleb128 0x33
	.4byte	$LASF241
	.byte	0x1
	.2byte	0x1d4
	.4byte	0xe82
	.uleb128 0x1
	.byte	0x62
	.uleb128 0x28
	.ascii	"iph\000"
	.byte	0x1
	.2byte	0x1d6
	.4byte	0xaf2
	.uleb128 0x1
	.byte	0x63
	.uleb128 0x27
	.4byte	$LASF220
	.byte	0x1
	.2byte	0x1d7
	.4byte	0xaf8
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x27
	.4byte	$LASF242
	.byte	0x1
	.2byte	0x1d8
	.4byte	0x37
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x14
	.ascii	"ppp\000"
	.byte	0x1
	.2byte	0x1d9
	.4byte	0x186
	.uleb128 0x28
	.ascii	"skb\000"
	.byte	0x1
	.2byte	0x1da
	.4byte	0x186
	.uleb128 0x1
	.byte	0x60
	.uleb128 0x29
	.4byte	$LASF243
	.byte	0x1
	.2byte	0x1db
	.4byte	0x57
	.uleb128 0x27
	.4byte	$LASF244
	.byte	0x1
	.2byte	0x1dd
	.4byte	0x57
	.uleb128 0x1
	.byte	0x63
	.uleb128 0x29
	.4byte	$LASF245
	.byte	0x1
	.2byte	0x1de
	.4byte	0x220
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0xf0
	.uleb128 0x29
	.4byte	$LASF246
	.byte	0x1
	.2byte	0x1ec
	.4byte	0x220
	.uleb128 0x29
	.4byte	$LASF247
	.byte	0x1
	.2byte	0x1ed
	.4byte	0x57
	.uleb128 0x29
	.4byte	$LASF248
	.byte	0x1
	.2byte	0x1ee
	.4byte	0x57
	.uleb128 0x24
	.4byte	$LBB181
	.4byte	$LBE181-$LBB181
	.uleb128 0x27
	.4byte	$LASF238
	.byte	0x1
	.2byte	0x255
	.4byte	0x123
	.uleb128 0x1
	.byte	0x64
	.uleb128 0x29
	.4byte	$LASF239
	.byte	0x1
	.2byte	0x255
	.4byte	0x186
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x186
	.uleb128 0x31
	.4byte	$LASF249
	.byte	0x1
	.2byte	0x28f
	.4byte	0x57
	.4byte	$LFB3074
	.4byte	$LFE3074-$LFB3074
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x106c
	.uleb128 0x22
	.ascii	"skb\000"
	.byte	0x1
	.2byte	0x28f
	.4byte	0x186
	.uleb128 0x1
	.byte	0x61
	.uleb128 0x29
	.4byte	$LASF250
	.byte	0x1
	.2byte	0x291
	.4byte	0x57
	.uleb128 0x29
	.4byte	$LASF251
	.byte	0x1
	.2byte	0x292
	.4byte	0xaf2
	.uleb128 0x27
	.4byte	$LASF252
	.byte	0x1
	.2byte	0x292
	.4byte	0x3ef
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x29
	.4byte	$LASF220
	.byte	0x1
	.2byte	0x293
	.4byte	0xaf8
	.uleb128 0x27
	.4byte	$LASF253
	.byte	0x1
	.2byte	0x293
	.4byte	0x4b9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x28
	.ascii	"tos\000"
	.byte	0x1
	.2byte	0x294
	.4byte	0x37
	.uleb128 0x1
	.byte	0x64
	.uleb128 0x28
	.ascii	"eth\000"
	.byte	0x1
	.2byte	0x295
	.4byte	0x106c
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x29
	.4byte	$LASF254
	.byte	0x1
	.2byte	0x296
	.4byte	0x57
	.uleb128 0x27
	.4byte	$LASF255
	.byte	0x1
	.2byte	0x297
	.4byte	0x57
	.uleb128 0x1
	.byte	0x60
	.uleb128 0x29
	.4byte	$LASF256
	.byte	0x1
	.2byte	0x297
	.4byte	0x57
	.uleb128 0x29
	.4byte	$LASF257
	.byte	0x1
	.2byte	0x297
	.4byte	0x57
	.uleb128 0x23
	.4byte	0x85f
	.4byte	$LBB185
	.4byte	$LBE185-$LBB185
	.byte	0x1
	.2byte	0x2a2
	.4byte	0xf6f
	.uleb128 0x2b
	.4byte	0x87a
	.uleb128 0x2b
	.4byte	0x86f
	.uleb128 0x24
	.4byte	$LBB186
	.4byte	$LBE186-$LBB186
	.uleb128 0x25
	.4byte	0x885
	.byte	0
	.byte	0
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0x118
	.uleb128 0x28
	.ascii	"ppp\000"
	.byte	0x1
	.2byte	0x2a8
	.4byte	0x186
	.uleb128 0x1
	.byte	0x63
	.uleb128 0x26
	.4byte	$Ldebug_ranges0+0x130
	.4byte	0xf98
	.uleb128 0x29
	.4byte	$LASF258
	.byte	0x1
	.2byte	0x2c3
	.4byte	0x186
	.byte	0
	.uleb128 0x26
	.4byte	$Ldebug_ranges0+0x148
	.4byte	0xfba
	.uleb128 0x29
	.4byte	$LASF238
	.byte	0x1
	.2byte	0x2d0
	.4byte	0x123
	.uleb128 0x29
	.4byte	$LASF239
	.byte	0x1
	.2byte	0x2d0
	.4byte	0x186
	.byte	0
	.uleb128 0x26
	.4byte	$Ldebug_ranges0+0x170
	.4byte	0xfdc
	.uleb128 0x29
	.4byte	$LASF238
	.byte	0x1
	.2byte	0x2d1
	.4byte	0x123
	.uleb128 0x29
	.4byte	$LASF239
	.byte	0x1
	.2byte	0x2d1
	.4byte	0x186
	.byte	0
	.uleb128 0x2a
	.4byte	0x7aa
	.4byte	$LBB197
	.4byte	$Ldebug_ranges0+0x190
	.byte	0x1
	.2byte	0x2e2
	.4byte	0x102a
	.uleb128 0x2b
	.4byte	0x7c5
	.uleb128 0x2b
	.4byte	0x7ba
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0x190
	.uleb128 0x25
	.4byte	0x7d0
	.uleb128 0x25
	.4byte	0x7db
	.uleb128 0x25
	.4byte	0x7e6
	.uleb128 0x25
	.4byte	0x7f1
	.uleb128 0x2f
	.4byte	0x72e
	.4byte	$LBB199
	.4byte	$LBE199-$LBB199
	.byte	0x3
	.byte	0x81
	.uleb128 0x2b
	.4byte	0x73e
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x26
	.4byte	$Ldebug_ranges0+0x1c0
	.4byte	0x104c
	.uleb128 0x29
	.4byte	$LASF238
	.byte	0x1
	.2byte	0x2e4
	.4byte	0x123
	.uleb128 0x29
	.4byte	$LASF239
	.byte	0x1
	.2byte	0x2e4
	.4byte	0x186
	.byte	0
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0x1d8
	.uleb128 0x29
	.4byte	$LASF238
	.byte	0x1
	.2byte	0x2f0
	.4byte	0x123
	.uleb128 0x29
	.4byte	$LASF239
	.byte	0x1
	.2byte	0x2f0
	.4byte	0x186
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x22b
	.uleb128 0x21
	.4byte	$LASF259
	.byte	0x1
	.2byte	0x304
	.4byte	$LFB3075
	.4byte	$LFE3075-$LFB3075
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x10b1
	.uleb128 0x22
	.ascii	"skb\000"
	.byte	0x1
	.2byte	0x304
	.4byte	0x186
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x29
	.4byte	$LASF220
	.byte	0x1
	.2byte	0x306
	.4byte	0xaf8
	.uleb128 0x28
	.ascii	"iph\000"
	.byte	0x1
	.2byte	0x307
	.4byte	0x220
	.uleb128 0x1
	.byte	0x52
	.byte	0
	.uleb128 0x3e
	.4byte	$LASF260
	.byte	0x1
	.2byte	0x38c
	.4byte	0x57
	.4byte	$LFB3078
	.4byte	$LFE3078-$LFB3078
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x11d9
	.uleb128 0x33
	.4byte	$LASF44
	.byte	0x1
	.2byte	0x38c
	.4byte	0x3f4
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x33
	.4byte	$LASF261
	.byte	0x1
	.2byte	0x38c
	.4byte	0x1fc
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x33
	.4byte	$LASF262
	.byte	0x1
	.2byte	0x38d
	.4byte	0x9e
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x33
	.4byte	$LASF245
	.byte	0x1
	.2byte	0x38d
	.4byte	0x186
	.uleb128 0x1
	.byte	0x57
	.uleb128 0x27
	.4byte	$LASF263
	.byte	0x1
	.2byte	0x38f
	.4byte	0x11d9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -208
	.uleb128 0x26
	.4byte	$Ldebug_ranges0+0x200
	.4byte	0x11af
	.uleb128 0x29
	.4byte	$LASF264
	.byte	0x1
	.2byte	0x394
	.4byte	0x186
	.uleb128 0x29
	.4byte	$LASF265
	.byte	0x1
	.2byte	0x394
	.4byte	0x5f3
	.uleb128 0x29
	.4byte	$LASF266
	.byte	0x1
	.2byte	0x394
	.4byte	0xa5
	.uleb128 0x26
	.4byte	$Ldebug_ranges0+0x218
	.4byte	0x117a
	.uleb128 0x29
	.4byte	$LASF267
	.byte	0x1
	.2byte	0x394
	.4byte	0x9e
	.uleb128 0x29
	.4byte	$LASF268
	.byte	0x1
	.2byte	0x394
	.4byte	0x9e
	.uleb128 0x29
	.4byte	$LASF269
	.byte	0x1
	.2byte	0x394
	.4byte	0x9e
	.uleb128 0x29
	.4byte	$LASF270
	.byte	0x1
	.2byte	0x394
	.4byte	0x9e
	.byte	0
	.uleb128 0x24
	.4byte	$LBB219
	.4byte	$LBE219-$LBB219
	.uleb128 0x27
	.4byte	$LASF271
	.byte	0x1
	.2byte	0x394
	.4byte	0x186
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x27
	.4byte	$LASF272
	.byte	0x1
	.2byte	0x394
	.4byte	0x5f3
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x27
	.4byte	$LASF273
	.byte	0x1
	.2byte	0x394
	.4byte	0xa5
	.uleb128 0x1
	.byte	0x56
	.byte	0
	.byte	0
	.uleb128 0x30
	.4byte	0x8bb
	.4byte	$LBB221
	.4byte	$LBE221-$LBB221
	.byte	0x1
	.2byte	0x395
	.uleb128 0x36
	.4byte	0x8cc
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x24
	.4byte	$LBB222
	.4byte	$LBE222-$LBB222
	.uleb128 0x2e
	.4byte	0x8d6
	.uleb128 0x1
	.byte	0x52
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x3f
	.4byte	0xd3
	.4byte	0x11e9
	.uleb128 0x40
	.4byte	0x15f
	.byte	0xc7
	.byte	0
	.uleb128 0x41
	.4byte	$LASF276
	.byte	0x1
	.2byte	0x407
	.4byte	0x12e
	.4byte	$LFB3085
	.4byte	$LFE3085-$LFB3085
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x123c
	.uleb128 0x33
	.4byte	$LASF44
	.byte	0x1
	.2byte	0x407
	.4byte	0x3f4
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x33
	.4byte	$LASF274
	.byte	0x1
	.2byte	0x407
	.4byte	0x1fc
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x33
	.4byte	$LASF262
	.byte	0x1
	.2byte	0x408
	.4byte	0x123
	.uleb128 0x1
	.byte	0x56
	.uleb128 0x22
	.ascii	"off\000"
	.byte	0x1
	.2byte	0x408
	.4byte	0x1cb
	.uleb128 0x1
	.byte	0x57
	.byte	0
	.uleb128 0x31
	.4byte	$LASF275
	.byte	0x1
	.2byte	0x39a
	.4byte	0x57
	.4byte	$LFB3079
	.4byte	$LFE3079-$LFB3079
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x13a7
	.uleb128 0x33
	.4byte	$LASF44
	.byte	0x1
	.2byte	0x39a
	.4byte	0x3f4
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x33
	.4byte	$LASF261
	.byte	0x1
	.2byte	0x39a
	.4byte	0x1fc
	.uleb128 0x1
	.byte	0x62
	.uleb128 0x33
	.4byte	$LASF262
	.byte	0x1
	.2byte	0x39b
	.4byte	0x9e
	.uleb128 0x1
	.byte	0x60
	.uleb128 0x33
	.4byte	$LASF245
	.byte	0x1
	.2byte	0x39b
	.4byte	0x186
	.uleb128 0x1
	.byte	0x57
	.uleb128 0x29
	.4byte	$LASF263
	.byte	0x1
	.2byte	0x39d
	.4byte	0xcd
	.uleb128 0x23
	.4byte	0x8e1
	.4byte	$LBB223
	.4byte	$LBE223-$LBB223
	.byte	0x1
	.2byte	0x3aa
	.4byte	0x12b9
	.uleb128 0x2b
	.4byte	0x8fc
	.uleb128 0x2b
	.4byte	0x8f1
	.byte	0
	.uleb128 0x42
	.4byte	$LBB225
	.4byte	$LBE225-$LBB225
	.4byte	0x135d
	.uleb128 0x29
	.4byte	$LASF264
	.byte	0x1
	.2byte	0x3ae
	.4byte	0x186
	.uleb128 0x29
	.4byte	$LASF265
	.byte	0x1
	.2byte	0x3ae
	.4byte	0x5f3
	.uleb128 0x29
	.4byte	$LASF266
	.byte	0x1
	.2byte	0x3ae
	.4byte	0xa5
	.uleb128 0x42
	.4byte	$LBB226
	.4byte	$LBE226-$LBB226
	.4byte	0x1328
	.uleb128 0x29
	.4byte	$LASF267
	.byte	0x1
	.2byte	0x3ae
	.4byte	0x9e
	.uleb128 0x29
	.4byte	$LASF268
	.byte	0x1
	.2byte	0x3ae
	.4byte	0x9e
	.uleb128 0x29
	.4byte	$LASF269
	.byte	0x1
	.2byte	0x3ae
	.4byte	0x9e
	.uleb128 0x29
	.4byte	$LASF270
	.byte	0x1
	.2byte	0x3ae
	.4byte	0x9e
	.byte	0
	.uleb128 0x24
	.4byte	$LBB227
	.4byte	$LBE227-$LBB227
	.uleb128 0x27
	.4byte	$LASF271
	.byte	0x1
	.2byte	0x3ae
	.4byte	0x186
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x27
	.4byte	$LASF272
	.byte	0x1
	.2byte	0x3ae
	.4byte	0x5f3
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x27
	.4byte	$LASF273
	.byte	0x1
	.2byte	0x3ae
	.4byte	0xa5
	.uleb128 0x1
	.byte	0x56
	.byte	0
	.byte	0
	.uleb128 0x23
	.4byte	0x8bb
	.4byte	$LBB228
	.4byte	$LBE228-$LBB228
	.byte	0x1
	.2byte	0x3af
	.4byte	0x1388
	.uleb128 0x2b
	.4byte	0x8cc
	.uleb128 0x24
	.4byte	$LBB229
	.4byte	$LBE229-$LBB229
	.uleb128 0x2e
	.4byte	0x8d6
	.uleb128 0x1
	.byte	0x53
	.byte	0
	.byte	0
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0x230
	.uleb128 0x29
	.4byte	$LASF238
	.byte	0x1
	.2byte	0x3b2
	.4byte	0x123
	.uleb128 0x29
	.4byte	$LASF239
	.byte	0x1
	.2byte	0x3b2
	.4byte	0x186
	.byte	0
	.byte	0
	.uleb128 0x41
	.4byte	$LASF277
	.byte	0x1
	.2byte	0x3f3
	.4byte	0x12e
	.4byte	$LFB3083
	.4byte	$LFE3083-$LFB3083
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x13fa
	.uleb128 0x33
	.4byte	$LASF44
	.byte	0x1
	.2byte	0x3f3
	.4byte	0x3f4
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x33
	.4byte	$LASF274
	.byte	0x1
	.2byte	0x3f3
	.4byte	0x1fc
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x33
	.4byte	$LASF262
	.byte	0x1
	.2byte	0x3f4
	.4byte	0x123
	.uleb128 0x1
	.byte	0x56
	.uleb128 0x22
	.ascii	"off\000"
	.byte	0x1
	.2byte	0x3f4
	.4byte	0x1cb
	.uleb128 0x1
	.byte	0x57
	.byte	0
	.uleb128 0x31
	.4byte	$LASF278
	.byte	0x1
	.2byte	0x43b
	.4byte	0x57
	.4byte	$LFB3086
	.4byte	$LFE3086-$LFB3086
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1433
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0x248
	.uleb128 0x29
	.4byte	$LASF238
	.byte	0x1
	.2byte	0x459
	.4byte	0x123
	.uleb128 0x29
	.4byte	$LASF239
	.byte	0x1
	.2byte	0x459
	.4byte	0x186
	.byte	0
	.byte	0
	.uleb128 0x43
	.4byte	$LASF355
	.byte	0x1
	.2byte	0x45e
	.4byte	$LFB3087
	.4byte	$LFE3087-$LFB3087
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x8
	.4byte	$LASF279
	.uleb128 0x8
	.4byte	$LASF280
	.uleb128 0x8
	.4byte	$LASF281
	.uleb128 0x8
	.4byte	$LASF282
	.uleb128 0x44
	.4byte	$LASF283
	.byte	0x19
	.byte	0x6c
	.4byte	0x69
	.4byte	0x1fbd0
	.uleb128 0x3f
	.4byte	0x7e
	.4byte	0x1478
	.uleb128 0x40
	.4byte	0x15f
	.byte	0x5
	.byte	0
	.uleb128 0x1c
	.4byte	$LASF284
	.byte	0x1a
	.byte	0x39
	.4byte	0x1483
	.uleb128 0xd
	.4byte	0x1468
	.uleb128 0x3d
	.4byte	$LASF285
	.byte	0x1
	.byte	0x30
	.4byte	0x4dc
	.uleb128 0x5
	.byte	0x3
	.4byte	pptpAccInfo
	.uleb128 0x3d
	.4byte	$LASF286
	.byte	0x1
	.byte	0x34
	.4byte	0x57
	.uleb128 0x5
	.byte	0x3
	.4byte	pptp_conn_check
	.uleb128 0x27
	.4byte	$LASF287
	.byte	0x1
	.2byte	0x434
	.4byte	0x14bc
	.uleb128 0x5
	.byte	0x3
	.4byte	res1
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1454
	.uleb128 0x27
	.4byte	$LASF288
	.byte	0x1
	.2byte	0x435
	.4byte	0x14bc
	.uleb128 0x5
	.byte	0x3
	.4byte	res_check_pptp
	.uleb128 0x45
	.4byte	$LASF289
	.byte	0x1b
	.byte	0x21
	.4byte	0x1dd
	.uleb128 0x3f
	.4byte	0x155
	.4byte	0x14ea
	.uleb128 0x46
	.byte	0
	.uleb128 0x45
	.4byte	$LASF290
	.byte	0x1c
	.byte	0x54
	.4byte	0x14df
	.uleb128 0x3f
	.4byte	0x57
	.4byte	0x1500
	.uleb128 0x46
	.byte	0
	.uleb128 0x45
	.4byte	$LASF291
	.byte	0x1d
	.byte	0x24
	.4byte	0x14f5
	.uleb128 0x3f
	.4byte	0xd3
	.4byte	0x1516
	.uleb128 0x46
	.byte	0
	.uleb128 0x47
	.4byte	$LASF292
	.byte	0x1e
	.2byte	0x1b2
	.4byte	0x1522
	.uleb128 0xd
	.4byte	0x150b
	.uleb128 0x45
	.4byte	$LASF293
	.byte	0x1f
	.byte	0x1c
	.4byte	0x57
	.uleb128 0x45
	.4byte	$LASF294
	.byte	0x1f
	.byte	0x50
	.4byte	0x153d
	.uleb128 0xd
	.4byte	0x1542
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1548
	.uleb128 0xd
	.4byte	0x15a
	.uleb128 0x3f
	.4byte	0x9e
	.4byte	0x1563
	.uleb128 0x40
	.4byte	0x15f
	.byte	0x20
	.uleb128 0x40
	.4byte	0x15f
	.byte	0
	.byte	0
	.uleb128 0x47
	.4byte	$LASF295
	.byte	0x1f
	.2byte	0x2f9
	.4byte	0x156f
	.uleb128 0xd
	.4byte	0x154d
	.uleb128 0x45
	.4byte	$LASF296
	.byte	0x20
	.byte	0x76
	.4byte	0x106
	.uleb128 0x45
	.4byte	$LASF297
	.byte	0x21
	.byte	0x22
	.4byte	0x57
	.uleb128 0x45
	.4byte	$LASF298
	.byte	0x21
	.byte	0x23
	.4byte	0x57
	.uleb128 0x45
	.4byte	$LASF299
	.byte	0x22
	.byte	0x8d
	.4byte	0x1445
	.uleb128 0x45
	.4byte	$LASF300
	.byte	0xd
	.byte	0x3f
	.4byte	0x9e
	.uleb128 0x45
	.4byte	$LASF301
	.byte	0xd
	.byte	0x4c
	.4byte	0x1ba
	.uleb128 0x45
	.4byte	$LASF302
	.byte	0x23
	.byte	0x3f
	.4byte	0x15c1
	.uleb128 0xd
	.4byte	0x9e
	.uleb128 0x45
	.4byte	$LASF303
	.byte	0x24
	.byte	0x1d
	.4byte	0x9e
	.uleb128 0x45
	.4byte	$LASF304
	.byte	0x25
	.byte	0x4c
	.4byte	0x57
	.uleb128 0x47
	.4byte	$LASF305
	.byte	0x25
	.2byte	0x2ad
	.4byte	0x194
	.uleb128 0x45
	.4byte	$LASF306
	.byte	0x26
	.byte	0x4d
	.4byte	0x15f3
	.uleb128 0x48
	.4byte	0x9e
	.uleb128 0x47
	.4byte	$LASF307
	.byte	0x27
	.2byte	0x151
	.4byte	0x1604
	.uleb128 0x6
	.byte	0x4
	.4byte	0x144a
	.uleb128 0x47
	.4byte	$LASF308
	.byte	0x27
	.2byte	0x154
	.4byte	0x1604
	.uleb128 0x47
	.4byte	$LASF309
	.byte	0x25
	.2byte	0x391
	.4byte	0x19f
	.uleb128 0x45
	.4byte	$LASF310
	.byte	0x28
	.byte	0x5b
	.4byte	0x162d
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1b5
	.uleb128 0x45
	.4byte	$LASF311
	.byte	0x29
	.byte	0x4d
	.4byte	0x1b5
	.uleb128 0x3f
	.4byte	0x9e
	.4byte	0x164e
	.uleb128 0x40
	.4byte	0x15f
	.byte	0x1
	.byte	0
	.uleb128 0x45
	.4byte	$LASF312
	.byte	0x2a
	.byte	0x12
	.4byte	0x163e
	.uleb128 0x47
	.4byte	$LASF313
	.byte	0x2b
	.2byte	0x799
	.4byte	0x144f
	.uleb128 0x45
	.4byte	$LASF314
	.byte	0x2c
	.byte	0x1b
	.4byte	0x57
	.uleb128 0x45
	.4byte	$LASF43
	.byte	0x2d
	.byte	0xfd
	.4byte	0x1f2
	.uleb128 0x47
	.4byte	$LASF315
	.byte	0x2b
	.2byte	0x61e
	.4byte	0x1687
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1e2
	.uleb128 0x47
	.4byte	$LASF316
	.byte	0x2e
	.2byte	0x1f4
	.4byte	0x1699
	.uleb128 0x6
	.byte	0x4
	.4byte	0x20c
	.uleb128 0x45
	.4byte	$LASF317
	.byte	0x2f
	.byte	0x2e
	.4byte	0x211
	.uleb128 0x3f
	.4byte	0x667
	.4byte	0x16ba
	.uleb128 0x40
	.4byte	0x15f
	.byte	0xd
	.byte	0
	.uleb128 0x45
	.4byte	$LASF318
	.byte	0x17
	.byte	0xe0
	.4byte	0x16aa
	.uleb128 0x45
	.4byte	$LASF319
	.byte	0x30
	.byte	0x8a
	.4byte	0x21b
	.uleb128 0x45
	.4byte	$LASF320
	.byte	0x31
	.byte	0xa
	.4byte	0x57
	.uleb128 0x45
	.4byte	$LASF321
	.byte	0x24
	.byte	0x21
	.4byte	0x9e
	.uleb128 0x3f
	.4byte	0x189
	.4byte	0x16f7
	.uleb128 0x49
	.4byte	0x15f
	.2byte	0x3ff
	.byte	0
	.uleb128 0x45
	.4byte	$LASF322
	.byte	0x32
	.byte	0x48
	.4byte	0x16e6
	.uleb128 0x45
	.4byte	$LASF323
	.byte	0x33
	.byte	0x4d
	.4byte	0x9e
	.uleb128 0x47
	.4byte	$LASF324
	.byte	0x34
	.2byte	0x1cb
	.4byte	0x9e
	.uleb128 0x3f
	.4byte	0x16b
	.4byte	0x1729
	.uleb128 0x40
	.4byte	0x15f
	.byte	0x1b
	.byte	0
	.uleb128 0x45
	.4byte	$LASF325
	.byte	0x35
	.byte	0x5d
	.4byte	0x1719
	.uleb128 0x47
	.4byte	$LASF326
	.byte	0x24
	.2byte	0x555
	.4byte	0x150b
	.uleb128 0x47
	.4byte	$LASF327
	.byte	0x24
	.2byte	0x555
	.4byte	0x150b
	.uleb128 0x3f
	.4byte	0x150
	.4byte	0x1762
	.uleb128 0x40
	.4byte	0x15f
	.byte	0xc
	.uleb128 0x40
	.4byte	0x15f
	.byte	0x7
	.byte	0
	.uleb128 0x45
	.4byte	$LASF328
	.byte	0x36
	.byte	0x62
	.4byte	0x174c
	.uleb128 0x3f
	.4byte	0x177d
	.4byte	0x177d
	.uleb128 0x40
	.4byte	0x15f
	.byte	0xc
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1783
	.uleb128 0xd
	.4byte	0x2fb
	.uleb128 0x45
	.4byte	$LASF80
	.byte	0x36
	.byte	0xea
	.4byte	0x176d
	.uleb128 0xa
	.4byte	0x17a3
	.uleb128 0xb
	.4byte	0x2f5
	.uleb128 0xb
	.4byte	0x17a3
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x300
	.uleb128 0x47
	.4byte	$LASF329
	.byte	0x36
	.2byte	0x114
	.4byte	0x17b5
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1793
	.uleb128 0x45
	.4byte	$LASF330
	.byte	0x37
	.byte	0x86
	.4byte	0x305
	.uleb128 0x47
	.4byte	$LASF118
	.byte	0x38
	.2byte	0x27b
	.4byte	0x17d2
	.uleb128 0x6
	.byte	0x4
	.4byte	0x3ea
	.uleb128 0x47
	.4byte	$LASF331
	.byte	0x39
	.2byte	0x2b8
	.4byte	0x1d8
	.uleb128 0x45
	.4byte	$LASF332
	.byte	0x3a
	.byte	0xcd
	.4byte	0x93
	.uleb128 0x45
	.4byte	$LASF333
	.byte	0x3a
	.byte	0xce
	.4byte	0x93
	.uleb128 0x45
	.4byte	$LASF334
	.byte	0x3b
	.byte	0xcd
	.4byte	0x1805
	.uleb128 0x6
	.byte	0x4
	.4byte	0x9e
	.uleb128 0x45
	.4byte	$LASF335
	.byte	0x3c
	.byte	0xb9
	.4byte	0x1816
	.uleb128 0xd
	.4byte	0x150b
	.uleb128 0x45
	.4byte	$LASF336
	.byte	0x11
	.byte	0x3e
	.4byte	0x464
	.uleb128 0x3f
	.4byte	0x2c
	.4byte	0x1836
	.uleb128 0x40
	.4byte	0x15f
	.byte	0xf
	.byte	0
	.uleb128 0x45
	.4byte	$LASF337
	.byte	0x3d
	.byte	0xd4
	.4byte	0x1841
	.uleb128 0xd
	.4byte	0x1826
	.uleb128 0x47
	.4byte	$LASF338
	.byte	0x3d
	.2byte	0x135
	.4byte	0x57
	.uleb128 0x45
	.4byte	$LASF339
	.byte	0x3e
	.byte	0xa
	.4byte	0x464
	.uleb128 0x47
	.4byte	$LASF340
	.byte	0x3f
	.2byte	0x11d
	.4byte	0x17b
	.uleb128 0x45
	.4byte	$LASF341
	.byte	0x40
	.byte	0x18
	.4byte	0x1454
	.uleb128 0x45
	.4byte	$LASF342
	.byte	0x1
	.byte	0x36
	.4byte	0x57
	.uleb128 0x47
	.4byte	$LASF343
	.byte	0x40
	.2byte	0x1b9
	.4byte	0x1a4
	.uleb128 0x4a
	.4byte	$LASF344
	.byte	0x1
	.byte	0x31
	.4byte	0x57
	.uleb128 0x5
	.byte	0x3
	.4byte	pptp_tcp_finished
	.uleb128 0x4b
	.4byte	$LASF345
	.byte	0x1
	.2byte	0x3fa
	.4byte	0x207
	.uleb128 0x5
	.byte	0x3
	.4byte	fastpath_pptp_proc_fops
	.uleb128 0x4b
	.4byte	$LASF346
	.byte	0x1
	.2byte	0x40e
	.4byte	0x207
	.uleb128 0x5
	.byte	0x3
	.4byte	pptp_conn_proc_fops
	.uleb128 0xa
	.4byte	0x18cb
	.uleb128 0xb
	.4byte	0xcd
	.byte	0
	.uleb128 0x47
	.4byte	$LASF347
	.byte	0x1
	.2byte	0x438
	.4byte	0x18d7
	.uleb128 0x6
	.byte	0x4
	.4byte	0x18c0
	.uleb128 0x4c
	.4byte	0x9e
	.uleb128 0x47
	.4byte	$LASF348
	.byte	0x1
	.2byte	0x439
	.4byte	0x18ee
	.uleb128 0x6
	.byte	0x4
	.4byte	0x18dd
	.byte	0
	.section	.debug_abbrev,"",@progbits
$Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x13
	.byte	0
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x13
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x13
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x4
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x4
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0xb
	.byte	0x1
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x28
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2b
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2d
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2f
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x30
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x31
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x32
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x33
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x34
	.uleb128 0x2e
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x35
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x36
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x37
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x38
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x39
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x3a
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x3b
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x3c
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3d
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x3e
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3f
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x40
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x41
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x42
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x43
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x44
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x45
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x46
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x47
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x48
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x49
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x4a
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x4b
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x4c
	.uleb128 0x15
	.byte	0
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x2c
	.2byte	0x2
	.4byte	$Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	$Ltext0
	.4byte	$Letext0-$Ltext0
	.4byte	$LFB3086
	.4byte	$LFE3086-$LFB3086
	.4byte	$LFB3087
	.4byte	$LFE3087-$LFB3087
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",@progbits
$Ldebug_ranges0:
	.4byte	$LBB131
	.4byte	$LBE131
	.4byte	$LBB160
	.4byte	$LBE160
	.4byte	0
	.4byte	0
	.4byte	$LBB132
	.4byte	$LBE132
	.4byte	$LBB135
	.4byte	$LBE135
	.4byte	0
	.4byte	0
	.4byte	$LBB136
	.4byte	$LBE136
	.4byte	$LBB140
	.4byte	$LBE140
	.4byte	$LBB141
	.4byte	$LBE141
	.4byte	0
	.4byte	0
	.4byte	$LBB142
	.4byte	$LBE142
	.4byte	$LBB145
	.4byte	$LBE145
	.4byte	0
	.4byte	0
	.4byte	$LBB146
	.4byte	$LBE146
	.4byte	$LBB149
	.4byte	$LBE149
	.4byte	0
	.4byte	0
	.4byte	$LBB150
	.4byte	$LBE150
	.4byte	$LBB157
	.4byte	$LBE157
	.4byte	$LBB158
	.4byte	$LBE158
	.4byte	$LBB159
	.4byte	$LBE159
	.4byte	0
	.4byte	0
	.4byte	$LBB169
	.4byte	$LBE169
	.4byte	$LBB172
	.4byte	$LBE172
	.4byte	0
	.4byte	0
	.4byte	$LBB176
	.4byte	$LBE176
	.4byte	$LBB178
	.4byte	$LBE178
	.4byte	0
	.4byte	0
	.4byte	$LBB177
	.4byte	$LBE177
	.4byte	$LBB179
	.4byte	$LBE179
	.4byte	0
	.4byte	0
	.4byte	$LBB180
	.4byte	$LBE180
	.4byte	$LBB182
	.4byte	$LBE182
	.4byte	$LBB183
	.4byte	$LBE183
	.4byte	$LBB184
	.4byte	$LBE184
	.4byte	0
	.4byte	0
	.4byte	$LBB187
	.4byte	$LBE187
	.4byte	$LBB215
	.4byte	$LBE215
	.4byte	0
	.4byte	0
	.4byte	$LBB188
	.4byte	$LBE188
	.4byte	$LBB189
	.4byte	$LBE189
	.4byte	0
	.4byte	0
	.4byte	$LBB190
	.4byte	$LBE190
	.4byte	$LBB191
	.4byte	$LBE191
	.4byte	$LBB192
	.4byte	$LBE192
	.4byte	$LBB193
	.4byte	$LBE193
	.4byte	0
	.4byte	0
	.4byte	$LBB194
	.4byte	$LBE194
	.4byte	$LBB195
	.4byte	$LBE195
	.4byte	$LBB196
	.4byte	$LBE196
	.4byte	0
	.4byte	0
	.4byte	$LBB197
	.4byte	$LBE197
	.4byte	$LBB205
	.4byte	$LBE205
	.4byte	$LBB206
	.4byte	$LBE206
	.4byte	$LBB208
	.4byte	$LBE208
	.4byte	$LBB209
	.4byte	$LBE209
	.4byte	0
	.4byte	0
	.4byte	$LBB207
	.4byte	$LBE207
	.4byte	$LBB210
	.4byte	$LBE210
	.4byte	0
	.4byte	0
	.4byte	$LBB211
	.4byte	$LBE211
	.4byte	$LBB212
	.4byte	$LBE212
	.4byte	$LBB213
	.4byte	$LBE213
	.4byte	$LBB214
	.4byte	$LBE214
	.4byte	0
	.4byte	0
	.4byte	$LBB216
	.4byte	$LBE216
	.4byte	$LBB220
	.4byte	$LBE220
	.4byte	0
	.4byte	0
	.4byte	$LBB217
	.4byte	$LBE217
	.4byte	$LBB218
	.4byte	$LBE218
	.4byte	0
	.4byte	0
	.4byte	$LBB230
	.4byte	$LBE230
	.4byte	$LBB231
	.4byte	$LBE231
	.4byte	0
	.4byte	0
	.4byte	$LBB232
	.4byte	$LBE232
	.4byte	$LBB233
	.4byte	$LBE233
	.4byte	0
	.4byte	0
	.4byte	$Ltext0
	.4byte	$Letext0
	.4byte	$LFB3086
	.4byte	$LFE3086
	.4byte	$LFB3087
	.4byte	$LFE3087
	.4byte	0
	.4byte	0
	.section	.debug_line,"",@progbits
$Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
$LASF191:
	.ascii	"kmalloc_order_trace\000"
$LASF157:
	.ascii	"IPV4_DEVCONF_FORWARDING\000"
$LASF156:
	.ascii	"pptp_acc_info\000"
$LASF130:
	.ascii	"RTAX_HOPLIMIT\000"
$LASF316:
	.ascii	"ksoftirqd\000"
$LASF351:
	.ascii	"/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_"
	.ascii	"v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_"
	.ascii	"20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/lin"
	.ascii	"ux-rtkmips_rtl8198c/linux-3.10.49\000"
$LASF298:
	.ascii	"overflowgid\000"
$LASF319:
	.ascii	"ioport_resource\000"
$LASF263:
	.ascii	"tmpbuf\000"
$LASF178:
	.ascii	"IPV4_DEVCONF_ARP_NOTIFY\000"
$LASF169:
	.ascii	"IPV4_DEVCONF_ARPFILTER\000"
$LASF299:
	.ascii	"init_user_ns\000"
$LASF52:
	.ascii	"IPPROTO_IP\000"
$LASF291:
	.ascii	"console_printk\000"
$LASF348:
	.ascii	"get_fastpptp_lastxmit_fphook\000"
$LASF145:
	.ascii	"ND_OPT_ROUTE_INFO\000"
$LASF187:
	.ascii	"flags\000"
$LASF161:
	.ascii	"IPV4_DEVCONF_SECURE_REDIRECTS\000"
$LASF138:
	.ascii	"__ND_OPT_PREFIX_INFO_END\000"
$LASF244:
	.ascii	"check_stats\000"
$LASF200:
	.ascii	"ip_fast_csum\000"
$LASF155:
	.ascii	"PptpCallDisconnectNotify\000"
$LASF46:
	.ascii	"task_struct\000"
$LASF129:
	.ascii	"RTAX_REORDERING\000"
$LASF93:
	.ascii	"IFLA_MASTER\000"
$LASF7:
	.ascii	"unsigned int\000"
$LASF85:
	.ascii	"IFLA_BROADCAST\000"
$LASF203:
	.ascii	"csum\000"
$LASF37:
	.ascii	"pglist_data\000"
$LASF108:
	.ascii	"IFLA_PORT_SELF\000"
$LASF281:
	.ascii	"pid_namespace\000"
$LASF135:
	.ascii	"__RTAX_MAX\000"
$LASF168:
	.ascii	"IPV4_DEVCONF_TAG\000"
$LASF41:
	.ascii	"module\000"
$LASF54:
	.ascii	"IPPROTO_IGMP\000"
$LASF309:
	.ascii	"contig_page_data\000"
$LASF296:
	.ascii	"persistent_clock_exist\000"
$LASF97:
	.ascii	"IFLA_MAP\000"
$LASF140:
	.ascii	"ND_OPT_TARGET_LL_ADDR\000"
$LASF285:
	.ascii	"pptpAccInfo\000"
$LASF182:
	.ascii	"IPV4_DEVCONF_ROUTE_LOCALNET\000"
$LASF77:
	.ascii	"NF_INET_LOCAL_OUT\000"
$LASF223:
	.ascii	"gre_len\000"
$LASF338:
	.ascii	"sysctl_ip_default_ttl\000"
$LASF246:
	.ascii	"ppp_data\000"
$LASF147:
	.ascii	"ND_OPT_DNSSL\000"
$LASF265:
	.ascii	"__cu_from\000"
$LASF274:
	.ascii	"userbuf\000"
$LASF179:
	.ascii	"IPV4_DEVCONF_ACCEPT_LOCAL\000"
$LASF33:
	.ascii	"seqcount\000"
$LASF67:
	.ascii	"IPPROTO_BEETPH\000"
$LASF176:
	.ascii	"IPV4_DEVCONF_PROMOTE_SECONDARIES\000"
$LASF121:
	.ascii	"RTAX_LOCK\000"
$LASF275:
	.ascii	"ppfw_write_proc\000"
$LASF38:
	.ascii	"plat_smp_ops\000"
$LASF289:
	.ascii	"__this_module\000"
$LASF267:
	.ascii	"__addr\000"
$LASF217:
	.ascii	"atoi_dec\000"
$LASF259:
	.ascii	"fast_pptp_sync_rx_seq\000"
$LASF142:
	.ascii	"ND_OPT_REDIRECT_HDR\000"
$LASF353:
	.ascii	"get_fastpptp_lastxmit\000"
$LASF144:
	.ascii	"__ND_OPT_ARRAY_MAX\000"
$LASF112:
	.ascii	"IFLA_EXT_MASK\000"
$LASF65:
	.ascii	"IPPROTO_ESP\000"
$LASF202:
	.ascii	"stop\000"
$LASF284:
	.ascii	"eth_reserved_addr_base\000"
$LASF330:
	.ascii	"init_net\000"
$LASF57:
	.ascii	"IPPROTO_EGP\000"
$LASF349:
	.ascii	"GNU C 4.8.3 -fpreprocessed -G 0 -mno-check-zero-division"
	.ascii	" -mabi=32 -mno-abicalls -mno-branch-likely -msoft-float "
	.ascii	"-march=mips32r2 -mno-long-calls -mllsc -mplt -mno-shared"
	.ascii	" -g -O2 -fno-strict-aliasing -fno-common -fno-delete-nul"
	.ascii	"l-pointer-checks -fno-reorder-blocks -fno-tree-ch -fno-c"
	.ascii	"aller-saves -fno-pic -ffreestanding -fno-stack-protector"
	.ascii	" -fomit-frame-pointer -femit-struct-debug-baseonly -fno-"
	.ascii	"var-tracking -fno-strict-overflow -fconserve-stack\000"
$LASF238:
	.ascii	"__len\000"
$LASF107:
	.ascii	"IFLA_VF_PORTS\000"
$LASF219:
	.ascii	"index\000"
$LASF13:
	.ascii	"__kernel_ssize_t\000"
$LASF243:
	.ascii	"pull_offset\000"
$LASF12:
	.ascii	"__kernel_size_t\000"
$LASF249:
	.ascii	"fast_pptp_to_wan\000"
$LASF9:
	.ascii	"long long unsigned int\000"
$LASF35:
	.ascii	"pte_t\000"
$LASF323:
	.ascii	"zero_page_mask\000"
$LASF209:
	.ascii	"ppp_device\000"
$LASF31:
	.ascii	"thread_info\000"
$LASF318:
	.ascii	"kmalloc_caches\000"
$LASF24:
	.ascii	"ssize_t\000"
$LASF28:
	.ascii	"cpuinfo_mips\000"
$LASF255:
	.ascii	"wanip1\000"
$LASF256:
	.ascii	"wanip2\000"
$LASF257:
	.ascii	"wanip3\000"
$LASF204:
	.ascii	"carry\000"
$LASF308:
	.ascii	"system_freezable_wq\000"
$LASF100:
	.ascii	"IFLA_LINKMODE\000"
$LASF355:
	.ascii	"fast_pptp_exit\000"
$LASF230:
	.ascii	"Check_GRE_rx_net_device\000"
$LASF94:
	.ascii	"IFLA_WIRELESS\000"
$LASF183:
	.ascii	"__IPV4_DEVCONF_MAX\000"
$LASF352:
	.ascii	"nf_inet_hooks\000"
$LASF47:
	.ascii	"kernel_stat\000"
$LASF23:
	.ascii	"size_t\000"
$LASF205:
	.ascii	"arch_irqs_disabled_flags\000"
$LASF247:
	.ascii	"offset\000"
$LASF105:
	.ascii	"IFLA_VFINFO_LIST\000"
$LASF159:
	.ascii	"IPV4_DEVCONF_PROXY_ARP\000"
$LASF235:
	.ascii	"ocreq\000"
$LASF196:
	.ascii	"csum_fold\000"
$LASF21:
	.ascii	"_Bool\000"
$LASF273:
	.ascii	"__cu_len_r\000"
$LASF229:
	.ascii	"is_pptp_device\000"
$LASF126:
	.ascii	"RTAX_SSTHRESH\000"
$LASF225:
	.ascii	"pptpconn_read_proc\000"
$LASF141:
	.ascii	"ND_OPT_PREFIX_INFO\000"
$LASF49:
	.ascii	"resource\000"
$LASF136:
	.ascii	"neigh_table\000"
$LASF87:
	.ascii	"IFLA_MTU\000"
$LASF59:
	.ascii	"IPPROTO_UDP\000"
$LASF158:
	.ascii	"IPV4_DEVCONF_MC_FORWARDING\000"
$LASF302:
	.ascii	"mips_io_port_base\000"
$LASF99:
	.ascii	"IFLA_OPERSTATE\000"
$LASF164:
	.ascii	"IPV4_DEVCONF_RP_FILTER\000"
$LASF78:
	.ascii	"NF_INET_POST_ROUTING\000"
$LASF152:
	.ascii	"PptpOutCallRequest\000"
$LASF4:
	.ascii	"__u16\000"
$LASF312:
	.ascii	"__per_cpu_offset\000"
$LASF106:
	.ascii	"IFLA_STATS64\000"
$LASF345:
	.ascii	"fastpath_pptp_proc_fops\000"
$LASF262:
	.ascii	"count\000"
$LASF329:
	.ascii	"nf_nat_decode_session_hook\000"
$LASF139:
	.ascii	"ND_OPT_SOURCE_LL_ADDR\000"
$LASF228:
	.ascii	"pptp_conn_single_open\000"
$LASF199:
	.ascii	"bcopy\000"
$LASF252:
	.ascii	"iph_newone\000"
$LASF15:
	.ascii	"char\000"
$LASF216:
	.ascii	"might_fault\000"
$LASF55:
	.ascii	"IPPROTO_IPIP\000"
$LASF45:
	.ascii	"file_operations\000"
$LASF321:
	.ascii	"totalram_pages\000"
$LASF132:
	.ascii	"RTAX_FEATURES\000"
$LASF207:
	.ascii	"__tmp1\000"
$LASF277:
	.ascii	"fastpath_pptp_single_write\000"
$LASF272:
	.ascii	"__cu_from_r\000"
$LASF188:
	.ascii	"order\000"
$LASF86:
	.ascii	"IFLA_IFNAME\000"
$LASF118:
	.ascii	"rps_sock_flow_table\000"
$LASF270:
	.ascii	"__ok\000"
$LASF266:
	.ascii	"__cu_len\000"
$LASF180:
	.ascii	"IPV4_DEVCONF_SRC_VMARK\000"
$LASF342:
	.ascii	"fast_pptp_fw\000"
$LASF44:
	.ascii	"file\000"
$LASF6:
	.ascii	"__u32\000"
$LASF280:
	.ascii	"workqueue_struct\000"
$LASF48:
	.ascii	"kmem_cache\000"
$LASF189:
	.ascii	"kmem_cache_alloc_trace\000"
$LASF341:
	.ascii	"proc_root\000"
$LASF337:
	.ascii	"ip_tos2prio\000"
$LASF173:
	.ascii	"IPV4_DEVCONF_FORCE_IGMP_VERSION\000"
$LASF75:
	.ascii	"NF_INET_LOCAL_IN\000"
$LASF260:
	.ascii	"pptpconn_write_proc\000"
$LASF64:
	.ascii	"IPPROTO_IPV6\000"
$LASF89:
	.ascii	"IFLA_QDISC\000"
$LASF8:
	.ascii	"long long int\000"
$LASF317:
	.ascii	"kstat\000"
$LASF148:
	.ascii	"__ND_OPT_MAX\000"
$LASF125:
	.ascii	"RTAX_RTTVAR\000"
$LASF58:
	.ascii	"IPPROTO_PUP\000"
$LASF236:
	.ascii	"occlrnotify\000"
$LASF82:
	.ascii	"seq_file\000"
$LASF42:
	.ascii	"inode\000"
$LASF103:
	.ascii	"IFLA_IFALIAS\000"
$LASF66:
	.ascii	"IPPROTO_AH\000"
$LASF79:
	.ascii	"NF_INET_NUMHOOKS\000"
$LASF146:
	.ascii	"ND_OPT_RDNSS\000"
$LASF36:
	.ascii	"page\000"
$LASF128:
	.ascii	"RTAX_ADVMSS\000"
$LASF53:
	.ascii	"IPPROTO_ICMP\000"
$LASF20:
	.ascii	"bool\000"
$LASF162:
	.ascii	"IPV4_DEVCONF_SEND_REDIRECTS\000"
$LASF185:
	.ascii	"min_count\000"
$LASF160:
	.ascii	"IPV4_DEVCONF_ACCEPT_REDIRECTS\000"
$LASF175:
	.ascii	"IPV4_DEVCONF_ARP_IGNORE\000"
$LASF73:
	.ascii	"IPPROTO_MAX\000"
$LASF167:
	.ascii	"IPV4_DEVCONF_LOG_MARTIANS\000"
$LASF195:
	.ascii	"kmalloc_index\000"
$LASF29:
	.ascii	"cpumask\000"
$LASF91:
	.ascii	"IFLA_COST\000"
$LASF311:
	.ascii	"cmp_smp_ops\000"
$LASF300:
	.ascii	"shm_align_mask\000"
$LASF261:
	.ascii	"buffer\000"
$LASF184:
	.ascii	"size\000"
$LASF198:
	.ascii	"kmemleak_alloc\000"
$LASF334:
	.ascii	"sysctl_local_reserved_ports\000"
$LASF113:
	.ascii	"IFLA_PROMISCUITY\000"
$LASF224:
	.ascii	"ppfw_read_proc\000"
$LASF43:
	.ascii	"dqstats\000"
$LASF110:
	.ascii	"IFLA_GROUP\000"
$LASF297:
	.ascii	"overflowuid\000"
$LASF163:
	.ascii	"IPV4_DEVCONF_SHARED_MEDIA\000"
$LASF74:
	.ascii	"NF_INET_PRE_ROUTING\000"
$LASF234:
	.ascii	"ocack\000"
$LASF304:
	.ascii	"page_group_by_mobility_disabled\000"
$LASF109:
	.ascii	"IFLA_AF_SPEC\000"
$LASF253:
	.ascii	"grehone\000"
$LASF131:
	.ascii	"RTAX_INITCWND\000"
$LASF294:
	.ascii	"cpu_online_mask\000"
$LASF60:
	.ascii	"IPPROTO_IDP\000"
$LASF279:
	.ascii	"user_namespace\000"
$LASF213:
	.ascii	"__res\000"
$LASF239:
	.ascii	"__ret\000"
$LASF245:
	.ascii	"data\000"
$LASF134:
	.ascii	"RTAX_INITRWND\000"
$LASF325:
	.ascii	"vm_stat\000"
$LASF278:
	.ascii	"fast_pptp_init\000"
$LASF242:
	.ascii	"ppp_type\000"
$LASF335:
	.ascii	"inet_csk_timer_bug_msg\000"
$LASF76:
	.ascii	"NF_INET_FORWARD\000"
$LASF123:
	.ascii	"RTAX_WINDOW\000"
$LASF104:
	.ascii	"IFLA_NUM_VF\000"
$LASF250:
	.ascii	"header_len\000"
$LASF307:
	.ascii	"system_wq\000"
$LASF336:
	.ascii	"nd_tbl\000"
$LASF322:
	.ascii	"invalid_pte_table\000"
$LASF81:
	.ascii	"flowi\000"
$LASF62:
	.ascii	"IPPROTO_RSVP\000"
$LASF115:
	.ascii	"IFLA_NUM_RX_QUEUES\000"
$LASF63:
	.ascii	"IPPROTO_GRE\000"
$LASF276:
	.ascii	"pptp_conn_single_write\000"
$LASF117:
	.ascii	"__IFLA_MAX\000"
$LASF221:
	.ascii	"is_forward\000"
$LASF30:
	.ascii	"sizetype\000"
$LASF194:
	.ascii	"kmalloc_large\000"
$LASF211:
	.ascii	"__cs\000"
$LASF212:
	.ascii	"__ct\000"
$LASF51:
	.ascii	"ethhdr\000"
$LASF190:
	.ascii	"gfpflags\000"
$LASF2:
	.ascii	"short int\000"
$LASF264:
	.ascii	"__cu_to\000"
$LASF11:
	.ascii	"long int\000"
$LASF124:
	.ascii	"RTAX_RTT\000"
$LASF347:
	.ascii	"set_pptp_device_fphook\000"
$LASF171:
	.ascii	"IPV4_DEVCONF_NOXFRM\000"
$LASF120:
	.ascii	"RTAX_UNSPEC\000"
$LASF95:
	.ascii	"IFLA_PROTINFO\000"
$LASF181:
	.ascii	"IPV4_DEVCONF_PROXY_ARP_PVLAN\000"
$LASF114:
	.ascii	"IFLA_NUM_TX_QUEUES\000"
$LASF331:
	.ascii	"memalloc_socks\000"
$LASF122:
	.ascii	"RTAX_MTU\000"
$LASF226:
	.ascii	"sync_tx_pptp_gre_seqno\000"
$LASF177:
	.ascii	"IPV4_DEVCONF_ARP_ACCEPT\000"
$LASF68:
	.ascii	"IPPROTO_PIM\000"
$LASF328:
	.ascii	"nf_hooks\000"
$LASF197:
	.ascii	"arch_local_irq_save\000"
$LASF354:
	.ascii	"Get_fast_pptp_fw\000"
$LASF101:
	.ascii	"IFLA_LINKINFO\000"
$LASF201:
	.ascii	"word\000"
$LASF165:
	.ascii	"IPV4_DEVCONF_ACCEPT_SOURCE_ROUTE\000"
$LASF303:
	.ascii	"max_mapnr\000"
$LASF222:
	.ascii	"protocol\000"
$LASF83:
	.ascii	"IFLA_UNSPEC\000"
$LASF315:
	.ascii	"cad_pid\000"
$LASF292:
	.ascii	"hex_asc\000"
$LASF150:
	.ascii	"pptp_pkt_hdr\000"
$LASF251:
	.ascii	"iph_new\000"
$LASF333:
	.ascii	"ipv6_hash_secret\000"
$LASF16:
	.ascii	"__be16\000"
$LASF70:
	.ascii	"IPPROTO_SCTP\000"
$LASF88:
	.ascii	"IFLA_LINK\000"
$LASF186:
	.ascii	"kmalloc_order\000"
$LASF192:
	.ascii	"__ilog2_u32\000"
$LASF149:
	.ascii	"pptp_gre_hdr\000"
$LASF320:
	.ascii	"debug_locks\000"
$LASF40:
	.ascii	"static_key\000"
$LASF310:
	.ascii	"mp_ops\000"
$LASF151:
	.ascii	"PptpControlHeader\000"
$LASF193:
	.ascii	"__get_order\000"
$LASF102:
	.ascii	"IFLA_NET_NS_PID\000"
$LASF26:
	.ascii	"atomic_t\000"
$LASF208:
	.ascii	"set_pptp_device\000"
$LASF288:
	.ascii	"res_check_pptp\000"
$LASF10:
	.ascii	"long unsigned int\000"
$LASF3:
	.ascii	"__u8\000"
$LASF306:
	.ascii	"jiffies\000"
$LASF326:
	.ascii	"__init_begin\000"
$LASF80:
	.ascii	"nf_afinfo\000"
$LASF137:
	.ascii	"tcphdr\000"
$LASF282:
	.ascii	"proc_dir_entry\000"
$LASF71:
	.ascii	"IPPROTO_UDPLITE\000"
$LASF290:
	.ascii	"cpu_data\000"
$LASF56:
	.ascii	"IPPROTO_TCP\000"
$LASF153:
	.ascii	"PptpOutCallReply\000"
$LASF116:
	.ascii	"IFLA_CARRIER\000"
$LASF69:
	.ascii	"IPPROTO_COMP\000"
$LASF111:
	.ascii	"IFLA_NET_NS_FD\000"
$LASF166:
	.ascii	"IPV4_DEVCONF_BOOTP_RELAY\000"
$LASF22:
	.ascii	"loff_t\000"
$LASF1:
	.ascii	"unsigned char\000"
$LASF14:
	.ascii	"__kernel_loff_t\000"
$LASF84:
	.ascii	"IFLA_ADDRESS\000"
$LASF332:
	.ascii	"inet_ehash_secret\000"
$LASF254:
	.ascii	"ppp_hdr_len\000"
$LASF340:
	.ascii	"xt_recseq\000"
$LASF218:
	.ascii	"kmalloc\000"
$LASF286:
	.ascii	"pptp_conn_check\000"
$LASF133:
	.ascii	"RTAX_RTO_MIN\000"
$LASF127:
	.ascii	"RTAX_CWND\000"
$LASF18:
	.ascii	"__sum16\000"
$LASF283:
	.ascii	"frag_percpu_counter_batch\000"
$LASF327:
	.ascii	"__init_end\000"
$LASF313:
	.ascii	"init_pid_ns\000"
$LASF170:
	.ascii	"IPV4_DEVCONF_MEDIUM_ID\000"
$LASF248:
	.ascii	"ppp_offset\000"
$LASF350:
	.ascii	"/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_"
	.ascii	"v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_"
	.ascii	"20160603/build_dir/target-mips_24kec_uClibc-0.9.33.2/lin"
	.ascii	"ux-rtkmips_rtl8198c/fastpath-0.1/fast_pptp_core.c\000"
$LASF27:
	.ascii	"list_head\000"
$LASF215:
	.ascii	"__current_thread_info\000"
$LASF17:
	.ascii	"__be32\000"
$LASF96:
	.ascii	"IFLA_TXQLEN\000"
$LASF343:
	.ascii	"sync_tx_pptp_gre_seqno_hook\000"
$LASF240:
	.ascii	"fast_pptp_to_lan\000"
$LASF231:
	.ascii	"fast_pptp_filter\000"
$LASF233:
	.ascii	"ctlh\000"
$LASF339:
	.ascii	"arp_tbl\000"
$LASF287:
	.ascii	"res1\000"
$LASF269:
	.ascii	"__mask\000"
$LASF119:
	.ascii	"iphdr\000"
$LASF90:
	.ascii	"IFLA_STATS\000"
$LASF268:
	.ascii	"__size\000"
$LASF174:
	.ascii	"IPV4_DEVCONF_ARP_ANNOUNCE\000"
$LASF0:
	.ascii	"signed char\000"
$LASF143:
	.ascii	"ND_OPT_MTU\000"
$LASF241:
	.ascii	"pskb\000"
$LASF98:
	.ascii	"IFLA_WEIGHT\000"
$LASF5:
	.ascii	"short unsigned int\000"
$LASF301:
	.ascii	"flush_data_cache_page\000"
$LASF154:
	.ascii	"PptpClearCallRequest\000"
$LASF344:
	.ascii	"pptp_tcp_finished\000"
$LASF25:
	.ascii	"gfp_t\000"
$LASF346:
	.ascii	"pptp_conn_proc_fops\000"
$LASF19:
	.ascii	"__wsum\000"
$LASF34:
	.ascii	"seqcount_t\000"
$LASF293:
	.ascii	"nr_cpu_ids\000"
$LASF220:
	.ascii	"greh\000"
$LASF214:
	.ascii	"current_thread_info\000"
$LASF39:
	.ascii	"double\000"
$LASF324:
	.ascii	"zero_pfn\000"
$LASF206:
	.ascii	"arch_local_irq_restore\000"
$LASF92:
	.ascii	"IFLA_PRIORITY\000"
$LASF172:
	.ascii	"IPV4_DEVCONF_NOPOLICY\000"
$LASF314:
	.ascii	"percpu_counter_batch\000"
$LASF227:
	.ascii	"fastpath_pptp_single_open\000"
$LASF32:
	.ascii	"atomic_long_t\000"
$LASF237:
	.ascii	"occlrreq\000"
$LASF258:
	.ascii	"new_skb\000"
$LASF61:
	.ascii	"IPPROTO_DCCP\000"
$LASF305:
	.ascii	"mem_map\000"
$LASF271:
	.ascii	"__cu_to_r\000"
$LASF50:
	.ascii	"sk_buff\000"
$LASF72:
	.ascii	"IPPROTO_RAW\000"
$LASF210:
	.ascii	"strcmp\000"
$LASF232:
	.ascii	"pptph\000"
$LASF295:
	.ascii	"cpu_bit_bitmap\000"
	.ident	"GCC: (OpenWrt/Linaro GCC 4.8-2014.04 r39885) 4.8.3"

	.section .mdebug.abi32
	.previous
	.gnu_attribute 4, 3
	.text
$Ltext0:
	.cfi_sections	.debug_frame
	.align	2
	.globl	sync_tx_pptp_gre_seqno
$LFB3083 = .
	.file 1 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/fastpath-0.1/fast_pptp_core.c"
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

$LBB238 = .
$LBB239 = .
	.file 2 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/irqflags.h"
	.loc 2 39 0
#APP
 # 39 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/irqflags.h" 1
		.set	push						
	.set	reorder						
	.set	noat						
	di	$16					
	andi	$16, 1					
	sll $0, $0, 3			
	.set	pop						

 # 0 "" 2
#NO_APP
$LBE239 = .
$LBE238 = .
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
$LBB240 = .
	.loc 1 821 0 is_stmt 1
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_data
	move	$4,$18
	.set	macro
	.set	reorder

	lw	$3,14($17)
	andi	$3,$3,0xf
	sll	$3,$3,2
	addiu	$3,$3,14
	addu	$2,$2,$3
$LBB241 = .
$LBB242 = .
	.loc 1 93 0
	lbu	$4,3($2)
$LBE242 = .
$LBE241 = .
	.loc 1 824 0
	lbu	$3,1($2)
$LBB244 = .
$LBB243 = .
	.loc 1 93 0
	lbu	$6,2($2)
	sb	$4,21($sp)
$LBE243 = .
$LBE244 = .
	.loc 1 824 0
	andi	$5,$3,0x7
	li	$4,1			# 0x1
	.set	noreorder
	.set	nomacro
	bne	$5,$4,$L4
	sb	$6,20($sp)
	.set	macro
	.set	reorder

$LBB245 = .
$LBB246 = .
$LBB247 = .
	.file 3 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/uapi/asm/swab.h"
	.loc 3 20 0
	lhu	$5,20($sp)
$LBE247 = .
$LBE246 = .
$LBE245 = .
	.loc 1 824 0
	li	$4,34827			# 0x880b
$LBB250 = .
$LBB249 = .
$LBB248 = .
	.loc 3 20 0
#APP
 # 20 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/uapi/asm/swab.h" 1
		wsbh	$5, $5			

 # 0 "" 2
#NO_APP
	andi	$5,$5,0xffff
$LBE248 = .
$LBE249 = .
$LBE250 = .
	.loc 1 824 0
	bne	$5,$4,$L4
	.loc 1 861 0
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
	.loc 1 868 0 is_stmt 1
	lw	$3,36($4)
$LBB251 = .
$LBB252 = .
$LBB253 = .
	.loc 3 31 0
	lw	$5,8($2)
#APP
 # 31 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/uapi/asm/swab.h" 1
		wsbh	$5, $5			
	rotr	$5, $5, 16		

 # 0 "" 2
#NO_APP
$LBE253 = .
$LBE252 = .
$LBE251 = .
	.loc 1 868 0
	addiu	$6,$3,1
$LBB254 = .
$LBB255 = .
	.loc 1 93 0
	srl	$9,$5,8
	srl	$8,$5,16
	srl	$7,$5,24
	sb	$5,48($4)
$LBE255 = .
$LBE254 = .
	.loc 1 868 0
	sw	$6,36($4)
$LBB257 = .
$LBB256 = .
	.loc 1 93 0
	sb	$9,49($4)
	sb	$8,50($4)
	sb	$7,51($4)
$LBE256 = .
$LBE257 = .
$LBB258 = .
$LBB259 = .
$LBB260 = .
	.loc 3 31 0
#APP
 # 31 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/uapi/asm/swab.h" 1
		wsbh	$3, $3			
	rotr	$3, $3, 16		

 # 0 "" 2
#NO_APP
$LBE260 = .
$LBE259 = .
$LBE258 = .
$LBB261 = .
$LBB262 = .
	.loc 1 93 0
	srl	$5,$3,16
	srl	$6,$3,8
	srl	$4,$3,24
$LBE262 = .
$LBE261 = .
	.loc 1 868 0
	sw	$3,16($sp)
$LBB264 = .
$LBB263 = .
	.loc 1 93 0
	sb	$3,8($2)
	sb	$5,10($2)
	sb	$6,9($2)
	sb	$4,11($2)
	lbu	$3,1($2)
$LBE263 = .
$LBE264 = .
$LBE240 = .
	.loc 1 815 0
	.set	noreorder
	.set	nomacro
	j	$L9
	move	$5,$0
	.set	macro
	.set	reorder

$L17:
$LBB285 = .
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
$LBB265 = .
$LBB266 = .
$LBB267 = .
	.loc 3 31 0 is_stmt 1
	lw	$3,40($3)
#APP
 # 31 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/uapi/asm/swab.h" 1
		wsbh	$3, $3			
	rotr	$3, $3, 16		

 # 0 "" 2
#NO_APP
$LBE267 = .
$LBE266 = .
$LBE265 = .
$LBB268 = .
$LBB269 = .
	.loc 1 93 0
	srl	$7,$3,8
	srl	$6,$3,16
	srl	$4,$3,24
$LBE269 = .
$LBE268 = .
	.loc 1 879 0
	sw	$3,16($sp)
$LBB271 = .
$LBB270 = .
	.loc 1 93 0
	sb	$3,12($2)
	sb	$7,13($2)
	sb	$6,14($2)
$LBE270 = .
$LBE271 = .
$LBE285 = .
	.set	noreorder
	.set	nomacro
	j	$L12
	sb	$4,15($2)
	.set	macro
	.set	reorder

$L11:
$LBB286 = .
	.loc 1 885 0
	lui	$4,%hi(pptpAccInfo)
	addiu	$4,$4,%lo(pptpAccInfo)
	lhu	$3,44($4)
$LBB272 = .
$LBB273 = .
	.file 4 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/checksum.h"
	.loc 4 121 0
	addiu	$2,$17,30
$LBE273 = .
$LBE272 = .
	.loc 1 885 0
	addiu	$3,$3,1
	andi	$3,$3,0xffff
	sh	$3,44($4)
$LBB279 = .
$LBB280 = .
$LBB281 = .
	.loc 3 20 0
#APP
 # 20 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/uapi/asm/swab.h" 1
		wsbh	$3, $3			

 # 0 "" 2
#NO_APP
$LBE281 = .
$LBE280 = .
$LBE279 = .
	.loc 1 885 0
	sh	$3,18($17)
	.loc 1 887 0
	lw	$5,14($17)
$LBB282 = .
$LBB276 = .
	.loc 4 109 0
	lw	$6,18($17)
$LBE276 = .
$LBE282 = .
	.loc 1 886 0
	sh	$0,24($17)
$LBB283 = .
$LBB277 = .
	.loc 4 113 0
	lw	$3,22($17)
	.loc 4 109 0
	addu	$7,$6,$5
	.loc 4 117 0
	lw	$4,26($17)
	.loc 4 110 0
	sltu	$6,$7,$6
	.loc 4 111 0
	addu	$7,$7,$3
	.loc 4 113 0
	addu	$6,$7,$6
	.loc 4 114 0
	sltu	$3,$6,$3
	.loc 4 115 0
	addu	$6,$6,$4
	.loc 4 117 0
	addu	$3,$6,$3
$LBE277 = .
$LBE283 = .
	.loc 1 887 0
	andi	$5,$5,0xf
$LBB284 = .
$LBB278 = .
	.loc 4 104 0
	sll	$5,$5,2
	.loc 4 118 0
	sltu	$4,$3,$4
	.loc 4 104 0
	addu	$5,$8,$5
	.loc 4 119 0
	addu	$3,$4,$3
$L14:
	.loc 4 123 0
	lw	$4,0($2)
	.loc 4 126 0
	addiu	$2,$2,4
	.loc 4 123 0
	addu	$3,$3,$4
	.loc 4 124 0
	sltu	$4,$3,$4
	.loc 4 127 0
	.set	noreorder
	.set	nomacro
	bne	$5,$2,$L14
	addu	$3,$4,$3
	.set	macro
	.set	reorder

$LBB274 = .
$LBB275 = .
	.loc 4 78 0
#APP
 # 78 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/checksum.h" 1
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
	.loc 4 91 0
#NO_APP
	sh	$3,24($17)
$L4:
$LBE275 = .
$LBE274 = .
$LBE278 = .
$LBE284 = .
$LBE286 = .
$LBB287 = .
$LBB288 = .
	.loc 2 58 0
#APP
 # 58 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/irqflags.h" 1
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
$LBE288 = .
$LBE287 = .
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
$LFE3083:
	.size	sync_tx_pptp_gre_seqno, .-sync_tx_pptp_gre_seqno
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	2
$LC0:
	.ascii	"%d\012\000"
	.text
	.align	2
	.globl	ppfw_read_proc
$LFB3087 = .
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
$LFE3087:
	.size	ppfw_read_proc, .-ppfw_read_proc
	.align	2
	.globl	pptpconn_read_proc
$LFB3088 = .
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
$LFE3088:
	.size	pptpconn_read_proc, .-pptpconn_read_proc
	.align	2
	.globl	fastpath_pptp_single_open
$LFB3089 = .
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
$LFE3089:
	.size	fastpath_pptp_single_open, .-fastpath_pptp_single_open
	.align	2
	.globl	pptp_conn_single_open
$LFB3091 = .
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
$LFE3091:
	.size	pptp_conn_single_open, .-pptp_conn_single_open
	.align	2
$LFB3080 = .
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

$LBB291 = .
$LBB292 = .
	lui	$3,%hi(pptpAccInfo)
	addiu	$2,$3,%lo(pptpAccInfo)
	lw	$2,4($2)
	.loc 1 648 0
	lw	$3,%lo(pptpAccInfo)($3)
	xori	$2,$2,0x1
	movn	$3,$0,$2
	move	$2,$3
$L38:
$LBE292 = .
$LBE291 = .
	.loc 1 651 0
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	get_fastpptp_lastxmit
	.cfi_endproc
$LFE3080:
	.size	get_fastpptp_lastxmit, .-get_fastpptp_lastxmit
	.align	2
$LFB3075 = .
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
$LBB295 = .
$LBB296 = .
	.loc 1 85 0
	jal	rtl_get_dev_by_name
	nop

	lui	$3,%hi(pptpAccInfo+56)
$LBE296 = .
$LBE295 = .
	.loc 1 87 0
	lw	$31,20($sp)
$LBB298 = .
$LBB297 = .
	.loc 1 85 0
	sw	$2,%lo(pptpAccInfo+56)($3)
$LBE297 = .
$LBE298 = .
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
$LFE3075:
	.size	set_pptp_device, .-set_pptp_device
	.align	2
	.globl	Get_fast_pptp_fw
$LFB3073 = .
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
$LFE3073:
	.size	Get_fast_pptp_fw, .-Get_fast_pptp_fw
	.align	2
	.globl	is_pptp_device
$LFB3074 = .
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

$LBB299 = .
$LBB300 = .
	.file 5 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/string.h"
	.loc 5 77 0 discriminator 1
	move	$4,$16
#APP
 # 77 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/string.h" 1
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
$LBE300 = .
$LBE299 = .
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
$LFE3074:
	.size	is_pptp_device, .-is_pptp_device
	.align	2
	.globl	Check_GRE_rx_net_device
$LFB3077 = .
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
	andi	$20,$3,0xf

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
$LFE3077:
	.size	Check_GRE_rx_net_device, .-Check_GRE_rx_net_device
	.align	2
	.globl	fast_pptp_filter
$LFB3078 = .
	.loc 1 116 0
	.cfi_startproc
	.set	nomips16
	.ent	fast_pptp_filter
	.type	fast_pptp_filter, @function
fast_pptp_filter:
	.frame	$sp,40,$31		# vars= 0, regs= 5/0, args= 16, gp= 0
	.mask	0x800f0000,-4
	.fmask	0x00000000,0
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
	.set	noreorder
	.set	nomacro
	jal	rtl_ip_hdr
	sw	$18,28($sp)
	.set	macro
	.set	reorder

	.loc 1 126 0
	move	$4,$17
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_len
	move	$16,$2
	.set	macro
	.set	reorder

	sltu	$2,$2,56
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L87
	lw	$31,36($sp)
	.set	macro
	.set	reorder

$LBB301 = .
	.loc 1 127 0
	lw	$2,0($16)
	.loc 1 129 0
	lbu	$3,9($16)
	.loc 1 127 0
	andi	$4,$2,0xf
	.loc 1 129 0
	li	$2,6			# 0x6
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L87
	sll	$4,$4,2
	.set	macro
	.set	reorder

	.loc 1 127 0 discriminator 1
	addu	$4,$16,$4
	.loc 1 129 0 discriminator 1
	lhu	$3,0($4)
	li	$2,47878			# 0xbb06
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L87
	li	$5,1			# 0x1
	.set	macro
	.set	reorder

	.loc 1 130 0
	lw	$2,12($4)
	ext	$2,$2,4,4
	sll	$2,$2,2
	addu	$4,$4,$2
	.loc 1 134 0
	lhu	$2,2($4)
$LBB302 = .
$LBB303 = .
$LBB304 = .
	.loc 3 20 0
#APP
 # 20 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/uapi/asm/swab.h" 1
		wsbh	$3, $2			

 # 0 "" 2
#NO_APP
	andi	$3,$3,0xffff
$LBE304 = .
$LBE303 = .
$LBE302 = .
	.loc 1 134 0
	.set	noreorder
	.set	nomacro
	bne	$3,$5,$L61
	li	$5,8			# 0x8
	.set	macro
	.set	reorder

$LBB305 = .
$LBB306 = .
$LBB307 = .
	.loc 3 20 0 discriminator 1
	lhu	$6,8($4)
#APP
 # 20 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/uapi/asm/swab.h" 1
		wsbh	$6, $6			

 # 0 "" 2
#NO_APP
	andi	$6,$6,0xffff
$LBE307 = .
$LBE306 = .
$LBE305 = .
	.loc 1 135 0 discriminator 1
	bne	$6,$5,$L61
	lbu	$5,16($4)
	.set	noreorder
	.set	nomacro
	bne	$5,$3,$L61
	lui	$18,%hi(pptpAccInfo)
	.set	macro
	.set	reorder

	.loc 1 143 0
	addiu	$18,$18,%lo(pptpAccInfo)
	lw	$2,36($18)
	beq	$2,$0,$L86
	.loc 1 143 0 is_stmt 0 discriminator 1
	lw	$2,20($18)
	beq	$2,$0,$L86
	lw	$2,32($18)
	bne	$2,$0,$L83
$L86:
	.set	noreorder
	.set	nomacro
	j	$L62
	lhu	$2,12($4)
	.set	macro
	.set	reorder

$L83:
	.loc 1 144 0 is_stmt 1
	lhu	$3,18($18)
	lhu	$2,12($4)
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L87
	lw	$31,36($sp)
	.set	macro
	.set	reorder

	.loc 1 144 0 is_stmt 0 discriminator 1
	lhu	$5,30($18)
	lhu	$3,14($4)
	.set	noreorder
	.set	nomacro
	bne	$5,$3,$L88
	lw	$19,32($sp)
	.set	macro
	.set	reorder

$L62:
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
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_dev
	sw	$2,32($18)
	.set	macro
	.set	reorder

$LBB308 = .
	.loc 1 162 0
	move	$4,$17
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_data
	sw	$2,8($18)
	.set	macro
	.set	reorder

	addiu	$2,$2,-8
	lwl	$3,3($2)
	lui	$6,%hi(pptpAccInfo+24)
	addiu	$5,$6,%lo(pptpAccInfo+24)
	lwr	$3,0($2)
$LBE308 = .
$LBB309 = .
	.loc 1 163 0
	move	$4,$17
$LBE309 = .
$LBB310 = .
	.loc 1 162 0
	sw	$3,%lo(pptpAccInfo+24)($6)
	lbu	$3,4($2)
	sb	$3,4($5)
	lbu	$2,5($2)
$LBE310 = .
$LBB311 = .
	.loc 1 163 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_data
	sb	$2,5($5)
	.set	macro
	.set	reorder

	addiu	$2,$2,-14
	lwl	$3,3($2)
	lui	$5,%hi(pptpAccInfo+12)
	addiu	$4,$5,%lo(pptpAccInfo+12)
	lwr	$3,0($2)
	sw	$3,%lo(pptpAccInfo+12)($5)
	lbu	$3,4($2)
	sb	$3,4($4)
	lbu	$2,5($2)
$LBE311 = .
	.loc 1 182 0
	sw	$19,4($18)
	.set	noreorder
	.set	nomacro
	j	$L58
	sb	$2,5($4)
	.set	macro
	.set	reorder

$L61:
$LBB312 = .
$LBB313 = .
$LBB314 = .
	.loc 3 20 0 discriminator 2
#APP
 # 20 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/uapi/asm/swab.h" 1
		wsbh	$2, $2			

 # 0 "" 2
#NO_APP
$LBE314 = .
$LBE313 = .
$LBE312 = .
	.loc 1 189 0 discriminator 2
	li	$3,1			# 0x1
$LBB317 = .
$LBB316 = .
$LBB315 = .
	.loc 3 20 0 discriminator 2
	andi	$2,$2,0xffff
$LBE315 = .
$LBE316 = .
$LBE317 = .
	.loc 1 189 0 discriminator 2
	.set	noreorder
	.set	nomacro
	bne	$2,$3,$L58
	li	$2,13			# 0xd
	.set	macro
	.set	reorder

$LBB318 = .
$LBB319 = .
$LBB320 = .
	.loc 3 20 0
	lhu	$3,8($4)
#APP
 # 20 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/uapi/asm/swab.h" 1
		wsbh	$3, $3			

 # 0 "" 2
#NO_APP
	andi	$3,$3,0xffff
$LBE320 = .
$LBE319 = .
$LBE318 = .
	.loc 1 189 0
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L58
	lui	$18,%hi(pptpAccInfo)
	.set	macro
	.set	reorder

	.loc 1 195 0
	addiu	$18,$18,%lo(pptpAccInfo)
	lw	$2,36($18)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L89
	lui	$2,%hi(pptp_tcp_finished)
	.set	macro
	.set	reorder

	.loc 1 195 0 is_stmt 0 discriminator 1
	lw	$2,20($18)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L89
	lui	$2,%hi(pptp_tcp_finished)
	.set	macro
	.set	reorder

	lw	$2,32($18)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L89
	lui	$2,%hi(pptp_tcp_finished)
	.set	macro
	.set	reorder

	.loc 1 196 0 is_stmt 1
	lhu	$3,18($18)
	lhu	$2,12($4)
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L87
	lw	$31,36($sp)
	.set	macro
	.set	reorder

	.loc 1 201 0
	lui	$2,%hi(pptp_tcp_finished)
$L89:
	sw	$0,%lo(pptp_tcp_finished)($2)
	.loc 1 202 0
	sw	$0,4($18)
$L58:
$LBE301 = .
	.loc 1 293 0
	lw	$31,36($sp)
$L87:
	lw	$19,32($sp)
$L88:
	lw	$18,28($sp)
	lw	$17,24($sp)
	lw	$16,20($sp)
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
	.cfi_restore 19
	.cfi_restore 31
	.end	fast_pptp_filter
	.cfi_endproc
$LFE3078:
	.size	fast_pptp_filter, .-fast_pptp_filter
	.align	2
	.globl	fast_pptp_to_lan
$LFB3079 = .
	.loc 1 469 0
	.cfi_startproc
	.set	nomips16
	.ent	fast_pptp_to_lan
	.type	fast_pptp_to_lan, @function
fast_pptp_to_lan:
	.frame	$sp,48,$31		# vars= 0, regs= 7/0, args= 16, gp= 0
	.mask	0x803f0000,-4
	.fmask	0x00000000,0
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
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_dev
	move	$4,$16
	.set	macro
	.set	reorder

	lw	$3,8($17)
	beq	$3,$2,$L91
$L93:
	.loc 1 484 0
	.set	noreorder
	.set	nomacro
	j	$L128
	move	$2,$0
	.set	macro
	.set	reorder

$L91:
	.loc 1 483 0 discriminator 1
	.set	noreorder
	.set	nomacro
	jal	rtl_ip_hdr
	move	$4,$16
	.set	macro
	.set	reorder

	lbu	$3,9($2)
	li	$2,47			# 0x2f
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L128
	move	$2,$0
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_len
	move	$4,$16
	.set	macro
	.set	reorder

	sltu	$2,$2,20
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L128
	move	$2,$0
	.set	macro
	.set	reorder

	.loc 1 486 0
	.set	noreorder
	.set	nomacro
	jal	rtl_ip_hdr
	move	$4,$16
	.set	macro
	.set	reorder

	move	$19,$2
	.loc 1 487 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_data
	move	$4,$16
	.set	macro
	.set	reorder

	.loc 1 488 0
	lw	$3,0($19)
	andi	$3,$3,0xf
	sll	$3,$3,2
	addu	$3,$2,$3
	.loc 1 490 0
	lbu	$4,1($3)
	li	$2,1			# 0x1
	andi	$4,$4,0x7
	.set	noreorder
	.set	nomacro
	bne	$4,$2,$L128
	move	$2,$0
	.set	macro
	.set	reorder

$LBB321 = .
$LBB322 = .
$LBB323 = .
	.loc 3 20 0
	lhu	$4,2($3)
$LBE323 = .
$LBE322 = .
$LBE321 = .
	.loc 1 490 0
	li	$2,34827			# 0x880b
$LBB326 = .
$LBB325 = .
$LBB324 = .
	.loc 3 20 0
#APP
 # 20 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/uapi/asm/swab.h" 1
		wsbh	$4, $4			

 # 0 "" 2
#NO_APP
	andi	$4,$4,0xffff
$LBE324 = .
$LBE325 = .
$LBE326 = .
	.loc 1 490 0
	.set	noreorder
	.set	nomacro
	bne	$4,$2,$L128
	move	$2,$0
	.set	macro
	.set	reorder

$LBB327 = .
	.loc 1 496 0
	lhu	$4,6($3)
	lhu	$2,30($17)
	bne	$4,$2,$L93
	.loc 1 501 0
	lbu	$4,0($3)
	andi	$4,$4,0x10
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L94
	li	$2,8			# 0x8
	.set	macro
	.set	reorder

$LBB328 = .
$LBB329 = .
$LBB330 = .
	.loc 3 31 0
	lw	$4,8($3)
$LBE330 = .
$LBE329 = .
$LBE328 = .
	.loc 1 503 0
	li	$2,12			# 0xc
$LBB333 = .
$LBB332 = .
$LBB331 = .
	.loc 3 31 0
#APP
 # 31 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/uapi/asm/swab.h" 1
		wsbh	$4, $4			
	rotr	$4, $4, 16		

 # 0 "" 2
#NO_APP
$LBE331 = .
$LBE332 = .
$LBE333 = .
	.loc 1 502 0
	sw	$4,40($17)
$L94:
	.loc 1 506 0
	lb	$6,1($3)
	.loc 1 512 0
	lhu	$4,4($3)
	.loc 1 507 0
	addiu	$5,$2,4
	slt	$6,$6,0
	.loc 1 512 0
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L93
	movn	$2,$5,$6
	.set	macro
	.set	reorder

	.loc 1 509 0
	addu	$3,$3,$2
	.loc 1 540 0
	lbu	$4,0($3)
	bne	$4,$0,$L96
	.loc 1 542 0
	addiu	$3,$3,1
	.set	noreorder
	.set	nomacro
	j	$L97
	li	$5,1			# 0x1
	.set	macro
	.set	reorder

$L96:
	.loc 1 544 0
	li	$6,255			# 0xff
	.set	noreorder
	.set	nomacro
	bne	$4,$6,$L97
	move	$5,$0
	.set	macro
	.set	reorder

	.loc 1 544 0 is_stmt 0 discriminator 1
	lbu	$5,1($3)
	li	$4,3			# 0x3
	bne	$5,$4,$L93
	.loc 1 547 0 is_stmt 1
	lbu	$5,2($3)
	.set	noreorder
	.set	nomacro
	bne	$5,$0,$L110
	addiu	$4,$3,2
	.set	macro
	.set	reorder

	.loc 1 549 0
	addiu	$3,$3,3
$LBE327 = .
	.loc 1 548 0
	.set	noreorder
	.set	nomacro
	j	$L97
	li	$5,3			# 0x3
	.set	macro
	.set	reorder

$L110:
$LBB335 = .
	.loc 1 546 0
	move	$3,$4
	.loc 1 545 0
	li	$5,2			# 0x2
$L97:
	.loc 1 552 0
	lbu	$3,0($3)
	li	$4,33			# 0x21
	.set	noreorder
	.set	nomacro
	beq	$3,$4,$L98
	move	$4,$16
	.set	macro
	.set	reorder

	.loc 1 552 0 is_stmt 0 discriminator 1
	li	$4,253			# 0xfd
	bne	$3,$4,$L93
$LBE335 = .
	.loc 1 563 0 is_stmt 1
	.set	noreorder
	.set	nomacro
	j	$L131
	lw	$3,0($19)
	.set	macro
	.set	reorder

$L129:
$LBB336 = .
	.loc 1 566 0 discriminator 1
	jal	rtl_get_ppp_dev_priv
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L93
	addiu	$5,$19,-2
	.set	macro
	.set	reorder

	.loc 1 569 0
	.set	noreorder
	.set	nomacro
	jal	skb_pull
	move	$4,$16
	.set	macro
	.set	reorder

	.loc 1 570 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_data
	move	$4,$16
	.set	macro
	.set	reorder

	.loc 1 572 0
	li	$3,-3			# 0xfffffffffffffffd
	sb	$3,1($2)
	.loc 1 571 0
	sb	$0,0($2)
	.loc 1 573 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_ppp_dev_priv
	lw	$4,56($17)
	.set	macro
	.set	reorder

	.loc 1 575 0
	move	$4,$2
	move	$5,$16
	.set	noreorder
	.set	nomacro
	jal	rtl_ppp_receive_nonmp_frame
	li	$6,1			# 0x1
	.set	macro
	.set	reorder

	.loc 1 576 0
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L111
	move	$16,$2
	.set	macro
	.set	reorder

	.loc 1 580 0
	sw	$2,0($18)
	.loc 1 582 0
	li	$19,1			# 0x1
$L107:
	.loc 1 593 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_data
	move	$4,$16
	.set	macro
	.set	reorder

	andi	$18,$2,0x3
	.loc 1 594 0
	beq	$18,$0,$L101
	.loc 1 595 0
	.set	noreorder
	.set	nomacro
	jal	rtl_skb_headroom
	move	$4,$16
	.set	macro
	.set	reorder

	sltu	$2,$2,$18
	bne	$2,$0,$L101
$LBB334 = .
	.loc 1 597 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_len
	move	$4,$16
	.set	macro
	.set	reorder

	move	$4,$16
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_data
	move	$20,$2
	.set	macro
	.set	reorder

	move	$4,$16
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_data
	subu	$21,$2,$18
	.set	macro
	.set	reorder

	move	$5,$2
	move	$4,$21
	.set	noreorder
	.set	nomacro
	jal	memmove
	move	$6,$20
	.set	macro
	.set	reorder

$LBE334 = .
	.loc 1 598 0
	move	$4,$16
	move	$5,$18
	.set	noreorder
	.set	nomacro
	jal	rtl_set_skb_data
	li	$6,1			# 0x1
	.set	macro
	.set	reorder

	.loc 1 599 0
	move	$4,$16
	move	$5,$18
	.set	noreorder
	.set	nomacro
	jal	rtl_set_skb_tail
	li	$6,1			# 0x1
	.set	macro
	.set	reorder

$L101:
	.loc 1 605 0
	.set	noreorder
	.set	nomacro
	jal	rtl_skb_reset_network_header
	move	$4,$16
	.set	macro
	.set	reorder

	.loc 1 606 0
	.set	noreorder
	.set	nomacro
	jal	rtl_skb_reset_transport_header
	move	$4,$16
	.set	macro
	.set	reorder

	.loc 1 612 0
	lw	$4,56($17)
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L128
	move	$2,$0
	.set	macro
	.set	reorder

	.loc 1 614 0
	bne	$19,$0,$L104
	.loc 1 615 0
	jal	rtl_get_ppp_dev_priv
	beq	$2,$0,$L104
	.loc 1 616 0
	.set	noreorder
	.set	nomacro
	jal	rtl_get_ppp_dev_priv
	lw	$4,56($17)
	.set	macro
	.set	reorder

	.loc 1 617 0
	move	$4,$16
	.set	noreorder
	.set	nomacro
	jal	rtl_get_skb_len
	move	$18,$2
	.set	macro
	.set	reorder

	addiu	$6,$2,-2
	move	$4,$18
	.set	noreorder
	.set	nomacro
	jal	rtl_inc_ppp_stats
	move	$5,$0
	.set	macro
	.set	reorder

$L104:
	.loc 1 625 0
	lw	$5,56($17)
	.set	noreorder
	.set	nomacro
	jal	rtl_set_skb_dev
	move	$4,$16
	.set	macro
	.set	reorder

	.loc 1 626 0
	.set	noreorder
	.set	nomacro
	j	$L128
	li	$2,1			# 0x1
	.set	macro
	.set	reorder

$L111:
$LBE336 = .
	.loc 1 578 0
	.set	noreorder
	.set	nomacro
	j	$L128
	li	$2,-2			# 0xfffffffffffffffe
	.set	macro
	.set	reorder

$L131:
$LBB337 = .
	.loc 1 566 0
	lw	$4,56($17)
	.loc 1 553 0
	addiu	$5,$5,1
	.loc 1 563 0
	andi	$3,$3,0xf
	sll	$3,$3,2
	addu	$2,$3,$2
	.loc 1 566 0
	.set	noreorder
	.set	nomacro
	bne	$4,$0,$L129
	addu	$19,$5,$2
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	j	$L128
	move	$2,$0
	.set	macro
	.set	reorder

$L98:
	.loc 1 563 0
	lw	$3,0($19)
	.loc 1 553 0
	addiu	$5,$5,1
	.loc 1 563 0
	andi	$3,$3,0xf
	sll	$3,$3,2
	addu	$2,$3,$2
	.loc 1 586 0
	.set	noreorder
	.set	nomacro
	jal	skb_pull
	addu	$5,$5,$2
	.set	macro
	.set	reorder

$LBE337 = .
	.loc 1 477 0
	.set	noreorder
	.set	nomacro
	j	$L107
	move	$19,$0
	.set	macro
	.set	reorder

$L128:
	.loc 1 643 0
	lw	$31,44($sp)
	lw	$21,40($sp)
	lw	$20,36($sp)
	lw	$19,32($sp)
	lw	$18,28($sp)
	lw	$17,24($sp)
	lw	$16,20($sp)
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,48
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
	.end	fast_pptp_to_lan
	.cfi_endproc
$LFE3079:
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
$LFB3081 = .
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
	sw	$17,64($sp)
	.cfi_offset 17, -24
	move	$17,$4
	sw	$31,84($sp)
	sw	$18,68($sp)
	sw	$16,60($sp)
	sw	$21,80($sp)
	sw	$20,76($sp)
	.cfi_offset 31, -4
	.cfi_offset 18, -20
	.cfi_offset 16, -28
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

	.loc 1 666 0
	move	$4,$17
	.set	noreorder
	.set	nomacro
	jal	rtl_ip_hdr
	lbu	$16,12($2)
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
	li	$2,10			# 0xa
	.set	noreorder
	.set	nomacro
	bne	$16,$2,$L133
	andi	$18,$18,0xff00
	.set	macro
	.set	reorder

	.loc 1 668 0 is_stmt 0 discriminator 1
	li	$2,16384			# 0x4000
	.set	noreorder
	.set	nomacro
	bne	$18,$2,$L133
	li	$2,16711680			# 0xff0000
	.set	macro
	.set	reorder

	.loc 1 667 0 is_stmt 1 discriminator 1
	and	$3,$3,$2
	.loc 1 668 0 discriminator 1
	li	$2,4194304			# 0x400000
	.set	noreorder
	.set	nomacro
	bne	$3,$2,$L165
	lui	$18,%hi(pptpAccInfo)
	.set	macro
	.set	reorder

	lui	$2,%hi(pptp_conn_check)
	lw	$3,%lo(pptp_conn_check)($2)
	li	$2,3			# 0x3
	.set	noreorder
	.set	nomacro
	beq	$3,$2,$L134
	move	$2,$0
	.set	macro
	.set	reorder

$L133:
	.loc 1 674 0
	lui	$18,%hi(pptpAccInfo)
$L165:
	addiu	$16,$18,%lo(pptpAccInfo)
	lw	$4,56($16)
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L134
	move	$2,$0
	.set	macro
	.set	reorder

	.loc 1 674 0 is_stmt 0 discriminator 1
	jal	rtl_get_ppp_dev_name
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L134
	move	$2,$0
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	jal	rtl_get_ppp_dev_name
	lw	$4,56($16)
	.set	macro
	.set	reorder

$LBB338 = .
$LBB339 = .
	.loc 5 77 0 is_stmt 1 discriminator 1
	lui	$3,%hi($LC1)
	addiu	$3,$3,%lo($LC1)
#APP
 # 77 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/string.h" 1
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
$LBE339 = .
$LBE338 = .
	.loc 1 674 0 discriminator 1
	.set	noreorder
	.set	nomacro
	bne	$4,$0,$L134
	move	$2,$0
	.set	macro
	.set	reorder

	.loc 1 677 0
	lw	$2,4($16)
	beq	$2,$0,$L136
	.loc 1 677 0 is_stmt 0 discriminator 1
	lw	$4,56($16)
	bne	$4,$0,$L137
$L143:
	.loc 1 762 0 is_stmt 1
	lui	$4,%hi($LC2)
	.set	noreorder
	.set	nomacro
	jal	printk
	addiu	$4,$4,%lo($LC2)
	.set	macro
	.set	reorder

$L162:
	.set	noreorder
	.set	nomacro
	j	$L134
	move	$2,$0
	.set	macro
	.set	reorder

$L137:
	.loc 1 677 0 discriminator 1
	jal	rtl_get_ppp_dev_priv
	beq	$2,$0,$L136
$LBB340 = .
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
	beq	$2,$3,$L134
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
	bne	$2,$0,$L134
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
	beq	$2,$0,$L144
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
	beq	$2,$0,$L138
	move	$4,$21
	.set	macro
	.set	reorder

$L164:
$LBB341 = .
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
	bne	$2,$0,$L160
	move	$17,$2
	.set	macro
	.set	reorder

	j	$L163
$L138:
$LBE341 = .
	.loc 1 706 0 discriminator 1
	.set	noreorder
	.set	nomacro
	jal	rtl_skb_cloned
	move	$4,$21
	.set	macro
	.set	reorder

	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L164
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
	beq	$2,$0,$L142
	move	$17,$21
	.set	macro
	.set	reorder

$LBE340 = .
	.loc 1 707 0
	.set	noreorder
	.set	nomacro
	j	$L164
	move	$4,$21
	.set	macro
	.set	reorder

$L163:
$LBB387 = .
$LBB342 = .
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
	j	$L134
	li	$2,1			# 0x1
	.set	macro
	.set	reorder

$L160:
	.loc 1 713 0
	.set	noreorder
	.set	nomacro
	jal	consume_skb
	move	$4,$21
	.set	macro
	.set	reorder

$L142:
$LBE342 = .
	.loc 1 719 0
	move	$4,$17
	.set	noreorder
	.set	nomacro
	jal	skb_push
	li	$5,50			# 0x32
	.set	macro
	.set	reorder

$LBB343 = .
	.loc 1 720 0
	lw	$3,24($16)
$LBE343 = .
	.loc 1 726 0
	lbu	$6,16($sp)
	li	$4,4			# 0x4
$LBB344 = .
	.loc 1 720 0
	swl	$3,3($2)
	swr	$3,0($2)
	lbu	$3,28($16)
$LBE344 = .
	.loc 1 726 0
	ins	$6,$4,4,4
	.loc 1 722 0
	li	$8,8			# 0x8
$LBB345 = .
	.loc 1 720 0
	sb	$3,4($2)
	lbu	$3,29($16)
$LBE345 = .
	.loc 1 734 0
	move	$5,$0
	.loc 1 730 0
	sb	$20,17($sp)
$LBB346 = .
	.loc 1 720 0
	sb	$3,5($2)
$LBE346 = .
$LBB347 = .
	.loc 1 721 0
	lw	$4,12($16)
$LBE347 = .
	.loc 1 728 0
	li	$3,64			# 0x40
	sh	$3,22($sp)
$LBB348 = .
	.loc 1 721 0
	swl	$4,9($2)
	swr	$4,6($2)
	lbu	$7,16($16)
$LBE348 = .
	.loc 1 734 0
	move	$4,$17
	.loc 1 733 0
	sb	$3,24($sp)
$LBB349 = .
	.loc 1 721 0
	sb	$7,10($2)
	lbu	$7,17($16)
$LBE349 = .
	.loc 1 722 0
	sb	$8,12($2)
	sb	$0,13($2)
$LBB350 = .
	.loc 1 721 0
	sb	$7,11($2)
$LBE350 = .
	.loc 1 731 0
	lw	$19,32($16)
	.loc 1 732 0
	lw	$21,20($16)
	.loc 1 727 0
	li	$2,5			# 0x5
	ins	$6,$2,0,4
	.loc 1 729 0
	li	$2,47			# 0x2f
	.loc 1 727 0
	sb	$6,16($sp)
	.loc 1 729 0
	sb	$2,25($sp)
	.loc 1 731 0
	sw	$19,32($sp)
	.loc 1 734 0
	.set	noreorder
	.set	nomacro
	jal	rtl_set_skb_ip_summed
	sw	$21,28($sp)
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
$LBB351 = .
$LBB352 = .
$LBB353 = .
	.loc 3 20 0
#APP
 # 20 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/uapi/asm/swab.h" 1
		wsbh	$2, $2			

 # 0 "" 2
#NO_APP
$LBE353 = .
$LBE352 = .
$LBE351 = .
	.loc 1 736 0
	addiu	$3,$3,1
	andi	$5,$3,0xffff
	.loc 1 735 0
	sh	$2,18($sp)
$LBB354 = .
$LBB355 = .
$LBB356 = .
	.loc 3 20 0
#APP
 # 20 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/uapi/asm/swab.h" 1
		wsbh	$3, $5			

 # 0 "" 2
#NO_APP
$LBE356 = .
$LBE355 = .
$LBE354 = .
	.loc 1 736 0
	sh	$3,20($sp)
$LBB357 = .
$LBB358 = .
	.loc 4 109 0
	lw	$2,20($sp)
$LBE358 = .
$LBE357 = .
	.loc 1 737 0
	sh	$0,26($sp)
$LBB365 = .
$LBB361 = .
	.loc 4 109 0
	lw	$6,16($sp)
	.loc 4 113 0
	lw	$4,24($sp)
$LBE361 = .
$LBE365 = .
	.loc 1 736 0
	sh	$5,44($16)
$LBB366 = .
$LBB362 = .
	.loc 4 109 0
	addu	$6,$2,$6
	.loc 4 110 0
	sltu	$2,$6,$2
	.loc 4 111 0
	addu	$6,$6,$4
	.loc 4 113 0
	addu	$2,$6,$2
	.loc 4 114 0
	sltu	$4,$2,$4
	.loc 4 115 0
	addu	$2,$2,$21
	.loc 4 117 0
	addu	$4,$2,$4
	.loc 4 119 0
	addu	$2,$4,$19
	.loc 4 118 0
	sltu	$21,$4,$21
	.loc 4 123 0
	addu	$2,$2,$21
$LBE362 = .
$LBE366 = .
$LBB367 = .
	.loc 1 740 0
	move	$4,$17
$LBE367 = .
$LBB368 = .
$LBB363 = .
	.loc 4 124 0
	sltu	$19,$2,$19
$LBE363 = .
$LBE368 = .
	.loc 1 739 0
	sh	$3,46($16)
$LBB369 = .
$LBB364 = .
	.loc 4 125 0
	addu	$2,$19,$2
$LBB359 = .
$LBB360 = .
	.loc 4 78 0
#APP
 # 78 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/checksum.h" 1
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
$LBE360 = .
$LBE359 = .
$LBE364 = .
$LBE369 = .
$LBB370 = .
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
	swl	$5,17($2)
	swr	$5,0($3)
	lw	$5,24($sp)
	swl	$4,7($3)
	swr	$4,4($3)
	lw	$4,28($sp)
	swl	$5,11($3)
	swr	$5,8($3)
	lw	$2,32($sp)
	swl	$4,15($3)
	swr	$4,12($3)
	swl	$2,19($3)
	swr	$2,16($3)
$LBE370 = .
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
	li	$2,2952			# 0xb88
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
	lhu	$7,18($16)
$LBB371 = .
	.loc 1 752 0
	move	$4,$17
$LBE371 = .
	.loc 1 750 0
	addiu	$6,$3,1
	.loc 1 749 0
	sh	$7,42($sp)
$LBB372 = .
$LBB373 = .
$LBB374 = .
	.loc 3 31 0
#APP
 # 31 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/uapi/asm/swab.h" 1
		wsbh	$3, $3			
	rotr	$3, $3, 16		

 # 0 "" 2
#NO_APP
$LBE374 = .
$LBE373 = .
$LBE372 = .
$LBB375 = .
$LBB376 = .
$LBB377 = .
	lw	$5,40($16)
$LBE377 = .
$LBE376 = .
$LBE375 = .
	.loc 1 750 0
	sw	$6,36($16)
$LBB380 = .
$LBB379 = .
$LBB378 = .
	.loc 3 31 0
#APP
 # 31 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/uapi/asm/swab.h" 1
		wsbh	$5, $5			
	rotr	$5, $5, 16		

 # 0 "" 2
#NO_APP
$LBE378 = .
$LBE379 = .
$LBE380 = .
	.loc 1 750 0
	sw	$3,44($sp)
	.loc 1 751 0
	sw	$5,48($sp)
	.loc 1 748 0
	addiu	$2,$2,-50
$LBB381 = .
$LBB382 = .
$LBB383 = .
	.loc 3 20 0
#APP
 # 20 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/uapi/asm/swab.h" 1
		wsbh	$2, $2			

 # 0 "" 2
#NO_APP
$LBE383 = .
$LBE382 = .
$LBE381 = .
$LBB384 = .
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
	swl	$5,37($2)
	swr	$5,0($3)
	lw	$5,44($sp)
	swl	$4,7($3)
	swr	$4,4($3)
	swl	$5,11($3)
	lw	$2,48($sp)
	swr	$5,8($3)
$LBE384 = .
	.loc 1 753 0
	lui	$4,%hi(jiffies)
	lw	$6,%lo(jiffies)($4)
	.loc 1 756 0
	lw	$5,8($16)
$LBB385 = .
	.loc 1 752 0
	swl	$2,15($3)
$LBE385 = .
	.loc 1 756 0
	move	$4,$17
$LBB386 = .
	.loc 1 752 0
	swr	$2,12($3)
$LBE386 = .
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
	j	$L134
	li	$2,1			# 0x1
	.set	macro
	.set	reorder

$L136:
$LBE387 = .
	.loc 1 761 0
	lw	$4,56($16)
	beq	$4,$0,$L143
	.loc 1 763 0
	jal	rtl_get_ppp_dev_priv
	bne	$2,$0,$L162
	.loc 1 764 0
	lui	$4,%hi($LC4)
	.set	noreorder
	.set	nomacro
	jal	printk
	addiu	$4,$4,%lo($LC4)
	.set	macro
	.set	reorder

	move	$2,$0
$L144:
$L134:
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
$LFE3081:
	.size	fast_pptp_to_wan, .-fast_pptp_to_wan
	.align	2
	.globl	fast_pptp_sync_rx_seq
$LFB3082 = .
	.loc 1 773 0
	.cfi_startproc
	.set	nomips16
	.ent	fast_pptp_sync_rx_seq
	.type	fast_pptp_sync_rx_seq, @function
fast_pptp_sync_rx_seq:
	.frame	$sp,24,$31		# vars= 0, regs= 1/0, args= 16, gp= 0
	.mask	0x80000000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-24
	.cfi_def_cfa_offset 24
	sw	$31,20($sp)
	.cfi_offset 31, -4
	.loc 1 775 0
	jal	rtl_ip_hdr
	.loc 1 779 0
	lbu	$3,21($2)
	li	$4,1			# 0x1
	andi	$5,$3,0x7
	.set	noreorder
	.set	nomacro
	bne	$5,$4,$L175
	lw	$31,20($sp)
	.set	macro
	.set	reorder

$LBB388 = .
$LBB389 = .
$LBB390 = .
	.loc 3 20 0
	lhu	$5,22($2)
$LBE390 = .
$LBE389 = .
$LBE388 = .
	.loc 1 779 0
	li	$4,34827			# 0x880b
$LBB393 = .
$LBB392 = .
$LBB391 = .
	.loc 3 20 0
#APP
 # 20 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/uapi/asm/swab.h" 1
		wsbh	$5, $5			

 # 0 "" 2
#NO_APP
	andi	$5,$5,0xffff
$LBE391 = .
$LBE392 = .
$LBE393 = .
	.loc 1 779 0
	bne	$5,$4,$L175
	.loc 1 785 0
	lbu	$4,20($2)
	andi	$4,$4,0x10
	.set	noreorder
	.set	nomacro
	beq	$4,$0,$L176
	seb	$3,$3
	.set	macro
	.set	reorder

	.loc 1 787 0
	lui	$3,%hi(pptpAccInfo)
	addiu	$3,$3,%lo(pptpAccInfo)
	lw	$4,52($3)
$LBB394 = .
$LBB395 = .
$LBB396 = .
	.loc 3 31 0
#APP
 # 31 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/uapi/asm/swab.h" 1
		wsbh	$5, $4			
	rotr	$5, $5, 16		

 # 0 "" 2
#NO_APP
$LBE396 = .
$LBE395 = .
$LBE394 = .
	.loc 1 787 0
	addiu	$4,$4,1
	sw	$4,52($3)
	lbu	$3,21($2)
	sw	$5,28($2)
	.loc 1 789 0
	seb	$3,$3
$L176:
	.set	noreorder
	.set	nomacro
	bgez	$3,$L175
	lw	$31,20($sp)
	.set	macro
	.set	reorder

	.loc 1 791 0
	lui	$3,%hi(pptpAccInfo+48)
$LBB397 = .
$LBB398 = .
$LBB399 = .
	.loc 3 31 0
	lw	$3,%lo(pptpAccInfo+48)($3)
#APP
 # 31 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/uapi/asm/swab.h" 1
		wsbh	$3, $3			
	rotr	$3, $3, 16		

 # 0 "" 2
#NO_APP
$LBE399 = .
$LBE398 = .
$LBE397 = .
	.loc 1 791 0
	sw	$3,32($2)
	.loc 1 795 0
	lw	$31,20($sp)
$L175:
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,24
	.set	macro
	.set	reorder

	.cfi_def_cfa_offset 0
	.cfi_restore 31
	.end	fast_pptp_sync_rx_seq
	.cfi_endproc
$LFE3082:
	.size	fast_pptp_sync_rx_seq, .-fast_pptp_sync_rx_seq
	.align	2
	.globl	pptpconn_write_proc
$LFB3085 = .
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
	bne	$4,$0,$L187
	.loc 1 916 0
	.set	noreorder
	.set	nomacro
	beq	$5,$0,$L187
	or	$4,$6,$5
	.set	macro
	.set	reorder

	.loc 1 910 0 discriminator 1
	addiu	$sp,$sp,-208
	.cfi_def_cfa_offset 208
$LBB400 = .
$LBB401 = .
	.loc 1 916 0 discriminator 1
	addu	$2,$6,$5
$LBE401 = .
$LBE400 = .
	.loc 1 910 0 discriminator 1
	sw	$31,204($sp)
	.cfi_offset 31, -4
$LBB404 = .
$LBB402 = .
	.loc 1 916 0 discriminator 1
	or	$2,$4,$2
	lw	$4,24($28)
	and	$2,$2,$4
$LBE402 = .
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L188
	lw	$31,204($sp)
	.set	macro
	.set	reorder

$LBB403 = .
	move	$4,$sp
#APP
 # 916 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/fastpath-0.1/fast_pptp_core.c" 1
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
$LBE403 = .
$LBE404 = .
	.set	noreorder
	.set	nomacro
	beq	$6,$0,$L181
	move	$3,$sp
	.set	macro
	.set	reorder

	.loc 1 920 0
	.set	noreorder
	.set	nomacro
	j	$L188
	lw	$31,204($sp)
	.set	macro
	.set	reorder

$L182:
$LBB405 = .
$LBB406 = .
	.loc 1 902 0
	addu	$2,$6,$4
	.loc 1 903 0
	addiu	$3,$3,1
$L181:
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
	bne	$5,$0,$L182
	addiu	$6,$6,-48
	.set	macro
	.set	reorder

$LBE406 = .
$LBE405 = .
	.loc 1 917 0
	lui	$3,%hi(pptp_conn_check)
	sw	$2,%lo(pptp_conn_check)($3)
	.loc 1 920 0
	lw	$31,204($sp)
$L188:
	li	$2,-14			# 0xfffffffffffffff2
	.set	noreorder
	.set	nomacro
	j	$31
	addiu	$sp,$sp,208
	.set	macro
	.set	reorder

	.cfi_def_cfa_offset 0
	.cfi_restore 31
$L187:
	.set	noreorder
	.set	nomacro
	j	$31
	li	$2,-14			# 0xfffffffffffffff2
	.set	macro
	.set	reorder

	.end	pptpconn_write_proc
	.cfi_endproc
$LFE3085:
	.size	pptpconn_write_proc, .-pptpconn_write_proc
	.align	2
$LFB3092 = .
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
$LFE3092:
	.size	pptp_conn_single_write, .-pptp_conn_single_write
	.align	2
	.globl	ppfw_write_proc
$LFB3086 = .
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
	bne	$2,$0,$L206
	move	$16,$6
	.set	macro
	.set	reorder

	move	$18,$5
$LBB407 = .
$LBB408 = .
	.file 6 "include/linux/slub_def.h"
	.loc 6 174 0
	addiu	$4,$6,32
	.set	noreorder
	.set	nomacro
	jal	__kmalloc
	li	$5,32			# 0x20
	.set	macro
	.set	reorder

$LBE408 = .
$LBE407 = .
	.loc 1 939 0
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L206
	move	$17,$2
	.set	macro
	.set	reorder

	.loc 1 942 0
	.set	noreorder
	.set	nomacro
	beq	$18,$0,$L194
	or	$3,$18,$16
	.set	macro
	.set	reorder

$LBB409 = .
$LBB410 = .
	.loc 1 942 0 is_stmt 0 discriminator 1
	addu	$2,$18,$16
	or	$2,$3,$2
	lw	$3,24($28)
	and	$2,$2,$3
$LBE410 = .
	.set	noreorder
	.set	nomacro
	bne	$2,$0,$L194
	move	$4,$17
	.set	macro
	.set	reorder

$LBB411 = .
	move	$5,$18
	move	$6,$16
#APP
 # 942 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/fastpath-0.1/fast_pptp_core.c" 1
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
$LBE411 = .
$LBE409 = .
	.set	noreorder
	.set	nomacro
	bne	$6,$0,$L194
	move	$5,$17
	.set	macro
	.set	reorder

	.loc 1 942 0
	.set	noreorder
	.set	nomacro
	j	$L195
	move	$3,$0
	.set	macro
	.set	reorder

$L196:
$LBB412 = .
$LBB413 = .
	.loc 1 902 0 is_stmt 1
	addu	$3,$9,$7
	.loc 1 903 0
	addiu	$5,$5,1
$L195:
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
	bne	$8,$0,$L196
	addiu	$9,$9,-48
	.set	macro
	.set	reorder

$LBE413 = .
$LBE412 = .
$LBB414 = .
	.loc 1 946 0
	lui	$4,%hi(pptpAccInfo)
$LBE414 = .
	.loc 1 943 0
	lui	$18,%hi(fast_pptp_fw)
$LBB415 = .
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

$LBE415 = .
	.loc 1 973 0
	lw	$2,%lo(fast_pptp_fw)($18)
	.set	noreorder
	.set	nomacro
	beq	$2,$0,$L197
	lui	$3,%hi(sync_tx_pptp_gre_seqno)
	.set	macro
	.set	reorder

	.loc 1 975 0
	addiu	$3,$3,%lo(sync_tx_pptp_gre_seqno)
	lui	$2,%hi(sync_tx_pptp_gre_seqno_hook)
	.set	noreorder
	.set	nomacro
	j	$L198
	sw	$3,%lo(sync_tx_pptp_gre_seqno_hook)($2)
	.set	macro
	.set	reorder

$L197:
	.loc 1 979 0
	lui	$2,%hi(sync_tx_pptp_gre_seqno_hook)
	sw	$0,%lo(sync_tx_pptp_gre_seqno_hook)($2)
$L198:
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
	j	$L192
	move	$2,$16
	.set	macro
	.set	reorder

$L194:
	.loc 1 986 0
	.set	noreorder
	.set	nomacro
	jal	kfree
	move	$4,$17
	.set	macro
	.set	reorder

$L206:
	.loc 1 987 0
	li	$2,-14			# 0xfffffffffffffff2
$L192:
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
$LFE3086:
	.size	ppfw_write_proc, .-ppfw_write_proc
	.align	2
$LFB3090 = .
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
$LFE3090:
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
$LFB3093 = .
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

$LBB416 = .
	.loc 1 1113 0
	lui	$4,%hi(pptpAccInfo)
$LBE416 = .
	.loc 1 1096 0
	lui	$3,%hi(res_check_pptp)
$LBB417 = .
	.loc 1 1113 0
	addiu	$4,$4,%lo(pptpAccInfo)
	move	$5,$0
	li	$6,64			# 0x40
	jal	memset
	sw	$2,%lo(res_check_pptp)($3)

$LBE417 = .
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
$LFE3093:
	.size	fast_pptp_init, .-fast_pptp_init
	.section	.exit.text,"ax",@progbits
	.align	2
	.globl	fast_pptp_exit
$LFB3094 = .
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
	beq	$2,$0,$L211
	sw	$0,%lo(fast_pptp_fw)($3)

	.loc 1 1129 0
	lui	$4,%hi($LC5)
	lui	$5,%hi(proc_root)
	addiu	$4,$4,%lo($LC5)
	jal	remove_proc_entry
	addiu	$5,$5,%lo(proc_root)

	.loc 1 1133 0
	sw	$0,%lo(res1)($16)
$L211:
	.loc 1 1136 0
	lui	$16,%hi(res_check_pptp)
	lw	$2,%lo(res_check_pptp)($16)
	beq	$2,$0,$L210
	lui	$4,%hi($LC6)

	.loc 1 1138 0
	lui	$5,%hi(proc_root)
	addiu	$4,$4,%lo($LC6)
	jal	remove_proc_entry
	addiu	$5,$5,%lo(proc_root)

	.loc 1 1142 0
	sw	$0,%lo(res_check_pptp)($16)
$L210:
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
$LFE3094:
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
	.file 7 "include/uapi/asm-generic/int-ll64.h"
	.file 8 "include/asm-generic/int-ll64.h"
	.file 9 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/include/uapi/asm-generic/posix_types.h"
	.file 10 "include/uapi/linux/types.h"
	.file 11 "include/linux/types.h"
	.file 12 "include/asm-generic/atomic-long.h"
	.file 13 "include/linux/seqlock.h"
	.file 14 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/page.h"
	.file 15 "include/uapi/linux/in.h"
	.file 16 "include/uapi/linux/if_link.h"
	.file 17 "include/uapi/linux/rtnetlink.h"
	.file 18 "include/net/ndisc.h"
	.file 19 "include/linux/inetdevice.h"
	.file 20 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/bitops.h"
	.file 21 "include/linux/kmemleak.h"
	.file 22 "include/linux/log2.h"
	.file 23 "include/asm-generic/getorder.h"
	.file 24 "include/linux/slab.h"
	.file 25 "include/uapi/linux/swab.h"
	.file 26 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/thread_info.h"
	.file 27 "include/net/inet_frag.h"
	.file 28 "include/linux/etherdevice.h"
	.file 29 "include/linux/export.h"
	.file 30 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/cpu-info.h"
	.file 31 "include/linux/printk.h"
	.file 32 "include/linux/kernel.h"
	.file 33 "include/linux/cpumask.h"
	.file 34 "include/linux/time.h"
	.file 35 "include/linux/highuid.h"
	.file 36 "include/linux/seq_file.h"
	.file 37 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/io.h"
	.file 38 "include/linux/mm.h"
	.file 39 "include/linux/mmzone.h"
	.file 40 "include/linux/jiffies.h"
	.file 41 "include/linux/workqueue.h"
	.file 42 "include/linux/sched.h"
	.file 43 "include/linux/quota.h"
	.file 44 "include/linux/interrupt.h"
	.file 45 "include/linux/kernel_stat.h"
	.file 46 "include/linux/ioport.h"
	.file 47 "include/linux/debug_locks.h"
	.file 48 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/pgtable-32.h"
	.file 49 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/pgtable.h"
	.file 50 "include/asm-generic/pgtable.h"
	.file 51 "include/linux/vmstat.h"
	.file 52 "include/linux/netfilter.h"
	.file 53 "include/net/net_namespace.h"
	.file 54 "include/net/sock.h"
	.file 55 "include/net/inet_sock.h"
	.file 56 "include/net/ip.h"
	.file 57 "include/net/inet_connection_sock.h"
	.file 58 "include/net/route.h"
	.file 59 "include/net/arp.h"
	.file 60 "include/linux/netfilter/x_tables.h"
	.file 61 "include/net/rtl/fastpath/fastpath_core.h"
	.file 62 "include/uapi/linux/netfilter.h"
	.file 63 "/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/linux-rtkmipsel_rtl8197f/linux-3.10.49/arch/mips/include/asm/bug.h"
	.section	.debug_info,"",@progbits
$Ldebug_info0:
	.4byte	0x1c55
	.2byte	0x4
	.4byte	$Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	$LASF344
	.byte	0x1
	.4byte	$LASF345
	.4byte	$LASF346
	.4byte	$Ldebug_ranges0+0x2f8
	.4byte	0
	.4byte	$Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	$LASF0
	.uleb128 0x3
	.4byte	$LASF3
	.byte	0x7
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
	.byte	0x7
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
	.byte	0x7
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
	.byte	0x8
	.byte	0x10
	.4byte	0x37
	.uleb128 0x5
	.ascii	"u16\000"
	.byte	0x8
	.byte	0x13
	.4byte	0x50
	.uleb128 0x5
	.ascii	"u32\000"
	.byte	0x8
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
	.byte	0x9
	.byte	0x43
	.4byte	0x69
	.uleb128 0x3
	.4byte	$LASF13
	.byte	0x9
	.byte	0x44
	.4byte	0x57
	.uleb128 0x3
	.4byte	$LASF14
	.byte	0x9
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
	.byte	0xa
	.byte	0x21
	.4byte	0x45
	.uleb128 0x3
	.4byte	$LASF17
	.byte	0xa
	.byte	0x23
	.4byte	0x5e
	.uleb128 0x3
	.4byte	$LASF18
	.byte	0xa
	.byte	0x27
	.4byte	0x45
	.uleb128 0x3
	.4byte	$LASF19
	.byte	0xa
	.byte	0x28
	.4byte	0x5e
	.uleb128 0x3
	.4byte	$LASF20
	.byte	0xb
	.byte	0x1d
	.4byte	0x111
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.4byte	$LASF21
	.uleb128 0x3
	.4byte	$LASF22
	.byte	0xb
	.byte	0x2d
	.4byte	0xc2
	.uleb128 0x3
	.4byte	$LASF23
	.byte	0xb
	.byte	0x36
	.4byte	0xac
	.uleb128 0x3
	.4byte	$LASF24
	.byte	0xb
	.byte	0x3b
	.4byte	0xb7
	.uleb128 0x3
	.4byte	$LASF25
	.byte	0xb
	.byte	0x9d
	.4byte	0x69
	.uleb128 0x7
	.uleb128 0x3
	.4byte	$LASF26
	.byte	0xb
	.byte	0xb1
	.4byte	0x144
	.uleb128 0x8
	.4byte	$LASF27
	.uleb128 0x8
	.4byte	$LASF28
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	$LASF29
	.uleb128 0x8
	.4byte	$LASF30
	.uleb128 0x3
	.4byte	$LASF31
	.byte	0xc
	.byte	0x8d
	.4byte	0x145
	.uleb128 0x8
	.4byte	$LASF32
	.uleb128 0x3
	.4byte	$LASF33
	.byte	0xd
	.byte	0x29
	.4byte	0x171
	.uleb128 0x9
	.byte	0x4
	.uleb128 0x7
	.uleb128 0x3
	.4byte	$LASF34
	.byte	0xe
	.byte	0x69
	.4byte	0x183
	.uleb128 0x6
	.byte	0x4
	.4byte	0x195
	.uleb128 0x8
	.4byte	$LASF35
	.uleb128 0x8
	.4byte	$LASF36
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1a5
	.uleb128 0xa
	.4byte	0x1b0
	.uleb128 0xb
	.4byte	0x181
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1b6
	.uleb128 0xa
	.4byte	0x1c1
	.uleb128 0xb
	.4byte	0x9e
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x118
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.4byte	$LASF37
	.uleb128 0x8
	.4byte	$LASF38
	.uleb128 0x8
	.4byte	$LASF39
	.uleb128 0xc
	.ascii	"pid\000"
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1e3
	.uleb128 0x8
	.4byte	$LASF40
	.uleb128 0x8
	.4byte	$LASF41
	.uleb128 0x8
	.4byte	$LASF42
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1f8
	.uleb128 0xd
	.4byte	0xd3
	.uleb128 0x8
	.4byte	$LASF43
	.uleb128 0x8
	.4byte	$LASF44
	.uleb128 0x8
	.4byte	$LASF45
	.uleb128 0x8
	.4byte	$LASF46
	.uleb128 0x8
	.4byte	$LASF47
	.uleb128 0x6
	.byte	0x4
	.4byte	0x37
	.uleb128 0x8
	.4byte	$LASF48
	.uleb128 0x8
	.4byte	$LASF49
	.uleb128 0xe
	.byte	0x4
	.byte	0xf
	.byte	0x19
	.4byte	0x2ba
	.uleb128 0xf
	.4byte	$LASF50
	.sleb128 0
	.uleb128 0xf
	.4byte	$LASF51
	.sleb128 1
	.uleb128 0xf
	.4byte	$LASF52
	.sleb128 2
	.uleb128 0xf
	.4byte	$LASF53
	.sleb128 4
	.uleb128 0xf
	.4byte	$LASF54
	.sleb128 6
	.uleb128 0xf
	.4byte	$LASF55
	.sleb128 8
	.uleb128 0xf
	.4byte	$LASF56
	.sleb128 12
	.uleb128 0xf
	.4byte	$LASF57
	.sleb128 17
	.uleb128 0xf
	.4byte	$LASF58
	.sleb128 22
	.uleb128 0xf
	.4byte	$LASF59
	.sleb128 33
	.uleb128 0xf
	.4byte	$LASF60
	.sleb128 46
	.uleb128 0xf
	.4byte	$LASF61
	.sleb128 47
	.uleb128 0xf
	.4byte	$LASF62
	.sleb128 41
	.uleb128 0xf
	.4byte	$LASF63
	.sleb128 50
	.uleb128 0xf
	.4byte	$LASF64
	.sleb128 51
	.uleb128 0xf
	.4byte	$LASF65
	.sleb128 94
	.uleb128 0xf
	.4byte	$LASF66
	.sleb128 103
	.uleb128 0xf
	.4byte	$LASF67
	.sleb128 108
	.uleb128 0xf
	.4byte	$LASF68
	.sleb128 132
	.uleb128 0xf
	.4byte	$LASF69
	.sleb128 136
	.uleb128 0xf
	.4byte	$LASF70
	.sleb128 255
	.uleb128 0xf
	.4byte	$LASF71
	.sleb128 256
	.byte	0
	.uleb128 0x10
	.4byte	$LASF347
	.byte	0x4
	.byte	0x3e
	.byte	0x2d
	.4byte	0x2eb
	.uleb128 0xf
	.4byte	$LASF72
	.sleb128 0
	.uleb128 0xf
	.4byte	$LASF73
	.sleb128 1
	.uleb128 0xf
	.4byte	$LASF74
	.sleb128 2
	.uleb128 0xf
	.4byte	$LASF75
	.sleb128 3
	.uleb128 0xf
	.4byte	$LASF76
	.sleb128 4
	.uleb128 0xf
	.4byte	$LASF77
	.sleb128 5
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x21c
	.uleb128 0x8
	.4byte	$LASF78
	.uleb128 0x8
	.4byte	$LASF79
	.uleb128 0xc
	.ascii	"net\000"
	.uleb128 0x8
	.4byte	$LASF80
	.uleb128 0xe
	.byte	0x4
	.byte	0x10
	.byte	0x65
	.4byte	0x3e0
	.uleb128 0xf
	.4byte	$LASF81
	.sleb128 0
	.uleb128 0xf
	.4byte	$LASF82
	.sleb128 1
	.uleb128 0xf
	.4byte	$LASF83
	.sleb128 2
	.uleb128 0xf
	.4byte	$LASF84
	.sleb128 3
	.uleb128 0xf
	.4byte	$LASF85
	.sleb128 4
	.uleb128 0xf
	.4byte	$LASF86
	.sleb128 5
	.uleb128 0xf
	.4byte	$LASF87
	.sleb128 6
	.uleb128 0xf
	.4byte	$LASF88
	.sleb128 7
	.uleb128 0xf
	.4byte	$LASF89
	.sleb128 8
	.uleb128 0xf
	.4byte	$LASF90
	.sleb128 9
	.uleb128 0xf
	.4byte	$LASF91
	.sleb128 10
	.uleb128 0xf
	.4byte	$LASF92
	.sleb128 11
	.uleb128 0xf
	.4byte	$LASF93
	.sleb128 12
	.uleb128 0xf
	.4byte	$LASF94
	.sleb128 13
	.uleb128 0xf
	.4byte	$LASF95
	.sleb128 14
	.uleb128 0xf
	.4byte	$LASF96
	.sleb128 15
	.uleb128 0xf
	.4byte	$LASF97
	.sleb128 16
	.uleb128 0xf
	.4byte	$LASF98
	.sleb128 17
	.uleb128 0xf
	.4byte	$LASF99
	.sleb128 18
	.uleb128 0xf
	.4byte	$LASF100
	.sleb128 19
	.uleb128 0xf
	.4byte	$LASF101
	.sleb128 20
	.uleb128 0xf
	.4byte	$LASF102
	.sleb128 21
	.uleb128 0xf
	.4byte	$LASF103
	.sleb128 22
	.uleb128 0xf
	.4byte	$LASF104
	.sleb128 23
	.uleb128 0xf
	.4byte	$LASF105
	.sleb128 24
	.uleb128 0xf
	.4byte	$LASF106
	.sleb128 25
	.uleb128 0xf
	.4byte	$LASF107
	.sleb128 26
	.uleb128 0xf
	.4byte	$LASF108
	.sleb128 27
	.uleb128 0xf
	.4byte	$LASF109
	.sleb128 28
	.uleb128 0xf
	.4byte	$LASF110
	.sleb128 29
	.uleb128 0xf
	.4byte	$LASF111
	.sleb128 30
	.uleb128 0xf
	.4byte	$LASF112
	.sleb128 31
	.uleb128 0xf
	.4byte	$LASF113
	.sleb128 32
	.uleb128 0xf
	.4byte	$LASF114
	.sleb128 33
	.uleb128 0xf
	.4byte	$LASF115
	.sleb128 34
	.byte	0
	.uleb128 0x8
	.4byte	$LASF116
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1ed
	.uleb128 0x11
	.byte	0x4
	.byte	0x11
	.2byte	0x167
	.4byte	0x455
	.uleb128 0xf
	.4byte	$LASF117
	.sleb128 0
	.uleb128 0xf
	.4byte	$LASF118
	.sleb128 1
	.uleb128 0xf
	.4byte	$LASF119
	.sleb128 2
	.uleb128 0xf
	.4byte	$LASF120
	.sleb128 3
	.uleb128 0xf
	.4byte	$LASF121
	.sleb128 4
	.uleb128 0xf
	.4byte	$LASF122
	.sleb128 5
	.uleb128 0xf
	.4byte	$LASF123
	.sleb128 6
	.uleb128 0xf
	.4byte	$LASF124
	.sleb128 7
	.uleb128 0xf
	.4byte	$LASF125
	.sleb128 8
	.uleb128 0xf
	.4byte	$LASF126
	.sleb128 9
	.uleb128 0xf
	.4byte	$LASF127
	.sleb128 10
	.uleb128 0xf
	.4byte	$LASF128
	.sleb128 11
	.uleb128 0xf
	.4byte	$LASF129
	.sleb128 12
	.uleb128 0xf
	.4byte	$LASF130
	.sleb128 13
	.uleb128 0xf
	.4byte	$LASF131
	.sleb128 14
	.uleb128 0xf
	.4byte	$LASF132
	.sleb128 15
	.byte	0
	.uleb128 0x8
	.4byte	$LASF133
	.uleb128 0x8
	.4byte	$LASF134
	.uleb128 0xe
	.byte	0x4
	.byte	0x12
	.byte	0x1b
	.4byte	0x4aa
	.uleb128 0xf
	.4byte	$LASF135
	.sleb128 0
	.uleb128 0xf
	.4byte	$LASF136
	.sleb128 1
	.uleb128 0xf
	.4byte	$LASF137
	.sleb128 2
	.uleb128 0xf
	.4byte	$LASF138
	.sleb128 3
	.uleb128 0xf
	.4byte	$LASF139
	.sleb128 4
	.uleb128 0xf
	.4byte	$LASF140
	.sleb128 5
	.uleb128 0xf
	.4byte	$LASF141
	.sleb128 6
	.uleb128 0xf
	.4byte	$LASF142
	.sleb128 24
	.uleb128 0xf
	.4byte	$LASF143
	.sleb128 25
	.uleb128 0xf
	.4byte	$LASF144
	.sleb128 31
	.uleb128 0xf
	.4byte	$LASF145
	.sleb128 32
	.byte	0
	.uleb128 0x8
	.4byte	$LASF146
	.uleb128 0x8
	.4byte	$LASF147
	.uleb128 0x8
	.4byte	$LASF148
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
	.uleb128 0xe
	.byte	0x4
	.byte	0x13
	.byte	0xf
	.4byte	0x57d
	.uleb128 0xf
	.4byte	$LASF154
	.sleb128 1
	.uleb128 0xf
	.4byte	$LASF155
	.sleb128 2
	.uleb128 0xf
	.4byte	$LASF156
	.sleb128 3
	.uleb128 0xf
	.4byte	$LASF157
	.sleb128 4
	.uleb128 0xf
	.4byte	$LASF158
	.sleb128 5
	.uleb128 0xf
	.4byte	$LASF159
	.sleb128 6
	.uleb128 0xf
	.4byte	$LASF160
	.sleb128 7
	.uleb128 0xf
	.4byte	$LASF161
	.sleb128 8
	.uleb128 0xf
	.4byte	$LASF162
	.sleb128 9
	.uleb128 0xf
	.4byte	$LASF163
	.sleb128 10
	.uleb128 0xf
	.4byte	$LASF164
	.sleb128 11
	.uleb128 0xf
	.4byte	$LASF165
	.sleb128 12
	.uleb128 0xf
	.4byte	$LASF166
	.sleb128 13
	.uleb128 0xf
	.4byte	$LASF167
	.sleb128 14
	.uleb128 0xf
	.4byte	$LASF168
	.sleb128 15
	.uleb128 0xf
	.4byte	$LASF169
	.sleb128 16
	.uleb128 0xf
	.4byte	$LASF170
	.sleb128 17
	.uleb128 0xf
	.4byte	$LASF171
	.sleb128 18
	.uleb128 0xf
	.4byte	$LASF172
	.sleb128 19
	.uleb128 0xf
	.4byte	$LASF173
	.sleb128 20
	.uleb128 0xf
	.4byte	$LASF174
	.sleb128 21
	.uleb128 0xf
	.4byte	$LASF175
	.sleb128 22
	.uleb128 0xf
	.4byte	$LASF176
	.sleb128 23
	.uleb128 0xf
	.4byte	$LASF177
	.sleb128 24
	.uleb128 0xf
	.4byte	$LASF178
	.sleb128 25
	.uleb128 0xf
	.4byte	$LASF179
	.sleb128 26
	.uleb128 0xf
	.4byte	$LASF180
	.sleb128 27
	.byte	0
	.uleb128 0x12
	.4byte	$LASF181
	.byte	0x3
	.byte	0x12
	.4byte	0x45
	.byte	0x3
	.4byte	0x597
	.uleb128 0x13
	.ascii	"x\000"
	.byte	0x3
	.byte	0x12
	.4byte	0x45
	.byte	0
	.uleb128 0x12
	.4byte	$LASF182
	.byte	0x3
	.byte	0x1d
	.4byte	0x5e
	.byte	0x3
	.4byte	0x5b1
	.uleb128 0x13
	.ascii	"x\000"
	.byte	0x3
	.byte	0x1d
	.4byte	0x5e
	.byte	0
	.uleb128 0x14
	.ascii	"fls\000"
	.byte	0x14
	.2byte	0x234
	.4byte	0x57
	.byte	0x3
	.4byte	0x5d7
	.uleb128 0x15
	.ascii	"x\000"
	.byte	0x14
	.2byte	0x234
	.4byte	0x57
	.uleb128 0x16
	.ascii	"r\000"
	.byte	0x14
	.2byte	0x236
	.4byte	0x57
	.byte	0
	.uleb128 0x17
	.ascii	"BUG\000"
	.byte	0x3f
	.byte	0xb
	.byte	0x3
	.uleb128 0x18
	.4byte	$LASF197
	.byte	0x15
	.byte	0x40
	.byte	0x3
	.4byte	0x618
	.uleb128 0x13
	.ascii	"ptr\000"
	.byte	0x15
	.byte	0x40
	.4byte	0x618
	.uleb128 0x19
	.4byte	$LASF183
	.byte	0x15
	.byte	0x40
	.4byte	0x123
	.uleb128 0x19
	.4byte	$LASF184
	.byte	0x15
	.byte	0x40
	.4byte	0x57
	.uleb128 0x13
	.ascii	"gfp\000"
	.byte	0x15
	.byte	0x41
	.4byte	0x139
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x61e
	.uleb128 0x1a
	.uleb128 0x12
	.4byte	$LASF185
	.byte	0x6
	.byte	0x6f
	.4byte	0x181
	.byte	0x3
	.4byte	0x65c
	.uleb128 0x19
	.4byte	$LASF183
	.byte	0x6
	.byte	0x6f
	.4byte	0x123
	.uleb128 0x19
	.4byte	$LASF186
	.byte	0x6
	.byte	0x6f
	.4byte	0x139
	.uleb128 0x19
	.4byte	$LASF187
	.byte	0x6
	.byte	0x6f
	.4byte	0x69
	.uleb128 0x1b
	.ascii	"ret\000"
	.byte	0x6
	.byte	0x71
	.4byte	0x181
	.byte	0
	.uleb128 0x12
	.4byte	$LASF188
	.byte	0x6
	.byte	0x8c
	.4byte	0x181
	.byte	0x3
	.4byte	0x68c
	.uleb128 0x13
	.ascii	"s\000"
	.byte	0x6
	.byte	0x8c
	.4byte	0x68c
	.uleb128 0x19
	.4byte	$LASF189
	.byte	0x6
	.byte	0x8c
	.4byte	0x139
	.uleb128 0x19
	.4byte	$LASF183
	.byte	0x6
	.byte	0x8c
	.4byte	0x123
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x20c
	.uleb128 0x12
	.4byte	$LASF190
	.byte	0x6
	.byte	0x92
	.4byte	0x181
	.byte	0x3
	.4byte	0x6c4
	.uleb128 0x19
	.4byte	$LASF183
	.byte	0x6
	.byte	0x92
	.4byte	0x123
	.uleb128 0x19
	.4byte	$LASF186
	.byte	0x6
	.byte	0x92
	.4byte	0x139
	.uleb128 0x19
	.4byte	$LASF187
	.byte	0x6
	.byte	0x92
	.4byte	0x69
	.byte	0
	.uleb128 0x12
	.4byte	$LASF191
	.byte	0x16
	.byte	0x20
	.4byte	0x57
	.byte	0x3
	.4byte	0x6de
	.uleb128 0x13
	.ascii	"n\000"
	.byte	0x16
	.byte	0x20
	.4byte	0x93
	.byte	0
	.uleb128 0x12
	.4byte	$LASF192
	.byte	0x17
	.byte	0xd
	.4byte	0x57
	.byte	0x3
	.4byte	0x705
	.uleb128 0x19
	.4byte	$LASF183
	.byte	0x17
	.byte	0xd
	.4byte	0x9e
	.uleb128 0x1c
	.4byte	$LASF187
	.byte	0x17
	.byte	0xf
	.4byte	0x57
	.byte	0
	.uleb128 0x12
	.4byte	$LASF193
	.byte	0x6
	.byte	0x98
	.4byte	0x181
	.byte	0x3
	.4byte	0x737
	.uleb128 0x19
	.4byte	$LASF183
	.byte	0x6
	.byte	0x98
	.4byte	0x123
	.uleb128 0x19
	.4byte	$LASF186
	.byte	0x6
	.byte	0x98
	.4byte	0x139
	.uleb128 0x1c
	.4byte	$LASF187
	.byte	0x6
	.byte	0x9a
	.4byte	0x69
	.byte	0
	.uleb128 0x12
	.4byte	$LASF194
	.byte	0x18
	.byte	0xed
	.4byte	0x57
	.byte	0x3
	.4byte	0x753
	.uleb128 0x19
	.4byte	$LASF183
	.byte	0x18
	.byte	0xed
	.4byte	0x123
	.byte	0
	.uleb128 0x12
	.4byte	$LASF195
	.byte	0x4
	.byte	0x4c
	.4byte	0xf0
	.byte	0x3
	.4byte	0x76f
	.uleb128 0x13
	.ascii	"sum\000"
	.byte	0x4
	.byte	0x4c
	.4byte	0xfb
	.byte	0
	.uleb128 0x1d
	.4byte	$LASF348
	.byte	0x1
	.2byte	0x285
	.4byte	0x9e
	.byte	0x1
	.uleb128 0x12
	.4byte	$LASF196
	.byte	0x2
	.byte	0x23
	.4byte	0x9e
	.byte	0x3
	.4byte	0x798
	.uleb128 0x1c
	.4byte	$LASF186
	.byte	0x2
	.byte	0x25
	.4byte	0x9e
	.byte	0
	.uleb128 0x18
	.4byte	$LASF198
	.byte	0x1
	.byte	0x5a
	.byte	0x3
	.4byte	0x7cf
	.uleb128 0x13
	.ascii	"dst\000"
	.byte	0x1
	.byte	0x5a
	.4byte	0x216
	.uleb128 0x13
	.ascii	"src\000"
	.byte	0x1
	.byte	0x5a
	.4byte	0x216
	.uleb128 0x13
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
	.uleb128 0x12
	.4byte	$LASF199
	.byte	0x19
	.byte	0x2e
	.4byte	0x45
	.byte	0x3
	.4byte	0x7eb
	.uleb128 0x13
	.ascii	"val\000"
	.byte	0x19
	.byte	0x2e
	.4byte	0x45
	.byte	0
	.uleb128 0x12
	.4byte	$LASF200
	.byte	0x19
	.byte	0x39
	.4byte	0x5e
	.byte	0x3
	.4byte	0x807
	.uleb128 0x13
	.ascii	"val\000"
	.byte	0x19
	.byte	0x39
	.4byte	0x5e
	.byte	0
	.uleb128 0x12
	.4byte	$LASF201
	.byte	0x4
	.byte	0x65
	.4byte	0xf0
	.byte	0x3
	.4byte	0x85a
	.uleb128 0x13
	.ascii	"iph\000"
	.byte	0x4
	.byte	0x65
	.4byte	0x618
	.uleb128 0x13
	.ascii	"ihl\000"
	.byte	0x4
	.byte	0x65
	.4byte	0x69
	.uleb128 0x1c
	.4byte	$LASF202
	.byte	0x4
	.byte	0x67
	.4byte	0x85a
	.uleb128 0x1c
	.4byte	$LASF203
	.byte	0x4
	.byte	0x68
	.4byte	0x85a
	.uleb128 0x1c
	.4byte	$LASF204
	.byte	0x4
	.byte	0x69
	.4byte	0x69
	.uleb128 0x1c
	.4byte	$LASF205
	.byte	0x4
	.byte	0x6a
	.4byte	0x57
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x860
	.uleb128 0xd
	.4byte	0x69
	.uleb128 0x12
	.4byte	$LASF206
	.byte	0x2
	.byte	0xb2
	.4byte	0x57
	.byte	0x3
	.4byte	0x881
	.uleb128 0x19
	.4byte	$LASF186
	.byte	0x2
	.byte	0xb2
	.4byte	0x9e
	.byte	0
	.uleb128 0x18
	.4byte	$LASF207
	.byte	0x2
	.byte	0x36
	.byte	0x3
	.4byte	0x8a4
	.uleb128 0x19
	.4byte	$LASF186
	.byte	0x2
	.byte	0x36
	.4byte	0x9e
	.uleb128 0x1c
	.4byte	$LASF208
	.byte	0x2
	.byte	0x38
	.4byte	0x9e
	.byte	0
	.uleb128 0x18
	.4byte	$LASF209
	.byte	0x1
	.byte	0x50
	.byte	0x1
	.4byte	0x8bc
	.uleb128 0x19
	.4byte	$LASF210
	.byte	0x1
	.byte	0x50
	.4byte	0xcd
	.byte	0
	.uleb128 0x12
	.4byte	$LASF211
	.byte	0x5
	.byte	0x49
	.4byte	0x57
	.byte	0x3
	.4byte	0x8ee
	.uleb128 0x19
	.4byte	$LASF212
	.byte	0x5
	.byte	0x49
	.4byte	0x1f2
	.uleb128 0x19
	.4byte	$LASF213
	.byte	0x5
	.byte	0x49
	.4byte	0x1f2
	.uleb128 0x1c
	.4byte	$LASF214
	.byte	0x5
	.byte	0x4b
	.4byte	0x57
	.byte	0
	.uleb128 0x12
	.4byte	$LASF215
	.byte	0x1a
	.byte	0x3d
	.4byte	0x90a
	.byte	0x3
	.4byte	0x90a
	.uleb128 0x1c
	.4byte	$LASF216
	.byte	0x1a
	.byte	0x3f
	.4byte	0x90a
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x161
	.uleb128 0x1e
	.4byte	$LASF217
	.byte	0x20
	.byte	0xc7
	.byte	0x3
	.uleb128 0x1f
	.4byte	$LASF218
	.byte	0x1
	.2byte	0x380
	.4byte	0x9e
	.byte	0x1
	.4byte	0x93e
	.uleb128 0x15
	.ascii	"s\000"
	.byte	0x1
	.2byte	0x380
	.4byte	0xcd
	.uleb128 0x16
	.ascii	"k\000"
	.byte	0x1
	.2byte	0x382
	.4byte	0x9e
	.byte	0
	.uleb128 0x12
	.4byte	$LASF219
	.byte	0x6
	.byte	0x9e
	.4byte	0x181
	.byte	0x3
	.4byte	0x972
	.uleb128 0x19
	.4byte	$LASF183
	.byte	0x6
	.byte	0x9e
	.4byte	0x123
	.uleb128 0x19
	.4byte	$LASF186
	.byte	0x6
	.byte	0x9e
	.4byte	0x139
	.uleb128 0x20
	.uleb128 0x1c
	.4byte	$LASF220
	.byte	0x6
	.byte	0xa5
	.4byte	0x57
	.byte	0
	.byte	0
	.uleb128 0x21
	.4byte	$LASF227
	.byte	0x1
	.2byte	0x320
	.4byte	$LFB3083
	.4byte	$LFE3083-$LFB3083
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xc3c
	.uleb128 0x22
	.ascii	"skb\000"
	.byte	0x1
	.2byte	0x320
	.4byte	0x181
	.uleb128 0x1
	.byte	0x62
	.uleb128 0x16
	.ascii	"iph\000"
	.byte	0x1
	.2byte	0x322
	.4byte	0xc3c
	.uleb128 0x16
	.ascii	"x\000"
	.byte	0x1
	.2byte	0x323
	.4byte	0x9e
	.uleb128 0x23
	.4byte	0x77c
	.4byte	$LBB238
	.4byte	$LBE238-$LBB238
	.byte	0x1
	.2byte	0x32b
	.4byte	0x9d0
	.uleb128 0x24
	.4byte	$LBB239
	.4byte	$LBE239-$LBB239
	.uleb128 0x25
	.4byte	0x78c
	.byte	0
	.byte	0
	.uleb128 0x26
	.4byte	$Ldebug_ranges0+0
	.4byte	0xc16
	.uleb128 0x27
	.4byte	$LASF221
	.byte	0x1
	.2byte	0x32e
	.4byte	0xc42
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x27
	.4byte	$LASF222
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
	.4byte	$LASF223
	.byte	0x1
	.2byte	0x331
	.4byte	0x50
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x29
	.4byte	$LASF224
	.byte	0x1
	.2byte	0x333
	.4byte	0x57
	.uleb128 0x2a
	.4byte	0x798
	.4byte	$LBB241
	.4byte	$Ldebug_ranges0+0x20
	.byte	0x1
	.2byte	0x336
	.4byte	0xa4d
	.uleb128 0x2b
	.4byte	0x7ba
	.uleb128 0x2b
	.4byte	0x7af
	.uleb128 0x2b
	.4byte	0x7a4
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0x20
	.uleb128 0x25
	.4byte	0x7c5
	.byte	0
	.byte	0
	.uleb128 0x2a
	.4byte	0x7cf
	.4byte	$LBB245
	.4byte	$Ldebug_ranges0+0x38
	.byte	0x1
	.2byte	0x339
	.4byte	0xa7e
	.uleb128 0x2b
	.4byte	0x7df
	.uleb128 0x2d
	.4byte	0x57d
	.4byte	$LBB246
	.4byte	$Ldebug_ranges0+0x38
	.byte	0x19
	.byte	0x33
	.uleb128 0x2e
	.4byte	0x58d
	.uleb128 0x1
	.byte	0x55
	.byte	0
	.byte	0
	.uleb128 0x23
	.4byte	0x7eb
	.4byte	$LBB251
	.4byte	$LBE251-$LBB251
	.byte	0x1
	.2byte	0x362
	.4byte	0xaad
	.uleb128 0x2b
	.4byte	0x7fb
	.uleb128 0x2f
	.4byte	0x597
	.4byte	$LBB252
	.4byte	$LBE252-$LBB252
	.byte	0x19
	.byte	0x3e
	.uleb128 0x2b
	.4byte	0x5a7
	.byte	0
	.byte	0
	.uleb128 0x2a
	.4byte	0x798
	.4byte	$LBB254
	.4byte	$Ldebug_ranges0+0x50
	.byte	0x1
	.2byte	0x363
	.4byte	0xadc
	.uleb128 0x2b
	.4byte	0x7ba
	.uleb128 0x2b
	.4byte	0x7af
	.uleb128 0x2b
	.4byte	0x7a4
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0x50
	.uleb128 0x25
	.4byte	0x7c5
	.byte	0
	.byte	0
	.uleb128 0x23
	.4byte	0x7eb
	.4byte	$LBB258
	.4byte	$LBE258-$LBB258
	.byte	0x1
	.2byte	0x364
	.4byte	0xb0b
	.uleb128 0x2b
	.4byte	0x7fb
	.uleb128 0x2f
	.4byte	0x597
	.4byte	$LBB259
	.4byte	$LBE259-$LBB259
	.byte	0x19
	.byte	0x3e
	.uleb128 0x2b
	.4byte	0x5a7
	.byte	0
	.byte	0
	.uleb128 0x2a
	.4byte	0x798
	.4byte	$LBB261
	.4byte	$Ldebug_ranges0+0x68
	.byte	0x1
	.2byte	0x365
	.4byte	0xb3a
	.uleb128 0x2b
	.4byte	0x7ba
	.uleb128 0x2b
	.4byte	0x7af
	.uleb128 0x2b
	.4byte	0x7a4
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0x68
	.uleb128 0x25
	.4byte	0x7c5
	.byte	0
	.byte	0
	.uleb128 0x23
	.4byte	0x7eb
	.4byte	$LBB265
	.4byte	$LBE265-$LBB265
	.byte	0x1
	.2byte	0x36f
	.4byte	0xb69
	.uleb128 0x2b
	.4byte	0x7fb
	.uleb128 0x2f
	.4byte	0x597
	.4byte	$LBB266
	.4byte	$LBE266-$LBB266
	.byte	0x19
	.byte	0x3e
	.uleb128 0x2b
	.4byte	0x5a7
	.byte	0
	.byte	0
	.uleb128 0x2a
	.4byte	0x798
	.4byte	$LBB268
	.4byte	$Ldebug_ranges0+0x80
	.byte	0x1
	.2byte	0x370
	.4byte	0xb98
	.uleb128 0x2b
	.4byte	0x7ba
	.uleb128 0x2b
	.4byte	0x7af
	.uleb128 0x2b
	.4byte	0x7a4
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0x80
	.uleb128 0x25
	.4byte	0x7c5
	.byte	0
	.byte	0
	.uleb128 0x2a
	.4byte	0x807
	.4byte	$LBB272
	.4byte	$Ldebug_ranges0+0x98
	.byte	0x1
	.2byte	0x377
	.4byte	0xbea
	.uleb128 0x2b
	.4byte	0x822
	.uleb128 0x2b
	.4byte	0x817
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0x98
	.uleb128 0x30
	.4byte	0x82d
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x30
	.4byte	0x838
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x25
	.4byte	0x843
	.uleb128 0x25
	.4byte	0x84e
	.uleb128 0x2f
	.4byte	0x753
	.4byte	$LBB274
	.4byte	$LBE274-$LBB274
	.byte	0x4
	.byte	0x81
	.uleb128 0x2b
	.4byte	0x763
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x31
	.4byte	0x7cf
	.4byte	$LBB279
	.4byte	$LBE279-$LBB279
	.byte	0x1
	.2byte	0x375
	.uleb128 0x2b
	.4byte	0x7df
	.uleb128 0x2f
	.4byte	0x57d
	.4byte	$LBB280
	.4byte	$LBE280-$LBB280
	.byte	0x19
	.byte	0x33
	.uleb128 0x2b
	.4byte	0x58d
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x31
	.4byte	0x881
	.4byte	$LBB287
	.4byte	$LBE287-$LBB287
	.byte	0x1
	.2byte	0x37d
	.uleb128 0x2b
	.4byte	0x88d
	.uleb128 0x24
	.4byte	$LBB288
	.4byte	$LBE288-$LBB288
	.uleb128 0x25
	.4byte	0x898
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x3e0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x4aa
	.uleb128 0x32
	.4byte	$LASF225
	.byte	0x1
	.2byte	0x3e0
	.4byte	0x57
	.4byte	$LFB3087
	.4byte	$LFE3087-$LFB3087
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xc7b
	.uleb128 0x22
	.ascii	"s\000"
	.byte	0x1
	.2byte	0x3e0
	.4byte	0xc7b
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x22
	.ascii	"v\000"
	.byte	0x1
	.2byte	0x3e0
	.4byte	0x181
	.uleb128 0x1
	.byte	0x55
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x300
	.uleb128 0x32
	.4byte	$LASF226
	.byte	0x1
	.2byte	0x3e7
	.4byte	0x57
	.4byte	$LFB3088
	.4byte	$LFE3088-$LFB3088
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xcb4
	.uleb128 0x22
	.ascii	"s\000"
	.byte	0x1
	.2byte	0x3e7
	.4byte	0xc7b
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x22
	.ascii	"v\000"
	.byte	0x1
	.2byte	0x3e7
	.4byte	0x181
	.uleb128 0x1
	.byte	0x55
	.byte	0
	.uleb128 0x33
	.4byte	$LASF228
	.byte	0x1
	.2byte	0x3ee
	.4byte	0x57
	.4byte	$LFB3089
	.4byte	$LFE3089-$LFB3089
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xceb
	.uleb128 0x34
	.4byte	$LASF40
	.byte	0x1
	.2byte	0x3ee
	.4byte	0x1dd
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x34
	.4byte	$LASF42
	.byte	0x1
	.2byte	0x3ee
	.4byte	0x3e5
	.uleb128 0x1
	.byte	0x55
	.byte	0
	.uleb128 0x33
	.4byte	$LASF229
	.byte	0x1
	.2byte	0x402
	.4byte	0x57
	.4byte	$LFB3091
	.4byte	$LFE3091-$LFB3091
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xd22
	.uleb128 0x34
	.4byte	$LASF40
	.byte	0x1
	.2byte	0x402
	.4byte	0x1dd
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x34
	.4byte	$LASF42
	.byte	0x1
	.2byte	0x402
	.4byte	0x3e5
	.uleb128 0x1
	.byte	0x55
	.byte	0
	.uleb128 0x35
	.4byte	0x76f
	.4byte	$LFB3080
	.4byte	$LFE3080-$LFB3080
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x36
	.4byte	0x8a4
	.4byte	$LFB3075
	.4byte	$LFE3075-$LFB3075
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xd57
	.uleb128 0x2e
	.4byte	0x8b0
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0xc0
	.uleb128 0x2b
	.4byte	0x8b0
	.byte	0
	.byte	0
	.uleb128 0x37
	.4byte	$LASF349
	.byte	0x1
	.byte	0x38
	.4byte	0x57
	.4byte	$LFB3073
	.4byte	$LFE3073-$LFB3073
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x38
	.4byte	$LASF230
	.byte	0x1
	.byte	0x46
	.4byte	0x57
	.4byte	$LFB3074
	.4byte	$LFE3074-$LFB3074
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xdbc
	.uleb128 0x39
	.4byte	$LASF210
	.byte	0x1
	.byte	0x46
	.4byte	0xcd
	.uleb128 0x1
	.byte	0x60
	.uleb128 0x2f
	.4byte	0x8bc
	.4byte	$LBB299
	.4byte	$LBE299-$LBB299
	.byte	0x1
	.byte	0x48
	.uleb128 0x2b
	.4byte	0x8d7
	.uleb128 0x2b
	.4byte	0x8cc
	.uleb128 0x24
	.4byte	$LBB300
	.4byte	$LBE300-$LBB300
	.uleb128 0x25
	.4byte	0x8e2
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x38
	.4byte	$LASF231
	.byte	0x1
	.byte	0x60
	.4byte	0x57
	.4byte	$LFB3077
	.4byte	$LFE3077-$LFB3077
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xdfb
	.uleb128 0x3a
	.ascii	"skb\000"
	.byte	0x1
	.byte	0x60
	.4byte	0x181
	.uleb128 0x1
	.byte	0x61
	.uleb128 0x3b
	.ascii	"iph\000"
	.byte	0x1
	.byte	0x62
	.4byte	0xc3c
	.uleb128 0x1
	.byte	0x60
	.uleb128 0x1c
	.4byte	$LASF221
	.byte	0x1
	.byte	0x63
	.4byte	0xc42
	.byte	0
	.uleb128 0x3c
	.4byte	$LASF232
	.byte	0x1
	.byte	0x73
	.4byte	$LFB3078
	.4byte	$LFE3078-$LFB3078
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xf7f
	.uleb128 0x3a
	.ascii	"skb\000"
	.byte	0x1
	.byte	0x73
	.4byte	0x181
	.uleb128 0x1
	.byte	0x61
	.uleb128 0x1c
	.4byte	$LASF233
	.byte	0x1
	.byte	0x75
	.4byte	0xf7f
	.uleb128 0x1c
	.4byte	$LASF234
	.byte	0x1
	.byte	0x76
	.4byte	0xf85
	.uleb128 0x1c
	.4byte	$LASF235
	.byte	0x1
	.byte	0x77
	.4byte	0xf8b
	.uleb128 0x1c
	.4byte	$LASF236
	.byte	0x1
	.byte	0x78
	.4byte	0xf91
	.uleb128 0x1c
	.4byte	$LASF237
	.byte	0x1
	.byte	0x79
	.4byte	0xf97
	.uleb128 0x1c
	.4byte	$LASF238
	.byte	0x1
	.byte	0x7a
	.4byte	0xf9d
	.uleb128 0x3b
	.ascii	"iph\000"
	.byte	0x1
	.byte	0x7b
	.4byte	0xc3c
	.uleb128 0x1
	.byte	0x60
	.uleb128 0x24
	.4byte	$LBB301
	.4byte	$LBE301-$LBB301
	.uleb128 0x3b
	.ascii	"th\000"
	.byte	0x1
	.byte	0x7f
	.4byte	0xfa3
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x3d
	.4byte	0x7cf
	.4byte	$LBB302
	.4byte	$LBE302-$LBB302
	.byte	0x1
	.byte	0x86
	.4byte	0xeb1
	.uleb128 0x2b
	.4byte	0x7df
	.uleb128 0x2f
	.4byte	0x57d
	.4byte	$LBB303
	.4byte	$LBE303-$LBB303
	.byte	0x19
	.byte	0x33
	.uleb128 0x2e
	.4byte	0x58d
	.uleb128 0x1
	.byte	0x53
	.byte	0
	.byte	0
	.uleb128 0x3d
	.4byte	0x7cf
	.4byte	$LBB305
	.4byte	$LBE305-$LBB305
	.byte	0x1
	.byte	0x87
	.4byte	0xee1
	.uleb128 0x2b
	.4byte	0x7df
	.uleb128 0x2f
	.4byte	0x57d
	.4byte	$LBB306
	.4byte	$LBE306-$LBB306
	.byte	0x19
	.byte	0x33
	.uleb128 0x2e
	.4byte	0x58d
	.uleb128 0x1
	.byte	0x56
	.byte	0
	.byte	0
	.uleb128 0x26
	.4byte	$Ldebug_ranges0+0xd8
	.4byte	0xf01
	.uleb128 0x1c
	.4byte	$LASF239
	.byte	0x1
	.byte	0xa2
	.4byte	0x123
	.uleb128 0x1c
	.4byte	$LASF240
	.byte	0x1
	.byte	0xa2
	.4byte	0x181
	.byte	0
	.uleb128 0x26
	.4byte	$Ldebug_ranges0+0xf0
	.4byte	0xf21
	.uleb128 0x1c
	.4byte	$LASF239
	.byte	0x1
	.byte	0xa3
	.4byte	0x123
	.uleb128 0x1c
	.4byte	$LASF240
	.byte	0x1
	.byte	0xa3
	.4byte	0x181
	.byte	0
	.uleb128 0x3e
	.4byte	0x7cf
	.4byte	$LBB312
	.4byte	$Ldebug_ranges0+0x108
	.byte	0x1
	.byte	0xbd
	.4byte	0xf51
	.uleb128 0x2b
	.4byte	0x7df
	.uleb128 0x2d
	.4byte	0x57d
	.4byte	$LBB313
	.4byte	$Ldebug_ranges0+0x108
	.byte	0x19
	.byte	0x33
	.uleb128 0x2e
	.4byte	0x58d
	.uleb128 0x1
	.byte	0x52
	.byte	0
	.byte	0
	.uleb128 0x2f
	.4byte	0x7cf
	.4byte	$LBB318
	.4byte	$LBE318-$LBB318
	.byte	0x1
	.byte	0xbe
	.uleb128 0x2b
	.4byte	0x7df
	.uleb128 0x2f
	.4byte	0x57d
	.4byte	$LBB319
	.4byte	$LBE319-$LBB319
	.byte	0x19
	.byte	0x33
	.uleb128 0x2e
	.4byte	0x58d
	.uleb128 0x1
	.byte	0x53
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x4af
	.uleb128 0x6
	.byte	0x4
	.4byte	0x4b4
	.uleb128 0x6
	.byte	0x4
	.4byte	0x4be
	.uleb128 0x6
	.byte	0x4
	.4byte	0x4b9
	.uleb128 0x6
	.byte	0x4
	.4byte	0x4c8
	.uleb128 0x6
	.byte	0x4
	.4byte	0x4c3
	.uleb128 0x6
	.byte	0x4
	.4byte	0x45a
	.uleb128 0x32
	.4byte	$LASF241
	.byte	0x1
	.2byte	0x1d4
	.4byte	0x57
	.4byte	$LFB3079
	.4byte	$LFE3079-$LFB3079
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x10ea
	.uleb128 0x34
	.4byte	$LASF242
	.byte	0x1
	.2byte	0x1d4
	.4byte	0x10ea
	.uleb128 0x1
	.byte	0x62
	.uleb128 0x28
	.ascii	"iph\000"
	.byte	0x1
	.2byte	0x1d6
	.4byte	0xc3c
	.uleb128 0x1
	.byte	0x63
	.uleb128 0x27
	.4byte	$LASF221
	.byte	0x1
	.2byte	0x1d7
	.4byte	0xc42
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x27
	.4byte	$LASF243
	.byte	0x1
	.2byte	0x1d8
	.4byte	0x37
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x16
	.ascii	"ppp\000"
	.byte	0x1
	.2byte	0x1d9
	.4byte	0x181
	.uleb128 0x28
	.ascii	"skb\000"
	.byte	0x1
	.2byte	0x1da
	.4byte	0x181
	.uleb128 0x1
	.byte	0x60
	.uleb128 0x29
	.4byte	$LASF244
	.byte	0x1
	.2byte	0x1db
	.4byte	0x57
	.uleb128 0x27
	.4byte	$LASF245
	.byte	0x1
	.2byte	0x1dd
	.4byte	0x57
	.uleb128 0x1
	.byte	0x63
	.uleb128 0x29
	.4byte	$LASF246
	.byte	0x1
	.2byte	0x1de
	.4byte	0x216
	.uleb128 0x2a
	.4byte	0x7cf
	.4byte	$LBB321
	.4byte	$Ldebug_ranges0+0x120
	.byte	0x1
	.2byte	0x1eb
	.4byte	0x106c
	.uleb128 0x2b
	.4byte	0x7df
	.uleb128 0x2d
	.4byte	0x57d
	.4byte	$LBB322
	.4byte	$Ldebug_ranges0+0x120
	.byte	0x19
	.byte	0x33
	.uleb128 0x2e
	.4byte	0x58d
	.uleb128 0x1
	.byte	0x54
	.byte	0
	.byte	0
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0x138
	.uleb128 0x29
	.4byte	$LASF247
	.byte	0x1
	.2byte	0x1ec
	.4byte	0x216
	.uleb128 0x29
	.4byte	$LASF248
	.byte	0x1
	.2byte	0x1ed
	.4byte	0x57
	.uleb128 0x29
	.4byte	$LASF249
	.byte	0x1
	.2byte	0x1ee
	.4byte	0x57
	.uleb128 0x2a
	.4byte	0x7eb
	.4byte	$LBB328
	.4byte	$Ldebug_ranges0+0x160
	.byte	0x1
	.2byte	0x1f6
	.4byte	0x10c4
	.uleb128 0x2b
	.4byte	0x7fb
	.uleb128 0x2d
	.4byte	0x597
	.4byte	$LBB329
	.4byte	$Ldebug_ranges0+0x160
	.byte	0x19
	.byte	0x3e
	.uleb128 0x2b
	.4byte	0x5a7
	.byte	0
	.byte	0
	.uleb128 0x24
	.4byte	$LBB334
	.4byte	$LBE334-$LBB334
	.uleb128 0x27
	.4byte	$LASF239
	.byte	0x1
	.2byte	0x255
	.4byte	0x123
	.uleb128 0x1
	.byte	0x64
	.uleb128 0x29
	.4byte	$LASF240
	.byte	0x1
	.2byte	0x255
	.4byte	0x181
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x181
	.uleb128 0x32
	.4byte	$LASF250
	.byte	0x1
	.2byte	0x28f
	.4byte	0x57
	.4byte	$LFB3081
	.4byte	$LFE3081-$LFB3081
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x13bf
	.uleb128 0x22
	.ascii	"skb\000"
	.byte	0x1
	.2byte	0x28f
	.4byte	0x181
	.uleb128 0x1
	.byte	0x61
	.uleb128 0x29
	.4byte	$LASF251
	.byte	0x1
	.2byte	0x291
	.4byte	0x57
	.uleb128 0x29
	.4byte	$LASF252
	.byte	0x1
	.2byte	0x292
	.4byte	0xc3c
	.uleb128 0x27
	.4byte	$LASF253
	.byte	0x1
	.2byte	0x292
	.4byte	0x3e0
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x29
	.4byte	$LASF221
	.byte	0x1
	.2byte	0x293
	.4byte	0xc42
	.uleb128 0x27
	.4byte	$LASF254
	.byte	0x1
	.2byte	0x293
	.4byte	0x4aa
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
	.4byte	0x13bf
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x29
	.4byte	$LASF255
	.byte	0x1
	.2byte	0x296
	.4byte	0x57
	.uleb128 0x27
	.4byte	$LASF256
	.byte	0x1
	.2byte	0x297
	.4byte	0x57
	.uleb128 0x1
	.byte	0x60
	.uleb128 0x29
	.4byte	$LASF257
	.byte	0x1
	.2byte	0x297
	.4byte	0x57
	.uleb128 0x29
	.4byte	$LASF258
	.byte	0x1
	.2byte	0x297
	.4byte	0x57
	.uleb128 0x23
	.4byte	0x8bc
	.4byte	$LBB338
	.4byte	$LBE338-$LBB338
	.byte	0x1
	.2byte	0x2a2
	.4byte	0x11d7
	.uleb128 0x2b
	.4byte	0x8d7
	.uleb128 0x2b
	.4byte	0x8cc
	.uleb128 0x24
	.4byte	$LBB339
	.4byte	$LBE339-$LBB339
	.uleb128 0x25
	.4byte	0x8e2
	.byte	0
	.byte	0
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0x178
	.uleb128 0x28
	.ascii	"ppp\000"
	.byte	0x1
	.2byte	0x2a8
	.4byte	0x181
	.uleb128 0x1
	.byte	0x63
	.uleb128 0x26
	.4byte	$Ldebug_ranges0+0x190
	.4byte	0x1200
	.uleb128 0x29
	.4byte	$LASF259
	.byte	0x1
	.2byte	0x2c3
	.4byte	0x181
	.byte	0
	.uleb128 0x26
	.4byte	$Ldebug_ranges0+0x1a8
	.4byte	0x1222
	.uleb128 0x29
	.4byte	$LASF239
	.byte	0x1
	.2byte	0x2d0
	.4byte	0x123
	.uleb128 0x29
	.4byte	$LASF240
	.byte	0x1
	.2byte	0x2d0
	.4byte	0x181
	.byte	0
	.uleb128 0x26
	.4byte	$Ldebug_ranges0+0x1d0
	.4byte	0x1244
	.uleb128 0x29
	.4byte	$LASF239
	.byte	0x1
	.2byte	0x2d1
	.4byte	0x123
	.uleb128 0x29
	.4byte	$LASF240
	.byte	0x1
	.2byte	0x2d1
	.4byte	0x181
	.byte	0
	.uleb128 0x23
	.4byte	0x7cf
	.4byte	$LBB351
	.4byte	$LBE351-$LBB351
	.byte	0x1
	.2byte	0x2df
	.4byte	0x1273
	.uleb128 0x2b
	.4byte	0x7df
	.uleb128 0x2f
	.4byte	0x57d
	.4byte	$LBB352
	.4byte	$LBE352-$LBB352
	.byte	0x19
	.byte	0x33
	.uleb128 0x2b
	.4byte	0x58d
	.byte	0
	.byte	0
	.uleb128 0x23
	.4byte	0x7cf
	.4byte	$LBB354
	.4byte	$LBE354-$LBB354
	.byte	0x1
	.2byte	0x2e0
	.4byte	0x12a2
	.uleb128 0x2b
	.4byte	0x7df
	.uleb128 0x2f
	.4byte	0x57d
	.4byte	$LBB355
	.4byte	$LBE355-$LBB355
	.byte	0x19
	.byte	0x33
	.uleb128 0x2b
	.4byte	0x58d
	.byte	0
	.byte	0
	.uleb128 0x2a
	.4byte	0x807
	.4byte	$LBB357
	.4byte	$Ldebug_ranges0+0x1f8
	.byte	0x1
	.2byte	0x2e2
	.4byte	0x12f0
	.uleb128 0x2b
	.4byte	0x822
	.uleb128 0x2b
	.4byte	0x817
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0x1f8
	.uleb128 0x25
	.4byte	0x82d
	.uleb128 0x25
	.4byte	0x838
	.uleb128 0x25
	.4byte	0x843
	.uleb128 0x25
	.4byte	0x84e
	.uleb128 0x2f
	.4byte	0x753
	.4byte	$LBB359
	.4byte	$LBE359-$LBB359
	.byte	0x4
	.byte	0x81
	.uleb128 0x2b
	.4byte	0x763
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x26
	.4byte	$Ldebug_ranges0+0x228
	.4byte	0x1312
	.uleb128 0x29
	.4byte	$LASF239
	.byte	0x1
	.2byte	0x2e4
	.4byte	0x123
	.uleb128 0x29
	.4byte	$LASF240
	.byte	0x1
	.2byte	0x2e4
	.4byte	0x181
	.byte	0
	.uleb128 0x26
	.4byte	$Ldebug_ranges0+0x240
	.4byte	0x1334
	.uleb128 0x29
	.4byte	$LASF239
	.byte	0x1
	.2byte	0x2f0
	.4byte	0x123
	.uleb128 0x29
	.4byte	$LASF240
	.byte	0x1
	.2byte	0x2f0
	.4byte	0x181
	.byte	0
	.uleb128 0x23
	.4byte	0x7eb
	.4byte	$LBB372
	.4byte	$LBE372-$LBB372
	.byte	0x1
	.2byte	0x2ee
	.4byte	0x1363
	.uleb128 0x2b
	.4byte	0x7fb
	.uleb128 0x2f
	.4byte	0x597
	.4byte	$LBB373
	.4byte	$LBE373-$LBB373
	.byte	0x19
	.byte	0x3e
	.uleb128 0x2b
	.4byte	0x5a7
	.byte	0
	.byte	0
	.uleb128 0x2a
	.4byte	0x7eb
	.4byte	$LBB375
	.4byte	$Ldebug_ranges0+0x268
	.byte	0x1
	.2byte	0x2ef
	.4byte	0x1392
	.uleb128 0x2b
	.4byte	0x7fb
	.uleb128 0x2d
	.4byte	0x597
	.4byte	$LBB376
	.4byte	$Ldebug_ranges0+0x268
	.byte	0x19
	.byte	0x3e
	.uleb128 0x2b
	.4byte	0x5a7
	.byte	0
	.byte	0
	.uleb128 0x31
	.4byte	0x7cf
	.4byte	$LBB381
	.4byte	$LBE381-$LBB381
	.byte	0x1
	.2byte	0x2ec
	.uleb128 0x2b
	.4byte	0x7df
	.uleb128 0x2f
	.4byte	0x57d
	.4byte	$LBB382
	.4byte	$LBE382-$LBB382
	.byte	0x19
	.byte	0x33
	.uleb128 0x2b
	.4byte	0x58d
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x221
	.uleb128 0x21
	.4byte	$LASF260
	.byte	0x1
	.2byte	0x304
	.4byte	$LFB3082
	.4byte	$LFE3082-$LFB3082
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x148f
	.uleb128 0x22
	.ascii	"skb\000"
	.byte	0x1
	.2byte	0x304
	.4byte	0x181
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x29
	.4byte	$LASF221
	.byte	0x1
	.2byte	0x306
	.4byte	0xc42
	.uleb128 0x28
	.ascii	"iph\000"
	.byte	0x1
	.2byte	0x307
	.4byte	0x216
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2a
	.4byte	0x7cf
	.4byte	$LBB388
	.4byte	$Ldebug_ranges0+0x280
	.byte	0x1
	.2byte	0x30c
	.4byte	0x1434
	.uleb128 0x2b
	.4byte	0x7df
	.uleb128 0x2d
	.4byte	0x57d
	.4byte	$LBB389
	.4byte	$Ldebug_ranges0+0x280
	.byte	0x19
	.byte	0x33
	.uleb128 0x2e
	.4byte	0x58d
	.uleb128 0x1
	.byte	0x55
	.byte	0
	.byte	0
	.uleb128 0x23
	.4byte	0x7eb
	.4byte	$LBB394
	.4byte	$LBE394-$LBB394
	.byte	0x1
	.2byte	0x313
	.4byte	0x1463
	.uleb128 0x2b
	.4byte	0x7fb
	.uleb128 0x2f
	.4byte	0x597
	.4byte	$LBB395
	.4byte	$LBE395-$LBB395
	.byte	0x19
	.byte	0x3e
	.uleb128 0x2b
	.4byte	0x5a7
	.byte	0
	.byte	0
	.uleb128 0x31
	.4byte	0x7eb
	.4byte	$LBB397
	.4byte	$LBE397-$LBB397
	.byte	0x1
	.2byte	0x317
	.uleb128 0x2b
	.4byte	0x7fb
	.uleb128 0x2f
	.4byte	0x597
	.4byte	$LBB398
	.4byte	$LBE398-$LBB398
	.byte	0x19
	.byte	0x3e
	.uleb128 0x2b
	.4byte	0x5a7
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x3f
	.4byte	$LASF261
	.byte	0x1
	.2byte	0x38c
	.4byte	0x57
	.4byte	$LFB3085
	.4byte	$LFE3085-$LFB3085
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x15b7
	.uleb128 0x34
	.4byte	$LASF42
	.byte	0x1
	.2byte	0x38c
	.4byte	0x3e5
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x34
	.4byte	$LASF262
	.byte	0x1
	.2byte	0x38c
	.4byte	0x1f2
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x34
	.4byte	$LASF263
	.byte	0x1
	.2byte	0x38d
	.4byte	0x9e
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x34
	.4byte	$LASF246
	.byte	0x1
	.2byte	0x38d
	.4byte	0x181
	.uleb128 0x1
	.byte	0x57
	.uleb128 0x27
	.4byte	$LASF264
	.byte	0x1
	.2byte	0x38f
	.4byte	0x15b7
	.uleb128 0x3
	.byte	0x91
	.sleb128 -208
	.uleb128 0x26
	.4byte	$Ldebug_ranges0+0x298
	.4byte	0x158d
	.uleb128 0x29
	.4byte	$LASF265
	.byte	0x1
	.2byte	0x394
	.4byte	0x181
	.uleb128 0x29
	.4byte	$LASF266
	.byte	0x1
	.2byte	0x394
	.4byte	0x618
	.uleb128 0x29
	.4byte	$LASF267
	.byte	0x1
	.2byte	0x394
	.4byte	0xa5
	.uleb128 0x26
	.4byte	$Ldebug_ranges0+0x2b0
	.4byte	0x1558
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
	.uleb128 0x29
	.4byte	$LASF271
	.byte	0x1
	.2byte	0x394
	.4byte	0x9e
	.byte	0
	.uleb128 0x24
	.4byte	$LBB403
	.4byte	$LBE403-$LBB403
	.uleb128 0x27
	.4byte	$LASF272
	.byte	0x1
	.2byte	0x394
	.4byte	0x181
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x27
	.4byte	$LASF273
	.byte	0x1
	.2byte	0x394
	.4byte	0x618
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x27
	.4byte	$LASF274
	.byte	0x1
	.2byte	0x394
	.4byte	0xa5
	.uleb128 0x1
	.byte	0x56
	.byte	0
	.byte	0
	.uleb128 0x31
	.4byte	0x918
	.4byte	$LBB405
	.4byte	$LBE405-$LBB405
	.byte	0x1
	.2byte	0x395
	.uleb128 0x2e
	.4byte	0x929
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x24
	.4byte	$LBB406
	.4byte	$LBE406-$LBB406
	.uleb128 0x30
	.4byte	0x933
	.uleb128 0x1
	.byte	0x52
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x40
	.4byte	0xd3
	.4byte	0x15c7
	.uleb128 0x41
	.4byte	0x15a
	.byte	0xc7
	.byte	0
	.uleb128 0x42
	.4byte	$LASF277
	.byte	0x1
	.2byte	0x407
	.4byte	0x12e
	.4byte	$LFB3092
	.4byte	$LFE3092-$LFB3092
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x161a
	.uleb128 0x34
	.4byte	$LASF42
	.byte	0x1
	.2byte	0x407
	.4byte	0x3e5
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x34
	.4byte	$LASF275
	.byte	0x1
	.2byte	0x407
	.4byte	0x1f2
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x34
	.4byte	$LASF263
	.byte	0x1
	.2byte	0x408
	.4byte	0x123
	.uleb128 0x1
	.byte	0x56
	.uleb128 0x22
	.ascii	"off\000"
	.byte	0x1
	.2byte	0x408
	.4byte	0x1c1
	.uleb128 0x1
	.byte	0x57
	.byte	0
	.uleb128 0x32
	.4byte	$LASF276
	.byte	0x1
	.2byte	0x39a
	.4byte	0x57
	.4byte	$LFB3086
	.4byte	$LFE3086-$LFB3086
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1785
	.uleb128 0x34
	.4byte	$LASF42
	.byte	0x1
	.2byte	0x39a
	.4byte	0x3e5
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x34
	.4byte	$LASF262
	.byte	0x1
	.2byte	0x39a
	.4byte	0x1f2
	.uleb128 0x1
	.byte	0x62
	.uleb128 0x34
	.4byte	$LASF263
	.byte	0x1
	.2byte	0x39b
	.4byte	0x9e
	.uleb128 0x1
	.byte	0x60
	.uleb128 0x34
	.4byte	$LASF246
	.byte	0x1
	.2byte	0x39b
	.4byte	0x181
	.uleb128 0x1
	.byte	0x57
	.uleb128 0x29
	.4byte	$LASF264
	.byte	0x1
	.2byte	0x39d
	.4byte	0xcd
	.uleb128 0x23
	.4byte	0x93e
	.4byte	$LBB407
	.4byte	$LBE407-$LBB407
	.byte	0x1
	.2byte	0x3aa
	.4byte	0x1697
	.uleb128 0x2b
	.4byte	0x959
	.uleb128 0x2b
	.4byte	0x94e
	.byte	0
	.uleb128 0x43
	.4byte	$LBB409
	.4byte	$LBE409-$LBB409
	.4byte	0x173b
	.uleb128 0x29
	.4byte	$LASF265
	.byte	0x1
	.2byte	0x3ae
	.4byte	0x181
	.uleb128 0x29
	.4byte	$LASF266
	.byte	0x1
	.2byte	0x3ae
	.4byte	0x618
	.uleb128 0x29
	.4byte	$LASF267
	.byte	0x1
	.2byte	0x3ae
	.4byte	0xa5
	.uleb128 0x43
	.4byte	$LBB410
	.4byte	$LBE410-$LBB410
	.4byte	0x1706
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
	.uleb128 0x29
	.4byte	$LASF271
	.byte	0x1
	.2byte	0x3ae
	.4byte	0x9e
	.byte	0
	.uleb128 0x24
	.4byte	$LBB411
	.4byte	$LBE411-$LBB411
	.uleb128 0x27
	.4byte	$LASF272
	.byte	0x1
	.2byte	0x3ae
	.4byte	0x181
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x27
	.4byte	$LASF273
	.byte	0x1
	.2byte	0x3ae
	.4byte	0x618
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x27
	.4byte	$LASF274
	.byte	0x1
	.2byte	0x3ae
	.4byte	0xa5
	.uleb128 0x1
	.byte	0x56
	.byte	0
	.byte	0
	.uleb128 0x23
	.4byte	0x918
	.4byte	$LBB412
	.4byte	$LBE412-$LBB412
	.byte	0x1
	.2byte	0x3af
	.4byte	0x1766
	.uleb128 0x2b
	.4byte	0x929
	.uleb128 0x24
	.4byte	$LBB413
	.4byte	$LBE413-$LBB413
	.uleb128 0x30
	.4byte	0x933
	.uleb128 0x1
	.byte	0x53
	.byte	0
	.byte	0
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0x2c8
	.uleb128 0x29
	.4byte	$LASF239
	.byte	0x1
	.2byte	0x3b2
	.4byte	0x123
	.uleb128 0x29
	.4byte	$LASF240
	.byte	0x1
	.2byte	0x3b2
	.4byte	0x181
	.byte	0
	.byte	0
	.uleb128 0x42
	.4byte	$LASF278
	.byte	0x1
	.2byte	0x3f3
	.4byte	0x12e
	.4byte	$LFB3090
	.4byte	$LFE3090-$LFB3090
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x17d8
	.uleb128 0x34
	.4byte	$LASF42
	.byte	0x1
	.2byte	0x3f3
	.4byte	0x3e5
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x34
	.4byte	$LASF275
	.byte	0x1
	.2byte	0x3f3
	.4byte	0x1f2
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x34
	.4byte	$LASF263
	.byte	0x1
	.2byte	0x3f4
	.4byte	0x123
	.uleb128 0x1
	.byte	0x56
	.uleb128 0x22
	.ascii	"off\000"
	.byte	0x1
	.2byte	0x3f4
	.4byte	0x1c1
	.uleb128 0x1
	.byte	0x57
	.byte	0
	.uleb128 0x32
	.4byte	$LASF279
	.byte	0x1
	.2byte	0x43b
	.4byte	0x57
	.4byte	$LFB3093
	.4byte	$LFE3093-$LFB3093
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1811
	.uleb128 0x2c
	.4byte	$Ldebug_ranges0+0x2e0
	.uleb128 0x29
	.4byte	$LASF239
	.byte	0x1
	.2byte	0x459
	.4byte	0x123
	.uleb128 0x29
	.4byte	$LASF240
	.byte	0x1
	.2byte	0x459
	.4byte	0x181
	.byte	0
	.byte	0
	.uleb128 0x44
	.4byte	$LASF350
	.byte	0x1
	.2byte	0x45e
	.4byte	$LFB3094
	.4byte	$LFE3094-$LFB3094
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x8
	.4byte	$LASF280
	.uleb128 0x8
	.4byte	$LASF281
	.uleb128 0x8
	.4byte	$LASF282
	.uleb128 0x8
	.4byte	$LASF283
	.uleb128 0x45
	.4byte	$LASF284
	.byte	0x1b
	.byte	0x6c
	.4byte	0x69
	.4byte	0x1fbd0
	.uleb128 0x40
	.4byte	0x7e
	.4byte	0x1856
	.uleb128 0x41
	.4byte	0x15a
	.byte	0x5
	.byte	0
	.uleb128 0x1c
	.4byte	$LASF285
	.byte	0x1c
	.byte	0x39
	.4byte	0x1861
	.uleb128 0xd
	.4byte	0x1846
	.uleb128 0x46
	.4byte	$LASF286
	.byte	0x1
	.byte	0x30
	.4byte	0x4cd
	.uleb128 0x5
	.byte	0x3
	.4byte	pptpAccInfo
	.uleb128 0x46
	.4byte	$LASF287
	.byte	0x1
	.byte	0x34
	.4byte	0x57
	.uleb128 0x5
	.byte	0x3
	.4byte	pptp_conn_check
	.uleb128 0x27
	.4byte	$LASF288
	.byte	0x1
	.2byte	0x434
	.4byte	0x189a
	.uleb128 0x5
	.byte	0x3
	.4byte	res1
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1832
	.uleb128 0x27
	.4byte	$LASF289
	.byte	0x1
	.2byte	0x435
	.4byte	0x189a
	.uleb128 0x5
	.byte	0x3
	.4byte	res_check_pptp
	.uleb128 0x47
	.4byte	$LASF290
	.byte	0x1d
	.byte	0x21
	.4byte	0x1d3
	.uleb128 0x40
	.4byte	0x155
	.4byte	0x18c8
	.uleb128 0x48
	.byte	0
	.uleb128 0x47
	.4byte	$LASF291
	.byte	0x1e
	.byte	0x54
	.4byte	0x18bd
	.uleb128 0x40
	.4byte	0x57
	.4byte	0x18de
	.uleb128 0x48
	.byte	0
	.uleb128 0x47
	.4byte	$LASF292
	.byte	0x1f
	.byte	0x24
	.4byte	0x18d3
	.uleb128 0x40
	.4byte	0xd3
	.4byte	0x18f4
	.uleb128 0x48
	.byte	0
	.uleb128 0x49
	.4byte	$LASF293
	.byte	0x20
	.2byte	0x1b2
	.4byte	0x1900
	.uleb128 0xd
	.4byte	0x18e9
	.uleb128 0x40
	.4byte	0x9e
	.4byte	0x191b
	.uleb128 0x41
	.4byte	0x15a
	.byte	0x20
	.uleb128 0x41
	.4byte	0x15a
	.byte	0
	.byte	0
	.uleb128 0x49
	.4byte	$LASF294
	.byte	0x21
	.2byte	0x2f9
	.4byte	0x1927
	.uleb128 0xd
	.4byte	0x1905
	.uleb128 0x47
	.4byte	$LASF295
	.byte	0x22
	.byte	0x76
	.4byte	0x106
	.uleb128 0x47
	.4byte	$LASF296
	.byte	0x23
	.byte	0x22
	.4byte	0x57
	.uleb128 0x47
	.4byte	$LASF297
	.byte	0x23
	.byte	0x23
	.4byte	0x57
	.uleb128 0x47
	.4byte	$LASF298
	.byte	0x24
	.byte	0x8d
	.4byte	0x1823
	.uleb128 0x47
	.4byte	$LASF299
	.byte	0xe
	.byte	0x3f
	.4byte	0x9e
	.uleb128 0x47
	.4byte	$LASF300
	.byte	0xe
	.byte	0x4c
	.4byte	0x1b0
	.uleb128 0x47
	.4byte	$LASF301
	.byte	0x25
	.byte	0x3f
	.4byte	0x1979
	.uleb128 0xd
	.4byte	0x9e
	.uleb128 0x47
	.4byte	$LASF302
	.byte	0x26
	.byte	0x1d
	.4byte	0x9e
	.uleb128 0x47
	.4byte	$LASF303
	.byte	0x27
	.byte	0x4c
	.4byte	0x57
	.uleb128 0x49
	.4byte	$LASF304
	.byte	0x27
	.2byte	0x2ad
	.4byte	0x18f
	.uleb128 0x47
	.4byte	$LASF305
	.byte	0x28
	.byte	0x4d
	.4byte	0x19ab
	.uleb128 0x4a
	.4byte	0x9e
	.uleb128 0x49
	.4byte	$LASF306
	.byte	0x29
	.2byte	0x151
	.4byte	0x19bc
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1828
	.uleb128 0x49
	.4byte	$LASF307
	.byte	0x29
	.2byte	0x154
	.4byte	0x19bc
	.uleb128 0x49
	.4byte	$LASF308
	.byte	0x27
	.2byte	0x391
	.4byte	0x19a
	.uleb128 0x49
	.4byte	$LASF309
	.byte	0x2a
	.2byte	0x799
	.4byte	0x182d
	.uleb128 0x47
	.4byte	$LASF41
	.byte	0x2b
	.byte	0xfd
	.4byte	0x1e8
	.uleb128 0x49
	.4byte	$LASF310
	.byte	0x2a
	.2byte	0x61e
	.4byte	0x19fd
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1d8
	.uleb128 0x49
	.4byte	$LASF311
	.byte	0x2c
	.2byte	0x1f4
	.4byte	0x1a0f
	.uleb128 0x6
	.byte	0x4
	.4byte	0x202
	.uleb128 0x47
	.4byte	$LASF312
	.byte	0x2d
	.byte	0x2e
	.4byte	0x207
	.uleb128 0x40
	.4byte	0x68c
	.4byte	0x1a30
	.uleb128 0x41
	.4byte	0x15a
	.byte	0xd
	.byte	0
	.uleb128 0x47
	.4byte	$LASF313
	.byte	0x18
	.byte	0xe0
	.4byte	0x1a20
	.uleb128 0x47
	.4byte	$LASF314
	.byte	0x2e
	.byte	0x8a
	.4byte	0x211
	.uleb128 0x47
	.4byte	$LASF315
	.byte	0x2f
	.byte	0xa
	.4byte	0x57
	.uleb128 0x47
	.4byte	$LASF316
	.byte	0x26
	.byte	0x21
	.4byte	0x9e
	.uleb128 0x40
	.4byte	0x184
	.4byte	0x1a6d
	.uleb128 0x4b
	.4byte	0x15a
	.2byte	0x3ff
	.byte	0
	.uleb128 0x47
	.4byte	$LASF317
	.byte	0x30
	.byte	0x48
	.4byte	0x1a5c
	.uleb128 0x47
	.4byte	$LASF318
	.byte	0x31
	.byte	0x4d
	.4byte	0x9e
	.uleb128 0x49
	.4byte	$LASF319
	.byte	0x32
	.2byte	0x1cb
	.4byte	0x9e
	.uleb128 0x40
	.4byte	0x166
	.4byte	0x1a9f
	.uleb128 0x41
	.4byte	0x15a
	.byte	0x1b
	.byte	0
	.uleb128 0x47
	.4byte	$LASF320
	.byte	0x33
	.byte	0x5d
	.4byte	0x1a8f
	.uleb128 0x49
	.4byte	$LASF321
	.byte	0x26
	.2byte	0x555
	.4byte	0x18e9
	.uleb128 0x49
	.4byte	$LASF322
	.byte	0x26
	.2byte	0x555
	.4byte	0x18e9
	.uleb128 0x40
	.4byte	0x150
	.4byte	0x1ad8
	.uleb128 0x41
	.4byte	0x15a
	.byte	0xc
	.uleb128 0x41
	.4byte	0x15a
	.byte	0x7
	.byte	0
	.uleb128 0x47
	.4byte	$LASF323
	.byte	0x34
	.byte	0x62
	.4byte	0x1ac2
	.uleb128 0x40
	.4byte	0x1af3
	.4byte	0x1af3
	.uleb128 0x41
	.4byte	0x15a
	.byte	0xc
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1af9
	.uleb128 0xd
	.4byte	0x2f1
	.uleb128 0x47
	.4byte	$LASF78
	.byte	0x34
	.byte	0xea
	.4byte	0x1ae3
	.uleb128 0xa
	.4byte	0x1b19
	.uleb128 0xb
	.4byte	0x2eb
	.uleb128 0xb
	.4byte	0x1b19
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x2f6
	.uleb128 0x49
	.4byte	$LASF324
	.byte	0x34
	.2byte	0x114
	.4byte	0x1b2b
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1b09
	.uleb128 0x47
	.4byte	$LASF325
	.byte	0x35
	.byte	0x86
	.4byte	0x2fb
	.uleb128 0x49
	.4byte	$LASF326
	.byte	0x36
	.2byte	0x2b8
	.4byte	0x1ce
	.uleb128 0x47
	.4byte	$LASF327
	.byte	0x37
	.byte	0xcd
	.4byte	0x93
	.uleb128 0x47
	.4byte	$LASF328
	.byte	0x37
	.byte	0xce
	.4byte	0x93
	.uleb128 0x47
	.4byte	$LASF329
	.byte	0x38
	.byte	0xcd
	.4byte	0x1b69
	.uleb128 0x6
	.byte	0x4
	.4byte	0x9e
	.uleb128 0x47
	.4byte	$LASF330
	.byte	0x39
	.byte	0xb9
	.4byte	0x1b7a
	.uleb128 0xd
	.4byte	0x18e9
	.uleb128 0x47
	.4byte	$LASF331
	.byte	0x12
	.byte	0x3e
	.4byte	0x455
	.uleb128 0x40
	.4byte	0x2c
	.4byte	0x1b9a
	.uleb128 0x41
	.4byte	0x15a
	.byte	0xf
	.byte	0
	.uleb128 0x47
	.4byte	$LASF332
	.byte	0x3a
	.byte	0xd4
	.4byte	0x1ba5
	.uleb128 0xd
	.4byte	0x1b8a
	.uleb128 0x49
	.4byte	$LASF333
	.byte	0x3a
	.2byte	0x135
	.4byte	0x57
	.uleb128 0x47
	.4byte	$LASF334
	.byte	0x3b
	.byte	0xa
	.4byte	0x455
	.uleb128 0x49
	.4byte	$LASF335
	.byte	0x3c
	.2byte	0x11d
	.4byte	0x176
	.uleb128 0x47
	.4byte	$LASF336
	.byte	0x3d
	.byte	0x18
	.4byte	0x1832
	.uleb128 0x47
	.4byte	$LASF337
	.byte	0x1
	.byte	0x36
	.4byte	0x57
	.uleb128 0x49
	.4byte	$LASF338
	.byte	0x3d
	.2byte	0x1b9
	.4byte	0x19f
	.uleb128 0x4c
	.4byte	$LASF339
	.byte	0x1
	.byte	0x31
	.4byte	0x57
	.uleb128 0x5
	.byte	0x3
	.4byte	pptp_tcp_finished
	.uleb128 0x4d
	.4byte	$LASF340
	.byte	0x1
	.2byte	0x3fa
	.4byte	0x1fd
	.uleb128 0x5
	.byte	0x3
	.4byte	fastpath_pptp_proc_fops
	.uleb128 0x4d
	.4byte	$LASF341
	.byte	0x1
	.2byte	0x40e
	.4byte	0x1fd
	.uleb128 0x5
	.byte	0x3
	.4byte	pptp_conn_proc_fops
	.uleb128 0xa
	.4byte	0x1c2f
	.uleb128 0xb
	.4byte	0xcd
	.byte	0
	.uleb128 0x49
	.4byte	$LASF342
	.byte	0x1
	.2byte	0x438
	.4byte	0x1c3b
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1c24
	.uleb128 0x4e
	.4byte	0x9e
	.uleb128 0x49
	.4byte	$LASF343
	.byte	0x1
	.2byte	0x439
	.4byte	0x1c52
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1c41
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
	.uleb128 0x13
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
	.uleb128 0x14
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
	.uleb128 0x15
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
	.uleb128 0x16
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
	.uleb128 0x17
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
	.uleb128 0x18
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
	.uleb128 0x19
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
	.uleb128 0x1a
	.uleb128 0x26
	.byte	0
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
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0x5
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
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x31
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
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x33
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
	.uleb128 0x34
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
	.uleb128 0x35
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
	.uleb128 0x36
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
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3e
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
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3f
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
	.uleb128 0x40
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x41
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x42
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
	.uleb128 0x43
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
	.uleb128 0x44
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
	.uleb128 0x1c
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x46
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
	.uleb128 0x47
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
	.uleb128 0x48
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x49
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
	.uleb128 0x4a
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4b
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x4c
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
	.uleb128 0x4d
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
	.uleb128 0x4e
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
	.4byte	$LFB3093
	.4byte	$LFE3093-$LFB3093
	.4byte	$LFB3094
	.4byte	$LFE3094-$LFB3094
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",@progbits
$Ldebug_ranges0:
	.4byte	$LBB240
	.4byte	$LBE240
	.4byte	$LBB285
	.4byte	$LBE285
	.4byte	$LBB286
	.4byte	$LBE286
	.4byte	0
	.4byte	0
	.4byte	$LBB241
	.4byte	$LBE241
	.4byte	$LBB244
	.4byte	$LBE244
	.4byte	0
	.4byte	0
	.4byte	$LBB245
	.4byte	$LBE245
	.4byte	$LBB250
	.4byte	$LBE250
	.4byte	0
	.4byte	0
	.4byte	$LBB254
	.4byte	$LBE254
	.4byte	$LBB257
	.4byte	$LBE257
	.4byte	0
	.4byte	0
	.4byte	$LBB261
	.4byte	$LBE261
	.4byte	$LBB264
	.4byte	$LBE264
	.4byte	0
	.4byte	0
	.4byte	$LBB268
	.4byte	$LBE268
	.4byte	$LBB271
	.4byte	$LBE271
	.4byte	0
	.4byte	0
	.4byte	$LBB272
	.4byte	$LBE272
	.4byte	$LBB282
	.4byte	$LBE282
	.4byte	$LBB283
	.4byte	$LBE283
	.4byte	$LBB284
	.4byte	$LBE284
	.4byte	0
	.4byte	0
	.4byte	$LBB295
	.4byte	$LBE295
	.4byte	$LBB298
	.4byte	$LBE298
	.4byte	0
	.4byte	0
	.4byte	$LBB308
	.4byte	$LBE308
	.4byte	$LBB310
	.4byte	$LBE310
	.4byte	0
	.4byte	0
	.4byte	$LBB309
	.4byte	$LBE309
	.4byte	$LBB311
	.4byte	$LBE311
	.4byte	0
	.4byte	0
	.4byte	$LBB312
	.4byte	$LBE312
	.4byte	$LBB317
	.4byte	$LBE317
	.4byte	0
	.4byte	0
	.4byte	$LBB321
	.4byte	$LBE321
	.4byte	$LBB326
	.4byte	$LBE326
	.4byte	0
	.4byte	0
	.4byte	$LBB327
	.4byte	$LBE327
	.4byte	$LBB335
	.4byte	$LBE335
	.4byte	$LBB336
	.4byte	$LBE336
	.4byte	$LBB337
	.4byte	$LBE337
	.4byte	0
	.4byte	0
	.4byte	$LBB328
	.4byte	$LBE328
	.4byte	$LBB333
	.4byte	$LBE333
	.4byte	0
	.4byte	0
	.4byte	$LBB340
	.4byte	$LBE340
	.4byte	$LBB387
	.4byte	$LBE387
	.4byte	0
	.4byte	0
	.4byte	$LBB341
	.4byte	$LBE341
	.4byte	$LBB342
	.4byte	$LBE342
	.4byte	0
	.4byte	0
	.4byte	$LBB343
	.4byte	$LBE343
	.4byte	$LBB344
	.4byte	$LBE344
	.4byte	$LBB345
	.4byte	$LBE345
	.4byte	$LBB346
	.4byte	$LBE346
	.4byte	0
	.4byte	0
	.4byte	$LBB347
	.4byte	$LBE347
	.4byte	$LBB348
	.4byte	$LBE348
	.4byte	$LBB349
	.4byte	$LBE349
	.4byte	$LBB350
	.4byte	$LBE350
	.4byte	0
	.4byte	0
	.4byte	$LBB357
	.4byte	$LBE357
	.4byte	$LBB365
	.4byte	$LBE365
	.4byte	$LBB366
	.4byte	$LBE366
	.4byte	$LBB368
	.4byte	$LBE368
	.4byte	$LBB369
	.4byte	$LBE369
	.4byte	0
	.4byte	0
	.4byte	$LBB367
	.4byte	$LBE367
	.4byte	$LBB370
	.4byte	$LBE370
	.4byte	0
	.4byte	0
	.4byte	$LBB371
	.4byte	$LBE371
	.4byte	$LBB384
	.4byte	$LBE384
	.4byte	$LBB385
	.4byte	$LBE385
	.4byte	$LBB386
	.4byte	$LBE386
	.4byte	0
	.4byte	0
	.4byte	$LBB375
	.4byte	$LBE375
	.4byte	$LBB380
	.4byte	$LBE380
	.4byte	0
	.4byte	0
	.4byte	$LBB388
	.4byte	$LBE388
	.4byte	$LBB393
	.4byte	$LBE393
	.4byte	0
	.4byte	0
	.4byte	$LBB400
	.4byte	$LBE400
	.4byte	$LBB404
	.4byte	$LBE404
	.4byte	0
	.4byte	0
	.4byte	$LBB401
	.4byte	$LBE401
	.4byte	$LBB402
	.4byte	$LBE402
	.4byte	0
	.4byte	0
	.4byte	$LBB414
	.4byte	$LBE414
	.4byte	$LBB415
	.4byte	$LBE415
	.4byte	0
	.4byte	0
	.4byte	$LBB416
	.4byte	$LBE416
	.4byte	$LBB417
	.4byte	$LBE417
	.4byte	0
	.4byte	0
	.4byte	$Ltext0
	.4byte	$Letext0
	.4byte	$LFB3093
	.4byte	$LFE3093
	.4byte	$LFB3094
	.4byte	$LFE3094
	.4byte	0
	.4byte	0
	.section	.debug_line,"",@progbits
$Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
$LASF190:
	.ascii	"kmalloc_order_trace\000"
$LASF154:
	.ascii	"IPV4_DEVCONF_FORWARDING\000"
$LASF153:
	.ascii	"pptp_acc_info\000"
$LASF127:
	.ascii	"RTAX_HOPLIMIT\000"
$LASF311:
	.ascii	"ksoftirqd\000"
$LASF297:
	.ascii	"overflowgid\000"
$LASF314:
	.ascii	"ioport_resource\000"
$LASF264:
	.ascii	"tmpbuf\000"
$LASF175:
	.ascii	"IPV4_DEVCONF_ARP_NOTIFY\000"
$LASF166:
	.ascii	"IPV4_DEVCONF_ARPFILTER\000"
$LASF298:
	.ascii	"init_user_ns\000"
$LASF50:
	.ascii	"IPPROTO_IP\000"
$LASF292:
	.ascii	"console_printk\000"
$LASF343:
	.ascii	"get_fastpptp_lastxmit_fphook\000"
$LASF199:
	.ascii	"__fswab16\000"
$LASF142:
	.ascii	"ND_OPT_ROUTE_INFO\000"
$LASF186:
	.ascii	"flags\000"
$LASF158:
	.ascii	"IPV4_DEVCONF_SECURE_REDIRECTS\000"
$LASF135:
	.ascii	"__ND_OPT_PREFIX_INFO_END\000"
$LASF245:
	.ascii	"check_stats\000"
$LASF201:
	.ascii	"ip_fast_csum\000"
$LASF152:
	.ascii	"PptpCallDisconnectNotify\000"
$LASF200:
	.ascii	"__fswab32\000"
$LASF126:
	.ascii	"RTAX_REORDERING\000"
$LASF91:
	.ascii	"IFLA_MASTER\000"
$LASF7:
	.ascii	"unsigned int\000"
$LASF83:
	.ascii	"IFLA_BROADCAST\000"
$LASF204:
	.ascii	"csum\000"
$LASF36:
	.ascii	"pglist_data\000"
$LASF106:
	.ascii	"IFLA_PORT_SELF\000"
$LASF282:
	.ascii	"pid_namespace\000"
$LASF132:
	.ascii	"__RTAX_MAX\000"
$LASF165:
	.ascii	"IPV4_DEVCONF_TAG\000"
$LASF39:
	.ascii	"module\000"
$LASF52:
	.ascii	"IPPROTO_IGMP\000"
$LASF308:
	.ascii	"contig_page_data\000"
$LASF295:
	.ascii	"persistent_clock_exist\000"
$LASF95:
	.ascii	"IFLA_MAP\000"
$LASF137:
	.ascii	"ND_OPT_TARGET_LL_ADDR\000"
$LASF286:
	.ascii	"pptpAccInfo\000"
$LASF179:
	.ascii	"IPV4_DEVCONF_ROUTE_LOCALNET\000"
$LASF75:
	.ascii	"NF_INET_LOCAL_OUT\000"
$LASF224:
	.ascii	"gre_len\000"
$LASF333:
	.ascii	"sysctl_ip_default_ttl\000"
$LASF247:
	.ascii	"ppp_data\000"
$LASF144:
	.ascii	"ND_OPT_DNSSL\000"
$LASF266:
	.ascii	"__cu_from\000"
$LASF275:
	.ascii	"userbuf\000"
$LASF176:
	.ascii	"IPV4_DEVCONF_ACCEPT_LOCAL\000"
$LASF32:
	.ascii	"seqcount\000"
$LASF65:
	.ascii	"IPPROTO_BEETPH\000"
$LASF173:
	.ascii	"IPV4_DEVCONF_PROMOTE_SECONDARIES\000"
$LASF118:
	.ascii	"RTAX_LOCK\000"
$LASF323:
	.ascii	"nf_hooks\000"
$LASF276:
	.ascii	"ppfw_write_proc\000"
$LASF290:
	.ascii	"__this_module\000"
$LASF268:
	.ascii	"__addr\000"
$LASF218:
	.ascii	"atoi_dec\000"
$LASF260:
	.ascii	"fast_pptp_sync_rx_seq\000"
$LASF139:
	.ascii	"ND_OPT_REDIRECT_HDR\000"
$LASF348:
	.ascii	"get_fastpptp_lastxmit\000"
$LASF141:
	.ascii	"__ND_OPT_ARRAY_MAX\000"
$LASF110:
	.ascii	"IFLA_EXT_MASK\000"
$LASF63:
	.ascii	"IPPROTO_ESP\000"
$LASF203:
	.ascii	"stop\000"
$LASF285:
	.ascii	"eth_reserved_addr_base\000"
$LASF325:
	.ascii	"init_net\000"
$LASF55:
	.ascii	"IPPROTO_EGP\000"
$LASF344:
	.ascii	"GNU C 4.8.3 -fpreprocessed -G 0 -mno-check-zero-division"
	.ascii	" -mabi=32 -mno-abicalls -mno-branch-likely -msoft-float "
	.ascii	"-march=mips32r2 -mno-long-calls -mllsc -mplt -mno-shared"
	.ascii	" -g -O2 -fno-strict-aliasing -fno-common -fno-delete-nul"
	.ascii	"l-pointer-checks -fno-reorder-blocks -fno-tree-ch -fno-c"
	.ascii	"aller-saves -fno-pic -ffreestanding -fno-stack-protector"
	.ascii	" -fomit-frame-pointer -femit-struct-debug-baseonly -fno-"
	.ascii	"var-tracking -fno-strict-overflow -fconserve-stack\000"
$LASF239:
	.ascii	"__len\000"
$LASF105:
	.ascii	"IFLA_VF_PORTS\000"
$LASF220:
	.ascii	"index\000"
$LASF13:
	.ascii	"__kernel_ssize_t\000"
$LASF244:
	.ascii	"pull_offset\000"
$LASF12:
	.ascii	"__kernel_size_t\000"
$LASF250:
	.ascii	"fast_pptp_to_wan\000"
$LASF9:
	.ascii	"long long unsigned int\000"
$LASF34:
	.ascii	"pte_t\000"
$LASF318:
	.ascii	"zero_page_mask\000"
$LASF210:
	.ascii	"ppp_device\000"
$LASF30:
	.ascii	"thread_info\000"
$LASF313:
	.ascii	"kmalloc_caches\000"
$LASF24:
	.ascii	"ssize_t\000"
$LASF28:
	.ascii	"cpuinfo_mips\000"
$LASF256:
	.ascii	"wanip1\000"
$LASF257:
	.ascii	"wanip2\000"
$LASF258:
	.ascii	"wanip3\000"
$LASF205:
	.ascii	"carry\000"
$LASF181:
	.ascii	"__arch_swab16\000"
$LASF307:
	.ascii	"system_freezable_wq\000"
$LASF98:
	.ascii	"IFLA_LINKMODE\000"
$LASF350:
	.ascii	"fast_pptp_exit\000"
$LASF231:
	.ascii	"Check_GRE_rx_net_device\000"
$LASF92:
	.ascii	"IFLA_WIRELESS\000"
$LASF180:
	.ascii	"__IPV4_DEVCONF_MAX\000"
$LASF347:
	.ascii	"nf_inet_hooks\000"
$LASF45:
	.ascii	"kernel_stat\000"
$LASF23:
	.ascii	"size_t\000"
$LASF206:
	.ascii	"arch_irqs_disabled_flags\000"
$LASF248:
	.ascii	"offset\000"
$LASF103:
	.ascii	"IFLA_VFINFO_LIST\000"
$LASF156:
	.ascii	"IPV4_DEVCONF_PROXY_ARP\000"
$LASF236:
	.ascii	"ocreq\000"
$LASF195:
	.ascii	"csum_fold\000"
$LASF21:
	.ascii	"_Bool\000"
$LASF274:
	.ascii	"__cu_len_r\000"
$LASF230:
	.ascii	"is_pptp_device\000"
$LASF123:
	.ascii	"RTAX_SSTHRESH\000"
$LASF226:
	.ascii	"pptpconn_read_proc\000"
$LASF138:
	.ascii	"ND_OPT_PREFIX_INFO\000"
$LASF47:
	.ascii	"resource\000"
$LASF133:
	.ascii	"neigh_table\000"
$LASF85:
	.ascii	"IFLA_MTU\000"
$LASF57:
	.ascii	"IPPROTO_UDP\000"
$LASF155:
	.ascii	"IPV4_DEVCONF_MC_FORWARDING\000"
$LASF301:
	.ascii	"mips_io_port_base\000"
$LASF97:
	.ascii	"IFLA_OPERSTATE\000"
$LASF161:
	.ascii	"IPV4_DEVCONF_RP_FILTER\000"
$LASF76:
	.ascii	"NF_INET_POST_ROUTING\000"
$LASF149:
	.ascii	"PptpOutCallRequest\000"
$LASF4:
	.ascii	"__u16\000"
$LASF249:
	.ascii	"ppp_offset\000"
$LASF104:
	.ascii	"IFLA_STATS64\000"
$LASF340:
	.ascii	"fastpath_pptp_proc_fops\000"
$LASF263:
	.ascii	"count\000"
$LASF324:
	.ascii	"nf_nat_decode_session_hook\000"
$LASF136:
	.ascii	"ND_OPT_SOURCE_LL_ADDR\000"
$LASF229:
	.ascii	"pptp_conn_single_open\000"
$LASF182:
	.ascii	"__arch_swab32\000"
$LASF198:
	.ascii	"bcopy\000"
$LASF253:
	.ascii	"iph_newone\000"
$LASF15:
	.ascii	"char\000"
$LASF217:
	.ascii	"might_fault\000"
$LASF53:
	.ascii	"IPPROTO_IPIP\000"
$LASF43:
	.ascii	"file_operations\000"
$LASF316:
	.ascii	"totalram_pages\000"
$LASF129:
	.ascii	"RTAX_FEATURES\000"
$LASF208:
	.ascii	"__tmp1\000"
$LASF278:
	.ascii	"fastpath_pptp_single_write\000"
$LASF273:
	.ascii	"__cu_from_r\000"
$LASF187:
	.ascii	"order\000"
$LASF84:
	.ascii	"IFLA_IFNAME\000"
$LASF271:
	.ascii	"__ok\000"
$LASF267:
	.ascii	"__cu_len\000"
$LASF177:
	.ascii	"IPV4_DEVCONF_SRC_VMARK\000"
$LASF337:
	.ascii	"fast_pptp_fw\000"
$LASF42:
	.ascii	"file\000"
$LASF6:
	.ascii	"__u32\000"
$LASF281:
	.ascii	"workqueue_struct\000"
$LASF46:
	.ascii	"kmem_cache\000"
$LASF188:
	.ascii	"kmem_cache_alloc_trace\000"
$LASF336:
	.ascii	"proc_root\000"
$LASF332:
	.ascii	"ip_tos2prio\000"
$LASF44:
	.ascii	"task_struct\000"
$LASF73:
	.ascii	"NF_INET_LOCAL_IN\000"
$LASF261:
	.ascii	"pptpconn_write_proc\000"
$LASF62:
	.ascii	"IPPROTO_IPV6\000"
$LASF87:
	.ascii	"IFLA_QDISC\000"
$LASF8:
	.ascii	"long long int\000"
$LASF312:
	.ascii	"kstat\000"
$LASF145:
	.ascii	"__ND_OPT_MAX\000"
$LASF122:
	.ascii	"RTAX_RTTVAR\000"
$LASF56:
	.ascii	"IPPROTO_PUP\000"
$LASF237:
	.ascii	"occlrnotify\000"
$LASF80:
	.ascii	"seq_file\000"
$LASF40:
	.ascii	"inode\000"
$LASF101:
	.ascii	"IFLA_IFALIAS\000"
$LASF64:
	.ascii	"IPPROTO_AH\000"
$LASF77:
	.ascii	"NF_INET_NUMHOOKS\000"
$LASF143:
	.ascii	"ND_OPT_RDNSS\000"
$LASF35:
	.ascii	"page\000"
$LASF125:
	.ascii	"RTAX_ADVMSS\000"
$LASF51:
	.ascii	"IPPROTO_ICMP\000"
$LASF20:
	.ascii	"bool\000"
$LASF159:
	.ascii	"IPV4_DEVCONF_SEND_REDIRECTS\000"
$LASF184:
	.ascii	"min_count\000"
$LASF157:
	.ascii	"IPV4_DEVCONF_ACCEPT_REDIRECTS\000"
$LASF172:
	.ascii	"IPV4_DEVCONF_ARP_IGNORE\000"
$LASF71:
	.ascii	"IPPROTO_MAX\000"
$LASF164:
	.ascii	"IPV4_DEVCONF_LOG_MARTIANS\000"
$LASF194:
	.ascii	"kmalloc_index\000"
$LASF89:
	.ascii	"IFLA_COST\000"
$LASF299:
	.ascii	"shm_align_mask\000"
$LASF262:
	.ascii	"buffer\000"
$LASF183:
	.ascii	"size\000"
$LASF197:
	.ascii	"kmemleak_alloc\000"
$LASF329:
	.ascii	"sysctl_local_reserved_ports\000"
$LASF111:
	.ascii	"IFLA_PROMISCUITY\000"
$LASF225:
	.ascii	"ppfw_read_proc\000"
$LASF41:
	.ascii	"dqstats\000"
$LASF108:
	.ascii	"IFLA_GROUP\000"
$LASF296:
	.ascii	"overflowuid\000"
$LASF160:
	.ascii	"IPV4_DEVCONF_SHARED_MEDIA\000"
$LASF72:
	.ascii	"NF_INET_PRE_ROUTING\000"
$LASF235:
	.ascii	"ocack\000"
$LASF303:
	.ascii	"page_group_by_mobility_disabled\000"
$LASF107:
	.ascii	"IFLA_AF_SPEC\000"
$LASF254:
	.ascii	"grehone\000"
$LASF128:
	.ascii	"RTAX_INITCWND\000"
$LASF58:
	.ascii	"IPPROTO_IDP\000"
$LASF280:
	.ascii	"user_namespace\000"
$LASF214:
	.ascii	"__res\000"
$LASF240:
	.ascii	"__ret\000"
$LASF246:
	.ascii	"data\000"
$LASF131:
	.ascii	"RTAX_INITRWND\000"
$LASF320:
	.ascii	"vm_stat\000"
$LASF279:
	.ascii	"fast_pptp_init\000"
$LASF243:
	.ascii	"ppp_type\000"
$LASF330:
	.ascii	"inet_csk_timer_bug_msg\000"
$LASF74:
	.ascii	"NF_INET_FORWARD\000"
$LASF120:
	.ascii	"RTAX_WINDOW\000"
$LASF102:
	.ascii	"IFLA_NUM_VF\000"
$LASF251:
	.ascii	"header_len\000"
$LASF345:
	.ascii	"/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_"
	.ascii	"v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_"
	.ascii	"20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/l"
	.ascii	"inux-rtkmipsel_rtl8197f/fastpath-0.1/fast_pptp_core.c\000"
$LASF306:
	.ascii	"system_wq\000"
$LASF331:
	.ascii	"nd_tbl\000"
$LASF317:
	.ascii	"invalid_pte_table\000"
$LASF79:
	.ascii	"flowi\000"
$LASF60:
	.ascii	"IPPROTO_RSVP\000"
$LASF113:
	.ascii	"IFLA_NUM_RX_QUEUES\000"
$LASF61:
	.ascii	"IPPROTO_GRE\000"
$LASF277:
	.ascii	"pptp_conn_single_write\000"
$LASF115:
	.ascii	"__IFLA_MAX\000"
$LASF222:
	.ascii	"is_forward\000"
$LASF29:
	.ascii	"sizetype\000"
$LASF193:
	.ascii	"kmalloc_large\000"
$LASF212:
	.ascii	"__cs\000"
$LASF213:
	.ascii	"__ct\000"
$LASF49:
	.ascii	"ethhdr\000"
$LASF189:
	.ascii	"gfpflags\000"
$LASF2:
	.ascii	"short int\000"
$LASF265:
	.ascii	"__cu_to\000"
$LASF11:
	.ascii	"long int\000"
$LASF121:
	.ascii	"RTAX_RTT\000"
$LASF342:
	.ascii	"set_pptp_device_fphook\000"
$LASF168:
	.ascii	"IPV4_DEVCONF_NOXFRM\000"
$LASF117:
	.ascii	"RTAX_UNSPEC\000"
$LASF93:
	.ascii	"IFLA_PROTINFO\000"
$LASF178:
	.ascii	"IPV4_DEVCONF_PROXY_ARP_PVLAN\000"
$LASF112:
	.ascii	"IFLA_NUM_TX_QUEUES\000"
$LASF326:
	.ascii	"memalloc_socks\000"
$LASF119:
	.ascii	"RTAX_MTU\000"
$LASF227:
	.ascii	"sync_tx_pptp_gre_seqno\000"
$LASF174:
	.ascii	"IPV4_DEVCONF_ARP_ACCEPT\000"
$LASF66:
	.ascii	"IPPROTO_PIM\000"
$LASF170:
	.ascii	"IPV4_DEVCONF_FORCE_IGMP_VERSION\000"
$LASF196:
	.ascii	"arch_local_irq_save\000"
$LASF349:
	.ascii	"Get_fast_pptp_fw\000"
$LASF99:
	.ascii	"IFLA_LINKINFO\000"
$LASF202:
	.ascii	"word\000"
$LASF162:
	.ascii	"IPV4_DEVCONF_ACCEPT_SOURCE_ROUTE\000"
$LASF302:
	.ascii	"max_mapnr\000"
$LASF223:
	.ascii	"protocol\000"
$LASF81:
	.ascii	"IFLA_UNSPEC\000"
$LASF310:
	.ascii	"cad_pid\000"
$LASF293:
	.ascii	"hex_asc\000"
$LASF147:
	.ascii	"pptp_pkt_hdr\000"
$LASF252:
	.ascii	"iph_new\000"
$LASF328:
	.ascii	"ipv6_hash_secret\000"
$LASF16:
	.ascii	"__be16\000"
$LASF68:
	.ascii	"IPPROTO_SCTP\000"
$LASF86:
	.ascii	"IFLA_LINK\000"
$LASF185:
	.ascii	"kmalloc_order\000"
$LASF191:
	.ascii	"__ilog2_u32\000"
$LASF146:
	.ascii	"pptp_gre_hdr\000"
$LASF315:
	.ascii	"debug_locks\000"
$LASF38:
	.ascii	"static_key\000"
$LASF148:
	.ascii	"PptpControlHeader\000"
$LASF192:
	.ascii	"__get_order\000"
$LASF100:
	.ascii	"IFLA_NET_NS_PID\000"
$LASF26:
	.ascii	"atomic_t\000"
$LASF209:
	.ascii	"set_pptp_device\000"
$LASF289:
	.ascii	"res_check_pptp\000"
$LASF10:
	.ascii	"long unsigned int\000"
$LASF3:
	.ascii	"__u8\000"
$LASF305:
	.ascii	"jiffies\000"
$LASF321:
	.ascii	"__init_begin\000"
$LASF78:
	.ascii	"nf_afinfo\000"
$LASF346:
	.ascii	"/home/extra_home/marklee/rtk_OpenWRT_BB/BB_v1407_branch_"
	.ascii	"v25/v25_relase_source_test_0830/rtk_OpenWRT_v2.5_Branch_"
	.ascii	"20160603/build_dir/target-mipsel_24kec_uClibc-0.9.33.2/l"
	.ascii	"inux-rtkmipsel_rtl8197f/linux-3.10.49\000"
$LASF134:
	.ascii	"tcphdr\000"
$LASF283:
	.ascii	"proc_dir_entry\000"
$LASF69:
	.ascii	"IPPROTO_UDPLITE\000"
$LASF291:
	.ascii	"cpu_data\000"
$LASF54:
	.ascii	"IPPROTO_TCP\000"
$LASF150:
	.ascii	"PptpOutCallReply\000"
$LASF114:
	.ascii	"IFLA_CARRIER\000"
$LASF67:
	.ascii	"IPPROTO_COMP\000"
$LASF109:
	.ascii	"IFLA_NET_NS_FD\000"
$LASF163:
	.ascii	"IPV4_DEVCONF_BOOTP_RELAY\000"
$LASF22:
	.ascii	"loff_t\000"
$LASF1:
	.ascii	"unsigned char\000"
$LASF14:
	.ascii	"__kernel_loff_t\000"
$LASF82:
	.ascii	"IFLA_ADDRESS\000"
$LASF327:
	.ascii	"inet_ehash_secret\000"
$LASF255:
	.ascii	"ppp_hdr_len\000"
$LASF335:
	.ascii	"xt_recseq\000"
$LASF219:
	.ascii	"kmalloc\000"
$LASF287:
	.ascii	"pptp_conn_check\000"
$LASF130:
	.ascii	"RTAX_RTO_MIN\000"
$LASF124:
	.ascii	"RTAX_CWND\000"
$LASF18:
	.ascii	"__sum16\000"
$LASF284:
	.ascii	"frag_percpu_counter_batch\000"
$LASF322:
	.ascii	"__init_end\000"
$LASF309:
	.ascii	"init_pid_ns\000"
$LASF167:
	.ascii	"IPV4_DEVCONF_MEDIUM_ID\000"
$LASF27:
	.ascii	"list_head\000"
$LASF216:
	.ascii	"__current_thread_info\000"
$LASF17:
	.ascii	"__be32\000"
$LASF94:
	.ascii	"IFLA_TXQLEN\000"
$LASF338:
	.ascii	"sync_tx_pptp_gre_seqno_hook\000"
$LASF241:
	.ascii	"fast_pptp_to_lan\000"
$LASF232:
	.ascii	"fast_pptp_filter\000"
$LASF234:
	.ascii	"ctlh\000"
$LASF334:
	.ascii	"arp_tbl\000"
$LASF288:
	.ascii	"res1\000"
$LASF270:
	.ascii	"__mask\000"
$LASF116:
	.ascii	"iphdr\000"
$LASF88:
	.ascii	"IFLA_STATS\000"
$LASF269:
	.ascii	"__size\000"
$LASF171:
	.ascii	"IPV4_DEVCONF_ARP_ANNOUNCE\000"
$LASF0:
	.ascii	"signed char\000"
$LASF140:
	.ascii	"ND_OPT_MTU\000"
$LASF242:
	.ascii	"pskb\000"
$LASF96:
	.ascii	"IFLA_WEIGHT\000"
$LASF5:
	.ascii	"short unsigned int\000"
$LASF300:
	.ascii	"flush_data_cache_page\000"
$LASF151:
	.ascii	"PptpClearCallRequest\000"
$LASF339:
	.ascii	"pptp_tcp_finished\000"
$LASF25:
	.ascii	"gfp_t\000"
$LASF341:
	.ascii	"pptp_conn_proc_fops\000"
$LASF19:
	.ascii	"__wsum\000"
$LASF33:
	.ascii	"seqcount_t\000"
$LASF221:
	.ascii	"greh\000"
$LASF215:
	.ascii	"current_thread_info\000"
$LASF37:
	.ascii	"double\000"
$LASF319:
	.ascii	"zero_pfn\000"
$LASF207:
	.ascii	"arch_local_irq_restore\000"
$LASF90:
	.ascii	"IFLA_PRIORITY\000"
$LASF169:
	.ascii	"IPV4_DEVCONF_NOPOLICY\000"
$LASF228:
	.ascii	"fastpath_pptp_single_open\000"
$LASF31:
	.ascii	"atomic_long_t\000"
$LASF238:
	.ascii	"occlrreq\000"
$LASF259:
	.ascii	"new_skb\000"
$LASF59:
	.ascii	"IPPROTO_DCCP\000"
$LASF304:
	.ascii	"mem_map\000"
$LASF272:
	.ascii	"__cu_to_r\000"
$LASF48:
	.ascii	"sk_buff\000"
$LASF70:
	.ascii	"IPPROTO_RAW\000"
$LASF211:
	.ascii	"strcmp\000"
$LASF233:
	.ascii	"pptph\000"
$LASF294:
	.ascii	"cpu_bit_bitmap\000"
	.ident	"GCC: (OpenWrt/Linaro GCC 4.8-2014.04 r39885) 4.8.3"

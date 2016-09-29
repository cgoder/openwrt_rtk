/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#ifndef	__PHYDM_IQK_8197F_H__
#define    __PHYDM_IQK_8197F_H__

/*--------------------------Define Parameters-------------------------------*/
#define	MAC_REG_NUM_8197F	2
#define	BB_REG_NUM_8197F		12
#define	RF_REG_NUM_8197F		3


#define	LOK_delay_8197F		100
#define	IQK_delay_8197F		100
#define	WBIQK_delay_8197F		100

/*---------------------------End Define Parameters-------------------------------*/


#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
VOID 
DoIQK_8197F(
	PVOID	pDM_VOID,
	u1Byte		DeltaThermalIndex,
	u1Byte		ThermalValue,	
	u1Byte		Threshold
	);
#else
VOID 
DoIQK_8197F(
	PVOID		pDM_VOID,
	u1Byte		DeltaThermalIndex,
	u1Byte		ThermalValue,	
	u1Byte		Threshold
	);
#endif

VOID	
PHY_IQCalibrate_8197F(	
	PVOID		pDM_VOID,
	BOOLEAN		bReCovery
	);



VOID
PHY_LCCalibrate_8197F(
	PVOID pDM_VOID
	);

#endif	/*#ifndef __PHYDM_IQK_8197F_H__*/

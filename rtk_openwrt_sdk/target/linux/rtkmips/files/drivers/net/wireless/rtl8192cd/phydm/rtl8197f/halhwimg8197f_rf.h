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

/*Image2HeaderVersion: 2.22*/
#if (RTL8197F_SUPPORT == 1)
#ifndef __INC_MP_RF_HW_IMG_8197F_H
#define __INC_MP_RF_HW_IMG_8197F_H


/******************************************************************************
*                           RadioA.TXT
******************************************************************************/

void
ODM_ReadAndConfig_MP_8197F_RadioA(/* TC: Test Chip, MP: MP Chip*/
	IN   PDM_ODM_T  pDM_Odm
);
u4Byte ODM_GetVersion_MP_8197F_RadioA(void);

/******************************************************************************
*                           RadioB.TXT
******************************************************************************/

void
ODM_ReadAndConfig_MP_8197F_RadioB(/* TC: Test Chip, MP: MP Chip*/
	IN   PDM_ODM_T  pDM_Odm
);
u4Byte ODM_GetVersion_MP_8197F_RadioB(void);

/******************************************************************************
*                           TxPowerTrack.TXT
******************************************************************************/

void
ODM_ReadAndConfig_MP_8197F_TxPowerTrack(/* TC: Test Chip, MP: MP Chip*/
	IN   PDM_ODM_T  pDM_Odm
);
u4Byte ODM_GetVersion_MP_8197F_TxPowerTrack(void);

/******************************************************************************
*                           TxPowerTrack_Type0.TXT
******************************************************************************/

void
ODM_ReadAndConfig_MP_8197F_TxPowerTrack_Type0(/* TC: Test Chip, MP: MP Chip*/
	IN   PDM_ODM_T  pDM_Odm
);
u4Byte ODM_GetVersion_MP_8197F_TxPowerTrack_Type0(void);

/******************************************************************************
*                           TxPowerTrack_Type1.TXT
******************************************************************************/

void
ODM_ReadAndConfig_MP_8197F_TxPowerTrack_Type1(/* TC: Test Chip, MP: MP Chip*/
	IN   PDM_ODM_T  pDM_Odm
);
u4Byte ODM_GetVersion_MP_8197F_TxPowerTrack_Type1(void);

#endif
#endif /* end of HWIMG_SUPPORT*/


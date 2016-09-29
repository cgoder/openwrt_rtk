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

#include "mp_precomp.h"
#include "../phydm_precomp.h"


/*---------------------------Define Local Constant---------------------------*/


/*---------------------------Define Local Constant---------------------------*/


#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
void DoIQK_8197F(
	PVOID		pDM_VOID,
	u1Byte		DeltaThermalIndex,
	u1Byte		ThermalValue,	
	u1Byte		Threshold
	)
{
	PDM_ODM_T	pDM_Odm = (PDM_ODM_T)pDM_VOID;

	PADAPTER	Adapter = pDM_Odm->Adapter;
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(Adapter);

	ODM_ResetIQKResult(pDM_Odm);		

	pDM_Odm->RFCalibrateInfo.ThermalValue_IQK = ThermalValue;
	
	PHY_IQCalibrate_8197F(pDM_Odm, FALSE);
	
}
#else
/*Originally pConfig->DoIQK is hooked PHY_IQCalibrate_8197F, but DoIQK_8197F and PHY_IQCalibrate_8197F have different arguments*/
void DoIQK_8197F(
	PVOID		pDM_VOID,
	u1Byte		DeltaThermalIndex,
	u1Byte		ThermalValue,	
	u1Byte		Threshold
	)
{
#if 1
	PDM_ODM_T	pDM_Odm = (PDM_ODM_T)pDM_VOID;
	BOOLEAN		bReCovery = (BOOLEAN) DeltaThermalIndex;

	PHY_IQCalibrate_8197F(pDM_Odm, bReCovery);
#endif
}
#endif

#define MAX_TOLERANCE		5
#define IQK_DELAY_TIME		1		/*ms*/

u1Byte			/*bit0 = 1 => Tx OK, bit1 = 1 => Rx OK*/
phy_PathA_IQK_8197F(
#if (DM_ODM_SUPPORT_TYPE & ODM_AP)
	PVOID		pDM_VOID,
#else
	PADAPTER	pAdapter,
#endif
	BOOLEAN		configPathB
)
{
	PDM_ODM_T		pDM_Odm	= (PDM_ODM_T)pDM_VOID;

	u4Byte regEAC, regE94, regE9C, regEA4, tmp;
	u1Byte result = 0x00;
	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(pAdapter);
	#if (DM_ODM_SUPPORT_TYPE == ODM_CE)
	PDM_ODM_T		pDM_Odm = &pHalData->odmpriv;
	#endif
	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)
	PDM_ODM_T		pDM_Odm = &pHalData->DM_OutSrc;
	#endif
	#endif
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] ====================Path A TXIQK start!====================\n"));

	/*=============================TXIQK setting=============================*/
	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x000000);

	/*modify TXIQK mode table*/
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, RF_WE_LUT, 0x80000, 0x1);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, RF_RCK_OS, bRFRegOffsetMask, 0x20000);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, RF_TXPA_G1, bRFRegOffsetMask, 0x0005f);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, RF_TXPA_G2, bRFRegOffsetMask, 0x01ff7);  /*PA off, default: 0x1fff*/

	if (pDM_Odm->ExtPA) {
		ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, 0xdf, 0x00800, 0x1);
		ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, 0x56, 0x003ff, 0x71);	
	} else if (pDM_Odm->ExtPA == 0 && pDM_Odm->CutVersion != ODM_CUT_A) {	
		ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, 0xdf, 0x00800, 0x1);
		ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, 0x56, 0x003ff, 0xe8);
	}

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0x56 at Path A TXIQK = 0x%x\n",
				 ODM_GetRFReg(pDM_Odm, ODM_RF_PATH_A, 0x56, bRFRegOffsetMask)));


	/*enter IQK mode*/
	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x808000);

	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Path-A IQK setting!\n"));*/
	ODM_SetBBReg(pDM_Odm, rTx_IQK_Tone_A, bMaskDWord, 0x18008c0c);
	ODM_SetBBReg(pDM_Odm, rRx_IQK_Tone_A, bMaskDWord, 0x38008c0c);
	ODM_SetBBReg(pDM_Odm, rTx_IQK_Tone_B, bMaskDWord, 0x38008c0c);
	ODM_SetBBReg(pDM_Odm, rRx_IQK_Tone_B, bMaskDWord, 0x38008c0c);

	if (pDM_Odm->CutVersion == ODM_CUT_A) { 
		if (pDM_Odm->ExtPA)
			ODM_SetBBReg(pDM_Odm, rTx_IQK_PI_A, bMaskDWord, 0x8214400f);
		else
			ODM_SetBBReg(pDM_Odm, rTx_IQK_PI_A, bMaskDWord, 0x82140002);
	} else
		ODM_SetBBReg(pDM_Odm, rTx_IQK_PI_A, bMaskDWord, 0x8214000f);
	
	ODM_SetBBReg(pDM_Odm, rRx_IQK_PI_A, bMaskDWord, 0x28140000);

	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] LO calibration setting!\n"));*/
	ODM_SetBBReg(pDM_Odm, rIQK_AGC_Rsp, bMaskDWord, 0x00862911);

	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] One shot, path A LOK & IQK!\n"));*/
	ODM_SetBBReg(pDM_Odm, rIQK_AGC_Pts, bMaskDWord, 0xf9005800);
	ODM_SetBBReg(pDM_Odm, rIQK_AGC_Pts, bMaskDWord, 0xf8005800);

	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Delay %d ms for One shot, path A LOK & IQK.\n", IQK_DELAY_TIME_97F));*/
	ODM_delay_ms(IQK_DELAY_TIME_97F);

	/*Check failed*/
	regEAC = ODM_GetBBReg(pDM_Odm, rRx_Power_After_IQK_A_2, bMaskDWord);
	regE94 = ODM_GetBBReg(pDM_Odm, rTx_Power_Before_IQK_A, bMaskDWord);
	regE9C = ODM_GetBBReg(pDM_Odm, rTx_Power_After_IQK_A, bMaskDWord);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xeac = 0x%x\n", regEAC));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xe94 = 0x%x, 0xe9c = 0x%x\n", regE94, regE9C));
	/*monitor image power before & after IQK*/
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xe90(before IQK)= 0x%x, 0xe98(afer IQK) = 0x%x\n",
				 ODM_GetBBReg(pDM_Odm, 0xe90, bMaskDWord), ODM_GetBBReg(pDM_Odm, 0xe98, bMaskDWord)));


	/*reload 0xdf and CCK_IND off  */
	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x000000);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, 0x0, BIT14, 0x0);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, 0xdf, 0x00800, 0x0);

	if (!(regEAC & BIT28) &&
		(((regE94 & 0x03FF0000) >> 16) != 0x142) &&
		(((regE9C & 0x03FF0000) >> 16) != 0x42))
		result |= 0x01;
	else
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] path A TXIQK is not success\n"));	
	return result;

}

u1Byte			/*bit0 = 1 => Tx OK, bit1 = 1 => Rx OK*/
phy_PathA_RxIQK_97F(
#if (DM_ODM_SUPPORT_TYPE & ODM_AP)
	PVOID		pDM_VOID,
#else
	PADAPTER	pAdapter,
#endif
	BOOLEAN		configPathB
)
{
	PDM_ODM_T		pDM_Odm	= (PDM_ODM_T)pDM_VOID;

	u4Byte regEAC, regE94, regE9C, regEA4, u4tmp, RXPGA;
	u1Byte result = 0x00;
	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(pAdapter);
	#if (DM_ODM_SUPPORT_TYPE == ODM_CE)
	PDM_ODM_T		pDM_Odm = &pHalData->odmpriv;
	#endif
	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)
	PDM_ODM_T		pDM_Odm = &pHalData->DM_OutSrc;
	#endif
	#endif
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Path A RxIQK start!\n"));

	/* =============================Get TXIMR setting=============================*/
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] ====================Path A RXIQK step1!====================\n"));


	/*modify RXIQK mode table*/
	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x000000);

	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, RF_WE_LUT, 0x80000, 0x1);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, RF_RCK_OS, bRFRegOffsetMask, 0x30000);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, RF_TXPA_G1, bRFRegOffsetMask, 0x0005f);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, RF_TXPA_G2, bRFRegOffsetMask, 0xf1df3); /*PA off, deafault:0xf1dfb*/

	if (pDM_Odm->CutVersion == ODM_CUT_A) {
		RXPGA = ODM_GetRFReg(pDM_Odm, ODM_RF_PATH_A, 0x8f, bRFRegOffsetMask);
		
		if (pDM_Odm->ExtPA)
			ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, 0x8f, bRFRegOffsetMask, 0xa8000);
		else
			ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, 0x8f, bRFRegOffsetMask, 0xae000);
	}
	/*enter IQK mode*/
	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x808000);

	/*path-A IQK setting*/
	ODM_SetBBReg(pDM_Odm, rTx_IQK_Tone_A, bMaskDWord, 0x18008c0c);
	ODM_SetBBReg(pDM_Odm, rRx_IQK_Tone_A, bMaskDWord, 0x38008c0c);
	ODM_SetBBReg(pDM_Odm, rTx_IQK_Tone_B, bMaskDWord, 0x38008c0c);
	ODM_SetBBReg(pDM_Odm, rRx_IQK_Tone_B, bMaskDWord, 0x38008c0c);
	ODM_SetBBReg(pDM_Odm, rTx_IQK_PI_A, bMaskDWord, 0x82160000);
	ODM_SetBBReg(pDM_Odm, rRx_IQK_PI_A, bMaskDWord, 0x28160000);
	ODM_SetBBReg(pDM_Odm, rTx_IQK, bMaskDWord, 0x01007c00);
	ODM_SetBBReg(pDM_Odm, rRx_IQK, bMaskDWord, 0x01004800);

	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] LO calibration setting!\n"));*/
	ODM_SetBBReg(pDM_Odm, rIQK_AGC_Rsp, bMaskDWord, 0x0046a911);

	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] One shot, path A LOK & IQK!\n"));*/
	ODM_SetBBReg(pDM_Odm, rIQK_AGC_Pts, bMaskDWord, 0xf9005800);
	ODM_SetBBReg(pDM_Odm, rIQK_AGC_Pts, bMaskDWord, 0xf8005800);

	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Delay %d ms for One shot, path A LOK & IQK.\n", IQK_DELAY_TIME_92E));*/
	ODM_delay_ms(IQK_DELAY_TIME_97F);


	/*Check failed*/
	regEAC = ODM_GetBBReg(pDM_Odm, rRx_Power_After_IQK_A_2, bMaskDWord);
	regE94 = ODM_GetBBReg(pDM_Odm, rTx_Power_Before_IQK_A, bMaskDWord);
	regE9C = ODM_GetBBReg(pDM_Odm, rTx_Power_After_IQK_A, bMaskDWord);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xeac = 0x%x\n", regEAC));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xe94 = 0x%x, 0xe9c = 0x%x\n", regE94, regE9C));
	/*monitor image power before & after IQK*/
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xe90(before IQK)= 0x%x, 0xe98(afer IQK) = 0x%x\n",
				 ODM_GetBBReg(pDM_Odm, 0xe90, bMaskDWord), ODM_GetBBReg(pDM_Odm, 0xe98, bMaskDWord)));

	if (pDM_Odm->CutVersion == ODM_CUT_A) {
	/*Restore RXPGA*/
	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x000000);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, 0x8f, bRFRegOffsetMask, RXPGA);
	}

	if (!(regEAC & BIT28) &&
		(((regE94 & 0x03FF0000) >> 16) != 0x142) &&
		(((regE9C & 0x03FF0000) >> 16) != 0x42))
		result |= 0x01;
	else {						/*if Tx not OK, ignore Rx*/
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Path A RXIQK step1 is not success\n"));


	return result;
	
	}

	u4tmp = 0x80007C00 | (regE94 & 0x3FF0000)  | ((regE9C & 0x3FF0000) >> 16);
	ODM_SetBBReg(pDM_Odm, rTx_IQK, bMaskDWord, u4tmp);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xe40 = 0x%x u4tmp = 0x%x\n", ODM_GetBBReg(pDM_Odm, rTx_IQK, bMaskDWord), u4tmp));


	/* =============================RXIQK setting=============================*/
	/*modify RXIQK mode table*/
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK]====================Path A RXIQK step2!====================\n"));
	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Path A RXIQK modify RXIQK mode table 2!\n"));*/
	/*leave IQK mode*/
	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x000000);

	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, RF_WE_LUT, 0x80000, 0x1);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, RF_RCK_OS, bRFRegOffsetMask, 0x38000);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, RF_TXPA_G1, bRFRegOffsetMask, 0x0005f);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, RF_TXPA_G2, bRFRegOffsetMask, 0xf1ff2);  /*PA off : default:0xf1ffa*/

	/*PA/PAD control by 0x56, and set = 0x0*/	
	if (pDM_Odm->CutVersion == ODM_CUT_A) {
		
		RXPGA = ODM_GetRFReg(pDM_Odm, ODM_RF_PATH_A, 0x8f, bRFRegOffsetMask);
		
		if (pDM_Odm->ExtPA) {
			ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, 0xdf, 0x00800, 0x1);
			ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, 0x56, 0x003e0, 0x3);
			ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, 0x8f, bRFRegOffsetMask, 0x28000);
		} else {
			ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, 0xdf, 0x00800, 0x1);
			ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, 0x56, 0x003e0, 0x0);
			ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, 0x8f, bRFRegOffsetMask, 0xae000);
		}
	} else {
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, 0xdf, 0x00800, 0x1);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, 0x56, 0x003e0, 0x3);
	}
	/*enter IQK mode*/
	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x808000);

	/*IQK setting*/
	ODM_SetBBReg(pDM_Odm, rRx_IQK, bMaskDWord, 0x01004800);

	/*path-A IQK setting*/
	ODM_SetBBReg(pDM_Odm, rTx_IQK_Tone_A, bMaskDWord, 0x38008c0c);
	ODM_SetBBReg(pDM_Odm, rRx_IQK_Tone_A, bMaskDWord, 0x18008c0c);
	ODM_SetBBReg(pDM_Odm, rTx_IQK_Tone_B, bMaskDWord, 0x38008c0c);
	ODM_SetBBReg(pDM_Odm, rRx_IQK_Tone_B, bMaskDWord, 0x38008c0c);
	ODM_SetBBReg(pDM_Odm, rTx_IQK_PI_A, bMaskDWord, 0x82170000);
	
	if (pDM_Odm->ExtPA == 1 && pDM_Odm->CutVersion == ODM_CUT_A)
		ODM_SetBBReg(pDM_Odm, rRx_IQK_PI_A, bMaskDWord, 0x28170c00);
	else
		ODM_SetBBReg(pDM_Odm, rRx_IQK_PI_A, bMaskDWord, 0x28170000);

	/*ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xe3c(RX_PI_Data)= 0x%x\n",
				 ODM_GetBBReg(pDM_Odm, 0xe3c, bMaskDWord)));*/


	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] LO calibration setting!\n"));*/
	ODM_SetBBReg(pDM_Odm, rIQK_AGC_Rsp, bMaskDWord, 0x0046a8d1);

	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] One shot, path A LOK & IQK!\n"));*/
	ODM_SetBBReg(pDM_Odm, rIQK_AGC_Pts, bMaskDWord, 0xf9005800);
	ODM_SetBBReg(pDM_Odm, rIQK_AGC_Pts, bMaskDWord, 0xf8005800);

	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Delay %d ms for One shot, path A LOK & IQK.\n", IQK_DELAY_TIME_92E));*/
	ODM_delay_ms(IQK_DELAY_TIME_97F);

	/*Check failed*/
	regEAC = ODM_GetBBReg(pDM_Odm, rRx_Power_After_IQK_A_2, bMaskDWord);
	regEA4 = ODM_GetBBReg(pDM_Odm, rRx_Power_Before_IQK_A_2, bMaskDWord);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xeac = 0x%x\n", regEAC));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xea4 = 0x%x, 0xeac = 0x%x\n", regEA4, regEAC));
	/*monitor image power before & after IQK*/
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xea0(before IQK)= 0x%x, 0xea8(afer IQK) = 0x%x\n",
				 ODM_GetBBReg(pDM_Odm, 0xea0, bMaskDWord), ODM_GetBBReg(pDM_Odm, 0xea8, bMaskDWord)));

	/*PA/PAD controlled by 0x0 & Restore RXPGA*/
	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x000000);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, 0xdf, 0x00800, 0x0);
	if (pDM_Odm->CutVersion == ODM_CUT_A)
		ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, 0x8f, bRFRegOffsetMask, RXPGA);

	if (!(regEAC & BIT27) &&	/*if Tx is OK, check whether Rx is OK*/
		(((regEA4 & 0x03FF0000) >> 16) != 0x132) &&
		(((regEAC & 0x03FF0000) >> 16) != 0x36))
		result |= 0x02;
	else
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Path A RxIQK step2 is not success!!\n"));
	return result;



}

u1Byte				/*bit0 = 1 => Tx OK, bit1 = 1 => Rx OK*/
phy_PathB_IQK_8197F(
#if (DM_ODM_SUPPORT_TYPE & ODM_AP)
	PVOID		pDM_VOID
#else
	PADAPTER	pAdapter
#endif
)
{
	PDM_ODM_T		pDM_Odm	= (PDM_ODM_T)pDM_VOID;

	u4Byte regEAC, regEB4, regEBC;
	u1Byte	result = 0x00;
	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(pAdapter);
	#if (DM_ODM_SUPPORT_TYPE == ODM_CE)
	PDM_ODM_T		pDM_Odm = &pHalData->odmpriv;
	#endif
	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)
	PDM_ODM_T		pDM_Odm = &pHalData->DM_OutSrc;
	#endif
	#endif
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] ====================Path B TXIQK start!====================\n"));

	/* =============================TXIQK setting=============================*/
	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x000000);
	/*modify TXIQK mode table*/
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, RF_WE_LUT, 0x80000, 0x1);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, RF_RCK_OS, bRFRegOffsetMask, 0x20000);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, RF_TXPA_G1, bRFRegOffsetMask, 0x0005f);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, RF_TXPA_G2, bRFRegOffsetMask, 0x01ff7); /*PA off, deafault:0xf1dfb*/

	/*path A to SI mode to avoid RF go to shot-down mode*/
	ODM_SetBBReg(pDM_Odm, 0x820, BIT8, 0x0);

	if (pDM_Odm->ExtPA) {
		ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, 0xdf, 0x00800, 0x1);
		ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, 0x56, 0x003ff, 0x71);	
	} else if (pDM_Odm->ExtPA == 0 && pDM_Odm->CutVersion != ODM_CUT_A) {	
		ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, 0xdf, 0x00800, 0x1);
		ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, 0x56, 0x003ff, 0xe8);
	}

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0x56 at Path B TXIQK = 0x%x\n",
				 ODM_GetRFReg(pDM_Odm, ODM_RF_PATH_B, 0x56, bRFRegOffsetMask)));

	/*enter IQK mode*/
	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x808000);
	ODM_SetBBReg(pDM_Odm, rTx_IQK_Tone_A, bMaskDWord, 0x38008c0c);
	ODM_SetBBReg(pDM_Odm, rRx_IQK_Tone_A, bMaskDWord, 0x38008c0c);
	ODM_SetBBReg(pDM_Odm, rTx_IQK_Tone_B, bMaskDWord, 0x18008c0c);
	ODM_SetBBReg(pDM_Odm, rRx_IQK_Tone_B, bMaskDWord, 0x38008c0c);

	if (pDM_Odm->CutVersion == ODM_CUT_A) { 
		if (pDM_Odm->ExtPA)
			ODM_SetBBReg(pDM_Odm, rTx_IQK_PI_B, bMaskDWord, 0x8214400f);
		else
			ODM_SetBBReg(pDM_Odm, rTx_IQK_PI_B, bMaskDWord, 0x82140002);
	} else
		ODM_SetBBReg(pDM_Odm, rTx_IQK_PI_B, bMaskDWord, 0x8214000f);

	ODM_SetBBReg(pDM_Odm, rRx_IQK_PI_B, bMaskDWord, 0x28140000);

	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] LO calibration setting!\n"));*/
	ODM_SetBBReg(pDM_Odm, rIQK_AGC_Rsp, bMaskDWord, 0x00862911);

	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] One shot, path B LOK & IQK!\n"));*/
	ODM_SetBBReg(pDM_Odm, rIQK_AGC_Pts, bMaskDWord, 0xfa005800);
	ODM_SetBBReg(pDM_Odm, rIQK_AGC_Pts, bMaskDWord, 0xf8005800);

	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Delay %d ms for One shot, path B LOK & IQK.\n", IQK_DELAY_TIME_97F));*/
	ODM_delay_ms(IQK_DELAY_TIME_97F);

	/*Check failed*/
	regEAC = ODM_GetBBReg(pDM_Odm, rRx_Power_After_IQK_A_2, bMaskDWord);
	regEB4 = ODM_GetBBReg(pDM_Odm, rTx_Power_Before_IQK_B, bMaskDWord);
	regEBC = ODM_GetBBReg(pDM_Odm, rTx_Power_After_IQK_B, bMaskDWord);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xeac = 0x%x\n", regEAC));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xeb4 = 0x%x, 0xebc = 0x%x\n", regEB4, regEBC));
	/*monitor image power before & after IQK*/
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xeb0(before IQK)= 0x%x, 0xeb8(afer IQK) = 0x%x\n",
				 ODM_GetBBReg(pDM_Odm, 0xeb0, bMaskDWord), ODM_GetBBReg(pDM_Odm, 0xeb8, bMaskDWord)));

	/*Path A back to PI mode*/
	ODM_SetBBReg(pDM_Odm, 0x820, BIT8, 0x1);

	/*reload 0xdf and CCK_IND off  */
	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x000000);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, 0x0, BIT14, 0x0);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, 0xdf, 0x00800, 0x0);

	if (!(regEAC & BIT31) &&
		(((regEB4 & 0x03FF0000) >> 16) != 0x142) &&
		(((regEBC & 0x03FF0000) >> 16) != 0x42))
		result |= 0x01;
	else 
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Path B TXIQK is not success\n"));
	return result;

}



u1Byte			/*bit0 = 1 => Tx OK, bit1 = 1 => Rx OK*/
phy_PathB_RxIQK_97F(
#if (DM_ODM_SUPPORT_TYPE & ODM_AP)
	PVOID		pDM_VOID,
#else
	PADAPTER	pAdapter,
#endif
	BOOLEAN		configPathB
)
{
	PDM_ODM_T		pDM_Odm	= (PDM_ODM_T)pDM_VOID;

	u4Byte regEAC, regEB4, regEBC, regECC, regEC4, u4tmp, RXPGA;
	u1Byte result = 0x00;
	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(pAdapter);
	#if (DM_ODM_SUPPORT_TYPE == ODM_CE)
	PDM_ODM_T		pDM_Odm = &pHalData->odmpriv;
	#endif
	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)
	PDM_ODM_T		pDM_Odm = &pHalData->DM_OutSrc;
	#endif
	#endif
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Path B RxIQK start!\n"));

	/* =============================Get TXIMR setting=============================*/
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] ====================Path B RXIQK step1!====================\n"));
	/*modify RXIQK mode table*/
	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Path B RXIQK modify RXIQK mode table!\n"));*/
	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x000000);

	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, RF_WE_LUT, 0x80000, 0x1);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, RF_RCK_OS, bRFRegOffsetMask, 0x30000);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, RF_TXPA_G1, bRFRegOffsetMask, 0x0005f);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, RF_TXPA_G2, bRFRegOffsetMask, 0xf1df3); /*PA off, deafault:0xf1dfb*/
	
	if (pDM_Odm->CutVersion == ODM_CUT_A) {
		RXPGA = ODM_GetRFReg(pDM_Odm, ODM_RF_PATH_B, 0x8f, bRFRegOffsetMask);
		
		if (pDM_Odm->ExtPA)
			ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, 0x8f, bRFRegOffsetMask, 0xa8000);
		else
			ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, 0x8f, bRFRegOffsetMask, 0xae000);
	}	

	/*path A to SI mode to avoid RF go to shot-down mode*/
	ODM_SetBBReg(pDM_Odm, 0x820, BIT8, 0x0);
	
	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x808000);

	/*path-B IQK setting*/
	ODM_SetBBReg(pDM_Odm, rTx_IQK_Tone_A, bMaskDWord, 0x38008c0c);
	ODM_SetBBReg(pDM_Odm, rRx_IQK_Tone_A, bMaskDWord, 0x38008c0c);
	ODM_SetBBReg(pDM_Odm, rTx_IQK_Tone_B, bMaskDWord, 0x18008c0c);
	ODM_SetBBReg(pDM_Odm, rRx_IQK_Tone_B, bMaskDWord, 0x38008c0c);
	ODM_SetBBReg(pDM_Odm, rTx_IQK_PI_B, bMaskDWord, 0x82160000);
	ODM_SetBBReg(pDM_Odm, rRx_IQK_PI_B, bMaskDWord, 0x28160000);
	ODM_SetBBReg(pDM_Odm, rTx_IQK, bMaskDWord, 0x01007c00);
	ODM_SetBBReg(pDM_Odm, rRx_IQK, bMaskDWord, 0x01004800);

	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] LO calibration setting!\n"));*/
	ODM_SetBBReg(pDM_Odm, rIQK_AGC_Rsp, bMaskDWord, 0x0046a911);

	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] One shot, Path B LOK & IQK!\n"));*/
	ODM_SetBBReg(pDM_Odm, rIQK_AGC_Pts, bMaskDWord, 0xfa005800);
	ODM_SetBBReg(pDM_Odm, rIQK_AGC_Pts, bMaskDWord, 0xf8005800);

	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK]Delay %d ms for One shot, path B LOK & IQK.\n", IQK_DELAY_TIME_97F));*/
	ODM_delay_ms(IQK_DELAY_TIME_97F);

	/*Check failed*/
	regEAC = ODM_GetBBReg(pDM_Odm, rRx_Power_After_IQK_A_2, bMaskDWord);
	regEB4 = ODM_GetBBReg(pDM_Odm, rTx_Power_Before_IQK_B, bMaskDWord);
	regEBC = ODM_GetBBReg(pDM_Odm, rTx_Power_After_IQK_B, bMaskDWord);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xeac = 0x%x\n", regEAC));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xeb4 = 0x%x, 0xebc = 0x%x\n", regEB4, regEBC));
	/*monitor image power before & after IQK*/
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xeb0(before IQK)= 0x%x, 0xeb8(afer IQK) = 0x%x\n",
				 ODM_GetBBReg(pDM_Odm, 0xeb0, bMaskDWord), ODM_GetBBReg(pDM_Odm, 0xeb8, bMaskDWord)));

	if (pDM_Odm->CutVersion == ODM_CUT_A) {
	/*Restore RXPGA*/
	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x000000);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, 0x8f, bRFRegOffsetMask, RXPGA);
	}
	
	/*Path A back to PI mode*/
	ODM_SetBBReg(pDM_Odm, 0x820, BIT8, 0x1);


	if (!(regEAC & BIT31) &&
		(((regEB4 & 0x03FF0000) >> 16) != 0x142) &&
		(((regEBC & 0x03FF0000) >> 16) != 0x42))
		result |= 0x01;
	else {						/*if Tx not OK, ignore Rx*/
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Path B RXIQK step1 is not success\n"));
		return result;
		
	}

	u4tmp = 0x80007C00 | (regEB4 & 0x3FF0000)  | ((regEBC & 0x3FF0000) >> 16);
	ODM_SetBBReg(pDM_Odm, rTx_IQK, bMaskDWord, u4tmp);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("0xe40 = 0x%x u4tmp = 0x%x\n", ODM_GetBBReg(pDM_Odm, rTx_IQK, bMaskDWord), u4tmp));


	/* =============================RXIQK setting=============================*/
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] ====================Path B RXIQK step2!====================\n"));

	/*modify RXIQK mode table*/
	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path-B RXIQK modify RXIQK mode table 2!\n"));*/
	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x000000);

	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, RF_WE_LUT, 0x80000, 0x1);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, RF_RCK_OS, bRFRegOffsetMask, 0x38000);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, RF_TXPA_G1, bRFRegOffsetMask, 0x0005f);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, RF_TXPA_G2, bRFRegOffsetMask, 0xf1ff2);  /*PA off : default:0xf1ffa*/

	/*PA/PAD control by 0x56, and set = 0x0*/	
	if (pDM_Odm->CutVersion == ODM_CUT_A) {
		
		RXPGA = ODM_GetRFReg(pDM_Odm, ODM_RF_PATH_B, 0x8f, bRFRegOffsetMask);
		
		if (pDM_Odm->ExtPA) {
			ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, 0xdf, 0x00800, 0x1);
			ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, 0x56, 0x003e0, 0x3);
			ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, 0x8f, bRFRegOffsetMask, 0x28000);
		} else {
			ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, 0xdf, 0x00800, 0x1);
			ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, 0x56, 0x003e0, 0x0);
			ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, 0x8f, bRFRegOffsetMask, 0xae000);
		}
	} else {
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, 0xdf, 0x00800, 0x1);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, 0x56, 0x003e0, 0x3);
	}

	/*path A to SI mode to avoid RF go to shot-down mode*/
	ODM_SetBBReg(pDM_Odm, 0x820, BIT8, 0x0);

	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x808000);

	/*IQK setting*/
	ODM_SetBBReg(pDM_Odm, rRx_IQK, bMaskDWord, 0x01004800);

	/*path-B IQK setting*/
	ODM_SetBBReg(pDM_Odm, rTx_IQK_Tone_A, bMaskDWord, 0x38008c0c);
	ODM_SetBBReg(pDM_Odm, rRx_IQK_Tone_A, bMaskDWord, 0x38008c0c);
	ODM_SetBBReg(pDM_Odm, rTx_IQK_Tone_B, bMaskDWord, 0x38008c0c);
	ODM_SetBBReg(pDM_Odm, rRx_IQK_Tone_B, bMaskDWord, 0x18008c0c);
	ODM_SetBBReg(pDM_Odm, rTx_IQK_PI_B, bMaskDWord, 0x82170000);

	if (pDM_Odm->ExtPA == 1 && pDM_Odm->CutVersion == ODM_CUT_A)
		ODM_SetBBReg(pDM_Odm, rRx_IQK_PI_B, bMaskDWord, 0x28170c00);
	else
		ODM_SetBBReg(pDM_Odm, rRx_IQK_PI_B, bMaskDWord, 0x28170000);

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xe5c(RX_PI_Data)= 0x%x\n",
				 ODM_GetBBReg(pDM_Odm, 0xe5c, bMaskDWord)));

	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("LO calibration setting!\n"));*/
	ODM_SetBBReg(pDM_Odm, rIQK_AGC_Rsp, bMaskDWord, 0x0046a8d1);

	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("One shot, path B LOK & IQK!\n"));*/
	ODM_SetBBReg(pDM_Odm, rIQK_AGC_Pts, bMaskDWord, 0xfa005800);
	ODM_SetBBReg(pDM_Odm, rIQK_AGC_Pts, bMaskDWord, 0xf8005800);

	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Delay %d ms for One shot, Path B LOK & IQK.\n", IQK_DELAY_TIME_97F));*/
	ODM_delay_ms(IQK_DELAY_TIME_97F);


	/*Check failed*/
	regEAC = ODM_GetBBReg(pDM_Odm, rRx_Power_After_IQK_A_2, bMaskDWord);
	regEC4 = ODM_GetBBReg(pDM_Odm, rRx_Power_Before_IQK_B_2, bMaskDWord);
	regECC = ODM_GetBBReg(pDM_Odm, rRx_Power_After_IQK_B_2, bMaskDWord);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xeac = 0x%x\n", regEAC));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xec4 = 0x%x, 0xecc = 0x%x\n", regEC4, regECC));
	/*monitor image power before & after IQK*/
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xec0(before IQK)= 0x%x, 0xec8(afer IQK) = 0x%x\n",
				 ODM_GetBBReg(pDM_Odm, 0xec0, bMaskDWord), ODM_GetBBReg(pDM_Odm, 0xec8, bMaskDWord)));

	/*PA/PAD controlled by 0x0 & Restore RXPGA*/
	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x000000);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, 0xdf, 0x00800, 0x0);
	if (pDM_Odm->CutVersion == ODM_CUT_A)
		ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, 0x8f, bRFRegOffsetMask, RXPGA);	

	/*Path A back to PI mode*/
	ODM_SetBBReg(pDM_Odm, 0x820, BIT8, 0x1);

	if (!(regEAC & BIT30) &&/*if Tx is OK, check whether Rx is OK*/
		(((regEC4 & 0x03FF0000) >> 16) != 0x132) &&
		(((regECC & 0x03FF0000) >> 16) != 0x36))
		result |= 0x02;
	else
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Path B RXIQK step2 is not success!!\n"));
	return result;


}

VOID
_PHY_PathAFillIQKMatrix_97F(
#if (DM_ODM_SUPPORT_TYPE & ODM_AP)
	PVOID		pDM_VOID,
#else
	PADAPTER	pAdapter,
#endif
	BOOLEAN		bIQKOK,
	s4Byte		result[][8],
	u1Byte		final_candidate,
	BOOLEAN		bTxOnly
)
{
	PDM_ODM_T		pDM_Odm	= (PDM_ODM_T)pDM_VOID;

	u4Byte	Oldval_0, X, TX0_A, reg;
	s4Byte	Y, TX0_C;
	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(pAdapter);
	#if (DM_ODM_SUPPORT_TYPE == ODM_CE)
	PDM_ODM_T		pDM_Odm = &pHalData->odmpriv;
	#endif
	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)
	PDM_ODM_T		pDM_Odm = &pHalData->DM_OutSrc;
	#endif
	#endif
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Path A IQ Calibration %s !\n", (bIQKOK) ? "Success" : "Failed"));

	if (final_candidate == 0xFF)
		return;

	else if (bIQKOK) {
		Oldval_0 = (ODM_GetBBReg(pDM_Odm, rOFDM0_XATxIQImbalance, bMaskDWord) >> 22) & 0x3FF;

		X = result[final_candidate][0];
		if ((X & 0x00000200) != 0)
			X = X | 0xFFFFFC00;
		TX0_A = (X * Oldval_0) >> 8;
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] X = 0x%x, TX0_A = 0x%x, Oldval_0 0x%x\n", X, TX0_A, Oldval_0));
		ODM_SetBBReg(pDM_Odm, rOFDM0_XATxIQImbalance, 0x3FF, TX0_A);

		ODM_SetBBReg(pDM_Odm, rOFDM0_ECCAThreshold, BIT(31), ((X * Oldval_0 >> 7) & 0x1));

		Y = result[final_candidate][1];
		if ((Y & 0x00000200) != 0)
			Y = Y | 0xFFFFFC00;


		TX0_C = (Y * Oldval_0) >> 8;
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Y = 0x%x, TX0_C = 0x%x\n", Y, TX0_C));
		ODM_SetBBReg(pDM_Odm, rOFDM0_XCTxAFE, 0xF0000000, ((TX0_C & 0x3C0) >> 6));
		ODM_SetBBReg(pDM_Odm, rOFDM0_XATxIQImbalance, 0x003F0000, (TX0_C & 0x3F));

		ODM_SetBBReg(pDM_Odm, rOFDM0_ECCAThreshold, BIT(29), ((Y * Oldval_0 >> 7) & 0x1));

		if (bTxOnly) {
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] _PHY_PathAFillIQKMatrix_97F only Tx OK\n"));
			return;
		}

		reg = result[final_candidate][2];
		#if (DM_ODM_SUPPORT_TYPE == ODM_AP)
		if (RTL_ABS(reg , 0x100) >= 16)
			reg = 0x100;
		#endif
		ODM_SetBBReg(pDM_Odm, rOFDM0_XARxIQImbalance, 0x3FF, reg);

		reg = result[final_candidate][3] & 0x3F;
		ODM_SetBBReg(pDM_Odm, rOFDM0_XARxIQImbalance, 0xFC00, reg);

		reg = (result[final_candidate][3] >> 6) & 0xF;
		ODM_SetBBReg(pDM_Odm, rOFDM0_RxIQExtAnta, 0xF0000000, reg);
	}
}

VOID
_PHY_PathBFillIQKMatrix_97F(
#if (DM_ODM_SUPPORT_TYPE & ODM_AP)
	PVOID		pDM_VOID,
#else
	PADAPTER	pAdapter,
#endif
	BOOLEAN		bIQKOK,
	s4Byte		result[][8],
	u1Byte		final_candidate,
	BOOLEAN		bTxOnly			/*do Tx only*/
)
{
	PDM_ODM_T		pDM_Odm	= (PDM_ODM_T)pDM_VOID;

	u4Byte	Oldval_1, X, TX1_A, reg;
	s4Byte	Y, TX1_C;
	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(pAdapter);
	#if (DM_ODM_SUPPORT_TYPE == ODM_CE)
	PDM_ODM_T		pDM_Odm = &pHalData->odmpriv;
	#endif
	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)
	PDM_ODM_T		pDM_Odm = &pHalData->DM_OutSrc;
	#endif
	#endif
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Path B IQ Calibration %s !\n", (bIQKOK) ? "Success" : "Failed"));

	if (final_candidate == 0xFF)
		return;

	else if (bIQKOK) {
		Oldval_1 = (ODM_GetBBReg(pDM_Odm, rOFDM0_XBTxIQImbalance, bMaskDWord) >> 22) & 0x3FF;

		X = result[final_candidate][4];
		if ((X & 0x00000200) != 0)
			X = X | 0xFFFFFC00;
		TX1_A = (X * Oldval_1) >> 8;
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] X = 0x%x, TX1_A = 0x%x\n", X, TX1_A));
		ODM_SetBBReg(pDM_Odm, rOFDM0_XBTxIQImbalance, 0x3FF, TX1_A);

		ODM_SetBBReg(pDM_Odm, rOFDM0_ECCAThreshold, BIT(27), ((X * Oldval_1 >> 7) & 0x1));

		Y = result[final_candidate][5];
		if ((Y & 0x00000200) != 0)
			Y = Y | 0xFFFFFC00;

		TX1_C = (Y * Oldval_1) >> 8;
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Y = 0x%x, TX1_C = 0x%x\n", Y, TX1_C));
		ODM_SetBBReg(pDM_Odm, rOFDM0_XDTxAFE, 0xF0000000, ((TX1_C & 0x3C0) >> 6));
		ODM_SetBBReg(pDM_Odm, rOFDM0_XBTxIQImbalance, 0x003F0000, (TX1_C & 0x3F));

		ODM_SetBBReg(pDM_Odm, rOFDM0_ECCAThreshold, BIT(25), ((Y * Oldval_1 >> 7) & 0x1));

		if (bTxOnly)
			return;

		reg = result[final_candidate][6];
		ODM_SetBBReg(pDM_Odm, rOFDM0_XBRxIQImbalance, 0x3FF, reg);

		reg = result[final_candidate][7] & 0x3F;
		ODM_SetBBReg(pDM_Odm, rOFDM0_XBRxIQImbalance, 0xFC00, reg);

		reg = (result[final_candidate][7] >> 6) & 0xF;
		ODM_SetBBReg(pDM_Odm, 0xca8, 0x000000F0, reg);
	}
}

#if (DM_ODM_SUPPORT_TYPE & ODM_CE)
BOOLEAN
ODM_CheckPowerStatus(
	IN	PADAPTER		Adapter)
{
#if 0
	HAL_DATA_TYPE		*pHalData = GET_HAL_DATA(Adapter);
	PDM_ODM_T			pDM_Odm = &pHalData->DM_OutSrc;
	RT_RF_POWER_STATE	rtState;
	PMGNT_INFO			pMgntInfo	= &(Adapter->MgntInfo);

	/* 2011/07/27 MH We are not testing ready~~!! We may fail to get correct value when init sequence.*/
	if (pMgntInfo->init_adpt_in_progress == TRUE) {
		ODM_RT_TRACE(pDM_Odm, COMP_INIT, DBG_LOUD, ("ODM_CheckPowerStatus Return TRUE, due to initadapter"));
		return	TRUE;
	}


	Adapter->HalFunc.GetHwRegHandler(Adapter, HW_VAR_RF_STATE, (pu1Byte)(&rtState));
	if (Adapter->bDriverStopped || Adapter->bDriverIsGoingToPnpSetPowerSleep || rtState == eRfOff) {
		ODM_RT_TRACE(pDM_Odm, COMP_INIT, DBG_LOUD, ("ODM_CheckPowerStatus Return FALSE, due to %d/%d/%d\n",
		Adapter->bDriverStopped, Adapter->bDriverIsGoingToPnpSetPowerSleep, rtState));
		return	FALSE;
	}
#endif
	return	TRUE;
}
#endif


VOID
_PHY_SaveADDARegisters_97F(
#if (DM_ODM_SUPPORT_TYPE & ODM_AP)
	PVOID		pDM_VOID,
#else
	PADAPTER	pAdapter,
#endif
	pu4Byte		ADDAReg,
	pu4Byte		ADDABackup,
	u4Byte		RegisterNum
)
{
	PDM_ODM_T		pDM_Odm	= (PDM_ODM_T)pDM_VOID;

	u4Byte	i;
	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(pAdapter);
	#if (DM_ODM_SUPPORT_TYPE == ODM_CE)
	PDM_ODM_T		pDM_Odm = &pHalData->odmpriv;
	#endif
	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)
	PDM_ODM_T		pDM_Odm = &pHalData->DM_OutSrc;
	#endif

	if (ODM_CheckPowerStatus(pAdapter) == FALSE)
		return;
	#endif

	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Save ADDA parameters.\n"));*/
	for (i = 0 ; i < RegisterNum ; i++)
		ADDABackup[i] = ODM_GetBBReg(pDM_Odm, ADDAReg[i], bMaskDWord);
}


VOID
_PHY_SaveMACRegisters_97F(
#if (DM_ODM_SUPPORT_TYPE & ODM_AP)
	PVOID		pDM_VOID,
#else
	PADAPTER	pAdapter,
#endif
	pu4Byte		MACReg,
	pu4Byte		MACBackup
)
{
	PDM_ODM_T		pDM_Odm	= (PDM_ODM_T)pDM_VOID;

	u4Byte	i;
	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(pAdapter);
	#if (DM_ODM_SUPPORT_TYPE == ODM_CE)
	PDM_ODM_T		pDM_Odm = &pHalData->odmpriv;
	#endif
	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)
	PDM_ODM_T		pDM_Odm = &pHalData->DM_OutSrc;
	#endif
	#endif
	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Save MAC parameters.\n"));*/
	for (i = 0 ; i < (IQK_MAC_REG_NUM - 1); i++)
		MACBackup[i] = ODM_Read1Byte(pDM_Odm, MACReg[i]);
	MACBackup[i] = ODM_Read4Byte(pDM_Odm, MACReg[i]);

}


VOID
_PHY_ReloadADDARegisters_97F(
#if (DM_ODM_SUPPORT_TYPE & ODM_AP)
	PVOID		pDM_VOID,
#else
	PADAPTER	pAdapter,
#endif
	pu4Byte		ADDAReg,
	pu4Byte		ADDABackup,
	u4Byte		RegiesterNum
)
{
	PDM_ODM_T		pDM_Odm	= (PDM_ODM_T)pDM_VOID;

	u4Byte	i;
	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(pAdapter);
	#if (DM_ODM_SUPPORT_TYPE == ODM_CE)
	PDM_ODM_T		pDM_Odm = &pHalData->odmpriv;
	#endif
	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)
	PDM_ODM_T		pDM_Odm = &pHalData->DM_OutSrc;
	#endif
	#endif

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Reload ADDA power saving parameters !\n"));
	for (i = 0 ; i < RegiesterNum; i++)
		ODM_SetBBReg(pDM_Odm, ADDAReg[i], bMaskDWord, ADDABackup[i]);
}

VOID
_PHY_ReloadMACRegisters_97F(
#if (DM_ODM_SUPPORT_TYPE & ODM_AP)
	PVOID		pDM_VOID,
#else
	PADAPTER	pAdapter,
#endif
	pu4Byte		MACReg,
	pu4Byte		MACBackup
)
{
	PDM_ODM_T		pDM_Odm	= (PDM_ODM_T)pDM_VOID;

	u4Byte	i;
	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(pAdapter);
	#if (DM_ODM_SUPPORT_TYPE == ODM_CE)
	PDM_ODM_T		pDM_Odm = &pHalData->odmpriv;
	#endif
	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)
	PDM_ODM_T		pDM_Odm = &pHalData->DM_OutSrc;
	#endif
	#endif
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Reload MAC parameters !\n"));
	#if 0
	ODM_SetBBReg(pDM_Odm, 0x520, bMaskByte2, 0x0);
	#else
	for (i = 0 ; i < (IQK_MAC_REG_NUM - 1); i++)
		ODM_Write1Byte(pDM_Odm, MACReg[i], (u1Byte)MACBackup[i]);
	ODM_Write4Byte(pDM_Odm, MACReg[i], MACBackup[i]);
	#endif
}

VOID
_PHY_PathADDAOn_97F(
#if (DM_ODM_SUPPORT_TYPE & ODM_AP)
	PVOID		pDM_VOID,
#else
	PADAPTER	pAdapter,
#endif
	pu4Byte		ADDAReg,
	BOOLEAN		isPathAOn,
	BOOLEAN		is2T
)
{
	PDM_ODM_T		pDM_Odm	= (PDM_ODM_T)pDM_VOID;

	u4Byte	pathOn;
	u4Byte	i;
	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(pAdapter);
	#if (DM_ODM_SUPPORT_TYPE == ODM_CE)
	PDM_ODM_T		pDM_Odm = &pHalData->odmpriv;
	#endif
	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)
	PDM_ODM_T		pDM_Odm = &pHalData->DM_OutSrc;
	#endif
	#endif
	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] ADDA ON.\n"));*/

	ODM_SetBBReg(pDM_Odm, 0xd94, 0x00ff0000, 0xff);	
	ODM_SetBBReg(pDM_Odm, 0xe70, bMaskDWord, 0x00400040);
	
#if 0
	pathOn = isPathAOn ? 0x0fc01616 : 0x0fc01616;
	if (FALSE == is2T) {
		pathOn = 0x0fc01616;
		ODM_SetBBReg(pDM_Odm, ADDAReg[0], bMaskDWord, 0x0fc01616);
	} else
		ODM_SetBBReg(pDM_Odm, ADDAReg[0], bMaskDWord, pathOn);

	for (i = 1 ; i < IQK_ADDA_REG_NUM ; i++)
		ODM_SetBBReg(pDM_Odm, ADDAReg[i], bMaskDWord, pathOn);
#endif
}

VOID
_PHY_MACSettingCalibration_97F(
#if (DM_ODM_SUPPORT_TYPE & ODM_AP)
	PVOID		pDM_VOID,
#else
	PADAPTER	pAdapter,
#endif
	pu4Byte		MACReg,
	pu4Byte		MACBackup
)
{
	PDM_ODM_T		pDM_Odm	= (PDM_ODM_T)pDM_VOID;

	/*u4Byte	i = 0;*/
	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(pAdapter);
	#if (DM_ODM_SUPPORT_TYPE == ODM_CE)
	PDM_ODM_T		pDM_Odm = &pHalData->odmpriv;
	#endif
	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)
	PDM_ODM_T		pDM_Odm = &pHalData->DM_OutSrc;
	#endif
	#endif
/*	ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("MAC settings for Calibration.\n"));*/

#if 0
	ODM_Write1Byte(pDM_Odm, MACReg[i], 0x3F);

	for (i = 1 ; i < (IQK_MAC_REG_NUM - 1); i++)
		ODM_Write1Byte(pDM_Odm, MACReg[i], (u1Byte)(MACBackup[i] & (~BIT3)));

	ODM_Write1Byte(pDM_Odm, MACReg[i], (u1Byte)(MACBackup[i] & (~BIT5)));
#endif

	#if 1
	ODM_SetBBReg(pDM_Odm, 0x520, bMaskByte2, 0xff);
	#else
	ODM_SetBBReg(pDM_Odm, 0x522, bMaskByte0, 0x7f);
	ODM_SetBBReg(pDM_Odm, 0x550, bMaskByte0, 0x15);
	ODM_SetBBReg(pDM_Odm, 0x551, bMaskByte0, 0x00);
	#endif


}

VOID
_PHY_PathAStandBy_97F(
#if (DM_ODM_SUPPORT_TYPE & ODM_AP)
	PVOID		pDM_VOID
#else
	PADAPTER	pAdapter
#endif
)
{
	PDM_ODM_T		pDM_Odm	= (PDM_ODM_T)pDM_VOID;

	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(pAdapter);
	#if (DM_ODM_SUPPORT_TYPE == ODM_CE)
	PDM_ODM_T		pDM_Odm = &pHalData->odmpriv;
	#endif
	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)
	PDM_ODM_T		pDM_Odm = &pHalData->DM_OutSrc;
	#endif
	#endif
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Path-A standby mode!\n"));

	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x0);
	/*ODM_SetBBReg(pDM_Odm, 0x840, bMaskDWord, 0x00010000);*/
	ODM_SetRFReg(pDM_Odm, 0x0, 0x0, bRFRegOffsetMask, 0x10000);
	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x808000);
}

VOID
_PHY_PathBStandBy_97F(
#if (DM_ODM_SUPPORT_TYPE & ODM_AP)
	PVOID		pDM_VOID
#else
	PADAPTER	pAdapter
#endif
)
{
	PDM_ODM_T		pDM_Odm	= (PDM_ODM_T)pDM_VOID;

	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(pAdapter);
	#if (DM_ODM_SUPPORT_TYPE == ODM_CE)
	PDM_ODM_T		pDM_Odm = &pHalData->odmpriv;
	#endif
	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)
	PDM_ODM_T		pDM_Odm = &pHalData->DM_OutSrc;
	#endif
	#endif
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Path-B standby mode!\n"));

	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x000000);
	ODM_SetRFReg(pDM_Odm, 0x1, 0x0, bRFRegOffsetMask, 0x10000);

	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x808000);
}


VOID
_PHY_PIModeSwitch_97F(
#if (DM_ODM_SUPPORT_TYPE & ODM_AP)
	PVOID		pDM_VOID,
#else
	PADAPTER	pAdapter,
#endif
	BOOLEAN		PIMode
)
{
	PDM_ODM_T		pDM_Odm	= (PDM_ODM_T)pDM_VOID;

	u4Byte	mode;
	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(pAdapter);
	#if (DM_ODM_SUPPORT_TYPE == ODM_CE)
	PDM_ODM_T		pDM_Odm = &pHalData->odmpriv;
	#endif
	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)
	PDM_ODM_T		pDM_Odm = &pHalData->DM_OutSrc;
	#endif
	#endif
	/*DM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] BB Switch to %s mode!\n", (PIMode ? "PI" : "SI")));*/

	mode = PIMode ? 0x01000100 : 0x01000000;
	ODM_SetBBReg(pDM_Odm, rFPGA0_XA_HSSIParameter1, bMaskDWord, mode);
	ODM_SetBBReg(pDM_Odm, rFPGA0_XB_HSSIParameter1, bMaskDWord, mode);
}

BOOLEAN
phy_SimularityCompare_8197F(
#if (DM_ODM_SUPPORT_TYPE & ODM_AP)
	PVOID		pDM_VOID,
#else
	PADAPTER	pAdapter,
#endif
	s4Byte		result[][8],
	u1Byte		 c1,
	u1Byte		 c2
)
{
	PDM_ODM_T		pDM_Odm	= (PDM_ODM_T)pDM_VOID;

	u4Byte		i, j, diff, SimularityBitMap, bound = 0;
	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(pAdapter);
	#if (DM_ODM_SUPPORT_TYPE == ODM_CE)
	PDM_ODM_T		pDM_Odm = &pHalData->odmpriv;
	#endif
	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)
	PDM_ODM_T		pDM_Odm = &pHalData->DM_OutSrc;
	#endif
	#endif
	u1Byte		final_candidate[2] = {0xFF, 0xFF};	/*for path A and path B*/
	BOOLEAN		bResult = TRUE;
/*#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)*/
/*	BOOLEAN		is2T = IS_92C_SERIAL( pHalData->VersionID);*/
/*#else*/
	BOOLEAN		is2T = TRUE;
/*#endif*/

	s4Byte tmp1 = 0, tmp2 = 0;

	if (is2T)
		bound = 8;
	else
		bound = 4;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] ===> IQK:phy_SimularityCompare_8197F c1 %d c2 %d!!!\n", c1, c2));


	SimularityBitMap = 0;

	for (i = 0; i < bound; i++) {

		if ((i == 1) || (i == 3) || (i == 5) || (i == 7)) {
			if ((result[c1][i] & 0x00000200) != 0)
				tmp1 = result[c1][i] | 0xFFFFFC00;
			else
				tmp1 = result[c1][i];

			if ((result[c2][i] & 0x00000200) != 0)
				tmp2 = result[c2][i] | 0xFFFFFC00;
			else
				tmp2 = result[c2][i];
		} else {
			tmp1 = result[c1][i];
			tmp2 = result[c2][i];
		}

		diff = (tmp1 > tmp2) ? (tmp1 - tmp2) : (tmp2 - tmp1);

		if (diff > MAX_TOLERANCE) {
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] differnece overflow %d index %d compare1 0x%x compare2 0x%x!!!\n",  diff, i, result[c1][i], result[c2][i]));

			if ((i == 2 || i == 6) && !SimularityBitMap) {
				if (result[c1][i] + result[c1][i + 1] == 0)
					final_candidate[(i / 4)] = c2;
				else if (result[c2][i] + result[c2][i + 1] == 0)
					final_candidate[(i / 4)] = c1;
				else
					SimularityBitMap = SimularityBitMap | (1 << i);
			} else
				SimularityBitMap = SimularityBitMap | (1 << i);
		}
	}

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] phy_SimularityCompare_8197F SimularityBitMap   %x !!!\n", SimularityBitMap));

	if (SimularityBitMap == 0) {
		for (i = 0; i < (bound / 4); i++) {
			if (final_candidate[i] != 0xFF) {
				for (j = i * 4; j < (i + 1) * 4 - 2; j++)
					result[3][j] = result[final_candidate[i]][j];
				bResult = FALSE;
			}
		}
		return bResult;

	} else {

		if (!(SimularityBitMap & 0x03)) {		/*path A TX OK*/
			for (i = 0; i < 2; i++)
				result[3][i] = result[c1][i];
		}

		if (!(SimularityBitMap & 0x0c)) {		/*path A RX OK*/
			for (i = 2; i < 4; i++)
				result[3][i] = result[c1][i];
		}

		if (!(SimularityBitMap & 0x30)) {	/*path B TX OK*/
			for (i = 4; i < 6; i++)
				result[3][i] = result[c1][i];

		}

		if (!(SimularityBitMap & 0xc0)) {	/*path B RX OK*/
			for (i = 6; i < 8; i++)
				result[3][i] = result[c1][i];
		}

		return FALSE;
	}

}

VOID
phy_IQCalibrate_8197F(
#if (DM_ODM_SUPPORT_TYPE & ODM_AP)
	PVOID		pDM_VOID,
#else
	PADAPTER	pAdapter,
#endif
	s4Byte		result[][8],
	u1Byte		t,
	BOOLEAN		is2T
)
{
	PDM_ODM_T		pDM_Odm	= (PDM_ODM_T)pDM_VOID;

	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(pAdapter);
	#if (DM_ODM_SUPPORT_TYPE == ODM_CE)
	PDM_ODM_T		pDM_Odm = &pHalData->odmpriv;
	#endif
	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)
	PDM_ODM_T		pDM_Odm = &pHalData->DM_OutSrc;
	#endif
	#endif
	u4Byte			i;
	u1Byte			PathAOK = 0, PathBOK = 0;
	u1Byte			tmp0xc50 = (u1Byte)ODM_GetBBReg(pDM_Odm, 0xC50, bMaskByte0);
	u1Byte			tmp0xc58 = (u1Byte)ODM_GetBBReg(pDM_Odm, 0xC58, bMaskByte0);
	u4Byte			ADDA_REG[IQK_ADDA_REG_NUM] = {
		0xd94, rRx_Wait_CCA		
	};
	u4Byte			IQK_MAC_REG[IQK_MAC_REG_NUM] = {
		REG_TXPAUSE,	REG_BCN_CTRL,
		REG_BCN_CTRL_1,	REG_GPIO_MUXCFG
	};

	/*since 92C & 92D have the different define in IQK_BB_REG*/
	u4Byte	IQK_BB_REG_92C[IQK_BB_REG_NUM] = {
		rOFDM0_TRxPathEnable,	rOFDM0_TRMuxPar,
		rFPGA0_XCD_RFInterfaceSW,	rConfig_AntA,	rConfig_AntB,
		0x930,	0x934,
		0x93c,	rCCK0_AFESetting
	};

	#if (DM_ODM_SUPPORT_TYPE & (ODM_AP|ODM_ADSL))
	u4Byte	retryCount = 2;
	#else
	#if MP_DRIVER
	const u4Byte	retryCount = 9;
	#else
	const u4Byte	retryCount = 2;
	#endif
	#endif

	/*Note: IQ calibration must be performed after loading*/
	/*PHY_REG.txt,and radio_a,radio_b.txt*/

	/*u4Byte bbvalue;*/

	#if (DM_ODM_SUPPORT_TYPE & ODM_AP)
	#ifdef MP_TEST
	if (pDM_Odm->priv->pshare->rf_ft_var.mp_specific)
		retryCount = 2;
	#endif
	#endif


	if (t == 0) {
		/*bbvalue = ODM_GetBBReg(pDM_Odm, rFPGA0_RFMOD, bMaskDWord);*/
		/*RT_DISP(FINIT, INIT_IQK, ("phy_IQCalibrate_8188E()==>0x%08x\n",bbvalue));*/
		/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("IQ Calibration for %s for %d times\n", (is2T ? "2T2R" : "1T1R"), t));*/

		/*Save ADDA parameters, turn Path A ADDA on*/
		#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
		_PHY_SaveADDARegisters_97F(pAdapter, ADDA_REG, pDM_Odm->RFCalibrateInfo.ADDA_backup, IQK_ADDA_REG_NUM);
		_PHY_SaveMACRegisters_97F(pAdapter, IQK_MAC_REG, pDM_Odm->RFCalibrateInfo.IQK_MAC_backup);
		_PHY_SaveADDARegisters_97F(pAdapter, IQK_BB_REG_92C, pDM_Odm->RFCalibrateInfo.IQK_BB_backup, IQK_BB_REG_NUM);
		#else
		_PHY_SaveADDARegisters_97F(pDM_Odm, ADDA_REG, pDM_Odm->RFCalibrateInfo.ADDA_backup, IQK_ADDA_REG_NUM);
		_PHY_SaveMACRegisters_97F(pDM_Odm, IQK_MAC_REG, pDM_Odm->RFCalibrateInfo.IQK_MAC_backup);
		_PHY_SaveADDARegisters_97F(pDM_Odm, IQK_BB_REG_92C, pDM_Odm->RFCalibrateInfo.IQK_BB_backup, IQK_BB_REG_NUM);
		#endif
	}
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] IQ Calibration for %s for %d times\n", (is2T ? "2T2R" : "1T1R"), t));

	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)

	_PHY_PathADDAOn_97F(pAdapter, ADDA_REG, TRUE, is2T);
	#else
	_PHY_PathADDAOn_97F(pDM_Odm, ADDA_REG, TRUE, is2T);
	#endif


	/*BB setting*/
	/*ODM_SetBBReg(pDM_Odm, rFPGA0_RFMOD, BIT24, 0x00);*/
	ODM_SetBBReg(pDM_Odm, rCCK0_AFESetting, 0x0f000000, 0xf);
	ODM_SetBBReg(pDM_Odm, rOFDM0_TRxPathEnable, bMaskDWord, 0x6f005403);
	ODM_SetBBReg(pDM_Odm, rOFDM0_TRMuxPar, bMaskDWord, 0x000804e4);
	ODM_SetBBReg(pDM_Odm, rFPGA0_XCD_RFInterfaceSW, bMaskDWord, 0x04203400);

	/*RF setting :RXBB leave power saving*/
	if (pDM_Odm->CutVersion != ODM_CUT_A) {
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, 0xdf, 0x00002, 0x1);
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, 0xdf, 0x00002, 0x1);
	}
	
#if 1
	/*FEM off when ExtPA or ExtLNA= 1*/
	if (pDM_Odm->ExtPA || pDM_Odm->ExtLNA) {
		ODM_SetBBReg(pDM_Odm, 0x930, bMaskDWord, 0xFFFF77FF);
		ODM_SetBBReg(pDM_Odm, 0x934, bMaskDWord, 0xFFFFFFF7);
		ODM_SetBBReg(pDM_Odm, 0x93c, bMaskDWord, 0xFFFF777F);
	} 	
#endif


/*	if(is2T) {*/
/*		ODM_SetBBReg(pDM_Odm, rFPGA0_XA_LSSIParameter, bMaskDWord, 0x00010000);*/
/*		ODM_SetBBReg(pDM_Odm, rFPGA0_XB_LSSIParameter, bMaskDWord, 0x00010000);*/
/*	}*/

	/*MAC settings*/
	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
	_PHY_MACSettingCalibration_97F(pAdapter, IQK_MAC_REG, pDM_Odm->RFCalibrateInfo.IQK_MAC_backup);
	#else
	_PHY_MACSettingCalibration_97F(pDM_Odm, IQK_MAC_REG, pDM_Odm->RFCalibrateInfo.IQK_MAC_backup);
	#endif

	/* IQ calibration setting*/
	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("IQK setting!\n"));*/
	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x808000);
	ODM_SetBBReg(pDM_Odm, rTx_IQK, bMaskDWord, 0x01007c00);
	ODM_SetBBReg(pDM_Odm, rRx_IQK, bMaskDWord, 0x01004800);
	

/*path A TXIQK*/
	#if 1
	for (i = 0 ; i < retryCount ; i++) {
		#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
		PathAOK = phy_PathA_IQK_8197F(pAdapter, is2T);
		#else
		PathAOK = phy_PathA_IQK_8197F(pDM_Odm, is2T);
		#endif
		if (PathAOK == 0x01) {
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Path A TXIQK Success!!\n"));
			result[t][0] = (ODM_GetBBReg(pDM_Odm, rTx_Power_Before_IQK_A, bMaskDWord) & 0x3FF0000) >> 16;
			result[t][1] = (ODM_GetBBReg(pDM_Odm, rTx_Power_After_IQK_A, bMaskDWord) & 0x3FF0000) >> 16;
			break;
		} else {
			/*ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Path A TXIQK Fail!!\n"));*/
			panic_printk("[IQK] Path A TXIQK Fail!!!\n");
			result[t][0] = 0x100;
			result[t][1] = 0x0;
		}
		#if 0
		else if (i == (retryCount - 1) && PathAOK == 0x01) {	/*Tx IQK OK*/
			RT_DISP(FINIT, INIT_IQK, ("Path A IQK Only  Tx Success!!\n"));

			result[t][0] = (ODM_GetBBReg(pDM_Odm, rTx_Power_Before_IQK_A, bMaskDWord) & 0x3FF0000) >> 16;
			result[t][1] = (ODM_GetBBReg(pDM_Odm, rTx_Power_After_IQK_A, bMaskDWord) & 0x3FF0000) >> 16;
		}
		#endif
	}
	#endif

/*path A RXIQK*/
	#if 1
	for (i = 0 ; i < retryCount ; i++) {
		#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
		PathAOK = phy_PathA_RxIQK_97F(pAdapter, is2T);
		#else
		PathAOK = phy_PathA_RxIQK_97F(pDM_Odm, is2T);
		#endif
		if (PathAOK == 0x03) {
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Path A RXIQK Success!!\n"));
			result[t][2] = (ODM_GetBBReg(pDM_Odm, rRx_Power_Before_IQK_A_2, bMaskDWord) & 0x3FF0000) >> 16;
			result[t][3] = (ODM_GetBBReg(pDM_Odm, rRx_Power_After_IQK_A_2, bMaskDWord) & 0x3FF0000) >> 16;
			break;
		} else {
			/*ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Path A RXIQK Fail!!\n"));*/
			panic_printk("[IQK] path A RXIQK Fail!!!\n");
			result[t][2] = 0x100;
			result[t][3] = 0x0;
		}
	}

	if (0x00 == PathAOK)
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Path A IQK failed!!\n"));

	#endif

	if (is2T) {

		#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
		_PHY_PathAStandBy_97F(pAdapter);

		/*Turn ADDA on*/
		_PHY_PathADDAOn_97F(pAdapter, ADDA_REG, FALSE, is2T);
		#else
		_PHY_PathAStandBy_97F(pDM_Odm);

		/*Turn ADDA on*/
		_PHY_PathADDAOn_97F(pDM_Odm, ADDA_REG, FALSE, is2T);
		#endif

		/*IQ calibration setting*/
		/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("IQK setting!\n"));*/
		ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x808000);
		ODM_SetBBReg(pDM_Odm, rTx_IQK, bMaskDWord, 0x01007c00);
		ODM_SetBBReg(pDM_Odm, rRx_IQK, bMaskDWord, 0x01004800);

/*path B Tx IQK*/
		#if 1
		for (i = 0 ; i < retryCount ; i++) {
			#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
			PathBOK = phy_PathB_IQK_8197F(pAdapter);
			#else
			PathBOK = phy_PathB_IQK_8197F(pDM_Odm);
			#endif

			if (PathBOK == 0x01) {
				ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Path B TXIQK Success!!\n"));
				result[t][4] = (ODM_GetBBReg(pDM_Odm, rTx_Power_Before_IQK_B, bMaskDWord) & 0x3FF0000) >> 16;
				result[t][5] = (ODM_GetBBReg(pDM_Odm, rTx_Power_After_IQK_B, bMaskDWord) & 0x3FF0000) >> 16;
				break;
			} else {
				/*ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path B TXIQK Fail!!\n"));*/
				panic_printk("[IQK] Path B TXIQK Fail!!!\n");
				result[t][4] = 0x100;
				result[t][5] = 0x0;
			}
			#if 0
			else if (i == (retryCount - 1) && PathAOK == 0x01) {	/*Tx IQK OK*/
				RT_DISP(FINIT, INIT_IQK, ("Path B IQK Only  Tx Success!!\n"));

				result[t][0] = (ODM_GetBBReg(pDM_Odm, rTx_Power_Before_IQK_B, bMaskDWord) & 0x3FF0000) >> 16;
				result[t][1] = (ODM_GetBBReg(pDM_Odm, rTx_Power_After_IQK_B, bMaskDWord) & 0x3FF0000) >> 16;
			}
			#endif
		}
		#endif

/*path B RX IQK*/
		#if 1

		for (i = 0 ; i < retryCount ; i++) {
			#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
			PathBOK = phy_PathB_RxIQK_97F(pAdapter, is2T);
			#else
			PathBOK = phy_PathB_RxIQK_97F(pDM_Odm, is2T);
			#endif
			if (PathBOK == 0x03) {
				ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Path B RXIQK Success!!\n"));
				result[t][6] = (ODM_GetBBReg(pDM_Odm, rRx_Power_Before_IQK_B_2, bMaskDWord) & 0x3FF0000) >> 16;
				result[t][7] = (ODM_GetBBReg(pDM_Odm, rRx_Power_After_IQK_B_2, bMaskDWord) & 0x3FF0000) >> 16;
				break;

			} else {
				/*ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path B Rx IQK Fail!!\n"));*/
				panic_printk("[IQK] Path B RXIQK Fail!!!\n");
				result[t][6] = 0x100;
				result[t][7] = 0x0;
		} 
	}

		if (0x00 == PathBOK)
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path B IQK failed!!\n"));

		#endif
	}

	/*Back to BB mode, load original value*/
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Back to BB mode, load original value!\n"));
	ODM_SetBBReg(pDM_Odm, rFPGA0_IQK, 0xffffff00, 0x000000);

	if (t != 0) {


		#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)

		/* Reload ADDA power saving parameters*/
		_PHY_ReloadADDARegisters_97F(pAdapter, ADDA_REG, pDM_Odm->RFCalibrateInfo.ADDA_backup, IQK_ADDA_REG_NUM);

		/* Reload MAC parameters*/
		_PHY_ReloadMACRegisters_97F(pAdapter, IQK_MAC_REG, pDM_Odm->RFCalibrateInfo.IQK_MAC_backup);

		_PHY_ReloadADDARegisters_97F(pAdapter, IQK_BB_REG_92C, pDM_Odm->RFCalibrateInfo.IQK_BB_backup, IQK_BB_REG_NUM);
		#else
		/* Reload ADDA power saving parameters*/
		_PHY_ReloadADDARegisters_97F(pDM_Odm, ADDA_REG, pDM_Odm->RFCalibrateInfo.ADDA_backup, IQK_ADDA_REG_NUM);

		/* Reload MAC parameters*/
		_PHY_ReloadMACRegisters_97F(pDM_Odm, IQK_MAC_REG, pDM_Odm->RFCalibrateInfo.IQK_MAC_backup);

		_PHY_ReloadADDARegisters_97F(pDM_Odm, IQK_BB_REG_92C, pDM_Odm->RFCalibrateInfo.IQK_BB_backup, IQK_BB_REG_NUM);
		#endif

		/*Allen initial gain 0xc50*/
		/* Restore RX initial gain*/
		ODM_SetBBReg(pDM_Odm, 0xc50, bMaskByte0, 0x50);
		ODM_SetBBReg(pDM_Odm, 0xc50, bMaskByte0, tmp0xc50);
		if (is2T) {
			ODM_SetBBReg(pDM_Odm, 0xc58, bMaskByte0, 0x50);
			ODM_SetBBReg(pDM_Odm, 0xc58, bMaskByte0, tmp0xc58);
		}
		/*RF setting :RXBB enter power saving*/
		if (pDM_Odm->CutVersion != ODM_CUT_A) {
		ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, 0xdf, 0x00002, 0x0);
		ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_B, 0xdf, 0x00002, 0x0);
		}

		#if 0
		/*load 0xe30 IQC default value*/
		ODM_SetBBReg(pDM_Odm, rTx_IQK_Tone_A, bMaskDWord, 0x01008c00);
		ODM_SetBBReg(pDM_Odm, rRx_IQK_Tone_A, bMaskDWord, 0x01008c00);
		#endif

	}
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] phy_IQCalibrate_8197F() <==\n"));

}

VOID
phy_LCCalibrate_8197F(
#if (DM_ODM_SUPPORT_TYPE & ODM_AP)
	PVOID		pDM_VOID,
#else
	PADAPTER	pAdapter,
#endif
	BOOLEAN		is2T
)
{
	PDM_ODM_T		pDM_Odm	= (PDM_ODM_T)pDM_VOID;

	u1Byte	tmpReg;
	u4Byte	RF_Amode = 0, RF_Bmode = 0, LC_Cal, cnt;
	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(pAdapter);
	#if (DM_ODM_SUPPORT_TYPE == ODM_CE)
	PDM_ODM_T		pDM_Odm = &pHalData->odmpriv;
	#endif
	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)
	PDM_ODM_T		pDM_Odm = &pHalData->DM_OutSrc;
	#endif
	#endif
	/*Check continuous TX and Packet TX*/
	tmpReg = ODM_Read1Byte(pDM_Odm, 0xd03);

	if ((tmpReg & 0x70) != 0)			/*Deal with contisuous TX case*/
		ODM_Write1Byte(pDM_Odm, 0xd03, tmpReg & 0x8F);	/*disable all continuous TX*/
	else							/* Deal with Packet TX case*/
		ODM_Write1Byte(pDM_Odm, REG_TXPAUSE, 0xFF);			/* block all queues*/


	/*backup RF0x18*/
	LC_Cal = ODM_GetRFReg(pDM_Odm, ODM_RF_PATH_A, RF_CHNLBW, bRFRegOffsetMask);
		
	/*Start LCK*/
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, RF_CHNLBW, bRFRegOffsetMask, LC_Cal|0x08000);
	
	for (cnt = 0; cnt < 100; cnt++) {
		if (ODM_GetRFReg(pDM_Odm, ODM_RF_PATH_A, RF_CHNLBW, 0x8000) != 0x1)
			break;
		
		ODM_delay_ms(10);
	}
	
	/*Recover channel number*/
	ODM_SetRFReg(pDM_Odm, ODM_RF_PATH_A, RF_CHNLBW, bRFRegOffsetMask, LC_Cal);	


	/*Restore original situation*/
	if ((tmpReg&0x70) != 0) {
		/*Deal with contisuous TX case*/
		ODM_Write1Byte(pDM_Odm, 0xd03, tmpReg);
	} else { 
		/* Deal with Packet TX case*/
		ODM_Write1Byte(pDM_Odm, REG_TXPAUSE, 0x00);
	}

}


VOID
PHY_IQCalibrate_8197F(
#if (DM_ODM_SUPPORT_TYPE & ODM_AP)
	PVOID		pDM_VOID,
#else
	PADAPTER	pAdapter,
#endif
	BOOLEAN		bReCovery
)
{
	PDM_ODM_T		pDM_Odm	= (PDM_ODM_T)pDM_VOID;

	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(pAdapter);

	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)
	PDM_ODM_T		pDM_Odm = &pHalData->DM_OutSrc;
	#else  /*(DM_ODM_SUPPORT_TYPE == ODM_CE)*/
	PDM_ODM_T		pDM_Odm = &pHalData->odmpriv;
	#endif

	#if (MP_DRIVER == 1)
	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)
	PMPT_CONTEXT	pMptCtx = &(pAdapter->MptCtx);
	#else/* (DM_ODM_SUPPORT_TYPE == ODM_CE)*/
	PMPT_CONTEXT	pMptCtx = &(pAdapter->mppriv.MptCtx);
	#endif
	#endif/*(MP_DRIVER == 1)*/
	#endif
	PODM_RF_CAL_T	pRFCalibrateInfo = &(pDM_Odm->RFCalibrateInfo);


	s4Byte			result[4][8];	/*last is final result*/
	u1Byte			i, final_candidate, Indexforchannel;
	u1Byte          channelToIQK = 7;
	BOOLEAN			bPathAOK, bPathBOK;
	s4Byte			RegE94, RegE9C, RegEA4, RegEAC, RegEB4, RegEBC, RegEC4, RegECC;
	BOOLEAN			is12simular, is13simular, is23simular;
	BOOLEAN			bStartContTx = FALSE, bSingleTone = FALSE, bCarrierSuppression = FALSE;
	u4Byte			IQK_BB_REG_92C[IQK_BB_REG_NUM] = {
		rOFDM0_XARxIQImbalance,		rOFDM0_XBRxIQImbalance,
		rOFDM0_ECCAThreshold,		0xca8,
		rOFDM0_XATxIQImbalance,		rOFDM0_XBTxIQImbalance,
		rOFDM0_XCTxAFE,				rOFDM0_XDTxAFE,
		rOFDM0_RxIQExtAnta
	};

	#if (DM_ODM_SUPPORT_TYPE & (ODM_WIN|ODM_CE))
	if (ODM_CheckPowerStatus(pAdapter) == FALSE)
		return;
	#else
	prtl8192cd_priv	priv = pDM_Odm->priv;

	#ifdef MP_TEST
	if (priv->pshare->rf_ft_var.mp_specific) {
		if ((OPMODE & WIFI_MP_CTX_PACKET) || (OPMODE & WIFI_MP_CTX_ST))
			return;
	}
	#endif
	/* if (priv->pshare->IQK_92E_done)*/
	/*		bReCovery= 1; */
	/*	priv->pshare->IQK_92E_done = 1;*/
	#endif

	#if (DM_ODM_SUPPORT_TYPE == ODM_CE)
	if (!(pDM_Odm->SupportAbility & ODM_RF_CALIBRATION))
		return;
	#endif

	#if MP_DRIVER == 1
	bStartContTx = pMptCtx->bStartContTx;
	bSingleTone = pMptCtx->bSingleTone;
	bCarrierSuppression = pMptCtx->bCarrierSuppression;
	#endif

	/* 20120213<Kordan> Turn on when continuous Tx to pass lab testing. (required by Edlu)*/
	if (bSingleTone || bCarrierSuppression)
		return;

	#ifdef DISABLE_BB_RF
	return;
	#endif

	if (pRFCalibrateInfo->bIQKInProgress)
		return;	

	#if (DM_ODM_SUPPORT_TYPE & (ODM_CE|ODM_AP))
	if (bReCovery)
	#else /*for ODM_WIN*/
	if (bReCovery && 
	(!pAdapter->bInHctTest)) /*YJ,add for PowerTest,120405*/
	#endif
	{
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_INIT, ODM_DBG_LOUD, ("[IQK] PHY_IQCalibrate_97F: Return due to bReCovery!\n"));
		#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
		_PHY_ReloadADDARegisters_97F(pAdapter, IQK_BB_REG_92C, pDM_Odm->RFCalibrateInfo.IQK_BB_backup_recover, 9);
		#else
		_PHY_ReloadADDARegisters_97F(pDM_Odm, IQK_BB_REG_92C, pDM_Odm->RFCalibrateInfo.IQK_BB_backup_recover, 9);
		#endif
		return;
	}

	/*check IC cut and IQK version*/
	if (pDM_Odm->CutVersion == ODM_CUT_A)
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Cut Version is A cut\n"));	
	else if (pDM_Odm->CutVersion == ODM_CUT_B)
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] Cut Version is B cut\n"));

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] IQK Version is v2.0 (20160419)\n"));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] ExtPA = %d, ExtLNA = %d\n", pDM_Odm->ExtPA, pDM_Odm->ExtLNA));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] IQK Start!!!\n"));
	priv->pshare->IQK_total_cnt++;

#if 0
	ODM_AcquireSpinLock(pDM_Odm, RT_IQK_SPINLOCK);
	pRFCalibrateInfo->bIQKInProgress = TRUE;
	ODM_ReleaseSpinLock(pDM_Odm, RT_IQK_SPINLOCK);
#endif

	for (i = 0; i < 8; i++) {
		result[0][i] = 0;
		result[1][i] = 0;
		result[2][i] = 0;

		if ((i == 0) || (i == 2) || (i == 4)  || (i == 6))
			result[3][i] = 0x100;
		else
			result[3][i] = 0;
	}

	final_candidate = 0xff;
	bPathAOK = FALSE;
	bPathBOK = FALSE;
	is12simular = FALSE;
	is23simular = FALSE;
	is13simular = FALSE;


	for (i = 0; i < 3; i++) {

		#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)

		phy_IQCalibrate_8197F(pAdapter, result, i, TRUE);


		#else


		phy_IQCalibrate_8197F(pDM_Odm, result, i, TRUE);
		#endif


		if (i == 1) {
			#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
			is12simular = phy_SimularityCompare_8197F(pAdapter, result, 0, 1);
			#else
			is12simular = phy_SimularityCompare_8197F(pDM_Odm, result, 0, 1);
			#endif

			if (is12simular) {
				final_candidate = 0;
				ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] is12simular final_candidate is %x\n", final_candidate));
				break;
			}
		}

		if (i == 2) {
			#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
			is13simular = phy_SimularityCompare_8197F(pAdapter, result, 0, 2);
			#else
			is13simular = phy_SimularityCompare_8197F(pDM_Odm, result, 0, 2);
			#endif

			if (is13simular) {
				final_candidate = 0;
				ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] is13simular final_candidate is %x\n", final_candidate));

				break;
			}
			#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
			is23simular = phy_SimularityCompare_8197F(pAdapter, result, 1, 2);
			#else
			is23simular = phy_SimularityCompare_8197F(pDM_Odm, result, 1, 2);
			#endif

			if (is23simular) {
				final_candidate = 1;
				ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] is23simular final_candidate is %x\n", final_candidate));
			} else {
#if 0
								for (i = 0; i < 4; i++)
									RegTmp &= result[3][i*2];

								if (RegTmp != 0)
									final_candidate = 3;
								else
									final_candidate = 0xFF;
#endif
				final_candidate = 3;

			}
		}
	}
#if 0
	if ((result[final_candidate][0] | result[final_candidate][2] | result[final_candidate][4] | result[final_candidate][6]) == 0) {
		for (i = 0; i < 8; i++) {
			if ((i == 0) || (i == 2) || (i == 4)  || (i == 6))
				result[final_candidate][i] = 0x100;
			else
				result[final_candidate][i] = 0;
		}
	}
#endif

	for (i = 0; i < 4; i++) {
		RegE94 = result[i][0];
		RegE9C = result[i][1];
		RegEA4 = result[i][2];
		RegEAC = result[i][3];
		RegEB4 = result[i][4];
		RegEBC = result[i][5];
		RegEC4 = result[i][6];
		RegECC = result[i][7];
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] RegE94=%x RegE9C=%x RegEA4=%x RegEAC=%x RegEB4=%x RegEBC=%x RegEC4=%x RegECC=%x\n ", RegE94, RegE9C, RegEA4, RegEAC, RegEB4, RegEBC, RegEC4, RegECC));
	}

	if (final_candidate != 0xff) {
		priv->pshare->RegE94 = pDM_Odm->RFCalibrateInfo.RegE94 = RegE94 = result[final_candidate][0];
		priv->pshare->RegE9C = pDM_Odm->RFCalibrateInfo.RegE9C = RegE9C = result[final_candidate][1];
		RegEA4 = result[final_candidate][2];
		RegEAC = result[final_candidate][3];
		priv->pshare->RegEB4 = pDM_Odm->RFCalibrateInfo.RegEB4 = RegEB4 = result[final_candidate][4];
		priv->pshare->RegEBC = pDM_Odm->RFCalibrateInfo.RegEBC = RegEBC = result[final_candidate][5];
		RegEC4 = result[final_candidate][6];
		RegECC = result[final_candidate][7];
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] final_candidate is %x\n", final_candidate));
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] TX0_X=%x TX0_Y=%x RX0_X=%x RX0_Y=%x TX1_X=%x TX1_Y=%x RX1_X=%x RX1_Y=%x\n ", RegE94, RegE9C, RegEA4, RegEAC, RegEB4, RegEBC, RegEC4, RegECC));
		bPathAOK = bPathBOK = TRUE;
	} else {
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] FAIL use default value\n"));

		pDM_Odm->RFCalibrateInfo.RegE94 = pDM_Odm->RFCalibrateInfo.RegEB4 = 0x100;	/*X default value*/
		pDM_Odm->RFCalibrateInfo.RegE9C = pDM_Odm->RFCalibrateInfo.RegEBC = 0x0;	/*Y default value*/
		panic_printk("[IQK] Load IQK default value");
		priv->pshare->IQK_fail_cnt++;
	}

	if ((RegE94 != 0)/*&&(RegEA4 != 0)*/) {
		#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
		_PHY_PathAFillIQKMatrix_97F(pAdapter, bPathAOK, result, final_candidate, (RegEA4 == 0));
		#else
		_PHY_PathAFillIQKMatrix_97F(pDM_Odm, bPathAOK, result, final_candidate, (RegEA4 == 0));
		#endif
	}

	if ((RegEB4 != 0)/*&&(RegEC4 != 0)*/) {
		#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
		_PHY_PathBFillIQKMatrix_97F(pAdapter, bPathBOK, result, final_candidate, (RegEC4 == 0));
		#else
		_PHY_PathBFillIQKMatrix_97F(pDM_Odm, bPathBOK, result, final_candidate, (RegEC4 == 0));
		#endif
	}

	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
	Indexforchannel = ODM_GetRightChnlPlaceforIQK(pHalData->CurrentChannel);
	#else
	Indexforchannel = 0;
	#endif

/*To Fix BSOD when final_candidate is 0xff*/
/*by sherry 20120321*/
	if (final_candidate < 4) {
		for (i = 0; i < IQK_Matrix_REG_NUM; i++)
			pDM_Odm->RFCalibrateInfo.IQKMatrixRegSetting[Indexforchannel].Value[0][i] = result[final_candidate][i];
		pDM_Odm->RFCalibrateInfo.IQKMatrixRegSetting[Indexforchannel].bIQKDone = TRUE;
	}
	/*RT_DISP(FINIT, INIT_IQK, ("\nIQK OK Indexforchannel %d.\n", Indexforchannel));*/
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] IQK OK Indexforchannel %d.\n", Indexforchannel));
	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)

	_PHY_SaveADDARegisters_97F(pAdapter, IQK_BB_REG_92C, pDM_Odm->RFCalibrateInfo.IQK_BB_backup_recover, 9);
	#else
	_PHY_SaveADDARegisters_97F(pDM_Odm, IQK_BB_REG_92C, pDM_Odm->RFCalibrateInfo.IQK_BB_backup_recover, IQK_BB_REG_NUM);
	#endif

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xc80 = 0x%x, 0xc94 = 0x%x\n", ODM_GetBBReg(pDM_Odm, 0xc80, bMaskDWord), ODM_GetBBReg(pDM_Odm, 0xc94, bMaskDWord)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xc14 = 0x%x, 0xca0 = 0x%x\n", ODM_GetBBReg(pDM_Odm, 0xc14, bMaskDWord), ODM_GetBBReg(pDM_Odm, 0xca0, bMaskDWord)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xc88 = 0x%x, 0xc9c = 0x%x\n", ODM_GetBBReg(pDM_Odm, 0xc88, bMaskDWord), ODM_GetBBReg(pDM_Odm, 0xc9c, bMaskDWord)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0xc1c = 0x%x, 0xca8 = 0x%x\n", ODM_GetBBReg(pDM_Odm, 0xc1c, bMaskDWord), ODM_GetBBReg(pDM_Odm, 0xca8, bMaskDWord)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0x58 at Path A = 0x%x\n",
				 ODM_GetRFReg(pDM_Odm, ODM_RF_PATH_A, 0x58, bRFRegOffsetMask)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] 0x58 at Path B = 0x%x\n",
				 ODM_GetRFReg(pDM_Odm, ODM_RF_PATH_B, 0x58, bRFRegOffsetMask)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("[IQK] IQK finished\n"));

}


VOID
PHY_LCCalibrate_8197F(
	PVOID		pDM_VOID
)
{
	PDM_ODM_T		pDM_Odm = (PDM_ODM_T)pDM_VOID;
	BOOLEAN			bStartContTx = FALSE, bSingleTone = FALSE, bCarrierSuppression = FALSE;
	u4Byte			timeout = 2000, timecount = 0;

	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
	PADAPTER		pAdapter = pDM_Odm->Adapter;
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(pAdapter);

	#if (MP_DRIVER == 1)
	#if (DM_ODM_SUPPORT_TYPE == ODM_WIN)
	PMPT_CONTEXT	pMptCtx = &(pAdapter->MptCtx);
	#else/* (DM_ODM_SUPPORT_TYPE == ODM_CE)*/
	PMPT_CONTEXT	pMptCtx = &(pAdapter->mppriv.MptCtx);
	#endif
	#endif/*(MP_DRIVER == 1)*/
	#endif




	#if MP_DRIVER == 1
	bStartContTx = pMptCtx->bStartContTx;
	bSingleTone = pMptCtx->bSingleTone;
	bCarrierSuppression = pMptCtx->bCarrierSuppression;
	#endif


	#ifdef DISABLE_BB_RF
	return;
	#endif

	#if (DM_ODM_SUPPORT_TYPE == ODM_CE)
	if (!(pDM_Odm->SupportAbility & ODM_RF_CALIBRATION))
		return;
	#endif
	/* 20120213<Kordan> Turn on when continuous Tx to pass lab testing. (required by Edlu) */
	if (bSingleTone || bCarrierSuppression)
		return;

	while (*(pDM_Odm->pbScanInProcess) && timecount < timeout) {
		ODM_delay_ms(50);
		timecount += 50;
	}

	pDM_Odm->RFCalibrateInfo.bLCKInProgress = TRUE;

	/*ODM_RT_TRACE(pDM_Odm,ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("LCK:Start!!!interface %d currentband %x delay %d ms\n", pDM_Odm->interfaceIndex, pHalData->CurrentBandType92D, timecount));*/
	#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)

	if (IS_2T2R(pHalData->VersionID))
		phy_LCCalibrate_8197F(pAdapter, TRUE);
	else
	#endif
	{
		/* For 88C 1T1R*/
		#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
		phy_LCCalibrate_8197F(pAdapter, FALSE);
		#else
		phy_LCCalibrate_8197F(pDM_Odm, FALSE);
		#endif
	}

	pDM_Odm->RFCalibrateInfo.bLCKInProgress = FALSE;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("LCK:Finish!!!interface %d\n", pDM_Odm->InterfaceIndex));

}




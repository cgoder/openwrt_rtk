#ifndef __HAL8822BE_DEF_H__
#define __HAL8822BE_DEF_H__

/*++
Copyright (c) Realtek Semiconductor Corp. All rights reserved.

Module Name:
	Hal8822BEDef.h
	
Abstract:
	Defined HAL 8822BE data structure & Define
	    
Major Change History:
	When       Who               What
	---------- ---------------   -------------------------------
	2015-06-25 Eric             Create.	
--*/


/*RT_STATUS
InitPON8822BE(
    IN  HAL_PADAPTER    Adapter,
    IN  u4Byte          ClkSel        
);

RT_STATUS
StopHW8822BE(
    IN  HAL_PADAPTER    Adapter
);


RT_STATUS
ResetHWForSurprise8822BE(
    IN  HAL_PADAPTER Adapter
);
*/

RT_STATUS	
hal_Associate_8822BE(
	struct rtl8192cd_priv *priv,
	BOOLEAN             IsDefaultAdapter
);

#if (BEAMFORMING_SUPPORT == 1)
VOID
SetBeamformInit8822B(
	struct rtl8192cd_priv *priv
	);

VOID
SetBeamformEnter8822B(
	struct rtl8192cd_priv *priv,
	IN u1Byte				BFerBFeeIdx
	);

VOID
SetBeamformLeave8822B(
	struct rtl8192cd_priv *priv,
	IN u1Byte				Idx
	);

VOID
SetBeamformStatus8822B(
	struct rtl8192cd_priv *priv,
	IN u1Byte				Idx
	);

VOID
HalTxbf8822B_ConfigGtab(
	struct rtl8192cd_priv *priv
	);

VOID
C2HTxBeamformingHandler_8822B(
	struct rtl8192cd_priv *priv,
		pu1Byte			CmdBuf,
		u1Byte			CmdLen
);
#endif 


#endif  //__HAL8822BE_DEF_H__


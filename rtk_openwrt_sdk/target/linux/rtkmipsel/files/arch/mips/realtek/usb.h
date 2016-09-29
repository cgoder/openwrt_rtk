/*
 * Realtek Semiconductor Corp.
 *
 * bsp/usb.h:
 *     bsp USB header file
 *
 * Copyright (C) 2006-2012 Tony Wu (tonywu@realtek.com)
 */

#ifndef _USB_H_
#define _USB_H_


#define OTG_GOTGCTL         (BSP_USB_OTG_BASE)
#define OTG_GOTGINT         (BSP_USB_OTG_BASE + 0x4)

#define OTG_GOTGINT_DbnceDone          (1<<19)
#define OTG_GOTGINT_ADevTOUTChg        (1<<18)
#define OTG_GOTGINT_HstNegDet          (1<<17)
#define OTG_GOTGINT_HstNegSucStsChng   (1<<9)
#define OTG_GOTGINT_SesReqSucStsChng   (1<<8)
#define OTG_GOTGINT_SesEndDet          (1<<2)

#define OTG_GOTGINT_ALL   (OTG_GOTGINT_DbnceDone | \
                           OTG_GOTGINT_ADevTOUTChg | \
                           OTG_GOTGINT_HstNegDet | \
                           OTG_GOTGINT_HstNegSucStsChng | \
                           OTG_GOTGINT_SesReqSucStsChng | \
                           OTG_GOTGINT_SesEndDet)

#define OTG_GAHBCFG                    (BSP_USB_OTG_BASE + 0x8)
#define OTG_GAHBCFG_PTxFEmpLvl         (1<<8)
#define OTG_GAHBCFG_NPTxFEmpLvl        (1<<7)
#define OTG_GAHBCFG_DMAEn              (1<<5)
#define OTG_GAHBCFG_HBstLen(len)       ((len & 0xf) << 1)
#define OTG_GAHBCFG_GlblIntrMsk        (1<<0)

#define OTG_GUSBCFG                      (BSP_USB_OTG_BASE + 0xC)
#define OTG_GUSBCFG_CorruptTxPacket      (1<<31)
#define OTG_GUSBCFG_ForceDevMode         (1<<30)
#define OTG_GUSBCFG_ForceHstMode         (1<<29)
#define OTG_GUSBCFG_TermSelDLPulse       (1<<22)
#define OTG_GUSBCFG_ULPIExtVbusIndicator (1<<21)
#define OTG_GUSBCFG_ULPIExtVbusDrv       (1<<20)
#define OTG_GUSBCFG_ULPIClkSusM          (1<<19)
#define OTG_GUSBCFG_ULPIAutoRes          (1<<18)
#define OTG_GUSBCFG_ULPIFsLs             (1<<17)
#define OTG_GUSBCFG_OtgI2CSel            (1<<16)
#define OTG_GUSBCFG_PhyLPwrClkSel        (1<<15)
#define OTG_GUSBCFG_USBTrdTime(x)        ((x & 0xf) << 10)
#define OTG_GUSBCFG_HNPCap               (1<<9)
#define OTG_GUSBCFG_SRPCap               (1<<8)
#define OTG_GUSBCFG_DDRSel               (1<<7)
#define OTG_GUSBCFG_PHYSel               (1<<6)
#define OTG_GUSBCFG_FSIntf               (1<<5)
#define OTG_GUSBCFG_ULPI_UTMI_Sel        (1<<4)
#define OTG_GUSBCFG_PHYIf                (1<<3)
#define OTG_GUSBCFG_TOutCal(x)           (x & 0x7)

#define OTG_GRSTCTL                      (BSP_USB_OTG_BASE + 0x10)
#define OTG_GRSTCTL_AHBIdle              (1<<31)
#define OTG_GRSTCTL_DMAReq               (1<<30)
#define OTG_GRSTCTL_TxFNum(num)          ((num & 0x1f)<<6)
#define OTG_GRSTCTL_TxFFlsh              (1<<5)
#define OTG_GRSTCTL_RxFFlsh              (1<<4)
#define OTG_GRSTCTL_INTknQFlsh           (1<<3)
#define OTG_GRSTCTL_FrmCntrRst           (1<<2)
#define OTG_GRSTCTL_HSftRst              (1<<1)
#define OTG_GRSTCTL_CSftRst              (1<<0)


#define OTG_GINTSTS                     (BSP_USB_OTG_BASE + 0x14)
#define OTG_GINTSTS_WkUpInt             (1<<31)
#define OTG_GINTSTS_SessReqInt          (1<<30)
#define OTG_GINTSTS_DisconnInt          (1<<29)
#define OTG_GINTSTS_ConIDStsChng        (1<<28)
#define OTG_GINTSTS_PTxFEmp             (1<<26)
#define OTG_GINTSTS_HChInt              (1<<25)
#define OTG_GINTSTS_PrtInt              (1<<24)
#define OTG_GINTSTS_FetSusp             (1<<22)
#define OTG_GINTSTS_incomplP            (1<<21)
#define OTG_GINTSTS_incompISOIN         (1<<20)
#define OTG_GINTSTS_OEPInt              (1<<19)
#define OTG_GINTSTS_IEPInt              (1<<18)
#define OTG_GINTSTS_EPMis               (1<<17)
#define OTG_GINTSTS_EOPF                (1<<15)
#define OTG_GINTSTS_ISOOutDrop          (1<<14)
#define OTG_GINTSTS_EnumDone            (1<<13)
#define OTG_GINTSTS_USBRst              (1<<12)
#define OTG_GINTSTS_USBSusp             (1<<11)
#define OTG_GINTSTS_ErlySusp            (1<<10)
#define OTG_GINTSTS_I2CINT              (1<<9)
#define OTG_GINTSTS_ULPICKINT           (1<<8)
#define OTG_GINTSTS_GOUTNakEff          (1<<7)
#define OTG_GINTSTS_GINNakEff           (1<<6)
#define OTG_GINTSTS_NPTxFEmp            (1<<5)
#define OTG_GINTSTS_RxFLvl              (1<<4)
#define OTG_GINTSTS_Sof                 (1<<3)
#define OTG_GINTSTS_OTGInt              (1<<2)
#define OTG_GINTSTS_ModeMis             (1<<1)
#define OTG_GINTSTS_CurHostMod          (1<<0)



#define OTG_GINTMSK                   (BSP_USB_OTG_BASE + 0x18)
#define OTG_GINTMSK_WkUpIntMsk          (1<<31)
#define OTG_GINTMSK_SessReqIntMsk       (1<<30)
#define OTG_GINTMSK_DisconnIntMsk       (1<<29)
#define OTG_GINTMSK_ConIDStsChngMsk     (1<<28)
#define OTG_GINTMSK_PTxFEmpMsk          (1<<26)
#define OTG_GINTMSK_HChIntMsk           (1<<25)
#define OTG_GINTMSK_PrtIntMsk           (1<<24)
#define OTG_GINTMSK_FetSuspMsk          (1<<22)
#define OTG_GINTMSK_incomplPMsk         (1<<21)
#define OTG_GINTMSK_incompISOINMsk      (1<<20)
#define OTG_GINTMSK_OEPIntMsk           (1<<19)
#define OTG_GINTMSK_INEPIntMsk          (1<<18)
#define OTG_GINTMSK_EPMisMsk            (1<<17)
#define OTG_GINTMSK_EOPFMsk             (1<<15)
#define OTG_GINTMSK_ISOOutDropMsk       (1<<14)
#define OTG_GINTMSK_EnumDoneMsk         (1<<13)
#define OTG_GINTMSK_USBRstMsk           (1<<12)
#define OTG_GINTMSK_USBSuspMsk          (1<<11)
#define OTG_GINTMSK_ErlySuspMsk         (1<<10)
#define OTG_GINTMSK_I2CINTMsk           (1<<9)
#define OTG_GINTMSK_ULPICKINTMsk        (1<<8)
#define OTG_GINTMSK_GOUTNakEffMsk       (1<<7)
#define OTG_GINTMSK_GINNakEffMsk        (1<<6)
#define OTG_GINTMSK_NPTxFEmpMsk         (1<<5)
#define OTG_GINTMSK_RxFLvlMsk           (1<<4)
#define OTG_GINTMSK_SofMsk              (1<<3)
#define OTG_GINTMSK_OTGIntMsk           (1<<2)
#define OTG_GINTMSK_ModeMisMsk          (1<<1)

#define OTG_GRXSTSP                     (BSP_USB_OTG_BASE + 0x20)
#define OTG_GRXSTSR                     (BSP_USB_OTG_BASE + 0x1c)
#define OTG_GNPTXSTS                    (BSP_USB_OTG_BASE + 0x2C)

// Synopsys ID Register
#define OTG_GSNPSID                     (BSP_USB_OTG_BASE + 0x40)
#define OTG_DFIFO(n)                    (BSP_USB_OTG_BASE + 0x1000+(0x1000*n))

#define OTG_HCFG                  (BSP_USB_OTG_BASE + 0x400)
#define OTG_HFIR                  (BSP_USB_OTG_BASE + 0x404)
#define OTG_HFNUM                 (BSP_USB_OTG_BASE + 0x408)
#define OTG_HPTXSTS               (BSP_USB_OTG_BASE + 0x410)
#define OTG_HAINT                 (BSP_USB_OTG_BASE + 0x414)
#define OTG_HAINTMSK              (BSP_USB_OTG_BASE + 0x418)
#define OTG_HPRT                  (BSP_USB_OTG_BASE + 0x440)

#define OTG_HPRT_PrtSpd            (1<<17)
#define OTG_HPRT_PrtTstCtl         (1<<13)
#define OTG_HPRT_PrtPwr            (1<<12)
#define OTG_HPRT_PrtRst            (1<<8)
#define OTG_HPRT_PrtSusp           (1<<7)
#define OTG_HPRT_PrtRes            (1<<6)
#define OTG_HPRT_PrtOvrCurrChng    (1<<5)
#define OTG_HPRT_PrtOvrCurrAct     (1<<4)
#define OTG_HPRT_PrtEnChng         (1<<3)
#define OTG_HPRT_PrtEna            (1<<2)
#define OTG_HPRT_PrtConnDet        (1<<1)
#define OTG_HPRT_PrtConnSts        (1<<0)

//channel register
#define OTG_HCCHAR(n)              (BSP_USB_OTG_BASE + 0x500 + (n)*0x20)
#define OTG_HCSPLT(n)              (BSP_USB_OTG_BASE + 0x504 + (n)*0x20)
#define OTG_HCINT(n)               (BSP_USB_OTG_BASE + 0x508 + (n)*0x20)
#define OTG_HCINTMSK(n)            (BSP_USB_OTG_BASE + 0x50c + (n)*0x20)
#define OTG_HCTSIZ(n)              (BSP_USB_OTG_BASE + 0x510 + (n)*0x20)
#define OTG_HCDMA(n)               (BSP_USB_OTG_BASE + 0x514 + (n)*0x20)

#endif

#if (BEAMFORMING_SUPPORT == 1)

#define TxBF_Nr(a,b) ((a>b) ? (b) : (a))

VOID
Beamforming_SetBeamFormInit(
	struct rtl8192cd_priv *priv
		);

u1Byte
Beamforming_GetHTNDPTxRate(
	struct rtl8192cd_priv *priv,
	u1Byte	CompSteeringNumofBFer
);

u1Byte
Beamforming_GetVHTNDPTxRate(
	struct rtl8192cd_priv *priv,
	u1Byte	CompSteeringNumofBFer
);

VOID
Beamforming_GidPAid(
	struct rtl8192cd_priv *priv,
	struct stat_info	*pstat
);

enum _BEAMFORMING_CAP

Beamforming_GetEntryBeamCapByMacId(
	struct rtl8192cd_priv *priv,
	IN	u1Byte		MacId
);

BOOLEAN
Beamforming_InitEntry(
	struct rtl8192cd_priv	*priv,
	struct stat_info		*pSTA,
	pu1Byte					Idx	
);

BOOLEAN
Beamforming_DeInitEntry(
	struct rtl8192cd_priv *priv,
	pu1Byte			RA
);

VOID
Beamforming_Notify(
	struct rtl8192cd_priv *priv
);

VOID
Beamforming_Enter(
	struct rtl8192cd_priv *priv,
	struct stat_info	*pstat
);

VOID
Beamforming_TimerCallback(
	struct rtl8192cd_priv *priv
);

VOID
Beamforming_AutoTest(
	struct rtl8192cd_priv *priv,
	u1Byte					Idx, 
	struct _RT_BEAMFORMING_ENTRY *pBeamformEntry
);

VOID
Beamforming_End(
	struct rtl8192cd_priv *priv,
	BOOLEAN			Status	
);

VOID
Beamforming_Leave(
	struct rtl8192cd_priv *priv,
	pu1Byte			RA
);
VOID
Beamforming_Release(
	struct rtl8192cd_priv *priv
);

BEAMFORMING_CAP
Beamforming_GetBeamCap(
	struct rtl8192cd_priv *priv, 
	IN PRT_BEAMFORMING_INFO 	pBeamInfo
);

VOID
Beamforming_Init(
	struct rtl8192cd_priv *priv
);

VOID
Beamforming_SetTxBFen(
	struct rtl8192cd_priv *priv, 
	u1Byte MacId, 
	BOOLEAN		bTxBF
);

PRT_BEAMFORMING_ENTRY
Beamforming_GetEntryByMacId(
	struct rtl8192cd_priv *priv,
	u1Byte		MacId,
	pu1Byte		Idx
	);

PRT_BEAMFORMING_ENTRY
Beamforming_GetFreeBFeeEntry(
	struct rtl8192cd_priv *priv,
	pu1Byte		Idx,
	pu1Byte         RA
	);

PRT_BEAMFORMER_ENTRY
Beamforming_GetFreeBFerEntry(
	struct rtl8192cd_priv *priv,
	OUT	pu1Byte		Idx,
	pu1Byte             RA
	);

VOID
Beamforming_GetNDPAFrame(
	struct rtl8192cd_priv *priv,
	pu1Byte					pNDPAFrame
	);



#if 1 //eric-8822
BOOLEAN
SendVHTNDPAPacket(
	struct rtl8192cd_priv *priv,
	IN	pu1Byte			RA,
	IN	u2Byte			AID,
	u1Byte 				BW,
	u1Byte		NDPTxRate
	);
BOOLEAN
SendVHTNDPAPacket_MU(
	struct rtl8192cd_priv *priv,
	IN	pu1Byte			RA,
	IN	u2Byte			AID,
	u1Byte 				BW,
	u1Byte		NDPTxRate
	);
BOOLEAN
SendReportPollPacket(
	struct rtl8192cd_priv *priv,
	IN	pu1Byte			RA,
	u1Byte 				BW,
	u1Byte				TxRate,
	BOOLEAN				bFinalPoll
	);

#endif

u1Byte
beamform_GetFirstMUBFeeEntryIdx(
	struct rtl8192cd_priv *priv
	);

VOID
beamform_UpdateMinSoundingPeriod(
	struct rtl8192cd_priv *priv,
	IN u2Byte			CurBFeePeriod,
	IN BOOLEAN		bBFeeLeave
	);

VOID 
beamform_SoundingTimerCallback(
	struct rtl8192cd_priv *priv
    );

VOID 
beamform_SoundingTimeout(
    struct rtl8192cd_priv *priv
    );

void issue_action_GROUP_ID(struct rtl8192cd_priv *priv, unsigned char idx);

VOID
Beamform_SoundingDown(
	struct rtl8192cd_priv *priv,
	IN BOOLEAN		Status	
	);

#endif


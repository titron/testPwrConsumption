/***********************************************************************************************************/
/* Cluster input                                                                                           */
/*                                                                                                         */
/* File          :                                                                                         */
/* Creation date : 18.04.2016, 14:30:55                                                                    */
/* Note          : Don't change filename or contents!                                                      */
/***********************************************************************************************************/

/*----- Node File -------*/
/* Node 1 : Node_1.h */
/* Node 2 : Node_2.h */
/* Node 3 : Node_3.h */
/*-----------------------*/
#define CSA                2        /* SUCC1 (gColdStartAttempts) */
#define LTN                1        /* SUCC2 (gListenNoise - 1) */
#define WCP                1        /* SUCC3 (gMaxWithoutClockCorrectionPassive) */
#define WCF                1        /* SUCC3 (gMaxWithoutClockCorrectionFatal) */
#define NML                0        /* NEMC (gNetworkManagementVectorLength) */
#define TSST               6        /* PRTC1 (gdTSSTransmitter) */
#define CASM               81       /* PRTC1 (gdCASRxLowMax) */
#define RXW                301      /* PRTC1 (gdWakeupSymbolRxWindow) */
#define RXI                59       /* PRTC2 (gdWakeupSymbolRxIdle) */
#define RXL                55       /* PRTC2 (gdWakeupSymbolRxLow) */
#define TXI                180      /* PRTC2 (gdWakeupSymbolTxIdle) */
#define TXL                60       /* PRTC2 (gdWakeupSymbolTxLow) */
#define SFDL               1        /* MHDC (gPayloadLengthStatic) */
#define MPC                16000    /* GTUC2 (gMacroPerCycle) */
#define SNM                3        /* GTUC2 (gSyncNodeMax) */
#define NIT                15401    /* GTUC4: Network Idle Time Start */
#define OCS                15501    /* GTUC4 (gOffsetCorrectionStart) */
#define SSL                659      /* GTUC7 (gdStaticSlot) */
#define NSS                18       /* GTUC7 (gNumberOfStaticSlots) */
#define MSL                0        /* GTUC8 (gdMinislot) */
#define NMS                0        /* GTUC8 (gNumberOfMinislots) */
#define APO                4        /* GTUC9 (gdActionPointOffset) */
#define MAPO               0        /* GTUC9 (gdMinislotActionPointOffset) */
#define DSI                0        /* GTUC9 (gdDynamicSlotIdlePhase) */

/* Followings can't be set in E-Ray. */

/* gdBit                   0.1      */
/* Number_of_Node          3        */
/* Bit_Rate                10       */
/* line_length             1        */
/* nStarPath_M,N           0        */
/* dStarTruncation         0.45     */
/* d_pdtransmitter         0.1      */
/* d_pdline                0.01     */
/* d_pdstar                0.25     */
/* gdMacrotick             1        */
/* gClusterDriftDamping    5        */
/* gdMaxPropagationDelay   0.005    */
/* SymbolWindowCheck       0        */
/* NIT_length              598      */
/* Dynamic_Segment_Enable  0        Not mean pDynamicSegmentEnable */

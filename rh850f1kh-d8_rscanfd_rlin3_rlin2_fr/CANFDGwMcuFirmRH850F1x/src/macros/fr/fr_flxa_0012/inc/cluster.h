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

#define TEST_LOAD_RATE
#define RXW                301      /* PRTC1 (gdWakeupSymbolRxWindow) *//* comment @Titron */

#define RXI                59       /* PRTC2 (gdWakeupSymbolRxIdle) *//* comment @Titron */
#define RXL                55       /* PRTC2 (gdWakeupSymbolRxLow) *//* comment @Titron */
#define TXI                180      /* PRTC2 (gdWakeupSymbolTxIdle) *//* comment @Titron */
#define TXL                60       /* PRTC2 (gdWakeupSymbolTxLow) *//* comment @Titron */

//#ifndef TEST_LOAD_RATE
//#else
//#define RXW                76      /* PRTC1 (gdWakeupSymbolRxWindow) *//* comment @Titron */
//
//#define RXI                14       /* PRTC2 (gdWakeupSymbolRxIdle) */
//#define RXL                10       /* PRTC2 (gdWakeupSymbolRxLow) *//* comment @Titron */
//#define TXI                45      /* PRTC2 (gdWakeupSymbolTxIdle) *//* comment @Titron */
//#define TXL                15       /* PRTC2 (gdWakeupSymbolTxLow) *//* comment @Titron */
//#endif

#define SFDL               1        /* MHDC (gPayloadLengthStatic) */

#define MPC                16000    /* GTUC2 (gMacroPerCycle) *//* comment @Titron */


#define NIT                15401    /* GTUC4: Network Idle Time Start *//* comment @Titron */
#define OCS                15501    /* GTUC4 (gOffsetCorrectionStart) *//* comment @Titron */
//#ifndef TEST_LOAD_RATE
//#else
////#define MPC                201    /* GTUC2 (gMacroPerCycle) */
//
//#define NIT                195    /* GTUC4: Network Idle Time Start *//* comment @Titron */
//#define OCS                197    /* GTUC4 (gOffsetCorrectionStart) *//* comment @Titron */
//#endif

#define SNM                3        /* GTUC2 (gSyncNodeMax) */

#ifndef TEST_LOAD_RATE
#define SSL                659      /* GTUC7 (gdStaticSlot) *//* comment @Titron */
#define NSS                18       /* GTUC7 (gNumberOfStaticSlots) *//* comment @Titron */
#else
#define SSL                15      /* GTUC7 (gdStaticSlot) *//* comment @Titron */
#define NSS                18       /* GTUC7 (gNumberOfStaticSlots) *//* comment @Titron */
#endif


#define MSL                0        /* GTUC8 (gdMinislot) */
#define NMS                0        /* GTUC8 (gNumberOfMinislots) */

#define APO                4        /* GTUC9 (gdActionPointOffset) *//* comment @Titron */

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

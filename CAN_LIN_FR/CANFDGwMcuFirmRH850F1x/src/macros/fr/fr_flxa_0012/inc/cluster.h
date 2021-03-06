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
#define LTN                1        /* SUCC2 (gListenNoise - 1), 2~16 */
#define WCP                1        /* SUCC3 (gMaxWithoutClockCorrectionPassive), 1~15 */
#define WCF                1        /* SUCC3 (gMaxWithoutClockCorrectionFatal), 1~15 */
#define NML                0        /* NEMC (gNetworkManagementVectorLength), 0~12bytes */

#define TSST               6        /* PRTC1 (gdTSSTransmitter), 3~15 */

//#define CASM               81       /* PRTC1 (gdCASRxLowMax), 67~99 */
#define CASM               67       /* PRTC1 (gdCASRxLowMax), 67~99 */

#define TEST_LOAD_RATE

//#define RXW                301      /* PRTC1 (gdWakeupSymbolRxWindow), 76~301 *//* comment @Titron */
#define RXW                76      /* PRTC1 (gdWakeupSymbolRxWindow), 76~301 *//* comment @Titron */

#define RXI                59       /* PRTC2 (gdWakeupSymbolRxIdle), 14~59 *//* comment @Titron */
#define RXL                55       /* PRTC2 (gdWakeupSymbolRxLow), 10~55 *//* comment @Titron */
#define TXI                180      /* PRTC2 (gdWakeupSymbolTxIdle), 45~180 *//* comment @Titron */
#define TXL                60       /* PRTC2 (gdWakeupSymbolTxLow), 15~60*//* comment @Titron */


#define SFDL               1        /* MHDC (gPayloadLengthStatic), 0~127 */
//#define SFDL               8        /* MHDC (gPayloadLengthStatic), 0~127 */



//#define MPC                16000    /* GTUC2 (gMacroPerCycle), 10~16000 MT *//* comment @Titron */
#define MPC                150    /* GTUC2 (gMacroPerCycle), 10~16000 MT *//* comment @Titron */

//#define NIT                15401    /* GTUC4: Network Idle Time Start, 7~15997MT *//* comment @Titron */
//#define OCS                15501    /* GTUC4 (gOffsetCorrectionStart), 8~15998MT *//* comment @Titron */
#define NIT                144    /* GTUC4: Network Idle Time Start, 7~15997MT *//* comment @Titron */
#define OCS                148    /* GTUC4 (gOffsetCorrectionStart), 8~15998MT *//* comment @Titron */

#define SNM                3        /* GTUC2 (gSyncNodeMax) */

#ifndef TEST_LOAD_RATE
#define SSL                659      /* GTUC7 (gdStaticSlot) *//* comment @Titron */
#else
#define SSL                15      /* GTUC7 (gdStaticSlot), 4~659MT *//* comment @Titron */
#endif

//#define NSS                18       /* GTUC7 (gNumberOfStaticSlots), 2~1023 *//* comment @Titron */
#define NSS                9       /* GTUC7 (gNumberOfStaticSlots), 2~1023 *//* comment @Titron */


#define MSL                0        /* GTUC8 (gdMinislot) */
#define NMS                0        /* GTUC8 (gNumberOfMinislots), 0~7986 */

//#define APO                4        /* GTUC9 (gdActionPointOffset), 1~63MT *//* comment @Titron */
#define APO                1        /* GTUC9 (gdActionPointOffset), 1~63MT *//* comment @Titron */

#define MAPO               0        /* GTUC9 (gdMinislotActionPointOffset), 1~31MT */
#define DSI                0        /* GTUC9 (gdDynamicSlotIdlePhase), 0~2 */

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

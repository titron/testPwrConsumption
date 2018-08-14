/******************************************************************************/
/* Node Name     : Node_1                                                     */
/*                                                                            */
/* File          : Node_1.h                                                   */
/* Creation date : 18.04.2016, 14:30:54                                       */
/* Note          : Don't change filename or contents!                         */
/******************************************************************************/

/************************ Interrupt and Timer Setting ************************/

#define EILS_SET                    0x00000000    /* Error Interrupt Line Select */
#define SILS_SET                    0x0303FFFF    /* Status Interrupt Line Select */
#define EIES_SET                    0x07070FFF    /* Error Interrupt Enable Set */
#define SIES_SET                    0x00000000    /* Status Interrupt Enable Set */
#define ILE_SET                     0x00000000    /* Interrupt Line Enable */
#define T0C_SET                     0x00000002    /* Timer 0 Configuration */
#define T1C_SET                     0x00000000    /* Timer 1 Configuration */
#define STPW1_SET                   0x00000000    /* Stop Watch Register 1 */

/* EILS - Error Interrupt Line Select */
#define PEMCL                       0             /* POC Error Mode Changed Interrupt Line */
#define CNAL                        0             /* Command Not Accepted Interrupt Line */
#define SFBML                       0             /* Sync Frames Below Minimum Interrupt Line */
#define SFOL                        0             /* Sync Frame Overflow Interrupt Line */
#define CCFL                        0             /* Clock Correction Failure Interrupt Line */
#define CCLL                        0             /* CHI Command Locked Interrupt Line */
#define PERRL                       0             /* Parity Error Interrupt Line */
#define RFOL                        0             /* Receive FIFO Overrun Interrupt Line */
#define EFAL                        0             /* Empty FIFO Access Interrupt Line */
#define IIBAL                       0             /* Illegal Input Buffer Access Interrupt Line */
#define IOBAL                       0             /* Latest Transmit Violation Channel B Interrupt Line */
#define MHFL                        0             /* Message Handler Constraints Flag Interrupt Line */
#define EDAL                        0             /* Error Detected on Channel A Interrupt Line */
#define LTVAL                       0             /* Latest Transmit Violation Channel A Interrupt Line */
#define TABAL                       0             /* Transmission Across Boundary Channel A Interrupt Line */
#define EDBL                        0             /* Error Detected on Channel B Interrupt Line */
#define LTVBL                       0             /* Latest Transmit Violation Channel B Interrupt Line */
#define TABBL                       0             /* Transmission Across Boundary Channel B Interrupt Line */

/* SILS - Status Interrupt Line Select */
#define WSTL                        1             /* Wakeup Status Interrupt Line */
#define CASL                        1             /* Collision Avoidance Symbol Interrupt Line */
#define CYCSL                       1             /* Cycle Start Interrupt Line */
#define TXIL                        1             /* Transmit Interrupt Line */
#define RXIL                        1             /* Receive Interrupt Line */
#define RFNEL                       1             /* Receive FIFO Not Empty Interrupt Line */
#define RFCLL                       1             /* Receive FIFO Critical Level Interrupt Line */
#define NMVCL                       1             /* Network Management Vector Changed Interrupt Line */
#define TI0L                        1             /* Timer Interrupt 0 Line */
#define TI1L                        1             /* Timer Interrupt 1 Line */
#define TIBCL                       1             /* Transfer Input Buffer Completed Interrupt Line */
#define TOBCL                       1             /* Transfer Output Buffer Completed Interrupt Line */
#define SWEL                        1             /* Stop Watch Event Interrupt Line */
#define SUCSL                       1             /* Startup Completed Successfully Interrupt Line */
#define MBSIL                       1             /* Message Buffer Status Interrupt Line */
#define SDSL                        1             /* Start of Dynamic Segment Interrupt Line */
#define WUPAL                       1             /* Wakeup Pattern Channel A Interrupt Line */
#define MTSAL                       1             /* Media Access Test Symbol Channel A Interrupt Line */
#define WUPBL                       1             /* Wakeup Pattern Channel B Interrupt Line */
#define MTSBL                       1             /* Media Access Test Symbol Channel B Interrupt Line */

/* EIES - Error Interrupt Enable Set Register */
#define PEMCE                       1             /* POC Error Mode Changed Interrupt Enable */
#define CNAE                        1             /* Command Not Accepted Interrupt Enable */
#define SFBME                       1             /* Sync Frames Below Minimum Interrupt Enable */
#define SFOE                        1             /* Sync Frame Overflow Interrupt Enable */
#define CCFE                        1             /* Clock Correction Failure Interrupt Enable */
#define CCLE                        1             /* CHI Command Locked Interrupt Enable */
#define PERRE                       1             /* Parity Error Interrupt Enable */
#define RFOE                        1             /* Receive FIFO Overrun Interrupt Enable */
#define EFAE                        1             /* Empty FIFO Access Interrupt Enable */
#define IIBAE                       1             /* Illegal Input Buffer Access Interrupt Enable */
#define IOBAE                       1             /* Latest Transmit Violation Channel B Interrupt Enable */
#define MHFE                        1             /* Message Handler Constraints Flag Interrupt Enable */
#define EDAE                        1             /* Error Detected on Channel A Interrupt Enable */
#define LTVAE                       1             /* Latest Transmit Violation Channel A Interrupt Enable */
#define TABAE                       1             /* Transmission Across Boundary Channel A Interrupt Enable */
#define EDBE                        1             /* Error Detected on Channel B Interrupt Enable */
#define LTVBE                       1             /* Latest Transmit Violation Channel B Interrupt Enable */
#define TABBE                       1             /* Transmission Across Boundary Channel B Interrupt Enable */

/* SIES - Status Interrupt Enable Set Register */
#define WSTE                        1             /* Wakeup Status Interrupt Enable */
#define CASE                        1             /* Collision Avoidance Symbol Interrupt Enable */
#define CYCSE                       1             /* Cycle Start Interrupt Enable */
#define TXIE                        1             /* Transmit Interrupt Enable */
#define RXIE                        1             /* Receive Interrupt Enable */
#define RFNEE                       1             /* Receive FIFO Not Empty Interrupt Enable */
#define RFCLE                       1             /* Receive FIFO Critical Level Interrupt Enable */
#define NMVCE                       1             /* Network Management Vector Changed Interrupt Enable */
#define TI0E                        1             /* Timer Interrupt 0 Enable */
#define TI1E                        1             /* Timer Interrupt 1 Enable */
#define TIBCE                       1             /* Transfer Input Buffer Completed Enable */
#define TOBCE                       1             /* Transfer Output Buffer Completed Enable */
#define SWEE                        1             /* Stop Watch Event Interrupt Enable */
#define SUCSE                       1             /* Startup Completed Successfully Interrupt Enable */
#define MBSIE                       1             /* Message Buffer Status Interrupt Enable */
#define SDSE                        1             /* Start of Dynamic Segment Interrupt Enable */
#define WUPAE                       1             /* Wakeup Pattern Channel A  Interrupt Enable */
#define MTSAE                       1             /* MTS Received on Channel A Interrupt Enable */
#define WUPBE                       1             /* Wakeup Pattern Channel B Interrupt Enable */
#define MTSBE                       1             /* MTS Received on Channel B Interrupt Enable */

/* ILE - Interrupt Line Enable Configuration Register */
#define EINT0                       0             /* Enable Interrupt Line 0 */
#define EINT1                       0             /* Enable Interrupt Line 1 */

/* T0C - Timer Interrupt 0 Configuration Register */
#define T0MS                        1             /* Timer 0 Mode Select */
#define T0CC                        0             /* Timer 0 Cycle Code */
#define T0MO                        0             /* Timer 0 Macrotick Offset */

/* TI1CR - Timer Interrupt 1 Configuration Register */
#define T1MS                        0             /* Timer 1 Mode Select */
#define T1MC                        0             /* Timer 1 Macrotick Count */

/* STPW1 - Stop Watch Register 1 */
#define ESWT                        0             /* External Stop Watch Trigger */
#define SWMS                        0             /* Stop Watch Mode Select */
#define EDGE                        0             /* Stop Watch Trigger Edge Select */
#define SSWT                        0             /* Software Stop Watch Trigger */
#define EETP                        0             /* Enable External Trigger Pin */
#define EINT0_S                     0             /* Enable Interrupt 0 Trigger */
#define EINT1_S                     0             /* Enable Interrupt 1 Trigger */


/*************************** CC Control Registers ****************************/

#define SUCC1_SET                   0x0C0F1300    /* SUC Configuration Register 1 (0x0080) */
#define SUCC2_SET                   0x01139706    /* SUC Configuration Register 2 (0x0084) */
#define SUCC3_SET                   0x00000011    /* SUC Configuration Register 3 (0x0088) */
#define NEMC_SET                    0x00000000    /* NEM Configuration Register (0x008C) */
#define PRTC1_SET                   0x092D0516    /* PRT Configuration Register 1 (0x0090) */
#define PRTC2_SET                   0x3CB4373B    /* PRT Configuration Register 2 (0x009C) */
#define MHDC_SET                    0x00000001    /* MHD Configuration Register (0x0098) */
#define GTUC1_SET                   0x0009C400    /* GTU Configuration Register 1 (0x00A0) */
#define GTUC2_SET                   0x00033E80    /* GTU Configuration Register 2 (0x00A4) */
#define GTUC3_SET                   0x05050404    /* GTU Configuration Register 3 (0x00A8) */
#define GTUC4_SET                   0x3C8D3C29    /* GTU Configuration Register 4 (0x00AC) */
#define GTUC5_SET                   0x24010000    /* GTU Configuration Register 5 (0x00B0) */
#define GTUC6_SET                   0x07830753    /* GTU Configuration Register 6 (0x00B4) */
#define GTUC7_SET                   0x00120293    /* GTU Configuration Register 7 (0x00B8) */
#define GTUC8_SET                   0x00000000    /* GTU Configuration Register 8 (0x00BC) */
#define GTUC9_SET                   0x00000004    /* GTU Configuration Register 9 (0x00C0) */
#define GTUC10_SET                  0x07830086    /* GTU Configuration Register 10 (0x00C4) */
#define GTUC11_SET                  0x00000000    /* GTU Configuration Register 11 (0x00C8) */

#define TXST                        1             /* SUCC1 (pKeySlotUsedForStartup) */
#define TXSY                        1             /* SUCC1 (pKeySlotUsedForSync) */
#define PTA                         15            /* SUCC1 (pAllowPassiveToActive) */
#define WUCS                        0             /* SUCC1 (pWakeupChannel) ( A:0, B:1 ) */
#define TSM                         0             /* SUCC1 (pSingleSlotEnabled) */
#define HCSE                        0             /* SUCC1 (pAllowHaltDueToClock) */
#define MTSA                        0             /* SUCC1: Select Channel A for MTS Transmission */
#define MTSB                        0             /* SUCC1: Select Channel B for MTS Transmission */
#define CCHA                        1             /* SUCC1 (pChannels) */
#define CCHB                        1             /* SUCC1 (pChannels) */
#define LT                          1284       /* SUCC2 (pdListenTimeout) */
#define SPP                         0             /* PRTC1: Strobe Point Position */
#define BRP                         0             /* PRTC1: Baud Rate Prescaler */
#define RWP                         2             /* PRTC1 (pWakeupPattern) */
#define SLT                         0             /* MHDC (pLatestTx) */
#define UT                          12000        /* GTUC1 (pMicroPerCycle), 640~640000uT *//* comment @Titron */
#define UIOA                        4             /* GTUC3 (pMicroInitialOffset[A]) */
#define UIOB                        4             /* GTUC3 (pMicroInitialOffset[B]) */
#define MIOA                        5             /* GTUC3 (pMacroInitialOffset[A]) */
#define MIOB                        5             /* GTUC3 (pMacroInitialOffset[B]) */
#define DCA                         0             /* GTUC5 (pDelayCompensation[A]) */
#define DCB                         0             /* GTUC5 (pDelayCompensation[B]) */
#define CDD                         1             /* GTUC5 (pClusterDriftDamping) */
#define DEC                         36            /* GTUC5 (pDecodingCorrection) */
#define ASR                         1875          /* GTUC6 (pdAcceptedStartupRange) */
#define MOD                         1923          /* GTUC6 (pdMaxDrift) */
#define MOC                         134           /* GTUC10 (pOffsetCorrectionOut) */
#define MRC                         1923          /* GTUC10 (pRateCorrectionOut) */
#define EOCC                        0             /* GTUC11: External Offset Correction Control (vExternOffsetControl) */
#define ERCC                        0             /* GTUC11: External Rate Correction Control (vExternRateControl) */
#define EOC                         0             /* GTUC11 (pExternOffsetCorrection) */
#define ERC                         0             /* GTUC11 (pExternRateCorrection) */

/*************************** Message Buffer Control Registers ****************************/

#define MRAMC_SET                   0x01088080    /* Message RAM Configuration (0x0300) */
#define FRF_SET                     0x01800000    /* FIFO Rejection Filter (0x0304) */
#define FRFM_SET                    0x00000000    /* FIFO Rejection Filter Mask (0x0308) */
#define FCL_SET                     0x00000080    /* FIFO Critical Level (0x030C) */

#define FDB                         128           /* MRC: First Dynamic Buffer */
#define FFB                         128           /* MRC: First FIFO Buffer */
#define LCB                         8             /* MRC: Last Configured Buffer */
#define SEC                         1             /* MRC: Secure Buffers */
#define SPLM                        0             /* MRC: Sync Frame Payload Multiplex */
#define CHA                         0             /* FRF: Channel Filter */
#define CHB                         0             /* FRF: Channel Filter */
#define FID                         0             /* FRF: Frame ID Filter */
#define CYF                         0             /* FRF: Cycle Code Filter */
#define RSS                         1             /* FRF: Reject Static Segment */
#define RNF                         1             /* FRF: Reject Null Frames */
#define MFID                        0             /* FRFM: FIFO Rejection Filter Mask Bits */
#define CL                          128           /* FCL: FIFO Critical Level */

/* Followings can't be set in E-Ray. */

/* KeySlotId                        1 */
/* pSamplesPerMicrotick             2 */
/* Sample_Clock                     80 */
/* E-Ray_Clock                      64 */
/* Number_of_FIFO_buffers           0 */
/* TxNumOfDynframe_chA              0 */
/* TxNumOfDynframe_chB              0 */
/* RxNumOfDynframe_chA              0 */
/* RxNumOfDynframe_chB              0 */

/*---------------------- Ch A ( Dynamic Segment ) ----------------------*/


/*---------------------- Ch B ( Dynamic Segment ) ----------------------*/


/************************** Each Slot Status **************************/

/*-------------------------------- ChA(Tx) --------------------------------*/

/* Tx_slot01_A                      1 */
/* Tx_slot02_A                      0 */
/* Tx_slot03_A                      0 */
/* Tx_slot04_A                      0 */
/* Tx_slot05_A                      1 */
/* Tx_slot06_A                      0 */
/* Tx_slot07_A                      0 */
/* Tx_slot08_A                      0 */
/* Tx_slot09_A                      1 */
/* Tx_slot10_A                      0 */
/* Tx_slot11_A                      0 */
/* Tx_slot12_A                      0 */
/* Tx_slot13_A                      0 */
/* Tx_slot14_A                      0 */
/* Tx_slot15_A                      0 */
/* Tx_slot16_A                      0 */
/* Tx_slot17_A                      1 */
/* Tx_slot18_A                      0 */
/* Tx_slot19_A                      0 */
/* Tx_slot20_A                      0 */
/* Tx_slot21_A                      0 */
/* Tx_slot22_A                      0 */
/* Tx_slot23_A                      0 */
/* Tx_slot24_A                      0 */
/* Tx_slot25_A                      0 */
/* Tx_slot26_A                      0 */
/* Tx_slot27_A                      0 */
/* Tx_slot28_A                      0 */
/* Tx_slot29_A                      0 */
/* Tx_slot30_A                      0 */
/* Tx_slot31_A                      0 */
/* Tx_slot32_A                      0 */
/* Tx_slot33_A                      0 */
/* Tx_slot34_A                      0 */
/* Tx_slot35_A                      0 */
/* Tx_slot36_A                      0 */
/* Tx_slot37_A                      0 */
/* Tx_slot38_A                      0 */
/* Tx_slot39_A                      0 */
/* Tx_slot40_A                      0 */
/* Tx_slot41_A                      0 */
/* Tx_slot42_A                      0 */
/* Tx_slot43_A                      0 */
/* Tx_slot44_A                      0 */
/* Tx_slot45_A                      0 */
/* Tx_slot46_A                      0 */
/* Tx_slot47_A                      0 */
/* Tx_slot48_A                      0 */
/* Tx_slot49_A                      0 */
/* Tx_slot50_A                      0 */
/* Tx_slot51_A                      0 */
/* Tx_slot52_A                      0 */
/* Tx_slot53_A                      0 */
/* Tx_slot54_A                      0 */
/* Tx_slot55_A                      0 */
/* Tx_slot56_A                      0 */
/* Tx_slot57_A                      0 */
/* Tx_slot58_A                      0 */
/* Tx_slot59_A                      0 */
/* Tx_slot60_A                      0 */
/* Tx_slot61_A                      0 */
/* Tx_slot62_A                      0 */
/* Tx_slot63_A                      0 */
/* Tx_slot64_A                      0 */
/* Tx_slot65_A                      0 */
/* Tx_slot66_A                      0 */
/* Tx_slot67_A                      0 */
/* Tx_slot68_A                      0 */
/* Tx_slot69_A                      0 */
/* Tx_slot70_A                      0 */
/* Tx_slot71_A                      0 */
/* Tx_slot72_A                      0 */
/* Tx_slot73_A                      0 */
/* Tx_slot74_A                      0 */
/* Tx_slot75_A                      0 */
/* Tx_slot76_A                      0 */
/* Tx_slot77_A                      0 */
/* Tx_slot78_A                      0 */
/* Tx_slot79_A                      0 */
/* Tx_slot80_A                      0 */
/* Tx_slot81_A                      0 */
/* Tx_slot82_A                      0 */
/* Tx_slot83_A                      0 */
/* Tx_slot84_A                      0 */
/* Tx_slot85_A                      0 */
/* Tx_slot86_A                      0 */
/* Tx_slot87_A                      0 */
/* Tx_slot88_A                      0 */
/* Tx_slot89_A                      0 */
/* Tx_slot90_A                      0 */
/* Tx_slot91_A                      0 */
/* Tx_slot92_A                      0 */
/* Tx_slot93_A                      0 */
/* Tx_slot94_A                      0 */
/* Tx_slot95_A                      0 */
/* Tx_slot96_A                      0 */
/* Tx_slot97_A                      0 */
/* Tx_slot98_A                      0 */
/* Tx_slot99_A                      0 */
/* Tx_slot100_A                     0 */
/* Tx_slot101_A                     0 */
/* Tx_slot102_A                     0 */
/* Tx_slot103_A                     0 */
/* Tx_slot104_A                     0 */
/* Tx_slot105_A                     0 */
/* Tx_slot106_A                     0 */
/* Tx_slot107_A                     0 */
/* Tx_slot108_A                     0 */
/* Tx_slot109_A                     0 */
/* Tx_slot110_A                     0 */
/* Tx_slot111_A                     0 */
/* Tx_slot112_A                     0 */
/* Tx_slot113_A                     0 */
/* Tx_slot114_A                     0 */
/* Tx_slot115_A                     0 */
/* Tx_slot116_A                     0 */
/* Tx_slot117_A                     0 */
/* Tx_slot118_A                     0 */
/* Tx_slot119_A                     0 */
/* Tx_slot120_A                     0 */
/* Tx_slot121_A                     0 */
/* Tx_slot122_A                     0 */
/* Tx_slot123_A                     0 */
/* Tx_slot124_A                     0 */
/* Tx_slot125_A                     0 */
/* Tx_slot126_A                     0 */
/* Tx_slot127_A                     0 */
/* Tx_slot128_A                     0 */

/*-------------------------------- ChB(Tx) --------------------------------*/

/* Tx_slot01_B                      1 */
/* Tx_slot02_B                      0 */
/* Tx_slot03_B                      0 */
/* Tx_slot04_B                      0 */
/* Tx_slot05_B                      1 */
/* Tx_slot06_B                      0 */
/* Tx_slot07_B                      0 */
/* Tx_slot08_B                      0 */
/* Tx_slot09_B                      1 */
/* Tx_slot10_B                      0 */
/* Tx_slot11_B                      0 */
/* Tx_slot12_B                      0 */
/* Tx_slot13_B                      1 */
/* Tx_slot14_B                      0 */
/* Tx_slot15_B                      0 */
/* Tx_slot16_B                      0 */
/* Tx_slot17_B                      0 */
/* Tx_slot18_B                      0 */
/* Tx_slot19_B                      0 */
/* Tx_slot20_B                      0 */
/* Tx_slot21_B                      0 */
/* Tx_slot22_B                      0 */
/* Tx_slot23_B                      0 */
/* Tx_slot24_B                      0 */
/* Tx_slot25_B                      0 */
/* Tx_slot26_B                      0 */
/* Tx_slot27_B                      0 */
/* Tx_slot28_B                      0 */
/* Tx_slot29_B                      0 */
/* Tx_slot30_B                      0 */
/* Tx_slot31_B                      0 */
/* Tx_slot32_B                      0 */
/* Tx_slot33_B                      0 */
/* Tx_slot34_B                      0 */
/* Tx_slot35_B                      0 */
/* Tx_slot36_B                      0 */
/* Tx_slot37_B                      0 */
/* Tx_slot38_B                      0 */
/* Tx_slot39_B                      0 */
/* Tx_slot40_B                      0 */
/* Tx_slot41_B                      0 */
/* Tx_slot42_B                      0 */
/* Tx_slot43_B                      0 */
/* Tx_slot44_B                      0 */
/* Tx_slot45_B                      0 */
/* Tx_slot46_B                      0 */
/* Tx_slot47_B                      0 */
/* Tx_slot48_B                      0 */
/* Tx_slot49_B                      0 */
/* Tx_slot50_B                      0 */
/* Tx_slot51_B                      0 */
/* Tx_slot52_B                      0 */
/* Tx_slot53_B                      0 */
/* Tx_slot54_B                      0 */
/* Tx_slot55_B                      0 */
/* Tx_slot56_B                      0 */
/* Tx_slot57_B                      0 */
/* Tx_slot58_B                      0 */
/* Tx_slot59_B                      0 */
/* Tx_slot60_B                      0 */
/* Tx_slot61_B                      0 */
/* Tx_slot62_B                      0 */
/* Tx_slot63_B                      0 */
/* Tx_slot64_B                      0 */
/* Tx_slot65_B                      0 */
/* Tx_slot66_B                      0 */
/* Tx_slot67_B                      0 */
/* Tx_slot68_B                      0 */
/* Tx_slot69_B                      0 */
/* Tx_slot70_B                      0 */
/* Tx_slot71_B                      0 */
/* Tx_slot72_B                      0 */
/* Tx_slot73_B                      0 */
/* Tx_slot74_B                      0 */
/* Tx_slot75_B                      0 */
/* Tx_slot76_B                      0 */
/* Tx_slot77_B                      0 */
/* Tx_slot78_B                      0 */
/* Tx_slot79_B                      0 */
/* Tx_slot80_B                      0 */
/* Tx_slot81_B                      0 */
/* Tx_slot82_B                      0 */
/* Tx_slot83_B                      0 */
/* Tx_slot84_B                      0 */
/* Tx_slot85_B                      0 */
/* Tx_slot86_B                      0 */
/* Tx_slot87_B                      0 */
/* Tx_slot88_B                      0 */
/* Tx_slot89_B                      0 */
/* Tx_slot90_B                      0 */
/* Tx_slot91_B                      0 */
/* Tx_slot92_B                      0 */
/* Tx_slot93_B                      0 */
/* Tx_slot94_B                      0 */
/* Tx_slot95_B                      0 */
/* Tx_slot96_B                      0 */
/* Tx_slot97_B                      0 */
/* Tx_slot98_B                      0 */
/* Tx_slot99_B                      0 */
/* Tx_slot100_B                     0 */
/* Tx_slot101_B                     0 */
/* Tx_slot102_B                     0 */
/* Tx_slot103_B                     0 */
/* Tx_slot104_B                     0 */
/* Tx_slot105_B                     0 */
/* Tx_slot106_B                     0 */
/* Tx_slot107_B                     0 */
/* Tx_slot108_B                     0 */
/* Tx_slot109_B                     0 */
/* Tx_slot110_B                     0 */
/* Tx_slot111_B                     0 */
/* Tx_slot112_B                     0 */
/* Tx_slot113_B                     0 */
/* Tx_slot114_B                     0 */
/* Tx_slot115_B                     0 */
/* Tx_slot116_B                     0 */
/* Tx_slot117_B                     0 */
/* Tx_slot118_B                     0 */
/* Tx_slot119_B                     0 */
/* Tx_slot120_B                     0 */
/* Tx_slot121_B                     0 */
/* Tx_slot122_B                     0 */
/* Tx_slot123_B                     0 */
/* Tx_slot124_B                     0 */
/* Tx_slot125_B                     0 */
/* Tx_slot126_B                     0 */
/* Tx_slot127_B                     0 */
/* Tx_slot128_B                     0 */

/*-------------------------------- ChA(Rx) --------------------------------*/

/* Rx_slot01_A                      0 */
/* Rx_slot02_A                      0 */
/* Rx_slot03_A                      1 */
/* Rx_slot04_A                      0 */
/* Rx_slot05_A                      0 */
/* Rx_slot06_A                      0 */
/* Rx_slot07_A                      1 */
/* Rx_slot08_A                      0 */
/* Rx_slot09_A                      0 */
/* Rx_slot10_A                      0 */
/* Rx_slot11_A                      1 */
/* Rx_slot12_A                      0 */
/* Rx_slot13_A                      0 */
/* Rx_slot14_A                      0 */
/* Rx_slot15_A                      0 */
/* Rx_slot16_A                      0 */
/* Rx_slot17_A                      0 */
/* Rx_slot18_A                      0 */
/* Rx_slot19_A                      0 */
/* Rx_slot20_A                      0 */
/* Rx_slot21_A                      0 */
/* Rx_slot22_A                      0 */
/* Rx_slot23_A                      0 */
/* Rx_slot24_A                      0 */
/* Rx_slot25_A                      0 */
/* Rx_slot26_A                      0 */
/* Rx_slot27_A                      0 */
/* Rx_slot28_A                      0 */
/* Rx_slot29_A                      0 */
/* Rx_slot30_A                      0 */
/* Rx_slot31_A                      0 */
/* Rx_slot32_A                      0 */
/* Rx_slot33_A                      0 */
/* Rx_slot34_A                      0 */
/* Rx_slot35_A                      0 */
/* Rx_slot36_A                      0 */
/* Rx_slot37_A                      0 */
/* Rx_slot38_A                      0 */
/* Rx_slot39_A                      0 */
/* Rx_slot40_A                      0 */
/* Rx_slot41_A                      0 */
/* Rx_slot42_A                      0 */
/* Rx_slot43_A                      0 */
/* Rx_slot44_A                      0 */
/* Rx_slot45_A                      0 */
/* Rx_slot46_A                      0 */
/* Rx_slot47_A                      0 */
/* Rx_slot48_A                      0 */
/* Rx_slot49_A                      0 */
/* Rx_slot50_A                      0 */
/* Rx_slot51_A                      0 */
/* Rx_slot52_A                      0 */
/* Rx_slot53_A                      0 */
/* Rx_slot54_A                      0 */
/* Rx_slot55_A                      0 */
/* Rx_slot56_A                      0 */
/* Rx_slot57_A                      0 */
/* Rx_slot58_A                      0 */
/* Rx_slot59_A                      0 */
/* Rx_slot60_A                      0 */
/* Rx_slot61_A                      0 */
/* Rx_slot62_A                      0 */
/* Rx_slot63_A                      0 */
/* Rx_slot64_A                      0 */
/* Rx_slot65_A                      0 */
/* Rx_slot66_A                      0 */
/* Rx_slot67_A                      0 */
/* Rx_slot68_A                      0 */
/* Rx_slot69_A                      0 */
/* Rx_slot70_A                      0 */
/* Rx_slot71_A                      0 */
/* Rx_slot72_A                      0 */
/* Rx_slot73_A                      0 */
/* Rx_slot74_A                      0 */
/* Rx_slot75_A                      0 */
/* Rx_slot76_A                      0 */
/* Rx_slot77_A                      0 */
/* Rx_slot78_A                      0 */
/* Rx_slot79_A                      0 */
/* Rx_slot80_A                      0 */
/* Rx_slot81_A                      0 */
/* Rx_slot82_A                      0 */
/* Rx_slot83_A                      0 */
/* Rx_slot84_A                      0 */
/* Rx_slot85_A                      0 */
/* Rx_slot86_A                      0 */
/* Rx_slot87_A                      0 */
/* Rx_slot88_A                      0 */
/* Rx_slot89_A                      0 */
/* Rx_slot90_A                      0 */
/* Rx_slot91_A                      0 */
/* Rx_slot92_A                      0 */
/* Rx_slot93_A                      0 */
/* Rx_slot94_A                      0 */
/* Rx_slot95_A                      0 */
/* Rx_slot96_A                      0 */
/* Rx_slot97_A                      0 */
/* Rx_slot98_A                      0 */
/* Rx_slot99_A                      0 */
/* Rx_slot100_A                     0 */
/* Rx_slot101_A                     0 */
/* Rx_slot102_A                     0 */
/* Rx_slot103_A                     0 */
/* Rx_slot104_A                     0 */
/* Rx_slot105_A                     0 */
/* Rx_slot106_A                     0 */
/* Rx_slot107_A                     0 */
/* Rx_slot108_A                     0 */
/* Rx_slot109_A                     0 */
/* Rx_slot110_A                     0 */
/* Rx_slot111_A                     0 */
/* Rx_slot112_A                     0 */
/* Rx_slot113_A                     0 */
/* Rx_slot114_A                     0 */
/* Rx_slot115_A                     0 */
/* Rx_slot116_A                     0 */
/* Rx_slot117_A                     0 */
/* Rx_slot118_A                     0 */
/* Rx_slot119_A                     0 */
/* Rx_slot120_A                     0 */
/* Rx_slot121_A                     0 */
/* Rx_slot122_A                     0 */
/* Rx_slot123_A                     0 */
/* Rx_slot124_A                     0 */
/* Rx_slot125_A                     0 */
/* Rx_slot126_A                     0 */
/* Rx_slot127_A                     0 */
/* Rx_slot128_A                     0 */

/*-------------------------------- ChB(Rx) --------------------------------*/

/* Rx_slot01_B                      0 */
/* Rx_slot02_B                      0 */
/* Rx_slot03_B                      1 */
/* Rx_slot04_B                      0 */
/* Rx_slot05_B                      0 */
/* Rx_slot06_B                      0 */
/* Rx_slot07_B                      1 */
/* Rx_slot08_B                      0 */
/* Rx_slot09_B                      0 */
/* Rx_slot10_B                      0 */
/* Rx_slot11_B                      0 */
/* Rx_slot12_B                      0 */
/* Rx_slot13_B                      0 */
/* Rx_slot14_B                      0 */
/* Rx_slot15_B                      1 */
/* Rx_slot16_B                      0 */
/* Rx_slot17_B                      0 */
/* Rx_slot18_B                      0 */
/* Rx_slot19_B                      0 */
/* Rx_slot20_B                      0 */
/* Rx_slot21_B                      0 */
/* Rx_slot22_B                      0 */
/* Rx_slot23_B                      0 */
/* Rx_slot24_B                      0 */
/* Rx_slot25_B                      0 */
/* Rx_slot26_B                      0 */
/* Rx_slot27_B                      0 */
/* Rx_slot28_B                      0 */
/* Rx_slot29_B                      0 */
/* Rx_slot30_B                      0 */
/* Rx_slot31_B                      0 */
/* Rx_slot32_B                      0 */
/* Rx_slot33_B                      0 */
/* Rx_slot34_B                      0 */
/* Rx_slot35_B                      0 */
/* Rx_slot36_B                      0 */
/* Rx_slot37_B                      0 */
/* Rx_slot38_B                      0 */
/* Rx_slot39_B                      0 */
/* Rx_slot40_B                      0 */
/* Rx_slot41_B                      0 */
/* Rx_slot42_B                      0 */
/* Rx_slot43_B                      0 */
/* Rx_slot44_B                      0 */
/* Rx_slot45_B                      0 */
/* Rx_slot46_B                      0 */
/* Rx_slot47_B                      0 */
/* Rx_slot48_B                      0 */
/* Rx_slot49_B                      0 */
/* Rx_slot50_B                      0 */
/* Rx_slot51_B                      0 */
/* Rx_slot52_B                      0 */
/* Rx_slot53_B                      0 */
/* Rx_slot54_B                      0 */
/* Rx_slot55_B                      0 */
/* Rx_slot56_B                      0 */
/* Rx_slot57_B                      0 */
/* Rx_slot58_B                      0 */
/* Rx_slot59_B                      0 */
/* Rx_slot60_B                      0 */
/* Rx_slot61_B                      0 */
/* Rx_slot62_B                      0 */
/* Rx_slot63_B                      0 */
/* Rx_slot64_B                      0 */
/* Rx_slot65_B                      0 */
/* Rx_slot66_B                      0 */
/* Rx_slot67_B                      0 */
/* Rx_slot68_B                      0 */
/* Rx_slot69_B                      0 */
/* Rx_slot70_B                      0 */
/* Rx_slot71_B                      0 */
/* Rx_slot72_B                      0 */
/* Rx_slot73_B                      0 */
/* Rx_slot74_B                      0 */
/* Rx_slot75_B                      0 */
/* Rx_slot76_B                      0 */
/* Rx_slot77_B                      0 */
/* Rx_slot78_B                      0 */
/* Rx_slot79_B                      0 */
/* Rx_slot80_B                      0 */
/* Rx_slot81_B                      0 */
/* Rx_slot82_B                      0 */
/* Rx_slot83_B                      0 */
/* Rx_slot84_B                      0 */
/* Rx_slot85_B                      0 */
/* Rx_slot86_B                      0 */
/* Rx_slot87_B                      0 */
/* Rx_slot88_B                      0 */
/* Rx_slot89_B                      0 */
/* Rx_slot90_B                      0 */
/* Rx_slot91_B                      0 */
/* Rx_slot92_B                      0 */
/* Rx_slot93_B                      0 */
/* Rx_slot94_B                      0 */
/* Rx_slot95_B                      0 */
/* Rx_slot96_B                      0 */
/* Rx_slot97_B                      0 */
/* Rx_slot98_B                      0 */
/* Rx_slot99_B                      0 */
/* Rx_slot100_B                     0 */
/* Rx_slot101_B                     0 */
/* Rx_slot102_B                     0 */
/* Rx_slot103_B                     0 */
/* Rx_slot104_B                     0 */
/* Rx_slot105_B                     0 */
/* Rx_slot106_B                     0 */
/* Rx_slot107_B                     0 */
/* Rx_slot108_B                     0 */
/* Rx_slot109_B                     0 */
/* Rx_slot110_B                     0 */
/* Rx_slot111_B                     0 */
/* Rx_slot112_B                     0 */
/* Rx_slot113_B                     0 */
/* Rx_slot114_B                     0 */
/* Rx_slot115_B                     0 */
/* Rx_slot116_B                     0 */
/* Rx_slot117_B                     0 */
/* Rx_slot118_B                     0 */
/* Rx_slot119_B                     0 */
/* Rx_slot120_B                     0 */
/* Rx_slot121_B                     0 */
/* Rx_slot122_B                     0 */
/* Rx_slot123_B                     0 */
/* Rx_slot124_B                     0 */
/* Rx_slot125_B                     0 */
/* Rx_slot126_B                     0 */
/* Rx_slot127_B                     0 */
/* Rx_slot128_B                     0 */

/* CYC PPIT TXM MBI */
/* CYC(0) = 0 PPIT(0) = 0 TXM(0) = 0 MBI(0) = 0 */
/* CYC(1) = 0 PPIT(1) = 0 TXM(1) = 0 MBI(1) = 0 */
/* CYC(2) = 0 PPIT(2) = 0 TXM(2) = 0 MBI(2) = 0 */
/* CYC(3) = 0 PPIT(3) = 0 TXM(3) = 0 MBI(3) = 0 */
/* CYC(4) = 0 PPIT(4) = 0 TXM(4) = 0 MBI(4) = 0 */
/* CYC(5) = 0 PPIT(5) = 0 TXM(5) = 0 MBI(5) = 0 */
/* CYC(6) = 0 PPIT(6) = 0 TXM(6) = 0 MBI(6) = 0 */
/* CYC(7) = 0 PPIT(7) = 0 TXM(7) = 0 MBI(7) = 0 */
/* CYC(8) = 0 PPIT(8) = 0 TXM(8) = 0 MBI(8) = 0 */
/* CYC(9) = 0 PPIT(9) = 0 TXM(9) = 0 MBI(9) = 0 */
/* CYC(10) = 0 PPIT(10) = 0 TXM(10) = 0 MBI(10) = 0 */
/* CYC(11) = 0 PPIT(11) = 0 TXM(11) = 0 MBI(11) = 0 */
/* CYC(12) = 0 PPIT(12) = 0 TXM(12) = 0 MBI(12) = 0 */
/* CYC(13) = 0 PPIT(13) = 0 TXM(13) = 0 MBI(13) = 0 */
/* CYC(14) = 0 PPIT(14) = 0 TXM(14) = 0 MBI(14) = 0 */
/* CYC(15) = 0 PPIT(15) = 0 TXM(15) = 0 MBI(15) = 0 */
/* CYC(16) = 0 PPIT(16) = 0 TXM(16) = 0 MBI(16) = 0 */
/* CYC(17) = 0 PPIT(17) = 0 TXM(17) = 0 MBI(17) = 0 */
/* CYC(18) = 0 PPIT(18) = 0 TXM(18) = 0 MBI(18) = 0 */
/* CYC(19) = 0 PPIT(19) = 0 TXM(19) = 0 MBI(19) = 0 */
/* CYC(20) = 0 PPIT(20) = 0 TXM(20) = 0 MBI(20) = 0 */
/* CYC(21) = 0 PPIT(21) = 0 TXM(21) = 0 MBI(21) = 0 */
/* CYC(22) = 0 PPIT(22) = 0 TXM(22) = 0 MBI(22) = 0 */
/* CYC(23) = 0 PPIT(23) = 0 TXM(23) = 0 MBI(23) = 0 */
/* CYC(24) = 0 PPIT(24) = 0 TXM(24) = 0 MBI(24) = 0 */
/* CYC(25) = 0 PPIT(25) = 0 TXM(25) = 0 MBI(25) = 0 */
/* CYC(26) = 0 PPIT(26) = 0 TXM(26) = 0 MBI(26) = 0 */
/* CYC(27) = 0 PPIT(27) = 0 TXM(27) = 0 MBI(27) = 0 */
/* CYC(28) = 0 PPIT(28) = 0 TXM(28) = 0 MBI(28) = 0 */
/* CYC(29) = 0 PPIT(29) = 0 TXM(29) = 0 MBI(29) = 0 */
/* CYC(30) = 0 PPIT(30) = 0 TXM(30) = 0 MBI(30) = 0 */
/* CYC(31) = 0 PPIT(31) = 0 TXM(31) = 0 MBI(31) = 0 */
/* CYC(32) = 0 PPIT(32) = 0 TXM(32) = 0 MBI(32) = 0 */
/* CYC(33) = 0 PPIT(33) = 0 TXM(33) = 0 MBI(33) = 0 */
/* CYC(34) = 0 PPIT(34) = 0 TXM(34) = 0 MBI(34) = 0 */
/* CYC(35) = 0 PPIT(35) = 0 TXM(35) = 0 MBI(35) = 0 */
/* CYC(36) = 0 PPIT(36) = 0 TXM(36) = 0 MBI(36) = 0 */
/* CYC(37) = 0 PPIT(37) = 0 TXM(37) = 0 MBI(37) = 0 */
/* CYC(38) = 0 PPIT(38) = 0 TXM(38) = 0 MBI(38) = 0 */
/* CYC(39) = 0 PPIT(39) = 0 TXM(39) = 0 MBI(39) = 0 */
/* CYC(40) = 0 PPIT(40) = 0 TXM(40) = 0 MBI(40) = 0 */
/* CYC(41) = 0 PPIT(41) = 0 TXM(41) = 0 MBI(41) = 0 */
/* CYC(42) = 0 PPIT(42) = 0 TXM(42) = 0 MBI(42) = 0 */
/* CYC(43) = 0 PPIT(43) = 0 TXM(43) = 0 MBI(43) = 0 */
/* CYC(44) = 0 PPIT(44) = 0 TXM(44) = 0 MBI(44) = 0 */
/* CYC(45) = 0 PPIT(45) = 0 TXM(45) = 0 MBI(45) = 0 */
/* CYC(46) = 0 PPIT(46) = 0 TXM(46) = 0 MBI(46) = 0 */
/* CYC(47) = 0 PPIT(47) = 0 TXM(47) = 0 MBI(47) = 0 */
/* CYC(48) = 0 PPIT(48) = 0 TXM(48) = 0 MBI(48) = 0 */
/* CYC(49) = 0 PPIT(49) = 0 TXM(49) = 0 MBI(49) = 0 */
/* CYC(50) = 0 PPIT(50) = 0 TXM(50) = 0 MBI(50) = 0 */
/* CYC(51) = 0 PPIT(51) = 0 TXM(51) = 0 MBI(51) = 0 */
/* CYC(52) = 0 PPIT(52) = 0 TXM(52) = 0 MBI(52) = 0 */
/* CYC(53) = 0 PPIT(53) = 0 TXM(53) = 0 MBI(53) = 0 */
/* CYC(54) = 0 PPIT(54) = 0 TXM(54) = 0 MBI(54) = 0 */
/* CYC(55) = 0 PPIT(55) = 0 TXM(55) = 0 MBI(55) = 0 */
/* CYC(56) = 0 PPIT(56) = 0 TXM(56) = 0 MBI(56) = 0 */
/* CYC(57) = 0 PPIT(57) = 0 TXM(57) = 0 MBI(57) = 0 */
/* CYC(58) = 0 PPIT(58) = 0 TXM(58) = 0 MBI(58) = 0 */
/* CYC(59) = 0 PPIT(59) = 0 TXM(59) = 0 MBI(59) = 0 */
/* CYC(60) = 0 PPIT(60) = 0 TXM(60) = 0 MBI(60) = 0 */
/* CYC(61) = 0 PPIT(61) = 0 TXM(61) = 0 MBI(61) = 0 */
/* CYC(62) = 0 PPIT(62) = 0 TXM(62) = 0 MBI(62) = 0 */
/* CYC(63) = 0 PPIT(63) = 0 TXM(63) = 0 MBI(63) = 0 */
/* CYC(64) = 0 PPIT(64) = 0 TXM(64) = 0 MBI(64) = 0 */
/* CYC(65) = 0 PPIT(65) = 0 TXM(65) = 0 MBI(65) = 0 */
/* CYC(66) = 0 PPIT(66) = 0 TXM(66) = 0 MBI(66) = 0 */
/* CYC(67) = 0 PPIT(67) = 0 TXM(67) = 0 MBI(67) = 0 */
/* CYC(68) = 0 PPIT(68) = 0 TXM(68) = 0 MBI(68) = 0 */
/* CYC(69) = 0 PPIT(69) = 0 TXM(69) = 0 MBI(69) = 0 */
/* CYC(70) = 0 PPIT(70) = 0 TXM(70) = 0 MBI(70) = 0 */
/* CYC(71) = 0 PPIT(71) = 0 TXM(71) = 0 MBI(71) = 0 */
/* CYC(72) = 0 PPIT(72) = 0 TXM(72) = 0 MBI(72) = 0 */
/* CYC(73) = 0 PPIT(73) = 0 TXM(73) = 0 MBI(73) = 0 */
/* CYC(74) = 0 PPIT(74) = 0 TXM(74) = 0 MBI(74) = 0 */
/* CYC(75) = 0 PPIT(75) = 0 TXM(75) = 0 MBI(75) = 0 */
/* CYC(76) = 0 PPIT(76) = 0 TXM(76) = 0 MBI(76) = 0 */
/* CYC(77) = 0 PPIT(77) = 0 TXM(77) = 0 MBI(77) = 0 */
/* CYC(78) = 0 PPIT(78) = 0 TXM(78) = 0 MBI(78) = 0 */
/* CYC(79) = 0 PPIT(79) = 0 TXM(79) = 0 MBI(79) = 0 */
/* CYC(80) = 0 PPIT(80) = 0 TXM(80) = 0 MBI(80) = 0 */
/* CYC(81) = 0 PPIT(81) = 0 TXM(81) = 0 MBI(81) = 0 */
/* CYC(82) = 0 PPIT(82) = 0 TXM(82) = 0 MBI(82) = 0 */
/* CYC(83) = 0 PPIT(83) = 0 TXM(83) = 0 MBI(83) = 0 */
/* CYC(84) = 0 PPIT(84) = 0 TXM(84) = 0 MBI(84) = 0 */
/* CYC(85) = 0 PPIT(85) = 0 TXM(85) = 0 MBI(85) = 0 */
/* CYC(86) = 0 PPIT(86) = 0 TXM(86) = 0 MBI(86) = 0 */
/* CYC(87) = 0 PPIT(87) = 0 TXM(87) = 0 MBI(87) = 0 */
/* CYC(88) = 0 PPIT(88) = 0 TXM(88) = 0 MBI(88) = 0 */
/* CYC(89) = 0 PPIT(89) = 0 TXM(89) = 0 MBI(89) = 0 */
/* CYC(90) = 0 PPIT(90) = 0 TXM(90) = 0 MBI(90) = 0 */
/* CYC(91) = 0 PPIT(91) = 0 TXM(91) = 0 MBI(91) = 0 */
/* CYC(92) = 0 PPIT(92) = 0 TXM(92) = 0 MBI(92) = 0 */
/* CYC(93) = 0 PPIT(93) = 0 TXM(93) = 0 MBI(93) = 0 */
/* CYC(94) = 0 PPIT(94) = 0 TXM(94) = 0 MBI(94) = 0 */
/* CYC(95) = 0 PPIT(95) = 0 TXM(95) = 0 MBI(95) = 0 */
/* CYC(96) = 0 PPIT(96) = 0 TXM(96) = 0 MBI(96) = 0 */
/* CYC(97) = 0 PPIT(97) = 0 TXM(97) = 0 MBI(97) = 0 */
/* CYC(98) = 0 PPIT(98) = 0 TXM(98) = 0 MBI(98) = 0 */
/* CYC(99) = 0 PPIT(99) = 0 TXM(99) = 0 MBI(99) = 0 */
/* CYC(100) = 0 PPIT(100) = 0 TXM(100) = 0 MBI(100) = 0 */
/* CYC(101) = 0 PPIT(101) = 0 TXM(101) = 0 MBI(101) = 0 */
/* CYC(102) = 0 PPIT(102) = 0 TXM(102) = 0 MBI(102) = 0 */
/* CYC(103) = 0 PPIT(103) = 0 TXM(103) = 0 MBI(103) = 0 */
/* CYC(104) = 0 PPIT(104) = 0 TXM(104) = 0 MBI(104) = 0 */
/* CYC(105) = 0 PPIT(105) = 0 TXM(105) = 0 MBI(105) = 0 */
/* CYC(106) = 0 PPIT(106) = 0 TXM(106) = 0 MBI(106) = 0 */
/* CYC(107) = 0 PPIT(107) = 0 TXM(107) = 0 MBI(107) = 0 */
/* CYC(108) = 0 PPIT(108) = 0 TXM(108) = 0 MBI(108) = 0 */
/* CYC(109) = 0 PPIT(109) = 0 TXM(109) = 0 MBI(109) = 0 */
/* CYC(110) = 0 PPIT(110) = 0 TXM(110) = 0 MBI(110) = 0 */
/* CYC(111) = 0 PPIT(111) = 0 TXM(111) = 0 MBI(111) = 0 */
/* CYC(112) = 0 PPIT(112) = 0 TXM(112) = 0 MBI(112) = 0 */
/* CYC(113) = 0 PPIT(113) = 0 TXM(113) = 0 MBI(113) = 0 */
/* CYC(114) = 0 PPIT(114) = 0 TXM(114) = 0 MBI(114) = 0 */
/* CYC(115) = 0 PPIT(115) = 0 TXM(115) = 0 MBI(115) = 0 */
/* CYC(116) = 0 PPIT(116) = 0 TXM(116) = 0 MBI(116) = 0 */
/* CYC(117) = 0 PPIT(117) = 0 TXM(117) = 0 MBI(117) = 0 */
/* CYC(118) = 0 PPIT(118) = 0 TXM(118) = 0 MBI(118) = 0 */
/* CYC(119) = 0 PPIT(119) = 0 TXM(119) = 0 MBI(119) = 0 */
/* CYC(120) = 0 PPIT(120) = 0 TXM(120) = 0 MBI(120) = 0 */
/* CYC(121) = 0 PPIT(121) = 0 TXM(121) = 0 MBI(121) = 0 */
/* CYC(122) = 0 PPIT(122) = 0 TXM(122) = 0 MBI(122) = 0 */
/* CYC(123) = 0 PPIT(123) = 0 TXM(123) = 0 MBI(123) = 0 */
/* CYC(124) = 0 PPIT(124) = 0 TXM(124) = 0 MBI(124) = 0 */
/* CYC(125) = 0 PPIT(125) = 0 TXM(125) = 0 MBI(125) = 0 */
/* CYC(126) = 0 PPIT(126) = 0 TXM(126) = 0 MBI(126) = 0 */
/* CYC(127) = 0 PPIT(127) = 0 TXM(127) = 0 MBI(127) = 0 */

/*========= Message Buffer ========*/

const unsigned short BufferHeader_u16[128][10] =
{
        /* FID,CYC,CHA,CHB,CFG,PPIT,TXM,MBI,PL,DP         Tx node */
/*MB_0*/  { 1 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 36 },    /* Node1 */
/*MB_1*/  { 3 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 1 , 37 },    /* Node2 */
/*MB_2*/  { 5 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 38 },    /* Node1 */
/*MB_3*/  { 7 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 1 , 39 },    /* Node2 */
/*MB_4*/  { 9 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 40 },    /* Node1 */
/*MB_5*/  { 11 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 41 },    /* Node2 */
/*MB_6*/  { 13 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 1 , 42 },    /* Node1 */
/*MB_7*/  { 15 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 43 },    /* Node2 */
/*MB_8*/  { 17 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 1 , 44 },    /* Node1 */
/*MB_9*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_10*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_11*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_12*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_13*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_14*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_15*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_16*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_17*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_18*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_19*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_20*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_21*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_22*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_23*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_24*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_25*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_26*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_27*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_28*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_29*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_30*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_31*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_32*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_33*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_34*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_35*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_36*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_37*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_38*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_39*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_40*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_41*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_42*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_43*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_44*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_45*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_46*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_47*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_48*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_49*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_50*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_51*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_52*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_53*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_54*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_55*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_56*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_57*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_58*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_59*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_60*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_61*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_62*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_63*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_64*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_65*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_66*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_67*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_68*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_69*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_70*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_71*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_72*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_73*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_74*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_75*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_76*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_77*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_78*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_79*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_80*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_81*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_82*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_83*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_84*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_85*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_86*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_87*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_88*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_89*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_90*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_91*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_92*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_93*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_94*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_95*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_96*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_97*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_98*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_99*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_100*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_101*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_102*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_103*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_104*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_105*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_106*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_107*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_108*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_109*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_110*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_111*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_112*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_113*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_114*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_115*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_116*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_117*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_118*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_119*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_120*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_121*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_122*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_123*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_124*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_125*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_126*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
/*MB_127*/  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 }
};

//============================================================================
// PROJECT = RSCFD Type RSCFDFD_UCIAPRCN_V3
//============================================================================
//                                 C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2017 by RENESAS Electronics (Europe) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
// Germany
//============================================================================
//Purpose: RSCFD Driver Hardware Configuration Sets
//
//Warranty Disclaimer
//
//Because the Product(s) is licensed free of charge, there is no warranty 
//of any kind whatsoever and expressly disclaimed and excluded by RENESAS, 
//either expressed or implied, including but not limited to those for 
//non-infringement of intellectual property, merchantability and/or 
//fitness for the particular purpose. 
//RENESAS shall not have any obligation to maintain, service or provide bug 
//fixes for the supplied Product(s) and/or the Application.
//
//Each User is solely responsible for determining the appropriateness of 
//using the Product(s) and assumes all risks associated with its exercise 
//of rights under this Agreement, including, but not limited to the risks 
//and costs of program errors, compliance with applicable laws, damage to 
//or loss of data, programs or equipment, and unavailability or 
//interruption of operations.
//
//Limitation of Liability
//
//In no event shall RENESAS be liable to the User for any incidental, 
//consequential, indirect, or punitive damage (including but not limited 
//to lost profits) regardless of whether such liability is based on breach 
//of contract, tort, strict liability, breach of warranties, failure of 
//essential purpose or otherwise and even if advised of the possibility of 
//such damages. RENESAS shall not be liable for any services or products 
//provided by third party vendors, developers or consultants identified or
//referred to the User by RENESAS in connection with the Product(s) and/or the 
//Application.
//
//
//
//============================================================================
// Environment: Devices:          All featuring RSCFDFD_UCIAPRCN_V3
//              Assembler:        GHS MULTI
//              C-Compiler:       GHS MULTI
//              Linker:           GHS MULTI
//              Debugger:         GHS MULTI
//============================================================================

#include <stddef.h>
#include <ree_types.h>

#define  DRIVER_LOCAL

#ifdef VLIB
#include <config_rscfd.h>

#else
#include <map_rscfd.h>
#endif

/* Default Configuration Macros */

#define EE_RSCFD_A_COMFIFO_OFF { 0, 0, 0, 0, \
                                 EE_RSCFD_FIFODL_8, 0, \
                                 EE_RSCFD_FIFO_MODE_RX, \
                                 EE_RSCFD_FIFO_IT_REFCLK, \
                                 EE_RSCFD_FIFO_IT_REFCLK1, \
                                 EE_RSCFD_FIFO_INT_ONLEVEL, \
                                 EE_RSCFD_FIFO_ILEVEL_1D8, \
                                 0, \
                                 EE_RSCFD_FIFO_DEPTH_0, \
                                 0 }                          /* COM FIFO disabled */

#define EE_RSCFD_A_RXFIFO_OFF  { 0, 0, 0, \
                                 EE_RSCFD_FIFODL_8, 0,  \
                                 EE_RSCFD_FIFO_DEPTH_0, 0, \
                                 EE_RSCFD_FIFO_INT_ONLEVEL, \
                                 EE_RSCFD_FIFO_ILEVEL_1D8, 0 } /* RX FIFO disabled */

#define EE_RSCFD_A_RXFIFO_SWGW { 1, 1, 0, \
                                 EE_RSCFD_FIFODL_64, 0,  \
                                 EE_RSCFD_FIFO_DEPTH_32, 0, \
                                 EE_RSCFD_FIFO_INT_ONEVERY, \
                                 EE_RSCFD_FIFO_ILEVEL_1D8, 0 } /* RX FIFO enabled with 64-byte*32 */

#define EE_RSCFD_A_TXQ_OFF { { EE_RSCFD_TXQ_OFF, 0, 0, 0, \
                               EE_RSCFD_TXQ_INT_ONLAST, \
                               EE_RSCFD_TXQ_OFF, 0 }, \
                             { EE_RSCFD_TXQ_OFF, 0, 0, 0, \
                               EE_RSCFD_TXQ_INT_ONLAST, \
                               EE_RSCFD_TXQ_OFF, 0 } }          /* TX Queue OFF */

#define EE_RSCFD_A_TXQ_ALL { { EE_RSCFD_TXQ_OFF, 0, 0, 0, \
                               EE_RSCFD_TXQ_INT_ONLAST, \
                               EE_RSCFD_TXQ_OFF, 0 }, \
                             { EE_RSCFD_TXQ_ON, 0, 0, 0, \
                               EE_RSCFD_TXQ_INT_ONEVERY, \
                               EE_RSCFD_MAXTXBUFFERS - 1, 0 } } /* Queue all TX buffers */

#define EE_RSCFD_A_THL_OFF { EE_RSCFD_THL_OFF, 0, 0, \
                             EE_RSCFD_THL_INT_ONLEVEL, \
                             EE_RSCFD_THL_ENTRY_QUEUED, 0 }          /* THL OFF */
#define EE_RSCFD_A_THL_ON  { EE_RSCFD_THL_ON, 0, 1, \
                             EE_RSCFD_THL_INT_ONEVERY, \
                             EE_RSCFD_THL_ENTRY_QUEUED, 0 }           /* THL ON */

#define EE_RSCFD_A_BT_AUTO { 0, 0, 0, 0, 0, 0, 0 }   /* Automatic bit timing */

#define EE_RSCFD_A_FDCFG_DEFAULT  { EE_RSCFD_EOC_ALLTXRX, 0,  \
                                    EE_RSCFD_TDC_MEASOFFSET,  \
                                    EE_RSCFD_TDC_DISABLE,     \
                                    EE_RSCFD_ESI_BYNODE, 0,   \
                                    0, 0,                     \
                                    EE_RSCFD_MULTIGW_DISABLE, \
                                    EE_RSCFD_FDF_FD,          \
                                    EE_RSCFD_BRS_SWITCH, 0,   \
                                    EE_RSCFD_FDMIXED,         \
                                    EE_RSCFD_RXEDGEFILTER_ON, \
                                    EE_RSCFD_FDMIXED, 0 }

/* ---------------------------------------------------------- */
/* 40 MHz on CAN communication clock needs to be set for this */
/* ---------------------------------------------------------- */

#define EE_RSCFD_A_BT_500_KBPS  { 0, 0,          /* BRP */   \
                                  15,            /* SJW */   \
                                  62, 0,         /* TSEG1 */ \
                                  15, 0 }        /* TSEG2 */ 

#define EE_RSCFD_A_BTD_4000_KBPS { 0, 0,         /* BRP */   \
                                   6,            /* TSEG1 */ \
                                   1, 0,         /* TSEG2 */ \
                                   1, 0 }        /* SJW */ 

#define EE_RSCFD_A_FDCFG_ACTTDC8  { EE_RSCFD_EOC_ALLTXRX, 0,  /* FD active, TDC 8 */ \
                                    EE_RSCFD_TDC_MEASOFFSET,  \
                                    EE_RSCFD_TDC_ENABLE,      \
                                    EE_RSCFD_ESI_BYNODE, 0,   \
                                    7, 0,                     \
                                    EE_RSCFD_MULTIGW_DISABLE, \
                                    EE_RSCFD_FDF_FD,          \
                                    EE_RSCFD_BRS_SWITCH, 0,   \
                                    EE_RSCFD_FDMIXED,         \
                                    EE_RSCFD_RXEDGEFILTER_ON, \
                                    EE_RSCFD_FDMIXED, 0 }

/* Default configurations */

const struct ee_rscfd_cfg_channel EE_RSCFD_A_CHCFG_BASIC = {

  500000,  0.0,                 /* arbitration bitrate 500 kbit/s, default BT */
  2000000, 0.0,                       /* data bitrate 2000 kbit/s, default BT */
  
  EE_RSCFD_A_BT_AUTO,                     /* automatic arbitration bit timing */
  EE_RSCFD_A_BT_AUTO,                            /* automatic data bit timing */
  {
    EE_RSCFD_OPMODE_KEEP, 0, 0, 0,    /* No implicit change of Operation Mode */
    EE_RSCFD_CINT_OFF, 0,                              /* No Error Interrupts */
    EE_RSCFD_BOM_ISO, 0,     /* Standard Bus Off behaviour & Error Signalling */
    0, EE_RSCFD_TEST_BASIC, 0,                               /* Test Mode Off */
    0, EE_RSCFD_RESTRICTED_DIS
  },
  {
    EE_RSCFD_OCC_KEEP,                  /* CAN-FD Occurrence Counter settings */
    EE_RSCFD_OCC_KEEP
  },
  EE_RSCFD_A_FDCFG_DEFAULT,                 /* CAN-FD Operation Configuration */
  
  0xFFFFFFFF,                                 /* enable all IRQ of TX Buffers */
  
  EE_RSCFD_A_TXQ_OFF,                      /* disable queues, lists and FIFOs */
  EE_RSCFD_A_THL_OFF,
  { EE_RSCFD_A_COMFIFO_OFF,
    EE_RSCFD_A_COMFIFO_OFF,
    EE_RSCFD_A_COMFIFO_OFF }
};

const struct ee_rscfd_cfg_channel EE_RSCFD_A_CHCFG_500_KBPS_4000KBPS = {

  0L,  0.0,                               /* arbitration bitrate manually set */
  0L,  0.0,                                      /* data bitrate manually set */
  
  EE_RSCFD_A_BT_500_KBPS,                           /* arbitration bit timing */
  EE_RSCFD_A_BTD_4000_KBPS,                                /* data bit timing */
  {
    EE_RSCFD_OPMODE_KEEP, 0, 0, 0,    /* No implicit change of Operation Mode */
    EE_RSCFD_CINT_OFF, 0,                              /* No Error Interrupts */
    EE_RSCFD_BOM_ISO, 0,     /* Standard Bus Off behaviour & Error Signalling */
    0, EE_RSCFD_TEST_BASIC, 0,                               /* Test Mode Off */
    EE_RSCFD_RESTRICTED_DIS
  },
  {
    EE_RSCFD_OCC_KEEP,                  /* CAN-FD Occurrence Counter settings */
    EE_RSCFD_OCC_KEEP
  },
  EE_RSCFD_A_FDCFG_ACTTDC8,                 /* CAN-FD Operation Configuration */
  
  0x00000000,                                /* disable all IRQ of TX Buffers */
  
  EE_RSCFD_A_TXQ_ALL,                             /* enable TX Queue (no IRQ) */
  EE_RSCFD_A_THL_ON,                                    /* enable THL with IRQ*/
  { EE_RSCFD_A_COMFIFO_OFF,                                  /* disable FIFOs */
    EE_RSCFD_A_COMFIFO_OFF,
    EE_RSCFD_A_COMFIFO_OFF }
};

const struct ee_rscfd_cfg_global EE_RSCFD_A_GCFG_BASIC = {

  {
    EE_RSCFD_TXPRIO_ID,                      /* TX priority by ID (standard) */
    EE_RSCFD_DLCCHECK_DISABLE, 
    EE_RSCFD_DLCREPL_DISABLE,                 /* no DLC check or replacement */
    EE_RSCFD_MIRROR_DISABLE,                               /* no Mirror Mode */
    EE_RSCFD_CLOCK_SYS,                              /* use peripheral clock */
    EE_RSCFD_PLOVF_TRUNCATE, 0, /* larger messages than buffer are truncated */
    0, EE_RSCFD_CLOCK_TSBIT, 
    EE_RSCFD_CHANNEL0,          /* Use 1TQ Bit-Timing clock 0 for Timestamps */
    EE_RSCFD_CLOCK_FIFO_OFF               /* interval timer of FIFO disabled */
  },
  {
    EE_RSCFD_OPMODE_KEEP, 
    EE_RSCFD_SLEEP_DISABLE, 0,       /* No implicit change of Operation Mode */
    EE_RSCFD_GINT_NONE, 0,                            /* No Error Interrupts */
    EE_RSCFD_TIMESTAMP_RESET,                             /* Timestamp reset */
    EE_RSCFD_TIMESTAMP_KEEP, 0       /* Timestamp is not written by software */
  },
  {
  	EE_RSCFD_PROTEXCEVENT_EN, 0, /* enable protocol exception event handling */
  	EE_RSCFD_TSCAPTURE_SOF, 0      /* timestamp capture performed at SOF bit */
  },
  {
  	EE_RSCFD_PROTOCOL_ISO, 0        /* use ISO conformous CRC field protocol */
  },
  {
  	EE_RSCFD_MAXRXBUFFERS,        /* use max. amount of classical RX buffers */
  	EE_RSCFD_BUFDL_8, 0  /* standard 8-byte size of all classical RX buffers */
  },
  {             
	  1, 1, 1, 1, 1, 1, 1, 1  	            /* every channel has one AFL entry */
  },
  {
		  EE_RSCFD_A_RXFIFO_SWGW,                           /* disable all RX FIFOs */
    EE_RSCFD_A_RXFIFO_OFF,
    EE_RSCFD_A_RXFIFO_OFF,
    EE_RSCFD_A_RXFIFO_OFF,
    EE_RSCFD_A_RXFIFO_OFF,
    EE_RSCFD_A_RXFIFO_OFF,
    EE_RSCFD_A_RXFIFO_OFF,
    EE_RSCFD_A_RXFIFO_OFF
  }
};

const struct ee_rscfd_cfg_global EE_RSCFD_A_GCFG_SWGW = {

  {
    EE_RSCFD_TXPRIO_ID,                      /* TX priority by ID (standard) */
    EE_RSCFD_DLCCHECK_DISABLE, 
    EE_RSCFD_DLCREPL_DISABLE,                 /* no DLC check or replacement */
    EE_RSCFD_MIRROR_DISABLE,                               /* no Mirror Mode */
    EE_RSCFD_CLOCK_SYS,                              /* use peripheral clock */
    EE_RSCFD_PLOVF_TRUNCATE, 0, /* larger messages than buffer are truncated */
    0, EE_RSCFD_CLOCK_TSBIT, 
    EE_RSCFD_CHANNEL0,          /* Use 1TQ Bit-Timing clock 0 for Timestamps */
    EE_RSCFD_CLOCK_FIFO_OFF               /* interval timer of FIFO disabled */
  },
  {
    EE_RSCFD_OPMODE_KEEP, 
    EE_RSCFD_SLEEP_DISABLE, 0,       /* No implicit change of Operation Mode */
    EE_RSCFD_GINT_NONE, 0,                            /* No Error Interrupts */
    EE_RSCFD_TIMESTAMP_RESET,                             /* Timestamp reset */
    EE_RSCFD_TIMESTAMP_KEEP, 0       /* Timestamp is not written by software */
  },
  {
  	EE_RSCFD_PROTEXCEVENT_EN, 0, /* enable protocol exception event handling */
  	EE_RSCFD_TSCAPTURE_SOF, 0      /* timestamp capture performed at SOF bit */
  },
  {
  	EE_RSCFD_PROTOCOL_ISO, 0        /* use ISO conformous CRC field protocol */
  },
  {
  	1,                                        /* use one classical RX buffer */
  	EE_RSCFD_BUFDL_64, 0         /* full 64-byte size of classical RX buffer */
  },
  {             
	  2, 2, 2, 2, 2, 2, 2, 2  	          /* every channel has two AFL entries */
  },
  {
    EE_RSCFD_A_RXFIFO_SWGW,                           /* enable all RX FIFOs */
    EE_RSCFD_A_RXFIFO_SWGW,
    EE_RSCFD_A_RXFIFO_SWGW,
    EE_RSCFD_A_RXFIFO_SWGW,
    EE_RSCFD_A_RXFIFO_SWGW,
    EE_RSCFD_A_RXFIFO_SWGW,
    EE_RSCFD_A_RXFIFO_SWGW,
    EE_RSCFD_A_RXFIFO_SWGW
  }
};

struct ee_rscfd_a_afl EE_RSCFD_A_AFL_RXBOX_ANY = {
  
  {
    0x0000000,               /* Default ID, not relevant because mask is open */
    EE_RSCFD_AFL_RXENTRY,                        /* receive entry type of AFL */
    EE_RSCFD_FRAME_DATA,                      /* RTR data frame configuration */
    EE_RSCFD_ID_STD                           /* standard frame configuration */
  },
  {
    EE_RSCFD_MASK_IDDONTCARE,                     /* mask is open for all IDs */
    0, EE_RSCFD_MASK_DONTCARE,               /* any type of frame is accepted */
    EE_RSCFD_MASK_DONTCARE
  },
  {
    EE_RSCFD_DLCCHECK_DISABLE, 0,      /* to enable DLC check, enter DLC here */
    0,                   /* RX Box Number - to be replaced with actual number */
    EE_RSCFD_SET,                                     /* RX Box is set active */
    0x0000          /* Receive HRH pointer - to be replaced with actual value */
  },
  {
    EE_RSCFD_AFL_RXFIF0_NONE,              /* this AFL entry only receives in */
    EE_RSCFD_AFL_COMFIFO_NONE                      /* classical message boxes */
  }
};

struct ee_rscfd_a_afl EE_RSCFD_A_AFL_RXFIFO_STDID_SWGW = {
  
  {
    0x0000000,            /* to be replaced by GW bus number in lowest 4 bits */
    EE_RSCFD_AFL_RXENTRY,                        /* receive entry type of AFL */
    EE_RSCFD_FRAME_DATA,                      /* RTR data frame configuration */
    EE_RSCFD_ID_STD                           /* standard frame configuration */
  },
  {
    0x0000000,                             /* mask is filtering GW bus number */
    0, EE_RSCFD_MASK_DONTCARE,                  /* only standard ID data frames */
	EE_RSCFD_MASK_DONTCARE
  },
  {
    EE_RSCFD_DLCCHECK_DISABLE, 0,      /* to enable DLC check, enter DLC here */
    0,                               /* RX Box Number - not relevant for FIFO */
    EE_RSCFD_CLEAR,                                 /* RX Box is set inactive */
    0x0000          /* Receive HRH pointer - to be replaced with actual value */
  },
  {
		  EE_RSCFD_AFL_RXFIF0_EN0,           /* to be replaced by assigned RX-FIFO */
    EE_RSCFD_AFL_COMFIFO_NONE                         /* COM-FIFO is not used */
  }
};

struct ee_rscfd_a_afl EE_RSCFD_A_AFL_RXBOX_EXTID_SWGWCTRL = {
  
  {
    0x0000000,                  /* Extended ID 0x00000000 to be received only */
    EE_RSCFD_AFL_RXENTRY,                        /* receive entry type of AFL */
    EE_RSCFD_FRAME_DATA,                      /* RTR data frame configuration */
    EE_RSCFD_ID_EXT                           /* extended frame configuration */
  },
  {
    EE_RSCFD_MASK_IDFULLCAN,                 /* mask is filtering exact match */
    0, EE_RSCFD_MASK_FILTER,                  /* only extended ID data frames */
    EE_RSCFD_MASK_FILTER
  },
  {
    EE_RSCFD_DLCCHECK_DISABLE, 0,      /* to enable DLC check, enter DLC here */
    0,                                                     /* RX Box Number 0 */
    EE_RSCFD_SET,                                     /* RX Box is set active */
    0x0000          /* Receive HRH pointer - to be replaced with actual value */
  },
  {
    EE_RSCFD_AFL_RXFIF0_NONE,                          /* RX-FIFO is not used */
    EE_RSCFD_AFL_COMFIFO_NONE                         /* COM-FIFO is not used */
  }
};

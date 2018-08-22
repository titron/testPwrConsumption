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
//Purpose: RSCFD Driver Hardware Register Include
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
//
// Test Registers not included
//
//============================================================================

#ifndef _RSCFDFD_UCIAPRCN_V3
#define _RSCFDFD_UCIAPRCN_V3
                   
#include <ree_types.h>

/* RSCFD Globals */
#define RH850_F1H_RSCFD20
//#define RH850_F1H_RSCFD20_OSC

#define EE_RSCFD_0       ( 0 )         /* RSCFD macro selection */
#define EE_RSCFD_1       ( 1 )
#define EE_RSCFD_INVALID ( 0xFF )      /* no macro assignment */

#define EE_RSCFD_NOIRQ   false         /* status report defines */
#define EE_RSCFD_IRQ     true
#define EE_RSCFD_OK      true
#define EE_RSCFD_ERROR   false
                                        /* RSCFD dimensions */
#define EE_RSCFD_MAXCHANNELS   ( 8 )    /* max. channels of hardware */
#define EE_RSCFD_AFLPAGESIZE   ( 16 )   /* common AFL page size */
#define EE_RSCFD_MAXAFLENTRIES ( 1024 ) /* max. entries in AFL total */
#define EE_RSCFD_MAXAFLCHANSET ( 255 )  /* max. entries in AFL per channel */
#define EE_RSCFD_MAXRXFIFOS    ( 8 )    /* for all channels */

#ifdef RH850_F1H_RSCFD20
#define EE_RSCFD_MAXRXBUFFERS  ( 64 )  /* for all channels */
#else
#define EE_RSCFD_MAXRXBUFFERS  ( 128 )  /* for all channels */
#endif
#define EE_RSCFD_MAXCOMFIFOS   ( 3 )    /* per channel */
#ifdef RH850_F1H_RSCFD20
#define EE_RSCFD_MAXTXBUFFERS  ( 16 )   /* per channel */
#else
#define EE_RSCFD_MAXTXBUFFERS  ( 32 )   /* per channel */
#endif
#ifdef RH850_F1H_RSCFD20
#define EE_RSCFD_MAXTXQUEUES   ( 8 )    /* per channel */
#else
#define EE_RSCFD_MAXTXQUEUES   ( 2 )    /* per channel */
#endif

#define EE_RSCFD_CHANNEL0      ( 0 )    /* RSCFD channels */
#define EE_RSCFD_CHANNEL1      ( 1 )
#define EE_RSCFD_CHANNEL2      ( 2 )
#define EE_RSCFD_CHANNEL3      ( 3 )
#define EE_RSCFD_CHANNEL4      ( 4 )
#define EE_RSCFD_CHANNEL5      ( 5 )
#define EE_RSCFD_CHANNEL6      ( 6 )
#define EE_RSCFD_CHANNEL7      ( 7 )
#define EE_RSCFD_GLOBAL        ( 0xFF ) /* for ALL channels */

#define EE_RSCFD_CHANNELS      ( ee_rscfd_channels[ UnitNumber_u08 ] )
#ifdef RH850_F1H_RSCFD20
#define EE_RSCFD_COMREGSBITS	 ( 8 )
#else
#define EE_RSCFD_COMREGSBITS	 ( 32 )
#endif

#ifdef RH850_F1H_RSCFD20
#define EE_RSCFD_COMTXREGS     ( 16)
#define EE_RSCFD_COMRXREGS     ( 64 )
#else
#define EE_RSCFD_COMTXREGS     ( EE_RSCFD_MAXTXBUFFERS * EE_RSCFD_MAXCHANNELS / EE_RSCFD_COMREGSBITS )
#define EE_RSCFD_COMRXREGS     ( EE_RSCFD_MAXRXBUFFERS / EE_RSCFD_COMREGSBITS )
#endif
#define EE_RSCFD_COMTXREG( N ) ( EE_RSCFD_MAXTXBUFFERS * N / EE_RSCFD_COMREGSBITS ) 
#define EE_RSCFD_COMRXREG( N ) ( N / EE_RSCFD_COMREGSBITS )
#define EE_RSCFD_COMRXBIT( N ) ( N % EE_RSCFD_COMREGSBITS )

#define EE_RSCFD_ID_STD        ( 0 )
#define EE_RSCFD_ID_EXT        ( 1 )
#define EE_RSCFD_ID_MAX        ( 0x1FFFFFFF )

#define EE_RSCFD_FRAME_DATA    ( 0 )
#define EE_RSCFD_FRAME_REMOTE  ( 1 )

#define EE_RSCFD_MASK_IDFULLCAN  ( 0x1FFFFFFF )
#define EE_RSCFD_MASK_IDDONTCARE ( 0x00000000 )
#define EE_RSCFD_MASK_DONTCARE   ( 0 )
#define EE_RSCFD_MASK_FILTER     ( 1 )

#define EE_RSCFD_DLC_CMAX  ( 8 )
#define EE_RSCFD_DLC_FDMAX ( 64 )
#define EE_RSCFD_DLC_FD_12 ( 9 )
#define EE_RSCFD_DLC_FD_16 ( 10 )
#define EE_RSCFD_DLC_FD_20 ( 11 )
#define EE_RSCFD_DLC_FD_24 ( 12 )
#define EE_RSCFD_DLC_FD_32 ( 13 )
#define EE_RSCFD_DLC_FD_48 ( 14 )
#define EE_RSCFD_DLC_FD_64 ( 15 )

#define EE_RSCFD_BUFDL_8   ( 0 )
#define EE_RSCFD_BUFDL_12  ( 1 )
#define EE_RSCFD_BUFDL_16  ( 2 )
#define EE_RSCFD_BUFDL_20  ( 3 )
#define EE_RSCFD_BUFDL_24  ( 4 )
#define EE_RSCFD_BUFDL_32  ( 5 )
#define EE_RSCFD_BUFDL_48  ( 6 )
#define EE_RSCFD_BUFDL_64  ( 7 )
#define EE_RSCFD_BUFDL_MAX ( 64 )

#define EE_RSCFD_FIFODL_8   ( 0 )
#define EE_RSCFD_FIFODL_12  ( 1 )
#define EE_RSCFD_FIFODL_16  ( 2 )
#define EE_RSCFD_FIFODL_20  ( 3 )
#define EE_RSCFD_FIFODL_24  ( 4 )
#define EE_RSCFD_FIFODL_32  ( 5 )
#define EE_RSCFD_FIFODL_48  ( 6 )
#define EE_RSCFD_FIFODL_64  ( 7 )
#define EE_RSCFD_FIFODL_MAX ( 64 )

#define EE_RSCFD_INT_GERR  ( 0x00 )  /* Interrupt vector definition */
#define EE_RSCFD_INT_RXF0  ( 0x01 )  /* Global vectors */
#define EE_RSCFD_INT_RXF1  ( 0x02 )
#define EE_RSCFD_INT_RXF2  ( 0x03 )
#define EE_RSCFD_INT_RXF3  ( 0x04 )
#define EE_RSCFD_INT_RXF4  ( 0x05 )
#define EE_RSCFD_INT_RXF5  ( 0x06 )
#define EE_RSCFD_INT_RXF6  ( 0x07 )
#define EE_RSCFD_INT_RXF7  ( 0x08 )

#define EE_RSCFD_INT_TX    ( 0x00 )  /* Channel vectors */
#define EE_RSCFD_INT_TXA   ( 0x01 )
#define EE_RSCFD_INT_TXQ0  ( 0x02 )
#define EE_RSCFD_INT_TXQ1  ( 0x03 )
#define EE_RSCFD_INT_CERR  ( 0x04 )
#define EE_RSCFD_INT_TXHL  ( 0x05 )
#define EE_RSCFD_INT_RXCF  ( 0x06 )
#define EE_RSCFD_INT_TXCF  ( 0x07 )

#define EE_RSCFD_INT_NOINT ( 0xFF )

#define EE_RSCFD_INT_ENABLE  ( 0x01 )
#define EE_RSCFD_INT_DISABLE ( 0x00 )

#define EE_RSCFD_INT_GLOBAL  ( 1 + EE_RSCFD_MAXRXFIFOS )
#define EE_RSCFD_INT_CHANNEL ( 8 )
#define EE_RSCFD_INT_MACRO   ( EE_RSCFD_INT_GLOBAL + ( EE_RSCFD_INT_CHANNEL * EE_RSCFD_MAXCHANNELS ) )

/* Arbitration Bittiming settings */

#define EE_RSCFD_BT_SPEC            ( true )
#define EE_RSCFD_BT_MAXTQ           ( 160 )
#define EE_RSCFD_BT_MINTQ           ( 5 )
#define EE_RSCFD_BT_MINTSEG1        ( 2 )
#define EE_RSCFD_BT_MAXTSEG1        ( 128 )
#define EE_RSCFD_BT_MINTSEG2        ( 2 )
#define EE_RSCFD_BT_MAXTSEG2        ( 32 )
#define EE_RSCFD_BT_MINSJW          ( 1 )
#define EE_RSCFD_BT_MAXSJW          ( 32 )
#define EE_RSCFD_BT_SYNCSEGLEN      ( 1 )

#define EE_RSCFD_BT_MAXBRP          ( 1024 )
#define EE_RSCFD_BT_SPTOPTIMUM      ( 0.75 )

/* Data Bittiming settings */

#define EE_RSCFD_BTD_SPEC           ( false )
#define EE_RSCFD_BTD_MAXTQ          ( 25 )
#define EE_RSCFD_BTD_MINTQ          ( 5 )
#define EE_RSCFD_BTD_MINTSEG1       ( 2 )
#define EE_RSCFD_BTD_MAXTSEG1       ( 16 )
#define EE_RSCFD_BTD_MINTSEG2       ( 2 )
#define EE_RSCFD_BTD_MAXTSEG2       ( 8 )
#define EE_RSCFD_BTD_MINSJW         ( 1 )
#define EE_RSCFD_BTD_MAXSJW         ( 8 )
#define EE_RSCFD_BTD_SYNCSEGLEN     ( 1 )

#define EE_RSCFD_BTD_MAXBRP         ( 256 )
#define EE_RSCFD_BTD_SPTOPTIMUM     ( 0.75 )

/* CAN-FD Parameters */

#define EE_RSCFD_OC_CLEAR           ( 1 )
#define EE_RSCFD_OC_KEEP            ( 0 )
#define EE_RSCFD_EOC_ALLTXRX        ( 0x00 )
#define EE_RSCFD_EOC_ALLTX          ( 0x01 )
#define EE_RSCFD_EOC_ALLRX          ( 0x02 )
#define EE_RSCFD_EOC_ALLTXRXFD      ( 0x04 )
#define EE_RSCFD_EOC_ALLTXFD        ( 0x05 )
#define EE_RSCFD_EOC_ALLRXFD        ( 0x06 )

#define EE_RSCFD_TDC_OFFSETONLY     ( 1 )
#define EE_RSCFD_TDC_MEASOFFSET     ( 0 )
#define EE_RSCFD_TDC_ENABLE         ( 1 )
#define EE_RSCFD_TDC_DISABLE        ( 0 )

#define EE_RSCFD_ESI_BYNODE         ( 0 )
#define EE_RSCFD_ESI_BYACTBUFFER    ( 1 )

#define EE_RSCFD_MULTIGW_ENABLE     ( 1 )
#define EE_RSCFD_MULTIGW_DISABLE    ( 0 )

#define EE_RSCFD_FDF_CLASSIC        ( 0 )
#define EE_RSCFD_FDF_FD             ( 1 )
#define EE_RSCFD_BRS_SWITCH         ( 1 )
#define EE_RSCFD_BRS_NOSWITCH       ( 0 )

#define EE_RSCFD_CLASSICALONLY      ( 1 )
#define EE_RSCFD_FDONLY             ( 1 )
#define EE_RSCFD_FDMIXED            ( 0 )

#define EE_RSCFD_RXEDGEFILTER_ON    ( 1 )
#define EE_RSCFD_RXEDGEFILTER_OFF   ( 0 )

#define EE_RSCFD_RESTRICTED_EN      ( 1 )
#define EE_RSCFD_RESTRICTED_DIS     ( 0 )

#define EE_RSCFD_PROTEXCEVENT_EN    ( 0 )
#define EE_RSCFD_PROTEXCEVENT_DIS   ( 1 )

#define EE_RSCFD_TSCAPTURE_SOF      ( 0x00 )
#define EE_RSCFD_TSCAPTURE_FRVALID  ( 0x01 )
#define EE_RSCFD_TSCAPTURE_RES      ( 0x02 )

#define EE_RSCFD_PROTOCOL_BOSCHV1   ( 1 )
#define EE_RSCFD_PROTOCOL_ISO       ( 0 )

#define EE_RSCFD_OCC_KEEP           ( 0 )
#define EE_RSCFD_OCC_CLEAR          ( 1 )

/* Clocking relationships of TL and system */

#define EE_RSCFD_TRLAYERFACTOR      ( 1 )
#define EE_RSCFD_CLKMINFACTOR       ( 10 )

/* Prescaler settings (FIFO interval, Timestamp) */

#define EE_RSCFD_FIFO_MAXPRS        ( 256 )
#define EE_RSCFD_FIFO_MINPRS        ( 1 )
#define EE_RSCFD_FIFO_CKPRS         ( 10 )
#define EE_RSCFD_TS_MAXPRS          ( 32768 )
#define EE_RSCFD_TS_MINPRS          ( 1 )

/* RSCFD Constant Values */   

#define EE_RSCFD_SET              ( 1 )
#define EE_RSCFD_CLEAR            ( 0 )

#define EE_RSCFD_OPMODE_OPER      ( 0x00 )
#define EE_RSCFD_OPMODE_RESET     ( 0x01 )
#define EE_RSCFD_OPMODE_HALT      ( 0x02 )
#define EE_RSCFD_OPMODE_KEEP      ( 0x03 )
#define EE_RSCFD_OPMODE_SLEEP     ( 0x04 )
#define EE_RSCFD_OPMODE_RECONLY   ( 0x05 )
#define EE_RSCFD_OPMODE_STEST     ( 0x06 )

#define EE_RSCFD_SLEEP_ENABLE     ( 0x01 )
#define EE_RSCFD_SLEEP_DISABLE    ( 0x00 )

#define EE_RSCFD_CINT_OFF         ( 0x000 )
#define EE_RSCFD_CINT_BUSERR      ( 0x001 )
#define EE_RSCFD_CINT_WARNING     ( 0x002 )
#define EE_RSCFD_CINT_PASSIVE     ( 0x004 )
#define EE_RSCFD_CINT_BUSOFF      ( 0x008 )
#define EE_RSCFD_CINT_RECOVERY    ( 0x010 )
#define EE_RSCFD_CINT_OVERLOAD    ( 0x020 )
#define EE_RSCFD_CINT_BUSLOCK     ( 0x040 )
#define EE_RSCFD_CINT_ARBLOST     ( 0x080 )
#define EE_RSCFD_CINT_TXABORT     ( 0x100 )
#define EE_RSCFD_CINT_ERRCOVF     ( 0x200 )
#define EE_RSCFD_CINT_SUCCOVF     ( 0x400 )
#define EE_RSCFD_CINT_TDCVIOL     ( 0x800 )

#define EE_RSCFD_PLOVF_REJECT     ( 0 )
#define EE_RSCFD_PLOVF_TRUNCATE   ( 1 )

#define EE_RSCFD_ECCERR_ENABLE    ( 1 )
#define EE_RSCFD_ECCERR_DISABLE   ( 0 )

#define EE_RSCFD_TXTS_ENABLE      ( 1 )
#define EE_RSCFD_TXTS_DISABLE     ( 0 )

#define EE_RSCFD_GINT_NONE        ( 0x00 )
#define EE_RSCFD_GINT_DLCCHECK    ( 0x01 )
#define EE_RSCFD_GINT_MSGLOST     ( 0x02 )
#define EE_RSCFD_GINT_THLLOST     ( 0x04 )
#define EE_RSCFD_GINT_FDMSGOVF    ( 0x08 )

#define EE_RSCFD_BOM_ISO          ( 0x00 )
#define EE_RSCFD_BOM_HALTBOFF     ( 0x01 )
#define EE_RSCFD_BOM_HALTRECV     ( 0x02 )
#define EE_RSCFD_BOM_SW           ( 0x03 )

#define EE_RSCFD_TEST_BASIC       ( 0x00 )
#define EE_RSCFD_TEST_RXONLY      ( 0x01 )
#define EE_RSCFD_TEST_EXTLOOP     ( 0x02 )
#define EE_RSCFD_TEST_INTLOOP     ( 0x03 )

#define EE_RSCFD_TXPRIO_ID        ( 0x00 )
#define EE_RSCFD_TXPRIO_MBOX      ( 0x01 )

#define EE_RSCFD_CLOCK_SYS        ( 0x00 )
#define EE_RSCFD_CLOCK_MOSC       ( 0x01 )
#define EE_RSCFD_CLOCK_TSMACRO    ( 0x00 )
#define EE_RSCFD_CLOCK_TSBIT      ( 0x01 )
#define EE_RSCFD_CLOCK_FIFO_OFF   ( 0x0000 )

/* RSCFD Status Return identifiers */

#define EE_RSCFD_STATUS_OPMODE       0
#define EE_RSCFD_STATUS_PSMODE       1
#define EE_RSCFD_STATUS_RECEIVE      2
#define EE_RSCFD_STATUS_TRANSMIT     3
#define EE_RSCFD_STATUS_BUSOFF       4
#define EE_RSCFD_STATUS_TOVF         10
#define EE_RSCFD_STATUS_THPM         11
#define EE_RSCFD_STATUS_TGPT         12
#define EE_RSCFD_STATUS_TXTS         13
#define EE_RSCFD_STATUS_VALID        14
#define EE_RSCFD_STATUS_TRERRCOUNT   15
#define EE_RSCFD_STATUS_RXERRCOUNT   16
#define EE_RSCFD_STATUS_NEWTXHISTORY 22
#define EE_RSCFD_STATUS_INTERRUPT    24
#define EE_RSCFD_STATUS_ERRCNTLEV    25
#define EE_RSCFD_STATUS_ERRPLEV      26
#define EE_RSCFD_STATUS_INT_RXFIFO   27
#define EE_RSCFD_STATUS_MLT_RXFIFO   28
#define EE_RSCFD_STATUS_MLT_COMFIFO  29

/* RSCFD Status Return values */

#define EE_RSCFD_RSTATUS_OPERATION ( 0x00 )
#define EE_RSCFD_RSTATUS_RESET     ( 0x01 )
#define EE_RSCFD_RSTATUS_HALT      ( 0x02 )
#define EE_RSCFD_RSTATUS_SLEEP     ( 0x04 )
#define EE_RSCFD_RSTATUS_PASSIVE   ( 0x08 )
#define EE_RSCFD_RSTATUS_BUSOFF    ( 0x10 )
#define EE_RSCFD_RSTATUS_TRANSMIT  ( 0x20 )
#define EE_RSCFD_RSTATUS_RECEIVE   ( 0x40 )
#define EE_RSCFD_RSTATUS_RDY       ( 0x80 )
#define EE_RSCFD_RSTATUS_RAMINIT   ( 0x08 )

/* RSCFD Error Status Return values */

#define EE_RSCFD_GERROR_DLCCHECK  ( 0x01 )
#define EE_RSCFD_GERROR_MSGLOST   ( 0x02 )
#define EE_RSCFD_GERROR_THLLOST   ( 0x04 )
#define EE_RSCFD_GERROR_RAMPARITY ( 0x08 )
#define EE_RSCFD_GERROR_PLLFAIL   ( 0x10 )
#define EE_RSCFD_GERROR_OTBFAIL   ( 0x20 )

#define EE_RSCFD_ERROR_BUSERR     ( 0x0001 )
#define EE_RSCFD_ERROR_WARNING    ( 0x0002 )
#define EE_RSCFD_ERROR_PASSIVE    ( 0x0004 )
#define EE_RSCFD_ERROR_BUSOFF     ( 0x0008 )
#define EE_RSCFD_ERROR_RECOVERY   ( 0x0010 )
#define EE_RSCFD_ERROR_OVERLOAD   ( 0x0020 )
#define EE_RSCFD_ERROR_BUSLOCK    ( 0x0040 )
#define EE_RSCFD_ERROR_ARBLOST    ( 0x0080 )
#define EE_RSCFD_ERROR_STUFFING   ( 0x0100 )
#define EE_RSCFD_ERROR_FORM       ( 0x0200 )
#define EE_RSCFD_ERROR_ACK        ( 0x0400 )
#define EE_RSCFD_ERROR_CRC        ( 0x0800 )
#define EE_RSCFD_ERROR_BITLEV1    ( 0x1000 )
#define EE_RSCFD_ERROR_BITLEV0    ( 0x2000 )
#define EE_RSCFD_ERROR_ACKDELIM   ( 0x4000 )

#define EE_RSCFD_ERROR_CLEARALL   ( 0x0000 )

/* RSCFD Constant Values */   

#define EE_RSCFD_DN_CLEARALL      ( 0x0000 )

/* RSCFD FIFO Settings */

#define	EE_RSCFD_RX_FIFO_EN		   	( 0x01 )
#define	EE_RSCFD_RX_FIFO_DIS		  ( 0x00 )
#define	EE_RSCFD_RX_FIFO_INT_EN		( 0x01 )
#define	EE_RSCFD_RX_FIFO_INT_DIS	( 0x00 )

#define EE_RSCFD_FIFO_DEPTH_0     ( 0x00 )
#define EE_RSCFD_FIFO_DEPTH_4     ( 0x01 )
#define EE_RSCFD_FIFO_DEPTH_8     ( 0x02 )
#define EE_RSCFD_FIFO_DEPTH_16    ( 0x03 )
#define EE_RSCFD_FIFO_DEPTH_32    ( 0x04 )
#define EE_RSCFD_FIFO_DEPTH_48    ( 0x05 )
#define EE_RSCFD_FIFO_DEPTH_64    ( 0x06 )
#define EE_RSCFD_FIFO_DEPTH_128   ( 0x07 )

#define EE_RSCFD_FIFO_ILEVEL_1D8  ( 0x00 )
#define EE_RSCFD_FIFO_ILEVEL_2D8  ( 0x01 )
#define EE_RSCFD_FIFO_ILEVEL_3D8  ( 0x02 )
#define EE_RSCFD_FIFO_ILEVEL_4D8  ( 0x03 )
#define EE_RSCFD_FIFO_ILEVEL_5D8  ( 0x04 )
#define EE_RSCFD_FIFO_ILEVEL_6D8  ( 0x05 )
#define EE_RSCFD_FIFO_ILEVEL_7D8  ( 0x06 )
#define EE_RSCFD_FIFO_ILEVEL_8D8  ( 0x07 )

#define EE_RSCFD_FIFO_INT_ONEVERY ( 0x01 )
#define EE_RSCFD_FIFO_INT_ONLEVEL ( 0x00 )

#define EE_RSCFD_FIFO_MODE_RX     ( 0x00 )
#define EE_RSCFD_FIFO_MODE_TX     ( 0x01 )
#define EE_RSCFD_FIFO_MODE_GW     ( 0x02 )

#define EE_RSCFD_FIFO_IT_REFCLK   ( 0x00 )
#define EE_RSCFD_FIFO_IT_BTCLK    ( 0x01 )
#define EE_RSCFD_FIFO_IT_REFCLK1  ( 0x00 )
#define EE_RSCFD_FIFO_IT_REFCLK10 ( 0x01 )

#define EE_RSCFD_FIFO_NEXTELEMENT ( 0xFF )

#define EE_RSCFD_TID_NOTUSED      ( 0xFF )

#define EE_RSCFD_FIFO_STATUS_FULL  ( 0 )
#define EE_RSCFD_FIFO_STATUS_EMPTY ( 1 )
#define EE_RSCFD_FIFO_STATUS_LOST  ( 2 )


/* RSCFD Transmit Box Settings */

#define EE_RSCFD_TRQ_ONGOING      ( 0x00 )
#define EE_RSCFD_TRQ_CLEAR        ( 0x00 )
#define EE_RSCFD_TRQ_ABORTED      ( 0x01 )
#define EE_RSCFD_TRQ_COMPLETED    ( 0x02 )
#define EE_RSCFD_TRQ_ABORTERROR   ( 0x03 )

/* RSCFD TX Queue settings */

#define EE_RSCFD_TXQ_OFF          ( 0x00 )
#define EE_RSCFD_TXQ_ON           ( 0x01 )
#define EE_RSCFD_TXQ_MIN          ( 0x02 )
#define EE_RSCFD_TXQ_MAX0         ( 0x0F )
#define EE_RSCFD_TXQ_MAX1         ( 0x1F )
#define EE_RSCFD_TXQ_INT_ONEVERY  ( 0x01 )
#define EE_RSCFD_TXQ_INT_ONLAST   ( 0x00 )

#define EE_RSCFD_TXQ_NEXTELEMENT  ( 0xFF )

#define EE_RSCFD_TMC_SET_TR       ( 0x01 )
#define EE_RSCFD_TMC_SET_AR       ( 0x02 )
#define EE_RSCFD_TMC_SET_OM       ( 0x04 )

#define EE_RSCFD_TMSTS_CLEAR      ( 0x00 )
#define EE_RSCFD_TMSTS_STSMSK     ( 0x19 )  /* checks TMTSTS, TMTRM and TMTARM flags! */
#define EE_RSCFD_TMSTS_RFMSK      ( 0x06 )

#define EE_RSCFD_TMIEC_SET_TMIE   ( 0x01 )
/* RSCFD TX History List settings */

#define EE_RSCFD_THL_OFF          ( 0x00 )
#define EE_RSCFD_THL_ON           ( 0x01 )
#define EE_RSCFD_THL_INT_ONLEVEL  ( 0x00 )
#define EE_RSCFD_THL_INT_ONEVERY  ( 0x01 )
#define EE_RSCFD_THL_ENTRY_ALL    ( 0x01 )
#define EE_RSCFD_THL_ENTRY_QUEUED ( 0x00 )

#define EE_RSCFD_THL_NEXTELEMENT  ( 0xFF )
#define EE_RSCFD_THL_EMPTY        ( 0x01 )

#define EE_RSCFD_THL_TX_BUFFER    ( 0x01 )
#define EE_RSCFD_THL_TX_FIFO      ( 0x02 )
#define EE_RSCFD_THL_TX_QUEUE     ( 0x04 )
#define EE_RSCFD_THL_BN_P         ( 3 )

/* RSCFD AFL Settings */

#define EE_RSCFD_AFL_RXENTRY      ( 0x00 )
#define EE_RSCFD_AFL_TXENTRY      ( 0x01 )

#define EE_RSCFD_AFL_RXFIF0_NONE  ( 0x00 )
#define EE_RSCFD_AFL_RXFIF0_EN0   ( 0x01 )
#define EE_RSCFD_AFL_RXFIF0_EN1   ( 0x02 )
#define EE_RSCFD_AFL_RXFIF0_EN2   ( 0x04 )
#define EE_RSCFD_AFL_RXFIF0_EN3   ( 0x08 )
#define EE_RSCFD_AFL_RXFIF0_EN4   ( 0x10 )
#define EE_RSCFD_AFL_RXFIF0_EN5   ( 0x20 )
#define EE_RSCFD_AFL_RXFIF0_EN6   ( 0x40 )
#define EE_RSCFD_AFL_RXFIF0_EN7   ( 0x80 )

#define EE_RSCFD_AFL_COMFIFO_NONE ( 0x000000 )

#define EE_RSCFD_AFL_COMFIFO_C0E0 ( 0x000001 )
#define EE_RSCFD_AFL_COMFIFO_C0E1 ( 0x000002 )
#define EE_RSCFD_AFL_COMFIFO_C0E2 ( 0x000004 )

#define EE_RSCFD_AFL_COMFIFO_C1E0 ( 0x000008 )
#define EE_RSCFD_AFL_COMFIFO_C1E1 ( 0x000010 )
#define EE_RSCFD_AFL_COMFIFO_C1E2 ( 0x000020 )

#define EE_RSCFD_AFL_COMFIFO_C2E0 ( 0x000040 )
#define EE_RSCFD_AFL_COMFIFO_C2E1 ( 0x000080 )
#define EE_RSCFD_AFL_COMFIFO_C2E2 ( 0x000100 )

#define EE_RSCFD_AFL_COMFIFO_C3E0 ( 0x000200 )
#define EE_RSCFD_AFL_COMFIFO_C3E1 ( 0x000400 )
#define EE_RSCFD_AFL_COMFIFO_C3E2 ( 0x000800 )

#define EE_RSCFD_AFL_COMFIFO_C4E0 ( 0x001000 )
#define EE_RSCFD_AFL_COMFIFO_C4E1 ( 0x002000 )
#define EE_RSCFD_AFL_COMFIFO_C4E2 ( 0x004000 )

#define EE_RSCFD_AFL_COMFIFO_C5E0 ( 0x008000 )
#define EE_RSCFD_AFL_COMFIFO_C5E1 ( 0x010000 )
#define EE_RSCFD_AFL_COMFIFO_C5E2 ( 0x020000 )

#define EE_RSCFD_AFL_COMFIFO_C6E0 ( 0x040000 )
#define EE_RSCFD_AFL_COMFIFO_C6E1 ( 0x080000 )
#define EE_RSCFD_AFL_COMFIFO_C6E2 ( 0x100000 )

#define EE_RSCFD_AFL_COMFIFO_C7E0 ( 0x200000 )
#define EE_RSCFD_AFL_COMFIFO_C7E1 ( 0x400000 )
#define EE_RSCFD_AFL_COMFIFO_C7E2 ( 0x800000 )

#define EE_RSCFD_BUF_DATA0_MASK   ( 0x000000FF )
#define EE_RSCFD_BUF_DATA1_MASK   ( 0x0000FF00 )
#define EE_RSCFD_BUF_DATA2_MASK   ( 0x00FF0000 )
#define EE_RSCFD_BUF_DATA3_MASK   ( 0xFF000000 )
#define EE_RSCFD_BUF_DATA4_MASK   ( 0x000000FF )
#define EE_RSCFD_BUF_DATA5_MASK   ( 0x0000FF00 )
#define EE_RSCFD_BUF_DATA6_MASK   ( 0x00FF0000 )
#define EE_RSCFD_BUF_DATA7_MASK   ( 0xFF000000 )

#define EE_RSCFD_BUF_DATA0_P      ( 0x00 )
#define EE_RSCFD_BUF_DATA1_P      ( 0x08 )
#define EE_RSCFD_BUF_DATA2_P      ( 0x10 )
#define EE_RSCFD_BUF_DATA3_P      ( 0x18 )
#define EE_RSCFD_BUF_DATA4_P      ( 0x00 )
#define EE_RSCFD_BUF_DATA5_P      ( 0x08 )
#define EE_RSCFD_BUF_DATA6_P      ( 0x10 )
#define EE_RSCFD_BUF_DATA7_P      ( 0x18 )

#define EE_RSCFD_DLCCHECK_ENABLE  ( 0x01 )
#define EE_RSCFD_DLCCHECK_DISABLE ( 0x00 )

#define EE_RSCFD_DLCREPL_ENABLE   ( 0x01 )
#define EE_RSCFD_DLCREPL_DISABLE  ( 0x00 )

#define EE_RSCFD_MIRROR_ENABLE    ( 0x01 )
#define EE_RSCFD_MIRROR_DISABLE   ( 0x00 )

#define EE_RSCFD_MSGPLOVF_REJECT  ( 0x00 )
#define EE_RSCFD_MSGPLOVF_TRUNC   ( 0x01 )

#define EE_RSCFD_ECCERROR_DISABLE ( 0x00 )
#define EE_RSCFD_ECCERROR_ENABLE  ( 0x01 )

#define EE_RSCFD_TIMESTAMP_RESET  ( 0x01 )
#define EE_RSCFD_TIMESTAMP_KEEP   ( 0x00 )
#define EE_RSCFD_TIMESTAMP_WRITE  ( 0x01 )

#define EE_RSCFD_TXTIMESTAMP_DIS  ( 0x00 )
#define EE_RSCFD_TXTIMESTAMP_EN   ( 0x01 )

/* RSCFD Driver Parameters */

#define EE_RSCFD_PATH_MSGBOX      ( 0x00 )
#define EE_RSCFD_PATH_COMFIFO     ( 0x01 )
#define EE_RSCFD_PATH_TXQUEUE     ( 0x02 )
#define EE_RSCFD_PATH_RXFIFO      ( 0x03 )
#define EE_RSCFD_PATH_ANY         ( 0xFF )

#define EE_RSCFD_PATHDETAIL_ANY   ( 0xFF )

#define EE_RSCFD_FAULT_NONE       ( 0x00 )
#define EE_RSCFD_FAULT_PARAMETER  ( 0x01 )
#define EE_RSCFD_FAULT_BUSY       ( 0x02 )
#define EE_RSCFD_FAULT_NODATA     ( 0x04 )
#define EE_RSCFD_FAULT_OTHER      ( 0xFF )

#define EE_RSCFD_RAMTEST_KEY1     ( 0x7575 )
#define EE_RSCFD_RAMTEST_KEY2     ( 0x8A8A )
#define EE_RSCFD_RAMTEST_MODE     ( 0x00000004 )

#define EE_RSCFD_RAMTEST_ENTRIES  ( 64 )

#define EE_RSCFD_COMTEST_ALLON    ( 0x1F )
#define EE_RSCFD_COMTEST_MODE     ( 0x00000001 )

/*............... The RSCFD access structures ............................*/

typedef struct ee_rscfd_c_ncfg
{
  volatile u32 nbrp      : 10;
  volatile u32 RESERVED0 : 1;
  volatile u32 nsjw      : 5;
  volatile u32 ntseg1    : 7;
  volatile u32 RESERVED1 : 1;
  volatile u32 ntseg2    : 5;
  volatile u32 RESERVED2 : 3;

} ee_rscfd_c_ncfg;

typedef struct ee_rscfd_c_ctr
{
  volatile u32 chmdc     : 2;
  volatile u32 cslpr     : 1;
  volatile u32 rtbo      : 1;
  volatile u32 RESERVED0 : 4;
  volatile u32 ie        : 12;
  volatile u32 RESERVED1 : 1;
  volatile u32 bom       : 2;
  volatile u32 errd      : 1;
  volatile u32 ctme      : 1;
  volatile u32 ctms      : 2;
  volatile u32 RESERVED2 : 3;
  volatile u32 crct      : 1;
  volatile u32 rom       : 1;  

} ee_rscfd_c_ctr;

typedef struct ee_rscfd_c_sts
{
  volatile u32 mds       : 2;
  volatile u32 slps      : 1;
  volatile u32 eps       : 1;
  volatile u32 boffs     : 1;
  volatile u32 trxs      : 1;
  volatile u32 recs      : 1;
  volatile u32 coms      : 1;
  volatile u32 esif      : 1;
  volatile u32 RESERVED0 : 7;
  volatile u32 rec       : 8;
  volatile u32 tec       : 8;

} ee_rscfd_c_sts;

typedef struct ee_rscfd_c_erfl
{
  volatile u32 err       : 15;
  volatile u32 RESERVED0 : 1;
  volatile u32 crc       : 15;
  volatile u32 RESERVED1 : 1;

} ee_rscfd_c_erfl;

typedef struct ee_rscfd_c_ch
{
  struct ee_rscfd_c_ncfg ncfg;
  struct ee_rscfd_c_ctr  ctr;
  struct ee_rscfd_c_sts  sts;
  struct ee_rscfd_c_erfl erfl;

} ee_rscfd_c_ch;

typedef struct ee_rscfd_c_dcfg
{
  volatile u32 dbrp      : 8;
  volatile u32 RESERVED0 : 8;
  volatile u32 dtseg1    : 4;
  volatile u32 dtseg2    : 3;
  volatile u32 RESERVED1 : 1;
  volatile u32 dsjw      : 3;
  volatile u32 RESERVED2 : 5;
  
} ee_rscfd_c_dcfg;

typedef struct ee_rscfd_c_fdcfg
{
  volatile u32 eoccfg    : 3;
  volatile u32 RESERVED0 : 5;
  volatile u32 tdcoc     : 1;
  volatile u32 tdce      : 1;
  volatile u32 esic      : 1;
  volatile u32 RESERVED1 : 5;
  volatile u32 tdco      : 7;
  volatile u32 RESERVED2 : 1;
  volatile u32 gwen      : 1;
  volatile u32 gwfdf     : 1;
  volatile u32 gwbrs     : 1;
  volatile u32 RESERVED3 : 1;
  volatile u32 fdoe      : 1;
  volatile u32 refe      : 1;
  volatile u32 cloe      : 1;
  volatile u32 RESERVED4 : 1;
  
} ee_rscfd_c_fdcfg;

typedef struct ee_rscfd_c_fdctr
{
  volatile u32 eocclr    : 1;
  volatile u32 socclr    : 1;
  volatile u32 RESERVED0 : 30;
  
} ee_rscfd_c_fdctr;

typedef struct ee_rscfd_c_fdsts
{
  volatile u32 tdcr      : 7;
  volatile u32 tdcvf     : 1;
  volatile u32 eoco      : 1;
  volatile u32 soco      : 1;
  volatile u32 RESERVED0 : 6;
  volatile u32 eoc       : 8;
  volatile u32 soc       : 8;
  
} ee_rscfd_c_fdsts;

typedef struct ee_rscfd_c_fdch
{
  struct ee_rscfd_c_dcfg  dcfg;
  struct ee_rscfd_c_fdcfg fdcfg;
  struct ee_rscfd_c_fdctr fdctr;
  struct ee_rscfd_c_fdsts fdsts;
  volatile u32            fdcrc;
  volatile u32 RESERVED0[ 3 ];
  
} ee_rscfd_c_fdch;

typedef struct ee_rscfd_c_gcfg
{
  volatile u32 tpri      : 1;
  volatile u32 dce       : 1;
  volatile u32 dre       : 1;
  volatile u32 mme       : 1;
  volatile u32 dcs       : 1;
  volatile u32 cmpoc     : 1;
  volatile u32 RESERVED0 : 2;
  volatile u32 tsp       : 4;
  volatile u32 tsss      : 1;
  volatile u32 tsbtcs    : 3;
  volatile u32 itrcp     : 16;
  
} ee_rscfd_c_gcfg;

typedef struct ee_rscfd_c_gctr
{
  volatile u32 gmdc      : 2;
  volatile u32 gslpr     : 1;
  volatile u32 RESERVED0 : 5;
  volatile u32 ie        : 4;
  volatile u32 RESERVED1 : 4;
  volatile u32 tsrst     : 1;
  volatile u32 tswr      : 1;
  volatile u32 RESERVED2 : 14;

} ee_rscfd_c_gctr;

typedef struct ee_rscfd_c_gsts
{
  volatile u32 mds       : 2;
  volatile u32 slps      : 1;
  volatile u32 rsts      : 1;
  volatile u32 RESERVED0 : 28;

} ee_rscfd_c_gsts;

typedef struct ee_rscfd_c_gerfl
{
  volatile u32 err       : 4;
  volatile u32 RESERVED0 : 12;
  volatile u32 eccerr    : 8;
  volatile u32 RESERVED1 : 8;

} ee_rscfd_c_gerfl;

typedef struct ee_rscfd_c_gafle
{
  volatile u32 aflpn     : 6;
  volatile u32 RESERVED0 : 2;
  volatile u32 afldae    : 1;
  volatile u32 RESERVED1 : 23;

} ee_rscfd_c_gafle;

typedef struct ee_rscfd_c_gaflc0          // <<-- specific for 6-channel macro
{
  volatile u32 rnc3		   : 8;
  volatile u32 rnc2      : 8;
  volatile u32 rnc1      : 8;
  volatile u32 rnc0      : 8;

} ee_rscfd_c_gaflc0;

typedef struct ee_rscfd_c_gaflc1
{
  volatile u32 rnc7      : 8;
  volatile u32 rnc6      : 8;
  volatile u32 rnc5      : 8;
  volatile u32 rnc4      : 8;

} ee_rscfd_c_gaflc1;

typedef struct ee_rscfd_c_rfcc
{
  volatile u32 rfe       : 1;
  volatile u32 rfie      : 1;
  volatile u32 RESERVED0 : 2;
  volatile u32 rfpls     : 3;
  volatile u32 RESERVED1 : 1;
  volatile u32 rfdc      : 3;
  volatile u32 RESERVED2 : 1;
  volatile u32 rfim      : 1;
  volatile u32 rfigcv    : 3;
  volatile u32 RESERVED3 : 16;

} ee_rscfd_c_rfcc;

typedef struct ee_rscfd_c_cfcc
{
  volatile u32 cfe       : 1;
  volatile u32 cfrxie    : 1;
  volatile u32 cftxie    : 1;
  volatile u32 RESERVED0 : 1;
  volatile u32 cfpls     : 3;
  volatile u32 RESERVED1 : 1;
  volatile u32 cfm       : 2;
  volatile u32 cfitss    : 1;
  volatile u32 cfitr     : 1;
  volatile u32 cfim      : 1;
  volatile u32 cfigcv    : 3;
  volatile u32 cftml     : 5;
  volatile u32 cfdc      : 3;
  volatile u32 cfitt     : 8;

} ee_rscfd_c_cfcc;

typedef struct ee_rscfd_c_rfsts
{
  volatile u32 rfemp     : 1;
  volatile u32 rffll     : 1;
  volatile u32 rfmlt     : 1;
  volatile u32 rfif      : 1;
  volatile u32 RESERVED0 : 4;
  volatile u32 rfmc      : 8;
  volatile u32 RESERVED1 : 16;

} ee_rscfd_c_rfsts;

typedef struct ee_rscfd_c_cfsts
{
  volatile u32 cfemp     : 1;
  volatile u32 cffll     : 1;
  volatile u32 cfmlt     : 1;
  volatile u32 cfrxif    : 1;
  volatile u32 cftxif    : 1;
  volatile u32 RESERVED0 : 3;
  volatile u32 cfmc      : 8;
  volatile u32 RESERVED1 : 16;

} ee_rscfd_c_cfsts;

typedef struct ee_rscfd_c_fpctr
{
  volatile u32 fpc       : 8;
  volatile u32 RESERVED0 : 24;

} ee_rscfd_c_fpctr;

typedef struct ee_rscfd_c_fsts
{
  volatile u32 rf        : 8;
  volatile u32 cf        : 24;

} ee_rscfd_c_fsts;

typedef struct ee_rscfd_c_tmc
{
  volatile u08 tr        : 1;
  volatile u08 ar        : 1;
  volatile u08 om        : 1;
  volatile u08 RESERVED0 : 5;

} ee_rscfd_c_tmc;

typedef struct ee_rscfd_c_tmsts
{
  volatile u08 sts       : 1;
  volatile u08 rf        : 2;
  volatile u08 rm        : 1;
  volatile u08 arm       : 1;
  volatile u08 RESERVED0 : 3;

} ee_rscfd_c_tmsts;

typedef struct ee_rscfd_c_txqcc
{
  volatile u32 qe        : 1;
  volatile u32 RESERVED0 : 4;
  volatile u32 ie        : 1;
  volatile u32 RESERVED1 : 1;
  volatile u32 im        : 1;
  volatile u32 dc        : 5;
  volatile u32 RESERVED2 : 19;

} ee_rscfd_c_txqcc;

typedef struct ee_rscfd_c_txqsts
{
  volatile u32 emp       : 1;
  volatile u32 fll       : 1;
  volatile u32 irq       : 1;
  volatile u32 RESERVED0 : 5;
  volatile u32 mc        : 6;
  volatile u32 RESERVED1 : 18;

} ee_rscfd_c_txqsts;

typedef struct ee_rscfd_c_thlcc
{
  volatile u32 thle      : 1;
  volatile u32 RESERVED0 : 7;
  volatile u32 ie        : 1;
  volatile u32 im        : 1;
  volatile u32 dte       : 1;
  volatile u32 RESERVED1 : 21;

} ee_rscfd_c_thlcc;

typedef struct ee_rscfd_c_thlsts
{
  volatile u32 emp       : 1;
  volatile u32 fll       : 1;
  volatile u32 elt       : 1;
  volatile u32 irq       : 1;
  volatile u32 RESERVED0 : 4;
  volatile u32 mc        : 6;
  volatile u32 RESERVED1 : 18;

} ee_rscfd_c_thlsts;

typedef struct ee_rscfd_c_gtcfg
{
  volatile u32 icbce	   : 8;
  volatile u32 RESERVED0 : 8;
  volatile u32 rtmps     : 9;
  volatile u32 RESERVED1 : 7;
  
} ee_rscfd_c_gtcfg;

typedef struct ee_rscfd_c_gtctr
{
  volatile u32 icbctme	 : 1;
  volatile u32 RESERVED0 : 1;
  volatile u32 rtme      : 1;
  volatile u32 RESERVED1 : 29;
    
} ee_rscfd_c_gtctr;

typedef struct ee_rscfd_c_rmnb
{
  volatile u32 nrxmb     : 8;
  volatile u32 rmpls     : 3;
  volatile u32 RESERVED0 : 21;
  
} ee_rscfd_c_rmnb;

typedef struct ee_rscfd_c_cdtct
{
  volatile u32 rfdmae    : 8;
  volatile u32 cfdmae    : 8;
  volatile u32 RESERVED0 : 16;
  
} ee_rscfd_c_cdtct;

typedef struct ee_rscfd_c_cdtsts
{
  volatile u32 rfdmasts  : 8;
  volatile u32 cfdmasts  : 8;
  volatile u32 RESERVED0 : 16;
  
} ee_rscfd_c_cdtsts;

typedef struct ee_rscfd_c_gfdcfg
{
  volatile u32 rped      : 1;
  volatile u32 RESERVED0 : 7;
  volatile u32 tsccfg    : 2;
  volatile u32 RESERVED1 : 22;
  
} ee_rscfd_c_gfdcfg;

typedef struct ee_rscfd_c_gcrccfg
{
  volatile u32 nie       : 1;
  volatile u32 RESERVED0 : 31;
  
} ee_rscfd_c_gcrccfg;

typedef struct ee_rscfd_c_txq
{
#ifdef RH850_F1H_RSCFD20
  struct ee_rscfd_c_txqcc   cc[8];
  struct ee_rscfd_c_txqsts  sts[8];
  volatile u32              pctr[8];
#else
  struct ee_rscfd_c_txqcc   cc[ EE_RSCFD_MAXCHANNELS ];
  struct ee_rscfd_c_txqsts  sts[ EE_RSCFD_MAXCHANNELS ];
  volatile u32              pctr[ EE_RSCFD_MAXCHANNELS ];
#endif
} ee_rscfd_c_txq;

typedef struct ee_rscfd_common 
{
  struct ee_rscfd_c_ch      ch[ EE_RSCFD_MAXCHANNELS ];       /* channel registers */
  volatile u32              gipv;                             /* global configuration */
  struct ee_rscfd_c_gcfg    gcfg;
  struct ee_rscfd_c_gctr    gctr;
  struct ee_rscfd_c_gsts    gsts;                             /* global status */
  struct ee_rscfd_c_gerfl   gerfl;
  volatile u32              gtsc;
  struct ee_rscfd_c_gafle   gafle;                            /* global AFL configuration */
  struct ee_rscfd_c_gaflc0  gaflc0;
  struct ee_rscfd_c_gaflc1  gaflc1;
  struct ee_rscfd_c_rmnb    rmnb;                             /* RX buffer configuration */
#ifdef RH850_F1H_RSCFD20
  volatile u32              rmnd[ 4 ];
  struct ee_rscfd_c_rfcc    rfcc[ 8 ];      /* RX FIFO configuration */
  struct ee_rscfd_c_rfsts   rfsts[ 8 ];
  struct ee_rscfd_c_fpctr   rfpctr[ 8 ];    /* Common FIFO configuration */
  struct ee_rscfd_c_cfcc    cfcc[ 8 * 3 ];
  struct ee_rscfd_c_cfsts   cfsts[ 8 * 3 ];
  struct ee_rscfd_c_fpctr   cfpctr[ 8 * 3 ];
#else
  volatile u32              rmnd[ EE_RSCFD_COMRXREGS ];
  struct ee_rscfd_c_rfcc    rfcc[ EE_RSCFD_MAXRXFIFOS ];      /* RX FIFO configuration */
  struct ee_rscfd_c_rfsts   rfsts[ EE_RSCFD_MAXRXFIFOS ];
  struct ee_rscfd_c_fpctr   rfpctr[ EE_RSCFD_MAXRXFIFOS ];    /* Common FIFO configuration */
  struct ee_rscfd_c_cfcc    cfcc[ EE_RSCFD_MAXCOMFIFOS * EE_RSCFD_MAXCHANNELS ];
  struct ee_rscfd_c_cfsts   cfsts[ EE_RSCFD_MAXCOMFIFOS * EE_RSCFD_MAXCHANNELS ];
  struct ee_rscfd_c_fpctr   cfpctr[ EE_RSCFD_MAXCOMFIFOS * EE_RSCFD_MAXCHANNELS ];
#endif
  struct ee_rscfd_c_fsts    fests;                            /* FIFO status */
  struct ee_rscfd_c_fsts    ffsts;
  struct ee_rscfd_c_fsts    fmsts;
  volatile u32              rfists;
  volatile u32              cfrists;
  volatile u32              cftists;                          /* TX buffer configuration */
  volatile u08              tmc[ EE_RSCFD_MAXTXBUFFERS * EE_RSCFD_MAXCHANNELS ];
  volatile u08              tmsts[ EE_RSCFD_MAXTXBUFFERS * EE_RSCFD_MAXCHANNELS ];
#ifdef RH850_F1H_RSCFD20
  volatile u32              tmtrsts[ 4 ];    /* TX buffer status */
  volatile u32              tmtarsts[ 4 ];
  volatile u32              tmtcsts[ 4 ];
  volatile u32              tmtasts[ 4 ];
  volatile u32              tmiec[ 4 ];
  struct ee_rscfd_c_txq     txq;      /* TX Queue configuration */
#else
  volatile u32              tmtrsts[ EE_RSCFD_COMTXREGS ];    /* TX buffer status */
  volatile u32              tmtarsts[ EE_RSCFD_COMTXREGS ];
  volatile u32              tmtcsts[ EE_RSCFD_COMTXREGS ];
  volatile u32              tmtasts[ EE_RSCFD_COMTXREGS ];
  volatile u32              tmiec[ EE_RSCFD_COMTXREGS ];
  struct ee_rscfd_c_txq     txq[ EE_RSCFD_MAXTXQUEUES ];      /* TX Queue configuration */
#endif
  struct ee_rscfd_c_thlcc   thlcc[ EE_RSCFD_MAXCHANNELS ];    /* THL configuration */
  struct ee_rscfd_c_thlsts  thlsts[ EE_RSCFD_MAXCHANNELS ];
  volatile u32              thlpctr[ EE_RSCFD_MAXCHANNELS ];
  volatile u32              gtintsts[ ( EE_RSCFD_MAXCHANNELS / 4 ) ];
  struct ee_rscfd_c_gtcfg   gtcfg;                            /* RAM Test registers */
  volatile u32              gtctr;
  volatile u32              RESERVED8[ 1 ];
  struct ee_rscfd_c_gfdcfg  gfdcfg;                          /* CAN FD global configuration */
  struct ee_rscfd_c_gcrccfg gcrccfg;
  volatile u32              glockk;
  volatile u32              RESERVED9[ 4 ];
  struct ee_rscfd_c_cdtct   cdtct;                           /* DMA configuration */
  struct ee_rscfd_c_cdtsts  cdtsts;
#ifdef RH850_F1H_RSCFD20
  volatile u32              RESERVED10[ 25 ];
  volatile u32              cfdgrmcfg;
#else
  volatile u32              RESERVED10[ 46 ];
#endif
  struct ee_rscfd_c_fdch    fdch[ EE_RSCFD_MAXCHANNELS ];    /* CAN FD channel configuration */
  
} ee_rscfd_common;

typedef struct ee_rscfd_a_aflid
{
  volatile u32 id  : 29;
  volatile u32 lb  : 1;
  volatile u32 rtr : 1;
  volatile u32 ide : 1;

} ee_rscfd_a_aflid;

typedef struct ee_rscfd_r_mask
{
  volatile u32 id        : 29;
  volatile u32 RESERVED0 : 1;
  volatile u32 rtr       : 1;
  volatile u32 ide       : 1;

} ee_rscfd_r_mask;

typedef struct ee_rscfd_t_mask
{
  volatile u32 id        : 29;
  volatile u32 thlen     : 1;
  volatile u32 rtr       : 1;
  volatile u32 ide       : 1;

} ee_rscfd_t_mask;

typedef struct ee_rscfd_a_aflptr0
{
  volatile u32 dlc       : 4;
  volatile u32 RESERVED0 : 4;
  volatile u32 rmdp      : 7;
  volatile u32 rmv       : 1;
  volatile u32 ptr       : 16;

} ee_rscfd_a_aflptr0;

typedef struct ee_rscfd_a_aflptr1
{
  volatile u32 rxfifomask  : 8;
  volatile u32 comfifomask : 24;

} ee_rscfd_a_aflptr1;

typedef struct ee_rscfd_a_afl
{
  struct ee_rscfd_a_aflid   id;
  struct ee_rscfd_r_mask    mask;
  struct ee_rscfd_a_aflptr0 ptr0;
  struct ee_rscfd_a_aflptr1 ptr1;

} ee_rscfd_a_afl;

typedef struct ee_rscfd_aflpage
{
  struct ee_rscfd_a_afl af[ EE_RSCFD_AFLPAGESIZE ];

} ee_rscfd_aflpage;

typedef struct ee_rscfd_r_ptr
{
  volatile u32 ts        : 16;
  volatile u32 RESERVED0 : 12;
  volatile u32 dlc       : 4;

} ee_rscfd_r_ptr;

typedef struct ee_rscfd_t_ptr
{
  volatile u32 RESERVED0 : 28;
  volatile u32 dlc       : 4;

} ee_rscfd_t_ptr;

typedef struct ee_rscfd_r_fdsts
{
  volatile u32 esi       : 1;
  volatile u32 brs       : 1;
  volatile u32 fdf       : 1;
  volatile u32 RESERVED0 : 13;
  volatile u32 ptr       : 16;
  
} ee_rscfd_r_fdsts;

typedef struct ee_rscfd_r_rmsg
{
  struct ee_rscfd_r_mask  id;
  struct ee_rscfd_r_ptr   ptr;
  struct ee_rscfd_r_fdsts fdsts;
  volatile u32            data[ EE_RSCFD_BUFDL_MAX / 4 ];
  volatile u32            RESERVED0[ 32 - 3 - ( EE_RSCFD_BUFDL_MAX / 4 ) ];

} ee_rscfd_r_rmsg;

typedef struct ee_rscfd_r_rfmsg
{
  struct ee_rscfd_r_mask  id;
  struct ee_rscfd_r_ptr   ptr;
  struct ee_rscfd_r_fdsts fdsts;
  volatile u32            data[ EE_RSCFD_FIFODL_MAX / 4 ];
  volatile u32            RESERVED0[ 32 - 3 - ( EE_RSCFD_FIFODL_MAX / 4 ) ];

} ee_rscfd_r_rfmsg;

typedef struct ee_rscfd_r_cmsg
{
  struct ee_rscfd_t_mask  id;
  struct ee_rscfd_r_ptr   ptr;
  struct ee_rscfd_r_fdsts fdsts;
  volatile u32            data[ EE_RSCFD_FIFODL_MAX / 4 ];
  volatile u32            RESERVED0[ 32 - 3 - ( EE_RSCFD_FIFODL_MAX / 4 ) ];

} ee_rscfd_r_cmsg;

typedef struct ee_rscfd_t_msg
{
  struct ee_rscfd_t_mask  id;
  struct ee_rscfd_t_ptr   ptr;
  struct ee_rscfd_r_fdsts fdsts;
  volatile u32            data[ EE_RSCFD_BUFDL_MAX / 4 ];
  volatile u32            RESERVED0[ 32 - 3 - ( EE_RSCFD_BUFDL_MAX / 4 ) ];

} ee_rscfd_t_msg;

typedef struct ee_rscfd_message
{
  struct ee_rscfd_t_mask  hdr;
  struct ee_rscfd_r_ptr   flag;
  struct ee_rscfd_r_fdsts fdsts;
  u08                     data[ EE_RSCFD_DLC_FDMAX ];
  u08                     path;
  u08                     pathdetail;
  
} ee_rscfd_message;

typedef struct ee_rscfd_rxmsg
{
  struct ee_rscfd_r_rmsg buf[ EE_RSCFD_MAXRXBUFFERS ];

} ee_rscfd_rxmsg;

typedef struct ee_rscfd_rxfifo
{
  struct ee_rscfd_r_rfmsg buf[ EE_RSCFD_MAXRXFIFOS ];

} ee_rscfd_rxfifo;

typedef struct ee_rscfd_comfifo
{
  struct ee_rscfd_r_cmsg buf[ EE_RSCFD_MAXCOMFIFOS ];

} ee_rscfd_comfifo;

typedef struct ee_rscfd_txmsg
{
  struct ee_rscfd_t_msg buf[ EE_RSCFD_MAXTXBUFFERS ];

} ee_rscfd_txmsg;

typedef struct ee_rscfd_thlacc0
{
  volatile u32 bt        : 3;
  volatile u32 bn        : 5;
  volatile u32 RESERVED0 : 8;
  volatile u32 tmts      : 16;
  
} ee_rscfd_thlacc0;

typedef struct ee_rscfd_thlacc1
{
  volatile u32 tid       : 16;
  volatile u32 RESERVED0 : 16;
  
} ee_rscfd_thlacc1;

typedef struct ee_rscfd_thl
{
  struct ee_rscfd_thlacc0 l;
  struct ee_rscfd_thlacc1 h;

} ee_rscfd_thl;

typedef struct ee_rscfd_ram
{
  volatile u32 cell[ EE_RSCFD_RAMTEST_ENTRIES ];

} ee_rscfd_ram;

/* SW Channel configuration */

typedef struct ee_rscfd_cfg_channel
{
  u32                     arb_bitrate;    /* if set to 0, register set "ncfg" is used */
  flt                     arb_samplingpointpos;     /* optional Parameter, can be 0.0 */
  u32                     data_bitrate;   /* if set to 0, register set "dcfg" is used */
  flt                     data_samplingpointpos;    /* optional Parameter, can be 0.0 */
  struct ee_rscfd_c_ncfg  ncfg;
  struct ee_rscfd_c_dcfg  dcfg;
  struct ee_rscfd_c_ctr   ctr;
  struct ee_rscfd_c_fdctr fdctr;
  struct ee_rscfd_c_fdcfg fdcfg;
  u32                     tmiec;                   /* TX Interrupt Enable per channel */
#ifdef RH850_F1H_RSCFD20
  struct ee_rscfd_c_txqcc txq;       /* TX Queues per channel */
#else
  struct ee_rscfd_c_txqcc txq[ EE_RSCFD_MAXTXQUEUES ];       /* TX Queues per channel */
#endif
  struct ee_rscfd_c_thlcc thlcc;                                 /* THL configuration */
  struct ee_rscfd_c_cfcc  cfcc[ EE_RSCFD_MAXCOMFIFOS ];     /* COM FIFO configuration */
} ee_rscfd_cfg_channel;

/* Global configuration */

typedef struct ee_rscfd_cfg_global
{
  struct ee_rscfd_c_gcfg    gcfg;
  struct ee_rscfd_c_gctr    gctr;
  struct ee_rscfd_c_gfdcfg  gfdcfg;
  struct ee_rscfd_c_gcrccfg gcrccfg;
  struct ee_rscfd_c_rmnb    rmnb;
	volatile u32              rnc[ EE_RSCFD_MAXCHANNELS ];
  struct ee_rscfd_c_rfcc    rfcc[ EE_RSCFD_MAXRXFIFOS ];

} ee_rscfd_cfg_global;

#endif


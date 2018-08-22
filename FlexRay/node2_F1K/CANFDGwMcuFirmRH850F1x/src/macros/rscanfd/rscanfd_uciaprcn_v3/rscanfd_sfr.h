#ifndef _lint
/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * (MISRA C:2012 Violation - Rule 3.1
 * Justification - C comment contains C++ comment can't avoid here.)
 * http:/ /www.renesas.com/disclaimer
 *
 * Copyright (C) 2011 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name	: rscanfd_sfr.h
 * Version      : 1.0
 * Description  : RSCANFD IP register definition
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 25.09.2014 1.00     First Release
 ***********************************************************************************************************************/
#ifndef RSCANFD_SFR_H
#define RSCANFD_SFR_H

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Macro definitions
 ***********************************************************************************************************************/
#define CPU_ENDIAN_BIG                 0
#define CPU_ENDIAN_LITTLE              1

/* ---- configuration (change based on CPU) ---- */
#define CPU_ENDIAN_TYPE                CPU_ENDIAN_LITTLE
#define CANFD_BASE_ADDR                0xFFD00000UL /* RSCAN0 base address */
#define CANFD1_ADDR_OFFSET             0x00008000UL /* RSCAN1 offset address */
#define RSC_FAR
#define RSC_VOLATILE                   volatile

/* ---- value of register bit field ---- */
/* TBD */

/***********************************************************************************************************************
 Typedef definitions
 ***********************************************************************************************************************/
/* ---- SFR common type ---- */
typedef unsigned char T_U8;
typedef unsigned short T_U16;
typedef unsigned int T_U32;

typedef RSC_VOLATILE T_U32 T_LONG;

typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	T_U16 H;
	T_U16 L;
#else
	T_U16 L;
	T_U16 H;
#endif
} T_WORD;

typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	T_U8 HH;
	T_U8 HL;
	T_U8 LH;
	T_U8 LL;
#else
	T_U8 LL;
	T_U8 LH;
	T_U8 HL;
	T_U8 HH;
#endif
} T_BYTE;

typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 B0 :1;
	T_U32 B1 :1;
	T_U32 B2 :1;
	T_U32 B3 :1;
	T_U32 B4 :1;
	T_U32 B5 :1;
	T_U32 B6 :1;
	T_U32 B7 :1;
	T_U32 B8 :1;
	T_U32 B9 :1;
	T_U32 B10 :1;
	T_U32 B11 :1;
	T_U32 B12 :1;
	T_U32 B13 :1;
	T_U32 B14 :1;
	T_U32 B15 :1;
	T_U32 B16 :1;
	T_U32 B17 :1;
	T_U32 B18 :1;
	T_U32 B19 :1;
	T_U32 B20 :1;
	T_U32 B21 :1;
	T_U32 B22 :1;
	T_U32 B23 :1;
	T_U32 B24 :1;
	T_U32 B25 :1;
	T_U32 B26 :1;
	T_U32 B27 :1;
	T_U32 B28 :1;
	T_U32 B29 :1;
	T_U32 B30 :1;
	T_U32 B31 :1;
#endif
} T_BIT;

/* ---- channel configuration & status registers ---- */
/* CnCFG */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	T_U32 :6;
	T_U32 SJW:2;
	T_U32 :1;
	T_U32 TSEG2:3;
	T_U32 TSEG1:4;
	T_U32 :6;
	T_U32 BRP:10;
#else
	T_U32 BRP :10;
	T_U32 :6;
	T_U32 TSEG1 :4;
	T_U32 TSEG2 :3;
	T_U32 :1;
	T_U32 SJW :2;
	T_U32 :6;
#endif
} T_CnCFG_BIT;
/* MISRA C:2004 Violation - Rule 18.4 */
/* Justification - Some union definition are used unavoidable */
/*lint -save -e960 */
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CnCFG_BIT BIT;
} T_CnCFG;

/* CFDCnNCFG */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	T_U32 :3;
	T_U32 NTSEG2:5;
	T_U32 :1;
	T_U32 NTSEG1:7;
	T_U32 NSJW:5;
	T_U32 :1;
	T_U32 NBRP:10;
#else
	T_U32 NBRP :10;
	T_U32 :1;
	T_U32 NSJW :5;
	T_U32 NTSEG1 :7;
	T_U32 :1;
	T_U32 NTSEG2 :5;
	T_U32 :3;
#endif
} T_CFDCnNCFG_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFDCnNCFG_BIT BIT;
} T_CFDCnNCFG;

/* CnCTR / CFDCnCTR */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 CHMDC :2;
	T_U32 CSLPR :1;
	T_U32 RTBO :1;
	T_U32 :4;
	T_U32 BEIE :1;
	T_U32 EWIE :1;
	T_U32 EPIE :1;
	T_U32 BOEIE :1;
	T_U32 BORIE :1;
	T_U32 OLIE :1;
	T_U32 BLIE :1;
	T_U32 ALIE :1;
	T_U32 TAIE :1;
	T_U32 :4;
	T_U32 BOM :2;
	T_U32 ERRD :1;
	T_U32 CTME :1;
	T_U32 CTMS :2;
	T_U32 TRWE :1;
	T_U32 TRH :1;
	T_U32 TRR :1;
	T_U32 CRCT :1;
	T_U32 :1;
#endif
} T_CnCTR_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CnCTR_BIT BIT;
} T_CnCTR;

typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 CHMDC :2;
	T_U32 CSLPR :1;
	T_U32 RTBO :1;
	T_U32 :4;
	T_U32 BEIE :1;
	T_U32 EWIE :1;
	T_U32 EPIE :1;
	T_U32 BOEIE :1;
	T_U32 BORIE :1;
	T_U32 OLIE :1;
	T_U32 BLIE :1;
	T_U32 ALIE :1;
	T_U32 TAIE :1;
	T_U32 EOCOIE :1;
	T_U32 SOCOIE :1;
	T_U32 TDCVFIE :1;
	T_U32 :1;
	T_U32 BOM :2;
	T_U32 ERRD :1;
	T_U32 CTME :1;
	T_U32 CTMS :2;
	T_U32 TRWE :1;
	T_U32 TRH :1;
	T_U32 TRR :1;
	T_U32 CRCT :1;
	T_U32 ROM :1;
#endif
} T_CFDCnCTR_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFDCnCTR_BIT BIT;
} T_CFDCnCTR;

/* CnSTS / CFDCnSTS */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 CRSTSTS :1;
	T_U32 CHLTSTS :1;
	T_U32 CSLPSTS :1;
	T_U32 EPSTS :1;
	T_U32 BOSTS :1;
	T_U32 TRMSTS :1;
	T_U32 RECSTS :1;
	T_U32 COMSTS :1;
	T_U32 :8;
	T_U32 REC :8;
	T_U32 TEC :8;
#endif
} T_CnSTS_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CnSTS_BIT BIT;
} T_CnSTS;

typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 CRSTSTS :1;
	T_U32 CHLTSTS :1;
	T_U32 CSLPSTS :1;
	T_U32 EPSTS :1;
	T_U32 BOSTS :1;
	T_U32 TRMSTS :1;
	T_U32 RECSTS :1;
	T_U32 COMSTS :1;
	T_U32 ESIF :1;
	T_U32 :7;
	T_U32 REC :8;
	T_U32 TEC :8;
#endif
} T_CFDCnSTS_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFDCnSTS_BIT BIT;
} T_CFDCnSTS;

/* (CFD)CnERFL */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 BEF :1;
	T_U32 EWF :1;
	T_U32 EPF :1;
	T_U32 BOEF :1;
	T_U32 BORF :1;
	T_U32 OVLF :1;
	T_U32 BLF :1;
	T_U32 ALF :1;
	T_U32 SERR :1;
	T_U32 FERR :1;
	T_U32 AERR :1;
	T_U32 CERR :1;
	T_U32 B1ERR :1;
	T_U32 B0ERR :1;
	T_U32 ADERR :1;
	T_U32 :1;
	T_U32 CRCREG :15;
	T_U32 :1;
#endif
} T_CnERFL_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CnERFL_BIT BIT;
} T_CnERFL;

/* CHANNEL group register (CnCFG, CnCTR, CnSTS, CnERFL) */
typedef RSC_VOLATILE struct
{
	T_CnCFG CnCFG;
	T_CnCTR CnCTR;
	T_CnSTS CnSTS;
	T_CnERFL CnERFL;
} T_CAN_CHANNEL;

/* FD CHANNEL group1 register (CFDCnNCFG, CFDCnCTR, CFDCnSTS, CnERFL) */
typedef RSC_VOLATILE struct
{
	T_CFDCnNCFG CFDCnNCFG;
	T_CFDCnCTR CFDCnCTR;
	T_CFDCnSTS CFDCnSTS;
	T_CnERFL CFDCnERFL;
} T_CANFD_CHANNEL_GROUP1;

/* (CFD)GIPV */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 IPV :8;
	T_U32 IPT :2;
	T_U32 :22;
#endif
} T_GIPV_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_GIPV_BIT BIT;
} T_GIPV;

/* GCFG / CFDGCFG */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 TPRI :1;
	T_U32 DCE :1;
	T_U32 DRE :1;
	T_U32 MME :1;
	T_U32 DCS :1;
	T_U32 :1;
	T_U32 EEFE :1;
	T_U32 TMTSCE :1;
	T_U32 TSP :4;
	T_U32 TSSS :1;
	T_U32 TSBTCS :3;
	T_U32 ITRCP :16;
#endif
} T_GCFG_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_GCFG_BIT BIT;
} T_GCFG;

typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 TPRI :1;
	T_U32 DCE :1;
	T_U32 DRE :1;
	T_U32 MME :1;
	T_U32 DCS :1;
	T_U32 CMPOC :1;
	T_U32 EEFE :1;
	T_U32 TMTSCE :1;
	T_U32 TSP :4;
	T_U32 TSSS :1;
	T_U32 TSBTCS :3;
	T_U32 ITRCP :16;
#endif
} T_CFDGCFG_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFDGCFG_BIT BIT;
} T_CFDGCFG;

/* GCTR / CFDGCTR */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 GMDC :2;
	T_U32 GSLPR :1;
	T_U32 :5;
	T_U32 DEIE :1;
	T_U32 MEIE :1;
	T_U32 THLEIE :1;
	T_U32 :5;
	T_U32 TSRST :1;
	T_U32 TSWR :1;
	T_U32 :14;
#endif
} T_GCTR_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_GCTR_BIT BIT;
} T_GCTR;

typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 GMDC :2;
	T_U32 GSLPR :1;
	T_U32 :5;
	T_U32 DEIE :1;
	T_U32 MEIE :1;
	T_U32 THLEIE :1;
	T_U32 CMPOFIE :1;
	T_U32 :4;
	T_U32 TSRST :1;
	T_U32 TSWR :1;
	T_U32 :14;
#endif
} T_CFDGCTR_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFDGCTR_BIT BIT;
} T_CFDGCTR;

/* (CFD)GSTS */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 GRSTSTS :1;
	T_U32 GHLTSTS :1;
	T_U32 GSLPSTS :1;
	T_U32 GRAMINIT :1;
	T_U32 :28;
#endif
} T_GSTS_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_GSTS_BIT BIT;
} T_GSTS;

/* GERFL / CFDGERFL */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 DEF :1;
	T_U32 MES :1;
	T_U32 THLES :1;
	T_U32 :2;
	T_U32 OTBMLTSTS :1;
	T_U32 :2;
	T_U32 RXSFAIL0 :1;
	T_U32 RXSFAIL1 :1;
	T_U32 RXSFAIL2 :1;
	T_U32 RXSFAIL3 :1;
	T_U32 RXSFAIL4 :1;
	T_U32 RXSFAIL5 :1;
	T_U32 :2;
	T_U32 EEF0 :1;
	T_U32 EEF1 :1;
	T_U32 EEF2 :1;
	T_U32 EEF3 :1;
	T_U32 EEF4 :1;
	T_U32 EEF5 :1;
	T_U32 :10;
#endif
} T_GERFL_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_GERFL_BIT BIT;
} T_GERFL;

typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 DEF :1;
	T_U32 MES :1;
	T_U32 THLES :1;
	T_U32 CMPOF :1;
	T_U32 :1;
	T_U32 OTBMLTSTS :1;
	T_U32 :2;
	T_U32 RXSFAIL0 :1;
	T_U32 RXSFAIL1 :1;
	T_U32 RXSFAIL2 :1;
	T_U32 RXSFAIL3 :1;
	T_U32 RXSFAIL4 :1;
	T_U32 RXSFAIL5 :1;
	T_U32 :2;
	T_U32 EEF0 :1;
	T_U32 EEF1 :1;
	T_U32 EEF2 :1;
	T_U32 EEF3 :1;
	T_U32 EEF4 :1;
	T_U32 EEF5 :1;
	T_U32 :10;
#endif
} T_CFDGERFL_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFDGERFL_BIT BIT;
} T_CFDGERFL;

/* (CFD)GTINTSTSv */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 TSIF0 :1;
	T_U32 TAIF0 :1;
	T_U32 TQIF0 :1;
	T_U32 CFTIF0 :1;
	T_U32 THIF0 :1;
	T_U32 :3;
	T_U32 TSIF1 :1;
	T_U32 TAIF1 :1;
	T_U32 TQIF1 :1;
	T_U32 CFTIF1 :1;
	T_U32 THIF1 :1;
	T_U32 :3;
	T_U32 TSIF2 :1;
	T_U32 TAIF2 :1;
	T_U32 TQIF2 :1;
	T_U32 CFTIF2 :1;
	T_U32 THIF2 :1;
	T_U32 :3;
	T_U32 TSIF3 :1;
	T_U32 TAIF3 :1;
	T_U32 TQIF3 :1;
	T_U32 CFTIF3 :1;
	T_U32 THIF3 :1;
	T_U32 :3;
#endif
} T_GTINTSTS_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_GTINTSTS_BIT BIT;
} T_GTINTSTS;

/* (CFD)GTSC */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 TS :16;
	T_U32 :16;
#endif
} T_GTSC_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_GTSC_BIT BIT;
} T_GTSC;

/* (CFD)GAFLECTR */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 AFLPN :5;
	T_U32 :3;
	T_U32 AFLDAE :1;
	T_U32 :23;
#endif
} T_GAFLECTR_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_GAFLECTR_BIT BIT;
} T_GAFLECTR;

/* RMNB / CFDRMNB */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 NRXMB :8;
	T_U32 :24;
#endif
} T_RMNB_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_RMNB_BIT BIT;
} T_RMNB;

typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 NRXMB :8;
	T_U32 RMPLS :2;
	T_U32 :22;
#endif
} T_CFDRMNB_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFDRMNB_BIT BIT;
} T_CFDRMNB;

/* (CFD)GAFLCFGw (w=0,1) */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 RNC3 :8;
	T_U32 RNC2 :8;
	T_U32 RNC1 :8;
	T_U32 RNC0 :8;
#endif
} T_GAFLCFG0_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_GAFLCFG0_BIT BIT;
} T_GAFLCFG0;

typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 RNC7 :8;
	T_U32 RNC6 :8;
	T_U32 RNC5 :8;
	T_U32 RNC4 :8;
#endif
} T_GAFLCFG1_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_GAFLCFG1_BIT BIT;
} T_GAFLCFG1;

/* (CFD)RMNDt */
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_BIT BIT;
} T_RMND;

/* RFCCa / CFDRFCCa */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 RFE :1;
	T_U32 RFIE :1;
	T_U32 :6;
	T_U32 RFDC :3;
	T_U32 :1;
	T_U32 RFIM :1;
	T_U32 RFIGCV :3;
	T_U32 :16;
#endif
} T_RFCC_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_RFCC_BIT BIT;
} T_RFCC;

typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 RFE :1;
	T_U32 RFIE :1;
	T_U32 :2;
	T_U32 RFPLS :3;
	T_U32 :1;
	T_U32 RFDC :3;
	T_U32 :1;
	T_U32 RFIM :1;
	T_U32 RFIGCV :3;
	T_U32 :16;
#endif
} T_CFDRFCC_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFDRFCC_BIT BIT;
} T_CFDRFCC;

/* (CFD)RFSTSa */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 RFEMP :1;
	T_U32 RFFLL :1;
	T_U32 RFMLT :1;
	T_U32 RFIF :1;
	T_U32 :4;
	T_U32 RFMC :8;
	T_U32 :16;
#endif
} T_RFSTS_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_RFSTS_BIT BIT;
} T_RFSTS;

/* (CFD)RFPCTRa */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 RFPC :8;
	T_U32 :24;
#endif
} T_RFPCTR_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_RFPCTR_BIT BIT;
} T_RFPCTR;

/* CFCCd / CFDCFCCd */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 CFE :1;
	T_U32 CFRXIE :1;
	T_U32 CFTXIE :1;
	T_U32 :5;
	T_U32 CFDC :3;
	T_U32 :1;
	T_U32 CFIM :1;
	T_U32 CFIGCV :3;
	T_U32 CFM :2;
	T_U32 CFITSS :1;
	T_U32 CFITR :1;
	T_U32 CFTML :4;
	T_U32 CFITT :8;
#endif
} T_CFCC_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFCC_BIT BIT;
} T_CFCC;

typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 CFE :1;
	T_U32 CFRXIE :1;
	T_U32 CFTXIE :1;
	T_U32 :1;
	T_U32 CFPLS :3;
	T_U32 :1;
	T_U32 CFDC :3;
	T_U32 :1;
	T_U32 CFIM :1;
	T_U32 CFIGCV :3;
	T_U32 CFM :2;
	T_U32 CFITSS :1;
	T_U32 CFITR :1;
	T_U32 CFTML :4;
	T_U32 CFITT :8;
#endif
} T_CFDCFCC_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFDCFCC_BIT BIT;
} T_CFDCFCC;

/* (CFD)CFSTSd */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 CFEMP :1;
	T_U32 CFFLL :1;
	T_U32 CFMLT :1;
	T_U32 CFRXIF :1;
	T_U32 CFTXIF :1;
	T_U32 :3;
	T_U32 CFMC :8;
	T_U32 :16;
#endif
} T_CFSTS_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFSTS_BIT BIT;
} T_CFSTS;

/* (CFD)CFPCTRd  */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 CFPC :8;
	T_U32 :24;
#endif
} T_CFPCTR_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFPCTR_BIT BIT;
} T_CFPCTR;

/* (CFD)FESTS */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 RF0EMP :1;
	T_U32 RF1EMP :1;
	T_U32 RF2EMP :1;
	T_U32 RF3EMP :1;
	T_U32 RF4EMP :1;
	T_U32 RF5EMP :1;
	T_U32 RF6EMP :1;
	T_U32 RF7EMP :1;
	T_U32 CF0EMP :1;
	T_U32 CF1EMP :1;
	T_U32 CF2EMP :1;
	T_U32 CF3EMP :1;
	T_U32 CF4EMP :1;
	T_U32 CF5EMP :1;
	T_U32 CF6EMP :1;
	T_U32 CF7EMP :1;
	T_U32 CF8EMP :1;
	T_U32 CF9EMP :1;
	T_U32 CF10EMP :1;
	T_U32 CF11EMP :1;
	T_U32 CF12EMP :1;
	T_U32 CF13EMP :1;
	T_U32 CF14EMP :1;
	T_U32 CF15EMP :1;
	T_U32 CF16EMP :1;
	T_U32 CF17EMP :1;
	T_U32 :6;
#endif
} T_FESTS_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_FESTS_BIT BIT;
} T_FESTS;

/* (CFD)FFSTS */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 RF0FLL :1;
	T_U32 RF1FLL :1;
	T_U32 RF2FLL :1;
	T_U32 RF3FLL :1;
	T_U32 RF4FLL :1;
	T_U32 RF5FLL :1;
	T_U32 RF6FLL :1;
	T_U32 RF7FLL :1;
	T_U32 CF0FLL :1;
	T_U32 CF1FLL :1;
	T_U32 CF2FLL :1;
	T_U32 CF3FLL :1;
	T_U32 CF4FLL :1;
	T_U32 CF5FLL :1;
	T_U32 CF6FLL :1;
	T_U32 CF7FLL :1;
	T_U32 CF8FLL :1;
	T_U32 CF9FLL :1;
	T_U32 CF10FLL :1;
	T_U32 CF11FLL :1;
	T_U32 CF12FLL :1;
	T_U32 CF13FLL :1;
	T_U32 CF14FLL :1;
	T_U32 CF15FLL :1;
	T_U32 CF16FLL :1;
	T_U32 CF17FLL :1;
	T_U32 :6;
#endif
} T_FFSTS_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_FFSTS_BIT BIT;
} T_FFSTS;

/* (CFD)FMSTS */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 RF0MLT :1;
	T_U32 RF1MLT :1;
	T_U32 RF2MLT :1;
	T_U32 RF3MLT :1;
	T_U32 RF4MLT :1;
	T_U32 RF5MLT :1;
	T_U32 RF6MLT :1;
	T_U32 RF7MLT :1;
	T_U32 CF0MLT :1;
	T_U32 CF1MLT :1;
	T_U32 CF2MLT :1;
	T_U32 CF3MLT :1;
	T_U32 CF4MLT :1;
	T_U32 CF5MLT :1;
	T_U32 CF6MLT :1;
	T_U32 CF7MLT :1;
	T_U32 CF8MLT :1;
	T_U32 CF9MLT :1;
	T_U32 CF10MLT :1;
	T_U32 CF11MLT :1;
	T_U32 CF12MLT :1;
	T_U32 CF13MLT :1;
	T_U32 CF14MLT :1;
	T_U32 CF15MLT :1;
	T_U32 CF16MLT :1;
	T_U32 CF17MLT :1;
	T_U32 :6;
#endif
} T_FMSTS_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_FMSTS_BIT BIT;
} T_FMSTS;

/* (CFD)RFISTS */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 RF0IF :1;
	T_U32 RF1IF :1;
	T_U32 RF2IF :1;
	T_U32 RF3IF :1;
	T_U32 RF4IF :1;
	T_U32 RF5IF :1;
	T_U32 RF6IF :1;
	T_U32 RF7IF :1;
	T_U32 :24;
#endif
} T_RFISTS_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_RFISTS_BIT BIT;
} T_RFISTS;

/* (CFD)CFRISTS */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 CF0RXIF :1;
	T_U32 CF1RXIF :1;
	T_U32 CF2RXIF :1;
	T_U32 CF3RXIF :1;
	T_U32 CF4RXIF :1;
	T_U32 CF5RXIF :1;
	T_U32 CF6RXIF :1;
	T_U32 CF7RXIF :1;
	T_U32 CF8RXIF :1;
	T_U32 CF9RXIF :1;
	T_U32 CF10RXIF :1;
	T_U32 CF11RXIF :1;
	T_U32 CF12RXIF :1;
	T_U32 CF13RXIF :1;
	T_U32 CF14RXIF :1;
	T_U32 CF15RXIF :1;
	T_U32 CF16RXIF :1;
	T_U32 CF17RXIF :1;
	T_U32 :14;
#endif
} T_CFRISTS_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFRISTS_BIT BIT;
} T_CFRISTS;

/* (CFD)CFTISTS */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 CF0TXIF :1;
	T_U32 CF1TXIF :1;
	T_U32 CF2TXIF :1;
	T_U32 CF3TXIF :1;
	T_U32 CF4TXIF :1;
	T_U32 CF5TXIF :1;
	T_U32 CF6TXIF :1;
	T_U32 CF7TXIF :1;
	T_U32 CF8TXIF :1;
	T_U32 CF9TXIF :1;
	T_U32 CF10TXIF :1;
	T_U32 CF11TXIF :1;
	T_U32 CF12TXIF :1;
	T_U32 CF13TXIF :1;
	T_U32 CF14TXIF :1;
	T_U32 CF15TXIF :1;
	T_U32 CF16TXIF :1;
	T_U32 CF17TXIF :1;
	T_U32 :14;
#endif
} T_CFTISTS_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFTISTS_BIT BIT;
} T_CFTISTS;

/* MISRA C:2004 Violation - Rule 6.4 */
/* Justification - current compiler allows unsigned char */
/*lint -save -e46 */
/* (CFD)TMCi */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U8 TMTR :1;
	T_U8 TMTAR :1;
	T_U8 TMOM :1;
	T_U8 :5;
#endif
} T_TMC_BIT;

typedef RSC_VOLATILE union
{
	T_U8 BYTE;
	T_TMC_BIT BIT;
} T_TMC;

/* (CFD)TMSTSj */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U8 TMTSTS :1;
	T_U8 TMTRF :2;
	T_U8 TMTRM :1;
	T_U8 TMTARM :1;
	T_U8 :3;
#endif
} T_TMSTS_BIT;
typedef RSC_VOLATILE union
{
	T_U8 BYTE;
	T_TMSTS_BIT BIT;
} T_TMSTS;

/* (CFD)TMTRSTSf */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U16 TMTRSTS0 :1;
	T_U16 TMTRSTS1 :1;
	T_U16 TMTRSTS2 :1;
	T_U16 TMTRSTS3 :1;
	T_U16 TMTRSTS4 :1;
	T_U16 TMTRSTS5 :1;
	T_U16 TMTRSTS6 :1;
	T_U16 TMTRSTS7 :1;
	T_U16 TMTRSTS8 :1;
	T_U16 TMTRSTS9 :1;
	T_U16 TMTRSTS10 :1;
	T_U16 TMTRSTS11 :1;
	T_U16 TMTRSTS12 :1;
	T_U16 TMTRSTS13 :1;
	T_U16 TMTRSTS14 :1;
	T_U16 TMTRSTS15 :1;
#endif
} T_TMTRSTS_BIT;
typedef RSC_VOLATILE union
{
	T_U16 WORD;
	T_TMTRSTS_BIT BIT;
} T_TMTRSTS;

/* (CFD)TMTARSTSf */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U16 TMTARSTS0 :1;
	T_U16 TMTARSTS1 :1;
	T_U16 TMTARSTS2 :1;
	T_U16 TMTARSTS3 :1;
	T_U16 TMTARSTS4 :1;
	T_U16 TMTARSTS5 :1;
	T_U16 TMTARSTS6 :1;
	T_U16 TMTARSTS7 :1;
	T_U16 TMTARSTS8 :1;
	T_U16 TMTARSTS9 :1;
	T_U16 TMTARSTS10 :1;
	T_U16 TMTARSTS11 :1;
	T_U16 TMTARSTS12 :1;
	T_U16 TMTARSTS13 :1;
	T_U16 TMTARSTS14 :1;
	T_U16 TMTARSTS15 :1;
#endif
} T_TMTARSTS_BIT;
typedef RSC_VOLATILE union
{
	T_U16 WORD;
	T_TMTARSTS_BIT BIT;
} T_TMTARSTS;

/* (CFD)TMTCSTSf */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U16 TMTCSTS0 :1;
	T_U16 TMTCSTS1 :1;
	T_U16 TMTCSTS2 :1;
	T_U16 TMTCSTS3 :1;
	T_U16 TMTCSTS4 :1;
	T_U16 TMTCSTS5 :1;
	T_U16 TMTCSTS6 :1;
	T_U16 TMTCSTS7 :1;
	T_U16 TMTCSTS8 :1;
	T_U16 TMTCSTS9 :1;
	T_U16 TMTCSTS10 :1;
	T_U16 TMTCSTS11 :1;
	T_U16 TMTCSTS12 :1;
	T_U16 TMTCSTS13 :1;
	T_U16 TMTCSTS14 :1;
	T_U16 TMTCSTS15 :1;
#endif
} T_TMTCSTS_BIT;
typedef RSC_VOLATILE union
{
	T_U16 WORD;
	T_TMTCSTS_BIT BIT;
} T_TMTCSTS;

/* (CFD)TMTASTSf */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U16 TMTASTS0 :1;
	T_U16 TMTASTS1 :1;
	T_U16 TMTASTS2 :1;
	T_U16 TMTASTS3 :1;
	T_U16 TMTASTS4 :1;
	T_U16 TMTASTS5 :1;
	T_U16 TMTASTS6 :1;
	T_U16 TMTASTS7 :1;
	T_U16 TMTASTS8 :1;
	T_U16 TMTASTS9 :1;
	T_U16 TMTASTS10 :1;
	T_U16 TMTASTS11 :1;
	T_U16 TMTASTS12 :1;
	T_U16 TMTASTS13 :1;
	T_U16 TMTASTS14 :1;
	T_U16 TMTASTS15 :1;
#endif
} T_TMTASTS_BIT;
typedef RSC_VOLATILE union
{
	T_U16 WORD;
	T_TMTASTS_BIT BIT;
} T_TMTASTS;

/* (CFD)TMIECf */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U16 TMIE0 :1;
	T_U16 TMIE1 :1;
	T_U16 TMIE2 :1;
	T_U16 TMIE3 :1;
	T_U16 TMIE4 :1;
	T_U16 TMIE5 :1;
	T_U16 TMIE6 :1;
	T_U16 TMIE7 :1;
	T_U16 TMIE8 :1;
	T_U16 TMIE9 :1;
	T_U16 TMIE10 :1;
	T_U16 TMIE11 :1;
	T_U16 TMIE12 :1;
	T_U16 TMIE13 :1;
	T_U16 TMIE14 :1;
	T_U16 TMIE15 :1;
#endif
} T_TMIEC_BIT;
typedef RSC_VOLATILE union
{
	T_U16 WORD;
	T_TMIEC_BIT BIT;
} T_TMIEC;

/* (CFD)TXQCCn */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 TXQE :1;
	T_U32 :7;
	T_U32 TXQDC :4;
	T_U32 TXQIE :1;
	T_U32 TXQIM :1;
	T_U32 :18;
#endif
} T_TXQCC_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_TXQCC_BIT BIT;
} T_TXQCC;

/* (CFD)TXQSTSn */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 TXQEMP :1;
	T_U32 TXQFLL :1;
	T_U32 TXQIF :1;
	T_U32 :5;
	T_U32 TXQMC :5;
	T_U32 :19;
#endif
} T_TXQSTS_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_TXQSTS_BIT BIT;
} T_TXQSTS;

/* (CFD)TXQPCTRn */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 TXQPC :8;
	T_U32 :24;
#endif
} T_TXQPCTR_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_TXQPCTR_BIT BIT;
} T_TXQPCTR;

/* (CFD)THLCCn */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 THLE :1;
	T_U32 :7;
	T_U32 THLIE :1;
	T_U32 THLIM :1;
	T_U32 THLDTE :1;
	T_U32 :21;
#endif
} T_THLCC_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_THLCC_BIT BIT;
} T_THLCC;

/* (CFD)THLSTSn */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 THLEMP :1;
	T_U32 THLFLL :1;
	T_U32 THLELT :1;
	T_U32 THLIF :1;
	T_U32 :4;
	T_U32 THLMC :5;
	T_U32 :19;
#endif
} T_THLSTS_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_THLSTS_BIT BIT;
} T_THLSTS;

/* (CFD)THLPCTRn */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 THLPC :8;
	T_U32 :24;
#endif
} T_THLPCTR_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_THLPCTR_BIT BIT;
} T_THLPCTR;

/* (CFD)GTSTCFG */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 C0ICBCE :1;
	T_U32 C1ICBCE :1;
	T_U32 C2ICBCE :1;
	T_U32 C3ICBCE :1;
	T_U32 C4ICBCE :1;
	T_U32 C5ICBCE :1;
	T_U32 :10;
	T_U32 RTMPS :7;
	T_U32 :9;
#endif
} T_GTSTCFG_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_GTSTCFG_BIT BIT;
} T_GTSTCFG;

/* (CFD)GTSTCTR */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 ICBCTME :1;
	T_U32 :1;
	T_U32 RTME :1;
	T_U32 :29;
#endif
} T_GTSTCTR_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_GTSTCTR_BIT BIT;
} T_GTSTCTR;

/* (CFD)GLOCKK */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 LOCK :16;
	T_U32 :16;
#endif
} T_GLOCKK_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_GLOCKK_BIT BIT;
} T_GLOCKK;

/* (CFD)GLOTB */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 OTBFE :1;
	T_U32 :7;
	T_U32 OTBEMP :1;
	T_U32 OTBFLL :1;
	T_U32 OTBMLT :1;
	T_U32 OTBMC :5;
	T_U32 :16;
#endif
} T_GLOTB_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_GLOTB_BIT BIT;
} T_GLOTB;

/* CFDCDTCT */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 RFDMAE0 :1;
	T_U32 RFDMAE1 :1;
	T_U32 RFDMAE2 :1;
	T_U32 RFDMAE3 :1;
	T_U32 RFDMAE4 :1;
	T_U32 RFDMAE5 :1;
	T_U32 RFDMAE6 :1;
	T_U32 RFDMAE7 :1;
	T_U32 CFDMAE0 :1;
	T_U32 CFDMAE1 :1;
	T_U32 CFDMAE2 :1;
	T_U32 CFDMAE3 :1;
	T_U32 CFDMAE4 :1;
	T_U32 CFDMAE5 :1;
	T_U32 :18;
#endif
} T_CFDCDTCT_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFDCDTCT_BIT BIT;
} T_CFDCDTCT;

/* CFDCDTSTS */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 RFDMASTS0 :1;
	T_U32 RFDMASTS1 :1;
	T_U32 RFDMASTS2 :1;
	T_U32 RFDMASTS3 :1;
	T_U32 RFDMASTS4 :1;
	T_U32 RFDMASTS5 :1;
	T_U32 RFDMASTS6 :1;
	T_U32 RFDMASTS7 :1;
	T_U32 CFDMASTS0 :1;
	T_U32 CFDMASTS1 :1;
	T_U32 CFDMASTS2 :1;
	T_U32 CFDMASTS3 :1;
	T_U32 CFDMASTS4 :1;
	T_U32 CFDMASTS5 :1;
	T_U32 :18;
#endif
} T_CFDCDTSTS_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFDCDTSTS_BIT BIT;
} T_CFDCDTSTS;

/* GCFDT */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 CFDTE :1;
	T_U32 :31;
#endif
} T_GCFDT_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_GCFDT_BIT BIT;
} T_GCFDT;

/* CFDGRMCFG */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 RCMC :1;
	T_U32 :31;
#endif
} T_CFDGRMCFG_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFDGRMCFG_BIT BIT;
} T_CFDGRMCFG;

/* CFDCnDCFG */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 DBRP :8;
	T_U32 :8;
	T_U32 DTSEG1 :4;
	T_U32 DTSEG2 :3;
	T_U32 :1;
	T_U32 DSJW :3;
	T_U32 :5;
#endif
} T_CFDCnDCFG_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFDCnDCFG_BIT BIT;
} T_CFDCnDCFG;

/* CFDCnCFG */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 EOCCFG :3;
	T_U32 :5;
	T_U32 TDCOC :1;
	T_U32 TDCE :1;
	T_U32 ESIC :1;
	T_U32 :5;
	T_U32 DTDCO :7;
	T_U32 :1;
	T_U32 GWEN :1;
	T_U32 GWFDF :1;
	T_U32 GWBRS :1;
	T_U32 TMME :1;
	T_U32 :4;
#endif
} T_CFDCnCFG_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFDCnCFG_BIT BIT;
} T_CFDCnCFG;

/* CFDCnFDCTR */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 EOCCLR :1;
	T_U32 SOCCLR :1;
	T_U32 :30;
#endif
} T_CFDCnFDCTR_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFDCnFDCTR_BIT BIT;
} T_CFDCnFDCTR;

/* CFDCnFDSTS */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 TDCR :7;
	T_U32 TDCVF :1;
	T_U32 EOCO :1;
	T_U32 SOCO :1;
	T_U32 :6;
	T_U32 EOC :8;
	T_U32 SOC :8;
#endif
} T_CFDCnFDSTS_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFDCnFDSTS_BIT BIT;
} T_CFDCnFDSTS;

/* CFDCnCRC */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 CRCREG :21;
	T_U32 :11;
#endif
} T_CFDCnCRC_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFDCnCRC_BIT BIT;
} T_CFDCnCRC;

/* CANFD Channel Register Group 2 */
typedef RSC_VOLATILE struct
{
	T_CFDCnDCFG CFDCnDCFG;
	T_CFDCnCFG CFDCnCFG;
	T_CFDCnFDCTR CFDCnFDCTR;
	T_CFDCnFDSTS CFDCnFDSTS;
	T_CFDCnCRC CFDCnCRC;
	T_U32 RSVD[3];
} T_CANFD_CHANNEL_GROUP2;

/* (CFD)GAFLIDr */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 GAFLID :29;
	T_U32 GAFLLB :1;
	T_U32 GAFLRTR :1;
	T_U32 GAFLIDE :1;
#endif
} T_GAFLID_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_GAFLID_BIT BIT;
} T_GAFLID;

/* (CFD)GAFLMr */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 GAFLIDM :29;
	T_U32 :1;
	T_U32 GAFLRTRM :1;
	T_U32 GAFLIDEM :1;
#endif
} T_GAFLM_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_GAFLM_BIT BIT;
} T_GAFLM;

/* (CFD)GAFLP0r */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 :8;
	T_U32 GAFLRMDP :7;
	T_U32 GAFLRMV :1;
	T_U32 CFDGAFLPTR :12;
	T_U32 GAFLDLC :4;
#endif
} T_GAFLP0_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_GAFLP0_BIT BIT;
} T_GAFLP0;

/* (CFD)GAFLP1r */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 GAFLFDP :26;
	T_U32 :6;
#endif
} T_GAFLP1_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_GAFLP1_BIT BIT;
} T_GAFLP1;

/* GAFL : global acceptance filter list */
typedef RSC_VOLATILE struct
{
	T_GAFLID GAFLID;
	T_GAFLM GAFLM;
	T_GAFLP0 GAFLP0;
	T_GAFLP1 GAFLP1;
} T_GAFL;

/* THLACCn / CFDTHLACCn */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 BT :3;
	T_U32 BN :4;
	T_U32 :1;
	T_U32 TID :8;
	T_U32 TMTS :16;
#endif
} T_THLACC_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_THLACC_BIT BIT;
} T_THLACC;

/* (CFD)RPGACCk */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	T_U32 RDTA:32;
#else
	T_U32 RDTA :32;
#endif
} T_RPGACC_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_RPGACC_BIT BIT;
} T_RPGACC;

/* (CFD)RMID */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 RMID :29;
	T_U32 :1;
	T_U32 RMRTR :1;
	T_U32 RMIDE :1;
#endif
} T_RMID_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_RMID_BIT BIT;
} T_RMID;

/* (CFD)RMPTR */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 RMTS :16;
	T_U32 RMPTR :12;
	T_U32 RMDLC :4;
#endif
} T_RMPTR_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_RMPTR_BIT BIT;
} T_RMPTR;

/* CFDRMFDSTS */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 RMESI :1;
	T_U32 RMBRS :1;
	T_U32 RMFDF :1;
	T_U32 :29;
#endif
} T_CFDRMFDSTS_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFDRMFDSTS_BIT BIT;
} T_CFDRMFDSTS;

/* (CFD)RMDFp */

/* RMBCP : Rx Message Buffer Component */
typedef RSC_VOLATILE struct
{
	T_RMID RMID;
	T_RMPTR RMPTR;
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U8 RMDF_RMDB[8];
#endif
} T_RMBCP;

typedef RSC_VOLATILE struct
{
	T_RMID CFDRMID;
	T_RMPTR CFDRMPTR;
	T_CFDRMFDSTS CFDRMFDSTS;
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U8 CFDRMDF_RMDB[20];
#endif
} T_CFDRMBCP;

/* (CFD)RFID */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 RFID :29;
	T_U32 :1;
	T_U32 RFRTR :1;
	T_U32 RFIDE :1;
#endif
} T_RFID_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_RFID_BIT BIT;
} T_RFID;

/* (CFD)RFPTR */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 RFTS :16;
	T_U32 RFPTR :12;
	T_U32 RFDLC :4;
#endif
} T_RFPTR_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_RFPTR_BIT BIT;
} T_RFPTR;

/* CFDRFFDSTS */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 RFESI :1;
	T_U32 RFBRS :1;
	T_U32 RFFDF :1;
	T_U32 :29;
#endif
} T_CFDRFFDSTS_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFDRFFDSTS_BIT BIT;
} T_CFDRFFDSTS;

/* (CFD)RFDFp */

/* RFMBCP: Rx FIFO Message Buffer Component */
typedef RSC_VOLATILE struct
{
	T_RFID RFID;
	T_RFPTR RFPTR;
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U8 RFDF_RFDB[8];
#endif
} T_RFMBCP;

typedef RSC_VOLATILE struct
{
	T_RFID CFDRFID;
	T_RFPTR CFDRFPTR;
	T_CFDRFFDSTS CFDRFFDSTS;
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U8 CFDRFDF_RFDB[64];
#endif
	T_U32 RSVD[13];
} T_CFDRFMBCP;

/* (CFD)CFID */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 CFID :29;
	T_U32 THLEN :1;
	T_U32 CFRTR :1;
	T_U32 CFIDE :1;
#endif
} T_CFID_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFID_BIT BIT;
} T_CFID;

/* (CFD)CFPTR */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 CFTS :16;
	T_U32 CFPTR :12;
	T_U32 CFDLC :4;
#endif
} T_CFPTR_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFPTR_BIT BIT;
} T_CFPTR;

/* CFDCFFDCSTS */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 CFESI :1;
	T_U32 CFBRS :1;
	T_U32 CFFDF :1;
	T_U32 :29;
#endif
} T_CFDCFFDCSTS_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFDCFFDCSTS_BIT BIT;
} T_CFDCFFDCSTS;

/* (CFD)CFDFp */

/* CFMBCP: Common FIFO Message Buffer Component */
typedef RSC_VOLATILE struct
{
	T_CFID CFID;
	T_CFPTR CFPTR;
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U8 CFDF_CFDB[8];
#endif
} T_CFMBCP;

typedef RSC_VOLATILE struct
{
	T_CFID CFDCFID;
	T_CFPTR CFDCFPTR;
	T_CFDCFFDCSTS CFDCFFDCSTS;
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U8 CFDCFDF_CFDB[64];
#endif
	T_U32 RSVD[13];
} T_CFDCFMBCP;

/* (CFD)TMID */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 TMID :29;
	T_U32 THLEN :1;
	T_U32 TMRTR :1;
	T_U32 TMIDE :1;
#endif
} T_TMID_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_TMID_BIT BIT;
} T_TMID;

/* (CFD)TMPTR */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 :16;
	T_U32 TMPTR :8;
	T_U32 :4;
	T_U32 TMDLC :4;
#endif
} T_TMPTR_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_TMPTR_BIT BIT;
} T_TMPTR;

/* CFDTMFDCTR */
typedef RSC_VOLATILE struct
{
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U32 TMESI :1;
	T_U32 TMBRS :1;
	T_U32 TMFDF :1;
	T_U32 :29;
#endif
} T_CFDTMFDCTR_BIT;
typedef RSC_VOLATILE union
{
	T_LONG LONG;
	T_WORD WORD;
	T_BYTE BYTE;
	T_CFDTMFDCTR_BIT BIT;
} T_CFDTMFDCTR;

/* (CFD)TMDFp */

/* TMBCP: Tx Message Buffer Component */
typedef RSC_VOLATILE struct
{
	T_TMID TMID;
	T_TMPTR TMPTR;
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U8 TMDF_TMDB[8];
#endif
} T_TMBCP;

typedef RSC_VOLATILE struct
{
	T_TMID CFDTMID;
	T_TMPTR CFDTMPTR;
	T_CFDTMFDCTR CFDTMFDCTR;
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U8 CFDTMDF_TMDB[20];
#endif
} T_CFDTMBCP;

/* TMBCP in merge mode */
typedef RSC_VOLATILE struct
{
	T_TMID CFDTMID;
	T_TMPTR CFDTMPTR;
	T_CFDTMFDCTR CFDTMFDCTR;
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_U8 CFDTMDF_TMDB[64];
#endif
} T_CFDTMBCPMD;

/* ---- RSCAN structure : CAN ISO 11898-1(2003) ---- */
/* PACK ON */
typedef RSC_VOLATILE struct
{
	T_CAN_CHANNEL CHANNEL[8]; /* 0000h : CAN channel register group */
	T_GIPV GIPV; /* 0080h : Global IP Version Register */
	T_GCFG GCFG; /* 0084h : Global Configuration Register */
	T_GCTR GCTR; /* 0088h : Global Control Register  */
	T_GSTS GSTS; /* 008ch : Global Status Register */
	T_GERFL GERFL; /* 0090h : Global Error Flag Register */
	T_GTSC GTSC; /* 0094h : Global Timestamp Counter Register */
	T_GAFLECTR GAFLECTR; /* 0098h : Global Acceptance Filter List Entry Control Register */
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	T_U8 GAFLCFG_RNC[8]; /* 009ch : Global Acceptance Filter List Configuration Register w */
#else
	T_GAFLCFG0 GAFLCFG0; /* 009ch : Global Acceptance Filter List Configuration Register 0 */
	T_GAFLCFG1 GAFLCFG1; /* 00A0h : Global Acceptance Filter List Configuration Register 1 */
#endif
	T_RMNB RMNB; /* 00A4h : RX Message Buffer Number Register */
	T_RMND RMND[4]; /* 00A8h : RX Message Buffer New Data Register */
	T_RFCC RFCC[8]; /* 00B8h : RX FIFO Configuration / Control Registers */
	T_RFSTS RFSTS[8]; /* 00D8h : RX FIFO Status Registers */
	T_RFPCTR RFPCTR[8]; /* 00F8h : RX FIFO Pointer Control Registers */
	T_CFCC CFCC[8][3]; /* 0118h : Common FIFO Configuration / Control Registers */
	T_CFSTS CFSTS[8][3]; /* 0178h : Common FIFO Status Registers */
	T_CFPCTR CFPCTR[8][3]; /* 01D8h : Common FIFO Pointer Control Registers */
	T_FESTS FESTS; /* 0238h : FIFO Empty Status Register */
	T_FFSTS FFSTS; /* 023Ch : FIFO Full Status Register */
	T_FMSTS FMSTS; /* 0240h : FIFO Message Lost Status Register */
	T_RFISTS RFISTS; /* 0244h : RX FIFO Interrupt Flag Status Register */
	T_CFRISTS CFRISTS; /* 0248h : Common FIFO RX Interrupt Flag Status Register */
	T_CFTISTS CFTISTS; /* 024Ch : Common FIFO TX Interrupt Flag Status Register */
	T_TMC TMC[8][16]; /* 0250h : TX Message Buffer Control Registers */
	T_TMSTS TMSTS[8][16]; /* 02D0h : TX Message Buffer Status Registers */
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_TMTRSTS TMTRSTS[8]; /* 0350h : TX Message Buffer Transmission Request Status Register */
	T_TMTARSTS TMTARSTS[8]; /* 0360h : TX Message Buffer Transmission Abort Request Status Register */
	T_TMTCSTS TMTCSTS[8]; /* 0370h : TX Message Buffer Transmission Completion Status Register */
	T_TMTASTS TMTASTS[8]; /* 0380h : TX Message Buffer Transmission Abort Status Register */
	T_TMIEC TMIEC[8]; /* 0390h : TX Message Buffer Interrupt Enable Configuration */
#endif
	T_TXQCC TXQCC[8]; /* 03A0h : TX Queue Configuration / Control Registers */
	T_TXQSTS TXQSTS[8]; /* 03C0h : TX Queue Status Registers */
	T_TXQPCTR TXQPCTR[8]; /* 03E0h : TX Queue Pointer Control Registers */
	T_THLCC THLCC[8]; /* 0400h : TX History List Configuration / Control Register */
	T_THLSTS THLSTS[8]; /* 0420h : TX History List Status Register */
	T_THLPCTR THLPCTR[8]; /* 0440h : TX History List Pointer Control Registers */
	T_U32 DUMMY1; /* 0460h : (CAN Parity Control Register) */
	T_U32 DUMMY2; /* 0464h : (CAN Parity Error Address Register) */
	T_GTSTCFG GTSTCFG; /* 0468h : Global Test Configuration Register */
	T_GTSTCTR GTSTCTR; /* 046Ch : Global Test Control Register */
	T_U32 DUMMY3[3]; /* 0470h : reserved */
	T_GLOCKK GLOCKK; /* 047Ch : Global Lock Key Register */
	T_GLOTB GLOTB; /* 0480h : Global OTB FIFO Configuration / Status Register */
	T_U32 DUMMY4[29]; /* 0484h : reserved */
	T_GCFDT GCFDT; /* 04F8h : Global OTB FIFO Configuration / Status Register */
	T_U32 DUMMY5; /* 04FCh : reserved */
	T_GAFL GAFL[16]; /* 0500h : Global Acceptance Filter List Registers */
	T_RMBCP RMBCP[128]; /* 0600h : RX Message Buffer Component */
	T_RFMBCP RFMBCP[8]; /* 0E00h : RX FIFO Message Buffer Component */
	T_CFMBCP CFMBCP[8][3]; /* 0E80h : Common FIFO Message Buffer Component */
	T_TMBCP TMBCP[8][16]; /* 1000h : TX Message Buffer Component */
	T_THLACC THLACC[8]; /* 1800h : TX History List Access Registers */
	T_U32 DUMMY6[56]; /* 1820h : reserved */
	T_RPGACC RPGACC[64]; /* 1900h : RAM Test Page Access Registers */
} T_RSCAN;
/* PACK OFF */

/* ---- RSCAN-FD structure : CAN-FD ISO 11898-1(2014) ---- */
/* PACK ON */
typedef RSC_VOLATILE struct
{
	T_CANFD_CHANNEL_GROUP1 CHANNEL_GROUP1[8]; /* 0000h : CAN FD channel register group 1 */
	T_GIPV CFDGIPV; /* 0080h : Global IP Version Register */
	T_CFDGCFG CFDGCFG; /* 0084h : Global Configuration Register */
	T_CFDGCTR CFDGCTR; /* 0088h : Global Control Register  */
	T_GSTS CFDGSTS; /* 008ch : Global Status Register */
	T_CFDGERFL CFDGERFL; /* 0090h : Global Error Flag Register */
	T_GTSC CFDGTSC; /* 0094h : Global Timestamp Counter Register */
	T_GAFLECTR CFDGAFLECTR; /* 0098h : Global Acceptance Filter List Entry Control Register */
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	T_U8 GAFLCFG_RNC[8]; /* 009ch : Global Acceptance Filter List Configuration Register w */
#else
	T_GAFLCFG0 CFDGAFLCFG0; /* 009ch : Global Acceptance Filter List Configuration Register 0 */
	T_GAFLCFG1 CFDGAFLCFG1; /* 00A0h : Global Acceptance Filter List Configuration Register 1 */
#endif
	T_CFDRMNB CFDRMNB; /* 00A4h : RX Message Buffer Number Register */
	T_RMND CFDRMND[4]; /* 00A8h : RX Message Buffer New Data Register */
	T_CFDRFCC CFDRFCC[8]; /* 00B8h : RX FIFO Configuration / Control Registers */
	T_RFSTS CFDRFSTS[8]; /* 00D8h : RX FIFO Status Registers */
	T_RFPCTR CFDRFPCTR[8]; /* 00F8h : RX FIFO Pointer Control Registers */
	T_CFDCFCC CFDCFCC[8][3]; /* 0118h : Common FIFO Configuration / Control Registers */
	T_CFSTS CFDCFSTS[8][3]; /* 0178h : Common FIFO Status Registers */
	T_CFPCTR CFDCFPCTR[8][3]; /* 01D8h : Common FIFO Pointer Control Registers */
	T_FESTS CFDFESTS; /* 0238h : FIFO Empty Status Register */
	T_FFSTS CFDFFSTS; /* 023Ch : FIFO Full Status Register */
	T_FMSTS CFDFMSTS; /* 0240h : FIFO Message Lost Status Register */
	T_RFISTS CFDRFISTS; /* 0244h : RX FIFO Interrupt Flag Status Register */
	T_CFRISTS CFDCFRISTS; /* 0248h : Common FIFO RX Interrupt Flag Status Register */
	T_CFTISTS CFDCFTISTS; /* 024Ch : Common FIFO TX Interrupt Flag Status Register */
	T_TMC CFDTMC[8][16]; /* 0250h : TX Message Buffer Control Registers */
	T_TMSTS CFDTMSTS[8][16]; /* 02D0h : TX Message Buffer Status Registers */
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
	/* TBD */
#else
	T_TMTRSTS CFDTMTRSTS[8]; /* 0350h : TX Message Buffer Transmission Request Status Register */
	T_TMTARSTS CFDTMTARSTS[8]; /* 0360h : TX Message Buffer Transmission Abort Request Status Register */
	T_TMTCSTS CFDTMTCSTS[8]; /* 0370h : TX Message Buffer Transmission Completion Status Register */
	T_TMTASTS CFDTMTASTS[8]; /* 0380h : TX Message Buffer Transmission Abort Status Register */
	T_TMIEC CFDTMIEC[8]; /* 0390h : TX Message Buffer Interrupt Enable Configuration */
#endif
	T_TXQCC CFDTXQCC[8]; /* 03A0h : TX Queue Configuration / Control Registers */
	T_TXQSTS CFDTXQSTS[8]; /* 03C0h : TX Queue Status Registers */
	T_TXQPCTR CFDTXQPCTR[8]; /* 03E0h : TX Queue Pointer Control Registers */
	T_THLCC CFDTHLCC[8]; /* 0400h : TX History List Configuration / Control Register */
	T_THLSTS CFDTHLSTS[8]; /* 0420h : TX History List Status Register */
	T_THLPCTR CFDTHLPCTR[8]; /* 0440h : TX History List Pointer Control Registers */
	T_U32 DUMMY1; /* 0460h : (CAN Parity Control Register) */
	T_U32 DUMMY2; /* 0464h : (CAN Parity Error Address Register) */
	T_GTSTCFG CFDGTSTCFG; /* 0468h : Global Test Configuration Register */
	T_GTSTCTR CFDGTSTCTR; /* 046Ch : Global Test Control Register */
	T_U32 DUMMY3[3]; /* 0470h : reserved */
	T_GLOCKK CFDGLOCKK; /* 047Ch : Global Lock Key Register */
	T_GLOTB CFDGLOTB; /* 0480h : Global OTB FIFO Configuration / Status Register */
	T_U32 DUMMY4[3]; /* 0484h : reserved */
	T_CFDCDTCT CFDCDTCT; /* 0490h : DMA Transfer Control Register */
	T_CFDCDTSTS CFDCDTSTS; /* 0494h : DMA Transfer Status Register */
	T_U32 DUMMY5[25]; /* 0498h : reserved */
	T_CFDGRMCFG CFDGRMCFG; /* 04FCh : Global Register Map Configuration Register */
	T_CANFD_CHANNEL_GROUP2 CHANNEL_GROUP2[8]; /* 0500h : CAN FD Channel Register Group 2 */
	T_U32 DUMMY6[640]; /* 0600h : reserved */
	T_GAFL GAFL[16]; /* 1000h : Global Acceptance Filter List Registers */
	T_U32 DUMMY7[960]; /* 1100h : reserved */
	T_CFDRMBCP CFDRMBCP[128]; /* 2000h : RX Message Buffer Component */
	T_CFDRFMBCP CFDRFMBCP[8]; /* 3000h : RX FIFO Message Buffer Component */
	T_CFDCFMBCP CFDCFMBCP[8][3]; /* 3400h : Common FIFO Message Buffer Component */
	T_CFDTMBCP CFDTMBCP[8][16]; /* 4000h : TX Message Buffer Component */
	T_U32 DUMMY8[1024]; /* 5000h: reserved */
	T_THLACC CFDTHLACC[8]; /* 6000h : TX History List Access Registers */
	T_U32 DUMMY9[248]; /* 6020h : reserved */
	T_RPGACC CFDRPGACC[64]; /* 6400h : RAM Test Page Access Registers */
} T_RSCANFD;
/* PACK OFF */
/*lint -restore */
/*lint -restore */

/* ---- register name (RSCAN mode) ---- */
#if 0
#define RSCAN                (*(T_RSCAN RSC_FAR *)CANFD_BASE_ADDR)
#define CnCFG(chn)           (*(T_CnCFG RSC_FAR *)(CANFD_BASE_ADDR + 0x0000 + (chn)*16))
#define CnCTR(chn)           (*(T_CnCTR RSC_FAR *)(CANFD_BASE_ADDR + 0x0004 + (chn)*16))
#define CnSTS(chn)           (*(T_CnSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0008 + (chn)*16))
#define CnERFL(chn)          (*(T_CnERFL RSC_FAR *)(CANFD_BASE_ADDR + 0x000C + (chn)*16))
#define GIPV                 (*(T_GIPV RSC_FAR *)(CANFD_BASE_ADDR + 0x0080))
#define GCFG                 (*(T_GCFG RSC_FAR *)(CANFD_BASE_ADDR + 0x0084))
#define GCTR                 (*(T_GCTR RSC_FAR *)(CANFD_BASE_ADDR + 0x0088))
#define GSTS                 (*(T_GSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x008C))
#define GERFL                (*(T_GERFL RSC_FAR *)(CANFD_BASE_ADDR + 0x0090))
#define GTSC                 (*(T_GTSC RSC_FAR *)(CANFD_BASE_ADDR + 0x0094))
#define GAFLECTR             (*(T_GAFLECTR RSC_FAR *)(CANFD_BASE_ADDR + 0x0098))
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
#define GAFLCFG_RNC(chn)     (*(T_U8 RSC_FAR *)(CANFD_BASE_ADDR + 0x009C + (chn)*1))
#else
#define GAFLCFG0             (*(T_GAFLCFG0 RSC_FAR *)(CANFD_BASE_ADDR + 0x009C))
#define GAFLCFG1             (*(T_GAFLCFG1 RSC_FAR *)(CANFD_BASE_ADDR + 0x00A0))
#endif
#define RMNB                 (*(T_RMNB RSC_FAR *)(CANFD_BASE_ADDR + 0x00A4))
#define RMND(i)              (*(T_RMND RSC_FAR *)(CANFD_BASE_ADDR + 0x00A8 + (i)*4))
#define RFCC(i)              (*(T_RFCC RSC_FAR *)(CANFD_BASE_ADDR + 0x00B8 + (i)*4))
#define RFSTS(i)             (*(T_RFSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x00D8 + (i)*4))
#define RFPCTR(i)            (*(T_RFPCTR RSC_FAR *)(CANFD_BASE_ADDR + 0x00F8 + (i)*4))
#define CFCC(chn, i)         (*(T_CFCC RSC_FAR *)(CANFD_BASE_ADDR + 0x0118 + (chn)*12 + (i)*4))
#define CFSTS(chn, i)        (*(T_CFSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0178 + (chn)*12 + (i)*4))
#define CFPCTR(chn, i)       (*(T_CFPCTR RSC_FAR *)(CANFD_BASE_ADDR + 0x01D8 + (chn)*12 + (i)*4))
#define FESTS                (*(T_FESTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0238))
#define FFSTS                (*(T_FFSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x023C))
#define FMSTS                (*(T_FMSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0240))
#define RFISTS               (*(T_RFISTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0244))
#define CFRISTS              (*(T_CFRISTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0248))
#define CFTISTS              (*(T_CFTISTS RSC_FAR *)(CANFD_BASE_ADDR + 0x024C))
#define TMC(chn, i)          (*(T_TMC RSC_FAR *)(CANFD_BASE_ADDR + 0x0250 + (chn)*16 + (i)*1))
#define TMSTS(chn, i)        (*(T_TMSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x02D0 + (chn)*16 + (i)*1))
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
/* TBD */
#else
#define TMTRSTS(chn)         (*(T_TMTRSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0350 + (chn)*2))
#define TMTARSTS(chn)        (*(T_TMTARSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0360 + (chn)*2))
#define TMTCSTS(chn)         (*(T_TMTCSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0370 + (chn)*2))
#define TMTASTS(chn)         (*(T_TMTASTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0380 + (chn)*2))
#define TMIEC(chn)           (*(T_TMIEC RSC_FAR *)(CANFD_BASE_ADDR + 0x0390 + (chn)*2))
#endif
#define TXQCC(chn)           (*(T_TXQCC RSC_FAR *)(CANFD_BASE_ADDR + 0x03A0 + (chn)*4))
#define TXQSTS(chn)          (*(T_TXQSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x03C0 + (chn)*4))
#define TXQPCTR(chn)         (*(T_TXQPCTR RSC_FAR *)(CANFD_BASE_ADDR + 0x03E0 + (chn)*4))
#define THLCC(chn)           (*(T_THLCC RSC_FAR *)(CANFD_BASE_ADDR + 0x0400 + (chn)*4))
#define THLSTS(chn)          (*(T_THLSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0420 + (chn)*4))
#define THLPCTR(chn)         (*(T_THLPCTR RSC_FAR *)(CANFD_BASE_ADDR + 0x0440 + (chn)*4))
#define GTSTCFG              (*(T_GTSTCFG RSC_FAR *)(CANFD_BASE_ADDR + 0x0468))
#define GTSTCTR              (*(T_GTSTCTR RSC_FAR *)(CANFD_BASE_ADDR + 0x046C))
#define GLOCKK               (*(T_GLOCKK RSC_FAR *)(CANFD_BASE_ADDR + 0x047C))
#define GLOTB                (*(T_GLOTB RSC_FAR *)(CANFD_BASE_ADDR + 0x0480))
#define GCFDT                (*(T_GCFDT RSC_FAR *)(CANFD_BASE_ADDR + 0x04F8))
#define GAFL(i)              (*(T_GAFL RSC_FAR *)(CANFD_BASE_ADDR + 0x0500 + (i)*16))
#define RMBCP(i)             (*(T_RMBCP RSC_FAR *)(CANFD_BASE_ADDR + 0x0600 + (i)*16))
#define RFMBCP(i)            (*(T_RFMBCP RSC_FAR *)(CANFD_BASE_ADDR + 0x0E00 + (i)*16))
#define CFMBCP(chn, i)       (*(T_CFMBCP RSC_FAR *)(CANFD_BASE_ADDR + 0x0E80 + (chn)*48 + (i)*16))
#define TMBCP(chn, i)        (*(T_TMBCP RSC_FAR *)(CANFD_BASE_ADDR + 0x1000 + (chn)*256 + (i)*16))
#define THLACC(chn)          (*(T_THLACC RSC_FAR *)(CANFD_BASE_ADDR + 0x1800 + (chn)*4))
#define RPGACC(i)            (*(T_RPGACC RSC_FAR *)(CANFD_BASE_ADDR + 0x1900 + (i)*4))

/* ---- register name (RSCAN FD mode) ---- */
#define RSCANFD              (*(T_RSCAN RSC_FAR *)CANFD_BASE_ADDR)
#define CFDCnNCFG(chn)       (*(T_CFDCnNCFG RSC_FAR *)(CANFD_BASE_ADDR + 0x0000 + (chn)*0x10))
#define CFDCnCTR(chn)        (*(T_CFDCnCTR RSC_FAR *)(CANFD_BASE_ADDR + 0x0004 + (chn)*0x10))
#define CFDCnSTS(chn)        (*(T_CFDCnSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0008 + (chn)*0x10))
#define CFDCnERFL(chn)       (*(T_CnERFL RSC_FAR *)(CANFD_BASE_ADDR + 0x000C + (chn)*0x10))
#define CFDGIPV              (*(T_GIPV RSC_FAR *)(CANFD_BASE_ADDR + 0x0080))
#define CFDGCFG              (*(T_CFDGCFG RSC_FAR *)(CANFD_BASE_ADDR + 0x0084))
#define CFDGCTR              (*(T_CFDGCTR RSC_FAR *)(CANFD_BASE_ADDR + 0x0088))
#define CFDGSTS              (*(T_GSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x008C))
#define CFDGERFL             (*(T_CFDGERFL RSC_FAR *)(CANFD_BASE_ADDR + 0x0090))
#define CFDGTSC              (*(T_GTSC RSC_FAR *)(CANFD_BASE_ADDR + 0x0094))
#define CFDGAFLECTR          (*(T_GAFLECTR RSC_FAR *)(CANFD_BASE_ADDR + 0x0098))
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
#define CFDGAFLCFG_RNC(chn)  (*(T_U8 RSC_FAR *)(CANFD_BASE_ADDR + 0x009C + (chn)*1))
#else
#define CFDGAFLCFG0          (*(T_GAFLCFG0 RSC_FAR *)(CANFD_BASE_ADDR + 0x009C))
#define CFDGAFLCFG1          (*(T_GAFLCFG1 RSC_FAR *)(CANFD_BASE_ADDR + 0x00A0))
#endif
#define CFDRMNB              (*(T_CFDRMNB RSC_FAR *)(CANFD_BASE_ADDR + 0x00A4))
#define CFDRMND(i)           (*(T_RMND RSC_FAR *)(CANFD_BASE_ADDR + 0x00A8 + (i)*4))
#define CFDRFCC(i)           (*(T_CFDRFCC RSC_FAR *)(CANFD_BASE_ADDR + 0x00B8 + (i)*4))
#define CFDRFSTS(i)          (*(T_RFSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x00D8 + (i)*4))
#define CFDRFPCTR(i)         (*(T_RFPCTR RSC_FAR *)(CANFD_BASE_ADDR + 0x00F8 + (i)*4))
#define CFDCFCC(chn, i)      (*(T_CFDCFCC RSC_FAR *)(CANFD_BASE_ADDR + 0x0118 + (chn)*12 + (i)*4))
#define CFDCFSTS(chn, i)     (*(T_CFSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0178 + (chn)*12 + (i)*4))
#define CFDCFPCTR(chn, i)    (*(T_CFPCTR RSC_FAR *)(CANFD_BASE_ADDR + 0x01D8 + (chn)*12 + (i)*4))
#define CFDFESTS             (*(T_FESTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0238))
#define CFDFFSTS             (*(T_FFSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x023C))
#define CFDFMSTS             (*(T_FMSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0240))
#define CFDRFISTS            (*(T_RFISTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0244))
#define CFDCFRISTS           (*(T_CFRISTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0248))
#define CFDCFTISTS           (*(T_CFTISTS RSC_FAR *)(CANFD_BASE_ADDR + 0x024C))
#define CFDTMC(chn, i)       (*(T_TMC RSC_FAR *)(CANFD_BASE_ADDR + 0x0250 + (chn)*16 + (i)*1))
#define CFDTMSTS(chn, i)     (*(T_TMSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x02D0 + (chn)*16 + (i)*1))
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
/* TBD */
#else
#define CFDTMTRSTS(chn)      (*(T_TMTRSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0350 + (chn)*2))
#define CFDTMTARSTS(chn)     (*(T_TMTARSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0360 + (chn)*2))
#define CFDTMTCSTS(chn)      (*(T_TMTCSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0370 + (chn)*2))
#define CFDTMTASTS(chn)      (*(T_TMTASTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0380 + (chn)*2))
#define CFDTMIEC(chn)        (*(T_TMIEC RSC_FAR *)(CANFD_BASE_ADDR + 0x0390 + (chn)*2))
#endif
#define CFDTXQCC(chn)        (*(T_TXQCC RSC_FAR *)(CANFD_BASE_ADDR + 0x03A0 + (chn)*4))
#define CFDTXQSTS(chn)       (*(T_TXQSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x03C0 + (chn)*4))
#define CFDTXQPCTR(chn)      (*(T_TXQPCTR RSC_FAR *)(CANFD_BASE_ADDR + 0x03E0 + (chn)*4))
#define CFDTHLCC(chn)        (*(T_THLCC RSC_FAR *)(CANFD_BASE_ADDR + 0x0400 + (chn)*4))
#define CFDTHLSTS(chn)       (*(T_THLSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0420 + (chn)*4))
#define CFDTHLPCTR(chn)      (*(T_THLPCTR RSC_FAR *)(CANFD_BASE_ADDR + 0x0440 + (chn)*4))
#define CFDGTSTCFG           (*(T_GTSTCFG RSC_FAR *)(CANFD_BASE_ADDR + 0x0468))
#define CFDGTSTCTR           (*(T_GTSTCTR RSC_FAR *)(CANFD_BASE_ADDR + 0x046C))
#define CFDGLOCKK            (*(T_GLOCKK RSC_FAR *)(CANFD_BASE_ADDR + 0x047C))
#define CFDGLOTB             (*(T_GLOTB RSC_FAR *)(CANFD_BASE_ADDR + 0x0480))
#define CFDCDTCT             (*(T_CFDCDTCT RSC_FAR *)(CANFD_BASE_ADDR + 0x0490))
#define CFDCDTSTS            (*(T_CFDCDTSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x0494))
#define CFDGRMCFG            (*(T_CFDGRMCFG RSC_FAR *)(CANFD_BASE_ADDR + 0x04FC))
#define CFDCnDCFG(chn)       (*(T_CFDCnDCFG RSC_FAR *)(CANFD_BASE_ADDR + 0x0500 + (chn)*32))
#define CFDCnCFG(chn)        (*(T_CFDCnCFG RSC_FAR *)(CANFD_BASE_ADDR + 0x0504 + (chn)*32))
#define CFDCnFDCTR(chn)      (*(T_CFDCnFDCTR RSC_FAR *)(CANFD_BASE_ADDR + 0x0508 + (chn)*32))
#define CFDCnFDSTS(chn)      (*(T_CFDCnFDSTS RSC_FAR *)(CANFD_BASE_ADDR + 0x050C + (chn)*32))
#define CFDCnCRC(chn)        (*(T_CFDCnCRC RSC_FAR *)(CANFD_BASE_ADDR + 0x0510 + (chn)*32))
#define CFDGAFL(i)           (*(T_GAFL RSC_FAR *)(CANFD_BASE_ADDR + 0x1000 + (i)*16))
#define CFDRMBCP(i)          (*(T_CFDRMBCP RSC_FAR *)(CANFD_BASE_ADDR + 0x2000 + (i)*32))
#define CFDRFMBCP(i)         (*(T_CFDRFMBCP RSC_FAR *)(CANFD_BASE_ADDR + 0x3000 + (i)*128))
#define CFDCFMBCP(chn, i)    (*(T_CFDCFMBCP RSC_FAR *)(CANFD_BASE_ADDR + 0x3400 + (chn)*384 + (i)*128))
#define CFDTMBCP(chn, i)     (*(T_CFDTMBCP RSC_FAR *)(CANFD_BASE_ADDR + 0x4000 + (chn)*512 + (i)*32))

/* TMBC in TX merge mode (TMB0, TMB3) */
#define CFDTMBCPMD_TMB0(chn) (*(T_CFDTMBCPMD RSC_FAR *)(CANFD_BASE_ADDR + 0x4000 + (chn)*512 + 0*32))
#define CFDTMBCPMD_TMB3(chn) (*(T_CFDTMBCPMD RSC_FAR *)(CANFD_BASE_ADDR + 0x4000 + (chn)*512 + 3*32))

#define CFDTHLACC(chn)       (*(T_THLACC RSC_FAR *)(CANFD_BASE_ADDR + 0x6000 + (chn)*4))
#define CFDRPGACC(i)         (*(T_RPGACC RSC_FAR *)(CANFD_BASE_ADDR + 0x6400 + (i)*4))
#else
#define RSCAN                (*(T_RSCAN RSC_FAR *)CANFD_BASE_ADDR)
#define CnCFG(unit,chn)      (*(T_CnCFG RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0000 + (chn)*16))
#define CnCTR(unit,chn)      (*(T_CnCTR RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0004 + (chn)*16))
#define CnSTS(unit,chn)      (*(T_CnSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0008 + (chn)*16))
#define CnERFL(unit,chn)     (*(T_CnERFL RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x000C + (chn)*16))
#define GIPV(unit)           (*(T_GIPV RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0080))
#define GCFG(unit)           (*(T_GCFG RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0084))
#define GCTR(unit)           (*(T_GCTR RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0088))
#define GSTS(unit)           (*(T_GSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x008C))
#define GERFL(unit)          (*(T_GERFL RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0090))
#define GTSC(unit)           (*(T_GTSC RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0094))
#define GAFLECTR(unit)       (*(T_GAFLECTR RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0098))
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
#define GAFLCFG_RNC(unit,chn)     (*(T_U8 RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x009C + (chn)*1))
#else
#define GAFLCFG0(unit)       (*(T_GAFLCFG0 RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x009C))
#define GAFLCFG1(unit)       (*(T_GAFLCFG1 RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x00A0))
#endif
#define RMNB(unit)           (*(T_RMNB RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x00A4))
#define RMND(unit,i)         (*(T_RMND RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x00A8 + (i)*4))
#define RFCC(unit,i)         (*(T_RFCC RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x00B8 + (i)*4))
#define RFSTS(unit,i)        (*(T_RFSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x00D8 + (i)*4))
#define RFPCTR(unit,i)       (*(T_RFPCTR RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x00F8 + (i)*4))
#define CFCC(unit,chn, i)    (*(T_CFCC RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0118 + (chn)*12 + (i)*4))
#define CFSTS(unit,chn, i)   (*(T_CFSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0178 + (chn)*12 + (i)*4))
#define CFPCTR(unit,chn, i)  (*(T_CFPCTR RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x01D8 + (chn)*12 + (i)*4))
#define FESTS(unit)          (*(T_FESTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0238))
#define FFSTS(unit)          (*(T_FFSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x023C))
#define FMSTS(unit)          (*(T_FMSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0240))
#define RFISTS(unit)         (*(T_RFISTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0244))
#define CFRISTS(unit)        (*(T_CFRISTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0248))
#define CFTISTS(unit)        (*(T_CFTISTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x024C))
#define TMC(unit,chn, i)     (*(T_TMC RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0250 + (chn)*16 + (i)*1))
#define TMSTS(unit,chn, i)   (*(T_TMSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x02D0 + (chn)*16 + (i)*1))
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
/* TBD */
#else
#define TMTRSTS(unit,chn)    (*(T_TMTRSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0350 + (chn)*2))
#define TMTARSTS(unit,chn)   (*(T_TMTARSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0360 + (chn)*2))
#define TMTCSTS(unit,chn)    (*(T_TMTCSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0370 + (chn)*2))
#define TMTASTS(unit,chn)    (*(T_TMTASTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0380 + (chn)*2))
#define TMIEC(unit,chn)      (*(T_TMIEC RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0390 + (chn)*2))
#endif
#define TXQCC(unit,chn)      (*(T_TXQCC RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x03A0 + (chn)*4))
#define TXQSTS(unit,chn)     (*(T_TXQSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x03C0 + (chn)*4))
#define TXQPCTR(unit,chn)    (*(T_TXQPCTR RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x03E0 + (chn)*4))
#define THLCC(unit,chn)      (*(T_THLCC RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0400 + (chn)*4))
#define THLSTS(unit,chn)     (*(T_THLSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0420 + (chn)*4))
#define THLPCTR(unit,chn)    (*(T_THLPCTR RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0440 + (chn)*4))
#define GTSTCFG(unit)        (*(T_GTSTCFG RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0468))
#define GTSTCTR(unit)        (*(T_GTSTCTR RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x046C))
#define GLOCKK(unit)         (*(T_GLOCKK RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x047C))
#define GLOTB(unit)          (*(T_GLOTB RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0480))
#define GCFDT(unit)          (*(T_GCFDT RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x04F8))
#define GAFL(unit,i)         (*(T_GAFL RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0500 + (i)*16))
#define RMBCP(unit,i)        (*(T_RMBCP RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0600 + (i)*16))
#define RFMBCP(unit,i)       (*(T_RFMBCP RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0E00 + (i)*16))
#define CFMBCP(unit,chn, i)  (*(T_CFMBCP RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0E80 + (chn)*48 + (i)*16))
#define TMBCP(unit,chn, i)   (*(T_TMBCP RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x1000 + (chn)*256 + (i)*16))
#define THLACC(unit,chn)     (*(T_THLACC RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x1800 + (chn)*4))
#define RPGACC(unit,i)       (*(T_RPGACC RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x1900 + (i)*4))

/* ---- register name (RSCAN FD mode) ---- */
#define RSCANFD              (*(T_RSCAN RSC_FAR *)CANFD_BASE_ADDR)
#define CFDCnNCFG(unit,chn)  (*(T_CFDCnNCFG RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0000 + (chn)*0x10))
#define CFDCnCTR(unit,chn)   (*(T_CFDCnCTR RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0004 + (chn)*0x10))
#define CFDCnSTS(unit,chn)   (*(T_CFDCnSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0008 + (chn)*0x10))
#define CFDCnERFL(unit,chn)  (*(T_CnERFL RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x000C + (chn)*0x10))
#define CFDGIPV(unit)        (*(T_GIPV RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0080))
#define CFDGCFG(unit)        (*(T_CFDGCFG RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0084))
#define CFDGCTR(unit)        (*(T_CFDGCTR RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0088))
#define CFDGSTS(unit)        (*(T_GSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x008C))
#define CFDGERFL(unit)       (*(T_CFDGERFL RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0090))
#define CFDGTSC(unit)        (*(T_GTSC RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0094))
#define CFDGAFLECTR(unit)    (*(T_GAFLECTR RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0098))
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
#define CFDGAFLCFG_RNC(unit,chn)  (*(T_U8 RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x009C + (chn)*1))
#else
#define CFDGAFLCFG0(unit)    (*(T_GAFLCFG0 RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x009C))
#define CFDGAFLCFG1(unit)    (*(T_GAFLCFG1 RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x00A0))
#endif
#define CFDRMNB(unit)        (*(T_CFDRMNB RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x00A4))
#define CFDRMND(unit,i)      (*(T_RMND RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x00A8 + (i)*4))
#define CFDRFCC(unit,i)      (*(T_CFDRFCC RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x00B8 + (i)*4))
#define CFDRFSTS(unit,i)     (*(T_RFSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x00D8 + (i)*4))
#define CFDRFPCTR(unit,i)    (*(T_RFPCTR RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x00F8 + (i)*4))
#define CFDCFCC(unit,chn, i)   (*(T_CFDCFCC RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0118 + (chn)*12 + (i)*4))
#define CFDCFSTS(unit,chn, i)  (*(T_CFSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0178 + (chn)*12 + (i)*4))
#define CFDCFPCTR(unit,chn, i) (*(T_CFPCTR RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x01D8 + (chn)*12 + (i)*4))
#define CFDFESTS(unit)       (*(T_FESTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0238))
#define CFDFFSTS(unit)       (*(T_FFSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x023C))
#define CFDFMSTS(unit)       (*(T_FMSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0240))
#define CFDRFISTS(unit)      (*(T_RFISTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0244))
#define CFDCFRISTS(unit)     (*(T_CFRISTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0248))
#define CFDCFTISTS(unit)     (*(T_CFTISTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x024C))
#define CFDTMC(unit,chn, i)    (*(T_TMC RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0250 + (chn)*16 + (i)*1))
#define CFDTMSTS(unit,chn, i)  (*(T_TMSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x02D0 + (chn)*16 + (i)*1))
#if (CPU_ENDIAN_TYPE == CPU_ENDIAN_BIG)
/* TBD */
#else
#define CFDTMTRSTS(unit,chn)   (*(T_TMTRSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0350 + (chn)*2))
#define CFDTMTARSTS(unit,chn)  (*(T_TMTARSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0360 + (chn)*2))
#define CFDTMTCSTS(unit,chn)   (*(T_TMTCSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0370 + (chn)*2))
#define CFDTMTASTS(unit,chn)   (*(T_TMTASTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0380 + (chn)*2))
#define CFDTMIEC(unit,chn)     (*(T_TMIEC RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0390 + (chn)*2))
#endif
#define CFDTXQCC(unit,chn)     (*(T_TXQCC RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x03A0 + (chn)*4))
#define CFDTXQSTS(unit,chn)    (*(T_TXQSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x03C0 + (chn)*4))
#define CFDTXQPCTR(unit,chn)   (*(T_TXQPCTR RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x03E0 + (chn)*4))
#define CFDTHLCC(unit,chn)     (*(T_THLCC RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0400 + (chn)*4))
#define CFDTHLSTS(unit,chn)    (*(T_THLSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0420 + (chn)*4))
#define CFDTHLPCTR(unit,chn)   (*(T_THLPCTR RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0440 + (chn)*4))
#define CFDGTSTCFG(unit)       (*(T_GTSTCFG RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0468))
#define CFDGTSTCTR(unit)       (*(T_GTSTCTR RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x046C))
#define CFDGLOCKK(unit)        (*(T_GLOCKK RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x047C))
#define CFDGLOTB(unit)         (*(T_GLOTB RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0480))
#define CFDCDTCT(unit)         (*(T_CFDCDTCT RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0490))
#define CFDCDTSTS(unit)        (*(T_CFDCDTSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0494))
#define CFDGRMCFG(unit)        (*(T_CFDGRMCFG RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x04FC))
#define CFDCnDCFG(unit,chn)       (*(T_CFDCnDCFG RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0500 + (chn)*32))
#define CFDCnCFG(unit,chn)        (*(T_CFDCnCFG RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0504 + (chn)*32))
#define CFDCnFDCTR(unit,chn)      (*(T_CFDCnFDCTR RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0508 + (chn)*32))
#define CFDCnFDSTS(unit,chn)      (*(T_CFDCnFDSTS RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x050C + (chn)*32))
#define CFDCnCRC(unit,chn)        (*(T_CFDCnCRC RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x0510 + (chn)*32))
#define CFDGAFL(unit,i)           (*(T_GAFL RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x1000 + (i)*16))
#define CFDRMBCP(unit,i)          (*(T_CFDRMBCP RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x2000 + (i)*32))
#define CFDRFMBCP(unit,i)         (*(T_CFDRFMBCP RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x3000 + (i)*128))
#define CFDCFMBCP(unit,chn, i)    (*(T_CFDCFMBCP RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x3400 + (chn)*384 + (i)*128))
#define CFDTMBCP(unit,chn, i)     (*(T_CFDTMBCP RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x4000 + (chn)*512 + (i)*32))

/* TMBC in TX merge mode (TMB0, TMB3) */
#define CFDTMBCPMD_TMB0(unit,chn) (*(T_CFDTMBCPMD RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x4000 + (chn)*512 + 0*32))
#define CFDTMBCPMD_TMB3(unit,chn) (*(T_CFDTMBCPMD RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x4000 + (chn)*512 + 3*32))

#define CFDTHLACC(unit,chn)       (*(T_THLACC RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x6000 + (chn)*4))
#define CFDRPGACC(unit,i)         (*(T_RPGACC RSC_FAR *)(CANFD_BASE_ADDR + (unit)*CANFD1_ADDR_OFFSET + 0x6400 + (i)*4))
#endif

/***********************************************************************************************************************
 Exported global variables
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/

#endif /* RSCANFD_SFR_H */

/* End of file */

#endif

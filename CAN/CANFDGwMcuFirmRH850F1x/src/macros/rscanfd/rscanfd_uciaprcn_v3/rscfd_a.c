//============================================================================
// PROJECT = RSCFD Type RSCFDFD_UCIAPRCN_V3
//============================================================================
//                                 C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2017 by Renesas Electronics Europe GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
// Germany
//============================================================================
//Purpose: RS-CAN Application Functions
//
//Warranty Disclaimer
//
//Because the Product(s) is licensed free of charge, there is no warranty 
//of any kind whatsoever and expressly disclaimed and excluded by NEC, 
//either expressed or implied, including but not limited to those for 
//non-infringement of intellectual property, merchantability and/or 
//fitness for the particular purpose. 
//NEC shall not have any obligation to maintain, service or provide bug 
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
//In no event shall Renesas be liable to the User for any incidental, 
//consequential, indirect, or punitive damage (including but not limited 
//to lost profits) regardless of whether such liability is based on breach 
//of contract, tort, strict liability, breach of warranties, failure of 
//essential purpose or otherwise and even if advised of the possibility of 
//such damages. Renesas shall not be liable for any services or products 
//provided by third party vendors, developers or consultants identified or
//referred to the User by NEC in connection with the Product(s) and/or the 
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

#include <ree_types.h>
#include <stddef.h>
#include <stdio.h>

#define  DRIVER_LOCAL
#define  APPLICATION_INTERFACE

#ifdef VLIB
#include <config_rscfd.h>

#else
#include <map_rscfd.h>
#include <map_asmn.h>
#include <map_asmn_basic.h>
#endif

#include "rscfd_p.h"
#include "rscfd_s.h"

/* ASMN Modules: Main Communication Port */
#if( EE_RSCFD_VERBOSE == 1 )
#if( ASMN_UARTINTERFACE == RLIN3_STANDARD )
#if( defined RLIN3_MACROS )
#include <map_rlin3.h>
#include <rlin3\rlin3_uciaprln\rlin3_p.h>
#include <rlin3\rlin3_uciaprln\rlin3_a.h>
#else
#error "RSCFD_A: RLIN3 Communication Interface Missing"
#endif

#elif( ASMN_UARTINTERFACE == DEBUG_INTERNAL )

#else
#error "RSCFD_A: No Communication Interface Defined"
#endif
#endif

/*
 * Global Settings
 */

#ifndef EE_RSCFD_A_TIMEOUT_LIMIT
#define EE_RSCFD_A_TIMEOUT_LIMIT ( 100000000L )
#endif

#ifdef  EE_RSCFD_VERBOSE
#if( EE_RSCFD_VERBOSE == 1 )
#ifdef VLIB
#ifdef IP_TEST
#include "test_api.h"
#define printf( String ) ( eeIo_Printf( String ) )
#endif
#else
#define printf( String ) \
              ( ASMN_UARTSENDSTRING( ASMN_MENUCOM, String, ASMN_UARTMODECRLF ) )
#endif
#endif

#if( EE_RSCFD_VERBOSE == 2 )
#endif

#if( EE_RSCFD_VERBOSE == 0 )
#define printf( String ) ( RSCFD_A_DoNothing( String ) )
#endif

#else
#define printf( String ) ( RSCFD_A_DoNothing( String ) )
#endif

/*
 * Global Variables
 */

static u16 EE_RSCFD_A_IRQ_REC_0 = 0;
static u16 EE_RSCFD_A_IRQ_REC_1 = 0;
static u16 EE_RSCFD_A_IRQ_TRX_0 = 0;
static u16 EE_RSCFD_A_IRQ_TRX_1 = 0;

#if( EE_RSCFD_VERBOSE == 1 )
static u32 EE_RSCFD_A_TXIDTRACE[ 1 << ( sizeof( u08 ) ) ];
#endif

/*
 * Local Support Functions
 */

void RSCFD_A_DoNothing(char *String) /* Suppress printing action */
{
}

void RSCFD_A_UnitRXFIFOReceiveIRQ(void) /* Receive Interrupt 1st Unit/Channel */
{
//	EE_RSCFD_CH0_RXF();
	return;
}
void RSCFD_A_UnitChannel1ReceiveIRQ(void) /* Receive Interrupt 1st Unit/Channel */
{
	EE_RSCFD_A_IRQ_REC_0++;
	return;
}

void RSCFD_A_UnitChannel2ReceiveIRQ(void) /* Receive Interrupt 1st Unit/Channel */
{
	EE_RSCFD_A_IRQ_REC_1++;
	return;
}

void RSCFD_A_UnitChannel1TransmitIRQ(void) /* Receive Interrupt 1st Unit/Channel */
{
	EE_RSCFD_A_IRQ_TRX_0++;
	EE_RSCFD_CH0_tx();
	return;
}

void RSCFD_A_UnitChannel2TransmitIRQ(void) /* Receive Interrupt 1st Unit/Channel */
{
	EE_RSCFD_A_IRQ_TRX_1++;
	return;
}

void RSCFD_A_GatewayTransmitIRQ(void) /* Transmit Interrupt Gateway */
{
	EE_RSCFD_A_IRQ_TRX_0++;
	return;
}

void RSCFD_A_GatewayReceiveIRQ(void) /* Receive Interrupt Gateway */
{
	EE_RSCFD_A_IRQ_REC_0++;
	return;
}

bit EE_RSCFD_Shutdown(u08 Unit_u08)
{
	bit EE_RSCFD_Status_bit = EE_RSCFD_OK;

	EE_RSCFD_Status_bit &= EE_RSCFD_Stop(Unit_u08,
	EE_RSCFD_GLOBAL,
	EE_RSCFD_OPMODE_RESET);
	return (EE_RSCFD_Status_bit);
}

/* Transfer a CAN-FD Message with Event Recording */

void EE_RSCFD_GatewayPrepare(struct ee_rscfd_message *OutputMessage,
		u08 SendChannel_u08)
{
	static u08 CopyCounter_u08 = 0;

	/* Transmit tracing */

	OutputMessage->hdr.thlen = EE_RSCFD_SET;
	OutputMessage->hdr.id = (OutputMessage->hdr.id & 0x1FFFFFF0)
			+ (u32) SendChannel_u08;
	OutputMessage->fdsts.ptr = (u32) CopyCounter_u08;

#if( RSCFD_VERBOSE == 1 )
	EE_RSCFD_A_TXIDTRACE[ CopyCounter_u08 ] = OutputMessage->hdr.id;
#endif
	CopyCounter_u08++;

	OutputMessage->path = EE_RSCFD_PATH_TXQUEUE;
	OutputMessage->pathdetail = EE_RSCFD_PATHDETAIL_ANY;

	return;
}

/*
 * Application Test Functions
 */

//=============================================================================
// FunctionName: EE_RSCFD_BasicTest
// IN  :         Unit Numbers, Channel Numbers
// OUT :         Success Status
// Description : Performs elementary sending and receiving of one standard 
//               message with default settings between two channels
// 
//=============================================================================
/***********************************************************************************************************************
 * Function Name: can_set_interrupt
 * Description  : This function enables CAN interrupt.
 * Arguments    : none
 * Return Value : none
 ***********************************************************************************************************************/
static void can_set_interrupt(void)
{
	/* MISRA C:2012 Violation - Rule 4.6 */
	/* Justification - register definition is used here, unavoidable */
	/* MISRA C:2012 Violation - Rule 11.4, 11.6 */
	/* Justification - conversion on pointer is used unavoidable here */
	/*** assign interrupt to PE1 ***/
	EIBD22 = 0x00000001; /* CAN global error interrupt */
	EIBD23 = 0x00000001; /* CAN receive FIFO interrupt */
	EIBD24 = 0x00000001; /* CAN0 error interrupt */
	EIBD25 = 0x00000001; /* CAN0 transmit/receive FIFO receive complete interrupt */
	EIBD26 = 0x00000001; /* CAN0 transmit interrupt */
	EIBD113 = 0x00000001; /* CAN1 error interrupt */
	EIBD114 = 0x00000001; /* CAN1 transmit/receive FIFO receive complete interrupt */
	EIBD115 = 0x00000001; /* CAN1 transmit interrupt */
	EIBD217 = 0x00000001; /* CAN2 error interrupt */
	EIBD218 = 0x00000001; /* CAN2 transmit/receive FIFO receive complete interrupt */
	EIBD219 = 0x00000001; /* CAN2 transmit interrupt */
	EIBD220 = 0x00000001; /* CAN3 error interrupt */
	EIBD221 = 0x00000001; /* CAN3 transmit/receive FIFO receive complete interrupt */
	EIBD222 = 0x00000001; /* CAN3 transmit interrupt */
	EIBD272 = 0x00000001; /* CAN4 error interrupt */
	EIBD273 = 0x00000001; /* CAN4 transmit/receive FIFO receive complete interrupt */
	EIBD274 = 0x00000001; /* CAN4 transmit interrupt */
	EIBD287 = 0x00000001; /* CAN5 error interrupt */
	EIBD288 = 0x00000001; /* CAN5 transmit/receive FIFO receive complete interrupt */
	EIBD289 = 0x00000001; /* CAN5 transmit interrupt */
	EIBD319 = 0x00000001; /* CAN global error interrupt */
	EIBD320 = 0x00000001; /* CAN receive FIFO interrupt */
	EIBD321 = 0x00000001; /* CAN6 error interrupt */
	EIBD322 = 0x00000001; /* CAN6 transmit/receive FIFO receive complete interrupt */
	EIBD323 = 0x00000001; /* CAN6 transmit interrupt */

	/*** set interrupt priority ***/
	PFSSIMR0 &= ~(0x07C00000); // Enable interrupt servicing - Interrupt mask bit
	REG_ICRCANGERR0 = 0x43U;
	REG_ICRCANGRECC0 = 0x44U;
	REG_ICRCAN0ERR = 0x43U;
	REG_ICRCAN0REC = 0x00U;
	REG_ICRCAN0TRX = 0x44U;
	REG_ICRCAN1ERR = 0x43U;
	REG_ICRCAN1REC = 0x44U;
	REG_ICRCAN1TRX = 0x44U;
	REG_ICRCAN2ERR = 0x43U;
	REG_ICRCAN2REC = 0x00U;
	REG_ICRCAN2TRX = 0x44U;
	REG_ICRCAN3ERR = 0x43U;
	REG_ICRCAN3REC = 0x00U;
	REG_ICRCAN3TRX = 0x44U;
	REG_ICRCAN4ERR = 0x43U;
	REG_ICRCAN4REC = 0x00U;
	REG_ICRCAN4TRX = 0x44U;
	REG_ICRCAN5ERR = 0x43U;
	REG_ICRCAN5REC = 0x00U;
	REG_ICRCAN5TRX = 0x44U;
	REG_ICRCANGERR1 = 0x43U;
	REG_ICRCANGRECC1 = 0x44U;
	REG_ICRCAN6ERR = 0x43U;
	REG_ICRCAN6REC = 0x00U;
	REG_ICRCAN6TRX = 0x44U;
} /* End of function can_set_interrupt() */


#if 0
bit EE_RSCFD_BasicTest(u08 Unit1_u08, /* runs with default configuration */
u08 Unit2_u08, u08 Channel1_u08, u08 Channel2_u08)
{
	bit EE_RSCFD_Status_bit = EE_RSCFD_OK;
	u08 DataCounter_u08;
	u08 SendStatus_u08;
	u08 ReceiveStatus_u08;
	u32 TimeoutLimit_u32;

	struct ee_rscfd_message SendMessage;
	struct ee_rscfd_message ReceiveMessage;
	struct ee_rscfd_a_afl *FilterEntry = &EE_RSCFD_A_AFL_RXBOX_ANY;

	/* Message Set Up */

	SendMessage.hdr.id = 0x5AA;
	SendMessage.hdr.thlen = EE_RSCFD_CLEAR; /* No entry in THL */
	SendMessage.hdr.rtr = 0; /* Data Frame */
	SendMessage.hdr.ide = 0; /* Standard Frame */
	SendMessage.fdsts.ptr = 0x23; /* HTH value */
	SendMessage.flag.dlc = DEFAULT_PAYLOAD_LENGTH;
	SendMessage.path = EE_RSCFD_PATH_MSGBOX; /* Send via Message Box */
	SendMessage.pathdetail = EE_RSCFD_PATHDETAIL_ANY; /* use any box... */

	for (DataCounter_u08 = 0; DataCounter_u08 < SendMessage.flag.dlc;
			DataCounter_u08++)
	{
		SendMessage.data[DataCounter_u08] = DEFAULT_PAYLOAD_DATA;
	}

	ReceiveMessage.path = EE_RSCFD_PATH_MSGBOX; /* Receive in msg box */
	ReceiveMessage.pathdetail = 0; /* Check in box #0 */
	FilterEntry->ptr0.rmdp = 0; /* Receive in box #0 */
	FilterEntry->ptr0.ptr = 0x23; /* HRH equal to HTH */

	/* Port activation */
	EE_RSCFD_Status_bit = EE_RSCFD_PortEnable(Unit1_u08, Channel1_u08);
	if (EE_RSCFD_Status_bit == EE_RSCFD_ERROR)
		return ( EE_RSCFD_ERROR);
#ifndef RSCFD_USED_RH850_F1KH_D8
	EE_RSCFD_Status_bit = EE_RSCFD_PortEnable( Unit2_u08,
			Channel2_u08 );
	if( EE_RSCFD_Status_bit == EE_RSCFD_ERROR ) return( EE_RSCFD_ERROR );
#endif

	/* Configuration */

	EE_RSCFD_Status_bit &= EE_RSCFD_SetGlobalConfiguration(Unit1_u08,
			&EE_RSCFD_A_GCFG_BASIC);
#ifndef RSCFD_USED_RH850_F1KH_D8
	EE_RSCFD_Status_bit &= EE_RSCFD_SetGlobalConfiguration( Unit2_u08,
			&EE_RSCFD_A_GCFG_BASIC );
#endif

	EE_RSCFD_Status_bit &= EE_RSCFD_Start(Unit1_u08, /* Perform global activation */
	Channel1_u08,
	EE_RSCFD_OPMODE_RESET, /* Channel Reset */
	EE_RSCFD_CLEAR,
	EE_RSCFD_CLEAR);
#ifndef RSCFD_USED_RH850_F1KH_D8
	EE_RSCFD_Status_bit &= EE_RSCFD_Start(Unit2_u08, /* Perform global activation */
	Channel2_u08,
	EE_RSCFD_OPMODE_RESET, /* Channel Reset */
	EE_RSCFD_CLEAR,
	EE_RSCFD_CLEAR);
#endif

	EE_RSCFD_Status_bit &= EE_RSCFD_SetChannelConfiguration(Unit1_u08,
			Channel1_u08, &EE_RSCFD_A_CHCFG_BASIC);
#ifndef RSCFD_USED_RH850_F1KH_D8
	EE_RSCFD_Status_bit &= EE_RSCFD_SetChannelConfiguration(Unit2_u08,
			Channel2_u08, &EE_RSCFD_A_CHCFG_BASIC);
#endif

	EE_RSCFD_Status_bit &= EE_RSCFD_CreateInterrupt(Unit1_u08, Channel1_u08,
	EE_RSCFD_INT_TX,
	EE_RSCFD_INTENABLEDEFAULT, RSCFD_A_UnitChannel1TransmitIRQ);
#ifndef RSCFD_USED_RH850_F1KH_D8
	EE_RSCFD_Status_bit &= EE_RSCFD_SetAFLEntry(Unit2_u08, Channel2_u08, 0,
			FilterEntry);
#endif

	if (EE_RSCFD_Status_bit == EE_RSCFD_ERROR)
		return ( EE_RSCFD_ERROR);

	/* Activate Units and Channels */

	EE_RSCFD_Status_bit &= EE_RSCFD_Start(Unit1_u08, Channel1_u08,
	EE_RSCFD_OPMODE_OPER, /* operation mode */
	EE_RSCFD_SET, /* error clearing */
	EE_RSCFD_SET); /* timestamp reset */
#ifndef RSCFD_USED_RH850_F1KH_D8
	EE_RSCFD_Status_bit &= EE_RSCFD_Start(Unit2_u08, Channel2_u08,
	EE_RSCFD_OPMODE_OPER, /* operation mode */
	EE_RSCFD_SET, /* error clearing */
	EE_RSCFD_SET); /* timestamp reset */
#endif

	EE_RSCFD_A_IRQ_TRX_0 = 0;

	/* Send Message to be received by other unit/channel */

	EE_RSCFD_Status_bit &= EE_RSCFD_SendMessage(Unit1_u08, Channel1_u08,
			&SendStatus_u08, &SendMessage);

	if (EE_RSCFD_Status_bit == EE_RSCFD_ERROR)
		return ( EE_RSCFD_ERROR);

	TimeoutLimit_u32 = EE_RSCFD_A_TIMEOUT_LIMIT;
	while ((--TimeoutLimit_u32 > 0) && (EE_RSCFD_A_IRQ_TRX_0 == 0))
		;
	if (EE_RSCFD_A_IRQ_TRX_0 == 0)
		return ( EE_RSCFD_ERROR);

#ifndef RSCFD_USED_RH850_F1KH_D8
	/* Receive the message */

	TimeoutLimit_u32 = EE_RSCFD_A_TIMEOUT_LIMIT;

	do
	{
		EE_RSCFD_Status_bit &= EE_RSCFD_ReceiveMessage(Unit2_u08,
				&ReceiveStatus_u08, &ReceiveMessage);
		if (EE_RSCFD_Status_bit == EE_RSCFD_ERROR)
			return ( EE_RSCFD_ERROR);

	} while ((ReceiveStatus_u08 == EE_RSCFD_FAULT_NODATA)
			&& (--TimeoutLimit_u32 > 0));

	if (TimeoutLimit_u32 == 0L)
		EE_RSCFD_Status_bit = EE_RSCFD_ERROR;

	/* Verify the message */

	EE_RSCFD_Status_bit &= (ReceiveMessage.hdr.id == SendMessage.hdr.id);
	EE_RSCFD_Status_bit &= (ReceiveMessage.hdr.rtr == SendMessage.hdr.rtr);
	EE_RSCFD_Status_bit &= (ReceiveMessage.hdr.ide == SendMessage.hdr.ide);
	EE_RSCFD_Status_bit &= (ReceiveMessage.fdsts.ptr == SendMessage.fdsts.ptr);
	EE_RSCFD_Status_bit &= (ReceiveMessage.flag.dlc == SendMessage.flag.dlc);

	for (DataCounter_u08 = 0; DataCounter_u08 < SendMessage.flag.dlc;
			DataCounter_u08++)
	{
		EE_RSCFD_Status_bit &= (ReceiveMessage.data[DataCounter_u08]
				== SendMessage.data[DataCounter_u08]);
	}
#endif

	while (1)
		;

	/* Shutdown */
	EE_RSCFD_Status_bit &= EE_RSCFD_Stop(Unit1_u08,
	EE_RSCFD_GLOBAL,
	EE_RSCFD_OPMODE_RESET);
#ifndef RSCFD_USED_RH850_F1KH_D8
	EE_RSCFD_Status_bit &= EE_RSCFD_Stop(Unit2_u08,
	EE_RSCFD_GLOBAL,
	EE_RSCFD_OPMODE_RESET);
#endif

	return (EE_RSCFD_Status_bit);
}
#else // evaluation power consumption
/* DEFAULT_PAYLOAD_LENGTH
 * Possible settings:
 * 0~ 8 --- 0 ~ 8 bytes
 *    9 --- 12 bytes
 *   10 --- 16 bytes
 *   11 --- 20 bytes
 *   12 --- 24 bytes
 *   13 --- 32 bytes
 *   14 --- 48 bytes
 *   15 --- 64 bytes
 */
#define DEFAULT_PAYLOAD_LENGTH_0BYTE	(0x00)
#define DEFAULT_PAYLOAD_LENGTH_1BYTE	(0x01)
#define DEFAULT_PAYLOAD_LENGTH_2BYTES	(0x02)
#define DEFAULT_PAYLOAD_LENGTH_3BYTES	(0x03)
#define DEFAULT_PAYLOAD_LENGTH_4BYTES	(0x04)
#define DEFAULT_PAYLOAD_LENGTH_5BYTES	(0x05)
#define DEFAULT_PAYLOAD_LENGTH_6BYTES	(0x06)
#define DEFAULT_PAYLOAD_LENGTH_7BYTES	(0x07)
#define DEFAULT_PAYLOAD_LENGTH_8BYTES	(0x08)
#define DEFAULT_PAYLOAD_LENGTH_12BYTES	(0x09)
#define DEFAULT_PAYLOAD_LENGTH_16BYTES	(0x0A)
#define DEFAULT_PAYLOAD_LENGTH_20BYTES	(0x0B)
#define DEFAULT_PAYLOAD_LENGTH_24BYTES	(0x0C)
#define DEFAULT_PAYLOAD_LENGTH_32BYTES	(0x0D)
#define DEFAULT_PAYLOAD_LENGTH_48BYTES	(0x0E)
#define DEFAULT_PAYLOAD_LENGTH_64BYTES	(0x0F)
#define DEFAULT_PAYLOAD_LENGTH			DEFAULT_PAYLOAD_LENGTH_8BYTES
#define DEFAULT_PAYLOAD_ID	 			(0x5AA)
#define DEFAULT_PAYLOAD_DATA 			(0x00)
bit EE_RSCFD_BasicTest(u08 Unit1_u08, /* runs with default configuration */
u08 Unit2_u08, u08 Channel1_u08, u08 Channel2_u08)
{
	bit EE_RSCFD_Status_bit = EE_RSCFD_OK;
	u08 DataCounter_u08;
	u08 SendStatus_u08;
	u08 ReceiveStatus_u08;
	u32 TimeoutLimit_u32;
//	u08 FIFONumber_u08;

	struct ee_rscfd_message SendMessage;
	struct ee_rscfd_message ReceiveMessage;
//	struct ee_rscfd_a_afl *FilterEntry = &EE_RSCFD_A_AFL_RXBOX_ANY;
	struct ee_rscfd_a_afl *FilterEntry = &EE_RSCFD_A_AFL_RXFIFO_STDID_SWGW;

	/* Message Set Up */

	SendMessage.hdr.id = DEFAULT_PAYLOAD_ID;
	SendMessage.hdr.thlen = EE_RSCFD_CLEAR; /* No entry in THL */
	SendMessage.hdr.rtr = EE_RSCFD_FRAME_DATA; /* Data Frame */
	SendMessage.hdr.ide = EE_RSCFD_ID_STD; /* Standard Frame */
	SendMessage.fdsts.ptr = 0x23; /* HTH value */
	SendMessage.flag.dlc = DEFAULT_PAYLOAD_LENGTH;
	SendMessage.path = EE_RSCFD_PATH_MSGBOX; /* Send via Message Box */
	SendMessage.pathdetail = EE_RSCFD_PATHDETAIL_ANY; /* use any box... */

	for (DataCounter_u08 = 0; DataCounter_u08 < SendMessage.flag.dlc;
			DataCounter_u08++)
	{
		SendMessage.data[DataCounter_u08] = DEFAULT_PAYLOAD_DATA;
	}

	ReceiveMessage.path = EE_RSCFD_PATH_RXFIFO; /* Receive in msg box */
	ReceiveMessage.pathdetail = 0; /* Check in box #0 */
#if 0
	FilterEntry->ptr0.rmdp = 0; /* Receive in box #0 */
	FilterEntry->ptr0.rmv = 0; /* NO receive buffer used */
	FilterEntry->ptr0.ptr = 0x23; /* HRH equal to HTH */
#endif
	FilterEntry->ptr1.rxfifomask = EE_RSCFD_AFL_RXFIF0_EN0; /* HRH equal to HTH */

	/* Port activation */
	EE_RSCFD_Status_bit = EE_RSCFD_PortEnable(Unit1_u08, Channel1_u08);
	if (EE_RSCFD_Status_bit == EE_RSCFD_ERROR)
		return ( EE_RSCFD_ERROR);

	/* Configuration */

	EE_RSCFD_Status_bit &= EE_RSCFD_SetGlobalConfiguration(Unit1_u08,
			&EE_RSCFD_A_GCFG_BASIC);

	EE_RSCFD_Status_bit &= EE_RSCFD_Start(Unit1_u08, /* Perform global activation */
	Channel1_u08,
	EE_RSCFD_OPMODE_RESET, /* Channel Reset */
	EE_RSCFD_CLEAR,
	EE_RSCFD_CLEAR);

	EE_RSCFD_Status_bit &= EE_RSCFD_EnableRXFIFO(Unit1_u08, 0,
	EE_RSCFD_SET);

	EE_RSCFD_Status_bit &= EE_RSCFD_SetChannelConfiguration(Unit1_u08,
			Channel1_u08, &EE_RSCFD_A_CHCFG_BASIC);

	EE_RSCFD_Status_bit &= EE_RSCFD_CreateInterrupt(Unit1_u08, Channel1_u08,
	EE_RSCFD_INT_TX,
	EE_RSCFD_INTENABLEDEFAULT, RSCFD_A_UnitChannel1TransmitIRQ);
	EE_RSCFD_Status_bit &= EE_RSCFD_CreateInterrupt(Unit1_u08, EE_RSCFD_GLOBAL,
	EE_RSCFD_INT_RXF0,
	EE_RSCFD_INTENABLEDEFAULT, RSCFD_A_UnitRXFIFOReceiveIRQ);


	EE_RSCFD_Status_bit &= EE_RSCFD_SetAFLEntry(Unit1_u08, Channel1_u08, 0,
				FilterEntry);

	if (EE_RSCFD_Status_bit == EE_RSCFD_ERROR)
		return ( EE_RSCFD_ERROR);

	if (EE_RSCFD_Status_bit == EE_RSCFD_ERROR)
		return ( EE_RSCFD_ERROR);

	/* Activate Units and Channels */

	EE_RSCFD_Status_bit &= EE_RSCFD_Start(Unit1_u08, Channel1_u08,
	EE_RSCFD_OPMODE_OPER, /* operation mode */
	EE_RSCFD_SET, /* error clearing */
	EE_RSCFD_SET); /* timestamp reset */

	EE_RSCFD_A_IRQ_TRX_0 = 0;

#if 1 // Send frame for basic board test
	/* Send Message to be received by other unit/channel */
	EE_RSCFD_Status_bit &= EE_RSCFD_SendMessage(Unit1_u08, Channel1_u08,
			&SendStatus_u08, &SendMessage);

	if (EE_RSCFD_Status_bit == EE_RSCFD_ERROR)
		return ( EE_RSCFD_ERROR);

	TimeoutLimit_u32 = EE_RSCFD_A_TIMEOUT_LIMIT;
	while ((--TimeoutLimit_u32 > 0) && (EE_RSCFD_A_IRQ_TRX_0 == 0))
		;
	if (EE_RSCFD_A_IRQ_TRX_0 == 0)
		return ( EE_RSCFD_ERROR);
#endif

	while (1)
		;

	/* Shutdown */
	EE_RSCFD_Status_bit &= EE_RSCFD_Stop(Unit1_u08,
	EE_RSCFD_GLOBAL,
	EE_RSCFD_OPMODE_RESET);

	return (EE_RSCFD_Status_bit);
}

struct ee_rscfd_message SendMessage;

bit EE_RSCFD_SingleCH(u08 Unit1_u08, /* runs with default configuration */
u08 Unit2_u08, u08 Channel1_u08, u08 Channel2_u08)
{
	bit EE_RSCFD_Status_bit = EE_RSCFD_OK;
	u08 DataCounter_u08;
	u08 SendStatus_u08;
	u08 ReceiveStatus_u08;
	u32 TimeoutLimit_u32;
//	u08 FIFONumber_u08;

	struct ee_rscfd_message ReceiveMessage;
//	struct ee_rscfd_a_afl *FilterEntry = &EE_RSCFD_A_AFL_RXBOX_ANY;
	struct ee_rscfd_a_afl *FilterEntry = &EE_RSCFD_A_AFL_RXFIFO_STDID_SWGW;

	/* Message Set Up */

	SendMessage.hdr.id = DEFAULT_PAYLOAD_ID;
	SendMessage.hdr.thlen = EE_RSCFD_CLEAR; /* No entry in THL */
	SendMessage.hdr.rtr = EE_RSCFD_FRAME_DATA; /* Data Frame */
	SendMessage.hdr.ide = EE_RSCFD_ID_STD; /* Standard Frame */
	SendMessage.fdsts.ptr = 0x23; /* HTH value */
	SendMessage.flag.dlc = DEFAULT_PAYLOAD_LENGTH;
	SendMessage.path = EE_RSCFD_PATH_MSGBOX; /* Send via Message Box */
	SendMessage.pathdetail = EE_RSCFD_PATHDETAIL_ANY; /* use any box... */

	for (DataCounter_u08 = 0; DataCounter_u08 < SendMessage.flag.dlc;
			DataCounter_u08++)
	{
		SendMessage.data[DataCounter_u08] = DEFAULT_PAYLOAD_DATA;
	}


	/* Port activation */
	EE_RSCFD_Status_bit = EE_RSCFD_PortEnable(Unit1_u08, Channel1_u08);
	if (EE_RSCFD_Status_bit == EE_RSCFD_ERROR)
		return ( EE_RSCFD_ERROR);

	/* Configuration */

	EE_RSCFD_Status_bit &= EE_RSCFD_SetGlobalConfiguration(Unit1_u08,
			&EE_RSCFD_A_GCFG_BASIC);

	EE_RSCFD_Status_bit &= EE_RSCFD_Start(Unit1_u08, /* Perform global activation */
	Channel1_u08,
	EE_RSCFD_OPMODE_RESET, /* Channel Reset */
	EE_RSCFD_CLEAR,
	EE_RSCFD_CLEAR);

	EE_RSCFD_Status_bit &= EE_RSCFD_SetChannelConfiguration(Unit1_u08,
			Channel1_u08, &EE_RSCFD_A_CHCFG_BASIC);

	EE_RSCFD_Status_bit &= EE_RSCFD_CreateInterrupt(Unit1_u08, Channel1_u08,
	EE_RSCFD_INT_TX,
	EE_RSCFD_INTENABLEDEFAULT, RSCFD_A_UnitChannel1TransmitIRQ);

	if (EE_RSCFD_Status_bit == EE_RSCFD_ERROR)
		return ( EE_RSCFD_ERROR);

	if (EE_RSCFD_Status_bit == EE_RSCFD_ERROR)
		return ( EE_RSCFD_ERROR);

	/* Activate Units and Channels */

	EE_RSCFD_Status_bit &= EE_RSCFD_Start(Unit1_u08, Channel1_u08,
	EE_RSCFD_OPMODE_OPER, /* operation mode */
	EE_RSCFD_SET, /* error clearing */
	EE_RSCFD_SET); /* timestamp reset */

	EE_RSCFD_A_IRQ_TRX_0 = 0;

	/* Send Message to be received by other unit/channel */
	EE_RSCFD_Status_bit &= EE_RSCFD_SendMessage(Unit1_u08, Channel1_u08,
			&SendStatus_u08, &SendMessage);

	if (EE_RSCFD_Status_bit == EE_RSCFD_ERROR)
		return ( EE_RSCFD_ERROR);

	TimeoutLimit_u32 = EE_RSCFD_A_TIMEOUT_LIMIT;
	while ((--TimeoutLimit_u32 > 0) && (EE_RSCFD_A_IRQ_TRX_0 == 0))
		;
	if (EE_RSCFD_A_IRQ_TRX_0 == 0)
		return ( EE_RSCFD_ERROR);

	while (1)
		;

	/* Shutdown */
	EE_RSCFD_Status_bit &= EE_RSCFD_Stop(Unit1_u08,
	EE_RSCFD_GLOBAL,
	EE_RSCFD_OPMODE_RESET);

	return (EE_RSCFD_Status_bit);
}
#endif

//=============================================================================
// FunctionName: EE_RSCFD_BasicSelfTest
// IN  :         Unit Number, Channel Numbers
// OUT :         Success Status
// Description : Performs elementary sending and receiving of one standard 
//               message with default settings between two channels internally
// 
//=============================================================================

bit EE_RSCFD_BasicSelfTest(u08 Unit1_u08, /* runs with default configuration */
u08 Channel1_u08, u08 Channel2_u08)
{
	bit EE_RSCFD_Status_bit = EE_RSCFD_OK;
	u08 DataCounter_u08;
	u08 SendStatus_u08;
	u08 ReceiveStatus_u08;
	u32 TimeoutLimit_u32;

	struct ee_rscfd_message SendMessage;
	struct ee_rscfd_message ReceiveMessage;
	struct ee_rscfd_a_afl *FilterEntry = &EE_RSCFD_A_AFL_RXBOX_ANY;

	/* Message Set Up */

	SendMessage.hdr.id = 0x5AA;
	SendMessage.hdr.thlen = EE_RSCFD_CLEAR; /* No entry in THL */
	SendMessage.hdr.rtr = 0; /* Data Frame */
	SendMessage.hdr.ide = 0; /* Standard Frame */
	SendMessage.fdsts.ptr = 0x23; /* HTH value */
	SendMessage.flag.dlc = 8;
	SendMessage.path = EE_RSCFD_PATH_MSGBOX; /* Send via Message Box */
	SendMessage.pathdetail = EE_RSCFD_PATHDETAIL_ANY; /* use any box... */

	for (DataCounter_u08 = 0; DataCounter_u08 < SendMessage.flag.dlc;
			DataCounter_u08++)
	{
		SendMessage.data[DataCounter_u08] = DataCounter_u08 + 1;
	}

	ReceiveMessage.path = EE_RSCFD_PATH_MSGBOX; /* Receive in msg box */
	ReceiveMessage.pathdetail = 0; /* Check in box #0 */
	FilterEntry->ptr0.rmdp = 0; /* Receive in box #0 */
	FilterEntry->ptr0.ptr = 0x23; /* HRH equal to HTH */

	/* Configuration */

	EE_RSCFD_Status_bit &= EE_RSCFD_SetGlobalConfiguration(Unit1_u08,
			&EE_RSCFD_A_GCFG_BASIC);

	EE_RSCFD_Status_bit &= EE_RSCFD_Start(Unit1_u08, /* Perform global activation */
	Channel1_u08,
	EE_RSCFD_OPMODE_RESET, /* Channel Reset */
	EE_RSCFD_CLEAR,
	EE_RSCFD_CLEAR);

	EE_RSCFD_Status_bit &= EE_RSCFD_Start(Unit1_u08, /* Perform global activation */
	Channel2_u08,
	EE_RSCFD_OPMODE_RESET, /* Channel Reset */
	EE_RSCFD_CLEAR,
	EE_RSCFD_CLEAR);

	EE_RSCFD_Status_bit &= EE_RSCFD_SetChannelConfiguration(Unit1_u08,
			Channel1_u08, &EE_RSCFD_A_CHCFG_BASIC);
	EE_RSCFD_Status_bit &= EE_RSCFD_SetChannelConfiguration(Unit1_u08,
			Channel2_u08, &EE_RSCFD_A_CHCFG_BASIC);

	EE_RSCFD_Status_bit &= EE_RSCFD_CreateInterrupt(Unit1_u08, Channel1_u08,
	EE_RSCFD_INT_TX,
	EE_RSCFD_INTENABLEDEFAULT, RSCFD_A_UnitChannel1TransmitIRQ);

	EE_RSCFD_Status_bit &= EE_RSCFD_SetAFLEntry(Unit1_u08, Channel2_u08, 0,
			FilterEntry);

	if (EE_RSCFD_Status_bit == EE_RSCFD_ERROR)
		return ( EE_RSCFD_ERROR);

	/* Activate internal communication test mode */

	EE_RSCFD_Status_bit &= EE_RSCFD_Stop(Unit1_u08,
	EE_RSCFD_GLOBAL,
	EE_RSCFD_OPMODE_HALT);

	EE_RSCFD_Status_bit &= EE_RSCFD_IntCANBusActivate(Unit1_u08);

	/* Activate Units and Channels */

	EE_RSCFD_Status_bit &= EE_RSCFD_Start(Unit1_u08, Channel1_u08,
	EE_RSCFD_OPMODE_OPER, /* operation mode */
	EE_RSCFD_SET, /* error clearing */
	EE_RSCFD_SET); /* timestamp reset */

	EE_RSCFD_Status_bit &= EE_RSCFD_Start(Unit1_u08, Channel2_u08,
	EE_RSCFD_OPMODE_OPER, /* operation mode */
	EE_RSCFD_SET, /* error clearing */
	EE_RSCFD_SET); /* timestamp reset */

	EE_RSCFD_A_IRQ_TRX_0 = 0;

	/* Send Message to be received by other unit/channel */

	EE_RSCFD_Status_bit &= EE_RSCFD_SendMessage(Unit1_u08, Channel1_u08,
			&SendStatus_u08, &SendMessage);

	if (EE_RSCFD_Status_bit == EE_RSCFD_ERROR)
		return ( EE_RSCFD_ERROR);

	TimeoutLimit_u32 = EE_RSCFD_A_TIMEOUT_LIMIT;
	while ((--TimeoutLimit_u32 > 0) && (EE_RSCFD_A_IRQ_TRX_0 == 0))
		;
	if (EE_RSCFD_A_IRQ_TRX_0 == 0)
		return ( EE_RSCFD_ERROR);

	/* Receive the message */

	TimeoutLimit_u32 = EE_RSCFD_A_TIMEOUT_LIMIT;

	do
	{
		EE_RSCFD_Status_bit &= EE_RSCFD_ReceiveMessage(Unit1_u08,
				&ReceiveStatus_u08, &ReceiveMessage);
		if (EE_RSCFD_Status_bit == EE_RSCFD_ERROR)
			return ( EE_RSCFD_ERROR);

	} while ((ReceiveStatus_u08 == EE_RSCFD_FAULT_NODATA)
			&& (--TimeoutLimit_u32 > 0));

	if (TimeoutLimit_u32 == 0L)
		EE_RSCFD_Status_bit = EE_RSCFD_ERROR;

	/* Verify the message */

	EE_RSCFD_Status_bit &= (ReceiveMessage.hdr.id == SendMessage.hdr.id);
	EE_RSCFD_Status_bit &= (ReceiveMessage.hdr.rtr == SendMessage.hdr.rtr);
	EE_RSCFD_Status_bit &= (ReceiveMessage.hdr.ide == SendMessage.hdr.ide);
	EE_RSCFD_Status_bit &= (ReceiveMessage.fdsts.ptr == SendMessage.fdsts.ptr);
	EE_RSCFD_Status_bit &= (ReceiveMessage.flag.dlc == SendMessage.flag.dlc);

	for (DataCounter_u08 = 0; DataCounter_u08 < SendMessage.flag.dlc;
			DataCounter_u08++)
	{
		EE_RSCFD_Status_bit &= (ReceiveMessage.data[DataCounter_u08]
				== SendMessage.data[DataCounter_u08]);
	}

	/* Shutdown */

	EE_RSCFD_Status_bit &= EE_RSCFD_Stop(Unit1_u08,
	EE_RSCFD_GLOBAL,
	EE_RSCFD_OPMODE_RESET);

	return (EE_RSCFD_Status_bit);
}

//=============================================================================
// FunctionName: EE_RSCFD_BasicIntSelfTest
// IN  :         Unit Number, Channel Number
// OUT :         Success Status
// Description : Performs elementary sending of one standard 
//               message with default settings to the channel itself internally
// 
//=============================================================================

bit EE_RSCFD_BasicIntSelfTest(u08 Unit_u08, /* runs with default configuration */
u08 Channel_u08)
{
	bit EE_RSCFD_Status_bit = EE_RSCFD_OK;
	u08 DataCounter_u08;
	u08 SendStatus_u08;
	u08 ReceiveStatus_u08;
	u32 TimeoutLimit_u32;

	struct ee_rscfd_message SendMessage;
	struct ee_rscfd_message ReceiveMessage;
	struct ee_rscfd_a_afl *FilterEntry = &EE_RSCFD_A_AFL_RXBOX_ANY;

	/* Message Set Up */

	SendMessage.hdr.id = 0x5AA;
	SendMessage.hdr.thlen = EE_RSCFD_CLEAR; /* No entry in THL */
	SendMessage.hdr.rtr = 0; /* Data Frame */
	SendMessage.hdr.ide = 0; /* Standard Frame */
	SendMessage.fdsts.ptr = 0x23; /* HTH value */
	SendMessage.flag.dlc = 8;
	SendMessage.path = EE_RSCFD_PATH_MSGBOX; /* Send via Message Box */
	SendMessage.pathdetail = EE_RSCFD_PATHDETAIL_ANY; /* use any box... */

	ReceiveMessage.path = EE_RSCFD_PATH_MSGBOX; /* RX to a Message Box */
	ReceiveMessage.pathdetail = EE_RSCFD_PATHDETAIL_ANY;

	for (DataCounter_u08 = 0; DataCounter_u08 < SendMessage.flag.dlc;
			DataCounter_u08++)
	{
		SendMessage.data[DataCounter_u08] = DataCounter_u08 + 1;
	}

	/* Configuration */

	EE_RSCFD_Status_bit &= EE_RSCFD_SetGlobalConfiguration(Unit_u08,
			&EE_RSCFD_A_GCFG_BASIC);

	EE_RSCFD_Status_bit &= EE_RSCFD_Start(Unit_u08, /* Perform global activation */
	Channel_u08,
	EE_RSCFD_OPMODE_RESET, /* Channel Reset */
	EE_RSCFD_SET, /* error clearing */
	EE_RSCFD_SET); /* timestamp reset */

	EE_RSCFD_Status_bit &= EE_RSCFD_SetChannelConfiguration(Unit_u08,
			Channel_u08, &EE_RSCFD_A_CHCFG_BASIC);

	EE_RSCFD_Status_bit &= EE_RSCFD_CreateInterrupt(Unit_u08, Channel_u08,
	EE_RSCFD_INT_TX,
	EE_RSCFD_INTENABLEDEFAULT, RSCFD_A_UnitChannel1TransmitIRQ);

	EE_RSCFD_Status_bit &= EE_RSCFD_SetAFLEntry(Unit_u08, Channel_u08, 0,
			FilterEntry);

	if (EE_RSCFD_Status_bit == EE_RSCFD_ERROR)
	{
		EE_RSCFD_Status_bit &= EE_RSCFD_Shutdown(Unit_u08);
		return ( EE_RSCFD_ERROR);
	}

	/* Activate Units and Channels */

	EE_RSCFD_Status_bit &= EE_RSCFD_Start(Unit_u08, Channel_u08,
	EE_RSCFD_OPMODE_STEST, /* self test mode */
	EE_RSCFD_CLEAR,
	EE_RSCFD_CLEAR);

	EE_RSCFD_A_IRQ_TRX_0 = 0;

	/* Send Message to own channel to receive */

	EE_RSCFD_Status_bit &= EE_RSCFD_SendMessage(Unit_u08, Channel_u08,
			&SendStatus_u08, &SendMessage);

	if (EE_RSCFD_Status_bit == EE_RSCFD_ERROR)
	{
		EE_RSCFD_Status_bit &= EE_RSCFD_Shutdown(Unit_u08);
		return ( EE_RSCFD_ERROR);
	}

	TimeoutLimit_u32 = EE_RSCFD_A_TIMEOUT_LIMIT;
	while ((--TimeoutLimit_u32 > 0) && (EE_RSCFD_A_IRQ_TRX_0 == 0))
		;
	if (EE_RSCFD_A_IRQ_TRX_0 == 0)
	{
		EE_RSCFD_Status_bit &= EE_RSCFD_Shutdown(Unit_u08);
		return ( EE_RSCFD_ERROR);
	}
	if (TimeoutLimit_u32 == 0L)
		EE_RSCFD_Status_bit = EE_RSCFD_ERROR;

	/* Receive a message */

	TimeoutLimit_u32 = EE_RSCFD_A_TIMEOUT_LIMIT;

	do
	{
		EE_RSCFD_Status_bit &= EE_RSCFD_ReceiveMessage(Unit_u08,
				&ReceiveStatus_u08, &ReceiveMessage);
		if (EE_RSCFD_Status_bit == EE_RSCFD_ERROR)
		{
			EE_RSCFD_Status_bit &= EE_RSCFD_Shutdown(Unit_u08);
			return ( EE_RSCFD_ERROR);
		}
	} while ((ReceiveStatus_u08 == EE_RSCFD_FAULT_NODATA)
			&& (--TimeoutLimit_u32 > 0));

	if (TimeoutLimit_u32 == 0L)
		EE_RSCFD_Status_bit = EE_RSCFD_ERROR;

	/* Shutdown */

	EE_RSCFD_Status_bit &= EE_RSCFD_Shutdown(Unit_u08);

	return (EE_RSCFD_Status_bit);
}

//=============================================================================
// FunctionName: EE_RSCFD_SW_Gateway
// IN  :         Number of channels to be used (minimum: 2)
//               If more channels are used than available in a unit, another unit
//               is allocated.
// OUT :         Success Status
// Description : Transfers Standard ID Messages from one channel to another, 
//               the lower 4 bits of the received ID are the destination channel
//               Sending an Extended ID 0x00000000 on any channel stops the gateway
//               In verbose mode, timestamps of RX and TX are sent to the UART
// 
//=============================================================================

bit EE_RSCFD_SW_Gateway(u08 Unit_u08, u08 ChannelCount_u08)
{
	bit EE_RSCFD_Status_bit = EE_RSCFD_OK;
	bit ExitFlag_bit = false;
	u08 CurrentChannel_u08;
	u08 FIFONumber_u08;
	u08 SendChannel_u08;
	u08 SendStatus_u08;
	u08 FIFOStatus_u08;
	u16 HistoryStatus_u16;
	u16 HistoryUpdateStatus_u16;
	u16 HistoryTimeStamp_u16;
	u08 ReceiveStatus_u08;
	u32 TimeoutLimit_u32;

	struct ee_rscfd_message GW_Message;
	struct ee_rscfd_message CTRL_Message;

#if( EE_RSCFD_VERBOSE == 1 )
	char VerboseString[ 50 ];
#endif

	/* Filters to be used for the gateway and control */

	struct ee_rscfd_a_afl *FilterEntry_Gateway =
			&EE_RSCFD_A_AFL_RXFIFO_STDID_SWGW;
	struct ee_rscfd_a_afl *FilterEntry_Control =
			&EE_RSCFD_A_AFL_RXBOX_EXTID_SWGWCTRL;

	/* Global initialization */

	EE_RSCFD_Status_bit &= EE_RSCFD_SetGlobalConfiguration(Unit_u08,
			&EE_RSCFD_A_GCFG_SWGW);
	EE_RSCFD_Status_bit &= EE_RSCFD_SetGlobalFIFOConfiguration(Unit_u08,
			&EE_RSCFD_A_GCFG_SWGW);

	EE_RSCFD_Status_bit &= EE_RSCFD_Start(Unit_u08, /* Perform global activation */
	EE_RSCFD_GLOBAL,
	EE_RSCFD_OPMODE_RESET, /* Channel Reset */
	EE_RSCFD_SET, /* error clearing */
	EE_RSCFD_SET); /* timestamp reset */

	/* Initialization of Units */

	if ((ChannelCount_u08 < 2)
			|| (ChannelCount_u08 > ee_rscfd_channels[Unit_u08]))
		return ( EE_RSCFD_ERROR);

	for (CurrentChannel_u08 = 0; CurrentChannel_u08 < ChannelCount_u08;
			CurrentChannel_u08++)
	{
		/* Enable Port I/O */

		EE_RSCFD_Status_bit &= EE_RSCFD_PortEnable(Unit_u08,
				CurrentChannel_u08);

		/* Set configuration (bitrate etc) */

		EE_RSCFD_Status_bit &= EE_RSCFD_SetChannelConfiguration(Unit_u08,
				CurrentChannel_u08, &EE_RSCFD_A_CHCFG_500_KBPS_4000KBPS);

		/* RX (FIFO) and TX (THL) Interrupts to transfer data and monitor transmission */

		EE_RSCFD_Status_bit &= EE_RSCFD_CreateInterrupt(Unit_u08,
				CurrentChannel_u08,
				EE_RSCFD_INT_TXHL,
				EE_RSCFD_INTENABLEDEFAULT, RSCFD_A_GatewayTransmitIRQ);

		EE_RSCFD_Status_bit &= EE_RSCFD_CreateInterrupt(Unit_u08,
		EE_RSCFD_GLOBAL,
		EE_RSCFD_INT_RXF0 + CurrentChannel_u08,
		EE_RSCFD_INTENABLEDEFAULT, RSCFD_A_GatewayReceiveIRQ);

		/* Filter setting: each unit filters local bus messages: */
		/* on the local bus, all messages have the lowest 4 bits of the ID
		 equal to the bus number, which is also equal to the unit number.
		 The target FIFO number is set identical to the channel number. */

		FilterEntry_Gateway->id.id = (u32) CurrentChannel_u08;
		FilterEntry_Gateway->ptr1.rxfifomask = (u32) (1 << CurrentChannel_u08);

		EE_RSCFD_Status_bit &= EE_RSCFD_SetAFLEntry(Unit_u08,
				CurrentChannel_u08, 0, FilterEntry_Gateway);
		EE_RSCFD_Status_bit &= EE_RSCFD_SetAFLEntry(Unit_u08,
				CurrentChannel_u08, 1, FilterEntry_Control);

		if (EE_RSCFD_Status_bit == EE_RSCFD_ERROR)
		{
			ExitFlag_bit = true;
			break;
		}
	}

	/* Activate Units */

	EE_RSCFD_Status_bit &= EE_RSCFD_Start(Unit_u08,
	EE_RSCFD_GLOBAL,
	EE_RSCFD_OPMODE_HALT, /* halt mode */
	EE_RSCFD_CLEAR, /* no error clearing */
	EE_RSCFD_CLEAR); /* no timestamp reset */
	for (FIFONumber_u08 = 0; FIFONumber_u08 < EE_RSCFD_MAXRXFIFOS;
			FIFONumber_u08++)
	{
		EE_RSCFD_Status_bit &= EE_RSCFD_EnableRXFIFO(Unit_u08, FIFONumber_u08,
		EE_RSCFD_SET);
	}

	EE_RSCFD_Status_bit &= EE_RSCFD_Start(Unit_u08,
	EE_RSCFD_GLOBAL,
	EE_RSCFD_OPMODE_OPER, /* operation mode */
	EE_RSCFD_CLEAR, /* no error clearing */
	EE_RSCFD_CLEAR); /* no timestamp reset */

	if (EE_RSCFD_Status_bit == EE_RSCFD_ERROR)
	{
		ExitFlag_bit = true;
	}

	/* Gateway processing loop */

	while ((ExitFlag_bit == false) && (EE_RSCFD_Status_bit == EE_RSCFD_OK))
	{
		/* Check for (global) Receive Interrupt occurred - Do Gateway Function */

		while ((EE_RSCFD_A_IRQ_REC_0 > 0) || (EE_RSCFD_A_IRQ_TRX_0 > 0))
		{
			for (CurrentChannel_u08 = 0; CurrentChannel_u08 < ChannelCount_u08;
					CurrentChannel_u08++)
			{
				EE_RSCFD_Status_bit &= EE_RSCFD_GetFIFOStatus(Unit_u08,
				EE_RSCFD_GLOBAL, CurrentChannel_u08,
				EE_RSCFD_FIFO_STATUS_LOST, &FIFOStatus_u08);

				if (FIFOStatus_u08 == EE_RSCFD_SET) /* FIFO has overflow, reset it */
				{
					EE_RSCFD_Status_bit &= EE_RSCFD_EnableRXFIFO(Unit_u08,
							CurrentChannel_u08,
							EE_RSCFD_CLEAR);
					EE_RSCFD_Status_bit &= EE_RSCFD_EnableRXFIFO(Unit_u08,
							CurrentChannel_u08,
							EE_RSCFD_SET);
					EE_RSCFD_A_IRQ_REC_0 = 0;
					break;
				}

				EE_RSCFD_Status_bit &= EE_RSCFD_GetFIFOStatus(Unit_u08,
				EE_RSCFD_GLOBAL, CurrentChannel_u08,
				EE_RSCFD_FIFO_STATUS_EMPTY, &FIFOStatus_u08);
				if (FIFOStatus_u08 == EE_RSCFD_CLEAR) /* FIFO is not empty */
				{
					TimeoutLimit_u32 = EE_RSCFD_A_TIMEOUT_LIMIT;

					do /* Receive the message from FIFO */
					{
						GW_Message.path = EE_RSCFD_PATH_RXFIFO;
						GW_Message.pathdetail = CurrentChannel_u08;

						EE_RSCFD_Status_bit &= EE_RSCFD_ReceiveMessage(Unit_u08,
								&ReceiveStatus_u08, &GW_Message);

						if ((EE_RSCFD_Status_bit == EE_RSCFD_OK)
								&& (ReceiveStatus_u08 == EE_RSCFD_FAULT_NONE))
						{
							if (EE_RSCFD_A_IRQ_REC_0 > 0)
							{
								EE_RSCFD_A_IRQ_REC_0--;
							}

#if( EE_RSCFD_VERBOSE == 1 )

							sprintf( VerboseString, "    RXC: %2d RXID: %08X @ %04X\n",
									( int )CurrentChannel_u08,
									( int )GW_Message.hdr.id,
									( int )GW_Message.flag.ts );
							printf( VerboseString );

#endif            
							for (SendChannel_u08 = 0;
									SendChannel_u08 < ChannelCount_u08;
									SendChannel_u08++)
							{
								if (SendChannel_u08 != CurrentChannel_u08)
								{
									EE_RSCFD_GatewayPrepare(&GW_Message,
											SendChannel_u08);
									TimeoutLimit_u32 = EE_RSCFD_A_TIMEOUT_LIMIT;

									do /* Push into each channels TX Queues */
									{
										EE_RSCFD_Status_bit &=
												EE_RSCFD_SendMessage(Unit_u08,
														SendChannel_u08,
														&SendStatus_u08,
														&GW_Message);
										if (EE_RSCFD_Status_bit
												== EE_RSCFD_ERROR)
											return ( EE_RSCFD_ERROR);

									} while ((SendStatus_u08
											== EE_RSCFD_FAULT_BUSY)
											&& (--TimeoutLimit_u32 > 0));
								}
							}
						}
					} while ((ReceiveStatus_u08 == EE_RSCFD_FAULT_NONE)
							&& (--TimeoutLimit_u32 > 0));
				}
			}

			/* Check for any Transmit Interrupt occurred - check Event List */

			if (EE_RSCFD_A_IRQ_TRX_0 > 0)
			{
				EE_RSCFD_A_IRQ_TRX_0--;

				for (CurrentChannel_u08 = 0;
						CurrentChannel_u08 < ChannelCount_u08;
						CurrentChannel_u08++)
				{
					do
					{
						/* Get Empty Status */
						EE_RSCFD_Status_bit &= EE_RSCFD_GetStatus(Unit_u08,
								CurrentChannel_u08,
								EE_RSCFD_STATUS_THPM, &HistoryUpdateStatus_u16);
						if (HistoryUpdateStatus_u16 == EE_RSCFD_CLEAR) /* entry available */
						{
							/* Get Index */
							EE_RSCFD_Status_bit &= EE_RSCFD_GetStatus(Unit_u08,
									CurrentChannel_u08,
									EE_RSCFD_STATUS_TGPT, &HistoryStatus_u16);
							/* Get Timestamp */
							EE_RSCFD_Status_bit &= EE_RSCFD_GetStatus(Unit_u08,
									CurrentChannel_u08,
									EE_RSCFD_STATUS_TXTS,
									&HistoryTimeStamp_u16);
							/* Move List */
							EE_RSCFD_Status_bit &= EE_RSCFD_GetStatus(Unit_u08,
									CurrentChannel_u08,
									EE_RSCFD_STATUS_NEWTXHISTORY,
									&HistoryUpdateStatus_u16);
						}

#if( EE_RSCFD_VERBOSE == 1 )

						if( HistoryUpdateStatus_u16 == EE_RSCFD_CLEAR )
						{
							sprintf( VerboseString, "%2X  TXC: %2d TXID: %08X @ %04X\n",
									( int )HistoryStatus_u16,
									( int )CurrentChannel_u08,
									( int )( ( EE_RSCFD_A_TXIDTRACE[ HistoryStatus_u16 ]
													& 0x1FFFFFF0 ) + ( u32 )CurrentChannel_u08 ),
									( int )HistoryTimeStamp_u16 );
							printf( VerboseString );
						}
#endif
					} while (HistoryUpdateStatus_u16 != EE_RSCFD_SET);
				}
			}
		}

		/* Polling for exit condition: Reception of an extended message in Box 0
		 * of any channel of the gateway
		 */

		CTRL_Message.path = EE_RSCFD_PATH_MSGBOX;
		CTRL_Message.pathdetail = 0;

		EE_RSCFD_Status_bit &= EE_RSCFD_ReceiveMessage(Unit_u08,
				&ReceiveStatus_u08, &CTRL_Message);

		if (ReceiveStatus_u08 == EE_RSCFD_FAULT_NONE)
		{
			ExitFlag_bit = true;
			break;
		}
	}

	/* Gateway synchronous shutdown */

	EE_RSCFD_Status_bit &= EE_RSCFD_Stop(Unit_u08,
	EE_RSCFD_GLOBAL,
	EE_RSCFD_OPMODE_HALT);
	EE_RSCFD_Status_bit &= EE_RSCFD_Stop(Unit_u08,
	EE_RSCFD_GLOBAL,
	EE_RSCFD_OPMODE_RESET);

	return (EE_RSCFD_Status_bit);
}

//=============================================================================
// FunctionName: EE_RSCFD_Reset
// IN  :         Unit Number
// OUT :         Success Status
// Description : Executes Reset of RS-CANFD Unit
// 
//=============================================================================

bit EE_RSCFD_Reset(u08 Unit_u08)
{
	bit EE_RSCFD_Status_bit;

	EE_RSCFD_Status_bit = EE_RSCFD_Stop(Unit_u08,
	EE_RSCFD_GLOBAL,
	EE_RSCFD_OPMODE_RESET);
	return (EE_RSCFD_Status_bit);
}

//=============================================================================
// FunctionName: EE_RSCFD_RAMTestApp
// IN  :         Unit Number
// OUT :         Success Status
// Description : Executes RAM Test after stopping RSCFD
// 
//=============================================================================

bit EE_RSCFD_RAMTestApp(u08 Unit_u08)
{
	bit EE_RSCFD_Status_bit = EE_RSCFD_OK;

	EE_RSCFD_Status_bit &= EE_RSCFD_SetGlobalConfiguration(Unit_u08,
			&EE_RSCFD_A_GCFG_BASIC);

	EE_RSCFD_Status_bit &= EE_RSCFD_Start(Unit_u08,
	EE_RSCFD_GLOBAL,
	EE_RSCFD_OPMODE_HALT, /* operation mode */
	EE_RSCFD_CLEAR,
	EE_RSCFD_CLEAR);

	EE_RSCFD_Status_bit &= EE_RSCFD_Stop(Unit_u08,
	EE_RSCFD_GLOBAL,
	EE_RSCFD_OPMODE_HALT);

	EE_RSCFD_Status_bit &= EE_RSCFD_RAMTest(Unit_u08);

	EE_RSCFD_Status_bit &= EE_RSCFD_Stop(Unit_u08,
	EE_RSCFD_GLOBAL,
	EE_RSCFD_OPMODE_RESET);

	return (EE_RSCFD_Status_bit);
}

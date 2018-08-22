//============================================================================
// PROJECT = ASMN Test Monitor
// MODULE  = $Source$
// VERSION = $Revision: 597 $
// DATE    = $Date: 2008-11-19 10:14:49 +0100 (Mi, 19 Nov 2008) $
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2002 by NEC Electronics (EUROPE) GmbH. All rights reserved.
// Kanzlerstrasse 2
// D-40472 Duesseldorf
//============================================================================
// Purpose: INTC Application Access Interface
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
//In no event shall NEC be liable to the User for any incidental, 
//consequential, indirect, or punitive damage (including but not limited 
//to lost profits) regardless of whether such liability is based on breach 
//of contract, tort, strict liability, breach of warranties, failure of 
//essential purpose or otherwise and even if advised of the possibility of 
//such damages. NEC shall not be liable for any services or products 
//provided by third party vendors, developers or consultants identified or
//referred to the User by NEC in connection with the Product(s) and/or the 
//Application.
//
//============================================================================
// Environment: Devices:          All featuring ASMN Monitor (min. 128k ROM)
//              Assembler:        GHS MULTI 2000
//              C-Compiler:       GHS MULTI 2000
//              Linker:           GHS MULTI 2000
//              Debugger:         GHS MULTI 2000
//============================================================================
//
// $Log$
// Revision 1.1  2003/12/11 13:58:45  liederr
// Initial creation.
//
//
//============================================================================

#include <ree_types.h>
#include <stdio.h>
#include <map_asmn_basic.h>
#include <map_device.h>

#ifdef INTC_MACROS

/* ASMN Modules: Main Communication Port */
#if( ASMN_UARTINTERFACE == UARTA_STANDARD )
#include <map_uarta.h>

#elif( ASMN_UARTINTERFACE == UARTC_STANDARD )
#include <map_uartc.h>

#elif( ASMN_UARTINTERFACE == UARTD_STANDARD )
#include <map_uartd.h>

#elif( ASMN_UARTINTERFACE == UARTE_STANDARD )
#include <map_uarte.h>

#elif( ASMN_UARTINTERFACE == UARTF_STANDARD )
#include <map_uartf.h>

#elif( ASMN_UARTINTERFACE == DEBUG_INTERNAL )

#else
#error "ASMN: No Communication Interface Defined"
#endif

/* INTC Driver Interface */
#include <map_intc.h>

/* Basic ASMN Configuration, dependent on device specifics */
#include <map_asmn.h>

#define ASMN_MENULINE_HDR1  "NMI / EXTERNAL INTERRUPT TEST MONITOR\n"
#define ASMN_MENULINE_HDR2  "  (C) RL 5/1999    \n\n"
#define ASMN_MENULINE_MEN0  "0 -> Exit\n"

#if( INTC_TYPE == QL85E70X )
#define ASMN_MENULINE_MEN1  "1 -> Port / Interrupt Enable\n"
#define ASMN_MENULINE_MEN2  "2 -> Port / Interrupt Disable\n"
#define ASMN_MENULINE_MEN3  "3 -> Create Interrupt\n"
#define ASMN_MENULINE_MEN9  "9 -> Enable NMI Monitor Call\n"
#endif

#define ASMN_MENULINE_CMD1  "\nPlease Enter Command: "
#define ASMN_MENULINE_NOCMD "\nILLEGAL COMMAND\n\n"
#define ASMN_MENULINE_OK    "\nOK.\n"
#define ASMN_MENULINE_FAIL  "\nFAILED!!\n"
#define ASMN_MENULINE_IERR  "\nINPUT ERROR\n"

#define ASMN_MENUINPUT_INTLEVEL  "\n Enter Interrupt Level: "
#define ASMN_MENUINPUT_INTNO     "\n Enter Interrupt [0=NMI0,1=NMI1...,10=INTP0,11=INTP1...]: "
#define ASMN_MENUINPUT_EDGE      "\n Enter Interrupt Edge [0=NEG,1=POS,2=OFF,3=BOTH]: "
#define ASMN_MENUINPUT_EDGENMI   "\n Enter Interrupt Edge [0=NEG,1=POS]: "
#define ASMN_MENUINPUT_IRQEVERY  "\n Enter Indicator Count Threshold: "
#define ASMN_MENUINPUT_MONCALL   "\n Enter Jump Target [1=MAIN, 0=SW-Reset]: "

#define ASMN_MENUINPUT_BUFLEN     20
#define ASMN_MENUINPUT_SCANOK     1

#define ASMN_MENUCODE_SCANOK 1
#define ASMN_MENUCODE_NOCMD -1
#define ASMN_MENUCODE_EXIT   0
#define ASMN_MENUCODE_PORTEN 1
#define ASMN_MENUCODE_PORTDI 2
#define ASMN_MENUCODE_CREATE 3
#define ASMN_MENUCODE_MON    9

#define INTC_NMIJUMP_MAIN       1
#define INTC_NMIJUMP_RESET      0

/* UART Replacement Functions for Monitor */

#define ASMN_A_TTYMODE_CR   0 /* application level constants */
#define ASMN_A_TTYMODE_CRLF 1
#define ASMN_A_HEXMODE      1
#define ASMN_A_DECMODE      0
#define ASMN_A_RECBUFLEN    80

/*
 * external calls
 */

extern void main( );
extern void _reset( );

/*
 * external functions
 */

extern bit ASMN_UARTSENDSTRING( u08, char*, u08 );
extern bit ASMN_UARTSENDBYTE( u08, u08 );
extern bit ASMN_UARTRECEIVEBYTE( u08, pu08 );
extern bit ASMN_UARTRECEIVEINT( u08, u16, char*, int*, pu08 );
extern bit ASMN_UARTRECEIVELONG( u08, u16, char*, unsigned long*, pu08 );
extern bit ASMN_UARTRECEIVEFLOAT( u08, u16, char*, float*, pu08 );

/*
 * global variables
 */


static unsigned int INTC_NMI0InterruptCount  = 0;
static unsigned int INTC_NMI1InterruptCount  = 0;
static unsigned int INTC_NMI2InterruptCount  = 0;
static unsigned int INTC_INT0InterruptCount  = 0;
static unsigned int INTC_INT1InterruptCount  = 0;
static unsigned int INTC_INT2InterruptCount  = 0;
static unsigned int INTC_INT3InterruptCount  = 0;
static unsigned int INTC_INT4InterruptCount  = 0;
static unsigned int INTC_INT5InterruptCount  = 0;
static unsigned int INTC_INT6InterruptCount  = 0;
static unsigned int INTC_INT7InterruptCount  = 0;
static unsigned int INTC_INT8InterruptCount  = 0;
static unsigned int INTC_INT9InterruptCount  = 0;
static unsigned int INTC_INT10InterruptCount = 0;
static unsigned int INTC_INT11InterruptCount = 0;
static unsigned int INTC_INT12InterruptCount = 0;
static unsigned int INTC_INT13InterruptCount = 0;


/*
 * interrupt functions
 */

void TestIntNMI0Notifier( )
{
  INTC_NMI0InterruptCount++;
}
void TestIntNMI1Notifier( )
{
  INTC_NMI1InterruptCount++;
}
void TestIntNMI2Notifier( )
{
  INTC_NMI2InterruptCount++;
}
void TestIntINT0Notifier( )
{
  INTC_INT0InterruptCount++;
}
void TestIntINT1Notifier( )
{
  INTC_INT1InterruptCount++;
}
void TestIntINT2Notifier( )
{
  INTC_INT2InterruptCount++;
}
void TestIntINT3Notifier( )
{
  INTC_INT3InterruptCount++;
}
void TestIntINT4Notifier( )
{
  INTC_INT4InterruptCount++;
}
void TestIntINT5Notifier( )
{
  INTC_INT5InterruptCount++;
}
void TestIntINT6Notifier( )
{
  INTC_INT6InterruptCount++;
}
void TestIntINT7Notifier( )
{
  INTC_INT7InterruptCount++;
}
void TestIntINT8Notifier( )
{
  INTC_INT8InterruptCount++;
}
void TestIntINT9Notifier( )
{
  INTC_INT9InterruptCount++;
}
void TestIntINT10Notifier( )
{
  INTC_INT10InterruptCount++;
}
void TestIntINT11Notifier( )
{
  INTC_INT11InterruptCount++;
}
void TestIntINT12Notifier( )
{
  INTC_INT12InterruptCount++;
}
void TestIntINT13Notifier( )
{
  INTC_INT13InterruptCount++;
}

/*
 * functions
 */

static bit                /* local submenu: invisible from outside */
DisplayMainMenu( u08   MenuCom,
                 char *MenuCommand )
{
  bit           UARTStatus;
  u08           UserInput    = 0;
  unsigned int  DigitCounter = 0;
  int           DigitValue;
  char          InputString[ ASMN_MENUCOM_BUFLEN ];

  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_HDR1, 
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_HDR2,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#ifdef ASMN_MENULINE_MEN0
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN0,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN1
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN1,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN2
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN2,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN3
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN3,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN9
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN9,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_CMD1,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );

  while( DigitCounter < ( ASMN_MENUCOM_BUFLEN-1 ) ) {

    do {  /* wait for one char to be received */
      
      UARTStatus = ASMN_UARTRECEIVEBYTE( MenuCom, &UserInput );
      
    } while( UARTStatus != ASMN_UARTTRANSFEROK );
    
    UARTStatus = ASMN_UARTSENDBYTE( MenuCom, UserInput ); /* echo */
    
    if( ( UserInput == ASMN_MENUCOM_EXE1 ) || 
        ( UserInput == ASMN_MENUCOM_EXE2 ) ) { /* the "return" */
      
      InputString[ DigitCounter ] = 0;       /* close string */
      sscanf( InputString, "%u", &DigitValue );
      *MenuCommand = ( unsigned char )DigitValue;
      return( UARTStatus );
    }
    else {  /* store digit */
      
      if( UserInput >= ' ' ) {
        InputString[ DigitCounter++ ] = ( char )UserInput;
      }
      else if( UserInput == 0x08 ) {
        if( DigitCounter > 0 ) DigitCounter--;
      }
    }
  }

  *MenuCommand = -1;
  return( UARTStatus );
}

bit
TestIntPortEnable( u08 MenuCom )
{
  bit            UARTStatus;
  unsigned char  ScanState;
  bit            SuccessFlag    = INTC_OK;
  int            IntNumber      = -1;
  int            IntLevel       = -1;
  int            EdgeDetection  = -1;
  u16            PEdgeDetection;
  u08            PIntLevel;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_INTNO,
				                    &IntNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = INTC_ERROR;

  SuccessFlag = INTC_GetIntSettings( ( u08 )IntNumber,
                                     &PEdgeDetection,
                                     &PIntLevel );
  if( SuccessFlag == INTC_OK ) {

    EdgeDetection = ( int )PEdgeDetection;
    IntLevel      = ( int )PIntLevel;
    
    if( ( IntNumber == INTC_INT0 )  ||
      	( IntNumber == INTC_INT1 )  ||
      	( IntNumber == INTC_INT2 )  ||
      	( IntNumber == INTC_INT3 )  ||
      	( IntNumber == INTC_INT4 )  ||
      	( IntNumber == INTC_INT5 )  ||
      	( IntNumber == INTC_INT6 )  ||
      	( IntNumber == INTC_INT7 )  ||
      	( IntNumber == INTC_INT8 )  ||
      	( IntNumber == INTC_INT9 ) ) {

      UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
					                    ASMN_MENUINPUT_INTLEVEL,
					                    &IntLevel,
					                    &ScanState );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
      if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = INTC_ERROR;      

      UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
					                    ASMN_MENUINPUT_EDGE,
					                    &EdgeDetection,
					                    &ScanState );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
      if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = INTC_ERROR;      
    }
    if( IntNumber == INTC_NMI0 ) {

      UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
					                    ASMN_MENUINPUT_EDGENMI,
					                    &EdgeDetection,
					                    &ScanState );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
      if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = INTC_ERROR;     
    } 

    if( SuccessFlag == INTC_OK ) {
      SuccessFlag = INTC_PortEnable( ( u08 )IntNumber,
                                     ( u16 )EdgeDetection,
                                     ( u08 )IntLevel );
    }
    else {
    
      UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                        ASMN_UARTMODECRLF );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    }
    
    if( SuccessFlag == INTC_OK ) {
      
      UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_OK,
                                        ASMN_UARTMODECRLF );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    }
    else {
      
      UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_FAIL,
                                        ASMN_UARTMODECRLF );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    }
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  return( UARTStatus );
}

bit
TestIntCreateInterrupt( u08 MenuCom )
{
  bit            UARTStatus;
  unsigned char  ScanState;
  bit            SuccessFlag    = INTC_OK;
  u08            DummyByte;
  int            IntNumber      = -1;
  int            EveryCount     = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_INTNO,
				                    &IntNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = INTC_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_IRQEVERY,
				                    &EveryCount,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = INTC_ERROR;

  if( SuccessFlag == INTC_OK ) {
    switch( IntNumber ) {

    case INTC_NMI0:
      SuccessFlag = INTC_CreateInterrupt( ( u08 )IntNumber,
					                     TestIntNMI0Notifier,
					                     INTC_EXE_NORMAL );
      break;

    case INTC_NMI1:
      SuccessFlag = INTC_CreateInterrupt( ( u08 )IntNumber,
					                     TestIntNMI1Notifier,
					                     INTC_EXE_NORMAL );
      break;

    case INTC_NMI2:
      SuccessFlag = INTC_CreateInterrupt( ( u08 )IntNumber,
					                     TestIntNMI2Notifier,
					                     INTC_EXE_NORMAL );
      break;

    case INTC_INT0:
      SuccessFlag = INTC_CreateInterrupt( ( u08 )IntNumber,
					                     TestIntINT0Notifier,
					                     INTC_EXE_NORMAL );
      break;

    case INTC_INT1:
      SuccessFlag = INTC_CreateInterrupt( ( u08 )IntNumber,
					                     TestIntINT1Notifier,
					                     INTC_EXE_NORMAL );
      break;

    case INTC_INT2:
      SuccessFlag = INTC_CreateInterrupt( ( u08 )IntNumber,
					                     TestIntINT2Notifier,
					                     INTC_EXE_NORMAL );
      break;

    case INTC_INT3:
      SuccessFlag = INTC_CreateInterrupt( ( u08 )IntNumber,
					                     TestIntINT3Notifier,
					                     INTC_EXE_NORMAL );
      break;

    case INTC_INT4:
      SuccessFlag = INTC_CreateInterrupt( ( u08 )IntNumber,
					                     TestIntINT4Notifier,
					                     INTC_EXE_NORMAL );
      break;

    case INTC_INT5:
      SuccessFlag = INTC_CreateInterrupt( ( u08 )IntNumber,
					                     TestIntINT5Notifier,
					                     INTC_EXE_NORMAL );
      break;

    case INTC_INT6:
      SuccessFlag = INTC_CreateInterrupt( ( u08 )IntNumber,
					                     TestIntINT6Notifier,
					                     INTC_EXE_NORMAL );
      break;

    case INTC_INT7:
      SuccessFlag = INTC_CreateInterrupt( ( u08 )IntNumber,
					                     TestIntINT7Notifier,
					                     INTC_EXE_NORMAL );
      break;

    case INTC_INT8:
      SuccessFlag = INTC_CreateInterrupt( ( u08 )IntNumber,
					                     TestIntINT8Notifier,
					                     INTC_EXE_NORMAL );
      break;

    case INTC_INT9:
      SuccessFlag = INTC_CreateInterrupt( ( u08 )IntNumber,
					                     TestIntINT9Notifier,
					                     INTC_EXE_NORMAL );
      break;

    case INTC_INT10:
      SuccessFlag = INTC_CreateInterrupt( ( u08 )IntNumber,
					                     TestIntINT10Notifier,
					                     INTC_EXE_NORMAL );
      break;

    case INTC_INT11:
      SuccessFlag = INTC_CreateInterrupt( ( u08 )IntNumber,
					                     TestIntINT11Notifier,
					                     INTC_EXE_NORMAL );
      break;

    case INTC_INT12:
      SuccessFlag = INTC_CreateInterrupt( ( u08 )IntNumber,
					                     TestIntINT12Notifier,
					                     INTC_EXE_NORMAL );
      break;

    case INTC_INT13:
      SuccessFlag = INTC_CreateInterrupt( ( u08 )IntNumber,
					                     TestIntINT13Notifier,
					                     INTC_EXE_NORMAL );
      break;

    default:
      break;
    }
  }

  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == INTC_OK ) {

    ASMN_UARTSENDSTRING( MenuCom, "\n", ASMN_UARTMODECRLF );

    do {

      switch( IntNumber ) {

      case INTC_NMI0:
	      if( INTC_NMI0InterruptCount >= EveryCount ) {
	        INTC_NMI0InterruptCount = 0;
	        ASMN_UARTSENDSTRING( MenuCom, ".", ASMN_UARTMODECR );
	      }
	      break;
      case INTC_NMI1:
	      if( INTC_NMI1InterruptCount >= EveryCount ) {
	        INTC_NMI1InterruptCount = 0;
	        ASMN_UARTSENDSTRING( MenuCom, ".", ASMN_UARTMODECR );
	      }
	      break;
      case INTC_NMI2:
	      if( INTC_NMI2InterruptCount >= EveryCount ) {
	        INTC_NMI2InterruptCount = 0;
	        ASMN_UARTSENDSTRING( MenuCom, ".", ASMN_UARTMODECR );
	      }
	      break;
      case INTC_INT0:
	      if( INTC_INT0InterruptCount >= EveryCount ) {
	        INTC_INT0InterruptCount = 0;
	        ASMN_UARTSENDSTRING( MenuCom, ".", ASMN_UARTMODECR );
	      }
	      break;
      case INTC_INT1:
	      if( INTC_INT1InterruptCount >= EveryCount ) {
	        INTC_INT1InterruptCount = 0;
	        ASMN_UARTSENDSTRING( MenuCom, ".", ASMN_UARTMODECR );
	      }
	      break;
      case INTC_INT2:
	      if( INTC_INT2InterruptCount >= EveryCount ) {
	        INTC_INT2InterruptCount = 0;
	        ASMN_UARTSENDSTRING( MenuCom, ".", ASMN_UARTMODECR );
	      }
	      break;
      case INTC_INT3:
	      if( INTC_INT3InterruptCount >= EveryCount ) {
	        INTC_INT3InterruptCount = 0;
	        ASMN_UARTSENDSTRING( MenuCom, ".", ASMN_UARTMODECR );
	      }
	      break;
      case INTC_INT4:
	      if( INTC_INT4InterruptCount >= EveryCount ) {
	        INTC_INT4InterruptCount = 0;
	        ASMN_UARTSENDSTRING( MenuCom, ".", ASMN_UARTMODECR );
	      }
	      break;
      case INTC_INT5:
	      if( INTC_INT5InterruptCount >= EveryCount ) {
	        INTC_INT5InterruptCount = 0;
	        ASMN_UARTSENDSTRING( MenuCom, ".", ASMN_UARTMODECR );
	      }
	      break;
      case INTC_INT6:
	      if( INTC_INT6InterruptCount >= EveryCount ) {
	        INTC_INT6InterruptCount = 0;
	        ASMN_UARTSENDSTRING( MenuCom, ".", ASMN_UARTMODECR );
	      }
	      break;
      case INTC_INT7:
	      if( INTC_INT7InterruptCount >= EveryCount ) {
	        INTC_INT7InterruptCount = 0;
	        ASMN_UARTSENDSTRING( MenuCom, ".", ASMN_UARTMODECR );
	      }
	      break;
      case INTC_INT8:
	      if( INTC_INT8InterruptCount >= EveryCount ) {
	        INTC_INT8InterruptCount = 0;
	        ASMN_UARTSENDSTRING( MenuCom, ".", ASMN_UARTMODECR );
	      }
	      break;
      case INTC_INT9:
	      if( INTC_INT9InterruptCount >= EveryCount ) {
	        INTC_INT9InterruptCount = 0;
	        ASMN_UARTSENDSTRING( MenuCom, ".", ASMN_UARTMODECR );
	      }
	      break;
      case INTC_INT10:
	      if( INTC_INT10InterruptCount >= EveryCount ) {
	        INTC_INT10InterruptCount = 0;
	        ASMN_UARTSENDSTRING( MenuCom, ".", ASMN_UARTMODECR );
	      }
	      break;
      case INTC_INT11:
	      if( INTC_INT11InterruptCount >= EveryCount ) {
	        INTC_INT11InterruptCount = 0;
	        ASMN_UARTSENDSTRING( MenuCom, ".", ASMN_UARTMODECR );
	      }
	      break;
      case INTC_INT12:
	      if( INTC_INT12InterruptCount >= EveryCount ) {
	        INTC_INT12InterruptCount = 0;
	        ASMN_UARTSENDSTRING( MenuCom, ".", ASMN_UARTMODECR );
	      }
	      break;
      case INTC_INT13:
	      if( INTC_INT13InterruptCount >= EveryCount ) {
	        INTC_INT13InterruptCount = 0;
	        ASMN_UARTSENDSTRING( MenuCom, ".", ASMN_UARTMODECR );
	      }
	      break;
      default:
	      break;
      }
      UARTStatus = ASMN_UARTRECEIVEBYTE( MenuCom, &DummyByte );

    } while( UARTStatus != ASMN_UARTTRANSFEROK );
    
    ASMN_UARTSENDSTRING( MenuCom, "\n", ASMN_UARTMODECRLF );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_FAIL,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  return( UARTStatus );
}

bit
TestIntMonitorEntry( u08 MenuCom )
{
  bit            UARTStatus;
  unsigned char  ScanState;
  bit            SuccessFlag    = INTC_OK;
  int            EntryPoint     = -1;
  int            IntLevel       = -1;
  int            EdgeDetection  = -1;
  u16            PEdgeDetection;
  u08            PIntLevel;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_MONCALL,
				                    &EntryPoint,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = INTC_ERROR;

  if( SuccessFlag == INTC_OK ) {

    SuccessFlag = INTC_GetIntSettings( INTC_NMI0,
				                      &PEdgeDetection,
				                      &PIntLevel );

    EdgeDetection = INTC_RISING_EDGE;

    if( SuccessFlag == INTC_OK ) {

      EdgeDetection = ( int )PEdgeDetection;
      IntLevel      = ( int )PIntLevel;

      SuccessFlag = INTC_PortEnable( INTC_NMI0,
				                    ( u16 )EdgeDetection,
				                    ( u08 )IntLevel );
    }

    if( SuccessFlag == INTC_OK ) {

      switch( EntryPoint ) {

      case INTC_NMIJUMP_MAIN:
	      SuccessFlag = INTC_CreateInterrupt( INTC_NMI0,
                                              main, INTC_EXE_DIRECT );
	      break;

      case INTC_NMIJUMP_RESET:
	      SuccessFlag = INTC_CreateInterrupt( INTC_NMI0,
                                              _reset, INTC_EXE_DIRECT );
	      break;

      default: 
	      SuccessFlag = INTC_ERROR;
	      break;
      }
    }
    if( SuccessFlag == INTC_OK ) {
      
      UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_OK,
                                        ASMN_UARTMODECRLF );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    }
    else {
      
      UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_FAIL,
                                        ASMN_UARTMODECRLF );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    }
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }
  return( UARTStatus );
}

bit
TestIntPortDisable( u08 MenuCom )
{
  bit            UARTStatus;
  unsigned char  ScanState;
  bit            SuccessFlag    = INTC_OK;
  int            IntNumber      = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                    ASMN_MENUINPUT_INTNO,
                                    &IntNumber,
                                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = INTC_ERROR;

  if( SuccessFlag == INTC_OK ) {

    SuccessFlag = INTC_PortDisable( ( u08 )IntNumber );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }
    
  if( SuccessFlag == INTC_OK ) {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_OK,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }
  else {
      
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_FAIL,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  return( UARTStatus );
}

unsigned char ASMN_INTCFunctions( u08 MenuCom )
{
  bit  UARTStatus   = ASMN_UARTTRANSFEROK;
  char MenuCommand  = ASMN_MENUCODE_NOCMD;

  while( ( UARTStatus  == ASMN_UARTTRANSFEROK ) && 
         ( MenuCommand != ASMN_MENUCODE_EXIT ) ) {

    UARTStatus = DisplayMainMenu( MenuCom, &MenuCommand );

    switch( MenuCommand ) {

    case ASMN_MENUCODE_EXIT: 
      break;
      
    case ASMN_MENUCODE_PORTEN:
      UARTStatus = TestIntPortEnable( MenuCom );
      break;

    case ASMN_MENUCODE_PORTDI:
      UARTStatus = TestIntPortDisable( MenuCom );
      break;

    case ASMN_MENUCODE_CREATE:
      UARTStatus = TestIntCreateInterrupt( MenuCom );
      break;

    case ASMN_MENUCODE_MON:
      UARTStatus = TestIntMonitorEntry( MenuCom );
      break;

    default:
      UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_NOCMD,
                                        ASMN_UARTMODECRLF );
      break;
    }
  }
  return( ( unsigned char )UARTStatus );
}

#endif

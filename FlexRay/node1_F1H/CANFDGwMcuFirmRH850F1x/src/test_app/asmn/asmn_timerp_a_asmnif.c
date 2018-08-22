//============================================================================
// PROJECT = ASMN Test Monitor
// MODULE  = $Source$
// VERSION = $Revision: 263 $
// DATE    = $Date: 2004-04-08 09:50:28 +0200 (Do, 08 Apr 2004) $
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2002 by NEC Electronics (EUROPE) GmbH. All rights reserved.
// Kanzlerstrasse 2
// D-40472 Duesseldorf
//============================================================================
// Purpose: Timer P Application Access Interface
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
// Revision 1.1  2004/04/08 07:50:28  liederr
// Initial creation.
//
//
//============================================================================

//#include <nec_types.h>
#include <map_asmn_basic.h>
#include <map_device.h>

#ifdef TMP_MACROS

/* ASMN Modules: Main Communication Port */
#if( ASMN_UARTINTERFACE == UARTA_STANDARD )
#if( defined UARTA_MACROS )
#include <map_uarta.h>
#else
#error "ASMN: UARTA Communication Interface Missing"
#endif

#elif( ASMN_UARTINTERFACE == UARTC_STANDARD )
#if( defined UARTC_MACROS )
#include <map_uartc.h>
#else
#error "ASMN: UARTC Communication Interface Missing"
#endif

#else
#error "ASMN: No Communication Interface Defined"
#endif

/* Timer P Driver Interface */
#include <map_timerp.h>

/* Basic ASMN Configuration, dependent on device specifics */
#include <map_asmn.h>

#define ASMN_MENULINE_HDR1  "TIMER P APPLICATION MENU\n"
#define ASMN_MENULINE_HDR2  "  (C) RL 02/2002    \n\n"
#define ASMN_MENULINE_MEN0  "0 -> Exit\n"

#if( TMP_TYPE == QLNPUTMPV1 )
#define ASMN_MENULINE_MEN1  "1 -> Interval Timer\n"
#endif

#define ASMN_MENULINE_CMD1  "\nPlease Enter Command: "
#define ASMN_MENULINE_NOCMD "\nILLEGAL COMMAND\n\n"
#define ASMN_MENULINE_OK    "\nOK.\n"
#define ASMN_MENULINE_FAIL  "\nFAILED!!\n"
#define ASMN_MENULINE_IERR  "\nINPUT ERROR\n"

#define ASMN_MENUINPUT_TIMERUNIT  "\n Enter Timer Unit: "
#define ASMN_MENUINPUT_CHANNEL    "\n Enter Channel: "
#define ASMN_MENUINPUT_PERIOD     "\n Enter Period [sec]: "
#define ASMN_MENUINPUT_INTLEVEL   "\n Enter Interrupt Level: "
#define ASMN_MENUINPUT_IRQEVERY   "\n Enter Indicator Count Threshold: "

#define ASMN_MENUINPUT_BUFLEN     20
#define ASMN_MENUINPUT_SCANOK     1

#define ASMN_MENUCODE_SCANOK   1
#define ASMN_MENUCODE_NOCMD   -1
#define ASMN_MENUCODE_EXIT     0
#define ASMN_MENUCODE_BACK     0
#define ASMN_MENUCODE_INTERVAL 1

/*
 * global variables
 */

static u16 TMP_InterruptCount_u16 = 0;

/*
 * interrupt functions
 */

void TestTimerP_A_IRQNotifier( )
{
  TMP_InterruptCount_u16++;
}

/*
 * functions
 */

static u08                /* local submenu: invisible from outside */
DisplayMainMenu( u08   MenuCom,
                 char *MenuCommand )
{
  u08           UARTStatus;
  u08           UserInput    = 0;
  unsigned int  DigitCounter = 0;
  int           DigitValue;
  char          InputString[ ASMN_MENUCOM_BUFLEN ];

  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_HDR1, 
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_HDR2,
				ASMN_UARTMODECRLF );
#ifdef ASMN_MENULINE_MEN0
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
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
#ifdef ASMN_MENULINE_MEN4
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN4,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN5
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN5,
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
        InputString[ DigitCounter++ ] = UserInput;
      }
      else if( UserInput == 0x08 ) {
        if( DigitCounter > 0 ) DigitCounter--;
      }
    }
  }

  *MenuCommand = -1;
  return( UARTStatus );
}

//=============================================================================
// FunctionName: ApplTimerPInterval
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Create Interval Interrupts
//=============================================================================
u08 ApplTimerPInterval( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag = TMP_OK;
  u08           DummyByte;
  flt           Interval    = 0.0;
  int           UnitNumber  = -1;
  int           EveryCount  = -1;
  int           IRQLevel    = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_TIMERUNIT,
                				    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  UARTStatus = ASMN_UARTRECEIVEFLOAT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_PERIOD,
                                      &Interval,
                                      &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_INTLEVEL,
                				    &IRQLevel,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_IRQEVERY,
                				    &EveryCount,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  if( SuccessFlag == TMP_OK ) {

    TMP_InterruptCount_u16 = 0;

    SuccessFlag = TMP_SetInterval( ( u08 )UnitNumber,
				  OSCILLATOR_FREQUENCY,
				  Interval,
				  ( u08 )IRQLevel,
				  TestTimerP_A_IRQNotifier );
  }

  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == TMP_OK ) {

    ASMN_UARTSENDSTRING( MenuCom, "\n", ASMN_UARTMODECRLF );

    do {

      if( TMP_InterruptCount_u16 >= EveryCount ) {

	    TMP_InterruptCount_u16 = 0;
	    ASMN_UARTSENDSTRING( MenuCom, ".", ASMN_UARTMODECR );
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

unsigned char ASMN_TimerPApplications( u08 MenuCom )
{
  u08           UARTStatus   = ASMN_UARTTRANSFEROK;
  char          MenuCommand  = ASMN_MENUCODE_NOCMD;

  while( ( UARTStatus  == ASMN_UARTTRANSFEROK ) && 
    	 ( MenuCommand != ASMN_MENUCODE_EXIT ) ) {

    UARTStatus = DisplayMainMenu( MenuCom, &MenuCommand );

    switch( MenuCommand ) {

    case ASMN_MENUCODE_EXIT: 
      break;
      
    case ASMN_MENUCODE_INTERVAL:
      UARTStatus = ApplTimerPInterval( MenuCom );
      break;

    default:
      UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_NOCMD,
				    ASMN_UARTMODECRLF );
      break;
    }
  }
  return( UARTStatus );
}

#endif

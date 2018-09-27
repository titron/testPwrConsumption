//============================================================================
// PROJECT = ASMN Test Monitor
// MODULE  = $RCSfile$
// VERSION = $Revision: 227 $
// DATE    = $Date: 2004-02-19 16:15:48 +0100 (Do, 19 Feb 2004) $
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2004 by NEC Electronics (EUROPE) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
//============================================================================
// Purpose: AFCAN Application Interface
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
// Environment:     Devices:      all featuring ASMN Monitor (min. 128k ROM)
//                  Assembler:    N/A
//                  C-Compiler:   GHS MULTI 2000
//                  Linker:       GHS MULTI 2000
//                  Debugger:     GHS MULTI 2000
//============================================================================
// Version Author Description
// $Log$
// Revision 1.1  2004/02/19 15:15:02  liederr
// Initial creation.
//
//
//============================================================================

#include <stddef.h>
//#include <nec_types.h>
#include <map_asmn_basic.h>
#include <map_device.h>

#ifdef BRG_MACROS

/* ASMN Modules: Main Communication Port */
#if( ASMN_UARTINTERFACE == UARTA_STANDARD )
#include <map_uarta.h>

#elif( ASMN_UARTINTERFACE == UARTC_STANDARD )
#include <map_uartc.h>

#else
#error "ASMN: No Communication Interface Defined"
#endif

/* BRG Driver Interface */
#include <map_brg.h>

/* Basic ASMN Configuration, dependent on device specifics */
#include <map_asmn.h>

#define ASMN_MENULINE_HDR1  "BRG TEST MONITOR\n"
#define ASMN_MENULINE_HDR2  "  (C) RL 02/2004    \n\n"
#define ASMN_MENULINE_MEN0  "0 -> Exit\n"

#if( BRG_TYPE == QLNPUBRG2V1 )
#define ASMN_MENULINE_MEN1  "1 -> Configuration\n"
#define ASMN_MENULINE_MEN2  "2 -> Start\n"
#define ASMN_MENULINE_MEN3  "3 -> Stop\n"
#define ASMN_MENULINE_MEN4  "4 -> Generate Interrupts\n"
#endif

#define ASMN_MENULINE_CMD1  "\nPlease Enter Command: "
#define ASMN_MENULINE_NOCMD "\nILLEGAL COMMAND\n\n"
#define ASMN_MENULINE_OK    "\nOK.\n"
#define ASMN_MENULINE_FAIL  "\nFAILED!!\n"
#define ASMN_MENULINE_IERR  "\nINPUT ERROR\n"

#define ASMN_MENUINPUT_UNIT       "\n Enter Unit: "
#define ASMN_MENUINPUT_OUTDISABLE "\n Enter Output Disable [0=OFF,1=ON]: "
#define ASMN_MENUINPUT_CLOCKSEL   "\n Enter Clock Selection [0=F,1=F/2,2=F/4,3=F/8]: "
#define ASMN_MENUINPUT_MODULUS    "\n Enter Modulus [0...255]: "
#define ASMN_MENUINPUT_INTLEVEL   "\n Enter Interrupt Level: "
#define ASMN_MENUINPUT_IRQEVERY   "\n Enter Indicator Count Threshold: "
#define ASMN_MENUINPUT_IRQSOURCE  "\n Enter Interrupt Source [0=TICK]: "
#define ASMN_MENUINPUT_BUFLEN     20
#define ASMN_MENUINPUT_SCANOK     1

#define ASMN_MENUCODE_SCANOK 1
#define ASMN_MENUCODE_NOCMD -1
#define ASMN_MENUCODE_EXIT  0

#if( BRG_TYPE == QLNPUBRG2V1 )
#define ASMN_MENUCODE_CFG   1
#define ASMN_MENUCODE_START 2
#define ASMN_MENUCODE_STOP  3
#define ASMN_MENUCODE_IRQ   4
#endif

/*
 * global variables
 */

static u16 BRG_InterruptCount_u16 = 0;

/*
 * interrupt functions
 */

void TestBRGIRQNotifier( )
{
  BRG_InterruptCount_u16++;
}

/*
 * functions
 */

//=============================================================================
// FunctionName: DisplayMenu
// IN  : MenuCom:       Communication Port ID
// OUT : MenuCommand:   Selected command number by user
//       Return:        Communication status
// Description : 
// Present submenu on the TTY and wait for user input. Return user's coice.
//=============================================================================
static u08                          /* local submenu: invisible from outside */
DisplayMenu( u08   MenuCom,
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
#ifdef ASMN_MENULINE_MEN4
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN4,
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
// FunctionName: TestBRGConfiguration
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
unsigned char TestBRGConfiguration( unsigned int MenuCom )
{
  unsigned char UARTStatus;
  unsigned char ScanState;
  unsigned char SuccessFlag          = BRG_OK;
           int  UnitNumber_int       = -1; 
           int  OutputDisable_int;
           int  ClockSelect_int;
           int  Modulus_int;
           u08  OutputDisable_u08;
           u08  ClockSelect_u08;
           u08  Modulus_u08;
           u08  Enable_u08;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = BRG_ERROR;

  ScanState = BRG_GetConfiguration( ( u08 )UnitNumber_int, 
                                          &Enable_u08,
                                          &OutputDisable_u08,
                                          &ClockSelect_u08,
                                          &Modulus_u08 );

  if( ScanState  != ASMN_MENUCODE_SCANOK ) 
  {
    SuccessFlag = BRG_ERROR;
  }
  else 
  {  
    OutputDisable_int = ( int )OutputDisable_u08;
    ClockSelect_int   = ( int )ClockSelect_u08;
    Modulus_int       = ( int )Modulus_u08;
  }

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_OUTDISABLE,
                				    &OutputDisable_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = BRG_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CLOCKSEL,
                				    &ClockSelect_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = BRG_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_MODULUS,
                				    &Modulus_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = BRG_ERROR;

  if( SuccessFlag == BRG_OK )
  {
    SuccessFlag = BRG_SetConfiguration( ( u08 )UnitNumber_int,
                                        ( u08 )OutputDisable_int,
                                        ( u08 )ClockSelect_int,
                                        ( u08 )Modulus_int );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == BRG_OK ) {
    
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

//=============================================================================
// FunctionName: TestBRGStart
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
unsigned char TestBRGStart( unsigned int MenuCom )
{
  unsigned char UARTStatus;
  unsigned char ScanState;
  unsigned char SuccessFlag          = BRG_OK;
           int  UnitNumber_int       = -1; 

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = BRG_ERROR;

  if( SuccessFlag == BRG_OK )
  {
    SuccessFlag = BRG_Start( ( u08 )UnitNumber_int );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == BRG_OK ) {
    
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

//=============================================================================
// FunctionName: TestBRGStop
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
unsigned char TestBRGStop( unsigned int MenuCom )
{
  unsigned char UARTStatus;
  unsigned char ScanState;
  unsigned char SuccessFlag          = BRG_OK;
           int  UnitNumber_int       = -1; 

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber_int,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = BRG_ERROR;

  if( SuccessFlag == BRG_OK )
  {
    SuccessFlag = BRG_Stop( ( u08 )UnitNumber_int );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == BRG_OK ) {
    
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

//=============================================================================
// FunctionName: TestBRGInterrupt
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Insert interrupt handler to show a dot on every x-th interrupt occurrance
//=============================================================================
unsigned char TestBRGInterrupt( unsigned int MenuCom )
{
  unsigned char UARTStatus;
  unsigned char ScanState;
  unsigned char SuccessFlag = BRG_OK;
  u08           DummyByte;
  int           UnitNumber  = -1;
  int           EveryCount  = -1;
  int           IRQSource   = -1;
  int           IRQLevel    = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = BRG_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_IRQEVERY,
                				    &EveryCount,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = BRG_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_IRQSOURCE,
                				    &IRQSource,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = BRG_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_INTLEVEL,
                				    &IRQLevel,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = BRG_ERROR;

  if( SuccessFlag == BRG_OK ) {

    BRG_InterruptCount_u16 = 0;

    SuccessFlag = BRG_CreateInterrupt( ( u08 )UnitNumber,
                                       ( u08 )IRQSource,
                                       ( u08 )IRQLevel,
                	 	                      TestBRGIRQNotifier );
  }

  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == BRG_OK ) {

    ASMN_UARTSENDSTRING( MenuCom, "\n", ASMN_UARTMODECRLF );

    do {

      if( BRG_InterruptCount_u16 >= EveryCount ) {

	    BRG_InterruptCount_u16 = 0;
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

//=============================================================================
// FunctionName: ASMN_BRGFunctions
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Decode and execute BRG Primitive Menu Functions.
//=============================================================================
unsigned char ASMN_BRGFunctions( u08 MenuCom )
{
  unsigned char UARTStatus   = ASMN_UARTTRANSFEROK;
  char          MenuCommand  = ASMN_MENUCODE_NOCMD;

  while( ( UARTStatus  == ASMN_UARTTRANSFEROK ) && 
         ( MenuCommand != ASMN_MENUCODE_EXIT ) ) {

    UARTStatus = DisplayMenu( MenuCom, &MenuCommand );

    switch( MenuCommand ) {
      
    case ASMN_MENUCODE_EXIT: 
      break;

#ifdef ASMN_MENUCODE_CFG      
    case ASMN_MENUCODE_CFG:
      UARTStatus = TestBRGConfiguration( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_START
    case ASMN_MENUCODE_START:
      UARTStatus = TestBRGStart( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_STOP
    case ASMN_MENUCODE_STOP:
      UARTStatus = TestBRGStop( MenuCom );
      break;
#endif
#ifdef ASMN_MENUCODE_IRQ
    case ASMN_MENUCODE_IRQ:
      UARTStatus = TestBRGInterrupt( MenuCom );
      break;
#endif
    default:
      UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_NOCMD,
                                        ASMN_UARTMODECRLF );
      break;
    }
  }
  return( UARTStatus );
}

#endif

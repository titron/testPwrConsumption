//============================================================================
// PROJECT = ASMN Test Monitor
// MODULE  = $Source$
// VERSION = $Revision: 284 $
// DATE    = $Date: 2004-08-09 09:54:17 +0200 (Mo, 09 Aug 2004) $
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2002 by NEC Electronics (EUROPE) GmbH. All rights reserved.
// Kanzlerstrasse 2
// D-40472 Duesseldorf
//============================================================================
// Purpose: Timer Y Primitive Access Interface
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
// Revision 1.1  2004/08/09 07:54:10  liederr
// Initial creation.
//
//
//============================================================================

//#include <nec_types.h>
#include <map_asmn_basic.h>
#include <map_device.h>

#ifdef TMY_MACROS

/* ASMN Modules: Main Communication Port */
#if( ASMN_UARTINTERFACE == UARTA_STANDARD )
#include <map_uarta.h>

#elif( ASMN_UARTINTERFACE == UARTC_STANDARD )
#include <map_uartc.h>

#else
#error "ASMN: No Communication Interface Defined"
#endif

/* Timer Y Driver Interface */
#include <map_timery.h>

/* Port I/O for Interrupt Port Toggles */
#include <map_ports.h>

/* Basic ASMN Configuration, dependent on device specifics */
#include <map_asmn.h>

#define ASMN_MENULINE_HDR1  "TIMER Y TEST MONITOR\n"
#define ASMN_MENULINE_HDR2  "  (C) RL 07/2004    \n\n"
#define ASMN_MENULINE_MEN0  "0 -> Exit\n"

#if( TMY_TYPE == QLNPUTMYV1 )
#define ASMN_MENULINE_MEN1  "1 -> Port Enable\n"
#define ASMN_MENULINE_MEN2  "2 -> Port Disable\n"
#define ASMN_MENULINE_MEN3  "3 -> Reset Timer Y\n"
#define ASMN_MENULINE_MEN4  "4 -> Configure Timer Y\n"
#define ASMN_MENULINE_MEN5  "5 -> Start/Stop Timer Y\n"
#define ASMN_MENULINE_MEN6  "6 -> Read Timer Y Timebase\n"
#define ASMN_MENULINE_MEN7  "7 -> Generate Interrupts\n"
#endif

#define ASMN_MENULINE_CMD1  "\nPlease Enter Command: "
#define ASMN_MENULINE_NOCMD "\nILLEGAL COMMAND\n\n"
#define ASMN_MENULINE_OK    "\nOK.\n"
#define ASMN_MENULINE_FAIL  "\nFAILED!!\n"
#define ASMN_MENULINE_IERR  "\nINPUT ERROR\n"

#define ASMN_MENUINPUT_TIMERUNIT  "\n Enter Timer Unit: "
#define ASMN_MENUINPUT_CHANNEL    "\n Enter Timer Channel: [1/2,3=ALL,FF=KEEP] "
#define ASMN_MENUINPUT_MODULUS0   "\n Enter Modulus[1]: "
#define ASMN_MENUINPUT_MODULUS1   "\n Enter Modulus[2]: "
#define ASMN_MENUINPUT_CLOCK0     "\n Enter Clock Input[1] [0..5]: "
#define ASMN_MENUINPUT_CLOCK1     "\n Enter Clock Input[2] [0..5]: "
#define ASMN_MENUINPUT_OUTLEVEL   "\n Enter Output Level [0=NORMAL,1=INVERTED]: "
#define ASMN_MENUINPUT_ENABLE     "\n Enter Count Enable [0=OFF,1=ON]: "
#define ASMN_MENUINPUT_INTLEVEL   "\n Enter Interrupt Level: "
#define ASMN_MENUINPUT_IRQEVERY   "\n Enter Indicator Count Threshold: "
#define ASMN_MENUINPUT_IRQSOURCE  "\n Enter Interrupt Source [0=ZERO0,1=ZERO1]: "
#define ASMN_MENUINPUT_IRQPORT    "\n Enter Port Toggle Only [0=NO,1=YES]: "
#define ASMN_MENUINPUT_BUFLEN     20
#define ASMN_MENUINPUT_SCANOK     1

#define ASMN_MENUCODE_SCANOK 1
#define ASMN_MENUCODE_NOCMD -1
#define ASMN_MENUCODE_EXIT  0

#if( TMY_TYPE == QLNPUTMYV1 )
#define ASMN_MENUCODE_PORTE 1
#define ASMN_MENUCODE_PORTD 2
#define ASMN_MENUCODE_RESET 3
#define ASMN_MENUCODE_CNF   4
#define ASMN_MENUCODE_SSTOP 5
#define ASMN_MENUCODE_RDTB  6
#define ASMN_MENUCODE_IRQ   7
#endif

/*
 * global variables
 */

static u16 TMY_InterruptCount_u16 = 0;

/*
 * interrupt functions
 */

void TestTimerYIRQNotifier( )
{
  TMY_InterruptCount_u16++;
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
static u08                /* local submenu: invisible from outside */
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
#ifdef ASMN_MENULINE_MEN5
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN5,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN6
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN6,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN7
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN7,
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
// FunctionName: TestTimerYPortEnable
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestTimerYPortEnable( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  u08           SuccessFlag = TMY_OK;
  int           UnitNumber  = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_TIMERUNIT,
				    &UnitNumber,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMY_ERROR;

  if( SuccessFlag == TMY_OK )
  {
    SuccessFlag = TMY_PortEnable( ( u08 )UnitNumber );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == TMY_OK ) {
    
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
// FunctionName: TestTimerYPortDisable
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestTimerYPortDisable( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag = TMY_OK;
  int           UnitNumber  = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_TIMERUNIT,
				    &UnitNumber,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMY_ERROR;

  if( SuccessFlag == TMY_OK )
  {
    SuccessFlag = TMY_PortDisable( ( u08 )UnitNumber );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == TMY_OK ) {
    
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
// FunctionName: TestTimerYConfig
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestTimerYConfig( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag = TMY_OK;
  int           UnitNumber    = -1;
  int           ChannelNumber = -1;
  int           Modulus0;
  int           Modulus1;
  int           OutputLevel;
  int           ClockSelection0;
  int           ClockSelection1;
  u16           PModulus0_u16;
  u16           PModulus1_u16;
  u08           POutputLevel_u08;
  u08           PClockSelection0_u08;
  u08           PClockSelection1_u08;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_TIMERUNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMY_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CHANNEL,
				                    &ChannelNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMY_ERROR;

  ScanState = TMY_GetConfiguration( ( u08 )UnitNumber,
                                    &PModulus0_u16,
                                    &PModulus1_u16,
                                    &POutputLevel_u08,
                                    &PClockSelection0_u08,
                                    &PClockSelection1_u08);

  if( ScanState  != ASMN_MENUCODE_SCANOK ) 
  {
    SuccessFlag = TMY_ERROR;
  }
  else 
  {
    Modulus0        = ( int )PModulus0_u16;
    Modulus1        = ( int )PModulus1_u16;
    ClockSelection0 = ( int )PClockSelection0_u08;
    ClockSelection1 = ( int )PClockSelection1_u08;
    OutputLevel     = ( int )POutputLevel_u08;
  }

  if( ChannelNumber & TMY_CHANNEL_0 )
    {
      UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                        ASMN_MENUINPUT_MODULUS0,
                                        &Modulus0,
                                        &ScanState );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
      if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMY_ERROR;

      UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                        ASMN_MENUINPUT_CLOCK0,
                                        &ClockSelection0,
                                        &ScanState );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
      if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMY_ERROR;
    }

  if( ChannelNumber & TMY_CHANNEL_1 )
    {
      UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                        ASMN_MENUINPUT_MODULUS1,
                                        &Modulus1,
                                        &ScanState );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
      if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMY_ERROR;

      UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                        ASMN_MENUINPUT_CLOCK1,
                                        &ClockSelection1,
                                        &ScanState );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
      if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMY_ERROR;
    }

  if( ( u08 )ClockSelection0 == PClockSelection0_u08 )
    ClockSelection0 = TMY_CLOCK_KEEP;
  if( ( u08 )ClockSelection1 == PClockSelection1_u08 )
    ClockSelection1 = TMY_CLOCK_KEEP;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                    ASMN_MENUINPUT_OUTLEVEL,
                                    &OutputLevel,
                                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMY_ERROR;

  if( SuccessFlag == TMY_OK )
  {
    SuccessFlag = TMY_SetConfiguration( ( u08 )UnitNumber,
                                        ( u08 )ChannelNumber,
                                        ( u16 )Modulus0,
                                        ( u16 )Modulus1,
                                        ( u08 )OutputLevel,
                                        ( u08 )ClockSelection0,
                                        ( u08 )ClockSelection1 );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == TMY_OK ) {
    
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
// FunctionName: TestTimerYReset
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestTimerYReset( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag = TMY_OK;
  int           UnitNumber  = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_TIMERUNIT,
                				    &UnitNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMY_ERROR;

  if( SuccessFlag == TMY_OK )
    SuccessFlag = TMY_Reset( ( u08 )UnitNumber );
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == TMY_OK ) {
    
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
// FunctionName: TestTimerYStartStop
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestTimerYStartStop( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag = TMY_OK;
  int           UnitNumber  = -1;
  int           Enable      = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_TIMERUNIT,
                				    &UnitNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMY_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_ENABLE,
				                    &Enable,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMY_ERROR;

  if( SuccessFlag == TMY_OK )
    SuccessFlag = TMY_StartStop( ( u08 )UnitNumber,
                                 ( u08 )Enable );
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == TMY_OK ) {
    
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
// FunctionName: TestTimerYReadTB
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestTimerYReadTB( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag   = TMY_OK;
  int           UnitNumber    = -1;
  u16           ReadValue0;
  u16           ReadValue1;
  char          ReadString[ 30 ];

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_TIMERUNIT,
                				    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMY_ERROR;

  if( SuccessFlag == TMY_OK )
    SuccessFlag = TMY_Read( ( u08 )UnitNumber, 
                            TMY_CHANNEL_ALL,
                            ( pu16 )( &ReadValue0 ),
                            ( pu16 )( &ReadValue1 ) );
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				                  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == TMY_OK ) {
    
    sprintf( ReadString, "\n[1]:%04XH [2]:%04XH\n", ReadValue0, ReadValue1 );
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ReadString,
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
// FunctionName: TestTimerYInterrupt
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Insert interrupt handler to show a dot on every x-th interrupt occurrance
//=============================================================================
u08 TestTimerYInterrupt( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag = TMY_OK;
  u08           DummyByte;
  int           UnitNumber  = -1;
  int           EveryCount  = -1;
  int           IRQSource   = -1;
  int           IRQLevel    = -1;
  int           IRQPortOnly = 0;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_TIMERUNIT,
                				    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMY_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_IRQEVERY,
                				    &EveryCount,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMY_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_IRQSOURCE,
                				    &IRQSource,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMY_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_INTLEVEL,
                				    &IRQLevel,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMY_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_IRQPORT,
                				    &IRQPortOnly,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMY_ERROR;

  if( SuccessFlag == TMY_OK ) {

    TMY_InterruptCount_u16 = 0;

    SuccessFlag = TMY_CreateInterrupt( ( u08 )UnitNumber,
                                       ( u08 )IRQSource,
                                       ( u08 )IRQLevel,
                                       TestTimerYIRQNotifier );
  }

  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == TMY_OK ) {

    ASMN_UARTSENDSTRING( MenuCom, "\n", ASMN_UARTMODECRLF );

#ifdef ASMN_INTTOGGLE_PORT
    PORT_Enable( ASMN_INTTOGGLE_PORT,
                 ASMN_INTTOGGLE_PORTBIT,
                 PORT_DIR_OUTPUT,
                 PORT_MODE_IO,
                 PORT_FUNCTION_NORMAL );
#endif

    do {

      if( TMY_InterruptCount_u16 >= EveryCount ) {

	    TMY_InterruptCount_u16 = 0;
        if( !IRQPortOnly )
          ASMN_UARTSENDSTRING( MenuCom, ".", ASMN_UARTMODECR );

#ifdef ASMN_INTTOGGLE_PORT
        PORT_Write( ASMN_INTTOGGLE_PORT,
                    ASMN_INTTOGGLE_PORTBIT );
        PORT_Write( ASMN_INTTOGGLE_PORT, 0 );
#endif
      }

      UARTStatus = ASMN_UARTRECEIVEBYTE( MenuCom, &DummyByte );

    } while( UARTStatus != ASMN_UARTTRANSFEROK );
    
    ASMN_UARTSENDSTRING( MenuCom, "\n", ASMN_UARTMODECRLF );

#ifdef ASMN_INTTOGGLE_PORT
    PORT_Disable( ASMN_INTTOGGLE_PORT,
                  ASMN_INTTOGGLE_PORTBIT );
#endif

  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_FAIL,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  return( UARTStatus );
}

//=============================================================================
// FunctionName: ASMN_TimerYFunctions
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Decode and execute Timer C Primitive Menu Functions.
//=============================================================================
unsigned char ASMN_TimerYFunctions( u08 MenuCom )
{
  u08           UARTStatus   = ASMN_UARTTRANSFEROK;
  char          MenuCommand  = ASMN_MENUCODE_NOCMD;

  while( ( UARTStatus  == ASMN_UARTTRANSFEROK ) && 
	 ( MenuCommand != ASMN_MENUCODE_EXIT ) ) {

    UARTStatus = DisplayMenu( MenuCom, &MenuCommand );

    switch( MenuCommand ) {
      
    case ASMN_MENUCODE_EXIT: 
      break;
      
    case ASMN_MENUCODE_CNF:
      UARTStatus = TestTimerYConfig( MenuCom );
      break;

    case ASMN_MENUCODE_SSTOP:
      UARTStatus = TestTimerYStartStop( MenuCom );
      break;
      
    case ASMN_MENUCODE_RESET:
      UARTStatus = TestTimerYReset( MenuCom );
      break;
      
    case ASMN_MENUCODE_RDTB:
      UARTStatus = TestTimerYReadTB( MenuCom );
      break;
      
    case ASMN_MENUCODE_IRQ:
      UARTStatus = TestTimerYInterrupt( MenuCom );
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

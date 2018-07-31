//============================================================================
// PROJECT = ASMN Test Monitor
// MODULE  = $Source$
// VERSION = $Revision: 256 $
// DATE    = $Date: 2004-04-07 14:02:55 +0200 (Mi, 07 Apr 2004) $
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2002 by NEC Electronics (EUROPE) GmbH. All rights reserved.
// Kanzlerstrasse 2
// D-40472 Duesseldorf
//============================================================================
// Purpose: Timer P Primitive Access Interface
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
// Revision 1.1  2004/04/07 11:59:58  liederr
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
#include <map_uarta.h>

#elif( ASMN_UARTINTERFACE == UARTC_STANDARD )
#include <map_uartc.h>

#else
#error "ASMN: No Communication Interface Defined"
#endif

/* Timer P Driver Interface */
#include <map_timerp.h>

/* Basic ASMN Configuration, dependent on device specifics */
#include <map_asmn.h>

#define ASMN_MENULINE_HDR1  "TIMER P TEST MONITOR\n"
#define ASMN_MENULINE_HDR2  "  (C) RL 01/2002    \n\n"
#define ASMN_MENULINE_MEN0  "0 -> Exit\n"

#if( TMP_TYPE == QLNPUTMPV1 )
#define ASMN_MENULINE_MEN1  "1 -> Port Enable\n"
#define ASMN_MENULINE_MEN2  "2 -> Port Disable\n"
#define ASMN_MENULINE_MEN3  "3 -> Timebase Configuration\n"
#define ASMN_MENULINE_MEN4  "4 -> Channel Configuration\n"
#define ASMN_MENULINE_MEN5  "5 -> Start Timer P\n"
#define ASMN_MENULINE_MEN6  "6 -> Stop Timer P\n"
#define ASMN_MENULINE_MEN7  "7 -> Reset Timer P\n"
#define ASMN_MENULINE_MEN8  "8 -> Read Timer P Timebase\n"
#define ASMN_MENULINE_MEN9  "9 -> Read/Write Timer P CC Registers\n"
#define ASMN_MENULINE_MEN10 "10-> Generate Interrupts\n"
#endif

#define ASMN_MENULINE_CMD1  "\nPlease Enter Command: "
#define ASMN_MENULINE_NOCMD "\nILLEGAL COMMAND\n\n"
#define ASMN_MENULINE_OK    "\nOK.\n"
#define ASMN_MENULINE_FAIL  "\nFAILED!!\n"
#define ASMN_MENULINE_IERR  "\nINPUT ERROR\n"

#define ASMN_MENUINPUT_TIMERUNIT  "\n Enter Timer Unit: "
#define ASMN_MENUINPUT_TICKPERIOD "\n Enter Tick Period: "
#define ASMN_MENUINPUT_TBONESHOT  "\n Enter OneShot Mode [0=OFF,1=ON]: "
#define ASMN_MENUINPUT_OPMODE     "\n Enter Operation Mode [0=INTERVAL,1=EXTCOUNT,2=EXTTRIG,3=ONESHOT,4=PWM,5=FREERUN,6=PWMEASURE]: "
#define ASMN_MENUINPUT_SYNCMODE   "\n Enter Synchronous Mode [0=OFF,1=SYNC]: "
#define ASMN_MENUINPUT_TBEXTEVT   "\n Enter Ext. Event Enable [0=OFF,1=ON]: "
#define ASMN_MENUINPUT_TBEDGEEVT  "\n Enter Ext. Event Edge [0=NONE,1=POS,2=NEG,3=BOTH]: "
#define ASMN_MENUINPUT_TBEDGETRG  "\n Enter Ext. Trig. Edge [0=NONE,1=POS,2=NEG,3=BOTH]: "
#define ASMN_MENUINPUT_CCMODE0    "\n Enter CC 0 Mode [1=CAPTURE,0=COMPARE,2=AS-IS]: "
#define ASMN_MENUINPUT_CCMODE1    "\n Enter CC 1 Mode [1=CAPTURE,0=COMPARE,2=AS-IS]: "
#define ASMN_MENUINPUT_CCOUTEN0   "\n Enter Output Enable 0 [0=OFF,1=ON]: "
#define ASMN_MENUINPUT_CCOUTEN1   "\n Enter Output Enable 1 [0=OFF,1=ON]: "
#define ASMN_MENUINPUT_CCOUTLVL0  "\n Enter Output Level 0 [0=NORM,1=INVERT]: "
#define ASMN_MENUINPUT_CCOUTLVL1  "\n Enter Output Level 1 [0=NORM,1=INVERT]: "
#define ASMN_MENUINPUT_CCEDGE0    "\n Enter Capture Edge CC0 [0=NEG,1=POS,2=AS-IS,3=BOTH]: "
#define ASMN_MENUINPUT_CCEDGE1    "\n Enter Capture Edge CC1 [0=NEG,1=POS,2=AS-IS,3=BOTH]: "
#define ASMN_MENUINPUT_CCVALUE1   "\n Enter CC "
#define ASMN_MENUINPUT_CCVALUE2   " Register Value: [ENTER=KEEP]: "
#define ASMN_MENUINPUT_INTLEVEL   "\n Enter Interrupt Level: "
#define ASMN_MENUINPUT_IRQEVERY   "\n Enter Indicator Count Threshold: "
#define ASMN_MENUINPUT_IRQSOURCE  "\n Enter Interrupt Source [0=OVF,1=CC0,2=CC1]: "
#define ASMN_MENUINPUT_BUFLEN     20
#define ASMN_MENUINPUT_SCANOK     1

#define ASMN_MENUCODE_SCANOK 1
#define ASMN_MENUCODE_NOCMD -1
#define ASMN_MENUCODE_EXIT  0

#if( TMP_TYPE == QLNPUTMPV1 )
#define ASMN_MENUCODE_PORTE 1
#define ASMN_MENUCODE_PORTD 2
#define ASMN_MENUCODE_TBCNF 3
#define ASMN_MENUCODE_CCCNF 4
#define ASMN_MENUCODE_STRT  5
#define ASMN_MENUCODE_STOP  6
#define ASMN_MENUCODE_RESET 7
#define ASMN_MENUCODE_RDTB  8
#define ASMN_MENUCODE_RWCC  9
#define ASMN_MENUCODE_IRQ   10
#endif

/*
 * global variables
 */

static u16 TMP_InterruptCount_u16 = 0;

/*
 * interrupt functions
 */

void TestTimerPIRQNotifier( )
{
  TMP_InterruptCount_u16++;
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
#ifdef ASMN_MENULINE_MEN8
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN8,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN9
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN9,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN10
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN10,
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
// FunctionName: TestTimerPPortEnable
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestTimerPPortEnable( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  u08           SuccessFlag = TMP_OK;
  int           UnitNumber  = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_TIMERUNIT,
				    &UnitNumber,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  if( SuccessFlag == TMP_OK )
  {
    SuccessFlag = TMP_PortEnable( ( u08 )UnitNumber );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == TMP_OK ) {
    
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
// FunctionName: TestTimerPPortDisable
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestTimerPPortDisable( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag = TMP_OK;
  int           UnitNumber  = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				    ASMN_MENUINPUT_TIMERUNIT,
				    &UnitNumber,
				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  if( SuccessFlag == TMP_OK )
  {
    SuccessFlag = TMP_PortDisable( ( u08 )UnitNumber );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == TMP_OK ) {
    
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
// FunctionName: TestTimerPTBConfig
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestTimerPCConfig( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag = TMP_OK;
  int           UnitNumber  = -1;
  int           CCMode0;
  int           CCMode1;
  int           OutputEnable0;
  int           OutputEnable1;
  int           ActiveLevel0;
  int           ActiveLevel1;
  int           Capture0Edge;
  int           Capture1Edge;
  u08           PCCMode0;
  u08           PCCMode1;
  u08           POutputEnable0;
  u08           POutputEnable1;
  u08           PActiveLevel0;
  u08           PActiveLevel1;
  u08           PCapture0Edge;
  u08           PCapture1Edge;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_TIMERUNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  ScanState = TMP_GetChannelConfiguration( ( u08 )UnitNumber,
                                                 &PCCMode0,
                                                 &PCCMode1,
                                                 &POutputEnable0,
                                                 &POutputEnable1,
                                                 &PActiveLevel0,
                                                 &PActiveLevel1,
			                                     &PCapture0Edge,
			                                     &PCapture1Edge );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) 
  {
    SuccessFlag = TMP_ERROR;
  }
  else 
  {
    CCMode0 = ( int )PCCMode0;
    CCMode1 = ( int )PCCMode1;
    OutputEnable0 = ( int )POutputEnable0;
    OutputEnable1 = ( int )POutputEnable1;
    ActiveLevel0  = ( int )PActiveLevel0;
    ActiveLevel1  = ( int )PActiveLevel1;
    Capture0Edge  = ( int )PCapture0Edge;
    Capture1Edge  = ( int )PCapture1Edge;
  }

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CCMODE0,
				                    &CCMode0,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CCMODE1,
				                    &CCMode1,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CCOUTEN0,
				                    &OutputEnable0,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CCOUTEN1,
				                    &OutputEnable1,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CCOUTLVL0,
				                    &ActiveLevel0,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CCOUTLVL1,
				                    &ActiveLevel1,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CCEDGE0,
				                    &Capture0Edge,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CCEDGE1,
				                    &Capture1Edge,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  if( SuccessFlag == TMP_OK )
  {
    SuccessFlag = TMP_SetChannelConfiguration( ( u08 )UnitNumber,
                                               ( u08 )CCMode0,
                                               ( u08 )CCMode1,
                                               ( u08 )OutputEnable0,
                                               ( u08 )OutputEnable1,
                                               ( u08 )ActiveLevel0,
                                               ( u08 )ActiveLevel1,
			                                   ( u08 )Capture0Edge,
			                                   ( u08 )Capture1Edge );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == TMP_OK ) {
    
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
// FunctionName: TestTimerPTBConfig
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestTimerPTBConfig( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag = TMP_OK;
  int           UnitNumber  = -1;
  float         TickPeriod;
  int           OperationMode;
  int           OneShotMode;
  int           SynchronousMode;
  int           ExtEventEnable;
  int           ExtEventEdge;
  int           ExtTrigEdge;
  u08           POperationMode;
  u08           POneShotMode;
  u08           PSynchronousMode;
  u08           PExtEventEnable;
  u08           PExtEventEdge;
  u08           PExtTrigEdge;
  u08           PClockSelection;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_TIMERUNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  ScanState = TMP_GetTimeBaseConfiguration( ( u08 )UnitNumber,
                                            OSCILLATOR_FREQUENCY,
                                            &TickPeriod, 
                                            &PClockSelection,
                                            &POperationMode,
                                            &POneShotMode,
                                            &PSynchronousMode,
                                            &PExtEventEnable,
                                            &PExtEventEdge,
                                            &PExtTrigEdge );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) 
  {
    SuccessFlag = TMP_ERROR;
  }
  else 
  {
    OperationMode = ( int )POperationMode;
    OneShotMode   = ( int )POneShotMode;
    SynchronousMode = ( int )PSynchronousMode;
    ExtEventEnable = ( int )PExtEventEnable;
    ExtEventEdge = ( int )PExtEventEdge;
    ExtTrigEdge = ( int )PExtTrigEdge;
  }

  UARTStatus = ASMN_UARTRECEIVEFLOAT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_TICKPERIOD,
                                      &TickPeriod,
                                      &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_OPMODE,
				                    &OperationMode,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_TBONESHOT,
				                    &OneShotMode,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_SYNCMODE,
				                    &SynchronousMode,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_TBEXTEVT,
				                    &ExtEventEnable,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_TBEDGEEVT,
				                    &ExtEventEdge,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_TBEDGETRG,
				                    &ExtTrigEdge,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  if( SuccessFlag == TMP_OK )
  {
    SuccessFlag = TMP_SetTimeBaseConfiguration( ( u08 )UnitNumber,
                                                OSCILLATOR_FREQUENCY,
                                                       TickPeriod, 
			                                    ( u08 )OperationMode,
                                                ( u08 )OneShotMode,
			                                    ( u08 )SynchronousMode,
			                                    ( u08 )ExtEventEnable,
			                                    ( u08 )ExtEventEdge,
			                                    ( u08 )ExtTrigEdge );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == TMP_OK ) {
    
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
// FunctionName: TestTimerPReset
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestTimerPReset( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag = TMP_OK;
  int           UnitNumber  = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_TIMERUNIT,
                				    &UnitNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  if( SuccessFlag == TMP_OK )
    SuccessFlag = TMP_Reset( ( u08 )UnitNumber );
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == TMP_OK ) {
    
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
// FunctionName: TestTimerPStart
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestTimerPStart( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag = TMP_OK;
  int           UnitNumber  = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_TIMERUNIT,
                				    &UnitNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  if( SuccessFlag == TMP_OK )
    SuccessFlag = TMP_Start( ( u08 )UnitNumber );
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == TMP_OK ) {
    
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
// FunctionName: TestTimerPStop
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestTimerPStop( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag = TMP_OK;
  int           UnitNumber  = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_TIMERUNIT,
                				    &UnitNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  if( SuccessFlag == TMP_OK )
    SuccessFlag = TMP_Stop( ( u08 )UnitNumber );
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == TMP_OK ) {
    
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
// FunctionName: TestTimerPReadWriteCC
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestTimerPReadWriteCC( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag   = TMP_OK;
  int           UnitNumber    = -1;
  u08           ReadChannels  = 0;
  int           ChannelValues[ TMP_CCREGS ];
  u16           PChannelValues[ TMP_CCREGS ];
  char          MenuString[ 80 ];

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_TIMERUNIT,
                				    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  ScanState = TMP_GetChannelValue( ( u08 )UnitNumber,
                                         &ReadChannels,
                                         &PChannelValues[ 0 ] );  

  if( ReadChannels != TMP_CCREGS ) SuccessFlag = TMP_ERROR;
  if( ScanState  != ASMN_MENUCODE_SCANOK ) 
  {
    SuccessFlag = TMP_ERROR;
  }
  else 
  {
    for( ReadChannels = 0; ReadChannels < TMP_CCREGS; ReadChannels++ )
    {
        ChannelValues[ ReadChannels ] = ( int )PChannelValues[ ReadChannels ];
        sprintf( MenuString, "%s%d%s", ASMN_MENUINPUT_CCVALUE1,
                                       ReadChannels,
                                       ASMN_MENUINPUT_CCVALUE2 );
        UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
        		                          MenuString,
                				          &ChannelValues[ ReadChannels ],
                				          &ScanState );
        if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
        if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;
    } // end for( ReadChannels = 0; ReadChannels < TMP_CCREGS; ReadChannels++ )
  }

  if( SuccessFlag == TMP_OK )
  {
    for( ReadChannels = 0; ReadChannels < TMP_CCREGS; ReadChannels++ )
    {
      SuccessFlag = TMP_SetChannelValue( ( u08 )UnitNumber,
                                                ReadChannels,
                                         ( u16 )ChannelValues[ ReadChannels ] );
      if( SuccessFlag != TMP_OK ) break;
    } // end for( ReadChannels = 0; ReadChannels < TMP_CCREGS; ReadChannels++ )
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == TMP_OK ) {
    
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
// FunctionName: TestTimerPReadTB
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestTimerPReadTB( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag = TMP_OK;
  int           UnitNumber  = -1;
  u16           ReadValue;
  char          ReadString[ 20 ];

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_TIMERUNIT,
                				    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  if( SuccessFlag == TMP_OK )
    SuccessFlag = TMP_GetTimeBaseValue( ( u08 )UnitNumber, 
                                        ( pu16 )( &ReadValue ) );
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				                  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == TMP_OK ) {
    
    sprintf( ReadString, "\n%04XH\n", ReadValue );
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
// FunctionName: TestTimerPInterrupt
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Insert interrupt handler to show a dot on every x-th interrupt occurrance
//=============================================================================
u08 TestTimerPInterrupt( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag = TMP_OK;
  u08           DummyByte;
  int           UnitNumber  = -1;
  int           EveryCount  = -1;
  int           IRQSource   = -1;
  int           IRQLevel    = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_TIMERUNIT,
                				    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_IRQEVERY,
                				    &EveryCount,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_IRQSOURCE,
                				    &IRQSource,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_INTLEVEL,
                				    &IRQLevel,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = TMP_ERROR;

  if( SuccessFlag == TMP_OK ) {

    TMP_InterruptCount_u16 = 0;

    SuccessFlag = TMP_CreateTimerInterrupt( ( u08 )UnitNumber,
                                            ( u08 )IRQSource,
                                            ( u08 )IRQLevel,
                			                TestTimerPIRQNotifier );
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

//=============================================================================
// FunctionName: ASMN_TimerPFunctions
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Decode and execute Timer C Primitive Menu Functions.
//=============================================================================
unsigned char ASMN_TimerPFunctions( u08 MenuCom )
{
  u08           UARTStatus   = ASMN_UARTTRANSFEROK;
  char          MenuCommand  = ASMN_MENUCODE_NOCMD;

  while( ( UARTStatus  == ASMN_UARTTRANSFEROK ) && 
	 ( MenuCommand != ASMN_MENUCODE_EXIT ) ) {

    UARTStatus = DisplayMenu( MenuCom, &MenuCommand );

    switch( MenuCommand ) {
      
    case ASMN_MENUCODE_EXIT: 
      break;
      
    case ASMN_MENUCODE_PORTE:
      UARTStatus = TestTimerPPortEnable( MenuCom );
      break;

    case ASMN_MENUCODE_PORTD:
      UARTStatus = TestTimerPPortDisable( MenuCom );
      break;

    case ASMN_MENUCODE_TBCNF:
      UARTStatus = TestTimerPTBConfig( MenuCom );
      break;

    case ASMN_MENUCODE_CCCNF:
      UARTStatus = TestTimerPCConfig( MenuCom );
      break;

    case ASMN_MENUCODE_STRT:
      UARTStatus = TestTimerPStart( MenuCom );
      break;
      
    case ASMN_MENUCODE_STOP:
      UARTStatus = TestTimerPStop( MenuCom );
      break;
      
    case ASMN_MENUCODE_RESET:
      UARTStatus = TestTimerPReset( MenuCom );
      break;
      
    case ASMN_MENUCODE_RDTB:
      UARTStatus = TestTimerPReadTB( MenuCom );
      break;
      
    case ASMN_MENUCODE_RWCC:
      UARTStatus = TestTimerPReadWriteCC( MenuCom );
      break;
      
    case ASMN_MENUCODE_IRQ:
      UARTStatus = TestTimerPInterrupt( MenuCom );
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

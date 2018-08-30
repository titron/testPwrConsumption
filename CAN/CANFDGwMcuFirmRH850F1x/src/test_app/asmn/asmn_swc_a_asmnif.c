//============================================================================
// PROJECT = ASMN Test Monitor
// MODULE  = $Source$
// VERSION = $Revision: 602 $
// DATE    = $Date: 2009-02-09 16:15:32 +0100 (Mo, 09 Feb 2009) $
//============================================================================
//                                 C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2002 by NEC Electronics (Europe) GmbH. All rights reserved.
// Kanzlerstrasse 2
// D-40472 Duesseldorf
// Germany
//============================================================================
//Purpose: SWC Application Interface
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
//
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
//
//============================================================================

#include <stddef.h>
#include <ree_types.h>
#include <map_asmn_basic.h>
#include <map_device.h>

#if( defined( EE_SWC_MACROS ) || defined( SWC_MACROS ) )

/* ASMN Modules: Main Communication Port */
#if( ASMN_UARTINTERFACE == UARTA_STANDARD )
#include <map_uarta.h>

#elif( ASMN_UARTINTERFACE == UARTC_STANDARD )
#include <map_uartc.h>

#elif( ASMN_UARTINTERFACE == UARTD_STANDARD )
#include <map_uartd.h>

#elif( ASMN_UARTINTERFACE == UARTE_STANDARD )
#include <map_uarte.h>

#else
#error "ASMN: No Communication Interface Defined"
#endif

/* SWC Driver Interface */
#include <map_swc.h>

/* Basic ASMN Configuration, dependent on device specifics */
#include <map_asmn.h>

#define ASMN_MENULINE_HDR1  "SWC APPLICATION MENU\n"
#define ASMN_MENULINE_HDR2  "  (C) RL 04/2010    \n\n"
#define ASMN_MENULINE_MEN0  " 0 -> Exit\n"

#if( SWC_TYPE == SWC_PROTOTYPE )
#define ASMN_MENULINE_MEN1  " 1 -> Start SWC with NM Support\n"
#define ASMN_MENULINE_MEN2  " 2 -> Send Standard Test Message\n"
#define ASMN_MENULINE_MEN3  " 3 -> Start & Wait on Sleep Timer\n"
#define ASMN_MENULINE_MEN4  " 4 -> Setup Wakeup Message & Check for Wakeup\n"
#define ASMN_MENULINE_MEN5  " 5 -> Setup NM Messages & Enable Periodic Sending\n"
#define ASMN_MENULINE_MEN6  " 6 -> Stop and Restart NM Messages\n"
#endif

#define ASMN_MENULINE_CMD1  "\nPlease Enter Command: "
#define ASMN_MENULINE_NOCMD "\nILLEGAL COMMAND\n\n"
#define ASMN_MENULINE_OK    "\nOK.\n"
#define ASMN_MENULINE_FAIL  "\nFAILED!!\n"
#define ASMN_MENULINE_IERR  "\nINPUT ERROR\n"

#define ASMN_MENUINPUT_CYCLES    "\n Enter Number of Cycles: "
#define ASMN_MENUINPUT_ECYCLES   "\n Enter Number of Cycles [0=Forever]: "
#define ASMN_MENUINPUT_ID        "\n Enter Message ID: "
#define ASMN_MENUINPUT_BAUDSEL   "\n Enter Baud Rate [bit/s, 0=MAX]: "
#define ASMN_MENUINPUT_UNIT      "\n Enter Unit [0...] "
#define ASMN_MENUINPUT_SLPTIMER  "\n Enter Sleep Timer Unit [0:1] "
#define ASMN_MENUINPUT_NMTIMER   "\n Enter # of NM Message Timer Units [1...3] "
#define ASMN_MENUINPUT_POWERSAVE "\n Enter Power Save Mode [0=ACTIVE,1=SLEEP,3=STOP] "
#define ASMN_MENUINPUT_ERRORMASK "\n Enter Error Mask [1CH = all on] "
#define ASMN_MENUINPUT_RESOL     "\n Enter Timer Resolution [sec] "
#define ASMN_MENUINPUT_SLPTIME   "\n Enter Sleep Time [sec] "
#define ASMN_MENUINPUT_WTTIME    "\n Enter Timeout Time [sec] "
#define ASMN_MENUINPUT_NMTIME    "\n Enter Average Message Period [sec] "
#define ASMN_MENUINPUT_RESYNC    "\n Enter Timer Resync Mode [0=NONE,1=ZERO,2=OFFSET] "

#define ASMN_MENUOUTPUT_WUPSTATE     "\n Wakeup Reason Register: %04xH, Combined Condition Code: %d"
#define ASMN_MENUOUTPUT_WUPFRAMEECTL "\n ID: %08lx; DLC: %02x; DATA: "
#define ASMN_MENUOUTPUT_WUPFRAMESCTL "\n ID: %03lx;      DLC: %02x; DATA: "
#define ASMN_MENUOUTPUT_WUPFRAMEDATA "%02x "
#define ASMN_MENUOUTPUT_WUPTIMEOUT   "\n TIMEOUT OCCURRED "
#define ASMN_MENUOUTPUT_WUPNMTIMEOUT "\n NM TIMEOUT OCCURRED "

#define ASMN_MENUINPUT_BUFLEN     20
#define ASMN_MENUINPUT_SCANOK     1

#define ASMN_MENUCODE_SCANOK   1
#define ASMN_MENUCODE_NOCMD   -1
#define ASMN_MENUCODE_EXIT     0
#define ASMN_MENUCODE_BACK     0

#if( SWC_TYPE == SWC_PROTOTYPE )
#define ASMN_MENUCODE_TEST1    1
#define ASMN_MENUCODE_TEST2    2
#define ASMN_MENUCODE_TEST3    3
#define ASMN_MENUCODE_TEST4    4
#define ASMN_MENUCODE_TEST5    5
#define ASMN_MENUCODE_TEST6    6
#endif

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
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN0,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
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
#ifdef ASMN_MENULINE_MEN11
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN11,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN20
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN20,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN21
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN21,
  			ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN30
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN30,
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
      else if( UserInput == 0x09 ) {
      	if( DigitCounter > 0 ) DigitCounter--;
      }
    }
  }

  *MenuCommand = -1;
  return( UARTStatus );
}

#ifdef ASMN_MENUCODE_TEST1

bit
ApplSWCInitWithNM( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = SWC_OK;
  int           Unit            = 0;
  unsigned long CANFrequency    = 0L;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &Unit,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = SWC_ERROR;

  UARTStatus = ASMN_UARTRECEIVELONG( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                     ASMN_MENUINPUT_BAUDSEL,
                                     &CANFrequency,
                                     &ScanState );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = SWC_ERROR;

  if( SuccessFlag == SWC_OK ) {
    
    SuccessFlag = SWC_ActivateForNM( ( u08 )Unit,
                                     ( u32 )CANFrequency );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == SWC_OK ) {
    
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

#endif

#ifdef ASMN_MENUCODE_TEST2

bit
ApplSWCSendStandardTestMessage( MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState       = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag     = SWC_OK;
  int           Unit            = 0;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &Unit,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = SWC_ERROR;

  if( SuccessFlag == SWC_OK ) {
    
    SuccessFlag = SWC_SendStandardTestFrame( ( u08 )Unit );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == SWC_OK ) {
    
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

#endif

#ifdef ASMN_MENUCODE_TEST3

bit ApplSWCStartAndWaitSleepTimer( MenuCom )
{
  bit           UARTStatus;
  unsigned char DummyByte;
  unsigned char ScanState           = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag         = SWC_OK;
  int           Unit                = 0;
  int           TimerInstance       = 0;
  flt           SleepTimeResolution = 0.0;
  flt           SleepTime           = 0.0;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &Unit,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = SWC_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_SLPTIMER,
				                    &TimerInstance,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = SWC_ERROR;

  UARTStatus = ASMN_UARTRECEIVEFLOAT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_RESOL,
                                      &SleepTimeResolution,
                                      &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = SWC_ERROR;

  UARTStatus = ASMN_UARTRECEIVEFLOAT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_SLPTIME,
                                      &SleepTime,
                                      &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = SWC_ERROR;

  ASMN_UARTSENDSTRING( MenuCom, "\n", ASMN_UARTMODECRLF );

  if( SuccessFlag == SWC_OK )
    {
      do
        {
          if( SuccessFlag == SWC_OK ) 
            {
              SuccessFlag = SWC_SleepTimer( ( u08 )Unit,
                                            ( u08 )TimerInstance,
                                            SleepTimeResolution,
                                            SleepTime );
              if( SuccessFlag == SWC_OK )
                ASMN_UARTSENDSTRING( MenuCom, ".", ASMN_UARTMODECR );
            }
          else 
            {
              break;
            }

#if( ASMN_UARTRECEIVEBYTE != ASMN_ReceiveByte )
          UARTStatus = ASMN_UARTRECEIVEBYTE( MenuCom, &DummyByte );
#else
  UARTStatus = ASMN_UARTERROR;
#endif          

        } while( UARTStatus != ASMN_UARTTRANSFEROK );

      ASMN_UARTSENDSTRING( MenuCom, "\n", ASMN_UARTMODECRLF );
    }
  else
    {
      UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                        ASMN_UARTMODECRLF );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    }
    
  if( SuccessFlag == SWC_OK ) {
    
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

#endif

#ifdef ASMN_MENUCODE_TEST4

bit ApplSWCSetupAndWaitMessages( MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState           = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag         = SWC_OK;
  int           Unit                = 0;

  flt           WTTimeResolution    = 0.0;
  flt           WTTime              = 0.0;

  u08           DataField[ SWC_DLC_MAX ];
  u08           DataCount;

  u16           WakeupReason        = 0x0000;
  u08           WakeupIndex         = 0x00;
  u08           ExtendedFrame       = 0x00;
  u32           Identifier          = 0x00000000L;
  u08           DataLength          = 0x00;
  unsigned long CANFrequency        = 0L;

  unsigned char DummyByte;
  char          WakeupString[ 80 ];

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &Unit,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = SWC_ERROR;

  UARTStatus = ASMN_UARTRECEIVELONG( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                     ASMN_MENUINPUT_BAUDSEL,
                                     &CANFrequency,
                                     &ScanState );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = SWC_ERROR;

  UARTStatus = ASMN_UARTRECEIVEFLOAT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_RESOL,
                                      &WTTimeResolution,
                                      &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = SWC_ERROR;

  UARTStatus = ASMN_UARTRECEIVEFLOAT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_WTTIME,
                                      &WTTime,
                                      &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = SWC_ERROR;

  if( SuccessFlag == SWC_OK ) {
    
    SuccessFlag =  SWC_SetWakeupMessages( ( u08 )Unit,
                                          WTTimeResolution,
                                          WTTime );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

#if( ASMN_UARTRECEIVEBYTE != ASMN_ReceiveByte )
  UARTStatus = ASMN_UARTRECEIVEBYTE( MenuCom, &DummyByte );
#else
  UARTStatus = ASMN_UARTERROR;
#endif
  
  SuccessFlag &= SWC_SetTLConfiguration( ( u08 )Unit,
                                         ( u32 )CANFrequency,
                                         0,
                                         0,
                                         0.0f );
  SuccessFlag &= SWC_Start( ( u08 )Unit,
                            SWC_NMSUPPORT_ON,
                            SWC_CANACTIVE_ON );

  while ( ( UARTStatus != ASMN_UARTTRANSFEROK ) &&
          ( SuccessFlag == SWC_OK ) ) {

#if( ASMN_UARTRECEIVEBYTE != ASMN_ReceiveByte )
    UARTStatus = ASMN_UARTRECEIVEBYTE( MenuCom, &DummyByte );       
#endif

    SuccessFlag &= SWC_CheckMessageWakeupReason( ( u08 )Unit,
                                                 &WakeupReason,
                                                 &WakeupIndex );
    if( WakeupReason != 0 )
      {
        sprintf( WakeupString, ASMN_MENUOUTPUT_WUPSTATE, 
                 WakeupReason, WakeupIndex );
        UARTStatus = ASMN_UARTSENDSTRING( MenuCom, WakeupString,
                                          ASMN_UARTMODECRLF );
        if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );

        SuccessFlag &= SWC_ReceiveWakeupMessage( ( u08 )Unit,
                                                 &ExtendedFrame,
                                                 &Identifier,
                                                 &DataLength,
                                                 &DataField[ 0 ] );
      }

#if( ASMN_UARTRECEIVEBYTE != ASMN_ReceiveByte )
    if( ( UARTStatus == ASMN_UARTTRANSFEROK ) &&
        ( DummyByte  == 'r' ) )
      {
#else
      {
        UARTStatus = ASMN_UARTTRANSFEROK;
#endif
        if( WakeupReason != 0 )
          {
            if( WakeupIndex == SWC_WUPREASON_TIMEOUT )
              {
                sprintf( WakeupString, ASMN_MENUOUTPUT_WUPTIMEOUT );
                UARTStatus = ASMN_UARTSENDSTRING( MenuCom, WakeupString,
                                                  ASMN_UARTMODECRLF );
                SuccessFlag &= SWC_Start( ( u08 )Unit,
                                          SWC_NMSUPPORT_ON,
                                          SWC_CANACTIVE_ON );
              }

            else if( WakeupIndex == SWC_WUPREASON_NMT )
              {
                sprintf( WakeupString, ASMN_MENUOUTPUT_WUPNMTIMEOUT );
                UARTStatus = ASMN_UARTSENDSTRING( MenuCom, WakeupString,
                                                  ASMN_UARTMODECRLF );
                SuccessFlag &= SWC_Start( ( u08 )Unit,
                                          SWC_NMSUPPORT_ON,
                                          SWC_CANACTIVE_ON );
              }

            else
              {
                if( ExtendedFrame )
                  sprintf( WakeupString, ASMN_MENUOUTPUT_WUPFRAMEECTL,
                           Identifier, DataLength );
                else
                  sprintf( WakeupString, ASMN_MENUOUTPUT_WUPFRAMESCTL,
                           Identifier, DataLength );
                UARTStatus = ASMN_UARTSENDSTRING( MenuCom, WakeupString,
                                                  ASMN_UARTMODECRLF );
                for( DataCount = 0; 
                     DataCount < ( DataLength <= SWC_DLC_MAX ? DataLength : SWC_DLC_MAX );
                     DataCount++ )
                  {
                    sprintf( WakeupString, ASMN_MENUOUTPUT_WUPFRAMEDATA,
                             DataField[ DataCount ] );
                    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, WakeupString,
                                                      ASMN_UARTMODECRLF );
                  }

                SuccessFlag &= SWC_Start( ( u08 )Unit,
                                          SWC_NMSUPPORT_ON,
                                          SWC_CANACTIVE_ON );
              }
          }
        UARTStatus = ASMN_UARTERROR;
      }
  }

  SuccessFlag &= SWC_DisableWakeupMessage( ( u08 )Unit,
                                           SWC_ENABLE_ALL );

  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, "\n",
                                    ASMN_UARTMODECRLF );
  if( SuccessFlag == SWC_OK ) {
    
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

#endif

#ifdef ASMN_MENUCODE_TEST5

bit ApplSWCInitializeNMMessages( MenuCom )
{
  bit           UARTStatus;
  unsigned char DummyByte;
  unsigned char ScanState           = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag         = SWC_OK;
  int           Unit                = 0;
  int           TimerInstances      = 1;
  flt           SleepTimeResolution = 0.0;
  flt           NMTime              = 0.0;

  unsigned long CANFrequency        = 0L;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &Unit,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = SWC_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_NMTIMER,
				                    &TimerInstances,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = SWC_ERROR;

  UARTStatus = ASMN_UARTRECEIVEFLOAT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_RESOL,
                                      &SleepTimeResolution,
                                      &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = SWC_ERROR;

  UARTStatus = ASMN_UARTRECEIVEFLOAT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_NMTIME,
                                      &NMTime,
                                      &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = SWC_ERROR;

  UARTStatus = ASMN_UARTRECEIVELONG( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                     ASMN_MENUINPUT_BAUDSEL,
                                     &CANFrequency,
                                     &ScanState );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = SWC_ERROR;

  if( SuccessFlag == SWC_OK )
    {
      SuccessFlag = SWC_NMSendTimer( ( u08 )Unit,
                                     ( u08 )TimerInstances,
                                     SleepTimeResolution,
                                     NMTime );
      
      SuccessFlag &= SWC_SetTLConfiguration( ( u08 )Unit,
                                             ( u32 )CANFrequency,
                                             0,
                                             0,
                                             0.0f );
      SuccessFlag &= SWC_Start( ( u08 )Unit,
                                SWC_NMSUPPORT_ON,
                                SWC_CANACTIVE_ON );
    }
  else
    {
      UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                        ASMN_UARTMODECRLF );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    }
    
  if( SuccessFlag == SWC_OK ) {
    
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

#endif

#ifdef ASMN_MENUCODE_TEST6

bit ApplSWCRestartNMMessages( MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState           = ASMN_MENUCODE_SCANOK;
  bit           SuccessFlag         = SWC_OK;
  int           Unit                = 0;
  int           TimerInstances      = 1;
  int           ResyncMode          = 0;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &Unit,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = SWC_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_NMTIMER,
				                    &TimerInstances,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = SWC_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_RESYNC,
				                    &ResyncMode,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = SWC_ERROR;

  if( SuccessFlag == SWC_OK )
    {
      SuccessFlag = SWC_NMTimerRestart( ( u08 )Unit,
                                        ( u08 )TimerInstances,
                                        ( u08 )ResyncMode );
    }
  else
    {
      UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                        ASMN_UARTMODECRLF );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    }
    
  if( SuccessFlag == SWC_OK ) {
    
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

#endif

bit ASMN_SWCApplications( u08 MenuCom )
{
  bit           UARTStatus   = ASMN_UARTTRANSFEROK;
  char          MenuCommand  = ASMN_MENUCODE_NOCMD;

  while( ( UARTStatus  == ASMN_UARTTRANSFEROK ) && 
         ( MenuCommand != ASMN_MENUCODE_EXIT ) ) {

    UARTStatus = DisplayMainMenu( MenuCom, &MenuCommand );

    switch( MenuCommand ) {

    case ASMN_MENUCODE_EXIT: 
      break;
      
#ifdef ASMN_MENUCODE_TEST1
    case ASMN_MENUCODE_TEST1:
      UARTStatus = ApplSWCInitWithNM( MenuCom );
      break;
#endif

#ifdef ASMN_MENUCODE_TEST2
    case ASMN_MENUCODE_TEST2:
      UARTStatus = ApplSWCSendStandardTestMessage( MenuCom );
      break;
#endif

#ifdef ASMN_MENUCODE_TEST3
    case ASMN_MENUCODE_TEST3:
      UARTStatus = ApplSWCStartAndWaitSleepTimer( MenuCom );
      break;
#endif

#ifdef ASMN_MENUCODE_TEST4
    case ASMN_MENUCODE_TEST4:
      UARTStatus = ApplSWCSetupAndWaitMessages( MenuCom );
      break;
#endif

#ifdef ASMN_MENUCODE_TEST5
    case ASMN_MENUCODE_TEST5:
      UARTStatus = ApplSWCInitializeNMMessages( MenuCom );
      break;
#endif

#ifdef ASMN_MENUCODE_TEST6
    case ASMN_MENUCODE_TEST6:
      UARTStatus = ApplSWCRestartNMMessages( MenuCom );
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

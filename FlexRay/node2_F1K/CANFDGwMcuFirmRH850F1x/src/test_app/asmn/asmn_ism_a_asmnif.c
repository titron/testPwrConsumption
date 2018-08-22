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
// Purpose: ISM Applications Access Interface
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

#include <stddef.h>
#include <ree_types.h>
#include <map_asmn_basic.h>
#include <map_device.h>

#ifdef EE_ISM_MACROS

/* ASMN Modules: Main Communication Port */
#if( ASMN_UARTINTERFACE == UARTA_STANDARD )
#include <map_uarta.h>

#elif( ASMN_UARTINTERFACE == UARTC_STANDARD )
#include <map_uartc.h>

#elif( ASMN_UARTINTERFACE == UARTD_STANDARD )
#include <map_uartd.h>

#elif( ASMN_UARTINTERFACE == UARTE_STANDARD )
#include <map_uarte.h>

#elif( ASMN_UARTINTERFACE == DEBUG_INTERNAL )
extern bit ASMN_SendString( u08   UnitNumber_u08,
                            char *SendString,
                            u08   TTYMode_u08 );
extern bit ASMN_SendByte( u08 UnitNumber_u08,
                          u08 SendByte_u08 );
extern bit ASMN_ReceiveByte( u08  UnitNumber_u08,
                             pu08 ReceiveByte_pu08 );
extern bit ASMN_ReceiveInteger( u08    UnitNumber_u08,
                                u16    ReceiveLength_u16,
                                char  *RequestString,
                                int   *Result,
                                pu08   ScanState_pu08 );
extern bit ASMN_ReceiveULong( u08            UnitNumber_u08,
                              u16            ReceiveLength_u16,
                              char          *RequestString,
                              unsigned long *Result,
                              pu08           ScanState_pu08 );
extern bit ASMN_ReceiveFloat( u08    UnitNumber_u08,
                              u16    ReceiveLength_u16,
                              char  *RequestString,
                              float *Result,
                              pu08   ScanState_pu08 );

#else
#error "ASMN: No Communication Interface Defined"
#endif

/* ISM Driver Interface */
#include <map_ism.h>

/* Basic ASMN Configuration, dependent on device specifics */
#include <map_asmn.h>

#define ASMN_MENULINE_HDR1  "ISM TEST MONITOR\n"
#define ASMN_MENULINE_HDR2  "  (C) RL 03/2009    \n\n"
#define ASMN_MENULINE_MEN0  "0 -> Exit\n"

#if( EE_ISM_TYPE == QLAPBISMV1 )
#define ASMN_MENULINE_MEN1  "1 -> Rotating PWM\n"
#define ASMN_MENULINE_MEN2  "2 -> Get CM Busy Time\n"
#define ASMN_MENULINE_MEN3  "3 -> Move by CM\n"
#define ASMN_MENULINE_MEN4  "4 -> Auto Move by CM (DEMO)\n"
#define ASMN_MENULINE_MEN5  "5 -> Select CM Parameter Set\n"
#define ASMN_MENULINE_MEN6  "6 -> Enable ZPD by CM\n"
#define ASMN_MENULINE_MEN7  "7 -> Monitor ZPD State\n"
#endif

#define ASMN_MENULINE_CMD1  "\nPlease Enter Command: "
#define ASMN_MENULINE_NOCMD "\nILLEGAL COMMAND\n\n"
#define ASMN_MENULINE_OK    "\nOK.\n"
#define ASMN_MENULINE_FAIL  "\nFAILED!!\n"
#define ASMN_MENULINE_IERR  "\nINPUT ERROR\n"

#define ASMN_MENUINPUT_UNIT       "\n Enter ISM Unit: "
#define ASMN_MENUINPUT_CHANNEL    "\n Enter Channel [0..5]: "
#define ASMN_MENUINPUT_CHANMASK   "\n Enter Channel Mask [5:0][SET=ENABLE,CLR=DISABLE]: "
#define ASMN_MENUINPUT_PWMFREQ    "\n Enter PWM Frequency: "
#define ASMN_MENUINPUT_CMFREQ     "\n Enter CM Frequency: "
#define ASMN_MENUINPUT_RECSIDE    "\n Enter Recirculation Side [0=VSS,1=VDD]: "
#define ASMN_MENUINPUT_CLEARPOS   "\n Enter Target Pos Clear Option [0=KEEP,1=CLEAR]: "
#define ASMN_MENUINPUT_SETTARGET  "\n Enter Target Position [Signed 16.8 Fixed Int Format]: "
#define ASMN_MENUINPUT_CHTYPE     "\n Enter Channel Type [0-5]: "
#define ASMN_MENUINPUT_CHPREC     "\n Enter Channel Precision [0=low,1=high]: "
#define ASMN_MENUINPUT_TABLENUM   "\n Enter Table Number [0...]: "
#define ASMN_MENUINPUT_PARAMNUM   "\n Enter Parameter Set Number [0=CONTI,1=JCI,2=CHINA,3=MARELLI]: "
#define ASMN_MENUINPUT_RNDMOVE    "\n Enter Random Movement Enable [0=OFF,1=ON]: "

#define ASMN_MENUINPUT_BUFLEN     20
#define ASMN_MENUINPUT_SCANOK     1

#define ASMN_MENUOUTPUT_RDBUSY    "\n Busy Count: %lu \n"
#define ASMN_MENUOUTPUT_MZPDHDR   "\nCH\tCZP\tCZC\tCZD\tZAF\tZIP\n"
#define ASMN_MENUOUTPUT_MZPDLINE  "%d:\t%d\t%d\t%d\t%d\t%d\n"

#define ASMN_MENUCODE_SCANOK 1
#define ASMN_MENUCODE_NOCMD -1
#define ASMN_MENUCODE_EXIT  0

#if( EE_ISM_TYPE == QLAPBISMV1 )
#define ASMN_MENUCODE_ROTPWM   1
#define ASMN_MENUCODE_GETBUSY  2
#define ASMN_MENUCODE_MOVECM   3
#define ASMN_MENUCODE_AMOVECM  4
#define ASMN_MENUCODE_SELPARAM 5
#define ASMN_MENUCODE_ZPDCM    6
#define ASMN_MENUCODE_MONZPD   7
#endif

/* UART Replacement Functions for Monitor */

#define ASMN_A_TTYMODE_CR   0 /* application level constants */
#define ASMN_A_TTYMODE_CRLF 1
#define ASMN_A_HEXMODE      1
#define ASMN_A_DECMODE      0
#define ASMN_A_RECBUFLEN    80

/*
 * global variables
 */

/*
 * interrupt functions
 */

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
#ifdef ASMN_MENULINE_MEN11
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN11,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN12
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN12,
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
// FunctionName: TestISMRotatePWM
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMRotatePWM( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag  = EE_ISM_OK;
  flt           PWMFrequency = 16.0e3;
  flt           CMFrequency  = 1.0e3;
  int           RecircSide   = 0;
  int           UnitNumber   = -1;
  int           ChannelFlags;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEFLOAT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_PWMFREQ,
                                      &PWMFrequency,
                                      &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEFLOAT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_CMFREQ,
                                      &CMFrequency,
                                      &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CHANMASK,
				                    &ChannelFlags,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_RECSIDE,
				                    &RecircSide,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  if( SuccessFlag == EE_ISM_OK )
  {
#ifdef ASMN_UARTCREATEINT
    SuccessFlag =  ASMN_UARTCREATEINT( MenuCom,
                                       ASMN_UARTIRQRX,
                                       ASMN_UARTIRQLEV,
                                       ISM_A_UARTABORT );
#endif
    SuccessFlag &= EE_ISM_PWMMoveTest( ( u08_t )UnitNumber,
                                       ( flt_t )PWMFrequency,
                                       ( flt_t )CMFrequency,
                                       ( u08_t )ChannelFlags,
                                       ( u08_t )RecircSide );
#ifdef ASMN_UARTCREATEINT
    SuccessFlag &= ASMN_UARTCREATEINT( MenuCom,
                                       ASMN_UARTIRQRX,
                                       ASMN_UARTIRQLEV,
                                       NULL );
#endif
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_ISM_OK ) {
    
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
// FunctionName: TestISMMonitorZPD
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMMonitorZPD( u08 MenuCom )
{
  u08           UserInput;
  u08           UARTStatus;
  u08           ScanState;
  u08           ChannelCount;
  bit           SuccessFlag  = EE_ISM_OK;
  u08           ZPDActive[ EE_ISM_CHANNELS ];
  u08           ZPDDelayState[ EE_ISM_CHANNELS ];
  u08           ZPDTableIndex[ EE_ISM_CHANNELS ];
  u08           ZPDMeasureActive[ EE_ISM_CHANNELS ];
  u08           ZPDCurrentResult[ EE_ISM_CHANNELS ];
  u08           ZPDAccumulatedResult[ EE_ISM_CHANNELS ];
  int           UnitNumber   = -1;
  int           ChannelFlags = -1;
  char          PrintString[ 80 ];

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CHANMASK,
				                    &ChannelFlags,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  if( SuccessFlag == EE_ISM_OK )
  {
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENUOUTPUT_MZPDHDR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );

    do {  /* repeat until one char to be received */

      SuccessFlag = EE_ISM_MonitorZPDCMChannels( ( u08_t )UnitNumber,
                                                 ( u08_t )ChannelFlags,
                                                 0,
                                                 &ZPDActive[ 0 ],
                                                 &ZPDDelayState[ 0 ],
                                                 &ZPDTableIndex[ 0 ],
                                                 &ZPDMeasureActive[ 0 ],
                                                 &ZPDCurrentResult[ 0 ],
                                                 &ZPDAccumulatedResult[ 0 ] );
      if( SuccessFlag == EE_ISM_OK ) {
    
        for( ChannelCount=0; ChannelCount<EE_ISM_CHANNELS; ChannelCount++ )
          {
            if( ChannelFlags & ( 1 << ChannelCount ) )
              {
                sprintf( PrintString, ASMN_MENUOUTPUT_MZPDLINE, 
                         ChannelCount,
                         ( int )ZPDActive[ ChannelCount ],
                         ( int )ZPDTableIndex[ ChannelCount ],
                         ( int )ZPDDelayState[ ChannelCount ],
                         ( int )ZPDMeasureActive[ ChannelCount ],
                         ( int )ZPDAccumulatedResult[ ChannelCount ] );

                UARTStatus = ASMN_UARTSENDSTRING( MenuCom, PrintString,
                                                  ASMN_UARTMODECRLF );
                if( UARTStatus != ASMN_UARTTRANSFEROK ) break;
              }
          }
      }
      else {

        UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_FAIL,
                                          ASMN_UARTMODECRLF );
        if( UARTStatus != ASMN_UARTTRANSFEROK ) break;
      }
      
      UARTStatus = ASMN_UARTRECEIVEBYTE( ASMN_MENUCOM, &UserInput );
      
    } while( UARTStatus != ASMN_UARTTRANSFEROK );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  SuccessFlag = EE_ISM_MonitorZPDCMChannels( ( u08_t )UnitNumber,
                                             ( u08_t )ChannelFlags,
                                             1,
                                             &ZPDActive[ 0 ],
                                             &ZPDDelayState[ 0 ],
                                             &ZPDTableIndex[ 0 ],
                                             &ZPDMeasureActive[ 0 ],
                                             &ZPDCurrentResult[ 0 ],
                                             &ZPDAccumulatedResult[ 0 ] );

  return( UARTStatus );
}

//=============================================================================
// FunctionName: TestISMGetBusyTime
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMGetBusyTime( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag  = EE_ISM_OK;
  flt           PWMFrequency = 16.0e3;
  flt           CMFrequency  = 1.0e3;
  u32           BusyCount;
  int           UnitNumber   = -1;
  int           ChannelFlags = -1;
  char          PrintString[ 80 ];

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEFLOAT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_PWMFREQ,
                                      &PWMFrequency,
                                      &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEFLOAT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_CMFREQ,
                                      &CMFrequency,
                                      &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CHANMASK,
				                    &ChannelFlags,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  if( SuccessFlag == EE_ISM_OK )
  {
    SuccessFlag = EE_ISM_GetCMCharacteristic( ( u08_t )UnitNumber,
                                              ( flt_t )PWMFrequency,
                                              ( flt_t )CMFrequency,
                                              ( u08_t )ChannelFlags,
                                              &BusyCount );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_ISM_OK ) {
    
    sprintf( PrintString, ASMN_MENUOUTPUT_RDBUSY, BusyCount );

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, PrintString,
                                      ASMN_UARTMODECRLF );

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
// FunctionName: TestISMSelectCMParamset
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMSelectCMParamset( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag      = EE_ISM_OK;
  int           ChannelNumber    = -1;
  int           SetNumber        = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CHANNEL,
				                    &ChannelNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_PARAMNUM,
				                    &SetNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  if( SuccessFlag == EE_ISM_OK )
  {
    SuccessFlag = EE_ISM_SelectCMParamset( ( u08_t )ChannelNumber,
                                           ( u08_t )SetNumber );
    switch( SetNumber )
      {
      case EE_ISM_A_USE_CONTI2000:
        SuccessFlag &= EE_ISM_SetMotor_CONTI2000( ( u08_t )ChannelNumber );
        break;

      case EE_ISM_A_USE_JCISONCEBOZ6403:
        SuccessFlag &= EE_ISM_SetMotor_JCISONCEBOZ6403( ( u08_t )ChannelNumber );
        break;

      case EE_ISM_A_USE_CHINASTANDARD:
        SuccessFlag &= EE_ISM_SetMotor_CHINASTANDARD( ( u08_t )ChannelNumber );
        break;

      case EE_ISM_A_USE_MARELLIPM20T:
        SuccessFlag &= EE_ISM_SetMotor_MARELLIPM20T( ( u08_t )ChannelNumber );
        break;

      default:
        SuccessFlag = EE_ISM_ERROR;
        break;
      }
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_ISM_OK ) {
    
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
// FunctionName: TestISMMoveCMChannel
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMMoveCMChannel( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag    = EE_ISM_OK;
  int           UnitNumber     = -1;
  int           ChannelFlags   = -1;
  unsigned long TargetPosition = 0L;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CHANMASK,
				                    &ChannelFlags,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVELONG( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                     ASMN_MENUINPUT_SETTARGET,
                                     &TargetPosition,
                                     &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  if( SuccessFlag == EE_ISM_OK )
  {
    SuccessFlag = EE_ISM_DownloadCMParamset( ( u08_t )UnitNumber,
                                             ( u08_t )ChannelFlags );
    SuccessFlag &= EE_ISM_SetupCMChannel( ( u08_t )UnitNumber,
                                          ( u08_t )ChannelFlags,
                                          0 );
    SuccessFlag &= EE_ISM_MoveCMChannel( ( u08_t )UnitNumber,
                                         ( u08_t )ChannelFlags,
                                         ( u32_t )TargetPosition );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_ISM_OK ) {
    
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
// FunctionName: TestISMZPDCMChannel
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMZPDCMChannel( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  u08           ChannelCount;
  u08           ChannelType;
  u08           ChannelPrecision;
  u08           HorizontalDelay;
  u08           VerticalDelay;
  u32           TargetPosition;
  bit           SuccessFlag    = EE_ISM_OK;
  int           UnitNumber     = -1;
  int           ChannelFlags   = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CHANMASK,
				                    &ChannelFlags,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  if( SuccessFlag == EE_ISM_OK )
  {
#ifdef ASMN_UARTCREATEINT
    SuccessFlag =  ASMN_UARTCREATEINT( MenuCom,
                                       ASMN_UARTIRQRX,
                                       ASMN_UARTIRQLEV,
                                       ISM_A_UARTABORT );
#endif
    /* Move selected motors to the next start of their PWM tables downwards */

    for( ChannelCount=0; ChannelCount<EE_ISM_CHANNELS; ChannelCount++ )
      {
        if( ChannelFlags & ( 1 << ChannelCount ) )
          {
            SuccessFlag &= EE_ISM_GetChannelControl( ( u08_t )UnitNumber,
                                                     ChannelCount,
                                                     &ChannelType,
                                                     &ChannelPrecision,
                                                     &HorizontalDelay,
                                                     &VerticalDelay );
            SuccessFlag &= EE_ISM_GetCMTargetPos( ( u08_t )UnitNumber,
                                                  ChannelCount,
                                                  &TargetPosition );
            if( TargetPosition != 0L )
              {
                if( ChannelPrecision ==  EE_ISM_PRECISION_HI )
                  TargetPosition &= ( ~( EE_ISM_TABLESIZE_HI - 1 ) ) << 8;
                else if( ChannelPrecision ==  EE_ISM_PRECISION_STD )
                  TargetPosition &= ( ~( EE_ISM_TABLESIZE_STD - 1 ) ) << 8;

                SuccessFlag &= EE_ISM_MoveCMChannel( ( u08_t )UnitNumber,
                                                     ( 1 << ChannelCount ),
                                                     TargetPosition );
              }
          }
      }

    /* Define the ZPD tables */

    SuccessFlag &= EE_ISM_DownloadCMParamset( ( u08_t )UnitNumber,
                                              ( u08_t )ChannelFlags );
    SuccessFlag &= EE_ISM_SetupCMChannel( ( u08_t )UnitNumber,
                                          ( u08_t )ChannelFlags,
                                          0 );

    /* Start ZPD Operation */

    SuccessFlag &= EE_ISM_ZPDCMChannel( ( u08_t )UnitNumber,
                                        ( u08_t )ChannelFlags );
#ifdef ASMN_UARTCREATEINT
    SuccessFlag &= ASMN_UARTCREATEINT( MenuCom,
                                       ASMN_UARTIRQRX,
                                       ASMN_UARTIRQLEV,
                                       NULL );
#endif
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_ISM_OK ) {
    
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
// FunctionName: TestISMAutoMoveCMChannel
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMAutoMoveCMChannel( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag    = EE_ISM_OK;
  int           UnitNumber     = -1;
  int           ChannelFlags   = -1;
  int           RandomMovement = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CHANMASK,
				                    &ChannelFlags,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_RNDMOVE,
				                    &RandomMovement,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  if( SuccessFlag == EE_ISM_OK )
  {
#ifdef ASMN_UARTCREATEINT
    SuccessFlag =  ASMN_UARTCREATEINT( MenuCom,
                                       ASMN_UARTIRQRX,
                                       ASMN_UARTIRQLEV,
                                       ISM_A_UARTABORT );
#endif
    SuccessFlag &= EE_ISM_DownloadCMParamset( ( u08_t )UnitNumber,
                                              ( u08_t )ChannelFlags );
    SuccessFlag &= EE_ISM_SetupCMChannel( ( u08_t )UnitNumber,
                                          ( u08_t )ChannelFlags,
                                          1 );
    SuccessFlag &= EE_ISM_AutoMoveCMChannel( ( u08_t )UnitNumber,
                                             ( u08_t )ChannelFlags,
                                             ( u08_t )RandomMovement );
#ifdef ASMN_UARTCREATEINT
    SuccessFlag &= ASMN_UARTCREATEINT( MenuCom,
                                       ASMN_UARTIRQRX,
                                       ASMN_UARTIRQLEV,
                                       NULL );
#endif
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_ISM_OK ) {
    
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
// FunctionName: ASMN_ISMApplications
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Decode and execute Timer C Primitive Menu Functions.
//=============================================================================
unsigned char ASMN_ISMApplications( u08 MenuCom )
{
  u08           UARTStatus   = ASMN_UARTTRANSFEROK;
  char          MenuCommand  = ASMN_MENUCODE_NOCMD;

  while( ( UARTStatus  == ASMN_UARTTRANSFEROK ) && 
	 ( MenuCommand != ASMN_MENUCODE_EXIT ) ) {

    UARTStatus = DisplayMenu( MenuCom, &MenuCommand );

    switch( MenuCommand ) {
      
    case ASMN_MENUCODE_EXIT: 
      break;
      
    case ASMN_MENUCODE_ROTPWM:
      UARTStatus = TestISMRotatePWM( MenuCom );
      break;

    case ASMN_MENUCODE_GETBUSY:
      UARTStatus = TestISMGetBusyTime( MenuCom );
      break;

    case ASMN_MENUCODE_MOVECM:
      UARTStatus = TestISMMoveCMChannel( MenuCom );
      break;

    case ASMN_MENUCODE_AMOVECM:
      UARTStatus = TestISMAutoMoveCMChannel( MenuCom );
      break;

    case ASMN_MENUCODE_SELPARAM:
      UARTStatus = TestISMSelectCMParamset( MenuCom );
      break;

    case ASMN_MENUCODE_ZPDCM:
      UARTStatus = TestISMZPDCMChannel( MenuCom );
      break;

    case ASMN_MENUCODE_MONZPD:
      UARTStatus = TestISMMonitorZPD( MenuCom );
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

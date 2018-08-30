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
// Purpose: ISM Primitive Access Interface
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
#define ASMN_MENULINE_MEN1  "1 -> Enable Ports\n"
#define ASMN_MENULINE_MEN2  "2 -> Disable Ports\n"
#define ASMN_MENULINE_MEN3  "3 -> Set Timebase\n"
#define ASMN_MENULINE_MEN4  "4 -> Read ISM Timebase\n"
#define ASMN_MENULINE_MEN5  "5 -> Generate Interrupts\n"
#define ASMN_MENULINE_MEN6  "6 -> Set Channel Configuration\n"
#define ASMN_MENULINE_MEN7  "7 -> Set PWM\n"
#define ASMN_MENULINE_MEN8  "8 -> Set Direct I/O\n"
#define ASMN_MENULINE_MEN9  "9 -> Release Direct I/O\n"
#define ASMN_MENULINE_MEN10 "10-> Set ZPD Configuration\n"
#define ASMN_MENULINE_MEN11 "11-> Set ZPD Channels\n"
#define ASMN_MENULINE_MEN12 "12-> ZPD Enable\n"
#define ASMN_MENULINE_MEN13 "13-> ZPD Reset\n"
#define ASMN_MENULINE_MEN14 "14-> ZPD Manual Start\n"
#define ASMN_MENULINE_MEN15 "15-> ZPD Read Status\n"
#define ASMN_MENULINE_MEN16 "16-> Soft Reset\n"
#define ASMN_MENULINE_MEN17 "17-> Set Channel Management\n"
#define ASMN_MENULINE_MEN18 "18-> Set Interrupt Enable\n"
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
#define ASMN_MENUINPUT_INTLEVEL   "\n Enter Interrupt Level: "
#define ASMN_MENUINPUT_IRQEVERY   "\n Enter Indicator Count Threshold: "
#define ASMN_MENUINPUT_IRQSOURCE  "\n Enter Interrupt Source [0=DONE,1=REACH,2=ZPDAD,3=ZPD]: "
#define ASMN_MENUINPUT_H_DELAY    "\n Enter Horizontal Delay [0-15]: "
#define ASMN_MENUINPUT_V_DELAY    "\n Enter Vertical Delay [0-15]: "
#define ASMN_MENUINPUT_CHTYPE     "\n Enter Channel Type [0-5]: "
#define ASMN_MENUINPUT_CHPREC     "\n Enter Channel Precision [0=low,1=high]: "
#define ASMN_MENUINPUT_H_DUTY     "\n Enter Horizontal Duty Cycle [%]: "
#define ASMN_MENUINPUT_V_DUTY     "\n Enter Vertical Duty Cycle [%]: "
#define ASMN_MENUINPUT_QUADRANT   "\n Enter Quadrant Info [0-3]: "
#define ASMN_MENUINPUT_H_RECIRC   "\n Enter Horizontal Recirculation Enable [0|1]: "
#define ASMN_MENUINPUT_V_RECIRC   "\n Enter Vertical Recirculation Enable [0|1]: "
#define ASMN_MENUINPUT_RECSIDE    "\n Enter Recirculation Side [0=VSS,1=VDD]: "
#define ASMN_MENUINPUT_H_DIRECT   "\n Enter Horizontal Direct I/O Control Code [H0-HF]: "
#define ASMN_MENUINPUT_V_DIRECT   "\n Enter Vertical Direct I/O Control Code [H0-HF]: "
#define ASMN_MENUINPUT_CMENABLE   "\n Enter Global CM Enable [0=OFF,1=ON]: "
#define ASMN_MENUINPUT_IEDONE     "\n Enter CM DONE Interrupt Enable [0=OFF,1=ON]: "
#define ASMN_MENUINPUT_IEZPDAD    "\n Enter CM ZPDAD Interrupt Enable [0=OFF,1=ON]: "
#define ASMN_MENUINPUT_ANLEVSEL   "\n Enter Analogue Level Selection [0|1]: "
#define ASMN_MENUINPUT_BLDELAY    "\n Enter Blanking Delay [0..65535]: "
#define ASMN_MENUINPUT_VIBDAMP    "\n Enter Vibration Damping [0|1]: "
#define ASMN_MENUINPUT_ZPDPERIOD  "\n Enter ZPD Step Period [us]: "
#define ASMN_MENUINPUT_ZPDSUSP    "\n Enter ZPD Suspend Clocks [0-7]: "
#define ASMN_MENUINPUT_ZPDFILLEN  "\n Enter ZPD Filter Level [0-15]: "
#define ASMN_MENUINPUT_ZPDFILDPTH "\n Enter ZPD Filter Depth [0-15]: "
#define ASMN_MENUINPUT_ZPDANALEV1 "\n Enter ZPD Analogue Level 1 [mV]:[8=150,9=250,10=350,11=450,12=550,13=650,14=750,15=850]: "
#define ASMN_MENUINPUT_ZPDANALEV2 "\n Enter ZPD Analogue Level 2 [mV]:[8=150,9=250,10=350,11=450,12=550,13=650,14=750,15=850]: "
#define ASMN_MENUINPUT_ZPDADCON   "\n Enter ZPD A/D Converter Connect [0=OFF,1=ON]: "
#define ASMN_MENUINPUT_ZPDEN      "\n Enter ZPD Enable [0|1]: "
#define ASMN_MENUINPUT_ZPDPWR     "\n Enter ZPD Power Save [0=ON,1=PWRSAVE]: "
#define ASMN_MENUINPUT_ZPDINPUT   "\n Enter ZPD Input [0=SINP,1=SINM,2=COSP,3=COSM]: "
#define ASMN_MENUINPUT_ZPDSTART   "\n Enter ZPD Trigger [0|1]: "

#define ASMN_MENUOUTPUT_RDTB      "\n Timebase: PWM: %lu Hz, CM: %lu Hz \n"
#define ASMN_MENUOUTPUT_RDZPD     "\n ZPD Period: %lu us \n"
#define ASMN_MENUOUTPUT_RDZPDSTAT "\n ZPD Status: Current ZDR: %d, ZIP: %d"

#define ASMN_MENUINPUT_BUFLEN     20
#define ASMN_MENUINPUT_SCANOK     1

#define ASMN_MENUCODE_SCANOK 1
#define ASMN_MENUCODE_NOCMD -1
#define ASMN_MENUCODE_EXIT  0

#if( EE_ISM_TYPE == QLAPBISMV1 )
#define ASMN_MENUCODE_PORTEN   1
#define ASMN_MENUCODE_PORTDIS  2
#define ASMN_MENUCODE_SETTB    3
#define ASMN_MENUCODE_RDTB     4
#define ASMN_MENUCODE_IRQ      5
#define ASMN_MENUCODE_CCONFIG  6
#define ASMN_MENUCODE_SETPWM   7
#define ASMN_MENUCODE_SETDIR   8
#define ASMN_MENUCODE_RELDIR   9
#define ASMN_MENUCODE_SETZPD   10
#define ASMN_MENUCODE_SETZPDCH 11
#define ASMN_MENUCODE_ZPDEN    12
#define ASMN_MENUCODE_ZPDRESET 13
#define ASMN_MENUCODE_ZPDSTART 14
#define ASMN_MENUCODE_ZPDSTATE 15
#define ASMN_MENUCODE_SRESET   16
#define ASMN_MENUCODE_CMEN     17
#define ASMN_MENUCODE_IEEN     18
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

static u16 ISM_InterruptCount_u16 = 0;

/*
 * interrupt functions
 */

void TestISMIRQNotifier( )
{
  ISM_InterruptCount_u16++;
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
#ifdef ASMN_MENULINE_MEN13
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN13,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN14
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN14,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN15
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN15,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN16
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN16,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN17
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN17,
				ASMN_UARTMODECRLF );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
#endif
#ifdef ASMN_MENULINE_MEN18
  UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_MEN18,
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
// FunctionName: TestISMChannelSetPWM
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMChannelSetPWM( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag         = EE_ISM_OK;
  int           UnitNumber          = -1;
  int           ChannelNumber       = -1;
  float         HorizontalDutyCycle;
  float         VerticalDutyCycle;
  int           QuadrantInfo        = -1;
  u16           HorizontalDutyCycle_u16;
  u16           VerticalDutyCycle_u16;
  u08           QuadrantInfo_u08;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CHANNEL,
				                    &ChannelNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  if( SuccessFlag == EE_ISM_OK )
    {
      SuccessFlag =  EE_ISM_GetPWM( ( u08_t )UnitNumber,
                                    ( u08_t )ChannelNumber,
                                    &HorizontalDutyCycle_u16,
                                    &VerticalDutyCycle_u16,
                                    &QuadrantInfo_u08 );
    }

  if( SuccessFlag == EE_ISM_OK )
    {
      HorizontalDutyCycle = 100.0 * ( float )( HorizontalDutyCycle_u16 ) / ( float )EE_ISM_TB_COUNTS;
      VerticalDutyCycle   = 100.0 * ( float )( VerticalDutyCycle_u16 ) / ( float )EE_ISM_TB_COUNTS;
      QuadrantInfo        = ( int )QuadrantInfo_u08;
      
      UARTStatus = ASMN_UARTRECEIVEFLOAT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                          ASMN_MENUINPUT_H_DUTY,
                                          &HorizontalDutyCycle,
                                          &ScanState );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
      if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

      UARTStatus = ASMN_UARTRECEIVEFLOAT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                          ASMN_MENUINPUT_V_DUTY,
                                          &VerticalDutyCycle,
                                          &ScanState );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
      if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

      UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                        ASMN_MENUINPUT_QUADRANT,
                                        &QuadrantInfo,
                                        &ScanState );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
      if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;
    }

  if( SuccessFlag == EE_ISM_OK )
  {
    SuccessFlag = EE_ISM_SetPWM( ( u08_t )UnitNumber,
                                 ( u08_t )ChannelNumber,
                                 ( u16_t )( HorizontalDutyCycle *
                                            ( float )EE_ISM_TB_COUNTS / 100.0 ),
                                 ( u16_t )( VerticalDutyCycle *
                                            ( float )EE_ISM_TB_COUNTS / 100.0 ),
                                 ( u08_t )QuadrantInfo );
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
// FunctionName: TestISMPortEnable
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMPortEnable( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag = EE_ISM_OK;
  int           UnitNumber    = 0;
  int           ChannelNumber = 0;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CHANNEL,
				                    &ChannelNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  if( SuccessFlag == EE_ISM_OK )
  {
    SuccessFlag = EE_ISM_PortEnable( ( u08 )UnitNumber,
                                     ( u08 )ChannelNumber );
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
// FunctionName: TestISMPortDisable
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMPortDisable( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag = EE_ISM_OK;
  int           UnitNumber    = 0;
  int           ChannelNumber = 0;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CHANNEL,
				                    &ChannelNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  if( SuccessFlag == EE_ISM_OK )
  {
    SuccessFlag = EE_ISM_PortDisable( ( u08 )UnitNumber,
                                      ( u08 )ChannelNumber );
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
// FunctionName: TestISMSetTB
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMSetTB( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag  = EE_ISM_OK;
  flt           PWMFrequency = 16.0e3;
  flt           CMFrequency  = 1.0e3;
  unsigned long PWMFrequency_r;
  unsigned long CMFrequency_r;
  int           UnitNumber   = -1;
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

  if( SuccessFlag == EE_ISM_OK )
  {
    SuccessFlag = EE_ISM_SetTimebase( ( u08 )UnitNumber,
                                      PWMFrequency,
                                      CMFrequency );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_ISM_OK )
  {
    SuccessFlag = EE_ISM_GetTimebase( ( u08 )UnitNumber,
                                      ( unsigned long* )( &PWMFrequency_r ),
                                      ( unsigned long* )( &CMFrequency_r ) );
  }

  if( SuccessFlag == EE_ISM_OK ) {
    
    sprintf( PrintString, ASMN_MENUOUTPUT_RDTB, PWMFrequency_r,
                                                CMFrequency_r );

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
// FunctionName: TestISMZPDStatus
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMZPDStatus( u08 MenuCom )
{
  u08           UserInput;
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag   = EE_ISM_OK;
  int           UnitNumber    = -1;
  int           ChannelNumber = -1;
  u08           ZPDCurrentResult_u08;
  u08           ZPDAccumulatedResult_u08;
  u08           DummyReadValue_u08;
  char          ReadString[ 80 ];

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CHANNEL,
				                    &ChannelNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  do {  /* repeat until one char to be received */

    if( SuccessFlag == EE_ISM_OK )
      SuccessFlag = EE_ISM_ReadZPDStatus( ( u08_t )UnitNumber,
                                          ( u08_t )ChannelNumber,
                                          &DummyReadValue_u08,
                                          &DummyReadValue_u08,
                                          &DummyReadValue_u08,
                                          &DummyReadValue_u08,
                                          &ZPDCurrentResult_u08,
                                          &ZPDAccumulatedResult_u08 );
    else {
      
      UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                        ASMN_UARTMODECRLF );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    }

    if( SuccessFlag == EE_ISM_OK ) {
    
      sprintf( ReadString, ASMN_MENUOUTPUT_RDZPDSTAT, ZPDCurrentResult_u08, 
               ZPDAccumulatedResult_u08 );
      UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ReadString,
                                        ASMN_UARTMODECRLF );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    }
    else {
      
      UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_FAIL,
                                        ASMN_UARTMODECRLF );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    }
      
    UARTStatus = ASMN_UARTRECEIVEBYTE( ASMN_MENUCOM, &UserInput );
      
  } while( UARTStatus != ASMN_UARTTRANSFEROK );

  return( UARTStatus );
}

//=============================================================================
// FunctionName: TestISMInterrupt
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Insert interrupt handler to show a dot on every x-th interrupt occurrance
//=============================================================================
u08 TestISMInterrupt( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag = EE_ISM_OK;
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
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_IRQEVERY,
                				    &EveryCount,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_IRQSOURCE,
                				    &IRQSource,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_INTLEVEL,
                				    &IRQLevel,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  if( SuccessFlag == EE_ISM_OK ) {

    ISM_InterruptCount_u16 = 0;

    SuccessFlag = EE_ISM_CreateInterrupt( ( u08 )UnitNumber,
                                          ( u08 )IRQSource,
                                          ( u16 )IRQLevel,
                                          TestISMIRQNotifier );
  }

  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_ISM_OK ) {

    ASMN_UARTSENDSTRING( MenuCom, "\n", ASMN_UARTMODECRLF );

    do {

      if( ISM_InterruptCount_u16 >= EveryCount ) {

	    ISM_InterruptCount_u16 = 0;
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
// FunctionName: TestISMReadTB
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMReadTB( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag = EE_ISM_OK;
  int           UnitNumber  = -1;
  u32           ReadValue;
  char          ReadString[ 20 ];

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
                				    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  if( SuccessFlag == EE_ISM_OK )
    SuccessFlag = EE_ISM_ReadTimebase( ( u08 )UnitNumber, 
                                       ( pu32 )( &ReadValue ) );
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				                  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_ISM_OK ) {
    
    sprintf( ReadString, "\n%08XH\n", ReadValue );
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
// FunctionName: TestISMSetZPDConfig
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMSetZPDConfig( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag  = EE_ISM_OK;
  flt           ZPDPeriod;
  u32           ZPDPeriodus_u32;
  u08           ZPDSuspendClocks_u08;
  u08           ZPDFilterLength_u08;
  u08           ZPDFilterDepth_u08;
  u08           ZPDAnalogLevel_u08;
  u08           ZPDADConnect_u08;
  int           UnitNumber   = -1;
  int           ZPDAnalogSelection = -1;
  unsigned long ZPDPeriodus;
  int           ZPDSuspendClocks;
  int           ZPDFilterLength;
  int           ZPDFilterDepth;
  int           ZPDAnalogLevel;
  int           ZPDADConnect;
  char          PrintString[ 80 ];

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_ANLEVSEL,
				                    &ZPDAnalogSelection,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  if( SuccessFlag == EE_ISM_OK )
  {
    SuccessFlag = EE_ISM_GetZPDGlobals( ( u08_t )UnitNumber,
                                        ( u08_t )ZPDAnalogSelection,
                                        &ZPDPeriodus_u32,
                                        &ZPDSuspendClocks_u08,
                                        &ZPDFilterLength_u08,
                                        &ZPDFilterDepth_u08,
                                        &ZPDAnalogLevel_u08,
                                        &ZPDADConnect_u08 );
  }

  if( SuccessFlag == EE_ISM_OK )
  {
    ZPDPeriodus      = ( unsigned long )ZPDPeriodus_u32;
    ZPDSuspendClocks =           ( int )ZPDSuspendClocks_u08;
    ZPDFilterLength  =           ( int )ZPDFilterLength_u08;
    ZPDFilterDepth   =           ( int )ZPDFilterDepth_u08;
    ZPDAnalogLevel   =           ( int )ZPDAnalogLevel_u08;
    ZPDADConnect     =           ( int )ZPDADConnect_u08;

    UARTStatus = ASMN_UARTRECEIVELONG( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                       ASMN_MENUINPUT_ZPDPERIOD,
                                       &ZPDPeriodus,
                                       &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_ZPDSUSP,
                                      &ZPDSuspendClocks,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_ZPDFILLEN,
                                      &ZPDFilterLength,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_ZPDFILDPTH,
                                      &ZPDFilterDepth,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_ZPDANALEV1,
                                      &ZPDAnalogLevel,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_ZPDADCON,
                                      &ZPDADConnect,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;
  }

  if( SuccessFlag == EE_ISM_OK )
  {
    ZPDPeriod   = ( flt )ZPDPeriodus * 1.0E-6;
    SuccessFlag = EE_ISM_SetZPDGlobals( ( u08_t )UnitNumber,
                                        ( flt_t )ZPDPeriod,
                                        ( u08_t )ZPDSuspendClocks,
                                        ( u08_t )ZPDFilterLength,
                                        ( u08_t )ZPDFilterDepth,
                                        ( u08_t )ZPDAnalogLevel,
                                        ( u08_t )ZPDAnalogSelection,
                                        ( u08_t )ZPDADConnect );
  }
  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == EE_ISM_OK )
  {
    SuccessFlag = EE_ISM_GetZPDGlobals( ( u08_t )UnitNumber,
                                        ( u08_t )ZPDAnalogSelection,
                                        &ZPDPeriodus_u32,
                                        &ZPDSuspendClocks_u08,
                                        &ZPDFilterLength_u08,
                                        &ZPDFilterDepth_u08,
                                        &ZPDAnalogLevel_u08,
                                        &ZPDADConnect_u08 );
  }

  if( SuccessFlag == EE_ISM_OK ) {
    
    sprintf( PrintString, ASMN_MENUOUTPUT_RDZPD, ZPDPeriodus_u32 );

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
// FunctionName: TestISMChannelSetConfig
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMChannelSetConfig( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag   = EE_ISM_OK;
  u08           ChannelType_u08;
  u08           ChannelPrecision_u08;
  u08           HorizontalDelay_u08;
  u08           VerticalDelay_u08;
  u08           RecirculationEnableHorizontal_u08;
  u08           RecirculationEnableVertical_u08;
  u08           RecirculationSide_u08;
  int           UnitNumber    = -1;
  int           ChannelNumber = -1;
  int           ChannelType   = 0;
  int           Precision     = 0;
  int           HorDelay      = 0;
  int           VerDelay      = 0;
  int           RecircSide    = 0;
  int           RecircHorEn   = 1;
  int           RecircVerEn   = 1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CHANNEL,
				                    &ChannelNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  if( SuccessFlag == EE_ISM_OK )
    {
      SuccessFlag =  EE_ISM_GetChannelControl( ( u08_t )UnitNumber,
                                               ( u08_t )ChannelNumber,
                                               &ChannelType_u08,
                                               &ChannelPrecision_u08,
                                               &HorizontalDelay_u08,
                                               &VerticalDelay_u08 );
      SuccessFlag &= EE_ISM_GetRecirculation( ( u08_t )UnitNumber,
                                              ( u08_t )ChannelNumber,
                                               &RecirculationEnableHorizontal_u08,
                                               &RecirculationEnableVertical_u08,
                                               &RecirculationSide_u08 );
    }

  if( SuccessFlag == EE_ISM_OK )
    {
      ChannelType   = ( int )ChannelType_u08;
      Precision     = ( int )ChannelPrecision_u08;
      HorDelay      = ( int )HorizontalDelay_u08;
      VerDelay      = ( int )VerticalDelay_u08;
      RecircSide    = ( int )RecirculationSide_u08;
      RecircHorEn   = ( int )RecirculationEnableHorizontal_u08;
      RecircVerEn   = ( int )RecirculationEnableVertical_u08;
      
      UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                        ASMN_MENUINPUT_CHTYPE,
                                        &ChannelType,
                                        &ScanState );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
      if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;
      
      UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                        ASMN_MENUINPUT_CHPREC,
                                        &Precision,
                                        &ScanState );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
      if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;
      
      UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                        ASMN_MENUINPUT_H_DELAY,
                                        &HorDelay,
                                        &ScanState );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
      if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;
      
      UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                        ASMN_MENUINPUT_V_DELAY,
                                        &VerDelay,
                                        &ScanState );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
      if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;
      
      UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                        ASMN_MENUINPUT_RECSIDE,
                                        &RecircSide,
                                        &ScanState );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
      if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;
      
      UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                        ASMN_MENUINPUT_H_RECIRC,
                                        &RecircHorEn,
                                        &ScanState );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
      if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;
      
      UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                        ASMN_MENUINPUT_V_RECIRC,
                                        &RecircVerEn,
                                        &ScanState );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
      if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;
    }

  if( SuccessFlag == EE_ISM_OK )
    {
      SuccessFlag =  EE_ISM_SetChannelType( ( u08_t )UnitNumber,
                                            ( u08_t )ChannelNumber,
                                            ( u08_t )ChannelType,
                                            ( u08_t )Precision );
      SuccessFlag &= EE_ISM_SetChannelDelay( ( u08_t )UnitNumber,
                                             ( u08_t )ChannelNumber,
                                             ( u08_t )HorDelay,
                                             ( u08_t )VerDelay );
      SuccessFlag &= EE_ISM_SetRecirculation( ( u08_t )UnitNumber,
                                              ( u08_t )ChannelNumber,
                                              ( u08_t )RecircHorEn,
                                              ( u08_t )RecircVerEn,
                                              ( u08_t )RecircSide );
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
// FunctionName: TestISMSetZPDChannel
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMSetZPDChannel( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag          = EE_ISM_OK;
  int           UnitNumber           = -1;
  int           ChannelNumber        = -1;
  int           AnalogLevelSelection = -1;
  int           BlankingDelay        = -1;
  int           VibrationDamping     = -1;
  u08           AnalogLevelSelection_u08;
  u08           VibrationDamping_u08;
  u16           BlankingDelay_u16;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CHANNEL,
				                    &ChannelNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  if( SuccessFlag == EE_ISM_OK )
    {
      SuccessFlag = EE_ISM_GetZPDChannels( ( u08_t )UnitNumber,
                                           ( u08_t )ChannelNumber,
                                           &AnalogLevelSelection_u08,
                                           &BlankingDelay_u16,
                                           &VibrationDamping_u08 );
    }

  if( SuccessFlag == EE_ISM_OK )
    {
      AnalogLevelSelection = ( int )AnalogLevelSelection_u08;
      BlankingDelay        = ( int )BlankingDelay_u16;
      VibrationDamping     = ( int )VibrationDamping_u08;
      
      UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                        ASMN_MENUINPUT_ANLEVSEL,
                                        &AnalogLevelSelection,
                                        &ScanState );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
      if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

      UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                        ASMN_MENUINPUT_BLDELAY,
                                        &BlankingDelay,
                                        &ScanState );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
      if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

      UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                        ASMN_MENUINPUT_VIBDAMP,
                                        &VibrationDamping,
                                        &ScanState );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
      if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

    }

  if( SuccessFlag == EE_ISM_OK )
  {
    SuccessFlag = EE_ISM_SetZPDChannels( ( u08_t )UnitNumber,
                                         ( u08_t )ChannelNumber,
                                         ( u08_t )AnalogLevelSelection,
                                         ( u16_t )BlankingDelay,
                                         ( u08_t )VibrationDamping );
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
// FunctionName: TestISMChannelSetDirectIO
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMChannelSetDirectIO( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag            = EE_ISM_OK;
  int           UnitNumber             = -1;
  int           ChannelNumber          = -1;
  int           HorizontalDirect       = -1;
  int           VerticalDirect         = -1;
  u08           HorizontalDirectEnable_u08;
  u08           HorizontalDirect_u08;
  u08           VerticalDirectEnable_u08;
  u08           VerticalDirect_u08;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CHANNEL,
				                    &ChannelNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  if( SuccessFlag == EE_ISM_OK )
    {
      SuccessFlag =  EE_ISM_GetDirectIO( ( u08_t )UnitNumber,
                                         ( u08_t )ChannelNumber,
                                         &HorizontalDirectEnable_u08,
                                         &HorizontalDirect_u08,
                                         &VerticalDirectEnable_u08,
                                         &VerticalDirect_u08 );
    }

  if( SuccessFlag == EE_ISM_OK )
    {
      HorizontalDirect       = ( int )HorizontalDirect_u08;
      VerticalDirect         = ( int )VerticalDirect_u08;
      
      UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                        ASMN_MENUINPUT_H_DIRECT,
                                        &HorizontalDirect,
                                        &ScanState );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
      if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

      UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                        ASMN_MENUINPUT_V_DIRECT,
                                        &VerticalDirect,
                                        &ScanState );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
      if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;
    }

  if( SuccessFlag == EE_ISM_OK )
  {
    SuccessFlag = EE_ISM_SetDirectIO( ( u08_t )UnitNumber,
                                      ( u08_t )ChannelNumber,
                                      ( u08_t )HorizontalDirect,
                                      ( u08_t )VerticalDirect );
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
// FunctionName: TestISMChannelReleaseDirectIO
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMChannelReleaseDirectIO( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag   = EE_ISM_OK;
  int           UnitNumber    = -1;
  int           ChannelNumber = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CHANNEL,
				                    &ChannelNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  if( SuccessFlag == EE_ISM_OK )
  {
    SuccessFlag = EE_ISM_ReleaseDirectIO( ( u08_t )UnitNumber,
                                          ( u08_t )ChannelNumber );
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
// FunctionName: TestISMZPDReset
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMZPDReset( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag   = EE_ISM_OK;
  int           UnitNumber    = -1;
  int           ChannelNumber = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_CHANNEL,
				                    &ChannelNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  if( SuccessFlag == EE_ISM_OK )
  {
    SuccessFlag = EE_ISM_ResetZPD( ( u08_t )UnitNumber,
                                   ( u08_t )ChannelNumber );
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
// FunctionName: TestISMSoftReset
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMSoftReset( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag   = EE_ISM_OK;
  int           UnitNumber    = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  if( SuccessFlag == EE_ISM_OK )
  {
    SuccessFlag = EE_ISM_Reset( ( u08_t )UnitNumber );
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
// FunctionName: TestISMCMEnable
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMCMEnable( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag   = EE_ISM_OK;
  int           UnitNumber    = -1;
  int           GlobalEnableFlag;
  int           ChannelFlags;
  u08           ChannelFlags_u08;
  u08           GlobalEnableFlag_u08;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  if( SuccessFlag == EE_ISM_OK )
  {
    SuccessFlag = EE_ISM_GetCMEnable( ( u08_t )UnitNumber,
                                      &ChannelFlags_u08,
                                      &GlobalEnableFlag_u08 );
  }

  if( SuccessFlag == EE_ISM_OK )
  {
    GlobalEnableFlag       = ( int )GlobalEnableFlag_u08;
    ChannelFlags           = ( int )ChannelFlags_u08;
    
    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_CMENABLE,
                                      &GlobalEnableFlag,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_CHANMASK,
                                      &ChannelFlags,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;
  }

  if( SuccessFlag == EE_ISM_OK )
  {
    SuccessFlag =  EE_ISM_SetCMEnable( ( u08_t )UnitNumber,
                                       ( ~( ( u08_t )ChannelFlags ) ) & 
                                       EE_ISM_CHANNEL_ENALL,
                                       0 );
    SuccessFlag &= EE_ISM_SetCMEnable( ( u08_t )UnitNumber,
                                       ( u08_t )ChannelFlags,
                                       1 );
    SuccessFlag &= EE_ISM_SetCMEnable( ( u08_t )UnitNumber,
                                       EE_ISM_GLOBAL_EN,
                                       ( u08_t )GlobalEnableFlag );
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
// FunctionName: TestISMZPDStart
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMZPDStart( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag    = EE_ISM_OK;
  int           UnitNumber     = -1;
  int           ChannelFlags   = -1;
  int           InputSelection = -1;
  int           StartStopFlag  = -1;

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
                                    ASMN_MENUINPUT_ZPDINPUT,
                                    &InputSelection,
                                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;
  
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                    ASMN_MENUINPUT_ZPDSTART,
                                    &StartStopFlag,
                                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;
  
  if( SuccessFlag == EE_ISM_OK )
  {
    SuccessFlag = EE_ISM_OperateZPDDirect( ( u08_t )UnitNumber,
                                           ( u08_t )ChannelFlags,
                                           ( u08_t )InputSelection,
                                           ( u08_t )StartStopFlag );
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
// FunctionName: TestISMZPDEnable
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMZPDEnable( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag   = EE_ISM_OK;
  int           UnitNumber    = -1;
  int           ZPDPowerSave;
  int           ZPDEnable;
  u08           ZPDEnable_u08;
  u08           ZPDPowerSave_u08;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  if( SuccessFlag == EE_ISM_OK )
  {
    SuccessFlag = EE_ISM_GetEnableZPD( ( u08_t )UnitNumber,
                                       &ZPDEnable_u08,
                                       &ZPDPowerSave_u08 );
  }

  if( SuccessFlag == EE_ISM_OK )
  {
    ZPDPowerSave       = ( int )ZPDPowerSave_u08;
    ZPDEnable          = ( int )ZPDEnable_u08;
    
    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_ZPDEN,
                                      &ZPDEnable,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_ZPDPWR,
                                      &ZPDPowerSave,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;
  }

  if( SuccessFlag == EE_ISM_OK )
  {
    SuccessFlag =  EE_ISM_SetEnableZPD( ( u08_t )UnitNumber,
                                        ( u08_t )ZPDEnable,
                                        ( u08_t )ZPDPowerSave );
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
// FunctionName: TestISMIntEnable
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Get Arguments from user, execute the function above on the peripheral.
//=============================================================================
u08 TestISMIntEnable( u08 MenuCom )
{
  u08           UARTStatus;
  u08           ScanState;
  bit           SuccessFlag   = EE_ISM_OK;
  int           UnitNumber    = -1;
  int           GlobalEnableFlag;
  int           ZPDADEnableFlag;
  int           ChannelFlags;
  u08           ChannelFlags_u08;
  u08           GlobalEnableFlag_u08;
  u08           ZPDADEnableFlag_u08;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                				    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
                				    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

  if( SuccessFlag == EE_ISM_OK )
  {
    SuccessFlag = EE_ISM_GetInterrupt( ( u08_t )UnitNumber,
                                       &ChannelFlags_u08,
                                       &GlobalEnableFlag_u08,
                                       &ZPDADEnableFlag_u08 );
  }

  if( SuccessFlag == EE_ISM_OK )
  {
    GlobalEnableFlag       = ( int )GlobalEnableFlag_u08;
    ZPDADEnableFlag        = ( int )ZPDADEnableFlag_u08;
    ChannelFlags           = ( int )ChannelFlags_u08;
    
    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_IEDONE,
                                      &GlobalEnableFlag,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_IEZPDAD,
                                      &ZPDADEnableFlag,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;

    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_CHANMASK,
                                      &ChannelFlags,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = EE_ISM_ERROR;
  }

  if( SuccessFlag == EE_ISM_OK )
  {
    SuccessFlag =  EE_ISM_SetInterrupt( ( u08_t )UnitNumber,
                                        ~( ( u08_t )ChannelFlags ),
                                        ( u08_t )GlobalEnableFlag,
                                        ( u08_t )ZPDADEnableFlag,
                                        0 );
    SuccessFlag &= EE_ISM_SetInterrupt( ( u08_t )UnitNumber,
                                        ( u08_t )ChannelFlags,
                                        ( u08_t )GlobalEnableFlag,
                                        ( u08_t )ZPDADEnableFlag,
                                        1 );
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
// FunctionName: ASMN_ISMFunctions
// IN  : MenuCom:       Communication Port ID
// OUT : Return:        Communication status
// Description : 
// Decode and execute Timer C Primitive Menu Functions.
//=============================================================================
unsigned char ASMN_ISMFunctions( u08 MenuCom )
{
  u08           UARTStatus   = ASMN_UARTTRANSFEROK;
  char          MenuCommand  = ASMN_MENUCODE_NOCMD;

  while( ( UARTStatus  == ASMN_UARTTRANSFEROK ) && 
	 ( MenuCommand != ASMN_MENUCODE_EXIT ) ) {

    UARTStatus = DisplayMenu( MenuCom, &MenuCommand );

    switch( MenuCommand ) {
      
    case ASMN_MENUCODE_EXIT: 
      break;
      
    case ASMN_MENUCODE_PORTEN:
      UARTStatus = TestISMPortEnable( MenuCom );
      break;

    case ASMN_MENUCODE_PORTDIS:
      UARTStatus = TestISMPortDisable( MenuCom );
      break;
      
    case ASMN_MENUCODE_SETTB:
      UARTStatus = TestISMSetTB( MenuCom );
      break;
      
    case ASMN_MENUCODE_RDTB:
      UARTStatus = TestISMReadTB( MenuCom );
      break;
      
    case ASMN_MENUCODE_IRQ:
      UARTStatus = TestISMInterrupt( MenuCom );
      break;

    case ASMN_MENUCODE_CCONFIG:
      UARTStatus = TestISMChannelSetConfig( MenuCom );
      break;

    case ASMN_MENUCODE_SETPWM:
      UARTStatus = TestISMChannelSetPWM( MenuCom );
      break;

    case ASMN_MENUCODE_SETDIR:
      UARTStatus = TestISMChannelSetDirectIO( MenuCom );
      break;

    case ASMN_MENUCODE_RELDIR:
      UARTStatus = TestISMChannelReleaseDirectIO( MenuCom );
      break;

    case ASMN_MENUCODE_SETZPD:
      UARTStatus = TestISMSetZPDConfig( MenuCom );
      break;

    case ASMN_MENUCODE_SETZPDCH:
      UARTStatus = TestISMSetZPDChannel( MenuCom );
      break;

    case ASMN_MENUCODE_ZPDEN:
      UARTStatus = TestISMZPDEnable( MenuCom );
      break;

    case ASMN_MENUCODE_ZPDRESET:
      UARTStatus = TestISMZPDReset( MenuCom );
      break;

    case ASMN_MENUCODE_ZPDSTART:
      UARTStatus = TestISMZPDStart( MenuCom );
      break;

    case ASMN_MENUCODE_ZPDSTATE:
      UARTStatus = TestISMZPDStatus( MenuCom );
      break;

    case ASMN_MENUCODE_SRESET:
      UARTStatus = TestISMSoftReset( MenuCom );
      break;

    case ASMN_MENUCODE_CMEN:
      UARTStatus = TestISMCMEnable( MenuCom );
      break;

    case ASMN_MENUCODE_IEEN:
      UARTStatus = TestISMIntEnable( MenuCom );
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

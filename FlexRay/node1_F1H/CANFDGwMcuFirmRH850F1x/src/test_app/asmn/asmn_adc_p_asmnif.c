//============================================================================
// PROJECT = ASMN Test Monitor
// MODULE  = $Source$
// VERSION = $Revision: 252 $
// DATE    = $Date: 2004-04-07 12:06:18 +0200 (Mi, 07 Apr 2004) $
//============================================================================
//                                 C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2002 by NEC Electronics (Europe) GmbH. All rights reserved.
// Kanzlerstrasse 2
// D-40472 Duesseldorf
// Germany
//============================================================================
//Purpose: A/D Converter Primitive Access Interface
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
// Revision 1.2  2004/04/07 10:06:18  liederr
// Added QMNPUADA82XV1 support.
//
// Revision 1.1  2003/12/11 13:58:45  liederr
// Initial creation.
//
//
//============================================================================

//#include <nec_types.h>
#include <map_asmn_basic.h>
#include <map_device.h>

#ifdef ADC_MACROS

/* ASMN Modules: Main Communication Port */
#if( ASMN_UARTINTERFACE == UARTA_STANDARD )
#include <map_uarta.h>

#elif( ASMN_UARTINTERFACE == UARTC_STANDARD )
#include <map_uartc.h>

#else
#error "ASMN: No Communication Interface Defined"
#endif

/* ADC Driver Interface */
#include <map_adc.h>

/* Basic ASMN Configuration, dependent on device specifics */
#include <map_asmn.h>

#define ASMN_ADPREADTIMEOUT 10000

#define ASMN_MENULINE_HDR1  "A/D CONVERTER TEST MONITOR\n"
#define ASMN_MENULINE_HDR2  "  (C) RL 01/1999    \n\n"
#define ASMN_MENULINE_MEN0  "0 -> Exit\n"

#if( ( ADC_TYPE == QL85EPAD ) ||\
     ( ADC_TYPE == QMNPUADA82XV1 ) ||\
     ( ADC_TYPE == AD_STANDARD ) )
#define ASMN_MENULINE_MEN1  "1 -> Reset\n"
#define ASMN_MENULINE_MEN2  "2 -> Configuration\n"
#define ASMN_MENULINE_MEN3  "3 -> A/D Trigger\n"
#define ASMN_MENULINE_MEN4  "4 -> Read One Channel\n"
#define ASMN_MENULINE_MEN5  "5 -> Read All Channels\n"
#define ASMN_MENULINE_MEN6  "6 -> Status\n"
#endif

#if( ( ADC_TYPE == AD_STANDARD ) ||\
     ( ADC_TYPE == QMNPUADA82XV1 ) )
#define ASMN_MENULINE_MEN7  "7 -> Voltage Surveillance Configuration\n"
#endif

#if( ( ADC_TYPE == QL85EPAD ) ||\
     ( ADC_TYPE == QMNPUADA82XV1 ) ||\
     ( ADC_TYPE == AD_STANDARD ) )
#define ASMN_MENULINE_MEN8  "8 -> Generate Interrupts\n"
#endif

#define ASMN_MENULINE_CMD1  "\nPlease Enter Command: "
#define ASMN_MENULINE_NOCMD "\nILLEGAL COMMAND\n\n"
#define ASMN_MENULINE_OK    "\nOK.\n"
#define ASMN_MENULINE_FAIL  "\nFAILED!!\n"
#define ASMN_MENULINE_IERR  "\nINPUT ERROR\n"

#define ASMN_MENUINPUT_UNIT       "\n Enter Unit: "
#define ASMN_MENUINPUT_POWERSAVE  "\n Enter PowerSave Mode [0=OFF,1=ON]: "
#define ASMN_MENUINPUT_SCAN       "\n Enter Scan Mode [0=SCAN,1=SELECT]: "
#define ASMN_MENUINPUT_POLLING    "\n Enter Polling Mode [0=OFF,1=ON]: "
#define ASMN_MENUINPUT_TRIGGER    "\n Enter Trigger Mode [0=SW,1..=TMR/EXT]: "
#define ASMN_MENUINPUT_TRIGEDGE   "\n Enter Trigger Edge [0=OFF,1=FALL,2=RISE,3=BOTH]: "
#define ASMN_MENUINPUT_BUFFER     "\n Enter Buffer Mode [0=1BUFFER,1=4BUFFER]: "
#define ASMN_MENUINPUT_INTLEVEL   "\n Enter Interrupt Level: [0-7]"
#define ASMN_MENUINPUT_IRQEVERY   "\n Enter Indicator Count Threshold: "
#define ASMN_MENUINPUT_BUFLEN     20
#define ASMN_MENUINPUT_CONMODE    "\n Enter Converter Mode[2=High Speed,1=Low Speed,0=Normal]: "
#define ASMN_MENUINPUT_PFMODE     "\n Enter Power Fail Mode [Bit 7 ON/OFF, Bit 6 Interrupt Generation]: "
#define ASMN_MENUINPUT_PFTHRES    "\n Enter Power Fail Threshold: "
#define ASMN_MENUINPUT_VALEDGE    "\n Enter Power Fail Direction [0=BELOW,1=ABOVE]: "

#define ASMN_MENUINPUT_START      "\n Enter Start Channel [0-13]: "
#define ASMN_MENUINPUT_END        "\n Enter End   Channel [0-13]: "
#define ASMN_MENUINPUT_SAMPLING   "\n Enter Sampling Factor [0-6]: "
#define ASMN_MENUINPUT_CLOCKS     "\n Enter Sampling Clocks [1=10,2=7]: "
#define ASMN_MENUINPUT_CHANNEL    "\n Enter Channel [0-13]: "
#define ASMN_MENUINPUT_VDETENABLE "\n Enter Detection Enable [0=OFF,1=ON]: "
#define ASMN_MENUINPUT_VDETDIR    "\n Enter Detection Direction [0=LOWER,1=HIGHER]: "
#define ASMN_MENUINPUT_VDETREF    "\n Enter Reference Level [12 Bits]: "
#define ASMN_MENUINPUT_IRQTYPE    "\n Enter IRQ Type [0=AD,1=SURV]: "

#define ASMN_MENUOUTPUT_STATUS    "Conversion Status [0=FINISHED,1=ONGOING]: %d\n"

#define ASMN_MENUCODE_EXIT   0
#define ASMN_MENUCODE_RESET  1
#define ASMN_MENUCODE_CONF   2
#define ASMN_MENUCODE_TRIG   3
#define ASMN_MENUCODE_READ1  4
#define ASMN_MENUCODE_READA  5
#define ASMN_MENUCODE_STAT   6
#define ASMN_MENUCODE_VDET   7
#define ASMN_MENUCODE_IRQ    8
#define ASMN_MENUCODE_SCANOK 1
#define ASMN_MENUCODE_NOCMD -1

/*
 * global variables
 */

static unsigned int AD_InterruptCount = 0;

/*
 * interrupt functions
 */

void
TestADIRQNotifier( )
{
  AD_InterruptCount++;
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

#ifdef ASMN_MENULINE_MEN1

unsigned char
TestADReset( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag    = ADC_OK;
  int           UnitNumber     = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  if( SuccessFlag == ASMN_UARTTRANSFEROK ) {
    
    SuccessFlag = ADC_Reset( ( u08 )UnitNumber );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == ADC_OK ) {
    
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

#ifdef ASMN_MENULINE_MEN2

unsigned char
TestADConfiguration( u08 MenuCom )
{
  bit            UARTStatus;
  unsigned char  ScanState;
  bit            SuccessFlag        = ADC_OK;
  int            UnitNumber         = -1;

#if( ( ADC_TYPE == QL85EPAD ) ||\
     ( ADC_TYPE == QMNPUADA82XV1 ) ||\
     ( ADC_TYPE == AD_STANDARD ) )
  int ScanMode           = -1;
  int BufferMode         = -1;
  int EndChannel         = -1;
  int SamplingClocks     = -1;
  int TriggerEdge        = -1;
  int TriggerMode        = -1;
  u08 PScanMode;
  u08 PBufferMode;
  u08 PEndChannel;
  u08 PSamplingClocks;
  u08 PTriggerMode;
  u08 PTriggerEdge;
  u08 PConversionEnable;
#endif

#if( ( ADC_TYPE == AD_STANDARD ) ||\
     ( ADC_TYPE == QMNPUADA82XV1 ) )
  int PollingMode        = -1;
  u08 PPollingMode;
#endif

#if( ADC_TYPE == QMNPUADA82XV1 )
  int ConversionSpeed    = -1;
  u08 PConversionSpeed;
#endif

#if( ADC_TYPE == AD_STANDARD )
  int PowerSaveMode      = -1;
  int StartChannel       = -1;
  int SamplingClocks     = -1;
  int ValidEdge   	     = -1;
  int ConverterMode      = -1;
  int PowerFailMode      = -1;
  int PowerFailThreshold = -1;
  int SamplingTimeFactor = -1;
  u08 PPowerSaveMode;
  u08 PStartChannel;
  u08 PSamplingClocks;
  u08 PValidEdge;
  u08 PConverterMode;
  u08 PPowerFailMode;
  u08 PPowerFailThreshold;
  u08 PSamplingTimeFactor;
#endif   

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;
  
#if( ( ADC_TYPE == QL85EPAD ) )
  SuccessFlag = ADC_GetConfiguration( ( u08 )UnitNumber,
                                      &PConversionEnable,
                                      &PScanMode,
                                      &PBufferMode,         
                                      &PEndChannel,
                                      &PSamplingClocks,
                                      &PTriggerEdge,
                                      &PTriggerMode );
#endif

#if( ( ADC_TYPE == QMNPUADA82XV1 ) )
  SuccessFlag = ADC_GetConfiguration( ( u08 )UnitNumber,
                                      &PConversionEnable,
                                      &PScanMode,
                                      &PPollingMode,
                                      &PBufferMode,         
                                      &PEndChannel,
                                      &PSamplingClocks,
                                      &PConversionSpeed,
                                      &PTriggerMode,
                                      &PTriggerEdge );
#endif

  if( SuccessFlag != ADC_OK ) {
    
    SuccessFlag = ADC_ERROR;
  }
  else {

#if( ( ADC_TYPE == QL85EPAD ) )
    ScanMode           = ( int )PScanMode;
    BufferMode         = ( int )PBufferMode;
    EndChannel         = ( int )PEndChannel;
	SamplingClocks     = ( int )PSamplingClocks;
    TriggerEdge        = ( int )PTriggerEdge;
    TriggerMode        = ( int )PTriggerMode;
#endif

#if( ( ADC_TYPE == QMNPUADA82XV1 ) )
    ScanMode           = ( int )PScanMode;
    PollingMode        = ( int )PPollingMode;
    BufferMode         = ( int )PBufferMode;
    EndChannel         = ( int )PEndChannel;
	SamplingClocks     = ( int )PSamplingClocks;
    ConversionSpeed    = ( int )PConversionSpeed;
    TriggerEdge        = ( int )PTriggerEdge;
    TriggerMode        = ( int )PTriggerMode;
#endif

#if( ( ADC_TYPE == QL85EPAD ) )
    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_SCAN,
                                      &ScanMode,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;
    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_BUFFER,
                                      &BufferMode,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;
    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_END,
                                      &EndChannel,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;
    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_SAMPLING,
                                      &SamplingClocks,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;
    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_TRIGGER,
                                      &TriggerMode,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;
    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_TRIGEDGE,
                                      &TriggerEdge,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;
#endif

#if( ( ADC_TYPE == QMNPUADA82XV1 ) )
    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_SCAN,
                                      &ScanMode,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;
    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_POLLING,
                                      &PollingMode,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;
    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_BUFFER,
                                      &BufferMode,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;
    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_END,
                                      &EndChannel,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;
    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_CONMODE,
                                      &ConversionSpeed,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;
    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_SAMPLING,
                                      &SamplingClocks,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;
    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_TRIGGER,
                                      &TriggerMode,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;
    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_TRIGEDGE,
                                      &TriggerEdge,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;
#endif
  }
    
  if( SuccessFlag == ADC_OK ) {

#if( ( ADC_TYPE == QL85EPAD ) )
    PScanMode           = ( u08 )ScanMode;
    PBufferMode         = ( u08 )BufferMode;
    PEndChannel         = ( u08 )EndChannel;
	PSamplingClocks     = ( u08 )SamplingClocks;
    PTriggerEdge        = ( u08 )TriggerEdge;
    PTriggerMode        = ( u08 )TriggerMode;
#endif

#if( ( ADC_TYPE == QMNPUADA82XV1 ) )
    PScanMode           = ( u08 )ScanMode;
    PPollingMode        = ( u08 )PollingMode;
    PBufferMode         = ( u08 )BufferMode;
    PEndChannel         = ( u08 )EndChannel;
	PSamplingClocks     = ( u08 )SamplingClocks;
    PConversionSpeed    = ( u08 )ConversionSpeed;
    PTriggerEdge        = ( u08 )TriggerEdge;
    PTriggerMode        = ( u08 )TriggerMode;
#endif

#if( ( ADC_TYPE == QL85EPAD ) )
    SuccessFlag = ADC_Configuration( ( u08 )UnitNumber,
                                     PScanMode,
                                     PBufferMode,
                                     PEndChannel,
                                     PSamplingClocks, 
                                     PTriggerEdge,
                                     PTriggerMode );
#endif
#if( ( ADC_TYPE == QMNPUADA82XV1 ) )
    SuccessFlag = ADC_Configuration( ( u08 )UnitNumber,
                                     PScanMode,
                                     PPollingMode,
                                     PBufferMode,
                                     PEndChannel,
                                     PSamplingClocks, 
                                     PConversionSpeed,
                                     PTriggerMode,
                                     PTriggerEdge );
#endif
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == ADC_OK ) {
    
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

#ifdef ASMN_MENULINE_MEN3

unsigned char
TestADTrigger( u08 MenuCom )
{
  bit            UARTStatus;
  unsigned char  ScanState;
  bit            SuccessFlag     = ADC_OK;
  int            UnitNumber      = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ASMN_UARTERROR;

  if( SuccessFlag == ASMN_UARTTRANSFEROK ) {
    
    SuccessFlag = ADC_Trigger( ( u08 )UnitNumber );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == ADC_OK ) {
    
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

#ifdef ASMN_MENULINE_MEN4

unsigned char
TestADGetValue( u08 MenuCom )
{
  bit            UARTStatus;
  unsigned char  ScanState;
  int            ChannelNumber   = -1;
  u16            ChannelValue;
  bit            SuccessFlag     = ADC_OK;
  char           ReadString[ 80 ];
  int            UnitNumber      = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_CHANNEL,
				                    &ChannelNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;

  if( SuccessFlag == ADC_OK ) {
    
    SuccessFlag = ADC_GetValue( ( u08 )UnitNumber,
                                ( u08 )ChannelNumber,
                                ASMN_ADPREADTIMEOUT,
                                &ChannelValue );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
				  ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == ADC_OK ) {
    
    sprintf( ReadString, "\n%04XH\n", ChannelValue );
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

#endif

#ifdef ASMN_MENULINE_MEN5

unsigned char
TestADGetValueArray( u08 MenuCom )
{
  bit            UARTStatus;
  unsigned char  ScanState;
  bit            SuccessFlag     = ADC_OK;
  unsigned int   ChannelCounter;
  u16            ChannelValueArray[ ADC_CHANNELS ];
  char           ReadString[ 80 ];
  int            UnitNumber      = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;

  SuccessFlag = ADC_GetValueArray( ( u08 )UnitNumber,
                                   ASMN_ADPREADTIMEOUT,
                                   ChannelValueArray );
  
  if( SuccessFlag == ADC_OK ) {
    
    for( ChannelCounter = 0;
         ChannelCounter < ADC_CHANNELS;
         ChannelCounter++ ) {

      sprintf( ReadString, "\n%04XH", 
               ( unsigned int )ChannelValueArray[ ChannelCounter ] );

      UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ReadString,
                                        ASMN_UARTMODECRLF );
      if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    }
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, "\n",
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

#ifdef ASMN_MENULINE_MEN6

unsigned char
TestADGetStatus( u08 MenuCom )
{
  bit            UARTStatus;
  unsigned char  ScanState;
  bit            SuccessFlag     = ADC_OK;
  u16            ConversionState;
  char           ReadString[ 80 ];
  int            UnitNumber      = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;

  SuccessFlag = ADC_GetStatus( ( u08 )UnitNumber, &ConversionState );

  if( SuccessFlag == ADC_OK ) {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, "\n",
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    sprintf( ReadString, ASMN_MENUOUTPUT_STATUS, ( unsigned int )ConversionState );
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

#endif

#ifdef ASMN_MENULINE_MEN7

unsigned char
TestADSetVoltageSurveillance( u08 MenuCom )
{
  bit            UARTStatus          = ASMN_UARTTRANSFEROK;
  unsigned char  ScanState;
  bit            SuccessFlag         = ADC_OK;
  int            VoltageDetectEnable = -1;
  int            DetectionDirection  = -1;
  int            ChannelNumber       = -1;
  int            ReferenceValue      = -1;
  int            UnitNumber          = -1;
  u08            PVoltageDetectEnable;
  u08            PDetectionDirection;
  u08            PChannelNumber;
  u16            PReferenceValue;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;
 
  SuccessFlag = ADC_GetVoltageSurveillance( ( u08 )UnitNumber, 
                                            &PVoltageDetectEnable,
                                            &PDetectionDirection,
                                            &PChannelNumber,
                                            &PReferenceValue );
  
  if( SuccessFlag == ADC_OK ) {
    
    VoltageDetectEnable = ( int )PVoltageDetectEnable;
    DetectionDirection  = ( int )PDetectionDirection;
    ChannelNumber       = ( int )PChannelNumber;
    ReferenceValue      = ( int )PReferenceValue;

    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_VDETENABLE,
                                      &VoltageDetectEnable,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;
    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_VDETDIR,
                                      &DetectionDirection,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;
    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_CHANNEL,
                                      &ChannelNumber,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;
    UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                      ASMN_MENUINPUT_VDETREF,
                                      &ReferenceValue,
                                      &ScanState );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
    if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;
  }

  if( SuccessFlag == ADC_OK ) {
    
    PVoltageDetectEnable = ( unsigned short )VoltageDetectEnable;
    PDetectionDirection  = ( unsigned short )DetectionDirection;
    PChannelNumber       = ( unsigned short )ChannelNumber;
    PReferenceValue      = ( unsigned short )ReferenceValue;

    SuccessFlag = ADC_SetVoltageSurveillance( ( u08 )UnitNumber, 
                                              VoltageDetectEnable,
                                              DetectionDirection,
                                              ChannelNumber,
                                              ReferenceValue );
  }
  else {
    
    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == ADC_OK ) {
    
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

#ifdef ASMN_MENULINE_MEN8

unsigned char
TestADInterrupt( u08 MenuCom )
{
  bit           UARTStatus;
  unsigned char ScanState;
  bit           SuccessFlag = ADC_OK;
  u08           DummyByte;
  int           IRQType     = -1;
  int           IntLevel    = -1;
  int           EveryCount  = -1;
  int           UnitNumber  = -1;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
				                    ASMN_MENUINPUT_UNIT,
				                    &UnitNumber,
				                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                    ASMN_MENUINPUT_IRQTYPE,
                                    &IRQType,
                                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;

  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                    ASMN_MENUINPUT_IRQEVERY,
                                    &EveryCount,
                                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;
  
  UARTStatus = ASMN_UARTRECEIVEINT( MenuCom, ASMN_MENUINPUT_BUFLEN,
                                    ASMN_MENUINPUT_INTLEVEL,
                                    &IntLevel,
                                    &ScanState );
  if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  if( ScanState  != ASMN_MENUCODE_SCANOK ) SuccessFlag = ADC_ERROR;

  if( SuccessFlag == ADC_OK ) {

    SuccessFlag = ADC_CreateInterrupt( ( u08 )UnitNumber,
                                       ( u08 )IRQType,
                                       ( u08 )IntLevel,
                                       TestADIRQNotifier );
  }

  else {

    UARTStatus = ASMN_UARTSENDSTRING( MenuCom, ASMN_MENULINE_IERR,
                                      ASMN_UARTMODECRLF );
    if( UARTStatus != ASMN_UARTTRANSFEROK ) return( UARTStatus );
  }

  if( SuccessFlag == ADC_OK ) {

    ASMN_UARTSENDSTRING( MenuCom, "\n", ASMN_UARTMODECRLF );

    do {

      if( AD_InterruptCount >= EveryCount ) {

        AD_InterruptCount = 0;
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

#endif

unsigned char ASMN_ADConverterFunctions( u08 MenuCom )
{
  unsigned char UARTStatus   = ASMN_UARTTRANSFEROK;
  char          MenuCommand  = ASMN_MENUCODE_NOCMD;

  while( ( UARTStatus  == ASMN_UARTTRANSFEROK ) && 
	 ( MenuCommand != ASMN_MENUCODE_EXIT ) ) {

    UARTStatus = DisplayMainMenu( MenuCom, &MenuCommand );

    switch( MenuCommand ) {

    case ASMN_MENUCODE_EXIT: 
      break;
      
#ifdef ASMN_MENULINE_MEN1
    case ASMN_MENUCODE_RESET:
      UARTStatus = TestADReset( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN2
    case ASMN_MENUCODE_CONF:
      UARTStatus = TestADConfiguration( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN3
    case ASMN_MENUCODE_TRIG:
      UARTStatus = TestADTrigger( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN4
    case ASMN_MENUCODE_READ1:
      UARTStatus = TestADGetValue( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN5
    case ASMN_MENUCODE_READA:
      UARTStatus = TestADGetValueArray( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN6
    case ASMN_MENUCODE_STAT:
      UARTStatus = TestADGetStatus( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN7
    case ASMN_MENUCODE_VDET:
      UARTStatus = TestADSetVoltageSurveillance( MenuCom );
      break;
#endif
#ifdef ASMN_MENULINE_MEN8
    case ASMN_MENUCODE_IRQ:
      UARTStatus = TestADInterrupt( MenuCom );
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

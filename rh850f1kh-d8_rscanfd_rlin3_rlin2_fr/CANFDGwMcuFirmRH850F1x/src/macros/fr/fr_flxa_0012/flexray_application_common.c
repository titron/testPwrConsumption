//============================================================================
// PROJECT  : REE FlexRay controller evalutation 
// MODULE   : flexray_application_common.c
// VERSION  : 0.2
// DATE     : 02.05.2014
//============================================================================
//                           C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2014 by REE Electronics (Europe) GmbH. All rights reserved.
// Arcadiastr. 10
// D-40472 Duesseldorf
// Germany
//============================================================================
//
// Warranty Disclaimer :
// Because the Product(s) is licensed free of charge, there is no warranty of
// any kind whatsoever and expressly disclaimed and excluded by REE, either
// expressed or implied, including but not limited to those for non-
// infringement of intellectual property, merchantability and/or fitness for
// the particular purpose. REE shall not have any obligation to maintain,
// service or provide bug fixes for the supplied Product(s) and/or the
// Application.
//
// Each User is solely responsible for determining the appropriateness of
// using the Product(s) and assumes all risks associated with its exercise
// of rights under this Agreement, including, but not limited to the risks
// and costs of program errors, compliance with applicable laws, damage to
// or loss of data, programs or equipment, and unavailability or
// interruption of operations.
//
// Limitation of Liability :
// In no event shall REE be liable to the User for any incidental,
// consequential, indirect, or punitive damage (including but not limited to
// lost profits) regardless of whether such liability is based on breach of
// contract, tort, strict liability, breach of warranties, failure of
// essential purpose or otherwise and even if advised of the possibility of
// such damages. REE shall not be liable for any services or products provided
// by third party vendors, developers or consultants identified or referred
// to the User by REE in connection with the Product(s) and/or the
// Application.
//
//============================================================================
// Enviroment : Devices    : RH850/P1x
//              Assembler  : GHS Multi              Version : 6.1.4
//              C-Compiler : GHS Multi              Version : 6.1.4
//              Linker     : GHS Multi              Version : 6.1.4
//              Debugger   : GHS Multi              Version : 6.1.4
//============================================================================
// Version    Author                       Description
// 0.1        P.Szczupak                   Initial Release
// 0.2        P.Szczupak                   Modified for P1x device
//============================================================================


//============================================================================
// Includes                                                                  
//============================================================================

#include "GlobalDefines.h"
#include "TypeDefines.h"
#include "FrDrv.h"

//============================================================================
// Prototypes
//============================================================================
void ERay_reset( void );
void FrDrv_SW_reset ( void );
void wait_us ( u16 time_u16 );
void wait_ms ( u16 time_u16 );

// from FrDrv_data_transfer.c
extern u16 FrDrv_read_16bit ( u32 addr_u32 );
extern void FrDrv_write_32bit ( u32 addr, u32 data_u32 );
extern void FrDrv_write_32bit ( u32 addr, u32 data_u32 );
// from FrDrv_state.c
extern void FrDrv_Interrupt_clear ( void );
//from flexray_application_1.c
#ifdef Application_1
extern void application_1 ( void );
#endif
#ifdef Application_2
extern void application_2 ( void );
#endif

//============================================================================
// Global variables
//============================================================================
extern u32 eies_reg_u32;
extern u32 sies_reg_u32;

//============================================================================
// Functions
//============================================================================

void ERay_reset( void )
//=============================================================================
// FunctionName: 
// IN :
// OUT :
// Description :
// Version:
//=============================================================================
{
  // SW reset
  FrDrv_SW_reset ( );

  //wait for CLEAR_RAMs finished
  while ( ( FrDrv_read_16bit( SUCC1_REG ) & 0x0080 ) != 0 ); //end of while
}

void FrDrv_SW_reset ( void ) { 
//=============================================================================
// FunctionName: 
// IN :
// OUT :
// Description :
// Version:
//============================================================================= 

#ifdef RH850
  u08 i_u08;

  FrDrv_write_32bit ( CR2_REG, 0x00000001 );//FLXA0FROC.OE=1

  for ( i_u08=0; i_u08 < 5; i_u08++ )
  {
    __nop();
  } // end of for
#endif

#ifdef V850
  u08 i_u08;
  FrDrv_write_32bit ( CR3_REG, 0x67000000 );
  FrDrv_write_32bit ( CR3_REG, 0x98000000 );// clear MD bit
  FrDrv_write_32bit ( CR3_REG, 0x67000000 );
  FrDrv_write_32bit ( CR3_REG, 0x98000001 );// set SR bit


  for ( i_u08=0; i_u08 < 5; i_u08++ )
  {
    __nop();
  } // end of for

  FrDrv_write_32bit ( CR3_REG, 0x67000000 );
  FrDrv_write_32bit ( CR3_REG, 0x98000000 );// clear SR bit
#endif

}

void wait_us ( u16 time_u16 )
//=============================================================================
// FunctionName: 
// IN :
// OUT :
// Description :
// Version:
//=============================================================================  
{
  u32 c_u32;
  for ( c_u32 = 0; c_u32 < ( time_u16 * 6 ); c_u32++ ) {

        __nop();
  } // end of for 
}

void wait_ms ( u16 time_u16 )
//=============================================================================
// FunctionName: 
// IN :
// OUT :
// Description :
// Version:
//=============================================================================  
{
  u32 c_u32;
  for ( c_u32 = 0; c_u32 < ( time_u16 * 6154 ); c_u32++ ) {

        __nop();
  } // end of for 
}


void FR_INTFLX0LINE0(void)//eint0
{
  FrDrv_Interrupt_clear ( );
}


void FR_INTFLX0LINE1(void)//eint1
{
  FrDrv_write_32bit ( EIR_REG, 0xFFFFFFFF );
  FrDrv_write_32bit ( SIR_REG, 0x0000000F );
}



void FR_INTFLX0TIM0(void)//Timer0
{
  #ifdef Application_1
    application_1 (  );
  #endif

  #ifdef Application_2
    application_2 (  );
  #endif
}


void FR_INTFLX0TIM1(void)//Timer1
{

}

void FR_INTFLX0TIM2(void)//Timer2
{

}
// end of file

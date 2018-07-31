//============================================================================
// PROJECT  : REE FlexRay driver
// MODULE   : FrDrv_state.c
// VERSION  : 0.2
// DATE     : 02.10.2013
//============================================================================
//                           C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2013 by REE Electronics (Europe) GmbH. All rights reserved.
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
// Enviroment : Devices    : RH850/P1x-C
//              Assembler  : GHS Multi              Version : 6.1.4
//              C-Compiler : GHS Multi              Version : 6.1.4
//              Linker     : GHS Multi              Version : 6.1.4       
//              Debugger   : GHS Multi              Version : 6.1.4
//============================================================================
// Version    Author                       Description
// 0.1        H.Schmerling                 Initial Release
// 0.2        P.Szczupak                   Modified for P1x-C device
//============================================================================


//============================================================================
// Includes                                                                  
//============================================================================
#define FLEXRAY_VARS
#include "FrDrv.h"
#undef FLEXRAY_VARS


//============================================================================
// Prototypes
//============================================================================
void FrDrv_unlock_seq_CONF ( void );
u08  FrDrv_send_command ( u08 command_u08 );
void FrDrv_EnterConfigMode ( void );
void FrDrv_LeaveConfigMode ( void );
void FrDrv_StartCommunication ( void );
void FrDrv_Start_timer0 ( void );
void FrDrv_Stop_timer0 ( void );
void FrDrv_Start_timer1 ( void );
void FrDrv_Stop_timer1 ( void );
void FrDrv_Interrupt_Line0_enable ( void );
void FrDrv_Interrupt_Line1_enable ( void );
void FrDrv_Interrupt_clear ( void );

#ifdef RH850
void FrDrv_Timer0_Interrupt_enable ( void );
void FrDrv_Timer0_Status_clear     ( void );
void FrDrv_Timer1_Interrupt_enable ( void );
void FrDrv_Timer1_Status_clear     ( void );
void FrDrv_Timer2_Interrupt_enable ( void );
void FrDrv_Timer2_Status_clear     ( void );
#endif


extern void FrDrv_write_32bit ( u32 addr, u32 data_u32 );
extern u32 FrDrv_read_32bit ( u32 addr_u32 );
extern Fr_ReturnType FrDrv_state_1 ( void );
//============================================================================
// Functions
//============================================================================

void FrDrv_unlock_seq_CONF ( void  ) { 
//=============================================================================
// FunctionName: FrDrv_unlock_seq_CONF
// IN: -
// OUT: -
// Description: Unlock sequence for leaving the E-Ray CONFIG state
//============================================================================= 

  //FrDrv_write_16bit ( LCK_REG, 0x00CE );
  //FrDrv_write_16bit ( LCK_REG, 0x0031 );
  //for Xx4 - 32bit
  FrDrv_write_32bit ( LCK_REG, 0x000000CE );
  FrDrv_write_32bit ( LCK_REG, 0x00000031 );
}

u08 FrDrv_send_command ( u08 command_u08) {
//=============================================================================
// FunctionName: FrDrv_send_command
// IN: E-Ray state change command
// OUT: REE FlexRay return value
// Description: Send E-Ray command
//============================================================================= 
  u32 value_u32;
  u08 i_u08 = 0;                                     // count variable

  // check if input buffer busy by the message handler
  while ( ( FrDrv_read_32bit ( SUCC1_REG ) & 0x0080 ) != 0 ) {
       i_u08++;
          if ( i_u08 == 0x80 ) {
              return FLEXRAY_STATUS_BUSY_TIME_OUT;
          } // end of if
  } // end of while

  value_u32 = FrDrv_read_32bit ( SUCC1_REG ) & ~0x000F;
  value_u32 |= command_u08;
  FrDrv_write_32bit ( SUCC1_REG, value_u32 );
  
  return FrDrv_state_1 ( );
}
 
void FrDrv_EnterConfigMode ( void ) {
//=============================================================================
// FunctionName: FrDrv_EnterConfigMode
// IN: -
// OUT: -
// Description : Enter E-Ray config state
//============================================================================= 

  FrDrv_send_command ( CONFIG );
}

void FrDrv_LeaveConfigMode ( void ) {
//=============================================================================
// FunctionName: FrDrv_LeaveConfigMode
// IN: -
// OUT: -
// Description: Leave E-Ray Config State
//============================================================================= 

  FrDrv_unlock_seq_CONF ( );
  FrDrv_send_command ( READY );
}

void FrDrv_StartCommunication ( void ) {
//=============================================================================
// FunctionName: FrDrv_StartCommunication
// IN: -
// OUT: -
// Description: Enter startup state
//============================================================================= 

  FrDrv_send_command ( RUN );
}


void FrDrv_Start_timer0 ( void ) {
//=============================================================================
// FunctionName: FrDrv_Start_timer0
// IN: -
// OUT: -
// Description: Enable timer 1
//============================================================================= 
  u32 value_u32;

  value_u32 = FrDrv_read_32bit ( T0C_REG );
  value_u32 |= 1;
  FrDrv_write_32bit ( T0C_REG, value_u32 );
}

void FrDrv_Stop_timer0 ( void ) {
//=============================================================================
// FunctionName: FrDrv_Stop_timer0
// IN: -
// OUT: -
// Description: Stop timer 0
//============================================================================= 
  u32 value_u32;

  value_u32 = FrDrv_read_32bit ( T0C_REG );
  value_u32 |= 0;
  FrDrv_write_32bit ( T0C_REG, value_u32 );
}

void FrDrv_Start_timer1 ( void ) {
//=============================================================================
// FunctionName: FrDrv_Start_timer1
// IN: -
// OUT: -
// Description: Enable timer 1
//============================================================================= 
  u32 value_u32;

  value_u32 = FrDrv_read_32bit ( T1C_REG );
  value_u32 |= 1;
  FrDrv_write_32bit ( T1C_REG, value_u32 );
}

void FrDrv_Stop_timer1 ( void ) {
//=============================================================================
// FunctionName: FrDrv_Stop_timer1
// IN: -
// OUT: -
// Description: Stop timer 1
//=============================================================================  
  u16 value_u32;

  value_u32 = FrDrv_read_32bit ( T1C_REG );
  value_u32 |= 0;
  FrDrv_write_32bit ( T1C_REG, value_u32 );
}

void FrDrv_Interrupt_Line0_enable ( void ) {
//=============================================================================
// FunctionName: FrDrv_Interrupt_Line0_enable
// IN: -
// OUT: -
// Description: Enable line 0 interrupt
//============================================================================= 
  u32 value_u32;

  value_u32 = FrDrv_read_32bit ( ILE_REG ) & 0x00000003;
  value_u32 |= 1;
  FrDrv_write_32bit ( ILE_REG, value_u32 );
}

void FrDrv_Interrupt_Line1_enable ( void ) {
//=============================================================================
// FunctionName: FrDrv_Interrupt_Line1_enable
// IN: -
// OUT: -
// Description: Enable line 1 interrupt
//============================================================================= 
  u32 value_u32;

  value_u32 = FrDrv_read_32bit ( ILE_REG ) & 0x00000003;
  value_u32 |= 1 << 1;
  FrDrv_write_32bit ( ILE_REG, value_u32 );
}

void FrDrv_Interrupt_clear ( void ) {
//=============================================================================
// FunctionName: FrDrv_Interrupt_clear
// IN: -
// OUT: -
// Description: Cleare/reset interrupt registers
//============================================================================= 

  FrDrv_write_32bit ( EIR_REG, 0xFFFFFFFF );
  FrDrv_write_32bit ( SIR_REG, 0xFFFFFFFF );
}

#ifdef RH850
void FrDrv_Timer0_Interrupt_enable ( void ) {
//=============================================================================
// FunctionName: FrDrv_Timer0_Interrupt_enable
// IN: -
// OUT: -
// Description: Enable timer 0 interrupt
//============================================================================= 
  u32 value_u32;

  value_u32 = FrDrv_read_32bit ( CR2_REG );
  value_u32 |= 0x00010000;
  FrDrv_write_32bit ( CR2_REG, value_u32 );
}

void FrDrv_Timer1_Interrupt_enable ( void ) {
//=============================================================================
// FunctionName: FrDrv_Timer1_Interrupt_enable
// IN: -
// OUT: -
// Description: Enable timer 1 interrupt
//============================================================================= 
  u32 value_u32;

  value_u32 = FrDrv_read_32bit ( CR2_REG );
  value_u32 |= 0x00020000;
  FrDrv_write_32bit ( CR2_REG, value_u32 );
}

void FrDrv_Timer2_Interrupt_enable ( void ) {
//=============================================================================
// FunctionName: FrDrv_Timer2_Interrupt_enable
// IN: -
// OUT: -
// Description: Enable timer 2 interrupt
//============================================================================= 
  u32 value_u32;

  value_u32 = FrDrv_read_32bit ( CR2_REG );
  value_u32 |= 0x00040000;
  FrDrv_write_32bit ( CR2_REG, value_u32 );
}

void FrDrv_Timer0_Status_clear ( void ) {
//=============================================================================
// FunctionName: FrDrv_Timer0_Status_clear
// IN: -
// OUT: -
// Description: Clear timer 0 interrupt status bit
//============================================================================= 
  u32 value_u32;

  value_u32 = FrDrv_read_32bit ( CR4_REG );
  value_u32 |= 0x00010000;
  FrDrv_write_32bit ( CR4_REG, value_u32 );
}

void FrDrv_Timer1_Status_clear ( void ) {
//=============================================================================
// FunctionName: FrDrv_Timer1_Status_clear
// IN: -
// OUT: -
// Description: Clear timer 1 interrupt status bit
//============================================================================= 
  u32 value_u32;

  value_u32 = FrDrv_read_32bit ( CR4_REG );
  value_u32 |= 0x00020000;
  FrDrv_write_32bit ( CR4_REG, value_u32 );
}

void FrDrv_Timer2_Status_clear ( void ) {
//=============================================================================
// FunctionName: FrDrv_Timer2_Status_clear
// IN: -
// OUT: -
// Description: Clear timer 2 interrupt status bit
//============================================================================= 
  u32 value_u32;

  value_u32 = FrDrv_read_32bit ( CR4_REG );
  value_u32 |= 0x00040000;
  FrDrv_write_32bit ( CR4_REG, value_u32 );
}

#endif
// end of file

//============================================================================
// PROJECT = RH850/F1KH-D8
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2017 by Renesas Electronics (EUROPE) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
//============================================================================
//Purpose: RSCAN Interrupt Vectors
//
//Warranty Disclaimer
//
//Because the Product(s) is licensed free of charge, there is no warranty 
//of any kind whatsoever and expressly disclaimed and excluded by Renesas, 
//either expressed or implied, including but not limited to those for 
//non-infringement of intellectual property, merchantability and/or 
//fitness for the particular purpose. 
//Renesas shall not have any obligation to maintain, service or provide bug 
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
//In no event shall Renesas be liable to the User for any incidental, 
//consequential, indirect, or punitive damage (including but not limited 
//to lost profits) regardless of whether such liability is based on breach 
//of contract, tort, strict liability, breach of warranties, failure of 
//essential purpose or otherwise and even if advised of the possibility of 
//such damages. Renesas shall not be liable for any services or products 
//provided by third party vendors, developers or consultants identified or
//referred to the User by Renesas in connection with the Product(s) and/or the 
//Application.
//
//============================================================================
// Environment: Devices:          RH850/F1KH-D8
//              Assembler:        GHS MULTI
//              C-Compiler:       GHS MULTI
//              Linker:           GHS MULTI
//              Debugger:         GHS MULTI
//============================================================================
#include <platform.h>

//#include <rlin2\rlin2_uciaprln\rlin2.h>
#include <rlin2.h>

extern void RLIN2_Interrupt( void );

extern u08 RLIN2_InterruptFlagUnit_u08;
extern u08 RLIN2_InterruptFlagChannel_u08;

#ifndef CSPLUS_PRJ_USED /* GHS project */
__interrupt void INTRLIN20( void );
__interrupt void INTRLIN21( void );
__interrupt void INTRLIN22( void );
__interrupt void INTRLIN23( void );
__interrupt void INTRLIN24( void );
__interrupt void INTRLIN25( void );
__interrupt void INTRLIN26( void );
__interrupt void INTRLIN27( void );
__interrupt void INTRLIN28( void );
__interrupt void INTRLIN29( void );

__interrupt void INTRLIN20( void )
{
  RLIN2_InterruptFlagUnit_u08    = 0;
  RLIN2_InterruptFlagChannel_u08 = 0;
  RLIN2_Interrupt( );
}

__interrupt void INTRLIN21( void )
{
  RLIN2_InterruptFlagUnit_u08    = 0;
  RLIN2_InterruptFlagChannel_u08 = 1;
  RLIN2_Interrupt( );
}

__interrupt void INTRLIN22( void )
{
  RLIN2_InterruptFlagUnit_u08    = 0;
  RLIN2_InterruptFlagChannel_u08 = 2;
  RLIN2_Interrupt( );
}

__interrupt void INTRLIN23( void )
{
  RLIN2_InterruptFlagUnit_u08    = 0;
  RLIN2_InterruptFlagChannel_u08 = 3;
  RLIN2_Interrupt( );
}

__interrupt void INTRLIN24( void )
{
  RLIN2_InterruptFlagUnit_u08    = 1;
  RLIN2_InterruptFlagChannel_u08 = 0;
  RLIN2_Interrupt( );
}

__interrupt void INTRLIN25( void )
{
  RLIN2_InterruptFlagUnit_u08    = 1;
  RLIN2_InterruptFlagChannel_u08 = 1;
  RLIN2_Interrupt( );
}

__interrupt void INTRLIN26( void )
{
  RLIN2_InterruptFlagUnit_u08    = 1;
  RLIN2_InterruptFlagChannel_u08 = 2;
  RLIN2_Interrupt( );
}

__interrupt void INTRLIN27( void )
{
  RLIN2_InterruptFlagUnit_u08    = 1;
  RLIN2_InterruptFlagChannel_u08 = 3;
  RLIN2_Interrupt( );
}
__interrupt void INTRLIN28( void )
{
  RLIN2_InterruptFlagUnit_u08    = 2;
  RLIN2_InterruptFlagChannel_u08 = 0;
  RLIN2_Interrupt( );
}
__interrupt void INTRLIN29( void )
{
  RLIN2_InterruptFlagUnit_u08    = 2;
  RLIN2_InterruptFlagChannel_u08 = 1;
  RLIN2_Interrupt( );
}
#else /* CS+ project */
#pragma section text"comint"
#pragma interrupt INTRLIN20( enable=false , channel=58 , callt=false , fpu=false )
void INTRLIN20( void )
{
  RLIN2_InterruptFlagUnit_u08    = 0;
  RLIN2_InterruptFlagChannel_u08 = 0;
  RLIN2_Interrupt( );
}

#pragma interrupt INTRLIN21( enable=false , channel=59 , callt=false , fpu=false )
void INTRLIN21( void )
{
  RLIN2_InterruptFlagUnit_u08    = 0;
  RLIN2_InterruptFlagChannel_u08 = 1;
  RLIN2_Interrupt( );
}

#pragma interrupt INTRLIN22( enable=false , channel=162 , callt=false , fpu=false )
void INTRLIN22( void )
{
  RLIN2_InterruptFlagUnit_u08    = 0;
  RLIN2_InterruptFlagChannel_u08 = 2;
  RLIN2_Interrupt( );
}

#pragma interrupt INTRLIN23( enable=false , channel=163 , callt=false , fpu=false )
void INTRLIN23( void )
{
  RLIN2_InterruptFlagUnit_u08    = 0;
  RLIN2_InterruptFlagChannel_u08 = 3;
  RLIN2_Interrupt( );
}

#pragma interrupt INTRLIN24( enable=false , channel=226 , callt=false , fpu=false )
void INTRLIN24( void )
{
  RLIN2_InterruptFlagUnit_u08    = 1;
  RLIN2_InterruptFlagChannel_u08 = 0;
  RLIN2_Interrupt( );
}

#pragma interrupt INTRLIN25( enable=false , channel=227 , callt=false , fpu=false )
void INTRLIN25( void )
{
  RLIN2_InterruptFlagUnit_u08    = 1;
  RLIN2_InterruptFlagChannel_u08 = 1;
  RLIN2_Interrupt( );
}

#pragma interrupt INTRLIN26( enable=false , channel=275 , callt=false , fpu=false )
void INTRLIN26( void )
{
  RLIN2_InterruptFlagUnit_u08    = 1;
  RLIN2_InterruptFlagChannel_u08 = 2;
  RLIN2_Interrupt( );
}

#pragma interrupt INTRLIN27( enable=false , channel=276 , callt=false , fpu=false )
void INTRLIN27( void )
{
  RLIN2_InterruptFlagUnit_u08    = 1;
  RLIN2_InterruptFlagChannel_u08 = 3;
  RLIN2_Interrupt( );
}
#pragma interrupt INTRLIN28( enable=false , channel=285 , callt=false , fpu=false )
void INTRLIN28( void )
{
  RLIN2_InterruptFlagUnit_u08    = 2;
  RLIN2_InterruptFlagChannel_u08 = 0;
  RLIN2_Interrupt( );
}
#pragma interrupt INTRLIN29( enable=false , channel=286 , callt=false , fpu=false )
void INTRLIN29( void )
{
  RLIN2_InterruptFlagUnit_u08    = 2;
  RLIN2_InterruptFlagChannel_u08 = 1;
  RLIN2_Interrupt( );
}
#pragma section default
#endif
// End of file

//============================================================================
// PROJECT = RH850/F1KH-S8
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
// Environment: Devices:          RH850/F1KH-S8
//              Assembler:        GHS MULTI
//              C-Compiler:       GHS MULTI
//              Linker:           GHS MULTI
//              Debugger:         GHS MULTI
//============================================================================
#include <platform.h>

//#include <rlin3\rlin3_uciaprln\rlin3.h>
#include <rlin3.h>

extern void RLIN3_IRQ_Common( u08 );
extern void RLIN3_IRQ_Send( u08 );
extern void RLIN3_IRQ_Receive( u08 );
extern void RLIN3_IRQ_Error( u08 );

#ifndef CSPLUS_PRJ_USED /* GHS project */
__interrupt void INTRLIN30( void );
__interrupt void INTRLIN30UR0( void );
__interrupt void INTRLIN30UR1( void );
__interrupt void INTRLIN30UR2( void );

__interrupt void INTRLIN31( void );
__interrupt void INTRLIN31UR0( void );
__interrupt void INTRLIN31UR1( void );
__interrupt void INTRLIN31UR2( void );

__interrupt void INTRLIN32( void );
__interrupt void INTRLIN32UR0( void );
__interrupt void INTRLIN32UR1( void );
__interrupt void INTRLIN32UR2( void );

__interrupt void INTRLIN33( void );
__interrupt void INTRLIN33UR0( void );
__interrupt void INTRLIN33UR1( void );
__interrupt void INTRLIN33UR2( void );

__interrupt void INTRLIN34( void );
__interrupt void INTRLIN34UR0( void );
__interrupt void INTRLIN34UR1( void );
__interrupt void INTRLIN34UR2( void );

__interrupt void INTRLIN35( void );
__interrupt void INTRLIN35UR0( void );
__interrupt void INTRLIN35UR1( void );
__interrupt void INTRLIN35UR2( void );

__interrupt void INTRLIN36( void );
__interrupt void INTRLIN36UR0( void );
__interrupt void INTRLIN36UR1( void );
__interrupt void INTRLIN36UR2( void );

__interrupt void INTRLIN37( void );
__interrupt void INTRLIN37UR0( void );
__interrupt void INTRLIN37UR1( void );
__interrupt void INTRLIN37UR2( void );

__interrupt void INTRLIN30( void )
{
  RLIN3_IRQ_Common( RLIN3_0 );
}

__interrupt void INTRLIN30UR0( void )
{
  RLIN3_IRQ_Send( RLIN3_0 );
}

__interrupt void INTRLIN30UR1( void )
{
  RLIN3_IRQ_Receive( RLIN3_0 );
}

__interrupt void INTRLIN30UR2( void )
{
  RLIN3_IRQ_Error( RLIN3_0 );
}

__interrupt void INTRLIN31( void )
{
  RLIN3_IRQ_Common( RLIN3_1 );
}

__interrupt void INTRLIN31UR0( void )
{
  RLIN3_IRQ_Send( RLIN3_1 );
}

__interrupt void INTRLIN31UR1( void )
{
  RLIN3_IRQ_Receive( RLIN3_1 );
}

__interrupt void INTRLIN31UR2( void )
{
  RLIN3_IRQ_Error( RLIN3_1 );
}

__interrupt void INTRLIN32( void )
{
  RLIN3_IRQ_Common( RLIN3_2 );
}

__interrupt void INTRLIN32UR0( void )
{
  RLIN3_IRQ_Send( RLIN3_2 );
}

__interrupt void INTRLIN32UR1( void )
{
  RLIN3_IRQ_Receive( RLIN3_2 );
}

__interrupt void INTRLIN32UR2( void )
{
  RLIN3_IRQ_Error( RLIN3_2 );
}

__interrupt void INTRLIN33( void )
{
  RLIN3_IRQ_Common( RLIN3_3 );
}

__interrupt void INTRLIN33UR0( void )
{
  RLIN3_IRQ_Send( RLIN3_3 );
}

__interrupt void INTRLIN33UR1( void )
{
  RLIN3_IRQ_Receive( RLIN3_3 );
}

__interrupt void INTRLIN33UR2( void )
{
  RLIN3_IRQ_Error( RLIN3_3 );
}

__interrupt void INTRLIN34( void )
{
  RLIN3_IRQ_Common( RLIN3_4 );
}

__interrupt void INTRLIN34UR0( void )
{
  RLIN3_IRQ_Send( RLIN3_4 );
}

__interrupt void INTRLIN34UR1( void )
{
  RLIN3_IRQ_Receive( RLIN3_4 );
}

__interrupt void INTRLIN34UR2( void )
{
  RLIN3_IRQ_Error( RLIN3_4 );
}

__interrupt void INTRLIN35( void )
{
  RLIN3_IRQ_Common( RLIN3_5 );
}

__interrupt void INTRLIN35UR0( void )
{
  RLIN3_IRQ_Send( RLIN3_5 );
}

__interrupt void INTRLIN35UR1( void )
{
  RLIN3_IRQ_Receive( RLIN3_5 );
}

__interrupt void INTRLIN35UR2( void )
{
  RLIN3_IRQ_Error( RLIN3_5 );
}

__interrupt void INTRLIN36( void )
{
  RLIN3_IRQ_Common( RLIN3_6 );
}

__interrupt void INTRLIN36UR0( void )
{
  RLIN3_IRQ_Send( RLIN3_6 );
}

__interrupt void INTRLIN36UR1( void )
{
  RLIN3_IRQ_Receive( RLIN3_6 );
}

__interrupt void INTRLIN36UR2( void )
{
  RLIN3_IRQ_Error( RLIN3_6 );
}

__interrupt void INTRLIN37( void )
{
  RLIN3_IRQ_Common( RLIN3_7 );
}

__interrupt void INTRLIN37UR0( void )
{
  RLIN3_IRQ_Send( RLIN3_7 );
}

__interrupt void INTRLIN37UR1( void )
{
  RLIN3_IRQ_Receive( RLIN3_7 );
}

__interrupt void INTRLIN37UR2( void )
{
  RLIN3_IRQ_Error( RLIN3_7 );
}
#else /* CS+ project */
#pragma section text"comint"
#pragma interrupt INTRLIN30( enable=false , channel=33 , callt=false , fpu=false )
void INTRLIN30( void )
{
  RLIN3_IRQ_Common( RLIN3_0 );
}

#pragma interrupt INTRLIN30UR0( enable=false , channel=34 , callt=false , fpu=false )
void INTRLIN30UR0( void )
{
  RLIN3_IRQ_Send( RLIN3_0 );
}

#pragma interrupt INTRLIN30UR1( enable=false , channel=35 , callt=false , fpu=false )
void INTRLIN30UR1( void )
{
  RLIN3_IRQ_Receive( RLIN3_0 );
}

#pragma interrupt INTRLIN30UR2( enable=false , channel=36 , callt=false , fpu=false )
void INTRLIN30UR2( void )
{
  RLIN3_IRQ_Error( RLIN3_0 );
}

#pragma interrupt INTRLIN31( enable=false , channel=120 , callt=false , fpu=false )
void INTRLIN31( void )
{
  RLIN3_IRQ_Common( RLIN3_1 );
}

#pragma interrupt INTRLIN31UR0( enable=false , channel=121 , callt=false , fpu=false )
void INTRLIN31UR0( void )
{
  RLIN3_IRQ_Send( RLIN3_1 );
}

#pragma interrupt INTRLIN31UR1( enable=false , channel=122 , callt=false , fpu=false )
void INTRLIN31UR1( void )
{
  RLIN3_IRQ_Receive( RLIN3_1 );
}

#pragma interrupt INTRLIN31UR2( enable=false , channel=123 , callt=false , fpu=false )
void INTRLIN31UR2( void )
{
  RLIN3_IRQ_Error( RLIN3_1 );
}

#pragma interrupt INTRLIN32( enable=false , channel=164 , callt=false , fpu=false )
void INTRLIN32( void )
{
  RLIN3_IRQ_Common( RLIN3_2 );
}

#pragma interrupt INTRLIN32UR0( enable=false , channel=165 , callt=false , fpu=false )
void INTRLIN32UR0( void )
{
  RLIN3_IRQ_Send( RLIN3_2 );
}

#pragma interrupt INTRLIN32UR1( enable=false , channel=166 , callt=false , fpu=false )
void INTRLIN32UR1( void )
{
  RLIN3_IRQ_Receive( RLIN3_2 );
}

#pragma interrupt INTRLIN32UR2( enable=false , channel=167 , callt=false , fpu=false )
void INTRLIN32UR2( void )
{
  RLIN3_IRQ_Error( RLIN3_2 );
}

#pragma interrupt INTRLIN33( enable=false , channel=228 , callt=false , fpu=false )
void INTRLIN33( void )
{
  RLIN3_IRQ_Common( RLIN3_3 );
}

#pragma interrupt INTRLIN33UR0( enable=false , channel=229 , callt=false , fpu=false )
void INTRLIN33UR0( void )
{
  RLIN3_IRQ_Send( RLIN3_3 );
}

#pragma interrupt INTRLIN33UR1( enable=false , channel=230 , callt=false , fpu=false )
void INTRLIN33UR1( void )
{
  RLIN3_IRQ_Receive( RLIN3_3 );
}

#pragma interrupt INTRLIN33UR2( enable=false , channel=231 , callt=false , fpu=false )
void INTRLIN33UR2( void )
{
  RLIN3_IRQ_Error( RLIN3_3 );
}

#pragma interrupt INTRLIN34( enable=false , channel=232 , callt=false , fpu=false )
void INTRLIN34( void )
{
  RLIN3_IRQ_Common( RLIN3_4 );
}

#pragma interrupt INTRLIN34UR0( enable=false , channel=233 , callt=false , fpu=false )
void INTRLIN34UR0( void )
{
  RLIN3_IRQ_Send( RLIN3_4 );
}

#pragma interrupt INTRLIN34UR1( enable=false , channel=234 , callt=false , fpu=false )
void INTRLIN34UR1( void )
{
  RLIN3_IRQ_Receive( RLIN3_4 );
}

#pragma interrupt INTRLIN34UR2( enable=false , channel=235 , callt=false , fpu=false )
void INTRLIN34UR2( void )
{
  RLIN3_IRQ_Error( RLIN3_4 );
}

#pragma interrupt INTRLIN35( enable=false , channel=236 , callt=false , fpu=false )
void INTRLIN35( void )
{
  RLIN3_IRQ_Common( RLIN3_5 );
}

#pragma interrupt INTRLIN35UR0( enable=false , channel=237 , callt=false , fpu=false )
void INTRLIN35UR0( void )
{
  RLIN3_IRQ_Send( RLIN3_5 );
}

#pragma interrupt INTRLIN35UR1( enable=false , channel=238 , callt=false , fpu=false )
void INTRLIN35UR1( void )
{
  RLIN3_IRQ_Receive( RLIN3_5 );
}

#pragma interrupt INTRLIN35UR2( enable=false , channel=239 , callt=false , fpu=false )
void INTRLIN35UR2( void )
{
  RLIN3_IRQ_Error( RLIN3_5 );
}

//#pragma interrupt INTRLIN36( enable=false , channel=58 , callt=false , fpu=false )
//void INTRLIN36( void )
//{
//  RLIN3_IRQ_Common( RLIN3_6 );
//}
//
//#pragma interrupt INTRLIN36UR0( enable=false , channel=58 , callt=false , fpu=false )
//void INTRLIN36UR0( void )
//{
//  RLIN3_IRQ_Send( RLIN3_6 );
//}
//
//#pragma interrupt INTRLIN36UR1( enable=false , channel=58 , callt=false , fpu=false )
//void INTRLIN36UR1( void )
//{
//  RLIN3_IRQ_Receive( RLIN3_6 );
//}
//
//#pragma interrupt INTRLIN36UR2( enable=false , channel=58 , callt=false , fpu=false )
//void INTRLIN36UR2( void )
//{
//  RLIN3_IRQ_Error( RLIN3_6 );
//}
//
//#pragma interrupt INTRLIN37( enable=false , channel=58 , callt=false , fpu=false )
//void INTRLIN37( void )
//{
//  RLIN3_IRQ_Common( RLIN3_7 );
//}
//
//#pragma interrupt INTRLIN37UR0( enable=false , channel=58 , callt=false , fpu=false )
//void INTRLIN37UR0( void )
//{
//  RLIN3_IRQ_Send( RLIN3_7 );
//}
//
//#pragma interrupt INTRLIN37UR1( enable=false , channel=58 , callt=false , fpu=false )
//void INTRLIN37UR1( void )
//{
//  RLIN3_IRQ_Receive( RLIN3_7 );
//}
//
//#pragma interrupt INTRLIN37UR2( enable=false , channel=58 , callt=false , fpu=false )
//void INTRLIN37UR2( void )
//{
//  RLIN3_IRQ_Error( RLIN3_7 );
//}
#pragma section default
#endif
// End of file

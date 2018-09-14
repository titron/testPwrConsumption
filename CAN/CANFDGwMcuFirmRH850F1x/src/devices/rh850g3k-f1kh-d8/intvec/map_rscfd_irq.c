//============================================================================
// PROJECT = RH850/F1KH-D8
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2017 by Renesas Electronics (EUROPE) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
//============================================================================
//Purpose: RSCFD Interrupt Vectors
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

//#include <rscanfd\rscanfd_uciaprcn_v3\rscfd.h>
#include <rscfd.h>

extern u08 EE_RSCFD_InterruptFlag_Unit_u08;
extern u08 EE_RSCFD_InterruptFlag_Global_u08;
extern u08 EE_RSCFD_InterruptFlag_Channel0_u08;
extern u08 EE_RSCFD_InterruptFlag_Channel1_u08;
extern u08 EE_RSCFD_InterruptFlag_Channel2_u08;
extern u08 EE_RSCFD_InterruptFlag_Channel3_u08;
extern u08 EE_RSCFD_InterruptFlag_Channel4_u08;
extern u08 EE_RSCFD_InterruptFlag_Channel5_u08;
extern u08 EE_RSCFD_InterruptFlag_Channel6_u08;
extern u08 EE_RSCFD_InterruptFlag_Channel7_u08;

extern void EE_RSCFD_Interrupt( void );

#ifndef CSPLUS_PRJ_USED /* GHS project */
__interrupt void INTRCAN0ERR( void );
__interrupt void INTRCAN0REC( void );
__interrupt void INTRCAN0TRX( void );

__interrupt void INTRCAN1ERR( void );
__interrupt void INTRCAN1REC( void );
__interrupt void INTRCAN1TRX( void );

__interrupt void INTRCAN2ERR( void );
__interrupt void INTRCAN2REC( void );
__interrupt void INTRCAN2TRX( void );

__interrupt void INTRCAN3ERR( void );
__interrupt void INTRCAN3REC( void );
__interrupt void INTRCAN3TRX( void );

__interrupt void INTRCAN4ERR( void );
__interrupt void INTRCAN4REC( void );
__interrupt void INTRCAN4TRX( void );

__interrupt void INTRCAN5ERR( void );
__interrupt void INTRCAN5REC( void );
__interrupt void INTRCAN5TRX( void );

__interrupt void INTRCAN6ERR( void );
__interrupt void INTRCAN6REC( void );
__interrupt void INTRCAN6TRX( void );

__interrupt void INTRCAN7ERR( void );
__interrupt void INTRCAN7REC( void );
__interrupt void INTRCAN7TRX( void );

__interrupt void INTRCANGERR0( void );
__interrupt void INTRCANGRECC0( void );

__interrupt void INTRCAN0ERR( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel0_u08 = EE_RSCFD_INT_CERR;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN0REC( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel0_u08 = EE_RSCFD_INT_RXCF;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN0TRX( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel0_u08 = EE_RSCFD_INT_TX;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN1ERR( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel1_u08 = EE_RSCFD_INT_CERR;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN1REC( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel1_u08 = EE_RSCFD_INT_RXCF;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN1TRX( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel1_u08 = EE_RSCFD_INT_TX;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN2ERR( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel2_u08 = EE_RSCFD_INT_CERR;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN2REC( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel2_u08 = EE_RSCFD_INT_RXCF;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN2TRX( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel2_u08 = EE_RSCFD_INT_TX;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN3ERR( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel3_u08 = EE_RSCFD_INT_CERR;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN3REC( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel3_u08 = EE_RSCFD_INT_RXCF;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN3TRX( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel3_u08 = EE_RSCFD_INT_TX;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN4ERR( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel4_u08 = EE_RSCFD_INT_CERR;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN4REC( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel4_u08 = EE_RSCFD_INT_RXCF;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN4TRX( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel4_u08 = EE_RSCFD_INT_TX;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN5ERR( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel5_u08 = EE_RSCFD_INT_CERR;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN5REC( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel5_u08 = EE_RSCFD_INT_RXCF;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN5TRX( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel5_u08 = EE_RSCFD_INT_TX;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN6ERR( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel6_u08 = EE_RSCFD_INT_CERR;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN6REC( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel6_u08 = EE_RSCFD_INT_RXCF;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN6TRX( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel6_u08 = EE_RSCFD_INT_TX;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN7ERR( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel7_u08 = EE_RSCFD_INT_CERR;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN7REC( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel7_u08 = EE_RSCFD_INT_RXCF;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCAN7TRX( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel7_u08 = EE_RSCFD_INT_TX;
  EE_RSCFD_Interrupt( );
}


__interrupt void INTRCANGERR0( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Global_u08 = EE_RSCFD_INT_GERR;
  EE_RSCFD_Interrupt( );
}

__interrupt void INTRCANGRECC0( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Global_u08 = EE_RSCFD_INT_RXF0;
  EE_RSCFD_Interrupt( );
}
#else /* CS+ project */
#pragma section text"comint"

#pragma interrupt INTRCANGERR0( enable=false , channel=22 , callt=false , fpu=false )
void INTRCANGERR0( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Global_u08 = EE_RSCFD_INT_GERR;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCANGRECC0( enable=false , channel=23 , callt=false , fpu=false )
void INTRCANGRECC0( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Global_u08 = EE_RSCFD_INT_RXF0;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN0ERR( enable=false , channel=24 , callt=false , fpu=false )
void INTRCAN0ERR( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel0_u08 = EE_RSCFD_INT_CERR;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN0REC( enable=false , channel=25 , callt=false , fpu=false )
void INTRCAN0REC( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel0_u08 = EE_RSCFD_INT_RXCF;
  EE_RSCFD_Interrupt( );

  /* Read received message */
  /* Transmit the received message */
}

#pragma interrupt INTRCAN0TRX( enable=false , channel=26 , callt=false , fpu=false )
void INTRCAN0TRX( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel0_u08 = EE_RSCFD_INT_TX;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN1ERR( enable=false , channel=113 , callt=false , fpu=false )
void INTRCAN1ERR( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel1_u08 = EE_RSCFD_INT_CERR;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN1REC( enable=false , channel=114 , callt=false , fpu=false )
void INTRCAN1REC( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel1_u08 = EE_RSCFD_INT_RXCF;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN1TRX( enable=false , channel=115 , callt=false , fpu=false )
void INTRCAN1TRX( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel1_u08 = EE_RSCFD_INT_TX;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN2ERR( enable=false , channel=217 , callt=false , fpu=false )
void INTRCAN2ERR( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel2_u08 = EE_RSCFD_INT_CERR;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN2REC( enable=false , channel=218 , callt=false , fpu=false )
void INTRCAN2REC( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel2_u08 = EE_RSCFD_INT_RXCF;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN2TRX( enable=false , channel=219 , callt=false , fpu=false )
void INTRCAN2TRX( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel2_u08 = EE_RSCFD_INT_TX;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN3ERR( enable=false , channel=220 , callt=false , fpu=false )
void INTRCAN3ERR( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel3_u08 = EE_RSCFD_INT_CERR;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN3REC( enable=false , channel=221 , callt=false , fpu=false )
void INTRCAN3REC( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel3_u08 = EE_RSCFD_INT_RXCF;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN3TRX( enable=false , channel=222 , callt=false , fpu=false )
void INTRCAN3TRX( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel3_u08 = EE_RSCFD_INT_TX;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN4ERR( enable=false , channel=272 , callt=false , fpu=false )
void INTRCAN4ERR( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel4_u08 = EE_RSCFD_INT_CERR;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN4REC( enable=false , channel=273 , callt=false , fpu=false )
void INTRCAN4REC( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel4_u08 = EE_RSCFD_INT_RXCF;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN4TRX( enable=false , channel=274 , callt=false , fpu=false )
void INTRCAN4TRX( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel4_u08 = EE_RSCFD_INT_TX;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN5ERR( enable=false , channel=287 , callt=false , fpu=false )
void INTRCAN5ERR( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel5_u08 = EE_RSCFD_INT_CERR;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN5REC( enable=false , channel=288 , callt=false , fpu=false )
void INTRCAN5REC( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel5_u08 = EE_RSCFD_INT_RXCF;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN5TRX( enable=false , channel=289 , callt=false , fpu=false )
void INTRCAN5TRX( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel5_u08 = EE_RSCFD_INT_TX;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN6ERR( enable=false , channel=321 , callt=false , fpu=false )
void INTRCAN6ERR( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel6_u08 = EE_RSCFD_INT_CERR;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN6REC( enable=false , channel=322 , callt=false , fpu=false )
void INTRCAN6REC( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel6_u08 = EE_RSCFD_INT_RXCF;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN6TRX( enable=false , channel=323 , callt=false , fpu=false )
void INTRCAN6TRX( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel6_u08 = EE_RSCFD_INT_TX;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN7ERR( enable=false , channel=332 , callt=false , fpu=false )
void INTRCAN7ERR( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel7_u08 = EE_RSCFD_INT_CERR;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN7REC( enable=false , channel=333 , callt=false , fpu=false )
void INTRCAN7REC( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel7_u08 = EE_RSCFD_INT_RXCF;
  EE_RSCFD_Interrupt( );
}

#pragma interrupt INTRCAN7TRX( enable=false , channel=334 , callt=false , fpu=false )
void INTRCAN7TRX( void )
{
  EE_RSCFD_InterruptFlag_Unit_u08 = 0;
  EE_RSCFD_InterruptFlag_Channel7_u08 = EE_RSCFD_INT_TX;
  EE_RSCFD_Interrupt( );
}


#pragma section default
#endif
//End of file

//============================================================================
// PROJECT = RH850/P1x-C
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2017 by Renesas Electronics (EUROPE) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
//============================================================================
//Purpose: FlexRay Interrupt Vectors
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
// Environment: Devices:          RH850/P1M-C (D3)
//              Assembler:        GHS MULTI
//              C-Compiler:       GHS MULTI
//              Linker:           GHS MULTI
//              Debugger:         GHS MULTI
//============================================================================
#include <platform.h>

extern void FR_INTFLX0LINE0( void );
extern void FR_INTFLX0LINE1( void );
extern void FR_INTFLX0TIM0 ( void );
extern void FR_INTFLX0TIM1 ( void );
extern void FR_INTFLX0TIM2 ( void );

#ifndef CSPLUS_PRJ_USED /* GHS project */
__interrupt void INTFLXA0LINE0( void );
__interrupt void INTFLXA0LINE1( void );
__interrupt void INTFLXA0TIM0 ( void );
__interrupt void INTFLXA0TIM1 ( void );
__interrupt void INTFLXA0TIM2 ( void );

__interrupt void INTFLXA0LINE0(void)//eint0
{
  FR_INTFLX0LINE0( );
}

__interrupt void INTFLXA0LINE1(void)//eint1
{
  FR_INTFLX0LINE1( );
}

__interrupt void INTFLXA0TIM0(void)//Timer0
{
  FR_INTFLX0TIM0( );
}

__interrupt void INTFLXA0TIM1(void)//Timer1
{
  FR_INTFLX0TIM1( );
}

__interrupt void INTFLXA0TIM2(void)//Timer2
{
  FR_INTFLX0TIM2( );
}
#else /* CS+ project */
#pragma section text"comint"
#pragma interrupt INTFLXA0LINE0( enable=false , channel=179 , callt=false , fpu=false )
void INTFLXA0LINE0(void)//eint0
{
  FR_INTFLX0LINE0( );
}

#pragma interrupt INTFLXA0LINE1( enable=false , channel=180 , callt=false , fpu=false )
void INTFLXA0LINE1(void)//eint1
{
  FR_INTFLX0LINE1( );
}

#pragma interrupt INTFLXA0TIM0( enable=false , channel=181 , callt=false , fpu=false )
void INTFLXA0TIM0(void)//Timer0
{
  FR_INTFLX0TIM0( );
}

#pragma interrupt INTFLXA0TIM1( enable=false , channel=182 , callt=false , fpu=false )
void INTFLXA0TIM1(void)//Timer1
{
  FR_INTFLX0TIM1( );
}

#pragma interrupt INTFLXA0TIM2( enable=false , channel=183 , callt=false , fpu=false )
void INTFLXA0TIM2(void)//Timer2
{
  FR_INTFLX0TIM2( );
}
#pragma section default
#endif

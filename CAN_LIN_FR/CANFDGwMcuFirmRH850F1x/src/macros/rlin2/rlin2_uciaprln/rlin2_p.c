//============================================================================
// PROJECT = RSCAN Type RLIN2_UCIAPRLN
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2014 by Renesas Electronics (EUROPE) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
//============================================================================
//Purpose: RLIN2 Low Level Driver
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
// Environment: Devices:          All featuring RLIN2_UCIAPRLN
//              Assembler:        GHS MULTI
//              C-Compiler:       GHS MULTI
//              Linker:           GHS MULTI
//              Debugger:         GHS MULTI
//============================================================================

#define DRIVER_LOCAL

#include <ree_types.h>

#include <map_rlin2.h>
#include <map_ports.h>
//#include <ports\standardports\standardports_p.h>
#include <standardports_p.h>

#include <stddef.h>

#if( RLIN2_MACROS > RLIN2_MAXMACROS )
#error "NUMBER OF CHANNELS OR UNITS NOT SUPPORTED"
#endif

#ifdef RLIN2_INT_BUNDLINGHOOK
extern void RLIN2_INT_BUNDLINGHOOK( u08*, u08*, u08* );
#endif

/*
 * CreateInterrupt() Jump Vector Table
 */
 
void RLIN2_IRQDefault( void );

static void ( *RLIN2_CIVector [ RLIN2_MAXMACROS ][ RLIN2_MAXCHANNELS ][ RLIN2_INTERRUPTS ] )( ) =
{
  {
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault },
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault },
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault },
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault }
  },
  {
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault },
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault },
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault },
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault }
  },
  {
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault },
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault },
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault },
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault }
  },
  {
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault },
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault },
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault },
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault }
  },
  {
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault },
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault },
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault },
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault }
  },
  {
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault },
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault },
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault },
    { RLIN2_IRQDefault, RLIN2_IRQDefault, RLIN2_IRQDefault }
  }
};

/*
 * Global Variables 
 */

u08 RLIN2_InterruptFlagType_u08    = RLIN2_IRQ_NOINT;  /* interrupt resolution */
u08 RLIN2_InterruptFlagChannel_u08 = RLIN2_IRQ_NOINT;
u08 RLIN2_InterruptFlagUnit_u08    = RLIN2_IRQ_NOINT;


/*
 * Common Interrupt Vector
 */

void RLIN2_Interrupt( void )
{
#ifdef RLIN2_INT_BUNDLINGHOOK

  RLIN2_INT_BUNDLINGHOOK( &RLIN2_InterruptFlagUnit_u08,
                          &RLIN2_InterruptFlagChannel_u08,
                          &RLIN2_InterruptFlagType_u08 );
#endif

  RLIN2_CIVector[ RLIN2_InterruptFlagUnit_u08 ]
                [ RLIN2_InterruptFlagChannel_u08 ]
                [ RLIN2_InterruptFlagType_u08 ]( );
}

/*
 * Local Functions
 */

void RLIN2_IRQDefault( void )
{
}


/*
 * The peripheral support Functions
 */

bit RLIN2_CreateInterrupt( u08 UnitNumber_u08,
                           u08 ChannelNumber_u08,
                           u08 InterruptSource_u08,
                           u08 InterruptLevel_u08,
                           void ( *FunctionVector )( ) )
{
  switch( UnitNumber_u08 )
  {
    case RLIN2_0:
      switch( ChannelNumber_u08 )
      {
        case RLIN2_CHANNEL_0:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM0C0TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM0C0TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM0C0RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM0C0RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM0C0ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM0C0ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;

        case RLIN2_CHANNEL_1:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM0C1TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM0C1TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM0C1RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM0C1RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM0C1ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM0C1ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;

        case RLIN2_CHANNEL_2:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM0C2TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM0C2TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM0C2RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM0C2RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM0C2ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM0C2ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;

        case RLIN2_CHANNEL_3:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM0C2TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM0C3TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM0C3RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM0C3RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM0C3ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM0C3ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;
      } // end switch( ChannelNumber )
      break;
      
    case RLIN2_1:
      switch( ChannelNumber_u08 )
      {
        case RLIN2_CHANNEL_0:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM1C0TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM1C0TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM1C0RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM1C0RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM1C0ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM1C0ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;

        case RLIN2_CHANNEL_1:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM1C1TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM1C1TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM1C1RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM1C1RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM1C1ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM1C1ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;

        case RLIN2_CHANNEL_2:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM1C2TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM1C2TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM1C2RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM1C2RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM1C2ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM1C2ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;

        case RLIN2_CHANNEL_3:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM1C3TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM1C3TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM1C3RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM1C3RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM1C3ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM1C3ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;
      } // end switch( ChannelNumber )
      break;

    case RLIN2_2:
      switch( ChannelNumber_u08 )
      {
        case RLIN2_CHANNEL_0:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM2C0TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM2C0TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM2C0RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM2C0RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM2C0ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM2C0ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;

        case RLIN2_CHANNEL_1:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM2C1TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM2C1TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM2C1RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM2C1RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM2C1ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM2C1ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;

        case RLIN2_CHANNEL_2:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM2C2TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM2C2TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM2C2RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM2C2RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM2C2ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM2C2ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;

        case RLIN2_CHANNEL_3:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM2C3TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM2C3TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM2C3RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM2C3RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM2C3ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM2C3ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;
      } // end switch( ChannelNumber )
      break;

    case RLIN2_3:
      switch( ChannelNumber_u08 )
      {
        case RLIN2_CHANNEL_0:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM3C0TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM3C0TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM3C0RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM3C0RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM3C0ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM3C0ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;

        case RLIN2_CHANNEL_1:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM3C1TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM3C1TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM3C1RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM3C1RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM3C1ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM3C1ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;

        case RLIN2_CHANNEL_2:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM3C2TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM3C2TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM3C2RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM3C2RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM3C2ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM3C2ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;

        case RLIN2_CHANNEL_3:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM3C3TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM3C3TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM3C3RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM3C3RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM3C3ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM3C3ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;
      } // end switch( ChannelNumber )
      break;

    case RLIN2_4:
      switch( ChannelNumber_u08 )
      {
        case RLIN2_CHANNEL_0:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM4C0TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM4C0TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM4C0RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM4C0RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM4C0ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM4C0ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;

        case RLIN2_CHANNEL_1:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM4C1TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM4C1TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM4C1RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM4C1RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM4C1ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM4C1ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;

        case RLIN2_CHANNEL_2:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM4C2TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM4C2TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM4C2RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM4C2RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM4C2ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM4C2ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;

        case RLIN2_CHANNEL_3:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM4C3TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM4C3TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM4C3RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM4C3RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM4C3ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM4C3ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;
      } // end switch( ChannelNumber )
      break;

    case RLIN2_5:
      switch( ChannelNumber_u08 )
      {
        case RLIN2_CHANNEL_0:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM5C0TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM5C0TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM5C0RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM5C0RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM5C0ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM5C0ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;

        case RLIN2_CHANNEL_1:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM5C1TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM5C1TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM5C1RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM5C1RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM5C1ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM5C1ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;

        case RLIN2_CHANNEL_2:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM5C2TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM5C2TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM5C2RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM5C2RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM5C2ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM5C2ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;

        case RLIN2_CHANNEL_3:
        switch( InterruptSource_u08 )
        {
#ifdef RLIN2_INTM5C3TX
          case RLIN2_IRQ_SEND:
            RLIN2_INTM5C3TX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM5C3RX
          case RLIN2_IRQ_RECEIVE:
            RLIN2_INTM5C3RX = ( FunctionVector == NULL ? 
                                RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
#ifdef RLIN2_INTM5C3ERR
          case RLIN2_IRQ_ERROR:
            RLIN2_INTM5C3ERR = ( FunctionVector == NULL ? 
                                 RLIN2_INTCLEAR : InterruptLevel_u08 );
            break;
#endif
          default: return( RLIN2_ERROR );
        } // end switch( InterruptSource )
        break;
      } // end switch( ChannelNumber )
      break;
  } // end switch ( UnitNumber )  
  
  if( FunctionVector == NULL ) FunctionVector = RLIN2_IRQDefault;
  
  RLIN2_CIVector[ UnitNumber_u08 ][ ChannelNumber_u08 ][ InterruptSource_u08 ] = 
    FunctionVector;
  
  return( RLIN2_OK );
}

bit RLIN2_PortEnable( u08 UnitNumber_u08,
                      u08 ChannelNumber_u08 )
{
  switch( UnitNumber_u08 ) 
  {

    case RLIN2_0:
      switch( ChannelNumber_u08 )
      {
#ifdef RLIN2_PORT_M0RX0
        case RLIN2_CHANNEL_0:
          PORT_Enable( RLIN2_PORT_M0RX0, RLIN2_PORT_BIT_M0RX0,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M0RX0 );
          PORT_Enable( RLIN2_PORT_M0TX0, RLIN2_PORT_BIT_M0TX0,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M0TX0 );
          break;
#endif                     

#ifdef RLIN2_PORT_M0RX1
        case RLIN2_CHANNEL_1:
          PORT_Enable( RLIN2_PORT_M0RX1, RLIN2_PORT_BIT_M0RX1,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M0RX1 );
          PORT_Enable( RLIN2_PORT_M0TX1, RLIN2_PORT_BIT_M0TX1,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M0TX1 );
          break;
#endif                     

#ifdef RLIN2_PORT_M0RX2
        case RLIN2_CHANNEL_2:
          PORT_Enable( RLIN2_PORT_M0RX2, RLIN2_PORT_BIT_M0RX2,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M0RX2 );
          PORT_Enable( RLIN2_PORT_M0TX2, RLIN2_PORT_BIT_M0TX2,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M0TX2 );
          break;
#endif                     

//#ifdef RLIN2_PORT_M0RX2
#ifdef RLIN2_PORT_M0RX3
        case RLIN2_CHANNEL_3:
          PORT_Enable( RLIN2_PORT_M0RX3, RLIN2_PORT_BIT_M0RX3,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M0RX3 );
          PORT_Enable( RLIN2_PORT_M0TX3, RLIN2_PORT_BIT_M0TX3,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M0TX3 );
          break;
#endif                     
        default:
          return( RLIN2_ERROR );
      }
      break;
        
    case RLIN2_1:
      switch( ChannelNumber_u08 )
      {
#ifdef RLIN2_PORT_M1RX0
        case RLIN2_CHANNEL_0:
          PORT_Enable( RLIN2_PORT_M1RX0, RLIN2_PORT_BIT_M1RX0,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M1RX0 );
          PORT_Enable( RLIN2_PORT_M1TX0, RLIN2_PORT_BIT_M1TX0,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M1TX0 );
          break;
#endif                     

#ifdef RLIN2_PORT_M1RX1
        case RLIN2_CHANNEL_1:
          PORT_Enable( RLIN2_PORT_M1RX1, RLIN2_PORT_BIT_M1RX1,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M1RX1 );
          PORT_Enable( RLIN2_PORT_M1TX1, RLIN2_PORT_BIT_M1TX1,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M1TX1 );
          break;
#endif                     

#ifdef RLIN2_PORT_M1RX2
        case RLIN2_CHANNEL_2:
          PORT_Enable( RLIN2_PORT_M1RX2, RLIN2_PORT_BIT_M1RX2,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M1RX2 );
          PORT_Enable( RLIN2_PORT_M1TX2, RLIN2_PORT_BIT_M1TX2,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M1TX2 );
          break;
#endif                     

//#ifdef RLIN2_PORT_M1RX2
#ifdef RLIN2_PORT_M1RX3
        case RLIN2_CHANNEL_3:
          PORT_Enable( RLIN2_PORT_M1RX3, RLIN2_PORT_BIT_M1RX3,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M1RX3 );
          PORT_Enable( RLIN2_PORT_M1TX3, RLIN2_PORT_BIT_M1TX3,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M1TX3 );
          break;
#endif                     
        default:
          return( RLIN2_ERROR );
      }
      break;
        
    case RLIN2_2:
      switch( ChannelNumber_u08 )
      {
#ifdef RLIN2_PORT_M2RX0
        case RLIN2_CHANNEL_0:
          PORT_Enable( RLIN2_PORT_M2RX0, RLIN2_PORT_BIT_M2RX0,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M2RX0 );
          PORT_Enable( RLIN2_PORT_M2TX0, RLIN2_PORT_BIT_M2TX0,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M2TX0 );
          break;
#endif                     

#ifdef RLIN2_PORT_M2RX1
        case RLIN2_CHANNEL_1:
          PORT_Enable( RLIN2_PORT_M2RX1, RLIN2_PORT_BIT_M2RX1,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M2RX1 );
          PORT_Enable( RLIN2_PORT_M2TX1, RLIN2_PORT_BIT_M2TX1,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M2TX1 );
          break;
#endif                     

#ifdef RLIN2_PORT_M2RX2
        case RLIN2_CHANNEL_2:
          PORT_Enable( RLIN2_PORT_M2RX2, RLIN2_PORT_BIT_M2RX2,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M2RX2 );
          PORT_Enable( RLIN2_PORT_M2TX2, RLIN2_PORT_BIT_M2TX2,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M2TX2 );
          break;
#endif                     

//#ifdef RLIN2_PORT_M2RX2
#ifdef RLIN2_PORT_M2RX3
        case RLIN2_CHANNEL_3:
          PORT_Enable( RLIN2_PORT_M2RX3, RLIN2_PORT_BIT_M2RX3,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M2RX3 );
          PORT_Enable( RLIN2_PORT_M2TX3, RLIN2_PORT_BIT_M2TX3,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M2TX3 );
          break;
#endif                     
        default:
          return( RLIN2_ERROR );
      }
      break;
        
    case RLIN2_3:
      switch( ChannelNumber_u08 )
      {
#ifdef RLIN2_PORT_M3RX0
        case RLIN2_CHANNEL_0:
          PORT_Enable( RLIN2_PORT_M3RX0, RLIN2_PORT_BIT_M3RX0,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M3RX0 );
          PORT_Enable( RLIN2_PORT_M3TX0, RLIN2_PORT_BIT_M3TX0,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M3TX0 );
          break;
#endif                     

#ifdef RLIN2_PORT_M3RX1
        case RLIN2_CHANNEL_1:
          PORT_Enable( RLIN2_PORT_M3RX1, RLIN2_PORT_BIT_M3RX1,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M3RX1 );
          PORT_Enable( RLIN2_PORT_M3TX1, RLIN2_PORT_BIT_M3TX1,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M3TX1 );
          break;
#endif                     

#ifdef RLIN2_PORT_M3RX2
        case RLIN2_CHANNEL_2:
          PORT_Enable( RLIN2_PORT_M3RX2, RLIN2_PORT_BIT_M3RX2,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M3RX2 );
          PORT_Enable( RLIN2_PORT_M3TX2, RLIN2_PORT_BIT_M3TX2,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M3TX2 );
          break;
#endif                     

#ifdef RLIN2_PORT_M3RX2
        case RLIN2_CHANNEL_3:
          PORT_Enable( RLIN2_PORT_M3RX3, RLIN2_PORT_BIT_M3RX3,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M3RX3 );
          PORT_Enable( RLIN2_PORT_M3TX3, RLIN2_PORT_BIT_M3TX3,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M3TX3 );
          break;
#endif                     
        default:
          return( RLIN2_ERROR );
      }
      break;

    case RLIN2_4:
      switch( ChannelNumber_u08 )
      {
#ifdef RLIN2_PORT_M4RX0
        case RLIN2_CHANNEL_0:
          PORT_Enable( RLIN2_PORT_M4RX0, RLIN2_PORT_BIT_M4RX0,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M4RX0 );
          PORT_Enable( RLIN2_PORT_M4TX0, RLIN2_PORT_BIT_M4TX0,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M4TX0 );
          break;
#endif                     

#ifdef RLIN2_PORT_M4RX1
        case RLIN2_CHANNEL_1:
          PORT_Enable( RLIN2_PORT_M4RX1, RLIN2_PORT_BIT_M4RX1,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M4RX1 );
          PORT_Enable( RLIN2_PORT_M4TX1, RLIN2_PORT_BIT_M4TX1,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M4TX1 );
          break;
#endif                     

#ifdef RLIN2_PORT_M4RX2
        case RLIN2_CHANNEL_2:
          PORT_Enable( RLIN2_PORT_M4RX2, RLIN2_PORT_BIT_M4RX2,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M4RX2 );
          PORT_Enable( RLIN2_PORT_M4TX2, RLIN2_PORT_BIT_M4TX2,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M4TX2 );
          break;
#endif                     

#ifdef RLIN2_PORT_M4RX2
        case RLIN2_CHANNEL_3:
          PORT_Enable( RLIN2_PORT_M4RX3, RLIN2_PORT_BIT_M4RX3,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M4RX3 );
          PORT_Enable( RLIN2_PORT_M4TX3, RLIN2_PORT_BIT_M4TX3,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M4TX3 );
          break;
#endif                     
        default:
          return( RLIN2_ERROR );
      }
      break;
        
    case RLIN2_5:
      switch( ChannelNumber_u08 )
      {
#ifdef RLIN2_PORT_M5RX0
        case RLIN2_CHANNEL_0:
          PORT_Enable( RLIN2_PORT_M5RX0, RLIN2_PORT_BIT_M5RX0,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M5RX0 );
          PORT_Enable( RLIN2_PORT_M5TX0, RLIN2_PORT_BIT_M5TX0,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M5TX0 );
          break;
#endif                     

#ifdef RLIN2_PORT_M5RX1
        case RLIN2_CHANNEL_1:
          PORT_Enable( RLIN2_PORT_M5RX1, RLIN2_PORT_BIT_M5RX1,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M5RX1 );
          PORT_Enable( RLIN2_PORT_M5TX1, RLIN2_PORT_BIT_M5TX1,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M5TX1 );
          break;
#endif                     

#ifdef RLIN2_PORT_M5RX2
        case RLIN2_CHANNEL_2:
          PORT_Enable( RLIN2_PORT_M5RX2, RLIN2_PORT_BIT_M5RX2,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M5RX2 );
          PORT_Enable( RLIN2_PORT_M5TX2, RLIN2_PORT_BIT_M5TX2,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M5TX2 );
          break;
#endif                     

#ifdef RLIN2_PORT_M5RX2
        case RLIN2_CHANNEL_3:
          PORT_Enable( RLIN2_PORT_M5RX3, RLIN2_PORT_BIT_M5RX3,
                       PORT_DIR_INPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M5RX3 );
          PORT_Enable( RLIN2_PORT_M5TX3, RLIN2_PORT_BIT_M5TX3,
                       PORT_DIR_OUTPUT, PORT_MODE_PERIPHERAL, 
                       RLIN2_PORT_FUNC_M5TX3 );
          break;
#endif                     
        default:
          return( RLIN2_ERROR );
      }
      break;
        
    default:
      return( RLIN2_ERROR );
    }
    
    return( RLIN2_OK );
}

bit RLIN2_PortDisable( u08 UnitNumber_u08,
                       u08 ChannelNumber_u08 )
{ 
  switch( UnitNumber_u08 ) 
  {
    case RLIN2_0:
      switch( ChannelNumber_u08 )
      {
#ifdef RLIN2_PORT_M0RX0
        case RLIN2_CHANNEL_0:
          PORT_Disable( RLIN2_PORT_M0RX0, RLIN2_PORT_BIT_M0RX0 );
          PORT_Disable( RLIN2_PORT_M0TX0, RLIN2_PORT_BIT_M0TX0 );
          break;
#endif
#ifdef RLIN2_PORT_M0RX1
        case RLIN2_CHANNEL_1:
          PORT_Disable( RLIN2_PORT_M0RX1, RLIN2_PORT_BIT_M0RX1 );
          PORT_Disable( RLIN2_PORT_M0TX1, RLIN2_PORT_BIT_M0TX1 );
          break;
#endif
#ifdef RLIN2_PORT_M0RX2
        case RLIN2_CHANNEL_2:
          PORT_Disable( RLIN2_PORT_M0RX2, RLIN2_PORT_BIT_M0RX2 );
          PORT_Disable( RLIN2_PORT_M0TX2, RLIN2_PORT_BIT_M0TX2 );
          break;
#endif
#ifdef RLIN2_PORT_M0RX3
        case RLIN2_CHANNEL_3:
          PORT_Disable( RLIN2_PORT_M0RX3, RLIN2_PORT_BIT_M0RX3 );
          PORT_Disable( RLIN2_PORT_M0TX3, RLIN2_PORT_BIT_M0TX3 );
          break;
#endif
        default:
          return( RLIN2_ERROR );
      }
      break;

    case RLIN2_1:
      switch( ChannelNumber_u08 )
      {
#ifdef RLIN2_PORT_M1RX0
        case RLIN2_CHANNEL_0:
          PORT_Disable( RLIN2_PORT_M1RX0, RLIN2_PORT_BIT_M1RX0 );
          PORT_Disable( RLIN2_PORT_M1TX0, RLIN2_PORT_BIT_M1TX0 );
          break;
#endif
#ifdef RLIN2_PORT_M1RX1
        case RLIN2_CHANNEL_1:
          PORT_Disable( RLIN2_PORT_M1RX1, RLIN2_PORT_BIT_M1RX1 );
          PORT_Disable( RLIN2_PORT_M1TX1, RLIN2_PORT_BIT_M1TX1 );
          break;
#endif
#ifdef RLIN2_PORT_M1RX2
        case RLIN2_CHANNEL_2:
          PORT_Disable( RLIN2_PORT_M1RX2, RLIN2_PORT_BIT_M1RX2 );
          PORT_Disable( RLIN2_PORT_M1TX2, RLIN2_PORT_BIT_M1TX2 );
          break;
#endif
#ifdef RLIN2_PORT_M1RX3
        case RLIN2_CHANNEL_3:
          PORT_Disable( RLIN2_PORT_M1RX3, RLIN2_PORT_BIT_M1RX3 );
          PORT_Disable( RLIN2_PORT_M1TX3, RLIN2_PORT_BIT_M1TX3 );
          break;
#endif
        default:
          return( RLIN2_ERROR );
      }
      break;

    case RLIN2_2:
      switch( ChannelNumber_u08 )
      {
#ifdef RLIN2_PORT_M2RX0
        case RLIN2_CHANNEL_0:
          PORT_Disable( RLIN2_PORT_M2RX0, RLIN2_PORT_BIT_M2RX0 );
          PORT_Disable( RLIN2_PORT_M2TX0, RLIN2_PORT_BIT_M2TX0 );
          break;
#endif
#ifdef RLIN2_PORT_M2RX1
        case RLIN2_CHANNEL_1:
          PORT_Disable( RLIN2_PORT_M2RX1, RLIN2_PORT_BIT_M2RX1 );
          PORT_Disable( RLIN2_PORT_M2TX1, RLIN2_PORT_BIT_M2TX1 );
          break;
#endif
#ifdef RLIN2_PORT_M2RX2
        case RLIN2_CHANNEL_2:
          PORT_Disable( RLIN2_PORT_M2RX2, RLIN2_PORT_BIT_M2RX2 );
          PORT_Disable( RLIN2_PORT_M2TX2, RLIN2_PORT_BIT_M2TX2 );
          break;
#endif
#ifdef RLIN2_PORT_M2RX3
        case RLIN2_CHANNEL_3:
          PORT_Disable( RLIN2_PORT_M2RX3, RLIN2_PORT_BIT_M2RX3 );
          PORT_Disable( RLIN2_PORT_M2TX3, RLIN2_PORT_BIT_M2TX3 );
          break;
#endif
        default:
          return( RLIN2_ERROR );
      }
      break;

    case RLIN2_3:
      switch( ChannelNumber_u08 )
      {
#ifdef RLIN2_PORT_M3RX0
        case RLIN2_CHANNEL_0:
          PORT_Disable( RLIN2_PORT_M3RX0, RLIN2_PORT_BIT_M3RX0 );
          PORT_Disable( RLIN2_PORT_M3TX0, RLIN2_PORT_BIT_M3TX0 );
          break;
#endif
#ifdef RLIN2_PORT_M3RX1
        case RLIN2_CHANNEL_1:
          PORT_Disable( RLIN2_PORT_M3RX1, RLIN2_PORT_BIT_M3RX1 );
          PORT_Disable( RLIN2_PORT_M3TX1, RLIN2_PORT_BIT_M3TX1 );
          break;
#endif
#ifdef RLIN2_PORT_M3RX2
        case RLIN2_CHANNEL_2:
          PORT_Disable( RLIN2_PORT_M3RX2, RLIN2_PORT_BIT_M3RX2 );
          PORT_Disable( RLIN2_PORT_M3TX2, RLIN2_PORT_BIT_M3TX2 );
          break;
#endif
#ifdef RLIN2_PORT_M3RX3
        case RLIN2_CHANNEL_3:
          PORT_Disable( RLIN2_PORT_M3RX3, RLIN2_PORT_BIT_M3RX3 );
          PORT_Disable( RLIN2_PORT_M3TX3, RLIN2_PORT_BIT_M3TX3 );
          break;
#endif
        default:
          return( RLIN2_ERROR );
      }
      break;

    case RLIN2_4:
      switch( ChannelNumber_u08 )
      {
#ifdef RLIN2_PORT_M4RX0
        case RLIN2_CHANNEL_0:
          PORT_Disable( RLIN2_PORT_M4RX0, RLIN2_PORT_BIT_M4RX0 );
          PORT_Disable( RLIN2_PORT_M4TX0, RLIN2_PORT_BIT_M4TX0 );
          break;
#endif
#ifdef RLIN2_PORT_M4RX1
        case RLIN2_CHANNEL_1:
          PORT_Disable( RLIN2_PORT_M4RX1, RLIN2_PORT_BIT_M4RX1 );
          PORT_Disable( RLIN2_PORT_M4TX1, RLIN2_PORT_BIT_M4TX1 );
          break;
#endif
#ifdef RLIN2_PORT_M4RX2
        case RLIN2_CHANNEL_2:
          PORT_Disable( RLIN2_PORT_M4RX2, RLIN2_PORT_BIT_M4RX2 );
          PORT_Disable( RLIN2_PORT_M4TX2, RLIN2_PORT_BIT_M4TX2 );
          break;
#endif
#ifdef RLIN2_PORT_M4RX3
        case RLIN2_CHANNEL_3:
          PORT_Disable( RLIN2_PORT_M4RX3, RLIN2_PORT_BIT_M4RX3 );
          PORT_Disable( RLIN2_PORT_M4TX3, RLIN2_PORT_BIT_M4TX3 );
          break;
#endif
        default:
          return( RLIN2_ERROR );
      }
      break;

    case RLIN2_5:
      switch( ChannelNumber_u08 )
      {
#ifdef RLIN2_PORT_M5RX0
        case RLIN2_CHANNEL_0:
          PORT_Disable( RLIN2_PORT_M5RX0, RLIN2_PORT_BIT_M5RX0 );
          PORT_Disable( RLIN2_PORT_M5TX0, RLIN2_PORT_BIT_M5TX0 );
          break;
#endif
#ifdef RLIN2_PORT_M5RX1
        case RLIN2_CHANNEL_1:
          PORT_Disable( RLIN2_PORT_M5RX1, RLIN2_PORT_BIT_M5RX1 );
          PORT_Disable( RLIN2_PORT_M5TX1, RLIN2_PORT_BIT_M5TX1 );
          break;
#endif
#ifdef RLIN2_PORT_M5RX2
        case RLIN2_CHANNEL_2:
          PORT_Disable( RLIN2_PORT_M5RX2, RLIN2_PORT_BIT_M5RX2 );
          PORT_Disable( RLIN2_PORT_M5TX2, RLIN2_PORT_BIT_M5TX2 );
          break;
#endif
#ifdef RLIN2_PORT_M5RX3
        case RLIN2_CHANNEL_3:
          PORT_Disable( RLIN2_PORT_M5RX3, RLIN2_PORT_BIT_M5RX3 );
          PORT_Disable( RLIN2_PORT_M5TX3, RLIN2_PORT_BIT_M5TX3 );
          break;
#endif
        default:
          return( RLIN2_ERROR );
      }
      break;

    default:
      return( RLIN2_ERROR );
  }
  
  return( RLIN2_OK );
}

bit RLIN2_Reset( u08 UnitNumber_u08 )
{
  bit StatusFlag_bit;
  u08 ChannelNumber_u08;
  
  if( UnitNumber_u08 >= RLIN2_MACROS ) return( RLIN2_ERROR );
  
  for( ChannelNumber_u08 = 0;
       ChannelNumber_u08 < ee_rlin2_channels[ UnitNumber_u08 ];
       ChannelNumber_u08++ )
  {
    rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lcuc.om = RLIN2_MMODE_RESET;

    while( ( rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lmst.om 
           & RLIN2_MMODE_RESET_MASK ) != RLIN2_MMODE_RESET );
  }
  
  StatusFlag_bit =  RLIN2_CreateInterrupt( UnitNumber_u08,
                                           ChannelNumber_u08,
                                           RLIN2_IRQ_SEND,
                                           0,
                                           NULL );
  StatusFlag_bit &= RLIN2_CreateInterrupt( UnitNumber_u08,
                                           ChannelNumber_u08,
                                           RLIN2_IRQ_RECEIVE,
                                           0,
                                           NULL );
  StatusFlag_bit &= RLIN2_CreateInterrupt( UnitNumber_u08,
                                           ChannelNumber_u08,
                                           RLIN2_IRQ_ERROR,
                                           0,
                                           NULL );

  return( RLIN2_OK );
}

RLIN2_ResetOnChannel( u08 UnitNumber_u08,
        u08 ChannelNumber_u08 )
{
	 bit StatusFlag_bit;

	  if( UnitNumber_u08 >= RLIN2_MACROS ) return( RLIN2_ERROR );


      rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lcuc.om = RLIN2_MMODE_RESET;

      while( ( rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lmst.om
	         & RLIN2_MMODE_RESET_MASK ) != RLIN2_MMODE_RESET );


	  StatusFlag_bit =  RLIN2_CreateInterrupt( UnitNumber_u08,
	                                           ChannelNumber_u08,
	                                           RLIN2_IRQ_SEND,
	                                           0,
	                                           NULL );
	  StatusFlag_bit &= RLIN2_CreateInterrupt( UnitNumber_u08,
	                                           ChannelNumber_u08,
	                                           RLIN2_IRQ_RECEIVE,
	                                           0,
	                                           NULL );
	  StatusFlag_bit &= RLIN2_CreateInterrupt( UnitNumber_u08,
	                                           ChannelNumber_u08,
	                                           RLIN2_IRQ_ERROR,
	                                           0,
	                                           NULL );

	  return( RLIN2_OK );
}

bit RLIN2_LINSetConfig( u08 UnitNumber_u08,
                        u08 ChannelNumber_u08,
                        flt Oscillator_Frequency_flt,
                        u08 LINStandard_u08,
                        u32 Baudrate_u32,
                        u08 ClockSelection_u08,
                        u08 BreakLength_u08,
                        u08 BreakDelimiter_u08,
                        u08 HeaderSpace_u08,
                        u08 InterByteSpace_u08 )
{
  u16 TimerModulus_u16;
  u08 ClockSelectionFactor_u08;
  flt Factor_flt;
  bit Success_bit = RLIN2_OK;

  if( UnitNumber_u08 >= RLIN2_MACROS ) return( RLIN2_ERROR );
  if( ChannelNumber_u08 >= ee_rlin2_channels[ UnitNumber_u08 ] ) 
    return( RLIN2_ERROR );

  if( ( rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lmst.om 
    & RLIN2_MMODE_RESET_MASK ) != RLIN2_MMODE_RESET )
    return( RLIN2_ERROR );

  switch( ClockSelection_u08 )
  {
    case RLIN2_CLOCK_FA:
      ClockSelectionFactor_u08 = RLIN2_CLOCKDIVIDER_FA;
      break;
    case RLIN2_CLOCK_FB:
      ClockSelectionFactor_u08 = RLIN2_CLOCKDIVIDER_FB;
      break;
    case RLIN2_CLOCK_FC:
      ClockSelectionFactor_u08 = RLIN2_CLOCKDIVIDER_FC;
      break;
    case RLIN2_CLOCK_FD:
      ClockSelectionFactor_u08 = RLIN2_CLOCKDIVIDER_FD;
      break;
    default:
      return( RLIN2_ERROR );
  }
  
  Factor_flt = ( flt )RLIN2_FREQFACTOR / 
               ( ( flt )RLIN2_SAMPLES_MASTER * ( flt )ClockSelectionFactor_u08 );

  TimerModulus_u16 = ( u16 )
    ( ( Oscillator_Frequency_flt * Factor_flt ) / ( ( flt )Baudrate_u32 ) );

  if( TimerModulus_u16 < RLIN2_MIN_MODULUS )
  {
    return( RLIN2_ERROR );
  } 
  
  if( TimerModulus_u16 > RLIN2_MAX_MODULUS )
  {
    switch( ClockSelection_u08 )  /* try other clock selections */
    {
      case RLIN2_CLOCK_FA:
        ClockSelection_u08 = RLIN2_CLOCK_FB;
        break;
      case RLIN2_CLOCK_FB:
        ClockSelection_u08 = RLIN2_CLOCK_FC;
        break;
      case RLIN2_CLOCK_FC:
      case RLIN2_CLOCK_FD:
      default:
        return( RLIN2_ERROR );
    }
    Success_bit = RLIN2_LINSetConfig( UnitNumber_u08,
                                      ChannelNumber_u08,
                                      Oscillator_Frequency_flt,
                                      LINStandard_u08,
                                      Baudrate_u32,
                                      ClockSelection_u08,
                                      BreakLength_u08,
                                      BreakDelimiter_u08,
                                      HeaderSpace_u08,
                                      InterByteSpace_u08 );
  }
  else
  {    
    /* Baudrate setting */
  
    rlin2_p[ UnitNumber_u08 ]->lwbr.lwbr0 = LINStandard_u08;
    
    if( ClockSelection_u08 == RLIN2_CLOCK_FD )
    {
      rlin2_p[ UnitNumber_u08 ]->brp1 = ( u08 )( TimerModulus_u16 );
    }
    else
    {
      rlin2_p[ UnitNumber_u08 ]->brp0 = ( u08 )( TimerModulus_u16 );
    }
  
    rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lbfc.blt = BreakLength_u08;
    rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lbfc.bdt = BreakDelimiter_u08;
  
    /* Other Parameters */
  
    rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lmd.lcks   = ClockSelection_u08;
    rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lsc.ibhs   = HeaderSpace_u08;
    rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lsc.ibs    = InterByteSpace_u08;
  
    /* Activate Communication */
    
    rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lcuc.om         = RLIN2_MMODE_OPERATION;
    while( rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lmst.om != RLIN2_MMODE_OPERATION );    
  }
  
  return( Success_bit );
}

bit RLIN2_LINSendMessage( u08  UnitNumber_u08,
                          u08  ChannelNumber_u08,
                          u08  PID_u08,
                          u08  MessageLength_u08,
                          u08  EnhancedCheckSum_u08,
                          u08  Direction_u08,
                          pu08 Data_pu08 )
{
  u08  DataCounter_u08;
  u08  PIDCalc_u08;
  pu08 DataBufferPtr_pu08 = Data_pu08;
  
  if( UnitNumber_u08 >= RLIN2_MACROS ) return( RLIN2_ERROR );
  if( ChannelNumber_u08 >= ee_rlin2_channels[ UnitNumber_u08 ] ) 
    return( RLIN2_ERROR );
    
  if( rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ltrc.fts == RLIN2_SET )
  {
    return( RLIN2_ERROR );
  }

  if( Direction_u08 == RLIN2_RESPONSE_TRANSMIT )
  {
    for( DataCounter_u08 = 0;
         DataCounter_u08 < MessageLength_u08;
         DataCounter_u08++ )
    {
      rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].buf[ DataCounter_u08 ] = 
        *DataBufferPtr_pu08;
        DataBufferPtr_pu08++;
    }
  }
  
  PID_u08 &= 0x3F;

  PIDCalc_u08 =    PID_u08 + ( PID_u08 >> 1 ) + 
                             ( PID_u08 >> 2 ) + 
                             ( PID_u08 >> 4 );
  PID_u08 |= ( ( PIDCalc_u08 & 0x01 ) << 6 );


  PIDCalc_u08 = ~( ( PID_u08 >> 1 ) + 
                   ( PID_u08 >> 3 ) + 
                   ( PID_u08 >> 4 ) + 
                   ( PID_u08 >> 5 ) );
  PID_u08 |= ( ( PIDCalc_u08 & 0x01 ) << 7 );

  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ldfc.rfdl = MessageLength_u08;
  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ldfc.rcds = Direction_u08;
  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ldfc.lcs  = EnhancedCheckSum_u08;
  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ldfc.fsm  = RLIN2_MFRAME_COMBINED;
  
  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lidb.id   = ( PID_u08 & RLIN2_PIDMASK );
  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lidb.idp0 = ( PID_u08 >> RLIN2_PID_P0 );
  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lidb.idp1 = ( PID_u08 >> RLIN2_PID_P1 );
  
   /* trigger transmission */
   
  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ltrc.fts = RLIN2_SET;

  return( RLIN2_OK );
}

bit RLIN2_LINEnableInterrupt( u08 UnitNumber_u08,
                              u08 ChannelNumber_u08,
                              u08 Transmit_u08,
                              u08 Receive_u08,
                              u08 ErrorGlobal_u08,
                              u08 ErrorBit_u08,
                              u08 ErrorPhyBus_u08,
                              u08 ErrorTimeout_u08,
                              u08 ErrorFrame_u08 )
{
  if( UnitNumber_u08 >= RLIN2_MACROS ) return( RLIN2_ERROR );
  if( ChannelNumber_u08 >= ee_rlin2_channels[ UnitNumber_u08 ] ) 
    return( RLIN2_ERROR );

  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lie.ftcie = Transmit_u08;
  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lie.frcie = Receive_u08;
  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lie.errie = ErrorGlobal_u08;
  
  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lede.bere  = ErrorBit_u08;
  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lede.pbere = ErrorPhyBus_u08;
  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lede.ftere = ErrorTimeout_u08;
  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lede.fere  = ErrorFrame_u08;

  return( RLIN2_OK );  
}

bit RLIN2_LINGetStatus( u08  UnitNumber_u08,
                        u08  ChannelNumber_u08,
                        pu08 NoAction_pu08,
                        pu08 HeaderComplete_pu08,
                        pu08 DataReceived_pu08,
                        pu08 DataTransmitted_pu08,
                        pu08 PID_pu08 )
{
  if( UnitNumber_u08 >= RLIN2_MACROS ) return( RLIN2_ERROR );
  if( ChannelNumber_u08 >= ee_rlin2_channels[ UnitNumber_u08 ] ) 
    return( RLIN2_ERROR );

  *HeaderComplete_pu08  = RLIN2_CLEAR;
  *DataReceived_pu08    = RLIN2_CLEAR;
  *DataTransmitted_pu08 = RLIN2_CLEAR;
  *NoAction_pu08        = RLIN2_SET;
  
  *PID_pu08 = ( rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lidb.id );

  if( rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lst.b.htrc )
  {
    *HeaderComplete_pu08 = RLIN2_SET;
    *NoAction_pu08 = RLIN2_CLEAR;
    rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lst.b.htrc = RLIN2_CLEAR;
  }

  if( rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lst.b.ftc )
  {
    *DataTransmitted_pu08 = RLIN2_SET;
    *NoAction_pu08 = RLIN2_CLEAR;
    rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lst.b.ftc = RLIN2_CLEAR;
  }
  
  if( rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lst.b.frc )
  {
    *DataReceived_pu08 = RLIN2_SET;
    *NoAction_pu08 = RLIN2_CLEAR;
    rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lst.b.frc = RLIN2_CLEAR;
  }
  
  return( RLIN2_OK );
}

bit RLIN2_LINGetError( u08  UnitNumber_u08,
                       u08  ChannelNumber_u08,
                       pu08 AnyError_pu08,
                       pu08 BitError_pu08,
                       pu08 DataConsistencyError_pu08,
                       pu08 TimeoutError_pu08,
                       pu08 FrameError_pu08,
                       pu08 CheckSumError_pu08 )
{
  if( UnitNumber_u08 >= RLIN2_MACROS ) return( RLIN2_ERROR );
  if( ChannelNumber_u08 >= ee_rlin2_channels[ UnitNumber_u08 ] ) 
    return( RLIN2_ERROR );

  *BitError_pu08                 = rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lest.ber;
  *DataConsistencyError_pu08     = rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lest.pber;
  *TimeoutError_pu08             = rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lest.ter;
  *FrameError_pu08               = rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lest.fer;
  *CheckSumError_pu08            = rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lest.cser;
  
  if( ( *BitError_pu08                 == RLIN2_SET ) ||
      ( *DataConsistencyError_pu08     == RLIN2_SET ) ||
      ( *TimeoutError_pu08             == RLIN2_SET ) ||
      ( *FrameError_pu08               == RLIN2_SET ) ||
      ( *CheckSumError_pu08            == RLIN2_SET ) )
  {
    *AnyError_pu08 = RLIN2_SET;
  }
  else
  {
    *AnyError_pu08 = RLIN2_CLEAR;
  }
  
  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lest.ber  = RLIN2_CLEAR;
  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lest.pber = RLIN2_CLEAR;
  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lest.ter  = RLIN2_CLEAR;
  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lest.fer  = RLIN2_CLEAR;
  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lest.cser = RLIN2_CLEAR;
  
  return( RLIN2_OK );
}

bit RLIN2_LINReceiveMessage( u08  UnitNumber_u08,
                             u08  ChannelNumber_u08,
                             u08  MessageLength_u08,
                             pu08 Data_pu08 )
{
  u08  DataCounter_u08;
  pu08 DataBufferPtr_pu08 = Data_pu08;
  
  if( UnitNumber_u08 >= RLIN2_MACROS ) return( RLIN2_ERROR );
  if( ChannelNumber_u08 >= ee_rlin2_channels[ UnitNumber_u08 ] ) 
    return( RLIN2_ERROR );

  for( DataCounter_u08 = 0;
       DataCounter_u08 < MessageLength_u08;
       DataCounter_u08++ )
  {
    *DataBufferPtr_pu08 = rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].buf
                                 [ DataCounter_u08 ];
    DataBufferPtr_pu08++;
  }
   
  return( RLIN2_OK );
}

bit RLIN2_LINSendWakeup( u08 UnitNumber_u08,
                         u08 ChannelNumber_u08,
                         u08 WakeupLength_u08 )
{
  if( UnitNumber_u08 >= RLIN2_MACROS ) return( RLIN2_ERROR );
  if( ChannelNumber_u08 >= ee_rlin2_channels[ UnitNumber_u08 ] ) 
    return( RLIN2_ERROR );

  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lcuc.om = RLIN2_MMODE_RESET;
  
  while( ( rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lmst.om 
          & RLIN2_MMODE_RESET_MASK ) != RLIN2_MMODE_RESET );

  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lwup.wutl = WakeupLength_u08;

  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lcuc.om = RLIN2_MMODE_WAKEUP;
  while( rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lmst.om != RLIN2_MMODE_WAKEUP );
  
  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ldfc.rcds = RLIN2_RESPONSE_TRANSMIT;
  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ltrc.fts  = RLIN2_SET;
  while( rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ltrc.fts == RLIN2_SET );
  
  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lcuc.om = RLIN2_MMODE_RESET;
  
  while( ( rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lmst.om 
          & RLIN2_MMODE_RESET_MASK ) != RLIN2_MMODE_RESET );

  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lcuc.om         = RLIN2_MMODE_OPERATION;
  while( rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lmst.om != RLIN2_MMODE_OPERATION );

  return( RLIN2_OK );  
}

bit RLIN2_LINReceiveWakeup( u08 UnitNumber_u08,
                            u08 ChannelNumber_u08 )
{
  if( UnitNumber_u08 >= RLIN2_MACROS ) return( RLIN2_ERROR );
  if( ChannelNumber_u08 >= ee_rlin2_channels[ UnitNumber_u08 ] ) 
    return( RLIN2_ERROR );

  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lcuc.om = RLIN2_MMODE_RESET;
  
  while( ( rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lmst.om 
          & RLIN2_MMODE_RESET_MASK  )!= RLIN2_MMODE_RESET );

  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ldfc.rcds = RLIN2_RESPONSE_RECEIVE;
  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].ltrc.fts  = RLIN2_SET;

  return( RLIN2_OK );  
}

bit RLIN2_LINRestart( u08 UnitNumber_u08,
                      u08 ChannelNumber_u08 )
{
  if( UnitNumber_u08 >= RLIN2_MACROS ) return( RLIN2_ERROR );
  if( ChannelNumber_u08 >= ee_rlin2_channels[ UnitNumber_u08 ] ) 
    return( RLIN2_ERROR );

  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lcuc.om = RLIN2_MMODE_RESET;
  
  while( ( rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lmst.om 
          & RLIN2_MMODE_RESET_MASK ) != RLIN2_MMODE_RESET );

  rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lcuc.om         = RLIN2_MMODE_OPERATION;
  while( rlin2_p[ UnitNumber_u08 ]->ch[ ChannelNumber_u08 ].lmst.om != RLIN2_MMODE_OPERATION );

  return( RLIN2_OK );  
}

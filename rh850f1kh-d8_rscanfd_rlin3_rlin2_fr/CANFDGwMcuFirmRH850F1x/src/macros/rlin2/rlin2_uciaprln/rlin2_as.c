//============================================================================
// PROJECT = RSCAN Type RLIN2_UCIAPRLN
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2014 by Renesas Electronics (EUROPE) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
//============================================================================
//Purpose: RLIN2 AUTOSAR interface
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

#include <ree_types.h>

#include <map_rlin2.h>
#include <rlin2_as.h>
#include <rlin2_as_cfg.h>

/* Local Static Flags */

static u08 WakeupLength[ RLIN2_MAXMACROS * RLIN2_MAXCHANNELS ] = 
    { RLIN2_WUPTL_8BITS, RLIN2_WUPTL_8BITS, RLIN2_WUPTL_8BITS, RLIN2_WUPTL_8BITS,
      RLIN2_WUPTL_8BITS, RLIN2_WUPTL_8BITS, RLIN2_WUPTL_8BITS, RLIN2_WUPTL_8BITS,
      RLIN2_WUPTL_8BITS, RLIN2_WUPTL_8BITS, RLIN2_WUPTL_8BITS, RLIN2_WUPTL_8BITS,
      RLIN2_WUPTL_8BITS, RLIN2_WUPTL_8BITS, RLIN2_WUPTL_8BITS, RLIN2_WUPTL_8BITS,
      RLIN2_WUPTL_8BITS, RLIN2_WUPTL_8BITS, RLIN2_WUPTL_8BITS, RLIN2_WUPTL_8BITS,
      RLIN2_WUPTL_8BITS, RLIN2_WUPTL_8BITS, RLIN2_WUPTL_8BITS, RLIN2_WUPTL_8BITS };

static Lin_FrameDlType CurrentDl[ RLIN2_MAXMACROS * RLIN2_MAXCHANNELS ] = 
    {  0, 0, 0, 0 ,  0, 0, 0, 0 ,  0, 0, 0, 0 ,
       0, 0, 0, 0 ,  0, 0, 0, 0 ,  0, 0, 0, 0  };

static Lin_StatusType CurrentState[ RLIN2_MAXMACROS * RLIN2_MAXCHANNELS ] = 
    { LIN_NOT_OK, LIN_NOT_OK, LIN_NOT_OK, LIN_NOT_OK,
      LIN_NOT_OK, LIN_NOT_OK, LIN_NOT_OK, LIN_NOT_OK,
      LIN_NOT_OK, LIN_NOT_OK, LIN_NOT_OK, LIN_NOT_OK,
      LIN_NOT_OK, LIN_NOT_OK, LIN_NOT_OK, LIN_NOT_OK,
      LIN_NOT_OK, LIN_NOT_OK, LIN_NOT_OK, LIN_NOT_OK,
      LIN_NOT_OK, LIN_NOT_OK, LIN_NOT_OK, LIN_NOT_OK };

/* Interrupt routines */

void RLIN2_LINM_AS_IRQSend( void )
{
  u08 ActiveUnit_u08    = RLIN2_InterruptFlagUnit_u08;
  u08 ActiveChannel_u08 = RLIN2_InterruptFlagChannel_u08;
  u08 HeaderReceived_u08;
  u08 DataReceived_u08;
  u08 DataTransmitted_u08;
  u08 NoAction_u08;
  u08 PID_u08;
  
  if( CurrentState[ ActiveUnit_u08 * RLIN2_MAXCHANNELS + ActiveChannel_u08 ] != LIN_NOT_OK )
  {
    RLIN2_LINGetStatus( ActiveUnit_u08,
                        ActiveChannel_u08,
                        &NoAction_u08,
                        &HeaderReceived_u08,
                        &DataReceived_u08,
                        &DataTransmitted_u08,
                        &PID_u08 );
                      
    switch( CurrentState[ ActiveUnit_u08 * RLIN2_MAXCHANNELS + ActiveChannel_u08 ] )
    {
      case LIN_TX_BUSY:
        if( DataTransmitted_u08 )
        {
          CurrentState[ ActiveUnit_u08 * RLIN2_MAXCHANNELS + ActiveChannel_u08 ] = LIN_TX_OK;
        }
        else
        {
          CurrentState[ ActiveUnit_u08 * RLIN2_MAXCHANNELS + ActiveChannel_u08 ] = LIN_TX_ERROR;
        }
      break;

    default:
      break;
    }
  }  
}

void RLIN2_LINM_AS_IRQReceive( void )
{
  u08 ActiveUnit_u08    = RLIN2_InterruptFlagUnit_u08;
  u08 ActiveChannel_u08 = RLIN2_InterruptFlagChannel_u08;
  u08 HeaderReceived_u08;
  u08 DataReceived_u08;
  u08 DataTransmitted_u08;
  u08 NoAction_u08;
  u08 PID_u08;
  
  if( CurrentState[ ActiveUnit_u08 * RLIN2_MAXCHANNELS + ActiveChannel_u08 ] != LIN_NOT_OK )
  {
    RLIN2_LINGetStatus( ActiveUnit_u08,
                        ActiveChannel_u08,
                        &NoAction_u08,
                        &HeaderReceived_u08,
                        &DataReceived_u08,
                        &DataTransmitted_u08,
                        &PID_u08 );
                      
    switch( CurrentState[ ActiveUnit_u08 * RLIN2_MAXCHANNELS + ActiveChannel_u08 ] )
    {
      case LIN_RX_BUSY:
        if( DataReceived_u08 )
        {
          CurrentState[ ActiveUnit_u08 * RLIN2_MAXCHANNELS + ActiveChannel_u08 ] = LIN_RX_OK;
        }
        else
        {
          CurrentState[ ActiveUnit_u08 * RLIN2_MAXCHANNELS + ActiveChannel_u08 ] = LIN_RX_ERROR;
        }
      break;

    default:
      break;
    }
  }
}

void RLIN2_LINM_AS_IRQError( void )
{
  u08 ActiveUnit_u08    = RLIN2_InterruptFlagUnit_u08;
  u08 ActiveChannel_u08 = RLIN2_InterruptFlagChannel_u08;
  u08 AnyError_u08;
  u08 BitError_u08;
  u08 DataConsistencyError_u08;
  u08 TimeoutError_u08;
  u08 FrameError_u08;
  u08 CheckSumError_u08;
  
  if( CurrentState[ ActiveUnit_u08 * RLIN2_MAXCHANNELS + ActiveChannel_u08 ] != LIN_NOT_OK )
  {
    RLIN2_LINGetError( ActiveUnit_u08,
                       ActiveChannel_u08,
                       &AnyError_u08,
                       &BitError_u08,
                       &DataConsistencyError_u08,
                       &TimeoutError_u08,
                       &FrameError_u08,
                       &CheckSumError_u08 );

    if( AnyError_u08 )
    {
      if( DataConsistencyError_u08 ) CurrentState[ ActiveUnit_u08 * RLIN2_MAXCHANNELS + ActiveChannel_u08 ] = LIN_TX_HEADER_ERROR;
      if( CheckSumError_u08 )        CurrentState[ ActiveUnit_u08 * RLIN2_MAXCHANNELS + ActiveChannel_u08 ] = LIN_RX_ERROR;
      if( TimeoutError_u08 )         CurrentState[ ActiveUnit_u08 * RLIN2_MAXCHANNELS + ActiveChannel_u08 ] = LIN_RX_NO_RESPONSE;
      if( BitError_u08 )             CurrentState[ ActiveUnit_u08 * RLIN2_MAXCHANNELS + ActiveChannel_u08 ] = LIN_TX_ERROR;
    }
  }
}

/* API Functions */

#ifdef RLIN2_AUTOSARIF

//=============================================================================
// FunctionName: Lin_Init
// IN  : Configuration set
// OUT : -
// Description : 
// Initialize AUTOSAR interface driver
//=============================================================================

void Lin_Init( const Lin_ConfigType *Config )
{
  u08 MacroUnit_u08;
  u08 ChannelUnit_u08;
  u08 CurrentUnit_u08;
  bit UARTStatus_bit   = RLIN2_OK;
  
  CurrentUnit_u08 = 0;
  
  for( MacroUnit_u08 = RLIN2_0;
       MacroUnit_u08 < RLIN2_MACROS;
       MacroUnit_u08++ )
  {
    UARTStatus_bit &= RLIN2_Reset( MacroUnit_u08 );

    for( ChannelUnit_u08 = RLIN2_CHANNEL_0;
         ChannelUnit_u08 < ee_rlin2_channels[ MacroUnit_u08 ];
         ChannelUnit_u08++ )
    {    
      if( ( Config->Unit[ CurrentUnit_u08 ] != NULL ) &&
          ( Config->Unit[ CurrentUnit_u08 ]->UnitNumber_u08 == CurrentUnit_u08 ) )
      {
        UARTStatus_bit &= RLIN2_PortEnable( MacroUnit_u08, ChannelUnit_u08 );
  
        UARTStatus_bit &= RLIN2_LINEnableInterrupt( 
                            MacroUnit_u08, ChannelUnit_u08,
                            RLIN2_SET,       /* TX */
                            RLIN2_SET,       /* RX */
                            RLIN2_SET,       /* ERR */
                            Config->Unit[ CurrentUnit_u08 ]->ErrorBit_u08,      /* Bit error */
                            Config->Unit[ CurrentUnit_u08 ]->ErrorPhyBus_u08,   /* Phys. Bus error */
                            Config->Unit[ CurrentUnit_u08 ]->ErrorTimeout_u08,  /* Timeout error */
                            Config->Unit[ CurrentUnit_u08 ]->ErrorFrame_u08     /* Frame error */
                            );
  
        UARTStatus_bit &= RLIN2_LINSetConfig( 
                            MacroUnit_u08, ChannelUnit_u08,
                            OSCILLATOR_FREQUENCY,
                            Config->Unit[ CurrentUnit_u08 ]->LINStandard_u08,
                            Config->Unit[ CurrentUnit_u08 ]->Baudrate_u32,
                            Config->Unit[ CurrentUnit_u08 ]->ClockSelection_u08,
                            Config->Unit[ CurrentUnit_u08 ]->BreakLength_u08,
                            Config->Unit[ CurrentUnit_u08 ]->BreakDelimiter_u08,
                            Config->Unit[ CurrentUnit_u08 ]->HeaderSpace_u08,
                            Config->Unit[ CurrentUnit_u08 ]->InterByteSpace_u08 );
  
        if( RLIN2_AS_IRQPRIO_TX != RLIN2_INTCLEAR )
          UARTStatus_bit &= RLIN2_CreateInterrupt( 
                              MacroUnit_u08, ChannelUnit_u08,
                              RLIN2_IRQ_SEND,
                              RLIN2_AS_IRQPRIO_TX,
                              RLIN2_LINM_AS_IRQSend );
        if( RLIN2_AS_IRQPRIO_RX != RLIN2_INTCLEAR )
          UARTStatus_bit &= RLIN2_CreateInterrupt( 
                              MacroUnit_u08, ChannelUnit_u08,
                              RLIN2_IRQ_RECEIVE,
                              RLIN2_AS_IRQPRIO_RX,
                              RLIN2_LINM_AS_IRQReceive );
        if( RLIN2_AS_IRQPRIO_ERR != RLIN2_INTCLEAR )
          UARTStatus_bit &= RLIN2_CreateInterrupt( 
                              MacroUnit_u08, ChannelUnit_u08,
                              RLIN2_IRQ_ERROR,
                              RLIN2_AS_IRQPRIO_ERR,
                              RLIN2_LINM_AS_IRQError );
                  
        if( UARTStatus_bit == RLIN2_OK ) 
        {
          WakeupLength[ CurrentUnit_u08 ] = 
                                      Config->Unit[ CurrentUnit_u08 ]
                                      ->WakeupLength_u08;
  
          CurrentState[ CurrentUnit_u08 ] = LIN_OPERATIONAL;
        }
      }
    }
    CurrentUnit_u08++;
  }
}

//=============================================================================
// FunctionName: Lin_SendFrame
// IN  : Channel, PDU
// OUT : -
// Description : 
// Send PDU on channel
//=============================================================================

Std_ReturnType Lin_SendFrame( uint8 Channel, Lin_PduType *PduInfoPtr )
{
  bit UARTStatus_bit;
  u08 CurrentUnit_u08;
  u08 CurrentChannel_u08;
  u08 SearchChannel_u08;
  
  if( ( CurrentState[ Channel ] == LIN_TX_BUSY ) ||
      ( CurrentState[ Channel ] == LIN_RX_BUSY ) ||
      ( CurrentState[ Channel ] == LIN_NOT_OK )  ||
      ( CurrentState[ Channel ] == LIN_CH_SLEEP ) )
  {
    return( E_NOT_OK );
  }
  
  SearchChannel_u08 = 0;
  
  for( CurrentUnit_u08 = RLIN2_0;
       CurrentUnit_u08 < RLIN2_MAXMACROS;
       CurrentUnit_u08++ )
  {
    for( CurrentChannel_u08 = RLIN2_CHANNEL_0;
         CurrentChannel_u08 < ee_rlin2_channels[ CurrentUnit_u08 ];
         CurrentChannel_u08++ )
    {
      if( SearchChannel_u08 != Channel )
      {
        SearchChannel_u08++;
      }
      else
      {
        UARTStatus_bit = RLIN2_LINSendMessage( CurrentUnit_u08,
                                               CurrentChannel_u08,
                                               ( u08 )PduInfoPtr->Pid,
                                               ( u08 )PduInfoPtr->Dl,
                                               ( u08 )PduInfoPtr->Cs,
                                               ( u08 )PduInfoPtr->Drc,
                                               ( pu08 )PduInfoPtr->SduPtr );
      
        CurrentDl[ Channel ] = PduInfoPtr->Dl;
      
        switch( PduInfoPtr->Drc )
        {
           case LIN_MASTER_RESPONSE:
            CurrentState[ Channel ] = LIN_TX_BUSY;
            break;
            
           case LIN_SLAVE_RESPONSE:
           case LIN_SLAVE_TO_SLAVE:
            CurrentState[ Channel ] = LIN_RX_BUSY;
            break;
        }
        CurrentUnit_u08    = RLIN2_MAXMACROS;
        CurrentChannel_u08 = RLIN2_MAXCHANNELS;
      }
    }
  }
  
  if( UARTStatus_bit == RLIN2_OK ) return( E_OK );
  else return( E_NOT_OK );
}

//=============================================================================
// FunctionName: Lin_GetStatus
// IN  : Channel, SDU pointer
// OUT : -
// Description : 
// Get LIN status and receive SDU from channel
//=============================================================================

Lin_StatusType Lin_GetStatus( uint8 Channel, uint8 *LinSduPtr )
{
  bit UARTStatus_bit;
  u08 ByteCounter_u08;
  u08 CurrentUnit_u08;
  u08 CurrentChannel_u08;
  u08 SearchChannel_u08;
  u08 LINBuffer[ RLIN2_LINDATALEN_MAX ];
  
  Lin_StatusType CurrentStateFlag;
  
  CurrentStateFlag = CurrentState[ Channel ];
  
  if( ( CurrentStateFlag == LIN_TX_HEADER_ERROR ) ||
      ( CurrentStateFlag == LIN_TX_ERROR )        ||
      ( CurrentStateFlag == LIN_RX_ERROR )        ||
      ( CurrentStateFlag == LIN_RX_NO_RESPONSE ) )
  {
    CurrentState[ Channel ] = LIN_OPERATIONAL;
  }
  
  SearchChannel_u08 = 0;
  
  for( CurrentUnit_u08 = RLIN2_0;
       CurrentUnit_u08 < RLIN2_MAXMACROS;
       CurrentUnit_u08++ )
  {
    for( CurrentChannel_u08 = RLIN2_CHANNEL_0;
         CurrentChannel_u08 < ee_rlin2_channels[ CurrentUnit_u08 ];
         CurrentChannel_u08++ )
    {
      if( SearchChannel_u08 != Channel )
      {
        SearchChannel_u08++;
      }
      else
      {
        if( CurrentStateFlag == LIN_RX_OK )
        {
          UARTStatus_bit = RLIN2_LINReceiveMessage( CurrentUnit_u08,
                                                    CurrentChannel_u08,
                                                    CurrentDl[ Channel ],
                                                    &LINBuffer[ 0 ] );
          if( UARTStatus_bit == RLIN2_OK )
          {
            for( ByteCounter_u08 = 0;
                 ByteCounter_u08 < CurrentDl[ Channel ];
                 ByteCounter_u08++ )
            {
              *LinSduPtr = LINBuffer[ ByteCounter_u08 ];
              LinSduPtr++;
            }
            return( CurrentStateFlag );
          }
          else
          {
            return( LIN_NOT_OK );
          }
        }
        else
        {
          return( CurrentStateFlag );
        }
      }
    }
  }
  return( LIN_NOT_OK );
}

//=============================================================================
// FunctionName: Lin_CheckWakeup
// IN  : Channel
// OUT : -
// Description : 
// Get LIN wakeup status
//=============================================================================

Std_ReturnType Lin_CheckWakeup( uint8 Channel )
{
  if( CurrentState[ Channel ] == LIN_CH_SLEEP ) return( E_NOT_OK );
  else return( E_OK );
}

//=============================================================================
// FunctionName: Lin_GoToSleep
// IN  : Channel
// OUT : -
// Description : 
// Set LIN channel in sleep mode
//=============================================================================

Std_ReturnType Lin_GoToSleep( uint8 Channel )
{
  bit UARTStatus_bit = RLIN2_ERROR;  
  u08 CurrentUnit_u08;
  u08 CurrentChannel_u08;
  u08 SearchChannel_u08;
  
  SearchChannel_u08 = 0;
  
  for( CurrentUnit_u08 = RLIN2_0;
       CurrentUnit_u08 < RLIN2_MAXMACROS;
       CurrentUnit_u08++ )
  {
    for( CurrentChannel_u08 = RLIN2_CHANNEL_0;
         CurrentChannel_u08 < ee_rlin2_channels[ CurrentUnit_u08 ];
         CurrentChannel_u08++ )
    {
      if( SearchChannel_u08 != Channel )
      {
        SearchChannel_u08++;
      }
      else
      {
        UARTStatus_bit = RLIN2_LINReceiveWakeup( CurrentUnit_u08,
                                                 CurrentChannel_u08 );
      }
    }
  }
  
  if( UARTStatus_bit == RLIN2_OK )
  {
    CurrentState[ Channel ] = LIN_CH_SLEEP;
    return( E_OK );
  }
  else
  {
    CurrentState[ Channel ] = LIN_NOT_OK;
    return( E_NOT_OK );
  }
}

//=============================================================================
// FunctionName: Lin_Wakeup
// IN  : Channel
// OUT : -
// Description : 
// Set LIN channel in active mode, send wake up frame
//=============================================================================

Std_ReturnType Lin_Wakeup( uint8 Channel )
{
  bit UARTStatus_bit = RLIN2_ERROR;  
  u08 CurrentUnit_u08;
  u08 CurrentChannel_u08;
  u08 SearchChannel_u08;
  
  SearchChannel_u08 = 0;
  
  for( CurrentUnit_u08 = RLIN2_0;
       CurrentUnit_u08 < RLIN2_MAXMACROS;
       CurrentUnit_u08++ )
  {
    for( CurrentChannel_u08 = RLIN2_CHANNEL_0;
         CurrentChannel_u08 < ee_rlin2_channels[ CurrentUnit_u08 ];
         CurrentChannel_u08++ )
    {
      if( SearchChannel_u08 != Channel )
      {
        SearchChannel_u08++;
      }
      else
      {  
        UARTStatus_bit = RLIN2_LINSendWakeup( CurrentUnit_u08,
                                              CurrentChannel_u08,
                                              WakeupLength[ Channel ] );
      }
    }
  }
  
  if( UARTStatus_bit == RLIN2_OK )
  {
    CurrentState[ Channel ] = LIN_OPERATIONAL;
    return( E_OK );
  }
  else
  {
    CurrentState[ Channel ] = LIN_NOT_OK;
    return( E_NOT_OK );
  }
}

#endif

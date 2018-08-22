//============================================================================
// PROJECT = RLIN3 Type RLIN3_UCIAPRLN
//============================================================================
// C O P Y R I G H T
//============================================================================
// Copyright (c) 2014 by Renesas Electronics (EUROPE) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
//============================================================================
//Purpose: RLIN3 Application Level
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
// Environment: Devices:          All featuring RLIN3_UCIAPRLN
//              Assembler:        GHS MULTI
//              C-Compiler:       GHS MULTI
//              Linker:           GHS MULTI
//              Debugger:         GHS MULTI
//============================================================================

#include <ree_types.h>

#include <map_rlin3.h>
#include <map_asmn.h>
#include <map_asmn_basic.h>

#include <string.h>
#include <stdio.h>

/*****************************************************************************/
/*                                                                           */
/*              LIN IMPLEMENTATION FOR RLIN3                                 */
/*                                                                           */
/*****************************************************************************/

/* Currently handled unit by interrupt and default vector counter support */

u08  RLIN3_LIN_ActiveUnit_u08 = RLIN3_NP;
u16  RLIN3_A_TRX_IRQ = 0;

/* LIN State Machine flags */

static u08 RLIN3_LINSF_State_u08[ RLIN3_MAXMACROS ] = 
           { RLIN3_A_LIN_STATE_IDLE, RLIN3_A_LIN_STATE_IDLE,
             RLIN3_A_LIN_STATE_IDLE, RLIN3_A_LIN_STATE_IDLE,
             RLIN3_A_LIN_STATE_IDLE, RLIN3_A_LIN_STATE_IDLE };

static bit RLIN3_LINSF_SlaveResponseEnable_bit[ RLIN3_MAXMACROS ] =
           { RLIN3_ERROR, RLIN3_ERROR, RLIN3_ERROR,
             RLIN3_ERROR, RLIN3_ERROR, RLIN3_ERROR };

/* LIN Buffer Handling flags */

static u08  RLIN3_LINMF_TableIndex_u08[ RLIN3_MAXMACROS ] = 
            { RLIN3_A_LIN_MAXTABLELENGTH, RLIN3_A_LIN_MAXTABLELENGTH,
              RLIN3_A_LIN_MAXTABLELENGTH, RLIN3_A_LIN_MAXTABLELENGTH,
              RLIN3_A_LIN_MAXTABLELENGTH, RLIN3_A_LIN_MAXTABLELENGTH };
              
static u08  RLIN3_LINMF_CurTable_u08[ RLIN3_MAXMACROS ]   = 
            { 0, 0, 0, 0, 0, 0 };
            
static u08  RLIN3_LINMF_TableStart_u08[ RLIN3_MAXMACROS ] = 
            { 1, 1, 1, 1, 1, 1 };

static struct rlin3_a_lintable_entry RLIN3_LINM_Buffer[ RLIN3_MAXMACROS ];

/*****************************************************************************/
/*                                                                           */
/*              INTERRUPT ROUTINES OF STANDARD UART                          */
/*                                                                           */
/*****************************************************************************/

void RLIN3_A_IRQSend( void )
{
  RLIN3_A_TRX_IRQ++;
}

/*****************************************************************************/
/*                                                                           */
/*              STANDARD SUPPORT FUNCTIONS FOR RLIN3                         */
/*                                                                           */
/*****************************************************************************/

bit RLIN3_SendString( u08   UnitNumber_u08,
                      char *SendString,
                      u08   TTYMode_u08 )
{
  bit SendStatus_bit = RLIN3_TRANSFER_OK;
  u16 length_u16;
  u16 pos_u16;
  
  length_u16 = ( u16 )strlen( SendString );

  for( pos_u16=0; pos_u16<length_u16; pos_u16++ ) {
    
    SendStatus_bit = RLIN3_SendByte( UnitNumber_u08, SendString[ pos_u16 ] );
    if( SendStatus_bit != RLIN3_TRANSFER_OK ) break;
    
    if( ( TTYMode_u08 == RLIN3_A_TTYMODE_CRLF ) &&
        ( SendString[ pos_u16 ] == '\n' ) ) {
      SendStatus_bit = RLIN3_SendByte( UnitNumber_u08, 0x0D );
      if( SendStatus_bit != RLIN3_TRANSFER_OK ) break;
    }
  }
  return( SendStatus_bit );
}

bit RLIN3_SendChar( u08           UnitNumber_u08,
                    unsigned char SendChar,
                    u08           TTYMode_u08 )
{
  bit SendStatus_bit = RLIN3_TRANSFER_OK;
  u08 digit_u08;
  u08 base_u08 = 100;

  if ( SendChar > 0 )
  {
    while (SendChar/base_u08 == 0)
    {
      base_u08 /= 10;
    }
    do
    {
      digit_u08 = SendChar/base_u08;
      SendStatus_bit = RLIN3_SendByte( UnitNumber_u08, ( u08 )(digit_u08+0x30) );
      if( SendStatus_bit != RLIN3_TRANSFER_OK ) break;
      SendChar = SendChar - base_u08 * digit_u08;
      base_u08 /= 10;    
    } while (base_u08);
  }
  else
  {
    SendStatus_bit = RLIN3_SendByte( UnitNumber_u08, ( u08 )(0+0x30) );
    if( SendStatus_bit != RLIN3_TRANSFER_OK ) return(SendStatus_bit);
  }
  
  if( TTYMode_u08 == RLIN3_A_TTYMODE_CRLF )
  {
      SendStatus_bit = RLIN3_SendByte( UnitNumber_u08, '\n' );
      if( SendStatus_bit != RLIN3_TRANSFER_OK ) return(SendStatus_bit);
      
      SendStatus_bit = RLIN3_SendByte( UnitNumber_u08, 0x0D );
      if( SendStatus_bit != RLIN3_TRANSFER_OK ) return(SendStatus_bit);
  }
  
  return( SendStatus_bit );
}

bit RLIN3_SendInt( u08          UnitNumber_u08,
                   unsigned int SendInt,
                   u08          TTYMode_u08 )
{
  bit SendStatus_bit = RLIN3_TRANSFER_OK;
  u08 digit_u08;
  unsigned int base = 1000000000;

  if ( SendInt > 0 )
  {
    while (SendInt/base == 0)
    {
      base /= 10;
    }
    do
    {
      digit_u08 = ( u08 )( SendInt/base );
      SendStatus_bit = RLIN3_SendByte( UnitNumber_u08, ( u08 )(digit_u08+0x30) );
      if( SendStatus_bit != RLIN3_TRANSFER_OK ) break;
      SendInt = SendInt - base * digit_u08;
      base /= 10;    
    } while (base);
  }
  else
  {
    SendStatus_bit = RLIN3_SendByte( UnitNumber_u08, ( u08 )(0+0x30) );
    if( SendStatus_bit != RLIN3_TRANSFER_OK ) return(SendStatus_bit);
  }
  
  if( TTYMode_u08 == RLIN3_A_TTYMODE_CRLF )
  {
      SendStatus_bit = RLIN3_SendByte( UnitNumber_u08, '\n' );
      if( SendStatus_bit != RLIN3_TRANSFER_OK ) return(SendStatus_bit);
      
      SendStatus_bit = RLIN3_SendByte( UnitNumber_u08, 0x0D );
      if( SendStatus_bit != RLIN3_TRANSFER_OK ) return(SendStatus_bit);
  }
  
  return( SendStatus_bit );
}

bit RLIN3_ReceiveString( u08   UnitNumber_u08,
                         char *ReceiveString,
                         u16   ReceiveLength_u16,
                         u32   TimeOutCount_u32 )
{
  bit ReceiveStatus_bit;
  u16 ActualReceived_u16 = 0;
  u32 ActualTimeOut_u32  = 0L;

  do 
  {
    ReceiveStatus_bit = RLIN3_ReceiveByte( UnitNumber_u08,
                        ( pu08 )( &ReceiveString[ ActualReceived_u16 ] ) );

    if( ReceiveStatus_bit == RLIN3_TRANSFER_OK ) 
    {
      ActualReceived_u16++;
      ActualTimeOut_u32 = 0L;
    }
    else 
    {
      ActualTimeOut_u32++;
      if( ActualTimeOut_u32 < TimeOutCount_u32 ) 
      {
	      ReceiveStatus_bit = RLIN3_TRANSFER_OK;
      }
    }       
  } while( ( ActualReceived_u16 < ReceiveLength_u16 ) &&
           ( ReceiveStatus_bit == RLIN3_TRANSFER_OK ) );
  
  if( ActualReceived_u16 == ReceiveLength_u16 ) return( RLIN3_TRANSFER_OK );
  else
  {
    return( RLIN3_ERROR );
  }
}

bit RLIN3_ReceiveUChar( u08            UnitNumber_u08,
                        u16            ReceiveLength_u16,
                        char          *RequestString,
                        unsigned char *Result,
                        pu08           ScanState_pu08 )
{
  bit  UARTStatus_bit;
  bit  ReceiveStatus_bit;
  s16  ActualReceived_s16 = 0;
  int  IntResult;
  char InputBuffer[ RLIN3_A_RECBUFLEN ];

  if( ReceiveLength_u16 >= RLIN3_A_RECBUFLEN ) return( RLIN3_ERROR );

  UARTStatus_bit = RLIN3_SendString( UnitNumber_u08, RequestString,
                                     RLIN3_A_TTYMODE_CR );
  if( UARTStatus_bit != RLIN3_TRANSFER_OK ) return( UARTStatus_bit );

  do 
  {
    ReceiveStatus_bit = RLIN3_ReceiveByte( UnitNumber_u08,
                        ( pu08 )( &InputBuffer[ ActualReceived_s16 ] ) );

    if( ReceiveStatus_bit == RLIN3_TRANSFER_OK ) 
    {
      RLIN3_SendByte( UnitNumber_u08, ( u08 )InputBuffer[ ActualReceived_s16 ] );
      ActualReceived_s16++;

      if( InputBuffer[ ActualReceived_s16 - 1 ] < ' ' ) 
      {
        if( InputBuffer[ ActualReceived_s16 - 1 ] == 0x08 ) 
        {
          InputBuffer[ ActualReceived_s16 - 1 ] = 0x00;
          ActualReceived_s16 -= 2;
          if( ActualReceived_s16 < 0 ) ActualReceived_s16 = 0;
        }
        continue;
      }
    }
  } while( ( ActualReceived_s16 < ReceiveLength_u16 ) &&
           ( InputBuffer[ ActualReceived_s16 - 1 ] != 0x0D ) &&
           ( InputBuffer[ ActualReceived_s16 - 1 ] != 0x0A ) );
  
  *ScanState_pu08 = ( u08 )sscanf( InputBuffer, "%d", &IntResult );
  *Result         = ( unsigned char )IntResult;

  return( UARTStatus_bit );
}

bit RLIN3_ReceiveFloat( u08    UnitNumber_u08,
                        u16    ReceiveLength_u16,
                        char  *RequestString,
                        float *Result,
                        pu08   ScanState_pu08 )
{
  bit  UARTStatus_bit;
  bit  ReceiveStatus_bit;
  s16  ActualReceived_s16 = 0;
  char InputBuffer[ RLIN3_A_RECBUFLEN ];

  if( ReceiveLength_u16 >= RLIN3_A_RECBUFLEN ) return( RLIN3_ERROR );

  UARTStatus_bit = RLIN3_SendString( UnitNumber_u08, RequestString,
                                     RLIN3_A_TTYMODE_CR );
  if( UARTStatus_bit != RLIN3_TRANSFER_OK ) return( UARTStatus_bit );

  do 
  {
    ReceiveStatus_bit = RLIN3_ReceiveByte( UnitNumber_u08,
                        ( pu08 )( &InputBuffer[ ActualReceived_s16 ] ) );

    if( ReceiveStatus_bit == RLIN3_TRANSFER_OK ) {

      RLIN3_SendByte( UnitNumber_u08, ( u08 )InputBuffer[ ActualReceived_s16 ] );
      ActualReceived_s16++;

      if( InputBuffer[ ActualReceived_s16 - 1 ] < ' ' ) 
      {
        if( InputBuffer[ ActualReceived_s16 - 1 ] == 0x08 ) 
        {
          InputBuffer[ ActualReceived_s16 - 1 ] = 0x00;
          ActualReceived_s16 -= 2;
          if( ActualReceived_s16 < 0 ) ActualReceived_s16 = 0;
        }
        continue;
      }
    }
  } while( ( ActualReceived_s16 < ReceiveLength_u16) &&
           ( InputBuffer[ ActualReceived_s16 - 1 ] != 0x0D ) &&
           ( InputBuffer[ ActualReceived_s16 - 1 ] != 0x0A ) );
  
  *ScanState_pu08 = ( unsigned char )sscanf( InputBuffer, "%f", Result );

  return( UARTStatus_bit );
}

bit RLIN3_ReceiveInteger( u08    UnitNumber_u08,
                          u16    ReceiveLength_u16,
                          char  *RequestString,
                          int   *Result,
                          pu08   ScanState_pu08 )
{
  bit  UARTStatus_bit;
  bit  ReceiveStatus_bit;
  u08  ReceiveMode_u08    = RLIN3_A_DECMODE;
  s16  ActualReceived_s16 = 0;
  char InputBuffer[ RLIN3_A_RECBUFLEN ];
  char ActualDisplayBuffer[ 20 ];

  if( ReceiveLength_u16 >= RLIN3_A_RECBUFLEN ) return( RLIN3_ERROR );

  UARTStatus_bit = RLIN3_SendString( UnitNumber_u08, RequestString,
                                     RLIN3_A_TTYMODE_CR );
  if( UARTStatus_bit != RLIN3_TRANSFER_OK ) return( UARTStatus_bit );

  if( *Result >= 0 ) {

    sprintf( ActualDisplayBuffer, "(%d [%XH]) ", *Result, *Result );
    UARTStatus_bit = RLIN3_SendString( UnitNumber_u08, ActualDisplayBuffer,
                                       RLIN3_A_TTYMODE_CR );
    if( UARTStatus_bit != RLIN3_TRANSFER_OK ) return( UARTStatus_bit );
  }

  do 
  {
    ReceiveStatus_bit = RLIN3_ReceiveByte( UnitNumber_u08,
                        ( pu08 )( &InputBuffer[ ActualReceived_s16 ] ) );

    if( ReceiveStatus_bit == RLIN3_TRANSFER_OK ) 
    {
      RLIN3_SendByte( UnitNumber_u08, ( u08 )InputBuffer[ ActualReceived_s16 ] );

      if( ( InputBuffer[ ActualReceived_s16 ] == 'H' ) || 
          ( InputBuffer[ ActualReceived_s16 ] == 'h' ) ) 
      {
        ReceiveMode_u08 = RLIN3_A_HEXMODE;
      }
      else 
      {
        ActualReceived_s16++;
        if( InputBuffer[ ActualReceived_s16 - 1 ] < ' ' ) 
        {
          if( InputBuffer[ ActualReceived_s16 - 1 ] == 0x08 ) 
          {
            InputBuffer[ ActualReceived_s16 - 1 ] = 0x00;
            ActualReceived_s16 -= 2;
            if( ActualReceived_s16 < 0 ) ActualReceived_s16 = 0;
          }
          continue;
        }
      }
    }
  } while( ( ActualReceived_s16 < ReceiveLength_u16 ) &&
           ( InputBuffer[ ActualReceived_s16 - 1 ] != 0x0D ) &&
           ( InputBuffer[ ActualReceived_s16 - 1 ] != 0x0A ) );

  if( ActualReceived_s16 > 1 ) {
    
    InputBuffer[ ActualReceived_s16 ] = 0;
    
    switch( ReceiveMode_u08 )
    {
 
    case RLIN3_A_DECMODE:
      *ScanState_pu08 = ( unsigned char )sscanf( InputBuffer, "%d", Result );
      break;

    case RLIN3_A_HEXMODE:
      *ScanState_pu08 = ( unsigned char )sscanf( InputBuffer, "%x", Result );
      break;

    default:
      return( RLIN3_ERROR );
    }
  }
  return( UARTStatus_bit );
}

bit RLIN3_ReceiveULong( u08            UnitNumber_u08,
                        u16            ReceiveLength_u16,
                        char          *RequestString,
                        unsigned long *Result,
                        pu08           ScanState_pu08 )
{
  bit  UARTStatus_bit;
  bit  ReceiveStatus_bit;
  u08  ReceiveMode_u08    = RLIN3_A_DECMODE;
  s16  ActualReceived_s16 = 0;
  char InputBuffer[ RLIN3_A_RECBUFLEN ];
  char ActualDisplayBuffer[ 20 ];

  if( ReceiveLength_u16 >= RLIN3_A_RECBUFLEN ) return( RLIN3_ERROR );

  UARTStatus_bit = RLIN3_SendString( UnitNumber_u08, RequestString,
                                     RLIN3_A_TTYMODE_CR );
  if( UARTStatus_bit != RLIN3_TRANSFER_OK ) return( UARTStatus_bit );

  sprintf( ActualDisplayBuffer, "(%ld [%lXH]) ", *Result, *Result );
  UARTStatus_bit = RLIN3_SendString( UnitNumber_u08, ActualDisplayBuffer,
                                     RLIN3_A_TTYMODE_CR );
  if( UARTStatus_bit != RLIN3_TRANSFER_OK ) return( UARTStatus_bit );

  do 
  {
    ReceiveStatus_bit = RLIN3_ReceiveByte( UnitNumber_u08,
                        ( pu08 )( &InputBuffer[ ActualReceived_s16 ] ) );

    if( ReceiveStatus_bit == RLIN3_TRANSFER_OK ) {

      RLIN3_SendByte( UnitNumber_u08, ( u08 )InputBuffer[ ActualReceived_s16 ] );

      if( ( InputBuffer[ ActualReceived_s16 ] == 'H' ) || 
          ( InputBuffer[ ActualReceived_s16 ] == 'h' ) ) 
      {
        ReceiveMode_u08 = RLIN3_A_HEXMODE;
      }
      else 
      {
        ActualReceived_s16++;
        if( InputBuffer[ ActualReceived_s16 - 1 ] < ' ' ) 
        {
          if( InputBuffer[ ActualReceived_s16 - 1 ] == 0x08 ) 
          {
            InputBuffer[ ActualReceived_s16 - 1 ] = 0x00;
            ActualReceived_s16 -= 2;
            if( ActualReceived_s16 < 0 ) ActualReceived_s16 = 0;
          }
          continue;
        }
      }
    }
  } while( ( ActualReceived_s16 < ReceiveLength_u16 ) &&
           ( InputBuffer[ ActualReceived_s16 - 1 ] != 0x0D ) &&
           ( InputBuffer[ ActualReceived_s16 - 1 ] != 0x0A ) );

  if( ActualReceived_s16 > 1 ) {
    
    InputBuffer[ ActualReceived_s16 ] = 0;
    
    switch( ReceiveMode_u08 ) 
    {
      
    case RLIN3_A_DECMODE:
      *ScanState_pu08 = ( unsigned char )sscanf( InputBuffer, "%ld", Result );
      break;

    case RLIN3_A_HEXMODE:
      *ScanState_pu08 = ( unsigned char )sscanf( InputBuffer, "%lx", Result );
      break;

    default:
      return( RLIN3_ERROR );
    }
  }
  return( UARTStatus_bit );
}

/*****************************************************************************/
/*                                                                           */
/*              LIN IMPLEMENTATION FOR RLIN3                                 */
/*                                                                           */
/*****************************************************************************/

/* LIN Interrupt vectors */

void RLIN3_LINS_IRQSend( void )
{
  u08 HeaderReceived_u08;
  u08 DataReceived_u08;
  u08 DataTransmitted_u08;
  u08 PID_u08;
  
  if( RLIN3_LIN_ActiveUnit_u08 == RLIN3_NP ) return;  /* invalid channel */
    
  RLIN3_LINGetStatus( RLIN3_LIN_ActiveUnit_u08,
                      &HeaderReceived_u08,
                      &DataReceived_u08,
                      &DataTransmitted_u08,
                      &PID_u08 );

  switch( RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] )
  {
    case RLIN3_A_LIN_STATE_TXDATA:
      if( !DataTransmitted_u08 )
      {
        RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_DLLERROR;
      }
      else
      {
        RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_IDLE;
        RLIN3_LINSReceiveAction( RLIN3_LIN_ActiveUnit_u08,
                                 RLIN3_A_GETHEADER,
                                 0,
                                 0 );
      }
      break;
      
    default:
      if( !( RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] & RLIN3_A_LIN_STATE_ERROR ) )
        RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_DLLERROR;
      break;      
  }
}

void RLIN3_LINS_IRQReceive( void )
{
  u08 HeaderReceived_u08;
  u08 DataReceived_u08;
  u08 DataTransmitted_u08;
  u08 PID_u08;
  u08 TableIndex_u08;
  u08 DataIndex_u08;
  u08 OperationMode_u08;
    
  if( RLIN3_LIN_ActiveUnit_u08 == RLIN3_NP ) return;  /* invalid channel */
    
  RLIN3_LINGetStatus( RLIN3_LIN_ActiveUnit_u08,
                      &HeaderReceived_u08,
                      &DataReceived_u08,
                      &DataTransmitted_u08,
                      &PID_u08 );
                        
  switch( RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] )
  {
    case RLIN3_A_LIN_STATE_SLEEP:
      RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_WAKEUP;
      break;
      
    case RLIN3_A_LIN_STATE_IDLE:
    case RLIN3_A_LIN_STATE_NEWSDATA:
      if( HeaderReceived_u08 )
      {
        for( TableIndex_u08 = 0;
             TableIndex_u08 < RLIN3_A_LIN_MAXTABLELENGTH;
             TableIndex_u08++ )
        {
          if( ( RLIN3_A_TAB_SLAVE_BASE[ TableIndex_u08 ]
                                        .Type_u08 == RLIN3_A_NO ) ||
              ( RLIN3_A_TAB_SLAVE_BASE[ TableIndex_u08 ]
                                         .PID_u08 == PID_u08 ) )
          {
            break;
          }
        }
        switch( RLIN3_A_TAB_SLAVE_BASE[ TableIndex_u08 ].Type_u08 )
        {
          case RLIN3_A_NO:
            if( RLIN3_A_TAB_SLAVE_BASE[ TableIndex_u08 ].PID_u08 == PID_u08 )
            {                /* verify the reception of a SLEEP instruction */
              RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_RXSLEEP;
              RLIN3_LINMF_TableIndex_u08[ RLIN3_LIN_ActiveUnit_u08 ] = TableIndex_u08;            
              RLIN3_LINSReceiveAction( RLIN3_LIN_ActiveUnit_u08,
                                       RLIN3_A_GETMESSAGE, 
                                       ( u16 )( RLIN3_A_TAB_SLAVE_BASE
                                       [ TableIndex_u08 ].DataLength_u08 ),
                                       RLIN3_CHECKSUM_CLASSIC ); 
                                       /* sleep command has standard CHS */
            }
            else
            {                /* the PID does not match - skip the message */
              RLIN3_LINSReceiveAction( RLIN3_LIN_ActiveUnit_u08,
                                       RLIN3_A_SKIPMESSAGE, 0,
                                       RLIN3_A_LIN_ENHANCEDCHKSUM );
            }
            break;
            
          case RLIN3_A_TX:   /* PID matches, a response must be sent */
            if( RLIN3_LINSF_SlaveResponseEnable_bit[ RLIN3_LIN_ActiveUnit_u08 ] == RLIN3_OK )
            {                /* give response in case that this is activated */
              RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_TXDATA;    
              RLIN3_LINMF_TableIndex_u08[ RLIN3_LIN_ActiveUnit_u08 ] = TableIndex_u08;

              for( DataIndex_u08 = 0;
                   DataIndex_u08 < RLIN3_A_TAB_SLAVE_BASE
                                   [ RLIN3_LINMF_TableIndex_u08[ RLIN3_LIN_ActiveUnit_u08 ] ]
                                   .DataLength_u08;
                   DataIndex_u08++ )
              {
                RLIN3_LINM_Buffer[ RLIN3_LIN_ActiveUnit_u08 ]
                                       .Data[ DataIndex_u08 ] = 
                                       RLIN3_A_TAB_SLAVE_BASE[ TableIndex_u08 ]
                                                             .Data[ DataIndex_u08 ];
              }

              RLIN3_LINSendMessage( RLIN3_LIN_ActiveUnit_u08,
                                    RLIN3_A_TAB_SLAVE_BASE[ TableIndex_u08 ]
                                                              .PID_u08,
                                    ( u16 )( RLIN3_A_TAB_SLAVE_BASE
                                            [ TableIndex_u08 ].DataLength_u08 ),
                                    RLIN3_A_LIN_ENHANCEDCHKSUM,
                                    RLIN3_RESPONSE_TRANSMIT,
                                    &RLIN3_LINM_Buffer[ RLIN3_LIN_ActiveUnit_u08 ]
                                                       .Data[ 0 ],
                                    &OperationMode_u08 );
            }
            else           /* we are not yet allowed to give responses */
            {
              RLIN3_LINSReceiveAction( RLIN3_LIN_ActiveUnit_u08,
                                       RLIN3_A_SKIPMESSAGE, 0,
                                       RLIN3_A_LIN_ENHANCEDCHKSUM );
            }
            break;
            
          case RLIN3_A_RX:   /* PID matches, a response must be received */
            RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_RXDATA;
            RLIN3_LINMF_TableIndex_u08[ RLIN3_LIN_ActiveUnit_u08 ] = TableIndex_u08;            
            RLIN3_LINSReceiveAction( RLIN3_LIN_ActiveUnit_u08,
                                     RLIN3_A_GETMESSAGE, 
                                     ( u16 )( RLIN3_A_TAB_SLAVE_BASE
                                     [ TableIndex_u08 ].DataLength_u08 ),
                                     RLIN3_A_LIN_ENHANCEDCHKSUM );
            break;
            
          default:
            RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_FSMERROR;
            break;
        }
      }
      else
      {
        RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_UNEXRECV;
      }
      break;
      
    case RLIN3_A_LIN_STATE_RXSLEEP:
      if( !DataReceived_u08 )
      {
        RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_UNEXRECV;
      }
      else  /* verify the validity of the SLEEP message by data content */
      {
        RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_IDLE;
        RLIN3_LINReceiveMessage( RLIN3_LIN_ActiveUnit_u08,
                                 RLIN3_A_TAB_SLAVE_BASE[ RLIN3_LINMF_TableIndex_u08
                                                       [ RLIN3_LIN_ActiveUnit_u08 ] ]
                                                        .DataLength_u08,
                                &RLIN3_LINM_Buffer[ RLIN3_LIN_ActiveUnit_u08 ]
                                                    .Data[ 0 ] );

        RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_SLEEP;
        
        for( TableIndex_u08 = 0;
             TableIndex_u08 < RLIN3_A_TAB_SLAVE_BASE
                              [ RLIN3_LINMF_TableIndex_u08[ RLIN3_LIN_ActiveUnit_u08 ] ]
                              .DataLength_u08;
             TableIndex_u08++ )
        {
          if( RLIN3_LINM_Buffer[ RLIN3_LIN_ActiveUnit_u08 ].Data[ TableIndex_u08 ] !=
              RLIN3_A_TAB_SLAVE_BASE[ RLIN3_LINMF_TableIndex_u08
                                    [ RLIN3_LIN_ActiveUnit_u08 ] ]
                                     .Data[ TableIndex_u08 ] )
          {
            RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_IDLE;
          }
        }
        if( RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] == RLIN3_A_LIN_STATE_IDLE )
        {
          RLIN3_LINSReceiveAction( RLIN3_LIN_ActiveUnit_u08,
                                   RLIN3_A_GETHEADER,
                                   0,
                                   0 );
        }
      }
      break;
      
    case RLIN3_A_LIN_STATE_RXDATA:
      if( !DataReceived_u08 )
      {
        RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_UNEXRECV;
      }
      else  /* receive response and trigger new header reception */
      {
        RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_NEWSDATA;
        RLIN3_LINReceiveMessage( RLIN3_LIN_ActiveUnit_u08,
                                 RLIN3_A_TAB_SLAVE_BASE[ RLIN3_LINMF_TableIndex_u08
                                                       [ RLIN3_LIN_ActiveUnit_u08 ] ]
                                                         .DataLength_u08,
                                &RLIN3_LINM_Buffer[ RLIN3_LIN_ActiveUnit_u08 ]
                                                   .Data[ 0 ] );

        for( DataIndex_u08 = 0;
             DataIndex_u08 < RLIN3_A_TAB_SLAVE_BASE
                             [ RLIN3_LINMF_TableIndex_u08[ RLIN3_LIN_ActiveUnit_u08 ] ]
                             .DataLength_u08;
             DataIndex_u08++ )
        {
          RLIN3_A_TAB_SLAVE_BASE[ RLIN3_LINMF_TableIndex_u08
                                [ RLIN3_LIN_ActiveUnit_u08 ] ]
                                 .Data[ DataIndex_u08 ] =
                                 RLIN3_LINM_Buffer[ RLIN3_LIN_ActiveUnit_u08 ]
                                 .Data[ DataIndex_u08 ];
        }

        RLIN3_LINSReceiveAction( RLIN3_LIN_ActiveUnit_u08,
                                 RLIN3_A_GETHEADER,
                                 0,
                                 0 );
      }
      break;

    default:
      if( !(RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] & RLIN3_A_LIN_STATE_ERROR ) )
        RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_UNEXRECV;
      break;
  }
}

void RLIN3_LINM_IRQSend( void )
{
  u08 HeaderReceived_u08;
  u08 DataReceived_u08;
  u08 DataTransmitted_u08;
  u08 PID_u08;
  
  if( RLIN3_LIN_ActiveUnit_u08 == RLIN3_NP ) return;  /* invalid channel */
    
  RLIN3_LINGetStatus( RLIN3_LIN_ActiveUnit_u08,
                      &HeaderReceived_u08,
                      &DataReceived_u08,
                      &DataTransmitted_u08,
                      &PID_u08 );
                        
  switch( RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] )
  {
    case RLIN3_A_LIN_STATE_TXBREAK:
      if( DataTransmitted_u08 )
      {
        if( RLIN3_A_TAB_MASTER_BASE[ RLIN3_LINMF_CurTable_u08
                                   [ RLIN3_LIN_ActiveUnit_u08 ] ]
                                   [ RLIN3_LINMF_TableIndex_u08
                                   [ RLIN3_LIN_ActiveUnit_u08 ] ].Type_u08 ==
                                     RLIN3_A_NO )
        {
          RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_SLEEP;
        }
        else
        {
          RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_IDLE;
        }
      }
      else
      {
        RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_FSMERROR;
      }
      break;

    case RLIN3_A_LIN_STATE_WAKEUP:
      RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_IDLE;
      break;
      
    default:
      if( !(RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] & RLIN3_A_LIN_STATE_ERROR ) )
        RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_FSMERROR;
      break;
  }
}

void RLIN3_LINM_IRQReceive( void )
{
  u08 HeaderReceived_u08;
  u08 DataReceived_u08;
  u08 DataTransmitted_u08;
  u08 DataIndex_u08;
  u08 PID_u08;
  
  if( RLIN3_LIN_ActiveUnit_u08 == RLIN3_NP ) return;  /* invalid channel */
    
  RLIN3_LINGetStatus( RLIN3_LIN_ActiveUnit_u08,
                      &HeaderReceived_u08,
                      &DataReceived_u08,
                      &DataTransmitted_u08,
                      &PID_u08 );

  switch( RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] )
  {
    case RLIN3_A_LIN_STATE_TXBREAK:
      if( DataReceived_u08 )
      {
        RLIN3_LINReceiveMessage( RLIN3_LIN_ActiveUnit_u08,
                                 RLIN3_A_TAB_MASTER_BASE
                                      [ RLIN3_LINMF_CurTable_u08
                                      [ RLIN3_LIN_ActiveUnit_u08 ] ]
                                      [ RLIN3_LINMF_TableIndex_u08
                                      [ RLIN3_LIN_ActiveUnit_u08 ] ]
                                        .DataLength_u08,
                                 &RLIN3_LINM_Buffer
                                      [ RLIN3_LIN_ActiveUnit_u08 ]
                                        .Data[ 0 ] );

        for( DataIndex_u08 = 0;
             DataIndex_u08 < RLIN3_A_TAB_MASTER_BASE
                             [ RLIN3_LINMF_CurTable_u08[ RLIN3_LIN_ActiveUnit_u08 ] ]
                             [ RLIN3_LINMF_TableIndex_u08[ RLIN3_LIN_ActiveUnit_u08 ] ]
                             .DataLength_u08;
             DataIndex_u08++ )
        {
          RLIN3_A_TAB_MASTER_BASE[ RLIN3_LINMF_CurTable_u08[ RLIN3_LIN_ActiveUnit_u08 ] ]
                                 [ RLIN3_LINMF_TableIndex_u08[ RLIN3_LIN_ActiveUnit_u08 ] ]
                                 .Data[ DataIndex_u08 ] =
                                 RLIN3_LINM_Buffer[ RLIN3_LIN_ActiveUnit_u08 ]
                                 .Data[ DataIndex_u08 ];
        }

        RLIN3_A_TAB_MASTER_BASE[ RLIN3_LINMF_CurTable_u08[ RLIN3_LIN_ActiveUnit_u08 ] ]
                               [ RLIN3_LINMF_TableIndex_u08[ RLIN3_LIN_ActiveUnit_u08 ] ]
                               .Type_u08 = RLIN3_A_RX;
                            
        RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_IDLE;
      }
      else
      {
        RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_UNEXRECV;
      }
      break;

    case RLIN3_A_LIN_STATE_WAKEUP:
      RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_IDLE;
      break;
      
    default:
      if( !(RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] & RLIN3_A_LIN_STATE_ERROR ) )
        RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_UNEXRECV;
      break;
  }
}

void RLIN3_LINM_IRQError( void )
{
  u08 AnyError_u08;
  u08 BitError_u08;
  u08 DataConsistencyError_u08;
  u08 TimeoutError_u08;
  u08 FrameError_u08;
  u08 SyncFieldError_u08;
  u08 CheckSumError_u08;
  u08 IdentParityError_u08;
  u08 ResponsePreparationError_u08;
  
  if( RLIN3_LIN_ActiveUnit_u08 == RLIN3_NP ) return;  /* invalid channel */
    
  RLIN3_LINGetError( RLIN3_LIN_ActiveUnit_u08,
                     &AnyError_u08,
                     &BitError_u08,
                     &DataConsistencyError_u08,
                     &TimeoutError_u08,
                     &FrameError_u08,
                     &SyncFieldError_u08,
                     &CheckSumError_u08,
                     &IdentParityError_u08,
                     &ResponsePreparationError_u08 );

  if( AnyError_u08 )
  {
    if( DataConsistencyError_u08 ) RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = 
                                   RLIN3_A_LIN_STATE_DCCERROR;
    if( CheckSumError_u08 )        RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] =
                                   RLIN3_A_LIN_STATE_CHSERROR;
      
    if( ( RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] & RLIN3_A_LIN_STATE_ERROR ) !=
                                 RLIN3_A_LIN_STATE_ERROR )
    {
      RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = 
                             RLIN3_A_LIN_STATE_DLLERROR; /* default error */
    }
  }
}

void RLIN3_LINS_IRQError( void )
{
  u08 AnyError_u08;
  u08 BitError_u08;
  u08 DataConsistencyError_u08;
  u08 TimeoutError_u08;
  u08 FrameError_u08;
  u08 SyncFieldError_u08;
  u08 CheckSumError_u08;
  u08 IdentParityError_u08;
  u08 ResponsePreparationError_u08;
  
  if( RLIN3_LIN_ActiveUnit_u08 == RLIN3_NP ) return;  /* invalid channel */
    
  RLIN3_LINGetError( RLIN3_LIN_ActiveUnit_u08,
                     &AnyError_u08,
                     &BitError_u08,
                     &DataConsistencyError_u08,
                     &TimeoutError_u08,
                     &FrameError_u08,
                     &SyncFieldError_u08,
                     &CheckSumError_u08,
                     &IdentParityError_u08,
                     &ResponsePreparationError_u08 );

  if( AnyError_u08 )
  {
    if( DataConsistencyError_u08 )     RLIN3_LINSF_State_u08
                                     [ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_DCCERROR;
    if( CheckSumError_u08 )            RLIN3_LINSF_State_u08
                                     [ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_CHSERROR;
    if( IdentParityError_u08 )         RLIN3_LINSF_State_u08
                                     [ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_PIDERROR;
    if( ResponsePreparationError_u08 ) RLIN3_LINSF_State_u08
                                     [ RLIN3_LIN_ActiveUnit_u08 ] = RLIN3_A_LIN_STATE_RPRERROR;
            
    if( ( RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] & RLIN3_A_LIN_STATE_ERROR ) !=
                                 RLIN3_A_LIN_STATE_ERROR )
    {
      RLIN3_LINSF_State_u08[ RLIN3_LIN_ActiveUnit_u08 ] = 
                             RLIN3_A_LIN_STATE_DLLERROR; /* default error */
    }
  }
}

/* Global configuration of LIN mode */

bit RLIN3_LIN_SetMode( u08 UnitNumber_u08,
                       u08 LINMode_u08,
                       u32 Baudrate_u32,
                       flt Oscillator_Frequency_flt )
{
  bit UARTStatus_bit;
  u08 TableIndex_u08;
  
  UARTStatus_bit =  RLIN3_Reset( UnitNumber_u08 );
  UARTStatus_bit &= RLIN3_PortEnable( UnitNumber_u08 );
  
  RLIN3_LINSF_SlaveResponseEnable_bit[ UnitNumber_u08 ] = RLIN3_ERROR;
  
  switch( LINMode_u08 )
  {
    case RLIN3_MODE_LINMASTER:
      UARTStatus_bit &= RLIN3_LINEnableInterrupt( UnitNumber_u08,
                                                  RLIN3_SET,       /* TX */
                                                  RLIN3_SET,       /* RX */
                                                  RLIN3_SET,       /* ERR */
                                                  RLIN3_SET,       /* Bit error */
                                                  RLIN3_SET,       /* Phys. Bus error */
                                                  RLIN3_SET,       /* Timeout error */
                                                  RLIN3_SET,       /* Frame error */
                                                  RLIN3_CLEAR,     /* not applicable */
                                                  RLIN3_CLEAR,     /* not applicable */
                                                  RLIN3_CLEAR,     /* Frame Timeout */
                                                  RLIN3_CLEAR );   /* HEADER */   
      UARTStatus_bit &= RLIN3_LINSetConfig( UnitNumber_u08,
                                            Oscillator_Frequency_flt,
                                            RLIN3_MODE_LINMASTER,
                                            RLIN3_LINSTANDARD_V2,
                                            Baudrate_u32,
                                            RLIN3_SAMPLES_MASTER,
                                            RLIN3_CLOCK_FA,
                                            RLIN3_SBFSLAVE_SHORT,
                                            RLIN3_SBF15BITS,
                                            RLIN3_BDT4BITS,
                                            RLIN3_SPACE_HDRRESP_1BITS,
                                            RLIN3_SPACE_RESBYTE_1BITS,
                                            RLIN3_SAMPLE_SINGLE,
                                            RLIN3_TRIPLE_INT );
      UARTStatus_bit &= RLIN3_CreateInterrupt( UnitNumber_u08,
                                               RLIN3_IRQ_SEND,
                                               RLIN3_INTENABLEDEFAULT,
                                               RLIN3_LINM_IRQSend );
      UARTStatus_bit &= RLIN3_CreateInterrupt( UnitNumber_u08,
                                               RLIN3_IRQ_RECEIVE,
                                               RLIN3_INTENABLEDEFAULT,
                                               RLIN3_LINM_IRQReceive );
      UARTStatus_bit &= RLIN3_CreateInterrupt( UnitNumber_u08,
                                               RLIN3_IRQ_ERROR,
                                               RLIN3_INTENABLEDEFAULT,
                                               RLIN3_LINM_IRQError );
      break;
      
    case RLIN3_MODE_LINSLAVE_FIX:
      UARTStatus_bit &= RLIN3_LINEnableInterrupt( UnitNumber_u08,
                                                  RLIN3_SET,       /* TX */
                                                  RLIN3_SET,       /* RX */
                                                  RLIN3_SET,       /* ERR */
                                                  RLIN3_SET,       /* Bit error */
                                                  RLIN3_CLEAR,     /* not applicable */
                                                  RLIN3_SET,       /* Timeout error */
                                                  RLIN3_SET,       /* Frame error */
                                                  RLIN3_SET,       /* Sync error */
                                                  RLIN3_SET,       /* ID Parity error */
                                                  RLIN3_CLEAR,     /* Frame Timeout */
                                                  RLIN3_SET );     /* HEADER */   
       UARTStatus_bit &= RLIN3_LINSetConfig( UnitNumber_u08,
                                            Oscillator_Frequency_flt,
                                            RLIN3_MODE_LINSLAVE_FIX,
                                            RLIN3_LINSTANDARD_V2,
                                            Baudrate_u32,
                                            RLIN3_SAMPLES_SLAVE_FIX,
                                            RLIN3_CLOCK_FA,
                                            RLIN3_SBFSLAVE_SHORT,
                                            RLIN3_SBF15BITS,
                                            RLIN3_BDT1BITS,
                                            RLIN3_SPACE_HDRRESP_1BITS,
                                            RLIN3_SPACE_RESBYTE_1BITS,
                                            RLIN3_SAMPLE_SINGLE,
                                            RLIN3_TRIPLE_INT );
      UARTStatus_bit &= RLIN3_CreateInterrupt( UnitNumber_u08,
                                               RLIN3_IRQ_SEND,
                                               RLIN3_INTENABLEDEFAULT,
                                               RLIN3_LINS_IRQSend );
      UARTStatus_bit &= RLIN3_CreateInterrupt( UnitNumber_u08,
                                               RLIN3_IRQ_RECEIVE,
                                               RLIN3_INTENABLEDEFAULT,
                                               RLIN3_LINS_IRQReceive );
      UARTStatus_bit &= RLIN3_CreateInterrupt( UnitNumber_u08,
                                               RLIN3_IRQ_ERROR,
                                               RLIN3_INTENABLEDEFAULT,
                                               RLIN3_LINS_IRQError );
      break;

   case RLIN3_MODE_LINSLAVE_AUTO:
      UARTStatus_bit &= RLIN3_LINEnableInterrupt( UnitNumber_u08,
                                                  RLIN3_SET,       /* TX */
                                                  RLIN3_SET,       /* RX */
                                                  RLIN3_SET,       /* ERR */
                                                  RLIN3_SET,       /* Bit error */
                                                  RLIN3_CLEAR,     /* not applicable */
                                                  RLIN3_CLEAR,     /* TER not allowed */
                                                  RLIN3_SET,       /* Frame error */
                                                  RLIN3_SET,       /* Sync error */
                                                  RLIN3_SET,       /* ID Parity error */
                                                  RLIN3_CLEAR,     /* Frame Timeout */
                                                  RLIN3_SET );     /* HEADER */   
      UARTStatus_bit &= RLIN3_LINSetConfig( UnitNumber_u08,
                                            Oscillator_Frequency_flt,
                                            RLIN3_MODE_LINSLAVE_AUTO,
                                            RLIN3_LINSTANDARD_V2,
                                            Baudrate_u32,
                                            RLIN3_SAMPLES_SLAVE_AUTO,
                                            RLIN3_CLOCK_FA,
                                            RLIN3_SBFSLAVE_SHORT,
                                            RLIN3_SBF15BITS,
                                            RLIN3_BDT1BITS,
                                            RLIN3_SPACE_HDRRESP_1BITS,
                                            RLIN3_SPACE_RESBYTE_1BITS,
                                            RLIN3_SAMPLE_SINGLE,
                                            RLIN3_TRIPLE_INT );
      UARTStatus_bit &= RLIN3_CreateInterrupt( UnitNumber_u08,
                                               RLIN3_IRQ_SEND,
                                               RLIN3_INTENABLEDEFAULT,
                                               RLIN3_LINS_IRQSend );
      UARTStatus_bit &= RLIN3_CreateInterrupt( UnitNumber_u08,
                                               RLIN3_IRQ_RECEIVE,
                                               RLIN3_INTENABLEDEFAULT,
                                               RLIN3_LINS_IRQReceive );
      UARTStatus_bit &= RLIN3_CreateInterrupt( UnitNumber_u08,
                                               RLIN3_IRQ_ERROR,
                                               RLIN3_INTENABLEDEFAULT,
                                               RLIN3_LINS_IRQError );
      break;
      
    default:
      UARTStatus_bit = RLIN3_ERROR;
      break;
  }
  
  if( UARTStatus_bit != RLIN3_OK ) return( UARTStatus_bit );
  
  /* Initialize the data buffers for "no update activity" */
  
  for( TableIndex_u08 = 0;
       TableIndex_u08 < RLIN3_MAXMACROS;
       TableIndex_u08++ )
  {
    RLIN3_LINM_Buffer[ TableIndex_u08 ].Type_u08 = RLIN3_A_NO;
  }
  
  RLIN3_LINSF_State_u08[ UnitNumber_u08 ] = RLIN3_A_LIN_STATE_IDLE;

  if( ( LINMode_u08 == RLIN3_MODE_LINSLAVE_FIX ) ||
      ( LINMode_u08 == RLIN3_MODE_LINSLAVE_AUTO ) )
  {
    /* Activate SLAVE header reception */
    
    UARTStatus_bit = RLIN3_LINSReceiveAction( UnitNumber_u08,
                                              RLIN3_A_GETHEADER,
                                              0,
                                              0 );
                                              
  }
  
  return( UARTStatus_bit );
}

/*************************************************/
/* LIN Master Support Functions for upper layers */
/*************************************************/

bit RLIN3_LINM_SetTable( u08 UnitNumber_u08,
                         u08 Table_u08 )
{
  if( Table_u08 >= RLIN3_A_LIN_MASTERTABLES ) return( RLIN3_ERROR );
  
  RLIN3_LINMF_TableIndex_u08[ UnitNumber_u08 ] = 0;
  RLIN3_LINMF_TableStart_u08[ UnitNumber_u08 ] = 1;
  RLIN3_LINMF_CurTable_u08[ UnitNumber_u08 ]   = Table_u08;
  
  return( RLIN3_OK );
}

bit RLIN3_LINM_RestartTable( u08 UnitNumber_u08 )
{
  RLIN3_LINMF_TableIndex_u08[ UnitNumber_u08 ] = 0;
  RLIN3_LINMF_TableStart_u08[ UnitNumber_u08 ] = 1;
  
  return( RLIN3_OK );
}

bit RLIN3_LINM_SetTableContent( u08  UnitNumber_u08,
                                u08  TableIndex_u08,
                                pu08 DataArray_pu08 )
{
  u08 DataIndex_u08;
  u08 DataLength_u08;
  
  if( TableIndex_u08 >= RLIN3_A_LIN_MAXTABLELENGTH ) return( RLIN3_ERROR );
  
  DataLength_u08 = RLIN3_A_TAB_MASTER_BASE[ RLIN3_LINMF_CurTable_u08[ UnitNumber_u08 ] ]
                                          [ TableIndex_u08 ]
                                             .DataLength_u08;

  ASMN_DICOMMAND;

  for( DataIndex_u08 = 0;
       DataIndex_u08 < DataLength_u08;
       DataIndex_u08++ )
  {
    RLIN3_A_TAB_MASTER_BASE[ RLIN3_LINMF_CurTable_u08[ UnitNumber_u08 ] ]
                           [ TableIndex_u08 ].Data
                           [ DataIndex_u08 ] = *DataArray_pu08;
    DataArray_pu08++;
  }

  ASMN_EICOMMAND;

  return( RLIN3_OK );
}

bit RLIN3_LINM_NextTableContent( u08 UnitNumber_u08 )
{
  bit UARTStatus_bit;
  u08 DataIndex_u08;
  u08 PID_u08;
  u08 OperationMode_u08;
  
  /* wait on LIN idle state */
  
  if( ( RLIN3_LINSF_State_u08[ UnitNumber_u08 ] != RLIN3_A_LIN_STATE_IDLE ) &&
      ( RLIN3_LINSF_State_u08[ UnitNumber_u08 ] != RLIN3_A_LIN_STATE_WAKEUP ) )
  {
    return( RLIN3_ERROR );
  }
  
  /* move to the next master table entry to be executed */
  
  if( !RLIN3_LINMF_TableStart_u08[ UnitNumber_u08 ] )
  {
    RLIN3_LINMF_TableIndex_u08[ UnitNumber_u08 ]++;
    if( RLIN3_LINMF_TableIndex_u08[ UnitNumber_u08 ] > RLIN3_A_LIN_MAXTABLELENGTH )
      RLIN3_LINMF_TableIndex_u08[ UnitNumber_u08 ] = 0;
    if( RLIN3_A_TAB_MASTER_BASE[ RLIN3_LINMF_CurTable_u08[ UnitNumber_u08 ] ]
                               [ RLIN3_LINMF_TableIndex_u08[ UnitNumber_u08 ] ].Type_u08 ==
                                 RLIN3_A_NO )
      RLIN3_LINMF_TableIndex_u08[ UnitNumber_u08 ] = 0;
  }
  else
  {
    RLIN3_LINMF_TableIndex_u08[ UnitNumber_u08 ] = 0;
    RLIN3_LINMF_TableStart_u08[ UnitNumber_u08 ] = 0;
  }
  
  /* copy current table entry into buffer */
  
  RLIN3_LINM_Buffer[ UnitNumber_u08 ].Type_u08 = RLIN3_A_TAB_MASTER_BASE
                     [ RLIN3_LINMF_CurTable_u08[ UnitNumber_u08 ] ]
                     [ RLIN3_LINMF_TableIndex_u08[ UnitNumber_u08 ] ].PID_u08;
  RLIN3_LINM_Buffer[ UnitNumber_u08 ].Type_u08 = RLIN3_A_TAB_MASTER_BASE
                     [ RLIN3_LINMF_CurTable_u08[ UnitNumber_u08 ] ]
                     [ RLIN3_LINMF_TableIndex_u08[ UnitNumber_u08 ] ].PID_u08;
  RLIN3_LINM_Buffer[ UnitNumber_u08 ].DataLength_u08 = RLIN3_A_TAB_MASTER_BASE
                     [ RLIN3_LINMF_CurTable_u08[ UnitNumber_u08 ] ]
                     [ RLIN3_LINMF_TableIndex_u08[ UnitNumber_u08 ] ].DataLength_u08;

  for( DataIndex_u08 = 0;
       DataIndex_u08 < RLIN3_A_TAB_MASTER_BASE
                       [ RLIN3_LINMF_CurTable_u08[ UnitNumber_u08 ] ]
                       [ RLIN3_LINMF_TableIndex_u08[ UnitNumber_u08 ] ]
                       .DataLength_u08;
       DataIndex_u08++ )
  {
    RLIN3_LINM_Buffer[ UnitNumber_u08 ].Data[ DataIndex_u08 ] = RLIN3_A_TAB_MASTER_BASE
                       [ RLIN3_LINMF_CurTable_u08[ UnitNumber_u08 ] ]
                       [ RLIN3_LINMF_TableIndex_u08[ UnitNumber_u08 ] ]
                       .Data[ DataIndex_u08 ];
                       
  }

  /* initiate a master frame cycle */
  
  RLIN3_LINSF_State_u08[ UnitNumber_u08 ] = RLIN3_A_LIN_STATE_TXBREAK;
  
  PID_u08 = RLIN3_A_TAB_MASTER_BASE[ RLIN3_LINMF_CurTable_u08[ UnitNumber_u08 ] ]
                                   [ RLIN3_LINMF_TableIndex_u08[ UnitNumber_u08 ] ].
                                    PID_u08;
  
  UARTStatus_bit = RLIN3_LINSendMessage( UnitNumber_u08,
                                         PID_u08,
                                         RLIN3_A_TAB_MASTER_BASE
                                         [ RLIN3_LINMF_CurTable_u08
                                         [ UnitNumber_u08 ] ]
                                         [ RLIN3_LINMF_TableIndex_u08
                                         [ UnitNumber_u08 ] ].
                                         DataLength_u08,
                                         ( ( PID_u08 >= RLIN3_A_LIN_CLASSCHKSUMLIM ) ?
                                         RLIN3_CHECKSUM_CLASSIC : RLIN3_CHECKSUM_ENHANCED ),
                                         RLIN3_A_TAB_MASTER_BASE
                                         [ RLIN3_LINMF_CurTable_u08
                                         [ UnitNumber_u08 ] ]
                                         [ RLIN3_LINMF_TableIndex_u08
                                         [ UnitNumber_u08 ] ].
                                         Type_u08,
                                         RLIN3_LINM_Buffer[ UnitNumber_u08 ].Data,
                                         &OperationMode_u08 );

  return( UARTStatus_bit );
}

bit RLIN3_LINM_GetTableContent( u08  UnitNumber_u08,
                                u08  ReadTableIndex_u08,
                                pu08 DataArray_pu08 )
{
  u08 DataIndex_u08;
  
  if( ReadTableIndex_u08 >= RLIN3_A_LIN_MAXTABLELENGTH ) 
    return( RLIN3_ERROR );

  /* get the appropriate content from the master table */
  
  ASMN_DICOMMAND;

  for( DataIndex_u08 = 0;
       DataIndex_u08 < RLIN3_A_TAB_MASTER_BASE
                       [ RLIN3_LINMF_CurTable_u08[ UnitNumber_u08 ] ]
                       [ ReadTableIndex_u08 ].DataLength_u08;
       DataIndex_u08++ )
  {
    *DataArray_pu08 = RLIN3_A_TAB_MASTER_BASE[ RLIN3_LINMF_CurTable_u08
                                             [ UnitNumber_u08 ] ]
                                             [ ReadTableIndex_u08 ].Data
                                             [ DataIndex_u08 ];
    DataArray_pu08++;
  }
  
  ASMN_EICOMMAND;

  return( RLIN3_OK );
}

u08 RLIN3_LINM_GetStatus( u08 UnitNumber_u08 )
{
  u08 ErrorCode_u08;
  
  ErrorCode_u08 = RLIN3_LINSF_State_u08[ UnitNumber_u08 ] & RLIN3_A_LIN_STATE_APIMASK;
  
  if( ErrorCode_u08 & RLIN3_A_LIN_STATE_ERROR )
  {
    ErrorCode_u08 = RLIN3_LINSF_State_u08[ UnitNumber_u08 ];
    RLIN3_LINSF_State_u08[ UnitNumber_u08 ] = RLIN3_A_LIN_STATE_IDLE;
  }
  
  return( ErrorCode_u08 );
}

bit RLIN3_LINM_ResetFrame( u08 UnitNumber_u08 )
{
  u08 ErrorCode_u08;
  
  ErrorCode_u08 = RLIN3_LINSF_State_u08[ UnitNumber_u08 ] & RLIN3_A_LIN_STATE_APIMASK;
  
  if( !( ErrorCode_u08 & RLIN3_A_LIN_STATE_ERROR ) )
  {
    RLIN3_LINSF_State_u08[ UnitNumber_u08 ] = RLIN3_A_LIN_STATE_IDLE;
    return( RLIN3_OK );
  }
  else
  {
    return( RLIN3_ERROR );
  }
}

bit RLIN3_LINM_SetSleepState( u08 UnitNumber_u08 )
{
  bit UARTStatus_bit;
  u08 TableIndex_u08 = 0;
  u08 PID_u08;
  u08 OperationMode_u08;
    
  /* search sleep instruction in current master table */
  
  while( RLIN3_A_TAB_MASTER_BASE[ RLIN3_LINMF_CurTable_u08[ UnitNumber_u08 ] ]
                                [ TableIndex_u08 ].Type_u08 != RLIN3_A_NO )
  {
    TableIndex_u08++;
  }
  
  /* use sleep instruction and initiate a restart of the table */
  
  RLIN3_LINMF_TableIndex_u08[ UnitNumber_u08 ] = TableIndex_u08;
  RLIN3_LINMF_TableStart_u08[ UnitNumber_u08 ] = 1;
  
  /* initiate a master frame cycle */
  
  RLIN3_LINSF_State_u08[ UnitNumber_u08 ] = RLIN3_A_LIN_STATE_TXBREAK;
   
  PID_u08 = RLIN3_A_TAB_MASTER_BASE[ RLIN3_LINMF_CurTable_u08[ UnitNumber_u08 ] ]
                                   [ RLIN3_LINMF_TableIndex_u08[ UnitNumber_u08 ] ].
                                    PID_u08;

  UARTStatus_bit = RLIN3_LINSendMessage( UnitNumber_u08,
                                         PID_u08,
                                         RLIN3_A_TAB_MASTER_BASE
                                         [ RLIN3_LINMF_CurTable_u08
                                         [ UnitNumber_u08 ] ]
                                         [ RLIN3_LINMF_TableIndex_u08
                                         [ UnitNumber_u08 ] ].
                                         DataLength_u08,
                                         ( ( PID_u08 >= RLIN3_A_LIN_CLASSCHKSUMLIM ) ?
                                         RLIN3_CHECKSUM_CLASSIC : RLIN3_CHECKSUM_ENHANCED ),
                                         RLIN3_A_TAB_MASTER_BASE
                                         [ RLIN3_LINMF_CurTable_u08
                                         [ UnitNumber_u08 ] ]
                                         [ RLIN3_LINMF_TableIndex_u08
                                         [ UnitNumber_u08 ] ].
                                         Type_u08,
                                         RLIN3_A_TAB_MASTER_BASE
                                         [ RLIN3_LINMF_CurTable_u08
                                         [ UnitNumber_u08 ] ]
                                         [ RLIN3_LINMF_TableIndex_u08
                                         [ UnitNumber_u08 ] ].
                                         Data,
                                         &OperationMode_u08 );
  
  while( ( RLIN3_LINSF_State_u08[ UnitNumber_u08 ] != RLIN3_A_LIN_STATE_SLEEP ) &&
         ( ( RLIN3_LINSF_State_u08[ UnitNumber_u08 ] & RLIN3_A_LIN_STATE_ERROR ) !=
                                                       RLIN3_A_LIN_STATE_ERROR ) );
  
  if( RLIN3_LINSF_State_u08[ UnitNumber_u08 ] == RLIN3_A_LIN_STATE_SLEEP )
  {
    UARTStatus_bit &= RLIN3_LINReceiveWakeup( UnitNumber_u08 );
  }
  
  return( UARTStatus_bit );
}

bit RLIN3_LINM_SendWakeup( u08 UnitNumber_u08 )
{
  bit UARTStatus_bit;
  
  /* any error does not allow to wake up */
  
  if( ( RLIN3_LINSF_State_u08[ UnitNumber_u08 ] != RLIN3_A_LIN_STATE_IDLE ) &&
      ( RLIN3_LINSF_State_u08[ UnitNumber_u08 ] != RLIN3_A_LIN_STATE_SLEEP ) )
  {
    return( RLIN3_ERROR );
  }
  
  /* initiate the sending of the wake up pattern */
  
  RLIN3_LINSF_State_u08[ UnitNumber_u08 ] = RLIN3_A_LIN_STATE_WAKEUP;
  
  UARTStatus_bit = RLIN3_LINSendWakeup( UnitNumber_u08,
                                        RLIN3_WUPTL_8BITS );
  return( UARTStatus_bit );
}

/************************************************/
/* LIN Slave Support Functions for upper layers */
/************************************************/

bit RLIN3_LINS_SetTableContent( u08  TableIndex_u08,
                                pu08 DataArray_pu08 )
{
  u08 DataIndex_u08;
  u08 DataLength_u08;

  if( TableIndex_u08 >= RLIN3_A_LIN_MAXTABLELENGTH ) return( RLIN3_ERROR );
  
  DataLength_u08 = RLIN3_A_TAB_SLAVE_BASE[ TableIndex_u08 ]
                                             .DataLength_u08;
  
  ASMN_DICOMMAND;

  for( DataIndex_u08 = 0;
       DataIndex_u08 < DataLength_u08;
       DataIndex_u08++ )
  {
    RLIN3_A_TAB_SLAVE_BASE[ TableIndex_u08 ].Data
                          [ DataIndex_u08 ] = *DataArray_pu08;
    DataArray_pu08++;
  }

  ASMN_EICOMMAND;

  return( RLIN3_OK );
}

bit RLIN3_LINS_GetTableContent( u08  ReadTableIndex_u08,
                                pu08 Type_pu08,
                                pu08 DataLength_pu08,
                                pu08 DataArray_pu08 )
{
  u08 DataIndex_u08;
  u08 DataLength_u08;

  if( ReadTableIndex_u08 >= RLIN3_A_LIN_MAXTABLELENGTH ) 
    return( RLIN3_ERROR );
  
  DataLength_u08 = RLIN3_A_TAB_SLAVE_BASE[ ReadTableIndex_u08 ]
                                             .DataLength_u08;
  *DataLength_pu08 = DataLength_u08;
  *Type_pu08 = RLIN3_A_TAB_SLAVE_BASE[ ReadTableIndex_u08 ]
                                             .Type_u08;
  
  ASMN_DICOMMAND;
  
  for( DataIndex_u08 = 0;
       DataIndex_u08 < DataLength_u08;
       DataIndex_u08++ )
  {
    *DataArray_pu08 = RLIN3_A_TAB_SLAVE_BASE[ ReadTableIndex_u08 ].Data
                                            [ DataIndex_u08 ];
    DataArray_pu08++;
  }

  ASMN_EICOMMAND;

  return( RLIN3_OK );
}

bit RLIN3_LINS_SetTablePID( u08 TableIndex_u08,
                            u08 NewPID_u08 )
{
  if( TableIndex_u08 >= RLIN3_A_LIN_MAXTABLELENGTH ) return( RLIN3_ERROR );
  
  RLIN3_A_TAB_SLAVE_BASE[ TableIndex_u08 ].PID_u08 = NewPID_u08;

  return( RLIN3_OK );
}

void RLIN3_LINS_ActivateResponses( u08 UnitNumber_u08,
                                   bit Activation_bit )
{
  RLIN3_LINSF_SlaveResponseEnable_bit[ UnitNumber_u08 ] = Activation_bit;
}

bit RLIN3_LINS_SetSleepState( u08 UnitNumber_u08 )
{
  RLIN3_LINSF_State_u08[ UnitNumber_u08 ] = RLIN3_A_LIN_STATE_SLEEP;
  return( RLIN3_LINReceiveWakeup( UnitNumber_u08 ) );
}

bit RLIN3_LINS_SendWakeup( u08 UnitNumber_u08 )
{
  bit UARTStatus_bit;
  
  /* any error does not allow to wake up */
  
  if( ( RLIN3_LINSF_State_u08[ UnitNumber_u08 ] != RLIN3_A_LIN_STATE_IDLE ) &&
      ( RLIN3_LINSF_State_u08[ UnitNumber_u08 ] != RLIN3_A_LIN_STATE_SLEEP ) )
  {
    return( RLIN3_ERROR );
  }
  
  /* initiate the sending of the wake up pattern */
  
  RLIN3_LINSF_State_u08[ UnitNumber_u08 ] = RLIN3_A_LIN_STATE_WAKEUP;
  
  UARTStatus_bit = RLIN3_LINSendWakeup( UnitNumber_u08,
                                        RLIN3_WUPTL_8BITS );
                                        
  UARTStatus_bit &= RLIN3_LINSReceiveAction( UnitNumber_u08,
                                             RLIN3_A_GETHEADER,
                                             0,
                                             0 );

  return( UARTStatus_bit );
}

u08 RLIN3_LINS_GetStatus( u08 UnitNumber_u08, pu08 TableIndex_pu08 )
{
  u08 ErrorCode_u08;
  
  ErrorCode_u08 = RLIN3_LINSF_State_u08[ UnitNumber_u08 ] & RLIN3_A_LIN_STATE_APIMASK;
  
  if( ErrorCode_u08 == RLIN3_A_LIN_STATE_WAKEUP )
  {
    RLIN3_LINRestart( UnitNumber_u08 );
  }
  
  if( ( ErrorCode_u08 &  RLIN3_A_LIN_STATE_ERROR ) ||
      ( ErrorCode_u08 == RLIN3_A_LIN_STATE_WAKEUP ) )
  {
    ErrorCode_u08 = RLIN3_LINSF_State_u08[ UnitNumber_u08 ];
    RLIN3_LINSF_State_u08[ UnitNumber_u08 ] = RLIN3_A_LIN_STATE_IDLE;
    
    RLIN3_LINSReceiveAction( UnitNumber_u08,
                             RLIN3_A_GETHEADER,
                             0,
                             0 );
  }
  
  if( ErrorCode_u08 == RLIN3_A_LIN_STATE_NEWSDATA )
  {
    RLIN3_LINSF_State_u08[ UnitNumber_u08 ] = RLIN3_A_LIN_STATE_IDLE;
    *TableIndex_pu08 = RLIN3_LINMF_TableIndex_u08[ UnitNumber_u08 ];
  }
  
  return( ErrorCode_u08 );
}

/*****************************************************************************/
/*                                                                           */
/*              STANDARD TEST FUNCTIONS FOR RLIN3                            */
/*                                                                           */
/*****************************************************************************/

/* Reset Unit */

bit RLIN3_ResetAll( u08 UnitNumber_u08 )
{
  bit UARTStatus_bit = RLIN3_OK;

  UARTStatus_bit &= RLIN3_Reset( UnitNumber_u08 );
  UARTStatus_bit &= RLIN3_CreateInterrupt( UnitNumber_u08,
                                           RLIN3_IRQ_SEND,
                                           RLIN3_INTCLEAR,
                                           NULL );
  UARTStatus_bit &= RLIN3_CreateInterrupt( UnitNumber_u08,
                                           RLIN3_IRQ_RECEIVE,
                                           RLIN3_INTCLEAR,
                                           NULL );
  UARTStatus_bit &= RLIN3_CreateInterrupt( UnitNumber_u08,
                                           RLIN3_IRQ_ERROR,
                                           RLIN3_INTCLEAR,
                                           NULL );
  UARTStatus_bit &= RLIN3_CreateInterrupt( UnitNumber_u08,
                                           RLIN3_IRQ_COMMON,
                                           RLIN3_INTCLEAR,
                                           NULL );
  UARTStatus_bit &= RLIN3_PortDisable( UnitNumber_u08 );

  return( UARTStatus_bit );
}

/* Send character string in UART Mode, using selectable baud rate,
   all other UART parameters are fixed 
 */

bit RLIN3_UARTSendString( u08  UnitNumber_u08,
                          u32  Baudrate_u32,
                          pu08 String_pu08 )
{
  bit UARTStatus_bit = RLIN3_OK;
  
  RLIN3_A_TRX_IRQ = 0;
 
  UARTStatus_bit =  RLIN3_Reset( UnitNumber_u08 );
  UARTStatus_bit &= RLIN3_PortEnable( UnitNumber_u08 );
  UARTStatus_bit &= RLIN3_CreateInterrupt( UnitNumber_u08,
                                           RLIN3_IRQ_SEND,
                                           RLIN3_INTENABLEDEFAULT,
                                           RLIN3_A_IRQSend );
  UARTStatus_bit &= RLIN3_LegacyConfig( UnitNumber_u08,
                                        OSCILLATOR_FREQUENCY,
                                        Baudrate_u32,
                                        ASMN_MENUCOM_PARITY,
                                        ASMN_MENUCOM_CHLEN,
                                        ASMN_MENUCOM_STOP,
                                        ASMN_MENUCOM_DIR );
  UARTStatus_bit &= RLIN3_SendString( UnitNumber_u08,
                                      ( char* )String_pu08,
                                      ASMN_UARTMODECR );
                                      
  while( RLIN3_A_TRX_IRQ < strlen( ( char* )String_pu08 ) );
                                      
  UARTStatus_bit &= RLIN3_Reset( UnitNumber_u08 );
  UARTStatus_bit &= RLIN3_CreateInterrupt( UnitNumber_u08,
                                           RLIN3_IRQ_SEND,
                                           RLIN3_INTCLEAR,
                                           NULL );
  UARTStatus_bit &= RLIN3_PortDisable( UnitNumber_u08 );
  
  return( UARTStatus_bit );
}

/* Activate LIN Master with selectable table,
   generates a WUP and then executes the table
 */
 
bit RLIN3_LINMasterExecution( u08 UnitNumber_u08,
                              u08 TableNumber_u08,
                              u32 Baudrate_u32 )
{
  bit UARTStatus_bit = RLIN3_OK;
  u08 ErrorStatus;

  UARTStatus_bit =  RLIN3_LIN_SetMode( UnitNumber_u08, 
                                       RLIN3_MODE_LINMASTER, 
                                       Baudrate_u32,
                                       OSCILLATOR_FREQUENCY );
  UARTStatus_bit &= RLIN3_LINM_SetTable( UnitNumber_u08,
                                         TableNumber_u08 );
  UARTStatus_bit &= RLIN3_LINM_RestartTable( UnitNumber_u08 );

  do
  {
    UARTStatus_bit &= RLIN3_LINM_SendWakeup( UnitNumber_u08 );
    
  } while( ( RLIN3_LINM_GetStatus( UnitNumber_u08 ) != RLIN3_A_LIN_STATE_IDLE ) &&
           ( RLIN3_LINM_GetStatus( UnitNumber_u08 ) != RLIN3_A_LIN_STATE_WAKEUP ) );


  while( RLIN3_A_TAB_MASTER_BASE[ RLIN3_LINMF_CurTable_u08[ UnitNumber_u08 ] ]
                                [ RLIN3_LINMF_TableIndex_u08[ UnitNumber_u08 ] + 1 ].Type_u08 !=
                                  RLIN3_A_NO )
  {
    UARTStatus_bit &= RLIN3_LINM_NextTableContent( UnitNumber_u08 );

    do
    {
      ErrorStatus = RLIN3_LINM_GetStatus( UnitNumber_u08 );
      
    } while( ErrorStatus != RLIN3_A_LIN_STATE_IDLE );
  }

  UARTStatus_bit &= RLIN3_Reset( UnitNumber_u08 );
  UARTStatus_bit &= RLIN3_CreateInterrupt( UnitNumber_u08,
                                           RLIN3_IRQ_SEND,
                                           RLIN3_INTCLEAR,
                                           NULL );
  UARTStatus_bit &= RLIN3_CreateInterrupt( UnitNumber_u08,
                                           RLIN3_IRQ_RECEIVE,
                                           RLIN3_INTCLEAR,
                                           NULL );
  UARTStatus_bit &= RLIN3_CreateInterrupt( UnitNumber_u08,
                                           RLIN3_IRQ_ERROR,
                                           RLIN3_INTCLEAR,
                                           NULL );
  UARTStatus_bit &= RLIN3_PortDisable( UnitNumber_u08 );

  return( UARTStatus_bit );
}

/* Activate LIN Slave with auto baud rate mode,
   according to built-in table with dedicated baud rate
 */

bit RLIN3_LINSlaveActivation( u08 UnitNumber_u08,
                              u32 Baudrate_u32 )
{
  bit UARTStatus_bit = RLIN3_OK;

  UARTStatus_bit = RLIN3_LIN_SetMode( UnitNumber_u08, 
                                      RLIN3_MODE_LINSLAVE_AUTO, 
                                      Baudrate_u32,
                                      OSCILLATOR_FREQUENCY );

  RLIN3_LINS_ActivateResponses( UnitNumber_u08, true );
  
  return( UARTStatus_bit );
}

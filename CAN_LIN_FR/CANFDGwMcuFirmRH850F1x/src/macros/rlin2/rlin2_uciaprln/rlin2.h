//============================================================================
// PROJECT = RLIN2 Type RLIN2_UCIAPRLN
//============================================================================
//                                 C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2015 by RENESAS Electronics (Europe) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
// Germany
//============================================================================
//Purpose: RLIN2 Driver Hardware Register Include
//
//Warranty Disclaimer
//
//Because the Product(s) is licensed free of charge, there is no warranty 
//of any kind whatsoever and expressly disclaimed and excluded by RENESAS, 
//either expressed or implied, including but not limited to those for 
//non-infringement of intellectual property, merchantability and/or 
//fitness for the particular purpose. 
//RENESAS shall not have any obligation to maintain, service or provide bug 
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
//In no event shall RENESAS be liable to the User for any incidental, 
//consequential, indirect, or punitive damage (including but not limited 
//to lost profits) regardless of whether such liability is based on breach 
//of contract, tort, strict liability, breach of warranties, failure of 
//essential purpose or otherwise and even if advised of the possibility of 
//such damages. RENESAS shall not be liable for any services or products 
//provided by third party vendors, developers or consultants identified or
//referred to the User by RENESAS in connection with the Product(s) and/or the 
//Application.
//
//
//
//============================================================================
// Environment: Devices:          All featuring RLIN2_UCIAPRLN
//              Assembler:        GHS MULTI
//              C-Compiler:       GHS MULTI
//              Linker:           GHS MULTI
//              Debugger:         GHS MULTI
//============================================================================
//
// Test Registers not included
//
//============================================================================

#ifndef _RLIN2_UCIAPRLN
#define _RLIN2_UCIAPRLN
                   
#include <ree_types.h>

/* RSCAN Globals */

#define RLIN2_0       ( 0 )         /* RLIN2 macro selection */
#define RLIN2_1       ( 1 )
#define RLIN2_2       ( 2 )
#define RLIN2_3       ( 3 )
#define RLIN2_4       ( 4 )
#define RLIN2_5       ( 5 )

#define RLIN2_CHANNEL_0  ( 0 )     /* RLIN2 channel selection */
#define RLIN2_CHANNEL_1  ( 1 )
#define RLIN2_CHANNEL_2  ( 2 )
#define RLIN2_CHANNEL_3  ( 3 )

#define RLIN2_MAXCHANNELS ( 4 )
#define RLIN2_MAXMACROS   ( 6 )

#define RLIN2_INVALID ( 0xFF )    /* no macro assignment */

#define RLIN2_OK          true    /* Status report defines */
#define RLIN2_ERROR       false

#define RLIN2_SET         ( 1 )
#define RLIN2_CLEAR       ( 0 )

#define RLIN2_IRQ_SEND    ( 0 )   /* interrupt sources */
#define RLIN2_IRQ_RECEIVE ( 1 )
#define RLIN2_IRQ_ERROR   ( 2 )
#define RLIN2_IRQ_NOINT   ( 0xFF )

#define RLIN2_INTERRUPTS  ( 3 )

/* application level constants */

/* Setting defines */

#define RLIN2_MAX_MODULUS         ( 0x100 )
#define RLIN2_MIN_MODULUS         ( 1 )

#define RLIN2_SAMPLES             ( 16 )

#define RLIN2_LINSTANDARD_V1      ( 0 )
#define RLIN2_LINSTANDARD_V2      ( 1 )

#define RLIN2_CLOCK_FA            ( 0 )
#define RLIN2_CLOCK_FB            ( 1 )
#define RLIN2_CLOCK_FC            ( 2 )
#define RLIN2_CLOCK_FD            ( 3 )

#define RLIN2_CLOCKDIVIDER_FA     ( 1 )
#define RLIN2_CLOCKDIVIDER_FB     ( 2 )
#define RLIN2_CLOCKDIVIDER_FC     ( 8 )
#define RLIN2_CLOCKDIVIDER_FD     ( 2 )

#define RLIN2_SAMPLES_MASTER      ( 16 )

#define RLIN2_MMODE_RESET         ( 0x00 )
#define RLIN2_MMODE_RESET_MASK    ( 0x01 )
#define RLIN2_MMODE_WAKEUP        ( 0x01 )
#define RLIN2_MMODE_OPERATION     ( 0x03 )

#define RLIN2_SBF13BITS           ( 0 )
#define RLIN2_SBF14BITS           ( 1 )
#define RLIN2_SBF15BITS           ( 2 )
#define RLIN2_SBF16BITS           ( 3 )
#define RLIN2_SBF17BITS           ( 4 )
#define RLIN2_SBF18BITS           ( 5 )
#define RLIN2_SBF19BITS           ( 6 )
#define RLIN2_SBF20BITS           ( 7 )
#define RLIN2_SBF21BITS           ( 8 )
#define RLIN2_SBF22BITS           ( 9 )
#define RLIN2_SBF23BITS           ( 10 )
#define RLIN2_SBF24BITS           ( 11 )
#define RLIN2_SBF25BITS           ( 12 )
#define RLIN2_SBF26BITS           ( 13 )
#define RLIN2_SBF27BITS           ( 14 )
#define RLIN2_SBF28BITS           ( 15 )

#define RLIN2_BDT1BITS            ( 0 )
#define RLIN2_BDT2BITS            ( 1 )
#define RLIN2_BDT3BITS            ( 2 )
#define RLIN2_BDT4BITS            ( 3 )

#define RLIN2_SPACE_HDRRESP_0BITS ( 0 )
#define RLIN2_SPACE_HDRRESP_1BITS ( 1 )
#define RLIN2_SPACE_HDRRESP_2BITS ( 2 )
#define RLIN2_SPACE_HDRRESP_3BITS ( 3 )
#define RLIN2_SPACE_HDRRESP_4BITS ( 4 )
#define RLIN2_SPACE_HDRRESP_5BITS ( 5 )
#define RLIN2_SPACE_HDRRESP_6BITS ( 6 )
#define RLIN2_SPACE_HDRRESP_7BITS ( 7 )

#define RLIN2_SPACE_RESBYTE_0BITS ( 0 )
#define RLIN2_SPACE_RESBYTE_1BITS ( 1 )
#define RLIN2_SPACE_RESBYTE_2BITS ( 2 )
#define RLIN2_SPACE_RESBYTE_3BITS ( 3 )

#define RLIN2_WUPTL_1BITS         ( 0 )
#define RLIN2_WUPTL_2BITS         ( 1 )
#define RLIN2_WUPTL_3BITS         ( 2 )
#define RLIN2_WUPTL_4BITS         ( 3 )
#define RLIN2_WUPTL_5BITS         ( 4 )
#define RLIN2_WUPTL_6BITS         ( 5 )
#define RLIN2_WUPTL_7BITS         ( 6 )
#define RLIN2_WUPTL_8BITS         ( 7 )
#define RLIN2_WUPTL_9BITS         ( 8 )
#define RLIN2_WUPTL_10BITS        ( 9 )
#define RLIN2_WUPTL_11BITS        ( 10 )
#define RLIN2_WUPTL_12BITS        ( 11 )
#define RLIN2_WUPTL_13BITS        ( 12 )
#define RLIN2_WUPTL_14BITS        ( 13 )
#define RLIN2_WUPTL_15BITS        ( 14 )
#define RLIN2_WUPTL_16BITS        ( 15 )

#define RLIN2_LINDATALEN_MAX      ( 8 )
#define RLIN2_UARTDATALEN_MAX     ( 9 )

#define RLIN2_RESPONSE_RECEIVE    ( 0 )
#define RLIN2_RESPONSE_TRANSMIT   ( 1 )

#define RLIN2_CHECKSUM_CLASSIC    ( 0 )
#define RLIN2_CHECKSUM_ENHANCED   ( 1 )

#define RLIN2_MFRAME_COMBINED     ( 0 )
#define RLIN2_MFRAME_SEPARATE     ( 1 )

#define RLIN2_PIDMASK             ( 0x3F )
#define RLIN2_PID_P0              ( 6 )
#define RLIN2_PID_P1              ( 7 )

/* RLIN2 access structures */

typedef struct rlin2_lwbr
{
  volatile u08                    lwbr0     : 1;
  
} rlin2_lwbr;

typedef struct rlin2_lmd
{
  volatile u08 RESERVED0                    : 2;
  volatile u08                    lcks      : 2;
  volatile u08 RESERVED1                    : 4;
    
} rlin2_lmd;

typedef struct rlin2_lsc
{
  volatile u08                    ibhs      : 3;
  volatile u08 RESERVED0                    : 1;
  volatile u08                    ibs       : 2;
  volatile u08 RESERVED1                    : 2;
    
} rlin2_lsc;

typedef struct rlin2_lwup
{
  volatile u08 RESERVED0                    : 4;
  volatile u08                    wutl      : 4;
  
} rlin2_lwup;

typedef struct rlin2_lie
{
  volatile u08                    ftcie     : 1;
  volatile u08                    frcie     : 1;
  volatile u08                    errie     : 1;
  volatile u08 RESERVED0                    : 5;
  
} rlin2_lie;

typedef struct rlin2_lcuc
{
  volatile u08                    om        : 2;
  volatile u08 RESERVED0                    : 6;
  
} rlin2_lcuc;

typedef struct rlin2_ltrc
{
  volatile u08                    fts       : 1;
  volatile u08                    rts       : 1;
  volatile u08 RESERVED0                    : 6;
  
} rlin2_ltrc;

typedef struct rlin2_lst_bit
{
  volatile u08                    ftc       : 1;
  volatile u08                    frc       : 1;
  volatile u08 RESERVED0                    : 1;
  volatile u08                    err       : 1;
  volatile u08 RESERVED1                    : 2;
  volatile u08                    d1rc      : 1;
  volatile u08                    htrc      : 1;
  
} rlin2_lst_bit;

typedef union rlin2_lst
{
  volatile u08                    all;
  struct rlin2_lst_bit            b;
  
} rlin2_lst;

typedef struct rlin2_lbfc
{
  volatile u08                    blt       : 4;
  volatile u08                    bdt       : 2;
  volatile u08 RESERVED0                    : 2;
  
} rlin2_lbfc;

typedef struct rlin2_lede
{
  volatile u08                    bere      : 1;
  volatile u08                    pbere     : 1;
  volatile u08                    ftere     : 1;
  volatile u08                    fere      : 1;
  volatile u08 RESERVED0                    : 4;
  
} rlin2_lede;

typedef struct rlin2_lest
{
  volatile u08                    ber       : 1;
  volatile u08                    pber      : 1;
  volatile u08                    ter       : 1;
  volatile u08                    fer       : 1;
  volatile u08 RESERVED0                    : 1;
  volatile u08                    cser      : 1;
  volatile u08 RESERVED1                    : 2;
  
} rlin2_lest;

typedef struct rlin2_ldfc
{
  volatile u08                    rfdl      : 4;
  volatile u08                    rcds      : 1;
  volatile u08                    lcs       : 1;
  volatile u08                    fsm       : 1;
  volatile u08 RESERVED0                    : 1;
  
} rlin2_ldfc;

typedef struct rlin2_lidb
{
  volatile u08                    id        : 6;
  volatile u08                    idp0      : 1;
  volatile u08                    idp1      : 1;
  
} rlin2_lidb;

typedef struct rlin2_channel
{
  struct rlin2_lmd                lmd;
  struct rlin2_lbfc               lbfc;
  struct rlin2_lsc                lsc;
  struct rlin2_lwup               lwup;
  struct rlin2_lie                lie;
  struct rlin2_lede               lede;
  struct rlin2_lcuc               lcuc;

  volatile u08                    RESERVED2[ 1 ];

  struct rlin2_ltrc               ltrc;
  struct rlin2_lcuc               lmst;
  union  rlin2_lst                lst;
  struct rlin2_lest               lest;
  struct rlin2_ldfc               ldfc;
  struct rlin2_lidb               lidb;
  volatile u08                    lcbr;
  volatile u08                    RESERVED3[ 1 ];
  volatile u08                    buf[ RLIN2_LINDATALEN_MAX ];
  volatile u08                    RESERVED4[ 8 ];
  
} rlin2_channel;

typedef struct rlin2
{
  volatile u08                    RESERVED0[ 1 ];

  struct rlin2_lwbr               lwbr;
  volatile u08                    brp0;
  volatile u08                    brp1;
  volatile u08                    lstc;

  volatile u08                    RESERVED1[ 3 ];

  struct rlin2_channel            ch[ RLIN2_MAXCHANNELS ];

} rlin2;

#endif

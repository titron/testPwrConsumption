//============================================================================
// PROJECT = RH850/F1KH-D8
//============================================================================
//                                 C O P Y R I G H T
//============================================================================
// Copyright (c) 2017 by Renesas Electronics Europe GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
// Germany
//============================================================================
//Purpose: Standard Port Hardware Mapping Definition
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
//
//
//============================================================================
// Environment: Devices:          RH850/F1KH-D8
//              Assembler:        GHS MULTI
//              C-Compiler:       GHS MULTI
//              Linker:           GHS MULTI
//              Debugger:         GHS MULTI
//============================================================================
//
// $Log$
//
//============================================================================

#ifndef _MAP_PORTS_H
#define _MAP_PORTS_H

#include <ree_macros.h>
//#include <ports\standardports\standardports.h>
#include <standardports.h>

#ifndef DRIVER_LOCAL
//#include <ports\standardports\standardports_p.h>
#include <standardports_p.h>
#endif

/* ADDRESS DEFINITIONS */

#define N_PORT_BASE                   ( 0xffc10000 )
#define N_PORT_DIR_BASE               ( 0xffc14100 )
#define N_PORT_MODE_BASE              ( 0xffc10300 )
#define N_PORT_MODE_CONTROL_BASE      ( 0xffc10400 )
#define N_PORT_FUNCTION_CONTROL_BASE  ( 0xffc10500 )
#define N_PORT_FUNCTION_CONTROL2_BASE ( 0xffc10600 )
#define N_PORT_FUNCTION_CONTROL4_BASE ( 0xffc10A00 )

#define N_PORT_FUNCLEVELS             ( 4 )

#define A_PORT_BASE                   ( 0xffc102cc )
#define A_PORT_CONTROL_BASE           ( 0xffc103cc )
#define A_PORT_MODE_CONTROL_BASE      ( 0xffc140cc )

/* NON-EXISTING PORT AREAS */

#undef PORT_3
#undef PORT_4
#undef PORT_5
#undef PORT_6
#undef PORT_7
#undef PORT_13
#undef PORT_14
#undef PORT_15
#undef PORT_16
#undef PORT_17
#undef PORT_22
#undef PORT_24
#undef PORT_25
#undef PORT_29
#undef PORT_31
#undef PORT_32
#undef PORT_33
#undef PORT_34

#undef PORT_DL
#undef PORT_DH
#undef PORT_AH
#undef PORT_CS
#undef PORT_CT
#undef PORT_CM
#undef PORT_CD

/* PORT STRUCTURE */

typedef struct port_numeric {

  volatile unsigned short  p0;
  volatile unsigned short  RESERVED0;
  volatile unsigned short  p1;
  volatile unsigned short  RESERVED1;
  volatile unsigned short  p2;
  volatile unsigned short  RESERVED2;
  volatile unsigned short  p3;
  volatile unsigned short  RESERVED3;
  volatile unsigned short  p4;
  volatile unsigned short  RESERVED4;
  volatile unsigned short  p5;
  volatile unsigned short  RESERVED5;
  volatile unsigned short  p6;
  volatile unsigned short  RESERVED6;
  volatile unsigned short  p7;
  volatile unsigned short  RESERVED7;
  volatile unsigned short  p8;
  volatile unsigned short  RESERVED8;
  volatile unsigned short  p9;
  volatile unsigned short  RESERVED9;
  volatile unsigned short  p10;
  volatile unsigned short  RESERVED10;
  volatile unsigned short  p11;
  volatile unsigned short  RESERVED11;
  volatile unsigned short  p12;
  volatile unsigned short  RESERVED12;
  volatile unsigned short  p13;
  volatile unsigned short  RESERVED13;
  volatile unsigned short  p14;
  volatile unsigned short  RESERVED14;
  volatile unsigned short  p15;
  volatile unsigned short  RESERVED15;
  volatile unsigned short  p16;
  volatile unsigned short  RESERVED16;
  volatile unsigned short  p17;
  volatile unsigned short  RESERVED17;
  volatile unsigned short  p18;
  volatile unsigned short  RESERVED18;
  volatile unsigned short  p19;
  volatile unsigned short  RESERVED19;
  volatile unsigned short  p20;
  volatile unsigned short  RESERVED20;

} port_numeric;


typedef struct port_dir_numeric {

  volatile unsigned short pbdc0;
  volatile unsigned short RESERVED0;
  volatile unsigned short pbdc1;
  volatile unsigned short RESERVED1;
  volatile unsigned short pbdc2;
  volatile unsigned short RESERVED2;
  volatile unsigned short pbdc3;
  volatile unsigned short RESERVED3;
  volatile unsigned short pbdc4;
  volatile unsigned short RESERVED4;
  volatile unsigned short pbdc5;
  volatile unsigned short RESERVED5;
  volatile unsigned short pbdc6;
  volatile unsigned short RESERVED6;
  volatile unsigned short pbdc7;
  volatile unsigned short RESERVED7;
  volatile unsigned short pbdc8;
  volatile unsigned short RESERVED8;
  volatile unsigned short pbdc9;
  volatile unsigned short RESERVED9;
  volatile unsigned short pbdc10;
  volatile unsigned short RESERVED10;
  volatile unsigned short pbdc11;
  volatile unsigned short RESERVED11;
  volatile unsigned short pbdc12;
  volatile unsigned short RESERVED12;
  volatile unsigned short pbdc13;
  volatile unsigned short RESERVED13;
  volatile unsigned short pbdc14;
  volatile unsigned short RESERVED14;
  volatile unsigned short pbdc15;
  volatile unsigned short RESERVED15;
  volatile unsigned short pbdc16;
  volatile unsigned short RESERVED16;
  volatile unsigned short pbdc17;
  volatile unsigned short RESERVED17;
  volatile unsigned short pbdc18;
  volatile unsigned short RESERVED18;
  volatile unsigned short pbdc19;
  volatile unsigned short RESERVED19;
  volatile unsigned short pbdc20;
  volatile unsigned short RESERVED20;

} port_dir_numeric;
typedef struct port_mode_numeric {

  volatile unsigned short pm0;
  volatile unsigned short RESERVED0;
  volatile unsigned short pm1;
  volatile unsigned short RESERVED1;
  volatile unsigned short pm2;
  volatile unsigned short RESERVED2;
  volatile unsigned short pm3;
  volatile unsigned short RESERVED3;
  volatile unsigned short pm4;
  volatile unsigned short RESERVED4;
  volatile unsigned short pm5;
  volatile unsigned short RESERVED5;
  volatile unsigned short pm6;
  volatile unsigned short RESERVED6;
  volatile unsigned short pm7;
  volatile unsigned short RESERVED7;
  volatile unsigned short pm8;
  volatile unsigned short RESERVED8;
  volatile unsigned short pm9;
  volatile unsigned short RESERVED9;
  volatile unsigned short pm10;
  volatile unsigned short RESERVED10;
  volatile unsigned short pm11;
  volatile unsigned short RESERVED11;
  volatile unsigned short pm12;
  volatile unsigned short RESERVED12;
  volatile unsigned short pm13;
  volatile unsigned short RESERVED13;
  volatile unsigned short pm14;
  volatile unsigned short RESERVED14;
  volatile unsigned short pm15;
  volatile unsigned short RESERVED15;
  volatile unsigned short pm16;
  volatile unsigned short RESERVED16;
  volatile unsigned short pm17;
  volatile unsigned short RESERVED17;
  volatile unsigned short pm18;
  volatile unsigned short RESERVED18;
  volatile unsigned short pm19;
  volatile unsigned short RESERVED19;
  volatile unsigned short pm20;
  volatile unsigned short RESERVED20;

} port_mode_numeric;


typedef struct port_mode_control_numeric {

  volatile unsigned short pmc0;
  volatile unsigned short RESERVED0;
  volatile unsigned short pmc1;
  volatile unsigned short RESERVED1;
  volatile unsigned short pmc2;
  volatile unsigned short RESERVED2;
  volatile unsigned short pmc3;
  volatile unsigned short RESERVED3;
  volatile unsigned short pmc4;
  volatile unsigned short RESERVED4;
  volatile unsigned short pmc5;
  volatile unsigned short RESERVED5;
  volatile unsigned short pmc6;
  volatile unsigned short RESERVED6;
  volatile unsigned short pmc7;
  volatile unsigned short RESERVED7;
  volatile unsigned short pmc8;
  volatile unsigned short RESERVED8;
  volatile unsigned short pmc9;
  volatile unsigned short RESERVED9;
  volatile unsigned short pmc10;
  volatile unsigned short RESERVED10;
  volatile unsigned short pmc11;
  volatile unsigned short RESERVED11;
  volatile unsigned short pmc12;
  volatile unsigned short RESERVED12;
  volatile unsigned short pmc13;
  volatile unsigned short RESERVED13;
  volatile unsigned short pmc14;
  volatile unsigned short RESERVED14;
  volatile unsigned short pmc15;
  volatile unsigned short RESERVED15;
  volatile unsigned short pmc16;
  volatile unsigned short RESERVED16;
  volatile unsigned short pmc17;
  volatile unsigned short RESERVED17;
  volatile unsigned short pmc18;
  volatile unsigned short RESERVED18;
  volatile unsigned short pmc19;
  volatile unsigned short RESERVED19;
  volatile unsigned short pmc20;
  volatile unsigned short RESERVED20;

} port_mode_control_numeric;

typedef struct port_function_control_numeric {

  volatile unsigned short pfc0;
  volatile unsigned short RESERVED0;
  volatile unsigned short pfc1;
  volatile unsigned short RESERVED1;
  volatile unsigned short pfc2;
  volatile unsigned short RESERVED2;
  volatile unsigned short pfc3;
  volatile unsigned short RESERVED3;
  volatile unsigned short pfc4;
  volatile unsigned short RESERVED4;
  volatile unsigned short pfc5;
  volatile unsigned short RESERVED5;
  volatile unsigned short pfc6;
  volatile unsigned short RESERVED6;
  volatile unsigned short pfc7;
  volatile unsigned short RESERVED7;
  volatile unsigned short pfc8;
  volatile unsigned short RESERVED8;
  volatile unsigned short pfc9;
  volatile unsigned short RESERVED9;
  volatile unsigned short pfc10;
  volatile unsigned short RESERVED10;
  volatile unsigned short pfc11;
  volatile unsigned short RESERVED11;
  volatile unsigned short pfc12;
  volatile unsigned short RESERVED12;
  volatile unsigned short pfc13;
  volatile unsigned short RESERVED13;
  volatile unsigned short pfc14;
  volatile unsigned short RESERVED14;
  volatile unsigned short pfc15;
  volatile unsigned short RESERVED15;
  volatile unsigned short pfc16;
  volatile unsigned short RESERVED16;
  volatile unsigned short pfc17;
  volatile unsigned short RESERVED17;
  volatile unsigned short pfc18;
  volatile unsigned short RESERVED18;
  volatile unsigned short pfc19;
  volatile unsigned short RESERVED19;
  volatile unsigned short pfc20;
  volatile unsigned short RESERVED20;

} port_function_control_numeric;

typedef struct port_function_control2_numeric {

  volatile unsigned short pfce0;
  volatile unsigned short RESERVED0;
  volatile unsigned short pfce1;
  volatile unsigned short RESERVED1;
  volatile unsigned short pfce2;
  volatile unsigned short RESERVED2;
  volatile unsigned short pfce3;
  volatile unsigned short RESERVED3;
  volatile unsigned short pfce4;
  volatile unsigned short RESERVED4;
  volatile unsigned short pfce5;
  volatile unsigned short RESERVED5;
  volatile unsigned short pfce6;
  volatile unsigned short RESERVED6;
  volatile unsigned short pfce7;
  volatile unsigned short RESERVED7;
  volatile unsigned short pfce8;
  volatile unsigned short RESERVED8;
  volatile unsigned short pfce9;
  volatile unsigned short RESERVED9;
  volatile unsigned short pfce10;
  volatile unsigned short RESERVED10;
  volatile unsigned short pfce11;
  volatile unsigned short RESERVED11;
  volatile unsigned short pfce12;
  volatile unsigned short RESERVED12;
  volatile unsigned short pfce13;
  volatile unsigned short RESERVED13;
  volatile unsigned short pfce14;
  volatile unsigned short RESERVED14;
  volatile unsigned short pfce15;
  volatile unsigned short RESERVED15;
  volatile unsigned short pfce16;
  volatile unsigned short RESERVED16;
  volatile unsigned short pfce17;
  volatile unsigned short RESERVED17;
  volatile unsigned short pfce18;
  volatile unsigned short RESERVED18;
  volatile unsigned short pfce19;
  volatile unsigned short RESERVED19;
  volatile unsigned short pfce20;
  volatile unsigned short RESERVED20;

} port_function_control2_numeric;

typedef struct port_function_control4_numeric {

  volatile unsigned short pfcae0;
  volatile unsigned short RESERVED0;
  volatile unsigned short pfcae1;
  volatile unsigned short RESERVED1;
  volatile unsigned short pfcae2;
  volatile unsigned short RESERVED2;
  volatile unsigned short pfcae3;
  volatile unsigned short RESERVED3;
  volatile unsigned short pfcae4;
  volatile unsigned short RESERVED4;
  volatile unsigned short pfcae5;
  volatile unsigned short RESERVED5;
  volatile unsigned short pfcae6;
  volatile unsigned short RESERVED6;
  volatile unsigned short pfcae7;
  volatile unsigned short RESERVED7;
  volatile unsigned short pfcae8;
  volatile unsigned short RESERVED8;
  volatile unsigned short pfcae9;
  volatile unsigned short RESERVED9;
  volatile unsigned short pfcae10;
  volatile unsigned short RESERVED10;
  volatile unsigned short pfcae11;
  volatile unsigned short RESERVED11;
  volatile unsigned short pfcae12;
  volatile unsigned short RESERVED12;
  volatile unsigned short pfcae13;
  volatile unsigned short RESERVED13;
  volatile unsigned short pfcae14;
  volatile unsigned short RESERVED14;
  volatile unsigned short pfcae15;
  volatile unsigned short RESERVED15;
  volatile unsigned short pfcae16;
  volatile unsigned short RESERVED16;
  volatile unsigned short pfcae17;
  volatile unsigned short RESERVED17;
  volatile unsigned short pfcae18;
  volatile unsigned short RESERVED18;
  volatile unsigned short pfcae19;
  volatile unsigned short RESERVED19;
  volatile unsigned short pfcae20;
  volatile unsigned short RESERVED20;

} port_function_control4_numeric;

typedef struct port_alpha {

  volatile unsigned short pal;
/*   volatile unsigned char  pah; */
/*   volatile unsigned char  RESERVED0; */
/*   volatile unsigned short pdl; */
/*   volatile unsigned short pdh; */
/*   volatile unsigned char  pcs; */
/*   volatile unsigned char  RESERVED1; */
/*   volatile unsigned char  pct; */
/*   volatile unsigned char  RESERVED2; */
/*   volatile unsigned char  pcm; */
/*   volatile unsigned char  RESERVED3; */
/*   volatile unsigned char  pcd; */

} port_alpha;


typedef struct port_mode_alpha {

  volatile unsigned short pmal;
/*   volatile unsigned char  pmah; */
/*   volatile unsigned char  RESERVED0; */
/*   volatile unsigned short pmdl; */
/*   volatile unsigned short pmdh; */
/*   volatile unsigned char  pmcs; */
/*   volatile unsigned char  RESERVED1; */
/*   volatile unsigned char  pmct; */
/*   volatile unsigned char  RESERVED2; */
/*   volatile unsigned char  pmcm; */
/*   volatile unsigned char  RESERVED3; */
/*   volatile unsigned char  pmcd; */

} port_mode_alpha;


typedef struct port_mode_control_alpha {

  volatile unsigned short pmcal;
/*   volatile unsigned char  pmcah; */
/*   volatile unsigned char  RESERVED0; */
/*   volatile unsigned short pmcdl; */
/*   volatile unsigned short pmcdh; */
/*   volatile unsigned char  pmccs; */
/*   volatile unsigned char  RESERVED1; */
/*   volatile unsigned char  pmcct; */
/*   volatile unsigned char  RESERVED2; */
/*   volatile unsigned char  pmccm; */
/*   volatile unsigned char  RESERVED3; */
/*   volatile unsigned char  pmccd;  */

} port_mode_control_alpha;


/* PORT DECLARATION */

static struct port_numeric
             *port_numeric_p =
                                 ( struct port_numeric * )
                                 ( N_PORT_BASE );

static struct port_dir_numeric
             *port_dir_numeric_p =
                                 ( struct port_dir_numeric * )
                                 ( N_PORT_DIR_BASE );
static struct port_mode_numeric
             *port_mode_numeric_p =
                                 ( struct port_mode_numeric * )
                                 ( N_PORT_MODE_BASE );

static struct port_mode_control_numeric
             *port_mode_control_numeric_p =
                                 ( struct port_mode_control_numeric * )
                                 ( N_PORT_MODE_CONTROL_BASE );

static struct port_function_control_numeric
             *port_function_control_numeric_p =
                                 ( struct port_function_control_numeric * )
                                 ( N_PORT_FUNCTION_CONTROL_BASE );

static struct port_function_control2_numeric
             *port_function_control2_numeric_p =
                                 ( struct port_function_control2_numeric * )
                                 ( N_PORT_FUNCTION_CONTROL2_BASE );

static struct port_function_control4_numeric
             *port_function_control4_numeric_p =
                                 ( struct port_function_control4_numeric * )
                                 ( N_PORT_FUNCTION_CONTROL4_BASE );

static struct port_alpha
             *port_alpha_p =
                                 ( struct port_alpha * )
                                 ( A_PORT_BASE );

static struct port_mode_alpha
             *port_mode_alpha_p =
                                 ( struct port_mode_alpha * )
                                 ( A_PORT_CONTROL_BASE );

static struct port_mode_control_alpha
             *port_mode_control_alpha_p =
                                 ( struct port_mode_control_alpha * )
                                 ( A_PORT_MODE_CONTROL_BASE );

#endif


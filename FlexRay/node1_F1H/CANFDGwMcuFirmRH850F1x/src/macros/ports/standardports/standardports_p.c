/*===========================================================================*/
/* PROJECT = STANDARD PORTS DRIVER                                           */
/*****************************************************************************/
/*                                  COPYRIGHT                                */
/*===========================================================================*/
/* Copyright (c) 2013 by Renesas Electronics Europe GmbH,                    */
/*               a company of the Renesas Electronics Corporation            */
/*===========================================================================*/
/*===========================================================================*/
/* In case of any question please do not hesitate to contact:                */
/*                                                                           */
/*        ABG.Support                                                        */
/*                                                                           */
/*        Renesas Electronics Europe GmbH                                    */
/*        Arcadiastrasse 10                                                  */
/*        D-40472 Duesseldorf, Germany                                       */
/*                                                                           */
/*        e-mail: device_support.rl78-eu@lm.renesas.com                      */
/*        FAX:   +49 - (0)211 / 65 03 - 12 79                                */
/*                                                                           */
/*===========================================================================*/
/* Warranty Disclaimer                                                       */
/*                                                                           */
/* Because the Product(s) is licensed free of charge, there is no warranty   */
/* of any kind whatsoever and expressly disclaimed and excluded by Renesas,  */
/* either expressed or implied, including but not limited to those for       */
/* non-infringement of intellectual property, merchantability and/or         */
/* fitness for the particular purpose.                                       */
/* Renesas shall not have any obligation to maintain, service or provide bug */
/* fixes for the supplied Product(s) and/or the Application.                 */
/*                                                                           */
/* Each User is solely responsible for determining the appropriateness of    */
/* using the Product(s) and assumes all risks associated with its exercise   */
/* of rights under this Agreement, including, but not limited to the risks   */
/* and costs of program errors, compliance with applicable laws, damage to   */
/* or loss of data, programs or equipment, and unavailability or             */
/* interruption of operations.                                               */
/*                                                                           */
/* Limitation of Liability                                                   */
/*                                                                           */
/* In no event shall Renesas be liable to the User for any incidental,       */
/* consequential, indirect, or punitive damage (including but not limited    */
/* to lost profits) regardless of whether such liability is based on breach  */
/* of contract, tort, strict liability, breach of warranties, failure of     */
/* essential purpose or otherwise and even if advised of the possibility of  */
/* such damages. Renesas shall not be liable for any services or products    */
/* provided by third party vendors, developers or consultants identified or  */
/* referred to the User by Renesas in connection with the Product(s) and/or  */
/* the Application.                                                          */
/*                                                                           */
/*===========================================================================*/

#define DRIVER_LOCAL

#include <ree_types.h>
#include "dr7f7015273.h"

#ifdef VLIB
#include <config_afcan.h>

#else
#include <map_ports.h>
#endif

//=============================================================================
// FunctionName: PORT_GetStatus
// IN  :         Port Number, Bit Spec
// OUT :         Error Flag
//               Port Direction, Peri. Mode, Alt. Mode (by reference)
// Description : Get Port Modes and Direction
// 
//=============================================================================

bit PORT_GetStatus( u16  PortNumber_u16,
                    u16  BitSpecification_u16,
                    pu08 PortDirection_pu08,
                    pu08 PeripheralMode_pu08,
                    pu08 AlternateFunction_pu08 )
{
    switch ( PortNumber_u16 )
    {                       
#ifdef PORT_NUMERIC
#ifdef PORT_0
        case PORT_0:
            if ( ( port_mode_numeric_p->pm0 & BitSpecification_u16 ) ==
                                              BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm0 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc0 & BitSpecification_u16 ) ==
                                                       BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc0 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc0 & BitSpecification_u16 ) ==
                                                           BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc0 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce0 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae0 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif
#ifdef PORT_1
        case PORT_1:
            if ( ( port_mode_numeric_p->pm1 & BitSpecification_u16 ) ==
                                              BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm1 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc1 & BitSpecification_u16 ) ==
                                                       BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc1 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc1 & BitSpecification_u16 ) ==
                                                           BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc1 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce1 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae1 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif
#ifdef PORT_2
        case PORT_2:
            if ( ( port_mode_numeric_p->pm2 & BitSpecification_u16 ) ==
                                              BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm2 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc2 & BitSpecification_u16 ) ==
                                                       BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc2 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc2 & BitSpecification_u16 ) ==
                                                           BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc2 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce2 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae2 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif
#ifdef PORT_3
        case PORT_3:
            if ( ( port_mode_numeric_p->pm3 & BitSpecification_u16 ) ==
                                              BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm3 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc3 & BitSpecification_u16 ) ==
                                                       BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc3 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc3 & BitSpecification_u16 ) ==
                                                           BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc3 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce3 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae3 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif
#ifdef PORT_4
        case PORT_4:
            if ( ( port_mode_numeric_p->pm4 & BitSpecification_u16 ) ==
                                              BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm4 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc4 & BitSpecification_u16 ) ==
                                                       BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc4 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc4 & BitSpecification_u16 ) ==
                                                           BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc4 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce4 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae4 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif
#ifdef PORT_5
        case PORT_5:
            if ( ( port_mode_numeric_p->pm5 & BitSpecification_u16 ) ==
                                              BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm5 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc5 & BitSpecification_u16 ) ==
                                                       BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc5 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc5 & BitSpecification_u16 ) ==
                                                           BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc5 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce5 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae5 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif
#ifdef PORT_6
        case PORT_6:
            if ( ( port_mode_numeric_p->pm6 & BitSpecification_u16 ) ==
                                              BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm6 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc6 & BitSpecification_u16 ) ==
                                                       BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc6 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc6 & BitSpecification_u16 ) ==
                                                           BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc6 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce6 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae6 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif
#ifdef PORT_7
        case PORT_7:
            if ( ( port_mode_numeric_p->pm7 & BitSpecification_u16 ) ==
                                              BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm7 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc7 & BitSpecification_u16 ) ==
                                                       BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc7 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc7 & BitSpecification_u16 ) ==
                                                           BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc7 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce7 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae7 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif
#ifdef PORT_8
        case PORT_8:
            if ( ( port_mode_numeric_p->pm8 & BitSpecification_u16 ) ==
                                              BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm8 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc8 & BitSpecification_u16 ) ==
                                                       BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc8 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc8 & BitSpecification_u16 ) ==
                                                           BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc8 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce8 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae8 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif
#ifdef PORT_9
        case PORT_9:
            if ( ( port_mode_numeric_p->pm9 & BitSpecification_u16 ) ==
                                              BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm9 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc9 & BitSpecification_u16 ) ==
                                                       BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc9 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc9 & BitSpecification_u16 ) ==
                                                           BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc9 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce9 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae9 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif
#ifdef PORT_10
        case PORT_10:
            if ( ( port_mode_numeric_p->pm10 & BitSpecification_u16 ) ==
                                              BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm10 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc10 & BitSpecification_u16 ) ==
                                                       BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc10 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc10 & BitSpecification_u16 ) ==
                                                           BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc10 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce10 & BitSpecification_u16 ) ==
                                                             BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae10 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif
#ifdef PORT_11
        case PORT_11:
            if ( ( port_mode_numeric_p->pm11 & BitSpecification_u16 ) ==
                                              BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm11 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc11 & BitSpecification_u16 ) ==
                                                       BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc11 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc11 & BitSpecification_u16 ) ==
                                                           BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc11 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce11 & BitSpecification_u16 ) ==
                                                             BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae11 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif
#ifdef PORT_12
        case PORT_12:
            if ( ( port_mode_numeric_p->pm12 & BitSpecification_u16 ) ==
                                              BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm12 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc12 & BitSpecification_u16 ) ==
                                                       BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc12 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc12 & BitSpecification_u16 ) ==
                                                           BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc12 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce12 & BitSpecification_u16 ) ==
                                                             BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae12 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif
#ifdef PORT_13
        case PORT_13:
            if ( ( port_mode_numeric_p->pm13 & BitSpecification_u16 ) ==
                                               BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm13 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc13 & BitSpecification_u16 ) ==
                                                        BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc13 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc13 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc13 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce13 & BitSpecification_u16 ) ==
                                                             BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae13 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif

#ifdef PORT_14
        case PORT_14:
            if ( ( port_mode_numeric_p->pm14 & BitSpecification_u16 ) ==
                                               BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm14 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc14 & BitSpecification_u16 ) ==
                                                        BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc14 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc14 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc14 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce14 & BitSpecification_u16 ) ==
                                                             BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae14 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif
#ifdef PORT_15
        case PORT_15:
            if ( ( port_mode_numeric_p->pm15 & BitSpecification_u16 ) ==
                                               BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm15 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc15 & BitSpecification_u16 ) ==
                                                        BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc15 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc15 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc15 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce15 & BitSpecification_u16 ) ==
                                                             BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae15 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif
#ifdef PORT_16
        case PORT_16:
            if ( ( port_mode_numeric_p->pm16 & BitSpecification_u16 ) ==
                                               BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm16 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc16 & BitSpecification_u16 ) ==
                                                        BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc16 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc16 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc16 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce16 & BitSpecification_u16 ) ==
                                                             BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae16 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif
#ifdef PORT_17
        case PORT_17:
            if ( ( port_mode_numeric_p->pm17 & BitSpecification_u16 ) ==
                                               BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm17 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc17 & BitSpecification_u16 ) ==
                                                        BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc17 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc17 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc17 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce17 & BitSpecification_u16 ) ==
                                                             BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae17 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif

#ifdef PORT_18
        case PORT_18:
            if ( ( port_mode_numeric_p->pm18 & BitSpecification_u16 ) ==
                                               BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm18 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc18 & BitSpecification_u16 ) ==
                                                        BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc18 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc18 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc18 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce18 & BitSpecification_u16 ) ==
                                                             BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae18 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif

#ifdef PORT_20
        case PORT_20:
            if ( ( port_mode_numeric_p->pm20 & BitSpecification_u16 ) ==
                                               BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm20 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc20 & BitSpecification_u16 ) ==
                                                        BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc20 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc20 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc20 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce20 & BitSpecification_u16 ) ==
                                                             BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae20 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif

#ifdef PORT_22
        case PORT_22:
            if ( ( port_mode_numeric_p->pm22 & BitSpecification_u16 ) ==
                                               BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm22 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc22 & BitSpecification_u16 ) ==
                                                        BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc22 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc22 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc22 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce22 & BitSpecification_u16 ) ==
                                                             BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae22 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif

#ifdef PORT_24
        case PORT_24:
            if ( ( port_mode_numeric_p->pm24 & BitSpecification_u16 ) ==
                                               BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm24 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc24 & BitSpecification_u16 ) ==
                                                        BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc24 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc24 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc24 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce24 & BitSpecification_u16 ) ==
                                                             BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae24 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif

#ifdef PORT_25
        case PORT_25:
            if ( ( port_mode_numeric_p->pm25 & BitSpecification_u16 ) ==
                                               BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm25 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc25 & BitSpecification_u16 ) ==
                                                        BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc25 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc25 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc25 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce25 & BitSpecification_u16 ) ==
                                                             BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae25 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif

#ifdef PORT_29
        case PORT_29:
            if ( ( port_mode_numeric_p->pm29 & BitSpecification_u16 ) ==
                                               BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm29 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc29 & BitSpecification_u16 ) ==
                                                        BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc29 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc29 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc29 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce29 & BitSpecification_u16 ) ==
                                                             BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae29 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif

#ifdef PORT_31
        case PORT_31:
            if ( ( port_mode_numeric_p->pm31 & BitSpecification_u16 ) ==
                                               BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_numeric_p->pm31 & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_numeric_p->pmc31 & BitSpecification_u16 ) ==
                                                        BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_numeric_p->pmc31 & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            if ( ( port_function_control_numeric_p->pfc31 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_ALTERN;
            else if ( ( port_function_control_numeric_p->pfc31 & BitSpecification_u16 ) == 0 )
                 *AlternateFunction_pu08 = PORT_FUNCTION_NORMAL;
            else *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
            if ( ( port_function_control2_numeric_p->pfce31 & BitSpecification_u16 ) ==
                                                             BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN2;
#endif
#if( N_PORT_FUNCLEVELS > 3 )
            if ( ( port_function_control4_numeric_p->pfcae31 & BitSpecification_u16 ) ==
                                                            BitSpecification_u16 )
                 *AlternateFunction_pu08 |= PORT_FUNCTION_ALTERN4;
#endif
#endif
            break;
#endif
#endif

#ifdef PORT_ALPHA
#ifdef PORT_DL
        case PORT_DL:
            if ( ( port_mode_alpha_p->pmdl & BitSpecification_u16 ) ==
                                             BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_alpha_p->pmdl & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_alpha_p->pmcdl & BitSpecification_u16 ) ==
                                                      BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_alpha_p->pmcdl & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
            break;
#endif
#ifdef PORT_DH
        case PORT_DH:
            if ( ( port_mode_alpha_p->pmdh & BitSpecification_u16 ) ==
                                             BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_alpha_p->pmdh & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_alpha_p->pmcdh & BitSpecification_u16 ) ==
                                                      BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_alpha_p->pmcdh & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
            break;
#endif
#ifdef PORT_AL
        case PORT_AL:
            if ( ( port_mode_alpha_p->pmal & BitSpecification_u16 ) ==
                                             BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_alpha_p->pmal & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_alpha_p->pmcal & BitSpecification_u16 ) ==
                                                      BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_alpha_p->pmcal & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
            break;
#endif
#ifdef PORT_AH
        case PORT_AH:
            if ( ( port_mode_alpha_p->pmah & BitSpecification_u16 ) ==
                                             BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_alpha_p->pmah & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_alpha_p->pmcah & BitSpecification_u16 ) ==
                                                      BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_alpha_p->pmcah & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
            break;
#endif
#ifdef PORT_CS
        case PORT_CS:
            if ( ( port_mode_alpha_p->pmcs & BitSpecification_u16 ) ==
                                             BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_alpha_p->pmcs & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_alpha_p->pmccs & BitSpecification_u16 ) ==
                                                      BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_alpha_p->pmccs & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
            break;
#endif
#ifdef PORT_CT
        case PORT_CT:
            if ( ( port_mode_alpha_p->pmct & BitSpecification_u16 ) ==
                                             BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_alpha_p->pmct & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_alpha_p->pmcct & BitSpecification_u16 ) ==
                                                      BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_alpha_p->pmcct & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
            break;
#endif
#ifdef PORT_CM
        case PORT_CM:
            if ( ( port_mode_alpha_p->pmcm & BitSpecification_u16 ) ==
                                             BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_alpha_p->pmcm & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_alpha_p->pmccm & BitSpecification_u16 ) ==
                                                      BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_alpha_p->pmccm & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
            break;
#endif
#ifdef PORT_CD
        case PORT_CD:
            if ( ( port_mode_alpha_p->pmcd & BitSpecification_u16 ) ==
                                             BitSpecification_u16 )
                 *PortDirection_pu08 = PORT_DIR_INPUT;
            else if ( ( port_mode_alpha_p->pmcd & BitSpecification_u16 ) == 0 )
                 *PortDirection_pu08 = PORT_DIR_OUTPUT;
            else *PortDirection_pu08 = PORT_DIR_KEEP;
            if ( ( port_mode_control_alpha_p->pmccd & BitSpecification_u16 ) ==
                                                      BitSpecification_u16 )
                 *PeripheralMode_pu08 = PORT_MODE_PERIPHERAL;
            else if ( ( port_mode_control_alpha_p->pmccd & BitSpecification_u16 ) == 0 )
                 *PeripheralMode_pu08 = PORT_MODE_IO;
            else *PeripheralMode_pu08 = PORT_MODE_KEEP;
            *AlternateFunction_pu08 = PORT_FUNCTION_KEEP;
            break;
#endif
#endif      
        default:
            return( PORT_ERROR );
            
    } // end switch ( PortNumber_u16 )

    return( PORT_OK );
    
}   
 
//=============================================================================
// FunctionName: PORT_Enable
// IN  :         Port Number, Bit Spec, Port Direction, Peri. Mode, Alt. Mode
// OUT :         Error Flag
// Description : Set Port to Mode and Direction
// 
//=============================================================================
#define WR_PROT_REG(cmd, reg, value)                \
    do {                                            \
        cmd = 0xA5U;                                \
        reg = value;                                \
        reg = ~value;                               \
        reg = value;                                \
    } while (0)

bit PORT_Enable( u16 PortNumber_u16,
                 u16 BitSpecification_u16,
                 u08 PortDirection_u08,
                 u08 PeripheralMode_u08,
                 u08 AlternateFunction_u08 )
{
    switch( PortNumber_u16 )
    {
#ifdef PORT_NUMERIC
#ifdef PORT_0
        case PORT_0:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc0 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc0 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc0 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce0 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae0 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc0 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce0 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae0 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm0 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm0 |=
                       BitSpecification_u16;
            }

            /* P0_0 setting:
             * P0_0 drives a low level after any kind of reset,
             * until it is later configured differently by register settings.
             * To avoid a data collision, the outside circuit connected to this pin must not drive a high level. */
            if(BitSpecification_u16 == BIT_0)
            {
				while (PODC0 != 0x00UL)
				{
					WR_PROT_REG(PPCMD0, PODC0, 0x00UL);
				}
            }
            break;
#endif
#ifdef PORT_1
        case PORT_1:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc1 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc1 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc1 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce1 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae1 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc1 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce1 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae1 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm1 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm1 |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_2
        case PORT_2:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc2 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc2 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc2 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce2 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae2 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc2 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce2 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae2 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm2 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm2 |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_3
        case PORT_3:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc3 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc3 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc3 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce3 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae3 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc3 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce3 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae3 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm3 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm3 |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_4
        case PORT_4:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc4 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc4 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc4 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce4 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae4 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc4 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce4 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae4 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm4 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm4 |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_5
        case PORT_5:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc5 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc5 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc5 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce5 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae5 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc5 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce5 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae5 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm5 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm5 |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_6
        case PORT_6:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc6 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc6 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc6 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce6 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae6 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc6 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce6 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae6 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm6 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm6 |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_7
        case PORT_7:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc7 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc7 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc7 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce7 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae7 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc7 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce7 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae7 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm7 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm7 |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_8
        case PORT_8:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc8 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc8 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc8 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce8 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae8 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc8 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce8 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae8 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm8 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm8 |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_9
        case PORT_9:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc9 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc9 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc9 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce9 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae9 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc9 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce9 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae9 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm9 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm9 |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_10
        case PORT_10:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc10 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc10 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc10 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce10 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae10 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc10 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce10 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae10 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm10 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm10 |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_11
        case PORT_11:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc11 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc11 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc11 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce11 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae11 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc11 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce11 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae11 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm11 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm11 |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_12
        case PORT_12:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc12 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc12 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc12 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce12 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae12 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc12 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce12 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae12 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm12 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm12 |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_13
        case PORT_13:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc13 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc13 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc13 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce13 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae13 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc13 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce13 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae13 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm13 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm13 |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_14
        case PORT_14:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc14 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc14 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc14 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce14 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae14 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc14 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce14 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae14 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm14 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm14 |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_15
        case PORT_15:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc15 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc15 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc15 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce15 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae15 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc15 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce15 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae15 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm15 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm15 |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_16
        case PORT_16:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc16 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc16 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc16 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce16 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae16 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc16 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce16 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae16 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm16 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm16 |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_17
        case PORT_17:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc17 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc17 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc17 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce17 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae17 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc17 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce17 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae17 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm17 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm17 |=
                       BitSpecification_u16;
            }
            break;
#endif

#ifdef PORT_18
        case PORT_18:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc18 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc18 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc18 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce18 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae18 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc18 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce18 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae18 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm18 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm18 |=
                       BitSpecification_u16;
            }
            break;
#endif

#ifdef PORT_20
        case PORT_20:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc20 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc20 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc20 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce20 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae20 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc20 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce20 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae20 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm20 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm20 |=
                       BitSpecification_u16;
            }
            break;
#endif

#ifdef PORT_22
        case PORT_22:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc22 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc22 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc22 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce22 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae22 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc22 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce22 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae22 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm22 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm22 |=
                       BitSpecification_u16;
            }
            break;
#endif

#ifdef PORT_24
        case PORT_24:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc24 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc24 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc24 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce24 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae24 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc24 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce24 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae24 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm24 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm24 |=
                       BitSpecification_u16;
            }
            break;
#endif

#ifdef PORT_25
        case PORT_25:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc25 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc25 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc25 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce25 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae25 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc25 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce25 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae25 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm25 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm25 |=
                       BitSpecification_u16;
            }
            break;
#endif

#ifdef PORT_29
        case PORT_29:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc29 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc29 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc29 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce29 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae29 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc29 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce29 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae29 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm29 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm29 |=
                       BitSpecification_u16;
            }
            break;
#endif

#ifdef PORT_31
        case PORT_31:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc31 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc31 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc31 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce31 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae31 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc31 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce31 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae31 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm31 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm31 |=
                       BitSpecification_u16;
            }
            break;
#endif

#ifdef PORT_32
        case PORT_32:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc32 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc32 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc32 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce32 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae32 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc32 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce32 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae32 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm32 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm32 |=
                       BitSpecification_u16;
            }
            break;
#endif

#ifdef PORT_33
        case PORT_33:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc33 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc33 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc33 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce33 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae33 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc33 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce33 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae33 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm33 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm33 |=
                       BitSpecification_u16;
            }
            break;
#endif

#ifdef PORT_34
        case PORT_34:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_numeric_p->pmc34 &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_numeric_p->pmc34 |= 
                       BitSpecification_u16;
            }
            if ( AlternateFunction_u08 == PORT_FUNCTION_KEEP )
              {
              }
            else if ( AlternateFunction_u08 == PORT_FUNCTION_NORMAL )
              {
                port_function_control_numeric_p->pfc34 &= 
                    ~( BitSpecification_u16 );
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                port_function_control2_numeric_p->pfce34 &= 
                    ~( BitSpecification_u16 );
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                port_function_control4_numeric_p->pfcae34 &= 
                    ~( BitSpecification_u16 );
#endif
#endif
              }
            else 
              {
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN )
                  {
                    port_function_control_numeric_p->pfc34 |= 
                      BitSpecification_u16;
                  }
#ifdef N_PORT_FUNCLEVELS
#if( N_PORT_FUNCLEVELS > 2 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN2 )
                  {
                    port_function_control2_numeric_p->pfce34 |= 
                      BitSpecification_u16;
                  }
#endif
#if( N_PORT_FUNCLEVELS > 3 )
                if ( AlternateFunction_u08 & PORT_FUNCTION_ALTERN4 )
                  {
                    port_function_control4_numeric_p->pfcae34 |= 
                      BitSpecification_u16;
                  }
#endif
#endif
              }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_numeric_p->pm34 &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_numeric_p->pm34 |=
                       BitSpecification_u16;
            }
            break;
#endif

#endif

#ifdef PORT_ALPHA
#ifdef PORT_DL
        case PORT_DL:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_alpha_p->pmcdl &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_alpha_p->pmcdl |= 
                       BitSpecification_u16;
            }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_alpha_p->pmdl &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_alpha_p->pmdl |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_DH
        case PORT_DH:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_alpha_p->pmcdh &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_alpha_p->pmcdh |= 
                       BitSpecification_u16;
            }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_alpha_p->pmdh &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_alpha_p->pmdh |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_AL
        case PORT_AL:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_alpha_p->pmcal &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_alpha_p->pmcal |= 
                       BitSpecification_u16;
            }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_alpha_p->pmal &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_alpha_p->pmal |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_AH
        case PORT_AH:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_alpha_p->pmcah &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_alpha_p->pmcah |= 
                       BitSpecification_u16;
            }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_alpha_p->pmah &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_alpha_p->pmah |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_CS
        case PORT_CS:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_alpha_p->pmccs &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_alpha_p->pmccs |= 
                       BitSpecification_u16;
            }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_alpha_p->pmcs &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_alpha_p->pmcs |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_CT
        case PORT_CT:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_alpha_p->pmcct &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_alpha_p->pmcct |= 
                       BitSpecification_u16;
            }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_alpha_p->pmct &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_alpha_p->pmct |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_CM
        case PORT_CM:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_alpha_p->pmccm &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_alpha_p->pmccm |= 
                       BitSpecification_u16;
            }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_alpha_p->pmcm &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_alpha_p->pmcm |=
                       BitSpecification_u16;
            }
            break;
#endif
#ifdef PORT_CD
        case PORT_CD:
            if ( PeripheralMode_u08 == PORT_MODE_IO )
                port_mode_control_alpha_p->pmccd &= 
                    ~( BitSpecification_u16 );
            else if ( PeripheralMode_u08 == PORT_MODE_PERIPHERAL )
            {
                port_mode_control_alpha_p->pmccd |= 
                       BitSpecification_u16;
            }
            if ( PortDirection_u08 == PORT_DIR_OUTPUT )
                port_mode_alpha_p->pmcd &=
                    ~( BitSpecification_u16 );
            else if ( PortDirection_u08 == PORT_DIR_INPUT )
            {
                port_mode_alpha_p->pmcd |=
                       BitSpecification_u16;
            }
            break;
#endif
#endif      
        case PORT_NOPORT:
            return( PORT_OK );
            
        default:
            return( PORT_ERROR );
            
    }                          
    
    return( PORT_OK );
    
}   

//=============================================================================
// FunctionName: PORT_PortDisable
// IN  :         Port Number
// OUT :         Error Flag
// Description : Set Port to Input Mode, Keep other settings
// 
//=============================================================================

bit PORT_Disable( u16 PortNumber_u16,
                  u16 BitSpecification_u16 )
{
  bit StatusValue_bit;
  
  StatusValue_bit =  PORT_Enable( PortNumber_u16,
                                  BitSpecification_u16,
                                  PORT_DIR_INPUT,
                                  PORT_MODE_KEEP,
                                  PORT_FUNCTION_KEEP );
  
  StatusValue_bit &= PORT_Enable( PortNumber_u16,
                                  BitSpecification_u16,
                                  PORT_DIR_INPUT,
                                  PORT_MODE_IO,
                                  PORT_FUNCTION_KEEP );
  return( StatusValue_bit );
}    
    
//=============================================================================
// FunctionName: PORT_Write
// IN  :         Port Number, Port Data
// OUT :         Error Flag
// Description : Write Data to Port
// 
//=============================================================================

bit PORT_Write( u16 PortNumber_u16,
                u16 PortData_u16 )
{
    switch( PortNumber_u16 )
    {
#ifdef PORT_NUMERIC
#ifdef PORT_0
        case PORT_0:
            port_numeric_p->p0 = PortData_u16;
            break;
#endif
#ifdef PORT_1
        case PORT_1:
            port_numeric_p->p1 = PortData_u16;
            break;
#endif
#ifdef PORT_2
        case PORT_2:
            port_numeric_p->p2 = PortData_u16;
            break;
#endif
#ifdef PORT_3
        case PORT_3:
            port_numeric_p->p3 = PortData_u16;
            break;
#endif
#ifdef PORT_4
        case PORT_4:
            port_numeric_p->p4 = PortData_u16;
            break;
#endif
#ifdef PORT_5
        case PORT_5:
            port_numeric_p->p5 = PortData_u16;
            break;
#endif
#ifdef PORT_6
        case PORT_6:
            port_numeric_p->p6 = PortData_u16;
            break;
#endif
#ifdef PORT_7
        case PORT_7:
            port_numeric_p->p7 = PortData_u16;
            break;
#endif
#ifdef PORT_8
        case PORT_8:
            port_numeric_p->p8 = PortData_u16;
            break;
#endif
#ifdef PORT_9
        case PORT_9:
            port_numeric_p->p9 = PortData_u16;
            break;
#endif
#ifdef PORT_10
        case PORT_10:
            port_numeric_p->p10 = PortData_u16;
            break;
#endif
#ifdef PORT_11
        case PORT_11:
            port_numeric_p->p11 = PortData_u16;
            break;
#endif
#ifdef PORT_12
        case PORT_12:
            port_numeric_p->p12 = PortData_u16;
            break;
#endif
#ifdef PORT_13
        case PORT_13:
            port_numeric_p->p13 = PortData_u16;
            break;
#endif
#ifdef PORT_14
        case PORT_14:
            port_numeric_p->p14 = PortData_u16;
            break;
#endif
#ifdef PORT_15
        case PORT_15:
            port_numeric_p->p15 = PortData_u16;
            break;
#endif
#ifdef PORT_16
        case PORT_16:
            port_numeric_p->p16 = PortData_u16;
            break;
#endif
#ifdef PORT_17
        case PORT_17:
            port_numeric_p->p17 = PortData_u16;
            break;
#endif
#ifdef PORT_18
        case PORT_18:
            port_numeric_p->p18 = PortData_u16;
            break;
#endif
#ifdef PORT_20
        case PORT_20:
            port_numeric_p->p20 = PortData_u16;
            break;
#endif
#ifdef PORT_24
        case PORT_24:
            port_numeric_p->p24 = PortData_u16;
            break;
#endif
#ifdef PORT_25
        case PORT_25:
            port_numeric_p->p25 = PortData_u16;
            break;
#endif
#ifdef PORT_29
        case PORT_29:
            port_numeric_p->p29 = PortData_u16;
            break;
#endif
#ifdef PORT_31
        case PORT_31:
            port_numeric_p->p31 = PortData_u16;
            break;
#endif
#ifdef PORT_32
        case PORT_32:
            port_numeric_p->p32 = PortData_u16;
            break;
#endif
#ifdef PORT_33
        case PORT_33:
            port_numeric_p->p33 = PortData_u16;
            break;
#endif
#ifdef PORT_34
        case PORT_34:
            port_numeric_p->p34 = PortData_u16;
            break;
#endif
#endif

#ifdef PORT_ALPHA
#ifdef PORT_DL
        case PORT_DL:
            port_alpha_p->pdl = PortData_u16;
            break;
#endif
#ifdef PORT_DH
        case PORT_DH:
            port_alpha_p->pdh = PortData_u16;
            break;
#endif
#ifdef PORT_AL
        case PORT_AL:
            port_alpha_p->pal = PortData_u16;
            break;
#endif
#ifdef PORT_AH
        case PORT_AH:
            port_alpha_p->pah = PortData_u16;
            break;
#endif
#ifdef PORT_CS
        case PORT_CS:
            port_alpha_p->pcs = PortData_u16;
            break;
#endif
#ifdef PORT_CT
        case PORT_CT:
            port_alpha_p->pct = PortData_u16;
            break;
#endif
#ifdef PORT_CM
        case PORT_CM:
            port_alpha_p->pcm = PortData_u16;
            break;
#endif
#ifdef PORT_CD
        case PORT_CD:
            port_alpha_p->pcd = PortData_u16;
            break;
#endif
#endif
        default:
            return( PORT_ERROR );
            
    }                          
    
    return( PORT_OK );   
}   

//=============================================================================
// FunctionName: PORT_Read
// IN  :         Port Number 
// OUT :         Error Flag
//               Port Data (by pointer reference)
// Description : Read Data from Port
// 
//=============================================================================

bit PORT_Read( u16  PortNumber_u16,
               pu16 PortData_pu16 )
{
    switch( PortNumber_u16 )
    {
#ifdef PORT_NUMERIC
#ifdef PORT_0
        case PORT_0:       
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc0 |= ( ~( port_read_enable_numeric_p->pibc0 ) );
            *PortData_pu16 = port_read_numeric_p->ppr0;
            port_read_enable_numeric_p->pibc0 &= ( ~( port_read_enable_numeric_p->pibc0 ) );
#else
            *PortData_pu16 = port_numeric_p->p0;
#endif
            break;
#endif
#ifdef PORT_1
        case PORT_1:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc1 |= ( ~( port_read_enable_numeric_p->pibc1 ) );
            *PortData_pu16 = port_read_numeric_p->ppr1;
            port_read_enable_numeric_p->pibc1 &= ( ~( port_read_enable_numeric_p->pibc1 ) );
#else
            *PortData_pu16 = port_numeric_p->p1;
#endif
            break;
#endif
#ifdef PORT_2
        case PORT_2:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc2 |= ( ~( port_read_enable_numeric_p->pibc2 ) );
            *PortData_pu16 = port_read_numeric_p->ppr2;
            port_read_enable_numeric_p->pibc2 &= ( ~( port_read_enable_numeric_p->pibc2 ) );
#else
            *PortData_pu16 = port_numeric_p->p2;
#endif
            break;
#endif
#ifdef PORT_3
        case PORT_3:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc3 |= ( ~( port_read_enable_numeric_p->pibc3 ) );
            *PortData_pu16 = port_read_numeric_p->ppr3;
            port_read_enable_numeric_p->pibc3 &= ( ~( port_read_enable_numeric_p->pibc3 ) );
#else
            *PortData_pu16 = port_numeric_p->p3;
#endif
            break;
#endif
#ifdef PORT_4
        case PORT_4:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc4 |= ( ~( port_read_enable_numeric_p->pibc4 ) );
            *PortData_pu16 = port_read_numeric_p->ppr4;
            port_read_enable_numeric_p->pibc4 &= ( ~( port_read_enable_numeric_p->pibc4 ) );
#else
            *PortData_pu16 = port_numeric_p->p4;
#endif
            break;
#endif
#ifdef PORT_5
        case PORT_5:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc5 |= ( ~( port_read_enable_numeric_p->pibc5 ) );
            *PortData_pu16 = port_read_numeric_p->ppr5;
            port_read_enable_numeric_p->pibc5 &= ( ~( port_read_enable_numeric_p->pibc5 ) );
#else
            *PortData_pu16 = port_numeric_p->p5;
#endif
            break;
#endif
#ifdef PORT_6
        case PORT_6:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc6 |= ( ~( port_read_enable_numeric_p->pibc6 ) );
            *PortData_pu16 = port_read_numeric_p->ppr6;
            port_read_enable_numeric_p->pibc6 &= ( ~( port_read_enable_numeric_p->pibc6 ) );
#else
            *PortData_pu16 = port_numeric_p->p6;
#endif
            break;
#endif
#ifdef PORT_7
        case PORT_7:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc7 |= ( ~( port_read_enable_numeric_p->pibc7 ) );
            *PortData_pu16 = port_read_numeric_p->ppr7;
            port_read_enable_numeric_p->pibc7 &= ( ~( port_read_enable_numeric_p->pibc7 ) );
#else
            *PortData_pu16 = port_numeric_p->p7;
#endif
            break;
#endif
#ifdef PORT_8
        case PORT_8:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc8 |= ( ~( port_read_enable_numeric_p->pibc8 ) );
            *PortData_pu16 = port_read_numeric_p->ppr8;
            port_read_enable_numeric_p->pibc8 &= ( ~( port_read_enable_numeric_p->pibc8 ) );
#else
            *PortData_pu16 = port_numeric_p->p8;
#endif
            break;
#endif
#ifdef PORT_9
        case PORT_9:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc9 |= ( ~( port_read_enable_numeric_p->pibc9 ) );
            *PortData_pu16 = port_read_numeric_p->ppr9;
            port_read_enable_numeric_p->pibc9 &= ( ~( port_read_enable_numeric_p->pibc9 ) );
#else
            *PortData_pu16 = port_numeric_p->p9;
#endif
            break;
#endif
#ifdef PORT_10
        case PORT_10:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc10 |= ( ~( port_read_enable_numeric_p->pibc10 ) );
            *PortData_pu16 = port_read_numeric_p->ppr10;
            port_read_enable_numeric_p->pibc10 &= ( ~( port_read_enable_numeric_p->pibc10 ) );
#else
            *PortData_pu16 = port_numeric_p->p10;
#endif
            break;
#endif
#ifdef PORT_11
        case PORT_11:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc11 |= ( ~( port_read_enable_numeric_p->pibc11 ) );
            *PortData_pu16 = port_read_numeric_p->ppr11;
            port_read_enable_numeric_p->pibc11 &= ( ~( port_read_enable_numeric_p->pibc11 ) );
#else
            *PortData_pu16 = port_numeric_p->p11;
#endif
            break;
#endif
#ifdef PORT_12
        case PORT_12:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc12 |= ( ~( port_read_enable_numeric_p->pibc12 ) );
            *PortData_pu16 = port_read_numeric_p->ppr12;
            port_read_enable_numeric_p->pibc12 &= ( ~( port_read_enable_numeric_p->pibc12 ) );
#else
            *PortData_pu16 = port_numeric_p->p12;
#endif
            break;
#endif
#ifdef PORT_13
        case PORT_13:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc13 |= ( ~( port_read_enable_numeric_p->pibc13 ) );
            *PortData_pu16 = port_read_numeric_p->ppr13;
            port_read_enable_numeric_p->pibc13 &= ( ~( port_read_enable_numeric_p->pibc13 ) );
#else
            *PortData_pu16 = port_numeric_p->p13;
#endif
            break;
#endif
#ifdef PORT_14
        case PORT_14:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc14 |= ( ~( port_read_enable_numeric_p->pibc14 ) );
            *PortData_pu16 = port_read_numeric_p->ppr14;
            port_read_enable_numeric_p->pibc14 &= ( ~( port_read_enable_numeric_p->pibc14 ) );
#else
            *PortData_pu16 = port_numeric_p->p14;
#endif
            break;
#endif
#ifdef PORT_15
        case PORT_15:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc15 |= ( ~( port_read_enable_numeric_p->pibc15 ) );
            *PortData_pu16 = port_read_numeric_p->ppr15;
            port_read_enable_numeric_p->pibc15 &= ( ~( port_read_enable_numeric_p->pibc15 ) );
#else
            *PortData_pu16 = port_numeric_p->p15;
#endif
            break;
#endif
#ifdef PORT_16
        case PORT_16:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc16 |= ( ~( port_read_enable_numeric_p->pibc16 ) );
            *PortData_pu16 = port_read_numeric_p->ppr16;
            port_read_enable_numeric_p->pibc16 &= ( ~( port_read_enable_numeric_p->pibc16 ) );
#else
            *PortData_pu16 = port_numeric_p->p16;
#endif
            break;
#endif
#ifdef PORT_17
        case PORT_17:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc17 |= ( ~( port_read_enable_numeric_p->pibc17 ) );
            *PortData_pu16 = port_read_numeric_p->ppr17;
            port_read_enable_numeric_p->pibc17 &= ( ~( port_read_enable_numeric_p->pibc17 ) );
#else
            *PortData_pu16 = port_numeric_p->p17;
#endif
            break;
#endif
#ifdef PORT_18
        case PORT_18:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc18 |= ( ~( port_read_enable_numeric_p->pibc18 ) );
            *PortData_pu16 = port_read_numeric_p->ppr18;
            port_read_enable_numeric_p->pibc18 &= ( ~( port_read_enable_numeric_p->pibc18 ) );
#else
            *PortData_pu16 = port_numeric_p->p18;
#endif
            break;
#endif
#ifdef PORT_20
        case PORT_20:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc20 |= ( ~( port_read_enable_numeric_p->pibc20 ) );
            *PortData_pu16 = port_read_numeric_p->ppr20;
            port_read_enable_numeric_p->pibc20 &= ( ~( port_read_enable_numeric_p->pibc20 ) );
#else
            *PortData_pu16 = port_numeric_p->p20;
#endif
            break;
#endif
#ifdef PORT_24
        case PORT_24:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc24 |= ( ~( port_read_enable_numeric_p->pibc24 ) );
            *PortData_pu16 = port_read_numeric_p->ppr24;
            port_read_enable_numeric_p->pibc24 &= ( ~( port_read_enable_numeric_p->pibc24 ) );
#else
            *PortData_pu16 = port_numeric_p->p24;
#endif
            break;
#endif
#ifdef PORT_25
        case PORT_25:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc25 |= ( ~( port_read_enable_numeric_p->pibc25 ) );
            *PortData_pu16 = port_read_numeric_p->ppr25;
            port_read_enable_numeric_p->pibc25 &= ( ~( port_read_enable_numeric_p->pibc25 ) );
#else
            *PortData_pu16 = port_numeric_p->p25;
#endif
            break;
#endif
#ifdef PORT_29
        case PORT_29:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc29 |= ( ~( port_read_enable_numeric_p->pibc29 ) );
            *PortData_pu16 = port_read_numeric_p->ppr29;
            port_read_enable_numeric_p->pibc29 &= ( ~( port_read_enable_numeric_p->pibc29 ) );
#else
            *PortData_pu16 = port_numeric_p->p29;
#endif
            break;
#endif
#ifdef PORT_31
        case PORT_31:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc31 |= ( ~( port_read_enable_numeric_p->pibc31 ) );
            *PortData_pu16 = port_read_numeric_p->ppr31;
            port_read_enable_numeric_p->pibc31 &= ( ~( port_read_enable_numeric_p->pibc31 ) );
#else
            *PortData_pu16 = port_numeric_p->p31;
#endif
            break;
#endif
#ifdef PORT_32
        case PORT_32:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc32 |= ( ~( port_read_enable_numeric_p->pibc32 ) );
            *PortData_pu16 = port_read_numeric_p->ppr32;
            port_read_enable_numeric_p->pibc32 &= ( ~( port_read_enable_numeric_p->pibc32 ) );
#else
            *PortData_pu16 = port_numeric_p->p32;
#endif
            break;
#endif
#ifdef PORT_33
        case PORT_33:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc33 |= ( ~( port_read_enable_numeric_p->pibc33 ) );
            *PortData_pu16 = port_read_numeric_p->ppr33;
            port_read_enable_numeric_p->pibc33 &= ( ~( port_read_enable_numeric_p->pibc33 ) );
#else
            *PortData_pu16 = port_numeric_p->p33;
#endif
            break;
#endif
#ifdef PORT_34
        case PORT_34:
#ifdef N_PORT_READ_PPR
            port_read_enable_numeric_p->pibc34 |= ( ~( port_read_enable_numeric_p->pibc34 ) );
            *PortData_pu16 = port_read_numeric_p->ppr34;
            port_read_enable_numeric_p->pibc34 &= ( ~( port_read_enable_numeric_p->pibc34 ) );
#else
            *PortData_pu16 = port_numeric_p->p34;
#endif
            break;
#endif
#endif

#ifdef PORT_ALPHA
#ifdef PORT_DL
        case PORT_DL:
            *PortData_pu16 = port_alpha_p->pdl;
            break;
#endif
#ifdef PORT_DH
        case PORT_DH:
            *PortData_pu16 = port_alpha_p->pdh;
            break;
#endif
#ifdef PORT_AL
        case PORT_AL:
            *PortData_pu16 = port_alpha_p->pal;
            break;
#endif
#ifdef PORT_AH
        case PORT_AH:
            *PortData_pu16 = port_alpha_p->pah;
            break;
#endif
#ifdef PORT_CS
        case PORT_CS:
            *PortData_pu16 = port_alpha_p->pcs;
            break;
#endif
#ifdef PORT_CT
        case PORT_CT:
            *PortData_pu16 = port_alpha_p->pct;
            break;
#endif
#ifdef PORT_CM
        case PORT_CM:
            *PortData_pu16 = port_alpha_p->pcm;
            break;
#endif
#ifdef PORT_CD
        case PORT_CD:
            *PortData_pu16 = port_alpha_p->pcd;
            break;
#endif
#endif
        default:
            return( PORT_ERROR );
            
    }                          
    
    return( PORT_OK );      
}

//=============================================================================
// FunctionName: PORT_WriteBit
// IN  :         Port Number, Bit Specification, Bit Value
// OUT :         Error Flag
// Description : Write Bit to Port
// 
//=============================================================================

bit PORT_WriteBit( u16 PortNumber_u16,
                   u16 BitSpecification_u16,
                   u16 BitValue_u16 )
{
  bit StatusValue_bit = PORT_OK;
  u16 PortValue_u16;
  
  StatusValue_bit = PORT_Read( PortNumber_u16, &PortValue_u16 );
  
  if( StatusValue_bit == PORT_OK )
  {
    if( BitValue_u16 )
    {
      PortValue_u16 = PortValue_u16 | BitSpecification_u16;
    }
    else
    {
      PortValue_u16 = PortValue_u16 & ( ~ ( BitSpecification_u16 ) );
    }
    PORT_Write( PortNumber_u16, PortValue_u16 );
  }
  return( StatusValue_bit );
}

//=============================================================================
// FunctionName: PORT_ReadBit
// IN  :         Port Number, Bit Specification, Bit Value
// OUT :         Error Flag
// Description : Read Bit from Port
// 
//=============================================================================

bit PORT_ReadBit( u16  PortNumber_u16,
                  u16  BitSpecification_u16,
                  pu16 BitValue_pu16 )
{
  bit StatusValue_bit = PORT_OK;
  u16 PortValue_u16;
  
  StatusValue_bit = PORT_Read( PortNumber_u16, &PortValue_u16 );
  
  if( StatusValue_bit == PORT_OK )
  {
    *BitValue_pu16 = PortValue_u16 & BitSpecification_u16;
  }
  return( StatusValue_bit );
}

//=============================================================================
// FunctionName: PORT_Oscillator_Switch_Setup
// IN  :         Port Number 
// OUT :         Error Flag
//               Port Data (by pointer reference)
// Description : Set up wished port as indicator of oscillator frequency
// 
//=============================================================================

bit PORT_Oscillator_Switch_Setup( )
{
#ifdef OSC_PORT

    switch( OSC_PORT )
    {
#ifdef PORT_NUMERIC
#ifdef PORT_CT
        case PORT_CT:
            port_mode_alpha_p->pmct = 0xFF;
			port_mode_control_alpha_p->pmcct = 0x00;
			return( PORT_OK );
            break;
#endif
#endif
        default:
            return( PORT_ERROR );
            
    }                          

#endif    
    return( PORT_OK );      
}

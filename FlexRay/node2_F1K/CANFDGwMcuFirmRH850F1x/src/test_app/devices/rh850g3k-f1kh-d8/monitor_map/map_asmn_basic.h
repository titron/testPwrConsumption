//============================================================================
// PROJECT = RH850/F1KH-D8
//============================================================================
//                                 C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2017 by RENESAS Electronics (Europe) GmbH. All rights reserved.
// Arcadiastrasse 10
// D-40472 Duesseldorf
// Germany
//============================================================================
//Purpose: Basic Settings Definition File for ASMN Monitor
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
//referred to the User by RENESAS in conrenesastion with the Product(s) and/or the 
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

#ifndef _MAP_ASMN_BASIC_H
#define _MAP_ASMN_BASIC_H

#include <ree_macros.h>
#include <map_device.h>

/*
 * The hardware type: specific settings within several modules
 */

/* Device identification name for low-level driver adaptation */

#define RH850_F1KH_D8

/*************************/
/* Hardware setup values */
/*************************/

/* Oscillator frequency in Hertz and floating point */

#define OSCILLATOR_FREQUENCY     ( ( float )( 80.0E6 ) )
#define OSC_FREQUENCY            ( 80000000 )
#define SUBOSCILLATOR_FREQUENCY  ( 0 )
#define SUBOSC_FREQUENCY         ( 0 )
#define MAX_CPU_FREQUENCY        ( 400000000 )

/* Communication Interface Type */

#define ASMN_UARTINTERFACE       RLIN3_STANDARD  // communication interface type

#endif

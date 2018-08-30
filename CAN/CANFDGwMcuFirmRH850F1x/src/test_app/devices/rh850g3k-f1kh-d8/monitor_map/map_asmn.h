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
//Purpose: Function Definition File for ASMN Monitor
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

#ifndef _MAP_ASMN_H
#define _MAP_ASMN_H

#include <ree_macros.h>
#include <map_device.h>

/*********************/
/* ASMN integrations */
/*********************/

#define REXIT RESET_PE1
extern int exit( int );
extern void REXIT( void );

/***********************************/
/* Specific macro library settings */
/***********************************/

/*
 * Settings for the Communications Interface
 */

#define ASMN_MENUCOM         RLIN3_1
#define ASMN_MENUCOM_ILEVEL  0
#define ASMN_MENUCOM_BAUD    9600L
#define ASMN_MENUCOM_PARITY  RLIN3_PARITY_NONE
#define ASMN_MENUCOM_CHLEN   RLIN3_CHARLEN_8BITS
#define ASMN_MENUCOM_STOP    RLIN3_ONESTOPBIT
#define ASMN_MENUCOM_DIR     RLIN3_DIR_LSBFIRST
#define ASMN_MENUCOM_EXE1    0x0D
#define ASMN_MENUCOM_EXE2    0x0A
#define ASMN_MENUCOM_BUFLEN  4

#define ASMN_UARTPORTENABLE   RLIN3_PortEnable
#define ASMN_UARTPORTDISABLE  RLIN3_PortDisable
#define ASMN_UARTRESET        RLIN3_Reset
#define ASMN_UARTCONFIG       RLIN3_LegacyConfig
#define ASMN_UARTSENDSTRING   RLIN3_SendString   
#define ASMN_UARTSENDBYTE     RLIN3_SendByte
#define ASMN_UARTRECEIVEBYTE  RLIN3_ReceiveByte 
#define ASMN_UARTRECEIVEINT   RLIN3_ReceiveInteger
#define ASMN_UARTRECEIVELONG  RLIN3_ReceiveULong
#define ASMN_UARTRECEIVEFLOAT RLIN3_ReceiveFloat
#define ASMN_UARTRECEIVESTRG  RLIN3_ReceiveString
#define ASMN_UARTCREATEINT    RLIN3_CreateInterrupt
#define ASMN_UARTTRANSFEROK   RLIN3_TRANSFER_OK
#define ASMN_UARTERROR        RLIN3_ERROR
#define ASMN_UARTMODECRLF     RLIN3_A_TTYMODE_CRLF
#define ASMN_UARTMODECR       RLIN3_A_TTYMODE_CR
#define ASMN_UARTIRQTX        RLIN3_IRQ_SEND
#define ASMN_UARTIRQRX        RLIN3_IRQ_RECEIVE
#define ASMN_UARTIRQLEV       RLIN3_INTENABLEDEFAULT

#define ASMN_EICOMMAND        { __EI(); }
#define ASMN_DICOMMAND        { __DI(); }

/*
 * Direct start of FR Application for CETITEC MCU Board
 */
 
// #define ASMN_DIRECTSTART ApplFRStart_1

#endif

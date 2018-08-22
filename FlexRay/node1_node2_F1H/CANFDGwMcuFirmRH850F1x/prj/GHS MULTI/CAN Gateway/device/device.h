//============================================================================
// PROJECT  :  Example project
//============================================================================
//                           C O P Y R I G H T
//============================================================================
// Copyright (c) 2011 by Renesas Electronics  GmbH. All rights reserved.
// Arcadiastr.10
// D-40472 Duesseldorf
// Germany
//============================================================================
//
// Warranty Disclaimer :
// Because the Product(s) is licensed free of charge, there is no warranty of
// any kind whatsoever and expressly disclaimed and excluded by NEC, either
// expressed or implied, including but not limited to those for non-
// infringement of intellectual property, merchantability and/or fitness for
// the particular purpose. NEC shall not have any obligation to maintain,
// service or provide bug fixes for the supplied Product(s) and/or the
// Application.
//
// Each User is solely responsible for determining the appropriateness of
// using the Product(s) and assumes all risks associated with its exercise
// of rights under this Agreement, including, but not limited to the risks
// and costs of program errors, compliance with applicable laws, damage to
// or loss of data, programs or equipment, and unavailability or
// interruption of operations.
//
// Limitation of Liability :
// In no event shall NEC be liable to the User for any incidental,
// consequential, indirect, or punitive damage (including but not limited to
// lost profits) regardless of whether such liability is based on breach of
// contract, tort, strict liability, breach of warranties, failure of
// essential purpose or otherwise and even if advised of the possibility of
// such damages. NEC shall not be liable for any services or products provided
// by third party vendors, developers or consultants identified or referred
// to the User by NEC in connection with the Product(s) and/or the
// Application.
//
//============================================================================
//
// Device specific main header file to be included in all source files.
//
//============================================================================

#ifndef   DEVICE_H
#define   DEVICE_H

//============================================================================
// Includes
//============================================================================
//#include <v800_ghs.h>

#include "../../../../../CANFDGwMcuFirmRH850F1x/prj/GHS MULTI/CAN Gateway/device/interrupt_reg.h"
#include "dr7f7015273-ghs.h"


//============================================================================
// Defines
//============================================================================

#define protected_write(preg,reg,value)   preg=0xa5;\
                                          reg=value;\
                                          reg=~value;\
                                          reg=value;


#define	PE1 1
#define	PE2 2


typedef void 	VOID;
typedef void *	PVOID;
typedef	void (*PFUNC)(void);
typedef	void (*PISR)(void);

extern void __unused_isr( void);
extern void __unused_eisr( void);
extern void __unused_ex( void);


#pragma ghs io __itbl 0x200
volatile const PFUNC __itbl[256];

__inline unsigned long GetPEID( void)
{
	unsigned long	__t;

	/* unsigned int __STSR(__ghs_c_int__ regID, __ghs_c_int__ selID); */ 
	__t= (__STSR( 0, 2) >>16) & 0x7;

	return __t;
}


#endif  /* DEVICE_H */

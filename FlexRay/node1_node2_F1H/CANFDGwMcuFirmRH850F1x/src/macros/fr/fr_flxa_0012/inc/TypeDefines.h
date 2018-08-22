//============================================================================
// PROJECT  : NEC FlexRay controller evalutation 
// MODULE   : TypeDefiness.h
// VERSION  : 0.1
// DATE     : 02.09.2003
//============================================================================
//                           C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2002 by NEC Electronics (Europe) GmbH. All rights reserved.
// Kanzlerstrasse 2
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
// Enviroment : Devices    : V850E/IA1  
//              Assembler  : GHS AS-V850 1.8.9             Version : 3.0
//              C-Compiler : GHS CCV850, Multi 2000, V800  Version : 3.5.1
//              Linker     : GHS lx, Multi 2000, V800      Version : 3.5.1       
//              Debugger   : GHS Multi 2000, V800          Version : 3.5.1
//============================================================================
// Version		Author            Description
// 0.1		H.Schmerling 	Initial Release
//============================================================================

#ifndef TYPEDEFINES_H_
#define TYPEDEFINES_H_

#ifdef TYPEDEFINES_VARS
   #define _EXTERN_
#else
   #define _EXTERN_ extern
#endif

// defines

#ifndef u08
#define u08 unsigned char
#endif

#ifndef s08
#define s08 char
#endif

#ifndef u16
#define u16 unsigned short
#endif

#ifndef s16
#define s16 short
#endif

#ifndef u32
#define u32 unsigned int
#endif

#ifndef s32
#define s32 int
#endif

#ifndef u64
#define u64 unsigned long
#endif

#ifndef s64
#define s64 long
#endif


#ifndef BOOL
#define BOOL unsigned char
#endif

#ifdef _EXTERN_
#undef _EXTERN_
#endif

#endif

/* end of file */

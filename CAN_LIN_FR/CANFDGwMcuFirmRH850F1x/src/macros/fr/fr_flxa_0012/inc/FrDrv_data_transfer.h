//============================================================================
// PROJECT  : NEC FlexRay driver 
// MODULE   : flexray_data_transfer.h
// VERSION  : 0.1
// DATE     : 24.02.2004
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


#ifndef FR_DATA_TRANSFER_H
#define FR_DATA_TRANSFER_H

#ifdef FLEXRAY_DATA_TRANSFER_VARS
   #define _EXTERN_
#else
   #define _EXTERN_ extern
#endif

// defines
#define MB0		0		// message buffer 0
#define MB1		1		// message buffer 1
#define MB2		2		// message buffer 2
#define MB3		3		// message buffer 3
#define MB4		4		// message buffer 4
#define MB5		5		// message buffer 5
#define MB6		6		// message buffer 6
#define MB7		7		// message buffer 7
#define MB8		8		// message buffer 8
#define MB9		9		// message buffer 9
#define MB10	10		// message buffer 10
#define MB11	11		// message buffer 11
#define MB12	12		// message buffer 12
#define MB13	13		// message buffer 13
#define MB14	14		// message buffer 14
#define MB15	15		// message buffer 15
#define MB16	16		// message buffer 16
#define MB17	17		// message buffer 17
#define MB18	18		// message buffer 18
#define MB19	19		// message buffer 19
#define MB20	20		// message buffer 20
#define MB21	21		// message buffer 21
#define MB22	22		// message buffer 22
#define MB23	23		// message buffer 23
#define MB24	24		// message buffer 24
#define MB25	25		// message buffer 25
#define MB26	26		// message buffer 26
#define MB27	27		// message buffer 27
#define MB28	28		// message buffer 28
#define MB29	29		// message buffer 29
#define MB30	30		// message buffer 30		
#define MB31	31		// message buffer 31
#define MB32	32		// message buffer 32
#define MB33	33		// message buffer 33
#define MB34	34		// message buffer 34
#define MB35	35		// message buffer 35
#define MB36	36		// message buffer 36
#define MB37	37		// message buffer 37
#define MB38	38		// message buffer 38
#define MB39	39		// message buffer 39
#define MB40	40		// message buffer 40
#define MB41	41		// message buffer 41
#define MB42	42		// message buffer 42
#define MB43	43		// message buffer 43
#define MB44	44		// message buffer 44
#define MB45	45		// message buffer 45
#define MB46	46		// message buffer 46 
#define MB47	47		// message buffer 47
#define MB48	48		// message buffer 48
#define MB49	49		// message buffer 49
#define MB50	50		// message buffer 50
#define MB51	51		// message buffer 51
#define MB52	52		// message buffer 52
#define MB53	53		// message buffer 53
#define MB54	54		// message buffer 54
#define MB55	55		// message buffer 55
#define MB56	56		// message buffer 56
#define MB57	57		// message buffer 57
#define MB58	58		// message buffer 58
#define MB59	59		// message buffer 59
#define MB60	60		// message buffer 60
#define MB61	61		// message buffer 61
#define MB62	62		// message buffer 62
#define MB63	63		// message buffer 63

#define IOS1	0	// InputOutput section 1
#define IOS2	1		// InputOutput section 2
#define IOS3	2		// InputOutput section 3
#define IOS4	3		// InputOutput section 4
#define IOS5	4		// InputOutput section 5
#define IOS6	5		// InputOutput section 6
#define IOS7	6		// InputOutput section 7
#define IOS8	7		// InputOutput section 8
#define IOS9	8		// InputOutput section 9
#define IOS10	9		// InputOutput section 10
#define IOS11	10		// InputOutput section 11
#define IOS12	11		// InputOutput section 12
#define IOS13	12		// InputOutput section 13
#define IOS14	13		// InputOutput section 14
#define IOS15	14		// InputOutput section 15
#define IOS16	15		// InputOutput section 16
#define IOS17	16		// InputOutput section 17
#define IOS18	17		// InputOutput section 18
#define IOS19	18		// InputOutput section 19
#define IOS20	19		// InputOutput section 20
#define IOS21	20		// InputOutput section 21
#define IOS22	21		// InputOutput section 22
#define IOS23	22		// InputOutput section 23
#define IOS24	23		// InputOutput section 24
#define IOS25	24		// InputOutput section 25
#define IOS26	25		// InputOutput section 26
#define IOS27	26		// InputOutput section 27
#define IOS28	27		// InputOutput section 28
#define IOS29	28		// InputOutput section 29
#define IOS30	29		// InputOutput section 30		
#define IOS31	30		// InputOutput section 31
#define IOS32	31		// InputOutput section 32
#define IOS33	32		// InputOutput section 33
#define IOS34	33		// InputOutput section 34
#define IOS35	34		// InputOutput section 35
#define IOS36	35		// InputOutput section 36
#define IOS37	36		// InputOutput section 37
#define IOS38	37		// InputOutput section 38
#define IOS39	38		// InputOutput section 39
#define IOS40	39		// InputOutput section 40
#define IOS41	40		// InputOutput section 41
#define IOS42	41		// InputOutput section 42
#define IOS43	42		// InputOutput section 43
#define IOS44	43		// InputOutput section 44
#define IOS45	44		// InputOutput section 45
#define IOS46	45		// InputOutput section 46 
#define IOS47	46		// InputOutput section 47
#define IOS48	47		// InputOutput section 48
#define IOS49	48		// InputOutput section 49
#define IOS50	49		// InputOutput section 50
#define IOS51	50		// InputOutput section 51
#define IOS52	51		// InputOutput section 52
#define IOS53	52		// InputOutput section 53
#define IOS54	53		// InputOutput section 54
#define IOS55	54		// InputOutput section 55
#define IOS56	55		// InputOutput section 56
#define IOS57	56		// InputOutput section 57
#define IOS58	57		// InputOutput section 58
#define IOS59	58		// InputOutput section 59
#define IOS60	59		// InputOutput section 60
#define IOS61	60		// InputOutput section 61
#define IOS62	61		// InputOutput section 62
#define IOS63	62		// InputOutput section 63
#define IOS64 63	    // InputOutput section 64
				
#define CHA_SET 	1	// Channel A select
#define CHB_CLEAR	0	// Channel A deselect
#define CHB_SET		1	// Channel B select
#define CHB_CLEAR	0	// Channel B deselect

#define TRANS_BUF	1	// Transmit Buffer
#define REC_BUF		0	// Receive Buffer

#define NM_ON		1		// Network management on
#define NM_OFF	0		// Network management off

#define SSM		1		// Single shot mode
#define CONM	0		// Continous mode

#define MBI_ON	1		// Message Buffer Interrupt enabled
#define MBI_OFF	0		// Message Buffer Interrupt disabled
	
#endif

#ifdef _EXTERN_
#undef _EXTERN_
#endif

// end of file

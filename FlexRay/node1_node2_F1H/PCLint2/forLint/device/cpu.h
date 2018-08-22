/*===============================================================================================

    Copyright (c) 2013 by Renesas Electronics Europe GmbH, a company of the Renesas Electronics 
    Corporation. All rights reserved.

  ===============================================================================================

    Warranty Disclaimer                                                       
                                                                             
    Because the Product(s) is licensed free of charge, there is no warranty of any kind
    whatsoever and expressly disclaimed and excluded by Renesas, either expressed or implied, 
    including but not limited to those for non-infringement of intellectual property, 
    merchantability and/or fitness for the particular purpose.
    Renesas shall not have any obligation to maintain, service or provide bug fixes for the
    supplied Product(s) and/or the Application.

    Each User is solely responsible for determining the appropriateness of using the Product(s)
    and assumes all risks associated with its exercise of rights under this Agreement, including,
    but not limited to the risks and costs of program errors, compliance with applicable laws,
    damage to or loss of data, programs or equipment, and unavailability or interruption of
    operations.

    Limitation of Liability

    In no event shall Renesas be liable to the User for any incidental, consequential, indirect,
    or punitive damage (including but not limited to lost profits) regardless of whether such
    liability is based on breach of contract, tort, strict liability, breach of warranties, 
    failure of essential purpose or otherwise and even if advised of the possibility of such
    damages. Renesas shall not be liable for any services or products provided by third party
    vendors, developers or consultants identified or referred to the User by Renesas in 
    connection with the Product(s) and/or the Application.

  ===============================================================================================*/

#ifndef __CPU_H__
#define __CPU_H__

#include <..\include\v800\v800_ghs.h>

/*
 * Groups
 */

/* CPU function group system register */
#define EIPC		(0)
#define EIPSW		(1)
#define FEPC		(2)
#define FEPSW		(3)
#define ECR			(4)
#define PSW			(5)
#define PID			(6)
#define CFG			(7)
#define RESV8		(8)
#define RESV9		(9)
#define RESV10		(10)
#define SCCFG		(11)
#define SCBP		(12)
#define EIIC		(13)
#define FEIC		(14)
#define DBIC		(15)
#define CTPC		(16)
#define CTPSW		(17)
#define DBPC		(18)
#define DBPSW		(19)
#define CTBP		(20)
#define DIR			(21)
#define RESV22		(22)
#define RESV23		(23)
#define RESV24		(24)
#define RESV25		(25)
#define RESV26		(26)
#define RESV27		(27)

/* Processor protection function group system registers */

/* PMU function group system registers */

/* FPU function group system registers */
							/* 0 to 5 Reserved for future function expansion. */
#define	FPSR		(6)		/* Floating-point configuration/status */
#define	FPEPC		(7)		/* Floating-point exception program counter */
#define	FPST		(8)		/* Floating point status */
#define	FPCC		(9)		/* Floating-point comparison result */
#define	FPCFG		(10)	/* Floating-point configuration */
#define	FPEC		(11)	/* Floating-point exception control */
							/* 12 to 26 Reserved for future function expansion. */

/* System registers available in all groups and banks */
#define EIWR		(28)
#define FWWR		(29)
#define DBWR		(30)
#define BSEL		(31)


/* BSEL Specifications */
typedef struct {
	unsigned char	bank;
	unsigned char	group;
	unsigned short	zero;
} T_bsel;

/* ECR Specifications */
#if 1
typedef union REGECR {
	struct {
		unsigned short	eicc;           /* Exception Code for EI Level Exception */
		unsigned short	fecc;           /* Exception Code for FE Level Exception */
	} 				lv;
	unsigned long 	cs;
} T_ecr;
#else
typedef	struct {
	unsigned short	eicc;           /* Exception Code for EI Level Exception */
	unsigned short	fecc;           /* Exception Code for FE Level Exception */
} T_ecr;
#endif

#define GROUP0		(0x00)			/* CPU function group */
#define GROUP16		(0x10)			/* Processor protection function group */
#define GROUP17		(0x11)			/* PMU function group */
#define GROUP12		(0x12)			/* PMU function group */
#define GROUP32		(0x20)			/* FPU function group */
#define GROUP255	(0xFF)			/* User group */

/* Allowed combinations Group 0 */
#define BANK_MAIN	(0)
#define EHSF0		(0x0010)		/* Exception handler switching function bank 0 */
#define EHSF1		(0x0011)		/* Exception handler switching function bank 1 */

/* Allowed combinations Group 0 */
#define HWDEF		(12)

/* Allowed combinations Group 16 */
#define PPV			(0x1000)		/* Processor protection violation bank */
#define PPS			(0x1001)		/* Processor protection setting bank */
#define SPB			(0x1010)		/* Software paging bank */

/* Allowed combinations Group 17 */
#define PMU			(0x1100)		/* PMU function bank */

/* Allowed combinations Group 32 */
#define FPUSTAT		(0x2000)		/* FPU status bank */

/* Allowed combinations Group 255 */
#define BANK0_USR	(0xff00)		/* User 0 bank */
#define BANKC_USR	(0xffff)		/* User compatible bank */



/* Register Bank EHSF0 */
#define SW_CTL		(0)
#define SW_CFG		(1)
#define SW_BASE		(3)

/* 
 * Register Bank EHSF1 
 * Write access only via
 * EHSF0->SW_CTL.SET
 */
#define EH_CFG		(1)
#define EH_RESET	(2)
#define EH_BASE		(3)

/*
 * G3M Definitions
 */
#define IFCR	(5)		/* register number 5, group 12, bank 0 */
#define BPCR	(8)		/* register number 8, group 12, bank 0 */

#if defined(__V850E3__)
/* 
 * void __LDSR( regID, selID, val);
 */

#define SelectBank(n) 	__LDSR( BSEL, n)
#else
#define SelectBank(n) 	__LDSR( BSEL, n)
#define SetSWBase(a)	\
	__LDSR( EHSF0_SW_BASE, a);	    /* Set Base register */ \
	__LDSR( EHSF0_SW_CFG, RINT);    /* transfer values */	\
	__LDSR( EHSF0_SW_CTL, 1);       /* transfer values */	\
	__asm("nop");
#endif		/* __V850E3__ */

#endif

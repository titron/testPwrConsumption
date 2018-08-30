/*===========================================================================*/
/* Module       = dr7f7015273.ld                                              */
/* Version      = E1.00a                                                     */
/*                manually created                                           */
/*                                                                           */
/*===========================================================================*/
/*                                  COPYRIGHT                                */
/*===========================================================================*/
/* Copyright (c) 2013 by Renesas Electronics Europe GmbH,                    */
/*               a company of the Renesas Electronics Corporation            */
/*===========================================================================*/
/* Purpose:     Template of linker directive file                            */
/*                                                                           */
/*===========================================================================*/
/*                                                                           */
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
/* Environment:                                                              */
/*              Device:         R7F701527xAFP                                */
/*              IDE:            GHS Multi for V800  V6.xx or later           */
/*===========================================================================*/


MEMORY
 {
  iROM_0        : ORIGIN = 0x00000000,  LENGTH = 1024k
  iROM_z        : ORIGIN = 0x00100000,  LENGTH = 1024k
  iROM_1        : ORIGIN = 0x00800000,  LENGTH = 2048k
  iROM_1_TOP    : ORIGIN = .         ,  LENGTH = 0
  iROM_2        : ORIGIN = 0x01000000,  LENGTH = 32k
  iROM_2_TOP    : ORIGIN = .         ,  LENGTH = 0
  iRAM_0        : ORIGIN = 0xFE9E0000,  LENGTH = 128k            // Local RAM for PE2
  iRAM_0_TOP    : ORIGIN = .         ,  LENGTH = 0
  iRAM_1        : ORIGIN = 0xFEBE0000,  LENGTH = 128k            // Local RAM for PE1
  iRAM_1_TOP    : ORIGIN = .         ,  LENGTH = 0
  iRAM_Self     : ORIGIN = 0xFEDE0000,  LENGTH = 128k            // Local RAM self
  iRAM_Self_TOP : ORIGIN = .         ,  LENGTH = 0
  gRAM_0        : ORIGIN = 0xFEEF8000,  LENGTH = 32k             // Global RAM Bank 0
  gRAM_0_TOP    : ORIGIN = .         ,  LENGTH = 0
  gRAM_1        : ORIGIN = 0xFEFF8000,  LENGTH = 32k             // Global RAM Bank 1
  gRAM_1_TOP    : ORIGIN = .         ,  LENGTH = 0
  iRAM_R        : ORIGIN = 0xFEF00000,  LENGTH = 64k            // Retention RAM
  iRAM_R_TOP    : ORIGIN = .         ,  LENGTH = 0
 }


/*===========================================================================*/
/*      End of File                                                          */
/*===========================================================================*/

//============================================================================
// PROJECT  : NEC FlexRay driver 
// MODULE   : FR.h
// VERSION  : 0.1
// DATE     : 10.11.2003
//============================================================================
//                           C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2002 by NEC Electronics (Europe) GmbH. All rights reserved.
//============================================================================
// Warranty Disclaimer :
// Because the Product(s) is licensed free of charge, there is no warranty of
// any kind whatsoever and expressly disclaimed and excluded by NEC, either
// expressed or implied, including but not limited to those for non-
// infringement of intellectual property, merchantability and/or fitness for
// the particular purpose. NEC shall not have any obligation to maintain,
// service or provide bug fixes for the supplied Product(s) and/or the
// Application.

//============================================================================
// Defines
//============================================================================
//#define Application_1
////#undef Application_1
//
//#define Application_2
//#undef Application_2
//
//#define Application_3
//#undef Application_3

//============================================================================
// Includes
//============================================================================

#include <map_fr.h>

#define GLOBALDEFINES_VARS
#include "GlobalDefines.h"
#undef GLOBALDEFINES_VARS

#define TYPEDEFINES_VARS
#include "TypeDefines.h"
#undef TYPEDEFINES_VARS

#define FLEXRAY_SERVICE_PARAMETER_VARS
#include "FrDrv_service_parameter.h"
#undef FLEXRAY_SERVICE_PARAMETER_VARS

#define FLEXRAY_DATA_TRANSFER_VARS
#include "FrDrv_data_transfer.h"
#undef FLEXRAY_DATA_TRANSFER_VARS


#ifndef FLEXRAY_H
#define FLEXRAY_H

#ifdef FLEXRAY_VARS
#define _EXTERN_
#else
#define _EXTERN_ extern
#endif


//============================================================================
// Defines
//============================================================================
#define RH850
//#undef RH850
//#define V850
#undef V850

// FR_CC Base address,
#ifdef RH850
#define FR_BASE_ADDR 0x10020000
#endif

#ifdef V850
#define FR_BASE_ADDR 0xff580000
#endif

// Register address offset

// Customer Registers
#define CR1_REG   ( 0x0000 + FR_BASE_ADDR ) // Customer register 1 
#define CR2_REG   ( 0x0004 + FR_BASE_ADDR ) // Customer register 2
#define CR3_REG   ( 0x0008 + FR_BASE_ADDR ) // Customer register 3
#define CR4_REG   ( 0x000C + FR_BASE_ADDR ) // Customer register 4
               
#define TEST1_REG ( 0x0010 + FR_BASE_ADDR ) // Test Register 1
#define TEST2_REG ( 0x0014 + FR_BASE_ADDR ) // Test Register 2
#define LCK_REG   ( 0x001C + FR_BASE_ADDR ) // Lock Register

// Interrupt Registers
#define EIR_REG   ( 0x0020 + FR_BASE_ADDR ) // Error Interrupt register
#define SIR_REG   ( 0x0024 + FR_BASE_ADDR ) // Status Interrupt register
#define EILS_REG  ( 0x0028 + FR_BASE_ADDR ) // Error Interrupt Line Select
#define SILS_REG  ( 0x002C + FR_BASE_ADDR ) // Status Interrupt Linje Select
#define EIES_REG  ( 0x0030 + FR_BASE_ADDR ) // Error Interrupt Enable Set
#define EIER_REG  ( 0x0034 + FR_BASE_ADDR ) // Error Interrupt Enable Reset
#define SIES_REG  ( 0x0038 + FR_BASE_ADDR ) // Status Interrupt Enable Set
#define SIER_REG  ( 0x003C + FR_BASE_ADDR ) // Status Interrupt Enable Reset
#define ILE_REG   ( 0x0040 + FR_BASE_ADDR ) // Interrupt Line Enable
#define T0C_REG   ( 0x0044 + FR_BASE_ADDR ) // Timer 0 Configuration
#define T1C_REG   ( 0x0048 + FR_BASE_ADDR ) // Timer 1 Configuration
#define STPW1_REG ( 0x004C + FR_BASE_ADDR ) // Stop Watch Register 1
#define STPW2_REG ( 0x0050 + FR_BASE_ADDR ) // Stop Watch Register 2
            
// CC Control Registers
#define SUCC1_REG   ( 0x0080 + FR_BASE_ADDR ) // SUC Configuration register 1
#define SUCC2_REG   ( 0x0084 + FR_BASE_ADDR ) // SUC Configuration register 2
#define SUCC3_REG   ( 0x0088 + FR_BASE_ADDR ) // SUC Configuration register 3
#define NEMC_REG    ( 0x008C + FR_BASE_ADDR ) // NEM Configuration Register
#define PRTC1_REG   ( 0x0090 + FR_BASE_ADDR ) // PRT Configuration Register 1
#define PRTC2_REG   ( 0x0094 + FR_BASE_ADDR ) // PRT Configuration Register 2
#define MHDC_REG    ( 0x0098 + FR_BASE_ADDR ) // MHD Configuration Register
#define GTUC1_REG   ( 0x00A0 + FR_BASE_ADDR ) // GTU Configuration Register 1
#define GTUC2_REG   ( 0x00A4 + FR_BASE_ADDR ) // GTU Configuration Register 2
#define GTUC3_REG   ( 0x00A8 + FR_BASE_ADDR ) // GTU Configuration Register 3
#define GTUC4_REG   ( 0x00AC + FR_BASE_ADDR ) // GTU Configuration Register 4
#define GTUC5_REG   ( 0x00B0 + FR_BASE_ADDR ) // GTU Configuration Register 5
#define GTUC6_REG   ( 0x00B4 + FR_BASE_ADDR ) // GTU Configuration Register 6
#define GTUC7_REG   ( 0x00B8 + FR_BASE_ADDR ) // GTU Configuration Register 7
#define GTUC8_REG   ( 0x00BC + FR_BASE_ADDR ) // GTU Configuration Register 8
#define GTUC9_REG   ( 0x00C0 + FR_BASE_ADDR ) // GTU Configuration Register 9
#define GTUC10_REG  ( 0x00C4 + FR_BASE_ADDR ) // GTU Configuration Register 10
#define GTUC11_REG  ( 0x00C8 + FR_BASE_ADDR ) // GTU Configuration Register 11
           
// CC Status Registers
#define CCSV_REG    ( 0x0100 + FR_BASE_ADDR ) // CC Status Vector
#define CCEV_REG  ( 0x0104 + FR_BASE_ADDR )   // CC Error Vector
#define SCV_REG   ( 0x0110 + FR_BASE_ADDR )   // Slot Counter Value
#define MTCCV_REG ( 0x0114 + FR_BASE_ADDR )   // Macrottick and Cycle Counter Value
#define RCV_REG   ( 0x0118 + FR_BASE_ADDR )   // Rate Correction Value
#define OCV_REG   ( 0x011C + FR_BASE_ADDR )   // Offset Correction Value
#define SFS_REG   ( 0x0120 + FR_BASE_ADDR )   // Sync Frame Status
#define SWNIT_REG ( 0x0124 + FR_BASE_ADDR )   // Symbol Window and NIT Status
#define ACS_REG   ( 0x0128 + FR_BASE_ADDR )   // Aggregated Channel Status
#define ESID_REG  ( 0x0130 + FR_BASE_ADDR )   // Even Sync ID
#define OSID_REG  ( 0x0170 + FR_BASE_ADDR )   // Odd Sync ID
#define NMV1_REG  ( 0x01B0 + FR_BASE_ADDR )   // Network Management Vector 1
#define NMV2_REG  ( 0x01B4 + FR_BASE_ADDR )   // Network Management Vector 2
#define NMV3_REG  ( 0x01B8 + FR_BASE_ADDR )   // Network Management Vector 3
                
// Message Buffer Control Registers
#define MRC_REG     ( 0x0300 + FR_BASE_ADDR ) // Message RAM Configuration
#define FRF_REG     ( 0x0304 + FR_BASE_ADDR ) // FIFO Rejection Filter
#define FRFM_REG    ( 0x0308 + FR_BASE_ADDR ) // FIFO Rejection Filter Mask
           
// Message Buffer Status Registers
#define FCL_REG   ( 0x030C + FR_BASE_ADDR )   // FIFO Critical Level
#define MHDS_REG  ( 0x0310 + FR_BASE_ADDR )   // Message Handler Status
#define LDTS_REG  ( 0x0314 + FR_BASE_ADDR )   // Last Dynamic Transmit Slot
#define FSR_REG   ( 0x0318 + FR_BASE_ADDR )   // FIFO Status Register
#define MHDF_REG  ( 0x031C + FR_BASE_ADDR )   // Message handler Constraints Flag
#define TXTQ1_REG ( 0x0320 + FR_BASE_ADDR )   // Transmission Request Register 1
#define TXRQ2_REG ( 0x0324 + FR_BASE_ADDR )   // Transmission Request Register 2
#define TXTQ3_REG ( 0x0328 + FR_BASE_ADDR )   // Transmission Request Register 3
#define TXRQ4_REG ( 0x032C + FR_BASE_ADDR )   // Transmission Request Register 4
#define NDAT1_REG ( 0x0330 + FR_BASE_ADDR )   // New Data Register 1
#define NDAT2_REG ( 0x0334 + FR_BASE_ADDR )   // New Data Register 2
#define NDAT3_REG ( 0x0338 + FR_BASE_ADDR )   // New Data Register 3
#define NDAT4_REG ( 0x033C + FR_BASE_ADDR )   // New Data Register 4
#define MBSC1_REG ( 0x0340 + FR_BASE_ADDR )   // Message Buffer Status Changed 1
#define MBSC2_REG ( 0x0344 + FR_BASE_ADDR )   // Message Buffer Status Changed 2            
#define MBSC3_REG ( 0x0348 + FR_BASE_ADDR )   // Message Buffer Status Changed 3
#define MBSC4_REG ( 0x034C + FR_BASE_ADDR )   // Message Buffer Status Changed 4  

// Identification Registers
#define CREL_REG  ( 0x03F0 + FR_BASE_ADDR )   // Core Release Register
#define ENDN_REG  ( 0x03F4 + FR_BASE_ADDR )   // Endian Register
              
// Input Buffer   
#define WRDS_REG  ( 0x400 + FR_BASE_ADDR )    // Write Data Section [1..64]
#define WRHS1_REG ( 0x500 + FR_BASE_ADDR )    // Write Header Section 1
#define WRHS2_REG ( 0x504 + FR_BASE_ADDR )    // Write Header Section 2
#define WRHS3_REG ( 0x508 + FR_BASE_ADDR )    // Write Header Section 3
#define IBCM_REG  ( 0x510 + FR_BASE_ADDR )    // Input Buffer Command Mask
#define IBCR_REG  ( 0x514 + FR_BASE_ADDR )    // Input Buffer Command Request
          
// Output Buffer  
#define RDDS_REG  ( 0x600 + FR_BASE_ADDR )    // Read Data Section [1..64]
#define RDHS1_REG ( 0x700 + FR_BASE_ADDR )    // Read Header Section 1
#define RDHS2_REG ( 0x704 + FR_BASE_ADDR )    // Read Header Section 2
#define RDHS3_REG ( 0x708 + FR_BASE_ADDR )    // Read Header Section 3
#define MBS_REG   ( 0x70C + FR_BASE_ADDR )    // Message Buffer Status
#define OBCM_REG  ( 0x710 + FR_BASE_ADDR )    // Output Buffer Command Mask
#define OBCR_REG  ( 0x714 + FR_BASE_ADDR )    // Output Buffer Command Request

// NEW REGISTERS (Dejan)
#define ITC_REG   ( 0x800 + FR_BASE_ADDR )    // Input Transfer Configuration
#define OTC_REG   ( 0x804 + FR_BASE_ADDR )    // Output Transfer Configuration
#define IBA_REG   ( 0x808 + FR_BASE_ADDR )    // Input pointer table Base Address
#define FBA_REG   ( 0x80C + FR_BASE_ADDR )    // FIFO pointer table Base Address
#define OBA_REG   ( 0x810 + FR_BASE_ADDR )    // Output pointer table Base Address
#define IQC_REG   ( 0x814 + FR_BASE_ADDR )    // Input Queue Control
#define UIR_REG   ( 0x818 + FR_BASE_ADDR )    // User Input transfer Request
#define UOR_REG   ( 0x81C + FR_BASE_ADDR )    // User Output transfer Request
#define ITS_REG   ( 0x820 + FR_BASE_ADDR )    // Input Transfer Status
#define OTS_REG   ( 0x824 + FR_BASE_ADDR )    // Output Transfer Status
#define AES_REG   ( 0x828 + FR_BASE_ADDR )    // Access Error Status
#define AEA_REG   ( 0x82C + FR_BASE_ADDR )    // Access Error Address

#define DA0_REG   ( 0x830 + FR_BASE_ADDR )    // message Data Available register 0
#define DA1_REG   ( 0x834 + FR_BASE_ADDR )    // message Data Available register 1
#define DA2_REG   ( 0x838 + FR_BASE_ADDR )    // message Data Available register 2
#define DA3_REG   ( 0x83C + FR_BASE_ADDR )    // message Data Available register 3

#define AHBC_REG  ( 0x840 + FR_BASE_ADDR )    // AHB Configuration
#define T2C_REG   ( 0x844 + FR_BASE_ADDR )    // Timer 2 Configuration
#define MTC_REG   ( 0x8D0 + FR_BASE_ADDR )    // Global Macrotick Timer Activation Status
#define MTAS_REG  ( 0x8D4 + FR_BASE_ADDR )    // Macrotick Timer Activation Status
#define MTES_REG  ( 0x8D8 + FR_BASE_ADDR )    // Macrotick Timer Expiration Status
#define MTEI_REG  ( 0x8DC + FR_BASE_ADDR )    // Macrotick Timer Expiration Index

#define MTC0_REG  ( 0x900 + FR_BASE_ADDR )    // Macrotick Timer Control register 0
#define MTC1_REG  ( 0x904 + FR_BASE_ADDR )    // Macrotick Timer Control register 1
#define MTC2_REG  ( 0x908 + FR_BASE_ADDR )    // Macrotick Timer Control register 2
#define MTC3_REG  ( 0x90C + FR_BASE_ADDR )    // Macrotick Timer Control register 3
#define MTC4_REG  ( 0x910 + FR_BASE_ADDR )    // Macrotick Timer Control register 4
#define MTC5_REG  ( 0x914 + FR_BASE_ADDR )    // Macrotick Timer Control register 5
#define MTC6_REG  ( 0x918 + FR_BASE_ADDR )    // Macrotick Timer Control register 6
#define MTC7_REG  ( 0x91C + FR_BASE_ADDR )    // Macrotick Timer Control register 7
#define MTC8_REG  ( 0x920 + FR_BASE_ADDR )    // Macrotick Timer Control register 8
#define MTC9_REG  ( 0x924 + FR_BASE_ADDR )    // Macrotick Timer Control register 9
#define MTC10_REG ( 0x928 + FR_BASE_ADDR )    // Macrotick Timer Control register 10
#define MTC11_REG ( 0x92C + FR_BASE_ADDR )    // Macrotick Timer Control register 11
#define MTC12_REG ( 0x930 + FR_BASE_ADDR )    // Macrotick Timer Control register 12
#define MTC13_REG ( 0x934 + FR_BASE_ADDR )    // Macrotick Timer Control register 13
#define MTC14_REG ( 0x938 + FR_BASE_ADDR )    // Macrotick Timer Control register 14
#define MTC15_REG ( 0x93C + FR_BASE_ADDR )    // Macrotick Timer Control register 15
#define MTC16_REG ( 0x940 + FR_BASE_ADDR )    // Macrotick Timer Control register 16
#define MTC17_REG ( 0x944 + FR_BASE_ADDR )    // Macrotick Timer Control register 17
#define MTC18_REG ( 0x948 + FR_BASE_ADDR )    // Macrotick Timer Control register 18
#define MTC19_REG ( 0x94C + FR_BASE_ADDR )    // Macrotick Timer Control register 19
#define MTC20_REG ( 0x950 + FR_BASE_ADDR )    // Macrotick Timer Control register 20
#define MTC21_REG ( 0x954 + FR_BASE_ADDR )    // Macrotick Timer Control register 21
#define MTC22_REG ( 0x958 + FR_BASE_ADDR )    // Macrotick Timer Control register 22
#define MTC23_REG ( 0x95C + FR_BASE_ADDR )    // Macrotick Timer Control register 23
#define MTC24_REG ( 0x960 + FR_BASE_ADDR )    // Macrotick Timer Control register 24
#define MTC25_REG ( 0x964 + FR_BASE_ADDR )    // Macrotick Timer Control register 25
#define MTC26_REG ( 0x968 + FR_BASE_ADDR )    // Macrotick Timer Control register 26
#define MTC27_REG ( 0x96C + FR_BASE_ADDR )    // Macrotick Timer Control register 27
#define MTC28_REG ( 0x970 + FR_BASE_ADDR )    // Macrotick Timer Control register 28
#define MTC29_REG ( 0x974 + FR_BASE_ADDR )    // Macrotick Timer Control register 29
#define MTC30_REG ( 0x978 + FR_BASE_ADDR )    // Macrotick Timer Control register 30
#define MTC31_REG ( 0x97C + FR_BASE_ADDR )    // Macrotick Timer Control register 31
                
// FRCC commands
#define CONFIG                   1
#define READY                    2
#define WAKEUP                   3
#define RUN                      4
#define ALL_SLOTS                5
#define HALT                     6
#define FREEZE                   7
#define SEND_MTS                 8
#define ALLOW_COLDSTART          9
#define RESET_STATUS_INDICATORS 10
#define MONITOR_MODE            11
#define CLEAR_RAMS              12
#define LOOP_BACK_MODE          15


// MB header structure
struct FR_MB_header
{
  u32 fid;        
  u32 cyc;    
  u32 cha;  
  u32 chb;  
  u32 cfg;  
  u32 nme;  
  u32 txm;  
  u32 mbi;  
  u32 crc;      
  u32 plc;
  u32 plr;
  u32 dp; 
  u32 rcc;
  u32 rci;
  u32 sfi;
  u32 syn;
  u32 nfi;
  u32 ppi;
  u32 res;
};

// Test mode
#define NormalOperationMode   0x000
#define RAMTestMode           0x001
#define DriveOutputPins       0x010
 
// Message Buffer section
#define MBRAM_1 0x000
#define MBRAM_2 0x001
#define MBRAM_3 0x010
#define MBRAM_4 0x011
#define MBRAM_5 0x100

// WTRE (Write Test Register Enable) bit of the SUCC1 register
#define WTREN_SET    1
#define WTREN_CLEAR  0


#endif

#ifdef _EXTERN_
#undef _EXTERN_
#endif

/* end of file*/ 

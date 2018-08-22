//============================================================================
// PROJECT  : REE FlexRay driver 
// MODULE   : flexray_data_transfer.c
// VERSION  : 0.2
// DATE     : 02.10.2013
//============================================================================
//                           C O P Y R I G H T                                    
//============================================================================
// Copyright (c) 2013 by REE Electronics (Europe) GmbH. All rights reserved.
// Arcadiastr. 10
// D-40472 Duesseldorf
// Germany
//============================================================================
//
// Warranty Disclaimer :
// Because the Product(s) is licensed free of charge, there is no warranty of
// any kind whatsoever and expressly disclaimed and excluded by REE, either
// expressed or implied, including but not limited to those for non-
// infringement of intellectual property, merchantability and/or fitness for
// the particular purpose. REE shall not have any obligation to maintain,
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
// In no event shall REE be liable to the User for any incidental,
// consequential, indirect, or punitive damage (including but not limited to
// lost profits) regardless of whether such liability is based on breach of
// contract, tort, strict liability, breach of warranties, failure of
// essential purpose or otherwise and even if advised of the possibility of
// such damages. REE shall not be liable for any services or products provided
// by third party vendors, developers or consultants identified or referred
// to the User by REE in connection with the Product(s) and/or the
// Application.
//
//============================================================================
// Enviroment : Devices    : RH850/P1x-C
//              Assembler  : GHS Multi              Version : 6.1.4
//              C-Compiler : GHS Multi              Version : 6.1.4
//              Linker     : GHS Multi              Version : 6.1.4       
//              Debugger   : GHS Multi              Version : 6.1.4
//============================================================================
// Version    Author                       Description
// 0.1        H. Schmerling                Initial Release
// 0.2        P. Szczupak                  Modified for P1x-C device
//============================================================================


//============================================================================
// Includes                                                                  
//============================================================================
#include "FrDrv.h"
#include "GlobalDefines.h"
#include "TypeDefines.h"


//============================================================================
// Prototypes
//============================================================================
Fr_ReturnType FrDrv_data_HOST_to_IB ( u32 *data_u32, u08 data_words_u08 );
Fr_ReturnType FrDrv_data_IB_to_MB ( u08 mb_u08 );
Fr_ReturnType FrDrv_data_IB_to_TRAM ( u08 mb_u08 );
Fr_ReturnType FrDrv_data_MB_to_TRAM ( u08 mb_u08 );
Fr_ReturnType FrDrv_data_OBF_to_HOST ( u32 *data_u32, u08 data_words_u08 );
Fr_ReturnType FrDrv_data_MB_to_OBF ( u08 mb_u08 );
void FrDrv_header_to_MB ( struct FR_MB_header header, u08 mb_u08 );
struct FR_MB_header  FrDrv_header_to_host ( u08 mb_u08 );
u32 FrDrv_crc ( u08 mb_u08 );
u32 FrDrv_header_cal ( u08 mb_u08 );
u16 FrDrv_read_16bit ( u32 addr_u32 );
u32 FrDrv_read_32bit ( u32 addr_u32 );
void FrDrv_write_16bit ( u32 addr, u16 data_u16 );
void FrDrv_write_32bit ( u32 addr, u32 data_u32 );
void WRITE32 ( u32 data_u32, u32 addr_u32 );


//============================================================================
// Functions
//============================================================================

Fr_ReturnType FrDrv_data_HOST_to_IB ( u32 *data_u32, u08 data_words_u08 ) {
//=============================================================================
// FunctionName: FrDrv_data_HOST_to_IB
// IN: transmit data, length of transmit data in 4 bytes unit
// OUT:  REE FlexRay return value
// Description: Copy data from CPU RAM to E-Ray input buffer
//=============================================================================  
  u32 wrds_reg_u32; 
  u32 * d_u32;
  
  // check if input buffer busy by the message handler
  while ( ( FrDrv_read_32bit ( IBCR_REG ) & 0x8000 ) != 0 ) {

  } // end of while
  
  wrds_reg_u32 = WRDS_REG ; 
  d_u32 = data_u32 + data_words_u08;
    
  while ( d_u32 != data_u32 ) {
       
    FrDrv_write_32bit ( wrds_reg_u32, *data_u32 );
    data_u32  += 1;
    wrds_reg_u32 += 4;       

  } // ende of while
   
  return FLEXRAY_STATUS_OK;
}

Fr_ReturnType FrDrv_data_IB_to_MB ( u08 mb_u08 ) {
//=============================================================================
// FunctionName: FrDrv_data_IB_to_MB
// IN: number of E-Ray message buffer
// OUT:  REE FlexRay return value
// Description: Transmits data from the E-Ray input buffer to the E-Ray message 
//              buffer
//=============================================================================  
  
   //IB, IBCMR - Input Buffer Command Mask Tegister
   FrDrv_write_16bit ( IBCM_REG, 0x02 );

   // check if input buffer busy by the message handler
   while ( ( ( FrDrv_read_32bit ( IBCR_REG ) & 0x8000 ) != 0 ) ) {

   } // end of while
          
   //IB, IBCRR - Input Buffer Command Request Register
  FrDrv_write_16bit ( IBCR_REG, mb_u08 );
               
   return FLEXRAY_STATUS_OK;
}

Fr_ReturnType FrDrv_data_IB_to_TRAM ( u08 mb_u08 ) {
//=============================================================================
// IN: number of E-Ray message buffer
// FunctionName: FrDrv_data_IB_to_TRAM
// OUT:  REE FlexRay return value    
// Description: Transmits data from the E-Ray input buffer direct to the E-Ray 
//              transient RAM
//=============================================================================  

   //IB, IBCMR - Input Buffer Command Mask Tegister
   FrDrv_write_32bit ( IBCM_REG, 0x00060006 );
   
   // check if input buffer busy by the message handler
   while ( ( ( FrDrv_read_32bit ( IBCR_REG ) & 0x8000 ) != 0 ) ) {

   } // end of while

   //IB, IBCRR - Input Buffer Command Request Register          
  FrDrv_write_32bit ( IBCR_REG, mb_u08 );
   
  return FLEXRAY_STATUS_OK;
}

Fr_ReturnType FrDrv_data_MB_to_TRAM ( u08 mb_u08 ) {
//=============================================================================
// FunctionName: FrDrv_data_MB_to_TRAM
// IN: number of E-Ray message buffer     
// OUT:  REE FlexRay return value 
// Description: Transmit data from the E-Ray message RAM to the transient RAM
//=============================================================================  

  //IB, IBCMR - Input Buffer Command Mask Tegister
  FrDrv_write_16bit ( IBCM_REG, 0x04 );

  //IB, IBCRR - Input Buffer Command Request Register
  FrDrv_write_16bit ( IBCR_REG, mb_u08 );
   
  return MESSAGE_BUFFER_OK;
}

Fr_ReturnType FrDrv_data_OBF_to_HOST ( u32 *data_u32, u08 data_words_u08 ) {
//==============================================================================
// FunctionName: FrDrv_data_OBF_to_HOST
// IN: pointer to the RAM, where the data should be copied, 
//     length of receive data in 4 bytes unit 
// OUT:  REE FlexRay return value 
// Description: Copy data from the E-Ray output buffer to the CPU RAM
//==============================================================================  
  u32 rdds_reg_u32; 
  u32 * d_u32;
    
  // check if output buffer busy by the message handler
  while ( ((FrDrv_read_16bit ( OBCR_REG ) & 0x8000) != 0) ) {

  } // end of while

  //OB, OBCRR - Output Buffer Command Request Register
  FrDrv_write_16bit ( OBCR_REG, 0x0100 );

  // check if output buffer busy by the message handler
  while ( ( ( FrDrv_read_16bit ( IBCR_REG ) & 0x8000 ) != 0 ) ) {

  } // end of while

  rdds_reg_u32 = RDDS_REG ; 
  d_u32 = data_u32 + data_words_u08;
  
  while ( d_u32 != data_u32 ) {

    *data_u32 = FrDrv_read_32bit ( rdds_reg_u32 );
    data_u32  += 1 ;       
    rdds_reg_u32 += 4;
    
  } // end of while 

  return FLEXRAY_STATUS_OK;
}

Fr_ReturnType FrDrv_data_MB_to_OBF ( u08 mb_u08 ) {
//=============================================================================
// FunctionName: FrDrv_data_MB_to_OBF
// IN: number of E-Ray message buffer
// OUT:  REE FlexRay return value 
// Description: Tranmit data from the E-Ray message buffer the E-Ray output 
//              buffer
//=============================================================================  
  u16   value_u16;
  
  if ( mb_u08 <= 31 ) {
       if ( ( ( FrDrv_read_32bit ( NDAT1_REG ) >> mb_u08 ) & 0x1 ) == FALSE ) {
           return MESSAGE_BUFFER_NO_DATA;
       } // end of if
  } else if ( (mb_u08 <= 63) & (mb_u08 > 31) ) {
       if ( ( ( FrDrv_read_32bit ( NDAT2_REG ) >> mb_u08 - 32 ) & 0x1 ) == FALSE ) {
           return MESSAGE_BUFFER_NO_DATA;
       } // end of if
  } else if ( (mb_u08 <= 95) & (mb_u08 > 63) ) {
       if ( ( ( FrDrv_read_32bit ( NDAT3_REG ) >> mb_u08 - 64 ) & 0x1 ) == FALSE ) {
           return MESSAGE_BUFFER_NO_DATA;
       } // end of if
  } else {
       if ( ( ( FrDrv_read_32bit ( NDAT4_REG ) >> mb_u08 - 96 ) & 0x1 ) == FALSE ) {
           return MESSAGE_BUFFER_NO_DATA;
       } // end of if
  } // end of if 

  //OB, OBCMR - Output Buffer Command Mask Register
  FrDrv_write_16bit ( OBCM_REG, 0x02 );   // Read Data Section
   
  // check if output buffer busy by the message handler
          while ( ( FrDrv_read_16bit ( OBCR_REG ) & 0x8000 ) != 0 ) {

  } // end of while
      
  //OB, OBCRR - Output Buffer Command Request Register
  value_u16 = 0;
  value_u16 |= ( mb_u08   & 0x7F );       // Message Buffer Select [5:0]
  value_u16 |=  0x1 << 9;                         // REQ
  FrDrv_write_16bit ( OBCR_REG, value_u16 );
   
  return MESSAGE_BUFFER_OK;
}

void FrDrv_header_to_MB ( struct FR_MB_header header, u08 mb_u08 ) {
//=============================================================================
// FunctionName: FrDrv_header_to_MB
// IN: message buffer header configuration, number of E-Ray message buffer
// OUT: -
// Description: Transmit the configuration data into the message buffer header
//              section
//=============================================================================  
  u32   value_u32;
  u16   value_u16;

  // IB, WRHS1 - Write Header Section 1
  value_u32 = 0;
  value_u32 |= ( header.fid   & 0x7FF );  // Frame ID [10:0]
  value_u32 |= ( header.cyc   & 0x7F )  << 16;  // Cycle Code [6:0] 
  value_u32 |= ( header.cha   & 0x1 ) << 24;  // Channel A Filter Control
  value_u32 |= ( header.chb   & 0x1 ) << 25;  // Channel B Filter Control
  value_u32 |= ( header.cfg   & 0x1 ) << 26;  // Message Buffer Configuration Bit
  value_u32 |= ( header.nme   & 0x1 ) << 27;  // Network Management Enable
  value_u32 |= ( header.txm   & 0x1 ) << 28;  // Transmission Mode
  value_u32 |= ( header.mbi   & 0x1 ) << 29;  // Message Buffer Interrupt
  FrDrv_write_32bit ( WRHS1_REG, value_u32 );

  // IB, WRHS3 - Write Header Section 3
  value_u32 = 0;
  value_u32 |= (header.dp   & 0x7FF); // Data Pointer [10:0]
  FrDrv_write_32bit ( WRHS3_REG, value_u32 );

  // IB, WRHS2 - Write Header Section 2
  value_u32 = 0;
  value_u32 |= (header.plc  & 0x7F) << 16;            // Payload Length [6:0] 
  value_u32 |= (FrDrv_crc ( mb_u08 )  & 0x7FF);         // Header CRC 
  FrDrv_write_32bit ( WRHS2_REG, value_u32 );

  // IB, IBCM - Input Buffer Command Mask Tegister
  value_u16 = 0;
  value_u16 |= 0x1;   // Load Header Section
  FrDrv_write_16bit ( IBCM_REG, value_u16 );

  // IB, IBCR - Input Buffer Command Request
  value_u16 = 0;
  value_u16 |= (mb_u08  & 0x7F);      // Message Buffer Select [5:0]
  FrDrv_write_16bit ( IBCR_REG, value_u16 );
}

struct FR_MB_header FrDrv_header_to_host ( u08 mb_u08 ) {
//=============================================================================
// FunctionName: FrDrv_header_to_host
// IN: number of E-Ray message buffer
// OUT: E-Ray message buffer header
// Description: Copies the E-Ray message buffer header to the CPU RAM
//=============================================================================  
  struct FR_MB_header header;
  u16   value_u16;

  FrDrv_write_16bit ( OBCM_REG, 0x01 ); // Load Header Section

  //OB, OBCRR - Output Buffer Command Request Register
  value_u16 = 0;
  value_u16 |= (mb_u08  & 0x7F);      // Message Buffer Select [5:0]
  FrDrv_write_16bit ( OBCR_REG, value_u16 );

  // IB, RDHS1 - Write Header Section 1
  header.fid = FrDrv_read_32bit (  RDHS1_REG )    & 0x7FF;  // Frame ID [10:0]
  header.cyc = (FrDrv_read_32bit ( RDHS1_REG )  >> 16) & 0x7F;  // Cycle Code [6:0] 
  header.cha = (FrDrv_read_32bit ( RDHS1_REG )  >> 24) & 0x1; // Channel A Filter Control
  header.chb = (FrDrv_read_32bit ( RDHS1_REG )  >> 25) & 0x1; // Channel B Filter Control
  header.cfg = (FrDrv_read_32bit ( RDHS1_REG )  >> 26) & 0x1; // Message Buffer Configuration Bit
  header.nme = (FrDrv_read_32bit ( RDHS1_REG )  >> 27) & 0x1; // Network Management Enable
  header.txm = (FrDrv_read_32bit ( RDHS1_REG )  >> 28) & 0x1; // Transmission Mode
  header.mbi = (FrDrv_read_32bit ( RDHS1_REG )  >> 29) & 0x1; // Message Buffer Interrupt

  // IB, WRHS3 - Write Header Section 3
  header.dp = FrDrv_read_32bit ( RDHS3_REG )     & 0x7FF;   // Data Pointer [10:0]

  // IB, WRHS2 - Write Header Section 2
  header.crc = FrDrv_read_32bit ( RDHS2_REG ) & 0x7FF;
  header.plc = (FrDrv_read_32bit ( RDHS2_REG )  >> 16) & 0x7F;      // Payload Length [6:0] 
  // Header CRC [10:0]

  return header;
}

u32 FrDrv_crc ( u08 mb_u08 ) {
//=============================================================================
// FunctionName: FrDrv_crc                     : FrDrv_crc
// IN: number of message buffer                       
// OUT: FlexRay frame header CRC calculation                     
// Description: Calculate the FlexRay frame header CRC
//============================================================================= 
  u32 CrcPoly_u32  = 0x385;             // CRC polynom
  u32 CrcReg_X_u32 = 0x1A;              // CRC register with initial value
  u32 CrcNext_u32;                      // CRC next input value
  u32 header_temp_u32, reg_temp_u32;    // help variables
  u32 len_u32      = 20;                // Header length

  u32 header_u32;

  header_u32 = FrDrv_header_cal ( mb_u08 );
  
  header_u32 <<= 11;
  CrcReg_X_u32 <<= 21;
  CrcPoly_u32 <<= 21;

  while ( len_u32 -- ) {
    header_u32 <<= 1;
    header_temp_u32 = header_u32 & 0x80000000;
    reg_temp_u32  = CrcReg_X_u32 & 0x80000000;
    if ( header_temp_u32 ^ reg_temp_u32 ) {
      CrcNext_u32 = 1;                    
    } else {         
      CrcNext_u32 = 0;
    } // end of if
                    
    CrcReg_X_u32 <<= 1;
    
    if ( CrcNext_u32 ) {
      CrcReg_X_u32 ^= CrcPoly_u32;                              
    } // end of if        
  } // end of while
         
  CrcReg_X_u32 >>= 21;
          
  return CrcReg_X_u32;
}

u32 FrDrv_header_cal ( u08 mb_u08 ) {
//=============================================================================
// FunctionName: FrDrv_header_cal
// IN: number of message buffer
// OUT: FlexRay frame header CRC
// Description: Calculate the FlexRay frame header CRC
//=============================================================================

  u08 syf_indicator_u08 = 0;        // Sync bit
  u08 suf_indicator_u08 = 0;        // Startup bit
  u16 frame_id_u16 = 0;         // Frame ID
  u08 length_u08 = 0;         // Payload length
  u32 header_crc_u32 = 0;       // FlexRay frame header

  if ( mb_u08 == 0 ) {  
    syf_indicator_u08 = ( FrDrv_read_32bit ( SUCC1_REG )  >> 9 ) & 0x1; // TXSY
    suf_indicator_u08 = ( FrDrv_read_32bit ( SUCC1_REG )  >> 8 ) & 0x1; // TXST
  } else {
    syf_indicator_u08 = ( 0 >> 9 ) & 0x1; // TXSY
    suf_indicator_u08 = ( 0 >> 8 ) & 0x1; // TXST
  }
      
  frame_id_u16 = FrDrv_read_32bit ( WRHS1_REG ) & 0x7FF;    // FID
  length_u08 =  ( FrDrv_read_32bit ( WRHS2_REG )  >> 16 ) & 0x7F; // PLC


  header_crc_u32 |= syf_indicator_u08;  // SYNC node bit
  header_crc_u32 <<= 1; 
  header_crc_u32 |= suf_indicator_u08;  // Startup node bit
  header_crc_u32 <<= 11;   
  header_crc_u32 |= frame_id_u16;       // Frame ID
  header_crc_u32 <<= 7;    
  header_crc_u32 |= length_u08;         // Payload length
  
  return ( header_crc_u32 );
}

u16 FrDrv_read_16bit ( u32 addr_u32 ) {
//=============================================================================
// FunctionName: FrDrv_read_16bit
// IN: Address value
// OUT: 16-bit data
// Description: Copy data from E-Ray register/RAM to CPU RAM
//=============================================================================
  volatile u16 data_u16 = 0;
  volatile u16 * BaseAddr_u16 = ( u16 * ) ( ( char * ) ( addr_u32 ) );

  data_u16 = BaseAddr_u16[0];
  
  return data_u16;
}

u32 FrDrv_read_32bit ( u32 addr_u32 ) {
//=============================================================================
// FunctionName: FrDrv_read_32bit
// IN: Address value
// OUT: 32-bit data
// Description: Copy data from E-Ray register/RAM to CPU RAM
//=============================================================================
  volatile u32 data_u32 = 0;
  volatile u32 * BaseAddr_u32 = ( u32 * ) ( ( char * ) ( addr_u32 ) );
  
  data_u32 = BaseAddr_u32[0];
  return data_u32;  
}

void FrDrv_write_16bit ( u32 addr_u32, u16 data_u16 ) {
//=============================================================================
// FunctionName: FrDrv_write_16bit
// IN: Address value, 16-bit data
// OUT: -
// Description: Copy data from CPU RAM to E-Ray register/RAM
//=============================================================================
  volatile u16 * BaseAddr_u16 = ( u16 * ) ( ( char * ) ( addr_u32 ) );

  BaseAddr_u16[0] = data_u16;
}

void FrDrv_write_32bit ( u32 addr_u32, u32 data_u32 ) {
//=============================================================================
// FunctionName: FrDrv_write_32bit
// IN: Address value, 32-bit data
// OUT: -
// Description: Copy data from CPU RAM to E-Ray register/RAM
//=============================================================================
  volatile u32 * BaseAddr_u32 = ( u32 * ) ( ( char * ) ( addr_u32 ) );  

  BaseAddr_u32[0] = data_u32;  
}

void WRITE32 ( u32 data_u32, u32 addr_u32 ) {
//=============================================================================
// FunctionName: WRITE32
// IN: 32-bit data, Address value
// OUT: -
// Description: Special function for copying Decomsys .chi file data to E-Ray
//              register
//=============================================================================
  volatile u32 * BaseAddr_u32 = ( u32 * ) ( ( char * ) ( addr_u32 ) );
  
  BaseAddr_u32[0] = data_u32;
}

// end of file

/*
 * riic_application.c
 *
 *  Created on: 2018Äê9ÔÂ5ÈÕ
 *      Author: a5059726
 */


/* for MasterSend(Pattern 1) */
#include "platform.h"
#include "r_riic_rh850f1x_if.h"

//#define I2C_ADDR_CPLD_CONFIG (0x20)
//#define I2C_ADDR_CPLD_CONFIG (0x3C)
//#define I2C_ADDR_CPLD_CONFIG (0x3D)
//#define I2C_ADDR_CPLD_CONFIG (0x3E)
#define I2C_ADDR_CPLD_CONFIG (0x4D)

riic_info_t iic_info_m;

void CallbackMaster(void);

void riic_app(void)
{
	volatile riic_return_t ret;
	uint32_t addr_eeprom[1] = {0x50};
	uint32_t access_addr1[1] = {0x00};
	uint32_t mst_send_data[5] = {0x00,0xff,0x55,0xaa,0x33};
	/* Sets IIC Information for sending pattern 1. */
	iic_info_m.dev_sts = RIIC_NO_INIT;
	iic_info_m.ch_no = 0;
	iic_info_m.callbackfunc = &CallbackMaster;
	iic_info_m.cnt2nd = 3;
	iic_info_m.cnt1st = 1;
	iic_info_m.p_data2nd = mst_send_data;
	iic_info_m.p_data1st = access_addr1;
	iic_info_m.p_slv_adr = addr_eeprom;

	/* RIIC open */
	ret = R_RIIC_Open(&iic_info_m);
	/* RIIC send start */
	ret = R_RIIC_MasterSend(&iic_info_m);
	if (RIIC_SUCCESS == ret)
	{
	while(RIIC_FINISH != iic_info_m.dev_sts);
	}
	else
	{
	/* error */
	}
	/* RIIC send complete */
	while(1);
}

void CallbackMaster(void)
{
	volatile riic_return_t ret;
	riic_mcu_status_t iic_status;
	ret = R_RIIC_GetStatus(&iic_info_m, &iic_status);
	if(RIIC_SUCCESS != ret)
	{
	/* Call error processing for the R_RIIC_GetStatus() function */
	}
	else
	{
	/* Processing when a timeout, arbitration-lost, NACK,
	or others is detected by verifying the iic_status flag. */
	}
}

void Cetic_GET_EXP_WUP_STS(void)
{
	volatile riic_return_t ret;
	uint8_t addr_eeprom[1] = {I2C_ADDR_CPLD_CONFIG};
	uint8_t access_addr1[1] = {0x00};
	uint8_t mst_store_area[20] = {0xFF,0xFF,0xFF,0xFF,0xFF,
			                      0xFF,0xFF,0xFF,0xFF,0xFF,
								  0xFF,0xFF,0xFF,0xFF,0xFF,
								  0xFF,0xFF,0xFF,0xFF,0xFF,};
	/* Sets IIC Information. */
	iic_info_m.dev_sts = RIIC_NO_INIT;
	iic_info_m.ch_no = 0;
	iic_info_m.callbackfunc = &CallbackMaster;
	iic_info_m.cnt2nd = 4;
	iic_info_m.cnt1st = 0;
	iic_info_m.p_data2nd = mst_store_area;
	iic_info_m.p_data1st = access_addr1;
	iic_info_m.p_slv_adr = addr_eeprom;
	/* RIIC open */
	ret = R_RIIC_Open(&iic_info_m);
	/* RIIC receive start */
	ret = R_RIIC_MasterReceive(&iic_info_m);
	if (RIIC_SUCCESS == ret)
	{
	while(RIIC_FINISH != iic_info_m.dev_sts);
	}
	else
	{
	/* error */
	}
	/* RIIC receive complete */
	while(1);
}

void Cetic_GET_MCU_WUP_STS(void)
{
	volatile riic_return_t ret;
	uint8_t addr_eeprom[1] = {I2C_ADDR_CPLD_CONFIG};
	uint8_t access_addr1[1] = {0x0E};
	uint8_t mst_store_area[30] = {0xFF,0xFF,0xFF,0xFF,0xFF,
			                      0xFF,0xFF,0xFF,0xFF,0xFF,
								  0xFF,0xFF,0xFF,0xFF,0xFF,
								  0xFF,0xFF,0xFF,0xFF,0xFF,
								  0xFF,0xFF,0xFF,0xFF,0xFF,
								  0xFF,0xFF,0xFF,0xFF,0xFF,};
	/* Sets IIC Information. */
	iic_info_m.dev_sts = RIIC_NO_INIT;
	iic_info_m.ch_no = 0;
	iic_info_m.callbackfunc = &CallbackMaster;
	iic_info_m.cnt2nd = 2;
	iic_info_m.cnt1st = 0;
	iic_info_m.p_data2nd = mst_store_area;
	iic_info_m.p_data1st = access_addr1;
	iic_info_m.p_slv_adr = addr_eeprom;
	/* RIIC open */
	ret = R_RIIC_Open(&iic_info_m);
	/* RIIC receive start */
	ret = R_RIIC_MasterReceive(&iic_info_m);
	if (RIIC_SUCCESS == ret)
	{
	while(RIIC_FINISH != iic_info_m.dev_sts);
	}
	else
	{
	/* error */
	}
	/* RIIC receive complete */
	while(1);
}

void Cetic_TRA_turn_On(uint32_t * psendData)
{
	volatile riic_return_t ret;
	uint32_t addr_eeprom[1] = {I2C_ADDR_CPLD_CONFIG};

	uint32_t access_addr1[1] = {0x00};
//	uint32_t mst_send_data[13] = {
//			0xff,// 0x0, output CAN enable0
//			0xff,// 0x1, output Can enable1
//			0xff,// 0x2, output CAN stbz0
//			0xff,// 0x3, output CAN stbz1
//			0x00,// 0x4, input CAN wake0
//			0x00,// 0X5, input CAN wake1
//			0x00,// 0x6, input rlin3x_mst
//			0xff,// 0x7, input rlin3x_slpz
//			0x00,// 0x8, input rlin3x_wakez
//			0xff,// 0x9, input rlin2x_slpz
//			0x00,// 0xA, input rlin2x_wakez
//			0x00,// 0xB, input can0 err
//			0x00,// 0xC, input can1 err
//	};
	uint32_t* pmst_send_data = psendData;
	/* Sets IIC Information for sending pattern 1. */
	iic_info_m.dev_sts = RIIC_NO_INIT;
	iic_info_m.ch_no = 0;
	iic_info_m.callbackfunc = &CallbackMaster;
	iic_info_m.cnt2nd = 13;
	iic_info_m.cnt1st = 1;
	iic_info_m.p_data2nd = pmst_send_data;
	iic_info_m.p_data1st = access_addr1;
	iic_info_m.p_slv_adr = addr_eeprom;

	/* RIIC open */
	ret = R_RIIC_Open(&iic_info_m);
	/* RIIC send start */
	/* Enable ENABLE pins */
	ret = R_RIIC_MasterSend(&iic_info_m);
	if (RIIC_SUCCESS == ret)
	{
		while(RIIC_FINISH != iic_info_m.dev_sts);
	}
	else
	{
		/* error */
		while(1);
	}

//	/* Enable STB pins */
//	access_addr1[0] = 0x02;
//	ret = R_RIIC_MasterSend(&iic_info_m);
//	if (RIIC_SUCCESS == ret)
//	{
//		while(RIIC_FINISH != iic_info_m.dev_sts);
//	}
//	else
//	{
//		/* error */
//		while(1);
//	}
}

void Cetic_CAN_LIN_TRA_turn_On(uint32_t * psendData)
{
//	Cetic_GET_EXP_WUP_STS();
//	Cetic_GET_MCU_WUP_STS();
	Cetic_TRA_turn_On(psendData);
}
// End of file

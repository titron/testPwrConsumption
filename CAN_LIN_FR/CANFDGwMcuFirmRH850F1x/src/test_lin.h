
#ifndef _TEST_LIN_H_
#define _TEST_LIN_H_

#define POWER_TEST_RLIN

#define LIN_BAUDRATE 20000

#define MAX_LIN_BUS_NUM			5

#define ACTIVATE_LIN_BUS_NUM	5	/* 1 : 2  channels lin power test,
                                       5 : 10 channels lin power test */
#define LIN2_MASTER_TABLE_NO	0	/* table no is used by lin communication,
                                       table is defined in file "rlin2_s.h" and "rlin3.h" */
#define R_DATA	0x00                /* 0x00 (maximum power consumption), 0x5A, 0xFF */

extern void powertest_lin_rlin2_m_rlin3_s();

#endif /* _TEST_LIN_H_ */

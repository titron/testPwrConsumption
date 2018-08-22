/*
 * test_port.h
 *
 *  Created on: 2018Äê7ÔÂ26ÈÕ
 *      Author: a5059726
 */

#ifndef CPU1_CUP1_TEST_PORT_H_
#define CPU1_CUP1_TEST_PORT_H_

#include <standardports.h>


#define EE_FR_PORT_TEST        PORT_0
#define EE_FR_PORT_BIT_TEST    BIT_4

#define PORT_SET_LEVEL(LEVEL)	PORT_WriteBit( EE_FR_PORT_TEST, EE_FR_PORT_BIT_TEST, LEVEL );

extern void port_init(void);
#endif /* CPU1_CUP1_TEST_PORT_H_ */

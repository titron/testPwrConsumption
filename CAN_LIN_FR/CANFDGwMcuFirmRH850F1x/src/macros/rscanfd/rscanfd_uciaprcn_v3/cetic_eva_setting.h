/*
 * cetic_eva_setting.h
 *
 *  Created on: 2018��9��17��
 *      Author: a5059726
 */

#ifndef CANFDGWMCUFIRMRH850F1X_SRC_MACROS_RSCANFD_CETIC_EVA_SETTING_H_
#define CANFDGWMCUFIRMRH850F1X_SRC_MACROS_RSCANFD_CETIC_EVA_SETTING_H_

/* Evaluation Mode */
#define EVA_CETIBOX_PWR_CONSUMPTION_SINGLE_CH	0
#define EVA_CETIBOX_PWR_CONSUMPTION_ALL_CHS		1
//#define EVA_CETIBOX_PWR_CONSUMPTION_MODE		EVA_CETIBOX_PWR_CONSUMPTION_SINGLE_CH
#define EVA_CETIBOX_PWR_CONSUMPTION_MODE		EVA_CETIBOX_PWR_CONSUMPTION_ALL_CHS

/* Settings */
#define DEFAULT_PAYLOAD_LENGTH_0BYTE	(0x00)
#define DEFAULT_PAYLOAD_LENGTH_1BYTE	(0x01)
#define DEFAULT_PAYLOAD_LENGTH_2BYTES	(0x02)
#define DEFAULT_PAYLOAD_LENGTH_3BYTES	(0x03)
#define DEFAULT_PAYLOAD_LENGTH_4BYTES	(0x04)
#define DEFAULT_PAYLOAD_LENGTH_5BYTES	(0x05)
#define DEFAULT_PAYLOAD_LENGTH_6BYTES	(0x06)
#define DEFAULT_PAYLOAD_LENGTH_7BYTES	(0x07)
#define DEFAULT_PAYLOAD_LENGTH_8BYTES	(0x08)
#define DEFAULT_PAYLOAD_LENGTH_12BYTES	(0x09)
#define DEFAULT_PAYLOAD_LENGTH_16BYTES	(0x0A)
#define DEFAULT_PAYLOAD_LENGTH_20BYTES	(0x0B)
#define DEFAULT_PAYLOAD_LENGTH_24BYTES	(0x0C)
#define DEFAULT_PAYLOAD_LENGTH_32BYTES	(0x0D)
#define DEFAULT_PAYLOAD_LENGTH_48BYTES	(0x0E)
#define DEFAULT_PAYLOAD_LENGTH_64BYTES	(0x0F)
#define DEFAULT_PAYLOAD_LENGTH			DEFAULT_PAYLOAD_LENGTH_8BYTES

#define DEFAULT_PAYLOAD_ID	 			(0x00)
#define DEFAULT_PAYLOAD_DATA 			(0x00)


#endif /* CANFDGWMCUFIRMRH850F1X_SRC_MACROS_RSCANFD_CETIC_EVA_SETTING_H_ */

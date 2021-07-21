/*
 * rtc.h
 *
 *  Created on: Jun 28, 2021
 *      Author: DQSmartIoT
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "comm.h"

uint8_t RTC_u8Init();
void RTC_vGetDateTime(RTC_DateTimeTypedef* hRTC_DateTime);
void RTC_vSetDateTime(RTC_DateTimeTypedef* hRTC_DateTime);

#ifdef __cplusplus
}
#endif

#endif /* INC_RTC_H_ */

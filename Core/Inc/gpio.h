/*
 * gpio.h
 *
 *  Created on: Jun 28, 2021
 *      Author: DQSmartIoT
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "comm.h"
#include "physical.h"

uint8_t GPIO_u8ButtonInit();
uint8_t GPIO_u8ButtonRead();
uint8_t GPIO_u8LedInit();
uint8_t GPIO_u8Led1On();
uint8_t GPIO_u8Led1Off();
uint8_t GPIO_u8Led2On();
uint8_t GPIO_u8Led2Off();
uint8_t GPIO_u8ScanInit();
uint8_t GPIO_u8ScanEnb();


#ifdef __cplusplus
}
#endif

#endif /* INC_GPIO_H_ */

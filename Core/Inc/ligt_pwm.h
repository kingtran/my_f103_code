/*
 * ligt_pwm.h
 *
 *  Created on: Jun 28, 2021
 *      Author: DQSmartIoT
 */

#ifndef INC_LIGT_PWM_H_
#define INC_LIGT_PWM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "comm.h"
#include "physical.h"

uint8_t LIPWM_u8Init();
uint8_t LIPWM_u8Start();
uint8_t LIPWM_u8Stop();
uint8_t LIPWM_u8GetValue();
void LIPWM_vSetValue(uint8_t u8Value, uint16_t u16TimeSmooth);

#ifdef __cplusplus
}
#endif

#endif /* INC_LIGT_PWM_H_ */

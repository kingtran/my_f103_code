/*
 * sim.h
 *
 *  Created on: Jun 28, 2021
 *      Author: DQSmartIoT
 */

#ifndef INC_SIM_H_
#define INC_SIM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "comm.h"
#include "physical.h"


uint8_t SIM_u8SimInit();
void SIM_vOnSim();
void SIM_vOffSim();


#ifdef __cplusplus
}
#endif

#endif /* INC_SIM_H_ */

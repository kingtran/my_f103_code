/*
 * nvm.h
 *
 *  Created on: Jul 19, 2021
 *      Author: DQSmartIoT
 */

#ifndef INC_NVM_H_
#define INC_NVM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "comm.h"
#include "physical.h"

void NVM_vStorageSchedulerData(Scheduler_DataTypeDef* pstSchedulerData);
void NVM_vReadSchedulerData(Scheduler_DataTypeDef* pstSchedulerData);

#ifdef __cplusplus
}
#endif

#endif /* INC_NVM_H_ */

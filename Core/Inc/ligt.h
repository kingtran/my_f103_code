/*
 * ligt.h
 *
 *  Created on: Jun 28, 2021
 *      Author: DQSmartIoT
 */

#ifndef INC_LIGT_H_
#define INC_LIGT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ligt_ambs.h"
#include "ligt_engm.h"
#include "ligt_pwm.h"
#include "ligt_dali.h"
#include "ligt_sw.h"
#include "comm.h"

uint8_t LI_u8EnableDataCollect();
uint8_t LI_u8DisableDataCollect();
uint8_t LI_u8GetDataCollected(LI_DataCollectedTypeDef* pstLiDataCollected);

#ifdef __cplusplus
}
#endif

#endif /* INC_LIGT_H_ */

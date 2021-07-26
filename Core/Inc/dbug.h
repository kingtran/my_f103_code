/*
 * dbug.h
 *
 *  Created on: Jun 28, 2021
 *      Author: DQSmartIoT
 */

#ifndef INC_DBUG_H_
#define INC_DBUG_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "comm.h"
#include "physical.h"

uint8_t DBUG_u8Init();
uint8_t DBUG_u8RxEnb();
uint8_t DBUG_u8GetRxByte();
uint8_t DBUG_u8SendByte(uint8_t* pu8Data, uint16_t u16Len);
uint8_t DBUG_u8GetCmdState();
uint8_t* DBUG_pu8GetDataCmd();

#ifdef __cplusplus
}
#endif

#endif /* INC_DBUG_H_ */

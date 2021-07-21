/*
 * physical.h
 *
 *  Created on: Jul 2, 2021
 *      Author: DQSmartIoT
 */

#ifndef INC_PHYSICAL_H_
#define INC_PHYSICAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "comm.h"

uint8_t PHY_u8Uart3Init();
uint8_t PHY_u8Uart1Init();
uint8_t PHY_u8Timer2Init();
uint8_t PHY_u8Timer2EnbInterrupt();
uint8_t PHY_u8Timer3Init();
uint8_t PHY_u8Timer3PwmStart();
uint8_t PHY_u8Timer3PwmStop();
uint8_t PHY_u8Timer3GetPwmValue();
void PHY_vTimer3SetPwmValue(uint8_t u8Value, uint16_t u16TimeSmooth);
uint8_t PHY_u8Spi1Init();
uint16_t PHY_u16CommEnergyIC(uint8_t u8RW, uint8_t u8Address, uint16_t u16Value);
uint8_t PHY_u8GpioInit();
uint8_t PHY_u8ButtonGpioInit();
uint8_t PHY_u8ButtonGpioRead();
uint8_t PHY_u8LedGpioInit();
uint8_t PHY_u8Led1On();
uint8_t PHY_u8Led1Off();
uint8_t PHY_u8Led2On();
uint8_t PHY_u8Led2Off();
uint8_t PHY_u8RtcInit();
void PHY_vGetDateTime(RTC_DateTimeTypedef* hRTC_DateTime);
void PHY_vSetDateTime(RTC_DateTimeTypedef* hRTC_DateTime);
uint8_t PHY_u8Adc1Init();
uint16_t PHY_u16Adc1Read();
uint8_t PHY_u8EnbInterrupt(uint8_t u8State);
uint8_t PHY_u8Uart3EnbInterrupt();
uint8_t* PHY_u8Uart3ReturnRxByte();
uint8_t PHY_u8Uart3SendByte(uint8_t* pu8Data, uint16_t u16Len);
uint8_t PHY_u8EnableDataCollect();
uint8_t PHY_u8DisableDataCollect();
uint8_t PHY_u8GetDataCollectStatus();

uint8_t PHY_u8SimInit();
void PHY_vOnSim();
void PHY_vOffSim();

#ifdef __cplusplus
}
#endif


#endif /* INC_PHYSICAL_H_ */

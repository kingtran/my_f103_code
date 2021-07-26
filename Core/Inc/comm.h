/*
 * comm.h
 *
 *  Created on: Jun 28, 2021
 *      Author: DQSmartIoT
 */

#ifndef INC_COMM_H_
#define INC_COMM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MinorVersion		0x0001
#define MajorVersion	0x0001

#define ENB 0
#define DIS 1
#define RX_MAX_LEN 20
#define TX_MAX_LEN 20

#define MA_STA_CMD 0
#define MA_STA_SET 1
#define MA_STA_RUN 2

#define MA_STA_NOP 0
#define MA_STA_RUN_MAN 10
#define MA_STA_RUN_MAN_LED 11
#define MA_STA_RUN_MAN_PWM 12

#define MA_STA_RUN_AUT1 100
#define MA_STA_RUN_AUT2 101

#define MA_STA_SET_SCH 200
#define MA_STA_SET_SCH_UPD 201
#define MA_STA_SET_SCH_END 202

#define PWM_NOP 0
#define PWM_INC 1
#define PWM_DEC 2

#define MAX_OF_SLOT 10
#define DAY_OF_WEEK 7

#define DATA_COLLECTION_CYCLE	1000
#define MAX_OF_FLASH 0x0800FFFF
#define START_OF_FLASH 0x0800F000
#define SIZE_OF_PAGE 0x400

// Cmd Code
#define CmdGetMcuVersion		0x00
#define CmdGetControlStatus		0x01
#define CmdGetLightSensorValue	0x02
#define CmdGetPMVoltageValue	0x03
#define CmdGetPMCurrentValue	0x04
#define CmdGetPMPowerValue		0x05
#define CmdGetPMFrequencyValue	0x06
#define CmdGetLightLevelValue	0x07
#define CmdGetLightStatus		0x08
#define CmdGetTimeStatus		0x09
#define CmdGetDateStatus		0x0a
#define CmdGetWarningStatus		0x0b
#define CmdSetControlStatus		0x0c
#define CmdSetLightLevelValue	0x0d
#define CmdSetLightStatus		0x0e
#define CmdSetTimeStatus		0x0f
#define CmdSetDateStatus		0x10
#define CmdSetSchedulerStart	0x11
#define CmdSetSchedulerData		0x12
#define CmdSetSchedulerEnd		0x13

#define Start1					0x03 // Buff Len = 3
#define Start2					0x04 // Buff Len = 4
#define Start3					0x06 // Buff Len = 6
#define Start4					0x07 // Buff Len = 7
#define Start5					0x0b // Buff Len = 11

// State Machine
#define StaNop					0x00
#define StaGetMcuVersion		0xa0
#define StaGetControlStatus		0xa1
#define StaGetLightSensorValue	0xa2
#define StaGetPMVoltageValue	0xa3
#define StaGetPMCurrentValue	0xa4
#define StaGetPMPowerValue		0xa5
#define StaGetPMFrequencyValue	0xa6
#define StaGetLightLevelValue	0xa7
#define StaGetLightStatus		0xa8
#define StaGetTimeStatus		0xa9
#define StaGetDateStatus		0xaa
#define StaGetWarningStatus		0xab
#define StaSetControlStatus		0xac
#define StaSetLightLevelValue	0xad
#define StaSetLightStatus		0xae
#define StaSetTimeStatus		0xaf
#define StaSetDateStatus		0xb0
#define StaSetSchedulerStart	0xb1
#define StaSetSchedulerData		0xb2
#define StaSetSchedulerEnd		0xb3

/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
uint8_t u8Rx1Data[RX_MAX_LEN];
uint8_t u8Tx1Data[TX_MAX_LEN];
uint8_t u8Rx3Data[RX_MAX_LEN];
uint8_t u8Tx3Data[TX_MAX_LEN];

//typedef struct __Machine_StatusTypeDef
//{
//	uint8_t sta_mode;
//	uint8_t sta_setup;
//	uint8_t sta_run;
//}Machine_StatusTypeDef;

typedef struct __Scheduler_ValueTypeDef
{
	uint8_t u8Hour;
	uint8_t u8Minute;
	uint8_t u8Value;
}Scheduler_ValueTypeDef;

typedef struct __Scheduler_DataSlotTypeDef
{
	uint8_t u8DayOfWeek;
	uint8_t u8Day;
	uint8_t u8Month;
	uint8_t u8Year;
	Scheduler_ValueTypeDef stSchedulerValue[MAX_OF_SLOT];
}Scheduler_DataSlotTypeDef;

typedef struct __Scheduler_DataTypeDef
{
	uint8_t u8Temp1;
	uint8_t u8Temp2;
	uint8_t u8Temp3;
	Scheduler_DataSlotTypeDef stSchedulerDataSlot[DAY_OF_WEEK];
}Scheduler_DataTypeDef;

typedef struct __RTC_DateTimeTypedef
{
	uint8_t Hours;
	uint8_t Minutes;
	uint8_t Seconds;
	uint8_t WeekDay;
	uint8_t Month;
	uint8_t Date;
	uint8_t Year;
}RTC_DateTimeTypedef;

typedef struct __ENGM_MeasuredValueTypeDef
{
	double dLineVoltage;
	double dLineCurrent;
	double dActivePower;
	double dFrequency;
}ENGM_MeasuredValueTypeDef;

typedef struct __LI_DataCollectedTypeDef
{
	uint16_t u16AmbsValue;
	ENGM_MeasuredValueTypeDef stEngmMeasuredValue;
}LI_DataCollectedTypeDef;
/* USER CODE END PV */


#ifdef __cplusplus
}
#endif

#endif /* INC_COMM_H_ */

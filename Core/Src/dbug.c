/*
 * dbug.c
 *
 *  Created on: Jun 28, 2021
 *      Author: DQSmartIoT
 */
#include "main.h"
#include "dbug.h"
#include "physical.h"

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
extern Scheduler_DataTypeDef stSchedulerData;
Scheduler_DataSlotTypeDef stSchedulerDataSlot;

uint8_t u8RxData[MAX_OF_LEN];
uint8_t u8TxData[MAX_OF_LEN];
uint8_t* u8RxByte;
uint8_t u8DataCmd[5];
/* USER CODE END PV */
/**
 * @fn uint8_t DBUG_u8Init()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t DBUG_u8Init()
{
	PHY_u8Uart3Init();
	return HAL_OK;
}
/**
 * @fn uint8_t u8DbugRxEnb()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t DBUG_u8RxEnb()
{
	PHY_u8Uart3EnbInterrupt();
	return HAL_OK;
}
/**
 * @fn uint8_t u8RxGetByte()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t DBUG_u8GetRxByte()
{
	u8RxByte = PHY_u8Uart3ReturnRxByte();
	return *u8RxByte;
}
/**
 * @fn uint8_t u8DbugSendByte(uint8_t)
 * @brief
 *
 * @pre
 * @post
 * @param u8Byte
 * @return
 */
uint8_t DBUG_u8SendByte(uint8_t* pu8Data, uint16_t u16Len)
{
	PHY_u8Uart3SendByte(pu8Data, u16Len);
	return HAL_OK;
}
/**
 * @fn uint8_t DBUG_u8GetCmdState()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t DBUG_u8GetCmdState()
{
	//-> 64 AUTO 1
	//03 <crc> 64
	//036464
	//-> 65 AUTO 2
	//03 <crc> 65
	//036565
	//-> 01 LED
	//04 <crc> 01 <1 byte pwm value>
	//04110110
	//04120111
	//04210120
	//04220121
	//-> 02 PWM
	//06 <crc> 02 <1 byte pwm value> <2 bytes smooth value>
	//060B023207D0
	//063D026407D0
	//-> 03 Scheduler
	//07 <crc> 03 <1 byte day of week> <3 bytes day/month/year>
	//07070301010101
	//-> 04 Scheduler Data
	//07 <crc> 04 <1 byte no of Slot> <3 bytes Hour/Minute/Value>
	//07070301010101
	uint8_t u8Item = 0;
	u8RxByte = PHY_u8Uart3ReturnRxByte();

	if(u8RxByte[0] == 0 && u8RxByte[1] == 0 && u8RxByte[1] == 0)
		return 0;

	for(u8Item = 0; u8Item < MAX_OF_LEN; u8Item++)
	{

		if((u8RxByte[u8Item] == 0x03)
			&& (u8RxByte[u8Item+1] ==  u8RxByte[u8Item+2])
			&& (u8RxByte[u8Item+2] == 0x64))
		{
			PHY_u8Uart3EnbInterrupt();
			return MA_STA_RUN_AUT1;
		}
		else if((u8RxByte[u8Item] == 0x03)
			&& (u8RxByte[u8Item+1] ==  u8RxByte[u8Item+2])
			&& (u8RxByte[u8Item+2] == 0x65))
		{
			PHY_u8Uart3EnbInterrupt();
			return MA_STA_RUN_AUT2;
		}
		else if((u8RxByte[u8Item] == 0x04)
			&& (u8RxByte[u8Item+1] ==  (uint8_t)(u8RxByte[u8Item+2] + u8RxByte[u8Item+3]))
			&& (u8RxByte[u8Item+2] == 0x01)
			&& (u8RxByte[u8Item+3] > 0))
		{
			u8DataCmd[0] = u8RxByte[u8Item+3] >> 4;
			u8DataCmd[1] = u8RxByte[u8Item+3] & 0x0F;

			PHY_u8Uart3EnbInterrupt();
			return MA_STA_RUN_MAN_LED;
		}
		else if((u8RxByte[u8Item] == 0x06)
			&& (u8RxByte[u8Item+1] == (uint8_t)(u8RxByte[u8Item+2] + u8RxByte[u8Item+3] + u8RxByte[u8Item+4] + u8RxByte[u8Item+5]))
			&& (u8RxByte[u8Item+2] == 0x02)
			&& (u8RxByte[u8Item+3] > 0)
			&& (u8RxByte[u8Item+4] > 0)
			&& (u8RxByte[u8Item+5] > 0))
		{
			u8DataCmd[0] = u8RxByte[u8Item+3];
			u8DataCmd[1] = u8RxByte[u8Item+4];
			u8DataCmd[2] = u8RxByte[u8Item+5];

			PHY_u8Uart3EnbInterrupt();
			return MA_STA_RUN_MAN_PWM;
		}
		else if((u8RxByte[u8Item] == 0x07)
			&& (u8RxByte[u8Item+1] == (uint8_t)(u8RxByte[u8Item+2] + u8RxByte[u8Item+3] + u8RxByte[u8Item+4] + u8RxByte[u8Item+5] + u8RxByte[u8Item+6]))
			&& (u8RxByte[u8Item+2] == 0x03)
			&& (u8RxByte[u8Item+3] >= 0)
			&& (u8RxByte[u8Item+4] > 0)
			&& (u8RxByte[u8Item+5] > 0)
			&& (u8RxByte[u8Item+6] >= 0))
		{

			u8DataCmd[0] = u8RxByte[u8Item+3];
			u8DataCmd[1] = u8RxByte[u8Item+4];
			u8DataCmd[2] = u8RxByte[u8Item+5];
			u8DataCmd[3] = u8RxByte[u8Item+6];

			stSchedulerDataSlot.u8DayOfWeek = u8DataCmd[0];
			stSchedulerDataSlot.u8Day 		= u8DataCmd[1];
			stSchedulerDataSlot.u8Month		= u8DataCmd[2];
			stSchedulerDataSlot.u8Year 		= u8DataCmd[3];

			PHY_u8Uart3EnbInterrupt();
			return MA_STA_SET_SCH;
		}
		else if((u8RxByte[u8Item] == 0x07)
			&& (u8RxByte[u8Item+1] == (uint8_t)(u8RxByte[u8Item+2] + u8RxByte[u8Item+3] + u8RxByte[u8Item+4] + u8RxByte[u8Item+5] + u8RxByte[u8Item+6]))
			&& (u8RxByte[u8Item+2] == 0x04)
			&& (u8RxByte[u8Item+3] > 0)
			&& (u8RxByte[u8Item+4] >= 0)
			&& (u8RxByte[u8Item+5] >= 0)
			&& (u8RxByte[u8Item+6] >= 0))
		{

			u8DataCmd[0] = u8RxByte[u8Item+3];
			u8DataCmd[1] = u8RxByte[u8Item+4];
			u8DataCmd[2] = u8RxByte[u8Item+5];
			u8DataCmd[3] = u8RxByte[u8Item+6];

			Scheduler_ValueTypeDef stSchedulerValue = {0};
			stSchedulerValue.u8Hour 	= u8DataCmd[1];
			stSchedulerValue.u8Minute	= u8DataCmd[2];
			stSchedulerValue.u8Value 	= u8DataCmd[3];

			stSchedulerDataSlot.stSchedulerValue[u8DataCmd[0] - 1] = stSchedulerValue;

			stSchedulerData.stSchedulerDataSlot[stSchedulerDataSlot.u8DayOfWeek] = stSchedulerDataSlot;

			PHY_u8Uart3EnbInterrupt();

			if(u8DataCmd[0] == MAX_OF_SLOT)
				return MA_STA_SET_SCH_END;

			return MA_STA_SET_SCH_UPD;
		}
	}
	return 0;
}
/**
 * @fn uint8_t DBUG_u8CheckCmdState()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t DBUG_u8CheckCmdState()
{
	return 0;
}
/**
 * @fn uint8_t DBUG_pu8GetDataCmd*()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t* DBUG_pu8GetDataCmd()
{
	return &u8DataCmd[0];
}


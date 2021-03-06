/*
 * app.c
 *
 *  Created on: Jul 23, 2021
 *      Author: PC
 */

#include "app.h"

uint8_t u8McuVersion;
uint8_t u8ControlStatus;
uint16_t u16LightSensorValue;
uint16_t u16PMVoltageValue;
uint16_t u16PMCurrentValue;
uint16_t u16PMPowerValue;
uint16_t u16PMFrequencyValue;
uint8_t u8LightLevelValue;
uint8_t u8LightStatus;
RTC_DateTimeTypedef stDateTimeStatus;
uint8_t u8WarningStatus;

static void vGenBuff(uint8_t* pBuff, uint8_t u8Len);
static void vGenBuff(uint8_t* pBuff, uint8_t u8Len)
{
	uint8_t u8Count;
	pBuff[0] = u8Len;
	for(u8Count = 2; u8Count < u8Len; u8Count++)
	{
		pBuff[1] += pBuff[u8Count];
	}
}

void APP_vGetMcuVersion()
{
	u8Tx3Data[0] = 0;
	u8Tx3Data[1] = 0;
	u8Tx3Data[2] = CmdGetMcuVersion;
	u8Tx3Data[3] = (uint8_t)MinorVersion;
	u8Tx3Data[4] = (uint8_t)(MinorVersion>>8);
	u8Tx3Data[5] = (uint8_t)MajorVersion;;
	u8Tx3Data[6] = (uint8_t)(MajorVersion>>8);
	vGenBuff((uint8_t*)u8Tx3Data, 7);
	DBUG_u8SendByte((uint8_t*)u8Tx3Data, 7);
}
void APP_vGetControlStatus()
{
	u8Tx3Data[0] = 0;
	u8Tx3Data[1] = 0;
	u8Tx3Data[2] = CmdGetControlStatus;
	u8Tx3Data[3] = u8ControlStatus;
	vGenBuff((uint8_t*)u8Tx3Data, 4);
	DBUG_u8SendByte((uint8_t*)u8Tx3Data, 4);
}
void APP_vGetLightSensorValue()
{
	u8Tx3Data[0] = 0;
	u8Tx3Data[1] = 0;
	u8Tx3Data[2] = CmdGetLightSensorValue;
	u8Tx3Data[3] = (uint8_t)u16LightSensorValue;
	u8Tx3Data[4] = (uint8_t)(u16LightSensorValue>>8);
	vGenBuff((uint8_t*)u8Tx3Data, 5);
	DBUG_u8SendByte((uint8_t*)u8Tx3Data, 5);
}
void APP_vGetPMVoltageValue()
{
	u8Tx3Data[0] = 0;
	u8Tx3Data[1] = 0;
	u8Tx3Data[2] = CmdGetPMVoltageValue;
	u8Tx3Data[3] = (uint8_t)u16PMVoltageValue;
	u8Tx3Data[4] = (uint8_t)(u16PMVoltageValue>>8);
	vGenBuff((uint8_t*)u8Tx3Data, 5);
	DBUG_u8SendByte((uint8_t*)u8Tx3Data, 5);
}
void APP_vGetPMCurrentValue()
{
	u8Tx3Data[0] = 0;
	u8Tx3Data[1] = 0;
	u8Tx3Data[2] = CmdGetPMCurrentValue;
	u8Tx3Data[3] = (uint8_t)u16PMCurrentValue;
	u8Tx3Data[4] = (uint8_t)(u16PMCurrentValue>>8);
	vGenBuff((uint8_t*)u8Tx3Data, 5);
	DBUG_u8SendByte((uint8_t*)u8Tx3Data, 5);
}
void APP_vGetPMPowerValue()
{
	u8Tx3Data[0] = 0;
	u8Tx3Data[1] = 0;
	u8Tx3Data[2] = CmdGetPMPowerValue;
	u8Tx3Data[3] = (uint8_t)u16PMPowerValue;
	u8Tx3Data[4] = (uint8_t)(u16PMPowerValue>>8);
	vGenBuff((uint8_t*)u8Tx3Data, 5);
	DBUG_u8SendByte((uint8_t*)u8Tx3Data, 5);
}
void APP_vGetPMFrequencyValue()
{
	u8Tx3Data[0] = 0;
	u8Tx3Data[1] = 0;
	u8Tx3Data[2] = CmdGetPMFrequencyValue;
	u8Tx3Data[3] = (uint8_t)u16PMFrequencyValue;
	u8Tx3Data[4] = (uint8_t)(u16PMFrequencyValue>>8);
	vGenBuff((uint8_t*)u8Tx3Data, 5);
	DBUG_u8SendByte((uint8_t*)u8Tx3Data, 5);
}
void APP_vGetLightLevelValue()
{
	u8Tx3Data[0] = 0;
	u8Tx3Data[1] = 0;
	u8Tx3Data[2] = CmdGetLightLevelValue;
	u8Tx3Data[3] = u8LightLevelValue;
	vGenBuff((uint8_t*)u8Tx3Data, 4);
	DBUG_u8SendByte((uint8_t*)u8Tx3Data, 4);
}
void APP_vGetLightStatus()
{
	u8Tx3Data[0] = 0;
	u8Tx3Data[1] = 0;
	u8Tx3Data[2] = CmdGetLightStatus;
	u8Tx3Data[3] = u8LightStatus;
	vGenBuff((uint8_t*)u8Tx3Data, 4);
	DBUG_u8SendByte((uint8_t*)u8Tx3Data, 4);
}
void APP_vGetTimeStatus()
{
	RTC_vGetDateTime(&stDateTimeStatus);
	u8Tx3Data[0] = 0;
	u8Tx3Data[1] = 0;
	u8Tx3Data[2] = CmdGetTimeStatus;
	u8Tx3Data[3] = stDateTimeStatus.Hours;
	u8Tx3Data[4] = stDateTimeStatus.Minutes;
	u8Tx3Data[5] = stDateTimeStatus.Seconds;
	vGenBuff((uint8_t*)u8Tx3Data, 6);
	DBUG_u8SendByte((uint8_t*)u8Tx3Data, 6);
}
void APP_vGetDateStatus()
{
	RTC_vGetDateTime(&stDateTimeStatus);
	u8Tx3Data[0] = 0;
	u8Tx3Data[1] = 0;
	u8Tx3Data[2] = CmdGetDateStatus;
	u8Tx3Data[3] = stDateTimeStatus.WeekDay;
	u8Tx3Data[4] = stDateTimeStatus.Date;
	u8Tx3Data[5] = stDateTimeStatus.Month;
	u8Tx3Data[6] = stDateTimeStatus.Year;
	vGenBuff((uint8_t*)u8Tx3Data, 7);
	DBUG_u8SendByte((uint8_t*)u8Tx3Data, 7);
}
void APP_vGetWarningStatus()
{
	u8Tx3Data[0] = 0;
	u8Tx3Data[1] = 0;
	u8Tx3Data[2] = CmdGetWarningStatus;
	u8Tx3Data[3] = u8WarningStatus;
	vGenBuff((uint8_t*)u8Tx3Data, 4);
	DBUG_u8SendByte((uint8_t*)u8Tx3Data, 4);
}
void APP_vSetControlStatus()
{

}
void APP_vSetLightLevelValue()
{

}
void APP_vSetLightStatus()
{

}
void APP_vSetTimeStatus()
{

}
void APP_vSetDateStatus()
{

}
void APP_vSetSchedulerStart()
{

}
void APP_vSetSchedulerData()
{

}
void APP_vSetSchedulerEnd()
{

}


/*
 * rtc.c
 *
 *  Created on: Jun 28, 2021
 *      Author: DQSmartIoT
 */
#include "rtc.h"

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */
/**
 * @fn uint8_t RTC_u8Init()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t RTC_u8Init()
{
	return PHY_u8RtcInit();
}
/**
 * @fn void RTC_vGetDateTime(RTC_DateTimeTypedef*)
 * @brief
 *
 * @pre
 * @post
 * @param hRTC_DateTime
 */
void RTC_vGetDateTime(RTC_DateTimeTypedef* hRTC_DateTime)
{
	PHY_vGetDateTime(hRTC_DateTime);
}
/**
 * @fn void RTC_vSetDateTime(RTC_DateTimeTypedef*)
 * @brief
 *
 * @pre
 * @post
 * @param hRTC_DateTime
 */
void RTC_vSetDateTime(RTC_DateTimeTypedef* hRTC_DateTime)
{
	PHY_vSetDateTime(hRTC_DateTime);
}

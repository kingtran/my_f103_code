/*
 * gpio.c
 *
 *  Created on: Jun 28, 2021
 *      Author: DQSmartIoT
 */
#include "gpio.h"

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */
/**
 * @fn uint8_t GPIO_ButtonInit()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t GPIO_u8ButtonInit()
{
	return PHY_u8ButtonGpioInit();
}
/**
 * @fn uint8_t GPIO_u8ButtonRead()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t GPIO_u8ButtonRead()
{
	return PHY_u8ButtonGpioRead();
}
/**
 * @fn uint8_t GPIO_LedInit()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t GPIO_u8LedInit()
{
	return PHY_u8LedGpioInit();
}
/**
 * @fn uint8_t GPIO_u8Led1On()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t GPIO_u8Led1On()
{
	return PHY_u8Led1On();
}
/**
 * @fn uint8_t GPIO_u8Led1Off()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t GPIO_u8Led1Off()
{
	return PHY_u8Led1Off();
}
/**
 * @fn uint8_t GPIO_u8Led2On()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t GPIO_u8Led2On()
{
	return PHY_u8Led2On();
}
/**
 * @fn uint8_t GPIO_u8Led2Off()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t GPIO_u8Led2Off()
{
	return PHY_u8Led2Off();
}
/**
 * @fn uint8_t GPIO_u8EnbInterrupt()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t GPIO_u8ScanEnb()
{
	return PHY_u8Timer2EnbInterrupt();
}
/**
 * @fn uint8_t GPIO_u8InitInterrupt()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t GPIO_u8ScanInit()
{
	return PHY_u8Timer2Init();
}


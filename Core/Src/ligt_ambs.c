/*
 * ligt_ambs.c
 *
 *  Created on: Jun 28, 2021
 *      Author: DQSmartIoT
 */
#include "main.h"
#include "ligt_ambs.h"
#include "physical.h"
/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */
/**
 * @fn uint8_t LIAMBS_u8Init()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t LIAMBS_u8Init()
{
	return PHY_u8Adc1Init();
}
/**
 * @fn uint16_t LIAMBS_u16Read()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint16_t LIAMBS_u16Read()
{
	return PHY_u16Adc1Read();
}

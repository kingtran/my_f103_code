/*
 * ligt_pwm.c
 *
 *  Created on: Jun 28, 2021
 *      Author: DQSmartIoT
 */
#include "ligt_pwm.h"
/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */
/**
 * @fn uint8_t LIPWM_u8Init()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t LIPWM_u8Init()
{
	return PHY_u8Timer3Init();
}
/**
 * @fn uint8_t LIPWM_u8Start()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t LIPWM_u8Start()
{
	return PHY_u8Timer3PwmStart();
}
/**
 * @fn uint8_t LIPWM_u8Stop()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t LIPWM_u8Stop()
{
	return PHY_u8Timer3PwmStop();
}
/**
 * @fn uint8_t LIPWM_u8GetValue()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t LIPWM_u8GetValue()
{
	return PHY_u8Timer3GetPwmValue();
}
/**
 * @fn void LIPWM_vSetValue(,)
 * @brief
 *
 * @pre
 * @post
 * @param u8Value
 * @param u16TimeSmooth
 */
void LIPWM_vSetValue(uint8_t u8Value, uint16_t u16TimeSmooth)
{
	PHY_vTimer3SetPwmValue(u8Value, u16TimeSmooth);
}


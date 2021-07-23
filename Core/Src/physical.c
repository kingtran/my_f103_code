/*
 * physical.c
 *
 *  Created on: Jul 2, 2021
 *      Author: DQSmartIoT
 */
#include "main.h"
#include "physical.h"

extern ADC_HandleTypeDef hadc1;

extern RTC_HandleTypeDef hrtc;

extern SPI_HandleTypeDef hspi1;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
void vButtonRead();
void vSmoothPwmActive();
void vDataCollectStatus();
/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
uint8_t u8Uart3IrptState;
uint8_t u8Uart3RxByte[MAX_OF_LEN];
uint8_t u8Uart3Path;
uint8_t u8ButtonState, u8Button1Detect, u8Button2Detect;
uint16_t u16Timer2Step;
uint8_t u8CurrentPwmValue, u8DestPwmValue, u8SmoothPwmActive;
uint16_t u16SmoothPwmStep, u16SmoothPwmStepCount;
uint8_t u8EnbDataCollect, u8DataCollectStatus;
uint32_t u32DataCollectionCycle;
/* USER CODE END PV */

/**
 * @fn uint8_t PHY_u8Uart3Init()
 * @brief Khoi tao khoi UART3 - dung cho chuc nang giao tiep voi PC
 *	BaudRate = 9600
 *	Parity = NONE
 *	StopBits = 1
 *	Mode = TX_RX
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8Uart3Init()
{
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 9600;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart3) != HAL_OK)
	{
		Error_Handler();
	}
	return HAL_OK;
}
/**
 * @fn uint8_t PHY_u8Uart1Init()
 * @brief Khoi tao khoi UART1 - dung cho chuc nang giao tiep voi SIM
 *	BaudRate = 9600
 *	Parity = NONE
 *	StopBits = 1
 *	Mode = TX_RX
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8Uart1Init()
{
	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 9600;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */
	return HAL_OK;
}
/**
 * @fn uint8_t PHY_u8Timer2Init()
 * @brief Khoi tao khoi Timer2 - dung cho chuc nang giao tiep voi LED, ...
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8Timer2Init()
{
	/* USER CODE BEGIN TIM2_Init 0 */

	/* USER CODE END TIM2_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	/* USER CODE BEGIN TIM2_Init 1 */

	/* USER CODE END TIM2_Init 1 */
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 1000-1;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 72-1;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM2_Init 2 */

	/* USER CODE END TIM2_Init 2 */
	return HAL_OK;
}
/**
 * @fn uint8_t PHY_u8Timer2EnbInterrupt()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8Timer2EnbInterrupt()
{
	HAL_TIM_Base_Start_IT(&htim2);
	return HAL_OK;
}
/**
 * @fn uint8_t PHY_u8Timer3Init()
 * @brief Khoi tao khoi Timer3 - dung cho chuc nang giao tiep voi PWM
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8Timer3Init()
{
	/* USER CODE BEGIN TIM3_Init 0 */

	/* USER CODE END TIM3_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};

	/* USER CODE BEGIN TIM3_Init 1 */

	/* USER CODE END TIM3_Init 1 */
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 360-1;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 100-1;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM3_Init 2 */

	/* USER CODE END TIM3_Init 2 */
	HAL_TIM_MspPostInit(&htim3);
	return HAL_OK;
}
/**
 * @fn uint8_t PHY_u8Timer3PwmStart()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8Timer3PwmStart()
{
	htim3.Instance->CCR1 = 10;
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	return HAL_OK;
}
/**
 * @fn uint8_t PHY_u8Timer3PwmStop()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8Timer3PwmStop()
{
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
	return HAL_OK;
}
/**
 * @fn uint8_t PHY_u8Timer3GetPwmValue()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8Timer3GetPwmValue()
{
	return htim3.Instance->CCR1;
}
/**
 * @fn void PHY_vTimer3SetPwmValue(uint8_t, uint16_t)
 * @brief
 *
 * @pre
 * @post
 * @param u8Value
 * @param u16TimeSmooth
 */
void PHY_vTimer3SetPwmValue(uint8_t u8Value, uint16_t u16TimeSmooth)
{
	u8CurrentPwmValue = (uint8_t)htim3.Instance->CCR1;
	u8DestPwmValue = u8Value;
	u16SmoothPwmStepCount = 0;

	if(u8CurrentPwmValue == u8DestPwmValue)
		u8SmoothPwmActive = PWM_NOP;
	else
	{
		if(u8CurrentPwmValue > u8DestPwmValue)
		{
			u16SmoothPwmStep = u16TimeSmooth/(u8CurrentPwmValue - u8DestPwmValue);
			u8SmoothPwmActive = PWM_DEC;
		}
		else
		{
			u16SmoothPwmStep = u16TimeSmooth/(u8DestPwmValue - u8CurrentPwmValue);
			u8SmoothPwmActive = PWM_INC;
		}
		if(u16SmoothPwmStep <= 0)
		{
			u8SmoothPwmActive = PWM_NOP;
			htim3.Instance->CCR1 = (uint32_t)u8Value;
		}
	}
}
/**
 * @fn uint8_t PHY_u8Spi1Init()
 * @brief Khoi tao khoi Spi1 - dung cho chuc nang giao tiep voi IC do nang luong
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8Spi1Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = SPI_CS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(SPI_CS_GPIO_Port, &GPIO_InitStruct);
	/* USER CODE BEGIN SPI1_Init 0 */

	/* USER CODE END SPI1_Init 0 */

	/* USER CODE BEGIN SPI1_Init 1 */

	/* USER CODE END SPI1_Init 1 */
	/* SPI1 parameter configuration*/
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN SPI1_Init 2 */

	/* USER CODE END SPI1_Init 2 */
	return HAL_OK;
}
/**
 * @fn uint16_t PHY_u16CommEnergyIC(uint8_t, uint8_t, uint16_t)
 * @brief
 *
 * @pre
 * @post
 * @param u8RW
 * @param u8Address
 * @param u16Value
 * @return
 */
uint16_t PHY_u16CommEnergyIC(uint8_t u8RW, uint8_t u8Address, uint16_t u16Value)
{
	uint8_t *pu8Data = (uint8_t *)&u16Value;
	uint16_t u16Output;
	uint8_t i;

	// switch MSB and LSB of value
	u16Output = (u16Value >> 8) | (u16Value << 8);
	u16Value = u16Output;

	// Set read write flag
	u8Address |= u8RW << 7;

	// Disable LoRa chip on M0-LoRa
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_SPI_Transmit(&hspi1, &u8Address, 1, HAL_TIMEOUT);
	/* Must wait 4 us for data to become valid */
	HAL_Delay(4);

	// Read data
	// Do for each byte in transfer
	if (u8RW)
	{
		for (i = 0; i < 2; i++)
		{
		  HAL_SPI_Receive(&hspi1, pu8Data, 1, HAL_TIMEOUT);
		  pu8Data++;
		}
	}
	else
	{
		for (i = 0; i < 2; i++)
		{
			HAL_SPI_Transmit(&hspi1, pu8Data, 1, HAL_TIMEOUT);
			pu8Data++;
		}
	}

	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
	HAL_Delay(10);

	u16Output = (u16Value >> 8) | (u16Value << 8); // reverse MSB and LSB
	return u16Output;
}
/**
 * @fn uint8_t PHY_u8GpioInit()
 * @brief Khoi tao khoi Gpio - dung cho chuc nang giao tiep voi Nut nhan, Led
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8GpioInit()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, LED1_Pin|LED2_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(SIM_KEY_GPIO_Port, SIM_KEY_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : SPI_CS_Pin */
	GPIO_InitStruct.Pin = SPI_CS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(SPI_CS_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : LED1_Pin LED2_Pin */
	GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins : BT_01_Pin BT_02_Pin */
	GPIO_InitStruct.Pin = BT_01_Pin|BT_02_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin : SIM_KEY_Pin */
	GPIO_InitStruct.Pin = SIM_KEY_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(SIM_KEY_GPIO_Port, &GPIO_InitStruct);

	return HAL_OK;
}
/**
 * @fn uint8_t PHY_u8ButtonGpioInit()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8ButtonGpioInit()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pins : BT_01_Pin BT_02_Pin */
	GPIO_InitStruct.Pin = BT_01_Pin|BT_02_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	return HAL_OK;
}
/**
 * @fn uint8_t PHY_u8ButtonGpioRead()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8ButtonGpioRead()
{
	if(u8ButtonState != 0)
		return u8ButtonState;
	return 0;
}
/**
 * @fn uint8_t PHY_u8LedGpioInit()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8LedGpioInit()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, LED1_Pin|LED2_Pin, GPIO_PIN_SET);

	/*Configure GPIO pins : LED1_Pin LED2_Pin */
	GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	return HAL_OK;
}
/**
 * @fn uint8_t PHY_u8Led1On()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8Led1On()
{
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
	return HAL_OK;
}
/**
 * @fn uint8_t PHY_u8Led1Off()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8Led1Off()
{
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
	return HAL_OK;
}
/**
 * @fn uint8_t PHY_u8Led2On()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8Led2On()
{
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
	return HAL_OK;
}
/**
 * @fn uint8_t PHY_u8Led2Off()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8Led2Off()
{
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
	return HAL_OK;
}
/**
 * @fn uint8_t PHY_u8RtcInit()
 * @brief Khoi tao khoi Gpio - dung cho chuc nang giao tiep với RTC
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8RtcInit()
{
	/* USER CODE BEGIN RTC_Init 0 */

	/* USER CODE END RTC_Init 0 */

	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef DateToUpdate = {0};

	/* USER CODE BEGIN RTC_Init 1 */

	/* USER CODE END RTC_Init 1 */
	/** Initialize RTC Only
	*/
	hrtc.Instance = RTC;
	hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
	hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
	if (HAL_RTC_Init(&hrtc) != HAL_OK)
	{
		Error_Handler();
	}

	/* USER CODE BEGIN Check_RTC_BKUP */

	/* USER CODE END Check_RTC_BKUP */

	/** Initialize RTC and set the Time and Date
	*/
	sTime.Hours = 0x11;
	sTime.Minutes = 0x25;
	sTime.Seconds = 0x0;

	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
	{
		Error_Handler();
	}
	DateToUpdate.WeekDay = RTC_WEEKDAY_MONDAY;
	DateToUpdate.Month = RTC_MONTH_JUNE;
	DateToUpdate.Date = 0x21;
	DateToUpdate.Year = 0x21;

	if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN RTC_Init 2 */

	/* USER CODE END RTC_Init 2 */
	return HAL_OK;
}
/**
 * @fn void PHY_vGetDateTime(RTC_DateTimeTypedef*)
 * @brief
 *
 * @pre
 * @post
 * @param hRTC_DateTime
 */
void PHY_vGetDateTime(RTC_DateTimeTypedef* hRTC_DateTime)
{
	RTC_DateTypeDef hRTC_Date = {0};
	RTC_TimeTypeDef hRTC_Time = {0};

	HAL_RTC_GetDate(&hrtc, &hRTC_Date, RTC_FORMAT_BIN);
	HAL_RTC_GetTime(&hrtc, &hRTC_Time, RTC_FORMAT_BIN);

	hRTC_DateTime->Hours = (hRTC_Time.Hours >> 4)*10 + (hRTC_Time.Hours & 0x0f);
	hRTC_DateTime->Minutes = (hRTC_Time.Minutes >> 4)*10 + (hRTC_Time.Minutes & 0x0f);
	hRTC_DateTime->Seconds = (hRTC_Time.Seconds >> 4)*10 + (hRTC_Time.Seconds & 0x0f);

	hRTC_DateTime->WeekDay = (hRTC_Date.WeekDay >> 4)*10 + (hRTC_Date.WeekDay & 0x0f);
	hRTC_DateTime->Month = (hRTC_Date.Month >> 4)*10 + (hRTC_Date.Month & 0x0f);
	hRTC_DateTime->Date = (hRTC_Date.Date >> 4)*10 + (hRTC_Date.Date & 0x0f);
	hRTC_DateTime->Year = (hRTC_Date.Year >> 4)*10 + (hRTC_Date.Year & 0x0f);
}
/**
 * @fn void PHY_vSetDateTime(RTC_DateTimeTypedef*)
 * @brief
 *
 * @pre
 * @post
 * @param hRTC_DateTime
 */
void PHY_vSetDateTime(RTC_DateTimeTypedef* hRTC_DateTime)
{
	RTC_DateTypeDef hRTC_Date = {0};
	RTC_TimeTypeDef hRTC_Time = {0};

	hRTC_Date.WeekDay = hRTC_DateTime->WeekDay;
	hRTC_Date.Month = hRTC_DateTime->Month;
	hRTC_Date.Date = hRTC_DateTime->Date;
	hRTC_Date.Year = hRTC_DateTime->Year;

	hRTC_Time.Hours = hRTC_DateTime->Hours;
	hRTC_Time.Minutes = hRTC_DateTime->Minutes;
	hRTC_Time.Seconds = hRTC_DateTime->Seconds;

	HAL_RTC_SetDate(&hrtc, &hRTC_Date, RTC_FORMAT_BIN);
	HAL_RTC_SetTime(&hrtc, &hRTC_Time, RTC_FORMAT_BIN);
}
/**
 * @fn uint8_t PHY_u8Adc1Init()
 * @brief Khoi tao khoi Gpio - dung cho chuc nang giao tiep voi Ambient Light Sensor
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8Adc1Init()
{
	/* USER CODE BEGIN ADC1_Init 0 */

	/* USER CODE END ADC1_Init 0 */

	ADC_ChannelConfTypeDef sConfig = {0};

	/* USER CODE BEGIN ADC1_Init 1 */

	/* USER CODE END ADC1_Init 1 */
	hadc1.Instance = ADC1;
	hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	if (HAL_ADC_Init(&hadc1) != HAL_OK)
	{
		Error_Handler();
	}
	/** Configure Regular Channel
	*/
	sConfig.Channel = ADC_CHANNEL_0;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN ADC1_Init 2 */
	return HAL_OK;
	/* USER CODE END ADC1_Init 2 */
}
/**
 * @fn uint16_t PHY_u16Adc1Read()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint16_t PHY_u16Adc1Read()
{
	uint16_t mResult = 0;
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	mResult = HAL_ADC_GetValue(&hadc1);
	return mResult;
}
/**
 * @fn uint8_t PHY_u8EnbInterrupt(uint8_t)
 * @brief Enable/Disable all used interrupt
 * u8State = ENB: Enable
 * u8State = DIS: Disable
 *
 * @pre
 * @post
 * @param u8State
 * @return
 */
uint8_t PHY_u8EnbInterrupt(uint8_t u8State)
{
	return HAL_OK;
}
/**
 * @fn uint8_t PHY_u8Uart3EnbInterrupt()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8Uart3EnbInterrupt()
{
	uint8_t u8Flush;
	u8Uart3Path = 0;
	u8Uart3IrptState = 0;
	for(u8Flush = 0; u8Flush < RX_MAX_LEN; u8Flush++)
		u8Rx3Data[u8Flush] = 0;
	HAL_UART_Receive_IT(&huart3, (uint8_t*)u8Rx3Data, RX_MAX_LEN);
	return HAL_OK;
}
/**
 * @fn uint8_t PHY_u8Uart3ReturnRxByte()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t* PHY_u8Uart3ReturnRxByte()
{
	if(u8Uart3IrptState == 1)
	{
		u8Uart3IrptState = 0;
		return (uint8_t*)u8Rx3Data;
	}
	return (uint8_t*)u8Uart3RxByte;
}
/**
 * @fn uint8_t PHY_u8Uart3SendByte()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8Uart3SendByte(uint8_t* pu8Data, uint16_t u16Len)
{
	return HAL_UART_Transmit_IT(&huart3, pu8Data, u16Len);
}
/**
 * @fn void HAL_UART_RxCpltCallback(UART_HandleTypeDef*)
 * @brief Rx Transfer completed callbacks.
 *
 * @pre
 * @post
 * @param Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
 */
__weak void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == huart1.Instance)
	{

	}
	else if(huart->Instance == huart3.Instance)
	{
		u8Uart3IrptState = 1;
		HAL_UART_Receive_IT(&huart3, (uint8_t*)u8Rx3Data, RX_MAX_LEN);
		switch(u8Uart3Path)
		{
			case 0:
				if(u8Rx3Data[0] == 0x01)
			break;
		}
	}
}
/**
 * @fn void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef*)
 * @brief
 *
 * @pre
 * @post
 * @param htim
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	if(htim->Instance == htim2.Instance)
	{
		vButtonRead();
		vSmoothPwmActive();

	}
}
/**
 * @fn void vButtonRead()
 * @brief
 *
 * @pre
 * @post
 */
void vButtonRead()
{
	if(HAL_GPIO_ReadPin(BT_01_GPIO_Port, BT_01_Pin) == GPIO_PIN_RESET)
	{
		if(u8Button1Detect == 0)
			u8Button1Detect = 1;
	}
	else
	{
		if(u8Button1Detect == 1)
		{
			u8Button1Detect = 0;
			u8ButtonState = 1;
		}
	}

	if(HAL_GPIO_ReadPin(BT_02_GPIO_Port, BT_02_Pin) == GPIO_PIN_RESET)
	{
		if(u8Button2Detect == 0)
			u8Button2Detect = 1;
	}
	else
	{
		if(u8Button2Detect == 1)
		{
			u8Button2Detect = 0;
			u8ButtonState = 2;
		}
	}
}
/**
 * @fn void vSmoothPwmActive()
 * @brief
 *
 * @pre
 * @post
 */
void vSmoothPwmActive()
{
	if(u8SmoothPwmActive == PWM_INC)
	{
		u16SmoothPwmStepCount++;
		if(u16SmoothPwmStepCount>= u16SmoothPwmStep)
		{
			u16SmoothPwmStepCount = 0;
			htim3.Instance->CCR1++;
			if(htim3.Instance->CCR1>= (uint32_t)u8DestPwmValue)
			{
				htim3.Instance->CCR1 = (uint32_t)u8DestPwmValue;
				u8SmoothPwmActive = PWM_NOP;
			}
		}
	}
	else if(u8SmoothPwmActive == PWM_DEC)
	{
		u16SmoothPwmStepCount++;
		if(u16SmoothPwmStepCount>= u16SmoothPwmStep)
		{
			u16SmoothPwmStepCount = 0;

			if(htim3.Instance->CCR1 <= 0)
			{
				htim3.Instance->CCR1 = 0;
				u8SmoothPwmActive = PWM_NOP;
			}
			else
			{
				htim3.Instance->CCR1--;
				if(htim3.Instance->CCR1<= (uint32_t)u8DestPwmValue)
				{
					htim3.Instance->CCR1 = (uint32_t)u8DestPwmValue;
					u8SmoothPwmActive = PWM_NOP;
				}
			}
		}
	}
}
/**
 * @fn void vDataCollectStatus()
 * @brief
 *
 * @pre
 * @post
 */
void vDataCollectStatus()
{
	if(u8EnbDataCollect)
	{
		u32DataCollectionCycle++;
		if(u32DataCollectionCycle >= DATA_COLLECTION_CYCLE)
		{
			u8DataCollectStatus = 1;
		}
		else
		{
			u8DataCollectStatus = 0;
		}
	}
}
/**
 * @fn uint8_t PHY_u8EnableDataCollect()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8EnableDataCollect()
{
	u8EnbDataCollect = 1;
	u32DataCollectionCycle = 0;
	u8DataCollectStatus = 1;
	return HAL_OK;
}
/**
 * @fn uint8_t LI_u8DisableDataCollect()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8DisableDataCollect()
{
	u8EnbDataCollect = 0;
	u32DataCollectionCycle = 0;
	u8DataCollectStatus = 0;
	return HAL_OK;
}
/**
 * @fn uint8_t PHY_u8GetDataCollectStatus()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8GetDataCollectStatus()
{
	if(u8DataCollectStatus)
		u32DataCollectionCycle = 0;
	return u8DataCollectStatus;
}
/**
 * @fn uint8_t PHY_u8SimInit()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t PHY_u8SimInit()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();

	HAL_GPIO_WritePin(SIM_KEY_GPIO_Port, SIM_KEY_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : SIM_KEY_Pin */
	GPIO_InitStruct.Pin = SIM_KEY_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(SIM_KEY_GPIO_Port, &GPIO_InitStruct);

	return HAL_OK;
}
/**
 * @fn void PHY_vOnSim()
 * @brief
 *
 * @pre
 * @post
 */
void PHY_vOnSim()
{
	HAL_GPIO_WritePin(SIM_KEY_GPIO_Port, SIM_KEY_Pin, GPIO_PIN_SET);
	HAL_Delay(1000);
	HAL_GPIO_WritePin(SIM_KEY_GPIO_Port, SIM_KEY_Pin, GPIO_PIN_RESET);
	HAL_Delay(3000);
}
/**
 * @fn void PHY_vOffSim()
 * @brief
 *
 * @pre
 * @post
 */
void PHY_vOffSim()
{
	HAL_GPIO_WritePin(SIM_KEY_GPIO_Port, SIM_KEY_Pin, GPIO_PIN_RESET);
	HAL_Delay(1000);
}
/**
 * @fn void PHY_vStorageSchedulerData(Scheduler_DataTypeDef*)
 * @brief
 *
 * @pre
 * @post
 * @param pstSchedulerData
 */
void PHY_vStorageSchedulerData(Scheduler_DataTypeDef* pstSchedulerData)
{
	volatile HAL_StatusTypeDef status;
	FLASH_EraseInitTypeDef EraseInitStruct;
	volatile uint32_t u32Temp = 0x00000000;
	volatile uint32_t u32Addr = START_OF_FLASH;
	uint32_t u32PageError;
	uint8_t u8LoopDay, u8LoopSlot;
	HAL_FLASH_Unlock();
	HAL_FLASH_OB_Unlock();
	PHY_u8Led1On();
	//
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = START_OF_FLASH;
	EraseInitStruct.NbPages = 2; // 1 page = 1KB
	status = HAL_FLASHEx_Erase(&EraseInitStruct, &u32PageError);
	//
	pstSchedulerData->u8Temp1 = 0x11;
	u32Temp = (uint32_t)pstSchedulerData->u8Temp1;
	status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, START_OF_FLASH, u32Temp);
	u32Addr+=4;
	pstSchedulerData->u8Temp2 = 0x22;
	u32Temp = (uint32_t)pstSchedulerData->u8Temp2;
	status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, START_OF_FLASH+4, u32Temp);
	u32Addr+=4;
	pstSchedulerData->u8Temp3 = 0x33;
	u32Temp = (uint32_t)pstSchedulerData->u8Temp3;
	status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, START_OF_FLASH+8, u32Temp);
	//

	for(u8LoopDay = 0; u8LoopDay < DAY_OF_WEEK; u8LoopDay++)
	{
		//
		u32Addr +=4;
		u32Temp = (uint32_t)pstSchedulerData->stSchedulerDataSlot[u8LoopDay].u8DayOfWeek;
		status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, u32Addr, u32Temp);
		u32Addr+=4;
		u32Temp = (uint32_t)pstSchedulerData->stSchedulerDataSlot[u8LoopDay].u8Day;
		status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, u32Addr, u32Temp);
		u32Addr+=4;
		u32Temp = (uint32_t)pstSchedulerData->stSchedulerDataSlot[u8LoopDay].u8Month;
		status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, u32Addr, u32Temp);
		u32Addr+=4;
		u32Temp = (uint32_t)pstSchedulerData->stSchedulerDataSlot[u8LoopDay].u8Year;
		status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, u32Addr, u32Temp);
		//
		for(u8LoopSlot = 0; u8LoopSlot < MAX_OF_SLOT; u8LoopSlot++)
		{
			u32Addr+=4;
			u32Temp = (uint32_t)pstSchedulerData->stSchedulerDataSlot[u8LoopDay].stSchedulerValue[u8LoopSlot].u8Hour;
			status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, u32Addr, u32Temp);
			u32Addr+=4;
			u32Temp = (uint32_t)pstSchedulerData->stSchedulerDataSlot[u8LoopDay].stSchedulerValue[u8LoopSlot].u8Minute;
			status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, u32Addr, u32Temp);
			u32Addr+=4;
			u32Temp = (uint32_t)pstSchedulerData->stSchedulerDataSlot[u8LoopDay].stSchedulerValue[u8LoopSlot].u8Value;
			status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, u32Addr, u32Temp);
		}
	}

	if(status == HAL_OK)
		PHY_u8Led1Off();
	HAL_FLASH_OB_Lock();
	HAL_FLASH_Lock();
}
/**
 * @fn void PHY_vReadSchedulerData(Scheduler_DataTypeDef*)
 * @brief
 *
 * @pre
 * @post
 * @param pstSchedulerData
 */
void PHY_vReadSchedulerData(Scheduler_DataTypeDef* pstSchedulerData)
{

}


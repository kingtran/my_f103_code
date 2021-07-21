/*
 * ligt.c
 *
 *  Created on: Jun 28, 2021
 *      Author: DQSmartIoT
 */
#include "main.h"
#include "ligt.h"
#include "physical.h"

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
uint8_t LI_u8GetDataCollectStatus();
/* USER CODE END PFP */
/**
 * @fn uint8_t LI_u8EnableDataCollect()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t LI_u8EnableDataCollect()
{
	return PHY_u8EnableDataCollect();
}
/**
 * @fn uint8_t LI_u8DisableDataCollect()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t LI_u8DisableDataCollect()
{
	return PHY_u8DisableDataCollect();
}
/**
 * @fn uint8_t LI_u8GetDataCollectStatus()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t LI_u8GetDataCollectStatus()
{
	return PHY_u8GetDataCollectStatus();
}
/**
 * @fn uint8_t LI_u8GetDataCollected(LI_DataCollectedTypeDef*)
 * @brief
 *
 * @pre
 * @post
 * @param pstLiDataCollected
 * @return
 */
uint8_t LI_u8GetDataCollected(LI_DataCollectedTypeDef* pstLiDataCollected)
{
	if(LI_u8GetDataCollectStatus())
	{
		pstLiDataCollected->u16AmbsValue = LIAMBS_u16Read();
		LIENGM_vGetMeasuredValue(&(pstLiDataCollected->stEngmMeasuredValue));
		return 1;
	}
	return 0;
}

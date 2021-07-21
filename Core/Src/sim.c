/*
 * sim.c
 *
 *  Created on: Jun 28, 2021
 *      Author: DQSmartIoT
 */

#include "sim.h"
/**
 * @fn uint8_t SIM_u8SimInit()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t SIM_u8SimInit()
{
	return PHY_u8SimInit();
}
/**
 * @fn void SIM_vOnSim()
 * @brief
 *
 * @pre
 * @post
 */
void SIM_vOnSim()
{
	PHY_vOnSim();
}
/**
 * @fn void SIM_vOffSim()
 * @brief
 *
 * @pre
 * @post
 */
void SIM_vOffSim()
{
	PHY_vOffSim();
}

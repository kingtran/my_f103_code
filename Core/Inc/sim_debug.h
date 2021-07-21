/*
 * sim_debug.h
 *
 *  Created on: May 20, 2021
 *      Author: DQSmartIoT
 */

#ifndef INC_SIM_DEBUG_H_
#define INC_SIM_DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif
/**/
uint8_t sim_debug_out(uint8_t* msg);
uint8_t sim_debug_read(uint8_t* rxbuff);
uint8_t sim_debug_out_temp(uint8_t* msg, uint16_t len);
uint8_t sim_debug_out__(uint8_t* msg);
/**/
#ifdef __cplusplus
}
#endif

#endif /* INC_SIM_DEBUG_H_ */

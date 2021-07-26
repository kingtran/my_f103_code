/*
 * app.h
 *
 *  Created on: Jul 23, 2021
 *      Author: PC
 */

#ifndef INC_APP_H_
#define INC_APP_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "comm.h"
#include "physical.h"

/*StaGetMcuVersion
StaGetControlStatus
StaGetLightSensorValue
StaGetPMVoltageValue
StaGetPMCurrentValue
StaGetPMPowerValue
StaGetPMFrequencyValue
StaGetLightLevelValue
StaGetLightStatus
StaGetTimeStatus
StaGetDateStatus
StaGetWarningStatus
StaSetControlStatus
StaSetLightLevelValue
StaSetLightStatus
StaSetTimeStatus
StaSetDateStatus
StaSetSchedulerStart
StaSetSchedulerData
StaSetSchedulerEnd*/

void APP_vGetMcuVersion();
void APP_vGetControlStatus();
void APP_vGetLightSensorValue();
void APP_vGetPMVoltageValue();
void APP_vGetPMCurrentValue();
void APP_vGetPMPowerValue();
void APP_vGetPMFrequencyValue();
void APP_vGetLightLevelValue();
void APP_vGetLightStatus();
void APP_vGetTimeStatus();
void APP_vGetDateStatus();
void APP_vGetWarningStatus();
void APP_vSetControlStatus();
void APP_vSetLightLevelValue();
void APP_vSetLightStatus();
void APP_vSetTimeStatus();
void APP_vSetDateStatus();
void APP_vSetSchedulerStart();
void APP_vSetSchedulerData();
void APP_vSetSchedulerEnd();

#ifdef __cplusplus
}
#endif


#endif /* INC_APP_H_ */

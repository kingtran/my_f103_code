/*
 * ligt_engm.h
 *
 *  Created on: Jun 28, 2021
 *      Author: DQSmartIoT
 */

#ifndef INC_LIGT_ENGM_H_
#define INC_LIGT_ENGM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "comm.h"
#include "physical.h"

#define SoftReset 0x00 // Software Reset
#define SysStatus 0x01 // System Status
#define FuncEn 0x02    // Function Enable
#define SagTh 0x03     // Voltage Sag Threshold
#define SmallPMod 0x04 // Small-Power Mode
#define LastData 0x06  // Last Read/Write SPI/UART Value
#define LSB 0x08       // RMS/Power 16-bit LSB
#define CalStart 0x20  // Calibration Start Command
#define PLconstH 0x21  // High Word of PL_Constant
#define PLconstH_Default 0x0015
#define PLconstL 0x22 // Low Word of PL_Constant
#define PLconstL_Default 0xD174
#define Lgain 0x23 // L Line Calibration Gain
#define Lgain_Default 0x0000
#define Lphi 0x24 // L Line Calibration Angle
#define Lphi_Default 0x0000
#define Ngain 0x25 // N Line Calibration Gain
#define Ngain_Default 0x0000
#define Nphi 0x26 // N Line Calibration Angle
#define Nphi_Default 0x0000
#define PStartTh 0x27 // Active Startup Power Threshold
#define PStartTh_Default 0x08BD
#define PNolTh 0x28 // Active No-Load Power Threshold
#define PNolTh_Default 0x0000
#define QStartTh 0x29 // Reactive Startup Power Threshold
#define QStartTh_Default 0x0AEC
#define QNolTh 0x2A // Reactive No-Load Power Threshold
#define QNolTh_Default 0x0000
#define MMode 0x2B // Metering Mode Configuration
#define MMode_Default 0x9422
#define CSOne 0x2C    // Checksum 1
#define AdjStart 0x30 // Measurement Calibration Start Command
#define Ugain 0x31    // Voltage rms Gain
#define Ugain_Default 0x6720
#define IgainL 0x32 // L Line Current rms Gain
#define IgainL_Default 0x7A13
#define IgainN 0x33 // N Line Current rms Gain
#define IgainN_Default 0x7530
#define Uoffset 0x34 // Voltage Offset
#define Uoffset_Default 0x0000
#define IoffsetL 0x35 // L Line Current Offset
#define IoffsetL_Default 0x0000
#define IoffsetN 0x36 // N Line Current Offse
#define IoffsetN_Default 0x0000
#define PoffsetL 0x37 // L Line Active Power Offset
#define PoffsetL_Default 0x0000
#define QoffsetL 0x38 // L Line Reactive Power Offset
#define QoffsetL_Default 0x0000
#define PoffsetN 0x39 // N Line Active Power Offset
#define PoffsetN_Default 0x0000
#define QoffsetN 0x3A // N Line Reactive Power Offset
#define QoffsetN_Default 0x0000
#define CSTwo 0x3B     // Checksum 2
#define APenergy 0x40  // Forward Active Energy
#define ANenergy 0x41  // Reverse Active Energy
#define ATenergy 0x42  // Absolute Active Energy
#define RPenergy 0x43  // Forward (Inductive) Reactive Energy
#define Rnenerg 0x44   // Reverse (Capacitive) Reactive Energy
#define Rtenergy 0x45  // Absolute Reactive Energy
#define EnStatus 0x46  // Metering Status
#define Irms 0x48      // L Line Current rms
#define Urms 0x49      // Voltage rms
#define Pmean 0x4A     // L Line Mean Active Power
#define Qmean 0x4B     // L Line Mean Reactive Power
#define Freq 0x4C      // Voltage Frequency
#define PowerF 0x4D    // L Line Power Factor
#define Pangle 0x4E    // Phase Angle between Voltage and L Line Current
#define Smean 0x4F     // L Line Mean Apparent Power
#define IrmsTwo 0x68   // N Line Current rms
#define PmeanTwo 0x6A  // N Line Mean Active Power
#define QmeanTwo 0x6B  // N Line Mean Reactive Power
#define PowerFTwo 0x6D // N Line Power Factor
#define PangleTwo 0x6E // Phase Angle between Voltage and N Line Current
#define SmeanTwo 0x6F  // N Line Mean Apparent Power

uint16_t metering[11];
enum metering_values {
_plconsth,
_plconstl,
_lgain,
_lphi,
_ngain,
_nphi,
_pstartth,
_pnolth,
_qstartth,
_qnolth,
_mmode
};
uint16_t _crc1;
uint16_t measurement[10];
enum measurement_values {
_ugain,
_igain,
_igainn,
_uoffset,
_ioffestl,
_ioffsetn,
_poffestl,
_qoffsetl,
_poffsetn,
_qoffsetn
};
uint16_t _crc2;

uint8_t LIENGM_u8Init();
void LIENGM_vGetMeasuredValue(ENGM_MeasuredValueTypeDef* hENGM_MeasuredValue);

#ifdef __cplusplus
}
#endif

#endif /* INC_LIGT_ENGM_H_ */

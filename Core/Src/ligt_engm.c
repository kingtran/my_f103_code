/*
 * ligt_engm.c
 *
 *  Created on: Jun 28, 2021
 *      Author: DQSmartIoT
 */

#include "ligt_engm.h"

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */
void vATM90E26_SPI();
uint16_t u16CommEnergyIC(uint8_t u8RW, uint8_t u8Address, uint16_t u16Val);
uint16_t u16CalcCheckSum(uint16_t checksum_id);
double dGetLineVoltage();
double dGetLineCurrent();
double dGetActivePower();
double dGetReactivePower();
double dGetApparentPower();
double dGetPhaseAngle();
double dGetFrequency();
double dGetPowerFactor();
double dGetImportEnergy();
double dGetExportEnergy();
void vSetUGain(uint16_t u16Ugain);
void vSetLGain(uint16_t u16Lgain);
void vSetIGain(uint16_t u16Igain);
void vInitEnergyIC();
uint8_t u8CalibrateEnergyIC();
uint16_t u16GetSysStatus();
uint16_t u16GetMeterStatus();

void vATM90E26_SPI()
{
	metering[_plconsth] = 0x00B9;
	metering[_plconstl] = 0xC1F3;
	metering[_lgain] = 0x1D39;
	metering[_lphi] = Lphi_Default;
	metering[_ngain] = Ngain_Default;
	metering[_nphi] = Nphi_Default;
	metering[_pstartth] = PStartTh_Default;
	metering[_pnolth] = PNolTh_Default;
	metering[_qstartth] = QStartTh_Default;
	metering[_qnolth] = QNolTh_Default;
	metering[_mmode] = MMode_Default;
	_crc1 = 0x4A34;

	measurement[_ugain] = 0xD464;
	measurement[_igain] = 0x6E49;
	measurement[_igainn] = IgainN_Default;
	measurement[_uoffset] = Uoffset_Default;
	measurement[_ioffestl] = IoffsetL_Default;
	measurement[_ioffsetn] = IoffsetN_Default;
	measurement[_poffestl] = PoffsetL_Default;
	measurement[_qoffsetl] = QoffsetL_Default;
	measurement[_poffsetn] = PoffsetN_Default;
	measurement[_qoffsetn] = QoffsetN_Default;
	_crc2 = 0xD294;
}

uint16_t u16CommEnergyIC(uint8_t u8RW, uint8_t u8Address, uint16_t u16Val)
{

	return PHY_u16CommEnergyIC(u8RW, u8Address, u16Val);
}

uint16_t u16CalcCheckSum(uint16_t checksum_id)
{
	//#CS1: metering
	// L2C=MOD(H21+H22+...+H2B+L21+L22+...+L2B, 2^8)
	// H2C=H21 XOR H22 XOR ... XOR H2B XOR L21 XOR L22 XOR ... XORL2
	if (checksum_id == 1)
	{
		unsigned char l2c = 0;
		unsigned char h2c = 0;
		for (int i = 0; i < 11; i++)
		{
			l2c += metering[i];
			l2c += metering[i] >> 8;
			h2c ^= metering[i];
			h2c ^= metering[i] >> 8;
		}
		return ((unsigned short)h2c << 8) | l2c;
	}
	//#CS2: measurement
	// L3B=MOD(H31+H32+...+H3A+L31+L32+...+L3A, 2^8)
	// H3B=H31 XOR H32 XOR ... XOR H3A XOR L31 XOR L32 XOR ... XORL3A
	else if (checksum_id == 2)
	{
		unsigned char l3b = 0;
		unsigned char h3b = 0;
		for (int i = 0; i < 10; i++)
		{
			l3b += measurement[i];
			l3b += measurement[i] >> 8;
			h3b ^= measurement[i];
			h3b ^= measurement[i] >> 8;
		}
		return ((unsigned short)h3b << 8) | l3b;
	}
	return 0;
}

double dGetLineVoltage()
{
	uint16_t voltage = u16CommEnergyIC(1, Urms, 0xFFFF);
	return (double)voltage / 100;
}

double dGetLineCurrent()
{
	uint16_t current = u16CommEnergyIC(1, Irms, 0xFFFF);
	return (double)current / 1000;
}

double dGetActivePower()
{
	int16_t apower = (int16_t)u16CommEnergyIC(1, Pmean, 0xFFFF); // Complement, MSB is signed bit
	return (double)apower;
}

double dGetReactivePower()
{
	int16_t apower = (int16_t)u16CommEnergyIC(1, Qmean, 0xFFFF); // Complement, MSB is signed bit
	return (double)apower;
}

double dGetApparentPower()
{
	int16_t apower = (int16_t)u16CommEnergyIC(1, Smean, 0xFFFF); // Complement, MSB is signed bit
	return (double)apower;
}

double dGetPhaseAngle()
{
	int16_t apower = (int16_t)u16CommEnergyIC(1, Pangle, 0xFFFF); // Complement, MSB is signed bit
	return (double)apower;
}

double dGetFrequency()
{
	uint16_t freq = u16CommEnergyIC(1, Freq, 0xFFFF);
	return (double)freq / 100;
}

double dGetPowerFactor()
{
	int16_t pf = (int16_t)u16CommEnergyIC(1, PowerF, 0xFFFF); // MSB is signed
															 // bit
	// if negative
	if (pf & 0x8000)
	{
		pf = (pf & 0x7FFF) * -1;
	}
	return (double)pf / 1000;
}

double dGetImportEnergy()
{
	// Register is cleared after reading
	uint16_t ienergy = u16CommEnergyIC(1, APenergy, 0xFFFF);
	return (double)ienergy * 0.0001; // returns kWh if PL constant set to 1000imp/kWh
}

double dGetExportEnergy()
{
	// Register is cleared after reading
	uint16_t eenergy = u16CommEnergyIC(1, ANenergy, 0xFFFF);
	return (double)eenergy * 0.0001; // returns kWh if PL constant set to 1000imp/kWh
}

void vSetUGain(uint16_t u16Ugain)
{
	measurement[_ugain] = u16Ugain;
}

void vSetLGain(uint16_t u16Lgain)
{
	metering[_lgain] = u16Lgain;
}

void vSetIGain(uint16_t u16Igain)
{
	metering[_igain] = u16Igain;
}

void vInitEnergyIC()
{
	u16CommEnergyIC(0, SoftReset, 0x789A); // Perform soft reset
	u16CommEnergyIC(0, FuncEn, 0x0030);    // Voltage sag irq=1, report on warnout
								  // pin=1, energy dir change irq=0
	u16CommEnergyIC(0, SagTh, 0x1F2F);     // Voltage sag threshhold

//	u8CalibrateEnergyIC();
}

uint8_t u8CalibrateEnergyIC()
{
	unsigned short systemstatus;

	// Calculate checksums
	_crc1 = u16CalcCheckSum(1);
	_crc2 = u16CalcCheckSum(2);

	// Set metering calibration values
	u16CommEnergyIC(0, CalStart, 0x5678); // Metering calibration startup command.
									 // Register 21 to 2B need to be set
	u16CommEnergyIC(0, PLconstH, metering[_plconsth]); // PL Constant MSB
	u16CommEnergyIC(0, PLconstL, metering[_plconstl]); // PL Constant LSB
	u16CommEnergyIC(0, Lgain, metering[_lgain]);       // Line calibration gain
	u16CommEnergyIC(0, CSOne, _crc1); // Write CSOne, as self calculated

//	Serial.print("Checksum 1:");
//	Serial.println(CommEnergyIC(1, CSOne, 0x0000), HEX); // Checksum 1. Needs to be calculated based off the above values.

	// Set measurement calibration values
	u16CommEnergyIC(0, AdjStart, 0x5678); // Measurement calibration startup command, registers 31-3A
	u16CommEnergyIC(0, Ugain, measurement[_ugain]);  // Voltage rms gain
	u16CommEnergyIC(0, IgainL, measurement[_igain]); // L line current gain
	u16CommEnergyIC(0, CSTwo, _crc2); // Write CSTwo, as self calculated

//	Serial.print("Checksum 2:");
//	Serial.println(CommEnergyIC(1, CSTwo, 0x0000), HEX); // Checksum 2. Needs to be calculated based off the above values.

	u16CommEnergyIC(0, CalStart, 0x8765); // Checks correctness of 21-2B registers
									 // and starts normal metering if ok
	u16CommEnergyIC(0, AdjStart, 0x8765); // Checks correctness of 31-3A registers
									 // and starts normal measurement  if ok

	systemstatus = u16GetSysStatus();

	if (systemstatus & 0xC000)
	{
		// checksum 1 error
//		Serial.println("Checksum 1 Error!!");
		return 1;
	}
	if (systemstatus & 0x3000)
	{
		// checksum 2 error
//		Serial.println("Checksum 2 Error!!");
		return 2;
	}
	return 0;
}

uint16_t u16GetSysStatus()
{
	return u16CommEnergyIC(1, SysStatus, 0xFFFF);
}

uint16_t u16GetMeterStatus()
{
	return u16CommEnergyIC(1, EnStatus, 0xFFFF);
}
/* USER CODE END PFP */
/**
 * @fn uint8_t LIENGM_u8Init()
 * @brief
 *
 * @pre
 * @post
 * @return
 */
uint8_t LIENGM_u8Init()
{
	PHY_u8Spi1Init();
	vATM90E26_SPI();
	vInitEnergyIC();
	return u8CalibrateEnergyIC();
}
/**
 * @fn void LIENGM_vGetMeasuredValue(ENGM_MeasuredValueTypeDef*)
 * @brief
 *
 * @pre
 * @post
 * @param hENGM_MeasuredValue
 */
void LIENGM_vGetMeasuredValue(ENGM_MeasuredValueTypeDef* hENGM_MeasuredValue)
{
	hENGM_MeasuredValue->dActivePower = dGetActivePower();
	hENGM_MeasuredValue->dFrequency = dGetFrequency();
	hENGM_MeasuredValue->dLineCurrent = dGetLineCurrent();
	hENGM_MeasuredValue->dLineVoltage = dGetLineVoltage();
}


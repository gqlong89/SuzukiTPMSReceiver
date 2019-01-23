/*
 * tda5235.c
 *
 *  Created on: Jan 14, 2019
 *      Author: wj1080
 */

#include "tda5235.h"
#include "systick.h"
#include "delayUs.h"
#include "spi.h"
#include "kbi.h"
#include "common.h"
#include "halSpi.h"



static uint8_t tda5235ICStatus = 0;
static uint8_t tda5235DeviceID[4] = {0,0,0,0};

static SensorProDef_t sensorPara =
{
	.rxTriggerFlag = FlagRESET,
	.rxRawData[0]  = 0,
	.rxRawData[1]  = 0,
	.rxRawData[2]  = 0,
	.rxRawData[3]  = 0,
	.rxRawData[4]  = 0,
	.rxRawData[5]  = 0,
	.rxRawData[6]  = 0,
	.rxRawData[7]  = 0,
	.rxRawData[8]  = 0,
	.rxRawData[9]  = 0,
	.rxRawData[10] = 0,
	.rxRawData[11] = 0,
};


static const uint8_t basicRun[] =
{
	0x02,	0xA6,	0x00,
	0x02,	0x80,	0x00,	 //Page switch
	0x02,	0x17,	0x02,	 //Wake-Up Control Register
	0x02,	0x1A,	0x08,	 //Wake-Up Bit or Chip Count Register
	0x02,	0x24,	0x28,	 //Signal Detector Saturation Threshold Register
	0x02,	0x26,	0x7E,	 //Synchronization Search Time-Out Register
	0x02,	0x2D,	0x50,	 //AFC Integrator 1 Gain Register 0
	0x02,	0x2F,	0x08,	 //AFC Integrator 2 Gain Register 0
	0x02,	0x31,	0x22,	 //Peak Memory Filter Up-Down Factor Register
	0x02,	0x39,	0x02,	 //Pre Decimation Factor Register
	0x02,	0x3A,	0x0E,	 //Pre Decimation Scaling Register FSK Mode
	0x02,	0x3B,	0x2A,	 //Pre Decimation Scaling Register ASK Mode
	0x02,	0x3C,	0x09,	 //Matched Filter Control Register
	0x02,	0x3D,	0x34,	 //Sampe Rate Converter NCO Tune
	0x02,	0x3E,	0x03,	 //Externel Data Slicer Configuration
	0x02,	0x48,	0x02,	 //Clock and Data Recovery RUNIN Configuration Register
	0x02,	0x4E,	0x10,	 //TSI Length Register A
	0x02,	0x51,	0x56,	 //TSI Pattern Data Reference A Register 0
	0x02,	0x52,	0x55,	 //TSI Pattern Data Reference A Register 1
	0x02,	0x55,	0x01,	 //End Of Message Control Register
	0x02,	0x56,	0x41,	 //EOM Data Length Limit Register
	0x02,	0x58,	0x05,	 //Channel Configuration Register
	0x02,	0x81,	0x52,	 //PP0 and PP1 Configuration Register
	0x02,	0x82,	0x11,	 //PP2 and PP3 Configuration Register
	0x02,	0x94,	0x07,	 //Interrupt Mask Register 0
	0x02,	0x98,	0x01,	 //Self Polling Mode Control Register
	0x02,	0x99,	0x03,	 //Self Polling Mode Reference Timer Register
	0x02,	0x9A,	0x75,	 //Self Polling Mode Off Time Register 0
	0x02,	0x9B,	0x32,	 //Self Polling Mode Off Time Register 1
	0x02,	0x9C,	0xF1,	 //Self Polling Mode On Time Config A Register 0
	0x02,	0xA6,	0x12,	 //Chip Mode Control Register 0
};

/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
void configSensorParaRxTriggerFlag(FlagStatus wValue)
{
	SUSPEND_INTERRUPT();
	sensorPara.rxTriggerFlag = wValue;
	RESUME_INTERRUPT();
}

/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
FlagStatus getSensorParaRxTriggerFlag(void)
{
	return (sensorPara.rxTriggerFlag);
}

/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
SensorProDef_t* getSensorParaStructVarPointer(void)
{
	return (&sensorPara);
}


/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
static void tda5235WriteBytesDataWithChipSelect(uint8_t* wData, uint8_t wtLength)
{
	uint8_t cnt, tempData;
	uint8_t dummyRxData;

	TDA5235_CS_Low();

	for (cnt = 0; cnt < wtLength; cnt++)
	{
		tempData = *(wData + cnt);

#if (TDA5235_COMM_USEHARDSPI == 1)
		HAL_SPITransferWait(SPI0, &dummyRxData, &tempData, 1);
#else
		HAL_SpiWriteOneByteData(tempData);
#endif
	}

	TDA5235_CS_High();
}

/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
static void tda5235WriteReadBytesDataWithChipSelect(uint8_t* pWdata, uint8_t wLength, uint8_t* pRdata, uint8_t rLength)
{
	uint8_t cnt, tempData;
	uint8_t dummyRxData;
	uint8_t dummyTxData = 0x00;

	TDA5235_CS_Low();

	for (cnt = 0; cnt < wLength; cnt++)
	{
		tempData = *(pWdata + cnt);

#if (TDA5235_COMM_USEHARDSPI == 1)
		HAL_SPITransferWait(SPI0, &dummyRxData, &tempData, 1);
#else
		HAL_SpiWriteOneByteData(tempData);
#endif
	}

	for (cnt = 0; cnt < rLength; cnt++)
	{
		tempData = 0;

#if (TDA5235_COMM_USEHARDSPI == 1)
		HAL_SPITransferWait(SPI0, &tempData, &dummyTxData, 1);
#else
		tempData = HAL_SpiReadOneByteData();
#endif
		*(pRdata + cnt) = tempData;
	}

	TDA5235_CS_High();
}

/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
static void tda5235PowerOnReset(void)
{
	GPIO_PinInit(TDA5235_PowerOn_Pin, GPIO_PinOutput_HighCurrent);
	TDA5235_PowerOn_Low();
	HAL_DelayMs(10);
	TDA5235_PowerOn_High();
}

/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
static void tda5235DataWakeupPinInit(void)
{
	uint8_t i;
	KBI_ConfigType kbiConfig;

	kbiConfig.sBits.bMode         = KBI_MODE_EDGE_ONLY;							/* KBI仅检测边沿,即仅边沿触发. */
	kbiConfig.sBits.bIntEn        = 1;											/* KBI中断使能. */
#if defined(CPU_KEA128)
	kbiConfig.sBits.bKbspEn 	  = 1;											/* 当中断标志出现时要读取KBxSP寄存器中的锁存值. */
	kbiConfig.sBits.bRstKbsp      = 1;											/* 复位KBIxSP寄存器. */
#endif

	/* 下面这段for循环很初始化重要,否则局部变量kbiConfig里面的数据很可能是垃圾数据. */
	for (i = 0; i < KBI_MAX_PINS_PER_PORT; i++)
	{
		kbiConfig.sPin[i].bEn = 0;
		kbiConfig.sPin[i].bEdge = KBI_FALLING_EDGE_LOW_LEVEL;
	}

	kbiConfig.sPin[TDA5235_WAKEUP_Piny].bEdge = KBI_FALLING_EDGE_LOW_LEVEL;		/* 下降沿或低电平触发. */
	kbiConfig.sPin[TDA5235_WAKEUP_Piny].bEn   = 1;								/* 当前通道使能. */

	HAL_KBIInit(TDA5235_WAKEUP_KBIx, TDA5235_WAKEUP_KBI_PRIO, &kbiConfig);		/* 初始化KBI且中断优先级最高. */
}

/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
static void tda5235SpiCommPortsInit(void)
{
	SPI_ConfigType spiConfig;

	spiConfig.u32BusClkHz = SYSTEM_BUSCLOCK_HZ;
	spiConfig.u32BitRate  = TDA5235_SPICOMM_BAUDRATE;
	spiConfig.sSettings.bIntEn = 0;
	spiConfig.sSettings.bModuleEn = 1;
	spiConfig.sSettings.bTxIntEn = 0;
	spiConfig.sSettings.bMasterMode = 1;
	spiConfig.sSettings.bClkPolarityLow = 1;
	spiConfig.sSettings.bClkPhase1 = 1;
	spiConfig.sSettings.bMasterAutoDriveSS = 0;
	spiConfig.sSettings.bShiftLSBFirst = 0;
	spiConfig.sSettings.bMatchIntEn = 0;
	spiConfig.sSettings.bModeFaultEn = 0;
	spiConfig.sSettings.bBidirectionModeEn = 0;
	spiConfig.sSettings.bPinAsOuput = 0;
	spiConfig.sSettings.bStopInWaitMode = 0;
	HAL_SPIInit(SPI0, &spiConfig);

	GPIO_PinInit(TDA5235_CS_Pin, GPIO_PinOutput);
	TDA5235_CS_High();
}

/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
static uint8_t tda5235ReadFinalRegisterAddress(void)
{
	uint8_t address;
	uint8_t cmdBuf[2] = {0x03, 0xB3};

	tda5235WriteReadBytesDataWithChipSelect(cmdBuf, (sizeof(cmdBuf) / sizeof(uint8_t)), &address, 1);

	return (address);
}

/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
static uint8_t tda5235ReadFinalRegisterValue(void)
{
	uint8_t value;
	uint8_t cmdBuf[2] = {0x03, 0xB4};

	tda5235WriteReadBytesDataWithChipSelect(cmdBuf, (sizeof(cmdBuf) / sizeof(uint8_t)), &value, 1);

	return (value);
}

/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
static void tda5235WriteConfigRegister(const uint8_t* pConfigPara)
{
	uint8_t retAddress, retData;
	uint8_t tempBuf[3] = {0,0,0};
	uint8_t tryTime = 0;
	uint8_t byteCnt = 0;

	while (tryTime < 5)
	{
		while (!((tempBuf[1] == 0xA6) && (tempBuf[2] != 0x00)))
		{
			tempBuf[0] = *(pConfigPara + byteCnt++);
			tempBuf[1] = *(pConfigPara + byteCnt++);
			tempBuf[2] = *(pConfigPara + byteCnt++);

			tda5235WriteBytesDataWithChipSelect(tempBuf, (sizeof(tempBuf) / sizeof(uint8_t)));
		}

		retAddress = tda5235ReadFinalRegisterAddress();
		retData    = tda5235ReadFinalRegisterValue();

		if ((retAddress == 0xA6) && (retData != 0x00))
		{
			if (retData == 0x12)
			{
				tda5235ICStatus = 0x01;
			}
			else
			{
				tda5235ICStatus = 0x02;
			}

			break;
		}
		else
		{
			tryTime++;
			tda5235ICStatus = 0x00;

			tempBuf[0] = 0;
			tempBuf[1] = 0;
			tempBuf[2] = 0;
			byteCnt    = 0;
		}
	}
}

/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
static void tda5235ReadDeviceID(void)
{
	uint8_t cmdBuf[2] = {0x03, 0xB6};

	tda5235WriteReadBytesDataWithChipSelect(cmdBuf, (sizeof(cmdBuf) / sizeof(uint8_t)), &tda5235DeviceID[0], 1);

	cmdBuf[1] = 0xB7;
	tda5235WriteReadBytesDataWithChipSelect(cmdBuf, (sizeof(cmdBuf) / sizeof(uint8_t)), &tda5235DeviceID[1], 1);

	cmdBuf[1] = 0xB8;
	tda5235WriteReadBytesDataWithChipSelect(cmdBuf, (sizeof(cmdBuf) / sizeof(uint8_t)), &tda5235DeviceID[2], 1);

	cmdBuf[1] = 0xB9;
	tda5235WriteReadBytesDataWithChipSelect(cmdBuf, (sizeof(cmdBuf) / sizeof(uint8_t)), &tda5235DeviceID[3], 1);
}

/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
uint8_t tda5235ReadSpecifiedRegisterValue(uint8_t regAddr)
{
	uint8_t value;
	uint8_t cmdBuf[2];

	cmdBuf[0] = 0x03;
	cmdBuf[1] = regAddr;

	RESUME_INTERRUPT();

	tda5235WriteReadBytesDataWithChipSelect(cmdBuf, (sizeof(cmdBuf) / sizeof(uint8_t)), &value, 1);

	RESUME_INTERRUPT();

	return (value);
}

/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
uint8_t tda5235ReadRSSIRegisterValue(void)
{
	uint8_t rssiValue;
	uint8_t cmdBuf[2] = {0x03, 0xAB};

	RESUME_INTERRUPT();

	tda5235WriteReadBytesDataWithChipSelect(cmdBuf, (sizeof(cmdBuf) / sizeof(uint8_t)), &rssiValue, 1);

	RESUME_INTERRUPT();

	return (rssiValue);
}

/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
void tda5235ReadFIFO(void)
{
	uint8_t cnt = 0, cmd = 0x04;

	SUSPEND_INTERRUPT();

	tda5235WriteReadBytesDataWithChipSelect(&cmd, 1, &sensorPara.rxRawData[cnt], 4);

	cnt += 4;
	tda5235WriteReadBytesDataWithChipSelect(&cmd, 1, &sensorPara.rxRawData[cnt], 4);

	cnt += 4;
	tda5235WriteReadBytesDataWithChipSelect(&cmd, 1, &sensorPara.rxRawData[cnt], 4);

	RESUME_INTERRUPT();
}

/**
  * @函数功能   tda5235射频芯片初始化.用于接收传感器或配置工具发送的数据.
  * @函数功能   注意：TDA5235是433M单向射频接收.
  * @函数参数  无.
  * @函数返回值  无.
  */
void tda5235Init(void)
{
	tda5235PowerOnReset();

#if (TDA5235_COMM_USEHARDSPI == 1)
	tda5235SpiCommPortsInit();
#else
	HAL_SpiCommPortsInit();
#endif

	tda5235WriteConfigRegister(basicRun);

	tda5235ReadDeviceID();

	tda5235DataWakeupPinInit();
}




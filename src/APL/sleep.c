/*
 * sleep.c
 *
 *  Created on: Jan 14, 2019
 *      Author: wj1080
 */

#include <stdio.h>
#include <string.h>
#include "sleep.h"
#include "acc.h"
#include "led.h"
#include "delayus.h"
#include "systick.h"
#include "uart.h"
#include "console.h"
#include "tda5235.h"
#include "crc.h"



/**
  * @brief  system hardware peripheral and module initialization.
  * @param  None.
  * @retval None.
  */
void systemSleepStateProcess(void)
{
	uint8_t calc_CRC;
	uint32_t id;
	SensorProDef_t *pSensorPar = getSensorParaStructVarPointer();

	/* 1, 休眠前现场相关数据的保存处理. */

	/* 2, 关闭相关系统外设的电源以及相关功能,为降低功耗做准备. */

	/* 3, 执行"wfi"指令,使MCU进入休眠态死等,直到唤醒. */

	/* 4, 分析判断唤醒信号源.根据不同的唤醒源转换系统的运行状态. */

	systemDelayUs(8000);
	ledLightOn();

	systemDelayUs(8000);
	ledLightOff();

	if (getSensorParaRxTriggerFlag() == FlagSET)
	{
		tda5235ReadFIFO();

		calc_CRC = CRC8_Calc(&pSensorPar->rxRawData[0], 7, 0, 0x07);

		if (calc_CRC == pSensorPar->rxRawData[7])
		{
			id = ((uint32_t)pSensorPar->rxRawData[0] << 24) + ((uint32_t)pSensorPar->rxRawData[1] << 16) + \
				 ((uint32_t)pSensorPar->rxRawData[2] << 8) + pSensorPar->rxRawData[3];

			if (id == 0x0825690f)
			{
				id = 0;
			}
		}

		configSensorParaRxTriggerFlag(FlagRESET);
	}
}



/*
 * init.c
 *
 *  Created on: Jan 14, 2019
 *      Author: wj1080
 */

#include "init.h"
#include "fsm.h"
#include "systick.h"
#include "pit.h"
#include "gpio.h"
#include "acc.h"
#include "inputKeys.h"
#include "led.h"
#include "delayus.h"
#include "flash.h"
#include "uart.h"
#include "tda5235.h"
#include "common.h"



/**
  * @函数功能   系统外设及设备初始化.
  * @函数参数   无.
  * @函数返回值  无.
  */
void systemInit(void)
{
	ACCSignalStateDef_t accSta;

	suspendSystemInterrupt();							/* 挂起系统总中断. */

#if defined(CPU_KEA64) | defined(CPU_KEA8)
	SIM->SOPT  &= ~SIM_SOPT_NMIE_MASK;
#else
	SIM->SOPT0 &= ~SIM_SOPT0_NMIE_MASK;					/* 关闭系统NMI功能. */
#endif

	FLASH_Init(SYSTEM_BUSCLOCK_HZ);						/* Flash初始化 */

	HAL_SystickInit();									/* 系统"滴答"定时器初始化. */

	HAL_PITChannel0Init();								/* PIT定时器通道0初始化,计数周期:5ms. */

	systemAccSignalInit();								/* ACC钥匙信号检测初始化. */

	inputKeysInit();									/* 用户按键输入初始化. */

	ledLightInit();										/* LED指示灯初始化. */

	HAL_UartCommInit();									/* 调试串口硬件初始化,波特率:115200. */

	tda5235Init();										/* tda5235射频芯片初始化. */

	resumeSystemInterrupt();							/* 恢复系统总中断. */

	accSta = systemAccSignalDetect();

	switch (accSta)
	{
		case ACC_VALID:   configureSystemFsmValue(Running);break;
		case ACC_INVALID: configureSystemFsmValue(Sleep);break;
		default: configureSystemFsmValue(Sleep);break;
	}
}


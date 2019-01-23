/*
 * acc.c
 *
 *  Created on: Jan 14, 2019
 *      Author: wj1080
 */

#include "acc.h"
#include "kbi.h"
#include "common.h"


static ACCSignalStateDef_t accSignalState = ACC_INVALID;					/* ACC钥匙信号默认无效态. */
static ACCSignalINTTriggerStateDef_t accSignalINTState = ACC_INT_FALSE;		/* ACC钥匙信号中断触发状态标志默认清零. */

static ACCSignalPropertyDef_t accSignalPro;
static ACCSignalEventFIFODef_t accSignalFifo;


/**
  * @函数功能    读取ACC钥匙信号引脚端口的电平值.如果读出来的是0信号则表示ACC钥匙信号有效,如果都出来的是1信号则表示ACC钥匙信号无效.
  * @函数参数  	无.
  * @函数返回值	 1, ACC钥匙信号有效; 0, ACC钥匙信号无效;
  */
static uint8_t isSystemAccSignalValid(void)
{
	if (ACC_SIGNAL_Read() == 0)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
  * @函数功能    ACC钥匙信号无效态硬件触发中断条件初始化.该函数需要在上电复位后调用或需要检测ACC钥匙信号有效时调用一次.
  * @函数参数  	无.
  * @函数返回值	 无.
  */
static void systemAccSignalInvalidInitHard(void)
{
	uint8_t i;
	KBI_ConfigType kbiConfig;

	/* 此处有个BUG,初次调用该函数会出现HardFault,未找到原因.估计是未开启外设时钟就操作其寄存器会出错. */
//	KBI_DeInit(ACC_SIGNAL_KBIx);											/* 复位KBI. */

	kbiConfig.sBits.bMode         = KBI_MODE_EDGE_ONLY;						/* KBI仅检测边沿,即仅边沿触发. */
	kbiConfig.sBits.bIntEn        = 1;										/* KBI中断使能. */
#if defined(CPU_KEA128)
	kbiConfig.sBits.bKbspEn 	  = 1;										/* 当中断标志出现时要读取KBxSP寄存器中的锁存值. */
	kbiConfig.sBits.bRstKbsp      = 1;										/* 复位KBIxSP寄存器. */
#endif

	/* 下面这段for循环很初始化重要,否则局部变量kbiConfig里面的数据很可能是垃圾数据. */
	for (i = 0; i < KBI_MAX_PINS_PER_PORT; i++)
	{
		kbiConfig.sPin[i].bEn = 0;
		kbiConfig.sPin[i].bEdge = KBI_FALLING_EDGE_LOW_LEVEL;
	}

	kbiConfig.sPin[ACC_SIGNAL_Piny].bEdge = KBI_FALLING_EDGE_LOW_LEVEL;		/* 下降沿或低电平触发. */
	kbiConfig.sPin[ACC_SIGNAL_Piny].bEn   = 1;								/* 当前通道使能. */

	HAL_KBIInit(ACC_SIGNAL_KBIx, 0, &kbiConfig);							/* 初始化KBI且中断优先级最高. */
}

/**
  * @函数功能    ACC钥匙信号有效态硬件触发中断条件初始化.该函数需要在检测ACC钥匙信号无效的时候调用一次.
  * @函数参数  	无.
  * @函数返回值	 无.
  */
static void systemAccSignalValidInitHard(void)
{
	uint8_t i;
	KBI_ConfigType kbiConfig;

	/* 此处有个BUG,初次调用该函数会出现HardFault,未找到原因.估计是未开启外设时钟就操作其寄存器会出错. */
//	KBI_DeInit(ACC_SIGNAL_KBIx);											/* 复位KBI. */

	kbiConfig.sBits.bMode         = KBI_MODE_EDGE_ONLY;						/* KBI仅检测边沿,即仅边沿触发. */
	kbiConfig.sBits.bIntEn        = 1;										/* KBI中断使能. */
#if defined(CPU_KEA128)
	kbiConfig.sBits.bKbspEn 	  = 1;										/* 当中断标志出现时要读取KBxSP寄存器中的锁存值. */
	kbiConfig.sBits.bRstKbsp      = 1;										/* 复位KBIxSP寄存器. */
#endif

	/* 下面这段for循环很初始化重要,否则局部变量kbiConfig里面的数据很可能是垃圾数据. */
	for (i = 0; i < KBI_MAX_PINS_PER_PORT; i++)
	{
		kbiConfig.sPin[i].bEn = 0;
		kbiConfig.sPin[i].bEdge = KBI_FALLING_EDGE_LOW_LEVEL;
	}

	kbiConfig.sPin[ACC_SIGNAL_Piny].bEdge = KBI_RISING_EDGE_HIGH_LEVEL;		/* 上升沿或高电平触发. */
	kbiConfig.sPin[ACC_SIGNAL_Piny].bEn   = 1;								/* 当前通道使能. */

	HAL_KBIInit(ACC_SIGNAL_KBIx, 0, &kbiConfig);							/* 初始化KBI且中断优先级最高. */
}

/**
  * @函数功能   系统ACC钥匙信号检测结构体全局变量初始化.
  * @函数参数  	无.
  * @函数返回值	 无.
  */
static void systemAccSignalInitVar(void)
{
	uint8_t i;

	accSignalFifo.writePtr = 0;
	accSignalFifo.readPtr  = 0;

	for (i = 0; i < ACC_SIGNAL_EVENT_FIFO_SIZE; i++)
	{
		accSignalFifo.ebuffer[i] = (uint8_t)ACC_SIGNAL_NONE;
	}

	accSignalPro.IsAccSigValidFunc = isSystemAccSignalValid;
	accSignalPro.validCount   = 0;
	accSignalPro.invalidCount = 0;
	accSignalPro.eventMutex   = 1;
	accSignalPro.timScanCount = 0;
}

/**
  * @函数功能   系统ACC钥匙信号检测读取.用户只要调用该函数一次就可获得系统ACC钥匙信号的当前状态.
  * @函数参数  	无.
  * @函数返回值	 实际的ACC钥匙信号状态.ACC_VALID,钥匙信号有效; ACC_INVALID,钥匙信号无效;
  */
ACCSignalStateDef_t systemAccSignalDetect(void)
{
	uint8_t accEvt = 0;

	if (accSignalINTState == ACC_INT_TRUE) 									/* ACC钥匙信号触发中断标志有效. */
	{
		while (!accEvt) 													/* 读取ACC钥匙信号事件缓存,直到读到了ACC事件. */
		{
			accEvt = systemAccSignalGetEvent();								/* 读取ACC钥匙信号事件. */
		}

		if (accSignalState == ACC_INVALID) 									/* 当前ACC钥匙信号是无效态. */
		{
			if (accEvt == (uint8_t)ACC_SIGNAL_VALID_ET) 					/* 读取到的是ACC钥匙信号有效事件. */
			{
				accSignalState = ACC_VALID;

				systemAccSignalValidInitHard();
			}
		}
		else if (accSignalState == ACC_VALID)								/* 当前ACC钥匙信号是有效态. */
		{
			if (accEvt == (uint8_t)ACC_SIGNAL_INVALID_ET)
			{
				accSignalState = ACC_INVALID;

				systemAccSignalInvalidInitHard();
			}
		}

		accSignalPro.eventMutex = 1;										/* 释放访问事件FIFO的互斥量.  */
		accSignalINTState       = ACC_INT_FALSE;							/* 清除ACC钥匙信号触发中断标志. */
	}

	return (accSignalState);
}

/**
  * @函数功能   系统ACC钥匙信号检测初始化.包括涉及到的全局变量初始化和硬件检测端口初始化.
  * @函数参数  	无.
  * @函数返回值	 无.
  */
void systemAccSignalInit(void)
{
	systemAccSignalInitVar();
	systemAccSignalInvalidInitHard();
}

/**
  * @函数功能   向ACC钥匙信号事件缓存器中添加钥匙事件值.
  * @函数参数  	wtCode,待写入的钥匙事件.
  * @函数返回值	 无.
  */
void systemAccSignalPutEvent(uint8_t wtCode)
{
	accSignalFifo.ebuffer[accSignalFifo.writePtr] = wtCode;

	if (++accSignalFifo.writePtr >= ACC_SIGNAL_EVENT_FIFO_SIZE)
	{
		accSignalFifo.writePtr = 0;
	}
}

/**
  * @函数功能   从ACC钥匙信号事件缓存器中读取钥匙事件值.
  * @函数参数  	无.
  * @函数返回值	 从事件缓存器中读出的钥匙事件.
  */
uint8_t systemAccSignalGetEvent(void)
{
	uint8_t ret = 0;

	if (accSignalFifo.readPtr == accSignalFifo.writePtr)
	{
		return (ret);
	}
	else
	{
		SUSPEND_INTERRUPT();
		ret = accSignalFifo.ebuffer[accSignalFifo.readPtr];
		accSignalFifo.ebuffer[accSignalFifo.readPtr] = (uint8_t)ACC_SIGNAL_NONE;
		RESUME_INTERRUPT();

		if (++accSignalFifo.readPtr >= ACC_SIGNAL_EVENT_FIFO_SIZE)
		{
			accSignalFifo.readPtr = 0;
		}

		return (ret);
	}
}

/**
  * @函数功能   从ACC钥匙信号事件缓存器中读取钥匙事件值.
  * @函数参数  	无.
  * @函数返回值	 从事件缓存器中读出的钥匙事件.
  */
static void systemAccSignalEventDetect(void)
{
	ACCSignalPropertyDef_t* pAccPro = &accSignalPro;

	if (accSignalState == ACC_VALID)										/* 当前ACC信号是有效态. */
	{
		if (pAccPro->IsAccSigValidFunc() == 0)								/* 有效态收到ACC信号无效. */
		{
			pAccPro->validCount = 0;

			if (pAccPro->invalidCount < ACC_SIGNAL_FILTER_TIME)
			{
				pAccPro->invalidCount++;
			}
			else
			{
				if (pAccPro->eventMutex == 1)								/* 获取访问事件FIFO的互斥量. */
				{
					pAccPro->eventMutex = 0;

					systemAccSignalPutEvent((uint8_t)ACC_SIGNAL_INVALID_ET);
				}
			}
		}
		else 																/* 有效态收到ACC信号有效. */
		{
			pAccPro->invalidCount = 0;

			if (pAccPro->validCount < ACC_SIGNAL_FILTER_TIME)
			{
				pAccPro->validCount++;
			}
			else
			{
				if (pAccPro->eventMutex == 1)								/* 获取访问事件FIFO的互斥量. */
				{
					pAccPro->eventMutex = 0;

					systemAccSignalPutEvent((uint8_t)ACC_SIGNAL_VALID_ET);
				}
			}
		}
	}
	else																	/* 当前ACC信号是无效态. */
	{
		if (pAccPro->IsAccSigValidFunc() != 0)								/* 无效态收到ACC信号有效. */
		{
			pAccPro->invalidCount = 0;

			if (pAccPro->validCount < ACC_SIGNAL_FILTER_TIME)
			{
				pAccPro->validCount++;
			}
			else
			{
				if (pAccPro->eventMutex == 1)								/* 获取访问事件FIFO的互斥量. */
				{
					pAccPro->eventMutex = 0;

					systemAccSignalPutEvent((uint8_t)ACC_SIGNAL_VALID_ET);
				}
			}
		}
		else 																/* 无效态收到ACC信号无效.(因抖动原因造成) */
		{
			pAccPro->validCount = 0;

			if (pAccPro->invalidCount < ACC_SIGNAL_FILTER_TIME)
			{
				pAccPro->invalidCount++;
			}
			else
			{
				if (pAccPro->eventMutex == 1)								/* 获取访问事件FIFO的互斥量. */
				{
					pAccPro->eventMutex = 0;

					systemAccSignalPutEvent((uint8_t)ACC_SIGNAL_INVALID_ET);
				}
			}
		}
	}
}

/**
  * @函数功能   ACC钥匙信号触发中断回调函数.该函数需要由KBI键盘中断ISR调用,实际上就是外部中断.
  * @函数参数  	无.
  * @函数返回值	 无.
  */
void systemAccSignalTriggerINTCallback(void)
{
	if (accSignalINTState == ACC_INT_FALSE)
	{
		accSignalINTState = ACC_INT_TRUE;
	}
}

/**
  * @函数功能   ACC钥匙信号定时扫描回调函数.该函数需要由定时器中断服务程序(TIMER_ISR)周期调用,用于实时检测状态值.
  * @函数参数  	无.
  * @函数返回值	 无.
  */
void systemAccSignalScanCallback(void)
{
	const uint8_t SCANPERIOD = 10;

	if (accSignalINTState == ACC_INT_TRUE)
	{
		if (++accSignalPro.timScanCount >= SCANPERIOD)
		{
			accSignalPro.timScanCount = 0;

			systemAccSignalEventDetect();
		}
	}
}



/*
 * learning.c
 *
 *  Created on: Jan 14, 2019
 *      Author: wj1080
 */

#include "learning.h"
#include "inputKeys.h"
#include "common.h"
#include "acc.h"
#include "fsm.h"


/**
  * @函数功能   TDA5235接收配置工具传送上来的参数信息并处理.注意：这是一个弱函数,用户可在其它位置再次定义一个同名同参的函数替代之.
  * @函数参数  	无.
  * @函数返回值	 无.
  */
__attribute__((weak)) void tda5235ReceiveFromConfigToolProcess(void)
{
;
}

/**
  * @函数功能   LCD显示器处于学习态中的信息显示.注意：这是一个弱函数,用户可在其它位置再次定义一个同名同参的函数替代之.
  * @函数参数  	无.
  * @函数返回值	 无.
  */
__attribute__((weak)) void lcdDisplayerLearningDis(void)
{
;
}

/**
  * @函数功能   系统处于学习态的任务处理.备注：学习过程如何结束暂不清除,所以由学习态转变为运行态的逻辑切换暂无法实现,需讨论之.
  * @函数参数  	无.
  * @函数返回值	 无.
  */
void systemLearningStateProcess(void)
{
	uint8_t keyEvent = KEY_NONE;
	ACCSignalStateDef_t accStat = ACC_VALID;

	/* 1, 接收并读取TDA5235收到的配置工具发送上来的无线数据. */
	tda5235ReceiveFromConfigToolProcess();

	/* 2, 查询用户按键事件. */
	keyEvent = inputKeysGetEvent();

	if (keyEvent == FLIPKEY_DOWN) 							/* 翻页键短按. */
	{
		/* Add code here to do... */
	}

	/* 3, 液晶显示屏实时显示信息数据. */
	lcdDisplayerLearningDis();

	/* 4, 查询ACC钥匙信号是否有效. */
	accStat = systemAccSignalDetect();

	if (accStat == ACC_INVALID)
	{
		configureSystemFsmValue(Sleep);						/* ACC钥匙信号无效,直接进入休眠态. */
	}
}

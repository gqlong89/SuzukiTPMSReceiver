/*
 * running.c
 *
 *  Created on: Jan 14, 2019
 *      Author: wj1080
 */

#include "running.h"
#include "inputKeys.h"
#include "fsm.h"

/**
  * @函数功能    显示器初始化信息显示.注意：这是一个弱函数,用户可在其它位置再次定义一个同名同参的函数替代之.
  * @函数参数  	无.
  * @函数返回值	 无.
  */
__attribute__((weak)) void lcdDisplayerInitialInfoDis(void)
{
;
}

/**
  * @函数功能    蜂鸣器自诊断一次,用于ACC钥匙启动信号开启后的自检测.注意：这是一个弱函数,用户可在其它位置再次定义一个同名同参的函数替代之.
  * @函数参数  	无.
  * @函数返回值	 无.
  */
__attribute__((weak)) void beeperSelfDiagnostic(void)
{
;
}


/**
  * @函数功能    系统运行态任务处理.
  * @函数参数  	无.
  * @函数返回值	 无.
  */
void systemRunningStateProcess(void)
{
	uint8_t keyEvent = KEY_NONE;

	lcdDisplayerInitialInfoDis();							/* lcd显示屏初始化显示全屏信息,用于lcd显示的自检测. */

	beeperSelfDiagnostic();									/* 蜂鸣器自诊断一次,用于ACC钥匙启动信号开启后的自检测. */

	keyEvent = inputKeysGetEvent();							/* 用户按键事件检测. */

	if (keyEvent == SETKEY_LONG)							/* 检测到了"设置"键长按事件.准备进入"学习态". */
	{
		configureSystemFsmValue(Learning);
	}
	else													/* 其它事件或没有检测到按键事件,准备进入"正常态". */
	{
		configureSystemFsmValue(Normal);
	}
}



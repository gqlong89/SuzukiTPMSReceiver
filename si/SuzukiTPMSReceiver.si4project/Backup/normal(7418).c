/*
 * normal.c
 *
 *  Created on: Jan 14, 2019
 *      Author: wj1080
 */

#include "normal.h"
#include "inputKeys.h"
#include "fsm.h"
#include "common.h"
#include "tda5235.h"
#include "acc.h"
#include "fsm.h"


/**
  * @函数功能   TDA5235接收传感器传送上来的参数信息并处理.注意：这是一个弱函数,用户可在其它位置再次定义一个同名同参的函数替代之.
  * @函数参数  	无.
  * @函数返回值	 无.
  */
__attribute__((weak)) void tda5235ReceiveFromSensorProcess(void)
{;}

/**
  * @函数功能   系统报警信息查询处理.注意：这是一个弱函数,用户可在其它位置再次定义一个同名同参的函数替代之.
  * @函数参数  	无.
  * @函数返回值	 无.
  */
__attribute__((weak)) void systemAlarmQueryProcess(void)
{;}

/**
  * @函数功能   LCD显示器处于正常态中的信息显示.注意：这是一个弱函数,用户可在其它位置再次定义一个同名同参的函数替代之.
  * @函数参数  	无.
  * @函数返回值	 无.
  */
__attribute__((weak)) void lcdDisplayerNormalDis(void)
{;}



/**
  * @函数功能   系统处于正常态的任务处理.
  * @函数参数  	无.
  * @函数返回值	 无.
  */
void systemNormalStateProcess(void)
{
	uint8_t keyEvent = KEY_NONE;
	FlagStatus modeStat = FlagRESET;
	ACCSignalStateDef_t accStat = ACC_VALID;

	/* 1, 接收并读取TDA5235收到的传感器发送上来的无线数据. */
	tda5235ReceiveFromSensorProcess();

	/* 2, 分析判断系统报警状态结果. */
	systemAlarmQueryProcess();

	/* 3, 查询用户按键事件. */
	keyEvent = inputKeysGetEvent();

	switch (keyEvent)
	{
		case SETKEY_LONG:  configureSystemFsmValue(Learning); modeStat = FlagSET; break;		/* 设置键长按. */
		case FLIPKEY_DOWN: /* Add code here to do... */ break;									/* 翻页键短按. */
		case FLIPKEY_LONG: /* Add code here to do... */ break;									/* 翻页键长按. */
		default: break;
	}
	if (modeStat == FlagSET)return;

	/* 4, 液晶显示屏实时显示信息数据. */
	lcdDisplayerNormalDis();

	/* 5, 查询ACC钥匙信号是否有效. */
	accStat = systemAccSignalDetect();

	if (accStat == ACC_INVALID)
	{
		configureSystemFsmValue(Sleep);															/* ACC钥匙信号无效,直接进入休眠态. */
	}
}


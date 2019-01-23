/*
 * alarm.c
 *
 *  Created on: Jan 19, 2019
 *      Author: wj1080
 */

#include "alarm.h"
#include "gpio.h"



//static systemAlarmFifoDef_t systemAlarmInfo =
//{
//	.AlarmTypeFifo[0]   = Alarm_None,
//	.AlarmTypeFifo[1]   = Alarm_None,
//	.AlarmTypeFifo[2]   = Alarm_None,
//	.AlarmTypeFifo[3]   = Alarm_None,
//	.AlarmTypeFifo[4]   = Alarm_None,
//	.AlarmTypeFifo[5]   = Alarm_None,
//
//	.AlarmPosFifo[0][0] = 0,
//	.AlarmPosFifo[0][1] = 0,
//	.AlarmPosFifo[0][2] = 0,
//	.AlarmPosFifo[0][3] = 0,
//
//	.AlarmPosFifo[1][0] = 0,
//	.AlarmPosFifo[1][1] = 0,
//	.AlarmPosFifo[1][2] = 0,
//	.AlarmPosFifo[1][3] = 0,
//
//	.AlarmPosFifo[2][0] = 0,
//	.AlarmPosFifo[2][1] = 0,
//	.AlarmPosFifo[2][2] = 0,
//	.AlarmPosFifo[2][3] = 0,
//
//	.AlarmPosFifo[3][0] = 0,
//	.AlarmPosFifo[3][1] = 0,
//	.AlarmPosFifo[3][2] = 0,
//	.AlarmPosFifo[3][3] = 0,
//
//	.AlarmPosFifo[4][0] = 0,
//	.AlarmPosFifo[4][1] = 0,
//	.AlarmPosFifo[4][2] = 0,
//	.AlarmPosFifo[4][3] = 0,
//
//	.AlarmPosFifo[5][0] = 0,
//	.AlarmPosFifo[5][1] = 0,
//	.AlarmPosFifo[5][2] = 0,
//	.AlarmPosFifo[5][3] = 0,
//};


static systemAlarmInfoDef_t curAlarmInf;



/**
  * @函数功能  报警蜂鸣器硬件端口初始化.
  * @函数参数  无.
  * @函数返回值  无.
  */
void alarmBeeperPortInit(void)
{
	ALARM_BEEPER_LOW();
	GPIO_PinInit(ALARM_BEEPER_Pin, GPIO_PinOutput);
	ALARM_BEEPER_LOW();
}

/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
static void dataLoseAlarmProcess(void)
{
	curAlarmInf.dataLoseCount++;

	if (curAlarmInf.dataLoseCount >= DATALOSE_ALARM_TIME)
	{
		curAlarmInf.dataLoseCount = 0;

		ALARM_BEEPER_TOGGLE();
	}
}

/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
static void tirePressureHighAlarmProcess(void)
{
	curAlarmInf.pressureHighCount++;

	if (curAlarmInf.pressureHighCount >= PRESSUREHIGH_ALARM_TIME)
	{
		curAlarmInf.pressureHighCount = 0;

		ALARM_BEEPER_TOGGLE();
	}
}

/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
static void tireTempHighAlarmProcess(void)
{
	curAlarmInf.tempHighCount++;

	if (curAlarmInf.tempHighCount >= TEMPHIGH_ALARM_TIME)
	{
		curAlarmInf.tempHighCount = 0;

		ALARM_BEEPER_TOGGLE();
	}
}

/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
static void tireLeakAlarmProcess(void)
{
	curAlarmInf.leakCount++;

	if (curAlarmInf.leakCount >= LEAK_ALARM_TIME)
	{
		curAlarmInf.leakCount = 0;

		ALARM_BEEPER_TOGGLE();
	}
}

/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
static void tirePressureLowAlarmProcess(void)
{
	curAlarmInf.pressureLowCount++;

	if (curAlarmInf.pressureLowCount >= PRESSURELOW_ALARM_TIME)
	{
		curAlarmInf.pressureLowCount = 0;

		ALARM_BEEPER_TOGGLE();
	}
}

/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
static void sensorVoltLowAlarmProcess(void)
{
	curAlarmInf.voltLowCount++;

	if (curAlarmInf.voltLowCount >= VOLTLOW_ALARM_TIME)
	{
		curAlarmInf.voltLowCount = 0;

		ALARM_BEEPER_TOGGLE();
	}
}

/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
static void beeperAlarmParaVarInit(void)
{
	curAlarmInf.beepAlarmType = Alarm_None;
	curAlarmInf.dataLoseCount = 0;
	curAlarmInf.pressureHighCount = 0;
	curAlarmInf.tempHighCount = 0;
	curAlarmInf.leakCount = 0;
	curAlarmInf.pressureLowCount = 0;
	curAlarmInf.voltLowCount = 0;
}

/**
  * @函数功能
  * @函数参数
  * @函数返回值
  */
void beeperAlarming(void)
{
	if (curAlarmInf.beepAlarmType != Alarm_None)
	{
		switch (curAlarmInf.beepAlarmType)
		{
			case Alarm_DataLose: 		 dataLoseAlarmProcess(); break;
			case Alarm_TirePressureHigh: tirePressureHighAlarmProcess(); break;
			case Alarm_TireTempHigh: 	 tireTempHighAlarmProcess(); break;
			case Alarm_TireLeak: 		 tireLeakAlarmProcess(); break;
			case Alarm_TirePressureLow:  tirePressureLowAlarmProcess(); break;
			case Alarm_SensorVoltLow: 	 sensorVoltLowAlarmProcess(); break;
			default: break;
		}
	}
	else
	{
		ALARM_BEEPER_LOW();
		beeperAlarmParaVarInit();
	}
}








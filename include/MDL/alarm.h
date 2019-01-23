/*
 * alarm.h
 *
 *  Created on: Jan 19, 2019
 *      Author: wj1080
 */

#ifndef ALARM_H_
#define ALARM_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "derivative.h"


#define   ALARM_BEEPER_Pin			GPIO_PTA6
#define   ALARM_BEEPER_HIGH()		GPIO_PinSet(ALARM_BEEPER_Pin)
#define   ALARM_BEEPER_LOW()		GPIO_PinClear(ALARM_BEEPER_Pin)
#define   ALARM_BEEPER_TOGGLE()		GPIO_PinToggle(ALARM_BEEPER_Pin)


#define   DATALOSE_ALARM_TIME		(200)
#define   PRESSUREHIGH_ALARM_TIME	(400)
#define   TEMPHIGH_ALARM_TIME		(600)
#define   LEAK_ALARM_TIME			(800)
#define   PRESSURELOW_ALARM_TIME	(1000)
#define   VOLTLOW_ALARM_TIME		(1200)


typedef enum
{
	Alarm_None = 0,							/* 无任何报警 */
	Alarm_DataLose,							/* 数据丢失报警 */
	Alarm_TirePressureHigh,					/* 胎压过高报警 */
	Alarm_TireTempHigh,						/* 胎温过高报警 */
	Alarm_TireLeak,							/* 轮胎漏气报警 */
	Alarm_TirePressureLow,					/* 胎压过低报警 */
	Alarm_SensorVoltLow,					/* 传感器电池电压低报警 */
}systemAlarmTypeDef_t;


#define  MAX_ALARMTYPE_FIFO_SIZE	(6)
#define  MAX_ALARMPOS_FIFO_SIZE		(4)

typedef struct
{
	systemAlarmTypeDef_t AlarmTypeFifo[MAX_ALARMTYPE_FIFO_SIZE];
	uint8_t AlarmPosFifo[MAX_ALARMTYPE_FIFO_SIZE][MAX_ALARMPOS_FIFO_SIZE];

	uint8_t writePtr;
	uint8_t readPtr;

}systemAlarmFifoDef_t;


typedef struct
{
	systemAlarmTypeDef_t disAlarmType;
	uint8_t disAlarmPos[4];

	systemAlarmTypeDef_t beepAlarmType;
	uint16_t dataLoseCount;
	uint16_t pressureHighCount;
	uint16_t tempHighCount;
	uint16_t leakCount;
	uint16_t pressureLowCount;
	uint16_t voltLowCount;

}systemAlarmInfoDef_t;



#ifdef __cplusplus
}
#endif
#endif /* APL_ALARM_H_ */

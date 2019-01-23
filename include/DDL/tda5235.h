/*
 * tda5235.h
 *
 *  Created on: Jan 14, 2019
 *      Author: wj1080
 */

#ifndef TDA5235_H_
#define TDA5235_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "derivative.h"
#include "common.h"


#define  TDA5235_COMM_USEHARDSPI	1										/* 使用硬件SPI接口与TDA5235通信. */

#define  TDA5235_CS_Pin			GPIO_PTB5
#define  TDA5235_CS_High()		GPIO_PinSet(TDA5235_CS_Pin)
#define  TDA5235_CS_Low()		GPIO_PinClear(TDA5235_CS_Pin)

#define  TDA5235_SPICOMM_BAUDRATE	(100000)								/* 硬件SPI通信波特率baudrate = 100Kbps */


#define  TDA5235_PowerOn_Pin		GPIO_PTD1
#define  TDA5235_DataWakeIRQ_Pin	GPIO_PTE5

#define  TDA5235_WAKEUP_KBIx		(KBI1)
#define  TDA5235_WAKEUP_Piny		(KBI1_P5)
#define  TDA5235_WAKEUP_KBI_PRIO	(0)

#define  TDA5235_PowerOn_High()		GPIO_PinSet(TDA5235_PowerOn_Pin)
#define  TDA5235_PowerOn_Low()		GPIO_PinClear(TDA5235_PowerOn_Pin)


#define  MAX_RECEIVED_SIZE			(12)

typedef struct
{
	uint8_t rxRawData[MAX_RECEIVED_SIZE];

	FlagStatus rxTriggerFlag;

}SensorProDef_t;


 void configSensorParaRxTriggerFlag(FlagStatus wValue);
 FlagStatus getSensorParaRxTriggerFlag(void);
 SensorProDef_t* getSensorParaStructVarPointer(void);

 uint8_t tda5235ReadSpecifiedRegisterValue(uint8_t regAddr);
 uint8_t tda5235ReadRSSIRegisterValue(void);
 void tda5235ReadFIFO(void);
 void tda5235Init(void);

#ifdef __cplusplus
}
#endif
#endif /* DDL_TDA5235_H_ */

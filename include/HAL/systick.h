/*
 * systick.h
 *
 *  Created on: Jan 12, 2019
 *      Author: wj1080
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "derivative.h"


#define  SYSTICK_INT_PRIORITY			((uint32_t)3)	/* Systick interrupt priority(Lowest by default). */


typedef enum
{
	HAL_TICK_FREQ_10HZ = 100,
	HAL_TICK_FREQ_100HZ = 10,
	HAL_TICK_FREQ_1KHZ = 1,
	HAL_TICK_FREQ_DEFAULT = HAL_TICK_FREQ_1KHZ
}HAL_TickFreqTypeDef;


int HAL_SystickInit(void);
void HAL_IncTick(void);
uint32_t HAL_GetTick(void);
void HAL_DelayMs(uint32_t delayTime);
int HAL_SetSystickFreq(HAL_TickFreqTypeDef freq);
HAL_TickFreqTypeDef HAL_GetSystickFreq(void);
void HAL_SuspendSystick(void);
void HAL_ResumeSystick(void);


void delay_ms(uint32_t nms);
void delay_us(uint32_t nus);


#ifdef __cplusplus
}
#endif
#endif /* HALDRIVERS_SYSTICK_H_ */

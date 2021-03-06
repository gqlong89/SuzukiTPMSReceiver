/*
 * SKEAxxx_it.h
 *
 *  Created on: Jan 19, 2019
 *      Author: wj1080
 */

#ifndef SKEAXXX_IT_H_
#define SKEAXXX_IT_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "derivative.h"


void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);

void SysTick_Handler(void);
void PIT_CH0_IRQHandler(void);
void PIT_CH1_IRQHandler(void);
void KBI0_IRQHandler(void);
void KBI1_IRQHandler(void);

#ifdef __cplusplus
}
#endif
#endif /* SKEAXXX_IT_H_ */

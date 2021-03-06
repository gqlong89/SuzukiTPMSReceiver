/*
 * fsm.h
 *
 *  Created on: Jan 13, 2019
 *      Author: wj1080
 */

#ifndef FSM_H_
#define FSM_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "derivative.h"


typedef enum
{
	Init = 1,
	Sleep,
	Query,
	Running,
	Learning,
	Normal,
}systemFiniteStateMachineTypeDef_t;


void configureSystemFsmValue(systemFiniteStateMachineTypeDef_t val);
systemFiniteStateMachineTypeDef_t getSystemFsmValue(void);

#ifdef __cplusplus
}
#endif
#endif /* FSM_H_ */

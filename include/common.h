/*
 * common.h
 *
 *  Created on: Jan 19, 2019
 *      Author: wj1080
 */

#ifndef COMMON_H_
#define COMMON_H_

#ifdef __cplusplus
 extern "C" {
#endif

 /* Includes ------------------------------------------------------------------*/
 #include <stdint.h>
 #include <stdlib.h>
 #include <stddef.h>
 #include <string.h>
 #include "derivative.h"


#if !defined(ARRAY_SIZE)
	#define  ARRAY_SIZE(x)		(sizeof(x) / sizeof((x)[0]))
#endif


#if (defined(FreeRTOS))
	#define  SUSPEND_INTERRUPT()	portENTER_CRITICAL()
	#define  RESUME_INTERRUPT()		portEXIT_CRITICAL()
#else
	#define  SUSPEND_INTERRUPT()	__disable_irq()
	#define  RESUME_INTERRUPT()		__enable_irq()
#endif


#define  SYSTEM_BUSCLOCK_HZ		(SystemCoreClock / 2)


 typedef enum
 {
 	FlagRESET = 0,
 	FlagSET = !FlagRESET,
 }FlagStatus;


 typedef struct
 {
 	void*    addr;
 	uint32_t mask;
 	uint32_t shift;
 }RegisterVarDef_t;


 void suspendSystemInterrupt(void);
 void resumeSystemInterrupt(void);


#ifdef __cplusplus
}
#endif
#endif /* COMMON_H_ */

/*
 * delayus.h
 *
 *  Created on: Jan 16, 2019
 *      Author: wj1080
 */

#ifndef DELAYUS_H_
#define DELAYUS_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "derivative.h"
#include "pit.h"


 void systemDelayUsInit(void);
 void systemDelayUs(uint16_t delayTimeUs);


#ifdef __cplusplus
}
#endif
#endif /* MDL_DELAYUS_H_ */

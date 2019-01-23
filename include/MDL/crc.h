/*
 * crc.h
 *
 *  Created on: Jan 22, 2019
 *      Author: wj1080
 */

#ifndef CRC_H_
#define CRC_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "derivative.h"


 uint8_t CRC8_Calc(uint8_t* u8Buffer, uint8_t u8SizeInBytes, uint8_t u8Remainder, uint8_t u8Poly);


#ifdef __cplusplus
}
#endif
#endif /* MDL_CRC_H_ */

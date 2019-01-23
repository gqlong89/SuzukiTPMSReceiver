/*
 * crc.c
 *
 *  Created on: Jan 22, 2019
 *      Author: wj1080
 */


#include "crc.h"


/**
  * @brief
  * @param
  * @retval
  */
uint8_t CRC8_Calc(uint8_t* u8Buffer, uint8_t u8SizeInBytes, uint8_t u8Remainder, uint8_t u8Poly)
{
	uint8_t i, j, temp;

	for(i = 0; i < u8SizeInBytes; i++)
	{
		temp = u8Buffer[i];

		for(j = 8; j != 0; j --)
		{
			if((u8Remainder & 0x80) != 0)
			{
				u8Remainder = (u8Remainder << 1) ^ u8Poly;
			}
			else
			{
				u8Remainder = u8Remainder << 1;
			}

			if((temp & 0x80) != 0)
			{
				u8Remainder = u8Remainder ^ u8Poly;
			}

			temp = temp << 1;
		}
	}

    return(u8Remainder);
}


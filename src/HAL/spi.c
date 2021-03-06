/*
 * spi.c
 *
 *  Created on: Jan 13, 2019
 *      Author: wj1080
 */

#include "spi.h"
#include "delayUs.h"



/* �½��ط���,�����ض�ȡ. */

/**
  * @brief  Serial comm delay. This function is only used in current project file.
  * @param  delayCnt, delay count time.
  * @retval None.
  */
static void serialCommDelay(uint16_t delayCnt)
{
	uint16_t i;

	for (i = 0; i < delayCnt; i++)
	{
		__NOP();
		__NOP();
		__NOP();
		__NOP();
		__NOP();
		__NOP();
		__NOP();
		__NOP();
	}
}

/**
  * @brief  Initializes SPI port which communicate with RF chip.
  * @param  None.
  * @retval None.
  */
void HAL_SpiCommPortsInit(void)
{
	RF_CS_High();
	GPIO_PinInit(RF_CS_Pin, GPIO_PinOutput);
	RF_CS_High();

	RF_SCK_High();
	GPIO_PinInit(RF_SCK_Pin, GPIO_PinOutput);
	RF_SCK_High();

	RF_MOSI_High();
	GPIO_PinInit(RF_MOSI_Pin, GPIO_PinOutput);
	RF_MOSI_High();

	GPIO_PinInit(RF_MISO_Pin, GPIO_PinInput);
}

/**
  * @brief  send specified length of data through SPI port.
  * @param  *wData, data buffer which will be sent;
  * @param  size, the sent data size;
  * @retval None.
  */
void HAL_SpiWriteOneByteData(uint8_t wData)
{
	uint8_t i;

	for (i = 0; i < 8; i++)
	{
		if (wData & 0x80)
		{
			RF_MOSI_High();
		}
		else
		{
			RF_MOSI_Low();
		}

		wData <<= 1;

		serialCommDelay(8);

		RF_SCK_Low();

		serialCommDelay(8);

		RF_SCK_High();
	}
}

/**
  * @brief  Read out one byte data through SPI port.
  * @param  None.
  * @retval Read out one byte data.
  */
uint8_t HAL_SpiReadOneByteData(void)
{
	uint8_t i, retVal = 0;

	for (i = 0; i < 8; i++)
	{
		RF_SCK_Low();

		serialCommDelay(8);

		RF_SCK_High();

		serialCommDelay(8);

		if (RF_MISO_Read() != 0)
		{
			retVal = (retVal << 1) | 0x01;
		}
		else
		{
			retVal = (retVal << 1);
		}
	}

	return (retVal);
}




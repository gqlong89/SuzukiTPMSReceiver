/*
 * inputKeys.c
 *
 *  Created on: Jan 14, 2019
 *      Author: wj1080
 */

#include "inputKeys.h"
#include "common.h"


static KEYPropertyDef_t keysPara[KEY_COUNT];
static KEYFIFOTypeDef_t keysFifo;
static volatile uint8_t scanCount = 0;



/**
  * @brief  Determine whethere the SET button is pressed.
  * @param  None.
  * @retval 0,not pressed; 1,pressed;
  */
static uint8_t IsSetKeyDown(void)
{
	if (GPIO_PinRead(GPIO_PIN_SETKEY) != 0)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
  * @brief  Determine whethere the FLIP button is pressed.
  * @param  None.
  * @retval 0,not pressed; 1,pressed;
  */
static uint8_t IsFlipKeyDown(void)
{
	if (GPIO_PinRead(GPIO_PIN_FLIPKEY) != 0)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
  * @brief  Determine whethere the FLIP button is pressed.
  * @param  None.
  * @retval None.
  */
static void InitKeysVar(void)
{
	uint8_t i;

	keysFifo.writePtr = 0;
	keysFifo.readPtr  = 0;

	for (i = 0; i < KEY_FIFO_SIZE; i++)
	{
		keysFifo.buffer[i] = KEY_NONE;
	}

	for (i = 0; i < KEY_COUNT; i++)
	{
		keysPara[i].longCount = 0;
		keysPara[i].longTime  = KEY_LONG_TIME;		/* If this member of the struct is clear to 0,it means do not detect long press event. */
		keysPara[i].count     = KEY_FILTER_TIME / 2;
		keysPara[i].state     = 0;					/* 0,there is no press event by default. */
	}

	keysPara[KID_SET].IsKeyDownFunc  = IsSetKeyDown;
	keysPara[KID_FLIP].IsKeyDownFunc = IsFlipKeyDown;
}

/**
  * @brief  Determine whethere the FLIP button is pressed.
  * @param  None.
  * @retval None.
  */
static void initKeysHard(void)
{
	GPIO_PinInit(GPIO_PIN_SETKEY, GPIO_PinInput_InternalPullup);
	GPIO_PinInit(GPIO_PIN_FLIPKEY, GPIO_PinInput_InternalPullup);
}

/**
  * @brief  Determine whethere the FLIP button is pressed.
  * @param  None.
  * @retval None.
  */
void inputKeysInit(void)
{
	InitKeysVar();
	initKeysHard();
}

/**
  * @brief  Determine whethere the FLIP button is pressed.
  * @param  None.
  * @retval None.
  */
void inputKeysPutEvent(uint8_t keyCode)
{
	keysFifo.buffer[keysFifo.writePtr] = keyCode;

	if (++keysFifo.writePtr >= KEY_FIFO_SIZE)
	{
		keysFifo.writePtr = 0;
	}
}

/**
  * @brief  Determine whethere the FLIP button is pressed.
  * @param  None.
  * @retval None.
  */
uint8_t inputKeysGetEvent(void)
{
	uint8_t ret;

	if (keysFifo.readPtr == keysFifo.writePtr)
	{
		return (KEY_NONE);
	}
	else
	{
		SUSPEND_INTERRUPT();
		ret = keysFifo.buffer[keysFifo.readPtr];
		keysFifo.buffer[keysFifo.readPtr] = (uint8_t)KEY_NONE;
		RESUME_INTERRUPT();

		if (++keysFifo.readPtr >= KEY_FIFO_SIZE)
		{
			keysFifo.readPtr = 0;
		}

		return (ret);
	}
}

/**
  * @brief  Determine whethere the FLIP button is pressed.
  * @param  None.
  * @retval None.
  */
static void inputKeysEventDetect(uint8_t idx)
{
	KEYPropertyDef_t* pKeyPro = &keysPara[idx];

	if (pKeyPro->IsKeyDownFunc()) 						/* There is input key press event occurred. */
	{
		if (pKeyPro->count < KEY_FILTER_TIME)
		{
			pKeyPro->count = KEY_FILTER_TIME;
		}
		else if (pKeyPro->count < (2 * KEY_FILTER_TIME))
		{
			pKeyPro->count++;
		}
		else
		{
			if (pKeyPro->state == 0)
			{
				pKeyPro->state = 1;

				inputKeysPutEvent((uint8_t)(3*idx + 1));
			}

			if (pKeyPro->longTime > 0)								/* If longTime is not clear to 0,user should detect long press event. */
			{
				if (pKeyPro->longCount < pKeyPro->longTime)
				{
					pKeyPro->longCount++;

					if (pKeyPro->longCount == pKeyPro->longTime)
					{
						inputKeysPutEvent((uint8_t)(3*idx + 3));	/* Long press event was occurred. */
					}
				}
			}
		}
	}
	else															/* There is no input key press event occurred. */
	{
		if (pKeyPro->count > KEY_FILTER_TIME)
		{
			pKeyPro->count = KEY_FILTER_TIME;
		}
		else if (pKeyPro->count != 0)
		{
			pKeyPro->count--;
		}
		else
		{
			if (pKeyPro->state == 1)
			{
				pKeyPro->state = 0;

				inputKeysPutEvent((uint8_t)(3*idx + 2));
			}
		}

		pKeyPro->longCount = 0;
	}
}

/**
  * @brief  Determine whethere the FLIP button is pressed.
  * @param  None.
  * @retval None.
  */
void inputKeysScanning(void)
{
	const uint8_t PERIOD = 10;
	uint8_t i;

	if (++scanCount >= PERIOD)					/* 1ms * 10 = 10ms. */
	{
		scanCount = 0;

		for (i = 0; i < KEY_COUNT; i++)
		{
			inputKeysEventDetect(i);
		}
	}
}


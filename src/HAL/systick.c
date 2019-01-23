/*
 * systick.c
 *
 *  Created on: Jan 12, 2019
 *      Author: wj1080
 */


#include "systick.h"
#include "system_SKEAZ1284.h"



static volatile uint32_t uwTickCount = 0;
static HAL_TickFreqTypeDef uwTickFreq = HAL_TICK_FREQ_DEFAULT;



/**
  * @brief  Initializes the System Timer and its interrupt, and starts the System Tick Timer.
  *         Counter is in free running mode to generate periodic interrupts.
  * @param  None.
  * @retval 0,success; -1,failure;
  */
int HAL_SystickInit(void)
{
	uint32_t ticks, tickPriority;

	ticks = SystemCoreClock / (1000 / uwTickFreq);

	if (SysTick_Config(ticks) == 0)
	{
		tickPriority = SYSTICK_INT_PRIORITY;

		if (tickPriority < (1 << __NVIC_PRIO_BITS))
		{
			NVIC_SetPriority(SysTick_IRQn, tickPriority);
			NVIC_EnableIRQ(SysTick_IRQn);

			return (0);
		}
		else
		{
			return (-1);
		}
	}
	else
	{
		return (-1);
	}
}

/**
  * @brief This function is called to increment  a global variable "uwTick"
  *        used as application time base.
  * @note In the default implementation, this variable is incremented each 1ms
  *       in SysTick ISR.
  * @note This function is declared as __weak to be overwritten in case of other
  *      implementations in user file.
  * @retval None
  */
void HAL_IncTick(void)
{
	uwTickCount += uwTickFreq;

	if (uwTickCount >= 0xFFFFFFFFU)
	{
		uwTickCount = 0;
	}
}

/**
  * @brief Provides a tick value in millisecond.
  * @note  This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @retval tick value
  */
uint32_t HAL_GetTick(void)
{
	return (uwTickCount);
}

/**
  * @brief This function provides minimum delay (in milliseconds) based
  *        on variable incremented.
  * @note In the default implementation , SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals where uwTick
  *       is incremented.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @param Delay specifies the delay time length, in milliseconds.
  * @retval None
  */
void HAL_DelayMs(uint32_t delayTime)
{
	uint32_t tickStart = HAL_GetTick();
	uint32_t wait = delayTime;

	if (wait == 0)
	{
		return;
	}

	while ((HAL_GetTick() - tickStart) < wait)
	{;}
}

/**
  * @brief Set new tick Freq.
  * @retval Status
  */
int HAL_SetSystickFreq(HAL_TickFreqTypeDef freq)
{
	int ret = -1;

	if (uwTickFreq != freq)
	{
		uwTickFreq = freq;

		ret = HAL_SystickInit();
	}

	return (ret);
}

/**
  * @brief Return tick frequency.
  * @retval tick period in Hz
  */
HAL_TickFreqTypeDef HAL_GetSystickFreq(void)
{
	return (uwTickFreq);
}

/**
  * @brief Suspend Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once HAL_SuspendTick()
  *       is called, the SysTick interrupt will be disabled and so Tick increment
  *       is suspended.
  * @retval None
  */
void HAL_SuspendSystick(void)
{
	SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
}

/**
  * @brief Resume Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once HAL_ResumeTick()
  *       is called, the SysTick interrupt will be enabled and so Tick increment
  *       is resumed.
  * @retval None
  */
void HAL_ResumeSystick(void)
{
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
}

#if 0
void delay_ms(uint32_t nms)
{
	uint32_t temp = (nms * 40 * 1000)&0x00ffffff;

	SysTick->LOAD = temp;
	SysTick->VAL  = 0;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	do
	{
		temp = SysTick->CTRL;
	}
	while (!(temp & (1 << 16)));

	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

	SysTick->VAL  = 0;
}

void delay_us(uint32_t nus)
{
	uint32_t temp = nus * 40;

	SysTick->LOAD = temp;
	SysTick->VAL  = 0;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	do
	{
		temp = SysTick->CTRL;
	}
	while (!(temp & (1 << 16)));

	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

	SysTick->VAL  = 0;
}
#endif



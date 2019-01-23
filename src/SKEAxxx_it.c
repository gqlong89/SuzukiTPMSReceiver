/*
 * SKEAZxx_it.c
 *
 *  Created on: Jan 12, 2019
 *      Author: wj1080
 */


#include "SKEAxxx_it.h"
#include "systick.h"
#include "pit.h"
#include "kbi.h"
#include "gpio.h"
#include "inputKeys.h"
#include "acc.h"
#include "led.h"
#include "tda5235.h"


/**
* @brief This function handles Non maskable interrupt.
* @param  None.
* @retval None.
*/
void NMI_Handler(void)
{
	while (1)
	{
	/* USER CODE BEGIN NonMaskableInt_IRQn  */
	/* USER CODE END NonMaskableInt_IRQn  */
	}
}

/**
* @brief This function handles Hard fault interrupt.
* @param  None.
* @retval None.
*/
void HardFault_Handler(void)
{
	/* USER CODE BEGIN HardFault_IRQn 0 */

	/* USER CODE END HardFault_IRQn 0 */
	while (1)
	{
	/* USER CODE BEGIN W1_HardFault_IRQn 0 */
	/* USER CODE END W1_HardFault_IRQn 0 */
	}
	/* USER CODE BEGIN HardFault_IRQn 1 */

	/* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles System service call via SWI instruction.
* @param  None.
* @retval None.
*/
void SVC_Handler(void)
{
	while (1)
	{
	/* USER CODE BEGIN SVCall_IRQn 0 */
	/* USER CODE END SVCall_IRQn 0 */
	}
}

/**
* @brief This function handles Pendable request for system service.
* @param  None.
* @retval None.
*/
void PendSV_Handler(void)
{
	while (1)
	{
	/* USER CODE BEGIN PendSV_IRQn */
	/* USER CODE END PendSV_IRQn */
	}
}

/**
* @brief This function is systick ISR routine,handles System tick timer.
* @param  None.
* @retval None.
*/
void SysTick_Handler(void)
{
	HAL_IncTick();
	inputKeysScanning();
	systemAccSignalScanCallback();
}

/**
* @brief This function is systick ISR routine,handles System tick timer.
* @param  None.
* @retval None.
*/
void PIT_CH0_IRQHandler(void)
{
	if (PIT_ChannelGetFlags(PIT_CHANNEL0) != 0)
	{
		PIT_ChannelClrFlags(PIT_CHANNEL0);

		/* TODO: Add code here to do... */
	}
}

/**
* @brief This function is systick ISR routine,handles System tick timer.
* @param  None.
* @retval None.
*/
void PIT_CH1_IRQHandler(void)
{
	if (PIT_ChannelGetFlags(PIT_CHANNEL1) != 0)
	{
		PIT_ChannelClrFlags(PIT_CHANNEL1);

		/* TODO: Add code here to do... */
	}
}

/**
* @brief This function is systick ISR routine,handles System tick timer.
* @param  None.
* @retval None.
*/
void KBI0_IRQHandler(void)
{
	if (KBI_GetFlags(KBI0) != 0)
	{
		KBI_ClrFlags(KBI0);

#if defined(CPU_KEA128)
		uint32_t spVal;

		spVal = KBI_GetSP(KBI0);

		if (spVal & ((uint32_t)(1 << ACC_SIGNAL_Piny)))
		{
			KBI_RstSP(KBI0);

			systemAccSignalTriggerINTCallback();
		}
#else
		systemAccSignalTriggerINTCallback();
#endif
	}
}

/**
* @brief This function is systick ISR routine,handles System tick timer.
* @param  None.
* @retval None.
*/
void KBI1_IRQHandler(void)
{
	if (KBI_GetFlags(KBI1) != 0)
	{
		KBI_ClrFlags(KBI1);

#if defined(CPU_KEA128)
		uint32_t spVal;

		spVal = KBI_GetSP(KBI1);

		if (spVal & ((uint32_t)(1 << TDA5235_WAKEUP_Piny)))
		{
			KBI_RstSP(KBI1);

			configSensorParaRxTriggerFlag(FlagSET);
		}
#endif
	}
}

/**
* @brief This function is systick ISR routine,handles System tick timer.
* @param  None.
* @retval None.
*/
void FTM0_IRQHandler(void)
{
	if (FTM0->SC & FTM_SC_TOF_MASK)
	{
		FTM0->SC &= ~FTM_SC_TOF_MASK;

		/* TODO: Add code here to do... */
	}
}

/**
* @brief This function is UART0 ISR routine.
* @param  None.
* @retval None.
*/
void UART0_IRQHandler(void)
{
	/* TODO: Add code here to do... */
}

/**
* @brief This function is UART1 ISR routine.
* @param  None.
* @retval None.
*/
void UART1_IRQHandler(void)
{
	/* TODO: Add code here to do... */
}

/**
* @brief This function is UART2 ISR routine.
* @param  None.
* @retval None.
*/
void UART2_IRQHandler(void)
{
	/* TODO: Add code here to do... */
}

/*
 * fsm.c
 *
 *  Created on: Jan 13, 2019
 *      Author: wj1080
 */

#include "fsm.h"
#include "common.h"


static systemFiniteStateMachineTypeDef_t systemFsmValue = Init;


/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void configureSystemFsmValue(systemFiniteStateMachineTypeDef_t val)
{
	SUSPEND_INTERRUPT();
	systemFsmValue = val;
	RESUME_INTERRUPT();
}

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
systemFiniteStateMachineTypeDef_t getSystemFsmValue(void)
{
	return (systemFsmValue);
}


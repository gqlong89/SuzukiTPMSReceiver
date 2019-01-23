/*
 * main implementation: use this 'C' sample to create your own application
 *
 */


#include "derivative.h" /* include peripheral declarations SSKEAZ128M4 */
#include "init.h"
#include "fsm.h"
#include "sleep.h"
#include "running.h"
#include "learning.h"
#include "normal.h"
#include "query.h"


/**
  * @brief  System main function after excute startup code.
  * @param  None.
  * @retval None.
  */
int main(void)
{
	systemFiniteStateMachineTypeDef_t curFsm;

	systemInit();

	while (1)
	{
		curFsm = getSystemFsmValue();

		switch (curFsm)
		{
			case Sleep:
			{
				systemSleepStateProcess();
			}break;

			case Running:
			{
				systemRunningStateProcess();
			}break;

			case Learning:
			{
				systemLearningStateProcess();
			}break;

			case Normal:
			{
				systemNormalStateProcess();
			}break;

			case Query:
			{
				systemQueryStateProcess();
			}break;

			default:break;
		}
	}
}

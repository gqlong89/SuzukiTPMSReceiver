/*
 * query.c
 *
 *  Created on: Jan 14, 2019
 *      Author: wj1080
 */

#include "query.h"
#include "acc.h"
#include "fsm.h"



/**
  * @函数功能   系统处于查询态的任务处理.
  * @函数参数  	无.
  * @函数返回值	 无.
  */
void systemQueryStateProcess(void)
{
	ACCSignalStateDef_t accStat = ACC_INVALID;

	accStat = systemAccSignalDetect();

	if (accStat == ACC_INVALID)
	{
		configureSystemFsmValue(Sleep);						/* ACC钥匙信号无效,再次进入休眠态. */
	}
	else
	{
		configureSystemFsmValue(Running);					/* ACC钥匙信号有效,直接进入运行态. */
	}
}


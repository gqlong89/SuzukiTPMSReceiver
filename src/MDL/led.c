/*
 * led.c
 *
 *  Created on: Jan 15, 2019
 *      Author: wj1080
 */


#include "led.h"


/**
  * @函数功能    LED指示灯初始化.默认熄灭LED指示灯.该函数用于在上电复位后调用一次.
  * @函数参数  	无.
  * @函数返回值	 无.
  */
void ledLightInit(void)
{
	GPIO_PinInit(LEDLIGHT_GPIO_Pin, GPIO_PinOutput);
	GPIO_PinSet(LEDLIGHT_GPIO_Pin);
}

/**
  * @函数功能    LED指示灯点亮.
  * @函数参数  	无.
  * @函数返回值	 无.
  */
void ledLightOn(void)
{
	GPIO_PinClear(LEDLIGHT_GPIO_Pin);
}

/**
  * @函数功能    LED指示灯熄灭.
  * @函数参数  	无.
  * @函数返回值	 无.
  */
void ledLightOff(void)
{
	GPIO_PinSet(LEDLIGHT_GPIO_Pin);
}

/**
  * @函数功能    LED指示灯反转.
  * @函数参数  	无.
  * @函数返回值	 无.
  */
void ledLightToggle(void)
{
	GPIO_PinToggle(LEDLIGHT_GPIO_Pin);
}

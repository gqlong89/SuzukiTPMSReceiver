/*
 * ht162x.h
 *
 *  Created on: Jan 14, 2019
 *      Author: wj1080
 */

#ifndef HT162X_H_
#define HT162X_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "derivative.h"
#include "gpio.h"



#define  HT162X_CS_GPIO_Pin		GPIO_PTA2
#define  HT162X_RD_GPIO_Pin		GPIO_PTA3
#define  HT162X_WR_GPIO_Pin		GPIO_PTD2
#define  HT162X_DATA_GPIO_Pin	GPIO_PTD3


#define  configHT162X_CSPinOutput()		GPIO_PinInit(HT162X_CS_GPIO_Pin, GPIO_PinOutput)
#define  HT162X_CSPin_OutputHigh()		GPIO_PinSet(HT162X_CS_GPIO_Pin)
#define  HT162X_CSPin_OutputLow()		GPIO_PinClear(HT162X_CS_GPIO_Pin)

#define  configHT162X_RDPinOutput()		GPIO_PinInit(HT162X_RD_GPIO_Pin, GPIO_PinOutput)
#define  HT162X_RDPin_OutputHigh()		GPIO_PinSet(HT162X_RD_GPIO_Pin)
#define  HT162X_RDPin_OutputLow()		GPIO_PinClear(HT162X_RD_GPIO_Pin)

#define  configHT612X_WRPinOutput()		GPIO_PinInit(HT162X_WR_GPIO_Pin, GPIO_PinOutput)
#define  HT162X_WRPin_OutputHigh()		GPIO_PinSet(HT162X_WR_GPIO_Pin)
#define  HT162X_WRPin_OutputLow()		GPIO_PinClear(HT162X_WR_GPIO_Pin)

#define  configHT162X_DATAPinOutput()	GPIO_PinInit(HT162X_DATA_GPIO_Pin, GPIO_PinOutput)
#define  HT162X_DATAPin_OutputHigh()	GPIO_PinSet(HT162X_DATA_GPIO_Pin)
#define  HT162X_DATAPin_OutputLow()		GPIO_PinClear(HT162X_DATA_GPIO_Pin)
#define  configHT162X_DATAPinInput()	GPIO_PinInit(HT162X_DATA_GPIO_Pin, GPIO_PinInput)
#define  HT162X_DATAPin_InputRead()		GPIO_PinRead(HT162X_DATA_GPIO_Pin)


#define  SYS_DIS		0x00			/* 关闭系统振荡器和LCD偏置发生器. */
#define  SYS_EN			0x01			/* 打开系统振荡器. */
#define  LCD_OFF		0x02			/* 关闭LCD显示. */
#define  LCD_ON			0x03			/* 打开LCD显示. */
#define  TIMER_DIS		0x04			/* 禁止时基输出. */
#define  WDT_DIS		0x05			/* 禁止WDT超时标志输出. */
#define  TIMER_EN		0x06			/* 启用时基输出. */
#define	 WDT_EN			0x07			/* 启用WDT超时标志输出. */
#define  TONE_OFF		0x08			/* 关闭声音输出. */
#define  CLR_TIMER		0x0D			/* 清除时基发生器的内容. */
#define	 CLR_WDT		0x0F			/* 清除WDT的内容. */
#define  RC_32K			0x18			/* 系统时钟源,片上RC32K时钟. */
#define  EXT_32K		0x1C			/* 系统时钟源,外部32K时钟. */
#define  TONE_4K		0x40			/* 声音输出频率:4KHZ. */
#define  TONE_2K		0x60			/* 声音输出频率:2KHZ. */
#define  IRQ_DIS		0x80			/* 禁止IRQ输出. */
#define  IRQ_EN			0x88			/* 启用IRQ输出. */
#define  F1				0xA0			/* 时钟时基输出：1HZ,WDT超时时间：4S. */
#define  F2				0xA1			/* 时钟时基输出：2HZ,WDT超时时间：2S. */
#define  F4				0xA2			/* 时钟时基输出：4HZ,WDT超时时间：1S. */
#define  F8				0xA3			/* 时钟时基输出：8HZ,WDT超时时间：1/2S. */
#define  F16			0xA4			/* 时钟时基输出：16HZ,WDT超时时间：1/4S. */
#define  F32			0xA5			/* 时钟时基输出：32HZ,WDT超时时间：1/8S. */
#define  F64			0xA6			/* 时钟时基输出：64HZ,WDT超时时间：1/16S. */
#define  F128			0xA7			/* 时钟时基输出：128HZ,WDT超时时间：1/32S. */
#define  TEST			0xE0			/* 测试模式,用户不使用. */
#define  NORMAL			0xE3			/* 普通模式. */


#define  READ_OPERATION_ID					(0xC0)
#define  WRITE_OPERATION_ID					(0xA0)
#define  READ_MODIFY_WRITE_OPERATION_ID		(0xA0)
#define  COMMAND_OPERATION_ID				(0x80)



int ht162xWriteDataBitsMSB(uint8_t wData, uint8_t wBitSize);
int ht162xWriteDataBitsLSB(uint8_t wData, uint8_t wBitSize);
void ht162xWriteCommand(uint8_t cmdData);
void ht162xInit(void);
void ht162xWriteHalfByteData(uint8_t addr, uint8_t wData);
void ht162xWriteOneByteData(uint8_t segAddr, uint8_t wtData);
void ht162xWriteSuccessiveBytesData(uint8_t segAddr, uint8_t segCount, uint8_t* pWdat);


#ifdef __cplusplus
}
#endif
#endif /* DDL_HT162X_H_ */

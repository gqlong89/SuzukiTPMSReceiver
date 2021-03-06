/*
 * console.c
 *
 *  Created on: Jan 19, 2019
 *      Author: wj1080
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "console.h"
#include "uart.h"



int_t __read_console(__file_handle handle, uchar_t* buffer, size_t* count)
{
//	uint32_t bytesRemain;
	bool MsgDone = false;
	uchar_t new_lin[]={"\n"};
	int i = 0;
	while (MsgDone == false)
	{
		UART_ReceiveWait(UART0, (uint8_t*)&buffer[i], 1);
//		LPUART_DRV_ReceiveData(INST_LPUART1, &buffer[i], 1);
//		while(LPUART_DRV_GetReceiveStatus(INST_LPUART1, &bytesRemain) != STATUS_SUCCESS);
//		LPUART_DRV_SendData(INST_LPUART1, &buffer[i], 1);
//		while(LPUART_DRV_GetTransmitStatus(INST_LPUART1, &bytesRemain) != STATUS_SUCCESS);
		UART_SendWait(UART0, (uint8_t*)&buffer[i], 1);
		if(buffer[i++] == '\r')
		{
		   buffer[i-1] = '\n';
		   MsgDone = true;
		}
	}
//	LPUART_DRV_SendData(INST_LPUART1, new_lin, 1);
//	while(LPUART_DRV_GetTransmitStatus(INST_LPUART1, &bytesRemain) != STATUS_SUCCESS);
	UART_SendWait(UART0, (uint8_t*)new_lin, 1);
	buffer[i]=0;
	*count = (size_t)i;
	return 0;
}


int_t __write_console(__file_handle handle, uchar_t * buffer, size_t * count)
{
//	uint32_t bytesRemain;
	size_t bytes = *count;
//	LPUART_DRV_SendData(INST_LPUART1, buffer, bytes);
//	while(LPUART_DRV_GetTransmitStatus(INST_LPUART1, &bytesRemain) != STATUS_SUCCESS);
	UART_SendWait(UART0, (uint8_t*)buffer, (uint32_t)bytes);
	return 0;
}


int_t __close_console(__file_handle handle)
{
	return 0;
}


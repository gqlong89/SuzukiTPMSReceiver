/*
 * uart.c
 *
 *  Created on: Jan 19, 2019
 *      Author: wj1080
 */

#include "uart.h"



/*****************************************************************************//*!
*
* @brief initialize the UART, interrupts disabled, and no hardware flow-control.
*
* @param[in] pUART       base of UART port
* @param[in] pConfig     pointer to UART configuration structure
*
* @return none
*
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
void UART_Init(UART_MemMapPtr pUART, UART_ConfigType *pConfig)
{
    uint16_t u16Sbr;
    uint8_t u8Temp;
    uint32_t u32SysClk = pConfig->u32SysClkHz;
    uint32_t u32Baud = pConfig->u32Baudrate;

	/* Enable the clock to the selected UART */
    if (pUART == UART0_BASE_PTR)
	{
    	SIM_BASE_PTR->PINSEL &= ~SIM_PINSEL_UART0PS_MASK;
    	SIM_BASE_PTR->SCGC |= SIM_SCGC_UART0_MASK;
	}
    if (pUART == UART1_BASE_PTR)
   	{
       	SIM_BASE_PTR->SCGC |= SIM_SCGC_UART1_MASK;
   	}
    if (pUART == UART2_BASE_PTR)
    {
        SIM_BASE_PTR->SCGC |= SIM_SCGC_UART2_MASK;
    }

    /* Make sure that the transmitter and receiver are disabled while we
     * change settings.
     */
    pUART->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK );

    /* Configure the UART for 8-bit mode, no parity */
    pUART->C1 = pConfig->sctrl1settings.byte;

    /* Calculate baud settings */
    u16Sbr = (((u32SysClk)>>4) + (u32Baud>>1))/u32Baud;

    /* Save off the current value of the UARTx_BDH except for the SBR field */
    u8Temp = pUART->BDH & ~(UART_BDH_SBR_MASK);

    pUART->BDH = u8Temp |  UART_BDH_SBR(u16Sbr >> 8);
    pUART->BDL = (uint8_t)(u16Sbr & UART_BDL_SBR_MASK);

    if(1 == pConfig->bSbns)
    {
    	UART_Set2StopBit(pUART);
    }
    else
    {
    	UART_Set1StopBit(pUART);
    }

    pUART->C3 = pConfig->sctrl3settings.byte;
  	pUART->C2 = pConfig->sctrl2settings.byte;

    if((1 == pConfig->sctrl2settings.bits.bIlie) || \
       (1 == pConfig->sctrl2settings.bits.bRie)  || \
	   (1 == pConfig->sctrl2settings.bits.bTcie) || \
	   (1 == pConfig->sctrl2settings.bits.bTie)  || \
	   (1 == pConfig->sctrl3settings.bits.bFeie) || \
	   (1 == pConfig->sctrl3settings.bits.bNeie) || \
	   (1 == pConfig->sctrl3settings.bits.bOrie) || \
	   (1 == pConfig->sctrl3settings.bits.bPeie))
    {
    	if(pUART == UART0)
    	{
    		NVIC_EnableIRQ(UART0_IRQn);
    	}
    	if(pUART == UART1)
    	{
    		NVIC_EnableIRQ(UART1_IRQn);
    	}
    	if(pUART == UART2)
    	{
    		NVIC_EnableIRQ(UART2_IRQn);
    	}
    }
}

/*****************************************************************************//*!
*
* @brief receive a character.
*
* @param[in] pUART       base of UART port
*
* @return unsigned char
*
*****************************************************************************/
uint8_t UART_GetChar(UART_MemMapPtr pUART)
{
    /* Wait until character has been received */
    while (!(pUART->S1 & UART_S1_RDRF_MASK));

    /* Return the 8-bit data from the receiver */
    return pUART->D;
}
/*****************************************************************************//*!
*
* @brief send a character.
*
* @param[in] pUART       base of UART port
* @param[in] u8Char      char to send
*
* @return none
*
*****************************************************************************/
void UART_PutChar(UART_MemMapPtr pUART, uint8_t u8Char)
{
    /* Wait until space is available in the FIFO */
    while (!(pUART->S1 & UART_S1_TDRE_MASK));

    /* Send the character */
    pUART->D = (uint8_t)u8Char;
}

/*****************************************************************************//*!
*
* @brief set baudrate.
*
* @param[in] pUART       base of UART port
* @param[in] pConfig     baudrate config parameters
*
* @return none
*
* @ Pass/ Fail criteria:
*****************************************************************************/
void UART_SetBaudrate(UART_MemMapPtr pUART, UART_ConfigBaudrateType *pConfig)
{
    uint8_t u8Temp;
    uint16_t u16Sbr;
    uint32_t u32SysClk    = pConfig->u32SysClkHz;
    uint32_t u32baud       = pConfig->u32Baudrate;

    /* Calculate baud settings */
    u16Sbr = (((u32SysClk)>>4) + (u32baud>>1))/u32baud;

    /* Save off the current value of the UARTx_BDH except for the SBR field */
    u8Temp = pUART->BDH & ~(UART_BDH_SBR_MASK);

    pUART->BDH = u8Temp |  UART_BDH_SBR(u16Sbr >> 8);
    pUART->BDL = (uint8_t)(u16Sbr & UART_BDL_SBR_MASK);

    /* Enable receiver and transmitter */
    pUART->C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK );
}

/*****************************************************************************//*!
*
* @brief disable interrupt.
*
* @param[in] pUART base of UART port
* @param[in] InterruptType interrupt type
*
* @return none
*
* @ Pass/ Fail criteria:
*****************************************************************************/
void UART_DisableInterrupt(UART_MemMapPtr pUART, UART_InterruptType InterruptType)
{
    if (InterruptType == UART_TxBuffEmptyInt)
    {
        pUART->C2 &= (~UART_C2_TIE_MASK);
    }
    else if (InterruptType == UART_TxCompleteInt)
    {
        pUART->C2 &= (~UART_C2_TCIE_MASK);
    }
    else if (InterruptType == UART_RxBuffFullInt)
    {
        pUART->C2 &= (~UART_C2_RIE_MASK);
    }
    else if (InterruptType == UART_IdleLineInt)
    {
        pUART->C2 &= (~UART_C2_ILIE_MASK);
    }
    else if (InterruptType == UART_RxOverrunInt)
    {
        pUART->C3 &= (~UART_C3_ORIE_MASK);
    }
    else if (InterruptType == UART_NoiseErrorInt)
    {
        pUART->C3 &= (~UART_C3_NEIE_MASK);
    }
    else if (InterruptType == UART_FramingErrorInt)
    {
        pUART->C3 &= (~UART_C3_FEIE_MASK);
    }
    else if (InterruptType == UART_ParityErrorInt)
    {
        pUART->C3 &= (~UART_C3_FEIE_MASK);
    }
    else
    {
        /* un-supported interrupt type */
    }
}

/*****************************************************************************//*!
*
* @brief get flags from 2 UART status registers.
*
* @param[in] pUART  base of UART port
*
* @return       16-bit flags
*
* @ Pass/ Fail criteria:
*****************************************************************************/
uint16_t UART_GetFlags(UART_MemMapPtr pUART)
{
    uint16_t u16StatusFlags = 0;

    u16StatusFlags = pUART->S2;
    u16StatusFlags = (u16StatusFlags<<8)| pUART->S1;

    return u16StatusFlags;
}

/*****************************************************************************//*!
*
* @brief check whether the specified flag is set.
*
* @param[in] pUART      base of UART port
* @param[in] FlagType   flag type
*
* @return
*               1, flag is set
*               0, flag is clear
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
uint8_t UART_CheckFlag(UART_MemMapPtr pUART, UART_FlagType FlagType)
{
    uint16_t u16StatusFlags = 0;

    u16StatusFlags = UART_GetFlags(pUART);

    return (u16StatusFlags & (1<<FlagType));
}

/*****************************************************************************//*!
*
* @brief send a series of charecters using polling mode.
*
* @param[in] pUART      base of UART port
* @param[in] pSendBuff  pointer of charecters to send
* @param[in] u32Length  number of charecters
*
* @return       none
*
* @ Pass/ Fail criteria:
*****************************************************************************/
void UART_SendWait(UART_MemMapPtr pUART, uint8_t *pSendBuff, uint32_t u32Length)
{
    uint8_t u8TxChar;
    uint32_t  i;

    for (i = 0; i < u32Length; i++)
    {
        u8TxChar = pSendBuff[i];
        while (!UART_IsTxBuffEmpty(pUART))
        {
        	;
        }
        UART_WriteDataReg(pUART, u8TxChar);
    }
}

/*****************************************************************************//*!
*
* @brief receive a series of charecters using polling mode.
*
* @param[in] pUART          base of UART port
* @param[in] pReceiveBuff   pointer of charecters to receive
* @param[in] u32Length      number of charecters
*
* @return       none
*
* @ Pass/ Fail criteria:
*****************************************************************************/
void UART_ReceiveWait(UART_MemMapPtr pUART, uint8_t *pReceiveBuff, uint32_t u32Length)
{
    uint8_t u8RxChar;
    uint32_t i;

    for (i = 0; i < u32Length; i++)
    {
        while (!UART_IsRxBuffFull(pUART))
        {
        	;
        }
        u8RxChar = UART_ReadDataReg(pUART);
        pReceiveBuff[i] = u8RxChar;
    }
}

/*****************************************************************************//*!
*
* @brief wait tx complete.
*
* @param[in] pUART      base of UART port
*
* @return       none
*
* @ Pass/ Fail criteria: none
* *****************************************************************************/
void UART_WaitTxComplete(UART_MemMapPtr pUART)
{
    while (!UART_IsTxComplete(pUART));
}

/*****************************************************************************//*!
*
* @brief wait tx complete.
*
* @param[in] pUART      base of UART port
*
* @return       none
*
* @ Pass/ Fail criteria: none
* *****************************************************************************/
void HAL_UartCommInit(void)
{
	UART_ConfigType uartConfig;

	uartConfig.sctrl1settings.bits.bLoops = 0;
	uartConfig.sctrl1settings.bits.bUartswai = 1;
	uartConfig.sctrl1settings.bits.bM = 0;
	uartConfig.sctrl1settings.bits.bWake = 0;
	uartConfig.sctrl1settings.bits.bIlt = 0;
	uartConfig.sctrl1settings.bits.bPe = 0;

	uartConfig.sctrl2settings.bits.bTie = 0;
	uartConfig.sctrl2settings.bits.bTcie = 0;
	uartConfig.sctrl2settings.bits.bRie = 0;
	uartConfig.sctrl2settings.bits.bIlie = 0;
	uartConfig.sctrl2settings.bits.bTe = 1;
	uartConfig.sctrl2settings.bits.bRe = 1;
	uartConfig.sctrl2settings.bits.bRwu = 0;
	uartConfig.sctrl2settings.bits.bSbk = 0;

	uartConfig.sctrl3settings.byte = 0x00;

	uartConfig.bSbns = 0;
	uartConfig.u32SysClkHz = SystemCoreClock / 2;
	uartConfig.u32Baudrate = 115200;

	UART_Init(UART0, &uartConfig);
}

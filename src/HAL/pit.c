/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2013 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
***************************************************************************//*!
*
* @file     pit.c
*
* @author   Freescale
*
* @version  0.0.1
*
* @date     Jun 25, 2013
*
* @brief    Periodic Interrupt Timer (PIT) source code.
*
******************************************************************************/

#include "pit.h"

/******************************************************************************
* Global variables
******************************************************************************/

/******************************************************************************
* Constants and macros
******************************************************************************/

/******************************************************************************
* Local types
******************************************************************************/

/******************************************************************************
* Local function prototypes
******************************************************************************/

/******************************************************************************
* Local variables
******************************************************************************/
/*!
 * @brief global variable to store PIT callbacks.
 *
 */
#if 0
PIT_CallbackType PIT_Callback[2] = {(PIT_CallbackType)NULL}; /*!< PIT initial callback */
#endif

/******************************************************************************
* Local functions
******************************************************************************/
#if 0
void PIT_Ch0Isr(void);
void PIT_Ch1Isr(void);
#endif


/******************************************************************************
* Global functions
******************************************************************************/

/******************************************************************************
* define PIT APIs
*
*//*! @addtogroup pit_api_list
* @{
*******************************************************************************/

/*****************************************************************************//*!
*
* @brief initialize pit module.
*
* @param[in]   u8Channel_No channel number
* @param[in]   pConfig point to configuration
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
void PIT_Init(uint8_t u8Channel_No, PIT_ConfigType *pConfig)
{
    SIM->SCGC |= SIM_SCGC_PIT_MASK;     /*!< enable clock to PIT */

    if (pConfig->bFreeze)
    {
        PIT_SetDebugFreeze();
    }

    if (pConfig->bModuleDis == 0)
    {
        PIT_Enable();       			/*!< enable pit module */
    }

    PIT_SetLoadVal(u8Channel_No, pConfig->u32LoadValue);

    if (pConfig->bInterruptEn)
    {
        if (u8Channel_No)
        {
        	NVIC_EnableIRQ(PIT_CH1_IRQn);
        }
        else
        {
            NVIC_EnableIRQ(PIT_CH0_IRQn);
        }

        PIT_ChannelEnableInt(u8Channel_No);
    }
    else
    {
        NVIC_DisableIRQ(PIT_CH0_IRQn);
    }

    if (pConfig->bChainMode)
    {
        PIT_ChannelEnableChain(u8Channel_No);
    }

    if (pConfig->bTimerEn)
    {
        PIT_ChannelEnable(u8Channel_No);
    }
}

/*****************************************************************************//*!
*
* @brief initialize pit module.
*
* @param[in]   u8Channel_No channel number
* @param[in]   u32loadvalue load value for pit register
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
void PIT_SetLoadVal(uint8_t u8Channel, uint32_t u32loadvalue)
{
    PIT->CHANNEL[u8Channel].LDVAL = u32loadvalue;
}

#if 0
/*****************************************************************************//*!
*
* @brief pit module set call back.
*
* @param[in] u8Channel_No channel number.
* @param[in] pfnCallback point to call back.
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
void PIT_SetCallback(uint8_t u8Channel_No, PIT_CallbackType pfnCallback)
{
  PIT_Callback[u8Channel_No] = pfnCallback;
}
#endif

/*****************************************************************************//*!
*
* @brief pit module de-initialize, reset pit register
*
* @param none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
void PIT_DeInit(void)
{
    NVIC_DisableIRQ(PIT_CH0_IRQn);
    NVIC_DisableIRQ(PIT_CH1_IRQn);
    PIT_SetLoadVal(0,0);
    PIT_SetLoadVal(1,0);
    PIT_ChannelDisable(0);
    PIT_ChannelDisable(1);
    PIT_ChannelDisableInt(0);
    PIT_ChannelDisableInt(1);
    PIT_ChannelDisableChain(0);
    PIT_ChannelDisableChain(1);
    PIT_ChannelClrFlags(0);
    PIT_ChannelClrFlags(1);
    PIT_SetDebugOn();
    PIT_Disable();
    SIM->SCGC &= ~SIM_SCGC_PIT_MASK;
}
/*! @} End of pit_api_list                                                   */


#if 0
/*****************************************************************************//*!
*
* @brief pit module channel 0 isr.
*
* @param none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
void PIT_Ch0Isr(void)
{
   PIT_ChannelClrFlags(0);

    if (PIT_Callback[0])
    {
        PIT_Callback[0]();
    }
}

/*****************************************************************************//*!
*
* @brief pit module channel 1 isr.
*
* @param none
*
* @return none
*
* @ Pass/ Fail criteria: none
*****************************************************************************/
void PIT_Ch1Isr(void)
{
    PIT_ChannelClrFlags(1);
    if (PIT_Callback[1])
    {
        PIT_Callback[1]();
    }
}
#endif

/**
  * @brief  Suspend the specified channel PIT timer.
  * @param  u8Channel, PIT timer channel number.
  * @retval None.
  */
void PIT_Suspend(uint8_t u8Channel)
{
	PIT_ChannelDisable(u8Channel);
}

/**
  * @brief  Resume the specified channel PIT timer.
  * @param  u8Channel, PIT timer channel number.
  * @retval None.
  */
void PIT_Resume(uint8_t u8Channel)
{
	PIT_ChannelEnable(u8Channel);
}

/**
  * @brief  Initialize PIT timer channel0 to count and enable interrupt.Time period is 5ms.
  * @param  None.
  * @retval None.
  */
void HAL_PITChannel0Init(void)
{
	PIT_ConfigType pitTimer0Config;

	pitTimer0Config.bFreeze      = 0;
	pitTimer0Config.bModuleDis   = 0;
	pitTimer0Config.bTimerEn     = 1;
	pitTimer0Config.bInterruptEn = 1;
	pitTimer0Config.bChainMode   = 0;
	pitTimer0Config.u32LoadValue = 100000 - 1;     /* PIT时钟主频20MHz,T = 0.05us.定时5ms,则LDVAL = 5000us/0.05 - 1= 99999. */

	PIT_Init(PIT_CHANNEL0, &pitTimer0Config);
	NVIC_SetPriority(PIT_CH0_IRQn, 2);
}




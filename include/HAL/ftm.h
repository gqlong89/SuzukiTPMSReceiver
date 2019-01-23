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
* @file ftm.h
*
* @author Freescale
*
* @version 0.0.1
*
* @date Jun. 25, 2013
*
* @brief header file for FTM.
*
*******************************************************************************
*
* provide APIs for accessing FTM
******************************************************************************/
#ifndef FTM_H_
#define FTM_H_
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
* Includes
******************************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include "derivative.h"
#include "assert.h"

/******************************************************************************
* Constants
******************************************************************************/

/******************************************************************************
* Macros
******************************************************************************/

/******************************************************************************
* FTM return status definition
*
*//*! @addtogroup ftm_returnstatus
* @{
*******************************************************************************/
#define FTM_ERR_SUCCESS         0               /*!< return ok */
#define FTM_ERR_INVALID_PARAM   1               /*!< return invalid parameter */
/*! @} End of ftm_returnstatus                                                */


/******************************************************************************
* FTM channel number definition
*
*//*! @addtogroup ftm_channelnumber
* @{
*******************************************************************************/
#define FTM_CHANNEL_CHANNEL0    0               /*!< channel 0 */
#define FTM_CHANNEL_CHANNEL1    1               /*!< channel 1 */
#define FTM_CHANNEL_CHANNEL2    2               /*!< channel 2 */
#define FTM_CHANNEL_CHANNEL3    3               /*!< channel 3 */
#define FTM_CHANNEL_CHANNEL4    4               /*!< channel 4 */
#define FTM_CHANNEL_CHANNEL5    5               /*!< channel 5 */

#define FTM_CHANNELPAIR0        0               /*!< channel pair 0:ch0 & ch1 */
#define FTM_CHANNELPAIR1        2               /*!< channel pair 1:ch2 & ch3 */
#define FTM_CHANNELPAIR2        4               /*!< channel pair 2:ch4 & ch5 */

/*! @} End of ftm_channelnumber                                               */

/******************************************************************************
* FTM pwm mode definition
*
*//*! @addtogroup ftm_pwmmode
* @{
*******************************************************************************/
#define FTM_PWMMODE_EDGEALLIGNED      1          /*!< EPWM */
#define FTM_PWMMODE_CENTERALLIGNED    2          /*!< CPWM */
#define FTM_PWMMODE_COMBINE           3          /*!< Combine PWM */
/*! @} End of ftm_pwmmode                                                     */

/******************************************************************************
* FTM init value definition
*
*//*! @addtogroup ftm_initvalue
* @{
*******************************************************************************/
#define FTM_MOD_INIT	(20000-1)                /*!< MOD inite value */
#define FTM_C0V_INIT	1000                     /*!< C0V inite value */
#define FTM_C1V_INIT	1000                     /*!< C1V inite value */
#define FTM_C2V_INIT	1000                     /*!< C2V inite value */
#define FTM_C3V_INIT	1000                     /*!< C3V inite value */
#define FTM_C4V_INIT	1000                     /*!< C4V inite value */
#define FTM_C5V_INIT	1000                     /*!< C5V inite value */
/*! @} End of ftm_initvalue                                                   */

/******************************************************************************
* FTM combine feature definition
*
*//*! @addtogroup ftm_combinefeature
* @{
*******************************************************************************/
#define FTM_COMBINE_FAULTEN_MASK  0x40       /*!< fault enable */
#define FTM_COMBINE_SYNCEN_MASK   0x20       /*!< sync enable */
#define FTM_COMBINE_DTEN_MASK     0x10       /*!< dead time insertion enable */
#define FTM_COMBINE_DECAP_MASK    0x08       /*!< dual capture status */
#define FTM_COMBINE_DECAPEN_MASK  0x04       /*!< dual capture enable */
#define FTM_COMBINE_COMP_MASK     0x02       /*!< complementary enable */
#define FTM_COMBINE_COMBINE_MASK  0x01       /*!< combine enable */
/*! @} End of ftm_combinefeature                                              */

/******************************************************************************
* FTM clock sources definition
*
*//*! @addtogroup ftm_clocksource
* @{
*******************************************************************************/
#define FTM_CLOCK_NOCLOCK             0                 /*!< No Clock */
#define FTM_CLOCK_SYSTEMCLOCK         1                 /*!< System clock/2 */
#define FTM_CLOCK_FIXEDFREQCLOCK      2                 /*!< Fixed Freq Clock */
#define FTM_CLOCK_EXTERNALCLOCK       3                 /*!< External Clock */

/* clock prescale */
#define FTM_CLOCK_PS_DIV1             0                 /*!< DIV 1 */
#define FTM_CLOCK_PS_DIV2             1                 /*!< DIV 2 */
#define FTM_CLOCK_PS_DIV4             2                 /*!< DIV 4 */
#define FTM_CLOCK_PS_DIV8             3                 /*!< DIV 8 */
#define FTM_CLOCK_PS_DIV16            4                 /*!< DIV 16 */
#define FTM_CLOCK_PS_DIV32            5                 /*!< DIV 32 */
#define FTM_CLOCK_PS_DIV64            6                 /*!< DIV 64 */
#define FTM_CLOCK_PS_DIV128           7                 /*!< DIV 128 */
/*! @} End of ftm_clocksource                                                 */

/******************************************************************************
* FTM dead time clock prescale definition
*
*//*! @addtogroup ftm_deadtimeprescale
* @{
*******************************************************************************/
/*  */
#define FTM_DEADTIME_DTPS_DIV1        0                 /*!< DIV 1 */
#define FTM_DEADTIME_DTPS_DIV4        2                 /*!< DIV 4 */
#define FTM_DEADTIME_DTPS_DIV16       3                 /*!< DIV 16 */
/*! @} End of ftm_deadtimeprescale                                            */

/******************************************************************************
* FTM output mode definition
*
*//*! @addtogroup ftm_outputmode
* @{
*******************************************************************************/
/* output mode */
#define FTM_OUTPUT_TOGGLE   1                    /*!< toggle output on match */
#define FTM_OUTPUT_CLEAR    2                    /*!< clear output on match */
#define FTM_OUTPUT_SET      3                    /*!< set output on match */
/*! @} End of ftm_outputmode                                                  */

/******************************************************************************
* FTM input capture edge definition
*
*//*! @addtogroup ftm_inputcaptureedge
* @{
*******************************************************************************/
/* mode edge select*/
#define FTM_INPUTCAPTURE_RISINGEDGE           1     /*!< rising edge */
#define FTM_INPUTCAPTURE_FALLINGEDGE          2     /*!< falling edge */
#define FTM_INPUTCAPTURE_BOTHEDGE             3     /*!< both edge */

#define FTM_INPUTCAPTURE_DUALEDGE_NOEDGE      0     /*!< none */
#define FTM_INPUTCAPTURE_DUALEDGE_RISINGEDGE  1     /*!< rising edge*/
#define FTM_INPUTCAPTURE_DUALEDGE_FALLInGEDGE 2     /*!< falling edge*/
#define FTM_INPUTCAPTURE_DUALEDGE_BOTHEDGE    3     /*!< both edge */
/*! @} End of ftm_inputcaptureedge                                            */

/******************************************************************************
* FTM dual edge capture mode definition
*
*//*! @addtogroup ftm_dualcapturemode
* @{
*******************************************************************************/
#define FTM_INPUTCAPTURE_DUALEDGE_ONESHOT     4  /*!< dual edge one shot mode*/
#define FTM_INPUTCAPTURE_DUALEDGE_CONTINUOUS  5  /*!< dual edge continuouse mode*/
/*! @} End of ftm_dualcapturemode                                            */

/******************************************************************************
* FTM PWM edge definition
*
*//*! @addtogroup ftm_pwmedge
* @{
*******************************************************************************/
#define FTM_PWM_HIGHTRUEPULSE        1            /*!< high true pulses */
#define FTM_PWM_LOWTRUEPULSE         2            /*!< low true pulses */
/*! @} End of ftm_pwmedge                                                     */

/******************************************************************************
* FTM sync trigger source definition
*
*//*! @addtogroup ftm_syncsource
* @{
*******************************************************************************/
#define FTM_SYNC_TRIGGER_SOFTWARE    1        /*!< Software synchronization */
#define FTM_SYNC_TRIGGER_TRIGGER2    2        /*!< Tigger2 synchronization, SIM_SOPT[FTMSYNC] */
#define FTM_SYNC_TRIGGER_TRIGGER1    3        /*!< Tigger1 synchronization, FTM0CH0 */
#define FTM_SYNC_TRIGGER_TRIGGER0    4        /*!< Tigger0 synchronization, ACMP0 */
/*! @} End of ftm_syncsource                                                  */

/******************************************************************************
* FTM SW output control definition
*
*//*! @addtogroup ftm_swoutputcontrol
* @{
*******************************************************************************/
#define FTM_SWOCTRL_HIGH    1                /*!< software output high */
#define FTM_SWOCTRL_LOW     0                /*!< software output low */
/*! @} End of ftm_swoutputcontrol                                             */

/******************************************************************************
* FTM  polarity definition
*
*//*! @addtogroup ftm_polarity
* @{
*******************************************************************************/
#define FTM_POLARITY_HIGHACTIVE     0        /*!< active high */
#define FTM_POLARITY_LOWACTIVE      1        /*!< active low */
/*! @} End of ftm_polarity                                                    */


/******************************************************************************
* Types
******************************************************************************/
/*! @brief FTM_CALLBACK function declaration                                  */
typedef void (*FTM_CallbackPtr)(void);
/*! @} End of ftm_callback                                                    */

/******************************************************************************
* FTM configure struct.
*
*//*! @addtogroup ftm_configsturct
* @{
*******************************************************************************/
/*!
* @brief FTM configure struct.
*
*/


/*! @} End of ftm_chconfigsturct                                              */

/******************************************************************************
* Global variables
******************************************************************************/

/*!
 * inline functions
 */
/******************************************************************************
* FTM inline functions
*
*//*! @addtogroup ftm_api_list
* @{
*******************************************************************************/
/*****************************************************************************//*!
*
* @brief  enable the over flow interrupt.
*
* @param[in]    pFTM          pointer to one of three FTM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_DisableOverflowInt.
*
*****************************************************************************/
__STATIC_INLINE void FTM_EnableOverflowInt(FTM_Type *pFTM)
{
    if(pFTM->SC & FTM_SC_TOF_MASK)
    {
        pFTM->SC &= ~FTM_SC_TOF_MASK;
    }
    pFTM->SC |= FTM_SC_TOIE_MASK;
}

/*****************************************************************************//*!
*
* @brief  disable the over flow interrupt.
*
* @param[in]    pFTM          pointer to one of three FTM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none
*
* @see FTM_EnableOverflowInt.
*
*****************************************************************************/
__STATIC_INLINE void FTM_DisableOverflowInt(FTM_Type *pFTM)
{
    pFTM->SC &= ~FTM_SC_TOIE_MASK;
}

/*****************************************************************************//*!
*
* @brief  enable the channel interrupt.
*
* @param[in]    pFTM           pointer to one of three FTM base register address.
* @param[in]    u8FTM_Channel  channel number.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_DisableChannelInt.
*
*****************************************************************************/
__STATIC_INLINE void FTM_EnableChannelInt(FTM_Type *pFTM, uint8_t u8FTM_Channel)
{
    pFTM->CONTROLS[u8FTM_Channel].CnSC |= FTM_CnSC_CHIE_MASK;
}

/*****************************************************************************//*!
*
* @brief  disable the channel interrupt.
*
* @param[in]    pFTM           pointer to one of three FTM base register address.
* @param[in]    u8FTM_Channel  channel number.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_EnableChannelInt.
*
*****************************************************************************/
__STATIC_INLINE void FTM_DisableChannelInt(FTM_Type *pFTM, uint8_t u8FTM_Channel)
{
    pFTM->CONTROLS[u8FTM_Channel].CnSC &= ~FTM_CnSC_CHIE_MASK;
}

/*****************************************************************************//*!
*
* @brief  get the over flow flag.
*
* @param[in]    pFTM           pointer to one of three FTM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_ClrOverFlowFlag.
*
*****************************************************************************/
__STATIC_INLINE uint8_t FTM_GetOverFlowFlag(FTM_Type *pFTM)
{
    return (pFTM->SC & FTM_SC_TOF_MASK);
}

/*****************************************************************************//*!
*
* @brief  clear the over flow flag.
*
* @param[in]    pFTM           pointer to one of three FTM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_GetOverFlowFlag.
*
*****************************************************************************/
__STATIC_INLINE void FTM_ClrOverFlowFlag(FTM_Type *pFTM)
{
    if(pFTM->SC & FTM_SC_TOF_MASK)
    {
         pFTM->SC &= ~FTM_SC_TOF_MASK;
    }
}

/*****************************************************************************//*!
*
* @brief  get the channel flag.
*
* @param[in]    pFTM           pointer to one of three FTM base register address.
* @param[in]    u8FTM_Channel  channel number.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_ClrChannelFlag.
*
*****************************************************************************/
__STATIC_INLINE uint8_t FTM_GetChannelFlag(FTM_Type *pFTM, uint8_t u8FTM_Channel)
{
    return (pFTM->CONTROLS[u8FTM_Channel].CnSC & FTM_CnSC_CHF_MASK);
}

/*****************************************************************************//*!
*
* @brief  clear the channel flag.
*
* @param[in]    pFTM           pointer to one of three FTM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_GetChannelFlag.
*
*****************************************************************************/
__STATIC_INLINE void FTM_ClrChannelFlag(FTM_Type *pFTM, uint8_t u8FTM_Channel)
{
    pFTM->CONTROLS[u8FTM_Channel].CnSC &= ~FTM_CnSC_CHF_MASK;
}

/*********************************************************************************//*!
*
* @brief enable the write protection function.Write protected bits cannot be written.
*
* @param[in]    pFTM              pointer to one of three FTM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_WriteProtectionDisable.
*
*********************************************************************************/
__STATIC_INLINE void FTM_WriteProtectionEnable(FTM_Type *pFTM)
{
    pFTM->FMS |= FTM_FMS_WPEN_MASK;
}

/*********************************************************************************//*!
*
* @brief disable the write protection function.Write protected bits can be written.
*
* @param[in]    pFTM              pointer to one of three FTM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_WriteProtectionDisable.
*
*********************************************************************************/
__STATIC_INLINE void FTM_WriteProtectionDisable(FTM_Type *pFTM)
{
    if (pFTM->FMS & FTM_FMS_WPEN_MASK)
    {
        pFTM->MODE |= FTM_MODE_WPDIS_MASK;
    }
}

/*****************************************************************************//*!
*
* @brief  set FTMEN bit to enable FTM-specific register.
*
* @param[in]    pFTM           pointer to one of three FTM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_SetFTMBasic.
*
*****************************************************************************/
__STATIC_INLINE void FTM_SetFTMEnhanced(FTM_Type *pFTM)
{
    if(pFTM->MODE & FTM_MODE_WPDIS_MASK)   /* if not write protected */
    {
        pFTM->MODE |= FTM_MODE_FTMEN_MASK;
    }
    else
    {
        FTM_WriteProtectionDisable(pFTM);
        pFTM->MODE |= FTM_MODE_FTMEN_MASK;
        FTM_WriteProtectionEnable(pFTM);
    }
}

/*****************************************************************************//*!
*
* @brief  clear FTMEN bit to disable FTM-specific registers, only TPM-compatible
*         registers can be used.
*
* @param[in]    pFTM           pointer to one of three FTM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_SetFTMEnhanced.
*
*****************************************************************************/
__STATIC_INLINE void FTM_SetFTMBasic(FTM_Type *pFTM)
{
    if(pFTM->MODE & FTM_MODE_WPDIS_MASK)    /* if not write protected */
    {
        pFTM->MODE &= ~FTM_MODE_FTMEN_MASK;
    }
    else
    {
        FTM_WriteProtectionDisable(pFTM);
        pFTM->MODE &= ~FTM_MODE_FTMEN_MASK;
        FTM_WriteProtectionEnable(pFTM);
    }
}

/*****************************************************************************//*!
*
* @brief  set the ftm mod value.
*
* @param[in]    pFTM           pointer to one of three FTM base register address.
* @param[in]    u16ModValue    the mod value required to set.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_SetChannelValue.
*
*****************************************************************************/
__STATIC_INLINE void FTM_SetModValue(FTM_Type *pFTM, uint16_t u16ModValue)
{
    pFTM->CNT = 0;
    pFTM->MOD = u16ModValue;
    if(FTM2 == pFTM)
    {
        if(pFTM->MODE & FTM_MODE_FTMEN_MASK)
        {
            pFTM->PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;
        }
        else
        {
        }
    }
    else
    {
    }
}

/*****************************************************************************//*!
*
* @brief  set the ftm channel value.
*
* @param[in]    pFTM             pointer to one of three FTM base register address.
* @param[in]    u16ChannelValue  the CnV value required to set.
* @param[in]    u8FTM_Channel    ftm channel number.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_SetModValue.
*
*****************************************************************************/
__STATIC_INLINE void FTM_SetChannelValue(FTM_Type *pFTM, uint8_t u8FTM_Channel, uint16_t u16ChannelValue)
{
    pFTM->CONTROLS[u8FTM_Channel].CnV = u16ChannelValue;
    if(FTM2 == pFTM)
    {
        if(pFTM->MODE & FTM_MODE_FTMEN_MASK)
        {
            if(u8FTM_Channel < 2)
            {
                pFTM->COMBINE |= FTM_COMBINE_SYNCEN0_MASK;  /* enable the sync function */
            }
            else if (u8FTM_Channel < 4)
            {
                pFTM->COMBINE |= FTM_COMBINE_SYNCEN1_MASK;
            }
            else
            {
                pFTM->COMBINE |= FTM_COMBINE_SYNCEN2_MASK;
            }
            pFTM->PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;
        }
        else
        {
        }
    }
    else
    {
    }
}

/*****************************************************************************//*!
*
* @brief  set the ftm channel value.
*
* @param[in]    pFTM              pointer to one of three FTM base register address.
* @param[in]    u16CounterValue   the CNTIN value required to set.
*
* @return none.
*
* @ Pass/ Fail criteria: none
*
* @see FTM_SetModValue.
*
*****************************************************************************/
__STATIC_INLINE void FTM_SetCounterInitValue(FTM_Type *pFTM, uint16_t u16CounterValue)
{
    pFTM->CNTIN = u16CounterValue;
    if(pFTM->MODE & FTM_MODE_FTMEN_MASK)
    {
        pFTM->PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;
    }
    else
    {
    }
}

/*****************************************************************************//*!
*
* @brief  set the channel output mask value, FTM2 used only.
*
* @param[in]    pFTM            pointer to one of three FTM base register address.
* @param[in]    u16ChMask       the CNTIN value required to set.
*
* @return none.
*
* @ Pass/ Fail criteria: none
*
* @see FTM_UnMaskChannels.
*
*****************************************************************************/
__STATIC_INLINE void FTM_MaskChannels(FTM_Type *pFTM, uint16_t u16ChMask)
{
     pFTM->OUTMASK |= u16ChMask;
}

/*****************************************************************************//*!
*
* @brief  clear the channel output mask value, FTM2 used only.
*
* @param[in]    pFTM            pointer to one of three FTM base register address.
* @param[in]    u16ChMask       the CNTIN value required to set.
*
* @return none.
*
* @ Pass/ Fail criteria: none
*
* @see FTM_MaskChannels.
*
*****************************************************************************/
__STATIC_INLINE void FTM_UnMaskChannels(FTM_Type *pFTM, uint16_t u16ChMask)
{
     pFTM->OUTMASK &= ~u16ChMask;
}

/*********************************************************************************//*!
*
* @brief set FTM channels polarity.
*
* @param[in]    pFTM                  pointer to one of three FTM base register address.
* @param[in]    u8ChsPolValue         the channels value need to be set.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_GetChannelsPolarity.
*
*********************************************************************************/
__STATIC_INLINE void FTM_SetChannelsPolarity(FTM_Type *pFTM, uint8_t u8ChsPolValue)
{
    pFTM->POL = u8ChsPolValue;
}

/*********************************************************************************//*!
*
* @brief get FTM channels polarity.
*
* @param[in]    pFTM                  pointer to one of three FTM base register address.
*
* @return uint8_t the channels polarity.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_SetChannelsPolarity.
*
*********************************************************************************/
__STATIC_INLINE uint8_t FTM_GetChannelsPolarity(FTM_Type *pFTM)
{
    return (pFTM->POL);
}

/*********************************************************************************//*!
*
* @brief select the enhanced SYNC mode.
*
* @param[in]    pFTM              pointer to one of three FTM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_DisableEnhancedSYNCMode.
*
*********************************************************************************/
__STATIC_INLINE void FTM_EnableEnhancedSYNCMode(FTM_Type *pFTM)
{
    pFTM->SYNCONF   |= FTM_SYNCONF_SYNCMODE_MASK;   /* recommend enhanced sync mode */
}

/*********************************************************************************//*!
*
* @brief select the legacy SYNC mode.
*
* @param[in]    pFTM              pointer to one of three FTM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_EnableEnhancedSYNCMode.
*
*********************************************************************************/
__STATIC_INLINE void FTM_DisableEnhancedSYNCMode(FTM_Type *pFTM)
{
    pFTM->SYNCONF   &= ~FTM_SYNCONF_SYNCMODE_MASK;   /* recommend enhanced sync mode */
}

/*********************************************************************************//*!
*
* @brief set the external trigger source.
*
* @param[in]    pFTM              pointer to one of three FTM base register address.
* @param[in]    u8TirggerSource   initial trigger or CHn(0~5)trigger
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_GetExternalTriggerFlag.
*
*********************************************************************************/
__STATIC_INLINE void FTM_SetExternalTrigger(FTM_Type *pFTM, uint8_t u8TirggerSource)
{
    pFTM->EXTTRIG   = u8TirggerSource;
}

/*********************************************************************************//*!
*
* @brief get the external trigger flag.
*
* @param[in]    pFTM              pointer to one of three FTM base register address.
*
* @return ex trigger flag.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_SetExternalTrigger.
*
*********************************************************************************/
__STATIC_INLINE uint8_t FTM_GetExternalTriggerFlag(FTM_Type *pFTM)
{
    return (pFTM->EXTTRIG & FTM_EXTTRIG_TRIGF_MASK);
}

/*********************************************************************************//*!
*
* @brief set LDOK bit.
*
* @param[in]    pFTM              pointer to one of three FTM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_SetLoadMatchChannel.
*
*********************************************************************************/
__STATIC_INLINE void FTM_SetLoadEnable(FTM_Type *pFTM)
{
    pFTM->PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;
}

/*********************************************************************************//*!
*
* @brief set the channel in the matching process.
*
* @param[in]    pFTM              pointer to one of three FTM base register address.
* @param[in]    u8Matchchannel    the channel in the matching process.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_SetLoadEnable.
*
*********************************************************************************/
__STATIC_INLINE void FTM_SetLoadMatchChannel(FTM_Type *pFTM, uint8_t u8Matchchannel)
{
    pFTM->PWMLOAD |= u8Matchchannel;
}

/*********************************************************************************//*!
*
* @brief disable the channel input capture filter.
*
* @param[in]    pFTM              pointer to one of three FTM base register address.
* @param[in]    u8FTM_Channel     the channel number: 0~3.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_InputCaptureFilterSet.
*
*********************************************************************************/
__STATIC_INLINE void FTM_InputCaptureFilterClr(FTM_Type *pFTM, uint8_t u8FTM_Channel)
{
    pFTM->FILTER &= ~(0x000F << (u8FTM_Channel << 2));
}

/*********************************************************************************//*!
*
* @brief set the channel input capture filter value.
*
* @param[in]    pFTM              pointer to one of three FTM base register address.
* @param[in]    u8FTM_Channel     the channel number: 0~3.
* @param[in]    u8FilterValue     fliter cycles:1~15, 0: disable channel filter.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_InputCaptureFilterClr.
*
*********************************************************************************/
__STATIC_INLINE void FTM_InputCaptureFilterSet(FTM_Type *pFTM, uint8_t u8FTM_Channel, uint8_t u8FilterValue)
{
    if (u8FilterValue)
    {
        pFTM->FILTER |= (u8FilterValue << (u8FTM_Channel << 2));
    }
    else
    {
        FTM_InputCaptureFilterClr(pFTM, u8FTM_Channel);
    }
}


/*********************************************************************************//*!
*
* @brief enable the fault input pin.
*
* @param[in]    pFTM              pointer to one of three FTM base register address.
* @param[in]    u8FaultPin        the fault input channel number: 0~3.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_FaultPinDisable.
*
*********************************************************************************/
__STATIC_INLINE void FTM_FaultPinEnable(FTM_Type *pFTM, uint8_t u8FaultPin)
{
    if (pFTM->MODE & FTM_MODE_WPDIS_MASK) /* if not protected */
    {
        pFTM->FLTCTRL |= (1 << u8FaultPin);
    }
    else                                  /* if protected */
    {
        FTM_WriteProtectionDisable(pFTM);
        pFTM->FLTCTRL |= (1 << u8FaultPin);
        FTM_WriteProtectionEnable(pFTM);
    }
}

/*********************************************************************************//*!
*
* @brief disable the fault input pin.
*
* @param[in]    pFTM              pointer to one of three FTM base register address.
* @param[in]    u8FaultPin        the fault input channel number: 0~3.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_FaultPinEnable.
*
*********************************************************************************/
__STATIC_INLINE void FTM_FaultPinDisable(FTM_Type *pFTM, uint8_t u8FaultPin)
{
    if (pFTM->MODE & FTM_MODE_WPDIS_MASK) /* if not protected */
    {
        pFTM->FLTCTRL &= ~(1 << u8FaultPin);
    }
    else                                  /* if protected */
    {
        FTM_WriteProtectionDisable(pFTM);
        pFTM->FLTCTRL &= ~(1 << u8FaultPin);
        FTM_WriteProtectionEnable(pFTM);
    }
}

/*********************************************************************************//*!
*
* @brief enable the fault pin filter.
*
* @param[in]    pFTM              pointer to one of three FTM base register address.
* @param[in]    u8FaultPin        the fault input channel number: 0~3.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_FaultPinFilterDisable.
*
*********************************************************************************/
__STATIC_INLINE void FTM_FaultPinFilterEnable(FTM_Type *pFTM, uint8_t u8FaultPin)
{
    if (pFTM->MODE & FTM_MODE_WPDIS_MASK) /* if not protected */
    {
        pFTM->FLTCTRL |= (0x10 << u8FaultPin);
    }
    else                                  /* if protected */
    {
        FTM_WriteProtectionDisable(pFTM);
        pFTM->FLTCTRL |= (0x10 << u8FaultPin);
        FTM_WriteProtectionEnable(pFTM);
    }
}

/*********************************************************************************//*!
*
* @brief disable the fault pin filter.
*
* @param[in]    pFTM              pointer to one of three FTM base register address.
* @param[in]    u8FaultPin        the fault input channel number: 0~3.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_FaultPinFilterDisable.
*
*********************************************************************************/
__STATIC_INLINE void FTM_FaultPinFilterDisable(FTM_Type *pFTM, uint8_t u8FaultPin)
{
    if (pFTM->MODE & FTM_MODE_WPDIS_MASK) /* if not protected */
    {
        pFTM->FLTCTRL &= ~(0x10 << u8FaultPin);
    }
    else                                  /* if protected */
    {
        FTM_WriteProtectionDisable(pFTM);
        pFTM->FLTCTRL &= ~(0x10 << u8FaultPin);
        FTM_WriteProtectionEnable(pFTM);
    }
}

/*********************************************************************************//*!
*
* @brief disable all the fault pins filter together.
*
* @param[in]    pFTM              pointer to one of three FTM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_FaultPinFilterSet.
*
*********************************************************************************/
__STATIC_INLINE void FTM_FaultPinFilterCDisableAll(FTM_Type *pFTM)
{
    pFTM->FLTCTRL &= ~FTM_FLTCTRL_FFVAL_MASK;
}

/*********************************************************************************//*!
*
* @brief set the fault filter value. All channels share the same filter value.
*
* @param[in]    pFTM              pointer to one of three FTM base register address.
* @param[in]    u8FilterValue     the fault input filter value: 1~15, 0 disable the filter.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_FaultPinFilterCDisableAll.
*
*********************************************************************************/
__STATIC_INLINE void FTM_FaultPinFilterSet(FTM_Type *pFTM, uint8_t u8FilterValue)
{
    if (u8FilterValue)
    {
        pFTM->FLTCTRL |= FTM_FLTCTRL_FFVAL(u8FilterValue);
    }
    else
    {
        FTM_FaultPinFilterCDisableAll(pFTM);
    }
}

/*********************************************************************************//*!
*
* @brief get the logic OR of all the fault detection flags
*
* @param[in]    pFTM              pointer to one of three FTM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_GetFaultDetectionFlag.
*
*********************************************************************************/
__STATIC_INLINE uint8_t FTM_GetFaultDetectionLogicORFlag(FTM_Type *pFTM)
{
    return (pFTM->FMS & FTM_FMS_FAULTF_MASK);
}

/*********************************************************************************//*!
*
* @brief get the fault detection flag
*
* @param[in]    pFTM              pointer to one of three FTM base register address.
* @param[in]    u8FaultPin        fault input pin number: 0~3.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_GetFaultDetectionLogicORFlag.
*
*********************************************************************************/
__STATIC_INLINE uint8_t FTM_GetFaultDetectionFlag(FTM_Type *pFTM, uint8_t u8FaultPin)
{
    return (pFTM->FMS & (1 << u8FaultPin));
}

/*********************************************************************************//*!
*
* @brief get the logic OR value of the fault inputs
*
* @param[in]    pFTM              pointer to one of three FTM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*********************************************************************************/
__STATIC_INLINE uint8_t FTM_GetFaultInputsLogicORValue(FTM_Type *pFTM)
{
    return (pFTM->FMS & FTM_FMS_FAULTIN_MASK);
}

/*! @} End of ftm_api_list                                                    */

/******************************************************************************
* Global functions
******************************************************************************/


/* FTM硬件模块编号. */
#define  HW_FTM0		(0x00)
#define  HW_FTM1		(0x01)
#define  HW_FTM2		(0x02)

/* FTM可用的通道编号. */
#define  HW_FTM_CH0		(0x00)
#define  HW_FTM_CH1		(0x01)
#define  HW_FTM_CH2		(0x02)
#define  HW_FTM_CH3		(0x03)
#define  HW_FTM_CH4		(0x04)
#define	 HW_FTM_CH5		(0x05)
#define  HW_FTM_CH6		(0x06)
#define  HW_FTM_CH7		(0x07)

typedef enum
{
	FTM_IT_TOF,    		/* 定时器溢出中断. */
	FTM_IT_CH0,			/* 通道0中断. */
	FTM_IT_CH1,			/* 通道1中断. */
	FTM_IT_CH2,			/* 通道2中断. */
	FTM_IT_CH3,			/* 通道3中断. */
	FTM_IT_CH4,			/* 通道4中断. */
	FTM_IT_CH5,			/* 通道5中断. */
	FTM_IT_CH6,			/* 通道6中断. */
	FTM_IT_CH7,			/* 通道7中断. */
}FTM_ITConfigDef_t;

typedef enum
{
	FTM_ClockDiv1 = 0,
	FTM_ClockDiv2,
	FTM_ClockDiv4,
	FTM_ClockDiv8,
	FTM_ClockDiv16,
	FTM_ClockDiv32,
	FTM_ClockDiv64,
	FTM_ClockDiv128,
}FTM_ClockDivDef_t;

typedef enum
{
	No_Clock = 0,
	System_Clock,
	Fixed_Clock,
	External_Clock,
}FTM_ClockSourceDef_t;

typedef struct
{
	uint8_t  InterruptState;				/* 中断使能状态. 1,使能; 0,不使能; */
	uint16_t ModVal;						/* 模数寄存器的值.计数器计到该寄存器的值后TOF标志置位. */
	uint16_t InitVal;						/* 计数器初始值. */
	FTM_ClockDivDef_t ClkDiv;				/* FTM定时器时钟分频值. */
	FTM_ClockSourceDef_t ClkSrc;			/* FTM定时器输入时钟源. */
}FTM_BasicCounterProDef_t;


void FTM_BasicCounterInit(uint8_t instance, FTM_BasicCounterProDef_t* pFTMPro);
void FTM_BasicCounterDeInit(uint8_t instance);
void FTM_BasicCounterWaitOverFlow(uint8_t instance);

#ifdef __cplusplus
}
#endif
#endif /* FTM_H_ */

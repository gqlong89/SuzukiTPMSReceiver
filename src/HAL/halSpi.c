/*
 * halSpi.c
 *
 *  Created on: Jan 23, 2019
 *      Author: wj1080
 */

#include "halSpi.h"
#include "assert.h"


/*****************************************************************************//*!
   *
   * @brief initialize SPI as per params.
   *
   * @param[in]  pSPI   point to SPI module type.
   * @param[in]  pConfig point to configuration parameters.
   *
   * @return none.
   *
   * @ Pass/ Fail criteria: none.
   *****************************************************************************/
void HAL_SPIInit(SPI_Type *pSPI, SPI_ConfigType *pConfig)
{
#if defined(CPU_KEA64)
     /* sanity check */
    ASSERT((pSPI == SPI0));
    SIM->SCGC |= SIM_SCGC_SPI0_MASK;
#else
    /* sanity check */
    ASSERT((pSPI == SPI0) ||  (pSPI == SPI1));

    /* enable SPI clock gating on */
    if( pSPI == SPI0)
    {
        SIM->SCGC |= SIM_SCGC_SPI0_MASK;

        SIM->PINSEL &= ~SIM_PINSEL_SPI0PS_MASK;
    }
    else
    {
        SIM->SCGC |= SIM_SCGC_SPI1_MASK;

        SIM->PINSEL1 &= ~SIM_PINSEL1_SPI1PS_MASK;
    }
#endif
    /* configure other control bits */
    if( pConfig->sSettings.bIntEn)
    {
        SPI_IntEnable(pSPI);
#if defined(CPU_KEA64)
        NVIC_EnableIRQ(SPI0_IRQn);
#else
        if( pSPI == SPI0 )
        {
			NVIC_EnableIRQ(SPI0_IRQn);
        }
        else
        {
			NVIC_EnableIRQ(SPI1_IRQn);
        }
#endif
    }

    if( pConfig->sSettings.bTxIntEn)
    {
        SPI_TxIntEnable(pSPI);

#if defined(CPU_KEA64)
        NVIC_EnableIRQ(SPI0_IRQn);
#else
        if( pSPI == SPI0 )
        {
			NVIC_EnableIRQ(SPI0_IRQn);
        }
        else
        {
			NVIC_EnableIRQ(SPI1_IRQn);
        }
#endif
    }

    if( pConfig->sSettings.bMasterMode)
    {
        SPI_SetMasterMode(pSPI);
    }
    else
    {
		SPI_SetSlaveMode(pSPI);
    }

    if( pConfig->sSettings.bClkPolarityLow)
    {
    	SPI_SetClockPol(pSPI,1);
    }

    if( pConfig->sSettings.bClkPhase1)
    {
        SPI_SetClockPhase(pSPI,1);
    }

    if( pConfig->sSettings.bShiftLSBFirst)
    {
        SPI_SetLSBFirst(pSPI);
    }

    if( pConfig->sSettings.bMatchIntEn)
    {
        SPI_MatchIntEnable(pSPI);
    }

    if( pConfig->sSettings.bModeFaultEn)
    {
        SPI_ModfEnable(pSPI);
    }

    if( pConfig->sSettings.bMasterAutoDriveSS)
    {
        /* set both SSOE and MODFEN bits when auto drive slave SS is enabled */
        SPI_SSOutputEnable(pSPI);
        SPI_ModfEnable(pSPI);
    }

    if( pConfig->sSettings.bPinAsOuput)
    {
        SPI_BidirPinEnable(pSPI);
    }

    if( pConfig->sSettings.bBidirectionModeEn)
    {
        SPI_BidirOutEnable(pSPI);
    }
    if( pConfig->sSettings.bStopInWaitMode)
    {
        SPI_ClockStopEnable(pSPI);
    }

    if(pConfig->sSettings.bMasterMode)
    {
    	HAL_SPISetBaudRate(pSPI,pConfig->u32BusClkHz,pConfig->u32BitRate);
    }

	/* enable SPI module */
    if( pConfig->sSettings.bModuleEn)
    {
        SPI_Enable(pSPI);
    }
}

/*****************************************************************************//*!
   *
   * @brief SPI set band rate.
   *
   * @param[in]  pSPI   point to SPI module type.
   * @param[in]  u32BusClock   Bus clock.
   * @param[in]  u32Bps   set spi's baudrate.
   *
   * @return  none.
   *
   * @ Pass/ Fail criteria: none.
   *****************************************************************************/
void HAL_SPISetBaudRate(SPI_Type *pSPI,uint32_t u32BusClock,uint32_t u32Bps)
{
	uint32_t u32BitRateDivisor;
	uint8_t u8Sppr;
	uint8_t u8Spr;
    uint8_t u8ReadFlag;
	u32BitRateDivisor = u32BusClock/u32Bps; /* calculate bit rate divisor */

    u8ReadFlag = 0;
    /* find best fit SPPR and SPR */
    for (u8Spr = 0; u8Spr <= 8; u8Spr++)
    {
        for(u8Sppr = 0; u8Sppr <= 7; u8Sppr++)
        {
            if((u32BitRateDivisor>>(u8Spr+1)) <= (u8Sppr+1))
            {
                u8ReadFlag = 1;
                break;
            }
        }
        if(u8ReadFlag)
        {
            break;
        }
    }
    if(u8Sppr >=8)
    {
        u8Sppr = 7;
    }
    if(u8Spr >8)
    {
        u8Spr = 8;
    }
    /* set bit rate */
    pSPI->BR = SPI_BR_SPPR(u8Sppr) | SPI_BR_SPR(u8Spr);
}

/*****************************************************************************//*!
   *
   * @brief implement write data to SPI.
   *
   * @param[in]   pSPI  pointer to SPI module type.
   * @param[in]   pWrBuff -- write data buffer pointer.
   * @param[in]   uiLength -- read/write data length.
   * @param[out]   pRdBuff -- read data buffer pointer.
   *
   * @return  if <0, means error, 0: success.
   *
   * @ Pass/ Fail criteria: none.
   *****************************************************************************/
ResultType HAL_SPITransferWait(SPI_Type *pSPI, SPI_WidthType* pRdBuff, SPI_WidthType *pWrBuff, uint32_t uiLength)
{
    ResultType err = SPI_ERR_SUCCESS;
    uint32_t  i;

    if(!uiLength)
    {
        return (err);
    }

    for(i = 0; i < uiLength; i++)
    {
        while(!SPI_IsSPTEF(pSPI));
        SPI_WriteDataReg(pSPI, pWrBuff[i]);

        while(!SPI_IsSPRF(pSPI));
        pRdBuff[i] = SPI_ReadDataReg(pSPI);
    }

    return (err);
}

/*****************************************************************************//*!
   *
   * @brief Deinitialize SPI to the default state (reset value).
   *
   * @param[in]   pSPI  pointer to SPI module type.
   *
   * @return none.
   *
   * @ Pass/ Fail criteria: none.
   *****************************************************************************/
void HAL_SPIDeInit(SPI_Type *pSPI)
{
    int16_t i;
    pSPI->C1 = SPI_C1_DEFAULT;
    pSPI->C2 = SPI_C2_DEFAULT;
    pSPI->BR = SPI_BR_DEFAULT;
    pSPI->M  = SPI_M_DEFAULT;
    for(i = 0; i<100; i++);                 /* wait for some cycles for the ISR exit */
}



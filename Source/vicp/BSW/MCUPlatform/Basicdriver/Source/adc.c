
/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                                 *
*   AUTHOR     :                                                       *
************************************************************************
* Object        :
* Module        :	ADC
* Instance      :
* Description   :	ADC operation, include channel config, start, stop.
				ADC value are updated in Interrupt.
				Support ADC0I0~ADC0I15. 
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date        Name    Changes and comments
* 0.1	   Jun 26,2016   PEI Jingli  Initial version
------------------------------------------------------------------------
* 0.2	   Aug 1,2016    PEI Jingli   Correct getValue inf 		
------------------------------------------------------------------------
* 0.3	   Aug 31,2016   PEI Jingli   Correct channel=0 error
------------------------------------------------------------------------
* 0.4	   Dec 28,2016   PEI Jingli   Modify for CodeReview result
*------------------------------------------------------------------------
* 0.5          Jan 24,2017  ZhangJie  Update for Coverity warning.
------------------------------------------------------------------------
* 0.6	   Apr 13,2017   PEI Jingli   Fix ICxxx.RF setting errors.
*=====================================================================*/
#include "adc.h"
#include "adc_if.h"
#include "irq_if.h"


volatile static U16 adc_ch_value_array[ADC_MAX]=
{
  0xFFFFU,0xFFFFU,0xFFFFU,0xFFFFU,0xFFFFU,0xFFFFU,0xFFFFU,0xFFFFU, 
  0xFFFFU,0xFFFFU,0xFFFFU,0xFFFFU,0xFFFFU,0xFFFFU,0xFFFFU,0xFFFFU 
};

static U8 vcr_ch=0;		/*number of virtual channels*/
static ADC_VIR_CH_MAP vcr_ch_map[ADC_MAX];
/***********************************************************************
*  Name        : ADC_Init
*  Description :  Initialize adc channel.Always used for ADCA0 group1 with  max 16 channel.
*  Parameter   : usedChannel  used channels. Each bit represent an ADC physical channel.
                                     bit_n=1, channel n is inuse
*                      scannum  unused
*  Returns     : None
***********************************************************************/
void ADC_Init(U16 usedChannels, U16 scannum )
{
    ADC_TYPE i=ADC_0;	
	
    if(!usedChannels)
    {
        /*no invalid channel error*/
    }
    else
    {
        /* clear error flag */
        ADC_REG_ADCA0ECR =ADC_ECR_LIMIT_CLEAR|ADC_ECR_OVERWRITE_CLEAR;
        IRQ_IntClr(INTADCA0ERR);   /*Reset InterreuptRequestFlag*/

        /* associate physical channels and virtual channels */
        vcr_ch=0;
        for(i=ADC_0;i<ADC_MAX;i++)
        {
            if( (1u<<i) & usedChannels)
            {
                /* link phy channel to virtual in sequence */
                ADC_REG_ADCA0VCR(vcr_ch)=i;
                vcr_ch_map[vcr_ch].virtual_channel=vcr_ch;
                vcr_ch_map[vcr_ch].phy_channel=(U16) (1u<<i);
                vcr_ch++;			
            }
        }
    
        /* configratin */
        ADC_REG_ADCA0ADCR = ADC_CR_SUSPEND_ASYN|ADC_CR_12BIT|ADC_CR_RIGHT_ALIGN|ADC_CR_SELFDIAG_OFF;
        ADC_REG_ADCA0SMPCR = ADC_SMCR_SUSPEND_SYN; /*Set sampling time to 18*1/16MHz(8-32MHz) = 1.125us*/
        ADC_REG_ADCA0SFTCR = ADC_SFTCR_OVERWRITE_ERRORINT_DIS|ADC_SFTCR_LIMMIT_ERRORINT_EN|ADC_SFTCR_READCLEAR_DIS; /*Upper/Lower limit error */       
        /*Enable group 1*/
        ADC_REG_ADCA0SGCR(ADC_GRPUP_1) = ADC_SGCR_SCANEND_INT_EN; /*ScanGroup interrupt is output when scan ends;use one group*/
        ADC_REG_ADCA0SGVCSP(ADC_GRPUP_1) = 0;	         /*scan-start channel is virtual channel 0*/
        ADC_REG_ADCA0SGVCEP(ADC_GRPUP_1) = vcr_ch-1u; /*scan-start channel is vcr_ch-1*/

    	 /* Enable ADCA0 group1 interrupt */
    	 IRQ_IntEn(INTADCA0I0);
    }
}

/***********************************************************************
*  Name        : ADC_DeInit
*  Description : Always used for ADCA0 group1 with  max 16 channel.
*  Parameter   : None

*  Returns     : None
***********************************************************************/
void ADC_DeInit( void )
{
    /* Disable ADCA0 group1 interrupt */
    IRQ_IntDis(INTADCA0I0);
}

/***********************************************************************
*  Name        : ADC_Start
*  Description : Conversion start trigger for ADCA0 group1
			  Should be called in cyclic task if not using _BLOCK_READ_ADC.
*  Parameter   : adc_ch- if not using _BLOCK_READ_ADC, specify physical channel

*  Returns     : None
***********************************************************************/
void ADC_Start( )
{
    ADC_REG_ADCA0SGSTCR(ADC_GRPUP_1) = 1U; /*set start-trigger of group1 to conversion starting*/       
}

/***********************************************************************
*  Name        : ADC_Stop
*  Description : no useful, automatically stop
*  Parameter   : None

*  Returns     : None
***********************************************************************/
void ADC_Stop( )
{
     /*Nothing to do*/
}

/***********************************************************************
*  Name        : ADC_Conversion
*  Description : start to scan group1
*  Parameter   : None

*  Returns     : None
***********************************************************************/
void  ADC_Conversion( void )
{
    ADC_Start();
}
/***********************************************************************
*  Name        : ADC_GetValue
*  Description : Get AD value of channel adc_ch. Always used for ADCA0 group1
*  Parameter   : channelId -index of physical channe,  ADC_TYPE
*                      *val     -A/D conversion value
*  Returns     : ERR_TYPE
***********************************************************************/
ERR_TYPE ADC_GetValue( ADC_TYPE channelId, U16* val )
{
    U8 vcr_ch_index=0;
    ADC_TYPE ch=ADC_0;
    ERR_TYPE eErr=ERR_FAILED;
    
    if((channelId>=ADC_MAX) ||(NULL==val))
    {
    }
    else
    {
        /* search for virtual channel index based on physical channel */
        for(ch=ADC_0;ch<ADC_MAX;ch++)
        {
            if(vcr_ch_map[ch].phy_channel==(U16)(1u<<channelId))
            {
                vcr_ch_index=vcr_ch_map[ch].virtual_channel;
                break;
            }
        }
      
        if(ch<ADC_MAX)
        {
            *val = adc_ch_value_array[vcr_ch_index];	
            eErr= ERR_OK;
        }
    }
	
    return eErr;
}

/***********************************************************************
*  Name        : ADC_Update_G1_Handler
*  Description : Get AD values of ADCA0 scan group1 after scan handler
*  Parameter   : None

*  Returns     : None
***********************************************************************/
void ADC_Update_G1_Handler( void )
{
    U8 ch_index=0;
 
    for(ch_index=0;ch_index<vcr_ch;ch_index++)
    {
        adc_ch_value_array[ch_index] = ADC_REG_ADCA0DIR(ch_index);
    }
}

/***********************************************************************
*  Name        : ISR_ADCA0_INTSG1func
*  Description : ADCA0 scan group1 ISR
*  Parameter   : None

*  Returns     : None
***********************************************************************/
void ISR_ADCA0_INTSG1func(void)
{
    ADC_Update_G1_Handler();
}


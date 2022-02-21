/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									   *
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   :
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
* ----------------------------------------------------------------------
* 0.1    Feb 10,2013    NI Rujin    Initial version
* ----------------------------------------------------------------------
* 0.2    Apr 20,2013    LIU Chenxi  Fix issues found when implementing 
             power management module
------------------------------------------------------------------------
* 0.3    July 07,2016  PEI Jingli  Adapt 64pin MCU
------------------------------------------------------------------------
* 0.4    Aug 1,2016    PEI Jingli   Rename interface and Correct errors about ADC conversion 		
*----------------------------------------------------------------------
* 0.5    Dec 20,2016   ShangQiuju Remove unused include files.
*----------------------------------------------------------------------
* 0.6    Dec 23,2016  PEI Jingli  Change adc channel micro
------------------------------------------------------------------------
* 0.7    Dec 28,2016  PEI Jingli  Modify for CodeReview result,add descripton
------------------------------------------------------------------------
* 0.8    Jan 06,2017   ShangQiuju  Update Sig get func accoding SIG update.
*------------------------------------------------------------------------
* 0.9    Jan 12,2017  ZhangJie  Add Update for Coverity warnings.
*----------------------------------------------------------------------
* 1.0    Jan 16,2017   RenWeimin  Add test code.
*------------------------------------------------------------------------
* 1.1   Jan 24,2017  ZhangJie  Fix Coverity warnings phase2.
*-----------------------------------------------------------------------
* 1.2    Feb 09,2017   ZhangJie   Remove EOL definition.
*-----------------------------------------------------------------------
* 1.3   Apr 01,2017   PEI Jingli  Fix headfiles.
*----------------------------------------------------------------------
* 1.4   Apr 07,2017  PEI Jingli  Fix warnings.
*=====================================================================*/
#include "Startup.h"
#include "ADC_APP.h"
#include "ADC_if.h"


#define   ADC_IN_CHANNEL    (ADCA0_CHANNEL_USED)

static Sig_ADData  Sig_ADGlobal =
{
    FALSE,	
    { 0u },
    { 0u }, 
    { 0u },
    { 0u }
};


ERR_TYPE read_adsignal(U8 number, E_ADDeviceType devicetype, U16* pvalue);

/***********************************************************************
*  Name        : Sig_ADInit
*  Description : Initializes the Sig_AD module, and calls AD driver initial.   
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Sig_ADInit(void)
{
    /******************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local ROM-constants
    * - all function local variables (auto and static)
    *******************************************************************/
    U16 Loops = 0U;
    /* clear the raw and filter value buffer */
    for( Loops = 0U; Loops < (U16)SIG_AD_NUM; Loops++)
    {
        Sig_ADGlobal.RawValue[Loops] = 0U;
        Sig_ADGlobal.ResultCounter[Loops] = 0U;
        Sig_ADGlobal.ResultValue[Loops] = 0U;
    }
    Sig_ADGlobal.InitState = TRUE; /* set sig_adc module as initialized. */
    ADC_Init( ADC_IN_CHANNEL, ADC_CHANNEL_COUNT-1u );
    
}

/***********************************************************************
*  Name        : Sig_ADDeInit
*  Description : de-Initializes the Sig_AD module.   
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Sig_ADDeInit(void)
{
    /******************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local ROM-constants
    * - all function local variables (auto and static)
    *******************************************************************/
    U16 Loops = 0U;
    /* clear the raw and filter value buffer */
    for( Loops = 0U; Loops < (U16)SIG_AD_NUM; Loops++)
    {
        Sig_ADGlobal.RawValue[Loops] = 0U;
        Sig_ADGlobal.ResultCounter[Loops] = 0U;
        Sig_ADGlobal.ResultValue[Loops] = 0U;
    }

    Sig_ADGlobal.InitState = FALSE; /* set sig_adc module as initialized. */

    ADC_DeInit();	  
}

/***********************************************************************
*  Name        : Sig_ADTick
*  Description : Restart A/D conversion by tick time.   
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Sig_ADTick(void)
{
    /******************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local ROM-constants
    * - all function local variables (auto and static)
    *******************************************************************/
   
    U16 Index;
    ERR_TYPE ret;
    U16 RawValue =0xFFFFu;
    Sig_ADChannelConfigType ChannelConfig;

    /******************************************************************
    * FUNCTION CODE
    *******************************************************************/
    if(Sig_ADGlobal.InitState == FALSE)return;

    for(Index = 0u; Index< (U16)SIG_AD_NUM; Index++)
    {
        if(Sig_ADGlobal.FreezeReq[Index])
            continue;
       ChannelConfig = Sig_ADConfig[Index];

        ret = read_adsignal(ChannelConfig.Portnumb,ChannelConfig.DeviceType, &RawValue);
        if(ERR_OK==ret)
        {
            if(ChannelConfig.Damp ==TRUE)
            {
                 /*Sig_ADGlobal.RawValue[Signal] =RawValue;*/
            }
            else
            { 
                 Sig_ADGlobal.ResultValue[Index] = RawValue;
            }            
        }
        else
        {
            /*nothing todo*/
        }
    } 

    ADC_Conversion();
}

/***********************************************************************
*  Name        : Sig_ADGetRawValue
*  Description : Get AD value after debounce handler.   
*  Parameter   : None
*  Returns     : None
***********************************************************************/
U16 Sig_ADGetRawValue(U16 Signal)
{			
    return Sig_ADGlobal.RawValue[Signal];
}

/***********************************************************************
*  Name        : Sig_ADDirectGetValue
*  Description : Get current value   
*  Parameter   : Signal,pvalue
*  Returns     : ERR_TYPE
***********************************************************************/
U8 Sig_ADDirectGetValue(U16 Signal, U8* pvalue)
{
    U8 retVal = (U8)ERR_OK;
    if(pvalue == NULL)
    {
        retVal = (U8)ERR_VALUE;
    }
    else
    {
        U16 adVal = 0u;
        Sig_ADChannelConfigType ChannelConfig;
        ADC_Conversion();
        ChannelConfig = Sig_ADConfig[Signal];
        delay_us(4u);  /*conversion time need mor than 3.75us.*/
        ADC_GetValue((ADC_TYPE)(ChannelConfig.Portnumb),  &adVal);
        pvalue[0] = (U8)(adVal>>8);
        pvalue[1] = (U8)(adVal&0xFFu);
    }
    return retVal;
}

/***********************************************************************
*  Name        : Sig_ADDirectGetValue
*  Description : Get A/D value   
*  Parameter   : Signal,pvalue
*  Returns     : ERR_TYPE
***********************************************************************/
U8 Sig_ADGetValue(U16 Signal, U8* pvalue)
{
    U8 retVal = (U8)ERR_OK;
    if(pvalue == NULL)
    {
        retVal = (U8)ERR_VALUE;
    }
    else
    {
        U16 adVal;        
        adVal = Sig_ADGlobal.ResultValue[Signal];
        pvalue[0] = (U8)(adVal&0xFFu);
		pvalue[1] = (U8)(adVal>>8);
    }
    return retVal;
}

/***********************************************************************
*  Name        : Adc_Freeze
*  Description : Freeze all signals   
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Adc_Freeze(void)
{
    Sig_ADGlobal.InitState = FALSE; 
}

/***********************************************************************
*  Name        : Adc_UnFreeze
*  Description : Un-freeze all signals    
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Adc_UnFreeze(void)
{
    Sig_ADGlobal.InitState = TRUE; 
}

/***********************************************************************
*  Name        : Adc_FreezeSignal
*  Description :  Freeze a signal  
*  Parameter   : Signal
*  Returns     : None
***********************************************************************/
void Adc_FreezeSignal(U16 Signal)
{
    Sig_ADGlobal.FreezeReq[Signal]= TRUE; 
}

/***********************************************************************
*  Name        : Adc_UnFreezeSignal
*  Description :  Un-freeze a signal  
*  Parameter   : Signal
*  Returns     : None
***********************************************************************/
void Adc_UnFreezeSignal(U16 Signal)
{
    Sig_ADGlobal.FreezeReq[Signal]= FALSE; 
}

/***********************************************************************
*  Name        : read_adsignal
*  Description :    
*  Parameter   : number,devicetype,pvalue
*  Returns     : U8
***********************************************************************/
ERR_TYPE read_adsignal(U8 number, E_ADDeviceType devicetype, U16* pvalue)
{
    ERR_TYPE value = ERR_OK;

    if(devicetype==E_AD)
    {
        value =AD_READ((ADC_TYPE)number,pvalue);
    }

    return value;
}

/**************** END OF FILE *****************************************/


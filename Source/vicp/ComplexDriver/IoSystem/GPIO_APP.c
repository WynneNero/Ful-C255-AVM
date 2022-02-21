/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   : Shao Guangxian										   *
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
* 0.1    Jun 26,2016    PEI Jingli  Initial version
* ----------------------------------------------------------------------
* 0.2    Aug 01,2016   PEI Jingli  Add signal configuration
* ----------------------------------------------------------------------
* 0.3    Jan 05,2017   ShangQiuju Update GetVal function according SIG module update.
*------------------------------------------------------------------------
* 0.4    Jan 24,2017  ZhangJie  Fix Coverity warnings.
*-----------------------------------------------------------------------
* 0.5  Apr 01,2017   PEI Jingli  Fix headfiles.
*=====================================================================*/
#include "GPIO_APP.h"
#include "GPIO_IF.h"

#define GPIO_FILTER_COUNTER    10u

#define DIO_READ(x,y)      GPIO_GetVal(x,y)
#define DIO_SET(x,y)         GPIO_SetVal(x,y,TRUE)
#define DIO_CLEAR(x,y)     GPIO_SetVal(x,y,FALSE)
#define DIO_SETHiZ(x,y)    GPIO_SetInputMode(x,y,E_INPUT_HIZ)
#define DIO_CLRHiZ(x,y)    GPIO_SetOutputMode(x,y,E_PUSH_PULL,E_LOW_10MHZ)

static U8 Sig_DioSwFilterCount[SIG_DIO_IN_NUM] = 
{
  0  
};

static Sig_DioInData  Sig_DioInGlobal =
{
    FALSE,	
    { 0 },
    { 0 }, 
    { 0 },
    { 0 }
};

static Sig_DioOutData Sig_DioOutGlobal=
{
    FALSE,	
    { 0 },
    { 0 }
};

U8 read_signal(U8 iohnumber, U8 iolownumber, E_DioDeviceType devicetype);
void write_signal(U8 iohnumber, U8 iolownumber, E_DioDeviceType devicetype, U8 value);
void Set_signal_HiZ(U8 iohnumber, U8 iolownumber, E_DioDeviceType devicetype);
void Clr_signal_HiZ(U8 iohnumber, U8 iolownumber, E_DioDeviceType devicetype);
/*******************************************************************************************
* Description:		Initializes the Sig_Dio module.
* Service ID:		0x02
* Parameters:		None
* Return:			None
*   
********************************************************************************************/
void Sig_DioInit(void)
{
    /***************************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local ROM-constants
    * - all function local variables (auto and static)
    ****************************************************************************************/
    U16 Loops = 0U;
    /*U8* PtrFilterCnt;*/

    /***************************************************************************************
    * FUNCTION CODE
    ****************************************************************************************/
    /* check the module had initialized or not? */
    for( Loops = 0U; Loops < (U16)SIG_DIO_IN_NUM; Loops++)
    {
        Sig_DioInGlobal.RawValue[Loops] = 0U;
        Sig_DioInGlobal.ResultCounter[Loops] = 0U;
        Sig_DioInGlobal.ResultValue[Loops] = 0U;
        Sig_DioSwFilterCount[Loops] = GPIO_FILTER_COUNTER;
    }
    Sig_DioInGlobal.InitState = TRUE; /* set sig_adc module as initialized. */


    for( Loops = 0U; Loops < (U16)SIG_DIO_OUT_NUM; Loops++)
    {
        Sig_DioOutGlobal.RawValue[Loops] = 0U;
    }
    Sig_DioOutGlobal.InitState = TRUE; /* set sig_adc module as initialized. */
                              
}


/*******************************************************************************************
* Description:		de-Initializes the Sig_Dio module.
* Service ID:		0x02
* Parameters:		None
* Return:			None
*   
********************************************************************************************/
void Sig_DioDeInit(void)
{
    /***************************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local ROM-constants
    * - all function local variables (auto and static)
    ****************************************************************************************/
    U16 Loops = 0U;

    /***************************************************************************************
    * FUNCTION CODE
    ****************************************************************************************/
    /* check the module had initialized or not? */
    /* clear the raw and filter value buffer */
    for( Loops = 0U; Loops < (U16)SIG_DIO_IN_NUM; Loops++)
    {
        Sig_DioInGlobal.RawValue[Loops] = 0U;
        Sig_DioInGlobal.ResultCounter[Loops] = 0U;
        Sig_DioInGlobal.ResultValue[Loops] = 0U;
    }
    
    Sig_DioInGlobal.InitState = FALSE; /* set sig_adc module as initialized. */

    for( Loops = 0U; Loops < (U16)SIG_DIO_OUT_NUM; Loops++)
    {
        Sig_DioOutGlobal.RawValue[Loops] = 0U;
    }
    Sig_DioOutGlobal.InitState = FALSE; /* set sig_adc module as initialized. */
          
}

/*******************************************************************************************
* Description:		cyclic task of gpio module.
* Service ID:		0x02
* Parameters:		None
* Return:			None
*   
********************************************************************************************/
void Sig_DioTick(void)
{
    /***************************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local ROM-constants
    * - all function local variables (auto and static)
    ****************************************************************************************/

    U16 Index;
    U8 SigValue;
    U8 RawValue =0xffu;
    Sig_DioChannelInConfigType ChannelConfig;

    /***************************************************************************************
    * FUNCTION CODE
    ****************************************************************************************/
    /* check the module had initialized or not? */
    /*TODO:*/
    /*SIG_DIO_VALIDATE((TRUE == Sig_DioGlobal.InitState), 
							SIG_DIO_TICK_SERVICE_ID, SIG_DIO_E_UNINIT)*/

    if(Sig_DioInGlobal.InitState)
    {
        for(Index = 0u; Index< (U16)SIG_DIO_IN_NUM; Index++)
        {
            if(Sig_DioInGlobal.FreezeReq[Index])
            {
                Sig_DioInGlobal.ResultCounter[Index] = 0;
            }
            else
            {
                ChannelConfig = Sig_InConfig[Index];

                SigValue = read_signal(ChannelConfig.PortHnumb,ChannelConfig.PortLnumb,ChannelConfig.DeviceType);
                if(SigValue != SIG_DIO_READING_INVALID)
                {
                    RawValue = SigValue;
                    if(ChannelConfig.Damp ==TRUE)
                    {
                        if(RawValue != Sig_DioInGlobal.RawValue[Index])
                        {
                            Sig_DioInGlobal.ResultCounter[Index] = 0u;
                            Sig_DioInGlobal.RawValue[Index] = RawValue;
                        }
                        else
                        {
                            if(Sig_DioInGlobal.ResultCounter[Index]<255u)
                            {
                                Sig_DioInGlobal.ResultCounter[Index]++;
                                if(Sig_DioInGlobal.ResultCounter[Index] == Sig_DioSwFilterCount[Index])
                                {
                                    Sig_DioInGlobal.ResultValue[Index] = RawValue;   
                                }
                                else
                                {
                                    /*nothing to do*/
                                }
                            }
                            else
                            {
                                /*nothing to do*/
                            }
                        }
                    }
                    else
                    { 
                        Sig_DioInGlobal.ResultValue[Index] = RawValue; 
                    }
                }
                else
                {
                    /*nothing to do*/
                }
            }
        }      
    }
    else
    {
        /*nothing to do*/
    }
}

/*******************************************************************************************
* Description:		Sig_DioGetRawValue
* Service ID:		0x02
* Parameters:		Signal
* Return:			U8
********************************************************************************************/
U8 Sig_DioGetRawValue(U16 Signal)
{
    /***************************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local ROM-constants
    * - all function local variables (auto and static)
    ****************************************************************************************/

    /***************************************************************************************
    * FUNCTION CODE
    ****************************************************************************************/
    return Sig_DioInGlobal.RawValue[Signal];
}

/*******************************************************************************************
* Description:		Sig_DioGetValue
* Service ID:		0x02
* Parameters:		Signal,pvalue
* Return:			U8
********************************************************************************************/
U8 Sig_DioGetValue(U16 Signal, U8* pvalue)
{
	/***************************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local ROM-constants
    * - all function local variables (auto and static)
    ****************************************************************************************/
    ERR_TYPE ret=ERR_OK;
    /***************************************************************************************
    * FUNCTION CODE
    ****************************************************************************************/
    if(pvalue!=NULL)
    {
        *pvalue = Sig_DioInGlobal.ResultValue[Signal];
    }
    else
    {
        ret = ERR_VALUE;
    }
    return (U8)ret;

}

/*******************************************************************************************
* Description:		free the Sig_Do module.
* Service ID:		0x02
* Parameters:		None
* Return:			None
*   
********************************************************************************************/
void Dio_OutFreeze(void)
{
    Sig_DioOutGlobal.InitState = FALSE; 
}

/*******************************************************************************************
* Description:		unfree the Sig_Do module.
* Service ID:		0x02
* Parameters:		None
* Return:			None
*   
********************************************************************************************/
void Dio_OutUnFreeze(void)
{
    Sig_DioOutGlobal.InitState = TRUE; 
}

/*******************************************************************************************
* Description:		free the Sig_Di module.
* Service ID:		0x02
* Parameters:		None
* Return:			None
*   
********************************************************************************************/
void Dio_InFreeze(void)
{
    Sig_DioInGlobal.InitState = FALSE; 
}

/*******************************************************************************************
* Description:		unfree the Sig_Di module.
* Service ID:		0x02
* Parameters:		None
* Return:			None
*   
********************************************************************************************/
void Dio_InUnFreeze(void)
{
    Sig_DioInGlobal.InitState = TRUE; 
}

/*******************************************************************************************
* Description:		free the Sig_Di signal.
* Service ID:		0x02
* Parameters:		Signal
* Return:			None
********************************************************************************************/
void Di_FreezeSignal(U16 Signal)
{
    Sig_DioInGlobal.FreezeReq[Signal] = TRUE;
}

/*******************************************************************************************
* Description:		free the Sig_D0 signal.
* Service ID:		0x02
* Parameters:		Signal
* Return:			None
********************************************************************************************/
void Do_FreezeSignal(U16 Signal)
{
    Sig_DioChannelOutConfigType ChannelConfig;

    Sig_DioOutGlobal.FreezeReq[Signal] = TRUE;
    ChannelConfig = Sig_OutConfig[Signal];
    Set_signal_HiZ(ChannelConfig.PortHnumb,ChannelConfig.PortLnumb,ChannelConfig.DeviceType);
}

/*******************************************************************************************
* Description:		Unfree the Sig_Di signal.
* Service ID:		0x02
* Parameters:		Signal
* Return:			None
********************************************************************************************/
void Di_UnFreezeSignal(U16 Signal)
{
    Sig_DioInGlobal.FreezeReq[Signal] = FALSE;
}

/*******************************************************************************************
* Description:		Unfree the Sig_Do signal.
* Service ID:		0x02
* Parameters:		Signal
* Return:			None
********************************************************************************************/
void Do_UnFreezeSignal(U16 Signal)
{
    Sig_DioChannelOutConfigType ChannelConfig;

    Sig_DioOutGlobal.FreezeReq[Signal] = FALSE;
    ChannelConfig = Sig_OutConfig[Signal];
    Clr_signal_HiZ(ChannelConfig.PortHnumb,ChannelConfig.PortLnumb,ChannelConfig.DeviceType);
}

/*******************************************************************************************
* Description:		get raw value
* Service ID:		0x02
* Parameters:		Signal
* Return:			U8
*   
********************************************************************************************/
U8 Sig_DioGetOutRawValue(U16 Signal)
{
    return Sig_DioOutGlobal.RawValue[Signal];
}

/*******************************************************************************************
* Description:		write value to output pin
* Service ID:		0x02
* Parameters:		signal,value
* Return:			None
*   
********************************************************************************************/
void Sig_DioWriteValue(U16 Signal, U8* value)
{
    Sig_DioChannelOutConfigType ChannelConfig;
    if(Sig_DioOutGlobal.InitState == FALSE ) return;

    ChannelConfig = Sig_OutConfig[Signal];
    Sig_DioOutGlobal.RawValue[Signal]=*value;
    write_signal(ChannelConfig.PortHnumb,ChannelConfig.PortLnumb,ChannelConfig.DeviceType, *value);
}
/*******************************************************************************************
* Description:		Get direct value
* Service ID:		0x02
* Parameters:		Signal,pvalue
* Return:			U8
********************************************************************************************/
U8 Sig_DioGetDirectValue(U16 Signal, U8* pvalue)
{
    /***************************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local ROM-constants
    * - all function local variables (auto and static)
    ****************************************************************************************/

    /***************************************************************************************
    * FUNCTION CODE
    ****************************************************************************************/
    Sig_DioChannelInConfigType ChannelConfig;
    ERR_TYPE ret=ERR_OK;
    if(pvalue != NULL)
    {
        ChannelConfig = Sig_InConfig[Signal];
        *pvalue =read_signal(ChannelConfig.PortHnumb,ChannelConfig.PortLnumb,ChannelConfig.DeviceType);
    }
    else
    {
        ret = ERR_VALUE;
    }
    return (U8)ret;
}


/*******************************************************************************************
* Description:		read signal
* Service ID:		0x02
* Parameters:		iohnumber,iolownumber,devicetype
* Return:			U8
********************************************************************************************/
U8 read_signal(U8 iohnumber, U8 iolownumber, E_DioDeviceType devicetype)
{
    U8 value =SIG_DIO_VALUE_INVALID;
    if(devicetype==E_DIO)
    {
        value =DIO_READ(iohnumber,iolownumber);
    }
    return value;
}


/*******************************************************************************************
* Description:		read signal
* Service ID:		0x02
* Parameters:		iohnumber,iolownumber,devicetype
* Return:			None
*   
********************************************************************************************/
void write_signal(U8 iohnumber, U8 iolownumber, E_DioDeviceType devicetype, U8 value)
{
    if(devicetype==E_DIO)
    {
        if(value!=0u)
        {
            DIO_SET(iohnumber,iolownumber);
        }
        else
        {
            DIO_CLEAR(iohnumber,iolownumber);
        }
    }
}


/*******************************************************************************************
* Description:		Clr_signal_HiZ
* Service ID:		0x02
* Parameters:		iohnumber,iolownumber,devicetype
* Return:			None
*   
********************************************************************************************/
void Clr_signal_HiZ(U8 iohnumber, U8 iolownumber, E_DioDeviceType devicetype)
{
    if(devicetype==E_DIO)
    {
        DIO_CLRHiZ(iohnumber, iolownumber);
    }
}

/*******************************************************************************************
* Description:		Set_signal_HiZ
* Service ID:		0x02
* Parameters:		iohnumber,iolownumber,devicetype
* Return:			None
*   
********************************************************************************************/
void Set_signal_HiZ(U8 iohnumber, U8 iolownumber, E_DioDeviceType devicetype)
{
    if(devicetype==E_DIO)
    {
        DIO_SETHiZ(iohnumber, iolownumber);
    }
}

/**************** END OF FILE *****************************************/


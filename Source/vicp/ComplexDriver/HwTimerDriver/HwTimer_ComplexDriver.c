/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.		                         	      *
*				  All Rights Reserved.          			                         		      *
*   Department : CT AD     							                      	            *
*   AUTHOR	   : 									                                        *
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
* ----------------------------------------------------------------------
* 0.1  Feb 20,2016    PEI Jingli  Initial version
* ----------------------------------------------------------------------
* 0.2  Mar 21,2017    PEI Jingli  Fixed enum.
*=====================================================================*/
#include "define.h"
#include "TimerUnit_if.h"
#include "HwTimer_ComplexDriver.h"
#include "Driver_if.h"


/***********************************************************************
*  Name        : HwTimer_ComplexDriver_Init
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void HwTimer_ComplexDriver_Init(void)
{

}

/***********************************************************************
*  Name        : HwTimer_ComplexDriver_DeInit
*  Description :
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void HwTimer_ComplexDriver_DeInit(void)
{

}

/***********************************************************************
*  Name        : HwTimer_ComplexDriver_IOControl
*  Description : control handler for service   
*  Parameter   : type E_DEV_START, E_DEV_STOP
*                      buffer structure:
*       E_DEV_START, ST_HWTIMER_DIVICE_PARAM
*       E_DEV_STOP,   ST_DIVICE_CHANNEL
*  Returns     : U8
***********************************************************************/
U8 HwTimer_ComplexDriver_IOControl(U8 type, void* buffer)
{
    U8 bRet=ERR_FAILED;

    if(NULL==buffer)
        bRet =ERR_VALUE;
    else
    {
        switch(type) 
        {
        case E_DEV_START:
        {
            ST_HWTIMER_DEVICE_PARAM *timerParam=(ST_HWTIMER_DEVICE_PARAM *)buffer;
            if(ERR_OK==TAU_Timer_Config(timerParam->timerChannel.un, timerParam->timerChannel.chm, timerParam->timerMs, timerParam->bWaveOutput, timerParam->bPeriodic))
            {
                if(TAU_Timer_Cmd(timerParam->timerChannel.un, timerParam->timerChannel.chm, (FUNCTION_STATE)TRUE))
                    bRet=ERR_OK;
            }
        }
        break;
        case E_DEV_STOP:
        {
            ST_DEVICE_CHANNEL *timerChannel=(ST_DEVICE_CHANNEL *)buffer;
            if(TAU_Timer_Cmd(timerChannel->un, timerChannel->chm, (FUNCTION_STATE)FALSE))
                bRet=ERR_OK;
        }
        break;
        default:break;
        }
    }
    
    return bRet;
}

/**************** END OF FILE *****************************************/


/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.		                         	      *
*				  All Rights Reserved.          			                         		      *
*   Department : CT AD     							                      	            *
*   AUTHOR	   : 									                                        *
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   : user pwmd configration
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
* ----------------------------------------------------------------------
* 0.1    Jan 03,2017  PEI Jingli  Initial version.
* ----------------------------------------------------------------------
* 0.2    Jan 10,2017  PEI Jingli  Change initial functions.
*----------------------------------------------------------------------
* 0.3  Jan 16,2017     RenWeimin  Add test code.
*------------------------------------------------------------------------
* 0.4  Jan 24,2017     ZhangJie  Fix Coverity warnings.
* ----------------------------------------------------------------------
* 0.5  Feb 09,2017    PEI Jingli  Interfaces restruction
* ----------------------------------------------------------------------
* 0.6  Mar 21,2017    PEI Jingli  Fixed enum.
*------------------------------------------------------------------------
* 0.7   Apr 01,2017   PEI Jingli  Fix headfile included.
*=====================================================================*/
#include "Pwmd_if.h"
#include "Pwmd_ComplexDriver.h"
#include "Driver_if.h"

/*module initial state*/
static BOOL bInitState=FALSE;

/***********************************************************************
*  Name        : Pwmd_ComplexDriver_Init
*  Description : Calls PWMD driver initial, and configrature channels used.
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Pwmd_ComplexDriver_Init(void)
{
    /*pwmd module init*/
    PWMD_Unit_Init();
    bInitState =TRUE;
}

/***********************************************************************
*  Name        : Pwmd_ComplexDriver_DeInit
*  Description : de-Initializes the PWMD.   
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Pwmd_ComplexDriver_DeInit(void)
{
    bInitState =FALSE;
    PWMD_Unit_Deinit();
}

/***********************************************************************
*  Name        : Pwmd_ComplexDriver_Control
*  Description : pwm control handler for service   
*  Parameter   : type E_DEV_START, E_DEV_STOP, E_DEV_SETDUTY
*                      buffer structure:
*       E_DEV_START, pwm channel:1B +ratio:2B + duty:2B
*       E_DEV_STOP,   pwm channel:1B 
*       E_DEV_SETDUTY, pwm channel:1B +ratio:2B+duty:2B
*            pwm channel range to  PWM_CHANNEL_MAX
*  Returns     : U8
***********************************************************************/
U8 Pwmd_ComplexDriver_IOControl(U8 type, void* buffer)
{
    U8 bRet=ERR_FAILED;
    U8 *param= (U8*)buffer;

    if(NULL==buffer)
        bRet =ERR_VALUE;
    else if(!bInitState)
        bRet =ERR_DISABLED;
    else
    {
        switch(type)
        {
        case E_DEV_START:
        {
            U16 dutytype=(U16)(param[1]<<8)+(param[2]);
            U16 duty =(U16)(param[3]<<8)+param[4];
            if(ERR_OK==PWMD_Config(*param, (Enum_PwmdRatio_Type)dutytype, duty))
            {
                if(PWMD_Cmd(*param, (FUNCTION_STATE)TRUE))
                    bRet=ERR_OK;
            }
        }
        break;
        case E_DEV_STOP:
            if(PWMD_Cmd(*param, (FUNCTION_STATE)FALSE))
                bRet=ERR_OK;
        break;
        case E_DEV_SETDUTY:
        {
            U16 dutytype=(U16)(param[1]<<8)+param[2];
            U16 duty =(U16)(param[3]<<8)+param[4];
            bRet=PWMD_SetDuty( *param, (Enum_PwmdRatio_Type)dutytype, duty);
        }
        break;
        default:break;
        }
    }
    
    return bRet;
}

/**************** END OF FILE *****************************************/


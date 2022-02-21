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
* 0.1    Feb 20,2017  PEI Jingli  Initial version.
* ----------------------------------------------------------------------
* 0.2   Mar 21,2017   PEI Jingli  Fixed enum.
*=====================================================================*/
#include "define.h"
#include "TimerUnit_if.h"
#include "TauPwm_ComplexDriver.h"
#include "Driver_if.h"

/***********************************************************************
*  Name        : Pwmd_ComplexDriver_Init
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void TauPwm_ComplexDriver_Init(void)
{
    /*pwmd module init*/

}

/***********************************************************************
*  Name        : Pwmd_ComplexDriver_DeInit
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void TauPwm_ComplexDriver_DeInit(void)
{
}

/***********************************************************************
*  Name        : Pwmd_ComplexDriver_Control
*  Description : pwm control handler for service   
*  Parameter   : type E_DEV_START, E_DEV_STOP, E_DEV_SETDUTY
*                      buffer structure:
*       E_DEV_START, ST_PWM_DIVICE_PARAM
*       E_DEV_STOP,   ST_PWM_DIVICE_CHANNEL
*       E_DEV_SETDUTY, ST_PWM_DIVICE_CHANGEDUTY
*  Returns     : U8
***********************************************************************/
U8 TauPwm_ComplexDriver_IOControl(U8 type, void* buffer)
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
            ST_PWM_DEVICE_PARAM *pwmParam=(ST_PWM_DEVICE_PARAM *)buffer;
            if(ERR_OK==TAU_PWM_Config(pwmParam->pwm.un, pwmParam->pwm.chm, pwmParam->pwm.sl_chm, pwmParam->freHZ, pwmParam->ratioType,pwmParam->duty))
            {
                if(TAU_PWM_Cmd(pwmParam->pwm.un, pwmParam->pwm.chm, pwmParam->pwm.sl_chm, (FUNCTION_STATE)TRUE))
                    bRet=ERR_OK;
            }
        }  
        break;
        case E_DEV_STOP:
        {
            ST_PWM_DEVICE_CHANNEL *pwm=(ST_PWM_DEVICE_CHANNEL *)buffer;
            if(TAU_PWM_Cmd(pwm->un, pwm->chm, pwm->sl_chm, (FUNCTION_STATE)FALSE))
                bRet=ERR_OK;
        }
        break;
        case E_DEV_SETDUTY:
        {
            ST_PWM_DEVICE_CHANGEDUTY *dutyParam=(ST_PWM_DEVICE_CHANGEDUTY *)buffer;
            bRet=TAU_PWM_SetDuty( dutyParam->pwm.un, dutyParam->pwm.chm, dutyParam->pwm.sl_chm, dutyParam->ratioType, dutyParam->duty);
        }
        break;
        default:break;
        }
    }
    
    return bRet;
}

/**************** END OF FILE *****************************************/


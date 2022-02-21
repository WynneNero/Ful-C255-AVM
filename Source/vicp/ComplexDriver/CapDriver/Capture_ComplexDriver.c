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
* 0.1  Feb 09,2017    PEI Jingli  Initial version.
* ----------------------------------------------------------------------
* 0.2  Mar 21,2017    PEI Jingli  Fixed enum.
*=====================================================================*/
#include "define.h"
#include "TimerUnit_if.h"
#include "Capture_ComplexDriver.h"
#include "Driver_if.h"


/***********************************************************************
*  Name        : Capture_ComplexDriver_Init
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Capture_ComplexDriver_Init(void)
{
}

/***********************************************************************
*  Name        : Capture_ComplexDriver_DeInit
*  Description : de-Initializes
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Capture_ComplexDriver_DeInit(void)
{
}

/***********************************************************************
*  Name        : Capture_ComplexDriver_IOControl
*  Description : control handler for service   
*  Parameter   : type E_PWM_START, E_PWM_STOP
*                      buffer structure:
*       E_DEV_START, ST_CAP_DIVICE_PARAM
*       E_DEV_STOP,   ST_DIVICE_CHANNEL
*  Returns     : U8
***********************************************************************/
U8 Capture_ComplexDriver_IOControl(U8 type, void* buffer)
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
              ST_CAP_DEVICE_PARAM *capParam=(ST_CAP_DEVICE_PARAM *)buffer;
              if(ERR_OK==TAU_Capture_Config(capParam->capChannel.un, capParam->capChannel.chm, capParam->edge))
              {
                  if(TAU_Capture_Cmd(capParam->capChannel.un, capParam->capChannel.chm, (FUNCTION_STATE)TRUE))
                      bRet=ERR_OK;
              }
          }
          break;
          case E_DEV_STOP:
          {
              ST_DEVICE_CHANNEL *capChannel=(ST_DEVICE_CHANNEL *)buffer;
              if(TAU_Capture_Cmd(capChannel->un,capChannel->chm, (FUNCTION_STATE)FALSE))
                  bRet=ERR_OK;
          }
          break;
          default:break;
        }
    }
    
    return bRet;
}

/**************** END OF FILE *****************************************/


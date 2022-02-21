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
* 0.1    Jan 05,2016                       Initialize
* ----------------------------------------------------------------------
* 0.2    Jan 05,2017    ZhangJie  Delete test code for TRACE_ENABLE/STACK_CHECK test 
*------------------------------------------------------------------------
* 0.3    Jan 24,2017  ZhangJie  Fix Coverity warnings.
*=====================================================================*/
#include<Core_I.h>
#include <Service_HOOKS.h>
#include <Tools.h>
#include "Sysswitch.h"


/*---Global-----------------------------------------------------------*/
STATIC U8 SysSwitch_u8PreState = SYS_S0; 
STATIC U8 SysSwitch_u8CurrentState = SYS_S0; 
STATIC U8 SysSwitch_u8RequestState;
STATIC BOOL SysSwitch_bSwitching;

extern void  SysState_SwitchProc(U8 fromindex, U8 toindex);

/***********************************************************************
*  Name        : SysSwitch_Init
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void  SysSwitch_Init(void)
{
  SysSwitch_u8PreState = SYS_S0; 
  SysSwitch_u8CurrentState = SYS_S0; 
  SysSwitch_u8RequestState=SYS_S0;
  SysSwitch_bSwitching=FALSE;
}


/***********************************************************************
*  Name        : SysSwitch_Deinit
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void  SysSwitch_Deinit(void)
{
  SysSwitch_u8PreState = SYS_S0; 
  SysSwitch_u8CurrentState = SYS_S0; 
  SysSwitch_u8RequestState=SYS_S0;
}


/***********************************************************************
*  Name        : SysSwitch_IsSwitching
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL  SysSwitch_IsSwitching(void)
{
 return SysSwitch_bSwitching;
}
/***********************************************************************
*  Name        : SysSwitch_GetCurrentState
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
U8  SysSwitch_GetCurrentState(void)
{
   U8 state =SYS_S0;

   OSAPI_LockSchedule();
   state=SysSwitch_u8CurrentState;
   OSAPI_UnlockSchedule();

   return state;
}

/***********************************************************************
*  Name        : SysSwitch_IsrGetCurrentState
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
U8 SysSwitch_IsrGetCurrentState(void)
{
 return SysSwitch_u8CurrentState;
}

/***********************************************************************
*  Name        : SysSwitch_GetPrevState
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
U8  SysSwitch_GetPrevState(void)
{

   U8 state =SYS_S0;

   OSAPI_LockSchedule();
   state=SysSwitch_u8PreState;
   OSAPI_UnlockSchedule();

   return state;
}

/***********************************************************************
*  Name        : SysSwitch_RequestSwitch
*  Description : system state switch, the function should be called in system state module        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
//void  systemstate(U8 newState)
void  SysSwitch_RequestSwitch(U8 newState)
{
    BOOL isOK =FALSE;
    if(newState<(U8)SYS_CFG_NO_OF_SYSTEM_STATES)
    {
        OSAPI_LockSchedule();
        if(SysSwitch_u8CurrentState!=newState)
        {
            if(SysSwitch_u8RequestState!= newState)
            {
                SysSwitch_u8RequestState= newState;
                isOK=TRUE;
            }

            OSAPI_UnlockSchedule();
            if(isOK==TRUE)
            {
                OSAPI_ActiveTask((U8)OSAPI_SYSTEMSWITCHLOW);
            }
            else {}
        }
        else
        {
            OSAPI_UnlockSchedule();
        }
    }
    else {}
}


/***********************************************************************
*  Name        : SysSwitch_HighTaskEntry
*  Description : None       
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysSwitch_HighTaskEntry(void)
{
    U8 fromState=0u;
    U8 toState =0u;
    OSAPI_LockSchedule();
				 
    /* Search the actual requested system state with the highest level. */
    if(SysSwitch_u8RequestState != SysSwitch_u8CurrentState)
    {
        SysSwitch_bSwitching=TRUE;
        SysSwitch_u8PreState=SysSwitch_u8CurrentState;
        SysSwitch_u8CurrentState=SysSwitch_u8RequestState;
        fromState=SysSwitch_u8PreState;
        toState =SysSwitch_u8CurrentState;
        OSAPI_UnlockSchedule();
        /*state has changed, call switch function*/
        SysState_SwitchProc(fromState,toState);

#if(SERVICE_HOOKS_EN==1u)
        SERVICE_SWITCH_HOOK(fromState, toState);	
#endif	

        OSAPI_LockSchedule();
        SysSwitch_bSwitching=FALSE;
        OSAPI_UnlockSchedule();
    }
    else
    {
        OSAPI_UnlockSchedule();
    }
	   
    	OSAPI_TerminateTask();	
}

/***********************************************************************
*  Name        : SysSwitch_LowTaskEntry
*  Description : None       
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysSwitch_LowTaskEntry(void)
{
	/***************************************************************************************
	* FUNCTION CODE
	****************************************************************************************/
	OSAPI_LockSchedule();	
    if(SysSwitch_u8RequestState != SysSwitch_u8CurrentState)
    {
        OSAPI_UnlockSchedule();
        OSAPI_ActiveTask((U8)OSAPI_SYSTEMSWITCHHIGH);
    }
    else
    {
        OSAPI_UnlockSchedule();
        /* Do nothing */
    }	
    OSAPI_TerminateTask();
}
/**************** END OF FILE *****************************************/


/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                     *
*                 All Rights Reserved.                                          *
*   Department : CT AD                                                  *
*   AUTHOR     :                                                        *
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
*------------------------------------------------------------------------
* 0.1          Jun 11,2016                  Init version.
*------------------------------------------------------------------------
* 0.2          Aug 01,2016            re-structure 
*------------------------------------------------------------------------
* 0.3          Jan 24,2017  ZhangJie  Fix Coverity warnings.
*=====================================================================*/
#include <Service_HOOKS.h>
#include <Tools.h>
#include <SystemState_Cfg.h>
#include "SystemState.h"

extern void SysState_apResetContainer(void);

/***********************************************************************
*  Name        : SysState_ResetProc
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysState_ResetProc(void)
{
    SysState_apResetContainer();
}

#if(SYSTEM_STATE_METHOD==SYSSTATE_FULLSTATE)
extern const Func_Void_Proc SysState_apToS0[];
extern const Func_Void_Proc SysState_apToS1[];
extern const Func_Void_Proc SysState_apToS2[];
extern const Func_Void_Proc SysState_apToS3[];
extern const Func_Void_Proc SysState_apToS4[];
extern const Func_Void_Proc SysState_apToS5[];
extern const Func_Void_Proc SysState_apToS6[];
extern const Func_Void_Proc SysState_apToS7[];

/***********************************************************************
*  Name        : SysState_Init
*  Description : system state switch
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysState_Init(void)
{

}

/***********************************************************************
*  Name        : SysState_DeInit
*  Description : system state switch
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysState_DeInit(void)
{

}

/***********************************************************************
*  Name        : SysState_SetRequest
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysState_SetRequest(U8 StateId)
{
    SysSwitch_RequestSwitch(StateId);
}


/***********************************************************************
*  Name        : SysState_ClearRequest
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysState_ClearRequest(U8 StateId)
{

}

/***********************************************************************
*  Name        : SysState_SwitchProc
*  Description : system state switch
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void  SysState_SwitchProc(U8 fromindex, U8 toindex)
{

    switch(toindex)
    {
        case SYS_S0:
            if(SysState_apToS0[fromindex]!=NULL)
            {
                SysState_apToS0[fromindex]();
            }
            break;
        case SYS_S1:
            if(SysState_apToS1[fromindex]!=NULL)
            {
                SysState_apToS1[fromindex]();
            }
            break;
        case SYS_S2:
            if(SysState_apToS2[fromindex]!=NULL)
            {
                SysState_apToS2[fromindex]();
            }
            break;
        case SYS_S3:
            if(SysState_apToS3[fromindex]!=NULL)
            {
                SysState_apToS3[fromindex]();
            }
            break;
        case SYS_S4:
            if(SysState_apToS4[fromindex]!=NULL)
            {
                SysState_apToS4[fromindex]();
            }
            break;
        case SYS_S5:
            if(SysState_apToS5[fromindex]!=NULL)
            {
                SysState_apToS5[fromindex]();
            }
            break;
        case SYS_S6:
            if(SysState_apToS6[fromindex]!=NULL)
            {
                SysState_apToS6[fromindex]();
            }
            break;
        case SYS_S7:
            if(SysState_apToS7[fromindex]!=NULL)
            {
                SysState_apToS7[fromindex]();
            }
            break;
        default:
            break;
    }
}
#elif (SYSTEM_STATE_METHOD==SYSSTATE_UPDOWNSTATE)

U8 SearchState(void);
BOOL SwitchState(U8 CurrentState ,U8 DestinationState);

extern const Func_Void_Proc SysState_apInit[];
extern const Func_Void_Proc SysState_apDeInit[];

const U8 SysState_au8StateMask[SYSSTATE_STATE_NUMBER]=
{
    SYSSTATE_INIT_OF_STATE_IDENT_ARRAY
};

U8 SysState_au8StateIdent[SYSSTATE_STATE_NUMBER]; /*TODO: change bit operate*/
VOLATILE U16 SysState_u16LockStateCntr;
/***********************************************************************
*  Name        : SysState_Init
*  Description : system state switch
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysState_Init(void)
{
    for(int i=0; i<SYSSTATE_STATE_NUMBER; i++)SysState_au8StateIdent[i]=0u;
    SysState_u16LockStateCntr=0u;
}

/***********************************************************************
*  Name        : SysState_DeInit
*  Description : system state switch
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysState_DeInit(void)
{

}

/*CAUTION: the following function is not tested and not suggestion to use*/
/***********************************************************************
*  Name        : SysState_LockState
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void  SysState_LockState(void)
{
    OSAPI_LockSchedule();
    SysState_u16LockStateCntr++;
    OSAPI_UnlockSchedule();
}

/***********************************************************************
*  Name        : SysState_UnlockState
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void  SysState_UnlockState(void)
{
    U8 DestinationState;
    U8 CurrentState;

    OSAPI_LockSchedule();
    if(SysState_u16LockStateCntr>0u)SysState_u16LockStateCntr--;

    if((SysState_u16LockStateCntr==0u))/*TODO: check if should check SysSwitch_IsSwitching*/
    {
        CurrentState=SysSwitch_GetCurrentState();
        DestinationState=SearchState();
        OSAPI_UnlockSchedule();

        if(DestinationState!=CurrentState)
        {
            SwitchState(CurrentState,DestinationState);
        }
        else
        {
        }
    }
    else
    {
        OSAPI_UnlockSchedule();
    }
}

/***********************************************************************
*  Name        : SysState_SetRequest
*  Description : system state switch
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysState_SetRequest(U8 StateId)
{
    U8 DestinationState;
    U8 CurrentState;

    OSAPI_LockSchedule();
    SysState_au8StateIdent[StateId]=1u;
    CurrentState=SysSwitch_GetCurrentState();
    DestinationState=SearchState();
    OSAPI_UnlockSchedule();

    if(DestinationState>CurrentState)
    {
        SwitchState(CurrentState,DestinationState);
    }
    else
    {
    }
}

/***********************************************************************
*  Name        : SysState_ClearRequest
*  Description : system state switch
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysState_ClearRequest(U8 StateId)
{
    U8 DestinationState;
    U8 CurrentState;

    OSAPI_LockSchedule();
    SysState_au8StateIdent[StateId]=0u;
    CurrentState=SysSwitch_GetCurrentState();
    DestinationState=SearchState();
    OSAPI_UnlockSchedule();
    if(DestinationState<CurrentState)
    {
        SwitchState(CurrentState,DestinationState);
    }
    else
    {
    }
}

/***********************************************************************
*  Name        : SysState_SwitchProc
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void  SysState_SwitchProc(U8 fromindex, U8 toindex)
{
    while(toindex != fromindex)
    {
        if(toindex > fromindex)
        {

            if(SysState_apInit[fromindex]!=NULL)
            {
                SysState_apInit[fromindex]();
            }

            fromindex++;
        }
        else
        {
            fromindex--;
            if(SysState_apDeInit[fromindex]!=NULL)
            {
                SysState_apDeInit[fromindex]();
            }
        }
    }
}


/***********************************************************************
*  Name        : SwitchState
*  Description : system state switch
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL SwitchState(U8 CurrentState ,U8 DestinationState)
{
    BOOL isOK =FALSE;

    if(DestinationState == CurrentState)
    {
        return isOK;
    }
    else
    {
        if(DestinationState < CurrentState)
        {
            if((CurrentState-DestinationState)<=SYSSTATE_MULTI_SWITCH_MAXNUM)
            {

                SysSwitch_RequestSwitch(DestinationState);
            }
            else
            {
                /* Do nothing */
                SYSSTATE_HANDLER_ACTIVATIVATION_EXCEPTION();
            }
        }
        else
        {
            if((DestinationState-CurrentState)<=SYSSTATE_MULTI_SWITCH_MAXNUM)
            {
                SysSwitch_RequestSwitch(DestinationState);
            }
            else
            {
                /* Do nothing */
                SYSSTATE_HANDLER_ACTIVATIVATION_EXCEPTION();
            }
        }
    }
    return isOK;
}

/***********************************************************************
*  Name        : SearchState
*  Description : system state switch
*  Parameter   : None
*  Returns     : None
***********************************************************************/
U8 SearchState(void)
{
    U8 i;
    OSAPI_LockSchedule();
    for(i = SYSSTATE_STATE_NUMBER; (i > 0u) && (SysState_au8StateIdent[i] == (U8)0u); i--)
    {
        /* Do nothing */
    }
    OSAPI_UnlockSchedule();
    return SysState_au8StateMask[i];
}
#endif

/**************** END OF FILE *****************************************/


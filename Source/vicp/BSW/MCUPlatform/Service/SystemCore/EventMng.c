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
* 0.1    Jan 05,2016                      Initialize
* ----------------------------------------------------------------------
* 0.2    Jan 05,2017    ZhangJie  Delete test code for TRACE_ENABLE test 
*------------------------------------------------------------------------
* 0.3    Jan 24,2017    ZhangJie  Fix Coverity warnings.
*------------------------------------------------------------------------
* 0.4    Apr 04,2017   PEI Jingli  Fix headfile included.
*=====================================================================*/
#include "Define.h"
#include <Service_HOOKS.h>
#include <Tools.h>
#include "EVENTMNG.H"
#include "OSAPI.h"


U8 GetRequestEvent(void);

#define EVENT_PASS_2
#include "EVENTMNG_DEF.H"

#define EVENT_PASS_3
#include "EVENTMNG_DEF.H"


/*#define EVT_ACTIVE_TIMES   0x03u*/

STATIC BOOL SysEvt_abActive[SYSEVT_EVENT_MAX];/*The last number for SWP TEST*/
STATIC BOOL SysEvt_bEvtInited;


/***********************************************************************
*  Name        : SysEvt_Init
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysEvt_Init(void)
{

    U8 Index = 0u;
    SysEvt_bEvtInited=TRUE;

    for(Index = 0u; Index < SYSEVT_EVENT_MAX; Index++)
    {
        SysEvt_abActive[Index]= FALSE;
    }
}

/***********************************************************************
*  Name        : SysEvt_Deinit
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysEvt_Deinit(void)
{
    SysEvt_bEvtInited=FALSE;
}


/***********************************************************************
*  Name        : SysEvt_TaskEntry
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysEvt_TaskEntry(void)
{	
    for(;;)
    {
        U8 msgret=0u;
        U8 Evtid=SYSEVT_EVENT_MAX;
        Evtid = GetRequestEvent();
	
        if(Evtid==SYSEVT_EVENT_MAX)
        {
            OSAPI_WaitingTask((U8)OSAPI_EVENTTASK,OSADP_WAIT_NOTIMEOUT,&msgret);

            if(msgret==OSAPI_TERMINATETASK)
            {
                break;
            }
            else
            {
                /*do nothing*/
            }
        }
        else
        {
            if(SysEvt_bEvtInited==TRUE)
            {
#if( SERVICE_HOOKS_EN==1u)
                SERVICE_EVENT_HOOK(Evtid);
#endif

#if (TASKMONITOR_EN ==1u)
                OSWDG_StartMonitor((U8)OSAPI_EVENTTASK);
#endif
                if(SysEvt_apEventProc[Evtid]!=NULL)
                {
                    /*Lib_RunContainer((Func_Void_Proc *)&(SysEvt_apEventProc[Evtid][0]));*/
                    SysEvt_apEventProc[Evtid]();
                }
#if (TASKMONITOR_EN ==1u)
                OSWDG_StopMonitor((U8)OSAPI_EVENTTASK);
#endif
            }
            else
            {
                /*do nothing*/
            }
        }
    }
}


/***********************************************************************
*  Name        : SysEvt_IsrSetEvent
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysEvt_IsrSetEvent(U8 Evtid)
{
    if(Evtid<SYSEVT_EVENT_MAX)
    {
        SysEvt_abActive[Evtid]=TRUE;
    }

    OSAPI_IsrActiveTask((U8)OSAPI_EVENTTASK);
}

/***********************************************************************
*  Name        : SysEvt_SetEvent
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysEvt_SetEvent(U8 Evtid)
{
    OSAPI_LockSchedule();
    if(Evtid<SYSEVT_EVENT_MAX)
    {
        SysEvt_abActive[Evtid]=TRUE;
    }
    else
    {
        /*  TODO: Add error log*/
    }
    OSAPI_UnlockSchedule();
    OSAPI_ActiveTask((U8)OSAPI_EVENTTASK);
}


/***********************************************************************
*  Name        : GetRequestEvent
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
U8 GetRequestEvent(void)
{
    U8 i=0u;
    U8 Evtid =SYSEVT_EVENT_MAX;

    OSAPI_LockSchedule();
    for(i=0u; i<SYSEVT_EVENT_MAX; i++)
    {
        if(SysEvt_abActive[i]==TRUE)
        {
            Evtid=i;
            SysEvt_abActive[i]=FALSE;
            break;
        }
    }
    OSAPI_UnlockSchedule();

    return Evtid;
}
/**************** END OF FILE *****************************************/


/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                         *
*   AUTHOR     :                                       *
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
* 0.2    Jan 05,2017    ZhangJie  Delete test code for TRACE_ENABLE test 
*------------------------------------------------------------------------
* 0.3    Jan 24,2017  ZhangJie  Fix Coverity warning.
*=====================================================================*/
#include<Core_I.h>
#include <Service_HOOKS.h>
#include <Tools.h>
#include "JOBMNG.H"

U8 GetRequestJob(void);

#define JOB_PASS_2
#include "JobMng_def.h"

#define JOB_PASS_3
#include "JobMng_def.h"

STATIC BOOL SysJob_abActive[SYSJOB_JOB_MAX];/*the last number is for SWP TEST*/
STATIC U8  SysJob_au8DelayTimer[SYSJOB_JOB_MAX];

STATIC BOOL SysJob_bInited;


/*---Global-----------------------------------------------------------*/
/***********************************************************************
*  Name        : SysJob_TaskEntry
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysJob_TaskEntry(void)
{
    /***************************************************************************************
    * FUNCTION CODE
    ****************************************************************************************/
    for(;;)
    {
        U8 msgret=0u;
        U8 jobId =SYSJOB_JOB_MAX;
        jobId = GetRequestJob();

        if(jobId==SYSJOB_JOB_MAX)
        {
            OSAPI_WaitingTask((U8)OSAPI_SLOWJOBTASK,OSADP_WAIT_NOTIMEOUT,&msgret);
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
            if(SysJob_bInited==TRUE)
            {
#if(SERVICE_HOOKS_EN==1u)
                SERVICE_JOB_HOOK(jobId);
#endif

#if (TASKMONITOR_EN ==1u)
                OSWDG_StartMonitor((U8)OSAPI_SLOWJOBTASK);
#endif
                if(SysJob_apProc[jobId]!=NULL)
                {
                    SysJob_apProc[jobId]();
                }
#if (TASKMONITOR_EN ==1u)
                OSWDG_StopMonitor((U8)OSAPI_SLOWJOBTASK);
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
*  Name        : SysJob_JobAlarm
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysJob_JobAlarm(void)
{
    BOOL isRestart =FALSE;
    U8 i=0u;

    if(SysJob_bInited==TRUE)
    {
        for(i=0u; i<(U8)SYSJOB_JOB_MAX; i++)
        {
            if(SysJob_au8DelayTimer[i]>0u)
            {
                SysJob_au8DelayTimer[i]--;
                if(SysJob_au8DelayTimer[i]==0u)
                {
                    isRestart= TRUE;
                    SysJob_abActive[i]=TRUE;
                }
            }
        }
        if(isRestart==TRUE)
        {
            OSAPI_IsrActiveTask((U8)OSAPI_SLOWJOBTASK);
        }
        else {}
    }
    else {}
}

/***********************************************************************
*  Name        : SysJob_Init
*  Description : init
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysJob_Init(void)
{
    U8 i =0u;
    SysJob_bInited=TRUE;

    for(i=0u; i<(U8)SYSJOB_JOB_MAX; i++)
    {
        SysJob_abActive[i]=FALSE;
        SysJob_au8DelayTimer[i]=0u;
    }
}

/***********************************************************************
*  Name        : SysJob_DeInit
*  Description : deinit
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysJob_DeInit(void)
{
    SysJob_bInited=FALSE;
}

/***********************************************************************
*  Name        : SysJob_IsrStartJob
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysJob_IsrStartJob(U8 JobId)
{
    if(SysJob_bInited==TRUE)
    {
        if(JobId<(U8)SYSJOB_JOB_MAX)
        {
            if(SysJob_abActive[JobId]==FALSE)
            {
                SysJob_abActive[JobId]=TRUE;
            }
        }
        OSAPI_IsrActiveTask((U8)OSAPI_SLOWJOBTASK);
    }
    else {}
}

/***********************************************************************
*  Name        : SysJob_DelayStartJob
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysJob_DelayStartJob(U8 JobId, U8 DelayTime)
{

    if(SysJob_bInited==TRUE)
    {
        OSAPI_LockSchedule();
        if(JobId<(U8)SYSJOB_JOB_MAX)
        {
            if(SysJob_abActive[JobId]==FALSE)
            {
                SysJob_au8DelayTimer[JobId]=(U8)OSAPI_SYSTEM_TICKMS(DelayTime);
            }
        }
        OSAPI_UnlockSchedule();
    }
    else {}
}
/***********************************************************************
*  Name        : SysJob_StartJob
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysJob_StartJob(U8 JobId)
{

    if(SysJob_bInited==TRUE)
    {
        OSAPI_LockSchedule();
        if(JobId<SYSJOB_JOB_MAX)
        {
            if(SysJob_abActive[JobId]==FALSE)
            {
                SysJob_abActive[JobId]=TRUE;
            }
        }
        else {}
        OSAPI_UnlockSchedule();
        OSAPI_ActiveTask((U8)OSAPI_SLOWJOBTASK);
    }
    else {}
}

/***********************************************************************
*  Name        : SysJob_ContinueJob
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysJob_ContinueJob(U8 JobId)
{

    if(SysJob_bInited==TRUE)
    {
        OSAPI_LockSchedule();
        if(JobId<SYSJOB_JOB_MAX)
        {
            if(SysJob_abActive[JobId]==FALSE)
            {
                SysJob_abActive[JobId]=TRUE;
            }
        }
        else {}
        OSAPI_UnlockSchedule();
    }
    else {}
}


/***********************************************************************
*  Name        : GetRequestJob
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
U8 GetRequestJob(void)
{
    U8 i=0u;
    U8 jobid =SYSJOB_JOB_MAX;

    OSAPI_LockSchedule();
    for(i=0u; i<(U8)SYSJOB_JOB_MAX; i++)
    {
        if(SysJob_abActive[i]==TRUE)
        {
            jobid=i;
            SysJob_abActive[i]=FALSE;
            break;
        }
    }
    OSAPI_UnlockSchedule();

    return jobid;
}
/**************** END OF FILE *****************************************/


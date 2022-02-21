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
* 0.1    Jan 31,2016            init version
* ----------------------------------------------------------------------
* 0.2    Aug 31,2016            re-structure 
* ----------------------------------------------------------------------
* 0.3    Jan 05,2017    ZhangJie  Delete test code for TRACE_ENABLE test 
*------------------------------------------------------------------------
* 0.4    Jan 11,2017  ZhangJie  Add u for constant value to avoid Coverity warning.
*----------------------------------------------------------------------
* 0.5    Jan 16,2017    RenWeimin  Add test code.
*------------------------------------------------------------------------
* 0.6    Jan 24,2017  ZhangJie   Fix Coverity warnings.
*-----------------------------------------------------------------------
* 0.7    Feb 09,2017   ZhangJie   Remove EOL definition.
*------------------------------------------------------------------------
* 0.8    Mar 08,2017  ZhangJie  Add  function to monitor cyclic task .
*----------------------------------------------------------------------
* 0.9    Mar 22,2017    ZhangJie    Add headfile for cpu rate.
*----------------------------------------------------------------------
* 1.0   Apr 04,2017   PEI Jingli  Fix headfile included.
*----------------------------------------------------------------------
* 1.1   Apr 07,2017   PEI Jingli  Fix warnings.
*=====================================================================*/
#include <CyclicTask_Cfg.h>
#include <Service_HOOKS.h>
#include <Tools.h>
#include "CYCLICMNG.h"
#include "Core_Cfg.h"
#include "CpuUsageRate.h"
#include "OSAdapter_if.h"
#include "Sysswitch.h"

extern const SysCycle_CycleTaskDef SysCycle_astFastAlarm[];
extern const SysCycle_CycleTaskDef SysCycle_astSlowAlarm[];

extern const Func_Void_Proc SysCycle_apFastTmsContainer[SYS_CFG_NO_OF_SYSTEM_STATES][SYSCYCLE_FASTCYCLE_COUNT];
extern const Func_Void_Proc SysCycle_apSlowTmsContainer[SYS_CFG_NO_OF_SYSTEM_STATES][SYSCYCLE_SLOWCYCLE_COUNT];
extern void SysCycle_apTimerContainer(void);


void TimerProc(void);
void FastTaskProc(U8 Cyclename);
void SlowTaskProc(U8 Cyclename);


/*---Global-----------------------------------------------------------*/
U32 SysCyle_u32ForegroundCntr;
U32 SysCyle_u32BrougroudnCntr;

U32 SYSCYCLE_FAST_ONECYCLETICK; 
U32 SYSCYCLE_SLOW_ONECYCLETICK;

#if (PRE_SECOND_FUNC_EN==1u)
U8 SysCyle_ForegroundCounter1S;
U8 SysCyle_BackgroundCounter1S;

BOOL SysCyle_ForegroundTickFlag1S;
BOOL SysCyle_BackgroundTickFlag1S;
#endif

/***********************************************************************
*  Name        : SysCycle_FastTaskEntry
*  Description :  fast timer task        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysCycle_FastTaskEntry(void)
{
    U8 i =0u;
    /***************************************************************************************
    * FUNCTION CODE
    ****************************************************************************************/

    SysCyle_u32ForegroundCntr++;

#if (PRE_SECOND_FUNC_EN==1u)
    SysCyle_ForegroundCounter1S ++;

    if(SysCyle_ForegroundCounter1S >= SYS_CFG_FOREGROUND_1S_TICK)
    {
        /*foreground 1s is reached*/
        SysCyle_ForegroundCounter1S = 0u;
        SysCyle_ForegroundTickFlag1S = TRUE;
    }
#endif

    for(i=0u; i<(U8)SYSCYCLE_FASTCYCLE_COUNT; i++)
    {
        if((SysCyle_u32ForegroundCntr%SysCycle_astFastAlarm[i].tickcount)==SysCycle_astFastAlarm[i].tickstart)
        {
#if (SERVICE_HOOKS_EN==1u)
            SERVICE_FAST_CYCLICTASK_HOOK(i);
#endif
#ifdef __DEBUG__	
           CpuRate_TaskStart(OSAPI_FASTCYCLIC,i);
#endif

            SysCycle_TestTaskEntry(i,TRUE);

            FastTaskProc(i);
            
            SysCycle_TestTaskEntry(i,FALSE);	
#ifdef __DEBUG__	
           CpuRate_TaskStop(OSAPI_FASTCYCLIC,i);
#endif
        }
    }

#if (PRE_SECOND_FUNC_EN==1u)
    SysCyle_ForegroundTickFlag1S = FALSE;
#endif

    if(SysCyle_u32ForegroundCntr==SYSCYCLE_FAST_ONECYCLETICK)
    {
        SysCyle_u32ForegroundCntr=0u;
    }
			 	
    OSAPI_TerminateTask();
}


/***********************************************************************
*  Name        : SysCycle_SlowTaskEntry
*  Description :  slow timer task        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysCycle_SlowTaskEntry(void)
{
    U8 i =0u;
    SysCyle_u32BrougroudnCntr++;
#if (PRE_SECOND_FUNC_EN==1u)
    SysCyle_BackgroundCounter1S ++;

    if(SysCyle_BackgroundCounter1S >= SYS_CFG_BACKGROUND_1S_TICK)
    {
        /*foreground 1s is reached*/
        SysCyle_BackgroundCounter1S = 0u;
        SysCyle_BackgroundTickFlag1S = TRUE;
    }
#endif

    for(i=0u; i<(U8)SYSCYCLE_SLOWCYCLE_COUNT; i++)
    {
        if((SysCyle_u32BrougroudnCntr%SysCycle_astSlowAlarm[i].tickcount)==SysCycle_astSlowAlarm[i].tickstart)
        {
#if( SERVICE_HOOKS_EN==1u)
            SERVICE_SLOW_CYCLICTASK_HOOK(i);
#endif
#ifdef __DEBUG__	
           CpuRate_TaskStart(OSAPI_SLOWCYCLIC,i);
#endif
            SysCycle_TestTaskEntry((i+SYSCYCLE_FASTCYCLE_COUNT),TRUE);	
	
            SlowTaskProc(i);
	
	     SysCycle_TestTaskEntry((i+SYSCYCLE_FASTCYCLE_COUNT),FALSE);
#ifdef __DEBUG__	
           CpuRate_TaskStop(OSAPI_SLOWCYCLIC,i);
#endif
        }
    }

#if (PRE_SECOND_FUNC_EN==1u)
    SysCyle_BackgroundTickFlag1S = FALSE;
#endif

    if(SysCyle_u32BrougroudnCntr==SYSCYCLE_SLOW_ONECYCLETICK)
    {
        SysCyle_u32BrougroudnCntr=0u;
    }

	
    OSAPI_TerminateTask();
}
/***********************************************************************
*  Name        : SysCycle_TimerHook
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysCycle_TimerHook(void)
{
#if(SERVICE_HOOKS_EN==1u)
    SERVICE_SLOW_ATIMER_HOOK();
#endif

    {
        SysCycle_apTimerContainer();
    }

}
/***********************************************************************
*  Name        : SysCycle_Init
*  Description : init
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysCycle_Init(void)
{
    U8 i=0u;
    SysCyle_u32ForegroundCntr=0u;
    SysCyle_u32BrougroudnCntr=0u;

    SYSCYCLE_FAST_ONECYCLETICK=0u;
    SYSCYCLE_SLOW_ONECYCLETICK=0u;

#if (PRE_SECOND_FUNC_EN==1u)
    SysCyle_ForegroundCounter1S = 0U;
    SysCyle_BackgroundCounter1S = 0U;

    SysCyle_ForegroundTickFlag1S = FALSE;
    SysCyle_BackgroundTickFlag1S = FALSE;
#endif

    for(i=0u; i<(U8)SYSCYCLE_FASTCYCLE_COUNT; i++)
    {
        if(SYSCYCLE_FAST_ONECYCLETICK<SysCycle_astFastAlarm[i].tickcount)
        {
            SYSCYCLE_FAST_ONECYCLETICK=SysCycle_astFastAlarm[i].tickcount;
        }
    }

    for(i=0u; i<SYSCYCLE_SLOWCYCLE_COUNT; i++)
    {
        if(SYSCYCLE_SLOW_ONECYCLETICK<SysCycle_astSlowAlarm[i].tickcount)
        {
            SYSCYCLE_SLOW_ONECYCLETICK=SysCycle_astSlowAlarm[i].tickcount;
        }
    }
}

/***********************************************************************
*  Name        : SysCycle_DeInit
*  Description : deinit
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysCycle_DeInit(void)
{
    SysCyle_u32ForegroundCntr=0u;
    SysCyle_u32BrougroudnCntr=0u;

#if (PRE_SECOND_FUNC_EN==1u)
    SysCyle_ForegroundCounter1S = 0U;
    SysCyle_BackgroundCounter1S = 0U;

    SysCyle_ForegroundTickFlag1S = FALSE;
    SysCyle_BackgroundTickFlag1S = FALSE;
#endif
}

/***********************************************************************
*  Name        : FastTaskProc
*  Description :  None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void FastTaskProc(U8 Cyclename)
{

    U8 systemstate = SysSwitch_GetCurrentState();

    if(SysCycle_apFastTmsContainer[systemstate][Cyclename]!=NULL)
    {
        /*Lib_RunContainer((Func_Void_Proc*)&SysCycle_apFastTmsContainer[systemstate][Cyclename][0]);*/
        SysCycle_apFastTmsContainer[systemstate][Cyclename]();
    }
}

/***********************************************************************
*  Name        : SlowTaskProc
*  Description :  None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SlowTaskProc(U8 Cyclename)
{
    U8 systemstate = SysSwitch_GetCurrentState();

    if(SysCycle_apSlowTmsContainer[systemstate][Cyclename]!=NULL)
    {
        /*Lib_RunContainer((Func_Void_Proc*)&SysCycle_apSlowTmsContainer[systemstate][Cyclename][0]);*/
        SysCycle_apSlowTmsContainer[systemstate][Cyclename]();
    }

}

#if (PRE_SECOND_FUNC_EN==1u)
BOOL SysCycle_Get1sForeground(void)
{
    return (SysCyle_ForegroundTickFlag1S);
}

BOOL SysCycle_Get1sBackground(void)
{
    return (SysCyle_BackgroundTickFlag1S);
}
#endif
/**************** END OF FILE *****************************************/


/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*                                      Application-Defined Task Hooks
*
*                                 (c) Copyright 2007; Micrium; Weston, FL
*                                           All Rights Reserved
*
* File    : APP_HOOKS.C
* By      : Fabiano Kovalski
*         : Eric Shufro
*********************************************************************************************************
*/
#include "Service_hooks.h"

#if (SWP_TEST_EN==1u)
void SWPTEST_SLOW_ATIMER_HOOK(void);
void SWPTEST_FAST_CYCLICTASK_HOOK(U8 AlarmId);
void SWPTEST_SLOW_CYCLICTASK_HOOK(U8 AlarmId);
void SWPTEST_EVENT_HOOK(U8 Eventid);
void SWPTEST_JOB_HOOK(U8 Jobid);
void SWPTEST_SWITCH_HOOK(U8 From, U8 To);
void SWPTEST_HARDWARE_INIT_HOOK(void);
void SWPTEST_MAIN_INIT_HOOK(void);
void SWPTEST_INIT_TASK_HOOK(void);
void SWPTEST_IDLE_TASK_HOOK(void);
void SWPTEST_BEFORESLEEP_PROC(void);
void SWPTEST_WAKEUPCHECK_PROC(void);
void SWPTEST_AFTERWAKEUP_PROC(void);
#endif

#if(SERVICE_HOOKS_EN==1u)
void SERVICE_SLOW_ATIMER_HOOK(void)
{
#if (SWP_TEST_EN==1u)
    SWPTEST_SLOW_ATIMER_HOOK();
#endif
}

void SERVICE_FAST_CYCLICTASK_HOOK(U8 AlarmId)
{
#if (SWP_TEST_EN==1u)
    SWPTEST_FAST_CYCLICTASK_HOOK(AlarmId);
#endif
}

void SERVICE_SLOW_CYCLICTASK_HOOK(U8 AlarmId)
{
#if (SWP_TEST_EN==1u)
    SWPTEST_SLOW_CYCLICTASK_HOOK(AlarmId);
#endif
}

void SERVICE_EVENT_HOOK(U8 Eventid)
{
#if (SWP_TEST_EN==1u)
    SWPTEST_EVENT_HOOK(Eventid);
#endif
}

void SERVICE_JOB_HOOK(U8 Jobid)
{
#if (SWP_TEST_EN==1u)
    SWPTEST_JOB_HOOK(Jobid);
#endif
}

void SERVICE_SWITCH_HOOK(U8 From, U8 To)
{
#if (SWP_TEST_EN==1u)
    SWPTEST_SWITCH_HOOK(From,To);
#endif
}

void SERVICE_HARDWARE_INIT_HOOK(void)
{
#if (SWP_TEST_EN==1u)
    SWPTEST_HARDWARE_INIT_HOOK();
#endif
}
void SERVICE_MAIN_INIT_HOOK(void)
{
#if (SWP_TEST_EN==1u)
    SWPTEST_MAIN_INIT_HOOK();
#endif
}

void SERVICE_INIT_TASK_HOOK(void)
{
#if (SWP_TEST_EN==1u)
    SWPTEST_INIT_TASK_HOOK();
#endif
}

void SERVICE_IDLE_TASK_HOOK(void)
{
#if (SWP_TEST_EN==1u)
    SWPTEST_IDLE_TASK_HOOK();
#endif
}

void SERVICE_BEFORESLEEP_PROC(void)
{
#if (SWP_TEST_EN==1u)
    SWPTEST_BEFORESLEEP_PROC();
#endif
}
void SERVICE_WAKEUPCHECK_PROC(void)
{
#if (SWP_TEST_EN==1u)
    SWPTEST_WAKEUPCHECK_PROC();
#endif
}


void SERVICE_AFTERWAKEUP_PROC(void)
{
#if (SWP_TEST_EN==1u)
    SWPTEST_AFTERWAKEUP_PROC();
#endif
}                                                               

#endif                                                                  
/* End of SERVICE_HOOKS_EN                                   */


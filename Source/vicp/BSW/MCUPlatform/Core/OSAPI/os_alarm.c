/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department :  CT AD NKG 
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   :
***********************************************************************/
/*-History--------------------------------------------------------------
* Ver    Date           Name        Changes and comment
** ----------------------------------------------------------------------
* 0.1    Feb 10,2013    NI Rujin    Initial version
*------------------------------------------------------------------------
* 0.2    Jan 24,2017  ZhangJie  Fix Coverity warning.
*-----------------------------------------------------------------------
* 0.3    Apr 07,2017   Pei Jingli   Fix warnings of OSAPI.
*=====================================================================*/

#include <MCUBoard_I.h>
#include <Core_I.h>
#include <Core_Cfg.h>
#include "OSAPI.H"
#include "OSAdapter_if.h"

extern void SysJob_JobAlarm(void);
extern void OSAPI_TaskAlarmHook(void);
extern void OSAlarm_AlarmHook(void);
extern void SysCycle_TimerHook(void);

BOOL OSAlarm_bCyclicTaskRun;
U8 OSAlarm_u8SysTickCnr;
U16 OSAlarm_u16SysTick;

/***********************************************************************
*  Name        : OSAlarm_StartAlarmTask
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSAlarm_StartAlarmTask(void)
{
   OSAlarm_bCyclicTaskRun=(BOOL)TRUE;
   OSAlarm_u8SysTickCnr=(U8)0;
}

/***********************************************************************
*  Name        : OSAlarm_StopAlarmTask
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSAlarm_StopAlarmTask(void)
{

       OSAlarm_bCyclicTaskRun=(BOOL)FALSE;
}


/***********************************************************************
*  Name        : OSAlarm_InitAlarmTimer
*  Description : deinit         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSAlarm_InitAlarmTimer(void)
{
  OSADP_InitOSTimer(OSAPI_SYSTEM_CLOCK);    
}

/***********************************************************************
*  Name        : OSAlarm_StartAlarmTimer
*  Description : deinit         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSAlarm_StartAlarmTimer(void)
{
    OSAlarm_u16SysTick=0u;
    OSADP_StartOSTimer();	
}

/***********************************************************************
*  Name        : OSAlarm_StopAlarmTtimer
*  Description : deinit         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSAlarm_StopAlarmTtimer(void)
{
     OSADP_StopOSTimer();     
}


/***********************************************************************
*  Name        : OSAlarm_GetSystemTime
*  Description : deinit         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
U16 OSAlarm_GetSystemTime(void)
{
  return OSAlarm_u16SysTick;
}

/***********************************************************************
*  Name        : system_alarm_hook
*  Description : This function is called every tick,  
			1) Interrupts may or may not be ENABLED during this call        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSAlarm_AlarmHook(void)
{
   OSAlarm_u16SysTick++;
  if(OSAPI_IsSystemReady()==TRUE)
  {
    /*TODO:CHECK WATCHDOG*/
#ifdef WDG_ENABLE
    OSWDG_TimHook();
#endif
    OSAPI_TaskAlarmHook();
    SysJob_JobAlarm();
#if(OSALARM_TIMER_ISR==1u)    
    SysCycle_TimerHook();
#endif

    if(OSAlarm_bCyclicTaskRun==(BOOL)TRUE)
    {
      OSAlarm_u8SysTickCnr++;  
/*      if((OSAlarm_u8SysTickCnr&OSALARM_FAST_ALARM_CARE_MSK)==OSALARM_FAST_ALARM_VAL)*/		/*problem here, not divided equally*/
      if((OSAlarm_u8SysTickCnr%OSALARM_FAST_ALARM_CARE_MSK)==0u)
      {
	OSAPI_IsrActiveTask((U8)OSAPI_FASTCYCLIC);
      } 
	
      if(OSAlarm_u8SysTickCnr>=(U8)OSALARM_SLOW_ALARM_VAL)
      {
        OSAlarm_u8SysTickCnr=0u;
   	 OSAPI_IsrActiveTask((U8)OSAPI_SLOWCYCLIC);
      } 
    }
    else
    {
      /*do nothing*/
    }
  }
  else{}
  	
}

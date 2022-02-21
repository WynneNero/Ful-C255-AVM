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
* 0.2    Aug 01,2016            re-structure 
*-----------------------------------------------------------------------
* 0.3    Dec 09,2016            Add handler for Timer service 
*----------------------------------------------------------------------
* 0.4    Dec 20,2016      ShangQiuju  remove unused include files
*----------------------------------------------------------------------
* 0.5    Jan 10,2017       ZhangJie     Add function Timer init/deinit definition
*-----------------------------------------------------------------------
* 0.6    Jan 24,2017       ZhangJie   Remove unused include file.
*-----------------------------------------------------------------------
* 0.7    Feb 10,2017       ZhangJie   Include headfile to open witchdog.
*=====================================================================*/
#include "core_cfg.h"
#include "SystemMode_Cfg.h"


extern void MCU_Wakeup(void);
extern void MCU_EnterSleep(void);
extern void SysState_Init(void);
extern void BusMng_Init(void);
extern void EED_Reset(void);
extern void EED_Init(void);
extern void EED_Deinit(void);
extern void Timer_Init(void);
extern void Timer_DeInit(void);

extern void OSAlarm_StartAlarmTimer(void);
extern void OSAlarm_StartAlarmTask(void);
extern void OSAlarm_StopAlarmTtimer(void);
extern void OSAlarm_StopAlarmTask(void);

extern void OSWDG_StartWDG(void);
extern void OSWDG_StopWDG(void);
extern void eng_comm_create(U8 is_eng_first_connect);

void SysMode_apMainInitContainer(void)
{
    /* Add the system service initialization function here! */
    SysState_Init();
    BusMng_Init();
    EED_Reset();
    EED_Init();
}

void SysMode_apSystemInitContainer(void)
{
    /* Add the System service initialization function here! */
    OSAlarm_StartAlarmTimer();
    OSAlarm_StartAlarmTask();
    Timer_Init();
#ifdef WDG_ENABLE
    OSWDG_StartWDG();
#endif
}


void SysMode_apBeforeSleepContainer(void)
{
    OSAlarm_StopAlarmTtimer();
    OSAlarm_StopAlarmTask();
    /* Add the System service deinitialization function here! */
    EED_Deinit();
    Timer_DeInit();
    /*Device sleep*/
    MCU_EnterSleep();
    OSWDG_StopWDG();
}

void SysMode_apWakeupCheckContainer(void)
{
    /* Add the application initialization function here! */
}

void SysMode_apAfterSleepContainer(void)
{
    /*Device wakeup*/
    MCU_Wakeup();
    OSAlarm_StartAlarmTimer();
    OSAlarm_StartAlarmTask();
    /* Add the System service initialization function here! */
    Timer_Init();
#ifdef WDG_ENABLE
    OSWDG_StartWDG();
#endif
}
/**************** END OF FILE *****************************************/


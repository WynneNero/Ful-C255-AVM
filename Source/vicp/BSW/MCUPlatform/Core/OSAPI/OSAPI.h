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
*----------------------------------------------------------------------
*  0.1      Jun 03,2016                      Init version.
*----------------------------------------------------------------------
*  0.2      Jan 24,2017    ZhangJie     Fix Coverity warning.
*----------------------------------------------------------------------
*  0.3      Mar 07,2017    PEI Jingli    Fix headfile included.
*-----------------------------------------------------------------------
* 0.4       Apr 1,2017     PEI Jingli   Fix include files.
*=====================================================================*/
#ifndef _OSAPI_H_
#define _OSAPI_H_ 
#include <MCUBoard_I.h>
#include "OSAPIDef.h"
#include "Core_Cfg.h"

/**** Declaration of functions ****/
void OSAPI_TaskAlarmHook(void);
void OSAlarm_AlarmHook(void);

void OSAPI_InitOS(void);
void OSAPI_StartOS(void);

BOOL OSAPI_IsSystemReady(void);
void OSAPI_CreateSystem(void);
void OSAPI_TerminateTask(void);
void OSAPI_ExitSystem(void);

void OSAPI_LockSchedule(void);
void OSAPI_UnlockSchedule(void);

void OSAPI_TerminateTask(void);
void OSAPI_IsrActiveTask(U8 taskid);
void OSAPI_ActiveTask(U8 taskid);
void OSAPI_DelayActiveTask(U8 taskid, U8 delaytime);
void OSAPI_WaitingTask(U8 taskid,U32 timeout,U8* pmsgv);

void OSAPI_RequestResource(U8 sectionid);
void OSAPI_ReleaseResource(U8 sectionid);


void OSAlarm_InitAlarmTimer(void);
void OSAlarm_StartAlarmTask(void);
void OSAlarm_StopAlarmTask(void);
void OSAlarm_StartAlarmTimer(void);
void OSAlarm_StopAlarmTtimer(void);
U16 OSAlarm_GetSystemTime(void);


void OSWDG_Init(void);
void OSWDG_DeInit(void);
void OSWDG_TimHook(void);
void OSWDG_StartWDG(void);
void OSWDG_FeedWDG(void);
void OSWDG_FeedExtWDG(void);
void OSWDG_StopWDG(void);
void OSWDG_SoftReset(void);

/*#if (TASKMONITOR_EN ==1u)*/
extern void OSWDG_StartMonitor(U8 taskid);
extern void OSWDG_StopMonitor(U8 taskid);
//#endif

void BasicTaskEntry(void);
void ExtendTaskEntry(void);
//void InitTaskEntry(void * p_arg);

void InitTaskEntry(void);

#endif /*_OSAPI_H_*/

/****************************** END OF FILE ***************************/


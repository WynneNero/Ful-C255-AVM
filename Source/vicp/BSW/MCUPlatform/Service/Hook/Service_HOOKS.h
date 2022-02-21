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
*-----------------------------------------------------------------------
* 0.1          Jun 17,2016                   Init version.
*-----------------------------------------------------------------------
* 0.2          Jan 17,2017   ZhangJie   Remove unused include file.
*------------------------------------------------------------------------
* 0.3     Apr 04,2017   PEI Jingli  Delete including "gpio_if.h".
*=====================================================================*/
#ifndef _SERVICE_HOOK_H_
#define _SERVICE_HOOK_H_
/**** Definition of constants ****/


/**** Definition of types ****/


/**** Definition of macros ****/

/**** Declaration of constants ****/


/**** Declaration of variables ****/


/**** Declaration of functions ****/

#if(SERVICE_HOOKS_EN==1u)
void SERVICE_SLOW_ATIMER_HOOK(void);
void SERVICE_FAST_CYCLICTASK_HOOK(U8 AlarmId);
void SERVICE_SLOW_CYCLICTASK_HOOK(U8 AlarmId);
void SERVICE_EVENT_HOOK(U8 Eventid);
void SERVICE_JOB_HOOK(U8 Jobid);
void SERVICE_SWITCH_HOOK(U8 From, U8 To);
void SERVICE_HARDWARE_INIT_HOOK(void);
void SERVICE_MAIN_INIT_HOOK(void);
void SERVICE_INIT_TASK_HOOK(void);
void SERVICE_IDLE_TASK_HOOK(void);
void SERVICE_BEFORESLEEP_PROC(void);
void SERVICE_WAKEUPCHECK_PROC(void);
void SERVICE_AFTERWAKEUP_PROC(void);
#endif              
#endif /*_SERVICE_HOOK_H_*/

/**************** END OF FILE *****************************************/

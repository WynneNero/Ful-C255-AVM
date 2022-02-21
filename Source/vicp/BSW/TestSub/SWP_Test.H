/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   :            										   *
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
* 0.2    Jan 05,2017    ZhangJie  Delete test code for IIC test
* ----------------------------------------------------------------------
* 0.3    Jan 06,2017    ZhangJie  Remove ICS useful micro to ICS_Driver.h and delete invalid ICS test micro
*------------------------------------------------------------------------
* 0.4    Jan 13,2017  ZhangJie  Fix Coverity warning.
*=====================================================================*/
#ifndef _SWP_TEST_H_
#define _SWP_TEST_H_ 
#include "define.h"

/**** Definition of macros ****/

#if(SWP_TEST_EN==1u)
/**** Definition of constants ****/



/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/
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
#endif /*_SWP_TEST_H_*/

/****************************** END OF FILE ***************************/


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
* 0.2          Jan 24,2017   ZhangJie   Remove unused include file.
*=====================================================================*/
#ifndef _JOBMNG_H_
#define _JOBMNG_H_ 
/**** Definition of constants ****/
/* Switch to select if the X ms auxiliary timer A is to be supported or not. */
/**** Definition of macros ****/
#define JOB_PASS_1
#include "JobMng_def.h"

#define SYSJOB_TEST_JOB SYSJOB_JOB_NUM
/**** Declaration of constants ****/

/**** Declaration of variables ****/

/**** Declaration of functions ****/
void SysJob_TaskEntry(void);
void SysJob_JobAlarm(void);
void SysJob_Init(void);
void SysJob_DeInit(void);
void SysJob_IsrStartJob(U8 JobId);
void SysJob_DelayStartJob(U8 JobId, U8 DelayTime);
void SysJob_StartJob(U8 JobId);
void SysJob_ContinueJob(U8 JobId);
#endif /*_JOBMNG_H_*/

/****************************** END OF FILE ***************************/


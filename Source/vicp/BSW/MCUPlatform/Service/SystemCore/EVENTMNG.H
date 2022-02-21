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
#ifndef _EVENTMNG_H_
#define _EVENTMNG_H_ 
/**** Definition of constants ****/
#define EVENT_PASS_1
#include "EVENTMNG_DEF.H"
/**** Definition of macros ****/

#define SYSEVT_TEST_EVNT SYSEVT_EVENT_NUM
/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/
/* main event treatment  */
void SysEvt_Deinit(void);
/* initial event treatment module */
void SysEvt_Init(void);
void SysEvt_TaskEntry(void);
/* create a system event with event id */
void SysEvt_SetEvent(U8 Evtid);
void SysEvt_IsrSetEvent(U8 Evtid);

#endif /*_EVENTMNG_H_*/

/****************************** END OF FILE ***************************/


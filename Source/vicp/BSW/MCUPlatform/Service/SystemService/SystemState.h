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
* ----------------------------------------------------------------------
* 0.1  Apr 15,2016                Initial version.  
*------------------------------------------------------------------------
* 0.2 Jan 24,2017  ZhangJie  Fix Coverity warnings.
*=====================================================================*/
#ifndef _SYSTEM_STATE_H_
#define _SYSTEM_STATE_H_ 
/**** Definition of constants ****/

/**** Definition of macros ****/

/**** Declaration of constants ****/
/**** Declaration of variables ****/
/**** Declaration of functions ****/

void SysState_Init(void);
void SysState_DeInit(void);
void SysState_SetRequest(U8 StateId);
void SysState_ClearRequest(U8 StateId);

void SysState_ResetProc(void); /*call from application and switch from reset to s0*/
void  SysState_SwitchProc(U8 fromindex, U8 toindex);
void  SysState_LockState(void);
void  SysState_UnlockState(void);
#endif /*_SYSTEM_STATE_H_*/

/****************************** END OF FILE ***************************/


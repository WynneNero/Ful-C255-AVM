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
* 0.2   Aug 31,2016             Re-define SYSSTATE
*-----------------------------------------------------------------------
* 0.3   Jan 24,2017   ZhangJie   Fix Coverity warnings.
*=====================================================================*/
#ifndef _SYS_SWITCH_H_
#define _SYS_SWITCH_H_ 
/**** Definition of constants ****/

/* Standard identifier of sytem state. */
#define SYS_S0 0u	/* reset*/
#define SYS_S1 1u	/* sleep*/
#define SYS_S2 2u	/* mode switch*/
#define SYS_S3 3u	/* normal*/
#define SYS_S4 4u	/* FCT*/
#define SYS_S5 5u
#define SYS_S6 6u
#define SYS_S7 7u

/* Number of sytem states. */ 

#define SYS_SYSTEM_STATE_NUM (SYS_S7 + 1u)

#define  SYSSTATE_FULLSTATE 1u
#define  SYSSTATE_UPDOWNSTATE 2u

/**** Definition of macros ****/
/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/
void  SysSwitch_Init(void);
void  SysSwitch_Deinit(void);
BOOL  SysSwitch_IsSwitching(void);
U8  SysSwitch_GetCurrentState(void);
U8 SysSwitch_IsrGetCurrentState(void);
U8  SysSwitch_GetPrevState(void);
void  SysSwitch_RequestSwitch(U8 newState);
void SysSwitch_HighTaskEntry(void);
void SysSwitch_LowTaskEntry(void);
#endif /*_SYS_SWITCH_H_*/

/****************************** END OF FILE ***************************/


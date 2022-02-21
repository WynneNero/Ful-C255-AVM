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
*------------------------------------------------------------------------
* 0.1	   Jun 26,2016                   Initial version
*------------------------------------------------------------------------
* 0.2	   Jun 10,2017  ZHANG Jie  Add function OSADP_InitWdg define,
*                                                    and add u for constant value to avoid Coverity warning.
*------------------------------------------------------------------------
* 0.3         Mar 07,2017 PEI Jingli    Fix headfile included.
*-----------------------------------------------------------------------
* 0.4         Apr 1,2017     PEI Jingli   Remove micro OSADP_WAIT_NOTIMEOUT.
*=====================================================================*/
#ifndef  _OSADAPTER_IF_H
#define  _OSADAPTER_IF_H
/**** System include files ****/
#include <McuBoard_I.h>
#include "RTOS_I.h"
#include "Os_cpu.h"


typedef void   (*pTaskEntry)(void *p_arg);
/*
typedef OS_EVENT OSADP_SEM ;
typedef OS_EVENT OSADP_MBX;
typedef OS_STK    OSADP_STK;
*/
typedef U64 OSADP_SEM ;
typedef U64 OSADP_MBX;
typedef U64  OSADP_STK;

/*---Global-----------------------------------------------------------*/

void OSADP_OSInit(void);
void OSADP_OSStatInit(void);
void OSADP_StartOS(void);
void OSADP_LockSchedule(void);
void OSADP_UnlockSchedule(void);
void OSADP_OSTaskDelSelf(void);

void  OSADP_CreateTask(U8 index,                         
			U8    prio,
			pTaskEntry proc,
			OSADP_STK  *ptos,                    
			OSADP_STK  *pbos,
			U32   stk_size);
			
U8  OSADP_GetTaskIndex (void);

BOOL OSADP_CreateSem(OSADP_SEM** pSem);
BOOL OSADP_WaitSem(OSADP_SEM* pSem, U32 timeout);
BOOL OSADP_PostSem(OSADP_SEM* pSem);

BOOL OSADP_CreateMbox(OSADP_MBX** pSMbox);
BOOL OSADP_PostMbox(OSADP_MBX* pSMbox, U8* pMsg);
BOOL OSADP_WaitMbox(OSADP_MBX* pSMbox, U8* pMsg, U32 timeout);

void OSADP_DisableAndSaveIrq(void);
void OSADP_EnableAndRestoreIrq(void);
void OSADP_InitOSTimer(U32 Tick_PerSec);
void OSADP_StartOSTimer(void);
void OSADP_StopOSTimer(void);

void OSADP_InitWdg(void);
void OSADP_FeedWdg(void);
void OSADP_StartWdg(void);
void OSADP_StopWdg(void);
void OSADP_FeedExtWdg(void);

#endif /*_OSADAPTER_IF_H*/
/**************** END OF FILE *****************************************/


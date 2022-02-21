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
* 0.1                                      Initial
* ----------------------------------------------------------------------
* 0.2    Sep 27,2016 PJL  modify _InitOSTimer.
*------------------------------------------------------------------------
* 0.3    Jan 24,2017  ZhangJie  Fix Coverity warning.
*=====================================================================*/
/**** System include files ****/
#include <McuBoard_I.h>
#include <Core_Cfg.h>
#include "OSAdapter_IF.h"
#include "oseksched.h"
#include "TimerUnit_if.h"

/*---Global-----------------------------------------------------------*/

/***********************************************************************
*  Name        : OSADP_OSInit
*  Description : os init         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSADP_OSInit(void)
{
   /*OSInit(); */
}


/***********************************************************************
*  Name        : OSADP_CreateTask
*  Description : os init         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
/*
void  OSADP_CreateTask(U8 index,                         
			U8    prio,
			pTaskEntry proc,
			OSADP_STK  *ptos,                    
			OSADP_STK  *pbos,
			U32   stk_size)
{
    U8 err=0;
    OSTaskCreateExt(
   		proc, 
		(void   *)0,
		(OS_STK          *)ptos, 
		prio, 
		prio,
		(OS_STK          *)pbos,			
		stk_size,
		(void      *)0,
		(INT16U  )OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);   

    OSTaskRegSet(prio,0u,index,&err);
}
*/
/***********************************************************************
*  Name        : OSADP_GetTaskIndex
*  Description :          
*  Parameter   : None
*  Returns     : None
***********************************************************************/
U8  OSADP_GetTaskIndex (void)
{
  U8 err=0;
  U16 taskid=(U16)OSAPI_TASKNUM;

/*  taskid= OSTaskRegGet(OS_PRIO_SELF,0u,&err);*/
/*  if(OS_ERR_NONE!=err)taskid=OSAPI_TASKNUM;*/

  err=osGetTaskID((TaskRefType)&taskid);
  if((U8)E_OK!=err)taskid=(U8)OSAPI_TASKNUM;
  return (U8)taskid;
}

/***********************************************************************
*  Name        : OSADP_StartOS
*  Description : Start OS      
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSADP_StartOS(void)
{			 
/*    OSStart(); */
	StartOS(OSDEFAULTAPPMODE);
}

/***********************************************************************
*  Name        : OSADP_CreateSem
*  Description : Start OS      
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL OSADP_CreateSem(OSADP_SEM** pSem)
{

    BOOL isOK=FALSE;
/*	
    OS_EVENT* pEvent=OSSemCreate(1u);

   if(pEvent!=(void*)0)
   {
     *((OS_EVENT**)pSem)=pEvent;
     isOK=TRUE;
   }
*/
   return isOK;
}

/***********************************************************************
*  Name        : OSADP_WaitSem
*  Description : Start OS      
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL OSADP_WaitSem(OSADP_SEM* pSem, U32 timeout)
{
    /*U8 error=0;*/
    BOOL isOK=FALSE;
	/*
    OSSemPend(pSem,timeout,&error);
    if(OS_ERR_NONE==error)
    {
	isOK=TRUE;
    }
*/
    return isOK;
}

/***********************************************************************
*  Name        : OSADP_WaitSem
*  Description : Start OS      
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL OSADP_PostSem(OSADP_SEM* pSem)
{
    BOOL isOK=FALSE;
	/*
    U8 ret=OSSemPost(pSem);
    if(OS_ERR_NONE==ret)
    {
	isOK=TRUE;
    }
    */
    return isOK;    
}

/***********************************************************************
*  Name        : OSADP_CreateMbox
*  Description : Start OS      
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL OSADP_CreateMbox(OSADP_MBX** pSMbox)
{
    BOOL isOK=FALSE;
	/*
    OS_EVENT* pEvent=OSMboxCreate((void*)0);

   if(pEvent!=(void*)0)
   {
     *((OS_EVENT**)pSMbox)=pEvent;
     isOK=TRUE;
   }
*/
   return isOK;
}


/***********************************************************************
*  Name        : OSADP_PostMbox
*  Description : Start OS      
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL OSADP_PostMbox(OSADP_MBX* pSMbox, U8* pMsg)
{

    BOOL isOK=FALSE;
	/*
    U8 nRet= OSMboxPost(pSMbox,pMsg);

   if(nRet==OS_ERR_NONE)
   {
     isOK=TRUE;
   }
*/
   return isOK;

}

/***********************************************************************
*  Name        : OSADP_PostMbox
*  Description : Start OS      
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL OSADP_WaitMbox(OSADP_MBX* pSMbox, U8* pMsg, U32 timeout)
{
    BOOL isOK=FALSE;
	/*
    U8 err=0;
    void* msg=OSMboxPend(pSMbox,timeout,&err);    

   if((err==OS_ERR_NONE)&&
   	(msg!=(void*)0))
   {
     isOK=TRUE;
     *pMsg=*((U8*)msg);
   }
*/
   return isOK;  
}
/***********************************************************************
*  Name        : OSAPI_LockSchedule
*  Description :          
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSADP_LockSchedule(void)
{  
   /*OSSchedLock();*/
   	osSuspendOSInterrupts();
}


/***********************************************************************
*  Name        : OSAPI_UnlockSchedule
*  Description :          
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSADP_UnlockSchedule(void)
{  
  /*OSSchedUnlock();*/
    osResumeOSInterrupts();
}

/***********************************************************************
*  Name        : OSADP_OSTaskDel
*  Description :          
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSADP_OSTaskDelSelf(void)
{  
    /*OSTaskDel(OS_PRIO_SELF); */
    osSchedRemoveRunningTask();		/*? to be checked*/
}

/***********************************************************************
*  Name        : OSADP_OSStatInit
*  Description :          
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSADP_OSStatInit(void)
{
  /*OSStatInit();*/
}


/***********************************************************************
*  Name        : OSADP_DisableAndSaveIrq
*  Description :          
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSADP_DisableAndSaveIrq(void)
{
  /*TODO: to change with di and save psw state*/
  MCU_DI();
}

/***********************************************************************
*  Name        : OSADP_EnableAndRestoreIrq
*  Description :          
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSADP_EnableAndRestoreIrq(void)
{
  /*TODO: to change with ei and restore psw state*/
 MCU_EI();
}


/***********************************************************************
*  Name        : OSErrorHook
*  Description :          
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void  OSErrorHook (U8 task, U8 Error)
{
  static U8 errtask=0;
  static U8 errCode=0;
  errtask=task;
  errCode=Error;

  (void)errtask;
  (void)errCode;
  for(;;);
}

/***********************************************************************
*  Name        : OSADP_InitOSTimer
*  Description : deinit         
*  Parameter   : Ms_PreTick, unit: 0.1ms
			   should be multiples of 5
*  Returns     : None
***********************************************************************/
void OSADP_InitOSTimer(U32 Ms_PreTick)
{
    TAU_OSTimer_Init(0, Ms_PreTick);
}

/***********************************************************************
*  Name        : OSADP_StartOSTimer
*  Description : deinit         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSADP_StartOSTimer(void)
{
    TAU_OSTimer_Cmd((BOOL)ENABLE);
}

/***********************************************************************
*  Name        : OSADP_StopOSTimer
*  Description : deinit         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSADP_StopOSTimer(void)
{
  TAU_OSTimer_Cmd((BOOL)DISABLE);
}


/**************** END OF FILE *****************************************/


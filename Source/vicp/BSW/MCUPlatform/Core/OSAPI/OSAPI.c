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
* Version  Date              Name       Changes and comments
* 	0.1						   All tasks except ResetTask are configured as extended tasks.
							   ResetTask will auto start once.
* ----------------------------------------------------------------------
* 	0.2   Jan 05,2017    ZhangJie   Delete test invalid code
*------------------------------------------------------------------------
*   0.3    Jan 24,2017  ZhangJie  Fix Coverity warning.
*------------------------------------------------------------------------
*   0.4    Mar 08,2017  ZhangJie  Add  function to monitor os task .
*-----------------------------------------------------------------------
*   0.5     Apr 1,2017   PEI Jingli   Fix include files.
*=====================================================================*/

/**** System include files ****/
#include <Core_I.h>
#include <Core_Cfg.h>
#include "OSAdapter_IF.h"
#include "OSAPI.H"
#include "Os.h"
#include "CpuUsageRate.h"

/*static const U8 vector_TaskID[6]={2,3,0,4,1,5};	  map vector task ID*/
static const U8 vector_TaskID[6]={0u,1u,2u,3u,4u,5u};	/*map vector task ID*/
/*---Public function and variables---------------------------------------------*/
extern void SINI_TaskInit(void);
extern const OSAPI_TaskCfgType OSCfg_astAllTask[OSAPI_TASKNUM] ;
/*---Global-----------------------------------------------------------*/

const char* MCUPlatformVersion ="MPSV_011";

const U8 OSAPI_u8QuitTaskMsg= OSAPI_TERMINATETASK;
const U8 OSAPI_u8ActiveTaskMsg= OSAPI_ACTIVETASK;

/*---Private----------------------------------------------------------*/
U16 OSAPI_u16OSLockCnt;
U16 OSAPI_u16IsrLockCnt;
BOOL OSAPI_bSystemStarted;


/*OSADP_MBX* OSAPI_apTaskMailbox[OSAPI_TASKNUM];*/
BOOL     OSAPI_bTaskQuit[OSAPI_TASKNUM];

/*OSADP_SEM* OSAPI_apCriticalSection[OSAPI_CSECTIONNUM];*/

U8 OSAPI_au8TaskDelayTimer[OSAPI_TASKNUM];

/*OSADP_STK OSAPI_astInitTaskStk[OSAPI_INITTASK_STACKSIZE];*/

/*===FUNCTIONS========================================================*/
/*void InitTaskEntry(void *p_arg);*/
void InitTaskEntry(void);
void BasicTaskEntry(void);
void ExtendTaskEntry(void);\
void QuitTask(U8 taskid);
void ResumeTask(U8 taskid);
void SuspendTask(VOLATILE U8 taskid,U32 timeout,  VOLATILE U8* pmsgv);
/*---Global-----------------------------------------------------------*/
/***********************************************************************
*  Name        : OSAPI_InitOS
*  Description : os init         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSAPI_InitOS(void)
{
 U8 i=0u;
  OSAPI_u16OSLockCnt=0u;
  OSAPI_u16IsrLockCnt=0u;
  OSAPI_bSystemStarted=(BOOL)FALSE;

     for(i=0u;i<(U8)OSAPI_TASKNUM;i++)
    {
         OSAPI_au8TaskDelayTimer[i]=0u;
     }
}


/***********************************************************************
*  Name        : OSAPI_TerminateTask
*  Description : terminal task         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL OSAPI_IsSystemReady(void)
{  
 return OSAPI_bSystemStarted;
}

/***********************************************************************
*  Name        : OSAPI_TerminateTask
*  Description : terminal task        
			MicroSAR requires to terminate basic task			
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSAPI_TerminateTask(void)
{  
	/*osTerminateTask();*/		/* extended task don't need to terminate*/
}

/***********************************************************************
*  Name        : OSAPI_IsrActiveTask
*  Description : active basic task         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSAPI_IsrActiveTask(U8 taskid)
{  
  if(taskid<(U8)OSAPI_TASKNUM)
  { 
    ResumeTask(taskid);
  }
  else{}
}

/***********************************************************************
*  Name        : OSAPI_IsrActiveTask
*  Description : active extend task         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSAPI_IsrActiveExtTask(U8 taskid)
{  
  if(taskid<(U8)OSAPI_TASKNUM)
  { 
    ResumeTask(taskid);
  }
  else{}
}

/***********************************************************************
*  Name        : OSAPI_ActiveTask
*  Description : relarm task         
			no used now
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSAPI_DelayActiveTask(U8 taskid, U8 delaytime)
{

  if(taskid<(U8)OSAPI_TASKNUM)
  {
	OSADP_DisableAndSaveIrq();
	OSAPI_au8TaskDelayTimer[taskid]=(U8)OSAPI_SYSTEM_TICKMS(delaytime);
	OSADP_EnableAndRestoreIrq();	
  }
  else{}
  
}

/***********************************************************************
*  Name        : OSAPI_ActiveTask
*  Description : active task directly
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSAPI_ActiveTask(U8 taskid)
{  
  if(taskid<(U8)OSAPI_TASKNUM)
  { 
    ResumeTask(taskid);
  }
  else{}
}

/***********************************************************************
*  Name        : OSAPI_ActiveExtTask
*  Description : active extended task, set event to make task enter ready state
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSAPI_ActiveExtTask(U8 taskid)
{  
  if(taskid<(U8)OSAPI_TASKNUM)
  { 
    ResumeTask(taskid);
  }
  else{}
}


/***********************************************************************
*  Name        : OSAPI_WaitingTask
*  Description : active task         
*  Parameter   : 
				timeout	-	not used now
*  Returns     : None
***********************************************************************/
void OSAPI_WaitingTask(U8 taskid,U32 timeout,U8* pmsgv)
{  
  if((taskid<(U8)OSAPI_TASKNUM)
     &&(OSAPI_bSystemStarted==(BOOL)TRUE))
  {
       SuspendTask(taskid, timeout,  pmsgv);
  }
  else{}
}


/***********************************************************************
*  Name        : OSAPI_StartOS
*  Description : Start OS, create init task       
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSAPI_StartOS(void)
{			 
    if(OSAPI_bSystemStarted==(BOOL)FALSE)
    {
      OSADP_StartOS(); 
    }
    else{}
}

/***********************************************************************
*  Name        : OSAPI_CreateSystem
*  Description : init user task, mailbox, critial section and OS resource         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSAPI_CreateSystem(void)
{
          osActivateTask(SlowJob);		
	   osActivateTask(EventTask);	
	   osActivateTask(FastCyclic);
  	   osActivateTask(SlowCyclic);
	   osActivateTask(SystemSwitchHigh);	
  	   osActivateTask(SystemSwitchLow);		
}

/***********************************************************************
*  Name        : OSAPI_ExitSystem
*  Description : kill all task ,just for test        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSAPI_ExitSystem(void)
{  

/* U8 i=0;*/
   OSADP_DisableAndSaveIrq();  
   /*
  for(i=0;i<OSAPI_TASKNUM;i++)
  {
    QuitTask(i);
  }
  */
  QuitTask(0);		/* task id doesn't matter*/
   
  OSAPI_bSystemStarted=FALSE;  
  OSADP_EnableAndRestoreIrq();   
}
/***********************************************************************
*  Name        : OSAPI_TaskAlarmHook
*  Description : active task         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSAPI_TaskAlarmHook(void)
{
  U8 i=0u;
  U8 taskcount =0u;
  if( OSAPI_bSystemStarted==(BOOL)TRUE)
  {  
   for(;i<(U8)OSAPI_TASKNUM;i++)
    {
       if(taskcount>=OSAPI_MULTIACTIVE_NUM)break;/*for OS isr stack*/
  	   if(OSAPI_au8TaskDelayTimer[i]>0u)	/*not used now*/
	   {
	   	 OSAPI_au8TaskDelayTimer[i]--;	
		 if(OSAPI_au8TaskDelayTimer[i]==0u)
		 {
		  OSAPI_IsrActiveTask(i);
		  taskcount++;
		 }
	  }
    }
  }
  else{}
}

/***********************************************************************
*  Name        : OSAPI_LockSchedule
*  Description :          
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSAPI_LockSchedule(void)
{  
  OSADP_LockSchedule();
}


/***********************************************************************
*  Name        : OSAPI_UnlockSchedule
*  Description :          
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSAPI_UnlockSchedule(void)
{  
 	OSADP_UnlockSchedule();
}

/***********************************************************************
*  Name        : OSAPI_RequestResource
*  Description :          
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSAPI_RequestResource(U8 sectionid)
{  
/*
if((sectionid<(U8)OSAPI_CSECTIONNUM)
           &&(OSAPI_bSystemStarted==(BOOL)TRUE))
        {
          OSADP_WaitSem(OSAPI_apCriticalSection[sectionid], 0);
        }
        else{}
 */
}

/***********************************************************************
*  Name        : OSAPI_ReleaseResource
*  Description :        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSAPI_ReleaseResource(U8 sectionid)
{         
/*
	if((sectionid<(U8)OSAPI_CSECTIONNUM)
           &&(OSAPI_bSystemStarted==(BOOL)TRUE))
        {
          OSADP_PostSem(OSAPI_apCriticalSection[sectionid]);
        }
        else{}        
 */
}

/***********************************************************************
*  Name        : OSAPI_InitTaskEntry
*  Description : create power_tast and initialize tasks' variables       
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void  InitTaskEntry (void)
{  
/*    (void)p_arg;*/
       OSAPI_bSystemStarted=(BOOL)TRUE;		
	SINI_TaskInit();	 

	/*	for uc-OS
	#if OSAPI_DEBUG_EN > 0u
   	OSADP_OSStatInit ();
	#endif		
	OSADP_OSTaskDelSelf(); 
	*/
	 osTerminateTask();

}
/***********************************************************************
*  Name        : OSAPI_ExtendTaskEntry
*  Description : task entery       
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void ExtendTaskEntry(void)
{
        VOLATILE U32  taskindex = OSADP_GetTaskIndex();
	if(taskindex<(U32)OSAPI_TASKNUM)
	{
#ifdef __DEBUG__	
       CpuRate_TaskStart(taskindex,0xFF);
#endif
	 if(OSCfg_astAllTask[taskindex].taskproc!=NULL)
	 {
		OSCfg_astAllTask[taskindex].taskproc();
	 }	
#ifdef __DEBUG__
       CpuRate_TaskStop(taskindex,0xFF);
#endif
	}
	else{}
	OSADP_OSTaskDelSelf();
}

/***********************************************************************
*  Name        : OSAPI_BasicTaskEntry
*  Description : task entery       
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void  BasicTaskEntry (void)
{  
	VOLATILE U8  msgv =OSAPI_ACTIVETASK;        
        	VOLATILE U8  taskindex = OSADP_GetTaskIndex();

	if(taskindex<(U8)OSAPI_TASKNUM)
	{
	 do{		
		SuspendTask((U8)taskindex,OSADP_WAIT_NOTIMEOUT,(VOLATILE U8*)&msgv);			

		 if(msgv==OSAPI_ACTIVETASK)
		 {
#ifdef __DEBUG__	
               CpuRate_TaskStart(taskindex,0xFF);
#endif
	 	#if (TASKMONITOR_EN ==1u)
	 	 OSWDG_StartMonitor(taskindex);
	 	#endif		 
			if(OSCfg_astAllTask[taskindex].taskproc!=NULL)
			{
				OSCfg_astAllTask[taskindex].taskproc();
			}	

	 	#if (TASKMONITOR_EN ==1u)
	 	 OSWDG_StopMonitor(taskindex);
	 	#endif
#ifdef __DEBUG__
               CpuRate_TaskStop(taskindex,0xFF);
#endif    

		 }
		 else if(msgv==OSAPI_TERMINATETASK)
		 {
			break;
		 }
		 else
		 {/*do nothing*/
		 }		

	 }while(TRUE);
	}
	else{}
	OSADP_OSTaskDelSelf(); 
}
/***********************************************************************
*  Name        : QuitTask
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void QuitTask(U8 taskid)
{  
  
  if(OSAPI_bSystemStarted==(BOOL)TRUE)
  {
/*    OSADP_DisableAndSaveIrq();*/  	/*called in OSAPI, not needed*/
/*
  	for(i=0;i<OSAPI_TASKNUM;i++)
  	{
    		OSAPI_bTaskQuit[i]=TRUE;
  	}
 */
	  osShutdownOS(0);			/* error=0; to be checked*/
/*    OSADP_EnableAndRestoreIrq();*/
/*    OSADP_PostMbox(OSAPI_apTaskMailbox[taskid], (U8*)&OSAPI_u8QuitTaskMsg);*/
  }
  else{}

}
/***********************************************************************
*  Name        : ResumeTask
*  Description : resum extend task         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void ResumeTask(U8 taskid)
{  
  if(OSAPI_bSystemStarted==(BOOL)TRUE)/*left one space for quit msg*/
  {
	/*OSADP_PostMbox(OSAPI_apTaskMailbox[taskid],(U8*)(&OSAPI_u8ActiveTaskMsg));*/
	osSetEvent(vector_TaskID[taskid],1);		/*for extended task*/
  }
  else{}  
}
/***********************************************************************
*  Name        : SuspendTask
*  Description : suspend extend task, must be called from extended task owning the event
*  Parameter   : 
			timeout	-	not use now
*  Returns     : None
***********************************************************************/
void SuspendTask(VOLATILE U8 taskid,U32 timeout,  VOLATILE U8* pmsgv)
{  
  /*U8 mbRet =0u;*/
  StatusType mbRet=0;
/*BOOL bRet=FALSE;*/
  VOLATILE BOOL isExit =FALSE;  

  OSADP_DisableAndSaveIrq();  
  isExit=OSAPI_bTaskQuit[taskid];
  OSADP_EnableAndRestoreIrq();

  if(isExit==FALSE)
  {  
   /*bRet=OSADP_WaitMbox(OSAPI_apTaskMailbox[taskid], (void*)&mbRet,timeout);*/
	  mbRet=osWaitEvent(MICROSAR_EVENT);	/*set task to waiting*/

	  if(mbRet==(StatusType)E_OK)		/*check return?  In standard status, no other return code except E_OK*/
	  {
		* pmsgv=OSAPI_ACTIVETASK;		/*OSAPI_SUSPENDTASK;*/
	  }
	  osClearEvent(1);
	  
	   OSADP_DisableAndSaveIrq();  
	   isExit=OSAPI_bTaskQuit[taskid];
	   OSADP_EnableAndRestoreIrq();

	   if(isExit==TRUE)			/*never enter here cause isExit is only set in OSAPI_ExitSystem*/
	   {
	      *pmsgv=OSAPI_TERMINATETASK;
	   }
	   else
	   {
	   /*
	      if (bRet==TRUE) 
	      {       
	       *pmsgv = mbRet;
	      }
	      else
	     {
	      *pmsgv=OSAPI_UNKNOWTASK;
	      }
	      */
	   }
  }
  else	/*never enter here cause isExit is only set in OSAPI_ExitSystem*/
  {
    *pmsgv=OSAPI_TERMINATETASK;
  }  
}
/**************** END OF FILE *****************************************/


/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department :  CT AD NKG 
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   :
***********************************************************************/
/*-History--------------------------------------------------------------
* Ver    Date           Name        Changes and comment
** ----------------------------------------------------------------------
* 0.1    Feb 10,2013    NI Rujin    Initial version
------------------------------------------------------------------------
* 0.2	 July 21,2016   PEI Jingli  Refine code structure.
*------------------------------------------------------------------------
* 0.3    Jan 13,2017  ZhangJie  Fix Coverity warning.
------------------------------------------------------------------------
* 0.4    Jan 13,2017   RenWeimin  Add eol test code here.
 ----------------------------------------------------------------------
* 0.5    Jan 16,2017   RenWeimin  Update test code. Not using signal in OSWDG_TimHook.
*----------------------------------------------------------------------
* 0.6    Jan 24,2017    ZhangJie     Fix Coverity warning phase2.
*-----------------------------------------------------------------------
* 0.7    Feb 09,2017   ZhangJie   Remove EOL definition.
*-----------------------------------------------------------------------
* 0.8    Apr 07,2017   Pei Jingli   Fix warnings of OSAPI.
*=====================================================================*/

#include <MCUBoard_I.h>
#include <Core_I.h>
#include <Core_Cfg.h>
#include "OSAPI.H"
#include "OSAdapter_if.h"
#include "GPIO_if.H"
#include "Mcu_if.h"
#if (TASKMONITOR_EN ==1u)
extern const OSAPI_WdgCfgType OSCfg_astAllWdg[OSAPI_TASKNUM];

U16 OSWDG_RunningTick[OSAPI_TASKNUM];
OSAPI_WDGState OSWDG_WDGState[OSAPI_TASKNUM];
#endif
BOOL OSWDG_bStartWDG;
BOOL OSWDG_bNeedReset;

extern U32 get_systemtick(void);

/***********************************************************************
*  Name        : OSWDG_Init
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSWDG_Init(void)
{
#if (TASKMONITOR_EN ==1u)
  U8 i=0;
  
  for(; i<(U8)OSAPI_TASKNUM;i++)
  {
	OSWDG_RunningTick[i]=0;
	OSWDG_WDGState[i]=OSAPI_WDG_STOP;
  }
#endif

  OSWDG_bNeedReset=FALSE;  
  OSWDG_bStartWDG=FALSE;
  OSADP_StopWdg();		/* not actually stop, disable wdt in standby mode*/
  OSADP_InitWdg();		/*config, not started yet*/
}

/***********************************************************************
*  Name        : OSWDG_DeInit
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSWDG_DeInit(void)
{

}
#if (TASKMONITOR_EN ==1u)
/***********************************************************************
*  Name        : OSWDG_StartMonitor
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSWDG_StartMonitor(U8 taskid)
{
  if(OSWDG_WDGState[taskid]!=OSAPI_WDG_START)
  {
	OSWDG_RunningTick[taskid]=0;
	OSWDG_WDGState[taskid]=OSAPI_WDG_START;
  }
  else{}
}

/***********************************************************************
*  Name        : OSWDG_StopMonitor
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSWDG_StopMonitor(U8 taskid)
{
  if(OSWDG_WDGState[taskid]!=OSAPI_WDG_STOP)
  {
	OSWDG_RunningTick[taskid]=0;
	OSWDG_WDGState[taskid]=OSAPI_WDG_STOP;
  }
  else{}  
}

/***********************************************************************
*  Name        : OSWDG_PauseMonitor
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSWDG_PauseMonitor(U8 taskid)
{
  if(OSWDG_WDGState[taskid]==OSAPI_WDG_START)
  {
     OSWDG_WDGState[taskid]=OSAPI_WDG_PAUSE;
  }
  else{}  
}

/***********************************************************************
*  Name        : OSWDG_UnPauseMonitor
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSWDG_UnPauseMonitor(U8 taskid)
{
  if(OSWDG_WDGState[taskid]==OSAPI_WDG_PAUSE)
  {
     OSWDG_WDGState[taskid]=OSAPI_WDG_START;
  }
  else{}  
}
#endif  
/***********************************************************************
*  Name        : OSWDG_Monitor
*  Description : This function is called every tick    
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSWDG_TimHook(void)
{
  if(OSWDG_bStartWDG==TRUE)
  {
#if (TASKMONITOR_EN ==1u)
  U8 i=0;
  BOOL isResetMCU=FALSE;
  for(; i<(U8)OSAPI_TASKNUM;i++)
  {
	if(OSWDG_WDGState[i]==OSAPI_WDG_START)
	{
	  OSWDG_RunningTick[i]++;

	  if(OSWDG_RunningTick[i]>OSCfg_astAllWdg[i].MaxTick)
	  {
	    if(OSCfg_astAllWdg[i].isResetMCU==TRUE)
	    {
	      isResetMCU=TRUE;
	    }
	    else{}
	    
	    if(OSCfg_astAllWdg[i].wdgproc!=NULL)
	    {
		OSCfg_astAllWdg[i].wdgproc(OSWDG_RunningTick[i]);
	    }
	    else{}
	    break;
	  }
	  else if(OSWDG_WDGState[i]==OSAPI_WDG_PAUSE)
	  {
	     break;
	  }
	  else{}
	  
	}
	else{}
  }  	
  OSWDG_bNeedReset=isResetMCU;
#endif

  if(OSWDG_bNeedReset==FALSE)
  {
       OSADP_FeedWdg();	
  }
  else
  { 
   for(;;); //wait for reset 
  }
  }
  else{}
}

/***********************************************************************
*  Name        : OSWDG_StartWDG
*  Description :     
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSWDG_StartWDG(void)
{
#if (TASKMONITOR_EN ==1u)
  U8 i=0;
  
  for(; i<(U8)OSAPI_TASKNUM;i++)
  {
    OSWDG_RunningTick[i]=0;
  }
#endif   

    OSADP_StartWdg();   
/*
	static U32 WDT_started_time=0;
MCU_DI();
    WDT_started_time=get_systemtick();
MCU_EI();
*/
    OSWDG_bStartWDG=TRUE;    
}

/***********************************************************************
*  Name        : OSWDG_FeedWDG
*  Description :     
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSWDG_FeedWDG(void)
{
  if(OSWDG_bStartWDG==TRUE)
  {
	  if(OSWDG_bNeedReset==FALSE)
	  {
	       OSADP_FeedWdg();	
	  }
	  else
	  { 
	    for(;;); /*wait for reset */
	  }
  }
  else{}
}

/***********************************************************************
*  Name        : OSWDG_FeedExtWDG
*  Description :     
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSWDG_FeedExtWDG(void)
{
  if(OSWDG_bStartWDG==TRUE)
  {
  if(OSWDG_bNeedReset==FALSE)
  {
    OSADP_FeedExtWdg();
  }
  else{}
  }
  else{}
}
/***********************************************************************
*  Name        : OSWDG_StopWDG
*  Description :     
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSWDG_StopWDG(void)
{
    OSADP_DisableAndSaveIrq();
    OSWDG_bStartWDG=FALSE;
    OSADP_EnableAndRestoreIrq();
 
     OSADP_StopWdg();		//no action, RH850 WDT can't stop once started
}

/***********************************************************************
*  Name        : OSWDG_SoftReset
*  Description :     
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSWDG_SoftReset(void)
{
    OSWDG_bNeedReset=TRUE;
//    if(OSWDG_bStartWDG==TRUE)
//    {
//        for(;;)
//        {
//            ;/*wait for reset */
//            /*TODO: CHECK RESET ACTION.*/
//        }		
//    }
//    else
//    {
        mcu_sw_reset();
//    }
}


/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				*
*				  All Rights Reserved.          			*
*   Department : RN R&D SW1      						*
*   AUTHOR	   : Shao  Guangxian					*
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
*----------------------------------------------------------------------
* 0.1    Dec 20,2015   init version
*----------------------------------------------------------------------
* 0.2    Dec 20,2016   remove unused .h files
*----------------------------------------------------------------------
* 0.3    Dec 26,2016   remove SERTIME_TEST
* ----------------------------------------------------------------------
* 0.4    Jan 05,2017    ZhangJie  Delete all test code and only reserved hook functions as a template
*------------------------------------------------------------------------
* 0.5    Jan 24,2017  ZhangJie  Fix Coverity warnings.
*=====================================================================*/
#include "SWP_Test.H"


/*---Global-----------------------------------------------------------*/

void SWPTEST_SLOW_ATIMER_HOOK(void)
{
	
}

void SWPTEST_FAST_CYCLICTASK_HOOK(U8 AlarmId)
{
   
}

void SWPTEST_SLOW_CYCLICTASK_HOOK(U8 AlarmId)
{

}

void SWPTEST_EVENT_HOOK(U8 Eventid)		/*0.5s period*/
{
	
}

void SWPTEST_JOB_HOOK(U8 Jobid)
{
	
}

void SWPTEST_SWITCH_HOOK(U8 From, U8 To)
{
  
}

void SWPTEST_HARDWARE_INIT_HOOK(void)
{

}

void SWPTEST_MAIN_INIT_HOOK(void)
{

}

void SWPTEST_INIT_TASK_HOOK(void)
{
   
}

void SWPTEST_IDLE_TASK_HOOK(void)
{

}

void SWPTEST_BEFORESLEEP_PROC(void)
{
	
}

void SWPTEST_WAKEUPCHECK_PROC(void)
{
	
}

void SWPTEST_AFTERWAKEUP_PROC(void)
{
	
}
/**************** END OF FILE *****************************************/


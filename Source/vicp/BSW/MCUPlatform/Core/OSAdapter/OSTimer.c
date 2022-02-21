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
** ----------------------------------------------------------------------
* 0.1    Feb 10,2013    NI Rujin    Initial version
------------------------------------------------------------------------
* 0.2	 July 21,2016   PEI Jingli  Add new interface "OSADP_SWReset"
*-----------------------------------------------------------------------
* 0.3	 Dec 20,2016   ShangQiuju Remove unused include files.
*------------------------------------------------------------------------
* 0.4	 Jan 10,2017  ZHANG Jie  Add wdg_if.h for compile warning
 ----------------------------------------------------------------------
* 0.5    Jan 16,2017   RenWeimin  Add test code.
*-----------------------------------------------------------------------
* 0.6    Feb 09,2017   ZhangJie   Remove unused eol headfile.
*=====================================================================*/
#include <MCUBoard_I.h>
#include <Core_Cfg.h>
#include <define.h>
#include <config.h>
#include "wdg_if.h"
#include "mcu_if.h"

extern void  OSAlarm_AlarmHook (void);
extern void OSWDG_TimHook(void);
/*
*********************************************************************************************************
*                                               TICK HOOK
*
* Description: This function is called every tick.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/
void  OSTimeTickHook (void)
{
  OSAlarm_AlarmHook();
}

/***********************************************************************
*  Name        : OSADP_StartWdg
*  Description : deinit         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSADP_StartWdg(void)
{
#ifdef WDG_ENABLE
    WATCHDOG_Enable();   
#endif
    ///TODO: CHECK WATCHDOG
    //Clock_AWDTA_Set(E_AWDTD_LSI1D);
}

/***********************************************************************
*  Name        : OSADP_FeedWdg
*  Description : deinit         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSADP_FeedWdg(void)
{
#ifdef WDG_ENABLE
       WATCHDOG_Clear();	
#endif
}
/***********************************************************************
*  Name        : OSADP_InitWdg(void)
*  Description : Init wdg, called once         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSADP_InitWdg(void)
{
#ifdef WDG_ENABLE
     WATCHDOG_Init();
#endif
}

/***********************************************************************
*  Name        : OSADP_StopWdg
*  Description : deinit         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSADP_StopWdg(void)
{
#ifdef WDG_ENABLE
     WATCHDOG_Disable();
#endif
}

/***********************************************************************
*  Name        : OSADP_SWReset
*  Description : deinit
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSADP_SWReset(void)
{
    mcu_sw_reset();
}

/***********************************************************************
*  Name        : OSADP_FeedExtWdg
*  Description : deinit         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSADP_FeedExtWdg(void)
{

}

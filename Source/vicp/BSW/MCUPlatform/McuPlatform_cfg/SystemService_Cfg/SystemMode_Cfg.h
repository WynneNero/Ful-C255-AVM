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
* 0.2   Aug 31,2016             Re-INIT
* ----------------------------------------------------------------------
* 0.3   Now 10,2016  PEI Jingli  relocated _POWERONMCUMODE
* ----------------------------------------------------------------------
* 0.4    Dec 20,2016  ShangQiuju		Remove unused include files.
*-----------------------------------------------------------------------
* 0.5    Jan 24,2017   ZhangJie   Fix Coverity warnings.
*=====================================================================*/
#ifndef _SYSTEMMODE_CFG_H_
#define _SYSTEMMODE_CFG_H_ 
#include "CONFIG.H"

#define SYSMODE_MCUSLEEP_DEBUG 			STD_OFF 

#define SYSMODE_SUPPORT_WAKEUPCHECK		STD_OFF

/**** Definition of constants ****/
#define SYSMODE_NORMAL_SLEEPMODE		MCU_STOP_MODE
#define SYSMODE_WAKEUP_SLEEPMODE		MCU_STOP_MODE 
#define SYSMODE_AFTERRESET_RUNMODE 		MCU_FULL_MODE
#define SYSMODE_AFTERWAKEUP_RUNMODE 	MCU_FULL_MODE


/**** Definition of macros ****/
#define SYSMODE_CONTROL_POWERONMCUMODE(mode) mcu_to_wakup_mode((MCU_WAKEUP_TYPE)mode)
#if(SYSMODE_MCUSLEEP_DEBUG==STD_ON)
#define SYSMODE_CONTROL_SLEEPMCUMODE(mode)      /*while(SysMode_bAllowSleep == TRUE);*/
#define SYSMODE_CONTROL_WAKEUPMCUMODE(mode)
#else
#define SYSMODE_CONTROL_SLEEPMCUMODE(mode)  mcu_to_sleep_mode((MCU_SLEEP_TYPE)mode)
#define SYSMODE_CONTROL_WAKEUPMCUMODE(mode) mcu_to_wakup_mode((MCU_WAKEUP_TYPE)mode)
#endif

#define SYSMODE_ENABLE_WAKEUPIRQ(irqnum, type) {  EXTI_Config((EXTI_TYPE)irqnum, (EXTI_TRIGGER_TYPE)type); EXTI_Cmd((EXTI_TYPE)irqnum, ENABLE);}
#define SYSMODE_DISABLE_WAKEUPIRQ(irqnum)   {EXTI_Cmd((EXTI_TYPE)irqnum, DISABLE);}

extern void Application_ResetHandle(void);
extern void Application_RunHandle(void);
extern void Application_TimerWakeupHandle(void);
extern void Application_AfterSleepHandle(void);

#define SYSMODE_CHANGEMODE(mode)
#define APPLICATION_RESETPROC()  Application_ResetHandle()
#define APPLICATION_RUNPROC()     Application_RunHandle()
#define APPLICATION_WAKEUPCHECKPROC() Application_TimerWakeupHandle()
#define APPLICATION_AFTERWAKEUPPROC() Application_AfterSleepHandle()

extern void SysMode_apMainInitContainer(void);
extern void SysMode_apSystemInitContainer(void);
extern void SysMode_apWakeupCheckContainer(void);
extern void SysMode_apBeforeSleepContainer(void);
extern void SysMode_apAfterSleepContainer(void);
/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/


#endif /*_SYSTEMMODE_CFG_H_*/

/****************************** END OF FILE ***************************/


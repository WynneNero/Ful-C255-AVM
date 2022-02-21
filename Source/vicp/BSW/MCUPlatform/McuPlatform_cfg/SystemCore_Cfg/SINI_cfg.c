/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                         *
*   AUTHOR     :                                       *
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
* 0.1    Aug 31 2016            Re-init
*-----------------------------------------------------------------------
* 0.2   Jan 24,2017   ZhangJie   Fix Coverity warnings.
*=====================================================================*/
#include <Core_I.h>

extern void  MCU_MainInit(void);
extern void OSAlarm_InitAlarmTimer(void);

extern void SysSwitch_Init(void);
extern void SysJob_Init(void);
extern void SysEvt_Init(void);
extern void SysCycle_Init(void);
/*extern void OSWDG_Init(void);*/

/*before go to main, run in reset handler, be careful to call C code*/
/*Init MCU and clock*/
void SINI_apHardwareResetContainer(void)
{
    /* Add the system core initialization function here! */
}

/*before start OS, run in Main*/
/*init system core, init phase 1 driver*/
void SINI_apCoreInit1Container(void)
{
    /* Add the system core initialization function here! */
#ifdef WDG_ENABLE
    OSWDG_Init();
#endif
    SysSwitch_Init();
    SysJob_Init();
    SysEvt_Init();
    SysCycle_Init();
    OSAlarm_InitAlarmTimer();
}

/*Before all task run,Run in init task*/
/*init system service init phase 2 driver*/
void SINI_apCoreInit2Container(void)
{
    /* Add the system core initialization function here! */
    /*Add the System service initialization function here!*/

}

/*Idle task*/
void SINI_apCoreIdleContainer(void)
{
    /* Add the application initialization function here! */
}
/**************** END OF FILE *****************************************/


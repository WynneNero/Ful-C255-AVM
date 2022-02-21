/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.         *
*                 All Rights Reserved.              *
*   Department : CT AD                          *
*   AUTHOR     :                            *
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
* 0.2    Aug 31,2016            Re-Init
*-----------------------------------------------------------------------
* 0.3   Jan 24,2017   ZhangJie   Fix Coverity warnings.
*=====================================================================*/
#include<Core_I.h>
#include <Service_HOOKS.h>
#include <Tools.h>
#include "SINI.h"

extern void SysMode_HardwareRest(void);
extern void SysMode_MainInit(void);
extern void SysMode_SystemInit(void);
extern void SysMode_SystemIdle(void);
/*---Global-----------------------------------------------------------*/

extern void SINI_apHardwareResetContainer(void);
extern void SINI_apCoreInit1Container(void);
extern void SINI_apCoreInit2Container(void);
extern void SINI_apCoreIdleContainer(void);

/***********************************************************************
*  Name        : SINI_HardwareInit
*  Description : Step 1: hardware is reset, run in rest isr, before call C_Lib
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SINI_HardwareInit(void)
{
    /*Lib_RunContainer((Func_Void_Proc*)&SINI_apHardwareResetContainer[0]);*/

    /*Add the System service initialization function here!*/
    SysMode_HardwareRest();
#if(SERVICE_HOOKS_EN==1u)
    SERVICE_HARDWARE_INIT_HOOK();
#endif
}

/***********************************************************************
*  Name        : SINI_MainInit
*  Description : Step 2: system is init, run in mian
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SINI_MainInit(void)
{

    /*Step 1: inti OS component*/
    OSAPI_InitOS();

    /*Step2: init phase 1 of system core  and basic driver*/
    SINI_apCoreInit1Container();
    /*Step3: init phase 1 of system service and application*/
    SysMode_MainInit();

    /*Step4: start os*/

#if(SERVICE_HOOKS_EN==1u)
    SERVICE_MAIN_INIT_HOOK();
#endif

    OSAPI_StartOS();
}

/***********************************************************************
*  Name        : SINI_TaskInit
*  Description : Step 3: Os is stared, run in init task
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SINI_TaskInit(void)
{
    /*Step1:Create all task and OS resource*/
    OSAPI_CreateSystem();

    /*Step2: init phase 2 of system core  and basic driver*/
    /*Lib_RunContainer((Func_Void_Proc*)&SINI_apCoreInit2Container[0]);*/
    SINI_apCoreInit2Container();
    /*Step3: init phase 2 of system service and application*/
    SysMode_SystemInit();

#if(SERVICE_HOOKS_EN==1u)
    SERVICE_INIT_TASK_HOOK();
#endif
}

/***********************************************************************
*  Name        : SINI_TaskIdle
*  Description : Step 4: check if go to sleep, run in idle task
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SINI_TaskIdle(void)
{

    /*Lib_RunContainer((Func_Void_Proc*)&SINI_apCoreIdleContainer[0]);*/
    SINI_apCoreIdleContainer();
    SysMode_SystemIdle();

#if(SERVICE_HOOKS_EN==1u)
    SERVICE_IDLE_TASK_HOOK();
#endif
}

/**************** END OF FILE *****************************************/


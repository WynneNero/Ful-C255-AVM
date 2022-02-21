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
*----------------------------------------------------------------------
*  0.1   Sep 26,2016                   Init version
*----------------------------------------------------------------------
*  0.2  Jan 12,2017     ZhangJie  Fix Coverity warning.
*----------------------------------------------------------------------
*  0.3  Jan 16,2017     RenWeimin  Add test code.
*----------------------------------------------------------------------
*  0.4  Jan 24,2017     ZhangJie  Fix Coverity phase2 warning.
*=====================================================================*/
#ifndef _SYSTEM_STATUS_H_
#define _SYSTEM_STATUS_H_
#include "CONFIG.H"
#include "TYPES.H"
#include "SystemStatus_cfg.h"
/**** Definition of constants ****/

/**** Definition of macros ****/
/**** Declaration of constants ****/
/*#define HB_TEST*/
/**** Declaration of variables ****/
/*#define HB_TEST*/

#define SYSTEMPATTERN 0xA5u
enum
{
    NORMAL_MODE=0x01,
    FCT_MODE=0x0A,/*tmp modify by wangyong*/
    EOL_MODE=0x0B,
};

typedef enum
{
    SAVING_IDLE,
    SAVING_ACCON,
    SAVING_ACCOFF,
    SAVING_TOACCOFF,
    SAVING_OFFTIMEOUT,
    SAVING_WAKEUPTIMEOUT,
    SAVING_MAXSTATE
} E_SAVING_STATE;

typedef enum
{
    E_APPRUN_IDLE,
    E_APPRUN_FIRST_ENTER_NORMAL_TIMEOUT,
    E_APPRUN_ALLALLOWSLEEP,
    E_APPRUN_TIMEOUT,
    APPRUN_MAXSTATE
} E_APPRUN_STATE;

typedef enum
{
    RESET_WAIT_POWER_NORMAL_STATE,
    RESET_INIT_STATE,
    RESET_LOADSTARTUP_STATE,
    RESET_WORKINGMODECHECK_STATE,
    RESET_MAX_STATE
} E_RESET_STATE;

typedef enum
{
    MODESWITCH_IDLE_STATE,
    MODESWITCH_NORMALTOSLEEP_STATE,
    MODESWITCH_SLEEPTONORMAL_STATE,
    MODESWITCH_POWERTONORMAL_STATE,
    MODESWITCH_EXITSWITCH_STATE,
    MODESWITCH_MAX_STATE,
} E_MODESWITCH_STATE;

typedef enum
{
    POWERTONORMAL_STEP1CHECK,
    POWERTONORMAL_STEP2,
    POWERTONORMAL_DONE,
    POWERTONORMAL_MAXSTEP,
} E_POWERTONORMAL_STEP;

typedef enum
{
    NORMALTOSLEEP_STEP1,
    NORMALTOSLEEP_STEP2,
    NORMALTOSLEEP_STEP3,
    NORMALTOSLEEP_DONE,
    NORMALTOSLEEP_MAXSTEP,
} E_NORMALTOSLEEP_STEP;

typedef enum
{
    FCT_INVALID_STATE,
    FCT_INIT_STATE,
    FCT_ENTERTEST,
    FCT_EXITTEST,
    FCT_IDLE,
    EOL_INIT_STATE,
    EOL_ENTERTEST,
    EOL_EXITTEST,
    EOL_IDLE,
    FCT_MAX_STATE
} E_FCT_STATE;

typedef enum
{
    SLEEPTONORMAL_STEP1,
    SLEEPTONORMAL_STEP2,
    SLEEPTONORMAL_STEP3,
    SLEEPTONORMAL_STEP4,
    SLEEPTONORMAL_DONE,
    SLEEPTONORMAL_MAXSTEP,
} E_SLEEPTONORMAL_STEP;

typedef enum
{
    E_MODESWITCH_NONE,
    E_NORMALTOSLEEP,
    E_SLEEPTONORMAL,
    E_POWERTONORMAL,
    E_MODESWITCH_MAXTYPE
} E_MODESWITCH_TYPE;

enum
{
    SLEEP_PREPARE_STATE,
    SLEEP_MONITOR_STATE,
    SLEEP_UNDV2INT_STATE,
    SLEEP_MODULEINT_STATE,
    SLEEP_TIMERINT_STATE,
    SLEEP_IOCHECK_STATE,
    SLEEP_DONE_STATE,
    SLEEP_MAX_STATE
};

typedef enum
{
    NORMAL_IDLE_STATE,
    NORMAL_FROMSLEEP_STATE,
    NORMAL_FROMRESET_STATE,
    NORMAL_MONITOR_STATE,
    NORMAL_MAX_STATE
} E_NORMAL_STATE;



/**** Declaration of functions ****/
extern void Application_DisableAllWakeupInt(void);
extern void  Application_ECallEvt(void);
extern void Application_TimerWakeupHandle(void);
extern void Application_AfterSleepHandle(void);
extern void  Application_ACCOnIsr(void);
extern void Application_CANInhIsr(void);
extern void Application_ReverseINIsr(void);
extern BOOL  Application_IsSleepAllowed(void);
#ifdef USE_BACKUP_BAT
extern void  Application_UDV2Isr(void);
#endif
extern void Application_GotoSleep(void);
extern void Application_SystemStateHandle(void);
extern void Application_OSReady(void);
extern void Application_OnNetworkDisconnected(void);
extern void Application_OnNetworkConnected(void);
extern void Application_S0Init(void);
extern E_FCT_STATE Appliaction_GetFctState(void);
U16 Application_FCTGetWaitRepTimer(void);
void Application_FCTSetWaitRepTimer(U16 WaitTimer);
BOOL Appliaction_CheckCrashInSig(void);
BOOL Application_CheckEcallSig(void);


#endif /*_DUMYAPP_H_*/

/****************************** END OF FILE ***************************/


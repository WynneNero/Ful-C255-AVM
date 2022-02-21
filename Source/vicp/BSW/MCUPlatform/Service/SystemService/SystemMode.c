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
* Version       Date     Name       Changes and comments
* 0.1    Aug 31,2016                  Re-arthitecture
*-----------------------------------------------------------------------
* 0.2    Nov 30,2016  PEI Jingli Disable/Enable interrupt during sleep-wakeup switch. 
*----------------------------------------------------------------------
* 0.3    Dec 20,2016   add include files.
*------------------------------------------------------------------------
* 0.4    Jan 24,2017  ZhangJie  Fix Coverity warnings.
*-----------------------------------------------------------------------
* 0.5    Feb 09,2017   ZhangJie   Using HAL to delivery data.
*=====================================================================*/
#include <Service_HOOKS.h>
#include <Tools.h>
#include <SystemMode_Cfg.h>
#include "SystemMode.h"
#include "mcu_if.h"
#include "exti_if.h"

BOOL SysMode_bAllowSleep;
U8 SysMode_u8Mode=(U8)SYSMODE_RESET;

/***********************************************************************
*  Name        : SysMode_GetSystemMode
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
U8 SysMode_GetSystemMode(void)
{
    if(SysMode_u8Mode>(U8)SYSMODE_MAXTYPE)
    {
        SysMode_u8Mode=SYSMODE_MAXTYPE;
    }
    return SysMode_u8Mode;
}


/***********************************************************************
*  Name        : SysMode_HardwareRest
*  Description : Run in reset_handler, before main()
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysMode_HardwareRest(void)
{
    SYSMODE_CONTROL_POWERONMCUMODE(SYSMODE_AFTERRESET_RUNMODE);
}

/***********************************************************************
*  Name        : SysMode_MainInit
*  Description : Run in main()
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysMode_MainInit(void)
{
    SysMode_bAllowSleep= TRUE;
    SysMode_u8Mode=(U8)SYSMODE_MAIN;
    SysMode_apMainInitContainer();
    SYSMODE_CHANGEMODE(SysMode_u8Mode);
    APPLICATION_RESETPROC();
}

/***********************************************************************
*  Name        : SysMode_SystemInit
*  Description : run in Init task
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysMode_SystemInit(void)
{
    SysMode_u8Mode=(U8)SYSMODE_SYSTEMRUN;
    SYSMODE_CHANGEMODE(SysMode_u8Mode);
    SysMode_apSystemInitContainer();
    APPLICATION_RUNPROC();
}


/***********************************************************************
*  Name        : SysMode_SystemIdle
*  Description : run in Idle task
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysMode_SystemIdle(void)
{

}
/***********************************************************************
*  Name        : SysMode_ToSleep
*  Description : mcu to sleep mode, and wakeup check
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysMode_ToSleep(void)
{
    /* Check if entering the Low Power mode is allowed */
    if(SysMode_bAllowSleep==FALSE)
    {
        /* Entering the LP mode is not allowed. set the Flag to TRUE agian so that
           next time sleep mode could be enterred.*/
    }
    else
    {
        /* Entering the LP mode is allowed */
        SysMode_apBeforeSleepContainer();
        mcu_disable_all_interrupt();
        if(SysMode_bAllowSleep == TRUE)
        {
#if(SERVICE_HOOKS_EN==1u)
            SERVICE_BEFORESLEEP_PROC();
#endif

            SysMode_u8Mode=(U8)SYSMODE_SLEEP;
            SYSMODE_CHANGEMODE(SysMode_u8Mode);
            SYSMODE_CONTROL_SLEEPMCUMODE(SYSMODE_NORMAL_SLEEPMODE);
            mcu_enable_all_interrupt();
            SysMode_u8Mode=(U8)SYSMODE_WAKUP;
            SYSMODE_CHANGEMODE(SysMode_u8Mode);


#if(SYSMODE_SUPPORT_WAKEUPCHECK == STD_ON)
            /* For platforms where the processor is not stopped in the Low Power
             *  Mode: call cyclic check function and leave this loop when a Wakeup
             *  event has been detected.
             */

            /* Make possible wake up with interrupts. 
            IREXT_DirectEnable(); 
            */

            /* Wait until a wake happen (not from IDLE mode). */
            while(SysMode_bAllowSleep == TRUE)
            {
                SysMode_apWakeupCheckContainer();
#if(SERVICE_HOOKS_EN==1u)
                SERVICE_WAKEUPCHECK_PROC();
#endif
                APPLICATION_WAKEUPCHECKPROC();


                if(SysMode_bAllowSleep==TRUE)
                {
                    SysMode_u8Mode=(U8)SYSMODE_SLEEP;
                    SYSMODE_CHANGEMODE(SysMode_u8Mode);
                    SYSMODE_CONTROL_SLEEPMCUMODE(SYSMODE_WAKEUP_SLEEPMODE);
                    SysMode_u8Mode=(U8)SYSMODE_WAKUP;
                    SYSMODE_CHANGEMODE(SysMode_u8Mode);
                }
            };
            /*IREXT_DirectDisable();        Disable all interrupts */
#endif

            SYSMODE_CONTROL_WAKEUPMCUMODE(SYSMODE_AFTERWAKEUP_RUNMODE);
        }
        else
        {
            mcu_enable_all_interrupt();
        }
        SysMode_apAfterSleepContainer();
    }

#if(SERVICE_HOOKS_EN==1u)
    SERVICE_AFTERWAKEUP_PROC();
#endif

    APPLICATION_AFTERWAKEUPPROC();

    /*CAUTION: if wakeup ISR is not disable before, system have one risk to enter to sleep*/
    /*et the flag to TRUE again after wakeup check procedure.*/
    /*since it may be changed by wakeup ISR*/
    /*Wakeup interrup must be disabled before*/
    SysMode_bAllowSleep = TRUE;
}

/***********************************************************************
*  Name        : SysMode_DisableWakeupInt
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysMode_DisableWakeupInt(U32 IRQ)
{
    SYSMODE_DISABLE_WAKEUPIRQ(IRQ);
}

/***********************************************************************
*  Name        : SysMode_EnableWakeupInt
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysMode_EnableWakeupInt(U32 IRQ,U32 type)
{
    SYSMODE_ENABLE_WAKEUPIRQ(IRQ,type);
}

/***********************************************************************
*  Name        : SysMode_PreventSleep
*  Description : call in wakup isr or wakeup check to prevent sleep
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SysMode_PreventSleep(void)
{
    SysMode_bAllowSleep=FALSE;
}
/**************** END OF FILE *****************************************/


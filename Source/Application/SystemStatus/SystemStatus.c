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
* Ver  Date               Name             Changes and comments
 ----------------------------------------------------------------------
*  0.1   Sep 26,2016   PEI Jingli         add EED handler
 ----------------------------------------------------------------------
*  0.2   Oct 24,2016    PEI Jingli         Modify for using-wrong.
---------------------------------------------------------------------
*  0.3   Dec 20,2016    ShangQiuju    Add Acc sleep check condition
*-----------------------------------------------------------------------
*  0.4   Dec 21,2016    PeiJingLi        Change include file patch according hw select option.
*----------------------------------------------------------------------
*  0.5   Dec 22,2016    Pei Jingli        Add 64pin hw switch 
*----------------------------------------------------------------------
*  0.6   Dec 22,2016    ShangQiuju    Use HAL_DevGetPowerStatus after hal update.
*----------------------------------------------------------------------
*  0.7  Jan 06,2017     ShangQiuju  Update CS_SIG_AsyncReceive according SIG module update.
*----------------------------------------------------------------------
*  0.8  Jan 13,2017     ZhangJie  Fix Coverity warning.
*----------------------------------------------------------------------
*  0.9  Jan 16,2017     RenWeimin  Add test code.
*----------------------------------------------------------------------
*  1.0  Jan 24,2017     ZhangJie  Fix Coverity phase2 warning.
*----------------------------------------------------------------------
*  1.1  Feb 09,2017     ZhangJie  Using signal to delivery data.
*=====================================================================*/
#include "ComplexDrvier_Globaldef_IF.H"
#include "Sig_Combine.H"
#include "SystemStatus.h"
#include "Signal_if.h"
#include "SystemState_Cfg.h"
#include "Hal_if.h"
#include "EEPData.h"

#define	SAVING_TIMEOUT	    10u	/* 100mS */
#define	WAKEUP_TIMEOUT	 10u	/* 100mS */
#define	APPRUN_TIMEOUT	300u		/* 3S */
#define NORMAL_TO_SLEEP_TIME_OUT  100u  /* S */

/* Function Config information */
BOOL isWakeup;
BOOL bIsSavingTimeout;
BOOL bIsWakeupTimeout;
BOOL bIsAppRunTimeout;
BOOL bSleepAllow;
BOOL bPowerAllow;
BOOL bPowerOnReq;
BOOL bSleepReq;
BOOL bWakeupReq;
BOOL bResetReq;
BOOL bPhyACCOn;
BOOL bSleepAllowedByAllApp;

U8 uWakeupReason;
U16 tSavingTimeoutTick;
U16 tWakeupTimeoutTick;
U16 tAppRunTimeoutTick;
U16 uNormalToSleepTimeCnt;

E_SYSTEMSTATE_TYPE eSystemState;
E_WAKEUP_REASON eWakeUpReason;
E_SYSTEM_VOLTAGE_STATUS eVoltStatus;
E_SAVING_STATE eSavingState;
E_APPRUN_STATE eAppRunState;
E_RESET_STATE eResetState;
E_MODESWITCH_STATE eModeSwitchState;
E_POWERTONORMAL_STEP ePowerToNormalStep;
E_NORMALTOSLEEP_STEP eNormalToSleepStep;
E_SLEEPTONORMAL_STEP eSleepToNormalStep;
E_MODESWITCH_TYPE eModeSwitchType;
E_NORMAL_STATE eNormalState;

U16 WaitRepTimer = 0u;
BOOL b_StartTimeOut = FALSE;
BOOL b_enterfEep = FALSE;

void OSReady(void);
void DisableSocPower(void);
void EnableSocPower(void);
/***********************************************************************
*  Name        : Application_TimeoutHandle
*  Description : Check wakeup timeout      
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Application_TimeoutHandle(void)
{
	U8 bI_ACCOn = FALSE;
	U8 bI_Vol = V_NORMAL;
	// 1. Saving timeout check
	#ifdef POWERVOLTAGEWAKEUP
//	CS_SIG_SyncReceive(SIG_ACCSTATUS, (U8*)&bI_ACCOn);
//	CS_SIG_SyncReceive(SIG_VOLTAGEFAIL_STATUS, (U8*)&bI_Vol);
	if(bI_ACCOn)
	{
		if((bI_Vol == V_L_ABNORMAL) || (bI_Vol == V_H_ABNORMAL))
		{
			bI_ACCOn=FALSE;
		}
		else
		{
			bI_ACCOn=bI_ACCOn&0x01;
		}
	}
	#else
	CS_SIG_SyncReceive(SIG_ACCSTATUS, (U16*)&bI_ACCOn);
    bI_ACCOn=bI_ACCOn&0x01;
	#endif
	switch(eSavingState)
	{
		case SAVING_IDLE:
			if(bI_ACCOn)
			{
				bIsSavingTimeout = FALSE;		
				bIsWakeupTimeout = FALSE;	
                tSavingTimeoutTick = 0u;
                eSavingState = SAVING_ACCON;				
            }
            else
            {
                bIsSavingTimeout = FALSE;		
                bIsWakeupTimeout = FALSE;				
                tWakeupTimeoutTick = 0u;
                eSavingState = SAVING_ACCOFF;
            }
        break;
        
		case SAVING_TOACCOFF:
            /* 1. Check ACC Status */
			if(bI_ACCOn)
			{
				eSavingState = SAVING_ACCON;
			}
            /* 2. Check saving timeout tick */
			else if(tSavingTimeoutTick++>=SAVING_TIMEOUT)
			{
//				bIsSavingTimeout = TRUE;  // LLF_MARK  temp cause it will system enter sleep  
				eSavingState = SAVING_OFFTIMEOUT;
			}
            else
            {
                /*nothing to do*/
            }
        break;
        
        case SAVING_ACCON:
            if(FALSE == bI_ACCOn)
            {
                /* 1. Reset saving timer tick */
                bIsSavingTimeout = FALSE;
                tSavingTimeoutTick = 0u;
                eSavingState = SAVING_TOACCOFF;
            }
            else
            {
                /*nothing to do*/
            }
        break;
        
        case SAVING_ACCOFF:
            /* 1. Check ACC Status */
            tWakeupTimeoutTick++;
            if(bI_ACCOn)
            {
                eSavingState = SAVING_ACCON;
            }            
            /* 2. Check Off timeout */
            else if(tWakeupTimeoutTick>=WAKEUP_TIMEOUT)
            {
//                bIsWakeupTimeout = TRUE;       // LLF_MARK  temp cause it will system enter sleep 
                eSavingState = SAVING_WAKEUPTIMEOUT;
            }
            else
            {
                /*nothing to do*/
            }
        break;
            
        case SAVING_OFFTIMEOUT:
        /* Only needs to check ACC ON here.*/
            if(bI_ACCOn)
            {
                bIsSavingTimeout = FALSE;			
                bIsWakeupTimeout = FALSE;
                eSavingState = SAVING_ACCON;
            }
            else
            {
                /*nothing to do*/
            }
        break;
        
        case SAVING_WAKEUPTIMEOUT:
        /*Only needs to check ACC ON here.*/
            if(bI_ACCOn)
            {
                bIsSavingTimeout = FALSE;			
                bIsWakeupTimeout = FALSE;
                eSavingState = SAVING_ACCON;
            }
            else
            {
                /*nothing to do*/
            }
        break;			
        
        default:
        break;
    }
}

/***********************************************************************
*  Name        : Application_AppRunTimeoutHandle
*  Description : Check App run timeout      
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Application_AppRunTimeoutHandle(void)
{
    U8 bS_SleepAllow = 0x0u;

    CS_SIG_SyncReceive((U16)SIG_SLEEP_ALLOW, &bS_SleepAllow);
    bS_SleepAllow=bS_SleepAllow&0x01u;
    
    switch(eAppRunState)
    {
        case E_APPRUN_IDLE:
            if(bS_SleepAllow)
            {
                bIsAppRunTimeout = FALSE;		
                tAppRunTimeoutTick = 0u;
                eAppRunState = E_APPRUN_ALLALLOWSLEEP;				
            }
            else
            {
                bIsAppRunTimeout = FALSE;		
            }
        break;
        
        case E_APPRUN_ALLALLOWSLEEP:
        /* 1. Check Sleep allow Status */
            if(((U8)0) == bS_SleepAllow)
            {
                eAppRunState = E_APPRUN_IDLE;		
            }
            /* 2. Check saving timeout tick */
            else if(tAppRunTimeoutTick++>=APPRUN_TIMEOUT)
            {
                bIsAppRunTimeout = TRUE;
                eAppRunState = E_APPRUN_TIMEOUT;
            }
            else
            {
                /*nothing to do*/
            }
        break;
        
        case E_APPRUN_TIMEOUT:
        /* 1. Check Sleep allow Status */
            if( 0u == bS_SleepAllow)
            {
                bIsAppRunTimeout = FALSE;
                eAppRunState = E_APPRUN_IDLE;		
            }
            else
            {
                /*nothing to do*/
            }
        break;
        
        default:
        break;
    }
}

/***********************************************************************
*  Name        : Application_SleepAllowHandle
*  Description : Check sleep allow conditions         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Application_SleepAllowHandle(void)
{    
  /*BOOL bIsCanSleep;*/
  
	/* 1. Saving or Wakeup timeout check */
	Application_TimeoutHandle();
	
	/* 2. Application sleep allow check */
	Application_AppRunTimeoutHandle();
	
	if(bIsSavingTimeout||bIsWakeupTimeout)
	{
            U8 bS_SleepAllow = 1u;
            /*intemediate flag to notify modem manager begin sleep processing.*/
            bSleepAllowedByAllApp = TRUE;        	              
            bSleepAllow = TRUE;
            CS_SIG_SyncSend((U16)SIG_SLEEP_ALLOW, &bS_SleepAllow);
	}
	else
	{
            U8 bS_SleepAllow = 0;
    	/*intemediate flag to notify modem manager begin sleep processing.*/
    	    bSleepAllowedByAllApp = FALSE;
  	        bSleepAllow = FALSE;
            CS_SIG_SyncSend(SIG_SLEEP_ALLOW, &bS_SleepAllow);
	}

}


/***********************************************************************
*  Name        : Application_IsSleepAllowed
*  Description : reruen sleep allow by app flag        
*  Parameter   : None
*  Returns     : BOOL
***********************************************************************/
BOOL  Application_IsSleepAllowed(void)
{
    return bSleepAllowedByAllApp;
}

/***********************************************************************
*  Name        : Application_S0Init
*  Description : init at s0        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Application_S0Init(void)
{
	WaitRepTimer = 0u;
	b_StartTimeOut = FALSE;
	b_enterfEep = FALSE;
       EnableSocPower();
	return;
}

/***********************************************************************
*  Name        : Application_ResetStateHandle
*  Description : Reset state handler         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Application_ResetStateHandle(void)
{	
    switch(eResetState)
    {
        case RESET_WAIT_POWER_NORMAL_STATE:
#if 0  /*  0 for no powermanager FW */
//            CS_SIG_SyncReceive((U16)SIG_VOLTAGEFAIL_STATUS , (U8*)&eVoltStatus);
#else
            eVoltStatus = V_NORMAL;
#endif
            if(eVoltStatus == V_NORMAL)
            {
                eResetState = RESET_INIT_STATE;
            }	    
            else
            {
                /*nothing to do*/
            }    
        break;

        case RESET_INIT_STATE:
            if(TRUE==EED_LoadStartup())
            {
            /* 1. Set MCU work mode: TSWP DONE*/
            /* 2. Config MCU IO work mode: TSWP DONE*/
            /* 3. Config power supply work mode: TSWP DONE*/
            /* 4. SW System initialization: TSWP DONE*/
            /* All above steps are already done IN TSWP before.*/                
            eResetState = RESET_LOADSTARTUP_STATE;                      
            }
            else
            {
                /*nothing to do*/
            }
        break;
        
        case RESET_LOADSTARTUP_STATE:
            if(TRUE==EED_isStartupLoad())
            {
                eResetState = RESET_WORKINGMODECHECK_STATE;    
            }
            else
            {
                /*nothing to do*/
            }
        break;
        
        case RESET_WORKINGMODECHECK_STATE:	
            bPowerAllow = TRUE;
            eSystemState = SYSTEM_MODESWITCH;
//            CS_SIG_SyncSend((U16)SIG_SYSTEM_STATUS, (U8*)&eSystemState);
            eModeSwitchState = MODESWITCH_IDLE_STATE;
            /* Switch to S2 */
            SysState_SetRequest(SYSSTAT_MODESWITCH_STATE);
        break;
        
        default:
        break;
    }
}

/***********************************************************************
*  Name        : Application_NormalStateHandle
*  Description : Normal state handler         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Application_NormalStateHandle(void)
{
    switch(eNormalState)
    {
        case NORMAL_IDLE_STATE:
            switch(eModeSwitchType)
            {
                case E_SLEEPTONORMAL:
                    eNormalState = NORMAL_FROMSLEEP_STATE;
                    eAppRunState = E_APPRUN_IDLE;
                break;
                
                case E_POWERTONORMAL:
                    eNormalState = NORMAL_FROMRESET_STATE;		
                    eAppRunState = E_APPRUN_IDLE;			
                break;

                default:
                break;
            }
        break;
        
        case NORMAL_FROMSLEEP_STATE:
            switch(eWakeUpReason)
            {
                case WAKEUP_CANIN:
                case WAKEUP_REVERSE:
                case WAKEUP_ACCON:
                break;
                default:
                break;
            }
            eNormalState = NORMAL_MONITOR_STATE;
            eSavingState = SAVING_IDLE;			
        break;
        
        case NORMAL_FROMRESET_STATE:
            /* All below modules needs to be initialized: DONE by Modules */
            eNormalState = NORMAL_MONITOR_STATE;
            eSavingState = SAVING_IDLE;
        break;
        
        case NORMAL_MONITOR_STATE:
            /* Detect allow to sleep, switch to mode switch state */
            Application_SleepAllowHandle();
            if(bSleepAllow)
            {
                eSystemState = SYSTEM_MODESWITCH;		
//                CS_SIG_SyncSend((U16)SIG_SYSTEM_STATUS, (U8*)&eSystemState);				
                eModeSwitchState = MODESWITCH_IDLE_STATE;				
                /* Switch to S2 */
                SysState_SetRequest(SYSSTAT_MODESWITCH_STATE);
            }		
            else
            {
                /*nothing to do*/
            }
        break;
        
        default:
        break;
    }
}

/***********************************************************************
*  Name        : Application_GotoSleep
*  Description :          
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Application_GotoSleep(void)
{
	uWakeupReason = 0;	
	CS_SIG_SyncSend((U16)SIG_WAKEUP_REASON, (U8*)&uWakeupReason);	
	SysMode_ToSleep();
}

/***********************************************************************
*  Name        : Application_PowerToNormalHandle
*  Description : Power to normal handler         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Application_PowerToNormalHandle(void)
{
    switch(ePowerToNormalStep)
    {
        case POWERTONORMAL_STEP1CHECK:
        /* Check CAN & EEPROM initialization status */
        if(EED_IsLoad())
        {
            bPowerOnReq = TRUE;
//            CS_SIG_SyncSend((U16)SIG_POWERON_REQ, (U8*)&bPowerOnReq);	
            bPowerAllow = FALSE;
            eModeSwitchType = E_POWERTONORMAL;			
            eModeSwitchState = MODESWITCH_EXITSWITCH_STATE;
        }
        else
        {
            /*nothing to do*/
        }
        break;

        
        case POWERTONORMAL_DONE:
        /* DO NOTHING */
        break;
        
        default:
        break;
    }
}

/***********************************************************************
*  Name        : Application_NormalToSleepHandle
*  Description :  Normal to Sleep handler         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Application_NormalToSleepHandle(void)
{
    switch(eNormalToSleepStep)
    {
        case NORMALTOSLEEP_STEP1:
            bSleepReq = TRUE;
//            CS_SIG_SyncSend((U16)SIG_SLEEP_REQ, (U8*)&bSleepReq);
            EED_Download_Request();
            eNormalToSleepStep = NORMALTOSLEEP_STEP2;
            uNormalToSleepTimeCnt = 0u;
        break;
        
        case NORMALTOSLEEP_STEP2:
        /* 1. Check all device status */
            if(E_DEV_SPOWEROFF == HAL_DevGetPowerStatus(DEV_SOC))
            {
                eNormalToSleepStep= NORMALTOSLEEP_STEP3;
            }
            else
            {
                if(E_DEV_SPOWERON == HAL_DevGetPowerStatus(DEV_SOC))
                {
                    DisableSocPower();
                }
                else
                {
                    /*nothing to do*/
                }
            }
		 break;
        
        case NORMALTOSLEEP_STEP3:
            /* Enable Interrupt */
#ifdef USE_REVERSE_INTERRUPT_OPTION
            SysMode_EnableWakeupInt(INT_REVERSE_WAKEUP, EXTI_TRIGGER_RISING);
#endif
#ifdef USE_CAN_WAKEUP_OPTION
            SysMode_EnableWakeupInt(INT_CAN_WAKEUP, EXTI_TRIGGER_LOW);
#endif
#ifdef USE_ACC_WAKEUP_OPTION
            {  /* Fix interface using error */
				#ifdef POWERVOLTAGEWAKEUP
                	U8 Acctemp=0; 
					U8 Voltemp=0;
//                	CS_SIG_SyncReceive((U16)SIG_ACC_DI_STATUS, &Acctemp);
//					CS_SIG_SyncReceive((U16)SIG_HCANPWR_DI_STATUS, &Voltemp);
                	if(Acctemp&0x01)
                	{
						if(Voltemp&0x01)
						{
							bPhyACCOn = TRUE;
						}
						else
						{
							bPhyACCOn = FALSE;						
							SysMode_EnableWakeupInt(INT_VOL_WAKEUP, EXTI_TRIGGER_RISING);
						}
                	}
					else
					{
						bPhyACCOn = FALSE;						
						SysMode_EnableWakeupInt(INT_ACC_WAKEUP, EXTI_TRIGGER_RISING);
					}
				#else
					U8 Acctemp=0; 
//					CS_SIG_SyncReceive((U16)SIG_ACC_DI_STATUS, &Acctemp);					
					SysMode_EnableWakeupInt(INT_ACC_WAKEUP, EXTI_TRIGGER_RISING);
					if(Acctemp&0x01)
					{
						bPhyACCOn = TRUE;
					}
                	else
                	{
                    	bPhyACCOn = FALSE;
                	}	
				#endif
            }
            if(bPhyACCOn)
            {			
                SysMode_PreventSleep();
            }
            else
            {
                /*nothing to do*/
            }
#endif
            eModeSwitchType = E_NORMALTOSLEEP;
            eModeSwitchState = MODESWITCH_EXITSWITCH_STATE;
        break;
        
        default:
        break;
    }
}

/***********************************************************************
*  Name        : Application_SleepToNormalHandle
*  Description :  Sleep to Normal handler         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Application_SleepToNormalHandle(void)
{
    switch(eSleepToNormalStep)
    {
        case SLEEPTONORMAL_STEP1:
            /* 1. Set MCU to normal work mode*/
            /* 2. Disable wakeup interrupt*/
            /* 3. Config MCU IO work mode*/
            /* 4. Config power supply work mode*/
            /* All above steps DONE in TSWP*/
            bWakeupReq = TRUE;
//            CS_SIG_SyncSend((U16)SIG_WAKEUP_REQ, (U8*)&bWakeupReq);
            bSleepAllow = FALSE;
            eModeSwitchType = E_SLEEPTONORMAL;
            eModeSwitchState = MODESWITCH_EXITSWITCH_STATE;			
#ifdef QUCIK_WAKEUP_IN_3_SECOND
            uFirstEnterNormalTimecnt = FIRST_ENTER_NORMAL_TIME_OUT;
#endif
        break;
        
        default:
        break;
    }
}

/***********************************************************************
*  Name        : Application_FCTStateHandle
*  Description : FCTTest state handler         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Application_ModeSwitchStateHandle(void)
{
    switch(eModeSwitchState)
    {
        case MODESWITCH_IDLE_STATE:
            if(bPowerAllow)
            {
                bResetReq = TRUE;
                eModeSwitchState = MODESWITCH_POWERTONORMAL_STATE;
                ePowerToNormalStep = POWERTONORMAL_STEP1CHECK;
            }
            else if(bSleepAllow)
            {
                bSleepReq = TRUE;
                eModeSwitchState = MODESWITCH_NORMALTOSLEEP_STATE;
                eNormalToSleepStep = NORMALTOSLEEP_STEP1;
            }
            else
            {
                bWakeupReq = TRUE;
                eModeSwitchState = MODESWITCH_SLEEPTONORMAL_STATE;	
                eSleepToNormalStep = SLEEPTONORMAL_STEP1;
                /*to reduce wakeup time for can.*/
                Application_SleepToNormalHandle();			       
                bPowerOnReq = FALSE;
                bSleepReq = FALSE;
                bWakeupReq = FALSE;
                bResetReq = FALSE;
                switch(eModeSwitchType)
                {
                    case E_SLEEPTONORMAL:
                        eSystemState = SYSTEM_NORMAL;
                        eNormalState = NORMAL_IDLE_STATE;						
//                        CS_SIG_SyncSend((U16)SIG_SYSTEM_STATUS, (U8*)&eSystemState);	
                        /* Check wakeup reason and send corresponding events*/
                        /* 3. GPSTimeout*/
                        /* Switch to S3*/
                        SysState_SetRequest(SYSSTAT_NORMAL_STATE);					
                    break;
                    
                    case E_NORMALTOSLEEP:
                        eSystemState = SYSTEM_SLEEP;
//                        CS_SIG_SyncSend((U16)SIG_SYSTEM_STATUS, (U8*)&eSystemState);												
                        /* Switch to S1*/
                        SysState_SetRequest(SYSSTAT_SLEEP_STATE);					
                    break;
                    
                    case E_POWERTONORMAL:
                        eSystemState = SYSTEM_NORMAL;	
                        eNormalState = NORMAL_IDLE_STATE;											
//                        CS_SIG_SyncSend((U16)SIG_SYSTEM_STATUS, (U8*)&eSystemState);												
                        eNormalState = NORMAL_IDLE_STATE;
                        /* Switch to S3*/
                        SysState_SetRequest(SYSSTAT_NORMAL_STATE);
                    break;
                    
                    default:
                    break;
                }
            }
        break;
        
        case MODESWITCH_NORMALTOSLEEP_STATE:
            Application_NormalToSleepHandle();
        break;
        
        case MODESWITCH_SLEEPTONORMAL_STATE:
            Application_SleepToNormalHandle();
        break;
        
        case MODESWITCH_POWERTONORMAL_STATE:
            Application_PowerToNormalHandle();
        break;
        
        case MODESWITCH_EXITSWITCH_STATE:
            bPowerOnReq = FALSE;
            bSleepReq = FALSE;
            bWakeupReq = FALSE;
            bResetReq = FALSE;
            switch(eModeSwitchType)
            {
                case E_SLEEPTONORMAL:
                    eSystemState = SYSTEM_NORMAL;

                    eNormalState = NORMAL_IDLE_STATE;						
//                    CS_SIG_SyncSend((U16)SIG_SYSTEM_STATUS, (U8*)&eSystemState);	
                    /* Check wakeup reason and send corresponding events*/
                    /* 3. GPSTimeout*/
                    /* Switch to S3*/
                    SysState_SetRequest(SYSSTAT_NORMAL_STATE);					
                break;
                
                case E_NORMALTOSLEEP:
                    eSystemState = SYSTEM_SLEEP;
//                    CS_SIG_SyncSend((U16)SIG_SYSTEM_STATUS, (U8*)&eSystemState);												
                    /* Switch to S1*/
                    SysState_SetRequest(SYSSTAT_SLEEP_STATE);					
                break;
                
                case E_POWERTONORMAL:
                    eSystemState = SYSTEM_NORMAL;	
                    eNormalState = NORMAL_IDLE_STATE;											
//                    CS_SIG_SyncSend((U16)SIG_SYSTEM_STATUS, (U8*)&eSystemState);												
                    eNormalState = NORMAL_IDLE_STATE;
                    /* Switch to S3*/
                    SysState_SetRequest(SYSSTAT_NORMAL_STATE);
                break;
                
                default:
                break;
            }
        break;
        		
        default:
        break;
    }
}

/***********************************************************************
*  Name        : Application_SystemStateHandle
*  Description :       
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Application_SystemStateHandle(void)
{
    switch(eSystemState)
    {
        case SYSTEM_RESET:
            Application_ResetStateHandle();
        break;
        
        case SYSTEM_NORMAL:
            Application_NormalStateHandle();
        break;
        
        case SYSTEM_SLEEP:
        break;
        
        case SYSTEM_MODESWITCH:
            Application_ModeSwitchStateHandle();
        break;
        
        case SYSTEM_FCTTEST:
            /*Application_FCTStateHandle();*/
        break;
        
        default:
        break;
    }
}

/***********************************************************************
*  Name        : DisableSocPower
*  Description :       
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void DisableSocPower(void)
{
 	U8 NaviPowerStatus = FALSE;

	HAL_DevPowerControl(DEV_SOC, E_DEV_SLEEP);
// 	CS_SIG_SyncSend((U16)SIG_B_NAVI_POWER_ON, &NaviPowerStatus);
}

/***********************************************************************
*  Name        : EnableSocPower
*  Description :       
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EnableSocPower(void)
{
 	U8 NaviPowerStatus = TRUE;

       //HAL_DevPowerControl(DEV_SOC, E_DEV_POWERON);
//  	CS_SIG_SyncSend((U16)SIG_B_NAVI_POWER_ON, &NaviPowerStatus);
}

/***********************************************************************
*  Name        : Application_ResetHandle
*  Description : pass task         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void  Application_ResetHandle(void)
{    
      isWakeup = FALSE;/*power on*/
}


/***********************************************************************
*  Name        : Application_RunHandle
*  Description : pass task         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Application_RunHandle(void)
{
	SysState_ResetProc();
	OSReady();
}

/***********************************************************************
*  Name        : Application_S1Init
*  Description : pass task         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Application_S1Init(void)
{
}

/***********************************************************************
*  Name        : Application_TimerWakeupHandle
*  Description : Sleep state handler         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Application_TimerWakeupHandle(void)
{
	/*TODO: 1. Enable IO detection, switch to IO Check state*/
	/* 1. Wakeup signal detection */
       /*CS_SIG_SyncReceive((U16)SIG_ACC_DI_STATUS, (U8*)&bPhyACCOn);*/
	if(bPhyACCOn)
	{
            U8 u8Wakeup = (U8)WAKEUP_ACCON;

            bSleepAllow = FALSE;
            eWakeUpReason = WAKEUP_ACCON;		
            uWakeupReason |= ((U8)1<<(u8Wakeup-(U8)1));	
            SysMode_PreventSleep();
	}
}

/***********************************************************************
*  Name        : Application_AfterSleepHandle
*  Description : pass task         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Application_AfterSleepHandle(void)
{       
       EnableSocPower();
	bSleepAllow = FALSE;
	Application_DisableAllWakeupInt();
	CS_SIG_SyncSend((U16)SIG_WAKEUP_REASON, (U8*)&uWakeupReason);
	eSystemState = SYSTEM_MODESWITCH;
	eModeSwitchState = MODESWITCH_IDLE_STATE;		
	eSavingState = SAVING_IDLE;	
	SysState_SetRequest(SYSSTAT_MODESWITCH_STATE);  /*GOTO S2*/
}

/***********************************************************************
*  Name        : Application_DisableAllWakeupInt
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Application_DisableAllWakeupInt(void)
{
#ifdef USE_REVERSE_INTERRUPT_OPTION
	SysMode_DisableWakeupInt(INT_REVERSE_WAKEUP);
#endif
#ifdef USE_ACC_WAKEUP_OPTION
	#ifdef POWERVOLTAGEWAKEUP
	SysMode_DisableWakeupInt(INT_ACC_WAKEUP);
	SysMode_DisableWakeupInt(INT_VOL_WAKEUP);
	#else
	SysMode_DisableWakeupInt(INT_ACC_WAKEUP);
	#endif
#endif
#ifdef USE_CAN_WAKEUP_OPTION
       SysMode_DisableWakeupInt(INT_CAN_WAKEUP);
#endif
}

/***********************************************************************
*  Name        : Application_ACCOnIsr
*  Description : ACCOn Isr         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void  Application_ACCOnIsr(void)
{
    U8  u8Wakeup = (U8)WAKEUP_ACCON;
    
    eWakeUpReason = WAKEUP_ACCON;
    u8Wakeup--;
    uWakeupReason |= (((U8)1)<<u8Wakeup);

    SysMode_PreventSleep();
}

/***********************************************************************
*  Name        : Application_KeyInIsr
*  Description : ECall Isr         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void  Application_ReverseINIsr(void)
{
#ifdef USE_REVERSE_INTERRUPT_OPTION
    U8  u8Wakeup = (U8)WAKEUP_REVERSE;

    eWakeUpReason = WAKEUP_REVERSE;
    u8Wakeup--;
    uWakeupReason |= (((U8)1)<<u8Wakeup);
    SysMode_PreventSleep();
#endif
}

/***********************************************************************
*  Name        : Application_CANInhIsr
*  Description : 3G Ring Isr         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void  Application_CANInhIsr(void)
{
#ifdef USE_CAN_WAKEUP_OPTION
    U8  u8Wakeup = (U8)WAKEUP_CANIN;

    eWakeUpReason = WAKEUP_CANIN;
    u8Wakeup--;
    uWakeupReason |= (((U8)1)<<u8Wakeup);
    SysMode_PreventSleep();
    SysMode_DisableWakeupInt(INT_CAN_WAKEUP);
#endif
}


/***********************************************************************
*  Name        : OSReady
*  Description : pass task         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void OSReady(void)
{
	 /* Init all variables here*/
	isWakeup = FALSE;
	bIsSavingTimeout = FALSE;
	bSleepAllow = FALSE;
	bPowerAllow = FALSE;
	bPowerOnReq = FALSE;
	bSleepReq = FALSE;
	bWakeupReq = FALSE;
	bResetReq = FALSE;

	bPhyACCOn = FALSE;

	tSavingTimeoutTick = 0u;

	eSystemState = SYSTEM_RESET;
	
//	CS_SIG_SyncSend((U16)SIG_SYSTEM_STATUS, (U8*)&eSystemState);								
	eWakeUpReason = WAKEUP_NONE;
	uWakeupReason = 0u;
	CS_SIG_SyncSend((U16)SIG_WAKEUP_REASON, (U8*)&uWakeupReason);	
	eVoltStatus = V_INIT;
	eSavingState = SAVING_IDLE;
	eResetState = RESET_WAIT_POWER_NORMAL_STATE;
	eModeSwitchState = MODESWITCH_IDLE_STATE;
	ePowerToNormalStep = POWERTONORMAL_STEP1CHECK;
	eNormalToSleepStep = NORMALTOSLEEP_STEP1;
	eSleepToNormalStep = SLEEPTONORMAL_STEP1;
	eModeSwitchType = E_MODESWITCH_NONE;

	eNormalState = NORMAL_IDLE_STATE;	
}
/**************** END OF FILE *****************************************/


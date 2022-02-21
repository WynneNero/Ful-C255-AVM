/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD NJ      									   *
*   AUTHOR	   :            										   *
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
* Version       Date        Name                  Changes and comments
*----------------------------------------------------------------------
*  0.1  Feb 20,2017       ZhangJie               Init Version.
*=====================================================================*/

/**** System include files ****/
#include "Can_App_il.h"
#include "CanSig_Def.h"
#include "CanSig_cfg.h"
#include "can_cfg.h"
#include "can_def.h"
#include "IL_INC.H"
#include "Cansig_cfg_if.h"
#include "Hal_if.h"
#include "CanApp.h"
#include "CanNm.h"
#include "ccl.h"

#include "CanDiagDtc.h"
#include "Signal_if.h"
#include "CanManager.h"
#include "IL_INC.h"
#include "ComplexDrvier_Globaldef_IF.H"
#include "tpmc.h"
#include "Desc.h"
#include "SocManager.h"

static CAN_STATE sCanState=E_CAN_NORMAL ;
BOOL bCanBusBusoff = FALSE;

#define HOLD_SOC_DEV_POWER_TIMEOUT                  18000
#define HOLD_SOC_POWER_TIMEOUT     					6000
#define CAN_TRANSCEIVER_NORMAL_TO_SLEEP_WAIT_TIMEOUT		1000//10S T=10MS*1000
#define CAN_HOLD_TIME    		  				    49
#define DELAY_TIME_TO_DETECT_INH  1
#define GET_SOC_HOLD_TIME(x)	((x == TRUE)?HOLD_SOC_POWER_TIMEOUT_Value:HOLD_SOC_POWER_TIMEOUT)

#define ACC_WAKEUP_VALUE 0x05
#define PDU_WAKEUP_VALUE 0x02
#define IN_REPEAT_STATE 0x00
#define IN_NORMAL_STATE 0x01
#define STAYAWAKE_REASON_OF_ACC 0x10
#define STAYAWAKE_REASON_OF_ACCOFF15S 0x08
#define STAYAWAKE_REASON_OF_DIAG 0x40

/* BYTE2:Wakeup reason */
#define LOCAL_WAKEUP_REASON    0x01
#define CAN_WAKEUP_REASON      0x02

/* BYTE3:Stay awake reason */
#define LOCAL_STAY_AWAKE_REASON  0x01
#define CAN_STAY_AWAKE_REASON    0x02
#define TIMER_NOT_EXPIRED        0x04

#define DELAY_3MIN_CNT 18000 

U8 canBusOffCnt = 0;
U16 uCanTimerCnt = 0;
U16 bHoldSocPowerTimeCount=0;
U16 HOLD_SOC_POWER_TIMEOUT_Value=HOLD_SOC_DEV_POWER_TIMEOUT;
BOOL bApplicationSleepAllowSig;
U16 uCanTimeForDelaySendFirstFrame;
U8 socNotCutOffOnceFlag = 0;
U8 canHoldTimeCnt = 0;
BOOL SOC_OFF_ALLOW_Flag = FALSE;

static U8 SystemVol = 0;
static U8 SystemVol_backup;
static U8 bstopflag = FALSE;

static BOOL ReleaseNM = FALSE;
static U8  FristPowerON = TRUE;
static Nm_StateType  gubNmState;  
static Nm_ModeType   gubNmMode;
static Nm_StateType  LastNmState = NM_STATE_UNINIT;
static Nm_StateType  LastNmStateBk = NM_STATE_UNINIT;
static U8 nm_userdata[6] = {0x0,0x0,0x0,0x0,0x0,0x0};				//accodring oem define
static U8 can_nm_accstatus = 0;
static U16	Twait_McuOffCnt;
static U16	WaitNMsleeptimeout_cnt;
static U8 ReceAnyMessageFlag = FALSE;
U8 NmWakeUpSta = FALSE;

BOOL bCanDiagDeActivated;
U16 bCanDiagActivedTimeout;
#define CAN_DIAG_TIME_OUT 60*100//Haima UDS specific 60S

void ApplCanInit(void);
void CanManager_gotosleep(void);
void ApplSleep(void);
void ApplCanSetTransciverToNormal(void);
vuint8 ApplCanMsgReceived(CanRxInfoStructPtr rxStruct);
void CanMsgControlWithVoltage(void);

void CanManager_diagnose_actived(void)
{
    bCanDiagActivedTimeout = 0;
    bCanDiagDeActivated = FALSE;
}

CAN_STATE GetCanstate(void)
{
    return sCanState;
}

U32 uSeedCnt;
U32 CanDriver_GetSeed(void)
{
    return uSeedCnt;
}


void clearCalibrationDoneFlag(void)
{
	if(EED_u8SocCalibrationDoneFlag == TRUE)
	{
		EED_LockDataBlock(EED_nEOLConfig);
		EED_u8SocCalibrationDoneFlag = FALSE;
		EED_UnlockAndSavDataBlock(EED_nEOLConfig);
	}
}

void CanManager_Init(void)
{
    canBusOffCnt = 0;
    ApplCanSetTransciverToNormal(); 
    ApplCanInit();   								//former init in mcu_to_wakup_mode()。
    sCanState = E_CAN_NORMAL;
	POWER_5V0_ON();
}

void can_nm_handler(void)
{
	CclScheduleTask();														//NM Task must to be called 
	//CclPollingTask();														//NM Task must to be called 
	Nm_GetState (0 , &gubNmState, &gubNmMode );
    if(LastNmState!=gubNmState)
    {
        LastNmStateBk=LastNmState;
        LastNmState=gubNmState;
    }		
	
	switch(gubNmState)
	{
	  case NM_STATE_UNINIT:
	  	ReceAnyMessageFlag = FALSE;
		if(can_nm_accstatus == TRUE)
		  {
			nm_userdata[0] = LOCAL_WAKEUP_REASON;
			nm_userdata[1] = LOCAL_STAY_AWAKE_REASON; 
			CanNm_SetUserData(0,nm_userdata);
			CanNm_NetworkRequest(0);	
		    FristPowerON = FALSE;
		  }
		 break;
	  
	  case NM_STATE_BUS_SLEEP:  /* FAW NM Staus: NMBusSleep */ 
			NmWakeUpSta = FALSE;
	  		if(ReceAnyMessageFlag)
	  		{
				ReceAnyMessageFlag = FALSE;
				nm_userdata[0] = CAN_WAKEUP_REASON;
				CanNm_SetUserData(0,nm_userdata);
				CanNm_NetworkRequest(0);
			}
	  
			if(((V_L_ABNORMAL == SystemVol)||(V_H_ABNORMAL == SystemVol)||(V_INIT==SystemVol))&&(FristPowerON==TRUE))
			{
				if(can_nm_accstatus == FALSE)
				{
					FristPowerON = TRUE;	
				}
			}
			else 
			{
				if(can_nm_accstatus == TRUE)
				{
					nm_userdata[0] = LOCAL_WAKEUP_REASON;
					nm_userdata[1] = LOCAL_STAY_AWAKE_REASON;
					CanNm_SetUserData(0,nm_userdata);
					CanNm_NetworkRequest(0);
					FristPowerON = FALSE;
				} 
				if((LastNmStateBk==NM_STATE_PREPARE_BUS_SLEEP)&&(LastNmState==NM_STATE_BUS_SLEEP))//from PREPARE_BUS_SLEE to BUS_SLEEP
			    {
				    ReleaseNM = TRUE;	
					Twait_McuOffCnt=0;//release nm from PREPARE_BUS_SLEE to BUS_SLEEP
				    LastNmState=NM_STATE_UNINIT;
			    } 
			}
		  break;
	  case NM_STATE_REPEAT_MESSAGE:  /* FAW NM Staus: NMStart */
	  	  if((NM_STATE_PREPARE_BUS_SLEEP == LastNmStateBk)||(NM_STATE_BUS_SLEEP == LastNmStateBk))
	  	  {
	  	  	if(NmWakeUpSta == FALSE){
				NmWakeUpSta = TRUE;
				ResetTimeCntFlag = TRUE;
	  	  	}
		  }
		  
	  	  ReceAnyMessageFlag = FALSE; 
		  CanNm_NetworkRequest(0);
		  if(can_nm_accstatus == TRUE) 
		  {
		  	//local sleep condition not satisfied(e.g. IG On).
			nm_userdata[1] = LOCAL_STAY_AWAKE_REASON;
		  }
		  else
		  {
		  	//local sleep condition satisfied but TActive_Min(500ms) not expired
			nm_userdata[1] |= TIMER_NOT_EXPIRED;  
		  }
		  CanNm_SetUserData(0,nm_userdata);
		  FristPowerON = FALSE;
		  break;
	  case NM_STATE_NORMAL_OPERATION: /* FAW NM Staus: NMNormal */ 	
			if(can_nm_accstatus)
			{
				CanNm_NetworkRequest(0);
				nm_userdata[1] = LOCAL_STAY_AWAKE_REASON;			 
			}
			else
			{
				CanNm_NetworkRelease(0);
				//nm_userdata[1] &= (~LOCAL_STAY_AWAKE_REASON);		
			}
			CanNm_SetUserData(0,nm_userdata);
			FristPowerON = FALSE;
		  break;
	  case NM_STATE_READY_SLEEP:      /* FAW NM Staus: NMNormalPresleep */ 		
			if(can_nm_accstatus == TRUE)
			{
				//nm_userdata[0] = LOCAL_WAKEUP_REASON; 
				CanNm_NetworkRequest(0);
			}
			//CanNm_SetUserData(0,nm_userdata);
		   break;
	 case NM_STATE_PREPARE_BUS_SLEEP:   /* FAW NM Staus: NMWaitBusSleep */ 		
	 	  NmWakeUpSta = FALSE;
		  if(can_nm_accstatus == TRUE)
		  {
			//nm_userdata[0] = LOCAL_WAKEUP_REASON; 
			//CanNm_SetUserData(0,nm_userdata);
			CanNm_NetworkRequest(0);
		  }
		  else
		  {
			//nm_userdata[0] = 0x00;
			//CanNm_SetUserData(0,nm_userdata);				
		  }
		  break;
	  
	  default:
	  break;
	}
}


void CanManager_10ms_Entry(void)
{
	U8 can_rx_data;
	U8 bI_CANOff=FALSE;
	static U8 is_reset_cnt = 0;
	U16 calibrationDoneCntTime = 0;
	static U16  delay3minCnt;
    CS_SIG_SyncReceive(SIG_VOLTAGEFAIL_STATUS, &SystemVol);
    SystemVol = (E_SYSTEM_VOLTAGE_STATUS)SystemVol;
    CS_SIG_SyncReceive(SIG_ACCSTATUS, &can_nm_accstatus);

	if(bCanBusBusoff)
	{
		can_diag_increase_bus_off_counter(); 
	}

	switch(sCanState)
	{
		case E_CAN_IDIT:
			if((GET_INH_VALUE() == FALSE))
			{
				sCanState = E_CAN_POWERON;
				FristPowerON = TRUE;
			}
			if(can_nm_accstatus == TRUE)
			{
			    sCanState = E_CAN_POWERON;
			}
			else
			{
				if(WaitNMsleeptimeout_cnt++>400)
				{
					sCanState = E_CAN_SLEEP ;
					WaitNMsleeptimeout_cnt = 0;
				}
			}
		break;
		case E_CAN_POWERON:
			
			ApplCanInit();
			bApplicationSleepAllowSig = FALSE;
			SOC_OFF_ALLOW_Flag = FALSE;
			sCanState = E_CAN_NORMAL;

		case E_CAN_NORMAL:
			can_nm_handler();
			if(bNAckSta){
				ApplCheckStatus();
			}
 		  	if(EED_u8SocCalibrationDoneFlag == TRUE)
			{
				bApplicationSleepAllowSig = FALSE;			/*hold soc */
				delay3minCnt++;
				if(delay3minCnt > DELAY_3MIN_CNT)
				{
					EED_LockDataBlock(EED_nEOLConfig);
					EED_u8SocCalibrationDoneFlag = 0x00;
					EED_UnlockAndSavDataBlock(EED_nEOLConfig);
					delay3minCnt=0;
				}
			}
			else
			{
				if(ReleaseNM == TRUE)
				{
					 sCanState = E_CAN_SLEEP;
					 ReleaseNM = FALSE;
				}
				else if((FristPowerON==TRUE))
			    {
				    if(Twait_McuOffCnt++ >100)					//first power ON wait 1000ms to  ensure valid wakeup event
				    {		
				      Twait_McuOffCnt=0; 
					  sCanState = E_CAN_SLEEP;
				    }
			    }
			}
			break;
			
		case E_CAN_SLEEP:
			CanManager_gotosleep();
			SOC_OFF_ALLOW_Flag = TRUE;
	    	bApplicationSleepAllowSig = TRUE;
			
			if(can_nm_accstatus == TRUE)
			{
			    sCanState = E_CAN_POWERON;
			}
			else
			{
				sCanState = E_CAN_IDIT;
			}
			break;

		break;

		default:
			break;
	}
	CanMsgControlWithVoltage();

	if( uSeedCnt++>0xFFFFFFF0)
	{
		 uSeedCnt = 0x0123;
	}
}

/***********************************************************************
*  Name        : CanMsgControlWithVoltage
*  Description : control can transmission accodring the voltage
*  Called By   : CanManager_10ms_Entry
*  Parameter   : SystemVol
	  				V_L_ABNORMAL:  3.3~6.5V
	  				V_H_ABNORMAL:  18.5V~
	  				V_INIT      ： init
*  Returns     : NONE
***********************************************************************/
void CanMsgControlWithVoltage(void)
{
	if(SystemVol_backup!=SystemVol)
	{
	   if((V_L_ABNORMAL == SystemVol)||(V_H_ABNORMAL == SystemVol))
	   {
			CanOffline();
			bstopflag = TRUE;
			
	   }else{
			if(bstopflag)
			{
				CanOnline();
				bstopflag =FALSE;
			}	
	   }
		SystemVol_backup=SystemVol;
	}
}


/***********************************************************************************
*  Name 	   : ApplCanMsgReceived 
*  Description : if massages communication will enter and received diag service
*  Parameter   : 
*  Protocol    : 
*  Returns	   : 1 or 0	
***********************************************************************************/
vuint8 ApplCanMsgReceived(CanRxInfoStructPtr rxStruct)
{
    vuint16 rx_id = CanRxActualId(rxStruct);
	U8 can_nm_accstatus;
	CS_SIG_SyncReceive(SIG_ACCSTATUS,&can_nm_accstatus);
	
    if((rx_id == 0x726)||(rx_id == 0x7DF))
    {
    	CanManager_diagnose_actived();
    }

	if((rx_id >= 0x580)&&(rx_id <= 0x5FF))	
	{
		if((can_nm_accstatus == FALSE )&&((gubNmState == NM_STATE_BUS_SLEEP)||(gubNmState == NM_STATE_PREPARE_BUS_SLEEP)))			
	    {
	    	if(gubNmState == NM_STATE_BUS_SLEEP)
	    	{
				nm_userdata[0] = CAN_WAKEUP_REASON;		
				
	    	}
			nm_userdata[1] = CAN_STAY_AWAKE_REASON|TIMER_NOT_EXPIRED;	
			CanNm_SetUserData(0,nm_userdata);	
		}
	}

	if(gubNmState == NM_STATE_BUS_SLEEP)
	{
		ReceAnyMessageFlag = TRUE;
		nm_userdata[1] = CAN_STAY_AWAKE_REASON|TIMER_NOT_EXPIRED;	
		CanNm_SetUserData(0,nm_userdata);	
	}
	
    return kCanCopyData;   
}

void set_fast_powerdown(U16 timeout)
{
	HOLD_SOC_POWER_TIMEOUT_Value = timeout;//500=5S
}

BOOL GetApplicationSleepAllowSig(void)
{
	return bApplicationSleepAllowSig;
}

void ApplCanSetTransciverToNormal(void)
{
    CAN_SET_WAKE();
    delay_us(100);
    CAN_CLR_WAKE();
    CAN_SET_EN();
    CAN_SET_STB();
}

void ApplCanInit(void)
{
	U8 i = 0;
	ApplCanSetTransciverToNormal();
	CanInitPowerOn();
	IlInitPowerOn();
	TpInitPowerOn();
	CclInitPowerOn();
	CclEnableCommunication();
	DescInitPowerOn(0);

	for(i=0;i<6;i++)
	{
		nm_userdata[i] = 0x0;
	}

	CanNm_SetUserData(0,nm_userdata);
}

void ApplSleep(void)
{
	 CAN_CLR_STB();
	 CAN_SET_EN();
	 delay_us(100);
	 CAN_CLR_EN();
	 delay_us(12000);
	 POWER_5V0_OFF();
}
void ApplCheckStatus()
{
	static U8 uCanPassiveNoACKTimerCnt = 0;
	static U8 uCanPassivePauseTimerCnt = 0;
	static BOOL CanPassivePaused = FALSE;

	if((V_L_ABNORMAL == SystemVol)||(V_H_ABNORMAL == SystemVol))
		return;
	
	if(CanGetStatus()== 0x25)
	{
		uCanPassiveNoACKTimerCnt++;
		if(uCanPassiveNoACKTimerCnt >= TNoACK)
		{
			CanOffline();
		    CanInit(0);
			uCanPassiveNoACKTimerCnt = 0;
			CanPassivePaused = TRUE;
		}
	}
	else if(CanPassivePaused)
	{
		uCanPassivePauseTimerCnt++;
		if(uCanPassivePauseTimerCnt >= TPause)
		{
		   CanOnline();
		   uCanPassivePauseTimerCnt = 0;
		   uCanPassiveNoACKTimerCnt = 0;
	       CanPassivePaused = FALSE;
		}
	}
    else 
    {
	    uCanPassiveNoACKTimerCnt = 0;	
    }

}

void ApplCanTxConfirmation(CanTxInfoStructPtr ptr)
{	
	bCanBusBusoff = TRUE;
	CanManagerTxConfirmation();
}

void ApplCanTask(void)
{
    if( CanTransmit( 0 ) == kCanTxOk )
    {
    }
}

void ApplCanNMStart(void)
{

}

void ApplNmBusOff(void)
{   
    IlTxWait();
    CanInit(0);
}

void ApplNmBusOffEnd(void)
{
	IlTxRelease();
}

void ApplNmCanNormal(void)
{
}

void ApplNmBusStart(void)
{
}

void ApplNmCanSleep(void)
{
}

void ApplNmCanBusSleep(void)
{
}

void ApplNmWaitBusSleep(void)
{
}

void ApplNmWaitBusSleepCancel(void)
{
}

U16 CanNmGetBusOffWaitTime(void)
{
    return 0;
}

void CanManager_wakeup(void)
{
	ApplCanSetTransciverToNormal();
}

void CanManager_gotosleep(void)
{
    ApplCanSetTransciverToNormal();
    delay_100us();
    ApplSleep();
}

void CanManagerTxConfirmation(void)   
{
    if(bCanBusBusoff)
    {
        bCanBusBusoff = FALSE;
    }
	canBusOffCnt = 0;
    can_diag_reset_bus_off_counter();
}

/***********************************************************************
*  Name 	   : ApplCclComStart
*  Description : The can bus start( NM request will be called)
*  Parameter   : can_nm_active_status 1: Enter Normal mode from bus sleep
*  Called By   : CclComStart
*  Returns	   : None
***********************************************************************/
void ApplCclComStart(void) //From NM BusSleep to NM repeatmessage mode
{
	ReleaseNM = FALSE;
	ReceAnyMessageFlag = FALSE;
	FristPowerON = TRUE;
	Twait_McuOffCnt=0;
	can_sig_init();	
}
/***********************************************************************
*  Name 	   : ApplCclComStop
*  Description : The can bus stop( NM enter bus sleep mode will be called)
				 NOTE:first power on will called at a time 
				 From NM PrepareSleep to BusSleep mode(active before ApplCclCanStandby() function)
				 
*  Parameter   : can_nm_active_status 0: Enter bus sleep mode
*  Called By   : CclComStart
*  Returns	   : None
***********************************************************************/
void ApplCclComStop(void) 
{

}

/***********************************************************************
*  Name 	   : ApplCclBusOffEnd
*  Description : Try to recover busoff at a time will be called 	 
*  Parameter   : gubCANBusOffFlag  0: bus off had recover for once
*  Called By   : 
*  Returns	   : None
***********************************************************************/
void ApplCclBusOffEnd (void) //Busoff end indication
{
	bCanBusBusoff = FALSE;
}
/***********************************************************************
*  Name 	   : ApplCclBusOffStart
*  Description : busoff had occurred in the bus, will be called 	 
*  Parameter   : gubCANBusOffFlag  0: bus off had recover for once
*  Called By   : 
*  Returns	   : None
***********************************************************************/
void ApplCclBusOffStart (void) 
{
	bCanBusBusoff = TRUE;
}


void ApplCclInit (void)
{
	
}

void ApplCclInitTrcv  (void)  // Init Transciver to 
{

}

void ApplCclWakeUpTrcv  (void) // Set Transciver to normal mode
{

}
void ApplCclSleepTrcv  (void) // Set Transciver to Sleep mode
{

}

void ApplCclStandbyTrcv  (void) // Set Transciver to standby mode
{

}
void ApplCclComWait  (void) //From NM ReadytoSleep to PrepareSleep mode
{
}

void ApplCclComResume  (void) //From NM PrepareSleep to RepeatMessage mode
{
}
vuint8 ApplCclCanStandby (vuint8 u8number) // IN BusSleep mode ,CCL will set CAN controller to Sleep mode
{
    return 1;
}



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
* Version       Date            Name            Changes and comments
* ----------------------------------------------------------------------
*  0.1          2016/8/29   ShangQiuju      Init version
* ----------------------------------------------------------------------
*  0.2 	    2016/10/12  ShangQiuju      Add handler of Swdl status event.
* ----------------------------------------------------------------------
*  0.3 	    2016/12/26  ShangQiuju      Change OPEN_TEST include source.
* ----------------------------------------------------------------------
*  0.4 	    2017/1/3      ShangQiuju      Remove unued test code.
*----------------------------------------------------------------------
*  0.5          2017/1/6      ShangQiuju       Update CS_SIG_AsyncReceive according SIG module update.
*----------------------------------------------------------------------
*  0.6          2017/1/13    ShangQiuju       Fix recoverity warnings.
*----------------------------------------------------------------------
*  0.7          2017/2/10    ShangQiuju       Init parameters.
*----------------------------------------------------------------------
*  0.8          2017/2/13    ShangQiuju       Fix warnings.
*-----------------------------------------------------------------------
*  0.9          2017/3/7      ShangQiuju       Add Spi dual buffer communication test of eol.
*-----------------------------------------------------------------------
*  1.0          2017/3/13    ShangQiuju       Add eol spi upgrade test function.
*----------------------------------------------------------------------------------------------
*  1.1          2017/3/31    ZhangJie           Extend Uart date length.
*=====================================================================*/
#include "SocManager.h"
#include "SocCommunicator.h"
#include "TYPES.h"
#include "Signal_if.h"
#include "CanApp.h"
#include "CanManager.h"
#include "ComplexDrvier_Globaldef_IF.H"
#include "SocDriver.H"
#include "SocMsg_Cfg.h"
#include "eol_app.h"


E_SOC_STATE eSocState;

U8 uErrorTimer;
U16 uWaitNaviRespCnt;
U8 uNaviConnectedFailCnt;
U8 SendBuf[SOC_FRAME_MAXLENGTH];

//receive request
BOOL bFirstConnected;
BOOL bPowerUpOK;
BOOL bJ6RequestToReset;
U16 SentCommandid;
BOOL IsSent;
U8 uSentFailCount;
BOOL bSocConnectedStatus;
BOOL bComAllow; 
BOOL bPowerOnAllow;

SOC_CONNECTED_STATE sSocConnectedState;
BOOL watchDogIn=FALSE;
BOOL watchDogInPre=FALSE;
BOOL bSOCLostWDG=FALSE;
BOOL B_SOCCommError=FALSE;
U16 watchDogLostCnt=0;
U16 ClosePMICCnt=0;
BOOL SOC_WATCHDOG_SWITCH = TRUE;
BOOL SOC_WATCHDOG_SWITCH_Backup = TRUE;
BOOL SOC_SLEEP_SWITCH = TRUE;
BOOL eol_shultdown_cpu_watchdog=FALSE;
STATIC void DataReset(void);
void DataHandler(void);
void GotoError(void);
void Dispatcher_RepMsg(U8 cmpt_id,U16 commandid, U8* data);
void Dispatcher_SentResult(U16 commandid, BOOL result);
void Monitor_CPU_WatchDog(void);
/***********************************************************************
*  Name        : SocManager_Init
*  Description : Init driver manager        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SocManager_Init(void)
{
  eSocState=E_SOC_IDLE;
  bSocConnectedStatus = FALSE;
  CS_SIG_SyncSend(SIG_B_SOC_CONNECTED,(U8*)&bSocConnectedStatus);
  sSocConnectedState = E_SOC_CONNECTED_STARTED;
  bJ6RequestToReset = FALSE;
  SOC_WATCHDOG_SWITCH = EED_u8SocWatchdogSwitch[0];
  DataReset();
}

/***********************************************************************
*  Name        : SocManager_DeInit
*  Description : DeInit driver manager        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SocManager_DeInit(void)
{
    eSocState = E_SOC_IDLE;
}


/***********************************************************************
*  Name        : Monitor_headuint
*  Description : Get driver manager status
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Monitor_headuint(void)
{
  ///ADD SOC STATE MONITOR IF NEED TO SEND SIGNAL 
    if(sSocConnectedState !=E_SOC_CONNECTED_FINISHED)
    {
        bSocConnectedStatus = FALSE;
        CS_SIG_SyncSend(SIG_B_SOC_CONNECTED,(U8*)&bSocConnectedStatus);
    }
    else
    {
        bSocConnectedStatus = TRUE;
        CS_SIG_SyncSend(SIG_B_SOC_CONNECTED,(U8*)&bSocConnectedStatus);
    }
}

void ConnenctedHandler(void)
{
    switch(sSocConnectedState)
    {
    case E_SOC_CONNECTED_STARTED:
        sSocConnectedState = E_SOC_CONNECTED_WAIT_FIRST_CONNECT_COMPLETE_EVENT; 
        uWaitNaviRespCnt = 0;
        bFirstConnected = FALSE;
    break;
    case E_SOC_CONNECTED_WAIT_FIRST_CONNECT_COMPLETE_EVENT:
        if(uWaitNaviRespCnt++>NAVI_FIRST_CONNECT_RESP_TIME)
        {
            sSocConnectedState = E_SOC_CONNECTED_ERROR;
        }
        if(bFirstConnected)
        {
            sSocConnectedState = E_SOC_CONNECTED_SEND_POWERUP_REQ;
        }
    break;
    case E_SOC_CONNECTED_SEND_POWERUP_REQ:
        uWaitNaviRespCnt = 0;
        sSocConnectedState = E_SOC_CONNECTED_WAIT_POWERUP_RESP;
    break;
    case E_SOC_CONNECTED_WAIT_POWERUP_RESP:
        if(uWaitNaviRespCnt++>NAVI_NORMAL_RESP_TIME)
        {
            sSocConnectedState = E_SOC_CONNECTED_ERROR;
        }
        if(bPowerUpOK)
        {
            sSocConnectedState = E_SOC_CONNECTED_FINISHED;
        }        
    break;
    case E_SOC_CONNECTED_FINISHED:
        //do nothing
    break;
    case E_SOC_CONNECTED_ERROR:
        sSocConnectedState = E_SOC_CONNECTED_STARTED;	 
        uNaviConnectedFailCnt++;
        if(uNaviConnectedFailCnt>NAVI_CONNECTED_FAIL_TIMES)
        {
            uNaviConnectedFailCnt = 209;
	    sSocConnectedState = E_SOC_CONNECTED_FAILED;
        }        
    break;
    case E_SOC_CONNECTED_FAILED:
        ///TODO:OSWDG_SoftReset();
    break;
    default:break;
    }
}

/***********************************************************************
*  Name		   : SocCommConditionCheck
*  Description :		   
*  Parameter   : None
*  Returns	   : None
***********************************************************************/
void SocCommConditionCheck(void)
{

}

/***********************************************************************
*  Name		   : SocPowerOnAllowCheck
*  Description :		   
*  Parameter   : None
*  Returns	   : None
***********************************************************************/
void SocPowerOnAllowCheck(void)
{
   	U8 AccStatus;
   	U8 vol_status;
   	static U8 VolSocNormalCnt=0;
	static U8 VolSocAbnorCnt=0;
	static U8 VolSocHVolCnt=0;
   	CS_SIG_SyncReceive(SIG_ACCSTATUS, (U16 *)&AccStatus);
   	CS_SIG_SyncReceive(SIG_VOLTAGEFAIL_STATUS, (U16 *)&vol_status);   
   	if(vol_status == V_NORMAL)
   	{
		VolSocNormalCnt++;
		VolSocAbnorCnt = 0;
		VolSocHVolCnt = 0;
		 if(VolSocNormalCnt > VOL_SOC_CNT)   // uidq0888:when start up voltage will drop down, flit 500ms 
		 {
			if((FALSE==GetApplicationSleepAllowSig())&&(bSOCLostWDG == FALSE))
		 	{
				bPowerOnAllow = TRUE;
				bComAllow = TRUE; 
		 	}
		 	else
		 	{
		    	bPowerOnAllow = FALSE;
		    	bComAllow = FALSE; 
		 	}
			VolSocNormalCnt = VOL_SOC_CNT+1;
		 }
   	}
   	else if((vol_status == V_L_ABNORMAL)||(vol_status == V_LOW)||(vol_status == V_H_ABNORMAL))
   	{	
		VolSocAbnorCnt++;
		VolSocNormalCnt = 0;
		VolSocHVolCnt = 0;
		if(VolSocAbnorCnt > VOL_SOC_CNT)
		{
			bPowerOnAllow = FALSE;
			bComAllow = FALSE; 
			VolSocAbnorCnt=VOL_SOC_CNT+1;
		}
   	}
	else if(vol_status == V_HIGH)
	{
		VolSocHVolCnt++;
		VolSocAbnorCnt = 0;
		VolSocNormalCnt = 0;
		if(VolSocHVolCnt > H_VOL_SOC_CNT)
		{
			bPowerOnAllow = FALSE;
			bComAllow = FALSE; 
			VolSocHVolCnt = H_VOL_SOC_CNT + 1;
		}
	}
}


/***********************************************************************
*  Name        : NaviService_20msEntry
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SocManager_20msEntry(void)
{
	U8 SocconnectError = 0;
	Monitor_headuint();
	SocCommConditionCheck();
	SocPowerOnAllowCheck();
	CorlCameraStatus();
	switch(eSocState)
	{
		case E_SOC_IDLE:
		 if(SOC_OFF_ALLOW_Flag==TRUE)
		{
			eSocState = E_SOC_POWER_OFF;
		}
		if(bPowerOnAllow)  
		{	
				SocMsg_ControlPower(E_DEV_POWERON);
				open_pmic_pwr();
				eSocState = E_SOC_POWER_ON;
		}
		else
		{
			DataHandler();
			if(TRUE==SocMsg_GetPower(E_DEV_POWERON))
			{
				eSocState=E_SOC_DEV_POWER_OFF;
			}
		}
		break;
		case E_SOC_POWER_ON:
			if(SOC_OFF_ALLOW_Flag==TRUE)
			{
				eSocState = E_SOC_POWER_OFF;
			}
			if(bPowerOnAllow)
			{
				if(bComAllow)
				{
					SocMsg_ControlCommunication(TRUE);
					eSocState=E_SOC_READY;
				}
			}
			else
			{
				eSocState=E_SOC_DEV_POWER_OFF;
			}
		break;
		case E_SOC_READY:
			if(SOC_OFF_ALLOW_Flag==TRUE)
			{
				eSocState = E_SOC_POWER_OFF;
			}
			if(!bPowerOnAllow)
			{
				eSocState=E_SOC_DEV_POWER_OFF;
			}
			else if(!bComAllow)
			{
				eSocState=E_SOC_POWER_ON;
			}
			else
			{
			   
				ConnenctedHandler();	   
				DataHandler();					
			}			 
		break;
		case E_SOC_CONNECTED:
			if(SOC_OFF_ALLOW_Flag==TRUE)
			{
				eSocState = E_SOC_POWER_OFF;
			}
			if(!bPowerOnAllow)
			{
				eSocState=E_SOC_DEV_POWER_OFF;
			}
			else if(!bComAllow)
			{
				eSocState=E_SOC_POWER_ON;
			}
			else
			{
				DataHandler();		
				//SocconnectError = FALSE;
				//CS_SIG_SyncSend(SIG_B_NAVICOMMERROR, (U8*)&SocconnectError);
				///TODO: add condition to switch to E_SOC_ERROR_COMMUNICATOR,E_SOC_POWER_OFF
			}			
		break;
		case E_SOC_ERROR_COMMUNICATOR:
			uErrorTimer--;
			if(uErrorTimer==0)
			{
				DataReset();
				eSocState=E_SOC_POWER_ON;
			}
		break;
		case E_SOC_POWER_OFF:
			if(SOC_OFF_ALLOW_Flag==TRUE)
			{
				Close_SOC_Power_Manage();
				if(bPowerOnAllow == FALSE)
				{
					eSocState = E_SOC_DEV_POWER_OFF;
				}
			}
			else
			{
				SocDriver_S0Init();
				eSocState = E_SOC_IDLE;
			}
			break;
				
		case E_SOC_DEV_POWER_OFF:
			DataReset();
			SocMsg_ControlCommunication(FALSE);
			SocMsg_ControlPower(E_DEV_POWEROFF);
			eSocState = E_SOC_IDLE;
		break;
		default:
		break;
	}
}


/***********************************************************************
*  Name        : CorlCameraStatus
*  Description : Control Camera      
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CorlCameraStatus(void)
{
	U8 camCtrlFlag = 0;
	U8 is_camera_power_on = FALSE;
	CS_SIG_SyncReceive(SIG_2F_CAMERA_CONTROL,&camCtrlFlag);
	if((bPowerOnAllow)&&(FALSE == camCtrlFlag))
	{
		SocControlCameraPower();
		CheckCameraPower(); 
	}
	else
	{
		is_camera_power_on = FALSE;
		CS_SIG_SyncSend(SIG_CAMERA_ONOFF, &is_camera_power_on);
	}
}


BOOL SocManager_SendMsg(U8 q_type, U8 cmd_type, U16 service, U8 nArgs,U8 *pArg)
{
    if(eSocState!=E_SOC_CONNECTED)
    {
        if((service!=RADIO_DISPATCH_CHANGE_POWER_MODE)&&(service!=M3_RESPOND_J6_EOL_STATUS))return FALSE;
    }

    _memset(SendBuf,0,nArgs+10);
    SendBuf[0] = q_type;
    SendBuf[1] = cmd_type;
    SendBuf[2] = service>>8;
    SendBuf[3] = service&0xff;
    SendBuf[4]= nArgs;
    _memcpy(SendBuf+5, pArg, nArgs);
    return(SocMsg_SendMessage(SendBuf,nArgs+5));
}

//private

void DataHandler(void)
{
	U8 SocPowerStatus;
	CS_SIG_SyncReceive(SIG_B_SOC_POWER_ON, &SocPowerStatus);
	#ifdef	SOC_WATCHDOG
	if((SOC_WATCHDOG_SWITCH)&&(SocPowerStatus))
	{
		Monitor_CPU_WatchDog();
	}else{
		watchDogLostCnt= 0;
	}

	if(SOC_WATCHDOG_SWITCH_Backup !=SOC_WATCHDOG_SWITCH)
	{
		SOC_WATCHDOG_SWITCH_Backup = SOC_WATCHDOG_SWITCH;
		EED_LockDataBlock(EED_TestCfg);
		EED_u8SocWatchdogSwitch[0] = SOC_WATCHDOG_SWITCH;
	    EED_UnlockAndSavDataBlock(EED_TestCfg);
	}
	#endif

    switch(eSocState)
    { 
        case E_SOC_READY:
               if( E_SOC_CONNECTED_FINISHED == sSocConnectedState )	    eSocState=E_SOC_CONNECTED;   
        break;
        case E_SOC_CONNECTED:  
        break;
        default:break;
    }
}

void GotoError(void)
{
    uErrorTimer=NAVI_ERRORWAIT;	 
    eSocState=E_SOC_ERROR_COMMUNICATOR;	
    SocMsg_ControlCommunication(FALSE);
}

void Monitor_CPU_WatchDog(void)
{
    U16 sig;
	U16 SystemVol = 0;
    CS_SIG_SyncReceive(SIG_SOCWDG_DI_STATUS, &sig);
	CS_SIG_SyncReceive(SIG_VOLTAGEFAIL_STATUS, &SystemVol);
    watchDogInPre = watchDogIn;
    watchDogIn = sig&0x01;

    if(watchDogIn!=watchDogInPre)
    {
        watchDogLostCnt= 0;
        B_SOCCommError = FALSE;
        CS_SIG_SyncSend(SIG_B_NAVICOMMERROR,(U8*)&B_SOCCommError);

    }

	if(eEolState != E_EOL_NORMAL)
	{
		if(SystemVol == V_NORMAL)
		{
			watchDogLostCnt++;
			if(watchDogLostCnt == WATCH_DOG_TIME_OUT_WARNING)
			{
			    ClosePMICCnt=0;
				B_SOCCommError = TRUE;
				CS_SIG_SyncSend(SIG_B_NAVICOMMERROR,(U8*)&B_SOCCommError);
			}
			
		    if(watchDogLostCnt>=WATCH_DOG_TIME_OUT)
		    {  
		      // bSOCLostWDG = TRUE;
		     //  ClosePMICCnt=0;
		    //   B_SOCCommError = TRUE;
		    //   CS_SIG_SyncSend(SIG_B_NAVICOMMERROR,(U8*)&B_SOCCommError);
			 	OSWDG_SoftReset();
		    } 
		}
		/*
	    if(bSOCLostWDG)
	    {
	        ClosePMICCnt++;
	        if(ClosePMICCnt >= WATCH_DOG_TIME_OPEN_PMIC)
	        {
	            ClosePMICCnt=0;
	            bSOCLostWDG=FALSE;
	        }
	    }
	    */
	} 
}

/***********************************************************************
*  Name        : DataReset
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void DataReset(void)
{
  uErrorTimer=0;
  watchDogLostCnt = 0;
  watchDogInPre = FALSE;
  watchDogIn = FALSE;
}

/***********************************************************************
*  Name        : Dispatcher_RepMsg
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SocManager_Dispatcher_Msg(U8 cmpt_id,U16 commandid, U8* data)
{    
	U8 EOL_STATUS = 0;
	if(CMPT_ID_OOM ==cmpt_id)
    {      
        switch(commandid)
        {
            case NAVI_SHUT_DOWN_EVENT : // 0x5401
                if(NAVI_FIRST_CONNECT_COMPLETE == data[0])//03
                {
                    U8 navi_msg[2];
                    bFirstConnected = TRUE;        
                    bPowerUpOK= FALSE;
                    navi_msg[0] = TO_USER_ON;
                    navi_msg[1] = ON_OFF_NORMAL;                       
                    SocManager_SendMsg(HQ_CMD,TYPE_SERVICE,RADIO_DISPATCH_CHANGE_POWER_MODE,2,navi_msg);
                    break;
                }
                if(NAVI_POWER_UP == data[0])
                {
                    bPowerUpOK = TRUE;
                    break;
                }
            break;

            case J6_REQUEST_M3_EOL_STATUS : //5306
                if(eEolState == E_EOL_NORMAL)
                {
					EOL_STATUS = E_EOL_STATUS_ON;
				}
				else
				{
					EOL_STATUS = E_EOL_STATUS_OFF;
				}
                                      
                  SocManager_SendMsg(HQ_CMD,TYPE_RESPONSE,M3_RESPOND_J6_EOL_STATUS,1,&EOL_STATUS);//5307
             break; 

            case NAVI_REQ_TO_RESET_EVENT://0x5414
                bJ6RequestToReset = TRUE;
                ///TODO: used for upgrade test
                Timer_Start(SOFTWARE_RESET,1000,TIMER_ONE_SHOT);
//              OSWDG_SoftReset();
	     break;

            case NAVI_SWDL_CONFIG_EVENT://0x5410
            case NAVI_SWDL_STATUS_EVENT://0x5413
                Notify_Upgrade_Req(commandid,data);
            break;

            case NAVI_GET_RADIO_STATUS://0x5201
	            if(0x03 == data[0])  //EOL status
           		 {
               		J6SelfDiagFlagHandler();
            	}
			break;
	
			case NAVI_SELF_UPGRADE_RESULT_EVENT://0x5415
				EOLAPP_DISPATCHER_MSG(commandid,data);
            break;

            case J6_SEND_RESPONSE_OF_VERSION:
            break;
            
            default:
            break;
        }
    }
    else if(CMPT_ID_SYSTEM == cmpt_id)
    {
		CanApp_recvnavimsg_handler(commandid,data);
		
		CANDIA_DISPATCHER_MSG(commandid, data);
		
	   switch(commandid)
       {
			case SOC_NOTI_CAMERA_FAULT:
				{
					SOC_DISPATCHER_DTC_MSG(commandid,data);
				}
           	break;
			case SOC_SEND_RESP_OF_REMOVABLE_DEVICE_STATUS:
				{
					EOLAPP_DISPATCHER_MSG(commandid,data);
				}
            break;
			case SOC_REQ_RESEND_IMPORTANT_MESSAGE:
				if(!SOC_WATCHDOG_SWITCH)
				{
					SOC_WATCHDOG_SWITCH = TRUE;
				}
			break;
			default :
				break;
       }
    }
	/*else if(CMPT_ID_DIAG == cmpt_id)
	{
		diag_svc(commandid ,data);	
	}
	else if(CMPT_ID_ENGINEER == cmpt_id)
	{
		eng_svc(commandid, data);	
	}
    else if(CMPT_ID_SYSTEM == cmpt_id)
    {
       switch(commandid)
       {
		 case RADIO_DISPATCH_BACKLIGHT_DATA:  //0x4107		 
			 illum_target_state_receive(data);
		 break;
		 
		 default:
		 break;

 
	   }
    }*/
    else if(CMPT_ID_EOL == cmpt_id)
    {
     	EOLAPP_DISPATCHER_MSG(commandid, data);
		if(commandid == J6_NOTIFY_M3_SELFTEST_RESULT)
		{
			SocManager_SendMsg(HQ_CMD,TYPE_RESPONSE,M3_SEND_RESP_OF_J6SELFTEST,0,NULL);
		}
		else if(commandid == J6_SEND_RESPONSE_OF_VERSION)
        {
            CANDIA_DISPATCHER_MSG(commandid, data);		
        }
    }
    else if(CMPT_ID_COMMONINFO == cmpt_id)
    {
    }
}

/***********************************************************************
*  Name        : Dispatcher_SentResult
*  Description :
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Dispatcher_SentResult(U16 commandid, BOOL result)
{
    switch(commandid)
    {
        default:break;
    }
}


 void SocManager_Dispatcher_SentResult(U16 commandid, BOOL result)
{
    SentCommandid = commandid;
    IsSent = result;    
}
 
/**************** END OF FILE *****************************************/


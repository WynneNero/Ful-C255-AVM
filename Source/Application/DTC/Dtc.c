/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD NJ                                          *
*   AUTHOR     :                                                       *
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
* ----------------------------------------------------------------------
* 0.1  2014/4/11  Shang Qiuju      Initial version
* ----------------------------------------------------------------------
*=====================================================================*/

/**** System include files ****/
//#include <RTL.H>
//#include <string.h>
#include "CONFIG.H"
#include "TYPES.H"

/*---Public include files---------------------------------------------*/
#include "Signal_if.h"
#include "EEPData_IF.h"
#include "SocManager.h"
//#include "CanDataStruct.H"
#include "EEPTable.h"

/*---Private include files--------------------------------------------*/
#include "Dtc.h"
#include "CanApp.h"
#include "GPIO_IF.H"

#include "il_inc.h"
#include "il_par.h"


#define POWER_ON_CHECK_TIMES 150//20MS BASE
#define ACC_ON_CHECK_TIMES_LED_CHECK_ON    57
#define ACC_ON_CHECK_TIMES_LED_CHECK_OFF   25
#define DTC_RECOVER_TIME 5
#define DTC_SET_TIME 5
#define DTC_OPEN_RECOVER_TIME 50
#define DTC_OPEN_SET_TIME 50
#define WAIT_AVM_TIME 1  //10s

E_DTC_RECORD_STRUCT sDtcData[DTC_MAX_NUM];

ALERT_STRUCT alertData;
ALERT_STRUCT alertDataBackup;
U16 uCntForPoweroncheck;
U16 uCntForAVMpowerOn;
U16 bNaviPower;
U16 bNaviPowerBackup;
U16 uCntForHKPoweroncheck;
U16 uCntForAvmOnoffKeyErr;
U8  bCrankSta = FALSE;
U8  led_on_check_err = FALSE;
U8  led_off_check_err = FALSE;
U16 uDtcSig[DTC_MAX_NUM]=
{             
    SIG_CAMERA_F_DI_STA,             
    SIG_CAMERA_L_DI_STA,                 
    SIG_CAMERA_B_DI_STA,               
    SIG_CAMERA_R_DI_STA,  
    SIG_AVM_LED_STATUS,
//    SIG_BUZZER_FAIL,
//    SIG_LED0_STATUS,    
//    SIG_LED1_STATUS,      
    #ifdef SIG_CPU_TEMP_CHECK
    SIG_CPU_TEMP_CHECK,
    #endif
};

#ifdef DIAG_TEMPERATURE_OPTION
U8 tempDiagResult;
#endif
BOOL sbAppHeadUnitOK;
BOOL bCameraFaultFromJ6[4];
BOOL bPowerOnDtcEnd;
BOOL bAccOnSelfCheckEnd;
extern BOOL bReqReportcamerafault;
void ReportDtc(void);
void Diag_led_handler(void);
void Led_Check_handler(U8 CheckType);
void Diag_camera_handler(void);
void PowerOnSelfCheckDtcHandler(void);
void AccOnSelfCheckDtcHandler(void);
void HardkeyPowerOnSelfCheckHandle(void);
void DtcRecord_SetNaviDtc(U8 dtcnum,U8 device_type);
void DtcRecordTimeHandler(U8 dtcNum,BOOL bError,U8 device_type,U16 recovertime,U16 settime);
#ifdef DIAG_TEMPERATURE_OPTION
void TemperatureMonitor(void);
#endif

U16 uPowerDownLedOpenTime;
#define OPEN_LED_POWER_DOWN_J6  20    //400ms
extern void PowerOnSelfCheckControlPower(void);

/*===VARIABLES========================================================*/
/*---Global-----------------------------------------------------------*/
//
/* separate from dtc_status structure for EEPROM operation convenience */
/*---Private----------------------------------------------------------*/

void Dtc_Init(void)
{
    U8 i;
    bPowerOnDtcEnd = FALSE;
	bAccOnSelfCheckEnd = FALSE;
    uCntForAVMpowerOn = WAIT_AVM_TIME;
    alertData.s2NaviDtc.faultu = 0;
    alertData.s2CanDtc1.cameraf = 0;
    alertData.s2CanDtc2.ledf = 0;
    alertDataBackup.s2NaviDtc.faultu = 0;
    alertDataBackup.s2CanDtc1.cameraf = 0;
    alertDataBackup.s2CanDtc2.ledf = 0;

    for(i = 0;i<DTC_MAX_NUM;i++)
    {
        sDtcData[i].berr = FALSE;
        sDtcData[i].dtc_create_cnt = 0;
        sDtcData[i].dtc_recover_cnt = 0;
    }
    _memset(bCameraFaultFromJ6 ,TRUE,4);
    CS_SIG_SyncReceive(SIG_B_SOC_POWER_ON, &bNaviPower);
    bNaviPowerBackup = bNaviPower&0x01;    
    if(bNaviPowerBackup)
    {
        uCntForPoweroncheck = POWER_ON_CHECK_TIMES;
    }
}
void Dtc_DeInit(void)
{
    U8 out = 0;
    //CS_SIG_SyncSend(SIG_LED0PWM_DO,&out);
    //CS_SIG_SyncSend(SIG_LED1PWM_DO,&out);
    uPowerDownLedOpenTime = 0;
}

void DTC_recvnavimsg_handler(U16 commandid, U8* data)
{
    U16 camera_power;
     CS_SIG_AsyncReceive(SIG_CAMERA_DVR_DI_EN,&camera_power);
		 camera_power = camera_power&0x01;
	 if(!camera_power)
	 {  
	    return;
	 }
    if(data[0]&0x01)  //front camera
    {
        bCameraFaultFromJ6[0] = TRUE;
    }
    else
    {
        bCameraFaultFromJ6[0]  = FALSE;        
    }
    if(data[0]&0x02)  //LEFT camera
    {
        bCameraFaultFromJ6[1]  = TRUE;
    }
    else
    {
        bCameraFaultFromJ6[1]  = FALSE;        
    }
    if(data[0]&0x04)  //rear camera
    {
        bCameraFaultFromJ6[2]  = TRUE;
    }
    else
    {
        bCameraFaultFromJ6[2]  = FALSE;        
    }
    if(data[0]&0x08)  //right camera
    {
        bCameraFaultFromJ6[3]  = TRUE;
    }
    else
    {
        bCameraFaultFromJ6[3]  = FALSE;        
    }
    SocManager_SendMsg(TX_LQ,TYPE_RESPONSE, SEND_RESP_OF_SOC_NOTIFY_CAMERA_FAULT,0 , NULL);
}

void Dtc_Main(void)//20MS
{
	U8 AccStatus;
    U16 bAppHeadUnitOK = 0;
    U16 SystemVol;
    CS_SIG_SyncReceive(SIG_B_SOC_CONNECTED ,&bAppHeadUnitOK);
    sbAppHeadUnitOK = (BOOL)(bAppHeadUnitOK&0x01);
    
    CS_SIG_SyncReceive(SIG_VOLTAGEFAIL_STATUS, &SystemVol);
    SystemVol = (E_SYSTEM_VOLTAGE_STATUS)SystemVol;

    CS_SIG_SyncReceive(SIG_ACCSTATUS, (U16 *)&AccStatus);
    if(SystemVol!=V_NORMAL)
    {
        //PowerOnSelfCheckControlPower();
        return;
    }

    if(!sbAppHeadUnitOK)
    {
        _memset(bCameraFaultFromJ6 ,TRUE,4);
    }

	if(AccStatus)
	{
		PowerOnSelfCheckDtcHandler();
		Diag_camera_handler();
	}

	AccOnSelfCheckDtcHandler();
        
    ReportDtc();
#ifdef DIAG_TEMPERATURE_OPTION
    TemperatureMonitor();
#endif
}

#ifdef CAN_DIAG_OPTION
BOOL Dtc_GetCanDiagDeviceDtc(U8* dtc)
{
    if(bPowerOnDtcEnd)
    {
        U8 i;
        for(i=0;i<CANDTC_CIRCUIT_CHECK_TYPE_NUMBER;i++)
        {
            dtc[i] = alertData.canDiagDtcData[i];
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
#endif
#ifdef DIAG_TEMPERATURE_OPTION
BOOL Dtc_GetCanDiagTempDtc(U8* dtc)
{
    if(bPowerOnDtcEnd)
    {
        dtc[0] = tempDiagResult;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
#endif
#ifdef EOL_OPTION
BOOL Dtc_GetNaviDiagResult(U8* dtc)
{
    if(bPowerOnDtcEnd)
    {
        dtc[0] = alertData.s2NaviDtc.faultu>>8;
        dtc[1] = alertData.s2NaviDtc.faultu&0xff;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
#endif


void ReportDtc(void)
{
    if(!sbAppHeadUnitOK) return;
    
    if(((alertData.s2CanDtc1.cameraf!=alertDataBackup.s2CanDtc1.cameraf))
        ||((alertData.s2CanDtc2.ledf!=alertDataBackup.s2CanDtc2.ledf)))
        {    
            alertDataBackup.s2CanDtc1.cameraf = alertData.s2CanDtc1.cameraf;
            alertDataBackup.s2CanDtc2.ledf = alertData.s2CanDtc2.ledf;
            Report_DeviceDTCtoCan(alertData.s2CanDtc1.cameraf,alertData.s2CanDtc2.ledf); 
        }
    if(uCntForAVMpowerOn>0)
    {
        uCntForAVMpowerOn--;
        return;
    }
    
    if((alertData.s2NaviDtc.faultu!=alertDataBackup.s2NaviDtc.faultu)||(bReqReportcamerafault == TRUE))
    {
        alertDataBackup.s2NaviDtc.faultu = alertData.s2NaviDtc.faultu;
        Report_DeviceDTCtoCPU(alertDataBackup.s2NaviDtc.faultu);
        bReqReportcamerafault = FALSE;
    }

}

void HardkeyPowerOnSelfCheckHandle(void)
{
	U8 dAvmOnoffKeySta;
	U8 HardKey_Err;

	uCntForHKPoweroncheck++;
	//uCntForHKPoweroncheck=5;
	if(uCntForHKPoweroncheck >= POWER_ON_HK_CHECK_TIMES)
	{
		uCntForHKPoweroncheck = POWER_ON_HK_CHECK_TIMES;
		return;
	}
	else
	{
		if(uCntForAvmOnoffKeyErr>=700)//750-700=1S use to power stability
		{
			//alertData.canDiagDtcData[DTC_AVM_ONOFF_SWITCH_TROUBLE] = 1;
		}
		else
		{
			//alertData.canDiagDtcData[DTC_AVM_ONOFF_SWITCH_TROUBLE] = 0;
		}

		//CS_SIG_SyncSend(SIG_HK_DIAG_STATUS, &HardKey_Err);

	}
	dAvmOnoffKeySta = GPIO_GetVal(GPIO_PORT_8, GPIO_PIN_1);//AVM
	/*AVM HK detect*/
	if(dAvmOnoffKeySta == TRUE)
	{
		uCntForAvmOnoffKeyErr++;
	}
	else
	{
		uCntForAvmOnoffKeyErr = 0;
	}
}

void PowerOnSelfCheckControlPower(void)
{
    CS_SIG_SyncReceive(SIG_B_SOC_POWER_ON, &bNaviPower);
    bNaviPower = bNaviPower&0x01;    
    if(bNaviPower!=bNaviPowerBackup)
    {
        if(bNaviPower)  //J6 power on
        {
            uCntForPoweroncheck = POWER_ON_CHECK_TIMES;
            uPowerDownLedOpenTime = 0;
        }
        else //J6 power off
        {
            uPowerDownLedOpenTime = OPEN_LED_POWER_DOWN_J6;
            uCntForPoweroncheck = 0;
        }
    }
    bNaviPowerBackup = bNaviPower;

}

void AccOnSelfCheckDtcHandler(void)
{
	static U16 uCntForACConcheckLedOn;
	static U16 uCntForACConcheckLedOff;
	static U16 bAccStatusForSelfCheck;
	static U16 bAccStatusForSelfCheckBackup;
	static U8  bLedCheck;
	U8 PowerState;
	CS_SIG_SyncReceive(SIG_ACCSTATUS, &bAccStatusForSelfCheck);

	if(bAccStatusForSelfCheck != bAccStatusForSelfCheckBackup)
	{
		if(bAccStatusForSelfCheck)
		{
				uCntForACConcheckLedOn = ACC_ON_CHECK_TIMES_LED_CHECK_ON;
				bLedCheck = LED_ON_CHECK;
				bAccOnSelfCheckEnd = FALSE;
		}
		else
		{
			uCntForACConcheckLedOn = 0;
			uCntForACConcheckLedOff = 0;
		}
		bAccStatusForSelfCheckBackup = bAccStatusForSelfCheck;
	}

	if((!uCntForACConcheckLedOn)&&(!uCntForACConcheckLedOff))
	{
		return;
	}

	if((ACC_ON_CHECK_TIMES_LED_CHECK_ON - 4) == uCntForACConcheckLedOn)
	{
		AVM_LED_ON();	  
	}

	PowerState = can_receive_sig(PowerMode);
	if(PowerState == 8)
	{
		bCrankSta = TRUE;
		uCntForACConcheckLedOn = 0;
		AVM_LED_OFF();
		uCntForACConcheckLedOff = ACC_ON_CHECK_TIMES_LED_CHECK_OFF;
		bLedCheck = LED_OFF_CHECK;
	}	

	if(bLedCheck == LED_ON_CHECK)
	{
		uCntForACConcheckLedOn--; 
		if(0 == uCntForACConcheckLedOn)
		{
			AVM_LED_OFF();
			uCntForACConcheckLedOff = ACC_ON_CHECK_TIMES_LED_CHECK_OFF;
			bLedCheck = LED_OFF_CHECK;
		}
	}
	else if(bLedCheck == LED_OFF_CHECK)
	{
		uCntForACConcheckLedOff--;
		if(0 == uCntForACConcheckLedOff)
		{
			bLedCheck = LED_CHECK_NONE;
			bAccOnSelfCheckEnd = TRUE; 
			Diag_led_handler();
		}
	}	
	else
	{
		return;
	}

	if(uCntForACConcheckLedOn <= (ACC_ON_CHECK_TIMES_LED_CHECK_ON - 4))
	{
		Led_Check_handler(bLedCheck);
	}
	
}

void PowerOnSelfCheckDtcHandler(void)
{
    CS_SIG_SyncReceive(SIG_B_SOC_POWER_ON, &bNaviPower);
    bNaviPower = bNaviPower&0x01;    
    if(bNaviPower!=bNaviPowerBackup)
    {
        if(bNaviPower)
        {
            uCntForPoweroncheck = POWER_ON_CHECK_TIMES;
        }
    }
    bNaviPowerBackup = bNaviPower;

	//HardkeyPowerOnSelfCheckHandle();
	if(!uCntForPoweroncheck)
	 {
		 return;
	 }
    //first time open power
    if(POWER_ON_CHECK_TIMES == uCntForPoweroncheck)
    {
		//AVM_LED_ON();
    }

    uCntForPoweroncheck--;
    //last time close power        
    if(0 == uCntForPoweroncheck)
    {
		//AVM_LED_OFF();		
        bPowerOnDtcEnd = TRUE; 
        return;
    }        

	if(uCntForPoweroncheck<50)
	{
	   //Diag_led_handler();
	}
}

void Diag_led_handler(void)
{
	U8 SystemVolSta = 0;
	CS_SIG_SyncReceive(SIG_VOLTAGEFAIL_STATUS, &SystemVolSta);

	if(SystemVolSta == V_NORMAL)
	{
		if(led_on_check_err||led_off_check_err)
		{
			//alertData.canDiagDtcData[DTC_AVM_INDICAROT_LIGHT_TROUBLE] = 1;
		}
		else
		{
			//alertData.canDiagDtcData[DTC_AVM_INDICAROT_LIGHT_TROUBLE] = 0;
		}
	}
	else
	{
		led_on_check_err = FALSE;
		led_off_check_err = FALSE;
	}
}

#define 	LEDON_CRANK_SET_ERR   	14
#define 	LEDON_ACCON_SET_ERR   	40
#define 	LEDON_ACCOFF_SET_ERR  	20

void Led_Check_handler(U8 CheckType)
{
    U16 led_adc = 0;
	static U8 led_on_err_cnt;
	static U8 led_off_err_cnt;
	static U8 set_err;

    CS_SIG_AsyncReceive(uDtcSig[DTC_AVM_LED_STATUS], &led_adc);

	if(CheckType == LED_ON_CHECK)
	{
		if((led_adc < AD_LED_NORMAL_MIN)&&(led_adc > AD_LED_GND))
		{
			led_on_err_cnt = 0;
		}
		else
		{
			led_on_err_cnt++;
		}
	}
	else if(CheckType == LED_OFF_CHECK)
	{
		if((led_adc > AD_LED_NORMAL_MAX))
		{
			led_off_err_cnt = 0;
		}
		else
		{
			led_off_err_cnt++;
		}
	}

	if(bCrankSta)
	{
		set_err = LEDON_CRANK_SET_ERR;
		bCrankSta = FALSE;
	}
	else
	{
		set_err = LEDON_ACCON_SET_ERR;
	}
	
	if((led_on_err_cnt >= set_err)||(led_off_err_cnt >= LEDON_ACCOFF_SET_ERR))
	{
		led_on_check_err = TRUE;
	}
	else
	{
		led_on_check_err = FALSE;
	}
}

void Diag_camera_handler(void)
{
    U16 camera_status = 0;
    U16 camera_power = 0;
    U8 i ;

     CS_SIG_AsyncReceive(SIG_CAMERA_DVR_DI_EN,&camera_power);
		 camera_power = camera_power&0x01;
     if(!camera_power)
     {  
        return;
     }
    /* check the camera status */
    for(i=0;i<4;i++)
    {
        CS_SIG_AsyncReceive(uDtcSig[i], &camera_status);
        /*is opened status*/
		/*open status*/
		if((camera_status<AD_CAMERA_OPEN_VALUE)&&(bCameraFaultFromJ6[i]))
		{
			 DtcRecordTimeHandler(i,TRUE,DEVICE_OPEN,DTC_OPEN_RECOVER_TIME,DTC_OPEN_SET_TIME); //open
		}
		/*short status*/
		else if((camera_status>=AD_CAMERA_SHORT_BAT_MIN)&&(camera_status<AD_CAMERA_SHORT_BAT_MAX)&&(bCameraFaultFromJ6[i]))
		{
			 DtcRecordTimeHandler(i,TRUE,DEVICE_SHORT_TO_BAT,DTC_RECOVER_TIME,DTC_SET_TIME); //short to BAT
		}
		else if((camera_status>=AD_CAMERA_SHORT_GND_MIN)&&(camera_status<AD_CAMERA_SHORT_GND_MAX)&&(bCameraFaultFromJ6[i]))
		{
			 DtcRecordTimeHandler(i,TRUE,DEVICE_SHORT_TO_GND,DTC_RECOVER_TIME,DTC_SET_TIME); //short to GND
		}
		/*normal status*/
		else if((camera_status>=AD_CAMERA_NORMAL_MIN) && (camera_status<AD_CAMERA_NORMAL_MAX) && (bCameraFaultFromJ6[i]))
		{
			 DtcRecordTimeHandler(i,FALSE,DEVICE_NORMAL,DTC_RECOVER_TIME,DTC_SET_TIME); //normal
		}
    }
}

void DtcRecordTimeHandler(U8 dtcNum,BOOL bError,U8 device_type,U16 recovertime,U16 settime)
{
    if(bError)
    {
        sDtcData[dtcNum].dtc_create_cnt++;
        sDtcData[dtcNum].dtc_recover_cnt = 0;

        if(sDtcData[dtcNum].dtc_create_cnt >= recovertime)
        {            
            sDtcData[dtcNum].dtc_create_cnt = 0;
            sDtcData[dtcNum].berr = TRUE;
            DtcRecord_SetNaviDtc(dtcNum,device_type);
        }
    }
    else
    {
        sDtcData[dtcNum].dtc_create_cnt = 0;
        sDtcData[dtcNum].dtc_recover_cnt ++;

        if(sDtcData[dtcNum].dtc_recover_cnt >= settime)
        {            
            sDtcData[dtcNum].dtc_recover_cnt= 0;
            sDtcData[dtcNum].berr = FALSE;
            DtcRecord_SetNaviDtc(dtcNum,device_type);
        }
    }
}

void DtcRecord_SetNaviDtc(U8 dtcnum,U8 device_type)
{
    switch(dtcnum)
    {
        case DTC_FRONT_CAMERA:          
                if(DEVICE_NORMAL == device_type)
                {
                    #ifdef CAN_DIAG_OPTION
					alertData.canDiagDtcData[DTC_FRONT_CAMERA_OPEN_CIRCUIT] = 0;
                    alertData.canDiagDtcData[DTC_FRONT_CAMERA_SHORT_GND] = 0;
					alertData.canDiagDtcData[DTC_FRONT_CAMERA_SHORT_BAT] = 0;
                    #endif
                    alertData.s2CanDtc1.camerab.front = 0;
                }
                else
                {
                    #ifdef CAN_DIAG_OPTION
                    if(DEVICE_OPEN== device_type)
                    {
                        alertData.canDiagDtcData[DTC_FRONT_CAMERA_OPEN_CIRCUIT] = 1;
                        alertData.canDiagDtcData[DTC_FRONT_CAMERA_SHORT_GND] = 0;
						alertData.canDiagDtcData[DTC_FRONT_CAMERA_SHORT_BAT] = 0;
                    }
                    else if(DEVICE_SHORT_TO_BAT == device_type)
					{
						alertData.canDiagDtcData[DTC_FRONT_CAMERA_OPEN_CIRCUIT] = 0;
                        alertData.canDiagDtcData[DTC_FRONT_CAMERA_SHORT_GND] = 0;
						alertData.canDiagDtcData[DTC_FRONT_CAMERA_SHORT_BAT] = 1;	
					}
					else if(DEVICE_SHORT_TO_GND == device_type)
                    {
                        alertData.canDiagDtcData[DTC_FRONT_CAMERA_OPEN_CIRCUIT] = 0;
                        alertData.canDiagDtcData[DTC_FRONT_CAMERA_SHORT_GND] = 1;
						alertData.canDiagDtcData[DTC_FRONT_CAMERA_SHORT_BAT] = 0;
                    }

                    #endif
                    alertData.s2CanDtc1.camerab.front = 1;
                }
                alertData.s2NaviDtc.faultb.front = device_type;      
        break;
        case DTC_LEFT_CAMERA:
                if(DEVICE_NORMAL == device_type)
                {
                    #ifdef CAN_DIAG_OPTION
                    alertData.canDiagDtcData[DTC_LEFT_CAMERA_OPEN_CIRCUIT] = 0;
                    alertData.canDiagDtcData[DTC_LEFT_CAMERA_SHORT_GND] = 0;
					alertData.canDiagDtcData[DTC_LEFT_CAMERA_SHORT_BAT] = 0;
                    #endif
                    alertData.s2CanDtc1.camerab.left = 0;
                }
                else
                {    
                    #ifdef CAN_DIAG_OPTION
                    if(DEVICE_OPEN == device_type)
                    {
                        alertData.canDiagDtcData[DTC_LEFT_CAMERA_OPEN_CIRCUIT] = 1;
                        alertData.canDiagDtcData[DTC_LEFT_CAMERA_SHORT_GND] = 0;
						alertData.canDiagDtcData[DTC_LEFT_CAMERA_SHORT_BAT] = 0;
                    }
                    else if(DEVICE_SHORT_TO_BAT == device_type)
					{
						alertData.canDiagDtcData[DTC_LEFT_CAMERA_OPEN_CIRCUIT] = 0;
                        alertData.canDiagDtcData[DTC_LEFT_CAMERA_SHORT_GND] = 0;
						alertData.canDiagDtcData[DTC_LEFT_CAMERA_SHORT_BAT] = 1;	
					}
					else if(DEVICE_SHORT_TO_GND == device_type)
                    {
                        alertData.canDiagDtcData[DTC_LEFT_CAMERA_OPEN_CIRCUIT] = 0;
                        alertData.canDiagDtcData[DTC_LEFT_CAMERA_SHORT_GND] = 1;
						alertData.canDiagDtcData[DTC_LEFT_CAMERA_SHORT_BAT] = 0;
                    }

                    #endif
                    alertData.s2CanDtc1.camerab.left = 1;
                }
                alertData.s2NaviDtc.faultb.left = device_type;     
        break;
        case DTC_REAR_CAMERA:
                if(DEVICE_NORMAL == device_type)
                {    
                #ifdef CAN_DIAG_OPTION
					alertData.canDiagDtcData[DTC_BACK_CAMERA_OPEN_CIRCUIT] = 0;
					alertData.canDiagDtcData[DTC_BACK_CAMERA_SHORT_GND] = 0;
					alertData.canDiagDtcData[DTC_BACK_CAMERA_SHORT_BAT] = 0;
                #endif
                    alertData.s2CanDtc1.camerab.rear = 0;
                }
                else
                {
                    #ifdef CAN_DIAG_OPTION
                    if(DEVICE_OPEN== device_type)
                    {
                        alertData.canDiagDtcData[DTC_BACK_CAMERA_OPEN_CIRCUIT] = 1;
                        alertData.canDiagDtcData[DTC_BACK_CAMERA_SHORT_GND] = 0;
						alertData.canDiagDtcData[DTC_BACK_CAMERA_SHORT_BAT] = 0;
                    }
                    else if(DEVICE_SHORT_TO_BAT == device_type)
					{
						alertData.canDiagDtcData[DTC_BACK_CAMERA_OPEN_CIRCUIT] = 0;
                        alertData.canDiagDtcData[DTC_BACK_CAMERA_SHORT_GND] = 0;
						alertData.canDiagDtcData[DTC_BACK_CAMERA_SHORT_BAT] = 1;	
					}
					else if(DEVICE_SHORT_TO_GND == device_type)
                    {
                        alertData.canDiagDtcData[DTC_BACK_CAMERA_OPEN_CIRCUIT] = 0;
                        alertData.canDiagDtcData[DTC_BACK_CAMERA_SHORT_GND] = 1;
						alertData.canDiagDtcData[DTC_LEFT_CAMERA_SHORT_BAT] = 0;
                    }

                    #endif
                    alertData.s2CanDtc1.camerab.rear = 1;
                }
                alertData.s2NaviDtc.faultb.rear = device_type;   
        break;
        case DTC_RIGHT_CAMERA:
                if(DEVICE_NORMAL == device_type)
                {    
                #ifdef CAN_DIAG_OPTION
					alertData.canDiagDtcData[DTC_RIGHT_CAMERA_OPEN_CIRCUIT] = 0;
					alertData.canDiagDtcData[DTC_RIGHT_CAMERA_SHORT_GND] = 0;
					alertData.canDiagDtcData[DTC_RIGHT_CAMERA_SHORT_BAT] = 0;
                #endif
                    alertData.s2CanDtc1.camerab.right = 0;
                }
                else
                {
                #ifdef CAN_DIAG_OPTION
					if(DEVICE_OPEN== device_type)
					{
						alertData.canDiagDtcData[DTC_RIGHT_CAMERA_OPEN_CIRCUIT] = 1;
						alertData.canDiagDtcData[DTC_RIGHT_CAMERA_SHORT_GND] = 0;
						alertData.canDiagDtcData[DTC_RIGHT_CAMERA_SHORT_BAT] = 0;
					}
					else if(DEVICE_SHORT_TO_BAT == device_type)
					{
						alertData.canDiagDtcData[DTC_RIGHT_CAMERA_OPEN_CIRCUIT] = 0;
						alertData.canDiagDtcData[DTC_RIGHT_CAMERA_SHORT_GND] = 0;
						alertData.canDiagDtcData[DTC_RIGHT_CAMERA_SHORT_BAT] = 1;	
					}
					else if(DEVICE_SHORT_TO_GND == device_type)
					{
						alertData.canDiagDtcData[DTC_RIGHT_CAMERA_OPEN_CIRCUIT] = 0;
						alertData.canDiagDtcData[DTC_RIGHT_CAMERA_SHORT_GND] = 1;
						alertData.canDiagDtcData[DTC_RIGHT_CAMERA_SHORT_BAT] = 0;
					}
                #endif
                    alertData.s2CanDtc1.camerab.right = 1;
                }
                alertData.s2NaviDtc.faultb.right = device_type;     
        break;	
        #ifdef DIAG_TEMPERATURE_OPTION
        case DTC_TEMP:
                tempDiagResult = device_type;
        break;
        #endif
        default:break;
    }
}

#ifdef DIAG_TEMPERATURE_OPTION
void TemperatureMonitor(void)
{    
    U16 addata;
    
        CS_SIG_AsyncReceive(uDtcSig[DTC_TEMP], &addata);
        /*is opened status*/
        if(addata>TEMP_NAV_TOO_COLD)
        {
             DtcRecordTimeHandler(DTC_TEMP,TRUE,TEMP_TOO_LOW,TEMP_RECOVERY_TIME,TEMP_CONFIRM_TIME); //open
        }
        /*is shorted status*/
        else if(addata<TEMP_NAV_TOO_HOT)
        {
             DtcRecordTimeHandler(DTC_TEMP,TRUE,TEMP_TOO_HOT,TEMP_RECOVERY_TIME,TEMP_CONFIRM_TIME); //short
        }
        else
        {
             DtcRecordTimeHandler(DTC_TEMP,FALSE,TEMP_NORMAL,TEMP_RECOVERY_TIME,TEMP_CONFIRM_TIME); //normal
        }
}
#endif
/**************** END OF FILE *****************************************/


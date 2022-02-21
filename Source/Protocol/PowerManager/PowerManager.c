/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									           *
*   AUTHOR	   : 									                   *
************************************************************************
* Object        :PowerManager.c
* Module        :PowerManager
* Instance      :
* Description   :Control the power
*-----------------------------------------------------------------------
* Version: 	0.6
* Date:		2017/8/18
* Author:	Zheng Xiaolei
***********************************************************************/
/*-History--------------------------------------------------------------
* Version	Date		 Name 			 Changes and comments
* 0.1		2017/6/29    Zheng Xiaolei	 Init version
* 0.2       2017/7/4     Zheng Xiaolei   Bug fix for state changed to emergency power
* 0.3       2017/7/29    Zheng Xiaolei   Change the TFT on&off control mode from EN to PWM.
* 0.4       2017/7/30    Zheng Xiaolei   Add RTC Config after power on.
* 0.5       2017/8/17    Zheng Xiaolei   Change the location of variable init when power up.
* 0.6       2017/8/18    Zheng Xiaolei   Add SOC watchdog handler.
*=====================================================================*/

#include "ComplexDrvier_Globaldef_IF.H"
#include "Sig_Combine.H"
#include "Signal_IF.H"
#include "PowerManager.h"
#include "PowerManager_IF.H"

#include "SocDriver.h"



BOOL bAccOnStatus;
U8 NaviPowerStatus;
BOOL bsysPowerOk = FALSE;
BOOL bsysCanPowerOk = FALSE; 
U8 uAccOnCnt = 0;
U8 uAccOffCnt = 0;
U8 VolDetCnt = 0;
extern BOOL bEol_Control_Accon;

/***********************************************************************
*  Name        : PowerManager_Init_S0
*  Description : 
*  Parameter   :
*  Returns     : 
***********************************************************************/
void PowerManager_Init_S0(void)
{
}

/***********************************************************************
*  Name        : PowerManager_Init_S3
*  Description : 
*  Parameter   :
*  Returns     : 
***********************************************************************/
void PowerManager_Init_S3(void)
{
	GPIO_SetInputMode(GPIO_PORT_8, GPIO_PIN_0, E_NO_MODE); // acc 
	//GPIO_SetInputMode(GPIO_PORT_10, GPIO_PIN_5,  E_NO_MODE, TRUE);
	//PowerManager_PowerSwitchOn();
}

/***********************************************************************
*  Name        : PowerManager_DeInit
*  Description : 
*  Parameter   :
*  Returns     : 
***********************************************************************/
void PowerManager_DeInit(void)
{
}

/***********************************************************************
*  Name        : PowerManager_5msEntry
*  Description : 
*  Parameter   :
*  Returns     : 
***********************************************************************/
U8 LLF_MARK = 0;

void PowerManager_5msEntry(void)
{
    //HandleNaviPower(SPowervoltageFail);    
    //HandleCPU_powerlowstatus();
    
	E_SYSTEM_VOLTAGE_STATUS vol_status = GetPowerVoltageStatus();
	//update direct voltage  status
   	CS_SIG_SyncSend(SIG_VOLTAGEFAIL_STATUS, (U8*) &vol_status);
	UpdateACCStatus();
}

/******** power detection condition ************
pin name		
state:                  VOLTAGE_ABNORMAL       VOLTAGE_LOWER        VOLTAGE_NORMAL
PWR_VALUSE	                   <6/>16	                       6-9v	                      9-16	
PS2up_PWR_DET_VALUE	6V=0X302,16V=0x832	9V=0x46B            
******************************************/
#define V_0V5_VALUE		 60		// 0.5V
#define V_6V_VALUE       1104   // 6V		
#define V_6V5_VALUE      1168   // 6.5V		
#define V_8V5_MIN_VALUE  1454   // 8.3V	  Load	
#define V_8V5_MAX_VALUE	 1605	// 8.8V   NotLoad
//#define V_9V5_VALUE   	1700	// 9.5V  
#define V_16V_MIN_VALUE	 2965   // 16.15  NotLoad	
#define V_16V_MAX_VALUE  3016   // 16.40  NotLoad
#define V_18V_VALUE   	 3332	// 18		
#define V_18V5_VALUE   	 3424	// 18.5		
#define PW_Vol_CNT   	 7


U8 pwVoltageStatus_backup = V_INIT;
U8 pwVoltageStatus_pre = V_INIT;
U8 pwVoltageStatus_Cnt = 0;

#ifdef POWER_AD_DETECT_CALIBRATION
U16 ad_detect_calibration_val;
#endif //POWER_AD_DETECT_CALIBRATION
E_SYSTEM_VOLTAGE_STATUS pwVoltageStatus = V_INIT;
E_SYSTEM_VOLTAGE_STATUS GetPowerVoltageStatus(void)
{

    U16 pwrValue = 0;
	CS_SIG_AsyncReceive(SIG_APP_PWR,&pwrValue);
	if((pwrValue > 4096)||(pwrValue==0))
	{
		return;
	}

#ifdef POWER_AD_DETECT_CALIBRATION
	ad_detect_calibration_val = pwrValue;
#endif //POWER_AD_DETECT_CALIBRATION

	if(V_INIT==pwVoltageStatus)
	{
		if(pwrValue<V_6V5_VALUE)
		{
			pwVoltageStatus = V_L_ABNORMAL;
		}
		else if((pwrValue>=V_6V5_VALUE)&&(pwrValue<V_8V5_MIN_VALUE))
		{
			pwVoltageStatus = V_LOW;
		}
		else if((pwrValue>=V_8V5_MAX_VALUE)&&(pwrValue<=V_16V_MAX_VALUE))
		{
			pwVoltageStatus = V_NORMAL;
		}
		else if((pwrValue>V_16V_MAX_VALUE)&&(pwrValue<=V_18V5_VALUE))
		{
			pwVoltageStatus = V_HIGH;
		}
		else if(pwrValue>V_18V5_VALUE)
		{
			pwVoltageStatus = V_H_ABNORMAL;
		}
	}
	else if(V_L_ABNORMAL==pwVoltageStatus)
	{
		if((pwrValue>=V_6V_VALUE)&&(pwrValue<V_8V5_MIN_VALUE))
		{
			pwVoltageStatus = V_LOW;
		}
		else if((pwrValue>=V_8V5_MAX_VALUE)&&(pwrValue<=V_16V_MAX_VALUE))
		{
			pwVoltageStatus = V_NORMAL;
		}
		else if((pwrValue>V_16V_MAX_VALUE)&&(pwrValue<=V_18V5_VALUE))
		{
			pwVoltageStatus = V_HIGH;
		}
		else if(pwrValue>V_18V5_VALUE)
		{
			pwVoltageStatus = V_H_ABNORMAL;
		}
	}
	else if(V_H_ABNORMAL==pwVoltageStatus)
	{
		if((pwrValue>V_16V_MIN_VALUE)&&(pwrValue<=V_18V_VALUE))
		{
			pwVoltageStatus = V_HIGH;
		}
		else if((pwrValue>=V_8V5_MAX_VALUE)&&(pwrValue<=V_16V_MIN_VALUE))
		{
			pwVoltageStatus = V_NORMAL;
		}
		else if((pwrValue>=V_6V5_VALUE)&&(pwrValue<V_8V5_MIN_VALUE))
		{
			pwVoltageStatus = V_LOW;
		}
		else if(pwrValue<V_6V5_VALUE)
		{
			pwVoltageStatus = V_L_ABNORMAL;
		}
	}
	else if(V_LOW==pwVoltageStatus)
	{
	    if(pwrValue<V_6V5_VALUE)
		{
			pwVoltageStatus = V_L_ABNORMAL;
		}
		else if((pwrValue>=V_8V5_MAX_VALUE)&&(pwrValue<=V_16V_MAX_VALUE))
		{
			pwVoltageStatus = V_NORMAL;
		}
		else if((pwrValue>V_16V_MAX_VALUE)&&(pwrValue<=V_18V5_VALUE))
		{
			pwVoltageStatus = V_HIGH;
		}
		else if(pwrValue>V_18V5_VALUE)
		{
			pwVoltageStatus = V_H_ABNORMAL;
		}
	}
	else if(V_NORMAL==pwVoltageStatus)
	{
		if((pwrValue>=V_6V_VALUE)&&(pwrValue<V_8V5_MIN_VALUE))
		{
			pwVoltageStatus = V_LOW;
		}
		else if(pwrValue<V_6V5_VALUE)
		{
			pwVoltageStatus = V_L_ABNORMAL;
		}
		else if((pwrValue>V_16V_MAX_VALUE)&&(pwrValue<=V_18V5_VALUE))
		{
			pwVoltageStatus = V_HIGH;
		}
		else if(pwrValue>V_18V5_VALUE)
		{
			pwVoltageStatus = V_H_ABNORMAL;
		}
	}
	else if(V_HIGH==pwVoltageStatus)
	{
		if((pwrValue>=V_8V5_MIN_VALUE)&&(pwrValue<=V_16V_MIN_VALUE))
		{
			pwVoltageStatus = V_NORMAL;
		}
		else if((pwrValue>=V_6V5_VALUE)&&(pwrValue<V_8V5_MIN_VALUE))
		{
			pwVoltageStatus = V_LOW;
		}
		else if(pwrValue<V_6V5_VALUE)
		{
			pwVoltageStatus = V_L_ABNORMAL;
		}
		else if(pwrValue>V_18V5_VALUE)
		{
			pwVoltageStatus = V_H_ABNORMAL;
		}
	}

	return  pwVoltageStatus;
#ifdef POWER_AD_DETECT_CALIBRATION   
	pwVoltageStatus=V_NORMAL;
#endif //POWER_AD_DETECT_CALIBRATION

/*
	if(pwVoltageStatus_backup == pwVoltageStatus)  // LLF MASK
	{
		pwVoltageStatus_Cnt++;
		if(pwVoltageStatus_Cnt > PW_Vol_CNT)
		{
			pwVoltageStatus_Cnt = PW_Vol_CNT+1;
			pwVoltageStatus_pre = pwVoltageStatus;
			return  pwVoltageStatus_pre;
		}
		else
		{
			return  pwVoltageStatus_pre;
		}
	}
	else
	{
		pwVoltageStatus_Cnt = 0;
		pwVoltageStatus_backup = pwVoltageStatus;
		return  pwVoltageStatus_pre;
		
	}
*/
}


U8 hw_acc_value=0;
BOOL hw_accon_flag=FALSE;
BOOL accon_flag=FALSE;
BOOL accon_flag_backup=FALSE;
BOOL hwaccon_flag=FALSE;
BOOL hwaccon_flag_backup=FALSE;
void UpdateACCStatus(void)
{
	BOOL acc_status_from_can=0;
	BOOL hw_acc_status=0;
	hw_acc_status = get_hw_ACC_status();
	acc_status_from_can = get_can_ACC_status();
	if(hw_acc_status|acc_status_from_can)
	{
		accon_flag = TRUE;
	}
	else
	{
		accon_flag = FALSE;
	}
	if(accon_flag_backup!=accon_flag)
	{
		accon_flag_backup = accon_flag;
	}

	if(bEol_Control_Accon == FALSE)
	{
		CS_SIG_SyncSend(SIG_ACCSTATUS, &accon_flag);
	}	
}


U8 get_hw_ACC_status(void)
{
	GPIO_SetInputMode( GPIO_PORT_8, GPIO_PIN_0,GPIO_OPT_INIT);
	hw_acc_value = GPIO_GetVal(GPIO_PORT_8, GPIO_PIN_0); //acc pin
	if((hw_acc_value&0x01) == 1) //acc on
	{
		uAccOnCnt++;
		uAccOffCnt = 0;
		if(uAccOnCnt>=ACC_MASK_ON_TIMES_DEBOUNCE)
		{
		    uAccOnCnt = ACC_MASK_ON_TIMES_DEBOUNCE;
		    hw_accon_flag = 1;
		}
	}
	else //acc off
	{
		uAccOnCnt=0;
		uAccOffCnt ++;
		if(uAccOffCnt>=ACC_MASK_OFF_TIMES_DEBOUNCE)
		{
		    uAccOffCnt = ACC_MASK_OFF_TIMES_DEBOUNCE;
		    hw_accon_flag = 0;   
		}
	}
	return hw_accon_flag;
}


U8 get_can_ACC_status(void)
{
	U8 accstatusfromcantemp = 0;
	CS_SIG_SyncReceive(SIG_ACC_CAN_IN_STATUS,&accstatusfromcantemp);
	return accstatusfromcantemp;
}

/******** TAUB0I11_timer_callback ************
*  Name        : TAUB0I11_timer_callback
*  Description :
*  Parameter   : None
*  Returns     : None
*****************************************************************************/
void TAUB0I11_timer_callback(U64 data)
{
//	SocWdgCapData = data;
}


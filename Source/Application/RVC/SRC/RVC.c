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
*
*=====================================================================*/
#include "config.h"
#include "Define.h"
#include "Sig_Combine.H"
#include "Signal_IF.H"
#include "RVC.h"
#include "RVC_IF.h"
#include "GPIO_if.h"

//U8 RvcStatusCnt;
U8 TunerStatusCnt;

/***********************************************************************
*  Name        : RvcTuner_PowerControl_5msEntry
*  Description : 
*  Parameter   :
*  Returns     : 
***********************************************************************/
void RvcTuner_PowerControl_5msEntry(void)
{
	RvcManager_5msEntry();
	TunerManager_5msEntry();
}

/***********************************************************************
*  Name        : RvcManager_5msEntry
*  Description : 
*  Parameter   :
*  Returns     : 
***********************************************************************/
void RvcManager_5msEntry(void)
{
	U8 bRvcSocEN=0;
	U8 sReverse=0;
	E_RVC_STATUS rvc_status = GetRvcVoltageStatus();
	sReverse = GPIO_GetVal(GPIO_PORT_11, GPIO_PIN_3);
	if(sReverse == 0)
	{
		bRvcSocEN=1;
		sReverse=1;
//		CS_SIG_AsyncSend(SIG_RVCSOCEN_DI_STATU, &bRvcSocEN);
	}
	else
	{
		bRvcSocEN=0;		
		sReverse=0;
//		CS_SIG_AsyncSend(SIG_RVCSOCEN_DI_STATU, &bRvcSocEN);
	}
	if((rvc_status == RVC_NORMAL)||(rvc_status == RVC_OPEN))
	{
//		Power_RVC_ON();
	}
	else if((rvc_status == RVC_OVERCURRENT)||(rvc_status == RVC_SHORTCIRCUIT)||(rvc_status == RVC_ABNORMAL))
	{
//		Power_RVC_OFF();
	}	
//	CS_SIG_SyncSend(SIG_RVC_REVERSE_STATUS,&sReverse);
}

/***********************************************************************
*  Name        : TunerManager_5msEntry
*  Description : 
*  Parameter   :
*  Returns     : 
***********************************************************************/
void TunerManager_5msEntry(void)
{
	E_TUNER_STATUS tuner_status = GetTunerVoltageStatus();
	if((tuner_status == TUNER_NORMAL)||(tuner_status == TUNER_OPEN))
	{
//		Power_TunerMast_ON();
	}
	else if((tuner_status == TUNER_OVERCURRENT)||(tuner_status == TUNER_SHORTCIRCUIT)||(tuner_status == TUNER_ABNORMAL))
	{
//		Power_TunerMast_OFF();
	}	
}

/***********************************************************************
*  Name        : GetRVCVoltageStatus
*  Description : 
*  Parameter   :
*  Returns     : 
***********************************************************************/
E_RVC_STATUS GetRvcVoltageStatus(void)
{
//    U16 rvcValue=0;
//	static E_RVC_STATUS rvcVoltageStatus = RVC_UNKNOWN;
//	RvcStatusCnt++;
//	CS_SIG_AsyncReceive(SIG_RVCDET_AD_STATU,&rvcValue);
//    if(rvcValue < VOL_INVALID_VALUE)
//    {		
//        if(RvcStatusCnt>=5)
//        {
//         	RvcStatusCnt=0;
//            rvcVoltageStatus=RVC_OPEN;
//        }
//    }
//    else if((rvcValue>=VOL_NORMAL_LOW_VALUE)&&(rvcValue <VOL_NORMAL_HIGH_VALUE))
//    {
//        if(RvcStatusCnt>=5)
//        {
//         	RvcStatusCnt=0;
//            rvcVoltageStatus=RVC_NORMAL;
//        }
//    }
//    else if(( rvcValue >=VOL_NORMAL_HIGH_VALUE) &&(rvcValue <VOL_OVER_CURRENT_VALUE))
//    {
//        if(RvcStatusCnt>=5)
//        {
//         	RvcStatusCnt=0;
//            rvcVoltageStatus=RVC_OVERCURRENT;
//        }
//    }
//    else if(( rvcValue >= VOL_OVER_CURRENT_VALUE) && (rvcValue < VOL_SHORT_CIRCUIT_VALUE))
//    {
//        if(RvcStatusCnt>=5)
//        {
//         	RvcStatusCnt=0;
//            rvcVoltageStatus=RVC_SHORTCIRCUIT;
//        }
//    }	
//    else if(( rvcValue >= VOL_SHORT_CIRCUIT_VALUE) && (rvcValue < VOL_CURRENT_REVERSE_VALUE))
//    {
//        if(RvcStatusCnt>=5)
//        {
//         	RvcStatusCnt=0;
//            rvcVoltageStatus=RVC_ABNORMAL;
//        }
//    }	
//    else
//    {
//        rvcVoltageStatus=RVC_UNKNOWN;     
//   	}
   
//	return  rvcVoltageStatus;
}

/***********************************************************************
*  Name        : GetTunerVoltageStatus
*  Description : 
*  Parameter   :
*  Returns     : 
***********************************************************************/
E_TUNER_STATUS GetTunerVoltageStatus(void)
{
    U16 tunerValue=0;
	static E_TUNER_STATUS tunerVoltageStatus = TUNER_UNKNOWN;
//	CS_SIG_AsyncReceive(SIG_TUNERDET_AD_STATU,&tunerValue);
    if(tunerValue < VOL_INVALID_VALUE)
    {		
        if(TunerStatusCnt>=5)
        {
         	TunerStatusCnt=0;
            tunerVoltageStatus=TUNER_OPEN;
        }
    }
    else if((tunerValue>=VOL_NORMAL_LOW_VALUE)&&(tunerValue <VOL_NORMAL_HIGH_VALUE))
    {
        if(TunerStatusCnt>=5)
        {
         	TunerStatusCnt=0;
            tunerVoltageStatus=TUNER_NORMAL;
        }
    }
    else if((tunerValue >=VOL_NORMAL_HIGH_VALUE) &&(tunerValue <VOL_OVER_CURRENT_VALUE))
    {
        if(TunerStatusCnt>=5)
        {
         	TunerStatusCnt=0;
            tunerVoltageStatus=TUNER_OVERCURRENT;
        }
    }
    else if((tunerValue >= VOL_OVER_CURRENT_VALUE) && (tunerValue < VOL_SHORT_CIRCUIT_VALUE))
    {
        if(TunerStatusCnt>=5)
        {
         	TunerStatusCnt=0;
            tunerVoltageStatus=TUNER_SHORTCIRCUIT;
        }
    }	
    else if((tunerValue >= VOL_SHORT_CIRCUIT_VALUE) && (tunerValue < VOL_CURRENT_REVERSE_VALUE))
    {
        if(TunerStatusCnt>=5)
        {
         	TunerStatusCnt=0;
            tunerVoltageStatus=TUNER_ABNORMAL;
        }
    }	
    else
    {
        tunerVoltageStatus=TUNER_UNKNOWN;     
   	}
   
	return  tunerVoltageStatus;
}



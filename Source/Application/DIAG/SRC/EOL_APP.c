/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD NJ     									   *
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
* Version       Date           Name            Changes and comments
* 0.1    	2015-12-15	ShangQiuju		Initial
*=====================================================================*/
/**** System include files ****/

#include "config.h"
#ifdef EOL_OPTION
#include "TYPES.H"
#include "TOOLS.H"
#include "eol_app.h"
#include "eol_app_if.h"
#include "eoluartdriver_if.h"
//#include "StringParser.h"
//#include "NaviService.h"
#include "SocManager.h"
//#include "dtc.h"
#include "EEP_DtcData.h"
#include "CanDiagDtc.h"
#include "CanDiagDtcCfg.h"
//#include "CanDataStruct.H"
#include "Signal_if.h"  
#include "naviapp.h"
#include "EEP_ECUSerialNumber.h"
#include "EEP_EOLconfig.h"
#include "SocDriver_IF.H"
#include "ComplexDrvier_Globaldef_IF.h"


/*---Public include files---------------------------------------------*/

/*===VARIABLES========================================================*/

/*---Global-----------------------------------------------------------*/

/*---Private----------------------------------------------------------*/
typedef void (*EolAppFuncType)(void);
#ifdef SX5_HW
#define SOFTWARE_VERSION_LEN (NaviApp_GetM3SWVersionLen())
#define VEHICLE_INFO_NUM (NaviApp_GetM3VehicleInfo())
#else				
#define SOFTWARE_VERSION_LEN 21
#endif	

BOOL bEolEnterReq;
BOOL bEolExistReq;
BOOL bJ6EnterDiagFlag;
BOOL bSentJ6enterEolevent;
BOOL bJ6selfDiagResultRec;
BOOL uUpgradeResult;
BOOL bJ6RequestEolStatus;

U8 returnCode;
U8 uPowerLevel;
U8 sResultCode;
U8 sRespLen;
U8 uJ6selfDiagResult[2];
U8 ReqMsgData[REQMSG_MAX_DATALEN];
U8* sRespPstr;
U8 sReqLen;
U8 eolStatus;
U8 m3Dtc[DTC_CODE_MAX_NUM] = {0};
U8 soc_powerdown_delay=0;
U8 delay_flag = 0;


#ifdef SX5_HW
U8 m3version[22];
#else	
U8 m3version[SOFTWARE_VERSION_LEN];
#endif
E_QUERY_J6_LICENSE_STRUCT reqJ6Data;
extern const U8 can_diag_system_supplier_ecu_software_number[2];

extern void reset_soc_power(void);


U16 uPowerOnTimeCnt;
U16 uEolExistTimeCnt;

E_EOL_STATE eEolState;
E_MSGTYPE sReqType;
#define IS_REQTYPE_VALID()  (sReqType<E_MSGTYPE_NUM)

U8 eepData[2];
BOOL bEOLWaitEEPwriteResp;
U16 uEOLWaitEEPwriteCnt;
E_DATASEND_RESULT bEolConfigEepSendResult; 
static U8 uBadResp = 0x00;
static U8 uOkResp = 0X01;
static U8 HighLevel = 0X02;

#define E_NAVI_CLOSE_TIME_OUT 35
BOOL bNaviIsClosed;
U16 uNaviCloseTimeCnt;
BOOL bEol_Control_Accon = FALSE;
#define LEN_OF_SERIAL_NUMBER 14
#define LEN_OF_MANUFACTURING_DATA 4
 const static REQSTATICMSQ Req_msg_table[E_MSGTYPE_NUM]=
{  
    E_MSGID_ENTER_EOL,5,//00
    E_MSGID_J6_START_FROM_SD,5,
    E_MSGID_EXIST_EOL,5,
    E_MSGID_READ_BOOT_VERSION,5,
    E_MSGID_READ_SOFTWARE_VERSION,5,
    E_MSGID_READ_J6OS_VERSION,5,
    E_MSGID_READ_J6SVP_VERSION,5,
    E_MSGID_WRITE_SERIAL_NUMBER,LEN_OF_SERIAL_NUMBER+5,
    E_MSGID_READ_SERIAL_NUMBER,5,
    E_MSGID_READ_M3_DTC,5,
    E_MSGID_CLEAR_DTC,5,
    E_MSGID_SET_EEP_CONFIG_VAL,7,
    E_MSGID_GET_EEP_CONFIG_VAL,5,
    E_MSGID_ENTER_AVM_PRESS_MODE,6,
    E_MSGID_ENTER_REVERSE_MODE,6,
    E_MSGID_READ_POWER_DET,5,
    E_MSGID_READ_CAN_POWER_DET,5,
    E_MSGID_READ_IGN,    5,    
    E_MSGID_CTL_LED0,6,
    E_MSGID_CTL_LED1,6,
    E_MSGID_CTL_CAMERA,6,//20
    E_MSGID_READ_REVERSE_SIGNAL,5,
    E_MSGID_UPGRADE_J6_LICENSE_START_REQ,5,
    E_MSGID_UPGRADE_J6_LICENSE_END,5,
    E_MSGID_SEND_LICENSE_PACKET0,NOT_NEEDED_CHECK_LEN,
    E_MSGID_LICENSE0_SEND_FINISHED,5,
    E_MSGID_SEND_LICENSE_PACKET1,NOT_NEEDED_CHECK_LEN,
    E_MSGID_LICENSE1_SEND_FINISHED,5,
	E_MSGID_SET_ECU_MANUFACTURING_DATE,9,
	E_MSGID_GET_ECU_MANUFACTURING_DATE,5,
    E_MSGID_SEND_LICENSE_PACKET2,NOT_NEEDED_CHECK_LEN,
    E_MSGID_LICENSE2_SEND_FINISHED,5,
    E_MSGID_SEND_LICENSE_PACKET3,NOT_NEEDED_CHECK_LEN,
    E_MSGID_LICENSE3_SEND_FINISHED,5,
    E_MSGID_SEND_LICENSE_PACKET4,NOT_NEEDED_CHECK_LEN,
    E_MSGID_LICENSE4_SEND_FINISHED,5,    
    #ifdef AB01_HW
    E_MSGID_ENTER_FAILSAFE_MODE,5,
    #endif
    E_MSGID_READ_AVM_HW_IN,5,
    E_MSGID_READ_USB_INTERFACE_STATUS,5,
	E_MSGID_READ_SDCARD_INTERFACE_STATUS,5,
	//E_MSGID_SET_VEHICLE_CONFIG,6,
    E_MSGID_GET_VEHICLE_CONFIG,5,
    E_MSGID_CTL_AVM_SHUT_DOWN_TIME,7,
    //E_MSGID_READ_SDCARD_INTERFACE_STATUS,5,
    E_MSGID_CTL_DTCSETTING_OFF,5,
    E_MSGID_CTL_AVM_LED,6,
    E_MSGID_CTL_ACCONSETTING_ON,5,
    E_MSGID_REQ_J6_ENTER_SELF_DIAG,5,
};

E_QUERY_J6_LICENSE_STRUCT licenseData;

void set_fast_powerdown(U16 timeout);

void EolEntryReqHandler(void);
void ReadVersionReqHandler(void);
void WriteSerialNumberReqHandler(void);
void ReadSerialNumberReqHandler(void);
void WriteManufacturingDataReqHandler(void);
void ReadManufacturingDataReqHandler(void);
void PowerDetReqHandler(void);
void CANPowerDetReqHandler(void);
void ReadM3DTCReqHandler(void);
void ClearDtcReqHandler(void);
void SetEepCfgReqHandler(void);
void GetEepCfgReqHandler(void);
void SetVehicleConfigReqHandler(void);
void GetVehicleConfigReqHandler(void);
void EolReqJ6StartFromSDHandler(void);
#ifdef AB01_HW
void EolReqJ6EnterFailSafeHandler(void);
#endif
void ReadignReqHandler(void);
void EnterAVMReqHandler(void);
void EnterReverseReqHandler(void);

void ControlLed0Handler(void);
void ControlLed1Handler(void);
void ControlCameraHandler(void);
void ReadReverseHwSignalHandler(void);
void ReadAVMHwSignalHandler(void);
void ReadUSBinterfaceStatusHandler(void);
void ReadSDCARDinterfaceStatusHandler(void);
//void ReadRemoveableDeviceStatusHandler(void);
void QuickShotDownHandler(void);
void J6licenseHandler(void);
BOOL EolApp_GetEolStatus(void);
void DTCSettingOffHandler(void);
void AVMLedControlHandler(void);
void AVMHardKeyTestHandler(void);
void ACCONSettingOnHandler(void);

void Request_j6_enter_self_diag(void);

EolAppFuncType EolAppFunc[E_MSGTYPE_NUM]={
    EolEntryReqHandler,//00
    EolReqJ6StartFromSDHandler,
    EolEntryReqHandler,
    ReadVersionReqHandler,
    ReadVersionReqHandler,
    ReadVersionReqHandler,    
    ReadVersionReqHandler,
    WriteSerialNumberReqHandler,
    ReadSerialNumberReqHandler,
    ReadM3DTCReqHandler,
    ClearDtcReqHandler,
    SetEepCfgReqHandler,
    GetEepCfgReqHandler,
    EnterAVMReqHandler,
    EnterReverseReqHandler,
    PowerDetReqHandler,
    CANPowerDetReqHandler,
    ReadignReqHandler,
    ControlLed0Handler,
    ControlLed1Handler,
    ControlCameraHandler,//20
    ReadReverseHwSignalHandler,
    J6licenseHandler,
    J6licenseHandler,
    J6licenseHandler,
    J6licenseHandler,
    J6licenseHandler,
    J6licenseHandler,
	WriteManufacturingDataReqHandler,//28
	ReadManufacturingDataReqHandler,//29
    J6licenseHandler,
    J6licenseHandler,
    J6licenseHandler,
    J6licenseHandler,
    J6licenseHandler,
    J6licenseHandler,
    #ifdef AB01_HW
    EolReqJ6EnterFailSafeHandler,
    #endif
    ReadAVMHwSignalHandler,
    ReadUSBinterfaceStatusHandler,
    ReadSDCARDinterfaceStatusHandler,
   // SetVehicleConfigReqHandler,
    GetVehicleConfigReqHandler,
    QuickShotDownHandler,
    DTCSettingOffHandler,
    AVMLedControlHandler,
    //AVMHardKeyTestHandler,
    ACCONSettingOnHandler,
    //ReadRemoveableDeviceStatusHandler,
     Request_j6_enter_self_diag,
};

/*===FUNCTIONS========================================================*/
void EOLInit(void);
void EOL_Main(void);
void HandleBootVersion(void);
void HandleEolReq(void);
void HandleForwardMsg(void);
BOOL IsReqFormatOK(U8 type);
BOOL IsAllowForwardMsg(void);
void SendStartEOLReq(void);
/*---Global-----------------------------------------------------------*/
/***********************************************************************
* FUNCTION    : eol_task
* DESCRIPTION :
* INPUTS      : void
* RETURN      : void
***********************************************************************/
#define testused_for_enter_eol

void EOLInit(void)
{
    U8 sig = 0;
    eEolState = E_EOL_INIT;
    uPowerOnTimeCnt = E_POWER_ON_TIMEOUT;
#ifdef testused_for_enter_eol
    bEolEnterReq = TRUE;
#else
    bEolEnterReq = FALSE;
#endif
    bEolExistReq = FALSE;
    reqJ6Data.data.bReqSent = FALSE;
    reqJ6Data.data.bRespReceived = FALSE;
    reqJ6Data.data.recvDatatime = 0;
    reqJ6Data.data.uRecvDatalen = 0;
    reqJ6Data.type = E_MSGID_INVALID;
    licenseData.type = E_MSGID_INVALID;
    licenseData.data.bReqSent = FALSE;
    licenseData.data.bRespReceived = FALSE;
    licenseData.data.recvDatatime = 0;
    licenseData.data.uRecvDatalen = 0;    
    bJ6EnterDiagFlag = FALSE;
    bJ6selfDiagResultRec = FALSE;
    CS_SIG_SyncSend(SIG_EOL_ACTIVE_STATUS,&sig);
    bJ6RequestEolStatus= FALSE;
	bEolConfigEepSendResult = E_NORESULT;	
	bEOLWaitEEPwriteResp = FALSE;
}

void EOL_S1S2Init(void)
{
    U8 sig = 0;
    CS_SIG_SyncSend(SIG_EOL_ACTIVE_STATUS,&sig);    
    eEolState = E_EOL_IDLE;
}



void EOL_Main(void)
{
    U8 sig = 0;
    switch(eEolState)
    {
        case E_EOL_INIT:
            eEolState = E_EOL_SEND_CONNECT_REQ;
            sig = 0;
            CS_SIG_SyncSend(SIG_EOL_ACTIVE_STATUS,&sig);    
        break;
        case E_EOL_SEND_CONNECT_REQ:
            SendStartEOLReq();
            uPowerOnTimeCnt = E_POWER_ON_TIMEOUT;
            bEolEnterReq = FALSE;
            eEolState = E_EOL_WAIT_CONNNECT_RESP;
            sig = 0;
            CS_SIG_SyncSend(SIG_EOL_ACTIVE_STATUS,&sig);    
        break;
        case E_EOL_WAIT_CONNNECT_RESP:
            if(0==uPowerOnTimeCnt)
            {
                eEolState = E_EOL_EXIT;
                uEolExistTimeCnt = 0;
                sig = 0;
                CS_SIG_SyncSend(SIG_EOL_ACTIVE_STATUS,&sig);    
                break;
            }      
            uPowerOnTimeCnt--;
            if(bEolEnterReq)
            {
                bEolEnterReq = FALSE;
                eEolState = E_EOL_NORMAL;
                sig = 1;
                CS_SIG_SyncSend(SIG_EOL_ACTIVE_STATUS,&sig);    
            }            
        break;
        case E_EOL_NORMAL:
            //HandleBootVersion();
            //soc_slc_handler();
            HandleForwardMsg();
            HandleEolReq();
			reset_soc_power();
            if(bEolExistReq)
            {
                bEolExistReq = FALSE;
                eEolState = E_EOL_EXIT;
                uEolExistTimeCnt = E_EXIST_EOL_TIMEOUT;
                
            }
            if(bNaviIsClosed)
            {
                if(uNaviCloseTimeCnt++>E_NAVI_CLOSE_TIME_OUT)
                {
                    U8 naviPower = 1;
                    uNaviCloseTimeCnt = 0;
					Open_SOC_Power();
					POWER_PMIC_ON();
					soc_startup_from_sd();  
                    bNaviIsClosed = FALSE;
                    CS_SIG_SyncSend(SIG_B_SOC_POWER_ON, &naviPower);
                }
            }
        break;
        case E_EOL_EXIT:        
            if(0==uEolExistTimeCnt)
            {
                eEolState = E_EOL_IDLE;     
                sig = 0;
                CS_SIG_SyncSend(SIG_EOL_ACTIVE_STATUS,&sig);       
                EolService_DeInit();        
                break;
            }    
            uEolExistTimeCnt--;
        break;
        case E_EOL_IDLE:           
        break;
        default:break;
    }
}

BOOL EolApp_IsEolActivated(void)
{
    if((E_EOL_NORMAL == eEolState)
        ||(E_EOL_EXIT == eEolState))
        {
            return TRUE;
        }
    else return FALSE;
}


void SendStartEOLReq(void)
{
     EolService_SendMsg(E_MSDID_START_EOL,NULL,0); 
}


/***********************************************************************
*  Name        : HandleEolReq
*  Description : DeInit eol msg handler        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
 void  HandleEolReq(void)
{    
        if(IS_REQTYPE_VALID())
        {                
            if(IsReqFormatOK(sReqType) == FALSE)
            {
                sResultCode=E_NEGATIVE_BAD_REQUEST;
                sRespPstr = &uBadResp;
                sRespLen = 1;
            }
            else
            {
                EolAppFunc[sReqType]();
            }  
            
            if(sResultCode!=E_NOT_SENT_RESULT)
                EolService_SendMsg(Req_msg_table[sReqType].msgid,sRespPstr,sRespLen); 
                
            sReqType = E_MSGTYPE_NUM;
            sRespPstr = NULL;
            sRespLen = 0;
        }  
}

void HandleForwardMsg(void)
{
    if(reqJ6Data.data.bReqSent)
    {
    #ifdef AB01_HW
        if(((reqJ6Data.type == E_MSGID_ENTER_FAILSAFE_MODE)&&(reqJ6Data.data.recvDatatime++>WAIT_J6_FAILSAFE_RESP_TIME))
            ||((reqJ6Data.type != E_MSGID_ENTER_FAILSAFE_MODE)&&(reqJ6Data.data.recvDatatime++>WAIT_J6_RESP_TIME)))
    #else
        if(reqJ6Data.data.recvDatatime++>WAIT_J6_RESP_TIME)
    #endif
        {
            reqJ6Data.data.bReqSent= FALSE;
			  bEOLWaitEEPwriteResp = FALSE; 			
            EolService_SendMsg(reqJ6Data.type,&uBadResp,1); 
        }
		 if(bEOLWaitEEPwriteResp == TRUE) //Only Check EEP write status of vehicle infomation flag for E_MSGID_SET_VEHICLE_CONFIG service
		 {
		 	  if((uEOLWaitEEPwriteCnt++>E_WAIT_EEP_WRITE_EOL_RESULT_TIME)
					||(E_SENTFAIL == bEolConfigEepSendResult))
		 	  {
		 	  			reqJ6Data.data.bReqSent= FALSE;
						bEOLWaitEEPwriteResp = FALSE;	
						//If EEP write failed for vehicle infomation flag, send negtive response
						EolService_SendMsg(reqJ6Data.type,&uBadResp,1);	
		 	  }
		 }
        if(reqJ6Data.data.bRespReceived)
        {
        	 if(TRUE == bEOLWaitEEPwriteResp) //Only for E_MSGID_SET_VEHICLE_CONFIG service 
        	 {
        	 		if(E_SENTOK  == bEolConfigEepSendResult)
        	 		{
        	 			bEOLWaitEEPwriteResp = FALSE;
        	 			EolService_SendMsg(reqJ6Data.type,reqJ6Data.data.uRecvData,reqJ6Data.data.uRecvDatalen); 
	            		reqJ6Data.data.bReqSent= FALSE;
        	 		}
        	 }
			 else
			 {
	            EolService_SendMsg(reqJ6Data.type,reqJ6Data.data.uRecvData,reqJ6Data.data.uRecvDatalen); 
	            reqJ6Data.data.bReqSent= FALSE;
			 }
        }
    }

    if(bJ6RequestEolStatus)
    {
        U8 data[2];
        data[0] = 0x03;
        data[1] = EolApp_GetEolStatus();
        if(SocManager_SendMsg(TX_LQ, TYPE_EVENT,NAVI_RESP_EVENT,2,&data[0]))
            bJ6RequestEolStatus = FALSE;
    }
    
	 if(bJ6EnterDiagFlag)
    {
        if(bSentJ6enterEolevent)
        {
            EolService_SendMsg(E_MSGID_REPORT_J6_DTC_START,NULL,0); 
            bSentJ6enterEolevent = FALSE;
        }
        
        if(bJ6selfDiagResultRec)
        {
			delay_flag ++;
			if(delay_flag >= 5)
			{
			    bJ6selfDiagResultRec = FALSE;
			    EolService_SendMsg(E_MSGID_REPORT_J6_DTC_RESULT, uJ6selfDiagResult,2);
				delay_flag = 0;
			}
        }
    }
	 
    if(licenseData.data.bReqSent)
    {
    /*
        if(licenseData.data.recvDatatime++>WAIT_J6_LICENSE_RESP_TIME)
        {
            licenseData.data.bReqSent = FALSE;
            EolService_SendMsg(licenseData.type,&uBadResp,1); 
        }
        if(licenseData.data.bRespReceived)
        {
            licenseData.data.bRespReceived = FALSE;
            if(E_MSGID_GET_J6_HW_INFO_OF_LICENSE == licenseData.type)
            {
                if((licenseData.data.uRecvData[0]==0)||(licenseData.data.uRecvData[0]==0x11))
                {                    
                    licenseData.data.bReqSent = FALSE;
                    EolService_SendMsg(licenseData.type,licenseData.data.uRecvData,licenseData.data.uRecvDatalen);    
                }
                else
                {
                    licenseData.data.recvDatatime = 0;
                    EolService_SendMsg(licenseData.type,licenseData.data.uRecvData,licenseData.data.uRecvDatalen);    
                }
            }
            else
            {
                licenseData.data.bReqSent = FALSE;
                EolService_SendMsg(licenseData.type,licenseData.data.uRecvData,licenseData.data.uRecvDatalen);       
            }
        }
        */
    }
    
}

void EolEntryReqHandler(void)
{    
    eolStatus = ReqMsgData[0];
    sResultCode=E_POSITIVE;
    sRespPstr = &uOkResp;
    sRespLen = 1;
}

void ReadVersionReqHandler(void)
{
	U8 version;
    switch(ReqMsgData[2])
    {
        case E_M3_BOOT_VERSION:    
                NaviApp_GetM3SoftVersion(m3version);
                sResultCode=E_POSITIVE;
                sRespPstr = m3version;
                sRespLen = SOFTWARE_VERSION_LEN;		
        break;
        case E_J6_OS_VERSION:
            version = 0x01;
            SocManager_SendMsg(TX_LQ,TYPE_EVENT, RADIO_QUERY_ENG_SW_VERSION, 1, &version);
            sResultCode = E_NOT_SENT_RESULT;
            reqJ6Data.data.bReqSent = TRUE;
            reqJ6Data.data.recvDatatime = 0;
            reqJ6Data.data.uRecvDatalen = 0;
            reqJ6Data.type = E_MSGID_READ_J6OS_VERSION;
            reqJ6Data.data.bRespReceived = FALSE;
        break;

        case E_J6_SVP_VERSION:
            version = 0x02;
            SocManager_SendMsg(TX_LQ,TYPE_EVENT, RADIO_QUERY_ENG_SW_VERSION, 1, &version);  
            sResultCode = E_NOT_SENT_RESULT;       
            reqJ6Data.data.bReqSent = TRUE;
            reqJ6Data.data.recvDatatime = 0;
            reqJ6Data.data.uRecvDatalen = 0;
            reqJ6Data.data.bRespReceived = FALSE;
            reqJ6Data.type = E_MSGID_READ_J6SVP_VERSION;
        break;
        default:
                sResultCode=E_NEGATIVE_BAD_REQUEST;
                sRespPstr = NULL;
                sRespLen = 0;
        break;
    }
}


void WriteSerialNumberReqHandler(void)
{    
    U8 i;
    
    EED_LockDataBlock(EED_nECUSerialNumber);
    for(i=0;i<LEN_OF_SERIAL_NUMBER;i++)
    {
        EED_u8EcuSerialNumber[i] = ReqMsgData[5+i];
    }
    EED_UnlockAndSavDataBlock(EED_nECUSerialNumber);	
	SysJob_StartJob(JOB_EEPRW);
    sResultCode=E_POSITIVE;
    sRespPstr =&uOkResp ;
    sRespLen = 1;        
}

void ReadSerialNumberReqHandler(void)
{
    sResultCode=E_POSITIVE;
    sRespPstr = EED_u8EcuSerialNumber;
    sRespLen = LEN_OF_SERIAL_NUMBER;
}

//addition

void WriteManufacturingDataReqHandler(void)
{    
    U8 i;
    U8 arg[4];
	
    EED_LockDataBlock(EED_nDiagData4);
    for(i=0;i<LEN_OF_MANUFACTURING_DATA;i++)
    {
        EED_ECUManufacturingDate[i] = ReqMsgData[5+i];
    }
    EED_UnlockAndSavDataBlock(EED_nDiagData4);	

	for(i=0;i<LEN_OF_MANUFACTURING_DATA;i++)
	{
		arg[i] = ReqMsgData[5+i];
	}
	FDLDriver_Write(F199_STORE_ADDRESS,arg,1);
	
	SysJob_StartJob(JOB_EEPRW);
    sResultCode=E_POSITIVE;
    sRespPstr =&uOkResp ;
    sRespLen = 1;        
}

void ReadManufacturingDataReqHandler(void)
{
    sResultCode=E_POSITIVE;
    sRespPstr = EED_ECUManufacturingDate;
    sRespLen = LEN_OF_MANUFACTURING_DATA;
}


void PowerDetReqHandler(void)
{
/*    U16 power;
   CS_SIG_SyncReceive(SIG_ACC_DI_STATUS ,&power);
    uPowerLevel = power&0x01;
    
    sResultCode=E_POSITIVE;
    sRespPstr = &uPowerLevel;
    sRespLen = 1;
*/
	E_SYSTEM_VOLTAGE_STATUS eol_vol_status;
	CS_SIG_SyncReceive(SIG_VOLTAGEFAIL_STATUS, (U16 *)&eol_vol_status);  

	if(eol_vol_status==V_NORMAL)
	{
		sResultCode=E_POSITIVE;
		uPowerLevel = 0x01;
		sRespPstr = &uPowerLevel;
		sRespLen = 1;
	}
	else
	{
		sResultCode=E_POSITIVE;
		uPowerLevel = 0x00;
		sRespPstr = &uPowerLevel;
		sRespLen = 1;

	}
	
}

void CANPowerDetReqHandler(void)
{
   /*U16 power;
    CS_SIG_SyncReceive(SIG_ACCSTATUS ,&power);
    uPowerLevel = power&0x01;
    
    sResultCode=E_POSITIVE;
    sRespPstr = &uPowerLevel;
    sRespLen = 1;
	*/
	E_SYSTEM_VOLTAGE_STATUS eol_vol_status;
	CS_SIG_SyncReceive(SIG_VOLTAGEFAIL_STATUS, (U16 *)&eol_vol_status);  

	if((eol_vol_status==V_LOW)||(eol_vol_status==V_NORMAL)||(eol_vol_status==V_HIGH))
	{
		sResultCode=E_POSITIVE;
		uPowerLevel = 0x01;
		sRespPstr = &uPowerLevel;
		sRespLen = 1;
	}
	else
	{
		sResultCode=E_POSITIVE;
		uPowerLevel = 0x00;
		sRespPstr = &uPowerLevel;
		sRespLen = 1;
	}

}

void ReadM3DTCReqHandler(void)
{
	U8 i;	
	U8 MSG[DTC_CODE_MAX_NUM];
	_memcpy(MSG, EED_CANDTC, BIT30);
	
	for(i=0;i<DTC_CODE_MAX_NUM1;i++)
    {
        MSG[i+BIT30] = EED_CANDTC1[i];
    }  

	_memcpy(m3Dtc, MSG, DTC_CODE_MAX_NUM);
	
    sResultCode=E_POSITIVE;
    sRespPstr = m3Dtc;
    sRespLen = DTC_CODE_MAX_NUM;
}

void ClearDtcExtendDataRecord(void)
{
	EED_LockDataBlock(EED_nDTCOccurrenceCount);
    _memset(EED_CANDTC_OCCURRENCE_CNT,0,BIT30);
    EED_UnlockDataBlock(EED_nDTCOccurrenceCount);

	EED_LockDataBlock(EED_nDTCOccurrenceCount1);
    _memset(EED_CANDTC_OCCURRENCE_CNT1,0,DTC_CODE_MAX_NUM1);
    EED_UnlockDataBlock(EED_nDTCOccurrenceCount1);

	EED_LockDataBlock(EED_nDTCAgingCount);
    _memset(EED_CANDTC_AGING_CNT,0,BIT30);
    EED_UnlockDataBlock(EED_nDTCAgingCount);

	EED_LockDataBlock(EED_nDTCAgingCount1);
    _memset(EED_CANDTC_AGING_CNT1,0,DTC_CODE_MAX_NUM1);
    EED_UnlockDataBlock(EED_nDTCAgingCount1);

	EED_LockDataBlock(EED_nDTCAgedCount);
    _memset(EED_CANDTC_AGED_CNT,0,BIT30);
    EED_UnlockDataBlock(EED_nDTCAgedCount);

	EED_LockDataBlock(EED_nDTCAgedCount1);
    _memset(EED_CANDTC_AGED_CNT1,0,DTC_CODE_MAX_NUM1);
    EED_UnlockDataBlock(EED_nDTCAgedCount1);
}

void ClearDtcSnapshotDataRecord(void)
{
	EED_LockDataBlock(EED_nDiagData1);
	_memset(EED_Snapshot0100_VehicleSpeed1,0,(2*15));
	EED_UnlockAndSavDataBlock(EED_nDiagData1);

	EED_LockDataBlock(EED_nDiagData2);
	_memset(EED_Snapshot0100_VehicleSpeed2,0,(2*15));
	EED_UnlockAndSavDataBlock(EED_nDiagData2);

	EED_LockDataBlock(EED_nDiagData3);
	_memset(EED_Snapshot0100_VehicleSpeed3,0,(2*13));
	EED_UnlockAndSavDataBlock(EED_nDiagData3);	
	

	EED_LockDataBlock(EED_nDiagData4);
	_memset(EED_Snapshot0101_VehicleOdometer1,0,(4*7));
	EED_LockDataBlock(EED_nDiagData4);

	EED_LockDataBlock(EED_nDiagData5);
	_memset(EED_Snapshot0101_VehicleOdometer2,0,(4*7));
	EED_LockDataBlock(EED_nDiagData5);

	EED_LockDataBlock(EED_nDiagData6);
	_memset(EED_Snapshot0101_VehicleOdometer3,0,(4*7));
	EED_LockDataBlock(EED_nDiagData6);

	EED_LockDataBlock(EED_nDiagData7);
	_memset(EED_Snapshot0101_VehicleOdometer4,0,(4*7));
	EED_LockDataBlock(EED_nDiagData7);

	EED_LockDataBlock(EED_nDiagData8);
	_memset(EED_Snapshot0101_VehicleOdometer5,0,(4*7));
	EED_LockDataBlock(EED_nDiagData8);

    EED_LockDataBlock(EED_nDiagData11);
	_memset(EED_Snapshot0101_VehicleOdometer6,0,(4*6));
	EED_LockDataBlock(EED_nDiagData11);

    EED_LockDataBlock(EED_nDiagData9);
	_memset(EED_Snapshot0102_SupplyVoltage1,0,(1*30));
	EED_LockDataBlock(EED_nDiagData9);

    EED_LockDataBlock(EED_nDiagData10);
	_memset(EED_Snapshot0102_SupplyVoltage2,0,(1*11));
	EED_LockDataBlock(EED_nDiagData10);
}

void ClearDtcReqHandler(void)
{
    EED_LockDataBlock(EED_nDTCrecord);
    _memset(EED_CANDTC,0,BIT30);
    EED_UnlockDataBlock(EED_nDTCrecord);

    EED_LockDataBlock(EED_nDTCrecord1);
    _memset(EED_CANDTC1,0,DTC_CODE_MAX_NUM1);
    EED_UnlockDataBlock(EED_nDTCrecord1);

    EED_LockDataBlock(EED_nDTCFidData);
    _memset(EED_CANDTC_FID_DATA,0,BIT30);
    EED_UnlockDataBlock(EED_nDTCFidData);

    EED_LockDataBlock(EED_nDTCFidData1);
    _memset(EED_CANDTC_FID_DATA1,0,DTC_CODE_MAX_NUM1);
    EED_UnlockDataBlock(EED_nDTCFidData1);

	ClearDtcExtendDataRecord();

	ClearDtcSnapshotDataRecord();
	
	SysJob_StartJob(JOB_EEPRW);
	CanDiagDtc_desc_delay_set_sig(DESC_DELAY_SIG_1);
    CanDiagDtc_sv14_clear_start();
    sResultCode=E_POSITIVE;
    sRespPstr = &uOkResp;
    sRespLen = 1;
}

void SetEepCfgReqHandler(void)
{
        EED_LockDataBlock(EED_nEOLConfig);
        EED_u16EOLConfig =ReqMsgData[6]+ReqMsgData[5]*0x100;
        EED_UnlockAndSavDataBlock(EED_nEOLConfig);	
		SysJob_StartJob(JOB_EEPRW);
        sResultCode=E_POSITIVE;
        sRespPstr = &uOkResp;
        sRespLen = 1;
}
void GetEepCfgReqHandler(void)
{
        eepData[0] = EED_u16EOLConfig>>8;
        eepData[1] = EED_u16EOLConfig&0xff;
        sResultCode=E_POSITIVE;
        sRespPstr = eepData;
        sRespLen = 2;
}

extern BOOL eol_shultdown_cpu_watchdog;
void EolReqJ6StartFromSDHandler(void)
{
        U8 naviPower = 0;
        sResultCode=E_POSITIVE;
        sRespPstr = &uOkResp;
        sRespLen = 1;
		Close_SOC_Power();
		Close_CAM_Power();	
		//POWER_PMIC_ON();//markbylf
		eol_shultdown_cpu_watchdog = TRUE;
        CS_SIG_SyncSend(SIG_B_SOC_POWER_ON, &naviPower);
        uNaviCloseTimeCnt = 0;
        bNaviIsClosed = TRUE;
}

#ifdef AB01_HW
void EolReqJ6EnterFailSafeHandler(void)
{
        SocManager_SendMsg(TX_LQ,TYPE_EVENT, RADIO_REQUEST_A6_ENTER_FAIL_SAFE_MODE, 0, NULL);
        reqJ6Data.data.bReqSent = TRUE;
        reqJ6Data.data.recvDatatime = 0;
        reqJ6Data.data.uRecvDatalen = 0;
        reqJ6Data.data.bRespReceived = FALSE;
        reqJ6Data.type = E_MSGID_ENTER_FAILSAFE_MODE;
        sResultCode = E_NOT_SENT_RESULT;   
}
#endif

void ReadignReqHandler(void)
{
    U16 power;
    //CS_SIG_SyncReceive(SIG_ACC_DI_STATUS ,&power);
	power = GPIO_GetVal(GPIO_PORT_8, GPIO_PIN_0);
    sResultCode=E_POSITIVE;
    uPowerLevel = power&0x01;
    sRespPstr = &uPowerLevel;
    sRespLen = 1;
}
void EnterAVMReqHandler(void)
{
    if(ReqMsgData[5]<=1)//valid
    {
        U8 data[7] = {0};
       sResultCode=E_POSITIVE;
	   sRespPstr = &uOkResp;
        sRespLen = 1;
        data[0] = 0x01;
        data[1] = 0x00;
		if(0x01 == ReqMsgData[5])
			{
       			 data[2] = 1;
			}
		else if(0x00 == ReqMsgData[5])
			{
				data[2] = 2;
			}
        SocManager_SendMsg(TX_LQ,TYPE_EVENT, RADIO_NOTIFY_KEY_STATUS, 7, data);
    }
    else //invalid
    {
        sResultCode=E_NEGATIVE_BAD_REQUEST;
        sRespPstr = &uBadResp;
        sRespLen = 1;
    }
}
void EnterReverseReqHandler(void)
{
    if(ReqMsgData[5]<=1)
    {
        U8 reverse = ReqMsgData[5];
        sResultCode=E_POSITIVE;
        sRespPstr = &uOkResp;
        sRespLen = 1;        
	SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_RVC_STATUS,1,&reverse);
    }
    else //invalid parameter
    {
        sResultCode=E_NEGATIVE_BAD_REQUEST;
        sRespPstr = &uBadResp;
        sRespLen = 1;
    }
}

void ControlLed0Handler(void)
{
    U8 out = 0;
    if(ReqMsgData[5]<=1)
    {
        if(ReqMsgData[5])    out = 1;
        else out =0;
        //CS_SIG_SyncSend(SIG_LED0PWM_DO,&out);
        sResultCode=E_POSITIVE;
        sRespPstr = &uOkResp;
        sRespLen = 1;        
    }
    else
    {
        sResultCode=E_NEGATIVE_BAD_REQUEST;
        sRespPstr = &uBadResp;
        sRespLen = 1;
    }
}

void ControlLed1Handler(void)
{
//    U8 out = 0;
//    if(ReqMsgData[5]<=1)
//    {
//        if(ReqMsgData[5])    out = 1;
//        else out =0;
//        CS_SIG_SyncSend(SIG_LED1PWM_DO,&out);
//	NaviService_SendMsg(TX_LQ,TYPE_EVENT, RADIO_REQUEST_SET_J6_LED_CONTROL, 1, &out);
//        sResultCode=E_POSITIVE;
//        sRespPstr = &uOkResp;
//        sRespLen = 1;        
//    }
//    else
//    {
//        sResultCode=E_NEGATIVE_BAD_REQUEST;
//        sRespPstr = &uBadResp;
//        sRespLen = 1;
//    }
}

void ControlCameraHandler(void)
{
    if(ReqMsgData[5]<=4)
    {
        U8 data[7] = {0};
        sResultCode=E_POSITIVE;
        sRespPstr = &uOkResp;
        sRespLen = 1;
        #ifdef KAIYI_HW
        data[0] = 0x01;
        data[1] = ReqMsgData[5];
        SocManager_SendMsg(TX_LQ,TYPE_EVENT, RADIO_NOTIFY_KEY_STATUS, 7, data);
        #endif
        #ifdef B60X_HW
        data[0] = 0x01;
        data[1] = ReqMsgData[5];
        SocManager_SendMsg(TX_LQ,TYPE_EVENT, RADIO_NOTIFY_KEY_STATUS, 7, data);
        #endif
        #ifdef SX5_HW
        data[0] = 0x01;
        data[1] = ReqMsgData[5];
        SocManager_SendMsg(TX_LQ,TYPE_EVENT, RADIO_NOTIFY_KEY_STATUS, 7, data);
        #endif
        #ifdef T15_HW
        data[0] = 0x03;
        data[1] = ReqMsgData[5];
        SocManager_SendMsg(TX_LQ,TYPE_EVENT, RADIO_NOTIFY_KEY_STATUS, 7, data);
        #endif	
        data[0] = ReqMsgData[5];
        SocManager_SendMsg(TX_LQ,TYPE_EVENT, M3_SEND_RESP_OF_CAMERA_STATUS, 2, data);
    }
    else
    {
        sResultCode=E_NEGATIVE_BAD_REQUEST;
        sRespPstr = &uBadResp;
        sRespLen = 1;
   }
}

void ReadReverseHwSignalHandler(void)
{    
    U16 sig = 0;
    //CS_SIG_SyncReceive(SIG_REVERSE_DI_STATUS ,&sig);
    sResultCode=E_POSITIVE;
    uPowerLevel = sig&0x01;
    sRespPstr = &uPowerLevel;
    sRespLen = 1;
}

void DTCSettingOffHandler(void)
{
    eolStatus = ReqMsgData[0];
    sResultCode=E_POSITIVE;
    can_diag_control_dtc_setting_off();
    sRespPstr = &uOkResp;
    sRespLen = 1;
}

void AVMLedControlHandler(void)
{
	U8 LevelFlag;
	U8 AVM_TurnOn_flag = 0;
 	if(ReqMsgData[5]<=1)//valid
	{      
		switch (ReqMsgData[5])
		{
		
			case 0:
			{
				AVM_TurnOn_flag = FALSE;
				CS_SIG_SyncSend(SIG_AVM_TURNON_FLAG, &AVM_TurnOn_flag);
				sResultCode=E_POSITIVE;
		        sRespPstr = &uOkResp;
		        sRespLen = 1;
				/*
				GPIO_SetOutputMode(GPIO_PORT_8, GPIO_PIN_2, GPIO_OPT_INIT, GPIO_OPT_INIT);
				GPIO_SetVal(GPIO_PORT_8, GPIO_PIN_2, FALSE);
				LevelFlag = GPIO_GetVal(GPIO_PORT_8, GPIO_PIN_2);
				if(!LevelFlag)
				{
					sResultCode=E_POSITIVE;
			        sRespPstr = &uOkResp;
			        sRespLen = 1;
				}
				else
				{
					sResultCode=E_NEGATIVE_BAD_REQUEST;
	        		sRespPstr = &uBadResp;
	        		sRespLen = 1;
				}
				*/
			}break;
			case 1:
			{
				AVM_TurnOn_flag = TRUE;
				CS_SIG_SyncSend(SIG_AVM_TURNON_FLAG, &AVM_TurnOn_flag);
				sResultCode=E_POSITIVE;
		        sRespPstr = &HighLevel;
		        sRespLen = 1;
				/*
				GPIO_SetOutputMode(GPIO_PORT_8, GPIO_PIN_2, GPIO_OPT_INIT, GPIO_OPT_INIT);
				GPIO_SetVal(GPIO_PORT_8, GPIO_PIN_2, TRUE);
				LevelFlag = GPIO_GetVal(GPIO_PORT_8, GPIO_PIN_2);
				if(LevelFlag)
				{
					sResultCode=E_POSITIVE;
			        sRespPstr = &HighLevel;
			        sRespLen = 1;
				}
				else
				{
					sResultCode=E_NEGATIVE_BAD_REQUEST;
	        		sRespPstr = &uBadResp;
	        		sRespLen = 1;
				}
				*/
			}break;
			default:
				break;
		}		
    }
    else //invalid
    {
        sResultCode=E_NEGATIVE_BAD_REQUEST;
        sRespPstr = &uBadResp;
        sRespLen = 1;
    }

}

void AVMHardKeyTestHandler(void)
{
	U8 AVMLedFlag;
	AVMLedFlag = GPIO_GetVal(GPIO_PORT_8, GPIO_PIN_2);		
	
	if(AVMLedFlag)
	{
		sResultCode=E_POSITIVE;
		sRespPstr = &HighLevel;
		sRespLen = 1;
	}
	else
	{
		sResultCode=E_POSITIVE;
		sRespPstr = &uOkResp;
		sRespLen = 1;
	}
}

void ACCONSettingOnHandler(void)
{
	BOOL bAccOnStart;
	
    sResultCode=E_POSITIVE;
    bAccOnStart = TRUE;
	CS_SIG_SyncSend(SIG_ACCSTATUS, &bAccOnStart);
	bEol_Control_Accon = TRUE;
    sRespPstr = &uOkResp;
    sRespLen = 1;
}

void ReadAVMHwSignalHandler(void)
{
    U16 sig = 0;
	#ifdef USE_IO_FOR_AVM_HW
    CS_SIG_SyncReceive(SIG_AVM_HW_IN_STATUS ,&sig);
	#endif
    sResultCode=E_POSITIVE;
    uPowerLevel = sig&0x01;
    sRespPstr = &uPowerLevel;
    sRespLen = 1;
}

void ReadUSBinterfaceStatusHandler(void)
{
	U8 data=0x00;
    SocManager_SendMsg(TX_LQ,TYPE_EVENT, REQ_SOC_TO_SEND_REMOVABLE_DEVICE_STATUS, 1, &data);
    reqJ6Data.data.bReqSent = TRUE;
    reqJ6Data.data.recvDatatime = 0;
    reqJ6Data.data.uRecvDatalen = 0;
    reqJ6Data.data.bRespReceived = FALSE;
    reqJ6Data.type = E_MSGID_READ_USB_INTERFACE_STATUS;
	sResultCode = E_NOT_SENT_RESULT;  
}

void ReadSDCARDinterfaceStatusHandler(void)
{
	U8 data=0x01;
	SocManager_SendMsg(TX_LQ,TYPE_EVENT, REQ_SOC_TO_SEND_REMOVABLE_DEVICE_STATUS, 1, &data);
	reqJ6Data.data.bReqSent = TRUE;
	reqJ6Data.data.recvDatatime = 0;
	reqJ6Data.data.uRecvDatalen = 0;
	reqJ6Data.data.bRespReceived = FALSE;
	reqJ6Data.type =E_MSGID_READ_SDCARD_INTERFACE_STATUS;
	sResultCode = E_NOT_SENT_RESULT;
}



void SetVehicleConfigReqHandler(void)
{
    #ifdef SX5_HW
        U8 data[2]={0,0};
        data[1] = ReqMsgData[5];
				bEolConfigEepSendResult = E_NORESULT;
				EED_LockDataBlock(EED_nEOLConfig);
				EED_u16EOLConfig =ReqMsgData[5];
				EED_UnlockAndSavDataBlock(EED_nEOLConfig);	
				SysJob_StartJob(JOB_EEPRW);
				bEOLWaitEEPwriteResp = TRUE;		
        SocManager_SendMsg(TX_LQ,TYPE_EVENT, RADIO_REQUEST_SET_J6_CONFIG_DATA, 2, data);
        reqJ6Data.data.bReqSent = TRUE;
        reqJ6Data.data.recvDatatime = 0;
        reqJ6Data.data.uRecvDatalen = 0;
        reqJ6Data.data.bRespReceived = FALSE;
        reqJ6Data.type = E_MSGID_SET_VEHICLE_CONFIG;
	sResultCode = E_NOT_SENT_RESULT;  
    #endif
}

void GetVehicleConfigReqHandler(void)
{
    #ifdef SX5_HW
        U8 data={0};
        SocManager_SendMsg(TX_LQ,TYPE_EVENT, RADIO_REQUEST_GET_J6_CONFIG_DATA, 1, &data);
        reqJ6Data.data.bReqSent = TRUE;
        reqJ6Data.data.recvDatatime = 0;
        reqJ6Data.data.uRecvDatalen = 0;
        reqJ6Data.data.bRespReceived = FALSE;
        reqJ6Data.type = E_MSGID_GET_VEHICLE_CONFIG;
		sResultCode = E_NOT_SENT_RESULT;  
    #endif
}

void QuickShotDownHandler(void)
{
		U16 temp_timer=500;
		BOOL bAccOnStart;
				
		temp_timer =ReqMsgData[6]+ReqMsgData[5]*0x100;
		set_fast_powerdown(temp_timer);//5s
		
		bAccOnStart = FALSE;
		CS_SIG_SyncSend(SIG_ACCSTATUS, &bAccOnStart);
		bEol_Control_Accon = FALSE;

		sResultCode=E_POSITIVE;
        sRespPstr = &uOkResp;
        sRespLen = 1; 
}


void J6licenseHandler(void)
{
/*
    if((sReqType<=E_MSGTYPE_LICENSE4_SEND_FINISHED)&&(sReqType>=E_MSGTYPE_UPGRADE_J6_LICENSE_START_REQ))
    {        
        U8 data[2] = {0};
        U16 service = 0;
        U8 len = 0;
        BOOL bRet = TRUE;
        switch(sReqType)
        {
            case E_MSGTYPE_UPGRADE_J6_LICENSE_START_REQ:
                len = 0;
                service = FORWARD_QUERY_J6_TO_START_UPGRADE_LICENSE_REQ;
                SocManager_SendMsg(TX_LQ,TYPE_QUERY, service, len, data);
            break;
            case E_MSGTYPE_GET_J6_HW_INFO_OF_LICENSE:
                len = 0;
                service = FORWARD_QUERY_J6_TO_SEND_LICENSE_HW_INFO_REQ;
                SocManager_SendMsg(TX_LQ,TYPE_QUERY, service, len, data);
            break;
            case E_MSGTYPE_UPGRADE_J6_LICENSE_START:
                data[0] = E_LICENSE_PACKET_SEND_START;
                data[1] = ReqMsgData[5];
                len = 2;
                service = FORWARD_QUERY_J6_OF_LICENSE_TRANSMIT_REQ;
                SocManager_SendMsg(TX_LQ,TYPE_QUERY, service, len, data);
            break;
            case E_MSGTYPE_UPGRADE_J6_LICENSE_END:
                data[0] = E_ALL_LICENSE_FINISHED;
                len = 1;
                service = FORWARD_QUERY_J6_OF_LICENSE_TRANSMIT_REQ;
                SocManager_SendMsg(TX_LQ,TYPE_QUERY, service, len, data);
            break;
            case E_MSGTYPE_SEND_LICENSE_PACKET0:
            case E_MSGTYPE_SEND_LICENSE_PACKET1:
            case E_MSGTYPE_SEND_LICENSE_PACKET2:
            case E_MSGTYPE_SEND_LICENSE_PACKET3:
            case E_MSGTYPE_SEND_LICENSE_PACKET4:
            if(ReqMsgData[6]<=190)
            {
                ReqMsgData[4] = (sReqType - E_MSGTYPE_SEND_LICENSE_PACKET0)/2;
                service = FORWARD_QUERY_J6_OF_LICENSE_TRANSMIT_DATA,
                len = ReqMsgData[6]+3;
                SocManager_SendMsg(TX_LQ,TYPE_QUERY, service, len, ReqMsgData+4);
            }
            else
            {
                bRet = FALSE;
            }
            break;
            case E_MSGTYPE_LICENSE0_SEND_FINISHED:    
            case E_MSGTYPE_LICENSE1_SEND_FINISHED:
            case E_MSGTYPE_LICENSE2_SEND_FINISHED:
            case E_MSGTYPE_LICENSE3_SEND_FINISHED:
            case E_MSGTYPE_LICENSE4_SEND_FINISHED:
                data[0] = E_LICENSE_PACKET0_FINISHED+(sReqType-E_MSGTYPE_LICENSE0_SEND_FINISHED)/2;    
                len = 1;
                service = FORWARD_QUERY_J6_OF_LICENSE_TRANSMIT_REQ;
                SocManager_SendMsg(TX_LQ,TYPE_QUERY, service, len, data);   
            break;
            default:
            break;
        }
        if(bRet)
        {
            licenseData.data.bReqSent= TRUE;    
            licenseData.data.bRespReceived = FALSE;          
            licenseData.data.recvDatatime = 0;
            licenseData.data.uRecvDatalen = 0;
            licenseData.type = Req_msg_table[sReqType].msgid;
            sResultCode = E_NOT_SENT_RESULT;       
        }
        else
        {
            sResultCode=E_NEGATIVE_BAD_REQUEST;
            sRespPstr = &uBadResp;
            sRespLen = 1;
        }
    }
    */
}

/***********************************************************************
*  Name        : IsReqFormatOK
*  Description : DeInit Navi msg handler        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL IsReqFormatOK(U8 type)
{
    if(type<E_MSGTYPE_NUM)
    {
        if((NOT_NEEDED_CHECK_LEN == Req_msg_table[type].Reqdatalen)||(sReqLen==Req_msg_table[type].Reqdatalen))
        {
            return TRUE;
        }
        else			
        {
            return FALSE;
        }
    }
    return FALSE;
}



void Eol_DISPATCHERREQMSG(U8 msgid, U8* data, U8 len)
{
    U8 index;    
    for(index=0;index<E_MSGTYPE_NUM;index++)
    {
        if(msgid==Req_msg_table[index].msgid)
        {
            if(len)
            {
                if(len>REQMSG_MAX_DATALEN)
                {
                    len = REQMSG_MAX_DATALEN;
                }
                _memcpy(ReqMsgData,data,len);
            }
            sReqType = (E_MSGTYPE)index;
            sReqLen = len;
            if(sReqType == E_MSGTYPE_ENTER_EOL)
            {
                    bEolEnterReq = TRUE;
                    bEolExistReq = FALSE;
            }
            else if(sReqType == E_MSGTYPE_EXIST_EOL)
                {
                    bEolExistReq = TRUE;
                    bEolEnterReq = FALSE;
                }
            break;
        }
    }
}

void Eol_DISPATCHERACK(U8 msgid, BOOL isSent)
{

}


void Eol_DISPATCHERREPMSG(U8 msgid, U8 Result, U8* data, U8 len)
{
}

void EOL_DISPATCHERSPIMSG(U16 commandid, U8* data)
{      
    switch (commandid)
    {
        case J6_SEND_RESPONSE_OF_VERSION:
        if(((reqJ6Data.data.bReqSent)&&(reqJ6Data.type == E_MSGID_READ_J6OS_VERSION)&&(0x01 == data[0]))//os
            ||((reqJ6Data.data.bReqSent)&&(reqJ6Data.type == E_MSGID_READ_J6SVP_VERSION)&&(0x02 == data[0])))//svp
        {
            reqJ6Data.data.uRecvDatalen = data[1]-1;
            if(reqJ6Data.data.uRecvDatalen>RESPMSG_MAX_DATALEN)
            {
                reqJ6Data.data.uRecvDatalen = RESPMSG_MAX_DATALEN;
            }					
            _memcpy(reqJ6Data.data.uRecvData, &data[2], reqJ6Data.data.uRecvDatalen);	
            reqJ6Data.data.bRespReceived = TRUE;
        }
        break;
     
        case SOC_SEND_RESP_OF_REMOVABLE_DEVICE_STATUS:
        if(((reqJ6Data.data.bReqSent)&&(reqJ6Data.type == E_MSGID_READ_USB_INTERFACE_STATUS)/*&&(0x00 == data[0])*/)
			||((reqJ6Data.data.bReqSent)&&(reqJ6Data.type == E_MSGID_READ_SDCARD_INTERFACE_STATUS)/*&&(0x01 == data[0])*/))
        {
            reqJ6Data.data.uRecvDatalen = 1;
            reqJ6Data.data.uRecvData[0] = data[0];
            reqJ6Data.data.bRespReceived = TRUE;
			
        }
        break;
        
		
    #ifdef AB01_HW
        case A6_SEND_ENTER_FAIL_SAFE_MODE_RESP_TO_RADIO:
        if((reqJ6Data.data.bReqSent)&&(reqJ6Data.type == E_MSGID_ENTER_FAILSAFE_MODE))
        {
            reqJ6Data.data.uRecvDatalen = 1;
            reqJ6Data.data.uRecvData[0] = data[0];
            reqJ6Data.data.bRespReceived = TRUE;
            if(data[0]  == 0x01)
            {
                U8 naviPower = 0;
                SET_NAV_ENTER_FAILSAFE();
                CS_SIG_SyncSend(SIG_B_SOC_POWER_ON, &naviPower);
                uNaviCloseTimeCnt = 0;
                bNaviIsClosed = TRUE;
            }
        }        
        break;
    #endif

		case J6_SEND_RESPONSE_OF_SET_J6_CONFIG_DATA:
        #ifdef SX5_HW
            reqJ6Data.data.uRecvDatalen = 1;
            reqJ6Data.data.uRecvData[0] = data[0];
            reqJ6Data.data.bRespReceived = TRUE;
        #endif
        break;
				
		case J6_SEND_RESPONSE_OF_GET_J6_CONFIG_DATA:
        #ifdef SX5_HW
        if(data[0] == 0)
        {
            reqJ6Data.data.uRecvDatalen = 1;
			 if(VEHICLE_INFO_NUM == data[1])
			 {
            	reqJ6Data.data.uRecvData[0] = data[1];
			 }
			 else
			 {
			 	reqJ6Data.data.uRecvData[0] = uBadResp;
			 }
            reqJ6Data.data.bRespReceived = TRUE;
        }
        #endif
        break;

        case FORWARD_START_UPGRADE_LICENSE_RESP_TO_PC:
            licenseData.data.bRespReceived = TRUE;
            licenseData.data.uRecvDatalen = 1;
            licenseData.data.uRecvData[0] = data[0];
        break;
        
        case FORWARD_SEND_LICENSE_HW_INFO_RESP_TO_PC:
            licenseData.data.bRespReceived = TRUE;
            if(0 == data[0])
            {
                licenseData.data.uRecvDatalen = 1;
                licenseData.data.uRecvData[0] = data[0];
            }
            else
            {
                if(data[2]>RESPMSG_MAX_DATALEN)
                {
                    licenseData.data.uRecvDatalen = RESPMSG_MAX_DATALEN;
                }
                else
                    licenseData.data.uRecvDatalen = data[2]+2;
                    
                licenseData.data.uRecvData[0] = data[0];
                licenseData.data.uRecvData[1] = data[1];
                _memcpy(licenseData.data.uRecvData+2, data+3, licenseData.data.uRecvDatalen);
            }
        break;

        case FORWARD_LICENSE_TRANSMIT_REQ_RESP_TO_PC:
                licenseData.data.bRespReceived = TRUE;
                licenseData.data.uRecvDatalen = 1;
                licenseData.data.uRecvData[0] = data[1];
            
        break;

        case FORWARD_LICENSE_TRANSMIT_DATA_RESP_TO_PC:
                licenseData.data.bRespReceived = TRUE;
                licenseData.data.uRecvDatalen = 1;
                licenseData.data.uRecvData[0] = data[1];
        break;
		case J6_RESP_OF_ENTER_SELF_DIAG_STATUS: //0x830E
			reqJ6Data.data.uRecvDatalen = 1;
			 reqJ6Data.data.uRecvData[0] = data[0];
			 reqJ6Data.data.bRespReceived = TRUE;
		break;

        case J6_NOTIFY_M3_SELFTEST_RESULT:
            bJ6selfDiagResultRec = TRUE;
            uJ6selfDiagResult[0] = data[0];
            uJ6selfDiagResult[1] = data[1];
        break;
				
        default:break;
    }
}


BOOL EolApp_GetEolStatus(void)
{
    return (E_EOL_NORMAL == eEolState);
}

/***********************************************************************
*  Name        : NaviApp_EEPWrite_CallBack
*  Description : DeInit Navi msg handler        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EolConfig_EEPWrite_CallBack (ERR_TYPE type)
{
    if(type == ERR_OK)
    {
    
        bEolConfigEepSendResult = E_SENTOK;
    }
    else
    {
        bEolConfigEepSendResult = E_SENTFAIL;
    }
}

void reset_soc_power(void)
{
		if(GPIO_GetVal(GPIO_PORT_0,GPIO_PIN_6)&&(soc_powerdown_delay==0))//detect reset emmc sig
		{
				GPIO_SetVal(GPIO_PORT_10,GPIO_PIN_2,FALSE);//LOW 
				soc_powerdown_delay=1;
		}
		if(soc_powerdown_delay)
		{
				soc_powerdown_delay++;
				if(soc_powerdown_delay>=26)//(26-1)*20ms=500ms
				{
					  GPIO_SetVal(GPIO_PORT_10,GPIO_PIN_2,TRUE);;//HIGH 
						soc_powerdown_delay=0;
				}
		}
}

void J6SelfDiagFlagHandler(void)
{
		bJ6RequestEolStatus = TRUE;               
		bJ6EnterDiagFlag = TRUE;
		bSentJ6enterEolevent = TRUE;           
}

	
void  Request_j6_enter_self_diag(void)//REQ_J6_ENTER_SELF_DIAG
{
	U8 uAction = 0x01;
	switch(ReqMsgData[2])
    {
        case 0x03:  //REQ_J6_ENTER_SELF_DIAG
            SocManager_SendMsg(TX_LQ,TYPE_EVENT, M3_REQ_J6_ENTER_SELF_DIAG, 1, &uAction);  //0x820D
            sResultCode = E_NOT_SENT_RESULT;	
			//sResultCode = E_POSITIVE;		
            reqJ6Data.data.bReqSent = TRUE;
            reqJ6Data.data.recvDatatime = 0;
            reqJ6Data.data.uRecvDatalen = 0;
            reqJ6Data.type =E_MSGID_REQ_J6_ENTER_SELF_DIAG ;
            reqJ6Data.data.bRespReceived = FALSE;
		
        break;		
        default:
        break;
        
	}
}


#endif
/**************** END OF FILE *****************************************/

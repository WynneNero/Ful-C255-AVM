/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
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
* Version       Date                Name            Changes and comments
* 0.1           2015/12/22    ShangQiiuju       init version
* 0.2           2017/02/07    ZhangJie            Reinit for vicp upgrade template.
*=====================================================================*/

#include "config.h"
#include "canDiagService.h"
#include "canDiagService_if.h"
#include "appdesc_cfg.h"
#include "desc.h"
#include "Hal_if.h"
#include "CanDiagDtcCfg.h"
#include "NaviApp.h"
//#include "EEP_EOLconfig.h"
//#include "EEP_DiagData.h"
#include "SocManager.h"
#include "Signal_IF.H"
#include "SocDriver.H"
#include "appdesc.h"
#ifdef CAN_DIAG_OPTION
//CanDiagFuncCallBackType CanDiagAppCallBack = NULL;
#endif

void CanDiagAppCallBack(APPL_DESC_SERVICE_ID_TYPE MsgContextId, DescMsgContext* pMsgContext);
//void CanManager_CanDiagCallBack(APPL_DESC_SERVICE_ID_TYPE MsgContextId, DescMsgContext* pMsgContext);
typedef void (*DiagHandler)(DescMsgContext* pMsgContext);

BOOL bReqReserMcu;
U8 DelayToResetMCU;
U16 Can_DelayToFailForFlash;
U8 SEnterCalibrationResult;
U8 SCalibrationResult;
U8 Calibration_RetryCnt;
U8 StartCalibrationResult;
U8 Calibration_enterSuccess = 0x1; //enter fault
U8 SEnterEOLViewResult;

U8 upgradeflag = 0;
E_DATASEND_RESULT bEepSendResult_toCAN;
#define DELAT_RESET_MCU_TIMES  10
#define DELAT_FAIL_FLASH_TIMES  425
E_QUERY_J6_VERSION_STRUCT J6VersionData;
#define DIAG_WAIT_J6_RESP_TIME 30
E_DATASEND_RESP bWaitJ6Resp;
U8 uWaitJ6RespCnt;
U8 uWaiteepResultCnt;
#define WAIT_J6_UPGRADE_SET_TIME 250    //5S
#define WAIT_WRITE_EEP_UPGRADE_FLAG 50 //1S
U8 enter_bootloader_step;
U8 uAVSCarModelColor;
U8 uAVSTransparency;
U8 uAVSViewMode;
U8 uAVSCalibrationSta;

BOOL bJ6_start_complete = FALSE;
BOOL Request_J6Version= FALSE;

E_IO_CONTROL_STRUCT IoControl;

#define DELAT_RESET_MCU_TIMES  10
#define DELAT_FAIL_FLASH_TIMES  425
#define DIAG_WAIT_J6_RESP_TIME 50
#define EEP_INVALID_ADDRESS     0xFFFFFFFF
#define EEP_INVALID_LENGTH      0x0
static U8 u8_write_arg[64] = {0x0};
static U8 u8_read_arg[64] = {0x0};
/* For EEP rewrite callback */
CAN_EEP_RETRY_STRUCT EepWriteControl =
{
    EEP_INVALID_ADDRESS,
    EEP_INVALID_LENGTH,
    EEP_INVALID_LENGTH
};
/* For EEP reread callback */
CAN_EEP_RETRY_STRUCT EepReadControl =
{
    EEP_INVALID_ADDRESS,
    EEP_INVALID_LENGTH,
    EEP_INVALID_LENGTH
};

//
 void ApplDescClearFaultMemory_AddOn(DescMsgContext* pMsgContext);

static void CAN_Navi_Response(DescMsgContext* pMsgContext);
void Request_J6Version_handler(void);
void SendDiagResponse(E_CAN_DIAG_RESP_TYPE type);
void can_diag_set_reset(void);
void Can_response(DescMsgContext* pMsgContext);
void CanResponseEnterOfflineCalibrationResult(DescMsgContext* pMsgContext);
void CanResponseCalibrationResultFormCPU(DescMsgContext* pMsgContext);
static BOOL NRC_31_RequestOutOfRange_check(APPL_DESC_SERVICE_ID_TYPE MsgContextId, DescMsgContext* pMsgContext);
static BOOL NRC_22_conditionsNotCorrect_check(APPL_DESC_SERVICE_ID_TYPE MsgContextId, DescMsgContext* pMsgContext);
static BOOL can_diag_svc_negative_response_check(APPL_DESC_SERVICE_ID_TYPE MsgContextId, DescMsgContext* pMsgContext);

//$11
 void ApplDescResetHard_AddOn(DescMsgContext* pMsgContext);
 void ApplDescResetSoft_AddOn(DescMsgContext* pMsgContext);

//$85
 void ApplDescControl_DTC_Setting_onControlDTCSetting_AddOn(DescMsgContext* pMsgContext);
 void ApplDescControl_DTC_Setting_offControlDTCSetting_AddOn(DescMsgContext* pMsgContext);
 //$19 && $14
 void ApplDescClearDiagData_AddOn(DescMsgContext* pMsgContext);
 void ApplDescRead_DTC_number_AddOn(DescMsgContext* pMsgContext);
 void ApplDescRead_DTC_by_status_maskFaultMemory_AddOn(DescMsgContext* pMsgContext);
 void ApplDescReadEnvironmentDataFaultMemory_AddOn(DescMsgContext* pMsgContext);
 void ApplDescReadExtDataRecordFaultMemory_AddOn(DescMsgContext* pMsgContext);
 void ApplDescRead_supported_DTCFaultMemory_AddOn(DescMsgContext* pMsgContext);

 //$22
 void ApplDescReadDidSupplier_ECU_Boot_Software_Version_Number_AddOn(DescMsgContext* pMsgContext);// DES_22_F183_READ_SUPPLIER_ECU_BOOT_SOFTWARE_VERSION_NUMBER
 void ApplDescReadDidFAW_Part_Number_AddOn(DescMsgContext* pMsgContext);	  //DES_22_F187_READ_FAW_PART_NUMBER,
 void ApplDescReadDidFAW_ECU_Software_Version_Number_AddOn(DescMsgContext* pMsgContext);  //DES_22_F189_READ_FAW_ECU_SOFTWARE_VERSION_NUMBER,
 void ApplDescReadDidFAW_Vehicle_Identification_Number_AddOn(DescMsgContext* pMsgContext);	  //DES_22_F190_READ_FAW_VECHICLE_ID_NUMBER,//FAW Vehicle Identification Number
 void ApplDescReadDidFAW_ECU_Hardware_Version_Number_AddOn(DescMsgContext* pMsgContext);  //DES_22_F191_READ_FAW_ECU_HARDWARE_VERSION_NUMBER, 
 void ApplDescReadDidSupplier_ECU_Hardware_Number_AddOn(DescMsgContext* pMsgContext);	// DES_22_F192_READ_SUPPLIER_ECU_HARDWARE_NUMBER,
 void ApplDescReadDidSupplier_ECU_Hardware_Version_Number_AddOn(DescMsgContext* pMsgContext);	  //DES_22_F193_READ_SUPPLIER_ECU_HARDWARE_VERSION_NUMBER,
 void ApplDescReadDidSupplier_ECU_Software_Number_AddOn(DescMsgContext* pMsgContext);	  //DES_22_F194_READ_SUPPLIER_ECU_SOFTWARE_NUMBER,
 void ApplDescReadDidSupplier_ECU_Software_Version_Number_AddOn(DescMsgContext* pMsgContext);	  //DES_22_F195_READ_SUPPLIER_ECU_SOFTWARE_VERSION_NUMBER,
 void ApplDescReadDidRepair_Shop_Code_and_or_Tester_Serial_Number_AddOn(DescMsgContext* pMsgContext);	  //DES_22_F198_READ_REPAIR_SHOP_CODE_AND_OR_TESTER_SERIAL_NUMBER,
 void ApplDescReadDidProgramming_Date_AddOn(DescMsgContext* pMsgContext);	  //DES_22_F199_READ_PROGRAMMING_DATA,
 void ApplDescReadDidECU_Installation_Date_AddOn(DescMsgContext* pMsgContext);	  //DES_22_F19D_READ_ECU_INSTALLATION_DATA,
 void ApplDescReadDidFAW_Reserved_AddOn(DescMsgContext* pMsgContext);	  //DES_22_F1A0_READ_FAW_RESERVED,
 void ApplDescReadDidSystem_Configuration_1_AddOn(DescMsgContext* pMsgContext); 	  //DES_22_F1A1_READ_SYSTEM_CONFIGURATION_1,
 void ApplDescReadDidFAW_Reserved1_AddOn(DescMsgContext* pMsgContext);	  //DES_22_F1A7_READ_FAW_RESERVED_1,
 void ApplDescReadDidAVS_Calibration_Status_AddOn(DescMsgContext* pMsgContext);  //DES_22_2B00_READ_DidAVS_Calibration_Status,
 void ApplDescReadDidAVS_View_change_status_AddOn(DescMsgContext* pMsgContext);  //DES_22_2B10_READ_DidAVS_View_change_status,
 void ApplDescReadDidVehicleSpeed_Value__AddOn(DescMsgContext* pMsgContext);//DES_22_0100_READ_DidVehicleSpeedValue,
 void ApplDescReadDidOdometer_Value__AddOn(DescMsgContext* pMsgContext);//DES_22_0101_READ_DidOdometerValue,
 void ApplDescReadDidSupplyVoltage_Value__AddOn(DescMsgContext* pMsgContext);//DES_22_0102_READ_DidSupplyVoltageValue

  // $2E
 void ApplDescWriteDidFAW_Vehicle_Identification_Number_AddOn(DescMsgContext* pMsgContext); 	  //DES_22_F190_WRITE_FAW_VECHICLE_ID_NUMBER,
 void ApplDescWriteDidRepair_Shop_Code_and_or_Tester_Serial_Number_AddOn(DescMsgContext* pMsgContext);	  //DES_22_F198_WRITE_REPAIR_SHOP_CODE_AND_OR_TESTER_SERIAL_NUMBER,
 void ApplDescWriteDidProgramming_Date_AddOn(DescMsgContext* pMsgContext);	  //DES_22_F199_WRITE_PROGRAMMING_DATA,
 void ApplDescWriteDidECU_Installation_Date_AddOn(DescMsgContext* pMsgContext); 	  //DES_22_F19D_WRITE_ECU_INSTALLATION_DATA,
 void ApplDescWriteDidFAW_Reserved_AddOn(DescMsgContext* pMsgContext);	  //DES_22_F1A0_WRITE_FAW_RESERVED,
 void ApplDescWriteDidSystem_Configuration_1_AddOn(DescMsgContext* pMsgContext);	  //DES_22_F1A1_WRITE_SYSTEM_CONFIGURATION_1,
 void ApplDescWriteDidFAW_Reserved1_AddOn(DescMsgContext* pMsgContext); 	  //DES_22_F1A7_WRITE_FAW_RESERVED_1,

 //$2F
 void ApplDescReturnControlToECU_AVSView_AddOn(DescMsgContext* pMsgContext);
 void ApplDescControl_AVSView_AddOn(DescMsgContext* pMsgContext);
 static void CAN_EEP_RewriteHandler(DescMsgContext* pMsgContext);
 static void CAN_EEP_RereadHandler(DescMsgContext* pMsgContext);

 //$31
void ApplDescStartEnterEOLView_AddOn(DescMsgContext* pMsgContext); //DESC_3101_E100_START_ENTER_EOL_VIEW
void ApplDescResultStartEnterEOLView_AddOn(DescMsgContext* pMsgContext); //DESC_3103_E100_REQUEST_ROUTINE_RESULT_ENTER_EOL_VIEW
void ApplDescStartCalibration_AddOn(DescMsgContext* pMsgContext);   // DESC_3101_E101_START_CALIBRATION
void ApplDescResultStartCalibration_AddOn(DescMsgContext* pMsgContext);  //DESC_3103_E101_REQUEST_ROUTINE_RESULT_START_CALIBRATION

DiagHandler CanDiagHandler[DESC_MAX_TYPE]=
{
    NULL,//DESC_10_01_DEFAULT_SESSION,
    NULL,//DESC_10_02_PROGRAMMING_SESSION
    NULL,//DESC_10_03_EXTENDED_SESSION,
    ApplDescResetHard_AddOn,//DESC_11_01_HARD_RESET,
	ApplDescResetSoft_AddOn,//DESC_11_03_SOFR_RESET

	/* $85:Control DTC Setting */
	ApplDescControl_DTC_Setting_onControlDTCSetting_AddOn,//DESC_85_01_CONTROL_DTC_SETTING_ON,//
	ApplDescControl_DTC_Setting_offControlDTCSetting_AddOn,//DESC_85_02_CONTROL_DTC_SETTING_OFF,//
	
	/* $19 && $14:Fault Memory */
	ApplDescClearDiagData_AddOn,//DESC_14_CLR_DIAGNOSTIC_INFORMATION, //
	ApplDescRead_DTC_number_AddOn,//DESC_19_01_READ_NUMBER_OF_FAULTMEMORY, //
	ApplDescRead_DTC_by_status_maskFaultMemory_AddOn,//DESC_19_02_READ_MASK_FAULT_MEMORY,//
	ApplDescReadEnvironmentDataFaultMemory_AddOn,//DESC_19_04_READ_Environment_Data_Fault_Memory
	ApplDescReadExtDataRecordFaultMemory_AddOn,//DESC_19_06_READ_ExtDataRecord_Fault_Memory
	ApplDescRead_supported_DTCFaultMemory_AddOn,//DESC_19_0A_RPT_SUPPORTED_DTC, //
	
 /* $22:Read by data identifier */
    ApplDescReadDidSupplier_ECU_Boot_Software_Version_Number_AddOn,// DES_22_F183_READ_SUPPLIER_ECU_BOOT_SOFTWARE_VERSION_NUMBER	
	ApplDescReadDidFAW_Part_Number_AddOn,//DES_22_F187_READ_FAW_PART_NUMBER,
	ApplDescReadDidFAW_ECU_Software_Version_Number_AddOn,//DES_22_F189_READ_FAW_ECU_SOFTWARE_VERSION_NUMBER,
	ApplDescReadDidFAW_Vehicle_Identification_Number_AddOn, //DES_22_F190_READ_FAW_VECHICLE_ID_NUMBER,//FAW Vehicle Identification Number
	ApplDescReadDidFAW_ECU_Hardware_Version_Number_AddOn,//DES_22_F191_READ_FAW_ECU_HARDWARE_VERSION_NUMBER,
	ApplDescReadDidSupplier_ECU_Hardware_Number_AddOn,//DES_22_F192_READ_SUPPLIER_ECU_HARDWARE_NUMBER,
	ApplDescReadDidSupplier_ECU_Hardware_Version_Number_AddOn,//DES_22_F193_READ_SUPPLIER_ECU_HARDWARE_VERSION_NUMBER,
	ApplDescReadDidSupplier_ECU_Software_Number_AddOn,//DES_22_F194_READ_SUPPLIER_ECU_SOFTWARE_NUMBER,
	ApplDescReadDidSupplier_ECU_Software_Version_Number_AddOn,//DES_22_F195_READ_SUPPLIER_ECU_SOFTWARE_VERSION_NUMBER,
	ApplDescReadDidRepair_Shop_Code_and_or_Tester_Serial_Number_AddOn,//DES_22_F198_READ_REPAIR_SHOP_CODE_AND_OR_TESTER_SERIAL_NUMBER,
	ApplDescReadDidProgramming_Date_AddOn,//DES_22_F199_READ_PROGRAMMING_DATA,
	ApplDescReadDidECU_Installation_Date_AddOn, //DES_22_F19D_READ_ECU_INSTALLATION_DATA,
	ApplDescReadDidFAW_Reserved_AddOn,	//DES_22_F1A0_READ_FAW_RESERVED,
	ApplDescReadDidSystem_Configuration_1_AddOn,//DES_22_F1A1_READ_SYSTEM_CONFIGURATION_1,
	ApplDescReadDidFAW_Reserved1_AddOn, //DES_22_F1A7_READ_FAW_RESERVED_1,
	ApplDescReadDidAVS_Calibration_Status_AddOn, //DES_22_2B00_READ_DidAVS_Calibration_Status,
	ApplDescReadDidAVS_View_change_status_AddOn, //DES_22_2B10_READ_DidAVSViewchangestatus,
	ApplDescReadDidVehicleSpeed_Value__AddOn,//DES_22_0100_READ_DidVehicleSpeedValue,
	ApplDescReadDidOdometer_Value__AddOn,//DES_22_0101_READ_DidOdometerValue,
	ApplDescReadDidSupplyVoltage_Value__AddOn,//DES_22_0102_READ_DidSupplyVoltageValue,
	
	/* $2E:Write by data identifier */	
	ApplDescWriteDidFAW_Vehicle_Identification_Number_AddOn,		//DES_22_F190_WRITE_FAW_VECHICLE_ID_NUMBER,
	ApplDescWriteDidRepair_Shop_Code_and_or_Tester_Serial_Number_AddOn, 	//DES_22_F198_WRITE_REPAIR_SHOP_CODE_AND_OR_TESTER_SERIAL_NUMBER,
	ApplDescWriteDidProgramming_Date_AddOn, 	//DES_22_F199_WRITE_PROGRAMMING_DATA,
	ApplDescWriteDidECU_Installation_Date_AddOn,		//DES_22_F19D_WRITE_ECU_INSTALLATION_DATA,
	ApplDescWriteDidFAW_Reserved_AddOn, 	//DES_22_F1A0_WRITE_FAW_RESERVED,
	ApplDescWriteDidSystem_Configuration_1_AddOn,		//DES_22_F1A1_WRITE_SYSTEM_CONFIGURATION_1,
	ApplDescWriteDidFAW_Reserved1_AddOn,		//DES_22_F1A7_WRITE_FAW_RESERVED_1,
	
	/* $2F:routine */
	ApplDescReturnControlToECU_AVSView_AddOn, //DESC_2F_C0C0_00_ControlToECU_AVS_VIEW_CHANGE
	ApplDescControl_AVSView_AddOn,   //DESC_2F_C0C0_03_CONTROL_AVS_VIEW_CHANGE
	
	/* $31:routine */ 
	ApplDescStartEnterEOLView_AddOn,   // DESC_3101_E100_START_ENTER_EOL_VIEW
	ApplDescResultStartEnterEOLView_AddOn, // DESC_3103_E100_REQUEST_ROUTINE_RESULT_ENTER_EOL_VIEW
    ApplDescStartCalibration_AddOn, //DESC_3101_E101_START_CALIBRATION
	ApplDescResultStartCalibration_AddOn, //DESC_3103_E101_REQUEST_ROUTINE_RESULT_START_CALIBRATION

};

 void ApplDescInValidMessageHandler(void)
 {
        DescSetNegResponse(kDescNrcServiceNotSupported);
        DescProcessingDone();
 }

 static BOOL can_diag_svc_negative_response_check(APPL_DESC_SERVICE_ID_TYPE MsgContextId, DescMsgContext* pMsgContext)
{
    BOOL NRC_occured = FALSE;

 	/* request range check */
	if((TRUE == NRC_31_RequestOutOfRange_check(MsgContextId, pMsgContext)) 
		||(TRUE == NRC_22_conditionsNotCorrect_check(MsgContextId, pMsgContext)))
		{
			NRC_occured = TRUE;
		}
		return(NRC_occured);


}

static BOOL NRC_31_RequestOutOfRange_check(APPL_DESC_SERVICE_ID_TYPE MsgContextId, DescMsgContext* pMsgContext)
{
    BOOL NRC_occured = FALSE;

    U32 dtc_group_type = 0;
	U8 ExtendedDataType = 0;
	U8 ControlState = 0;
	U8 DTCSnapshotRecordNumber = 0;
	U8 index = 0;
	U8 WriteDate = 0;
	U8 HighFourBit = 0;
	U8 LowFourBit = 0;

    switch(MsgContextId)
    {
		/* $19 && $14:Fault Memory */                    
        case DESC_14_CLR_DIAGNOSTIC_INFORMATION:
            dtc_group_type = (((vuint32)pMsgContext->reqData[0]) << 16) & 0x00FF0000; /* High byte */
            dtc_group_type |= (((vuint32)pMsgContext->reqData[1]) << 8) & 0x0000FF00; /* Middle byte */
            dtc_group_type |= (((vuint32)pMsgContext->reqData[2])) & 0x000000FF; /* low byte */            
            if((DTC_GRP_ALL != dtc_group_type) && ( DTC_GRP_NETWORK != dtc_group_type )) /* Chery only use group-all */
            {
                NRC_occured = TRUE;
            }
            break;
		case DESC_19_04_READ_Environment_Data_Fault_Memory:
			DTCSnapshotRecordNumber = (U8)pMsgContext->reqData[3];
			if((FALSE == can_diag_check_supported_dtc(pMsgContext))||
				((DTCSnapshotRecordNumber != 0x01)&&(DTCSnapshotRecordNumber != 0xFF)))
			{
				NRC_occured = TRUE;
			}
			break;
		case DESC_19_06_READ_ExtDataRecord_Fault_Memory:
			ExtendedDataType = (U8)pMsgContext->reqData[3];
			if((FALSE == can_diag_check_supported_dtc(pMsgContext))||
				(((ExtendedDataType>0x04)&&(ExtendedDataType!=0xFF))||(ExtendedDataType==0x00)))
			{
				NRC_occured = TRUE;
			}
			break;
		// case DESC_2F_C0C0_03_CONTROL_AVS_VIEW_CHANGE:
		// 	ControlState = (U8)pMsgContext->reqData[0];
		// 	if(ControlState > 0x07)
		// 	{
		// 		NRC_occured = TRUE;
		// 	}
		// 	break;
/*		case DESC_2F_C0C1_03_CONTROL_AVS_DYNAMICPGS_STATUS:
			ControlState = (U8)pMsgContext->reqData[0];
			if((ControlState == 0)||(ControlState > 0x04))
			{
				NRC_occured = TRUE;
			}
			break;*/
		case DES_22_F19D_WRITE_ECU_INSTALLATION_DATA:
			/* BCD Code Check */
			for(index = 0; index < 4; index++)
			{
				WriteDate = (U8)pMsgContext->reqData[index];
				LowFourBit = ((U8)pMsgContext->reqData[index] & 0x0F);
				HighFourBit = (((U8)pMsgContext->reqData[index] >> 4) & 0x0F);
				if((HighFourBit >= 0x0A)||(LowFourBit >= 0x0A))
				{
					NRC_occured = TRUE;
				}
			}
			break;
        default:
            NRC_occured = FALSE; /* no NRC occured or no need to check */
        break;
    }

    if(TRUE == NRC_occured)
    {
        DescSetNegResponse(kDescNrcRequestOutOfRange);
    }

    return(NRC_occured);
}

static BOOL NRC_22_conditionsNotCorrect_check(APPL_DESC_SERVICE_ID_TYPE MsgContextId, DescMsgContext* pMsgContext)
{
	U8 VehicleSpeed[2];
	BOOL NRC_occured = FALSE;
	 switch(MsgContextId)
    {
 		case DESC_11_01_HARD_RESET:    
		case DESC_11_03_SOFR_RESET:
		case DES_22_F190_WRITE_FAW_VECHICLE_ID_NUMBER:
		case DES_22_F198_WRITE_REPAIR_SHOP_CODE_AND_OR_TESTER_SERIAL_NUMBER:
		case DES_22_F199_WRITE_PROGRAMMING_DATA:
		case DES_22_F19D_WRITE_ECU_INSTALLATION_DATA:
		case DES_22_F1A0_WRITE_FAW_RESERVED:
		case DES_22_F1A1_WRITE_SYSTEM_CONFIGURATION_1:
		case DES_22_F1A7_WRITE_FAW_RESERVED_1:
//        case DESC_2F_C0C1_00_ControlToECU_AVS_DYNAMICPGS_STATUS:
// 		case DESC_2F_C0C1_03_CONTROL_AVS_DYNAMICPGS_STATUS:
   		case DESC_2F_C0C0_00_ControlToECU_AVS_VIEW_CHANGE:
   		case DESC_2F_C0C0_03_CONTROL_AVS_VIEW_CHANGE:
		case DESC_14_CLR_DIAGNOSTIC_INFORMATION:
		case DESC_85_01_CONTROL_DTC_SETTING_ON:
		case DESC_85_02_CONTROL_DTC_SETTING_OFF:
		case DESC_3101_E101_START_CALIBRATION:
		case DESC_3103_E101_REQUEST_ROUTINE_RESULT_START_CALIBRATION:
		case DESC_3101_E100_START_ENTER_EOL_VIEW:
		case DESC_3103_E100_REQUEST_ROUTINE_RESULT_ENTER_EOL_VIEW:

			
	    CanAppGetSpeed(&VehicleSpeed);	
        if(((VehicleSpeed[0]*0x100+VehicleSpeed[1]) >= 0x0A))   // Speed must be smaller than 10 km/h
        {
            NRC_occured = TRUE;
        }
        break;

        default:
            NRC_occured = FALSE; /* no NRC occured or no need to check */
        break;
    }

    if(TRUE == NRC_occured)
    {
        DescSetNegResponse(kDescNrcConditionsNotCorrect);
    }

    return(NRC_occured);



}


void CanDiagAppCallBack(APPL_DESC_SERVICE_ID_TYPE MsgContextId, DescMsgContext* pMsgContext)
{
    if(MsgContextId>=DESC_MAX_TYPE)
    {
        ApplDescInValidMessageHandler();
    }
    else
    {
        if(CanDiagHandler[MsgContextId]!=NULL)
        {   
            CanDiagHandler[MsgContextId](pMsgContext);
        }
    }
}

void can_diag_set_reset(void)
{
    bReqReserMcu = TRUE;
    DelayToResetMCU = DELAT_RESET_MCU_TIMES;
}



void CanDiagServiceInit(void)
{
    //HAL_IoControl(DEV_CANDRIVER,E_REGISTER_CALLBACK, (void*)(CanManager_CanDiagCallBack));
}

void SendDiagResponse(E_CAN_DIAG_RESP_TYPE type)
{
    DescProcessingDone();
}


void CanDiagService_20msEntry(void)
{
    U32 CanUpgradeFlag;// = 0xa55aa55a;//app invalue
    U8 CanUpgradeFlagArg[4] = {0xa5,0x5a,0xa5,0x5a};
    U32 readData = 0;
	
	DiagRequest_Navi_handler();
	Request_J6Version_handler();
	
    if(upgradeflag == 1)
    {	
		if(uWaitJ6RespCnt == 0)
        {
            U8 data = 0;
            SocManager_SendMsg(TX_HQ,TYPE_QUERY, M3_SEND_UOGRADE_REQUEST_TO_J6, 1,&data);    
			#if 0
			bWaitJ6Resp = E_NULL;
			#else
			bWaitJ6Resp = E_ACK;
			#endif
            uWaitJ6RespCnt ++;
        }
        else
        {
            if(bWaitJ6Resp == E_ACK)
            {
                U8 i;
                upgradeflag = 2;                    
	      		bEepSendResult_toCAN = E_NORESULT;
				CanUpgradeFlag = (((U32)CanUpgradeFlagArg[3]<<24)+((U32)CanUpgradeFlagArg[2]<<16)+((U32)CanUpgradeFlagArg[1]<<8)+(U32)CanUpgradeFlagArg[0]);
				if(ERR_OK == HAL_Write(DEV_FDL,(U8*)&CanUpgradeFlag,CAN_UPGRADE_FLAG_LEN_OF_WORD))
				{
					if(CAN_UPGRADE_FLAG_LEN_OF_WORD == HAL_Read(DEV_FDL, (U8*)&readData,CAN_UPGRADE_FLAG_LEN_OF_WORD))
					{
						if(readData == CanUpgradeFlag)
						{
							bEepSendResult_toCAN = E_SENTOK;
						}
						else
						{
							bEepSendResult_toCAN = E_SENTFAIL;
						}
					}
				}
				else
				{
					bEepSendResult_toCAN = E_WRITEFAIL;
				}
				
                uWaiteepResultCnt = 0;
            }
            else if((bWaitJ6Resp == E_NACK)||(uWaitJ6RespCnt++>WAIT_J6_UPGRADE_SET_TIME))
            {
		    	upgradeflag = 0;          
            }
        }

    }
	if(upgradeflag == 2)
	{
        if((uWaiteepResultCnt++>WAIT_WRITE_EEP_UPGRADE_FLAG)||(bEepSendResult_toCAN == E_SENTFAIL))
        {			
            U8 data = 1;
	  		upgradeflag = 0;		
            SocManager_SendMsg(TX_HQ,TYPE_QUERY, M3_SEND_UOGRADE_REQUEST_TO_J6, 1,&data);   
        }
        if(bEepSendResult_toCAN == E_SENTOK)
        {
            upgradeflag = 0;
            OSWDG_SoftReset();
        }
		else if(bEepSendResult_toCAN == E_WRITEFAIL)
		{
			bEepSendResult_toCAN = E_NORESULT;
			upgradeflag = 1;
			
		}
	}

    /*For 11 03 Reset*/
    if(bReqReserMcu)
    {
        if(0 == DelayToResetMCU)
        {
        	OSWDG_StopWDG();//ccj.inorder to make sure wdg reset time not effect reset delay time
            OSWDG_SoftReset();
            bReqReserMcu = FALSE;
        }
        else
        {
            DelayToResetMCU--;
        }
    }
}

void CanDiag_SetDelayTime(void)
{
	Can_DelayToFailForFlash = DELAT_FAIL_FLASH_TIMES;
}

void Can_response(DescMsgContext* pMsgContext)
{
	if(0 == Can_DelayToFailForFlash)
	{
		upgradeflag = 0;
		bEepSendResult_toCAN = E_NORESULT;
		DescSetNegResponse(kDescNrcGeneralProgrammingFailure);
		DescProcessingDone();
	}
	else
	{
		Can_DelayToFailForFlash--;
	}
}

void CanResponseEnterOfflineCalibrationResult(DescMsgContext* pMsgContext)
{
	U8 mEnterCalibration = 0;
	
	if(0 == Can_DelayToFailForFlash)
	{
		if(SEnterCalibrationResult == 1)
		{
			SEnterCalibrationResult = 0;
			app_31ServiceNRC78Flag = 0;
			Calibration_RetryCnt = 0;
			DescProcessingDone();
		}
		else if(Calibration_RetryCnt > 1)  //30s timeout response nr22
		{
			DescSetNegResponse(kDescNrcConditionsNotCorrect);
			Calibration_RetryCnt = 0;
			app_31ServiceNRC78Flag = 0;
			DescProcessingDone();
			return;
		}
		else
		{
			Can_DelayToFailForFlash = DELAT_FAIL_FLASH_TIMES;
			Calibration_RetryCnt++;
		}
	}
	else
	{
		Can_DelayToFailForFlash--;
	}
}

/******************************************************************************
* Name:    CanResponseStartCalibration 
*
* Desc:    
* Param:   
* Return:  
* Global:  
* Note:    
* Author:  uidq3099_colin
* -------------------------------------
* Log:    2021/06/21, Create this function by uidq3099_colin
 ******************************************************************************/
void CanResponseStartCalibration(DescMsgContext* pMsgContext)
{
	U8 mStartEnterCalibration = 0;
	
	if(0 == Can_DelayToFailForFlash)
	{
		if(StartCalibrationResult == 1)
		{
			StartCalibrationResult = 0;
			app_31ServiceNRC78Flag = 0;
			Calibration_RetryCnt = 0;
			DescProcessingDone();
		}
		else if(Calibration_RetryCnt > 1)  //30s timeout response nr22
		{
			DescSetNegResponse(kDescNrcConditionsNotCorrect);
			Calibration_RetryCnt = 0;
			app_31ServiceNRC78Flag = 0;
			DescProcessingDone();
			return;
		}		
		else
		{
			Can_DelayToFailForFlash = DELAT_FAIL_FLASH_TIMES;
			Calibration_RetryCnt++;
		}
	}
	else
	{
		Can_DelayToFailForFlash--;
	}
}


void CanResponseCalibrationResultFormCPU(DescMsgContext* pMsgContext)
{
	if(0 == Can_DelayToFailForFlash)
	{
		if(SCalibrationResult == 0)
		{
			pMsgContext->resDataLen = 1;
			pMsgContext->resData = SCalibrationResult;
			DescProcessingDone();
		}
		else
		{
			Can_DelayToFailForFlash = DELAT_FAIL_FLASH_TIMES;
		}
	}
	else
	{
		Can_DelayToFailForFlash--;
	}
}

void ApplDescResetHard_AddOn(DescMsgContext* pMsgContext)
{
    if(FALSE == can_diag_svc_negative_response_check(DESC_11_01_HARD_RESET, pMsgContext))
    {
        can_diag_set_reset();
    }
    DescProcessingDone();
}

void ApplDescResetSoft_AddOn(DescMsgContext* pMsgContext)
{
    if(FALSE == can_diag_svc_negative_response_check(DESC_11_03_SOFR_RESET, pMsgContext))
    {
        can_diag_set_reset();
    }
    DescProcessingDone();
}

void ApplDescClearFaultMemory_AddOn(DescMsgContext* pMsgContext)
{
    if(!CanDiagDtc_desc_delay_get_sig(DESC_DELAY_SIG_1))
    {
        SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
    }
}

void ApplDescControl_DTC_Setting_onControlDTCSetting_AddOn(DescMsgContext* pMsgContext)
{
    if(FALSE == can_diag_svc_negative_response_check(DESC_85_01_CONTROL_DTC_SETTING_ON, pMsgContext))
    {
        can_diag_control_dtc_setting_on();
    }
    SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
}

void ApplDescControl_DTC_Setting_offControlDTCSetting_AddOn(DescMsgContext* pMsgContext)
{
    if(FALSE == can_diag_svc_negative_response_check(DESC_85_02_CONTROL_DTC_SETTING_OFF, pMsgContext))
    {
        can_diag_control_dtc_setting_off();
    }
    SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
}

void ClearDiagDtcData(void)
{
	/*
	CanDiagDtc_desc_delay_set_sig(DESC_DELAY_SIG_1);
	CanDiagDtc_sv14_clear_start(); 
	*/
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
}

void ApplDescClearDiagData_AddOn(DescMsgContext* pMsgContext)
{
	U32 dtc_group_type = 0;

    if(FALSE == can_diag_svc_negative_response_check(DESC_14_CLR_DIAGNOSTIC_INFORMATION, pMsgContext))
    {
    	dtc_group_type = (((vuint32)pMsgContext->reqData[0]) << 16) & 0x00FF0000; /* High byte */
        dtc_group_type |= (((vuint32)pMsgContext->reqData[1]) << 8) & 0x0000FF00; /* Middle byte */
        dtc_group_type |= (((vuint32)pMsgContext->reqData[2])) & 0x000000FF; /* low byte */    
		CanDiagDtc_desc_delay_set_sig(DESC_DELAY_SIG_1);
    	if(dtc_group_type == DTC_GRP_ALL)
    	{
            CanDiagDtc_sv14_clear_start(); 
    	}
		else if((dtc_group_type == DTC_GRP_NETWORK))
		{
			CanDiagDtc_sv14_clear_network_grp_start();
		}
		 DescStartRepeatedServiceCall(&ApplDescClearFaultMemory_AddOn);   
    }
    else
    {        
        SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
    }
}


void ApplDescRead_DTC_number_AddOn(DescMsgContext* pMsgContext)
{
    U16 dtc_num = 0; 

    if(FALSE == can_diag_svc_negative_response_check(DESC_19_01_READ_NUMBER_OF_FAULTMEMORY, pMsgContext))
    {
        dtc_num = can_diag_get_dtc_count( pMsgContext->reqData[0]);
        pMsgContext->resData[0] = DTC_STATUS_AVAILABILITY_MASK;
        pMsgContext->resData[1] = DTC_FORMAT_INDENTIFIER;        
        pMsgContext->resData[2] = (U8)(dtc_num>>8);        
        pMsgContext->resData[3] =  (U8)(dtc_num&0xff);
        pMsgContext->resDataLen = 4;
    }
    SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
}

void ApplDescRead_DTC_by_status_maskFaultMemory_AddOn(DescMsgContext* pMsgContext)
{
    U16 dtc_num = 0; 

    if(FALSE == can_diag_svc_negative_response_check(DESC_19_02_READ_MASK_FAULT_MEMORY, pMsgContext))
    {
        dtc_num = can_diag_get_dtc_status_by_status_mask(&(pMsgContext->resData[1]), pMsgContext->reqData[0]);
        pMsgContext->resData[0] = DTC_STATUS_AVAILABILITY_MASK;
        pMsgContext->resDataLen = 1 + dtc_num * 4;
    }
    SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
}

void ApplDescReadEnvironmentDataFaultMemory_AddOn(DescMsgContext* pMsgContext)
{
    if(FALSE == can_diag_svc_negative_response_check(DESC_19_04_READ_Environment_Data_Fault_Memory, pMsgContext))
    {
        pMsgContext->resData[0] = pMsgContext->reqData[0];
        pMsgContext->resData[1] = pMsgContext->reqData[1];
        pMsgContext->resData[2] = pMsgContext->reqData[2];
        pMsgContext->resData[3] = can_diag_get_dtc_status_by_DTC(pMsgContext);
		
		if(pMsgContext->resData[3] & (DTC_STATUS_BIT0_MASK_TF|DTC_STATUS_BIT3_MASK_CDTC))
		{
			pMsgContext->resData[4] = DTC_SNAPSHOT_RECORD_NUMBER;
			pMsgContext->resData[5] = DTC_SNAPSHOT_RECORD_NUMBER_OF_IDENTIFIERS;
	        can_diag_get_dtc_snapshot_record(&(pMsgContext->resData[6]),pMsgContext);
	        pMsgContext->resDataLen = DTC_SNAPSHOT_RECORD_NUMBER_LEN;
		}
		else
		{
			pMsgContext->resDataLen = DTC_SNAPSHOT_RECORD_NUMBER_LEN - 15;
		}
    }
    SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
}

void ApplDescReadExtDataRecordFaultMemory_AddOn(DescMsgContext* pMsgContext)
{
   U16 dtc_num = 0;
   DescMsgLen reslen = 0;
   if(FALSE == can_diag_svc_negative_response_check(DESC_19_06_READ_ExtDataRecord_Fault_Memory, pMsgContext))
   {
 		pMsgContext->resData[0] = pMsgContext->reqData[0];
        pMsgContext->resData[1] = pMsgContext->reqData[1];
        pMsgContext->resData[2] = pMsgContext->reqData[2];	
		reslen = can_diag_get_dtc_extdata_record(&(pMsgContext->resData[4]),pMsgContext);
		pMsgContext->resData[3] = can_diag_get_dtc_status_by_DTC(pMsgContext);
		if(pMsgContext->resData[3] & (DTC_STATUS_BIT0_MASK_TF|DTC_STATUS_BIT3_MASK_CDTC))
		{
			pMsgContext->resDataLen = reslen;
		}
		else
		{
			pMsgContext->resDataLen = 4;
		}
   }
   SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
}

void ApplDescRead_supported_DTCFaultMemory_AddOn(DescMsgContext* pMsgContext)
{
    U16 dtc_num = 0;
    if(FALSE == can_diag_svc_negative_response_check(DESC_19_0A_RPT_SUPPORTED_DTC, pMsgContext))
    {
        pMsgContext->resData[0] = DTC_STATUS_AVAILABILITY_MASK;
        dtc_num = can_diag_get_supported_dtc(&(pMsgContext->resData[1]));

        pMsgContext->resDataLen = 1 + dtc_num * 4;
    }
      
    SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
 }     


///////////////////////////// $22 /////////////////////////////////////

void ApplDescReadDidSupplier_ECU_Boot_Software_Version_Number_AddOn(DescMsgContext* pMsgContext)//DES_22_F183_READ_SUPPLIER_ECU_BOOT_SOFTWARE_VERSION_NUMBER,
{
	U8 *bootloader_version = BOOTLOADER_VERSION_ADDRESS;
	if(FALSE == can_diag_svc_negative_response_check(DES_22_F183_READ_SUPPLIER_ECU_BOOT_SOFTWARE_VERSION_NUMBER, pMsgContext))
	{  
		pMsgContext->resDataLen = BOOTLOADER_VERSION_LENGTH;  
		_memcpy(pMsgContext->resData, bootloader_version, pMsgContext->resDataLen);
		SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
	}
	else 
		SendDiagResponse(E_NEGATIVE_DIAG_RESPONSE);
}

void ApplDescReadDidFAW_Part_Number_AddOn(DescMsgContext* pMsgContext)		 //DES_22_F187_READ_FAW_PART_NUMBER,
{
	U8 arg[16]={"3785150-QC02    "};
    if(FALSE == can_diag_svc_negative_response_check(DES_22_F187_READ_FAW_PART_NUMBER, pMsgContext))
	{  
		pMsgContext->resDataLen = 16;  
		_memcpy(pMsgContext->resData, arg, pMsgContext->resDataLen);
	}
    SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);

}
void ApplDescReadDidFAW_ECU_Software_Version_Number_AddOn(DescMsgContext* pMsgContext) //DES_22_F189_READ_FAW_ECU_SOFTWARE_VERSION_NUMBER,
{
	if(FALSE == can_diag_svc_negative_response_check(DES_22_F189_READ_FAW_ECU_SOFTWARE_VERSION_NUMBER, pMsgContext))
	{
		J6VersionData.bReqSent = TRUE;
		J6VersionData.uSoftwareVersionType = FAW_ECU_SOFT_TYPE;
		J6VersionData.uReqVersionType = 0x03;
		J6VersionData.uRecvDatatime = 0;
		J6VersionData.bRespReceived = TRUE;	
		J6VersionData.uReqNumber = 15;
		Request_J6Version =TRUE;
		DescStartRepeatedServiceCall(&CAN_Navi_Response);
	}
}

void ApplDescReadDidFAW_Vehicle_Identification_Number_AddOn(DescMsgContext* pMsgContext)	 //DES_22_F190_READ_FAW_VECHICLE_ID_NUMBER,//FAW Vehicle Identification Number
{
	U8 arg[20]={0};
	U8 arg_nowrite[20]={0};
	U8 RET;
	if(FALSE == can_diag_svc_negative_response_check(DES_22_F190_READ_FAW_VECHICLE_ID_NUMBER, pMsgContext))
	{  
		pMsgContext->resDataLen = 17;
		RET = FDdriver_BlackCheck(F190_STORE_ADDRESS, 5);
		if(RET == TRUE)
		{
			/* not written */
			_memcpy(pMsgContext->resData, arg_nowrite, pMsgContext->resDataLen);
		}
		else
		{
			/* is written */
			RET = FDLDriver_Read(F190_STORE_ADDRESS, arg, 5);
			_memcpy(pMsgContext->resData, arg, pMsgContext->resDataLen);
			if(0 == RET)
            {
                /* Read Error, need retry! */
                EepReadControl.uEepRetryAddr = F190_STORE_ADDRESS;
                EepReadControl.uEepRetryWordNum = 5;
                EepReadControl.uEepRetryByte = pMsgContext->resDataLen;
                DescStartRepeatedServiceCall(&CAN_EEP_RereadHandler);
                return;
            }
		}
		SendDiagResponse(E_POSITIVE_DIAG_RESPONSE); 	
	}
	else
	{
		SendDiagResponse(E_NEGATIVE_DIAG_RESPONSE);
	}

}
void ApplDescReadDidFAW_ECU_Hardware_Version_Number_AddOn(DescMsgContext* pMsgContext)	 //DES_22_F191_READ_FAW_ECU_HARDWARE_VERSION_NUMBER,
{
	static U8 arg[15]={"HW001210706"};  

	if(FALSE == can_diag_svc_negative_response_check(DES_22_F191_READ_FAW_ECU_HARDWARE_VERSION_NUMBER, pMsgContext))
	{  
		pMsgContext->resDataLen = 16;
		_memcpy(pMsgContext->resData, arg, pMsgContext->resDataLen);
	}
	SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
}

void ApplDescReadDidSupplier_ECU_Hardware_Number_AddOn(DescMsgContext* pMsgContext) 	 //DES_22_F192_READ_SUPPLIER_ECU_HARDWARE_NUMBER,
{
	static U8 arg[16]={"HW001210706"};
	if(FALSE == can_diag_svc_negative_response_check(DES_22_F192_READ_SUPPLIER_ECU_HARDWARE_NUMBER, pMsgContext))
	{  
		pMsgContext->resDataLen = 16;
		_memcpy(pMsgContext->resData, arg, pMsgContext->resDataLen);
	}
	SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
}

void ApplDescReadDidSupplier_ECU_Hardware_Version_Number_AddOn(DescMsgContext* pMsgContext) 	 //DES_22_F193_READ_SUPPLIER_ECU_HARDWARE_VERSION_NUMBER,
{
	static U8 arg[16]={"HW001210706"};
	if(FALSE == can_diag_svc_negative_response_check(DES_22_F193_READ_SUPPLIER_ECU_HARDWARE_VERSION_NUMBER, pMsgContext))
	{  
		pMsgContext->resDataLen = 16;
		_memcpy(pMsgContext->resData, arg, pMsgContext->resDataLen);
	}
	SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
}

void ApplDescReadDidSupplier_ECU_Software_Number_AddOn(DescMsgContext* pMsgContext)//DES_22_F194_READ_SUPPLIER_ECU_SOFTWARE_NUMBER,
{
	if(FALSE == can_diag_svc_negative_response_check(DES_22_F194_READ_SUPPLIER_ECU_SOFTWARE_NUMBER, pMsgContext))
	{  
		J6VersionData.bReqSent = TRUE;
		J6VersionData.uSoftwareVersionType = SUPPLIER_ECU_SOFT;
		J6VersionData.uReqVersionType = 0x03;
		J6VersionData.uRecvDatatime = 0;
		J6VersionData.bRespReceived = TRUE;	
		J6VersionData.uReqNumber = 15;
		Request_J6Version =TRUE;
		DescStartRepeatedServiceCall(&CAN_Navi_Response);
	}
}

void ApplDescReadDidSupplier_ECU_Software_Version_Number_AddOn(DescMsgContext* pMsgContext)//DES_22_F195_READ_SUPPLIER_ECU_SOFTWARE_VERSION_NUMBER,
{
	if(FALSE == can_diag_svc_negative_response_check(DES_22_F195_READ_SUPPLIER_ECU_SOFTWARE_VERSION_NUMBER, pMsgContext))
	{  
		J6VersionData.bReqSent = TRUE;
		J6VersionData.uSoftwareVersionType = SUPPLIER_ECU_SOFT;
		J6VersionData.uReqVersionType = 0x03;
		J6VersionData.uRecvDatatime = 0;
		J6VersionData.bRespReceived = TRUE;	
		J6VersionData.uReqNumber = 15;
		Request_J6Version =TRUE;
		DescStartRepeatedServiceCall(&CAN_Navi_Response);
	}
}

void ApplDescReadDidRepair_Shop_Code_and_or_Tester_Serial_Number_AddOn(DescMsgContext* pMsgContext)//DES_22_F198_READ_REPAIR_SHOP_CODE_AND_OR_TESTER_SERIAL_NUMBER,
{
	U8 arg[12]={0};
	U8 arg_nowrite[12]={0};
	U8 RET;
	if(FALSE == can_diag_svc_negative_response_check(DES_22_F198_READ_REPAIR_SHOP_CODE_AND_OR_TESTER_SERIAL_NUMBER, pMsgContext))
	{  		
		pMsgContext->resDataLen = 10;
		RET = FDdriver_BlackCheck(F198_STORE_ADDRESS,arg, 3);
		if(RET == TRUE)
		{
			/* not written */
			_memcpy(pMsgContext->resData, arg_nowrite, pMsgContext->resDataLen);
		}
		else
		{
			RET = FDLDriver_Read(F198_STORE_ADDRESS,arg, 3);
			_memcpy(pMsgContext->resData, arg, pMsgContext->resDataLen);
			if(0 == RET)
            {
                /* Read Error, need retry! */
                EepReadControl.uEepRetryAddr = F198_STORE_ADDRESS;
                EepReadControl.uEepRetryWordNum = 3;
                EepReadControl.uEepRetryByte = pMsgContext->resDataLen;
                DescStartRepeatedServiceCall(&CAN_EEP_RereadHandler);
                return;
            }
		}
		SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
	}
	else
	{
		SendDiagResponse(E_NEGATIVE_DIAG_RESPONSE);
	}
}

void ApplDescReadDidProgramming_Date_AddOn(DescMsgContext* pMsgContext) 	 //DES_22_F199_READ_PROGRAMMING_DATA,
{
	U8 arg[4]={0};
	U8 arg_nowrite[4]={0};
	U8 invalue_arg[4] = {0xFF,0xFF,0xFF,0xFF};
	U8 RET;
	if(FALSE == can_diag_svc_negative_response_check(DES_22_F199_READ_PROGRAMMING_DATA, pMsgContext))
	{  
		pMsgContext->resDataLen = 4;
		RET = FDdriver_BlackCheck(F199_STORE_ADDRESS, 1);
		if(RET == TRUE)
		{
			/* not written */
			_memcpy(pMsgContext->resData, arg_nowrite, pMsgContext->resDataLen);
		}
		else
		{
			/* is written */
			RET = FDLDriver_Read(F199_STORE_ADDRESS,arg, 1);
			_memcpy(pMsgContext->resData, arg, pMsgContext->resDataLen);
			if(0 == RET)
            {
                /* Read Error, need retry! */
                EepReadControl.uEepRetryAddr = F199_STORE_ADDRESS;
                EepReadControl.uEepRetryWordNum = 1;
                EepReadControl.uEepRetryByte = pMsgContext->resDataLen;
                DescStartRepeatedServiceCall(&CAN_EEP_RereadHandler);
                return;
            }
			else
			{
				if(_memcmp(invalue_arg, arg,4))
				{
					_memcpy(pMsgContext->resData, arg, pMsgContext->resDataLen);
				}
				else
				{
					_memcpy(pMsgContext->resData, arg_nowrite, pMsgContext->resDataLen);
				}
			}
		}
		SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
	}
	else
	{
		SendDiagResponse(E_NEGATIVE_DIAG_RESPONSE);
	}
}

void ApplDescReadDidECU_Installation_Date_AddOn(DescMsgContext* pMsgContext)	 //DES_22_F19D_READ_ECU_INSTALLATION_DATA,
{
	U8 arg[4]={0};
	U8 arg_nowrite[4]={0};
	U8 invalue_arg[4] = {0xFF,0xFF,0xFF,0xFF};
	U8 RET;
	if(FALSE == can_diag_svc_negative_response_check(DES_22_F19D_READ_ECU_INSTALLATION_DATA, pMsgContext))
	{  
		pMsgContext->resDataLen = 4;
		RET = FDdriver_BlackCheck(F19D_STORE_ADDRESS, 1);
		if(RET == TRUE)
		{
			/* not written */
			_memcpy(pMsgContext->resData, arg_nowrite, pMsgContext->resDataLen);
		}
		else
		{
			/* is written */
			RET = FDLDriver_Read(F19D_STORE_ADDRESS,arg, 1);
			_memcpy(pMsgContext->resData, arg, pMsgContext->resDataLen);
			if(0 == RET)
            {
                /* Read Error, need retry! */
                EepReadControl.uEepRetryAddr = F19D_STORE_ADDRESS;
                EepReadControl.uEepRetryWordNum = 1;
                EepReadControl.uEepRetryByte = pMsgContext->resDataLen;
                DescStartRepeatedServiceCall(&CAN_EEP_RereadHandler);
                return;
            }
			else
			{
				if(_memcmp(invalue_arg, arg,4))
				{
					_memcpy(pMsgContext->resData, arg, pMsgContext->resDataLen);
				}
				else
				{
					_memcpy(pMsgContext->resData, arg_nowrite, pMsgContext->resDataLen);
				}
			}
		}
		SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
	}
	else
	{
		SendDiagResponse(E_NEGATIVE_DIAG_RESPONSE);
	}
}

void ApplDescReadDidFAW_Reserved_AddOn(DescMsgContext* pMsgContext) 	 //DES_22_F1A0_READ_FAW_RESERVED,
{
	U8 arg[20]={0};
	U8 arg_nowrite[20]={0};
	U8 RET;
	if(FALSE == can_diag_svc_negative_response_check(DES_22_F1A0_READ_FAW_RESERVED, pMsgContext))
	{ 
		pMsgContext->resDataLen = 16;
		RET = FDdriver_BlackCheck(F1A0_STORE_ADDRESS, 5);
		if(RET == TRUE)
		{
			/* not written */
			_memcpy(pMsgContext->resData, arg_nowrite, pMsgContext->resDataLen);
		}
		else
		{
			/* is written */
			RET = FDLDriver_Read(F1A0_STORE_ADDRESS,arg, 5);
			_memcpy(pMsgContext->resData, arg, pMsgContext->resDataLen);
			if(0 == RET)
            {
                /* Read Error, need retry! */
                EepReadControl.uEepRetryAddr = F1A0_STORE_ADDRESS;
                EepReadControl.uEepRetryWordNum = 5;
                EepReadControl.uEepRetryByte = pMsgContext->resDataLen;
                DescStartRepeatedServiceCall(&CAN_EEP_RereadHandler);
                return;
            }
		}
		SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
	}
	else
	{
		SendDiagResponse(E_NEGATIVE_DIAG_RESPONSE);
	}
}

void ApplDescReadDidSystem_Configuration_1_AddOn(DescMsgContext* pMsgContext)	 //DES_22_F1A1_READ_SYSTEM_CONFIGURATION_1,
{
	U8 arg[20]={0};
	U8 arg_nowrite[20]={0};
	U8 RET;
	if(FALSE == can_diag_svc_negative_response_check(DES_22_F1A1_READ_SYSTEM_CONFIGURATION_1, pMsgContext))
	{  
		pMsgContext->resDataLen = 4;

		RET = FDdriver_BlackCheck(F1A1_STORE_ADDRESS, 5);
		if(RET == TRUE)
		{
			/* not written */
			_memcpy(pMsgContext->resData, arg_nowrite, pMsgContext->resDataLen);
		}
		else
		{
			/* is written */
			RET = FDLDriver_Read(F1A1_STORE_ADDRESS,arg, 5);
			_memcpy(pMsgContext->resData, arg, pMsgContext->resDataLen);
			if(0 == RET)
            {
                /* Read Error, need retry! */
                EepReadControl.uEepRetryAddr = F1A1_STORE_ADDRESS;
                EepReadControl.uEepRetryWordNum = 5;
                EepReadControl.uEepRetryByte = pMsgContext->resDataLen;
                DescStartRepeatedServiceCall(&CAN_EEP_RereadHandler);
                return;
            }
		}
		SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
	}
	else
	{
		SendDiagResponse(E_NEGATIVE_DIAG_RESPONSE);
	}
}

void ApplDescReadDidFAW_Reserved1_AddOn(DescMsgContext* pMsgContext)	 //DES_22_F1A7_READ_FAW_RESERVED_1,
{
	U8 arg[20]={0};
	U8 arg_nowrite[20]={0};
	U8 RET;
	if(FALSE == can_diag_svc_negative_response_check(DES_22_F1A7_READ_FAW_RESERVED_1, pMsgContext))
	{  
		pMsgContext->resDataLen = 16;
		RET = FDdriver_BlackCheck(F1A7_STORE_ADDRESS, 5);
		if(RET == TRUE)
		{
			/* not written */
			_memcpy(pMsgContext->resData, arg_nowrite, pMsgContext->resDataLen);
		}
		else
		{
			/* is written */
			RET = FDLDriver_Read(F1A7_STORE_ADDRESS,arg, 5);
			_memcpy(pMsgContext->resData, arg, pMsgContext->resDataLen);
			if(0 == RET)
            {
                /* Read Error, need retry! */
                EepReadControl.uEepRetryAddr = F1A7_STORE_ADDRESS;
                EepReadControl.uEepRetryWordNum = 5;
                EepReadControl.uEepRetryByte = pMsgContext->resDataLen;
                DescStartRepeatedServiceCall(&CAN_EEP_RereadHandler);
                return;
            }
		}
		SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
	}
	else
	{
		SendDiagResponse(E_NEGATIVE_DIAG_RESPONSE);
	}
}

void ApplDescReadDidAVS_Calibration_Status_AddOn(DescMsgContext* pMsgContext)	 //DES_22_2B00_READ_AVSCARMODELCOLOR,
{
	if(FALSE == can_diag_svc_negative_response_check(DES_22_2B00_READ_DidAVS_Calibration_Status, pMsgContext))
	{  
		pMsgContext->resDataLen = 1;
		//pMsgContext->resData[0] = uAVSCalibrationSta;
		pMsgContext->resData[0] = EED_Calibration;
	 }
	SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
}

void ApplDescReadDidAVS_View_change_status_AddOn(DescMsgContext* pMsgContext)	 //DES_22_2B10_READ_DidAVS_View_change_status
{
	if(FALSE == can_diag_svc_negative_response_check(DES_22_2B10_READ_DidAVS_View_change_status, pMsgContext))
	{  
		pMsgContext->resDataLen = 1;
		pMsgContext->resData[0] = uAVSViewMode;
	 }
	SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
}

void ApplDescReadDidVehicleSpeed_Value__AddOn(DescMsgContext* pMsgContext)//DES_22_0100_READ_DidVehicleSpeedValue
{
	if(FALSE == can_diag_svc_negative_response_check(DES_22_0100_READ_DidVehicleSpeedValue, pMsgContext))
	{  
		pMsgContext->resDataLen = 2;
		pMsgContext->resData[0] = Can_Signal_Snapshot_Data.Snapshot0100_VehicleSpeed>>8;
		pMsgContext->resData[1] = Can_Signal_Snapshot_Data.Snapshot0100_VehicleSpeed&0xFF;
	 }
	SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
}

void ApplDescReadDidOdometer_Value__AddOn(DescMsgContext* pMsgContext)  //DES_22_0101_READ_DidOdometerValue
{
	if(FALSE == can_diag_svc_negative_response_check(DES_22_0101_READ_DidOdometerValue, pMsgContext))
	{  
		pMsgContext->resDataLen = 4;
		pMsgContext->resData[0] = (Can_Signal_Snapshot_Data.Snapshot0101_Odometer >> 24)& 0x000000FF;
		pMsgContext->resData[1] = (Can_Signal_Snapshot_Data.Snapshot0101_Odometer >> 16)& 0x000000FF;
		pMsgContext->resData[2] = (Can_Signal_Snapshot_Data.Snapshot0101_Odometer >> 8)& 0x000000FF;
		pMsgContext->resData[3] = Can_Signal_Snapshot_Data.Snapshot0101_Odometer & 0x000000FF;
	 }
	SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
}

void ApplDescReadDidSupplyVoltage_Value__AddOn(DescMsgContext* pMsgContext)  //DES_22_0102_READ_DidSupplyVoltageValue
{
	U16 PWrVALUE = 0;
	float f_PWrVALUE = 0;
	CS_SIG_AsyncReceive(SIG_APP_PWR,&PWrVALUE);
	f_PWrVALUE = PWrVALUE*12/212.00;
	Can_Signal_Snapshot_Data.Snapshot0102_SupplyVoltage = (U8)f_PWrVALUE;

	if(FALSE == can_diag_svc_negative_response_check(DES_22_0102_READ_DidSupplyVoltageValue, pMsgContext))
	{  
		pMsgContext->resDataLen = 1;
		pMsgContext->resData[0] = Can_Signal_Snapshot_Data.Snapshot0102_SupplyVoltage & 0xFF;
	 }
	SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
}

/////////////////////////////$2E////////////////////////////////////
void ApplDescWriteDidFAW_Vehicle_Identification_Number_AddOn(DescMsgContext* pMsgContext)		 //DES_22_F190_WRITE_FAW_VECHICLE_ID_NUMBER,
{
	U8 RET = ERR_FAULT;
	U8 i;
	U8 arg[20] = {0};
	if(FALSE == can_diag_svc_negative_response_check(DES_22_F190_WRITE_FAW_VECHICLE_ID_NUMBER, pMsgContext))
	{  
		for(i=0;i<17;i++)
		{
			arg[i] = pMsgContext->reqData[i];
		}
		RET = FDLDriver_Write(F190_STORE_ADDRESS,arg,5);
        if(ERR_OK != RET)
        {
            /* Write Error, need retry! */
            EepWriteControl.uEepRetryAddr = F190_STORE_ADDRESS;
            EepWriteControl.uEepRetryWordNum = 5;
            EepWriteControl.uEepRetryByte = 17;
            DescStartRepeatedServiceCall(&CAN_EEP_RewriteHandler);
        }	
		else
        {
            SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
        }
	}
    else
    {
        SendDiagResponse(E_NEGATIVE_DIAG_RESPONSE);
    }	
}

void ApplDescWriteDidRepair_Shop_Code_and_or_Tester_Serial_Number_AddOn(DescMsgContext* pMsgContext)	 //DES_22_F198_WRITE_REPAIR_SHOP_CODE_AND_OR_TESTER_SERIAL_NUMBER,
{
	U8 RET = ERR_FAULT;
	U8 i;
	U8 arg[16] = {0};
	if(FALSE == can_diag_svc_negative_response_check(DES_22_F198_WRITE_REPAIR_SHOP_CODE_AND_OR_TESTER_SERIAL_NUMBER, pMsgContext))
	{   
		for(i=0;i<10;i++)
		{
			arg[i] = pMsgContext->reqData[i];
		}
		RET = FDLDriver_Write(F198_STORE_ADDRESS,arg,4);
        if(ERR_OK != RET)
        {
            /* Write Error, need retry! */
            EepWriteControl.uEepRetryAddr = F198_STORE_ADDRESS;
            EepWriteControl.uEepRetryWordNum = 4;
            EepWriteControl.uEepRetryByte = 10;
            DescStartRepeatedServiceCall(&CAN_EEP_RewriteHandler);
        }	
		else
        {
            SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
        }		
	}
    else
    {
        SendDiagResponse(E_NEGATIVE_DIAG_RESPONSE);
    }
}

void ApplDescWriteDidProgramming_Date_AddOn(DescMsgContext* pMsgContext)	 //DES_22_F199_WRITE_PROGRAMMING_DATA,
{
	U8 RET = ERR_FAULT;
	U8 i;
	U8 arg[4] = {0};
	if(FALSE == can_diag_svc_negative_response_check(DES_22_F199_WRITE_PROGRAMMING_DATA, pMsgContext))
	{  
		for(i=0;i<4;i++)
		{
			arg[i] = pMsgContext->reqData[i];
		}
		RET = FDLDriver_Write(F199_STORE_ADDRESS,arg,1);
        if(ERR_OK != RET)
        {
            /* Write Error, need retry! */
            EepWriteControl.uEepRetryAddr = F199_STORE_ADDRESS;
            EepWriteControl.uEepRetryWordNum = 1;
            EepWriteControl.uEepRetryByte = 4;
            DescStartRepeatedServiceCall(&CAN_EEP_RewriteHandler);
        }	
		else
        {
            SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
        }		
	}
    else
    {
        SendDiagResponse(E_NEGATIVE_DIAG_RESPONSE);
    }
}

void ApplDescWriteDidECU_Installation_Date_AddOn(DescMsgContext* pMsgContext)		 //DES_22_F19D_WRITE_ECU_INSTALLATION_DATA,
{
	U8 RET = ERR_FAULT;
	U8 i;
	U8 arg[4] = {0};
	if(FALSE == can_diag_svc_negative_response_check(DES_22_F19D_WRITE_ECU_INSTALLATION_DATA, pMsgContext))
	{  	 
		for(i=0;i<4;i++)
		{
			arg[i] = pMsgContext->reqData[i];
		}
		RET = FDLDriver_Write(F19D_STORE_ADDRESS,arg,1);
		if(ERR_OK != RET)
        {
            /* Write Error, need retry! */
            EepWriteControl.uEepRetryAddr = F19D_STORE_ADDRESS;
            EepWriteControl.uEepRetryWordNum = 1;
            EepWriteControl.uEepRetryByte = 4;
            DescStartRepeatedServiceCall(&CAN_EEP_RewriteHandler);
        }	
		else
        {
            SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
        }
	}
    else
    {
        SendDiagResponse(E_NEGATIVE_DIAG_RESPONSE);
    }
}

void ApplDescWriteDidFAW_Reserved_AddOn(DescMsgContext* pMsgContext)	 //DES_22_F1A0_WRITE_FAW_RESERVED,
{
	U8 RET = ERR_FAULT;
	U8 i;
	U8 arg[20] = {0};
	if(FALSE == can_diag_svc_negative_response_check(DES_22_F1A0_WRITE_FAW_RESERVED, pMsgContext))
	{   
		for(i=0;i<16;i++)
		{
			arg[i] = pMsgContext->reqData[i];
		}
		RET = FDLDriver_Write(F1A0_STORE_ADDRESS,arg,5);
		if(ERR_OK != RET)
        {
            /* Write Error, need retry! */
            EepWriteControl.uEepRetryAddr = F1A0_STORE_ADDRESS;
            EepWriteControl.uEepRetryWordNum = 5;
            EepWriteControl.uEepRetryByte = 16;
            DescStartRepeatedServiceCall(&CAN_EEP_RewriteHandler);
        }	
		else
        {
            SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
        }		
	}
    else
    {
        SendDiagResponse(E_NEGATIVE_DIAG_RESPONSE);
    }
}

void ApplDescWriteDidSystem_Configuration_1_AddOn(DescMsgContext* pMsgContext)		 //DES_22_F1A1_WRITE_SYSTEM_CONFIGURATION_1,
{
	U8 RET = ERR_FAULT;
	U8 i;
	U8 arg[20] = {0};
	if(FALSE == can_diag_svc_negative_response_check(DES_22_F1A1_WRITE_SYSTEM_CONFIGURATION_1, pMsgContext))
	{  
		for(i=0;i<4;i++)
		{
			arg[i] = pMsgContext->reqData[i];
		}
		RET = FDLDriver_Write(F1A1_STORE_ADDRESS,arg,5);
		if(ERR_OK != RET)
        {
            /* Write Error, need retry! */
            EepWriteControl.uEepRetryAddr = F1A1_STORE_ADDRESS;
            EepWriteControl.uEepRetryWordNum = 5;
            EepWriteControl.uEepRetryByte = 4;
            DescStartRepeatedServiceCall(&CAN_EEP_RewriteHandler);
        }	
		else
        {
            SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
        }	
	}
    else
    {
        SendDiagResponse(E_NEGATIVE_DIAG_RESPONSE);
    }

}

void ApplDescWriteDidFAW_Reserved1_AddOn(DescMsgContext* pMsgContext)		 //DES_22_F1A7_WRITE_FAW_RESERVED_1,
{
	U8 RET = ERR_FAULT;
	U8 i;
	U8 arg[20] = {0};
	if(FALSE == can_diag_svc_negative_response_check(DES_22_F1A7_WRITE_FAW_RESERVED_1, pMsgContext))
	{   
		for(i=0;i<16;i++)
		{
			arg[i] = pMsgContext->reqData[i];
		}
		RET = FDLDriver_Write(F1A7_STORE_ADDRESS,arg,5);
		if(ERR_OK != RET)
        {
            /* Write Error, need retry! */
            EepWriteControl.uEepRetryAddr = F1A7_STORE_ADDRESS;
            EepWriteControl.uEepRetryWordNum = 5;
            EepWriteControl.uEepRetryByte = 16;
            DescStartRepeatedServiceCall(&CAN_EEP_RewriteHandler);
        }	
		else
        {
            SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
        }			
	}
    else
    {
        SendDiagResponse(E_NEGATIVE_DIAG_RESPONSE);
    }
}

/////////////////////////////$2F////////////////////////////////////

void ApplDescReturnControlToECU_AVSView_AddOn(DescMsgContext* pMsgContext)
{
	if(FALSE == can_diag_svc_negative_response_check(DESC_2F_C0C0_00_ControlToECU_AVS_VIEW_CHANGE, pMsgContext))
	{  
		IoControl.bReqSent = TRUE;
		IoControl.bControlParameterType = RETURNCONTROL_TYPE;
		IoControl.bControlType  = VIEW_CONTROL;
		IoControl.bControlState	= 0x02;
		IoControl.uRecvDatatime = 0;
		IoControl.bBeenSend = TRUE;
		DescStartRepeatedServiceCall(&CAN_Navi_Response);
	}
	else
	{
		SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
	}
}

void ApplDescControl_AVSView_AddOn(DescMsgContext* pMsgContext)
{
	if(FALSE == can_diag_svc_negative_response_check(DESC_2F_C0C0_03_CONTROL_AVS_VIEW_CHANGE, pMsgContext))
	{
		IoControl.bReqSent = TRUE;
		IoControl.bControlParameterType = CONTROL_TYPE;
		IoControl.bControlType  = VIEW_CONTROL;
		IoControl.bControlState	= pMsgContext->reqData[0];
		IoControl.uRecvDatatime = 0;
		IoControl.bBeenSend = TRUE;
		DescStartRepeatedServiceCall(&CAN_Navi_Response);
	}
	else
	{
		SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
	}
}

/*************************************************31******************************************/
void ApplDescStartEnterEOLView_AddOn(DescMsgContext* pMsgContext)
{
	U8 mStartEnterEOLView = 0;
	U8 EOLView_default = 0x0;
	if(FALSE == can_diag_svc_negative_response_check(DESC_3101_E100_START_ENTER_EOL_VIEW, pMsgContext))
	 {	

	 	EED_LockDataBlock(EED_nEOLConfig);
		EED_EnterEOLView = EOLView_default; 
		EED_UnlockAndSavDataBlock(EED_nEOLConfig); 


	 	SocManager_SendMsg(LQ_CMD,TYPE_EVENT, MCU_Send_EOL_Line_View_To_APP,1,mStartEnterEOLView);


		SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);

 	 }
	else
	{
		SendDiagResponse(E_NEGATIVE_DIAG_RESPONSE);
	}

}


void ApplDescResultStartEnterEOLView_AddOn(DescMsgContext* pMsgContext)
{
	if(FALSE == can_diag_svc_negative_response_check(DESC_3103_E100_REQUEST_ROUTINE_RESULT_ENTER_EOL_VIEW, pMsgContext))
	{  
		pMsgContext->resDataLen = 2;
		pMsgContext->resData[0]  = (SEnterEOLViewResult == 0x01)? 1 : 0;
		pMsgContext->resData[1]  = (SEnterEOLViewResult == 0x01)? 1 : 0;
		SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);

	}
	else
	{
		SendDiagResponse(E_NEGATIVE_DIAG_RESPONSE);
	}

}

void ApplDescStartCalibration_AddOn(DescMsgContext* pMsgContext)
{
	U8 mStartEnterCalibration = 0;
	U8 Calibration_default = 0x1;
	if(FALSE == can_diag_svc_negative_response_check(DESC_3101_E101_START_CALIBRATION, pMsgContext))
	 {	

	 	EED_LockDataBlock(EED_nEOLConfig);
		EED_Calibration = Calibration_default; //recalibration :clear data
		EED_UnlockAndSavDataBlock(EED_nEOLConfig); //clear the calibration data of last time


	 	SocManager_SendMsg(LQ_CMD,TYPE_EVENT, RADIO_NOTIFY_START_OFFLINE_CALIBRATION,1,mStartEnterCalibration);


		SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);

 	 }
	else
	{
		SendDiagResponse(E_NEGATIVE_DIAG_RESPONSE);
	}

}


void ApplDescResultStartCalibration_AddOn(DescMsgContext* pMsgContext)
{
	if(FALSE == can_diag_svc_negative_response_check(DESC_3103_E101_REQUEST_ROUTINE_RESULT_START_CALIBRATION, pMsgContext))
	{  
		pMsgContext->resDataLen = 2;
		pMsgContext->resData[0]  = (SCalibrationResult == 0x01)? 1 : 0;
		pMsgContext->resData[1]  = SCalibrationResult;
	 }
	SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);

}


void DiagRequest_Navi_handler(void)
{
	U8 arg[8] = {0};
	if(bJ6_start_complete == TRUE)
	{
		switch(IoControl.bControlType)
		{
			case VIEW_CONTROL:
				if(IoControl.bBeenSend)
				{
					arg[0] = IoControl.bControlState;
					SocManager_SendMsg(TX_HQ,TYPE_EVENT, RADIO_NOTIFY_VIEW_MODE_ANGLE, 1, arg);
					IoControl.bBeenSend = FALSE;
				}
			break;
			case DYNAMICPGS_CONTROL:
			{
				if(IoControl.bBeenSend)
				{
					arg[2] = IoControl.bControlState;
					SocManager_SendMsg(TX_HQ,TYPE_EVENT, RADIO_NOTIFY_SET_STATUS, 3, arg);
					IoControl.bBeenSend = FALSE;
				}
			}break;
			default:
        	break;
		}
	}

}

static void CAN_Navi_Response(DescMsgContext* pMsgContext)
{
	int VersionCopyCounter = 0;
	if(IoControl.bReqSent == TRUE)
	{
		if(IoControl.uRecvDatatime++ > DIAG_WAIT_J6_RESP_TIME)
		{
			DescSetNegResponse(kDescNrcConditionsNotCorrect);
			DescProcessingDone();
			_memset(&IoControl,0,sizeof(E_IO_CONTROL_STRUCT));
			return;
		}
		if(IoControl.bRespReceived == TRUE)
		{
			if(IoControl.bControlType == IoControl.bRespControlType)
			{
				IoControl.uRecvDatatime = 0;
				if(IoControl.bControlParameterType == CONTROL_TYPE)
				{
					pMsgContext->resDataLen = 1;
					pMsgContext->resData[0] = IoControl.bRespControlState;
				}				
				SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
				_memset(&IoControl,0,sizeof(E_IO_CONTROL_STRUCT));
			}
		}
	}	
	if(J6VersionData.bReqSent == TRUE)
	{
		if(J6VersionData.uRecvDatatime++ > DIAG_WAIT_J6_RESP_TIME)
		{
			if(J6VersionData.uReqNumber == 0)
			{
				DescSetNegResponse(kDescNrcConditionsNotCorrect);
				DescProcessingDone();
				_memset(&J6VersionData,0,sizeof(E_QUERY_J6_VERSION_STRUCT));
				return;
			}
			else
			{
				J6VersionData.uReqNumber--;
				J6VersionData.bReqSent = TRUE;
				J6VersionData.uReqVersionType = 0x03;
				J6VersionData.uRecvDatatime = 0;
				J6VersionData.bRespReceived = TRUE; 
				Request_J6Version =TRUE;
			}
		}
		if(J6VersionData.bRespReceived == TRUE)
		{
			if(J6VersionData.uReqVersionType == J6VersionData.uRespVersionType)
			{
				J6VersionData.uRecvDatatime = 0;
				
				//pMsgContext->resDataLen = J6VersionData.uRecvDatalen;
				if(J6VersionData.uSoftwareVersionType == FAW_ECU_SOFT_TYPE)
				{
					pMsgContext->resDataLen = 16;
				}
				else if(J6VersionData.uSoftwareVersionType == SUPPLIER_ECU_SOFT)
				{
					pMsgContext->resDataLen = 16;
				}
				for(VersionCopyCounter = 0; VersionCopyCounter < J6VersionData.uRecvDatalen;VersionCopyCounter++)
				{
					pMsgContext->resData[VersionCopyCounter] = J6VersionData.uRecvData[VersionCopyCounter];
				}	
				for(VersionCopyCounter = (J6VersionData.uRecvDatalen-1); VersionCopyCounter < pMsgContext->resDataLen;VersionCopyCounter++)
				{
					pMsgContext->resData[VersionCopyCounter] = 0x00;
				}
				SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
				_memset(&J6VersionData,0,sizeof(E_QUERY_J6_VERSION_STRUCT));
			}
		}	
		}
}

void CanDiag_recvnavimsg_handler(U16 commandid, U8* data)
{
	int VersionCopyCounter = 0;
	if(IoControl.bReqSent == TRUE)
	{
		switch (commandid)
		{
			case CPU_NOTIFY_M3_AVM_SETTING_RESULT:
				IoControl.bRespReceived = TRUE;
				IoControl.bRespControlType = DYNAMICPGS_CONTROL;
				IoControl.bRespControlState = data[2];
			break;	
					
			case CPU_NOTIFY_M3_AVM_DISPLAY_VIEWSTSRSP:
				IoControl.bRespReceived = TRUE;
				IoControl.bRespControlType = VIEW_CONTROL;
				IoControl.bRespControlState = data[0];
			break;
			default:break;
				
		}
	}
	switch(commandid)
	{
		case J6_SEND_RESPONSE_OF_VERSION:
			J6VersionData.bRespReceived = TRUE;
			J6VersionData.uRespVersionType = data[0];
			J6VersionData.uRecvDatalen = data[1];
			for(VersionCopyCounter = 0; VersionCopyCounter < data[1]; VersionCopyCounter++)
			{
				J6VersionData.uRecvData[VersionCopyCounter] = data[VersionCopyCounter + 2];
			}
		break;
		default:
		break;
	}
}

void Request_J6Version_handler()
{
   if((Request_J6Version)&&(bJ6_start_complete))
   {
		SocManager_SendMsg(TX_HQ,TYPE_EVENT, RADIO_QUERY_ENG_SW_VERSION, 1, &J6VersionData.uReqVersionType);
		Request_J6Version = FALSE;
   }
}

void CAN_EEP_RewriteHandler(DescMsgContext* pMsgContext)
{
    static U8 write_counter = 0;
    static U8 write_timer = 0;
    U8 i = 0;
    U8 ret = ERR_FAULT;

    /* The max retry times are 5 */
    if((write_counter < 5)&&
    (EEP_INVALID_ADDRESS != EepWriteControl.uEepRetryAddr)&&(EEP_INVALID_LENGTH != EepWriteControl.uEepRetryWordNum))
    {
        /* retry per 50ms */
        if(write_timer >= 4)
        {
            if(0 == write_counter)
            {
                /* Get data */
                for(i=0; i<EepWriteControl.uEepRetryByte; i++)
                {
                    u8_write_arg[i] = pMsgContext->reqData[i];
                }
            }
            write_timer = 0;
            write_counter++;
            /* write data */
            ret = FDLDriver_Write(EepWriteControl.uEepRetryAddr, u8_write_arg, EepWriteControl.uEepRetryWordNum);
            if(ERR_OK == ret)
            {
                /* write successfully */
                SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
                write_counter = 0;
                write_timer = 0;
                /* End */
            }
            else
            {
                /* write failed */
            }
        }
        else
        {
            write_timer++;
        }
    }
    else
    {
        /* write failed in 5 times */
		DescSetNegResponse(kDescNrcGeneralProgrammingFailure);
        DescProcessingDone();
        write_counter = 0;
        write_timer = 0;
        /* End */
    }
}

void CAN_EEP_RereadHandler(DescMsgContext* pMsgContext)
{
    static U8 read_counter = 0;
    static U8 read_timer = 0;
    U8 i = 0;
    U8 rlen = 0;

    /* The max retry times are 5 */
    if((read_counter < 5)&&
    (EEP_INVALID_ADDRESS != EepReadControl.uEepRetryAddr)&&(EEP_INVALID_LENGTH != EepReadControl.uEepRetryWordNum))
    {
        /* retry per 50ms */
        if(read_timer >= 4)
        {
            read_timer = 0;
            read_counter++;
            /* read data */
            rlen = FDLDriver_Read(EepReadControl.uEepRetryAddr, u8_read_arg, EepReadControl.uEepRetryWordNum);
            if(0 != rlen)
            {
                /* read successfully */
                pMsgContext->resDataLen = EepReadControl.uEepRetryByte;
                _memcpy(pMsgContext->resData, u8_read_arg, pMsgContext->resDataLen);
                SendDiagResponse(E_POSITIVE_DIAG_RESPONSE);
                read_counter = 0;
                read_timer = 0;
                /* End */
            }
            else
            {
                /* read failed */
            }
        }
        else
        {
            read_timer++;
        }
    }
    else
    {
        /* write failed in 5 times */
		DescSetNegResponse(kDescNrcConditionsNotCorrect);
        DescProcessingDone();
        read_counter = 0;
        read_timer = 0;
        /* End */
    }
}


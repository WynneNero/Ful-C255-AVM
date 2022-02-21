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
*=====================================================================*/
#include "config.h"
#ifdef CAN_BUS_OPTION
#ifdef CAN_DIAG_OPTION
#include "candiagdtc.h"
//#include "EEPDriver_IF.h"
#include "EEP_DtcData.h"
#include "canDiagDtcCfg.h"
#include "Sig_Combine.H"
#include "Signal_if.h"  
#include "Cansig_cfg_if.h"
//#include "Dtc.h"
#include "desc.h"
#include "il_inc.h"
#include "can_par.h"
#include "can_cfg.h"
#include "can_def.h"
#include "CONFIG.H"
#include "TYPES.H"

#include "EEPTable.h"
#include "EEP_EOLconfig.h"
#include "Dtc.h"

#include "CanDiagService.h"
#include "CanApp.h"
#include "Can_App_il.h"

#include "CanManager.h"

/*---Private----------------------------------------------------------*/
static BOOL dtc_control_setting_on_off = TRUE;
static U8 dtc_record_enable_mask = DTC_RECORD_ENABLE_NONE;
static U8 can_diag_dtc_task_counter = 0;

static DTC_INIT_STEP_TYPE dtc_eeprom_init_step = DTC_INIT_STEP_START;
static U8 dtc_status_svc14_clear_counter = DTC_STATUS_SVC14_CLEAR_FINISHED;
U16 can_diag_init_delay_timer;
U16 can_diag_init_nm_delay_timer;
U16 can_diag_bat_volt_recover_delay_timer;
U16 can_diag_bdy_bat_volt_recover_delay_timer;

E_SYSTEM_VOLTAGE_STATUS sPower_Can;
E_SYSTEM_VOLTAGE_STATUS sPower_CanPre;
U16 can_diag_ign_delay_timer;
BOOL bBatteryOn = FALSE;
BOOL bWakeupOn = FALSE;
BOOL bAccOn;
BOOL bAccOnPreStatus;
U16 desc_delay_sig;
BOOL bDtcDataNeedSendToEep = FALSE;
BOOL bDtcFirstFrameDataNeedSendToEep = FALSE;
#define USE_AD_CHECK_POWER
#ifdef USE_AD_CHECK_POWER
U8 powerOverCnt;
U8 powerDownCnt;
U8 powerNormalCnt;
void PowerDetInit(void);
 void PowerDetAD(void);
#endif

extern BOOL hw_accon_flag;

#ifndef NOT_DIAG_SYS_POWER
static void can_diag_dtc_bat_volt_monitor(void);
#endif
static void can_diag_dtc_status_report(U8 dtc_code, U16 dtc_status_mask, BOOL write_delay);
static BOOL can_diag_dtc_proc_test_failed(U8 dtc_code, U16 dtc_status_mask);
static BOOL can_diag_dtc_proc_test_failed_operation(U8 dtc_code, U16 dtc_status_mask);
static BOOL can_diag_dtc_proc_pending_DTC(U8 dtc_code, U16 dtc_status_mask);
static BOOL can_diag_dtc_proc_confirmed_DTC(U8 dtc_code, U16 dtc_status_mask);
static BOOL can_diag_dtc_proc_test_not_completed_since_clear(U8 dtc_code, U16 dtc_status_mask);
static BOOL can_diag_dtc_proc_test_failed_since_clear(U8 dtc_code, U16 dtc_status_mask);
static BOOL can_diag_dtc_proc_not_completed_operation(U8 dtc_code, U16 dtc_status_mask);
static BOOL can_diag_dtc_proc_warning_indicator_requested(U8 dtc_code, U16 dtc_status_mask);
#ifndef NOT_DIAG_CAN_BUSOFF
static void can_diag_dtc_bus_off_monitor(void);
#endif
static BOOL can_diag_dtc_record_nm_enable_check(void);
static BOOL can_diag_dtc_record_body_enable_check(void);
static BOOL can_diag_dtc_record_op_volt_enable_check(void);
static BOOL can_diag_control_dtc_setting_check(void);
static void can_diag_dtc_nm_lost_node_monitor(void);
static void can_diag_dtc_GW_node_lost_monitor();
static void can_diag_dtc_HU_message_lost_monitor();
static void can_diag_dtc_ESP_node_lost_monitor();
static void can_diag_dtc_BCM1_node_lost_monitor();
static void can_diag_dtc_HCU_node_lost_monitor();
// static void can_diag_dtc_PDC_node_lost_monitor();
static BOOL SYS_control_dtc_setting_check(void);
static void can_diag_dtc_device_err_monitor(void);
static void can_diag_bdy_dtc_volt_handle(void);
#ifdef DIAG_TEMPERATURE_OPTION
static void can_diag_dtc_temp_err_monitor(void);
#endif
#ifndef NOT_DIAG_CAN_TRANSCRIVER
static void can_diag_dtc_transceiver_err_monitor(void);
#endif
#ifdef DIAG_INNER_COMMUNICATION
static void can_diag_dtc_inner_communication_monitor(void);
#endif
#ifdef DIAG_AVM_ONOFF_SWITCH
static void can_diag_dtc_avm_onoff_key_monitor(void);
#endif

#ifdef DIAG_LED_INDICATOR
static void can_diag_avm_indicator_light_monitor(void);
#endif

#ifdef DIAG_AVM_CALIBRATION
static void can_diag_dtc_avm_calibration_monitor(void);
#endif

#ifdef CANDTC_DIAG_DVR_STATUS
static void can_diag_dtc_dvr_err_monitor(void);
#endif

#ifdef DIAG_NM_TIMEOUT_NOT_USE_IL_TIMEOUT_FLAG
BOOL CanDiag_GetNMTimeOutFlag(U8 nodeindex);
BOOL CanDiag_GetGWNodeLostFlag(void);
BOOL CanDiag_GetESPMessageLostFlag(void);
BOOL CanDiag_GetBCM1MessageLostFlag(void);
BOOL CanDiag_GetHCUMessageLostFlag(void);
// BOOL CanDiag_GetPDCMessageLostFlag(void);
BOOL CanDiag_GetHUMessageLostFlag(void);

void ResetCanDiagTimeoutState(void);
void CanDiag_NmTimeout_monitor_handler(void);
void CanDiag_GWNodeLost_monitor_handler(void);
void CanDiag_EPSMessageLost_monitor_handler(void);
void CanDiag_BCM1MessageLost_monitor_handler(void);
void CanDiag_HCUMessageLost_monitor_handler(void);
// void CanDiag_PDCMessageLost_monitor_handler(void);
void CanDiag_HUMessageLost_monitor_handler(void);
void can_diag_dtc_ESP_content_error_monitor();
void can_diag_dtc_ESP_signal_invalid_monitor();
void can_diag_dtc_EPS_content_error_monitor();
void can_diag_dtc_EPS_checksum_error_monitor();
void can_diag_dtc_ESP_checksum_error_monitor();
void can_diag_dtc_EPS_signal_invalid_monitor();
static void can_diag_dtc_GW_node_lost_fid_record(void);
static void can_diag_HU_node_lost_fid_record(void);
static void can_diag_ESP_node_lost_fid_record(void);
static void can_diag_record_fid_to_DTC(U8 dtc_code);
static void can_diag_ESP_signal_invalid_fid_record(void);
static void can_diag_ESP_content_error_fid_record(void);
static void can_diag_EPS_checksum_error_fid_record(void);

#endif
#ifdef CANDTC_DIAG_LIMPHOME
static void can_diag_dtc_limphome_monitor(void);
#endif
void WriteAllDtcToEEP(void);
void ReadDtcFromEEP(void);
/* consecutive bus off counter */
static U8 dtc_bus_off_counter = 0;
BOOL bWaitEEPwriteResp;
U16 uWaitEEPwriteCnt;
#define E_WAIT_EEP_WRITE_RESULT_TIME_OUT  50*10
U8 uFailWriteEEPcnt;
#define E_FAIL_WRITE_EEP_CNT  3
E_DATASEND_RESULT eCabdiagEPsentResult; 
BOOL bEEPloadFinished = FALSE;
U16 uWaitEEPdownloadTimes;
U16 uWaitEEPdownloadTimes2;
#define WAIT_EEP_DOWNLOAD_TIMES     65
#define WAIT_EEP_DOWNLOAD_TIMES2    60*50
U16 SpiFailedCnt = 0;
BOOL bGWNodeIsLost = FALSE;
BOOL bPDCNodeIsLost = FALSE;
BOOL bDTCBusoffRecordSta = FALSE;
BOOL bNAckSta = FALSE;
BOOL ResetTimeCntFlag = FALSE;

U8 uESP_2_AliveCountError1Times;
U8 uESP_2_AliveCountError2Times;
U8 uESP_2_ChecksumErrorTimes;

U8 uABS_2_AliveCountError1Times;
U8 uABS_2_AliveCountError2Times;
U8 uABS_2_ChecksumErrorTimes;

U8 uABS_1_AliveCountError1Times;
U8 uABS_1_AliveCountError2Times;
U8 uABS_1_ChecksumErrorTimes;

U8 uSAS_1_AliveCountError1Times;
U8 uSAS_1_AliveCountError2Times;
U8 uSAS_1_ChecksumErrorTimes;

/*===FUNCTIONS========================================================*/

/*---Global-----------------------------------------------------------*/
/***********************************************************************
* FUNCTION    : void desc_dtc_init(void)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
void can_diag_dtc_init(void)
{    
    dtc_eeprom_init_step = DTC_INIT_STEP_START;
    dtc_status_svc14_clear_counter = DTC_STATUS_SVC14_CLEAR_FINISHED;

    /* control dtc setting to on in default */
    dtc_control_setting_on_off = TRUE;

    /* init to disable all dtc record */
    dtc_record_enable_mask = DTC_RECORD_ENABLE_NONE;

    /* Adjust dtc record enable mask */
    can_diag_dtc_record_enable_adjust();
    dtc_bus_off_counter = 0;
    bDtcDataNeedSendToEep = FALSE;
    bWaitEEPwriteResp = FALSE;
    #ifdef DTC_AGING_COUNTER
    _memset(bSetClearHistoryFaultCntFlag,TRUE,DTC_CODE_MAX_NUM);
    #endif
    #ifdef DIAG_NM_TIMEOUT_NOT_USE_IL_TIMEOUT_FLAG
    ResetCanDiagTimeoutState();
    #endif
    uWaitEEPdownloadTimes = 0;
    uWaitEEPdownloadTimes2 = 0;
}

void CanDiagDtc_Notify_EEP_load_ok(void)
{
    bEEPloadFinished = TRUE;
}
/***********************************************************************
* FUNCTION    : void can_diag_dtc_eeprom_init_handle(void)
* DESCRIPTION : Initialize all the dtc eeprom data at one time will lead to other can function delay,
*such as nm or app cycle msg transmition. So we separate the init action of dtc eeprom.
*This function called by can_diag_task() in 10ms cycle.
* INPUTS      : none
* RETURN      : none
***********************************************************************/
void can_diag_dtc_eeprom_init_handle(void)
{
    U8 record_count;
   
    switch(dtc_eeprom_init_step)
    {
        case DTC_INIT_STEP_START:
            if(bEEPloadFinished)
            {
                dtc_eeprom_init_step = DTC_INIT_STEP_READ_DTC_ST;
                uWaitEEPdownloadTimes = 0;
                uWaitEEPdownloadTimes2 = 0;
                break;
            }
            if(sPower_Can >= V_NORMAL)
            {
                if(uWaitEEPdownloadTimes++>WAIT_EEP_DOWNLOAD_TIMES)
                {
                    dtc_eeprom_init_step = DTC_INIT_STEP_READ_DTC_ST;
                    uWaitEEPdownloadTimes = 0;
                    uWaitEEPdownloadTimes2 = 0;
                    break;
                }
            }
			#if 0
            if(uWaitEEPdownloadTimes2++>WAIT_EEP_DOWNLOAD_TIMES2)
            {
                dtc_eeprom_init_step = DTC_INIT_STEP_READ_DTC_ST;
                uWaitEEPdownloadTimes = 0;
                uWaitEEPdownloadTimes2 = 0;
                break;
            }
			#endif
        break;

        case DTC_INIT_STEP_READ_DTC_ST:
            /* recall DTC status */
            ReadDtcFromEEP();
            
            dtc_eeprom_init_step = DTC_INIT_STEP_CALCULATE_DTC_ST;
            break;            

        case DTC_INIT_STEP_CALCULATE_DTC_ST:
            for(record_count = 0; record_count < DTC_CODE_MAX_NUM; record_count++)
            {
                /* Initialize dtc record counter. */
                dtc_status_record_cnt[record_count].dtc_create_cnt = 0;
                dtc_status_record_cnt[record_count].dtc_recover_cnt = 0;
                
                /* Initialize dtc status. */
                can_diag_dtc_status_report(record_count, (DTC_TEST_INIT|DTC_TEST_NEW_OPR), TRUE);
            }

            dtc_eeprom_init_step = DTC_INIT_STEP_WRITE_EEPROM_ST;
            break;

        case DTC_INIT_STEP_WRITE_EEPROM_ST:
            /* store dtc status */
           // WriteAllDtcToEEP();
            dtc_eeprom_init_step = DTC_INIT_STEP_FINISHED;

            /* Adjust dtc record enable mask */
            can_diag_dtc_record_enable_adjust();
            break;

        case DTC_INIT_STEP_FINISHED:
            if(bDtcDataNeedSendToEep)
            {                
                if(TRUE)//if(!bWaitEEPwriteResp)
                {
                    WriteAllDtcToEEP();
					//can_diag_record_snapshot();
                    bDtcDataNeedSendToEep = FALSE;
                    bWaitEEPwriteResp = TRUE;
                    uWaitEEPwriteCnt = 0;
                    eCabdiagEPsentResult = E_NORESULT;
                }
            }
            if(bWaitEEPwriteResp)
            {
                if((uWaitEEPwriteCnt++>E_WAIT_EEP_WRITE_RESULT_TIME_OUT)
                    ||(E_SENTFAIL==eCabdiagEPsentResult ))
                {
                    if(uFailWriteEEPcnt++>E_FAIL_WRITE_EEP_CNT)
                    {
                        uFailWriteEEPcnt = 0;
                        bWaitEEPwriteResp = FALSE;
                    }
                    else
                    {
                        bDtcDataNeedSendToEep = TRUE;
                        bWaitEEPwriteResp = FALSE;
                    }
                    break;
                }
                if(E_SENTOK ==eCabdiagEPsentResult )
                {
                     bWaitEEPwriteResp = FALSE;           
                     uFailWriteEEPcnt = 0;         
                }
            }            
        break;

        default:
            break;
    }
}

void ReadSnapshotFormEEP(void)
{
	int i;	
	for(i=0; i< 15; i++)
	{
		dtc_snapshot_record[i].Snapshot0100_VehicleSpeed = EED_Snapshot0100_VehicleSpeed1[i];
	}

	for(i=0; i< 15; i++)
	{
		dtc_snapshot_record[i+DTC_CAN_BUS_ERROR].Snapshot0100_VehicleSpeed = EED_Snapshot0100_VehicleSpeed2[i];
	}
	
	for(i=0; i< 13; i++)
	{
		dtc_snapshot_record[i+DTC_LOST_EMS_MESSAGE].Snapshot0100_VehicleSpeed = EED_Snapshot0100_VehicleSpeed3[i];
	}

	for(i=0; i< 7; i++)
	{
		dtc_snapshot_record[i].Snapshot0101_Odometer = EED_Snapshot0101_VehicleOdometer1[i];
	}

	for(i=0; i< 7; i++)
	{
		dtc_snapshot_record[i+DTC_BACK_CAMERA_SHORT_BAT].Snapshot0101_Odometer = EED_Snapshot0101_VehicleOdometer2[i];
	}

	for(i=0; i< 7; i++)
	{
		dtc_snapshot_record[i+DTC_AVM_SYSTEM_ERROR].Snapshot0101_Odometer = EED_Snapshot0101_VehicleOdometer3[i];
	}

	for(i=0; i< 7; i++)
	{
		dtc_snapshot_record[i+DTC_LOST_PDC_NODE].Snapshot0101_Odometer = EED_Snapshot0101_VehicleOdometer4[i];
	}

	for(i=0; i< 7; i++)
	{
		dtc_snapshot_record[i+DTC_LOST_TCU_MESAGE].Snapshot0101_Odometer = EED_Snapshot0101_VehicleOdometer5[i];
	}

    for(i=0; i< 6; i++)
	{
		dtc_snapshot_record[i+DTC_ESP_MESSAGE_LIVECOUNTER_ERROR].Snapshot0101_Odometer = EED_Snapshot0101_VehicleOdometer6[i];
	}

    for(i=0; i< 30; i++)
	{
		dtc_snapshot_record[i].Snapshot0102_SupplyVoltage = EED_Snapshot0102_SupplyVoltage1[i];
	}

    for(i=0; i< 11; i++)
	{
		dtc_snapshot_record[i+DTC_LOST_EMS_MESSAGE].Snapshot0102_SupplyVoltage = EED_Snapshot0102_SupplyVoltage1[i];
	}
}

void ReadDtcFromEEP(void)
{
    U8 i;
    for(i=0;i<BIT30;i++)
    {
        dtc_status_record[i].dtc_status.status_byte = EED_CANDTC[i];
        #ifdef DTC_AGING_COUNTER
		dtc_status_aging_cnt[i] = EED_CANDTC_AGING_CNT[i];
		dtc_status_aged_cnt[i] = EED_CANDTC_AGED_CNT[i];
		dtc_status_occurrence_cnt[i] = EED_CANDTC_OCCURRENCE_CNT[i];
        #endif
		dtc_status_fid_data[i] = EED_CANDTC_FID_DATA[i];
    }  

	for(i=0;i<DTC_CODE_MAX_NUM1;i++)
	{
		dtc_status_record[BIT30+i].dtc_status.status_byte = EED_CANDTC1[i];
        #ifdef DTC_AGING_COUNTER
		dtc_status_aging_cnt[BIT30+i] = EED_CANDTC_AGING_CNT1[i];
		dtc_status_aged_cnt[BIT30+i] = EED_CANDTC_AGED_CNT1[i];
		dtc_status_occurrence_cnt[BIT30+i] = EED_CANDTC_OCCURRENCE_CNT1[i];
        #endif	
		dtc_status_fid_data[BIT30+i] = EED_CANDTC_FID_DATA1[i];
	}
	
	ReadSnapshotFormEEP();
}

/***********************************************************************
*  Name        : NaviApp_EEPWrite_CallBack
*  Description : DeInit Navi msg handler        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CanDiagDtc_EEPWrite_CallBack (ERR_TYPE type)
{
    if(type == ERR_OK)
    {
        eCabdiagEPsentResult = E_SENTOK;
    }
    else
    {
        eCabdiagEPsentResult = E_SENTFAIL;
    }
}

void WriteSnapshotToEEP(void)
{
	int i;
	EED_LockDataBlock(EED_nDiagData1);
	for(i=0; i< 15; i++)
	{
		EED_Snapshot0100_VehicleSpeed1[i] = dtc_snapshot_record[i].Snapshot0100_VehicleSpeed;
	}
	EED_UnlockAndSavDataBlock(EED_nDiagData1);

	EED_LockDataBlock(EED_nDiagData2);
	for(i=0; i< 15; i++)
	{
		EED_Snapshot0100_VehicleSpeed2[i] = dtc_snapshot_record[i+DTC_CAN_BUS_ERROR].Snapshot0100_VehicleSpeed;
	}
	EED_UnlockAndSavDataBlock(EED_nDiagData2);

	EED_LockDataBlock(EED_nDiagData3);
	for(i=0; i< 13; i++)
	{
		EED_Snapshot0100_VehicleSpeed3[i] = dtc_snapshot_record[i+DTC_LOST_EMS_MESSAGE].Snapshot0100_VehicleSpeed;
	}
	EED_UnlockAndSavDataBlock(EED_nDiagData3);	


	EED_LockDataBlock(EED_nDiagData4);
	for(i=0; i< 7; i++)
	{
		EED_Snapshot0101_VehicleOdometer1[i] = dtc_snapshot_record[i].Snapshot0101_Odometer;
	}
	EED_UnlockAndSavDataBlock(EED_nDiagData4);

	EED_LockDataBlock(EED_nDiagData5);
	for(i=0; i< 7; i++)
	{
		EED_Snapshot0101_VehicleOdometer2[i] = dtc_snapshot_record[i+DTC_BACK_CAMERA_SHORT_BAT].Snapshot0101_Odometer;
	}
	EED_UnlockAndSavDataBlock(EED_nDiagData5);

	EED_LockDataBlock(EED_nDiagData6);
	for(i=0; i< 7; i++)
	{
		EED_Snapshot0101_VehicleOdometer3[i] = dtc_snapshot_record[i+DTC_AVM_SYSTEM_ERROR].Snapshot0101_Odometer;
	}
	EED_UnlockAndSavDataBlock(EED_nDiagData6);

	EED_LockDataBlock(EED_nDiagData7);
	for(i=0; i< 7; i++)
	{
		EED_Snapshot0101_VehicleOdometer4[i] = dtc_snapshot_record[i+DTC_LOST_PDC_NODE].Snapshot0101_Odometer;
	}
	EED_UnlockAndSavDataBlock(EED_nDiagData7);

	EED_LockDataBlock(EED_nDiagData8);
	for(i=0; i< 7; i++)
	{
		EED_Snapshot0101_VehicleOdometer5[i] = dtc_snapshot_record[i+DTC_LOST_TCU_MESAGE].Snapshot0101_Odometer;
	}
	EED_UnlockAndSavDataBlock(EED_nDiagData8);

    EED_LockDataBlock(EED_nDiagData9);
	for(i=0; i< 30; i++)
	{
		EED_Snapshot0102_SupplyVoltage1[i] = dtc_snapshot_record[i].Snapshot0102_SupplyVoltage;
	}
	EED_UnlockAndSavDataBlock(EED_nDiagData9);

    EED_LockDataBlock(EED_nDiagData10);
	for(i=0; i< 11; i++)
	{
		EED_Snapshot0102_SupplyVoltage2[i] = dtc_snapshot_record[i+DTC_LOST_EMS_MESSAGE].Snapshot0102_SupplyVoltage;
	}
	EED_UnlockAndSavDataBlock(EED_nDiagData10);

    EED_LockDataBlock(EED_nDiagData11);
	for(i=0; i< 6; i++)
	{
		EED_Snapshot0101_VehicleOdometer6[i] = dtc_snapshot_record[i+DTC_ESP_MESSAGE_LIVECOUNTER_ERROR].Snapshot0101_Odometer;
	}
	EED_UnlockAndSavDataBlock(EED_nDiagData11);
	
}

void WriteAllDtcToEEP(void)
{
        U8 i;
        EED_LockDataBlock(EED_nDTCrecord);
        for(i=0;i<BIT30;i++)
        {
            EED_CANDTC[i] = dtc_status_record[i].dtc_status.status_byte;
        } 
		EED_UnlockAndSavDataBlock(EED_nDTCrecord);

        EED_LockDataBlock(EED_nDTCrecord1);
        for(i=0;i<DTC_CODE_MAX_NUM1;i++)
        {
            EED_CANDTC1[i] = dtc_status_record[i+BIT30].dtc_status.status_byte;
        } 
		EED_UnlockAndSavDataBlock(EED_nDTCrecord1);
		
		WriteSnapshotToEEP();

        EED_LockDataBlock(EED_nDTCFidData);
        for(i=0;i<BIT30;i++)
        {
            EED_CANDTC_FID_DATA[i] = dtc_status_fid_data[i];
        } 
		EED_UnlockAndSavDataBlock(EED_nDTCFidData);

        EED_LockDataBlock(EED_nDTCFidData1);
        for(i=0;i<DTC_CODE_MAX_NUM1;i++)
        {
            EED_CANDTC_FID_DATA1[i] = dtc_status_fid_data[i+BIT30];
        } 
		EED_UnlockAndSavDataBlock(EED_nDTCFidData1);		
		
		#ifdef DTC_AGING_COUNTER
		
        EED_LockDataBlock(EED_nDTCOccurrenceCount);
        for(i=0;i<BIT30;i++)
        {
            EED_CANDTC_OCCURRENCE_CNT[i] = dtc_status_occurrence_cnt[i];
        } 
		EED_UnlockAndSavDataBlock(EED_nDTCOccurrenceCount);


        EED_LockDataBlock(EED_nDTCOccurrenceCount1);
        for(i=0;i<DTC_CODE_MAX_NUM1;i++)
        {
            EED_CANDTC_OCCURRENCE_CNT1[i] = dtc_status_occurrence_cnt[i+BIT30];
        } 
		EED_UnlockAndSavDataBlock(EED_nDTCOccurrenceCount1);

		

		EED_LockDataBlock(EED_nDTCAgingCount);
		for(i=0;i<BIT30;i++)
        {
            EED_CANDTC_AGING_CNT[i] = dtc_status_aging_cnt[i];
        } 
		EED_UnlockAndSavDataBlock(EED_nDTCAgingCount);

		EED_LockDataBlock(EED_nDTCAgingCount1);
		for(i=0;i<DTC_CODE_MAX_NUM1;i++)
        {
            EED_CANDTC_AGING_CNT1[i] = dtc_status_aging_cnt[i+BIT30];
        } 
		EED_UnlockAndSavDataBlock(EED_nDTCAgingCount1);		


		EED_LockDataBlock(EED_nDTCAgedCount);
		for(i=0;i<BIT30;i++)
        {
            EED_CANDTC_AGED_CNT[i] = dtc_status_aged_cnt[i];
        } 
		EED_UnlockAndSavDataBlock(EED_nDTCAgedCount);

		EED_LockDataBlock(EED_nDTCAgedCount1);
		for(i=0;i<DTC_CODE_MAX_NUM;i++)
        {
            EED_CANDTC_AGED_CNT1[i] = dtc_status_aged_cnt[i+BIT30];
        } 
		EED_UnlockAndSavDataBlock(EED_nDTCAgedCount1);				
		#endif
}

/***********************************************************************
* FUNCTION    : BOOL can_diag_dtc_check_init_finished(void)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
BOOL can_diag_dtc_check_init_finished(void)
{
    if(DTC_INIT_STEP_FINISHED == dtc_eeprom_init_step)
    {
        return(TRUE);
    }
    else
    {
        return(FALSE);
    }
}

/***********************************************************************
* FUNCTION    : void can_diag_control_dtc_setting_on(void)
* DESCRIPTION : TRUE:means control dtc setting is on,
*                         FALSE:means control dtc setting is off.
* INPUTS      : none
* RETURN      : none
***********************************************************************/
void can_diag_control_dtc_setting_on(void)
{
    dtc_control_setting_on_off = TRUE;
}

/***********************************************************************
* FUNCTION    : void can_diag_control_dtc_setting_off(void)
* DESCRIPTION : TRUE:means control dtc setting is on,
*                         FALSE:means control dtc setting is off.
* INPUTS      : none
* RETURN      : none
***********************************************************************/
void can_diag_control_dtc_setting_off(void)
{
    dtc_control_setting_on_off = FALSE;
}

/***********************************************************************
* FUNCTION    : BOOL can_diag_control_dtc_setting_check(U8 dtc_code)
* DESCRIPTION : TRUE:means control dtc setting is on,
*                         FALSE:means control dtc setting is off.
* INPUTS      : none
* RETURN      : none
***********************************************************************/
static BOOL can_diag_control_dtc_setting_check(void)
{
    return dtc_control_setting_on_off;
}

/***********************************************************************
* FUNCTION    : static BOOL SYS_control_dtc_setting_check(void)
* DESCRIPTION : TRUE:means control dtc setting is on,
*                         FALSE:means control dtc setting is off.
* INPUTS      : none
* RETURN      : none
***********************************************************************/
static BOOL SYS_control_dtc_setting_check(void)
{
	if((GW_OTAMode_fun == 0x00) && (TRUE == can_diag_control_dtc_setting_check()))
	{
    	return TRUE;
	}
	return FALSE;
}

//BOOL desc_get_dtc_setting(void)

/***********************************************************************
* FUNCTION    : void can_diag_dtc_record_enable_adjust(void)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
void can_diag_dtc_record_enable_adjust(void)
{   
	static U8 sPower_Bdy;
	CS_SIG_SyncReceive(SIG_VOLTAGEFAIL_STATUS, (U16 *)&sPower_Bdy); 

	/* diagnosis function start-up init delay according to vehicle manufacturer */
    if(CAN_DIAG_INIT_DELAY_TIMEOUT != can_diag_init_delay_timer)
    {
        /* all dtc record disable */
        dtc_record_enable_mask = DTC_RECORD_ENABLE_NONE;
        
        return;
    }
    else
    {
        /* Disable here, because we do not know the other situations, so let other judgement following to do this job. */
        dtc_record_enable_mask = DTC_RECORD_ENABLE_NONE;
    }

/* dtc eeprom init delay */
    if(DTC_INIT_STEP_FINISHED != dtc_eeprom_init_step)
    {
        /* all dtc record disable */
        dtc_record_enable_mask = DTC_RECORD_ENABLE_NONE;
        
        return;    
    }
    else
    {
        /* Disable here, because we do not know the other situations, so let other judgement following to do this job. */
        dtc_record_enable_mask = DTC_RECORD_ENABLE_NONE;        
    }

/* service $14 clear dtc eeprom init delay */
    if(DTC_STATUS_SVC14_CLEAR_FINISHED != dtc_status_svc14_clear_counter)
    {
        /* all dtc record disable */
        dtc_record_enable_mask = DTC_RECORD_ENABLE_NONE;
        
        return;    
    }
    else
    {
        /* Disable here, because we do not know the other situations, so let other judgement following to do this job. */
        dtc_record_enable_mask = DTC_RECORD_ENABLE_NONE;        
    }

    /* other delay according to vehicle manufacturer */
    if(sPower_Can == V_NORMAL)  //if power out range of [9-16v],stop candiag
    {
        dtc_record_enable_mask = (dtc_record_enable_mask|DTC_RECORD_ENABLE_OP_VOLT);

        if(CAN_DIAG_BAT_VOLT_RECOVER_DELAY_TIMEOUT != can_diag_bat_volt_recover_delay_timer)
        {
            dtc_record_enable_mask = (dtc_record_enable_mask&(~DTC_RECORD_ENABLE_NM));
            //dtc_record_enable_mask = (dtc_record_enable_mask&(~DTC_RECORD_ENALBE_BDY));

            //return;
        }
        else
        {
            //dtc_record_enable_mask = (dtc_record_enable_mask|DTC_RECORD_ENALBE_BDY);

            if(CAN_DIAG_NM_INIT_DELAY_TIMEOUT == can_diag_init_nm_delay_timer)
            {
                dtc_record_enable_mask = (dtc_record_enable_mask|DTC_RECORD_ENABLE_NM);
            }
            else
            {
                dtc_record_enable_mask = (dtc_record_enable_mask&(~DTC_RECORD_ENABLE_NM));
            }
        }
    }
    else
    {
        dtc_record_enable_mask = (dtc_record_enable_mask|DTC_RECORD_ENABLE_OP_VOLT);
        
        dtc_record_enable_mask = (dtc_record_enable_mask&(~DTC_RECORD_ENABLE_NM));
        //dtc_record_enable_mask = (dtc_record_enable_mask&(~DTC_RECORD_ENALBE_BDY));
    }

    if(sPower_Bdy == V_NORMAL)  
    {
        dtc_record_enable_mask = (dtc_record_enable_mask|DTC_RECORD_ENABLE_OP_VOLT);

        if(CAN_DIAG_BAT_VOLT_RECOVER_DELAY_TIMEOUT != can_diag_bdy_bat_volt_recover_delay_timer)
        {
            dtc_record_enable_mask = (dtc_record_enable_mask&(~DTC_RECORD_ENALBE_BDY));

            //return;
        }
        else
        {
            dtc_record_enable_mask = (dtc_record_enable_mask|DTC_RECORD_ENALBE_BDY);
        }
    }
    else
    {
        dtc_record_enable_mask = (dtc_record_enable_mask|DTC_RECORD_ENABLE_OP_VOLT);
        dtc_record_enable_mask = (dtc_record_enable_mask&(~DTC_RECORD_ENALBE_BDY));
    }	
}

/***********************************************************************
* FUNCTION    :  can_diag_increase_bus_off_counter
* DESCRIPTION : 
* INPUTS      : 
* RETURN      : 
***********************************************************************/
void can_diag_increase_bus_off_counter(void)
{
    if(dtc_bus_off_counter < 255)
    {
        dtc_bus_off_counter++;
    }
}

/***********************************************************************
* FUNCTION    :  can_diag_reset_bus_off_counter
* DESCRIPTION : 
* INPUTS      : 
* RETURN      : 
***********************************************************************/
void can_diag_reset_bus_off_counter(void)
{
	if(dtc_bus_off_counter != 0)
	{
		dtc_bus_off_counter = 0;
	}
    dtc_bus_off_counter = 0;
}

/***********************************************************************
* FUNCTION    : BOOL can_diag_dtc_record_nm_enable_check(void)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
static BOOL can_diag_dtc_record_nm_enable_check(void)
{
    return(((dtc_record_enable_mask & DTC_RECORD_ENABLE_NM) != 0) ? 1 : 0);
}

/***********************************************************************
* FUNCTION    : BOOL can_diag_dtc_record_body_enable_check(void)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
static BOOL can_diag_dtc_record_body_enable_check(void)
{
    return(((dtc_record_enable_mask & DTC_RECORD_ENALBE_BDY) != 0) ? 1 : 0);
}

/***********************************************************************
* FUNCTION    : BOOL can_diag_dtc_record_op_volt_enable_check(void)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
static BOOL can_diag_dtc_record_op_volt_enable_check(void)
{
    return(((dtc_record_enable_mask & DTC_RECORD_ENABLE_OP_VOLT) != 0) ? 1 : 0);
}

/***********************************************************************
* FUNCTION    : U16 can_diag_get_dtc_status_by_status_mask(U8 *p_dtc, U8 status_mask)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
U16 can_diag_get_dtc_status_by_status_mask(U8 *p_dtc, U8 status_mask)
{
    U16 dtc_count = 0;
    U8 record_count;

    for(record_count = 0; record_count < DTC_CODE_MAX_NUM; record_count++)
    {
    #ifdef SUPPORT_READ_HISTORY_FAULT
        if((((status_mask == HISTORY_DTC)||(status_mask == CURRENT_DTC))&&(dtc_status_record[record_count].dtc_status.status_byte == status_mask))
            ||((status_mask != HISTORY_DTC)&&(status_mask != CURRENT_DTC)&&(dtc_status_record[record_count].dtc_status.status_byte & status_mask) != 0))
    #else
        if((dtc_status_record[record_count].dtc_status.status_byte & status_mask) != 0)
    #endif
        {
            *p_dtc++ = dtc_code_data[record_count].dtc_high_byte;
            *p_dtc++ = dtc_code_data[record_count].dtc_middle_byte;
            *p_dtc++ = dtc_code_data[record_count].dtc_low_byte;
            *p_dtc++ = dtc_status_record[record_count].dtc_status.status_byte;
            
            dtc_count++;
        }
    }
    
    return dtc_count;
}

/***********************************************************************
* FUNCTION    : U16 can_diag_get_dtc_status_by_DTC(DescMsgContext* pMsgContext)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
U8 can_diag_get_dtc_status_by_DTC(DescMsgContext* pMsgContext)
{
    U8 dtc_sts = 0;
    U8 record_count;

    for(record_count = 0; record_count < DTC_CODE_MAX_NUM; record_count++)
    {
    	if((dtc_code_data[record_count].dtc_high_byte == pMsgContext->reqData[0]) 
			&& (dtc_code_data[record_count].dtc_middle_byte == pMsgContext->reqData[1])
			&& (dtc_code_data[record_count].dtc_low_byte == pMsgContext->reqData[2]))
        {
            dtc_sts = dtc_status_record[record_count].dtc_status.status_byte;
        }
    }
    
    return dtc_sts;
}
/***********************************************************************
* FUNCTION    : DTC_SNAPSHOT_RECORD_IDENTIFIERS read_Snapshot_from_EEP(U8 DTC_NUM)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
DTC_SNAPSHOT_RECORD_IDENTIFIERS read_Snapshot_from_EEP(U8 DTC_NUM)
{
	DTC_SNAPSHOT_RECORD_IDENTIFIERS DTC_Snapshot_Record_Identifiers;
	if((DTC_NUM / 15) >= 1)
	{
		DTC_Snapshot_Record_Identifiers.Snapshot0100_VehicleSpeed = EED_Snapshot0100_VehicleSpeed1[DTC_NUM % 15];
	}
	else
	{
		DTC_Snapshot_Record_Identifiers.Snapshot0100_VehicleSpeed = EED_Snapshot0100_VehicleSpeed2[DTC_NUM];
	}

	switch(DTC_NUM / 7)
	{
		case 0:
			DTC_Snapshot_Record_Identifiers.Snapshot0101_Odometer = EED_Snapshot0101_VehicleOdometer1[DTC_NUM];
			break;
		case 1:
			DTC_Snapshot_Record_Identifiers.Snapshot0101_Odometer = EED_Snapshot0101_VehicleOdometer2[DTC_NUM % 7];
			break;
		case 2:
			DTC_Snapshot_Record_Identifiers.Snapshot0101_Odometer = EED_Snapshot0101_VehicleOdometer3[DTC_NUM % 7];
			break;
		case 3:
			DTC_Snapshot_Record_Identifiers.Snapshot0101_Odometer = EED_Snapshot0101_VehicleOdometer4[DTC_NUM % 7];
			break;			
		default:
			break;
	}
    if(DTC_NUM <30)
	{
		DTC_Snapshot_Record_Identifiers.Snapshot0102_SupplyVoltage = EED_Snapshot0102_SupplyVoltage1[DTC_NUM % 30];
	}
	else
	{
		DTC_Snapshot_Record_Identifiers.Snapshot0102_SupplyVoltage = EED_Snapshot0102_SupplyVoltage2[DTC_NUM];
	}
	
	return DTC_Snapshot_Record_Identifiers;
}


/***********************************************************************
* FUNCTION    : void can_diag_record_snapshoot_to_DTC(U8 dtc_code)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
void can_diag_record_snapshoot_to_DTC(U8 dtc_code)
{
    U16 PWrVALUE = 0;
	float f_PWrVALUE = 0;
    CS_SIG_AsyncReceive(SIG_APP_PWR,&PWrVALUE);
	f_PWrVALUE = PWrVALUE*12/212.00;
	Can_Signal_Snapshot_Data.Snapshot0102_SupplyVoltage = (U8)f_PWrVALUE;
	dtc_snapshot_record[dtc_code].Snapshot0100_VehicleSpeed = Can_Signal_Snapshot_Data.Snapshot0100_VehicleSpeed;
	dtc_snapshot_record[dtc_code].Snapshot0101_Odometer = Can_Signal_Snapshot_Data.Snapshot0101_Odometer;
    dtc_snapshot_record[dtc_code].Snapshot0102_SupplyVoltage = Can_Signal_Snapshot_Data.Snapshot0102_SupplyVoltage;
}


/***********************************************************************
* FUNCTION    : void can_diag_record_fid_to_DTC(U8 dtc_code)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
static void can_diag_record_fid_to_DTC(U8 dtc_code)
{
	switch(dtc_code)
	{
		case DTC_LOST_GW_NODE:
			can_diag_dtc_GW_node_lost_fid_record();
		break;
		case DTC_LOST_ESP_MESAGE:
			can_diag_ESP_node_lost_fid_record();
		break;
		case DTC_LOST_HU_MESSAGE:
			can_diag_HU_node_lost_fid_record();
		break;
		case DTC_ESP_MESSAGE_LIVECOUNTER_ERROR:
			can_diag_ESP_content_error_fid_record();
		break;
		case DTC_ESP_MESSAGE_CHECKSUM_ERROR:
			can_diag_EPS_checksum_error_fid_record();
		break;
		case DTC_ESP_MESSAGE_SIGNAL_INVALID:
			can_diag_ESP_signal_invalid_fid_record();
		break;		
		
		default:
		break;
	}
}

/***********************************************************************
* FUNCTION    : void can_diag_get_dtc_snapshot_record(U8 *p_dtc,DescMsgContext* pMsgContext)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
void can_diag_get_dtc_snapshot_record(U8 *p_dtc,DescMsgContext* pMsgContext)
{
    U8 dtc_sts = 0;
    U8 record_count;
	//DTC_SNAPSHOT_RECORD_IDENTIFIERS DTC_Snapshot_Record_Identifiers;
	for(record_count = 0; record_count < DTC_CODE_MAX_NUM; record_count++)
    {
    	if((dtc_code_data[record_count].dtc_high_byte == pMsgContext->reqData[0]) 
			&& (dtc_code_data[record_count].dtc_middle_byte == pMsgContext->reqData[1])
			&& (dtc_code_data[record_count].dtc_low_byte == pMsgContext->reqData[2]))
        {
        	//DTC_Snapshot_Record_Identifiers = read_Snapshot_from_EEP(record_count);
        	//if((dtc_status_record[record_count].dtc_status.status_byte & DTC_STATUS_AVAILABILITY_MASK) != 0)
        	{
        		*p_dtc++ = VEHICLESPEED_DTC_SNAPSHOT_DATAIDENTIFIER >> 8;
				*p_dtc++ = VEHICLESPEED_DTC_SNAPSHOT_DATAIDENTIFIER & 0x00FF;
				*p_dtc++ = dtc_snapshot_record[record_count].Snapshot0100_VehicleSpeed >> 8;
				*p_dtc++ = dtc_snapshot_record[record_count].Snapshot0100_VehicleSpeed & 0x00FF;
        		*p_dtc++ = ODOMETER_DTC_SNAPSHOT_DATAIDENTIFIER >> 8;
				*p_dtc++ = ODOMETER_DTC_SNAPSHOT_DATAIDENTIFIER & 0x00FF;				
				*p_dtc++ = dtc_snapshot_record[record_count].Snapshot0101_Odometer >> 24;
				*p_dtc++ = dtc_snapshot_record[record_count].Snapshot0101_Odometer >> 16;
				*p_dtc++ = dtc_snapshot_record[record_count].Snapshot0101_Odometer >> 8;
				*p_dtc++ = dtc_snapshot_record[record_count].Snapshot0101_Odometer & 0x00FF;
                *p_dtc++ = SUPPLYVOLTAGE_DTC_SNAPSHOT_DATAIDENTIFIER >> 8;
				*p_dtc++ = SUPPLYVOLTAGE_DTC_SNAPSHOT_DATAIDENTIFIER & 0x00FF;
                *p_dtc++ = dtc_snapshot_record[record_count].Snapshot0102_SupplyVoltage & 0x00FF;
			}
        }
    }
}

/***********************************************************************
* FUNCTION    : U8 can_diag_get_dtc_extdata_record(U8 *p_dtc,DescMsgContext* pMsgContext)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
U8 can_diag_get_dtc_extdata_record(U8 *p_dtc,DescMsgContext* pMsgContext)
{
    U8 record_count;
	U8 DTCExtDataRecordNumber = 0;
	U8 datalen;
	DTCExtDataRecordNumber = pMsgContext->reqData[3];
	for(record_count = 0; record_count < DTC_CODE_MAX_NUM; record_count++)
	{
		if((dtc_code_data[record_count].dtc_high_byte == pMsgContext->reqData[0]) 
			&& (dtc_code_data[record_count].dtc_middle_byte == pMsgContext->reqData[1])
			&& (dtc_code_data[record_count].dtc_low_byte == pMsgContext->reqData[2]))
		{
			break;
		}
	}
	if(ALL_EXTENDED_DATA_RECORDS == pMsgContext->reqData[3])
	{
		//if((dtc_status_record[record_count].dtc_status.status_byte & DTC_STATUS_AVAILABILITY_MASK) != 0)
    	//{
    		*p_dtc++ = DTC_OCCURRENCE_CNT;
			*p_dtc++ = dtc_status_occurrence_cnt[record_count];
			*p_dtc++ = DTC_AGING_CNT;
    		*p_dtc++ = dtc_status_aging_cnt[record_count];
			// *p_dtc++ = DTC_FID;
			// *p_dtc++ = dtc_status_fid_data[record_count];
			*p_dtc++ = DTC_AGED_CNT;
    		*p_dtc++ = dtc_status_aged_cnt[record_count];				
		//}
		datalen = 10;
	}
	else if(pMsgContext->reqData[3] <= 3)
	{
		switch(pMsgContext->reqData[3])
		{
			case 1:
			{
				*p_dtc++ = DTC_OCCURRENCE_CNT;
				*p_dtc++ = dtc_status_occurrence_cnt[record_count];
			}break;
			case 2:
			{
				*p_dtc++ = DTC_AGING_CNT;
	    		*p_dtc++ = dtc_status_aging_cnt[record_count];
			}break;

			case 3:
			{
				*p_dtc++ = DTC_AGED_CNT;
	    		*p_dtc++ = dtc_status_aged_cnt[record_count];	
			}break;

			// case 4:
			// {
			// 	*p_dtc++ = DTC_FID;
	    	// 	*p_dtc++ = dtc_status_fid_data[record_count];
			// }break;			
			default:
				break;
		}

		datalen = 6;
	}

	return datalen;
}

/***********************************************************************
* FUNCTION    : U16 can_diag_check_supported_dtc(DescMsgContext* pMsgContext)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
BOOL can_diag_check_supported_dtc(DescMsgContext* pMsgContext)
{
	U8 record_count;

	for(record_count = 0; record_count < DTC_CODE_MAX_NUM; record_count++)
	{
		if((dtc_code_data[record_count].dtc_high_byte == pMsgContext->reqData[0]) 
			&& (dtc_code_data[record_count].dtc_middle_byte == pMsgContext->reqData[1])
			&& (dtc_code_data[record_count].dtc_low_byte == pMsgContext->reqData[2]))
		{
			return TRUE;
		}
	}
	
	return FALSE;
}


/***********************************************************************
* FUNCTION    : U16 can_diag_get_supported_dtc(U8 *p_dtc)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
U16 can_diag_get_supported_dtc(U8 *p_dtc)
{
    U16 dtc_count = 0;
    U8 record_count;

    for(record_count = 0; record_count < DTC_CODE_MAX_NUM; record_count++)
    {
        *p_dtc++ = dtc_code_data[record_count].dtc_high_byte;
        *p_dtc++ = dtc_code_data[record_count].dtc_middle_byte;
        *p_dtc++ = dtc_code_data[record_count].dtc_low_byte;
        *p_dtc++ = dtc_status_record[record_count].dtc_status.status_byte;
        
        dtc_count++;
    }
    
    return dtc_count;
}



/***********************************************************************
* FUNCTION    : U16 can_diag_get_dtc_count(U8 status_mask)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
U16 can_diag_get_dtc_count(U8 status_mask)
{
    U16 dtc_count = 0;
    U8 record_count;

    for(record_count = 0; record_count < DTC_CODE_MAX_NUM; record_count++)
    {
        if((dtc_status_record[record_count].dtc_status.status_byte & status_mask) != 0)
        {
            dtc_count++;
        }
    }
    
    return dtc_count;
}

/***********************************************************************
* FUNCTION    : void can_diag_dtc_monitor_handle(void)
* DESCRIPTION : cycle call is 10ms by can_diag_task.
* INPUTS      : none
* RETURN      : none
***********************************************************************/
void can_diag_dtc_monitor_handle(void)
{
    if(++can_diag_dtc_task_counter > 200)         /* max period 2000ms */
    {
        can_diag_dtc_task_counter = 1;

        if(0 != can_diag_get_dtc_count(0x09))
        {
            can_nm_set_curr_fail_status(TRUE);
        }
        else
        {
            can_nm_set_curr_fail_status(FALSE);
        }
    }


/* network related diagnosis */
 #ifndef NOT_DIAG_CAN_TRANSCRIVER
    if(can_diag_dtc_task_counter % DTC_CHECK_MONITOR_CYCLE_TRANSCEIVER_ERR == 0)
    {
        can_diag_dtc_transceiver_err_monitor();
    }
#endif
#ifndef NOT_DIAG_CAN_BUSOFF
    if(can_diag_dtc_task_counter % DTC_CHECK_MONITOR_CYCLE_BUS_OFF == 0)
    {
        can_diag_dtc_bus_off_monitor();
#ifdef CANDTC_DIAG_LIMPHOME
        can_diag_dtc_limphome_monitor();
#endif
    }
#endif

/* body related diagnosis */
#ifndef NOT_DIAG_SYS_POWER
    if(can_diag_dtc_task_counter % DTC_CHECK_MONITOR_CYCLE_OP_VOLT_LOW == 0)
    {
        can_diag_dtc_bat_volt_monitor();
    }
#endif

#ifdef DIAG_INNER_COMMUNICATION
    if(can_diag_dtc_task_counter % DTC_CHECK_MONITOR_CYCLE_INNERCOMMU_ERR == 0)
    {
        can_diag_dtc_inner_communication_monitor();
    }
#endif

#ifdef DIAG_AVM_ONOFF_SWITCH
	if(can_diag_dtc_task_counter % DTC_CHECK_MONITOR_CYCLE_AVM_ONOFF_KEY_ERR == 0)
	{
		can_diag_dtc_avm_onoff_key_monitor();
	}
#endif

#ifdef DIAG_AVM_CALIBRATION
	if(can_diag_dtc_task_counter % DTC_CHECK_MONITOR_CYCLE_AVM_CALIBRATION_ERR == 0)
	{
		can_diag_dtc_avm_calibration_monitor();
	}
#endif

#ifdef DIAG_LED_INDICATOR
	if(can_diag_dtc_task_counter % DTC_CHECK_MONITOR_CYCLE_LED_INDICATOR_ERR == 0)
	{
		can_diag_avm_indicator_light_monitor();
	}
#endif

    if(can_diag_dtc_task_counter % DTC_CHECK_MONITOR_CYCLE_OP_VOLT_LOW == 0)
    {
        can_diag_dtc_device_err_monitor();
        #ifdef CANDTC_DIAG_DVR_STATUS
        can_diag_dtc_dvr_err_monitor();
        #endif
    }
    #ifdef DIAG_TEMPERATURE_OPTION
    if(can_diag_dtc_task_counter % DTC_CHECK_MONITOR_CYCLE_TEMP_FAULT== 0)
    {
        can_diag_dtc_temp_err_monitor();
    }
    #endif
//monitor node communication
    if(can_diag_dtc_task_counter % DTC_CHECK_MONITOR_CYCLE_LOST_COMM == 0)
    {
  	    can_diag_dtc_GW_node_lost_monitor();
		can_diag_dtc_HU_message_lost_monitor();
		can_diag_dtc_ESP_node_lost_monitor();
        can_diag_dtc_BCM1_node_lost_monitor();
        can_diag_dtc_HCU_node_lost_monitor();
        // can_diag_dtc_PDC_node_lost_monitor();
        can_diag_dtc_nm_lost_node_monitor();
    }

	can_diag_dtc_ESP_content_error_monitor();
	can_diag_dtc_ESP_checksum_error_monitor();
	can_diag_dtc_ESP_signal_invalid_monitor();

	can_diag_dtc_EPS_content_error_monitor();
	can_diag_dtc_EPS_checksum_error_monitor();
	can_diag_dtc_EPS_signal_invalid_monitor();
}

#ifdef CANDTC_DIAG_LIMPHOME
/***********************************************************************
* FUNCTION    :  can_diag_dtc_limphome_monitor
* DESCRIPTION : 
* INPUTS      : 
* RETURN      : 
***********************************************************************/
static void can_diag_dtc_limphome_monitor(void)
{
    if(!bAccOn) /* network related diagnosis is only enable in IGN-ON */
    {
        dtc_status_record_cnt[DTC_CODE_LIMPHOME].dtc_create_cnt = 0;
        dtc_status_record_cnt[DTC_CODE_LIMPHOME].dtc_recover_cnt = 0;
        return;
    }

    if(NmStateLimphome(NmGetStatus()) ? TRUE: FALSE)
    {
        dtc_status_record_cnt[DTC_CODE_LIMPHOME].dtc_create_cnt++;
        dtc_status_record_cnt[DTC_CODE_LIMPHOME].dtc_recover_cnt = 0;

        if(dtc_status_record_cnt[DTC_CODE_LIMPHOME].dtc_create_cnt >= DTC_SET_LIMPHOME_CNT_MAX)
        {
            if((TRUE == can_diag_dtc_record_nm_enable_check())
                &&(FALSE == (NmStateBusError(NmGetStatus()) ? TRUE: FALSE))
                )
            {
                can_diag_dtc_status_report(DTC_CODE_LIMPHOME, DTC_TEST_FAILED, FALSE);
            }
            dtc_status_record_cnt[DTC_CODE_LIMPHOME].dtc_create_cnt = 0;
        }
    }
    else
    {
        dtc_status_record_cnt[DTC_CODE_LIMPHOME].dtc_recover_cnt++;
        
        if(dtc_status_record_cnt[DTC_CODE_LIMPHOME].dtc_recover_cnt >= DTC_CLR_LIMPHOME_CNT_MAX)
        {
            if(TRUE == can_diag_dtc_record_nm_enable_check())
            {
                can_diag_dtc_status_report(DTC_CODE_LIMPHOME, DTC_TEST_PASSED, FALSE);
            }
            dtc_status_record_cnt[DTC_CODE_LIMPHOME].dtc_recover_cnt = 0;
            
            dtc_status_record_cnt[DTC_CODE_LIMPHOME].dtc_create_cnt = 0;
        }        
    }
}
#endif

/*
    ALERT_INFO_FRONT_CAMERA,
    ALERT_INFO_LEFT_CAMERA,
    ALERT_INFO_REAR_CAMERA,
    ALERT_INFO_RIGHT_CAMERA,
*/
/***********************************************************************
* FUNCTION    :  can_diag_dtc_front_switch_err_monitor
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
U16 dtc_set_circuit_fault_cnt_max;
U16 dtc_clr_circuit_fault_cnt_max;
static void can_diag_dtc_device_err_monitor(void)
{    
    U8 i;
    U8 status[CANDTC_CIRCUIT_CHECK_TYPE_NUMBER] = {0};

    if(!Dtc_GetCanDiagDeviceDtc(status))
    {
         for(i=0;i<CANDTC_CIRCUIT_CHECK_TYPE_NUMBER;i++)
         {
                if(TRUE == can_diag_dtc_record_body_enable_check())
                {
                    can_diag_dtc_status_report(i, DTC_TEST_INIT, FALSE);
                }
         }
         return;
    }
    
    for(i=0;i<CANDTC_CIRCUIT_CHECK_TYPE_NUMBER;i++)
    {
		if(i<=DTC_BACK_CAMERA_OPEN_CIRCUIT)
		{
			dtc_set_circuit_fault_cnt_max = DTC_SET_CIRCUIT_OPEN_CNT_MAX;
			dtc_clr_circuit_fault_cnt_max = DTC_CLR_CIRCUIT_OPEN_CNT_MAX;
		}
		else if((i>=DTC_FRONT_CAMERA_SHORT_GND) && (i<=DTC_RIGHT_CAMERA_SHORT_BAT))
		{
			dtc_set_circuit_fault_cnt_max = DTC_SET_CIRCUIT_SHORT_CNT_MAX;
			dtc_clr_circuit_fault_cnt_max = DTC_CLR_CIRCUIT_SHORT_CNT_MAX;
		}
		/*
		else if(i == DTC_AVM_INDICAROT_LIGHT_TROUBLE)
		{
			dtc_set_circuit_fault_cnt_max = DTC_SET_LED_INDICATOR_ERR_CNT_MAX;
			dtc_clr_circuit_fault_cnt_max = DTC_CLR_LED_INDICATOR_ERR_CNT_MAX;
		}
		*/

        if(status[i])
        {
            dtc_status_record_cnt[i].dtc_create_cnt++;
            dtc_status_record_cnt[i].dtc_recover_cnt = 0;

            if(dtc_status_record_cnt[i].dtc_create_cnt >= dtc_set_circuit_fault_cnt_max)
            {
                if(TRUE == can_diag_dtc_record_body_enable_check())
                {
                    can_diag_dtc_status_report(i, DTC_TEST_FAILED, FALSE);
                }
                dtc_status_record_cnt[i].dtc_create_cnt = 0;
            }
        }
        else
        {
            dtc_status_record_cnt[i].dtc_recover_cnt++;
            
            if(dtc_status_record_cnt[i].dtc_recover_cnt >= dtc_clr_circuit_fault_cnt_max)
            {
                if(TRUE == can_diag_dtc_record_body_enable_check())
                {
                    can_diag_dtc_status_report(i, DTC_TEST_PASSED, FALSE);
                }
                dtc_status_record_cnt[i].dtc_recover_cnt = 0;
                
                dtc_status_record_cnt[i].dtc_create_cnt = 0;
            }        
        }
    }
}
#ifdef CANDTC_DIAG_DVR_STATUS
static void can_diag_dtc_dvr_err_monitor(void)
{
    U8 status = 0;

    GetCanDvrStatus(&status);    
    
    if(status!=0)
    {
        dtc_status_record_cnt[DTC_SD_FAIL].dtc_create_cnt++;
        dtc_status_record_cnt[DTC_SD_FAIL].dtc_recover_cnt = 0;

        if(dtc_status_record_cnt[DTC_SD_FAIL].dtc_create_cnt >= DTC_SET_DVR_FAULT_CNT_MAX)
        {
            if(TRUE == can_diag_dtc_record_body_enable_check())
            {
                can_diag_dtc_status_report(DTC_SD_FAIL, DTC_TEST_FAILED, FALSE);
            }
            dtc_status_record_cnt[DTC_SD_FAIL].dtc_create_cnt = 0;
        }
    }
    else
    {
        dtc_status_record_cnt[DTC_SD_FAIL].dtc_recover_cnt++;
        
        if(dtc_status_record_cnt[DTC_SD_FAIL].dtc_recover_cnt >= DTC_CLR_DVR_FAULT_CNT_MAX)
        {
            if(TRUE == can_diag_dtc_record_body_enable_check())
            {
                can_diag_dtc_status_report(DTC_SD_FAIL, DTC_TEST_PASSED, FALSE);
            }
            dtc_status_record_cnt[DTC_SD_FAIL].dtc_recover_cnt = 0;
            
            dtc_status_record_cnt[DTC_SD_FAIL].dtc_create_cnt = 0;
        }        
    }
}
#endif

#ifdef DIAG_TEMPERATURE_OPTION
/***********************************************************************
* FUNCTION    :  can_diag_dtc_front_switch_err_monitor
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
static void can_diag_dtc_temp_err_monitor(void)
{
    U8 status = 0 ;

    if(!Dtc_GetCanDiagTempDtc(&status))
    {
         if(TRUE == can_diag_dtc_record_body_enable_check())
         {
             can_diag_dtc_status_report(DTC_WORK_OVER_TEMPERATURE, DTC_TEST_INIT, FALSE);
             can_diag_dtc_status_report(DTC_WORK_BELOW_TEMPERATURE, DTC_TEST_INIT, FALSE);
         }
         return;
    }
    
    if(TEMP_TOO_HOT== status)
    {
        dtc_status_record_cnt[DTC_WORK_OVER_TEMPERATURE].dtc_create_cnt++;
        dtc_status_record_cnt[DTC_WORK_OVER_TEMPERATURE].dtc_recover_cnt = 0;

        if(dtc_status_record_cnt[DTC_WORK_OVER_TEMPERATURE].dtc_create_cnt >= DTC_SET_TEMP_FAULT_CNT_MAX)
        {
            if(TRUE == can_diag_dtc_record_body_enable_check())
            {
                can_diag_dtc_status_report(DTC_WORK_OVER_TEMPERATURE, DTC_TEST_FAILED, FALSE);
            }
            dtc_status_record_cnt[DTC_WORK_OVER_TEMPERATURE].dtc_create_cnt = 0;
        }
    }
    else
    {
        dtc_status_record_cnt[DTC_WORK_OVER_TEMPERATURE].dtc_recover_cnt++;
        
        if(dtc_status_record_cnt[DTC_WORK_OVER_TEMPERATURE].dtc_recover_cnt >= DTC_CLR_TEMP_FAULT_CNT_MAX)
        {
            if(TRUE == can_diag_dtc_record_body_enable_check())
            {
                can_diag_dtc_status_report(DTC_WORK_OVER_TEMPERATURE, DTC_TEST_PASSED, FALSE);
            }
            dtc_status_record_cnt[DTC_WORK_OVER_TEMPERATURE].dtc_recover_cnt = 0;
            
            dtc_status_record_cnt[DTC_WORK_OVER_TEMPERATURE].dtc_create_cnt = 0;
        }        
    }

    if(TEMP_TOO_LOW== status)
    {
        dtc_status_record_cnt[DTC_WORK_BELOW_TEMPERATURE].dtc_create_cnt++;
        dtc_status_record_cnt[DTC_WORK_BELOW_TEMPERATURE].dtc_recover_cnt = 0;

        if(dtc_status_record_cnt[DTC_WORK_BELOW_TEMPERATURE].dtc_create_cnt >= DTC_SET_TEMP_FAULT_CNT_MAX)
        {
            if(TRUE == can_diag_dtc_record_body_enable_check())
            {
                can_diag_dtc_status_report(DTC_WORK_BELOW_TEMPERATURE, DTC_TEST_FAILED, FALSE);
            }
            dtc_status_record_cnt[DTC_WORK_BELOW_TEMPERATURE].dtc_create_cnt = 0;
        }
    }
    else
    {
        dtc_status_record_cnt[DTC_WORK_BELOW_TEMPERATURE].dtc_recover_cnt++;
        
        if(dtc_status_record_cnt[DTC_WORK_BELOW_TEMPERATURE].dtc_recover_cnt >= DTC_CLR_TEMP_FAULT_CNT_MAX)
        {
            if(TRUE == can_diag_dtc_record_body_enable_check())
            {
                can_diag_dtc_status_report(DTC_WORK_BELOW_TEMPERATURE, DTC_TEST_PASSED, FALSE);
            }
            dtc_status_record_cnt[DTC_WORK_BELOW_TEMPERATURE].dtc_recover_cnt = 0;
            
            dtc_status_record_cnt[DTC_WORK_BELOW_TEMPERATURE].dtc_create_cnt = 0;
        }        
    }
}
#endif
#ifndef NOT_DIAG_SYS_POWER
/***********************************************************************
* FUNCTION    : void can_diag_dtc_bat_volt_monitor(void)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
static void can_diag_dtc_bat_volt_monitor(void)
{
		U16 SystemVol = 0;    
		E_SYSTEM_VOLTAGE_STATUS sPower_Can_ISR;
    CS_SIG_SyncReceive(SIG_VOLTAGEFAIL_STATUS, &SystemVol);
    sPower_Can_ISR = (E_SYSTEM_VOLTAGE_STATUS)SystemVol;
    /* ECU operation volt low monitor */
    if(sPower_Can_ISR<V_NORMAL) 
    {
        dtc_status_record_cnt[DTC_WORK_BELOW_VOLTAGE].dtc_create_cnt++;
        dtc_status_record_cnt[DTC_WORK_BELOW_VOLTAGE].dtc_recover_cnt = 0;

        if(dtc_status_record_cnt[DTC_WORK_BELOW_VOLTAGE].dtc_create_cnt >= DTC_SET_OP_VOLT_LOW_CNT_MAX)
        {
            if(TRUE == can_diag_dtc_record_op_volt_enable_check())
            {
                can_diag_dtc_status_report(DTC_WORK_BELOW_VOLTAGE, DTC_TEST_FAILED, FALSE);
            }
            dtc_status_record_cnt[DTC_WORK_BELOW_VOLTAGE].dtc_create_cnt = 0;
        }
    }
    else
    {
        dtc_status_record_cnt[DTC_WORK_BELOW_VOLTAGE].dtc_recover_cnt++;
        
        if(dtc_status_record_cnt[DTC_WORK_BELOW_VOLTAGE].dtc_recover_cnt >= DTC_CLR_OP_VOLT_LOW_CNT_MAX)
        {
            if(TRUE == can_diag_dtc_record_op_volt_enable_check())
            {
                can_diag_dtc_status_report(DTC_WORK_BELOW_VOLTAGE, DTC_TEST_PASSED, FALSE);
            }
            dtc_status_record_cnt[DTC_WORK_BELOW_VOLTAGE].dtc_recover_cnt = 0;
            
            dtc_status_record_cnt[DTC_WORK_BELOW_VOLTAGE].dtc_create_cnt = 0;
        }        
    }

    /* ECU operation volt high monitor */
    if(sPower_Can_ISR>V_NORMAL)
    {
        dtc_status_record_cnt[DTC_WORK_OVER_VOLTAGE].dtc_create_cnt++;
        dtc_status_record_cnt[DTC_WORK_OVER_VOLTAGE].dtc_recover_cnt = 0;

        if(dtc_status_record_cnt[DTC_WORK_OVER_VOLTAGE].dtc_create_cnt >= DTC_SET_OP_VOLT_HIGH_CNT_MAX)
        {
            if(TRUE == can_diag_dtc_record_op_volt_enable_check())
            {
                can_diag_dtc_status_report(DTC_WORK_OVER_VOLTAGE, DTC_TEST_FAILED, FALSE);
            }
            dtc_status_record_cnt[DTC_WORK_OVER_VOLTAGE].dtc_create_cnt = 0;
        }
    }
    else
    {
        dtc_status_record_cnt[DTC_WORK_OVER_VOLTAGE].dtc_recover_cnt++;
        
        if(dtc_status_record_cnt[DTC_WORK_OVER_VOLTAGE].dtc_recover_cnt >= DTC_CLR_OP_VOLT_HIGH_CNT_MAX)
        {
            if(TRUE == can_diag_dtc_record_op_volt_enable_check())
            {
                can_diag_dtc_status_report(DTC_WORK_OVER_VOLTAGE, DTC_TEST_PASSED, FALSE);
            }
            dtc_status_record_cnt[DTC_WORK_OVER_VOLTAGE].dtc_recover_cnt = 0;
            
            dtc_status_record_cnt[DTC_WORK_OVER_VOLTAGE].dtc_create_cnt = 0;
        }        
    }
    
}
#endif
#ifndef NOT_DIAG_CAN_TRANSCRIVER
/***********************************************************************
* FUNCTION    :  can_diag_dtc_transceiver_err_monitor
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
static void can_diag_dtc_transceiver_err_monitor(void)
{
    U16 bCanErrState = 0;
    CS_SIG_SyncReceive(SIG_CAN_TRANSIEVER_ERROR_STATUS,&bCanErrState);
    
 /*   if(bCanErrState&0x01)
    {
        dtc_status_record_cnt[DTC_CAN_TRANSCEIVER_ERROR].dtc_create_cnt++;
        dtc_status_record_cnt[DTC_CAN_TRANSCEIVER_ERROR].dtc_recover_cnt = 0;

        if(dtc_status_record_cnt[DTC_CAN_TRANSCEIVER_ERROR].dtc_create_cnt >= DTC_SET_TRANSCEIVER_ERR_CNT_MAX)
        {
            if(TRUE == can_diag_dtc_record_nm_enable_check())
            {
                can_diag_dtc_status_report(DTC_CAN_TRANSCEIVER_ERROR, DTC_TEST_FAILED, FALSE);
            }
            dtc_status_record_cnt[DTC_CAN_TRANSCEIVER_ERROR].dtc_create_cnt = 0;
        }
    }
    else
    {
        dtc_status_record_cnt[DTC_CAN_TRANSCEIVER_ERROR].dtc_recover_cnt++;
        
        if(dtc_status_record_cnt[DTC_CAN_TRANSCEIVER_ERROR].dtc_recover_cnt >= DTC_CLR_TRANSCEIVER_ERR_CNT_MAX)
        {
            if(TRUE == can_diag_dtc_record_nm_enable_check())
            {
                can_diag_dtc_status_report(DTC_CAN_TRANSCEIVER_ERROR, DTC_TEST_PASSED, FALSE);
            }
            dtc_status_record_cnt[DTC_CAN_TRANSCEIVER_ERROR].dtc_recover_cnt = 0;
            
            dtc_status_record_cnt[DTC_CAN_TRANSCEIVER_ERROR].dtc_create_cnt = 0;
        }        
    }*/
}
#endif

#ifdef DIAG_INNER_COMMUNICATION
static void can_diag_dtc_inner_communication_monitor(void)
{
	U16 SystemVol = 0;
    BOOL bcomErrStateWatchdog = 0; 
	BOOL bcomErrStateSpi = 0; 
	BOOL bSocConnectedStatus;
	 
    CS_SIG_SyncReceive(SIG_B_SOC_CONNECTED ,&bSocConnectedStatus);
    CS_SIG_SyncReceive(SIG_B_NAVICOMMERROR,&bcomErrStateWatchdog);
	CS_SIG_SyncReceive(SIG_VOLTAGEFAIL_STATUS, &SystemVol);

	if(!bSocConnectedStatus)
	{
		if(SystemVol == V_NORMAL)
		{
			if(SpiFailedCnt++ >= SPI_HANDSHAKE_TIMEOUT) 
			{
				bcomErrStateSpi = TRUE;
			}
		}
	}else{
			SpiFailedCnt = 0;
			bcomErrStateSpi = FALSE; 
	}
    
    if((bcomErrStateWatchdog)||(bcomErrStateSpi))
    {
        dtc_status_record_cnt[DTC_AVM_SYSTEM_ERROR].dtc_create_cnt++;
        dtc_status_record_cnt[DTC_AVM_SYSTEM_ERROR].dtc_recover_cnt = 0;

        if(dtc_status_record_cnt[DTC_AVM_SYSTEM_ERROR].dtc_create_cnt >= DTC_SET_INNERCOMMU_ERR_CNT_MAX)
        {
            if(TRUE == can_diag_dtc_record_body_enable_check())
            {
                can_diag_dtc_status_report(DTC_AVM_SYSTEM_ERROR, DTC_TEST_FAILED, FALSE);
            }
            dtc_status_record_cnt[DTC_AVM_SYSTEM_ERROR].dtc_create_cnt = 0;
        }
    }
    else
    {
        dtc_status_record_cnt[DTC_AVM_SYSTEM_ERROR].dtc_recover_cnt++;
        
        if(dtc_status_record_cnt[DTC_AVM_SYSTEM_ERROR].dtc_recover_cnt >= DTC_CLR_INNERCOMMU_ERR_CNT_MAX)
        {
            if(TRUE == can_diag_dtc_record_body_enable_check())
            {
                can_diag_dtc_status_report(DTC_AVM_SYSTEM_ERROR, DTC_TEST_PASSED, FALSE);
            }
            dtc_status_record_cnt[DTC_AVM_SYSTEM_ERROR].dtc_recover_cnt = 0;
            
            dtc_status_record_cnt[DTC_AVM_SYSTEM_ERROR].dtc_create_cnt = 0;
        }        
    }
}
#endif

#ifdef DIAG_AVM_ONOFF_SWITCH
static void can_diag_dtc_avm_onoff_key_monitor(void)
{
	static U16 bAvmOnoffKeyPressCount = 0; 
	BOOL bAvmOnoffKeySta=0;
    //CS_SIG_SyncReceive(SIG_B_NAVICOMMERROR,&bAvmOnoffKeySta);
	bAvmOnoffKeySta = GPIO_GetVal(GPIO_PORT_8, GPIO_PIN_1);

	if(bAvmOnoffKeySta)
	{
		bAvmOnoffKeyPressCount=0;
	}
	else
	{
		bAvmOnoffKeyPressCount++;
		if(bAvmOnoffKeyPressCount==0xffff)
		{
			bAvmOnoffKeyPressCount=750;
		}
	}
    if(bAvmOnoffKeyPressCount>=750)//15S
    {
        dtc_status_record_cnt[DTC_AVM_ONOFF_SWITCH_TROUBLE].dtc_create_cnt++;
        dtc_status_record_cnt[DTC_AVM_ONOFF_SWITCH_TROUBLE].dtc_recover_cnt = 0;

        if(dtc_status_record_cnt[DTC_AVM_ONOFF_SWITCH_TROUBLE].dtc_create_cnt >= DTC_SET_AVM_ONOFF_KEY_ERR_CNT_MAX)
        {
            if(TRUE == can_diag_dtc_record_body_enable_check())
            {
                can_diag_dtc_status_report(DTC_AVM_ONOFF_SWITCH_TROUBLE, DTC_TEST_FAILED, FALSE);
            }
            dtc_status_record_cnt[DTC_AVM_ONOFF_SWITCH_TROUBLE].dtc_create_cnt = 0;
        }
    }
    else
    {
        dtc_status_record_cnt[DTC_AVM_ONOFF_SWITCH_TROUBLE].dtc_recover_cnt++;
        
        if(dtc_status_record_cnt[DTC_AVM_ONOFF_SWITCH_TROUBLE].dtc_recover_cnt >= DTC_CLR_AVM_ONOFF_KEY_ERR_CNT_MAX)
        {
            if(TRUE == can_diag_dtc_record_body_enable_check())
            {
                can_diag_dtc_status_report(DTC_AVM_ONOFF_SWITCH_TROUBLE, DTC_TEST_PASSED, FALSE);
            }
            dtc_status_record_cnt[DTC_AVM_ONOFF_SWITCH_TROUBLE].dtc_recover_cnt = 0;
            
            dtc_status_record_cnt[DTC_AVM_ONOFF_SWITCH_TROUBLE].dtc_create_cnt = 0;
        }        
    }
}
#endif

#ifdef DIAG_LED_INDICATOR
static void can_diag_avm_indicator_light_monitor(void)
{
	U16 led_adc = 0;
	U8 bAVMTurnOnFlag = 0;
	U8 fault = 0;
	U8 SystemVolSta = 0;
	U8 bACCStatus = 0;
	static U8 AVMIndicatorErrCnt = 0;
	CS_SIG_AsyncReceive(SIG_AVM_LED_STATUS, &led_adc);
	CS_SIG_SyncReceive(SIG_AVM_TURNON_FLAG, &bAVMTurnOnFlag);
	CS_SIG_SyncReceive(SIG_VOLTAGEFAIL_STATUS, &SystemVolSta);
    CS_SIG_SyncReceive(SIG_ACCSTATUS, &bACCStatus);
	/* 
		Support hardware failure detection:
		AVM Indicator ON:  B+ And GND circuit
		AVM Indicator OFF: GND circuit
		Open circuit
	*/
	if((bACCStatus)&&(SystemVolSta == V_NORMAL))
	{
		if(((bAVMTurnOnFlag == 1)&&(led_adc < AD_LED_NORMAL_MIN)&&(led_adc > AD_LED_GND))
		  ||((bAVMTurnOnFlag == 0)&&(led_adc > AD_LED_NORMAL_MAX)))
		{
			AVMIndicatorErrCnt = 0;
		}
		else
		{	
			AVMIndicatorErrCnt++;
			if(AVMIndicatorErrCnt>=25)
			{
				AVMIndicatorErrCnt=25;
				bAVMTurnOnFlag = 0;
				CS_SIG_SyncSend(SIG_AVM_TURNON_FLAG, &bAVMTurnOnFlag);
			}
		}
	}
	
	if(AVMIndicatorErrCnt >= 25)
	{
		dtc_status_record_cnt[DTC_AVM_INDICAROT_LIGHT_TROUBLE].dtc_create_cnt++;
		dtc_status_record_cnt[DTC_AVM_INDICAROT_LIGHT_TROUBLE].dtc_recover_cnt = 0;

		if(dtc_status_record_cnt[DTC_AVM_INDICAROT_LIGHT_TROUBLE].dtc_create_cnt >= DTC_SET_LED_INDICATOR_ERR_CNT_MAX)
		{
			if(TRUE == can_diag_dtc_record_body_enable_check())
			{
				can_diag_dtc_status_report(DTC_AVM_INDICAROT_LIGHT_TROUBLE, DTC_TEST_FAILED, FALSE);
			}
			dtc_status_record_cnt[DTC_AVM_INDICAROT_LIGHT_TROUBLE].dtc_create_cnt = 0;
		}        		
	}
	else
	{
 		 dtc_status_record_cnt[DTC_AVM_INDICAROT_LIGHT_TROUBLE].dtc_recover_cnt++;
        
        if(dtc_status_record_cnt[DTC_AVM_INDICAROT_LIGHT_TROUBLE].dtc_recover_cnt >= DTC_CLR_LED_INDICATOR_ERR_CNT_MAX)
        {
            if(TRUE == can_diag_dtc_record_body_enable_check())
            {
                can_diag_dtc_status_report(DTC_AVM_INDICAROT_LIGHT_TROUBLE, DTC_TEST_PASSED, FALSE);
            }
            dtc_status_record_cnt[DTC_AVM_INDICAROT_LIGHT_TROUBLE].dtc_recover_cnt = 0;
            
            dtc_status_record_cnt[DTC_AVM_INDICAROT_LIGHT_TROUBLE].dtc_create_cnt = 0;
        }		
	}
}
#endif

#ifdef DIAG_AVM_CALIBRATION
static void can_diag_dtc_avm_calibration_monitor(void)
{
    if(EED_Calibration!=1)//15S
    {
        dtc_status_record_cnt[DTC_AVM_CALIBRATION_TROUBLE].dtc_create_cnt++;
        dtc_status_record_cnt[DTC_AVM_CALIBRATION_TROUBLE].dtc_recover_cnt = 0;

        if(dtc_status_record_cnt[DTC_AVM_CALIBRATION_TROUBLE].dtc_create_cnt >= DTC_SET_AVM_CALIBRATION_ERR_CNT_MAX)
        {
            if(TRUE == can_diag_dtc_record_body_enable_check())
            {
                can_diag_dtc_status_report(DTC_AVM_CALIBRATION_TROUBLE, DTC_TEST_FAILED, FALSE);
            }
            dtc_status_record_cnt[DTC_AVM_CALIBRATION_TROUBLE].dtc_create_cnt = 0;
        }
    }
    else
    {
        dtc_status_record_cnt[DTC_AVM_CALIBRATION_TROUBLE].dtc_recover_cnt++;
        
        if(dtc_status_record_cnt[DTC_AVM_CALIBRATION_TROUBLE].dtc_recover_cnt >= DTC_CLR_AVM_CALIBRATION_ERR_CNT_MAX)
        {
            if(TRUE == can_diag_dtc_record_body_enable_check())
            {
                can_diag_dtc_status_report(DTC_AVM_CALIBRATION_TROUBLE, DTC_TEST_PASSED, FALSE);
            }
            dtc_status_record_cnt[DTC_AVM_CALIBRATION_TROUBLE].dtc_recover_cnt = 0;
            
            dtc_status_record_cnt[DTC_AVM_CALIBRATION_TROUBLE].dtc_create_cnt = 0;
        }        
    }
}
#endif






#ifndef NOT_DIAG_CAN_BUSOFF
/***********************************************************************
* FUNCTION    :  can_diag_dtc_bus_off_monitor
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
static void can_diag_dtc_bus_off_monitor(void)
{
    if(dtc_bus_off_counter>=BUS_OFF_CONFIRM_TIMES)    
    {
        dtc_status_record_cnt[DTC_CAN_BUS_ERROR].dtc_create_cnt++;
        dtc_status_record_cnt[DTC_CAN_BUS_ERROR].dtc_recover_cnt = 0;

        if(dtc_status_record_cnt[DTC_CAN_BUS_ERROR].dtc_create_cnt >= DTC_SET_BUS_OFF_CNT_MAX)
        {
            if((TRUE == can_diag_dtc_record_nm_enable_check())&&(bDTCBusoffRecordSta))
            {
                can_diag_dtc_status_report(DTC_CAN_BUS_ERROR, DTC_TEST_FAILED, FALSE);
            }
            dtc_status_record_cnt[DTC_CAN_BUS_ERROR].dtc_create_cnt = 0;
        }
    }
    else
    {
        dtc_status_record_cnt[DTC_CAN_BUS_ERROR].dtc_recover_cnt++;
        
        if(dtc_status_record_cnt[DTC_CAN_BUS_ERROR].dtc_recover_cnt >= DTC_CLR_BUS_OFF_CNT_MAX)
        {
            if((TRUE == can_diag_dtc_record_nm_enable_check())&&(bDTCBusoffRecordSta))
            {
                can_diag_dtc_status_report(DTC_CAN_BUS_ERROR, DTC_TEST_PASSED, FALSE);
            }
            dtc_status_record_cnt[DTC_CAN_BUS_ERROR].dtc_recover_cnt = 0;
            
            dtc_status_record_cnt[DTC_CAN_BUS_ERROR].dtc_create_cnt = 0;
        }        
    }
}
#endif



/***********************************************************************
* FUNCTION    : void can_diag_dtc_status_report(U8 dtc_code, U16 dtc_status_mask, BOOL write_delay)
* DESCRIPTION : 
* INPUTS      : 
* RETURN      : 
***********************************************************************/
static void can_diag_dtc_status_report(U8 dtc_code, U16 dtc_status_mask, BOOL write_delay)
{
    BOOL dtc_staus_changed = FALSE;
     
    if((dtc_code < DTC_CODE_MAX_NUM)
       && ((TRUE == SYS_control_dtc_setting_check())
       ||(DTC_TEST_CLEAR == dtc_status_mask) /* $85 can not prohibit $14 */
       ))
    {
        if(TRUE == can_diag_dtc_proc_test_failed(dtc_code, dtc_status_mask))
        {
            dtc_staus_changed = TRUE;
        }
        
        if(TRUE == can_diag_dtc_proc_test_failed_operation(dtc_code, dtc_status_mask))
        {
            dtc_staus_changed = TRUE;
        }
        
        if(TRUE == can_diag_dtc_proc_pending_DTC(dtc_code, dtc_status_mask))
        {
            dtc_staus_changed = TRUE;
        }
        
        if(TRUE == can_diag_dtc_proc_confirmed_DTC(dtc_code, dtc_status_mask))
        {
            dtc_staus_changed = TRUE;
            bDtcDataNeedSendToEep = TRUE;
        }
        
        if(TRUE == can_diag_dtc_proc_test_not_completed_since_clear(dtc_code, dtc_status_mask))
        {
            dtc_staus_changed = TRUE;
        }
        
        if(TRUE == can_diag_dtc_proc_test_failed_since_clear(dtc_code, dtc_status_mask))
        {
            dtc_staus_changed = TRUE;
        }
        
        if(TRUE == can_diag_dtc_proc_not_completed_operation(dtc_code, dtc_status_mask))
        {
            dtc_staus_changed = TRUE;
        }
        
        if(TRUE == can_diag_dtc_proc_warning_indicator_requested(dtc_code, dtc_status_mask))
        {
            dtc_staus_changed = TRUE;
        }
        
        if((TRUE == dtc_staus_changed) && (FALSE == write_delay))
        {}
    }
}

/***********************************************************************
* FUNCTION    : void can_diag_dtc_sv14_clear_start(void)
* DESCRIPTION : 
* INPUTS      : 
* RETURN      : 
***********************************************************************/
void CanDiagDtc_sv14_clear_start(void)
{
    /* do not care about last time, just reset the whole clear things */
    dtc_status_svc14_clear_counter = DTC_STATUS_SVC14_CLEAR_START; /* clear begin */

	//DTC occurrence counter, aging counter and aged counter could be reset by service 14 hex.
	_memset(dtc_status_occurrence_cnt,DTC_STATUS_OCCURRENCE_CNT_RESET,DTC_CODE_MAX_NUM);
    _memset(dtc_status_aging_cnt,DTC_STATUS_AGING_CNT_RESET,DTC_CODE_MAX_NUM);
	//_memset(dtc_status_aged_cnt,DTC_STATUS_AGED_CNT_RESET,DTC_CODE_MAX_NUM);
	_memset(&dtc_status_fid_data,0,DTC_CODE_MAX_NUM);
	_memset(&dtc_snapshot_record,0,sizeof(DTC_SNAPSHOT_RECORD_IDENTIFIERS)*DTC_CODE_MAX_NUM);

    /* Adjust dtc record enable mask */
    can_diag_dtc_record_enable_adjust();
}

/***********************************************************************
* FUNCTION    : void can_diag_dtc_sv14_clear_start(void)
* DESCRIPTION : 
* INPUTS      : 
* RETURN      : 
***********************************************************************/
void CanDiagDtc_sv14_clear_network_grp_start(void)
{
    /* do not care about last time, just reset the whole clear things */
    dtc_status_svc14_clear_counter = DTC_NETWORK_GRP_START; /* clear begin */

	_memset(&dtc_status_occurrence_cnt[DTC_NETWORK_GRP_START],DTC_STATUS_OCCURRENCE_CNT_RESET,DTC_CODE_MAX_NUM-DTC_NETWORK_GRP_START);
    _memset(&dtc_status_aging_cnt[DTC_NETWORK_GRP_START],DTC_STATUS_AGING_CNT_RESET,DTC_CODE_MAX_NUM-DTC_NETWORK_GRP_START);
	//_memset(dtc_status_aged_cnt[DTC_NETWORK_GRP_START],DTC_STATUS_AGED_CNT_RESET,DTC_CODE_MAX_NUM-DTC_NETWORK_GRP_START);
	_memset(&dtc_status_fid_data,0,DTC_CODE_MAX_NUM-DTC_NETWORK_GRP_START);
	_memset(&dtc_snapshot_record[DTC_NETWORK_GRP_START],0,sizeof(DTC_SNAPSHOT_RECORD_IDENTIFIERS)*(DTC_CODE_MAX_NUM-DTC_NETWORK_GRP_START));

    /* Adjust dtc record enable mask */
    can_diag_dtc_record_enable_adjust();
}



/***********************************************************************
* FUNCTION    : BOOL can_diag_dtc_status_svc14_clear_all(void)
* DESCRIPTION : Do not clear all the dtc status at the same time, it would cost worse CPU/thread load,
*                         So just separate the clear action, Called by desc_delay_service_task to do this job.
* INPUTS      : 
* RETURN      : 
***********************************************************************/
BOOL CanDiagDtc_status_svc14_clear_all(void)
{
    BOOL clear_finished;

    if(dtc_status_svc14_clear_counter < DTC_CODE_MAX_NUM)
    {
        can_diag_dtc_status_report(dtc_status_svc14_clear_counter, DTC_TEST_CLEAR, FALSE);
		
        dtc_status_svc14_clear_counter++;    
        clear_finished = FALSE;
    }
    else
    {
        if(DTC_CODE_MAX_NUM == dtc_status_svc14_clear_counter) /* avoid being called frequently */
        {
            dtc_status_svc14_clear_counter = DTC_STATUS_SVC14_CLEAR_FINISHED; /* clear finished */
            
            /* Adjust dtc record enable mask */
            can_diag_dtc_record_enable_adjust();    
        }
        
        clear_finished = TRUE;
    }
    
    return (clear_finished);
}

/***********************************************************************
* FUNCTION    : BOOL can_diag_dtc_status_svc14_clear_finished(void)
* DESCRIPTION : 
*                         
* INPUTS      : 
* RETURN      : 
***********************************************************************/
BOOL can_diag_dtc_status_svc14_clear_finished(void)
{
    return((DTC_STATUS_SVC14_CLEAR_FINISHED == dtc_status_svc14_clear_counter) ? 1 : 0);
}


/***********************************************************************
* FUNCTION    : BOOL can_diag_dtc_proc_test_failed(U8 dtc_code, U16 dtc_status_mask)
* DESCRIPTION : 
* INPUTS      : 
* RETURN      : 
***********************************************************************/
static BOOL can_diag_dtc_proc_test_failed(U8 dtc_code, U16 dtc_status_mask)
{
    BOOL dtc_staus_changed = FALSE;

    if(dtc_code < DTC_CODE_MAX_NUM)
    {
        if(DTC_STATUS_BIT0_MASK_TF&DTC_STATUS_AVAILABILITY_MASK) /* dtc status bit supported check */
        {
            if((dtc_status_mask&DTC_TEST_INIT) != 0)
            {
                if(TRUE == dtc_status_record[dtc_code].dtc_status.status_bits.testFailed)
                {
                    dtc_status_record[dtc_code].dtc_status.status_bits.testFailed = FALSE;
                    dtc_staus_changed = TRUE;
                }
            }

            if((dtc_status_mask&DTC_TEST_PASSED) != 0)
            {
                if(TRUE == dtc_status_record[dtc_code].dtc_status.status_bits.testFailed)
                {
                    dtc_status_record[dtc_code].dtc_status.status_bits.testFailed = FALSE;
                    dtc_staus_changed = TRUE;
                }
            }

            if((dtc_status_mask&DTC_TEST_FAILED) != 0)
            {
                if(FALSE == dtc_status_record[dtc_code].dtc_status.status_bits.testFailed)
                {
                    dtc_status_record[dtc_code].dtc_status.status_bits.testFailed = TRUE;
					#ifdef DTC_AGING_COUNTER
					if(dtc_status_occurrence_cnt[dtc_code]!=DTC_STATUS_OCCURRENCE_CNT_MAX)
					{
						dtc_status_occurrence_cnt[dtc_code]++;			
					}
					//error had maturated, DTC aging counter will be reset to 0.
	                if(dtc_status_aging_cnt[dtc_code]!=DTC_STATUS_AGING_CNT_RESET)
	                {
	                    dtc_status_aging_cnt[dtc_code] = DTC_STATUS_AGING_CNT_RESET;
	                }
	                #endif
					//record snapshoot
					can_diag_record_snapshoot_to_DTC(dtc_code);
					can_diag_record_fid_to_DTC(dtc_code);
					
					bDtcDataNeedSendToEep = TRUE;
                    dtc_staus_changed = TRUE;
                }
            }

            if((dtc_status_mask&DTC_TEST_CLEAR) != 0)
            {
                dtc_status_record_cnt[dtc_code].dtc_create_cnt = 0;
                dtc_status_record_cnt[dtc_code].dtc_recover_cnt = 0;

                if(TRUE == dtc_status_record[dtc_code].dtc_status.status_bits.testFailed)
                {
                    dtc_status_record[dtc_code].dtc_status.status_bits.testFailed = FALSE;
                    dtc_staus_changed = TRUE;
                }
            }

            if((dtc_status_mask&DTC_TEST_NEW_OPR) != 0)
            {
                /* nothing to do */
            }
        }
        else /* dtc status bit not support, set to a default value if needed */
        {
            /* please adapter the default value according to SPEC. */
            if(TRUE == dtc_status_record[dtc_code].dtc_status.status_bits.testFailed)
            {
                dtc_status_record[dtc_code].dtc_status.status_bits.testFailed = FALSE;
                dtc_staus_changed = TRUE;
            }
        }
    }

    return(dtc_staus_changed);
}

/***********************************************************************
* FUNCTION    : BOOL can_diag_dtc_proc_test_failed_operation(U8 dtc_code, U16 dtc_status_mask)
* DESCRIPTION : 
* INPUTS      : 
* RETURN      : 
***********************************************************************/
static BOOL can_diag_dtc_proc_test_failed_operation(U8 dtc_code, U16 dtc_status_mask)
{
    BOOL dtc_staus_changed = FALSE;

    if(dtc_code < DTC_CODE_MAX_NUM)
    {
        if(DTC_STATUS_BIT1_MASK_TFTOC&DTC_STATUS_AVAILABILITY_MASK) /* dtc status bit supported check */
        {
            if((dtc_status_mask&DTC_TEST_INIT) != 0)
            {
                /* nothing to do */
            }

            if((dtc_status_mask&DTC_TEST_PASSED) != 0)
            {
                /* nothing to do */
            }
            
            if((dtc_status_mask&DTC_TEST_FAILED) != 0)
            {
                if(FALSE == dtc_status_record[dtc_code].dtc_status.status_bits.testFailedThisOperationCycle)
                {
                    dtc_status_record[dtc_code].dtc_status.status_bits.testFailedThisOperationCycle = TRUE;
                    dtc_staus_changed = TRUE;
                }
            }
                
            if((dtc_status_mask&DTC_TEST_CLEAR) != 0)
            {
                dtc_status_record_cnt[dtc_code].dtc_create_cnt = 0;
                dtc_status_record_cnt[dtc_code].dtc_recover_cnt = 0;
                
                if(TRUE == dtc_status_record[dtc_code].dtc_status.status_bits.testFailedThisOperationCycle)
                {
                    dtc_status_record[dtc_code].dtc_status.status_bits.testFailedThisOperationCycle = FALSE;
                    dtc_staus_changed = TRUE;
                }
            }

            if((dtc_status_mask&DTC_TEST_NEW_OPR) != 0)
            {
                if(TRUE == dtc_status_record[dtc_code].dtc_status.status_bits.testFailedThisOperationCycle)
                {
                    dtc_status_record[dtc_code].dtc_status.status_bits.testFailedThisOperationCycle = FALSE;
                    dtc_staus_changed = TRUE;
                }
            }      
        }
        else /* dtc status bit not support, set to a default value if needed */
        {
            /* please adapter the default value according to SPEC. */
            if(TRUE == dtc_status_record[dtc_code].dtc_status.status_bits.testFailedThisOperationCycle)
            {
                dtc_status_record[dtc_code].dtc_status.status_bits.testFailedThisOperationCycle = FALSE;
                dtc_staus_changed = TRUE;
            }
        }
    }

    return(dtc_staus_changed);
}

/***********************************************************************
* FUNCTION    : BOOL can_diag_dtc_proc_pending_DTC(U8 dtc_code, U16 dtc_status_mask)
* DESCRIPTION : 
* INPUTS      : 
* RETURN      : 
***********************************************************************/
static BOOL can_diag_dtc_proc_pending_DTC(U8 dtc_code, U16 dtc_status_mask)
{
    BOOL dtc_staus_changed = FALSE;

    if(dtc_code < DTC_CODE_MAX_NUM)
    {
        if(DTC_STATUS_BIT2_MASK_PDTC&DTC_STATUS_AVAILABILITY_MASK) /* dtc status bit supported check */
        {
            if((dtc_status_mask&DTC_TEST_INIT) != 0)
            {
                /* nothing to do */
            }

            if((dtc_status_mask&DTC_TEST_PASSED) != 0)
            {
                /* too complex!!!
                *To be continued......
                */
            }

            if((dtc_status_mask&DTC_TEST_FAILED) != 0)
            {
                if(FALSE == dtc_status_record[dtc_code].dtc_status.status_bits.pendingDTC)
                {
                dtc_status_record[dtc_code].dtc_status.status_bits.pendingDTC = TRUE;
                dtc_staus_changed = TRUE;
                }
            }

            if((dtc_status_mask&DTC_TEST_CLEAR) != 0)
            {
                dtc_status_record_cnt[dtc_code].dtc_create_cnt = 0;
                dtc_status_record_cnt[dtc_code].dtc_recover_cnt = 0;

                if(TRUE == dtc_status_record[dtc_code].dtc_status.status_bits.pendingDTC)
                {
                dtc_status_record[dtc_code].dtc_status.status_bits.pendingDTC = FALSE;
                dtc_staus_changed = TRUE;
                }
            }

            if((dtc_status_mask&DTC_TEST_NEW_OPR) != 0)
            {
                /* nothing to do */
            }
                  
        }
        else /* dtc status bit not support, set to a default value if needed */
        {
            /* please adapter the default value according to SPEC. */
            if(TRUE == dtc_status_record[dtc_code].dtc_status.status_bits.pendingDTC)
            {
                dtc_status_record[dtc_code].dtc_status.status_bits.pendingDTC = FALSE;
                dtc_staus_changed = TRUE;
            }
        }
    }

    return(dtc_staus_changed);
}


/***********************************************************************
* FUNCTION    : BOOL can_diag_dtc_proc_confirmed_DTC(U8 dtc_code, U16 dtc_status_mask)
* DESCRIPTION : 
* INPUTS      : 
* RETURN      : 
***********************************************************************/
static BOOL can_diag_dtc_proc_confirmed_DTC(U8 dtc_code, U16 dtc_status_mask)
	{
    BOOL dtc_staus_changed = FALSE;

    if(dtc_code < DTC_CODE_MAX_NUM)
    {
        if(DTC_STATUS_BIT3_MASK_CDTC&DTC_STATUS_AVAILABILITY_MASK) /* dtc status bit supported check */
        {
            if((dtc_status_mask&DTC_TEST_INIT) != 0)
            {
                /* nothing to do */
            }

            if((dtc_status_mask&DTC_TEST_PASSED) != 0)
            {
            #ifdef DTC_AGING_COUNTER
                if(bSetClearHistoryFaultCntFlag[dtc_code])
                {
                    bSetClearHistoryFaultCntFlag[dtc_code] = FALSE;
                    if(dtc_status_record[dtc_code].dtc_status.status_bits.confirmedDTC)
                    {
                        if(dtc_status_aging_cnt[dtc_code]>=DTC_STATUS_AGING_CNT_HEALING)
                        {
                            dtc_status_record[dtc_code].dtc_status.status_bits.confirmedDTC = FALSE;
							//DTC aging counter and DTC occurrence counter will be reset to 0 by self healing
                            dtc_status_aging_cnt[dtc_code] = DTC_STATUS_AGING_CNT_RESET;
							dtc_status_occurrence_cnt[dtc_code] = DTC_STATUS_OCCURRENCE_CNT_RESET;

							//When the aging counter is up to self healing value, DTC will be moved out from current memory
							can_diag_dtc_status_report(dtc_code, DTC_TEST_CLEAR, FALSE);
							
							if(dtc_status_aged_cnt[dtc_code]<DTC_STATUS_AGED_CNT_MAX)
							{
								//When the DTC's aging counter is up to set-value, Aged counter will be increased by 1.
								dtc_status_aged_cnt[dtc_code]++;
							}
							else
							{
								//If the aged counter is up to 255, it will keep to 255.
								dtc_status_aged_cnt[dtc_code] = DTC_STATUS_AGED_CNT_MAX;
							}
                            dtc_staus_changed = TRUE;
                        }
                        else
                        {
                        	//ECU error never occur during the last whole operation cycle, driving cycle, or warm-up cycle.The DTC aging
							//counter value shall be increased by 1.
                            dtc_status_aging_cnt[dtc_code]++;
                            dtc_staus_changed = TRUE;
                        }
                    }
                }
            #endif
            }
                
            if((dtc_status_mask&DTC_TEST_FAILED) != 0)
            {
                if(FALSE == dtc_status_record[dtc_code].dtc_status.status_bits.confirmedDTC)
                {
                	//If the DTC status "confirmedDTC" has been change from 0 to 1, aging counter starts as 0.
                	dtc_status_aging_cnt[dtc_code] = DTC_STATUS_AGING_CNT_RESET;
                    dtc_status_record[dtc_code].dtc_status.status_bits.confirmedDTC = TRUE;
                    dtc_staus_changed = TRUE;
                }
            }
                
            if((dtc_status_mask&DTC_TEST_CLEAR) != 0)
            {
                dtc_status_record_cnt[dtc_code].dtc_create_cnt = 0;
                dtc_status_record_cnt[dtc_code].dtc_recover_cnt = 0;
                
                if(TRUE == dtc_status_record[dtc_code].dtc_status.status_bits.confirmedDTC)
                {
                    dtc_status_record[dtc_code].dtc_status.status_bits.confirmedDTC = FALSE;
                    dtc_staus_changed = TRUE;
                }
            }
            
            if((dtc_status_mask&DTC_TEST_NEW_OPR) != 0)
            {
                /* nothing to do */
            }        
        }
        else /* dtc status bit support, set to a default value if needed */
        {
            /* please adapter the default value according to SPEC. */
            if(TRUE == dtc_status_record[dtc_code].dtc_status.status_bits.confirmedDTC)
            {
                dtc_status_record[dtc_code].dtc_status.status_bits.confirmedDTC = FALSE;
                dtc_staus_changed = TRUE;
            }
        }
    }

    return(dtc_staus_changed);
}

/***********************************************************************
* FUNCTION    : BOOL can_diag_dtc_proc_test_not_completed_since_clear(U8 dtc_code, U16 dtc_status_mask)
* DESCRIPTION : 
* INPUTS      : 
* RETURN      : 
***********************************************************************/
static BOOL can_diag_dtc_proc_test_not_completed_since_clear(U8 dtc_code, U16 dtc_status_mask)
{
    BOOL dtc_staus_changed = FALSE;

    if(dtc_code < DTC_CODE_MAX_NUM)
    {
        if(DTC_STATUS_BIT4_MASK_TNCSLC&DTC_STATUS_AVAILABILITY_MASK) /* dtc status bit supported check */
        {
            if((dtc_status_mask&DTC_TEST_INIT) != 0)
            {
                if(FALSE == dtc_status_record[dtc_code].dtc_status.status_bits.testNotCompletedSinceLastClear)
                {
                    dtc_status_record[dtc_code].dtc_status.status_bits.testNotCompletedSinceLastClear = TRUE;
                    dtc_staus_changed = TRUE;
                }
            }

            if((dtc_status_mask&DTC_TEST_PASSED) != 0)
            {
                if(TRUE == dtc_status_record[dtc_code].dtc_status.status_bits.testNotCompletedSinceLastClear)
                {
                    dtc_status_record[dtc_code].dtc_status.status_bits.testNotCompletedSinceLastClear = FALSE;
                    dtc_staus_changed = TRUE;
                }
            }
                
            if((dtc_status_mask&DTC_TEST_FAILED) != 0)
            {
                if(TRUE == dtc_status_record[dtc_code].dtc_status.status_bits.testNotCompletedSinceLastClear)
                {
                    dtc_status_record[dtc_code].dtc_status.status_bits.testNotCompletedSinceLastClear = FALSE;
                    dtc_staus_changed = TRUE;
                }
            }
                
            if((dtc_status_mask&DTC_TEST_CLEAR) != 0)
            {
                dtc_status_record_cnt[dtc_code].dtc_create_cnt = 0;
                dtc_status_record_cnt[dtc_code].dtc_recover_cnt = 0;
                
                if(FALSE == dtc_status_record[dtc_code].dtc_status.status_bits.testNotCompletedSinceLastClear)
                {
                    dtc_status_record[dtc_code].dtc_status.status_bits.testNotCompletedSinceLastClear = TRUE;
                    dtc_staus_changed = TRUE;
                }
            }

            if((dtc_status_mask&DTC_TEST_NEW_OPR) != 0)
            {
                /* nothing to do */
            } 
  
        }
        else /* dtc status bit support, set to a default value if needed */
        {
            /* please adapter the default value according to SPEC. */
            if(TRUE == dtc_status_record[dtc_code].dtc_status.status_bits.testNotCompletedSinceLastClear)
            {
                dtc_status_record[dtc_code].dtc_status.status_bits.testNotCompletedSinceLastClear = FALSE;
                dtc_staus_changed = TRUE;
            }
        }
    }

    return(dtc_staus_changed);
}

/***********************************************************************
* FUNCTION    : BOOL can_diag_dtc_proc_test_failed_since_clear(U8 dtc_code, U16 dtc_status_mask)
* DESCRIPTION : 
* INPUTS      : 
* RETURN      : 
***********************************************************************/
static BOOL can_diag_dtc_proc_test_failed_since_clear(U8 dtc_code, U16 dtc_status_mask)
{
    BOOL dtc_staus_changed = FALSE;

    if(dtc_code < DTC_CODE_MAX_NUM)
    {
        if(DTC_STATUS_BIT5_MASK_TFSLC&DTC_STATUS_AVAILABILITY_MASK) /* dtc status bit supported check */
        {
            if((dtc_status_mask&DTC_TEST_INIT) != 0)
            {
                if(TRUE == dtc_status_record[dtc_code].dtc_status.status_bits.testFailedSinceLastClear)
                {
                    dtc_status_record[dtc_code].dtc_status.status_bits.testFailedSinceLastClear = FALSE;
                    dtc_staus_changed = TRUE;
                }
            }
            
            if((dtc_status_mask&DTC_TEST_PASSED) != 0)
            {
                /* nothing to do */
            }
                
            if((dtc_status_mask&DTC_TEST_FAILED) != 0)
            {
                if(FALSE == dtc_status_record[dtc_code].dtc_status.status_bits.testFailedSinceLastClear)
                {
                    dtc_status_record[dtc_code].dtc_status.status_bits.testFailedSinceLastClear = TRUE;
                    dtc_staus_changed = TRUE;
                }
            }
                
            if((dtc_status_mask&DTC_TEST_CLEAR) != 0)
            {
                dtc_status_record_cnt[dtc_code].dtc_create_cnt = 0;
                dtc_status_record_cnt[dtc_code].dtc_recover_cnt = 0;
                
                if(TRUE == dtc_status_record[dtc_code].dtc_status.status_bits.testFailedSinceLastClear)
                {
                    dtc_status_record[dtc_code].dtc_status.status_bits.testFailedSinceLastClear = FALSE;
                    dtc_staus_changed = TRUE;
                }
            }

            if((dtc_status_mask&DTC_TEST_NEW_OPR) != 0)
            {
                /* nothing to do */
            }
 
        }
        else /* dtc status bit support, set to a default value if needed */
        {
            /* please adapter the default value according to SPEC. */
            if(TRUE == dtc_status_record[dtc_code].dtc_status.status_bits.testFailedSinceLastClear)
            {
                dtc_status_record[dtc_code].dtc_status.status_bits.testFailedSinceLastClear = FALSE;
                dtc_staus_changed = TRUE;
            }
        }
    }

    return(dtc_staus_changed);
}

/***********************************************************************
* FUNCTION    : BOOL can_diag_dtc_proc_not_completed_operation(U8 dtc_code, U16 dtc_status_mask)
* DESCRIPTION : 
* INPUTS      : 
* RETURN      : 
***********************************************************************/
static BOOL can_diag_dtc_proc_not_completed_operation(U8 dtc_code, U16 dtc_status_mask)
{
    BOOL dtc_staus_changed = FALSE;

    if(dtc_code < DTC_CODE_MAX_NUM)
    {
        if(DTC_STATUS_BIT6_MASK_TNCTOC&DTC_STATUS_AVAILABILITY_MASK) /* dtc status bit supported check */
        {
            if((dtc_status_mask&DTC_TEST_INIT) != 0)
            {
                if(FALSE == dtc_status_record[dtc_code].dtc_status.status_bits.testNotCompletedThisOperationCycle)
                {
                    dtc_status_record[dtc_code].dtc_status.status_bits.testNotCompletedThisOperationCycle = TRUE;
                    dtc_staus_changed = TRUE;
                }
            }

            if((dtc_status_mask&DTC_TEST_PASSED) != 0)
            {
                if(TRUE == dtc_status_record[dtc_code].dtc_status.status_bits.testNotCompletedThisOperationCycle)
                {
                    dtc_status_record[dtc_code].dtc_status.status_bits.testNotCompletedThisOperationCycle = FALSE;
                    dtc_staus_changed = TRUE;
                }
            }
            
            if((dtc_status_mask&DTC_TEST_FAILED) != 0)
            {
                if(TRUE == dtc_status_record[dtc_code].dtc_status.status_bits.testNotCompletedThisOperationCycle)
                {
                    dtc_status_record[dtc_code].dtc_status.status_bits.testNotCompletedThisOperationCycle = FALSE;
                    dtc_staus_changed = TRUE;
                }
            }
            
            if((dtc_status_mask&DTC_TEST_CLEAR) != 0)
            {
                dtc_status_record_cnt[dtc_code].dtc_create_cnt = 0;
                dtc_status_record_cnt[dtc_code].dtc_recover_cnt = 0;
                
                if(FALSE == dtc_status_record[dtc_code].dtc_status.status_bits.testNotCompletedThisOperationCycle)
                {
                    dtc_status_record[dtc_code].dtc_status.status_bits.testNotCompletedThisOperationCycle = TRUE;
                    dtc_staus_changed = TRUE;
                }
            }

            if((dtc_status_mask&DTC_TEST_NEW_OPR) != 0)
            {
                if(FALSE == dtc_status_record[dtc_code].dtc_status.status_bits.testNotCompletedThisOperationCycle)
                {
                    dtc_status_record[dtc_code].dtc_status.status_bits.testNotCompletedThisOperationCycle = TRUE;
                    dtc_staus_changed = TRUE;
                }
            }
        }
        else /* dtc status bit support, set to a default value if needed */
        {
            /* please adapter the default value according to SPEC. */
            if(TRUE == dtc_status_record[dtc_code].dtc_status.status_bits.testNotCompletedThisOperationCycle)
            {
                dtc_status_record[dtc_code].dtc_status.status_bits.testNotCompletedThisOperationCycle = FALSE;
                dtc_staus_changed = TRUE;
            }
        }
    }

    return(dtc_staus_changed);
}


/***********************************************************************
* FUNCTION    : BOOL can_diag_dtc_proc_warning_indicator_requested(U8 dtc_code, U16 dtc_status_mask)
* DESCRIPTION : 
* INPUTS      : 
* RETURN      : 
***********************************************************************/
static BOOL can_diag_dtc_proc_warning_indicator_requested(U8 dtc_code, U16 dtc_status_mask)
{
    BOOL dtc_staus_changed = FALSE;

    if(dtc_code < DTC_CODE_MAX_NUM)
    {
        if(DTC_STATUS_BIT7_MASK_WIR&DTC_STATUS_AVAILABILITY_MASK) /* dtc status bit supported check */
        {
        /* Not implement in our system yet */
            if((dtc_status_mask&DTC_TEST_INIT) != 0)
            {
                 /*  Not implement yet */
            }

            if((dtc_status_mask&DTC_TEST_PASSED) != 0)
            {
                 /*  Not implement yet */
            }
            
            if((dtc_status_mask&DTC_TEST_FAILED) != 0)
            {
                 /*  Not implement yet */
            }
            
            if((dtc_status_mask&DTC_TEST_CLEAR) != 0)
            {
                dtc_status_record_cnt[dtc_code].dtc_create_cnt = 0;
                dtc_status_record_cnt[dtc_code].dtc_recover_cnt = 0;

                 /*  Not implement yet */
            }

            if((dtc_status_mask&DTC_TEST_NEW_OPR) != 0)
            {
                 /*  Not implement yet */
            }    
        }
        else
        {
            /* please adapter the default value according to SPEC. */
            if(TRUE == dtc_status_record[dtc_code].dtc_status.status_bits.warningIndicatorRequested)
            {
                dtc_status_record[dtc_code].dtc_status.status_bits.warningIndicatorRequested = FALSE;
                dtc_staus_changed = TRUE;
            }
        }
    }

    return(dtc_staus_changed);
}


#ifdef DIAG_NM_TIMEOUT_NOT_USE_IL_TIMEOUT_FLAG
BOOL CanDiag_GetNMTimeOutFlag(U8 nodeindex)
{
    return(bMessageTimeOutStatus[nodeindex]);
}

void ResetCanDiagTimeoutState(void)
{
    U8 i;
    for(i = 0;i<MESSAGE_TIMEOUT_TYPE_NUMBER;i++)
    {
        uMessageTimeOutCnt[i] = uMessageTimeoutStartTime[i];
        bMessageTimeOutStatus[i] = FALSE ;
    }

    for(i = 0;i<GW_MESSAGE_MONITOR_MAX;i++)
    {
        uMessageTimeOutCntForGWNodeLost[i] = 25;
        bMessageLostStaForGWNodeLost[i] = FALSE ;
    }
	
    for(i = 0;i<ESP_MESSAGE_MONITOR_MAX;i++)
    {
        uMessageTimeOutCntForESPMissing[i] = 25;
        bMessageLostForESPMissing[i] = FALSE ;
    }

    for(i = 0;i<BCM1MESSAGE_MONITOR_MAX;i++)
    {
        uMessageTimeOutCntForBCM1Missing[i] = 50;
        bMessageLostForBCM1Missing[i] = FALSE ;
    }
    for(i = 0;i<HCUMESSAGE_MONITOR_MAX;i++)
    {
        uMessageTimeOutCntForHCUMissing[i] = 25;
        bMessageLostForHCUMissing[i] = FALSE ;
    }

    // for(i = 0;i<PDCMESSAGE_MONITOR_MAX;i++)
    // {
    //     uMessageTimeOutCntForPDCMissing[i] = 25;
    //     bMessageLostForPDCMissing[i] = FALSE ;
    // }

    for(i = 0;i<HU_MESSAGE_MONITOR_MAX;i++)
    {
        uMessageTimeOutCntForHUMissing[i] = 25;
        bMessageLostForHUMissing[i] = FALSE ;
    }	

	uESP_2_AliveCountError1Times = 0;
	uESP_2_AliveCountError2Times = 0;
	uESP_2_ChecksumErrorTimes = 0;

	uABS_2_AliveCountError1Times = 0;
	uABS_2_AliveCountError2Times = 0;
	uABS_2_ChecksumErrorTimes = 0;

	uABS_1_AliveCountError1Times = 0;
	uABS_1_AliveCountError2Times = 0;
	uABS_1_ChecksumErrorTimes = 0;
	
	uSAS_1_AliveCountError1Times = 0;
	uSAS_1_AliveCountError2Times = 0;
	uSAS_1_ChecksumErrorTimes = 0;
}

BOOL CanDiag_GetGWNodeLostFlag(void)
{
	U8 i;
   	for(i = 0;i < GW_MESSAGE_MONITOR_MAX;i++)
   	{
		if(bMessageLostStaForGWNodeLost[i]==FALSE)
			return FALSE;
	}
	return TRUE;
}

BOOL CanDiag_GetESPMessageLostFlag(void)
{
	U8 i;
   	for(i = 0;i < ESP_MESSAGE_MONITOR_MAX;i++)
   	{
		if(bMessageLostForESPMissing[i]==TRUE)
			return TRUE;
	}
	return FALSE;
}

BOOL CanDiag_GetBCM1MessageLostFlag(void)
{
	U8 i;
   	for(i = 0;i < BCM1MESSAGE_MONITOR_MAX;i++)
   	{
		if(bMessageLostForBCM1Missing[i]==TRUE)
			return TRUE;
	}
	return FALSE;
}

BOOL CanDiag_GetHCUMessageLostFlag(void)
{
	U8 i;
   	for(i = 0;i < HCUMESSAGE_MONITOR_MAX;i++)
   	{
		if(bMessageLostForHCUMissing[i]==TRUE)
			return TRUE;
	}
	return FALSE;
}

// BOOL CanDiag_GetPDCMessageLostFlag(void)
// {
// 	U8 i;
//    	for(i = 0;i < PDCMESSAGE_MONITOR_MAX;i++)
//    	{
// 		if(bMessageLostForPDCMissing[i]==FALSE)
// 			return FALSE;
// 	}
// 	return TRUE;
// }

BOOL CanDiag_GetHUMessageLostFlag(void)
{
	U8 i;
   	for(i = 0;i < HU_MESSAGE_MONITOR_MAX;i++)
   	{
		if(bMessageLostForHUMissing[i]==TRUE)
			return TRUE;
	}
	return FALSE;
}

void CanDiag_EPSMessageLost_monitor_handler(void)
{
	U8 i;
	if(!bDTCRecordStatus[DTC_LOST_ESP_MESAGE_INDEX])
	{
		return;
	}

	for(i = 0;i<ESP_MESSAGE_MONITOR_MAX;i++)
	{
		if(uMessageTimeOutCntForESPMissing[i]>0)
		{
			uMessageTimeOutCntForESPMissing[i]--;
			bMessageLostForESPMissing[i] = FALSE;
		}
		if(uMessageTimeOutCntForESPMissing[i] == 0)
		{
			bMessageLostForESPMissing[i] = TRUE;
		}
	}
}

void CanDiag_BCM1MessageLost_monitor_handler(void)
{
	U8 i;
/* 	if(!bDTCRecordStatus[DTC_LOST_BCM1_MESAGE_INDEX])
	{
		return;
	} */

	for(i = 0;i<BCM1MESSAGE_MONITOR_MAX;i++)
	{
		if(uMessageTimeOutCntForBCM1Missing[i]>0)
		{
			uMessageTimeOutCntForBCM1Missing[i]--;
			bMessageLostForBCM1Missing[i] = FALSE;
		}
		if(uMessageTimeOutCntForBCM1Missing[i] == 0)
		{
			bMessageLostForBCM1Missing[i] = TRUE;
		}
	}
}

void CanDiag_HCUMessageLost_monitor_handler(void)
{
	U8 i;
/* 	if(!bDTCRecordStatus[DTC_LOST_BCM1_MESAGE_INDEX])
	{
		return;
	} */

	for(i = 0;i<HCUMESSAGE_MONITOR_MAX;i++)
	{
		if(uMessageTimeOutCntForHCUMissing[i]>0)
		{
			uMessageTimeOutCntForHCUMissing[i]--;
			bMessageLostForHCUMissing[i] = FALSE;
		}
		if(uMessageTimeOutCntForHCUMissing[i] == 0)
		{
			bMessageLostForHCUMissing[i] = TRUE;
		}
	}
}

// void CanDiag_PDCMessageLost_monitor_handler(void)
// {
// 	U8 i;
// 	if(!bDTCRecordStatus[DTC_LOST_PDC_MESAGE_INDEX])
// 	{
// 		return;
// 	}

// 	for(i = 0;i<PDCMESSAGE_MONITOR_MAX;i++)
// 	{
// 		if(uMessageTimeOutCntForPDCMissing[i]>0)
// 		{
// 			uMessageTimeOutCntForPDCMissing[i]--;
// 			bMessageLostForPDCMissing[i] = FALSE;
// 		}
// 		if(uMessageTimeOutCntForPDCMissing[i] == 0)
// 		{
// 			bMessageLostForPDCMissing[i] = TRUE;
// 		}
// 	}
// }

void CanDiag_HUMessageLost_monitor_handler(void)
{
	U8 i;
	if(!bDTCRecordStatus[DTC_LOST_HU_MESSAGE_INDEX])
	{
		return;
	}

	for(i = 0;i<HU_MESSAGE_MONITOR_MAX;i++)
	{
		if(uMessageTimeOutCntForHUMissing[i]>0)
		{
			uMessageTimeOutCntForHUMissing[i]--;
			bMessageLostForHUMissing[i] = FALSE;
		}
		if(uMessageTimeOutCntForHUMissing[i] == 0)
		{
			bMessageLostForHUMissing[i] = TRUE;
		}
	}
}


void CanDiag_GWNodeLost_monitor_handler(void)
{
	U8 i;
	if(!bDTCRecordStatus[DTC_LOST_GW_NODE_INDEX])
	{
		return;
	}

	for(i = 0;i<GW_MESSAGE_MONITOR_MAX;i++)
	{
		if(uMessageTimeOutCntForGWNodeLost[i]>0)
		{
			uMessageTimeOutCntForGWNodeLost[i]--;
			bMessageLostStaForGWNodeLost[i] = FALSE;
		}
		if(uMessageTimeOutCntForGWNodeLost[i] == 0)
		{
			bMessageLostStaForGWNodeLost[i] = TRUE;
		}
	}
}

void CanDiag_NmTimeout_monitor_handler(void)
{
	U8 i;
	for(i = 0;i<(DTC_MAX_NUM_INDEX - DTC_LOST_HU_MESSAGE_INDEX);i++)
	{
		if(bDTCRecordStatus[i + DTC_LOST_PDC_MESAGE_INDEX] == TRUE)
		{
			if(uMessageTimeOutCnt[i]>0)
			{
					uMessageTimeOutCnt[i]--;
					bMessageTimeOutStatus[i] = FALSE;
			}
			if(uMessageTimeOutCnt[i] == 0)
			{
					bMessageTimeOutStatus[i] = TRUE;      
			}
		} 
	}  
}
#endif

static void can_diag_HU_node_lost_fid_record(void)
{
	U8 index;
	for(index = 0; index < HU_MESSAGE_MONITOR_MAX; index++)
	{
		if(bMessageLostForHUMissing[index] == TRUE)
		{
			dtc_status_fid_data[DTC_LOST_ESP_MESAGE]  = FID_Definition[index + HU_5_MESSAGE_MISSING_FID_INDEX];
			break;
		}
	}
}

static void can_diag_dtc_HU_message_lost_monitor(void)
{
	U8 timeout;
	timeout = CanDiag_GetHUMessageLostFlag();
	if((TRUE == timeout)&&(bGWNodeIsLost==FALSE))
	{
		dtc_status_record_cnt[DTC_LOST_HU_MESSAGE].dtc_create_cnt++;
        dtc_status_record_cnt[DTC_LOST_HU_MESSAGE].dtc_recover_cnt = 0;

        if(dtc_status_record_cnt[DTC_LOST_HU_MESSAGE].dtc_create_cnt >= DTC_SET_LOST_COMM_CNT_MAX)
        {
            if((TRUE == can_diag_dtc_record_nm_enable_check())&&(0 == dtc_bus_off_counter))
            {
                can_diag_dtc_status_report(DTC_LOST_HU_MESSAGE, DTC_TEST_FAILED, FALSE);	
				
            }
            dtc_status_record_cnt[DTC_LOST_HU_MESSAGE].dtc_create_cnt = 0;
        }	
	}
	else
  	{
		dtc_status_record_cnt[DTC_LOST_HU_MESSAGE].dtc_recover_cnt++;

		if(dtc_status_record_cnt[DTC_LOST_HU_MESSAGE].dtc_recover_cnt >= DTC_CLR_LOST_COMM_CNT_MAX)
		{
		  if(TRUE == can_diag_dtc_record_nm_enable_check())
		  {
			  can_diag_dtc_status_report(DTC_LOST_HU_MESSAGE, DTC_TEST_PASSED, FALSE);
		  }
		  dtc_status_record_cnt[DTC_LOST_HU_MESSAGE].dtc_recover_cnt = 0;
		  
		  dtc_status_record_cnt[DTC_LOST_HU_MESSAGE].dtc_create_cnt = 0;
		} 	   
  	}
}

static void can_diag_ESP_node_lost_fid_record(void)
{
	U8 index;
	for(index = 0; index < ESP_MESSAGE_MONITOR_MAX; index++)
	{
		if(bMessageLostForESPMissing[index] == TRUE)
		{
			dtc_status_fid_data[DTC_LOST_ESP_MESAGE]  = FID_Definition[index];
			break;
		}
	}
}

static void can_diag_dtc_ESP_node_lost_monitor()
{
	U8 timeout;
	timeout = CanDiag_GetESPMessageLostFlag();
	if((TRUE == timeout)&&(bGWNodeIsLost==FALSE))
	{
		dtc_status_record_cnt[DTC_LOST_ESP_MESAGE].dtc_create_cnt++;
        dtc_status_record_cnt[DTC_LOST_ESP_MESAGE].dtc_recover_cnt = 0;

        if(dtc_status_record_cnt[DTC_LOST_ESP_MESAGE].dtc_create_cnt >= DTC_SET_LOST_COMM_CNT_MAX)
        {
            if((TRUE == can_diag_dtc_record_nm_enable_check())&&(0 == dtc_bus_off_counter))
            {
                can_diag_dtc_status_report(DTC_LOST_ESP_MESAGE, DTC_TEST_FAILED, FALSE);				
            }
            dtc_status_record_cnt[DTC_LOST_ESP_MESAGE].dtc_create_cnt = 0;
        }	
	}
	else
  	{
		dtc_status_record_cnt[DTC_LOST_ESP_MESAGE].dtc_recover_cnt++;

		if(dtc_status_record_cnt[DTC_LOST_ESP_MESAGE].dtc_recover_cnt >= DTC_CLR_LOST_COMM_CNT_MAX)
		{
		  if(TRUE == can_diag_dtc_record_nm_enable_check())
		  {
			  can_diag_dtc_status_report(DTC_LOST_ESP_MESAGE, DTC_TEST_PASSED, FALSE);
		  }
		  dtc_status_record_cnt[DTC_LOST_ESP_MESAGE].dtc_recover_cnt = 0;
		  
		  dtc_status_record_cnt[DTC_LOST_ESP_MESAGE].dtc_create_cnt = 0;
		} 	   
  	}
}

static void can_diag_dtc_BCM1_node_lost_monitor()
{
	U8 timeout;
	timeout = CanDiag_GetBCM1MessageLostFlag();
	if((TRUE == timeout)&&(bGWNodeIsLost==FALSE))
	{
		dtc_status_record_cnt[DTC_LOST_BCM1_MESAGE].dtc_create_cnt++;
        dtc_status_record_cnt[DTC_LOST_BCM1_MESAGE].dtc_recover_cnt = 0;

        if(dtc_status_record_cnt[DTC_LOST_BCM1_MESAGE].dtc_create_cnt >= DTC_SET_LOST_COMM_CNT_MAX)
        {
            if((TRUE == can_diag_dtc_record_nm_enable_check())&&(0 == dtc_bus_off_counter))
            {
                can_diag_dtc_status_report(DTC_LOST_BCM1_MESAGE, DTC_TEST_FAILED, FALSE);				
            }
            dtc_status_record_cnt[DTC_LOST_BCM1_MESAGE].dtc_create_cnt = 0;
        }	
	}
	else
  	{
		dtc_status_record_cnt[DTC_LOST_BCM1_MESAGE].dtc_recover_cnt++;

		if(dtc_status_record_cnt[DTC_LOST_BCM1_MESAGE].dtc_recover_cnt >= DTC_CLR_LOST_COMM_CNT_MAX)
		{
		  if(TRUE == can_diag_dtc_record_nm_enable_check())
		  {
			  can_diag_dtc_status_report(DTC_LOST_BCM1_MESAGE, DTC_TEST_PASSED, FALSE);
		  }
		  dtc_status_record_cnt[DTC_LOST_BCM1_MESAGE].dtc_recover_cnt = 0;
		  
		  dtc_status_record_cnt[DTC_LOST_BCM1_MESAGE].dtc_create_cnt = 0;
		} 	   
  	}
}

static void can_diag_dtc_HCU_node_lost_monitor()
{
	U8 timeout;
	timeout = CanDiag_GetHCUMessageLostFlag();
	if((TRUE == timeout)&&(bGWNodeIsLost==FALSE))
	{
		dtc_status_record_cnt[DTC_LOST_HCU_MESAGE].dtc_create_cnt++;
        dtc_status_record_cnt[DTC_LOST_HCU_MESAGE].dtc_recover_cnt = 0;

        if(dtc_status_record_cnt[DTC_LOST_HCU_MESAGE].dtc_create_cnt >= DTC_SET_LOST_COMM_CNT_MAX)
        {
            if((TRUE == can_diag_dtc_record_nm_enable_check())&&(0 == dtc_bus_off_counter))
            {
                can_diag_dtc_status_report(DTC_LOST_HCU_MESAGE, DTC_TEST_FAILED, FALSE);				
            }
            dtc_status_record_cnt[DTC_LOST_HCU_MESAGE].dtc_create_cnt = 0;
        }	
	}
	else
  	{
		dtc_status_record_cnt[DTC_LOST_HCU_MESAGE].dtc_recover_cnt++;

		if(dtc_status_record_cnt[DTC_LOST_HCU_MESAGE].dtc_recover_cnt >= DTC_CLR_LOST_COMM_CNT_MAX)
		{
		  if(TRUE == can_diag_dtc_record_nm_enable_check())
		  {
			  can_diag_dtc_status_report(DTC_LOST_HCU_MESAGE, DTC_TEST_PASSED, FALSE);
		  }
		  dtc_status_record_cnt[DTC_LOST_HCU_MESAGE].dtc_recover_cnt = 0;
		  
		  dtc_status_record_cnt[DTC_LOST_HCU_MESAGE].dtc_create_cnt = 0;
		} 	   
  	}
}

// static void can_diag_dtc_PDC_node_lost_monitor()
// {
// 	U8 timeout;
// 	timeout = CanDiag_GetPDCMessageLostFlag();
// //	if((TRUE == timeout)&&(bPDCNodeIsLost==FALSE))
//     if((TRUE == timeout))
// 	{
// 		dtc_status_record_cnt[DTC_LOST_PDC_NODE].dtc_create_cnt++;
//         dtc_status_record_cnt[DTC_LOST_PDC_NODE].dtc_recover_cnt = 0;

//         if(dtc_status_record_cnt[DTC_LOST_PDC_NODE].dtc_create_cnt >= DTC_SET_LOST_COMM_CNT_MAX)
//         {
//             if((TRUE == can_diag_dtc_record_nm_enable_check())&&(0 == dtc_bus_off_counter))
//             {
//                 can_diag_dtc_status_report(DTC_LOST_PDC_NODE, DTC_TEST_FAILED, FALSE);				
//             }
//             dtc_status_record_cnt[DTC_LOST_PDC_NODE].dtc_create_cnt = 0;
//         }
//         bPDCNodeIsLost = TRUE;	
// 	}
// 	else
//   	{
// 		dtc_status_record_cnt[DTC_LOST_PDC_NODE].dtc_recover_cnt++;

// 		if(dtc_status_record_cnt[DTC_LOST_PDC_NODE].dtc_recover_cnt >= DTC_CLR_LOST_COMM_CNT_MAX)
// 		{
// 		  if(TRUE == can_diag_dtc_record_nm_enable_check())
// 		  {
// 			  can_diag_dtc_status_report(DTC_LOST_PDC_NODE, DTC_TEST_PASSED, FALSE);
// 		  }
// 		  dtc_status_record_cnt[DTC_LOST_PDC_NODE].dtc_recover_cnt = 0;
		  
// 		  dtc_status_record_cnt[DTC_LOST_PDC_NODE].dtc_create_cnt = 0;
// 		}
//         bPDCNodeIsLost = FALSE; 	   
//   	}
// }

static void can_diag_dtc_GW_node_lost_fid_record(void)
{
	U8 index;
	for(index = 0; index < ATC_2_MESSAGE; index++)
	{
		if(bMessageLostStaForGWNodeLost[index] == TRUE)
		{
			dtc_status_fid_data[DTC_LOST_GW_NODE]  = FID_Definition[index];
			break;
		}
	}
}

static void can_diag_dtc_GW_node_lost_monitor(void)
{
	U8 timeout;
	timeout = CanDiag_GetGWNodeLostFlag();
	if(TRUE == timeout)
	{
		dtc_status_record_cnt[DTC_LOST_GW_NODE].dtc_create_cnt++;
        dtc_status_record_cnt[DTC_LOST_GW_NODE].dtc_recover_cnt = 0;

        if(dtc_status_record_cnt[DTC_LOST_GW_NODE].dtc_create_cnt >= DTC_SET_LOST_COMM_CNT_MAX)
        {
            if((TRUE == can_diag_dtc_record_nm_enable_check())&&(0 == dtc_bus_off_counter))
            {
                can_diag_dtc_status_report(DTC_LOST_GW_NODE, DTC_TEST_FAILED, FALSE);				
            }
            dtc_status_record_cnt[DTC_LOST_GW_NODE].dtc_create_cnt = 0;
        }
		bGWNodeIsLost = TRUE;	
	}
	else
  	{
		dtc_status_record_cnt[DTC_LOST_GW_NODE].dtc_recover_cnt++;

		if(dtc_status_record_cnt[DTC_LOST_GW_NODE].dtc_recover_cnt >= DTC_CLR_LOST_COMM_CNT_MAX)
		{
		  if(TRUE == can_diag_dtc_record_nm_enable_check())
		  {
			  can_diag_dtc_status_report(DTC_LOST_GW_NODE, DTC_TEST_PASSED, FALSE);
		  }
		  dtc_status_record_cnt[DTC_LOST_GW_NODE].dtc_recover_cnt = 0;
		  
		  dtc_status_record_cnt[DTC_LOST_GW_NODE].dtc_create_cnt = 0;
		} 	   
		bGWNodeIsLost = FALSE;
  	}
}

static void can_diag_dtc_nm_lost_node_monitor()
{
    U8 index;
    U8 timeout;
    for(index = 0;index<MESSAGE_TIMEOUT_TYPE_NUMBER;index++)
    {
        timeout = FALSE;
        #ifdef DIAG_NM_TIMEOUT_NOT_USE_IL_TIMEOUT_FLAG
        timeout = CanDiag_GetNMTimeOutFlag(index);
        #else
        //CanSig_CANGetValue(CanDiagNmTimeOutSigName[index],&timeout, 1);
        #endif
        if((TRUE == timeout)&&(bGWNodeIsLost==FALSE))
        {
            dtc_status_record_cnt[index+NM_TIMEOUT_START_INDEX].dtc_create_cnt++;
            dtc_status_record_cnt[index+NM_TIMEOUT_START_INDEX].dtc_recover_cnt = 0;

            if(dtc_status_record_cnt[index+NM_TIMEOUT_START_INDEX].dtc_create_cnt >= DTC_SET_LOST_COMM_CNT_MAX)
            {
                if((TRUE == can_diag_dtc_record_nm_enable_check())&&(0 == dtc_bus_off_counter))
                {
                    can_diag_dtc_status_report(index+NM_TIMEOUT_START_INDEX, DTC_TEST_FAILED, FALSE);				
                }
                dtc_status_record_cnt[index+NM_TIMEOUT_START_INDEX].dtc_create_cnt = 0;
            }
        }
        else
        {
            dtc_status_record_cnt[index+NM_TIMEOUT_START_INDEX].dtc_recover_cnt++;
            
            if(dtc_status_record_cnt[index+NM_TIMEOUT_START_INDEX].dtc_recover_cnt >= DTC_CLR_LOST_COMM_CNT_MAX)
            {
                if(TRUE == can_diag_dtc_record_nm_enable_check())
                {
                    can_diag_dtc_status_report(index+NM_TIMEOUT_START_INDEX, DTC_TEST_PASSED, FALSE);
                }
                dtc_status_record_cnt[index+NM_TIMEOUT_START_INDEX].dtc_recover_cnt = 0;
                
                dtc_status_record_cnt[index+NM_TIMEOUT_START_INDEX].dtc_create_cnt = 0;
            }        
        }
    }
}

#define SIGNAL_INVALID_VALUE  0x7FFF
static U8 err_time[5] = {25,25,25,25,25};
void ESP_signal_invalid_check_monitor_handler(void)
{
	U16 ESP_SignalErrArg[5];
	U8 index;

	ESP_SignalErrArg[0] = can_receive_sig(WheelSpeed_FL);
	ESP_SignalErrArg[1] = can_receive_sig(WheelSpeed_FR);
	ESP_SignalErrArg[2] = can_receive_sig(WheelSpeed_RL);
	ESP_SignalErrArg[3] = can_receive_sig(WheelSpeed_RR);
	ESP_SignalErrArg[4] = can_receive_sig(VehicleSpeed);

	for(index = 0; index < 5; index++)
	{
		if(ESP_SignalErrArg[index] == SIGNAL_INVALID_VALUE)
		{
			if(err_time[index] > 0)
			{
				err_time[index]--;
			}	
		}
		else
		{
			err_time[index] = 25;
		}
	}
}


static void can_diag_ESP_signal_invalid_fid_record(void)
{
	U8 index;
	for(index = 0; index < 5; index++)
	{
		if(err_time[index] == 0)
		{
			dtc_status_fid_data[DTC_ESP_MESSAGE_SIGNAL_INVALID]  = FID_Definition[index + WHEEL_FL_INVALID_FID_INDEX];
			break;
		}
	}
}

void can_diag_dtc_ESP_signal_invalid_monitor(void)
{	
	static BOOL Err_Sta;
	U8 index;
	for(index = 0; index < 5; index++)
	{
		if(err_time[index] == 0)
		{
			Err_Sta = TRUE;
			break;
		}
		Err_Sta = FALSE;
	}

	if(Err_Sta)
	{
		dtc_status_record_cnt[DTC_ESP_MESSAGE_SIGNAL_INVALID].dtc_create_cnt++;
		dtc_status_record_cnt[DTC_ESP_MESSAGE_SIGNAL_INVALID].dtc_recover_cnt = 0;

		if(dtc_status_record_cnt[DTC_ESP_MESSAGE_SIGNAL_INVALID].dtc_create_cnt >= DTC_SET_LOST_COMM_CNT_MAX)
		{
			if((TRUE == can_diag_dtc_record_nm_enable_check())&&(0 == dtc_bus_off_counter))
			{
				can_diag_dtc_status_report(DTC_ESP_MESSAGE_SIGNAL_INVALID, DTC_TEST_FAILED, FALSE);				
			}
			dtc_status_record_cnt[DTC_ESP_MESSAGE_SIGNAL_INVALID].dtc_create_cnt = 0;
		}
	}
	else
	{
		dtc_status_record_cnt[DTC_ESP_MESSAGE_SIGNAL_INVALID].dtc_recover_cnt++;
		
		if(dtc_status_record_cnt[DTC_ESP_MESSAGE_SIGNAL_INVALID].dtc_recover_cnt >= DTC_CLR_LOST_COMM_CNT_MAX)
		{
			if(TRUE == can_diag_dtc_record_nm_enable_check())
			{
				can_diag_dtc_status_report(DTC_ESP_MESSAGE_SIGNAL_INVALID, DTC_TEST_PASSED, FALSE);
			}
			dtc_status_record_cnt[DTC_ESP_MESSAGE_SIGNAL_INVALID].dtc_recover_cnt = 0;
			
			dtc_status_record_cnt[DTC_ESP_MESSAGE_SIGNAL_INVALID].dtc_create_cnt = 0;
		}		 
	}	
}

void can_diag_dtc_ESP_checksum_error_monitor(void)
{
	if((uESP_2_ChecksumErrorTimes >= 3)||(uABS_2_ChecksumErrorTimes >= 3)||(uABS_1_ChecksumErrorTimes >= 3))
	{
		dtc_status_record_cnt[DTC_ESP_MESSAGE_CHECKSUM_ERROR].dtc_create_cnt++;
		dtc_status_record_cnt[DTC_ESP_MESSAGE_CHECKSUM_ERROR].dtc_recover_cnt = 0;

		if(dtc_status_record_cnt[DTC_ESP_MESSAGE_CHECKSUM_ERROR].dtc_create_cnt >= DTC_SET_LOST_COMM_CNT_MAX)
		{
			if((TRUE == can_diag_dtc_record_nm_enable_check())&&(0 == dtc_bus_off_counter))
			{
				can_diag_dtc_status_report(DTC_ESP_MESSAGE_CHECKSUM_ERROR, DTC_TEST_FAILED, FALSE); 			
			}
			dtc_status_record_cnt[DTC_ESP_MESSAGE_CHECKSUM_ERROR].dtc_create_cnt = 0;
		}
	}
	else
	{
		dtc_status_record_cnt[DTC_ESP_MESSAGE_CHECKSUM_ERROR].dtc_recover_cnt++;
		
		if(dtc_status_record_cnt[DTC_ESP_MESSAGE_CHECKSUM_ERROR].dtc_recover_cnt >= DTC_CLR_LOST_COMM_CNT_MAX)
		{
			if(TRUE == can_diag_dtc_record_nm_enable_check())
			{
				can_diag_dtc_status_report(DTC_ESP_MESSAGE_CHECKSUM_ERROR, DTC_TEST_PASSED, FALSE);
			}
			dtc_status_record_cnt[DTC_ESP_MESSAGE_CHECKSUM_ERROR].dtc_recover_cnt = 0;
			
			dtc_status_record_cnt[DTC_ESP_MESSAGE_CHECKSUM_ERROR].dtc_create_cnt = 0;
		}		 
	}	
}

static void can_diag_EPS_checksum_error_fid_record(void)
{
	if(uABS_1_ChecksumErrorTimes >= 3)
	{
		dtc_status_fid_data[DTC_ESP_MESSAGE_CHECKSUM_ERROR]	= FID_Definition[ABS_1_CHECKSUM_ERR_FID_INDEX];
	}
	else if(uABS_2_ChecksumErrorTimes >= 3)
	{
		dtc_status_fid_data[DTC_ESP_MESSAGE_CHECKSUM_ERROR]	= FID_Definition[ABS_2_CHECKSUM_ERR_FID_INDEX];
	}
	else if(uESP_2_ChecksumErrorTimes >= 3)
	{
		dtc_status_fid_data[DTC_ESP_MESSAGE_CHECKSUM_ERROR]	= FID_Definition[ESP_2_CHECKSUM_ERR_FID_INDEX];
	}

}

void can_diag_dtc_EPS_checksum_error_monitor(void)
{
	if(uSAS_1_ChecksumErrorTimes >= 3)
	{
		dtc_status_record_cnt[DTC_EPS_MESSAGE_CHECKSUM_ERROR].dtc_create_cnt++;
		dtc_status_record_cnt[DTC_EPS_MESSAGE_CHECKSUM_ERROR].dtc_recover_cnt = 0;

		if(dtc_status_record_cnt[DTC_EPS_MESSAGE_CHECKSUM_ERROR].dtc_create_cnt >= DTC_SET_LOST_COMM_CNT_MAX)
		{
			if((TRUE == can_diag_dtc_record_nm_enable_check())&&(0 == dtc_bus_off_counter))
			{
				can_diag_dtc_status_report(DTC_EPS_MESSAGE_CHECKSUM_ERROR, DTC_TEST_FAILED, FALSE); 			
			}
			dtc_status_record_cnt[DTC_EPS_MESSAGE_CHECKSUM_ERROR].dtc_create_cnt = 0;
		}
	}
	else
	{
		dtc_status_record_cnt[DTC_EPS_MESSAGE_CHECKSUM_ERROR].dtc_recover_cnt++;
		
		if(dtc_status_record_cnt[DTC_EPS_MESSAGE_CHECKSUM_ERROR].dtc_recover_cnt >= DTC_CLR_LOST_COMM_CNT_MAX)
		{
			if(TRUE == can_diag_dtc_record_nm_enable_check())
			{
				can_diag_dtc_status_report(DTC_EPS_MESSAGE_CHECKSUM_ERROR, DTC_TEST_PASSED, FALSE);
			}
			dtc_status_record_cnt[DTC_EPS_MESSAGE_CHECKSUM_ERROR].dtc_recover_cnt = 0;
			
			dtc_status_record_cnt[DTC_EPS_MESSAGE_CHECKSUM_ERROR].dtc_create_cnt = 0;
		}		 
	}	
}

void can_diag_dtc_EPS_signal_invalid_monitor(void)
{
	U16 SigSteeringWheelAngle;
	static U8 sig_err_time = 25;  //500ms

	SigSteeringWheelAngle = can_receive_sig(SteeringWAngle);

	if(SigSteeringWheelAngle == SIGNAL_INVALID_VALUE)
	{
		if(sig_err_time > 0)
		{
			sig_err_time--;
		}
	}
	else
	{
		sig_err_time = 25;
	}

	if(sig_err_time == 0)
	{
		dtc_status_record_cnt[DTC_EPS_MESSAGE_SIGNAL_INVALID].dtc_create_cnt++;
		dtc_status_record_cnt[DTC_EPS_MESSAGE_SIGNAL_INVALID].dtc_recover_cnt = 0;

		if(dtc_status_record_cnt[DTC_EPS_MESSAGE_SIGNAL_INVALID].dtc_create_cnt >= DTC_SET_LOST_COMM_CNT_MAX)
		{
			if((TRUE == can_diag_dtc_record_nm_enable_check())&&(0 == dtc_bus_off_counter))
			{
				can_diag_dtc_status_report(DTC_EPS_MESSAGE_SIGNAL_INVALID, DTC_TEST_FAILED, FALSE);				
			}
			dtc_status_record_cnt[DTC_EPS_MESSAGE_SIGNAL_INVALID].dtc_create_cnt = 0;
		}
	}
	else
	{
		dtc_status_record_cnt[DTC_EPS_MESSAGE_SIGNAL_INVALID].dtc_recover_cnt++;
		
		if(dtc_status_record_cnt[DTC_EPS_MESSAGE_SIGNAL_INVALID].dtc_recover_cnt >= DTC_CLR_LOST_COMM_CNT_MAX)
		{
			if(TRUE == can_diag_dtc_record_nm_enable_check())
			{
				can_diag_dtc_status_report(DTC_EPS_MESSAGE_SIGNAL_INVALID, DTC_TEST_PASSED, FALSE);
			}
			dtc_status_record_cnt[DTC_EPS_MESSAGE_SIGNAL_INVALID].dtc_recover_cnt = 0;
			
			dtc_status_record_cnt[DTC_EPS_MESSAGE_SIGNAL_INVALID].dtc_create_cnt = 0;
		}		 
	}	

}

void can_diag_dtc_EPS_content_error_monitor(void)
{
	static U8 Error;

	if((uSAS_1_AliveCountError1Times >= 5)||(uSAS_1_AliveCountError2Times >= 3))
	{
		Error = TRUE;
	}
	else
	{
		Error = FALSE;
	}

	if(Error)
	{
		dtc_status_record_cnt[DTC_EPS_MESSAGE_LIVECOUNTER_ERROR].dtc_create_cnt++;
		dtc_status_record_cnt[DTC_EPS_MESSAGE_LIVECOUNTER_ERROR].dtc_recover_cnt = 0;

		if(dtc_status_record_cnt[DTC_EPS_MESSAGE_LIVECOUNTER_ERROR].dtc_create_cnt >= DTC_SET_LOST_COMM_CNT_MAX)
		{
			if((TRUE == can_diag_dtc_record_nm_enable_check())&&(0 == dtc_bus_off_counter))
			{
				can_diag_dtc_status_report(DTC_EPS_MESSAGE_LIVECOUNTER_ERROR, DTC_TEST_FAILED, FALSE);				
			}
			dtc_status_record_cnt[DTC_EPS_MESSAGE_LIVECOUNTER_ERROR].dtc_create_cnt = 0;
		}
	}
	else
	{
		dtc_status_record_cnt[DTC_EPS_MESSAGE_LIVECOUNTER_ERROR].dtc_recover_cnt++;
		
		if(dtc_status_record_cnt[DTC_EPS_MESSAGE_LIVECOUNTER_ERROR].dtc_recover_cnt >= DTC_CLR_LOST_COMM_CNT_MAX)
		{
			if(TRUE == can_diag_dtc_record_nm_enable_check())
			{
				can_diag_dtc_status_report(DTC_EPS_MESSAGE_LIVECOUNTER_ERROR, DTC_TEST_PASSED, FALSE);
			}
			dtc_status_record_cnt[DTC_EPS_MESSAGE_LIVECOUNTER_ERROR].dtc_recover_cnt = 0;
			
			dtc_status_record_cnt[DTC_EPS_MESSAGE_LIVECOUNTER_ERROR].dtc_create_cnt = 0;
		}		 
	}	
}

static void can_diag_ESP_content_error_fid_record(void)
{
	if((uABS_1_AliveCountError1Times >= 5)||(uABS_1_AliveCountError2Times >= 3))
	{
		dtc_status_fid_data[DTC_ESP_MESSAGE_LIVECOUNTER_ERROR]	= FID_Definition[ABS_1_LIVECOUNTER_ERR_FID_INDEX];
	}
	else if((uABS_2_AliveCountError1Times >= 5)||(uABS_2_AliveCountError2Times >= 3))
	{
		dtc_status_fid_data[DTC_ESP_MESSAGE_LIVECOUNTER_ERROR]	= FID_Definition[ABS_2_LIVECOUNTER_ERR_FID_INDEX];
	}
	else if((uESP_2_AliveCountError1Times >= 5)||(uESP_2_AliveCountError2Times >= 3))
	{
		dtc_status_fid_data[DTC_ESP_MESSAGE_LIVECOUNTER_ERROR]	= FID_Definition[ESP_2_LIVECOUNTER_ERR_FID_INDEX];
	}	
}

void can_diag_dtc_ESP_content_error_monitor(void)
{
	static U8 Error;

	if((uABS_1_AliveCountError1Times >= 5)||(uABS_1_AliveCountError2Times >= 3)||
	   (uABS_2_AliveCountError1Times >= 5)||(uABS_2_AliveCountError2Times >= 3)||
	   (uESP_2_AliveCountError1Times >= 5)||(uESP_2_AliveCountError2Times >= 3))
	{
		Error = TRUE;
	}
	else
	{
		Error = FALSE;
	}
		
	if(Error)
	{
		dtc_status_record_cnt[DTC_ESP_MESSAGE_LIVECOUNTER_ERROR].dtc_create_cnt++;
		dtc_status_record_cnt[DTC_ESP_MESSAGE_LIVECOUNTER_ERROR].dtc_recover_cnt = 0;

		if(dtc_status_record_cnt[DTC_ESP_MESSAGE_LIVECOUNTER_ERROR].dtc_create_cnt >= DTC_SET_LOST_COMM_CNT_MAX)
		{
			if((TRUE == can_diag_dtc_record_nm_enable_check())&&(0 == dtc_bus_off_counter))
			{
				can_diag_dtc_status_report(DTC_ESP_MESSAGE_LIVECOUNTER_ERROR, DTC_TEST_FAILED, FALSE);				
			}
			dtc_status_record_cnt[DTC_ESP_MESSAGE_LIVECOUNTER_ERROR].dtc_create_cnt = 0;
		}
	}
	else
	{
		dtc_status_record_cnt[DTC_ESP_MESSAGE_LIVECOUNTER_ERROR].dtc_recover_cnt++;
		
		if(dtc_status_record_cnt[DTC_ESP_MESSAGE_LIVECOUNTER_ERROR].dtc_recover_cnt >= DTC_CLR_LOST_COMM_CNT_MAX)
		{
			if(TRUE == can_diag_dtc_record_nm_enable_check())
			{
				can_diag_dtc_status_report(DTC_ESP_MESSAGE_LIVECOUNTER_ERROR, DTC_TEST_PASSED, FALSE);
			}
			dtc_status_record_cnt[DTC_ESP_MESSAGE_LIVECOUNTER_ERROR].dtc_recover_cnt = 0;
			
			dtc_status_record_cnt[DTC_ESP_MESSAGE_LIVECOUNTER_ERROR].dtc_create_cnt = 0;
		}		 
	}
}

/***********************************************************************
* FUNCTION    : void desc_delay_set_sig(U16 sig)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
void CanDiagDtc_desc_delay_set_sig(U16 sig)
{
    desc_delay_sig |= sig;
}


/***********************************************************************
* FUNCTION    : void desc_delay_clr_sig(U16 sig)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
void CanDiagDtc_desc_delay_clr_sig(U16 sig)
{
    desc_delay_sig &= ~sig;
}

/***********************************************************************
* FUNCTION    : BOOL CanDiagDtc_desc_delay_get_sig(U16 sig)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
BOOL CanDiagDtc_desc_delay_get_sig(U16 sig)
{
    return((desc_delay_sig & sig) != 0);
}

/***********************************************************************
* FUNCTION    : void can_desc_delay_service_monitor(void)
* DESCRIPTION : 
* INPUTS      : none
* RETURN      : none
***********************************************************************/
static void can_desc_delay_service_monitor(void)
{
    if(CanDiagDtc_desc_delay_get_sig(DESC_DELAY_SIG_1))
    {
        if(CanDiagDtc_status_svc14_clear_all())
        {
            CanDiagDtc_desc_delay_clr_sig(DESC_DELAY_SIG_1);
        }
    }

    if(CanDiagDtc_desc_delay_get_sig(DESC_DELAY_SIG_2))
    {
        CanDiagDtc_desc_delay_clr_sig(DESC_DELAY_SIG_2);
    }

    if(CanDiagDtc_desc_delay_get_sig(DESC_DELAY_SIG_3))
    {
        CanDiagDtc_desc_delay_clr_sig(DESC_DELAY_SIG_3);
    }

    if(CanDiagDtc_desc_delay_get_sig(DESC_DELAY_SIG_4))
    {
        CanDiagDtc_desc_delay_clr_sig(DESC_DELAY_SIG_4);
    }

    if(CanDiagDtc_desc_delay_get_sig(DESC_DELAY_SIG_5))
    {
        CanDiagDtc_desc_delay_clr_sig(DESC_DELAY_SIG_5);
    }

    if(CanDiagDtc_desc_delay_get_sig(DESC_DELAY_SIG_6))
    {
        CanDiagDtc_desc_delay_clr_sig(DESC_DELAY_SIG_6);
    }

    if(CanDiagDtc_desc_delay_get_sig(DESC_DELAY_SIG_7))
    {
   ///shangqiuju     if(can_diag_check_os_version())
        {
            CanDiagDtc_desc_delay_clr_sig(DESC_DELAY_SIG_7);
        }
    }

    if(CanDiagDtc_desc_delay_get_sig(DESC_DELAY_SIG_8))
    {
    //shangqiuju    if(can_diag_set_machine_id())
        {
            CanDiagDtc_desc_delay_clr_sig(DESC_DELAY_SIG_8);
        }
    }

    if(CanDiagDtc_desc_delay_get_sig(DESC_DELAY_SIG_9))
    {
        CanDiagDtc_desc_delay_clr_sig(DESC_DELAY_SIG_9);
    }
}

/***********************************************************************
* FUNCTION    : void can_diag_bat_volt_supervision(void)
* DESCRIPTION : diag volt monitor. Called by can_diag_task only. cycle call:10ms
* INPUTS      : none
* RETURN      : none
***********************************************************************/
static void can_diag_bat_volt_supervision(void)
{

    /* current volt abnormal */
    if(V_NORMAL!= sPower_Can)
    {
        /* previous volt normal */
        if(V_NORMAL == sPower_CanPre)
        {
            can_diag_bat_volt_recover_delay_timer = CAN_DIAG_BAT_VOLT_RECOVER_DELAY_TIME;

            /* Adjust dtc record enable mask */
            can_diag_dtc_record_enable_adjust();
        }
        else /* previous volt abnormal */
        {
            /* do not let timer run out */
            can_diag_bat_volt_recover_delay_timer = CAN_DIAG_BAT_VOLT_RECOVER_DELAY_TIME;
        }
    }
    else /* current volt normal */
    {
        /* previous volt abnormal */
        if(V_NORMAL != sPower_CanPre)
        {
            /* launch timer */
            can_diag_bat_volt_recover_delay_timer = CAN_DIAG_BAT_VOLT_RECOVER_DELAY_TIME;
            
            /* Adjust dtc record enable mask */
            can_diag_dtc_record_enable_adjust();
        }
        else /* previous volt normal */
        {
            /* keep the timer running out if possible */
        }
    }

    sPower_CanPre = sPower_Can;

    if(can_diag_bat_volt_recover_delay_timer > CAN_DIAG_BAT_VOLT_RECOVER_DELAY_TIMEOUT)
    {
        can_diag_bat_volt_recover_delay_timer--;

        if(CAN_DIAG_BAT_VOLT_RECOVER_DELAY_TIMEOUT == can_diag_bat_volt_recover_delay_timer)
        {
            /* Adjust dtc record enable mask */
            can_diag_dtc_record_enable_adjust();
        }
    }
}


static void can_diag_bdy_dtc_volt_handle(void)
{
	static U8 Power_Bdy;
	static U8 Power_BdyPre;
	CS_SIG_SyncReceive(SIG_VOLTAGEFAIL_STATUS, (U16 *)&Power_Bdy); 

	/* current volt abnormal */
	if(V_NORMAL!= Power_Bdy)
	{
		/* previous volt normal */
		if(V_NORMAL == Power_BdyPre)
		{
			can_diag_bdy_bat_volt_recover_delay_timer = CAN_DIAG_BAT_VOLT_RECOVER_DELAY_TIME;

			/* Adjust dtc record enable mask */
			can_diag_dtc_record_enable_adjust();
		}
		else /* previous volt abnormal */
		{
			/* do not let timer run out */
			can_diag_bdy_bat_volt_recover_delay_timer = CAN_DIAG_BAT_VOLT_RECOVER_DELAY_TIME;
		}
	}
	else /* current volt normal */
	{
		/* previous volt abnormal */
		if(V_NORMAL != Power_BdyPre)
		{
			/* launch timer */
			can_diag_bdy_bat_volt_recover_delay_timer = CAN_DIAG_BAT_VOLT_RECOVER_DELAY_TIME;
			
			/* Adjust dtc record enable mask */
			can_diag_dtc_record_enable_adjust();
		}
		else /* previous volt normal */
		{
			/* keep the timer running out if possible */
		}
	}
	
	Power_BdyPre = Power_Bdy;

	if(can_diag_bdy_bat_volt_recover_delay_timer > CAN_DIAG_BAT_VOLT_RECOVER_DELAY_TIMEOUT)
	{
		can_diag_bdy_bat_volt_recover_delay_timer--;

		if(CAN_DIAG_BAT_VOLT_RECOVER_DELAY_TIMEOUT == can_diag_bdy_bat_volt_recover_delay_timer)
		{
			/* Adjust dtc record enable mask */
			can_diag_dtc_record_enable_adjust();
		}
	}
}


/***********************************************************************
* FUNCTION    : void can_diag_pow_mode_supervise_init(void)
* DESCRIPTION : ignition position monitor. Called by can_diag_init only.
* INPUTS      : none
* RETURN      : none
***********************************************************************/
static void can_diag_pow_mode_supervise_init(void)
{
    can_diag_init_nm_delay_timer = CAN_DIAG_NM_INIT_DELAY_TIME;
}

/***********************************************************************
* FUNCTION    : void can_diag_pow_mode_supervision(void)
* DESCRIPTION : ignition position monitor. Called by can_diag_task only. cycle call:10ms
* INPUTS      : none
* RETURN      : none
***********************************************************************/
static void can_diag_pow_mode_supervision(void)
{
    if(bAccOn)
    {
        if(! bAccOnPreStatus)/* IGN OFF --> IGN ON */
        {
            can_diag_init_nm_delay_timer = CAN_DIAG_NM_INIT_DELAY_TIME; //reset the timer
        }

        if(can_diag_init_nm_delay_timer > CAN_DIAG_NM_INIT_DELAY_TIMEOUT)
        {
            can_diag_init_nm_delay_timer--;
        }
    }
    else
    {
        can_diag_init_nm_delay_timer = CAN_DIAG_NM_INIT_DELAY_TIME; //keep the timer.
    #ifdef DTC_AGING_COUNTER
        if(bAccOnPreStatus)
        {
            _memset(bSetClearHistoryFaultCntFlag,TRUE,DTC_CODE_MAX_NUM);
        }
    #endif
    }
    /* Adjust dtc record enable mask */
    can_diag_dtc_record_enable_adjust();
}

void Dtc_S0Init(void)
{
	bBatteryOn = TRUE;
}

void Dtc_S1Init(void)
{
	bWakeupOn = TRUE;
}

void CanDiagDtcInit(void)
{
///TODO:if need to get hardware /software version.shangqiuju
    //can_diag_can_diag_vehicle_manufacturer_ecu_hardware_buildup();
    //can_diag_system_supplier_ecu_software_number_buildup();
    can_diag_pow_mode_supervise_init();

    can_diag_dtc_init();
	
    can_diag_init_delay_timer = CAN_DIAG_INIT_DELAY_TIME;
    can_diag_init_nm_delay_timer = CAN_DIAG_NM_INIT_DELAY_TIME;
	can_diag_ign_delay_timer = CAN_DIAG_NM_IGN_ON_DELAY_TIME;
    can_diag_bat_volt_recover_delay_timer = CAN_DIAG_BAT_VOLT_RECOVER_DELAY_TIMEOUT;
	can_diag_bdy_bat_volt_recover_delay_timer = CAN_DIAG_BAT_VOLT_RECOVER_DELAY_TIMEOUT;
	
    #ifdef USE_AD_CHECK_POWER
    PowerDetInit();
    #endif
}

void CanDiagDtcDeInit(void)
{
    bEEPloadFinished = FALSE;
    uWaitEEPdownloadTimes = 0;
    uWaitEEPdownloadTimes2 = 0;
}

#ifdef USE_AD_CHECK_POWER
void PowerDetInit(void)
{
    U16 newPower;
    U16 NaviPowerStatus;
    U16 uVoltageHigh16v;
    U16 uVoltageLow9v;
    
     sPower_Can = V_LOW;
     powerOverCnt=0;
     powerDownCnt =0;
     powerNormalCnt = 0;
    CS_SIG_SyncReceive(SIG_APP_PWR, &newPower);
    if(newPower == 0xffff) return;
    
    CS_SIG_SyncReceive(SIG_B_SOC_POWER_ON, &NaviPowerStatus);
    NaviPowerStatus = NaviPowerStatus&0x01;        
    
//    if(NaviPowerStatus)
//    {
//        uVoltageHigh16v = VOLTAGE_16V;
//        uVoltageLow9v = VOLTAGE_9V;
//    }
//    else
//    {
//        uVoltageHigh16v = VOLTAGE_16V;
//        uVoltageLow9v = (VOLTAGE_9V+VOLTAGE_CLOSE_J6_OFFSET);
//    }
    if(newPower>uVoltageHigh16v)
    {
        sPower_Can = V_HIGH;
    }
    else if(newPower<uVoltageLow9v)
    {
        sPower_Can = V_LOW;
    }
    else
    {
        sPower_Can = V_NORMAL;
    }
}

 void PowerDetAD(void)
 {
    U16 newPower;
    U16 NaviPowerStatus;
    CS_SIG_AsyncReceive(SIG_APP_PWR, &newPower);
    if(newPower == 0xffff) return;
    
    CS_SIG_SyncReceive(SIG_B_SOC_POWER_ON, &NaviPowerStatus);
    NaviPowerStatus = NaviPowerStatus&0x01;  
   
    if(newPower>VOLTAGE_16V)
    {
		sPower_Can = V_HIGH;        
    }
    else if(newPower<VOLTAGE_9V)
    {
        sPower_Can = V_LOW;            
    }
    else
    {
    	if(sPower_Can == V_HIGH)
    	{
			if(newPower<VOLTAGE_15V5)
			{
				sPower_Can = V_NORMAL; 
			}
		}
    	if(sPower_Can == V_LOW)
    	{
    		if(newPower>(VOLTAGE_9V5))
    		{
				sPower_Can = V_NORMAL; 
    		}
		}		             
    }    
 }
#endif


void CanDiagDtc_20msEntry(void)
{    
    U16 AccStatus;
	U16 IGNStatus;
	U8 index;	
	static U8 StartTimer;
	static BOOL bNmWakeUpedSta;
    #ifdef USE_AD_CHECK_POWER
    PowerDetAD();
    #else
    U16 SystemVol = 0;    
    CS_SIG_SyncReceive(SIG_VOLTAGEFAIL_STATUS, &SystemVol);
    sPower_Can = (E_SYSTEM_VOLTAGE_STATUS)SystemVol;
    #endif
    
	CS_SIG_SyncReceive(SIG_ACC_CAN_IN_STATUS, &IGNStatus);
	IGNStatus = IGNStatus&0x01;
	
	CS_SIG_SyncReceive(SIG_ACCSTATUS, &AccStatus);
	
    bAccOnPreStatus = bAccOn;
    bAccOn = AccStatus&0x01;

	if(hw_accon_flag == TRUE)
	{
		if(bNmWakeUpedSta){
			bNmWakeUpedSta = FALSE;
			can_diag_ign_delay_timer = CAN_DIAG_NM_IGN_ON_DELAY_TIME;
			for(index = 0;index<DTC_MAX_NUM_INDEX;index++)
			{
				bDTCRecordStatus[index] = FALSE;
			}
		}
		StartTimer = TRUE;
		NmWakeUpSta = FALSE;
	}
	else if(NmWakeUpSta == TRUE)
	{
		StartTimer = TRUE;
		bNmWakeUpedSta = TRUE;
	}	
	else
	{
		StartTimer = FALSE;
	}
	
	
	if(StartTimer)
	{
		if(can_diag_ign_delay_timer > CAN_DIAG_NM_IGN_ON_DELAY_TIMEOUT)
		{
			can_diag_ign_delay_timer--;
			if(CAN_DIAG_NM_IGN_ON_DELAY_TIMEOUT == can_diag_ign_delay_timer)
			{
				for(index = 0;index<DTC_MAX_NUM_INDEX;index++)
				{
					bDTCRecordStatus[index] = TRUE;
				}
				bDTCBusoffRecordSta = TRUE;
				bNAckSta = TRUE;
			}
		}
	}
	else
	{
		for(index = 0;index<DTC_MAX_NUM_INDEX;index++)
		{
			bDTCRecordStatus[index] = FALSE;
		}
		bDTCBusoffRecordSta = FALSE;
		can_diag_ign_delay_timer = CAN_DIAG_NM_IGN_ON_DELAY_TIME;
		bNAckSta = FALSE;
	}
    /* Diagnosis init, dtc record enable delay */
    if(can_diag_init_delay_timer > CAN_DIAG_INIT_DELAY_TIMEOUT)
    {
        can_diag_init_delay_timer--;

        if(CAN_DIAG_INIT_DELAY_TIMEOUT == can_diag_init_delay_timer)
        {
            /* Adjust dtc record enable mask */
            can_diag_dtc_record_enable_adjust();
        }
    }	

    /* Control init dtc eeprom when system Power up */
     can_diag_dtc_eeprom_init_handle();  
    
    /* battery volt supervision */
     can_diag_bat_volt_supervision();

	/* none nm dtc volt condition handle */
	 can_diag_bdy_dtc_volt_handle();

    /* desc service delay execute monitor */
     can_desc_delay_service_monitor();

    /* dtc monitor */
     can_diag_dtc_monitor_handle();  

    /* power mode bat volt supervision */
     can_diag_pow_mode_supervision();
	
#ifndef SX5_HW
#ifdef DIAG_NM_TIMEOUT_NOT_USE_IL_TIMEOUT_FLAG
    if((FALSE == can_diag_dtc_record_nm_enable_check())||(0 != dtc_bus_off_counter)||(ResetTimeCntFlag))
    {
        ResetCanDiagTimeoutState();
		ResetTimeCntFlag = FALSE;
    }
    CanDiag_NmTimeout_monitor_handler();
	CanDiag_GWNodeLost_monitor_handler();
	CanDiag_HUMessageLost_monitor_handler();
	CanDiag_EPSMessageLost_monitor_handler();
    CanDiag_BCM1MessageLost_monitor_handler();
    CanDiag_HCUMessageLost_monitor_handler();
//    CanDiag_PDCMessageLost_monitor_handler();
	ESP_signal_invalid_check_monitor_handler();
#endif
#endif
}
#endif
#endif


/*This 10ms task is only used for monitoring SX5 10ms message timeout*/
/*Generally if you using 20ms task to handle 10ms messages' timeout, the time will not fulfill the plus-minus 10% requirement*/
void CanDiagDtc_10msEntry(void)
{
#ifdef SX5_HW
#ifdef DIAG_NM_TIMEOUT_NOT_USE_IL_TIMEOUT_FLAG
    if(FALSE == can_diag_dtc_record_nm_enable_check())
    {
        ResetCanDiagTimeoutState();
    }
    CanDiag_NmTimeout_monitor_handler();
#endif
#endif
}

void IC_1_Received(CanReceiveHandle rcvObject)
{
	uMessageTimeOutCntForGWNodeLost[IC_1_MESSAGE] = 25;		
	uMessageTimeOutCnt[MESSAGE_IC_1_LOST_INDEX] = uMessageTimeoutStartTime[MESSAGE_IC_1_LOST_INDEX];
}

void TCU_3_Received(CanReceiveHandle rcvObject)
{
	uMessageTimeOutCntForGWNodeLost[TCU_3_MESSAGE] = 25;
    uMessageTimeOutCntForHCUMissing[TCU_3_MESSAGE_1] = 25;
	uMessageTimeOutCnt[MESSAGE_TCU_3_LOST_INDEX] = uMessageTimeoutStartTime[MESSAGE_TCU_3_LOST_INDEX];
}

void SAS_1_Received(CanReceiveHandle rcvObject)
{
	static U8 PreAliveCount;
	static U8 CurAliveCount;
	static U8 RxChecksum,CalcuChecksum;
	static U8 DIF;

	PreAliveCount = CurAliveCount;
	CurAliveCount = can_receive_sig(LiveCounter_SAS_1);
	RxChecksum = can_receive_sig(Checksum_SAS_1);

	//Checksum (byte0) = byte1 XOR byte2 XOR byte3 XOR byte4 …XOR byteN-1, N = message length
	CalcuChecksum = c2_SAS_1_c^c3_SAS_1_c^c4_SAS_1_c^c5_SAS_1_c^c6_SAS_1_c^c7_SAS_1_c^c8_SAS_1_c;
	if(RxChecksum != CalcuChecksum)
	{
		uSAS_1_ChecksumErrorTimes++;
		if(uSAS_1_ChecksumErrorTimes >= 3)
		{
			uSAS_1_ChecksumErrorTimes = 3;
		}
	}
	else
	{
		uSAS_1_ChecksumErrorTimes = 0;
	}
		
	uMessageTimeOutCntForGWNodeLost[SAS_1_MESSAGE] = 25;	
	uMessageTimeOutCnt[MESSAGE_SAS_1_LOST_INDEX] = uMessageTimeoutStartTime[MESSAGE_SAS_1_LOST_INDEX];

	DIF = (PreAliveCount > CurAliveCount)?(PreAliveCount-CurAliveCount):(CurAliveCount-PreAliveCount);

	if(DIF == 0)  //same counts are received.
	{
		uSAS_1_AliveCountError1Times++;
		if(uSAS_1_AliveCountError1Times >= 5)
		{
			uSAS_1_AliveCountError1Times = 5;
		}
	}
	else if(DIF > 2)  //Two consecutive cycles counter values are greater than 2.
	{
		uSAS_1_AliveCountError2Times++;
		if(uSAS_1_AliveCountError2Times >= 3)
		{
			uSAS_1_AliveCountError2Times = 3;
		}
	}	
	else
	{
		 if((PreAliveCount+1) == CurAliveCount)
		 {
			uSAS_1_AliveCountError1Times = 0;
			uSAS_1_AliveCountError2Times = 0;
		 }
	 }
}

void PLG_1_Received(CanReceiveHandle rcvObject)
{		
	uMessageTimeOutCntForGWNodeLost[PLG_1_MESSAGE] = 25;	
	uMessageTimeOutCnt[MESSAGE_PLG_1_LOST_INDEX] = uMessageTimeoutStartTime[MESSAGE_PLG_1_LOST_INDEX];
}

void HU_5_Received(CanReceiveHandle rcvObject)
{		
	uMessageTimeOutCntForGWNodeLost[HU_5_MESSAGE] = 25;		
	uMessageTimeOutCntForHUMissing[HU_5_MESSAGE_1] = 50;
}

void HU_6_Received(CanReceiveHandle rcvObject)
{		
	uMessageTimeOutCntForGWNodeLost[HU_6_MESSAGE] = 25;		
	uMessageTimeOutCntForHUMissing[HU_6_MESSAGE_1] = 50;
}

void HU_20_Received(CanReceiveHandle rcvObject)
{
    uMessageTimeOutCntForGWNodeLost[HU_20_MESSAGE] = 25;
    uMessageTimeOutCntForHUMissing[HU_20_MESSAGE_1] = 50;
}

void GW_Config_Received(CanReceiveHandle rcvObject)
{
	uMessageTimeOutCntForGWNodeLost[GW_CONFIG_MESSAGE] = 25;

}

void PDC_1_Received(CanReceiveHandle rcvObject)
{		
	uMessageTimeOutCnt[MESSAGE_PDC_1_LOST_INDEX] = uMessageTimeoutStartTime[MESSAGE_PDC_1_LOST_INDEX];
}
void PDCU_1_Received(CanReceiveHandle rcvObject)
{	
	uMessageTimeOutCntForGWNodeLost[PDCU_1_MESSAGE] = 25;
	uMessageTimeOutCnt[MESSAGE_PDCU_1_LOST_INDEX] = uMessageTimeoutStartTime[MESSAGE_PDCU_1_LOST_INDEX];
}
void DDCU_1_Received(CanReceiveHandle rcvObject)
{
	uMessageTimeOutCntForGWNodeLost[DDCU_1_MESSAGE] = 25;
	uMessageTimeOutCnt[MESSAGE_DDCU_1_LOST_INDEX] = uMessageTimeoutStartTime[MESSAGE_DDCU_1_LOST_INDEX];
}

void RRDCU_1_Received(CanReceiveHandle rcvObject)
{
	uMessageTimeOutCntForGWNodeLost[RRDCU_1_MESSAGE] = 25;
    uMessageTimeOutCnt[MESSAGE_RRDCU_1_LOST_INDEX] = uMessageTimeoutStartTime[MESSAGE_RRDCU_1_LOST_INDEX];
}

void RLDCU_1_Received(CanReceiveHandle rcvObject)
{
	uMessageTimeOutCntForGWNodeLost[RLDCU_1_MESSAGE] = 25;
    uMessageTimeOutCnt[MESSAGE_RLDCU_1_LOST_INDEX] = uMessageTimeoutStartTime[MESSAGE_RLDCU_1_LOST_INDEX];
}

void DMS_2_Received(CanReceiveHandle rcvObject)
{
	uMessageTimeOutCntForGWNodeLost[DMS_2_MESSAGE] = 25;
    uMessageTimeOutCnt[MESSAGE_DMS_2_LOST_INDEX] = uMessageTimeoutStartTime[MESSAGE_DMS_2_LOST_INDEX];
}

void BCM1_1_Received(CanReceiveHandle rcvObject)
{	
	uMessageTimeOutCntForGWNodeLost[BCM1_1_MESSAGE] = 25;
    uMessageTimeOutCntForBCM1Missing[BCM1_1_MESSAGE_1]	= 50;	
//	uMessageTimeOutCnt[MESSAGE_BCM1_1_LOST_INDEX] = uMessageTimeoutStartTime[MESSAGE_BCM1_1_LOST_INDEX];
}

void BCM1_2_Received(CanReceiveHandle rcvObject)
{	
	uMessageTimeOutCntForGWNodeLost[BCM1_2_MESSAGE] = 25;	
    uMessageTimeOutCntForBCM1Missing[BCM1_2_MESSAGE_1]	= 50;
}

void ATC_2_Received(CanReceiveHandle rcvObject)
{
	uMessageTimeOutCntForGWNodeLost[ATC_2_MESSAGE] = 25;		
	uMessageTimeOutCnt[MESSAGE_ATC_2_LOST_INDEX] = uMessageTimeoutStartTime[MESSAGE_ATC_2_LOST_INDEX];
}

void EMS_3_Received(CanReceiveHandle rcvObject)
{
	uMessageTimeOutCntForGWNodeLost[EMS_3_MESSAGE] = 25;
    uMessageTimeOutCntForHCUMissing[EMS_3_MESSAGE_1] = 25;
    uMessageTimeOutCnt[MESSAGE_EMS_3_LOST_INDEX] = uMessageTimeoutStartTime[MESSAGE_EMS_3_LOST_INDEX];
}

void MCP_1_Received(CanReceiveHandle rcvObject)
{		
	uMessageTimeOutCntForGWNodeLost[MCP_1_MESSAGE] = 25;
	uMessageTimeOutCnt[MESSAGE_MCP_1_LOST_INDEX] = uMessageTimeoutStartTime[MESSAGE_MCP_1_LOST_INDEX];
}

void LCDA_1_Received(CanReceiveHandle rcvObject)
{
	uMessageTimeOutCnt[MESSAGE_LCDA_1_LOST_INDEX] = uMessageTimeoutStartTime[MESSAGE_LCDA_1_LOST_INDEX];

}

// void PDC_3_Received(CanReceiveHandle rcvObject)
// {		
// 	uMessageTimeOutCntForPDCMissing[PDC_3_MESSAGE] = 25;
// }

// void PDC_4_Received(CanReceiveHandle rcvObject)
// {		
// 	uMessageTimeOutCntForPDCMissing[PDC_4_MESSAGE] = 25;
// }

// void PDC_9_Received(CanReceiveHandle rcvObject)
// {		
// 	uMessageTimeOutCntForPDCMissing[PDC_9_MESSAGE] = 25;
// }


void ESP_2_Received(CanReceiveHandle rcvObject)
{	
	static U8 PreAliveCount;
	static U8 CurAliveCount;
	static U8 RxChecksum,CalcuChecksum;
	static U8 DIF;

	PreAliveCount = CurAliveCount;
	CurAliveCount = can_receive_sig(LiveCounter_ESP_2);
	RxChecksum = can_receive_sig(Checksum_ESP_2);

	//Checksum (byte0) = byte1 XOR byte2 XOR byte3 XOR byte4 …XOR byteN-1, N = message length
	CalcuChecksum = c2_ESP_2_c^c3_ESP_2_c^c4_ESP_2_c^c5_ESP_2_c^c6_ESP_2_c^c7_ESP_2_c^c8_ESP_2_c;
	if(RxChecksum != CalcuChecksum)
	{
		uESP_2_ChecksumErrorTimes++;
		if(uESP_2_ChecksumErrorTimes >= 3)
		{
			uESP_2_ChecksumErrorTimes = 3;
		}
	}
	else
	{
		uESP_2_ChecksumErrorTimes = 0;
	}
	
	uMessageTimeOutCntForGWNodeLost[ESP_2_MESSAGE] = 25;	
	uMessageTimeOutCntForESPMissing[ESP_2_MESSAGE_1] = 25;

	DIF = (PreAliveCount > CurAliveCount)?(PreAliveCount-CurAliveCount):(CurAliveCount-PreAliveCount);

	if(DIF == 0)  //same counts are received.
	{
		uESP_2_AliveCountError1Times++;
		if(uESP_2_AliveCountError1Times >= 5)
		{
			uESP_2_AliveCountError1Times = 5;
		}
	}
	else if(DIF > 2)  //Two consecutive cycles counter values are greater than 2.
	{
		uESP_2_AliveCountError2Times++;
		if(uESP_2_AliveCountError2Times >= 3)
		{
			uESP_2_AliveCountError2Times = 3;
		}
	}	
	else
	{
		 if((PreAliveCount+1) == CurAliveCount)
		 {
			uESP_2_AliveCountError1Times = 0;
			uESP_2_AliveCountError2Times = 0;
		 }
	}
}


void ABS_2_Received(CanReceiveHandle rcvObject)
{
	static U8 PreAliveCount;
	static U8 CurAliveCount;
	static U8 RxChecksum,CalcuChecksum;
	static U8 DIF;
	
	PreAliveCount = CurAliveCount;
	CurAliveCount = can_receive_sig(LiveCounter_ABS_2);
	RxChecksum = can_receive_sig(Checksum_ABS_2);

	//Checksum (byte0) = byte1 XOR byte2 XOR byte3 XOR byte4 …XOR byteN-1, N = message length
	CalcuChecksum = c2_ABS_2_c^c3_ABS_2_c^c4_ABS_2_c^c5_ABS_2_c^c6_ABS_2_c^c7_ABS_2_c^c8_ABS_2_c;
	if(RxChecksum != CalcuChecksum)
	{
		uABS_2_ChecksumErrorTimes++;
		if(uABS_2_ChecksumErrorTimes >= 3)
		{
			uABS_2_ChecksumErrorTimes = 3;
		}
	}
	else
	{
		uABS_2_ChecksumErrorTimes = 0;
	}	
	uMessageTimeOutCntForGWNodeLost[ABS_2_MESSAGE] = 25;
	uMessageTimeOutCntForESPMissing[ABS_2_MESSAGE_1] = 25;

	DIF = (PreAliveCount > CurAliveCount)?(PreAliveCount-CurAliveCount):(CurAliveCount-PreAliveCount);
	
	if(PreAliveCount == CurAliveCount)
	{
		uABS_2_AliveCountError1Times++;
		if(uABS_2_AliveCountError1Times >= 5)
		{
			uABS_2_AliveCountError1Times = 5;
		}
	}
	else if(DIF > 2)
	{
		uABS_2_AliveCountError2Times++;
		if(uABS_2_AliveCountError2Times >= 3)
		{
			uABS_2_AliveCountError2Times = 3;
		}
	}	
	else
	{
		 if((PreAliveCount+1) == CurAliveCount)
		 {
			uABS_2_AliveCountError1Times = 0;
			uABS_2_AliveCountError2Times = 0;
		 }
	}	
}


void ABS_1_Received(CanReceiveHandle rcvObject)
{	
	static U8 PreAliveCount;
	static U8 CurAliveCount;
	static U8 RxChecksum,CalcuChecksum;
	static U8 DIF;
	
	PreAliveCount = CurAliveCount;
	CurAliveCount = can_receive_sig(LiveCounter_ABS_1);
	RxChecksum = can_receive_sig(Checksum_ABS_1);

	//Checksum (byte0) = byte1 XOR byte2 XOR byte3 XOR byte4 …XOR byteN-1, N = message length
	CalcuChecksum = c2_ABS_1_c^c3_ABS_1_c^c4_ABS_1_c^c5_ABS_1_c^c6_ABS_1_c^c7_ABS_1_c^c8_ABS_1_c;
	if(RxChecksum != CalcuChecksum)
	{
		uABS_1_ChecksumErrorTimes++;
		if(uABS_1_ChecksumErrorTimes >= 3)
		{
			uABS_1_ChecksumErrorTimes = 3;
		}
	}
	else
	{
		uABS_1_ChecksumErrorTimes = 0;
	}	
	
	uMessageTimeOutCntForGWNodeLost[ABS_1_MESSAGE] = 25;
	uMessageTimeOutCntForESPMissing[ABS_1_MESSAGE_1] = 25;

	DIF = (PreAliveCount > CurAliveCount)?(PreAliveCount-CurAliveCount):(CurAliveCount-PreAliveCount);

	if(PreAliveCount == CurAliveCount)
	{
		uABS_1_AliveCountError1Times++;
		if(uABS_1_AliveCountError1Times >= 5)
		{
			uABS_1_AliveCountError1Times = 5;
		}
	}
	else if(DIF > 2)
	{
		uABS_1_AliveCountError2Times++;
		if(uABS_1_AliveCountError2Times >= 3)
		{
			uABS_1_AliveCountError2Times = 3;
		}
	}	
	else
	{
		 if((PreAliveCount+1) == CurAliveCount)
		 {
			uABS_1_AliveCountError1Times = 0;
			uABS_1_AliveCountError2Times = 0;
		 }
	}
}





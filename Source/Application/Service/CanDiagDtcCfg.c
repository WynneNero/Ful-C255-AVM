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
#include "candiagdtccfg.h"
#include "can_par.h"
#include "can_def.h"
#include "EEPTable.h"
#include "Sig_Combine.H"
#include "Signal_IF.H"

#ifdef CAN_BUS_OPTION
#ifdef CAN_DIAG_OPTION
/*---Private----------------------------------------------------------*/
DTC_CODE_DATA_TYPE dtc_code_data[DTC_CODE_MAX_NUM] = 
{
	{0x9A, 0x81, 0x13},//DTC_FRONT_CAMERA_OPEN_CIRCUIT,   	//B1A8113 //0
	{0x9A, 0x82, 0x13},//DTC_LEFT_CAMERA_OPEN_CIRCUIT,    	//B1A8213
	{0x9A, 0x83, 0x13},//DTC_RIGHT_CAMERA_OPEN_CIRCUIT,   	//B1A8313
	{0x9A, 0x84, 0x13},//DTC_BACK_CAMERA_OPEN_CIRCUIT,    	//B1A8413 
	{0x9A, 0x85, 0x11},//DTC_FRONT_CAMERA_SHORT_GND,      	//B1A8511
	{0x9A, 0x85, 0x12},//DTC_FRONT_CAMERA_SHORT_BAT,      	//B1A8512
	{0x9A, 0x86, 0x11},//DTC_BACK_CAMERA_SHORT_GND,       	//B1A8611
	{0x9A, 0x86, 0x12},//DTC_BACK_CAMERA_SHORT_BAT,       	//B1A8612
	{0x9A, 0x87, 0x11},//DTC_LEFT_CAMERA_SHORT_GND,       	//B1A8711
	{0x9A, 0x87, 0x12},//DTC_LEFT_CAMERA_SHORT_BAT,      	//B1A8712
	{0x9A, 0x88, 0x11},//DTC_RIGHT_CAMERA_SHORT_GND,      	//B1A8811
	{0x9A, 0x88, 0x12},//DTC_RIGHT_CAMERA_SHORT_BAT,     	//B1A8812 
	
	{0x9A, 0x80, 0x17},//DTC_WORK_OVER_VOLTAGE,  	      	//B1A8017
	{0x9A, 0x80, 0x16},//DTC_WORK_BELOW_VOLTAGE,         	//B1A8016  
	{0x9A, 0x8A, 0x1C},//DTC_AVM_SYSTEM_ERROR,            	//B1A8A1C //14
	
	{0xC0, 0x37, 0x88},//DTC_CAN_BUS_ERROR,                 //U003788
	
	{0xC1, 0x46, 0x87},//DTC_LOST_GW_NODE,  			  	//U014687 
	{0xD1, 0x21, 0x87},//DTC_LOST_ESP_MESAGE,  		        //U112187
	{0xD2, 0x45, 0x87},//DTC_LOST_HU_MESSAGE                //U124587
	{0xD1, 0x40, 0x87},//DTC_LOST_BCM1_MESAGE,  			//U114087
	{0xD2, 0x93, 0x87},//DTC_LOST_HCU_MESAGE,				//U129387

	{0xC1, 0x59, 0x87},//DTC_LOST_PDC_NODE,  			    //U015987
	{0xD1, 0x64, 0x87},//DTC_LOST_ATC_MESAGE,  			    //U116487
	{0xD1, 0x99, 0x87},//DTC_LOST_LFDCU_MESAGE,  			//U119987
	{0xD2, 0x00, 0x87},//DTC_LOST_RFDCU_MESAGE,  			//U120087
	{0xD1, 0x46, 0x87},//DTC_LOST_GW_MESSAGE,  	            //U114687
	{0xD1, 0x31, 0x87},//DTC_LOST_EPS_MESAGE,  			    //U113187
	{0xD2, 0x30, 0x87},//DTC_LOST_PLG1_MESSAGE     	        //U123087
 	{0xD1, 0x01, 0x87},//DTC_LOST_TCU_MESAGE,     			//U110187  //27
	{0xC2, 0x32, 0x87},//DTC_LOST_LCDA_MESSAGE,				//U023287
	{0xD1, 0x00, 0x87},//DTC_LOST_EMS_MESSAGE,				//U110087
	{0xD1, 0x38, 0x87},//DTC_LOST_DMS_MESSAGE,				//U113887
	{0xD1, 0x55, 0x87},//DTC_LOST_IC_MESSAGE,				//U115587
	{0xD2, 0x01, 0x87},//DTC_LOST_RLDCU_MESSAGE,			//U120187
	{0xD2, 0x02, 0x87},//DTC_LOST_RLDCU_MESSAGE,			//U120287
			       
	{0xC4, 0x15, 0x82},//DTC_ESP_MESSAGE_LIVECOUNTER_ERROR,	  //U041582	
	{0xC4, 0x15, 0x83},//DTC_ESP_MESSAGE_CHECKSUM_ERROR,	  //U041583
	{0xC4, 0x15, 0x86},//DTC_ESP_MESSAGE_SIGNAL_INVALID, 	  //U041586
	{0xC4, 0x20, 0x82},//DTC_EPS_MESSAGE_LIVECOUNTER_ERROR,   //U042082		
	{0xC4, 0x20, 0x83},//DTC_EPS_MESSAGE_CHECKSUM_ERROR, 	  //U042083
	{0xC4, 0x20, 0x86},//DTC_EPS_MESSAGE_SIGNAL_INVALID, 	  //U042086 //33

	{0x9A, 0x89 , 0x48},//DTC_AVM_CALIBRATION_TROUBLE                 //B1A8948
};

DTC_RECORD_TYPE dtc_status_record[DTC_CODE_MAX_NUM] = {0x00};
DTC_RECORD_CNT_TYPE dtc_status_record_cnt[DTC_CODE_MAX_NUM] = {{0x00,0x00}};
BOOL bSetClearHistoryFaultCntFlag[DTC_CODE_MAX_NUM] = {0x00};
U8 dtc_status_occurrence_cnt[DTC_CODE_MAX_NUM] = {0x00};
U8 dtc_status_aging_cnt[DTC_CODE_MAX_NUM] = {0x00};
U8 dtc_status_aged_cnt[DTC_CODE_MAX_NUM] = {0x00};
U8 dtc_status_fid_data[DTC_CODE_MAX_NUM] = {0x00};

DTC_SNAPSHOT_RECORD_IDENTIFIERS dtc_snapshot_record[DTC_CODE_MAX_NUM] = {{0x00,0x00}};

BOOL bMessageLostStaForGWNodeLost[GW_MESSAGE_MONITOR_MAX]= {FALSE};
U8 uMessageTimeOutCntForGWNodeLost[GW_MESSAGE_MONITOR_MAX] = {0};

BOOL bMessageLostForESPMissing[ESP_MESSAGE_MONITOR_MAX]= {FALSE};
U8 uMessageTimeOutCntForESPMissing[ESP_MESSAGE_MONITOR_MAX] = {0};

BOOL bMessageLostForBCM1Missing[BCM1MESSAGE_MONITOR_MAX]= {FALSE};
U8 uMessageTimeOutCntForBCM1Missing[BCM1MESSAGE_MONITOR_MAX] = {0};

BOOL bMessageLostForHCUMissing[HCUMESSAGE_MONITOR_MAX]= {FALSE};
U8 uMessageTimeOutCntForHCUMissing[HCUMESSAGE_MONITOR_MAX] = {0};

// BOOL bMessageLostForPDCMissing[PDCMESSAGE_MONITOR_MAX]= {FALSE};
// U8 uMessageTimeOutCntForPDCMissing[PDCMESSAGE_MONITOR_MAX] = {0};

BOOL bMessageLostForHUMissing[HU_MESSAGE_MONITOR_MAX]= {FALSE};
U8 uMessageTimeOutCntForHUMissing[HU_MESSAGE_MONITOR_MAX] = {0};

BOOL bMessageTimeOutStatus[MESSAGE_TIMEOUT_TYPE_NUMBER] = {FALSE};
U16 uMessageTimeOutCnt[MESSAGE_TIMEOUT_TYPE_NUMBER] = {0};
U16 uMessageTimeoutStartTime[MESSAGE_TIMEOUT_TYPE_NUMBER] =		//t=N*20MS  TIMEOUT=t*20
{
	50,	//PDC_1 
    50,	//ATC_2      
//    50,	//BCM1_1
    50,	//DDCU_1 
    50,	//PDCU_1 
    25,	//MCP_1 
    25,	//SAS_1
    50, //PLG_1
    25, //TCU_3
	50, //LCDA_1
	25, //EMS_3
	50, //DMS_2
	50, //IC_1
	50, //RLDCU_1
	50, //RRDCU_1
};

U8 FID_Definition[FID_DEFINITION_MAX_INDEX] = 
{
	0x01, //ABS_1(0xC0) is missing
	0x02, //ABS_2(0xC2) is missing
	0x03, //ESP_2(0x132) is missing
//	0x04, //DP_1(0x1A5) is missing
	0x06, //HU_5(0x288) is missing
	0x08, //IC_1(0x290) is missing
	0x09, //Livecounter_ABS_1: same counts are received. or Two consecutive cycles counter values are greater than 2.
	0x0A, //Livecounter_ABS_2: same counts are received. or Two consecutive cycles counter values are greater than 2.
	0x0B, //Livecounter_ESP_2: same counts are received. or Two consecutive cycles counter values are greater than 2.
	0x0C, //Checksum_ABS_1: received and calculated values are inconsistent
	0x0D, //Checksum_ABS_2: received and calculated values are inconsistent
	0x0E, //Checksum_ESP_2: received and calculated values are inconsistent
	0x0F, //Signal invalid error: WheelSpeed_FL = Invalid Value
	0x10, //Signal invalid error: WheelSpeed_FR = Invalid Value
	0x11, //Signal invalid error: WheelSpeed_RL = Invalid Value
	0x12, //Signal invalid error: WheelSpeed_RR = Invalid Value
	0x13, //Signal invalid error: VehicleSpeed = Invalid Value
};



BOOL bDTCRecordStatus[DTC_MAX_NUM_INDEX] = {FALSE};

#endif
#endif



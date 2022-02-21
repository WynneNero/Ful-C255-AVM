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
#ifndef _CAN_DIAG_DTC_DIAG_H_
#define _CAN_DIAG_DTC_DIAG_H_
#include "config.h"
//#ifdef CAN_DIAG_OPTION
/**** Definition of constants ****/

#include "CanDiagDtc.h"

//#define DIAG_TEMPERATURE_OPTION
#define DIAG_NM_TIMEOUT_NOT_USE_IL_TIMEOUT_FLAG
//#define DIAG_F1B9_NOT_CONFIG
#define DIAG_INNER_COMMUNICATION
#define DIAG_AVM_CALIBRATION
#define DTC_AGING_COUNTER
//#define DIAG_AVM_ONOFF_SWITCH
//#define DIAG_LED_INDICATOR
//#define USE_AD_CHECK_POWER
//#define DTC_AGING_COUNTER
//#define DIAG_AVM_ONOFF_SWITCH
//#define DIAG_INNER_COMMUNICATION
#define DTC_STATUS_AGING_CNT_HEALING      40
#define DTC_STATUS_AGING_CNT_RESET        0
#define DTC_STATUS_OCCURRENCE_CNT_MAX     255 - 1
#define DTC_STATUS_OCCURRENCE_CNT_RESET   0
#define DTC_STATUS_AGED_CNT_MAX           255
#define DTC_STATUS_AGED_CNT_RESET         0



/**** Definition of types ****/ 
typedef enum DTC_CODE_NUM_TYPE_TAG
{
	DTC_FRONT_CAMERA_OPEN_CIRCUIT,   	//B1A8113 //0
	DTC_LEFT_CAMERA_OPEN_CIRCUIT,    	//B1A8213
	DTC_RIGHT_CAMERA_OPEN_CIRCUIT,   	//B1A8313
	DTC_BACK_CAMERA_OPEN_CIRCUIT,    	//B1A8413 
	DTC_FRONT_CAMERA_SHORT_GND,      	//B1A8511
	DTC_FRONT_CAMERA_SHORT_BAT,      	//B1A8512
	DTC_BACK_CAMERA_SHORT_GND,       	//B1A8611
	DTC_BACK_CAMERA_SHORT_BAT,       	//B1A8612
	DTC_LEFT_CAMERA_SHORT_GND,       	//B1A8711
	DTC_LEFT_CAMERA_SHORT_BAT,      	//B1A8712
	DTC_RIGHT_CAMERA_SHORT_GND,      	//B1A8811
	DTC_RIGHT_CAMERA_SHORT_BAT,     	//B1A8812 
	
	DTC_WORK_OVER_VOLTAGE,  	      	//B1A8017
	DTC_WORK_BELOW_VOLTAGE,         	//B1A8016  
	DTC_AVM_SYSTEM_ERROR,            	//B1A8A1C //14
	
	DTC_CAN_BUS_ERROR,                  //U003788
	
	DTC_LOST_GW_NODE,  			  	    //U014687 
	DTC_LOST_ESP_MESAGE,  		        //U112187
	DTC_LOST_HU_MESSAGE,                //U124587
	DTC_LOST_BCM1_MESAGE,  			    //U114087
	DTC_LOST_HCU_MESAGE,				//U129387
	
	DTC_LOST_PDC_NODE,  			    //U015987
	DTC_LOST_ATC_MESAGE,  			    //U116487
	DTC_LOST_LFDCU_MESAGE,  			//U119987
	DTC_LOST_RFDCU_MESAGE,  			//U120087
	DTC_LOST_GW_MESSAGE,  	            //U114687
	DTC_LOST_EPS_MESAGE,  			    //U113187
	DTC_LOST_PLG1_MESSAGE,     	        //U123087
 	DTC_LOST_TCU_MESAGE,     			//U110187  //28
	DTC_LOST_LCDA_MESSAGE,				//U023287  //29
	DTC_LOST_EMS_MESSAGE,				//U110087
	DTC_LOST_DMS_MESSAGE,				//U113887
	DTC_LOST_IC_MESSAGE,				//U115587
	DTC_LOST_RLDCU_MESSAGE,				//U120187
	DTC_LOST_RRDCU_MESSAGE,				//U120287
			       
	DTC_ESP_MESSAGE_LIVECOUNTER_ERROR,	//U041582	
	DTC_ESP_MESSAGE_CHECKSUM_ERROR,     //U041583
	DTC_ESP_MESSAGE_SIGNAL_INVALID, 	//U041586
	DTC_EPS_MESSAGE_LIVECOUNTER_ERROR,  //U042082		
	DTC_EPS_MESSAGE_CHECKSUM_ERROR, 	//U042083
	DTC_EPS_MESSAGE_SIGNAL_INVALID, 	//U042086 	

	DTC_AVM_CALIBRATION_TROUBLE,        //B1A8948 //40
	
    DTC_CODE_MAX_NUM,
} DTC_CODE_NUM_TYPE;

enum DTC_MESSAGE_NUM_TAG
{
	DTC_LOST_GW_NODE_INDEX,  					//U014687 
	DTC_LOST_ESP_MESAGE_INDEX,  		        //U112187
	DTC_LOST_HU_MESSAGE_INDEX,                	//U124587

	DTC_LOST_PDC_MESAGE_INDEX,  			    //U015987
	DTC_LOST_ATC_MESAGE_INDEX,  			    //U116487
//	DTC_LOST_BCM1_MESAGE_INDEX,  			    //U114087
	DTC_LOST_LFDCU_MESAGE_INDEX,  				//U119987
	DTC_LOST_RFDCU_MESAGE_INDEX,  				//U120087
	DTC_LOST_GW_MESSAGE_INDEX,  	            //U114687
	DTC_LOST_EPS_MESAGE_INDEX,  			    //U113187
	DTC_LOST_PLG1_MESSAGE_INDEX,     	        //U123087
 	DTC_LOST_TCU_MESSAGE_INDEX,     			//U110187  //28
	DTC_LOST_LCDA_MESSAGE_INDEX,     			//U023287 
	DTC_LOST_EMS_MESSAGE_INDEX,					//U110087
	DTC_LOST_DMS_MESSAGE_INDEX,					//U113887
	DTC_LOST_IC_MESSAGE_INDEX,					//U115587
	DTC_LOST_RLDCU_MESSAGE_INDEX,				//U120187
	DTC_LOST_RRDCU_MESSAGE_INDEX,				//U120287
	DTC_MAX_NUM_INDEX,
} ;

enum MESSAGE_NUM_TYPE_TAG
{
	MESSAGE_PDC_1_LOST_INDEX,
	MESSAGE_ATC_2_LOST_INDEX,					
//	MESSAGE_BCM1_1_LOST_INDEX,				   
	MESSAGE_DDCU_1_LOST_INDEX,					
	MESSAGE_PDCU_1_LOST_INDEX,			   
	MESSAGE_MCP_1_LOST_INDEX,			    
	MESSAGE_SAS_1_LOST_INDEX,  			   
	MESSAGE_PLG_1_LOST_INDEX,					
	MESSAGE_TCU_3_LOST_INDEX,
	MESSAGE_LCDA_1_LOST_INDEX,	
	MESSAGE_EMS_3_LOST_INDEX,
	MESSAGE_DMS_2_LOST_INDEX,
	MESSAGE_IC_1_LOST_INDEX,
	MESSAGE_RLDCU_1_LOST_INDEX,	
	MESSAGE_RRDCU_1_LOST_INDEX,			
    MESSAGE_TIMEOUT_TYPE_NUMBER,
};
	
enum MESSAGE_TIMEOUT_FOR_GW_NODE_LOST
{
	ABS_1_MESSAGE,
	ABS_2_MESSAGE,
	ESP_2_MESSAGE,
	ATC_2_MESSAGE,
	BCM1_1_MESSAGE,
	BCM1_2_MESSAGE,
	DDCU_1_MESSAGE,
	DMS_2_MESSAGE,
	EMS_3_MESSAGE,
	GW_CONFIG_MESSAGE,
	MCP_1_MESSAGE,
	HU_5_MESSAGE,
	HU_6_MESSAGE,
	HU_20_MESSAGE,
	IC_1_MESSAGE,
	PDCU_1_MESSAGE,
	PLG_1_MESSAGE,
	RLDCU_1_MESSAGE,
	RRDCU_1_MESSAGE,
	SAS_1_MESSAGE,
	TCU_3_MESSAGE,
	GW_MESSAGE_MONITOR_MAX,
};

enum FID_DEFINITION_TYPE
{
	ABS_1_MESSAGE_MISSING_FID_INDEX,
	ABS_2_MESSAGE_MISSING_FID_INDEX,
	ESP_2_MESSAGE_MISSING_FID_INDEX,
//	DP_1_MESSAGE_MISSING_FID_INDEX,
	HU_5_MESSAGE_MISSING_FID_INDEX,
	IC_1_MESSAGE_MISSING_FID_INDEX,
	ABS_1_LIVECOUNTER_ERR_FID_INDEX,
	ABS_2_LIVECOUNTER_ERR_FID_INDEX,
	ESP_2_LIVECOUNTER_ERR_FID_INDEX,
	ABS_1_CHECKSUM_ERR_FID_INDEX,
	ABS_2_CHECKSUM_ERR_FID_INDEX,
	ESP_2_CHECKSUM_ERR_FID_INDEX,
	WHEEL_FL_INVALID_FID_INDEX,
	WHEEL_FR_INVALID_FID_INDEX,
	WHEEL_RL_INVALID_FID_INDEX,	
	WHEEL_RR_INVALID_FID_INDEX,
	VEHICLE_SPPED_INVALID_FID_INDEX,
	FID_DEFINITION_MAX_INDEX,
};


enum MESSAGE_TIMEOUT_FOR_ESP_MESSAGE_LOST
{
	ABS_1_MESSAGE_1,
	ABS_2_MESSAGE_1,
	ESP_2_MESSAGE_1,
	ESP_MESSAGE_MONITOR_MAX,
};

enum MESSAGE_TIMEOUT_FOR_BCM1_MESSAGE_LOST
{
	BCM1_1_MESSAGE_1,
	BCM1_2_MESSAGE_1,
	BCM1MESSAGE_MONITOR_MAX,
};

enum MESSAGE_TIMEOUT_FOR_HCU_NODE_LOST
{
	EMS_3_MESSAGE_1,
	TCU_3_MESSAGE_1,
	HCUMESSAGE_MONITOR_MAX,
};

// enum MESSAGE_TIMEOUT_FOR_PDC_NODE_LOST
// {
// 	PDC_3_MESSAGE,
// 	PDC_4_MESSAGE,
// 	PDC_9_MESSAGE,
// 	PDCMESSAGE_MONITOR_MAX,
// };

enum MESSAGE_TIMEOUT_FOR_HU_MESSAGE_LOST
{
	HU_5_MESSAGE_1,
	HU_6_MESSAGE_1,
	HU_20_MESSAGE_1,
	HU_MESSAGE_MONITOR_MAX,
};

#define BIT30						30
#define DTC_CODE_MAX_NUM1           (DTC_CODE_MAX_NUM - BIT30)

#define VEHICLESPEED_DTC_SNAPSHOT_DATAIDENTIFIER 0x0100
#define ODOMETER_DTC_SNAPSHOT_DATAIDENTIFIER     0x0101
#define SUPPLYVOLTAGE_DTC_SNAPSHOT_DATAIDENTIFIER     0x0102

#define DTC_OCCURRENCE_CNT        0x01
#define DTC_AGING_CNT			  0x02	
#define DTC_AGED_CNT              0x03
#define DTC_FID                   0x04
#define ALL_EXTENDED_DATA_RECORDS 0xFF

#define DTC_SNAPSHOT_RECORD_NUMBER 0x01
#define DTC_SNAPSHOT_RECORD_NUMBER_OF_IDENTIFIERS 0x03
#define DTC_SNAPSHOT_RECORD_NUMBER_LEN 19

#define NM_TIMEOUT_START_INDEX  DTC_LOST_PDC_NODE
//#define NM_TIMEOUT_END_INDEX  	DTC_LOST_BCM2
//#define NM_TIMEOUT_TYPE_NUMBER (NM_TIMEOUT_END_INDEX+1-NM_TIMEOUT_START_INDEX)

#define CANDTC_CIRCUIT_CHECK_START_INDEX 	DTC_FRONT_CAMERA_OPEN_CIRCUIT
#define CANDTC_CIRCUIT_CHECK_END_INDEX 		DTC_WORK_OVER_VOLTAGE
#define CANDTC_CIRCUIT_CHECK_TYPE_NUMBER 	(CANDTC_CIRCUIT_CHECK_END_INDEX+1-CANDTC_CIRCUIT_CHECK_START_INDEX)

#define BUS_OFF_CONFIRM_TIMES  14 //bus-off continuous 3 times are detected(150MS)
/**** Definition of macros ****/
/*
Bit0  testFailed                            M 
Bit1  testFailedThisOperationCycle          U     /    M for aging
Bit2  pendingDTC                            U 
Bit3  confirmedDTC                          M 
Bit4  testNotCompletedSinceLastClear        U
Bit5  testFailedSinceLastClear              U 
Bit6  testNotCompletedThisOperationCycle    U     /    M for aging
Bit7  WarningIndicator                      U
*/
#define DTC_STATUS_AVAILABILITY_MASK    (DTC_STATUS_BIT0_MASK_TF|DTC_STATUS_BIT3_MASK_CDTC|DTC_STATUS_BIT6_MASK_TNCTOC)///0x49
#define DTC_FORMAT_INDENTIFIER 0x00   //ISO15031-6DTC format

/**** Declaration of constants ****/
#define DTC_STATUS_SVC14_CLEAR_FINISHED (DTC_CODE_MAX_NUM+1)
#define DTC_STATUS_SVC14_CLEAR_START 0
#define DTC_NETWORK_GRP_START   DTC_CAN_BUS_ERROR  

/* ECU operation Voltage low:7~9v */
/* Monitor cycle: 10ms. It means checking the volt for each 10ms */
/* Set condition max checking counter:10 */
/* Clear condition max checking counter:10 */
#define DTC_CHECK_MONITOR_CYCLE_OP_VOLT_LOW 1 /*10ms = 10*CAN_DIAG_TASK_SCHEDULE_TIME */
#define DTC_SET_OP_VOLT_LOW_CNT_MAX 10
#define DTC_CLR_OP_VOLT_LOW_CNT_MAX 10

/* ECU operation Voltage high:16~18v */
/* Monitor cycle: 10ms. It means checking the volt for each 10ms */
/* Set condition max checking counter:10 */
/* Clear condition max checking counter:10 */
#define DTC_CHECK_MONITOR_CYCLE_OP_VOLT_HIGH 1 /*10ms = 1s*CAN_DIAG_TASK_SCHEDULE_TIME */
#define DTC_SET_OP_VOLT_HIGH_CNT_MAX 10
#define DTC_CLR_OP_VOLT_HIGH_CNT_MAX 10


/* transceiver error monitor */
/* Monitor cycle: 10ms. It means checking for each 10ms */
/* Set condition max checking counter:10 */
/* Clear condition max checking counter:10 */
#define DTC_CHECK_MONITOR_CYCLE_TRANSCEIVER_ERR 1 /*10ms = 1*CAN_DIAG_TASK_SCHEDULE_TIME */
#define DTC_SET_TRANSCEIVER_ERR_CNT_MAX 10
#define DTC_CLR_TRANSCEIVER_ERR_CNT_MAX 10

#ifdef DIAG_INNER_COMMUNICATION
#define DTC_CHECK_MONITOR_CYCLE_INNERCOMMU_ERR 1 /*10ms = 1*CAN_DIAG_TASK_SCHEDULE_TIME */
#define DTC_SET_INNERCOMMU_ERR_CNT_MAX 10
#define DTC_CLR_INNERCOMMU_ERR_CNT_MAX 10
#endif

#ifdef DIAG_AVM_ONOFF_SWITCH
#define DTC_CHECK_MONITOR_CYCLE_AVM_ONOFF_KEY_ERR 1 /*10ms = 1*CAN_DIAG_TASK_SCHEDULE_TIME */
#define DTC_SET_AVM_ONOFF_KEY_ERR_CNT_MAX 10
#define DTC_CLR_AVM_ONOFF_KEY_ERR_CNT_MAX 10
#endif

#ifdef DIAG_AVM_CALIBRATION
#define DTC_CHECK_MONITOR_CYCLE_AVM_CALIBRATION_ERR 1 /*10ms = 1*CAN_DIAG_TASK_SCHEDULE_TIME */
#define DTC_SET_AVM_CALIBRATION_ERR_CNT_MAX 1
#define DTC_CLR_AVM_CALIBRATION_ERR_CNT_MAX 1
#endif

#define DTC_SET_LED_INDICATOR_ERR_CNT_MAX 1
#define DTC_CLR_LED_INDICATOR_ERR_CNT_MAX 1

/* bus off monitor */
/* Monitor cycle: 10ms. It means checking for each 10ms */
/* Set condition max checking counter:10 */
/* Clear condition max checking counter:10 */
#define DTC_CHECK_MONITOR_CYCLE_BUS_OFF 1 /*10ms = 1*CAN_DIAG_TASK_SCHEDULE_TIME */
#define DTC_SET_BUS_OFF_CNT_MAX 1
#define DTC_CLR_BUS_OFF_CNT_MAX 1

/* camera fault monitor */
/* Monitor cycle: 10ms. It means checking for each 10ms */
/* Set condition max checking counter:10 */
/* Clear condition max checking counter:10 */
#define DTC_CHECK_MONITOR_CYCLE_CIRCUIT_FAULT 1 /*10ms = 1*CAN_DIAG_TASK_SCHEDULE_TIME */
#define DTC_SET_CIRCUIT_SHORT_CNT_MAX 	5	/*100ms=5*20ms*/
#define DTC_CLR_CIRCUIT_SHORT_CNT_MAX 	5
#define DTC_SET_CIRCUIT_OPEN_CNT_MAX 	50	/*1000ms=50*20ms*/
#define DTC_CLR_CIRCUIT_OPEN_CNT_MAX 	50

/* temp status monitor */
/* Monitor cycle: 10ms. It means checking for each 10ms */
/* Set condition max checking counter:10 */
/* Clear condition max checking counter:10 */
#define DTC_CHECK_MONITOR_CYCLE_TEMP_FAULT 1 /*10ms = 1*CAN_DIAG_TASK_SCHEDULE_TIME */
#define DTC_SET_TEMP_FAULT_CNT_MAX 10
#define DTC_CLR_TEMP_FAULT_CNT_MAX 10

/* Lost Communications with other nodes */
/* Monitor cycle: 10ms. It means checking the timeout flag from IL for each 10ms, jus the same as task-clycle */
/* Set condition max checking counter:1 */
/* Clear condition max checking counter:1 */
#define DTC_CHECK_MONITOR_CYCLE_LOST_COMM 1 /*10ms = 1*CAN_DIAG_TASK_SCHEDULE_TIME */
#define DTC_SET_LOST_COMM_CNT_MAX 1
#define DTC_CLR_LOST_COMM_CNT_MAX 1

/**** Declaration of constants ****/
#define CAN_DIAG_TASK_SCHEDULE_TIME 10 /* 10ms */

/* All dtc diag delay */
#define CAN_DIAG_INIT_DELAY_TIME     25 /* 500ms = 50*CAN_DIAG_TASK_SCHEDULE_TIME */
#define CAN_DIAG_INIT_DELAY_TIMEOUT  0

/* Network related dtc diag delay */
#define CAN_DIAG_NM_INIT_DELAY_TIME     50 /* 1000ms = 100*CAN_DIAG_TASK_SCHEDULE_TIME */
#define CAN_DIAG_NM_INIT_DELAY_TIMEOUT  0

/*Network ign on related dtc diag delay*/
#define CAN_DIAG_NM_IGN_ON_DELAY_TIME     85   /* 1700ms */
#define CAN_DIAG_NM_IGN_ON_DELAY_TIMEOUT  0

#define CAN_DIAG_BAT_VOLT_RECOVER_DELAY_TIME    35    /*voltage threshold recover delay, 700ms = 35*20ms */
#define CAN_DIAG_BAT_VOLT_RECOVER_DELAY_TIMEOUT  0

#define VOLTAGE_9V   1610   //9V
#define VOLTAGE_9V5  1689  //9.5V
#define VOLTAGE_16V  2902   //16V 
#define VOLTAGE_15V5 2810   //15.5v



 typedef  struct
{
	U16 Snapshot0100_VehicleSpeed;
	U32 Snapshot0101_Odometer;
	U8 Snapshot0102_SupplyVoltage;
}DTC_SNAPSHOT_RECORD_IDENTIFIERS;

typedef  struct
{
	U8 ExtDataRecord_occurrence;
	U8 ExtDataRecord_aging;
	U8 ExtDataRecord_aged;
}DTC_EXTDATARECORD;;


/**** Declaration of functions ****/
extern DTC_CODE_DATA_TYPE dtc_code_data[DTC_CODE_MAX_NUM];
extern DTC_RECORD_TYPE dtc_status_record[DTC_CODE_MAX_NUM];
extern DTC_RECORD_CNT_TYPE dtc_status_record_cnt[DTC_CODE_MAX_NUM];
extern BOOL bSetClearHistoryFaultCntFlag[DTC_CODE_MAX_NUM];
extern U8 dtc_status_occurrence_cnt[DTC_CODE_MAX_NUM];
extern U8 dtc_status_aging_cnt[DTC_CODE_MAX_NUM];
extern U8 dtc_status_aged_cnt[DTC_CODE_MAX_NUM];
extern DTC_SNAPSHOT_RECORD_IDENTIFIERS dtc_snapshot_record[DTC_CODE_MAX_NUM];
extern DTC_SNAPSHOT_RECORD_IDENTIFIERS Can_Signal_Snapshot_Data;
extern BOOL bMessageLostStaForGWNodeLost[GW_MESSAGE_MONITOR_MAX];
extern U8 uMessageTimeOutCntForGWNodeLost[GW_MESSAGE_MONITOR_MAX];
extern BOOL bMessageLostForESPMissing[ESP_MESSAGE_MONITOR_MAX];
extern U8 uMessageTimeOutCntForESPMissing[ESP_MESSAGE_MONITOR_MAX];
extern BOOL bMessageLostForBCM1Missing[BCM1MESSAGE_MONITOR_MAX];
extern U8 uMessageTimeOutCntForBCM1Missing[BCM1MESSAGE_MONITOR_MAX];
extern BOOL bMessageLostForHCUMissing[HCUMESSAGE_MONITOR_MAX];
extern U8 uMessageTimeOutCntForHCUMissing[HCUMESSAGE_MONITOR_MAX];
// extern BOOL bMessageLostForPDCMissing[PDCMESSAGE_MONITOR_MAX];
// extern U8 uMessageTimeOutCntForPDCMissing[PDCMESSAGE_MONITOR_MAX];
extern BOOL bMessageLostForHUMissing[HU_MESSAGE_MONITOR_MAX];
extern U8 uMessageTimeOutCntForHUMissing[HU_MESSAGE_MONITOR_MAX];
extern BOOL bMessageTimeOutStatus[MESSAGE_TIMEOUT_TYPE_NUMBER];
extern U16 uMessageTimeOutCnt[MESSAGE_TIMEOUT_TYPE_NUMBER];
extern U16 uMessageTimeoutStartTime[MESSAGE_TIMEOUT_TYPE_NUMBER];
extern BOOL bDTCRecordStatus[DTC_MAX_NUM_INDEX];
extern U8 FID_Definition[FID_DEFINITION_MAX_INDEX];
extern U8 dtc_status_fid_data[DTC_CODE_MAX_NUM];

//#endif
#endif


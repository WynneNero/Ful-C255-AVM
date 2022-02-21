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
* Ver  Date         Name       Changes and comments
*----------------------------------------------------------------------
*  0.1 Sep 26,2016 init version.
*----------------------------------------------------------------------
*  0.2 Dec 20,2016 ShangQiuju Add exti_if.h for compile fail.
*----------------------------------------------------------------------
*  0.3 Jan 24,2017 ZhangJie     Fix Coverity warning.
*----------------------------------------------------------------------
*  0.4 Feb 07,2017 ZhangJie     Define GPIO as micro.
*----------------------------------------------------------------------
*  0.5 Feb 09,2017 ZhangJie     Include diag head files for compile warning.
*----------------------------------------------------------------------
*  0.6 Feb 09,2017 ZhangJie     Remove wakeup source configuration.
*----------------------------------------------------------------------
*  0.7 Feb 20,2017 ZhangJie     Remove can protocol code to CANmanager.c.
*=====================================================================*/
#include "CanApp.h"
#include "Can_App_il.h"
#include "CanSig_Def.h"
#include "CanSig_cfg.h"
#include "can_cfg.h"
#include "can_def.h"
#include "Cansig_cfg_if.h"
#include "iodefine.h"
#include "SocCommunicator.H"
#include "il_inc.h"
#include "il_par.h"
#include "Sig_Combine.H"
#include "Signal_IF.H"
#include "NaviApp.h"
#include "CanDiagService.h"
#include "GPIO_IF.H"
#include "Pwmd_if.h"
#include "M4MsgHandler_IF.h"
#include "AVM_DR.h"


/*---Global-----------------------------------------------------------*/

BOOL bReqToSendLeverInfoSignal = FALSE;
BOOL bReqToSendTurnSignal = FALSE;
BOOL bReqToSendSpeedSignal = FALSE;
BOOL bReqToSendIGNstatus = FALSE;
BOOL bReqToSendCoordinateResolution = FALSE;
BOOL bReqToSendSteerWheelAngleSignal = FALSE;
BOOL bReqToSenddoortatus = FALSE;
BOOL bReqToSendRearviewMirrorSt = FALSE;
BOOL bReqToSendRadarDistance = FALSE;
BOOL bReqToSendSpeechReqSignal = FALSE;
BOOL bReqToSendViewModeReqSignal = FALSE;
BOOL bReqToSendLanguageSetReqSignal = FALSE;
BOOL bReqReportcamerafault = FALSE;
BOOL bReqToSendBlindSpotFilled = FALSE;
BOOL bReqToSendTrunFollowUp = FALSE;
BOOL bReqToSendRCTASt = FALSE;
BOOL bReqToSendPDCSensorErrorSt = FALSE;
BOOL bReqToSendPDCSensorBlockageSt = FALSE;
BOOL bReqToSendPDCAndRadarSt = FALSE;
BOOL bReqToSendDynamicPGSSt = FALSE;

BOOL SVP_SUCCEED_FLAG = FALSE;
DTC_SNAPSHOT_RECORD_IDENTIFIERS Can_Signal_Snapshot_Data;
U16 can_vehiclespeed_backup=0;
U8 AVM_Speech_Req = 0;
U8 GW_OTAMode_fun = 0x00;

/*===FUNCTIONS========================================================*/
void CanAppGetEngStatus(U8* data);

void SocCan_20ms_Entry(void)
{
	can_acckey_rxhandler();
	can_avm_act_req_rxhandler();
	can_vehiclespeed_rxhandler();
	can_LeverInfo_rxhandler();
	can_steering_angle_rxhandler();
	can_coordinate_rxhandler();
	can_VehicleOdometer_rxhandler();
	CAN_CarDoorStaus_rxhandler();
	CAN_CarRearviewMirrorSt_rxhandler();
	can_radar_distance_value_msg_rxhandler();
	can_PDCAndRadarSt_rxhander();
	can_PDCSensorErrorSt_rxhander();
	can_PDCSensorBlockageSt_rxhander();
	can_AVM_LED_Control();
	can_turnlamp_rxhandler();
	can_SetLanguage_rxhandler();
	can_AVM_ViewModeControl_rxhandler();
	can_FactoryModeReq_rxhandler();
	can_BlindSpotFilledReq_rxhandler();
	can_AVSTurnFollowUpFunctionReq_rxhander();
	can_RCTASt_rxhander();
	can_DynamicPGSSt_rxhandler();
	
	can_AVSErrorSt_txhandler();
	can_AVSStatus_txhandler();

	can_CameraErrorSt_txhandler();
	can_OTAMode_rxhandler();
}

void can_sig_init(void)
{
	U8 AVM_LanedepartureSt_initValue = 2;
	bReqToSendCoordinateResolution = FALSE;
	bReqToSendLeverInfoSignal = FALSE;
	bReqToSendTurnSignal = FALSE;
	bReqToSendSpeechReqSignal = FALSE;
	bReqToSendSpeedSignal = FALSE;
	bReqToSendIGNstatus = FALSE;
	bReqToSendViewModeReqSignal = FALSE;
	bReqToSendLanguageSetReqSignal = FALSE;
	bReqToSendSteerWheelAngleSignal = FALSE;
	bReqToSenddoortatus = FALSE;
	bReqToSendRadarDistance = FALSE;
	SVP_SUCCEED_FLAG = FALSE;
	bJ6_start_complete = FALSE;
	bReqToSendRearviewMirrorSt = FALSE;
	bReqToSendBlindSpotFilled = FALSE;
	bReqToSendTrunFollowUp = FALSE;
	bReqToSendRCTASt = FALSE;
	bReqToSendDynamicPGSSt = FALSE;
	bReqToSendPDCSensorErrorSt = FALSE;
	bReqToSendPDCSensorBlockageSt = FALSE;
	bReqToSendPDCAndRadarSt = FALSE;
}

BOOL GetNMTimeOutFlag(U8 nodeindex)
{
    return(bMessageTimeOutStatus[nodeindex]);
}

BOOL GetMessageTimeOutFlag(U8 nodeindex)
{
    return(bMessageLostStaForGWNodeLost[nodeindex]);
}

void can_vehiclespeed_rxhandler(void)
{
	U32 spd_cal;
	static U16 can_vehiclespeed=0,phy_vehiclespeed=0;
	U8 arg[2];

	/* The Vehicle speed message missing: 0x8000 */
	if(GetMessageTimeOutFlag(ABS_1_MESSAGE))
	{	
		if(EolApp_IsEolActivated() == FALSE)
		{
			can_vehiclespeed = SPEED_MISSING_VALUE;	
		}else{
			can_vehiclespeed = 0;
		}
		phy_vehiclespeed = 0;
	}
	else
	{
		can_vehiclespeed = can_receive_sig(VehicleSpeed);
		/* Bus value range:0x0000-0x7FFE */
		if(can_vehiclespeed >= SPEED_ERROR_VALUE) //error value
		{
			can_vehiclespeed = SPEED_ERROR_VALUE;
		}
		phy_vehiclespeed = can_vehiclespeed;
	}
	
	Can_Signal_Snapshot_Data.Snapshot0100_VehicleSpeed = can_vehiclespeed;	

	/* Formula: Physical value = 0.01*bus value */
	phy_vehiclespeed = (U16)(phy_vehiclespeed/100); //x*0.01 = km/h 
//	if(can_vehiclespeed > 15)//标定值
//	{
//		can_send_sig(AVS_AbnormalTip,0x1); //speed too high exit AVS 
//	}
	
	if(phy_vehiclespeed!=can_vehiclespeed_backup)
	{
		can_vehiclespeed_backup = phy_vehiclespeed;
		arg[0] = (U8)(phy_vehiclespeed>>8);
		arg[1] = (U8)(phy_vehiclespeed&0xFF);
		SocManager_SendMsg(LQ_CMD,TYPE_EVENT,RADIO_NOTIFY_SPEED_DATA,2,arg);
	}
	
	if(bReqToSendSpeedSignal)
	{
		bReqToSendSpeedSignal = FALSE;
		can_vehiclespeed_backup = phy_vehiclespeed;
		arg[0] = (U8)(phy_vehiclespeed>>8);
		arg[1] = (U8)(phy_vehiclespeed&0xFF);
		SocManager_SendMsg(LQ_CMD,TYPE_EVENT,RADIO_NOTIFY_SPEED_DATA,2,arg);
	}
	//can_vehiclespeed = 200;
    M4Msg_Update(E_M4_VehicleSpeed_U16, phy_vehiclespeed);
	M4Msg_Update(E_M4_FLWheelSpeed_U16,phy_vehiclespeed);
	M4Msg_Update(E_M4_FRwheelSpeed_U16,phy_vehiclespeed);
	M4Msg_Update(E_M4_RLwheelSpeed_U16,phy_vehiclespeed);
	M4Msg_Update(E_M4_RRwheelSpeed_U16,phy_vehiclespeed);
}

static void CanAppAvmSteeringAngleSmallChange(U16 steeringAngle, U8 steeringDirection)
{
	U8 steeringWheelDir =0;
	static U8 steeringWheelDir_backup =0;

	/**/
	if(steeringAngle <= 5)
 	{
 		steeringWheelDir = steeringWheelDir_center;	
	}
	else if(steeringDirection==STEERING_DIRECT_RIGHT)
	{
		steeringWheelDir = steeringWheelDir_right;
	}
	else if(steeringDirection == STEERING_DIRECT_LEFT)
	{
		steeringWheelDir = steeringWheelDir_left;		
	}	 
	else 
	{
		/*do nothing */
	}		
		 
	if((steeringWheelDir_backup != steeringWheelDir) || bReqToSendSteerWheelAngleSignal)
	{
		steeringWheelDir_backup = steeringWheelDir;
		SocManager_SendMsg(HQ_CMD,TYPE_EVENT, RADIO_NOTIFY_STEERING_WHEEL_DIRECTION, 1, &steeringWheelDir); //443F
	}
}

void can_steering_angle_rxhandler(void)
{
	U8 arg[3];
	static U8 steering_angle_dir = 0;
	static U8 steering_angle_dir_backup = 0xFF; //invalid
	static U16 steering_angle_value = 0;
	static U16 wheel_angle_value = 0;
	static U16 wheel_angle_value_backup = 0;

	steering_angle_value = can_receive_sig(SteeringWAngle);
	steering_angle_dir = can_receive_sig(SteeringWAngleSign);
	
	if(steering_angle_value>=ERROR_VALUE_RANGE) 
	{
		return;
	}
	steering_angle_value = steering_angle_value * 0.04357 ;
//	steering_angle_value = (U16)((steering_angle_value * ANGLE_DATA_MAX) / CAN_ANGLE_DATA_RANGE_HIGH);
	
	wheel_angle_value = steering_angle_value/16;

	if(wheel_angle_value>40) 
	{
		return;
	}
	
	if((steering_angle_dir!=steering_angle_dir_backup)||(wheel_angle_value!=wheel_angle_value_backup))
	{
		steering_angle_dir_backup = steering_angle_dir;
		wheel_angle_value_backup = wheel_angle_value;
		can_wheel_angle_value = steering_angle_value;
		arg[0] = (U8)(wheel_angle_value >> 8);
		arg[1] = (U8)wheel_angle_value;
		arg[2] = steering_angle_dir;
		M4Msg_Update(E_M4_SteerWheelDirection_U8, steering_angle_dir);
		M4Msg_Update(E_M4_SteerWheelAngle_Multiple1H_U16, wheel_angle_value);
		CanAppAvmSteeringAngleSmallChange(steering_angle_value,steering_angle_dir);
	    SocManager_SendMsg(HQ_CMD,TYPE_EVENT, RADIO_NOTIFY_STEERING_WHEEL_DATA, 3, &arg[0]);	  
	}
	
	if(bReqToSendSteerWheelAngleSignal)
	{
		can_wheel_angle_value = steering_angle_value;
		arg[0] = (U8)(wheel_angle_value >> 8);
	    arg[1] = (U8)wheel_angle_value;
	    arg[2] = steering_angle_dir;
		M4Msg_Update(E_M4_SteerWheelDirection_U8, steering_angle_dir);
		M4Msg_Update(E_M4_SteerWheelAngle_Multiple1H_U16, wheel_angle_value);
		CanAppAvmSteeringAngleSmallChange(steering_angle_value,steering_angle_dir);
	    SocManager_SendMsg(HQ_CMD,TYPE_EVENT, RADIO_NOTIFY_STEERING_WHEEL_DATA, 3, &arg[0]);
		bReqToSendSteerWheelAngleSignal = FALSE;
	}
}

void CAN_CarDoorStaus_rxhandler(void)
{
 
    U8 index;
	U8 ValidValue = 0;
	static U8 uRecvCanMsg[8];
	static U8 uVehicleDoorMsg_Backup[E_VEHICLE_DOOR_NUM];
    
    for(index= 0;index<E_VEHICLE_DOOR_NUM;index++)
    {  
		if(E_DRIVER_DOOR == index)
		{
			uRecvCanMsg[0] = can_receive_sig(DoorSt_FL);
		}
		else if(E_PSNG_DOOR == index)
		{
			uRecvCanMsg[1] = can_receive_sig(DoorSt_FR);
		}
		else if (E_RR_DOOR == index)
		{
			uRecvCanMsg[2] = can_receive_sig(DoorSt_RR);
		}
		else if (E_LR_DOOR == index)
		{
			uRecvCanMsg[3] = can_receive_sig(DoorSt_RL);
		}
		else if(E_TRUNK_DOOR == index)
		{
			uRecvCanMsg[4] = can_receive_sig(LuggageDoorSt);
		}
		else if (E_EngineHood == index)
		{
			uRecvCanMsg[5] = can_receive_sig(EngineHoodSt);
		}	
    }
	
    if(_memcmp(uRecvCanMsg, uVehicleDoorMsg_Backup,E_VEHICLE_DOOR_NUM))
    {
        _memcpy(uVehicleDoorMsg_Backup, uRecvCanMsg,E_VEHICLE_DOOR_NUM);
		SocManager_SendMsg(HQ_CMD,TYPE_EVENT, RADIO_NOTIFY_DOORS_INFO, E_VEHICLE_DOOR_NUM, uRecvCanMsg); 
    }

	if(bReqToSenddoortatus)
	{
		bReqToSenddoortatus = FALSE;
		_memcpy(uVehicleDoorMsg_Backup, uRecvCanMsg,E_VEHICLE_DOOR_NUM);		
		SocManager_SendMsg(HQ_CMD,TYPE_EVENT, RADIO_NOTIFY_DOORS_INFO, E_VEHICLE_DOOR_NUM, uRecvCanMsg); 
	}
}

void CAN_CarRearviewMirrorSt_rxhandler(void)
{
	static U8 arg[8] = {0};
	U8 left_mirror_st = 0;
	U8 right_mirror_st = 0;
	static U8 left_mirror_st_backup = 0;
	static U8 right_mirror_st_backup = 0;

	left_mirror_st = can_receive_sig(MirrorFoldSt_FL);
	right_mirror_st = can_receive_sig(MirrorFoldSt_FR);

	if((left_mirror_st != left_mirror_st_backup)||(right_mirror_st != right_mirror_st_backup))
	{
		left_mirror_st_backup = left_mirror_st;
		right_mirror_st_backup = right_mirror_st;
		arg[0] = left_mirror_st_backup;
		arg[1] = right_mirror_st_backup;
		SocManager_SendMsg(TX_HQ,TYPE_EVENT, RADIO_NOTIFY_REARVIEW_MIRROR_STATUS, 2, arg);
	}	
	
	if(bReqToSendRearviewMirrorSt)
	{
		bReqToSendRearviewMirrorSt = FALSE;
		arg[0] = left_mirror_st_backup;
		arg[1] = right_mirror_st_backup;
		SocManager_SendMsg(TX_HQ,TYPE_EVENT, RADIO_NOTIFY_REARVIEW_MIRROR_STATUS, 2, arg);
	}
}

void can_RCTASt_rxhander(void)
{
	static U8 arg[8] = {0};
	U8 RCTA_left_st = 0;
	U8 RCTA_right_st = 0;
	static U8 RCTA_left_st_bak = 0;
	static U8 RCTA_right_st_bak = 0;

	RCTA_left_st = can_receive_sig(WarningCmd_RCTA_left);
	RCTA_right_st = can_receive_sig(WarningCmd_RCTA_Right);

	if((RCTA_left_st != RCTA_left_st_bak)||(RCTA_right_st != RCTA_right_st_bak))
	{
		RCTA_left_st_bak = RCTA_left_st;
		RCTA_right_st_bak = RCTA_right_st;
		arg[0] = RCTA_left_st_bak;
		arg[1] = RCTA_right_st_bak;
		SocManager_SendMsg(TX_HQ,TYPE_EVENT, RADIO_NOTIFY_WARN_RCTA_STATUS, 2, arg);
	}	
	
	if(bReqToSendRCTASt)
	{
		bReqToSendRCTASt = FALSE;
		arg[0] = RCTA_left_st_bak;
		arg[1] = RCTA_right_st_bak;
		SocManager_SendMsg(TX_HQ,TYPE_EVENT, RADIO_NOTIFY_WARN_RCTA_STATUS, 2, arg);
	}
}

void can_DynamicPGSSt_rxhandler(void)
{
	U8 DynamicPGSSt;
	static U8 DynamicPGSSt_bak;

	DynamicPGSSt = can_receive_sig(DynamicPGSReq);

	if(DynamicPGSSt_bak != DynamicPGSSt)
	{
		DynamicPGSSt_bak = DynamicPGSSt;
		SocManager_SendMsg(TX_HQ,TYPE_EVENT, RADIO_NOTIFY_DYNAMICPGS_STATUS, 1, &DynamicPGSSt);
	}
	
	if(bReqToSendDynamicPGSSt)
	{
		bReqToSendDynamicPGSSt = FALSE;
		SocManager_SendMsg(TX_HQ,TYPE_EVENT, RADIO_NOTIFY_DYNAMICPGS_STATUS, 1, &DynamicPGSSt_bak);
	}	

}

void can_acckey_rxhandler(void)
{
	U8 ign;
	static BOOL ignmsg_accstatus=FALSE;
	static BOOL ignmsg_accstatus_backup=FALSE;
	static BOOL can_accon_flag=FALSE;
	static BOOL can_accon_flag_backup=FALSE;
	static U8 can_acc_status=0;
	
	CS_SIG_SyncReceive(SIG_ACCSTATUS, &ignmsg_accstatus);  //ACC and CAN
    if(ignmsg_accstatus_backup!=ignmsg_accstatus)
   	{
   		ignmsg_accstatus_backup = ignmsg_accstatus;
		if(ignmsg_accstatus)
	    {
			ign=2;
		}
		else
		{
			ign=0;
		}
		SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_IGN_KEY_STATUS,1,&ign);//440D
	}

	if(bReqToSendIGNstatus)
	{
		bReqToSendIGNstatus = FALSE;
		if(ignmsg_accstatus)
	    {
			ign=2;
		}
		else
		{
			ign=0;
		}
		SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_IGN_KEY_STATUS,1,&ign);//440D
	}
	
	can_acc_status = can_receive_sig(PowerMode);

	if(can_acc_status >= 0x04)
	{
		can_accon_flag = TRUE;
	}
	else
	{	
		can_accon_flag = FALSE;
	}

	if(can_accon_flag!=can_accon_flag_backup)
	{
		can_accon_flag_backup = can_accon_flag;
		
	}

	CS_SIG_SyncSend(SIG_ACC_CAN_IN_STATUS, &can_accon_flag);
}

void ApplLeverInfoRxSigTimeout(void)
{

}

void can_LeverInfo_rxhandler(void)
{
	static U8 rec_LeverInfo_status = 0;
	static U8 rec_LeverInfo_status_backup = 0;
	static U8 rec_LeverInfo_sig_backup = 0;
	static U8 LeverInfoCnt; 

	if(IlGetLeverInfoRxTimeout())
	{
		IlClrLeverInfoRxTimeout();
		rec_LeverInfo_status = 0; //time out send P level info
		rec_LeverInfo_sig_backup = 0;
		rec_LeverInfo_status_backup = 0;
		SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_GEAR_DISPLAY_STATUS,1,&rec_LeverInfo_status);
		return;
	}

	rec_LeverInfo_status = can_receive_sig(LeverInfo);

	if(rec_LeverInfo_sig_backup != rec_LeverInfo_status)
	{
		rec_LeverInfo_sig_backup = rec_LeverInfo_status;
		LeverInfoCnt = 0;
	}

	if(rec_LeverInfo_status_backup != rec_LeverInfo_status)
	{
		LeverInfoCnt++;
		if(LeverInfoCnt > LEVERINFO_DEBUNCE_TIME)
		{
			LeverInfoCnt = 0;
			rec_LeverInfo_status_backup = rec_LeverInfo_status;	
			can_ger_status = rec_LeverInfo_status_backup;
			M4Msg_Update(E_M4_GearStatus_U8, rec_LeverInfo_status_backup);	
			SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_GEAR_DISPLAY_STATUS,1,&rec_LeverInfo_status);
		}
	}
	else
	{
		LeverInfoCnt = 0;
	}
	
	if(bReqToSendLeverInfoSignal)
	{
		bReqToSendLeverInfoSignal = FALSE;
		can_ger_status = rec_LeverInfo_status_backup;	
		M4Msg_Update(E_M4_GearStatus_U8, rec_LeverInfo_status_backup);
		SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_GEAR_DISPLAY_STATUS,1,&rec_LeverInfo_status);
	}
}


void can_coordinate_rxhandler(void)
{
	U8 arg[10];
	static COORDINATE_DATA_DEF coordinate_data;
	static COORDINATE_DATA_DEF coordinate_data_backup;

	coordinate_data.x1_val = can_receive_sig(ScreenPressPosition_X1); 
    coordinate_data.y1_val = can_receive_sig(ScreenPressPosition_Y1); 
	coordinate_data.ScreenPressType1 = can_receive_sig(ScreenPressType1); 
	coordinate_data.x2_val = can_receive_sig(ScreenPressPosition_X2); 
	coordinate_data.y2_val = can_receive_sig(ScreenPressPosition_Y2); 
	coordinate_data.ScreenPressType2 = can_receive_sig(ScreenPressType2); 
	if((coordinate_data.x1_val != coordinate_data_backup.x1_val)||(coordinate_data.y1_val != coordinate_data_backup.y1_val)
	|| (coordinate_data.ScreenPressType1 != coordinate_data_backup.ScreenPressType1) || (coordinate_data.x2_val != coordinate_data_backup.x2_val)
	|| (coordinate_data.y2_val != coordinate_data_backup.y2_val) || (coordinate_data.ScreenPressType2 != coordinate_data_backup.ScreenPressType2)) //change
	{
		coordinate_data_backup.x1_val = coordinate_data.x1_val;
		coordinate_data_backup.y1_val = coordinate_data.y1_val;
		coordinate_data_backup.ScreenPressType1 = coordinate_data.ScreenPressType1; 
		coordinate_data_backup.x2_val = coordinate_data.x2_val; 
		coordinate_data_backup.y2_val = coordinate_data.y2_val; 
		coordinate_data_backup.ScreenPressType2 = coordinate_data.ScreenPressType2;
		arg[0]=(U8)coordinate_data.ScreenPressType1;
		arg[1]=(U8)(coordinate_data.x1_val>>8);
		arg[2]=(U8)coordinate_data.x1_val;
		arg[3]=(U8)(coordinate_data.y1_val>>8);
		arg[4]=(U8)coordinate_data.y1_val;
		arg[5]=(U8)coordinate_data.ScreenPressType2;
		arg[6]=(U8)(coordinate_data.x2_val>>8); 
		arg[7]=(U8)coordinate_data.x2_val;		
		arg[8]=(U8)(coordinate_data.y2_val>>8);	
		arg[9]=(U8)coordinate_data.y2_val;		 
		SocManager_SendMsg(LQ_CMD,TYPE_EVENT,RADIO_NOTIFY_COORDINATE_DATA,10,arg);
	}
}


void can_VehicleOdometer_rxhandler(void)
{
	U32 spd_cal;
	static U32 can_vehicleOdometer=0;

	/* The Odometer message missing: 0x02000000 */
	if(GetMessageTimeOutFlag(IC_1_MESSAGE))
	{
		can_vehicleOdometer = ODOMETER_MISSING_VALUE;
		Can_Signal_Snapshot_Data.Snapshot0101_Odometer = can_vehicleOdometer;
		return;
	}
	else
	{
		can_vehicleOdometer = can_receive_sig(OdometerValue);
	}

	/* Bus value range:0x00000000-0x01FFFFFE */
	if(can_vehicleOdometer>=ODOMETER_ERROR_VALUE)
	{
		can_vehicleOdometer = ODOMETER_ERROR_VALUE;
	}

	Can_Signal_Snapshot_Data.Snapshot0101_Odometer = can_vehicleOdometer;
}

void can_radar_distance_value_msg_rxhandler(void)
{
	U8 Index;
	static U8 radar_distance_value[8];
	static U8 radar_distance_value_backup[8];	
	
	if((PDC_ON == can_receive_sig(SysSt_PDC))&&(NoError == can_receive_sig(ErrorSt_PDC)))
	{
		if(PDC_ON == can_receive_sig(RadarSysSt_Front))
		{
			if(NoError == can_receive_sig(SensorErrorSt_FL)){
				radar_distance_value[0] = can_receive_sig(ObjectRange_FL);
			}else{
				radar_distance_value[0] = 0;
			}
			
			if(NoError == can_receive_sig(SensorErrorSt_FR)){
				radar_distance_value[1] = can_receive_sig(ObjectRange_FR);
			}else{
				radar_distance_value[1] = 0;
			}

			if(NoError == can_receive_sig(SensorErrorSt_FML)){
				radar_distance_value[6] = can_receive_sig(ObjectRange_FML);
			}else{
				radar_distance_value[6] = 0;
			}
			
			if(NoError == can_receive_sig(SensorErrorSt_FMR)){
				radar_distance_value[7] = can_receive_sig(ObjectRange_FMR);
			}else{
				radar_distance_value[7] = 0;
			}
		}	
		else
		{
			radar_distance_value[0] = 0;
			radar_distance_value[1] = 0;
			radar_distance_value[6] = 0;
			radar_distance_value[7] = 0;
		}

		if(PDC_ON == can_receive_sig(RadarSysSt_Rear))
		{
			if(NoError == can_receive_sig(SensorErrorSt_RL)){
				radar_distance_value[2] = can_receive_sig(ObjectRange_RL);
			}else{
				radar_distance_value[2] = 0;
			}
			
			if(NoError == can_receive_sig(SensorErrorSt_RR)){
				radar_distance_value[3] = can_receive_sig(ObjectRange_RR);
			}else{
				radar_distance_value[3] = 0;
			}

			if(NoError == can_receive_sig(SensorErrorSt_RML)){
				radar_distance_value[4] = can_receive_sig(ObjectRange_RML);
			}else{
				radar_distance_value[4] = 0;
			}
			
			if(NoError == can_receive_sig(SensorErrorSt_RMR)){
				radar_distance_value[5] = can_receive_sig(ObjectRange_RMR);
			}else{
				radar_distance_value[5] = 0;
			}
		}
		else
		{
			radar_distance_value[2] = 0;
			radar_distance_value[3] = 0;
			radar_distance_value[4] = 0;
			radar_distance_value[5] = 0;
		}

	}
	else
	{
		for(Index=0;Index<8;Index++)
			radar_distance_value[Index] = 0;
	}

	
	for(Index=0;Index<8;Index++)
	{
		if(radar_distance_value[Index] >= 0x07)	 // >=0x07:Invalid Value
		{															
			radar_distance_value[Index] = 0;
		}
	}
	
	for(Index=0;Index<8;Index++)
	{
		if(radar_distance_value[Index] != radar_distance_value_backup[Index])	
		{															
			radar_distance_value_backup[Index]=radar_distance_value[Index];
			SocManager_SendMsg(LQ_CMD,TYPE_EVENT,RADIO_NOTIFY_RADAR_SENSOR_DISTANCE,8,radar_distance_value);
		}
	}

	if(bReqToSendRadarDistance)
	{							
		bReqToSendRadarDistance = FALSE;
		SocManager_SendMsg(LQ_CMD,TYPE_EVENT,RADIO_NOTIFY_RADAR_SENSOR_DISTANCE,8,radar_distance_value);
	}
}

void can_PDCAndRadarSt_rxhander(void)
{
	U8 Index;
	static U8 PDCAndRadar_status[6];
	static U8 PDCAndRadar_status_backup[6];

	PDCAndRadar_status[0] = can_receive_sig(SysSt_PDC);
	PDCAndRadar_status[1] = can_receive_sig(ErrorSt_PDC);
	PDCAndRadar_status[2] = can_receive_sig(RadarSysSt_Front);
	PDCAndRadar_status[3] = can_receive_sig(RadarSysSt_Rear);
	PDCAndRadar_status[4] = can_receive_sig(RadarSysSt_FrontSide);
	PDCAndRadar_status[5] = can_receive_sig(RadarSysSt_RearSide);

	if((PDCAndRadar_status[0] != PDCAndRadar_status_backup[0]) || (PDCAndRadar_status[1] != PDCAndRadar_status_backup[1])
	 || (PDCAndRadar_status[2] != PDCAndRadar_status_backup[2]) || (PDCAndRadar_status[3] != PDCAndRadar_status_backup[3])
	 || (PDCAndRadar_status[4] != PDCAndRadar_status_backup[4]) || (PDCAndRadar_status[5] != PDCAndRadar_status_backup[5]))
	{
		for(Index = 0;Index < 6;Index++)
		{
			PDCAndRadar_status_backup[Index] = PDCAndRadar_status[Index];
		}
		SocManager_SendMsg(LQ_CMD,TYPE_EVENT,RADIO_NOTIFY_RADAR_AND_PDC_STATUS,6,PDCAndRadar_status_backup); //4416
	}

	if(bReqToSendPDCAndRadarSt)
	{							
		bReqToSendPDCAndRadarSt = FALSE;
		SocManager_SendMsg(LQ_CMD,TYPE_EVENT,RADIO_NOTIFY_RADAR_AND_PDC_STATUS,6,PDCAndRadar_status_backup); //4416
	}
}

void can_PDCSensorErrorSt_rxhander(void)
{
	U8 Index;
	static U8 radar_sensor_status[8];
	static U8 radar_sensor_status_backup[8];

	radar_sensor_status[0] = can_receive_sig(SensorErrorSt_FL);
	radar_sensor_status[1] = can_receive_sig(SensorErrorSt_FR);
	radar_sensor_status[2] = can_receive_sig(SensorErrorSt_RL);
	radar_sensor_status[3] = can_receive_sig(SensorErrorSt_RR);
	radar_sensor_status[4] = can_receive_sig(SensorErrorSt_RML);
	radar_sensor_status[5] = can_receive_sig(SensorErrorSt_RMR);
	radar_sensor_status[6] = can_receive_sig(SensorErrorSt_FML);
	radar_sensor_status[7] = can_receive_sig(SensorErrorSt_FMR);

	if((radar_sensor_status[0] != radar_sensor_status_backup[0]) || (radar_sensor_status[1] != radar_sensor_status_backup[1]) || (radar_sensor_status[2] != radar_sensor_status_backup[2])
	|| (radar_sensor_status[3] != radar_sensor_status_backup[3]) || (radar_sensor_status[4] != radar_sensor_status_backup[4]) || (radar_sensor_status[5] != radar_sensor_status_backup[5])
	|| (radar_sensor_status[6] != radar_sensor_status_backup[6]) || (radar_sensor_status[7] != radar_sensor_status_backup[7]))
	{
		for(Index = 0;Index < 8;Index++)
		{
			radar_sensor_status_backup[Index] = radar_sensor_status[Index];
		}
		SocManager_SendMsg(LQ_CMD,TYPE_EVENT,RADIO_NOTIFY_RADAR_SENSOR_ERROR_FLAG,8,radar_sensor_status_backup); //4416
	}

	if(bReqToSendPDCSensorErrorSt)
	{							
		bReqToSendPDCSensorErrorSt = FALSE;
		SocManager_SendMsg(LQ_CMD,TYPE_EVENT,RADIO_NOTIFY_RADAR_SENSOR_ERROR_FLAG,8,radar_sensor_status_backup); //4416
	}
}

void can_PDCSensorBlockageSt_rxhander(void)
{
	U8 Index;
	static U8 radar_Blockage_status[8];
	static U8 radar_Blockage_status_backup[8];

	radar_Blockage_status[0] = can_receive_sig(SensorBlockageSt_FL);
	radar_Blockage_status[1] = can_receive_sig(SensorBlockageSt_FR);
	radar_Blockage_status[2] = can_receive_sig(SensorBlockageSt_RL);
	radar_Blockage_status[3] = can_receive_sig(SensorBlockageSt_RR);
	radar_Blockage_status[4] = can_receive_sig(SensorBlockageSt_RML);
	radar_Blockage_status[5] = can_receive_sig(SensorBlockageSt_RMR);
	radar_Blockage_status[6] = can_receive_sig(SensorBlockageSt_FML);
	radar_Blockage_status[7] = can_receive_sig(SensorBlockageSt_FMR);

	if((radar_Blockage_status[0] != radar_Blockage_status_backup[0]) || (radar_Blockage_status[1] != radar_Blockage_status_backup[1]) || (radar_Blockage_status[2] != radar_Blockage_status_backup[2])
	|| (radar_Blockage_status[3] != radar_Blockage_status_backup[3]) || (radar_Blockage_status[4] != radar_Blockage_status_backup[4]) || (radar_Blockage_status[5] != radar_Blockage_status_backup[5])
	|| (radar_Blockage_status[6] != radar_Blockage_status_backup[6]) || (radar_Blockage_status[7] != radar_Blockage_status_backup[7]))
	{
		for(Index = 0;Index < 8;Index++)
		{
			radar_Blockage_status_backup[Index] = radar_Blockage_status[Index];
		}
		SocManager_SendMsg(LQ_CMD,TYPE_EVENT,RADIO_NOTIFY_RADAR_SENSOR_BLOCKAGE_FLAG,8,radar_Blockage_status_backup); // 4417
	}

	if(bReqToSendPDCSensorBlockageSt)
	{							
		bReqToSendPDCSensorBlockageSt = FALSE;
		SocManager_SendMsg(LQ_CMD,TYPE_EVENT,RADIO_NOTIFY_RADAR_SENSOR_BLOCKAGE_FLAG,8,radar_Blockage_status_backup);
	}
}

void can_AVM_LED_Control(void)
{
	U8 bAVMTurnOnFlag = 0;
	U8 bLightTurnOnFlag = 0;
	//U16 SystemVol = 0;  
	BOOL NaviPowerSta = FALSE;  

	CS_SIG_SyncReceive(SIG_AVM_TURNON_FLAG, &bAVMTurnOnFlag);
	//CS_SIG_SyncReceive(SIG_VOLTAGEFAIL_STATUS, &SystemVol);
	CS_SIG_SyncReceive(SIG_B_SOC_POWER_ON, &NaviPowerSta);

	/*
	if((SystemVol < V_NORMAL) && (bAVMTurnOnFlag == 1))   
	{
		bAVMTurnOnFlag = 0;
		CS_SIG_SyncSend(SIG_AVM_TURNON_FLAG, &bAVMTurnOnFlag);
	}
	*/
	
	if((NaviPowerSta == FALSE ) && (bAVMTurnOnFlag == 1))   
	{
		bAVMTurnOnFlag = 0;
//		can_send_sig(AVSWorkingMode,SK_EXIT);
		CS_SIG_SyncSend(SIG_AVM_TURNON_FLAG, &bAVMTurnOnFlag);
	}
	
	if(bAccOnSelfCheckEnd)
	{
		if(bAVMTurnOnFlag)	//0x4410
		{
			AVMON_BRIGHT();
		}
		else
		{
			AVMOFF_BRIGHT();
		}
	}
}

void can_AVM_ViewModeControl_rxhandler()
{
	static U8 arg[8] = {0};
	static U8 can_view_req=0;
	static U8 can_view_req_backup=0;	

	can_view_req = can_receive_sig(AVSViewModeReq);

	if(can_view_req >= CAN_RESERVED_VIEW)
		return;

	if(can_view_req!=can_view_req_backup)
	{
		can_view_req_backup = can_view_req;
		arg[0] = can_view_req_backup;
		SocManager_SendMsg(TX_HQ,TYPE_EVENT, RADIO_NOTIFY_VIEW_MODE_ANGLE, 1, arg);
	}	
	
	if(bReqToSendViewModeReqSignal)
	{
		bReqToSendViewModeReqSignal = FALSE;
		arg[0] = can_view_req_backup;
		SocManager_SendMsg(TX_HQ,TYPE_EVENT, RADIO_NOTIFY_VIEW_MODE_ANGLE, 1, arg);
	}
}

void can_FactoryModeReq_rxhandler()
{
	static U8 can_calibration_req=0;
	static U8 can_calibration_backup=0;	
	static U8 arg[3];
	
	can_calibration_req = can_receive_sig(AVSViewModeReq);

	if(can_calibration_req != can_calibration_backup)
	{
		can_calibration_backup = can_calibration_req;

		if(can_calibration_req == CAN_FACTROY_MODE)
		{
			arg[0] = CAN_SOFTKEY_TYPE;
			arg[1] = CAN_CALIBRATION_TYPE;
			arg[2] = 0x01;
			SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_KEY_STATUS,3,arg);
		}
	}
}


void can_SetLanguage_rxhandler()
{
	static U8 uSetLanguage = 0;
	static U8 uSetLanguage_backup = 0;
	U8 uCanRecLanguage = 0;

	switch(can_receive_sig(LanguageSet))
	{
		case Inactive: break;
		case Can_Simplified_Chinese: uSetLanguage = SPI_Chinese; break;
		case Can_Traditional_Chinese: break;
		case Can_English: uSetLanguage = SPI_English; break;
		case Can_French: break;
		case Can_Arabic: break;
		case Can_Russian: break;
		default: break;
	}
	
	if(uSetLanguage!= uSetLanguage_backup)
	{
		uSetLanguage_backup = uSetLanguage;			
		SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_LANGIAGE_SET,1,&uSetLanguage); //442A
	}
	
	if(bReqToSendLanguageSetReqSignal)
	{
		bReqToSendLanguageSetReqSignal = FALSE;
		SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_LANGIAGE_SET,1,&uSetLanguage_backup); //442A
	}	
}

void can_turnlamp_rxhandler(void)
{
	static U8 can_rx_turnlamp_status = CAN_TURNLAMP_MAX_DATA;
	static U8 uRightTurnLamp = 0;
	static U8 uHazardTurnLamp = 0;
	static U8 uLeftTurnLamp = 0;
	static U8 turnLampStatus_backup = 0;
    static U8 HazardTurnLampStatus_backup = 0;
	static U8 can_turnlamp_count =0;

	uRightTurnLamp = can_receive_sig(TurningSt_right);
	uLeftTurnLamp = can_receive_sig(TurningSt_Left); 
	uHazardTurnLamp = can_receive_sig(HazardWarningSt); 

    if((!uRightTurnLamp)&&(uLeftTurnLamp))
	{
	   can_rx_turnlamp_status = CAN_TURNLAMP_LEFT;
	   can_turnlamp_count = 0;
	}
    else if((uRightTurnLamp)&&(!uLeftTurnLamp))
	{
	   can_rx_turnlamp_status = CAN_TURNLAMP_RIGHT;
	   can_turnlamp_count = 0;
	}
	else
	{
	    can_turnlamp_count++;
        if(27 == can_turnlamp_count)
        {
            can_rx_turnlamp_status = CAN_TURNLAM_OFF;
            can_turnlamp_count = 0;
        }
	}

	if((can_rx_turnlamp_status<CAN_TURNLAMP_MAX_DATA)&&(can_rx_turnlamp_status != turnLampStatus_backup))
	{
		turnLampStatus_backup = can_rx_turnlamp_status;
		SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_TURNING_SIGNAL,1,&can_rx_turnlamp_status);
	}
	
	if(uHazardTurnLamp != HazardTurnLampStatus_backup)
	{
	   HazardTurnLampStatus_backup = uHazardTurnLamp;
	   M4Msg_Update(E_M4_HAZARD_STATUS_U8,HazardTurnLampStatus_backup);
	   SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_HAZARD_TURNING_SIGNAL,1,&uHazardTurnLamp);
	}

	if(bReqToSendTurnSignal)
	{
		bReqToSendTurnSignal = FALSE;
		if(can_rx_turnlamp_status < CAN_TURNLAMP_MAX_DATA)
		{
			SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_TURNING_SIGNAL,1,&can_rx_turnlamp_status);
		}
		 SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_HAZARD_TURNING_SIGNAL,1,&uHazardTurnLamp);
	}
}

void can_avm_act_req_rxhandler(void)
{
	can_AVS_switch_rxhandler();
	can_avm_pdcautoon_req_rxhandler();
	can_avm_hu_req_exit_rxhandler();
	can_avm_enter_exit_speech_rxhandler();
}

void can_AVS_switch_rxhandler(void)
{
	U8 AVS_switch_Sta = 0;
	static BOOL switch_pending_flag = FALSE;
	U8 arg[3];

	AVS_switch_Sta = can_receive_sig(MCP_AVSandFRadarSwitch); 

	if(AVS_switch_Sta)
	{
		if(!switch_pending_flag)
		{
			switch_pending_flag = TRUE;
			arg[0] = CAN_HARDKEY_TYPE;              
			arg[1] = 0x0;
			arg[2] = 0x0;
			SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_KEY_STATUS,3,arg);
		}
	}
	else
	{
		switch_pending_flag = FALSE;
	}
}

void can_avm_pdcautoon_req_rxhandler(void)
{
	U8 PdcAutoOn_switchAVS_Sta = 0;
	U8 arg[3];
	static U8 PdcAutoOn_switchAVS_Sta_bak = 0;
	PdcAutoOn_switchAVS_Sta = can_receive_sig(SwitchScreenRequest_PDC);
	if(PdcAutoOn_switchAVS_Sta != PdcAutoOn_switchAVS_Sta_bak)
	{
		PdcAutoOn_switchAVS_Sta_bak = PdcAutoOn_switchAVS_Sta;
		arg[0] = CAN_SOFTKEY_TYPE;
		arg[1] = AVM_ENTER_EXIT_SWITCH;
		arg[2] = PdcAutoOn_switchAVS_Sta;
		SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_KEY_STATUS,3,arg);
	}
}

void can_avm_enter_exit_speech_rxhandler(void)
{
	U8 arg[3];
	static U8 can_speech_req=0;
	static U8 can_speech_req_backup=0;	
	
	can_speech_req = can_receive_sig(HU_SpeedReq_AVS); 
	
	if(can_speech_req == 0x01)  //AVM Speech off      
	{
		can_speech_req = AVM_EXIT_REQUEST;
	}
	else if(can_speech_req == 0x02)  //AVM Speech on
	{
		can_speech_req = AVM_ENTER_REQUEST; 
	}
	
	if(can_speech_req!=can_speech_req_backup)
	{
		can_speech_req_backup = can_speech_req;

		if(can_speech_req == AVM_EXIT_REQUEST)
		{
			AVM_Speech_Req = AVM_EXIT_REQUEST;
		}
		else if(can_speech_req == AVM_ENTER_REQUEST)
		{
			AVM_Speech_Req = AVM_ENTER_REQUEST;
		}
		
		arg[0] = CAN_SOFTKEY_TYPE;
		arg[1] = AVM_ENTER_EXIT_SWITCH;
		arg[2] = can_speech_req;
		SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_KEY_STATUS,3,arg);
	}
	
 	if(bReqToSendSpeechReqSignal)
	{
		bReqToSendSpeechReqSignal = FALSE;
		arg[0] = CAN_SOFTKEY_TYPE;
		arg[1] = AVM_ENTER_EXIT_SWITCH;
		arg[2] = can_speech_req;
		SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_KEY_STATUS,3,arg);
	}	
}

void can_avm_hu_req_exit_rxhandler(void)
{
	U8 arg[3];
	static U8 can_softkey_req=0;
	static U8 can_softkey_req_backup=0;
	can_softkey_req = can_receive_sig(AVSFunctionExitReq);        
	
	if(can_softkey_req!=can_softkey_req_backup)
	{
		can_softkey_req_backup = can_softkey_req;
		if(can_softkey_req)
		{
			arg[0] = CAN_SOFTKEY_TYPE;
			arg[1] = AVM_ENTER_EXIT_SWITCH;
			arg[2] = 0x02;//AVM Exit Request
			SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_KEY_STATUS,3,arg);
		}
	}
}

void can_BlindSpotFilledReq_rxhandler(void)
{
	U8 uBlindSpotFilled = 0;
	static U8 uBlindSpotFilled_backup = 0;
	static BOOL uBlindSpotFilledFlag = FALSE;

	uBlindSpotFilled = can_receive_sig(HU_BlindSpotFilledFunctionReq);
	if(uBlindSpotFilled && (uBlindSpotFilled<3))
	{
		if(!uBlindSpotFilledFlag)
		{
			uBlindSpotFilledFlag = TRUE;
			if(uBlindSpotFilled_backup != 2)
			{
				uBlindSpotFilled_backup = 2;
				SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_J6_BLINDSPOTFILLED_REQ,1,&uBlindSpotFilled_backup); //4445
			}
			else
			{
				uBlindSpotFilled_backup = 1;
				SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_J6_BLINDSPOTFILLED_REQ,1,&uBlindSpotFilled_backup); //4445
			}
		}
	}
	else
	{
		uBlindSpotFilledFlag = FALSE;
	}
	
	if(bReqToSendBlindSpotFilled)
	{
		bReqToSendBlindSpotFilled = FALSE;
		SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_J6_BLINDSPOTFILLED_REQ,1,&uBlindSpotFilled_backup); //4445
	}
}

void can_AVSTurnFollowUpFunctionReq_rxhander(void)
{
	U8 uTurnFollowUp = 0;
	static U8 uTurnFollowUp_bak = 0;
	static BOOL uTurnFollowUpFlag = FALSE;

	uTurnFollowUp = can_receive_sig(AVSTurnLightFollowupFunctionReq);
	if(uTurnFollowUp&&(uTurnFollowUp<3))
	{
		if(!uTurnFollowUpFlag)
		{
			uTurnFollowUpFlag = TRUE;
			if(uTurnFollowUp_bak != 2)
			{
				uTurnFollowUp_bak = 2;//on
				SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_J6_TurnFollowUp_REQ,1,&uTurnFollowUp_bak); //4447
			}			
			else
			{
				uTurnFollowUp_bak = 1;//off
				SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_J6_TurnFollowUp_REQ,1,&uTurnFollowUp_bak); //4447
			}
		}
	}
	else
	{
		uTurnFollowUpFlag = FALSE;
	}
	
	if(bReqToSendTrunFollowUp)
	{
		bReqToSendTrunFollowUp = FALSE;
		SocManager_SendMsg(HQ_CMD,TYPE_EVENT,RADIO_NOTIFY_J6_TurnFollowUp_REQ,1,&uTurnFollowUp_bak); //4447
	}
}

void can_OTAMode_rxhandler(void)
{
	U8 mode = 0;
	static U8 mode_bk = 0;

	mode = can_receive_sig(GW_OTAMode);

	if(mode != mode_bk)
	{
		mode_bk = mode;
		GW_OTAMode_fun = mode;
	}
}

void CanApp_ReportDeviceDtc(U8 camerafault,U8 ledfault)
{
}

void CanApp_ReportDeviceDtcToCpu(U16 fault)
{        
	static U8 uDeviceFault[2] = {0};
    uDeviceFault[0] = fault>>8;
    uDeviceFault[1] = fault&0xff;
    SocManager_SendMsg(TX_HQ,TYPE_EVENT, RADIO_NOTIFY_ALERT_INFO, 2, uDeviceFault);      
}

void can_AVSErrorSt_txhandler(void)
{
	 static U8 Dtc_AVM_Error_Sta = 0;
	 static U8 Dtc_AVM_Error_Sta_Backup = 0;
	 Dtc_AVM_Error_Sta = dtc_status_record[DTC_AVM_SYSTEM_ERROR].dtc_status.status_bits.testFailed;
	 if(Dtc_AVM_Error_Sta != Dtc_AVM_Error_Sta_Backup)
	 {
	 	Dtc_AVM_Error_Sta_Backup = Dtc_AVM_Error_Sta;
		if(Dtc_AVM_Error_Sta)
		{
			can_send_sig(AVSErrorSt,0x01);
		}
		else
		{
			can_send_sig(AVSErrorSt,0x00);
		}
	 }
}

void can_CameraErrorSt_txhandler(void)
{
	U8 Index;
	static U8 camera_error_st[4];
	static U8 camera_error_st_backup[4];

	if((dtc_status_record[DTC_FRONT_CAMERA_OPEN_CIRCUIT].dtc_status.status_bits.testFailed)||
		(dtc_status_record[DTC_FRONT_CAMERA_SHORT_GND].dtc_status.status_bits.testFailed)||
		(dtc_status_record[DTC_FRONT_CAMERA_SHORT_BAT].dtc_status.status_bits.testFailed))
	{
		camera_error_st[FRONT_CAMERA_INDEX] = TRUE;
	}
	else
	{
		camera_error_st[FRONT_CAMERA_INDEX] = FALSE;
	}

	if((dtc_status_record[DTC_LEFT_CAMERA_OPEN_CIRCUIT].dtc_status.status_bits.testFailed)||
		(dtc_status_record[DTC_LEFT_CAMERA_SHORT_GND].dtc_status.status_bits.testFailed)||
		(dtc_status_record[DTC_LEFT_CAMERA_SHORT_BAT].dtc_status.status_bits.testFailed))
	{
		camera_error_st[LEFT_CAMERA_INDEX] = TRUE;
	}
	else
	{
		camera_error_st[LEFT_CAMERA_INDEX] = FALSE;
	}

	if((dtc_status_record[DTC_BACK_CAMERA_OPEN_CIRCUIT].dtc_status.status_bits.testFailed)||
		(dtc_status_record[DTC_BACK_CAMERA_SHORT_GND].dtc_status.status_bits.testFailed)||
		(dtc_status_record[DTC_BACK_CAMERA_SHORT_BAT].dtc_status.status_bits.testFailed))
	{
		camera_error_st[REAR_CAMERA_INDEX] = TRUE;
	}
	else
	{
		camera_error_st[REAR_CAMERA_INDEX] = FALSE;
	}

	if((dtc_status_record[DTC_RIGHT_CAMERA_OPEN_CIRCUIT].dtc_status.status_bits.testFailed)||
		(dtc_status_record[DTC_RIGHT_CAMERA_SHORT_GND].dtc_status.status_bits.testFailed)||
		(dtc_status_record[DTC_RIGHT_CAMERA_SHORT_BAT].dtc_status.status_bits.testFailed))
	{
		camera_error_st[RIGHT_CAMERA_INDEX] = TRUE;
	}
	else
	{
		camera_error_st[RIGHT_CAMERA_INDEX] = FALSE;
	}	
	
	for(Index = 0;Index < CAMERA_INDEX_MAX;Index++)
	{
		if(camera_error_st[Index] != camera_error_st_backup[Index])	
		{															
			camera_error_st_backup[Index] = camera_error_st[Index];

			if(camera_error_st[Index])
			{
				if(Index == FRONT_CAMERA_INDEX) can_send_sig(AVSCameraErrorSt_Front,0x01);
				if(Index == LEFT_CAMERA_INDEX)  can_send_sig(AVSCameraErrorSt_Left, 0x01);	
				if(Index == REAR_CAMERA_INDEX)  can_send_sig(AVSCameraErrorSt_Rear, 0x01);
				if(Index == RIGHT_CAMERA_INDEX) can_send_sig(AVSCameraErrorSt_Right,0x01);
			}
			else
			{	
				if(Index == FRONT_CAMERA_INDEX) can_send_sig(AVSCameraErrorSt_Front,0x00);
				if(Index == LEFT_CAMERA_INDEX) can_send_sig(AVSCameraErrorSt_Left, 0x00);	
				if(Index == REAR_CAMERA_INDEX) can_send_sig(AVSCameraErrorSt_Rear, 0x00);
				if(Index == RIGHT_CAMERA_INDEX) can_send_sig(AVSCameraErrorSt_Right,0x00);				
			}
		}
	}
}

void can_AVSStatus_txhandler(void)
{
	static U8 can_AVM_Sta = 0;
	static U8 can_AVM_Resp_Sta = 0;
	static U8 can_AVM_Sta_Backup = 0;
	can_AVM_Resp_Sta = can_receive_sig(SwitchScreenResponseAVS);
	
	switch(can_AVM_Resp_Sta)
	{
		case AVS_ENTER_RESP:
			can_AVM_Sta = 1;
		break;	
		case AVS_EXIT_RESP:
			can_AVM_Sta = 0;
		break;
		default:
		break;
	}
		
	if(can_AVM_Sta != can_AVM_Sta_Backup)
	{
	   can_AVM_Sta_Backup = can_AVM_Sta;
	   if(can_AVM_Sta)
	   {
		   can_send_sig(AVSSt,0x01);
	   }
	   else
	   {
		   can_send_sig(AVSSt,0x00);
	   }
	}
}


void CanApp_recvnavimsg_handler(U16 commandid, U8* data)
{  
	U8 tempValue;
	U8 AVM_TurnOn_flag = 0;
    switch (commandid)
    {
        case CPU_NOTIFY_M3_AVM_DISPLAY_STATUS : //4410
        	switch(data[0])
    		{	
    			case AVM_SOFTKEY_RESP:
					if (data[1]==0)
					{
						can_send_sig(AVSSt,SK_OPEN_AVM);
						AVM_TurnOn_flag = TRUE;
						CS_SIG_SyncSend(SIG_AVM_TURNON_FLAG, &AVM_TurnOn_flag);
						if(AVM_Speech_Req == AVM_ENTER_REQUEST)
						{
							AVM_Speech_Req = 0;
							can_send_sig(AVS_SpeechControlFeedback,0x03); //On Success
						}
					}
					else if(data[1]==1)
					{
						can_send_sig(AVSSt,SK_EXIT);
						AVM_TurnOn_flag = FALSE;
						CS_SIG_SyncSend(SIG_AVM_TURNON_FLAG, &AVM_TurnOn_flag);
						if(AVM_Speech_Req == AVM_EXIT_REQUEST)
						{
							AVM_Speech_Req = 0;
							can_send_sig(AVS_SpeechControlFeedback,0x01); //Off Success
						}
					}
					break;	
				case AVM_FACTORY_MODE:
					if (data[1]==1)
					{
						//can_send_sig(AVSWorkingMode,SK_UPDATE_AVM); 
					}
					break;	
				default:
					break;
    		}
        	break;

		case CPU_NOTIFY_M3_AVM_SETTING_RESULT://4411
			uAVSCarModelColor = data[0];

			if(data[1] == 0x00)  //Chinsese
			{
				can_send_sig(LanguageTypeSt_AVS,0x00); 
			}else if(data[1] == 0x01){ //English
				can_send_sig(LanguageTypeSt_AVS,0x02); 
			}
		
			if(data[2] == 0x01)
			{
				can_send_sig(DybanicPGSSt_AVS,0x00); 
			}else if(data[2] == 0x04){
				can_send_sig(DybanicPGSSt_AVS,0x01); 
			}
		break;	

		case CPU_NOTIFY_M3_AVM_DISPLAY_VIEWSTSRSP : 
			uAVSViewMode = data[0];
			can_send_sig(AVSViewMode,data[0]);
		
        	break;   

        case CPU_NOTIFY_M3_AVM_SYSTEM_STATUS://4412  
        	break;

        case CPU_NOTIFY_M3_LDW_SETTING_RESULT://4413
//			CanSig_CANSendValue(TX_SIG_SET_ID_AVM_LanedepartureSt_2U,(U8*)&data[0],1);
//			can_send_sig(AVM_LanedepartureSt_2U,data[0]);
        	break;
        
        case CPU_NOTIFY_M3_LDW_STATUS://4414
//			CanSig_CANSendValue(TX_SIG_SET_ID_AVM_LandpartSt_3U,(U8*)&data[0],1);
//        	can_send_sig(AVM_LandpartSt_3U,data[0]);
        	break;

		case CPU_NOTIFY_M3_CALIBRATION_SUCCESS://4433
			EED_LockDataBlock(EED_nEOLConfig);
			EED_Calibration = data[0];
			EED_u8SocCalibrationDoneFlag = data[0];
			EED_UnlockAndSavDataBlock(EED_nEOLConfig);	
			uAVSCalibrationSta= data[0];
			can_send_sig(AVS_CalibrationSt,uAVSCalibrationSta);
			/* Clear all DTC after successful calibration */
			if(EED_Calibration == 1)
			{
				ClearDiagDtcData();
			}
			break;
		
		case J6_SEND_RESPONSE_OF_BLINDSPOTFILLED_STATUS://4443
			if(data[0] == 0)
			{
				can_send_sig(BlindSpotFilledFunctionInd,BlindFilledInd_off);
			}
			if(data[0] == 1)
			{
				can_send_sig(BlindSpotFilledFunctionInd,BlindFilledInd_on);
			}
			break;

		case J6_SEND_RESPONSE_OF_TurnFollowUp_STATUS://4446
			if(data[0] == 0)
			{
				can_send_sig(AVSTurnLightFollowupFunctionSt,TurnFollowUpFunctionInd_off);
			}
			if(data[0] == 1)
			{
				can_send_sig(AVSTurnLightFollowupFunctionSt,TurnFollowUpFunctionInd_on);
			}
			break;

        case SOC_REQ_RESEND_IMPORTANT_MESSAGE://4202
			bReqToSendSteerWheelAngleSignal = TRUE;
			bReqToSendCoordinateResolution = TRUE;
			bReqToSendLeverInfoSignal = TRUE;
			bReqToSendIGNstatus = TRUE;
			bReqToSendViewModeReqSignal = TRUE;
			bReqToSendLanguageSetReqSignal = TRUE;
			bReqToSendTurnSignal = TRUE;
			bReqToSendSpeechReqSignal = TRUE;
			bReqToSendSpeedSignal = TRUE;
			bReqToSenddoortatus = TRUE;
			bReqToSendRadarDistance = TRUE;
			SVP_SUCCEED_FLAG = TRUE;
			bJ6_start_complete = TRUE;
			bReqToSendRearviewMirrorSt = TRUE;
			bReqReportcamerafault = TRUE;
			bReqToSendBlindSpotFilled = TRUE;
			bReqToSendTrunFollowUp = TRUE;
			bReqToSendRCTASt = TRUE;
			bReqToSendPDCSensorErrorSt = TRUE;
			bReqToSendPDCSensorBlockageSt = TRUE;
			bReqToSendDynamicPGSSt = TRUE;
        	break;
		case SOC_REQ_SOFT_VERSION: //4201
			bJ6RequestM3Version = TRUE;
        	break;

		case CPU_NOTIFY_M3_OFFLINE_CALIBRATION_RESULT://44F3
			if(data[0] == 0)//enter calibration mode succefully
			{
				SCalibrationResult = 0x01;
			}
			else if(data[0] == 0x01)
			{
				SCalibrationResult = 0x00;
			}
			break;

		case APP_Send_EOL_View_Result_To_MCU: //44C8
			if(data[0] == 0)//enter calibration mode succefully
			{
				SEnterEOLViewResult = 0x00;
			}
			else if(data[0] == 0x01)
			{
				SEnterEOLViewResult = 0x01;
			}
			break;

		case NAVI_SEND_CAMERA_BLOCKAGE_STATUS: //4418
			can_send_sig(AVSCameraBlockageSt_Front,data[0]);
			can_send_sig(AVSCameraBlockageSt_Rear,data[1]);
			can_send_sig(AVSCameraBlockageSt_Left,data[2]);
			can_send_sig(AVSCameraBlockageSt_Right,data[3]);
			break;

        default:
			break;
    }
}

void CanAppGetSpeed(U8* data)
{
   data[0] = can_vehiclespeed_backup >>8 ;
   data[1] = can_vehiclespeed_backup &0xFF; 	 
}

void CanAppGetEngStatus(U8* data)
{
  	 data[0]=can_receive_sig(PowerMode);
}



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
*  0.2 Jan 24,2017 ZhangJie     Fix Coverity warning.
*----------------------------------------------------------------------
*  0.3 Feb 07,2017 ZhangJie     Define GPIO as micro.
*----------------------------------------------------------------------
*  0.4 Feb 20,2017 ZhangJie     Remove can protocol code to CANmanager.c.
*----------------------------------------------------------------------
*  0.5 Apr 01,2017 Pei Jingli    Fix headfile included.
*=====================================================================*/
#ifndef   _CANAPP_H
#define   _CANAPP_H
//#include "CanMgr.h"
#define CANTXSIG_PASS_1
#include "Cansig_def.h"
#define CANRXSIG_PASS_1
#include "Cansig_def.h"
#include "Pwmd_if.h"

extern void can_sig_init(void);
extern void SocCan_20ms_Entry(void);

#define AVM_LED_OFF()    PWMD_SetDuty(22,E_PWMD_RATIO100,0);//GPIO_SetVal(GPIO_PORT_8, GPIO_PIN_2, FALSE)
#define AVM_LED_ON()     PWMD_SetDuty(22,E_PWMD_RATIO100,95);//GPIO_SetVal(GPIO_PORT_8, GPIO_PIN_2, TRUE)

//can signal send/receive interface
#define can_send_sig(x,c)     IlPutTx##x(c)
#define can_receive_sig(x)    IlGetRx##x()

#define STEERING_ANGLE_FAC 58
#define STEERING_ANGLE_FAC_VALUE 1000
#define MAX_STEERING_ANGLE 46 
#define STEERING_ANGLE_FACTOR 16
#define AVM_SWITCH_ON  1
#define AVM_SWITCH_OFF 0

/* vehiclespeed define */
#define SPEED_ERROR_VALUE    0x7FFF
#define SPEED_MISSING_VALUE  0x8000

/* steering angle define */
#define ANGLE_DATA_MAX 720 
#define CAN_ANGLE_DATA_RANGE_HIGH 780
#define ERROR_VALUE_RANGE 0x7FFF

/* LeverInfo define */
#define LEVERINFO_DEBUNCE_TIME 25

/* VehicleOdometer define */
#define ODOMETER_ERROR_VALUE    0x01FFFFFF
#define ODOMETER_MISSING_VALUE  0x02000000

/* Turnlamp define */
#define TURN_SWITCH_FILTER_TIME  3
#define TURN_SWITCH_FILTER_TIME_END  5
#define ROD_BACK_FILTER_TIME_END  6

/* LED Control define */
#define AVMOFF_BRIGHT()    PWMD_SetDuty(22,E_PWMD_RATIO100,0)//GPIO_SetVal(GPIO_PORT_8, GPIO_PIN_2, FALSE)
#define AVMON_BRIGHT()     PWMD_SetDuty(22,E_PWMD_RATIO100,95)//GPIO_SetVal(GPIO_PORT_8, GPIO_PIN_2, TRUE)

enum
{
    E_DRIVER_DOOR,
    E_PSNG_DOOR,
 	E_RR_DOOR,
 	E_LR_DOOR,
 	E_TRUNK_DOOR = 0x04,
	E_EngineHood,
    E_VEHICLE_DOOR_NUM,
};

enum 
{
 NoError,
 Error,
};

enum 
{
 PDC_OFF,
 PDC_ON,
};

 
enum AVS_STA_TYPE
{
	SK_EXIT=0x00,
	SK_OPEN_AVM=0x01,
	//SK_ENTER_CALIBRATION=3,
	//SK_UPDATE_AVM=4,
};

enum CAN_AVM_VIEW_MODE_TYPE
{
	CAN_ALL_TOP_VIEW = 0x01,
	CAN_TOP_VIEW_AND_FRONT_VIEW = 0x02,
	CAN_TOP_VIEW_AND_REAR_VIEW = 0x03,
	CAN_TOP_VIEW_AND_LEFT_VIEW = 0x04,
	CAN_TOP_VIEW_AND_RIGHT_VIEW = 0x05,
	CAN_FRONT_WIDE_VIEW = 0x06,
	CAN_REAR_WIDE_VIEW = 0x07,
	CAN_FRONT_RIM_VIEW = 0x09,
	CAN_REAR_RIM_VIEW = 0x0A,
	CAN_SCREEN_DRAGGED_3D_VIEW = 0x0B,
	CAN_RESERVED_VIEW = 0x0C,
	CAN_FACTROY_MODE = 0x0D,
	CAN_CALIBRATION_MODE = 0x0E,
};

enum CAN_AVS_RESP_STA
{
	AVS_ENTER_RESP = 0x01,
	AVS_EXIT_RESP = 0x02,
};

enum CAMERA_INDEX
{
	FRONT_CAMERA_INDEX,
	REAR_CAMERA_INDEX,  
	LEFT_CAMERA_INDEX, 
	RIGHT_CAMERA_INDEX, 
	CAMERA_INDEX_MAX,
};

enum CAN_DYNAMIC_PGL_TYPE
{
	F_OFF_AND_R_OFF = 0x01,
	F_OFF_AND_R_ON = 0x02,
	F_ON_AND_R_OFF = 0x03,
	F_ON_AND_R_ON = 0x04,	
};

typedef enum STEERING_DIRECT_TAG
{
    STEERING_DIRECT_LEFT,
    STEERING_DIRECT_RIGHT,
} STEERING_DIRECT;

enum  steering_wheel_direction_Info {
	steeringWheelDir_center = 0,  
	steeringWheelDir_left,		    
	steeringWheelDir_right,		   
};

typedef enum CAN_TURNLAMP_STSTUS_DATA_TAG
{
    CAN_TURNLAM_OFF,
    CAN_TURNLAMP_LEFT,
    CAN_TURNLAMP_RIGHT,
    CAN_TURNLAMP_HAZRD,
    CAN_TURNLAMP_MAX_DATA,
} CAN_TURNLAMP_STSTUS_DATA;

typedef enum CAN_SHIFTER_LEVER_DATA_TAG
{
    CAN_GEAR_SWITCH_OFF,
    CAN_GEAR_SWITCH_ON,  
    CAN_GEAR_SWITCH_MAXDATA,
} CAN_GEAR_SWITCH_DATA;

typedef enum   // change
{
	NOT_TOUCH = 0x00,
	TOUCH_PEN_DOWN,
	TOUCH_PEN_UP,
	TOUCH_PEN_MOVE,   // c095 add
} SCREEN_PRESS_TOUCH_TYPE;
	
typedef struct
{
	U16 x1_val;
	U16 y1_val;
	U16 x2_val; // add
	U16 y2_val; // add
	SCREEN_PRESS_TOUCH_TYPE ScreenPressType1; //add
	SCREEN_PRESS_TOUCH_TYPE ScreenPressType2; //add
}COORDINATE_DATA_DEF;    

enum CAN_KEY_TYPE
{
	CAN_HARDKEY_TYPE=0x00,
    CAN_SOFTKEY_TYPE=0x01,
    CAN_CALIBRATION_TYPE=0x03,
};

enum CAN_SOFTKEY_TYPE_S
{
	AVM_ENTER_EXIT_SWITCH,
	AVM_VIEW_ANGLE_SWITCH,
	AVM_VIEW_MODE_SWITCH,
	CALIBRATION_REQ,
	DVR_HOME_REQ,
	DVR_SDFORMAT_REQ,
	DVR_RESTORE_FACTORY_REQ,
};

enum AVM_DISPLAY_REQ
{
	AVM_CONTROL_REQ,
	AVM_SOFTKEY_RESP,
	AVM_FACTORY_MODE,
	AVM_CarColorSetting,
	AVM_TrajSetting,

};
enum AVM_CTRL_RESP
{
	AVM_NO_REQ,
	AVM_ENT_HK,
	AVM_ENT_RGEAR,
	AVM_EXIT_HK,
	DVR_EXIT_SPEED,
};

enum AVM_ONOFF_REQ
{
	NO_REQUEST,
	AVM_ENTER_REQUEST,
	AVM_EXIT_REQUEST,
};
	
enum AVM_ONOFF_RSP
{
	AVM_ENTER_RESPONE,
	AVM_EXIT_RESPONE,
};

enum AVM_Output_View_Status
{
	EXIT_AVM,
	ENTER_AVM,
	Enter_Calibration,
	Update_AVM,
};

enum CAN_LANGUAGE_TYPE
{
	Inactive = 0x00,
	Can_Simplified_Chinese,
	Can_Traditional_Chinese,
	Can_English,
	Can_French,
	Can_Arabic,
	Can_Russian,
};

enum SPI_LANGUAGE_TYPE
{
	SPI_Chinese,
	SPI_English,
};

enum HU_BlindSpotFilledFunctionReq_TYPE
{
	BlindFilledReq_Inactive = 0,
	BlindFilledReq_off,
	BlindFilledReq_on,
	BlindFilledReq_Reserved,
};

enum BlindSpotFilledFunctionInd_TYPE
{
	BlindFilledInd_off = 0,
	BlindFilledInd_on = 1,
};

enum AVSTurnFollowUpFunctionReq_TYPE
{
	AVSTurnFollowUpFunctionReq_Inactive = 0,
	AVSTurnFollowUpFunctionReq_off,
	AVSTurnFollowUpFunctionReq_on,
	AVSTurnFollowUpFunctionReq_Reserved,
};

enum TurnFollowUpFunctionInd_TYPE
{
	TurnFollowUpFunctionInd_off = 0,
	TurnFollowUpFunctionInd_on = 1,
};
typedef struct
{
	union
    {
        U8 uAVMConfigCode;
        struct
        {
            U8 unsed:5;   			// bit 0-4 
            U8 isRRSExist:1;  		// bit 5 
            U8 isAPAExist:1;		// bit 6
            U8 isAVMConfigured:1;	// bit 7
        }bAVMConfigCode;
    }AVMConfigUnion;
} AVM_CONFIG_CODE;

AVM_CONFIG_CODE AVMCofigCode;
extern BOOL bAccOnSelfCheckEnd;
extern BOOL bJ6_start_complete;
extern U8 SCalibrationResult;
extern U8 SEnterEOLViewResult;
extern void can_turnlamp_rxhandler(void);
extern void can_sig_init(void);
extern void can_avm_act_req_rxhandler(void);
extern void can_vehiclespeed_rxhandler(void);
extern void can_LeverInfo_rxhandler(void);
extern void can_AVS_switch_rxhandler(void);
extern void can_avm_hu_req_exit_rxhandler(void);
extern void can_avm_pdcautoon_req_rxhandler(void);
extern void can_avm_enter_exit_speech_rxhandler(void);
extern void can_acckey_rxhandler(void);
extern void can_steering_angle_rxhandler(void);
extern void can_coordinate_rxhandler(void);
extern void can_VehicleOdometer_rxhandler(void);
extern void CAN_CarDoorStaus_rxhandler(void);
extern void CAN_CarRearviewMirrorSt_rxhandler(void);
extern void can_msg_rx_attribute_handle(void);
extern void can_radar_distance_value_msg_rxhandler(void);
extern void can_PDCAndRadarSt_rxhander(void);
extern void can_PDCSensorErrorSt_rxhander(void);
extern void can_PDCSensorBlockageSt_rxhander(void);
extern void can_view_mode_angle_rxhandler(void);
extern void can_HUReqViewMode_rxhandler(void); 
extern void can_AVM_LED_Control();
extern void can_AVSErrorSt_txhandler(void);
extern void can_AVSStatus_txhandler(void);
extern void can_AVM_ViewModeControl_rxhandler(void);
extern void can_DynamicPGS_rxhandler(void);
extern void can_SetLanguage_rxhandler();
extern void can_CameraErrorSt_txhandler(void);
extern void can_FactoryModeReq_rxhandler(void);
extern void can_BlindSpotFilledReq_rxhandler(void);
extern void can_AVSTurnFollowUpFunctionReq_rxhander(void);
extern void can_RCTASt_rxhander(void);
extern void can_DynamicPGSSt_rxhandler(void);
extern void can_OTAMode_rxhandler(void);


extern U8 GW_OTAMode_fun;

#endif/*_CANAPP_H*/


#ifndef _M4_MSG_HANDLER_IF_H_
#define _M4_MSG_HANDLER_IF_H_ 
#define TEST_M4_UART

enum
{
    E_M4_MOVE_DATA_START,
    
    E_M4_VehicleSpeed_U16,
    E_M4_GearStatus_U8,
    E_M4_SteerWheelDirection_U8,
    E_M4_SteerWheelAngle_Multiple1H_U16,// Two decimal places
    E_M4_YawRateDirection_U8,
    E_M4_YawRate_Multiple1K_U32,// Three decimal places
    E_M4_LateralAcce_Multiple1K_U16,// Three decimal places
    E_M4_LongitAcce_Multiple1K_U16,// Three decimal places
    
    E_M4_FLWheelSpeed_U16,
    E_M4_FRwheelSpeed_U16,
    E_M4_RLwheelSpeed_U16,
    E_M4_RRwheelSpeed_U16,

    E_M4_FLWheelSpeed_PULSE_U16,
    E_M4_FRwheelSpeed_PULSE_U16,
    E_M4_RLwheelSpeed_PULSE_U16,
    E_M4_RRwheelSpeed_PULSE_U16,

	E_M4_ABSOLUTE_DELTA_X_U16,
	E_M4_ABSOLUTE_DELTA_Y_U16,
	E_M4_ABSOLUTE_DELTA_ANGLE_U16,

	E_M4_RELATIVE_DELTA_X_U16,
	E_M4_RELATIVE_DELTA_Y_U16,
	E_M4_RELATIVE_DELTA_ANGLE_U16,

	E_M4_PAS_COORDINATE_A_X_U16,
	E_M4_PAS_COORDINATE_A_Y_U16,

	E_M4_PAS_COORDINATE_B_X_U16,
	E_M4_PAS_COORDINATE_B_Y_U16,

	E_M4_PAS_COORDINATE_C_X_U16,
	E_M4_PAS_COORDINATE_C_Y_U16,

	E_M4_PAS_COORDINATE_D_X_U16,
	E_M4_PAS_COORDINATE_D_Y_U16,
	
	E_M4_PAS_COORDINATE_DEPTH_U16,

	E_M4_RESET_POSITION_REQ_U8,

	E_M4_BREAK_PEDAL_SWITCH_REQ_U8,

	E_M4_BREAK_POWER_U16,

	E_M4_HAZARD_STATUS_U8,

	E_M4_WIPER_STATUS_U8,

	E_M4_IPK_TIME_U32,

	E_M4_StandStill_U8,

	E_M4_RESERVE1_U8,
	E_M4_RESERVE2_U8,
	E_M4_RESERVE3_U8,
	E_M4_RESERVE4_U8,
	E_M4_RESERVE5_U8,
	E_M4_RESERVE6_U8,
	E_M4_RESERVE7_U8,
	E_M4_RESERVE8_U8,
	E_M4_RESERVE9_U8,

	E_M4MSGCOUNTER_U16,
	E_M4MSGCHECKSUM_U16,



    E_M4_MOVE_DATA_END,

    E_M4_CTRL_DATA_START,
    E_M4_PowerStatus_U8,
    E_M4_TurnSignal_U8,
    E_M4_DrvSeatbeltBuckleStatus_U8,
    E_M4_BrakePedalSwitchStatus_U8,
    E_M4_EPBStatus_U8,
    E_M4_AccelPedalPosition_U8,
    E_M4_AllBeamStatus_ByBit_U16,
    E_M4_AllDoorStatus_ByBit_U16,
    E_M4_CTRL_DATA_END,

    E_M4_RADAR_DATA_START,
    E_M4_RadarWorkingSatus_ByBit_U8,
    E_M4_RadarDis_FrontLeft_U16,
    E_M4_RadarDis_FrontMidLeft_U16,
    E_M4_RadarDis_FrontMidRight_U16,
    E_M4_RadarDis_FrontRight_U16,
    E_M4_RadarDis_LeftFront_U32,
    E_M4_RadarDis_LeftBack_U32,
    E_M4_RadarDis_BackLeft_U16,
    E_M4_RadarDis_BackMidLeft_U16,
    E_M4_RadarDis_BackMidRight_U16,
    E_M4_RadarDis_BackRight_U16 ,
    E_M4_RadarDis_RightFront_U32,
    E_M4_RadarDis_RightBack_U32,
    E_M4_RADAR_DATA_END,

	E_M4_RADAR_SENSOR_DIASTANCE_STATRT,
	E_M4_Radar_Sensor_Distance_FrontLeft_Long_U8,//1
	E_M4_Radar_Sensor_Distance_FrontRight_Long_U8,//2
	E_M4_Radar_Sensor_Distance_FrontLeft_Short_U8,//3
	E_M4_Radar_Sensor_Distance_FrontMiddleLeft_Short_U8,//4
	E_M4_Radar_Sensor_Distance_FrontMiddleRight_Short_U8,//5
	E_M4_Radar_Sensor_Distance_FrontRight_Short_U8,//6
	E_M4_Radar_Sensor_Distance_RearLeft_Long_U8,//7
	E_M4_Radar_Sensor_Distance_RearRight_Long_U8,//8
	E_M4_Radar_Sensor_Distance_RearLeft_Short_U8,//9
	E_M4_Radar_Sensor_Distance_RearMiddleLeft_Short_U8,//10
	E_M4_Radar_Sensor_Distance_RearMiddleRight_Short_U8,//11
	E_M4_Radar_Sensor_Distance_RearRight_Short_U8,//12
	E_M4_RADAR_SENSOR_DIASTANCE_END
};

    U8 M4Msg_Update(U8 MsgID,U32 Value);

#endif

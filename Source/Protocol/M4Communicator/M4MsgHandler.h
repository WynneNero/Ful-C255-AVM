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
* Version: 1.0
* Date:2017/10/30
* Author: TanPeng
***********************************************************************/
#ifndef _M4_MSG_HANDLER_H_
#define _M4_MSG_HANDLER_H_

#include "Hal_if.h"
#include "TYPES.H"
#include "Define.h"
#include "M4UartDriver_IF.H"
#include "M4MsgHandler_IF.h"
#include "GPIO_IF.H"

#define M4_MSG_BUF_SIZE (UART_FIFO_BUF_SIZE)

enum
{
    E_MOV_START = 0,
    
    E_VE_SPEED = E_MOV_START,
    E_GEAR_STATUS = E_VE_SPEED + 2,
    E_WHEEL_DIR = E_GEAR_STATUS + 1,
    E_WHEEL_ANGLE = E_WHEEL_DIR + 1,
    E_YAW_DIR = E_WHEEL_ANGLE+2,
    E_YAW_RATE = E_YAW_DIR + 1,
    E_LATERAL_ACCE = E_YAW_RATE +4,
    E_LONGIT_ACCE = E_LATERAL_ACCE + 2,

    E_FL_SPPED = E_LONGIT_ACCE + 2,
    E_FR_SPEED = E_FL_SPPED + 2,
    E_RL_SPEED = E_FR_SPEED + 2,
    E_RR_SPEED = E_RL_SPEED + 2,

    E_FL_SPPED_PULSE = E_RR_SPEED + 2,
    E_FR_SPEED_PULSE = E_FL_SPPED_PULSE + 2,
    E_RL_SPEED_PULSE = E_FR_SPEED_PULSE + 2,
    E_RR_SPEED_PULSE = E_RL_SPEED_PULSE + 2,

	E_ABSOLUTE_POS_X = E_RR_SPEED_PULSE + 2,
	E_ABSOLUTE_POS_Y = E_ABSOLUTE_POS_X + 2,
	E_ABSOLUTE_POS_ANGLE = E_ABSOLUTE_POS_Y + 2,

	E_RELATIVE_POS_X = E_ABSOLUTE_POS_ANGLE + 2,
	E_RELATIVE_POS_Y = E_RELATIVE_POS_X + 2,
	E_RELATIVE_POS_ANGLE = E_RELATIVE_POS_Y + 2,
	
	E_PAS_COORDINATE_A_X = E_RELATIVE_POS_ANGLE +2,
	E_PAS_COORDINATE_A_Y = E_PAS_COORDINATE_A_X +2,
	E_PAS_COORDINATE_B_X = E_PAS_COORDINATE_A_Y +2,
	E_PAS_COORDINATE_B_Y = E_PAS_COORDINATE_B_X +2,
	E_PAS_COORDINATE_C_X = E_PAS_COORDINATE_B_Y +2,
	E_PAS_COORDINATE_C_Y = E_PAS_COORDINATE_C_X +2,
	E_PAS_COORDINATE_D_X = E_PAS_COORDINATE_C_Y +2,
	E_PAS_COORDINATE_D_Y = E_PAS_COORDINATE_D_X +2,
	E_PAS_COORDINATE_DEPTH = E_PAS_COORDINATE_D_Y +2,

	E_RESET_POS_REQ = E_PAS_COORDINATE_DEPTH + 2,

	E_BREAK_PEDAL_SWITCH_REQ = E_RESET_POS_REQ + 1,
	E_BREAK_POWER = E_BREAK_PEDAL_SWITCH_REQ + 1,
	E_HAZARD_STATUS = E_BREAK_POWER + 2,
	E_WIPER_STATUS = E_HAZARD_STATUS + 1,
	E_IPK_TIME = E_WIPER_STATUS + 1,
	E_M4_StandStill = E_IPK_TIME + 4,
	
	E_RESERVE1 = E_M4_StandStill + 1,
	E_RESERVE2 = E_RESERVE1 + 1,
	E_RESERVE3 = E_RESERVE2 + 1,
	E_RESERVE4 = E_RESERVE3 + 1,
	E_RESERVE5 = E_RESERVE4 + 1,
	E_RESERVE6 = E_RESERVE5 + 1,
	E_RESERVE7 = E_RESERVE6 + 1,
	E_RESERVE8 = E_RESERVE7 + 1,
	E_RESERVE9 = E_RESERVE8 + 1,

	E_M4MSGCOUNTER = E_RESERVE9 +1,
	E_M4MSGCHECKSUM = E_M4MSGCOUNTER +2,

    E_MOV_END = E_M4MSGCHECKSUM + 2
 
};

enum
{
    E_CTRL_START = 0,
    E_POWER_STATUS = E_CTRL_START,
    E_TURN_SIGNAL = E_POWER_STATUS + 1,
    E_BUCKLE_STATUS = E_TURN_SIGNAL + 1,
    E_SWITCH_STATUS = E_BUCKLE_STATUS +1,
    E_EPB_STATUS = E_SWITCH_STATUS + 1,
    E_PEDAL_POSI = E_EPB_STATUS + 1,
    E_BEAM_STATUS = E_PEDAL_POSI + 1,
    E_DOOR_STATUS = E_BEAM_STATUS + 2,
    E_CTRL_END = E_DOOR_STATUS +2
    
};

enum
{
    // F: FRONT     L : LEFT    B: BACK      R: RIGHT
    E_RADAR_START = 0,
    E_WORKING_STATUS = E_RADAR_START, 
    E_DIS_FL = E_WORKING_STATUS + 1,
    E_DIS_FML = E_DIS_FL + 1,
    E_DIS_FMR = E_DIS_FML + 1,
    E_DIS_FR = E_DIS_FMR + 1,
    E_DIS_LF = E_DIS_FR + 1,
    E_DIS_LB = E_DIS_LF + 2,
    E_DIS_BL = E_DIS_LB + 2,
    E_DIS_BML = E_DIS_BL + 1,
    E_DIS_BMR = E_DIS_BML + 1,
    E_DIS_BR = E_DIS_BMR + 1,
    E_DIS_RF = E_DIS_BR + 1,
    E_DIS_RB = E_DIS_RF + 2,
    E_RADAR_END = E_DIS_RB +2
    
};

enum
{
	E_RADAR_SENSOR_DISTANCE_START = 0,
	E_FrontLeft_Long = E_RADAR_SENSOR_DISTANCE_START,
	E_FrontRight_Long = E_FrontLeft_Long + 1,	
	E_FrontLeft_Short = E_FrontRight_Long + 1,
	E_FrontMiddleLeft_Short = E_FrontLeft_Short + 1,
	E_FrontMiddleRight_Short = E_FrontMiddleLeft_Short + 1,
	E_FrontRight_Short = E_FrontMiddleRight_Short + 1,
	E_RearLeft_Long = E_FrontRight_Short + 1,
	E_RearRight_Long = E_RearLeft_Long + 1,
	E_RearLeft_Short = E_RearRight_Long + 1,
	E_RearMiddleLeft_Short = E_RearLeft_Short + 1,
	E_RearMiddleRight_Short = E_RearMiddleLeft_Short + 1,
	E_RearRight_Short = E_RearMiddleRight_Short + 1,
	E_RADAR_SENSOR_DISTANCE_END = E_RearRight_Short + 1
};

typedef enum  m4MsgID
{
    MSG_SEND_M4_CUR_CAR_MOVE_DATA              = 0X4401,
    MSG_SEND_M4_CUR_CAR_CTRL_DATA              = 0X4402,
    MSG_SEND_M4_CUR_CAR_RADAR_DATA             = 0X4403,
    MSG_SEND_M4_CUR_RADAR_SENSOR_DISTANCE      = 0X440A,
    
    MSG_M4_REQ_START_SEND               = 0X44AA,
    MSG_M4_REQ_RE_SEND                  = 0X44AB,
    MSG_SEND_M4_START_RECEIVE           = 0X44AC,
    MSG_M4_RESP_START_RECEIVE           = 0X44AD,
    
}M4MsgID;

enum
{
    E_M4MSG_ST_IDLE,
    E_M4MSG_ST_START,
    E_M4MSG_ST_WAIT_RESP,
    E_M4MSG_ST_RUN,
    E_M4MSG_ST_STOP,
    E_M4MSG_ST_MAX
};

typedef enum
{
	M4LED_BCM_TurnIndicatorLeft,
	M4LED_BCM_TurnIndicatorRight,
	M4LED_BCM_LowBeamSts,
	M4LED_BCM_HighBeamSts,
	M4LED_BCM_PositionLightSts,
	M4LED_BCM_FrontFogLightSts,
	M4LED_BCM_RearFogLightSts
}M4LEDStatus;

typedef enum
{
	M4LED_DDM_FrontLeftDoorAjarStatus,
	M4LED_PDM_FrontRightDoorAjarStatus,
	M4LED_PDM_RearRightDoorAjarStatus,
	M4LED_DDM_RearLeftDoorAjarStatus,
}M4DOORStatus;


typedef struct m4MsgHandler
{
    U16 status;
    BOOL isReqInit;
    BOOL isReqDeInit;
    BOOL isRecReqStart;
    BOOL isRecRespStart;
    U8 sendBuf[M4_MSG_BUF_SIZE];
    U8 rcvBuf[M4_MSG_BUF_SIZE];
}M4MsgHandler;

typedef struct m4MsgStruct
{
    U16 id;
    volatile U8  isreading; // mutex
    volatile U8  iswriting; // mutex
    U8  len;
    U8  data[M4_MSG_BUF_SIZE];
}M4MsgStruct;

typedef struct m4MsgMoveData
{
    M4MsgStruct send;
    BOOL isUpdate;
}M4Msg_MoveData;

typedef struct m4MsgCtrlData
{
    M4MsgStruct send;
    BOOL isUpdate;
}M4Msg_CtrlData;

typedef struct m4MsgRadarData
{
    M4MsgStruct send;
    volatile BOOL isUpdate;
}M4Msg_RadarData;

typedef struct m4MsgRadarDistance
{
	M4MsgStruct send;
    BOOL isUpdate;
}M4Msg_RadarSensorDistance;



#define M4UART_INITPIN_RX() 	GPIO_SetAlterMode(GPIO_PORT_0, GPIO_PIN_D, E_ALTERFUNC_1, GPIO_OPT_INIT|GPIO_OPT_INPUT); //RX
#define M4UART_INITPIN_TX()		GPIO_SetAlterMode(GPIO_PORT_0, GPIO_PIN_E, E_ALTERFUNC_1, GPIO_OPT_INIT);  //TX
#define SET_RX_OUTPUTMODE()		GPIO_SetOutputMode(GPIO_PORT_0, GPIO_PIN_D, GPIO_OPT_INIT, GPIO_OPT_INIT);
#define SET_TX_OUTPUTMODE()		GPIO_SetOutputMode(GPIO_PORT_0, GPIO_PIN_E, GPIO_OPT_INIT, GPIO_OPT_INIT);
#define SET_RX_OUTPUTLOW()		GPIO_SetVal(GPIO_PORT_0, GPIO_PIN_D, FALSE);
#define SET_TX_OUTPUTLOW()		GPIO_SetVal(GPIO_PORT_0, GPIO_PIN_E, FALSE);


void M4_DriverOpen(void);
void M4_DriverClose(void);

U8 M4_MsgSend(M4MsgStruct* psend);
void M4_MsgRcv(M4MsgStruct* prcv);

void M4_RcvDataHandle(M4MsgStruct* prcv);
void M4_TxHandle(void);
void M4_RxHandle(void);

void M4Msg_Init(void);
void M4Msg_DeInit(void);
void M4Msg_40ms_Entry(void);
extern U32 M4MSG_checksum_handler(void);
void M4UartPin_ChangeTo_GenIO(void); 


#endif

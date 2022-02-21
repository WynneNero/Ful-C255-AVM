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
#include "M4MsgHandler.h"
#include "Signal_if.h"
#include "ComplexDrvier_Globaldef_IF.H"
#include "TimerMng.h"

static M4MsgHandler msgHand;
static M4MsgStruct rcv;

static M4Msg_MoveData moveDataSend;
static M4Msg_CtrlData ctrlDataSend;
//static M4Msg_RadarData radarDataSend;
static M4Msg_RadarSensorDistance raderDistanceSend;


void M4Msg_MoveData_Update(U8 MsgID,U32 Value)
{
    switch(MsgID)
    {
        case E_M4_VehicleSpeed_U16:
        {
            moveDataSend.send.data[E_VE_SPEED] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_VE_SPEED+1] = (U8)((Value >> 0) & 0XFF);
            break;
        }

        case E_M4_GearStatus_U8:
        {
            moveDataSend.send.data[E_GEAR_STATUS] = (U8)((Value >> 0) & 0XFF);
            break;
        }

        case E_M4_SteerWheelDirection_U8:
        {
            moveDataSend.send.data[E_WHEEL_DIR] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_SteerWheelAngle_Multiple1H_U16:
        {
            moveDataSend.send.data[E_WHEEL_ANGLE] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_WHEEL_ANGLE+1] = (U8)((Value >> 0) & 0XFF);
            break;
        }

        case E_M4_YawRateDirection_U8:
        {
             moveDataSend.send.data[E_YAW_DIR] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        case E_M4_YawRate_Multiple1K_U32:
        {
            moveDataSend.send.data[E_YAW_RATE] = (U8)((Value >> 24) & 0XFF);
            moveDataSend.send.data[E_YAW_RATE+1] = (U8)((Value >> 16) & 0XFF);
            moveDataSend.send.data[E_YAW_RATE+2] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_YAW_RATE+3] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_LateralAcce_Multiple1K_U16:
        {
            moveDataSend.send.data[E_LATERAL_ACCE] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_LATERAL_ACCE+1] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_LongitAcce_Multiple1K_U16:
        {
            moveDataSend.send.data[E_LONGIT_ACCE] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_LONGIT_ACCE+1] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        case E_M4_FLWheelSpeed_U16:
        {
            moveDataSend.send.data[E_FL_SPPED] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_FL_SPPED+1] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        case E_M4_FRwheelSpeed_U16:
        {
            moveDataSend.send.data[E_FR_SPEED] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_FR_SPEED+1] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_RLwheelSpeed_U16:
        {
            moveDataSend.send.data[E_RL_SPEED] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_RL_SPEED+1] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_RRwheelSpeed_U16:
        {
            moveDataSend.send.data[E_RR_SPEED] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_RR_SPEED+1] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_FLWheelSpeed_PULSE_U16:
        {
            moveDataSend.send.data[E_FL_SPPED_PULSE] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_FL_SPPED_PULSE+1] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_FRwheelSpeed_PULSE_U16:
        {
            moveDataSend.send.data[E_FR_SPEED_PULSE] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_FR_SPEED_PULSE+1] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_RLwheelSpeed_PULSE_U16:
        {
            moveDataSend.send.data[E_RL_SPEED_PULSE] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_RL_SPEED_PULSE+1] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_RRwheelSpeed_PULSE_U16:
        {
            moveDataSend.send.data[E_RR_SPEED_PULSE] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_RR_SPEED_PULSE+1] = (U8)((Value >> 0) & 0XFF);
            break;
        } 
		
        case E_M4_ABSOLUTE_DELTA_X_U16:
        {
            moveDataSend.send.data[E_ABSOLUTE_POS_X] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_ABSOLUTE_POS_X+1] = (U8)((Value >> 0) & 0XFF);
            break;
        } 
		
        case E_M4_ABSOLUTE_DELTA_Y_U16:
        {
            moveDataSend.send.data[E_ABSOLUTE_POS_Y] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_ABSOLUTE_POS_Y+1] = (U8)((Value >> 0) & 0XFF);
            break;
        } 
		
        case E_M4_ABSOLUTE_DELTA_ANGLE_U16:
        {
            moveDataSend.send.data[E_ABSOLUTE_POS_ANGLE] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_ABSOLUTE_POS_ANGLE+1] = (U8)((Value >> 0) & 0XFF);
            break;
        } 
		
        case E_M4_RELATIVE_DELTA_X_U16:
        {
            moveDataSend.send.data[E_RELATIVE_POS_X] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_RELATIVE_POS_X+1] = (U8)((Value >> 0) & 0XFF);
            break;
        } 
		
        case E_M4_RELATIVE_DELTA_Y_U16:
        {
            moveDataSend.send.data[E_RELATIVE_POS_Y] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_RELATIVE_POS_Y+1] = (U8)((Value >> 0) & 0XFF);
            break;
        } 
		
        case E_M4_RELATIVE_DELTA_ANGLE_U16:
        {
            moveDataSend.send.data[E_RELATIVE_POS_ANGLE] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_RELATIVE_POS_ANGLE+1] = (U8)((Value >> 0) & 0XFF);
            break;
        } 

        case E_M4_PAS_COORDINATE_A_X_U16:
        {
            moveDataSend.send.data[E_PAS_COORDINATE_A_X] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_PAS_COORDINATE_A_X+1] = (U8)((Value >> 0) & 0XFF);
            break;
        } 
		
        case E_M4_PAS_COORDINATE_A_Y_U16:
        {
            moveDataSend.send.data[E_PAS_COORDINATE_A_Y] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_PAS_COORDINATE_A_Y+1] = (U8)((Value >> 0) & 0XFF);
            break;
        } 
		
        case E_M4_PAS_COORDINATE_B_X_U16:
        {
            moveDataSend.send.data[E_PAS_COORDINATE_B_X] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_PAS_COORDINATE_B_X+1] = (U8)((Value >> 0) & 0XFF);
            break;
        } 
		
        case E_M4_PAS_COORDINATE_B_Y_U16:
        {
            moveDataSend.send.data[E_PAS_COORDINATE_B_Y] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_PAS_COORDINATE_B_Y+1] = (U8)((Value >> 0) & 0XFF);
            break;
        } 
		
        case E_M4_PAS_COORDINATE_C_X_U16:
        {
            moveDataSend.send.data[E_PAS_COORDINATE_C_X] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_PAS_COORDINATE_C_X+1] = (U8)((Value >> 0) & 0XFF);
            break;
        } 

        case E_M4_PAS_COORDINATE_C_Y_U16:
        {
            moveDataSend.send.data[E_PAS_COORDINATE_C_Y] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_PAS_COORDINATE_C_Y+1] = (U8)((Value >> 0) & 0XFF);
            break;
        } 

		case E_M4_PAS_COORDINATE_D_X_U16:
        {
            moveDataSend.send.data[E_PAS_COORDINATE_D_X] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_PAS_COORDINATE_D_X+1] = (U8)((Value >> 0) & 0XFF);
            break;
        } 

        case E_M4_PAS_COORDINATE_D_Y_U16:
        {
			moveDataSend.send.data[E_PAS_COORDINATE_D_Y] = (U8)((Value >> 8) & 0XFF);
			moveDataSend.send.data[E_PAS_COORDINATE_D_Y+1] = (U8)((Value >> 0) & 0XFF);
            break;
        } 

        case E_M4_PAS_COORDINATE_DEPTH_U16:
        {
            moveDataSend.send.data[E_PAS_COORDINATE_DEPTH] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_PAS_COORDINATE_DEPTH+1] = (U8)((Value >> 0) & 0XFF);
            break;
        } 

        case E_M4_RESET_POSITION_REQ_U8:
        {
            moveDataSend.send.data[E_RESET_POS_REQ] = (U8)((Value >> 0) & 0XFF);
            break;
        } 

		case E_M4_BREAK_PEDAL_SWITCH_REQ_U8:
		{
			moveDataSend.send.data[E_BREAK_PEDAL_SWITCH_REQ] = (U8)((Value >> 0) & 0XFF);
            break;
		}
		case E_M4_BREAK_POWER_U16:
		{
			moveDataSend.send.data[E_BREAK_POWER] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_BREAK_POWER+1] = (U8)((Value >> 0) & 0XFF);			
            break;
		}
		case E_M4_HAZARD_STATUS_U8:
		{
			moveDataSend.send.data[E_HAZARD_STATUS] = (U8)((Value >> 0) & 0XFF);
            break;
		}
		case E_M4_WIPER_STATUS_U8:
		{
			moveDataSend.send.data[E_WIPER_STATUS] = (U8)((Value >> 0) & 0XFF);
            break;
		}
		case E_M4_IPK_TIME_U32:
		{
			moveDataSend.send.data[E_IPK_TIME] = (U8)((Value >> 24) & 0XFF);
            moveDataSend.send.data[E_IPK_TIME+1] = (U8)((Value >> 16) & 0XFF);
            moveDataSend.send.data[E_IPK_TIME+2] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_IPK_TIME+3] = (U8)((Value >> 0) & 0XFF);
            break;
		}
		case E_M4_StandStill_U8:
		{
			moveDataSend.send.data[E_M4_StandStill] = (U8)((Value >> 0) & 0XFF);
            break;
		}

		//********************************reserve byte*******************************//
		case E_M4_RESERVE1_U8:
		{
			moveDataSend.send.data[E_RESERVE1] = (U8)((Value >> 0) & 0XFF);
            break;
		}
		case E_M4_RESERVE2_U8:
		{
			moveDataSend.send.data[E_RESERVE2] = (U8)((Value >> 0) & 0XFF);
            break;
		}
		case E_M4_RESERVE3_U8:
		{
			moveDataSend.send.data[E_RESERVE3] = (U8)((Value >> 0) & 0XFF);
            break;
		}
		case E_M4_RESERVE4_U8:
		{
			moveDataSend.send.data[E_RESERVE4] = (U8)((Value >> 0) & 0XFF);
            break;
		}
		case E_M4_RESERVE5_U8:
		{
			moveDataSend.send.data[E_RESERVE5] = (U8)((Value >> 0) & 0XFF);
            break;
		}
		case E_M4_RESERVE6_U8:
		{
			moveDataSend.send.data[E_RESERVE6] = (U8)((Value >> 0) & 0XFF);
            break;
		}
		case E_M4_RESERVE7_U8:
		{
			moveDataSend.send.data[E_RESERVE7] = (U8)((Value >> 0) & 0XFF);
            break;
		}
		case E_M4_RESERVE8_U8:
		{
			moveDataSend.send.data[E_RESERVE8] = (U8)((Value >> 0) & 0XFF);
            break;
		}
		case E_M4_RESERVE9_U8:
		{
			moveDataSend.send.data[E_RESERVE9] = (U8)((Value >> 0) & 0XFF);
            break;
		}
        /*
		case E_M4_RESERVE10_U8:
		{
			moveDataSend.send.data[E_RESERVE10] = (U8)((Value >> 0) & 0XFF);
            break;
		}
		*/
		case E_M4MSGCOUNTER_U16:
		{
			moveDataSend.send.data[E_M4MSGCOUNTER] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_M4MSGCOUNTER+1] = (U8)((Value >> 0) & 0XFF);			
            break;
		}
		case E_M4MSGCHECKSUM_U16:
		{
			moveDataSend.send.data[E_M4MSGCHECKSUM] = (U8)((Value >> 8) & 0XFF);
            moveDataSend.send.data[E_M4MSGCHECKSUM+1] = (U8)((Value >> 0) & 0XFF);			
            break;
		}
        default :
            break;
    }
}

void M4Msg_CtrlData_Update(U8 MsgID,U32 Value)
{
    switch(MsgID)
    {
        case E_M4_PowerStatus_U8:
        {
            ctrlDataSend.send.data[E_POWER_STATUS] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_TurnSignal_U8:
        {
            ctrlDataSend.send.data[E_TURN_SIGNAL] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_DrvSeatbeltBuckleStatus_U8:
        {
            ctrlDataSend.send.data[E_BUCKLE_STATUS] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_BrakePedalSwitchStatus_U8:
        {
            ctrlDataSend.send.data[E_SWITCH_STATUS] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_EPBStatus_U8:
        {
            ctrlDataSend.send.data[E_EPB_STATUS] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_AccelPedalPosition_U8:
        {
            ctrlDataSend.send.data[E_PEDAL_POSI] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_AllBeamStatus_ByBit_U16:
        {
            ctrlDataSend.send.data[E_BEAM_STATUS] = (U8)((Value >> 8) & 0XFF);
            ctrlDataSend.send.data[E_BEAM_STATUS+1] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_AllDoorStatus_ByBit_U16:
        {
            ctrlDataSend.send.data[E_DOOR_STATUS] = (U8)((Value >> 8) & 0XFF);
            ctrlDataSend.send.data[E_DOOR_STATUS+1] = (U8)((Value >> 0) & 0XFF);
            break;
        }
         
        default :
            break;
    }
}
/*
void M4Msg_RadarData_Update(U8 MsgID,U32 Value)
{
    switch(MsgID)
    {
        case E_M4_RadarWorkingSatus_ByBit_U8:
        {
            radarDataSend.send.data[E_WORKING_STATUS] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_RadarDis_FrontLeft_U16:
        {
            radarDataSend.send.data[E_DIS_FL] = (U8)((Value >> 8) & 0XFF);
            radarDataSend.send.data[E_DIS_FL+1] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_RadarDis_FrontMidLeft_U16:
        {
            radarDataSend.send.data[E_DIS_FML] = (U8)((Value >> 8) & 0XFF);
            radarDataSend.send.data[E_DIS_FML+1] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_RadarDis_FrontMidRight_U16:
        {
            radarDataSend.send.data[E_DIS_FMR] = (U8)((Value >> 8) & 0XFF);
            radarDataSend.send.data[E_DIS_FMR+1] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_RadarDis_FrontRight_U16:
        {
            radarDataSend.send.data[E_DIS_FR] = (U8)((Value >> 8) & 0XFF);
            radarDataSend.send.data[E_DIS_FR+1] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_RadarDis_LeftFront_U32:
        {
            radarDataSend.send.data[E_DIS_LF] = (U8)((Value >> 24) & 0XFF);
            radarDataSend.send.data[E_DIS_LF+1] = (U8)((Value >> 16) & 0XFF);
            radarDataSend.send.data[E_DIS_LF+2] = (U8)((Value >> 8) & 0XFF);
            radarDataSend.send.data[E_DIS_LF+3] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_RadarDis_LeftBack_U32:
        {
            radarDataSend.send.data[E_DIS_LB] = (U8)((Value >> 24) & 0XFF);
            radarDataSend.send.data[E_DIS_LB+1] = (U8)((Value >> 16) & 0XFF);
            radarDataSend.send.data[E_DIS_LB+2] = (U8)((Value >> 8) & 0XFF);
            radarDataSend.send.data[E_DIS_LB+3] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_RadarDis_BackLeft_U16:
        {
            radarDataSend.send.data[E_DIS_BL] = (U8)((Value >> 8) & 0XFF);
            radarDataSend.send.data[E_DIS_BL+1] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_RadarDis_BackMidLeft_U16:
        {
            radarDataSend.send.data[E_DIS_BML] = (U8)((Value >> 8) & 0XFF);
            radarDataSend.send.data[E_DIS_BML+1] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_RadarDis_BackMidRight_U16:
        {
            radarDataSend.send.data[E_DIS_BMR] = (U8)((Value >> 8) & 0XFF);
            radarDataSend.send.data[E_DIS_BMR+1] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_RadarDis_BackRight_U16:
        {
            radarDataSend.send.data[E_DIS_BR] = (U8)((Value >> 8) & 0XFF);
            radarDataSend.send.data[E_DIS_BR+1] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_RadarDis_RightFront_U32:
        {
            radarDataSend.send.data[E_DIS_RF] = (U8)((Value >> 24) & 0XFF);
            radarDataSend.send.data[E_DIS_RF+1] = (U8)((Value >> 16) & 0XFF);
            radarDataSend.send.data[E_DIS_RF+2] = (U8)((Value >> 8) & 0XFF);
            radarDataSend.send.data[E_DIS_RF+3] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_RadarDis_RightBack_U32:
        {
            radarDataSend.send.data[E_DIS_RB] = (U8)((Value >> 24) & 0XFF);
            radarDataSend.send.data[E_DIS_RB+1] = (U8)((Value >> 16) & 0XFF);
            radarDataSend.send.data[E_DIS_RB+2] = (U8)((Value >> 8) & 0XFF);
            radarDataSend.send.data[E_DIS_RB+3] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        default :
            break;
    }
}
*/
void M4Msg_RadarSensorDistance_Data(U8 MsgID,U32 Value)
{
    switch(MsgID)
    {
        case E_M4_Radar_Sensor_Distance_FrontLeft_Long_U8:
        {
            raderDistanceSend.send.data[E_FrontLeft_Long] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_Radar_Sensor_Distance_FrontRight_Long_U8:
        {
            raderDistanceSend.send.data[E_FrontRight_Long] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_Radar_Sensor_Distance_FrontLeft_Short_U8:
        {
            raderDistanceSend.send.data[E_FrontLeft_Short] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_Radar_Sensor_Distance_FrontMiddleLeft_Short_U8:
        {
            raderDistanceSend.send.data[E_FrontMiddleLeft_Short] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_Radar_Sensor_Distance_FrontMiddleRight_Short_U8:
        {
            raderDistanceSend.send.data[E_FrontMiddleRight_Short] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_Radar_Sensor_Distance_FrontRight_Short_U8:
        {
           raderDistanceSend.send.data[E_FrontRight_Short] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_Radar_Sensor_Distance_RearLeft_Long_U8:
        {
            raderDistanceSend.send.data[E_RearLeft_Long] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_Radar_Sensor_Distance_RearRight_Long_U8:
        {
            raderDistanceSend.send.data[E_RearRight_Long] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_Radar_Sensor_Distance_RearLeft_Short_U8:
        {
            raderDistanceSend.send.data[E_RearLeft_Short] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_Radar_Sensor_Distance_RearMiddleLeft_Short_U8:
        {
            raderDistanceSend.send.data[E_RearMiddleLeft_Short] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_Radar_Sensor_Distance_RearMiddleRight_Short_U8:
        {
            raderDistanceSend.send.data[E_RearMiddleRight_Short] = (U8)((Value >> 0) & 0XFF);
            break;
        }
        
        case E_M4_Radar_Sensor_Distance_RearRight_Short_U8:
        {
            raderDistanceSend.send.data[E_RearRight_Short] = (U8)((Value >> 0) & 0XFF);
            break;
        }

        default :
            break;
    }
}



U8 M4Msg_Update(U8 MsgID,U32 Value)
{
    U8 result = ERR_FAILED;
    if((MsgID > E_M4_MOVE_DATA_START) && (MsgID < E_M4_MOVE_DATA_END))
    {
        if(moveDataSend.send.isreading == FALSE)
        {
            moveDataSend.send.iswriting = TRUE;
            moveDataSend.send.id = MSG_SEND_M4_CUR_CAR_MOVE_DATA;
            moveDataSend.send.len = E_MOV_END - E_MOV_START;
            M4Msg_MoveData_Update(MsgID,Value);
            moveDataSend.isUpdate = TRUE;
            moveDataSend.send.iswriting = FALSE;
			M4Msg_MoveData_Update(E_M4MSGCHECKSUM_U16,M4MSG_checksum_handler());
            result = ERR_OK;
        }
        
    }
    
    if((MsgID > E_M4_CTRL_DATA_START) && (MsgID < E_M4_CTRL_DATA_END))
    {
        if(ctrlDataSend.send.isreading == FALSE)
        {
            ctrlDataSend.send.iswriting = TRUE;
            ctrlDataSend.send.id = MSG_SEND_M4_CUR_CAR_CTRL_DATA;
            ctrlDataSend.send.len = E_CTRL_END - E_CTRL_START;
            M4Msg_CtrlData_Update(MsgID,Value);
            ctrlDataSend.isUpdate = TRUE;
            ctrlDataSend.send.iswriting = FALSE;
            result = ERR_OK;
        }
    }
    /*
    if((MsgID > E_M4_RADAR_DATA_START) && (MsgID < E_M4_RADAR_DATA_END))
    {
        if(radarDataSend.send.isreading == FALSE)
        {
            radarDataSend.send.iswriting = TRUE;
            radarDataSend.send.id = MSG_SEND_M4_CUR_CAR_RADAR_DATA;
            radarDataSend.send.len = E_RADAR_END - E_RADAR_START;
            //M4Msg_RadarData_Update(MsgID,Value);
            radarDataSend.isUpdate = TRUE;
            radarDataSend.send.iswriting = FALSE;
            result = ERR_OK;
        }
    }
	*/
	if((MsgID > E_M4_RADAR_SENSOR_DIASTANCE_STATRT) && (MsgID < E_M4_RADAR_SENSOR_DIASTANCE_END))
    {
        if(raderDistanceSend.send.isreading == FALSE)
        {
            raderDistanceSend.send.iswriting = TRUE;
            raderDistanceSend.send.id = MSG_SEND_M4_CUR_RADAR_SENSOR_DISTANCE;
            raderDistanceSend.send.len = E_RADAR_SENSOR_DISTANCE_END - E_RADAR_SENSOR_DISTANCE_START;
            M4Msg_RadarSensorDistance_Data(MsgID,Value);
            raderDistanceSend.isUpdate = TRUE;
            raderDistanceSend.send.iswriting = FALSE;
            result = ERR_OK;
        }
    }
    return result;
}



void M4_DriverOpen(void)
{
    HAL_Open(DEV_M4DRIVER);
}

void M4_DriverClose(void)
{
    HAL_Close(DEV_M4DRIVER);
}

U8 M4_MsgSend(M4MsgStruct* psend)
{
    U8 result = ERR_FAILED;
    if(psend == NULL)
    {
        return  result;
    }
    
    _memset(msgHand.sendBuf,0,M4_MSG_BUF_SIZE);
    psend->isreading = TRUE;
    msgHand.sendBuf[0] = (U8)((psend->id >> 8) & 0X00FF);
    msgHand.sendBuf[1] = (U8)(psend->id & 0X00FF);
    msgHand.sendBuf[2] = psend->len;
    _memcpy(&msgHand.sendBuf[3],psend->data,psend->len);
    psend->isreading = FALSE;
    result = HAL_Write(DEV_M4DRIVER, msgHand.sendBuf,psend->len+3); 
    return result ;
 
}

void M4_MsgRcv(M4MsgStruct* prcv)
{
    if(prcv == NULL)
    {
        return;
    }
    
    _memset((U8*)prcv,0,sizeof(M4MsgStruct));
    _memset(msgHand.rcvBuf,0,M4_MSG_BUF_SIZE);

    
    if(HAL_Read(DEV_M4DRIVER,msgHand.rcvBuf,UART_FIFO_BUF_SIZE))
    {
        prcv->id = (msgHand.rcvBuf[0]<<8)+ msgHand.rcvBuf[1];
        prcv->len = msgHand.rcvBuf[2];
        _memcpy(prcv->data,&msgHand.rcvBuf[3],rcv.len);
    }
}

void M4Msg_Init(void)
{
   	msgHand.isReqInit = TRUE;
 }
void M4DataReset(void)
{
    _memset(msgHand.sendBuf,0,M4_MSG_BUF_SIZE);
    _memset(msgHand.rcvBuf,0,M4_MSG_BUF_SIZE);
    _memset(&rcv,0,sizeof(rcv));
        
    _memset(&moveDataSend,0,sizeof(moveDataSend));
    _memset(&ctrlDataSend,0,sizeof(ctrlDataSend));
    //_memset(&radarDataSend,0,sizeof(radarDataSend));
    moveDataSend.isUpdate = TRUE;
    ctrlDataSend.isUpdate = TRUE;
    //radarDataSend.isUpdate = TRUE;
}

void M4Msg_DeInit(void)
{
    msgHand.isReqDeInit = TRUE;
}

void M4_TxHandle(void)
{
    if((moveDataSend.isUpdate == TRUE)&&(moveDataSend.send.iswriting == FALSE))
    {
        if(M4_MsgSend(&(moveDataSend.send)) == ERR_OK)
        {
            //moveDataSend.isUpdate == FALSE;
        }
    }

	if((raderDistanceSend.isUpdate == TRUE)&&(raderDistanceSend.send.iswriting == FALSE))
		{
			if(M4_MsgSend(&(raderDistanceSend.send)) == ERR_OK)
			{
				//moveDataSend.isUpdate == FALSE;
			}
		}

    if((ctrlDataSend.isUpdate == TRUE)&&(ctrlDataSend.send.iswriting == FALSE))
    {
         if(M4_MsgSend(&(ctrlDataSend.send)) == ERR_OK)
         {
             ctrlDataSend.isUpdate = FALSE;
         }
    }
}

void M4_NotifyStart(void)
{
    M4MsgStruct send;
    send.id = MSG_SEND_M4_START_RECEIVE ;
    send.len = 1;
    send.data[0] = 1;
    M4_MsgSend(&send);
}

#ifdef TEST_M4_UART
void test_m4_tx(void)
{
    M4MsgStruct send;
    static U8 tect_cnt = 2;
//    if(tect_cnt)
    {
        send.id = 0X44AA;
        send.len = 0x1;
        send.data[0]= 0x01;

        M4_MsgSend(&send);

        send.id = 0X44AD;
        send.len = 0x1;
        send.data[0]= 0x01;
        
//        tect_cnt--;
    }
    
}
#endif

void M4_RxHandle(void)
{
    M4_MsgRcv(&rcv);
    M4_RcvDataHandle(&rcv);
}

void M4_RcvDataHandle(M4MsgStruct* prcv)
{
    if(prcv == NULL)
    {
        return;
    }
    
    switch (prcv->id)
    {
        case MSG_M4_REQ_START_SEND:
        {
      		M4_NotifyStart();		
            msgHand.isRecReqStart = TRUE;
            break;
        }
        case MSG_M4_RESP_START_RECEIVE:
        {
             msgHand.isRecRespStart = TRUE;
             break;
        }
        case MSG_M4_REQ_RE_SEND:
        {
            // wait exception handler
            break;
        }

        default:
            break;


    }

}

void open_m4uart_pwr(void)
{
	M4UartDriver_Init();
	M4Msg_Init();
}

/*
void M4Msg_Handle_20msEntry(void)
{
	static U8 M4MsgSendCnt=0;
	M4MsgSendCnt++;
	if(M4MsgSendCnt > 1)
	{
		M4Msg_40ms_Entry();
		M4MsgSendCnt = 0;
	}
}
*/
/*
void M4Msg_Counter_Handle_40msEntry(void)
{
	static U16 M4MsgSendCounter;
	M4MsgSendCounter++;
	if(M4MsgSendCounter == 0xFFFF)
	{
		M4MsgSendCounter = 0;
	}
	M4Msg_Update(E_M4MSGCOUNTER_U16,M4MsgSendCounter);  // M4 msg counter 40ms cycle
}
*/
U8 M4MsgHandlerSt;
void M4Msg_40ms_Entry(void)
{
	//M4Msg_Counter_Handle_40msEntry(); 
    switch (msgHand.status)
    {
      case E_M4MSG_ST_IDLE:
      { 
            if(msgHand.isReqInit)
            {	
				M4UART_INITPIN_RX();
				M4UART_INITPIN_TX();
		    	M4DataReset();
                M4_DriverOpen();
                msgHand.isReqInit = FALSE;
                msgHand.status = E_M4MSG_ST_START;
                //msgHand.status = E_M4MSG_ST_RUN;
            }
            break;
      }
      case E_M4MSG_ST_START:
      {     
            M4_RxHandle();
            if(msgHand.isRecReqStart)
            {
                msgHand.isRecReqStart = FALSE;
                msgHand.status = E_M4MSG_ST_WAIT_RESP;
            }
            if(msgHand.isReqDeInit)
            {
                M4_DriverClose();
                msgHand.isReqDeInit = FALSE;
                msgHand.status = E_M4MSG_ST_STOP;
            }
            break;
      }
      case E_M4MSG_ST_WAIT_RESP:
      {
            M4_RxHandle();
			if(msgHand.isRecRespStart)
			{
				msgHand.status = E_M4MSG_ST_RUN;
			}
			if(msgHand.isReqDeInit)
            {
                M4_DriverClose();
                msgHand.isReqDeInit = FALSE;
                msgHand.status = E_M4MSG_ST_STOP;
            }
            break;
      }
      case E_M4MSG_ST_RUN:
      {
            M4_TxHandle();
            M4_RxHandle(); 
			if(msgHand.isReqDeInit)
            {
                M4_DriverClose();
                msgHand.isReqDeInit = FALSE;
                msgHand.status = E_M4MSG_ST_STOP;
            }
            break;
      }
      case E_M4MSG_ST_STOP:
      {
            if(msgHand.isReqInit)
            {
				 M4UART_INITPIN_RX();
				 M4UART_INITPIN_TX();
				 M4DataReset();
				 M4_DriverOpen();
				 msgHand.isReqInit = FALSE;
				 msgHand.isReqDeInit = FALSE;
				 msgHand.status = E_M4MSG_ST_START;
            } 
			else 
			{
				M4UartPin_ChangeTo_GenIO();
			}
      }
      default:
            break;
    }
    M4MsgHandlerSt = msgHand.status;
}

/***********************************************************************
*  Name        : M4UartPin_ChangeTo_GenIO
*  Description : When the SOC closing, need to set the UART pin switch for the output low
*  Parameter  :  None
*  Returns     : None
***********************************************************************/
void M4UartPin_ChangeTo_GenIO(void) // uidq0888:To prevent hardware string of electricity
{
	SET_RX_OUTPUTMODE();
	SET_TX_OUTPUTMODE();
	SET_RX_OUTPUTLOW();
	SET_TX_OUTPUTLOW();
}

U32 M4MSG_checksum_handler(void)
{
	U16 i;
	U32 M4_checksum = 0;
	for(i=E_MOV_START;i<E_M4MSGCHECKSUM;i++)
	{
		M4_checksum += moveDataSend.send.data[i];
	}
	return M4_checksum;
}

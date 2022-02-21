/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : IDA SW1     									   		   *
*   AUTHOR	   : 									                   *
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
* Version   Date        Name             Changes and comments
* ----------------------------------------------------------------------
* 0.1    	20190501  	LUWEI			    Initial version
*=====================================================================*/
#include "math.h"
#include "APSDR.h"



ExtL_APSDR_T APSDR_L;
ExtW_APSDR_T APSDR_W;
float SinLength = 0;
//float dt_dr_yaw = 0;
//float dt_dr_esc = 0;
//float dt_dr_sas = 0;
float dr_yaw = 0;
float dr_esc = 0;
float dr_sas = 0;

void APSDR_init(void)
{
	APSDR_W.DRTheta = 0;
	APSDR_W.DRXPosition = 0;
	APSDR_W.DRYPosition = 0;
	dr_yaw = 0;
	dr_esc = 0;
	dr_sas = 0;
	SinLength = 2*pi*DR_ESC_WheelRadius/DR_ESC_PulseNum;
}

void APSDR_step(void)
{
	static float dx_dr = 0;
	static float dy_dr = 0;
	static float dt_dr_yaw = 0;
	static float dt_dr_esc = 0;
	static float dt_dr_sas = 0;
	static short dRLC_dt = 0;
	static short dRRC_dt = 0;
	static unsigned short RLWheelSpeedRC[2] = {0};
	static unsigned short RRWheelSpeedRC[2] = {0};
	static float Left_length = 0;
	static float Right_length = 0;

	dRLC_dt = APSDR_L.RLWheelSpeedRC - RLWheelSpeedRC[1];
	dRRC_dt = APSDR_L.RRWheelSpeedRC - RRWheelSpeedRC[1];
	RRWheelSpeedRC[1] = RRWheelSpeedRC[0];
	RRWheelSpeedRC[0] = APSDR_L.RRWheelSpeedRC;
	RLWheelSpeedRC[1] = RLWheelSpeedRC[0];
	RLWheelSpeedRC[0] = APSDR_L.RLWheelSpeedRC;
	
	if(dRLC_dt < 0)
	{
		dRLC_dt = dRLC_dt + DR_ESC_PulseMax;
	}
	if(dRRC_dt < 0)
	{
		dRRC_dt = dRRC_dt + DR_ESC_PulseMax;
	}
	
	Left_length = dRLC_dt * SinLength/2;
	Right_length = dRRC_dt * SinLength/2;

	dx_dr = ((Right_length + Left_length)/2)*cos(APSDR_W.DRTheta/Ang_to_Rad);
	dy_dr = ((Right_length + Left_length)/2)*sin(APSDR_W.DRTheta/Ang_to_Rad);

	dt_dr_yaw = (APSDR_L.YawRate - APSDR_L.Zerodrift) * yaw_cycle;													//横摆角计算角度
	dt_dr_esc = (Right_length - Left_length)/DR_ESC_CarWidth*Rad_to_Ang;											//轮速脉冲计算角度
	dt_dr_sas = ((Right_length + Left_length)/2)/(DR_ESC_Wheelbase/tan(APSDR_L.Saswheelsteerangle/DR_Radio/Ang_to_Rad))*Rad_to_Ang;	//转向半径计算角度

	if(APSDR_L.ModeGearDisplaySt == 0x4)
	{
		APSDR_W.DRXPosition += dx_dr;
		APSDR_W.DRYPosition += dy_dr;
		dr_esc += dt_dr_esc;
		dr_sas += dt_dr_sas;
	}
	else if(APSDR_L.ModeGearDisplaySt == 0x2)
	{
		APSDR_W.DRXPosition -= dx_dr;
		APSDR_W.DRYPosition -= dy_dr;
		dr_esc -= dt_dr_esc;
		dr_sas -= dt_dr_sas;
	}
	dr_yaw += dt_dr_yaw;

	APSDR_W.DRTheta = ((dr_esc*esc_factor)+(dr_yaw*yaw_factor)+(dr_sas*sas_factor));
}


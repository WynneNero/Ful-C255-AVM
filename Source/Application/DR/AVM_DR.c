#include "AVM_DR.h"

#include "M4MsgHandler_IF.h"
#include "il_par.h"
#include "CanApp.h"
#include "math.h"
//#include "APSDR.h"


APA_VehiclePositionFloat VehOriginPos, VehRelativePos;
extern float can_YawRate;
extern U16 can_vehiclespeed;
extern float SinLength;

U8 AVM_DrCnt = 0;
//#define BlindPaddingReq_SW

void AVM_DR_20ms_Entry(void)
{
	apscan_YRS_Status();
	apscan_ESC_WheelSpeedsRC();
	VehicleDeadReckoningHandler();
}


//////////////////////////////////////////////////////DR handle///////////////////////////////////////////
/***********************************************************************
*  Name        : VehicleDeadReckoningHandler
*  Description :
*  Parameter   :
*  Returns     :
***********************************************************************/
void VehicleDeadReckoningHandler(void)
{
	AVM_DrCnt++;
	if(AVM_DrCnt == 2)
	{
		AVM_DrCnt = 0;
		return;
	}
	
	APSDR_L.YawRate = can_YawRate;
	APSDR_L.RRWheelSpeedRC = get_RRWheelSpeedRC();
	APSDR_L.RLWheelSpeedRC = get_RLWheelSpeedRC();
	APSDR_L.ModeGearDisplaySt = get_gear_status();
	APSDR_L.Saswheelsteerangle= get_SAS_WheelSteerAngle();
	APSDR_step();
	
	VehOriginPos = GetVehiclePositionByOrigin();
	VehRelativePos = VehiclePosition40MsHandler();

	VehiclePositionEstimateErrorHandler(APSDR_W, 20, 3);

	if( (fabs(APSDR_W.DRXPosition)>30000.0f) || (fabs(APSDR_W.DRYPosition)>30000.0f))
	{
		VehiclePositionInitRequest(0x01);
	}

	
	VehOriginPos.x = VehOriginPos.x * 500;
	VehOriginPos.y = VehOriginPos.y * 500;
	VehRelativePos.x = VehRelativePos.x * 500;
	VehRelativePos.y = VehRelativePos.y * 500;
	VehOriginPos.theta = 100 * VehOriginPos.theta;
	VehRelativePos.theta = 100 * VehRelativePos.theta;
	
	M4Msg_Update(E_M4_ABSOLUTE_DELTA_X_U16, VehiclePositionSendToSocUnitExchange(VehOriginPos.x));
	M4Msg_Update(E_M4_ABSOLUTE_DELTA_Y_U16, VehiclePositionSendToSocUnitExchange(VehOriginPos.y));
	M4Msg_Update(E_M4_ABSOLUTE_DELTA_ANGLE_U16, VehiclePositionSendToSocUnitExchange(VehOriginPos.theta));
	M4Msg_Update(E_M4_RELATIVE_DELTA_X_U16, VehiclePositionSendToSocUnitExchange(VehRelativePos.x));
	M4Msg_Update(E_M4_RELATIVE_DELTA_Y_U16, VehiclePositionSendToSocUnitExchange(VehRelativePos.y));
	M4Msg_Update(E_M4_RELATIVE_DELTA_ANGLE_U16, VehiclePositionSendToSocUnitExchange(VehRelativePos.theta));
}


U16 can_FLWheelSpeedRC = 0;
U16 can_FRWheelSpeedRC = 0;
U16 can_RLWheelSpeedRC = 0;
U16 can_RRWheelSpeedRC = 0;
U8  can_ger_status = 0;
U16 can_wheel_angle_value = 0;
U8  Blind_Padding_Status = 0;

U16 get_RLWheelSpeedRC(void)
{
	return can_RLWheelSpeedRC;
}
U16 get_RRWheelSpeedRC(void)
{
	return can_RRWheelSpeedRC;
}
float get_ESC_VehicleSpeed(void)
{
	//return can_receive_sig(ESC_VehicleSpeed);
}
float get_SAS_WheelSteerAngle(void)
{
    /*
    float SAS_NUM = 0;
	SAS_NUM = can_receive_sig(SAS_SteerWheelAngle);
	SAS_NUM *= 0.1;
	return SAS_NUM;
	*/
	return (float)(can_wheel_angle_value);
}
U8 get_gear_status(void)
{
    return can_ger_status;
}
U8 GetBlindPaddingStatus(void)
{
    return Blind_Padding_Status;
}



/***********************************************************************
*  Name        : GetVehiclePositionInSearchingMode
*  Description :
*  Parameter   :
*  Returns     :
***********************************************************************/

APA_VehiclePositionFloat GetVehiclePositionByOrigin(void)
{	
	APA_VehiclePositionFloat VehicleCurrentLocation = {0};
	U8 VehCyclicCnt = 0;
	U8 BlindPaddingReq = GetBlindPaddingStatus();

#ifdef BlindPaddingReq_SW
        BlindPaddingReq = TRUE;
        SinLength = 2*pi*DR_ESC_WheelRadius/DR_ESC_PulseNum;
#endif


	if(BlindPaddingReq == TRUE)
	{
		VehiclePositionInitRequest(FALSE);

		VehicleCurrentLocation.x = -APSDR_W.DRYPosition;
		VehicleCurrentLocation.y = APSDR_W.DRXPosition;
		VehicleCurrentLocation.theta = -APSDR_W.DRTheta;

		if(VehicleCurrentLocation.theta >= 0)
		{
			VehCyclicCnt = (U8)((VehicleCurrentLocation.theta)/360);
			VehicleCurrentLocation.theta = VehicleCurrentLocation.theta - 360*VehCyclicCnt;
		}
		else
		{
			VehCyclicCnt = (U8)((VehicleCurrentLocation.theta*(-1))/360);
			VehicleCurrentLocation.theta = VehicleCurrentLocation.theta + 360*VehCyclicCnt;
		}

		if((VehicleCurrentLocation.theta > 180)&&(VehicleCurrentLocation.theta < 360))
		{
			VehicleCurrentLocation.theta = VehicleCurrentLocation.theta - 360;
		}
		else if((VehicleCurrentLocation.theta < -180)&&(VehicleCurrentLocation.theta > -360))
		{
			VehicleCurrentLocation.theta = VehicleCurrentLocation.theta + 360;
		}
	}
	else
	{
		VehiclePositionInitRequest(TRUE);
	}
	return VehicleCurrentLocation;
}



/***********************************************************************
*  Name        : GetVehiclePosition40MsHandler
*  Description :
*  Parameter   :
*  Returns     :
***********************************************************************/
APA_VehiclePositionFloat VehiclePosition40MsHandler(void)
{
	static APA_VehiclePositionFloat VehRelativePosition;
	static APA_VehiclePositionFloat VehLastPosition;
	U8 BlindPaddingReq = GetBlindPaddingStatus();

#ifdef BlindPaddingReq_SW
    BlindPaddingReq = TRUE;
    SinLength = 2*pi*DR_ESC_WheelRadius/DR_ESC_PulseNum;
#endif

	if(BlindPaddingReq == TRUE)
	{
		VehRelativePosition.x = (-APSDR_W.DRYPosition) - VehLastPosition.x;
		VehRelativePosition.y = APSDR_W.DRXPosition - VehLastPosition.y;
		VehRelativePosition.theta = -APSDR_W.DRTheta - VehLastPosition.theta;
		VehLastPosition.x = -APSDR_W.DRYPosition;
		VehLastPosition.y = APSDR_W.DRXPosition;
		VehLastPosition.theta = -APSDR_W.DRTheta;
	}
	else
	{
		VehRelativePosition.x = 0;
		VehRelativePosition.y = 0;
		VehRelativePosition.theta = 0;
	}

	return VehRelativePosition;

}


/***********************************************************************
*  Name        : VehiclePositionSendToSocUnitExchange
*  Description :
*  Parameter   :
*  Returns     :
***********************************************************************/
U16 VehiclePositionSendToSocUnitExchange(float VehPosition)
{
	U16 VehPositionU16 = 0;
	if(VehPosition >= 0)
	{
		VehPositionU16 = (U16)(VehPosition)&0x7FFF;
	}
	else
	{
		VehPositionU16 = (U16)(VehPosition*(-1))|0x8000;
	}
	return VehPositionU16;
}

/***********************************************************************
*  Name        : VehiclePositionInitRequest
*  Description :
*  Parameter   :
*  Returns     :
***********************************************************************/
void VehiclePositionInitRequest(BOOL InitReq)
{
	if(InitReq == TRUE)
	{
		//APSDR_U.StateFlag = FALSE;
		APSDR_init();
	}
	else
	{
		//APSDR_U.StateFlag = TRUE;
	}
	M4Msg_Update(E_M4_RESET_POSITION_REQ_U8, InitReq);
}


float can_LateralAcce = 0;
float can_YawRate = 0;
//U8  can_LongitSensorState = 3;
float can_LongitAcce = 0;
/****************************************************************************
*  Name			: apscan_YRS_Status
*  Description	: 
*  Parameter	: None
*  Returns		: None
****************************************************************************/
void apscan_YRS_Status(void)
{
	U16 calValue1 = 0;
	U16 calValue2 = 0;
	U16 calValue3 = 0;
	U16 M4_can_LateralAcce = 0;
	U32 M4_can_YawRate = 0;
	U16 M4_can_LongitAcce = 0;
	//calValue1 = can_receive_sig(YRS_LateralAcce);
	//can_LateralAcce = (float)(calValue1*YRSACCEFACTOR - YRSACCEOFFSET);
	can_LateralAcce = 0;
	M4_can_LateralAcce = can_LateralAcce*1000;
	M4Msg_Update(E_M4_LateralAcce_Multiple1K_U16,M4_can_LateralAcce);
	
	calValue2 = can_receive_sig(YawRate);
    if(calValue2&0x0800) //is left or right
	{
		calValue2 = 0x0FFF-calValue2+1; //
        M4Msg_Update(E_M4_YawRateDirection_U8,0x2);
	}
    else 
    {
        M4Msg_Update(E_M4_YawRateDirection_U8,0x1);
    }
	can_YawRate = (float)(calValue2*YAWRATEFACTOR - YSWRATEOFFSET);
	M4_can_YawRate = can_YawRate*1000;
    /*
    if(can_YawRate>0)
	{
		M4Msg_Update(E_M4_YawRateDirection_U8,0x1);
	}
	else
	{
		M4Msg_Update(E_M4_YawRateDirection_U8,0x2);
	}
	*/
	M4Msg_Update(E_M4_YawRate_Multiple1K_U32,M4_can_YawRate);//uidp5358
	
//	can_LongitSensorState = can_receive_sig(YRS_LongitSensorState);
	
	//calValue3 = can_receive_sig(YRS_LongitAcce);
	//can_LongitAcce = (float)(calValue3*YRSACCEFACTOR - YRSACCEOFFSET);
	can_LongitAcce = 0;
	M4_can_LongitAcce = can_LongitAcce*1000;
	M4Msg_Update(E_M4_LongitAcce_Multiple1K_U16,M4_can_LongitAcce);
}


/****************************************************************************
*  Name			: apscan_ESC_WheelSpeedsRC
*  Description	: 
*  Parameter	: None
*  Returns		: None
****************************************************************************/
void apscan_ESC_WheelSpeedsRC(void)
{
	can_FLWheelSpeedRC = can_receive_sig(WheelSpeed_FL);
	M4Msg_Update(E_M4_FLWheelSpeed_PULSE_U16,can_FLWheelSpeedRC);

	can_FRWheelSpeedRC = can_receive_sig(WheelSpeed_FR);
	M4Msg_Update(E_M4_FRwheelSpeed_PULSE_U16,can_FRWheelSpeedRC);
	
	can_RLWheelSpeedRC = can_receive_sig(WheelSpeed_RL);
	M4Msg_Update(E_M4_RLwheelSpeed_PULSE_U16,can_RLWheelSpeedRC);
	
	can_RRWheelSpeedRC = can_receive_sig(WheelSpeed_RR);
	M4Msg_Update(E_M4_RRwheelSpeed_PULSE_U16,can_RRWheelSpeedRC);


}

/***********************************************************************
*  Name        : VehiclePositionEstimateErrorHandler
*  Description :
*  Parameter   :
*  Returns     :
***********************************************************************/
static U8 VehiclePositionEstimateErrorHandler(ExtW_APSDR_T VehPos, float PositionInitLen,U8 EstiCnt)
{
	float VehMovlength = 0;
	static U8 InitStatus;
	static U8 InitCnt;
	VehMovlength = sqrt((VehPos.DRXPosition * VehPos.DRXPosition) + (VehPos.DRYPosition * VehPos.DRYPosition));
	if(InitStatus == TRUE)
	{
		InitCnt++;
		if(InitCnt > EstiCnt)
		{
			InitStatus = FALSE;
			InitCnt = 0;
		}
		else
		{
			VehiclePositionInitRequest(0x02);
		}
	}
	else
	{
		if(VehMovlength > PositionInitLen)
		{
			VehiclePositionInitRequest(0x01);
			InitStatus = TRUE;
		}
		else
		{
			VehiclePositionInitRequest(0x00);
			InitStatus = FALSE;
		}
	}
	return InitStatus;
}


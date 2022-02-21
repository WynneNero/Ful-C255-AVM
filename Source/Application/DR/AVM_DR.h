
#include "Define.h"

#include "APSDR.h"


typedef struct {
	float x;
	float y;
	float theta;
} APA_VehiclePositionFloat;


#define WHEELSPEEDKPHFACTOR 0.05625
#define STEERINGWHEELANGMAX 4600
#define STEERINGWHEELANGMIN (-4600)
#define TARGETACCEFACTOR	0.05
#define TARGETACCEOFFSET	5
#define DOUBLETOCHAROFFSET	0.5
#define YRSACCEFACTOR 0.001
#define YRSACCEOFFSET 2.0
#define YAWRATEFACTOR 0.0625
#define YSWRATEOFFSET 0
#define PASDISTANOFFSET 2.0


void VehicleDeadReckoningHandler(void);
void apscan_ESC_WheelSpeedsRC(void);
U16 get_RLWheelSpeedRC(void);
U16 get_RRWheelSpeedRC(void);
float get_ESC_VehicleSpeed(void);
float get_SAS_WheelSteerAngle(void);
APA_VehiclePositionFloat GetVehiclePositionByOrigin(void);
APA_VehiclePositionFloat VehiclePosition40MsHandler(void);
U16 VehiclePositionSendToSocUnitExchange(float VehPosition);
void apscan_YRS_Status(void);
static U8 VehiclePositionEstimateErrorHandler(ExtW_APSDR_T VehPos, float PositionInitLen,U8 EstiCnt);
extern U8 can_ger_status;
extern U16 can_wheel_angle_value;
U8 get_gear_status(void);
void VehiclePositionInitRequest(BOOL InitReq);
extern U8  Blind_Padding_Status;













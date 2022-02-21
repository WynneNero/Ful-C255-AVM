/* -----------------------------------------------------------------------------
  Filename:    drv_par.h
  Description: Toolversion: 02.03.11.01.70.09.79.00.00.00
               
               Serial Number: CBD1700979
               Customer Info: Huizhou Desay SV Automotive Co., Ltd.
                              Package: CBD_Vector_SLP2
                              Micro: R7F7016213AFP
                              Compiler: Green Hills 2015.1.7
               
               
               Generator Fwk   : GENy 
               Generator Module: GenTool_GenyDriverBase
               
               Configuration   : D:\uida0262\Desktop\tool205\CBD1700979 D00 Rh850 GreenHills FAW C095 AVM.gny
               
               ECU: 
                       TargetSystem: Hw_Rh850Cpu
                       Compiler:     GreenHills
                       Derivates:    F1L
               
               Channel "Channel0":
                       Databasefile: D:\uida0262\Desktop\tool205\ab02_979_C095_CAN1_V0.5_20220105.dbc
                       Bussystem:    CAN
                       Manufacturer: Vector
                       Node:         AVM

 ----------------------------------------------------------------------------- */
/* -----------------------------------------------------------------------------
  C O P Y R I G H T
 -------------------------------------------------------------------------------
  Copyright (c) 2001-2015 by Vector Informatik GmbH. All rights reserved.
 
  This software is copyright protected and proprietary to Vector Informatik 
  GmbH.
  
  Vector Informatik GmbH grants to you only those rights as set out in the 
  license conditions.
  
  All other rights remain with Vector Informatik GmbH.
 -------------------------------------------------------------------------------
 ----------------------------------------------------------------------------- */

#if !defined(__DRV_PAR_H__)
#define __DRV_PAR_H__

/* -----------------------------------------------------------------------------
    &&&~ Signal Structures
 ----------------------------------------------------------------------------- */

typedef struct _c_ABS_1_msgTypeTag
{
  vbittype Checksum_ABS_1 : 8;
  vbittype WheelSpeed_FL_0 : 8;
  vbittype WheelSpeed_FL_1 : 7;
  vbittype unused0 : 1;
  vbittype WheelSpeed_FR_0 : 8;
  vbittype WheelSpeed_FR_1 : 7;
  vbittype unused1 : 1;
  vbittype VehicleSpeed_0 : 8;
  vbittype VehicleSpeed_1 : 7;
  vbittype unused2 : 1;
  vbittype DrivingDirection : 2;
  vbittype unused3 : 2;
  vbittype LiveCounter_ABS_1 : 4;
} _c_ABS_1_msgType;
typedef struct _c_IC_1_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype OdometerValue_0 : 8;
  vbittype OdometerValue_1 : 8;
  vbittype OdometerValue_2 : 8;
  vbittype OdometerValue_3 : 1;
  vbittype HandParkingBrakeSt : 2;
  vbittype unused3 : 5;
} _c_IC_1_msgType;
typedef struct _c_HU_5_msgTypeTag
{
  vbittype Checksum_HU_5 : 8;
  vbittype AVSFunctionReq : 2;
  vbittype AVSViewModeReq : 4;
  vbittype AVSFunctionExitReq : 1;
  vbittype AVSMonitoringVideoModeReq : 1;
  vbittype DynamicPGSReq : 2;
  vbittype MODReq : 2;
  vbittype LanguageSet : 4;
  vbittype SwitchScreenResponseAVS : 2;
  vbittype unused0 : 6;
  vbittype AVSTurnLightFollowupFunctionReq : 2;
  vbittype unused1 : 6;
  vbittype unused2 : 8;
  vbittype AVSViewtypeReq : 2;
  vbittype HU_AVM_RemoteMonitorSharpnessSet : 2;
  vbittype HU_AVM_RemoteMonitoringIFrameReq : 1;
  vbittype HU_RemoteMonitoringSt : 1;
  vbittype unused3 : 2;
  vbittype unused4 : 4;
  vbittype LiveCounter_HU_5 : 4;
} _c_HU_5_msgType;
typedef struct _c_TCU_3_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 8;
  vbittype unused6 : 8;
  vbittype LeverInfo : 4;
  vbittype unused7 : 4;
} _c_TCU_3_msgType;
typedef struct _c_SAS_1_msgTypeTag
{
  vbittype Checksum_SAS_1 : 8;
  vbittype SteeringWAngle_0 : 8;
  vbittype SteeringWAngle_1 : 7;
  vbittype SteeringWAngleSign : 1;
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype SAS_St : 2;
  vbittype unused4 : 2;
  vbittype LiveCounter_SAS_1 : 4;
} _c_SAS_1_msgType;
typedef struct _c_PDC_1_msgTypeTag
{
  vbittype SysSt_PDC : 1;
  vbittype ErrorSt_PDC : 1;
  vbittype RadarSysSt_Front : 1;
  vbittype RadarSysSt_Rear : 1;
  vbittype unused0 : 1;
  vbittype BuzeerCmd_PDC : 3;
  vbittype unused1 : 3;
  vbittype RadarSysSt_FrontSide : 1;
  vbittype RadarSysSt_RearSide : 1;
  vbittype unused2 : 3;
  vbittype ObjectRange_RR : 3;
  vbittype SensorErrorSt_RR : 1;
  vbittype ObjectRange_RMR : 3;
  vbittype SensorErrorSt_RMR : 1;
  vbittype ObjectRange_RML : 3;
  vbittype SensorErrorSt_RML : 1;
  vbittype ObjectRange_RL : 3;
  vbittype SensorErrorSt_RL : 1;
  vbittype ObjectRange_FR : 3;
  vbittype SensorErrorSt_FR : 1;
  vbittype ObjectRange_FMR : 3;
  vbittype SensorErrorSt_FMR : 1;
  vbittype ObjectRange_FML : 3;
  vbittype SensorErrorSt_FML : 1;
  vbittype ObjectRange_FL : 3;
  vbittype SensorErrorSt_FL : 1;
  vbittype unused3 : 5;
  vbittype PDCAutoOnFunctionInd : 1;
  vbittype SwitchScreenRequest_PDC : 2;
} _c_PDC_1_msgType;
typedef struct _c_AVS_1_msgTypeTag
{
  vbittype AVSSt : 1;
  vbittype AVSErrorSt : 1;
  vbittype AVSViewMode : 4;
  vbittype AVSViewtype : 2;
  vbittype AVSCameraErrorSt_Front : 1;
  vbittype AVSCameraErrorSt_Rear : 1;
  vbittype AVSCameraErrorSt_Left : 1;
  vbittype AVSCameraErrorSt_Right : 1;
  vbittype LanguageTypeSt_AVS : 4;
  vbittype DybanicPGSSt_AVS : 1;
  vbittype MODSt_AVS : 1;
  vbittype MODWarning_Front : 1;
  vbittype MODWarning_Rear : 1;
  vbittype AVSTurnLightFollowupFunctionSt : 1;
  vbittype unused0 : 3;
  vbittype SwitchScreenRequest_AVS : 2;
  vbittype BlindSpotFilledFunctionInd : 1;
  vbittype FoundSlotBuzzerTip : 1;
  vbittype unused1 : 4;
  vbittype AVS_SpeechControlFeedback : 5;
  vbittype AVSCameraBlockageSt_Front : 1;
  vbittype AVSCameraBlockageSt_Rear : 1;
  vbittype AVSCameraBlockageSt_Left : 1;
  vbittype AVSCameraBlockageSt_Right : 1;
  vbittype AVS_AbnormalTip : 3;
  vbittype AVS_CalibrationSt : 2;
  vbittype AVS_PDWarning_Front : 1;
  vbittype AVS_PDWarning_Rear : 1;
  vbittype AVS_RemoteMonitoringFeedback : 3;
  vbittype AVS_RemoteSharpnessFeedback : 3;
  vbittype RemoteMonitoringSharpnessSt_AVS : 1;
  vbittype RemoteMonitoringSt_AVS : 1;
  vbittype RemoteMonitoringModeSt_AVS : 1;
  vbittype unused2 : 2;
  vbittype AVS_RemoteViewModeFeedback : 5;
} _c_AVS_1_msgType;
typedef struct _c_ATC_2_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype AmbientTemp : 8;
} _c_ATC_2_msgType;
typedef struct _c_GPS_1_msgTypeTag
{
  vbittype GPSTime_Hour : 5;
  vbittype unused0 : 3;
  vbittype GPSTime_Minute : 6;
  vbittype unused1 : 2;
  vbittype GPSTime_Second : 6;
  vbittype unused2 : 2;
  vbittype GPSTime_Year : 7;
  vbittype unused3 : 1;
  vbittype GPSTime_Month : 4;
  vbittype unused4 : 4;
  vbittype GPSTime_Day : 7;
  vbittype unused5 : 1;
} _c_GPS_1_msgType;
typedef struct _c_PDCU_1_msgTypeTag
{
  vbittype unused0 : 2;
  vbittype DoorSt_FR : 1;
  vbittype unused1 : 5;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 2;
  vbittype MirrorFoldSt_FR : 2;
  vbittype unused6 : 4;
} _c_PDCU_1_msgType;
typedef struct _c_PLG_1_msgTypeTag
{
  vbittype LuggageDoorSt : 1;
  vbittype unused0 : 7;
} _c_PLG_1_msgType;
typedef struct _c_EMS_3_msgTypeTag
{
  vbittype Checksum_EMS_3 : 8;
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 3;
  vbittype BakePedalSt : 2;
  vbittype unused4 : 3;
  vbittype unused5 : 8;
  vbittype unused6 : 8;
  vbittype unused7 : 4;
  vbittype LiveCounter_EMS_3 : 4;
} _c_EMS_3_msgType;
typedef struct _c_HU_Speech_1_msgTypeTag
{
  vbittype Checksum_HU_Speech_1 : 8;
  vbittype unused0 : 6;
  vbittype HU_SpeedReq_AVS : 2;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 8;
  vbittype unused6 : 4;
  vbittype LiveCounter_HU_Speech_1 : 4;
} _c_HU_Speech_1_msgType;
typedef struct _c_ESP_3_msgTypeTag
{
  vbittype Checksum_ESP_3 : 8;
  vbittype YawRate_0 : 8;
  vbittype YawRate_1 : 4;
  vbittype YRSSt : 1;
  vbittype Acceleration_X_0 : 3;
  vbittype Acceleration_X_1 : 8;
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype Acceleration_Y_0 : 8;
  vbittype Acceleration_Y_1 : 3;
  vbittype ErrorSt_YRS : 1;
  vbittype LiveCounter_ESP_3 : 4;
} _c_ESP_3_msgType;
typedef struct _c_ESP_2_msgTypeTag
{
  vbittype Checksum_ESP_2 : 8;
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype WorkingSt_EPB : 2;
  vbittype unused5 : 6;
  vbittype unused6 : 4;
  vbittype LiveCounter_ESP_2 : 4;
} _c_ESP_2_msgType;
typedef struct _c_DDCU_1_msgTypeTag
{
  vbittype unused0 : 2;
  vbittype DoorSt_FL : 1;
  vbittype unused1 : 5;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 2;
  vbittype MirrorFoldSt_FL : 2;
  vbittype unused6 : 4;
} _c_DDCU_1_msgType;
typedef struct _c_BCM1_1_msgTypeTag
{
  vbittype unused0 : 7;
  vbittype LowBeamSt_FL : 1;
  vbittype LowBeamSt_FR : 1;
  vbittype unused1 : 1;
  vbittype HighBeamSt_FL : 1;
  vbittype HighBeamSt_FR : 1;
  vbittype AutoLightMode : 1;
  vbittype unused2 : 3;
  vbittype TurningSt_Left : 1;
  vbittype TurningSt_right : 1;
  vbittype unused3 : 4;
  vbittype HazardWarningSt : 1;
  vbittype unused4 : 1;
} _c_BCM1_1_msgType;
typedef struct _c_ABS_3_msgTypeTag
{
  vbittype Checksum_ABS_3 : 8;
  vbittype WheelPulse_FL : 8;
  vbittype WheelPulse_FR : 8;
  vbittype WheelPulse_RL : 8;
  vbittype WheelPulse_RR : 8;
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 4;
  vbittype LiveCounter_ABS_3 : 4;
} _c_ABS_3_msgType;
typedef struct _c_ABS_2_msgTypeTag
{
  vbittype Checksum_ABS_2 : 8;
  vbittype WheelSpeed_RL_0 : 8;
  vbittype WheelSpeed_RL_1 : 7;
  vbittype unused0 : 1;
  vbittype WheelSpeed_RR_0 : 8;
  vbittype WheelSpeed_RR_1 : 7;
  vbittype unused1 : 1;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 4;
  vbittype LiveCounter_ABS_2 : 4;
} _c_ABS_2_msgType;
typedef struct _c_BCM1_2_msgTypeTag
{
  vbittype unused0 : 4;
  vbittype PowerMode : 4;
} _c_BCM1_2_msgType;
typedef struct _c_AVS_NM_msgTypeTag
{
  vbittype Wakeup_reason : 8;
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype Stay_awake_reason : 8;
  vbittype Extension_information : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
} _c_AVS_NM_msgType;
typedef struct _c_PDC_2_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype SensorBlockageSt_RR : 1;
  vbittype SensorBlockageSt_RMR : 1;
  vbittype SensorBlockageSt_RML : 1;
  vbittype SensorBlockageSt_RL : 1;
  vbittype SensorBlockageSt_FR : 1;
  vbittype SensorBlockageSt_FMR : 1;
  vbittype SensorBlockageSt_FML : 1;
  vbittype SensorBlockageSt_FL : 1;
} _c_PDC_2_msgType;
typedef struct _c_LCDA_1_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype WarningCmd_RCTA_left : 2;
  vbittype unused2 : 2;
  vbittype WarningCmd_RCTA_Right : 2;
  vbittype unused3 : 2;
} _c_LCDA_1_msgType;
typedef struct _c_TBOX_1_msgTypeTag
{
  vbittype Checksum_TBOX_1 : 8;
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype RemoteMonitoringReq : 2;
  vbittype unused5 : 3;
  vbittype RemoteAVSSharpnessReq : 2;
  vbittype unused6 : 1;
  vbittype RemoteAVSViewModeReq : 4;
  vbittype LiveCounter_TBOX_1 : 4;
} _c_TBOX_1_msgType;
typedef struct _c_RRDCU_1_msgTypeTag
{
  vbittype unused0 : 2;
  vbittype DoorSt_RR : 1;
  vbittype unused1 : 5;
} _c_RRDCU_1_msgType;
typedef struct _c_RLDCU_1_msgTypeTag
{
  vbittype unused0 : 2;
  vbittype DoorSt_RL : 1;
  vbittype unused1 : 5;
} _c_RLDCU_1_msgType;
typedef struct _c_MCP_1_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 1;
  vbittype MCP_AVSandFRadarSwitch : 1;
  vbittype unused4 : 6;
} _c_MCP_1_msgType;
typedef struct _c_HU_6_msgTypeTag
{
  vbittype TargetSelectionCenter_X_0 : 8;
  vbittype TargetSelectionCenter_X_1 : 3;
  vbittype TargetSelection_Area : 1;
  vbittype TargetSelectionCenter_Y_0 : 4;
  vbittype TargetSelectionCenter_Y_1 : 7;
  vbittype unused0 : 1;
  vbittype TargetSelectionCenter_Angle_0 : 8;
  vbittype TargetSelectionCenter_Angle_1 : 2;
  vbittype unused1 : 1;
  vbittype TargetSelection_ParkType : 3;
  vbittype TargetSelection_ParkDirection : 2;
  vbittype TargetSelection_LineAngle_0 : 8;
  vbittype TargetSelection_LineAngle_1 : 2;
  vbittype TargetSelection_ConfirmReq : 1;
  vbittype unused2 : 5;
  vbittype ParkOutDirection : 4;
  vbittype unused3 : 4;
} _c_HU_6_msgType;
typedef struct _c_HU_20_msgTypeTag
{
  vbittype ScreenPressPosition_X1_0 : 8;
  vbittype ScreenPressPosition_X1_1 : 4;
  vbittype ScreenPressPosition_Y1_0 : 4;
  vbittype ScreenPressPosition_Y1_1 : 8;
  vbittype ScreenPressPosition_X2_0 : 8;
  vbittype ScreenPressPosition_X2_1 : 4;
  vbittype ScreenPressPosition_Y2_0 : 4;
  vbittype ScreenPressPosition_Y2_1 : 8;
  vbittype ScreenPressType1 : 2;
  vbittype ScreenPressType2 : 2;
  vbittype unused0 : 4;
} _c_HU_20_msgType;
typedef struct _c_HU_18_msgTypeTag
{
  vbittype Checksum_HU_18 : 8;
  vbittype HU_BlindSpotFilledFunctionReq : 2;
  vbittype unused0 : 6;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
  vbittype unused5 : 8;
  vbittype unused6 : 4;
  vbittype LiveCounter_HU_18 : 4;
} _c_HU_18_msgType;
typedef struct _c_HU_14_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype DisplayTheme : 3;
  vbittype unused3 : 5;
} _c_HU_14_msgType;
typedef struct _c_GW_Config_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 4;
  vbittype GW_RemoteVehicleMode : 1;
  vbittype unused2 : 3;
  vbittype GW_OTAMode : 3;
  vbittype unused3 : 5;
} _c_GW_Config_msgType;
typedef struct _c_DMS_2_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype DMS_VehicleModeInfo : 4;
  vbittype unused1 : 4;
} _c_DMS_2_msgType;
typedef struct _c_BCM1_7_msgTypeTag
{
  vbittype RainIntensity : 4;
  vbittype unused0 : 4;
  vbittype Brightness_L : 8;
  vbittype Brightness_R_0 : 8;
  vbittype Brightness_R_1 : 2;
  vbittype unused1 : 6;
} _c_BCM1_7_msgType;
typedef struct _c_BCM1_3_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 4;
  vbittype EngineHoodSt : 1;
  vbittype unused2 : 3;
} _c_BCM1_3_msgType;


/* -----------------------------------------------------------------------------
    &&&~ Signal value names
 ----------------------------------------------------------------------------- */



/* -----------------------------------------------------------------------------
    &&&~ Message Unions
 ----------------------------------------------------------------------------- */

typedef union _c_ABS_1_bufTag
{
  vuint8 _c[8];
  _c_ABS_1_msgType ABS_1;
} _c_ABS_1_buf;
typedef union _c_TxDynamicMsg0_bufTag
{
  vuint8 _c[8];
} _c_TxDynamicMsg0_buf;
typedef union _c_IC_1_bufTag
{
  vuint8 _c[7];
  _c_IC_1_msgType IC_1;
} _c_IC_1_buf;
typedef union _c_HU_5_bufTag
{
  vuint8 _c[8];
  _c_HU_5_msgType HU_5;
} _c_HU_5_buf;
typedef union _c_TCU_3_bufTag
{
  vuint8 _c[8];
  _c_TCU_3_msgType TCU_3;
} _c_TCU_3_buf;
typedef union _c_SAS_1_bufTag
{
  vuint8 _c[8];
  _c_SAS_1_msgType SAS_1;
} _c_SAS_1_buf;
typedef union _c_PDC_1_bufTag
{
  vuint8 _c[7];
  _c_PDC_1_msgType PDC_1;
} _c_PDC_1_buf;
typedef union _c_AVS_1_bufTag
{
  vuint8 _c[8];
  _c_AVS_1_msgType AVS_1;
} _c_AVS_1_buf;
typedef union _c_ATC_2_bufTag
{
  vuint8 _c[4];
  _c_ATC_2_msgType ATC_2;
} _c_ATC_2_buf;
typedef union _c_GPS_1_bufTag
{
  vuint8 _c[6];
  _c_GPS_1_msgType GPS_1;
} _c_GPS_1_buf;
typedef union _c_PDCU_1_bufTag
{
  vuint8 _c[5];
  _c_PDCU_1_msgType PDCU_1;
} _c_PDCU_1_buf;
typedef union _c_PLG_1_bufTag
{
  vuint8 _c[1];
  _c_PLG_1_msgType PLG_1;
} _c_PLG_1_buf;
typedef union _c_EMS_3_bufTag
{
  vuint8 _c[8];
  _c_EMS_3_msgType EMS_3;
} _c_EMS_3_buf;
typedef union _c_HU_Speech_1_bufTag
{
  vuint8 _c[8];
  _c_HU_Speech_1_msgType HU_Speech_1;
} _c_HU_Speech_1_buf;
typedef union _c_ESP_3_bufTag
{
  vuint8 _c[8];
  _c_ESP_3_msgType ESP_3;
} _c_ESP_3_buf;
typedef union _c_ESP_2_bufTag
{
  vuint8 _c[8];
  _c_ESP_2_msgType ESP_2;
} _c_ESP_2_buf;
typedef union _c_DDCU_1_bufTag
{
  vuint8 _c[5];
  _c_DDCU_1_msgType DDCU_1;
} _c_DDCU_1_buf;
typedef union _c_BCM1_1_bufTag
{
  vuint8 _c[3];
  _c_BCM1_1_msgType BCM1_1;
} _c_BCM1_1_buf;
typedef union _c_ABS_3_bufTag
{
  vuint8 _c[8];
  _c_ABS_3_msgType ABS_3;
} _c_ABS_3_buf;
typedef union _c_ABS_2_bufTag
{
  vuint8 _c[8];
  _c_ABS_2_msgType ABS_2;
} _c_ABS_2_buf;
typedef union _c_BCM1_2_bufTag
{
  vuint8 _c[1];
  _c_BCM1_2_msgType BCM1_2;
} _c_BCM1_2_buf;
typedef union _c_AVS_NM_bufTag
{
  vuint8 _c[8];
  _c_AVS_NM_msgType AVS_NM;
} _c_AVS_NM_buf;
typedef union _c_PDC_2_bufTag
{
  vuint8 _c[2];
  _c_PDC_2_msgType PDC_2;
} _c_PDC_2_buf;
typedef union _c_LCDA_1_bufTag
{
  vuint8 _c[3];
  _c_LCDA_1_msgType LCDA_1;
} _c_LCDA_1_buf;
typedef union _c_TBOX_1_bufTag
{
  vuint8 _c[8];
  _c_TBOX_1_msgType TBOX_1;
} _c_TBOX_1_buf;
typedef union _c_RRDCU_1_bufTag
{
  vuint8 _c[1];
  _c_RRDCU_1_msgType RRDCU_1;
} _c_RRDCU_1_buf;
typedef union _c_RLDCU_1_bufTag
{
  vuint8 _c[1];
  _c_RLDCU_1_msgType RLDCU_1;
} _c_RLDCU_1_buf;
typedef union _c_MCP_1_bufTag
{
  vuint8 _c[4];
  _c_MCP_1_msgType MCP_1;
} _c_MCP_1_buf;
typedef union _c_HU_6_bufTag
{
  vuint8 _c[8];
  _c_HU_6_msgType HU_6;
} _c_HU_6_buf;
typedef union _c_HU_20_bufTag
{
  vuint8 _c[7];
  _c_HU_20_msgType HU_20;
} _c_HU_20_buf;
typedef union _c_HU_18_bufTag
{
  vuint8 _c[8];
  _c_HU_18_msgType HU_18;
} _c_HU_18_buf;
typedef union _c_HU_14_bufTag
{
  vuint8 _c[4];
  _c_HU_14_msgType HU_14;
} _c_HU_14_buf;
typedef union _c_GW_Config_bufTag
{
  vuint8 _c[3];
  _c_GW_Config_msgType GW_Config;
} _c_GW_Config_buf;
typedef union _c_DMS_2_bufTag
{
  vuint8 _c[2];
  _c_DMS_2_msgType DMS_2;
} _c_DMS_2_buf;
typedef union _c_BCM1_7_bufTag
{
  vuint8 _c[4];
  _c_BCM1_7_msgType BCM1_7;
} _c_BCM1_7_buf;
typedef union _c_BCM1_3_bufTag
{
  vuint8 _c[2];
  _c_BCM1_3_msgType BCM1_3;
} _c_BCM1_3_buf;


/* -----------------------------------------------------------------------------
    &&&~ Message Buffers
 ----------------------------------------------------------------------------- */

/* RAM CATEGORY 2 START */
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_ABS_1_buf V_MEMRAM2 ABS_1;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TxDynamicMsg0_buf V_MEMRAM2 TxDynamicMsg0;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_IC_1_buf V_MEMRAM2 IC_1;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HU_5_buf V_MEMRAM2 HU_5;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TCU_3_buf V_MEMRAM2 TCU_3;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_SAS_1_buf V_MEMRAM2 SAS_1;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_PDC_1_buf V_MEMRAM2 PDC_1;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_AVS_1_buf V_MEMRAM2 AVS_1;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_ATC_2_buf V_MEMRAM2 ATC_2;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_GPS_1_buf V_MEMRAM2 GPS_1;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_PDCU_1_buf V_MEMRAM2 PDCU_1;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_PLG_1_buf V_MEMRAM2 PLG_1;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_EMS_3_buf V_MEMRAM2 EMS_3;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HU_Speech_1_buf V_MEMRAM2 HU_Speech_1;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_ESP_3_buf V_MEMRAM2 ESP_3;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_ESP_2_buf V_MEMRAM2 ESP_2;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_DDCU_1_buf V_MEMRAM2 DDCU_1;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_BCM1_1_buf V_MEMRAM2 BCM1_1;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_ABS_3_buf V_MEMRAM2 ABS_3;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_ABS_2_buf V_MEMRAM2 ABS_2;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_BCM1_2_buf V_MEMRAM2 BCM1_2;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_AVS_NM_buf V_MEMRAM2 AVS_NM;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_PDC_2_buf V_MEMRAM2 PDC_2;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_LCDA_1_buf V_MEMRAM2 LCDA_1;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_TBOX_1_buf V_MEMRAM2 TBOX_1;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_RRDCU_1_buf V_MEMRAM2 RRDCU_1;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_RLDCU_1_buf V_MEMRAM2 RLDCU_1;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_MCP_1_buf V_MEMRAM2 MCP_1;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HU_6_buf V_MEMRAM2 HU_6;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HU_20_buf V_MEMRAM2 HU_20;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HU_18_buf V_MEMRAM2 HU_18;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_HU_14_buf V_MEMRAM2 HU_14;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_GW_Config_buf V_MEMRAM2 GW_Config;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_DMS_2_buf V_MEMRAM2 DMS_2;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_BCM1_7_buf V_MEMRAM2 BCM1_7;
/* RAM CATEGORY 2 END */

/* RAM CATEGORY 2 START */
V_MEMRAM0 extern  V_MEMRAM1 _c_BCM1_3_buf V_MEMRAM2 BCM1_3;
/* RAM CATEGORY 2 END */






/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 400925945
      //#error "The magic number of the generated file <D:\uida0262\Desktop\tool205\gen979_1_5\drv_par.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 400925945
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __DRV_PAR_H__ */

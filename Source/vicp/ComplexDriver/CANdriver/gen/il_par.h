/* -----------------------------------------------------------------------------
  Filename:    il_par.h
  Description: Toolversion: 02.03.11.01.70.09.79.00.00.00
               
               Serial Number: CBD1700979
               Customer Info: Huizhou Desay SV Automotive Co., Ltd.
                              Package: CBD_Vector_SLP2
                              Micro: R7F7016213AFP
                              Compiler: Green Hills 2015.1.7
               
               
               Generator Fwk   : GENy 
               Generator Module: Il_Vector
               
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

#if !defined(__IL_PAR_H__)
#define __IL_PAR_H__

/* -----------------------------------------------------------------------------
    &&&~ Typedefs
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_TX)
typedef vuint8 IltTxCounter;
#endif

#if defined(IL_ENABLE_TX)
typedef vuint8 IltTxUpdateCounter;
#endif

#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_TIMEOUT)
typedef vuint8 IltTxTimeoutCounter;
#endif

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_TIMEOUT)
typedef vuint8 IltRxTimeoutCounter;
#endif

#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_SECURE_EVENT)
typedef vuint8 IltTxRepetitionCounter;
#endif



/* -----------------------------------------------------------------------------
    &&&~ Message Handles
 ----------------------------------------------------------------------------- */

#define IlRxMsgHndHU_20                      0
#define IlRxMsgHndGW_Config                  1
#define IlRxMsgHndGPS_1                      2
#define IlRxMsgHndTBOX_1                     3
#define IlRxMsgHndHU_14                      4
#define IlRxMsgHndIC_1                       5
#define IlRxMsgHndHU_Speech_1                6
#define IlRxMsgHndHU_6                       7
#define IlRxMsgHndHU_5                       8
#define IlRxMsgHndHU_18                      9
#define IlRxMsgHndLCDA_1                     10
#define IlRxMsgHndPDC_2                      11
#define IlRxMsgHndPDC_1                      12
#define IlRxMsgHndRRDCU_1                    13
#define IlRxMsgHndRLDCU_1                    14
#define IlRxMsgHndPDCU_1                     15
#define IlRxMsgHndDDCU_1                     16
#define IlRxMsgHndPLG_1                      17
#define IlRxMsgHndBCM1_7                     18
#define IlRxMsgHndBCM1_3                     19
#define IlRxMsgHndBCM1_2                     20
#define IlRxMsgHndBCM1_1                     21
#define IlRxMsgHndATC_2                      22
#define IlRxMsgHndDMS_2                      23
#define IlRxMsgHndMCP_1                      24
#define IlRxMsgHndESP_3                      25
#define IlRxMsgHndESP_2                      26
#define IlRxMsgHndABS_3                      27
#define IlRxMsgHndSAS_1                      28
#define IlRxMsgHndABS_2                      29
#define IlRxMsgHndABS_1                      30
#define IlRxMsgHndTCU_3                      31
#define IlRxMsgHndEMS_3                      32
#define IlTxMsgHndAVS_1                      0


/* -----------------------------------------------------------------------------
    &&&~ Signal Handles
 ----------------------------------------------------------------------------- */

#define IlRxSigHndScreenPressPosition_X1     IlRxMsgHndHU_20
#define IlRxSigHndScreenPressPosition_Y1     IlRxMsgHndHU_20
#define IlRxSigHndScreenPressPosition_X2     IlRxMsgHndHU_20
#define IlRxSigHndScreenPressPosition_Y2     IlRxMsgHndHU_20
#define IlRxSigHndScreenPressType1           IlRxMsgHndHU_20
#define IlRxSigHndScreenPressType2           IlRxMsgHndHU_20
#define IlRxSigHndGW_RemoteVehicleMode       IlRxMsgHndGW_Config
#define IlRxSigHndGW_OTAMode                 IlRxMsgHndGW_Config
#define IlRxSigHndGPSTime_Hour               IlRxMsgHndGPS_1
#define IlRxSigHndGPSTime_Minute             IlRxMsgHndGPS_1
#define IlRxSigHndGPSTime_Second             IlRxMsgHndGPS_1
#define IlRxSigHndGPSTime_Year               IlRxMsgHndGPS_1
#define IlRxSigHndGPSTime_Month              IlRxMsgHndGPS_1
#define IlRxSigHndGPSTime_Day                IlRxMsgHndGPS_1
#define IlRxSigHndChecksum_TBOX_1            IlRxMsgHndTBOX_1
#define IlRxSigHndRemoteMonitoringReq        IlRxMsgHndTBOX_1
#define IlRxSigHndRemoteAVSSharpnessReq      IlRxMsgHndTBOX_1
#define IlRxSigHndRemoteAVSViewModeReq       IlRxMsgHndTBOX_1
#define IlRxSigHndLiveCounter_TBOX_1         IlRxMsgHndTBOX_1
#define IlRxSigHndDisplayTheme               IlRxMsgHndHU_14
#define IlRxSigHndOdometerValue              IlRxMsgHndIC_1
#define IlRxSigHndHandParkingBrakeSt         IlRxMsgHndIC_1
#define IlRxSigHndChecksum_HU_Speech_1       IlRxMsgHndHU_Speech_1
#define IlRxSigHndHU_SpeedReq_AVS            IlRxMsgHndHU_Speech_1
#define IlRxSigHndLiveCounter_HU_Speech_1    IlRxMsgHndHU_Speech_1
#define IlRxSigHndTargetSelectionCenter_X    IlRxMsgHndHU_6
#define IlRxSigHndTargetSelectionCenter_Y    IlRxMsgHndHU_6
#define IlRxSigHndTargetSelectionCenter_Angle IlRxMsgHndHU_6
#define IlRxSigHndTargetSelection_Area       IlRxMsgHndHU_6
#define IlRxSigHndTargetSelection_ParkType   IlRxMsgHndHU_6
#define IlRxSigHndTargetSelection_ParkDirection IlRxMsgHndHU_6
#define IlRxSigHndTargetSelection_LineAngle  IlRxMsgHndHU_6
#define IlRxSigHndTargetSelection_ConfirmReq IlRxMsgHndHU_6
#define IlRxSigHndParkOutDirection           IlRxMsgHndHU_6
#define IlRxSigHndChecksum_HU_5              IlRxMsgHndHU_5
#define IlRxSigHndAVSFunctionReq             IlRxMsgHndHU_5
#define IlRxSigHndAVSViewModeReq             IlRxMsgHndHU_5
#define IlRxSigHndAVSFunctionExitReq         IlRxMsgHndHU_5
#define IlRxSigHndAVSMonitoringVideoModeReq  IlRxMsgHndHU_5
#define IlRxSigHndDynamicPGSReq              IlRxMsgHndHU_5
#define IlRxSigHndMODReq                     IlRxMsgHndHU_5
#define IlRxSigHndLanguageSet                IlRxMsgHndHU_5
#define IlRxSigHndSwitchScreenResponseAVS    IlRxMsgHndHU_5
#define IlRxSigHndAVSTurnLightFollowupFunctionReq IlRxMsgHndHU_5
#define IlRxSigHndAVSViewtypeReq             IlRxMsgHndHU_5
#define IlRxSigHndHU_AVM_RemoteMonitorSharpnessSet IlRxMsgHndHU_5
#define IlRxSigHndHU_AVM_RemoteMonitoringIFrameReq IlRxMsgHndHU_5
#define IlRxSigHndHU_RemoteMonitoringSt      IlRxMsgHndHU_5
#define IlRxSigHndLiveCounter_HU_5           IlRxMsgHndHU_5
#define IlRxSigHndChecksum_HU_18             IlRxMsgHndHU_18
#define IlRxSigHndHU_BlindSpotFilledFunctionReq IlRxMsgHndHU_18
#define IlRxSigHndLiveCounter_HU_18          IlRxMsgHndHU_18
#define IlRxSigHndWarningCmd_RCTA_left       IlRxMsgHndLCDA_1
#define IlRxSigHndWarningCmd_RCTA_Right      IlRxMsgHndLCDA_1
#define IlRxSigHndSensorBlockageSt_RR        IlRxMsgHndPDC_2
#define IlRxSigHndSensorBlockageSt_RMR       IlRxMsgHndPDC_2
#define IlRxSigHndSensorBlockageSt_RML       IlRxMsgHndPDC_2
#define IlRxSigHndSensorBlockageSt_RL        IlRxMsgHndPDC_2
#define IlRxSigHndSensorBlockageSt_FR        IlRxMsgHndPDC_2
#define IlRxSigHndSensorBlockageSt_FMR       IlRxMsgHndPDC_2
#define IlRxSigHndSensorBlockageSt_FML       IlRxMsgHndPDC_2
#define IlRxSigHndSensorBlockageSt_FL        IlRxMsgHndPDC_2
#define IlRxSigHndSysSt_PDC                  IlRxMsgHndPDC_1
#define IlRxSigHndErrorSt_PDC                IlRxMsgHndPDC_1
#define IlRxSigHndRadarSysSt_Front           IlRxMsgHndPDC_1
#define IlRxSigHndRadarSysSt_Rear            IlRxMsgHndPDC_1
#define IlRxSigHndBuzeerCmd_PDC              IlRxMsgHndPDC_1
#define IlRxSigHndRadarSysSt_FrontSide       IlRxMsgHndPDC_1
#define IlRxSigHndRadarSysSt_RearSide        IlRxMsgHndPDC_1
#define IlRxSigHndObjectRange_RR             IlRxMsgHndPDC_1
#define IlRxSigHndSensorErrorSt_RR           IlRxMsgHndPDC_1
#define IlRxSigHndObjectRange_RMR            IlRxMsgHndPDC_1
#define IlRxSigHndSensorErrorSt_RMR          IlRxMsgHndPDC_1
#define IlRxSigHndObjectRange_RML            IlRxMsgHndPDC_1
#define IlRxSigHndSensorErrorSt_RML          IlRxMsgHndPDC_1
#define IlRxSigHndObjectRange_RL             IlRxMsgHndPDC_1
#define IlRxSigHndSensorErrorSt_RL           IlRxMsgHndPDC_1
#define IlRxSigHndObjectRange_FR             IlRxMsgHndPDC_1
#define IlRxSigHndSensorErrorSt_FR           IlRxMsgHndPDC_1
#define IlRxSigHndObjectRange_FMR            IlRxMsgHndPDC_1
#define IlRxSigHndSensorErrorSt_FMR          IlRxMsgHndPDC_1
#define IlRxSigHndObjectRange_FML            IlRxMsgHndPDC_1
#define IlRxSigHndSensorErrorSt_FML          IlRxMsgHndPDC_1
#define IlRxSigHndObjectRange_FL             IlRxMsgHndPDC_1
#define IlRxSigHndSensorErrorSt_FL           IlRxMsgHndPDC_1
#define IlRxSigHndPDCAutoOnFunctionInd       IlRxMsgHndPDC_1
#define IlRxSigHndSwitchScreenRequest_PDC    IlRxMsgHndPDC_1
#define IlRxSigHndDoorSt_RR                  IlRxMsgHndRRDCU_1
#define IlRxSigHndDoorSt_RL                  IlRxMsgHndRLDCU_1
#define IlRxSigHndDoorSt_FR                  IlRxMsgHndPDCU_1
#define IlRxSigHndMirrorFoldSt_FR            IlRxMsgHndPDCU_1
#define IlRxSigHndDoorSt_FL                  IlRxMsgHndDDCU_1
#define IlRxSigHndMirrorFoldSt_FL            IlRxMsgHndDDCU_1
#define IlRxSigHndLuggageDoorSt              IlRxMsgHndPLG_1
#define IlRxSigHndRainIntensity              IlRxMsgHndBCM1_7
#define IlRxSigHndBrightness_L               IlRxMsgHndBCM1_7
#define IlRxSigHndBrightness_R               IlRxMsgHndBCM1_7
#define IlRxSigHndEngineHoodSt               IlRxMsgHndBCM1_3
#define IlRxSigHndPowerMode                  IlRxMsgHndBCM1_2
#define IlRxSigHndLowBeamSt_FL               IlRxMsgHndBCM1_1
#define IlRxSigHndLowBeamSt_FR               IlRxMsgHndBCM1_1
#define IlRxSigHndHighBeamSt_FL              IlRxMsgHndBCM1_1
#define IlRxSigHndHighBeamSt_FR              IlRxMsgHndBCM1_1
#define IlRxSigHndAutoLightMode              IlRxMsgHndBCM1_1
#define IlRxSigHndTurningSt_Left             IlRxMsgHndBCM1_1
#define IlRxSigHndTurningSt_right            IlRxMsgHndBCM1_1
#define IlRxSigHndHazardWarningSt            IlRxMsgHndBCM1_1
#define IlRxSigHndAmbientTemp                IlRxMsgHndATC_2
#define IlRxSigHndDMS_VehicleModeInfo        IlRxMsgHndDMS_2
#define IlRxSigHndMCP_AVSandFRadarSwitch     IlRxMsgHndMCP_1
#define IlRxSigHndChecksum_ESP_3             IlRxMsgHndESP_3
#define IlRxSigHndYawRate                    IlRxMsgHndESP_3
#define IlRxSigHndYRSSt                      IlRxMsgHndESP_3
#define IlRxSigHndAcceleration_X             IlRxMsgHndESP_3
#define IlRxSigHndAcceleration_Y             IlRxMsgHndESP_3
#define IlRxSigHndErrorSt_YRS                IlRxMsgHndESP_3
#define IlRxSigHndLiveCounter_ESP_3          IlRxMsgHndESP_3
#define IlRxSigHndChecksum_ESP_2             IlRxMsgHndESP_2
#define IlRxSigHndWorkingSt_EPB              IlRxMsgHndESP_2
#define IlRxSigHndLiveCounter_ESP_2          IlRxMsgHndESP_2
#define IlRxSigHndChecksum_ABS_3             IlRxMsgHndABS_3
#define IlRxSigHndWheelPulse_FL              IlRxMsgHndABS_3
#define IlRxSigHndWheelPulse_FR              IlRxMsgHndABS_3
#define IlRxSigHndWheelPulse_RL              IlRxMsgHndABS_3
#define IlRxSigHndWheelPulse_RR              IlRxMsgHndABS_3
#define IlRxSigHndLiveCounter_ABS_3          IlRxMsgHndABS_3
#define IlRxSigHndChecksum_SAS_1             IlRxMsgHndSAS_1
#define IlRxSigHndSteeringWAngle             IlRxMsgHndSAS_1
#define IlRxSigHndSteeringWAngleSign         IlRxMsgHndSAS_1
#define IlRxSigHndSAS_St                     IlRxMsgHndSAS_1
#define IlRxSigHndLiveCounter_SAS_1          IlRxMsgHndSAS_1
#define IlRxSigHndChecksum_ABS_2             IlRxMsgHndABS_2
#define IlRxSigHndWheelSpeed_RL              IlRxMsgHndABS_2
#define IlRxSigHndWheelSpeed_RR              IlRxMsgHndABS_2
#define IlRxSigHndLiveCounter_ABS_2          IlRxMsgHndABS_2
#define IlRxSigHndChecksum_ABS_1             IlRxMsgHndABS_1
#define IlRxSigHndWheelSpeed_FL              IlRxMsgHndABS_1
#define IlRxSigHndWheelSpeed_FR              IlRxMsgHndABS_1
#define IlRxSigHndVehicleSpeed               IlRxMsgHndABS_1
#define IlRxSigHndDrivingDirection           IlRxMsgHndABS_1
#define IlRxSigHndLiveCounter_ABS_1          IlRxMsgHndABS_1
#define IlRxSigHndLeverInfo                  IlRxMsgHndTCU_3
#define IlRxSigHndChecksum_EMS_3             IlRxMsgHndEMS_3
#define IlRxSigHndBakePedalSt                IlRxMsgHndEMS_3
#define IlRxSigHndLiveCounter_EMS_3          IlRxMsgHndEMS_3
#define IlTxSigHndAVSSt                      IlTxMsgHndAVS_1
#define IlTxSigHndAVSErrorSt                 IlTxMsgHndAVS_1
#define IlTxSigHndAVSViewMode                IlTxMsgHndAVS_1
#define IlTxSigHndAVSViewtype                IlTxMsgHndAVS_1
#define IlTxSigHndAVSCameraErrorSt_Front     IlTxMsgHndAVS_1
#define IlTxSigHndAVSCameraErrorSt_Rear      IlTxMsgHndAVS_1
#define IlTxSigHndAVSCameraErrorSt_Left      IlTxMsgHndAVS_1
#define IlTxSigHndAVSCameraErrorSt_Right     IlTxMsgHndAVS_1
#define IlTxSigHndLanguageTypeSt_AVS         IlTxMsgHndAVS_1
#define IlTxSigHndDybanicPGSSt_AVS           IlTxMsgHndAVS_1
#define IlTxSigHndMODSt_AVS                  IlTxMsgHndAVS_1
#define IlTxSigHndMODWarning_Front           IlTxMsgHndAVS_1
#define IlTxSigHndMODWarning_Rear            IlTxMsgHndAVS_1
#define IlTxSigHndAVSTurnLightFollowupFunctionSt IlTxMsgHndAVS_1
#define IlTxSigHndSwitchScreenRequest_AVS    IlTxMsgHndAVS_1
#define IlTxSigHndBlindSpotFilledFunctionInd IlTxMsgHndAVS_1
#define IlTxSigHndFoundSlotBuzzerTip         IlTxMsgHndAVS_1
#define IlTxSigHndAVS_SpeechControlFeedback  IlTxMsgHndAVS_1
#define IlTxSigHndAVSCameraBlockageSt_Front  IlTxMsgHndAVS_1
#define IlTxSigHndAVSCameraBlockageSt_Rear   IlTxMsgHndAVS_1
#define IlTxSigHndAVSCameraBlockageSt_Left   IlTxMsgHndAVS_1
#define IlTxSigHndAVSCameraBlockageSt_Right  IlTxMsgHndAVS_1
#define IlTxSigHndAVS_AbnormalTip            IlTxMsgHndAVS_1
#define IlTxSigHndAVS_CalibrationSt          IlTxMsgHndAVS_1
#define IlTxSigHndAVS_PDWarning_Front        IlTxMsgHndAVS_1
#define IlTxSigHndAVS_PDWarning_Rear         IlTxMsgHndAVS_1
#define IlTxSigHndAVS_RemoteMonitoringFeedback IlTxMsgHndAVS_1
#define IlTxSigHndAVS_RemoteSharpnessFeedback IlTxMsgHndAVS_1
#define IlTxSigHndRemoteMonitoringSharpnessSt_AVS IlTxMsgHndAVS_1
#define IlTxSigHndRemoteMonitoringSt_AVS     IlTxMsgHndAVS_1
#define IlTxSigHndRemoteMonitoringModeSt_AVS IlTxMsgHndAVS_1
#define IlTxSigHndAVS_RemoteViewModeFeedback IlTxMsgHndAVS_1


/* -----------------------------------------------------------------------------
    &&&~ Critical section macros for signals
 ----------------------------------------------------------------------------- */

#define IlEnterCriticalAVSSt()               CanGlobalInterruptDisable()
#define IlLeaveCriticalAVSSt()               CanGlobalInterruptRestore()
#define IlEnterCriticalAVSErrorSt()          CanGlobalInterruptDisable()
#define IlLeaveCriticalAVSErrorSt()          CanGlobalInterruptRestore()
#define IlEnterCriticalAVSViewMode()         CanGlobalInterruptDisable()
#define IlLeaveCriticalAVSViewMode()         CanGlobalInterruptRestore()
#define IlEnterCriticalAVSViewtype()         CanGlobalInterruptDisable()
#define IlLeaveCriticalAVSViewtype()         CanGlobalInterruptRestore()
#define IlEnterCriticalAVSCameraErrorSt_Front() CanGlobalInterruptDisable()
#define IlLeaveCriticalAVSCameraErrorSt_Front() CanGlobalInterruptRestore()
#define IlEnterCriticalAVSCameraErrorSt_Rear() CanGlobalInterruptDisable()
#define IlLeaveCriticalAVSCameraErrorSt_Rear() CanGlobalInterruptRestore()
#define IlEnterCriticalAVSCameraErrorSt_Left() CanGlobalInterruptDisable()
#define IlLeaveCriticalAVSCameraErrorSt_Left() CanGlobalInterruptRestore()
#define IlEnterCriticalAVSCameraErrorSt_Right() CanGlobalInterruptDisable()
#define IlLeaveCriticalAVSCameraErrorSt_Right() CanGlobalInterruptRestore()
#define IlEnterCriticalLanguageTypeSt_AVS()  CanGlobalInterruptDisable()
#define IlLeaveCriticalLanguageTypeSt_AVS()  CanGlobalInterruptRestore()
#define IlEnterCriticalDybanicPGSSt_AVS()    CanGlobalInterruptDisable()
#define IlLeaveCriticalDybanicPGSSt_AVS()    CanGlobalInterruptRestore()
#define IlEnterCriticalMODSt_AVS()           CanGlobalInterruptDisable()
#define IlLeaveCriticalMODSt_AVS()           CanGlobalInterruptRestore()
#define IlEnterCriticalMODWarning_Front()    CanGlobalInterruptDisable()
#define IlLeaveCriticalMODWarning_Front()    CanGlobalInterruptRestore()
#define IlEnterCriticalMODWarning_Rear()     CanGlobalInterruptDisable()
#define IlLeaveCriticalMODWarning_Rear()     CanGlobalInterruptRestore()
#define IlEnterCriticalAVSTurnLightFollowupFunctionSt() CanGlobalInterruptDisable()
#define IlLeaveCriticalAVSTurnLightFollowupFunctionSt() CanGlobalInterruptRestore()
#define IlEnterCriticalSwitchScreenRequest_AVS() CanGlobalInterruptDisable()
#define IlLeaveCriticalSwitchScreenRequest_AVS() CanGlobalInterruptRestore()
#define IlEnterCriticalBlindSpotFilledFunctionInd() CanGlobalInterruptDisable()
#define IlLeaveCriticalBlindSpotFilledFunctionInd() CanGlobalInterruptRestore()
#define IlEnterCriticalFoundSlotBuzzerTip()  CanGlobalInterruptDisable()
#define IlLeaveCriticalFoundSlotBuzzerTip()  CanGlobalInterruptRestore()
#define IlEnterCriticalAVS_SpeechControlFeedback() CanGlobalInterruptDisable()
#define IlLeaveCriticalAVS_SpeechControlFeedback() CanGlobalInterruptRestore()
#define IlEnterCriticalAVSCameraBlockageSt_Front() CanGlobalInterruptDisable()
#define IlLeaveCriticalAVSCameraBlockageSt_Front() CanGlobalInterruptRestore()
#define IlEnterCriticalAVSCameraBlockageSt_Rear() CanGlobalInterruptDisable()
#define IlLeaveCriticalAVSCameraBlockageSt_Rear() CanGlobalInterruptRestore()
#define IlEnterCriticalAVSCameraBlockageSt_Left() CanGlobalInterruptDisable()
#define IlLeaveCriticalAVSCameraBlockageSt_Left() CanGlobalInterruptRestore()
#define IlEnterCriticalAVSCameraBlockageSt_Right() CanGlobalInterruptDisable()
#define IlLeaveCriticalAVSCameraBlockageSt_Right() CanGlobalInterruptRestore()
#define IlEnterCriticalAVS_AbnormalTip()     CanGlobalInterruptDisable()
#define IlLeaveCriticalAVS_AbnormalTip()     CanGlobalInterruptRestore()
#define IlEnterCriticalAVS_CalibrationSt()   CanGlobalInterruptDisable()
#define IlLeaveCriticalAVS_CalibrationSt()   CanGlobalInterruptRestore()
#define IlEnterCriticalAVS_PDWarning_Front() CanGlobalInterruptDisable()
#define IlLeaveCriticalAVS_PDWarning_Front() CanGlobalInterruptRestore()
#define IlEnterCriticalAVS_PDWarning_Rear()  CanGlobalInterruptDisable()
#define IlLeaveCriticalAVS_PDWarning_Rear()  CanGlobalInterruptRestore()
#define IlEnterCriticalAVS_RemoteMonitoringFeedback() CanGlobalInterruptDisable()
#define IlLeaveCriticalAVS_RemoteMonitoringFeedback() CanGlobalInterruptRestore()
#define IlEnterCriticalAVS_RemoteSharpnessFeedback() CanGlobalInterruptDisable()
#define IlLeaveCriticalAVS_RemoteSharpnessFeedback() CanGlobalInterruptRestore()
#define IlEnterCriticalRemoteMonitoringSharpnessSt_AVS() CanGlobalInterruptDisable()
#define IlLeaveCriticalRemoteMonitoringSharpnessSt_AVS() CanGlobalInterruptRestore()
#define IlEnterCriticalRemoteMonitoringSt_AVS() CanGlobalInterruptDisable()
#define IlLeaveCriticalRemoteMonitoringSt_AVS() CanGlobalInterruptRestore()
#define IlEnterCriticalRemoteMonitoringModeSt_AVS() CanGlobalInterruptDisable()
#define IlLeaveCriticalRemoteMonitoringModeSt_AVS() CanGlobalInterruptRestore()
#define IlEnterCriticalAVS_RemoteViewModeFeedback() CanGlobalInterruptDisable()
#define IlLeaveCriticalAVS_RemoteViewModeFeedback() CanGlobalInterruptRestore()
#define IlEnterCriticalScreenPressPosition_X1() CanGlobalInterruptDisable()
#define IlLeaveCriticalScreenPressPosition_X1() CanGlobalInterruptRestore()
#define IlEnterCriticalScreenPressPosition_Y1() CanGlobalInterruptDisable()
#define IlLeaveCriticalScreenPressPosition_Y1() CanGlobalInterruptRestore()
#define IlEnterCriticalScreenPressPosition_X2() CanGlobalInterruptDisable()
#define IlLeaveCriticalScreenPressPosition_X2() CanGlobalInterruptRestore()
#define IlEnterCriticalScreenPressPosition_Y2() CanGlobalInterruptDisable()
#define IlLeaveCriticalScreenPressPosition_Y2() CanGlobalInterruptRestore()
#define IlEnterCriticalScreenPressType1()    CanGlobalInterruptDisable()
#define IlLeaveCriticalScreenPressType1()    CanGlobalInterruptRestore()
#define IlEnterCriticalScreenPressType2()    CanGlobalInterruptDisable()
#define IlLeaveCriticalScreenPressType2()    CanGlobalInterruptRestore()
#define IlEnterCriticalGW_RemoteVehicleMode() CanGlobalInterruptDisable()
#define IlLeaveCriticalGW_RemoteVehicleMode() CanGlobalInterruptRestore()
#define IlEnterCriticalGW_OTAMode()          CanGlobalInterruptDisable()
#define IlLeaveCriticalGW_OTAMode()          CanGlobalInterruptRestore()
#define IlEnterCriticalGPSTime_Hour()        CanGlobalInterruptDisable()
#define IlLeaveCriticalGPSTime_Hour()        CanGlobalInterruptRestore()
#define IlEnterCriticalGPSTime_Minute()      CanGlobalInterruptDisable()
#define IlLeaveCriticalGPSTime_Minute()      CanGlobalInterruptRestore()
#define IlEnterCriticalGPSTime_Second()      CanGlobalInterruptDisable()
#define IlLeaveCriticalGPSTime_Second()      CanGlobalInterruptRestore()
#define IlEnterCriticalGPSTime_Year()        CanGlobalInterruptDisable()
#define IlLeaveCriticalGPSTime_Year()        CanGlobalInterruptRestore()
#define IlEnterCriticalGPSTime_Month()       CanGlobalInterruptDisable()
#define IlLeaveCriticalGPSTime_Month()       CanGlobalInterruptRestore()
#define IlEnterCriticalGPSTime_Day()         CanGlobalInterruptDisable()
#define IlLeaveCriticalGPSTime_Day()         CanGlobalInterruptRestore()
#define IlEnterCriticalChecksum_TBOX_1()     CanGlobalInterruptDisable()
#define IlLeaveCriticalChecksum_TBOX_1()     CanGlobalInterruptRestore()
#define IlEnterCriticalRemoteMonitoringReq() CanGlobalInterruptDisable()
#define IlLeaveCriticalRemoteMonitoringReq() CanGlobalInterruptRestore()
#define IlEnterCriticalRemoteAVSSharpnessReq() CanGlobalInterruptDisable()
#define IlLeaveCriticalRemoteAVSSharpnessReq() CanGlobalInterruptRestore()
#define IlEnterCriticalRemoteAVSViewModeReq() CanGlobalInterruptDisable()
#define IlLeaveCriticalRemoteAVSViewModeReq() CanGlobalInterruptRestore()
#define IlEnterCriticalLiveCounter_TBOX_1()  CanGlobalInterruptDisable()
#define IlLeaveCriticalLiveCounter_TBOX_1()  CanGlobalInterruptRestore()
#define IlEnterCriticalDisplayTheme()        CanGlobalInterruptDisable()
#define IlLeaveCriticalDisplayTheme()        CanGlobalInterruptRestore()
#define IlEnterCriticalOdometerValue()       CanGlobalInterruptDisable()
#define IlLeaveCriticalOdometerValue()       CanGlobalInterruptRestore()
#define IlEnterCriticalHandParkingBrakeSt()  CanGlobalInterruptDisable()
#define IlLeaveCriticalHandParkingBrakeSt()  CanGlobalInterruptRestore()
#define IlEnterCriticalChecksum_HU_Speech_1() CanGlobalInterruptDisable()
#define IlLeaveCriticalChecksum_HU_Speech_1() CanGlobalInterruptRestore()
#define IlEnterCriticalHU_SpeedReq_AVS()     CanGlobalInterruptDisable()
#define IlLeaveCriticalHU_SpeedReq_AVS()     CanGlobalInterruptRestore()
#define IlEnterCriticalLiveCounter_HU_Speech_1() CanGlobalInterruptDisable()
#define IlLeaveCriticalLiveCounter_HU_Speech_1() CanGlobalInterruptRestore()
#define IlEnterCriticalTargetSelectionCenter_X() CanGlobalInterruptDisable()
#define IlLeaveCriticalTargetSelectionCenter_X() CanGlobalInterruptRestore()
#define IlEnterCriticalTargetSelectionCenter_Y() CanGlobalInterruptDisable()
#define IlLeaveCriticalTargetSelectionCenter_Y() CanGlobalInterruptRestore()
#define IlEnterCriticalTargetSelectionCenter_Angle() CanGlobalInterruptDisable()
#define IlLeaveCriticalTargetSelectionCenter_Angle() CanGlobalInterruptRestore()
#define IlEnterCriticalTargetSelection_Area() CanGlobalInterruptDisable()
#define IlLeaveCriticalTargetSelection_Area() CanGlobalInterruptRestore()
#define IlEnterCriticalTargetSelection_ParkType() CanGlobalInterruptDisable()
#define IlLeaveCriticalTargetSelection_ParkType() CanGlobalInterruptRestore()
#define IlEnterCriticalTargetSelection_ParkDirection() CanGlobalInterruptDisable()
#define IlLeaveCriticalTargetSelection_ParkDirection() CanGlobalInterruptRestore()
#define IlEnterCriticalTargetSelection_LineAngle() CanGlobalInterruptDisable()
#define IlLeaveCriticalTargetSelection_LineAngle() CanGlobalInterruptRestore()
#define IlEnterCriticalTargetSelection_ConfirmReq() CanGlobalInterruptDisable()
#define IlLeaveCriticalTargetSelection_ConfirmReq() CanGlobalInterruptRestore()
#define IlEnterCriticalParkOutDirection()    CanGlobalInterruptDisable()
#define IlLeaveCriticalParkOutDirection()    CanGlobalInterruptRestore()
#define IlEnterCriticalChecksum_HU_5()       CanGlobalInterruptDisable()
#define IlLeaveCriticalChecksum_HU_5()       CanGlobalInterruptRestore()
#define IlEnterCriticalAVSFunctionReq()      CanGlobalInterruptDisable()
#define IlLeaveCriticalAVSFunctionReq()      CanGlobalInterruptRestore()
#define IlEnterCriticalAVSViewModeReq()      CanGlobalInterruptDisable()
#define IlLeaveCriticalAVSViewModeReq()      CanGlobalInterruptRestore()
#define IlEnterCriticalAVSFunctionExitReq()  CanGlobalInterruptDisable()
#define IlLeaveCriticalAVSFunctionExitReq()  CanGlobalInterruptRestore()
#define IlEnterCriticalAVSMonitoringVideoModeReq() CanGlobalInterruptDisable()
#define IlLeaveCriticalAVSMonitoringVideoModeReq() CanGlobalInterruptRestore()
#define IlEnterCriticalDynamicPGSReq()       CanGlobalInterruptDisable()
#define IlLeaveCriticalDynamicPGSReq()       CanGlobalInterruptRestore()
#define IlEnterCriticalMODReq()              CanGlobalInterruptDisable()
#define IlLeaveCriticalMODReq()              CanGlobalInterruptRestore()
#define IlEnterCriticalLanguageSet()         CanGlobalInterruptDisable()
#define IlLeaveCriticalLanguageSet()         CanGlobalInterruptRestore()
#define IlEnterCriticalSwitchScreenResponseAVS() CanGlobalInterruptDisable()
#define IlLeaveCriticalSwitchScreenResponseAVS() CanGlobalInterruptRestore()
#define IlEnterCriticalAVSTurnLightFollowupFunctionReq() CanGlobalInterruptDisable()
#define IlLeaveCriticalAVSTurnLightFollowupFunctionReq() CanGlobalInterruptRestore()
#define IlEnterCriticalAVSViewtypeReq()      CanGlobalInterruptDisable()
#define IlLeaveCriticalAVSViewtypeReq()      CanGlobalInterruptRestore()
#define IlEnterCriticalHU_AVM_RemoteMonitorSharpnessSet() CanGlobalInterruptDisable()
#define IlLeaveCriticalHU_AVM_RemoteMonitorSharpnessSet() CanGlobalInterruptRestore()
#define IlEnterCriticalHU_AVM_RemoteMonitoringIFrameReq() CanGlobalInterruptDisable()
#define IlLeaveCriticalHU_AVM_RemoteMonitoringIFrameReq() CanGlobalInterruptRestore()
#define IlEnterCriticalHU_RemoteMonitoringSt() CanGlobalInterruptDisable()
#define IlLeaveCriticalHU_RemoteMonitoringSt() CanGlobalInterruptRestore()
#define IlEnterCriticalLiveCounter_HU_5()    CanGlobalInterruptDisable()
#define IlLeaveCriticalLiveCounter_HU_5()    CanGlobalInterruptRestore()
#define IlEnterCriticalChecksum_HU_18()      CanGlobalInterruptDisable()
#define IlLeaveCriticalChecksum_HU_18()      CanGlobalInterruptRestore()
#define IlEnterCriticalHU_BlindSpotFilledFunctionReq() CanGlobalInterruptDisable()
#define IlLeaveCriticalHU_BlindSpotFilledFunctionReq() CanGlobalInterruptRestore()
#define IlEnterCriticalLiveCounter_HU_18()   CanGlobalInterruptDisable()
#define IlLeaveCriticalLiveCounter_HU_18()   CanGlobalInterruptRestore()
#define IlEnterCriticalWarningCmd_RCTA_left() CanGlobalInterruptDisable()
#define IlLeaveCriticalWarningCmd_RCTA_left() CanGlobalInterruptRestore()
#define IlEnterCriticalWarningCmd_RCTA_Right() CanGlobalInterruptDisable()
#define IlLeaveCriticalWarningCmd_RCTA_Right() CanGlobalInterruptRestore()
#define IlEnterCriticalSensorBlockageSt_RR() CanGlobalInterruptDisable()
#define IlLeaveCriticalSensorBlockageSt_RR() CanGlobalInterruptRestore()
#define IlEnterCriticalSensorBlockageSt_RMR() CanGlobalInterruptDisable()
#define IlLeaveCriticalSensorBlockageSt_RMR() CanGlobalInterruptRestore()
#define IlEnterCriticalSensorBlockageSt_RML() CanGlobalInterruptDisable()
#define IlLeaveCriticalSensorBlockageSt_RML() CanGlobalInterruptRestore()
#define IlEnterCriticalSensorBlockageSt_RL() CanGlobalInterruptDisable()
#define IlLeaveCriticalSensorBlockageSt_RL() CanGlobalInterruptRestore()
#define IlEnterCriticalSensorBlockageSt_FR() CanGlobalInterruptDisable()
#define IlLeaveCriticalSensorBlockageSt_FR() CanGlobalInterruptRestore()
#define IlEnterCriticalSensorBlockageSt_FMR() CanGlobalInterruptDisable()
#define IlLeaveCriticalSensorBlockageSt_FMR() CanGlobalInterruptRestore()
#define IlEnterCriticalSensorBlockageSt_FML() CanGlobalInterruptDisable()
#define IlLeaveCriticalSensorBlockageSt_FML() CanGlobalInterruptRestore()
#define IlEnterCriticalSensorBlockageSt_FL() CanGlobalInterruptDisable()
#define IlLeaveCriticalSensorBlockageSt_FL() CanGlobalInterruptRestore()
#define IlEnterCriticalSysSt_PDC()           CanGlobalInterruptDisable()
#define IlLeaveCriticalSysSt_PDC()           CanGlobalInterruptRestore()
#define IlEnterCriticalErrorSt_PDC()         CanGlobalInterruptDisable()
#define IlLeaveCriticalErrorSt_PDC()         CanGlobalInterruptRestore()
#define IlEnterCriticalRadarSysSt_Front()    CanGlobalInterruptDisable()
#define IlLeaveCriticalRadarSysSt_Front()    CanGlobalInterruptRestore()
#define IlEnterCriticalRadarSysSt_Rear()     CanGlobalInterruptDisable()
#define IlLeaveCriticalRadarSysSt_Rear()     CanGlobalInterruptRestore()
#define IlEnterCriticalBuzeerCmd_PDC()       CanGlobalInterruptDisable()
#define IlLeaveCriticalBuzeerCmd_PDC()       CanGlobalInterruptRestore()
#define IlEnterCriticalRadarSysSt_FrontSide() CanGlobalInterruptDisable()
#define IlLeaveCriticalRadarSysSt_FrontSide() CanGlobalInterruptRestore()
#define IlEnterCriticalRadarSysSt_RearSide() CanGlobalInterruptDisable()
#define IlLeaveCriticalRadarSysSt_RearSide() CanGlobalInterruptRestore()
#define IlEnterCriticalObjectRange_RR()      CanGlobalInterruptDisable()
#define IlLeaveCriticalObjectRange_RR()      CanGlobalInterruptRestore()
#define IlEnterCriticalSensorErrorSt_RR()    CanGlobalInterruptDisable()
#define IlLeaveCriticalSensorErrorSt_RR()    CanGlobalInterruptRestore()
#define IlEnterCriticalObjectRange_RMR()     CanGlobalInterruptDisable()
#define IlLeaveCriticalObjectRange_RMR()     CanGlobalInterruptRestore()
#define IlEnterCriticalSensorErrorSt_RMR()   CanGlobalInterruptDisable()
#define IlLeaveCriticalSensorErrorSt_RMR()   CanGlobalInterruptRestore()
#define IlEnterCriticalObjectRange_RML()     CanGlobalInterruptDisable()
#define IlLeaveCriticalObjectRange_RML()     CanGlobalInterruptRestore()
#define IlEnterCriticalSensorErrorSt_RML()   CanGlobalInterruptDisable()
#define IlLeaveCriticalSensorErrorSt_RML()   CanGlobalInterruptRestore()
#define IlEnterCriticalObjectRange_RL()      CanGlobalInterruptDisable()
#define IlLeaveCriticalObjectRange_RL()      CanGlobalInterruptRestore()
#define IlEnterCriticalSensorErrorSt_RL()    CanGlobalInterruptDisable()
#define IlLeaveCriticalSensorErrorSt_RL()    CanGlobalInterruptRestore()
#define IlEnterCriticalObjectRange_FR()      CanGlobalInterruptDisable()
#define IlLeaveCriticalObjectRange_FR()      CanGlobalInterruptRestore()
#define IlEnterCriticalSensorErrorSt_FR()    CanGlobalInterruptDisable()
#define IlLeaveCriticalSensorErrorSt_FR()    CanGlobalInterruptRestore()
#define IlEnterCriticalObjectRange_FMR()     CanGlobalInterruptDisable()
#define IlLeaveCriticalObjectRange_FMR()     CanGlobalInterruptRestore()
#define IlEnterCriticalSensorErrorSt_FMR()   CanGlobalInterruptDisable()
#define IlLeaveCriticalSensorErrorSt_FMR()   CanGlobalInterruptRestore()
#define IlEnterCriticalObjectRange_FML()     CanGlobalInterruptDisable()
#define IlLeaveCriticalObjectRange_FML()     CanGlobalInterruptRestore()
#define IlEnterCriticalSensorErrorSt_FML()   CanGlobalInterruptDisable()
#define IlLeaveCriticalSensorErrorSt_FML()   CanGlobalInterruptRestore()
#define IlEnterCriticalObjectRange_FL()      CanGlobalInterruptDisable()
#define IlLeaveCriticalObjectRange_FL()      CanGlobalInterruptRestore()
#define IlEnterCriticalSensorErrorSt_FL()    CanGlobalInterruptDisable()
#define IlLeaveCriticalSensorErrorSt_FL()    CanGlobalInterruptRestore()
#define IlEnterCriticalPDCAutoOnFunctionInd() CanGlobalInterruptDisable()
#define IlLeaveCriticalPDCAutoOnFunctionInd() CanGlobalInterruptRestore()
#define IlEnterCriticalSwitchScreenRequest_PDC() CanGlobalInterruptDisable()
#define IlLeaveCriticalSwitchScreenRequest_PDC() CanGlobalInterruptRestore()
#define IlEnterCriticalDoorSt_RR()           CanGlobalInterruptDisable()
#define IlLeaveCriticalDoorSt_RR()           CanGlobalInterruptRestore()
#define IlEnterCriticalDoorSt_RL()           CanGlobalInterruptDisable()
#define IlLeaveCriticalDoorSt_RL()           CanGlobalInterruptRestore()
#define IlEnterCriticalDoorSt_FR()           CanGlobalInterruptDisable()
#define IlLeaveCriticalDoorSt_FR()           CanGlobalInterruptRestore()
#define IlEnterCriticalMirrorFoldSt_FR()     CanGlobalInterruptDisable()
#define IlLeaveCriticalMirrorFoldSt_FR()     CanGlobalInterruptRestore()
#define IlEnterCriticalDoorSt_FL()           CanGlobalInterruptDisable()
#define IlLeaveCriticalDoorSt_FL()           CanGlobalInterruptRestore()
#define IlEnterCriticalMirrorFoldSt_FL()     CanGlobalInterruptDisable()
#define IlLeaveCriticalMirrorFoldSt_FL()     CanGlobalInterruptRestore()
#define IlEnterCriticalLuggageDoorSt()       CanGlobalInterruptDisable()
#define IlLeaveCriticalLuggageDoorSt()       CanGlobalInterruptRestore()
#define IlEnterCriticalRainIntensity()       CanGlobalInterruptDisable()
#define IlLeaveCriticalRainIntensity()       CanGlobalInterruptRestore()
#define IlEnterCriticalBrightness_L()        CanGlobalInterruptDisable()
#define IlLeaveCriticalBrightness_L()        CanGlobalInterruptRestore()
#define IlEnterCriticalBrightness_R()        CanGlobalInterruptDisable()
#define IlLeaveCriticalBrightness_R()        CanGlobalInterruptRestore()
#define IlEnterCriticalEngineHoodSt()        CanGlobalInterruptDisable()
#define IlLeaveCriticalEngineHoodSt()        CanGlobalInterruptRestore()
#define IlEnterCriticalPowerMode()           CanGlobalInterruptDisable()
#define IlLeaveCriticalPowerMode()           CanGlobalInterruptRestore()
#define IlEnterCriticalLowBeamSt_FL()        CanGlobalInterruptDisable()
#define IlLeaveCriticalLowBeamSt_FL()        CanGlobalInterruptRestore()
#define IlEnterCriticalLowBeamSt_FR()        CanGlobalInterruptDisable()
#define IlLeaveCriticalLowBeamSt_FR()        CanGlobalInterruptRestore()
#define IlEnterCriticalHighBeamSt_FL()       CanGlobalInterruptDisable()
#define IlLeaveCriticalHighBeamSt_FL()       CanGlobalInterruptRestore()
#define IlEnterCriticalHighBeamSt_FR()       CanGlobalInterruptDisable()
#define IlLeaveCriticalHighBeamSt_FR()       CanGlobalInterruptRestore()
#define IlEnterCriticalAutoLightMode()       CanGlobalInterruptDisable()
#define IlLeaveCriticalAutoLightMode()       CanGlobalInterruptRestore()
#define IlEnterCriticalTurningSt_Left()      CanGlobalInterruptDisable()
#define IlLeaveCriticalTurningSt_Left()      CanGlobalInterruptRestore()
#define IlEnterCriticalTurningSt_right()     CanGlobalInterruptDisable()
#define IlLeaveCriticalTurningSt_right()     CanGlobalInterruptRestore()
#define IlEnterCriticalHazardWarningSt()     CanGlobalInterruptDisable()
#define IlLeaveCriticalHazardWarningSt()     CanGlobalInterruptRestore()
#define IlEnterCriticalAmbientTemp()         CanGlobalInterruptDisable()
#define IlLeaveCriticalAmbientTemp()         CanGlobalInterruptRestore()
#define IlEnterCriticalDMS_VehicleModeInfo() CanGlobalInterruptDisable()
#define IlLeaveCriticalDMS_VehicleModeInfo() CanGlobalInterruptRestore()
#define IlEnterCriticalMCP_AVSandFRadarSwitch() CanGlobalInterruptDisable()
#define IlLeaveCriticalMCP_AVSandFRadarSwitch() CanGlobalInterruptRestore()
#define IlEnterCriticalChecksum_ESP_3()      CanGlobalInterruptDisable()
#define IlLeaveCriticalChecksum_ESP_3()      CanGlobalInterruptRestore()
#define IlEnterCriticalYawRate()             CanGlobalInterruptDisable()
#define IlLeaveCriticalYawRate()             CanGlobalInterruptRestore()
#define IlEnterCriticalYRSSt()               CanGlobalInterruptDisable()
#define IlLeaveCriticalYRSSt()               CanGlobalInterruptRestore()
#define IlEnterCriticalAcceleration_X()      CanGlobalInterruptDisable()
#define IlLeaveCriticalAcceleration_X()      CanGlobalInterruptRestore()
#define IlEnterCriticalAcceleration_Y()      CanGlobalInterruptDisable()
#define IlLeaveCriticalAcceleration_Y()      CanGlobalInterruptRestore()
#define IlEnterCriticalErrorSt_YRS()         CanGlobalInterruptDisable()
#define IlLeaveCriticalErrorSt_YRS()         CanGlobalInterruptRestore()
#define IlEnterCriticalLiveCounter_ESP_3()   CanGlobalInterruptDisable()
#define IlLeaveCriticalLiveCounter_ESP_3()   CanGlobalInterruptRestore()
#define IlEnterCriticalChecksum_ESP_2()      CanGlobalInterruptDisable()
#define IlLeaveCriticalChecksum_ESP_2()      CanGlobalInterruptRestore()
#define IlEnterCriticalWorkingSt_EPB()       CanGlobalInterruptDisable()
#define IlLeaveCriticalWorkingSt_EPB()       CanGlobalInterruptRestore()
#define IlEnterCriticalLiveCounter_ESP_2()   CanGlobalInterruptDisable()
#define IlLeaveCriticalLiveCounter_ESP_2()   CanGlobalInterruptRestore()
#define IlEnterCriticalChecksum_ABS_3()      CanGlobalInterruptDisable()
#define IlLeaveCriticalChecksum_ABS_3()      CanGlobalInterruptRestore()
#define IlEnterCriticalWheelPulse_FL()       CanGlobalInterruptDisable()
#define IlLeaveCriticalWheelPulse_FL()       CanGlobalInterruptRestore()
#define IlEnterCriticalWheelPulse_FR()       CanGlobalInterruptDisable()
#define IlLeaveCriticalWheelPulse_FR()       CanGlobalInterruptRestore()
#define IlEnterCriticalWheelPulse_RL()       CanGlobalInterruptDisable()
#define IlLeaveCriticalWheelPulse_RL()       CanGlobalInterruptRestore()
#define IlEnterCriticalWheelPulse_RR()       CanGlobalInterruptDisable()
#define IlLeaveCriticalWheelPulse_RR()       CanGlobalInterruptRestore()
#define IlEnterCriticalLiveCounter_ABS_3()   CanGlobalInterruptDisable()
#define IlLeaveCriticalLiveCounter_ABS_3()   CanGlobalInterruptRestore()
#define IlEnterCriticalChecksum_SAS_1()      CanGlobalInterruptDisable()
#define IlLeaveCriticalChecksum_SAS_1()      CanGlobalInterruptRestore()
#define IlEnterCriticalSteeringWAngle()      CanGlobalInterruptDisable()
#define IlLeaveCriticalSteeringWAngle()      CanGlobalInterruptRestore()
#define IlEnterCriticalSteeringWAngleSign()  CanGlobalInterruptDisable()
#define IlLeaveCriticalSteeringWAngleSign()  CanGlobalInterruptRestore()
#define IlEnterCriticalSAS_St()              CanGlobalInterruptDisable()
#define IlLeaveCriticalSAS_St()              CanGlobalInterruptRestore()
#define IlEnterCriticalLiveCounter_SAS_1()   CanGlobalInterruptDisable()
#define IlLeaveCriticalLiveCounter_SAS_1()   CanGlobalInterruptRestore()
#define IlEnterCriticalChecksum_ABS_2()      CanGlobalInterruptDisable()
#define IlLeaveCriticalChecksum_ABS_2()      CanGlobalInterruptRestore()
#define IlEnterCriticalWheelSpeed_RL()       CanGlobalInterruptDisable()
#define IlLeaveCriticalWheelSpeed_RL()       CanGlobalInterruptRestore()
#define IlEnterCriticalWheelSpeed_RR()       CanGlobalInterruptDisable()
#define IlLeaveCriticalWheelSpeed_RR()       CanGlobalInterruptRestore()
#define IlEnterCriticalLiveCounter_ABS_2()   CanGlobalInterruptDisable()
#define IlLeaveCriticalLiveCounter_ABS_2()   CanGlobalInterruptRestore()
#define IlEnterCriticalChecksum_ABS_1()      CanGlobalInterruptDisable()
#define IlLeaveCriticalChecksum_ABS_1()      CanGlobalInterruptRestore()
#define IlEnterCriticalWheelSpeed_FL()       CanGlobalInterruptDisable()
#define IlLeaveCriticalWheelSpeed_FL()       CanGlobalInterruptRestore()
#define IlEnterCriticalWheelSpeed_FR()       CanGlobalInterruptDisable()
#define IlLeaveCriticalWheelSpeed_FR()       CanGlobalInterruptRestore()
#define IlEnterCriticalVehicleSpeed()        CanGlobalInterruptDisable()
#define IlLeaveCriticalVehicleSpeed()        CanGlobalInterruptRestore()
#define IlEnterCriticalDrivingDirection()    CanGlobalInterruptDisable()
#define IlLeaveCriticalDrivingDirection()    CanGlobalInterruptRestore()
#define IlEnterCriticalLiveCounter_ABS_1()   CanGlobalInterruptDisable()
#define IlLeaveCriticalLiveCounter_ABS_1()   CanGlobalInterruptRestore()
#define IlEnterCriticalLeverInfo()           CanGlobalInterruptDisable()
#define IlLeaveCriticalLeverInfo()           CanGlobalInterruptRestore()
#define IlEnterCriticalChecksum_EMS_3()      CanGlobalInterruptDisable()
#define IlLeaveCriticalChecksum_EMS_3()      CanGlobalInterruptRestore()
#define IlEnterCriticalBakePedalSt()         CanGlobalInterruptDisable()
#define IlLeaveCriticalBakePedalSt()         CanGlobalInterruptRestore()
#define IlEnterCriticalLiveCounter_EMS_3()   CanGlobalInterruptDisable()
#define IlLeaveCriticalLiveCounter_EMS_3()   CanGlobalInterruptRestore()


/* -----------------------------------------------------------------------------
    &&&~ Access to RxTimeout flags
 ----------------------------------------------------------------------------- */

#define IlGetLeverInfoRxTimeout()            (((vuint8) (ilRxTimeoutFlags[0] & (vuint8) 0x01)) != (vuint8) 0x00)
#define IlSetLeverInfoRxTimeout()            (ilRxTimeoutFlags[0] |= (vuint8) 0x01)
#define IlClrLeverInfoRxTimeout()            (ilRxTimeoutFlags[0] &= (vuint8) (0xFF & (vuint8) 0xFE))


/* -----------------------------------------------------------------------------
    &&&~ Declaration Confirmation Functions
 ----------------------------------------------------------------------------- */

/* Application signal confirmation callback functions */


/* -----------------------------------------------------------------------------
    &&&~ Declaration Indication Functions
 ----------------------------------------------------------------------------- */

/* Application signal indication callback functions */


/* -----------------------------------------------------------------------------
    &&&~ Declaration Rx Timeout Indication Functions
 ----------------------------------------------------------------------------- */

extern void ApplLeverInfoRxSigTimeout(void);


/* -----------------------------------------------------------------------------
    &&&~ Declaration User Timeout Functions
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_TIMEOUT)
#endif



/* -----------------------------------------------------------------------------
    &&&~ Get Rx Signal Access for signals smaller or equal 8bit
 ----------------------------------------------------------------------------- */

/* Handle:    4,Name:               ScreenPressType1,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxScreenPressType1()            (HU_20.HU_20.ScreenPressType1)
#endif

/* Handle:    5,Name:               ScreenPressType2,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxScreenPressType2()            (HU_20.HU_20.ScreenPressType2)
#endif

/* Handle:    6,Name:           GW_RemoteVehicleMode,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxGW_RemoteVehicleMode()        (GW_Config.GW_Config.GW_RemoteVehicleMode)
#endif

/* Handle:    7,Name:                     GW_OTAMode,Size:  3,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxGW_OTAMode()                  (GW_Config.GW_Config.GW_OTAMode)
#endif

/* Handle:    8,Name:                   GPSTime_Hour,Size:  5,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxGPSTime_Hour()                (GPS_1.GPS_1.GPSTime_Hour)
#endif

/* Handle:    9,Name:                 GPSTime_Minute,Size:  6,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxGPSTime_Minute()              (GPS_1.GPS_1.GPSTime_Minute)
#endif

/* Handle:   10,Name:                 GPSTime_Second,Size:  6,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxGPSTime_Second()              (GPS_1.GPS_1.GPSTime_Second)
#endif

/* Handle:   11,Name:                   GPSTime_Year,Size:  7,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxGPSTime_Year()                (GPS_1.GPS_1.GPSTime_Year)
#endif

/* Handle:   12,Name:                  GPSTime_Month,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxGPSTime_Month()               (GPS_1.GPS_1.GPSTime_Month)
#endif

/* Handle:   13,Name:                    GPSTime_Day,Size:  7,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxGPSTime_Day()                 (GPS_1.GPS_1.GPSTime_Day)
#endif

/* Handle:   14,Name:                Checksum_TBOX_1,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxChecksum_TBOX_1()             (TBOX_1.TBOX_1.Checksum_TBOX_1)
#endif

/* Handle:   15,Name:            RemoteMonitoringReq,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxRemoteMonitoringReq()         (TBOX_1.TBOX_1.RemoteMonitoringReq)
#endif

/* Handle:   16,Name:          RemoteAVSSharpnessReq,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxRemoteAVSSharpnessReq()       (TBOX_1.TBOX_1.RemoteAVSSharpnessReq)
#endif

/* Handle:   17,Name:           RemoteAVSViewModeReq,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxRemoteAVSViewModeReq()        (TBOX_1.TBOX_1.RemoteAVSViewModeReq)
#endif

/* Handle:   18,Name:             LiveCounter_TBOX_1,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxLiveCounter_TBOX_1()          (TBOX_1.TBOX_1.LiveCounter_TBOX_1)
#endif

/* Handle:   19,Name:                   DisplayTheme,Size:  3,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxDisplayTheme()                (HU_14.HU_14.DisplayTheme)
#endif

/* Handle:   21,Name:             HandParkingBrakeSt,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxHandParkingBrakeSt()          (IC_1.IC_1.HandParkingBrakeSt)
#endif

/* Handle:   22,Name:           Checksum_HU_Speech_1,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxChecksum_HU_Speech_1()        (HU_Speech_1.HU_Speech_1.Checksum_HU_Speech_1)
#endif

/* Handle:   23,Name:                HU_SpeedReq_AVS,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxHU_SpeedReq_AVS()             (HU_Speech_1.HU_Speech_1.HU_SpeedReq_AVS)
#endif

/* Handle:   24,Name:        LiveCounter_HU_Speech_1,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxLiveCounter_HU_Speech_1()     (HU_Speech_1.HU_Speech_1.LiveCounter_HU_Speech_1)
#endif

/* Handle:   28,Name:           TargetSelection_Area,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxTargetSelection_Area()        (HU_6.HU_6.TargetSelection_Area)
#endif

/* Handle:   29,Name:       TargetSelection_ParkType,Size:  3,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxTargetSelection_ParkType()    (HU_6.HU_6.TargetSelection_ParkType)
#endif

/* Handle:   30,Name:  TargetSelection_ParkDirection,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxTargetSelection_ParkDirection() (HU_6.HU_6.TargetSelection_ParkDirection)
#endif

/* Handle:   32,Name:     TargetSelection_ConfirmReq,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxTargetSelection_ConfirmReq()  (HU_6.HU_6.TargetSelection_ConfirmReq)
#endif

/* Handle:   33,Name:               ParkOutDirection,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxParkOutDirection()            (HU_6.HU_6.ParkOutDirection)
#endif

/* Handle:   34,Name:                  Checksum_HU_5,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxChecksum_HU_5()               (HU_5.HU_5.Checksum_HU_5)
#endif

/* Handle:   35,Name:                 AVSFunctionReq,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxAVSFunctionReq()              (HU_5.HU_5.AVSFunctionReq)
#endif

/* Handle:   36,Name:                 AVSViewModeReq,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxAVSViewModeReq()              (HU_5.HU_5.AVSViewModeReq)
#endif

/* Handle:   37,Name:             AVSFunctionExitReq,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxAVSFunctionExitReq()          (HU_5.HU_5.AVSFunctionExitReq)
#endif

/* Handle:   38,Name:      AVSMonitoringVideoModeReq,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxAVSMonitoringVideoModeReq()   (HU_5.HU_5.AVSMonitoringVideoModeReq)
#endif

/* Handle:   39,Name:                  DynamicPGSReq,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxDynamicPGSReq()               (HU_5.HU_5.DynamicPGSReq)
#endif

/* Handle:   40,Name:                         MODReq,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxMODReq()                      (HU_5.HU_5.MODReq)
#endif

/* Handle:   41,Name:                    LanguageSet,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxLanguageSet()                 (HU_5.HU_5.LanguageSet)
#endif

/* Handle:   42,Name:        SwitchScreenResponseAVS,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxSwitchScreenResponseAVS()     (HU_5.HU_5.SwitchScreenResponseAVS)
#endif

/* Handle:   43,Name: AVSTurnLightFollowupFunctionReq,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxAVSTurnLightFollowupFunctionReq() (HU_5.HU_5.AVSTurnLightFollowupFunctionReq)
#endif

/* Handle:   44,Name:                 AVSViewtypeReq,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxAVSViewtypeReq()              (HU_5.HU_5.AVSViewtypeReq)
#endif

/* Handle:   45,Name: HU_AVM_RemoteMonitorSharpnessSet,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxHU_AVM_RemoteMonitorSharpnessSet() (HU_5.HU_5.HU_AVM_RemoteMonitorSharpnessSet)
#endif

/* Handle:   46,Name: HU_AVM_RemoteMonitoringIFrameReq,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxHU_AVM_RemoteMonitoringIFrameReq() (HU_5.HU_5.HU_AVM_RemoteMonitoringIFrameReq)
#endif

/* Handle:   47,Name:          HU_RemoteMonitoringSt,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxHU_RemoteMonitoringSt()       (HU_5.HU_5.HU_RemoteMonitoringSt)
#endif

/* Handle:   48,Name:               LiveCounter_HU_5,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxLiveCounter_HU_5()            (HU_5.HU_5.LiveCounter_HU_5)
#endif

/* Handle:   49,Name:                 Checksum_HU_18,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxChecksum_HU_18()              (HU_18.HU_18.Checksum_HU_18)
#endif

/* Handle:   50,Name:  HU_BlindSpotFilledFunctionReq,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxHU_BlindSpotFilledFunctionReq() (HU_18.HU_18.HU_BlindSpotFilledFunctionReq)
#endif

/* Handle:   51,Name:              LiveCounter_HU_18,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxLiveCounter_HU_18()           (HU_18.HU_18.LiveCounter_HU_18)
#endif

/* Handle:   52,Name:           WarningCmd_RCTA_left,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxWarningCmd_RCTA_left()        (LCDA_1.LCDA_1.WarningCmd_RCTA_left)
#endif

/* Handle:   53,Name:          WarningCmd_RCTA_Right,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxWarningCmd_RCTA_Right()       (LCDA_1.LCDA_1.WarningCmd_RCTA_Right)
#endif

/* Handle:   54,Name:            SensorBlockageSt_RR,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxSensorBlockageSt_RR()         (PDC_2.PDC_2.SensorBlockageSt_RR)
#endif

/* Handle:   55,Name:           SensorBlockageSt_RMR,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxSensorBlockageSt_RMR()        (PDC_2.PDC_2.SensorBlockageSt_RMR)
#endif

/* Handle:   56,Name:           SensorBlockageSt_RML,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxSensorBlockageSt_RML()        (PDC_2.PDC_2.SensorBlockageSt_RML)
#endif

/* Handle:   57,Name:            SensorBlockageSt_RL,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxSensorBlockageSt_RL()         (PDC_2.PDC_2.SensorBlockageSt_RL)
#endif

/* Handle:   58,Name:            SensorBlockageSt_FR,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxSensorBlockageSt_FR()         (PDC_2.PDC_2.SensorBlockageSt_FR)
#endif

/* Handle:   59,Name:           SensorBlockageSt_FMR,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxSensorBlockageSt_FMR()        (PDC_2.PDC_2.SensorBlockageSt_FMR)
#endif

/* Handle:   60,Name:           SensorBlockageSt_FML,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxSensorBlockageSt_FML()        (PDC_2.PDC_2.SensorBlockageSt_FML)
#endif

/* Handle:   61,Name:            SensorBlockageSt_FL,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxSensorBlockageSt_FL()         (PDC_2.PDC_2.SensorBlockageSt_FL)
#endif

/* Handle:   62,Name:                      SysSt_PDC,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxSysSt_PDC()                   (PDC_1.PDC_1.SysSt_PDC)
#endif

/* Handle:   63,Name:                    ErrorSt_PDC,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxErrorSt_PDC()                 (PDC_1.PDC_1.ErrorSt_PDC)
#endif

/* Handle:   64,Name:               RadarSysSt_Front,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxRadarSysSt_Front()            (PDC_1.PDC_1.RadarSysSt_Front)
#endif

/* Handle:   65,Name:                RadarSysSt_Rear,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxRadarSysSt_Rear()             (PDC_1.PDC_1.RadarSysSt_Rear)
#endif

/* Handle:   66,Name:                  BuzeerCmd_PDC,Size:  3,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxBuzeerCmd_PDC()               (PDC_1.PDC_1.BuzeerCmd_PDC)
#endif

/* Handle:   67,Name:           RadarSysSt_FrontSide,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxRadarSysSt_FrontSide()        (PDC_1.PDC_1.RadarSysSt_FrontSide)
#endif

/* Handle:   68,Name:            RadarSysSt_RearSide,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxRadarSysSt_RearSide()         (PDC_1.PDC_1.RadarSysSt_RearSide)
#endif

/* Handle:   69,Name:                 ObjectRange_RR,Size:  3,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxObjectRange_RR()              (PDC_1.PDC_1.ObjectRange_RR)
#endif

/* Handle:   70,Name:               SensorErrorSt_RR,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxSensorErrorSt_RR()            (PDC_1.PDC_1.SensorErrorSt_RR)
#endif

/* Handle:   71,Name:                ObjectRange_RMR,Size:  3,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxObjectRange_RMR()             (PDC_1.PDC_1.ObjectRange_RMR)
#endif

/* Handle:   72,Name:              SensorErrorSt_RMR,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxSensorErrorSt_RMR()           (PDC_1.PDC_1.SensorErrorSt_RMR)
#endif

/* Handle:   73,Name:                ObjectRange_RML,Size:  3,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxObjectRange_RML()             (PDC_1.PDC_1.ObjectRange_RML)
#endif

/* Handle:   74,Name:              SensorErrorSt_RML,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxSensorErrorSt_RML()           (PDC_1.PDC_1.SensorErrorSt_RML)
#endif

/* Handle:   75,Name:                 ObjectRange_RL,Size:  3,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxObjectRange_RL()              (PDC_1.PDC_1.ObjectRange_RL)
#endif

/* Handle:   76,Name:               SensorErrorSt_RL,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxSensorErrorSt_RL()            (PDC_1.PDC_1.SensorErrorSt_RL)
#endif

/* Handle:   77,Name:                 ObjectRange_FR,Size:  3,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxObjectRange_FR()              (PDC_1.PDC_1.ObjectRange_FR)
#endif

/* Handle:   78,Name:               SensorErrorSt_FR,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxSensorErrorSt_FR()            (PDC_1.PDC_1.SensorErrorSt_FR)
#endif

/* Handle:   79,Name:                ObjectRange_FMR,Size:  3,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxObjectRange_FMR()             (PDC_1.PDC_1.ObjectRange_FMR)
#endif

/* Handle:   80,Name:              SensorErrorSt_FMR,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxSensorErrorSt_FMR()           (PDC_1.PDC_1.SensorErrorSt_FMR)
#endif

/* Handle:   81,Name:                ObjectRange_FML,Size:  3,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxObjectRange_FML()             (PDC_1.PDC_1.ObjectRange_FML)
#endif

/* Handle:   82,Name:              SensorErrorSt_FML,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxSensorErrorSt_FML()           (PDC_1.PDC_1.SensorErrorSt_FML)
#endif

/* Handle:   83,Name:                 ObjectRange_FL,Size:  3,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxObjectRange_FL()              (PDC_1.PDC_1.ObjectRange_FL)
#endif

/* Handle:   84,Name:               SensorErrorSt_FL,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxSensorErrorSt_FL()            (PDC_1.PDC_1.SensorErrorSt_FL)
#endif

/* Handle:   85,Name:           PDCAutoOnFunctionInd,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxPDCAutoOnFunctionInd()        (PDC_1.PDC_1.PDCAutoOnFunctionInd)
#endif

/* Handle:   86,Name:        SwitchScreenRequest_PDC,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxSwitchScreenRequest_PDC()     (PDC_1.PDC_1.SwitchScreenRequest_PDC)
#endif

/* Handle:   87,Name:                      DoorSt_RR,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxDoorSt_RR()                   (RRDCU_1.RRDCU_1.DoorSt_RR)
#endif

/* Handle:   88,Name:                      DoorSt_RL,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxDoorSt_RL()                   (RLDCU_1.RLDCU_1.DoorSt_RL)
#endif

/* Handle:   89,Name:                      DoorSt_FR,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxDoorSt_FR()                   (PDCU_1.PDCU_1.DoorSt_FR)
#endif

/* Handle:   90,Name:                MirrorFoldSt_FR,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxMirrorFoldSt_FR()             (PDCU_1.PDCU_1.MirrorFoldSt_FR)
#endif

/* Handle:   91,Name:                      DoorSt_FL,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxDoorSt_FL()                   (DDCU_1.DDCU_1.DoorSt_FL)
#endif

/* Handle:   92,Name:                MirrorFoldSt_FL,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxMirrorFoldSt_FL()             (DDCU_1.DDCU_1.MirrorFoldSt_FL)
#endif

/* Handle:   93,Name:                  LuggageDoorSt,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxLuggageDoorSt()               (PLG_1.PLG_1.LuggageDoorSt)
#endif

/* Handle:   94,Name:                  RainIntensity,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxRainIntensity()               (BCM1_7.BCM1_7.RainIntensity)
#endif

/* Handle:   95,Name:                   Brightness_L,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxBrightness_L()                (BCM1_7.BCM1_7.Brightness_L)
#endif

/* Handle:   97,Name:                   EngineHoodSt,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxEngineHoodSt()                (BCM1_3.BCM1_3.EngineHoodSt)
#endif

/* Handle:   98,Name:                      PowerMode,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxPowerMode()                   (BCM1_2.BCM1_2.PowerMode)
#endif

/* Handle:   99,Name:                   LowBeamSt_FL,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxLowBeamSt_FL()                (BCM1_1.BCM1_1.LowBeamSt_FL)
#endif

/* Handle:  100,Name:                   LowBeamSt_FR,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxLowBeamSt_FR()                (BCM1_1.BCM1_1.LowBeamSt_FR)
#endif

/* Handle:  101,Name:                  HighBeamSt_FL,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxHighBeamSt_FL()               (BCM1_1.BCM1_1.HighBeamSt_FL)
#endif

/* Handle:  102,Name:                  HighBeamSt_FR,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxHighBeamSt_FR()               (BCM1_1.BCM1_1.HighBeamSt_FR)
#endif

/* Handle:  103,Name:                  AutoLightMode,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxAutoLightMode()               (BCM1_1.BCM1_1.AutoLightMode)
#endif

/* Handle:  104,Name:                 TurningSt_Left,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxTurningSt_Left()              (BCM1_1.BCM1_1.TurningSt_Left)
#endif

/* Handle:  105,Name:                TurningSt_right,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxTurningSt_right()             (BCM1_1.BCM1_1.TurningSt_right)
#endif

/* Handle:  106,Name:                HazardWarningSt,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxHazardWarningSt()             (BCM1_1.BCM1_1.HazardWarningSt)
#endif

/* Handle:  107,Name:                    AmbientTemp,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxAmbientTemp()                 (ATC_2.ATC_2.AmbientTemp)
#endif

/* Handle:  108,Name:            DMS_VehicleModeInfo,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxDMS_VehicleModeInfo()         (DMS_2.DMS_2.DMS_VehicleModeInfo)
#endif

/* Handle:  109,Name:         MCP_AVSandFRadarSwitch,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxMCP_AVSandFRadarSwitch()      (MCP_1.MCP_1.MCP_AVSandFRadarSwitch)
#endif

/* Handle:  110,Name:                 Checksum_ESP_3,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxChecksum_ESP_3()              (ESP_3.ESP_3.Checksum_ESP_3)
#endif

/* Handle:  112,Name:                          YRSSt,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxYRSSt()                       (ESP_3.ESP_3.YRSSt)
#endif

/* Handle:  115,Name:                    ErrorSt_YRS,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxErrorSt_YRS()                 (ESP_3.ESP_3.ErrorSt_YRS)
#endif

/* Handle:  116,Name:              LiveCounter_ESP_3,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxLiveCounter_ESP_3()           (ESP_3.ESP_3.LiveCounter_ESP_3)
#endif

/* Handle:  117,Name:                 Checksum_ESP_2,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxChecksum_ESP_2()              (ESP_2.ESP_2.Checksum_ESP_2)
#endif

/* Handle:  118,Name:                  WorkingSt_EPB,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxWorkingSt_EPB()               (ESP_2.ESP_2.WorkingSt_EPB)
#endif

/* Handle:  119,Name:              LiveCounter_ESP_2,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxLiveCounter_ESP_2()           (ESP_2.ESP_2.LiveCounter_ESP_2)
#endif

/* Handle:  120,Name:                 Checksum_ABS_3,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxChecksum_ABS_3()              (ABS_3.ABS_3.Checksum_ABS_3)
#endif

/* Handle:  121,Name:                  WheelPulse_FL,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxWheelPulse_FL()               (ABS_3.ABS_3.WheelPulse_FL)
#endif

/* Handle:  122,Name:                  WheelPulse_FR,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxWheelPulse_FR()               (ABS_3.ABS_3.WheelPulse_FR)
#endif

/* Handle:  123,Name:                  WheelPulse_RL,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxWheelPulse_RL()               (ABS_3.ABS_3.WheelPulse_RL)
#endif

/* Handle:  124,Name:                  WheelPulse_RR,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxWheelPulse_RR()               (ABS_3.ABS_3.WheelPulse_RR)
#endif

/* Handle:  125,Name:              LiveCounter_ABS_3,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxLiveCounter_ABS_3()           (ABS_3.ABS_3.LiveCounter_ABS_3)
#endif

/* Handle:  126,Name:                 Checksum_SAS_1,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxChecksum_SAS_1()              (SAS_1.SAS_1.Checksum_SAS_1)
#endif

/* Handle:  128,Name:             SteeringWAngleSign,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxSteeringWAngleSign()          (SAS_1.SAS_1.SteeringWAngleSign)
#endif

/* Handle:  129,Name:                         SAS_St,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxSAS_St()                      (SAS_1.SAS_1.SAS_St)
#endif

/* Handle:  130,Name:              LiveCounter_SAS_1,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxLiveCounter_SAS_1()           (SAS_1.SAS_1.LiveCounter_SAS_1)
#endif

/* Handle:  131,Name:                 Checksum_ABS_2,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxChecksum_ABS_2()              (ABS_2.ABS_2.Checksum_ABS_2)
#endif

/* Handle:  134,Name:              LiveCounter_ABS_2,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxLiveCounter_ABS_2()           (ABS_2.ABS_2.LiveCounter_ABS_2)
#endif

/* Handle:  135,Name:                 Checksum_ABS_1,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxChecksum_ABS_1()              (ABS_1.ABS_1.Checksum_ABS_1)
#endif

/* Handle:  139,Name:               DrivingDirection,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxDrivingDirection()            (ABS_1.ABS_1.DrivingDirection)
#endif

/* Handle:  140,Name:              LiveCounter_ABS_1,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxLiveCounter_ABS_1()           (ABS_1.ABS_1.LiveCounter_ABS_1)
#endif

/* Handle:  141,Name:                      LeverInfo,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxLeverInfo()                   (TCU_3.TCU_3.LeverInfo)
#endif

/* Handle:  142,Name:                 Checksum_EMS_3,Size:  8,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxChecksum_EMS_3()              (EMS_3.EMS_3.Checksum_EMS_3)
#endif

/* Handle:  143,Name:                    BakePedalSt,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxBakePedalSt()                 (EMS_3.EMS_3.BakePedalSt)
#endif

/* Handle:  144,Name:              LiveCounter_EMS_3,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_RX
#define IlGetRxLiveCounter_EMS_3()           (EMS_3.EMS_3.LiveCounter_EMS_3)
#endif



/* -----------------------------------------------------------------------------
    &&&~ Get Rx Signal Access for signals greater 8bit and smaller or equal 32bit
 ----------------------------------------------------------------------------- */

/* Handle:    0,Name:         ScreenPressPosition_X1,Size: 12,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint16 IlGetRxScreenPressPosition_X1(void);
#endif

/* Handle:    1,Name:         ScreenPressPosition_Y1,Size: 12,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint16 IlGetRxScreenPressPosition_Y1(void);
#endif

/* Handle:    2,Name:         ScreenPressPosition_X2,Size: 12,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint16 IlGetRxScreenPressPosition_X2(void);
#endif

/* Handle:    3,Name:         ScreenPressPosition_Y2,Size: 12,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint16 IlGetRxScreenPressPosition_Y2(void);
#endif

/* Handle:   20,Name:                  OdometerValue,Size: 25,UsedBytes:  4,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint32 IlGetRxOdometerValue(void);
#endif

/* Handle:   25,Name:        TargetSelectionCenter_X,Size: 11,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint16 IlGetRxTargetSelectionCenter_X(void);
#endif

/* Handle:   26,Name:        TargetSelectionCenter_Y,Size: 11,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint16 IlGetRxTargetSelectionCenter_Y(void);
#endif

/* Handle:   27,Name:    TargetSelectionCenter_Angle,Size: 10,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint16 IlGetRxTargetSelectionCenter_Angle(void);
#endif

/* Handle:   31,Name:      TargetSelection_LineAngle,Size: 10,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint16 IlGetRxTargetSelection_LineAngle(void);
#endif

/* Handle:   96,Name:                   Brightness_R,Size: 10,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint16 IlGetRxBrightness_R(void);
#endif

/* Handle:  111,Name:                        YawRate,Size: 12,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint16 IlGetRxYawRate(void);
#endif

/* Handle:  113,Name:                 Acceleration_X,Size: 11,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint16 IlGetRxAcceleration_X(void);
#endif

/* Handle:  114,Name:                 Acceleration_Y,Size: 11,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint16 IlGetRxAcceleration_Y(void);
#endif

/* Handle:  127,Name:                 SteeringWAngle,Size: 15,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint16 IlGetRxSteeringWAngle(void);
#endif

/* Handle:  132,Name:                  WheelSpeed_RL,Size: 15,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint16 IlGetRxWheelSpeed_RL(void);
#endif

/* Handle:  133,Name:                  WheelSpeed_RR,Size: 15,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint16 IlGetRxWheelSpeed_RR(void);
#endif

/* Handle:  136,Name:                  WheelSpeed_FL,Size: 15,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint16 IlGetRxWheelSpeed_FL(void);
#endif

/* Handle:  137,Name:                  WheelSpeed_FR,Size: 15,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint16 IlGetRxWheelSpeed_FR(void);
#endif

/* Handle:  138,Name:                   VehicleSpeed,Size: 15,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
extern vuint16 IlGetRxVehicleSpeed(void);
#endif



/* -----------------------------------------------------------------------------
    &&&~ Set Tx Signal Access for signals smaller or equal 8bit, SendType cyclic or none
 ----------------------------------------------------------------------------- */

/* Handle:    3,Name:                    AVSViewtype,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxAVSViewtype(c) \
{ \
  IlEnterCriticalAVSViewtype(); \
  AVS_1.AVS_1.AVSViewtype = (c); \
  IlLeaveCriticalAVSViewtype(); \
}
#endif

/* Handle:   10,Name:                      MODSt_AVS,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxMODSt_AVS(c) \
{ \
  IlEnterCriticalMODSt_AVS(); \
  AVS_1.AVS_1.MODSt_AVS = (c); \
  IlLeaveCriticalMODSt_AVS(); \
}
#endif

/* Handle:   11,Name:               MODWarning_Front,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxMODWarning_Front(c) \
{ \
  IlEnterCriticalMODWarning_Front(); \
  AVS_1.AVS_1.MODWarning_Front = (c); \
  IlLeaveCriticalMODWarning_Front(); \
}
#endif

/* Handle:   12,Name:                MODWarning_Rear,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxMODWarning_Rear(c) \
{ \
  IlEnterCriticalMODWarning_Rear(); \
  AVS_1.AVS_1.MODWarning_Rear = (c); \
  IlLeaveCriticalMODWarning_Rear(); \
}
#endif

/* Handle:   13,Name: AVSTurnLightFollowupFunctionSt,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxAVSTurnLightFollowupFunctionSt(c) \
{ \
  IlEnterCriticalAVSTurnLightFollowupFunctionSt(); \
  AVS_1.AVS_1.AVSTurnLightFollowupFunctionSt = (c); \
  IlLeaveCriticalAVSTurnLightFollowupFunctionSt(); \
}
#endif

/* Handle:   14,Name:        SwitchScreenRequest_AVS,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxSwitchScreenRequest_AVS(c) \
{ \
  IlEnterCriticalSwitchScreenRequest_AVS(); \
  AVS_1.AVS_1.SwitchScreenRequest_AVS = (c); \
  IlLeaveCriticalSwitchScreenRequest_AVS(); \
}
#endif

/* Handle:   15,Name:     BlindSpotFilledFunctionInd,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxBlindSpotFilledFunctionInd(c) \
{ \
  IlEnterCriticalBlindSpotFilledFunctionInd(); \
  AVS_1.AVS_1.BlindSpotFilledFunctionInd = (c); \
  IlLeaveCriticalBlindSpotFilledFunctionInd(); \
}
#endif

/* Handle:   16,Name:             FoundSlotBuzzerTip,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxFoundSlotBuzzerTip(c) \
{ \
  IlEnterCriticalFoundSlotBuzzerTip(); \
  AVS_1.AVS_1.FoundSlotBuzzerTip = (c); \
  IlLeaveCriticalFoundSlotBuzzerTip(); \
}
#endif

/* Handle:   17,Name:      AVS_SpeechControlFeedback,Size:  5,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxAVS_SpeechControlFeedback(c) \
{ \
  IlEnterCriticalAVS_SpeechControlFeedback(); \
  AVS_1.AVS_1.AVS_SpeechControlFeedback = (c); \
  IlLeaveCriticalAVS_SpeechControlFeedback(); \
}
#endif

/* Handle:   18,Name:      AVSCameraBlockageSt_Front,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxAVSCameraBlockageSt_Front(c) \
{ \
  IlEnterCriticalAVSCameraBlockageSt_Front(); \
  AVS_1.AVS_1.AVSCameraBlockageSt_Front = (c); \
  IlLeaveCriticalAVSCameraBlockageSt_Front(); \
}
#endif

/* Handle:   19,Name:       AVSCameraBlockageSt_Rear,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxAVSCameraBlockageSt_Rear(c) \
{ \
  IlEnterCriticalAVSCameraBlockageSt_Rear(); \
  AVS_1.AVS_1.AVSCameraBlockageSt_Rear = (c); \
  IlLeaveCriticalAVSCameraBlockageSt_Rear(); \
}
#endif

/* Handle:   20,Name:       AVSCameraBlockageSt_Left,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxAVSCameraBlockageSt_Left(c) \
{ \
  IlEnterCriticalAVSCameraBlockageSt_Left(); \
  AVS_1.AVS_1.AVSCameraBlockageSt_Left = (c); \
  IlLeaveCriticalAVSCameraBlockageSt_Left(); \
}
#endif

/* Handle:   21,Name:      AVSCameraBlockageSt_Right,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxAVSCameraBlockageSt_Right(c) \
{ \
  IlEnterCriticalAVSCameraBlockageSt_Right(); \
  AVS_1.AVS_1.AVSCameraBlockageSt_Right = (c); \
  IlLeaveCriticalAVSCameraBlockageSt_Right(); \
}
#endif

/* Handle:   22,Name:                AVS_AbnormalTip,Size:  3,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxAVS_AbnormalTip(c) \
{ \
  IlEnterCriticalAVS_AbnormalTip(); \
  AVS_1.AVS_1.AVS_AbnormalTip = (c); \
  IlLeaveCriticalAVS_AbnormalTip(); \
}
#endif

/* Handle:   23,Name:              AVS_CalibrationSt,Size:  2,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxAVS_CalibrationSt(c) \
{ \
  IlEnterCriticalAVS_CalibrationSt(); \
  AVS_1.AVS_1.AVS_CalibrationSt = (c); \
  IlLeaveCriticalAVS_CalibrationSt(); \
}
#endif

/* Handle:   24,Name:            AVS_PDWarning_Front,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxAVS_PDWarning_Front(c) \
{ \
  IlEnterCriticalAVS_PDWarning_Front(); \
  AVS_1.AVS_1.AVS_PDWarning_Front = (c); \
  IlLeaveCriticalAVS_PDWarning_Front(); \
}
#endif

/* Handle:   25,Name:             AVS_PDWarning_Rear,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxAVS_PDWarning_Rear(c) \
{ \
  IlEnterCriticalAVS_PDWarning_Rear(); \
  AVS_1.AVS_1.AVS_PDWarning_Rear = (c); \
  IlLeaveCriticalAVS_PDWarning_Rear(); \
}
#endif

/* Handle:   26,Name:   AVS_RemoteMonitoringFeedback,Size:  3,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxAVS_RemoteMonitoringFeedback(c) \
{ \
  IlEnterCriticalAVS_RemoteMonitoringFeedback(); \
  AVS_1.AVS_1.AVS_RemoteMonitoringFeedback = (c); \
  IlLeaveCriticalAVS_RemoteMonitoringFeedback(); \
}
#endif

/* Handle:   27,Name:    AVS_RemoteSharpnessFeedback,Size:  3,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxAVS_RemoteSharpnessFeedback(c) \
{ \
  IlEnterCriticalAVS_RemoteSharpnessFeedback(); \
  AVS_1.AVS_1.AVS_RemoteSharpnessFeedback = (c); \
  IlLeaveCriticalAVS_RemoteSharpnessFeedback(); \
}
#endif

/* Handle:   28,Name: RemoteMonitoringSharpnessSt_AVS,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxRemoteMonitoringSharpnessSt_AVS(c) \
{ \
  IlEnterCriticalRemoteMonitoringSharpnessSt_AVS(); \
  AVS_1.AVS_1.RemoteMonitoringSharpnessSt_AVS = (c); \
  IlLeaveCriticalRemoteMonitoringSharpnessSt_AVS(); \
}
#endif

/* Handle:   29,Name:         RemoteMonitoringSt_AVS,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxRemoteMonitoringSt_AVS(c) \
{ \
  IlEnterCriticalRemoteMonitoringSt_AVS(); \
  AVS_1.AVS_1.RemoteMonitoringSt_AVS = (c); \
  IlLeaveCriticalRemoteMonitoringSt_AVS(); \
}
#endif

/* Handle:   30,Name:     RemoteMonitoringModeSt_AVS,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxRemoteMonitoringModeSt_AVS(c) \
{ \
  IlEnterCriticalRemoteMonitoringModeSt_AVS(); \
  AVS_1.AVS_1.RemoteMonitoringModeSt_AVS = (c); \
  IlLeaveCriticalRemoteMonitoringModeSt_AVS(); \
}
#endif

/* Handle:   31,Name:     AVS_RemoteViewModeFeedback,Size:  5,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
#define IlPutTxAVS_RemoteViewModeFeedback(c) \
{ \
  IlEnterCriticalAVS_RemoteViewModeFeedback(); \
  AVS_1.AVS_1.AVS_RemoteViewModeFeedback = (c); \
  IlLeaveCriticalAVS_RemoteViewModeFeedback(); \
}
#endif



/* -----------------------------------------------------------------------------
    &&&~ Set Tx Signal Access extern decl
 ----------------------------------------------------------------------------- */

/* Handle:    0,Name:                          AVSSt,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxAVSSt(vuint8 sigData);
#endif

/* Handle:    1,Name:                     AVSErrorSt,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxAVSErrorSt(vuint8 sigData);
#endif

/* Handle:    2,Name:                    AVSViewMode,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxAVSViewMode(vuint8 sigData);
#endif

/* Handle:    4,Name:         AVSCameraErrorSt_Front,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxAVSCameraErrorSt_Front(vuint8 sigData);
#endif

/* Handle:    5,Name:          AVSCameraErrorSt_Rear,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxAVSCameraErrorSt_Rear(vuint8 sigData);
#endif

/* Handle:    6,Name:          AVSCameraErrorSt_Left,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxAVSCameraErrorSt_Left(vuint8 sigData);
#endif

/* Handle:    7,Name:         AVSCameraErrorSt_Right,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxAVSCameraErrorSt_Right(vuint8 sigData);
#endif

/* Handle:    8,Name:             LanguageTypeSt_AVS,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxLanguageTypeSt_AVS(vuint8 sigData);
#endif

/* Handle:    9,Name:               DybanicPGSSt_AVS,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
extern void IlPutTxDybanicPGSSt_AVS(vuint8 sigData);
#endif




/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 400925945
      //#error "The magic number of the generated file <D:\uida0262\Desktop\tool205\gen979_1_5\il_par.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 400925945
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __IL_PAR_H__ */

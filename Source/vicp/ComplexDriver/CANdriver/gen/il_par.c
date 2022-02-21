/* -----------------------------------------------------------------------------
  Filename:    il_par.c
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

/* -----------------------------------------------------------------------------
    &&&~ Misra  justifications
 ----------------------------------------------------------------------------- */

/* PRQA S 3458 EOF *//* MD_CBD_19.4 */
/* PRQA S 3408 EOF *//* MD_Il_8.8 */
/* PRQA S 3460 EOF *//* MD_CBD_19.4 */
/* PRQA S 3412 EOF *//* MD_CBD_19.4 */
/* PRQA S 3453 EOF *//* MD_CBD_19.7 */
/* PRQA S 2006 EOF *//* MD_CBD_14.7 */
/* PRQA S 0777 EOF *//* MD_Il_0777 */
/* PRQA S 0778 EOF *//* MD_Il_0778 */
/* PRQA S 0779 EOF *//* MD_Il_0779 */
/* PRQA S 3673 EOF *//* MD_Il_3673 */
/* PRQA S 0310 EOF *//* MD_Il_0310 */
/* PRQA S 0312 EOF *//* MD_Il_0312 */
/* PRQA S 0635 EOF *//* MD_Il_0635 */
/* PRQA S 0781 EOF *//* MD_Il_0781 */
/* PRQA S 3410 EOF *//* MD_Il_3410 */
/* PRQA S 1330 EOF *//* MD_Il_1330 */
/* PRQA S 0342 EOF *//* MD_Il_0342 */
/* PRQA S 0857 EOF *//* MD_CBD_1.1 */
/* PRQA S 3109 EOF *//* MD_CBD_14.3 */
/* PRQA S 0883 EOF *//* */


#include "il_inc.h"

/* -----------------------------------------------------------------------------
    &&&~ local variables
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_CYCLIC_EVENT)
#endif



/* -----------------------------------------------------------------------------
    &&&~ Local function prototypes
 ----------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------
    &&&~ IL internal rx message timeout indication functions
 ----------------------------------------------------------------------------- */

static void IlMsgBCM1_2TimeoutIndication(void);
static void IlMsgTCU_3TimeoutIndication(void);




/* -----------------------------------------------------------------------------
    &&&~ Internal Timer Handles
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_TIMEOUT)
#define IlParHndRxBCM1_2                     0
#define IlParHndRxTCU_3                      1
#endif



#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_TIMEOUT)
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 IlTxTimeoutIndirection[kIlNumberOfTxObjects] = 
{
  kIlNoTxToutIndirection /* ID: 0x00000258, Handle: 0, AVS_1 [BC] */
};
#endif


#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_FAST_ON_START)
V_MEMROM0 V_MEMROM1 IltTxCounter V_MEMROM2 IlTxFastOnStartDuration[kIlNumberOfTxObjects] = 
{
  kIlNoFastOnStartDuration /* ID: 0x00000258, Handle: 0, AVS_1 [BC] */
};
#endif


#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_FAST_ON_START) && defined(IL_ENABLE_TX_MODE_SIGNALS)
V_MEMROM0 V_MEMROM1 IltTxCounter V_MEMROM2 IlTxFastOnStartMuxDelay[kIlNumberOfTxObjects] = 
{
  0 /* ID: 0x00000258, Handle: 0, AVS_1 [BC] */
};
#endif


#if defined(IL_ENABLE_TX)
V_MEMROM0 V_MEMROM1 IltTxCounter V_MEMROM2 IlTxStartCycles[kIlNumberOfTxObjects] = 
{
  kIlNoCycleTime /* ID: 0x00000258, Handle: 0, AVS_1 [BC] */
};
#endif


#if defined(IL_ENABLE_TX)
V_MEMROM0 V_MEMROM1 IltTxUpdateCounter V_MEMROM2 IlTxUpdateCycles[kIlNumberOfTxObjects] = 
{
  kIlNoDelayTime /* ID: 0x00000258, Handle: 0, AVS_1 [BC] */
};
#endif


#if defined(IL_ENABLE_TX)
V_MEMROM0 V_MEMROM1 IltTxCounter V_MEMROM2 IlTxCyclicCycles[kIlNumberOfTxObjects] = 
{
  10 /* ID: 0x00000258, Handle: 0, AVS_1 [BC] */
};
#endif


#if defined(IL_ENABLE_TX) && (defined(IL_ENABLE_TX_CYCLIC_EVENT) || defined(IL_ENABLE_TX_SECURE_EVENT) || defined(IL_ENABLE_TX_FAST_ON_START))
V_MEMROM0 V_MEMROM1 IltTxCounter V_MEMROM2 IlTxEventCycles[kIlNumberOfTxObjects] = 
{
  kIlNoCycleTimeFast /* ID: 0x00000258, Handle: 0, AVS_1 [BC] */
};
#endif


#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_POLLING)
V_MEMROM0 V_MEMROM1 IlConfirmationFct V_MEMROM2 IlTxConfirmationFctPtr[kIlNumberOfTxObjects] = 
{
  V_NULL /* ID: 0x00000258, Handle: 0, AVS_1 [BC] */
};
#endif


#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_TIMEOUT) && defined(C_MULTIPLE_RECEIVE_CHANNEL) && defined(IL_ENABLE_TX_VARYING_TIMEOUT) && (kIlNumberOfChannels > 1)
V_MEMROM0 V_MEMROM1 IltTxTimeoutCounter V_MEMROM2 IlTxTimeout[kIlNumberOfChannels] = 
{
  0
};
#endif


#if defined(IL_ENABLE_TX) && defined(IL_ENABLE_TX_SECURE_EVENT) && defined(IL_ENABLE_TX_VARYING_REPETITION) && (kIlNumberOfTxObjects > 1)
V_MEMROM0 V_MEMROM1 IltTxRepetitionCounter V_MEMROM2 IlTxRepetitionCounters[kIlNumberOfTxObjects] = 
{
  0 /* ID: 0x00000258, Handle: 0, AVS_1 [BC] */
};
#endif


/* -----------------------------------------------------------------------------
    &&&~ Rx Timeout Table
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_TIMEOUT)
V_MEMROM0 V_MEMROM1 IltRxTimeoutCounter V_MEMROM2 IlRxTimeoutTbl[kIlNumberOfRxTimeoutCounters] = 
{
  50 /* ID: 0x00000232, BCM1_2 [BC] */, 
  20 /* ID: 0x000000b4, TCU_3 [BC] */
};
#endif




#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_TIMEOUT)
V_MEMROM0 V_MEMROM1 IlTimeoutIndicationFct V_MEMROM2 IlRxTimeoutFctPtr[kIlNumberOfRxTimeoutCounters] = 
{
  IlMsgBCM1_2TimeoutIndication /* ID: 0x00000232, BCM1_2 [BC] */, 
  IlMsgTCU_3TimeoutIndication /* ID: 0x000000b4, TCU_3 [BC] */
};
#endif


#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_POLLING)
V_MEMROM0 V_MEMROM1 IlIndicationFct V_MEMROM2 IlCanRxIndicationFctPtr[kIlCanNumberOfRxObjects] = 
{
  V_NULL /* ID: 0x00000381, Handle: 0, HU_20 [BC] */, 
  V_NULL /* ID: 0x000002b0, Handle: 1, GW_Config [BC] */, 
  V_NULL /* ID: 0x000002a6, Handle: 2, GPS_1 [BC] */, 
  V_NULL /* ID: 0x000002a0, Handle: 3, TBOX_1 [BC] */, 
  V_NULL /* ID: 0x00000291, Handle: 4, HU_14 [BC] */, 
  V_NULL /* ID: 0x00000290, Handle: 5, IC_1 [BC] */, 
  V_NULL /* ID: 0x0000028c, Handle: 6, HU_Speech_1 [BC] */, 
  V_NULL /* ID: 0x0000028a, Handle: 7, HU_6 [BC] */, 
  V_NULL /* ID: 0x00000288, Handle: 8, HU_5 [BC] */, 
  V_NULL /* ID: 0x00000283, Handle: 9, HU_18 [BC] */, 
  V_NULL /* ID: 0x00000268, Handle: 10, LCDA_1 [BC] */, 
  V_NULL /* ID: 0x0000025d, Handle: 11, PDC_2 [BC] */, 
  V_NULL /* ID: 0x0000025c, Handle: 12, PDC_1 [BC] */, 
  V_NULL /* ID: 0x0000024f, Handle: 13, RRDCU_1 [BC] */, 
  V_NULL /* ID: 0x0000024e, Handle: 14, RLDCU_1 [BC] */, 
  V_NULL /* ID: 0x0000024c, Handle: 15, PDCU_1 [BC] */, 
  V_NULL /* ID: 0x0000024a, Handle: 16, DDCU_1 [BC] */, 
  V_NULL /* ID: 0x00000242, Handle: 17, PLG_1 [BC] */, 
  V_NULL /* ID: 0x0000023b, Handle: 18, BCM1_7 [BC] */, 
  V_NULL /* ID: 0x00000234, Handle: 19, BCM1_3 [BC] */, 
  V_NULL /* ID: 0x00000232, Handle: 20, BCM1_2 [BC] */, 
  V_NULL /* ID: 0x00000230, Handle: 21, BCM1_1 [BC] */, 
  V_NULL /* ID: 0x00000222, Handle: 22, ATC_2 [BC] */, 
  V_NULL /* ID: 0x00000216, Handle: 23, DMS_2 [BC] */, 
  V_NULL /* ID: 0x000001a4, Handle: 24, MCP_1 [BC] */, 
  V_NULL /* ID: 0x00000134, Handle: 25, ESP_3 [BC] */, 
  V_NULL /* ID: 0x00000132, Handle: 26, ESP_2 [BC] */, 
  V_NULL /* ID: 0x00000130, Handle: 27, ABS_3 [BC] */, 
  V_NULL /* ID: 0x000000d0, Handle: 28, SAS_1 [BC] */, 
  V_NULL /* ID: 0x000000c2, Handle: 29, ABS_2 [BC] */, 
  V_NULL /* ID: 0x000000c0, Handle: 30, ABS_1 [BC] */, 
  V_NULL /* ID: 0x000000b4, Handle: 31, TCU_3 [BC] */, 
  V_NULL /* ID: 0x00000094, Handle: 32, EMS_3 [BC] */
};
#endif


/* -----------------------------------------------------------------------------
    &&&~ RxDefaultInitValue Message Tables
 ----------------------------------------------------------------------------- */

V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 HU_20IlRxDefaultInitValue[7] = 
{
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00
};
V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 GPS_1IlRxDefaultInitValue[6] = 
{
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00
};
V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 IC_1IlRxDefaultInitValue[7] = 
{
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00
};
V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 HU_6IlRxDefaultInitValue[8] = 
{
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00
};
V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 PDC_1IlRxDefaultInitValue[7] = 
{
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00
};
V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 ATC_2IlRxDefaultInitValue[4] = 
{
  0x00, 
  0x00, 
  0x00, 
  0x50
};
V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 ESP_3IlRxDefaultInitValue[8] = 
{
  0x00, 
  0xD0, 
  0x87, 
  0x63, 
  0x00, 
  0x00, 
  0x1C, 
  0x03
};
V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 ABS_3IlRxDefaultInitValue[8] = 
{
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00
};
V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 SAS_1IlRxDefaultInitValue[8] = 
{
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x01
};
V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 ABS_2IlRxDefaultInitValue[8] = 
{
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00
};
V_MEMROM0 V_MEMROM1 static vuint8 V_MEMROM2 ABS_1IlRxDefaultInitValue[8] = 
{
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00, 
  0x00
};


/* -----------------------------------------------------------------------------
    &&&~ RxDefaultInitValue
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_DEFAULTVALUE)
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 V_MEMROM3* V_MEMROM1 V_MEMROM2 IlRxDefaultInitValue[kIlNumberOfRxObjects] = 
{
  HU_20IlRxDefaultInitValue, 
  V_NULL, 
  GPS_1IlRxDefaultInitValue, 
  V_NULL, 
  V_NULL, 
  IC_1IlRxDefaultInitValue, 
  V_NULL, 
  HU_6IlRxDefaultInitValue, 
  V_NULL, 
  V_NULL, 
  V_NULL, 
  V_NULL, 
  PDC_1IlRxDefaultInitValue, 
  V_NULL, 
  V_NULL, 
  V_NULL, 
  V_NULL, 
  V_NULL, 
  V_NULL, 
  V_NULL, 
  V_NULL, 
  V_NULL, 
  ATC_2IlRxDefaultInitValue, 
  V_NULL, 
  V_NULL, 
  ESP_3IlRxDefaultInitValue, 
  V_NULL, 
  ABS_3IlRxDefaultInitValue, 
  SAS_1IlRxDefaultInitValue, 
  ABS_2IlRxDefaultInitValue, 
  ABS_1IlRxDefaultInitValue, 
  V_NULL, 
  V_NULL
};
#endif



/* -----------------------------------------------------------------------------
    &&&~ Implementation of Precopy Functions
 ----------------------------------------------------------------------------- */

#ifdef IL_ENABLE_RX
vuint8 IlMsgBCM1_2PreCopy(CanRxInfoStructPtr rxStruct)
{
  rxStruct = rxStruct;
  IlEnterCriticalFlagAccess();
  ilRxTimerFlags[0] |= (vuint8) 0x01;
  IlLeaveCriticalFlagAccess();
  return kCanCopyData;
}


#endif

#ifdef IL_ENABLE_RX
vuint8 IlMsgTCU_3PreCopy(CanRxInfoStructPtr rxStruct)
{
  rxStruct = rxStruct;
  IlEnterCriticalFlagAccess();
  ilRxTimerFlags[0] |= (vuint8) 0x02;
  IlLeaveCriticalFlagAccess();
  return kCanCopyData;
}


#endif



/* -----------------------------------------------------------------------------
    &&&~ Implementation of Indication Functions
 ----------------------------------------------------------------------------- */

void IlMsgTCU_3Indication(CanReceiveHandle rxObject)
{
  rxObject = rxObject;
  IlEnterCriticalFlagAccess();
  ilRxTimeoutFlags[0] &= (vuint8) 0xFE;
  IlLeaveCriticalFlagAccess();
}




/* -----------------------------------------------------------------------------
    &&&~ Implementation Rx Timeout Indication Functions
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_RX) && (defined(IL_ENABLE_RX_TIMEOUT) || defined(IL_ENABLE_RX_EXT_TIMEOUT))
static void IlMsgBCM1_2TimeoutIndication(void)
{
  CanGlobalInterruptDisable();
  BCM1_2._c[0] &= (vuint8) 0x0F;
  BCM1_2._c[0] |= (vuint8) 0x00;
  CanGlobalInterruptRestore();
}


#endif

#if defined(IL_ENABLE_RX) && (defined(IL_ENABLE_RX_TIMEOUT) || defined(IL_ENABLE_RX_EXT_TIMEOUT))
static void IlMsgTCU_3TimeoutIndication(void)
{
  CanGlobalInterruptDisable();
  ilRxTimeoutFlags[0] |= (vuint8) 0x01;
  TCU_3._c[7] &= (vuint8) 0xF0;
  TCU_3._c[7] |= (vuint8) 0x00;
  CanGlobalInterruptRestore();
  ApplLeverInfoRxSigTimeout();
}


#endif



/* -----------------------------------------------------------------------------
    &&&~ Implementation of a function to check IfActive flags
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_SYS_TX_SIGNALS_ARE_ACTIVE_FCT)
Il_Boolean IlTxSignalsAreActive(void )
{
  return IL_FALSE;
}


#endif



/* -----------------------------------------------------------------------------
    &&&~ Implementation function to reset indication flags
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_RX) && defined(IL_ENABLE_RX_POLLING)
void IlResetCanIndicationFlags(void )
{
  CanGlobalInterruptDisable();
  CanGlobalInterruptRestore();
}


#endif



/* -----------------------------------------------------------------------------
    &&&~ Implementation function to reset confirmation flags
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_TX)
void IlResetCanConfirmationFlags(void )
{
  CanGlobalInterruptDisable();
  IlGetTxConfirmationFlags(0) &= (vuint8) 0xFD;
  CanGlobalInterruptRestore();
}


#endif



/* -----------------------------------------------------------------------------
    &&&~ Get Rx Signal Access for signals greater 8bit and smaller or equal 32bit
 ----------------------------------------------------------------------------- */

/* Handle:    0,Name:         ScreenPressPosition_X1,Size: 12,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
vuint16 IlGetRxScreenPressPosition_X1(void)
{
  vuint16 rc;
  IlEnterCriticalScreenPressPosition_X1();
  rc = ((vuint16) HU_20.HU_20.ScreenPressPosition_X1_0);
  rc |= ((vuint16) HU_20.HU_20.ScreenPressPosition_X1_1) << 8;
  IlLeaveCriticalScreenPressPosition_X1();
  return rc;
}


#endif

/* Handle:    1,Name:         ScreenPressPosition_Y1,Size: 12,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
vuint16 IlGetRxScreenPressPosition_Y1(void)
{
  vuint16 rc;
  IlEnterCriticalScreenPressPosition_Y1();
  rc = ((vuint16) HU_20.HU_20.ScreenPressPosition_Y1_0);
  rc |= ((vuint16) HU_20.HU_20.ScreenPressPosition_Y1_1) << 4;
  IlLeaveCriticalScreenPressPosition_Y1();
  return rc;
}


#endif

/* Handle:    2,Name:         ScreenPressPosition_X2,Size: 12,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
vuint16 IlGetRxScreenPressPosition_X2(void)
{
  vuint16 rc;
  IlEnterCriticalScreenPressPosition_X2();
  rc = ((vuint16) HU_20.HU_20.ScreenPressPosition_X2_0);
  rc |= ((vuint16) HU_20.HU_20.ScreenPressPosition_X2_1) << 8;
  IlLeaveCriticalScreenPressPosition_X2();
  return rc;
}


#endif

/* Handle:    3,Name:         ScreenPressPosition_Y2,Size: 12,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
vuint16 IlGetRxScreenPressPosition_Y2(void)
{
  vuint16 rc;
  IlEnterCriticalScreenPressPosition_Y2();
  rc = ((vuint16) HU_20.HU_20.ScreenPressPosition_Y2_0);
  rc |= ((vuint16) HU_20.HU_20.ScreenPressPosition_Y2_1) << 4;
  IlLeaveCriticalScreenPressPosition_Y2();
  return rc;
}


#endif

/* Handle:   20,Name:                  OdometerValue,Size: 25,UsedBytes:  4,SingleSignal */
#ifdef IL_ENABLE_RX
vuint32 IlGetRxOdometerValue(void)
{
  vuint32 rc;
  IlEnterCriticalOdometerValue();
  rc = ((vuint32) IC_1.IC_1.OdometerValue_0);
  rc |= ((vuint32) IC_1.IC_1.OdometerValue_1) << 8;
  rc |= ((vuint32) IC_1.IC_1.OdometerValue_2) << 16;
  rc |= ((vuint32) IC_1.IC_1.OdometerValue_3) << 24;
  IlLeaveCriticalOdometerValue();
  return rc;
}


#endif

/* Handle:   25,Name:        TargetSelectionCenter_X,Size: 11,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
vuint16 IlGetRxTargetSelectionCenter_X(void)
{
  vuint16 rc;
  IlEnterCriticalTargetSelectionCenter_X();
  rc = ((vuint16) HU_6.HU_6.TargetSelectionCenter_X_0);
  rc |= ((vuint16) HU_6.HU_6.TargetSelectionCenter_X_1) << 8;
  IlLeaveCriticalTargetSelectionCenter_X();
  return rc;
}


#endif

/* Handle:   26,Name:        TargetSelectionCenter_Y,Size: 11,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
vuint16 IlGetRxTargetSelectionCenter_Y(void)
{
  vuint16 rc;
  IlEnterCriticalTargetSelectionCenter_Y();
  rc = ((vuint16) HU_6.HU_6.TargetSelectionCenter_Y_0);
  rc |= ((vuint16) HU_6.HU_6.TargetSelectionCenter_Y_1) << 4;
  IlLeaveCriticalTargetSelectionCenter_Y();
  return rc;
}


#endif

/* Handle:   27,Name:    TargetSelectionCenter_Angle,Size: 10,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
vuint16 IlGetRxTargetSelectionCenter_Angle(void)
{
  vuint16 rc;
  IlEnterCriticalTargetSelectionCenter_Angle();
  rc = ((vuint16) HU_6.HU_6.TargetSelectionCenter_Angle_0);
  rc |= ((vuint16) HU_6.HU_6.TargetSelectionCenter_Angle_1) << 8;
  IlLeaveCriticalTargetSelectionCenter_Angle();
  return rc;
}


#endif

/* Handle:   31,Name:      TargetSelection_LineAngle,Size: 10,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
vuint16 IlGetRxTargetSelection_LineAngle(void)
{
  vuint16 rc;
  IlEnterCriticalTargetSelection_LineAngle();
  rc = ((vuint16) HU_6.HU_6.TargetSelection_LineAngle_0);
  rc |= ((vuint16) HU_6.HU_6.TargetSelection_LineAngle_1) << 8;
  IlLeaveCriticalTargetSelection_LineAngle();
  return rc;
}


#endif

/* Handle:   96,Name:                   Brightness_R,Size: 10,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
vuint16 IlGetRxBrightness_R(void)
{
  vuint16 rc;
  IlEnterCriticalBrightness_R();
  rc = ((vuint16) BCM1_7.BCM1_7.Brightness_R_0);
  rc |= ((vuint16) BCM1_7.BCM1_7.Brightness_R_1) << 8;
  IlLeaveCriticalBrightness_R();
  return rc;
}


#endif

/* Handle:  111,Name:                        YawRate,Size: 12,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
vuint16 IlGetRxYawRate(void)
{
  vuint16 rc;
  IlEnterCriticalYawRate();
  rc = ((vuint16) ESP_3.ESP_3.YawRate_0);
  rc |= ((vuint16) ESP_3.ESP_3.YawRate_1) << 8;
  IlLeaveCriticalYawRate();
  return rc;
}


#endif

/* Handle:  113,Name:                 Acceleration_X,Size: 11,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
vuint16 IlGetRxAcceleration_X(void)
{
  vuint16 rc;
  IlEnterCriticalAcceleration_X();
  rc = ((vuint16) ESP_3.ESP_3.Acceleration_X_0);
  rc |= ((vuint16) ESP_3.ESP_3.Acceleration_X_1) << 3;
  IlLeaveCriticalAcceleration_X();
  return rc;
}


#endif

/* Handle:  114,Name:                 Acceleration_Y,Size: 11,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
vuint16 IlGetRxAcceleration_Y(void)
{
  vuint16 rc;
  IlEnterCriticalAcceleration_Y();
  rc = ((vuint16) ESP_3.ESP_3.Acceleration_Y_0);
  rc |= ((vuint16) ESP_3.ESP_3.Acceleration_Y_1) << 8;
  IlLeaveCriticalAcceleration_Y();
  return rc;
}


#endif

/* Handle:  127,Name:                 SteeringWAngle,Size: 15,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
vuint16 IlGetRxSteeringWAngle(void)
{
  vuint16 rc;
  IlEnterCriticalSteeringWAngle();
  rc = ((vuint16) SAS_1.SAS_1.SteeringWAngle_0);
  rc |= ((vuint16) SAS_1.SAS_1.SteeringWAngle_1) << 8;
  IlLeaveCriticalSteeringWAngle();
  return rc;
}


#endif

/* Handle:  132,Name:                  WheelSpeed_RL,Size: 15,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
vuint16 IlGetRxWheelSpeed_RL(void)
{
  vuint16 rc;
  IlEnterCriticalWheelSpeed_RL();
  rc = ((vuint16) ABS_2.ABS_2.WheelSpeed_RL_0);
  rc |= ((vuint16) ABS_2.ABS_2.WheelSpeed_RL_1) << 8;
  IlLeaveCriticalWheelSpeed_RL();
  return rc;
}


#endif

/* Handle:  133,Name:                  WheelSpeed_RR,Size: 15,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
vuint16 IlGetRxWheelSpeed_RR(void)
{
  vuint16 rc;
  IlEnterCriticalWheelSpeed_RR();
  rc = ((vuint16) ABS_2.ABS_2.WheelSpeed_RR_0);
  rc |= ((vuint16) ABS_2.ABS_2.WheelSpeed_RR_1) << 8;
  IlLeaveCriticalWheelSpeed_RR();
  return rc;
}


#endif

/* Handle:  136,Name:                  WheelSpeed_FL,Size: 15,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
vuint16 IlGetRxWheelSpeed_FL(void)
{
  vuint16 rc;
  IlEnterCriticalWheelSpeed_FL();
  rc = ((vuint16) ABS_1.ABS_1.WheelSpeed_FL_0);
  rc |= ((vuint16) ABS_1.ABS_1.WheelSpeed_FL_1) << 8;
  IlLeaveCriticalWheelSpeed_FL();
  return rc;
}


#endif

/* Handle:  137,Name:                  WheelSpeed_FR,Size: 15,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
vuint16 IlGetRxWheelSpeed_FR(void)
{
  vuint16 rc;
  IlEnterCriticalWheelSpeed_FR();
  rc = ((vuint16) ABS_1.ABS_1.WheelSpeed_FR_0);
  rc |= ((vuint16) ABS_1.ABS_1.WheelSpeed_FR_1) << 8;
  IlLeaveCriticalWheelSpeed_FR();
  return rc;
}


#endif

/* Handle:  138,Name:                   VehicleSpeed,Size: 15,UsedBytes:  2,SingleSignal */
#ifdef IL_ENABLE_RX
vuint16 IlGetRxVehicleSpeed(void)
{
  vuint16 rc;
  IlEnterCriticalVehicleSpeed();
  rc = ((vuint16) ABS_1.ABS_1.VehicleSpeed_0);
  rc |= ((vuint16) ABS_1.ABS_1.VehicleSpeed_1) << 8;
  IlLeaveCriticalVehicleSpeed();
  return rc;
}


#endif



/* -----------------------------------------------------------------------------
    &&&~ Set Tx Signal Access 
 ----------------------------------------------------------------------------- */

/* Handle:    0,Name:                          AVSSt,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxAVSSt(vuint8 sigData)
{
  IlEnterCriticalAVSSt();
  AVS_1.AVS_1.AVSSt = ((vuint8) (sigData & (vuint8) 0x01));
  IlSetEvent(IlTxSigHndAVSSt);
  IlLeaveCriticalAVSSt();
}


#endif

/* Handle:    1,Name:                     AVSErrorSt,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxAVSErrorSt(vuint8 sigData)
{
  IlEnterCriticalAVSErrorSt();
  AVS_1.AVS_1.AVSErrorSt = ((vuint8) (sigData & (vuint8) 0x01));
  IlSetEvent(IlTxSigHndAVSErrorSt);
  IlLeaveCriticalAVSErrorSt();
}


#endif

/* Handle:    2,Name:                    AVSViewMode,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxAVSViewMode(vuint8 sigData)
{
  IlEnterCriticalAVSViewMode();
  AVS_1.AVS_1.AVSViewMode = ((vuint8) (sigData & (vuint8) 0x0F));
  IlSetEvent(IlTxSigHndAVSViewMode);
  IlLeaveCriticalAVSViewMode();
}


#endif

/* Handle:    4,Name:         AVSCameraErrorSt_Front,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxAVSCameraErrorSt_Front(vuint8 sigData)
{
  IlEnterCriticalAVSCameraErrorSt_Front();
  AVS_1.AVS_1.AVSCameraErrorSt_Front = ((vuint8) (sigData & (vuint8) 0x01));
  IlSetEvent(IlTxSigHndAVSCameraErrorSt_Front);
  IlLeaveCriticalAVSCameraErrorSt_Front();
}


#endif

/* Handle:    5,Name:          AVSCameraErrorSt_Rear,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxAVSCameraErrorSt_Rear(vuint8 sigData)
{
  IlEnterCriticalAVSCameraErrorSt_Rear();
  AVS_1.AVS_1.AVSCameraErrorSt_Rear = ((vuint8) (sigData & (vuint8) 0x01));
  IlSetEvent(IlTxSigHndAVSCameraErrorSt_Rear);
  IlLeaveCriticalAVSCameraErrorSt_Rear();
}


#endif

/* Handle:    6,Name:          AVSCameraErrorSt_Left,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxAVSCameraErrorSt_Left(vuint8 sigData)
{
  IlEnterCriticalAVSCameraErrorSt_Left();
  AVS_1.AVS_1.AVSCameraErrorSt_Left = ((vuint8) (sigData & (vuint8) 0x01));
  IlSetEvent(IlTxSigHndAVSCameraErrorSt_Left);
  IlLeaveCriticalAVSCameraErrorSt_Left();
}


#endif

/* Handle:    7,Name:         AVSCameraErrorSt_Right,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxAVSCameraErrorSt_Right(vuint8 sigData)
{
  IlEnterCriticalAVSCameraErrorSt_Right();
  AVS_1.AVS_1.AVSCameraErrorSt_Right = ((vuint8) (sigData & (vuint8) 0x01));
  IlSetEvent(IlTxSigHndAVSCameraErrorSt_Right);
  IlLeaveCriticalAVSCameraErrorSt_Right();
}


#endif

/* Handle:    8,Name:             LanguageTypeSt_AVS,Size:  4,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxLanguageTypeSt_AVS(vuint8 sigData)
{
  IlEnterCriticalLanguageTypeSt_AVS();
  AVS_1.AVS_1.LanguageTypeSt_AVS = ((vuint8) (sigData & (vuint8) 0x0F));
  IlSetEvent(IlTxSigHndLanguageTypeSt_AVS);
  IlLeaveCriticalLanguageTypeSt_AVS();
}


#endif

/* Handle:    9,Name:               DybanicPGSSt_AVS,Size:  1,UsedBytes:  1,SingleSignal */
#ifdef IL_ENABLE_TX
void IlPutTxDybanicPGSSt_AVS(vuint8 sigData)
{
  IlEnterCriticalDybanicPGSSt_AVS();
  AVS_1.AVS_1.DybanicPGSSt_AVS = ((vuint8) (sigData & (vuint8) 0x01));
  IlSetEvent(IlTxSigHndDybanicPGSSt_AVS);
  IlLeaveCriticalDybanicPGSSt_AVS();
}


#endif



#if defined(IL_ENABLE_TX)
V_MEMROM0 V_MEMROM1 CanTransmitHandle V_MEMROM2 IlTxIndirection[kIlNumberOfTxObjects] = 
{
  1 /* ID: 0x00000258, Handle: 0, AVS_1 [BC] */
};
#endif


/* -----------------------------------------------------------------------------
    &&&~ CAN handle to Il start stop handle
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_TX) && defined(C_ENABLE_CAN_CANCEL_NOTIFICATION)
V_MEMROM0 V_MEMROM1 IlStartStopHnd V_MEMROM2 IlCanHndToIlHnd[kIlCanNumberOfTxObjects] = 
{
  { 0, 0 } /* no Il message */, 
  { 0, 1 } /* start - stop  ID: 0x00000258, AVS_1 [BC] */, 
  { 0, 0 } /* no Il message */
};
#endif




/* -----------------------------------------------------------------------------
    &&&~ TxTypes for interaction layer tx messages 
 ----------------------------------------------------------------------------- */

#if defined(IL_ENABLE_TX)
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 IlTxType[kIlNumberOfTxObjects] = 
{
  kTxSendCyclic /* ID: 0x00000258, Handle: 0, AVS_1 [BC] */
};
#endif




/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 400925945
      //#error "The magic number of the generated file <D:\uida0262\Desktop\tool205\gen979_1_5\il_par.c> is different. Please check time and date of generated files!"
  #endif
#else
  #error "The magic number is not defined in the generated file <D:\uida0262\Desktop\tool205\gen979_1_5\il_par.c> "

#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */


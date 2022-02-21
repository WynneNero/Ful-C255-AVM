/* -----------------------------------------------------------------------------
  Filename:    can_par.h
  Description: Toolversion: 02.03.11.01.70.09.79.00.00.00
               
               Serial Number: CBD1700979
               Customer Info: Huizhou Desay SV Automotive Co., Ltd.
                              Package: CBD_Vector_SLP2
                              Micro: R7F7016213AFP
                              Compiler: Green Hills 2015.1.7
               
               
               Generator Fwk   : GENy 
               Generator Module: DrvCan__base
               
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

#if !defined(__CAN_PAR_H__)
#define __CAN_PAR_H__

#include "can_cfg.h"
#include "v_inc.h"
#include "drv_par.h"

/* -----------------------------------------------------------------------------
    &&&~ Extern declarations of callback functions
 ----------------------------------------------------------------------------- */

#if defined(C_MULTIPLE_RECEIVE_CHANNEL) || defined(C_SINGLE_RECEIVE_CHANNEL)
#endif

/* CODE CATEGORY 1 START */
extern vuint8 IlMsgBCM1_2PreCopy(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 IlMsgTCU_3PreCopy(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 TpPrecopyNormalDiagFunc(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern vuint8 TpPrecopyNormalDiagPhys(CanRxInfoStructPtr rxStruct);
/* CODE CATEGORY 1 END */


/* -----------------------------------------------------------------------------
    &&&~ Extern declarations of confirmation functions
 ----------------------------------------------------------------------------- */

/* CODE CATEGORY 1 START */
extern void CanNm_NmMsgConfirmation(CanTransmitHandle txObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void TpDrvConfirmation(CanTransmitHandle txObject);
/* CODE CATEGORY 1 END */



/* -----------------------------------------------------------------------------
    &&&~ Extern declarations of indication functions
 ----------------------------------------------------------------------------- */

/* CODE CATEGORY 1 START */
extern void HU_20_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void GW_Config_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void IC_1_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void HU_6_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void HU_5_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void LCDA_1_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void PDC_1_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void RRDCU_1_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void RLDCU_1_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void PDCU_1_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void DDCU_1_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void PLG_1_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void BCM1_2_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void BCM1_1_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void ATC_2_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void DMS_2_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void MCP_1_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void ESP_2_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void SAS_1_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void ABS_2_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void ABS_1_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void TCU_3_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void CanRxTCU_3IndicationFct(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */
/* CODE CATEGORY 1 START */
extern void IlMsgTCU_3Indication(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */

/* CODE CATEGORY 1 START */
extern void EMS_3_Received(CanReceiveHandle rcvObject);
/* CODE CATEGORY 1 END */



/* -----------------------------------------------------------------------------
    &&&~ Extern declarations Hw specififc
 ----------------------------------------------------------------------------- */

/* ROM CATEGORY 4 START */
V_MEMROM0 extern  V_MEMROM1 vuint8 V_MEMROM2 CanRxFifoDepth_0[1];
/* ROM CATEGORY 4 END */

/* ROM CATEGORY 4 START */
V_MEMROM0 extern  V_MEMROM1 tCanFilterRulesBc V_MEMROM2 CanFilterRulesBc_0[2];
/* ROM CATEGORY 4 END */





/* -----------------------------------------------------------------------------
    &&&~ Handles of send objects
 ----------------------------------------------------------------------------- */

#define CanTxAVS_NM                          0
#define CanTxAVS_1                           1
#define CanTxTxDynamicMsg0                   2


/* -----------------------------------------------------------------------------
    &&&~ Access to confirmation flags
 ----------------------------------------------------------------------------- */

#define AVS_NM_conf_b                        (CanConfirmationFlags.w[0].b0)
#define CanWriteSyncAVS_NM_conf_b(x) \
{ \
  CanStartFlagWriteSync(); \
  AVS_NM_conf_b = (x); \
  CanEndFlagWriteSync(); \
}
#define AVS_1_conf_b                         (CanConfirmationFlags.w[0].b1)
#define CanWriteSyncAVS_1_conf_b(x) \
{ \
  CanStartFlagWriteSync(); \
  AVS_1_conf_b = (x); \
  CanEndFlagWriteSync(); \
}
#define TxDynamicMsg0_conf_b                 (CanConfirmationFlags.w[0].b2)
#define CanWriteSyncTxDynamicMsg0_conf_b(x) \
{ \
  CanStartFlagWriteSync(); \
  TxDynamicMsg0_conf_b = (x); \
  CanEndFlagWriteSync(); \
}


/* -----------------------------------------------------------------------------
    &&&~ Handles of receive objects
 ----------------------------------------------------------------------------- */

#define CanRxHU_20                           0
#define CanRxGW_Config                       1
#define CanRxGPS_1                           2
#define CanRxTBOX_1                          3
#define CanRxHU_14                           4
#define CanRxIC_1                            5
#define CanRxHU_Speech_1                     6
#define CanRxHU_6                            7
#define CanRxHU_5                            8
#define CanRxHU_18                           9
#define CanRxLCDA_1                          10
#define CanRxPDC_2                           11
#define CanRxPDC_1                           12
#define CanRxRRDCU_1                         13
#define CanRxRLDCU_1                         14
#define CanRxPDCU_1                          15
#define CanRxDDCU_1                          16
#define CanRxPLG_1                           17
#define CanRxBCM1_7                          18
#define CanRxBCM1_3                          19
#define CanRxBCM1_2                          20
#define CanRxBCM1_1                          21
#define CanRxATC_2                           22
#define CanRxDMS_2                           23
#define CanRxMCP_1                           24
#define CanRxESP_3                           25
#define CanRxESP_2                           26
#define CanRxABS_3                           27
#define CanRxSAS_1                           28
#define CanRxABS_2                           29
#define CanRxABS_1                           30
#define CanRxTCU_3                           31
#define CanRxEMS_3                           32
#define CanRxDiag_Fun_Req                    33
#define CanRxAVS_Phy_Req                     34


/* -----------------------------------------------------------------------------
    &&&~ Access to signals
 ----------------------------------------------------------------------------- */

#define b_Wakeup_reason_c                    (AVS_NM.AVS_NM.Wakeup_reason)
#define b_Stay_awake_reason_c                (AVS_NM.AVS_NM.Stay_awake_reason)
#define b_Extension_information_c            (AVS_NM.AVS_NM.Extension_information)


/* -----------------------------------------------------------------------------
    &&&~ Access to data bytes of Rx messages
 ----------------------------------------------------------------------------- */

/* ID: 0x00000381, Handle: 0, HU_20 [BC] */
#define c1_HU_20_c                           (HU_20._c[0])
#define c2_HU_20_c                           (HU_20._c[1])
#define c3_HU_20_c                           (HU_20._c[2])
#define c4_HU_20_c                           (HU_20._c[3])
#define c5_HU_20_c                           (HU_20._c[4])
#define c6_HU_20_c                           (HU_20._c[5])
#define c7_HU_20_c                           (HU_20._c[6])

/* ID: 0x000002b0, Handle: 1, GW_Config [BC] */
#define c1_GW_Config_c                       (GW_Config._c[0])
#define c2_GW_Config_c                       (GW_Config._c[1])
#define c3_GW_Config_c                       (GW_Config._c[2])

/* ID: 0x000002a6, Handle: 2, GPS_1 [BC] */
#define c1_GPS_1_c                           (GPS_1._c[0])
#define c2_GPS_1_c                           (GPS_1._c[1])
#define c3_GPS_1_c                           (GPS_1._c[2])
#define c4_GPS_1_c                           (GPS_1._c[3])
#define c5_GPS_1_c                           (GPS_1._c[4])
#define c6_GPS_1_c                           (GPS_1._c[5])

/* ID: 0x000002a0, Handle: 3, TBOX_1 [BC] */
#define c1_TBOX_1_c                          (TBOX_1._c[0])
#define c2_TBOX_1_c                          (TBOX_1._c[1])
#define c3_TBOX_1_c                          (TBOX_1._c[2])
#define c4_TBOX_1_c                          (TBOX_1._c[3])
#define c5_TBOX_1_c                          (TBOX_1._c[4])
#define c6_TBOX_1_c                          (TBOX_1._c[5])
#define c7_TBOX_1_c                          (TBOX_1._c[6])
#define c8_TBOX_1_c                          (TBOX_1._c[7])

/* ID: 0x00000291, Handle: 4, HU_14 [BC] */
#define c1_HU_14_c                           (HU_14._c[0])
#define c2_HU_14_c                           (HU_14._c[1])
#define c3_HU_14_c                           (HU_14._c[2])
#define c4_HU_14_c                           (HU_14._c[3])

/* ID: 0x00000290, Handle: 5, IC_1 [BC] */
#define c1_IC_1_c                            (IC_1._c[0])
#define c2_IC_1_c                            (IC_1._c[1])
#define c3_IC_1_c                            (IC_1._c[2])
#define c4_IC_1_c                            (IC_1._c[3])
#define c5_IC_1_c                            (IC_1._c[4])
#define c6_IC_1_c                            (IC_1._c[5])
#define c7_IC_1_c                            (IC_1._c[6])

/* ID: 0x0000028c, Handle: 6, HU_Speech_1 [BC] */
#define c1_HU_Speech_1_c                     (HU_Speech_1._c[0])
#define c2_HU_Speech_1_c                     (HU_Speech_1._c[1])
#define c3_HU_Speech_1_c                     (HU_Speech_1._c[2])
#define c4_HU_Speech_1_c                     (HU_Speech_1._c[3])
#define c5_HU_Speech_1_c                     (HU_Speech_1._c[4])
#define c6_HU_Speech_1_c                     (HU_Speech_1._c[5])
#define c7_HU_Speech_1_c                     (HU_Speech_1._c[6])
#define c8_HU_Speech_1_c                     (HU_Speech_1._c[7])

/* ID: 0x0000028a, Handle: 7, HU_6 [BC] */
#define c1_HU_6_c                            (HU_6._c[0])
#define c2_HU_6_c                            (HU_6._c[1])
#define c3_HU_6_c                            (HU_6._c[2])
#define c4_HU_6_c                            (HU_6._c[3])
#define c5_HU_6_c                            (HU_6._c[4])
#define c6_HU_6_c                            (HU_6._c[5])
#define c7_HU_6_c                            (HU_6._c[6])
#define c8_HU_6_c                            (HU_6._c[7])

/* ID: 0x00000288, Handle: 8, HU_5 [BC] */
#define c1_HU_5_c                            (HU_5._c[0])
#define c2_HU_5_c                            (HU_5._c[1])
#define c3_HU_5_c                            (HU_5._c[2])
#define c4_HU_5_c                            (HU_5._c[3])
#define c5_HU_5_c                            (HU_5._c[4])
#define c6_HU_5_c                            (HU_5._c[5])
#define c7_HU_5_c                            (HU_5._c[6])
#define c8_HU_5_c                            (HU_5._c[7])

/* ID: 0x00000283, Handle: 9, HU_18 [BC] */
#define c1_HU_18_c                           (HU_18._c[0])
#define c2_HU_18_c                           (HU_18._c[1])
#define c3_HU_18_c                           (HU_18._c[2])
#define c4_HU_18_c                           (HU_18._c[3])
#define c5_HU_18_c                           (HU_18._c[4])
#define c6_HU_18_c                           (HU_18._c[5])
#define c7_HU_18_c                           (HU_18._c[6])
#define c8_HU_18_c                           (HU_18._c[7])

/* ID: 0x00000268, Handle: 10, LCDA_1 [BC] */
#define c1_LCDA_1_c                          (LCDA_1._c[0])
#define c2_LCDA_1_c                          (LCDA_1._c[1])
#define c3_LCDA_1_c                          (LCDA_1._c[2])

/* ID: 0x0000025d, Handle: 11, PDC_2 [BC] */
#define c1_PDC_2_c                           (PDC_2._c[0])
#define c2_PDC_2_c                           (PDC_2._c[1])

/* ID: 0x0000025c, Handle: 12, PDC_1 [BC] */
#define c1_PDC_1_c                           (PDC_1._c[0])
#define c2_PDC_1_c                           (PDC_1._c[1])
#define c3_PDC_1_c                           (PDC_1._c[2])
#define c4_PDC_1_c                           (PDC_1._c[3])
#define c5_PDC_1_c                           (PDC_1._c[4])
#define c6_PDC_1_c                           (PDC_1._c[5])
#define c7_PDC_1_c                           (PDC_1._c[6])

/* ID: 0x0000024f, Handle: 13, RRDCU_1 [BC] */
#define c1_RRDCU_1_c                         (RRDCU_1._c[0])

/* ID: 0x0000024e, Handle: 14, RLDCU_1 [BC] */
#define c1_RLDCU_1_c                         (RLDCU_1._c[0])

/* ID: 0x0000024c, Handle: 15, PDCU_1 [BC] */
#define c1_PDCU_1_c                          (PDCU_1._c[0])
#define c2_PDCU_1_c                          (PDCU_1._c[1])
#define c3_PDCU_1_c                          (PDCU_1._c[2])
#define c4_PDCU_1_c                          (PDCU_1._c[3])
#define c5_PDCU_1_c                          (PDCU_1._c[4])

/* ID: 0x0000024a, Handle: 16, DDCU_1 [BC] */
#define c1_DDCU_1_c                          (DDCU_1._c[0])
#define c2_DDCU_1_c                          (DDCU_1._c[1])
#define c3_DDCU_1_c                          (DDCU_1._c[2])
#define c4_DDCU_1_c                          (DDCU_1._c[3])
#define c5_DDCU_1_c                          (DDCU_1._c[4])

/* ID: 0x00000242, Handle: 17, PLG_1 [BC] */
#define c1_PLG_1_c                           (PLG_1._c[0])

/* ID: 0x0000023b, Handle: 18, BCM1_7 [BC] */
#define c1_BCM1_7_c                          (BCM1_7._c[0])
#define c2_BCM1_7_c                          (BCM1_7._c[1])
#define c3_BCM1_7_c                          (BCM1_7._c[2])
#define c4_BCM1_7_c                          (BCM1_7._c[3])

/* ID: 0x00000234, Handle: 19, BCM1_3 [BC] */
#define c1_BCM1_3_c                          (BCM1_3._c[0])
#define c2_BCM1_3_c                          (BCM1_3._c[1])

/* ID: 0x00000232, Handle: 20, BCM1_2 [BC] */
#define c1_BCM1_2_c                          (BCM1_2._c[0])

/* ID: 0x00000230, Handle: 21, BCM1_1 [BC] */
#define c1_BCM1_1_c                          (BCM1_1._c[0])
#define c2_BCM1_1_c                          (BCM1_1._c[1])
#define c3_BCM1_1_c                          (BCM1_1._c[2])

/* ID: 0x00000222, Handle: 22, ATC_2 [BC] */
#define c1_ATC_2_c                           (ATC_2._c[0])
#define c2_ATC_2_c                           (ATC_2._c[1])
#define c3_ATC_2_c                           (ATC_2._c[2])
#define c4_ATC_2_c                           (ATC_2._c[3])

/* ID: 0x00000216, Handle: 23, DMS_2 [BC] */
#define c1_DMS_2_c                           (DMS_2._c[0])
#define c2_DMS_2_c                           (DMS_2._c[1])

/* ID: 0x000001a4, Handle: 24, MCP_1 [BC] */
#define c1_MCP_1_c                           (MCP_1._c[0])
#define c2_MCP_1_c                           (MCP_1._c[1])
#define c3_MCP_1_c                           (MCP_1._c[2])
#define c4_MCP_1_c                           (MCP_1._c[3])

/* ID: 0x00000134, Handle: 25, ESP_3 [BC] */
#define c1_ESP_3_c                           (ESP_3._c[0])
#define c2_ESP_3_c                           (ESP_3._c[1])
#define c3_ESP_3_c                           (ESP_3._c[2])
#define c4_ESP_3_c                           (ESP_3._c[3])
#define c5_ESP_3_c                           (ESP_3._c[4])
#define c6_ESP_3_c                           (ESP_3._c[5])
#define c7_ESP_3_c                           (ESP_3._c[6])
#define c8_ESP_3_c                           (ESP_3._c[7])

/* ID: 0x00000132, Handle: 26, ESP_2 [BC] */
#define c1_ESP_2_c                           (ESP_2._c[0])
#define c2_ESP_2_c                           (ESP_2._c[1])
#define c3_ESP_2_c                           (ESP_2._c[2])
#define c4_ESP_2_c                           (ESP_2._c[3])
#define c5_ESP_2_c                           (ESP_2._c[4])
#define c6_ESP_2_c                           (ESP_2._c[5])
#define c7_ESP_2_c                           (ESP_2._c[6])
#define c8_ESP_2_c                           (ESP_2._c[7])

/* ID: 0x00000130, Handle: 27, ABS_3 [BC] */
#define c1_ABS_3_c                           (ABS_3._c[0])
#define c2_ABS_3_c                           (ABS_3._c[1])
#define c3_ABS_3_c                           (ABS_3._c[2])
#define c4_ABS_3_c                           (ABS_3._c[3])
#define c5_ABS_3_c                           (ABS_3._c[4])
#define c6_ABS_3_c                           (ABS_3._c[5])
#define c7_ABS_3_c                           (ABS_3._c[6])
#define c8_ABS_3_c                           (ABS_3._c[7])

/* ID: 0x000000d0, Handle: 28, SAS_1 [BC] */
#define c1_SAS_1_c                           (SAS_1._c[0])
#define c2_SAS_1_c                           (SAS_1._c[1])
#define c3_SAS_1_c                           (SAS_1._c[2])
#define c4_SAS_1_c                           (SAS_1._c[3])
#define c5_SAS_1_c                           (SAS_1._c[4])
#define c6_SAS_1_c                           (SAS_1._c[5])
#define c7_SAS_1_c                           (SAS_1._c[6])
#define c8_SAS_1_c                           (SAS_1._c[7])

/* ID: 0x000000c2, Handle: 29, ABS_2 [BC] */
#define c1_ABS_2_c                           (ABS_2._c[0])
#define c2_ABS_2_c                           (ABS_2._c[1])
#define c3_ABS_2_c                           (ABS_2._c[2])
#define c4_ABS_2_c                           (ABS_2._c[3])
#define c5_ABS_2_c                           (ABS_2._c[4])
#define c6_ABS_2_c                           (ABS_2._c[5])
#define c7_ABS_2_c                           (ABS_2._c[6])
#define c8_ABS_2_c                           (ABS_2._c[7])

/* ID: 0x000000c0, Handle: 30, ABS_1 [BC] */
#define c1_ABS_1_c                           (ABS_1._c[0])
#define c2_ABS_1_c                           (ABS_1._c[1])
#define c3_ABS_1_c                           (ABS_1._c[2])
#define c4_ABS_1_c                           (ABS_1._c[3])
#define c5_ABS_1_c                           (ABS_1._c[4])
#define c6_ABS_1_c                           (ABS_1._c[5])
#define c7_ABS_1_c                           (ABS_1._c[6])
#define c8_ABS_1_c                           (ABS_1._c[7])

/* ID: 0x000000b4, Handle: 31, TCU_3 [BC] */
#define c1_TCU_3_c                           (TCU_3._c[0])
#define c2_TCU_3_c                           (TCU_3._c[1])
#define c3_TCU_3_c                           (TCU_3._c[2])
#define c4_TCU_3_c                           (TCU_3._c[3])
#define c5_TCU_3_c                           (TCU_3._c[4])
#define c6_TCU_3_c                           (TCU_3._c[5])
#define c7_TCU_3_c                           (TCU_3._c[6])
#define c8_TCU_3_c                           (TCU_3._c[7])

/* ID: 0x00000094, Handle: 32, EMS_3 [BC] */
#define c1_EMS_3_c                           (EMS_3._c[0])
#define c2_EMS_3_c                           (EMS_3._c[1])
#define c3_EMS_3_c                           (EMS_3._c[2])
#define c4_EMS_3_c                           (EMS_3._c[3])
#define c5_EMS_3_c                           (EMS_3._c[4])
#define c6_EMS_3_c                           (EMS_3._c[5])
#define c7_EMS_3_c                           (EMS_3._c[6])
#define c8_EMS_3_c                           (EMS_3._c[7])



/* -----------------------------------------------------------------------------
    &&&~ Access to data bytes of Tx messages
 ----------------------------------------------------------------------------- */

/* ID: 0x0000058e, Handle: 0, AVS_NM [BC] */
#define c1_AVS_NM_c                          (AVS_NM._c[0])
#define c2_AVS_NM_c                          (AVS_NM._c[1])
#define c3_AVS_NM_c                          (AVS_NM._c[2])
#define c4_AVS_NM_c                          (AVS_NM._c[3])
#define c5_AVS_NM_c                          (AVS_NM._c[4])
#define c6_AVS_NM_c                          (AVS_NM._c[5])
#define c7_AVS_NM_c                          (AVS_NM._c[6])
#define c8_AVS_NM_c                          (AVS_NM._c[7])

/* ID: 0x00000258, Handle: 1, AVS_1 [BC] */
#define c1_AVS_1_c                           (AVS_1._c[0])
#define c2_AVS_1_c                           (AVS_1._c[1])
#define c3_AVS_1_c                           (AVS_1._c[2])
#define c4_AVS_1_c                           (AVS_1._c[3])
#define c5_AVS_1_c                           (AVS_1._c[4])
#define c6_AVS_1_c                           (AVS_1._c[5])
#define c7_AVS_1_c                           (AVS_1._c[6])
#define c8_AVS_1_c                           (AVS_1._c[7])

/* ID: 0x000007ff, Handle: 2, TxDynamicMsg0 [BC] */
#define c1_TxDynamicMsg0_c                   (TxDynamicMsg0._c[0])
#define c2_TxDynamicMsg0_c                   (TxDynamicMsg0._c[1])
#define c3_TxDynamicMsg0_c                   (TxDynamicMsg0._c[2])
#define c4_TxDynamicMsg0_c                   (TxDynamicMsg0._c[3])
#define c5_TxDynamicMsg0_c                   (TxDynamicMsg0._c[4])
#define c6_TxDynamicMsg0_c                   (TxDynamicMsg0._c[5])
#define c7_TxDynamicMsg0_c                   (TxDynamicMsg0._c[6])
#define c8_TxDynamicMsg0_c                   (TxDynamicMsg0._c[7])



/* -----------------------------------------------------------------------------
    &&&~ RDS Access
 ----------------------------------------------------------------------------- */

typedef struct _c_AVS_1_RDS_msgTypeTag
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
} _c_AVS_1_RDS_msgType;

#define b_CAN_Wakeup_reason_c                (RDSTx.AVS_NM.Wakeup_reason)
#define b_CAN_Stay_awake_reason_c            (RDSTx.AVS_NM.Stay_awake_reason)
#define b_CAN_Extension_information_c        (RDSTx.AVS_NM.Extension_information)

typedef struct _c_AVS_NM_RDS_msgTypeTag
{
  vbittype Wakeup_reason : 8;
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype Stay_awake_reason : 8;
  vbittype Extension_information : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 8;
  vbittype unused4 : 8;
} _c_AVS_NM_RDS_msgType;

typedef struct _c_Diag_Fun_Req_RDS_msgTypeTag
{
  vbittype Diag_Fun_Req_0 : 8;
  vbittype Diag_Fun_Req_1 : 8;
  vbittype Diag_Fun_Req_2 : 8;
  vbittype Diag_Fun_Req_3 : 8;
  vbittype Diag_Fun_Req_4 : 8;
  vbittype Diag_Fun_Req_5 : 8;
  vbittype Diag_Fun_Req_6 : 8;
  vbittype Diag_Fun_Req_7 : 8;
} _c_Diag_Fun_Req_RDS_msgType;

typedef struct _c_ABS_1_RDS_msgTypeTag
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
} _c_ABS_1_RDS_msgType;

typedef struct _c_AVS_Phy_Req_RDS_msgTypeTag
{
  vbittype AVS_Phy_Req_0 : 8;
  vbittype AVS_Phy_Req_1 : 8;
  vbittype AVS_Phy_Req_2 : 8;
  vbittype AVS_Phy_Req_3 : 8;
  vbittype AVS_Phy_Req_4 : 8;
  vbittype AVS_Phy_Req_5 : 8;
  vbittype AVS_Phy_Req_6 : 8;
  vbittype AVS_Phy_Req_7 : 8;
} _c_AVS_Phy_Req_RDS_msgType;

typedef struct _c_IC_1_RDS_msgTypeTag
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
} _c_IC_1_RDS_msgType;

typedef struct _c_HU_5_RDS_msgTypeTag
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
} _c_HU_5_RDS_msgType;

typedef struct _c_TCU_3_RDS_msgTypeTag
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
} _c_TCU_3_RDS_msgType;

typedef struct _c_SAS_1_RDS_msgTypeTag
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
} _c_SAS_1_RDS_msgType;

typedef struct _c_PDC_1_RDS_msgTypeTag
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
} _c_PDC_1_RDS_msgType;

typedef struct _c_ATC_2_RDS_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype AmbientTemp : 8;
} _c_ATC_2_RDS_msgType;

typedef struct _c_GPS_1_RDS_msgTypeTag
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
} _c_GPS_1_RDS_msgType;

typedef struct _c_PDCU_1_RDS_msgTypeTag
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
} _c_PDCU_1_RDS_msgType;

typedef struct _c_PLG_1_RDS_msgTypeTag
{
  vbittype LuggageDoorSt : 1;
  vbittype unused0 : 7;
} _c_PLG_1_RDS_msgType;

typedef struct _c_EMS_3_RDS_msgTypeTag
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
} _c_EMS_3_RDS_msgType;

typedef struct _c_HU_Speech_1_RDS_msgTypeTag
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
} _c_HU_Speech_1_RDS_msgType;

typedef struct _c_ESP_3_RDS_msgTypeTag
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
} _c_ESP_3_RDS_msgType;

typedef struct _c_ESP_2_RDS_msgTypeTag
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
} _c_ESP_2_RDS_msgType;

typedef struct _c_DDCU_1_RDS_msgTypeTag
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
} _c_DDCU_1_RDS_msgType;

typedef struct _c_BCM1_1_RDS_msgTypeTag
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
} _c_BCM1_1_RDS_msgType;

typedef struct _c_ABS_3_RDS_msgTypeTag
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
} _c_ABS_3_RDS_msgType;

typedef struct _c_ABS_2_RDS_msgTypeTag
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
} _c_ABS_2_RDS_msgType;

typedef struct _c_BCM1_2_RDS_msgTypeTag
{
  vbittype unused0 : 4;
  vbittype PowerMode : 4;
} _c_BCM1_2_RDS_msgType;

typedef struct _c_PDC_2_RDS_msgTypeTag
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
} _c_PDC_2_RDS_msgType;

typedef struct _c_LCDA_1_RDS_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype WarningCmd_RCTA_left : 2;
  vbittype unused2 : 2;
  vbittype WarningCmd_RCTA_Right : 2;
  vbittype unused3 : 2;
} _c_LCDA_1_RDS_msgType;

typedef struct _c_TBOX_1_RDS_msgTypeTag
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
} _c_TBOX_1_RDS_msgType;

typedef struct _c_RRDCU_1_RDS_msgTypeTag
{
  vbittype unused0 : 2;
  vbittype DoorSt_RR : 1;
  vbittype unused1 : 5;
} _c_RRDCU_1_RDS_msgType;

typedef struct _c_RLDCU_1_RDS_msgTypeTag
{
  vbittype unused0 : 2;
  vbittype DoorSt_RL : 1;
  vbittype unused1 : 5;
} _c_RLDCU_1_RDS_msgType;

typedef struct _c_MCP_1_RDS_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype unused3 : 1;
  vbittype MCP_AVSandFRadarSwitch : 1;
  vbittype unused4 : 6;
} _c_MCP_1_RDS_msgType;

typedef struct _c_HU_6_RDS_msgTypeTag
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
} _c_HU_6_RDS_msgType;

typedef struct _c_HU_20_RDS_msgTypeTag
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
} _c_HU_20_RDS_msgType;

typedef struct _c_HU_18_RDS_msgTypeTag
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
} _c_HU_18_RDS_msgType;

typedef struct _c_HU_14_RDS_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 8;
  vbittype unused2 : 8;
  vbittype DisplayTheme : 3;
  vbittype unused3 : 5;
} _c_HU_14_RDS_msgType;

typedef struct _c_GW_Config_RDS_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 4;
  vbittype GW_RemoteVehicleMode : 1;
  vbittype unused2 : 3;
  vbittype GW_OTAMode : 3;
  vbittype unused3 : 5;
} _c_GW_Config_RDS_msgType;

typedef struct _c_DMS_2_RDS_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype DMS_VehicleModeInfo : 4;
  vbittype unused1 : 4;
} _c_DMS_2_RDS_msgType;

typedef struct _c_BCM1_7_RDS_msgTypeTag
{
  vbittype RainIntensity : 4;
  vbittype unused0 : 4;
  vbittype Brightness_L : 8;
  vbittype Brightness_R_0 : 8;
  vbittype Brightness_R_1 : 2;
  vbittype unused1 : 6;
} _c_BCM1_7_RDS_msgType;

typedef struct _c_BCM1_3_RDS_msgTypeTag
{
  vbittype unused0 : 8;
  vbittype unused1 : 4;
  vbittype EngineHoodSt : 1;
  vbittype unused2 : 3;
} _c_BCM1_3_RDS_msgType;

typedef union _c_RDS_Tx_bufTag
{
  vuint8 _c[8];
  _c_AVS_1_RDS_msgType AVS_1;
  _c_AVS_NM_RDS_msgType AVS_NM;
} _c_RDS_Tx_buf;
typedef union _c_RDSBasic_bufTag
{
  vuint8 _c[8];
  _c_Diag_Fun_Req_RDS_msgType Diag_Fun_Req;
  _c_ABS_1_RDS_msgType ABS_1;
  _c_AVS_Phy_Req_RDS_msgType AVS_Phy_Req;
  _c_IC_1_RDS_msgType IC_1;
  _c_HU_5_RDS_msgType HU_5;
  _c_TCU_3_RDS_msgType TCU_3;
  _c_SAS_1_RDS_msgType SAS_1;
  _c_PDC_1_RDS_msgType PDC_1;
  _c_ATC_2_RDS_msgType ATC_2;
  _c_GPS_1_RDS_msgType GPS_1;
  _c_PDCU_1_RDS_msgType PDCU_1;
  _c_PLG_1_RDS_msgType PLG_1;
  _c_EMS_3_RDS_msgType EMS_3;
  _c_HU_Speech_1_RDS_msgType HU_Speech_1;
  _c_ESP_3_RDS_msgType ESP_3;
  _c_ESP_2_RDS_msgType ESP_2;
  _c_DDCU_1_RDS_msgType DDCU_1;
  _c_BCM1_1_RDS_msgType BCM1_1;
  _c_ABS_3_RDS_msgType ABS_3;
  _c_ABS_2_RDS_msgType ABS_2;
  _c_BCM1_2_RDS_msgType BCM1_2;
  _c_PDC_2_RDS_msgType PDC_2;
  _c_LCDA_1_RDS_msgType LCDA_1;
  _c_TBOX_1_RDS_msgType TBOX_1;
  _c_RRDCU_1_RDS_msgType RRDCU_1;
  _c_RLDCU_1_RDS_msgType RLDCU_1;
  _c_MCP_1_RDS_msgType MCP_1;
  _c_HU_6_RDS_msgType HU_6;
  _c_HU_20_RDS_msgType HU_20;
  _c_HU_18_RDS_msgType HU_18;
  _c_HU_14_RDS_msgType HU_14;
  _c_GW_Config_RDS_msgType GW_Config;
  _c_DMS_2_RDS_msgType DMS_2;
  _c_BCM1_7_RDS_msgType BCM1_7;
  _c_BCM1_3_RDS_msgType BCM1_3;
} _c_RDSBasic_buf;


#define RDSTx                                ((* ((_c_RDS_Tx_buf MEMORY_NORMAL *)(0xffd00000 + 0x608 + 0xb00))))
#define RDSBasic                             ((* ((_c_RDSBasic_buf MEMORY_NORMAL *)(canRDSRxPtr[0]))))



#define C_TX_NORMAL_HW_OBJ                   176
#define C_TX_NORMAL_HW_CHANNEL               0
#define C_BASIC0_HW_OBJ                      128
#define C_BASIC0_HW_CHANNEL                  0




/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 400925945
      //#error "The magic number of the generated file <D:\uida0262\Desktop\tool205\gen979_1_5\can_par.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 400925945
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __CAN_PAR_H__ */

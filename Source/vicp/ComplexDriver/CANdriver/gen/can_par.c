/* -----------------------------------------------------------------------------
  Filename:    can_par.c
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

#define C_DRV_INTERNAL
#include "can_inc.h"
#include "can_par.h"
#include "v_inc.h"

/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 tCanTxId0 V_MEMROM2 CanTxId0[kCanNumberOfTxObjects] = 
{
  MK_STDID0(0x58Eu) /* ID: 0x0000058e, Handle: 0, AVS_NM [BC] */, 
  MK_STDID0(0x258u) /* ID: 0x00000258, Handle: 1, AVS_1 [BC] */, 
  MK_STDID0(0x7FFu) /* ID: 0x000007ff, Handle: 2, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 1 END */


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanTxDLC[kCanNumberOfTxObjects] = 
{
  MK_TX_DLC(8) /* ID: 0x0000058e, Handle: 0, AVS_NM [BC] */, 
  MK_TX_DLC(8) /* ID: 0x00000258, Handle: 1, AVS_1 [BC] */, 
  MK_TX_DLC(8) /* ID: 0x000007ff, Handle: 2, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 1 END */


#ifdef C_ENABLE_COPY_TX_DATA
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 TxDataPtr V_MEMROM2 CanTxDataPtr[kCanNumberOfTxObjects] = 
{
  (TxDataPtr) AVS_NM._c /* ID: 0x0000058e, Handle: 0, AVS_NM [BC] */, 
  (TxDataPtr) AVS_1._c /* ID: 0x00000258, Handle: 1, AVS_1 [BC] */, 
  (TxDataPtr) TxDynamicMsg0._c /* ID: 0x000007ff, Handle: 2, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_PRETRANSMIT_FCT
/* ROM CATEGORY 1 START */
/* PRQA  S 1334 QAC_Can_1334 */ /* MD_Can_1334 */
V_MEMROM0 V_MEMROM1 ApplPreTransmitFct V_MEMROM2 CanTxApplPreTransmitPtr[kCanNumberOfTxObjects] = 
{
  V_NULL /* ID: 0x0000058e, Handle: 0, AVS_NM [BC] */, 
  V_NULL /* ID: 0x00000258, Handle: 1, AVS_1 [BC] */, 
  V_NULL /* ID: 0x000007ff, Handle: 2, TxDynamicMsg0 [BC] */
};
/* PRQA  L:QAC_Can_1334 */

/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_CONFIRMATION_FCT
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 ApplConfirmationFct V_MEMROM2 CanTxApplConfirmationPtr[kCanNumberOfTxObjects] = 
{
  CanNm_NmMsgConfirmation /* ID: 0x0000058e, Handle: 0, AVS_NM [BC] */, 
  V_NULL /* ID: 0x00000258, Handle: 1, AVS_1 [BC] */, 
  TpDrvConfirmation /* ID: 0x000007ff, Handle: 2, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_PART_OFFLINE
/* ROM CATEGORY 2 START */

V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanTxSendMask[kCanNumberOfTxObjects] = 
{
  (vuint8) C_SEND_GRP_NM /* ID: 0x0000058e, Handle: 0, AVS_NM [BC] */, 
  (vuint8) C_SEND_GRP_IL /* ID: 0x00000258, Handle: 1, AVS_1 [BC] */, 
  (vuint8) C_SEND_GRP_DIAG /* ID: 0x000007ff, Handle: 2, TxDynamicMsg0 [BC] */
};

/* ROM CATEGORY 2 END */

#endif


#ifdef C_ENABLE_CONFIRMATION_FLAG
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanConfirmationOffset[kCanNumberOfTxObjects] = 
{
  0 /* ID: 0x0000058e, Handle: 0, AVS_NM [BC] */, 
  0 /* ID: 0x00000258, Handle: 1, AVS_1 [BC] */, 
  0 /* ID: 0x000007ff, Handle: 2, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 1 END */


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanConfirmationMask[kCanNumberOfTxObjects] = 
{
  0x01u /* ID: 0x0000058e, Handle: 0, AVS_NM [BC] */, 
  0x02u /* ID: 0x00000258, Handle: 1, AVS_1 [BC] */, 
  0x04u /* ID: 0x000007ff, Handle: 2, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 1 END */


#endif




/* Id table depending on search algorithm */
/* Linear search */
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 tCanRxId0 V_MEMROM2 CanRxId0[kCanNumberOfRxObjects] = 
{
  MK_STDID0(0x7DFu) /* ID: 0x000007df, Handle: 33, Diag_Fun_Req [BC] */, 
  MK_STDID0(0x726u) /* ID: 0x00000726, Handle: 34, AVS_Phy_Req [BC] */, 
  MK_STDID0(0x381u) /* ID: 0x00000381, Handle: 0, HU_20 [BC] */, 
  MK_STDID0(0x2B0u) /* ID: 0x000002b0, Handle: 1, GW_Config [BC] */, 
  MK_STDID0(0x2A6u) /* ID: 0x000002a6, Handle: 2, GPS_1 [BC] */, 
  MK_STDID0(0x2A0u) /* ID: 0x000002a0, Handle: 3, TBOX_1 [BC] */, 
  MK_STDID0(0x291u) /* ID: 0x00000291, Handle: 4, HU_14 [BC] */, 
  MK_STDID0(0x290u) /* ID: 0x00000290, Handle: 5, IC_1 [BC] */, 
  MK_STDID0(0x28Cu) /* ID: 0x0000028c, Handle: 6, HU_Speech_1 [BC] */, 
  MK_STDID0(0x28Au) /* ID: 0x0000028a, Handle: 7, HU_6 [BC] */, 
  MK_STDID0(0x288u) /* ID: 0x00000288, Handle: 8, HU_5 [BC] */, 
  MK_STDID0(0x283u) /* ID: 0x00000283, Handle: 9, HU_18 [BC] */, 
  MK_STDID0(0x268u) /* ID: 0x00000268, Handle: 10, LCDA_1 [BC] */, 
  MK_STDID0(0x25Du) /* ID: 0x0000025d, Handle: 11, PDC_2 [BC] */, 
  MK_STDID0(0x25Cu) /* ID: 0x0000025c, Handle: 12, PDC_1 [BC] */, 
  MK_STDID0(0x24Fu) /* ID: 0x0000024f, Handle: 13, RRDCU_1 [BC] */, 
  MK_STDID0(0x24Eu) /* ID: 0x0000024e, Handle: 14, RLDCU_1 [BC] */, 
  MK_STDID0(0x24Cu) /* ID: 0x0000024c, Handle: 15, PDCU_1 [BC] */, 
  MK_STDID0(0x24Au) /* ID: 0x0000024a, Handle: 16, DDCU_1 [BC] */, 
  MK_STDID0(0x242u) /* ID: 0x00000242, Handle: 17, PLG_1 [BC] */, 
  MK_STDID0(0x23Bu) /* ID: 0x0000023b, Handle: 18, BCM1_7 [BC] */, 
  MK_STDID0(0x234u) /* ID: 0x00000234, Handle: 19, BCM1_3 [BC] */, 
  MK_STDID0(0x232u) /* ID: 0x00000232, Handle: 20, BCM1_2 [BC] */, 
  MK_STDID0(0x230u) /* ID: 0x00000230, Handle: 21, BCM1_1 [BC] */, 
  MK_STDID0(0x222u) /* ID: 0x00000222, Handle: 22, ATC_2 [BC] */, 
  MK_STDID0(0x216u) /* ID: 0x00000216, Handle: 23, DMS_2 [BC] */, 
  MK_STDID0(0x1A4u) /* ID: 0x000001a4, Handle: 24, MCP_1 [BC] */, 
  MK_STDID0(0x134u) /* ID: 0x00000134, Handle: 25, ESP_3 [BC] */, 
  MK_STDID0(0x132u) /* ID: 0x00000132, Handle: 26, ESP_2 [BC] */, 
  MK_STDID0(0x130u) /* ID: 0x00000130, Handle: 27, ABS_3 [BC] */, 
  MK_STDID0(0x0D0u) /* ID: 0x000000d0, Handle: 28, SAS_1 [BC] */, 
  MK_STDID0(0x0C2u) /* ID: 0x000000c2, Handle: 29, ABS_2 [BC] */, 
  MK_STDID0(0x0C0u) /* ID: 0x000000c0, Handle: 30, ABS_1 [BC] */, 
  MK_STDID0(0x0B4u) /* ID: 0x000000b4, Handle: 31, TCU_3 [BC] */, 
  MK_STDID0(0x094u) /* ID: 0x00000094, Handle: 32, EMS_3 [BC] */
};
/* ROM CATEGORY 1 END */


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 CanReceiveHandle V_MEMROM2 CanRxMsgIndirection[kCanNumberOfRxObjects] = 
{
  33 /* ID: 0x000007df, Handle: 33, Diag_Fun_Req */, 
  34 /* ID: 0x00000726, Handle: 34, AVS_Phy_Req */, 
  0 /* ID: 0x00000381, Handle: 0, HU_20 */, 
  1 /* ID: 0x000002b0, Handle: 1, GW_Config */, 
  2 /* ID: 0x000002a6, Handle: 2, GPS_1 */, 
  3 /* ID: 0x000002a0, Handle: 3, TBOX_1 */, 
  4 /* ID: 0x00000291, Handle: 4, HU_14 */, 
  5 /* ID: 0x00000290, Handle: 5, IC_1 */, 
  6 /* ID: 0x0000028c, Handle: 6, HU_Speech_1 */, 
  7 /* ID: 0x0000028a, Handle: 7, HU_6 */, 
  8 /* ID: 0x00000288, Handle: 8, HU_5 */, 
  9 /* ID: 0x00000283, Handle: 9, HU_18 */, 
  10 /* ID: 0x00000268, Handle: 10, LCDA_1 */, 
  11 /* ID: 0x0000025d, Handle: 11, PDC_2 */, 
  12 /* ID: 0x0000025c, Handle: 12, PDC_1 */, 
  13 /* ID: 0x0000024f, Handle: 13, RRDCU_1 */, 
  14 /* ID: 0x0000024e, Handle: 14, RLDCU_1 */, 
  15 /* ID: 0x0000024c, Handle: 15, PDCU_1 */, 
  16 /* ID: 0x0000024a, Handle: 16, DDCU_1 */, 
  17 /* ID: 0x00000242, Handle: 17, PLG_1 */, 
  18 /* ID: 0x0000023b, Handle: 18, BCM1_7 */, 
  19 /* ID: 0x00000234, Handle: 19, BCM1_3 */, 
  20 /* ID: 0x00000232, Handle: 20, BCM1_2 */, 
  21 /* ID: 0x00000230, Handle: 21, BCM1_1 */, 
  22 /* ID: 0x00000222, Handle: 22, ATC_2 */, 
  23 /* ID: 0x00000216, Handle: 23, DMS_2 */, 
  24 /* ID: 0x000001a4, Handle: 24, MCP_1 */, 
  25 /* ID: 0x00000134, Handle: 25, ESP_3 */, 
  26 /* ID: 0x00000132, Handle: 26, ESP_2 */, 
  27 /* ID: 0x00000130, Handle: 27, ABS_3 */, 
  28 /* ID: 0x000000d0, Handle: 28, SAS_1 */, 
  29 /* ID: 0x000000c2, Handle: 29, ABS_2 */, 
  30 /* ID: 0x000000c0, Handle: 30, ABS_1 */, 
  31 /* ID: 0x000000b4, Handle: 31, TCU_3 */, 
  32 /* ID: 0x00000094, Handle: 32, EMS_3 */
};
/* ROM CATEGORY 1 END */


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanRxDataLen[kCanNumberOfRxObjects] = 
{
  7 /* ID: 0x00000381, Handle: 0, HU_20 [BC] */, 
  3 /* ID: 0x000002b0, Handle: 1, GW_Config [BC] */, 
  6 /* ID: 0x000002a6, Handle: 2, GPS_1 [BC] */, 
  8 /* ID: 0x000002a0, Handle: 3, TBOX_1 [BC] */, 
  4 /* ID: 0x00000291, Handle: 4, HU_14 [BC] */, 
  7 /* ID: 0x00000290, Handle: 5, IC_1 [BC] */, 
  8 /* ID: 0x0000028c, Handle: 6, HU_Speech_1 [BC] */, 
  8 /* ID: 0x0000028a, Handle: 7, HU_6 [BC] */, 
  8 /* ID: 0x00000288, Handle: 8, HU_5 [BC] */, 
  8 /* ID: 0x00000283, Handle: 9, HU_18 [BC] */, 
  3 /* ID: 0x00000268, Handle: 10, LCDA_1 [BC] */, 
  2 /* ID: 0x0000025d, Handle: 11, PDC_2 [BC] */, 
  7 /* ID: 0x0000025c, Handle: 12, PDC_1 [BC] */, 
  1 /* ID: 0x0000024f, Handle: 13, RRDCU_1 [BC] */, 
  1 /* ID: 0x0000024e, Handle: 14, RLDCU_1 [BC] */, 
  5 /* ID: 0x0000024c, Handle: 15, PDCU_1 [BC] */, 
  5 /* ID: 0x0000024a, Handle: 16, DDCU_1 [BC] */, 
  1 /* ID: 0x00000242, Handle: 17, PLG_1 [BC] */, 
  4 /* ID: 0x0000023b, Handle: 18, BCM1_7 [BC] */, 
  2 /* ID: 0x00000234, Handle: 19, BCM1_3 [BC] */, 
  1 /* ID: 0x00000232, Handle: 20, BCM1_2 [BC] */, 
  3 /* ID: 0x00000230, Handle: 21, BCM1_1 [BC] */, 
  4 /* ID: 0x00000222, Handle: 22, ATC_2 [BC] */, 
  2 /* ID: 0x00000216, Handle: 23, DMS_2 [BC] */, 
  4 /* ID: 0x000001a4, Handle: 24, MCP_1 [BC] */, 
  8 /* ID: 0x00000134, Handle: 25, ESP_3 [BC] */, 
  8 /* ID: 0x00000132, Handle: 26, ESP_2 [BC] */, 
  8 /* ID: 0x00000130, Handle: 27, ABS_3 [BC] */, 
  8 /* ID: 0x000000d0, Handle: 28, SAS_1 [BC] */, 
  8 /* ID: 0x000000c2, Handle: 29, ABS_2 [BC] */, 
  8 /* ID: 0x000000c0, Handle: 30, ABS_1 [BC] */, 
  8 /* ID: 0x000000b4, Handle: 31, TCU_3 [BC] */, 
  8 /* ID: 0x00000094, Handle: 32, EMS_3 [BC] */, 
  0 /* ID: 0x000007df, Handle: 33, Diag_Fun_Req [BC] */, 
  0 /* ID: 0x00000726, Handle: 34, AVS_Phy_Req [BC] */
};
/* ROM CATEGORY 1 END */


#ifdef C_ENABLE_COPY_RX_DATA
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 RxDataPtr V_MEMROM2 CanRxDataPtr[kCanNumberOfRxObjects] = 
{
  (RxDataPtr) HU_20._c /* ID: 0x00000381, Handle: 0, HU_20 [BC] */, 
  (RxDataPtr) GW_Config._c /* ID: 0x000002b0, Handle: 1, GW_Config [BC] */, 
  (RxDataPtr) GPS_1._c /* ID: 0x000002a6, Handle: 2, GPS_1 [BC] */, 
  (RxDataPtr) TBOX_1._c /* ID: 0x000002a0, Handle: 3, TBOX_1 [BC] */, 
  (RxDataPtr) HU_14._c /* ID: 0x00000291, Handle: 4, HU_14 [BC] */, 
  (RxDataPtr) IC_1._c /* ID: 0x00000290, Handle: 5, IC_1 [BC] */, 
  (RxDataPtr) HU_Speech_1._c /* ID: 0x0000028c, Handle: 6, HU_Speech_1 [BC] */, 
  (RxDataPtr) HU_6._c /* ID: 0x0000028a, Handle: 7, HU_6 [BC] */, 
  (RxDataPtr) HU_5._c /* ID: 0x00000288, Handle: 8, HU_5 [BC] */, 
  (RxDataPtr) HU_18._c /* ID: 0x00000283, Handle: 9, HU_18 [BC] */, 
  (RxDataPtr) LCDA_1._c /* ID: 0x00000268, Handle: 10, LCDA_1 [BC] */, 
  (RxDataPtr) PDC_2._c /* ID: 0x0000025d, Handle: 11, PDC_2 [BC] */, 
  (RxDataPtr) PDC_1._c /* ID: 0x0000025c, Handle: 12, PDC_1 [BC] */, 
  (RxDataPtr) RRDCU_1._c /* ID: 0x0000024f, Handle: 13, RRDCU_1 [BC] */, 
  (RxDataPtr) RLDCU_1._c /* ID: 0x0000024e, Handle: 14, RLDCU_1 [BC] */, 
  (RxDataPtr) PDCU_1._c /* ID: 0x0000024c, Handle: 15, PDCU_1 [BC] */, 
  (RxDataPtr) DDCU_1._c /* ID: 0x0000024a, Handle: 16, DDCU_1 [BC] */, 
  (RxDataPtr) PLG_1._c /* ID: 0x00000242, Handle: 17, PLG_1 [BC] */, 
  (RxDataPtr) BCM1_7._c /* ID: 0x0000023b, Handle: 18, BCM1_7 [BC] */, 
  (RxDataPtr) BCM1_3._c /* ID: 0x00000234, Handle: 19, BCM1_3 [BC] */, 
  (RxDataPtr) BCM1_2._c /* ID: 0x00000232, Handle: 20, BCM1_2 [BC] */, 
  (RxDataPtr) BCM1_1._c /* ID: 0x00000230, Handle: 21, BCM1_1 [BC] */, 
  (RxDataPtr) ATC_2._c /* ID: 0x00000222, Handle: 22, ATC_2 [BC] */, 
  (RxDataPtr) DMS_2._c /* ID: 0x00000216, Handle: 23, DMS_2 [BC] */, 
  (RxDataPtr) MCP_1._c /* ID: 0x000001a4, Handle: 24, MCP_1 [BC] */, 
  (RxDataPtr) ESP_3._c /* ID: 0x00000134, Handle: 25, ESP_3 [BC] */, 
  (RxDataPtr) ESP_2._c /* ID: 0x00000132, Handle: 26, ESP_2 [BC] */, 
  (RxDataPtr) ABS_3._c /* ID: 0x00000130, Handle: 27, ABS_3 [BC] */, 
  (RxDataPtr) SAS_1._c /* ID: 0x000000d0, Handle: 28, SAS_1 [BC] */, 
  (RxDataPtr) ABS_2._c /* ID: 0x000000c2, Handle: 29, ABS_2 [BC] */, 
  (RxDataPtr) ABS_1._c /* ID: 0x000000c0, Handle: 30, ABS_1 [BC] */, 
  (RxDataPtr) TCU_3._c /* ID: 0x000000b4, Handle: 31, TCU_3 [BC] */, 
  (RxDataPtr) EMS_3._c /* ID: 0x00000094, Handle: 32, EMS_3 [BC] */, 
  (RxDataPtr) 0 /* ID: 0x000007df, Handle: 33, Diag_Fun_Req [BC] */, 
  (RxDataPtr) 0 /* ID: 0x00000726, Handle: 34, AVS_Phy_Req [BC] */
};
/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_PRECOPY_FCT
/* CODE CATEGORY 1 START */
/* CODE CATEGORY 1 END */

/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 ApplPrecopyFct V_MEMROM2 CanRxApplPrecopyPtr[kCanNumberOfRxObjects] = 
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
  IlMsgBCM1_2PreCopy /* ID: 0x00000232, Handle: 20, BCM1_2 [BC] */, 
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
  IlMsgTCU_3PreCopy /* ID: 0x000000b4, Handle: 31, TCU_3 [BC] */, 
  V_NULL /* ID: 0x00000094, Handle: 32, EMS_3 [BC] */, 
  TpPrecopyNormalDiagFunc /* ID: 0x000007df, Handle: 33, Diag_Fun_Req [BC] */, 
  TpPrecopyNormalDiagPhys /* ID: 0x00000726, Handle: 34, AVS_Phy_Req [BC] */
};
/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_INDICATION_FCT
void CanRxTCU_3IndicationFct(CanReceiveHandle rcvObject)
{
  TCU_3_Received(rcvObject);
  IlMsgTCU_3Indication(rcvObject);
}


/* ROM CATEGORY 1 START */
/* PRQA  S 1334 QAC_Can_1334 */ /* MD_Can_1334 */
V_MEMROM0 V_MEMROM1 ApplIndicationFct V_MEMROM2 CanRxApplIndicationPtr[kCanNumberOfRxObjects] = 
{
  HU_20_Received /* ID: 0x00000381, Handle: 0, HU_20 [BC] */, 
  GW_Config_Received /* ID: 0x000002b0, Handle: 1, GW_Config [BC] */, 
  V_NULL /* ID: 0x000002a6, Handle: 2, GPS_1 [BC] */, 
  V_NULL /* ID: 0x000002a0, Handle: 3, TBOX_1 [BC] */, 
  V_NULL /* ID: 0x00000291, Handle: 4, HU_14 [BC] */, 
  IC_1_Received /* ID: 0x00000290, Handle: 5, IC_1 [BC] */, 
  V_NULL /* ID: 0x0000028c, Handle: 6, HU_Speech_1 [BC] */, 
  HU_6_Received /* ID: 0x0000028a, Handle: 7, HU_6 [BC] */, 
  HU_5_Received /* ID: 0x00000288, Handle: 8, HU_5 [BC] */, 
  V_NULL /* ID: 0x00000283, Handle: 9, HU_18 [BC] */, 
  LCDA_1_Received /* ID: 0x00000268, Handle: 10, LCDA_1 [BC] */, 
  V_NULL /* ID: 0x0000025d, Handle: 11, PDC_2 [BC] */, 
  PDC_1_Received /* ID: 0x0000025c, Handle: 12, PDC_1 [BC] */, 
  RRDCU_1_Received /* ID: 0x0000024f, Handle: 13, RRDCU_1 [BC] */, 
  RLDCU_1_Received /* ID: 0x0000024e, Handle: 14, RLDCU_1 [BC] */, 
  PDCU_1_Received /* ID: 0x0000024c, Handle: 15, PDCU_1 [BC] */, 
  DDCU_1_Received /* ID: 0x0000024a, Handle: 16, DDCU_1 [BC] */, 
  PLG_1_Received /* ID: 0x00000242, Handle: 17, PLG_1 [BC] */, 
  V_NULL /* ID: 0x0000023b, Handle: 18, BCM1_7 [BC] */, 
  V_NULL /* ID: 0x00000234, Handle: 19, BCM1_3 [BC] */, 
  BCM1_2_Received /* ID: 0x00000232, Handle: 20, BCM1_2 [BC] */, 
  BCM1_1_Received /* ID: 0x00000230, Handle: 21, BCM1_1 [BC] */, 
  ATC_2_Received /* ID: 0x00000222, Handle: 22, ATC_2 [BC] */, 
  DMS_2_Received /* ID: 0x00000216, Handle: 23, DMS_2 [BC] */, 
  MCP_1_Received /* ID: 0x000001a4, Handle: 24, MCP_1 [BC] */, 
  V_NULL /* ID: 0x00000134, Handle: 25, ESP_3 [BC] */, 
  ESP_2_Received /* ID: 0x00000132, Handle: 26, ESP_2 [BC] */, 
  V_NULL /* ID: 0x00000130, Handle: 27, ABS_3 [BC] */, 
  SAS_1_Received /* ID: 0x000000d0, Handle: 28, SAS_1 [BC] */, 
  ABS_2_Received /* ID: 0x000000c2, Handle: 29, ABS_2 [BC] */, 
  ABS_1_Received /* ID: 0x000000c0, Handle: 30, ABS_1 [BC] */, 
  CanRxTCU_3IndicationFct /* ID: 0x000000b4, Handle: 31, TCU_3 [BC] */, 
  EMS_3_Received /* ID: 0x00000094, Handle: 32, EMS_3 [BC] */, 
  V_NULL /* ID: 0x000007df, Handle: 33, Diag_Fun_Req [BC] */, 
  V_NULL /* ID: 0x00000726, Handle: 34, AVS_Phy_Req [BC] */
};
/* PRQA  L:QAC_Can_1334 */

/* ROM CATEGORY 1 END */

#endif


#ifdef C_ENABLE_INDICATION_FLAG
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanIndicationOffset[kCanNumberOfRxObjects] = 
{
  0 /* ID: 0x00000381, Handle: 0, HU_20 [BC] */, 
  0 /* ID: 0x000002b0, Handle: 1, GW_Config [BC] */, 
  0 /* ID: 0x000002a6, Handle: 2, GPS_1 [BC] */, 
  0 /* ID: 0x000002a0, Handle: 3, TBOX_1 [BC] */, 
  0 /* ID: 0x00000291, Handle: 4, HU_14 [BC] */, 
  0 /* ID: 0x00000290, Handle: 5, IC_1 [BC] */, 
  0 /* ID: 0x0000028c, Handle: 6, HU_Speech_1 [BC] */, 
  0 /* ID: 0x0000028a, Handle: 7, HU_6 [BC] */, 
  0 /* ID: 0x00000288, Handle: 8, HU_5 [BC] */, 
  0 /* ID: 0x00000283, Handle: 9, HU_18 [BC] */, 
  0 /* ID: 0x00000268, Handle: 10, LCDA_1 [BC] */, 
  0 /* ID: 0x0000025d, Handle: 11, PDC_2 [BC] */, 
  0 /* ID: 0x0000025c, Handle: 12, PDC_1 [BC] */, 
  0 /* ID: 0x0000024f, Handle: 13, RRDCU_1 [BC] */, 
  0 /* ID: 0x0000024e, Handle: 14, RLDCU_1 [BC] */, 
  0 /* ID: 0x0000024c, Handle: 15, PDCU_1 [BC] */, 
  0 /* ID: 0x0000024a, Handle: 16, DDCU_1 [BC] */, 
  0 /* ID: 0x00000242, Handle: 17, PLG_1 [BC] */, 
  0 /* ID: 0x0000023b, Handle: 18, BCM1_7 [BC] */, 
  0 /* ID: 0x00000234, Handle: 19, BCM1_3 [BC] */, 
  0 /* ID: 0x00000232, Handle: 20, BCM1_2 [BC] */, 
  0 /* ID: 0x00000230, Handle: 21, BCM1_1 [BC] */, 
  0 /* ID: 0x00000222, Handle: 22, ATC_2 [BC] */, 
  0 /* ID: 0x00000216, Handle: 23, DMS_2 [BC] */, 
  0 /* ID: 0x000001a4, Handle: 24, MCP_1 [BC] */, 
  0 /* ID: 0x00000134, Handle: 25, ESP_3 [BC] */, 
  0 /* ID: 0x00000132, Handle: 26, ESP_2 [BC] */, 
  0 /* ID: 0x00000130, Handle: 27, ABS_3 [BC] */, 
  0 /* ID: 0x000000d0, Handle: 28, SAS_1 [BC] */, 
  0 /* ID: 0x000000c2, Handle: 29, ABS_2 [BC] */, 
  0 /* ID: 0x000000c0, Handle: 30, ABS_1 [BC] */, 
  0 /* ID: 0x000000b4, Handle: 31, TCU_3 [BC] */, 
  0 /* ID: 0x00000094, Handle: 32, EMS_3 [BC] */, 
  0 /* ID: 0x000007df, Handle: 33, Diag_Fun_Req [BC] */, 
  0 /* ID: 0x00000726, Handle: 34, AVS_Phy_Req [BC] */
};
/* ROM CATEGORY 1 END */


/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanIndicationMask[kCanNumberOfRxObjects] = 
{
  0x00u /* ID: 0x00000381, Handle: 0, HU_20 [BC] */, 
  0x00u /* ID: 0x000002b0, Handle: 1, GW_Config [BC] */, 
  0x00u /* ID: 0x000002a6, Handle: 2, GPS_1 [BC] */, 
  0x00u /* ID: 0x000002a0, Handle: 3, TBOX_1 [BC] */, 
  0x00u /* ID: 0x00000291, Handle: 4, HU_14 [BC] */, 
  0x00u /* ID: 0x00000290, Handle: 5, IC_1 [BC] */, 
  0x00u /* ID: 0x0000028c, Handle: 6, HU_Speech_1 [BC] */, 
  0x00u /* ID: 0x0000028a, Handle: 7, HU_6 [BC] */, 
  0x00u /* ID: 0x00000288, Handle: 8, HU_5 [BC] */, 
  0x00u /* ID: 0x00000283, Handle: 9, HU_18 [BC] */, 
  0x00u /* ID: 0x00000268, Handle: 10, LCDA_1 [BC] */, 
  0x00u /* ID: 0x0000025d, Handle: 11, PDC_2 [BC] */, 
  0x00u /* ID: 0x0000025c, Handle: 12, PDC_1 [BC] */, 
  0x00u /* ID: 0x0000024f, Handle: 13, RRDCU_1 [BC] */, 
  0x00u /* ID: 0x0000024e, Handle: 14, RLDCU_1 [BC] */, 
  0x00u /* ID: 0x0000024c, Handle: 15, PDCU_1 [BC] */, 
  0x00u /* ID: 0x0000024a, Handle: 16, DDCU_1 [BC] */, 
  0x00u /* ID: 0x00000242, Handle: 17, PLG_1 [BC] */, 
  0x00u /* ID: 0x0000023b, Handle: 18, BCM1_7 [BC] */, 
  0x00u /* ID: 0x00000234, Handle: 19, BCM1_3 [BC] */, 
  0x00u /* ID: 0x00000232, Handle: 20, BCM1_2 [BC] */, 
  0x00u /* ID: 0x00000230, Handle: 21, BCM1_1 [BC] */, 
  0x00u /* ID: 0x00000222, Handle: 22, ATC_2 [BC] */, 
  0x00u /* ID: 0x00000216, Handle: 23, DMS_2 [BC] */, 
  0x00u /* ID: 0x000001a4, Handle: 24, MCP_1 [BC] */, 
  0x00u /* ID: 0x00000134, Handle: 25, ESP_3 [BC] */, 
  0x00u /* ID: 0x00000132, Handle: 26, ESP_2 [BC] */, 
  0x00u /* ID: 0x00000130, Handle: 27, ABS_3 [BC] */, 
  0x00u /* ID: 0x000000d0, Handle: 28, SAS_1 [BC] */, 
  0x00u /* ID: 0x000000c2, Handle: 29, ABS_2 [BC] */, 
  0x00u /* ID: 0x000000c0, Handle: 30, ABS_1 [BC] */, 
  0x00u /* ID: 0x000000b4, Handle: 31, TCU_3 [BC] */, 
  0x00u /* ID: 0x00000094, Handle: 32, EMS_3 [BC] */, 
  0x00u /* ID: 0x000007df, Handle: 33, Diag_Fun_Req [BC] */, 
  0x00u /* ID: 0x00000726, Handle: 34, AVS_Phy_Req [BC] */
};
/* ROM CATEGORY 1 END */


#endif




/* -----------------------------------------------------------------------------
    &&&~ Init structures
 ----------------------------------------------------------------------------- */

/* ROM CATEGORY 4 START */
/* PRQA S 3408 1 */ /* MD_Can_3408_extLinkage */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanInitObjectStartIndex[2] = 
{
  0, 
  1
};

/* ROM CATEGORY 4 END */

/* ROM CATEGORY 4 START */
V_MEMROM0 V_MEMROM1 tCanFilterRulesBc V_MEMROM2 CanFilterRulesBc_0[2] = 
{
  
  {
    0x0280u, 
    0x02A0u
  }, 
  
  {
    0x0000u, 
    0x0000u
  }
};
V_MEMROM0 V_MEMROM1 vuint32 V_MEMROM2 CanInitBCFG[1] = 
{
  0x033A0004u
};
/* ROM CATEGORY 4 END */



#if defined(C_ENABLE_MULTI_ECU_CONFIG)
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanPhysToLogChannel[kVNumberOfIdentities][kCanNumberOfPhysChannels] = 
{
  
  {
    kCanChannelNotUsed, 
    0
  }
};
/* ROM CATEGORY 1 END */

#endif

#if defined(C_ENABLE_MULTI_ECU_CONFIG)
/* ROM CATEGORY 2 START */

V_MEMROM0 V_MEMROM1 tVIdentityMsk V_MEMROM2 CanChannelIdentityAssignment[kCanNumberOfChannels] = 
{
  0x01u
};

/* ROM CATEGORY 2 END */

#endif

#if defined(C_ENABLE_MULTI_ECU_PHYS)
/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 tVIdentityMsk V_MEMROM2 CanRxIdentityAssignment[kCanNumberOfRxObjects] = 
{
  0x01u /* ID: 0x00000381, Handle: 0, HU_20 [BC] */, 
  0x01u /* ID: 0x000002b0, Handle: 1, GW_Config [BC] */, 
  0x01u /* ID: 0x000002a6, Handle: 2, GPS_1 [BC] */, 
  0x01u /* ID: 0x000002a0, Handle: 3, TBOX_1 [BC] */, 
  0x01u /* ID: 0x00000291, Handle: 4, HU_14 [BC] */, 
  0x01u /* ID: 0x00000290, Handle: 5, IC_1 [BC] */, 
  0x01u /* ID: 0x0000028c, Handle: 6, HU_Speech_1 [BC] */, 
  0x01u /* ID: 0x0000028a, Handle: 7, HU_6 [BC] */, 
  0x01u /* ID: 0x00000288, Handle: 8, HU_5 [BC] */, 
  0x01u /* ID: 0x00000283, Handle: 9, HU_18 [BC] */, 
  0x01u /* ID: 0x00000268, Handle: 10, LCDA_1 [BC] */, 
  0x01u /* ID: 0x0000025d, Handle: 11, PDC_2 [BC] */, 
  0x01u /* ID: 0x0000025c, Handle: 12, PDC_1 [BC] */, 
  0x01u /* ID: 0x0000024f, Handle: 13, RRDCU_1 [BC] */, 
  0x01u /* ID: 0x0000024e, Handle: 14, RLDCU_1 [BC] */, 
  0x01u /* ID: 0x0000024c, Handle: 15, PDCU_1 [BC] */, 
  0x01u /* ID: 0x0000024a, Handle: 16, DDCU_1 [BC] */, 
  0x01u /* ID: 0x00000242, Handle: 17, PLG_1 [BC] */, 
  0x01u /* ID: 0x0000023b, Handle: 18, BCM1_7 [BC] */, 
  0x01u /* ID: 0x00000234, Handle: 19, BCM1_3 [BC] */, 
  0x01u /* ID: 0x00000232, Handle: 20, BCM1_2 [BC] */, 
  0x01u /* ID: 0x00000230, Handle: 21, BCM1_1 [BC] */, 
  0x01u /* ID: 0x00000222, Handle: 22, ATC_2 [BC] */, 
  0x01u /* ID: 0x00000216, Handle: 23, DMS_2 [BC] */, 
  0x01u /* ID: 0x000001a4, Handle: 24, MCP_1 [BC] */, 
  0x01u /* ID: 0x00000134, Handle: 25, ESP_3 [BC] */, 
  0x01u /* ID: 0x00000132, Handle: 26, ESP_2 [BC] */, 
  0x01u /* ID: 0x00000130, Handle: 27, ABS_3 [BC] */, 
  0x01u /* ID: 0x000000d0, Handle: 28, SAS_1 [BC] */, 
  0x01u /* ID: 0x000000c2, Handle: 29, ABS_2 [BC] */, 
  0x01u /* ID: 0x000000c0, Handle: 30, ABS_1 [BC] */, 
  0x01u /* ID: 0x000000b4, Handle: 31, TCU_3 [BC] */, 
  0x01u /* ID: 0x00000094, Handle: 32, EMS_3 [BC] */, 
  0x01u /* ID: 0x000007df, Handle: 33, Diag_Fun_Req [BC] */, 
  0x01u /* ID: 0x00000726, Handle: 34, AVS_Phy_Req [BC] */
};
/* ROM CATEGORY 1 END */

/* ROM CATEGORY 4 START */
V_MEMROM0 V_MEMROM1 tVIdentityMsk V_MEMROM2 CanTxIdentityAssignment[kCanNumberOfTxObjects] = 
{
  0x01u /* ID: 0x0000058e, Handle: 0, AVS_NM [BC] */, 
  0x01u /* ID: 0x00000258, Handle: 1, AVS_1 [BC] */, 
  0x01u /* ID: 0x000007ff, Handle: 2, TxDynamicMsg0 [BC] */
};
/* ROM CATEGORY 4 END */

#endif


#ifdef C_ENABLE_TX_FULLCAN_OBJECTS
/* ROM CATEGORY 2 START */
#ifdef C_ENABLE_HW_OBJ_EXCEED_255_DRV
V_MEMROM0 V_MEMROM1 CanObjectHandle V_MEMROM2 CanTxHwObj[kCanNumberOfTxObjects] = 
{
  0xB0 /* ID: 0x0000058e, Handle: 0, AVS_NM [BC] */, 
  0xB0 /* ID: 0x00000258, Handle: 1, AVS_1 [BC] */, 
  0xB0 /* ID: 0x000007ff, Handle: 2, TxDynamicMsg0 [BC] */
};
#else
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanTxHwObj[kCanNumberOfTxObjects] = 
{
  0xB0 /* ID: 0x0000058e, Handle: 0, AVS_NM [BC] */, 
  0xB0 /* ID: 0x00000258, Handle: 1, AVS_1 [BC] */, 
  0xB0 /* ID: 0x000007ff, Handle: 2, TxDynamicMsg0 [BC] */
};
#endif

/* ROM CATEGORY 2 END */

#endif



/* -----------------------------------------------------------------------------
    &&&~ Hw specific
 ----------------------------------------------------------------------------- */

/* ROM CATEGORY 1 START */
V_MEMROM0 V_MEMROM1 tCanChannelData V_MEMROM2 CanChannelData[kCanNumberOfHwChannels] = 
{
  
  {
    CanRxFifoDepth_0 /* CanRxFifoDepth */, 
    CanFilterRulesBc_0 /* CanFilterRulesBc */, 
    0xFFFFA0D6u /* CanIntcChTxBaseAdr */, 
    0xFFFFA0D2u /* CanIntcChErrorBaseAdr */, 
    0xFFFF903Cu /* CanIntcChWakeupBaseAdr */, 
    { 0x00000000u } /* CanRxFcMask */, 
    0x0001u /* CanTxIntMask */, 
    0u /* CanFilterRulesStartIndex */, 
    0x02u /* CanFilterRulesTotalCount */, 
    2u /* CanFilterRulesBcCount */, 
    0x01u /* CanRxBcMask */, 
    0x08u /* CanRxBcMsgProcessCount */, 
    0u /* CanRxBcStartIndex */, 
    1u /* CanRxBcStopIndex */, 
    3u /* CanIntPrio */
  }
};
/* ROM CATEGORY 1 END */

/* ROM CATEGORY 1 START */
/* ROM CATEGORY 1 END */

/* ROM CATEGORY 4 START */
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanRxFifoDepth_0[1] = 
{
  0x01u
};
/* ROM CATEGORY 4 END */





/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 400925945
      //#error "The magic number of the generated file <D:\uida0262\Desktop\tool205\gen979_1_5\can_par.c> is different. Please check time and date of generated files!"
  #endif
#else
  #error "The magic number is not defined in the generated file <D:\uida0262\Desktop\tool205\gen979_1_5\can_par.c> "

#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */


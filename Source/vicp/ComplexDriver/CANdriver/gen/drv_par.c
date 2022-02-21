/* -----------------------------------------------------------------------------
  Filename:    drv_par.c
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

#include "v_inc.h"
#include "can_inc.h"

#include "drv_par.h"
/* -----------------------------------------------------------------------------
    &&&~ Message Buffers
 ----------------------------------------------------------------------------- */

/* RAM CATEGORY 2 START */
/* PRQA  S 0759 QAC_Can_0759 */ /* MD_Can_0759 */
V_MEMRAM0 V_MEMRAM1 _c_ABS_1_buf V_MEMRAM2 ABS_1;
V_MEMRAM0 V_MEMRAM1 _c_TxDynamicMsg0_buf V_MEMRAM2 TxDynamicMsg0;
V_MEMRAM0 V_MEMRAM1 _c_IC_1_buf V_MEMRAM2 IC_1;
V_MEMRAM0 V_MEMRAM1 _c_HU_5_buf V_MEMRAM2 HU_5;
V_MEMRAM0 V_MEMRAM1 _c_TCU_3_buf V_MEMRAM2 TCU_3;
V_MEMRAM0 V_MEMRAM1 _c_SAS_1_buf V_MEMRAM2 SAS_1;
V_MEMRAM0 V_MEMRAM1 _c_PDC_1_buf V_MEMRAM2 PDC_1;
V_MEMRAM0 V_MEMRAM1 _c_AVS_1_buf V_MEMRAM2 AVS_1;
V_MEMRAM0 V_MEMRAM1 _c_ATC_2_buf V_MEMRAM2 ATC_2;
V_MEMRAM0 V_MEMRAM1 _c_GPS_1_buf V_MEMRAM2 GPS_1;
V_MEMRAM0 V_MEMRAM1 _c_PDCU_1_buf V_MEMRAM2 PDCU_1;
V_MEMRAM0 V_MEMRAM1 _c_PLG_1_buf V_MEMRAM2 PLG_1;
V_MEMRAM0 V_MEMRAM1 _c_EMS_3_buf V_MEMRAM2 EMS_3;
V_MEMRAM0 V_MEMRAM1 _c_HU_Speech_1_buf V_MEMRAM2 HU_Speech_1;
V_MEMRAM0 V_MEMRAM1 _c_ESP_3_buf V_MEMRAM2 ESP_3;
V_MEMRAM0 V_MEMRAM1 _c_ESP_2_buf V_MEMRAM2 ESP_2;
V_MEMRAM0 V_MEMRAM1 _c_DDCU_1_buf V_MEMRAM2 DDCU_1;
V_MEMRAM0 V_MEMRAM1 _c_BCM1_1_buf V_MEMRAM2 BCM1_1;
V_MEMRAM0 V_MEMRAM1 _c_ABS_3_buf V_MEMRAM2 ABS_3;
V_MEMRAM0 V_MEMRAM1 _c_ABS_2_buf V_MEMRAM2 ABS_2;
V_MEMRAM0 V_MEMRAM1 _c_BCM1_2_buf V_MEMRAM2 BCM1_2;
V_MEMRAM0 V_MEMRAM1 _c_AVS_NM_buf V_MEMRAM2 AVS_NM;
V_MEMRAM0 V_MEMRAM1 _c_PDC_2_buf V_MEMRAM2 PDC_2;
V_MEMRAM0 V_MEMRAM1 _c_LCDA_1_buf V_MEMRAM2 LCDA_1;
V_MEMRAM0 V_MEMRAM1 _c_TBOX_1_buf V_MEMRAM2 TBOX_1;
V_MEMRAM0 V_MEMRAM1 _c_RRDCU_1_buf V_MEMRAM2 RRDCU_1;
V_MEMRAM0 V_MEMRAM1 _c_RLDCU_1_buf V_MEMRAM2 RLDCU_1;
V_MEMRAM0 V_MEMRAM1 _c_MCP_1_buf V_MEMRAM2 MCP_1;
V_MEMRAM0 V_MEMRAM1 _c_HU_6_buf V_MEMRAM2 HU_6;
V_MEMRAM0 V_MEMRAM1 _c_HU_20_buf V_MEMRAM2 HU_20;
V_MEMRAM0 V_MEMRAM1 _c_HU_18_buf V_MEMRAM2 HU_18;
V_MEMRAM0 V_MEMRAM1 _c_HU_14_buf V_MEMRAM2 HU_14;
V_MEMRAM0 V_MEMRAM1 _c_GW_Config_buf V_MEMRAM2 GW_Config;
V_MEMRAM0 V_MEMRAM1 _c_DMS_2_buf V_MEMRAM2 DMS_2;
V_MEMRAM0 V_MEMRAM1 _c_BCM1_7_buf V_MEMRAM2 BCM1_7;
V_MEMRAM0 V_MEMRAM1 _c_BCM1_3_buf V_MEMRAM2 BCM1_3;
/* PRQA  L:QAC_Can_0759 */

/* RAM CATEGORY 2 END */





/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 400925945
      //#error "The magic number of the generated file <D:\uida0262\Desktop\tool205\gen979_1_5\drv_par.c> is different. Please check time and date of generated files!"
  #endif
#else
  #error "The magic number is not defined in the generated file <D:\uida0262\Desktop\tool205\gen979_1_5\drv_par.c> "

#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */


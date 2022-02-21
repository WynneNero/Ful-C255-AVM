/* -----------------------------------------------------------------------------
  Filename:    ccl_par.h
  Description: Toolversion: 02.03.11.01.70.09.79.00.00.00
               
               Serial Number: CBD1700979
               Customer Info: Huizhou Desay SV Automotive Co., Ltd.
                              Package: CBD_Vector_SLP2
                              Micro: R7F7016213AFP
                              Compiler: Green Hills 2015.1.7
               
               
               Generator Fwk   : GENy 
               Generator Module: Ccl__core
               
               Configuration   : D:\Renesas_Platform\FAWHQ_C205_Source\FAWHQ_C205_AVM_MCU\Source\vicp\ComplexDriver\CANdriver\tool\CBD1700979 D00 Rh850 GreenHills FAW C205.gny
               
               ECU: 
                       TargetSystem: Hw_Rh850Cpu
                       Compiler:     GreenHills
                       Derivates:    F1L
               
               Channel "Channel0":
                       Databasefile: D:\Renesas_Platform\FAWHQ_C205_Source\FAWHQ_C205_AVM_MCU\Source\vicp\ComplexDriver\CANdriver\tool\ab02_979_C205_CAN1_V0.1_20191120.dbc
                       Bussystem:    CAN
                       Manufacturer: Vector
                       Node:         AVS

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

#if !defined(__CCL_PAR_H__)
#define __CCL_PAR_H__

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "v_cfg.h"
#include "v_def.h"
#include "can_inc.h"
#include "ccl_inc.h"

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/
#ifndef NM_OK
  #define NM_OK 0
#endif

#if !defined ( DRV_API_CALLBACK_TYPE )
  #define DRV_API_CALLBACK_TYPE
#endif


#define CCL_DISABLE_WAKEUP_EV

#define CCL_DISABLE_SLEEP_COND

#define CCL_ENABLE_STOP_TIMEOUT


V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 cclNmWakeUpAble;
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 cclStartIndex[1];
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 cclStopIndex[1];
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 cclUserOffset[kCclNumberOfUser];
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 cclUserMask[kCclNumberOfUser];
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 cclUserChannel[kCclNumberOfUser];
/*** prototypes ***/
extern void CclInitPowerOnFct(void);
extern void CclInitFct(void);
extern void CclSystemShutdownFct(void);
extern void CclNmSleepReqFct(vuint8 network);
extern vuint8 CclNmActiveReqFct(vuint8 network);
extern void CclNmPrepareSleepReqFct(void);
extern void CclInitTrcvFct(void);
extern void CclWakeUpTrcvFct(void);
extern void CclSleepTrcvFct(void);


/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 335188586
      #error "The magic number of the generated file <D:\Renesas_Platform\FAWHQ_C205_Source\FAWHQ_C205_AVM_MCU\Source\vicp\ComplexDriver\CANdriver\tool\gen979\ccl_par.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 335188586
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __CCL_PAR_H__ */

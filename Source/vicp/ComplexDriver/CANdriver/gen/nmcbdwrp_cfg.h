/* -----------------------------------------------------------------------------
  Filename:    nmcbdwrp_cfg.h
  Description: Toolversion: 02.03.11.01.70.09.79.00.00.00
               
               Serial Number: CBD1700979
               Customer Info: Huizhou Desay SV Automotive Co., Ltd.
                              Package: CBD_Vector_SLP2
                              Micro: R7F7016213AFP
                              Compiler: Green Hills 2015.1.7
               
               
               Generator Fwk   : GENy 
               Generator Module: Nm_AsrNmCANbeddedWrapper
               
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

#if !defined(__NMCBDWRP_CFG_H__)
#define __NMCBDWRP_CFG_H__

/* Version */
#define NM_ASRNMCANWRAPPEREXTDLL_VERSION     0x0329u
#define NM_ASRNMCANWRAPPEREXTDLL_RELEASE_VERSION 0x00u
/* Instance properties */
#define kCbdWrpNumberOfChannels              1
#define kCbdWrpNumberOfCanChannels           1
/* Module options */
#define CBDWRP_DISABLE_ASR_ERROR_REPORT
#define CBDWRP_DISABLE_ASSERTIONS
#define CBDWRP_DISABLE_EARLY_BUSOFF_REINIT
#define CBDWRP_DISABLE_ASRNM_BUSOFF_SUPPORT
#define CBDWRP_DISABLE_TESTDEBUG
#define CBDWRP_DISABLE_RESET_BUSOFF_THRESHOLD_COUNTER_ON_ANY_TX_CONFIRMATION
#define CBDWRP_DISABLE_FASTBUSOFFRECOVERY_CHANGE_CALLBACK
/* Channel specific parameters */
#define kCbdWrpBusOffRecoveryTime            19
#define kCbdWrpBusOffRecoveryTimeFast        5
#define kCbdWrpBusOffThreshold               5
#define kCbdWrpCycleTime                     10
/* --------------------- Configuration Data Prototypes --------------------- */
#if defined ( CBDWRP_ADAPTATION_LAYER )
#else
# if ( kCbdWrpNumberOfChannels > 1u )
/* BusOff recovery time parameters. */
extern V_MEMROM0 V_MEMROM1 vuint16 V_MEMROM2 CbdWrpBusOffRecoveryTime[kCbdWrpNumberOfChannels];
extern V_MEMROM0 V_MEMROM1 vuint16 V_MEMROM2 CbdWrpBusOffRecoveryTimeFast[kCbdWrpNumberOfChannels];
extern V_MEMROM0 V_MEMROM1 vuint8  V_MEMROM2 CbdWrpBusOffThreshold[kCbdWrpNumberOfChannels];
extern V_MEMROM0 V_MEMROM1 vuint8  V_MEMROM2 CbdWrpCycleTime[kCbdWrpNumberOfChannels];
# endif
#endif

#if ( kCbdWrpNumberOfChannels != kCbdWrpNumberOfCanChannels )
/* CAN to local NM channel */
extern V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanNm_CanToNmChannelInd[kCbdWrpNumberOfCanChannels];
# if defined ( CBDWRP_ADAPTATION_LAYER )
# else
/* Local NM to CAN channel */
extern V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 CanNm_NmToCanChannelInd[kCbdWrpNumberOfChannels];
# endif
#endif

#if defined ( NM_ASRNMCANWRAPPEREXT_SOURCE ) || defined ( __NMCBDWRP_PAR_C__ )
/* --------------------- Module Data Prototypes --------------------- */
# if defined ( CBDWRP_ADAPTATION_LAYER )
# else
/* BusOff recovery timer. */
extern V_MEMRAM0 V_MEMRAM1 vuint16 V_MEMRAM2 cbdWrpBusOffRecTimer[kCbdWrpNumberOfChannels];
extern V_MEMRAM0 V_MEMRAM1 vuint8  V_MEMRAM2 cbdWrpBusOffThresholdCounter[kCbdWrpNumberOfChannels];

#  if defined ( CBDWRP_ENABLE_EARLY_BUSOFF_REINIT )
/* Indication Flag that the CAN Driver is in BusOff state */
extern V_MEMRAM0 V_MEMRAM1 vuint8 V_MEMRAM2 cbdWrpDrvCanIsBusOff[kCbdWrpNumberOfChannels];
#  endif
# endif
#endif

/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 335188586
      #error "The magic number of the generated file <D:\Renesas_Platform\FAWHQ_C205_Source\FAWHQ_C205_AVM_MCU\Source\vicp\ComplexDriver\CANdriver\tool\gen979\nmcbdwrp_cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 335188586
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __NMCBDWRP_CFG_H__ */

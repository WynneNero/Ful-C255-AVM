/* -----------------------------------------------------------------------------
  Filename:    v_cfg.h
  Description: Toolversion: 02.03.11.01.70.09.79.00.00.00
               
               Serial Number: CBD1700979
               Customer Info: Huizhou Desay SV Automotive Co., Ltd.
                              Package: CBD_Vector_SLP2
                              Micro: R7F7016213AFP
                              Compiler: Green Hills 2015.1.7
               
               
               Generator Fwk   : GENy 
               Generator Module: GenTool_GenyVcfgNameDecorator
               
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

#if !defined(__V_CFG_H__)
#define __V_CFG_H__

#ifndef VGEN_GENY
#define VGEN_GENY
#endif

#ifndef GENy
#define GENy
#endif

#ifndef SUPPLIER_CANBEDDED
#define SUPPLIER_CANBEDDED                   30
#endif

/* -----------------------------------------------------------------------------
    &&&~ General Switches
 ----------------------------------------------------------------------------- */

#ifndef V_OSTYPE_OSEK
#define V_OSTYPE_OSEK
#endif



/* -----------------------------------------------------------------------------
    &&&~ Processor specific
 ----------------------------------------------------------------------------- */

#ifndef C_CPUTYPE_32BIT
#define C_CPUTYPE_32BIT
#endif


#ifndef V_CPUTYPE_BITARRAY_32BIT
#define V_CPUTYPE_BITARRAY_32BIT
#endif


#ifndef C_CPUTYPE_LITTLEENDIAN
#define C_CPUTYPE_LITTLEENDIAN
#endif


#ifndef C_CPUTYPE_BITORDER_LSB2MSB
#define C_CPUTYPE_BITORDER_LSB2MSB
#endif


#ifndef V_DISABLE_USE_DUMMY_FUNCTIONS
#define V_DISABLE_USE_DUMMY_FUNCTIONS
#endif


#ifndef V_ENABLE_USE_DUMMY_STATEMENT
#define V_ENABLE_USE_DUMMY_STATEMENT
#endif


#ifndef C_COMP_GHS_RH850_RSCAN
#define C_COMP_GHS_RH850_RSCAN
#endif


#ifndef V_CPU_RH850
#define V_CPU_RH850
#endif

#ifndef V_COMP_GHS
#define V_COMP_GHS
#endif

#ifndef V_COMP_GHS_RH850
#define V_COMP_GHS_RH850
#endif

#ifndef V_PROCESSOR_F1L
#define V_PROCESSOR_F1L
#endif


#ifndef C_PROCESSOR_F1L
#define C_PROCESSOR_F1L
#endif




/* -----------------------------------------------------------------------------
    &&&~ Used Modules
 ----------------------------------------------------------------------------- */

#ifndef VGEN_ENABLE_VSTDLIB
#define VGEN_ENABLE_VSTDLIB
#endif

#ifndef VSTD_ENABLE_DEFAULT_INTCTRL
#define VSTD_ENABLE_DEFAULT_INTCTRL
#endif

#ifndef VSTD_ENABLE_GLOBAL_LOCK
#define VSTD_ENABLE_GLOBAL_LOCK
#endif

#ifndef VSTD_DISABLE_DEBUG_SUPPORT
#define VSTD_DISABLE_DEBUG_SUPPORT
#endif

#ifndef VSTD_ENABLE_LIBRARY_FUNCTIONS
#define VSTD_ENABLE_LIBRARY_FUNCTIONS
#endif


#define VGEN_ENABLE_DIAG_CANDESC_UDS
#define VGEN_ENABLE_CCL
#define VGEN_ENABLE_CAN_DRV
#define C_ENABLE_CAN_CHANNELS
#define V_BUSTYPE_CAN
#define VGEN_ENABLE_IL_VECTOR
#define VGEN_ENABLE_NM_ASR_IF
#define VGEN_ENABLE_NM_ASRNMCANWRAPPEREXT
#define VGEN_ENABLE_NM_ASR_CAN
#define VGEN_ENABLE_TP_ISO_MC


#ifndef kVNumberOfIdentities
#define kVNumberOfIdentities                 1
#endif

#ifndef tVIdentityMsk
#define tVIdentityMsk                        vuint8
#endif

#ifndef kVIdentityIdentity_0
#define kVIdentityIdentity_0                 (vuint8) 0
#endif

#ifndef VSetActiveIdentity
#define VSetActiveIdentity(identityLog)
#endif

#ifndef V_ACTIVE_IDENTITY_MSK
#define V_ACTIVE_IDENTITY_MSK                1
#endif

#ifndef V_ACTIVE_IDENTITY_LOG
#define V_ACTIVE_IDENTITY_LOG                0
#endif


#define DIAG_API_CALL_TYPE
#define DIAG_API_CALLBACK_TYPE
#define DIAG_INTERNAL_CALL_TYPE
/* -----------------------------------------------------------------------------
    &&&~ Paging support
 ----------------------------------------------------------------------------- */

#define CCL_API_CALL_TYPE
#define CCL_API_CALLBACK_TYPE
#define CCL_INTERNAL_CALL_TYPE


#define TP_API_CALL_TYPE
#define TP_API_CALLBACK_TYPE
#define TP_INTERNAL_CALL_TYPE

/* -----------------------------------------------------------------------------
    &&&~ ExtendedAsrVersionCheck
 ----------------------------------------------------------------------------- */

/* V_SUPPRESS_EXTENDED_VERSION_CHECK */


/* -----------------------------------------------------------------------------
    &&&~ Optimization
 ----------------------------------------------------------------------------- */

#ifndef V_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define V_ATOMIC_BIT_ACCESS_IN_BITFIELD      STD_OFF
#endif

#ifndef V_ATOMIC_VARIABLE_ACCESS
#define V_ATOMIC_VARIABLE_ACCESS             16
#endif




#ifndef VGEN_ENABLE_VSTDLIB
/* Diag_CanDesc requires VSTDLIB */
#define VGEN_ENABLE_VSTDLIB
#endif

#ifndef C_CLIENT_VECTOR
#define C_CLIENT_VECTOR
#endif

#ifndef __AVS__
#define __AVS__
#endif

/* -----------------------------------------------------------------------------
    &&&~ Compatibility defines for ComSetCurrentECU
 ----------------------------------------------------------------------------- */

#ifndef kComNumberOfNodes
#define kComNumberOfNodes                    kVNumberOfIdentities
#endif

#ifndef ComSetCurrentECU
#define ComSetCurrentECU                     VSetActiveIdentity
#endif

#ifndef comMultipleECUCurrent
#define comMultipleECUCurrent                vActiveIdentityLog
#endif



#define C_VERSION_REF_IMPLEMENTATION         0x150u


#ifndef VGEN_ENABLE_VSTDLIB
/* DrvCan__baseRi15 requires VSTDLIB */
#define VGEN_ENABLE_VSTDLIB
#endif

#ifndef VGEN_ENABLE_VSTDLIB
#define VGEN_ENABLE_VSTDLIB
#endif


#ifndef VGEN_ENABLE_VSTDLIB
/* TpMC requires VSTDLIB */
#define VGEN_ENABLE_VSTDLIB
#endif


#define ApplCanCancelNotification   IlCanCancelNotification

//#ifndef C_ENABLE_ECU_SWITCH_PASS
//#define C_ENABLE_ECU_SWITCH_PASS
//#endif /* C_ENABLE_ECU_SWITCH_PASS*/

/* By the use of this defines it is possible to change the 'rx_limit' / 'tx_limit'  */
/* Please note that it is not recommended to change these values! */
#define RX_CNT_MAX  ((vuint8)4)
#define TX_CNT_MAX  ((vuint8)8)

/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 335188586
      #error "The magic number of the generated file <D:\Renesas_Platform\FAWHQ_C205_Source\FAWHQ_C205_AVM_MCU\Source\vicp\ComplexDriver\CANdriver\tool\gen979\v_cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 335188586
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __V_CFG_H__ */

/* -----------------------------------------------------------------------------
  Filename:    tp_cfg.h
  Description: Toolversion: 02.03.11.01.70.09.79.00.00.00
               
               Serial Number: CBD1700979
               Customer Info: Huizhou Desay SV Automotive Co., Ltd.
                              Package: CBD_Vector_SLP2
                              Micro: R7F7016213AFP
                              Compiler: Green Hills 2015.1.7
               
               
               Generator Fwk   : GENy 
               Generator Module: Tp_Iso15765
               
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

#if !defined(__TP_CFG_H__)
#define __TP_CFG_H__

#include "can_par.h"
#define TP_MEMORY_MODEL_DATA

#define TP_ENABLE_SINGLE_MSG_OBJ
#define TP_ISO15765DLL_VERSION               0x0235u
#define TP_ISO15765DLL_RELEASE_VERSION       0x01u

#define kTpNumberOfCanChannels               1
#ifndef kTpOn
#define kTpOn                                1
#endif

#ifndef kTpOff
#define kTpOff                               0
#endif

#define TP_TYPE_MULTI_MULTIPLE_ADDRESSING
struct tTpCopyToCanInfoStruct_s
{
  canuint8                       Channel;     /* TP Channel                           */
  TxDataPtr                      pDestination;/* Pointer to destination buffer        */
  TP_MEMORY_MODEL_DATA canuint8* pSource;     /* Pointer to source buffer (if linear) */
  canuint16                      Length;      /* The maximum length to copy           */
};
typedef struct tTpCopyToCanInfoStruct_s tTpCopyToCanInfoStruct;
typedef struct tTpCopyToCanInfoStruct_s *TpCopyToCanInfoStructPtr;

#define TP_USE_ISO_COMPLIANCE                kTpOn
#define TP_USE_FAST_PRECOPY                  kTpOff
#define TP_USE_DIAGPRECOPY                   kTpOff
#define TP_CAN_CHANNEL_INDEX                 0
#define TP_ENABLE_ISO_15765_2_2
#define TP_DISABLE_ASR_SINGLE_TP
#define TP_DISABLE_OBD_PRECOPY

/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

#define TP_USE_EXTENDED_API_BS               kTpOff
#define TP_USE_EXTENDED_API_STMIN            kTpOff
#define TP_USE_TX_OF_FC_IN_ISR               kTpOn
#define TP_USE_OVERRUN_INDICATION            kTpOff
#define TP_USE_ONLY_FIRST_FC                 kTpOn
#define TP_USE_FAST_TX_TRANSMISSION          kTpOff
#define TP_USE_QUEUE_IN_ISR                  kTpOn
#define TP_USE_NO_STMIN_AFTER_FC             kTpOff
#define MEMORY_NEAR_TP_SAVE                  MEMORY_NEAR
#define TP_USE_TX_HANDLE_CHANGEABLE          kTpOff
#define TP_USE_GATEWAY_API                   kTpOff
#define TP_USE_RX_CHANNEL_WITHOUT_FC         kTpOff
#define TP_USE_TX_CHANNEL_WITHOUT_FC         kTpOff
#define TP_USE_OLD_STMIN_CALCULATION         kTpOff
#define TP_USE_VARIABLE_RX_DLC_CHECK         kTpOn
#define TP_USE_FIX_RX_DLC_CHECK              kTpOff
#define TP_USE_PADDING                       kTpOn
#define TP_PADDING_PATTERN                   0x00
#define TP_USE_VARIABLE_DLC                  kTpOff
#define TP_DISABLE_IGNORE_FC_RES_STMIN
#define TP_DISABLE_CANCEL_FC_RES_STMIN
#define TP_DISABLE_IGNORE_FC_OVFL
#define TP_DISABLE_WAIT_FOR_CORRECT_SN
#define TP_DISABLE_SINGLE_CHAN_MULTICONN
#define TP_DISABLE_FC_WAIT
#define TP_USE_UNEXPECTED_FC_CANCELATION     kTpOff
#define TP_DISABLE_EXT_COPYFROMCAN_API


/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

#define TP_USE_NORMAL_ADDRESSING             kTpOn
#define TP_USE_NORMAL_FIXED_ADDRESSING       kTpOff
#define TP_USE_EXTENDED_ADDRESSING           kTpOn
#define TP_USE_MIXED_11_ADDRESSING           kTpOff
#define TP_USE_MIXED_29_ADDRESSING           kTpOff
#define TP_DISABLE_SINGLE_CHANNEL_TP
#define TP_ENABLE_MULTIPLE_ADDRESSING
#define TP_DISABLE_MULTIPLE_NODES
#define TP_DISABLE_USER_CHECK
#define TP_DISABLE_INTERNAL_CHECK
#define TP_DISABLE_GEN_CHECK
#define TP_DISABLE_RUNTIME_CHECK
#define TP_DISABLE_CANFD
#define TP_DISABLE_LONG_FIRST_FRAMES


/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

#define TP_USE_PRE_COPY_CHECK                kTpOff

#define TPC_ENABLE_DYN_TX_OBJECTS
#define TPC_ENABLE_DYN_TX_ID
#define TPC_ENABLE_DYN_TX_DLC
#define TPC_DISABLE_DYN_TX_DATAPTR
#define TPC_DISABLE_DYN_TX_PRETRANS_FCT
#define TPC_DISABLE_DYN_TX_CONF_FCT
#define TP_USE_APPL_PRECOPY                  kTpOn
#define TP_USE_FREE_CHANNEL_SEARCH           kTpOn
#define TP_USE_CUSTOM_RX_MEMCPY              kTpOff
#define TP_DISABLE_FUNCTIONAL_FC_WAIT
#define TP_LOWEST_FUNCTIONAL_ADDRESS         0x00
#define TP_HIGHEST_FUNCTIONAL_ADDRESS        0xFF
#define TP_RX_BASE_ADDRESS                   0x00


/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

#define TP_USE_STMIN_OF_FC                   kTpOn
#define TP_USE_TP_TRANSMIT_QUEUE             kTpOn
#define TP_USE_DYN_ID                        kTpOn
#define TP_USE_CUSTOM_TX_MEMCPY              kTpOn


/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

#define TP_USE_WAIT_FRAMES                   kTpOff
#define TP_USE_MULTIPLE_BASEADDRESS          kTpOff
#define TP_USE_PRE_DISPATCHED_MODE           kTpOff


/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

#define TP_USE_EXT_IDS_FOR_NORMAL            kTpOff
#define TP_USE_MIXED_IDS_FOR_NORMAL          kTpOff
#define TP_USE_MULTIPLE_ECU_NR               kTpOff
#define TP_USE_MULTIPLE_ECU                  kTpOff
#define TP_TX_ECU_NR(tpChannel)              0x00
#define TP_RX_ECU_NR(tpChannel)              0x00
#define kTpPhysPGNNormalFixed                0xDA
#define kTpPhysPrioNormalFixed               0x06
#define kTpPhysPGNMixed29                    0xCE
#define kTpPhysPrioMixed29                   0x06
#define TP_ECU_NUMBER                        0x00


/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

#define TP_DISABLE_MIN_TIMER
#define kTpTxChannelCount                    1
#define kTpRxChannelCount                    1

#define TpMemCpy                             memcpy
#define TpTxCallCycle                        10
#define TpRxCallCycle                        10

#define kBSRequested                         0
#define kTpTxConfirmationTimeout             11
#define kTpRxConfirmationTimeout             11
#define TpSTMin                              10
#define TpTxTimeoutFC                        8
#define TpRxTimeoutCF                        16
#define TpTxTransmitCF                       3
#define __ApplTpPreCopyCheckFunction(x)
#define __ApplTpPrecopyCheckFCFunctional(tpCurrentTargetAddress)
#define TP_DISABLE_CHECKTA_COMPATIBILITY
#define __ApplTpPrecopy(target)              DescCheckTA(target)
typedef enum
{
  kTpNone = 0,
  kTpPhysical = 1,
  kTpFunctional = 2
} t_ta_type;
t_ta_type DescCheckTA(vuint8 tpCurrentTargetAddress);


#define kTpTxHandle CanTxTxDynamicMsg0

#define kTpTxData TxDynamicMsg0._c


/* function prototypes */
void ApplTpRxIndication(canuint8 tpChannel, canuint16 datLen);
void ApplTpRxErrorIndication(canuint8 tpChannel, canuint8 errNo);
void ApplTpTxConfirmation(canuint8 tpChannel, canuint8 state);
void ApplTpRxFF(canuint8 tpChannel);
void ApplTpTxNotification(canuint8 tpChannel, canuint8 datLen);
canuint8* ApplTpRxGetBuffer(canuint8 tpChannel, canuint16 datLen);
canuint8 ApplTxErrorIndication(canuint8 tpChannel, canuint8 errNo);
vuint8 ApplCopyToCAN(TpCopyToCanInfoStructPtr infoStruct);
void ApplTpRxCF(canuint8 tpChannel);

#define __ApplTpRxIndication(tpChannel, datLen) (ApplTpRxIndication(tpChannel, datLen))
#define __ApplTpRxErrorIndication(tpChannel, errNo) (ApplTpRxErrorIndication(tpChannel, errNo))
#define __ApplTpTxConfirmation(tpChannel, state) (ApplTpTxConfirmation(tpChannel, state))
#define __ApplTpRxSF(tpChannel) 
#define __ApplTpRxFF(tpChannel) (ApplTpRxFF(tpChannel))
#define __ApplTpRxCF(tpChannel) 
#define __ApplTpTxNotification(tpChannel, datLen) (ApplTpTxNotification(tpChannel, datLen))
#define __ApplTpTxCanMessageTransmitted(tpChannel) 
#define __ApplTpTxFC(tpChannel) 
#define __ApplTpRxGetBuffer(tpChannel, datLen) (ApplTpRxGetBuffer(tpChannel, datLen))
#define __ApplTpTxErrorIndication(tpChannel, errNo) (ApplTxErrorIndication(tpChannel, errNo))
#define __ApplTpTxCopyToCAN(infoStruct) (ApplCopyToCAN(infoStruct))
#define __ApplTpRxCopyFromCAN(tpChannel, src, datLen) 
#define __ApplTpRxCanMessageTransmitted(tpChannel) (ApplTpRxCF(tpChannel))
#define __ApplTpTxDelayFinished(tpChannel, state) 

#define TpTransmitDiag(dataPtr, dataLen) TpTransmit(0, dataPtr, dataLen)

#define DESC_ENABLE_OVERRIDE_TP_MA_CHECK

/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 335188586
      #error "The magic number of the generated file <D:\Renesas_Platform\FAWHQ_C205_Source\FAWHQ_C205_AVM_MCU\Source\vicp\ComplexDriver\CANdriver\tool\gen979\tp_cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 335188586
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __TP_CFG_H__ */

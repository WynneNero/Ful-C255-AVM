
/*****************************************************************************
| Project Name: Node-Management Basic
|    File Name: nm_basic.h
|
|  Description: implementation of node management for CAN Class C ECUs
|
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2016 by Vector Informatik GmbH.           All rights reserved.
|
| COPYRIGHT NOTE / Urheberrechtlicher Vermerk
| 
|
| This software is copyright protected and proprietary 
| to Vector Informatik GmbH. Vector Informatik GmbH 
| grants to you only those rights as set out in the 
| license conditions. All other rights remain with 
| Vector Informatik GmbH.
|
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     ------------------------------------
| Bs           Thomas Balster            Vector Informatik GmbH
| Et           Thomas Ebert              Vector Informatik GmbH
| Pet          Thomas Petrus             Vector Informatik GmbH
| Dhf          Daniel Hof                Vector Informatik GmbH
| vismpf       Marco Pfalzgraf           Vector Informatik GmbH
| vismno       Martin Nonnenmann         Vector Informatik GmbH
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date         Ver   Author    Description
| ----------   ---   -------   -----------------------------------------------
| 2003-10-31   1.0   Et,Pet    creation
| 2004-09-06   1.01  Bs        copyright paragraph changed into english version
|                              ESCAN00009376: adapt the names of the constants which store the version numbers
|                              ESCAN00009408: no changes in this file
|                              ESCAN00009426: no changes in this file
|                              ESCAN00009681: no changes in this file
|                              ESCAN00009705: add callback functions for transceiver handling
| 2004-10-13   1.02  Bs        ESCAN00009377: no changes in this file
|                              ESCAN00009874: no changes in this file
|                              ESCAN00009877: no changes in this file
|                              ESCAN00009878: Naming Conventions: change version defines to serve the Vector naming rules
|                              ESCAN00009910: no changes in this file
|                              ESCAN00009911: no changes in this file
|                              ESCAN00009912: no changes in this file
| 2005-04-05   1.03  Bs        ESCAN00010780: no changes in this file
|                              ESCAN00011711: no changes in this file
|                              ESCAN00011712: add the new BusOff recovery algorithm 'extended'
|                              ESCAN00011728: NM start and stop handling must be configurable
|                              ESCAN00011765: no changes in this file
|                              ESCAN00011785: add assertions for runtime checks
|                              ESCAN00011786: add a 'get Net state' function
|                              ESCAN00011787: add const pragma to support IAR linker
| 2005-04-21   1.04  Bs        ESCAN00011990: change memory qualifier of version number constants
|                              ESCAN00011994: change datatype of configuration fields for multi channel support
|                              ESCAN00012062: standardization of NMbasic defines
|                              ESCAN00012063: add support of indexed and indirected NM channels for use in multi channel systems
|                              ESCAN00012064: no changes in this file
|                              ESCAN00012065: no changes in this file
|                              ESCAN00012066: no changes in this file
|                              ESCAN00012098: no changes in this file
|                              ESCAN00012099: no changes in this file
|                              ESCAN00012104: no changes in this file
| 2005-07-06   1.05  Bs        ESCAN00012094: no changes in this file
|                              ESCAN00012094: just check the indirection switch instead in combination with indexed NM
|                              ESCAN00012095: add interface to AsrNm
|                              ESCAN00012156: no changes in this file
|                              ESCAN00012158: no changes in this file
|                              ESCAN00012490: include of configuration header file added
|                              ESCAN00012670: two compiler switches corrected
|                              ESCAN00012671: no changes in this file
|                              ESCAN00012672: no changes in this file
|                              ESCAN00012786: no changes in this file
|                              ESCAN00012853: Add return value to application callback function 
|                                             'ApplNmBasicSwitchTransceiverOff()'
|                              ESCAN00012854: no changes in this file
| 2005-07-14   1.06  Bs        ESCAN00012903: no changes in this file
|                              ESCAN00012904: no changes in this file
|                              ESCAN00012905: no changes in this file
|                              ESCAN00012906: Delete the define 'kNmBasicErrStateNotRunInTxConf'
|                              ESCAN00012919: no changes in this file
|                              ESCAN00012920: no changes in this file
|                              ESCAN00012926: no changes in this file
| 2005-07-25   1.07  Bs        ESCAN00012883: no changes in this file
|                              ESCAN00013016: change automatic version number detection
|                              ESCAN00013091: no changes in this file
| 2006-02-16   1.08  Bs        ESCAN00014289: no changes in this file
|                              ESCAN00014705: no changes in this file
|                              ESCAN00015623: Assertion-Defines 'kNmBasicErrStateNotOkInStart' and 
|                                             'kNmBasicErrStateNotOkInStop' not used anymore
| 2006-03-14   1.09  Pet       ESCAN00015663: initialization of multi NM-channel systems corrected for no channel indirection
| 2006-04-26   1.10  Bs        Assertion defines reworked
|                              ESCAN00015987: no changes in this file
|                              ESCAN00016185: no changes in this file
|                              ESCAN00016186: no changes in this file
|                              ESCAN00016211: no changes in this file
| 2006-06-08   1.11  Bs        ESCAN00016466: no changes in this file
|                              ESCAN00016556: no changes in this file
| 2006-08-03   1.12  Dhf       ESCAN00017158: no changes in this file
|                              ESCAN00016667: no changes in this file
| 2006-10-05   1.13  Dhf       ESCAN00017908: Adaption of Nm_PwrTrainBasic to 
|                              support the BusOff algorithm 'time supervised'
| 2007-01-24   1.14  Dhf       ESCAN00012093: changes just in source file
|                              ESCAN00012097: add assertions to check the generated tabels during initialization
|                              ESCAN00018548: changes just in source file
|                              ESCAN00018971: Nm Basic uses incorrect preprocessor switch: VGEN_ENABLE_NM_ASR_GENERIC replaced by VGEN_ENABLE_NM_ASR_CAN
|                              ESCAN00018298: changes just in source file
|                              ESCAN00019119: added BusOff additions and Tx-Observation-Handling
|                              ESCAN00019593: changes just in source file
| 2008-11-10   1.15  Dhf       ESCAN00023008: changes in source file only
|                              ESCAN00025822: changes in source file only
|                              ESCAN00030715: changes in source file only
|                              ESCAN00031037: changes in source file only
|                              ESCAN00031155: Adapt NM Basic to support QNX context switch
|                              ESCAN00031157: added external CanOnline/Offline handling
|                              ESCAN00031403: changes in source file only
| 2009-02-04   1.15.01 Dhf     ESCAN00032403: changes in source file only
| 2009-10-19   1.15.02 Dhf     ESCAN00034728: changes in source file only
|                              ESCAN00038780: changes in source file only
| 2010-08-18   1.15.03 Dhf     ESCAN00044450: changes in source file only
| 2011-11-23   1.15.04 vismpf  ESCAN00051839: changes in source file only
| 2012-10-08   1.15.05 vismpf  ESCAN00061225: corrected encapsulation of bNmBasicStateRequest and bNmBasicBusOffRepaired
| 2013-03-21   1.15.06 vismpf  ESCAN00066076: corrected compiler abstraction of NmBasicCanToNmIndirection and NmBasicNmToCanIndirection
| 2013-05-21   1.16.00 vismpf  ESCAN00066190: adapted usage of Compiler Memory Qualifier V_MEMROM0
|                              ESCAN00067505: support TML 'three-step' BusOff recovery algorithm
|                              ESCAN00067591: removed code duplication for multi channel use case
|                              ESCAN00067678: removed declaration of NmBasicCanBusOff
|                              ESCAN00067823: no changes in this file
| 2014-03-24   1.17.00 vismpf  ESCAN00074418: extended encapsulation with C_CLIENT_BMWAG
|                              ESCAN00081008: no changes in this file
| 2015-10-07   1.18.00 vismpf  ESCAN00085715: Corrected declaration of ApplNmBasicCanOnline/Offline
|                              ESCAN00085728: Adapted forwarding of Tx Observation callbacks to application
| 2015-11-02   1.19.00 vismpf  ESCAN00086224: Support longer BusOff Recovery Timeouts
|                              ESCAN00086247: no changes in this file
| 2016-04-20   1.19.01 vismno  ESCAN00089618: increased bugfix version due to changed filter rules
|****************************************************************************/

#ifndef NMBASIC_IMPL_H
#define NMBASIC_IMPL_H

#include "v_cfg.h"

#if defined ( VGEN_GENY )
# include "v_inc.h"
#else
# include "can_inc.h"
#endif

#include "nmb_cfg.h"

/***************************************************************************
* defines
****************************************************************************/
/* node management version */
/* ##V_CFG_MANAGEMENT ##CQProject : Nm_PwrTrainBasic CQComponent : Implementation */
#define NM_PWRTRAINBASIC_VERSION 0x0119
#define NM_PWRTRAINBASIC_RELEASE_VERSION 0x01

#define NM_TYPE_NMBASIC

/* NM states */
#define NMBASIC_STATE_POWER_OFF      0x00
#define NMBASIC_STATE_TX_ERROR       0x01 /* ESCAN00019119 */
#define NMBASIC_STATE_STOP           0x02
#define NMBASIC_STATE_RUN            0x03
#define NMBASIC_STATE_BUSOFF         0x04

/* different handling of channel parameter in prototypes and funcion calls */
/* used for NM and CAN Driver functions */
#if defined ( NMBASIC_ENABLE_INDEXED_NM )
# if defined ( C_MULTIPLE_RECEIVE_CHANNEL )
#  define NMBASIC_CHANNEL_NMTYPE_ONLY     CanChannelHandle channel
#  define NMBASIC_CHANNEL_NMTYPE_FIRST    CanChannelHandle channel,
#  define NMBASIC_CHANNEL_NMPARA_ONLY     channel
#  define NMBASIC_CHANNEL_NMPARA_FIRST    channel,

#  if defined ( NMBASIC_ENABLE_CHANNEL_INDIRECTION )
#   define NMBASIC_CHANNEL_CANTYPE_ONLY  CanChannelHandle channel
#   define NMBASIC_CHANNEL_CANTYPE_FIRST CanChannelHandle channel,
#   define NMBASIC_CHANNEL_CANPARA_ONLY  NmBasicNmToCanIndirection[channel]
#   define NMBASIC_CHANNEL_CANPARA_FIRST NmBasicNmToCanIndirection[channel],
#  else
#   define NMBASIC_CHANNEL_CANTYPE_ONLY  NMBASIC_CHANNEL_NMTYPE_ONLY
#   define NMBASIC_CHANNEL_CANTYPE_FIRST NMBASIC_CHANNEL_NMTYPE_FIRST
#   define NMBASIC_CHANNEL_CANPARA_ONLY  NMBASIC_CHANNEL_NMPARA_ONLY
#   define NMBASIC_CHANNEL_CANPARA_FIRST NMBASIC_CHANNEL_NMPARA_FIRST
#  endif

#  define NMBASIC_CHANNEL_APPLTYPE_ONLY   NMBASIC_CHANNEL_NMTYPE_ONLY
#  define NMBASIC_CHANNEL_APPLTYPE_FIRST  NMBASIC_CHANNEL_NMTYPE_FIRST
#  define NMBASIC_CHANNEL_APPLPARA_ONLY   NMBASIC_CHANNEL_CANPARA_ONLY
#  define NMBASIC_CHANNEL_APPLPARA_FIRST  NMBASIC_CHANNEL_CANPARA_FIRST
# else
#  error "Configuration error in NMBASIC: NM indexed on driver without C_MULTIPLE_RECEIVE_CHANNEL not possible!"
# endif
#else  /* NMBASIC_ENABLE_INDEXED_NM */
# define NMBASIC_CHANNEL_NMTYPE_ONLY         void  /* PRQA S 3460 */ /* MD_CBD_19.4 */
# define NMBASIC_CHANNEL_NMTYPE_FIRST
# define NMBASIC_CHANNEL_NMPARA_ONLY
# define NMBASIC_CHANNEL_NMPARA_FIRST

# if defined ( C_MULTIPLE_RECEIVE_CHANNEL )
#  define NMBASIC_CHANNEL_CANTYPE_ONLY      CanChannelHandle channel
#  define NMBASIC_CHANNEL_CANTYPE_FIRST     CanChannelHandle channel,

#  if defined ( NMBASIC_CAN_CHANNEL )
#   define NMBASIC_CHANNEL_CANPARA_ONLY    NMBASIC_CAN_CHANNEL
#   define NMBASIC_CHANNEL_CANPARA_FIRST   NMBASIC_CAN_CHANNEL,
#  else
#   if ( cNmBasicNrOfChannels > 1 )
#    error "Configuration error in NMBASIC: NM non indexed on more than one channels with C_MULTIPLE_RECEIVE_CHANNEL not possible!"
#   else
#    define NMBASIC_CHANNEL_CANPARA_ONLY  0
#    define NMBASIC_CHANNEL_CANPARA_FIRST 0,
#   endif
#  endif
# else
#  define NMBASIC_CHANNEL_CANTYPE_ONLY      NMBASIC_CHANNEL_NMTYPE_ONLY
#  define NMBASIC_CHANNEL_CANTYPE_FIRST     NMBASIC_CHANNEL_NMTYPE_FIRST
#  define NMBASIC_CHANNEL_CANPARA_ONLY      NMBASIC_CHANNEL_NMPARA_ONLY
#  define NMBASIC_CHANNEL_CANPARA_FIRST     NMBASIC_CHANNEL_NMPARA_FIRST
# endif

# define NMBASIC_CHANNEL_APPLTYPE_ONLY       NMBASIC_CHANNEL_NMTYPE_ONLY
# define NMBASIC_CHANNEL_APPLTYPE_FIRST      NMBASIC_CHANNEL_NMTYPE_FIRST
# define NMBASIC_CHANNEL_APPLPARA_ONLY
# define NMBASIC_CHANNEL_APPLPARA_FIRST
#endif  /* NMBASIC_ENABLE_INDEXED_NM */

#if defined ( NMBASIC_ENABLE_INDEXED_NM )
# define NMBASICVAR_CH_DEF(var)               ((var)[cNmBasicNrOfChannels])  /* PRQA S 3453 */ /* MD_CBD_19.7 */
# define NMBASICVAR(var)                      ((var)[channel])  /* PRQA S 3453 */ /* MD_CBD_19.7 */
#else
# define NMBASICVAR_CH_DEF(var)               (var)  /* PRQA S 3453 */ /* MD_CBD_19.7 */
# define NMBASICVAR(var)                      (var)  /* PRQA S 3453 */ /* MD_CBD_19.7 */
#endif

/***************************************************************************/
/* error codes for ApplNmBasicFatalError                                   */
/***************************************************************************/
/* error codes to check generated tables */
/* There are gaps in the assertion numbering. These gaps belong to former assertions which were deleted meanwhile. */
#if (defined NMBASIC_ENABLE_SOFTWARE_CHECK)
# define kNmBasicErrStateUndefined                  0x01u /* an undefined state is detected in the NM state machine */

/* ESCAN00012097 */
# define kNmBasicErrInitObjOutOfRange               0x02u /* the initialization object is out of range */

# if( defined(NMBASIC_BUSOFF_RECOV_DELAYED) || defined(NMBASIC_BUSOFF_RECOV_EXTENDED) || defined(NMBASIC_BUSOFF_RECOV_THREE_STEP) )
#  define kNmBasicErrBusOffFastTimeOutOfRange       0x03u /* the fast BusOff recovery time is out of range */
# endif

# if defined(NMBASIC_BUSOFF_RECOV_EXTENDED)
#  define kNmBasicErrBusOffFastSlowTimeOutOfRange   0x04u /* the change-from-fast-to-slow BusOff recovery time is out of range */
#  define kNmBasicErrFastLargerSlowTime             0x05u
# endif

# if defined(NMBASIC_BUSOFF_RECOV_THREE_STEP)
#  define kNmBasicErrBusOffImmediateTimeOutOfRange  0x06u /* the immediate BusOff recovery time is out of range */
# endif

# if( defined(NMBASIC_BUSOFF_RECOV_EXTENDED) || defined(NMBASIC_BUSOFF_RECOV_THREE_STEP) )
#  define kNmBasicErrBusOffSlowTimeOutOfRange       0x07u /* the slow BusOff recovery time is out of range */
#  if defined(NMBASIC_ENABLE_BUSOFFREP_TIMER)
#   define kNmBasicErrBusOffRepTimeOutOfRange       0x08u /* the BusOff repaired time is out of range */
#   define kNmBasicErrBusOffRepairTimeTooSmall      0x09u /* the fast BusOff repaired time is too small */
#  endif
# endif

# define kNmBasicErrWrongChannelHandle              0x0D /* NM Basic API is called for a CAN channel which does not belong to the current identity */
#endif

/**********************************************************************************************************************
  Global typedefs
**********************************************************************************************************************/
/* ESCAN00031155 */

/***************************************************************************/
/* External Data                                                           */
/***************************************************************************/
/* ROM constants for version control */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kNmBasicMainVersion;
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kNmBasicSubVersion;
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kNmBasicReleaseVersion;

/* ROM tables for multi NM channel systems */
#if defined ( NMBASIC_ENABLE_CHANNEL_INDIRECTION )  /* ESCAN00012670 */
/* channel indirection */
V_MEMROM0 extern V_MEMROM1 CanChannelHandle V_MEMROM2 NmBasicCanToNmIndirection[kCanNumberOfChannels];
V_MEMROM0 extern V_MEMROM1 CanChannelHandle V_MEMROM2 NmBasicNmToCanIndirection[cNmBasicNrOfChannels];
#endif

#if( defined NMBASIC_ENABLE_INDEXED_NM )
/* field of init objects */
V_MEMROM0 extern V_MEMROM1 CanInitHandle V_MEMROM2 NmBasicCanInitObject_Field[cNmBasicNrOfChannels];

/* field of task cyles */
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 NmBasicTaskPeriod_Field[cNmBasicNrOfChannels];

# if( defined(NMBASIC_BUSOFF_RECOV_DELAYED) || defined(NMBASIC_BUSOFF_RECOV_EXTENDED) \
  || defined(NMBASIC_BUSOFF_RECOV_TIME_SUPERVISED) || defined(NMBASIC_BUSOFF_RECOV_THREE_STEP) )/* ESCAN00017908 */
/* time distance between HW BusOff event and SW BusOff recovery */
V_MEMROM0 extern V_MEMROM1 vuint16 V_MEMROM2 NmBasicBusOffRecTime_Field[cNmBasicNrOfChannels];
# endif

# if defined(NMBASIC_BUSOFF_RECOV_THREE_STEP)
V_MEMROM0 extern V_MEMROM1 vuint8  V_MEMROM2 NmBasicBusOffImmediateToQuickCnt_Field[cNmBasicNrOfChannels];
V_MEMROM0 extern V_MEMROM1 vuint8  V_MEMROM2 NmBasicBusOffQuickToSlowCnt_Field[cNmBasicNrOfChannels];
V_MEMROM0 extern V_MEMROM1 vuint16 V_MEMROM2 NmBasicBusOffRecTimeImmediate_Field[cNmBasicNrOfChannels];
#endif

# if( defined(NMBASIC_BUSOFF_RECOV_EXTENDED) || defined(NMBASIC_BUSOFF_RECOV_THREE_STEP) )
/* time distance between HW BusOff event and SW BusOff recovery for slow recovery */
V_MEMROM0 extern V_MEMROM1 vuint16 V_MEMROM2 NmBasicBusOffRecTimeSlow_Field[cNmBasicNrOfChannels];
# endif

# if defined(NMBASIC_BUSOFF_RECOV_EXTENDED)
/* time distance between first fast and first slow BusOff recovery */
V_MEMROM0 extern V_MEMROM1 vuint16 V_MEMROM2 NmBasicBusOffFastToSlow_Field[cNmBasicNrOfChannels];
# endif

# if defined(NMBASIC_ENABLE_BUSOFFREP_TIMER)
/* time distance between detected BusOff event and a detection of BusOff repaired */
V_MEMROM0 extern V_MEMROM1 vuint16 V_MEMROM2 NmBasicBusOffRepairedTime_Field[cNmBasicNrOfChannels];
# endif

#endif

/***************************************************************************
* service function prototypes
****************************************************************************/
extern void NmBasicInitPowerOn(void);
extern void NmBasicInit(NMBASIC_CHANNEL_NMTYPE_ONLY);
extern void NmBasicTask(NMBASIC_CHANNEL_NMTYPE_ONLY);
extern void NmBasicStart(NMBASIC_CHANNEL_NMTYPE_ONLY);
extern void NmBasicStop(NMBASIC_CHANNEL_NMTYPE_ONLY);
extern vuint8 NmBasicGetNetState(NMBASIC_CHANNEL_NMTYPE_ONLY);

/***************************************************************************
* callback function prototypes
****************************************************************************/
extern void ApplNmBasicBusOffStart(NMBASIC_CHANNEL_APPLTYPE_ONLY);
extern void ApplNmBasicBusOffEnd(NMBASIC_CHANNEL_APPLTYPE_ONLY);

#if( (defined NMBASIC_BUSOFF_RECOV_EXTENDED) || (defined NMBASIC_BUSOFF_RECOV_THREE_STEP) )
extern void ApplNmBasicBusOffRestart(NMBASIC_CHANNEL_APPLTYPE_ONLY);
#endif
#if (defined NMBASIC_BUSOFF_RECOV_EXTENDED)
extern void ApplNmBasicFirstBusOffSlow(NMBASIC_CHANNEL_APPLTYPE_ONLY);
#endif

/* ESCAN00085728 */
#if( ( (defined NMBASIC_BUSOFF_RECOV_EXTENDED) && (defined NMBASIC_ENABLE_BUSOFFREP_MSG) ) )
extern void ApplNmBasicCanInit( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txHwObjectFirstUsed, CanObjectHandle txHwObjectFirstUnused );
extern void ApplNmBasicTxObjStart( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txHwObject );
extern void ApplNmBasicTxObjConfirmed( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txHwObject );
#endif

extern void ApplNmBasicEnabledCom(NMBASIC_CHANNEL_APPLTYPE_ONLY);
extern void ApplNmBasicSwitchTransceiverOn(NMBASIC_CHANNEL_APPLTYPE_ONLY);

extern void ApplNmBasicDisabledCom(NMBASIC_CHANNEL_APPLTYPE_ONLY);
extern vuint8 ApplNmBasicSwitchTransceiverOff(NMBASIC_CHANNEL_APPLTYPE_ONLY);

#if (defined NMBASIC_ENABLE_SOFTWARE_CHECK)
# if( defined (C_MULTIPLE_RECEIVE_CHANNEL) && defined (NMBASIC_ENABLE_INDEXED_NM) )
extern void ApplNmBasicFatalError(NMBASIC_CHANNEL_APPLTYPE_FIRST vuint8 error);
# else
extern void ApplNmBasicFatalError(vuint8 error);
# endif
#endif

/* ESCAN00031157 */
#if defined ( NMBASIC_ENABLE_EXTERNAL_CANONLINE_HANDLING )
extern void ApplNmBasicCanOnline( NMBASIC_CHANNEL_CANTYPE_ONLY );
extern void ApplNmBasicCanOffline( NMBASIC_CHANNEL_CANTYPE_ONLY );
#endif

#endif  /* NMBASIC_IMPL_H */

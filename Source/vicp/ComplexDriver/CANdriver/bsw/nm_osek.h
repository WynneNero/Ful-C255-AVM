/* ORGANI: STARTSINGLE_OF_MULTIPLE */


/**********************************************************************************************************************
  COPYRIGHT
-----------------------------------------------------------------------------------------------------------------------
  Copyright (c) 2001-2010 by Vector Informatik GmbH.                                             All rights reserved.
 
                This software is copyright protected and proprietary to Vector Informatik GmbH.
                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
                All other rights remain with Vector Informatik GmbH.
-----------------------------------------------------------------------------------------------------------------------
  FILE DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
         File:  Depends on OEM:
                - n_onmdef.h
                - n_vnmdef.h
                - nm_osek.h
      Project:  Nm_DirOsek
       Module:  -
    Generator:  -
  Description:  Vector OSEK Network Management header file
**********************************************************************************************************************/

/**********************************************************************************************************************
  AUTHOR IDENTITY
-----------------------------------------------------------------------------------------------------------------------
  Initials     Name                      Company
-----------------------------------------------------------------------------------------------------------------------
  Bs           Thomas Balster            Vector Informatik GmbH
  Ba           Bernd Baudermann          Vector Informatik GmbH
  Bd           Steffen Braendle          Vector Informatik GmbH
  Be           Christian Baeuerle        Vector Informatik GmbH
  dH           Gunnar de Haan            Vector Informatik GmbH
  Et           Thomas Ebert              Vector Informatik GmbH 
  Fr           Guenther Foerstner        Vector Informatik GmbH
  Fz           Ralf Fritz                Vector Informatik GmbH
  Gu           Alexander Gutlederer      Vector Informatik GmbH 
  Gz           Oliver Garnatz            Vector Informatik GmbH
  HH           Hartmut Hoerner           Vector Informatik GmbH
  Ht           Heike Honert              Vector Informatik GmbH
  Js           Bernd Jesse               Vector Informatik GmbH
  vismas       Markus Schwarz            Vector Informatik GmbH
  Ml           Patrick Markl             Vector Informatik GmbH
  Mr           Rainer Mueller            Vector Informatik GmbH
  visoh        Oliver Hornung            Vector Informatik GmbH
  Pl           Georg Pfluegel            Vector Informatik GmbH
  Rn           Jochen Rein               Vector Informatik GmbH
  Sa           Mishel Shishmanyan        Vector Informatik GmbH
  Si           Bernd Sigle               Vector Informatik GmbH
  Th           Jochen Theuer             Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
-----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Change Id     Description
-----------------------------------------------------------------------------------------------------------------------
  0.01.00   1999-01-25  dH                    Creation
  0.02.00   1999-01-26  dH                    first tests with C167 and VECTOR_NM succesfull
  0.03.00   1999-01-27  dH                    changes according to code review with Ba
  0.04.00   1999-01-28  dH                    optimizations
  0.05.00   1999-02-01  HH                    unchanged
  0.06.00   1999-02-02  dH                    added _0 (first step to multichannel version)
  0.08.00   1999-02-03  dH                    multichannel NM
  1.00.00   1999-04-27  Fr                    Mod. for new definition of multichanneling
  3.00.00   1999-06-18  dH                    some bugfixing within processor defines deTAB
                        dH                    bugfixing: moved some code from single to multiple
                                              -> removed all C_CLIENT_XXX
                                              C_COMP_TASKING_C16x -> C_COMP_TASKING_C16X
                        dH                    merged several branches into single source
                                              corrected some errors in the NM algorithm
                        Ba                    first official version
  3.01.00   1999-07-02  dH                    changed NmPrecopy: no statement before variable declarations
                                              added channel at CanEcuNumber&=0x1f within NmPrecopy
                                              added nmSendmess to multican define section
                        Ba                    CanInterruptDisable/Restore channel dependent
                        Si                    changes in prototype of ApplWriteWakeUpInfo
                        Ba                    CANNWM channel 0 also added for nmRecvMess macro
  3.10.00   1999-12-06  HH                    adapted to automatic gentool
  3.11.00   1999-12-07  HH                    enable selective disabling of channels by means of NM_TYPE_NONE
            1999-12-13  Be                    Compatibility for SINGLE_/MULTIPLE_RECEIVE_BUFFER
  3.12.00   2000-02-28  dH                    adaptation to new GenTool CANgen
                                              renamed callback functions to ApplNm...
                                              renamed timing parameters to NM_COUNT...
                                              changed NM_NumberOfConfigNodes to NM_NUMBER_OF_CONFIG_NODES
                                              changed NM_NumberOfConfigBytes to NM_NUMBER_OF_CONFIG_BYTES
                                              added plausibility checks
  3.15.00   2000-02-15  Mr                    changes according to DC-ONM ver. 3.14d
                        Mr                    StateNetSleepInd, PreNetSleepInd (DC-ONM) implemented
                        Mr                    Userdata-Protocol (UDP for DC-ONM) implemented
  3.16.00   2000-04-10  Rn                    conditional check RANGES
            2000-04-12  Fz                    added C_COMP_NEC_V85X
  3.17.00   2000-05-30  Gz                    unchanged
  3.18.00   2000-06-02  Et                    range mechanism not necessary for C_COMP_FJVGC
  3.20.00   2000-08-15  Gu                    adapted prototypes for ApplCanErrorPinSend()/Receive()
            2000-08-15  Js                    C_COMP_MITSUBISHI_M32R added, revision
            2000-09-04  Js                    bus diagnostics added and ringdata mechanism changed
            2000-09-09  Gu                    deleted old prototypes NmCanOff and NmCanOn
                                              adapted function prototypes and external macros
                                              added #define NmStateErrBit
  3.21.00   2000-09-29  Js                    NM_NO_COMPATIBILITY channel dependend added
  3.22.00   2000-10-09  Gu                    Updated versions of supported compiler
            2000-10-19  Fr                    no changes
            2000-11-13  Bd                    no changes
            2000-11-15  Gu                    added variable kNmBugfixVersion Bugfix support
  3.23.00   2000-12-04  Gz                    no changes
  3.24.00   2000-12-18  Gu                    no changes
            2001-01-08  Gu                    NM_DBAG_... -> NM_TYPE_DBAG
                                              added compatibility mode for old usage of NM_DBAG define 
                                              moved compatibility switch for DC_ONM
            2001-02-14  Gu                    no changes
  3.25.00   2001-02-22  Rn                    no changes
  3.26.00   2001-02-23  Bs                    no changes
            2001-03-01  Gu                    no changes
  3.27.00   2001-03-19  Gu                    no changes
            2001-04-06  Gu                    added new customer switch
                                              added prototypes for extended NM Callbacks
                                              changed statement ConfigMaskTable TargetConfigTable
                                              to avoid compiler warnings
            2001-04-06  Sa                    no changes
            2001-04-09  Pl                    no changes
                        Gu                    added compatibility mode for nmEcuNr->kNmEcuNr,
                                              nmTxObj->kNmTxObj, nmCanPara->kNmCanPara
  3.28.00   2001-04-19  Gu                    no changes
  3.29.00   2001-04-26  Gu                    no changes
                        Bs      ESCAN00000677 support of C_COMP_OKI_CC665S added in source file
  3.30.00   2001-06-08  Ba      ESCAN00000792 Implementation for indexed usage of the NM
                                ESCAN00000560 no changes
                                              Remark: Compatibility modes are not adapted
  3.31.00   2001-07-16  Ht      ESCAN00000867 no changes
                        Gu      ESCAN00000835 no changes
                                ESCAN00000875 no changes
                                ESCAN00000876 no changes
                                ESCAN00000927 no changes
                                ESCAN00000930 no changes
                                ESCAN00000928 no changes
                                ESCAN00000931 no changes
                                ESCAN00000570 no changes
                                ESCAN00001039 no changes
                                ESCAN00000933 deleted unnecessary pragma-statement for M16C
                                ESCAN00000980 Adaptions for Ford
  3.32.00   2001-07-27  Gu      ESCAN00001072 no changes
                        Rn      ESCAN00001055 tempCanRxActualDLC deleted
                        Ml      ESCAN00001069 added cast to avoid HC12 compiler errors when using -pck option
                                ESCAN00001068 no changes
  3.33.00   2001-08-03  Gu      ESCAN00001127 Using old API with indexed NM causes no compiler error anymore
                                ESCAN00001124 declaration of ConfigMask and TargetConfigTable restored 
                        Js      ESCAN00001229 no changes
  3.34.00   2001-08-23  Gu      ESCAN00001284 no changes
  3.35.00   2001-08-30  Ba      ESCAN00001358 Support of Hiware compiler with Motorola HC08
  3.36.00   2001-09-03  Gu      ESCAN00001375 Special inquiry in case NM_NUMBER_OF_CONFIG_NODES is not used
  3.37.00   2001-09-12  Gu      ESCAN00001446 no changes
                        Gu      ESCAN00001463 no changes
  3.38.00   2001-09-21  Gu      ESCAN00001480 no changes
                        Gu      ESCAN00001468 temporary buffer for userdata access used for BMW
                        Gu      ESCAN00001516 no changes
  3.39.00   2001-10-25  Gu      ESCAN00001688 no changes
  3.40.00   2001-11-01  Rn      ESCAN00001731 no changes
            2001-11-05  Gu      ESCAN00001733 no changes
                                ESCAN00001712 no changes
                                ESCAN00001736 no changes
                                ESCAN00001737 no changes
                                ESCAN00001738 compatibility defines encapsulated
            2001-11-07  Rn      ESCAN00001748 no changes
                                ESCAN00001749 no changes
            2001-11-29  Gu      ESCAN00001842 no changes
            2001-12-13  Gu      ESCAN00001901 no changes
                                ESCAN00001917 no changes
  3.41.00   2002-01-03  Ml      ESCAN00001855 Added keywords for paging support
            2002-01-15  Gu      ESCAN00002062 ApplWriteWakeUpInfo does not support MEMORY_NEAR for Hiware Compiler
  3.42.00   2002-01-22  Gu      ESCAN00002111 New features according to the new specification of a car manufacturer
                        Js      ESCAN00002210 refer ESCAN00001855, missed one type
  3.43.00   2002-03-04  Js      ESCAN00002413 missed prototype for NmCountRingTypInitial_Field
                                ESCAN00002757 configuration check of NM_COUNT_RING_TYP_INITIAL removed
                        Gu      ESCAN00001900 no changes
                                ESCAN00002594 no changes
                                ESCAN00004445 no changes
                                ESCAN00002759 no changes
                                ESCAN00002760 no changes
                                ESCAN00002807 no changes
            2002-05-24  Fz      ESCAN00002926 No changes
            2002-06-18  Et      ESCAN00003089 support of physical multiple ECUs
            2002-07-25  Js      ESCAN00002906 UdTask() and UdInit() renamed to NmUserDataTask() and UserDataInit()
                                ESCAN00002952 Missing prototypes added
  3.45.00   2002-11-11  Js      ESCAN00004376 Formal changes
                                ESCAN00004259 Use SendMessFlag in own byte, split NmStateType in to
                                              two state types to avoid data inconsistency in nmState
                                ESCAN00004286 kNmEcuNr handling for indexed NM according to implementation of
                                              ESCAN00003089 corrected
                                ESCAN00002905 Some missed volatile types added
                                ESCAN00003570 Header file guarded against multiple inclusion
                                ESCAN00002357 no changes
                                ESCAN00004163 no changes
                                ESCAN00004146 no changes
                                ESCAN00004247 no changes
                                ESCAN00004328 no changes
                                ESCAN00003323 no changes
                                ESCAN00004441 no changes
                                ESCAN00004607 no changes
                                ESCAN00004500 Further status functions according to ESCAN00004259
  3.46.00   2003-02-22  Js      ESCAN00003535 No channel-Paramter for NmSendUserDataProtected
                                              and NmSendUserDataunProtected
                                ESCAN00004844 DC Userdata support will not compile in a code doubled system
  3.47.00   2003-03-17  Js      ESCAN00005108 no changes
  3.48.00   2003-03-28  Js      ESCAN00005245 no changes
                                ESCAN00005246 no changes
                                ESCAN00003524 Memory qualifier for zero page mapping for C_COMP_HIWARE_08
  3.49.00   2003-05-06  Js      ESCAN00005573 no changes
  3.50.00   2003-06-17  Js      ESCAN00004601 no changes
  3.51.00   2003-09-03  Js      ESCAN00006420 no changes
  3.52.00   2003-10-06  Js      ESCAN00006646 New features (2nd step) according to the new
                                              specification of a car manufacturer
                                ESCAN00006727 Error Pin detection does not work on
                                              indexed multi channel NM for special OEM
                                ESCAN00006769 no changes
                                ESCAN00005970 no changes
                                ESCAN00006771 no changes
                                ESCAN00006891 no changes
                                ESCAN00006916 no changes
  3.53.00   2003-11-27  Js      ESCAN00007008 WakeUp Type Indication for a car manufacturer added
                                ESCAN00007091 Changes according GENy introduction
                                ESCAN00007216 User Data extracted for special car manufacturer
                                ESCAN00007217 Generic NM adaptation API introduced
                                ESCAN00006970 no changes
                                ESCAN00006361 no changes
                                ESCAN00007275 no changes
                                ESCAN00007287 no changes
  3.54.00   2004-01-28  Js      ESCAN00007369 ONMX send data access changed
                                ESCAN00007382 no changes
  3.55.00   2004-02-13  Rn      ESCAN00007561 no changes
  3.56.00   2004-02-17  Js      ESCAN00007430 no changes
                                ESCAN00007436 no changes
                                ESCAN00007437 no changes
  3.57.00   2004-03-11  Js      ESCAN00007856 no changes
                                ESCAN00007535 no changes
                                ESCAN00007530 no changes
                                ESCAN00007822 no changes
                                ESCAN00007866 Usage of Multiple ECU for special configuration
  3.58.00   2004-04-05  Js      ESCAN00007954 Driver plausibility check deleted
                                ESCAN00008104 no changes
                                ESCAN00008229 no changes
                                ESCAN00008463 no changes
                                ESCAN00008466 Feature review and rework
                                ESCAN00008489 Formal adaptations for specific car manufacturer
  3.59.00   2004-06-29  Js      ESCAN00008585 StatusType defined according OSEK Binding Specification
                                ESCAN00008665 no changes
  3.60.00   2004-10-01  Js      ESCAN00009420 no changes
                                ESCAN00009728 New Version Defines introduced
                                ESCAN00009711 no changes
  3.61.00   2004-10-14  Js      ESCAN00009728 New Version Defines introduced
  3.62.00   2004-10-29  Js      ESCAN00010055 no changes
  3.63.00   2004-11-29  Js      ESCAN00010415 Support of 256 nodes
                                ESCAN00010454 no changes
                                ESCAN00010455 Compatibility section for special OEMs removed
                                ESCAN00010456 no changes
                                ESCAN00010463 Fast BusOff recovery introduced
                                ESCAN00010468 Extensions for special OEM removed
                                ESCAN00010471 Generic compatibility section removed
                                ESCAN00010498 no changes
  3.64.00   2005-01-18  Js      ESCAN00010855 CarWakeUp for special OEM introduced
  3.65.00   2005-03-29  Js      ESCAN00011622 Extensions for special OEM re-integrated
                                ESCAN00011925 Compile issue in special configuration for indexed NM
                                ESCAN00011970 Standard vector type qualifier implemented
                                ESCAN00011997 ECU's NM does not participate on a bus in a valid way
  3.66.00   2005-07-11  Js      ESCAN00012831 Extensions for special OEM re-integrated
                                ESCAN00013626 no changes in this file
                                ESCAN00012842 Include structure adapted
                                ESCAN00012901 no changes
                                ESCAN00012928 kNmBugfixVersion renamed to kNmReleaseVersion
  3.67.00   2006-01-23  Js      ESCAN00014119 changed implementation of SkippedAlive
                        vismas  ESCAN00014635 Re-integrated ErrorPin in NmPrecopy
                        vismas  ESCAN00014458 Fixed access on TX object for multiple ECUs
                        vismas  ESCAN00015016 added ORGANI filter checks
  3.68.00   2006-03-07  vismas  ESCAN00015469 corrected layout of bus diagnostic for some OEMs
  3.69.00   2006-03-16  vismas  ESCAN00015700 changed byte order within NmGetCanErrorConfig()
  3.70.00   2006-09-04  vismas  ESCAN00017526 no changes in this file
                                ESCAN00017787 no changes in this file
  3.71.00   2007-04-11  vismas  ESCAN00017962 no changes in this file
                                ESCAN00018325 no changes in this file
                                ESCAN00014814 added assertion handling added support of AUTOSAR CAN interface
                                ESCAN00020078 added features for new OEM
                                ESCAN00020079 updated component to current implementation/layout rules
  3.72.00   2007-08-22  vismas  ESCAN00020303 adapted type for NmTxObj_Field[]
                                ESCAN00020580 no changes in this file
                                ESCAN00020743 no changes in this file
                                ESCAN00020990 no changes in this file
                                ESCAN00021051 no changes in this file
  3.72.01   2007-10-01  visoh   ESCAN00022595 removed CanChannelHandle define
  3.72.02   2007-10-08  vismas  ESCAN00022656 added prototype for BusOff indication function for If_AsrCanIf
                                ESCAN00023028 adapted to updated AUTOSAR CAN IF
  3.73.00   2007-12-12  vismas  ESCAN00023665 no changes in this file
                                ESCAN00023668 added support for new OEM
  3.74.00   2008-02-04  vismas  ESCAN00022737 removed MISRA warning for NmGetStatus macros
                                ESCAN00024379 added support of indirection to system channels (not only CAN)
                                ESCAN00022927 no changes in this file
                                ESCAN00023863 no changes in this file
                                ------------- adapted to current coding template
                                ESCAN00022144 no changes in this file
                                ESCAN00024402 no changes in this file
  3.74.01   2008-03-10  vismas  ------------- no changes in this file
  3.74.02   2008-05-21  vismas  ------------- adaption for Autosar 3.0
  3.74.03   2008-06-16  vismas  ------------- removed new callback from 3.74.02
  3.75.00   2008-08-15  vismas  ESCAN00026277 no changes in this file
                                ESCAN00028050 added some parantheses
                                ESCAN00028089 no changes in this file
                                ESCAN00028510 no changes in this file
                                ESCAN00028757 added support for QNX
                                ESCAN00029951 no changes in this file
                                ESCAN00029982 no changes in this file
  3.75.01   2008-09-24  visoh   ESCAN00030216 removed/replaces occurences of kCanNumberOfChannels
            2008-10-16  vismas  ESCAN00030725 adapted timing for WaitBusSleep
  3.75.02   2008-10-27  vismas  ESCAN00031148 removed canproto.h
  3.75.03   2009-02-03  vismas  ESCAN00032787 adapted prototypes for ApplNmCanOnline()/Offline() and channel parameter
                                ESCAN00032811 no changes in this file
  3.75.04   2009-03-20  vismas  ESCAN00033467 no changes in this file
            2009-03-25  vismas  ESCAN00033660 ApplNmBusOffEnd now not available in AUTOSAR environment
            2009-03-25  vismas  ESCAN00034057 supported new OEM
  3.75.05   2009-04-27  vismas  ESCAN00034744 no changes in this file
  3.76.00   2009-05-05  vismas  ESCAN00034893 added optional callbacks for LimpHome
  3.76.01   2009-05-29  vismas  ESCAN00035240 no changes in this file
  3.77.00   2009-07-20  vismas  ESCAN00025937 added ApplNmBusOffChangeFastToSlow()
                                ESCAN00035150 no changes in this file
                                ESCAN00035209 corrected MISRA warnings
                                ESCAN00036712 added new OEM
                                ESCAN00036713 no changes in this file
                                ESCAN00036956 no changes in this file
  3.77.01   2009-10-23  vismas  ESCAN00038607 no changes in this file
  3.77.02   2009-12-22  vismas  ESCAN00039382 Adaptions for MISRA
            2010-01-20  vismas  ESCAN00040150 Added prototype for usage in AUTOSAR environments
  3.77.03   2010-06-23  vismas  ESCAN00043531 no changes in this file
**********************************************************************************************************************/
#if defined V_NM_DIROSEK_HEADER
#else
#define V_NM_DIROSEK_HEADER
#define NM_OSEK_H

/**********************************************************************************************************************
  Includes
**********************************************************************************************************************/
#include "v_cfg.h"
#include "v_def.h"

#if defined ( VGEN_ENABLE_NM_OSEK_D )

#include "nm_cfg.h"

#include "can_inc.h"
  #if defined ( VGEN_GENY )
#include "can_par.h"
  #endif

/**********************************************************************************************************************
  Version data
**********************************************************************************************************************/
/* ##V_CFG_MANAGEMENT ##CQProject : Nm_DirOsek CQComponent : Implementation */
#define NM_DIROSEK_VERSION                0x0377
#define NM_DIROSEK_RELEASE_VERSION        0x03

/**********************************************************************************************************************
  Configuration check
**********************************************************************************************************************/
#if defined ( VGEN_GENY )
  #if defined ( __NM_CFG_H__ ) || \
      defined ( __NMDIROSEK_CFG_H__ )
  #else
    #error "Nm_DirOsek: Configuration file is not included. Please check your configuration."
  #endif
#endif

/**********************************************************************************************************************
  Global configuration
**********************************************************************************************************************/
/* implicit configuration options */



/* compatibility defines for older configuration tools */
#if defined ( VGEN_GENY )
#endif

#if defined ( C_ENABLE_MULTICHANNEL_API )
  #define NM_ENABLE_INDEXED_DRVCAN
#endif

#if ( kNmNumberOfSystemChannels > kNmNumberOfChannels )
  #define NM_ENABLE_APPLCHANNEL_INDIRECTION
#endif

#if defined ( kComNumberOfNodes )
#else
  #define kComNumberOfNodes  1
#endif


#if defined ( NM_ENABLE_INDEXED_NM )
  #define NMVAR_CH_DEF(var)               var[kNmNumberOfChannels] /* PRQA S 3410 */ /* not possible for this kind of macro usage */
  #define NMVAR(var)                      var[channel]             /* PRQA S 3410 */ /* not possible for this kind of macro usage */
#else
  #define NMVAR_CH_DEF(var)               var /* PRQA S 3410 */ /* not possible for this kind of macro usage */
  #define NMVAR(var)                      var /* PRQA S 3410 */ /* not possible for this kind of macro usage */
#endif

/**********************************************************************************************************************
  Global typedefs
**********************************************************************************************************************/
/*
 * Name:    NMModeName
 * Used by: GotoMode() (parameter) 
 */
typedef enum
{
  BusSleep = 0,
  Awake
} NMModeName;

/*
 * Name:    NmInitType
 * Used by: NmOsekInit() (parameter) 
 */
typedef enum
{
  NM_DISABLE = 0,             /* do not start NM                */
  NM_NORMAL = 1,              /* SleepInd=0, active mode        */
  NM_NMPASSIVE = 2,           /* SleepInd=1, passive mode       */
  NM_SLEEPIND = 3,            /* SleepInd=1, active mode        */
  NM_SLEEPIND_NMPASSIVE = 4,  /* SleepInd=1, passive mode       */
  NM_CANSLEEP = 6             /* NM is asleep                   */
} NmInitType;


#if defined ( NM_ENABLE_CONFIG )
/* 
 * Name:    NmReturnType
 * Used by: CmpConfig() (return type) 
 */
typedef vuint8 NmReturnType;
#endif


#if defined ( STATUSTYPEDEFINED )
/* another OSEK component has already defined the status type */
#else
  #define STATUSTYPEDEFINED
  #define E_OK                  0

/* 
 * Name:    StatusType
 * Used by: ReadRingData() (return type)
 *          TransmitRingData() (return type)
 */
typedef unsigned char StatusType;
#endif

/* Note: This define is not defined with STATUSTYPEDEFINED */
#define E_NotOK               64


/* 
 * Name:    NmStatusType
 * Used by: GetStatus() (parameter)
 *          NmGetStatus() (return type) 
 */
typedef vuint8 NmStatusType;

#if defined ( NM_ENABLE_CONFIG ) 
/* 
 * Name:    NmConfigType
 * Used by: ConfigMaskTable (type of array)
 *          TargetConfigTable (type of array)
 *          GetConfig (parameter)
 *          NmGetCanErrorConfig (parameter)
 */
typedef struct
{
    #if defined ( NM_ENABLE_INDEXED_NM )
  vuint8 nmConfigChar[(NM_NUMBER_OF_CONFIG_NODES)/8 * kNmNumberOfChannels];
    #else
  vuint8 nmConfigChar[(NM_NUMBER_OF_CONFIG_NODES)/8];
    #endif
} NmConfigType;
#endif



/**********************************************************************************************************************
  Global data defines
**********************************************************************************************************************/
/* NM type */
#if defined ( NM_ENABLE_INDEXED_NM )
  #define NM_CHANNEL_NMTYPE_ONLY              CanChannelHandle channel
  #define NM_CHANNEL_NMTYPE_FIRST             CanChannelHandle channel,
  #define NM_CHANNEL_NMPARA_ONLY              channel
  #define NM_CHANNEL_NMPARA_FIRST             channel,
#else
  #define NM_CHANNEL_NMTYPE_ONLY              void /* PRQA S 3460 */ /* keyword used within macro due to common channel-handling */
  #define NM_CHANNEL_NMTYPE_FIRST             
  #define NM_CHANNEL_NMPARA_ONLY              
  #define NM_CHANNEL_NMPARA_FIRST             
#endif

/* CAN type */
#if defined ( NM_ENABLE_INDEXED_NM )
  #if defined ( NM_ENABLE_CHANNEL_INDIRECTION ) /* ESCAN00032787 */
    #define NM_CHANNEL_CANTYPE_ONLY           CanChannelHandle channel
    #define NM_CHANNEL_CANTYPE_FIRST          CanChannelHandle channel,
    #define NM_CHANNEL_CANPARA_ONLY           NmNmToCanIndirection[channel]
    #define NM_CHANNEL_CANPARA_FIRST          NmNmToCanIndirection[channel],
  #else
    #define NM_CHANNEL_CANTYPE_ONLY           CanChannelHandle channel
    #define NM_CHANNEL_CANTYPE_FIRST          CanChannelHandle channel,
    #define NM_CHANNEL_CANPARA_ONLY           channel
    #define NM_CHANNEL_CANPARA_FIRST          channel,
  #endif
#else
  #if defined ( NM_ENABLE_INDEXED_DRVCAN ) /* ESCAN00032787 */
    #define NM_CHANNEL_CANTYPE_ONLY           CanChannelHandle channel
    #define NM_CHANNEL_CANTYPE_FIRST          CanChannelHandle channel,

    #if defined ( NM_CAN_CHANNEL )            
      #define NM_CHANNEL_CANPARA_ONLY         NM_CAN_CHANNEL
      #define NM_CHANNEL_CANPARA_FIRST        NM_CAN_CHANNEL,
    #else
      #define NM_CHANNEL_CANPARA_ONLY         0
      #define NM_CHANNEL_CANPARA_FIRST        0,
    #endif
  #else
    #define NM_CHANNEL_CANTYPE_ONLY           void  /* PRQA S 3460 */ /* keyword used within macro due to common channel-handling */
    #define NM_CHANNEL_CANTYPE_FIRST          
    #define NM_CHANNEL_CANPARA_ONLY           
    #define NM_CHANNEL_CANPARA_FIRST          
  #endif
#endif

/* APPL type */
#if defined ( NM_ENABLE_INDEXED_NM )
  #define NM_CHANNEL_APPLTYPE_ONLY            CanChannelHandle channel
  #define NM_CHANNEL_APPLTYPE_FIRST           CanChannelHandle channel,
  #if defined ( NM_ENABLE_APPLCHANNEL_INDIRECTION )
    #define NM_CHANNEL_APPLPARA_ONLY          NmNmToSystemIndirection[channel]
    #define NM_CHANNEL_APPLPARA_FIRST         NmNmToSystemIndirection[channel],
  #else
    #define NM_CHANNEL_APPLPARA_ONLY          channel
    #define NM_CHANNEL_APPLPARA_FIRST         channel,
  #endif
#else                                         
  #define NM_CHANNEL_APPLTYPE_ONLY            void /* PRQA S 3460 */ /* keyword used within macro due to common channel-handling */
  #define NM_CHANNEL_APPLTYPE_FIRST           
  #define NM_CHANNEL_APPLPARA_ONLY            
  #define NM_CHANNEL_APPLPARA_FIRST           
#endif

#if defined ( NM_API_CALL_TYPE )
#else
  #define NM_API_CALL_TYPE
#endif

#if defined ( NM_API_CALLBACK_TYPE )
#else
  #define NM_API_CALLBACK_TYPE
#endif

#if defined ( NM_INTERNAL_CALL_TYPE )
#else
  #define NM_INTERNAL_CALL_TYPE
#endif




#if defined ( NM_ENABLE_ASSERTIONS )
  /*
   * Name:        kNmAssert...
   * Description: symbolic values for NM assertions
   * Used by      ApplNmDirOsekFatalError() (parameter)
   */
  #define kNmAssertConfirmationHasWrongCanHandle  0x10
  #define kNmAssertWrongFlagWaitBusSleep          0x11
  #define kNmAssertWrongFlagBusSleep              0x12
  #define kNmAssertInvalidChannel                 0x13
  /* Note: kNmAssertCanIsOffline is equal to kNmAssertCanIsOnline.
           kNmAssertCanIsOffline is nor more used in component but kept for component compatibility.
   */
  #define kNmAssertCanIsOffline                   0x14
  #define kNmAssertCanIsOnline                    0x14
#endif

/**********************************************************************************************************************
  Global macro defines
**********************************************************************************************************************/
/*
 * Name:        NmState...()
 * Description: macros for status evaluation
 * Used by      application
 */
/* ESCAN00022737, ESCAN00028050 */
#define NmStateRingStable(state)          ((((state) & (NmStatusType)0x0001) != 0) ? 1 : 0) /* PRQA S 3453 */ /* macro used for optimization reason: masking of flag */
#define NmStateBusError(state)            ((((state) & (NmStatusType)0x0002) != 0) ? 1 : 0) /* PRQA S 3453 */ /* macro used for optimization reason: masking of flag */
#define NmStateActive(state)              ((((state) & (NmStatusType)0x0004) != 0) ? 1 : 0) /* PRQA S 3453 */ /* macro used for optimization reason: masking of flag */
#define NmStatePassive(state)             ((((state) & (NmStatusType)0x0004) != 0) ? 0 : 1) /* PRQA S 3453 */ /* macro used for optimization reason: masking of flag */
#define NmStateLimphome(state)            ((((state) & (NmStatusType)0x0008) != 0) ? 1 : 0) /* PRQA S 3453 */ /* macro used for optimization reason: masking of flag */
#define NmStateBusSleep(state)            ((((state) & (NmStatusType)0x0010) != 0) ? 1 : 0) /* PRQA S 3453 */ /* macro used for optimization reason: masking of flag */
#define NmStateWaitBusSleep(state)        ((((state) & (NmStatusType)0x0020) != 0) ? 1 : 0) /* PRQA S 3453 */ /* macro used for optimization reason: masking of flag */
#define NmStateTxRingDataAllowed(state)   ((((state) & (NmStatusType)0x0040) != 0) ? 1 : 0) /* PRQA S 3453 */ /* macro used for optimization reason: masking of flag */
#define NmStateBusSleepInd(state)         ((((state) & (NmStatusType)0x0080) != 0) ? 1 : 0) /* PRQA S 3453 */ /* macro used for optimization reason: masking of flag */
#define NmStateBusWakeUp(state)           ((((state) & (NmStatusType)0x0080) != 0) ? 0 : 1) /* PRQA S 3453 */ /* macro used for optimization reason: masking of flag */

/**********************************************************************************************************************
  Global data prototypes (exported, RAM)
**********************************************************************************************************************/




/**********************************************************************************************************************
  Global data prototypes (exported, ROM)
**********************************************************************************************************************/

V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kNmMainVersion;
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kNmSubVersion;
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 kNmReleaseVersion;

/* for compatibility reasons */
#define kNmBugfixVersion      kNmReleaseVersion


/**********************************************************************************************************************
  Global data prototypes (imported, RAM)
**********************************************************************************************************************/
#if defined ( NM_ENABLE_INDEXED_NM )
#else 
  #if defined ( NM_ENABLE_MULTIPLE_NODES )
    #if defined ( NM_CAN_CHANNEL )
V_MEMRAM0 extern V_MEMRAM1 vuint8 V_MEMRAM2 comMultipleECUCurrent[kNmNumberOfCanChannels];
    #else
V_MEMRAM0 extern V_MEMRAM1 vuint8 V_MEMRAM2 comMultipleECUCurrent;
    #endif
  #endif
#endif


/**********************************************************************************************************************
  Global data prototypes (imported, ROM)
**********************************************************************************************************************/

/*----------------------------------------------------------
 * from configuration tool
 *----------------------------------------------------------*/
#if defined ( NM_ENABLE_INDEXED_NM )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 NmCallCycle_Field[kNmNumberOfChannels];
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 NmCountRingTyp_Field[kNmNumberOfChannels];
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 NmCountRingMax_Field[kNmNumberOfChannels];
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 NmCountLimphome_Field[kNmNumberOfChannels];
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 NmCountWaitBussleep_Field[kNmNumberOfChannels];

  #if defined ( VGEN_GENY )
    #if ( kNmNumberOfRanges > 1 )
V_MEMROM0 extern V_MEMROM1 vuint8  V_MEMROM2 NmRangeMask_Field[kNmNumberOfChannels];
V_MEMROM0 extern V_MEMROM1 vuint16 V_MEMROM2 NmRangeCode_Field[kNmNumberOfChannels];
    #endif
  #endif

  #if defined ( NM_ENABLE_CHANNEL_INDIRECTION )
V_MEMROM0 extern V_MEMROM1 CanChannelHandle V_MEMROM2 NmCanToNmIndirection[kNmNumberOfCanChannels];
V_MEMROM0 extern V_MEMROM1 CanChannelHandle V_MEMROM2 NmNmToCanIndirection[kNmNumberOfChannels];
  #endif

  #if ( kNmNumberOfSystemChannels > kNmNumberOfCanChannels )
V_MEMROM0 extern V_MEMROM1 CanChannelHandle V_MEMROM2 NmSystemToNmIndirection[kNmNumberOfSystemChannels];
V_MEMROM0 extern V_MEMROM1 CanChannelHandle V_MEMROM2 NmNmToSystemIndirection[kNmNumberOfChannels];
  #else
    #define NmSystemToNmIndirection     NmCanToNmIndirection
    #define NmNmToSystemIndirection     NmNmToCanIndirection
  #endif

    #if defined ( NM_ENABLE_MULTIPLE_NODES )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 NmEcuNr_Field[kNmNumberOfChannels][kComNumberOfNodes];
V_MEMROM0 extern V_MEMROM1 CanTransmitHandle V_MEMROM2 NmTxObj_Field[kNmNumberOfChannels][kComNumberOfNodes];
    #else
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 NmEcuNr_Field[kNmNumberOfChannels];
V_MEMROM0 extern V_MEMROM1 CanTransmitHandle V_MEMROM2 NmTxObj_Field[kNmNumberOfChannels];
    #endif

V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 NmCanPara_Field[kNmNumberOfChannels];




#endif


#if defined ( NM_ENABLE_INDEXED_NM )
#else 
  #if defined ( NM_ENABLE_MULTIPLE_NODES )
V_MEMROM0 extern V_MEMROM1 vuint8 V_MEMROM2 NmEcuNr_Field[kComNumberOfNodes];
V_MEMROM0 extern V_MEMROM1 CanTransmitHandle V_MEMROM2 NmTxObj_Field[kComNumberOfNodes];
  #endif
#endif

/*----------------------------------------------------------
 * from application
 *----------------------------------------------------------*/
#if defined ( NM_ENABLE_CONFIG )
V_MEMROM0 extern V_MEMROM1 NmConfigType V_MEMROM2 ConfigMaskTable[];
V_MEMROM0 extern V_MEMROM1 NmConfigType V_MEMROM2 TargetConfigTable[];
#endif


/**********************************************************************************************************************
  Global function prototypes
**********************************************************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
  service functions
---------------------------------------------------------------------------------------------------------------------*/
extern void NM_API_CALL_TYPE NmOsekInit( NM_CHANNEL_NMTYPE_FIRST NmInitType initMode );
extern void NM_API_CALL_TYPE NmTask( NM_CHANNEL_NMTYPE_ONLY );
extern void NM_API_CALL_TYPE GotoMode( NM_CHANNEL_NMTYPE_FIRST NMModeName mode );

extern void NM_API_CALL_TYPE GetStatus( NM_CHANNEL_NMTYPE_FIRST NmStatusType *dest );
extern NmStatusType NM_API_CALL_TYPE NmGetStatus( NM_CHANNEL_NMTYPE_ONLY );

extern void NM_API_CALL_TYPE StartNM( NM_CHANNEL_NMTYPE_ONLY );
extern void NM_API_CALL_TYPE StopNM( NM_CHANNEL_NMTYPE_ONLY );
extern void NM_API_CALL_TYPE TalkNM( NM_CHANNEL_NMTYPE_ONLY );
extern void NM_API_CALL_TYPE SilentNM( NM_CHANNEL_NMTYPE_ONLY );

#if defined ( NM_ENABLE_RINGDATA_ACCESS )
extern StatusType NM_API_CALL_TYPE ReadRingData( NM_CHANNEL_NMTYPE_FIRST vuint8 *ringData );
extern StatusType NM_API_CALL_TYPE TransmitRingData( NM_CHANNEL_NMTYPE_FIRST vuint8 *ringData );
#endif

#if defined ( NM_ENABLE_CONFIG )
extern void         NM_API_CALL_TYPE GetConfig( NM_CHANNEL_NMTYPE_FIRST NmConfigType *dataPtr );
extern NmReturnType NM_API_CALL_TYPE CmpConfig( NM_CHANNEL_NMTYPE_FIRST vuint8 idx );
#endif














/*---------------------------------------------------------------------------------------------------------------------
  service functions (DrvCan)
---------------------------------------------------------------------------------------------------------------------*/
/*
 * The prototypes of the service functions for the CAN driver are defined
 * by the CAN driver.
 * - NmCanError()
 * - NmConfirmation()
 * - NmPrecopy()
 * - NmPreTransmit()
 */

/*---------------------------------------------------------------------------------------------------------------------
  callback functions
---------------------------------------------------------------------------------------------------------------------*/
extern void NM_API_CALLBACK_TYPE ApplNmCanNormal( NM_CHANNEL_APPLTYPE_ONLY );
extern void NM_API_CALLBACK_TYPE ApplNmCanSleep( NM_CHANNEL_APPLTYPE_ONLY );
extern void NM_API_CALLBACK_TYPE ApplNmCanBusSleep( NM_CHANNEL_APPLTYPE_ONLY );
extern void NM_API_CALLBACK_TYPE ApplNmBusOff( NM_CHANNEL_APPLTYPE_ONLY );

#if defined ( NM_ENABLE_EXTENDED_CALLBACK )
extern void NM_API_CALLBACK_TYPE ApplNmBusOffEnd( NM_CHANNEL_APPLTYPE_ONLY );
extern void NM_API_CALLBACK_TYPE ApplNmBusStart( NM_CHANNEL_APPLTYPE_ONLY );
extern void NM_API_CALLBACK_TYPE ApplNmWaitBusSleep( NM_CHANNEL_APPLTYPE_ONLY );
extern void NM_API_CALLBACK_TYPE ApplNmWaitBusSleepCancel( NM_CHANNEL_APPLTYPE_ONLY );
#endif

#if defined ( NM_ENABLE_EXTERNAL_CANONLINE_HANDLING ) /* ESCAN00032787 */
extern void ApplNmCanOnline( NM_CHANNEL_CANTYPE_ONLY );
extern void ApplNmCanOffline( NM_CHANNEL_CANTYPE_ONLY );
#endif

#if defined ( NM_ENABLE_RINGDATA_ACCESS )
extern void NM_API_CALLBACK_TYPE ApplNmIndRingData( NM_CHANNEL_APPLTYPE_ONLY );
#endif






#if defined ( NM_ENABLE_ASSERTIONS )
extern void NM_API_CALLBACK_TYPE ApplNmDirOsekFatalError( vuint8 error );
#endif


#endif /* VGEN_ENABLE_NM_OSEK_D */
#endif /* V_NM_DIROSEK_HEADER */


/**********************************************************************************************************************
  EOF
**********************************************************************************************************************/
/* ORGANI: STOPSINGLE_OF_MULTIPLE */

/************   Organi, Version 3.9.0 Vector-Informatik GmbH  ************/

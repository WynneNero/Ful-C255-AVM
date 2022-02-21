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
                - n_onm.c
                - n_vnm.c
                - nm_osek.c
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
                        Ba                    CANNWM channel 0 also added for nmRxMsgBuffer macro
  3.10.00   1999-12-06  HH                    adapted to automatic gentool
  3.11.00   1999-12-07  HH                    enable selective disabling of channels by means of NM_TYPE_NONE
  3.12.00   2000-02-28  Be                    Compatibility for SINGLE_/MULTIPLE_RECEIVE_BUFFER
                        dH                    adaptation to new GenTool CANgen
                                              renamed callback functions to ApplNm...
                                              renamed timing parameters to NM_COUNT...
                                              no more #ifndef
                                              added C_COMP_HEW_SH7055
                                              added some casts to avoid compiler warnings
                                              changed C_ENABLE_MULTICAN and CANNWM to NM_CAN_CHANNEL
                                              changed NM_NumberOfConfigNodes to NM_NUMBER_OF_CONFIG_NODES
                                              changed NM_NumberOfConfigBytes to NM_NUMBER_OF_CONFIG_BYTES
  3.15.00   2000-02-15  Mr                    changes according to DC-ONM ver. 3.14d
                        Mr                    StateNetSleepInd, PreNetSleepInd (DC-ONM) implemented
                        Mr                    Userdata-Protocol (UDP for DC-ONM) implemented
  3.16.00   2000-04-10  Fz                    adaptation to new GenTool CANgen
                                              nmEcuNr->kNmEcuNr, nmTxObj->kNmTxObj, nmCanPara->kNmCanPara
                        Rn                    conditional namechanges of includefiles
            2000-04-12  Fz                    added C_COMP_NEC_V85X
            2000-04-26  Bd                    bugfix for NM_BROADCAST_ACCESS_USED with C_MULTIPLE_RECEIVE_BUFFER
  3.17.00   2000-05-30  Gz                    adaptation CanEcuNumber -> canEcuNumber
                                              changed switch for FJVGC 
  3.18.00   2000-06-02  Et                    inserted dummy assignment to avoid compiler warnings for all C_COMP_...
                                              access to SleepInd and SleepAck both by DB and by VAG
  3.19.00   2000-08-17  Rn                    delete C_SPECIAL_HC08AGATE 
                        Gu                    new CUSTOMER_SWITCH
                        Rn                    support C_MULTIPLE_RECEIVE_CHANNEL 
                        Gu                    added C_COMP_IAR_78K0 and C_COMP_HEW_H8S
                        Gu                    divided ApplCanErrorPin() into ApplCanErrorPinReceive()/Send()
                        Js                    C_COMP_MITSUBISHI_M32R added
  3.20.00   2000-09-01  Js                    Correction: ResetConfig now also works with 128 nodes 
                                              bus diagnostic added
            2000-09-04  Fz                    changed NmMessType for NEC CA850 compiler  
            2000-09-04  Js                    bus diagnostics added and ringdata mechanism changed
            2000-09-08  Gu                    moved initialisation of NmTxMsgByteUser1 and NmTxMsgByteUser2
                                              added C_COMP_IAR_12 in CopyErrorBitToMess
                                              condensed union NmMessType for C_COMP_NEC_V85X
                                              added plausibility check of NM configuration
  3.21.00   2000-09-20  Js                    Ring Address (nmSendMess.c[0]) and
                                              Control Byte (nmSendMess.c[1]) initialized with 0
            2000-09-25  Th                    added support for GNU ST9
            2000-09-27  Rn                    CanInterruptDisable without Paramater with index-Can-driver
  3.22.00   2000-10-09  Gu                    Updated versions of supported compiler
            2000-10-19  Fr                    added C_COMP_ANSI_TMS_470
            2000-11-13  Bd                    added support for DIABDATA MCORE
            2000-11-15  Gu                    added variable kNmBugfixVersion Bugfix support
                                              bugfix for direct repetition in NmCanError
  3.23.00   2000-11-20  Gu                    no special treatment for C5x5C in CanError needed anymore
            2000-11-21  Th                    added support  for HIWARE ST7
            2000-11-21  Gz                    C_COMP_MITSUBISHI_NC30 -> C_COMP_MITSUBISHI_M16C 
                                              added NM_DUMMY_STATEMENT to avoid compiler warnings
  3.24.00   2000-12-18  Gu                    C_COMP_KEIL_C16x -> C_COMP_KEIL_C16X
            2000-01-08  Gu                    changed instruction in state NM_ACTION_START to avoid compiler warnings 
                                              NM_DBAG_... -> NM_TYPE_DBAG
                                              added condition for old DC_ONM define to ensure compilation of header
            2001-02-14  Rn                    added channel 4, correction in channel 1,2,3
                        Gu                    changed instruction in function NmTask to avoid compiler warnings 
  3.25.00   2001-02-22  Rn                    bugfix: CanReset... for indexed-Can-driver with paramter NM_CAN_CHANNEL
  3.26.00   2001-02-23  Bs                    Greenhils MULTI2000 for OKI ARM7TM added / C_COMP_GHS_ARM7TM
            2001-03-01  Gu                    Deleted MEMORY_ROM assigment for multiple ECU declaration
  3.27.00   2001-03-19  Gu                    no special treatment for C5x5C in NmTask needed anymore
                                              changed dummy statement for M16C in NmConfirmation
                                              added plausibility check for include structure
                                              deleted old DC define
                                              moved compatibility mode of nmEcuNr->kNmEcuNr, nmTxObj->kNmTxObj, 
                                              nmCanPara->kNmCanPara into NM_CFG.H, Source also changed
            2001-04-06  Gu                    added new Customer switch
                                              added extended NM Callbacks
            2001-04-06  Sa                    added Dummy Statement to avoid compiler warnings for NEC 78K0 
                                              and nested comment fix.
            2001-04-09  Pl                    added support for ARM7TDMI
                        Gu                    changed compatibility mode for older versions of Gen-Tool
  3.28.00   2001-04-19  Gu                    added Dummy Statement to avoid compiler warnings
                                              for KEIL C16X Compiler
  3.29.00   2001-04-26  Gu                    XPAGE setting for C_COMP_KEIL_C5x5 removed due to CAN LI1.2 support
                        Bs      ESCAN00000677 no changes
  3.30.00   2001-06-08  Ba      ESCAN00000792 Implementation for indexed usage of the NM
                                ESCAN00000560 wrong param for callback for indexed CAN-Driver fixed
  3.31.00   2001-07-16  Ht      ESCAN00000867 support for C_SINGLE_RECEIVE_CHANNEL added
                        Gu      ESCAN00000835 Changed pChipDataPtr to CanChipDataPtr which was changed in reference 
                                              implementation 1.1 of the CAN Driver
                                ESCAN00000875 Wrong assigment of #define TargetErrorConfig changed
                                ESCAN00000876 changed instruction in function ReadBroadcastData
                                              to avoid compiler warnings
                                ESCAN00000927 refer next line
                                ESCAN00000930 changed instruction in function ResetConfig 
                                              and ResetErrorConfig to avoid compiler warnings
                                ESCAN00000928 code for time-measurement added
                                ESCAN00000931 Missing define for PAG added when using 128 nodes
                                ESCAN00000570 Vector NM now also works with 128 nodes
                                ESCAN00001039 tempCanRxActualDLC dependens not only of NM_BROADCAST_ACCESS_USED
                                ESCAN00000980 Adaptions for Ford
                                ESCAN00000933 no changes
  3.32.00   2001-07-27  Gu      ESCAN00001055 DLC-check in tempCanRxActualDLC optimized
                        Rn      ESCAN00001055 tempCanRxActualDLC deleted
                        Ml      ESCAN00001069 added cast to avoid HC12 compiler errors when using -pck option
                        Rn      ESCAN00001068 fixed compiler error in case of indexed CAN-Driver and DC Userdata
                        Gu      ESCAN00001072 Added some casts to avoid warning when using strict typechecking
  3.33.00   2001-08-03  Gu      ESCAN00001127 no changes
                                ESCAN00001124 no changes
                        Js      ESCAN00001229 C_COMP_TASKING_MC376 added
  3.34.00   2001-08-23  Gu      ESCAN00001284 Bugfix in case of using the Ford-NM
  3.35.00   2001-08-30  Ba      ESCAN00001358 Support of Hiware compiler with Motorola HC08
  3.36.00   2001-09-03  Gu      ESCAN00001375 Special inquiry in case NM_NUMBER_OF_CONFIG_NODES is not used
  3.37.00   2001-09-12  Gu      ESCAN00001446 Incomplete statement in case of using STM ST7 and indexed NM corrected
                        Gu      ESCAN00001463 Support for extended Userdata Access
  3.38.00   2001-09-21  Gu      ESCAN00001480 added new and deleted some old compiler switches
                        Gu      ESCAN00001468 temporary buffer for userdata access used for BMW
                        Gu      ESCAN00001516 udinit and udtask changed to UdInit and UdTask
  3.39.00   2001-10-25  Gu      ESCAN00001688 Change in bus-off handling for Ford NOS
  3.40.00   2001-11-01  Rn      ESCAN00001731 added missing brackets for userdata DC
            2001-11-05  Gu      ESCAN00001733 Fixed another incomplete code line using STM ST7
                                ESCAN00001712 changed switch from C_COMP_<xxx>_SH7055 to  C_COMP_<xxx>_SH705X
                                ESCAN00001736 Additional Micro Support for NM C_COMP_COSMIC_ST7_BECAN
                                ESCAN00001737 Corrected some comments
                                ESCAN00001738 no changes
            2001-11-07  Rn      ESCAN00001748 DC-Userdata: clear nmpdu in case of limphome
                                ESCAN00001749 GW-Support: code before definition
            2001-11-29  Gu      ESCAN00001842 DC-Userdata: notification of userdata
                                              service in case ECU is not addressed
            2001-12-13  Gu      ESCAN00001901 Remove compiler specific definition of bit fields
                                ESCAN00001917 Adapted call of function ApplWriteWakeUpInfo
                                              in C-File according to Header-File
  3.41.00   2002-01-03  Ml      ESCAN00001855 Added keywords for paging support
            2002-01-15  Gu      ESCAN00002062 ApplWriteWakeUpInfo does not support MEMORY_NEAR for Hiware Compiler
  3.42.00   2002-01-22  Gu      ESCAN00002111 New features according to the new specification of a car manufacturer
                        Js      ESCAN00002210 no changes
  3.43.00   2002-03-04  Js      ESCAN00002413 no changes
                                ESCAN00002757 no changes
                        Gu      ESCAN00001900 Added typecast's for NM send buffer to avoid linker warnings
                                ESCAN00004445 During execution of GotoMode(): Possible loss
                                              of sleep / wakeup information
                                ESCAN00002759 Corrected bus-off handling for Ford NOS
                                ESCAN00002760 Type nmAction has been changed from
                                              enum to vuint8 to avoid compiler warnings
                                ESCAN00002807 Insert interrupt protection in API functions to ensure data consistency
                                ESCAN00002594 no changes
                                ESCAN00002952 no changes
  3.44.00   2002-05-24  Fz      ESCAN00002926 nmSendMess array aligned to two bytes for V850 with NEC compiler
            2002-06-18  Et      ESCAN00003089 support of physical multiple ECUs
            2002-07-17          ESCAN00002926 nmSendMess array aligned to two bytes for 16-/32-bit MCUs
            2002-07-25  Js      ESCAN00002906 UdTask() and UdInit() renamed to
                                              ApplNmUserDataTask() and ApplUserDataInit()
  3.45.00   2002-11-11  Js      ESCAN00004146 C-Library functions not longer used
                                ESCAN00004247 Rx/Tx Inversion resolution
                                ESCAN00004259 Delayed state transition or during execution of
                                              GotoMode(): Possible loss of sleep information
                                ESCAN00004328 CanOnline() added to NM_ACTION_START in NmTask()
                                ESCAN00004376 Formal changes
                                ESCAN00004286 kNmEcuNr handling for indexed NM 
                                              according to implementation of ESCAN00003089 corrected
                                ESCAN00003323 Lint warnings removed
                                ESCAN00004441 Wrong access to UD receive message command
                                ESCAN00002357 AND
                                ESCAN00004163 Some compiler produces warning on dummy statements
                                              V_ENABLE_USE_DUMMY_STATEMENT inserted
                                ESCAN00004500 Further status functions according to ESCAN00004259
                                ESCAN00004601 To less copy and initialization of User Data for NM_TYPE_VECTOR_OSEK
                                ESCAN00004607 No Skipped Alive for a special Ring Message
                                ESCAN00002905 no changes
                                ESCAN00003570 no changes
  3.46.00   2003-02-22  Js      ESCAN00004844 DC Userdata support will not compile in a code doubled system
                                ESCAN00003535 no changes
  3.47.00   2003-03-17  Js      ESCAN00005108 Wrong definition of SendMessFlag and NmStateTypeDcUd for C5X5
  3.48.00   2003-03-28  Js      ESCAN00005245 No CanInterruptRestore() in ReadRingData() for special OEM
                                ESCAN00005246 MEMORY_CAN inserted
                                              SINGLE_RECEIVE_BUFFER and MULTIPLE_RECEIVE_BUFFER deleted
                                ESCAN00003524 Memory qualifier for zero page mapping for C_COMP_HIWARE_08
  3.49.00   2003-05-06  Js      ESCAN00005573 Warning removed
  3.50.00   2003-06-17  Js      ESCAN00004601 To less copy and initialization of User Data for NM_TYPE_VECTOR_OSEK
  3.51.00   2003-09-03  Js      ESCAN00006420 OSEK NM send message has incorrect data due to alignment problem
  3.52.00   2003-10-06  Js      ESCAN00006646 New features (2nd step) according to the new
                                              specification of a car manufacturer
                                ESCAN00006727 Error Pin detection does not work on
                                              indexed multi channel NM for special OEM
                                ESCAN00006769 No WakeUp after BusSleep for Ring Message with set Sleep Indication
                                ESCAN00005970 canChannel for Multiple ECUs with indirection not defined
                                ESCAN00006771 Amount of User Data changed for special OEM
                                ESCAN00006891 nmSendMess now fix on 8 byte
                                ESCAN00006916 canEcuNumber not longer used
  3.53.00   2003-11-27  Js      ESCAN00007008 WakeUp Type Indication for a car manufacturer added
                                ESCAN00007091 Changes according GENy introduction
                                ESCAN00007216 User Data extracted for special car manufacturer
                                ESCAN00007217 Generic NM adaptation API introduced
                                ESCAN00006970 Warning is generated "canChannel not used"
                                ESCAN00006361 Prepare Sleep Counter for Indexed Systems
                                ESCAN00007275 Possible compiler report for truncating assignment
                                ESCAN00007287 Error Configuration mismatch for special car manufacturer
  3.54.00   2004-01-28  Js      ESCAN00007369 ONMX send data access changed
                                ESCAN00007382 Cosmic HC(S)12 issue fix
  3.55.00   2004-02-13  Rn      ESCAN00007561 Include v_inc.h instead of can_inc.h in case of GENy
  3.56.00   2004-02-17  Js      ESCAN00007430 Remote Sleep Indication adapted
                                ESCAN00007436 ESCAN00006769 moved to NmPrecopy
                                ESCAN00007437 ESCAN00007008 reworked for wait bus sleep
  3.57.00   2004-03-11  Js      ESCAN00007856 Faster solution for ESCAN00004247
                                ESCAN00007535 Multiple calls of ApplNmWaitBusSleep when
                                              multiply receiving RING messages with set SleepAck
                                ESCAN00007530 Compiler Warning for GetConfig() and CmpConfig()
                                ESCAN00007822 Warning about unreferenced variable 'channel'
                                ESCAN00007866 Usage of Multiple ECU for special configuration
  3.58.00   2004-04-05  Js      ESCAN00007954 no changes
                                ESCAN00008104 Unexpected copy of User Data
                                ESCAN00008229 Optimization of UD handling for special car manufacturer
                                ESCAN00008463 Tx path activation to late after cancel of TwaitBusSleep
                                ESCAN00008466 Feature review and rework
                                ESCAN00008489 Formal adaptations for specific car manufacturer
  3.59.00   2004-06-29  Js      ESCAN00008585 no changes
                                ESCAN00008665 Usage of temp. buffer for indexed C16x driver
  3.60.00   2004-10-01  Js      ESCAN00009420 The ECU does not transmit any message except NM messages
                                ESCAN00009728 New Version Defines introduced
                                ESCAN00009711 BusOff Flag remains active
  3.61.00   2004-10-14  Js      ESCAN00009728 New Version Defines introduced
  3.62.00   2004-10-29  Js      ESCAN00010055 Wrong context of CanOffline
  3.63.00   2004-11-29  Js      ESCAN00010415 Support of 256 nodes
                                ESCAN00010454 Config algorithm equal for all OEMs
                                ESCAN00010455 no changes
                                ESCAN00010456 C_COMP_HITECH_05 removed
                                ESCAN00010463 Fast BusOff recovery introduced
                                ESCAN00010468 Extensions for special OEM removed
                                ESCAN00010471 no changes
                                ESCAN00010498 Wrong Fast BusOff recovery time
  3.64.00   2005-01-18  Js      ESCAN00010855 CarWakeUp for special OEM introduced
  3.65.00   2005-03-29  Js      ESCAN00011622 Extensions for special OEM re-integrated
                                ESCAN00011925 Compile issue in special configuration for indexed NM
                                ESCAN00011970 Standard vector type qualifier implemented
                                ESCAN00011997 ECU's NM does not participate on a bus in a valid way
  3.66.00   2005-07-11  Js      ESCAN00012831 Extensions for special OEM re-integrated
                                ESCAN00013626 Fixed by ESCAN00012831
                                ESCAN00012842 Include structure adapted
                                ESCAN00012901 Unexpected user data for special OEM
                                ESCAN00012928 kNmBugfixVersion renamed to kNmReleaseVersion
  3.67.00   2006-01-23  Js      ESCAN00014119 changed implementation of SkippedAlive
                        vismas  ESCAN00014635 Re-integrated ErrorPin in NmPrecopy
                        vismas  ESCAN00014458 Fixed access on TX object for multiple ECUs
                        vismas  ESCAN00015016 added ORGANI filter checks
  3.68.00   2006-03-07  vismas  ESCAN00015469 corrected layout of bus diagnostic for some OEMs
  3.69.00   2006-03-16  vismas  ESCAN00015700 changed byte order within NmGetCanErrorConfig()
  3.70.00   2006-09-04  vismas  ESCAN00017526 - changed variable assignment in NmPreTransmit()
                                ESCAN00017787 - extended feature CarWakeUp for certain OEM 
                                <internal>    - moved local functions to the end of the file and 
                                                added prototypes
                                <internal>    - adapted comments and applied changes for MISRA
  3.71.00   2007-04-11  vismas  ESCAN00017962 added reset of limphome status
                                ESCAN00018325 removed volatile from variable definition
                                              removed LINT exclusions
                                ESCAN00014814 added assertion handling
                                              added support of AUTOSAR CAN interface
                                ESCAN00020078 added features for new OEM
                                ESCAN00020079 updated component to current implementation/layout rules
  3.72.00   2007-08-22  vismas  ESCAN00020303 no changes in this file
                                ESCAN00020580 removed compiler warnings for kNmEcuNr == 0x00
                                ESCAN00020743 adapted availability of channel indirection
                                ESCAN00020990 changed handling of solution for ESCAN00020580
                                ESCAN00021051 added BusOff end handling for RX of SleepAck in LimpHome
                                              added support for PostBuild in AUTOSAR environment
                                              adapted handling of variable definition and access
  3.72.01   2007-10-01  visoh   ESCAN00022595 no changes in this file
  3.72.02   2007-10-08  vismas  ESCAN00022656 no changes in this file
                                ESCAN00023028 adapted to updated AUTOSAR CAN IF
  3.73.00   2007-12-12  vismas  ESCAN00023665 made feature NM_ENABLE_EXTERNAL_CANONLINE_HANDLING available 
                                              independent of CanIf
                                ESCAN00023668 added support for new OEM
  3.74.00   2008-02-04  vismas  ESCAN00022737 no changes in this file
                                ESCAN00024379 added support of indirection to system channels (not only CAN)
                                ESCAN00022927 added feature NM_ENABLE_EARLY_BUSOFF_REINIT
                                ESCAN00023863 added platform-specific #pragma for nmSendMess
                                ------------- adapted to current coding template
                                ESCAN00022144 added CanOnline() to state change within LimpHome
                                ESCAN00024402 added condition for restart of minimum LimpHome timer
  3.74.01   2008-03-10  vismas  ------------- corrected usage of CAN API for If_AsrIfCan
  3.74.02   2008-05-21  vismas  ------------- adaption for Autosar 3.0
                                ------------- added optional callback for LimpHome Tx notification
  3.74.03   2008-06-16  vismas  ------------- removed new callback from 3.74.02
  3.75.00   2008-08-15  vismas  ESCAN00026277 changed access on DrvCan API in case of AUTOSAR usage
                                ESCAN00028050 no changes in this file
                                ESCAN00028089 changed encpasulation of condition for update of NM node table
                                ESCAN00028510 changed user data default value for special OEM
                                ESCAN00028757 added support for QNX
                                ESCAN00029951 corrected API NmGetState()
                                ESCAN00029982 made Tx counter configurable
  3.75.01   2008-09-24  visoh   ESCAN00030216 removed/replaces occurences of kCanNumberOfChannels
            2008-10-16  vismas  ESCAN00030725 adapted timing for WaitBusSleep
  3.75.02   2008-10-27  vismas  ESCAN00031148 no changes in this file
  3.75.03   2009-02-03  vismas  ESCAN00032787 adapted parameter for ApplNmCanOnline()/ApplNmCanOffline()
                                ESCAN00032811 corrected detection for node monitoring
                                ------------- added casts due to MISRA warnings
                                ------------- added MISRA justifications
  3.75.04   2009-03-20  vismas  ESCAN00033467 removed compiler warning for condition that is always true
            2009-03-25  vismas  ESCAN00033660 ApplNmBusOffEnd now not available in AUTOSAR environment
            2009-03-25  vismas  ESCAN00034057 supported new OEM
  3.75.05   2009-03-27  vismas  ESCAN00034744 ApplNmBusOffEnd now not available in AUTOSAR environment
  3.76.00   2009-05-05  vismas  ESCAN00034893 added optional callbacks for LimpHome
  3.76.01   2009-05-29  vismas  ESCAN00035240 corrected handling for critical sections in AUTOSAR environment
  3.77.00   2009-07-20  vismas  ESCAN00025937 added ApplNmBusOffChangeFastToSlow()
                                ESCAN00035150 corrected NM message reception for invalid messages
                                ESCAN00035209 no changes in this file
                                ESCAN00036712 added new OEM
                                ESCAN00036713 corrected assertion for CAN offline during Tx request
                                ESCAN00036956 added callback to Nm_AsrNmIf for external wakeup while in NM sleep state
  3.77.01   2009-10-23  vismas  ESCAN00038607 corrected encapsulation of pragma for C_COMP_MTRWRKS_MCS12X_MSCAN12
  3.77.02   2009-12-22  vismas  ESCAN00039382 No changes in this file
            2010-01-20  vismas  ESCAN00040150 No changes in this file
  3.77.03   2010-06-23  vismas  ESCAN00043531 changed order of instructions in NmCanError()
**********************************************************************************************************************/

#define V_NM_DIROSEK_SOURCE

/**********************************************************************************************************************
  Includes
**********************************************************************************************************************/
#include "nm_osek.h"



#if defined ( VGEN_ENABLE_NM_OSEK_D )


/**********************************************************************************************************************
  Version check
**********************************************************************************************************************/
/*--- check version of static files ---------------------------------------------------------------------------------*/
#if ( NM_DIROSEK_VERSION != 0x0377 )
  #error "Nm_DirOsek: Header and Source file are inconsistent (version)!"
#endif
#if ( NM_DIROSEK_RELEASE_VERSION != 0x03 )
  #error "Nm_DirOsek: Header and Source file are inconsistent (release version)!"
#endif

/*--- check version of configuration tool / generated files ---------------------------------------------------------*/
#if defined ( VGEN_GENY )
  #if defined ( NM_DIROSEKDLL_VERSION )
    #if ( NM_DIROSEKDLL_VERSION < 0x0200 )
      #error "Nm_DirOsek: This version of Nm_DirOsek requires a newer version of the Nm_DirOsek GENy DLL"
    #endif
  #else
    #error "Nm_DirOsek: 'NM_DIROSEKDLL_VERSION' is not defined. Please check your configuration file."
  #endif
#endif

/**********************************************************************************************************************
  ORGANI check
**********************************************************************************************************************/

/**********************************************************************************************************************
  Local configuration
**********************************************************************************************************************/

#if defined ( NM_ENABLE_INDEXED_NM ) || \
    defined ( NM_ENABLE_MULTIPLE_NODES )
  #define NM_INT_DISABLE_OPTIMIZED_SKIPPED_DETECTION
#else
  /* ESCAN00020990 */
  /* ESCAN00020580 */
  #if ( kNmEcuNr == 0x00 )
    #define NM_INT_ENABLE_OPTIMIZED_SKIPPED_DETECTION
  #else
    #define NM_INT_DISABLE_OPTIMIZED_SKIPPED_DETECTION
  #endif
#endif

/**********************************************************************************************************************
  Configuration check
**********************************************************************************************************************/
/*--- check system setup ----------------------------------------------------*/
#if defined ( VGEN_ENABLE_NM_OSEK_D )
#else
  #error "Nm_DirOsek: Source is part of the project, but not part of the system configuration."
#endif

#if defined ( C_CPUTYPE_BITORDER_MSB2LSB ) || \
    defined ( C_CPUTYPE_BITORDER_LSB2MSB )
#else
  #error "Nm_DirOsek: Unknown/invalid setting for CPUTYPE"
#endif

/*--- check channel assignment ----------------------------------------------*/
#if defined ( kNmNumberOfChannels )
  #if ( kNmNumberOfChannels < 1 )
    #error "Nm_DirOsek: Invalid value of 'kNmNumberOfChannels'."
  #endif
#else
  #error "Nm_DirOsek: 'kNmNumberOfChannels' is not defined. Please check your configuration file."
#endif


/*--- check timing values ---------------------------------------------------*/


/*--- check features --------------------------------------------------------*/
/*
 * Name:        NM_ENABLE_CHANNEL_INDIRECTION
 * Description: This define enables/disables 
 * Origin:      GenTool system configuration
 */
#if defined ( NM_ENABLE_CHANNEL_INDIRECTION )
  #if defined ( NM_ENABLE_INDEXED_NM )
  #else
    #error "Nm_DirOsek: Systems with channel indirection need indexed NM."
  #endif
#endif

#if defined ( NM_ENABLE_COPY_RINGDATA )
  #if defined ( NM_ENABLE_COPY_RINGDATA_TO_TEMPBUFFER )
    #error "Nm_DirOsek: Copy of Ringdata only possible if temporary buffer for ringdata is disabled"
  #endif
#endif

#if defined ( NM_ENABLE_CONFIG )
  #if defined ( NM_NUMBER_OF_CONFIG_NODES )
    #if ( (  (NM_NUMBER_OF_CONFIG_NODES) > 0)       && \
          ( ((NM_NUMBER_OF_CONFIG_NODES) % 8) == 0) && \
          (  (NM_NUMBER_OF_CONFIG_NODES) <= 256) )
    #else
      #error "Nm_DirOsek: Invalid value of NM_NUMBER_OF_CONFIG_NODES."
    #endif
  #else
    #error "Nm_DirOsek: NM_NUMBER_OF_CONFIG_NODES is not defined."
  #endif
#endif

#if defined ( NM_ENABLE_CONFIG )
  #if defined ( NM_NUMBER_OF_CONFIG_NODES )
  #else
    #error "Nm_DirOsek: NM_NUMBER_OF_CONFIG_NODES is not defined."
  #endif
#endif

#if defined ( NM_ENABLE_EARLY_BUSOFF_REINIT )
  #if defined ( C_ENABLE_DRIVER_STATUS )
  #else
    #error "Nm_DirOsek: Feature 'NM_ENABLE_EARLY_BUSOFF_REINIT' requires a DrvCan that supports 'C_ENABLE_DRIVER_STATUS' "
  #endif
#endif

/**********************************************************************************************************************
  Local data defines
**********************************************************************************************************************/
/* 
 * Name:        kNmTxMsgSize
 *              tNmTxMsgType
 * Description: These defines determine the internal representation of the NM message.
 *              Depending on the used CPU type, the most efficient access is used.
 */
#if defined ( C_CPUTYPE_8BIT )
  #define kNmTxMsgSize            8
  #define tNmTxMsgType            vuint8
#else
  #if defined ( C_CPUTYPE_16BIT )
    #define kNmTxMsgSize          4
    #define tNmTxMsgType          vuint16
  #else
    #if defined ( C_CPUTYPE_32BIT )
      #define kNmTxMsgSize        2
      #define tNmTxMsgType        vuint32
    #else
      #error "Nm_DirOsek: Missing/Unknown setting for C_CPUTYPE_xBIT. Please check v_cfg.h."
    #endif
  #endif
#endif

/* 
 * Name:        RX_CNT_...
 *              TX_CNT_...
 * Description: These are the masks, thresholds and increments for the
 *              NM RX and TX counters.
 */
#define RX_CNT_MASK               ((vuint8)0x0F)
#define RX_CNT_STEP               ((vuint8)0x01)
#define TX_CNT_MASK               ((vuint8)0xF0)
#define TX_CNT_STEP               ((vuint8)0x10)

#if defined ( RX_CNT_MAX )
/* Note: RX_CNT_MAX can be configured in the user configuration file */
#else
  #define RX_CNT_MAX              ((vuint8)4)
#endif

  /* ESCAN00029982 */
  #if defined ( TX_CNT_MAX )
/* Note: TX_CNT_MAX can be configured in the user configuration file */
  #else
    #define TX_CNT_MAX              ((vuint8)8)
  #endif

#if defined ( NM_ENABLE_CONFIG ) 
/* 
 * Name:        BYTE_OFFSET_MASK
 * Description: This mask is used for calculation of the desired entry 
 *              within the node and/or error configuration table
 */
  #define BYTE_OFFSET_MASK        ((vuint8)0x07)
#endif

/*--- symbolic values for states ---------------------------------------------*/
/* 
 * Name:        NM_ACTION_...
 * Description: These are the symbolic names of the states of the NM state machine.
 */
#define NO_ACTION                     ((NmActionType)0x00)
#define NM_ACTION_START               ((NmActionType)0x01)
#define NM_ACTION_WAIT_SENDTOKEN      ((NmActionType)0x02)
#define NM_ACTION_WAIT_RINGMSG        ((NmActionType)0x03)
#define NM_ACTION_LH_WAIT_LIMPHOME_TX ((NmActionType)0x04)
#define NM_ACTION_LH_PREPARE_SLEEP    ((NmActionType)0x05)
#define NM_ACTION_GO_BUSSLEEP         ((NmActionType)0x06)
#define NM_ACTION_BUS_SLEEP           ((NmActionType)0x07)
#define NM_ACTION_REPEAT              ((NmActionType)0x80)



/* Defines for NM message bits */
#if defined ( NM_TYPE_GAC_OSEK ) 
  #define ALIVE                     ((vuint8)0x01)
  #define RING                      ((vuint8)0x02)
  #define LIMPHOME                  ((vuint8)0x04)

  #define SLEEP_IND                 ((vuint8)0x10)
  #define SLEEP_ACK                 ((vuint8)0x20)

  #define CTRL_INIT                 ((vuint8)0x00)
  #define DATA_INIT                 ((vuint8)0x00)
#endif

/**********************************************************************************************************************
  Local macro defines
**********************************************************************************************************************/
/*-----------------------------------------------------------------------------
 * function-like macros
 *---------------------------------------------------------------------------*/
#if defined ( NM_ENABLE_ASSERTIONS )
  /*
   * Name:        NmAssert() 
   *              NmAssertAlways()
   * Description: These macro are used for assertion handling during system integration and test.
   */
  #define NmAssert(p, e)         if((p)==0) ApplNmDirOsekFatalError(e) /* PRQA S 3412 */ /* used for optimization reason */
  #define NmAssertAlways(p, e)   ( ApplNmDirOsekFatalError(e) ) /* PRQA S 3453 */ /* macro used for optimization reason */
#else
  #define NmAssert(p, e)
  #define NmAssertAlways(p, e)
#endif


/*
 * Name:        NmCalculateConfigByte()
 * Description: This macro is used to calculate the byte for access the node and/or error configuration array.
 */
#if defined ( NM_ENABLE_INDEXED_NM ) || \
    defined ( NM_ENABLE_MULTIPLE_NODES )
  #define NmCalculateConfigByte(i)  (vuint8)((vuint8)((i)>>3) + (channel*(vuint8)((NM_NUMBER_OF_CONFIG_NODES)/8)))  /* PRQA S 3453 */ /* macro used for optimization reason */
  #define NmCalculateOwnConfigByte(i)  (vuint8)((vuint8)((i)>>3) + (channel*(vuint8)((NM_NUMBER_OF_CONFIG_NODES)/8))) /* PRQA S 3453 */ /* macro used for optimization reason */
#else
  /* ESCAN00032811 */
  #define NmCalculateConfigByte(i)  (vuint8)((i)>>3)  /* PRQA S 3453 */ /* macro used for optimization reason */
  #if ( kNmEcuNr <= 0x07 )
    #define NmCalculateOwnConfigByte(i)  0
  #else
    #define NmCalculateOwnConfigByte(i)  (vuint8)((i)>>3) /* PRQA S 3453 */ /* macro used for optimization reason */
  #endif
#endif

/*
 * Name:        NmResetNmStatusRxFlags()
 * Description: This macro is used to reset the low nibble of nmStateByteLocal.
 */
#define NmResetNmStatusRxFlags()    (nmStateByteLocal &= (vuint8)0xF0)

/*
 * Name:        NmGetRxMsgSourceAdr()
 * Description: This macro is used to determine the CAN ID of a received NM message.
 * Note:        This macro is only valid in NmPrecopy().
 */
#if defined ( NM_ENABLE_INDEXED_DRVCAN ) || \
    defined ( C_SINGLE_RECEIVE_CHANNEL )
  #define NmGetRxMsgSourceAdr()     ((vuint8)((vuint8)(CanRxActualId(rxStruct)) & kNmSourceMask))
#else
  #define NmGetRxMsgSourceAdr()     ((vuint8)((vuint8)(CanRxActualId      ) & kNmSourceMask))
#endif

/*-----------------------------------------------------------------------------
 * wrapper-like macros
 *---------------------------------------------------------------------------*/
/* multi-channel CAN driver */
#if defined ( C_SINGLE_RECEIVE_BUFFER ) || \
    defined ( C_MULTIPLE_RECEIVE_BUFFER )
  #if defined ( NM_CAN_CHANNEL )
    #if ( NM_CAN_CHANNEL == 0 )
      #define CanRxActualId             CanRxActualId_0
      #define CanTransmit               CanTransmit_0
      #define NmCanResetBusOffStart(a)  CanResetBusOffStart_0(a)
      #define NmCanResetBusOffEnd(a)    CanResetBusOffEnd_0(a)
      #define NmCanResetBusSleep(a)     CanResetBusSleep_0(a)
      #define NmCanOffline              CanOffline_0
      #define NmCanOnline               CanOnline_0
      #define CanInterruptDisable       CanInterruptDisable_0
      #define CanInterruptRestore       CanInterruptRestore_0
      #define CanRxActualDLC            CanRxActualDLC_0
      #define NmConfirmation            NmConfirmation_0
      #define NmPrecopy                 NmPrecopy_0
      #define NmCanError                NmCanError_0
      #define nmSendMess                nmSendMess_0
    #endif
    #if ( NM_CAN_CHANNEL == 1 )
      #define CanRxActualId             CanRxActualId_1
      #define CanTransmit               CanTransmit_1
      #define NmCanResetBusOffStart(a)  CanResetBusOffStart_1(a)
      #define NmCanResetBusOffEnd(a)    CanResetBusOffEnd_1(a)
      #define NmCanResetBusSleep(a)     CanResetBusSleep_1(a)
      #define NmCanOffline              CanOffline_1
      #define NmCanOnline               CanOnline_1
      #define CanInterruptDisable       CanInterruptDisable_1
      #define CanInterruptRestore       CanInterruptRestore_1
      #define CanRxActualDLC            CanRxActualDLC_1
      #define NmConfirmation            NmConfirmation_1
      #define NmPrecopy                 NmPrecopy_1
      #define NmCanError                NmCanError_1
      #define nmSendMess                nmSendMess_1
    #endif
    #if ( NM_CAN_CHANNEL == 2 )
      #define CanRxActualId             CanRxActualId_2
      #define CanTransmit               CanTransmit_2
      #define NmCanResetBusOffStart(a)  CanResetBusOffStart_2(a)
      #define NmCanResetBusOffEnd(a)    CanResetBusOffEnd_2(a)
      #define NmCanResetBusSleep(a)     CanResetBusSleep_2(a)
      #define NmCanOffline              CanOffline_2
      #define NmCanOnline               CanOnline_2
      #define CanInterruptDisable       CanInterruptDisable_2
      #define CanInterruptRestore       CanInterruptRestore_2
      #define CanRxActualDLC            CanRxActualDLC_2
      #define NmConfirmation            NmConfirmation_2
      #define NmPrecopy                 NmPrecopy_2
      #define NmCanError                NmCanError_2
      #define nmSendMess                nmSendMess_2
    #endif
    #if ( NM_CAN_CHANNEL == 3 )
      #define CanRxActualId             CanRxActualId_3
      #define CanTransmit               CanTransmit_3
      #define NmCanResetBusOffStart(a)  CanResetBusOffStart_3(a)
      #define NmCanResetBusOffEnd(a)    CanResetBusOffEnd_3(a)
      #define NmCanResetBusSleep(a)     CanResetBusSleep_3(a)
      #define NmCanOffline              CanOffline_3
      #define NmCanOnline               CanOnline_3
      #define CanInterruptDisable       CanInterruptDisable_3
      #define CanInterruptRestore       CanInterruptRestore_3
      #define CanRxActualDLC            CanRxActualDLC_3
      #define NmConfirmation            NmConfirmation_3
      #define NmPrecopy                 NmPrecopy_3
      #define NmCanError                NmCanError_3
      #define nmSendMess                nmSendMess_3
    #endif
    #if ( NM_CAN_CHANNEL == 4 )
      #define CanRxActualId             CanRxActualId_4
      #define CanTransmit               CanTransmit_4
      #define NmCanResetBusOffStart(a)  CanResetBusOffStart_4(a)
      #define NmCanResetBusOffEnd(a)    CanResetBusOffEnd_4(a)
      #define NmCanResetBusSleep(a)     CanResetBusSleep_4(a)
      #define NmCanOffline              CanOffline_4
      #define NmCanOnline               CanOnline_4
      #define CanInterruptDisable       CanInterruptDisable_4
      #define CanInterruptRestore       CanInterruptRestore_4
      #define CanRxActualDLC            CanRxActualDLC_4
      #define NmConfirmation            NmConfirmation_4
      #define NmPrecopy                 NmPrecopy_4
      #define NmCanError                NmCanError_4
      #define nmSendMess                nmSendMess_4
    #endif
  #endif
#endif

#if defined ( NM_ENABLE_EXTERNAL_CANONLINE_HANDLING )
  /* CanOnline()/CanOffline() is handled by application */
  /* ESCAN00023665 */ /* ESCAN00032787 */
  #if defined ( NM_ENABLE_INDEXED_DRVCAN )
    #define NmCanOnline(c)              ApplNmCanOnline(c)   /* PRQA S 3453 */ /* macro used for optimization reason */
    #define NmCanOffline(c)             ApplNmCanOffline(c)  /* PRQA S 3453 */ /* macro used for optimization reason */
  #else
    #define NmCanOnline(c)              ApplNmCanOnline()   /* PRQA S 3453 */ /* macro used for optimization reason */
    #define NmCanOffline(c)             ApplNmCanOffline()  /* PRQA S 3453 */ /* macro used for optimization reason */
  #endif
#else
  /* CanOnline()/CanOffline() is handled by Nm_DirOsek */
    #if defined ( NM_ENABLE_INDEXED_DRVCAN )
      #define NmCanOnline(c)              CanOnline(c)   /* PRQA S 3453 */ /* macro used for optimization reason */
      #define NmCanOffline(c)             CanOffline(c)  /* PRQA S 3453 */ /* macro used for optimization reason */
    #else
      #define NmCanOnline(c)              CanOnline()   /* PRQA S 3453 */ /* macro used for optimization reason */
      #define NmCanOffline(c)             CanOffline()  /* PRQA S 3453 */ /* macro used for optimization reason */
    #endif
#endif


    #if defined( NM_ENABLE_INDEXED_DRVCAN )
      #define NmCanResetBusOffStart(c, s)   CanResetBusOffStart(c, s) /* PRQA S 3453 */ /* macro used for optimization reason */
      #define NmCanResetBusOffEnd(c, s)     CanResetBusOffEnd(c, s) /* PRQA S 3453 */ /* macro used for optimization reason */
      #define NmCanResetBusSleep(c, s)      CanResetBusSleep(c, s) /* PRQA S 3453 */ /* macro used for optimization reason */
    #else
      #define NmCanResetBusOffStart(s)      CanResetBusOffStart(s) /* PRQA S 3453 */ /* macro used for optimization reason */
      #define NmCanResetBusOffEnd(s)        CanResetBusOffEnd(s) /* PRQA S 3453 */ /* macro used for optimization reason */
      #define NmCanResetBusSleep(s)         CanResetBusSleep(s) /* PRQA S 3453 */ /* macro used for optimization reason */
    #endif


/*-----------------------------------------------------------------------------
 * macros for RX buffer (on-chip receive buffer)
 *---------------------------------------------------------------------------*/
/*
 * Name:        nmRxMsgBuffer
 * Description: 
 */
  #if defined ( C_SINGLE_RECEIVE_BUFFER )
    #if defined ( NM_CAN_CHANNEL )
      #if ( NM_CAN_CHANNEL == 0 )
        #define nmRxMsgBuffer               ((CanChipDataPtr)(CanRDSPtr_0))
      #endif
      #if ( NM_CAN_CHANNEL == 1 )
        #define nmRxMsgBuffer               ((CanChipDataPtr)(CanRDSPtr_1))
      #endif
      #if ( NM_CAN_CHANNEL == 2 )
        #define nmRxMsgBuffer               ((CanChipDataPtr)(CanRDSPtr_2))
      #endif
      #if ( NM_CAN_CHANNEL == 3 )
        #define nmRxMsgBuffer               ((CanChipDataPtr)(CanRDSPtr_3))
      #endif
    #else
      #define nmRxMsgBuffer                 ((CanChipDataPtr)(CanRDSPtr))
    #endif
  #endif
  #if defined ( C_MULTIPLE_RECEIVE_BUFFER )
    #define nmRxMsgBuffer                   ((CanChipDataPtr)(rxDataPtr))
  #endif
  #if defined ( NM_ENABLE_INDEXED_DRVCAN ) || \
      defined ( C_SINGLE_RECEIVE_CHANNEL )
    #define nmRxMsgBuffer                   ((CanChipDataPtr)(rxStruct->pChipData))
  #endif


/*-----------------------------------------------------------------------------
 * macros for variable access
 *---------------------------------------------------------------------------*/
/* nmState */
#define nmStateByteGlobal            NMVAR(nmState).c[0]
#define nmStateByteLocal             NMVAR(nmState).c[1]
#define nmStateRingStable            NMVAR(nmState).b.b_RingStable
#define mmStateBusError              NMVAR(nmState).b.b_BusError
#define nmStateActive                NMVAR(nmState).b.b_Active
#define nmStateLimpHome              NMVAR(nmState).b.b_LimpHome
#define nmStateBusSleep              NMVAR(nmState).b.b_BusSleep
#define nmStateWaitBusSleep          NMVAR(nmState).b.b_WaitBusSleep
  #define nmStateTxRingDataAllow     NMVAR(nmState).b.b_TxRingDataAllow
#define nmStateBusSleepInd           NMVAR(nmState).b.b_BusSleepInd
#define nmStateNmMsgRecv             NMVAR(nmState).b.b_NmMsgRecv
#define nmStateRingMsgRecv           NMVAR(nmState).b.b_RingMsgRecv
#define nmStateImAddressed           NMVAR(nmState).b.b_ImAddressed
#define nmStateImSkippedOver         NMVAR(nmState).b.b_ImSkippedOver
#define nmStateNmMsgRecvRemind       NMVAR(nmState).b.b_NmMsgRecvRemind
#define nmStateRxTxLockUd            NMVAR(nmState).b.b_RxTxLockUd  /* ESCAN00008104 */
#define nmStateRingPreStable         NMVAR(nmState).b.b_RingPreStable
#define nmStatePrepSleep             NMVAR(nmState).b.b_PrepSleep



/* nmSendMess */
  #define NmTxMsgFlagSleepAck         (*(tNmTxMsgTypeUnion*)NMVAR(nmSendMess)).b.bSleepAck
  #define NmTxMsgFlagSleepInd         (*(tNmTxMsgTypeUnion*)NMVAR(nmSendMess)).b.bSleepInd
  #define NmTxMsgFlagConfig           (*(tNmTxMsgTypeUnion*)NMVAR(nmSendMess)).b.bConfig
  #define NmTxMsgByte0                (*(tNmTxMsgTypeUnion*)NMVAR(nmSendMess)).c[0]
  #define NmTxMsgByte1                (*(tNmTxMsgTypeUnion*)NMVAR(nmSendMess)).c[1]
  #define NmTxMsgByte2                (*(tNmTxMsgTypeUnion*)NMVAR(nmSendMess)).c[2]
    #define NmTxMsgByteCmd            (*(tNmTxMsgTypeUnion*)NMVAR(nmSendMess)).b.cCmd
    #define NmTxMsgFlagCmdSet         (*(tNmTxMsgTypeUnion*)NMVAR(nmSendMess)).b.cCmd
    #define NmTxMsgFlagCmdIf          (*(tNmTxMsgTypeUnion*)NMVAR(nmSendMess)).b.cCmd
    #define NmTxMsgByteDest           (*(tNmTxMsgTypeUnion*)NMVAR(nmSendMess)).c[0]
    #define NmTxMsgByteUser0          (*(tNmTxMsgTypeUnion*)NMVAR(nmSendMess)).c[2]
    #define NmTxMsgByteUser1          (*(tNmTxMsgTypeUnion*)NMVAR(nmSendMess)).c[3]
    #define NmTxMsgByteUser2          (*(tNmTxMsgTypeUnion*)NMVAR(nmSendMess)).c[4]
    #define NmTxMsgByteUser3          (*(tNmTxMsgTypeUnion*)NMVAR(nmSendMess)).c[5]
    #define NmTxMsgByteUser4          (*(tNmTxMsgTypeUnion*)NMVAR(nmSendMess)).c[6]
    #define NmTxMsgByteUser5          (*(tNmTxMsgTypeUnion*)NMVAR(nmSendMess)).c[7]

/* nmRxMsgBuffer */
  #define nmRxMsgFlagDestAdr        ((vuint8)(nmRxMsgBuffer[0]))
  #define nmRxMsgFlagCmd            ((vuint8)(nmRxMsgBuffer[1] & (vuint8)0x0F))
  #define nmRxMsgFlagSleepInd       ((vuint8)(nmRxMsgBuffer[1] & SLEEP_IND))
  #define nmRxMsgFlagSleepAck       ((vuint8)(nmRxMsgBuffer[1] & SLEEP_ACK))

  #define nmRxMsgUserStartAdr               (&nmRxMsgBuffer[2])
  #define nmRxMsgByteUser0          ((vuint8)(nmRxMsgBuffer[2]))
  #define nmRxMsgByteUser1          ((vuint8)(nmRxMsgBuffer[3]))
  #define nmRxMsgByteUser2          ((vuint8)(nmRxMsgBuffer[4]))
  #define nmRxMsgByteUser3          ((vuint8)(nmRxMsgBuffer[5]))
  #define nmRxMsgByteUser4          ((vuint8)(nmRxMsgBuffer[6]))
  #define nmRxMsgByteUser5          ((vuint8)(nmRxMsgBuffer[7]))


/*-----------------------------------------------------------------------------
 * macros for configuration access
 *---------------------------------------------------------------------------*/
#if defined ( NM_ENABLE_INDEXED_NM )
  #define NMCFG_COUNT_RINGTYP             NmCountRingTyp_Field[channel]
  #define NMCFG_COUNT_RINGMAX             NmCountRingMax_Field[channel]
  #define NMCFG_COUNT_LIMPHOME            NmCountLimphome_Field[channel]
  #define NMCFG_COUNT_WAITBUSSLEEP        NmCountWaitBussleep_Field[channel]
  #define kNmCfg_CanPara                  (CanInitHandle)NmCanPara_Field[channel]
#else
  #define NMCFG_COUNT_RINGTYP             NM_COUNT_RING_TYP
  #define NMCFG_COUNT_RINGMAX             NM_COUNT_RING_MAX
  #define NMCFG_COUNT_LIMPHOME            NM_COUNT_LIMPHOME
  #define NMCFG_COUNT_WAITBUSSLEEP        NM_COUNT_WAIT_BUSSLEEP
  #define kNmCfg_CanPara                  (CanInitHandle)kNmCanPara
#endif



  #if defined ( NM_ENABLE_INDEXED_NM )
    #if defined ( NM_ENABLE_MULTIPLE_NODES )
      #define kNmCfg_EcuNr                  nmEcuNr_FieldMultipleNodes[channel]
      #define kNmCfg_TxObj                  nmTxObj_FieldMultipleNodes[channel]
    #else
      #define kNmCfg_EcuNr                  NmEcuNr_Field[channel]
      #define kNmCfg_TxObj                  NmTxObj_Field[channel]
    #endif
  #else
    #if defined ( NM_ENABLE_MULTIPLE_NODES )
      #if defined ( NM_CAN_CHANNEL )
        #define kNmCfg_EcuNr                NmEcuNr_Field[comMultipleECUCurrent[NM_CAN_CHANNEL]]
        #define kNmCfg_TxObj                NmTxObj_Field[comMultipleECUCurrent[NM_CAN_CHANNEL]]
      #else
        #define kNmCfg_EcuNr                NmEcuNr_Field[comMultipleECUCurrent]
        #define kNmCfg_TxObj                NmTxObj_Field[comMultipleECUCurrent]
      #endif
    #else
        #define kNmCfg_EcuNr                kNmEcuNr
        #define kNmCfg_TxObj                kNmTxObj
    #endif
  #endif

/* 
 * Name:        kNmSourceMask 
 * Description: This mask is used to determine the assigned station address 
 *              of a received NM message.
 * Note:        Only valid within NmPrecopy()
 */
#if defined ( VGEN_GENY )
/* GENy generates the mask information depending on the DBC attribute NmMessageCount */
  #if defined ( NM_ENABLE_INDEXED_NM )
    #if ( kNmNumberOfRanges > 1 )
      #define kNmSourceMask               (NmRangeMask_Field[channel])
    #else
      #define kNmSourceMask               ((vuint8)NM_RANGE_MASK)
    #endif
  #else
    #define   kNmSourceMask               ((vuint8)NM_RANGE_MASK)
  #endif
#endif



/**********************************************************************************************************************
  Local data types and structures
**********************************************************************************************************************/
/****************************************
 * Name:        NmActionType
 * Description: This type is used for the state of the NM state machine.
 */
typedef vuint8 NmActionType;

/****************************************
 * Name:        tNmTimeCnt
 * Description: This type is used for the NM task counter.
 * Note       : The value range of the counter may depend on the used features.
 */
typedef vuint16 tNmTimeCnt;

/****************************************
 * Name:        tNmStateType
 * Description: This type represents the various status flags.
 */
typedef union
{ /* PRQA S 0750 */ /* union used for optimization reason */
  vuint8 c[2];

  #if defined ( C_CPUTYPE_BITORDER_MSB2LSB )
  struct 
  {
    vbittype    b_BusSleepInd     :1;     /* byte0 bit7 */
    vbittype    b_TxRingDataAllow :1;     /* byte0 bit6 */
    vbittype    b_WaitBusSleep    :1;     /* byte0 bit5 */
    vbittype    b_BusSleep        :1;     /* byte0 bit4 */
    vbittype    b_LimpHome        :1;     /* byte0 bit3 */
    vbittype    b_Active          :1;     /* byte0 bit2 */
    vbittype    b_BusError        :1;     /* byte0 bit1 */
    vbittype    b_RingStable      :1;     /* byte0 bit0 */

    vbittype    b_PrepSleep       :1;     /* byte1 bit7 */
    vbittype    b_RingPreStable   :1;     /* byte1 bit6 */
    vbittype    b_RxTxLockUd      :1;     /* byte1 bit5 */  /* ESCAN00008104 */
    vbittype    b_NmMsgRecvRemind :1;     /* byte1 bit4 */
    vbittype    b_ImSkippedOver   :1;     /* byte1 bit3 */
    vbittype    b_ImAddressed     :1;     /* byte1 bit2 */
    vbittype    b_RingMsgRecv     :1;     /* byte1 bit1 */
    vbittype    b_NmMsgRecv       :1;     /* byte1 bit0 */
  }b;
  #else
  struct /* PRQA S 0635 */ /* behaviour of the struct within union explicetly checked */
  {
    vbittype    b_RingStable      :1;     /* byte0 bit0 */
    vbittype    b_BusError        :1;     /* byte0 bit1 */
    vbittype    b_Active          :1;     /* byte0 bit2 */
    vbittype    b_LimpHome        :1;     /* byte0 bit3 */
    vbittype    b_BusSleep        :1;     /* byte0 bit4 */
    vbittype    b_WaitBusSleep    :1;     /* byte0 bit5 */
    vbittype    b_TxRingDataAllow :1;     /* byte0 bit6 */
    vbittype    b_BusSleepInd     :1;     /* byte0 bit7 */

    vbittype    b_NmMsgRecv       :1;     /* byte1 bit0 */
    vbittype    b_RingMsgRecv     :1;     /* byte1 bit1 */
    vbittype    b_ImAddressed     :1;     /* byte1 bit3 */
    vbittype    b_ImSkippedOver   :1;     /* byte1 bit4 */
    vbittype    b_NmMsgRecvRemind :1;     /* byte1 bit6 */
    vbittype    b_RxTxLockUd      :1;     /* byte1 bit5 */  /* ESCAN00008104 */
    vbittype    b_RingPreStable   :1;     /* byte1 bit6 */
    vbittype    b_PrepSleep       :1;     /* byte1 bit7 */
  }b;
  #endif
} tNmStateType;


/****************************************
 * Name:        tNmTxMsgTypeUnion
 * Description: This type represents the message layout of the NM TX message.
 */
typedef union
{ /* PRQA S 0750 */ /* union used for optimization reason */
  vuint8 c[8];

  #if defined ( C_CPUTYPE_BITORDER_MSB2LSB )
  struct
  {
    vbittype cDest          :8;   /* byte0 bit07..00 */
    vbittype bReserved0     :1;   /* byte1 bit15 */
    vbittype bConfig        :1;   /* byte1 bit14 */
    vbittype bSleepAck      :1;   /* byte1 bit13 */
    vbittype bSleepInd      :1;   /* byte1 bit12 */
    vbittype cCmd           :4;   /* byte1 bit11..08 */
                                  /* byte2..7 are accessed by byte element of union */
  }b;
  #else
  struct /* PRQA S 0635 */ /* behaviour of the struct within union explicetly checked */
  {
    vbittype cDest          :8;   /* byte0 bit07..00 */
    vbittype cCmd           :4;   /* byte1 bit11..08 */
    vbittype bSleepInd      :1;   /* byte1 bit12 */
    vbittype bSleepAck      :1;   /* byte1 bit13 */
    vbittype bConfig        :1;   /* byte1 bit14 */
    vbittype bReserved0     :1;   /* byte1 bit15 */
                                  /* byte2..7 are accessed by byte element of union */
  }b;
  #endif
} tNmTxMsgTypeUnion;


/**********************************************************************************************************************
  Global data definitions (ROM)
**********************************************************************************************************************/

V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kNmMainVersion    = (vuint8)(NM_DIROSEK_VERSION >> 8);
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kNmSubVersion     = (vuint8)(NM_DIROSEK_VERSION & 0xFF);
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kNmReleaseVersion = (vuint8)(NM_DIROSEK_RELEASE_VERSION);


/**********************************************************************************************************************
  Global data definitions (RAM)
**********************************************************************************************************************/


/****************************************
* Name       : nmSendMess
* Description: 
* Values     : 
* Note       : Name is fix, as it is used by the CAN driver
*/
    #if defined ( C_COMP_MTRWRKS_MCS12X_MSCAN12 )
      /* ESCAN00023863 */
      #if defined(C_ENABLE_XGATE_USED) /* ESCAN00038607 */
        #pragma DATA_SEG SEGDRV_XGATE_SHARED
      #endif
    #endif
V_MEMRAM0 V_MEMRAM1_NEAR vuint8 V_MEMRAM2_NEAR NMVAR_CH_DEF(nmSendMess)[8];
    #if defined ( C_COMP_MTRWRKS_MCS12X_MSCAN12 )
      /* ESCAN00023863 */
      #if defined(C_ENABLE_XGATE_USED) /* ESCAN00038607 */
        #pragma DATA_SEG DEFAULT
      #endif
    #endif


/**********************************************************************************************************************
  Local data definitions (ROM)
**********************************************************************************************************************/

/**********************************************************************************************************************
  Local data definitions (RAM)
**********************************************************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
  Page0
*--------------------------------------------------------------------------------------------------------------------*/

/****************************************
* Name:        nmState
* Description: 
* Values:      
*/
static tNmStateType MEMORY_NEAR NMVAR_CH_DEF(nmState); /* PRQA S 0759 */ /* union used for optimization reason */

/****************************************
* Name:        nmTxRequest
* Description: ESCAN00004259
* Values:      
*/
static volatile vuint8 MEMORY_NEAR NMVAR_CH_DEF(nmTxRequest);


#if defined ( NM_ENABLE_MULTIPLE_NODES )
/****************************************
* Name:        nmEcuNr_FieldMultipleNodes
* Description: 
* Values:      
*/
  #if defined ( NM_ENABLE_INDEXED_NM )
static vuint8 MEMORY_NEAR nmEcuNr_FieldMultipleNodes[kNmNumberOfChannels];
  #else
/* not possible */
  #endif
#endif

#if defined ( NM_ENABLE_MULTIPLE_NODES )
/****************************************
* Name:        nmTxObj_FieldMultipleNodes
* Description: 
* Values:      
*/
  #if defined ( NM_ENABLE_INDEXED_NM )
static vuint8 MEMORY_NEAR nmTxObj_FieldMultipleNodes[kNmNumberOfChannels];
  #else
/* not possible */
  #endif
#endif



/*---------------------------------------------------------------------------------------------------------------------
  Extended page
*--------------------------------------------------------------------------------------------------------------------*/

#if defined ( NM_ENABLE_COPY_RINGDATA_TO_TEMPBUFFER )
/****************************************
 * Name:        nmUserDataBuffer
 * Description: 
 * Values:      
 */
static vuint8 NMVAR_CH_DEF(nmUserDataBuffer)[6];
#endif








/****************************************
* Name:        nmTimeCnt
* Description: 
* Values:      
*/
static tNmTimeCnt NMVAR_CH_DEF(nmTimeCnt);

/****************************************
* Name:        nmAction
* Description: 
* Values:      
*/
static NmActionType NMVAR_CH_DEF(nmAction);

/****************************************
* Name:        nmRxNmMsgSourceAdr
* Description: 
* Values:      
*/
static vuint8 NMVAR_CH_DEF(nmRxNmMsgSourceAdr);

/****************************************
* Name:        nmRxTxCnt
* Description: 
* Values:      
*/
static vuint8 NMVAR_CH_DEF(nmRxTxCnt);

/****************************************
* Name:        nmLogicalSuccessor
* Description: 
* Values:      
*/
static vuint8 NMVAR_CH_DEF(nmLogicalSuccessor);

#if defined ( NM_ENABLE_CONFIG )
/****************************************
* Name:        nmConfig
* Description: 
* Values:      
* Notes      : This variable is identical for single/multi channel systems.
*              The channel-dependency is handled by the type of the variable.
*/
static NmConfigType nmConfig;
#endif











#if defined ( NM_ENABLE_EARLY_BUSOFF_REINIT )
/* ESCAN00022927 */
/****************************************
* Name:        nmDrvCanIsBusOff
* Description: This flag indicates if the DrvCan is in BusOf state.
*              This flag is set upon BusOff event and cleared as soon the DrvCan is re-init within CanResetBusOffEnd().
* Values:      
*/
static vuint8 NMVAR_CH_DEF(nmDrvCanIsBusOff);
#endif


/**********************************************************************************************************************
  Local function prototypes
**********************************************************************************************************************/
static void NmTransmitSkippedAlive( NM_CHANNEL_NMTYPE_ONLY );
static void NmResetNodeConfig( NM_CHANNEL_NMTYPE_ONLY );


extern vuint16 CanNmGetBusOffWaitTime(void);
/**********************************************************************************************************************
  Global function definitions
**********************************************************************************************************************/
/******************************************************************************
 * Name:            NmCanError
 * Called by:       CAN driver
 * Parameter:       (CAN channel)
 * Return value:    ---
 * Description:     This API informs the NM about a BusOff event.
 * Precondition:    ---
 *****************************************************************************/
void NM_INTERNAL_CALL_TYPE NmCanError(NM_CHANNEL_CANTYPE_ONLY)
{
# if defined ( NM_ENABLE_INDEXED_NM )
#  if defined ( NM_ENABLE_CHANNEL_INDIRECTION )
  channel = NmCanToNmIndirection[channel]; /* ESCAN00032787 */
#  endif
# else
#  if defined ( NM_ENABLE_INDEXED_DRVCAN )
#   if defined ( NM_CAN_CHANNEL )
#    if defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  channel = channel; /* PRQA S 3199 */ /* dummy assignment for unused parameter */
#    endif
#   endif
#  endif
# endif

  mmStateBusError = 1; /* ESCAN00043531 */

  NmCanOffline(NM_CHANNEL_CANPARA_ONLY);


#  if defined ( NM_ENABLE_INDEXED_DRVCAN )
  /* code: macros must be encapsulated in this way */
  NmCanResetBusOffStart((vuint8)NM_CHANNEL_CANPARA_ONLY, kNmCfg_CanPara);
#  else
  NmCanResetBusOffStart(kNmCfg_CanPara);
#  endif

  if( (nmStatePrepSleep == 1) && \
      ((nmStateBusSleep == 1) || (nmStateWaitBusSleep == 1)) )
  {
    /* ESCAN00009420:
     * There was a BusOff after the SleepAck, i.e. while the NM is about to be in sleep mode
     * Hold the Sleep state regardless of BusOff - restart always with Reset Alive.
     * The call of ApplNmBusOff() and ApplNmBusOffEnd() is not symmetric.
     * The Application has to decide, depending on the WaitBusSleep-State within
     *  ApplNmBusOff(), if it is neccessary to stop the communication (IL)
     *  or not if already in this state.
     */
#  if defined ( NM_ENABLE_INDEXED_DRVCAN )
    /* code: macros must be encapsulated in this way */
    NmCanResetBusOffEnd(NM_CHANNEL_CANPARA_ONLY, kNmCfg_CanPara);
#  else
    NmCanResetBusOffEnd(kNmCfg_CanPara);
#  endif
  }
  else
  {
#  if defined ( NM_ENABLE_EARLY_BUSOFF_REINIT )
    /* ESCAN00022927 */
    NMVAR(nmDrvCanIsBusOff) = 1; /* set channel-specific flag */
#  endif

    NmResetNmStatusRxFlags();
    nmStateNmMsgRecvRemind = 0;
    nmStateRxTxLockUd      = 0; /* ESCAN00008104 */
    NMVAR(nmTxRequest)     = 0; /* cancel any NM TX request */

    /* clear RX counter, set TX counter to 1 */
    NMVAR(nmRxTxCnt) = TX_CNT_STEP;

    if((NMVAR(nmAction) & ((NmActionType)(~(vuintx)NM_ACTION_REPEAT))) != NM_ACTION_LH_PREPARE_SLEEP)
    {
      /* start LimpHome timer */
      NMVAR(nmTimeCnt)   =CanNmGetBusOffWaitTime();//NMCFG_COUNT_LIMPHOME;
      /* goto LimpHome */
      NMVAR(nmAction)  = NM_ACTION_LH_WAIT_LIMPHOME_TX;
    }
  }


  /* inform application about start of BusOff */
  ApplNmBusOff(NM_CHANNEL_APPLPARA_ONLY);
}

/******************************************************************************
 * Name:            NmConfirmation
 * Called by:       CAN driver (TX interrupt)
 * Parameter:       TX object
 * Return value:    ---
 * Description:     This API informs the NM about the successful transmission of
 *                  the NM message.
 * Precondition:    ---
 *****************************************************************************/
void NM_INTERNAL_CALL_TYPE NmConfirmation(CanTransmitHandle txObject)
{



  #if defined ( NM_ENABLE_INDEXED_NM )
  CanChannelHandle channel;
  #endif

  #if defined ( NM_ENABLE_INDEXED_NM )
  /* determine NM channel from CAN transmit handle */
    #if defined( NM_ENABLE_MULTIPLE_NODES )
  for( channel=0; txObject!=NmTxObj_Field[channel][comMultipleECUCurrent[channel]]; channel++ ) 
  {
    /* ESCAN00014458 */
  }
    #else
      #if ( kNmNumberOfChannels == 1 )
  channel = 0;
      #else
  for( channel=0; txObject!=kNmCfg_TxObj; channel++ ) 
  {
  }
      #endif
    #endif
  #else
    NmAssert( txObject == kNmTxObj, kNmAssertConfirmationHasWrongCanHandle ); /* PRQA S 2214 */ /* MD_NmDirOsek_2214 */

    #if defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  txObject = txObject; /* PRQA S 3199 */ /* dummy assignment for unused parameter */
    #endif
  #endif


  /* release waiting for NmConfirmation (ESCAN00008104) */
  nmStateRxTxLockUd = 0;

  /* message transmitted => reset TX counter */
  NMVAR(nmRxTxCnt) &= ((vuint8)(~(vuintx)TX_CNT_MASK));



  /*---------------------------------------------------------------------------*/
  if( NmTxMsgFlagCmdIf == RING ) /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
  /*---------------------------------------------------------------------------*/
  {

    /* ESCAN00007856 */
    if( (nmStatePrepSleep == 1) && (NmTxMsgFlagSleepAck == 1) ) /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
    {
      NmCanOffline(NM_CHANNEL_CANPARA_ONLY);


      nmStateWaitBusSleep  = 1;
      NMVAR(nmTxRequest) = 0; /* cancel NM TX request, nmStateRxTxLockUd is already 0 */


      NMVAR(nmTimeCnt)  = NMCFG_COUNT_WAITBUSSLEEP;
      NMVAR(nmAction) = NM_ACTION_GO_BUSSLEEP;
    }
    else
    {
      if( (nmStateBusSleepInd == 1) && (NmTxMsgFlagSleepInd == 1) ) /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
      {

        nmStatePrepSleep = 1;

      }

      /*
        Do not wait for any Ring message if we are currently go to sleep.
        This could happen, if we receive a Sleep Acknowledge (NmPrecopy()) while waiting for
        our own Confirmation for the Sleep Indication message.
        Then, this last retrigger and state transition could be discarded.
        Leave the nmStateImAddressed and nmStatePrepSleep information too.
        These flags got it's latest update also in NmPrecopy().
      */
      if( nmStateWaitBusSleep == 0 ) /* ESCAN00007856 */
      {
        nmStateImAddressed = 0;
        nmStateLimpHome = 0; /* ESCAN00017962 */

        /* re-trigger timer to avoid duplicate rings */
        NMVAR(nmTimeCnt) = NMCFG_COUNT_RINGMAX;
        NMVAR(nmAction) = NM_ACTION_WAIT_RINGMSG;
      }
    }
  }
  else
  {
    /*---------------------------------------------------------------------------*/
    if( NmTxMsgFlagCmdIf == LIMPHOME ) /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
    /*---------------------------------------------------------------------------*/
    {

      if( (nmStateActive == 1) && (nmStateNmMsgRecvRemind == 1) )
      {
        NMVAR(nmAction) = NM_ACTION_START;
      }
    }
    else
    {
      /*---------------------------------------------------------------------------*/
      if( NmTxMsgFlagCmdIf == ALIVE ) /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
      /*---------------------------------------------------------------------------*/
      {

        if( (NMVAR(nmAction) == NM_ACTION_LH_WAIT_LIMPHOME_TX) || /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
            (NMVAR(nmAction) == NM_ACTION_LH_PREPARE_SLEEP   ) )
        {
          /* set TX counter, use as Limphome TX mark, reset only on limphome msg */
          NMVAR(nmRxTxCnt) = TX_CNT_STEP; 
        }
      }
    }
  }




} /* PRQA S 4700 */ /* metric data used as information only */

/******************************************************************************
 * Name:            NmPrecopy
 * Called by:       CAN driver (RX interrupt)
 * Parameter:       RX object
 * Return value:    kCanNoCopyData
 * Description:     This API informs the NM about the reception of
 *                  a NM message.
 * Precondition:    ---
 *****************************************************************************/
  #if defined ( C_SINGLE_RECEIVE_BUFFER )
vuint8 NM_INTERNAL_CALL_TYPE NmPrecopy(CanReceiveHandle rcvObject)
{
  #endif
  #if defined ( C_MULTIPLE_RECEIVE_BUFFER )
vuint8 NM_INTERNAL_CALL_TYPE NmPrecopy(CanChipDataPtr rxDataPtr)
{
  #endif
  #if defined ( NM_ENABLE_INDEXED_DRVCAN ) || \
      defined ( C_SINGLE_RECEIVE_CHANNEL )
vuint8 NM_INTERNAL_CALL_TYPE NmPrecopy(CanRxInfoStructPtr rxStruct)
{
  #endif
  vuint8 validNmMsgReceived;




    #if defined ( NM_ENABLE_INDEXED_NM )
      #if defined ( NM_ENABLE_CHANNEL_INDIRECTION )
  CanChannelHandle channel = NmCanToNmIndirection[rxStruct->Channel];
      #else
  CanChannelHandle channel = rxStruct->Channel;
      #endif
    #endif

  #if defined ( NM_ENABLE_CONFIG ) 
  vuint8 configByte;
  #endif


  #if defined ( C_SINGLE_RECEIVE_BUFFER )
    #if defined ( V_ENABLE_USE_DUMMY_STATEMENT )
  rcvObject = rcvObject; /* PRQA S 3199 */ /* dummy assignment for unused parameter */
    #endif
  #endif

  validNmMsgReceived = 0;


  /* get the source address from the received NM message valid until the next message will be received */
  NMVAR(nmRxNmMsgSourceAdr) = NmGetRxMsgSourceAdr();



  /*---------------------------------------------------------------------------*/
  if( (nmRxMsgFlagCmd == RING ) || (nmRxMsgFlagCmd == ALIVE) )
  /*---------------------------------------------------------------------------*/
  {
    /* ESCAN00007856 */

    validNmMsgReceived = 1;

  #if defined ( NM_ENABLE_CONFIG )
    /*--- update NM node table ---*/
    /* ESCAN00028089 */
    #if defined ( NM_ENABLE_INDEXED_NM )
      /* ESCAN00033467 */
      #if defined ( NM_RANGE_MASK )
        #if ( (NM_RANGE_MASK+1) != NM_NUMBER_OF_CONFIG_NODES )
    if( NMVAR(nmRxNmMsgSourceAdr) <= ((vuint8)((NM_NUMBER_OF_CONFIG_NODES) - 1)) )
        #endif
      #else
    if( NMVAR(nmRxNmMsgSourceAdr) <= ((vuint8)((NM_NUMBER_OF_CONFIG_NODES) - 1)) )
      #endif
    #else
      #if ( (NM_RANGE_MASK+1) != NM_NUMBER_OF_CONFIG_NODES )
    if( NMVAR(nmRxNmMsgSourceAdr) <= ((vuint8)((NM_NUMBER_OF_CONFIG_NODES) - 1)) )
      #endif
    #endif
    {
      /* calculate the index for the config table */
      configByte = NmCalculateConfigByte(NMVAR(nmRxNmMsgSourceAdr));

      /* set bit of received NM node within NM node table */
      nmConfig.nmConfigChar[configByte] |= (vuint8)(1<<(NMVAR(nmRxNmMsgSourceAdr) & BYTE_OFFSET_MASK));
    }
  #endif

    /*--- determine logical successor ---*/
    if( NMVAR(nmLogicalSuccessor) > kNmCfg_EcuNr )
    {
      if( (NMVAR(nmRxNmMsgSourceAdr) < NMVAR(nmLogicalSuccessor)) &&
          (NMVAR(nmRxNmMsgSourceAdr) > kNmCfg_EcuNr ) )
      {
        NMVAR(nmLogicalSuccessor) = NMVAR(nmRxNmMsgSourceAdr);
      }
    }
    else
    {
      if( (NMVAR(nmRxNmMsgSourceAdr) < NMVAR(nmLogicalSuccessor)) ||
          (NMVAR(nmRxNmMsgSourceAdr) > kNmCfg_EcuNr ) )
      {
        NMVAR(nmLogicalSuccessor) = NMVAR(nmRxNmMsgSourceAdr);
      }
    }

    /*---------------------------------------------------------------------------*/
    if( nmRxMsgFlagCmd == RING ) /* RX RING */
    /*---------------------------------------------------------------------------*/
    {

      nmStateRingMsgRecv = 1;

      /* check if own node got the token */
      if( (nmRxMsgFlagDestAdr == kNmCfg_EcuNr ) ||            /* own node addressed */
          (nmRxMsgFlagDestAdr == NMVAR(nmRxNmMsgSourceAdr)) ) /* sender addressed */
      {

        nmStateImAddressed = 1;

        /*--- copy used data ---*/

        if( nmRxMsgFlagDestAdr == kNmCfg_EcuNr ) /* own node addressed */
        {
    #if defined ( NM_ENABLE_RINGDATA_ACCESS )
          /* own node has the token => allow ring data access */
          nmStateTxRingDataAllow = 1;
    #endif


          if( nmStateRxTxLockUd == 0 ) /*  */
          {
            /* ESCAN00008104: protect send buffer: user data should not be copied until TX request was sent */

      #if defined ( NM_ENABLE_COPY_RINGDATA )
            /* OSEK mechanism: TX buffer is filled with RX buffer */

            NmTxMsgByteUser0 = nmRxMsgByteUser0; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
            NmTxMsgByteUser1 = nmRxMsgByteUser1; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
            NmTxMsgByteUser2 = nmRxMsgByteUser2; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
            NmTxMsgByteUser3 = nmRxMsgByteUser3; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
            NmTxMsgByteUser4 = nmRxMsgByteUser4; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
            NmTxMsgByteUser5 = nmRxMsgByteUser5; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
      #else

        #if defined ( NM_ENABLE_COPY_RINGDATA_TO_TEMPBUFFER )
            /* modified mechanism: RX buffer is copied to temporary buffer */
            NMVAR(nmUserDataBuffer)[0] = nmRxMsgByteUser0;
            NMVAR(nmUserDataBuffer)[1] = nmRxMsgByteUser1;
            NMVAR(nmUserDataBuffer)[2] = nmRxMsgByteUser2;
            NMVAR(nmUserDataBuffer)[3] = nmRxMsgByteUser3;
            NMVAR(nmUserDataBuffer)[4] = nmRxMsgByteUser4;
            NMVAR(nmUserDataBuffer)[5] = nmRxMsgByteUser5;
        #endif

            /* modified mechanism: TX buffer is filled with default values */

            NmTxMsgByteUser0 = DATA_INIT; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
            NmTxMsgByteUser1 = DATA_INIT; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
            NmTxMsgByteUser2 = DATA_INIT; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
            NmTxMsgByteUser3 = DATA_INIT; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
            NmTxMsgByteUser4 = DATA_INIT; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
            NmTxMsgByteUser5 = DATA_INIT; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
      #endif
          }
        }
      }
      else
      {
        /* own node not addressed */
        nmStateImAddressed = 0;

        /*--- check for skipped ---*/
      #if defined ( NM_INT_ENABLE_OPTIMIZED_SKIPPED_DETECTION )
        /* Code: Special use case: In this configuration, the kNmCfg_EcuNr is a preprocessor define with the value 0.
         *       This leads to some compiler warnings for the standard algorithm. 
         *       The warnings can be removed and the code can be optimized for this use case.*/
        /* ESCAN00020580 */
        if( NMVAR(nmRxNmMsgSourceAdr) >= nmRxMsgFlagDestAdr )
        {
          nmStateImSkippedOver = 1;
        }
      #else
        if( (vsint16)nmRxMsgFlagDestAdr < (vsint16)kNmCfg_EcuNr ) /* ESCAN00007275 */
        {
          if( (         NMVAR(nmRxNmMsgSourceAdr) >= nmRxMsgFlagDestAdr     ) &&
              ((vsint16)NMVAR(nmRxNmMsgSourceAdr) <  (vsint16)kNmCfg_EcuNr))
          {
            nmStateImSkippedOver = 1;
          }
        }
        else
        {
          if( NMVAR(nmRxNmMsgSourceAdr) < nmRxMsgFlagDestAdr )
          {
            if( (vsint16)NMVAR(nmRxNmMsgSourceAdr) < (vsint16)kNmCfg_EcuNr )
            {
              nmStateImSkippedOver = 1;
            }
          }
          else
          {
            nmStateImSkippedOver = 1;
          }
        }
      #endif
      }

    }
    /*---------------------------------------------------------------------------*/
    else /* RX ALIVE */
    /*---------------------------------------------------------------------------*/
    {

      /* ring is unstable */
      nmStateRingStable    = 0;
      nmStateRingPreStable = 0;

    }
  }
  else
  {
    /*---------------------------------------------------------------------------*/
    if( nmRxMsgFlagCmd == LIMPHOME ) /* RX LIMPHOME */
    /*---------------------------------------------------------------------------*/
    {

      validNmMsgReceived = 1;
    }
  }

  /*---------------------------------------------------------------------------*/
  if( validNmMsgReceived == 1 )  /* RX valid NM message */
  /*---------------------------------------------------------------------------*/
  {
    nmStateNmMsgRecv = 1;

    /* NM message received => reset RX counter */
    NMVAR(nmRxTxCnt) &= (vuint8)(~(vuintx)RX_CNT_MASK);

    /* check if network sleep status is not given any more */
    if( (nmRxMsgFlagSleepInd != SLEEP_IND) || (nmStateBusSleep == 1) ) /* ESCAN00007436 */
    {
      nmStatePrepSleep = 0;



    }

    /* RX SleepAck */
    if( nmRxMsgFlagSleepAck == SLEEP_ACK )
    {

      if( (nmStateBusSleep == 0) && (nmStateWaitBusSleep == 0) ) /* ESCAN00007535 */
      {
        /* Start transition to BUSSLEEP */

        if( nmStateBusSleepInd == 1 )
        {
          /* RX SleepAck and sleep is allowed */

          /* stop TX path of CAN controller */
          NmCanOffline(NM_CHANNEL_CANPARA_ONLY);

          nmStatePrepSleep     = 1;
          nmStateWaitBusSleep  = 1;
          nmStateRxTxLockUd    = 0; /* ESCAN00008104 */
          NMVAR(nmTxRequest) = 0; /* cancel NM TX request */

  #if defined ( NM_ENABLE_RINGDATA_ACCESS )
          nmStateTxRingDataAllow = 0; /* disable user(ring)data access */
  #endif



          NMVAR(nmTimeCnt)  = NMCFG_COUNT_WAITBUSSLEEP;
          NMVAR(nmAction) = NM_ACTION_GO_BUSSLEEP;
        }
        else
        {
          /* RX SleepAck but sleep is not allowed */

          /* ESCAN00021051 */
          if( (NMVAR(nmAction) == NM_ACTION_LH_WAIT_LIMPHOME_TX) || 
              (NMVAR(nmAction) == NM_ACTION_LH_PREPARE_SLEEP) )
          {
            if( mmStateBusError == 1 )
            {
              mmStateBusError = 0;

              #if defined( C_MULTIPLE_RECEIVE_CHANNEL )
              /* macros must be encapsulated in this way */
              NmCanResetBusOffEnd(NM_CHANNEL_CANPARA_ONLY, kNmCfg_CanPara);
              #else
              NmCanResetBusOffEnd(kNmCfg_CanPara);
              #endif

              #if defined( NM_ENABLE_EXTENDED_CALLBACK )
              ApplNmBusOffEnd(NM_CHANNEL_APPLPARA_ONLY);
              #endif
            }
          }




        }
      }
      else
      {
        /* NM is already in sleep mode => ignore SleepAck */
      }
    }
  }


  /* no need for further processing of RX message:
   * - there is no buffer for the NM message => save ressources
   * - the message has been completely processed by the NM
   */
  return( kCanNoCopyData );
} /* PRQA S 4700 */ /* metric data used as information only */

/******************************************************************************
 * Name:            NmOsekInit
 * Called by:       application
 * Parameter:       initMode: initialization parameter
 * Return value:    ---
 * Description:     This API initializes the NM
 * Precondition:    transceiver and CAN driver have to be initialized
 *****************************************************************************/
void NM_API_CALL_TYPE NmOsekInit(NM_CHANNEL_NMTYPE_FIRST NmInitType initMode )
{
  #if defined ( NM_ENABLE_INDEXED_NM ) && \
      defined ( NM_ENABLE_APPLCHANNEL_INDIRECTION )
    #if defined ( NM_ENABLE_MULTIPLE_NODES )
  CanChannelHandle sysChannel = channel;
    #endif
  channel = NmSystemToNmIndirection[channel];
  #endif

  CanInterruptDisable();

  nmStateByteGlobal = 0;
  nmStateByteLocal  = 0;

  NMVAR(nmTxRequest) = 0; /* ESCAN00004259 */

  #if defined ( NM_ENABLE_INDEXED_NM ) && defined ( NM_ENABLE_MULTIPLE_NODES )
  /* store configuration data in local variable for direct access and runtime optimization */
    #if defined ( NM_ENABLE_APPLCHANNEL_INDIRECTION )
  kNmCfg_EcuNr = NmEcuNr_Field[channel][comMultipleECUCurrent[sysChannel]];
  kNmCfg_TxObj = NmTxObj_Field[channel][comMultipleECUCurrent[sysChannel]];
    #else
  kNmCfg_EcuNr = NmEcuNr_Field[channel][comMultipleECUCurrent[channel]];
  kNmCfg_TxObj = NmTxObj_Field[channel][comMultipleECUCurrent[channel]];
    #endif
  #endif



  NMVAR(nmTimeCnt) = 0;
  NMVAR(nmRxNmMsgSourceAdr) = kNmCfg_EcuNr;  /* initial value - self addressed */
  NMVAR(nmRxTxCnt) = 0x00;


  #if defined ( NM_ENABLE_COPY_RINGDATA_TO_TEMPBUFFER )
  /*
   * nmUserDataBuffer[0] = 0x00;
   * nmUserDataBuffer[1] = 0x00;
   * nmUserDataBuffer[2] = 0x00;
   * nmUserDataBuffer[3] = 0x00;
   * nmUserDataBuffer[4] = 0x00;
   * nmUserDataBuffer[5] = 0x00;
   * => no initialization needed, because array can only be accessed when ring is stable.
   *    Before the ring gets stable, a message must be received.
   *    This array is updated when a ring message is received.
   */
  #endif










  #if defined ( NM_ENABLE_EARLY_BUSOFF_REINIT )
  /* ESCAN00022927 */
  NMVAR(nmDrvCanIsBusOff) = 0;
  #endif

  {
    /* initialize NM control bytes */
    NmTxMsgByte0 = CTRL_INIT; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
    NmTxMsgByte1 = CTRL_INIT; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */


    /* initialize node configuration array (nmConfig) */
    NmResetNodeConfig(NM_CHANNEL_NMPARA_ONLY);
  }


  /* set default state => can be overwritten in the init-specific handling */
  NMVAR(nmAction) = NM_ACTION_START;

  /*------------------------
   * specific handling
   *------------------------*/
  switch( initMode )
  {
    /*---------------------------------*/
    case NM_NORMAL:
    /*---------------------------------*/
      nmStateActive       = 1;
   /* nmStateBusSleep     = 0; */
   /* nmStateBusSleepInd  = 0; */
   /* nmStatePrepSleep    = 0; */
      break;
    /*---------------------------------*/
    case NM_NMPASSIVE:
    /*---------------------------------*/
   /* nmStateActive       = 0; */
   /* nmStateBusSleep     = 0; */
   /* nmStateBusSleepInd  = 0; */
   /* nmStatePrepSleep    = 0; */
      break;
    /*---------------------------------*/
    case NM_SLEEPIND:
    /*---------------------------------*/
      nmStateActive       = 1;
   /* nmStateBusSleep     = 0; */
      nmStateBusSleepInd  = 1;
   /* nmStatePrepSleep    = 0; */

      break;
    /*---------------------------------*/
    case NM_SLEEPIND_NMPASSIVE:
    /*---------------------------------*/
   /* nmStateActive       = 0; */
   /* nmStateBusSleep     = 0; */
      nmStateBusSleepInd  = 1;
   /* nmStatePrepSleep    = 0; */
      break;
    /*---------------------------------*/
    case NM_CANSLEEP:
    /*---------------------------------*/
      nmStateActive       = 1;
      nmStateBusSleep     = 1;
      nmStateBusSleepInd  = 1;
      nmStatePrepSleep    = 1;

      NMVAR(nmAction) = NM_ACTION_BUS_SLEEP;




      break;
    /*---------------------------------*/
    case NM_DISABLE:
      /* code: the break-statement is intentionally left out here */
    /*---------------------------------*/
    default :
    /*---------------------------------*/
      NMVAR(nmAction) = NO_ACTION;
      break;
  }


  switch( NMVAR(nmAction) )
  {
    case NM_ACTION_START:
      /* notify application about start of network operation */
      ApplNmCanNormal( NM_CHANNEL_APPLPARA_ONLY );
      NmCanOnline( NM_CHANNEL_CANPARA_ONLY );
  #if defined ( NM_ENABLE_EXTENDED_CALLBACK )
      ApplNmBusStart( NM_CHANNEL_APPLPARA_ONLY );
  #endif
      break;
    case NM_ACTION_BUS_SLEEP:
      /* notify application about end of network operation */
      NmCanOffline(NM_CHANNEL_CANPARA_ONLY);
      ApplNmCanSleep( NM_CHANNEL_APPLPARA_ONLY );
      ApplNmCanBusSleep( NM_CHANNEL_APPLPARA_ONLY );
      break;
    default:
      /* do nothing */
      break;
  }

  CanInterruptRestore();
} /* PRQA S 4700 */ /* metric data used as information only */


/******************************************************************************
 * Name:            NmTask
 * Called by:       application
 * Parameter:       (NM channel)
 * Return value:    ---
 * Description:     This API is the cyclic task function of the NM.
 *                  It contains the NM main state machine.
 * Precondition:    NM has to be initializes
 *                  Has to be called cyclically with a constant, 
 *                  predefined task cycle.
 *****************************************************************************/
void NM_API_CALL_TYPE NmTask(NM_CHANNEL_NMTYPE_ONLY)
{


  #if defined ( NM_ENABLE_INDEXED_NM ) && \
      defined ( NM_ENABLE_APPLCHANNEL_INDIRECTION )
  channel = NmSystemToNmIndirection[channel];
  #endif

  CanInterruptDisable();

  #if defined ( NM_ENABLE_EARLY_BUSOFF_REINIT )
  /* ESCAN00022927 */
  if( NMVAR(nmDrvCanIsBusOff) != 0 )
  {
    /* check if DrvCan indicates that it has recovered from BusOff, i.e. it is ready for re-init */
    if( CanGetDriverStatus(NM_CHANNEL_CANPARA_ONLY) != kCanDriverBusoff )
    {
      NMVAR(nmDrvCanIsBusOff) = 0;

      #if defined ( NM_ENABLE_INDEXED_DRVCAN )
      /* code: macros must be encapsulated in this way */
      NmCanResetBusOffEnd(NM_CHANNEL_CANPARA_ONLY, kNmCfg_CanPara);
      #else
      NmCanResetBusOffEnd(kNmCfg_CanPara);
      #endif
    }
  }
  #endif


  /* update task counter */
  if( NMVAR(nmTimeCnt) > 0 )
  {
    NMVAR(nmTimeCnt)--;
  }

  CanInterruptRestore();

  /* code: loop for immediate switch to next state in time-critical cases */
  do
  {

    CanInterruptDisable();

    NMVAR(nmAction) &= (NmActionType)(~(vuintx)NM_ACTION_REPEAT);

    /* check NM TX counter */
    if( (vuint8)((NMVAR(nmRxTxCnt) & TX_CNT_MASK)>>4) > TX_CNT_MAX )
    {
      /* TX counter run off -> start limphome */
      NMVAR(nmRxTxCnt) = TX_CNT_STEP; /* use TX counter as limphome mark */
      NMVAR(nmTimeCnt) = NMCFG_COUNT_LIMPHOME;
      NMVAR(nmAction) = NM_ACTION_LH_WAIT_LIMPHOME_TX;
    }

    /*--- NM state machine ---*/
    switch( NMVAR(nmAction) )
    {
     /*----------------------------------------------------------*/
      case NM_ACTION_START:
     /*----------------------------------------------------------*/

        NmResetNodeConfig( NM_CHANNEL_NMPARA_ONLY );

        /* reset internal status bytes */ 
        nmStateByteLocal        = 0;

        /* reset global status bytes that do not depend on application */

        nmStateRingStable       = 0;
        mmStateBusError         = 0; /* ESCAN00009711 */
     /* nmStateActive           = 0; => do not reset */
        nmStateLimpHome         = 0;
        nmStateBusSleep         = 0;
        nmStateWaitBusSleep     = 0; /* ESCAN00009420 */
        nmStateTxRingDataAllow  = 0;
     /* nmStateBusSleepInd      = 0; => do not reset */

        NMVAR(nmTxRequest) = 0;  /* ESCAN00004259 */
        NMVAR(nmRxNmMsgSourceAdr) = kNmCfg_EcuNr; /* initial value: self-addressed */
        NMVAR(nmRxTxCnt) += RX_CNT_STEP; /* increment RX counter */

        /* unlock TX path */
        NmCanOnline(NM_CHANNEL_CANPARA_ONLY); /* ESCAN00004328 */




        if( nmStateActive == 1 )
        { 

          nmStateRxTxLockUd  = 1; /* ESCAN00008104 - wait for NmConfirmation() */
          NMVAR(nmTxRequest) = 1; /* request TX of ALIVE message */

          NMVAR(nmRxTxCnt) += TX_CNT_STEP; /* increment TX counter */

          /*--- build ALIVE message ---*/

          NMVAR(nmLogicalSuccessor) = kNmCfg_EcuNr;
          NmTxMsgByteDest           = kNmCfg_EcuNr; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
          NmTxMsgFlagCmdSet         = ALIVE; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
          NmTxMsgFlagSleepAck       = 0; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
          NmTxMsgFlagSleepInd       = 0; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */

          /* initialize user data */
          NmTxMsgByteUser0 = DATA_INIT; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
          NmTxMsgByteUser1 = DATA_INIT; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
          NmTxMsgByteUser2 = DATA_INIT; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
          NmTxMsgByteUser3 = DATA_INIT; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
          NmTxMsgByteUser4 = DATA_INIT; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
          NmTxMsgByteUser5 = DATA_INIT; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
        }

        /* check NM RX counter */
        if( (NMVAR(nmRxTxCnt) & RX_CNT_MASK) <= RX_CNT_MAX )
        {
          NMVAR(nmTimeCnt) = (vuint8)(NMCFG_COUNT_RINGTYP + 1);
          NMVAR(nmAction) = NM_ACTION_WAIT_SENDTOKEN;
        }
        else
        {
          /* RX counter run off -> start limphome */
          NMVAR(nmRxTxCnt) = TX_CNT_STEP; /* use TX counter as limphome mark */

          NMVAR(nmTimeCnt) = NMCFG_COUNT_LIMPHOME;
          NMVAR(nmAction)  = NM_ACTION_LH_WAIT_LIMPHOME_TX;
        }

        break;

     /*----------------------------------------------------------*/
      case NM_ACTION_WAIT_SENDTOKEN:
     /*----------------------------------------------------------*/

        if( nmStateActive == 0 )
        {
          /* NmPassive */
          nmStatePrepSleep = nmStateBusSleepInd;



          /* there is no TX is passive mode => change to waiting state */
          NMVAR(nmTimeCnt) = NMCFG_COUNT_RINGMAX;
          NMVAR(nmAction)  = NM_ACTION_WAIT_RINGMSG;
        }
        else
        {
          /* NmActive */

          /* check for skipped condition */
          if( nmStateImSkippedOver == 1 )
          {
            /*
             * code: don't change the counter. 
             *       The own NM message might be transmitted now or by the next task call,
             */


            /* transmit SKIPPED ALIVE message */
            NmTransmitSkippedAlive(NM_CHANNEL_NMPARA_ONLY);
          }

          /* check for NM message reception */
          if( nmStateRingMsgRecv == 1 )
          {
            if( nmStateImAddressed == 1 )
            {
              /* refresh timer */
              NMVAR(nmTimeCnt) = NMCFG_COUNT_RINGTYP;
            }
            else
            {
              /* another node received the token => cancel own transmit token */
              NMVAR(nmTimeCnt) = NMCFG_COUNT_RINGMAX;
              NMVAR(nmAction) = NM_ACTION_WAIT_RINGMSG;
            }
          }
          else
          {
            if( NMVAR(nmTimeCnt) == 0 )
            {
              /*--- transmit RING message ---*/


              #if defined ( NM_ENABLE_RINGDATA_ACCESS )
              /* token is passed on => disable access on userdata */
              nmStateTxRingDataAllow = 0;
              #endif

              nmStateRxTxLockUd  = 1; /* ESCAN00008104 - wait for NmConfirmation() */
              NMVAR(nmTxRequest) = 1; /* request TX of RING message */

              NMVAR(nmRxTxCnt) += TX_CNT_STEP; /* increment NM TX counter */

              /*--- determine status of flags SleepInd and SleepAck ---*/
              if( NMVAR(nmLogicalSuccessor) != kNmCfg_EcuNr )
              {
                /* check if SleepAck should be transmitted */
                if( (nmStatePrepSleep == 1) && (nmStateBusSleepInd == 1) )
                {
                  /* set SleepAck */
                  NmTxMsgFlagSleepAck = 1; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
                }
                else
                {
                  NmTxMsgFlagSleepAck = 0; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */

                }

                /* bit SleepInd is directly derived from the application request */
                NmTxMsgFlagSleepInd = nmStateBusSleepInd; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
              }
              else
              {
                /* there is no SleepInd and no SleepAck if the node addresses itself */
                NmTxMsgFlagSleepAck = 0; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
                NmTxMsgFlagSleepInd = 0; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
              }

              /*--- check stability of ring ---*/
              if( nmStateRingPreStable == 1 )
              {
                nmStateRingStable = 1;

              }
              else
              {
                nmStateRingPreStable = 1;
              }


              /* build RING message */
              NmTxMsgFlagCmdSet = RING; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
              NmTxMsgByteDest   = NMVAR(nmLogicalSuccessor); /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */


              /* state transition */
              NMVAR(nmTimeCnt) = NMCFG_COUNT_RINGMAX;
              NMVAR(nmAction)  = NM_ACTION_WAIT_RINGMSG;
            }
          }
        }
        break;
     /*----------------------------------------------------------*/
      case NM_ACTION_WAIT_RINGMSG:
     /*----------------------------------------------------------*/

        /* check for received NM message */
        if( nmStateRingMsgRecv == 1 )
        {

          if( (nmStateActive == 1) && (nmStateImAddressed == 1) )
          {
            /* token received */

            #if defined ( NM_ENABLE_RINGDATA_ACCESS )
            if( nmStateRingStable == 1 )
            {
              /* inform application about possibility to access ringdata */
              ApplNmIndRingData(NM_CHANNEL_APPLPARA_ONLY);
            }
            #endif

            /* state transition */
            NMVAR(nmTimeCnt)  = NMCFG_COUNT_RINGTYP;
            NMVAR(nmAction) = NM_ACTION_WAIT_SENDTOKEN;
          }
          else
          {
            /* refresh timer */
            NMVAR(nmTimeCnt) = NMCFG_COUNT_RINGMAX;
          }
        }

        if( nmStateActive == 1 )
        {
          /* check for skipped condition */
          if( nmStateImSkippedOver == 1 )
          {
            /*
             * code: don't change the counter. 
             *       The own NM message might be transmitted now or by the next task call,
             */


            /* transmit SKIPPED ALIVE message */
            NmTransmitSkippedAlive(NM_CHANNEL_NMPARA_ONLY);
          }
        }
        else
        {
          /* NmPassive */

          /*--- check stability of ring ---*/
          if( nmStateRingPreStable == 1 )
          {
            nmStateRingStable = 1;
          }
          else
          {
            nmStateRingPreStable = 1;
          }

          nmStatePrepSleep = nmStateBusSleepInd;


        }

        if( NMVAR(nmTimeCnt) == 0 )
        { 
          /* RX timeout */

          /* state transition */
          NMVAR(nmAction) = NM_ACTION_START;
        }
        break;
     /*----------------------------------------------------------*/
      case NM_ACTION_LH_WAIT_LIMPHOME_TX:
      case NM_ACTION_LH_PREPARE_SLEEP:
     /*----------------------------------------------------------*/
        NmResetNodeConfig(NM_CHANNEL_NMPARA_ONLY);
        nmStateLimpHome = 1;

        NMVAR(nmRxTxCnt) &= (vuint8)(~(vuintx)RX_CNT_MASK);  /* reset NM RX counter */


        /* remember if a NM message has been received while in limphome */
        if( nmStateNmMsgRecv == 1 )
        {
          nmStateNmMsgRecvRemind = 1;
        }

        if( (nmStateNmMsgRecvRemind == 1) && 
            ((nmStateActive == 0) || (NMVAR(nmRxTxCnt) == 0)) )
        {
          NMVAR(nmRxTxCnt) = 0; /* reset NM RX and TX counter */

          /* state transition (time-critical) */
          NMVAR(nmAction) = (NmActionType)(NM_ACTION_START | NM_ACTION_REPEAT);
        }
        else
        {
         /*----------------------------------------------------------
           NM_ACTION_LH_WAIT_LIMPHOME_TX
          *----------------------------------------------------------*/
          if( NMVAR(nmAction) == NM_ACTION_LH_WAIT_LIMPHOME_TX )
          {

            if( NMVAR(nmTimeCnt) == 0 )
            {
              /* check if there is was a BusOff */
              if( mmStateBusError == 1 )
              {
                mmStateBusError = 0;

                /* recover BusOff */ /* ESCAN00022927 */
                #if defined ( NM_ENABLE_EARLY_BUSOFF_REINIT )
                if ( NMVAR(nmDrvCanIsBusOff) != 0 )
                {
                  NMVAR(nmDrvCanIsBusOff) = 0;
                #else
                {
                #endif
                  #if defined ( NM_ENABLE_INDEXED_DRVCAN )
                  /* code: macros must be encapsulated in this way */
                  NmCanResetBusOffEnd( NM_CHANNEL_CANPARA_ONLY, kNmCfg_CanPara );
                  #else
                  NmCanResetBusOffEnd( kNmCfg_CanPara );
                  #endif
                }

                #if defined ( NM_ENABLE_EXTENDED_CALLBACK )
                ApplNmBusOffEnd(NM_CHANNEL_APPLPARA_ONLY);
                #endif
              }

              NmCanOnline(NM_CHANNEL_CANPARA_ONLY);

              if( nmStateActive == 1 )
              {
                /* transmit LIMPHOME message */


                nmStatePrepSleep = nmStateBusSleepInd;
                nmStateRxTxLockUd = 1; /* ESCAN00008104 - wait for NmConfirmation() */
                NMVAR(nmTxRequest) = 1; /* request transmission of LimpHome message */

                NMVAR(nmRxTxCnt) = TX_CNT_STEP;  /* set TX counter as limphome mark */



                /* build LIMPHOME message */
                NmTxMsgByteDest      = NMVAR(nmLogicalSuccessor); /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
                NmTxMsgFlagCmdSet    = LIMPHOME; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
                NmTxMsgFlagSleepAck  = 0; /* ESCAN00007382 */ /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
                NmTxMsgFlagSleepInd = nmStateBusSleepInd; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */

              }

              NMVAR(nmTimeCnt) = NMCFG_COUNT_LIMPHOME;
            }

            if( nmStateActive == 0 )
            {
              nmStatePrepSleep = nmStateBusSleepInd;


            }

            if( nmStatePrepSleep == 1 )
            {

              /* state transition (time-critical) */
              NMVAR(nmTimeCnt) = NMCFG_COUNT_RINGMAX;
              NMVAR(nmAction) = (NmActionType)(NM_ACTION_LH_PREPARE_SLEEP | NM_ACTION_REPEAT);
            }
          }
          /*----------------------------------------------------------
            NM_ACTION_LH_PREPARE_SLEEP
           *----------------------------------------------------------*/
          else
          {
            if( nmStatePrepSleep == 1 )
            {

              if( nmStateRingMsgRecv == 1 )
              {
                NMVAR(nmTimeCnt) = NMCFG_COUNT_RINGMAX; /* refresh timer */
              }
              else
              {
                if( NMVAR(nmTimeCnt) == 0 )
                {
                  /* start sleep sequence */

                  NmCanOffline(NM_CHANNEL_CANPARA_ONLY);

                  nmStateWaitBusSleep = 1;
                  nmStateRxTxLockUd   = 0; /* ESCAN00008104 */
                  NMVAR(nmTxRequest)  = 0; /* cancel NM TX request */


                  if( mmStateBusError == 1 ) /* PRQA S 0715 */ /* changes in algo are critical */
                  { /* PRQA S 0715 */ /* Nesting depth due to optimized code handling */
                    mmStateBusError = 0;

                    /* recover BusOff */

                    #if defined ( NM_ENABLE_INDEXED_DRVCAN )
                    /* code: macros must be encapsulated in this way */
                    NmCanResetBusOffEnd(NM_CHANNEL_CANPARA_ONLY, kNmCfg_CanPara);
                    #else
                    NmCanResetBusOffEnd(kNmCfg_CanPara);
                    #endif

                    #if defined ( NM_ENABLE_EXTENDED_CALLBACK )
                    ApplNmBusOffEnd(NM_CHANNEL_APPLPARA_ONLY);
                    #endif
                  }

                  /* state transition */
                  NMVAR(nmTimeCnt) = NMCFG_COUNT_WAITBUSSLEEP;
                  NMVAR(nmAction) = NM_ACTION_GO_BUSSLEEP;
                }
              }
            }
            else
            {
              /* application wakeup */
              nmStateNmMsgRecvRemind = 0;

              /* ESCAN00022144 - unlock CAN-Transmit path immediately */
              NmCanOnline(NM_CHANNEL_CANPARA_ONLY);

              NMVAR(nmTimeCnt) = NMCFG_COUNT_LIMPHOME;  /* stop PREPARE_SLEEP */
              NMVAR(nmAction) = NM_ACTION_LH_WAIT_LIMPHOME_TX;
            }
          }
        }
        break;
      /*----------------------------------------------------------*/
      case NM_ACTION_GO_BUSSLEEP:
      /*----------------------------------------------------------*/
        NmAssert( nmStateWaitBusSleep != 0, kNmAssertWrongFlagWaitBusSleep ); /* PRQA S 2214 */ /* MD_NmDirOsek_2214 */
        NmAssert( nmStateBusSleep == 0, kNmAssertWrongFlagBusSleep ); /* PRQA S 2214 */ /* MD_NmDirOsek_2214 */

        NmResetNodeConfig( NM_CHANNEL_NMPARA_ONLY );
        nmStateNmMsgRecvRemind = 0;


        NMVAR(nmRxTxCnt) = 0;

        #if defined ( NM_ENABLE_EXTENDED_CALLBACK )
        if( NMVAR(nmTimeCnt) == ((NMCFG_COUNT_WAITBUSSLEEP - 1)) )
        {
          /* inform application */
          ApplNmWaitBusSleep(NM_CHANNEL_APPLPARA_ONLY);
        }
        #endif

        /* check sleep condition */
        if( nmStatePrepSleep == 0 )
        {
          /* 
           * sleep condition not true anymore
           * => - GotoMode(Awake) called or
           *    - RX of NM message with SleepInd=0 *
           * => abort sleep sequence 
           */

          nmStateWaitBusSleep = 0;  /* leave the context, because of possible WakeUp detection in GotoMode() */

          /* ESCAN00008463 - unlock CAN-Transmit path immediately */
          NmCanOnline(NM_CHANNEL_CANPARA_ONLY);


          /* check if LimpHome was active before the sleep sequence */
          if( nmStateLimpHome == 1 )
          {
            NMVAR(nmRxTxCnt) = TX_CNT_STEP;  /* use TX counter as limphome mark */

            /* update time counter */
            NMVAR(nmTimeCnt)   = NMCFG_COUNT_LIMPHOME;

            /* state transition */
            NMVAR(nmAction)  = NM_ACTION_LH_WAIT_LIMPHOME_TX;

          }
          else
          {
            /* state transition (time-critical) */
            NMVAR(nmAction) = (NmActionType)(NM_ACTION_START | NM_ACTION_REPEAT);
          }

          #if defined ( NM_ENABLE_EXTENDED_CALLBACK )
          /* inform application that NmWaitBusSleep is left */
          ApplNmWaitBusSleepCancel(NM_CHANNEL_APPLPARA_ONLY);
          #endif

          /* note: If NmWaitBusSleep is left towards NmLimpHome, the CAN TX path is offline until the next task cycle */
        }
        else
        {
          /* sleep condition is still true */

          if( NMVAR(nmTimeCnt) == 1 )
          {
            NmCanOffline(NM_CHANNEL_CANPARA_ONLY);

            nmStateRxTxLockUd  = 0; /* ESCAN00008104 */
            NMVAR(nmTxRequest) = 0; /* cancel any NM TX request */

            /* initialize CAN-Chip to clear TX requests */
            #if defined ( NM_ENABLE_INDEXED_DRVCAN )
            /* code: macros must be encapsulated in this way */
            NmCanResetBusSleep((vuint8)NM_CHANNEL_CANPARA_ONLY, kNmCfg_CanPara);
            #else
            NmCanResetBusSleep(kNmCfg_CanPara);
            #endif
          }
          else
          {
            if( NMVAR(nmTimeCnt) == 0 )
            {
              nmStateWaitBusSleep = 0;
              nmStateBusSleep     = 1;

              /* inform application */
              ApplNmCanSleep(NM_CHANNEL_APPLPARA_ONLY);
              ApplNmCanBusSleep(NM_CHANNEL_APPLPARA_ONLY);

              /* state transition */
              NMVAR(nmAction) = NM_ACTION_BUS_SLEEP;
            }
          }
        }
        break;
      /*----------------------------------------------------------*/
      case NM_ACTION_BUS_SLEEP:
      /*----------------------------------------------------------*/
        NmAssert( nmStateWaitBusSleep == 0, kNmAssertWrongFlagWaitBusSleep ); /* PRQA S 2214 */ /* MD_NmDirOsek_2214 */
        NmAssert( nmStateBusSleep != 0, kNmAssertWrongFlagBusSleep ); /* PRQA S 2214 */ /* MD_NmDirOsek_2214 */

        nmStateLimpHome = 0;

        /* check sleep condition */
        if( nmStatePrepSleep == 0 ) /* ESCAN00007436 */
        {
          /* 
           * sleep condition not true anymore
           * => - GotoMode(Awake) called or
           *    - RX of any NM message *
           * => abort sleep
           */
          nmStateBusSleep = 0;


          /* inform application to enable transceiver and to wake CAN controller */
          ApplNmCanNormal(NM_CHANNEL_APPLPARA_ONLY);
          /* unlock CAN TX path */
          NmCanOnline(NM_CHANNEL_CANPARA_ONLY);
          #if defined ( NM_ENABLE_EXTENDED_CALLBACK )
          ApplNmBusStart(NM_CHANNEL_APPLPARA_ONLY);
          #endif
          /* state transition (time-critical) */
          NMVAR(nmAction) = (NmActionType)(NM_ACTION_START | NM_ACTION_REPEAT);
        }
        break;

      /*----------------------------------------------------------*/
      case NO_ACTION:
      case NM_ACTION_REPEAT:
      default :
      /*----------------------------------------------------------*/
        NmResetNodeConfig( NM_CHANNEL_NMPARA_ONLY );

        /* reset all status flags */
        nmStateByteGlobal   = 0;
        nmStateByteLocal    = 0;

        NMVAR(nmTxRequest)  = 0; /* ESCAN00004259 */

        NMVAR(nmTimeCnt)    = 0;
        NMVAR(nmRxTxCnt)    = 0;
        NMVAR(nmRxNmMsgSourceAdr) = kNmCfg_EcuNr;  /* initial value - self addressed */


        break;
    } /* switch(NMVAR(nmAction)) */



    NmResetNmStatusRxFlags();

    CanInterruptRestore();

  /*----------------------------------------------------------*/
  } while( (NMVAR(nmAction) & NM_ACTION_REPEAT) != 0 ); 
  /*----------------------------------------------------------*/

  /*-------------------------------------
   * transmission handling 
   *-------------------------------------*/
  if( (NMVAR(nmTxRequest) == 1) && (nmStateActive == 1) )
  {
    /* ESCAN00036713 */
  #if defined ( NM_ENABLE_INDEXED_DRVCAN )
    NmAssert( (CanGetStatus(NM_CHANNEL_CANPARA_ONLY) & kCanTxOn) == kCanTxOn, kNmAssertCanIsOnline ); /* PRQA S 2214 */ /* MD_NmDirOsek_2214 */
  #else
    NmAssert( (CanGetStatus() & kCanTxOn) == kCanTxOn, kNmAssertCanIsOnline ); /* PRQA S 2214 */ /* MD_NmDirOsek_2214 */
  #endif




    if( CanTransmit(kNmCfg_TxObj) == kCanTxOk )
    {
      NMVAR(nmTxRequest) = 0;

    }
    else
    {
    }
  }
} /* PRQA S 4700 */ /* metric data used as information only */

/******************************************************************************
 * Name:            GotoMode
 * Called by:       application
 * Parameter:       (NM channel)
 *                  mode  -Awake    application needs communication
 *                        -BusSleep application is ready for sleep
 * Return value:    ---
 * Description:     This API informs the NM about the communication needs of 
 *                  the application.
 * Precondition:    ---
 *****************************************************************************/
void NM_API_CALL_TYPE GotoMode( NM_CHANNEL_NMTYPE_FIRST NMModeName mode )
{
  #if defined ( NM_ENABLE_INDEXED_NM ) && \
      defined ( NM_ENABLE_APPLCHANNEL_INDIRECTION )
  channel = NmSystemToNmIndirection[channel];
  NmAssert( channel != 0xFF, kNmAssertInvalidChannel ); /* PRQA S 2214 */ /* MD_NmDirOsek_2214 */
  #endif

  CanInterruptDisable();

  if( mode == BusSleep )
  {
    nmStateBusSleepInd = 1;
  }
  else /* code: enum-value. => mode==Awake */
  {



    nmStateBusSleepInd = 0;
    nmStatePrepSleep   = 0;
  }

  CanInterruptRestore();
}


/******************************************************************************
 * Name:            GetStatus
 * Called by:       application
 * Parameter:       (NM channel)
 *                  *dest   pointer to application-specific variable
 * Return value:    ---
 * Description:     This API copies the current NM state into an 
 *                  application-specific variable.
 * Precondition:    ---
 *****************************************************************************/
void NM_API_CALL_TYPE GetStatus( NM_CHANNEL_NMTYPE_FIRST NmStatusType *dest )
{
  #if defined ( NM_ENABLE_INDEXED_NM ) && \
      defined ( NM_ENABLE_APPLCHANNEL_INDIRECTION )
  channel = NmSystemToNmIndirection[channel];
  NmAssert( channel != 0xFF, kNmAssertInvalidChannel ); /* PRQA S 2214 */ /* MD_NmDirOsek_2214 */
  #endif

  *dest = (NmStatusType)(nmStateByteGlobal);
}

/******************************************************************************
 * Name:            NmGetStatus
 * Called by:       application
 * Parameter:       (NM channel)
 * Return value:    state of NM
 * Description:     This API returns the current NM state.
 * Precondition:    ---
 *****************************************************************************/
NmStatusType NM_API_CALL_TYPE NmGetStatus( NM_CHANNEL_NMTYPE_ONLY )
{
  #if defined ( NM_ENABLE_INDEXED_NM ) && \
      defined ( NM_ENABLE_APPLCHANNEL_INDIRECTION )
  channel = NmSystemToNmIndirection[channel];
  NmAssert( channel != 0xFF, kNmAssertInvalidChannel ); /* PRQA S 2214 */ /* MD_NmDirOsek_2214 */
  #endif

  return( (NmStatusType)(nmStateByteGlobal) );
}


/******************************************************************************
 * Name:            StartNM
 * Called by:       application
 * Parameter:       (NM channel)
 * Return value:    ---
 * Description:     This API starts the NM.
 * Precondition:    ---
 *****************************************************************************/
void NM_API_CALL_TYPE StartNM ( NM_CHANNEL_NMTYPE_ONLY )
{
  #if defined ( NM_ENABLE_INDEXED_NM ) && \
      defined ( NM_ENABLE_APPLCHANNEL_INDIRECTION )
  /* Code: No channel indirection needed, as only external API is called.
           Channel indirection is handled within that funtion. */
  #endif

  NmOsekInit( NM_CHANNEL_NMPARA_FIRST NM_NORMAL );
}


/******************************************************************************
 * Name:            StopNM
 * Called by:       application
 * Parameter:       (NM channel)
 * Return value:    ---
 * Description:     This API stops the NM.
 * Precondition:    ---
 *****************************************************************************/
void NM_API_CALL_TYPE StopNM( NM_CHANNEL_NMTYPE_ONLY )
{
  #if defined ( NM_ENABLE_INDEXED_NM ) && \
      defined ( NM_ENABLE_APPLCHANNEL_INDIRECTION )
  /* Code: No channel indirection needed, as only external API is called.
           Channel indirection is handled within that funtion. */
  #endif

  NmOsekInit( NM_CHANNEL_NMPARA_FIRST NM_DISABLE );
}


/******************************************************************************
 * Name:            TalkNM
 * Called by:       application
 * Parameter:       (NM channel)
 * Return value:    ---
 * Description:     This API sets the NM into active mode, i.e. the NM
 *                  can transmit NM messages and take part in the logical ring.
 * Precondition:    ---
 *****************************************************************************/
void NM_API_CALL_TYPE TalkNM( NM_CHANNEL_NMTYPE_ONLY )
{
  #if defined ( NM_ENABLE_INDEXED_NM ) && \
      defined ( NM_ENABLE_APPLCHANNEL_INDIRECTION )
  channel = NmSystemToNmIndirection[channel];
  NmAssert( channel != 0xFF, kNmAssertInvalidChannel ); /* PRQA S 2214 */ /* MD_NmDirOsek_2214 */
  #endif

  CanInterruptDisable();
  nmStateActive = 1;
  CanInterruptRestore();
}


/******************************************************************************
 * Name:            SilentNM
 * Called by:       application
 * Parameter:       (NM channel)
 * Return value:    ---
 * Description:     This API sets the NM into passive mode, i.e. the NM
 *                  cannot transmit NM messages. It only monitors the logical ring.
 * Precondition:    ---
 *****************************************************************************/
void NM_API_CALL_TYPE SilentNM( NM_CHANNEL_NMTYPE_ONLY )
{
  #if defined ( NM_ENABLE_INDEXED_NM ) && \
      defined ( NM_ENABLE_APPLCHANNEL_INDIRECTION )
  channel = NmSystemToNmIndirection[channel];
  NmAssert( channel != 0xFF, kNmAssertInvalidChannel );
  #endif

  CanInterruptDisable();
  nmStateActive = 0;
  CanInterruptRestore();
}


#if defined ( NM_ENABLE_RINGDATA_ACCESS )
/******************************************************************************
 * Name:            ReadRingData
 * Called by:       application
 * Parameter:       (NM channel)
 *                  *ringData   pointer to a user-specific array where the
 *                              user data have to be copied in
 * Return value:    - E_NotOK   access on ring data not possible because
 *                              - received ring data has not been stored
 *                              - ring is not stable
 *                  - E_OK      array 'ringData' has been updated with data 
 *                              from the NM message
 * Description:     This API copies the last received user data into an
 *                  application-specific buffer <ringData>.
 * Precondition:    ---
 *****************************************************************************/
StatusType NM_API_CALL_TYPE ReadRingData( NM_CHANNEL_NMTYPE_FIRST vuint8* ringData )
{
  StatusType rval;

  #if defined ( NM_ENABLE_INDEXED_NM ) && \
      defined ( NM_ENABLE_APPLCHANNEL_INDIRECTION )
  channel = NmSystemToNmIndirection[channel];
  NmAssert( channel != 0xFF, kNmAssertInvalidChannel ); /* PRQA S 2214 */ /* MD_NmDirOsek_2214 */
  #endif

  if( nmStateRingStable == 0 )
  {
    /* ring is not stable => ringData is not valid */
    rval = E_NotOK;
  }
  else
  {
  #if defined ( NM_ENABLE_COPY_RINGDATA )
    /* 
     * normal OSEK mechanism
     * received ring data was copied to NM TX buffer
     * => get it from there
     */
    CanInterruptDisable();
    *(ringData    ) = NmTxMsgByteUser0; /* PRQA S 0310,0489 */ /* MD_NmDirOsek_0310, MD_NmDirOsek_0489 */
    *(ringData + 1) = NmTxMsgByteUser1; /* PRQA S 0310,0489 */ /* MD_NmDirOsek_0310, MD_NmDirOsek_0489 */
    *(ringData + 2) = NmTxMsgByteUser2; /* PRQA S 0310,0488 */ /* MD_NmDirOsek_0310, MD_NmDirOsek_0488 */
    *(ringData + 3) = NmTxMsgByteUser3; /* PRQA S 0310,0488 */ /* MD_NmDirOsek_0310, MD_NmDirOsek_0488 */
    *(ringData + 4) = NmTxMsgByteUser4; /* PRQA S 0310,0488 */ /* MD_NmDirOsek_0310, MD_NmDirOsek_0488 */
    *(ringData + 5) = NmTxMsgByteUser5; /* PRQA S 0310,0488 */ /* MD_NmDirOsek_0310, MD_NmDirOsek_0488 */
    CanInterruptRestore();

    rval = E_OK;
  #elif defined ( NM_ENABLE_COPY_RINGDATA_TO_TEMPBUFFER )
    /* 
     * modified mechanism:
     * received ring data was copied to specific NM buffer
     * => get it from there
     */
    CanInterruptDisable();
    *(ringData    ) = NMVAR(nmUserDataBuffer)[0]; /* PRQA S 0489 */ /* MD_NmDirOsek_0489 */
    *(ringData + 1) = NMVAR(nmUserDataBuffer)[1]; /* PRQA S 0489 */ /* MD_NmDirOsek_0489 */
    *(ringData + 2) = NMVAR(nmUserDataBuffer)[2]; /* PRQA S 0488 */ /* MD_NmDirOsek_0488 */
    *(ringData + 3) = NMVAR(nmUserDataBuffer)[3]; /* PRQA S 0488 */ /* MD_NmDirOsek_0488 */
    *(ringData + 4) = NMVAR(nmUserDataBuffer)[4]; /* PRQA S 0488 */ /* MD_NmDirOsek_0488 */
    *(ringData + 5) = NMVAR(nmUserDataBuffer)[5]; /* PRQA S 0488 */ /* MD_NmDirOsek_0488 */
    CanInterruptRestore();

    rval = E_OK;
  #else
    /* 
     * received ring data was not copied at all
     * => impossible to access it
     */
    #if defined ( V_ENABLE_USE_DUMMY_STATEMENT )
    *ringData = *ringData; /* PRQA S 3199 */ /* dummy assignment for unused parameter */
    #endif

    rval = E_NotOK;
  #endif
  }
  return( rval );
}
#endif


#if defined ( NM_ENABLE_RINGDATA_ACCESS )
/******************************************************************************
 * Name:            TransmitRingData
 * Called by:       application
 * Parameter:       (NM channel)
 *                  *ringData   pointer to a user-specific array where the
 *                              user data have to be copied from
 * Return value:    - E_NotOK   access on ring data not possible
 *                  - E_OK      ring data have been updated
 * Description:     This API copies the user data from an application-specific buffer
 *                  into the user data of the NM message buffer.
 * Precondition:    ---
 *****************************************************************************/
StatusType NM_API_CALL_TYPE TransmitRingData( NM_CHANNEL_NMTYPE_FIRST vuint8* ringData ) /* PRQA S 3673 */ /* API is defined by specification and can't be modified */
{
  StatusType rval;

  #if defined ( NM_ENABLE_INDEXED_NM ) && \
      defined ( NM_ENABLE_APPLCHANNEL_INDIRECTION )
  channel = NmSystemToNmIndirection[channel];
  NmAssert( channel != 0xFF, kNmAssertInvalidChannel ); /* PRQA S 2214 */ /* MD_NmDirOsek_2214 */
  #endif

  /* check if access on ring data is not allowed */
  if( nmStateTxRingDataAllow == 0 )
  {
    rval = E_NotOK;
  }
  else
  {
    CanInterruptDisable();

    NmTxMsgByteUser0 = *(ringData    ); /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
    NmTxMsgByteUser1 = *(ringData + 1); /* PRQA S 0310,0489 */ /* MD_NmDirOsek_0310, MD_NmDirOsek_0489 */
    NmTxMsgByteUser2 = *(ringData + 2); /* PRQA S 0310,0488 */ /* MD_NmDirOsek_0310, MD_NmDirOsek_0488 */
    NmTxMsgByteUser3 = *(ringData + 3); /* PRQA S 0310,0488 */ /* MD_NmDirOsek_0310, MD_NmDirOsek_0488 */
    NmTxMsgByteUser4 = *(ringData + 4); /* PRQA S 0310,0488 */ /* MD_NmDirOsek_0310, MD_NmDirOsek_0488 */
    NmTxMsgByteUser5 = *(ringData + 5); /* PRQA S 0310,0488 */ /* MD_NmDirOsek_0310, MD_NmDirOsek_0488 */

    CanInterruptRestore();

    rval = E_OK;
  }
  return( rval );
}
#endif


#if defined ( NM_ENABLE_CONFIG )
/******************************************************************************
 * Name:            GetConfig
 * Called by:       application
 * Parameter:       (NM channel)
 *                  *dataPtr    pointer to the application-specific array
 *                              where the configuration has to be copied to
 * Return value:    ---
 * Description:     This API copies the current node configuration into an
 *                  application-specific buffer.
 * Precondition:    ---
 *****************************************************************************/
void NM_API_CALL_TYPE GetConfig( NM_CHANNEL_NMTYPE_FIRST NmConfigType *dataPtr )
{
  vuint8 configByte;

  #if defined ( NM_ENABLE_INDEXED_NM ) && \
      defined ( NM_ENABLE_APPLCHANNEL_INDIRECTION )
  channel = NmSystemToNmIndirection[channel];
  NmAssert( channel != 0xFF, kNmAssertInvalidChannel ); /* PRQA S 2214 */ /* MD_NmDirOsek_2214 */
  #endif

  CanInterruptDisable();

  #if defined ( NM_ENABLE_INDEXED_NM )
  for( configByte =   (vuint8)channel      * (vuint8)((NM_NUMBER_OF_CONFIG_NODES)/8);
       configByte < (((vuint8)channel + 1) * (vuint8)((NM_NUMBER_OF_CONFIG_NODES)/8));
       configByte++)
  {
  #else
  for( configByte = 0; 
       configByte < (vuint8)((NM_NUMBER_OF_CONFIG_NODES)/8); 
       configByte++)
  {
  #endif
    /* copy data */
    dataPtr->nmConfigChar[configByte] = nmConfig.nmConfigChar[configByte];
  }

  CanInterruptRestore();
}
#endif


#if defined ( NM_ENABLE_CONFIG )
/******************************************************************************
 * Name:            CmpConfig
 * Called by:       application
 * Parameter:       (NM channel)
 *                  idx:  index of ConfigMaskTable and TargetConfigTable
 * Return value:    - 1: configuration does match reference
 *                  - 0: configuration does not match reference
 * Description:     This API compares the current NM node configuration with a 
 *                  reference configuration stored in memory.
 *                  The reference is identified by <idx>.
 * Precondition:    ---
 *****************************************************************************/
NmReturnType CmpConfig( NM_CHANNEL_NMTYPE_FIRST vuint8 idx )
{
  vuint8 configByte;
  NmReturnType rval = 1;

  #if defined ( NM_ENABLE_INDEXED_NM ) && \
      defined ( NM_ENABLE_APPLCHANNEL_INDIRECTION )
  channel = NmSystemToNmIndirection[channel];
  NmAssert( channel != 0xFF, kNmAssertInvalidChannel ); /* PRQA S 2214 */ /* MD_NmDirOsek_2214 */
  #endif

  CanInterruptDisable();

  #if defined ( NM_ENABLE_INDEXED_NM )
  for( configByte =   (vuint8)channel      * (vuint8)((NM_NUMBER_OF_CONFIG_NODES)/8);
       configByte < (((vuint8)channel + 1) * (vuint8)((NM_NUMBER_OF_CONFIG_NODES)/8));
       configByte++ )
  #else
  for( configByte = 0;
       configByte < (vuint8)((NM_NUMBER_OF_CONFIG_NODES)/8); 
       configByte++ )
  #endif
  {
    /* compare data */
    if( ((TargetConfigTable[idx].nmConfigChar[configByte] ^ nmConfig.nmConfigChar[configByte]) &
        ConfigMaskTable[idx].nmConfigChar[configByte]) != 0x00 )
    {
      rval = 0;
      break;
    }
  }

  CanInterruptRestore();
  return( rval );
}
#endif














































/**********************************************************************************************************************
  Local function definitions
**********************************************************************************************************************/
/******************************************************************************
 * Name:            NmTransmitSkippedAlive
 * Called by:       Nm_DirOsek
 * Parameter:       (NM channel)
 * Return value:    ---
 * Description:     This API prepares a SkippedAlive message for asynchronous
 *                  transmission.
 * Precondition:    ---
 *******************************************************************************/
static void NmTransmitSkippedAlive( NM_CHANNEL_NMTYPE_ONLY )
{
  nmStateRxTxLockUd = 1; /* ESCAN00008104 */

  NMVAR(nmTxRequest) = 1;           /* request transmission */
  NMVAR(nmRxTxCnt)  += TX_CNT_STEP; /* increment TX counter */

  NmTxMsgFlagCmdSet    = ALIVE; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
  NmTxMsgByteDest      = NMVAR(nmLogicalSuccessor); /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
  NmTxMsgFlagSleepInd  = nmStateBusSleepInd; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */
  NmTxMsgFlagSleepAck  = 0; /* PRQA S 0310 */ /* MD_NmDirOsek_0310 */


  nmStateRingStable    = 0;
  nmStateRingPreStable = 0;

}


/******************************************************************************
 * Name:            NmResetNodeConfig
 * Called by:       Nm_DirOsek
 * Parameter:       (NM channel)
 * Return value:    ---
 * Description:     This API resets the node configuration.
 * Precondition:    ---
 * Note:            This API is also available, even if the node configuration 
 *                  monitoring is not enabled.
 *******************************************************************************/
static void NmResetNodeConfig( NM_CHANNEL_NMTYPE_ONLY )
{
  #if defined ( NM_ENABLE_CONFIG )
  vuint8 configByte;
  #endif

  nmStateRingStable    = 0;
  nmStateRingPreStable = 0;

  #if defined ( NM_ENABLE_CONFIG )
  /* clear the whole configuration */
    #if defined ( NM_ENABLE_INDEXED_NM )
  for( configByte =   (vuint8)channel      * (vuint8)((NM_NUMBER_OF_CONFIG_NODES)/8);
       configByte < (((vuint8)channel + 1) * (vuint8)((NM_NUMBER_OF_CONFIG_NODES)/8));
       configByte++ )
    #else
  for( configByte = 0; 
       configByte < (vuint8)((NM_NUMBER_OF_CONFIG_NODES)/8);
       configByte++ )
    #endif
  {
    nmConfig.nmConfigChar[configByte] = 0x00;
  }

  /* set own ECU number as present */
  configByte = NmCalculateOwnConfigByte( kNmCfg_EcuNr ); /* ESCAN00032811 */
  nmConfig.nmConfigChar[configByte] |= (vuint8)(1<<(kNmCfg_EcuNr & BYTE_OFFSET_MASK));
  #endif
}





#endif /* VGEN_ENABLE_NM_OSEK_D */

/* module specific MISRA deviations:
   MD_NmDirOsek_0310:
     Reason:     Casting to different object pointer type.
     Risk:       Invalid cast.
     Prevention: Check correct cast during review.
   MD_NmDirOsek_0488:
     Reason:     Pointer arithmetic used for efficiency and historical reasons
     Risk:       Usage of pointer arithmetic.
     Prevention: Assert correct usage during review.
   MD_NmDirOsek_0489:
     Reason:     Pointer arithmetic used for efficiency and historical reasons
     Risk:       Usage of pointer arithmetic.
     Prevention: Assert correct usage during review.
   MD_NmDirOsek_2214:
     Reason:     Body of control statement is on the same line and is not enclosed within braces
                 Assertions are implementes as macros to increase maintainability.
     Risk:       Code is not structured as intended, but this is limited to the macro defition.
     Prevention: Assertions should be used during the devleopment/intergration phase only.
*/

/**********************************************************************************************************************
  EOF
**********************************************************************************************************************/
/* ORGANI: STOPSINGLE_OF_MULTIPLE */

/************   Organi, Version 3.9.0 Vector-Informatik GmbH  ************/

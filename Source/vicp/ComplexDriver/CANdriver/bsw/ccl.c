/*****************************************************************************
| Project Name: CCL Communication Control Layer
| File Name: 
|
|  Description: CCL OEM for VECTOR
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2016 by Vector Informatik GmbH.           All rights reserved.
|
|               This software is copyright protected and proprietary 
|               to Vector Informatik GmbH. Vector Informatik GmbH 
|               grants to you only those rights as set out in the 
|               license conditions. All other rights remain with 
|               Vector Informatik GmbH.
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     ------------------------------------
| Et           Thomas Ebert              Vector Informatik GmbH
| Pet          Thomas Kuhl               Vector Informatik GmbH
| Dhf          Daniel Hof                Vector Informatik GmbH
| vismno       Martin Nonnenmann         Vector Informatik GmbH
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver      Author  Description
| ---------   -------  ------  --------------------------------------------------
| 2003-03-31  1.00     Pet     intitial version
| 2004-10-04  1.01     Pet     ESCAN00009749: new VECTOR OEM version defines
|                              change core version to V1.17.00
| 2005-07-26  1.02.FF  Pet     change core version to V1.37.00
| 2006-03-14  1.03.FF  Pet     change core version to V2.00.00
|                              Add NmBasic support
| 2006-05-05  1.03.00  Pet     change core Version to V2.02.00
| 2006-10-27  1.04.00  Pet     change core Version to V2.08.00
| 2007-07-24  1.05.00  Pet     change core Version to V2.16.00
| 2007-12-06  1.06.00  Dhf     change core Version to V2.22.00
|                              ESCAN00021267: Support of INM OSEK and NM ASR added
|                              ESCAN00023349: extern declaration of ApplCclSmStatusIndication() encapsulated
|                              ESCAN00023372: adaption to support NM ASR for AUTOSAR version 2.1
|                              ESCAN00023403: added support of new API functions
| 2008-07-07  1.07.00  Pet     ESCAN00027041: Add support for new OEM McLaren
|                              change core version to V2.29.00
| 2009-01-21  1.08.00  Dhf     change core Version to V2.35.01
| 2009-08-10  1.09.00  Dhf     ESCAN00035226: added implementation of ApplNmDirOsekFatalError()
|                              ESCAN00036920: provide extended NM initialization and minimum NM active time handling
| 2011-03-15  1.10.00  Dhf     ESCAN00049279: added support of NM ASR for ASR release 3
|                              ESCAN00049392: added precompile checks
|                              change core Version to V2.47.02
| 2012-05-04  1.11.00  Pet     ESCAN00058717: Support NM Variant AUTOSAR NM with NMBasic
| 2015-06-11  1.11.01  vismno  change core Version to V2.47.03
| 2015-11-05  1.12.00  vismno  ESCAN00086312: added support of NmHdLan
|                              change core Version to V2.47.05
| 2016-04-14  1.12.01  vismno  ESCAN00089450: changed encapsulation of function calls in NmOsek callbacks
|                              ESCAN00089463: changed channel parameter macros in NmOsek callbacks
|                              ESCAN00089497: added dummy statement in NmOsek callback
| 2016-04-25  1.13.00  vismno  ESCAN00089699: Support of missing Tx acknowledge observation
|                              change core version to 2.47.06
| 2016-05-10  1.13.01  vismno  ESCAN00089940: adapted encapsulation of dummy statements
|                              change core version to 2.47.07
| 2016-07-12  1.14.00  vismno  ESCAN00090958: Support EMC Wake Up Handling
|                              change core version to 2.47.08
| 2016-09-05  1.14.01  vismno  change core version to 2.47.09
| 2016-09-30  1.14.02  vismno  ESCAN00092203: Adapted filter rules and added plausibility checks
|                              change core version to 2.47.10
|****************************************************************************/

/***************************************************************************/
/* CORE                                                                    */
/***************************************************************************/

/*****************************************************************************
|  File Name: CCL.C
|
|  Description: Communication Control Layer (CORE) 
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2016 by Vector Informatik GmbH.           All rights reserved.
|
|               This software is copyright protected and proprietary 
|               to Vector Informatik GmbH. Vector Informatik GmbH 
|               grants to you only those rights as set out in the 
|               license conditions. All other rights remain with 
|               Vector Informatik GmbH.
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     ------------------------------------
| Bs           Thomas Balster            Vector Informatik GmbH
| Et           Thomas Ebert              Vector Informatik GmbH
| Zw           Werner Ziegler            Vector Informatik GmbH
| Pet          Thomas Petrus             Vector Informatik GmbH
| Dhf          Daniel Hof                Vector Informatik GmbH
| vismno       Martin Nonnenmann         Vector Informatik GmbH
| vismpf       Marco Pfalzgraf           Vector Informatik GmbH
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver     Author  Description
| ---------   ----    ------  ------------------------------------------------
| 31.05.02    1.00    Et/Zw   Initial version
| 02.12.02            Pet     add support for psa
| 2002-12-03  1.01    Pet     add support for Micronas CEVF
| 2003-02-04  1.02    Pet     ESCAN00004878: add support for GMLAN (single receive channel)
| 2003-02-06          Pet     ESCAN00004881: add support for NM JUNIOR
|                     Pet     ESCAN00004886: variable task container
|                     Pet     ESCAN00005256: add internal version controll
|                     Pet     ESCAN00005188: add support for CANdesc
| 2003-03-10          Pet     ESCAN00005255: add support for DBAG OSEK
| 2003-03-24  1.03    Pet     ESCAN00005195: wrong plausibility check for GMLAN
| 2003-04-01  1.04    Pet     ESCAN00005345: separation CCL into core files and OEM extension files
| 2003-06-05  1.05    Pet     CCL DLL version change
| 2003-06-16  1.05.01 Pet     review changes
| 2003-07-25  1.05.02 Pet     optimization for PSA organ type 3
| 2003-08-11  1.05.03 Pet     new DLL bugfix version
| 2003-08-19  1.05.04 Pet     new DLL version
|                     Pet     ESCAN00006299: check return value of "CanSleep"
|                     Pet     ESCAN00006375: multiple release of network requests
| 2003-09-24  1.06    Et      ESCAN00007184: EMC wake up
|                             ESCAN00007185: network management restriction
|                             ESCAN00007187: pagging support
|                             ESCAN00007189: initialization API
|                             ESCAN00007190: reworking (algorithms and namings)
| 2003-12-28  1.07    Et      ESCAN00007258: debug access to internal states (C_COMP_ANSI_CANOE)
|                             ESCAN00007259: initialisation of "cclComHwState" and "cclComSwState"
|                             ESCAN00007260: start EMC wake up timer at power on (+30 reset)
|                             ESCAN00007261: support EMC wake up for CAN driver API
|                             ESCAN00007262: "C_SINGLE_RECEIVE_BUFFER" and "C_MULTIPLE_RECEIVE_BUFFER"
|                             ESCAN00007263: DLL compatibility defines (< V1.06)
|                             ESCAN00007264: support edge triggered transceiver port interrupt
|                             ESCAN00007265: correct network restriction handling
|                             ESCAN00007266: correct network restriction handling
|                             ESCAN00007267: conditional message reception & internal network request
| 2004-01-17  1.07.01 Et      ESCAN00007277: COSMIC compiler option -pck
| 2004-01-21  1.07.02 Pet     ESCAN00007310: wrong #endif
|                             ESCAN00007311: missing encapsulation of cclCanSleepRepetition
|                             ESCAN00007296: different parameter list by Error Hook function CclFatalError
| 2004-01-23  1.08    Pet     ESCAN00007328: add component define for DPM
|                             ESCAN00007403: dummy assignment  NM_MSG_COND_RX_PARAMETER_NAME
|                             ESCAN00007404: support MISRA compliance
| 2004-02-02  1.09    Et      ESCAN00007429: incorrect CclComRelFct notification (set network restriction)
|                             ESCAN00007481: gateway component handle
|                             ESCAN00007548: extern declaration debug variables
| 2004-03-01  1.10    Pet     ESCAN00007741: compiler error in CclInitPowerOn
|                     Et      ESCAN00007722: support no external network requests
|                             ESCAN00007763: add include v_inc.h
|                             ESCAN00007773: no cancel of repeated CanSleep by external wake up
| 2004-03-16  1.11    Pet     ESCAN00007907: function CclGetNmState now API function
|                             ESCAN00007615: support of virtual networks (only for single receive channel)
|                             ESCAN00007939: wrong assertion check
| 2004-06-17  1.12    Pet     ESCAN00008082: EMC Wakeup Time in DPM is lower than 500ms
|                             ESCAN00008379: missing datatype in the prototypes of ApplCclVnDeactivated and ApplCclVnActivated
| 2004-07-02  1.13    Pet     ESCAN00008750: wrong assertion check
| 2004-07-30  1.14    Pet     ESCAN00009037: support multiple configurations
|                     Pet     ESCAN00009074: init value of variable "cclNmState"
|                     Pet     ESCAN00009098: support for GMLAN multichannel
|                     Pet     ESCAN00009118: compiler warning: variable network not used
| 2004-09-09  1.15    Pet     ESCAN00009431: add support for VAG NM C
| 2004-09-21  1.16    Pet     ESCAN00009573: change StateOn handling
|                             ESCAN00009192: missing paging define "DRV_API_CALLBACK_TYPE" in function "ApplCanMsgCondReceived"
|                             ESCAN00009623: prevent additional CAN wake up events
| 2004-10-04  1.17    Pet     ESCAN00009634: missing defines kCclNoCanAvailable and kCclCanAvailable
|                             ESCAN00009686: new core version defines
|                             ESCAN00009693: add support for CAN driver macro CanResetWakeup
|                             ESCAN00009740: inconsistent system request/release state
|                             reject ESCAN00009623
| 2004-10-12  1.18    Pet     ESCAN00009851: add support for Fj16lx
|                             ESCAN00009856: administrative service component handle
|                             ESCAN00009857: NM user data component handle
| 2004-11-02  1.19    Pet     ESCAN00010066: encapsulate CCL software state [only GM]
|                             ESCAN00010069: add support for transceiver type NONE
| 2004-11-10  1.20    Pet     ESCAN00010181: Add support for INM-OSEK (Organ Typ 1)
|                             ESCAN00010071: Transition to network state "prepare to sleep" in spite of pending internal network requests
|                             ESCAN00010087: Transition to network state "sleep" while running communication [only DC]
| 2004-12-10  1.21    Pet     ESCAN00010140: Wrong comment for cclNmRestriction[]. [only DC]
|                             ESCAN00009061: CclGetTrcvErrorPortFct contains NULL pointer
|                             ESCAN00010588: change the visibility of the network request field
|                             ESCAN00010613: Define VGEN_ENABLE_CIOA
| 2005-02-17  1.22    Pet     ESCAN00011217: inconsistencies between DPM and CCL state handling [only DC]
|                             ESCAN00011218: wakeup via CAN bus is not possible
| 2005-02-18  1.23    Bs      ESCAN00011142: change define VGEN_ENABLE_CIOA into CCL_ENABLE_EXTENDED_STATEON
|                             ESCAN00011147: add a comment at any time the CCL changes from an indexed to a code-doubled system
|                             ESCAN00011151: function CclGetNmState() is not needed anymore
|                             ESCAN00011167: add or modify some comments
|                             ESCAN00011035: Compiler error in ccl.c CclAssert: missing parameter
|                             ESCAN00011170: some variables and functions are not necessary if assertions are not activated
|                             ESCAN00011173: change names of function parameters
|                             ESCAN00011176: use defines instead of numbers
|                             ESCAN00011177: wrong variable used in 'CclSystemShutdown()'
|                             ESCAN00011187: change name and type of 'CanECUHandle'
|                             ESCAN00011212: change type of "channel" variable
|                             ESCAN00010661: support fullpreemptive OSEK-OS
|                     Pet     ESCAN00010421: advance system shutdown handling
|                             ESCAN00011118: NULL should not be used in the component
|                             ESCAN00011273: During restriction missing EMC wake up event
| 2005-03-07  1.24    Pet     ESCAN00011382: Add define for advanced shutdown handling
|                             ESCAN00011401: Add defines CCL_ENABLE_SYSTEM_STARTUP and CCL_ENABLE_SYSTEM_SHUTDOWN
| 2005-03-14  1.25    Pet     ESCAN00011430: Remove not used variable cclEndIndex
|                     Pet     ESCAN00011453: Wrong VN handling
|                     Pet     ESCAN00011500: Non expected wake up
|                     Pet     ESCAN00011503: Non wake up able through bus event
|                     Pet     ESCAN00011508: Wrong wake up reason
| 2005-04-05  1.26    Pet     ESCAN00011709: network restriction handling for multichannel systems
|                     Pet     ESCAN00011723: Add define for CclGetNmState
| 2005-04-11  1.27    Pet     ESCAN00011832: add support for wake up registration
|                             ESCAN00011833: add support for the component FIM
| 2005-04-20  1.28    Pet     ESCAN00011977: Support wake up for conditional wake up message
| 2005-05-13  1.29    Pet     ESCAN00012254: No wake up is possible during active restricion in special cirrumstances.
| 2005-05-23  1.30    Pet     ESCAN00012399: multichannel support for network initialization
| 2005-06-08  1.31    Pet     ESCAN00012515: Missing variable encapsulation
|                             ESCAN00012538: Add support for power fail handling
|                             ESCAN00012544: Lock global interrupt during sleep mode transition
| 2005-06-21  1.32    Pet     ESCAN00012614: Add support for single channel optimized CCL with a multichannel CAN driver
|                             ESCAN00012627: Missing internal standby event notification during power fail
|                             ESCAN00012638: Wrong CanOnline call
| 2005-07-05  1.33    Pet     ESCAN00012760: Review changes
|                             ESCAN00013027: Missing excplicitly variable initialization
|                             ESCAN00013208: Wrong call of CanInit during Bus Off recovery at the end of power fail
| 2005-08-15  1.34    Pet     ESCAN00012342: Wrong IL-NI PowerOn/Reset handling
|                             ESCAN00013241: Unexpected Tx timeout error (Tx observe) on first message after PowerFail
| 2005-08-27  1.35    Et      ESCAN00013331: GAIO compiler: symbol redefinition (variable: cclInit / function: CclInit)
| 2005-09-07  1.36    Pet     ESCAN00013450: adapt CAN driver API for reference implementation 1.20
| 2005-09-12  1.37    Pet     ESCAN00013229: update wake up timer handling
|                             ESCAN00013534: Wrong state change notification
|                             ESCAN00013232: Wrong CAN Driver state check during system shutdown
|                             ESCAN00013538: Reduce interrupt locking time in the CCL task
|                             ESCAN00013609: Macro CclAssert must be external visible
| 2005-09-27  1.38    Pet     ESCAN00013679: Rename kCclBugFixVersion in to kCclBugfixVersion
| 2005-09-29  1.39    Pet     ESCAN00012038: Additional WakeUp Reason has to be inserted
| 2005-10-26  1.40    Pet     ESCAN00014084: Support new memory qualifier
|                             ESCAN00014141: Advance version check
| 2005-11-10  1.41    Pet     ESCAN00014240: Add support of Nm Mazda
| 2005-11-15  1.42    Pet     ESCAN00014282: change Transceiver interrupt function container call
| 2005-11-16  1.43    Pet     ESCAN00013956: 5s 'alive' timer not used for local wakeup or remote wakeup
| 2005-11-25  1.44    Pet     ESCAN00014294: Compiler error if paging is used and CCL is located in a far page
| 2005-12-06  2.00    Pet     ESCAN00014618: Support CAN driver code replicated API (only single channel)
|                             ESCAN00014810: Advance the network request handling API
|                             ESCAN00014852: Add support for NPM functionality
|                             ESCAN00014934: Rename CCL version variable kCclBugfixVersion
|                             ESCAN00015231: Remove debug access to internal states
| 2006-03-24  2.01    Pet     ESCAN00014056: no VN activation
|                             adapt core for GMLAN
|                             ESCAN00015888: Inconsistent interrupt lock 
| 2006-04-21  2.02    Pet     ESCAN00016122: Missing variable encapsulation
| 2006-06-13  2.03    Pet     ESCAN00016600: Remove special handling for PSA
|                             ESCAN00016604: Add support for organ type 2
| 2006-07-06  2.04    Pet     ESCAN00016816: remove dead assignments
|                             ESCAN00016713: ECU is not able to wake up
|                             ESCAN00016726: Missing state change notification function call
|                             ESCAN00016860: CAN channel is not able to wake up
|                             ESCAN00016882: Add support for the old request/release API in newer CCL core versions
| 2006-07-18  2.05    Pet     ESCAN00016726: adapt CCL core for Il NI handling
|                             ESCAN00016969: Remove compiler warning
| 2006-07-25  2.06    Pet     ESCAN00017047: Remove Compiler error
|                             ESCAN00017270: Adapt the NM startup timer
|                             ESCAN00017283: NM (NmOsek-direct) sets the sleep indication bit later then the expected time
|                             ESCAN00017290: Runtime assertion during CclInitPowerOn
| 2006-08-18  2.07    Pet     ESCAN00017326: Support of FBL restart
| 2006-10-06  2.08    Pet     ESCAN00017917: ECU does not transmit CAN messages
|                             adaptions for SYMC
| 2006-11-17  2.09    Pet     ESCAN00018001: change plausibility checks
| 2006-11-27  2.10    Pet     ESCAN00018736: Add minimum CAN channel awake time
| 2007-01-15  2.11    Pet     ESCAN00019022: Adapt CCL_CORE for NM-Osek(indirect) Organ Type 3
| 2007-01-29  2.12    Pet     ESCAN00018893: Missing variable cast
| 2007-02-08  2.13    Pet     ESCAN00018648: ECU does not transmit or receive messages
| 2007-05-30  2.14    Pet     ESCAN00020286: CAN channel stay alive even if no application network request is pending
|                             ESCAN00020765: The CAN channel is not more able to wake up via a CAN bus event
| 2007-06-11  2.15    Pet     ESCAN00020295: CAN channel stay alive even if no application network request is pending
| 2007-06-26  2.16    Dhf     ESCAN00021188: Wrong variable used
| 2007-07-27  2.17    Dhf     ESCAN00021299: Support of ECU Manager added
|                     Dhf     ESCAN00021604: Extended NM initialization and NM activation timer handling added
| 2007-08-13  2.18    Dhf     ESCAN00021870: Wrong function prototypes
| 2007-09-18  2.19    Pet/Dhf ESCAN00019944: Support of limphome supervision added
|                             ESCAN00020011: Adaption of the CCL to support the keep alive timer handling
|                             ESCAN00020012: Support of the Gateway Sleep Wake Up Handling
|                             ESCAN00021083: Emergency Stop handling added
| 2007-10-10  2.20    Dhf     ESCAN00022602: Brace placement corrected
|                             ESCAN00022665: Encapsulated function CclSetUserRequest()
|                             ESCAN00022666: Summarisation of statements in CclReleaseCommunication()
|                             ESCAN00022670: NM initialization parameter validation adapted
|                             ESCAN00022723: Evaluation of the wake up source adapted
|                             ESCAN00022717: removed unsused variable
|                             ESCAN00022725: changed initialization of controller mode variables
|                             ESCAN00022743: added error code for wrong channel handle and component code for the car wake up manager
|                             ESCAN00022754: Offline switching in CclCanStandby() adapted
| 2007-11-14  2.21    Pet/Dhf ESCAN00022807: some minor changes to be MISRA compliant
|                             ESCAN00022973: Added support of transceiver TLE6152G
|                             ESCAN00022877: Add support for CAN channels which using no NM
|                             ESCAN00015144: Change configuration check for transceiver and CAN wake up settings
| 2007-12-06  2.22    Pet/Dhf ESCAN00023347: adaptions for NM type "None"
|                             ESCAN00023408: added support of NM passive mode
|                             ESCAN00023460: missing declaration of function CclInit()
|                             ESCAN00023464: adapted gateway handling to support multiple configuration
|                             ESCAN00023473: ECU does not change to sleep/stop mode
|                             ESCAN00023454: provided several features for general use
|                             ESCAN00023534: Adapt core for VN handling
|                             ESCAN00023724: added support of CAN driver reference implementation RI 1.2
| 2007-12-06  2.23    Pet     ESCAN00024231: Minor changes to support different INM Ecu types
| 2008-04-01  2.24    Dhf     ESCAN00025791: general adaptions
|                             ESCAN00026051: emergency stop handling made channel specific
|                             ESCAN00026013: Added check for number of channels
|                             ESCAN00026123: no transmission of CAN messages possible
|                             ESCAN00026161: bit operations adapted to be MISRA compliant
| 2008-04-25  2.25    Dhf     ESCAN00026414: encapsulation of braces
|                             ESCAN00026441: VN handling adapted
| 2008-04-29  2.25.01 Dhf     ESCAN00026476: minor changes for code filtering
| 2008-05-08  2.26    Dhf     ESCAN00026778: compile error when using an indexed CAN driver
|                             ESCAN00026785: added support for NM coordinator
|                             ESCAN00026780: compile error when an indexed NM Osek is used
|                             ESCAN00027176: MISRA compliance
| 2008-06-06  2.27    Dhf     ESCAN00027460: added support of ASR 3.0
| 2008-06-20  2.28    Pet     ESCAN00018830: Missing DPM state change notification during NM startup
|                             ESCAN00027769: Add compatibility to CANgen and DBKOMgen
| 2008-07-07  2.29    Dhf     ESCAN00028150: added definition of CAN driver API macros
| 2008-07-08  2.30    Dhf     ESCAN00028203: CAN channels do not start up due to external wake up events
| 2008-08-12  2.31    Dhf     ESCAN00029183: replace V_BUSTYPE_LIN switch with CCL_BUSTYPE_LIN
|                     Pet     ESCAN00029102: Support post build configurations which are mapped to different memory sections
| 2008-09-05  2.32    Dhf     ESCAN00029743: compile errors when multiple identity is enabled
| 2008-09-11  2.33    Pet     ESCAN00029931: Add support for complier and platform independent implementation of the ASR configuration pointer
| 2008-10-23  2.34    Dhf     ESCAN00030842: added delay for network related diagnostic
| 2008-12-03  2.35    Dhf     ESCAN00031376: added support of NM Honda
|                             ESCAN00031836: added else-path to avoid misra warning
| 2009-01-21  2.35.01 Dhf     ESCAN00027812: Ecu shutdown during running communication
| 2009-02-06  2.36    Dhf     ESCAN00032891: compiler error due to undefined variables
|                             ESCAN00032904: Add support of new memory qualifier V_MEMROMx_CFG
| 2009-04-02  2.37    Dhf     ESCAN00032540: added support of OEM GAC
|                             ESCAN00034328: BETA version - no series production allowed 
| 2009-04-08  2.38    Dhf     ESCAN00034471: compiler warning
|                             ESCAN00034501: adapted wait and resume handling
|                             ESCAN00034653: some minor improvements
|                             ESCAN00034741: removed error directive for state notification functions
| 2009-08-25  2.39    Dhf     ESCAN00037336: added support of NM Toyota 
| 2009-09-03  2.40    Dhf     ESCAN00037499: extended function EcuM_CheckWakeup() for LIN
|                             ESCAN00037554: some minor changes for code optimization
|                             ESCAN00037646: added support of OEM Baic
|                             ESCAN00037703: call CclEmergencyEnd()
|                             ESCAN00037697: add assertion for channel parameter in CclInit()
| 2009-12-03  2.41    Dhf     ESCAN00039551: no changes in this file
| 2010-01-07  2.42    Dhf     ESCAN00039850: no changes
| 2010-02-18  2.43    Dhf     ESCAN00040967: adapted CclInitPowerOn/CclInit
|                             ESCAN00040721: added interrupt lock
| 2010-06-15  2.44    Dhf     ESCAN00043411: adapted limphome detection for coordinator usecase
|                             ESCAN00043412: adapted remote sleep detection for coordinator usecase
|                             ESCAN00043536: switch only online in CclCanOnline if state is > waitBusSleep for coordinator
| 2010-07-20  2.45    Dhf     ESCAN00044173: adaption for extended gateway
|                             ESCAN00044298: relocate EcuM function call 
| 2010-08-05  2.46    Dhf     ESCAN00028369: added NPM data access
|                             ESCAN00028484: CCL does not accept communication requests
|                             ESCAN00028492: no communication request possible
|                             ESCAN00028799: NPM message timeout notification for wrong channel
|                             ESCAN00044475: compile warning
| 2010-08-16  2.47    Dhf     ESCAN00044481: resolved
|                             ESCAN00037523: changed initialization of cclNmState for NM High
|                             ESCAN00025339: Change handling of the internal stored CCL state via cclStateTmp
|                             ESCAN00044778: used macro is not defined
|                             ESCAN00044782: removed ";" after CclAssert(), adapted assertions for multiple configuration
| 2010-09-08  2.47.01 Dhf     ESCAN00041758: changes in CclEmergencyEnd()
| 2010-12-06  2.47.02 Dhf     ESCAN00039233: removed useless assignments
|                             ESCAN00044729: call VStdInitPowerOn() during initialization
|                             ESCAN00047685: encapsulated usage of cclNmType only for Nm_DirOsek
| 2015-06-01  2.47.03 vismno  ESCAN00057750: ECU does not react on CAN controller bus wake ups
|                             ESCAN00076639: Forward ApplCanWakeUp, ApplCanPreWakeUp and ApplCanMsgCondReceived calls to application for non Ccl-channels
| 2015-10-08  2.47.04 vismpf  ESCAN00085726: Support of missing Tx acknowledge observation
| 2015-11-05  2.47.05 vismno  ESCAN00086310: added support of NmHdLan
| 2016-04-25  2.47.06 vismno  ESCAN00089741: Support of missing Tx acknowledge observation for Ccl_Vector
| 2016-05-10  2.47.07 vismno  ESCAN00089936: no changes
| 2016-07-12  2.47.08 vismno  ESCAN00090959: changed type of cclEmcWakeUpTimer in context of Emc wakeup support for Ccl_Vector
| 2016-09-05  2.47.09 vismno  ESCAN00091671: changed order of 2 statements to properly disable MissingAck handling
| 2016-09-30  2.47.10 vismno  ESCAN00091878: set cclNmState to correct state if EMC wake up is used
|****************************************************************************/

#define CCL_MODULE

/***************************************************************************/
/* Include files                                                           */
/***************************************************************************/
#include "v_cfg.h"

#if defined( VGEN_GENY )
#include "v_inc.h"
#endif

#include "ccl.h"

#if defined(VGEN_ENABLE_ECUM_SMSVE)
#  include "SmSve.h"
#endif

/***************************************************************************/
/* Version check                                                           */
/***************************************************************************/
#if( CCL__CORE_VERSION != 0x0247)
#  error "CCL core: incorrect main or sub version"
#endif

#if( CCL__CORE_RELEASE_VERSION != 0x10)
#  error "CCL core: incorrect release version"
#endif

#if defined( VGEN_GENY )
#  if( CCL__COREDLL_VERSION < 0x0206u )
#    error "Incompatible CCL DLL-Version with this CCL-Implementation!"
#  endif
#  if( CCL__COREDLL_VERSION == 0x0206u )
#    if( CCL__COREDLL_RELEASE_VERSION < 0x07u )
#      error "Incompatible CCL DLL-Version with this CCL-Implementation!"
#    endif
#  endif
#endif

/***************************************************************************/
/* Plausibility checks                                                     */
/***************************************************************************/
#if( CCL_DLL_VERSION < 0x0106 )
#  if((defined(CCL_USE_REQUEST_SETCOM_FCT) && !defined(CCL_USE_REQUEST_CLEARCOM_FCT)) || \
      (!defined(CCL_USE_REQUEST_SETCOM_FCT) && defined(CCL_USE_REQUEST_CLEARCOM_FCT)))
#    error "Not all CCL state notification functions are configured. If you use the state notification then you have to configure all state notification functions !!"
#  endif
#endif

/* ESCAN00026013 */
#if( kCclNrOfChannels > 8)
#  error "The CCL does not support more than 8 channels!"
#endif

#if (kCclNumberOfUser > 255)
#  error "The CCL does not support more than 255 user requests!"
#endif

/***************************************************************************/
/* Defines                                                                 */
/***************************************************************************/

#if defined(C_SINGLE_RECEIVE_BUFFER) || defined(C_MULTIPLE_RECEIVE_BUFFER)
#  if !defined(CAN_CHANNEL_CANTYPE_ONLY)
#    define CAN_CHANNEL_CANTYPE_ONLY      void
#  endif
#endif

#if defined (CCL_ENABLE_EMC_WAKEUP)
#  define cclExtWakeUpReq     cclExtEmcWakeUpReq
#  if(kCclNrOfChannels > 1)
#    define CclExtComReqFctTbl CclExtEmcComReqFctTbl
#  else
#    define CclExtComReqFct    CclExtEmcComReqFct
#  endif
#else
#  define cclExtWakeUpReq     cclExtCanWakeUpReq
#  if(kCclNrOfChannels > 1)
#    define CclExtComReqFctTbl CclExtCanComReqFctTbl
#  else
#    define CclExtComReqFct    CclExtCanComReqFct
#  endif
#endif

#if( CCL_DLL_VERSION < 0x0106 )
#  define CCL_ENABLE_CANBEDDED_HANDLING
#endif

#if !defined ( VGEN_ENABLE_IF_ASRIFCAN )
#  if defined ( C_VERSION_REF_IMPLEMENTATION )
#    if( C_VERSION_REF_IMPLEMENTATION < 0x130u )
#      define CanGlobalInterruptDisable  CanInterruptDisable
#      define CanGlobalInterruptRestore  CanInterruptRestore
#    endif
#  else
#    error "The CAN driver reference implementation define is missing!"
#  endif
#endif

/* ESCAN00028150 */
#if !defined ( DRV_API_CALL_TYPE )
#  define DRV_API_CALL_TYPE
#endif
#if !defined ( DRV_API_CALLBACK_TYPE )
#  define DRV_API_CALLBACK_TYPE
#endif

#if defined (VGEN_ENABLE_NM_ASR_IF)
#  if defined (NM_COORDINATOR_SUPPORT_ENABLED) /* ESCAN00026785 */
#    if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
#      define CCL_ENABLE_NM_COORDINATOR
#    endif
#  endif

#  if !defined (CCL_ENABLE_NM_COORDINATOR)
#    if defined (NM_GW_EXT_ENABLED)
#      define CCL_ENABLE_NM_COORDINATOR
#    endif
#  endif
#endif

/***************************************************************************/
/* Macros                                                                  */
/***************************************************************************/
#if !defined(CAN_RESET_WAKEUP)
/* ESCAN00026778 */
#  if ( ( kCclNrOfSystemChannels > 1 ) || (defined (C_ENABLE_MULTICHANNEL_API) ) )
#    if defined ( VGEN_ENABLE_IF_ASRIFCAN )
       /* ESCAN00022807 */
#      define CanResetWakeup(a) (void)CanIf_SetControllerMode((vuint8)(a), CANIF_CS_STARTED)
#    else
#        define CanResetWakeup(a) ((void)CanWakeUp((a))) /* PRQA S 3453 */ /* MD_CBD_19.7 */
#    endif
#  else
#   if defined (VGEN_ENABLE_IF_ASRIFCAN)
       /* ESCAN00022807 */
#      define CanResetWakeup() (void)CanIf_SetControllerMode(CCL_CHANNEL_CCLINDEX, CANIF_CS_STARTED)
#   else
#        define CanResetWakeup() ((void)CanWakeUp())
#   endif
#  endif
#endif

/***************************************************************************/
/* Constants                                                               */
/***************************************************************************/

/***************************************************************************/
/* Local data definitions                                                  */
/***************************************************************************/
#if defined( CCL_ENABLE_EXTERNAL_REQUEST ) || defined ( VGEN_ENABLE_IF_ASRIFCAN )
#  if defined (CCL_ENABLE_EMC_WAKEUP)
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cclExtEmcWakeUpReq[kCclNrOfChannels];
 /*
 * Description        : flag to handle external channel wake up by EMC
 * Access rights      : r/w
 * Val. range / Coding: kCclNoExtEmcChWupReq / kCclExtEmcChWupReq
           (Hint: for downward compatibility these defines are used 
            instead of kCclNoExtChWupReq / kCclExtChWupReq)
 */

V_MEMRAM0 static V_MEMRAM1 vuint16 V_MEMRAM2 cclEmcWakeUpTimer[kCclNrOfChannels];
 /*
 * Description        : timer to force state transition to sleep after
 *                      after an invalid external channel wake up by EMC
 * Access rights      : r/w
 * Val. range / Coding: 0..kCclEmcWakeUpTime
 */
#  endif

V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cclExtCanWakeUpReq[kCclNrOfChannels];
 /*
 * Description        : flag to handle external channel wake up by CAN
 * Access rights      : r/w
 * Val. range / Coding: kCclNoExtCanChWupReq / kCclExtCanChWupReq
 */

#  if defined (CCL_ENABLE_EMC_WAKEUP)
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cclEmcWakeUpActive[kCclNrOfChannels];
 /*
 * Description        : timer flag to check if the wake up timer is running
 * Access rights      : r/w
 * Val. range / Coding: kCclEmcWakeUpTimerActive
 *                      kCclEmcWakeUpTimerDeactive
 */
#  endif

#  if defined(CCL_ENABLE_SLEEP_REPETITION)
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cclCanSleepRepetition[kCclNrOfChannels];
 /*
 * Description        : flag to handle repetition of function "CanSleep"
 *                      due to failed transition from NORMAL to SLEEP mode
 * Access rights      : r/w
 * Val. range / Coding: kCclNoRepeatCanSleep / kCclRepeatCanSleep
 */
#  endif

V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM1 cclCanSleepReturnCode[kCclNrOfChannels];
 /*
 * Description        : return value of function "CanSleep" to ask
 *                      the application about the following handling
 * Access rights      : r/w
 * Val. range / Coding: kCclNoRepeatCanSleep / kCclRepeatCanSleep
 */

#  if defined (CCL_ENABLE_EMC_WAKEUP)
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cclEmcWakeUpExp[kCclNrOfChannels];
 /*
 * Description        : timer flag to check if the emc wake up timer is 
 *                      expiered
 * Access rights      : r/w
 * Val. range / Coding: kCclEmcWakeUpTimerRunning / kCclEmcWakeUpTimerDeactive
 */
#  endif
#endif

#if defined( CCL_ENABLE_INTERNAL_REQUEST )
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cclIntNetReq[kCclNrOfNetworks];
 /*
 * Description        : flag to handle internal network request
 * Access rights      : r/w
 * Val. range / Coding: 0..kCclNrOfNetworks
 */

V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cclIntNetRel[kCclNrOfNetworks];
 /*
 * Description        : flag to handle internal network release
 * Access rights      : r/w
 * Val. range / Coding: 0..kCclNrOfNetworks
 */

V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cclIntNetRelHistory[kCclNrOfNetworks];
 /*
 * Description        : flag to handle internal network release
 * Access rights      : r/w
 * Val. range / Coding: 0..kCclNrOfNetworks
 */

#endif

V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cclComHwState[kCclNrOfChannels];
 /*
 * Description        : state of HW to make communication possible
 *                      (PLL, CAN controller, CAN transceiver)
 * Access rights      : r/w
 * Val. range / Coding: 0: kCclComHwEnabled  (HW is enabled by power management)
 *                      1: kCclComHwDisabled (HW is disabled by power management)
 */

V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cclBusState[kCclNrOfChannels];
 /*
 * Description        : Bus state 
 * Access rights      : r/w
 * Val. range / Coding: 0: kCclBusOn
 *                      1: kCclBusOff
 */

#if defined(C_ENABLE_APPLCANPREWAKEUP_FCT)
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cclBusTrcvState[kCclNrOfChannels]; /* ESCAN00057750 */
 /*
 * Description        : Trcv state 
 * Access rights      : r/w
 * Val. range / Coding: 0: kCclBusOn  Trcv is in normal
 *                      1: kCclBusOff  Trcv is in standby or sleep
 */
#endif

#if defined(CCL_ENABLE_TRCV_PORT_INT)
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cclWakeUpIntState[kCclNrOfChannels];
 /*
 * Description        : state of wake up interrupt by IO port
 * Access rights      : r/w
 * Val. range / Coding: 0: kCclDisableWakeUpInt (port INT is disabled)
 *                      1: kCclEnableWakeUpInt  (port INT is enabled)
 */
#endif

#  if( CCL_DLL_VERSION < 0x0106 )
#  else
#    if defined( CCL_ENABLE_CANBEDDED_HANDLING ) 
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cclStackInit;
 /*
 * Description        : flag to distinguish between the system specific and
 *                      channel specific CANbedded stack intialisation
 * Access rights      : r/w
 * Val. range / Coding: 0: system specific initialisation
 *                      1: channel specific initialisation
 */
#    endif
#  endif

#if ( ( defined ( VGEN_ENABLE_IF_ASRIFCAN ) && defined( CCL_NM_TYPE_NMJUNIOR ) ) || \
      ( defined ( CCL_ENABLE_MISSING_ACK_HANDLING ) ) )
V_MEMRAM0 V_MEMRAM1 vuint8 V_MEMRAM2 cclBusOffFlag[kCclNrOfChannels];
/*
 * Description        : Flag which shows the BusOff state 
 * Access rights      : r/w
 * Val. range / Coding: 0: BusOff recovery is not active
 *                      1: BusOff recovery is active 
 */
#endif

#if defined (CCL_ENABLE_MIN_NM_ACTIVATION_TIME) /* ESCAN00021604 */
V_MEMRAM0 static V_MEMRAM1 vuint16 V_MEMRAM2 cclMinNmActivationTimer[kCclNrOfChannels];
 /*
 * Description        : NM Osek activation timer
 * Access rights      : r/w
 * Val. range         : 0..65535
 */
#endif

#if defined ( CCL_ENABLE_MISSING_ACK_HANDLING )
V_MEMRAM0 static V_MEMRAM1 vuint16 V_MEMRAM2 cclMissingAckTimer[kCclNrOfChannels];
/* Description        : timer variable for missing ACK detection
 * Access rights      : r/w
 * Val. range         : 0 ... 0xFFFF */

V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cclMissingAckTxStopped[kCclNrOfChannels];
/* Description        : boolean variable indicating Tx Pause after missing ACK detection
 * Access rights      : r/w
 * Val. range         : 0 (false) / 1 (true) */

V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cclMissingAckEnabled[kCclNrOfChannels];
/* Description        : boolean variable indicating if Missing ACK handling is enabled
 * Access rights      : r/w
 * Val. range         : 0 (false) / 1 (true) */
#endif

#if defined (NMHDLAN_NM_TYPE)
V_MEMRAM0 static V_MEMRAM1 vuint8 V_MEMRAM2 cclNmCommunicationState[kCclNrOfChannels];
/* Description        : variable to store current communication state of the NM
 * Access rights      : r/w
 * Val. range         : 0 ... 0xFF */
#endif

/***************************************************************************/
/* Global data definitions                                                 */
/***************************************************************************/
#if defined( CCL_ENABLE_ERROR_HOOK )
V_MEMRAM0 V_MEMRAM1 vuint8 V_MEMRAM2 cclChannelNumber;
 /*
 * Description        : channel number to identify the occured assertion
 * Access rights      : r/w
 * Val. range / Coding: 0..kCclNrOfChannels
 */

V_MEMRAM0 V_MEMRAM1 vuint16 V_MEMRAM2 cclErrorCode;
 /*
 * Description        : error code to identify the occured assertion
 * Access rights      : r/w
 * Val. range / Coding: s. CCL_INC.H
 */

V_MEMRAM0 V_MEMRAM1 vuint16 V_MEMRAM2 cclErrorLine;
 /*
 * Description        : error line to identify the occured assertion
 * Access rights      : r/w
 * Val. range / Coding: s. DRV, IL, NM, TP or DIAG
 */

V_MEMRAM0 V_MEMRAM1 vuint16 V_MEMRAM2 cclComponentID;
 /*
 * Description        : component identifier to identify the occured assertion
 * Access rights      : r/w
 * Val. range / Coding: s. CCL_INC.H
 */
#endif

#if defined(CCL_ENABLE_INTERNAL_REQUEST)
V_MEMRAM0 volatile V_MEMRAM1 vuint8 V_MEMRAM2 cclIntNetState[kCclNetReqTableSize];
 /*
 * Description        : state of internal network request/release
 * Access rights      : r/w
 * Val. range / Coding: 0: network released
 *                      1: network requested
 */

#endif

V_MEMRAM0 V_MEMRAM1 vuint8 V_MEMRAM2 cclNmState[kCclNrOfChannels];
 /*
 * Description        : state of CCL depending
 *                      on external channel requests and
 *                      internal network requests or releases
 * Access rights      : r/w
 * Val. range / Coding: 0: kCclNmStateSleep (neither external nor internal request)
 *                      1: kCclNmStateGoToSleep (only external request)
 *                      2: kCclNmStateActive (at least internal request)
 *                      3: kCclNmPowerFail (power fail is active)
 */

#if defined( CCL_ENABLE_SW_COM_STATE )
V_MEMRAM0 V_MEMRAM1 vuint8 V_MEMRAM2 cclComSwState[kCclNrOfChannels];
 /*
 * Description        : communication state of CANbedded stack (DRV, IL, NM)
 * Access rights      : r/w
 * Val. range / Coding: 0: kCclComSwOff  (communication is switched off by CCL)
 *                      1: kCclComSwOn   (communication is switched on by CCL)
 */
#endif

/***************************************************************************/
/* Local function prototypes                                               */
/***************************************************************************/
static void CCL_API_CALL_TYPE CclInitPorts(CCL_CHANNEL_CCLTYPE_ONLY);

#if defined ( VGEN_ENABLE_IF_ASRIFCAN )
#  if defined (CCL_ENABLE_EXTERNAL_REQUEST)
static void CCL_INTERNAL_CALL_TYPE CclWakeUp(CCL_CHANNEL_CCLTYPE_ONLY);
#  endif
#endif

#if ( defined( C_CLIENT_VECTOR ) )
#  if ( defined( CCL_ENABLE_MISSING_ACK_HANDLING ) )
static void CCL_INTERNAL_CALL_TYPE CclCanOnline (CCL_CHANNEL_CCLTYPE_ONLY);
static void CCL_INTERNAL_CALL_TYPE CclCanOffline (CCL_CHANNEL_CCLTYPE_ONLY);
#  endif
#endif

/* ESCAN00032540 */

#if defined (VGEN_ENABLE_NM_ASR_CAN)
#  if defined (CCL_ENABLE_NM_COORDINATOR)
#  endif
#endif

#if defined(CCL_ENABLE_EXTENDED_NMINIT) /* ESCAN00021604 */
#  if ( (defined CCL_ENABLE_MIN_NM_ACTIVATION_TIME ) ) /* ESCAN00022670 */
static void CclValidateNmInitValue( CCL_CHANNEL_CCLTYPE_FIRST tCclNmInitParaType nmInitValue );
#  endif
#endif

/***************************************************************************/
/* Local functions                                                         */
/***************************************************************************/

#if defined (VGEN_ENABLE_NM_ASR_CAN)
#  if defined (CCL_ENABLE_NM_COORDINATOR)
#  endif
#endif

/* ESCAN00032540 */

#if ( ( ( defined( C_CLIENT_VECTOR ) ) && \
        ( defined( CCL_ENABLE_MISSING_ACK_HANDLING ) ) ) ) /* ESCAN00025791 */
/************************************************************************
| NAME:               CclCanOnline
| CALLED BY:          CCL
|                     Application is NOT ALLOWED to call this function!
| PRECONDITIONS:      -
| INPUT PARAMETERS:   single channel: void
|                     multiple channels: channel parameter
| RETURN VALUE:       -
| DESCRIPTION:        This API function switches the CAN driver to online mode.
|*************************************************************************/
#  if ( defined( C_CLIENT_VECTOR ) )
static void CCL_INTERNAL_CALL_TYPE CclCanOnline (CCL_CHANNEL_CCLTYPE_ONLY)
#  else
void CCL_API_CALL_TYPE CclCanOnline(CCL_CHANNEL_CCLTYPE_ONLY)
#  endif
{
  CanGlobalInterruptDisable();

  {
    {

#  if ( defined ( CCL_ENABLE_MISSING_ACK_HANDLING ) )
      if( !cclMissingAckTxStopped[CCL_CHANNEL_CCLINDEX] )
#  endif
      {
#  if defined (CCL_ENABLE_NM_COORDINATOR)
        if( (cclNmState[CCL_CHANNEL_CCLINDEX] > kCclStateWaitBusSleep) 
          )
#  endif
        {
#  if defined (VGEN_ENABLE_IF_ASRIFCAN)
          (void)CanIf_SetPduMode(CCL_CHANNEL_CCLINDEX, CANIF_SET_ONLINE);
#  else
          CanOnline(CCL_CHANNEL_CANPARA_ONLY);
#  endif
        }
      }
    }
  }

  CanGlobalInterruptRestore();
}

/************************************************************************
| NAME:               CclCanOffline
| CALLED BY:          CCL
|                     Application is NOT ALLOWED to call this function!
| PRECONDITIONS:      -
| INPUT PARAMETERS:   single channel: void
|                     multiple channels: channel parameter
| RETURN VALUE:       -
| DESCRIPTION:        This API function switches the CAN driver to online mode.
|*************************************************************************/
#  if ( defined( C_CLIENT_VECTOR ) )
static void CCL_INTERNAL_CALL_TYPE CclCanOffline (CCL_CHANNEL_CCLTYPE_ONLY)
#  else
void CCL_API_CALL_TYPE CclCanOffline(CCL_CHANNEL_CCLTYPE_ONLY)
#  endif
{
  CanGlobalInterruptDisable();

  {
#  if ( defined ( CCL_ENABLE_MISSING_ACK_HANDLING ) )
    /* If CanOffline is called (by NM) during T Pause Missing ACK Handling shall be cancelled.
     * So that CanOnline is not called by Ccl after T Pause but has to be called by NM. */
    if( cclMissingAckTxStopped[CCL_CHANNEL_CCLINDEX] == 1u )
    {
      /* Missing ACK handling is cancelled and restarted when First message is transmitted after CanOnline is called again. */
      cclMissingAckTimer[CCL_CHANNEL_CCLINDEX] = 0u;
      cclMissingAckTxStopped[CCL_CHANNEL_CCLINDEX] = 0u;
    }
#  endif

#  if defined (VGEN_ENABLE_IF_ASRIFCAN)
    (void)CanIf_SetPduMode(CCL_CHANNEL_CCLINDEX, CANIF_SET_TX_OFFLINE);
#  else
    CanOffline( CCL_CHANNEL_CANPARA_ONLY );
#  endif
  }

  CanGlobalInterruptRestore();
}

#endif /* CCL_ENABLE_DIAGNOSTIC_DELAY || CCL_ENABLE_MISSING_ACK_HANDLING */

#if defined(CCL_ENABLE_ERROR_HOOK)
/************************************************************************
| NAME:               CclFatalError
| PROTOTYPE:          void CCL_API_CALL_TYPE CclFatalError(vuint8 ChannelNumber, vuint16 ErrorCode, vuint16 ErrorLine, vuint8 ComponentID)
| CALLED BY:          assertions within the CANbedded stack and/or CCL
|                     re-directe the call of the "FatalError"-functions
|                     Application is NOT ALLOWED to call this function!
| PRECONDITIONS:      'use CCL ErrorHook' has to be activated in the used generation tool to notify the application
| INPUT PARAMETERS:   ChannelNumber: 0-255    (255 default for 'NO_CHANNEL_INFO_AVAILABLE')
|                     ErrorCode    : 0-65.535 (individual specified in each layer)
|                     ErrorLine    : __LINE__ (0 if no information is available)
|                     ComponentID  : s. CCL_INC.H
| RETURN VALUE:       void
| DESCRIPTION:        Convert the given error information to the global error handling
|                     variables and call a application function to handle the error.
|*************************************************************************/
void CCL_API_CALL_TYPE CclFatalError(CanChannelHandle ChannelNumber, vuint16 ErrorCode, vuint16 ErrorLine, vuint8 ComponentID)
 {
   /* pin assertion information */
   cclChannelNumber = (vuint8)ChannelNumber; /* channel number */
   cclErrorCode     = ErrorCode;     /* error code */
   cclErrorLine     = ErrorLine;     /* error line */
   cclComponentID   = ComponentID;   /* component ID */

   /* error hook (assertions) */
   ApplCclFatalError();
 }
#endif

/************************************************************************
| NAME:               CclInitPorts
| PROTOTYPE:          void CclInitPorts(CanChannelHandle channel)
|                     or
|                     void CclInitPorts(void)
| CALLED BY:          CclInitPowerOn
|                     Application is NOT ALLOWED to call this function!
| PRECONDITIONS:      to be called in loop for each channel
| INPUT PARAMETERS:   channel (multiple channel)
|                     or
|                     void (single channel)
| RETURN VALUE:       void
| DESCRIPTION:        calls function container to inizialise all HW ports
|                     (both the transceiver port register and the
|                     transceiver port interrupt) with the channel specific
|                     parameters.
|*************************************************************************/
static void CCL_API_CALL_TYPE CclInitPorts(CCL_CHANNEL_CCLTYPE_ONLY)
{
#if defined (CCL_ENABLE_MULTIPLE_CONFIG)
  if((cclIdChMap[V_ACTIVE_IDENTITY_LOG] & (vuint8)((vuint8)1 << (CCL_CHANNEL_CCLINDEX))) > 0x00)
#endif    
  {
#if defined( CCL_ENABLE_TRCV_TYPE_NONE )
   /* nothing to do */
#else
   /* init transceiver port register */
#  if(kCclNrOfChannels > 1)
   if( CclInitTrcvFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
   {
     /* By using the following table of function calls, code-doubled functions 
     * are called from the indexed CCL. This is done to simplify the called 
     * functions (no distinction of the parameter 'channel' is necessary). */
     (CclInitTrcvFctTbl[CCL_CHANNEL_CCLINDEX])();
   }
#  else
   CclInitTrcvFct();
#  endif
#endif

#if defined(CCL_ENABLE_TRCV_PORT_INT)
#  if defined(CCL_ENABLE_EXTERNAL_REQUEST)
   /* init transceiver port interrupt */
#    if(kCclNrOfChannels > 1)
   /* By using the following tables of function calls, code-doubled functions 
  * are called from the indexed CCL. This is done to simplify the called 
  * functions (no distinction of the parameter 'channel' is necessary). */
   if(CclConfigTrcvIntFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
   {
     (CclConfigTrcvIntFctTbl[CCL_CHANNEL_CCLINDEX])();
   }
   if(CclDisableTrcvIntFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
   {
     (CclDisableTrcvIntFctTbl[CCL_CHANNEL_CCLINDEX])();
   }
   if(CclClearTrcvIntFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
   {
     (CclClearTrcvIntFctTbl[CCL_CHANNEL_CCLINDEX])();
   }
#    else
   CclConfigTrcvIntFct();
   CclDisableTrcvIntFct();
   CclClearTrcvIntFct();
#    endif
   /* set INT state to "disable" */
   cclWakeUpIntState[CCL_CHANNEL_CCLINDEX] = kCclDisableWakeUpInt;
#  endif
#endif
  }
 }

#if defined ( VGEN_ENABLE_IF_ASRIFCAN )
#else
#  if defined(CCL_ENABLE_EXTERNAL_REQUEST)
 /************************************************************************
 | NAME:               ApplCanWakeUp
 | PROTOTYPE:          void ApplCanWakeUp(CanChannelHandle channel)
 |                     or
 |                     void ApplCanWakeUp(void)
 | CALLED BY:          CANdrv:  CanWakeUpInt / CanWakeUpTask (internal wake up INT)
 |                     CCL:     CclCanWakeUpInt (external wake up INT)
 |                     Application is NOT ALLOWED to call this function!
 | PRECONDITIONS:      -
 | INPUT PARAMETERS:   channel (multiple channel)
 |                     or
 |                     void (single channel)
 | RETURN VALUE:       void
 | DESCRIPTION:        Function notifies WakeUp over RX/INH transceiver port
 |                     (handled in CCL) or WakeUp over CAN controller
 |                     (handled in CAN driver), sets the external channel
 |                     wakeup request flag and requests the power manager state.
 |*************************************************************************/
void DRV_API_CALLBACK_TYPE ApplCanWakeUp(CAN_CHANNEL_CANTYPE_ONLY)
 {
#    if ( kCclNrOfSystemChannels > kCclNrOfChannels )
   if( channel >= kCclNrOfChannels )
   {
     ApplCclCanWakeUp( channel ); /* ESCAN00076639 */
   }
   else
#    endif
   {
     /* set external EMC or CAN wake up request */
     cclExtWakeUpReq[CCL_CHANNEL_CCLINDEX] = kCclExtChWupReq;

#    if defined( CCL_ENABLE_INTERNAL_REQUEST)
     if(cclIntNetReq[CCL_CHANNEL_CCLINDEX] == kCclNoIntNetReq) /* ESCAN00011217 and ESCAN00011218 */
#    endif
     {

#    if ( defined(CCL_USE_REQUEST_SETEXTCOM_FCT) || defined(VGEN_ENABLE_ECUM_SMSVE) )
       /* external EMC or CAN communication request notification */
       if( cclNmState[CCL_CHANNEL_CCLINDEX] == kCclNmStateSleep )
       {
#      if defined(CCL_USE_REQUEST_SETEXTCOM_FCT)
#        if(kCclNrOfChannels > 1)
         if (CclExtComReqFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
         {
           /* By using the following table of function calls, code-doubled functions 
            * are called from the indexed CCL. This is done to simplify the called 
            * functions (no distinction of the parameter 'channel' is necessary). */
           (CclExtComReqFctTbl[CCL_CHANNEL_CCLINDEX])();
         }
#        else
         CclExtComReqFct();
#        endif
#      endif

#    if defined(VGEN_ENABLE_ECUM_SMSVE)
         /* CCL is in sleep: check if RUN state of the ECU Manager is not yet requested (e.g. from an internal communication request before): */
         if( EcuM_ComM_HasRequestedRUN(CCL_CHANNEL_CCLPARA_ONLY) == FALSE )
         {
           (void)EcuM_ComM_RequestRUN(CCL_CHANNEL_CCLPARA_ONLY);
         }
#    endif
       }
#  endif

     }
   }
 }

#    if defined(C_ENABLE_APPLCANPREWAKEUP_FCT)
 /************************************************************************
 | NAME:               ApplCanPreWakeUp
 | PROTOTYPE:          void ApplCanPreWakeUp(CanChannelHandle channel)
 |                     or
 |                     void ApplCanPreWakeUp(void)
 | CALLED BY:          CANdrv:  CanWakeUpInt / CanWakeUpTask (internal wake up INT)
 |                     Application is NOT ALLOWED to call this function!
 | PRECONDITIONS:      -
 | INPUT PARAMETERS:   channel (multiple channel)
 |                     or
 |                     void (single channel)
 | RETURN VALUE:       void
 | DESCRIPTION:        Function sets the transceiver in normal mode
 |*************************************************************************/
void DRV_API_CALLBACK_TYPE ApplCanPreWakeUp(CAN_CHANNEL_CANTYPE_ONLY) /* ESCAN00057750 */
{
#      if ( kCclNrOfSystemChannels > kCclNrOfChannels )
  if( channel >= kCclNrOfChannels )
  {
    ApplCclCanPreWakeUp( channel ); /* ESCAN00076639 */
  }
  else
#      endif
  {

     {
      /* check the actual bus state, to prevent multiple activations */
      if(cclBusTrcvState[CCL_CHANNEL_CCLINDEX] == kCclBusOff)
      {
        /* the bus state is off */
#      if defined( CCL_ENABLE_TRCV_TYPE_NONE )
       /* nothing to do */
#      else
       /* set transceiver to NORMAL mode by port register */
#        if(kCclNrOfChannels > 1)
       if( CclWakeUpTrcvFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
       {
         /* By using the following table of function calls, code-doubled functions 
          * are called from the indexed CCL. This is done to simplify the called 
          * functions (no distinction of the parameter 'channel' is necessary). */
         (CclWakeUpTrcvFctTbl[CCL_CHANNEL_CCLINDEX])();
       }
#        else
       CclWakeUpTrcvFct();
#        endif
       cclBusTrcvState[CCL_CHANNEL_CCLINDEX] = kCclBusOn;
#      endif
      }
    }
  }
}
#    endif
#  endif
#endif

#if ( defined CCL_ENABLE_MISSING_ACK_HANDLING )
/*****************************************************************************************************
| NAME:             ApplCanInit
| CALLED BY:        CAN driver
| PRECONDITIONS:    initialization
| INPUT PARAMETERS: CAN_CHANNEL_CANTYPE_FIRST = defined to nothing in single channel system
|                   CAN_CHANNEL_CANTYPE_FIRST = channel number in multi channel system
|                   txHwObjectFirstUsed = first HW object used by CAN driver for transmission
|                   txHwObjectFirstUnused = first HW object unused by CAN driver for transmission
| RETURN VALUE:     none
| DESCRIPTION:      Ccl uses the TX_OBSERVE mechanism for the Missing ACK handling, 
|                   to which this CAN driver application callback function belongs.
|                   This function is called during initialization and it is empty.
|*****************************************************************************************************/
# if( ( (defined NMBASIC_BUSOFF_RECOV_EXTENDED) && (defined NMBASIC_ENABLE_BUSOFFREP_MSG) ) )
void ApplNmBasicCanInit( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txHwObjectFirstUsed, CanObjectHandle txHwObjectFirstUnused )
# else
void ApplCanInit( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txHwObjectFirstUsed, CanObjectHandle txHwObjectFirstUnused )
# endif
{
  /* ApplCanInit is not used by Ccl. Just forward to application. */
  ApplCclCanInit( CAN_CHANNEL_CANPARA_FIRST txHwObjectFirstUsed, txHwObjectFirstUnused );
}

/************************************************************************
| NAME:             ApplCanTxObjStart
| CALLED BY:        CAN driver
| PRECONDITIONS:    initialization
| INPUT PARAMETERS: CAN_CHANNEL_CANTYPE_FIRST = defined to nothing in single channel system
|                   CAN_CHANNEL_CANTYPE_FIRST = channel number in multi channel system
|                   txHwObject = HW object used by CAN driver for current transmission
| RETURN VALUE:     none
| DESCRIPTION:      Ccl uses the TX_OBSERVE mechanism for the Missing ACK handling, 
|                   to which this CAN driver application callback function belongs.
|                   This function is called when a message transmission is started.
|                   If the Missing ACK handling is enabled the Tx confirmation timeout timer is set to the
|                   configured value to start the timeout observation.
|*************************************************************************/
# if( ( (defined NMBASIC_BUSOFF_RECOV_EXTENDED) && (defined NMBASIC_ENABLE_BUSOFFREP_MSG) ) )
void ApplNmBasicTxObjStart( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txHwObject )
# else
void ApplCanTxObjStart( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txHwObject )
# endif
{
#      if ( kCclNrOfSystemChannels > kCclNrOfChannels )
  if( channel < kCclNrOfChannels )
#      endif
  {
    if( !cclMissingAckTxStopped[CCL_CHANNEL_CCLINDEX] )
    {
      /* Start timeout for missing ACK detection.
       * Generated value is 0 if feature not active on this channel. */
      cclMissingAckTimer[CCL_CHANNEL_CCLINDEX] = cclMissingAckTimeoutValue[CCL_CHANNEL_CCLINDEX];
    }
  }

  /* Forward callback to application */
  ApplCclCanTxObjStart( CAN_CHANNEL_CANPARA_FIRST txHwObject );
}

/************************************************************************************************
| NAME:             ApplCanTxObjConfirmed
| CALLED BY:        CAN driver
| PRECONDITIONS:    initialization
| INPUT PARAMETERS: CAN_CHANNEL_CANTYPE_FIRST = defined to nothing in single channel system
|                   CAN_CHANNEL_CANTYPE_FIRST = channel number in multi channel system
|                   txHwObject = HW object used by CAN driver for current transmission
| RETURN VALUE:     none
| DESCRIPTION:      Ccl uses the TX_OBSERVE mechanism for the Missing ACK handling, 
|                   to which this CAN driver application callback function belongs.
|                   If the Missing ACK handling is enabled the Tx confirmation timeout timer is 
|                   stopped here.
|************************************************************************************************/
# if( ( (defined NMBASIC_BUSOFF_RECOV_EXTENDED) && (defined NMBASIC_ENABLE_BUSOFFREP_MSG) ) )
void ApplNmBasicTxObjConfirmed( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txHwObject )
# else
void ApplCanTxObjConfirmed( CAN_CHANNEL_CANTYPE_FIRST CanObjectHandle txHwObject )
# endif
{
#      if ( kCclNrOfSystemChannels > kCclNrOfChannels )
  if( channel < kCclNrOfChannels )
#      endif
  {
    if( !cclMissingAckTxStopped[CCL_CHANNEL_CCLINDEX] )
    {
      /* Stop timeout for missing ACK detection. */
      cclMissingAckTimer[CCL_CHANNEL_CCLINDEX] = 0u;
    }
  }

  /* Forward callback to application */
  ApplCclCanTxObjConfirmed( CAN_CHANNEL_CANPARA_FIRST txHwObject );
}
#endif /* defined CCL_ENABLE_MISSING_ACK_HANDLING */

#if ( defined ( VGEN_ENABLE_IF_ASRIFCAN ) )
#  if defined (CCL_ENABLE_EXTERNAL_REQUEST)
/* ESCAN00028203 */
/************************************************************************
 | NAME:               EcuM_CheckWakeup
 | PROTOTYPE:          void EcuM_CheckWakeup (EcuM_WakeupSourceType wakeupSource)
 | CALLED BY:          CAN driver
 |                     Application is NOT ALLOWED to call this function!
 | PRECONDITIONS:      -
 | INPUT PARAMETERS:   EcuM_WakeupSourceType
 | RETURN VALUE:       void
 | DESCRIPTION:        
 |****************************************************/ 
void EcuM_CheckWakeup( EcuM_WakeupSourceType wakeupSource )
{

#    if defined ( VGEN_ENABLE_IF_ASRIFCAN )
  {
    (void)CanIf_CheckWakeup(wakeupSource);
  }
#    endif
}

/************************************************************************
 | NAME:               EcuM_SetWakeupEvent
 | PROTOTYPE:          void EcuM_SetWakeupEvent (EcuM_WakeupSourceType sources)
 | CALLED BY:          CANIf
 |                     LINIf
 |                     Application is NOT ALLOWED to call this function!
 | PRECONDITIONS:      -
 | INPUT PARAMETERS:   EcuM_WakeupSourceType
 | RETURN VALUE:       void
 | DESCRIPTION:        
 |****************************************************/ 
void EcuM_SetWakeupEvent(EcuM_WakeupSourceType sources)
{
#    if ( kCclNrOfChannels > 1 )
  CanChannelHandle channel;

  /* ESCAN00022723 */
 
  /* Get the appropriate CCL channel of the wake up event: */
  channel = CclGetEventChannelHandle(sources);

  /* check channel value: */
  CclAssert(channel < kCclNrOfChannels ,kCclErrWrongWakeUpChannel)
#    else
#      if defined(V_ENABLE_USE_DUMMY_STATEMENT)
  sources = sources;
#      endif
#    endif

  CclWakeUp(CCL_CHANNEL_CCLPARA_ONLY);
}

/************************************************************************
 | NAME:               CclWakeUp
 | PROTOTYPE:          static void CclWakeUp(CclChannelType channel)
 |                     or
 |                     static void CclWakeUp(void)
 | CALLED BY:          CCL
 |                     Application is NOT ALLOWED to call this function!
 | PRECONDITIONS:      -
 | INPUT PARAMETERS:   channel (multiple channel)
 |                     or
 |                     void (single channel)
 | RETURN VALUE:       void
 | DESCRIPTION:        Function notifies the CCL about a wake up event
 |*************************************************************************/
static void CCL_INTERNAL_CALL_TYPE CclWakeUp(CCL_CHANNEL_CCLTYPE_ONLY)
{
#  if ( kCclNrOfSystemChannels > 1 )
#      if( kCclNrOfChannels == 1)
  if(channel == (CanChannelHandle)kCclChannelIndex)
#      endif
#    endif
  {
    /* set external EMC or CAN wake up request */
    cclExtWakeUpReq[CCL_CHANNEL_CCLINDEX] = kCclExtChWupReq;
    
    if(cclIntNetReq[CCL_CHANNEL_CCLINDEX] == kCclNoIntNetReq)
    {

#    if ( defined(CCL_USE_REQUEST_SETEXTCOM_FCT) )
      /* external EMC or CAN communication request notification */
      if( cclNmState[CCL_CHANNEL_CCLINDEX] == kCclNmStateSleep )
      {
#      if defined(CCL_USE_REQUEST_SETEXTCOM_FCT)
#        if(kCclNrOfChannels > 1)
        if (CclExtComReqFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
        {
          /* By using the following table of function calls, code-doubled functions 
           * are called from the indexed CCL. This is done to simplify the called 
           * functions (no distinction of the parameter 'channel' is necessary). */
          (CclExtComReqFctTbl[CCL_CHANNEL_CCLINDEX])();
        }
#        else
        CclExtComReqFct();
#        endif
#      endif

      }
#    endif

    }
  }
}
#  endif
#endif

/***************************************************************************/
/* Global functions                                                        */
/***************************************************************************/

/************************************************************************
 | NAME:               CclCanNormal
 | PROTOTYPE:          void CclCanNormal(CanChannelHandle channel)
 |                     or
 |                     void CclCanNormal(void)
 | CALLED BY:          CCL
 |                     Application is NOT ALLOWED to call this function!
 | PRECONDITIONS:      -
 | INPUT PARAMETERS:   channel (multiple channel)
 |                     or
 |                     void (single channel)
 | RETURN VALUE:       void
 | DESCRIPTION:        set CAN transceiver and CAN controller to NORMAL mode
 |*************************************************************************/
void CCL_API_CALL_TYPE CclCanNormal(CCL_CHANNEL_CCLTYPE_ONLY)
{

#if defined(CCL_ENABLE_EXTERNAL_REQUEST)
#  if defined(CCL_ENABLE_SLEEP_REPETITION)
  /* stop sleep repetition handling */
  cclCanSleepRepetition[CCL_CHANNEL_CCLINDEX] = kCclNoRepeatCanSleep;
#  endif
#endif

  {
    /* check the actual bus state, to prevent multiple activations */
    if(cclBusState[CCL_CHANNEL_CCLINDEX] == kCclBusOff)
    {
      /* the bus state is off */
#if defined( CCL_ENABLE_TRCV_TYPE_NONE )
   /* nothing to do */
#else

#if defined(C_ENABLE_APPLCANPREWAKEUP_FCT)
      /* check the actual transceiver state, to prevent multiple activations */
      if(cclBusTrcvState[CCL_CHANNEL_CCLINDEX] == kCclBusOff) /* ESCAN00057750 */
      {
#endif
         /* set transceiver to NORMAL mode by port register */
#  if(kCclNrOfChannels > 1)
         if( CclWakeUpTrcvFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
         {
           /* By using the following table of function calls, code-doubled functions 
            * are called from the indexed CCL. This is done to simplify the called 
            * functions (no distinction of the parameter 'channel' is necessary). */
           (CclWakeUpTrcvFctTbl[CCL_CHANNEL_CCLINDEX])();
         }
#  else
         CclWakeUpTrcvFct();
#  endif
#endif

#if defined(C_ENABLE_APPLCANPREWAKEUP_FCT)
         cclBusTrcvState[CCL_CHANNEL_CCLINDEX] = kCclBusOn; /* ESCAN00057750 */
      }
#endif

#  if defined(CCL_ENABLE_EXTERNAL_REQUEST)
#    if(kCclNrOfChannels > 1)
       /* check wake up / sleep support */
       if((cclNmWakeUpAble & (vuint8)((vuint8)1 << (CCL_CHANNEL_CCLINDEX))) != kCclNoWakeUpAble)
#    endif
       {
         /* set CAN controller to NORMAL mode */
         /* ESCAN00026778 */
        CanGlobalInterruptDisable();
#    if ( ( kCclNrOfSystemChannels > 1 ) || (defined (C_ENABLE_MULTICHANNEL_API) ) )
        CanResetWakeup(CCL_CHANNEL_CANPARA_ONLY);
#    else
        CanResetWakeup();
#    endif
        CanGlobalInterruptRestore();

       }
#  endif
       /* set the CAN state to on */
       cclBusState[CCL_CHANNEL_CCLINDEX] = kCclBusOn;
     }
#  if defined(CCL_ENABLE_EXTERNAL_REQUEST)
    else if(cclCanSleepReturnCode[CCL_CHANNEL_CCLINDEX] == kCanFailed)
    {
#    if(kCclNrOfChannels > 1)
      /* check wake up / sleep support */
      if((cclNmWakeUpAble & (vuint8)((vuint8)1 << (CCL_CHANNEL_CCLINDEX))) != kCclNoWakeUpAble)
#    endif
      {
        /* set CAN controller to NORMAL mode */
        /* ESCAN00026778 */
        CanGlobalInterruptDisable();
#    if ( ( kCclNrOfSystemChannels > 1 ) || (defined (C_ENABLE_MULTICHANNEL_API) ) ) 
        CanResetWakeup(CCL_CHANNEL_CANPARA_ONLY);
#    else
        CanResetWakeup();
#    endif
        CanGlobalInterruptRestore();

      }
    }
    /* ESCAN00031836 */
    else
    {
    }
#  endif

#if defined(CCL_ENABLE_EXTERNAL_REQUEST)
     /* reset the CanSleep return value */
    cclCanSleepReturnCode[CCL_CHANNEL_CCLINDEX] = kCanOk;
#endif

  }
}

 /************************************************************************
 | NAME:                CclCanStandby
 | PROTOTYPE:           void CclCanStandby(CanChannelHandle channel)
 |                      or
 |                      void CclCanStandby(void)
 | CALLED BY:           CCL
 |                      Application is NOT ALLOWED to call this function!
 | PRECONDITIONS:       -
 | INPUT PARAMETERS:    channel (multiple channel)
 |                      or
 |                      void (single channel)
 | RETURN VALUE:        void
 | DESCRIPTION:         set CAN controller and CAN transceiver to SLEEP mode,
 |                      release the power manager state and enable the
 |                      external wakeup port INT
 |*************************************************************************/
void CCL_API_CALL_TYPE CclCanStandby(CCL_CHANNEL_CCLTYPE_ONLY)
{
  CanGlobalInterruptDisable();

  {
    {
#if defined (CCL_ENABLE_EMC_WAKEUP)
      /* check EMC wake up timer */
      if(cclEmcWakeUpTimer[CCL_CHANNEL_CCLINDEX] == kCclEmcWakeUpTimerStopped)
#endif
      {
#  if defined(CCL_ENABLE_EXTERNAL_REQUEST) || defined (VGEN_ENABLE_IF_ASRIFCAN)
#    if defined ( VGEN_ENABLE_IF_ASRIFCAN )
        /* check wake up / sleep support */
        if((cclNmWakeUpAble & (vuint8)((vuint8)1 << (CCL_CHANNEL_CCLINDEX))) != kCclNoWakeUpAble )
#    else
#      if(kCclNrOfChannels > 1)
        /* check wake up / sleep support */
        if((cclNmWakeUpAble & (vuint8)((vuint8)1 << (CCL_CHANNEL_CCLINDEX))) != kCclNoWakeUpAble )
#      endif
#    endif
        {
#    if defined ( VGEN_ENABLE_IF_ASRIFCAN )
          /* set CAN controller to SLEEP mode */
          cclCanSleepReturnCode[CCL_CHANNEL_CCLINDEX] = (vuint8)CanIf_SetControllerMode(CCL_CHANNEL_CCLINDEX, CANIF_CS_SLEEP);
#    else
          /* set CAN controller to SLEEP mode */
          cclCanSleepReturnCode[CCL_CHANNEL_CCLINDEX] = CanSleep(CCL_CHANNEL_CANPARA_ONLY);
#    endif
        }
#    if defined ( VGEN_ENABLE_IF_ASRIFCAN )
        else
        {
          {
            /* set CAN controller to STOP mode */
            cclCanSleepReturnCode[CCL_CHANNEL_CCLINDEX] = (vuint8)CanIf_SetControllerMode(CCL_CHANNEL_CCLINDEX, CANIF_CS_STOPPED);
          }
        }
#    endif

         {          
           /* set CCL into wait bus sleep */
           cclNmState[CCL_CHANNEL_CCLINDEX] = kCclStateWaitBusSleep;
         }
         
       /* check "CanSleep" return code */
       if(cclCanSleepReturnCode[CCL_CHANNEL_CCLINDEX] != kCanFailed)
#  endif
       {
#if defined ( VGEN_ENABLE_IF_ASRIFCAN )
         {
           /* The Rx path must not be switched offline until the CAN controller was 
              switched successfully to sleep / stop mode. Here we are in sleep / stop mode
              and can now switch both Tx and Rx offline: */
           (void)CanIf_SetPduMode(CCL_CHANNEL_CCLINDEX, CANIF_SET_OFFLINE);
         }
#endif

#if defined(CCL_ENABLE_EXTERNAL_REQUEST) || defined (VGEN_ENABLE_IF_ASRIFCAN)
#  if defined(CCL_ENABLE_SLEEP_REPETITION)
         /* stop sleep repetition handling */
         cclCanSleepRepetition[CCL_CHANNEL_CCLINDEX] = kCclNoRepeatCanSleep;
#  endif
#endif

#  if defined( CCL_ENABLE_TRCV_TYPE_NONE )
         /* nothing to do */
#  else
         /* set transceiver to SLEEP or STANDBY mode by port register */
#    if(kCclNrOfChannels > 1)
         if( CclSleepTrcvFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
         {
           /* By using the following table of function calls, code-doubled functions 
           * are called from the indexed CCL. This is done to simplify the called 
           * functions (no distinction of the parameter 'channel' is necessary). */
           (CclSleepTrcvFctTbl[CCL_CHANNEL_CCLINDEX])();
         }
#    else
         CclSleepTrcvFct();
#    endif
#  endif

         /* set the CCL state to SLEEP */
         cclNmState[CCL_CHANNEL_CCLINDEX] = kCclStateSleep;

         /* set the bus state to off */
         cclBusState[CCL_CHANNEL_CCLINDEX] = kCclBusOff;

#if defined(C_ENABLE_APPLCANPREWAKEUP_FCT)
         cclBusTrcvState[CCL_CHANNEL_CCLINDEX] = kCclBusOff; /* ESCAN00057750 */
#endif

#if defined(CCL_USE_REQUEST_CLEARCOM_FCT)
#  if ( defined ( VGEN_ENABLE_IF_ASRIFCAN ) && defined ( CCL_NM_TYPE_NMJUNIOR ) ) 
         if (cclBusOffFlag[CCL_CHANNEL_CCLINDEX] == kCclBusOffRecNotActive)
#  endif
         {
           /* communication release notification */
#  if(kCclNrOfChannels > 1)
           if(CclComRelFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
           {
             /* By using the following table of function calls, code-doubled functions 
              * are called from the indexed CCL. This is done to simplify the called 
              * functions (no distinction of the parameter 'channel' is necessary). */
             (CclComRelFctTbl[CCL_CHANNEL_CCLINDEX])();
           }
#  else
         CclComRelFct();
#  endif
         }
#endif

#if defined(CCL_ENABLE_TRCV_PORT_INT)
#  if defined(CCL_ENABLE_INTERNAL_REQUEST)
         if(cclIntNetReq[CCL_CHANNEL_CCLINDEX] == kCclNoIntNetReq)
         {
           /* no internal request is pending */
#  endif
           /* enable transceiver port interrupt */
#  if( kCclNrOfChannels > 1 )
           /* By using the following table of function calls, code-doubled functions 
           * are called from the indexed CCL. This is done to simplify the called 
           * functions (no distinction of the parameter 'channel' is necessary). */
           /* Wtihin the following function calls a maybe pending 
           *  Transceiver interrupt will be cleared! */
           if(CclClearTrcvIntFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
           {
             (CclClearTrcvIntFctTbl[CCL_CHANNEL_CCLINDEX])();
           }
           if(CclEnableTrcvIntFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
           {
             (CclEnableTrcvIntFctTbl[CCL_CHANNEL_CCLINDEX])();
           }
#  else
           /* Within the following function calls a maybe pending 
           *  Transceiver interrupt will be cleared! */
           CclClearTrcvIntFct();
           CclEnableTrcvIntFct();
#  endif

           /* set INT state to "enable" */
           cclWakeUpIntState[CCL_CHANNEL_CCLINDEX] = kCclEnableWakeUpInt;

#  if defined(CCL_ENABLE_TRCV_PORT_EDGE_TRIGGER)
           /* check transceiver port register */
#    if( kCclNrOfChannels > 1 )
           if(CclCheckTrcvIntFctTbl[CCL_CHANNEL_CCLINDEX]() == kCclTrcvWakeIntPending)
           {
             /* By using the following table of function calls, code-doubled functions 
             * are called from the indexed CCL. This is done to simplify the called 
             * functions (no distinction of the parameter 'channel' is necessary). */

             /* disable transceiver port interrupt */
             if(CclDisableTrcvIntFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
             {
               (CclDisableTrcvIntFctTbl[CCL_CHANNEL_CCLINDEX])();
             }
#    else
             if(CclCheckTrcvIntFct() == kCclTrcvWakeIntPending)
             {
               /* disable transceiver port interrupt */
               CclDisableTrcvIntFct();
#    endif

               /* check INT state */
               if(cclWakeUpIntState[CCL_CHANNEL_CCLINDEX] == kCclEnableWakeUpInt)
               {
                 /* external EMC/CAN wake up notification */
                 CclCanWakeUpInt(CCL_CHANNEL_CCLPARA_ONLY);
               }
             }
#  endif
#  if defined(CCL_ENABLE_INTERNAL_REQUEST)
           }
#  endif
#endif

#if defined(VGEN_ENABLE_ECUM_SMSVE)
         (void)EcuM_ComM_ReleaseRUN(CCL_CHANNEL_CCLPARA_ONLY);
#endif
       }

#if defined(CCL_ENABLE_EXTERNAL_REQUEST) || defined (VGEN_ENABLE_IF_ASRIFCAN)
#  if defined(CCL_ENABLE_SLEEP_REPETITION)
       cclCanSleepRepetition[CCL_CHANNEL_CCLINDEX] = ApplCclCanStandby(CCL_CHANNEL_CCLPARA_FIRST cclCanSleepReturnCode[CCL_CHANNEL_CCLINDEX]);

       CclAssert( ( ((cclCanSleepRepetition[CCL_CHANNEL_CCLINDEX] == kCclNoRepeatCanSleep) && (cclCanSleepReturnCode[CCL_CHANNEL_CCLINDEX] == kCanOk)) || \
                        ((cclCanSleepRepetition[CCL_CHANNEL_CCLINDEX] == kCclNoRepeatCanSleep) && (cclCanSleepReturnCode[CCL_CHANNEL_CCLINDEX] == kCanNotSupported)) || \
                        ((cclCanSleepRepetition[CCL_CHANNEL_CCLINDEX] == kCclRepeatCanSleep) && (cclCanSleepReturnCode[CCL_CHANNEL_CCLINDEX] == kCanFailed)) \
                       ), kWrongReturnValue)

#  else
       (void)ApplCclCanStandby(CCL_CHANNEL_CCLPARA_FIRST cclCanSleepReturnCode[CCL_CHANNEL_CCLINDEX]);
#  endif
#endif

#if defined(CCL_NM_TYPE_NONE)
#    if defined(CCL_ENABLE_EXTERNAL_REQUEST) || defined (VGEN_ENABLE_IF_ASRIFCAN)
       /* check "CanSleep" return code */
       if(cclCanSleepReturnCode[CCL_CHANNEL_CCLINDEX] != kCanFailed)
#    endif
       {
#    if(kCclNrOfChannels > 1)
         if((cclChannelWithoutNm & (vuint8)((vuint8)1 << (CCL_CHANNEL_CCLINDEX))) != kCclChWithNm )
#    endif
         {
           ApplCclNmStateChange(CCL_CHANNEL_CCLPARA_FIRST kCclStateWaitBusSleep, kCclStateSleep);
         }
       }
#endif

#if defined(CCL_ENABLE_INTERNAL_REQUEST)
#  if defined(CCL_USE_REQUEST_SETINTCOM_FCT) 
       if(cclIntNetReq[CCL_CHANNEL_CCLINDEX] != kCclNoIntNetReq)
       {
         /* min. one internal request is pending */
#    if defined( CCL_USE_REQUEST_SETINTCOM_FCT )
#      if defined(CCL_ENABLE_EXTERNAL_REQUEST) || defined (VGEN_ENABLE_IF_ASRIFCAN)
         /* check "CanSleep" return code */
         if(cclCanSleepReturnCode[CCL_CHANNEL_CCLINDEX] != kCanFailed) /* ESCAN00022602 */
#      endif
         {

#      if ( defined ( VGEN_ENABLE_IF_ASRIFCAN ) && defined ( CCL_NM_TYPE_NMJUNIOR ) ) 
           /* check if this function is called out of the BusOff indication function: */
           if (cclBusOffFlag[CCL_CHANNEL_CCLINDEX] == kCclBusOffRecNotActive)
#      endif
           {
           
             /* internal communication request notification */
#      if ( kCclNrOfChannels > 1 )
             if (CclIntComReqFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
             {
               /* By using the following table of function calls, code-doubled functions 
                * are called from the indexed CCL. This is done to simplify the called 
                * functions (no distinction of the parameter 'channel' is necessary). */
               (CclIntComReqFctTbl[CCL_CHANNEL_CCLINDEX])();
             }
#      else
             CclIntComReqFct();
#      endif
           }
         }
#    endif

       }
#  endif
#endif
      }
    }
  }

  CanGlobalInterruptRestore();
 }

#if (defined( CCL_ENABLE_EXTERNAL_REQUEST ) ||\
     defined( CCL_ENABLE_INTERNAL_REQUEST ))
/************************************************************************
| NAME:               CclTask
| PROTOTYPE:          void CclTask( void )
| CALLED BY:          generated task container function
|                     Application is NOT ALLOWED to call this function!
| PRECONDITIONS:
| INPUT PARAMETERS:   void
| RETURN VALUE:       void
| DESCRIPTION:        internal network request handling
|                     internal network release handling
|                     external channel request handling
|                     EMC wake up timeout handling
|                     sleep repetition handling
|*************************************************************************/
void CCL_API_CALL_TYPE CclTask(void)
 {
#  if(kCclNrOfChannels > 1)
#    if defined (VGEN_ENABLE_IF_ASRIFCAN)
   uint8 channel;
#    else
   CanChannelHandle channel; /* number of physical channels */
#    endif
#  endif

#  if defined(CCL_NM_TYPE_NONE)
   vuint8 cclNmStateTmp[kCclNrOfChannels];
#  endif

#  if(kCclNrOfNetworks > 1)
   vuint8 network; /* number of logical networks */
#  endif

#  if(kCclNrOfChannels > 1)
   channel = 0;
#  endif

#  if(kCclNrOfNetworks > 1)
   network = 0;
#  endif

#  if defined ( VGEN_ENABLE_NM_ASR_CAN )
#    if defined (CCL_ENABLE_NM_COORDINATOR)
#    endif
#  endif

#  if(kCclNrOfNetworks > 1)
   for(network=0; network<kCclNrOfNetworks; network++)
   {
#  endif
     /* ESCAN00010661 
      *  Disable the global interrupt to guarantee data consistency 
      *  if this function is called from interrupt insted of task level. */

#    if(kCclNrOfChannels > 1)
#      if defined (VGEN_ENABLE_IF_ASRIFCAN)
     channel = (uint8)network;
#      else
     channel = (CanChannelHandle)network;
#      endif
#    endif

#  if defined (CCL_ENABLE_MULTIPLE_CONFIG)
     if((cclIdChMap[V_ACTIVE_IDENTITY_LOG] & (vuint8)((vuint8)1 << (CCL_CHANNEL_CCLINDEX))) > 0x00)
     {
#  endif    
     
     /* check HW communication state */
     if(cclComHwState[CCL_CHANNEL_CCLINDEX] == kCclComHwEnabled)
     {
#  if defined( CCL_ENABLE_INTERNAL_REQUEST )
       
#  endif
         CanGlobalInterruptDisable();
#  if defined( CCL_ENABLE_INTERNAL_REQUEST )
/* ===================================================================== */
/* = begin "internal network request handling" ========================= */
/* ===================================================================== */
         
           /* pending internal network request? */
           if((cclIntNetReq[CCL_NET_CCLINDEX] != kCclNoIntNetReq))
           {
#    if defined(VGEN_ENABLE_ECUM_SMSVE)
             if( EcuM_GetState() == ECUM_STATE_RUN )
             {
#    endif

#      if defined(CCL_ENABLE_EMC_WAKEUP)
               if( (cclNmState[CCL_CHANNEL_CCLINDEX] < kCclNmStateActive) ||
                   (cclEmcWakeUpTimer[CCL_CHANNEL_CCLINDEX] != kCclEmcWakeUpTimerStopped) )
#      else
               /* ESCAN00026441 */
               if(cclNmState[CCL_CHANNEL_CCLINDEX] < kCclNmStateActive)
#      endif
               {
#    if defined (CCL_ENABLE_EMC_WAKEUP)
                   /* reject message reception notification */
                   CanResetMsgReceivedCondition(CCL_CHANNEL_CANPARA_ONLY);
#    endif

                   /* container function for transition from SLEEP or GO TO SLEEP to ACTIVE */

#      if(kCclNrOfChannels > 1)
                   /* By using the following table of function calls, code-doubled functions 
                    * are called from the indexed CCL. This is done to simplify the called 
                    * functions (no distinction of the parameter 'channel' is necessary). */
                  (void)CclNmActiveReqFctTbl[CCL_NET_CCLINDEX](cclIntNetReq[CCL_NET_CCLINDEX]);
#      else
                  (void)CclNmActiveReqFct(cclIntNetReq[CCL_NET_CCLINDEX]);
#      endif

#    if ( defined(CCL_ENABLE_MIN_NM_ACTIVATION_TIME) ) /* ESCAN00021604, ESCAN00030842 */
                 if(cclNmState[CCL_CHANNEL_CCLINDEX] < kCclStateGoToSleep)
                 {
#      if defined(CCL_ENABLE_MIN_NM_ACTIVATION_TIME)
                   if (cclMinNmActivationTimerValue[CCL_CHANNEL_CCLINDEX] != kCclNmActTimerStopped)
                   {
                     (void)CclRequestCommunication(CCL_CHANNEL_CCLINDEX);
                   
                     cclMinNmActivationTimer[CCL_CHANNEL_CCLINDEX] = cclMinNmActivationTimerValue[CCL_CHANNEL_CCLINDEX] + 1; /* plus 1 because timer is decremented in same cycle */
                   }
#      endif
                 }
#    endif

#      if defined(CCL_NM_TYPE_NONE)
                 cclNmStateTmp[CCL_CHANNEL_CCLINDEX] = cclNmState[CCL_CHANNEL_CCLINDEX];
#      endif
                 /* set CCL state to ACTIVE */
                 cclNmState[CCL_CHANNEL_CCLINDEX] = kCclNmStateActive;
#      if defined(CCL_NM_TYPE_NONE)
#        if(kCclNrOfChannels > 1)
                 if((cclChannelWithoutNm & (vuint8)((vuint8)1 << (CCL_CHANNEL_CCLINDEX))) != kCclChWithNm )
#        endif
                 {
                   ApplCclNmStateChange(CCL_CHANNEL_CCLPARA_FIRST cclNmStateTmp[CCL_CHANNEL_CCLINDEX], kCclNmStateActive);
                 }
#      endif
             
                 /* ESCAN00026441 */
               }

               /* clear internal network request flag */
               cclIntNetReq[CCL_NET_CCLINDEX] = kCclNoIntNetReq;

               /* clear internal network release history flag */
               cclIntNetRelHistory[CCL_NET_CCLINDEX] = kCclNoIntNetRel;

#    if defined( CCL_ENABLE_EXTERNAL_REQUEST )
#      if defined (CCL_ENABLE_EMC_WAKEUP)
               /* clear external EMC channel request */
               cclExtEmcWakeUpReq[CCL_CHANNEL_CCLINDEX] = kCclNoExtChWupReq;

               /* stop EMC wake up timer */
               cclEmcWakeUpTimer[CCL_CHANNEL_CCLINDEX] = kCclEmcWakeUpTimerStopped;
               cclEmcWakeUpActive[CCL_CHANNEL_CCLINDEX] = kCclEmcWakeUpTimerDeactive;
               cclEmcWakeUpExp[CCL_CHANNEL_CCLINDEX] = kCclEmcWakeUpTimerDeactive;
             
#      endif

               /* clear external CAN channel request flag */
               cclExtCanWakeUpReq[CCL_CHANNEL_CCLINDEX] = kCclNoExtChWupReq;

#      if defined(CCL_ENABLE_SLEEP_REPETITION)
               /* stop sleep repetition handling */
               cclCanSleepRepetition[CCL_CHANNEL_CCLINDEX] = kCclNoRepeatCanSleep;
#      endif
#    endif
#    if defined(VGEN_ENABLE_ECUM_SMSVE)
             }
#    endif
           }

/* ===================================================================== */
/* = end "internal network request handling" =========================== */
/* ===================================================================== */

/* ===================================================================== */
/* = begin "internal network release handling" ========================= */
/* ===================================================================== */
         if( (cclIntNetRel[CCL_NET_CCLINDEX] != kCclNoIntNetRel) )
         {
           /* no communication request is pending,
            * set the CCL state to prepare sleep */

#    if defined(CCL_NM_TYPE_NONE)
           cclNmStateTmp[CCL_CHANNEL_CCLINDEX] = cclNmState[CCL_CHANNEL_CCLINDEX];
#    endif
           cclNmState[CCL_CHANNEL_CCLINDEX] = kCclNmStateGoToSleep;

           /* container function for transition from active to prepare sleep */
#    if ( kCclNrOfChannels > 1 )
           /* By using the following table of function calls, code-doubled functions 
            * are called from the indexed CCL. This is done to simplify the called 
            * functions (no distinction of the parameter 'channel' is necessary). */
           (CclNmSleepReqFctTbl[CCL_CHANNEL_CCLINDEX])(cclIntNetRel[CCL_NET_CCLINDEX]);
#    else
           CclNmSleepReqFct(cclIntNetRel[CCL_NET_CCLINDEX]);
#    endif
           
#    if defined(CCL_NM_TYPE_NONE)
#      if(kCclNrOfChannels > 1)
           if((cclChannelWithoutNm & (vuint8)((vuint8)1 << (CCL_CHANNEL_CCLINDEX))) != kCclChWithNm )
#      endif
           {
             ApplCclNmStateChange(CCL_CHANNEL_CCLPARA_FIRST cclNmStateTmp[CCL_CHANNEL_CCLINDEX], kCclNmStateGoToSleep);
           }
#    endif

           /* clear internal network release flag */
           cclIntNetRel[CCL_NET_CCLINDEX] = kCclNoIntNetRel;

           /* clear internal network release history flag */
           cclIntNetRelHistory[CCL_NET_CCLINDEX] = kCclNoIntNetRel;

         }
/* ===================================================================== */
/* = end "internal network release handling" =========================== */
/* ===================================================================== */
#  endif

#  if defined(CCL_ENABLE_EXTERNAL_REQUEST)
/* ===================================================================== */
/* = begin "external channel request handling" ========================= */
/* ===================================================================== */
#    if defined (CCL_ENABLE_EMC_WAKEUP)
         /* pending external EMC channel request */
         if(cclExtEmcWakeUpReq[CCL_CHANNEL_CCLINDEX] == kCclExtChWupReq)
         {
           /* EMC request is pending,
            * check the CCL state
            */
           if( cclNmState[CCL_CHANNEL_CCLINDEX] == kCclNmStateSleep )
           {
             /* CCL state is sleep,
              * set CAN communication (HW and SW) to NORMAL mode
              */
              CclCanNormal(CCL_CHANNEL_CCLPARA_ONLY);

             /* start EMC wake up timer */
             cclEmcWakeUpTimer[CCL_CHANNEL_CCLINDEX] = kCclEmcWakeUpTime + 1;
             cclEmcWakeUpActive[CCL_CHANNEL_CCLINDEX] = kCclEmcWakeUpTimerActive;
           }

           /* clear external EMC channel request */
           cclExtEmcWakeUpReq[CCL_CHANNEL_CCLINDEX] = kCclNoExtChWupReq;
         }
#    endif

         /* pending external CAN channel request? */
         if(cclExtCanWakeUpReq[CCL_CHANNEL_CCLINDEX] == kCclExtChWupReq)
         {
#    if defined(VGEN_ENABLE_ECUM_SMSVE)
           if( EcuM_GetState() == ECUM_STATE_RUN )
#    endif
           {

             if( cclNmState[CCL_CHANNEL_CCLINDEX] < kCclNmStateGoToSleep )
             {
#      if defined(CCL_NM_TYPE_NONE)
               /* save old state */
               cclNmStateTmp[CCL_CHANNEL_CCLINDEX] = cclNmState[CCL_CHANNEL_CCLINDEX];
#      endif

#      if defined (CCL_ENABLE_EMC_WAKEUP)
               /* stop EMC wake up timer */
               cclEmcWakeUpTimer[CCL_CHANNEL_CCLINDEX] = kCclEmcWakeUpTimerStopped;
               cclEmcWakeUpActive[CCL_CHANNEL_CCLINDEX] = kCclEmcWakeUpTimerDeactive;
               cclEmcWakeUpExp[CCL_CHANNEL_CCLINDEX] = kCclEmcWakeUpTimerDeactive;
#      endif

               if( cclNmState[CCL_CHANNEL_CCLINDEX] == kCclNmStateSleep )
               {

                 /* set CCL state to prepare sleep */
                 cclNmState[CCL_CHANNEL_CCLINDEX] = kCclNmStateGoToSleep;

                 /* container function for transition from sleep to prepare sleep */
#      if(kCclNrOfChannels > 1)
                 /* By using the following table of function calls, code-doubled functions 
                  * are called from the indexed CCL. This is done to simplify the called 
                  * functions (no distinction of the parameter 'channel' is necessary). */
                 (CclNmPrepareSleepReqFctTbl[CCL_CHANNEL_CCLINDEX])();
#      else
                 CclNmPrepareSleepReqFct();
#      endif

               }
               else
               {
                 /* set CCL state to prepare sleep */
                 cclNmState[CCL_CHANNEL_CCLINDEX] = kCclNmStateGoToSleep;
               }

#      if defined(CCL_NM_TYPE_NONE)
#        if(kCclNrOfChannels > 1)
          
               if((cclChannelWithoutNm & (vuint8)((vuint8)1 << (CCL_CHANNEL_CCLINDEX))) != kCclChWithNm )
#        endif
               {
                 ApplCclNmStateChange(CCL_CHANNEL_CCLPARA_FIRST cclNmStateTmp[CCL_CHANNEL_CCLINDEX], kCclNmStateGoToSleep);
               }
#      endif

#      if defined(CCL_ENABLE_SLEEP_REPETITION)
               /* stop sleep repetition handling */
               cclCanSleepRepetition[CCL_CHANNEL_CCLINDEX] = kCclNoRepeatCanSleep;
#      endif

#      if defined(CCL_ENABLE_MIN_NM_ACTIVATION_TIME) /* ESCAN00021604 */
               if (cclMinNmActivationTimerValue[CCL_CHANNEL_CCLINDEX] != kCclNmActTimerStopped)
               {
                 (void)CclRequestCommunication(CCL_CHANNEL_CCLINDEX);
                   
                 cclMinNmActivationTimer[CCL_CHANNEL_CCLINDEX] = cclMinNmActivationTimerValue[CCL_CHANNEL_CCLINDEX] + 1; /* plus 1 because timer is decremented in same cycle */
               }
#      endif

             }
             /* clear external CAN channel request flag */
             cclExtCanWakeUpReq[CCL_CHANNEL_CCLINDEX] = kCclNoExtChWupReq;
           }
         }
/* ===================================================================== */
/* = end "external channel request handling" =========================== */
/* ===================================================================== */

#    if defined(CCL_ENABLE_MIN_NM_ACTIVATION_TIME) /* ESCAN00021604 */
/* ===================================================================== */
/* = begin "NM activation timer handling" ============================== */
/* ===================================================================== */
         /* timer is activated? */
         if(cclMinNmActivationTimer[CCL_CHANNEL_CCLINDEX] != kCclNmActTimerStopped)
         {
           /* decrement timer */
           cclMinNmActivationTimer[CCL_CHANNEL_CCLINDEX]--;

           /* timer is expired? */
           if(cclMinNmActivationTimer[CCL_CHANNEL_CCLINDEX] == kCclNmActTimerStopped)
           {
             /* release communication request of the CCL system user */
             CclReleaseCommunication(CCL_CHANNEL_CCLINDEX);
            }
         }
/* ===================================================================== */
/* = end   "NM activation timer handling" ============================== */
/* ===================================================================== */
#    endif

#    if defined (CCL_ENABLE_EMC_WAKEUP)
/* ===================================================================== */
/* = begin "EMC wake up timeout handling" ============================== */
/* ===================================================================== */
         /* EMC wake up timer is active? */         
         if(cclEmcWakeUpActive[CCL_CHANNEL_CCLINDEX] < kCclEmcWakeUpTimerDeactive)
         {
           /* EMC wake up timer is running */
           if(cclEmcWakeUpTimer[CCL_CHANNEL_CCLINDEX] > kCclEmcWakeUpTimerStopped)
           {
             /* decrement EMC wake up timer */
             cclEmcWakeUpTimer[CCL_CHANNEL_CCLINDEX]--;
           }
           else
           {
             /* EMC wake up timer is expired */
             cclEmcWakeUpExp[CCL_CHANNEL_CCLINDEX] = kCclEmcWakeUpTimerExpired;
           }

           /* EMC wake up timer is expired? */
           if(cclEmcWakeUpExp[CCL_CHANNEL_CCLINDEX] < kCclEmcWakeUpTimerRunning)
           {
             /* set CAN communication (HW and SW) to SLEEP */
             CclCanStandby(CCL_CHANNEL_CCLPARA_ONLY);
             /* deactive the EMC wake up timer */
             cclEmcWakeUpActive[CCL_CHANNEL_CCLINDEX] = kCclEmcWakeUpTimerDeactive;
             cclEmcWakeUpExp[CCL_CHANNEL_CCLINDEX] = kCclEmcWakeUpTimerDeactive;
           }
         }
#      if defined( CCL_ENABLE_DEBUG)
         if(cclEmcWakeUpActive[CCL_CHANNEL_CCLINDEX] == kCclEmcWakeUpTimerDeactive)
         {
           CclAssert(cclEmcWakeUpTimer[CCL_CHANNEL_CCLINDEX] == kCclEmcWakeUpTimerStopped, kCclErrEMCTimerHdlgFailed)
         }
         if(cclEmcWakeUpActive[CCL_CHANNEL_CCLINDEX] == kCclEmcWakeUpTimerDeactive)
         {
           CclAssert(cclEmcWakeUpExp[CCL_CHANNEL_CCLINDEX] == kCclEmcWakeUpTimerDeactive , kCclErrEMCTimerHdlgFailed)
         }
#      endif
/* ===================================================================== */
/* = end "EMC wake up timeout handling" ================================ */
/* ===================================================================== */
#    endif
#    if defined(CCL_ENABLE_SLEEP_REPETITION)
/* ===================================================================== */
/* = begin "sleep repetition handling" =================================== */
/* ===================================================================== */
         /* check sleep repetition handling */
         if(cclCanSleepRepetition[CCL_CHANNEL_CCLINDEX] != kCclNoRepeatCanSleep)
         {
           /* sleep repetition is active,
            * set CAN communication (HW and SW) to SLEEP
            */
           CclCanStandby(CCL_CHANNEL_CCLPARA_ONLY);
         }
/* ===================================================================== */
/* = end "sleep repetition handling" =================================== */
/* ===================================================================== */
#    endif

#  endif

#  if defined ( CCL_ENABLE_MISSING_ACK_HANDLING )
/* ===================================================================== */
/* = begin "Missing ACK handling" ====================================== */
/* ===================================================================== */
         if( cclMissingAckTimer[CCL_CHANNEL_CCLINDEX] != 0u )
         {
           /* Check if missing ACK handling can be performed */
           if( /* Missing Ack Handling is enabled */
               ( cclMissingAckEnabled[CCL_CHANNEL_CCLINDEX] ) &&
               /* and No BusOff recovery is running */
               ( cclBusOffFlag[CCL_CHANNEL_CCLINDEX] == kCclBusOffRecNotActive ) &&
               /* and CAN is online or offline due to Tpause after missing ACK was detected */
               ( ( CanIsOnline( CanGetStatus( CCL_CHANNEL_CANPARA_ONLY ) ) ) || ( cclMissingAckTxStopped[CCL_CHANNEL_CCLINDEX] ) ) )
           {
             {
               cclMissingAckTimer[CCL_CHANNEL_CCLINDEX]--;
               if( cclMissingAckTimer[CCL_CHANNEL_CCLINDEX] == 0u )
               {
                 if( !cclMissingAckTxStopped[CCL_CHANNEL_CCLINDEX] )
                 {
                   /* Re-Init CAN */
                   CclCanOffline( CCL_CHANNEL_CCLPARA_ONLY );
                   CanInit( CCL_CHANNEL_CANPARA_FIRST 0u );

                   /* Start Tpause timer */
                   if( cclMissingAckPauseTimeoutValue[CCL_CHANNEL_CCLINDEX] > 0 )
                   {
                     cclMissingAckTxStopped[CCL_CHANNEL_CCLINDEX] = 1u;
                     cclMissingAckTimer[CCL_CHANNEL_CCLINDEX] = cclMissingAckPauseTimeoutValue[CCL_CHANNEL_CCLINDEX];
                   }
                   else
                   {
                     /* Tpause is 0ms -> Restart transmission immediately */
                     CclCanOnline( CCL_CHANNEL_CCLPARA_ONLY );
                   }
                 }
                 else
                 {
                   cclMissingAckTxStopped[CCL_CHANNEL_CCLINDEX] = 0u;
                   /* Restart transmission */
                   CclCanOnline( CCL_CHANNEL_CCLPARA_ONLY );
                 }
               }
             }
           }
           else
           {
             /* Missing ACK handling is not performed.
              * Reset timer so that timer can be restarted when First message is transmitted after Missing ACK handling is active again. */
             cclMissingAckTimer[CCL_CHANNEL_CCLINDEX] = 0u;
             cclMissingAckTxStopped[CCL_CHANNEL_CCLINDEX] = 0u;
           }
         }
/* ===================================================================== */
/* = end "Missing ACK handling" ======================================== */
/* ===================================================================== */
#  endif

         CanGlobalInterruptRestore();
     }
#  if defined (CCL_ENABLE_MULTIPLE_CONFIG)
    }
#  endif
#  if(kCclNrOfNetworks > 1)
  }
#  endif
}
#endif

/************************************************************************
| NAME:               CclInit
| PROTOTYPE:          void CclInit(CanChannelHandle channel)
|                     or
|                     void CclInit(void)
| CALLED BY:          Application during startup the system or while runtime
| PRECONDITIONS:      -
| INPUT PARAMETERS:   channel (multiple channel)
|                     or
|                     void (single channel)
| RETURN VALUE:       void
| DESCRIPTION:        channel specific initialisation of CCL and CANbedded stack
|*************************************************************************/
#if defined(CCL_ENABLE_EXTENDED_NMINIT) /* ESCAN00021604 */
void CCL_API_CALL_TYPE CclInit(CCL_CHANNEL_CCLTYPE_FIRST CCL_NM_INITPOINTER_TYPE)
#else
void CCL_API_CALL_TYPE CclInit(CCL_CHANNEL_CCLTYPE_ONLY)
#endif
 {

#if defined( CCL_ENABLE_INTERNAL_REQUEST)
   vuint8 count;
#endif

#if (kCclNrOfChannels > 1 )
  CclAssert(channel < kCclNrOfChannels ,kCclWrongChannelHandle)
#endif

#if defined( CCL_ENABLE_ERROR_HOOK)
   cclChannelNumber = 0; /* init channel number */
   cclErrorCode     = 0; /* init error code */
   cclErrorLine     = 0; /* init error line */
   cclComponentID   = 0; /* init component ID */
#endif

#if defined( CCL_ENABLE_EXTERNAL_REQUEST )
   /* clear the external CAN channel request flag */
   cclExtCanWakeUpReq[CCL_CHANNEL_CCLINDEX] = kCclNoExtChWupReq; /* PRQA S 3689 */ /*lint !e661*/

#    if defined CCL_ENABLE_SLEEP_REPETITION
   /* deactivate sleep repetition */
   cclCanSleepRepetition[CCL_CHANNEL_CCLINDEX] = kCclNoRepeatCanSleep; /* PRQA S 3689 */ /*lint !e661*/
#    endif
   /* set the default value kCanOk of the CanSleep return value */
   cclCanSleepReturnCode[CCL_CHANNEL_CCLINDEX] = kCanOk; /* PRQA S 3689 */ /*lint !e661*/
#endif

#if defined( CCL_ENABLE_SW_COM_STATE )
   /* disable communication SW state */
   cclComSwState[CCL_CHANNEL_CCLINDEX] = kCclComSwOff; /* PRQA S 3689 */ /*lint !e661*/
#endif

#if defined (NMHDLAN_NM_TYPE)
   cclNmCommunicationState[CCL_CHANNEL_CCLINDEX] = kCclNmCommunicationSuspended; /* PRQA S 3689 */ /*lint !e661*/
#endif

#if defined (CCL_ENABLE_MULTIPLE_CONFIG)
   if((cclIdChMap[V_ACTIVE_IDENTITY_LOG] & (vuint8)((vuint8)1 << (CCL_CHANNEL_CCLINDEX))) > 0x00)
   {
#endif

#if defined (CCL_ENABLE_EMC_WAKEUP)
     /* clear external EMC channel request */
     cclExtEmcWakeUpReq[CCL_CHANNEL_CCLINDEX] = kCclNoExtChWupReq; /* PRQA S 3689 */ /*lint !e661*/

#  if(kCclNrOfChannels > 1)
     /* check wake up / sleep support */
     if ((cclNmWakeUpAble & (vuint8)((vuint8)1 << (CCL_CHANNEL_CCLINDEX))) != kCclNoWakeUpAble)
#  endif
     {
       /* start EMC wake up timer */
       cclEmcWakeUpTimer[CCL_CHANNEL_CCLINDEX] = kCclEmcWakeUpTime; /* PRQA S 3689 */ /*lint !e661*/
       cclEmcWakeUpActive[CCL_CHANNEL_CCLINDEX] = kCclEmcWakeUpTimerActive; /* PRQA S 3689 */ /*lint !e661*/
       cclEmcWakeUpExp[CCL_CHANNEL_CCLINDEX] = kCclEmcWakeUpTimerRunning; /* PRQA S 3689 */ /*lint !e661*/
     }
#  if(kCclNrOfChannels > 1)
     else
     {
       /* do not start EMC wake up timer on non-wakeable channels */
       cclEmcWakeUpTimer[CCL_CHANNEL_CCLINDEX] = kCclEmcWakeUpTimerStopped; /* PRQA S 3689 */ /*lint !e661*/
       cclEmcWakeUpActive[CCL_CHANNEL_CCLINDEX] = kCclEmcWakeUpTimerDeactive; /* PRQA S 3689 */ /*lint !e661*/
       cclEmcWakeUpExp[CCL_CHANNEL_CCLINDEX] = kCclEmcWakeUpTimerDeactive; /* PRQA S 3689 */ /*lint !e661*/
     }
#  endif
#endif

#  if defined( CCL_ENABLE_EMC_WAKEUP )
#    if(kCclNrOfChannels > 1)
     /* check wake up / sleep support */
     if ((cclNmWakeUpAble & (vuint8)((vuint8)1 << (CCL_CHANNEL_CCLINDEX))) != kCclNoWakeUpAble)
#    endif
     {
       /* If EMC wake up is enabled, Ccl must be initialized to sleep state, since NM callback (which
          normally sets state to sleep) is not executed in this case, see ESCAN00091878 */
       cclNmState[CCL_CHANNEL_CCLINDEX] = kCclNmStateSleep; /* PRQA S 3689 */ /*lint !e661*/
     }
#    if(kCclNrOfChannels > 1)
     else
     {
       /* For non-wakeable channels Ccl is initialized to active state because EMC wake up handling
          is not started on initialization */
       cclNmState[CCL_CHANNEL_CCLINDEX] = kCclNmStateActive; /* PRQA S 3689 */ /*lint !e661*/
     }
#    endif
#  else
     cclNmState[CCL_CHANNEL_CCLINDEX] = kCclNmStateActive; /* PRQA S 3689 */ /*lint !e661*/
#  endif
     
     /* enable communication HW state */
     cclComHwState[CCL_CHANNEL_CCLINDEX] = kCclComHwEnabled; /* PRQA S 3689 */ /*lint !e661*/

     /* set CCL bus state to on */
     cclBusState[CCL_CHANNEL_CCLINDEX] = kCclBusOn; /* PRQA S 3689 */ /*lint !e661*/

#if defined(C_ENABLE_APPLCANPREWAKEUP_FCT)
     cclBusTrcvState[CCL_CHANNEL_CCLINDEX] = kCclBusOn; /* ESCAN00057750 */ /* PRQA S 3689 */ /*lint !e661*/
#endif

#if defined (CCL_ENABLE_MULTIPLE_CONFIG)
   }
   else
   {

#  if defined (CCL_ENABLE_EMC_WAKEUP)
     /* clear external EMC channel request */
      cclExtEmcWakeUpReq[CCL_CHANNEL_CCLINDEX] = kCclNoExtChWupReq; /* PRQA S 3689 */ /*lint !e661*/
     /* stop EMC wake up timer */
     cclEmcWakeUpTimer[CCL_CHANNEL_CCLINDEX] = kCclEmcWakeUpTimerStopped; /* PRQA S 3689 */ /*lint !e661*/
     cclEmcWakeUpActive[CCL_CHANNEL_CCLINDEX]    = kCclEmcWakeUpTimerDeactive; /* PRQA S 3689 */ /*lint !e661*/
     cclEmcWakeUpExp[CCL_CHANNEL_CCLINDEX]       = kCclEmcWakeUpTimerDeactive; /* PRQA S 3689 */ /*lint !e661*/
#  endif

     /* set CCL state to sleep */
     cclNmState[CCL_CHANNEL_CCLINDEX] = kCclNmStateSleep; /* PRQA S 3689 */ /*lint !e661*/

     /* disable communication HW state */
     cclComHwState[CCL_CHANNEL_CCLINDEX] = kCclComHwDisabled; /* PRQA S 3689 */ /*lint !e661*/

     /* set CCL bus state to of */
     cclBusState[CCL_CHANNEL_CCLINDEX] = kCclBusOff; /* PRQA S 3689 */ /*lint !e661*/

#  if defined(C_ENABLE_APPLCANPREWAKEUP_FCT)
     cclBusTrcvState[CCL_CHANNEL_CCLINDEX] = kCclBusOff; /* ESCAN00057750 */ /* PRQA S 3689 */ /*lint !e661*/
#  endif

   }
#endif

#if defined( CCL_ENABLE_INTERNAL_REQUEST )

   {
     {
       for(count=cclStartIndex[CCL_NET_CCLINDEX]; count<=cclStopIndex[CCL_NET_CCLINDEX]; count++) /* PRQA S 3689 */ /*lint !e661*/
       {
         /* clear communication request field */
         cclIntNetState[count] = 0x00;
       }

       /* clear internal network request flag */
       cclIntNetReq[CCL_NET_CCLINDEX] = kCclNoIntNetReq; /* PRQA S 3689 */ /*lint !e661*/

       /* clear internal network release flag */
       cclIntNetRel[CCL_NET_CCLINDEX] = kCclNoIntNetRel; /* PRQA S 3689 */ /*lint !e661*/

       /* clear internal network release history flag */
       cclIntNetRelHistory[CCL_NET_CCLINDEX] = kCclNoIntNetRel; /* PRQA S 3689 */ /*lint !e661*/
     }
   }

#endif

#if ( ( defined( VGEN_ENABLE_IF_ASRIFCAN ) && defined( CCL_NM_TYPE_NMJUNIOR ) ) \
      || ( defined( CCL_ENABLE_MISSING_ACK_HANDLING ) ) )
   cclBusOffFlag[CCL_CHANNEL_CCLINDEX] = kCclBusOffRecNotActive;
#endif

#if defined ( CCL_ENABLE_MISSING_ACK_HANDLING )
  cclMissingAckTimer[CCL_CHANNEL_CCLINDEX] = 0u;
  cclMissingAckTxStopped[CCL_CHANNEL_CCLINDEX] = 0u;
  cclMissingAckEnabled[CCL_CHANNEL_CCLINDEX] = 1u;
#endif

#if defined(CCL_ENABLE_EXTENDED_NMINIT) /* ESCAN00021604 */
#  if ( (defined CCL_ENABLE_MIN_NM_ACTIVATION_TIME ) ) /* ESCAN00022670 */
#    if (kCclNrOfChannels > 1)  
  switch (CCL_CHANNEL_CCLINDEX)
  {
    case 0:
#    endif
      CclValidateNmInitValue( CCL_CHANNEL_CCLPARA_FIRST cclNmInitPointer->cclNmInit_0 );

#    if (kCclNrOfChannels > 1)
      break;

    case 1:
      CclValidateNmInitValue( CCL_CHANNEL_CCLPARA_FIRST cclNmInitPointer->cclNmInit_1 );
      break;
#    endif

#    if (kCclNrOfChannels > 2)
    case 2:
      CclValidateNmInitValue( CCL_CHANNEL_CCLPARA_FIRST cclNmInitPointer->cclNmInit_2 );
      break;
#    endif

#    if (kCclNrOfChannels > 3)
    case 3:
      CclValidateNmInitValue( CCL_CHANNEL_CCLPARA_FIRST cclNmInitPointer->cclNmInit_3 );
      break;
#    endif

#    if (kCclNrOfChannels > 4)
    case 4:
      CclValidateNmInitValue( CCL_CHANNEL_CCLPARA_FIRST cclNmInitPointer->cclNmInit_4 );
      break;
#    endif

#    if (kCclNrOfChannels > 5)
    case 5:
      CclValidateNmInitValue( CCL_CHANNEL_CCLPARA_FIRST cclNmInitPointer->cclNmInit_5 );
       break;
#    endif

#    if (kCclNrOfChannels > 6)
    case 6:
     CclValidateNmInitValue( CCL_CHANNEL_CCLPARA_FIRST cclNmInitPointer->cclNmInit_6 );
      break;
#    endif

#    if (kCclNrOfChannels > 7)
    case 7:
      CclValidateNmInitValue( CCL_CHANNEL_CCLPARA_FIRST cclNmInitPointer->cclNmInit_7 );
      break;
#    endif

#    if (kCclNrOfChannels > 1) 
       default:
         break;
      }
#    endif
#  endif
#endif

#  if( CCL_DLL_VERSION < 0x0106 )
#  else
   /* check initialisation type flag */
#    if defined( CCL_ENABLE_CANBEDDED_HANDLING )
   if(cclStackInit == kCclChannelSpecificInit)
   {
     /* re-initialisation is active */
     /* call container function for CANbedded re-initialisation */
#      if(kCclNrOfChannels > 1)
     /* By using the following table of function calls, code-doubled functions 
     * are called from the indexed CCL. This is done to simplify the called 
     * functions (no distinction of the parameter 'channel' is necessary). */
     (CclInitFctTbl[CCL_CHANNEL_CCLINDEX])(CCL_NM_INITPOINTER_PARA); /* PRQA S 3689 */ /*lint !e661*/
#      else
     CclInitFct(CCL_NM_INITPOINTER_PARA);
#      endif
   }
#    endif
#  endif
 }

/************************************************************************
| NAME:               CclInitPowerOn
| CALLED BY:          Application during startup the system or while runtime
| PRECONDITIONS:      global interrupts have to be disabled
| RETURN VALUE:       void
| DESCRIPTION:        system specific initialisation of CCL and CANbedded stack
|*************************************************************************/
#if defined(CCL_ENABLE_EXTENDED_NMINIT) /* ESCAN00021604 */
void CCL_API_CALL_TYPE CclInitPowerOn(CCL_ECUS_NODESTYPE_FIRST CCL_NM_INITPOINTER_TYPE)
#else
 void CCL_API_CALL_TYPE CclInitPowerOn(CCL_ECUS_NODESTYPE_ONLY)
#endif
{
#if(kCclNrOfChannels > 1)
#    if defined (VGEN_ENABLE_IF_ASRIFCAN)
   uint8 channel;
#    else
   CanChannelHandle channel;
#    endif
#endif

#  if( CCL_DLL_VERSION < 0x0106 )
#  else
#    if defined( CCL_ENABLE_CANBEDDED_HANDLING ) 
   /* clear repeated initialisation flag */
   cclStackInit = kCclSystemSpecificInit;
#    endif
#  endif

#if defined(CCL_ENABLE_EXTENDED_NMINIT) /* ESCAN00021604 */
#  if(kCclNrOfChannels > 1)
   /* initialize channel variable, needed for assertion */
   channel = (CanChannelHandle)0;
#  endif
   /* check NM initialization pointer: */
   CclAssert(cclNmInitPointer != V_NULL, kCclErrNullPointer)

#endif   

#if defined( CCL_ENABLE_CANBEDDED_HANDLING )
#  if defined(CCL_ENABLE_MULTIPLE_CONFIG)
   /* set active identity */
   VSetActiveIdentity(CCL_ECUS_NODESPARA_ONLY)
#  endif
#endif

#if(kCclNrOfChannels > 1)
   /* init channel parameters */
   for(channel=0; channel<(CanChannelHandle)kCclNrOfChannels; channel++)
#endif
   {
     /* initialize the transceiver ports */
     CclInitPorts(CCL_CHANNEL_CCLPARA_ONLY);

     /* inititialize the communication control layer */
#if defined(CCL_ENABLE_EXTENDED_NMINIT) /* ESCAN00021604 */
     CclInit(CCL_CHANNEL_CCLPARA_FIRST CCL_NM_INITPOINTER_PARA); /* ESCAN00021604 */
#else  /* ESCAN00021870 */
     CclInit(CCL_CHANNEL_CCLPARA_ONLY);
#endif

   }

#if defined( CCL_ENABLE_CANBEDDED_HANDLING )
#  if defined(CCL_ENABLE_MULTIPLE_NODES)
#    if defined(VGEN_GENY)
   /* set active identity */
   VSetActiveIdentity(CCL_ECUS_NODESPARA_ONLY); /* PRQA S 3109 */ /* MD_CBD_14.3 */
#    else
   /* set common multiple ECU handle for CAN modules */
   ComSetCurrentECU(CCL_ECUS_NODESPARA_ONLY);
#    endif
#  endif

   /* container function for CANbedded component initialization */
   CclInitPowerOnFct(CCL_NM_INITPOINTER_PARA);
#endif

#if defined( CCL_ENABLE_TRCV_PORT_INT )
   CclAssert(cclNmWakeUpAble!=0,kExtAndIntWakeUp)
#endif

#  if( CCL_DLL_VERSION < 0x0106 )
#  else
#    if defined( CCL_ENABLE_CANBEDDED_HANDLING ) 
   /* set repeated initialisation flag */
   cclStackInit = kCclChannelSpecificInit;
#    endif
#  endif

 }

#if defined(CCL_ENABLE_EXTENDED_NMINIT) /* ESCAN00021604 */
#  if ( (defined CCL_ENABLE_MIN_NM_ACTIVATION_TIME ) ) /* ESCAN00022670 */
/************************************************************************
| NAME:               CclValidateNmInitValue
| CALLED BY:          CCL
| PRECONDITIONS:
| INPUT PARAMETERS:   CAN channel, NM initialization parameter value
| RETURN VALUE:       void
| DESCRIPTION:        validate init pointer and set NM Osek activation timer
|*************************************************************************/
static void CclValidateNmInitValue( CCL_CHANNEL_CCLTYPE_FIRST tCclNmInitParaType nmInitValue)
{

#    if defined (CCL_ENABLE_MIN_NM_ACTIVATION_TIME)
  cclMinNmActivationTimer[CCL_CHANNEL_CCLINDEX] = kCclNmActTimerStopped;
#    endif

#    if ( defined (CCL_ENABLE_MIN_NM_ACTIVATION_TIME) ) 
  if (cclNmType[CCL_CHANNEL_CCLINDEX] == kComponentNm)
  {
    /* NM Osek part: if init value is normal set the activation timer, otherwise leave timer value */
    if (nmInitValue == kCclNmInitNormal)
    {
#      if defined (CCL_ENABLE_MIN_NM_ACTIVATION_TIME)
      cclMinNmActivationTimer[CCL_CHANNEL_CCLINDEX] = cclMinNmActivationTimerValue[CCL_CHANNEL_CCLINDEX];
#      endif

#      if defined( CCL_ENABLE_EMC_WAKEUP )
      /* If EMC wake up is enabled and NmDirOsek is initialized to normal,
         Ccl state must be set to state active, see ESCAN00091878 */
      cclNmState[CCL_CHANNEL_CCLINDEX] = kCclNmStateActive;
#      endif

      /* set system user request for this channel: */
      (void)CclRequestCommunication(CCL_CHANNEL_CCLINDEX);
    }
  }
#    endif
}
#  endif
#endif

#if defined(CCL_ENABLE_SYSTEM_SHUTDOWN)
/************************************************************************
| NAME:               CclSystemShutdown
| PROTOTYPE:          void CclSystemShutdown(void)
| CALLED BY:          Application
| PRECONDITIONS:      This function has to be called with disabled global
|                     interrupts.
| INPUT PARAMETERS:   void
| RETURN VALUE:       void
| DESCRIPTION:        shutdown handling of CANbedded stack
|*************************************************************************/
void CCL_API_CALL_TYPE CclSystemShutdown(void)
 {

#  if(kCclNrOfChannels > 1)
   CanChannelHandle channel;
#  endif

#  if(kCclNrOfChannels > 1)
   /* init channel parameters */
   for(channel=0; channel<(CanChannelHandle)kCclNrOfChannels; channel++)
#  endif
   {
#  if defined(CCL_ENABLE_MULTIPLE_CONFIG)
     if((cclIdChMap[V_ACTIVE_IDENTITY_LOG] & (vuint8)((vuint8)1 << (CCL_CHANNEL_CCLINDEX))) > 0x00)
     {
#  endif
     /* By using the following table of function calls, code-doubled functions 
     * are called from the indexed CCL. This is done to simplify the called 
     * functions (no distinction of the parameter 'channel' is necessary). */
#  if(kCclNrOfChannels > 1)
       /* system shutdown notification */
       (CclSystemShutdownFctTbl[CCL_CHANNEL_CCLINDEX])();
#  endif
#  if defined(CCL_ENABLE_MULTIPLE_CONFIG)
     }
#  endif
   }
#  if(kCclNrOfChannels > 1)
#  else

     CclSystemShutdownFct();
#  endif

 }
#endif

#if defined(CCL_ENABLE_ERROR_PIN)
/************************************************************************
| NAME:               CclGetErrorPort
| PROTOTYPE:          vuint8 CclGetErrorPort(CanChannelHandle channel)
|                     or
|                     vuint8 CclGetErrorPort(void)
| CALLED BY:          Application
| PRECONDITIONS:
| INPUT PARAMETERS:   channel (multiple channel)
|                     or
|                     void (single channel)
| RETURN VALUE:       state of transceiver error port
| DESCRIPTION:        returns the current transceiver error port state
|*************************************************************************/
vuint8 CCL_API_CALL_TYPE CclGetErrorPort(CCL_CHANNEL_CCLTYPE_ONLY)
 {
   /* get transceiver error port value */
#if(kCclNrOfChannels > 1)
   /* By using the following table of function calls, code-doubled functions 
   * are called from the indexed CCL. This is done to simplify the called 
   * functions (no distinction of the parameter 'channel' is necessary). */
   if(CclGetTrcvErrorPortFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
   {
     return (CclGetTrcvErrorPortFctTbl[CCL_CHANNEL_CCLINDEX])();
   }
   else
   {
     /* no transceiver error port information available */
     return kCclNoErrPort;
   }
#  else
   return CclGetTrcvErrorPortFct();
#  endif
 }
#endif

/************************************************************************
| NAME:               CclGetChannelState
| PROTOTYPE:          vuint8 CclGetChannelState(CanChannelHandle channel)
|                     or
|                     vuint8 CclGetChannelState(void)
| CALLED BY:          Application
| PRECONDITIONS:
| INPUT PARAMETERS:   channel (multiple channel)
|                     or
|                     void (single channel)
| RETURN VALUE:       kCclNmStateSleep, sleep state 
|                     kCclNmStateGoToSleep, prepare sleep state
|                     kCclNmStateActive, normal state
|                     kCclNmPowerFail, power fail state
| DESCRIPTION:        returns the current CCL state
|*************************************************************************/
vuint8 CCL_API_CALL_TYPE CclGetChannelState(CCL_CHANNEL_CCLTYPE_ONLY)
{
  return cclNmState[CCL_CHANNEL_CCLINDEX];
}

#if (defined(CCL_ENABLE_EXTERNAL_REQUEST) &&\
     defined(CCL_ENABLE_TRCV_PORT_INT))
/************************************************************************
| NAME:               CclCanWakeUpInt
| PROTOTYPE:          void CclCanWakeUpInt(CanChannelHandle channel)
|                     or
|                     void CclCanWakeUpInt(void)
| CALLED BY:          application wakeup-ISR
| PRECONDITIONS:      external wakeup port INT via RX/INH of CAN transceiver
| INPUT PARAMETERS:   channel (multiple channel)
|                     or
|                     void (single channel)
| RETURN VALUE:       void
| DESCRIPTION:        disable the external wakeup port INT and notify CCL
|                     the wakeup event
|*************************************************************************/
void CCL_API_CALL_TYPE CclCanWakeUpInt(CCL_CHANNEL_CCLTYPE_ONLY)
{
   CclAssert(cclWakeUpIntState[CCL_CHANNEL_CCLINDEX]==kCclDisablePortIRQ, kAssertNotSleepAndTRCVINTactive)

   /* disable port interrupt */
#  if (kCclNrOfChannels > 1)
   /* By using the following table of function calls, code-doubled functions 
   * are called from the indexed CCL. This is done to simplify the called 
   * functions (no distinction of the parameter 'channel' is necessary). */
   if(CclDisableTrcvIntFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
   {
     (CclDisableTrcvIntFctTbl[CCL_CHANNEL_CCLINDEX])();
   }
#  else
   CclDisableTrcvIntFct();
#  endif

   /* set INT state to "disable" */
   cclWakeUpIntState[CCL_CHANNEL_CCLINDEX] = kCclDisableWakeUpInt;

#  if defined (VGEN_ENABLE_IF_ASRIFCAN)
   CclWakeUp(CCL_CHANNEL_CCLPARA_ONLY);
#  else
   ApplCanWakeUp(CCL_CHANNEL_CANPARA_ONLY);
#  endif
}
#endif

#if defined( CCL_ENABLE_INTERNAL_REQUEST )
#  if defined( CCL_ENABLE_COM_REQ_HANDLING_API )
/************************************************************************
| NAME:               CclRequestCommunication
| PROTOTYPE:          vuint8 CCL_API_CALL_TYPE CclRequestCommunication(vuint8 cclComHandle)
| CALLED BY:          Application
| PRECONDITIONS:
| INPUT PARAMETERS:   cclComHandle: communication request handle
| RETURN VALUE:       kCclReqOk: the communication request is set correctly
|                     kCclReqFailed: the communication request is stored but
|                                    not handeled
| DESCRIPTION:        request the communication on the CAN channels which
|                     are configured for the cclComHandle
|*************************************************************************/
vuint8 CCL_API_CALL_TYPE CclRequestCommunication(vuint8 cclComHandle)
{
  vuint8 intNetState;
#      if(kCclNetReqTableSize > 1)
  vuint8 index;
#      endif

  vuint8 channel;
  vuint8 retValue;

  /* ESCAN00010661 
   *  Disable the global interrupt to guarantee data consistency 
   *  if this function is called from interrupt insted of task level. */
  CanGlobalInterruptDisable();
 
  /* set the return value to ok */
  retValue = kCclReqOk;

#    if defined( CCL_ENABLE_DEBUG)
#      if ( kCclNrOfSystemChannels > 1 )
#        if ( kCclNrOfChannels > 1 )
  /* assignment needed because variable "channel" is used in CclAssert() macro */
  channel = 0;
#        endif
#      endif
#    endif

  /* check for valid communication handle */
  CclAssert( (cclComHandle < kCclNumberOfUser), kCclErrInvalidComHandle)

  channel = cclUserChannel[cclComHandle]; /* PRQA S 3689 */ /*lint !e661*/

#    if defined (CCL_ENABLE_MULTIPLE_CONFIG)
  CclAssert( (cclIdChMap[V_ACTIVE_IDENTITY_LOG] & (vuint8)((vuint8)1 << (channel))) > (vuint8)0x00, kCclWrongChannelHandle)
  
  if((cclIdChMap[V_ACTIVE_IDENTITY_LOG] & (vuint8)((vuint8)1 << (channel))) > 0x00)
  {
#    endif

#    if defined (CCL_ENABLE_NMPASSIVE_MODE) /* ESCAN00023408 */
  /* check for valid NM mode */
  CclAssert( (cclNmPassiveMode[channel] == kCclNmActiveMode ), kCclErrInvalidNmMode)
  
  if( cclNmPassiveMode[channel] == kCclNmActiveMode )
  {
#    endif
  
#      if(kCclNetReqTableSize > 1)
    intNetState = 0;
#      endif

    {
        /* the communication request is set the first time for the communication handle,
         * calculate if the request the first for this CAN channel
         */

#    if(kCclNetReqTableSize > 1)
          for(index=cclStartIndex[CCL_NET_CCLINDEX]; index<=cclStopIndex[CCL_NET_CCLINDEX]; index++)
          {
            intNetState |= cclIntNetState[index];
          }
#    else
          intNetState = cclIntNetState[0];
#    endif

          if((cclIntNetState[cclUserOffset[cclComHandle]] & cclUserMask[cclComHandle]) == 0) /* PRQA S 3689 */ /*lint !e661*/
          {
            /* store the communication request for this handle */
            cclIntNetState[cclUserOffset[cclComHandle]] |= cclUserMask[cclComHandle]; /* PRQA S 3689 */ /*lint !e661*/
            if( intNetState == kCclNoNetRequest )
            {
              /* the communication request is the first for this CAN channel */
              if(cclNmState[channel] == kCclNmStateSleep)
              {
                /* the CCL is in sleep */
                {
                  /* the communication request rrestriction is deactive */
#      if defined(CCL_ENABLE_TRCV_PORT_INT)
                  /* disable transceiver port interrupt */
#        if(kCclNrOfChannels > 1)
                  /* By using the following table of function calls, code-doubled functions 
                   * are called from the indexed CCL. This is done to simplify the called 
                   * functions (no distinction of the parameter 'channel' is necessary). */
                  if(CclDisableTrcvIntFctTbl[channel] != V_NULL)
                  {
                    (CclDisableTrcvIntFctTbl[channel])();
                  }
#        else
                  CclDisableTrcvIntFct();
#        endif
                  /* set the port interrupt state to deactive */
                  cclWakeUpIntState[channel] = kCclDisableWakeUpInt;
#      endif

#      if defined( CCL_USE_REQUEST_SETINTCOM_FCT )
                  /* inform the application about the first communication request */
#        if ( kCclNrOfChannels > 1 )
                  if (CclIntComReqFctTbl[channel] != V_NULL)
                  {
                    /* By using the following table of function calls, code-doubled functions 
                     * are called from the indexed CCL. This is done to simplify the called 
                     * functions (no distinction of the parameter 'channel' is necessary). */
                    (CclIntComReqFctTbl[channel])();
                  }
#        else
                  CclIntComReqFct();
#        endif
#    endif
#    if defined(VGEN_ENABLE_ECUM_SMSVE)
                  /* CCL is in sleep: check if RUN state of the ECU Manager is not yet requested (e.g. from an external wake up event before): */
                  if( EcuM_ComM_HasRequestedRUN(CCL_CHANNEL_CCLPARA_ONLY) == FALSE )
                  {
                    (void)EcuM_ComM_RequestRUN(CCL_CHANNEL_CCLPARA_ONLY);
                  }
#    endif
                }
              }
              /* clear internal network release flag */
              cclIntNetRel[CCL_NET_CCLINDEX] = kCclNoIntNetReq;
              /* set internal network request flag */
              cclIntNetReq[CCL_NET_CCLINDEX] = CCL_CHANNEL_CCLINDEX;
            }
          } /* ESCAN00022602 */

    }

#    if ( defined (CCL_ENABLE_NMPASSIVE_MODE) || defined (CCL_ENABLE_MULTIPLE_CONFIG) )
  }
  else
  {
    retValue = kCclReqFailed;
  }
#    endif
   
   /* ESCAN00010661 
    *  Enable the global interrupt before leaving the function. */   
   CanGlobalInterruptRestore();
     
   return retValue;
}
#  endif

#  if defined( CCL_ENABLE_COM_REQ_HANDLING_API )
/************************************************************************
| NAME:               CclReleaseCommunication
| PROTOTYPE:          void CCL_API_CALL_TYPE CclReleaseCommunication(vuint8 cclComHandle)
| CALLED BY:          Application
| PRECONDITIONS:
| INPUT PARAMETERS:   cclComHandle: communication request handle
| RETURN VALUE:       -
| DESCRIPTION:        release the communication request for CAN channels which
|                     are configured for the cclComHandle
|*************************************************************************/
void CCL_API_CALL_TYPE CclReleaseCommunication(vuint8 cclComHandle)
{
   vuint8 intNetState;
   vuint8 channel;
#    if (kCclNetReqTableSize > 1)
   vuint8 index;
#    endif

#    if defined ( VGEN_ENABLE_IF_ASRIFCAN )
   /* ESCAN00022725 */
   CanIf_ControllerModeType controllerMode;
   CanIf_ControllerModeType expectedControllerMode;
#    endif

/* ESCAN00010661 
   *  Disable the global interrupt to guarantee data consistency 
   *  if this function is called from interrupt insted of task level. */
   CanGlobalInterruptDisable();

#    if(kCclNetReqTableSize > 1)
   intNetState = 0;
#    endif

#    if defined( CCL_ENABLE_DEBUG)
#      if ( kCclNrOfSystemChannels > 1 )
#        if ( kCclNrOfChannels > 1 )
  /* assignment needed because variable "channel" is used in CclAssert() macro */
  channel = 0;
#        endif
#      endif
#    endif

   /* check for valid communication handle */
   CclAssert( (cclComHandle < kCclNumberOfUser), kCclErrInvalidComHandle)

   channel = cclUserChannel[cclComHandle]; /* PRQA S 3689 */ /*lint !e661*/

#    if defined(CCL_ENABLE_MULTIPLE_CONFIG)
   if((cclIdChMap[V_ACTIVE_IDENTITY_LOG] & (vuint8)((vuint8)1 << (CCL_CHANNEL_CCLINDEX))) > 0x00)   
   {
#    endif

#    if defined (CCL_ENABLE_NMPASSIVE_MODE) /* ESCAN00023408 */
   /* check for valid NM mode */
   CclAssert( (cclNmPassiveMode[channel] == kCclNmActiveMode ), kCclErrInvalidNmMode)
  
   if( cclNmPassiveMode[channel] == kCclNmActiveMode )
   {
#    endif
   
         if( (cclIntNetState[cclUserOffset[cclComHandle]] & cclUserMask[cclComHandle]) != kCclNoNetRequest ) /* PRQA S 3689 */ /*lint !e661*/
         {
           /* the communication request of the cclComHandle handle is released the first time,
            * clear communication request for the cclComHandle handle */
           cclIntNetState[cclUserOffset[cclComHandle]] &= (vuint8)(~cclUserMask[cclComHandle]); /* PRQA S 3689 */ /*lint !e661*/

           /* calculate if there are other communication requests pending */
  #    if(kCclNetReqTableSize > 1)
           for(index=cclStartIndex[CCL_NET_CCLINDEX]; index<=cclStopIndex[CCL_NET_CCLINDEX]; index++)
           {
             intNetState |= cclIntNetState[index];
           }
  #    else
           intNetState = cclIntNetState[0];
  #    endif

           if(intNetState == kCclNoNetRequest)
           {
             /* no communication requests are pending for the CAN channel */
               /* communication restriction is deactive,
                * check if an internal request is pending */
               if(cclIntNetReq[CCL_NET_CCLINDEX] == kCclNoIntNetReq)
               {
                 /* no internal network request is pending ,
                  * set the internal release network flag */
                 cclIntNetRel[CCL_NET_CCLINDEX] = channel;

                 /* set internal network release history flag */
                 cclIntNetRelHistory[CCL_NET_CCLINDEX] = channel;
               }
               else
               {
                 /* clear internal network request flag */
                 cclIntNetReq[CCL_NET_CCLINDEX] = kCclNoIntNetReq;

                 /* internal request is pending ,
                   * check the CCL state */
#      if defined(CCL_ENABLE_EXTERNAL_REQUEST)
                 /* and check if no external wake up request is pending: */
                 /* ESCAN00022666 */
                 if((cclNmState[channel] == kCclNmStateSleep) && (cclExtCanWakeUpReq[channel] == kCclNoExtChWupReq))
#      else
                 if(cclNmState[channel] == kCclNmStateSleep)
#      endif
                 {
#      if defined ( VGEN_ENABLE_IF_ASRIFCAN )   
                   if((cclNmWakeUpAble & (vuint8)((vuint8)1 << (CCL_CHANNEL_CCLINDEX))) != kCclNoWakeUpAble )
                   {
                     /* NM wake up able, we are in state sleep and expect the controller to be in sleep mode: */
                     expectedControllerMode = CANIF_CS_SLEEP;
                   }
                   else
                   {
                     /* NM not wake up able, we are in state sleep and expect the controller to be in stop mode: */
                     expectedControllerMode = CANIF_CS_STOPPED;
                   }
                     /* Get the controller mode: */                   
                     (void)CanIf_GetControllerMode(channel, &controllerMode);
                   
                   /* NM with sleep capability: controller must be in sleep mode */
                   if ( controllerMode != expectedControllerMode )
                   {
                     /* Set controller back to sleep/stop mode: */
                     CclCanStandby(CCL_CHANNEL_CCLPARA_ONLY);
                   }
                   else
#      endif
                   {
                     /* inform the application about the state change to sleep */
#      if defined(CCL_USE_REQUEST_CLEARCOM_FCT)
#        if(kCclNrOfChannels > 1)
                     if(CclComRelFctTbl[channel] != V_NULL)
                     {
                       (CclComRelFctTbl[channel])();
                     }
#        else
                      
                     CclComRelFct();
#        endif
#      endif
                   }

#      if defined(VGEN_ENABLE_ECUM_SMSVE)   
                   (void)EcuM_ComM_ReleaseRUN(CCL_CHANNEL_CCLPARA_ONLY);
#      endif

                 }
                  
                 else
                 {
                   if(cclIntNetRelHistory[CCL_NET_CCLINDEX] != kCclNoIntNetRel)
                   {
                     /* ESCAN00020286 */
                     /* internal release network */
                     cclIntNetRel[CCL_NET_CCLINDEX] = channel; /* ESCAN00021188 */
                   }
                 }
               }

#  if defined(CCL_ENABLE_TRCV_PORT_INT)            
               if(cclNmState[channel] == kCclNmStateSleep)
               {
#    if defined(CCL_ENABLE_EXTERNAL_REQUEST)
                 /* clear external CAN network request */
                 if(cclExtCanWakeUpReq[CCL_CHANNEL_CCLINDEX] == kCclNoExtChWupReq)
#    endif
                 {
                   if(cclWakeUpIntState[CCL_CHANNEL_CCLINDEX] == kCclDisableWakeUpInt)
                   {
                     /* enable transceiver port interrupt */
#    if( kCclNrOfChannels > 1 )
                     /* By using the following table of function calls, code-doubled functions 
                      * are called from the indexed CCL. This is done to simplify the called 
                      * functions (no distinction of the parameter 'channel' is necessary). */
            
                     /* Within the following function calls a maybe pending 
                      *  Transceiver interrupt will be cleared! */ 
                     if(CclClearTrcvIntFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
                     {                     
                       (CclClearTrcvIntFctTbl[CCL_CHANNEL_CCLINDEX])();
                     }
                     if(CclEnableTrcvIntFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
                     {
                       (CclEnableTrcvIntFctTbl[CCL_CHANNEL_CCLINDEX])();
                     }
  #      else
                     /* Wtihin the following function calls a maybe pending 
                      *  Transceiver interrupt will be cleared! */
                     CclClearTrcvIntFct();
                     CclEnableTrcvIntFct();
  #      endif

                     /* set INT state to "enable" */
                     cclWakeUpIntState[CCL_CHANNEL_CCLINDEX] = kCclEnableWakeUpInt;

  #      if defined(CCL_ENABLE_TRCV_PORT_EDGE_TRIGGER)
                     /* check transceiver port register */
  #        if( kCclNrOfChannels > 1 )
                     if(CclCheckTrcvIntFctTbl[CCL_CHANNEL_CCLINDEX]() == kCclTrcvWakeIntPending)
                     {
                       /* By using the following table of function calls, code-doubled functions 
                        * are called from the indexed CCL. This is done to simplify the called 
                        * functions (no distinction of the parameter 'channel' is necessary). */

                       /* disable transceiver port interrupt */
                       if(CclDisableTrcvIntFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
                       {
                         (CclDisableTrcvIntFctTbl[CCL_CHANNEL_CCLINDEX])();
                       }
  #        else
                       if(CclCheckTrcvIntFct() == kCclTrcvWakeIntPending)
                       {
                         /* disable transceiver port interrupt */
                         CclDisableTrcvIntFct();
  #        endif
                     
                         /* check INT state */
                         if(cclWakeUpIntState[CCL_CHANNEL_CCLINDEX] == kCclEnableWakeUpInt)
                         {
                           /* external EMC/CAN wake up notification */
                           CclCanWakeUpInt(CCL_CHANNEL_CCLPARA_ONLY);
                         }
                       }
  #      endif
                     }
                   }
                 }
  #    endif
               /* clear internal network request flag */
               cclIntNetReq[CCL_NET_CCLINDEX] = kCclNoIntNetReq; /* ESCAN00011503 */
           }
         }
#    if defined (CCL_ENABLE_NMPASSIVE_MODE)
  }
#    endif

#    if defined(CCL_ENABLE_MULTIPLE_CONFIG)
  }
#    endif

   /* ESCAN00010661 
   *  Enable the global interrupt before leaving the function. */
   CanGlobalInterruptRestore();
 }
#  endif

#  if defined( CCL_ENABLE_COM_REQ_HANDLING_API )
/************************************************************************
| NAME:               CclGetComHandleState
| PROTOTYPE:          vuint8 CCL_API_CALL_TYPE CclGetComHandleState(vuint8 cclComHandle)
| CALLED BY:          Application
| PRECONDITIONS:
| INPUT PARAMETERS:   cclComHandle: communication request handle
| RETURN VALUE:       kCclComReqPending: the communication request is set
|                     kCclComReqNotPending: the communication request is not set
| DESCRIPTION:        Return the communication handle request state
|*************************************************************************/
vuint8 CCL_API_CALL_TYPE CclGetComHandleState(vuint8 cclComHandle)
{
  vuint8 retValue;

  retValue = kCclComReqNotPending;

  /* disable glaobal interrupts */
  CanGlobalInterruptDisable();

  /* check if the communication request is set */
  if( (cclIntNetState[cclUserOffset[cclComHandle]] & cclUserMask[cclComHandle]) != kCclNoNetRequest )
  {
    /* the communication request is not set */
    retValue = kCclComReqPending;
  }

  /* enable global interrupts */
  CanGlobalInterruptRestore();

  return retValue;
}

/************************************************************************
| NAME:               CclComRequestPending
| PROTOTYPE:          vuint8 CCL_API_CALL_TYPE CclComRequestPending(void) or
|                     vuint8 CCL_API_CALL_TYPE CclComRequestPending(CanChannelHandle channel)
| CALLED BY:          Application
| PRECONDITIONS:      
| INPUT PARAMETERS:   channel: communication request handle
| RETURN VALUE:       kCclComReqPending: minimum one communication request is set
|                                        for the channel
|                     kCclComReqNotPending: no communication request is set
|                                           for the channel
| DESCRIPTION:        Return the communication state for the CAN channel
|*************************************************************************/
vuint8 CCL_API_CALL_TYPE CclComRequestPending(CCL_CHANNEL_CCLTYPE_ONLY)
{
  vuint8 retValue;
  vuint8 intNetState;
#    if(kCclNetReqTableSize > 1)
  vuint8 index;
#    endif

#    if(kCclNetReqTableSize > 1)
  intNetState = 0;
#    endif

  retValue = kCclComReqPending;

  /* disable global interrupts */
  CanGlobalInterruptDisable();

  /* calculate if a communication request is pending */
#    if(kCclNetReqTableSize > 1)
  for(index=cclStartIndex[CCL_CHANNEL_CCLINDEX]; index<=cclStopIndex[CCL_CHANNEL_CCLINDEX]; index++)
  {
    intNetState |= cclIntNetState[index];
  }
#    else
  intNetState = cclIntNetState[CCL_CHANNEL_CCLINDEX];
#    endif

  if( intNetState == kCclNoNetRequest )
  {
    /* no communication request is pending for the CAN channel */
    retValue = kCclComReqNotPending;
  }

  /* enable global interrupts */
  CanGlobalInterruptRestore();

  return retValue;
}
#  endif

#  if defined (CCL_ENABLE_EMC_WAKEUP)
#    if defined (C_ENABLE_COND_RECEIVE_FCT)
/************************************************************************
| NAME:               ApplCanMsgCondReceived
| PROTOTYPE:          void ApplCanMsgCondReceived(CanRxInfoStructPtr rxStruct)
| CALLED BY:          CAN driver
| PRECONDITIONS:
| INPUT PARAMETERS:   rxStruct
| RETURN VALUE:       -
| DESCRIPTION:        notification about a conditional message reception
|                     to detect a valid CAN message after an EMC wakeup event
|*************************************************************************/
void DRV_API_CALLBACK_TYPE ApplCanMsgCondReceived(NM_MSG_COND_RX_PARAMETER_TYPE NM_MSG_COND_RX_PARAMETER_NAME)
 {

#if defined(C_MULTIPLE_RECEIVE_CHANNEL)
   CanChannelHandle channel;

   channel = NM_MSG_COND_RX_CHANNEL;
#endif

#if defined( C_MULTIPLE_RECEIVE_CHANNEL )  || \
    defined( C_SINGLE_RECEIVE_CHANNEL )
#  if defined( V_ENABLE_USE_DUMMY_STATEMENT )
   /* dummy assignment to avoid compiler warning */
   NM_MSG_COND_RX_PARAMETER_NAME = NM_MSG_COND_RX_PARAMETER_NAME;
#  endif
#endif

#if ( kCclNrOfSystemChannels > kCclNrOfChannels )
   if( channel >= kCclNrOfChannels )
   {
     ApplCclCanMsgCondReceived( NM_MSG_COND_RX_PARAMETER_NAME ); /* ESCAN00076639 */
   }
   else
#endif
   {
     /* set external CAN network request */
     cclExtCanWakeUpReq[CCL_CHANNEL_CCLINDEX] = kCclExtChWupReq;
     if(cclIntNetReq[CCL_CHANNEL_CCLINDEX] == kCclNoIntNetReq) /* ESCAN00011508 */
     {

       {

#        if defined (CCL_USE_REQUEST_SETEXTCOM_FCT)
         /* external CAN communication request notification */
#          if(kCclNrOfChannels > 1)
         if (CclExtCanComReqFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
         {
           /* By using the following table of function calls, code-doubled functions 
            * are called from the indexed CCL. This is done to simplify the called 
            * functions (no distinction of the parameter 'channel' is necessary). */
           (CclExtCanComReqFctTbl[CCL_CHANNEL_CCLINDEX])();
         }
#          else
         CclExtCanComReqFct();
#          endif
#        endif
       }
     }

   }
     {

     /* reject message reception notification */
     CanResetMsgReceivedCondition(CCL_CHANNEL_CANPARA_ONLY);
   }
 }
#    else
#      error "conditional received function must be activated for 'EMC wakeup' algorithm"
#    endif
#  endif

#endif /* CCL_ENABLE_INTERNAL_REQUEST */

/************************************************************************
| NAME:               CclEnableCommunication
| PROTOTYPE:          void CclEnableCommunication(vuint8 channel)
|                     or
|                     void CclEnableCommunication(void)
| CALLED BY:          DPM or Application
| PRECONDITIONS:      Not to be called within ISR
|                     If the DPM component is configured than it is not allowed
|                     to call this function by the application.
| INPUT PARAMETERS:   channel (multiple channel)
|                     or
|                     void (single channel)
| RETURN VALUE:       -
| DESCRIPTION:        enable the HW communication state of CAN controller
|                     CAN transceiver and allow the communication (caused
|                     by external channel and internal network requests)
|*************************************************************************/
void CCL_API_CALL_TYPE CclEnableCommunication(CCL_CHANNEL_CCLTYPE_ONLY)
 {
   /* set HW communication state to enable */
   cclComHwState[CCL_CHANNEL_CCLINDEX] = kCclComHwEnabled;
 }

/************************************************************************
| NAME:               CclDisableCommunication
| PROTOTYPE:          void CclDisableCommunication(vuint8 channel)
|                     or
|                     void CclDisableCommunication(void)
| CALLED BY:          DPM or Application
| PRECONDITIONS:      Not to be called within ISR
|                     If the DPM component is configured than it is not allowed
|                     to call this function by the application.
| INPUT PARAMETERS:   channel (multiple channel)
|                     or
|                     void (single channel)
| RETURN VALUE:       -
| DESCRIPTION:        disable the HW communication state of CAN controller
|                     CAN transceiver and prevent the communication (caused
|                     by external channel and internal network requests)
|*************************************************************************/
void CCL_API_CALL_TYPE CclDisableCommunication(CCL_CHANNEL_CCLTYPE_ONLY)
 {
   /* set HW communication state to disable */
   cclComHwState[CCL_CHANNEL_CCLINDEX] = kCclComHwDisabled;
 }

#if defined ( CCL_ENABLE_MISSING_ACK_HANDLING )
/************************************************************************
| NAME:               CclDisableMissingAck
| CALLED BY:          Application
| INPUT PARAMETERS:   channel (multiple channel)
|                     or
|                     void (single channel)
| RETURN VALUE:       -
| DESCRIPTION:        Disable the Missing Acknowledge Handling
|*************************************************************************/
void CCL_API_CALL_TYPE CclDisableMissingAck( CCL_CHANNEL_CCLTYPE_ONLY )
{
  CanGlobalInterruptDisable();
  cclMissingAckEnabled[CCL_CHANNEL_CCLINDEX] = 0u;
  cclMissingAckTimer[CCL_CHANNEL_CCLINDEX] = 0u;

  if( cclMissingAckTxStopped[CCL_CHANNEL_CCLINDEX] == 1u )
  {
    cclMissingAckTxStopped[CCL_CHANNEL_CCLINDEX] = 0u;
    CclCanOnline( CCL_CHANNEL_CCLPARA_ONLY );
  }
  CanGlobalInterruptRestore();
}

/************************************************************************
| NAME:               CclEnableMissingAck
| CALLED BY:          Application
| INPUT PARAMETERS:   channel (multiple channel)
|                     or
|                     void (single channel)
| RETURN VALUE:       -
| DESCRIPTION:        Enable the Missing Acknowledge Handling
|*************************************************************************/
void CCL_API_CALL_TYPE CclEnableMissingAck( CCL_CHANNEL_CCLTYPE_ONLY )
{
  cclMissingAckEnabled[CCL_CHANNEL_CCLINDEX] = 1u;
}
#endif

#if defined (CCL_ENABLE_TRCV_TYPE_TLE6251G) /* ESCAN00022973 */
/************************************************************************
| NAME:               CclSetTrcvRxOnlyMode
| PROTOTYPE:          void CclSetTrcvRxOnlyMode(CanChannelHandle channel)
| CALLED BY:          Application from task level
| PRECONDITIONS:
| INPUT PARAMETERS:   channel (multiple receive channel)
|                     or
|                     void (single receive channel)
| RETURN VALUE:       kCclTrcvStateChangePerformed
|                     or
|                     kCclTrcvStateChangeNotPerformed
| DESCRIPTION:        informs the CCL to set the transceiver into the receive
|                     only mode
|*************************************************************************/
vuint8 CclSetTrcvRxOnlyMode(CCL_CHANNEL_CCLTYPE_ONLY)
{
  vuint8 retVal;

  retVal = kCclTrcvStateChangePerformed;
  
  /* CCL must be in state Active or GoToSleep: */
  CclAssert( (cclNmState[CCL_CHANNEL_CCLINDEX] > kCclStateWaitBusSleep), kCclErrWrongCclState)

  if(cclNmState[CCL_CHANNEL_CCLINDEX] > kCclStateWaitBusSleep)
  {
#  if(kCclNrOfChannels > 1)
    if (CclSetTrcvRxOnlyModeFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
    {
      /* By using the following table of function calls, code-doubled functions 
      * are called from the indexed CCL. This is done to simplify the called 
      * functions (no distinction of the parameter 'channel' is necessary). */
      (CclSetTrcvRxOnlyModeFctTbl[CCL_CHANNEL_CCLINDEX])();
    }
#  else
    CclSetTrcvRxOnlyModeFct();
#  endif
  }
  else
  {
    retVal = kCclTrcvStateChangeNotPerformed;
  }

  return retVal;
}

/************************************************************************
| NAME:               CclLeaveTrcvRxOnlyMode
| PROTOTYPE:          void CclLeaveTrcvRxOnlyMode(CanChannelHandle channel)
| CALLED BY:          Application from task level
| PRECONDITIONS:
| INPUT PARAMETERS:   channel (multiple receive channel)
|                     or
|                     void (single receive channel)
| RETURN VALUE:       kCclTrcvStateChangePerformed
|                     or
|                     kCclTrcvStateChangeNotPerformed
| DESCRIPTION:        informs the CCL to set the transceiver back to normal mode
|*************************************************************************/
vuint8 CclLeaveTrcvRxOnlyMode(CCL_CHANNEL_CCLTYPE_ONLY)
{ 
  vuint8 retVal;

  retVal = kCclTrcvStateChangePerformed;

  /* CCL must be in state Active or GoToSleep: */
  CclAssert( (cclNmState[CCL_CHANNEL_CCLINDEX] > kCclStateWaitBusSleep), kCclErrWrongCclState)

  if(cclNmState[CCL_CHANNEL_CCLINDEX] > kCclStateWaitBusSleep)
  {
#  if(kCclNrOfChannels > 1)
    if (CclLeaveTrcvRxOnlyModeFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
    {
      /* By using the following table of function calls, code-doubled functions 
      * are called from the indexed CCL. This is done to simplify the called 
      * functions (no distinction of the parameter 'channel' is necessary). */
      (CclLeaveTrcvRxOnlyModeFctTbl[CCL_CHANNEL_CCLINDEX])();
    }
#  else
    CclLeaveTrcvRxOnlyModeFct();
#  endif
  }
  else
  {
    retVal = kCclTrcvStateChangeNotPerformed;
  }

  return retVal;
}
#endif

#if defined(CCL_NM_TYPE_NONE)
/************************************************************************
| NAME:               CclNmWaitBusSleep
| PROTOTYPE:          void CclNmWaitBusSleep(CanChannelHandle channel)
| CALLED BY:          Application from task level
| PRECONDITIONS:
| INPUT PARAMETERS:   channel (multiple receive channel)
|                     or
|                     void (single receive channel)
| RETURN VALUE:       void
| DESCRIPTION:        informs the CCL to change into the wait bus sleep mode
|*************************************************************************/
void CCL_API_CALL_TYPE CclNmWaitBusSleep(CCL_CHANNEL_CCLTYPE_ONLY)
{
  CclAssert(cclNmState[CCL_CHANNEL_CCLINDEX] == kCclStateGoToSleep, kCclErrWrongStateTransition)

  CclAssert((cclChannelWithoutNm & (vuint8)((vuint8)1 << (CCL_CHANNEL_CCLINDEX))) != kCclChWithNm, kCclWrongChannelHandle )

  CanOffline(CCL_CHANNEL_CANPARA_ONLY);

  CclComWait(CCL_CHANNEL_CCLPARA_ONLY);

  cclNmState[CCL_CHANNEL_CCLINDEX] = kCclStateWaitBusSleep;

  ApplCclNmStateChange(CCL_CHANNEL_CCLPARA_FIRST kCclStateGoToSleep, kCclStateWaitBusSleep);
}

/************************************************************************
| NAME:               CclNmWaitBusSleepCancel
| PROTOTYPE:          void CclNmWaitBusSleepCancel(CanChannelHandle channel)
| CALLED BY:          Application from task level
| PRECONDITIONS:
| INPUT PARAMETERS:   channel (multiple receive channel)
|                     or
|                     void (single receive channel)
| RETURN VALUE:       void
| DESCRIPTION:        informs the CCL to cancel the the wait bus sleep mode
|*************************************************************************/
void CCL_API_CALL_TYPE CclNmWaitBusSleepCancel(CCL_CHANNEL_CCLTYPE_ONLY)
{
  CclAssert(cclNmState[CCL_CHANNEL_CCLINDEX] == kCclStateWaitBusSleep, kCclErrWrongStateTransition)

  CclAssert((cclChannelWithoutNm & (vuint8)((vuint8)1 << (CCL_CHANNEL_CCLINDEX))) != kCclChWithNm, kCclWrongChannelHandle )

  CanOnline(CCL_CHANNEL_CANPARA_ONLY);
  
  CclComResume(CCL_CHANNEL_CCLPARA_ONLY);

  cclNmState[CCL_CHANNEL_CCLINDEX] = kCclStateGoToSleep;
  
  ApplCclNmStateChange(CCL_CHANNEL_CCLPARA_FIRST kCclStateWaitBusSleep, kCclStateGoToSleep);
}

/************************************************************************
| NAME:               CclNmSleep
| PROTOTYPE:          void CclNmSleep(CanChannelHandle channel)
| CALLED BY:          Application from task level
| PRECONDITIONS:
| INPUT PARAMETERS:   channel (multiple receive channel)
|                     or
|                     void (single receive channel)
| RETURN VALUE:       void
| DESCRIPTION:        informs the CCL to change into the sleep mode
|*************************************************************************/
void CCL_API_CALL_TYPE CclNmSleep(CCL_CHANNEL_CCLTYPE_FIRST CanInitHandle initObject )
{
  CclAssert(cclNmState[CCL_CHANNEL_CCLINDEX] == kCclStateWaitBusSleep ,kCclErrWrongStateTransition)

  CclAssert((cclChannelWithoutNm & (vuint8)((vuint8)1 << (CCL_CHANNEL_CCLINDEX))) != kCclChWithNm, kCclWrongChannelHandle )

  CanOffline(CCL_CHANNEL_CANPARA_ONLY);

#  if defined ( C_MULTIPLE_RECEIVE_CHANNEL )
  /* Macros must be encapsulated in this way */
  CanResetBusSleep( CCL_CHANNEL_CCLPARA_ONLY, initObject );
#  else
  CanResetBusSleep( initObject );
#  endif

  CclComStop(CCL_CHANNEL_CCLPARA_ONLY);
  CclCanStandby(CCL_CHANNEL_CCLPARA_ONLY);
}

/************************************************************************
| NAME:               CclComBusOffStart
| PROTOTYPE:          void CclBusOffStart(CanChannelHandle channel)
| CALLED BY:          Application from task level
| PRECONDITIONS:
| INPUT PARAMETERS:   channel (multiple receive channel)
|                     or
|                     void (single receive channel)
| RETURN VALUE:       void
| DESCRIPTION:        informs the CCL about the bus off recovery start phase
|*************************************************************************/
void CCL_API_CALL_TYPE CclComBusOffStart(CCL_CHANNEL_CCLTYPE_ONLY)
{
  CanOffline(CCL_CHANNEL_CANPARA_ONLY);
  CclBusOffStart(CCL_CHANNEL_CCLPARA_ONLY);
}

/************************************************************************
| NAME:               CclComBusOffEnd
| PROTOTYPE:          void CclBusOffEnd(CanChannelHandle channel)
| CALLED BY:          Application from task level
| PRECONDITIONS:
| INPUT PARAMETERS:   channel (multiple receive channel)
|                     or
|                     void (single receive channel)
| RETURN VALUE:       void
| DESCRIPTION:        informs the CCL about the bus off recovery end
|*************************************************************************/
void CCL_API_CALL_TYPE CclComBusOffEnd(CCL_CHANNEL_CCLTYPE_ONLY)
{
  if(cclNmState[CCL_CHANNEL_CCLINDEX] > kCclStateWaitBusSleep)
  {
    CanOnline(CCL_CHANNEL_CANPARA_ONLY);
  }
 
  CclBusOffEnd (CCL_CHANNEL_CCLPARA_ONLY);
}
#endif

/* module specific MISRA deviations:
 MD_Ccl_3689:
      Reason:     Channel parameter is used for array access.
      Risk:       Index out of bounds access.
      Prevention: Channel index is checked by an assertion.
*/

/***************************************************************************/
/* Version check                                                           */
/***************************************************************************/

#if (CCL_VECTOR_VERSION != 0x0114)
  #error "CCL VECTOR OEM: incorrect main or sub version !"
#endif

#if (CCL_VECTOR_RELEASE_VERSION != 0x02)
  #error "CCL VECTOR OEM: incorrect release version!"
#endif

V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kCclMainVersion    =(vuint8)(CCL_VECTOR_VERSION >> 8);
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kCclSubVersion     =(vuint8)( (CCL_VECTOR_VERSION) & 0xFF);
V_MEMROM0 V_MEMROM1 vuint8 V_MEMROM2 kCclReleaseVersion =(vuint8)( (CCL_VECTOR_RELEASE_VERSION) & 0xFF);

/***************************************************************************/ 
/* Plausibility checks                                                     */ 
/***************************************************************************/
#if defined( NM_TYPE_VECTOR_OSEK ) || defined( NM_TYPE_DBAG_OSEK )
#  if !defined( NM_ENABLE_EXTENDED_CALLBACK )
#    error "No extended callbacks activated for NM-OSEK !"
#  endif
#  if defined( VGEN_ENABLE_NM_ASRNMCANWRAPPEREXT )
#    error "NM ASR is not supported together with NM OSEK!"
#  endif
#endif

#if defined( NM_TYPE_BASIC ) || defined( NM_TYPE_VECTOR_OSEK ) || defined( NM_TYPE_DBAG_OSEK )
#  if defined ( CCL_NM_TYPE_NONE )
#    error "NM type 'None' is not supported together with NM BASIC or NM OSEK!"
#  endif
#endif

#if defined( NM_TYPE_BASIC )
#  if defined( CCL_ENABLE_MISSING_ACK_HANDLING )
#    if defined( NMBASIC_ENABLE_EXTERNAL_CANONLINE_HANDLING )
#    else
#      error "The external CanOnline handling in NM BASIC must be enabled."
#    endif
#  endif
#endif

#if defined( NMHDLAN_NM_TYPE )
#  if defined( NM_TYPE_VECTOR_OSEK ) || defined( NM_TYPE_DBAG_OSEK )
#    error "NMHDLAN is not supported together with NM OSEK!"
#  endif
#  if defined( VGEN_ENABLE_NM_ASRNMCANWRAPPEREXT ) || defined( VGEN_ENABLE_NM_ASR_CAN )
#    error "NMHDLAN is not supported together with NM ASR!"
#  endif
#endif

#if defined (VGEN_ENABLE_NM_ASR_IF)
#  if defined (NM_COORDINATOR_SUPPORT_ENABLED)
#    if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
#      error "NM coordinator feature is not supported with this Ccl version!"
#    endif
#  endif
#endif

#if defined(VGEN_ENABLE_ECUM_SMSVE)
#  error "EcuM for SVE is not supported with this Ccl version!"
#endif

#if defined (VGEN_ENABLE_NM_ASR_GENERIC)
#  error "Generic NM is not supported with this Ccl version!"
#endif

#if defined( VGEN_ENABLE_NM_ASRNMCANWRAPPEREXT )
#  if  ( NM_STATE_CHANGE_IND_ENABLED == STD_OFF )
#   error "Please enable the state change notification of the NM ASR in the generation tool."
#  endif
#endif

#if defined( VGEN_ENABLE_NM_ASR_CAN )
#  if ( NM_ASRNMIF_VERSION < 0x0217u )
#    error "Nm_AsrIf version >= 2.17 needed!"
#  endif
#endif

#if defined (VGEN_GENY)
#  if( CCL__COREDLL_VERSION == 0x0311 )
#    if( CCL__COREDLL_RELEASE_VERSION < 0x27 )
#      error "Incompatible Ccl__core.dll-version for this CCL-Implementation! The CCL needs minimum version 3.11.27!"
#    endif
#  else
#    error "Incompatible Ccl__core.dll-version for this CCL-Implementation! The CCL needs minimum version 3.11.27!"
#  endif
#endif

#if defined( CCL_ENABLE_MISSING_ACK_HANDLING )
#  if defined( C_CLIENT_VECTOR )
#  else
#    error "Missing Acknowledge handling is only supported for OEM Vector."
#  endif
#  if defined( C_ENABLE_TX_OBSERVE )
#  else
#    error "Tx Observation feature in CAN driver must be enabled."
#  endif
#endif

#if defined( CCL_ENABLE_EMC_WAKEUP )
#  if defined( C_CLIENT_VECTOR )
#  else
#    error "EMC wake-up handling is only supported for OEM Vector."
#  endif
#  if defined( CCL_ENABLE_EXTERNAL_REQUEST )
#  else
#    error "External requests must be enabled for EMC wake-up handling."
#  endif
#endif

/***************************************************************************/ 
/* defines                                                                 */ 
/***************************************************************************/
#if defined(VGEN_ENABLE_NM_ASRNMCANWRAPPEREXT)
# if( kCclNrOfChannels > 1 )
#  if ( kCbdWrpNumberOfChannels == 1u )
#   define CCL_NM_CBD_WRP_CHANNEL_PARA    (CanChannelHandle)kCclNmCbdWrpChIndex
#   define CCL_NM_CBD_WRP_CHANNEL_INDEX   kCclNmCbdWrpChIndex
#  else
#   define CCL_NM_CBD_WRP_CHANNEL_PARA    (CanChannelHandle)nmChannelHandle
#   define CCL_NM_CBD_WRP_CHANNEL_INDEX   nmChannelHandle
#  endif
# else
#  define CCL_NM_CBD_WRP_CHANNEL_PARA    
#  define CCL_NM_CBD_WRP_CHANNEL_INDEX    0u
# endif
#endif

/***************************************************************************/ 
/* callback functions                                                      */ 
/***************************************************************************/ 

#if defined(NM_TYPE_VECTOR_OSEK) || defined(NM_TYPE_DBAG_OSEK)
/************************************************************************
| NAME:                ApplNmCanNormal
| PROTOTYPE:           void ApplNmCanNormal(void) or
|                      void ApplNmCanNormal(CanChannelHandle channel)
| CALLED BY:           OSEK-NM from NmOsekInit() and NmTask()
| PRECONDITIONS:
| INPUT PARAMETERS:    void (single channel) or channel (multiple channel)
| RETURN VALUE:        void
| DESCRIPTION:         Set the CAN controller and the CAN transceiver in NORMAL mode
|                      and disable the external wakeup port INT.
|*************************************************************************/
void NM_API_CALLBACK_TYPE ApplNmCanNormal(NM_CHANNEL_APPLTYPE_ONLY)
 {
#  if ( kCclNrOfChannels == 1 ) || ( defined( NM_ENABLE_INDEXED_NM ) )
   CclCanNormal(CCL_CHANNEL_CCLPARA_ONLY);
#  else
   CclCanNormal(NM_CAN_CHANNEL);
#  endif
}

/************************************************************************
| NAME:                ApplNmCanSleep
| PROTOTYPE:           void ApplNmCanSleep(void)
|                      void ApplNmCanSleep(CanChannelHandle channel)
| CALLED BY:           OSEK-NM from NmOsekInit() and NmTask()
| PRECONDITIONS:
| INPUT PARAMETERS:    void (single channel) or channel (multiple channel)
| RETURN VALUE:        void
| DESCRIPTION:         Set the CAN controller and the CAN transceiver in SLEEP mode
|                      and enables the external wakeup port INT.
|*************************************************************************/
void NM_API_CALLBACK_TYPE ApplNmCanSleep(NM_CHANNEL_APPLTYPE_ONLY)
 {
#  if ( kCclNrOfChannels == 1 ) || ( defined( NM_ENABLE_INDEXED_NM ) )
   CclComStop(CCL_CHANNEL_CCLPARA_ONLY);
   CclCanStandby(CCL_CHANNEL_CCLPARA_ONLY);
#  else
   CclComStop(NM_CAN_CHANNEL);
   CclCanStandby(NM_CAN_CHANNEL);
#  endif
 }

/************************************************************************
| NAME:                ApplNmCanBusSleep
| PROTOTYPE:           void ApplNmCanBusSleep(void) or
|                      void ApplNmCanBusSleep(CanChannelHandle channel)
| CALLED BY:           OSEK-NM from NmOsekInit() and NmTask()
| PRECONDITIONS:
| INPUT PARAMETERS:    void (single channel) or channel (multiple channel)
| RETURN VALUE:        void
| DESCRIPTION:         s. ApplNmCanSleep
|*************************************************************************/
void NM_API_CALLBACK_TYPE ApplNmCanBusSleep(NM_CHANNEL_APPLTYPE_ONLY)
 {
#  if defined(V_ENABLE_USE_DUMMY_STATEMENT)
#    if defined ( NM_ENABLE_INDEXED_NM )
   (void)channel;  /* PRQA S 3112 */ /* MD_Ccl_3112 */
#    endif
#endif
 }

/************************************************************************
| NAME:               ApplNmBusOff
| PROTOTYPE:          void ApplNmBusOff(void) or 
|                     void ApplNmBusOff(CanChannelHandle channel)
| CALLED BY:          OSEK-NM from NmCanError() (CAN driver error interrupt)
| PRECONDITIONS:
| INPUT PARAMETERS:   void (single channel) or channel (multiple channel)
| RETURN VALUE:       void
| DESCRIPTION:        The CCL handles the configured interaction layer in
 |                    dependency of the CCL configuration.
|*************************************************************************/
void NM_API_CALLBACK_TYPE ApplNmBusOff(NM_CHANNEL_APPLTYPE_ONLY)
 {
#  if ( kCclNrOfChannels == 1 ) || ( defined( NM_ENABLE_INDEXED_NM ) )
   CclBusOffStart(CCL_CHANNEL_CCLPARA_ONLY);
#  else
   CclBusOffStart(NM_CAN_CHANNEL);
#  endif
 }

/************************************************************************
| NAME:               ApplNmBusOffEnd
| PROTOTYPE:          void ApplNmBusOffEnd(void) or
|                     void ApplNmBusOffEnd(CanChannelHandle channel)
| CALLED BY:          OSEK-NM from NmTask()
| PRECONDITIONS:
| INPUT PARAMETERS:   void (single channel) or channel (multiple channel)
| RETURN VALUE:       void
| DESCRIPTION:        The CCL handles the configured interaction layer in
|                     dependency of the CCL configuration.
|*************************************************************************/
void NM_API_CALLBACK_TYPE ApplNmBusOffEnd(NM_CHANNEL_APPLTYPE_ONLY)
 {
#  if ( kCclNrOfChannels == 1 ) || ( defined( NM_ENABLE_INDEXED_NM ) )
   CclBusOffEnd(CCL_CHANNEL_CCLPARA_ONLY);
#  else
   CclBusOffEnd(NM_CAN_CHANNEL);
#  endif
 }

/************************************************************************
| NAME:               ApplNmBusStart
| PROTOTYPE:          void ApplNmBusStart(void) or
|                     void ApplNmBusStart(CanChannelHandle channel)
| CALLED BY :         OSEK-NM from NmOsekInit() and NmTask()
| PRECONDITIONS:
| INPUT PARAMETERS:   void (single channel) or channel (multiple channel)
| RETURN VALUE:       void
| DESCRIPTION:        Start the communication via interaction layer.
|*************************************************************************/
void NM_API_CALLBACK_TYPE ApplNmBusStart(NM_CHANNEL_APPLTYPE_ONLY)
 {
#  if ( kCclNrOfChannels == 1 ) || ( defined( NM_ENABLE_INDEXED_NM ) )
  if( cclNmState[CCL_CHANNEL_CCLINDEX] < kCclStateGoToSleep )
#  else
  if( cclNmState[NM_CAN_CHANNEL] < kCclStateGoToSleep )
#  endif
  {
#  if ( kCclNrOfChannels == 1 ) || ( defined( NM_ENABLE_INDEXED_NM ) )
    if( cclNmState[CCL_CHANNEL_CCLINDEX] == kCclNmStateSleep )
#  else
    if( cclNmState[NM_CAN_CHANNEL] == kCclNmStateSleep )
#  endif
    {
#  if defined(CCL_USE_REQUEST_SETEXTCOM_FCT)
#    if(kCclNrOfChannels > 1)
#      if defined(NM_ENABLE_INDEXED_NM)
      if(cclExtCanWakeUpReq[CCL_CHANNEL_CCLINDEX] == kCclNoExtChWupReq)
      {
        if (CclExtCanComReqFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
        {
          /* By using the following table of function calls, code-doubled functions 
          * are called from the indexed CCL. This is done to simplify the called 
           * functions (no distinction of the parameter 'channel' is necessary). */
          (CclExtCanComReqFctTbl[CCL_CHANNEL_CCLINDEX])();
        }
      }
#      else
      if(cclExtCanWakeUpReq[NM_CAN_CHANNEL] == kCclNoExtChWupReq)
      {
        if (CclExtCanComReqFctTbl[NM_CAN_CHANNEL] != V_NULL)
        {
          /* By using the following table of function calls, code-doubled functions 
          * are called from the indexed CCL. This is done to simplify the called 
          * functions (no distinction of the parameter 'channel' is necessary). */
          (CclExtCanComReqFctTbl[NM_CAN_CHANNEL])();
        }
      }
#      endif
#    else
      if(cclExtCanWakeUpReq[CCL_CHANNEL_CCLINDEX] == kCclNoExtChWupReq)
      {
        CclExtCanComReqFct();
      }
#    endif
#  endif
    }

    /* change CCL state to go to sleep */
#  if ( kCclNrOfChannels == 1 ) || ( defined( NM_ENABLE_INDEXED_NM ) )
    cclNmState[CCL_CHANNEL_CCLINDEX] = kCclNmStateGoToSleep;
#    if defined(CCL_ENABLE_MIN_NM_ACTIVATION_TIME)
#      if defined(CCL_ENABLE_COM_REQ_HANDLING_API)
    (void)CclRequestCommunication((vuint8)CCL_CHANNEL_CCLINDEX);
#      endif
    cclMinNmActivationTimer[CCL_CHANNEL_CCLINDEX] = cclMinNmActivationTimerValue[CCL_CHANNEL_CCLINDEX];
#    endif
#  else
    cclNmState[NM_CAN_CHANNEL] = kCclNmStateGoToSleep;
#    if defined(CCL_ENABLE_MIN_NM_ACTIVATION_TIME)
#      if defined(CCL_ENABLE_COM_REQ_HANDLING_API)
    (void)CclRequestCommunication((vuint8)NM_CAN_CHANNEL);
#      endif
    cclMinNmActivationTimer[NM_CAN_CHANNEL] = cclMinNmActivationTimerValue[NM_CAN_CHANNEL];
#    endif
#  endif
  }
  
  /* start the communication */
#  if ( kCclNrOfChannels == 1 ) || ( defined( NM_ENABLE_INDEXED_NM ) )
  CclComStart(CCL_CHANNEL_CCLPARA_ONLY);
#  else
  CclComStart(NM_CAN_CHANNEL);
#  endif
}

/************************************************************************
| NAME:               ApplNmWaitBusSleep
| PROTOTYPE:          void ApplNmWaitBusSleep(void) or
|                     void ApplNmWaitBusSleep(CanChannelHandle channel)
| CALLED BY :         OSEK-NM from NmTask()
| PRECONDITIONS:
| INPUT PARAMETERS:   void (single channel) or channel (multiple channel)
| RETURN VALUE :      void
| DESCRIPTION :       Stop the communication via interaction layer.
|*************************************************************************/
void NM_API_CALLBACK_TYPE ApplNmWaitBusSleep(NM_CHANNEL_APPLTYPE_ONLY)
{
#  if ( kCclNrOfChannels == 1 ) || ( defined( NM_ENABLE_INDEXED_NM ) )
  cclNmState[CCL_CHANNEL_CCLINDEX] = kCclStateWaitBusSleep;
  CclComWait(CCL_CHANNEL_CCLPARA_ONLY);
#  else
  cclNmState[NM_CAN_CHANNEL] = kCclStateWaitBusSleep;
  CclComWait(NM_CAN_CHANNEL);
#  endif
}

/************************************************************************
| NAME:               ApplNmWaitBusSleepCancel
| PROTOTYPE:          void ApplNmWaitBusSleepCancel(void) or
|                     void ApplNmWaitBusSleepCancel(CanChannelHandle channel)
| CALLED BY :         OSEK-NM from NmTask()
| PRECONDITIONS:
| INPUT PARAMETERS:   void (single channel) or channel (multiple channel)
| RETURN VALUE :      void
| DESCRIPTION :       Start the communication via interaction layer.
|*************************************************************************/
void NM_API_CALLBACK_TYPE ApplNmWaitBusSleepCancel(NM_CHANNEL_APPLTYPE_ONLY)
{
#  if ( kCclNrOfChannels == 1 ) || ( defined( NM_ENABLE_INDEXED_NM ) )
  ApplCanWakeUp(CCL_CHANNEL_CANPARA_ONLY);
#   if defined ( CCL_ENABLE_EMC_WAKEUP )
  /* With EMC handling active ApplCanWakeUp() only sets ExtEmcWakeUp flag.
     Set ExtCanWakeUp flag to assure correct handling in CclTask. */
  cclExtCanWakeUpReq[CCL_CHANNEL_CCLINDEX] = kCclExtChWupReq;
#   endif
  CclComResume(CCL_CHANNEL_CCLPARA_ONLY);
#  else
  ApplCanWakeUp(NM_CAN_CHANNEL);
#   if defined ( CCL_ENABLE_EMC_WAKEUP )
  /* With EMC handling active ApplCanWakeUp() only sets ExtEmcWakeUp flag.
     Set ExtCanWakeUp flag to assure correct handling in CclTask. */
  cclExtCanWakeUpReq[NM_CAN_CHANNEL] = kCclExtChWupReq;
#   endif
  CclComResume(NM_CAN_CHANNEL);
#  endif
}

#  if defined( CCL_ENABLE_MISSING_ACK_HANDLING )
#    if defined( NM_ENABLE_EXTERNAL_CANONLINE_HANDLING )
/************************************************************************
| NAME:               ApplNmCanOnline
| PROTOTYPE:          void ApplNmCanOnline(CanChannelHandle channel)
| CALLED BY:          NM task
| PRECONDITIONS:      -
| INPUT PARAMETERS:   channel (if indexed) or void (code doubled)
| RETURN VALUE:       void
| DESCRIPTION :       Triggers the CCL to switch the CAN driver to online mode.
|*************************************************************************/
void ApplNmCanOnline(NM_CHANNEL_CANTYPE_ONLY)
{
#      if defined( V_ENABLE_USE_DUMMY_STATEMENT )
#        if ( defined( C_MULTIPLE_RECEIVE_CHANNEL ) && ( kCclNrOfChannels == 1 ) )
  (void)channel;  /* PRQA S 3112 */ /* MD_Ccl_3112 */
#        endif
#      endif

  CclCanOnline(CCL_CHANNEL_CCLPARA_ONLY);
}

/************************************************************************
| NAME:               ApplNmCanOffline
| PROTOTYPE:          void ApplNmCanOffline(CanChannelHandle channel)
| CALLED BY:          NM task
| PRECONDITIONS:      -
| INPUT PARAMETERS:   channel (if indexed) or void (code doubled)
| RETURN VALUE:       void
| DESCRIPTION :       Triggers the CCL to switch the CAN driver to offline mode.
|*************************************************************************/
void ApplNmCanOffline(NM_CHANNEL_CANTYPE_ONLY)
{
#      if defined( V_ENABLE_USE_DUMMY_STATEMENT )
#        if ( defined( C_MULTIPLE_RECEIVE_CHANNEL ) && ( kCclNrOfChannels == 1 ) )
  (void)channel;  /* PRQA S 3112 */ /* MD_Ccl_3112 */
#        endif
#      endif

  CclCanOffline(CCL_CHANNEL_CCLPARA_ONLY);
}
#    endif
#  endif

#  if defined ( NM_ENABLE_ASSERTIONS )
#    if defined(CCL_ENABLE_ERROR_HOOK)
/************************************************************************
| NAME:               ApplNmDirOsekFatalError
| PROTOTYPE:          void ApplNmDirOsekFatalError(vuint8 error)
| CALLED BY:          NM task
| PRECONDITIONS:      -
| INPUT PARAMETERS:   error code
| RETURN VALUE:       void
| DESCRIPTION :       Notifies the CCL about a fatal error in NM Osek
|*************************************************************************/
void NM_API_CALLBACK_TYPE ApplNmDirOsekFatalError( vuint8 error )
{
  CclFatalError(CCL_NO_CHANNEL_INFO_AVAILABLE, (vuint16)error, 0, kComponentNm);
}
#    endif
#  endif
#endif

#if defined(NM_TYPE_BASIC)
/************************************************************************
 | NAME:               ApplNmBasicBusOffStart
 | PROTOTYPE:          void ApplNmBasicBusOffStart(void) or
 |                     void ApplNmBasicBusOffStart(CanChannelHandle channel)
 | CALLED BY:          NM Powertrain Basic from NmBasicCanBusOff 
 |                     (CAN driver error interrupt)
 | PRECONDITIONS:
 | INPUT PARAMETERS:   void (single channel) or channel (multiple channel)
 | RETURN VALUE:       void
 | DESCRIPTION :       The CCL handles the configured interaction layer in
 |                     dependency of the CCL configuration.
 |*************************************************************************/
 void ApplNmBasicBusOffStart(NMBASIC_CHANNEL_NMTYPE_ONLY)
 {
#  if(kCclNrOfChannels > 1)
#    if defined(NMBASIC_ENABLE_INDEXED_NM)
   CclBusOffStart(NMBASIC_CHANNEL_NMPARA_ONLY);
#    else
   CclBusOffStart(NMBASIC_CAN_CHANNEL);
#    endif
#  else
   CclBusOffStart(CCL_CHANNEL_CCLPARA_ONLY);
#  endif
 }
 
 /************************************************************************
 | NAME:               ApplNmBasicBusOffEnd
 | PROTOTYPE:          void ApplNmBasicBusOffEnd(void) or
 |                     void ApplNmBasicBusOffEnd(CanChannelHandle channel)
 | CALLED BY:          NM Powertrain Basic (task level)
 | PRECONDITIONS:
 | INPUT PARAMETERS:   void (single channel) or channel (multiple channel)
 | RETURN VALUE:       void
 | DESCRIPTION :       The CCL handles the configured interaction layer in
 |                     dependency of the CCL configuration.
 |*************************************************************************/
 void ApplNmBasicBusOffEnd(NMBASIC_CHANNEL_NMTYPE_ONLY)
 {
#  if(kCclNrOfChannels > 1)
#    if defined(NMBASIC_ENABLE_INDEXED_NM)
   CclBusOffEnd(NMBASIC_CHANNEL_NMPARA_ONLY);
#    else
   CclBusOffEnd(NMBASIC_CAN_CHANNEL);
#    endif
#  else
   CclBusOffEnd(CCL_CHANNEL_CCLPARA_ONLY);
#  endif
 }
 
 /************************************************************************
 | NAME:               ApplNmBasicEnabledCom
 | PROTOTYPE:          void ApplNmBasicEnabledCom(void) or
 |                     void ApplNmBasicEnabledCom(CanChannelHandle channel)
 | CALLED BY:          NM Powertrain Basic (task level)
 | PRECONDITIONS:
 | INPUT PARAMETERS:   void (single channel) or channel (multiple channel)
 | RETURN VALUE:       void
 | DESCRIPTION :       Start the communication via interaction layer.
 |*************************************************************************/
 void ApplNmBasicEnabledCom(NMBASIC_CHANNEL_NMTYPE_ONLY)
 {
#  if(kCclNrOfChannels > 1)
#    if defined(NMBASIC_ENABLE_INDEXED_NM)
   CclComStart(NMBASIC_CHANNEL_NMPARA_ONLY);
#    else
   CclComStart(NMBASIC_CAN_CHANNEL);
#    endif
#  else
   CclComStart(CCL_CHANNEL_CCLPARA_ONLY);
#  endif
 }
 
 /************************************************************************
 | NAME:               ApplNmBasicDisabledCom
 | PROTOTYPE:          void ApplNmBasicDisabledCom(void) or
 |                     void ApplNmBasicDisabledCom(CanChannelHandle channel)
 | CALLED BY:          NM Powertrain Basic (task level)
 | PRECONDITIONS:
 | INPUT PARAMETERS:   void (single channel) or channel (multiple channel)
 | RETURN VALUE:       void
 | DESCRIPTION :       Stop the communication via interaction layer.
 |*************************************************************************/
 void ApplNmBasicDisabledCom(NMBASIC_CHANNEL_NMTYPE_ONLY)
 {
#  if(kCclNrOfChannels > 1)
#    if defined(NMBASIC_ENABLE_INDEXED_NM)
   CclComStop(NMBASIC_CHANNEL_NMPARA_ONLY);
#    else
   CclComStop(NMBASIC_CAN_CHANNEL);
#    endif
#  else
   CclComStop(CCL_CHANNEL_CCLPARA_ONLY);
#  endif
 }
 
 /************************************************************************
| NAME:               ApplNmBasicSwitchTransceiverOn
| PROTOTYPE:          void ApplNmBasicSwitchTransceiverOn(void) or
|                     void AApplNmBasicSwitchTransceiverOn(CanChannelHandle channel)
| CALLED BY:          NM Powertrain Basic (task level)
| PRECONDITIONS:      -
| INPUT PARAMETERS:   void (single channel) or channel (multiple channel)
| RETURN VALUE:       void
| DESCRIPTION:        Set the transceiver into the normal mode.
|*************************************************************************/
void ApplNmBasicSwitchTransceiverOn(NMBASIC_CHANNEL_NMTYPE_ONLY)
 {
#  if(kCclNrOfChannels > 1)
#    if defined(NMBASIC_ENABLE_INDEXED_NM)
   CclCanNormal(NMBASIC_CHANNEL_NMPARA_ONLY);
#    else
   CclCanNormal(NMBASIC_CAN_CHANNEL);
#    endif
#  else
   CclCanNormal(CCL_CHANNEL_CCLPARA_ONLY);
#  endif
 }

/************************************************************************
| NAME:               ApplNmBasicSwitchTransceiverOff
| PROTOTYPE:          void ApplNmBasicSwitchTransceiverOff(void) or
|                     void ApplNmBasicSwitchTransceiverOff(CanChannelHandle channel)
| CALLED BY:          NM Powertrain Basic (task level)
| PRECONDITIONS:      -
| INPUT PARAMETERS:   void (single channel) or channel (multiple channel)
| RETURN VALUE:       vuint8
| DESCRIPTION:        Set the transceiver into the standby/sleep mode.
|*************************************************************************/
vuint8 ApplNmBasicSwitchTransceiverOff(NMBASIC_CHANNEL_NMTYPE_ONLY)
 {
#  if(kCclNrOfChannels > 1)
#    if defined(NMBASIC_ENABLE_INDEXED_NM)
   CclCanStandby(NMBASIC_CHANNEL_NMPARA_ONLY);
#    else
   CclCanStandby(NMBASIC_CAN_CHANNEL);
#    endif
#  else
   CclCanStandby(CCL_CHANNEL_CCLPARA_ONLY);
#  endif

   return kCanNotSupported;
 }
 
#  if defined( CCL_ENABLE_MISSING_ACK_HANDLING )
#    if defined( NMBASIC_ENABLE_EXTERNAL_CANONLINE_HANDLING )
/************************************************************************
| NAME:               ApplNmBasicCanOnline
| PROTOTYPE:          void ApplNmBasicCanOnline(CanChannelHandle channel)
| CALLED BY:          NM task
| PRECONDITIONS:      -
| INPUT PARAMETERS:   channel (if indexed) or void (code doubled)
| RETURN VALUE:       void
| DESCRIPTION :       Triggers the CCL to switch the CAN driver to online mode.
|*************************************************************************/
void ApplNmBasicCanOnline( NMBASIC_CHANNEL_CANTYPE_ONLY )
{
#      if defined( V_ENABLE_USE_DUMMY_STATEMENT )
#        if ( defined( C_MULTIPLE_RECEIVE_CHANNEL ) && ( kCclNrOfChannels == 1 ) )
  (void)channel;  /* PRQA S 3112 */ /* MD_Ccl_3112 */
#        endif
#      endif

  CclCanOnline( CCL_CHANNEL_CCLPARA_ONLY );
}

/************************************************************************
| NAME:               ApplNmBasicCanOffline
| PROTOTYPE:          void ApplNmBasicCanOffline(CanChannelHandle channel)
| CALLED BY:          NM task
| PRECONDITIONS:      -
| INPUT PARAMETERS:   channel (if indexed) or void (code doubled)
| RETURN VALUE:       void
| DESCRIPTION :       Triggers the CCL to switch the CAN driver to offline mode.
|*************************************************************************/
void ApplNmBasicCanOffline( NMBASIC_CHANNEL_CANTYPE_ONLY )
{
#      if defined( V_ENABLE_USE_DUMMY_STATEMENT )
#        if ( defined( C_MULTIPLE_RECEIVE_CHANNEL ) && ( kCclNrOfChannels == 1 ) )
  (void)channel;  /* PRQA S 3112 */ /* MD_Ccl_3112 */
#        endif
#      endif

  CclCanOffline( CCL_CHANNEL_CCLPARA_ONLY );
}
#    endif
#  endif

#  if defined(NMBASIC_ENABLE_SOFTWARE_CHECK) && defined(CCL_ENABLE_ERROR_HOOK)
/************************************************************************
| NAME:               ApplNmBasicFatalError
| PROTOTYPE:          void ApplNmBasicFatalError(vuint8 error) or
|                     void ApplNmBasicFatalError(CanChannelHandle channel, vuint8 error)
| CALLED BY :         NM Powertrain Basic
| PRECONDITIONS:      NM Powertrain Basic assert occurs
| INPUT PARAMETERS:   void (single channel) or channel (multiple channel)
| RETURN VALUE:       void
| DESCRIPTION:        Call the CCL error handler.
|*************************************************************************/
void ApplNmBasicFatalError(NMBASIC_CHANNEL_APPLTYPE_FIRST vuint8 error)
{
#    if(kCclNrOfChannels > 1)
#      if defined(NMBASIC_ENABLE_INDEXED_NM)
  CclFatalError(NMBASIC_CHANNEL_NMPARA_FIRST (vuint16)error, 0, kComponentNmBasic);
#      else
  CclFatalError(NMBASIC_CAN_CHANNEL, (vuint16)error, 0, kComponentNmBasic);
#      endif
#    else
  CclFatalError(CCL_NO_CHANNEL_INFO_AVAILABLE, (vuint16)error, 0, kComponentNmBasic);
#    endif
}
#  endif
#endif

#if defined(VGEN_ENABLE_NM_ASRNMCANWRAPPEREXT)
/* Indication that some nodes in the network have entered the Network Mode. */
/************************************************************************
| NAME:                ApplCbdWrpNetworkStartIndication
| PROTOTYPE:           void ApplCbdWrpNetworkStartIndication( void ) or
|                      void ApplCbdWrpNetworkStartIndication( const Nm_ChannelHandleType nmChannelHandle )
| CALLED BY:           NM CANbedded Wrapper (task level)
| PRECONDITIONS:
| INPUT PARAMETERS:    nmChannelHandle:  NM channel
| RETURN VALUE:        void
| DESCRIPTION:         Informs the CCL about the event wake up via a CAN message
|*************************************************************************/
void  ApplCbdWrpNetworkStartIndication( CBDWRP_CHANNEL_APPLTYPE_ONLY )
{
  if( cclNmState[CCL_NM_CBD_WRP_CHANNEL_INDEX] < kCclStateGoToSleep )
  {
#  if defined(CCL_USE_REQUEST_SETEXTCOM_FCT)
    if(cclExtCanWakeUpReq[CCL_NM_CBD_WRP_CHANNEL_INDEX] == kCclNoExtChWupReq)
    {   
      if( cclNmState[CCL_NM_CBD_WRP_CHANNEL_INDEX] == kCclNmStateSleep )
      {
#      if(kCclNrOfChannels > 1)      
        if (CclExtCanComReqFctTbl[CCL_NM_CBD_WRP_CHANNEL_INDEX] != V_NULL)
        {
          /* By using the following table of function calls, code-doubled functions 
          * are called from the indexed CCL. This is done to simplify the called 
           * functions (no distinction of the parameter 'channel' is necessary). */
          (CclExtCanComReqFctTbl[CCL_NM_CBD_WRP_CHANNEL_INDEX])();
        }
#      else
        CclExtCanComReqFct();
#      endif
      }
    }
#  endif

    (void)Nm_PassiveStartUp(CCL_NM_CBD_WRP_CHANNEL_INDEX);

    cclNmState[CCL_NM_CBD_WRP_CHANNEL_INDEX] = kCclNmStateGoToSleep;
  }
}

/************************************************************************
| NAME:                ApplCbdWrpStateChange
| CALLED BY:           NM CANbedded Wrapper (task level)
| PRECONDITIONS:       -
| DESCRIPTION:         Notifies the CCL that the NM state has changed
|*************************************************************************/
void ApplCbdWrpStateChange(NetworkHandleType nmChannelHandle, Nm_StateType nmPreviousState, Nm_StateType nmCurrentState )
{
  if( (nmPreviousState == NM_STATE_PREPARE_BUS_SLEEP) && (nmCurrentState == NM_STATE_REPEAT_MESSAGE ) )
  {
    if( cclNmState[nmChannelHandle] == kCclStateWaitBusSleep )
    { 
      /* the CCL state is WaitBusSleep: this indicates a reception of a NM message, call CclWakeUp to set the external request flag: */    
     /* ESCAN00025693 */
#  if defined(C_ENABLE_MULTICHANNEL_API) /* ESCAN00028126 */
      ApplCanWakeUp((CanChannelHandle)nmChannelHandle);
#  else
      ApplCanWakeUp();
#  endif
#  if defined ( CCL_ENABLE_EMC_WAKEUP )
      /* With EMC handling active ApplCanWakeUp() only sets ExtEmcWakeUp flag.
         Set ExtCanWakeUp flag to assure correct handling in CclTask. */
      cclExtCanWakeUpReq[nmChannelHandle] = kCclExtChWupReq;
#  endif
    }

    /* resume the communication: */
    CclComResume(CCL_NM_CBD_WRP_CHANNEL_PARA);
  }

  if( (nmPreviousState == NM_STATE_BUS_SLEEP) && (nmCurrentState == NM_STATE_REPEAT_MESSAGE ) )
  {     
    CclCanNormal(CCL_NM_CBD_WRP_CHANNEL_PARA);
    CclComStart(CCL_NM_CBD_WRP_CHANNEL_PARA);
  }
}

/************************************************************************
| NAME:                ApplCbdWrpBusSleep
| PROTOTYPE:           void ApplCbdWrpBusSleep( void ) or
|                      void ApplCbdWrpBusSleep( const Nm_ChannelHandleType nmChannelHandle )
| CALLED BY:           NM CANbedded Wrapper (task level)
| PRECONDITIONS:
| INPUT PARAMETERS:    nmChannelHandle:  NM channel
| RETURN VALUE:        void
| DESCRIPTION:         Set the CAN controller and the CAN transceiver in SLEEP mode
|                      and enables the external wakeup port INT.
|*************************************************************************/
void  ApplCbdWrpBusSleep( CBDWRP_CHANNEL_APPLTYPE_ONLY )
{
  CclComStop(CCL_NM_CBD_WRP_CHANNEL_PARA);
  CclCanStandby(CCL_NM_CBD_WRP_CHANNEL_PARA);
}

/************************************************************************
| NAME:                ApplCbdWrpNetStart
| PROTOTYPE:           void ApplCbdWrpNetStart( void )
|                      void ApplCbdWrpNetStart( const Nm_ChannelHandleType channel )
| CALLED BY:           NM CANbedded Wrapper (task level)
| PRECONDITIONS:
| INPUT PARAMETERS:    nmChannelHandle:  NM channel
| RETURN VALUE:        void
| DESCRIPTION:         Set the CAN controller and the CAN transceiver in NORMAL mode
|                      and disable the external wakeup port INT.
|*************************************************************************/
void  ApplCbdWrpNetStart( CBDWRP_CHANNEL_APPLTYPE_ONLY )
{
  if(cclNmState[CCL_NM_CBD_WRP_CHANNEL_INDEX] == kCclStateWaitBusSleep)
  {
    /* CCL is in wait bus sleep and the network management
     * is woken up by a NM message
     */
    ApplCanWakeUp(CCL_NM_CBD_WRP_CHANNEL_PARA);
#  if defined ( CCL_ENABLE_EMC_WAKEUP )
    /* With EMC handling active ApplCanWakeUp() only sets ExtEmcWakeUp flag.
       Set ExtCanWakeUp flag to assure correct handling in CclTask. */
    cclExtCanWakeUpReq[CCL_NM_CBD_WRP_CHANNEL_INDEX] = kCclExtChWupReq;
#  endif
  }
  CclCanNormal(CCL_NM_CBD_WRP_CHANNEL_PARA);
}

/************************************************************************
| NAME:                ApplCbdWrpEnableCom
| PROTOTYPE:           void ApplCbdWrpEnableCom( void )
|                      void ApplCbdWrpEnableCom( const Nm_ChannelHandleType channel )
| CALLED BY:           NM CANbedded Wrapper (task level)
| PRECONDITIONS:
| INPUT PARAMETERS:    nmChannelHandle:  NM channel
| RETURN VALUE:        void
| DESCRIPTION:         Start the communication via interaction layer.
|*************************************************************************/
void  ApplCbdWrpEnableCom( CBDWRP_CHANNEL_APPLTYPE_ONLY )
{
#  if defined(V_ENABLE_USE_DUMMY_STATEMENT)
#    if ( kCbdWrpNumberOfChannels > 1u )
  (void)nmChannelHandle; /* PRQA S 3112 */ /* MD_Ccl_3112 */
#    endif
#  endif
}

/************************************************************************
| NAME:                ApplCbdWrpDisableCom
| PROTOTYPE:           void ApplCbdWrpDisableCom( void )
|                      void ApplCbdWrpDisableCom( const Nm_ChannelHandleType channel )
| CALLED BY:           NM CANbedded Wrapper (task level)
| PRECONDITIONS:
| INPUT PARAMETERS:    nmChannelHandle:  NM channel
| RETURN VALUE:        void
| DESCRIPTION:         Stop the communication via interaction layer.
|*************************************************************************/
void  ApplCbdWrpDisableCom( CBDWRP_CHANNEL_APPLTYPE_ONLY )
{
  CclComWait(CCL_NM_CBD_WRP_CHANNEL_PARA);

  cclNmState[CCL_NM_CBD_WRP_CHANNEL_INDEX] = kCclStateWaitBusSleep;
}

/************************************************************************
| NAME:                ApplCbdWrpNetStop
| PROTOTYPE:           void ApplCbdWrpNetStop( void ) or
|                      void ApplCbdWrpNetStop( const Nm_ChannelHandleType channel )
| CALLED BY:           NM CANbedded Wrapper (task level)
| PRECONDITIONS:
| INPUT PARAMETERS:    nmChannelHandle:  NM channel
| RETURN VALUE:        void
| DESCRIPTION:         s. ApplCbdWrpDisableCom
|*************************************************************************/
void  ApplCbdWrpNetStop( CBDWRP_CHANNEL_APPLTYPE_ONLY )
{
#  if defined(V_ENABLE_USE_DUMMY_STATEMENT)
#    if ( kCbdWrpNumberOfChannels > 1u )
  (void)nmChannelHandle; /* PRQA S 3112 */ /* MD_Ccl_3112 */
#    endif
#  endif
}

/************************************************************************
| NAME:                ApplCbdWrpBusOffStart
| PROTOTYPE:           void ApplCbdWrpBusOffStart( void ) or
|                      void ApplCbdWrpBusOffStart( const Nm_ChannelHandleType channel )
| CALLED BY:           NM CANbedded Wrapper (task level)
| PRECONDITIONS:
| INPUT PARAMETERS:    nmChannelHandle:  NM channel
| RETURN VALUE:        void
| DESCRIPTION:         The CCL handles the configured interaction layer in
|                      dependency of the CCL configuration.
|*************************************************************************/
void  ApplCbdWrpBusOffStart( CBDWRP_CHANNEL_APPLTYPE_ONLY )
{
  CclBusOffStart(CCL_NM_CBD_WRP_CHANNEL_PARA);
}

/************************************************************************
| NAME:                ApplCbdWrpBusOffEnd
| PROTOTYPE:           void ApplCbdWrpBusOffEnd( void ) or
|                      void ApplCbdWrpBusOffEnd( const Nm_ChannelHandleType channel )
| CALLED BY:           NM CANbedded Wrapper (task level)
| PRECONDITIONS:
| INPUT PARAMETERS:    nmChannelHandle:  NM channel
| RETURN VALUE:        void
| DESCRIPTION:         The CCL handles the configured interaction layer in
|                      dependency of the CCL configuration.
|*************************************************************************/
void  ApplCbdWrpBusOffEnd( CBDWRP_CHANNEL_APPLTYPE_ONLY )
{
  CclBusOffEnd(CCL_NM_CBD_WRP_CHANNEL_PARA);
}

# if defined (CCL_ENABLE_ERROR_HOOK)
#  if defined ( CBDWRP_ENABLE_ASSERTIONS ) || \
  ( (!defined ( CBDWRP_ENABLE_ASR_ERROR_REPORT ) ) && \
  ( ( NM_DEV_ERROR_DETECT == STD_ON ) || ( CANNM_DEV_ERROR_DETECT == STD_ON ) ) )
/************************************************************************
| NAME:                ApplCbdWrpFatalError
| CALLED BY:           NM CANbedded Wrapper (task level)
| PRECONDITIONS:
| DESCRIPTION:         The NM CANbedded Wrapper reports a development error
|*************************************************************************/
void ApplCbdWrpFatalError( CBDWRP_CHANNEL_APPLTYPE_FIRST V_MEMROM1 vuint8 V_MEMROM2 moduleId, V_MEMROM1 vuint8 V_MEMROM2 errorCode )
{
  switch(moduleId)
  {
    case kCbdWrpModuleIdNm:
      CclFatalError((CanChannelHandle)CCL_NM_CBD_WRP_CHANNEL_INDEX, (vuint16)errorCode, 0, kComponentNmAsrGeneric);
      break;

    case kCbdWrpModuleIdCanNm:
      CclFatalError((CanChannelHandle)CCL_NM_CBD_WRP_CHANNEL_INDEX, (vuint16)errorCode, 0, kComponentNmAsrCan);
      break;

    case kCbdWrpModuleIdCbdWrp:
      CclFatalError((CanChannelHandle)CCL_NM_CBD_WRP_CHANNEL_INDEX, (vuint16)errorCode, 0, kComponentNmCbdWrp);
      break;

    default:
      ; /* semicolon exists to satisfy QAC */
      break;
  }
}
#  endif
# endif
#endif

#if defined( NMHDLAN_NM_TYPE )
/************************************************************************
| NAME:                ApplNmHdLanBusStop
| PROTOTYPE:           void ApplNmHdLanBusStop( CanChannelHandle canChannel )
| CALLED BY:           NmHdLan in NmHdLanTask() when NetworkOff state is entered.
| PRECONDITIONS:       -
| INPUT PARAMETERS:    canChannel
| RETURN VALUE:        -
| DESCRIPTION:         Stops communication, sets the CAN controller
|                      and the CAN transceiver in SLEEP mode and enables
|                      the external wakeup port INT.
|*************************************************************************/
void ApplNmHdLanBusStop( CanChannelHandle canChannel )
{
# if( kCclNrOfChannels > 1 )
  CanChannelHandle channel = canChannel;
# else
#  if defined(V_ENABLE_USE_DUMMY_STATEMENT)
  (void)canChannel;  /* PRQA S 3112 */ /* MD_Ccl_3112 */
#  endif
# endif
  cclNmCommunicationState[CCL_CHANNEL_CCLINDEX] = kCclNmCommunicationSuspended;
  CclComStop( CCL_CHANNEL_CCLPARA_ONLY );
  CclCanStandby( CCL_CHANNEL_CCLPARA_ONLY );
}

/************************************************************************
| NAME:                ApplNmHdLanBusStart
| PROTOTYPE:           void ApplNmHdLanBusStart( CanChannelHandle canChannel )
| CALLED BY:           NmHdLan in NmHdLanTask() when NetworkOff state is left.
| PRECONDITIONS:       -
| INPUT PARAMETERS:    canChannel
| RETURN VALUE:        -
| DESCRIPTION:         Set the CAN controller and the CAN transceiver in NORMAL mode
|                      and disable the external wakeup port INT.
|*************************************************************************/
void ApplNmHdLanBusStart( CanChannelHandle canChannel )
{
# if( kCclNrOfChannels > 1 )
  CanChannelHandle channel = canChannel;
# else
#  if defined(V_ENABLE_USE_DUMMY_STATEMENT)
  (void)canChannel;  /* PRQA S 3112 */ /* MD_Ccl_3112 */
#  endif
# endif
  CclCanNormal(CCL_CHANNEL_CCLPARA_ONLY);

  if( cclNmState[CCL_CHANNEL_CCLINDEX] < kCclStateGoToSleep )
  {
    if( cclNmState[CCL_CHANNEL_CCLINDEX] == kCclNmStateSleep )
    {
# if defined(CCL_USE_REQUEST_SETEXTCOM_FCT)
      if(cclExtCanWakeUpReq[CCL_CHANNEL_CCLINDEX] == kCclNoExtChWupReq)
      {
#  if ( kCclNrOfChannels > 1 )
        if (CclExtCanComReqFctTbl[CCL_CHANNEL_CCLINDEX] != V_NULL)
        {
          /* By using the following table of function calls, code-doubled functions 
           * are called from the indexed CCL. This is done to simplify the called 
           * functions (no distinction of the parameter 'channel' is necessary). */
          (CclExtCanComReqFctTbl[CCL_CHANNEL_CCLINDEX])();
        }
#  else
        CclExtCanComReqFct();
#  endif
      }
# endif
    }

    cclNmState[CCL_CHANNEL_CCLINDEX] = kCclNmStateGoToSleep;
  }
}

# if defined( NMHDLAN_ENABLE_BUSOFFSTART_FCT )
/************************************************************************
| NAME:               ApplNmHdLanBusOffStart
| PROTOTYPE:          void ApplNmHdLanBusOffStart( CanChannelHandle canChannel )
| CALLED BY:          NmHdLan in CAN Error/BusOff interrupt.
| PRECONDITIONS:      -
| INPUT PARAMETERS:   canChannel
| RETURN VALUE:       -
| DESCRIPTION:        Calls the corresponding application function to notify
|                     a BusOff has occurred. If IL-timeout check is disabled
|                     corresponding wait-functions are called to stop the
|                     timeout counter.
|*************************************************************************/
void ApplNmHdLanBusOffStart( CanChannelHandle canChannel )
{
#  if( kCclNrOfChannels > 1 )
  CanChannelHandle channel = canChannel;
#  else
#   if defined(V_ENABLE_USE_DUMMY_STATEMENT)
  (void)canChannel;  /* PRQA S 3112 */ /* MD_Ccl_3112 */
#   endif
#  endif
  CclBusOffStart(CCL_CHANNEL_CCLPARA_ONLY);
}
# endif

# if defined( NMHDLAN_ENABLE_BUSOFFEND_FCT )
/************************************************************************
| NAME:               ApplNmHdLanBusOffEnd
| PROTOTYPE:          void ApplNmHdLanBusOffEnd( CanChannelHandle canChannel )
| CALLED BY:          NmHdLan in NmHdLanTask()
| PRECONDITIONS:      BusOff pending
| INPUT PARAMETERS:   canChannel
| RETURN VALUE:       -
| DESCRIPTION:        Call the corresponding application function.
|                     If IL-timeout check during BusOff is disabled 
|                     corresponding release-functions are called to start the
|                     timeout counter again.
|*************************************************************************/
void ApplNmHdLanBusOffEnd( CanChannelHandle canChannel )
{
#  if( kCclNrOfChannels > 1 )
  CanChannelHandle channel = canChannel;
#  else
#   if defined(V_ENABLE_USE_DUMMY_STATEMENT)
  (void)canChannel;  /* PRQA S 3112 */ /* MD_Ccl_3112 */
#   endif
#  endif
  CclBusOffEnd(CCL_CHANNEL_CCLPARA_ONLY);
}
# endif

/************************************************************************
| NAME:               ApplNmHdLanStartTransmission
| PROTOTYPE:          void ApplNmHdLanStartTransmission( CanChannelHandle canChannel )
| CALLED BY:          NmHdLan in NmHdLanTask() when NetworkOn state is entered.
| PRECONDITIONS:      -
| INPUT PARAMETERS:   canChannel
| RETURN VALUE:       -
| DESCRIPTION:        Function is called by NmHdLan when state NetworkOn is entered.
|                     Enables Communication.
|*************************************************************************/
void ApplNmHdLanStartTransmission( CanChannelHandle canChannel )
{
# if( kCclNrOfChannels > 1 )
  CanChannelHandle channel = canChannel;
# else
#  if defined(V_ENABLE_USE_DUMMY_STATEMENT)
  (void)canChannel;  /* PRQA S 3112 */ /* MD_Ccl_3112 */
#  endif
# endif
  if( cclNmCommunicationState[CCL_CHANNEL_CCLINDEX] == kCclNmCommunicationWait )
  {
    CclComResume(CCL_CHANNEL_CCLPARA_ONLY);
  }
  else
  {
    CclComStart(CCL_CHANNEL_CCLPARA_ONLY);
  }
  cclNmCommunicationState[CCL_CHANNEL_CCLINDEX] = kCclNmCommunicationRunning;
}

/************************************************************************
| NAME:               ApplNmHdLanStopTransmission
| PROTOTYPE:          void ApplNmHdLanStopTransmission( CanChannelHandle canChannel )
| CALLED BY:          NmHdLan in NmHdLanTask()
| PRECONDITIONS :     -
| INPUT PARAMETERS:   canChannel
| RETURN VALUE :      -
| DESCRIPTION :       Function is called by NmHdLan when state NetworkSilent is entered.
|                     Stops Communication.
|*************************************************************************/
void ApplNmHdLanStopTransmission( CanChannelHandle canChannel )
{
# if( kCclNrOfChannels > 1 )
  CanChannelHandle channel = canChannel;
# else
#  if defined(V_ENABLE_USE_DUMMY_STATEMENT)
  (void)canChannel;  /* PRQA S 3112 */ /* MD_Ccl_3112 */
#  endif
# endif
  cclNmState[CCL_CHANNEL_CCLINDEX] = kCclStateWaitBusSleep;
  cclNmCommunicationState[CCL_CHANNEL_CCLINDEX] = kCclNmCommunicationWait;
  CclComWait( CCL_CHANNEL_CCLPARA_ONLY );
}

# if defined( NMHDLAN_ENABLE_SOFTWARE_CHECK )
#  if defined( CCL_ENABLE_ERROR_HOOK )
/************************************************************************
| NAME:               ApplNmHdLanFatalError
| PROTOTYPE:          void ApplNmHdLanFatalError( CanChannelHandle canChannel, vuint8 error )
| CALLED BY:          NmHdLan
| PRECONDITIONS:      -
| INPUT PARAMETERS:   canChannel, error code
| RETURN VALUE:       -
| DESCRIPTION :       Notifies the CCL about a fatal error in NmHdLan
|*************************************************************************/
void ApplNmHdLanFatalError( CanChannelHandle canChannel, vuint8 error )
{
  CclFatalError(canChannel, (vuint16)error, 0, kComponentNmHdLan);
}
#  endif
# endif
#endif

/* module specific MISRA deviations:
 MD_Ccl_3112:
      Reason:     Dummy statement to avoid compiler warnings.
      Risk:       There is no risk as such statements have no effect on the code.
      Prevention: Covered by code review.
*/

/************   Organi, Version 3.9.1 Vector-Informatik GmbH  ************/

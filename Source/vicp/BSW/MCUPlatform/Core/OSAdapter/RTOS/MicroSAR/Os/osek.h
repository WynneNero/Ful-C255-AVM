/* Kernbauer Version: 2.16 Konfiguration: RH850 Erzeugungsgangnummer: 214 Zweig: 1 */

/*****************************************************************************
| Project Name: MICROSAR OS
|    File Name: osek.h
|
|  General code: @Version: 9.01.04@
|  Module version: $vv$=2.27
|
|  Description: contains osek prototypes and defines
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2000-2015 Vector Informatik GmbH          All rights reserved.
|****************************************************************************/

/* CovComment 0:  file: osek.h */
















/* MISRA RULE 19.15 VIOLATION: The QAC-Tool states a violation of rule 19.15 with 
 * message 0883 below. Anyhow, there is a double include prevention and therefore,
 * the message is considered to be wrong. */
/* double include preventer */
#ifndef _OSEK_H      /* PRQA S 0883 EOF */ /* see MISRA comment above */
#define _OSEK_H

/*lint -save Messages inhibited in this file, will be re-enabled at the end of file */
/*lint -e539 Did not expect positive indentation */

#if defined __cplusplus
extern "C"
{
#endif

/* Vector release management */
#if defined USE_QUOTE_INCLUDES
 #include "vrm.h"
#else
 #include <vrm.h>
#endif
/* KB begin vrmReleaseNumber (overwritten) */
/* Source release number */
#define osdVrmMajRelNum 1
#define osdVrmMinRelNum 6
/* KB end vrmReleaseNumber */
#if defined USE_QUOTE_INCLUDES
 #include "vrm.h"
#else
 #include <vrm.h>
#endif

/* autosar conformant information publishing */
#define OS_VENDOR_ID 30        /*Autosar/HIS vendor ID Vector-Informatik*/
#define OS_MODULE_ID 0x01

#define OS_AR_RELEASE_MAJOR_VERSION 4
#define OS_AR_RELEASE_MINOR_VERSION 0
#define OS_AR_RELEASE_REVISION_VERSION 3
/* KB begin vrmReleaseNumber (overwritten) */
/* Source release number */
#define osdVrmMajRelNum 1
#define osdVrmMinRelNum 6
/* KB end vrmReleaseNumber */
#define OS_SW_MAJOR_VERSION osdVrmMajRelNumRef
#define OS_SW_MINOR_VERSION osdVrmMinRelNumRef
/* KB begin AutosarPatchVersion (default) */
#define OS_SW_PATCH_VERSION 0
/* KB end AutosarPatchVersion */

/* KB begin osekDefaultConstants (default) */
/* defines for all conformance classes */
#define BCC1   1U
#define BCC2   2U
#define ECC1   3U
#define ECC2   4U

/* and for all scalability classes */
#define SC1    1U
#define SC2    2U
#define SC3    3U
#define SC4    4U

#define STANDARD_STATUS 0U
#define EXTENDED_STATUS 1U

#define osdFALSE 0U
#define osdTRUE  1U

#define osdNULL ((osqPROM1 osqPROM2 void osqPROM3 *)0)

/* state of tasks */
#define PRE_READY       0
#define RUNNING         1
#define WAITING         2
#define READY           3
#define SUSPENDED       4
#define WAIT_SEMAPHORE  5

/* return codes for protection hook */
#ifndef OS_SUPPRESS_PROTHOOK_OLD_RET_VALS
#define PRO_KILLTASKISR           1U
#define PRO_KILLAPPL              2U
#define PRO_KILLAPPL_RESTART      3U
#endif /*OS_SUPPRESS_PROTHOOK_OLD_RET_VALS*/
#define PRO_TERMINATETASKISR      1U
#define PRO_TERMINATEAPPL         2U
#define PRO_TERMINATEAPPL_RESTART 3U
#define PRO_SHUTDOWN              4U
#define PRO_IGNORE                5U

/* KB end osekDefaultConstants */

/* OS type definitions */
/* KB begin osTypeDefinitions (default) */
typedef unsigned char  osuint8;
typedef unsigned short osuint16;
typedef unsigned long  osuint32;
typedef signed   char  osint8;
typedef signed   short osint16;
typedef signed   long  osint32;
/* KB end osTypeDefinitions */

/* Boolean definition */
/* KB begin osekBooleanDef (overwritten) */
#ifndef osbool
#define osbool osuint8
#endif
/* KB end osekBooleanDef */

/* Type for boolean arrays */
/* KB begin osekBooleanArrayBaseTypeDef (default) */
typedef osbool osBoolArrayBaseType;
/* KB end osekBooleanArrayBaseTypeDef */


/* Are we in a PRQA/QAC/MISRA-check? */
#ifdef PRQA_PTRDIFF_T
 /* YES: Perform some adaptations to the OS */
 /* First the general adaptations: */
 #pragma PRQA_NO_RETURN osAbortSystem
 #pragma PRQA_NO_RETURN osAssertFailed
 #pragma PRQA_NO_RETURN osSysShutdownOS

 /* Then possible plattform specific adaptations: */
 /* KB begin osekHWosPrqaAdaptation (default) */
 /* no platform specific adaptations for PRQA/QAC */
 /* KB end osekHWosPrqaAdaptation */
#endif

/* Known Compilers */
/* KB begin osekCompilerDefines (overwritten) */
/* KB end osekCompilerDefines */


   #if defined USE_QUOTE_INCLUDES
    #include "tcb.h"  /* include before */
   #else
    #include <tcb.h>  /* include before */
   #endif



/* KB begin osekStartOfHModule (overwritten) */
/* KB end osekStartOfHModule */

/* KB begin osekHwMemoryQualifierDefines (overwritten) */

/* define to nothing in the default case */

/* osqROM0 osqROM1 const osqROM2 osVersionVariantCodingType osqROM3 oskVersionVariant; */
#define osqROM0
#define osqROM1
#define osqROM2
#define osqROM3

/* extern osqPROM1 const osqPROM2 char osqPROM3 * osqROM1 const osqROM2 osqROM3 oskTcbTaskName[osdNumberOfAllTasks]; */
#define osqPROM1
#define osqPROM2
#define osqPROM3

/* osqRAM1 volatile osqRAM2 TickType osqRAM3 osSystemCounter; */
/* osqRAM1 osqRAM2 osDispatcherLockType osqRAM3 osLockDispatcher; */
#define osqRAM0
#define osqRAM1 
#define osqRAM2 
#define osqRAM3 

/* osqPRAM1 char osqPRAM2 * osqPRAM3 osActiveTaskModule; */
#define osqPRAM1
#define osqPRAM2
#define osqPRAM3

/* osqBOOL1 volatile osqBOOL2 osbool osqBOOL3 osStartDispatcher; */
#define osqBOOL1 
#define osqBOOL2 
#define osqBOOL3 

/* osqTcbRAM1 volatile osqTcbRAM2 TickType osqTcbRAM3 osCounter[5]; */
/* extern osqTcbRAM1 osqTcbRAM2 osQEntryCountType osqTcbRAM3 osQReadyTaskHead[osdNumberOfPriorities]; */
#define osqTcbRAM1 
#define osqTcbRAM2 
#define osqTcbRAM3 

/* extern (osqPTcbRAM1 osqPTcbRAM2 TaskType osqPTcbRAM3 *) osqROM1 const osqROM2 osqROM3 oskQActivationQueues[osdNumberOfPriorities]; */
#define osqPTcbRAM1 
#define osqPTcbRAM2 
#define osqPTcbRAM3 

/* osqStack1 osqStack2 osStackDataType osqStack3 osTaskStack1[80]; */
#define osqStack1
#define osqStack2
#define osqStack3

/* osqFunc1 void osqFunc2 Function1(void); */
#define osqFunc1
#define osqFunc2 

#define osqScRAM0 
#define osqScRAM1 
#define osqScRAM2 
#define osqScRAM3 
#define osqScPRAM1
#define osqScPRAM2
#define osqScPRAM3

/* qualifiers for inline functions (one qualifier for each function) */
#define osqInlineGetHighPrioBit inline
/* KB end osekHwMemoryQualifierDefines */

/* include hardware specific header files before OSEK Typedefinitions */
/* KB begin osekHWincludeHwHeaderPreTypes (overwritten) */
#if defined USE_QUOTE_INCLUDES
#include "osDerivatives.h"
#else
#include <osDerivatives.h>
#endif
/* KB end osekHWincludeHwHeaderPreTypes */

#if defined USE_QUOTE_INCLUDES
 #include "osekcov.h"
 #include "osekasrt.h" /* posix types must be defined      */
 #include "osekerr.h"  /* definitions of all error numbers */
#else
 #include <osekcov.h>
 #include <osekasrt.h> /* posix types must be defined      */
 #include <osekerr.h>  /* definitions of all error numbers */
#endif

/* KB begin osekTypedDefaultConstants (default) */
#define INVALID_ISR           ((ISRType)(0xFFFFFFFFUL))
#define INVALID_TASK          ((TaskType)(0xFFFFFFFFUL))
#define INVALID_OSAPPLICATION ((ApplicationType)0xFFU)
#define INVALID_SCHEDULETABLE ((ScheduleTableType)(0xFFFFFFFFUL))
#define INVALID_PROCESS       (((osProcessType)(0xFFFFFFFFUL)))

/* TR:SASR40:6011 Start */
#define APPLICATION_ACCESSIBLE ((ApplicationStateType)1)
#define APPLICATION_RESTARTING ((ApplicationStateType)2)
#define APPLICATION_TERMINATED ((ApplicationStateType)3)
/* TR:SASR40:6011 End */

/* idle definition for task */
#define osdNoActiveTask       INVALID_TASK
/* idle definition for prio */
#define osdNoActivePrio       ((osPrioType)(0xFFFFFFFFUL))
/* idle definition for resource list */
#define osdNoResource         ((ResourceType)(0xFFFFFFFFUL))

/* idle definition for semaphore list */
#define osdNoSemaphore   ((osSemaphoreType)(0xFFFFFFFFUL))

/* KB end osekTypedDefaultConstants */
/* access rights */
#define NO_ACCESS 0U
#define ACCESS 1U


/* Schedule Table status confirms to AS 3.0 */

#define SCHEDULETABLE_STOPPED                 0U
#define SCHEDULETABLE_NEXT                    1U
#define SCHEDULETABLE_WAITING                 2U
#define SCHEDULETABLE_RUNNING                 3U
#define SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS 4U

/* values for AccessType */
#define oskAccess_None 0x0U
#define oskAccess_Read 0x1U
#define oskAccess_Write 0x2U
#define oskAccess_Execute 0x4U
#define oskAccess_Stack 0x8U

/* macros for AccessType */
#define OSMEMORY_IS_READABLE(x) (((x) & oskAccess_Read)? 1 : 0)
#define OSMEMORY_IS_WRITEABLE(x) (((x) & oskAccess_Write)? 1 : 0)
#define OSMEMORY_IS_EXECUTABLE(x) (((x) & oskAccess_Execute)? 1 : 0)
#define OSMEMORY_IS_STACKSPACE(x) (((x) & oskAccess_Stack)? 1 : 0)

/* values for RestartType */
#define RESTART    1
#define NO_RESTART 2

/* SCHEDULETABLE AUTOSTART TYPE */
#define osdScheduleTableAutostartNO                  0U
#define osdScheduleTableAutostartABSOLUT             1U
#define osdScheduleTableAutostartRELATIVE            2U
#define osdScheduleTableAutostartSYNCHRON            3U

/* ALARM AUTOSTART TYPE */
#define osdAlarmAutostartNO                          0U
#define osdAlarmAutostartABSOLUTE                    1U
#define osdAlarmAutostartRELATIVE                    2U

#define OSINVALIDAPPMODE                             0U

/* KB begin osekHwTASKmacro (overwritten) */
/* OSEK-conform task-function-macro */
#define TASK(x) void x##func(void)
/* KB end osekHwTASKmacro */
/* KB begin osekHWISRmacro (default) */
/* OSEK-conform interrupt-function-macro */
#define ISR(x) void x##func(void)
/* KB end osekHWISRmacro */
/* KB begin osekHWAlrmCallbckmacro (default) */
/* OSEK-conform function-macro for alarm callbacks */
#define ALARMCALLBACK(x) void x(void)
/* KB end osekHWAlrmCallbckmacro */
/* Default application mode is generated (OSEK 2.2) */


/* implementation specific constants */
/* KB begin osekConstants (overwritten) */

#define osdPrioBitsPerWord       32
#define osdIntAPIMaxNesting      (osdIntAPIDisableAll-1)

#ifndef OS_CHECK_INTAPISTATUS
#define OS_CHECK_INTAPISTATUS 1
#endif

#ifndef osdRH850_FPU
#define osdRH850_FPU 0
#endif

#ifndef osdUseFEINT
#define osdUseFEINT 0
#endif
/* KB end osekConstants */



/* KB begin osekTickTypeDef (default) */
typedef osuint32             TickType;
typedef osint32              osTickTimeDiffType;
/* KB end osekTickTypeDef */

/* KB begin osekAditionalTypeDef (default) */

    
/* implementation specific types (OSEK types) */
/* KB begin osekTypes (overwritten) */
/*
    !!! Max priorities: Min(2^(sizeof(osPrioType)*8), 2^(sizeof(osPrioOffsetType)*8) * sizeof(osPrioFlagType)*8)
*/
typedef osuint16      osPrioType;         /* has to be unsigned (invalid is higher than others) */
typedef osuint8       osPrioOffsetType;

typedef osuint32      osStdFlagType; /* Standard-Flag-Type e.g. for AutoStartFlagField of alarms */

typedef osStdFlagType osPrioFlagType;

typedef osStdFlagType osResAccessMaskType;

typedef osuint32            osIntLevelType;      /* also used for level mask */
typedef osuint8             osTaskPreemptionType;
typedef osuint8             osTaskFlagType;
typedef osuint16            osQEntryCountType;
typedef osuint8             osActivationCountType;
typedef osuint32            osStackDataType;  
typedef osuint16            osStackSizeType;      /* maximum stacksize is 64k */
typedef osuint16            osTaskIndexType;  
typedef osuint16            osResourceIndexType;  

typedef osuint16            osTIPType;
typedef osTIPType           osAlarmIndexType; 
typedef osAlarmIndexType    AlarmType;
typedef osAlarmIndexType     *osAlarmIndexRefType;
typedef osTIPType           ScheduleTableType;
/* KB end osekTypes */

/* Autosar types */
/* KB begin atosTypes (overwritten) */
typedef osuint16                 osProcessType;
typedef osuint16                 ISRType;
typedef osuint8                  ScheduleTableStatusType;
typedef ScheduleTableStatusType* ScheduleTableStatusRefType;
typedef osuint8                  RestartType;
typedef osuint16                 CounterType;
typedef osuint32                 PhysicalTimeType;
#ifdef _MSC_VER
typedef unsigned __int64         osTPTimeStampType;
#else
typedef unsigned long long       osTPTimeStampType;
#endif
typedef osTPTimeStampType*       osTPTimeStampRefType;
typedef osuint32                 osTPTimeType;
typedef osTPTimeType*            osTPTimeRefType;

typedef osuint8                  osMPUAreaType;
typedef osuint8                  osMPUAttributesType;

typedef osuint32                 osMiniLockType;
typedef osMiniLockType*          osMiniLockRefType;
typedef osuint32                 CoreIdType;


typedef double                   osTimeComputationType;/* used in macros for conversion between time and ticks to avoid usage of basic type */
/* KB end atosTypes */

/* KB begin applicationTypeDef (overwritten) */
#ifndef _MSC_VER
typedef osuint8                          ApplicationType;
#endif
/* KB end applicationTypeDef */

/* KB begin osekOSEKTypes (overwritten) */
typedef osTaskIndexType     TaskType;
typedef osResourceIndexType ResourceType;
typedef osuint16            osSemaphoreType;

typedef osuint8             osRTSizeType; /* typedef for library */
typedef osuint16            osSystemTimerReloadValueType;
typedef osuint32            EventMaskType;
#define osdEventMaskTypeSize    4
#define osdMaxAllowedTimeStamp  0xffffffffffffffffU
/* KB end osekOSEKTypes */
/* KB begin osekDispatcherLockType (default) */
typedef osuint8               osDispatcherLockType;
/* KB end osekDispatcherLockType */

#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED
typedef osuint8               StatusType;
#define E_OK 0
#endif

typedef osuint8              TaskStateType;
typedef osuint8              AppModeType;
typedef TaskType            *TaskRefType;
typedef TaskStateType       *TaskStateRefType;
typedef TickType            *TickRefType;
typedef EventMaskType       *EventMaskRefType;
typedef ISRType             *ISRRefType;

/* Schedule Table related */
typedef TickType osSTOffsetType;
typedef TickType GlobalTimeTickType;
typedef osuint16 osSTIndexType;

typedef osuint8               ApplicationStateType;    /* TR:SASR40:6010 */
typedef ApplicationStateType *ApplicationStateRefType; /* TR:SASR40:6012 */




/* KB end osekAditionalTypeDef */

/* KB begin osekDefaultTypes (default) */
/* KB begin osekHWosTaskFctType (overwritten) */
typedef void                (*osTaskFctType)(void);
typedef void                (*osIsrFctType)(void);
/* KB end osekHWosTaskFctType */

typedef osuint16              osStackUsageType;
typedef osuint8               osTaskStateType;
/* KB begin osekHWosStackPtrType (overwritten) */
typedef void       *        osStackPtrType;
typedef void const *        osStackPtrToConstType;

typedef struct {
   osStackPtrType start;
   osStackPtrType end;
} osStackType;
/* KB end osekHWosStackPtrType */
typedef osuint8               osResCounterType;
/* KB end osekDefaultTypes */




/* KB begin osekOSEKdeclarations (default) */
#define DeclareTask(TaskId)     osqRAM0 extern osqRAM1 osqRAM2 TaskType osqRAM3 osNotUsed1##TaskId
#define DeclareResource(ResId)  osqRAM0 extern osqRAM1 osqRAM2 TaskType osqRAM3 osNotUsed2##ResId
#define DeclareEvent(Event)     osqRAM0 extern osqRAM1 osqRAM2 TaskType osqRAM3 osNotUsed3##Event
#define DeclareAlarm(AlarmId)   osqRAM0 extern osqRAM1 osqRAM2 TaskType osqRAM3 osNotUsed4##AlarmId
/* KB end osekOSEKdeclarations */    /* DeclareTask, DeclareAlarm,... */

/* structure for AlarmBase */
typedef struct
{
   TickType maxallowedvalue;/* Maximum possible allowed count value (for example */
                            /* in ticks or angle degrees) */
   TickType ticksperbase;   /* Number of ticks required to reach a counter-specific */
                            /* (significant) unit. */
   TickType mincycle;       /* Minimum allowed number of ticks for a cyclic alarm */
                            /* (only for systems with Extended Status). */
} AlarmBaseType;

typedef AlarmBaseType     *AlarmBaseRefType;

typedef osTIPType         osHeapElementType;
typedef osHeapElementType *osHeapElementRefType;
typedef struct
{
   osHeapElementRefType heap;
   osAlarmIndexRefType  count;
} osHeapType;
typedef osHeapType const * osHeapRefType;

typedef osuint16          OSServiceIdType;
typedef void              (*osAlarmCallbackType)(void);
typedef osuint8           BlockTypeType;





#if (osdClearTIPAbsIdx != -1)
 osqFunc1 void osqFunc2 osClearTimerInterruptPointAbs(CounterType CounterID);
#endif
#if (osdClearTIPRelIdx != -1)
 osqFunc1 void osqFunc2 osClearTimerInterruptPointRel(CounterType CounterID);
#endif
#if (osdSetTIPAbsMaxGtSemiCountIdx != -1)
 osqFunc1 osbool osqFunc2 osSetTIPAbsMaxGtSemiCount(CounterType CounterID, TickType timeToSet);
#endif
#if (osdSetTIPRelMaxGtSemiCountIdx != -1)
 osqFunc1 osbool osqFunc2 osSetTIPRelMaxGtSemiCount(CounterType CounterID, TickType timeToSet);
#endif
#if (osdSetTIPAbsMaxLeSemiCountIdx != -1)
 osqFunc1 osbool osqFunc2 osSetTIPAbsMaxLeSemiCount(CounterType CounterID, TickType timeToSet);
#endif
#if (osdSetTIPRelMaxLeSemiCountIdx != -1)
 osqFunc1 osbool osqFunc2 osSetTIPRelMaxLeSemiCount(CounterType CounterID, TickType timeToSet);
#endif
#if (osdGetCurrentTimeHighResHybridIdx != -1)
 osqFunc1 TickType osqFunc2 osGetCurrentTimeHiResHybrid(CounterType CounterID);
#endif
#if (osdGetCurrentTimeHighResMonoIdx != -1)
 osqFunc1 TickType osqFunc2 osGetCurrentTimeHiResMono(CounterType CounterID);
#endif
#if (osdGetCurrentTimeStdIdx != -1)
 osqFunc1 TickType osqFunc2 osGetCurrentTimeStd(CounterType CounterID);
#endif
#if (osdHandleCounterInterruptStdIdx != -1)
 osqFunc1 void osqFunc2 osHandleCounterInterruptStd(CounterType CounterID);
#endif
#if (osdHandleCounterInterruptHiResIdx != -1)
 osqFunc1 void osqFunc2 osHandleCounterInterruptHiRes(CounterType CounterID);
#endif

#define osdCounterId2HiResCounterId(x)    ((x) -  osdNumberOfSWAndSRCounters)
#define osdIsHiResCounter(x)              ((osdNumberOfSWAndSRCounters == 0) || ((x) >= osdNumberOfSWAndSRCounters))
#define osdCounterId2HwCounterId(x)       ((x) -  osdNumberOfSWCounters)
#define osdIsHwCounter(x)                 ((x) >= osdNumberOfSWCounters)

typedef void (*osClearTimerInterruptPointOpType)(CounterType);
typedef osbool (*osSetTimerInterruptPointOpType)(CounterType, TickType);
typedef TickType (*osGetCurrentTimeOpType)(CounterType);
typedef void (*osHandleCounterInterruptsOpType)(CounterType);
typedef osqFunc1 void osqFunc2 (*osInsertMinHeapOpType)(osHeapElementType newItem, osHeapType const * const h, CounterType ctr);


typedef TickType  osHWTimerCompType;


typedef union
{
   TaskType          osTaskType;
   TaskRefType       osTaskRefType;
   ResourceType      osResourceType;
   EventMaskType     osEventMaskType;
   osTIPType         osAlarmType;
   CounterType       osCounterType;
   ScheduleTableType osScheduleTableType;
   ISRType           osISRType;
   osSemaphoreType   osOsSemaphoreType;
} osAPIParam1Type;

typedef union
{
   TaskStateRefType           osTaskStateRefType;
   EventMaskType              osEventMaskType;
   EventMaskRefType           osEventMaskRefType;
   AlarmBaseRefType           osAlarmBaseRefType;
   TickType                   osTickType;
   TickRefType                osTickRefType;
   ScheduleTableType          osScheduleTableType;
   ScheduleTableStatusRefType osScheduleTableStatusRefType;
   BlockTypeType              osBlockType;
} osAPIParam2Type;

typedef union
{
   TickType     osTickType;
   ResourceType osResourceType;
   TickRefType  osTickRefType;
} osAPIParam3Type;



/* KB begin osHWCtrlVarStruct (default) */
typedef struct
{
   TaskType   ossHighReadyTaskIndex; /* ready task with highest priority */
   osPrioType ossHighReadyTaskPrio;  /* Priority of ready task with highest priority */
   osbool ossStartDispatcher;
#if (CC==BCC2) || (CC==ECC2)
   #if (osdNumberOfPriorities > 0)
      osQEntryCountType ossQReadyTaskHead[osdNumberOfPriorities];
      osQEntryCountType ossQReadyTaskTail[osdNumberOfPriorities];
   #else
      osQEntryCountType ossQReadyTaskHead[1];
      osQEntryCountType ossQReadyTaskTail[1];
   #endif
#else
   #if (osdNumberOfPriorities > 0)
      TaskType ossQReadyTask[osdNumberOfPriorities];
   #else
      TaskType ossQReadyTask[1];
   #endif
#endif
#if (osdRTSize > 1)
   osPrioFlagType ossQReadyPrios[osdRTSize];
#else
   osPrioFlagType ossQReadyPrios;
#endif
}osCtrlVarsLockNeededType;

typedef struct
{
   /* KB begin osekHwSctxCtrlVarsCandidates (default) */
   osuint8 ossIntNestingDepth;
   TaskType ossActiveTaskIndex;    /* indicates the currently running task */
   ISRType ossActiveISRID;     /* Id of the currently running (cat2) ISR */
   osuint8 ossIntSaveDisableCounter;
   osuint8 ossIntSaveDisableCounterGlobal;
   #if (STATUS_LEVEL == EXTENDED_STATUS)
   volatile osuint8 ossIntAPIStatus;
   #endif
   #if (osdNumberOfApplications > 0)
   ApplicationType ossActiveApplicationID;
   #endif
   
   /* KB begin osekHwAdditionalSctxCtrlVarsCandidates (overwritten) */
   volatile osuint8 ossCallDispatcher;
   /* KB end osekHwAdditionalSctxCtrlVarsCandidates */
   /* KB end osekHwSctxCtrlVarsCandidates */
   
   osPrioType ossActiveTaskPrio;     /* Priority of actually active task */
   osIntLevelType ossSavedIntLevel;
   osIntLevelType ossSavedIntLevelNested;
   osbool ossStarted;
  
   /* KB begin osCtrlVarStructVariablesForGlobalDisable (overwritten) */
   osuint32 ossSavedIntDisFlag;
   osuint32 ossSavedIntDisFlagNested;
   /* KB end osCtrlVarStructVariablesForGlobalDisable */

#if (osdFullPreempt || osdMixedPreempt)
   volatile osDispatcherLockType ossLockDispatcher;
#endif
#if osdExceptionDetails
   osint16 ossISRUnhandledException_Number;
#endif
#if ((osdSC == SC3) || (osdSC == SC4))
   osuint16 ossCurrentContext;
   osuint32 ossIsInUserMode;
   osuint8  ossInSystemFct;
#endif
#if (osdNumberOfApplications > 0)
   volatile osbool ossInApplHook;
#endif /* (osdNumberOfApplications > 0) */

#if STATUS_LEVEL == EXTENDED_STATUS
   osResCounterType ossResGlobalOccupationCounter;
  #if (osdNumberOfInterruptResources > 0)
   osIntLevelType ossInitialIntLevel;
  #endif
#endif
#if (osdParameterAccessMacros && osdErrorHook)
   osAPIParam1Type ossAPIParam1;
   osAPIParam2Type ossAPIParam2;
   osAPIParam3Type ossAPIParam3;
   osuint32 * osqPRAM3 ossAPIParam4;
#endif

#if (osdStackCheck || osdCallTimingHooks)
   TaskType ossLastActiveTaskIndex;
#endif

#if osdORTIDebug
   volatile osuint8 ossORTICurrentServiceId;
#endif

#if (osdErrorHook!=0)
   #if osdORTIDebug 
      StatusType ossLastErrorCode;
   #endif
   volatile osuint16 ossLastError;
   osbool ossErrorFlag;
#endif
   /* KB begin osCtrlVarsNoLockNeededAdditionalHWVariables (overwritten) */
   #if osdExceptionDetails
   osuint32 ossUnhandledExceptionDetail;
   #endif
   /* KB end osCtrlVarsNoLockNeededAdditionalHWVariables */
}osCtrlVarsNoLockNeededType;

typedef struct
{ 
   volatile osCtrlVarsLockNeededType    LockIsNeeded;
   osCtrlVarsNoLockNeededType  LockIsNotNeeded;
} osCtrlVarType;

#define ptrToCcb (&osOwnCcb->LockIsNeeded)
/* KB end osHWCtrlVarStruct */

/* KB begin osOwnCcbDefine (overwritten) */
#define osOwnCcb (osConfigBlock.CcbAddress[osSysGetCoreID()])

#define osdCounterInternalMaximumValue(x) (oskCounterInternalMaximumValue[x])


/* KB end osOwnCcbDefine */

/* KB begin osekHWConfigBlock (default) */
typedef struct {

   /* Frame */
   osuint8  aucMagicNumber[4];   /* 130 42 12 196  = 0x82 2A 0C C4 */
   osuint16 uiLength;
   osuint16 uiHardwareID;        /* Hardware Identification */
   osuint8  ucMajorVersion;
   osuint8  ucMinorVersion;
   osuint16 uiConfigVersion;     /* Version number of configuration block format*/
   osuint16 uiUserConfigVersion; /* Version number of configuration assigned by user*/

   /* cargo --------------------------------------------------------------- */

   /* start address of config block */
   const void*                      uiStartAddressConfigBlock;
   /* start addresses of sub-containers (fixed number) */
   const void*                      uiStartAddressSubCont0;                /* Sub-container 0 */
   const osTaskFctType*             uiStartAddressTaskStartAddress;        /* Sub-container 1 */
   const osuint8*                   uiStartAddressTaskPreemptive;          /* Sub-container 2 */
   const osuint8*                   uiStartAddressTaskTrusted;             /* Sub-container 3 */
   const osStackPtrType*            uiStartAddressTaskStackStartAddress;   /* Sub-container 4 */
   const osStackPtrType*            uiStartAddressTaskStackEndAddress;     /* Sub-container 5 */
   const osuint8*                   uiStartAddressTaskToAppl;              /* Sub-container 6 */
   const osuint8*                   uiStartAddressIsrTrusted;              /* Sub-container 7 */
   const osuint8*                   uiStartAddressIsrToAppl;               /* Sub-container 8 */
   const osuint8*                   StartAddressApplTrusted;               /* Sub-container 9 */
   const osuint8*                   StartAddressTrustedFunctions;          /* Sub-container 10 */
   const osuint8*                   StartAddressNonTrustedFunctions;       /* Sub-container 11 */
   const osIsrFctType*              StartAddresscat2IsrStartAddress;       /* Sub-container 12 */
   const osuint8*                   StartAddressIsrNestable;               /* Sub-container 13 */
   const CoreIdType*                StartAddressProcessToCore;             /* Sub-container 14 */
   const CoreIdType*                StartAddressAlarmToCore;               /* Sub-container 15 */
   const CoreIdType*                StartAddressResourceToCore;            /* Sub-container 16 */
   const CoreIdType*                StartAddressCounterToCore;             /* Sub-container 17 */
   const CoreIdType*                StartAddressScheduleTableToCore;       /* Sub-container 18 */
   const CoreIdType*                StartAddressApplicationToCore;         /* Sub-container 19 */
   const CoreIdType*                StartAddressTrustedFunctionToCore;     /* Sub-container 20 */
   const CoreIdType*                StartAddressNonTrustedFunctionToCore;  /* Sub-container 21 */
   osCtrlVarType* const *           StartAddressCcbAddress;                /* Sub-container 22 */
   const osuint8*                   StartAddressPeripheralRegions;         /* Sub-container 23 */
   const osuint8*                   StartAddressSpinlockLockMethods;       /* Sub-container 24 */
   const osuint8*                   StartAddressSpinlockLockTypes;         /* Sub-container 25 */
   osMiniLockType*const*            StartAddressOptimizedSpinlockVars;     /* Sub-container 26 */


/* KB begin osekHWConfigBlockStartAddrSpecific (overwritten) */
   const osStackType*               StartAddressCat2IsrStacks;             /* Sub-container 27 */
   const osuint16* const            StartAddrISRChannel;                   /* Sub-container 28 */
   const osuint16* const            StartAddrISRPrioLevel;                 /* Sub-container 29 */
   const osuint8* const             StartAddrIsrToCore;                    /* Sub-container 30 */
/* KB end osekHWConfigBlockStartAddrSpecific */  

   /* Sub-Container 0 */
   osuint16 uiNumberOfTasks;               /* = osdNumberOfAllTasks            */
   osuint16 uiNumberOfCat2ISRs;            /* = osdNumberOfCat2ISRs            */
   osuint16 uiNumberOfTrustedFunctions;    /* = osdNumberOfTrustedFunctions    */
   osuint16 uiNumberOfNonTrustedFunctions; /* = osdNumberOfNonTrustedFunctions */
   osuint16 uiNumberOfApplications;        /* = osdNumberOfApplications        */
   osuint16 uiNumberOfPeripheralRegions;   /* = osdNumberOfPeripheralRegions   */
   osuint8  ucStackUsageMeasurement;       /* = osdStackUsageMeasurement       */
   osuint16 NumberOfAlarms;                /* = osdNumberOfAlarms              */
   osuint16 NumberOfAllResources;          /* = osdNumberOfAllResources        */
   osuint16 NumberOfAvailableCores;        /* = osdNumberOfAvailableCores      */
   osuint16 NumberOfCounters;              /* = osdNumberOfCounters            */
   osuint16 NumberOfProcesses;             /* = osdNumberOfProcesses           */
   osuint16 NumberOfScheduleTables;        /* = osdNumberOfScheduleTables      */
   osuint16 NumberOfSpinlocks;             /* = osdNumberOfSpinlocks           */

   /* KB begin osekHWConfigBlockSubCont0Specific (overwritten) */
   osStackType SystemStack[osdNumberOfAvailableCores];   
   /* KB end osekHWConfigBlockSubCont0Specific */ 

   /* Sub-Container 1 */
   osTaskFctType              aulTaskStartAddress[osdNumberOfAllTasks+1];
   /* Sub-Container 2 */
   osuint8                    aucTaskPreemptive[osdNumberOfAllTasks+1];
   /* Sub-Container 3 */
   osuint8                    aucTaskTrusted[osdNumberOfAllTasks+1];
   /* Sub-Container 4 */
   osStackPtrType             aulTaskStackStartAddress[osdNumberOfAllTasks+1]; /* TR:SPMF07:0003 */
   /* Sub-Container 5 */
   const osStackPtrType       aulTaskStackEndAddress[osdNumberOfAllTasks+1]; /* TR:SPMF08:0004 */
   /* Sub-Container 6 */
   osuint8                    acTaskToAppl[osdNumberOfAllTasks+1]; 
   /* Sub-Container 7 */
   osuint8                    aucIsrTrusted[osdNumberOfCat2ISRs+1];
   /* Sub-Container 8 */
   osuint8                    acIsrToAppl[osdNumberOfCat2ISRs+1];
   /* Sub-Container 9 */
   osuint8                    applTrusted[osdNumberOfApplications+1];
   /* Sub-Container 10 */
   osuint8                    trustedFunctions[1];
   /* Sub-Container 11 */
   osuint8                    nonTrustedFunctions[1];
   /* Sub-Container 12 */
   osIsrFctType               cat2IsrStartAddress[osdNumberOfCat2ISRs+1];
   /* Sub-Container 13 */
   osuint8                    IsrNestable[osdNumberOfCat2ISRs+1];
   /* Sub-Container 14 */
   CoreIdType                 ProcessToCore[osdNumberOfProcesses+1];
   /* Sub-Container 15 */
   CoreIdType                 AlarmToCore[osdNumberOfAlarms+1];
   /* Sub-Container 16 */
   CoreIdType                 ResourceToCore[osdNumberOfAllResources+1];
   /* Sub-Container 17 */
   CoreIdType                 CounterToCore[osdNumberOfCounters+1];
   /* Sub-Container 18 */
   CoreIdType                 ScheduleTableToCore[osdNumberOfScheduleTables+1];
   /* Sub-Container 19 */
   CoreIdType                 ApplicationToCore[osdNumberOfApplications+1];
   /* Sub-Container 20 */
   CoreIdType                 TrustedFunctionToCore[osdNumberOfTrustedFunctions+1];
   /* Sub-Container 21 */
   CoreIdType                 NonTrustedFunctionToCore[1];
   /* Sub-Container 22 */
   osCtrlVarType* const       CcbAddress[osdNumberOfAvailableCores+1];
   /* Sub-Container 23 */
   osuint8                    peripheralRegions[1];
   /* Sub-Container 24 */
   osuint8                    SpinlockLockMethods[1];
   /* Sub-Container 25 */
   osuint8                    SpinlockLockTypes[1];
   /* Sub-Container 26 */
   osMiniLockType*            OptimizedSpinlockVars[1];



/* KB begin osekHWConfigBlockSubContainersSpecific (overwritten) */
   /* Sub-Container 27 */
   osStackType                osCat2IsrStacks[osdNumberOfCat2ISRs+1];
   /* Sub-Container 28 */
   const osuint16             osIsrChannel[osdNumberOfAllISRs+1];
   /* Sub-Container 29 */
   const osuint16             osIsrPrioLevel[osdNumberOfAllISRs+1];
   /* Sub-Container 30 */
   const osuint8              osIsrToCore[osdNumberOfAllISRs+1];
/* KB end osekHWConfigBlockSubContainersSpecific */

   /* Frame End ---------------------------------------------------------- */
   osuint32 uiCheckSum;

} tsConfigBlock;
/* KB end osekHWConfigBlock */
/* KB begin osekHWexternConfigBlock (default) */
/* MISRA RULE 8.8 not violated: the external declaration is defined more than once in the vector testsuite.
                                it is declared only once in the OS code
 */ 
extern const tsConfigBlock osConfigBlock; /* PRQA S 3451 */ 
/* KB end osekHWexternConfigBlock */

/* Parameter values for MICROSAR OS Timing Hooks */
#define OS_VTHP_TASK_TERMINATION 0x01
#define OS_VTHP_ISR_END          0x02
#define OS_VTHP_TASK_WAITEVENT   0x04
#define OS_VTHP_TASK_WAITSEMA    0x08
#define OS_VTHP_THREAD_PREEMPT   0x10
#define OS_VTHP_TASK_ACTIVATION  0x21
#define OS_VTHP_ISR_START        0x22
#define OS_VTHP_TASK_SETEVENT    0x24
#define OS_VTHP_TASK_GOTSEMA     0x28
#define OS_VTHP_THREAD_RESUME    0x30

/* Bit to be set in order to change a 'from thread reason' into a 'to thread reason' */
#define OS_VTHP_MODIFY_FROM_TO_REASON 0x20

#define OS_VTHP_CAT2INTERRUPTS 1
#define OS_VTHP_ALLINTERRUPTS 2

#ifndef osdCallTimingHooks
#error "The generator has not defined osdCallTimingHooks (should always be defined)"
#endif

#if osdCallTimingHooks
#include osdTimingHooksFileName
osqRAM0 extern osqRAM1 osqRAM2 osuint8 osqRAM3  osNextRunReason[osdNumberOfAllTasks];
#endif

/*
 *  MICROSAR OS timing hooks call macros, used by interrupt API functions and macros
 *  (may be expanded into the application)
 */
/* CovComment 4:  Macro: OS_VTH_CALL_DISABLEDINT_HOOK */
#if osdCallTimingHooks
#define OS_VTH_CALL_DISABLEDINT_HOOK(IntLockId)                         \
   COVER(0x0004)                                                              \
   OS_VTH_DISABLEDINT((IntLockId), 0)
#else
#define OS_VTH_CALL_DISABLEDINT_HOOK(IntLockId)                         \
   COVER(0x0005)
#endif

/* CovComment 4:  Macro: OS_VTH_CALL_ENABLEDINT_HOOK */
#if osdCallTimingHooks
#define OS_VTH_CALL_ENABLEDINT_HOOK(IntLockId)                          \
   COVER(0x0006)                                                              \
   OS_VTH_ENABLEDINT((IntLockId), 0)
#else
#define OS_VTH_CALL_ENABLEDINT_HOOK(IntLockId)                          \
   COVER(0x0007)
#endif

#if osdORTIDebug
 #define osdTestMacros 1
#endif

#ifndef osdTestMacros
 #if defined USE_QUOTE_INCLUDES
  #include "emptymac.h"
 #else
  #include <emptymac.h>
 #endif
#else                           
 #if (osdTestMacros == 1)
  #if defined USE_QUOTE_INCLUDES
   #include "testmac1.h"
  #else
   #include <testmac1.h>
  #endif
 #endif
 #if (osdTestMacros == 3)
  #if defined USE_QUOTE_INCLUDES
   #include "testmac3.h"
  #else
   #include <testmac3.h>
  #endif
 #endif
 #if (osdTestMacros == 4)
  #if defined USE_QUOTE_INCLUDES
   #include "testmac4.h"
  #else
   #include <testmac4.h>
  #endif
 #endif
#endif /*osdTestMacros*/

/* KB begin osekHWVariableSectionStartHeader (overwritten) */
/* KB end osekHWVariableSectionStartHeader */

/* KB begin osekHWDefineNegateTick (default) */
/* KB end osekHWDefineNegateTick */

/* KB begin osekHWDefineDummyRead (overwritten) */
#define osdDummyRead(x)   if((x)!=0){__asm("NOP");}
/* KB end osekHWDefineDummyRead */

osqRAM0 extern osqRAM1 volatile osqRAM2 AppModeType osqRAM3 osActiveAppMode;


/* KB begin osekHWVariableSectionEndHeader (overwritten) */
/* KB end osekHWVariableSectionEndHeader */

/* KB begin osekOsAbortSystemPrototype (default) */
osqFunc1 void osqFunc2 osAbortSystem(osuint16 uiError);
/* KB end osekOsAbortSystemPrototype */
/* KB begin osekOsUnrecoverableErrorPrototype (default) */
osqFunc1 void osqFunc2 osUnrecoverableError(StatusType StdErrorCode, osuint16 osOsekErrorCode);
/* KB end osekOsUnrecoverableErrorPrototype */

/* necessary for task/ISR-kill and to handle a missing TerminateTask in SC3/4 */
#if (osdKillTaskIsrPossible || (osdSC == SC3) || (osdSC == SC4))
 #if (osdNumberOfAllResources > 0)
 #if (!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed))
  osqFunc1 void osqFunc2 osSysKillResourceList(ResourceType ResId);
 #endif
 #endif
#endif



/* KB begin osekHwDeclareApiWrapperPrototypes (default) */

#if ((osdSC== SC3) || (osdSC== SC4))
#define osdApiCall(ParamApiCall) osPsys##ParamApiCall
#else
#define osdApiCall(ParamApiCall) os##ParamApiCall
#endif
/* MISRA RULE 19.10 VIOLATION: (4 times) The macros osdParamsX are only used build function declarations and definitions 
 * within further macros. The parameters may be formal parameters of a function consisting of type and name where 
 * parentheses could not be used. (3410) */
#define osdParams1(a) a                      /* PRQA S 3410 */
#define osdParams2(a, b) a, b               /* PRQA S 3410 */
#define osdParams3(a, b, c) a, b, c        /* PRQA S 3410 */
#define osdParams4(a, b, c, d) a, b, c, d /* PRQA S 3410 */

#if ((osdSC == SC3) || (osdSC == SC4))
/* MISRA RULE 19.10 VIOLATION: The macro osdDeclareApiWrappers uses macro parameters 
 * outside of '(' and ')'. This is unavoidable as it uses the parameters as return type 
 * in a function definition (3410) */
#define osdDeclareApiWrappers(RetType, ApiName, FormalParams)  \
   osqFunc1 RetType osqFunc2 osPsys##ApiName(FormalParams);/* PRQA S 3410 */
#else
#define osdDeclareApiWrappers(RetType, ApiName, FormalParams)
#endif

/* KB end osekHwDeclareApiWrapperPrototypes */

/* fullfills [SR:001] of $\AutosarOS\general\Generation5\_doc\12_SystemRequirements\RequirementsSpec_MicrosarOS.doc */
/* OSEK-Prototypes */
/* system services */

/* QAC-message below can be accepted as osdApiCall uses the parameter just with token merging (##) (3443) (6 times)*/
#ifndef osdActivateTaskNotUsed
#define ActivateTask(x) osdApiCall(ActivateTask(x)) /* PRQA S 3443 */
#endif

#ifndef osdTerminateTaskNotUsed
#define TerminateTask() osdApiCall(TerminateTask()) /* PRQA S 3443 */
#endif

#ifndef osdChainTaskNotUsed
#define ChainTask(x) (osdApiCall(ChainTask(x))) /* PRQA S 3443 */
#endif

#ifndef osdScheduleNotUsed
#define Schedule() osdApiCall(Schedule()) /* PRQA S 3443 */
#endif

#ifndef osdGetTaskIDNotUsed
#define GetTaskID(x) (osdApiCall(GetTaskID(x))) /* PRQA S 3443 */
#endif

#ifndef osdGetTaskStateNotUsed
#define GetTaskState(x, y) (osdApiCall(GetTaskState((x), (y)))) /* PRQA S 3443 */
#endif


#ifndef osdActivateTaskNotUsed
osqFunc1 StatusType osqFunc2 osActivateTask( TaskType taskIndex);
#endif
#ifndef osdTerminateTaskNotUsed
osqFunc1 StatusType osqFunc2 osTerminateTask ( void );
#endif
#ifndef osdChainTaskNotUsed
osqFunc1 StatusType osqFunc2 osChainTask ( TaskType taskIndex );
#endif
#ifndef osdScheduleNotUsed
osqFunc1 StatusType osqFunc2 osSchedule ( void );              
#endif
#ifndef osdGetTaskIDNotUsed
osqFunc1 StatusType osqFunc2 osGetTaskID ( TaskRefType TaskId); 
#endif
#ifndef osdGetTaskStateNotUsed
osqFunc1 StatusType osqFunc2 osGetTaskState(TaskType TaskId, TaskStateRefType State);
#endif


/* KB begin osekOsAssertFailedPrototype (default) */
osqFunc1 void osqFunc2 osAssertFailed(void);
/* KB end osekOsAssertFailedPrototype */
/* KB begin osekHwOsekGlobalPrototypes (overwritten) */

#if (osdStackCheck == 1)
#if (osdMPUSupportInSVMode == 0) || (osdSC == SC1) || (osdSC == SC2)
#define osdSoftwareStackCheck
#endif
#endif 



osqFunc1 void osqFunc2 osInitStacks(void);
osqFunc1 void osqFunc2 osInitINTC(void);
osqFunc1 void osqFunc2 osInitMPU(void);
osqFunc1 osuint16 osqFunc2 osGetConfigBlockVersion(void);

#define ptrToCcb2            (&osOwnCcb->LockIsNotNeeded)



#define osReadICR8(addr)   (*(volatile osuint8*)(addr))
#define osReadICR16(addr)  (*(volatile osuint16*)(addr))

#define osReadIMR8(addr)   (*(volatile osuint8*)(addr))
#define osReadIMR16(addr)  (*(volatile osuint16*)(addr))
#define osReadIMR32(addr)  (*(volatile osuint32*)(addr))

#define osdICRMaskBit    (osuint16)0x0080U
#define osdICRTableBit   (osuint16)0x0040U

#define osdIntMaxIndex   osdNumberOfInterrupts-1

#define osdEIBD0         0xFFFEEB00UL
#define osdEIBD1         0xFFFFB800UL

#define osSetEIBD1(x)    (*((volatile osuint32*)(osdEIBD1 + ((x)*4))))

#define osdIPIR_BASE              0xFFFEEC80UL
#define osdIPIR_CHANNEL(channel)  (osdIPIR_BASE + (4 * (channel)))
#define osdSetIPIR(channel, core) ((*((volatile osuint32*)osdIPIR_CHANNEL(channel))) = (core))

#define osdICRADDR(x)           (((x)<32)?((osdICRBASE0)+((x)*2)):((osdICRBASE1)+((x)*2)))
#define osdICRxLo(x)            (*((volatile osuint8*)(osdICRADDR(x))))
#define osdICRxHi(x)            (*((volatile osuint8*)(osdICRADDR(x)+1)))
#define osdICRx16(x)            (*((volatile osuint16*)(osdICRADDR(x))))

#define osGetICRx8Lo(x)         osdICRxLo(x)
#define osGetICRx8Hi(x)         osdICRxHi(x)
#define osGetICRx16(x)          osdICRx16(x)


#define osWriteICRxLo(x, val)    (osdICRxLo(x)=(val))
#define osWriteICRxHi(x, val)    (osdICRxHi(x)=(val))
#define osWriteICRx16(x, val)    (osdICRx16(x)=(val))

#define osDisableInterrupt(x)     osSetICRxMask(osdICRADDR(x))
#define osEnableInterrupt(x)      osClearICRxMask(osdICRADDR(x))

#define osSysDisableInterruptSource(x)  osDisableInterrupt(x)
#define osSysEnableInterruptSource(x)   osEnableInterrupt(x)

#if (osdNumberOfPrioLevels == 8)
#define osdPMRMask         0xFF
#define osdPMRHiBit        0x100
#else
#define osdPMRMask         0xFFFF
#define osdPMRHiBit        0x10000
#endif

#define osDisableGlobal()        __asm("DI")
#define osEnableGlobal()         __asm("EI")

#define osGetInitialLevel()      osGetLevelISPR()
#define osSetLevel(x)            osSetLevelPMR(x)
#define osGetLevel()             osGetLevelPMR()

#define osCheckInterruptsDisabled()  (osCheckIntDisabled())
#define osCheckInterruptsEnabled()   (!osCheckIntDisabled())

#define osSaveDisableGlobal()        ptrToCcb2->ossSavedIntDisFlag=osGetDisableGlobal();
#define osRestoreEnableGlobal()      if(ptrToCcb2->ossSavedIntDisFlag==0){osEnableGlobal();}

#define osSaveDisableLevel()         ptrToCcb2->ossSavedIntLevel=osGetDisableLevel();
#define osRestoreEnableLevel()       osRestoreLevel();
/* KB end osekHwOsekGlobalPrototypes */ 

#ifndef osdGetCoreIDNotUsed
/* KB begin GetCoreIDFunctionPrototype (default) */
 #define GetCoreID() (osSysGetCoreID())
/* KB end GetCoreIDFunctionPrototype */
#endif

/* KB begin osekHwRTEInterruptMacros (default) */
/* Message 3459: (no MISRA rule related to this) The macros below use the do{...}while(0) construct to implement
                 function like macros which always accept a ';' after their usage. There is no risk in this.
 */
/* CovComment 4:  Macro: osDisableLevelKM */
#define osDisableLevelKM()                               \
do{                                                      \
   osDisableLevel();                                     \
   OS_VTH_CALL_DISABLEDINT_HOOK(OS_VTHP_CAT2INTERRUPTS)  \
   COVER(0x0008)                                               \
}while(0) /* PRQA S 3459 */ 

/* CovComment 4:  Macro: osEnableLevelKM */
#define osEnableLevelKM()                                \
do{                                                      \
   OS_VTH_CALL_ENABLEDINT_HOOK(OS_VTHP_CAT2INTERRUPTS)   \
   osEnableLevel();                                      \
   COVER(0x0009)                                               \
}while(0) /* PRQA S 3459 */ 

/* CovComment 4:  Macro: osDisableGlobalKM */
 #define osDisableGlobalKM()                             \
 do{                                                     \
    osDisableGlobal();                                   \
    OS_VTH_CALL_DISABLEDINT_HOOK(OS_VTHP_ALLINTERRUPTS)  \
    COVER(0x000A)                                              \
 }while(0) /* PRQA S 3459 */ 

/* CovComment 4:  Macro: osEnableGlobalKM */
 #define osEnableGlobalKM()                              \
 do{                                                     \
    OS_VTH_CALL_ENABLEDINT_HOOK(OS_VTHP_ALLINTERRUPTS)   \
    osEnableGlobal();                                    \
    COVER(0x000B)                                              \
 }while(0) /* PRQA S 3459 */ 



#if ((osdSC == SC3) || (osdSC == SC4))

osqFunc1 void osqFunc2 osPsysDisableLevelUM(void);
osqFunc1 void osqFunc2 osPsysEnableLevelUM(void);

/* CovComment 4:  Macro: osDisableLevelUM */
#define osDisableLevelUM()                      \
do{                                             \
   osPsysDisableLevelUM();                      \
   COVER(0x000C)                                      \
}while(0) /* PRQA S 3459 */ 

/* CovComment 4:  Macro: osEnableLevelUM */
#define osEnableLevelUM()                       \
do{                                             \
   osPsysEnableLevelUM();                       \
   COVER(0x000D)                                      \
}while(0) /* PRQA S 3459 */ 

#else /*((osdSC== SC3) || (osdSC== SC4))*/

/* CovComment 4:  Macro: osDisableLevelUM */
#define osDisableLevelUM()                      \
do{                                             \
   osDisableLevelKM();                          \
   COVER(0x000E)                                      \
}while(0) /* PRQA S 3459 */ 

/* CovComment 4:  Macro: osEnableLevelUM */
#define osEnableLevelUM()                       \
do{                                             \
   osEnableLevelKM();                           \
   COVER(0x000F)                                      \
}while(0) /* PRQA S 3459 */ 

#endif /*((osdSC== SC3) || (osdSC== SC4))*/



#if ((osdSC == SC3) || (osdSC == SC4))

osqFunc1 void osqFunc2 osPsysDisableGlobalUM(void);
osqFunc1 void osqFunc2 osPsysEnableGlobalUM(void);

/* CovComment 4:  Macro: osDisableGlobalUM */
#define osDisableGlobalUM()                     \
do{                                             \
   osPsysDisableGlobalUM();                     \
   COVER(0x0010)                                      \
}while(0) /* PRQA S 3459 */ 

/* CovComment 4:  Macro: osEnableGlobalUM */
#define osEnableGlobalUM()                      \
do{                                             \
   osPsysEnableGlobalUM();                      \
   COVER(0x0011)                                      \
}while(0) /* PRQA S 3459 */ 

#else /*((osdSC== SC3) || (osdSC== SC4))*/

/* CovComment 4:  Macro: osDisableGlobalUM */
#define osDisableGlobalUM()                     \
do{                                             \
   osDisableGlobalKM();                         \
   COVER(0x0012)                                      \
}while(0) /* PRQA S 3459 */ 

/* CovComment 4:  Macro: osEnableGlobalUM */
#define osEnableGlobalUM()                      \
do{                                             \
   osEnableGlobalKM();                          \
   COVER(0x0013)                                      \
}while(0) /* PRQA S 3459 */ 

#endif /*((osdSC== SC3) || (osdSC== SC4))*/



/* CovComment 4:  Macro: osDisableLevelAM */
#define osDisableLevelAM()                      \
do{                                             \
   osDisableLevelUM();                          \
   COVER(0x0014)                                      \
}while(0) /* PRQA S 3459 */ 


/* CovComment 4:  Macro: osEnableLevelAM */
#define osEnableLevelAM()                       \
do{                                             \
   osEnableLevelUM();                           \
   COVER(0x0015)                                      \
}while(0) /* PRQA S 3459 */ 




/* CovComment 4:  Macro: osDisableGlobalAM */
#define osDisableGlobalAM()                     \
do{                                             \
   osDisableGlobalUM();                         \
   COVER(0x0016)                                      \
}while(0) /* PRQA S 3459 */ 


/* CovComment 4:  Macro: osEnableGlobalAM */
#define osEnableGlobalAM()                      \
do{                                             \
   osEnableGlobalUM();                          \
   COVER(0x0017)                                      \
}while(0) /* PRQA S 3459 */ 






/* KB end osekHwRTEInterruptMacros */

/* interrupt handling */
#ifndef osdEnableAllInterruptsNotUsed
osqFunc1 void osqFunc2 osEnableAllInterrupts(void);
#endif

#ifndef osdDisableAllInterruptsNotUsed
osqFunc1 void osqFunc2 osDisableAllInterrupts(void);
#endif

#ifndef osdResumeOSInterruptsNotUsed
osqFunc1 void osqFunc2 osResumeOSInterrupts(void);
#endif

#ifndef osdSuspendOSInterruptsNotUsed
osqFunc1 void osqFunc2 osSuspendOSInterrupts(void);
#endif

#ifndef osdResumeAllInterruptsNotUsed
osqFunc1 void osqFunc2 osResumeAllInterrupts(void);
#endif

#ifndef osdSuspendAllInterruptsNotUsed
osqFunc1 void osqFunc2 osSuspendAllInterrupts(void);
#endif

#if ((osdSC== SC3) || (osdSC== SC4))
/* KB begin osekHwPsysWrapperPrototypes (default) */
#if (((osdNumberOfAllTasks > 0) && !defined(osdActivateTaskNotUsed)))
osdDeclareApiWrappers(StatusType, ActivateTask, osdParams1(TaskType Param0_taskIndex))
#endif

#if (((osdNumberOfAllTasks > 0) && !defined(osdChainTaskNotUsed)))
osdDeclareApiWrappers(StatusType, ChainTask, osdParams1(TaskType Param0_taskIndex))
#endif

#if (((osdNumberOfAllTasks > 0) && !defined(osdGetTaskIDNotUsed)))
osdDeclareApiWrappers(StatusType, GetTaskID, osdParams1(TaskRefType Param0_TaskId))
#endif

#if (((osdNumberOfAllTasks > 0) && !defined(osdGetTaskStateNotUsed)))
osdDeclareApiWrappers(StatusType, GetTaskState, osdParams2(TaskType Param0_TaskId, TaskStateRefType Param1_State))
#endif

#if ((((osdNumberOfAllResources - osdNumberOfInternalResources) > 0) && !defined(osdGetResourceNotUsed)))
osdDeclareApiWrappers(StatusType, GetResource, osdParams1(ResourceType Param0_ResId))
#endif

#if ((((osdNumberOfAllResources - osdNumberOfInternalResources) > 0) && !defined(osdReleaseResourceNotUsed)))
osdDeclareApiWrappers(StatusType, ReleaseResource, osdParams1(ResourceType Param0_ResId))
#endif

#if ((((CC == ECC1) || (CC == ECC2)) && (osdNumberOfExtendedTasks > 0) && !defined(osdSetEventNotUsed)))
osdDeclareApiWrappers(StatusType, SetEvent, osdParams2(TaskType Param0_taskIndex, EventMaskType Param1_setMask))
#endif

#if ((((CC == ECC1) || (CC == ECC2)) && (osdNumberOfExtendedTasks > 0) && !defined(osdClearEventNotUsed)))
osdDeclareApiWrappers(StatusType, ClearEvent, osdParams1(EventMaskType Param0_Mask))
#endif

#if ((((CC == ECC1) || (CC == ECC2)) && (osdNumberOfExtendedTasks > 0) && !defined(osdGetEventNotUsed)))
osdDeclareApiWrappers(StatusType, GetEvent, osdParams2(TaskType Param0_taskIndex, EventMaskRefType Param1_Event))
#endif

#if ((((CC == ECC1) || (CC == ECC2)) && (osdNumberOfExtendedTasks > 0) && !defined(osdWaitEventNotUsed)))
osdDeclareApiWrappers(StatusType, WaitEvent, osdParams1(EventMaskType Param0_Mask))
#endif

#if (((osdNumberOfAlarms > 0) && !defined(osdGetAlarmBaseNotUsed)))
osdDeclareApiWrappers(StatusType, GetAlarmBase, osdParams2(AlarmType Param0_AlarmId, AlarmBaseRefType Param1_Info))
#endif

#if (((osdNumberOfAlarms > 0) && !defined(osdGetAlarmNotUsed)))
osdDeclareApiWrappers(StatusType, GetAlarm, osdParams2(AlarmType Param0_alarmID, TickRefType Param1_diffTickTime))
#endif

#if (((osdNumberOfAlarms > 0) && !defined(osdSetRelAlarmNotUsed)))
osdDeclareApiWrappers(StatusType, SetRelAlarm, osdParams3(AlarmType Param0_alarmID, 
                                                          TickType Param1_deltaTicks, 
                                                          TickType Param2_cycle      )
                     )
#endif

#if (((osdNumberOfAlarms > 0) && !defined(osdSetAbsAlarmNotUsed)))
osdDeclareApiWrappers(StatusType, SetAbsAlarm, osdParams3(AlarmType Param0_alarmID, 
                                                          TickType Param1_start, 
                                                          TickType Param2_cycle    )
                     )
#endif

#if (((osdNumberOfAlarms > 0) && !defined(osdCancelAlarmNotUsed)))
osdDeclareApiWrappers(StatusType, CancelAlarm, osdParams1(AlarmType Param0_alarmID))
#endif

osdDeclareApiWrappers(void, ShutdownOS, osdParams1(StatusType Param0_Error))

#if (((osdNumberOfScheduleTables > 0) && !defined(osdStartScheduleTableRelNotUsed)))
osdDeclareApiWrappers(StatusType, StartScheduleTableRel, osdParams2(ScheduleTableType Param0_ScheduleTableID,
                                                                    TickType Param1_Offset                   )
                     )
#endif

#if (((osdNumberOfScheduleTables > 0) && !defined(osdStartScheduleTableAbsNotUsed)))
osdDeclareApiWrappers(StatusType, StartScheduleTableAbs, osdParams2(ScheduleTableType Param0_ScheduleTableID,
                                                                    TickType Param1_Offset                   )
                     )
#endif

#if (((osdNumberOfScheduleTables > 0) && !defined(osdNextScheduleTableNotUsed)))
osdDeclareApiWrappers(StatusType, NextScheduleTable, osdParams2(ScheduleTableType Param0_ScheduleTableID_current, 
                                                                ScheduleTableType Param1_ScheduleTableID_next    )
                     )
#endif

#if (((osdNumberOfScheduleTables > 0) && !defined(osdStopScheduleTableNotUsed)))
osdDeclareApiWrappers(StatusType, StopScheduleTable, osdParams1(ScheduleTableType Param0_ScheduleTableID))
#endif


#if (((osdNumberOfScheduleTables > 0) && !defined(osdGetScheduleTableStatusNotUsed)))
osdDeclareApiWrappers(StatusType, GetScheduleTableStatus, osdParams2(ScheduleTableType Param0_ScheduleTableID, 
                                                                     ScheduleTableStatusRefType Param1_ScheduleStatus)
                     )
#endif

#if (((osdNumberOfSWCounters > 0) && !defined(osdIncrementCounterNotUsed)))
osdDeclareApiWrappers(StatusType, IncrementCounter, osdParams1(CounterType Param0_CounterID))
#endif

#if ((!defined(osdGetCounterValueNotUsed)))
osdDeclareApiWrappers(StatusType, GetCounterValue, osdParams2(CounterType Param0_CounterID, TickRefType Param1_Value))
#endif


#if ((!defined(osdGetElapsedValueNotUsed)))
osdDeclareApiWrappers(StatusType, GetElapsedValue, osdParams3(CounterType Param0_CounterID, 
                                                              TickRefType Param1_Value, 
                                                              TickRefType Param2_ElapsedValue)
                     )
#endif

#if (((osdNumberOfApplications > 0) && !defined(osdTerminateApplicationNotUsed)))
osdDeclareApiWrappers(StatusType, TerminateApplication, osdParams2(ApplicationType Param0_Application, 
                                                                   RestartType Param1_RestartOption   )
                     )
#endif

#if ((((osdSC == SC3) || (osdSC == SC4)) && !defined(osdGetApplicationStateNotUsed)))
osdDeclareApiWrappers(StatusType, GetApplicationState, osdParams2(ApplicationType Param0_Application, 
                                                                  ApplicationStateRefType Param1_Value)
                     )
#endif

#if ((!defined(osdCallTrustedFunctionNotUsed)))
osdDeclareApiWrappers(StatusType, CallTrustedFunction, osdParams2(TrustedFunctionIndexType Param0_FunctionIndex, 
                                                       TrustedFunctionParameterRefType Param1_FunctionParams    )
                     )
#endif


#if ((!defined(osdCheckISRMemoryAccessNotUsed)))
osdDeclareApiWrappers(AccessType, CheckISRMemoryAccess, osdParams3(ISRType Param0_ISRID, 
                                                                   MemoryStartAddressType Param1_Address, 
                                                                   MemorySizeType Param2_Size            )
                     )
#endif

#if ((!defined(osdCheckTaskMemoryAccessNotUsed)))
osdDeclareApiWrappers(AccessType, CheckTaskMemoryAccess, osdParams3(TaskType Param0_TaskID, 
                                                                    MemoryStartAddressType Param1_Address, 
                                                                    MemorySizeType Param2_Size            )
                     )
#endif

#if ((!defined(osdCheckObjectAccessNotUsed)))
osdDeclareApiWrappers(ObjectAccessType, CheckObjectAccess, osdParams3(ApplicationType Param0_ApplID, 
                                                                      ObjectTypeType Param1_ObjectType, 
                                                                      ObjectIDType Param2_ObjectID     )
                     )
#endif

#if ((!defined(osdCheckObjectOwnershipNotUsed)))
osdDeclareApiWrappers(ApplicationType, CheckObjectOwnership, osdParams2(ObjectTypeType Param0_ObjectType, 
                                                                        ObjectIDType Param1_ObjectID     )
                     )
#endif

#if (((osdTimingProtectionUsed) && (osdTimingMeasurement) && !defined(osdosGetTaskMaxExecutionTimeNotUsed)))
osdDeclareApiWrappers(StatusType, osGetTaskMaxExecutionTime, osdParams2(TaskType Param0_TaskID, 
                                                                        osTPTimeRefType Param1_MaxTime)
                     )
#endif

#if (((osdTimingProtectionUsed) && (osdTimingMeasurement) && !defined(osdosGetISRMaxExecutionTimeNotUsed)))
osdDeclareApiWrappers(StatusType, osGetISRMaxExecutionTime, osdParams2(ISRType Param0_ISRID, 
                                                                       osTPTimeRefType Param1_MaxTime)
                     )
#endif

#if (((osdTimingProtectionUsed) && (osdTimingMeasurement) && !defined(osdosGetTaskMaxBlockingTimeNotUsed)))
osdDeclareApiWrappers(StatusType, osGetTaskMaxBlockingTime, osdParams4(TaskType Param0_TaskID, 
                                                                       BlockTypeType Param1_BlockType, 
                                                                       ResourceType Param2_ResourceID, 
                                                                       osTPTimeRefType Param3_MaxTime )
                     )
#endif

#if (((osdTimingProtectionUsed) && (osdTimingMeasurement) && !defined(osdosGetISRMaxBlockingTimeNotUsed)))
osdDeclareApiWrappers(StatusType, osGetISRMaxBlockingTime, osdParams4(ISRType Param0_ISRID, 
                                                                      BlockTypeType Param1_BlockType, 
                                                                      ResourceType Param2_ResourceID, 
                                                                      osTPTimeRefType Param3_MaxTime)
                     )
#endif

#if (((osdTimingProtectionUsed) && (osdTimingMeasurement) && !defined(osdosGetTaskMinInterArrivalTimeNotUsed)))
osdDeclareApiWrappers(StatusType, osGetTaskMinInterArrivalTime, osdParams2(TaskType Param0_TaskID, 
                                                                           osTPTimeStampRefType Param1_MinTime)
                     )
#endif

#if (((osdTimingProtectionUsed) && (osdTimingMeasurement) && !defined(osdosGetISRMinInterArrivalTimeNotUsed)))
osdDeclareApiWrappers(StatusType, osGetISRMinInterArrivalTime, osdParams2(ISRType Param0_ISRID, 
                                                                          osTPTimeStampRefType Param1_MinTime)
                     )
#endif

#if (((osdNumberOfAllTasks > 0) && !defined(osdTerminateTaskNotUsed)))
osdDeclareApiWrappers(StatusType, TerminateTask, void)
#endif

#if (((osdNumberOfAllTasks > 0) && !defined(osdScheduleNotUsed)))
osdDeclareApiWrappers(StatusType, Schedule, void)
#endif

#if (!defined(osdGetActiveApplicationModeNotUsed))
osdDeclareApiWrappers(AppModeType, GetActiveApplicationMode, void)
#endif

#if (!defined(osdGetISRIDNotUsed))
osdDeclareApiWrappers(ISRType, GetISRID, void)
#endif

#if ((!defined(osdDisableAllInterruptsNotUsed)))
osdDeclareApiWrappers(void, DisableAllInterrupts, void)
#endif

#if ((!defined(osdEnableAllInterruptsNotUsed)))
osdDeclareApiWrappers(void, EnableAllInterrupts, void)
#endif

#if ((!defined(osdSuspendAllInterruptsNotUsed)))
osdDeclareApiWrappers(void, SuspendAllInterrupts, void)
#endif

#if ((!defined(osdResumeAllInterruptsNotUsed)))
osdDeclareApiWrappers(void, ResumeAllInterrupts, void)
#endif

#if ((!defined(osdSuspendOSInterruptsNotUsed)))
osdDeclareApiWrappers(void, SuspendOSInterrupts, void)
#endif

#if ((!defined(osdResumeOSInterruptsNotUsed)))
osdDeclareApiWrappers(void, ResumeOSInterrupts, void)
#endif

#if ((((osdSC == SC3) || (osdSC == SC4)) && !defined(osdAllowAccessNotUsed)))
osdDeclareApiWrappers(StatusType, AllowAccess, void)
#endif

osqFunc1 void osqFunc2 osPsysCallApplStartupHook(ApplicationType Param0_applID);

osqFunc1 void osqFunc2 osPsysCallApplErrorHook(StatusType Param0_ErrorCode, ApplicationType Param1_applID);

osqFunc1 void osqFunc2 osPsysCallApplShutdownHook(StatusType Param0_Error, ApplicationType Param1_applID);


/* KB end osekHwPsysWrapperPrototypes */
#endif /* ((osdSC== SC3) || (osdSC== SC4)) */

#define osdIntAPIDisableAll 0x80U

#if (STATUS_LEVEL == EXTENDED_STATUS)
   #define osSetIntAPIStatus(x) (osOwnCcb->LockIsNotNeeded.ossIntAPIStatus = (x))
   #define osIncIntAPIStatus() (osOwnCcb->LockIsNotNeeded.ossIntAPIStatus++)
   #define osDecIntAPIStatus() (osOwnCcb->LockIsNotNeeded.ossIntAPIStatus--)
#else
   #define osSetIntAPIStatus(x)
   #define osIncIntAPIStatus()
   #define osDecIntAPIStatus()
#endif


/* QAC-message below can be accepted as osdApiCall uses the parameter just with token merging (##) (3443) (8 times)*/
#ifndef osdEnableAllInterruptsNotUsed
#define EnableAllInterrupts() (osdApiCall(EnableAllInterrupts())) /* PRQA S 3443 */
#endif

#ifndef osdDisableAllInterruptsNotUsed
#define DisableAllInterrupts() (osdApiCall(DisableAllInterrupts())) /* PRQA S 3443 */
#endif

#ifndef osdResumeOSInterruptsNotUsed
#define ResumeOSInterrupts() (osdApiCall(ResumeOSInterrupts())) /* PRQA S 3443 */
#endif

#ifndef osdSuspendOSInterruptsNotUsed
#define SuspendOSInterrupts() (osdApiCall(SuspendOSInterrupts())) /* PRQA S 3443 */
#endif

#ifndef osdResumeAllInterruptsNotUsed
#define ResumeAllInterrupts() (osdApiCall(ResumeAllInterrupts())) /* PRQA S 3443 */
#endif

#ifndef osdSuspendAllInterruptsNotUsed
#define SuspendAllInterrupts() (osdApiCall(SuspendAllInterrupts())) /* PRQA S 3443 */
#endif


/* resource management */

#ifndef osdGetResourceNotUsed
#define GetResource(x) (osdApiCall(GetResource(x))) /* PRQA S 3443 */
#endif


#ifndef osdReleaseResourceNotUsed
#define ReleaseResource(x) (osdApiCall(ReleaseResource(x))) /* PRQA S 3443 */
#endif


#ifndef osdGetResourceNotUsed
osqFunc1 StatusType osqFunc2 osGetResource(ResourceType ResId);
#endif

#ifndef osdReleaseResourceNotUsed
osqFunc1 StatusType osqFunc2 osReleaseResource(ResourceType ResId); 
#endif

/* KB begin osekSemaphores (default) */
/* semaphores for OSEK */

/* QAC-message below can be accepted as osdApiCall uses the parameter just with token merging (##) (3443) (2 times)*/
#ifndef osdGetSemaphoreNotUsed
#define GetSemaphore(x) (osdApiCall(GetSemaphore(x))) /* PRQA S 3443 */
#endif

#ifndef osdReleaseSemaphoreNotUsed
#define ReleaseSemaphore(x) (osdApiCall(ReleaseSemaphore(x))) /* PRQA S 3443 */
#endif


#ifndef osdGetSemaphoreNotUsed
osqFunc1 StatusType osqFunc2 osGetSemaphore(osSemaphoreType SemaId);
#endif
#ifndef osdReleaseSemaphoreNotUsed
osqFunc1 StatusType osqFunc2 osReleaseSemaphore(osSemaphoreType SemaId);
#endif

/* KB end osekSemaphores */

/* event control */
/* QAC-message below can be accepted as osdApiCall uses the parameter just with token merging (##) (3443) (4 times)*/
#if (CC == ECC1) || (CC == ECC2)

#ifndef osdSetEventNotUsed
#define SetEvent(x, y) (osdApiCall(SetEvent((x), (y)))) /* PRQA S 3443 */
#endif

#ifndef osdGetEventNotUsed
#define GetEvent(x, y) (osdApiCall(GetEvent((x), (y)))) /* PRQA S 3443 */
#endif

#ifndef osdClearEventNotUsed
#define ClearEvent(x) (osdApiCall(ClearEvent(x))) /* PRQA S 3443 */
#endif

#ifndef osdWaitEventNotUsed
#define WaitEvent(x) (osdApiCall(WaitEvent(x))) /* PRQA S 3443 */
#endif

#ifndef osdSetEventNotUsed
osqFunc1 StatusType osqFunc2 osSetEvent(TaskType taskIndex, EventMaskType setMask);
#endif

#ifndef osdClearEventNotUsed
osqFunc1 StatusType osqFunc2 osClearEvent (EventMaskType Mask );                  
#endif

#ifndef osdGetEventNotUsed
osqFunc1 StatusType osqFunc2 osGetEvent(TaskType taskIndex, EventMaskRefType Event); 
#endif

#ifndef osdWaitEventNotUsed
osqFunc1 StatusType osqFunc2 osWaitEvent(EventMaskType mask);                    
#endif

#else /*CC...*/

#ifndef osdSetEventNotUsed
#define SetEvent(x, y) (Event API used with wrong conformance class)
#endif
#ifndef osdClearEventNotUsed
#define ClearEvent(x) (Event API used with wrong conformance class)
#endif
#ifndef osdGetEventNotUsed
#define GetEvent(x, y) (Event API used with wrong conformance class)
#endif
#ifndef osdWaitEventNotUsed
#define WaitEvent(x)   (Event API used with wrong conformance class)
#endif

#endif /*CC...*/


/* alarms        */
/* QAC-message below can be accepted as osdApiCall uses the parameter just with token merging (##) (3443) */
#ifndef osdGetAlarmBaseNotUsed
#define GetAlarmBase(x, y) (osdApiCall(GetAlarmBase((x), (y)))) /* PRQA S 3443 */
#endif

#ifndef osdSetRelAlarmNotUsed
#if (osdNumberOfAlarms > 0)
/* KB begin osekHwSetRelAlarmDefine2 (default) */
/* QAC-message below can be accepted as osdApiCall uses the parameter just with token merging (##) (3443)*/
#define SetRelAlarm(x, y, z) (osdApiCall(SetRelAlarm((x), (y), (z)))) /* PRQA S 3443 */
/* KB end osekHwSetRelAlarmDefine2 */
#endif
#endif

#ifndef osdSetAbsAlarmNotUsed
#if (osdNumberOfAlarms > 0)
/* KB begin osekHwSetAbsAlarmDefine2 (default) */
/* QAC-message below can be accepted as osdApiCall uses the parameter just with token merging (##) (3443)*/
#define SetAbsAlarm(x, y, z) (osdApiCall(SetAbsAlarm((x), (y), (z)))) /* PRQA S 3443 */
/* KB end osekHwSetAbsAlarmDefine2 */
#endif
#endif

/* QAC-message below can be accepted as osdApiCall uses the parameter just with token merging (##) (3443) (3 times)*/
#ifndef osdCancelAlarmNotUsed
#define CancelAlarm(x) (osdApiCall(CancelAlarm(x))) /* PRQA S 3443 */
#endif
 
#if (osdNumberOfAlarmIncrementCounter > 0) || !defined(osdIncrementCounterNotUsed)
/* TR:SPMF09:0011 Start */
#define IncrementCounter(x) (osdApiCall(IncrementCounter(x))) /* PRQA S 3443 */
/* TR:SPMF09:0011 End */
#endif


#ifndef osdGetCounterValueNotUsed
 /* TR:SASR30:0383 Start */
  #define GetCounterValue(x, y) (osdApiCall(GetCounterValue((x), (y)))) /* PRQA S 3443 */
 /* TR:SASR30:0383 End */
#endif

#ifndef osdGetElapsedValueNotUsed
 /* TR:SASR30:0392 Start */
/* QAC-message below can be accepted as osdApiCall uses the parameter just with token merging (##) (3443)*/
  #define GetElapsedCounterValue(x,y,z) GetElapsedValue((x),(y),(z)) /* compatibility ASR3/ASR4 */
  #define GetElapsedValue(x, y, z) (osdApiCall(GetElapsedValue((x), (y), (z)))) /* PRQA S 3443 */
 /* TR:SASR30:0392 End */
#endif


/* QAC-message below can be accepted as osdApiCall uses the parameter just with token merging (##) (3443) (6 times)*/
#ifndef osdGetAlarmNotUsed
#define GetAlarm(x, y) (osdApiCall(GetAlarm((x), (y)))) /* PRQA S 3443 */
#endif

#ifndef osdStartScheduleTableRelNotUsed
#define StartScheduleTableRel(x, y) osdApiCall(StartScheduleTableRel((x), (y))) /* PRQA S 3443 */
#endif

#ifndef osdStartScheduleTableAbsNotUsed
#define StartScheduleTableAbs(x, y) osdApiCall(StartScheduleTableAbs((x), (y))) /* PRQA S 3443 */
#endif

#ifndef osdStopScheduleTableNotUsed
#define StopScheduleTable(x) osdApiCall(StopScheduleTable((x))) /* PRQA S 3443 */
#endif

#ifndef osdNextScheduleTableNotUsed
#define NextScheduleTable(x, y) osdApiCall(NextScheduleTable((x), (y))) /* PRQA S 3443 */
#endif

#ifndef osdGetScheduleTableStatusNotUsed
#define GetScheduleTableStatus(x, y) osdApiCall(GetScheduleTableStatus((x), (y))) /* PRQA S 3443 */
#endif



#ifndef osdGetAlarmBaseNotUsed
osqFunc1 StatusType osqFunc2 osGetAlarmBase(AlarmType AlarmId, AlarmBaseRefType Info);
#endif

#ifndef osdSetRelAlarmNotUsed
/* KB begin osekHWosSetRelAlarmPrototype (default) */
#if (osdNumberOfAlarms > 0)
osqFunc1 StatusType osqFunc2 osSetRelAlarm(AlarmType alarmID, 
                                           TickType deltaTicks,
                                           TickType cycle);
#endif
/* KB end osekHWosSetRelAlarmPrototype */
#endif

#ifndef osdSetAbsAlarmNotUsed
/* KB begin osekHWosSetAbsAlarmPrototype (default) */
#if (osdNumberOfAlarms > 0)
osqFunc1 StatusType osqFunc2 osSetAbsAlarm(AlarmType alarmID, 
                                           TickType start,
                                           TickType cycle);
#endif
/* KB end osekHWosSetAbsAlarmPrototype */
#endif

#ifndef osdCancelAlarmNotUsed
osqFunc1 StatusType osqFunc2 osCancelAlarm(AlarmType alarmID);
#endif

/* fullfills [SR:315] of $\AutosarOS\general\Generation5\_doc\12_SystemRequirements\RequirementsSpec_MicrosarOS.doc */
#if (osdNumberOfAlarmIncrementCounter > 0) || !defined(osdIncrementCounterNotUsed)
osqFunc1 StatusType osqFunc2 osIncrementCounter(CounterType CounterID);
#endif

#ifndef osdGetCounterValueNotUsed
osqFunc1 StatusType osqFunc2 osGetCounterValue(CounterType CounterID, TickRefType Value); /* TR:SASR30:5108 */
#endif

#ifndef osdGetElapsedValueNotUsed
osqFunc1 StatusType osqFunc2 osGetElapsedValue(CounterType CounterID, TickRefType Value, TickRefType ElapsedValue); /* TR:SASR30:5109 */
#endif

#ifndef osdGetAlarmNotUsed
osqFunc1 StatusType osqFunc2 osGetAlarm(AlarmType alarmID, TickRefType diffTickTime);
#endif


#ifndef osdStartScheduleTableRelNotUsed
osqFunc1 StatusType osqFunc2 osStartScheduleTableRel(ScheduleTableType ScheduleTableID, TickType Offset);
#endif
#ifndef osdStartScheduleTableAbsNotUsed
osqFunc1 StatusType osqFunc2 osStartScheduleTableAbs(ScheduleTableType ScheduleTableID, TickType Tickvalue);
#endif

#ifndef osdNextScheduleTableNotUsed
osqFunc1 StatusType osqFunc2 osNextScheduleTable(ScheduleTableType ScheduleTableID_current, ScheduleTableType ScheduleTableID_next);
#endif
#ifndef osdGetScheduleTableStatusNotUsed
osqFunc1 StatusType osqFunc2 osGetScheduleTableStatus(ScheduleTableType ScheduleTableID, ScheduleTableStatusRefType ScheduleStatus);
#endif
#ifndef osdStopScheduleTableNotUsed
osqFunc1 StatusType osqFunc2 osStopScheduleTable(ScheduleTableType ScheduleTableID);
#endif




/* TR:SPMF20:0013 Start */
/* definitions for static alarms */
/* these macros should be used as parameters for SetRelAlarm/SetAbsAlarm in case of static alarms */
#define OS_STATIC_ALARM_TIME 0
#define OS_STATIC_CYCLE_TIME 0
/* TR:SPMF20:0013 End */

/* Operating system execution control */
osqFunc1 void osqFunc2 osErrorHook(StatusType ErrorCode);
osqFunc1 void osqFunc2 osShutdownOS(StatusType Error);
/* QAC-message below can be accepted as osdApiCall uses the parameter just with token merging (##) (3443)*/
#define ShutdownOS(x) (osdApiCall(ShutdownOS(x))) /* PRQA S 3443 */

osqFunc1 void osqFunc2 osStartOSasm(void); /* TR:SPMF05:0001 */

/* Definition of StartOS(). */
/* Error-Checking is done is osStartOSc */
/* TR:SPMF05:0001 Start */
#define StartOS(x)                              \
   osActiveAppMode=(x);                         \
   osStartOSasm()
/* TR:SPMF05:0001 End */

/* fullfills [SR:006] of $\AutosarOS\general\Generation5\_doc\12_SystemRequirements\RequirementsSpec_MicrosarOS.doc */
osqFunc1 void osqFunc2 osInitialize(void); /* TR:SPMF05:0001 */


osqFunc1 ApplicationType osqFunc2 osGetApplicationID(void);
/* KB begin osekGetApplicationIDDef (overwritten) */
#define GetApplicationID()   (osGetApplicationID())
/* KB end osekGetApplicationIDDef */

osqFunc1 AppModeType osqFunc2 osGetActiveApplicationMode(void);
/* KB begin osekGetActiveApplicationModeDef (overwritten) */
#define GetActiveApplicationMode()   (osGetActiveApplicationMode())
/* KB end osekGetActiveApplicationModeDef */

osqFunc1 ISRType osqFunc2 osGetISRID(void);
/* KB begin osekGetISRIDDef (overwritten) */
#define GetISRID()   (osGetISRID())
/* KB end osekGetISRIDDef */
osqFunc1 ISRType osqFunc2 osGetISRch(void);

/* KB begin osekCallBackSectionStart (overwritten) */
/* KB end osekCallBackSectionStart */

/* hook routines */
osqFunc1 void osqFunc2 ErrorHook (StatusType Error);
osqFunc1 void osqFunc2 StartupHook (void);
osqFunc1 void osqFunc2 ShutdownHook (StatusType Error);

#if osdPreTaskHook
osqFunc1 void osqFunc2 PreTaskHook (void);
#endif
#if osdPostTaskHook
osqFunc1 void osqFunc2 PostTaskHook (void);
#endif

#if ((osdSC == SC2) || (osdSC == SC3) || (osdSC == SC4))
ProtectionReturnType ProtectionHook(StatusType Fatalerror);
#endif

/* KB begin osekCallBackSectionEnd (default) */
/* KB end osekCallBackSectionEnd */

#if osdStackCheck
 #if osdStackUsageMeasurement
  osqFunc1 osStackUsageType osqFunc2 osGetStackUsage(TaskType taskId); /* TR:SPMF08:0007 */
  /* KB begin osekStackUsagePrototypes (overwritten) */
  osqFunc1 osStackUsageType osqFunc2 osGetISRStackUsage(ISRType isrId);
  osqFunc1 osStackUsageType osqFunc2 osGetSystemStackUsage(void);
  /* KB end osekStackUsagePrototypes */
 #endif
#endif


#if !defined osdProvideTimeStamp
#define osdProvideTimeStamp 0
#endif

/* KB begin osekHWosVersionVariant (default) */
/* TR:SPMF29:0001 Start */
/* structure for version and variant coding */
typedef struct
{
   osuint8 ucMagicNumber1;     /* magic number (e.g. for identification in hex files) */
   osuint8 ucMagicNumber2;     /* defined as osuint8 for independancy of byte order   */
   osuint8 ucMagicNumber3;     /*                                                     */
   osuint8 ucMagicNumber4;     /*                                                     */
   osuint8 ucSysVersionMaj;    /* version of operating system, Major                  */
   osuint8 ucSysVersionMin;    /* version of operating system, Minor                  */
   osuint8 ucGenVersionMaj;    /* version of code generator                           */
   osuint8 ucGenVersionMin;    /* version of code generator                           */
   osuint8 ucSysVariant1;      /* general variant coding 1                            */
   osuint8 ucSysVariant2;      /* general variant coding 2                            */
   osuint8 ucOrtiVariant;      /* ORTI version and variant       TR:SPMF14:0011  TR:SPMF29:0003      */ 
   /* KB begin osekTypeSpecVersionVariant (overwritten) */
   osuint8 ucSpecVariant; /* typedef of implementation specific variant coding */
   /* KB end osekTypeSpecVersionVariant */
} osVersionVariantCodingType;
/* TR:SPMF29:0001 End */

/* KB begin osekConstSectionHeaderStart (default) */
/* KB end osekConstSectionHeaderStart */
osqROM0 extern osqROM1 const osqROM2 osVersionVariantCodingType osqROM3 oskVersionVariant;
/* KB begin osekConstSectionHeaderEnd (default) */
/* KB end osekConstSectionHeaderEnd */
/* KB end osekHWosVersionVariant */

/* setup defines for filling up the variant coding structure */
#if CC == BCC1
   #define osdVariantCC 0U
#elif CC == BCC2
   #define osdVariantCC 1U
#elif CC == ECC1
   #define osdVariantCC 2U
#elif CC == ECC2
   #define osdVariantCC 3U
#else
#error wrong conformance class
#endif

#if STATUS_LEVEL == EXTENDED_STATUS
   #define osdVariantStatus 1U
#else
   #define osdVariantStatus 0U
#endif

#if osdNonPreempt
   #define osdVariantSchedule 0U
#elif osdFullPreempt
   #define osdVariantSchedule 1U
#elif osdMixedPreempt
   #define osdVariantSchedule 2U
#else
#error wrong scheduling policy
#endif


#if osdStackCheck
   #define osdVariantStackcheck 1U
#else
   #define osdVariantStackcheck 0U
#endif


/* TR:SPMF12:0005 Start */
#if osdEnableAssertions
   #define osdVariantAssertionsEnabled 1U
#else
   #define osdVariantAssertionsEnabled 0U
#endif
/* TR:SPMF12:0005 End */
#if (osdSC== SC1)
   #define osdVariantSC 0U
#elif (osdSC== SC2)
   #define osdVariantSC 1U
#elif (osdSC== SC3)
   #define osdVariantSC 2U
#elif (osdSC== SC4)
   #define osdVariantSC 3U
#else
#error wrong scalability class
#endif

#if (osdNumberOfScheduleTables>0)
   #define osdVariantFeaturesUsed_ST 1U
#else 
   #define osdVariantFeaturesUsed_ST 0U
#endif
#if (osdNumberOfHiResSchedTabs>0)
   #define osdVariantFeaturesUsed_HRST 1U
#else 
   #define osdVariantFeaturesUsed_HRST 0U
#endif
   #define osdVariantFeaturesUsed_Sync 0U
#if (osdTimingProtectionUsed)
   #define osdVariantFeaturesUsed_TP   1U
#else 
   #define osdVariantFeaturesUsed_TP   0U
#endif

#if osdORTIEnabled
/* osdORTIStdVersion is decimal coded, osdVariantORTIVersion shall be BCD coded */
#define osdVariantORTIVersion ((((osdORTIStdVersion)/100)<<4)|(((osdORTIStdVersion)%100)/10))
#define osdVariantORTIDebug osdORTIDebug
#else
#define osdVariantORTIVersion 0
#define osdVariantORTIDebug   0
#endif /* osdORTIEnabled */

/* KB begin osekDefineSpecVersionVariant (overwritten) */
/* Derivative */
#define osdVariantCompiler    0
#define osdVariantDerivative  0

#if ((defined(__NoFloat__)) || (defined(__SoftwareFloat__)))
   #define osdVariantFPUSupport 0
#else
   #define osdVariantFPUSupport 1
#endif

/* terminate application is not supported in SafeContext */
#ifndef osdTerminateApplicationNotUsed
#define osdTerminateApplicationNotUsed
#endif
/* KB end osekDefineSpecVersionVariant */



/* KB begin osekSpecificHeaderInclude (overwritten) */
/* KB end osekSpecificHeaderInclude */


 #if defined USE_QUOTE_INCLUDES
  #include "tcbpost.h"
 #else
  #include <tcbpost.h>
 #endif


/* include hardware specific header files after OSEK Typedefinitions */
/* KB begin osekHWincludeHwHeaderPostTypes (overwritten) */
#if defined USE_QUOTE_INCLUDES
#include "osekasm.h"
#else
#include <osekasm.h>
#endif

#define osdHwTimerNeeded0_OSTM osdHwTimerNeeded_OSTM
#define osdHwTimerNeeded0_OSTM_HIRES osdHwTimerNeeded_OSTM_HIRES

#define osdTimerOSTMID 0

#ifdef osdTimerOSTMID
 #define osdTimer0OSTMID osdTimerOSTMID
#endif
#ifdef osdTimerOSTM_HIRESID
 #define osdTimer0OSTM_HIRESID osdTimerOSTM_HIRESID
#endif
/* KB end osekHWincludeHwHeaderPostTypes */

/* KB begin osekEndOfHModule (overwritten) */
/* KB end osekEndOfHModule */

#if defined __cplusplus
} /* ENDOF extern "C" */
#endif

/*lint -restore re-enable messages*/

#endif/* double include preventer */

/* END OF HEADER osek.h */


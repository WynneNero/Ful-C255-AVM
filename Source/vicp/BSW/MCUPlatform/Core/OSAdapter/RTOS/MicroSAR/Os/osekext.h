/* Kernbauer Version: 2.16 Konfiguration: RH850 Erzeugungsgangnummer: 214 Zweig: 1 */

/*****************************************************************************
| Project Name: MICROSAR OS
|    File Name: osekext.h
|
|  General code: @Version: 9.01.04@
|  Module version: $vv$=1.78
|
|  Description: external declarations (only for system internal use)
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2000-2015 Vector Informatik GmbH          All rights reserved.
|****************************************************************************/

/* CovComment 0:  file: osekext.h */
/* MISRA RULE 19.15 VIOLATION: The QAC-Tool states a violation of rule 19.15 with 
 * message 0883 below. Anyhow, there is a double include prevention and therefore,
 * the message is considered to be wrong. */
/* double include preventer */
#ifndef _OSEKEXT_H      /* PRQA S 0883 EOF */ /* see MISRA comment above */
#define _OSEKEXT_H

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

#if defined USE_QUOTE_INCLUDES
 #include "osekSched.h"
#else
 #include <osekSched.h>
#endif

/* KB begin osekextSpecificHeaderInclude (overwritten) */
/* KB end osekextSpecificHeaderInclude */

/* KB begin osekStartOfHModule (overwritten) */
/* KB end osekStartOfHModule */

/* KB begin osekHwDefinitions (overwritten) */
#define osdOSTM_CMP(x)     (*((volatile osuint32*)(osdOSTMBaseAddr+0x00UL+(0x1000UL*(x))))) /* compare value          */
#define osdOSTM_CNT(x)     (*((volatile osuint32*)(osdOSTMBaseAddr+0x04UL+(0x1000UL*(x))))) /* current count          */
#define osdOSTM_TO(x)      (*((volatile osuint8* )(osdOSTMBaseAddr+0x08UL+(0x1000UL*(x))))) /* output register        */
#define osdOSTM_TOE(x)     (*((volatile osuint8* )(osdOSTMBaseAddr+0x0CUL+(0x1000UL*(x))))) /* output enable register */
#define osdOSTM_TE(x)      (*((volatile osuint8* )(osdOSTMBaseAddr+0x10UL+(0x1000UL*(x))))) /* count enable status register */
#define osdOSTM_TS(x)      (*((volatile osuint8* )(osdOSTMBaseAddr+0x14UL+(0x1000UL*(x))))) /* count start trigger    */
#define osdOSTM_TT(x)      (*((volatile osuint8* )(osdOSTMBaseAddr+0x18UL+(0x1000UL*(x))))) /* count stop trigger     */
#define osdOSTM_CTL(x)     (*((volatile osuint8* )(osdOSTMBaseAddr+0x20UL+(0x1000UL*(x))))) /* control register       */
/* KB end osekHwDefinitions */


/* KB begin osekHWinterHooksPrototypes (default) */
#define osPreTaskHook  osInterPreTaskHook
#define osPostTaskHook osInterPostTaskHook
extern void osInterPreTaskHook(void);
extern void osInterPostTaskHook(void);
extern void osInterStartupHook(void);
extern void osInterErrorHook(StatusType Error);
/* KB end osekHWinterHooksPrototypes */

#if (osdNumberOfAllTasks > 0)
osqRAM0 extern osqRAM1 osqRAM2 osStackPtrType osqRAM3 osTcbSP[osdNumberOfAllTasks];
#else
osqRAM0 extern osqRAM1 osqRAM2 osStackPtrType osqRAM3 osTcbSP[1];
#endif

/* prototypes for OSEK internal functions */

#if ((osdTimingProtectionUsed) || (osdSC== SC3) || (osdSC== SC4))
osqFunc1 void osqFunc2 osHandleProtectionErrors(ProtectionReturnType proRet, StatusType Fatalerror);
#endif

#if (osdNumberOfAlarms > 0)
osqFunc1 void osqFunc2 osInitAlarms(void); /* TR:SPMF20:0014 */
#if ((osdSC== SC3) || (osdSC== SC4))
osqFunc1 void osqFunc2 osSysCancelAlarm(AlarmType alarmID);
#endif
#endif

#if (osdNumberOfScheduleTables > 0)
#if ((osdSC== SC3) || (osdSC== SC4))
osqFunc1 void osqFunc2 osSysStopScheduleTable(ScheduleTableType ScheduleTableID);
#endif
#endif

osqFunc1 void osqFunc2 osStartOSc(void);

#if (osdNumberOfAllTasks > 0)
osqFunc1 StatusType osqFunc2 osSysActivateTask( TaskType taskIndex);
#endif

#if ((osdNumberOfAlarmSetEvent > 0) || (osdNumberOfSTSetEvent > 0))
osqFunc1 StatusType osqFunc2 osSysSetEvent(TaskType taskIndex, EventMaskType setMask);
#endif

/* KB begin osekOsSysShutdownOSPrototype (default) */
osqFunc1 void osqFunc2 osSysShutdownOS(StatusType Error);
/* KB end osekOsSysShutdownOSPrototype */

osqFunc1 void osqFunc2 osErrorHookWrapper(StatusType ErrorCode);

#if ((osdSC== SC2) || (osdSC== SC3) || (osdSC== SC4))
osqFunc1 ProtectionReturnType osqFunc2 osProtectionHookWrapper(StatusType argErr);
#endif

#if osdStackCheck
/* KB begin osekHwosFillTaskStacksPrototype (default) */
/* KB end osekHwosFillTaskStacksPrototype */
#endif

osqFunc1 void osqFunc2 osWorkHeap(osHeapType const * const h, CounterType counterID);
#if (osdNumberOfAlarms > 0)
osqFunc1 void osqFunc2 osWorkAlarm(AlarmType alarmID, osHeapType const * const h);
#endif /* #if (osdNumberOfAlarms > 0) */
#if (osdNumberOfScheduleTables > 0)
osqFunc1 void osqFunc2 osWorkScheduleTable(osTIPType TIPid);
#endif /* #if (osdNumberOfScheduleTables > 0) */

#define osGetHeapTime(x) (osAlarmTime[x])
#define osGetFirstAlarm(h) ((h)->heap[0])
#define osGetActiveAlarmCount(h) (*((h)->count))

#define osdHeapItemNotFound     0U
#define osdHeapMinItemUnchanged 1U
#define osdHeapMinItemChanged   2U
#define osdHeapLastItemRemoved  3U

osqFunc1 osuint8 osqFunc2 osRemoveItemMinHeap(osHeapElementType aItem, osHeapType const * const h, CounterType ctr);

osqFunc1 void osqFunc2 osInsertMinHeapStd(osHeapElementType newItem, osHeapType const * const h, CounterType ctr);

#if (osdUseHighResolutionTimer != 0)
osqFunc1 void osqFunc2 osInsertMinHeapHiRes(osHeapElementType newItem, osHeapType const * const h, CounterType ctr);
#endif

#if (osdNumberOfAlarms == 0) && (osdNumberOfScheduleTables > 0)
osqFunc1 void osqFunc2 osInitMinHeap(void);
#endif

/* KB begin osekHWosInitTimerPrototype (default) */
osqFunc1 void osqFunc2 osInitTimer(void);
/* KB end osekHWosInitTimerPrototype */

/* KB begin osekHWosPreInitTimerPrototype (default) */
osqFunc1 void osqFunc2 osPreInitTimer(void);
/* KB end osekHWosPreInitTimerPrototype */

#if (osdKillTaskIsrPossible || (osdSC== SC3) || (osdSC== SC4))
osqFunc1 void osqFunc2 osSysKillRunningTask(osbool issueError);
#endif
#if (((osdSC== SC3) || (osdSC== SC4)) && (osdProtReactKillApplAllowed || osdProtReactKillApplRestAllowed || !defined osdTerminateApplicationNotUsed))
osqFunc1 void osqFunc2 osSysKillApplication(ApplicationType applToKill, RestartType RestartOption);
osqFunc1 void osqFunc2 osSysKillPreemptedTask(TaskType taskID);
#endif


#if (STATUS_LEVEL == EXTENDED_STATUS)
osqFunc1 void osqFunc2 osMissingTerminateError(void);
#endif

/* KB begin osekHwosUnhandledExceptionPrototype (default) */
osqFunc1 void osqFunc2 osUnhandledException(void); /* TR:SPMF78:0002 */
/* KB end osekHwosUnhandledExceptionPrototype */

#if osdStackCheck
osqFunc1 void osqFunc2 osStackOverflow(void);
#endif

osqFunc1 void osqFunc2 osSysIncrementCounter(CounterType CounterID);

#if (osdNumberOfScheduleTables > 0)
osqFunc1 void osqFunc2 osInitScheduleTables(void);
#endif


/* KB begin osekHwPrototypes (overwritten) */
#ifdef osdSoftwareStackCheck
osqFunc1 void osqFunc2 osStackError(osuint32 onSystemStack);
osqFunc1 void osqFunc2 osStackOverflowDetected(void);
#else
#define osCheckCurrentStack()  
#define osCheckStackPattern()
#endif


osqFunc1 void osqFunc2 osEnterSafeState(StatusType SystemError, osuint16 ErrorReason);

osqFunc1 void osqFunc2 osSaveDisableLevelNested(void);
osqFunc1 void osqFunc2 osRestoreEnableLevelNested(void);

osqFunc1 osStackPtrType osqFunc2 osDispatcher(osStackPtrType stackPtr);
osqFunc1 osuint32 osqFunc2 osCallCat2ISR(ISRType ISRID);

osqFunc1 void osqFunc2 osUnhandledCoreException(osuint32 Status);
osqFunc1 void osqFunc2 osCoreExceptionHandler(osuint32 Status);
osqFunc1 void osqFunc2 osUnhandledDirectBranchException(osuint32 Status);
osqFunc1 void osqFunc2 osDirectBranchExceptionHandler(osuint32 Status);
osqFunc1 void osqFunc2 osUnhandledEIINTException(osuint32 Status);
osqFunc1 void osqFunc2 osEIINTExceptionHandler(osuint32 Status);

osqFunc1 void osqFunc2 osStartupHook(void);
osqFunc1 void osqFunc2 osEnterSafeState(StatusType SystemError, osuint16 ErrorReason);

osqFunc1 void osqFunc2 osStartTrustedTask(osuint32 stack_start, osuint32 stack_end, const osTaskFctType task_addr);
osqFunc1 void osqFunc2 osStartNonTrustedTask(osuint32 stack_start, osuint32 stack_end, const osTaskFctType task_addr);

osqFunc1 void osqFunc2 osStartTrustedISR(osuint32 ISRAddr, osuint32 newPSW);
osqFunc1 void osqFunc2 osStartNonTrustedISR(osuint32 ISRAddr, osuint32 newPSW);


/* MISRA RULE 19.12 not violated: The operator ## is used for symbol assignment in this macro. */
#define osCAT2ISRC0(IsrName, Level)\
   .align  4                                       ;\
   .globl  _##IsrName##_CAT2                       ;\
_##IsrName##_CAT2:                                 ;\
   pushsp  r1-r2                                   ;\
   pushsp  r4-r31                                  ;\
   mov     IsrName##_index, r6                     ;\
   mov     _osIntStackLevel##Level##_c0_StartAddr, r7 ;\
   mov     _osIntStackLevel##Level##_c0_EndAddr, r8   ;\
   jr      _osCat2IsrWrapper /* PRQA S 881 */
   
/* MISRA RULE 19.12 not violated: The operator ## is used for symbol assignment in this macro. */
#define osCAT2ISRC1(IsrName, Level)\
   .align  4                                       ;\
   .globl  _##IsrName##_CAT2                       ;\
_##IsrName##_CAT2:                                 ;\
   pushsp  r1-r2                                   ;\
   pushsp  r4-r31                                  ;\
   mov     IsrName##_index, r6                     ;\
   mov     _osIntStackLevel##Level##_c1_StartAddr, r7 ;\
   mov     _osIntStackLevel##Level##_c1_EndAddr, r8   ;\
   jr      _osCat2IsrWrapper /* PRQA S 881 */


#if (osdRH850_FPU == 0)
#define osdIsrContext   28
#define osdTaskContext  136
#else
#define osdIsrContext   36
#define osdTaskContext  144
#endif

#ifdef osdNOASM
#define osSetMpuConfig(x)
#define osGetSPR(x,y)     (0)
#define osSetSPR(x,y,z)
#endif


#ifdef osdASIDUsed
#define osSetASID(x)    osSetSPR(7, 2, (x))
#else
#define osSetASID(x)
#endif

#define osSetEBASE(x)   osSetSPR(3, 1, (x))

#define osSetINTBP(x)   osSetSPR(4, 1, (x))
#define osSetINTCFG(x)  osSetSPR(13, 2, (x))

#define osSetSCCFG(x)   osSetSPR(11, 1, (x))
#define osSetSCBP(x)    osSetSPR(12, 1, (x))                                             

#define osSetMPM(x)     osSetSPR(0, 5, (x))
#define osSetMPRC(x)    osSetSPR(1, 5, (x))

/* KB end osekHwPrototypes */


/* OSEK internal defines */

/* Task flags */
#define osdTaskFlagScheduleAllowed  ((osTaskFlagType)0U)
#define osdTaskFlagNotUsingSchedule ((osTaskFlagType)2U)

/* Preemption Type */
#define osdTaskTypeNonPreempt       ((osTaskPreemptionType) 0U)
#define osdTaskTypePreempt          ((osTaskPreemptionType) 1U)


/* alarm action */
#define osdAlarmActionSetEvent     ((osuint8)0U)
#define osdAlarmActionActivateTask ((osuint8)1U)
#define osdAlarmActionCallback     ((osuint8)2U)
#define osdAlarmActionIncrementCounter ((osuint8)3U)
/* KB begin osekHWosDiffTickTypeComparison (default) */
typedef union
{
   TickType           unsignedNumber;
   osTickTimeDiffType signedNumber;
}TickTypeTmp;

#define osdCounterCompareLt(left,right,halfrange) \
   (((left) <= (halfrange)) ? \
   (((right) > (left)) && ((right) <= ( (left) + (halfrange)     ))) : \
   (((right) > (left)) || ((right) <= (((left) - (halfrange)) - 1))))
#define osdCounterCompareLe(left,right,halfrange) \
   (((left) <= (halfrange)) ? \
   (((right) >= (left)) && ((right) <= ( (left) + (halfrange)     ))) : \
   (((right) >= (left)) || ((right) <= (((left) - (halfrange)) - 1))))
#define osdCounterCompareGt(left,right,halfrange) (!osdCounterCompareLe((left),(right),(halfrange)))
#define osdCounterCompareGe(left,right,halfrange) (!osdCounterCompareLt((left),(right),(halfrange)))


#define osdCounterOverflowRange(x) ((oskCounterInternalMaximumValue[x] - oskCounterMaxAllowedValue[x]) - 1)

/* KB end osekHWosDiffTickTypeComparison */

 
   #define osdSystemCounterMask    ((TickType)(0xC0000000UL))

/* KB begin osekAssignStack (default) */
/* stack grows from high to lower addresses; decrement before push */
#define osAssignStack(stack)    ((osStackDataType*)((&(stack)[0])+(sizeof(stack)/sizeof((stack)[0])))) 
/* KB end osekAssignStack */
/* KB begin osekBottomofStack (default) */
#define osBottomOfStack(stack)  ((osStackDataType*)(stack))
/* KB end osekBottomofStack */


/* KB begin osekHWVariableSectionStartHeader (overwritten) */
/* KB end osekHWVariableSectionStartHeader */

/****************************************************************************/
/* schedule table synchronization */
#define osdSTSyncNon           ((osuint8)0U)
#define osdSTSyncImplicit      ((osuint8)1U) /* "Implicit" and "Non" need to be distinguished in StartScheduleTableRel */
#define osdSTSyncExplicit      ((osuint8)2U)

#if (osdNumberOfCounters > 0)
osqRAM0 extern osqRAM1 osqRAM2 osAlarmIndexType osqRAM3 osAlarmHeapCount[osdNumberOfCounters];    /* Number of heap elements */
#endif

/* KB begin osekHwExternalDeclarations (overwritten) */
/* KB end osekHwExternalDeclarations */
#if (osdNumberOfScheduleTables>0)
typedef osuint8 osSTReactionType;
#define osdSTReact_Continue     ((osSTReactionType)0U)
#define osdSTReact_FinalDelay   ((osSTReactionType)1U)
#define osdSTReact_InitialDelay ((osSTReactionType)2U)
#define osdSTReact_Repeat       ((osSTReactionType)3U)
#define osdSTReact_Stop         ((osSTReactionType)4U)


osqFunc1 osSTReactionType osqFunc2 osSTWorkActions(GlobalTimeTickType* diff, 
                                                   osSTIndexType CurrentEP   );

#endif /*if (osdNumberOfScheduleTables>0)*/


/****************************************************************************/
/* spinlock methode and type */
#define osdSpLockMethodLOCK_NOTHING            (0U)
#define osdSpLockMethodLOCK_WITH_RES_SCHEDULER (1U)
#define osdSpLockMethodLOCK_CAT2_INTERRUPTS    (2U)
#define osdSpLockMethodLOCK_ALL_INTERRUPTS     (3U)

#define osdSpLockTypeStandardAutosar           (0U)
#define osdSpLockTypeOptimized                 (1U)


/* KB begin osekHWVariableSectionEndHeader (overwritten) */
/* KB end osekHWVariableSectionEndHeader */

/* KB begin osekEndOfHModule (overwritten) */
/* KB end osekEndOfHModule */

/*lint -restore re-enable messages*/

#if defined __cplusplus
} /* ENDOF extern "C" */
#endif

#endif /* _OSEKEXT_H, double include preventer */

/* END OF HEADER osekext.h */


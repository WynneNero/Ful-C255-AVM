/* Kernbauer Version: 2.16 Konfiguration: RH850 Erzeugungsgangnummer: 214 Zweig: 1 */

/*****************************************************************************
| Project Name: MICROSAR OS
|    File Name: testmac1.h
|
|  General code: @Version: 9.01.04@
|  Module version: $vv$=1.40
|
|  Description: test API macro definitions
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2000-2015 Vector Informatik GmbH          All rights reserved.
|****************************************************************************/

/* CovComment 0:  file: testmac1.h */
/* double include preventer */
#ifndef _TESTMAC1_H
#define _TESTMAC1_H

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

#if osdORTIDebug 

#define osdORTINoService              0

/*******************/
/* Task management */
/*******************/
#define osdORTIActivateTask           1
#define osdORTITerminateTask          2
#define osdORTIChainTask              3
#define osdORTISchedule               4
#define osdORTIGetTaskID              5
#define osdORTIGetTaskState           6

/**********************/
/* Interrupt handling */
/**********************/
#define osdORTIResumeAllInterrupts    7
#define osdORTISuspendAllInterrupts   8
#define osdORTIEnableAllInterrupts    12
#define osdORTIDisableAllInterrupts   13
#define osdORTIResumeOSInterrupts     14
#define osdORTISuspendOSInterrupts    15

/***********************/
/* Resource management */
/***********************/
#define osdORTIGetResource            16
#define osdORTIReleaseResource        17

/*****************/
/* Event control */
/*****************/
#define osdORTISetEvent               18
#define osdORTIClearEvent             19
#define osdORTIGetEvent               20
#define osdORTIWaitEvent              21

/**********/
/* Alarms */
/**********/
#define osdORTIGetAlarmBase           22
#define osdORTIGetAlarm               23
#define osdORTISetRelAlarm            24
#define osdORTISetAbsAlarm            25
#define osdORTICancelAlarm            26


/************/
/* Counters */
/************/

#define osdORTIIncrementCounter       27

/*******************/
/* Schedule tables */
/*******************/

#define osdORTIStartScheduleTableRel  28
#define osdORTIStartScheduleTableAbs  29
#define osdORTIStopScheduleTable      30
#define osdORTIGetScheduleTableStatus 31
#define osdORTINextScheduleTable      32

/**************************************/
/* Operating system execution control */
/**************************************/
#define osdORTIGetActiveApplicationMode 33
#define osdORTIStartOS                34
#define osdORTIShutdownOS             35

/*****************/
/* Hook routines */
/*****************/
#define osdORTIErrorHook              36
#define osdORTIPreTaskHook            37 
#define osdORTIPostTaskHook           38
#define osdORTIStartupHook            39
#define osdORTIShutdownHook           40

/*****************/
/* Misc routines */
/*****************/
#define osdORTIIdleEntry              52
#define osdORTISytemTimer             53 
#define osdORTIStartDispatch          54
#define osdORTIGetISRID               55

/************************/
/* Application routines */
/************************/
#define osdORTIGetApplicationID       56

/********************/
/* SC2/SC4 routines */
/********************/
#define osdORTISyncScheduleTable      64
#define osdORTISetScheduleTableAsync  65
#define osdORTIStartScheduleTableSynchron  66

#define osdORTIGetSemaphore           67
#define osdORTIReleaseSemaphore       68


#define osdORTIGetCounterValue        71
#define osdORTIGetElapsedValue        72


#endif /* osdORTIDebug */

#if osdORTIDebug 
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
  #define osORTISetCurrentServiceId(x)   (osOwnCcb->LockIsNotNeeded.ossORTICurrentServiceId = (((x)<<1)+1) )
  #define osORTIResetCurrentServiceId(x) (osOwnCcb->LockIsNotNeeded.ossORTICurrentServiceId = ( (x)<<1   ) )
 #else
   #ifndef osdORTIDebugTest
      #define osORTISetCurrentServiceId(x) (osOwnCcb->LockIsNotNeeded.ossORTICurrentServiceId = (x))
      #define osORTISaveCurrentServiceId() (osORTISavedServiceId = osOwnCcb->LockIsNotNeeded.ossORTICurrentServiceId)
      #define osORTIRestoreCurrentServiceId() (osOwnCcb->LockIsNotNeeded.ossORTICurrentServiceId = osORTISavedServiceId)
   #else
      #define osORTISetCurrentServiceId(x) (osOwnCcb->LockIsNotNeeded.ossORTICurrentServiceId = (osuint8)(( (x) == 0)? osOwnCcb->LockIsNotNeeded.ossORTICurrentServiceId : (x) ))
      #define osORTISaveCurrentServiceId() (osORTISavedServiceId = osOwnCcb->LockIsNotNeeded.ossORTICurrentServiceId)
      #define osORTIRestoreCurrentServiceId() (tstORTISavedServiceId = osORTISavedServiceId)
      extern osqRAM0 osqRAM1 volatile osqRAM2 osuint8 tstORTISavedServiceId;
   #endif
 #endif
#else
 #if osdORTIStdVersion == 200
   #define osORTISetCurrentServiceId(x) ((void) 0)
   #define osORTISaveCurrentServiceId() ((void) 0)
   #define osORTIRestoreCurrentServiceId() ((void) 0)
 #endif
#endif



#if osdORTIDebug 

/*******************/
/* Task management */
/*******************/

/* ActivateTask */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_AT_ENTRY()            osORTISetCurrentServiceId(osdORTIActivateTask);
#define OS_AT_EXIT()             osORTIResetCurrentServiceId(osdORTIActivateTask);
#else
#define OS_AT_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIActivateTask);
#define OS_AT_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_AT_START_CRITICAL()
#define OS_AT_END_CRITICAL()

/* TerminateTask */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_TT_ENTRY()            osORTISetCurrentServiceId(osdORTITerminateTask);
#define OS_TT_EXIT()             osORTIResetCurrentServiceId(osdORTITerminateTask);
#else
#define OS_TT_ENTRY()            osORTISetCurrentServiceId(osdORTITerminateTask);
#define OS_TT_EXIT()             osORTISetCurrentServiceId(osdORTINoService);
#endif
#define OS_TT_START_CRITICAL()
#define OS_TT_END_CRITICAL()

/* ChainTask */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_HT_ENTRY()            osORTISetCurrentServiceId(osdORTIChainTask);
#define OS_HT_EXIT()             osORTIResetCurrentServiceId(osdORTIChainTask);
#else
#define OS_HT_ENTRY()            osORTISetCurrentServiceId(osdORTIChainTask);
#define OS_HT_EXIT()             osORTISetCurrentServiceId(osdORTINoService);
#endif
#define OS_HT_START_CRITICAL()
#define OS_HT_END_CRITICAL()

/* Schedule */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SH_ENTRY()            osORTISetCurrentServiceId(osdORTISchedule);
#define OS_SH_EXIT()             osORTIResetCurrentServiceId(osdORTISchedule);
#else
#define OS_SH_ENTRY()            osORTISetCurrentServiceId(osdORTISchedule);
#define OS_SH_EXIT()             osORTISetCurrentServiceId(osdORTINoService);
#endif
#define OS_SH_START_CRITICAL()
#define OS_SH_END_CRITICAL()

/* osGetTaskID */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_GI_ENTRY()            osORTISetCurrentServiceId(osdORTIGetTaskID);
#define OS_GI_EXIT()             osORTIResetCurrentServiceId(osdORTIGetTaskID);
#else
#define OS_GI_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIGetTaskID);
#define OS_GI_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_GI_START_CRITICAL()
#define OS_GI_END_CRITICAL()
             
/* osGetTaskState */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_GS_ENTRY()            osORTISetCurrentServiceId(osdORTIGetTaskState);
#define OS_GS_EXIT()             osORTIResetCurrentServiceId(osdORTIGetTaskState);
#else
#define OS_GS_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIGetTaskState);
#define OS_GS_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_GS_START_CRITICAL()
#define OS_GS_END_CRITICAL()


/**********************/
/* Interrupt handling */
/**********************/

/* ResumeAllInterrupts */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_RA_ENTRY()            osORTISetCurrentServiceId(osdORTIResumeAllInterrupts);
#define OS_RA_EXIT()             osORTIResetCurrentServiceId(osdORTIResumeAllInterrupts);
#else
#define OS_RA_ENTRY()               osuint8 osORTISavedServiceId;       \
                                    osORTISaveCurrentServiceId();       \
                                    osORTISetCurrentServiceId(osdORTIResumeAllInterrupts);
#define OS_RA_EXIT()                osORTIRestoreCurrentServiceId();
#endif
#define OS_RA_START_CRITICAL()
#define OS_RA_END_CRITICAL()

/* SuspendAllInterrupts */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_PA_ENTRY()            osORTISetCurrentServiceId(osdORTISuspendAllInterrupts);
#define OS_PA_EXIT()             osORTIResetCurrentServiceId(osdORTISuspendAllInterrupts);
#else
#define OS_PA_ENTRY()               osuint8 osORTISavedServiceId;       \
                                    osORTISaveCurrentServiceId();       \
                                    osORTISetCurrentServiceId(osdORTISuspendAllInterrupts);
#define OS_PA_EXIT()                osORTIRestoreCurrentServiceId();
#endif
#define OS_PA_START_CRITICAL()
#define OS_PA_END_CRITICAL()

/* EnableAllInterrupts */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_EA_ENTRY()            osORTISetCurrentServiceId(osdORTIEnableAllInterrupts);
#define OS_EA_EXIT()             osORTIResetCurrentServiceId(osdORTIEnableAllInterrupts);
#else
#define OS_EA_ENTRY()               osuint8 osORTISavedServiceId;       \
                                    osORTISaveCurrentServiceId();       \
                                    osORTISetCurrentServiceId(osdORTIEnableAllInterrupts);
#define OS_EA_EXIT()                osORTIRestoreCurrentServiceId();
#endif
#define OS_EA_START_CRITICAL()
#define OS_EA_END_CRITICAL()
 
/* DisableAllInterrupts */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_DA_ENTRY()            osORTISetCurrentServiceId(osdORTIDisableAllInterrupts);
#define OS_DA_EXIT()             osORTIResetCurrentServiceId(osdORTIDisableAllInterrupts);
#else
#define OS_DA_ENTRY()               osuint8 osORTISavedServiceId;       \
                                    osORTISaveCurrentServiceId();       \
                                    osORTISetCurrentServiceId(osdORTIDisableAllInterrupts);
#define OS_DA_EXIT()                osORTIRestoreCurrentServiceId();
#endif
#define OS_DA_START_CRITICAL()
#define OS_DA_END_CRITICAL()

/* ResumeOSInterrupts */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_RI_ENTRY()            osORTISetCurrentServiceId(osdORTIResumeOSInterrupts);
#define OS_RI_EXIT()             osORTIResetCurrentServiceId(osdORTIResumeOSInterrupts);
#else
#define OS_RI_ENTRY()               osuint8 osORTISavedServiceId;       \
                                    osORTISaveCurrentServiceId();       \
                                    osORTISetCurrentServiceId(osdORTIResumeOSInterrupts);
#define OS_RI_EXIT()                osORTIRestoreCurrentServiceId();
#endif
#define OS_RI_START_CRITICAL()
#define OS_RI_END_CRITICAL()

/* SuspendOSInterrupts */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SI_ENTRY()            osORTISetCurrentServiceId(osdORTISuspendOSInterrupts);
#define OS_SI_EXIT()             osORTIResetCurrentServiceId(osdORTISuspendOSInterrupts);
#else
#define OS_SI_ENTRY()               osuint8 osORTISavedServiceId;       \
                                    osORTISaveCurrentServiceId();       \
                                    osORTISetCurrentServiceId(osdORTISuspendOSInterrupts);
#define OS_SI_EXIT()                osORTIRestoreCurrentServiceId();
#endif
#define OS_SI_START_CRITICAL()
#define OS_SI_END_CRITICAL()


/***********************/
/* Resource management */
/***********************/

/* GetResource */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_GR_ENTRY()            osORTISetCurrentServiceId(osdORTIGetResource);
#define OS_GR_EXIT()             osORTIResetCurrentServiceId(osdORTIGetResource);
#else
#define OS_GR_ENTRY()            osORTISetCurrentServiceId(osdORTIGetResource);
#define OS_GR_EXIT()             osORTISetCurrentServiceId(osdORTINoService);
#endif
#define OS_GR_START_CRITICAL()
#define OS_GR_END_CRITICAL()

/* ReleaseResource */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_RR_ENTRY()            osORTISetCurrentServiceId(osdORTIReleaseResource);
#define OS_RR_EXIT()             osORTIResetCurrentServiceId(osdORTIReleaseResource);
#else
#define OS_RR_ENTRY()            osORTISetCurrentServiceId(osdORTIReleaseResource);
#define OS_RR_EXIT()             osORTISetCurrentServiceId(osdORTINoService);
#endif
#define OS_RR_START_CRITICAL()
#define OS_RR_END_CRITICAL()

/* GetSemaphore */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_GM_ENTRY()            osORTISetCurrentServiceId(osdORTIGetSemaphore);
#define OS_GM_EXIT()             osORTIResetCurrentServiceId(osdORTIGetSemaphore);
#else
#define OS_GM_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIGetSemaphore);
#define OS_GM_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_GM_START_CRITICAL()
#define OS_GM_END_CRITICAL()

/* ReleaseSemaphore */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_RS_ENTRY()            osORTISetCurrentServiceId(osdORTIReleaseSemaphore);
#define OS_RS_EXIT()             osORTIResetCurrentServiceId(osdORTIReleaseSemaphore);
#else
#define OS_RS_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIReleaseSemaphore);
#define OS_RS_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_RS_START_CRITICAL()
#define OS_RS_END_CRITICAL()


/*****************/
/* Event control */
/*****************/
#define OS_IM_ENTRY()
#define OS_IM_EXIT()
#define OS_IM_START_CRITICAL()
#define OS_IM_END_CRITICAL()

/* SetEvent */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SE_ENTRY()            osORTISetCurrentServiceId(osdORTISetEvent);
#define OS_SE_EXIT()             osORTIResetCurrentServiceId(osdORTISetEvent);
#else
#define OS_SE_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTISetEvent);
#define OS_SE_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_SE_START_CRITICAL()
#define OS_SE_END_CRITICAL()
                           
/* ClearEvent */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_CE_ENTRY()            osORTISetCurrentServiceId(osdORTIClearEvent);
#define OS_CE_EXIT()             osORTIResetCurrentServiceId(osdORTIClearEvent);
#else
#define OS_CE_ENTRY()            osORTISetCurrentServiceId(osdORTIClearEvent);
#define OS_CE_EXIT()             osORTISetCurrentServiceId(osdORTINoService);
#endif
#define OS_CE_START_CRITICAL()
#define OS_CE_END_CRITICAL()
                           
/* GetEvent */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_GE_ENTRY()            osORTISetCurrentServiceId(osdORTIGetEvent);
#define OS_GE_EXIT()             osORTIResetCurrentServiceId(osdORTIGetEvent);
#else
#define OS_GE_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIGetEvent);
#define OS_GE_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_GE_START_CRITICAL()
#define OS_GE_END_CRITICAL()
                           
/* WaitEvent */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_WE_ENTRY()            osORTISetCurrentServiceId(osdORTIWaitEvent);
#define OS_WE_EXIT()             osORTIResetCurrentServiceId(osdORTIWaitEvent);
#else
#define OS_WE_ENTRY()            osORTISetCurrentServiceId(osdORTIWaitEvent);
#define OS_WE_EXIT()             osORTISetCurrentServiceId(osdORTINoService);
#endif
#define OS_WE_START_CRITICAL()
#define OS_WE_END_CRITICAL()


/**********/
/* Alarms */
/**********/

/* GetAlarmBase */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_GB_ENTRY()            osORTISetCurrentServiceId(osdORTIGetAlarmBase);
#define OS_GB_EXIT()             osORTIResetCurrentServiceId(osdORTIGetAlarmBase);
#else
#define OS_GB_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIGetAlarmBase);
#define OS_GB_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_GB_START_CRITICAL()
#define OS_GB_END_CRITICAL()
                  
/* SetRelAlarm */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SA_ENTRY()            osORTISetCurrentServiceId(osdORTISetRelAlarm);
#define OS_SA_EXIT()             osORTIResetCurrentServiceId(osdORTISetRelAlarm);
#else
#define OS_SA_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTISetRelAlarm);
#define OS_SA_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_SA_START_CRITICAL()
#define OS_SA_END_CRITICAL()

/* SetAbsAlarm */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SL_ENTRY()            osORTISetCurrentServiceId(osdORTISetAbsAlarm);
#define OS_SL_EXIT()             osORTIResetCurrentServiceId(osdORTISetAbsAlarm);
#else
#define OS_SL_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTISetAbsAlarm);
#define OS_SL_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_SL_START_CRITICAL()
#define OS_SL_END_CRITICAL()

/* CancelAlarm */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_CA_ENTRY()            osORTISetCurrentServiceId(osdORTICancelAlarm);
#define OS_CA_EXIT()             osORTIResetCurrentServiceId(osdORTICancelAlarm);
#else
#define OS_CA_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTICancelAlarm);
#define OS_CA_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_CA_START_CRITICAL()
#define OS_CA_END_CRITICAL()

/* GetAlarm */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_GA_ENTRY()            osORTISetCurrentServiceId(osdORTIGetAlarm);
#define OS_GA_EXIT()             osORTIResetCurrentServiceId(osdORTIGetAlarm);
#else
#define OS_GA_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIGetAlarm);
#define OS_GA_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_GA_START_CRITICAL()
#define OS_GA_END_CRITICAL()

/************/
/* Counters */
/************/

/* IncrementCounter */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_IC_ENTRY()            osORTISetCurrentServiceId(osdORTIIncrementCounter);
#define OS_IC_EXIT()             osORTIResetCurrentServiceId(osdORTIIncrementCounter);
#else
#define OS_IC_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIIncrementCounter);
#define OS_IC_EXIT()             osORTIRestoreCurrentServiceId();
#endif
/*x = counter index*/
#define OS_IC_START_CRITICAL()
#define OS_IC_END_CRITICAL()

/* GetCounterValue */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_GC_ENTRY()            osORTISetCurrentServiceId(osdORTIGetCounterValue);
#define OS_GC_EXIT()             osORTIResetCurrentServiceId(osdORTIGetCounterValue);
#else
#define OS_GC_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIGetCounterValue);
#define OS_GC_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_GC_START_CRITICAL()
#define OS_GC_END_CRITICAL()

/* GetElapsed(Counter)Value */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_GV_ENTRY()            osORTISetCurrentServiceId(osdORTIGetElapsedValue);
#define OS_GV_EXIT()             osORTIResetCurrentServiceId(osdORTIGetElapsedValue);
#else
#define OS_GV_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIGetElapsedValue);
#define OS_GV_EXIT()             osORTIRestoreCurrentServiceId();
#endif

#define OS_GV_START_CRITICAL()
#define OS_GV_END_CRITICAL()

/*******************/
/* Schedule tables */
/*******************/

/* StartScheduleTableRel */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SR_ENTRY()            osORTISetCurrentServiceId(osdORTIStartScheduleTableRel);
#define OS_SR_EXIT()             osORTIResetCurrentServiceId(osdORTIStartScheduleTableRel);
#else
#define OS_SR_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIStartScheduleTableRel);
#define OS_SR_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_SR_START_CRITICAL()
#define OS_SR_END_CRITICAL()

/* StartScheduleTableAbs */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SS_ENTRY()            osORTISetCurrentServiceId(osdORTIStartScheduleTableAbs);
#define OS_SS_EXIT()             osORTIResetCurrentServiceId(osdORTIStartScheduleTableAbs);
#else
#define OS_SS_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIStartScheduleTableAbs);
#define OS_SS_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_SS_START_CRITICAL()
#define OS_SS_END_CRITICAL()


/* StopScheduleTable */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SP_ENTRY()            osORTISetCurrentServiceId(osdORTIStopScheduleTable);
#define OS_SP_EXIT()             osORTIResetCurrentServiceId(osdORTIStopScheduleTable);
#else
#define OS_SP_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIStopScheduleTable);
#define OS_SP_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_SP_START_CRITICAL()
#define OS_SP_END_CRITICAL()

/* GetScheduleTableStatus */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SG_ENTRY()            osORTISetCurrentServiceId(osdORTIGetScheduleTableStatus);
#define OS_SG_EXIT()             osORTIResetCurrentServiceId(osdORTIGetScheduleTableStatus);
#else
#define OS_SG_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIGetScheduleTableStatus);
#define OS_SG_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_SG_START_CRITICAL()
#define OS_SG_END_CRITICAL()

/* NextScheduleTable */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SN_ENTRY()            osORTISetCurrentServiceId(osdORTINextScheduleTable);
#define OS_SN_EXIT()             osORTIResetCurrentServiceId(osdORTINextScheduleTable);
#else
#define OS_SN_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTINextScheduleTable);
#define OS_SN_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_SN_START_CRITICAL()
#define OS_SN_END_CRITICAL()


/************************/
/* Application routines */
/************************/


/**************************************/
/* Operating system execution control */
/**************************************/
                 
/* StartOS */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_ST_ENTRY()            osORTISetCurrentServiceId(osdORTIStartOS);
#define OS_ST_EXIT()             osORTIResetCurrentServiceId(osdORTIStartOS);
#else
#define OS_ST_ENTRY()            osORTISetCurrentServiceId(osdORTIStartOS);
#define OS_ST_EXIT()             osORTISetCurrentServiceId(osdORTINoService);
#endif
#define OS_ST_START_CRITICAL()
#define OS_ST_END_CRITICAL()

/* ShutdownOS */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_SD_ENTRY()            osORTISetCurrentServiceId(osdORTIShutdownOS);
#define OS_SD_EXIT()             osORTIResetCurrentServiceId(osdORTIShutdownOS);
#else
#define OS_SD_ENTRY()            osORTISetCurrentServiceId(osdORTIShutdownOS);
#define OS_SD_EXIT()             osORTISetCurrentServiceId(osdORTINoService);
#endif
#define OS_SD_START_CRITICAL()
#define OS_SD_END_CRITICAL()


/*****************/
/* Hook routines */
/*****************/

/* ErrorHook */
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_ERHOOK_ENTRY()        osORTISetCurrentServiceId(osdORTIErrorHook);
#define OS_ERHOOK_EXIT()         osORTIResetCurrentServiceId(osdORTIErrorHook);
                                                
/* StartupHook */
#define OS_STHOOK_ENTRY()        osORTISetCurrentServiceId(osdORTIStartupHook);
#define OS_STHOOK_EXIT()         osORTIResetCurrentServiceId(osdORTIStartupHook);

/* ShutdownHook */               
#define OS_SDHOOK_ENTRY()        osORTISetCurrentServiceId(osdORTIShutdownHook);
#define OS_SDHOOK_EXIT()         osORTIResetCurrentServiceId(osdORTIShutdownHook);

/* PreTaskHook */
#define OS_PREHOOK_ENTRY()       osORTISetCurrentServiceId(osdORTIPreTaskHook);
#define OS_PREHOOK_EXIT()        osORTIResetCurrentServiceId(osdORTIPreTaskHook);

/* PostTaskHook */
#define OS_POSTHOOK_ENTRY()      osORTISetCurrentServiceId(osdORTIPostTaskHook);
#define OS_POSTHOOK_EXIT()       osORTIResetCurrentServiceId(osdORTIPostTaskHook);
#else
#define OS_ERHOOK_ENTRY()        {  \
                                    osuint8 osORTISavedServiceId; \
                                    osORTISaveCurrentServiceId(); \
                                    osORTISetCurrentServiceId(osdORTIErrorHook);
#define OS_ERHOOK_EXIT()            osORTIRestoreCurrentServiceId(); \
                                 }
                                                
/* StartupHook */
#define OS_STHOOK_ENTRY()        {  \
                                    osuint8 osORTISavedServiceId; \
                                    osORTISaveCurrentServiceId(); \
                                    osORTISetCurrentServiceId(osdORTIStartupHook);
#define OS_STHOOK_EXIT()            osORTIRestoreCurrentServiceId(); \
                                 }

/* ShutdownHook */               
#define OS_SDHOOK_ENTRY()        {  \
                                    osuint8 osORTISavedServiceId; \
                                    osORTISaveCurrentServiceId(); \
                                    osORTISetCurrentServiceId(osdORTIShutdownHook);
#define OS_SDHOOK_EXIT()            osORTIRestoreCurrentServiceId(); \
                                 }

/* PreTaskHook */
#define OS_PREHOOK_ENTRY()       {  \
                                    osuint8 osORTISavedServiceId; \
                                    osORTISaveCurrentServiceId(); \
                                    osORTISetCurrentServiceId(osdORTIPreTaskHook); 
#define OS_PREHOOK_EXIT()           osORTIRestoreCurrentServiceId(); \
                                 }

/* PostTaskHook */
#define OS_POSTHOOK_ENTRY()      {  \
                                    osuint8 osORTISavedServiceId; \
                                    osORTISaveCurrentServiceId(); \
                                    osORTISetCurrentServiceId(osdORTIPostTaskHook); 
#define OS_POSTHOOK_EXIT()          osORTIRestoreCurrentServiceId(); \
                                 }
#endif


/**************************/
/* miscellaneous routines */
/**************************/

/* osTimerInterrupt */             
#define OS_TI_ENTRY()            
#define OS_TI_EXIT()
#define OS_TI_START_CRITICAL()
#define OS_TI_END_CRITICAL()

/* GetISRID */           
#if ((osdORTIStdVersion == 210) || (osdORTIStdVersion == 220))
#define OS_II_ENTRY()            osORTISetCurrentServiceId(osdORTIGetISRID);
#define OS_II_EXIT()             osORTIResetCurrentServiceId(osdORTIGetISRID);
#else
#define OS_II_ENTRY()            osuint8 osORTISavedServiceId; \
                                 osORTISaveCurrentServiceId(); \
                                 osORTISetCurrentServiceId(osdORTIGetISRID);
#define OS_II_EXIT()             osORTIRestoreCurrentServiceId();
#endif
#define OS_II_START_CRITICAL()
#define OS_II_END_CRITICAL()

/* dispatcher */
#define OS_START_DISPATCH()

/* idle loop */
#define OS_IDLE_ENTRY()
#define OS_IDLE_PROC()      


  /****************************/
 /* MICROSAR OS Timing Hooks */
/****************************/
/* task activation hooks */
#ifndef OS_VTH_ACTIVATION
#define OS_VTH_ACTIVATION(TaskId, DestCoreId, CallerCoreId)
#endif
#ifndef OS_VTH_SETEVENT
#define OS_VTH_SETEVENT(TaskId, EventMask, StateChange, DestCoreId, CallerCoreId)
#endif
#ifndef OS_VTH_TRANSFER_SEMA
#define OS_VTH_TRANSFER_SEMA(FromThreadId, ToTaskId, SemaId, DestCoreId, CallerCoreId)
#endif

/* thread switch hook */
#ifndef OS_VTH_SCHEDULE
#define OS_VTH_SCHEDULE(FromThreadId, FromThreadReason, ToThreadId, ToThreadReason, CallerCoreId)
#endif

/* lock hooks */
#ifndef OS_VTH_GOT_RES
#define OS_VTH_GOT_RES(ResId, CallerCoreId)
#endif
#ifndef OS_VTH_REL_RES
#define OS_VTH_REL_RES(ResId, CallerCoreId)
#endif
#ifndef OS_VTH_REQ_SPINLOCK
#define OS_VTH_REQ_SPINLOCK(SpinlockId, CallerCoreId)
#endif
#ifndef OS_VTH_GOT_SPINLOCK
#define OS_VTH_GOT_SPINLOCK(SpinlockId, CallerCoreId)
#endif
#ifndef OS_VTH_REL_SPINLOCK
#define OS_VTH_REL_SPINLOCK(SpinlockId, CallerCoreId)
#endif
#ifndef OS_VTH_REQ_ISPINLOCK
#define OS_VTH_REQ_ISPINLOCK(SpinlockId, CallerCoreId)
#endif
#ifndef OS_VTH_GOT_ISPINLOCK
#define OS_VTH_GOT_ISPINLOCK(SpinlockId, CallerCoreId)
#endif
#ifndef OS_VTH_REL_ISPINLOCK
#define OS_VTH_REL_ISPINLOCK(SpinlockId, CallerCoreId)
#endif
#ifndef OS_VTH_TOOK_SEMA
#define OS_VTH_TOOK_SEMA(TaskId, SemaId, CallerCoreId)
#endif
#ifndef OS_VTH_REL_SEMA
#define OS_VTH_REL_SEMA(ThreadId, SemaId, CallerCoreId)
#endif
#ifndef OS_VTH_DISABLEDINT
#define OS_VTH_DISABLEDINT(IntLockId, CallerCoreId)
#endif
#ifndef OS_VTH_ENABLEDINT
#define OS_VTH_ENABLEDINT(IntLockId, CallerCoreId)
#endif
#ifndef OS_VTH_IDISABLEDINT
#define OS_VTH_IDISABLEDINT(IntLockId, CallerCoreId)
#endif
#ifndef OS_VTH_IENABLEDINT
#define OS_VTH_IENABLEDINT(IntLockId, CallerCoreId)
#endif

/* Hardware specific macro */
/* KB begin osekHwTestMacro1 (overwritten) */
#define OS_INT_ENTRY(x)
#define OS_INT_EXIT(x)
/* KB end osekHwTestMacro1 */

#endif /* osdORTIDebug */

#endif /* _TESTMAC1_H */


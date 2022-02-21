/* Kernbauer Version: 2.16 Konfiguration: RH850 Erzeugungsgangnummer: 214 Zweig: 1 */

/*****************************************************************************
| Project Name: MICROSAR OS
|    File Name: osektask.c
|
|  General code: @Version: 9.01.04@
|  Module version: $vv$=1.75
|
|  Description: osek API-functions for controlling tasks
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2000-2015 Vector Informatik GmbH          All rights reserved.
|****************************************************************************/


/* next define is set in the makefile
 * switches of the include of (generated) tcb.h, includes instead
 * the library config file
 */

#if defined USE_QUOTE_INCLUDES
 #include "osek.h"
 #include "osekext.h"
#else
 #include <osek.h>
 #include <osekext.h>
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

/* CovComment 0:  file: osektask.c */

/* KB begin osekStartOfCModule (overwritten) */
#pragma ghs section bss=".os_bss"
#pragma ghs section data=".os_data"
#pragma ghs section sbss=".os_sbss"
#pragma ghs section sdata=".os_sdata"
#pragma ghs section text=".os_text"
#pragma ghs section rodata=".os_rodata"
#pragma ghs section rosdata=".os_rosdata"
/* KB end osekStartOfCModule */


/*
 *  MICROSAR OS timing hooks call macro, used by task API below
 */
/* CovComment 4:  Macro: OS_VTH_CALL_ACTIVATION_HOOK */
#if osdCallTimingHooks
#define OS_VTH_CALL_ACTIVATION_HOOK(TaskId)                                      \
   COVER(0x03D3)                                                                       \
   OS_VTH_ACTIVATION(TaskId, 0, 0)
#else
#define OS_VTH_CALL_ACTIVATION_HOOK(TaskId)  \
   COVER(0x03D4)
#endif


#if ((osdNumberOfAllTasks > 0) && !defined(osdActivateTaskNotUsed))
/*-+--------------------------------------------------------------------------
 / ActivateTask
 / ============
 /
 / Syntax:          StatusType ActivateTask ( TaskType <TaskID> )
 / Parameter (In):  TaskID Task reference
 / Parameter (Out): none
 / Description:     The task <TaskID> is transferred from the suspended state
 /                  into the ready state. The operating system ensures that the 
 /                  task code is being executed from the first statement.
 / Particularities: The service may be called from interrupt level and from 
 /                  task level.
 /                  Rescheduling after the call to ActivateTask depends on the
 /                  place it is called from (ISR, non preemptable task, 
 /                  preemptable task).
 /                  If E_OS_LIMIT is returned the activation is ignored.
 /                  When an extended task is transferred from suspended state
 /                  into ready state all its events are cleared.
 / Status:
 /  -Standard:      - No error, E_OK
 /                  - Too many task activations of <TaskID>, E_OS_LIMIT
 /  -Extended:      - Task <TaskID> is invalid, E_OS_ID
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     BCC1, BCC2, ECC1, ECC2
 / Context:
 /  -General:       Task, Cat2-ISR, interrupts not disabled by the 
 /                  application
 /  -SC1/SC2 only:  StartupHook (compatibility to older OSEK-OS)
 /     
 /--------------------------------------------------------------------------*/
/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/ActivateTask
 */
osqFunc1 StatusType osqFunc2 osActivateTask(TaskType taskIndex)
{
   /* CovComment 4:  Function: osActivateTask */
/* KB begin actTaskBody (default) */


   OS_AT_ENTRY()
   COVER(0x03D5)
#if (STATUS_LEVEL == EXTENDED_STATUS)

   if (taskIndex >= osrNumberOfAllTasks)
   {
      COVER(0x03D6)
      #if osdErrorHook 
      COVER(0x03D7)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveActivateTask_TaskID(taskIndex)
      #endif
      osAPIError(E_OS_ID, osdErrATWrongTaskID);
      #if osdErrorHook 
      COVER(0x03D8)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_AT_EXIT()
      return E_OS_ID;
   }
   ELSEWITHCOVER(0x03D9)
   if (osOwnCcb->LockIsNotNeeded.ossIntAPIStatus != 0)
   {
      COVER(0x03DA)
      #if osdErrorHook 
      COVER(0x03DB)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveActivateTask_TaskID(taskIndex)
      #endif
      osAPIError(E_OS_DISABLEDINT, osdErrATIntAPIDisabled);
      #if osdErrorHook 
      COVER(0x03DC)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_AT_EXIT()
      return E_OS_DISABLEDINT;
   }
   ELSEWITHCOVER(0x03DD)
#endif /* (STATUS_LEVEL == EXTENDED_STATUS) */


   COVER(0x03DE)
   /* user API may only be called with enabled interrupts, no nesting necessary. */
   /* KB begin osekHWosSaveDisableLevel (overwritten) */
   osSaveDisableLevel() /* save level and disable up to system level, no nesting */
   /* KB end osekHWosSaveDisableLevel */
   OS_AT_START_CRITICAL()



#if ((CC == ECC2) || (CC == BCC2))
   if (osTcbActivationCount[taskIndex] >= oskTcbAllowedActivations[taskIndex])
   {
      COVER(0x03DF)
#else
   if (osTcbTaskState[taskIndex] != SUSPENDED)
   {
      COVER(0x03E0)
#endif
      osSaveActivateTask_TaskID(taskIndex)
      COVER(0x03E1)
      osAPIError(E_OS_LIMIT, osdErrATMultipleActivation);
      COVER(0x03E2)
      OS_AT_END_CRITICAL()
      /* KB begin osekHWosRestoreEnableLevel (overwritten) */
      osRestoreEnableLevel() /* restore level saved by osSaveDisableLevel */
      /* KB end osekHWosRestoreEnableLevel */
      OS_AT_EXIT()
      return E_OS_LIMIT;
   }
   ELSEWITHCOVER(0x03E3)


      COVER(0x03E4)
      /* KB begin osekHWosDisableTimProtInterrupt (overwritten) */
      /* KB end osekHWosDisableTimProtInterrupt */

      OS_VTH_CALL_ACTIVATION_HOOK(((TaskType) taskIndex))

#if ((CC == ECC2) || (CC == BCC2))
      if (osTcbActivationCount[taskIndex] == 0)
      {
         COVER(0x03E5)
         osTcbTaskState[taskIndex] = PRE_READY;
      }
      ELSEWITHCOVER(0x03E6)
      osTcbActivationCount[taskIndex]++;
#else
      COVER(0x03E7)
      osTcbTaskState[taskIndex] = PRE_READY;
#endif

#if (osdNumberOfExtendedTasks > 0)
#if osdNumberOfExtendedTasks < osdNumberOfAllTasks
      if(taskIndex<osrNumberOfExtendedTasks)
      {
         COVER(0x03E8)
         osTcbSetEventMask[taskIndex]= 0;    /* with extended tasks clear event field */
      }
      ELSEWITHCOVER(0x03E9)
#else
      /*all tasks are extended*/
      COVER(0x03EA)
      osTcbSetEventMask[taskIndex]= 0;    /* with extended tasks clear event field */
#endif
#endif /* (osdNumberOfExtendedTasks > 0) */

      osSchedInsertTask(taskIndex);

#if osdFullPreempt || osdMixedPreempt
      /* start dispatcher only if requested by the scheduler */

      if (osdTRUE == ptrToCcb->ossStartDispatcher)
      {
         COVER(0x03EB)
            if (osOwnCcb->LockIsNotNeeded.ossLockDispatcher == 0)
            {
               /* trigger the dispatcher on the current core */
               COVER(0x03EC)
               COVER(0x03ED)
               /* KB begin osekHWosEnableTimProtInterrupt (overwritten) */
               /* KB end osekHWosEnableTimProtInterrupt */

               OS_AT_END_CRITICAL()

               /* KB begin osekHWosRestoreEnableLevel (overwritten) */
               osRestoreEnableLevel() /* restore level saved by osSaveDisableLevel */
               /* KB end osekHWosRestoreEnableLevel */
               OS_AT_EXIT()
               OS_START_DISPATCH()
               /* KB begin osekHWosLocalDispatcher (overwritten) */
               ptrToCcb2->ossCallDispatcher = 1;
               osDispatch();
               /* KB end osekHWosLocalDispatcher */
               return E_OK;
            }
            ELSEWITHCOVER(0x03EE)
      }
      ELSEWITHCOVER(0x03EF)
#endif /* osdFullPreempt || osdMixedPreempt */


      /* KB begin osekHWosEnableTimProtInterrupt (overwritten) */
      /* KB end osekHWosEnableTimProtInterrupt */



   OS_AT_END_CRITICAL()

   OS_AT_EXIT()
   COVER(0x03F0)
   /* KB begin osekHWosRestoreEnableLevel (overwritten) */
   osRestoreEnableLevel() /* restore level saved by osSaveDisableLevel */
   /* KB end osekHWosRestoreEnableLevel */
   COVER(0x03F1)
   return E_OK;

/* KB end actTaskBody */
}

#endif /* ((osdNumberOfAllTasks > 0) && !defined(osdActivateTaskNotUsed)) */


#if (osdNumberOfAllTasks > 0)
/* version for OS internal use, not using osDisable/osEnable */
/*
 * MISRA RULE 14.1 VIOLATION: The function osSysActivateTask is unused in some configurations. In order to keep the code 
 * simple and error free, it is available in more configurations than necessary.
 */
osqFunc1 StatusType osqFunc2 osSysActivateTask(TaskType taskIndex) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osSysActivateTask */
/* KB begin sysActTaskBody (default) */

   OS_AT_ENTRY()
   COVER(0x03F2)

   COVER(0x03F3)
   /* this function is called with disabled interrupts, no disabling necessary. */



#if ((CC == ECC2) || (CC == BCC2))
   if (osTcbActivationCount[taskIndex] >= oskTcbAllowedActivations[taskIndex])
   {
      COVER(0x03F4)
#else
   if (osTcbTaskState[taskIndex] != SUSPENDED)
   {
      COVER(0x03F5)
#endif
      osSaveActivateTask_TaskID(taskIndex)
      COVER(0x03F6)
      osAPIError(E_OS_LIMIT, osdErrATAlarmMultipleActivation);
      OS_AT_EXIT()
      return E_OS_LIMIT;
   }
   ELSEWITHCOVER(0x03F7)


      OS_VTH_CALL_ACTIVATION_HOOK(((TaskType) taskIndex))

#if ((CC == ECC2) || (CC == BCC2))
      if (osTcbActivationCount[taskIndex] == 0)
      {
         COVER(0x03F8)
         osTcbTaskState[taskIndex] = PRE_READY;
      }
      ELSEWITHCOVER(0x03F9)
      osTcbActivationCount[taskIndex]++;
#else
      COVER(0x03FA)
      osTcbTaskState[taskIndex] = PRE_READY;
#endif

#if (osdNumberOfExtendedTasks > 0)
#if osdNumberOfExtendedTasks < osdNumberOfAllTasks
      if(taskIndex<osrNumberOfExtendedTasks)
      {
         COVER(0x03FB)
         osTcbSetEventMask[taskIndex]= 0;    /* with extended tasks clear event field */
      }
      ELSEWITHCOVER(0x03FC)
#else
      /*all tasks are extended*/
      COVER(0x03FD)
      osTcbSetEventMask[taskIndex]= 0;    /* with extended tasks clear event field */
#endif
#endif /* (osdNumberOfExtendedTasks > 0) */

      osSchedInsertTask(taskIndex);



   OS_AT_EXIT()
   COVER(0x03FE)
   return E_OK;

/* KB end sysActTaskBody */
}
#endif /* (osdNumberOfAllTasks > 0) */

#if ((osdNumberOfAllTasks > 0) && !defined(osdTerminateTaskNotUsed))
/*-+--------------------------------------------------------------------------
 / TerminateTask
 / =============
 /
 / Syntax:          StatusType TerminateTask ( void )
 / Parameter (In):  none
 / Parameter (Out): none
 / Description:     This service causes the termination of the calling task. 
 /                  The calling task is transferred from the running state 
 /                  into the suspended state.
 / Particularities: An internal resource assigned to the calling task is
 /                  automatically released. Other resources occupied by the 
 /                  task must have been released before the call of 
 /                  TerminateTask. If a resource is still occupied in standard 
 /                  status the behaviour is undefined.
 /                  If the call was successful, TerminateTask does not return 
 /                  to the call level and the status can not be evaluated.
 /                  If the version with extended status is used, the service 
 /                  returns in case of error, and provides a status which 
 /                  can be evaluated in the application.
 /                  If the service TerminateTask is called successfully, 
 /                  it enforces a rescheduling.
 /  -SC1/SC2 only:  Ending a task function without call of TerminateTask or
 /                  ChainTask is strictly forbidden and may leave the system 
 /                  in an undefined state. This error is detected and reported
 /                  by osCAN in extended status.
 /  -SC3/SC4 only:  Ending a task function without call of TerminateTask or
 /                  ChainTask is reported by a call of the ErrorHook, 
 /                  afterwards interrupts are enabled, resources released
 /                  and a task switch is performed like TerminateTask had
 /                  been called.
 / Status:
 /  -Standard:      No return to call level
 /  -Extended:      - Task still occupies resources, E_OS_RESOURCE
 /                  - Call at interrupt level, E_OS_CALLEVEL
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     BCC1, BCC2, ECC1, ECC2
 / Context:         Task, interrupts enabled, no resources occupied
 /--------------------------------------------------------------------------*/

/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/TerminateTask
 */
osqFunc1 StatusType osqFunc2 osTerminateTask (void)
{
   /* CovComment 4:  Function: osTerminateTask */
   
   TaskType taskIndex = osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex;
   
   OS_TT_ENTRY()
   COVER(0x03FF)

#if STATUS_LEVEL == EXTENDED_STATUS
   if (osOwnCcb->LockIsNotNeeded.ossIntNestingDepth != 0)
   {
      COVER(0x0400)
      #if osdErrorHook 
      COVER(0x0401)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      #endif
      osAPIError(E_OS_CALLEVEL, osdErrTTOnInterruptLevel);
      #if osdErrorHook 
      COVER(0x0402)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_TT_EXIT()
      return E_OS_CALLEVEL;
   }
   ELSEWITHCOVER(0x0403)
#endif /* STATUS_LEVEL == EXTENDED_STATUS */


#if STATUS_LEVEL == EXTENDED_STATUS

 #if (osdNumberOfInternalResources == 0) && (osdNumberOfInterruptResources == 0)
   /* check for task resources only system */
   if (osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio != oskTcbHomePrio[taskIndex])
   {
      COVER(0x0404)
 #else
   /* check for mixed resource system (task, interrupt and internal) */
   if (osTcbResourceCounter[taskIndex] != 0)
   {
      COVER(0x0405)
 #endif
      #if osdErrorHook 
      COVER(0x0406)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      #endif
      osAPIError(E_OS_RESOURCE, osdErrTTResourcesOccupied);
      #if osdErrorHook 
      COVER(0x0407)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_TT_EXIT()
      return E_OS_RESOURCE;
   }
   ELSEWITHCOVER(0x0408)

   if (osCheckInterruptsEnabled() == 0)
   {
      COVER(0x0409)
      #if osdErrorHook 
      COVER(0x040A)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      #endif
      osAPIError(E_OS_DISABLEDINT, osdErrTTDisabledInterrupts);
      #if osdErrorHook 
      COVER(0x040B)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_TT_EXIT()
      return E_OS_DISABLEDINT;
   }
   ELSEWITHCOVER(0x040C)
#endif

   COVER(0x040D)
   /* KB begin osekHWosDisableLevel (overwritten) */
   osDisableLevel(); /* disable interrupts up to system level */
   /* KB end osekHWosDisableLevel */
   OS_TT_START_CRITICAL()

   /* KB begin osekHWosDisableTimProtInterrupt (overwritten) */
   /* KB end osekHWosDisableTimProtInterrupt */

#if osdPostTaskHook
   COVER(0x040E)
   /* call PostTaskHook before clearing osRunTaskIndex! */
   osPostTaskHook();
#endif


   /* KB begin osekHWosEnableTimProtInterrupt (overwritten) */
   /* KB end osekHWosEnableTimProtInterrupt */


#if ((CC == ECC2) || (CC == BCC2))
#if (STATUS_LEVEL == EXTENDED_STATUS)
   COVER(0x040F)
   osSysErrAssert(osTcbActivationCount[taskIndex], osdErrTTNotActivated)
#endif
   
   COVER(0x0410)
   osTcbActivationCount[taskIndex]--;
   
   if (osTcbActivationCount[taskIndex] != 0)
   {  
      COVER(0x0411)
      osTcbTaskState[taskIndex] = PRE_READY;
   }
   else
   {
      COVER(0x0412)
      osTcbTaskState[taskIndex] = SUSPENDED;
   }
#else
   COVER(0x0413)
   osTcbTaskState[taskIndex] = SUSPENDED;
#endif
   
   osSchedRemoveRunningTask();

   COVER(0x0414)
   /* KB begin osPrepareForStackCorrection (default) */
   /* KB end osPrepareForStackCorrection */

#if (osdStackCheck || osdCallTimingHooks)
   COVER(0x0415)
   osOwnCcb->LockIsNotNeeded.ossLastActiveTaskIndex = taskIndex;
#endif

   osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex = osdNoActiveTask;
   osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio  = osdNoActivePrio;

   /* for TerminateTask, osSchedRemoveRunningTask() always sets
    * ossStartDispatcher to osdTRUE
    * (same task is never running when reaching this point of code) */

   OS_TT_END_CRITICAL()
   OS_TT_EXIT()

   /* KB begin osekHWosEnableLevel (overwritten) */
   osEnableLevel(); /* enable task level interrupt */
   /* KB end osekHWosEnableLevel */

   /* start dispatcher */
   OS_START_DISPATCH()
   /* KB begin osekHWosLocalDispatcher (overwritten) */
   ptrToCcb2->ossCallDispatcher = 1;
   osDispatch();
   /* KB end osekHWosLocalDispatcher */

   /* KB begin osekHWosRollBackStack (default) */
   /* KB end osekHWosRollBackStack */
/* TR:SPMF12:0011 Start */
   /* KB begin osekHWAfterOsDispatchInTT (overwritten) */
   osDisableGlobal();
   return E_OK;
   /* KB end osekHWAfterOsDispatchInTT */
/* TR:SPMF12:0011 End */

} /* END OF osTerminateTask */

#endif /* ((osdNumberOfAllTasks > 0) && !defined(osdTerminateTaskNotUsed)) */


#if ((osdNumberOfAllTasks > 0) && !defined(osdChainTaskNotUsed))
/*-+--------------------------------------------------------------------------
 / ChainTask
 / =========
 /
 / Syntax:          StatusType ChainTask ( TaskType <TaskID> )
 / Parameter (In):  TaskID Reference to the task to be activated after the 
 /                  current task has been terminated.
 / Parameter (Out): none
 / Description:     This service causes the termination of the calling task. 
 /                  After termination of the calling task a succeeding 
 /                  task <TaskID> is activated. Using this service 
 /                  ensures that the succeeding task starts to run 
 /                  earliest after the calling task has been terminated.
 / Particularities: If the succeeding task is identical with the current task, 
 /                  this does not result in multiple requests. The task is not 
 /                  transferred to the suspended state. An internal resource 
 /                  assigned to the calling task is automatically released, 
 /                  even if the succeeding task is identical with the current 
 /                  task. Other resources occupied by the calling task must 
 /                  have been released before ChainTask is called. If a 
 /                  resource is still occupied in standard status the 
 /                  behaviour is undefined.
 /                  If called successfully, ChainTask does not return to the 
 /                  call level and the status can not be evaluated.
 /                  In case of error the service returns to the calling task 
 /                  and provides a status which can then be evaluated in the
 /                  application.
 /                  If the service ChainTask is called successfully, this 
 /                  enforces a rescheduling.
 /                  If E_OS_LIMIT is returned the activation is ignored.
 /                  When an extended task is transferred from suspended state
 /                  into ready state all its events are cleared.
 /  -SC1/SC2 only:  Ending a task function without call of TerminateTask or
 /                  ChainTask is strictly forbidden and may leave the system 
 /                  in an undefined state. This error is detected and reported
 /                  by osCAN in extended status.
 /  -SC3/SC4 only:  Ending a task function without call of TerminateTask or
 /                  ChainTask is reported by a call of the ErrorHook, 
 /                  afterwards interrupts are enabled, resources released
 /                  and a task switch is performed like TerminateTask had
 /                  been called.
 / Status:
 /  -Standard:      - No return to call level
 /                  - Too many task activations of <TaskID>, E_OS_LIMIT
 /  -Extended:      - Task <TaskID> is invalid, E_OS_ID
 /                  - Calling task still occupies resources, E_OS_RESOURCE
 /                  - Call at interrupt level, E_OS_CALLEVEL
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     BCC1, BCC2, ECC1, ECC2
 / Context:         Task, interrupts enabled, no resources occupied
 /--------------------------------------------------------------------------*/

/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/ChainTask
 */
osqFunc1 StatusType osqFunc2 osChainTask(TaskType taskIndex)
{
   /* CovComment 4:  Function: osChainTask */
   
   TaskType activeTaskID;

   OS_HT_ENTRY()
   COVER(0x0416)

#if STATUS_LEVEL == EXTENDED_STATUS
   if (osOwnCcb->LockIsNotNeeded.ossIntNestingDepth != 0)
   {
      COVER(0x0417)
      #if osdErrorHook 
      COVER(0x0418)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveChainTask_TaskID(taskIndex)
      #endif
      osAPIError(E_OS_CALLEVEL, osdErrHTOnInterruptLevel);
      #if osdErrorHook 
      COVER(0x0419)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_HT_EXIT()
      return E_OS_CALLEVEL;
   }
   ELSEWITHCOVER(0x041A)
#endif /* STATUS_LEVEL == EXTENDED_STATUS */

   activeTaskID = osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex;
   

#if STATUS_LEVEL == EXTENDED_STATUS

#if (osdNumberOfInternalResources == 0) && (osdNumberOfInterruptResources == 0)
   /* check for task resources only system */
   if (osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio != oskTcbHomePrio[activeTaskID])
   {
      COVER(0x041B)
#else
   /* check for mixed resource system (task, interrupt and internal) */
   if (osTcbResourceCounter[activeTaskID] != 0)
   {
      COVER(0x041C)
#endif
      #if osdErrorHook 
      COVER(0x041D)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveChainTask_TaskID(taskIndex)
      #endif
      osAPIError(E_OS_RESOURCE, osdErrHTResourcesOccupied);
      #if osdErrorHook 
      COVER(0x041E)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_HT_EXIT()
      return E_OS_RESOURCE;
   }
   ELSEWITHCOVER(0x041F)

   if (taskIndex >= osrNumberOfAllTasks)
   {
      COVER(0x0420)
      #if osdErrorHook 
      COVER(0x0421)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveChainTask_TaskID(taskIndex)
      #endif
      osAPIError(E_OS_ID, osdErrHTWrongTaskID);
      #if osdErrorHook 
      COVER(0x0422)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_HT_EXIT()
      return E_OS_ID;
   }
   ELSEWITHCOVER(0x0423)

   if (osCheckInterruptsEnabled() == 0)
   {
      COVER(0x0424)
      #if osdErrorHook 
      COVER(0x0425)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveChainTask_TaskID(taskIndex)
      #endif
      osAPIError(E_OS_DISABLEDINT, osdErrHTInterruptsDisabled);
      #if osdErrorHook 
      COVER(0x0426)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_HT_EXIT()
      return E_OS_DISABLEDINT;
   }
   ELSEWITHCOVER(0x0427)
#endif

   COVER(0x0428)
   /* KB begin osekHWosDisableLevel (overwritten) */
   osDisableLevel(); /* disable interrupts up to system level */
   /* KB end osekHWosDisableLevel */
   OS_HT_START_CRITICAL()



   if (taskIndex != activeTaskID)
   {
#if ((CC == ECC2) || (CC == BCC2))
      if (osTcbActivationCount[taskIndex] >= oskTcbAllowedActivations[taskIndex])
      {
         COVER(0x0429)
#else
      if (osTcbTaskState[taskIndex] != SUSPENDED)
      {
         COVER(0x042A)
#endif
         osSaveChainTask_TaskID(taskIndex)
         osAPIError(E_OS_LIMIT, osdErrHTMultipleActivation);
         OS_HT_END_CRITICAL()
         OS_HT_EXIT()
         /* KB begin osekHWosEnableLevel (overwritten) */
         osEnableLevel(); /* enable task level interrupt */
         /* KB end osekHWosEnableLevel */
         return E_OS_LIMIT;
      }
      ELSEWITHCOVER(0x042B)
   }
   ELSEWITHCOVER(0x042C)

   /*************************************************************************
    * terminate old task
    *************************************************************************/

   /* KB begin osekHWosDisableTimProtInterrupt (overwritten) */
   /* KB end osekHWosDisableTimProtInterrupt */

   /* call hook routine for the terminated task */
#if osdPostTaskHook
   COVER(0x042D)
   /* call PostTaskHook before clearing osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex! */
   osPostTaskHook();
#endif

#if ((CC == ECC2) || (CC == BCC2))
#if (STATUS_LEVEL == EXTENDED_STATUS)
   COVER(0x042E)
   osSysErrAssert(osTcbActivationCount[activeTaskID], osdErrHTNotActivated)
#endif

   osTcbActivationCount[activeTaskID]--;

   if (osTcbActivationCount[activeTaskID] != 0)
   {  
      COVER(0x042F)
      osTcbTaskState[activeTaskID] = PRE_READY;
   }
   else
   {
      COVER(0x0430)
      osTcbTaskState[activeTaskID] = SUSPENDED;
   }
#else /* ((CC == ECC2) || (CC == BCC2)) */
   COVER(0x0431)
   osTcbTaskState[activeTaskID] = SUSPENDED;
#endif /* ((CC == ECC2) || (CC == BCC2)) else */

   COVER(0x0432)
   osSchedRemoveRunningTask();

   /* KB begin osPrepareForStackCorrection (default) */
   /* KB end osPrepareForStackCorrection */

#if (osdStackCheck || osdCallTimingHooks)
   COVER(0x0433)
   osOwnCcb->LockIsNotNeeded.ossLastActiveTaskIndex = activeTaskID;
#endif


   /* KB begin osekHWosEnableTimProtInterrupt (overwritten) */
   /* KB end osekHWosEnableTimProtInterrupt */
   osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex = osdNoActiveTask;
   osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio  = osdNoActivePrio;



      /*************************************************************************
       * now activate the new task
       *************************************************************************/
#if (STATUS_LEVEL == STANDARD_STATUS)
      #if ((CC == ECC2) || (CC == BCC2))
      if (osTcbActivationCount[taskIndex] < oskTcbAllowedActivations[taskIndex])
      {
         COVER(0x0434)
      #else
      if (osTcbTaskState[taskIndex] == SUSPENDED)
      {
         COVER(0x0435)
      #endif
#endif

      OS_VTH_CALL_ACTIVATION_HOOK(((TaskType) taskIndex))

#if (osdNumberOfExtendedTasks > 0)
 #if osdNumberOfExtendedTasks < osdNumberOfAllTasks
         /* with extended tasks clear event field */
         if(taskIndex < osrNumberOfExtendedTasks)
         {
            COVER(0x0436)
            osTcbSetEventMask[taskIndex]= 0;
         }
         ELSEWITHCOVER(0x0437)
 #else /* ((osdNumberOfExtendedTasks < osdNumberOfAllTasks) || (osdLib)) */
         COVER(0x0438)
         /* no basic tasks, so for all tasks clear event field */
         osTcbSetEventMask[taskIndex] = 0;
 #endif /* ((osdNumberOfExtendedTasks < osdNumberOfAllTasks) || (osdLib)) */
#endif /* (osdNumberOfExtendedTasks > 0) */

#if ((CC == ECC2) || (CC == BCC2))
         if (osTcbActivationCount[taskIndex] == 0)
         {
            COVER(0x0439)
            osTcbTaskState[taskIndex] = PRE_READY;
         }
         ELSEWITHCOVER(0x043A)
         osTcbActivationCount[taskIndex]++;
#else
         COVER(0x043B)
         osTcbTaskState[taskIndex] = PRE_READY;
#endif
         COVER(0x043C)
         osSchedInsertTask(taskIndex);
#if (STATUS_LEVEL == STANDARD_STATUS)
      }
      ELSEWITHCOVER(0x043D)
#endif
   COVER(0x043E)


   OS_HT_END_CRITICAL()
   OS_HT_EXIT()

   /* KB begin osekHWosEnableLevel (overwritten) */
   osEnableLevel(); /* enable task level interrupt */
   /* KB end osekHWosEnableLevel */

   /* for ChainTask, osSchedRemoveRunningTask() always sets
    * ossStartDispatcher to osdTRUE
    * (same task is never running when reaching this point of code) */
   /* start dispatcher */
   OS_START_DISPATCH()
   /* KB begin osekHWosLocalDispatcher (overwritten) */
   ptrToCcb2->ossCallDispatcher = 1;
   osDispatch();
   /* KB end osekHWosLocalDispatcher */

   /* KB begin osekHWosRollBackStack (default) */
   /* KB end osekHWosRollBackStack */
   /* TR:SPMF12:0012 Start */
   /* KB begin osekHWAfterOsDispatchInHT (overwritten) */
   osDisableGlobal();
   return E_OK;
   /* KB end osekHWAfterOsDispatchInHT */
   /* TR:SPMF12:0012 End */

} /* END OF osChainTask */
#endif /* ((osdNumberOfAllTasks > 0) && !defined(osdChainTaskNotUsed)) */

#if ((osdNumberOfAllTasks > 0) && !defined(osdScheduleNotUsed))
/*-+--------------------------------------------------------------------------
 / Schedule
 / ========
 /
 / Syntax:          StatusType Schedule ( void )
 / Parameter (In):  none
 / Parameter (Out): none
 / Description:     If a higher-priority task is ready, the internal resource 
 /                  of the current task is released, the current task is put 
 /                  into the ready state, its context is saved and the 
 /                  higher-priority task is executed.
 /                  Otherwise the calling task is continued.
 / Particularities: Rescheduling can only take place if an internal resource is
 /                  assigned to the calling task during system generation.
 /                  (A non-preemptable task is seen as a task with a resource
 /                  of highest task priority assigned.) For these tasks, Schedule 
 /                  enables a processor assignment to other tasks with lower 
 /                  priority than the ceiling priority of the internal
 /                  resource and higher priority than the priority of the 
 /                  calling task in application-specific locations. 
 /                  When returning from Schedule, the internal resource has 
 /                  been taken again.
 /                  This service has no influence on tasks with no internal 
 /                  resource assigned (preemptable tasks).
 / Status:
 /  -Standard:      - No error, E_OK
 /  -Extended:      - Call at interrupt level, E_OS_CALLEVEL
 /                  - Calling task occupies resources, E_OS_RESOURCE
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     BCC1, BCC2, ECC1, ECC2
 / Context:         Task, interrupts enabled, no resources occupied
 /--------------------------------------------------------------------------*/

/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/Schedule
 */
osqFunc1 StatusType osqFunc2 osSchedule(void)
{
   /* CovComment 4:  Function: osSchedule */
   
#if STATUS_LEVEL == EXTENDED_STATUS
   TaskType activeTaskID;
#endif /* STATUS_LEVEL == EXTENDED_STATUS */

   OS_SH_ENTRY()

   COVER(0x043F)
#if STATUS_LEVEL == EXTENDED_STATUS

   if (osOwnCcb->LockIsNotNeeded.ossIntNestingDepth != 0)
   {
      COVER(0x0440)
      #if osdErrorHook 
      COVER(0x0441)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      #endif
      osAPIError(E_OS_CALLEVEL, osdErrSHOnInterruptLevel);
      #if osdErrorHook 
      COVER(0x0442)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_SH_EXIT()
      return E_OS_CALLEVEL;
   }
   ELSEWITHCOVER(0x0443)

   if (osCheckInterruptsEnabled() == 0)
   {
      COVER(0x0444)
      #if osdErrorHook 
      COVER(0x0445)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      #endif
      osAPIError(E_OS_DISABLEDINT, osdErrSHInterruptsDisabled);
      #if osdErrorHook 
      COVER(0x0446)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_SH_EXIT()
      return E_OS_DISABLEDINT;
   }
   ELSEWITHCOVER(0x0447)

   activeTaskID = osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex;


#if (osdNumberOfInternalResources == 0) && (osdNumberOfInterruptResources == 0)
   /* check for task resources only system */
   if (osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio != oskTcbHomePrio[activeTaskID])
   {
      COVER(0x0448)
#else
   /* check for mixed resource system (task, interrupt and internal) */
   if (osTcbResourceCounter[activeTaskID] != 0)
   {
      COVER(0x0449)
#endif
      #if osdErrorHook 
      COVER(0x044A)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      #endif
      osAPIError(E_OS_RESOURCE, osdErrSHResourcesOccupied);
      #if osdErrorHook 
      COVER(0x044B)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_SH_EXIT()
      return E_OS_RESOURCE;
   }
   ELSEWITHCOVER(0x044C)

   osSysErrAssert(((oskTcbTaskFlags[activeTaskID] & osdTaskFlagNotUsingSchedule) == 0U),
       osdErrSHScheduleNotAllowed)   /* NOCOV */     

#endif /* #if STATUS_LEVEL == EXTENDED_STATUS */

   COVER(0x044D)
   /* KB begin osekHWosDisableLevel (overwritten) */
   osDisableLevel(); /* disable interrupts up to system level */
   /* KB end osekHWosDisableLevel */
   OS_SH_START_CRITICAL()
   /* KB begin osekHWosDisableTimProtInterrupt (overwritten) */
   /* KB end osekHWosDisableTimProtInterrupt */

   osSchedOnHomePrio();

   if (osdTRUE == ptrToCcb->ossStartDispatcher)
   {
      COVER(0x044E)
      OS_SH_END_CRITICAL()
      OS_SH_EXIT()
      /* KB begin osekHWosEnableTimProtInterrupt (overwritten) */
      /* KB end osekHWosEnableTimProtInterrupt */
      /* KB begin osekHWosEnableLevel (overwritten) */
      osEnableLevel(); /* enable task level interrupt */
      /* KB end osekHWosEnableLevel */

      /* start dispatcher */
      OS_START_DISPATCH()
      /* KB begin osekHWosLocalDispatcher (overwritten) */
      ptrToCcb2->ossCallDispatcher = 1;
      osDispatch();
      /* KB end osekHWosLocalDispatcher */
      return E_OK;
   }
   ELSEWITHCOVER(0x044F)

#if osdNumberOfInternalResources > 0
   COVER(0x0450)
   osSchedBackToRunPrio();
#endif

   COVER(0x0451)
   
   /* KB begin osekHWosEnableTimProtInterrupt (overwritten) */
   /* KB end osekHWosEnableTimProtInterrupt */
   OS_SH_END_CRITICAL()
   OS_SH_EXIT()
   /* KB begin osekHWosEnableLevel (overwritten) */
   osEnableLevel(); /* enable task level interrupt */
   /* KB end osekHWosEnableLevel */
   return E_OK;
} /* END OF osSchedule */

#endif /* ((osdNumberOfAllTasks > 0) && !defined(osdScheduleNotUsed)) */


#if ((osdNumberOfAllTasks > 0) && !defined(osdGetTaskIDNotUsed))
/*-+--------------------------------------------------------------------------
 / GetTaskID
 / =========
 /
 / Syntax:          StatusType GetTaskID ( TaskRefType <TaskID> )
 / Parameter (In):  none
 / Parameter (Out): TaskID Reference to the task which is currently running
 / Description:     GetTaskID writes the information about the TaskID of the 
 /                  task which is currently running to the location, defined
 /                  by the reference TaskID.
 / Particularities: Allowed on task level, ISR level and in several hook 
 /                  routines.
 /                  This service is intended to be used by library functions 
 /                  and hook routines.
 /                  If <TaskID> can't be evaluated (no task currently 
 /                  running), the service returns INVALID_TASK as TaskID.
 / Status:
 /  -Standard:      - No error, E_OK
 /  -Extended:      - No error, E_OK
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     BCC1, BCC2, ECC1, ECC2
 / Context:         Task, Cat2-ISR, ErrorHook, PreTaskHook, PostTaskHook,
 /                  ProtectionHook, interrupts not disabled by the 
 /                  application
 /--------------------------------------------------------------------------*/

/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/GetTaskID
 */
osqFunc1 StatusType osqFunc2 osGetTaskID (TaskRefType TaskId)
{
   /* CovComment 4:  Function: osGetTaskID */

   OS_GI_ENTRY()
   COVER(0x0452)


#if STATUS_LEVEL == EXTENDED_STATUS

   if (osOwnCcb->LockIsNotNeeded.ossIntAPIStatus != 0)
   {
      COVER(0x0453)
      #if osdErrorHook 
      COVER(0x0454)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveGetTaskID_TaskID(TaskId)
      #endif
      osAPIError(E_OS_DISABLEDINT, osdErrGIIntAPIDisabled);
      #if osdErrorHook 
      COVER(0x0455)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_GI_EXIT()
      return E_OS_DISABLEDINT;
   }
   ELSEWITHCOVER(0x0456)

#endif
   COVER(0x0457)
   COVER(0x0458)
   *TaskId = osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex;

   OS_GI_EXIT()
   return E_OK;
} /* END OF osGetTaskID */

#endif /* ((osdNumberOfAllTasks > 0) && !defined(osdGetTaskIDNotUsed)) */


#if ((osdNumberOfAllTasks > 0) && !defined(osdGetTaskStateNotUsed))
/*-+--------------------------------------------------------------------------
 / GetTaskState
 / ============
 /
 / Syntax:          StatusType GetTaskState ( TaskType <TaskID>,
 /                                            TaskStateRefType <State> )
 / Parameter (In):  TaskID Task reference
 / Parameter (Out): State Reference to the state of the task <TaskID>
 / Description:     Writes the current state of a task (RUNNING, READY, WAITING, 
 /                  SUSPENDED) to the location, defined by the parameter
 /                  State.
 / Particularities: The service may be called from interrupt service routines, 
 /                  task level, and some hook routines.
 /                  When a call is made from a task in a full preemptive system,
 /                  the result may already be incorrect at the time of 
 /                  evaluation.
 /                  When the service is called for a task, which is multiply
 /                  activated, the state is set to running if any instance 
 /                  of the task is running.
 / Status:
 /  -Standard:      - No error, E_OK
 /  -Extended:      - Task <TaskID> is invalid, E_OS_ID
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     BCC1, BCC2, ECC1, ECC2
 / Context:         Task, Cat2-ISR, ErrorHook, PreTaskHook, PostTaskHook,
 /                  interrupts not disabled by the application
/--------------------------------------------------------------------------*/

/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/GetTaskState
 */
osqFunc1 StatusType osqFunc2 osGetTaskState(TaskType TaskId, TaskStateRefType State)
{
   /* CovComment 4:  Function: osGetTaskState */

   OS_GS_ENTRY()
   COVER(0x0459) 


#if STATUS_LEVEL == EXTENDED_STATUS
   if (TaskId >= osrNumberOfAllTasks)
   {
      COVER(0x045A) 
      #if osdErrorHook 
      COVER(0x045B) 
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveGetTaskState_TaskID(TaskId)
      osSaveGetTaskState_State(State)
      #endif
      osAPIError(E_OS_ID, osdErrGSWrongTaskID);
      #if osdErrorHook 
      COVER(0x045C) 
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_GS_EXIT()
      return E_OS_ID;
   }
   ELSEWITHCOVER(0x045D) 
#endif


#if STATUS_LEVEL == EXTENDED_STATUS

   if (osOwnCcb->LockIsNotNeeded.ossIntAPIStatus != 0)
   {
      COVER(0x045E) 
      #if osdErrorHook 
      COVER(0x045F) 
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveGetTaskState_TaskID(TaskId)
      osSaveGetTaskState_State(State)
      #endif
      osAPIError(E_OS_DISABLEDINT, osdErrGSIntAPIDisabled);
      #if osdErrorHook 
      COVER(0x0460) 
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_GS_EXIT()
      return E_OS_DISABLEDINT;
   }
   ELSEWITHCOVER(0x0461) 

#endif

   COVER(0x0462) 
   *State = osTcbTaskState[TaskId];

   /* change PRE_READY to READY */
   if ((*State) == PRE_READY)
   {
      COVER(0x0463)
      *State = READY;
   }
   ELSEWITHCOVER(0x0464) 

   OS_GS_EXIT()
   return E_OK;
} /* END OF osGetTaskState */

#endif /* ((osdNumberOfAllTasks > 0) && !defined(osdGetTaskStateNotUsed)) */

#if (osdNumberOfAllTasks == 0)
/* KB begin osekHWosOsekTaskDummy (default) */
/* KB end osekHWosOsekTaskDummy */
#endif /* (osdNumberOfAllTasks == 0) */

/* KB begin osekEndOfCModule (overwritten) */
#pragma ghs section bss=default
#pragma ghs section data=default
#pragma ghs section sbss=default
#pragma ghs section sdata=default
#pragma ghs section text=default
#pragma ghs section rodata=default
#pragma ghs section rosdata=default
/* KB end osekEndOfCModule */

/* END OF MODULE osektask.c */


/* Kernbauer Version: 2.16 Konfiguration: RH850 Erzeugungsgangnummer: 214 Zweig: 1 */

/*****************************************************************************
| Project Name: MICROSAR OS
|    File Name: osekevnt.c
|
|  General code: @Version: 9.01.04@
|  Module version: $vv$=1.57
|
|  Description: osek API-functions for handling events
|               - SetEvent
|               - ClearEvent
|               - GetEvent
|               - WaitEvent
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

#ifndef QUEUED_EVENT
	#define QUEUED_EVENT
#endif	

//EventMaskType TskEvtCnt[6]={0,0,0,0,0,0};		
/*
EventTskEvtCnt
FastCycEvtCnt;
SlowCycEvtCnt;
SlowJobEvtCnt;
SysSwitchHiEvtCnt;
SysSwitchLoEvtCnt;
*/	

/* CovComment 0:  file: osekevnt.c */

/* KB begin osekStartOfCModule (overwritten) */
#pragma ghs section bss=".os_bss"
#pragma ghs section data=".os_data"
#pragma ghs section sbss=".os_sbss"
#pragma ghs section sdata=".os_sdata"
#pragma ghs section text=".os_text"
#pragma ghs section rodata=".os_rodata"
#pragma ghs section rosdata=".os_rosdata"
/* KB end osekStartOfCModule */

#if ((CC == ECC1) || (CC == ECC2)) && (osdNumberOfExtendedTasks > 0)

/*
 *  MICROSAR OS timing hooks call macro, used by event API below
 */
/* CovComment 4:  Macro: OS_VTH_CALL_SETEVENT_HOOK */
#if osdCallTimingHooks
#define OS_VTH_CALL_SETEVENT_HOOK(TaskId, EventMask, StateChange)              \
   COVER(0x0290)                                                                     \
   OS_VTH_SETEVENT((TaskId), (EventMask), (StateChange), 0, 0)
#else
#define OS_VTH_CALL_SETEVENT_HOOK(TaskId, EventMask, StateChange) \
   COVER(0x0291)
#endif




#ifndef osdSetEventNotUsed
/*-+--------------------------------------------------------------------------
 / SetEvent
 / ========          
 /
 / Syntax:          StatusType SetEvent ( TaskType <TaskID>
 /                                        EventMaskType <Mask> )
 / Parameter (In):  - TaskID Reference to the task for which one or 
 /                    several events are to be set.
 /                  - Mask Mask of the events to be set
 / Parameter (Out): none
 / Description:     The service might be called from an interrupt service 
 /                  routine and from the task level, but not from hook 
 /                  routines.
 /                  The events of task <TaskID> are set according to the 
 /                  event mask <Mask>. Calling SetEvent causes the task 
 /                  <TaskID> to be transferred to the ready state, if it
 /                  has been waiting for at least one of the events 
 /                  specified in <Mask>.
 / Particularities: Any events not set in the event mask remain unchanged.
 / Status:
 /  -Standard:      - No error, E_OK
 /  -Extended:      - Task <TaskID> is invalid, E_OS_ID
 /                  - Referenced task is no extended task, E_OS_ACCESS
 /                  - Events can not be set as the referenced task is in the
 /                    suspended state, E_OS_STATE
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     ECC1, ECC2
 / Context:         Task, Cat2-ISR, interrupts not disabled by the application
 /--------------------------------------------------------------------------*/

/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/SetEvent
 */

// change:
// lowest bit of setMask is used as flag;
// other bits used as counter to prevent missing event.
osqFunc1 StatusType osqFunc2 osSetEvent(TaskType taskIndex, EventMaskType setMask)
{
   /* CovComment 4:  Function: osSetEvent */
/* KB begin setEventBody (default) */

   OS_SE_ENTRY()
   COVER(0x0292)

#if STATUS_LEVEL == EXTENDED_STATUS
   COVER(0x0293)

   if (taskIndex >= osrNumberOfAllTasks)
   {
      COVER(0x0294)
      #if osdErrorHook 
      COVER(0x0295)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveSetEvent_TaskID(taskIndex)
      osSaveSetEvent_Mask(setMask)
      #endif
      osAPIError(E_OS_ID, osdErrSEWrongTaskID);
      #if osdErrorHook 
      COVER(0x0296)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_SE_EXIT()
      return E_OS_ID;
   }
   ELSEWITHCOVER(0x0297)

#if osdNumberOfExtendedTasks != osdNumberOfAllTasks
   if (taskIndex >= osrNumberOfExtendedTasks)
   {
      COVER(0x0298)
      #if osdErrorHook 
      COVER(0x0299)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveSetEvent_TaskID(taskIndex)
      osSaveSetEvent_Mask(setMask)
      #endif
      osAPIError(E_OS_ACCESS, osdErrSENotExtendedTask);
      #if osdErrorHook 
      COVER(0x029A)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_SE_EXIT()
      return E_OS_ACCESS;
   }
   ELSEWITHCOVER(0x029B)
#endif

   if (osOwnCcb->LockIsNotNeeded.ossIntAPIStatus != 0)
   {
      COVER(0x029C)
      #if osdErrorHook 
      COVER(0x029D)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveSetEvent_TaskID(taskIndex)
      osSaveSetEvent_Mask(setMask)
      #endif
      osAPIError(E_OS_DISABLEDINT, osdErrSEIntAPIDisabled);
      #if osdErrorHook 
      COVER(0x029E)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_SE_EXIT()
      return E_OS_DISABLEDINT;
   }
   ELSEWITHCOVER(0x029F)

#endif   /* STATUS_LEVEL == EXTENDED_STATUS */


   COVER(0x02A0)
   /* KB begin osekHWosSaveDisableLevel (overwritten) */
   osSaveDisableLevel() /* save level and disable up to system level, no nesting */
   /* KB end osekHWosSaveDisableLevel */
   OS_SE_START_CRITICAL()


#if STATUS_LEVEL == EXTENDED_STATUS

   if (osTcbTaskState[taskIndex] == SUSPENDED)
   {
      COVER(0x02A1)
      osSaveSetEvent_TaskID(taskIndex)
      osSaveSetEvent_Mask(setMask)
      osAPIError(E_OS_STATE, osdErrSETaskSuspended);
      COVER(0x02A2)
      OS_SE_END_CRITICAL()
      /* KB begin osekHWosRestoreEnableLevel (overwritten) */
      osRestoreEnableLevel() /* restore level saved by osSaveDisableLevel */
      /* KB end osekHWosRestoreEnableLevel */
      OS_SE_EXIT()
      return E_OS_STATE;
   }
   ELSEWITHCOVER(0x02A3)
#endif

   COVER(0x02A4)
   /* KB begin osekHWosDisableTimProtInterrupt (overwritten) */
   /* KB end osekHWosDisableTimProtInterrupt */

   COVER(0x02A5)
	
#ifdef QUEUED_EVENT
   //TskEvtCnt[taskIndex]++;   
   osTcbSetEventMask[taskIndex] +=2;
#endif

   osTcbSetEventMask[taskIndex]|= setMask; /* set event flag(s)    */

   if (osTcbTaskState[taskIndex] == WAITING)
   {
      /* task is waiting */
      if ((osTcbSetEventMask[taskIndex] & osTcbWaitEventMask[taskIndex]) != 0)
      {
         COVER(0x02A6)

         OS_VTH_CALL_SETEVENT_HOOK(((TaskType) taskIndex)   ,
                                   ((EventMaskType) setMask),
                                   ((osbool) osdTRUE)       )

         /*  satisfied, change from waiting to ready */
         osTcbTaskState[taskIndex] = READY;
         
         osSchedInsertTask(taskIndex);

#if osdFullPreempt || osdMixedPreempt
         if (osdTRUE == ptrToCcb->ossStartDispatcher)
         {
            COVER(0x02A7)
               if (osOwnCcb->LockIsNotNeeded.ossLockDispatcher == 0)
               {
                  /* trigger the dispatcher on the current core */
                  COVER(0x02A8)
                  COVER(0x02A9)
                  /* KB begin osekHWosEnableTimProtInterrupt (overwritten) */
                  /* KB end osekHWosEnableTimProtInterrupt */

                  OS_SE_END_CRITICAL()
                  /* KB begin osekHWosRestoreEnableLevel (overwritten) */
                  osRestoreEnableLevel() /* restore level saved by osSaveDisableLevel */
                  /* KB end osekHWosRestoreEnableLevel */
                  OS_SE_EXIT()
                  OS_START_DISPATCH()
                  /* KB begin osekHWosLocalDispatcher (overwritten) */
                  ptrToCcb2->ossCallDispatcher = 1;
                  osDispatch();
                  /* KB end osekHWosLocalDispatcher */
                  return E_OK;
               }
               ELSEWITHCOVER(0x02AA)
         }
         ELSEWITHCOVER(0x02AB)
#endif /* osdFullPreempt || osdMixedPreempt */
      }/*if ((EventsRequireStateChange == osdTRUE) && (StateChangeAllowed == osdTRUE))*/
      else
      {
         COVER(0x02AC)
         /* no change of task state as the task was not waiting for this event or timing protection prevented the state change */
         OS_VTH_CALL_SETEVENT_HOOK(((TaskType) taskIndex)   ,
                                   ((EventMaskType) setMask),
                                   ((osbool) osdFALSE)       )
      }
   }/* if (osTcbTaskState[taskIndex] == WAITING) */
   else
   {
      COVER(0x02AD)
      /* no change of task state as the task was not waiting at all */
      OS_VTH_CALL_SETEVENT_HOOK(((TaskType) taskIndex)   ,
                                ((EventMaskType) setMask),
                                ((osbool) osdFALSE)       )
   }


   COVER(0x02AE)
   /* KB begin osekHWosEnableTimProtInterrupt (overwritten) */
   /* KB end osekHWosEnableTimProtInterrupt */

   OS_SE_END_CRITICAL()
   /* KB begin osekHWosRestoreEnableLevel (overwritten) */
   osRestoreEnableLevel() /* restore level saved by osSaveDisableLevel */
   /* KB end osekHWosRestoreEnableLevel */
   OS_SE_EXIT()
   return E_OK; /* TR:SPMF82:0002 */

/* KB end setEventBody */
} /* END OF osSetEvent */
#endif


#if ((osdNumberOfAlarmSetEvent > 0) || (osdNumberOfSTSetEvent > 0))
/*
 * MISRA RULE 14.1 VIOLATION: The function osSysSetEvent is unused in some configurations. In order to keep the code 
 * simple and error free, it is available in more configurations than necessary.
 */
osqFunc1 StatusType osqFunc2  osSysSetEvent(TaskType taskIndex, EventMaskType setMask) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osSysSetEvent */
/* KB begin sysSetEventBody (default) */

   OS_SE_ENTRY()
   COVER(0x02AF)




#if STATUS_LEVEL == EXTENDED_STATUS

   if (osTcbTaskState[taskIndex] == SUSPENDED)
   {
      COVER(0x02B0)
      osSaveSetEvent_TaskID(taskIndex)
      osSaveSetEvent_Mask(setMask)
      osAPIError(E_OS_STATE, osdErrSETaskSuspended);
      OS_SE_EXIT()
      return E_OS_STATE;
   }
   ELSEWITHCOVER(0x02B1)
#endif

   COVER(0x02B2)
   osTcbSetEventMask[taskIndex]|= setMask; /* set event flag(s)    */

   if (osTcbTaskState[taskIndex] == WAITING)
   {
      /* task is waiting */
      
      COVER(0x02B3)
      if ((osTcbSetEventMask[taskIndex] & osTcbWaitEventMask[taskIndex]) != 0)
      {
         COVER(0x02B4)

         OS_VTH_CALL_SETEVENT_HOOK(((TaskType) taskIndex)   ,
                                   ((EventMaskType) setMask),
                                   ((osbool) osdTRUE)       )

         /*  satisfied, change from waiting to ready */
         osTcbTaskState[taskIndex] = READY;
         
         osSchedInsertTask(taskIndex);

      }/*if ((EventsRequireStateChange == osdTRUE) && (StateChangeAllowed == osdTRUE))*/
      else
      {
         COVER(0x02B5)
         /* no change of task state as the task was not waiting for this event or timing protection prevented the state change */
         OS_VTH_CALL_SETEVENT_HOOK(((TaskType) taskIndex)   ,
                                   ((EventMaskType) setMask),
                                   ((osbool) osdFALSE)       )
      }
   }/* if (osTcbTaskState[taskIndex] == WAITING) */
   else
   {
      COVER(0x02B6)
      /* no change of task state as the task was not waiting at all */
      OS_VTH_CALL_SETEVENT_HOOK(((TaskType) taskIndex)   ,
                                ((EventMaskType) setMask),
                                ((osbool) osdFALSE)       )
   }


   OS_SE_EXIT()
   return E_OK; /* TR:SPMF82:0002 */

/* KB end sysSetEventBody */
} /* END OF osSysSetEvent */
#endif


#ifndef osdClearEventNotUsed
/*-+--------------------------------------------------------------------------
 / ClearEvent
 / =========
 /
 / Syntax:          StatusType ClearEvent ( EventMaskType <Mask> )
 / Parameter (In):  Mask Mask of the events to be cleared
 / Parameter (Out): none
 / Description:     The events of the extended task calling ClearEvent are 
 /                  cleared according to the event mask <Mask>.
 / Particularities: The system service ClearEvent is restricted to extended 
 /                  tasks which own the event.
 / Status:
 /  -Standard:      - No error, E_OK
 /  -Extended:      - Call not from extended task, E_OS_ACCESS
 /                  - Call at interrupt level, E_OS_CALLEVEL
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     ECC1, ECC2
 / Context:         Extended task, interrupts enabled
 /--------------------------------------------------------------------------*/

/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/ClearEvent
 */

// change:
// lowest bit of setMask is used as flag;
// other bits used as counter to prevent missing event.
osqFunc1 StatusType osqFunc2 osClearEvent (EventMaskType Mask)
{
   /* CovComment 4:  Function: osClearEvent */
   OS_CE_ENTRY()
   COVER(0x02B7)

#if STATUS_LEVEL == EXTENDED_STATUS
   COVER(0x02B8)

   if (osOwnCcb->LockIsNotNeeded.ossIntNestingDepth != 0)
   {
      COVER(0x02B9)
      #if osdErrorHook 
      COVER(0x02BA)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveClearEvent_Mask(Mask)
      #endif
      osAPIError(E_OS_CALLEVEL, osdErrCEOnInterruptLevel);
      #if osdErrorHook 
      COVER(0x02BB)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_CE_EXIT()
      return E_OS_CALLEVEL;
   }
   ELSEWITHCOVER(0x02BC)

   if (osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex >= osrNumberOfExtendedTasks)
   {
      COVER(0x02BD)
      #if osdErrorHook 
      COVER(0x02BE)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveClearEvent_Mask(Mask)
      #endif
      osAPIError(E_OS_ACCESS, osdErrCENotExtendedTask);
      #if osdErrorHook 
      COVER(0x02BF)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_CE_EXIT()
      return E_OS_ACCESS;
   }
   ELSEWITHCOVER(0x02C0)

   if (osOwnCcb->LockIsNotNeeded.ossIntAPIStatus != 0)
   {
      COVER(0x02C1)
      #if osdErrorHook 
      COVER(0x02C2)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveClearEvent_Mask(Mask)
      #endif
      osAPIError(E_OS_DISABLEDINT, osdErrCEIntAPIDisabled);
      #if osdErrorHook 
      COVER(0x02C3)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_CE_EXIT()
      return E_OS_DISABLEDINT;
   }
   ELSEWITHCOVER(0x02C4)
#endif

   /* KB begin osekHWosSaveDisableLevel (overwritten) */
   osSaveDisableLevel() /* save level and disable up to system level, no nesting */
   /* KB end osekHWosSaveDisableLevel */ /* disable interrupts as next command is not atomic */
   OS_CE_START_CRITICAL()
   
   /*to prevent missing event
   if(TskEvtCnt[osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex]>0)
   {
	TskEvtCnt[osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex]--;
   }

   if(0==TskEvtCnt[osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex])	  
   {
   	osTcbSetEventMask[osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex]&=(EventMaskType)(~Mask);
   }
   */
#ifdef QUEUED_EVENT
   if(osTcbSetEventMask[osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex] & 0xfffe)
   {
	osTcbSetEventMask[osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex] -=2;
   }  
   ///TODO: RE-CONSISDER EVENT  
   else if(osTcbSetEventMask[osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex] == MICROSAR_EVENT)
   {
   }
#endif   	
   {
   	osTcbSetEventMask[osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex]&=(EventMaskType)(~Mask);
   }
   OS_CE_END_CRITICAL()
   /* KB begin osekHWosRestoreEnableLevel (overwritten) */
   osRestoreEnableLevel() /* restore level saved by osSaveDisableLevel */
   /* KB end osekHWosRestoreEnableLevel */

   COVER(0x02C5)
   OS_CE_EXIT()
   return E_OK;
} /* END OF osClearEvent */
#endif


#ifndef osdGetEventNotUsed
/*-+--------------------------------------------------------------------------
 / GetEvent
 / ========
 /
 / Syntax:          StatusType GetEvent ( TaskType <TaskID>, 
 /                                        EventMaskRefType <Event> )
 / Parameter (In):  TaskID Task whose event mask is to be returned.
 / Parameter (Out): Event Reference to the memory of the return data.
 / Description:     This service returns the current state of all event bits 
 /                  of the task <TaskID>, not the events that the task is 
 /                  waiting for.
 /                  The service might be called from interrupt service 
 /                  routines, task level and some hook routines.
 /                  The current status of the event mask of task <TaskID> is
 /                  copied to <Event>.
 / Particularities: The referenced task must be an extended task.
 / Status:
 /  -Standard:      - No error, E_OK
 /  -Extended:      - Task <TaskID> is invalid, E_OS_ID
 /                  - Referenced task <TaskID> is not an extended task, 
 /                    E_OS_ACCESS
 /                  - Referenced task <TaskID> is in the suspended state, 
 /                    E_OS_STATE
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     ECC1, ECC2
 / Context:         Task, Cat2-ISR, ErrorHook, PreTaskHook, PostTaskHook,
 /                  interrupts not disabled by the application
 /--------------------------------------------------------------------------*/

/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/GetEvent
 */
osqFunc1 StatusType osqFunc2 osGetEvent(TaskType taskIndex, EventMaskRefType Event)
{
   /* CovComment 4:  Function: osGetEvent */

   OS_GE_ENTRY()
   COVER(0x02C6)

#if STATUS_LEVEL == EXTENDED_STATUS
   COVER(0x02C7)

   if (taskIndex >= osrNumberOfAllTasks)
   {
      COVER(0x02C8)
      #if osdErrorHook 
      COVER(0x02C9)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveGetEvent_TaskID(taskIndex)
      osSaveGetEvent_Event(Event)
      #endif
      osAPIError(E_OS_ID, osdErrGEWrongTaskID);
      #if osdErrorHook 
      COVER(0x02CA)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_GE_EXIT()
      return E_OS_ID;
   }
   ELSEWITHCOVER(0x02CB)

#if osdNumberOfExtendedTasks != osdNumberOfAllTasks
   COVER(0x02CC)
   if (taskIndex >= osrNumberOfExtendedTasks)
   {
      COVER(0x02CD)
      #if osdErrorHook 
      COVER(0x02CE)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveGetEvent_TaskID(taskIndex)
      osSaveGetEvent_Event(Event)
      #endif
      osAPIError(E_OS_ACCESS, osdErrGENotExtendedTask);
      #if osdErrorHook 
      COVER(0x02CF)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_GE_EXIT()
      return E_OS_ACCESS;
   }
   ELSEWITHCOVER(0x02D0)
#endif

   if (osTcbTaskState[taskIndex] == SUSPENDED)
   {
      COVER(0x02D1)
      #if osdErrorHook 
      COVER(0x02D2)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveGetEvent_TaskID(taskIndex)
      osSaveGetEvent_Event(Event)
      #endif
      osAPIError(E_OS_STATE, osdErrGETaskSuspended);
      #if osdErrorHook 
      COVER(0x02D3)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_GE_EXIT()
      return E_OS_STATE;
   }
   ELSEWITHCOVER(0x02D4)

   if (osOwnCcb->LockIsNotNeeded.ossIntAPIStatus != 0)
   {
      COVER(0x02D5)
      #if osdErrorHook 
      COVER(0x02D6)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveGetEvent_TaskID(taskIndex)
      osSaveGetEvent_Event(Event)
      #endif
      osAPIError(E_OS_DISABLEDINT, osdErrGEIntAPIDisabled);
      #if osdErrorHook 
      COVER(0x02D7)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_GE_EXIT()
      return E_OS_DISABLEDINT;
   }
   ELSEWITHCOVER(0x02D8)
#endif


   COVER(0x02D9)
/* KB begin osekHWGetEventMaskAccess (overwritten) */
*Event= osTcbSetEventMask[taskIndex];
/* KB end osekHWGetEventMaskAccess */

   COVER(0x02DA)
   OS_GE_EXIT()
   return E_OK;
   
} /* END OF osGetEvent */
#endif


#ifndef osdWaitEventNotUsed
/*-+--------------------------------------------------------------------------
 / WaitEvent
 / =========
 /
 / Syntax:          StatusType WaitEvent ( EventMaskType <Mask> )
 / Parameter (In):  Mask Mask of the events waited for.
 / Parameter (Out): none
 / Description:     The state of the calling task is set to waiting, unless 
 /                  at least one of the events specified in <Mask> has 
 /                  already been set.
 / Particularities: This call enforces rescheduling, if the wait condition 
 /                  occurs. If rescheduling takes place, the internal 
 /                  resource of the task is released while the task is in 
 /                  the waiting state.
 /                  This service must only be called from the extended task 
 /                  owning the event.
 / Status:
 /  -Standard:      - No error, E_OK
 /  -Extended:      - Calling task is not an extended task, E_OS_ACCESS
 /                  - Calling task occupies resources, E_OS_RESOURCE
 /                  - Call at interrupt level, E_OS_CALLEVEL
 /                  - Call with disabled interrupts, E_OS_DISABLEDINT
 / Conformance:     ECC1, ECC2
 / Context:         Extended task, interrupts enabled, no resources occupied
 /--------------------------------------------------------------------------*/

/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/WaitEvent
 */
osqFunc1 StatusType osqFunc2 osWaitEvent(EventMaskType mask)
{
   /* CovComment 4:  Function: osWaitEvent */
   TaskType taskIndex = osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex;
   
   OS_WE_ENTRY()
   COVER(0x02DB)

#if STATUS_LEVEL == EXTENDED_STATUS
   COVER(0x02DC)

   if (osOwnCcb->LockIsNotNeeded.ossIntNestingDepth != 0)
   {
      COVER(0x02DD)
      COVER(0x02DE)
      #if osdErrorHook 
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveWaitEvent_Mask(mask)
      #endif
      osAPIError(E_OS_CALLEVEL, osdErrWEOnInterruptLevel);
      #if osdErrorHook 
      COVER(0x02DF)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_WE_EXIT()
      return E_OS_CALLEVEL;
   }
   ELSEWITHCOVER(0x02E0)

   if (taskIndex >= osrNumberOfExtendedTasks)
   {
      COVER(0x02E1)
      #if osdErrorHook 
      COVER(0x02E2)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveWaitEvent_Mask(mask)
      #endif
      osAPIError(E_OS_ACCESS, osdErrWENotExtendedTask);
      #if osdErrorHook 
      COVER(0x02E3)
      /* KB begin osekHWosRestoreEnableLevelNested (obe
      verwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_WE_EXIT()
      return E_OS_ACCESS;
   }
   ELSEWITHCOVER(0x02E4)
   

#if (osdNumberOfInternalResources == 0) && (osdNumberOfInterruptResources == 0)
   COVER(0x02E5)
   /* check for task resources only system */
   if (osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio != oskTcbHomePrio[taskIndex])
#else
   COVER(0x02E6)
   /* check for mixed resource system (task, interrupt and internal) */
   if (osTcbResourceCounter[taskIndex] != 0)
#endif
   {
      COVER(0x02E7)
      #if osdErrorHook 
      COVER(0x02E8)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveWaitEvent_Mask(mask)
      #endif
      osAPIError(E_OS_RESOURCE, osdErrWEResourcesOccupied);
      #if osdErrorHook 
      COVER(0x02E9)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_WE_EXIT()
      return E_OS_RESOURCE;
   }
   ELSEWITHCOVER(0x02EA)

   if (osCheckInterruptsEnabled() == 0)
   {
      COVER(0x02EB)
      #if osdErrorHook 
      COVER(0x02EC)
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveWaitEvent_Mask(mask)
      #endif
      osAPIError(E_OS_DISABLEDINT, osdErrWEInterruptsDisabled);
      #if osdErrorHook 
      COVER(0x02ED)
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_WE_EXIT()
      return E_OS_DISABLEDINT;
   }
   ELSEWITHCOVER(0x02EE)
#endif

   COVER(0x02EF)
   /* KB begin osekHWosDisableLevel (overwritten) */
   osDisableLevel(); /* disable interrupts up to system level */
   /* KB end osekHWosDisableLevel */ /* (WaitEvent is only called from task level) */
   OS_WE_START_CRITICAL()
   /* KB begin osekHWosDisableTimProtInterrupt (overwritten) */
   /* KB end osekHWosDisableTimProtInterrupt */

   osTcbWaitEventMask[taskIndex]= mask;

   if ((osTcbSetEventMask[taskIndex] & mask) == 0)
   {
      COVER(0x02F0)
      /* no expected event set, set task into waiting state */

      /* call hook routine for the waiting task */
#if osdPostTaskHook
      COVER(0x02F1)
      osPostTaskHook();
#endif


      COVER(0x02F2)
      /* change task state from ready to waiting */
      osTcbTaskState[taskIndex] = WAITING;

      osSchedRemoveRunningTask();

      /* for WaitEvent, osSchedRemoveRunningTask() always sets
       * ossStartDispatcher to osdTRUE
       * (same task is never running when reaching this point of code) */
      /* KB begin osekHWosEnableTimProtInterrupt (overwritten) */
      /* KB end osekHWosEnableTimProtInterrupt */
      OS_WE_END_CRITICAL()
      OS_WE_EXIT()
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
   
   /* KB begin osekHWosEnableTimProtInterrupt (overwritten) */
   /* KB end osekHWosEnableTimProtInterrupt */
   OS_WE_END_CRITICAL()
   OS_WE_EXIT()
   /* KB begin osekHWosEnableLevel (overwritten) */
   osEnableLevel(); /* enable task level interrupt */
   /* KB end osekHWosEnableLevel */

   return E_OK;
} /* END OF osWaitEvent */
#endif

#else 
/* KB begin osekHWosOsekEvntDummy (default) */
/* KB end osekHWosOsekEvntDummy */
#endif /* End of ((CC == ECC1) || (CC == ECC2)) && (osdNumberOfExtendedTasks > 0) */
/* KB begin osekEndOfCModule (overwritten) */
#pragma ghs section bss=default
#pragma ghs section data=default
#pragma ghs section sbss=default
#pragma ghs section sdata=default
#pragma ghs section text=default
#pragma ghs section rodata=default
#pragma ghs section rosdata=default
/* KB end osekEndOfCModule */

/* END OF MODULE osekevnt.c */


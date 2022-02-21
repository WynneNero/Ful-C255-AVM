/* Kernbauer Version: 2.16 Konfiguration: RH850 Erzeugungsgangnummer: 214 Zweig: 1 */

/*****************************************************************************
| Project Name: MICROSAR OS
|    File Name: osekSched.c
|
|  General code: @Version: 9.01.04@
|  Module version: $vv$=1.04
|
|  Description: OSEK Scheduler
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2000-2015 Vector Informatik GmbH          All rights reserved.
|****************************************************************************/


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

/* CovComment 0:  file: osekSched.c */

/* KB begin osekStartOfCModule (overwritten) */
#pragma ghs section bss=".os_bss"
#pragma ghs section data=".os_data"
#pragma ghs section sbss=".os_sbss"
#pragma ghs section sdata=".os_sdata"
#pragma ghs section text=".os_text"
#pragma ghs section rodata=".os_rodata"
#pragma ghs section rosdata=".os_rosdata"
/* KB end osekStartOfCModule */

/* KB begin osekHWosGetHighPrioBit (overwritten) */
/* osGetHighPrioBit is provided via assembler macro in osekasm.h */
/* KB end osekHWosGetHighPrioBit */

#if (osdNumberOfAllTasks > 0)
/*-+--------------------------------------------------------------------------
 / osSchedInsertTask
 / Function:
 /   - inserts the task into its home priority queue
 /   - sets the corresponding ready mask bit to TRUE
 /   - if the new task has a higher priority than the current HighReadyTask,
 /     - HighReadyTask and HighReadyPrio are set to the new task
 /     - StartDispatcher is set to TRUE.
 /
 /   Note: This function must be called with interrupts disabled and the new
 /         task's core's lock occupied!
 /
 / Parameter:     taskID : task to be inserted
 / Return value:  void
 /--------------------------------------------------------------------------*/

osqFunc1 void osqFunc2 osSchedInsertTask(TaskType taskIndex)
{
   /* CovComment 4:  Function: osSchedInsertTask */

   /* get priority of task to insert */
   osPrioType taskPriority = oskTcbHomePrio[taskIndex];

   /* validate the priority */
   osSysErrAssert(taskPriority < osrNumberOfPriorities, osdErrQIWrongTaskPrio)

#if ((CC == ECC2) || (CC == BCC2))
   COVER(0x017A)
   /* Add task to the ready queue */
   oskQActivationQueues[taskPriority][ptrToCcb->ossQReadyTaskTail[taskPriority]] = taskIndex;
   /* increment tail and handle overflow */
   ptrToCcb->ossQReadyTaskTail[taskPriority]++;
   if (ptrToCcb->ossQReadyTaskTail[taskPriority] > oskQMaxActivations[taskPriority])
   {
      COVER(0x017B)
      ptrToCcb->ossQReadyTaskTail[taskPriority] = 0;
   }
   ELSEWITHCOVER(0x017C)
#else
   COVER(0x017D)
   /* this task is ready on this taskPriority */
   ptrToCcb->ossQReadyTask[taskPriority] = taskIndex;
#endif

   /* at least one task is now ready on this priority */
#if (osdRTSize > 1)
   COVER(0x017E)
   ptrToCcb->ossQReadyPrios[oskTcbReadyPrioOffset[taskIndex]] |= oskTcbReadyPrioMask[taskIndex];
#else
   COVER(0x017F)
   ptrToCcb->ossQReadyPrios |= oskTcbReadyPrioMask[taskIndex];
#endif

   /* start dispatcher only if new task has greater prio */
   if (taskPriority < ptrToCcb->ossHighReadyTaskPrio)
   {
      COVER(0x0180)
      ptrToCcb->ossHighReadyTaskPrio  = taskPriority;
      ptrToCcb->ossHighReadyTaskIndex = taskIndex;
      ptrToCcb->ossStartDispatcher    = osdTRUE;
   }
}
#endif /* (osdNumberOfAllTasks > 0) */

#if (osdNumberOfAllTasks > 0)
/*-+--------------------------------------------------------------------------
 / osSchedRemoveRunningTask
 / Function:
 /   - removes the currently running task from the ready queue
 /   - if the queue is empty afterwards, the corresponding ready mask bit is
 /     cleared
 /   - a new HighReadyTask and HighReadyPrio are calculated
 /   - StartDispatcher is set to TRUE (the previously active task was preempted or
 /     terminated, so we need the dispatcher to continue in any case)
 /
 /   Note: This function must be called with interrupts disabled and local
 /         core's lock occupied! No cross-core support! Tasks can only deactivate
 /         themselves, so this function will be executed on the tasks's core
 /         exclusively.
 /
 / Parameter:     void
 / Return value:  void
 /--------------------------------------------------------------------------*/
 /* MISRA RULE 14.1 VIOLATION: osSchedRemoveRunningTask is a function which might be unused. In order to keep the code 
  * simple and error free, it is available in more configurations than necessary.*/
osqFunc1 void osqFunc2 osSchedRemoveRunningTask(void) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osSchedRemoveRunningTask */

   osPrioType hiPriorTask;
#if osdRTSize > 1
   osqPRAM1 volatile osqPRAM2 osPrioFlagType osqPRAM3 *ptr;
   osPrioFlagType uiTestPattern;
#endif
   TaskType activeTaskID;
   osPrioType activeTaskPrio;
   
   activeTaskID = osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex;
   activeTaskPrio = osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio;


#if (STATUS_LEVEL == EXTENDED_STATUS)
   COVER(0x0181)
   osSysErrAssert((osCheckInterruptsDisabled() != 0), osdErrQRInterruptsEnabled) /* TR:SPMF12:0007 */
#endif

#if osdNumberOfInternalResources > 0
   COVER(0x0182)
   /* release internal resource, if one is occupied by the task */
   if (oskResInternalCeilingPrioMask[activeTaskID] != 0)
   {
#if osdRTSize == 1
      COVER(0x0183)
      ptrToCcb->ossQReadyPrios &= ~oskResInternalCeilingPrioMask[activeTaskID];
#else
      COVER(0x0184)
      ptrToCcb->ossQReadyPrios[oskResInternalCeilingPrioOffset[activeTaskID]] &=
         ~oskResInternalCeilingPrioMask[activeTaskID];
#endif
#if ((CC == ECC2) || (CC == BCC2))
      /* delete task out of the prio queue */
      ptrToCcb->ossQReadyTaskHead[activeTaskPrio]++;
      if (ptrToCcb->ossQReadyTaskHead[activeTaskPrio] > oskQMaxActivations[activeTaskPrio])
      {
         COVER(0x0185)
         ptrToCcb->ossQReadyTaskHead[activeTaskPrio]= 0;
      }
      ELSEWITHCOVER(0x0186)
#else
      /* delete task from the prio */
      ptrToCcb->ossQReadyTask[activeTaskPrio] = osdNoActiveTask;
#endif
      COVER(0x0187)
      activeTaskPrio = osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio = oskTcbHomePrio[activeTaskID];

#if osdORTIDebug
      COVER(0x0188)
      osTcbActualPrio[activeTaskID] = oskTcbHomePrio[activeTaskID];
#endif
   }
   ELSEWITHCOVER(0x0189)
#endif /* osdNumberOfInternalResources > 0 */

#if ((CC == ECC2) || (CC == BCC2))
   /* delete task out of the prio queue */
   ptrToCcb->ossQReadyTaskHead[activeTaskPrio]++;
   if (ptrToCcb->ossQReadyTaskHead[activeTaskPrio] > oskQMaxActivations[activeTaskPrio])
   {
      COVER(0x018A)
      ptrToCcb->ossQReadyTaskHead[activeTaskPrio]= 0;
   }
   ELSEWITHCOVER(0x018B)

   if (ptrToCcb->ossQReadyTaskHead[activeTaskPrio] == ptrToCcb->ossQReadyTaskTail[activeTaskPrio])
   {  /* queue empty */
      COVER(0x018C)
#else
   /* delete task from the prio */
   ptrToCcb->ossQReadyTask[activeTaskPrio] = osdNoActiveTask;
#endif

#if (osdRTSize > 1)
      COVER(0x018D)
      ptrToCcb->ossQReadyPrios[oskTcbReadyPrioOffset[activeTaskID]]&= ~oskTcbReadyPrioMask[activeTaskID];
#else
      COVER(0x018E)
      ptrToCcb->ossQReadyPrios&= ~oskTcbReadyPrioMask[activeTaskID];
#endif

#if ((CC == ECC2) || (CC == BCC2))
   }
   ELSEWITHCOVER(0x018F)
#endif

   /* calculate ready task with highest priority */
   COVER(0x0190)
#if osdRTSize > 1
   COVER(0x0191)
   ptr = ptrToCcb->ossQReadyPrios;
   uiTestPattern = *ptr;
   hiPriorTask = 0;
   IFCOVER(!uiTestPattern,0x01F1,0x01F2)
   while (!uiTestPattern)
   {
      ptr++;
      if (ptr > &ptrToCcb->ossQReadyPrios[osrRTSize-1])
      {  /* prepare for IDLE-Loop */
         COVER(0x0192)
         ptrToCcb->ossHighReadyTaskPrio  = osdNoActivePrio;
         ptrToCcb->ossHighReadyTaskIndex = osdNoActiveTask;
         ptrToCcb->ossStartDispatcher    = osdTRUE;
         return;
      }
      ELSEWITHCOVER(0x0193)
      uiTestPattern = *ptr;
      hiPriorTask += osdPrioBitsPerWord;
      IFCOVER(!uiTestPattern,0x01F3,0x01F4)
   }
   COVER(0x0194)
   hiPriorTask += osGetHighPrioBit(uiTestPattern);
#else
   if (ptrToCcb->ossQReadyPrios == 0)
   {  /* prepare for IDLE-Loop */
      COVER(0x0195)
      ptrToCcb->ossHighReadyTaskPrio  = osdNoActivePrio;
      ptrToCcb->ossHighReadyTaskIndex = osdNoActiveTask;
      ptrToCcb->ossStartDispatcher    = osdTRUE;
      return;
   }
   ELSEWITHCOVER(0x0196)
   hiPriorTask = osGetHighPrioBit(ptrToCcb->ossQReadyPrios);
#endif


#if ((CC == BCC2) || (CC == ECC2))
   COVER(0x0197)
   ptrToCcb->ossHighReadyTaskIndex = oskQActivationQueues[hiPriorTask][ptrToCcb->ossQReadyTaskHead[hiPriorTask]];
#else
   COVER(0x0198)
   ptrToCcb->ossHighReadyTaskIndex = ptrToCcb->ossQReadyTask[hiPriorTask];
#endif

   ptrToCcb->ossHighReadyTaskPrio  = hiPriorTask;

   /* we have just removed the running task from the ready queue, so we need a dispatcher call in any case. */
   ptrToCcb->ossStartDispatcher    = osdTRUE;
   return;
}
#endif /* (osdNumberOfAllTasks > 0) */


#if (((osdSC== SC3) || (osdSC== SC4)) && (osdProtReactKillApplAllowed || osdProtReactKillApplRestAllowed || !defined osdTerminateApplicationNotUsed))
#if (osdNumberOfApplications > 0)
#if (osdNumberOfAllTasks > 0)
/*-+--------------------------------------------------------------------------
 / osSchedKillApplication
 / Function:
 /   - searches for tasks belonging to applId in each ReadyQueue, and removes them
 /   - tasks of other applications remain untouched
 /   - if there is no task left on the priority, the corresponding ready mask bit
 /     is cleared
 /   - the highest priority with a remaining ready task is calculated
 /   - if the first element to remain in the highest priority ready queue differs
 /     from the previous HighReadyTask,
 /     - HighReadyTask and HighReadyPrio are set to that task
 /     - StartDispatcher is set to TRUE.
 /
 /   Note: This function must be called with interrupts disabled and local
 /         core's lock occupied! No cross-core support! Cross-core killing
 /         requires remote procedure call, so this function will be
 /         executed on the application's core exclusively.
 /
 / Parameter:     applId : application to be killed
 / Return value:  void
 /--------------------------------------------------------------------------*/

osqFunc1 void osqFunc2 osSchedKillApplication(ApplicationType applId)
{
   /* CovComment 4:  Function: osSchedKillApplication */

   osPrioType currentPriority;
   osPrioType highReadyTaskPrio = osdNoActivePrio;
#if (CC==BCC2) || (CC==ECC2)
   osQEntryCountType Head, oldTail, newTail;
#endif
   
   /* start at the lowest priority - this allows us to keep track of the highReadyTaskPrio */
   currentPriority = osrNumberOfPriorities;
   do {
      COVER(0x0199)
      currentPriority--;
#if (CC==BCC2) || (CC==ECC2)
      COVER(0x019A)
      /* calculating on local copies improves speed */
      Head = ptrToCcb->ossQReadyTaskHead[currentPriority];
      oldTail = ptrToCcb->ossQReadyTaskTail[currentPriority];
      if(Head != oldTail)
      {
         COVER(0x019B)
         newTail = oldTail;
         /* we've done the first comparison already, so do..while is sufficient... */
         do {
            if(osConfigBlock.acTaskToAppl[oskQActivationQueues[currentPriority][Head]] != applId)
            {
               COVER(0x019C)
               /* take a copy of preservable entries from the front to the end of the queue */
               oskQActivationQueues[currentPriority][newTail] = oskQActivationQueues[currentPriority][Head];
               newTail++; /* we've entered something, so go one further for the next one */
               if (newTail > oskQMaxActivations[currentPriority])
               {
                  COVER(0x019D)
                  newTail = 0;
               }
               ELSEWITHCOVER(0x019E)
            }
            ELSEWITHCOVER(0x019F)
            Head++; /* item done, now look at the next one */
            if (Head > oskQMaxActivations[currentPriority])
            {
               COVER(0x01A0)
               Head = 0;
            }
            ELSEWITHCOVER(0x01A1)
            IFCOVER(Head != oldTail,0x01F5,0x01F6)
         } while(Head != oldTail); /* run through the old queue */
         ptrToCcb->ossQReadyTaskHead[currentPriority] = Head;    /* we've calculated a new Head, copy it to the global variable */
         ptrToCcb->ossQReadyTaskTail[currentPriority] = newTail; /* the old Tail, we've kept for the break condition only, store only the newly calculated one */
         if(Head == newTail)
         {
            /* Queue is empty, clear the priority */
#if (osdRTSize > 1)
            osPrioOffsetType idx = (osPrioOffsetType)(currentPriority / osdPrioBitsPerWord); /* currentPriority =  0..31: idx = 0
                                                                                32..63: idx = 1
                                                                                ......... */
            osPrioFlagType mask = (osPrioFlagType)(((osPrioFlagType)1U)<<(currentPriority - (idx * osdPrioBitsPerWord)));
            COVER(0x01A2)
            ptrToCcb->ossQReadyPrios[idx] &= ~mask;
#else /* osdRTSize > 1 */
            COVER(0x01A3)
            ptrToCcb->ossQReadyPrios &= ~((osPrioFlagType)(((osPrioFlagType)1U)<<currentPriority));
#endif /* else osdRTSize > 1 */
         }
         else
         {
            COVER(0x01A4)
            /* There is still a task alive on this priority, so store the prio as (potential) highReadyTaskPrio */
            highReadyTaskPrio = currentPriority;
         }
      }
      ELSEWITHCOVER(0x01A5)
#else /* (CC==BCC2) || (CC==ECC2) */
      COVER(0x01A6)
      if(ptrToCcb->ossQReadyTask[currentPriority] != osdNoActiveTask)
      {
         COVER(0x01A7)
         /* found a valid task on this priority: check if it needs to be killed */
         if(osConfigBlock.acTaskToAppl[ptrToCcb->ossQReadyTask[currentPriority]] == applId)
         {
            /* yes, kill it */
#if (osdRTSize > 1)
            osPrioOffsetType idx = (osPrioOffsetType)(currentPriority / osdPrioBitsPerWord); /* currentPriority =  0..31: idx = 0
                                                                                32..63: idx = 1
                                                                                ......... */
            osPrioFlagType mask = (osPrioFlagType)(((osPrioFlagType)1U)<<(currentPriority - (idx * osdPrioBitsPerWord)));
            COVER(0x01A8)
            ptrToCcb->ossQReadyPrios[idx] &= ~mask;
#else /* osdRTSize > 1 */
            COVER(0x01A9)
            ptrToCcb->ossQReadyPrios &= ~((osPrioFlagType)(((osPrioFlagType)1U)<<currentPriority));
#endif /* else osdRTSize > 1 */
            ptrToCcb->ossQReadyTask[currentPriority] = osdNoActiveTask;
         }
         else
         {
            COVER(0x01AA)
            /* There is still a task alive on this priority, so store the prio as (potential) highReadyTaskPrio */
            highReadyTaskPrio = currentPriority;
         }
      }
      ELSEWITHCOVER(0x01AB)
#endif /* else (CC==BCC2) || (CC==ECC2) */
      IFCOVER(currentPriority != 0,0x01F7,0x01F8)
   } while(currentPriority != 0);
   ptrToCcb->ossHighReadyTaskPrio  = highReadyTaskPrio;
   if(osdNoActivePrio == highReadyTaskPrio)
   {
      COVER(0x01AC)
      /* Prepare for Idle Loop */
      ptrToCcb->ossHighReadyTaskIndex = osdNoActiveTask;
      ptrToCcb->ossStartDispatcher    = osdTRUE;
   }
   else
   {
      /* start dispatcher only if new task differs from the old one */
#if ((CC == BCC2) || (CC == ECC2))
      COVER(0x01AD)
      if (ptrToCcb->ossHighReadyTaskIndex != oskQActivationQueues[highReadyTaskPrio][ptrToCcb->ossQReadyTaskHead[highReadyTaskPrio]])
      {
         COVER(0x01AE)
         ptrToCcb->ossHighReadyTaskIndex = oskQActivationQueues[highReadyTaskPrio][ptrToCcb->ossQReadyTaskHead[highReadyTaskPrio]];
         ptrToCcb->ossStartDispatcher    = osdTRUE;
      }
      ELSEWITHCOVER(0x01AF)
#else /* (CC==BCC2) || (CC==ECC2) */
      COVER(0x01B0)
      if (ptrToCcb->ossHighReadyTaskIndex != ptrToCcb->ossQReadyTask[highReadyTaskPrio])
      {
         COVER(0x01B1)
         ptrToCcb->ossHighReadyTaskIndex = ptrToCcb->ossQReadyTask[highReadyTaskPrio];
         ptrToCcb->ossStartDispatcher    = osdTRUE;
      }
      ELSEWITHCOVER(0x01B2)
#endif /* else (CC==BCC2) || (CC==ECC2) */
   }
}
#endif /* (osdNumberOfAllTasks > 0) */
#endif /* (osdNumberOfApplications > 0) */
#endif /* (((osdSC== SC3) || (osdSC== SC4)) && (osdProtReactKillApplAllowed || osdProtReactKillApplRestAllowed || !defined osdTerminateApplicationNotUsed)) */


#if (osdNumberOfTaskResources > 0)
#if (!defined(osdGetResourceNotUsed))
/*-+--------------------------------------------------------------------------
 / osSchedGetResource
 / Function:
 /   - occupies the given resource's ceiling priority with the active task
 /   - active task prio and high ready task prio and index are adapted if
 /     adequate.
 /
 /   Note: This function must be called with interrupts disabled and local
 /         core's lock occupied! No cross-core support!
 /
 / Parameter:     ResId : resource to be occupied
 / Return value:  void
 /--------------------------------------------------------------------------*/

osqFunc1 void osqFunc2 osSchedGetResource(ResourceType ResId)
{
   /* CovComment 4:  Function: osSchedGetResource */


   /* validate that the resource's priority is free */
 #if osdRTSize == 1
   COVER(0x01B3)
   osSysErrAssert(((ptrToCcb->ossQReadyPrios & oskResCeilingPrioMask[ResId]) == 0U), osdErrGRPriorityOccupied)
 #else /* osdRTSize == 0 */
   COVER(0x01B4)
   osSysErrAssert(((ptrToCcb->ossQReadyPrios[oskResCeilingPrioOffset[ResId]] & 
                    oskResCeilingPrioMask[ResId]) == 0U), osdErrGRPriorityOccupied)  /* NOCOV */
 #endif /* osdRTSize == 1 */

 #if (CC==BCC2) || (CC==ECC2)
   COVER(0x01B5)
   /* Add task to the ready queue */
   oskQActivationQueues[oskResCeilingPrio[ResId]][ptrToCcb->ossQReadyTaskTail[oskResCeilingPrio[ResId]]] = osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex;
   /* increment tail and handle overflow */
   ptrToCcb->ossQReadyTaskTail[oskResCeilingPrio[ResId]]++;
   if (ptrToCcb->ossQReadyTaskTail[oskResCeilingPrio[ResId]] > oskQMaxActivations[oskResCeilingPrio[ResId]])
   {
      COVER(0x01B6)
      ptrToCcb->ossQReadyTaskTail[oskResCeilingPrio[ResId]] = 0;
   }
   ELSEWITHCOVER(0x01B7)
 #else /* BCC1 || ECC1 */
   COVER(0x01B8)
   /* this task is ready on this priority */
   ptrToCcb->ossQReadyTask[oskResCeilingPrio[ResId]] = osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex;
 #endif /* (CC==BCC2) || (CC==ECC2) */

   /* set the ready bitmask */
 #if osdRTSize == 1
   COVER(0x01B9)
   ptrToCcb->ossQReadyPrios |= oskResCeilingPrioMask[ResId];
 #else /* osdRTSize == 0 */
   COVER(0x01BA)
   ptrToCcb->ossQReadyPrios[oskResCeilingPrioOffset[ResId]] |= oskResCeilingPrioMask[ResId];
 #endif /* osdRTSize == 1 */

   /* increase current task's priority to the ceiling prio */
   if (oskResCeilingPrio[ResId] < osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio)
   {
      COVER(0x01BB)
      osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio = oskResCeilingPrio[ResId];
   }
   ELSEWITHCOVER(0x01BC)

   /* update high ready task prio and index */
   /* no need to trigger dispatcher: high ready task is already running */
   if (oskResCeilingPrio[ResId] < ptrToCcb->ossHighReadyTaskPrio)
   {
      COVER(0x01BD)
      ptrToCcb->ossHighReadyTaskPrio  = oskResCeilingPrio[ResId];
      ptrToCcb->ossHighReadyTaskIndex = osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex;
   }
   ELSEWITHCOVER(0x01BE)
   return;
}
#endif


#if (!defined(osdReleaseResourceNotUsed))
/*-+--------------------------------------------------------------------------
 / osSchedReleaseResource
 / Function:
 /   - releases the given resource's ceiling priority
 /   - recalculates high ready task index and prio, and requests dispatcher
 /     activation, if adequate.
 /
 /   Note: This function must be called with interrupts disabled and local
 /         core's lock occupied! No cross-core support!
 /
 / Parameter:     ResId : resource to be released
 / Return value:  void
 /--------------------------------------------------------------------------*/

osqFunc1 void osqFunc2 osSchedReleaseResource(ResourceType ResId)
{
   /* CovComment 4:  Function: osSchedReleaseResource */

   osPrioType hiPriorTask;
#if osdRTSize > 1
   osqPRAM1 volatile osqPRAM2 osPrioFlagType osqPRAM3 *ptr;
   osPrioFlagType uiTestPattern;
#endif

   /* next assertion checks if there is a bit set in the ready bits */
#if osdRTSize == 1
   COVER(0x01BF)
   osSysErrAssert(((ptrToCcb->ossQReadyPrios & oskResCeilingPrioMask[ResId]) != 0U), 
      osdErrRRCeilingPriorityNotSet) /* NOCOV */
#else
   COVER(0x01C0)
   osSysErrAssert(((ptrToCcb->ossQReadyPrios[oskResCeilingPrioOffset[ResId]] &
      oskResCeilingPrioMask[ResId]) != 0U), osdErrRRCeilingPriorityNotSet) /* NOCOV */
#endif

#if ((CC == ECC2) || (CC == BCC2))
   /* delete task out of the prio queue */
   ptrToCcb->ossQReadyTaskHead[oskResCeilingPrio[ResId]]++;
   if (ptrToCcb->ossQReadyTaskHead[oskResCeilingPrio[ResId]] > oskQMaxActivations[oskResCeilingPrio[ResId]])
   {
      COVER(0x01C1)
      ptrToCcb->ossQReadyTaskHead[oskResCeilingPrio[ResId]]= 0;
   }
   ELSEWITHCOVER(0x01C2)
#else
   /* delete task from the prio */
   ptrToCcb->ossQReadyTask[oskResCeilingPrio[ResId]] = osdNoActiveTask;
#endif

#if osdRTSize == 1
   COVER(0x01C3)
   ptrToCcb->ossQReadyPrios &= ~oskResCeilingPrioMask[ResId];
#else
   COVER(0x01C4)
   ptrToCcb->ossQReadyPrios[oskResCeilingPrioOffset[ResId]] &= ~oskResCeilingPrioMask[ResId];
#endif

   /* calculate ready task with highest priority */
   COVER(0x01C5)
#if osdRTSize > 1
   COVER(0x01C6)
   ptr = ptrToCcb->ossQReadyPrios;
   uiTestPattern = *ptr;
   hiPriorTask = 0;
   IFCOVER(!uiTestPattern,0x01F9,0x01FA)
   while (!uiTestPattern)
   {
      ptr++;
      /* at least the task releasing its resource must still be ready on its home prio. */
      osSysErrAssert((ptr <= &ptrToCcb->ossQReadyPrios[osrRTSize-1]), osdErrRRNoReadyTaskFound)
      uiTestPattern = *ptr;
      hiPriorTask += osdPrioBitsPerWord;
      IFCOVER(!uiTestPattern,0x01FB,0x01FC)
   }
   COVER(0x01C7)
   hiPriorTask += osGetHighPrioBit(uiTestPattern);
#else
   /* at least the task releasing its resource must still be ready on its home prio. */
   osSysErrAssert((ptrToCcb->ossQReadyPrios != 0), osdErrRRNoReadyTaskFound)
   hiPriorTask = osGetHighPrioBit(ptrToCcb->ossQReadyPrios);
#endif


#if ((CC == BCC2) || (CC == ECC2))
   COVER(0x01C8)
   ptrToCcb->ossHighReadyTaskIndex = oskQActivationQueues[hiPriorTask][ptrToCcb->ossQReadyTaskHead[hiPriorTask]];
#else
   COVER(0x01C9)
   ptrToCcb->ossHighReadyTaskIndex = ptrToCcb->ossQReadyTask[hiPriorTask];
#endif

   ptrToCcb->ossHighReadyTaskPrio  = hiPriorTask;

   /* KB begin osekHWosSchedulePrioReaction (default) */
      if (ptrToCcb->ossHighReadyTaskIndex != osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex)
      {
         COVER(0x01CA)
         ptrToCcb->ossStartDispatcher    = osdTRUE;
      }
      ELSEWITHCOVER(0x01CB)
   /* KB end osekHWosSchedulePrioReaction */
   return;
}
#endif
#endif


/*-+--------------------------------------------------------------------------
 / osSchedOccupyInternalResource
 / Function:
 /   - occupies the ceiling priority of the internal resource assigned to the
 /     active task
 /   - high ready task prio is adapted if adequate.
 /   - active task prio is set (even if no internal resource is assigned)
 /
 /   Note: This function must be called with interrupts disabled and local
 /         core's lock occupied! No cross-core support!
 /         osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex must be set to the task
 /         that is being dispatched before this function is called!
 /
 / Parameter:     void
 / Return value:  void
 /--------------------------------------------------------------------------*/
/* MISRA RULE 14.1 not violated: osSchedOccupyInternalResource is a function which is called from 
 *                               assembly language in some implementations. This is not recognized 
 *                               by the MISRA checker. 
 */
osqFunc1 void osqFunc2 osSchedOccupyInternalResource(void) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osSchedOccupyInternalResource */

#if ((osdNumberOfInternalResources > 0) || osdORTIDebug) && (osdNumberOfAllTasks > 0)
   TaskType activeTaskID;
   
   activeTaskID = osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex;

#endif /* ((osdNumberOfInternalResources > 0) || osdORTIDebug) && (osdNumberOfAllTasks > 0) */

#if (osdNumberOfInternalResources > 0)
   if (oskResInternalCeilingPrioMask[activeTaskID] != 0)
   {
      osPrioType IntResCeilingPrio = oskResInternalCeilingPrio[activeTaskID];
      COVER(0x01CC)

#if ((CC == ECC2) || (CC == BCC2))
      COVER(0x01CD)
      /* Only add task to the ready queue if not yet in there */
      if(ptrToCcb->ossQReadyTaskHead[IntResCeilingPrio] == ptrToCcb->ossQReadyTaskTail[IntResCeilingPrio])
      {
         oskQActivationQueues[IntResCeilingPrio][ptrToCcb->ossQReadyTaskTail[IntResCeilingPrio]] = activeTaskID;
         /* increment tail and handle overflow */
         ptrToCcb->ossQReadyTaskTail[IntResCeilingPrio]++;
         if (ptrToCcb->ossQReadyTaskTail[IntResCeilingPrio] > oskQMaxActivations[IntResCeilingPrio])
         {
            COVER(0x01CE)
            ptrToCcb->ossQReadyTaskTail[IntResCeilingPrio] = 0;
         }
         ELSEWITHCOVER(0x01CF)
      }
      ELSEWITHCOVER(0x01D0)
#else
      COVER(0x01D1)
      /* this task is ready on this priority */
      ptrToCcb->ossQReadyTask[IntResCeilingPrio] = activeTaskID;
#endif

      /* task is ready on this priority */
#if osdRTSize == 1
      COVER(0x01D2)
      ptrToCcb->ossQReadyPrios |= oskResInternalCeilingPrioMask[activeTaskID];
#else
      COVER(0x01D3)
      ptrToCcb->ossQReadyPrios[oskResInternalCeilingPrioOffset[activeTaskID]] |= /*;*/
         oskResInternalCeilingPrioMask[activeTaskID];
#endif

      /* correct ptrToCcb->ossHighReadyTaskPrio if required */
      if(IntResCeilingPrio < ptrToCcb->ossHighReadyTaskPrio)
      {
         COVER(0x01D4)
         ptrToCcb->ossHighReadyTaskPrio               = IntResCeilingPrio;
         osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio  = IntResCeilingPrio;
      }
      else
      {
         COVER(0x01D5)
         osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio  = ptrToCcb->ossHighReadyTaskPrio;
      }
   }
   else
   {
      COVER(0x01D6)
#endif /* (osdNumberOfInternalResources > 0) */
      COVER(0x01D7)
      osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio  = ptrToCcb->ossHighReadyTaskPrio;
#if (osdNumberOfInternalResources > 0)
   }
#endif /*(osdNumberOfInternalResources > 0)*/

#if ( (osdNumberOfAllTasks > 0) && osdORTIDebug)
   COVER(0x01D8)
   osTcbActualPrio[activeTaskID] = osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio;
#endif
}

#if ((osdNumberOfAllTasks > 0) && !defined(osdScheduleNotUsed))
/*-+--------------------------------------------------------------------------
 / osSchedOnHomePrio
 / Function:
 /   - releases the internal resource held by the running task (if applicable)
 /   - recalculates high ready task index and prio, and requests dispatcher
 /     activation, if adequate.
 /
 /   Note: This function must be called with interrupts disabled and local
 /         core's lock occupied! No cross-core support!
 /
 / Parameter:     void
 / Return value:  void
 /--------------------------------------------------------------------------*/

osqFunc1 void osqFunc2 osSchedOnHomePrio(void)
{
   /* CovComment 4:  Function: osSchedOnHomePrio */

   osPrioType hiPriorTask;
#if osdRTSize > 1
   osqPRAM1 volatile osqPRAM2 osPrioFlagType osqPRAM3 *ptr;
   osPrioFlagType uiTestPattern;
#endif

#if (STATUS_LEVEL == EXTENDED_STATUS)
   COVER(0x01D9)
   osSysErrAssert((osCheckInterruptsDisabled() != 0), osdErrQSInterruptsEnabled) /* TR:SPMF12:0007 */
#endif

#if osdNumberOfInternalResources > 0
   COVER(0x01DA)
   /* release internal resource, if one is occupied by the task */
   if (oskResInternalCeilingPrioMask[osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex] != 0)
   {
#if osdRTSize == 1
      COVER(0x01DB)
      ptrToCcb->ossQReadyPrios &= ~oskResInternalCeilingPrioMask[osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex];
#else
      COVER(0x01DC)
      ptrToCcb->ossQReadyPrios[oskResInternalCeilingPrioOffset[osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex]] &=
         ~oskResInternalCeilingPrioMask[osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex];
#endif
#if ((CC == ECC2) || (CC == BCC2))
      /* delete task out of the prio queue */
      ptrToCcb->ossQReadyTaskHead[osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio]++;
      if (ptrToCcb->ossQReadyTaskHead[osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio] > oskQMaxActivations[osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio])
      {
         COVER(0x01DD)
         ptrToCcb->ossQReadyTaskHead[osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio]= 0;
      }
      ELSEWITHCOVER(0x01DE)
#else
      /* delete task from the prio */
      ptrToCcb->ossQReadyTask[osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio] = osdNoActiveTask;
#endif
      COVER(0x01DF)

#if osdORTIDebug
      COVER(0x01E0)
      osTcbActualPrio[osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex] = oskTcbHomePrio[osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex];
#endif
   }
   ELSEWITHCOVER(0x01E1)
#endif /* osdNumberOfInternalResources > 0 */

   /* calculate ready task with highest priority */
   COVER(0x01E2)
#if osdRTSize > 1
   COVER(0x01E3)
   ptr = ptrToCcb->ossQReadyPrios;
   uiTestPattern = *ptr;
   hiPriorTask = 0;
   IFCOVER(!uiTestPattern,0x01FD,0x01FE)
   while (!uiTestPattern)
   {
      ptr++;
      /* at least the task releasing its internal resource must still be ready on its home prio. */
      osSysErrAssert((ptr <= &ptrToCcb->ossQReadyPrios[osrRTSize-1]), osdErrQSNoReadyTaskFound)
      uiTestPattern = *ptr;
      hiPriorTask += osdPrioBitsPerWord;
      IFCOVER(!uiTestPattern,0x01FF,0x0200)
   }
   COVER(0x01E4)
   hiPriorTask += osGetHighPrioBit(uiTestPattern);
#else
   /* at least the task releasing its internal resource must still be ready on its home prio. */
   osSysErrAssert((ptrToCcb->ossQReadyPrios != 0), osdErrQSNoReadyTaskFound)
   hiPriorTask = osGetHighPrioBit(ptrToCcb->ossQReadyPrios);
#endif


#if ((CC == BCC2) || (CC == ECC2))
   COVER(0x01E5)
   ptrToCcb->ossHighReadyTaskIndex = oskQActivationQueues[hiPriorTask][ptrToCcb->ossQReadyTaskHead[hiPriorTask]];
#else
   COVER(0x01E6)
   ptrToCcb->ossHighReadyTaskIndex = ptrToCcb->ossQReadyTask[hiPriorTask];
#endif

   ptrToCcb->ossHighReadyTaskPrio  = hiPriorTask;

   /* KB begin osekHWosSchedulePrioReaction (default) */
      if (ptrToCcb->ossHighReadyTaskIndex != osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex)
      {
         COVER(0x01E7)
         ptrToCcb->ossStartDispatcher    = osdTRUE;
      }
      ELSEWITHCOVER(0x01E8)
   /* KB end osekHWosSchedulePrioReaction */
   return;
}
#endif /* ((osdNumberOfAllTasks > 0) && !defined(osdScheduleNotUsed)) */


#if (osdNumberOfInternalResources > 0)
/*-+--------------------------------------------------------------------------
 / osSchedBackToRunPrio
 / Function:
 /   - occupies the ceiling priority of the internal resource assigned to the
 /     active task
 /   - high ready task prio is reset to the ceiling prio (may have been lowered
 /     by osSchedOnHomePrio before)
 /
 /   Note: This function must be called with interrupts disabled and local
 /         core's lock occupied! No cross-core support!
 /
 / Parameter:     void
 / Return value:  void
 /--------------------------------------------------------------------------*/

osqFunc1 void osqFunc2 osSchedBackToRunPrio(void)
{
   /* CovComment 4:  Function: osSchedBackToRunPrio */


   if (oskResInternalCeilingPrioMask[osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex] != 0)
   {
      osPrioType IntResCeilingPrio = oskResInternalCeilingPrio[osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex];

#if ((CC == ECC2) || (CC == BCC2))
      COVER(0x01E9)
      /* Add task to the ready queue */
      oskQActivationQueues[IntResCeilingPrio][ptrToCcb->ossQReadyTaskTail[IntResCeilingPrio]] = osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex;
      /* increment tail and handle overflow */
      ptrToCcb->ossQReadyTaskTail[IntResCeilingPrio]++;
      if (ptrToCcb->ossQReadyTaskTail[IntResCeilingPrio] > oskQMaxActivations[IntResCeilingPrio])
      {
         COVER(0x01EA)
         ptrToCcb->ossQReadyTaskTail[IntResCeilingPrio] = 0;
      }
      ELSEWITHCOVER(0x01EB)
#else
      COVER(0x01EC)
      /* this task is ready on this priority */
      ptrToCcb->ossQReadyTask[IntResCeilingPrio] = osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex;
#endif

      /* task is ready on this priority */
#if osdRTSize == 1
      COVER(0x01ED)
      ptrToCcb->ossQReadyPrios |= oskResInternalCeilingPrioMask[osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex];
#else
      COVER(0x01EE)
      ptrToCcb->ossQReadyPrios[oskResInternalCeilingPrioOffset[osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex]] |= /*;*/
         oskResInternalCeilingPrioMask[osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex];
#endif

      /* ptrToCcb->ossHighReadyTaskPrio was modified in osSchedOnHomePrio - reset to ceiling prio */
      ptrToCcb->ossHighReadyTaskPrio = IntResCeilingPrio;

#if osdORTIDebug
      COVER(0x01EF)
      osTcbActualPrio[osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex] = osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio;
#endif
   }
   ELSEWITHCOVER(0x01F0)
}
#endif

/* KB begin osekEndOfCModule (overwritten) */
#pragma ghs section bss=default
#pragma ghs section data=default
#pragma ghs section sbss=default
#pragma ghs section sdata=default
#pragma ghs section text=default
#pragma ghs section rodata=default
#pragma ghs section rosdata=default
/* KB end osekEndOfCModule */

/* END OF MODULE osekSched.c */


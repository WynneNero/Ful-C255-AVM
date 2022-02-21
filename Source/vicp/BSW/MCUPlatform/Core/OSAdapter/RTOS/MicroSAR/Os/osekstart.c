/* Kernbauer Version: 2.16 Konfiguration: RH850 Erzeugungsgangnummer: 214 Zweig: 1 */

/*****************************************************************************
| Project Name: MICROSAR OS
|    File Name: osekstart.c
|
|  General code: @Version: 9.01.04@
|  Module version: $vv$=1.06
|
|  Description: OSEK Start API
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

/* CovComment 0:  file: osekstart.c */

/* KB begin osekStartOfCModule (overwritten) */
#pragma ghs section bss=".os_bss"
#pragma ghs section data=".os_data"
#pragma ghs section sbss=".os_sbss"
#pragma ghs section sdata=".os_sdata"
#pragma ghs section text=".os_text"
#pragma ghs section rodata=".os_rodata"
#pragma ghs section rosdata=".os_rosdata"
/* KB end osekStartOfCModule */


#if (osdNumberOfAllTasks>0)
static osqFunc1 void osqFunc2 osInitTCBs(void);
#endif

/* KB begin osekStartAdditionalPrototypes (overwritten) */
static osqFunc1 void osqFunc2 osInitSystemStack(void);
#if (osdNumberOfAllTasks > 0)   
static osqFunc1 void osqFunc2 osInitTaskStacks(void);
#endif
#if (osdNumberOfCat2ISRs > 0)
static osqFunc1 void osqFunc2 osInitISRStacks(void);
#endif


/* MISRA RULE 14.1 not violated: osInitINTC is called in assember code. */
osqFunc1 void osqFunc2 osInitINTC(void) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osInitINTC       */
   COVER(0x0102)   
         osSetEBASE((osuint32)&osExceptionVectorTable_c0);
         osSetPSW(osGetPSW() | (osuint32)0x00008000UL);
         osSetINTCFG((osuint32)0);
         osSetINTBP((osuint32)&osEIINTVectorTable_c0);
#if (osdNumberOfAllISRs > 0)
         {
            osuint16 index;
            IFCOVER(0 >= osdNumberOfAllISRs,0x015A,0x015B)      
            for(index = 0; index < osdNumberOfAllISRs; index++)
            {
               osuint16 priolevel = osConfigBlock.osIsrPrioLevel[index];                 
               COVER(0x0103)               
               if(priolevel < osdNumberOfPrioLevels)
               {
                  osuint16 channel = osConfigBlock.osIsrChannel[index];                  
                  COVER(0x0104)                  
                  if(channel < 32)
                  {
                     {
                        osINTC1_ICxxx[channel].SEMANTIC.level = priolevel;
                        osINTC1_ICxxx[channel].SEMANTIC.TBxxx = 1;
                     }
                  }
                  else
                  {
                     {
                        osINTC2_ICxxx[channel].SEMANTIC.level = priolevel;
                        osINTC2_ICxxx[channel].SEMANTIC.TBxxx = 1;
                     }
                  }
               }
               ELSEWITHCOVER(0x0105)
            }
         }
#endif /* (osdNumberOfAllISRs > 0) */

#if (osdHwTimerNeeded0_OSTM || osdHwTimerNeeded0_OSTM_HIRES)
         osEnableInterrupt(osdTimerInterruptSourceNumberCore0); /* enables the system timer interrupt source */
#endif /* (osdHwTimerNeeded0_OSTM || osdHwTimerNeeded0_OSTM_HIRES) */
}

/* MISRA RULE 14.1 not violated: osInitStacks is called in assember code. */
osqFunc1 void osqFunc2 osInitStacks(void) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osInitStacks */
   COVER(0x0106)   
   osInitSystemStack();
#if (osdNumberOfAllTasks > 0)   
   osInitTaskStacks();
#endif
#if (osdNumberOfCat2ISRs > 0)
   osInitISRStacks();      
#endif
}


static osqFunc1 void osqFunc2 osInitSystemStack(void)
{
   /* CovComment 4:  Function: osInitSystemStack */
   osuint32 *stackPtr;
   osuint32 *stackEnd;

   COVER(0x0107)
   if (osConfigBlock.ucStackUsageMeasurement != 0)
   {
      COVER(0x0108)
      stackPtr = (osuint32*)osConfigBlock.SystemStack[osSysGetCoreID()].start;
      stackEnd = (osuint32*)osGetCurrentSP();
      osSysErrAssert(((stackEnd > (osuint32*)osConfigBlock.SystemStack[osSysGetCoreID()].start) && (stackEnd < (osuint32*)osConfigBlock.SystemStack[osSysGetCoreID()].end)), osdErrYOSystemStackOverflow) 
      while(stackPtr < stackEnd)
      {  
         COVER(0x0109)
         *stackPtr = osdStackCheckPattern;
         stackPtr++;
      }         
   }
   else
   {
      COVER(0x010A)
      *(osuint32*)osConfigBlock.SystemStack[osSysGetCoreID()].start = osdStackCheckPattern;   
   }
}

#if (osdNumberOfCat2ISRs > 0)
static osqFunc1 void osqFunc2 osInitISRStacks(void)
{
   /* CovComment 4:  Function: osInitISRStacks */
   osuint32 cat2ISRID;
   osuint32* stackPtr;
   COVER(0x010B)
   if (osConfigBlock.ucStackUsageMeasurement != 0)
   {         
      COVER(0x010C)         
      for (cat2ISRID = 0; cat2ISRID < osConfigBlock.uiNumberOfCat2ISRs; cat2ISRID++)
      {
         stackPtr = (osuint32*)osConfigBlock.osCat2IsrStacks[ cat2ISRID ].start;
         while (stackPtr < (osuint32*)osConfigBlock.osCat2IsrStacks[ cat2ISRID ].end)
         {
            COVER(0x010D)
            *stackPtr = osdStackCheckPattern;
            stackPtr++;
         }                        
      }
   }
   else
   {
      COVER(0x010E)         
      for (cat2ISRID=0; cat2ISRID < osConfigBlock.uiNumberOfCat2ISRs; cat2ISRID++)
      {
         COVER(0x010F)
         *((osuint32*)osConfigBlock.osCat2IsrStacks[ cat2ISRID ].start) = osdStackCheckPattern;
      }
   }
}
#endif /* (osdNumberOfCat2ISRs > 0) */

#if osdNumberOfAllTasks>0
static osqFunc1 void osqFunc2 osInitTaskStacks(void)
{
   /* CovComment 4:  Function: osInitTaskStacks */
   osTaskIndexType taskID;
   osuint32* stackPtr;
   
   COVER(0x0110)   
   if (osConfigBlock.ucStackUsageMeasurement != 0)               
   {    
      for(taskID = 0; taskID < osConfigBlock.uiNumberOfTasks; taskID++)
      {  
         COVER(0x0111)
         stackPtr = (osuint32*)osConfigBlock.aulTaskStackStartAddress[taskID];            
         while (stackPtr < (osuint32*)osConfigBlock.aulTaskStackEndAddress[taskID])
         {
            COVER(0x0112)
            *stackPtr = osdStackCheckPattern;
            stackPtr++;
         }
      }
   }
   else
   {      
      for(taskID = 0; taskID < osConfigBlock.uiNumberOfTasks; taskID++)   
      {
         COVER(0x0113)
         *((osuint32*)osConfigBlock.aulTaskStackStartAddress[taskID]) = osdStackCheckPattern;
      }
   }
}
#endif
/* KB end osekStartAdditionalPrototypes */


#if osdStackCheck
 #if osdStackUsageMeasurement
/* KB begin osekHWosFillSystemStackSrc (overwritten) */
/* KB end osekHWosFillSystemStackSrc */

 #else /* osdStackUsageMeasurement */
/* KB begin osekHWosInitSystemStackSrc (overwritten) */
/* KB end osekHWosInitSystemStackSrc */

 #endif /* osdStackUsageMeasurement */

  #if (osdNumberOfAllTasks > 0)
   #if osdStackUsageMeasurement
/* KB begin osekHwosFillTaskStacksSrc (overwritten) */
/* task stacks are filled in function osInitTaskStacks */
/* KB end osekHwosFillTaskStacksSrc */

   #else /* osdStackUsageMeasurement */
/* KB begin osekHWosInitTaskStacksSrc (overwritten) */
/* KB end osekHWosInitTaskStacksSrc */

   #endif /* osdStackUsageMeasurement */
  #endif /* (osdNumberOfAllTasks > 0) */
#endif /* osdStackCheck */

/*----------------------------------------------------------------------------
 / osInitialize
 / Function:
 /   - Initialize all OS-variables, that are used by OS-API-functions which 
 /     might be used before StartOS() is called. This function should be used,
 /     if variables are not initialized by the startup-code, delivered with
 /     the compiler.
 / Parameter:    none
 / Return value: none
 /--------------------------------------------------------------------------*/

/* MISRA RULE 14.1 not violated: (command 1503) The function osInitialize is general 
 * code, called from within the function osStartOSasm, which might be implemented 
 * in assembly language or in C language dependent on the implementation. Therefore the
 * MISRA checker might not see the call and wrongly state a violation of rule 14.1 */
/* MISRA RULE 8.10 VIOLATION: (command 1505) The function osInitialize is part of the 
 * described API of the OS. Therefore external linkage is required and it depends
 * on the application whether or not the function is ever called. */
osqFunc1 void osqFunc2 osInitialize(void)      /* PRQA S 1503 */ /* PRQA S 1505 */
{
   /* CovComment 4:  Function: osInitialize */
   COVER(0x0114)
   /* KB begin osekHWosInitialize (overwritten) */
   ptrToCcb2->ossCallDispatcher = 0;
   /* KB end osekHWosInitialize */
   /* KB begin osekHWInitLevelDisableCounter (overwritten) */
   ptrToCcb2->ossIntSaveDisableCounter = 0;
   /* KB end osekHWInitLevelDisableCounter */
   /* KB begin osekHWInitGlobalDisableCounter (overwritten) */
   ptrToCcb2->ossIntSaveDisableCounterGlobal = 0;
   /* KB end osekHWInitGlobalDisableCounter */

   #if (STATUS_LEVEL == EXTENDED_STATUS)
   COVER(0x0115)
   osOwnCcb->LockIsNotNeeded.ossIntAPIStatus = 0;
   #endif
} 


/* TR:SPMF05:0001 Start */
/*-+--------------------------------------------------------------------------
 / StartOS 
 / =======
 / Syntax void StartOS ( AppModeType <Mode> )
 / Parameter (In):
 / Mode application mode
 / Parameter (Out): none
 / Description: The user can call this system service to start the operating
 / system in a specific mode, see chapter 5, Application modes.
 / Particularities: Only allowed outside of the operating system, therefore
 / implementation specific restrictions may apply. See also
 / chapter 11.3, System start-up, especially with respect to
 / systems where OSEK and OSEKtime coexist. This call does
 / not need to return.
 / Conformance: BCC1, BCC2, ECC1, ECC2
 /--------------------------------------------------------------------------*/
/* MISRA RULE 14.1 not violated: (command 1503) See comment for 8.10 */
/* MISRA RULE 8.10 VIOLATION: (command 1505) The function osStartOSc is general code 
 * and is called from within the implementation specific function osStartOSasm. 
 * That function might be written in assembler or C and be located in the same 
 * file as osStartOSc or another file, dependent on the implementation. Therfore 
 * MISRA checking tools might not see the call and state violation of rule 14.1 
 * wrongly or they see the call and state a violation of rule 8.10 correctly.
 * Anyhow, the function osStartOSc needs to have external linkage as some 
 * implementations have the calling function osStartOSasm in another file.
 */
osqFunc1 void osqFunc2 osStartOSc(void)     /* PRQA S 1503 *//* PRQA S 1505 */
{
   /* CovComment 4:  Function: osStartOSc */
   /* is called (from osStartOSasm) with interrupts disabled up to system level */

   /* KB begin osekHwSpecificStartOSVars (overwritten) */
   /* KB end osekHwSpecificStartOSVars */


   COVER(0x0116)

   OS_ST_ENTRY()
   OS_ST_START_CRITICAL()

   COVER(0x0117)

   /* Allow cat 1 interrupts (if they hadn't been enabled by the user anyway) */
   /* KB begin osekHWStartAllowCat1 (overwritten) */
   /* KB end osekHWStartAllowCat1 */

   /* KB begin dummyVariablesInit (default) */
   /* KB end dummyVariablesInit */


#if (STATUS_LEVEL == EXTENDED_STATUS)
   COVER(0x0118)
   osOwnCcb->LockIsNotNeeded.ossIntAPIStatus = 0;
#endif


#if (osdErrorHook!=0)
   COVER(0x0119)
   osOwnCcb->LockIsNotNeeded.ossErrorFlag = osdFALSE;
   /* KB begin osekInitGlobalError (default) */
   #if osdORTIDebug
   COVER(0x011A)
   osOwnCcb->LockIsNotNeeded.ossLastErrorCode=0;
   #endif
   COVER(0x011B)
   osOwnCcb->LockIsNotNeeded.ossLastError=0;
   /* KB end osekInitGlobalError */
#endif


#if STATUS_LEVEL == EXTENDED_STATUS
   /* Parameter checking, Mode is a bit-mask with only just one bit set */
   IF3ORCOVER( ((osActiveAppMode & ((AppModeType)(osActiveAppMode-((AppModeType)1)))) != 0), (osActiveAppMode == 0), (osActiveAppMode > (1U << (osrNumberOfAppModes - 1))) ,0x0176,0x0177,0x0178,0x0179)
   /* MISRA RULE 12.4 not violated: Reading the variable osActiveAppMode is sideeffect free.
    */
   if (((osActiveAppMode & ((AppModeType)(osActiveAppMode-((AppModeType)1)))) != 0)  ||   /* more than one bit set   */  /* PRQA S 3415 */
       (osActiveAppMode == 0)                                                ||   /* zero      */
       (osActiveAppMode > (1U << (osrNumberOfAppModes - 1)))             )                /* exceeding maximum value */
   {
      COVER(0x011C)
      osUnrecoverableError(E_OS_SYS_ABORT, osdErrSTWrongAppMode);
   }
   ELSEWITHCOVER(0x011D)
#endif


#if (osdNumberOfAllTasks>0)
   COVER(0x011F)
   osInitTCBs();
#else
   COVER(0x0120)
   ptrToCcb->ossQReadyPrios = 0;
#endif

#if (osdNumberOfSemaphores > 0)
   {
      osSemaphoreType ns;
      IFCOVER( 0>=osdNumberOfSemaphores,0x015C,0x015D)
      for (ns= 0; ns < osdNumberOfSemaphores; ns++)
      {
         COVER(0x0121)
         osSemaphoreState[ns]= 1; /* semaphore is released at startup */
#if (osdKillTaskIsrPossible || (osdSC== SC3) || (osdSC== SC4))
         COVER(0x0122)
         osSemaOwner[ns] = osdNoActiveTask;
#endif
         IFCOVER( (ns+1) < osdNumberOfSemaphores,0x015E,0x015F)
      }
      COVER(0x0123)
   }
#endif


 #if osdStackCheck
   COVER(0x0124)
  #if (osdNumberOfAllTasks > 0)
   COVER(0x0125)
   #if osdStackUsageMeasurement
   {
      COVER(0x0126)
      /* TR:SPMF08:0003 Start */
      /* TR:SPMF08:0005 Start */
      /* KB begin osekHWosFillTaskStacks (overwritten) */
      /* already called in osStartOSasm */
      /* KB end osekHWosFillTaskStacks */
      /* TR:SPMF08:0003 End */
      /* TR:SPMF08:0005 End */
   }
   #else
   {
      COVER(0x0127)
      /* TR:SPMF07:0002 Start */
      /* TR:SPMF07:0004 Start */
      /* TR:SPMF08:0005 Start */
      /* KB begin osekHWosInitTaskStacks (overwritten) */
      /* already called in osStartOSasm */
      /* KB end osekHWosInitTaskStacks */
      /* TR:SPMF07:0002 End */
      /* TR:SPMF07:0004 End */
      /* TR:SPMF08:0005 End */
   }
   #endif
  #endif
 #endif
#if (osdStackCheck || osdCallTimingHooks)
   osOwnCcb->LockIsNotNeeded.ossLastActiveTaskIndex = osdNoActiveTask;
#endif

   osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio  = ptrToCcb->ossHighReadyTaskPrio  = osdNoActivePrio;
   osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex = ptrToCcb->ossHighReadyTaskIndex = osdNoActiveTask;

   osOwnCcb->LockIsNotNeeded.ossIntNestingDepth = 0;
   ptrToCcb->ossStartDispatcher = osdFALSE;
#if (osdFullPreempt || osdMixedPreempt)
   COVER(0x0128)
   osOwnCcb->LockIsNotNeeded.ossLockDispatcher = 1; /* lock dispatcher during StartOS */
#endif

   /* fullfills [SR:167] of $\AutosarOS\general\Generation5\_doc\12_SystemRequirements\RequirementsSpec_MicrosarOS.doc */
   osOwnCcb->LockIsNotNeeded.ossActiveISRID = INVALID_ISR;

#if (STATUS_LEVEL == EXTENDED_STATUS)
   COVER(0x0129)
/* TR:SPMF12:0006 Start */
#if osdEnableAssertions
   COVER(0x012A)
   /* check memory access */
   osSysErrAssert((ptrToCcb->ossStartDispatcher == osdFALSE), osdErrSTMemoryError)
#if (osdFullPreempt || osdMixedPreempt)
   COVER(0x012B)
   osSysErrAssert((osOwnCcb->LockIsNotNeeded.ossLockDispatcher==1), osdErrSTMemoryError)
#endif
   /* assure that OS variables are really linked to RAM, osOwnCcb->LockIsNotNeeded.ossIntAPIStatus is volatile so compiler optimizations do not disturb */
   osOwnCcb->LockIsNotNeeded.ossIntAPIStatus = 7; 
   osSysErrAssert((osOwnCcb->LockIsNotNeeded.ossIntAPIStatus==7), osdErrSTMemoryError)
   osOwnCcb->LockIsNotNeeded.ossIntAPIStatus = 0;
   osSysErrAssert((osOwnCcb->LockIsNotNeeded.ossIntAPIStatus==0), osdErrSTMemoryError)
#endif
/* TR:SPMF12:0006 End */
#if (!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed))
 #if ((osdNumberOfAllResources - osdNumberOfInternalResources) > 0)
   osOwnCcb->LockIsNotNeeded.ossResGlobalOccupationCounter = 0;
 #endif
#endif
#endif /* STATUS_LEVEL == EXTENDED_STATUS */

#if (osdNumberOfAllResources > 0)
   COVER(0x012C)
#if (STATUS_LEVEL == EXTENDED_STATUS) || osdORTIDebug
   {
      osResourceIndexType nr;
      
      for (nr = 0; nr < osrNumberOfAllResources; nr++)
      {
         COVER(0x012D)
            #if (STATUS_LEVEL == EXTENDED_STATUS) && ((!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed)))
               COVER(0x012E)
               osResOccupationCounter[nr] = 0;
            #endif
            #if ((STATUS_LEVEL == EXTENDED_STATUS) && osdEnableAssertions && ((!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed)))) || osdORTIDebug
               COVER(0x012F)
               osResActualTask[nr] = osdNoActiveTask;
            #endif
         IFCOVER( (nr+1) < osrNumberOfAllResources,0x0160,0x0161)
      }
      COVER(0x0130)
   }
#endif /* (STATUS_LEVEL == EXTENDED_STATUS) || osdORTIDebug */
#endif /* (osdNumberOfAllResources > 0) */


   
#if (osdNumberOfAllTasks > 0)
   {
      osTaskIndexType nt;

      /* activate all autostart tasks */
      
      for (nt = 0; nt < osrNumberOfAllTasks; nt++)
      {
         COVER(0x0131)
            osTcbTaskState[nt] = SUSPENDED;
            #if STATUS_LEVEL == EXTENDED_STATUS
            COVER(0x0132)
            #if (osdNumberOfInternalResources > 0) || (osdNumberOfInterruptResources > 0)
            COVER(0x0133)
            osTcbResourceCounter[nt]=0;
            #endif
            #endif

#if osdCallTimingHooks
            osNextRunReason[nt] = OS_VTHP_TASK_ACTIVATION;
            COVER(0x0134)
#else
            COVER(0x0135)
#endif

            if ((oskTcbAutoStart[nt] & osActiveAppMode) != 0)
            {
               COVER(0x0136)
               (void) osSysActivateTask(nt); 
            }
            ELSEWITHCOVER(0x0137)
         IFCOVER( (nt+1) < osrNumberOfAllTasks,0x0162,0x0163)
      }
      COVER(0x0138)
   }
#endif

#if (osdNumberOfCounters > 0)
   {
      osuint8 nc;

      for(nc = 0; nc < osrNumberOfCounters; nc++)
      {
         COVER(0x0139)
            osCounter[nc] = 0;
            osAlarmHeapCount[nc] = 0;
         IFCOVER( (nc+1) < osrNumberOfCounters,0x0164,0x0165)
      }
      COVER(0x013A)
   }
#endif

#if (osdHardwareTimerNeeded)
   {
      COVER(0x013B)
      osPreInitTimer(); /* initialize all the timer stuff, but do not start them */
   }
#endif /*#if (osdHardwareTimerNeeded)*/

#if (osdNumberOfAlarms > 0)
   COVER(0x013C)
   osInitAlarms(); /* TR:SPMF20:0014 */
#endif

#if (osdNumberOfScheduleTables > 0)
   COVER(0x013D)
   osInitScheduleTables();
#endif


   /* KB begin osekHWStartupSpecial (overwritten) */
   COVER(0x013E)
   #if osdExceptionDetails
   ptrToCcb2->ossUnhandledExceptionDetail = 0;
   ptrToCcb2->ossISRUnhandledException_Number = 0;
   #endif
   /* KB end osekHWStartupSpecial */

#if (osdNumberOfAllResources > 0)
   COVER(0x013F)
#if (osdKillTaskIsrPossible || (osdSC== SC3) || (osdSC== SC4))
   COVER(0x0140)
#if (osdNumberOfCat2ISRs > 0)
   COVER(0x0141)
   {
      ISRType ni;
      
      for (ni=0; ni<osdNumberOfCat2ISRs; ni++)
      {
         COVER(0x0142)
            osIcbLockedResource[ni] = osdNoResource;
         IFCOVER( (ni+1)<osdNumberOfCat2ISRs,0x0166,0x0167)
      }
      COVER(0x0143)
   }
#endif /*osdNumberOfCat2ISRs*/
#if (osdNumberOfAllTasks > 0)
   COVER(0x0144)
   {
      osTaskIndexType nt;
      
      for (nt=0; nt<osdNumberOfAllTasks; nt++)
      {
         COVER(0x0145)
            osTcbLockedResource[nt] = osdNoResource;
         IFCOVER( (nt+1)<osdNumberOfAllTasks,0x0168,0x0169)
      }
      COVER(0x0146)
   }
#endif /*osdNumberOfAllTasks*/
   {
      osResourceIndexType nr;
      
      for (nr=0; nr<osdNumberOfAllResources; nr++)
      {
         COVER(0x0147)
            osResNextLockedResource[nr] = osdNoResource;
         IFCOVER( (nr+1)<osdNumberOfAllResources,0x016A,0x016B)
      }
      COVER(0x0148)
   }
#endif /*(osdKillTaskIsrPossible || (osdSC== SC3) || (osdSC== SC4)) */
#endif /* (osdNumberOfAllResources > 0) */

   COVER(0x0149)

#if (osdNumberOfApplications > 0)
   /* osOwnCcb->LockIsNotNeeded.ossActiveApplicationID might be sometimes used in the StartupHook.
    * Therefore it must be initialized here, even if it is not always 
    * used before the next assignment. This is no MISRA error. (3198) */
   osOwnCcb->LockIsNotNeeded.ossActiveApplicationID = INVALID_OSAPPLICATION;   /* PRQA S 3198 */
#endif /* (osdNumberOfApplications > 0) */


   osOwnCcb->LockIsNotNeeded.ossStarted = osdTRUE;


#if osdSysStartupHook
   COVER(0x014A)
   /* call hook-routine for system startup (initialization of drivers etc.) */
   OS_STHOOK_ENTRY()
   /* KB begin osekHWInterStartupHook (overwritten) */
   COVER(0x014B)
   osCheckCurrentStack();
   //StartupHook();
   osCheckStackPattern();
   /* KB end osekHWInterStartupHook */
   OS_STHOOK_EXIT()
#endif



#if (osdHardwareTimerNeeded)
   {
      COVER(0x014C)
      osInitTimer(); /* start each used timer (called after startup-hook) */
   }
#endif /*#if (osdHardwareTimerNeeded)*/

#if (osdFullPreempt || osdMixedPreempt)
   COVER(0x014D)
   /* free dispatcher (after osSysActivateTask for AutoStart-Tasks and after StartupHook */
   osOwnCcb->LockIsNotNeeded.ossLockDispatcher = 0; 
#endif


   OS_ST_END_CRITICAL()
   OS_ST_EXIT()
   /* KB begin osekHWosEnableLevelInStartOS (overwritten) */
   osEnableLevel();
   /* KB end osekHWosEnableLevelInStartOS */

   OS_START_DISPATCH()

   /* KB begin osekHWosLocalDispatcher (overwritten) */
   ptrToCcb2->ossCallDispatcher = 1;
   osDispatch();
   /* KB end osekHWosLocalDispatcher */

   /* KB begin osekHWAfterOsDispatchInST (overwritten) */
   osDispatch();
   /* fullfills [SR:012] of $\AutosarOS\general\Generation5\_doc\12_SystemRequirements\RequirementsSpec_MicrosarOS.doc */
   osEnterSafeState(E_OS_SYS_ASSERTION, osdErrSTNoImmediateTaskSwitch);
   /* KB end osekHWAfterOsDispatchInST */
} /* END OF osStartOSc */

/* KB begin osekHWosStartOSasmSrc (overwritten) */
/* KB end osekHWosStartOSasmSrc */


/*-+--------------------------------------------------------------------------
 / osInitTCBs
 / Funktion:
 /   - inits all tasks as SUSPENDED
 / Parameter:
 / Returnvalue:
 /--------------------------------------------------------------------------*/
#if (osdNumberOfAllTasks>0)
static osqFunc1 void osqFunc2 osInitTCBs(void)
{
   /* CovComment 4:  Function: osInitTCBs */
   osPrioType np;

#if ((CC==BCC2) || (CC==ECC2) || osdORTIDebug)
   osTaskIndexType nt;

   for (nt=0; nt<osrNumberOfAllTasks; nt++)
   {
      COVER(0x0151)
         #if (CC==BCC2) || (CC==ECC2)
         COVER(0x0152)
         osTcbActivationCount[nt]= 0;
         #endif
         #if osdORTIDebug
         COVER(0x0153)
         osTcbActualPrio[nt] = oskTcbHomePrio[nt];
         osTcbORTIServiceId[nt] = osdORTINoService;
         #endif
      IFCOVER( (nt+1)<osrNumberOfAllTasks,0x0170,0x0171)
   }
   COVER(0x0154)
#endif /* ((CC==BCC2) || (CC==ECC2) || osdORTIDebug) */

#if (osdRTSize > 1)
   
   for (np=0; np<osrRTSize; np++)
   {
      COVER(0x0155)
      ptrToCcb->ossQReadyPrios[np] = 0;
      IFCOVER( (np+1)<osrRTSize,0x0172,0x0173)
   }
   COVER(0x0156)
#else
   COVER(0x0157)
   ptrToCcb->ossQReadyPrios = 0;
#endif

   /* all activation queues are empty */

   for (np = 0; np < osrNumberOfPriorities; np++)
   {
   #if (CC==BCC2) || (CC==ECC2)
      COVER(0x0158)
      ptrToCcb->ossQReadyTaskHead[np]= ptrToCcb->ossQReadyTaskTail[np]= 0;
   #else
      COVER(0x0159)
      ptrToCcb->ossQReadyTask[np]= osdNoActiveTask;
   #endif
      IFCOVER( (np+1) < osrNumberOfPriorities,0x0174,0x0175)
   } /* for (np = 0; np < osrNumberOfPriorities; np++) */

   /* KB begin osekHWosInitTcbExtension (overwritten) */
   /* KB end osekHWosInitTcbExtension */
} /* END OF osInitTCBs */
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

/* END OF MODULE osekstart.c */


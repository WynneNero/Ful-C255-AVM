/* Kernbauer Version: 2.16 Konfiguration: RH850 Erzeugungsgangnummer: 214 Zweig: 1 */

/*****************************************************************************
| Project Name: MICROSAR OS
|    File Name: osek.c
|
|  General code: @Version: 9.01.04@
|  Module version: $vv$=2.40
|
|  Description: osek startup, scheduler and dispatcher
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

/* CovComment 0:  file: osek.c */

/* KB begin osekHWcompileTimeChecks (default) */
#define OS_STATIC_ASSERT(COND,MSG) typedef char os_static_assertion_##MSG[(COND)?1:-1]
/* KB begin osekHWspecCompileTimeChecks (overwritten) */
/* KB end osekHWspecCompileTimeChecks */
/* KB end osekHWcompileTimeChecks */

/* KB begin osekHWOsekAdditionalInclude (default) */
/* KB end osekHWOsekAdditionalInclude */

/* KB begin osekStartOfCModule (overwritten) */
#pragma ghs section bss=".os_bss"
#pragma ghs section data=".os_data"
#pragma ghs section sbss=".os_sbss"
#pragma ghs section sdata=".os_sdata"
#pragma ghs section text=".os_text"
#pragma ghs section rodata=".os_rodata"
#pragma ghs section rosdata=".os_rosdata"
/* KB end osekStartOfCModule */

/* KB begin osekHWVariableSectionStart (overwritten) */
/* KB end osekHWVariableSectionStart */

#if (osdNumberOfAllTasks > 0)
/* MISRA RULE 8.10 VIOLATION: On some platforms, osTcbSP might be used by several
 * functions / files. Conditional definition of the variable for these
 * platforms would increase the code complexity to unacceptable level (1504).
 */
/* MISRA RULE 8.7 VIOLATION: On some platforms, osTcbSP might be used by several
 * functions / files. Conditional definition of the variable for these
 * platforms would increase the code complexity to unacceptable level (1514).
 */
osqRAM0 osqRAM1 osqRAM2 osStackPtrType osqRAM3 osTcbSP[osdNumberOfAllTasks]; /* PRQA S 1504 */ /* PRQA S 1514 */ 

#else
/* MISRA RULE 8.10 VIOLATION: On some platforms, osTcbSP might be used by several
 * functions / files. Conditional definition of the variable for these
 * platforms would increase the code complexity to unacceptable level (1504).
 */
/* MISRA RULE 8.7 VIOLATION: On some platforms, osTcbSP might be used by several
 * functions / files. Conditional definition of the variable for these
 * platforms would increase the code complexity to unacceptable level (1514).
 */
osqRAM0 osqRAM1 osqRAM2 osStackPtrType osqRAM3 osTcbSP[1]; /* PRQA S 1504 */ /* PRQA S 1514 */
#endif

#if (osdNumberOfCounters > 0)
osqRAM0 osqRAM1 osqRAM2 osAlarmIndexType osqRAM3 osAlarmHeapCount[osdNumberOfCounters];    /* Number of heap elements */
#endif

osqRAM0 osqRAM1 volatile osqRAM2 AppModeType osqRAM3 osActiveAppMode;

/* KB begin dummyVariables (default) */
/* KB end dummyVariables */

/* KB begin osekHWVariableDefinition (overwritten) */
/* MISRA RULE 8.8 VIOLATION: Pointer oskStackTop_SYS_c0 is only used in osekasm.c.
   It is used in assembler code and therefore it cannot be static. */
void* const * const oskStackTop_SYS_c0 = &osConfigBlock.SystemStack[0].start; /* PRQA S 3408 */
/* KB end osekHWVariableDefinition */

/* KB begin osekHWVariableSectionEnd (overwritten) */
/* KB end osekHWVariableSectionEnd */

/* KB begin osekConstSectionCodeStart (overwritten) */
/* MISRA RULE 8.8 VIOLATION: Pointer ptrToCallDispatcher_c0 is used in assembler code and therefore it cannot be static. */
volatile osuint8* const ptrToCallDispatcher_c0 = (volatile osuint8*)&(osCtrlVarsCore0.LockIsNotNeeded.ossCallDispatcher); /* PRQA S 3408 */

/* MISRA RULE 8.8 VIOLATION: Pointer ptrToNestingDepth_c0 is used in assembler code and therefore it cannot be static. */
volatile osuint8* const ptrToNestingDepth_c0 = (volatile osuint8*)&(osCtrlVarsCore0.LockIsNotNeeded.ossIntNestingDepth); /* PRQA S 3408 */

/* MISRA RULE 8.8 VIOLATION: Pointer ptrToSavedIntLevel_c0 is used in assembler code and therefore it cannot be static. */
volatile osuint32* const ptrToSavedIntLevel_c0 = (volatile osuint32*)&(osCtrlVarsCore0.LockIsNotNeeded.ossSavedIntLevel); /* PRQA S 3408 */

/* MISRA RULE 8.8 VIOLATION: Pointer ptrToSavedIntLevelNested_c0 is used in assembler code and therefore it cannot be static. */
volatile osuint32* const ptrToSavedIntLevelNested_c0 = (volatile osuint32*)&(osCtrlVarsCore0.LockIsNotNeeded.ossSavedIntLevelNested); /* PRQA S 3408 */

/* KB end osekConstSectionCodeStart */

/* TR:SPMF29:0002 Start */
/* MISRA RULE 8.7 VIOLATION: This constant is to be included into the binary to identify the configuration. 
 * It is not used by internal code, instead it is meant for usage by external tools. 
 * So it exists without a reference.
 */
osqROM0 osqROM1 const osqROM2 osVersionVariantCodingType osqROM3 oskVersionVariant = /* PRQA S 1514 */
{
   0xAF, /* magic number */
   0xFE,
   0xDE,
   0xAD,
   (osuint8)osdVrmMajRelNumRef, /* version of operating system, Major, defined in vrm.h */
   (osuint8)osdVrmMinRelNumRef, /* version of operating system, Minor */

   (osuint8)osdVrmGenMajRelNumRef, /* version of code generator */
   (osuint8)osdVrmGenMinRelNumRef,

   /* variant used (part 1) */
   /* Bit 0..1:   Conformance Class */
   /* Bit 2:      Status level */
   /* Bit 3..4:   Scheduling policy */
   /* Bit 5:      Stackcheck */
   /* Bit 6:      EnableInternalAssertions */
   /* Bit 7:      currently not used */

   (osuint8)(((osdVariantCC)                    ) |
             ((osdVariantStatus)            << 2) |
             ((osdVariantSchedule)          << 3) |
             ((osdVariantStackcheck)        << 5) |
             ((osdVariantAssertionsEnabled) << 6) |
             ((0U)                          << 7)), /* TR:SPMF12:0005 */

   /* variant used (part 2) */
   /* Bit 0..1:   Scalability Class */
   /* Bit 2:      Schedule table(s) used (Not used in library version) */
   /* Bit 3:      High resolution schedule table(s) used (Not used in library version) */
   /* Bit 4:      Schedule table synchronization used*/
   /* Bit 5:      timing protection used */
   /* Bit 6:      Not yet used, always zero */
   /* Bit 7:      Not yet used, always zero */
   (osuint8)(((osdVariantSC)                    ) |
             ((osdVariantFeaturesUsed_ST)   << 2) |
             ((osdVariantFeaturesUsed_HRST) << 3) |
             ((osdVariantFeaturesUsed_Sync) << 4) |
             ((osdVariantFeaturesUsed_TP)   << 5)),
   
   /* ORTI variant                          */
   /* Bit 0..6: ORTI standard version       */
   /* Bit 7   : ORTI additional information */

   (osuint8)(((osdVariantORTIVersion)      ) |   
             ((osdVariantORTIDebug)    << 7)), /* TR:SPMF14:0011 */  /* TR:SPMF29:0003 */

   /* KB begin osekStructSpecVersionVariant (overwritten) */
      (osuint8) (0            )
   /* KB end osekStructSpecVersionVariant */

}; /* TR:SPMF29:0002 End */
/* KB begin osekConstSectionCodeEnd (overwritten) */
/* KB end osekConstSectionCodeEnd */







#if osdShutdownHook 
static osqFunc1 void osqFunc2 osInterShutdownHook(StatusType Error);
#endif /* osdShutdownHook  */

/* KB begin osekSysShutdownOS (default) */
/* osSysShutdownOS is called internally by the OS, osShutdownOS is the user */
/* API and contains additional checks */

/* fullfills [SR:162] of $\AutosarOS\general\Generation5\_doc\12_SystemRequirements\RequirementsSpec_MicrosarOS.doc */
/* fullfills [SR:013] of $\AutosarOS\general\Generation5\_doc\12_SystemRequirements\RequirementsSpec_MicrosarOS.doc */
/* MISRA RULE 8.10 VIOLATION: The function osSysShutdownOS is a general implementation which is used 
 * identically on different plattforms. On some of them, it is called only in osek.c, on others it 
 * is called also from other files. Therefore it is made globally visible. The risk of potential 
 * name collisions is expected to be low.*/
osqFunc1 void osqFunc2 osSysShutdownOS(StatusType Error)      /* PRQA S 1505 */
{
   /* CovComment 4:  Function: osSysShutdownOS */
   /* KB begin osekReadUnusedVarsAndConstsAux (default) */
      osuint8 ucTmp;
   /* KB end osekReadUnusedVarsAndConstsAux */


   /* KB begin osekHWSysShutdownOSAdditionalVariables (default) */
   /* KB end osekHWSysShutdownOSAdditionalVariables */

   OS_SD_ENTRY()
   COVER(0x0018)
   
   /* KB begin osekHWosDisableGlobal (overwritten) */
   osDisableGlobal(); /* disable all interrupts, no nesting */
   /* KB end osekHWosDisableGlobal */ /* disable all interrupts */

   /* Necessary to allow interrupt API functions in the shutdown hook 
    * together with timing protection */
   osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex = osdNoActiveTask;
   osOwnCcb->LockIsNotNeeded.ossIntNestingDepth = 0;
   
   

   /* call shutdown hook routines */


#if osdShutdownHook 
   COVER(0x0019)
   /* call system shutdown hook */
   OS_SDHOOK_ENTRY()
   //osInterShutdownHook(Error);
   OS_SDHOOK_EXIT()
#endif
   OS_SD_EXIT()
   
   /* osdDummyRead might intentionally assign a value to an unused variable on 
    * some platforms to avoid compiler warnings. This is no MISRA error. (3199) */
   osdDummyRead(Error) /* PRQA S 3199 */ 
   
   /* KB begin osekReadUnusedVarsAndConsts (default) */
   /* force the compiler to link these 'unused' variables, too */
   ucTmp  = (osuint8)oskVersionVariant.ucMagicNumber1;
   #if osdErrorHook
   ucTmp |= (osuint8)osOwnCcb->LockIsNotNeeded.ossLastError;
   #endif
   #if osdORTIDebug
   ucTmp |= (osuint8)osTcbActualPrio[0];
    #if osdErrorHook
   ucTmp |= (osuint8)osOwnCcb->LockIsNotNeeded.ossLastErrorCode;
    #endif
   #endif
   /* osdDummyRead might intentionally assign a value to an unused variable on 
    * some platforms to avoid compiler warnings. This is no MISRA error. (3199) */
   osdDummyRead(ucTmp)   /* PRQA S 3199 */
   /* KB end osekReadUnusedVarsAndConsts */
   /* KB begin osekHWosShutdownReactionSrc (default) */
   for(;;) 
   {
      ;
   }
   /* KB end osekHWosShutdownReactionSrc */
} /* END OF osSysShutdownOS */
/* KB end osekSysShutdownOS */

/*-+--------------------------------------------------------------------------
 / ShutdownOS
 / ==========
 /
 / Syntax void ShutdownOS ( StatusType <Error> )
 / Parameter (In):
 / Error error occurred
 / Parameter (Out): none
 / Description: The user can call this system service to abort the overall
 / system (e.g. emergency off). The operating system also calls
 / this function internally, if it has reached an undefined internal
 / state and is no longer ready to run.
 / If a ShutdownHook is configured the hook routine
 / ShutdownHook is always called (with <Error> as argument)
 / before shutting down the operating system.
 / If ShutdownHook returns, further behaviour of ShutdownOS is
 / implementation specific.
 / In case of a system where OSEK OS and OSEKtime OS
 / coexist, ShutdownHook must return.
 / <Error> must be a valid error code supported by OSEK OS. In
 / case of a system where OSEK OS and OSEKtime OS coexist,
 / <Error> might also be a value accepted by OSEKtime OS. In
 / this case, if enabled by an OSEKtime configuration parameter,
 / OSEKtime OS will be shut down after OSEK OS shutdown.
 / Particularities: After this service the operating system is shut down.
 / Allowed at task level, ISR level, in ErrorHook and StartupHook,
 / and also called internally by the operating system.
 / If the operating system calls ShutdownOS it never uses E_OK
 / as the passed parameter value.
 / Conformance: BCC1, BCC2, ECC1, ECC2
 /--------------------------------------------------------------------------*/

/* QAC messages 3206,3199: The parameter 'Error' is intentionally used only in certain 
 * configurations. In other configurations, it depends on the plattform specific 
 * definition of osdDummyRead, which of the messages is stated. Both messages are 
 * not relevant for MISRA */
/* MISRA RULE 14.1 VIOLATION: osShutdownOS might be not called in some
 * configuration. Conditional compiling of the function would increase
 * the code complexity to unacceptable level (1503) */ 
/* MISRA RULE 8.10 VIOLATION: On some platforms, osShutdownOS might be only
 * referenced from an API dispatch table in this file. Declaring it static for
 * only those platforms would increase the code complexity to unacceptable level
 * (1505) */ 
osqFunc1 void osqFunc2 osShutdownOS(StatusType Error) /* PRQA S 1503 */ /* PRQA S 1505 */ /* PRQA S 3206 */ /* PRQA S 3199 */
{
   /* CovComment 4:  Function: osShutdownOS */
   OS_SD_ENTRY()
   COVER(0x001A)
   

   COVER(0x001B)
   osSysShutdownOS(Error);
}

#if osdStackCheck
/* KB begin osekStackOverflow (overwritten) */
#ifdef osdSoftwareStackCheck
/*-+--------------------------------------------------------------------------
 / osStackError
 / Description: called if stack overflow was detected
 / Parameter: onSystemStack contains info on which stack the overflow was detected
 / Returnvalue: -
 /--------------------------------------------------------------------------*/
/* MISRA RULE 8.8 VIOLATION: The function osStackError is only called in assembler code. 
 * It cannot be made static because the compiler reports errors then. */
/* MISRA RULE 14.1 not violated: The function osStackError is only called in assembler code. 
 * MISRA checking tools do not see that and complain about it. */
osqFunc1 void osqFunc2 osStackError(osuint32 onSystemStack) /* PRQA S 3408 */ /* PRQA S 1503 */
{  
   /* CovComment 4:  Function: osStackError */
   #if osdErrorHook
   COVER(0x001C)
   if(onSystemStack != 0)
   {
      COVER(0x001D)
      ptrToCcb2->ossLastError = osdErrYOSystemStackOverflow;
   }
   else
   {
      COVER(0x001E)
      if(ptrToCcb2->ossIntNestingDepth != 0)
      {
         COVER(0x001F)
         ptrToCcb2->ossLastError = osdErrYOISRStackOverflow;         
      }
      else
      {
         COVER(0x0020)
         ptrToCcb2->ossLastError = osdErrSOStackOverflow;
      }
   }
   osErrorHook(E_OS_STACKFAULT);
   #endif

   COVER(0x0021)
   osSysShutdownOS(E_OS_STACKFAULT);
}
#endif
/* KB end osekStackOverflow */

/* KB begin osekHWosSystemStackOverflowSrc (overwritten) */
/* KB end osekHWosSystemStackOverflowSrc */

#if osdStackUsageMeasurement
/* KB begin osekStackUsageSrc (overwritten) */
/*-+--------------------------------------------------------------------------
 / osGetSystemStackUsage
 / Funktion: calculate maximum stack usage of interrupt stack
 / Parameter: -
 / Returnvalue: calculated stack usage (in byte)
 /--------------------------------------------------------------------------*/
/* MISRA RULE 14.1 VIOLATION: osGetSystemStackUsage is an API function which might be unused. */
osqFunc1 osStackUsageType osqFunc2 osGetSystemStackUsage(void) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osGetSystemStackUsage */
   osuint32 *stackPtr;   
   COVER(0x0022) 
   stackPtr = (osuint32*)osConfigBlock.SystemStack[osSysGetCoreID()].start;   
   IF2ANDCOVER((stackPtr < (osuint32*)osConfigBlock.SystemStack[osSysGetCoreID()].end), (*stackPtr == osdStackCheckPattern),0x00F6,0x00F7,0x00F8)   
   while ((stackPtr < (osuint32*)osConfigBlock.SystemStack[osSysGetCoreID()].end) && (*stackPtr == osdStackCheckPattern))
   {
      COVER(0x0023)
      stackPtr++;
   }
   COVER(0x0024)
   return (osStackUsageType)((osuint8*)osConfigBlock.SystemStack[osSysGetCoreID()].end - (osuint8*)stackPtr);
} /* end of osGetSystemStackUsage */
/* KB end osekStackUsageSrc */
  #if (osdNumberOfAllTasks > 0)
/* KB begin osekOsGetStackUsage (overwritten) */
/*-+--------------------------------------------------------------------------
 / osGetStackUsage
 / Description: calculate maximum stack usage of specified task
 / Parameter: task index
 / Returnvalue: calculated stack usage in byte
 /--------------------------------------------------------------------------*/
/* MISRA RULE 14.1 VIOLATION: osGetStackUsage is an API function which might be unused. */
osqFunc1 osStackUsageType osqFunc2 osGetStackUsage(TaskType taskId) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osGetStackUsage */
   osuint32 *stackPtr;
   COVER(0x0025) 
#if (STATUS_LEVEL == EXTENDED_STATUS)
   IFCOVER(taskId < osdNumberOfAllTasks,0x00E4,0x00E5)
   osSysErrAssert((taskId < osdNumberOfAllTasks), osdErrSUInvalidTaskIndex)
#endif
   stackPtr = (osuint32*)osConfigBlock.aulTaskStackStartAddress[taskId];
   IF2ANDCOVER((stackPtr < (osuint32*)osConfigBlock.aulTaskStackEndAddress[taskId]), (*stackPtr == osdStackCheckPattern),0x00F9,0x00FA,0x00FB)
   while ((stackPtr < (osuint32*)osConfigBlock.aulTaskStackEndAddress[taskId]) && (*stackPtr == osdStackCheckPattern))
   {
      COVER(0x0026)   
      stackPtr++;
   }
   COVER(0x0027)
   return (osStackUsageType)((osuint8*)osConfigBlock.aulTaskStackEndAddress[taskId] - (osuint8*)stackPtr);
} /* end of osGetStackUsage */

#if (osdNumberOfCat2ISRs > 0)
/*-+--------------------------------------------------------------------------
 / osGetISRStackUsage
 / Description: calculate maximum stack usage of ISRs on specific level  
 / Parameter: ISR index
 / Returnvalue: calculated stack usage in byte
 /--------------------------------------------------------------------------*/
/* MISRA RULE 14.1 VIOLATION: osGetISRStackUsage is an API function which might be unused. */ 
osqFunc1 osStackUsageType osqFunc2 osGetISRStackUsage(ISRType isrId) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osGetISRStackUsage */
   osuint32 *stackPtr;
   COVER(0x0028)   
#if (STATUS_LEVEL == EXTENDED_STATUS)
   IFCOVER(isrId < osdNumberOfCat2ISRs,0x00E6,0x00E7)
   osSysErrAssert(isrId < osdNumberOfCat2ISRs, osdErrSUInvalidIsrIndex)
#endif
   stackPtr = (osuint32*)osConfigBlock.osCat2IsrStacks[isrId].start;   
   IFCOVER(stackPtr != osdNULL,0x00E8,0x00E9)
   if (stackPtr != osdNULL)
   {
      IF2ANDCOVER((stackPtr < (osuint32*)(osConfigBlock.osCat2IsrStacks[isrId].end)) , (*stackPtr == osdStackCheckPattern),0x00FC,0x00FD,0x00FE)
      while ((stackPtr < (osuint32*)(osConfigBlock.osCat2IsrStacks[isrId].end)) && (*stackPtr == osdStackCheckPattern))
      {
         COVER(0x0029)
         stackPtr++;
      }
      COVER(0x002A)
   }
   return (osStackUsageType)((osuint8*)osConfigBlock.osCat2IsrStacks[isrId].end - (osuint8*)stackPtr);
} /* end of osGetISRStackUsage */
#endif
/* KB end osekOsGetStackUsage */
  #endif
#endif /* osdStackUsageMeasurement */
#endif /* osdStackCheck */

/* Necessary to Kill a task/ISR and to handle missing TerminateTask in SC3/4 */
#if (osdKillTaskIsrPossible || (osdSC== SC3) || (osdSC== SC4))

/*-+--------------------------------------------------------------------------
 / osSysKillResourceList
 / Funktion:
 /   - releases resource ResID and all resources locked by the same task/ISR
 /
 / Attention: function must be called with interrupts disabled!  
 /
 / Parameter: ResId : first resource to be released
 / Returnvalue:
 /--------------------------------------------------------------------------*/

#if (osdNumberOfAllResources > 0)
 #if (!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed))
/* MISRA RULE 8.10 VIOLATION: On some platforms, this function might only be accessed from within this file. 
   Catching all cases would be too difficult and error prone */
osqFunc1 void osqFunc2 osSysKillResourceList(ResourceType ResId) /* PRQA S 1505 */
{
   /* CovComment 4:  Function: osSysKillResourceList */
   
   COVER(0x002B)
   IFCOVER( ResId != osdNoResource,0x00EA,0x00EB)
   while (ResId != osdNoResource)
   {
      COVER(0x002C)
#if ((STATUS_LEVEL == EXTENDED_STATUS) && osdEnableAssertions && ((!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed)))) || osdORTIDebug
      COVER(0x002D)
      osResActualTask[ResId]= osdNoActiveTask;
#endif
#if STATUS_LEVEL == EXTENDED_STATUS
 #if (!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed))
      COVER(0x002E)
      osResOccupationCounter[ResId]= 0; /* not occupied */
  #if ((osdNumberOfAllResources - osdNumberOfInternalResources) > 0)
      osOwnCcb->LockIsNotNeeded.ossResGlobalOccupationCounter--;
  #endif /* ((osdNumberOfAllResources - osdNumberOfInternalResources) > 0) */
 #endif
#endif

#if (osdNumberOfInterruptResources > 0)
 #if (osdNumberOfTaskResources > 0)
      COVER(0x002F)
      if(ResId>=osrNumberOfTaskResources)
 #endif      
      {
         COVER(0x0030)
         /* switch from higher processing level */

         /* KB begin osekDecDispatcherLock (default) */
         #if (osdFullPreempt || osdMixedPreempt)
            COVER(0x0031)
            osOwnCcb->LockIsNotNeeded.ossLockDispatcher--;
         #endif
         /* KB end osekDecDispatcherLock */

         #if STATUS_LEVEL == EXTENDED_STATUS
         /* counter needed only for mixed resource system (task, interrupt and internal) */
         
         /* decrement counter only if task is accessing */
         if (osOwnCcb->LockIsNotNeeded.ossIntNestingDepth == 0)
         {
            COVER(0x0032)
            osTcbResourceCounter[osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex]--;
         }
         ELSEWITHCOVER(0x0033)
         #endif
         
         #if osdORTIDebug
         COVER(0x0034)
         osResActualTask[ResId]= osdNoActiveTask;
         #endif

      }
 #if (osdNumberOfTaskResources > 0)
      else
      {
         COVER(0x0035)
         /* stay on task level - business as usual */     
 #endif
#endif

#if osdRTSize == 1
         COVER(0x0036)
         osOwnCcb->LockIsNeeded.ossQReadyPrios&= ~oskResCeilingPrioMask[ResId];
#else
         COVER(0x0037)
         osOwnCcb->LockIsNeeded.ossQReadyPrios[oskResCeilingPrioOffset[ResId]]&= ~oskResCeilingPrioMask[ResId];
#endif

#if (osdNumberOfInterruptResources > 0)
 #if (osdNumberOfTaskResources > 0)
      }
 #endif
#endif
      COVER(0x0038)
      /* remove resource from linked list */
      ResId = osResNextLockedResource[ResId];

      IFCOVER( ResId != osdNoResource,0x00EC,0x00ED)
   } /* while (ResId != osdNoResource) */
}
 #endif /* (!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed)) */
#endif /* (osdNumberOfAllResources > 0) */


/*-+--------------------------------------------------------------------------
 / osSysKillSemaphoreList
 / Funktion:
 /   - releases semaphore SemaID and all semaphores locked by the same task
 /
 / Attention: function must be called with interrupts disabled!  
 /
 / Parameter: ResId : SemaID semaphore to be released
 / Returnvalue:
 /--------------------------------------------------------------------------*/
#if (osdNumberOfSemaphores > 0)
 #if (!defined(osdGetSemaphoreNotUsed)) || (!defined(osdReleaseSemaphoreNotUsed))
static osqFunc1 void osqFunc2 osSysKillSemaphoreList(TaskType taskID);
static osqFunc1 void osqFunc2 osSysKillSemaphoreList(TaskType taskID)
{
   /* CovComment 4:  Function: osSysKillSemaphoreList */
   TaskType taskIndex;
   osSemaphoreType semaID;
   COVER(0x0039)
   
   IFCOVER( 0>=osdNumberOfSemaphores,0x00EE,0x00EF)
   for (semaID= 0; semaID < osdNumberOfSemaphores; semaID++)
   {
      if (osSemaOwner[semaID] == taskID)
      {
         COVER(0x003A)
         /* now check if a task is waiting */
         osSemaphoreState[semaID] = 1;
         IFCOVER( 0>=osrNumberOfExtendedTasks,0x00F0,0x00F1)
         for (taskIndex= 0; taskIndex < osrNumberOfExtendedTasks; taskIndex++)
         {
            if (osTcbTaskState[taskIndex] == WAIT_SEMAPHORE)
            {
               if (osTcbWaitForSemaphore[taskIndex] == semaID)
               {
                  /* this is the highest priority task waiting for this sema */
                  osTcbTaskState[taskIndex] = READY;
                  /* semaphore stays occupied */
                  osSemaphoreState[semaID] = 0;
                  osSemaOwner[semaID] = taskIndex;

                  osSchedInsertTask(taskIndex);

                  break;
               }
               ELSEWITHCOVER(0x003B)
            }
            ELSEWITHCOVER(0x003C)
            IFCOVER( (taskIndex+1) < osrNumberOfExtendedTasks,0x00F2,0x00F3)
         } /* for (taskIndex= 0; taskIndex < osrNumberOfExtendedTasks; taskIndex++) */
      }
      IFCOVER( (ns+1) < osdNumberOfSemaphores,0x00F4,0x00F5)
   } /* for (ns= 0; ns < osdNumberOfSemaphores; ns++) */
   COVER(0x003D)
}
 #endif /* (!defined(osdGetSemaphoreNotUsed)) || (!defined(osdReleaseSemaphoreNotUsed)) */
#endif /* (osdNumberOfSemaphores > 0) */


#if (osdNumberOfAllTasks > 0)
/*-+--------------------------------------------------------------------------
 / osSysKillRunningTask
 / Function:
 /   - kills task and releases all resources locked by the task
 /   - only current activation is killed, future activations remain valid.
 /   - only allowed for RUNNING tasks
 /     - use osSysKillPreemptedTask for preempted tasks
 /     - PRE_READY tasks do not need any additional killing function. Only the activation
 /       is to be deleted, which can be done in osSysKillApplication directly.
 /   - must be called with interrupts disabled and local core's lock occupied!
 /
 / Parameter:   issueError : osdTRUE:  Automatic task termination (missing TerminateTask),
 /                                     function calls the ErrorHook.
 /                           osdFALSE: Running Task terminated due to protection error
 /                                     or TerminateApplication. No ErrorHook call.
 / Returnvalue: void
 /--------------------------------------------------------------------------*/

osqFunc1 void osqFunc2 osSysKillRunningTask(osbool issueError)
{
   /* CovComment 4:  Function: osSysKillRunningTask */
   TaskType taskID = osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex;

   COVER(0x003E)
   if (issueError == osdTRUE)
   {
      COVER(0x003F)
      osAPIError(E_OS_MISSINGEND, osdErrMTMissingTerminateTask);
   }
#if (osdErrorHook!=0)
   else
   {
      COVER(0x0040)
      /* Reset osOwnCcb->LockIsNotNeeded.ossErrorFlag, task might be killed in ErrorHook */
      osOwnCcb->LockIsNotNeeded.ossErrorFlag = osdFALSE;
   }
#else
   ELSEWITHCOVER(0x0041)
#endif

#if (STATUS_LEVEL == EXTENDED_STATUS)
   COVER(0x0042)
   /* must be reset before PostTaskHook to avoid IntAPI errors inside hook */
   COVER(0x0043)
   osOwnCcb->LockIsNotNeeded.ossIntAPIStatus = 0;
#endif

#if osdPostTaskHook
   if (issueError == osdTRUE)
   {
      COVER(0x0044)
      /* call PostTaskHook before clearing osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex! */
      osPostTaskHook();
   }
   ELSEWITHCOVER(0x0045)
#endif


#if ( (osdNumberOfInternalResources > 0) && ((CC == ECC2) || (CC == BCC2)) )
   if (oskResInternalCeilingPrioMask[taskID] != 0)
   {
      COVER(0x0046)
      osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio = oskTcbHomePrio[taskID];
   }
   ELSEWITHCOVER(0x0047)
#endif /* osdNumberOfInternalResources > 0 */


#if (osdNumberOfAllResources > 0)
 #if (!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed))
   if (osTcbLockedResource[taskID] != osdNoResource)
   {
      COVER(0x0048)
      osSysKillResourceList(osTcbLockedResource[taskID]);
   }
   ELSEWITHCOVER(0x0049)
 #endif /* (!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed)) */
#endif /* (osdNumberOfAllResources > 0) */

#if (osdNumberOfSemaphores > 0)
 #if (!defined(osdGetSemaphoreNotUsed)) || (!defined(osdReleaseSemaphoreNotUsed))
   if (taskID < osdNumberOfExtendedTasks)
   {
      COVER(0x004A)
      osSysKillSemaphoreList(taskID);
   }
   ELSEWITHCOVER(0x004B)
 #endif /* (!defined(osdGetSemaphoreNotUsed)) || (!defined(osdReleaseSemaphoreNotUsed)) */
#endif /* (osdNumberOfSemaphores > 0) */

#if STATUS_LEVEL == EXTENDED_STATUS
 #if (osdNumberOfInternalResources > 0) || (osdNumberOfInterruptResources > 0)
   COVER(0x004C)
   osTcbResourceCounter[taskID] = 0;
 #endif
#endif
#if osdORTIDebug
   COVER(0x004D)
   osTcbActualPrio[taskID] = oskTcbHomePrio[taskID];
   osTcbORTIServiceId[taskID] = osdORTINoService;
#endif
   osTcbLockedResource[taskID] = osdNoResource;

#if ((CC == ECC2) || (CC == BCC2))
   osTcbActivationCount[taskID]--;
   if (osTcbActivationCount[taskID] != 0)
   {  
      COVER(0x004E)
      osTcbTaskState[taskID] = PRE_READY;
   }
   else
   {
      COVER(0x004F)
      osTcbTaskState[taskID] = SUSPENDED;
   }
#else
   COVER(0x0050)
   osTcbTaskState[taskID] = SUSPENDED;
#endif

   osSchedRemoveRunningTask();

   #if osdMixedPreempt
   if (osConfigBlock.aucTaskPreemptive[taskID] == osdTaskTypeNonPreempt)
   {   
      COVER(0x0051)
      osOwnCcb->LockIsNotNeeded.ossLockDispatcher--; 
   } 
   ELSEWITHCOVER(0x0052)
   #endif

   /* KB begin osekHWosKillRunnigTaskSpecialActionsSrc (default) */
   /* KB end osekHWosKillRunnigTaskSpecialActionsSrc */

   osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex = osdNoActiveTask;
   osOwnCcb->LockIsNotNeeded.ossActiveTaskPrio  = osdNoActivePrio;
} /* END OF osSysKillRunningTask */
#endif /* (osdNumberOfAllTasks > 0) */


/*-+--------------------------------------------------------------------------
 / osSysKillPreemptedTask
 / Funktion:
 /   - kills task and releases all resources locked by the task
 /   - activation counter is reset, and task is left in SUSPENDED state
 /   - only allowed for preempted tasks (READY, WAITING or WAIT_SEMAPHORE)
 /     - use osSysKillRunningTask to kill the running Task
 /     - PRE_READY tasks do not need any additional killing function. Only the activation
 /       is to be deleted, which can be done in osSysKillApplication directly.
 /   - must be called with interrupts disabled and local core's lock occupied!
 /
 / Parameter:     taskID : task to be killed
 / Returnvalue:   void
 /--------------------------------------------------------------------------*/

#if ((osdNumberOfAllTasks > 0) && (osdNumberOfApplications > 0))
#if (((osdSC == SC3) || (osdSC == SC4)) && (osdProtReactKillApplAllowed || osdProtReactKillApplRestAllowed || !defined osdTerminateApplicationNotUsed))
osqFunc1 void osqFunc2 osSysKillPreemptedTask(TaskType taskID)
{
   /* CovComment 4:  Function: osSysKillPreemptedTask */

   COVER(0x0053)


#if (osdNumberOfAllResources > 0)
 #if (!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed))
   if (osTcbLockedResource[taskID] != osdNoResource)
   {
      COVER(0x0054)
      osSysKillResourceList(osTcbLockedResource[taskID]);
   }
   ELSEWITHCOVER(0x0055)
 #endif /* (!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed)) */
#endif /* (osdNumberOfAllResources > 0) */

#if (osdNumberOfSemaphores > 0)
 #if (!defined(osdGetSemaphoreNotUsed)) || (!defined(osdReleaseSemaphoreNotUsed))
   if (taskID < osdNumberOfExtendedTasks)
   {
      COVER(0x0056)
      osSysKillSemaphoreList(taskID);
   }
   ELSEWITHCOVER(0x0057)
 #endif /* (!defined(osdGetSemaphoreNotUsed)) || (!defined(osdReleaseSemaphoreNotUsed)) */
#endif /* (osdNumberOfSemaphores > 0) */

#if STATUS_LEVEL == EXTENDED_STATUS
 #if (osdNumberOfInternalResources > 0) || (osdNumberOfInterruptResources > 0)
   COVER(0x0058)
   osTcbResourceCounter[taskID] = 0;
 #endif
#endif
#if osdORTIDebug
   COVER(0x0059)
   osTcbActualPrio[taskID] = oskTcbHomePrio[taskID];
   osTcbORTIServiceId[taskID] = osdORTINoService;
#endif
   osTcbLockedResource[taskID] = osdNoResource;

#if ((CC == ECC2) || (CC == BCC2))
   COVER(0x005A)
   osTcbActivationCount[taskID] = 0;
#endif
   osTcbTaskState[taskID] = SUSPENDED;
} /* END OF osSysKillPreemptedTask */
#endif /* (((osdSC == SC3) || (osdSC == SC4)) && (osdProtReactKillApplAllowed || osdProtReactKillApplRestAllowed || !defined osdTerminateApplicationNotUsed)) */
#endif /* ((osdNumberOfAllTasks > 0) && (osdNumberOfApplications > 0)) */

#endif /* (osdKillTaskIsrPossible || (osdSC== SC3) || (osdSC== SC4)) */

#if (STATUS_LEVEL == EXTENDED_STATUS)
 #if (osdNumberOfAllTasks > 0)
/* KB begin osekHWosCheckInterruptsEnabledSrc (overwritten) */
/* KB end osekHWosCheckInterruptsEnabledSrc */
 #endif

 #if osdEnableAssertions
/* KB begin osekHWosCheckInterruptsDisabledSrc (overwritten) */
/* KB end osekHWosCheckInterruptsDisabledSrc */
 #endif
#endif

/* KB begin osekHWosDisableLevelSrc (overwritten) */
/* KB end osekHWosDisableLevelSrc */

/* KB begin osekHWosEnableLevelSrc (overwritten) */
/* KB end osekHWosEnableLevelSrc */

/* KB begin osekHWosSetAlarmLevelSrc (overwritten) */
/* KB end osekHWosSetAlarmLevelSrc */

/* KB begin osekHWosSaveDisableLevelSrc (overwritten) */
/* KB end osekHWosSaveDisableLevelSrc */

/* KB begin osekHWosRestoreEnableLevelSrc (overwritten) */
/* KB end osekHWosRestoreEnableLevelSrc */

/* KB begin osekHWosDisableGlobalSrc (overwritten) */
/* KB end osekHWosDisableGlobalSrc */

/* KB begin osekHWosEnableGlobalSrc (overwritten) */
/* KB end osekHWosEnableGlobalSrc */

/* KB begin osekHWosSaveDisableLevelNestedSrc (default) */
/*-+--------------------------------------------------------------------------
 / osSaveDisableLevelNested
 / Funktion: save level and disable up to system level, nested
 /           similar to API function SuspendOSInterrupts but used in the OS only
 /   - 
 / Parameter:
 / Returnvalue:
 /--------------------------------------------------------------------------*/
/* MISRA RULE 14.1 VIOLATION: The function is osSaveDisableLevelNested is used in 
 * many different functions in the OS. Anyhow, dependend on the configuration, 
 * the function is unused in rare cases. Provision of this function only in the 
 * cases where it is necessary, would increase code complexity too much. (1503) */
osqFunc1 void osqFunc2 osSaveDisableLevelNested(void)    /* PRQA S 1503 */ 
{
   /* CovComment 4:  Function: osSaveDisableLevelNested */
   /* KB begin osekHWosSaveDisableLevelNestedBody (overwritten) */
   COVER(0x005B)
   if (ptrToCcb2->ossIntSaveDisableCounter < 63U)
   {
      COVER(0x005C)   
      if (ptrToCcb2->ossIntSaveDisableCounter == 0) 
      {
         COVER(0x005D)      
         ptrToCcb2->ossSavedIntLevelNested = osGetDisableLevel();
      }  
      ELSEWITHCOVER(0x005E)
      ptrToCcb2->ossIntSaveDisableCounter++;           
   }
   else
   {
      COVER(0x005F)      
      osEnterSafeState(E_OS_SYS_ASSERTION, osdErrSDWrongCounter);
   }
   /* KB end osekHWosSaveDisableLevelNestedBody */
}
/* KB end osekHWosSaveDisableLevelNestedSrc */

/* KB begin osekHWosRestoreEnableLevelNestedSrc (default) */
/*-+--------------------------------------------------------------------------
 / osRestoreEnableLevelNested
 / Funktion: restore level saved by osSaveDisableLevelNested
 /           similar to API function ResumeOSInterrupts but used in the OS only
 /   - 
 / Parameter:
 / Returnvalue:
 /--------------------------------------------------------------------------*/
/* MISRA RULE 14.1 VIOLATION: The function is osRestoreEnableLevelNested is used in 
 * many different functions in the OS. Anyhow, dependend on the configuration, 
 * the function is unused in rare cases. Provision of this function only in the 
 * cases where it is necessary, would increase code complexity too much. (1503) */
osqFunc1 void osqFunc2 osRestoreEnableLevelNested(void)    /* PRQA S 1503 */ 
{
   /* CovComment 4:  Function: osRestoreEnableLevelNested */
   /* KB begin osekHWosRestoreEnableLevelNestedBody (overwritten) */
   COVER(0x0060)
   if (ptrToCcb2->ossIntSaveDisableCounter != 0)
   {
      COVER(0x0061)
      ptrToCcb2->ossIntSaveDisableCounter--;   
      if (ptrToCcb2->ossIntSaveDisableCounter == 0)
      {
         COVER(0x0062)
         osRestoreLevelNested();
      } 
      ELSEWITHCOVER(0x0063)
   }
   else
   {
      COVER(0x0064)
      osEnterSafeState(E_OS_SYS_ASSERTION, osdErrREWrongCounter);      
   }
   /* KB end osekHWosRestoreEnableLevelNestedBody */
}
/* KB end osekHWosRestoreEnableLevelNestedSrc */

/* KB begin osekHWosSaveDisableGlobalNestedSrc (overwritten) */
/* KB end osekHWosSaveDisableGlobalNestedSrc */

/* KB begin osekHWosRestoreEnableGlobalNestedSrc (overwritten) */
/* KB end osekHWosRestoreEnableGlobalNestedSrc */

/* KB begin MicrosarOsThreadSwitchHookCall (default) */
#if osdCallTimingHooks

osqRAM0 osqRAM1 osqRAM2 osuint8 osqRAM3  osNextRunReason[osdNumberOfAllTasks];

/* CovComment 4:  Macro: OS_VTH_CALL_SCHEDULE_HOOK */
#define OS_VTH_CALL_SCHEDULE_HOOK(LastActiveTask, ActiveTask, NextTask) \
   {                                                                    \
      osProcessType FromTask;                                           \
      osuint8 FromTaskReason;                                           \
      osuint8 ToTaskReason;                                             \
      CoreIdType CoreId = 0;                                            \
      if((ActiveTask) == osdNoActiveTask)                               \
      {                                                                 \
         FromTask = (osProcessType) (LastActiveTask);                   \
         if((LastActiveTask) == osdNoActiveTask)                        \
         {                                                              \
            /* Idle Loop is always preempted */                         \
            FromTaskReason = (OS_VTHP_THREAD_PREEMPT);                  \
            /* No change of osNextRunReason[] necessary here */         \
            COVER(0x0065)                                                     \
         }                                                              \
         else                                                           \
         {                                                              \
            FromTaskReason = (OS_VTHP_TASK_TERMINATION);                \
            osNextRunReason[FromTask] = FromTaskReason |                \
                                        (OS_VTHP_MODIFY_FROM_TO_REASON);\
            COVER(0x0066)                                                     \
         }                                                              \
      }                                                                 \
      else                                                              \
      {                                                                 \
         FromTask = (osProcessType) (ActiveTask);                       \
         if( osTcbTaskState[FromTask] == WAITING)                       \
         {                                                              \
            FromTaskReason = (OS_VTHP_TASK_WAITEVENT);                  \
            osNextRunReason[FromTask] = FromTaskReason |                \
                                        (OS_VTHP_MODIFY_FROM_TO_REASON);\
            COVER(0x0067)                                                     \
         }                                                              \
         else if (osTcbTaskState[FromTask] == WAIT_SEMAPHORE)           \
         {                                                              \
            FromTaskReason = (OS_VTHP_TASK_WAITSEMA);                   \
            osNextRunReason[FromTask] = FromTaskReason |                \
                                        (OS_VTHP_MODIFY_FROM_TO_REASON);\
            COVER(0x0068)                                                     \
         }                                                              \
         else                                                           \
         {                                                              \
            FromTaskReason = (OS_VTHP_THREAD_PREEMPT);                  \
            osNextRunReason[FromTask] = FromTaskReason |                \
                                        (OS_VTHP_MODIFY_FROM_TO_REASON);\
            COVER(0x0069)                                                     \
         }                                                              \
      }                                                                 \
      if ((NextTask) == osdNoActiveTask)                                \
      {                                                                 \
         /* idle loop always resumes */                                 \
         ToTaskReason = (OS_VTHP_THREAD_RESUME);                        \
         COVER(0x006A)                                                        \
      }                                                                 \
      else                                                              \
      {                                                                 \
         ToTaskReason = osNextRunReason[(NextTask)];                    \
         COVER(0x006B)                                                        \
      }                                                                 \
      OS_VTH_SCHEDULE( ((osProcessType) FromTask),                      \
                       ((osuint8) FromTaskReason),                      \
                       ((osProcessType) (NextTask)),                    \
                       ((osuint8) ToTaskReason)  ,                      \
                       ((CoreIdType) CoreId)     )                      \
   }
#else /*osdCallTimingHooks*/

/* empty definition if no timing hooks configured */
#define OS_VTH_CALL_SCHEDULE_HOOK(LastActiveTask, ActiveTask, NextTask) \
   COVER(0x006C)

#endif /*osdCallTimingHooks*/
/* KB end MicrosarOsThreadSwitchHookCall */

/* KB begin osekHWosDispatcherSrc (overwritten) */

/*****************************************************************************
  osIdleLoop
  Description: called when no active task is running
  Parameter: -
  ReturnValue: -
*****************************************************************************/
static osqFunc1 void osqFunc2 osIdleLoop(void);
static osqFunc1 void osqFunc2 osIdleLoop(void)
{
   /* CovComment 4:  Function: osIdleLoop */
   COVER(0x006D)
   OS_IDLE_ENTRY();
   for(;;)
   {
      COVER(0x006E)
      #if (osdNonPreempt != 0)
      if (osOwnCcb->LockIsNeeded.ossStartDispatcher != 0U)
      {
         ptrToCcb2->ossCallDispatcher = 1;
         osDispatch();
         COVER(0x006F)
      }
      ELSEWITHCOVER(0x0070)
      #endif
      
      OS_IDLE_PROC()
   }
}

/*-+--------------------------------------------------------------------------
/ osDispatcher
/ Description: run into idle loop or start new task or resume preempted task
/ Parameter: stack pointer of current active task
/ Returnvalue: stack pointer for preempted task to be resumed
/--------------------------------------------------------------------------*/
/* MISRA RULE 8.8 VIOLATION: The function osDispatcher is called from assembly language.
   Declaring the function static causes assembler errors (3408). */
/* MISRA RULE 14.1 not violated: The function osDispatcher is called from assembly language.
   MISRA checking tools do not see the call and complain about it. */ 
osqFunc1 osStackPtrType osqFunc2 osDispatcher(osStackPtrType stackPtr) /* PRQA S 3408 */ /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osDispatcher */
   TaskType taskIndex;
   COVER(0x0071)
   
   
   ptrToCcb2->ossCallDispatcher = 0;
   ptrToCcb->ossStartDispatcher = osdFALSE;

   #if (osdNumberOfAllTasks > 0)
   taskIndex = ptrToCcb2->ossActiveTaskIndex;
   if (taskIndex < osdNumberOfAllTasks)
   {
      COVER(0x0072)
      if (osTcbTaskState[taskIndex] == RUNNING)      
      {
         COVER(0x0073)
         #if (osdPostTaskHook == 1)
         osPostTaskHook();         
         #endif
         osTcbTaskState[taskIndex] = READY;         
      }    
      ELSEWITHCOVER(0x0074)
      osTcbSP[taskIndex] = stackPtr;
      #if osdORTIDebug
      osTcbORTIServiceId[taskIndex] = ptrToCcb2->ossORTICurrentServiceId;
      #endif      
   }
   ELSEWITHCOVER(0x0075)
   #endif   
   taskIndex = ptrToCcb->ossHighReadyTaskIndex;
   OS_VTH_CALL_SCHEDULE_HOOK(ptrToCcb2->ossLastActiveTaskIndex, ptrToCcb2->ossActiveTaskIndex, taskIndex);
   ptrToCcb2->ossActiveTaskIndex = taskIndex;
   if (taskIndex == osdNoActiveTask)
   {
      COVER(0x0076)
      ptrToCcb2->ossActiveTaskPrio = ptrToCcb->ossHighReadyTaskPrio;
      #if osdORTIDebug
      ptrToCcb2->ossORTICurrentServiceId = osdORTINoService;
      #endif      
      #if (osdFullPreempt || osdMixedPreempt)      
      ptrToCcb2->ossLockDispatcher = osdFALSE;
      #endif         
      osStartTrustedTask((osuint32)osConfigBlock.SystemStack[osSysGetCoreID()].start,
                         (osuint32)osConfigBlock.SystemStack[osSysGetCoreID()].end,
                         (osTaskFctType)osIdleLoop);
      return (osStackPtrType)0; /* must never be reached! */
   }
   else
   {
      COVER(0x0077)
      osSchedOccupyInternalResource();    
      ptrToCcb2->ossActiveTaskPrio = ptrToCcb->ossHighReadyTaskPrio;
      #if (osdStackCheck || osdCallTimingHooks)
      ptrToCcb2->ossLastActiveTaskIndex = taskIndex;
      #endif      
      #if (osdFullPreempt || osdMixedPreempt)
      if(osConfigBlock.aucTaskPreemptive[taskIndex] == osdTaskTypePreempt)
      {
         COVER(0x0078)      
         ptrToCcb2->ossLockDispatcher = osdFALSE;
      }
      else
      {
         COVER(0x0079)      
         ptrToCcb2->ossLockDispatcher = osdTRUE;
      }
      #endif
   
      if (osTcbTaskState[taskIndex] == PRE_READY)
      {
         COVER(0x007A)
         osTcbTaskState[taskIndex] = RUNNING;      
         #if osdORTIDebug
         ptrToCcb2->ossORTICurrentServiceId = osdORTINoService;
         #endif         
         #if (osdPreTaskHook == 1)
         osPreTaskHook();
         #endif
         {
            COVER(0x007B)
            osStartTrustedTask((osuint32)osConfigBlock.aulTaskStackStartAddress[taskIndex],
                               (osuint32)osConfigBlock.aulTaskStackEndAddress[taskIndex],
                               (osTaskFctType)osConfigBlock.aulTaskStartAddress[taskIndex]);
         }
      }
      else
      {
         COVER(0x007C)
         osTcbTaskState[taskIndex] = RUNNING;
         #if osdORTIDebug
         ptrToCcb2->ossORTICurrentServiceId = osTcbORTIServiceId[taskIndex];
         #endif
         #if (osdPreTaskHook == 1)
         osPreTaskHook();
         #endif
      } 
      COVER(0x007D)                 
      return (osStackPtrType)osTcbSP[taskIndex];
   }   
} /* END OF osDispatcher */
/* KB end osekHWosDispatcherSrc */

/* KB begin osekHWAdditionalAPIFunctions (overwritten) */
/* MISRA RULE 14.1 VIOLATION: osGetConfigBlockVersion is an API function which might be unused. */
osqFunc1 osuint16 osqFunc2 osGetConfigBlockVersion(void) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osGetConfigBlockVersion */
   COVER(0x007E)
   return osConfigBlock.uiUserConfigVersion;
}


#if (osdNumberOfCat2ISRs > 0)
/*****************************************************************************
  osCallCat2ISR
  Description: called by ISR prologue if CAT2 ISR has occured
  Parameter: ISRID = index of CAT2 ISR 
             ISRAddr = address of the CAT2 ISR to be started
  ReturnValue: Request for dispatcher start
*****************************************************************************/
/* MISRA RULE 14.1 not violated: The function osCallCat2ISR is called from assembler code.
   MISRA checking tools do not see the call and complain about it. */
osqFunc1 osuint32 osqFunc2 osCallCat2ISR(ISRType ISRID) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osCallCat2ISR */
   ISRType SavedIsrId;
   osuint32 retVal;
   osuint32 newPSW;
   #if osdORTIDebug
   osuint8 SavedORTIServiceId;
   #endif

   COVER(0x007F)
   osSysErrAssert((ISRID < osdNumberOfCat2ISRs), osdErrCIInvalidIsrIndex)
   retVal = 0;   
      SavedIsrId = ptrToCcb2->ossActiveISRID;
      ptrToCcb2->ossActiveISRID = ISRID;

   
      #if osdORTIDebug
      SavedORTIServiceId = ptrToCcb2->ossORTICurrentServiceId;
      ptrToCcb2->ossORTICurrentServiceId = osdORTINoService;
      #endif
      
      ptrToCcb2->ossIntNestingDepth++;                           
      #if (osdFullPreempt || osdMixedPreempt)
      ptrToCcb2->ossLockDispatcher++;        
      #endif
      #if osdCallTimingHooks
      if(ptrToCcb2->ossIntNestingDepth == 1)
      {  /* interrupted process is a task */         
         COVER(0x0080)
         OS_VTH_SCHEDULE(osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex, OS_VTHP_THREAD_PREEMPT, (osdNumberOfAllTasks + ISRID), OS_VTHP_ISR_START, GetCoreID());
      }
      else
      {  /* interrupted process is an ISR */      
         COVER(0x0081)
         OS_VTH_SCHEDULE((osdNumberOfAllTasks+SavedIsrId), OS_VTHP_THREAD_PREEMPT, (osdNumberOfAllTasks + ISRID), OS_VTHP_ISR_START, GetCoreID());      
      }
      #endif            
   
      newPSW = osGetPSW(); /* CPU is in supervisor mode and interrupts are disabled */            
      if(osConfigBlock.IsrNestable[ISRID] != 0)      
      {
         COVER(0x0082)
         newPSW &= (osuint32)0xFFFFFFDFUL;      
      }
      ELSEWITHCOVER(0x0083)
      {
         COVER(0x0084)
         osStartTrustedISR((osuint32)osConfigBlock.cat2IsrStartAddress[ISRID], (osuint32)newPSW);
      }
      #if osdCallTimingHooks
      if(ptrToCcb2->ossIntNestingDepth == 1)
      {  /* interrupted process is a task */ 
         COVER(0x0085)     
         OS_VTH_SCHEDULE((osdNumberOfAllTasks+ISRID), OS_VTHP_ISR_END, osOwnCcb->LockIsNotNeeded.ossActiveTaskIndex, OS_VTHP_THREAD_RESUME, GetCoreID());
      }
      else
      {  /* interrupted process is an ISR */      
         COVER(0x0086)
         OS_VTH_SCHEDULE((osdNumberOfAllTasks+ISRID), OS_VTHP_ISR_END, (osdNumberOfAllTasks+SavedIsrId), OS_VTHP_THREAD_RESUME, GetCoreID());           
      }
      #endif
      #if (osdFullPreempt || osdMixedPreempt)
      ptrToCcb2->ossLockDispatcher--;
      #endif
      ptrToCcb2->ossIntNestingDepth--;

      ptrToCcb2->ossActiveISRID = SavedIsrId;
      #if osdORTIDebug
      ptrToCcb2->ossORTICurrentServiceId = SavedORTIServiceId;
      #endif

      #if ((STATUS_LEVEL == EXTENDED_STATUS) && (osdEnableAssertions == 1))
      if (ptrToCcb2->ossIntAPIStatus != 0)
      {
         COVER(0x0087)
         osEnterSafeState(E_OS_DISABLEDINT, osdErrIXIntAPIDisabled);
      }
      ELSEWITHCOVER(0x0088)
      #endif

      #if (osdFullPreempt || osdMixedPreempt)
      COVER(0x0089)
      if(ptrToCcb->ossStartDispatcher == osdTRUE)
      {
         COVER(0x008A)
         if(ptrToCcb2->ossLockDispatcher == osdFALSE)
         {
            COVER(0x008B)         
            retVal = 1; /* request for dispatcher start */
         }
         ELSEWITHCOVER(0x008C)
      }
      ELSEWITHCOVER(0x008D)
      #endif
   return retVal; /* return normal */
}
#endif /* osdNumberOfCat2ISRs > 0 */

/* KB end osekHWAdditionalAPIFunctions */


/* KB begin osekHWdelayTilEnableTookEffectSrc (default) */
/* KB end osekHWdelayTilEnableTookEffectSrc */


   



#ifndef osdEnableAllInterruptsNotUsed
/* KB begin osekEnableAllInterrupts (default) */
/*-+--------------------------------------------------------------------------
 / osEnableAllInterrupts
 / Function:    implementation of API function EnableAllInterrupts
 / Parameter:   void
 / Returnvalue: void
 /--------------------------------------------------------------------------*/
/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/EnableAllInterrupts
 */
osqFunc1 void osqFunc2 osEnableAllInterrupts(void)
{ 
   /* CovComment 4:  Function: osEnableAllInterrupts */
   OS_EA_ENTRY()
   COVER(0x008E)
   osSysErrAssert(osOwnCcb->LockIsNotNeeded.ossIntAPIStatus==osdIntAPIDisableAll,osdErrEAIntAPIWrongSequence)
#if ((osdEnableAssertions == 0) && (STATUS_LEVEL == EXTENDED_STATUS))
   if (osOwnCcb->LockIsNotNeeded.ossIntAPIStatus!=osdIntAPIDisableAll)
   {
      COVER(0x008F)
      OS_EA_EXIT()
      return;
   }
   ELSEWITHCOVER(0x0090)
#endif
   OS_VTH_CALL_ENABLEDINT_HOOK(OS_VTHP_ALLINTERRUPTS)
   osSetIntAPIStatus(0);
   /* KB begin osekHWosRestoreEnableGlobalBody (overwritten) */
   if(ptrToCcb2->ossSavedIntDisFlag == 0)
   {
      COVER(0x0091)
      osEnableGlobal();
   }      
   ELSEWITHCOVER(0x0092)
   /* KB end osekHWosRestoreEnableGlobalBody */
   OS_EA_EXIT()
}
/* KB end osekEnableAllInterrupts */
#endif


#ifndef osdDisableAllInterruptsNotUsed
/* KB begin osekDisableAllInterrupts (default) */
/*-+--------------------------------------------------------------------------
 / osDisableAllInterrupts
 / Function:    implementation of API function DisableAllInterrupts
 / Parameter:   void
 / Returnvalue: void
 /--------------------------------------------------------------------------*/
/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/DisableAllInterrupts
 */
osqFunc1 void osqFunc2 osDisableAllInterrupts(void)
{
   /* CovComment 4:  Function: osDisableAllInterrupts */
   OS_DA_ENTRY()
   COVER(0x0093)
   osSysErrAssert(!osOwnCcb->LockIsNotNeeded.ossIntAPIStatus,osdErrDAIntAPIDisabled)
#if ((osdEnableAssertions == 0) && (STATUS_LEVEL == EXTENDED_STATUS))
   if (osOwnCcb->LockIsNotNeeded.ossIntAPIStatus!=0)
   {
      COVER(0x0094)
      OS_DA_EXIT()
      return;
   }
   ELSEWITHCOVER(0x0095)
#endif
   /* KB begin osekHWosSaveDisableGlobalBody (overwritten) */
   ptrToCcb2->ossSavedIntDisFlag = osGetDisableGlobal();      
   /* KB end osekHWosSaveDisableGlobalBody */
   osSetIntAPIStatus(osdIntAPIDisableAll);
   OS_VTH_CALL_DISABLEDINT_HOOK(OS_VTHP_ALLINTERRUPTS)
   OS_DA_EXIT()
}
/* KB end osekDisableAllInterrupts */
#endif


#ifndef osdResumeOSInterruptsNotUsed
/* KB begin osekResumeOSInterrupts (default) */
/*-+--------------------------------------------------------------------------
 / osResumeOSInterrupts
 / Function:    implementation of API function ResumeOSInterrupts
 / Parameter:   void
 / Returnvalue: void
 /--------------------------------------------------------------------------*/
/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/ResumeOSInterrupts
 */
osqFunc1 void osqFunc2 osResumeOSInterrupts(void)
{
   /* CovComment 4:  Function: osResumeOSInterrupts */
   OS_RI_ENTRY()
   COVER(0x0096)
#if (osdEnableAssertions == 0)
   if (osOwnCcb->LockIsNotNeeded.ossIntSaveDisableCounter==0)
   {
      COVER(0x0097)
      OS_RI_EXIT()
      return;
   }
   ELSEWITHCOVER(0x0098)
#endif
   
   osDecIntAPIStatus();

#if osdCallTimingHooks
   if (osOwnCcb->LockIsNotNeeded.ossIntSaveDisableCounter == 1)
   {
      COVER(0x0099)
      OS_VTH_CALL_ENABLEDINT_HOOK(OS_VTHP_CAT2INTERRUPTS)
   }
   ELSEWITHCOVER(0x009A)
#endif

   /* KB begin osekHWosRestoreEnableLevelNestedBody (overwritten) */
   COVER(0x009B)
   if (ptrToCcb2->ossIntSaveDisableCounter != 0)
   {
      COVER(0x009C)
      ptrToCcb2->ossIntSaveDisableCounter--;   
      if (ptrToCcb2->ossIntSaveDisableCounter == 0)
      {
         COVER(0x009D)
         osRestoreLevelNested();
      } 
      ELSEWITHCOVER(0x009E)
   }
   else
   {
      COVER(0x009F)
      osEnterSafeState(E_OS_SYS_ASSERTION, osdErrREWrongCounter);      
   }
   /* KB end osekHWosRestoreEnableLevelNestedBody */
   OS_RI_EXIT()
}
/* KB end osekResumeOSInterrupts */
#endif


#ifndef osdSuspendOSInterruptsNotUsed
/* KB begin osekSuspendOSInterrupts (default) */
/*-+--------------------------------------------------------------------------
 / osSuspendOSInterrupts
 / Function:    implementation of API function SuspendOSInterrupts
 / Parameter:   void
 / Returnvalue: void
 /--------------------------------------------------------------------------*/
/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/SuspendOSInterrupts
 */
osqFunc1 void osqFunc2 osSuspendOSInterrupts(void)
{
   /* CovComment 4:  Function: osSuspendOSInterrupts */
   OS_SI_ENTRY()
   COVER(0x00A0)
#if (osdEnableAssertions == 0)
   if (osOwnCcb->LockIsNotNeeded.ossIntSaveDisableCounter==255)
   {
      COVER(0x00A1)
      OS_SI_EXIT()
      return;
   }
   ELSEWITHCOVER(0x00A2)
#endif
   /* KB begin osekHWosSaveDisableLevelNestedBody (overwritten) */
   COVER(0x00A3)
   if (ptrToCcb2->ossIntSaveDisableCounter < 63U)
   {
      COVER(0x00A4)   
      if (ptrToCcb2->ossIntSaveDisableCounter == 0) 
      {
         COVER(0x00A5)      
         ptrToCcb2->ossSavedIntLevelNested = osGetDisableLevel();
      }  
      ELSEWITHCOVER(0x00A6)
      ptrToCcb2->ossIntSaveDisableCounter++;           
   }
   else
   {
      COVER(0x00A7)      
      osEnterSafeState(E_OS_SYS_ASSERTION, osdErrSDWrongCounter);
   }
   /* KB end osekHWosSaveDisableLevelNestedBody */
#if osdCallTimingHooks
   if (osOwnCcb->LockIsNotNeeded.ossIntSaveDisableCounter == 1)
   {
      COVER(0x00A8)
      OS_VTH_CALL_DISABLEDINT_HOOK(OS_VTHP_CAT2INTERRUPTS)
   }
   ELSEWITHCOVER(0x00A9)
#endif
   osIncIntAPIStatus();
   OS_SI_EXIT()
}
/* KB end osekSuspendOSInterrupts */
#endif


#ifndef osdResumeAllInterruptsNotUsed
/* KB begin osekResumeAllInterrupts (default) */
/*-+--------------------------------------------------------------------------
 / osResumeAllInterrupts
 / Function:    implementation of API function ResumeAllInterrupts
 / Parameter:   void
 / Returnvalue: void
 /--------------------------------------------------------------------------*/
/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/ResumeAllInterrupts
 */
osqFunc1 void osqFunc2 osResumeAllInterrupts(void)
{
   /* CovComment 4:  Function: osResumeAllInterrupts */
   OS_RA_ENTRY()
   COVER(0x00AA)
#if (osdEnableAssertions == 0)
#if osdTimingProtectionUsed
   if (osOwnCcb->LockIsNotNeeded.ossIntSaveDisableHighLevelCounter==0)
   {
      COVER(0x00AB)
      OS_RA_EXIT()
      return;
   }
   ELSEWITHCOVER(0x00AC)
#else /* osdTimingProtectionUsed */
   if (0==
       /* KB begin osekHWosIntSaveDisableGlobalCounterName (default) */
       osOwnCcb->LockIsNotNeeded.ossIntSaveDisableCounterGlobal
       /* KB end osekHWosIntSaveDisableGlobalCounterName */
      )
   {
      COVER(0x00AD)
      OS_RA_EXIT()
      return;
   }
   ELSEWITHCOVER(0x00AE)
#endif /*osdTimingProtectionUsed else*/
#endif /*osdEnableAssertions == 0*/

   osDecIntAPIStatus();

#if osdCallTimingHooks
   if (1 ==
       /* KB begin osekHWosIntSaveDisableGlobalCounterName (default) */
       osOwnCcb->LockIsNotNeeded.ossIntSaveDisableCounterGlobal
       /* KB end osekHWosIntSaveDisableGlobalCounterName */
      )/* first nesting level */
   {
      COVER(0x00AF)
      OS_VTH_CALL_ENABLEDINT_HOOK(OS_VTHP_ALLINTERRUPTS)
   }
   ELSEWITHCOVER(0x00B0)
#endif
   /* KB begin osekHWosRestoreEnableGlobalNestedBody (overwritten) */
   if (ptrToCcb2->ossIntSaveDisableCounterGlobal != 0)
   {
      COVER(0x00B1)
      ptrToCcb2->ossIntSaveDisableCounterGlobal--;   
      if (ptrToCcb2->ossIntSaveDisableCounterGlobal == 0)
      {
         COVER(0x00B2)      
         if(ptrToCcb2->ossSavedIntDisFlagNested == 0)
         {
            COVER(0x00B3)
            osEnableGlobal();
         }
         ELSEWITHCOVER(0x00B4)               
      } 
      ELSEWITHCOVER(0x00B5)                       
   }
   else
   {
      COVER(0x00B6)
      osEnterSafeState(E_OS_SYS_ASSERTION, osdErrRGWrongCounter);      
   }
   /* KB end osekHWosRestoreEnableGlobalNestedBody */

   OS_RA_EXIT()
}
/* KB end osekResumeAllInterrupts */
#endif


#ifndef osdSuspendAllInterruptsNotUsed
/* KB begin osekSuspendAllInterrupts (default) */
/*-+--------------------------------------------------------------------------
 / osSuspendAllInterrupts
 / Function:    implementation of API function SuspendAllInterrupts
 / Parameter:   void
 / Returnvalue: void
 /--------------------------------------------------------------------------*/
/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/SuspendAllInterrupts
 */
osqFunc1 void osqFunc2 osSuspendAllInterrupts(void)
{
   /* CovComment 4:  Function: osSuspendAllInterrupts */
   OS_PA_ENTRY()
   COVER(0x00B7)
#if (osdEnableAssertions == 0)
#if osdTimingProtectionUsed
   if (osOwnCcb->LockIsNotNeeded.ossIntSaveDisableHighLevelCounter==255)
   {
      COVER(0x00B8)
      OS_PA_EXIT()
      return;
   }
   ELSEWITHCOVER(0x00B9)
#else /* osdTimingProtectionUsed */
   if (255==
       /* KB begin osekHWosIntSaveDisableGlobalCounterName (default) */
       osOwnCcb->LockIsNotNeeded.ossIntSaveDisableCounterGlobal
       /* KB end osekHWosIntSaveDisableGlobalCounterName */
      )
   {
      COVER(0x00BA)
      OS_PA_EXIT()
      return;
   }
   ELSEWITHCOVER(0x00BB)
#endif /*osdTimingProtectionUsed else*/
#endif /*osdEnableAssertions == 0*/

   /* KB begin osekHWosSaveDisableGlobalNestedBody (overwritten) */
   if (ptrToCcb2->ossIntSaveDisableCounterGlobal < 63U)
   {
      COVER(0x00BC)   
      if (ptrToCcb2->ossIntSaveDisableCounterGlobal == 0) 
      {
         COVER(0x00BD)
         ptrToCcb2->ossSavedIntDisFlagNested = osGetDisableGlobal();
      }  
      ELSEWITHCOVER(0x00BE)
      ptrToCcb2->ossIntSaveDisableCounterGlobal++;           
   }
   else
   {
      COVER(0x00BF)      
      osEnterSafeState(E_OS_SYS_ASSERTION, osdErrSGWrongCounter);
   }
   /* KB end osekHWosSaveDisableGlobalNestedBody */
#if osdCallTimingHooks
   if (1 ==
       /* KB begin osekHWosIntSaveDisableGlobalCounterName (default) */
       osOwnCcb->LockIsNotNeeded.ossIntSaveDisableCounterGlobal
       /* KB end osekHWosIntSaveDisableGlobalCounterName */
      )/* first nesting level */
   {
      COVER(0x00C0)
      OS_VTH_CALL_DISABLEDINT_HOOK(OS_VTHP_ALLINTERRUPTS)
   }
   ELSEWITHCOVER(0x00C1)
#endif
   osIncIntAPIStatus();
   OS_PA_EXIT()
}
/* KB end osekSuspendAllInterrupts */
#endif


/* KB begin osekHWinterHooks (default) */
/* Hook routines */

#if osdSysErrorHook
void osInterErrorHook(StatusType Error)
{
   /* CovComment 4:  Function: osInterErrorHook */
   COVER(0x00C2)
   
 #if ((osdSC== SC3) || (osdSC== SC4))
   COVER(0x00C3)
   osOwnCcb->LockIsNotNeeded.ossInSystemFct++;
 #endif

   COVER(0x00C4)
   /* KB begin osekHWcallErrorHook (default) */
   //ErrorHook(Error);
   /* KB end osekHWcallErrorHook */

 #if ((osdSC== SC3) || (osdSC== SC4))
   COVER(0x00C5)
   osOwnCcb->LockIsNotNeeded.ossInSystemFct--;
 #endif
} /* END OF osInterErrorHook */
#endif /* osdSysErrorHook */

#if osdSysShutdownHook
static osqFunc1 void osqFunc2 osInterShutdownHook(StatusType Error)
{

   /* CovComment 4:  Function: osInterShutdownHook */
   
 #if ((osdSC== SC3) || (osdSC== SC4))
   osuint16 previousContext;
   
   osOwnCcb->LockIsNotNeeded.ossInSystemFct = osdTRUE;
   previousContext = osOwnCcb->LockIsNotNeeded.ossCurrentContext;
   osOwnCcb->LockIsNotNeeded.ossCurrentContext = osdCtxShutdownHook;
   COVER(0x00C6)
 #endif

   COVER(0x00C7)

   /* KB begin osekHWcallShutdownHook (default) */
      ShutdownHook(Error);
   /* KB end osekHWcallShutdownHook */

 #if ((osdSC== SC3) || (osdSC== SC4))
   osOwnCcb->LockIsNotNeeded.ossCurrentContext = previousContext;
   osOwnCcb->LockIsNotNeeded.ossInSystemFct = osdFALSE;
   COVER(0x00C8)
 #endif
} /* END OF osInterShutdownHook */
#endif /* osdSysShutdownHook */

#if osdPreTaskHook
/* MISRA RULE 8.10 VIOLATION: The function osInterPreTaskHook is general code for 
 * different platform specific OS implementations. Depending on the implementation,
 * the calling function may or may not be located in the same file.
 * Making the function static for only some implementations would
 * increase code complexity too much. */
osqFunc1 void osqFunc2 osInterPreTaskHook(void) /* PRQA S 1505 */
{
   /* CovComment 4:  Function: osInterPreTaskHook */
   
 #if ((osdSC== SC3) || (osdSC== SC4))
   osuint16 previousContext;

   osOwnCcb->LockIsNotNeeded.ossInSystemFct++;
   previousContext = osOwnCcb->LockIsNotNeeded.ossCurrentContext;
   osOwnCcb->LockIsNotNeeded.ossCurrentContext = osdCtxPreTaskHook;
   COVER(0x00C9)
 #endif

   OS_PREHOOK_ENTRY()
   PreTaskHook();
   OS_PREHOOK_EXIT()

 #if ((osdSC== SC3) || (osdSC== SC4))
   osOwnCcb->LockIsNotNeeded.ossCurrentContext = previousContext;
   osOwnCcb->LockIsNotNeeded.ossInSystemFct--;
   COVER(0x00CA)
 #endif

   COVER(0x00CB)

} /* END OF osInterPreTaskHook */
#endif /* osdPreTaskHook */

#if osdPostTaskHook
/* MISRA RULE 8.10 VIOLATION: The function osInterPostTaskHook is general code for 
 * different platform specific OS implementations. Depending on the implementation,
 * the calling function may or may not be located in the same file.
 * Making the function static for only some implementations would
 * increase code complexity too much. */
osqFunc1 void osqFunc2 osInterPostTaskHook(void) /* PRQA S 1505 */
{
   /* CovComment 4:  Function: osInterPostTaskHook */
   
 #if ((osdSC== SC3) || (osdSC== SC4))
   osuint16 previousContext;
   osOwnCcb->LockIsNotNeeded.ossInSystemFct++;
   previousContext = osOwnCcb->LockIsNotNeeded.ossCurrentContext;
   osOwnCcb->LockIsNotNeeded.ossCurrentContext = osdCtxPostTaskHook;
   COVER(0x00CC)
 #endif

   OS_POSTHOOK_ENTRY()
   PostTaskHook();
   OS_POSTHOOK_EXIT()

 #if ((osdSC== SC3) || (osdSC== SC4))
   osOwnCcb->LockIsNotNeeded.ossCurrentContext = previousContext;
   osOwnCcb->LockIsNotNeeded.ossInSystemFct--;
   COVER(0x00CD)
 #endif

   COVER(0x00CE)

} /* END OF osInterPostTaskHook */
#endif /* osdPostTaskHook */
/* KB end osekHWinterHooks */

/* KB begin osekHWIncrementCounter (default) */
#if (osdNumberOfSWCounters > 0)
/*-+--------------------------------------------------------------------------
 / IncrementCounter                                                           
 / ================                                                           
 /                                                                            
 / Syntax:                                                                    
 /    StatusType IncrementCounter(CounterType CounterID)                      
 / Parameter (In):                                                            
 /   CounterType CounterID                                                    
 / Parameter (Out):                                                           
 /   none                                                                     
 / Description:                                                               
 /   This service increments the counter <CounterID> by one. If any alarm time
  or schedule table expiry point is reached by this increment, the            
 /   configured action (e.g. task activation) is performed.                   
 / Return value (depends on OIL-Attribute STATUS):                            
 /    STANDARD:                                                               
 /       - No error, E_OK                                                     
 /    EXTENDED:                                                               
 /       - <CounterID> not valid, E_OS_ID                                     
 /       - The service has been called with interrupts disabled,               
 /         E_OS_DISABLEDINT                                                   
 / Scalability Classes:                                                       
 /    SC1, SC2, SC3, SC4                                                      
 /--------------------------------------------------------------------------*/
/* MISRA RULE 8.10 VIOLATION: osSysIncrementCounter is called from different modules in several configurations.
 * Declaring this function static for the other configurations would increase code complexity too much.
 */
osqFunc1 void osqFunc2 osSysIncrementCounter(CounterType CounterID) /* PRQA S 1505 */
{
   /* CovComment 4:  Function: osSysIncrementCounter */
   COVER(0x00CF)

   if(osCounter[CounterID] == oskCounterInternalMaximumValue[CounterID])
   {
      COVER(0x00D0)
      /* internal overflow to zero */
      osCounter[CounterID] = 0;
   }
   else
   {
      COVER(0x00D1)
      osCounter[CounterID]++;
   }
   
   COVER(0x00D2)
#if (osdNumberOfAlarms + osdNumberOfScheduleTables > 0)
   osWorkHeap(&oskAlarmHeaps[CounterID], CounterID);
#endif
   
}

#if !defined(osdIncrementCounterNotUsed)
/* MISRA RULE 8.10 VIOLATION: IncrementCounter is part of the defined OS API. Depending on the OS configuration, it is
 * called only in this file.
 */
/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/IncrementCounter!
 */
osqFunc1 StatusType osqFunc2 osIncrementCounter(CounterType CounterID) /* PRQA S 1505 */
{
   /* CovComment 4:  Function: osIncrementCounter */
   OS_IC_ENTRY()
   COVER(0x00D3)
#if STATUS_LEVEL == EXTENDED_STATUS
   /* check counter ID */
#if (osdNumberOfSWCounters > 0)
   if (CounterID >= osdNumberOfSWCounters)
   {
      COVER(0x00D4)
#else
      COVER(0x00D5)
#endif
      #if osdErrorHook
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveIncrementCounter_CounterID(CounterID)
      #endif
      osAPIError(E_OS_ID, osdErrICWrongCounterID);
      #if osdErrorHook
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_IC_EXIT()
      return E_OS_ID;
#if (osdNumberOfSWCounters > 0)
   }
   ELSEWITHCOVER(0x00D6)
#endif
#endif /* STATUS_LEVEL == EXTENDED_STATUS */

#if (osdNumberOfSWCounters > 0)
#if STATUS_LEVEL == EXTENDED_STATUS
#if ((osdSC == SC3) || (osdSC == SC4))
   /* check call context */
   if ((osdValidCtx_IncrementCounter & osOwnCcb->LockIsNotNeeded.ossCurrentContext) == 0)
   {
      COVER(0x00D7)
      #if osdErrorHook
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveIncrementCounter_CounterID(CounterID)
      #endif
      osAPIError(E_OS_CALLEVEL, osdErrICCallContext);

      #if osdErrorHook
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_IC_EXIT()
      return E_OS_CALLEVEL;
   }
   ELSEWITHCOVER(0x00D8)

   /* check access rights for this object */
   if (((oskApplCounterAccess[CounterID] & (1UL << osOwnCcb->LockIsNotNeeded.ossActiveApplicationID)) == 0))
   {
      COVER(0x00D9)
      #if osdErrorHook
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveIncrementCounter_CounterID(CounterID)
      #endif
      osAPIError(E_OS_ACCESS, osdErrICNoAccess);
      #if osdErrorHook
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_IC_EXIT()
      return E_OS_ACCESS;
   }
   ELSEWITHCOVER(0x00DA)
   
#endif /* ((osdSC == SC3) || (osdSC == SC4)) */


   if (osOwnCcb->LockIsNotNeeded.ossIntAPIStatus != 0)
   {
      COVER(0x00DB)
      #if osdErrorHook
      /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
      osSaveDisableLevelNested();
      /* KB end osekHWosSaveDisableLevelNested */
      osSaveIncrementCounter_CounterID(CounterID)
      #endif
      osAPIError(E_OS_DISABLEDINT, osdErrICIntAPIDisabled);
      #if osdErrorHook
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      #endif
      OS_IC_EXIT()
      return E_OS_DISABLEDINT;
   }
   ELSEWITHCOVER(0x00DC)
#endif /* STATUS_LEVEL == EXTENDED_STATUS */

   /* KB begin osekHWosSaveDisableLevelNested (overwritten) */
   osSaveDisableLevelNested();
   /* KB end osekHWosSaveDisableLevelNested */
   OS_IC_START_CRITICAL()


   #if (osdFullPreempt || osdMixedPreempt)
   osOwnCcb->LockIsNotNeeded.ossLockDispatcher++;
   #endif /* osdFullPreempt || osdMixedPreempt */
   
   osSysIncrementCounter(CounterID);

   #if (osdFullPreempt || osdMixedPreempt)
   osOwnCcb->LockIsNotNeeded.ossLockDispatcher--;
/* MISRA RULE 12.4 not violated: Reading the variable osOwnCcb->LockIsNotNeeded.ossLockDispatcher is sideeffect free.
 */
   IF2ANDCOVER((osOwnCcb->LockIsNotNeeded.ossLockDispatcher == 0) , (osOwnCcb->LockIsNeeded.ossStartDispatcher != osdFALSE),0x00FF,0x0100,0x0101)
   if (((osOwnCcb->LockIsNotNeeded.ossLockDispatcher == 0) && (osOwnCcb->LockIsNeeded.ossStartDispatcher != osdFALSE))) /* PRQA S 3415 */
   {
      COVER(0x00DD)
      OS_IC_END_CRITICAL()
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      OS_IC_EXIT()
      OS_START_DISPATCH()
      /* KB begin osekHWosLocalDispatcher (overwritten) */
      ptrToCcb2->ossCallDispatcher = 1;
      osDispatch();
      /* KB end osekHWosLocalDispatcher */
   }
   else
   #endif /* osdFullPreempt || osdMixedPreempt */
   {
      COVER(0x00DE)
      OS_IC_END_CRITICAL()
      /* KB begin osekHWosRestoreEnableLevelNested (overwritten) */
      osRestoreEnableLevelNested();
      /* KB end osekHWosRestoreEnableLevelNested */
      OS_IC_EXIT()
   }
   COVER(0x00DF)
   return E_OK;
#endif /* (osdNumberOfSWCounters > 0) */
}
#endif /* !defined(osdIncrementCounterNotUsed) */
#endif /* (osdNumberOfSWCounters > 0) */
/* KB end osekHWIncrementCounter */

/* KB begin osekGetActiveApplicationModeSrc (default) */
#if (!defined(osdGetActiveApplicationModeNotUsed))
/*-+--------------------------------------------------------------------------
 / GetActiveApplicationMode
 / ========================
 /
 / Syntax:          AppModeType osGetActiveApplicationMode ( void )
 / Parameter (In):  none
 / Parameter (Out): return value: Application mode in which the OS is currently
 /                  running
 / Description:     GetActiveApplicationMode returns the information about the
 /                  Application mode in which the OS is currently running.
 / Particularities: Allowed on task level, ISR level and in several hook 
 /                  routines.
 /                  This service is intended to be used by library functions 
 /                  and hook routines.
 /                  If a valid Application mode can't be evaluated (invalid call
 /                  context), the service returns OSINVALIDAPPMODE.
 / Context:         Task, Cat2-ISR, ErrorHook, Pre- and PostTaskHook, StartupHook,
 /                  ShutdownHook
 /--------------------------------------------------------------------------*/
/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/GetActiveApplicationMode
 */
osqFunc1 AppModeType osqFunc2 osGetActiveApplicationMode(void)
{
   /* CovComment 4:  Function: osGetActiveApplicationMode */

      COVER(0x00E0)
      return osActiveAppMode;
} /* END OF osGetActiveApplicationMode */

#endif /* (!defined(osdGetActiveApplicationModeNotUsed)) */
/* KB end osekGetActiveApplicationModeSrc */

/* KB begin osekGetISRIDSrc (default) */
#if (!defined(osdGetISRIDNotUsed))
/*-+--------------------------------------------------------------------------
 / GetISRID
 / ========
 /
 / Syntax:          ISRType osGetISRID ( void )
 / Parameter (In):  none
 / Parameter (Out): return value: ID of the ISR which is currently running
 / Description:     GetISRID returns the information about the ISR ID of the 
 /                  ISR.
 / Particularities: Allowed on task level, ISR level and in several hook 
 /                  routines.
 /                  This service is intended to be used by library functions 
 /                  and hook routines.
 /                  If a valid ISR ID can't be evaluated (no ISR currently 
 /                  running), the service returns INVALID_ISR.
 / Context:         Task, Cat2-ISR, ErrorHook, ProtectionHook
 /--------------------------------------------------------------------------*/

/* If this function is reported by a MISRA checking tool to violate Rule 14.1 (because this function is never called)
 * the API function may be switched off by the OS configuration parameter OS/APIOptimization/Manual/GetISRID
 */
osqFunc1 ISRType osqFunc2 osGetISRID(void)
{
   /* CovComment 4:  Function: osGetISRID */

      COVER(0x00E1)
      return osOwnCcb->LockIsNotNeeded.ossActiveISRID;
} /* END OF osGetISRID */

#endif /* (!defined(osdGetISRIDNotUsed)) */
/* KB end osekGetISRIDSrc */

// return channel number of active ISR
osqFunc1 ISRType osqFunc2 osGetISRch(void)
{
    return osConfigBlock.osIsrChannel[osOwnCcb->LockIsNotNeeded.ossActiveISRID];
}


#define osdEmptyToken

#if ((osdSC == SC3) || (osdSC == SC4))

/* MISRA RULE 19.12 VIOLATION: The macro osdDefineModeCheckFunctions uses ## multiply. The undefined order of 
 * evaluation is no problem here as there is at most one occurrence of ## in one statement. (0881) */
/* MISRA RULE 19.10 VIOLATION: (3 times) The macro osdDefineModeCheckFunctions uses macro parameters 
 * outside of '(' and ')'. This is unavoidable as it uses the parameters as return type and return 
 * instruction in a function definition (3410) */
/* CovComment 4:  Macro: osdDefineModeCheckFunctions */
#define osdDefineModeCheckFunctions(RetType, ApiName, FormalParams, ActualParams, ReturnInstr) \
   osqFunc1 RetType osqFunc2 osModeCheck##ApiName(FormalParams)/* PRQA S 3410 */ \
   {                                                                             \
      if (osAmITrusted())                                                        \
      {                                                                          \
         COVER(0x00E2)                                                                 \
         ReturnInstr os##ApiName(ActualParams);                /* PRQA S 3410 */ \
      }                                                                          \
      else                                                                       \
      {                                                                          \
         COVER(0x00E3)                                                                 \
         ReturnInstr osPsys##ApiName(ActualParams);            /* PRQA S 3410 */ \
      }                                                                          \
                                                                                 \
   }/* PRQA S 0881 */

#else /*((osdSC == SC3) || (osdSC == SC4))*/
#define osdDefineModeCheckFunctions(RetType, ApiName, FormalParams, ActualParams, ReturnInstr)
#endif /*((osdSC == SC3) || (osdSC == SC4))*/




/* KB begin osekEndOfCModule (overwritten) */
#pragma ghs section bss=default
#pragma ghs section data=default
#pragma ghs section sbss=default
#pragma ghs section sdata=default
#pragma ghs section text=default
#pragma ghs section rodata=default
#pragma ghs section rosdata=default
/* KB end osekEndOfCModule */

/* END OF MODULE osek.c */

/* SBSW_JUSTIFICATION_BEGIN
SBSW_JUSTIFICATION_END */

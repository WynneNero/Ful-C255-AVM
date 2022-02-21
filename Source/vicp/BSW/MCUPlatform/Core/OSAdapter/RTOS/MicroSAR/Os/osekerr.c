/* Kernbauer Version: 2.16 Konfiguration: RH850 Erzeugungsgangnummer: 214 Zweig: 1 */

/*****************************************************************************
| Project Name: MICROSAR OS
|    File Name: osekerr.c
|
|  General code: @Version: 9.01.04@
|  Module version: $vv$=1.52
|
|  Description: functions for handling of errors
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2000-2015 Vector Informatik GmbH          All rights reserved.
|****************************************************************************/
/*-History---------------------------------------------------------------------
* Version       Date          Name              Changes and comments    
* ----------------------------------------------------------------------------
* 0.1    May 25 ,2016                             Init version.
* ----------------------------------------------------------------------------
* 0.2    Dec 26 ,2016      ShangQiuju       remove #pragma ghs section data=".rdata" for gen s19 files.
* ----------------------------------------------------------------------
* 0.3   Jan 05,2017       ZhangJie            Delete test code for NMI
* ----------------------------------------------------------------------------
* 0.4   Jan 06,2017       ZhangJie           Recover NMI related function and add function discription
*-----------------------------------------------------------------------------*/
/* next define is set in the makefile
 * switches off the include of (generated) tcb.h, includes instead
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

#include "iodefine.h"

/* CovComment 0:  file: osekerr.c */

/* KB begin osekStartOfCModule (overwritten) */
#pragma ghs section bss=".os_bss"
#pragma ghs section data=".os_data"
#pragma ghs section sbss=".os_sbss"
#pragma ghs section sdata=".os_sdata"
#pragma ghs section text=".os_text"
#pragma ghs section rodata=".os_rodata"
#pragma ghs section rosdata=".os_rosdata"
/* KB end osekStartOfCModule */

/*-+--------------------------------------------------------------------------
 / osAbortSystem
 / Funktion:
 /              - called from system assertion osSysErrFail
 / Parameter:   uiError  error code
 / Returnvalue:
 / Context:     any, this function is meant for OS internal use
 /--------------------------------------------------------------------------*/
/* MISRA RULE 8.10 VIOLATION: Depending on the configuration, this function may be called only in this module.
 * Declaring this function static for some configurations would increase code complexity, too much.
 */
osqFunc1 void osqFunc2 osAbortSystem(osuint16 uiError) /* PRQA S 1505 */
{
   /* CovComment 4:  Function: osAbortSystem */
   osDisableGlobal();

   #if osdErrorHook
   COVER(0x027B)
   osOwnCcb->LockIsNotNeeded.ossLastError = uiError; 
   osErrorHook(E_OS_SYS_ABORT);
   #else
   COVER(0x027C)
   /* KB begin dummyAssignAbortSystem (default) */
   /* osdDummyRead might intentionally assign a value to an unused variable on 
    * some platforms to avoid compiler warnings. This is no MISRA error. (3199) */
   osdDummyRead(uiError)   /* PRQA S 3199 */
   /* KB end dummyAssignAbortSystem */
   #endif

   COVER(0x027D)
   osSysShutdownOS(E_OS_SYS_ABORT);

} /* END OF osAbortSystem */

/*-+--------------------------------------------------------------------------
 / osAssertFailed
 / Funktion:
 /              - called if assertion failed, interrupts are disabled in 
 /                assertion
 / Parameter:    
 / Returnvalue:
 / Context:     any, this function is meant for OS internal use
 /--------------------------------------------------------------------------*/
#if (STATUS_LEVEL == EXTENDED_STATUS) && (osdEnableAssertions==1)
osqFunc1 void osqFunc2 osAssertFailed(void)
{
   /* CovComment 4:  Function: osAssertFailed */
   COVER(0x027E)
   #if osdErrorHook
   COVER(0x027F)
   osErrorHook(E_OS_SYS_ASSERTION);
   #endif
   COVER(0x0280)
   /* system is now shut down */

   osSysShutdownOS(E_OS_SYS_ASSERTION);

} /* END OF osAssertFailed */
#endif

/*-+--------------------------------------------------------------------------
 / osUnrecoverableError
 / Function:    Called on detection of an error that is not recoverable, i.e.
 /              assertions or error conditions that must lead to system abort.
 /              This function disables all interrupts, calls the error hook
 /              if it is configured, and then goes into Shutdown.
 / Parameter:   StatusType StdErrorCode  - the OSEK/Autosar E_OS_xxx Error Code
 /              osuint16   osOsekErrorCode - the 16 bit extended error code
 / Returnvalue: void - this function will never return.
 / Context:     any, this function is meant for OS internal use
 /--------------------------------------------------------------------------*/
/* MISRA RULE 14.1 VIOLATION: osUnrecoverableError might not be called in some
 * configuration. Conditional compiling of the function would increase
 * the code complexity to unacceptable level (1503) */
osqFunc1 void osqFunc2 osUnrecoverableError(StatusType StdErrorCode, osuint16 osOsekErrorCode) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osUnrecoverableError */
   COVER(0x0281)
   /* KB begin osekHWosDisableGlobal (overwritten) */
   osDisableGlobal(); /* disable all interrupts, no nesting */
   /* KB end osekHWosDisableGlobal */
   #if osdErrorHook
   COVER(0x0282)
   osOwnCcb->LockIsNotNeeded.ossLastError = osOsekErrorCode; 
   osErrorHook(StdErrorCode);
   #else
   /* osdDummyRead might intentionally assign a value to an unused variable on 
    * some platforms to avoid compiler warnings. This is no MISRA error. (3199) */
   osdDummyRead(osOsekErrorCode) /* PRQA S 3199 */
   #endif
   osSysShutdownOS(StdErrorCode);
} /* END OF osUnrecoverableError */

/*-+--------------------------------------------------------------------------
 / osErrorHook
 / Funktion:
 /              - wrap Errorhook: disable interrupts and prevent recursive call
 / Parameter:   StatusType ErrorCode
 / Returnvalue:
 / Context:     any, this function is meant for OS internal use
 /--------------------------------------------------------------------------*/

#if osdErrorHook

/* MISRA RULE 8.10 VIOLATION: Depending on the configuration, this function may be
 * called only in this module. Declaring this function static for some
 * configurations would increase code complexity too much.
 */
osqFunc1 void osqFunc2 osErrorHook(StatusType ErrorCode) /* PRQA S 1505 */
{  
   /* CovComment 4:  Function: osErrorHook */
#if (STATUS_LEVEL == EXTENDED_STATUS)
   osuint8 osSavedAPIStatus;
#endif
#if ((osdSC== SC3) || (osdSC== SC4))
   osuint16 previousContext;
#endif
   
/* KB begin osekHWosErrorHookAddVars (default) */
/* KB end osekHWosErrorHookAddVars */
   COVER(0x0283)
   OS_ERHOOK_ENTRY()

#if (STATUS_LEVEL == EXTENDED_STATUS)
   COVER(0x0284)
   /* save and reset API status to prevent IntAPI errors inside errorhook */
   osSavedAPIStatus = osOwnCcb->LockIsNotNeeded.ossIntAPIStatus;
   osSetIntAPIStatus(0);
#endif

   /* KB begin osekAssignGlobalError (default) */
   #if osdORTIDebug
   osOwnCcb->LockIsNotNeeded.ossLastErrorCode=ErrorCode;
   #endif
   /* KB end osekAssignGlobalError */

   if (osOwnCcb->LockIsNotNeeded.ossErrorFlag == osdFALSE)
   {
      COVER(0x0285)
      osOwnCcb->LockIsNotNeeded.ossErrorFlag=osdTRUE; /* first entry in ErrorHook, lock ErrorHook */

#if (STATUS_LEVEL == EXTENDED_STATUS)
      COVER(0x0286)
/* MISRA RULE 16.2 VIOLATION: The (indirectly) recursive call of function osErrorHook is prevented
 * by the variable osOwnCcb->LockIsNotNeeded.ossErrorFlag.
 */
      osSysErrAssert((osCheckInterruptsDisabled() != 0), osdErrEHInterruptsEnabled) /* PRQA S 1580, 1520 */
#endif

      /* KB begin osekHWosErrorHookStartActions (overwritten) */
      osCheckCurrentStack();
      /* KB end osekHWosErrorHookStartActions */


#if osdSysErrorHook
      osInterErrorHook(ErrorCode);
#endif /* osdSysErrorHook */


      /* KB begin osekHWosErrorHookEndActions (overwritten) */
      osCheckStackPattern();
      /* KB end osekHWosErrorHookEndActions */

      osOwnCcb->LockIsNotNeeded.ossErrorFlag=osdFALSE; /* unlock ErrorHook */
   }
   ELSEWITHCOVER(0x0287)

#if (STATUS_LEVEL == EXTENDED_STATUS)
   COVER(0x0288)
   /* restore old IntAPI status */
   osSetIntAPIStatus(osSavedAPIStatus);
#endif

   COVER(0x0289)
   OS_ERHOOK_EXIT()
} /* END OF osErrorHook */
#endif
                  

/*-+--------------------------------------------------------------------------
 / osMissingTerminateError
 / Funktion:
 /              - called on return from task function without TerminateTask
 /              - shutdown system
 / Parameter:
 / Returnvalue:
 / Context:     any, this function is meant for OS internal use
 /--------------------------------------------------------------------------*/
#if (STATUS_LEVEL == EXTENDED_STATUS) && (osdNumberOfAllTasks > 0)
/* MISRA RULE 14.1 not violated: The OS sets the return addresses of all tasks to the 
 * address of the function osMissingTerminateError, so it becomes active whenever 
 * a tasks returns without calling TerminateTask(). MISRA-checkers will typcally 
 * be unable to detect this.
 */
osqFunc1 void osqFunc2 osMissingTerminateError(void)      /* PRQA S 1503 */ 
{
   /* CovComment 4:  Function: osMissingTerminateError */
   COVER(0x028A)
   
   COVER(0x028B)
   osUnrecoverableError(E_OS_MISSINGEND, osdErrMTMissingTerminateTask);
}
#endif /* (STATUS_LEVEL == EXTENDED_STATUS) && (osdNumberOfAllTasks > 0) */

/*-+--------------------------------------------------------------------------
 / osUnhandledException
 / Funktion:
 /              - called if an unhandled exception occures
 / Parameter:
 / Returnvalue:
 / Context:     any, this function is meant for OS internal use
 /--------------------------------------------------------------------------*/
/* MISRA RULE 8.10 not violated: see justification for rule 14.1 below */
/* MISRA RULE 14.1 not violated: The function osUnhandledException is a general handler 
 * for all unconfigured interrupts. MISRA-checkers can typically not evaluate the 
 * link from the interrupt vector table to this function.
 */
/* TR:SPMF78:0002 Start */
osqFunc1 void osqFunc2 osUnhandledException(void)      /* PRQA S 1503 */ /* PRQA S 1505 */
{
   /* CovComment 4:  Function: osUnhandledException */
   COVER(0x028C)
   osAbortSystem(osdErrUEUnhandledException); /* TR:SPMF78:0003 */

} /* END OF osUnhandledException */
/* TR:SPMF78:0002 End */

U32 nmiflag=0;
U32 nmi_cnt=0;
/*****************************************************************************
  FENMIHandlerfunc
  Description: called if NMI exception has occured
  Parameter: -
  ReturnValue: -
*****************************************************************************/
osqFunc1 void osqFunc2 FENMIHandlerfunc(void)
{
	nmiflag = WDTNMIF;	//read NMI factor, WDT0/1/TNMI
	nmi_cnt++;
	while(1);		    // wait for watchdog reset
}


/* KB begin osekHWosISRUnhandledExeptionSrc (overwritten) */
/*****************************************************************************
  osCoreExceptionHandler
  Description: called if unhandled core exception has occured
  Parameter: index of the core exception source
  ReturnValue: -
*****************************************************************************/
/* MISRA RULE 14.1 not violated: The function osUnhandledCoreExceptionHandler is called from 
   assembly language. MISRA checking tools do not see the call and complain about it. */
osqFunc1 void osqFunc2 osCoreExceptionHandler(osuint32 Status) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osCoreExceptionHandler */
   COVER(0x028D)
   #if osdExceptionDetails==1
   ptrToCcb2->ossUnhandledExceptionDetail = Status;
   ptrToCcb2->ossISRUnhandledException_Number = (osint16)(Status & 0x00FFUL);
   #endif
   osAbortSystem(osdErrUEUnhandledCoreException);
}

/*****************************************************************************
  osDirectBranchExceptionHandler
  Description: called if unhandled direct branch exception has occured
  Parameter: index of the exception source
  ReturnValue: -
*****************************************************************************/
/* MISRA RULE 14.1 not violated: The function osDirectBranchExceptionHandler is called from 
   assembly language. MISRA checking tools do not see the call and complain about it. */
osqFunc1 void osqFunc2 osDirectBranchExceptionHandler(osuint32 Status) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osDirectBranchExceptionHandler */
   COVER(0x028E)
   #if osdExceptionDetails==1
   ptrToCcb2->ossUnhandledExceptionDetail = Status;
   ptrToCcb2->ossISRUnhandledException_Number = (osint16)(Status & 0x01FFUL);
   #endif
   osAbortSystem(osdErrUEUnhandledDirectBranch);
}

/*****************************************************************************
  osEIINTExceptionHandler
  Description: called if unhandled EIINT exception has occured
  Parameter: index of the EIINT exception source
  ReturnValue: -
*****************************************************************************/
/* MISRA RULE 14.1 not violated: The function osEIINTExceptionHandler is called from 
   assembly language. MISRA checking tools do not see the call and complain about it. */
osqFunc1 void osqFunc2 osEIINTExceptionHandler(osuint32 Status) /* PRQA S 1503 */
{
   /* CovComment 4:  Function: osEIINTExceptionHandler */
   COVER(0x028F)
   #if osdExceptionDetails==1
   ptrToCcb2->ossUnhandledExceptionDetail = Status;
   ptrToCcb2->ossISRUnhandledException_Number = (osint16)(Status & 0x01FFUL);
   #endif
   osUnhandledException();
}
/* KB end osekHWosISRUnhandledExeptionSrc */


/* KB begin osekEndOfCModule (overwritten) */
#pragma ghs section bss=default
#pragma ghs section data=default
#pragma ghs section sbss=default
#pragma ghs section sdata=default
#pragma ghs section text=default
#pragma ghs section rodata=default
#pragma ghs section rosdata=default
/* KB end osekEndOfCModule */

/* END OF MODULE osekerr.c */


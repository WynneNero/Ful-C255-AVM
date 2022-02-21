/* Kernbauer Version: 2.16 Konfiguration: RH850 Erzeugungsgangnummer: 214 Zweig: 1 */

/*****************************************************************************
| Project Name: MICROSAR OS
|    File Name: osekasrt.h
|
|  General code: @Version: 9.01.04@
|  Module version: $vv$=1.27
|
|  Description: different assertions for error detection
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2000-2015 Vector Informatik GmbH          All rights reserved.
|****************************************************************************/

/* CovComment 0:  file: osekasrt.h */
/* double include preventer */
#ifndef _OSEKASRT_H
#define _OSEKASRT_H

/*lint -save Messages inhibited in this file, will be re-enabled at the end of file */
/*lint -e539 Did not expect positive indentation */

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

/* KB begin osekHw_FILE_Cast (default) */
#define osd_FILE_Cast
/* KB end osekHw_FILE_Cast */


/* TR:SPMF10:0010 Start */
#if osdErrorHook
 #define osAssertFailed_(x) osOwnCcb->LockIsNotNeeded.ossLastError = (osuint16) (x); osAssertFailed()
#else
 #define osAssertFailed_(x) osAssertFailed()
#endif
/* TR:SPMF10:0010 End */

#if ((STATUS_LEVEL == EXTENDED_STATUS) && (osdEnableAssertions))
    #define osSysErrAssertFailed(x)  {\
                                    osDisableGlobal();\
                                    osAssertFailed_(x);\
                                 }
/* TR:SPMF12:0004 Start */
    #define osSysErrAssert(p, x) if ((p) == 0)\
                                 {\
                                    osSysErrAssertFailed(x)\
                                 } /* TR:SPMF12:0004 End */
#else /* if STATUS_LEVEL == STANDARD_STATUS */
   #define osSysErrAssert(p, x)
   #define osSysErrAssertFailed(x)
#endif /* STATUS_LEVEL == STANDARD_STATUS */

/* TR:SPMF10:0008 Start */
#if osdErrorHook
   #define osAPIError(x, y)                                    \
      osOwnCcb->LockIsNotNeeded.ossLastError = (osuint16) (y); \
      osErrorHook((StatusType) (x))
#else
   #define osAPIError(x, y)
#endif
/* TR:SPMF10:0008 End */



/*lint -restore re-enable messages*/

#endif /* double include preventer */

/* END OF HEADER osekasrt.h */


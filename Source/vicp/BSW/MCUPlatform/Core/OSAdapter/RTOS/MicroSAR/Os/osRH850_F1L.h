/* Kernbauer Version: 2.16 Konfiguration: RH850 Erzeugungsgangnummer: 214 Zweig: 1 */

/*****************************************************************************
| Project Name: MICROSAR OS
|    File Name: osRH850_F1L.h
|
|  Module version: $vv$=1.00
|
|  Description: RH850 F1L specific header file
|  Platform:    RH850
|
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2014-2014 Vector Informatik GmbH          All rights reserved.
|****************************************************************************/

#ifndef _OSRH850_F1L_H
#define _OSRH850_F1L_H

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

#define osdMPUSupportInSVMode 0

#define osdOSTMBaseAddr   0xFFEC0000UL

#define osdICRBASE0       0xFFFF9000UL
#define osdICRBASE1       0xFFFFA000UL
#define osdIMRBASE0       0xFFFF90F0UL
#define osdIMRBASE1       0xFFFFA400UL

#define osdTAUJ0BaseAddr  0xFFE50000UL

#define osdTPArrivalTimerChannel   72
#define osdTPExecutionTimerChannel 73
#define osdTPBlockingTimerChannel  74

#if defined USE_QUOTE_INCLUDES
 #include "osINTC2.h"
#else
 #include <osINTC2.h>
#endif

#define osSysGetCoreID()  osdOnCore

#if defined __cplusplus
} /* ENDOF extern "C" */
#endif

#endif /* _OSRH850_F1L_H, double include preventer */

/* END OF HEADER _OSRH850_F1L_H.h */


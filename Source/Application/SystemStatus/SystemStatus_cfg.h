/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                         *
*   AUTHOR     :                                       *
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   :
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
* ----------------------------------------------------------------------
* 0.1             Jan 20,2016 init version.
* ----------------------------------------------------------------------
* 0.2             Dec 20,2016 ShangQiuju  add config according using hw.
*-----------------------------------------------------------------------
* 0.3             Dec 21,2016 ShangQiuju   Add Needed using include files "exti_if.h"
*-----------------------------------------------------------------------
* 0.4             Dec 22,2016 ShangQiuju   Add hw-switch for acc interrupt
*----------------------------------------------------------------------
* 0.5             Jan 24,2017     ZhangJie  Fix Coverity warning.
*=====================================================================*/
#ifndef _SYSTEM_STATUS_CFG_H_
#define _SYSTEM_STATUS_CFG_H_
#include "CONFIG.H"
#include "TYPES.H"
#include "EXTI_if.h"
/**** Definition of constants ****/

/**** Definition of macros ****/
/**** Declaration of constants ****/
#define INT_ACC_WAKEUP              EXTI_06
#define INT_VOL_WAKEUP				EXTI_03
/*#define INT_REVERSE_WAKEUP       EXTI_15*/

#define WAKEUPREASON_CANIN      (1u<<(WAKEUP_CANIN-1u))
#define WAKEUPREASON_ACCON  (1u<<(WAKEUP_ACCON-1u))


//#define ReadDirectACC(acc)       CS_SIG_SyncReceive((U16)SIG_ACC_DI_STATUS, acc )
/**** Declaration of variables ****/

#endif /*_SYSTEM_STATUS_CFG_H_*/

/****************************** END OF FILE ***************************/


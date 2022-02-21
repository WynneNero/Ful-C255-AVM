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
* 0.1    Jun 26,2016                   Initial version
*-----------------------------------------------------------------------
* 0.2    Jan 24,2017   ZhangJie   Remove unused include file.
*-----------------------------------------------------------------------
* 0.3    Feb 09,2017   ZhangJie   Using micro to call app function.
*-----------------------------------------------------------------------
* 0.4   Apr 01,2017   PEI Jingli  Fix headfiles.
*=====================================================================*/
#ifndef _CYCLICMNG_H_
#define _CYCLICMNG_H_
#include "define.h"

/**** Definition of constants ****/
typedef struct _SYSCYCLE_CYCLETASKDEFINE
{
    U8 tickcount;
    U8 tickstart;
} SysCycle_CycleTaskDef;

/**** Definition of macros ****/
/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/
void SysCycle_Init(void);
void SysCycle_DeInit(void);

void SysCycle_TimerHook(void);
void SysCycle_FastTaskEntry(void);
void SysCycle_SlowTaskEntry(void);

#define SysCycle_TestTaskEntry(index,output_level) 


#if (PRE_SECOND_FUNC_EN==1u)
/*This interface provides 1 second tick flag of Foreground task*/
BOOL SysCycle_Get1sForeground(void);

/*This interface provides 1 second tick flag of Background task*/
BOOL SysCycle_Get1sBackground(void);
#endif
#endif /*_CYCLICMNG_H_*/

/****************************** END OF FILE ***************************/


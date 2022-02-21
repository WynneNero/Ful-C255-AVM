/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.		           *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									                   *
************************************************************************
* Object        :  stbc_if.h 
* Module        : 
* Instance      : 
* Description   : Interface of mcu stand-by mode
*-----------------------------------------------------------------------
* Version: 
* Date: 
* Author: 
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
* ----------------------------------------------------------------------
* 0.1    Jul 21,2016    PEI Jingli  Initial version
* ----------------------------------------------------------------------
* 0.2   Dec 29,2016   PEI Jingli     Delete include file
* ----------------------------------------------------------------------
* 0.3   Mar 22,2017   PEI Jingli     Add interface checking cyclic-run mode used 
===============================================================*/
#ifndef  _STBC_IF_H
#define   _STBC_IF_H
#include "define.h"

extern void Stbc_Set_WakeupFactor(void);
extern void Stbc_Reset_WakeupFactor(void);
extern BOOL Stbc_CyclicRunEnableCheck(void);

extern void Stbc_Clear_IoHoldMode(void);
extern void Stbc_Run2Stop(void );
extern void Stbc_Run2DeepStop(void);

#endif/*_STBC_IF_H */


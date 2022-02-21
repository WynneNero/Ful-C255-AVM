/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.		           *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									                   *
************************************************************************
* Object        :  stbc.h 
* Module        : 
* Instance      : 
* Description   : 5 clock OSC, clock domain
*-----------------------------------------------------------------------
* Version: 
* Date: 
* Author: 
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
* ----------------------------------------------------------------------
* 0.1  Apr 15,2016    PEI Jingli  Initial 5 clock OSC, and clock domain.
* ----------------------------------------------------------------------
* 0.2  July 21,2016    PEI Jingli update CSI clock domain settings.
* ----------------------------------------------------------------------
* 0.3  Aug 10,2016   PEI Jingli add 11M MOSC configration.
* ----------------------------------------------------------------------
* 0.4 Nov 25,2016    PEI Jingli  Code architecture for code review
* ----------------------------------------------------------------------
* 0.5 Jan 10,2017     ZhangJie  Add function Clock_AWDTA_SetStpmsK define
*----------------------------------------------------------------------
* 0.6 Jan 24,2017     ZhangJie  Fix Coverity warning.
=======================================================================*/
#ifndef  _CLOCK_IF_H
#define   _CLOCK_IF_H
#include "Config.h"

/*---------------Function Define----------------*/

/*---- set cpu clock using clock source ----*/
extern void Clock_Setup_External_Highclock(void);	
extern void Clock_Setup_Internal_Highclock( void );
extern void Clock_Setup_Internal_Lowclock( void );
/*---- set clock sources of cpu clock  ----*/
extern void Clock_Stop_External_Highclock(void);
extern void Clock_Stop_Internal_Highclock(void);

/*----get frequency of clock domain ----*/
extern U32 Clock_GetFrequency_ATAUJ(void);

/* set stop mask in stand-by mode */
extern void Clock_AWDTA_SetStpmsK( BOOL isMask);

#endif/*_CLOCL_IF_H*/


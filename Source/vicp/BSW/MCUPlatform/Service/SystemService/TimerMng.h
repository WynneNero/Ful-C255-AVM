/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									   *
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
* 0.1   Jul 14,2016    PEI Jingli    initialize
------------------------------------------------------------------------
* 0.2   Dec 19,2016  PEI Jingli   Refactor after code review	
*-----------------------------------------------------------------------
* 0.3   Jan 24,2017   ZhangJie   Remove unused include file.
*=====================================================================*/
#ifndef _TIMER_MNG_H_
#define _TIMER_MNG_H_ 

/**** Definition of macros ****/
#define TIMERMNG_PASS_1
#include "TimerMng_def.h"


/**** Declaration of types ****/
/*define timer type*/
typedef enum
{
    TIMER_PERIODIC,    
    TIMER_ONE_SHOT   /*one time*/
}TIMER_TYPES;

/**** Declaration of variables ****/

/**** Declaration of functions ****/
/*Start a timer to do handler after delay a period*/
extern ERR_TYPE Timer_Start(U8 timerId, U16 periodMs, TIMER_TYPES type);
/*Force to stop a timer*/
extern ERR_TYPE Timer_Stop(U8 timerId);

#endif /*_TIMER_MNG_H_*/

/****************************** END OF FILE ***************************/


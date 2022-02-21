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
* Version       Date           Name           Changes and comments
------------------------------------------------------------------------
* 0.1	   Jun 26,2016    PEI Jingli       Initial version
------------------------------------------------------------------------
* 0.2	   Jun 29,2016    LIU Chenxi    Correct errors during merging		
------------------------------------------------------------------------
* 0.3	   July 07,2016   PEI Jingli       Adapt 64pin MCU
------------------------------------------------------------------------
* 0.4	   July 21,2016   LIU Chenxi    Adjust feature option
------------------------------------------------------------------------
* 0.5	   Aug 29,2016   PEI Jingli       Add option macro for HW PWM feature.
 ----------------------------------------------------------------------
* 0.6	   Dec 21,2016   PEI Jingli       Close IIC test option.
* ----------------------------------------------------------------------
* 0.7	   Jan 05,2017   ZhangJie       Close and Delete all TEST micro.
*------------------------------------------------------------------------
* 0.8          Jan 24,2017  ZhangJie        Fix Coverity warnings.
*-----------------------------------------------------------------------
* 0.9     Apr 04,2017   PEI Jingli   Add micro OSADP_WAIT_NOTIMEOUT.
*=====================================================================*/
#ifndef _CORE_CFG_H_
#define _CORE_CFG_H_ 

#include "Define.h"
#include "cpu.h"
/**** Definition of constants ****/

#define MICROSAR_EVENT 1u		/* lowest bit use as event flag*/
/*TASK config*/
#define OSADP_WAIT_NOTIMEOUT 0u

typedef enum E_OSAPI_TASKID
{
     OSAPI_SYSTEMSWITCHHIGH,
	OSAPI_FASTCYCLIC,
	OSAPI_EVENTTASK,
	OSAPI_SLOWCYCLIC,
	OSAPI_SLOWJOBTASK,
	OSAPI_SYSTEMSWITCHLOW,
	/*The next can add user task*/
	OSAPI_TASKNUM
}OSAPI_TaskIDType;


typedef enum E_OSAPI_TASKPRIORITY
{
	OSAPI_RESET_PRIO= 1,
	OSAPI_SYSTEMSWITCHHIGH_PRIO,
	OSAPI_FASTCYCLIC_PRIO,
	OSAPI_EVENTTASK_PRIO,
	OSAPI_SLOWCYCLIC_PRIO,
	OSAPI_SLOWJOBTASK_PRIO,
	/*The system switch low task should be low priority and just higher than idle task*/
	OSAPI_SYSTEMSWITCHLOW_PRIO
}OSAPI_TaskPriType;

typedef enum E_OSAPI_RESOURCE
{
 	OSAPI_EEPROMSECTION=0,
 	OSAPI_CSECTIONNUM
}OSAPI_ResourceType;

#define TASKMONITOR_EN    1u
#define WDG_ENABLE		/* open internal Watch dog*/
/**** Definition of macros ****/
/*#define OSAPI_INITTASK_STACKSIZE 100u*/

/*OS error check*/
#define OSAPI_DEBUG_EN  1u

/* 
* Description: Number of implemented system states.
*                      
* Range:       2...8
*              Example: 5 = S0, S1, S2, S3 and S4
*/
#define SYS_CFG_NO_OF_SYSTEM_STATES 8u

/*alarm task hook config*/
/*Fast alarm*/
#define OSALARM_FAST_ALARM_CARE_MSK 2u  /* 5ms	n * OSAPI_SYSTEM_CLOCK*/
/*#define OSALARM_FAST_ALARM_VAL 5		0x01u*/

/*Slow alarm*/
/*#define OSALARM_SLOW_ALARM_CARE_MSK 25		0x0Au 25ms*/
#define OSALARM_SLOW_ALARM_VAL 10u	/* 25ms*/

#define OSALARM_TIMER_ISR 	1u

/*OS timer config*/
#define OSAPI_SYSTEM_CLOCK 	25u   /*	2.5ms          1u   1ms*/
/*#define OSAPI_SYSTEM_TICK      		1   1 ms*/
#define OSAPI_SYSTEM_TICKMS(ms)  	(U8)(ms)
/*OS error check*/
#define OSAPI_DEBUG_EN  1u

/**** Declaration of constants ****/
/**** Declaration of variables ****/
#define SERVICE_HOOKS_EN 0u
#define SWP_TEST_EN  0u	
/**** Declaration of constants ****/


/**** Declaration of variables ****/

/**** Declaration of functions ****/

#if    (SERVICE_HOOKS_EN==0u&&SWP_TEST_EN>0u)
#error  "Service must enable!"
#endif

/**** Declaration of functions ****/



#endif /*_TASK_CFG_H_*/

/****************************** END OF FILE ***************************/


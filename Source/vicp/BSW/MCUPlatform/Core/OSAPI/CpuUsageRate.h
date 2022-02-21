/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				                    *
*				  All Rights Reserved.          					                           *
*   Department : CT AD                                                                                           *
*   AUTHOR	   : 									                                         *
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   :  CPU Usage rate caculator
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
* ----------------------------------------------------------------------
* 0.1    Mar 06,2017  ZhangJie  Initial version.
* ----------------------------------------------------------------------
* 0.2    Mar 22,2017  ZhangJie  Module only caculate max usage for per second, the total usage statistics should be done by APP.
*=====================================================================*/
#ifndef _CPU_USAGE_RATE_H_
#define _CPU_USAGE_RATE_H_
#ifdef __DEBUG__

#include "TimerUnit_if.h"

/**** Definition of constants ****/
#define SYSTEM_TICK_PERIOD (10) /*100us*/
#define CPURATE_COUNT_CYCLE 10 /*1s*/

#define CPUTASK_NUM (OSAPI_TASKNUM+SYSCYCLE_FASTCYCLE_COUNT+SYSCYCLE_SLOWCYCLE_COUNT)

#define CpuRate_SystemTick TAU_GetSystemTick_10us

/**** Definition of types ****/
enum
{
	CPU_Rate_Start=0u,
	CPU_Rate_Sop,
       CPU_Rate_Max
};

typedef struct st_CPU_TIMER_PARAM{
  U16 StartTimer;
  U16 StopTimer;
  struct st_CPU_TIMER_PARAM *SubTaskParam;
  U16 Usage_Counter;
  U16 Max_Usage_Counter;
  U8 Rollig_Counter[CPU_Rate_Max];
}ST_CPU_TIMER_PARAM;

/**** Definition of macros ****/

/**** Declaration of constants ****/


/**** Declaration of variables ****/

/**** Declaration of functions ****/
extern void CpuRate_TaskStart(U8 index, U8 Subindex);
extern void CpuRate_TaskStop(U8 index, U8 Subindex);
extern void CpuRate_100msEntry(void);
extern U16 CpuRate_GetMaxUsage(void);
extern U16* CpuRate_GetTaskMaxUsageTime(void);

#endif /* end of __DEBUG__ */
#endif /* end of _CPU_USAGE_RATE_H_ */
/****************************** END OF FILE ***************************/


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
* 0.1    Mar 08,2017  ZhangJie  Initial version.
* ----------------------------------------------------------------------
* 0.2    Mar 22,2017  ZhangJie  Module only caculate max usage for per second, the total usage statistics should be done by APP.
* ----------------------------------------------------------------------
* 0.3    Mar 24,2017  ZhangJie  Rename preprocessing micro.
*=====================================================================*/
#ifndef _STACK_USAGE_RATE_H_
#define _STACK_USAGE_RATE_H_
#ifdef __DEBUG__

#include "CyclicTask_Cfg.h"
#include "tcbpost.h"

/**** Definition of macros ****/
#define OSTIMER_ISR_ID ISR_TAUD0I15

#define OTHER_ISR_ID (0u)

#define STACK_NUM (OSAPI_TASKNUM+3u)

/**** Definition of constants ****/ 

/**** Definition of types ****/
typedef struct{
  U16 Usage;
  U16 Max_Usage;
}ST_STACK_USAGE_PARAM;

/**** Declaration of constants ****/


/**** Declaration of variables ****/

/**** Declaration of functions ****/
extern void StackRate_100msEntry(void);
extern U16* StackRate_GetMaxUsage(void);
extern U8* StackRate_GetMaxUsageRate(void);

#endif /* end of __DEBUG__ */
#endif /* end of _STACK_USAGE_RATE_H_ */
/****************************** END OF FILE ***************************/


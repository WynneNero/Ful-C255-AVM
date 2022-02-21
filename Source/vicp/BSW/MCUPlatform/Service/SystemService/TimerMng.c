/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									   *
************************************************************************
* Object        :                  TimerMng.c
* Module        :
* Instance      :
* Description   :
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version     Date      Name    Changes and comments
* 1.0   Jul 14,2016    PEI Jingli    initialize
------------------------------------------------------------------------
* 0.2   Jul 29,2016   PEI Jingli   Correct timer counter by OSAPI_SYSTEM_CLOCK 	
------------------------------------------------------------------------
* 0.3   Aug 31,2016  PEI Jingli   Correct timer timerout	
------------------------------------------------------------------------
* 0.4   Dec 19,2016  PEI Jingli   Refactor after code review
*------------------------------------------------------------------------
* 0.5   Jan 12,2017  ZhangJie  Add parentheses, add u for constant value and add conditional statement to avoid Coverity warnings.
*-----------------------------------------------------------------------
* 0.6   Jan 24,2017    ZhangJie     Remove unused include headfile.
*=====================================================================*/
#include "config.h"
#include "define.h"
#include "Eventmng.h"
#include "TimerMng.h"
#include "core_cfg.h"

#define TIMERMNG_PASS_2
#include "TimerMng_def.h"

#define TIMERMNG_PASS_3
#include "TimerMng_def.h"

/**** Declaration of variables ****/
/*Timer service invalid or not*/
static BOOL bTimerInited;
/*flag to execute timer-process*/
static BOOL bTimeout[SYSTIMER_MAX];
/*Timer inusing flag*/
static BOOL bActive[SYSTIMER_MAX];
/*time of periodic timer. If one-time timer,value is 0.unit by 1millisecond*/  
static U16  timeoutVal[SYSTIMER_MAX];
/*time counter*/ 
static U16  counter[SYSTIMER_MAX];      

/******************************************************************************
* Function Name : Timer_Init
* Description   : Initialize. 
* Argument     : none
* Return Value  : none
******************************************************************************/
void Timer_Init(void)
{
    U8 timerId=0u;
    for(timerId=0u; timerId<SYSTIMER_MAX; timerId++)
    {
        bTimeout[timerId] =FALSE;
        bActive[timerId] =FALSE;
        timeoutVal[timerId] =0u;
        counter[timerId] =0u;
    }
    bTimerInited=TRUE;
}

void Timer_DeInit(void)
{
    bTimerInited=FALSE;
}

/***********************************************************************
*  Name        : Timer_Start
*  Description : start a timer to do handler after delay a period.  
*  Parameter   : periodMs  delay time by millisecond. 
*          Note that periodMs less than OSAPI_SYSTEM_CLOCK/10 is invalid,  
*          and periodMs should be in multiples of OSAPI_SYSTEM_CLOCK/10 
*               type  TIMER_PERIODIC  =cycle timer
*                        TIMER_ONE_SHOT 
*  Returns     : None
***********************************************************************/
ERR_TYPE Timer_Start(U8 timerId, U16 periodMs, TIMER_TYPES type)
{
    ERR_TYPE eRet=ERR_OK;
    
    if((SYSTIMER_MAX<=timerId) ||((periodMs*10u)<OSAPI_SYSTEM_CLOCK)||(type>TIMER_ONE_SHOT)) /*invalid param*/
    {
        eRet=ERR_RANGE;
    }
    else if(NULL==TimerMng_apProc[timerId])
    {
        eRet=ERR_VALUE;
    }
    else 
    {
        if(bTimerInited==TRUE)
        {
            if(bActive[timerId]==FALSE)
            {
                counter[timerId]=(U16)(((U32)periodMs*10u)/OSAPI_SYSTEM_CLOCK);
                if(TIMER_ONE_SHOT==type)
                {
                    timeoutVal[timerId]=0u;
                }
                else
                {
                    timeoutVal[timerId]=counter[timerId];
                }
                bTimeout[timerId]=FALSE;
                bActive[timerId]=TRUE;
            }
            else
            {
                eRet=ERR_DISABLED;
            }
        }
        else
        {
          eRet=ERR_DISABLED;
        }
    }
    
    return eRet;
}

/***********************************************************************
*  Name        : Timer_Stop
*  Description : stop a timer 
*  Parameter   : 
*  Returns     : None
***********************************************************************/
ERR_TYPE Timer_Stop(U8 timerId)
{
    ERR_TYPE eRet=ERR_OK;
    
    if(SYSTIMER_MAX<=timerId)
    {
        eRet=ERR_RANGE;
    }
    else 
    {
        if(bTimerInited==TRUE)
        {
            bActive[timerId]=FALSE;
            counter[timerId]=0u;
            timeoutVal[timerId]=0u;
        }
        else
        {
            eRet=ERR_DISABLED;
        }
    }

    return eRet;
}

/***********************************************************************
*  Name        : Timer_tick_polling
*  Description : all timer counter 
*  Parameter   : 
*  Called       : ostick_isr. os tick=1ms
*  Returns    : None
***********************************************************************/
void Timer_tick_polling(void)  
{
    U8 timerId=0u;
    
    if(bTimerInited==TRUE)
    {
        for(timerId = 0u; timerId < SYSTIMER_MAX; timerId++)
        {
            if((TRUE==bActive[timerId]) && (0u!=counter[timerId])) 
            {
                counter[timerId]--;
                if(0u==counter[timerId])
                {
                    bTimeout[timerId]=TRUE;
                    if(0u==timeoutVal[timerId])
                    {
                        Timer_Stop(timerId);
                    }
                    else
                    {
                        counter[timerId]=timeoutVal[timerId];
                    }
                    
                    SysEvt_SetEvent(EVT_TIMER);
                }
            }
        }    
    }
}

/***********************************************************************
*  Name        : Timer_EventProc
*  Description : Exacute Timer-processing functions in event task
*  Parameter   : 
*  Called       : by event task
*  Returns    : None
***********************************************************************/
void Timer_EventProc(void)
{
    U8 timerId=0u;

    if(bTimerInited==TRUE)
    {
        for(timerId=0u;timerId<SYSTIMER_MAX;timerId++)
        {
           if( (TRUE == bTimeout[timerId])  && (NULL!=TimerMng_apProc[timerId]) )
           {           
               TimerMng_apProc[timerId]();
               bTimeout[timerId] = FALSE;
           }
        }
    }
}

/**************** END OF FILE *****************************************/


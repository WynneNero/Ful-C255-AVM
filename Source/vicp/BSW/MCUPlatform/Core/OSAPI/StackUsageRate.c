/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.		                         	      *
*				  All Rights Reserved.          			                         		      *
*   Department : CT AD     							                      	            *
*   AUTHOR	   : 									                                        *
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
* 0.1    Mar 08,2017  ZhangJie  Initial version.
* ----------------------------------------------------------------------
* 0.2    Mar 22,2017  ZhangJie  Module only caculate max usage for per second, the total usage statistics should be done by APP.
*-----------------------------------------------------------------------
* 0.3    Apr 1,2017   PEI Jingli   Fix include files.
*=====================================================================*/
#ifdef __DEBUG__
#include "Core_cfg.h"
#include "StackUsageRate.h"
#include "osek.h"

ST_STACK_USAGE_PARAM StackUsage[STACK_NUM]={0};
U16 maxStackUsage[STACK_NUM] = {0};
U8 maxStackUsageRate[STACK_NUM] = {0};
U16 Stack[STACK_NUM] = {300,300,300,300,300,300,300,50,150};
/***********************************************************************
*  Name        : StackRate_Init
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void StackRate_Init(void)
{

}

/***********************************************************************
*  Name        : StackRate_10msEntry
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void StackRate_10msEntry(void)
{
    U8 Stack_Counter = 0u;
    StackUsage[0].Usage =osGetSystemStackUsage ();
    for(Stack_Counter=1u;Stack_Counter<OSAPI_TASKNUM+1u;Stack_Counter++)
    {
        StackUsage[Stack_Counter].Usage=osGetStackUsage(Stack_Counter);
    }
    StackUsage[OSAPI_TASKNUM+1].Usage = osGetISRStackUsage(OSTIMER_ISR_ID);
    StackUsage[OSAPI_TASKNUM+2].Usage = osGetISRStackUsage(OTHER_ISR_ID);
    for(Stack_Counter =0u;Stack_Counter<STACK_NUM;Stack_Counter++)
    {
        if(StackUsage[Stack_Counter].Max_Usage<StackUsage[Stack_Counter].Usage)
        {
            StackUsage[Stack_Counter].Max_Usage = StackUsage[Stack_Counter].Usage;
        }
    }
}

/***********************************************************************
*  Name        : StackRate_GetMaxUsage
*  Description : 
*  Parameter   : None
*  Returns     : U16*
***********************************************************************/
U16* StackRate_GetMaxUsage(void)
{
    U8 Stack_Counter = 0u;
    for(Stack_Counter =0u;Stack_Counter<STACK_NUM;Stack_Counter++)
    {
        maxStackUsage[Stack_Counter] = StackUsage[Stack_Counter].Max_Usage;
        StackUsage[Stack_Counter].Max_Usage = 0;
    }
    return maxStackUsage;
}

/***********************************************************************
*  Name        : StackRate_GetMaxUsage
*  Description : 
*  Parameter   : None
*  Returns     : U8*
***********************************************************************/
U8* StackRate_GetMaxUsageRate(void)
{
    U8 Stack_Counter = 0u;
    for(Stack_Counter =0u;Stack_Counter<STACK_NUM;Stack_Counter++)
    {
        maxStackUsageRate[Stack_Counter] = (U8)((StackUsage[Stack_Counter].Max_Usage*100)/(Stack[Stack_Counter]*4));
        StackUsage[Stack_Counter].Max_Usage = 0;
    }
    return maxStackUsageRate;
}

#endif /*__DEBUG__*/

/**************** END OF FILE *****************************************/


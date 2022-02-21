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
* 0.1    Mar 06,2017  ZhangJie  Initial version.
* ----------------------------------------------------------------------
* 0.2    Mar 20,2017  ZhangJie  Rename ST_HWTIMER_DEVICE_PARAM.
* ----------------------------------------------------------------------
* 0.3    Mar 22,2017  ZhangJie  Module only caculate max usage for per second, the total usage statistics should be done by APP.
* ----------------------------------------------------------------------
* 0.4    Apr 13,2017  ZhangJie  Fix hwtimerParam for mcu with different pins.
*=====================================================================*/
#ifdef __DEBUG__
#include "Core_cfg.h"
#include "HAL.h"
#include "CpuUsageRate.h"
#include "CyclicTask_Cfg.h"

ST_HWTIMER_DEVICE_PARAM hwtimerParam ={{(TAU_UNIT)0, TAU_CH0}, 1000,FALSE, TRUE}; /* select a TAU channel */
ST_CPU_TIMER_PARAM FastTaskTimer[SYSCYCLE_FASTCYCLE_COUNT]={0};
ST_CPU_TIMER_PARAM SlowTaskTimer[SYSCYCLE_SLOWCYCLE_COUNT]={0};
ST_CPU_TIMER_PARAM CpuTimer[OSAPI_TASKNUM]={0};
U32 CpuRate_TaskUsage_Counter = 0;
U16 CpuRate_Usage = 0;
U16 CpuRate_maxUsage = 0;
U16 maxCpuUsage[CPUTASK_NUM]={0};
U8 CpuRate_cyclicCounter = 0;

/***********************************************************************
*  Name        : CpuRate_Init
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CpuRate_Init(void)
{
    CpuRate_TaskUsage_Counter = 0;
    CpuRate_Usage = 0;
    CpuRate_cyclicCounter = 0;
    CpuTimer[OSAPI_FASTCYCLIC].SubTaskParam=FastTaskTimer;
    CpuTimer[OSAPI_SLOWCYCLIC].SubTaskParam=SlowTaskTimer;
    hwtimerParam.timerChannel.un = TAUJ1_U4;
    hwtimerParam.timerChannel.chm =TAU_CH0;
    hwtimerParam.timerMs =SYSTEM_TICK_PERIOD;
    hwtimerParam.bWaveOutput =FALSE;
    hwtimerParam.bPeriodic =TRUE;
    if(ERR_OK==TAU_Timer_Config_US(hwtimerParam.timerChannel.un, hwtimerParam.timerChannel.chm, hwtimerParam.timerMs, hwtimerParam.bWaveOutput, hwtimerParam.bPeriodic))
    {
        TAU_Timer_Cmd(hwtimerParam.timerChannel.un, hwtimerParam.timerChannel.chm, (FUNCTION_STATE)TRUE);
    }

}

void CpuRate_100msEntry(void)
{
    CpuRate_cyclicCounter++;
    if(CpuRate_cyclicCounter == CPURATE_COUNT_CYCLE)
    {
        CpuRate_Usage = (CpuRate_TaskUsage_Counter/(1000/SYSTEM_TICK_PERIOD));
        CpuRate_TaskUsage_Counter = 0;
        CpuRate_cyclicCounter = 0;
    }
    if(CpuRate_maxUsage<CpuRate_Usage)
    {
        CpuRate_maxUsage = CpuRate_Usage;
    }
}

void CpuRate_TaskStart(U8 index, U8 Subindex)
{
    if(Subindex == 0xFF)
    {
        CpuTimer[index].StartTimer = CpuRate_SystemTick();
        CpuTimer[index].Rollig_Counter[CPU_Rate_Start]++;
    }
    else
    {
        (CpuTimer[index].SubTaskParam+Subindex)->StartTimer = CpuRate_SystemTick();
        (CpuTimer[index].SubTaskParam+Subindex)->Rollig_Counter[CPU_Rate_Start]++;
    }
}

void CpuRate_TaskStop(U8 index, U8 Subindex)
{
    if(Subindex == 0xFF)
    {
        CpuTimer[index].Rollig_Counter[CPU_Rate_Sop]++;
        if(CpuTimer[index].Rollig_Counter[CPU_Rate_Start] == CpuTimer[index].Rollig_Counter[CPU_Rate_Sop])
        {
            CpuTimer[index].StopTimer = CpuRate_SystemTick();
            if(CpuTimer[index].StopTimer >= CpuTimer[index].StartTimer)
            {
                CpuTimer[index].Usage_Counter = CpuTimer[index].StopTimer - CpuTimer[index].StartTimer;
            }
            else
            {
                CpuTimer[index].Usage_Counter = 0xFFFFu + CpuTimer[index].StopTimer - CpuTimer[index].StartTimer;
            }
            if(CpuTimer[index].Max_Usage_Counter<CpuTimer[index].Usage_Counter)
            {
                CpuTimer[index].Max_Usage_Counter=CpuTimer[index].Usage_Counter;
            }
            CpuRate_TaskUsage_Counter +=CpuTimer[index].Usage_Counter;
        }
    }
    else
    {
        (CpuTimer[index].SubTaskParam+Subindex)->Rollig_Counter[CPU_Rate_Sop]++;
        if((CpuTimer[index].SubTaskParam+Subindex)->Rollig_Counter[CPU_Rate_Start]== (CpuTimer[index].SubTaskParam+Subindex)->Rollig_Counter[CPU_Rate_Sop])
        {
            (CpuTimer[index].SubTaskParam+Subindex)->StopTimer = CpuRate_SystemTick();
            if((CpuTimer[index].SubTaskParam+Subindex)->StopTimer>= (CpuTimer[index].SubTaskParam+Subindex)->StartTimer)
            {
                (CpuTimer[index].SubTaskParam+Subindex)->Usage_Counter =(CpuTimer[index].SubTaskParam+Subindex)->StopTimer - (CpuTimer[index].SubTaskParam+Subindex)->StartTimer;
            }
            else
            {
                (CpuTimer[index].SubTaskParam+Subindex)->Usage_Counter =0xFFFFu+ (CpuTimer[index].SubTaskParam+Subindex)->StopTimer - (CpuTimer[index].SubTaskParam+Subindex)->StartTimer;
            }
        }
        if( (CpuTimer[index].SubTaskParam+Subindex)->Max_Usage_Counter < (CpuTimer[index].SubTaskParam+Subindex)->Usage_Counter)
        {
            (CpuTimer[index].SubTaskParam+Subindex)->Max_Usage_Counter = (CpuTimer[index].SubTaskParam+Subindex)->Usage_Counter;
        }
    }
}

/***********************************************************************
*  Name        : CpuRate_GetMaxUsage
*  Description : 
*  Parameter   : None
*  Returns     : U8*
***********************************************************************/
U16 CpuRate_GetMaxUsage(void)
{
    U16 ret =0;
    ret = CpuRate_maxUsage;
    CpuRate_maxUsage = 0;
    return ret;
}

/***********************************************************************
*  Name        : CpuRate_GetMaxTaskUsageTime
*  Description : 
*  Parameter   : None
*  Returns     : U16*
***********************************************************************/
U16* CpuRate_GetTaskMaxUsageTime(void)
{
    U8 CpuRate_MaxTimeCounter = 0;
    for(CpuRate_MaxTimeCounter = 0; CpuRate_MaxTimeCounter<OSAPI_TASKNUM; CpuRate_MaxTimeCounter++)
    {
        maxCpuUsage[CpuRate_MaxTimeCounter] = CpuTimer[CpuRate_MaxTimeCounter].Max_Usage_Counter;
        CpuTimer[CpuRate_MaxTimeCounter].Max_Usage_Counter = 0;
    }
    for(CpuRate_MaxTimeCounter = 0; CpuRate_MaxTimeCounter<SYSCYCLE_FASTCYCLE_COUNT; CpuRate_MaxTimeCounter++)
    {
        maxCpuUsage[CpuRate_MaxTimeCounter+OSAPI_TASKNUM] = (CpuTimer[OSAPI_FASTCYCLIC].SubTaskParam+CpuRate_MaxTimeCounter)->Max_Usage_Counter;
        (CpuTimer[OSAPI_FASTCYCLIC].SubTaskParam+CpuRate_MaxTimeCounter)->Max_Usage_Counter = 0;
    }
    for(CpuRate_MaxTimeCounter = 0; CpuRate_MaxTimeCounter<SYSCYCLE_SLOWCYCLE_COUNT; CpuRate_MaxTimeCounter++)
    {
        maxCpuUsage[CpuRate_MaxTimeCounter+OSAPI_TASKNUM+SYSCYCLE_FASTCYCLE_COUNT] = (CpuTimer[OSAPI_SLOWCYCLIC].SubTaskParam+CpuRate_MaxTimeCounter)->Max_Usage_Counter;
        (CpuTimer[OSAPI_SLOWCYCLIC].SubTaskParam+CpuRate_MaxTimeCounter)->Max_Usage_Counter = 0;
    }
    return maxCpuUsage;
}

#endif /*__DEBUG__*/

/**************** END OF FILE *****************************************/


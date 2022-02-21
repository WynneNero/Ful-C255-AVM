<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text" indent="yes" encoding="ISO-8859-1"/> 
<xsl:template match="/">   
/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *				  
*   All Rights Reserved.                                               *                                    					   
*   Department : RN RD SW1                                             *      									  
*   AUTHOR     : Shao Guangxian                                        *
************************************************************************
* Object        :  Tcbpost.h
* Module        :
* Instance      :
* Description   :
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:

***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date           Name         Changes and comment
 <xsl:for-each select="IRQ_Set/INF">
 <xsl:for-each select="info_Group">
 ------------------------------------------------------------------------
 *<xsl:value-of select="@Version"/>         .<xsl:value-of select="@Date"/>    .<xsl:value-of select="@Name"/>     .<xsl:value-of select="@Comment"/>
 </xsl:for-each>
</xsl:for-each>
*=====================================================================*/
#define __TCBPOST_H__
#if defined USE_QUOTE_INCLUDES
 #include "vrm.h"
#else
 #include <xsl:text disable-output-escaping="yes">&lt;</xsl:text>vrm.h<xsl:text disable-output-escaping="yes">&gt;</xsl:text>
#endif

#define osdVrmGenMajRelNum 1
#define osdVrmGenMinRelNum 6
#if defined USE_QUOTE_INCLUDES
 #include "vrm.h"
#else
 #include <xsl:text disable-output-escaping="yes">&lt;</xsl:text>vrm.h<xsl:text disable-output-escaping="yes">&gt;</xsl:text>
#endif
#include "os.h"

#define osClearTimerInterruptPoint(cnt) 
#define osHandleCounterInterrupt(cnt) 
#define osSetTimerInterruptPoint(cnt, time) osdFALSE
#define osInsertMinHeap(newItem, h, cnt) 
#define osGetCurrentTime(cnt) osCounter[cnt]


/*--------------------------------------------------------------------------*/
/*    alarms                                                                */
/*--------------------------------------------------------------------------*/
#if (osdNumberOfAlarms + osdNumberOfScheduleTables>0)
   extern osqTcbRAM1 volatile osqTcbRAM2 TickType osqTcbRAM3 osAlarmTime[osdNumberOfAlarms + osdNumberOfScheduleTables];
#else
   extern osqTcbRAM1 volatile osqTcbRAM2 TickType osqTcbRAM3 osAlarmTime[1];
#endif
#if (osdNumberOfAlarms > 0)
      extern osqTcbRAM1 volatile osqTcbRAM2 osuint8 osqTcbRAM3 osAlarmActivated[osdNumberOfAlarms];
#else
      extern osqTcbRAM1 volatile osqTcbRAM2 osuint8 osqTcbRAM3 osAlarmActivated[1];
#endif


#if (osdNumberOfAlarms > 0)
   extern osqTcbRAM1 volatile osqTcbRAM2 TickType osqTcbRAM3 osAlarmCycleTime[osdNumberOfAlarms];
#else
   extern osqTcbRAM1 volatile osqTcbRAM2 TickType osqTcbRAM3 osAlarmCycleTime[1];
#endif

#if (osdNumberOfCounters > 0)   
   extern osqROM0 osqROM1 const osqROM2 osHeapType osqROM3 oskAlarmHeaps[0];
   extern osqROM0 osqROM1 const osqROM2 osAlarmIndexType osqROM3 oskAlarmHeapSize[0];
#endif

#if (osdNumberOfAlarms > 0)   
      extern osqROM0 osqROM1 const osqROM2 TickType osqROM3 oskStaticAlarmTime[osdNumberOfAlarms];
      extern osqROM0 osqROM1 const osqROM2 TickType osqROM3 oskStaticAlarmCycleTime[osdNumberOfAlarms];
#else 
      osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskStaticAlarmTime[1];
      osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskStaticAlarmCycleTime[1];
#endif

#if (osdNumberOfAlarms > 0)
      osqROM0 extern osqROM1 const osqROM2 TaskType osqROM3 oskAlarmTask[osdNumberOfAlarms];
      #if (osdNumberOfAlarmSetEvent > 0)
         osqROM0 extern osqROM1 const osqROM2 EventMaskType osqROM3 oskAlarmEvent[osdNumberOfAlarms];
      #else
         osqROM0 extern osqROM1 const osqROM2 EventMaskType osqROM3 oskAlarmEvent[1];
      #endif
      osqROM0 extern osqROM1 const osqROM2 osuint8 osqROM3 oskAlarmAction[osdNumberOfAlarms];
      #if (osdNumberOfAlarmCallback > 0)
         osqROM0 extern osqROM1 const osqROM2 osAlarmCallbackType osqROM3 oskAlarmCallback[osdNumberOfAlarms];
      #else
         osqROM0 extern osAlarmCallbackType osqROM1 const osqROM2 osqROM3 oskAlarmCallback[1];
      #endif
      #if (osdNumberOfAlarmIncrementCounter > 0)
         osqROM0 extern osqROM1 const osqROM2 CounterType osqROM3 oskAlarmIncrementCounterID[osdNumberOfAlarms];
      #else
         osqROM0 extern osqROM1 const osqROM2 CounterType osqROM3 oskAlarmIncrementCounterID[1];
      #endif
#else /*if (osdNumberOfAlarms > 0)*/
      osqROM0 extern osqROM1 const osqROM2 TaskType osqROM3 oskAlarmTask[1];
      osqROM0 extern osqROM1 const osqROM2 EventMaskType osqROM3 oskAlarmEvent[1];
      osqROM0 extern osqROM1 const osqROM2 osuint8 osqROM3 oskAlarmAction[1];
      osqROM0 extern osAlarmCallbackType osqROM1 const osqROM2 osqROM3 oskAlarmCallback[1];
      osqROM0 extern osqROM1 const osqROM2 CounterType osqROM3 oskAlarmIncrementCounterID[1];
#endif /*if (osdNumberOfAlarms > 0)*/


/* Schedule Tables */ 

#if (osdNumberOfScheduleTables > 0)
extern osqROM0 osqROM1 const osqROM2 CounterType osqROM3 oskCounterOfST[osdNumberOfScheduleTables];
extern osqROM0 osqROM1 const osqROM2 TickType osqROM3 oskSTMaxAllowed[osdNumberOfScheduleTables];
extern osqROM0 osqROM1 const osqROM2 TickType osqROM3 oskScheduleTableInitialOffset[osdNumberOfScheduleTables];
extern osqROM0 osqROM1 const osqROM2 TickType osqROM3 oskAutostartScheduleTableOffset[osdNumberOfScheduleTables];
extern osqROM0 osqROM1 const osqROM2 TickType osqROM3 oskPrecision[osdNumberOfScheduleTables];
extern osqROM0 osqROM1 const osqROM2 osSTIndexType osqROM3 oskSTStartIndex[osdNumberOfScheduleTables];
extern osqROM0 osqROM1 const osqROM2 osuint8 osqROM3 oskScheduleTableAutoStart      [osdNumberOfScheduleTables];
extern osqROM0 osqROM1 const osqROM2 osuint8 osqROM3 oskScheduleTableAutoStartType  [osdNumberOfScheduleTables];
osqRAM0 extern osqRAM1 volatile osqRAM2 osSTIndexType           osqRAM3 osSTCurrentIndex[osdNumberOfScheduleTables];
osqRAM0 extern osqRAM1 volatile osqRAM2 ScheduleTableStatusType osqRAM3 osSTState[osdNumberOfScheduleTables];
osqRAM0 extern osqRAM1 volatile osqRAM2 ScheduleTableType       osqRAM3 osSTNextTable[osdNumberOfScheduleTables];
#else
extern osqROM0 osqROM1 const osqROM2 CounterType    osqROM3 oskCounterOfST                 [1];
extern osqROM0 osqROM1 const osqROM2 TickType       osqROM3 oskSTMaxAllowed                [1];
extern osqROM0 osqROM1 const osqROM2 osSTOffsetType osqROM3 oskScheduleTableInitialOffset  [1];
extern osqROM0 osqROM1 const osqROM2 TickType       osqROM3 oskAutostartScheduleTableOffset[1];
extern osqROM0 osqROM1 const osqROM2 TickType       osqROM3 oskPrecision                   [1];
extern osqROM0 osqROM1 const osqROM2 osSTIndexType  osqROM3 oskSTStartIndex                [1];
extern osqROM0 osqROM1 const osqROM2 osuint8        osqROM3 oskScheduleTableAutoStart      [1];
extern osqROM0 osqROM1 const osqROM2 osuint8        osqROM3 oskScheduleTableAutoStartType  [1];
osqRAM0 extern osqRAM1 volatile osqRAM2 osSTIndexType           osqRAM3 osSTCurrentIndex[1];
osqRAM0 extern osqRAM1 volatile osqRAM2 ScheduleTableStatusType osqRAM3 osSTState[1];
osqRAM0 extern osqRAM1 volatile osqRAM2 ScheduleTableType       osqRAM3 osSTNextTable[1];
#endif /* (osdNumberOfScheduleTables > 0) */

/* Counters */

/* Holds all counter values. Use this array only for write access.
For read access use osGetCurrentTime(). Size = #Counter */
extern osqTcbRAM1 volatile osqTcbRAM2 TickType osqTcbRAM3 osCounter[1];

/* Holds the maximum allowed value of all counters. Size = #Counter */
osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskCounterMaxAllowedValue[1];

/* Size = #Counter */
osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskCounterInternalMaximumValue[1];

/* Size = #Counter */
osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskCounterHalfrange[1];

/* Size = #Counter */
osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskCounterTicksPerBase[1];

/* Defines the minimum time between two counter actions. Size = #Counter */
osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskCounterMinCycle[1];

/* The counters' reload values. Size = #Counter */
osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskCounterReloadValue[1];

/* The id of the core, this counter is assigned too. Size = #Counter */
osqROM0 extern osqROM1 const osqROM2 CoreIdType osqROM3 oskCounterCoreId[1];

/* The half allowed maximum value of high resolution counter. Size = #HiResCounter */
osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskCounterHiResMaxHardwareValueHalf[1];

/* Timer mask; n LSbs set, where n = timer bit width. Size = #HiResCounter */
osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskHiResTimerBitMask[1];

/* The half allowed maximum value of high resolution timer. Size = #HiResCounter */
osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskHWTimerSemiCount[1];

/* The minimum time between two high resolution timer interrupts. Size = #HiResCounter */
osqROM0 extern osqROM1 const osqROM2 TickType osqROM3 oskMinTimeBetweenTimerIrqs[1];

/* Holds the last time of a high resolution timer interrupt. Size = #HiResCounter */
extern osqTcbRAM1 volatile osqTcbRAM2 TickType osqTcbRAM3 osLastHighResTimerIrq[1];

/* Holds the time of the next allowed high resolution interrupt. Size = #HiResCounter */
extern osqTcbRAM1 volatile osqTcbRAM2 TickType osqTcbRAM3 osNextAllowedTimerInt[1];

#define osReleaseHiResTimerISR(counterId) 

#define osTriggerHiResTimerISR(counterId) 

#define osGetHWTimerCounterValue(counterId) 0

#define osSetHWTimerDeltaValue(counterId,timeToSet) 

#define osSetHWTimerCompareValue(counterId,timeToSet) 
#if ((CC == BCC2) || (CC == ECC2))
   #if (osdNumberOfAllTasks > 0)
      extern volatile osqTcbRAM1 osqTcbRAM2 osActivationCountType osqTcbRAM3 osTcbActivationCount[osdNumberOfAllTasks];
   #else
      extern volatile osqTcbRAM1 osqTcbRAM2 osActivationCountType osqTcbRAM3 osTcbActivationCount[1];
   #endif
#endif

extern osqTcbRAM1 osqTcbRAM2 osCtrlVarType osqTcbRAM3 osCtrlVarsCore0;
   extern osqTcbRAM1 volatile osqTcbRAM2 EventMaskType osqTcbRAM3 osTcbWaitEventMask[osdNumberOfExtendedTasks];



#if ((osdSC == SC3) || (osdSC == SC4))
   extern osqTcbRAM1 volatile osqTcbRAM2 ApplicationStateType osqTcbRAM3 osApplicationState [osdNumberOfApplications];
#endif



#if (osdNumberOfAllTasks > 0)
  osqROM0 extern osqROM1 const osqROM2 osTaskFlagType osqROM3 oskTcbTaskFlags[osdNumberOfAllTasks];
#if (osdNumberOfExtendedTasks > 0) || osdLib
   extern osqTcbRAM1 volatile osqTcbRAM2 EventMaskType osqTcbRAM3 osTcbSetEventMask[osdNumberOfExtendedTasks];
#endif
#else
   #if STATUS_LEVEL == EXTENDED_STATUS
      osqROM0 extern osqROM1 const osqROM2 osTaskFlagType osqROM3 oskTcbTaskFlags[1];
   #endif
#if (osdNumberOfExtendedTasks > 0) || osdLib
      extern osqTcbRAM1 volatile osqTcbRAM2 EventMaskType osqTcbRAM3 osTcbSetEventMask[1];
#endif                                                 
#endif

#if (osdNumberOfAllTasks > 0)
   extern osqTcbRAM1 volatile osqTcbRAM2 osTaskStateType osqTcbRAM3 osTcbTaskState[osdNumberOfAllTasks];
   #if osdORTIDebug
    extern osqTcbRAM1 osqTcbRAM2 osPrioType osqTcbRAM3 osTcbActualPrio[osdNumberOfAllTasks];
    extern osqTcbRAM1 osqTcbRAM2 osuint8 osqTcbRAM3 osTcbORTIServiceId[osdNumberOfAllTasks];
   #endif
   #if STATUS_LEVEL == EXTENDED_STATUS
    #if (osdNumberOfInternalResources > 0) || (osdNumberOfInterruptResources > 0)
     extern osqTcbRAM1 osqTcbRAM2 osuint8 osqTcbRAM3 osTcbResourceCounter[osdNumberOfAllTasks];
    #endif
   #endif

#else
   extern osqTcbRAM1 volatile osqTcbRAM2 osTaskStateType osqTcbRAM3 osTcbTaskState[1];
   #if osdORTIDebug
   extern osqTcbRAM1 osqTcbRAM2 osPrioType osqTcbRAM3 osTcbActualPrio[1];
   extern osqTcbRAM1 osqTcbRAM2 osuint8 osqTcbRAM3 osTcbORTIServiceId[1];
   #endif

   #if STATUS_LEVEL == EXTENDED_STATUS
   #if (osdNumberOfInternalResources > 0) || (osdNumberOfInterruptResources > 0)
   extern osqTcbRAM1 osqTcbRAM2 osuint8 osqTcbRAM3 osTcbResourceCounter[1];
   #endif
   #endif
#endif

/* Resources */

#if (osdNumberOfAllResources > 0)
   #if ((!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed)))
      extern osqTcbRAM1 osqTcbRAM2 osPrioType osqTcbRAM3 osResSavedPrio[osdNumberOfAllResources];
   #endif
   #if STATUS_LEVEL == EXTENDED_STATUS <xsl:text disable-output-escaping="yes">&amp;</xsl:text><xsl:text disable-output-escaping="yes">&amp;</xsl:text> ((!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed)))
      extern osqTcbRAM1 osqTcbRAM2 osResCounterType osqTcbRAM3 osResOccupationCounter[osdNumberOfAllResources];
   #endif
   #if ((STATUS_LEVEL == EXTENDED_STATUS) <xsl:text disable-output-escaping="yes">&amp;</xsl:text><xsl:text disable-output-escaping="yes">&amp;</xsl:text> ((!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed)))) || osdORTIDebug
      extern osqTcbRAM1 osqTcbRAM2 TaskType osqTcbRAM3 osResActualTask[osdNumberOfAllResources];
   #endif
   
   #if (!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed))
      extern osqROM0 osqROM1 const osqROM2 osPrioType osqROM3 oskResCeilingPrio[osdNumberOfAllResources];
   #endif
#else
   #if ((!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed)))
      extern osqTcbRAM1 osqTcbRAM2 osPrioType osqTcbRAM3 osResSavedPrio[1];
   #endif
   #if STATUS_LEVEL == EXTENDED_STATUS <xsl:text disable-output-escaping="yes">&amp;</xsl:text><xsl:text disable-output-escaping="yes">&amp;</xsl:text>((!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed)))
      extern osqTcbRAM1 osqTcbRAM2 osResCounterType osqTcbRAM3 osResOccupationCounter[1];
   #endif
   #if ((STATUS_LEVEL == EXTENDED_STATUS)<xsl:text disable-output-escaping="yes">&amp;</xsl:text><xsl:text disable-output-escaping="yes">&amp;</xsl:text>osdEnableAssertions <xsl:text disable-output-escaping="yes">&amp;</xsl:text><xsl:text disable-output-escaping="yes">&amp;</xsl:text> ((!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed)))) || osdORTIDebug
      extern osqTcbRAM1 osqTcbRAM2 TaskType osqTcbRAM3 osResActualTask[1];
   #endif
   
   #if (!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed))
   extern osqROM0 osqROM1 const osqROM2 osPrioType osqROM3 oskResCeilingPrio[1];
   #endif
#endif
#if (!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed))
 #if (osdNumberOfTaskResources > 0)
   #if (osdRTSize > 1)
      extern osqROM0 osqROM1 const osqROM2 osPrioOffsetType osqROM3 oskResCeilingPrioOffset[osdNumberOfTaskResources];
   #endif
   extern osqROM0 osqROM1 const osqROM2 osPrioFlagType osqROM3 oskResCeilingPrioMask[osdNumberOfTaskResources];
 #else
   #if (osdRTSize > 1)
      extern osqROM0 osqROM1 const osqROM2 osPrioOffsetType osqROM3 oskResCeilingPrioOffset[1];
   #endif
   extern osqROM0 osqROM1 const osqROM2 osPrioFlagType osqROM3 oskResCeilingPrioMask[1];
 #endif
#endif /* (!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed)) */

#if (osdNumberOfInternalResources > 0)
   extern osqROM0 osqROM1 const osqROM2 osPrioType osqROM3 oskResInternalCeilingPrio[osdNumberOfAllTasks];
   extern osqROM0 osqROM1 const osqROM2 osPrioFlagType osqROM3 oskResInternalCeilingPrioMask[osdNumberOfAllTasks];
   #if (osdRTSize > 1)
      extern osqROM0 osqROM1 const osqROM2 osPrioOffsetType osqROM3 oskResInternalCeilingPrioOffset[osdNumberOfAllTasks];
   #endif
#endif
#if (osdNumberOfSemaphores > 0)
   extern osqTcbRAM1 osqTcbRAM2 osuint8 osqTcbRAM3 osSemaphoreState[osdNumberOfSemaphores];
   #if (osdNumberOfExtendedTasks == 0) <xsl:text disable-output-escaping="yes">&amp;</xsl:text><xsl:text disable-output-escaping="yes">&amp;</xsl:text>osdLib
   extern osqTcbRAM1 volatile osqTcbRAM2 osSemaphoreType osqTcbRAM3 osTcbWaitForSemaphore[1];
   #else
   extern osqTcbRAM1 volatile osqTcbRAM2 osSemaphoreType osqTcbRAM3 osTcbWaitForSemaphore[osdNumberOfExtendedTasks];
   #endif
   #if (osdKillTaskIsrPossible || (osdSC== SC3) || (osdSC== SC4))
      extern osqTcbRAM1 volatile osqTcbRAM2 TaskType osqTcbRAM3 osSemaOwner[osdNumberOfSemaphores];
   #endif
#endif

#if osdLib
   #define osrRTSize                     oskRTSize 
   #define osrNumberOfPriorities         oskNumberOfPriorities
   #define osrNumberOfAppModes           oskNumberOfAppModes
   #define osrNumberOfAllTasks           oskNumberOfAllTasks
   #define osrNumberOfAllResources       oskNumberOfAllResources
   #define osrNumberOfTaskResources      oskNumberOfTaskResources
   #define osrNumberOfInterruptResources oskNumberOfInterruptResources
   #define osrNumberOfInternalResources  oskNumberOfInternalResources
   #define osrNumberOfExtendedTasks      oskNumberOfExtendedTasks
   #define osrNumberOfAlarms             oskNumberOfAlarms
   #define osrNumberOfScheduleTables     oskNumberOfScheduleTables
   #define osrNumberOfSemaphores         oskNumberOfSemaphores
   #define osrSystemTimer                oskSystemTimer
   #define osrNumberOfCounters           oskNumberOfCounters

   extern const osRTSizeType               oskRTSize;
   extern const osAppModeIndexType         oskNumberOfAppModes;
   extern const osTaskIndexType            oskNumberOfAllTasks;
   extern const osTaskIndexType            oskNumberOfExtendedTasks;
   extern const osPrioType                 oskNumberOfPriorities;
   extern const osResourceIndexType        oskNumberOfAllResources;
   extern const osResourceIndexType        oskNumberOfTaskResources;
   extern const osResourceIndexType        oskNumberOfInterruptResources;
   extern const osResourceIndexType        oskNumberOfInternalResources;

   extern const osAlarmIndexType           oskNumberOfAlarms;

   extern const ScheduleTableType          oskNumberOfScheduleTables;
   extern const osSemaphoreType            oskNumberOfSemaphores;
   extern const CounterType                oskSystemTimer;
   extern const CounterType                oskNumberOfCounters;

   extern const TickType oskMaxAllowedValue;
   extern const TickType oskTicksPerBase;
   extern const TickType oskMinCycle;
   extern const osuint8 oskAlarmAutoStart[];

   extern const osuint8 oskTcbAutoStart[];


   extern const osVersionVariantCodingType oskLibVersionVariant;

#else
   #define osrRTSize                      osdRTSize 
   #define osrNumberOfPriorities          osdNumberOfPriorities 
   #define osrNumberOfAppModes            osdNumberOfAppModes
   #define osrNumberOfAllTasks            osdNumberOfAllTasks
   #define osrNumberOfAllResources        osdNumberOfAllResources
   #define osrNumberOfTaskResources       osdNumberOfTaskResources
   #define osrNumberOfInterruptResources  osdNumberOfInterruptResources
   #define osrNumberOfInternalResources   osdNumberOfInternalResources
   #define osrNumberOfExtendedTasks       osdNumberOfExtendedTasks
   #define osrNumberOfAlarms              osdNumberOfAlarms
   #define osrNumberOfScheduleTables      osdNumberOfScheduleTables
   #define osrNumberOfSemaphores          osdNumberOfSemaphores
   #define osrNumberOfCounters            osdNumberOfCounters
   /* in source code variant map hook routines directly to user functions */
#endif

osqROM0 extern osStackPtrType osqROM1 const osqROM2 osqROM3  oskSystemStackTop;

/* End of invariant part */
#if (osdKillTaskIsrPossible || (osdSC == SC3) || (osdSC == SC4))
#if (osdNumberOfCat2ISRs > 0)
   extern osqTcbRAM1 osqTcbRAM2 osResourceIndexType osqTcbRAM3 osIcbLockedResource[osdNumberOfCat2ISRs];
#else
   extern osqTcbRAM1 osqTcbRAM2 osResourceIndexType osqTcbRAM3 osIcbLockedResource[1];
#endif
#endif

/* Tasks */ 
#define SystemSwitchHigh ((TaskType)0)
#define FastCyclic ((TaskType)1)
#define EventTask ((TaskType)2)
#define SlowCyclic ((TaskType)3)
#define SlowJob ((TaskType)4)
#define SystemSwitchLow ((TaskType)5)
#define ResetTask ((TaskType)6)

/* Task function prototypes */ 
void SystemSwitchHighfunc(void);
void FastCyclicfunc(void);
void EventTaskfunc(void);
void SlowCyclicfunc(void);
void SlowJobfunc(void);
void SystemSwitchLowfunc(void);
//void ResetTaskfunc(void);
extern void InitTaskEntry(void);
/*
extern void SysCycle_FastTaskEntry(void);
extern void SysEvt_TaskEntry(void);
extern void SysCycle_SlowTaskEntry(void);
extern void SysJob_TaskEntry(void);
extern void SysSwitch_LowTaskEntry(void);
extern void SysSwitch_HighTaskEntry(void);
extern void InitTaskEntry(void *p_arg);
*/

osqROM0 extern osqROM1 const osqROM2 osTaskFlagType osqROM3 oskTcbTaskFlags[osdNumberOfAllTasks];
osqROM0 extern osqROM1 const osqROM2 osPrioFlagType osqROM3 oskTcbReadyPrioMask[osdNumberOfAllTasks];
#if (osdRTSize > 1)
osqROM0 extern osqROM1 const osqROM2 osPrioOffsetType osqROM3 oskTcbReadyPrioOffset[osdNumberOfAllTasks];
#endif /* (osdRTSize > 1) */
osqROM0 extern osqROM1 const osqROM2 osPrioType osqROM3 oskTcbHomePrio[osdNumberOfAllTasks];
#if (CC == BCC2) || (CC == ECC2)
osqROM0 extern osqROM1 const osqROM2 osActivationCountType osqROM3 oskTcbAllowedActivations[osdNumberOfAllTasks];
#endif /* (CC == BCC2) || (CC == ECC2) */

/* ISRs */ 

/* ISR categories */ 
#define osdIsrISR_CAN0ERRCat 2
#define osdIsrISR_CAN0RECCat 2
#define osdIsrISR_CAN0TRXCat 2
#define osdIsrISR_CANGERRCat 2
#define osdIsrISR_CANGRECCCat 2
#define osdIsrISR_TAUB0I0Cat 2
#define osdIsrISR_TAUD0I0Cat 2
#define osdIsrISR_TAUJ0I0Cat 2
#define osdIsrISR_TAUJ1I0Cat 2
#define osdIsrISR_WDTA0Cat 2
#define osdIsrosTrapDispatcher_c0Cat 1

/* ISR IDs */ 
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_0'">
	#define ISR_TAUD0I0 ((ISRType)0)//0
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_2'">
	#define ISR_TAUD0I2 ((ISRType)1)//1
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_4'">
    #define ISR_TAUD0I4 ((ISRType)2)//2
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_6'">
    #define ISR_TAUD0I6 ((ISRType)3)//3
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_8'">
    #define ISR_TAUD0I8 ((ISRType)4)//4
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_10'">
    #define ISR_TAUD0I10 ((ISRType)5)//5
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_12'">
    #define ISR_TAUD0I12 ((ISRType)6)//6
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_14'">
    #define ISR_TAUD0I14 ((ISRType)7)//7
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'ADC']">
	<xsl:choose>
	<xsl:when test="value='1'">
	#define ISR_ADCA0_INTSG1 ((ISRType)10)//10
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'ADC']">
	<xsl:choose>
	<xsl:when test="value='2'">
    #define ISR_ADCA0_INTSG2 ((ISRType)11)//11
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'ADC']">
	<xsl:choose>
	<xsl:when test="value='3'">
	#define ISR_ADCA0_INTSG3 ((ISRType)12)//12
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='0'or value='1'or value='2'">
	#define ISR_CANGERR ((ISRType)14)//14
	#define ISR_CANGRECC ((ISRType)15)//15 
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='0'">
	#define ISR_CAN0ERR ((ISRType)16)//16
	#define ISR_CAN0REC ((ISRType)17)//17
	#define ISR_CAN0TRX ((ISRType)18)//18
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='0'">
	#define ISR_CSIH0IC ((ISRType)21)//21
	#define ISR_CSIH0IR ((ISRType)22)//22
	#define ISR_CSIH0IRE ((ISRType)23)//23
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise> 
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='0'">
	#define ISR_UART0 ((ISRType)25)//25
	#define ISR_UART0 ((ISRType)26)//26
	#define ISR_UART0 ((ISRType)27)//27
	#define ISR_UART0_Error ((ISRType)28)//28
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='0'">
    #define ISR_INTP0 ((ISRType)29)//29
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='1'">
    #define ISR_INTP1 ((ISRType)30)//30
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='2'">
    #define ISR_INTP2 ((ISRType)31)//31
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'WD']">
	<xsl:choose>
	<xsl:when test="value='0'">
    #define ISR_WDTA0 ((ISRType)32)//32
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
      <xsl:for-each select="IRQ_Set/FUN[@Register = 'WD']">
	<xsl:choose>
	<xsl:when test="value='1'">
	#define ISR_WDTA1 ((ISRType)33)//33
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='3'">
    #define ISR_INTP3 ((ISRType)34)//34
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='4'">
    #define ISR_INTP4 ((ISRType)35)//35
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='5'">
    #define ISR_INTP5 ((ISRType)36)//36
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='10'">
    #define ISR_INTP10 ((ISRType)37)//37
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='11'">
	#define ISR_INTP11 ((ISRType)38)//38
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_1'">
    #define ISR_TAUD0I1 ((ISRType)39)//39
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_3'">
    #define ISR_TAUD0I3 ((ISRType)40)//40
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_5'">
    #define ISR_TAUD0I5 ((ISRType)41)//41
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_7'">
    #define ISR_TAUD0I7 ((ISRType)42)//42
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_9'">
    #define ISR_TAUD0I9 ((ISRType)43)//43
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_11'">
    #define ISR_TAUD0I11 ((ISRType)44)//44
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_13'">
    #define ISR_TAUD0I13 ((ISRType)45)//45
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_15'">
    #define ISR_TAUD0I15 ((ISRType)46)//46
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='0'">
	#define ISR_DMA0 ((ISRType)52)//52
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='1'">
    #define ISR_DMA0 ((ISRType)53)//53
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='2'">
    #define ISR_DMA0 ((ISRType)54)//54
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='3'">
    #define ISR_DMA0 ((ISRType)55)//55
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='4'">
    #define ISR_DMA0 ((ISRType)56)//56
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='5'">
    #define ISR_DMA0 ((ISRType)57)//57
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='6'">
    #define ISR_DMA0 ((ISRType)58)//58
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='7'">
    #define ISR_DMA7 ((ISRType)59)//59
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='8'">
    #define ISR_DMA8 ((ISRType)60)//60
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='9'">
    #define ISR_DMA9 ((ISRType)61)//61
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='10'">
    #define ISR_DMA10 ((ISRType)62)//62
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='11'">
    #define ISR_DMA11 ((ISRType)64)//64
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='12'">
    #define ISR_DMA12 ((ISRType)65)//65
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='13'">
    #define ISR_DMA13 ((ISRType)66)//66
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='14'">
    #define ISR_DMA14 ((ISRType)67)//67
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'IIC']">
	<xsl:choose>
	<xsl:when test="value='0'">
	#define ISR_IIC0TI ((ISRType)68)//68
	#define ISR_IIC0TEI ((ISRType)69)//69
	#define ISR_IIC0RI ((ISRType)70)//70
	#define ISR_IIC0EE ((ISRType)71)//71
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_0'">
    #define ISR_TAUJ0I0 ((ISRType)72)//72
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_1'">
    #define ISR_TAUJ0I1 ((ISRType)73)//73
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_2'">
    #define ISR_TAUJ0I2 ((ISRType)74)//74
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_3'">
    #define ISR_TAUJ0I3 ((ISRType)75)//75
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'OS']">
	<xsl:choose>
	<xsl:when test="value='0'">
	#define ISR_OSTM0 ((ISRType)76)//76
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='0'">
    #define ISR_PWGA0 ((ISRType)84)//84
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='1'">
    #define ISR_PWGA1 ((ISRType)85)//85
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='2'">
     #define ISR_PWGA2 ((ISRType)86)//86
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='3'">
    #define ISR_PWGA3 ((ISRType)87)//87
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='8'">
    #define ISR_PWGA8 ((ISRType)88)//88
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='9'">
    #define ISR_PWGA9 ((ISRType)89)//89
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='10'">
    #define ISR_PWGA10 ((ISRType)90)//90
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='11'">
    #define ISR_PWGA11 ((ISRType)91)//91
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='12'">
    #define ISR_PWGA12 ((ISRType)92)//92
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='13'">
    #define ISR_PWGA13 ((ISRType)93)//93
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='14'">
    #define ISR_PWGA14 ((ISRType)94)//94
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='15'">
    #define ISR_PWGA15 ((ISRType)95)//95
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   	<xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='1'">
    #define ISR_CAN1ERR ((ISRType)105)//105
	#define ISR_CAN1REC ((ISRType)106)//106
	#define ISR_CAN1TRX ((ISRType)107)//107
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='1'">
	#define ISR_CSIH1IC ((ISRType)108)//108
	#define ISR_CSIH1IR ((ISRType)109)//109
	#define ISR_CSIH1IRE ((ISRType)110)//110
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='1'">
	#define ISR_UART1 ((ISRType)112)//112
	#define ISR_UART1_Tx ((ISRType)113)//113
	#define ISR_UART1_Rx ((ISRType)114)//114
	#define ISR_UART1_Error ((ISRType)115)//115
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='20'">
    #define ISR_PWGA20 ((ISRType)116)//116
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='21'">
    #define ISR_PWGA21 ((ISRType)117)//117
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='22'">
    #define ISR_PWGA22 ((ISRType)118)//118
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
		<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='23'">
    #define ISR_PWGA23 ((ISRType)119)//119
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='6'">
	#define ISR_INTP6 ((ISRType)120)//120
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='7'">
    #define ISR_INTP7 ((ISRType)121)//121
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='8'">
    #define ISR_INTP8 ((ISRType)122)//122
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='12'">
    #define ISR_INTP12 ((ISRType)123)//123
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='2'">
	#define ISR_CSIH2IC ((ISRType)124)//124
	#define ISR_CSIH2IR ((ISRType)125)//125
	#define ISR_CSIH2IRE ((ISRType)126)//126
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_0'">
    #define ISR_TAUB0I0 ((ISRType)134)//134
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_1'">
    #define ISR_TAUB0I1 ((ISRType)135)//135
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_2'">
    #define ISR_TAUB0I2 ((ISRType)136)//136
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_3'">
    #define ISR_TAUB0I3 ((ISRType)137)//137
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_4'">
    #define ISR_TAUB0I4 ((ISRType)138)//138
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_5'">
    #define ISR_TAUB0I5 ((ISRType)139)//139
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_6'">
    #define ISR_TAUB0I6 ((ISRType)140)//140
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_7'">
    #define ISR_TAUB0I7 ((ISRType)141)//141
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_8'">
    #define ISR_TAUB0I8 ((ISRType)142)//142
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_9'">
    #define ISR_TAUB0I9 ((ISRType)143)//143
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_10'">
    #define ISR_TAUB0I10 ((ISRType)144)//144
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_11'">
    #define ISR_TAUB0I11 ((ISRType)145)//145
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_12'">
    #define ISR_TAUB0I12 ((ISRType)146)//146
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_13'">
    #define ISR_TAUB0I13 ((ISRType)147)//147
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_14'">
    #define ISR_TAUB0I14 ((ISRType)148)//148
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_15'">
    #define ISR_TAUB0I15 ((ISRType)149)//149
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='3'">
	#define ISR_CSIH3IC ((ISRType)150)//150
	#define ISR_CSIH3IR ((ISRType)151)//151
	#define ISR_CSIH3IRE ((ISRType)152)//152
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='2'">
	#define ISR_UART2 ((ISRType)156)//156
	#define ISR_UART2_Tx ((ISRType)157)//157
	#define ISR_UART2_Rx ((ISRType)158)//158
	#define ISR_UART2_Error ((ISRType)159)//159
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_0'">
    #define ISR_TAUJ1I0 ((ISRType)160)//160
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_1'">
    #define ISR_TAUJ1I1 ((ISRType)161)//161
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_2'">   
	#define ISR_TAUJ1I2 ((ISRType)162)//162
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_3'">
    #define ISR_TAUJ1I3 ((ISRType)175)//175
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='24'">
    #define SR_PWGA24 ((ISRType)176)//176
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='25'">
    #define SR_PWGA25 ((ISRType)177)//177
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='27'">
    #define SR_PWGA27 ((ISRType)178)//178
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='28'">
    #define SR_PWGA28 ((ISRType)179)//179
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='29'">
    #define SR_PWGA29 ((ISRType)180)//180
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='32'">
    #define SR_PWGA32 ((ISRType)181)//181
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='33'">
    #define SR_PWGA33 ((ISRType)182)//182
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='34'">
    #define SR_PWGA34 ((ISRType)183)//183
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='35'">
    #define SR_PWGA35 ((ISRType)184)//184
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='36'">
   #define SR_PWGA36 ((ISRType)185)//185
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='37'">
    #define SR_PWGA37 ((ISRType)186)//186
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='38'">
    #define SR_PWGA38 ((ISRType)187)//187
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='39'">
    #define SR_PWGA39 ((ISRType)188)//188
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='40'">
    #define SR_PWGA40 ((ISRType)189)//189
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='41'">
    #define SR_PWGA41 ((ISRType)190)//190
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='42'">
    #define SR_PWGA42 ((ISRType)191)//191
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='43'">
    #define SR_PWGA43 ((ISRType)192)//192
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='44'">
    #define SR_PWGA44 ((ISRType)193)//193
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='45'">
    #define SR_PWGA45 ((ISRType)194)//194
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='46'">
    #define SR_PWGA46 ((ISRType)195)//195
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='47'">
	#define SR_PWGA47 ((ISRType)196)//196
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='2'">
	#define ISR_CAN2ERR ((ISRType)209)//209
	#define ISR_CAN2REC ((ISRType)210)/210
	#define ISR_CAN2TRX_Error ((ISRType)211)//211
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='3'">
   	#define ISR_UART3 ((ISRType)220)//220
	#define ISR_UART3_Tx ((ISRType)221)//221
	#define ISR_UART3_Rx ((ISRType)222)//222
	#define ISR_UART3_Error ((ISRType)223)//223
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each> 

#if ((osdSC== SC3) || (osdSC== SC4))
#endif

/* ISR function prototypes */ 
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_0'">
	void ISR_TAUD0I0func(void);//0
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_2'">
	void ISR_TAUD0I2func(void);//1
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_4'">
    void ISR_TAUD0I4func(void);//2
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_6'">
    void ISR_TAUD0I6func(void);//3
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_8'">
    void ISR_TAUD0I8func(void);//4
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_10'">
    void ISR_TAUD0I10func(void);//5
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_12'">
    void ISR_TAUD0I12func(void);//6
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_14'">
    void ISR_TAUD0I14func(void);//7
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'ADC']">
	<xsl:choose>
	<xsl:when test="value='1'">
	void ISR_ADCA1_INTSG1func(void);//10
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'ADC']">
	<xsl:choose>
	<xsl:when test="value='2'">
    void ISR_ADCA2_INTSG1func(void);//11
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'ADC']">
	<xsl:choose>
	<xsl:when test="value='3'">
	void ISR_ADCA3_INTSG1func(void);//12
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='0'or value='1'or value='2'">
	void CanIsrGlobalStatusfunc(void);//14
	void CanIsrRxFifofunc(void);//15
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='0'">
	void CanIsrStatus_0func(void);//16
	void CanIsrWakeup_0func(void);//17
	void CanIsrTx_0func(void);//18
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='0'">
	void CSIH0_Rx_handler(void);//21
    void CSIH0_Tx_handler(void);//22
    void CSIH0_Error_handler(void);//23
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise> 
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='0'">
    void UART0_Handler(void);//25
    void UART0_Tx_Handler(void);//26
    void UART0_Rx_Handler(void);//27
    void UART0_Error_Handler(void);//28
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='0'">
    void ISR_INTP0func(void);//29
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='1'">
    void ISR_INTP1func(void);//30
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='2'">
    void ISR_INTP2func(void);//31
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'WD']">
	<xsl:choose>
	<xsl:when test="value='0'">
    void ISR_WDTA0funcvoid);//32
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'WD']">
	<xsl:choose>
	<xsl:when test="value='1'">
	void ISR_WDTA1func(void);//33
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='3'">
    void ISR_INTP3func(void);//34
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='4'">
    void ISR_INTP4func(void);//35
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='5'">
    void ISR_INTP5func(void);//36
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='10'">
    void ISR_INTP10func(void);//37
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='11'">
	void ISR_INTP11func(void);38
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_1'">
    void ISR_TAUD0I1func(void);//39
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_3'">
    void ISR_TAUD0I3func(void);//40
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_5'">
    void ISR_TAUD0I5func(void);//41
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_7'">
    void ISR_TAUD0I7func(void);//42
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_9'">
    void ISR_TAUD0I9func(void);//43
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_11'">
    void ISR_TAUD0I11func(void);//44
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_13'">
    void ISR_TAUD0I13func(void);//45
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_15'">
    void ISR_TAUD0I15func(void);//46
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='0'">
	//#define ISR_DMA0 ((ISRType)52)//52
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='1'">
    //#define ISR_DMA0 ((ISRType)53)//53
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='2'">
    //#define ISR_DMA0 ((ISRType)54)//54
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='3'">
    //#define ISR_DMA0 ((ISRType)55)//55
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='4'">
    //#define ISR_DMA0 ((ISRType)56)//56
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='5'">
    //#define ISR_DMA0 ((ISRType)57)//57
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='6'">
    //#define ISR_DMA0 ((ISRType)58)//58
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='7'">
    //#define ISR_DMA7 ((ISRType)59)//59
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='8'">
    //#define ISR_DMA8 ((ISRType)60)//60
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='9'">
    //#define ISR_DMA9 ((ISRType)61)//61
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='10'">
    //#define ISR_DMA10 ((ISRType)62)//62
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='11'">
    //#define ISR_DMA11 ((ISRType)64)//64
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='12'">
    //#define ISR_DMA12 ((ISRType)65)//65
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='13'">
    //#define ISR_DMA13 ((ISRType)66)//66
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='14'">
    //#define ISR_DMA14 ((ISRType)67)//67
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'IIC']">
	<xsl:choose>
	<xsl:when test="value='0'">
	void ISR_IIC0RIfunc(void);//68
    void ISR_IIC0TIfunc(void);//69
    void ISR_IIC0TEIfunc(void);//70
    void ISR_IIC0EEfunc(void);//71
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_0'">
    void ISR_TAUJ0I0func(void);//72
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_1'">
    void ISR_TAUJ0I1func(void);//73
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_2'">
    void ISR_TAUJ0I2func(void);//74
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_3'">
    void ISR_TAUJ0I3func(void);//75
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'OS']">
	<xsl:choose>
	<xsl:when test="value='0'">
	void ISR_OSTM0func(void);//76
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='0'">
    //#define ISR_PWGA0 ((ISRType)84)//84
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='1'">
    //#define ISR_PWGA1 ((ISRType)85)//85
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='2'">
    //#define ISR_PWGA2 ((ISRType)86)//86
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='3'">
    //#define ISR_PWGA3 ((ISRType)87)//87
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='8'">
    //#define ISR_PWGA8 ((ISRType)88)//88
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='9'">
    //#define ISR_PWGA9 ((ISRType)89)//89
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='10'">
    //#define ISR_PWGA10 ((ISRType)90)//90
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='11'">
    //#define ISR_PWGA11 ((ISRType)91)//91
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='12'">
    //#define ISR_PWGA12 ((ISRType)92)//92
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='13'">
    //#define ISR_PWGA13 ((ISRType)93)//93
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='14'">
    //#define ISR_PWGA14 ((ISRType)94)//94
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='15'">
    ///#define ISR_PWGA15 ((ISRType)95)//95
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   	<xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='1'">
    void CanIsrStatus_1func(void);//105
	void CanIsrWakeup_1func(void);//106
	void CanIsrTx_1func(void);//107
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='1'">
	void CSIH1_Rx_handler(void);//108
    void CSIH1_Tx_handler(void);//109
    void CSIH1_Error_handler(void);//110
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='1'">
	void UART1_Handler(void);//112
	void UART1_Tx_Handler(void);//113
    void UART1_Rx_Handler(void);//114
    void UART1_Error_Handler(void);//115
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='20'">
    //#define ISR_PWGA20 ((ISRType)116)//116
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='21'">
    //#define ISR_PWGA21 ((ISRType)117)//117
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='22'">
    //#define ISR_PWGA22 ((ISRType)118)//118
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
		<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='23'">
    //#define ISR_PWGA23 ((ISRType)119)//119
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='6'">
	void ISR_INTP6func(void);//120
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='7'">
    void ISR_INTP7func(void);//121
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='8'">
    void ISR_INTP8func(void);//122
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='12'">
    void ISR_INTP12func(void);//123
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='2'">
	void CSIH2_Rx_handler();//124
    void CSIH2_Tx_handler(void);//125
    void CSIH2_Error_handler(void);//126
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_0'">
    void ISR_TAUB0I0func(void);//134
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_1'">
    void ISR_TAUB0I1func(void);//135
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_2'">
    void ISR_TAUB0I2func(void);//136
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_3'">
    void ISR_TAUB0I3func(void);//137
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_4'">
    void ISR_TAUB0I4func(void);//138
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_5'">
    void ISR_TAUB0I5func(void);//139
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_6'">
    void ISR_TAUB0I6func(void);//140
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_7'">
    void ISR_TAUB0I7func(void);//141
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_8'">
    void ISR_TAUB0I8func(void);//142
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_9'">
    void ISR_TAUB0I9func(void);//143
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_10'">
    void ISR_TAUB0I10func(void);//144
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_11'">
    void ISR_TAUB0I11func(void);//145
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_12'">
    void ISR_TAUB0I12func(void);//146
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_13'">
    void ISR_TAUB0I13func(void);//147
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_14'">
    void ISR_TAUB0I14func(void);//148
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_15'">
    void ISR_TAUB0I15func(void);//149
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='3'">
    void CSIH3_Rx_handler();//150
    void CSIH3_Tx_handler(void);//151
    void CSIH3_Error_handler(void);//152
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='2'">
	void UART2_Handler(void);//156
	void UART2_Tx_Handler(void);//157
    void UART2_Rx_Handler(void);//158
    void UART2_Error_Handler(void);//159
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_0'">
    void ISR_TAUJ1I0func(void);//160
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_1'">
    void ISR_TAUJ1I1func(void);//161
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_2'">   
	void ISR_TAUJ1I2func(void);//162
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_3'">
    void ISR_TAUJ1I3func(void);//175
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='24'">
    //#define SR_PWGA24 ((ISRType)176)//176
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='25'">
    //#define SR_PWGA25 ((ISRType)177)//177
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='27'">
    //#define SR_PWGA27 ((ISRType)178)//178
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='28'">
    //#define SR_PWGA28 ((ISRType)179)//179
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='29'">
    //#define SR_PWGA29 ((ISRType)180)//180
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='32'">
    //#define SR_PWGA32 ((ISRType)181)//181
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='33'">
    //#define SR_PWGA33 ((ISRType)182)//182
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='34'">
    //#define SR_PWGA34 ((ISRType)183)//183
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='35'">
    //#define SR_PWGA35 ((ISRType)184)//184
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='36'">
    //#define SR_PWGA36 ((ISRType)185)//185
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='37'">
    //#define SR_PWGA37 ((ISRType)186)//186
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='38'">
    //#define SR_PWGA38 ((ISRType)187)//187
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='39'">
    //#define SR_PWGA39 ((ISRType)188)//188
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='40'">
    //#define SR_PWGA40 ((ISRType)189)//189
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='41'">
    //#define SR_PWGA41 ((ISRType)190)//190
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='42'">
    //#define SR_PWGA42 ((ISRType)191)//191
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='43'">
    //#define SR_PWGA43 ((ISRType)192)//192
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='44'">
    //#define SR_PWGA44 ((ISRType)193)//193
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='45'">
    //#define SR_PWGA45 ((ISRType)194)//194
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='46'">
    //#define SR_PWGA46 ((ISRType)195)//195
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='47'">
	//#define SR_PWGA47 ((ISRType)196)//196
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='2'">
	void CanIsrStatus_2func(void);//209
	void CanIsrWakeup_2func(void);//210
	void CanIsrTx_2func(void);//211
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='3'">
  	void UART1_Handler(void);//220
	void UART1_Tx_Handler(void);//221
    void UART1_Rx_Handler(void);//222
    void UART1_Error_Handler(void);//223
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each> 
#if (osdNumberOfAlarms > 0)
 osqROM0 extern osqROM1 const osqROM2 osuint8 osqROM3 oskAlarmAutoStart[osdNumberOfAlarms];
#endif

#if (osdNumberOfAlarms > 0)
extern osqROM0 osqROM1 const osqROM2 osuint8 osqROM3 oskAlarmAutoStartType  [osdNumberOfAlarms];
#endif

#if (osdNumberOfAllTasks > 0)
 osqROM0 extern osqROM1 const osqROM2 osuint8 osqROM3 oskTcbAutoStart[osdNumberOfAllTasks];
#endif

#define osdNumberOfAppModes 1
#define OSDEFAULTAPPMODE 1
/* Events */ 
#define EventTskEvt ((EventMaskType)(0x01))
#define FastCycEvt ((EventMaskType)(0x01))
#define SlowCycEvt ((EventMaskType)(0x01))
#define SlowJobEvt ((EventMaskType)(0x01))
#define SysSwitchHiEvt ((EventMaskType)(0x01))
#define SysSwitchLoEvt ((EventMaskType)(0x01))
/* Alarms */ 
/* prototypes for alarm callback functions */

#pragma ghs startdata
/* MISRA RULE 8.12 VIOLATION: (2 times) The compiler requires the [] notation and the size of the 
   sections is unknown at generation time. No problem because the symbols are never used as arrays. */
extern osuint32 osExceptionVectorTable_c0[]; /* PRQA S 3684 */
extern osuint32 osEIINTVectorTable_c0[]; /* PRQA S 3684 */
#pragma ghs enddata

#if (osdKillTaskIsrPossible || (osdSC== SC3) || (osdSC== SC4))
#if (osdNumberOfAllTasks > 0)
   extern osqTcbRAM1 osqTcbRAM2 osResourceIndexType osqTcbRAM3 osTcbLockedResource[osdNumberOfAllTasks];
#else
   extern osqTcbRAM1 osqTcbRAM2 osResourceIndexType osqTcbRAM3 osTcbLockedResource[1];
#endif
#endif
/* Resources */



#if (STATUS_LEVEL == EXTENDED_STATUS) <xsl:text disable-output-escaping="yes">&amp;</xsl:text><xsl:text disable-output-escaping="yes">&amp;</xsl:text> osdEnableAssertions
 #if ((!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed)))
osqROM0 extern osqROM1 const osqROM2 osResAccessMaskType osqROM3 oskResAccessMask[1][1];


 #endif /* ((!defined(osdGetResourceNotUsed)) || (!defined(osdReleaseResourceNotUsed))) */
#endif /* (STATUS_LEVEL == EXTENDED_STATUS)<xsl:text disable-output-escaping="yes">&amp;</xsl:text><xsl:text disable-output-escaping="yes">&amp;</xsl:text>osdEnableAssertions */

#if (osdKillTaskIsrPossible || (osdSC == SC3) || (osdSC == SC4))
#if (osdNumberOfAllResources > 0)
   extern osqTcbRAM1 osqTcbRAM2 osResourceIndexType osqTcbRAM3 osResNextLockedResource[osdNumberOfAllResources];
#else
   extern osqTcbRAM1 osqTcbRAM2 osResourceIndexType osqTcbRAM3 osResNextLockedResource[1];
#endif
#endif


#if ((osdSC== SC3) || (osdSC== SC4))
#endif


/* END OF D:\AutoSar generated code\tcb.h */

#endif /* ! defined __TCBPOST_H__ */
</xsl:template>   
</xsl:stylesheet>
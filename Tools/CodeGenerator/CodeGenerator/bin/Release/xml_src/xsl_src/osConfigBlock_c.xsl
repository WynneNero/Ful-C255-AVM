<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text" indent="yes" encoding="ISO-8859-1"/>
<xsl:template match="/">
/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *				  
*   All Rights Reserved.                                               *                                    					   
*   Department : RN RD SW1                                             *      									  
*   AUTHOR     : Shao Guangxian                                        *
************************************************************************
* Object        :  osConfigBlock.c
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

#if defined USE_QUOTE_INCLUDES
 #include "osStacks.h"
#else
 #include <xsl:text disable-output-escaping="yes">&lt;</xsl:text>osStacks.h<xsl:text disable-output-escaping="yes">&gt;</xsl:text>
#endif

#if defined USE_QUOTE_INCLUDES
 #include "Os.h"
#else
 #include <xsl:text disable-output-escaping="yes">&lt;</xsl:text>Os.h<xsl:text disable-output-escaping="yes">&gt;</xsl:text>
#endif

#if defined USE_QUOTE_INCLUDES
 #include "osekext.h"
#else
 #include <xsl:text disable-output-escaping="yes">&lt;</xsl:text>osekext.h<xsl:text disable-output-escaping="yes">&gt;</xsl:text>
#endif

#pragma ghs section rodata=".os_rodata"
#pragma ghs section rosdata=".os_rosdata"

/* MISRA RULE 8.10 VIOLATION: osConfigBlock is accessed by several modules in many configurations.
*  Declaring this variable static in the other cases would increase code complexity too much.
*/
osqROM0 osqROM1 const osqROM2 tsConfigBlock osqROM3 osConfigBlock = /* PRQA S 1504 */ 
{
   /* Frame */
   {0x82, 0x2A, 0x0C, 0xC4}, /* aucMagicNumber */
   (osuint16)((((sizeof(osConfigBlock))  <xsl:text disable-output-escaping="yes">&amp;</xsl:text> 0xFF)  <xsl:text disable-output-escaping="yes">&lt;</xsl:text><xsl:text disable-output-escaping="yes">&lt;</xsl:text> 8)|
              (( sizeof(osConfigBlock))         >> 8)), /* Length (little endian) */
   9,
   osdVrmMajRelNumRef,    /* MajorVersion */
   osdVrmMinRelNumRef,    /* MinorVersion */
   (osuint16)3,           /* ConfigBlockVersion */
   (osuint16)1, /* UserConfigVersion */
   /* cargo --------------------------------------------------------------- */
   <xsl:text disable-output-escaping="yes">&amp;</xsl:text>osConfigBlock,
   /* start addresses of sub-containers (fixed number) */
    <xsl:text disable-output-escaping="yes">&amp;</xsl:text>(osConfigBlock.uiNumberOfTasks),        /* Sub-Container 0 */
   (osConfigBlock.aulTaskStartAddress),     /* Sub-Container 1 */
   (osConfigBlock.aucTaskPreemptive),       /* Sub-Container 2 */
   (osConfigBlock.aucTaskTrusted),          /* Sub-Container 3 */
   (osConfigBlock.aulTaskStackStartAddress),/* Sub-Container 4 */
   (osConfigBlock.aulTaskStackEndAddress),  /* Sub-Container 5 */
   (osConfigBlock.acTaskToAppl),            /* Sub-Container 6 */
   (osConfigBlock.aucIsrTrusted),           /* Sub-Container 7 */
   (osConfigBlock.acIsrToAppl),             /* Sub-Container 8 */
   (osConfigBlock.applTrusted),             /* Sub-Container 9 */
   (osConfigBlock.trustedFunctions),        /* Sub-Container 10 */
   (osConfigBlock.nonTrustedFunctions),     /* Sub-Container 11 */
   (osConfigBlock.cat2IsrStartAddress),     /* Sub-Container 12 */
   (osConfigBlock.IsrNestable),             /* Sub-Container 13 */
   (osConfigBlock.ProcessToCore),           /* Sub-Container 14 */
   (osConfigBlock.AlarmToCore),             /* Sub-Container 15 */
   (osConfigBlock.ResourceToCore),          /* Sub-Container 16 */
   (osConfigBlock.CounterToCore),           /* Sub-Container 17 */
   (osConfigBlock.ScheduleTableToCore),     /* Sub-Container 18 */
   (osConfigBlock.ApplicationToCore),       /* Sub-Container 19 */
   (osConfigBlock.TrustedFunctionToCore),   /* Sub-Container 20 */
   (osConfigBlock.NonTrustedFunctionToCore),/* Sub-Container 21 */
   (osConfigBlock.CcbAddress),              /* Sub-Container 22 */
   (osConfigBlock.peripheralRegions),       /* Sub-Container 23 */
   (osConfigBlock.SpinlockLockMethods),     /* Sub-Container 24 */
   (osConfigBlock.SpinlockLockTypes),       /* Sub-Container 25 */
   (osConfigBlock.OptimizedSpinlockVars),   /* Sub-Container 26 */
   (osConfigBlock.osCat2IsrStacks),         /* Sub-Container 27 */
   (osConfigBlock.osIsrChannel),            /* Sub-Container 28 */
   (osConfigBlock.osIsrPrioLevel),          /* Sub-Container 29 */
   (osConfigBlock.osIsrToCore),             /* Sub-Container 30 */
   /* Sub-Container 0 */
   osdNumberOfAllTasks,
   osdNumberOfCat2ISRs,
   osdNumberOfTrustedFunctions,
   0,
   osdNumberOfApplications,
   0,
   osdStackUsageMeasurement,
   osdNumberOfAlarms,
   osdNumberOfAllResources,
   osdNumberOfAvailableCores,
   osdNumberOfCounters,
   osdNumberOfProcesses,
   osdNumberOfScheduleTables,
   0,

   {
      {(osStackPtrType)osdSystemStack_c0_BOT, (osStackPtrType)osdSystemStack_c0_TOP},
   },
 /* Sub-Container 1, task start addresses */
   {       
      <xsl:text disable-output-escaping="yes">&amp;</xsl:text>BasicTaskEntry,		
      <xsl:text disable-output-escaping="yes">&amp;</xsl:text>BasicTaskEntry,
    //<xsl:text disable-output-escaping="yes">&amp;</xsl:text>BasicTaskEntry,
      <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ExtendTaskEntry,
      <xsl:text disable-output-escaping="yes">&amp;</xsl:text>BasicTaskEntry,
    //<xsl:text disable-output-escaping="yes">&amp;</xsl:text>BasicTaskEntry,
      <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ExtendTaskEntry,
      <xsl:text disable-output-escaping="yes">&amp;</xsl:text>BasicTaskEntry,
      <xsl:text disable-output-escaping="yes">&amp;</xsl:text>InitTaskEntry,
       /*
      <xsl:text disable-output-escaping="yes">&amp;</xsl:text>SystemSwitchHighfunc,
      <xsl:text disable-output-escaping="yes">&amp;</xsl:text>FastCyclicfunc,
      <xsl:text disable-output-escaping="yes">&amp;</xsl:text>EventTaskfunc,
      <xsl:text disable-output-escaping="yes">&amp;</xsl:text>SlowCyclicfunc,
      <xsl:text disable-output-escaping="yes">&amp;</xsl:text>SlowJobfunc,
      <xsl:text disable-output-escaping="yes">&amp;</xsl:text>SystemSwitchLowfunc,
      <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ResetTaskfunc,
      */
      (osTaskFctType)0//
   },
    /* Sub-Container 2, task preemptiveness */
   {
      osdTaskTypePreempt,
      osdTaskTypePreempt,
      osdTaskTypePreempt,
      osdTaskTypePreempt,
      osdTaskTypePreempt,
      osdTaskTypePreempt,
      osdTaskTypePreempt,
      0
   },
    /* Sub-Container 3, task trusted */
   {
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0
   },
   /* Sub-Container 4, stack start address */
   {
      (osStackPtrType)osdSystemSwitchHigh_BOT,
      (osStackPtrType)osdFastCyclic_BOT,
      (osStackPtrType)osdEventTask_BOT,
      (osStackPtrType)osdSlowCyclic_BOT,
      (osStackPtrType)osdSlowJob_BOT,
      (osStackPtrType)osdSystemSwitchLow_BOT,
      (osStackPtrType)osdResetTask_BOT,
      (osStackPtrType)0
   },
    /* Sub-Container 5, stack end addresses */
   {
      (osStackPtrType)osdSystemSwitchHigh_TOP,
      (osStackPtrType)osdFastCyclic_TOP,
      (osStackPtrType)osdEventTask_TOP,
      (osStackPtrType)osdSlowCyclic_TOP,
      (osStackPtrType)osdSlowJob_TOP,
      (osStackPtrType)osdSystemSwitchLow_TOP,
      (osStackPtrType)osdResetTask_TOP,
      (osStackPtrType)0
   },
   /* Sub-Container 6, translation table: task -> os-application */
   {
      INVALID_OSAPPLICATION,
      INVALID_OSAPPLICATION,
      INVALID_OSAPPLICATION,
      INVALID_OSAPPLICATION,
      INVALID_OSAPPLICATION,
      INVALID_OSAPPLICATION,
      INVALID_OSAPPLICATION,
      INVALID_OSAPPLICATION
   },
   /* Sub-Container 7, isr trusted */
   {
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='0'or value='1'or value='2'">
     0,
	 0,
	 </xsl:when>
     <xsl:otherwise>
     </xsl:otherwise>
     </xsl:choose>
	 </xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'Count']/value_count">
	 0,
	 </xsl:for-each>
	 0
   },
   /* Sub-Container 8, translation table: isr -> os-application */
   {     
      <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	  <xsl:choose>
	 <xsl:when test="value='0'or value='1'or value='2'">
      INVALID_OSAPPLICATION,
	  INVALID_OSAPPLICATION,
	 </xsl:when>
     <xsl:otherwise>
     </xsl:otherwise>
     </xsl:choose>
	 </xsl:for-each>
       <xsl:for-each select="IRQ_Set/FUN[@Register = 'Count']/value_count">
	  INVALID_OSAPPLICATION,
	  </xsl:for-each>
	  INVALID_OSAPPLICATION
   },
   /* Sub-Container 9, is application trusted information */
   {
      0
   },
   /* Sub-Container 10, trusted functions */
   {
      0
   },
   /* Sub-Container 11, non trusted functions */
   {
      0
   },
   /* Sub-Container 12, Cat 2 ISR start addresses */
   {
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_0'">
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUD0I0func,//0
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_2'">
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUD0I2func,/1
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_4'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUD0I4func,//2
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_6'">
    <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUD0I6func,//3
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_8'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUD0I8func,//4
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_10'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUD0I10func,//5
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_12'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUD0I12func,//6
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_14'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUD0I14func,//7
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'ADC']">
	<xsl:choose>
	<xsl:when test="value='1'">
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_ADCA1_INTSG1func,//10
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'ADC']">
	<xsl:choose>
	<xsl:when test="value='2'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_ADCA2_INTSG1func,/11
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'ADC']">
	<xsl:choose>
	<xsl:when test="value='3'">
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_ADCA3_INTSG1func,//12
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	  <xsl:choose>
	 <xsl:when test="value='0'or value='1'or value='2'">
      <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CanIsrGlobalStatusfunc,//14
	  <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CanIsrRxFifofunc,//15
	 </xsl:when>
     <xsl:otherwise>
     </xsl:otherwise>
     </xsl:choose>
	 </xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='0'">
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CanIsrStatus_0func,//16
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CanIsrWakeup_0func,//17
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CanIsrTx_0func,//18
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='0'">
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CSIH0_Rx_handler//21
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CSIH0_Tx_handler,//22
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CSIH0_Error_handler,//23
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise> 
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='0'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>UART0_Handler,//25
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>UART0_Tx_Handler,//26
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>UART0_Rx_Handler(//27
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>UART0_Error_Handler,//28
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='0'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_INTP0func,//29
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='1'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_INTP1func,//30
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='2'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_INTP2func,//31
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'WD']">
	<xsl:choose>
	<xsl:when test="value='0'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_WDTA0func,//32
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'WD']">
	<xsl:choose>
	<xsl:when test="value='1'">
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_WDTA1func,//33
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='3'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_INTP3func,//34
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='4'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_INTP4func,//35
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='5'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_INTP5func,//36
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='10'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_INTP10func,//37
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='11'">
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_INTP11func,//38
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_1'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUD0I1func,//39
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_3'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUD0I3func,//40
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_5'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUD0I5func,//41
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_7'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUD0I7func,//42
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_9'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUD0I9func,//43
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_11'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>SR_TAUD0I11func,//44
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_13'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUD0I13func,//45
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_15'">
    //#define ISR_TAUD0I15 ((ISRType)46)//46
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
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_IIC0RIfunc,//68
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_IIC0TIfunc,//69
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_IIC0TEIfunc,//70
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_IIC0EEfunc,//71
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_0'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUJ0I0func,//72
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_1'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUJ0I1func,//73
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_2'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUJ0I2func,//74
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_3'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUJ0I3func,//75
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'OS']">
	<xsl:choose>
	<xsl:when test="value='0'">
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_OSTM0func,//76
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
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CanIsrStatus_1func,//105
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CanIsrWakeup_1func,//106
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CanIsrTx_1func,//107
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='1'">
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CSIH1_Rx_handler,//108
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CSIH1_Tx_handler,//109
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CSIH1_Error_handler,//110
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='1'">
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>UART1_Handler,//112
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>UART1_Tx_Handler,//113
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>UART1_Rx_Handler,//114
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>UART1_Error_Handler,//115
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
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_INTP6func,//120
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='7'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_INTP7func,//121
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='8'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_INTP8func,//122
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='12'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_INTP12func,//123
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='2'">
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CSIH2_Rx_handler,//124
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CSIH2_Tx_handler,//125
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CSIH2_Error_handler,//126
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_0'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUB0I0func,//134
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_1'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUB0I1func,//135
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_2'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUB0I2func,//136
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_3'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUB0I3func,//137
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_4'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUB0I4func,//138
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_5'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUB0I5func,//139
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_6'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUB0I6func,//140
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_7'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUB0I7func,//141
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_8'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUB0I8func,//142
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_9'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUB0I9func,//143
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_10'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUB0I10func,//144
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_11'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUB0I11func,//145
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_12'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUB0I12func,//146
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_13'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUB0I13func,//147
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_14'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUB0I14func,//148
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_15'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUB0I15func,//149
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='3'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CSIH3_Rx_handler,//150
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CSIH3_Tx_handler,//151
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CSIH3_Error_handler,//152
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='2'">
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>UART2_Handler,//156
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>UART2_Tx_Handler,//157
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>UART2_Rx_Handler,//158
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>UART2_Error_Handler,//159
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_0'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUJ1I0func,//160
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_1'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUJ1I1func,//161
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_2'">   
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUJ1I2func,//162
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_3'">
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>ISR_TAUJ1I3func,//175
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='24'">
    //#define ISR_PWGA24 ((ISRType)176)//176
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='25'">
    //#define ISR_PWGA25 ((ISRType)177)//177
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='27'">
    //#define ISR_PWGA27 ((ISRType)178)//178
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='28'">
    //#define ISR_PWGA28 ((ISRType)179)//179
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='29'">
    //#define ISR_PWGA29 ((ISRType)180)//180
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='32'">
    //#define ISR_PWGA32 ((ISRType)181)//181
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='33'">
    //#define ISR_PWGA33 ((ISRType)182)//182
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='34'">
    //#define ISR_PWGA34 ((ISRType)183)//183
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='35'">
    //#define ISR_PWGA35 ((ISRType)184)//184
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='36'">
    //#define ISR_PWGA36 ((ISRType)185)//185
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='37'">
    //#define ISR_PWGA37 ((ISRType)186)//186
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='38'">
    //#define ISR_PWGA38 ((ISRType)187)//187
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='39'">
    //#define ISR_PWGA39 ((ISRType)188)//188
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='40'">
    //#define ISR_PWGA40 ((ISRType)189)//189
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='41'">
    //#define ISR_PWGA41 ((ISRType)190)//190
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='42'">
    //#define ISR_PWGA42 ((ISRType)191)//191
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='43'">
    //#define ISR_PWGA43 ((ISRType)192)//192
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='44'">
    //#define ISR_PWGA44 ((ISRType)193)//193
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='45'">
    //#define ISR_PWGA45 ((ISRType)194)//194
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='46'">
    //#define ISR_PWGA46 ((ISRType)195)//195
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='47'">
	//#define ISR_PWGA47 ((ISRType)196)//196
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='2'">
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CanIsrStatus_2func,//209
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CanIsrWakeup_2func,//210
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>CanIsrTx_2func,//211
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='3'">
  	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>UART1_Handler,//220
	 <xsl:text disable-output-escaping="yes">&amp;</xsl:text>UART1_Tx_Handler,//221
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>UART1_Rx_Handler,//222
     <xsl:text disable-output-escaping="yes">&amp;</xsl:text>UART1_Error_Handler,//223
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each> 
      (osIsrFctType)0
   },
     /* Sub-Container 13, Cat 2 ISR nestable */
   {
      osdFALSE, 
	  osdFALSE, 
	   <xsl:for-each select="IRQ_Set/FUN[@Register = 'Count']/value_count">
	  osdFALSE,
	  </xsl:for-each>
      (osuint8)0
   },
   /* Sub-Container 14, ProcessToCore */
   {
      0U, /* TASK SystemSwitchHigh */
      0U, /* TASK FastCyclic */
      0U, /* TASK EventTask */
      0U, /* TASK SlowCyclic */
      0U, /* TASK SlowJob */
      0U, /* TASK SystemSwitchLow */
      0U, /* TASK ResetTask */
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='0'or value='1'or value='2'">
      0U,
	  0U,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	  <xsl:for-each select="IRQ_Set/FUN[@Register = 'Count']/value_count">
	  0U,
	  </xsl:for-each> 
      (CoreIdType)0
   },
   /* Sub-Container 15, AlarmToCore */
   {
      (CoreIdType)0
   },
   /* Sub-Container 16, ResourceToCore */
   {
      (CoreIdType)0
   },
   /* Sub-Container 17, CounterToCore */
   {
      (CoreIdType)0
   },
   /* Sub-Container 18, ScheduleTableToCore */
   {
      (CoreIdType)0
   },
   /* Sub-Container 19, ApplicationToCore */
   {
      (CoreIdType)0
   },
   /* Sub-Container 20, TrustedFunctionToCore */
   {
      (CoreIdType)0
   },
   /* Sub-Container 21, NonTrustedFunctionToCore */
   {
      (CoreIdType)0
   },
   /* Sub-Container 22, Core Control Block addresses */
   {
       <xsl:text disable-output-escaping="yes">&amp;</xsl:text>osCtrlVarsCore0,
      (osCtrlVarType*)0
   },
   /* Sub-Container 23, peripheral regions */
   {
      0
   },
   /* Sub-Container 24, Spinlock lock method */
   {
      (osuint8)0
   },
   /* Sub-Container 25, Spinlock lock type */
   {
      (osuint8)0
   },
   /* Sub-Container 26, Optimized Spinlock variables */
   {
      (osMiniLockType*) osdNULL
   },
     /* Sub-Container 27 ISR stack information */
   {
      <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='0'or value='1'or value='2'">
      {
         (osStackPtrType)osdISR_ADD_BOT,
         (osStackPtrType)osdISR_ADD_TOP
      },
      {
         (osStackPtrType)osdISR_ADD_BOT,
         (osStackPtrType)osdISR_ADD_TOP
      },
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	   <xsl:for-each select="IRQ_Set/FUN[@Register = 'Count']/value_count">
	  {
        (osStackPtrType)osdISR_ADD_BOT,
        (osStackPtrType)osdISR_ADD_TOP
      },
	  </xsl:for-each>    
      {
         (osStackPtrType)0,
         (osStackPtrType)0
      }
   },
      /* Sub-Container 28: ISR interrupt channel index */
   {
      <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_0'">
    (osuint16) 0,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_2'">
    (osuint16) 1,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_4'">
    (osuint16) 2,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_6'">
    (osuint16) 3,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_8'">
    (osuint16) 4,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_10'">
    (osuint16) 5,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_12'">
    (osuint16) 6,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_14'">
    (osuint16) 7,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'ADC']">
	<xsl:choose>
	<xsl:when test="value='1'">
    (osuint16) 10,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'ADC']">
	<xsl:choose>
	<xsl:when test="value='2'">
    (osuint16) 11,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'ADC']">
	<xsl:choose>
	<xsl:when test="value='3'">
	(osuint16) 12,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='0'or value='1'or value='2'">
    (osuint16) 14,
	(osuint16) 15,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='0'">
    (osuint16) 16,
	(osuint16) 17,
	(osuint16) 18,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='0'">
	(osuint16) 21,
	(osuint16) 22,
	(osuint16) 23,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise> 
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='0'">
	(osuint16) 25,
	(osuint16) 26,
	(osuint16) 27,
	(osuint16) 28,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='0'">
    (osuint16) 29,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='1'">
    (osuint16) 30,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='2'">
    (osuint16) 31,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'WD']">
	<xsl:choose>
	<xsl:when test="value='0'">
    (osuint16) 32,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
      <xsl:for-each select="IRQ_Set/FUN[@Register = 'WD']">
	<xsl:choose>
	<xsl:when test="value='1'">
	(osuint16) 33,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='3'">
    (osuint16) 34,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='4'">
    (osuint16) 35,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='5'">
    (osuint16) 36,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='10'">
    (osuint16) 37,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='11'">
	(osuint16) 38,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_1'">
    (osuint16) 39,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_3'">
    (osuint16) 40,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_5'">
    (osuint16) 41,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_7'">
    (osuint16) 42,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_9'">
    (osuint16) 43,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_11'">
    (osuint16) 44,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_13'">
    (osuint16) 45,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_15'">
    (osuint16) 46,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='0'">
    (osuint16) 52,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='1'">
    (osuint16) 53,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='2'">
    (osuint16) 54,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='3'">
    (osuint16) 55,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='4'">
    (osuint16) 56,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='5'">
    (osuint16) 57,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='6'">
    (osuint16) 58,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='7'">
    (osuint16) 59,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='8'">
    (osuint16) 60,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='9'">
    (osuint16) 61,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='10'">
    (osuint16) 62,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='11'">
    (osuint16) 64,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='12'">
    (osuint16) 65,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='13'">
    (osuint16) 66,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='14'">
    (osuint16) 67,
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'IIC']">
	<xsl:choose>
	<xsl:when test="value='0'">
    (osuint16) 68,
	(osuint16) 69,
	(osuint16) 70,
	(osuint16) 71
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_0'">
    (osuint16) 72
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_1'">
    (osuint16) 73
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_2'">
    (osuint16) 74
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_3'">
    (osuint16) 75
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'OS']">
	<xsl:choose>
	<xsl:when test="value='0'">
	(osuint16) 76
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='0'">
    (osuint16) 84
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='1'">
    (osuint16) 85
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='2'">
    (osuint16) 86
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='3'">
    (osuint16) 87
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='8'">
    (osuint16) 88
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='9'">
    (osuint16) 89
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='10'">
    (osuint16) 90
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='11'">
    (osuint16) 91
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='12'">
    (osuint16) 92
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='13'">
    (osuint16) 93
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='14'">
    (osuint16) 94
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='15'">
    (osuint16) 95
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   	<xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='1'">
    (osuint16) 105
	(osuint16) 106
	(osuint16) 107
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='1'">
	(osuint16) 108
	(osuint16) 109
	(osuint16) 110
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='1'">
    (osuint16) 112
	(osuint16) 113
	(osuint16) 114
	(osuint16) 115
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='20'">
    (osuint16) 116
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='21'">
    (osuint16) 117
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='22'">
    (osuint16) 118
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
		<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='23'">
    (osuint16) 119
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='6'">
	(osuint16) 120
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='7'">
    (osuint16) 121
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='8'">
    (osuint16) 122
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='12'">
    (osuint16) 23
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='2'">
	(osuint16) 124
	(osuint16) 125
	(osuint16) 126
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_0'">
    (osuint16) 134
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_1'">
    (osuint16) 135
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_2'">
    (osuint16) 136
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_3'">
    (osuint16) 137
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_4'">
    (osuint16) 138
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_5'">
    (osuint16) 139
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_6'">
    (osuint16) 140
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_7'">
    (osuint16) 141
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_8'">
    (osuint16) 142
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_9'">
    (osuint16) 143
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_10'">
    (osuint16) 144
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_11'">
    (osuint16) 145
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_12'">
    (osuint16) 146
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_13'">
    (osuint16) 147
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_14'">
    (osuint16) 148
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_15'">
    (osuint16) 2149
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='3'">
	(osuint16) 150
	(osuint16) 151
	(osuint16) 152
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='2'">
    (osuint16) 156
	(osuint16) 157
	(osuint16) 158
	(osuint16) 159
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_0'">
    (osuint16) 160
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_1'">
    (osuint16) 161
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_2'">
    (osuint16) 162
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_3'">
    (osuint16) 175
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='24'">
    (osuint16) 176
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='25'">
    (osuint16) 177
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='27'">
    (osuint16) 178
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='28'">
    (osuint16) 179
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='29'">
    (osuint16) 180
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='32'">
    (osuint16) 181
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='33'">
    (osuint16) 182
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='34'">
    (osuint16) 183
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='35'">
    (osuint16) 184
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='36'">
    (osuint16) 185
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='37'">
    (osuint16) 186
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='38'">
    (osuint16) 187
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='39'">
    (osuint16) 188
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='40'">
    (osuint16) 189
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='41'">
    (osuint16) 190
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='42'">
    (osuint16) 191
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='43'">
    (osuint16) 192
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='44'">
    (osuint16) 193
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='45'">
    (osuint16) 194
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='46'">
    (osuint16) 195
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='47'">
	(osuint16) 196
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='2'">
	(osuint16) 209
	(osuint16) 210
	(osuint16) 211
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='3'">
    (osuint16) 220
	(osuint16) 221
	(osuint16) 222
	(osuint16) 223
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>           
    (osuint16)  0  /* empty */
   },
      /* Sub-Container 29: ISR interrupt priority level */
   {
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='0'or value='1'or value='2'">
      (osuint16)0x0001, 
      (osuint16)0x0001, 
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
       <xsl:for-each select="IRQ_Set/FUN[@Register = 'Count']/value_count">
	  (osuint16)0x0001,
	  </xsl:for-each>   	             
      (osuint16)0x0000  /* empty */
   },

   /* Sub-Container 30: ISR to Core assignment */
   {
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='0'or value='1'or value='2'">
      0U,
      0U, 
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
      <xsl:for-each select="IRQ_Set/FUN[@Register = 'Count']/value_count">
	  0U,
	  </xsl:for-each>   	     		                                       
      0U  /* empty */
   },
   (osuint32)0 /* uiCheckSum */
};

#pragma ghs section rodata=default
#pragma ghs section rosdata=default
 
</xsl:template>
</xsl:stylesheet>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text" indent="yes" encoding="ISO-8859-1"/>
<xsl:template match="/">   
/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *				  
*   All Rights Reserved.                                               *                                    					   
*   Department : RN RD SW1                                             *      									  
*   AUTHOR     : Shao Guangxian                                        *
************************************************************************
* Object        :  tcb.h
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
#if ! defined __TCB_H__   /* PRQA S 0883 EOF */ 
#define __TCB_H__
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
 
#define osdNumberOfAlarmsOnHiResCounter 0

#define osdUseHighResolutionTimer 0

#define osdHwTimerNeeded_OSTM 0 // 1	//open OSTM		//	0		
#define osdHwTimerNeeded_OSTM_HIRES 0

#define osdHardwareTimerNeeded 0 // 1	//open OSTM		//	0
#define osdGetCurrentTimeHighResHybridIdx -1
#define osdGetCurrentTimeHighResMonoIdx -1
#define osdGetCurrentTimeStdIdx -1
#define osdSetTIPAbsMaxGtSemiCountIdx -1
#define osdSetTIPAbsMaxLeSemiCountIdx -1
#define osdSetTIPRelMaxGtSemiCountIdx -1
#define osdSetTIPRelMaxLeSemiCountIdx -1
#define osdClearTIPAbsIdx -1
#define osdClearTIPRelIdx -1
#define osdHandleCounterInterruptHiResIdx -1
#define osdHandleCounterInterruptStdIdx -1
#define osdInsertMinHeapHiResIdx -1
#define osdInsertMinHeapStdIdx -1
#define osdORTIDebug 0
#define osdORTIVersion  not used anymore!
#define osdORTIStdVersion 210
#define osdORTIEnabled 1
#define osdNumberOfScheduleTables 0
#define osdNumberOfHiResSchedTabs 0
#define osdScheduleTableSyncUsed 0
#define osdNumberOfSTExpiryPoints 0
#define osdNumberOfSTSetEvent 0
#define osdNumberOfSTActivateTask 0
#define osdNumberOfSTEntries 0
#define osdCallTimingHooks 1
#define osdTimingHooksFileName "TimingHook.h"
#define osdRH850_F1L		//osdRH850_D1M

#define osdExceptionDetails  1
#define osdRH850_FPU   0
 
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_0'">
	#define ISR_TAUD0I0_index  0//0
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_2'">
	#define ISR_TAUD0I2_index  1//1
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_4'">
    #define ISR_TAUD0I4_index  2//2
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_6'">
    #define ISR_TAUD0I6_index  3//3
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_8'">
    #define ISR_TAUD0I8_index  4//4
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_10'">
    #define ISR_TAUD0I10_index  5//5
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_12'">
    #define ISR_TAUD0I12_index  6//6
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_14'">
    #define ISR_TAUD0I14_index  7//7
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'ADC']">
	<xsl:choose>
	<xsl:when test="value='1'">
	#define ISR_ADCA0_INTSG1_index  10//10
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'ADC']">
	<xsl:choose>
	<xsl:when test="value='2'">
    #define ISR_ADCA0_INTSG2_index  11//11
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'ADC']">
	<xsl:choose>
	<xsl:when test="value='3'">
	#define ISR_ADCA0_INTSG3_index  12//12
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='0'or value='1'or value='2'">
	#define ISR_CANGERR_index  14//14
	#define ISR_CANGRECC_index  15//15
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='0'">
	#define ISR_CAN0ERR_index  16//16
	#define ISR_CAN0REC_index  17//17
	#define ISR_CAN0TRX_index  18//18
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='0'">
	#define ISR_CSIH0IC_index  21//21
	#define ISR_CSIH0IR_index  22//22
	#define ISR_CSIH0IRE_index 23//23
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise> 
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='0'">
	#define ISR_UART0_index  25//25
	#define ISR_UART0_Tx_index  26//26
	#define ISR_UART0_Rx_index  27//27
	#define ISR_UART0_Error_index  28//28
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='0'">
    #define ISR_INTP0_index  29//29
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='1'">
    #define ISR_INTP1_index  30//30
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='2'">
    #define ISR_INTP2_index  31//31
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'WD']">
	<xsl:choose>
	<xsl:when test="value='0'">
    #define ISR_WDTA0_index  32//32
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
      <xsl:for-each select="IRQ_Set/FUN[@Register = 'WD']">
	<xsl:choose>
	<xsl:when test="value='1'">
	#define ISR_WDTA1_index  33//33
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='3'">
    #define ISR_INTP3_index  34//34
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='4'">
    #define ISR_INTP4_index  35//35
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='5'">
    #define ISR_INTP5_index  36//36
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='10'">
    #define ISR_INTP10_index  37//37
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='11'">
	#define ISR_INTP11_index  38//38
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_1'">
    #define ISR_TAUD0I1_index  39//39
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_3'">
    #define ISR_TAUD0I3_index  40//40
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_5'">
    #define ISR_TAUD0I5_index  41//41
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_7'">
    #define ISR_TAUD0I7_index  42//42
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_9'">
    #define ISR_TAUD0I9_index  43//43
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_11'">
    #define ISR_TAUD0I11_index  44//44
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_13'">
    #define ISR_TAUD0I13_index  45//45
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_15'">
    #define ISR_TAUD0I15_index  46//46
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='0'">
	#define ISR_DMA0_index  52//52
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='1'">
    #define ISR_DMA0_index  53//53
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='2'">
    #define ISR_DMA0_index  54//54
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='3'">
    #define ISR_DMA0_index  55//55
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='4'">
    #define ISR_DMA0_index  56//56
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='5'">
    #define ISR_DMA0_index  57//57
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='6'">
    #define ISR_DMA0_index  58//58
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='7'">
    #define ISR_DMA7_index  59//59
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='8'">
    #define ISR_DMA8_index  60//60
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='9'">
    #define ISR_DMA9_index  61//61
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='10'">
    #define ISR_DMA10_index  62//62
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='11'">
    #define ISR_DMA11_index  64//64
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='12'">
    #define ISR_DMA12_index  65//65
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='13'">
    #define ISR_DMA13_index  66//66
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='14'">
    #define ISR_DMA14_index  67//67
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'IIC']">
	<xsl:choose>
	<xsl:when test="value='0'">
	#define ISR_IIC0TI_index  68//68
	#define ISR_IIC0TEI_index  69//69
	#define ISR_IIC0RI_index  70//70
	#define ISR_IIC0EE_index  71//71
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_0'">
    #define ISR_TAUJ0I0_index  72//72
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_1'">
    #define ISR_TAUJ0I1_index  73//73
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_2'">
    #define ISR_TAUJ0I2_index  74//74
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_3'">
    #define ISR_TAUJ0I3_index  75//75
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'OS']">
	<xsl:choose>
	<xsl:when test="value='0'">
	#define ISR_OSTM0_index  76//76
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='0'">
    #define ISR_PWGA0_index  84//84
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='1'">
    #define ISR_PWGA1_index  85//85
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='2'">
     #define ISR_PWGA2_index  86//86
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='3'">
    #define ISR_PWGA3_index  87//87
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='8'">
    #define ISR_PWGA8_index  88//88
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='9'">
    #define ISR_PWGA9_index  89//89
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='10'">
    #define ISR_PWGA10_index  90//90
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='11'">
    #define ISR_PWGA11_index  91//91
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='12'">
    #define ISR_PWGA12_index  92//92
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='13'">
    #define ISR_PWGA13_index  93//93
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='14'">
    #define ISR_PWGA14_index  94//94
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='15'">
    #define ISR_PWGA15_index  95//95
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   	<xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='1'">
    #define ISR_CAN1ERR_index  105//105
	#define ISR_CAN1REC_index  106//106
	#define ISR_CAN1TRX_index  107//107
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='1'">
	#define ISR_CSIH1IC_index  108//108
	#define ISR_CSIH1IR_index  109//109
	#define ISR_CSIH1IRE_index 110//110
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='1'">
	#define ISR_UART1_index  112//112
	#define ISR_UART1_Tx_index  113//113
	#define ISR_UART1_Rx_index  114//114
	#define ISR_UART1_Error_index  115//115
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='20'">
    #define ISR_PWGA20_index  116//116
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='21'">
    #define ISR_PWGA21_index  117//117
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='22'">
    #define ISR_PWGA22_index  118//118
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
		<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='23'">
    #define ISR_PWGA23_index  119//119
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='6'">
	#define ISR_INTP6_index  120//120
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='7'">
    #define ISR_INTP7_index  121//121
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='8'">
    #define ISR_INTP8_index  122//122
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='12'">
    #define ISR_INTP12_index  123//123
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='2'">
	#define ISR_CSIH2IC_index  124//124
	#define ISR_CSIH2IR_index  125//125
	#define ISR_CSIH2IRE_index 126//126
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_0'">
    #define ISR_TAUB0I0_index  134//134
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_1'">
    #define ISR_TAUB0I1_index  135//135
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_2'">
    #define ISR_TAUB0I2_index  136//136
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_3'">
    #define ISR_TAUB0I3_index  137//137
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_4'">
    #define ISR_TAUB0I4_index  138//138
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_5'">
    #define ISR_TAUB0I5_index  139//139
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_6'">
    #define ISR_TAUB0I6_index  140//140
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_7'">
    #define ISR_TAUB0I7_index  141//141
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_8'">
    #define ISR_TAUB0I8_index  142//142
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_9'">
    #define ISR_TAUB0I9_index  143//143
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_10'">
    #define ISR_TAUB0I10_index  144//144
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_11'">
    #define ISR_TAUB0I11_index  145//145
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_12'">
    #define ISR_TAUB0I12_index  146//146
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_13'">
    #define ISR_TAUB0I13_index  147//147
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_14'">
    #define ISR_TAUB0I14_index  148//148
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_15'">
    #define ISR_TAUB0I15_index  149//149
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='3'">
	#define ISR_CSIH3IC_index  150//150
	#define ISR_CSIH3IR_index  151//151
	#define ISR_CSIH3IRE_index 152//152
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='2'">
	#define ISR_UART2_index     156//156
	#define ISR_UART2_Tx_index  157//157
	#define ISR_UART2_Rx_index  158//158
	#define ISR_UART2_Error_index 159//159
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_0'">
    #define ISR_TAUJ1I0_index  160//160
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_1'">
    #define ISR_TAUJ1I1_index  161//161
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_2'">   
	#define ISR_TAUJ1I2_index  162//162
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_3'">
    #define ISR_TAUJ1I3_index  175//175
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='24'">
    #define ISR_PWGA24_index 176//176
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='25'">
    #define ISR_PWGA25_index 177//177
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='27'">
    #define ISR_PWGA27_index 178//178
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='28'">
    #define ISR_PWGA28_index 179//179
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='29'">
    #define ISR_PWGA29_index 180//180
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='32'">
    #define ISR_PWGA32_index 181//181
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='33'">
    #define ISR_PWGA33_index 182//182
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='34'">
    #define ISR_PWGA34_index 183//183
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='35'">
    #define ISR_PWGA35_index 184//184
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='36'">
   #define ISR_PWGA36_index 185//185
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='37'">
    #define ISR_PWGA37_index 186//186
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='38'">
    #define ISR_PWGA38_index 187//187
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='39'">
    #define ISR_PWGA39_index 188//188
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='40'">
    #define ISR_PWGA40_index 189//189
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='41'">
    #define ISR_PWGA41_index 190//190
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='42'">
    #define ISR_PWGA42_index 191//191
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='43'">
    #define ISR_PWGA43_index 192//192
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='44'">
    #define ISR_PWGA44_index 193//193
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='45'">
    #define ISR_PWGA45_index 194//194
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='46'">
    #define ISR_PWGA46_index 195//195
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='47'">
	#define ISR_PWGA47_index 196//196
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='2'">
	#define ISR_CAN2ERR_index 209//209
	#define ISR_CAN2REC_index 210//210
	#define ISR_CAN2TRX_Error_index 211//211
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='3'">
   	#define ISR_UART3_index  220//220
	#define ISR_UART3_Tx_index  221//221
	#define ISR_UART3_Rx_index 222//222
	#define ISR_UART3_Error_index 223//223
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each> 
#define osdISRHooks            0

#define osdNumberOfPrioLevels  16
#define osdNumberOfInterrupts  256

#define osdSystemLevel         0
#define osdSystemLevelMask     0x0000ffffUL
#define osdSystemStackSize     600
#define osdStackCheckPattern   0xaaaaaaaaUL

#define osdOnCore                  0
#define osdNumberOfAvailableCores  1
#define osdTimerInterruptSourceNumberCore0 125
#define CC ECC1		//AUTO?
#define STATUS_LEVEL STANDARD_STATUS		//EXTENDED_STATUS
#define osdAllowAccessNotUsed 
#define osdByteSize 8U
#define osdCallTrustedFunctionNotUsed 
#define osdCancelAlarmNotUsed 
#define osdCheckISRMemoryAccessNotUsed 
#define osdCheckObjectAccessNotUsed 
#define osdCheckObjectOwnershipNotUsed 
#define osdCheckTaskMemoryAccessNotUsed 
#define osdCompiler osdCompilerGHSRH850
#define osdFullPreempt 1
#define osdGetAlarmBaseNotUsed 
#define osdGetAlarmNotUsed 
#define osdGetApplicationStateNotUsed 
#define osdGetCounterValueNotUsed 
#define osdGetElapsedValueNotUsed 
#define osdGetResourceNotUsed 
#define osdGetScheduleTableStatusNotUsed 
#define osdIncrementCounterNotUsed 
#define osdLib 0
#define osdMixedPreempt 0
#define osdNeedIOCTypes 0
#define osdNextScheduleTableNotUsed 
#define osdNonPreempt 0
#define osdNumApplErrorHooks 0
#define osdNumApplShutdownHooks 0
#define osdNumApplStartupHooks 0
#define osdNumberOfAllResources 0
#define osdNumberOfBasicTasks 1
#define osdNumberOfExtendedTasks 6
#define osdNumberOfIOCCommunications 0
#define osdNumberOfInternalResources 0
#define osdNumberOfInterruptResources 0
#define osdNumberOfPriorities 7
#define osdNumberOfQueuedIOCCallbacks 0
#define osdNumberOfQueuedIOCCommunications 0
#define osdNumberOfSemaphores 0
#define osdNumberOfTaskResources 0 
#define osdRTSize 1
#define osdReducedStatusChecks 0
#define osdReleaseResourceNotUsed 
#define osdResAccessMaskBits 32
#define osdSC SC1
#define osdSetAbsAlarmNotUsed 
#define osdSetRelAlarmNotUsed 
#define osdSetScheduleTableAsyncNotUsed 
#define osdStartScheduleTableAbsNotUsed 
#define osdStartScheduleTableRelNotUsed 
#define osdStartScheduleTableSynchronNotUsed 
#define osdStopScheduleTableNotUsed 
#define osdSyncScheduleTableNotUsed 
#define osdSysErrorHook 0
#define osdSysShutdownHook 0
#define osdSysStartupHook 0
#define osdTimingProtectionUsed 0
#define osdUseIOC 0
#define osdosGetISRMaxBlockingTimeNotUsed 
#define osdosGetISRMaxExecutionTimeNotUsed 
#define osdosGetISRMinInterArrivalTimeNotUsed 
#define osdosGetTaskMaxBlockingTimeNotUsed 
#define osdosGetTaskMaxExecutionTimeNotUsed 
#define osdosGetTaskMinInterArrivalTimeNotUsed 
<xsl:variable name="calculation" select="IRQ_Set/FUN[@Register = 'Var']/Var_value"/>
<xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='0'or value='1'or value='2'">
#define osdNumberOfAllISRs  <xsl:value-of select="($calculation)+2"/>
	</xsl:when>
    <xsl:otherwise>
#define osdNumberOfAllISRs  <xsl:value-of select="$calculation"/>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
#define osdNumberOfAllTasks 7
#define osdNumberOfCat1ISRs 0
<xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='0'or value='1'or value='2'">
#define osdNumberOfCat2ISRs  <xsl:value-of select="($calculation)+2"/>
	</xsl:when>
    <xsl:otherwise>
#define osdNumberOfCat2ISRs <xsl:value-of select="$calculation"/>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
#define osdNumberOfTrustedFunctions 0
#define osdUseTrustedFunctionStubs 0
#define osdNumberOfAlarms 0
#define osdNumberOfAlarmCallback 0
#define osdNumberOfAlarmSetEvent 0
#define osdNumberOfAlarmActivateTask 0
#define osdNumberOfAlarmIncrementCounter 0
#define osdNumberOfCounters 0
#define osdNumberOfSWCounters 0
#define osdNumberOfSWAndSRCounters 0
#define osdNumberOfApplications 0
#define osdStackCheck 1
#define osdStackUsageMeasurement 1

#define osdTypeHeaderInclude 1

#define osdEnableAssertions 1

#define osdGetServiceIdMacros 0
#define osdParameterAccessMacros 0
  
#define osdTimingMeasurement 0
#define osdProtectAndMeasureAll 0
#define osdAsSelected 0
#define osdOnlyMeasureAll 0

#define osdProtReactKillTaskIsrAllowed  0
#define osdProtReactKillApplAllowed     0
#define osdProtReactKillApplRestAllowed 0
#define osdErrorHook 0
#define osdPreTaskHook 0
#define osdPostTaskHook 0
#define osdShutdownHook 0
#define osdProtectionHook 0

#if osdProtectionHook

 #if (osdTimingProtectionUsed  osdProtReactKillTaskIsrAllowed)
  #define osdKillTaskIsrPossible 1
 #endif /*(osdTimingProtectionUsed <xsl:text disable-output-escaping="yes">&amp;</xsl:text><xsl:text disable-output-escaping="yes">&amp;</xsl:text> osdProtReactKillTaskIsrAllowed)*/

 #if ((osdSC == SC4) <xsl:text disable-output-escaping="yes">&amp;</xsl:text><xsl:text disable-output-escaping="yes">&amp;</xsl:text>(defined osdTimingProtectionUsed) <xsl:text disable-output-escaping="yes">&amp;</xsl:text><xsl:text disable-output-escaping="yes">&amp;</xsl:text> (osdProtReactKillApplAllowed || osdProtReactKillApplRestAllowed))
  #ifndef osdKillTaskIsrPossible
   #define osdKillTaskIsrPossible 1
  #endif
  #define osdKillApplPossible 1
 #endif /* (osdSC == SC4) <xsl:text disable-output-escaping="yes">&amp;</xsl:text><xsl:text disable-output-escaping="yes">&amp;</xsl:text> (defined osdTimingProtectionUsed) <xsl:text disable-output-escaping="yes">&amp;</xsl:text><xsl:text disable-output-escaping="yes">&amp;</xsl:text> (osdProtReactKillApplAllowed || osdProtReactKillApplRestAllowed))*/

#endif /* osdProtectionHook */

#if ((osdSC == SC3) || (osdSC == SC4)) <xsl:text disable-output-escaping="yes">&amp;</xsl:text><xsl:text disable-output-escaping="yes">&amp;</xsl:text> (!defined osdTerminateApplicationNotUsed)
 #ifndef osdKillTaskIsrPossible /* prevent from double-definition */
  #define osdKillTaskIsrPossible 1
 #endif
 #ifndef osdKillApplPossible
  #define osdKillApplPossible 1
 #endif
#endif /* ((osdSC == SC3) || (osdSC == SC4)) */

#ifndef osdKillTaskIsrPossible
 #define osdKillTaskIsrPossible 0
#endif

#ifndef osdKillApplPossible
 #define osdKillApplPossible 0
#endif

#define osdNumberOfProcesses (osdNumberOfAllTasks+osdNumberOfCat2ISRs)

#endif /* ! defined __TCB_H__ */
</xsl:template>  
</xsl:stylesheet>
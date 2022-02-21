<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text" indent="yes" encoding="ISO-8859-1"/>
<xsl:template match="/">
/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *				  
*   All Rights Reserved.                                               *                                    					   
*   Department : RN RD SW1                                             *      									  
*   AUTHOR     : Shao Guangxian                                        *
************************************************************************
* Object        :  intvect_c0.c
* Module        :
* Instance      :
* Description   :
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:

*************************************************************************/
/*-History--------------------------------------------------------------
* Version       Date           Name         Changes and comment
 <xsl:for-each select="IRQ_Set/INF">
 <xsl:for-each select="info_Group">
 ------------------------------------------------------------------------
 *<xsl:value-of select="@Version"/>         .<xsl:value-of select="@Date"/>    .<xsl:value-of select="@Name"/>     .<xsl:value-of select="@Comment"/>
 </xsl:for-each>
</xsl:for-each>
*=======================================================================*/
#if defined USE_QUOTE_INCLUDES
 #include "vrm.h"
#else
 #include "vrm.h"
#endif
 
#define osdVrmGenMajRelNum 1
#define osdVrmGenMinRelNum 6
#if defined USE_QUOTE_INCLUDES
 #include "vrm.h"
#else
 #include <xsl:text disable-output-escaping="yes">&lt;</xsl:text>vrm.h<xsl:text disable-output-escaping="yes">&gt;</xsl:text>
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

//.extern		_priority7_interrupt

#pragma asm

   .align 512
   .section ".osExceptionVectorTable_c0", "ax"

   .globl _osExceptionVectorTable_c0   /* start of the core exception vector table */
_osExceptionVectorTable_c0:

   .offset 0x0000
   .globl _RESET
   jr _RESET

   .offset 0x0010
   .globl _osCoreException_c0_0x0010
_osCoreException_c0_0x0010:
   jr _osUnhandledCoreException

   .offset 0x0020
   .globl _osCoreException_c0_0x0020
_osCoreException_c0_0x0020:
   jr _osUnhandledCoreException

   .offset 0x0030
   .globl _osCoreException_c0_0x0030
_osCoreException_c0_0x0030:
   jr _osUnhandledCoreException

   .offset 0x0040
   .globl _osCoreException_c0_0x0040
_osCoreException_c0_0x0040:
   jr _osTrapDispatcher_c0

   .offset 0x0050
   .globl _osCoreException_c0_0x0050
_osCoreException_c0_0x0050:
   jr _osUnhandledCoreException

   .offset 0x0060
   .globl _osCoreException_c0_0x0060
_osCoreException_c0_0x0060:
   jr _osUnhandledCoreException

   .offset 0x0070
   .globl _osCoreException_c0_0x0070
_osCoreException_c0_0x0070:
   jr _osUnhandledCoreException

   .offset 0x0080
   .globl _osCoreException_c0_0x0080
_osCoreException_c0_0x0080:
   jr _osUnhandledCoreException

   .offset 0x0090
   .globl _osCoreException_c0_0x0090
_osCoreException_c0_0x0090:
   jr _osUnhandledCoreException

   .offset 0x00a0
   .globl _osCoreException_c0_0x00a0
_osCoreException_c0_0x00a0:
   jr _osUnhandledCoreException

   .offset 0x00b0
   .globl _osCoreException_c0_0x00b0
_osCoreException_c0_0x00b0:
   jr _osUnhandledCoreException
 
   .offset 0x00c0
   .globl _osCoreException_c0_0x00c0
_osCoreException_c0_0x00c0:
   jr _osUnhandledCoreException

   .offset 0x00d0
   .globl _osCoreException_c0_0x00d0
_osCoreException_c0_0x00d0:
   jr _osUnhandledCoreException

   .offset 0x00e0
   .globl _osCoreException_c0_0x00e0
_osCoreException_c0_0x00e0:
   jr _osUnhandledCoreException

   .offset 0x00f0
   .globl _osCoreException_c0_0x00f0
_osCoreException_c0_0x00f0:
   jr _osUnhandledCoreException

   .offset 0x0100
   .globl _osCoreException_c0_0x0100
_osCoreException_c0_0x0100:
   jr _osUnhandledDirectBranchException

   .offset 0x0110
   .globl _osCoreException_c0_0x0110
_osCoreException_c0_0x0110:
   jr _osUnhandledDirectBranchException

   .offset 0x0120
   .globl _osCoreException_c0_0x0120
_osCoreException_c0_0x0120:
   jr _osUnhandledDirectBranchException

   .offset 0x0130
   .globl _osCoreException_c0_0x0130
_osCoreException_c0_0x0130:
   jr _osUnhandledDirectBranchException

   .offset 0x0140
   .globl _osCoreException_c0_0x0140
_osCoreException_c0_0x0140:
   jr _osUnhandledDirectBranchException

   .offset 0x0150
   .globl _osCoreException_c0_0x0150
_osCoreException_c0_0x0150:
   jr _osUnhandledDirectBranchException

   .offset 0x0160
   .globl _osCoreException_c0_0x0160
_osCoreException_c0_0x0160:
   jr _osUnhandledDirectBranchException

   .offset 0x0170
   .globl _osCoreException_c0_0x0170
_osCoreException_c0_0x0170:
   jr _osUnhandledDirectBranchException		/*test WDT0 NMI INT*/
	//jr	_priority7_interrupt

   
   .offset 0x0180
   .globl _osCoreException_c0_0x0180
_osCoreException_c0_0x0180:
   jr _osUnhandledDirectBranchException

   .offset 0x0190
   .globl _osCoreException_c0_0x0190
_osCoreException_c0_0x0190:
   jr _osUnhandledDirectBranchException

   .offset 0x01a0
   .globl _osCoreException_c0_0x01a0
_osCoreException_c0_0x01a0:
   jr _osUnhandledDirectBranchException

   .offset 0x01b0
   .globl _osCoreException_c0_0x01b0
_osCoreException_c0_0x01b0:
   jr _osUnhandledDirectBranchException

   .offset 0x01c0
   .globl _osCoreException_c0_0x01c0
_osCoreException_c0_0x01c0:
   jr _osUnhandledDirectBranchException

   .offset 0x01d0
   .globl _osCoreException_c0_0x01d0
_osCoreException_c0_0x01d0:
   jr _osUnhandledDirectBranchException

   .offset 0x01e0
   .globl _osCoreException_c0_0x01e0
_osCoreException_c0_0x01e0:
   jr _osUnhandledDirectBranchException

   .offset 0x01f0
   .globl _osCoreException_c0_0x01f0
_osCoreException_c0_0x01f0:
   jr _osUnhandledDirectBranchException

   .globl _osExceptionVectorTableEnd_c0
_osExceptionVectorTableEnd_c0:   /* end of the core exception vector table */

#pragma endasm


#pragma asm

   .align 512
   .section ".osEIINTVectorTable_c0", "ax"

   .globl _osEIINTVectorTable_c0   /* start of the EIINT exception vector table */
_osEIINTVectorTable_c0:
 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_0'">
    .word _ISR_TAUD0I0_CAT2//0
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//0
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_2'">
    .word _ISR_TAUD0I2_CAT2//1
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//1
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_4'">
    .word _ISR_TAUD0I4_CAT2//2
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//2
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_6'">
    .word _ISR_TAUD0I6_CAT2//3
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//3
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_8'">
    .word _ISR_TAUD0I8_CAT2//4
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//4
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_10'">
    .word _ISR_TAUD0I10_CAT2//5
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//5
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_12'">
    .word _ISR_TAUD0I12_CAT2//6
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//6
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_14'">
    .word _ISR_TAUD0I14_CAT2//7
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//7
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    .word _osUnhandledEIINTException//8#define INTTAPA0IPEK0 8
    .word _osUnhandledEIINTException//9#define INTTAPA0IVLY0 9
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'ADC']">
	<xsl:choose>
	<xsl:when test="value='1'">
    .word _ISR_ADCA0_INTSG1_CAT2//10
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//10
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'ADC']">
	<xsl:choose>
	<xsl:when test="value='2'">
    .word _ISR_ADCA0_INTSG2_CAT2//11
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//11
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'ADC']">
	<xsl:choose>
	<xsl:when test="value='3'">
    .word _ISR_ADCA0_INTSG3_CAT2//12
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//12
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    .word _osUnhandledEIINTException//13  #define INTDCUTDI 13
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='0'or value='1'or value='2'">
    .word _ISR_CANGERR_CAT2  //14
	.word _ISR_CANGRECC_CAT2 //15
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//14
	.word _osUnhandledEIINTException//15
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='0'">
    .word _ISR_CAN0ERR_CAT2   //16
    .word _ISR_CAN0REC_CAT2   //17
    .word _ISR_CAN0TRX_CAT2   //18
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//16
	.word _osUnhandledEIINTException//17
	.word _osUnhandledEIINTException//18
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    .word _osUnhandledEIINTException//19 #define INTCSIG0IC 19
    .word _osUnhandledEIINTException//20 #define INTCSIG0IR 20
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='0'">
    .word _ISR_CSIH0IC_CAT2	   //21
    .word _ISR_CSIH0IR_CAT2	  //22
    .word _ISR_CSIH0IRE_CAT2  //23
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//21
    .word _osUnhandledEIINTException//22
    .word _osUnhandledEIINTException//23
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    .word _osUnhandledEIINTException//#define INTCSIH0IJC 24
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='0'">
    .word _ISR_UART0_CAT2//25
    .word _ISR_UART0_Tx_CAT2//26
    .word _ISR_UART0_Rx_CAT2//27
    .word _ISR_UART0_Error_CAT2//28
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//25
    .word _osUnhandledEIINTException//26
    .word _osUnhandledEIINTException//27
	.word _osUnhandledEIINTException//28
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='0'">
    .word _ISR_INTP0_CAT2//29
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//29
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='1'">
    .word _ISR_INTP1_CAT2//30
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//30
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='2'">
    .word _ISR_INTP2_CAT2//31
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//31
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'WD']">
	<xsl:choose>
	<xsl:when test="value='0'">
     .word _ISR_WDTA0_CAT2  //32
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//32
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
      <xsl:for-each select="IRQ_Set/FUN[@Register = 'WD']">
	<xsl:choose>
	<xsl:when test="value='1'">
     .word _ISR_WDTA1_CAT2  //33
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//33
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose> 
	<xsl:when test="value='3'">
    .word _ISR_INTP3_CAT2//34
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//34
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='4'">
    .word _ISR_INTP4_CAT2//35
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//35
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='5'">
    .word _ISR_INTP5_CAT2//36
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//36
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='10'">
    .word _ISR_INTP10_CAT2//37
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//37
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='11'">
    .word _ISR_INTP11_CAT2//38
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//38
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_1'">
    .word _ISR_TAUD0I1_CAT2//39
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//39
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_3'">
    .word _ISR_TAUD0I3_CAT2//40
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//40
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_5'">
    .word _ISR_TAUD0I5_CAT2//41
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//41
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_7'">
    .word _ISR_TAUD0I7_CAT2//42
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//42
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_9'">
    .word _ISR_TAUD0I9_CAT2//43
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//43
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_11'">
    .word _ISR_TAUD0I11_CAT2//44
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//44
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_13'">
    .word _ISR_TAUD0I13_CAT2//45
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//45
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_15'">
    .word _ISR_TAUD0I15_CAT2//46
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//46
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   .word _osUnhandledEIINTException//47 define INTADCA0ERR 47
   .word _osUnhandledEIINTException//48 
   .word _osUnhandledEIINTException//49 #define INTCSIG0IRE 49
   .word _osUnhandledEIINTException//50 #define INTRLIN20 50
   .word _osUnhandledEIINTException//51 #define INTRLIN21 51
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='0'">
    .word _ISR_DMA0_CAT2//52
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//52
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='1'">
    .word _ISR_DMA1_CAT2//53
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//53
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='2'">
    .word _ISR_DMA2_CAT2//54
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//54
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='3'">
    .word _ISR_DMA3_CAT2//55
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//55
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='4'">
    .word _ISR_DMA4_CAT2//56
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//56
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='5'">
    .word _ISR_DMA5_CAT2//57
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//57
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='6'">
    .word _ISR_DMA6_CAT2//58
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//58
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='7'">
    .word _ISR_DMA7_CAT2//59
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//59
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='8'">
    .word _ISR_DMA8_CAT2//60
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//60
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='9'">
    .word _ISR_DMA9_CAT2//61
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//61
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='10'">
    .word _ISR_DMA10_CAT2//62
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//63
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='11'">
    .word _ISR_DMA11_CAT2//64
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//64
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='12'">
    .word _ISR_DMA12_CAT2//65
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//65
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='13'">
    .word _ISR_DMA13_CAT2//66
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//66
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='14'">
    .word _ISR_DMA14_CAT2//67
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//67
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'IIC']">
	<xsl:choose>
	<xsl:when test="value='0'">
    .word _ISR_IIC0TI_CAT2//68
    .word _ISR_IIC0TEI_CAT2//69
    .word _ISR_IIC0RI_CAT2//70
    .word _ISR_IIC0EE_CAT2//71
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//68
    .word _osUnhandledEIINTException//69
    .word _osUnhandledEIINTException//70
	.word _osUnhandledEIINTException//71
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_0'">
    .word _ISR_TAUJ0I0_CAT2//72
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//72
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_1'">
    .word _ISR_TAUJ0I1_CAT2//73
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//73
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_2'">
    .word _ISR_TAUJ0I2_CAT2//74
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//74
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_3'">
    .word _ISR_TAUJ0I3_CAT2//75
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//75
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'OS']">
	<xsl:choose>
	<xsl:when test="value='0'">
    .word _ISR_OSTM0_CAT2//76
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//76
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   .word _osUnhandledEIINTException//77#define INTENCA0IOV 77
   .word _osUnhandledEIINTException//78#define INTENCA0IUD 78
   .word _osUnhandledEIINTException//79#define INTENCA0I0 79
   .word _osUnhandledEIINTException//80#define INTENCA0I1 80
   .word _osUnhandledEIINTException//81#define INTENCA0IEC 81
   .word _osUnhandledEIINTException//82#define INTKR0 82
   .word _osUnhandledEIINTException//83#define INTQFULL 83
   	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='0'">
    .word _ISR_PWGA0_CAT2//84
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//84
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='1'">
    .word _ISR_PWGA1_CAT2//85
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//85
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='2'">
    .word _ISR_PWGA2_CAT2//86
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//86
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='3'">
    .word _ISR_PWGA3_CAT2//87
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//87
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='8'">
    .word _ISR_PWGA8_CAT2//88
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//88
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='9'">
    .word _ISR_PWGA9_CAT2//89
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//89
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='10'">
    .word _ISR_PWGA10_CAT2//90
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//90
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='11'">
    .word _ISR_PWGA11_CAT2//91
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//91
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='12'">
    .word _ISR_PWGA12_CAT2//92
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//92
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='13'">
    .word _ISR_PWGA13_CAT2//93
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//93
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='14'">
    .word _ISR_PWGA14_CAT2//94
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//94
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='15'">
    .word _ISR_PWGA15_CAT2//95
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//95
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   .word _osUnhandledEIINTException//96
   .word _osUnhandledEIINTException//97
   .word _osUnhandledEIINTException//98
   .word _osUnhandledEIINTException//99
   .word _osUnhandledEIINTException//100
   .word _osUnhandledEIINTException//101
   .word _osUnhandledEIINTException//102#define INTFLERR 102
   .word _osUnhandledEIINTException//103#define INTFLENDNM 103
   .word _osUnhandledEIINTException//104#define INTCWEND 104
   	<xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='1'">
    .word _ISR_CAN1ERR_CAT2   //105
    .word _ISR_CAN1REC_CAT2   //106
    .word _ISR_CAN1TRX_CAT2   //107
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//105
	.word _osUnhandledEIINTException//106
	.word _osUnhandledEIINTException//107
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='1'">
    .word _ISR_CSIH1IC_CAT2	   //108
    .word _ISR_CSIH1IR_CAT2	  //109
    .word _ISR_CSIH1IRE_CAT2  //110
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//108
    .word _osUnhandledEIINTException//109
    .word _osUnhandledEIINTException//110
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    .word _osUnhandledEIINTException//#define INTCSIH1IJC 111
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='1'">
    .word _ISR_UART1_CAT2//112
    .word _ISR_UART1_Tx_CAT2//113
    .word _ISR_UART1_Rx_CAT2//114
    .word _ISR_UART1_Error_CAT2//115
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//112
    .word _osUnhandledEIINTException//113
    .word _osUnhandledEIINTException//114
	.word _osUnhandledEIINTException//115
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='20'">
    .word _ISR_PWGA20_CAT2//116
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//116
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='21'">
    .word _ISR_PWGA21_CAT2//117
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//117
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='22'">
    .word _ISR_PWGA22_CAT2//118
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//118
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
		<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='23'">
    .word _ISR_PWGA23_CAT2//119
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//119
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='6'">
    .word _ISR_INTP6_CAT2//120
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//120
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='7'">
    .word _ISR_INTP7_CAT2//121
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//121
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='8'">
    .word _ISR_INTP8_CAT2//122
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//122
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='12'">
    .word _ISR_INTP12_CAT2//123
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//123
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='2'">
    .word _ISR_CSIH2IC_CAT2	   //124
    .word _ISR_CSIH2IR_CAT2	  //125
    .word _ISR_CSIH2IRE_CAT2  //126
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//124
    .word _osUnhandledEIINTException//125
    .word _osUnhandledEIINTException//126
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	.word _osUnhandledEIINTException//#define INTCSIH2IJC 127
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_0'">
    .word _ISR_TAUB0I0_CAT2//134
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//134
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_1'">
    .word _ISR_TAUB0I1_CAT2//135
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//135
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_2'">
    .word _ISR_TAUB0I2_CAT2//136
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//136
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_3'">
    .word _ISR_TAUB0I3_CAT2//137
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//137
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_4'">
    .word _ISR_TAUB0I4_CAT2//138
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//138
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_5'">
    .word _ISR_TAUB0I5_CAT2//139
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//139
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_6'">
    .word _ISR_TAUB0I6_CAT2//140
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//140
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_7'">
    .word _ISR_TAUB0I7_CAT2//141
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//141
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_8'">
    .word _ISR_TAUB0I8_CAT2//142
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//142
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_9'">
    .word _ISR_TAUB0I9_CAT2//143
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//143
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_10'">
    .word _ISR_TAUB0I10_CAT2//144
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//144
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_11'">
    .word _ISR_TAUB0I11_CAT2//145
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//145
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_12'">
    .word _ISR_TAUB0I12_CAT2//146
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//146
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_13'">
    .word _ISR_TAUB0I13_CAT2//147
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//147
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_14'">
    .word _ISR_TAUB0I14_CAT2//148
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//148
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_15'">
    .word _ISR_TAUB0I15_CAT2//149
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//149
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='3'">
    .word _ISR_CSIH3IC_CAT2	   //150
    .word _ISR_CSIH3IR_CAT2	  //151
    .word _ISR_CSIH3IRE_CAT2  //152
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//150
    .word _osUnhandledEIINTException//151
    .word _osUnhandledEIINTException//152
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	.word _osUnhandledEIINTException//#define INTCSIH3IJC 153
	.word _osUnhandledEIINTException//#define INTRLIN22 154
	.word _osUnhandledEIINTException//155
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='2'">
    .word _ISR_UART2_CAT2//156
    .word _ISR_UART2_Tx_CAT2//157
    .word _ISR_UART2_Rx_CAT2//158
    .word _ISR_UART2_Error_CAT2//159
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//156
    .word _osUnhandledEIINTException//157
    .word _osUnhandledEIINTException//158
	.word _osUnhandledEIINTException//159
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_0'">
    .word _ISR_TAUJ1I0_CAT2//160
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//160
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_1'">
    .word _ISR_TAUJ1I1_CAT2//161
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//161
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_2'">
    .word _ISR_TAUJ1I2_CAT2//162
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//162
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_3'">
    .word _ISR_TAUJ1I3_CAT2//163
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//163
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	.word _osUnhandledEIINTException//164
    .word _osUnhandledEIINTException//165
    .word _osUnhandledEIINTException//166
	.word _osUnhandledEIINTException//167
	.word _osUnhandledEIINTException//168
    .word _osUnhandledEIINTException//169
    .word _osUnhandledEIINTException//170
	.word _osUnhandledEIINTException//171
	.word _osUnhandledEIINTException//172
	.word _osUnhandledEIINTException//173
	.word _osUnhandledEIINTException//174
    .word _osUnhandledEIINTException//175
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='24'">
    .word _ISR_PWGA24_CAT2//176
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//176
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='25'">
    .word _ISR_PWGA25_CAT2//177
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//177
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='27'">
    .word _ISR_PWGA27_CAT2//178
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//178
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='28'">
    .word _ISR_PWGA28_CAT2//179
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//179
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='29'">
    .word _ISR_PWGA29_CAT2//180
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//180
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='32'">
    .word _ISR_PWGA32_CAT2//181
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//181
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='33'">
    .word _ISR_PWGA33_CAT2//182
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//182
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='34'">
    .word _ISR_PWGA34_CAT2//183
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//183
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='35'">
    .word _ISR_PWGA35_CAT2//184
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//184
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='36'">
    .word _ISR_PWGA36_CAT2//185
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//185
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='37'">
    .word _ISR_PWGA37_CAT2//186
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//186
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='38'">
    .word _ISR_PWGA38_CAT2//187
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//187
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='39'">
    .word _ISR_PWGA39_CAT2//188
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//188
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='40'">
    .word _ISR_PWGA40_CAT2//189
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//189
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='41'">
    .word _ISR_PWGA41_CAT2//190
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//190
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='42'">
    .word _ISR_PWGA42_CAT2//191
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//191
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='43'">
    .word _ISR_PWGA43_CAT2//192
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//192
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='44'">
    .word _ISR_PWGA44_CAT2//193
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//193
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='45'">
    .word _ISR_PWGA45_CAT2//194
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//194
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='46'">
    .word _ISR_PWGA46_CAT2//195
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//195
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='47'">
    .word _ISR_PWGA47_CAT2//196
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//196
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   .word _osUnhandledEIINTException//197
   .word _osUnhandledEIINTException//198
   .word _osUnhandledEIINTException//199
   .word _osUnhandledEIINTException//200
   .word _osUnhandledEIINTException//201
   .word _osUnhandledEIINTException//202
    word _osUnhandledEIINTException//203
   .word _osUnhandledEIINTException//204
   .word _osUnhandledEIINTException//205
   .word _osUnhandledEIINTException//206
   .word _osUnhandledEIINTException//207
   .word _osUnhandledEIINTException//#define Reserved 208
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='2'">
    .word _ISR_CAN2ERR_CAT2   //209
    .word _ISR_CAN2REC_CAT2   //210
    .word _ISR_CAN2TRX_CAT2   //211
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//209
	.word _osUnhandledEIINTException//210
	.word _osUnhandledEIINTException//211
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	.word _osUnhandledEIINTException//212
    .word _osUnhandledEIINTException//213
    .word _osUnhandledEIINTException//214
	.word _osUnhandledEIINTException//215
	.word _osUnhandledEIINTException//216
    .word _osUnhandledEIINTException//217
    .word _osUnhandledEIINTException//218
	.word _osUnhandledEIINTException//219
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='3'">
    .word _ISR_UART3_CAT2//220
    .word _ISR_UART3_Tx_CAT2//221
    .word _ISR_UART3_Rx_CAT2//222
    .word _ISR_UART3_Error_CAT2//223
	</xsl:when>
    <xsl:otherwise>
    .word _osUnhandledEIINTException//220
    .word _osUnhandledEIINTException//221
    .word _osUnhandledEIINTException//222
	.word _osUnhandledEIINTException//223
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    .word _osUnhandledEIINTException//224
    .word _osUnhandledEIINTException//225
    .word _osUnhandledEIINTException//226
	.word _osUnhandledEIINTException//227
	.word _osUnhandledEIINTException//228
    .word _osUnhandledEIINTException//229
    .word _osUnhandledEIINTException//230
	.word _osUnhandledEIINTException//231
	.word _osUnhandledEIINTException//232
    .word _osUnhandledEIINTException//233
    .word _osUnhandledEIINTException//234
	.word _osUnhandledEIINTException//235
	.word _osUnhandledEIINTException//236
    .word _osUnhandledEIINTException//237
    .word _osUnhandledEIINTException//238
	.word _osUnhandledEIINTException//239
    .word _osUnhandledEIINTException//240
    .word _osUnhandledEIINTException//241
    .word _osUnhandledEIINTException//242
	.word _osUnhandledEIINTException//243
	.word _osUnhandledEIINTException//244
    .word _osUnhandledEIINTException//245
    .word _osUnhandledEIINTException//246
	.word _osUnhandledEIINTException//247
	.word _osUnhandledEIINTException//248
    .word _osUnhandledEIINTException//249
	.word _osUnhandledEIINTException//250
	.word _osUnhandledEIINTException//251
    .word _osUnhandledEIINTException//252
    .word _osUnhandledEIINTException//253
	.word _osUnhandledEIINTException//254
	.word _osUnhandledEIINTException//255
   .globl _osEIINTVectorTableEnd_c0
_osEIINTVectorTableEnd_c0:   /* end of the EIINT exception vector table */

#pragma endasm

#pragma asm

 .section ".os_text", "ax"

    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_0'">
	/* MISRA RULE 14.1 not violated: ISR_TAUD0I0 is branched via EIINT vector table. */
    osCAT2ISRC0(ISR_TAUD0I0,0)//0/* PRQA S 1503 */
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_2'">
    osCAT2ISRC0(ISR_TAUD0I2,1)//1
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_4'">
    osCAT2ISRC0(ISR_TAUD0I4,1)//1//2
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_6'">
    osCAT2ISRC0(ISR_TAUD0I6,1)//1//3
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_8'">
    osCAT2ISRC0(ISR_TAUD0I8,1)//1//4
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_10'">
    osCAT2ISRC0(ISR_TAUD0I10,1)//5
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_12'">
    osCAT2ISRC0(ISR_TAUD0I12,1)//6
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_14'">
    osCAT2ISRC0(ISR_TAUD0I14,1)//7
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'ADC']">
	<xsl:choose>
	<xsl:when test="value='1'">
    osCAT2ISRC0(ISR_ADCA0_INTSG1,1)//10
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'ADC']">
	<xsl:choose>
	<xsl:when test="value='2'">
    osCAT2ISRC0(ISR_ADCA0_INTSG2,1)//11
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'ADC']">
	<xsl:choose>
	<xsl:when test="value='3'">
	osCAT2ISRC0(ISR_ADCA0_INTSG3,1)//12
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='0'or value='1'or value='2'">
    osCAT2ISRC0(ISR_CANGERR,1)//14
	osCAT2ISRC0(ISR_CANGRECC,1)//15
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='0'">
    osCAT2ISRC0(ISR_CAN0ERR,1)//16
	osCAT2ISRC0(ISR_CAN0REC,1)//17
	osCAT2ISRC0(ISR_CAN0TRX,1)//18
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='0'">
	osCAT2ISRC0(ISR_CSIH0IC,1)//21
	osCAT2ISRC0(ISR_CSIH0IR,1)//22
	osCAT2ISRC0(ISR_CSIH0IRE,1)//23
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise> 
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='0'">
	osCAT2ISRC0(ISR_UART0,1)//25
	osCAT2ISRC0(ISR_UART0_Tx,1)//26
	osCAT2ISRC0(ISR_UART0_Rx,1)//27
	osCAT2ISRC0(ISR_UART0_Error,1)//28
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='0'">
    osCAT2ISRC0(ISR_INTP0,1)//29
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='1'">
    osCAT2ISRC0(ISR_INTP1,1)//30
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='2'">
    osCAT2ISRC0(ISR_INTP2,1)//31
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'WD']">
	<xsl:choose>
	<xsl:when test="value='0'">
    osCAT2ISRC0(ISR_WDTA0,1)//32
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
      <xsl:for-each select="IRQ_Set/FUN[@Register = 'WD']">
	<xsl:choose>
	<xsl:when test="value='1'">
	osCAT2ISRC0(ISR_WDTA1,1)//33
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='3'">
    osCAT2ISRC0(ISR_INTP3,1)//34
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='4'">
    osCAT2ISRC0(ISR_INTP4,1)//35
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='5'">
    osCAT2ISRC0(ISR_INTP2,1)//36
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='10'">
    osCAT2ISRC0(ISR_INTP10,1)//37
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='11'">
	osCAT2ISRC0(ISR_INTP11,1)//38
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_1'">
    osCAT2ISRC0(ISR_TAUD0I1,1)//39
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_3'">
    osCAT2ISRC0(ISR_TAUD0I3,1)//40
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_5'">
    osCAT2ISRC0(ISR_TAUD0I5,1)//41
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_7'">
     osCAT2ISRC0(ISR_TAUD0I7,1)//42
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_9'">
    osCAT2ISRC0(ISR_TAUD0I9,1)//43
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_11'">
    osCAT2ISRC0(ISR_TAUD0I11,1)//44
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_13'">
    osCAT2ISRC0(ISR_TAUD0I13,1)//45
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='D0_15'">
    osCAT2ISRC0(ISR_TAUD0I15,1)//46
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='0'">
    osCAT2ISRC0(ISR_DMA0,1)//52
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='1'">
    osCAT2ISRC0(ISR_DMA1,1)//53
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='2'">
    osCAT2ISRC0(ISR_DMA2,1)//54
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='3'">
    osCAT2ISRC0(ISR_DMA3,1)//55
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='4'">
    osCAT2ISRC0(ISR_DMA4,1)//56
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='5'">
    osCAT2ISRC0(ISR_DMA5,1)//57
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='6'">
    osCAT2ISRC0(ISR_DMA6,1)//58
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='7'">
    osCAT2ISRC0(ISR_DMA7,1)//59
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='8'">
    osCAT2ISRC0(ISR_DMA8,1)//60
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='9'">
    osCAT2ISRC0(ISR_DMA9,1)//61
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='10'">
    osCAT2ISRC0(ISR_DMA10,1)//62
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='11'">
    osCAT2ISRC0(ISR_DMA11,1)//64
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='12'">
    osCAT2ISRC0(ISR_DMA12,1)//65
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='13'">
    osCAT2ISRC0(ISR_DMA13,1)//66
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'DMA']">
	<xsl:choose>
	<xsl:when test="value='14'">
    osCAT2ISRC0(ISR_DMA14,1)//67
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'IIC']">
	<xsl:choose>
	<xsl:when test="value='0'">
    osCAT2ISRC0(ISR_IIC0TI,1)//68
	osCAT2ISRC0(ISR_IIC0TEI,1)//69
	osCAT2ISRC0(ISR_IIC0RI,1)//70
	osCAT2ISRC0(ISR_IIC0EE,1)//71
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_0'">
    osCAT2ISRC0(ISR_TAUJ0I0,1)//72
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_1'">
    osCAT2ISRC0(ISR_TAUJ0I1,1)//73
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_2'">
    osCAT2ISRC0(ISR_TAUJ0I2,1)//74
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J0_3'">
    osCAT2ISRC0(ISR_TAUJ0I3,1)//75
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'OS']">
	<xsl:choose>
	<xsl:when test="value='0'">
	osCAT2ISRC0(ISR_OSTM0,1)//76
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='0'">
    osCAT2ISRC0(ISR_PWGA0,1)//84
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='1'">
    osCAT2ISRC0(ISR_PWGA1,1)//85
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='2'">
    osCAT2ISRC0(ISR_PWGA2,1)//86
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='3'">
    osCAT2ISRC0(ISR_PWGA3,1)//87
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='8'">
    osCAT2ISRC0(ISR_PWGA8,1)//88
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='9'">
    osCAT2ISRC0(ISR_PWGA9,1)//89
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='10'">
    osCAT2ISRC0(ISR_PWGA10,1)//90
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='11'">
    osCAT2ISRC0(ISR_PWGA11,1)//91
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='12'">
    osCAT2ISRC0(ISR_PWGA12,1)//92
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='13'">
    osCAT2ISRC0(ISR_PWGA13,1)//93
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='14'">
    osCAT2ISRC0(ISR_PWGA14,1)//94
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='15'">
    osCAT2ISRC0(ISR_PWGA15,1)//95
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   	<xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='1'">
    osCAT2ISRC0(ISR_CAN1ERR,1)//105
	osCAT2ISRC0(ISR_CAN1REC,1)//106
	osCAT2ISRC0(ISR_CAN1TRX,1)//107
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='1'">
	osCAT2ISRC0(ISR_CSIH1IC,1)//108
	osCAT2ISRC0(ISR_CSIH1IR,1)//109
	osCAT2ISRC0(ISR_CSIH1IRE,1)//110
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='1'">
    osCAT2ISRC0(ISR_UART1,1)//112
	osCAT2ISRC0(ISR_UART1_Tx,1)//113
	osCAT2ISRC0(ISR_UART1_Rx,1)//114
	osCAT2ISRC0(ISR_UART1_Error,1)//115
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='20'">
    osCAT2ISRC0(ISR_PWGA20,1)//116
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='21'">
    osCAT2ISRC0(ISR_PWGA21,1)//117
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='22'">
    osCAT2ISRC0(ISR_PWGA22,1)//118
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
		<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='23'">
    osCAT2ISRC0(ISR_PWGA23,1)//119
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='6'">
	osCAT2ISRC0(ISR_INTP6,1)//120
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='7'">
    osCAT2ISRC0(ISR_INTP7,1)//121
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='8'">
    osCAT2ISRC0(ISR_INTP8,1)//122
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'EX']">
	<xsl:choose>
	<xsl:when test="value='12'">
    osCAT2ISRC0(ISR_INTP12,1)//123
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='2'">
	osCAT2ISRC0(ISR_CSIH2IC,1)//124
	osCAT2ISRC0(ISR_CSIH2IR,1)//125
	osCAT2ISRC0(ISR_CSIH2IRE,1)//126
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_0'">
    osCAT2ISRC0(ISR_TAUB0I0,1)//134
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
   <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_1'">
    osCAT2ISRC0(ISR_TAUB0I1,1)//135
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_2'">
    osCAT2ISRC0(ISR_TAUB0I2,1)//136
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_3'">
    osCAT2ISRC0(ISR_TAUB0I3,1)//137
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_4'">
    osCAT2ISRC0(ISR_TAUB0I4,1)//138
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_5'">
    osCAT2ISRC0(ISR_TAUB0I5,1)//139
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_6'">
    osCAT2ISRC0(ISR_TAUB0I6,1)//140
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
     <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_7'">
    osCAT2ISRC0(ISR_TAUB0I7,1)//141
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_8'">
    osCAT2ISRC0(ISR_TAUB0I8,1)//142
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_9'">
    osCAT2ISRC0(ISR_TAUB0I9,1)//143
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_10'">
    osCAT2ISRC0(ISR_TAUB0I10,1)//144
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_11'">
    osCAT2ISRC0(ISR_TAUB0I11,1)//145
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_12'">
    osCAT2ISRC0(ISR_TAUB0I12,1)//146
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_13'">
    osCAT2ISRC0(ISR_TAUB0I13,1)//147
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_14'">
    osCAT2ISRC0(ISR_TAUB0I14,1)//148
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	 <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='B0_15'">
    osCAT2ISRC0(ISR_TAUB0I15,1)//2149
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'SPI']">
	<xsl:choose>
	<xsl:when test="value='3'">
	osCAT2ISRC0(ISR_CSIH3IC,1)//150
	osCAT2ISRC0(ISR_CSIH3IR,1)//151
	osCAT2ISRC0(ISR_CSIH3IRE,1)//152
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='2'">
    osCAT2ISRC0(ISR_UART2,1)//156
	osCAT2ISRC0(ISR_UART2_Tx,1)//157
	osCAT2ISRC0(ISR_UART2_Rx,1)//158
	osCAT2ISRC0(ISR_UART2_Error,1)//159
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_0'">
    osCAT2ISRC0(ISR_TAUJ1I0,1)//160
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_1'">
    osCAT2ISRC0(ISR_TAUJ1I1,1)//161
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_2'">
    osCAT2ISRC0(ISR_TAUJ1I2,1)//162
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'TAU']">
	<xsl:choose>
	<xsl:when test="value='J1_3'">
    osCAT2ISRC0(ISR_TAUJ1I3,1)//175
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='24'">
    osCAT2ISRC0(ISR_PWGA24,1)//176
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='25'">
    osCAT2ISRC0(ISR_PWGA25,1)//177
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='27'">
    osCAT2ISRC0(ISR_PWGA27,1)//178
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='28'">
    osCAT2ISRC0(ISR_PWGA28,1)//179
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='29'">
    osCAT2ISRC0(ISR_PWGA29,1)//180
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='32'">
    osCAT2ISRC0(ISR_PWGA32,1)//181
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='33'">
    osCAT2ISRC0(ISR_PWGA33,1)//182
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='34'">
    osCAT2ISRC0(ISR_PWGA34,1)//183
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='35'">
    osCAT2ISRC0(ISR_PWGA35,1)//184
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='36'">
    osCAT2ISRC0(ISR_PWGA36,1)//185
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='37'">
    osCAT2ISRC0(ISR_PWGA37,1)//186
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='38'">
    osCAT2ISRC0(ISR_PWGA38,1)//187
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='39'">
    osCAT2ISRC0(ISR_PWGA39,1)//188
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='40'">
    osCAT2ISRC0(ISR_PWGA40,1)//189
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='41'">
    osCAT2ISRC0(ISR_PWGA41,1)//190
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='42'">
    osCAT2ISRC0(ISR_PWGA42,1)//191
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='43'">
    osCAT2ISRC0(ISR_PWGA43,1)//192
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='44'">
    osCAT2ISRC0(ISR_PWGA44,1)//193
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='45'">
    osCAT2ISRC0(ISR_PWGA45,1)//194
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='46'">
    osCAT2ISRC0(ISR_PWGA46,1)//195
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'PWM']">
	<xsl:choose>
	<xsl:when test="value='47'">
	osCAT2ISRC0(ISR_PWGA47,1)//196
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
    <xsl:for-each select="IRQ_Set/FUN[@Register = 'CAN']">
	<xsl:choose>
	<xsl:when test="value='2'">
	osCAT2ISRC0(ISR_CAN2ERR,1)//209
	osCAT2ISRC0(ISR_CAN2REC,1)//210
	osCAT2ISRC0(ISR_CAN2TRX,1)//211
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
	<xsl:for-each select="IRQ_Set/FUN[@Register = 'UART']">
	<xsl:choose>
	<xsl:when test="value='3'">
    osCAT2ISRC0(ISR_UART3,1)//220
	osCAT2ISRC0(ISR_UART3_Tx,1)//221
	osCAT2ISRC0(ISR_UART3_Rx,1)//222
	osCAT2ISRC0(ISR_UART3_Error,1)//223
	</xsl:when>
    <xsl:otherwise>
    </xsl:otherwise>
    </xsl:choose>
	</xsl:for-each>
#pragma endasm

</xsl:template>
</xsl:stylesheet>
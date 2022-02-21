/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.		       
*				  All Rights Reserved.                 
*   Department :  CT AD NKG      				     
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   : IRQ header file
***********************************************************************/
/*-History--------------------------------------------------------------
* Version  Date   	 Name        Changes and comments
------------------------------------------------------------------------
* 0.1	   Apr 28,2016   PEI Jingli  Initial version
------------------------------------------------------------------------
* 0.2	   Jun 29,2016   LIU Chenxi  Correct errors during merging	
------------------------------------------------------------------------
* 0.3	   July 07,2016  PEI Jingli  Adapt 64pin MCU
* ----------------------------------------------------------------------
* 0.4         July 07,2016  LIU Chenxi  Refine code structure
* ----------------------------------------------------------------------
* 0.5         Aug 26,2016  PEI Jingli  redefine INT with 2 sources
* ----------------------------------------------------------------------
* 0.6         Dec 20,2016  ShangQiuju	add config according using hw.
*------------------------------------------------------------------------
* 0.7	   Jan 24,2017      ZhangJie  Fix Coverity warning.
*-----------------------------------------------------------------------
* 0.4         Apr 1,2017     PEI Jingli   Fix include files.
*=====================================================================*/

#ifndef  _IRQ_H
#define  _IRQ_H

#include "Config.h"
#include "Cpu.h"

/* ------------------- BIT DEFINES --------------------*/
#define  DEF_BIT_NONE                                   ((U16)0x00u)

#define  DEF_BIT_00                                     ((U16)0x01u)
#define  DEF_BIT_01                                     ((U16)0x02u)
#define  DEF_BIT_02                                     ((U16)0x04u)
#define  DEF_BIT_03                                     ((U16)0x08u)
#define  DEF_BIT_04                                     ((U16)0x10u)
#define  DEF_BIT_05                                     ((U16)0x20u)
#define  DEF_BIT_06                                     ((U16)0x40u)
#define  DEF_BIT_07                                     ((U16)0x80u)

#define  DEF_BIT_08                                   ((U16)0x0100u)
#define  DEF_BIT_09                                   ((U16)0x0200u)
#define  DEF_BIT_10                                   ((U16)0x0400u)
#define  DEF_BIT_11                                   ((U16)0x0800u)
#define  DEF_BIT_12                                   ((U16)0x1000u)
#define  DEF_BIT_13                                   ((U16)0x2000u)
#define  DEF_BIT_14                                   ((U16)0x4000u)
#define  DEF_BIT_15                                   ((U16)0x8000u)

#define  DEF_BIT_SET_08(val, mask)                     ((val) = (CPU_INT08U)(((CPU_INT08U)(val)) | ((CPU_INT08U) (mask))))

#define  DEF_BIT_SET_16(val, mask)                     ((val) = (CPU_INT16U)(((CPU_INT16U)(val)) | ((CPU_INT16U) (mask))))

#define  DEF_BIT_SET_32(val, mask)                     ((val) = (CPU_INT32U)(((CPU_INT32U)(val)) | ((CPU_INT32U) (mask))))

#define  DEF_BIT_SET_64(val, mask)                     ((val) = (CPU_INT64U)(((CPU_INT64U)(val)) | ((CPU_INT64U) (mask))))

#define  DEF_BIT_SET(val, mask)                 ((sizeof(val) == CPU_WORD_SIZE_08) ? DEF_BIT_SET_08(val, mask) :     \
                                                ((sizeof(val) == CPU_WORD_SIZE_16) ? DEF_BIT_SET_16(val, mask) :     \
                                                ((sizeof(val) == CPU_WORD_SIZE_32) ? DEF_BIT_SET_32(val, mask) :     \
                                                ((sizeof(val) == CPU_WORD_SIZE_64) ? DEF_BIT_SET_64(val, mask) : 0))))

#define  DEF_BIT_CLR_08(val, mask)                     ((val) = (CPU_INT08U)(((CPU_INT08U)(val)) & ((CPU_INT08U)~(mask))))

#define  DEF_BIT_CLR_16(val, mask)                     ((val) = (CPU_INT16U)(((CPU_INT16U)(val)) & ((CPU_INT16U)~(mask))))

#define  DEF_BIT_CLR_32(val, mask)                     ((val) = (CPU_INT32U)(((CPU_INT32U)(val)) & ((CPU_INT32U)~(mask))))

#define  DEF_BIT_CLR_64(val, mask)                     ((val) = (CPU_INT64U)(((CPU_INT64U)(val)) & ((CPU_INT64U)~(mask))))

#define  DEF_BIT_CLR(val, mask)                 ((sizeof(val) == CPU_WORD_SIZE_08) ? DEF_BIT_CLR_08((val), (mask)) :     \
                                                ((sizeof(val) == CPU_WORD_SIZE_16) ? DEF_BIT_CLR_16((val), (mask)) :     \
                                                ((sizeof(val) == CPU_WORD_SIZE_32) ? DEF_BIT_CLR_32((val), (mask)) :     \
                                                ((sizeof(val) == CPU_WORD_SIZE_64) ? DEF_BIT_CLR_64((val), (mask)) : 0))))



#define IRQ_INT_REG_ICxx_BASE                   ( (U32 )0xFFFF9000u)
/*address not continous*/
#define IRQ_INT_REG_ICxx_BASE_SEC                ( (U32 )0xFFFFA040u)

#define IRQ_INT_REG_ICxx(n)                     (*(U16 *)(((n)>31)?(IRQ_INT_REG_ICxx_BASE_SEC + (2 * ((n)-32))) : (IRQ_INT_REG_ICxx_BASE + (2 * (n))))	)

#define IRQ_INT_ICxx_EIMKn                       DEF_BIT_07
#define IRQ_INT_ICxx_EITBn                       DEF_BIT_06
#define IRQ_INT_ICxx_EIRFn                       DEF_BIT_12

void IRQ_Init_Setup (void);
void IRQ_IntClr           (U16     int_id);
void IRQ_IntDis           (U16  int_id);
void IRQ_IntEn            (U16     int_id);
void IRQ_IntDisAll        (void);
void  IRQ_IntClrAll        (void);
#endif                                                         


/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   : Shao Guangxian										   *
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
*-----------------------------------------------------------------------
* 0.1	   Dec 02,2016   PEI Jingli  Initial version
* ----------------------------------------------------------------------
* 0.2         Dec 20,2016  ShangQiuju	add EXTI_if.h for complie error.
*----------------------------------------------------------------------
* 0.3         Jan 24,2017    ZhangJie     Fix Coverity warning.
*=====================================================================*/
#ifndef _EXTI_H_
#define _EXTI_H_
#include "Config.h"
#include "IRQ_if.h"
#include "EXTI_if.h"

/**** Definition of constants ****/
/*INTP0~15 filter control register */
#define  GPIO_REG_FCLA0TLn_INTP_BASE		 ( (CPU_INT32U )0xFFC34020u)
#define  GPIO_REG_FCLA0TLn_INTP(n)           (*(CPU_REG08 *)((GPIO_REG_FCLA0TLn_INTP_BASE) + (n)*4))


/**** Definition of types ****/


/**** Definition of macros ****/


/**** Declaration of constants ****/


/**** Declaration of variables ****/
/*  relation of INTP channel and the INT  */
typedef struct{
  EXTI_TYPE  intp;
  U8  int_id;
}ST_INTP_INTID;

/* table of TAU channel and the INT  */
const ST_INTP_INTID Intp_INT_Table[EXTI_NUM]=
{
  {EXTI_00, INTP0}
 ,{EXTI_01, INTP1}
 ,{EXTI_02, INTP2}
 ,{EXTI_03, INTP3}
 ,{EXTI_04, INTP4}
 ,{EXTI_05, INTP5}
 
 #if MCU_PIN<=PIN64
 ,{EXTI_06, IRQ_INT_ID_MAX} /*invalid*/
 ,{EXTI_07, IRQ_INT_ID_MAX}
 ,{EXTI_08, IRQ_INT_ID_MAX}
#else
 ,{EXTI_06, INTP6}
 ,{EXTI_07, INTP7}
 ,{EXTI_08, INTP8}
#endif

#if MCU_PIN<=PIN100
 ,{EXTI_09, IRQ_INT_ID_MAX}
#else
,{EXTI_09, INTP9}
#endif

 ,{EXTI_10, INTP10}
 ,{EXTI_11, INTP11}
 
#if MCU_PIN<=PIN64
 ,{EXTI_12, IRQ_INT_ID_MAX}
#else
 ,{EXTI_12, INTP12}
#endif
#if MCU_PIN<=PIN80
 ,{EXTI_13, IRQ_INT_ID_MAX}
#else
 ,{EXTI_13, INTP13}
#endif

#if MCU_PIN<=PIN100
  ,{EXTI_14, IRQ_INT_ID_MAX}
  ,{EXTI_15, IRQ_INT_ID_MAX}
#else
 ,{EXTI_14, INTP14}
 ,{EXTI_15, INTP15}
#endif
};

/**** Declaration of functions ****/


#endif /* _EXTI_H_ */
/****************************** END OF FILE ***************************/

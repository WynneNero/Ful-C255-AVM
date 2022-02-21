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
*----------------------------------------------------------------------
* 0.2          Jan 24,2017    ZhangJie     Fix Coverity warning.
*=====================================================================*/
#ifndef _EXTI_IF_H_
#define _EXTI_IF_H_
#include "Define.h"

/**** Definition of constants ****/


/**** Definition of types ****/
/* INTP:external interruput channel*/
typedef enum
{
    EXTI_00 = 0x00,
    EXTI_01 = 0x01,	
    EXTI_02 = 0x02,	
    EXTI_03 = 0x03,	
    EXTI_04 = 0x04,
    EXTI_05 = 0x05,
    EXTI_06 = 0x06,
    EXTI_07 = 0x07,
    EXTI_08 = 0x08,
    EXTI_09 = 0x09,
    EXTI_10 = 0x0A,
    EXTI_11 = 0x0B,
    EXTI_12 = 0x0C,
    EXTI_13 = 0x0D,	
    EXTI_14 = 0x0E,
    EXTI_15 = 0x0F,
    EXTI_NUM
} EXTI_TYPE;

/* INTP trigger type*/
typedef enum
{
    EXTI_TRIGGER_LOW = 0x00,
    EXTI_TRIGGER_HIGH = 0x01,
    EXTI_TRIGGER_RISING = 0x02,
    EXTI_TRIGGER_FALLING = 0x03,
    EXTI_TRIGGER_RISFALL = 0x04
} EXTI_TRIGGER_TYPE;

/**** Definition of macros ****/
#if MCU_PIN ==PIN100
#define IS_EXTI_TYPE(exti_x)        ((exti_x<EXTI_NUM) && (EXTI_09!=exti_x)&&(EXTI_14!=exti_x)&&(EXTI_15 !=exti_x))
#elif (MCU_PIN ==PIN64)
#define IS_EXTI_TYPE(exti_x)        (((EXTI_00<=exti_x) &&(exti_x<=EXTI_05)) ||(EXTI_10==exti_x) ||(EXTI_11==exti_x))

#else
#define IS_EXTI_TYPE(exti_x)        (exti_x<EXTI_NUM)
#endif

/**** Declaration of constants ****/


/**** Declaration of variables ****/


/**** Declaration of functions ****/
extern void EXTI_Config( EXTI_TYPE intp, EXTI_TRIGGER_TYPE exti_trigger );
extern void EXTI_Cmd( EXTI_TYPE intp, FUNCTION_STATE state );

#endif /* _EXTI_IF_H_ */
/****************************** END OF FILE ***************************/


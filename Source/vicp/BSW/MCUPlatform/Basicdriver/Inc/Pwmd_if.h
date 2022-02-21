/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.		           *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									                   *
************************************************************************
* Object        :  Pwmd_if.h 
* Module        : 
* Instance      : 
* Description   : pwm diagnostic interface
*-----------------------------------------------------------------------
* Version: 
* Date: 
* Author: 
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
* ----------------------------------------------------------------------
* 0.1 Aug 18,2016   PEI Jingli  Initialize
------------------------------------------------------------------------
*0.2  Dec 15,2016   PEI Jingli  Add dutyType micro
------------------------------------------------------------------------
*0.3  Dec 16,2016   PEI Jingli  Add return type of PWD_SetDuty
------------------------------------------------------------------------
*0.4  Dec 20,2016   PEI Jingli  Change return value to ERR_TYPE
*-----------------------------------------------------------------------
*0.5  Jan 03,2017   PEI Jingli   Changes for codeReview result
*-----------------------------------------------------------------------
*0.6  Jan 10,2017   PEI Jingli   Remove micros
*----------------------------------------------------------------------
*0.7  Jan 24,2017    ZhangJie     Fix Coverity warning.
=======================================================================*/
#ifndef _PWMD_IF_H_
#define _PWMD_IF_H_
#include "define.h"

/**** Definition of micros ****/

/**** Definition of types ****/

/* PWM Ratio definition */
typedef enum PWMD_DUTYRATIO{
  E_PWMD_RATIO100=100u,
  E_PWMD_RATIO255=0xffu,
  E_PWMD_RATIO4095=0xfffu  /*max val=0xfff*/
}Enum_PwmdRatio_Type;

/**** Definition of macros ****/

/**** Declaration of constants ****/


/**** Declaration of variables ****/


/**** Declaration of functions ****/


extern void PWMD_Unit_Init(void);
extern void PWMD_Unit_Deinit(void);
extern ERR_TYPE PWMD_Config( U8 pwm_channel, Enum_PwmdRatio_Type dutyType, U16 duty );
extern BOOL PWMD_Cmd( U8 pwm_channel, FUNCTION_STATE state );
extern ERR_TYPE PWMD_SetDuty( U8 pwm_channel, Enum_PwmdRatio_Type dutyType, U16 duty );
extern U32 PWMD_GetFrequency(U8 pwm_channel);


#endif/*_PWMD_IF_H_*/
/**************** END OF FILE *****************************************/


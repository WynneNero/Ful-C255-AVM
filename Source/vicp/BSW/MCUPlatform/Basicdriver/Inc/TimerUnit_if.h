/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 										   *
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
------------------------------------------------------------------------
* 0.1	   Jun 26,2016   PEI Jingli  Initial version
------------------------------------------------------------------------
* 0.2	   Jun 29,2016   LIU Chenxi  Correct errors during merging		
------------------------------------------------------------------------
* 0.3	   July 07,2016  PEI Jingli  Adapt 64pin MCU
* ----------------------------------------------------------------------
* 0.4      July 07,2016  LIU Chenxi  Refine code structure
* ----------------------------------------------------------------------
* 0.5      July 21,2016  PEI Jingli  Refactor codes and interfaces.
* ----------------------------------------------------------------------
* 0.6      Aug  10,2016  PEI Jingli  add get TAU_clock interfaces.
* ----------------------------------------------------------------------
* 0.7      Oct 11,2016  PEI Jingli  Rename of PWM,Timer,Cap interface
------------------------------------------------------------------------
*0.8      Dec 15,2016  PEI Jingli  Add dutyType micro
------------------------------------------------------------------------
*0.9      Dec 20,2016  PEI Jingli  Change return value to ERR_TYPE
*----------------------------------------------------------------------
*1.0      Jan 12,2017    ZhangJie       Fix Coverity warning.
*-----------------------------------------------------------------------
*1.1      Jan 24,2017    ZhangJie     Remove unused include headfile.
*-----------------------------------------------------------------------
*1.2      Feb 15,2017   PEI Jingli   Fix codeReview results
*-----------------------------------------------------------------------
*1.3      Mar 08,2017   ZhangJie   Add us timer config function and interface to get system tick.
*=====================================================================*/
#ifndef _TIMERUNIT_IF_H
#define _TIMERUNIT_IF_H
#include "config.h"
#include "define.h"
/*  channel enum of Timer Array Unit
* TAUB0/B1/D0   chl 0~15
* TAUJ0/J1      chl 0~3
*/
typedef enum
{ 
 TAU_CH0,
 TAU_CH1,
 TAU_CH2,
 TAU_CH3,
 TAU_CH4,
 TAU_CH5,
 TAU_CH6,
 TAU_CH7,
 TAU_CH8, 
 TAU_CH9,
 TAU_CH10,
 TAU_CH11,
 TAU_CH12,
 TAU_CH13,
 TAU_CH14,
 TAU_CH15,
 TAU_CH_MAX
}TAU_CHANNEL;

typedef enum{
  E_CAP_PERIOD_FALLING=0,     /* capture function:Falling edge */
  E_CAP_PERIOD_RISING,           /* capture function:Rising edge  */
  E_CAP_WIDTH_FALL_RISE,     /* capture function:falling and Rising edges (low-width measurement selection) */
  E_CAP_WIDTH_RISE_FALL,     /* capture function:Rising and falling edges (high-width measurement selection) */
  E_CAP_ALL_EDGE_DETECT        /* just edge detect for capture-init interface, be not register value  */
}CAP_TYPE_ST;

/* Timer Array unit defination */
typedef enum
{
#if (MCU_PIN>=PIN100)
 TAUB0_U0,
#endif 

#if(MCU_PIN==PIN176)
 TAUB1_U1, /*for MCU of 176 pins*/
#endif 

 TAUD0_U2,
 TAUJ0_U3,
#if(MCU_PIN>=PIN100)
 TAUJ1_U4,
#endif 
 TAU_U_MAX
}TAU_UNIT;


/**** Declaration of functions ****/
extern void TAU_setup_init(void);
extern void TAU_setup_deinit( void);

/*hardware interval timer interface*/
extern ERR_TYPE TAU_Timer_Config(TAU_UNIT un, TAU_CHANNEL chm, U32 MS_count, BOOL bWaveOutput, BOOL bPeriodic);
extern ERR_TYPE TAU_Timer_Config_US(TAU_UNIT un, TAU_CHANNEL chm, U32 US_count, BOOL bWaveOutput, BOOL bPeriodic);
extern BOOL TAU_Timer_Cmd(TAU_UNIT un, TAU_CHANNEL chm, FUNCTION_STATE state);

/*PWM interface*/
extern ERR_TYPE TAU_PWM_Config (TAU_UNIT un, TAU_CHANNEL chm, TAU_CHANNEL sl_chm, U32 freHZ, U16 RatioType, U16 duty );
extern BOOL TAU_PWM_Cmd(TAU_UNIT un, TAU_CHANNEL chm, TAU_CHANNEL sl_chm, FUNCTION_STATE state);
extern ERR_TYPE TAU_PWM_SetDuty (TAU_UNIT un, TAU_CHANNEL chm, TAU_CHANNEL sl_chm, U16 ratioType, U16 duty );

/*capture interface*/
ERR_TYPE TAU_Capture_Config(TAU_UNIT un, TAU_CHANNEL chm, CAP_TYPE_ST edge);
extern BOOL TAU_Capture_Cmd(TAU_UNIT un, TAU_CHANNEL chm, FUNCTION_STATE state);

/*os timer interface*/
extern BOOL TAU_OSTimer_Init(U32 osc_freq, U32 tick_time );
extern void TAU_OSTimer_Cmd(BOOL enable);

/* get clock frequecy of a tau channel */
ERR_TYPE TAU_GetClolckFre_Channel( TAU_UNIT un, TAU_CHANNEL chm, U32 *fre);

/*get system tick by 10us*/
extern U16 TAU_GetSystemTick_10us(void);

#endif/*_TIMERUNIT_IF_H*/
/**************** END OF FILE *****************************************/


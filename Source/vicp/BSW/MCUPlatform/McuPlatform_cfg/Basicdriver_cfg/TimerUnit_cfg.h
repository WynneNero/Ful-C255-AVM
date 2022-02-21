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
* ----------------------------------------------------------------------
* 0.1  Apr 15,2016    PEI Jinglii      Initial. clock hand in MCU work mode
------------------------------------------------------------------------
* 0.2  Jun 29,2016   LIU Chenxi  Correct errors during merging
* ----------------------------------------------------------------------
* 0.3  Aug 10,2016  PEI Jinglii  defined ISR callback array
* ----------------------------------------------------------------------
* 0.4  Aug 29,2016  PEI Jinglii  Add clock config for all channels. Optimize stack using
*----------------------------------------------------------------------
* 0.5  Dec 20,2016   ShangQiuju  add using file "mcu_if.h"
*------------------------------------------------------------------------
* 0.6  Jan 24,2017  ZhangJie  Fix Coverity warnings.
*-----------------------------------------------------------------------
* 0.7  Feb 15,2017   PEI Jingli   Fix codeReview results
*-----------------------------------------------------------------------
* 0.8  Feb 22,2017   PEI Jingli   Add const tau_func_callback 
*=====================================================================*/
#ifndef _TIMERUNIT_CFG_H
#define _TIMERUNIT_CFG_H
#include "TimerUnit_if.h"

/******************************************************************************
 *                                           Timer Array Unit              
 * configrate prescaler clock with each TAUB,D,J
 ******************************************************************************/
extern const U8 tauCfg[TAU_U_MAX][5];

/*   all channels configration   */
extern const U8 tauChanlCfg[TAU_U_MAX][TAU_CH_MAX];

/* ISR callback for all TAU channel */
extern const Func_Param64_Proc tau_func_callback[TAU_U_MAX][TAU_CH_MAX];

#endif/*_TIMERUNIT_CFG_H */
/**************** END OF FILE *****************************************/

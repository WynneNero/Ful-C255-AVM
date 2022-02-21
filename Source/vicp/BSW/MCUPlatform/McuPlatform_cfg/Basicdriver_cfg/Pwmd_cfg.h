/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.	                                        *
*				  All Rights Reserved.                                                                 *
*   Department : CT AD                                                                                          *
*   AUTHOR	   : Pei Jingli                                                                                      *
************************************************************************
* Object        : PWMD_cfg.h
* Module        :
* Instance      :
* Description   : For configration 
*-----------------------------------------------------------------------
* Version:  0.1
* Date: 2017-01-03
* Author: Pei Jingli
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
*-----------------------------------------------------------------------
* 0.1   Jan 03,2017   PEI Jingli   Initial version.Changes for codeReview result
*-----------------------------------------------------------------------
* 0.2   Jan 18,2017    ZhangJie     Remove unused include headfile.
*-----------------------------------------------------------------------
* 0.3   Apr 04,2017   PEI Jingli   Fix headfile included.
*=====================================================================*/
#ifndef _PWMD_CFG_H_
#define _PWMD_CFG_H_
#include "Pwmd.h"
#include "define.h"

/**** Definition of constants ****/

/**** Definition of types ****/


/**** Definition of macros ****/


/**** Declaration of constants ****/

/**** Declaration of variables ****/
extern const U16 pwmClocKCfg[E_PWMCLK_MAX];
extern const PWM_CLKTYPE pwmChannelClocK[PWM_CHANNEL_MAX];

/**** Declaration of functions ****/

#endif
/**************** END OF FILE *****************************************/

/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD                                                 *
*   AUTHOR	   : 
************************************************************************
* Object        : 
* Module        : WATCHDOG config item.
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
* 0.1    Jan 16,2017  RenWeimin  Add test code.
*-----------------------------------------------------------------------
* 0.2   Jan 24,2017   ZhangJie   Fix Coverity warnings.
*-----------------------------------------------------------------------
* 0.3    Feb 09,2017   ZhangJie   Remove EOL definition.
*=====================================================================*/
#ifndef _WDG_CFG_H_
#define _WDG_CFG_H_

/**** Definition of macros ****/

/* option byte must be the same as below settings */
#define WDG_START_MODE   WDG_START_SW	/*WDG_START_DEFAULT*/
#define WDG_VAC_SET	WDG_FIXED	/*WDG_VARIABLE*/

/* for WDT0, range from 273ms~35s
 WDTATCKI = fRL(240 kHz) / 128  = 1,875Hz
 overflow time = 2^WDG_TIMEOUT * 512 / WDTATCKI = 2^WDG_TIMEOUT * 273ms
*/
#define WDG_TIMEOUT   	WDG_TIME_2184MS

#endif

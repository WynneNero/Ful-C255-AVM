/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD                                                 *
*   AUTHOR	   : 
************************************************************************
* Object        : 
* Module        : WATCHDOG
* Instance      :
* Description   :
*-----------------------------------------------------------------------
* Version: 
* Date: 
* Author: 
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
*------------------------------------------------------------------------
* 0.1	   Jun 26,2016                             Initial version
*------------------------------------------------------------------------
* 0.2	   Jan 18,2017      ZhangJie           Remove typedef to solute Coverity warning.
*=====================================================================*/
#ifndef _WDG_H_
#define _WDG_H_


/**** Definition of types ****/
enum
{
	WDG_START_SW=0,			//Writing an activation code to the WDTA trigger register starts WDTA
	WDG_START_DEFAULT		//counter starts after reset release.
};

enum
{
	WDG_FIXED=0,
	WDG_VARIABLE
};	

enum
{
	WDG_TIME_273MS=0,
	WDG_TIME_546MS,
	WDG_TIME_1092MS,
	WDG_TIME_2184MS,
	WDG_TIME_4368MS,
	WDG_TIME_8736MS,
	WDG_TIME_17472MS,
	WDG_TIME_34944MS
};	

/**** Definition of constants ****/

/**** Definition of macros ****/

/**** Declaration of variables ****/

/**** Declaration of functions ****/

#endif /* _WDG_H_ */
/****************************** END OF FILE ***************************/



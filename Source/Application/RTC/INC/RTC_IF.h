/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   :            										   *
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
* 
*=====================================================================*/
#ifndef _RTC_IF_H_
#define _RTC_IF_H_ 

#include "RTC.h"

/**** Definition of constants ****/


/**** Definition of types ****/ 

/**** Definition of macros ****/

/**** Declaration of constants ****/

/**** Declaration of variables ****/

/**** Declaration of functions ****/
extern void Calendar_Message_Send(void);
extern void Calendar_Message_Handler(U16 commandid,U8* data);
extern void Calendar_Init(void);
extern void RTC_PowerOn_Init(void);
extern void Calendar_PowerOn_Handler(void);
#endif /*_RTC_IF_H_*/

/****************************** END OF FILE ***************************/


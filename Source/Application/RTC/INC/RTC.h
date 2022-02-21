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
#ifndef _RTC_H_
#define _RTC_H_ 
#include "CONFIG.H"
#include "IIC_IF.h"

/**** Definition of constants ****/

/**** Definition of types ****/ 
typedef struct
{
	U8 second;
	U8 minute;
	U8 hour;
	U8 date;
	//U8 week;
	U8 month;
	U8 year;
} RTC_DATA_TYPE;

/**** Definition of macros ****/
typedef enum
{
	REG_SECOND = 0x02,
	REG_MINUTE = 0x03,
	REG_HOUR = 0x04,
	REG_DAY = 0x05,
	REG_WEEK = 0x06,
	REG_MONTH = 0x07,
	REG_YEAR = 0x08,

}RTC_REG;

/**** Declaration of variables ****/
#define ADDR_RTC 0x51 

#define RTC_MODULE_INIT_TIME 30  /* 30x100ms=3S */


/**** Declaration of functions ****/
void RTC_Init(void);
void Calendar_Init(void);
RTC_DATA_TYPE Calendar_Get(void);
void Calendar_Set(RTC_DATA_TYPE *time);
U8 Calendar_SendFormat_Transfer(U8* data, U8* hexdata);
U8 Calendar_RecFormat_Transfer(U8* data, U8* hexdata);
void Hex2BCD(U8* a);
void BCD2Hex(U8* a);
#endif /*_RTC_H_*/

/****************************** END OF FILE ***************************/


/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									   *
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
* 0.1  Apr 15,2016                Initial version.  
*------------------------------------------------------------------------
* 0.2 Jan 12,2017  ZhangJie  Fix Coverity warnings.
* ----------------------------------------------------------------------
* 0.3 Jan 24,2017   ZhangJie   Remove unused include file.
*=====================================================================*/
#ifndef _BUSMNG_H_
#define _BUSMNG_H_ 
#define BUSMNG_PASS_1
#include "BusMng_def.h"

#define BUSMNG_PASS_2
#include "BusMng_def.h"
/**** Definition of constants ****/

/**** Definition of macros ****/

/**** Declaration of constants ****/
/**** Declaration of variables ****/

typedef enum
{
	BUSMNG_REQUEST_ACCEPTED,
	BUSMNG_REQUEST_REQUESTED,
	BUSMNG_REQUEST_FINISHED,
	BUSMNG_REQUEST_FAIL
}BusMng_RequestBusType;

enum
{
 BUSMNG_DEV_IDLE,
 BUSMNG_DEV_REQBUS,
 BUSMNG_DEV_USEBUS,
 BUSMNG_DEV_RELBUS
};

/*
typedef struct _DevBusCfg
{
U8 BusID;
}BusMng_DevBusCfgType;
*/

/**** Declaration of functions ****/
typedef  void( *BusRequested )(void);
typedef  void( *BusReleased )(void);


void BusMng_Init(void);
void BusMng_DeInit(void);
void BusMng_Job(void);
BOOL BusMng_IsBuy(U8 DevId);
BusMng_RequestBusType BusMng_Request(U8 DevId, BOOL isWaiting,BusRequested fBusRequested);
BusMng_RequestBusType BusMng_Release(U8 DevId, BOOL isWaiting,BusReleased fBusReleased);

#endif /*_BUSMNG_H_*/

/****************************** END OF FILE ***************************/


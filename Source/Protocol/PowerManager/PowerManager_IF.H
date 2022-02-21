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
*
*=====================================================================*/
#ifndef _POWER_MANAGER_IF_H_
#define _POWER_MANAGER_IF_H_

extern void PowerManager_Init_S0(void);
extern void PowerManager_Init_S3(void);
extern void PowerManager_5msEntry(void);
//extern void Dispatch_Virtual_Source_Key_Value(U8* data);
extern void TAUB0I11_timer_callback(U64 data);
#endif /*_POWER_MANAGER_IF_H_*/

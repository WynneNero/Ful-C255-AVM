/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD NJ     									   *
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
* Version       Date           Name            Changes and comments
* 0.1    	2015-12-15	ShangQiuju		Initial
*=====================================================================*/
/**** System include files ****/
#ifndef _EOL_APP_H_
#define _EOL_APP_H_

#include "CONFIG.H"

#ifdef EOL_OPTION
#include "TYPES.H"
#include "MP5_MSG_NAVI_IF.H"

extern void Eol_DISPATCHERREQMSG(U8 msgid, U8* data, U8 len);
extern void Eol_DISPATCHERACK(U8 msgid, BOOL isSent);
extern void Eol_DISPATCHERREPMSG(U8 msgid, U8 Result, U8* data, U8 len);
extern void EOL_DISPATCHERSPIMSG(U16 commandid, U8* data);

extern void EolApp_spi_msg_handle(NAVI_FRAME *msg);
extern BOOL EolApp_GetEolStatus(void);
extern void EolApp_SetJ6SDiagState(void);
extern void EolApp_SetJ6UpgradeState(U8 result);
extern void EOL_S1S2Init(void);
#endif
#endif
/**************** END OF FILE *****************************************/

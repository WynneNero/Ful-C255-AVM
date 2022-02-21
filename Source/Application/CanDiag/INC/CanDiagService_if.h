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
* Version       Date                Name            Changes and comments
* 0.1           2015/12/22    ShangQiiuju       init version
* 0.2           2017/02/07    ZhangJie            Reinit for vicp upgrade template.
*=====================================================================*/
#ifndef _CAN_DIAG_SERVICE_IF_H_
#define _CAN_DIAG_SERVICE_IF_H_
#include "config.h"
#include "appdesc_cfg.h"
#include "desc.h"

extern U8 upgradeflag;

#ifdef CAN_DIAG_OPTION
extern void CanDiagServiceInit(void);
#endif

//typedef void (*CanDiagFuncCallBackType)(APPL_DESC_SERVICE_ID_TYPE MsgContextId, DescMsgContext* pMsgContext);

extern void Can_response(DescMsgContext* pMsgContext);
extern void CanDiag_SetDelayTime(void);
#ifdef CAN_DIAG_OPTION
typedef enum
{
    E_POSITIVE_DIAG_RESPONSE,
	E_NEGATIVE_DIAG_RESPONSE,
    E_NEGATIVE_DIAG_RESPONSE_OUT_FOR_RANGE,
}E_CAN_DIAG_RESP_TYPE;

//extern CanDiagFuncCallBackType CanDiagAppCallBack;
extern void CanDiagAppCallBack(APPL_DESC_SERVICE_ID_TYPE MsgContextId, DescMsgContext* pMsgContext);
#endif

#endif


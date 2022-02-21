/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                         *
*   AUTHOR     :                                       *
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
* 0.1  Mar 01,2013  NI Rujin    Initial version
* ----------------------------------------------------------------------
* 0.2  Jul 10,2013  SHANG Qiuju Add Navi event handler
* ----------------------------------------------------------------------
* 0.3  Nov 01,2013  LIU Chenxi  Add incoming call event handler
* ----------------------------------------------------------------------
* 0.4  Nov 06,2013  SHNAG Qiuju update incoming call event handling
* ----------------------------------------------------------------------
* 0.5  Dec 25,2013  SHNAG Qiuju correct parameter checking for sending
       NaviEvent
*----------------------------------------------------------------------
* 0.6 Mar 07,2017   PEI Jingli    Fix headfile included.
*=====================================================================*/

#include "TYPES.h"
#include "Signal_if.h"
#include "SocTransmitManager.h"


///TODO: 


void SocTransmitManager_Init(void){};
void SocTransmitManager_DeInit(void){};
void SocTransmitManager_Send(TRANSMITTYPE type, U8* buf){};
void SocTransmitManager_10ms_Entry(void){};
void SocTransmitManager_ForwardMsg(U8* pMessage){};
void SocTransmitManager_SentResult(U16 commandid, BOOL isSent){};
void SocTransmitManager_GetResp(U16 commandid, U8*pMessage){};



/**************** END OF FILE *****************************************/


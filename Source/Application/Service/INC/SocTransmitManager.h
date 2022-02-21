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
* 0.1  Jul 10,2013  SHANG Qiuju Initial version
*=====================================================================*/
#ifndef _SOC_TRANSMIT_MANAGER_H_
#define _SOC_TRANSMIT_MANAGER_H_

#include "CONFIG.H"
#include "TYPES.H"

/**** Definition of constants ****/
/**** Definition of macros ****/
/**** Declaration of constants ****/
/**** Declaration of variables ****/
typedef enum
{
    E_TRANSMIT_NUMBER,
} TRANSMITTYPE;



typedef void (*SOCSERVICE_EVENTSEND_RESULT_HANDLER)(BOOL sent) ;



/**** Declaration of functions ****/
void SocTransmitManager_Init(void);
void SocTransmitManager_DeInit(void);
void SocTransmitManager_Send(TRANSMITTYPE type, U8* buf);
void SocTransmitManager_10ms_Entry(void);
void SocTransmitManager_ForwardMsg(U8* pMessage);
void SocTransmitManager_SentResult(U16 commandid, BOOL isSent);
void SocTransmitManager_GetResp(U16 commandid, U8*pMessage);
/**** Definition of macros ****/




#endif /*_SOC_TRANSMIT_MANAGER_H_*/

/****************************** END OF FILE ***************************/


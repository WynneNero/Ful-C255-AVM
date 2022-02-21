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
*
*=====================================================================*/
#ifndef _EOL_SERVICE_H_
#define _EOL_SERVICE_H_

#include "CONFIG.H"

#ifdef EOL_OPTION
#include "TYPES.H"
#include "eolCommunicator.h"
/**** Definition of constants ****/

#define EOL_ERRORWAIT 150   // 3S
#define T_RECEVIE_MAXTIME 1500 // 30s
#define N_SENDFAIL_MAXCOUNT 15 //send fail 
/**** Definition of macros ****/


/**** Declaration of constants ****/
typedef void (*EOLSERVER_REQMSG_HANDLER)(U8 Msgid, U8* data, U8 len);
typedef void (*EOLSERVER_RESPMSG_HANDLER)(U8 Msgid, U8 result,U8* data, U8 len);
typedef void (*EOLSERVER_SEND_RESULT_HANDLER)(U8 Msgid, BOOL isSend) ;
/**** Declaration of variables ****/

typedef enum
{
    E_EOLSERVICE_IDLE,
    E_EOLSERVICE_READY,
    E_EOLSERVICE_CONNECTED,
    E_EOLSERVICE_ERROR
} E_EOLSERVICE_STATE;

enum
{
    E_ERROR_NO_ERROR =0x00,                    //NO_ERROR
    E_ERROR_PRECONDITION_NOT_FULFILLED=0x01,   //requested actions could not be performed due to condition not fulfilled.    i.e. request to use protected feature when service is not activated
    E_ERROR_BUSY=0x02,                         // Resource for process the request is not available.
    E_ERROR_HW_FAIL=0x03,                      //Error caused by HW failure
    E_ERROR_CHANNEL_BUSY = 0x04,                       // make call request not allow because of channel busy
    E_ERROR_OTHER=0x0F,                        // Other reasons
};


typedef enum
{
    E_MAKECALL,
    E_REVCALL,
    E_ENDCALL,
    E_GETPHONESTATUS,
    E_SENDDTMF,
    E_REQNUM
} PHONE_REQ;

/**** Declaration of functions ****/
void EolService_Init(void);
void EolService_DeInit(void);
void EolService_20msEntry(void);
BOOL EolService_SendMsg(U8 MsgId,U8* Msgdata,U8 Len);

/**** Definition of macros ****/

//CONFIG
extern void EolEvent_ACK(U8 msgid, BOOL isSent);
extern void EolEvent_RepMsg(U8 Msgid, U8 result,U8* data, U8 len);

extern void Eol_DISPATCHERREQMSG(U8 msgid, U8* data, U8 len);
extern void Eol_DISPATCHERACK(U8 msgid, BOOL isSent);
extern void Eol_DISPATCHERREPMSG(U8 msgid, U8 Result, U8* data, U8 len);



#define EolAPP_REPMSG(Msgid, Result,data, len)    Eol_DISPATCHERREPMSG(Msgid, Result,data, len) 
#define EolAPP_REQUESTMSG(Msgid, data, len)  Eol_DISPATCHERREQMSG(Msgid, data, len)
#define EolAPP_ACK(Msgid,isSend)  Eol_DISPATCHERACK(Msgid,isSend)
extern U8 EolService_GetState(void);
#endif
#endif /*_EOL_SERVICE_H_*/

/****************************** END OF FILE ***************************/


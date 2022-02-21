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
*=====================================================================*/
#include "config.h"

#ifdef EOL_OPTION
#include "eolService.h"
#include "eolCommunicator.h"


static void DataReset(void);
void EolDataHandler(void);
void DispatcherUartReqMsg(U8 Msgid, U8* data, U8 len);
void DispatcherUartRepMsg(U8 Msgid, U8 result,U8* data, U8 len);
void DispatcherUartSentAck(U8 Msgid, BOOL isSend) ;

E_EOLSERVICE_STATE EOLServiceState;

U16 uRecvMonitor;
U8 uSentFailCount;
U8 uErrorCnt;

//receive request
RepMsg Respose;
ReqMsg  Request;

U8 SentMsgid;
BOOL IsSent;

U8 EventMsg[2];
U8 ConnectMsg;
BOOL B_EOLCommError;
BOOL sHBconnected;
U8 uSendMsgData[50];

/***********************************************************************
*  Name        : EolService_Init
*  Description : Init driver manager
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EolService_Init(void)
{
    EOLServiceState=E_EOLSERVICE_IDLE;
    B_EOLCommError = FALSE;
    DataReset();
    sHBconnected = FALSE;
    EolMsg_ControlCommunication(TRUE);
}

/***********************************************************************
*  Name        : EolService_DeInit
*  Description : DeInit driver manager
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EolService_DeInit(void)
{
    EOLServiceState=E_EOLSERVICE_IDLE;
    EolMsg_ControlCommunication(FALSE);
}

/***********************************************************************
*  Name        : EolService_GetState
*  Description : Get driver manager status
*  Parameter   : None
*  Returns     : None
***********************************************************************/
U8 EolService_GetState(void)
{
    return EOLServiceState;
}

/***********************************************************************
*  Name        : EolService_20msEntry
*  Description :
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EolService_20msEntry(void)
{    
    switch(EOLServiceState)
    {
        case E_EOLSERVICE_IDLE:
                EolDataHandler();
                EOLServiceState=E_EOLSERVICE_CONNECTED;
        break;

        case E_EOLSERVICE_READY:
                EolDataHandler();
            break;

        case E_EOLSERVICE_CONNECTED:
                EolDataHandler();
            break;

        case E_EOLSERVICE_ERROR:
            uErrorCnt--;

            if(uErrorCnt==0)
            {
                DataReset();
                EOLServiceState=E_EOLSERVICE_IDLE;
            }
            break;
        default:
            break;
    }

    Request.MsgId=E_MSGID_INVALID;
    Respose.MsgId=E_MSGID_INVALID;
    SentMsgid=E_MSGID_INVALID;

}

void EolService_RequestMsgIn(U8 msgid, U8* data, U8 len)
{
    Request.MsgId=msgid;
    Request.pMsgData=data;
    Request.MsgLen=len;
}

void EolService_SendACKIn(U8 msgid, BOOL isSent)
{
    SentMsgid=msgid;
    IsSent=isSent;
}

BOOL EolService_SendMsg(U8 MsgId, U8* Msgdata,U8 Len)
{
    if(EOLServiceState!=E_EOLSERVICE_CONNECTED)return FALSE;
    uSendMsgData[0] = Len+5;
    uSendMsgData[1] = 0xFF;
    uSendMsgData[2] = GetEOLMessageIDValue(MsgId);
    uSendMsgData[3] = 0xFF;
    uSendMsgData[4] = 0xFF;
    if(Msgdata!=NULL)
    {
        _memcpy(uSendMsgData+5, Msgdata, Len);
    }
    EolMsg_SendRepMsage(uSendMsgData);
	return TRUE;
}

//private

void EolDataHandler(void)
{
    switch(EOLServiceState)
    {
        case E_EOLSERVICE_IDLE:
            break;

        case E_EOLSERVICE_READY:
            break;

        case E_EOLSERVICE_CONNECTED:
            uRecvMonitor++;

            if(Request.MsgId!=E_MSGID_INVALID)
            {
                uRecvMonitor=0;
                DispatcherUartReqMsg(Request.MsgId,Request.pMsgData,Request.MsgLen);
            }

            if(SentMsgid!=E_MSGID_INVALID)
            {
                if(IsSent==FALSE)
                {
                    uSentFailCount++;
                }
                else
                {
                    uSentFailCount=0;
                }
                DispatcherUartSentAck(SentMsgid, IsSent);
            }
            break;
        case E_EOLSERVICE_ERROR:
            break;
        default:
            break;
    }
}

/***********************************************************************
*  Name        : DataReset
*  Description :
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void DataReset(void)
{
    uRecvMonitor=0;
    uSentFailCount=0;
    uErrorCnt=0;

    Request.MsgId=E_MSGID_INVALID;
    Respose.MsgId=E_MSGID_INVALID;
    SentMsgid=E_MSGID_INVALID;

}

//Config
/***********************************************************************
*  Name        : Dispatcher_ReqMsg
*  Description :
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void DispatcherUartReqMsg(U8 Msgid, U8* data, U8 len)
{
    if(Msgid<E_MSGID_NUM)//E_MSGID_NUM
    {
        EolAPP_REQUESTMSG(Msgid, data, len);
    }
    else
    {
        //..do nothing
    }

}

/***********************************************************************
*  Name        : DispatcherUartRepMsg
*  Description :
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void DispatcherUartRepMsg(U8 Msgid, U8 result,U8* data, U8 len)
{
    if(Msgid<E_MSGID_NUM)
    {
            EolAPP_REPMSG(Msgid, result, data, len);
    }
}

/***********************************************************************
*  Name        : DispatcherUartSentAck
*  Description :
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void DispatcherUartSentAck(U8 Msgid, BOOL isSend)
{
    if(Msgid<E_MSGID_NUM)
    {
        EolAPP_ACK(Msgid, isSend);
    }
}

#endif
/**************** END OF FILE *****************************************/


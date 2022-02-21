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
#ifndef _EOL_MSGHANDLER_H_
#define _EOL_MSGHANDLER_H_
#include "CONFIG.H"

#ifdef EOL_OPTION
#include "TYPES.H"

#include "eolMsg_Cfg.h"

/**** Definition of constants ****/
#define MAX_MSG_QUEUE 5
#define T_WAITSENDCOUNT   300 // 3s
#define T_SEND_TIMECNT 4
/**** Definition of macros ****/
#define MSGID_LEN 5

typedef struct
{
    U8 MsgId;
    U8* pMsgData;
    U8   MsgLen;
} ReqMsg;

typedef struct
{
    U8 MsgId;
    U8* pMsgData;
    U8   MsgLen;
    U8  ResultCode;
} RepMsg;

/**** Declaration of constants ****/
typedef struct
{
    U8   MsgId;
    U8* pMsgData;
    U8  MsgLen;
    U8  ResultCode;
    U8  PriCount;//Priority value
    U8 RetryCount;
    BOOL isReq;
} MsgInfo;

/**** Declaration of variables ****/



/**** Declaration of functions ****/
extern void EolMsg_Init(void);
extern void EolMsg_DeInit(void);
extern void EolMsg_20ms_Entry(void);
extern U8   EolMsg_SendRepMsage(U8* pMsg);
extern void EolMsg_ControlCommunication(BOOL isEnable);



#endif
#endif /*_EOL_MSGHANDLER_H_*/

/****************************** END OF FILE ***************************/


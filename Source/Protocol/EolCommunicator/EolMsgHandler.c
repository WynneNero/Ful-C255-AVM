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
#include "CONFIG.H"

#ifdef EOL_OPTION
#include "Hal_if.h"
#include "TYPES.H"
#include "EOLMsgHandler.h"
#include "EOLMsg_Cfg.h"
#include "SocMsgHandler.h"

#include "EolService.h"

static void Data_Reset(void);
static void ResetInfo(MsgInfo* pInfo);

void EolMsg_ReceiveCallback(U8* data, U8 len);
void EolMsg_Sent(BOOL isSent);
BOOL IsRecieveReqMsg(U8* pdata, U8 len);
U8 UnPackMsgFrame(U8* pdata, U8 len,U8* pFramlen);
U8 PackageRepMsgFrame(U8 MsgID, U8* pdata, U8 len, U8 ResultCode);
U8 PackageReqMsgFrame(U8 MsgID, U8* pdata, U8 len);
BOOL EolMsg_SendMessage(U8* pData, U8 len);
void UartDeviceCallback (U8 evetype);
void RXmsg_Handler(void);
void TXmsg_Handler(void);

MsgInfo MsgQueue[MAX_MSG_QUEUE];
MsgInfo SendingMsg;
U8 SendMsgFrame[MAX_EOL_BUFF];
U8* RevMsgFrame;//TODO: handler buffer for multi-recv and send
U8 Reclen;

U8 uRevFrame[MAX_EOL_BUFF];
BOOL bAckRec;
BOOL bFailAckRec;

U16 WaitSendingTimer;
BOOL bWaitingSending;
U8 EnableReq;

U16 uSentTimeCnt;
/***********************************************************************
*  Name        : EolMsg_Init
*  Description : Init EOL msg handler        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EolMsg_Init(void)
{
  Data_Reset();
}

/***********************************************************************
*  Name        : EolMsg_DeInit
*  Description : DeInit EOL msg handler        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EolMsg_DeInit(void)
{
  Data_Reset();
}

/***********************************************************************
*  Name        : Data_Reset
*  Description :       
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Data_Reset(void)
{
  U8 i=0;
  
   EnableReq=E_NO_CONTROL;
  bAckRec=FALSE;;
  bFailAckRec=FALSE;;
  bWaitingSending=FALSE;
  WaitSendingTimer=0;
  uSentTimeCnt = 0;
  
  for(;i<MAX_MSG_QUEUE;i++)
  {
   ResetInfo(&MsgQueue[i]);	
  }
  ResetInfo(&SendingMsg);
}
/***********************************************************************
*  Name        : EolMsg_20ms_Entry
*  Description : EOL msg task        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EolMsg_20ms_Entry(void)
{
 U8 Req =  EnableReq;

 EnableReq=E_NO_CONTROL;
 
 if(Req==E_NO_CONTROL)
 {
  TXmsg_Handler();
  RXmsg_Handler();
 }
 else if(Req==E_ENABLE_CONTROL)
 {
      HAL_Open(DEV_EOLDRIVER);
 }
 else if(Req==E_DISABLE_CONTROL)
 {
      HAL_Close(DEV_EOLDRIVER);
      Data_Reset();
 }
 
}

/***********************************************************************
*  Name        : EOL_AckReceive
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Eol_AckReceive(void)
{
  UartDeviceCallback(E_DATA_SENT);
}

/***********************************************************************
*  Name        : Eol_NAckReceive
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Eol_NAckReceive(void)
{
  UartDeviceCallback(E_DATA_SENT_FAIL);
}

/***********************************************************************
*  Name        : EolMsg_ControlCommunication
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EolMsg_ControlCommunication(BOOL isEnable)
{
  if(isEnable==TRUE)
  {
      EnableReq=E_ENABLE_CONTROL;
  }
  else
  {
	EnableReq=E_DISABLE_CONTROL;
  }

}



/***********************************************************************
*  Name        : EolMsg_SendRepMsage
*  Description : EOL msg task        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
U8 EolMsg_SendRepMsage(U8* pMsg)
{
 U8* pData=pMsg;
 U8 len=pMsg[0];
 
 return(EolMsg_SendMessage(pData,len)==TRUE);
}

/***********************************************************************
*  Name        : RX_Handler
*  Description : RX_Handler       
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void RXmsg_Handler(void)
{
    U8 reclen =0; 

    reclen=HAL_Read(DEV_EOLDRIVER,uRevFrame,MAX_EOL_BUFF);
    if(reclen>0)
    {
        EolMsg_ReceiveCallback(uRevFrame, reclen);
    }

    if(bAckRec==TRUE)
    {
        bWaitingSending=FALSE;
        bAckRec=FALSE;
        EolMsg_Sent(TRUE);
    }

    if(bFailAckRec==TRUE)
    {
        bWaitingSending=FALSE;
        bFailAckRec=FALSE;
        EolMsg_Sent(FALSE);
    }

    if(bWaitingSending==TRUE)
    {
        if(WaitSendingTimer>0)WaitSendingTimer--;
        if(WaitSendingTimer==0)
        {
            bWaitingSending=FALSE;
            EolMsg_Sent(FALSE);
        }
    }
}


/***********************************************************************
*  Name        : TX_Handler
*  Description :      
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void TXmsg_Handler(void)
{
 U8 i=0;
 U8 HighCount =0;
 U8 HighIndex =MAX_MSG_QUEUE;

  if(uSentTimeCnt>0)
  {
    uSentTimeCnt--;
    return;
  }
 
  if(SendingMsg.MsgId!=E_MSGID_INVALID) return;//sending one message
  
  //Get the high priority message
  for(;i<MAX_MSG_QUEUE;i++)
  {    
    if(MsgQueue[i].MsgId!=E_MSGID_INVALID)
   {
    if(HighCount<MsgQueue[i].PriCount)
    {
     HighCount =MsgQueue[i].PriCount;
     HighIndex=i;
    }
   }
  }
   
  if(HighIndex!=MAX_MSG_QUEUE)
  {
    U8 len=0;
    U8 MessageId =0;
   if(MsgQueue[HighIndex].isReq==FALSE)
   {
     len=PackageRepMsgFrame(MsgQueue[HighIndex].MsgId,
	 	MsgQueue[HighIndex].pMsgData,
	 	MsgQueue[HighIndex].MsgLen,
	 	MsgQueue[HighIndex].ResultCode);
   }
   else
   {
     len=PackageReqMsgFrame(MsgQueue[HighIndex].MsgId,
	 	MsgQueue[HighIndex].pMsgData,
	 	MsgQueue[HighIndex].MsgLen);
   }
   
   if(EolMsg_SendMessage(SendMsgFrame,len)==TRUE)
   {
      SendingMsg=MsgQueue[HighIndex];
     ResetInfo(&MsgQueue[HighIndex]);	  
   }
   else
   {
     MessageId=MsgQueue[HighIndex].MsgId;	
     ResetInfo(&MsgQueue[HighIndex]);	 	 
   }
  }

}

/***********************************************************************
*  Name        : EolMsg_ReceiveCallback
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EolMsg_ReceiveCallback(U8* data, U8 len)
{
	U8 MsgId =0;
	U8 Reclen=0;
	
 	RevMsgFrame=data;
	MsgId=GetEOLMessageID(RevMsgFrame[2]);
	Reclen = RevMsgFrame[0];
	
    EOL_MSGDISPATCHER(MsgId,RevMsgFrame,Reclen);
}

/***********************************************************************
*  Name        : EolMsg_Sent
*  Description : EolMsg_Sent msg task        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EolMsg_Sent(BOOL isSent)
{
   if(SendingMsg.MsgId!=E_MSGID_INVALID)
   {
     ResetInfo(&SendingMsg);   
   } 
}

//private
/***********************************************************************
*  Name        : PackageMsgFrame
*  Description : EOL msg task        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
U8 PackageRepMsgFrame(U8 MsgID, U8* pdata, U8 len, U8 ResultCode)
{
    return 0;
}

/***********************************************************************
*  Name        : PackageMsgFrame
*  Description : EOL msg task        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
U8 PackageReqMsgFrame(U8 MsgID, U8* pdata, U8 len)
{
    return 0;
}


/***********************************************************************
*  Name        : EolMsg_SendMessage
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EolMsg_SendMessage(U8* pData, U8 len)
{
  BOOL ret = FALSE;
  if(HAL_Write(DEV_EOLDRIVER,pData,len)==0)
  {
     uSentTimeCnt=T_SEND_TIMECNT;
     bWaitingSending= TRUE;
     WaitSendingTimer=T_WAITSENDCOUNT;
     ret = TRUE;
  }
  else{/*ignore*/}	

  return ret;
}

/***********************************************************************
*  Name        : UartDeviceCallback
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void UartDeviceCallback (U8 evetype)
{
   switch(evetype)
   {
   case E_DATA_RECEIVED:
   break;
   case E_DATA_SENT:
   	bAckRec=TRUE;	
	
	bWaitingSending=FALSE;
   	break;
   case E_DATA_SENT_FAIL:
   	bFailAckRec=TRUE;		
	
	bWaitingSending=FALSE;		
   	break;
	  default:
		break;
   }
}


/***********************************************************************
*  Name        : ResetInfo
*  Description : EOL msg task        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
static void ResetInfo(MsgInfo* pInfo)
{
   pInfo->pMsgData=NULL;
   pInfo->MsgId=E_MSGID_INVALID;
   pInfo->MsgLen =0;
   pInfo->ResultCode =0;
    pInfo->isReq=FALSE;
    pInfo->PriCount=0;
}
#endif
/**************** END OF FILE *****************************************/


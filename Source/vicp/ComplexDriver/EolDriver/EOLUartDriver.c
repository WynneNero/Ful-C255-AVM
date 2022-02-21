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
* 0.1  Mar 01,2013  NI Rujin    Initial version
* ----------------------------------------------------------------------
* 0.2  Jul 10,2013  LIU Chenxi  Remove signal reversion to adapt real HU
* ----------------------------------------------------------------------
* 0.3  Jul 15,2013  LIU Chenxi  Recover to previous version to adapt new
*      chante on real HU
*=====================================================================*/

#include "CONFIG.H"

#ifdef EOL_OPTION
#include "TYPES.H"
#include "EOLUartDriver.h"
#include "EOLUartDriver_if.h"
#include "irq_if.h"
#include "tools.h"
//#include "ERR_DEF.H"
#include "UART_IF.H"

static void DataReset(void);
static void NormalProcess(void);


static void SendFrame(U8 RC);
static void ParseFrame(U8 index);

volatile U8 DriverStatus;//driver state machine
volatile U8 DevRequest;// up layer request

//send logical	
U8 uSendBuf[MAX_EOL_BUFF];
U8 ReqSendLen;
U8 SendRC;
BOOL  Sent;
U8 SendTimer;

//receive logical
U8 ReceiveRC;
U8 ReceiveCKS;
EOL_FRAME_TYPE sRecvQ[EOL_RECVQ_SIZE];
U8 ReceivBuf[MAX_EOL_BUFF];
U8 ReqReceiveLen;
U8 ReceivedLen;

//Frame and ACK logical
BOOL bWaitingACK;
U8 WaitACKTimer;
U8 RetryCount;
BOOL bACKRequest;
BOOL bFrameRequest;
BOOL bNoACKFrameRequest;
//up layer interface

BOOL bRecvBufFull;
//IOCALLBACK_FUNC ClientCallback;
/***********************************************************************
*  Name        : EolUartDriver_Init
*  Description : Init driver        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EolUartDriver_Init(void)
{
      U8 i=0;
      for(i=0;i<MAX_EOL_BUFF;i++)
      {
    	uSendBuf[i]=0;
    	ReceivBuf[i]=0;
      }
        
      bRecvBufFull = FALSE;
      DataReset();
}

U8 ReturnReceivQEmptyIndex(void)
{
    U8 index;
    for(index = 0; index <EOL_RECVQ_SIZE; index++ )
    {
        if(sRecvQ[index].length == 0) return index;        
    }
    return index;
}


U8 ReturnReceivQUnparsedIndex(void)
{
    U8 index;
    for(index = 0; index <EOL_RECVQ_SIZE; index++ )
    {
        if(!sRecvQ[index].bIsParsed) return index;        
    }
    return index;
}


void DeleteHandledRecvQ(U8 handledIndex)
{
    U8 index;
    
    //mcu_disable_interrupt();
    if(handledIndex == EOL_RECVQ_SIZE-1 )
    {
        sRecvQ[handledIndex].length = 0;
        sRecvQ[handledIndex].bIsParsed = TRUE;
    }
    else
    {    
        for(index = handledIndex; index <EOL_RECVQ_SIZE-1; index++ )
        {
             sRecvQ[index].bIsParsed= sRecvQ[index+1].bIsParsed;
             sRecvQ[index].cks = sRecvQ[index+1].cks;
             sRecvQ[index].length = sRecvQ[index+1].length;
             sRecvQ[index].rc = sRecvQ[index+1].rc;
             _memcpy(sRecvQ[index].buf, sRecvQ[index+1].buf, sRecvQ[index+1].length);
        }
        sRecvQ[index].length = 0;
        sRecvQ[index].bIsParsed = TRUE;
    }
    //mcu_enable_interrupt();
}


/***********************************************************************
*  Name        : NaviDriver_DeInit
*  Description : Init driver        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EolUartDriver_DeInit(void)
{
    DataReset();
    UART_Stop(EOL_UART);	  //when wakeup disable uart interrupt
}

/***********************************************************************
*  Name        : NaviDriver_Open
*  Description : Open driver        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
U8 EolUartDriver_Open(void)
{
    DevRequest=E_EOLDRIVER_REQSTART;
  return ERR_OK;	
}

/***********************************************************************
*  Name        : EolUartDriver_Read
*  Description :       
*  Parameter   : None
*  Returns     : None
***********************************************************************/
U16 EolUartDriver_Read( U8* buffer, U16 Len)
{
    U16 relen = 0;

    if((sRecvQ[0].length)&&(sRecvQ[0].bIsParsed))
    {
        relen = sRecvQ[0].length;
        if(Len >= relen)
        {
            _memcpy(buffer,sRecvQ[0].buf,relen);
            DeleteHandledRecvQ(0);           
        }
        else
        {
            relen = 0;
        }
    }
  return relen;	
}

/***********************************************************************
*  Name        : EolUartDriver_Write
*  Description : send request        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
U8 EolUartDriver_Write( U8* buffer, U16 Len)
{
  U8 ret = ERR_BUSY;
  if((DriverStatus==E_EOLDRIVER_NORMAL||
  	DriverStatus==E_EOLDRIVER_SENDACK)&& 
  	bFrameRequest==FALSE&&
  	bNoACKFrameRequest==FALSE)
  {
    ret = ERR_OK;
    _memcpy(uSendBuf, buffer, Len);
    ReqSendLen=Len+EOL_FRAME_CKS;//frame haead + MSG data+CKS
    DevRequest|= E_EOLDRIVER_REQSENDFRAME;
  }

  return ret;
}

/***********************************************************************
*  Name        : EolUartDriver_Close
*  Description : close driver        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
U8 EolUartDriver_Close(void)
{
    DevRequest=E_EOLDRIVER_REQSTOP;
  return ERR_OK;	
}

/***********************************************************************
*  Name        : EolUartDriver_10ms_Entry
*  Description : 10 ms entry        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EolUartDriver_10ms_Entry(void)
{
   U8 unParsedIndex;
   U8 temp[5] = {0x22,0x34,0x55,0x66,0x77};

   unParsedIndex = ReturnReceivQUnparsedIndex();
  
  if(DriverStatus!=E_EOLDRIVER_IDLE
  	&&DevRequest!=E_EOLDRIVER_REQSTOP //if stop, ignore receive data
  	&&(unParsedIndex < EOL_RECVQ_SIZE) )
  {
        ParseFrame(unParsedIndex);
  }

  if(WaitACKTimer>0)WaitACKTimer--;
  
  switch(DriverStatus)
  {
    case E_EOLDRIVER_IDLE:
	if(DevRequest==E_EOLDRIVER_REQSTART)
	{
	  DriverStatus=E_EOLDRIVER_NORMAL;	
      UART_Start(EOL_UART,UART_BAUDRATE_19200);
	}
	else
	{
	}
	 DevRequest=E_EOLDRIVER_NOREQ;	
	break;

	case E_EOLDRIVER_NORMAL:
	if(DevRequest&E_EOLDRIVER_REQSTOP)
	{
         UART_Stop(EOL_UART);
         DataReset();
	  DriverStatus=E_EOLDRIVER_IDLE;	
	 DevRequest=E_EOLDRIVER_NOREQ;		  
	}
	else
	{
	  if(DevRequest&E_EOLDRIVER_REQSENDFRAME)
	  {
           bFrameRequest=TRUE;
	   DevRequest=DevRequest&(~E_EOLDRIVER_REQSENDFRAME);
	  }
	  NormalProcess();
	}
	break;
	
	case E_EOLDRIVER_SENDFRAME:
	break;	
	
	case E_EOLDRIVER_SENDACK:
	break;	
	
	default:
		break;
  }
}

/***********************************************************************
*  Name        : NormalProcess
*  Description : driver is normal status and check the send request        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void NormalProcess(void)
{
   if(bFrameRequest==TRUE)
   {
		 bFrameRequest = FALSE;
     SendFrame(0);
   }
}

/***********************************************************************
*  Name        : FrameSending
*  Description : driver is SendFrame status and check if is sent        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void FrameSending(void)
{
     SendTimer++; 
   if(Sent==TRUE)
   {
       SendTimer=0;
	if(bNoACKFrameRequest==TRUE)
	{
	  bNoACKFrameRequest= FALSE;
         EolDriverDataSentOk();	
	}
       DriverStatus=E_EOLDRIVER_NORMAL; 	
   }
   else
   {
     if(SendTimer>=SEND_TIMEROUT)
    {
       SendTimer=0;
    if(bNoACKFrameRequest==TRUE)
    {
	bNoACKFrameRequest= FALSE;
           EolDriverDataSentFail();		
    }  
       DriverStatus=E_EOLDRIVER_NORMAL; 	
    }
   } 
}

/***********************************************************************
*  Name        : DataReset
*  Description : reset running data       
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void DataReset(void)
{
  U8 index;
  ReceivedLen=0;
  ReqReceiveLen=0;


  bACKRequest=FALSE;
  bFrameRequest=FALSE;
  bNoACKFrameRequest = FALSE;
  
  bWaitingACK=FALSE;
  WaitACKTimer=0;
  SendTimer=0;
  Sent=FALSE;
  RetryCount=0;
  
  DevRequest=E_EOLDRIVER_NOREQ;
  DriverStatus=E_EOLDRIVER_IDLE;

  for(index = 0;index<EOL_RECVQ_SIZE;index++)
  {
    sRecvQ[index].bIsParsed = TRUE;
    sRecvQ[index].length = 0;
    sRecvQ[index].cks = 0;
    sRecvQ[index].rc = 0;
    _memset(sRecvQ[index].buf, 0, MAX_EOL_BUFF);
  }
}

/***********************************************************************
*  Name        : SendFrame
*  Description : send frame       
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SendFrame(U8 RC)
{
 U8 CKS=0;
 U8 i=0;
  for(i=0;i<ReqSendLen-1;i++)
  {
   CKS=CKS^uSendBuf[i];
  }
  uSendBuf[i]=CKS;
  
  SendTimer=0;
  Sent=FALSE;
  UART_SendBuf(EOL_UART,uSendBuf,ReqSendLen);
}

/***********************************************************************
*  Name        : ParseFrame
*  Description : parse recieve frame , run in 10ms      
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void ParseFrame(U8 index)
{
 U8 CKS=0;
 U8 i=0;	
 
  for(i=0;i<sRecvQ[index].length;i++)
  {
   CKS=CKS^sRecvQ[index].buf[i];
  }

  if(CKS==sRecvQ[index].cks)
  {
        //mcu_disable_interrupt();
        sRecvQ[index].bIsParsed = TRUE;
        //mcu_enable_interrupt();
   }
  else// CKS error
  {
      DeleteHandledRecvQ(index);
  }
}

U8 EolUartDriver_GetDriverStatus(void)
{
    if(E_EOLDRIVER_IDLE== DriverStatus) return 0;
    else return 1;
}


/***********************************************************************
*  Name        : Sent_Isr
*  Description : buf data is sent , run in isr      
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EolUartDriver_SentIsr(void)
{
  Sent= TRUE;
}

/***********************************************************************
*  Name        : Receive_Isr
*  Description : one data is received , run in isr      
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EolUartDriver_ReceiveIsr(U8 data)
{
    switch(ReceivedLen)
    {
        case 0://len
        if(data>=5)
        {
            ReqReceiveLen = data;
            ReceivBuf[ReceivedLen] = data;
            ReceivedLen++;
        }
        else
        {
            ReceivedLen = 0;
            break;
        }
        break;
        case 1://0xff
        case 3:
        case 4:
            if(0xff == data)
            {
                ReceivBuf[ReceivedLen] = data;
                ReceivedLen++;
            }
            else
            {
                ReceivedLen = 0;
            }
        break;
        case 2: //comand
            ReceivBuf[ReceivedLen] = data;
            ReceivedLen++;       
        break;
        default:
            if(ReceivedLen ==ReqReceiveLen )  //recv end
            {
                U8 emptyIndex = ReturnReceivQEmptyIndex();

                if(emptyIndex < EOL_RECVQ_SIZE)
                {
                    sRecvQ[emptyIndex].bIsParsed = FALSE;
                    sRecvQ[emptyIndex].length = ReqReceiveLen;
                    sRecvQ[emptyIndex].cks = data;
                    ReceivedLen=0;	
                  _memcpy(sRecvQ[emptyIndex].buf,ReceivBuf,ReqReceiveLen);	
                }
                else
                {
                    bRecvBufFull = TRUE;  //test use
                    ReceivedLen=0;	
                    ReqReceiveLen = 0;
                    //buf is full,lost the msg.
                }	  
            }
						else
						{
            ReceivBuf[ReceivedLen] = data;
            ReceivedLen++;     
						}
        break;
    }
}
#endif
/**************** END OF FILE *****************************************/


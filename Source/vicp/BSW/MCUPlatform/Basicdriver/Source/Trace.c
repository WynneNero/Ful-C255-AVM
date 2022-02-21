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
*------------------------------------------------------------------------
*  0.1     2014/05/09 ShangQiuju     Init
*------------------------------------------------------------------------
*  0.2      Jan 24,2017  ZhangJie  Fix Coverity warning.
*=====================================================================*/
#include "Trace.h"
#include "uart_if.h"

#define TRACESENDTIMEOUT  25u  /*500MS*/ 
#define GET_MSG_1SINTERVAL  50u  /* 1S*/
#define GET_MSG_5SINTERVAL  200u  /* 4S*/
#define MAX_TRACE_LEN 64u

enum
{
    TRACE_IDLE,
    TRACE_READY,
    TRACE_WAIT,
};

enum
{
    STEP_GET_RESETREASON,
    STEP_GET_WAKEUPREASON,
    STEP_GET_1SSTATE,
    STEP_1STIMEWAIT,
    STEP_GET_5SSTATE,
    STEP_5STIMEWAIT,
    #ifdef USED_FOR_NET_STRESS_TEST
    STEP_GET_20SSTATE,
    STEP_20STIMEWAIT,
    #endif
 };

BOOL bResetFlag;
BOOL bWakeupFlag;

U8 SendInfo[MAX_TRACE_LEN];
U8 SendInfolen;
U8 SendInfoCpy[MAX_TRACE_LEN];
U8 SendInfoCpylen;
U16 SentTimecnt;
U16 uIntervalCnt;
U8 Send1sTimeCnt;

void TraceOut_MsgWithNumbers(char* msg, U8* number,U8 len);
void TraceOut_MsgWithNumbersWithOut0x(char* msg, U8* number,U8 len);
U16 _strlen(const char* dest);
char ConvertHalfByteHexValue2AsciiChar(U8 hex);

/***********************************************************************
*  Name        : Log_Init
*  Description : Init driver manager        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Log_Init(void)
{
  bResetFlag = TRUE;
  bWakeupFlag = FALSE;
  SendInfolen=0u;
  SendInfoCpylen=0u;
}


/***********************************************************************
*  Name        : Log
*  Description : Init driver manager        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Log(U8* pinfo, U8 Len)
{
  U8 i=0u;
  
  for(i=0u;i<Len;i++)
  {
   if(SendInfoCpylen<MAX_TRACE_LEN)
   {
      SendInfoCpy[SendInfoCpylen]=pinfo[i];
      SendInfoCpylen++;
   }
  }
  UART_SendBuf(UART_0,(U8*)(&SendInfoCpy[0]),Len);		
}

void GetMsgHandler(void)
{
    
}

void SendTranceHandler(void)
{

}
/***********************************************************************
*  Name        : EndLog
*  Description : Init driver manager        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EndLog(void)
{
  SendInfoCpylen=0u;
  SendInfolen=0u;
}



/*add helper function to facilitate output trace informaiton*/
void TraceOut_ByteArray(U8* pinfo, U8 Len)
{
	Log_Init();
    Log(pinfo, Len);  	
	EndLog();
}


/*i.e.   TraceOut_Msg("XXXX module Init ok!");*/
void TraceOut_Msg(char* msg)
{
  U8 i=0u;
  U8 len = (U8)_strlen(msg);
    
  for(i=0;i<len;i++)
  {
   if(SendInfolen<64u)
   {
      SendInfo[SendInfolen]=(U8)msg[i];
      SendInfolen++;
   }
  }

  if(SendInfolen<62u)
  {
    SendInfo[SendInfolen]=(U8)'\r';
    SendInfo[SendInfolen+1u]=(U8)'\n';
    SendInfolen +=2u;
  }
  	UART_SendBuf(UART_0,(U8*)(&SendInfo[0]),SendInfolen);
}

void TraceOut_Messages(char* msg1, U8* msg2, U8 msg2Len )
{
  U8 i=0u;
  U8 len = (U8)_strlen(msg1);
  
  
  for(i=0u;i<len;i++)
  {
   if(SendInfolen<64u)
   {
      SendInfo[SendInfolen]=(U8)msg1[i];
      SendInfolen++;
   }
  }

  for(i=0u;i<msg2Len;i++)
  {
   if(SendInfolen<64u)
   {
      SendInfo[SendInfolen]=msg2[i];
      SendInfolen++;
   }
  }

  if(SendInfolen<62u)
  {
    SendInfo[SendInfolen]=(U8)'\r';
    SendInfo[SendInfolen+1u]=(U8)'\n';
    SendInfolen +=2u;
  }
	UART_SendBuf(UART_0,(U8*)(&SendInfo[0]),SendInfolen);
}

void TraceOut_MsgAndChar(char* msg, U8 ch)
{
  U8 i=0u;
  U8 len = (U8)_strlen(msg);
    
  for(i=0u;i<len;i++)
  {
   if(SendInfolen<64u)
   {
      SendInfo[SendInfolen]=(U8)msg[i];
      SendInfolen++;
   }
  }


  if(SendInfolen<60u)
  {
    SendInfo[SendInfolen] = ch;
    SendInfo[SendInfolen+1u] = ' ';
    SendInfo[SendInfolen+2u]='\r';
    SendInfo[SendInfolen+3u]='\n';
    SendInfolen +=4u;
  }
    
}



/*i.e.   TraceOut_Msg("data received is:", 20);*/
/*output will be : data received is: 0x14*/
void TraceOut_MsgWithNumber(char* msg, U8 number)
{
    char msg2[4] ={'0','x',0,0};
    msg2[2] = ConvertHalfByteHexValue2AsciiChar(number>>4);
    msg2[3] = ConvertHalfByteHexValue2AsciiChar(number&0x0Fu);

    TraceOut_Messages(msg,(U8*)msg2,4u);
}

/*i.e.   TraceOut_Msg("data received is:", 20,20);*/
/*output will be : data received is: 0x14,0x14*/
void TraceOut_MsgWithNumbersWithOut0x(char* msg, U8* number,U8 len)
{
    U8 index;
    char msg2[64] ={0};
    for(index = 0u;index<len;index++)
    {
    msg2[0u+(index*3u)] = ConvertHalfByteHexValue2AsciiChar(number[index]>>4);
    msg2[1u+(index*3u)] = ConvertHalfByteHexValue2AsciiChar(number[index]&0x0Fu);
    msg2[2u+(index*3u)] = ' ';
    }
    TraceOut_Messages(msg,(U8*)msg2,(len*3u) -1u);
}
/*i.e.   TraceOut_Msg("data received is:", 20,20);*/
/*output will be : data received is: 0x14,0x14*/
void TraceOut_MsgWithNumbers(char* msg, U8* number,U8 len)
{
    U8 index;
    char msg2[64] ={0};
    msg2[0]='0';
    msg2[1]='x';
    for(index = 0u;index<len;index++)
    {
    msg2[2u+(index*3u)] = ConvertHalfByteHexValue2AsciiChar(number[index]>>4);
    msg2[3u+(index*3u)] = ConvertHalfByteHexValue2AsciiChar(number[index]&0x0Fu);
    msg2[4u+(index*3u)] = ',';
    }
    TraceOut_Messages(msg,(U8*)msg2,2u+(len*3u) -1u);
}

char ConvertHalfByteHexValue2AsciiChar(U8 hex)
{
    char ascii = '0';

    if(hex <= 0x09u)
    {
        ascii = hex + '0';
    }
    else if((hex >= 0x0Au)&& (hex <= 0x0Fu))
    {
        /*'A' is 0x41, 0x41-0x0A = 0x37*/
        ascii = (char)(hex + 0x37u);
    }
    else
    {
        /*not possible.*/
    }

    return ascii;
}

/**************** END OF FILE *****************************************/


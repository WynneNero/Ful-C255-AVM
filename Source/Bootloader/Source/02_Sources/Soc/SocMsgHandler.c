/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD  NJ								   *
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
* Version       Date              Name              Changes and comments
* ----------------------------------------------------------------------
*   0.1         2016/8/20       ShangQiuju      Init verssion
* ----------------------------------------------------------------------
*   0.2         2016/8/29       ShangQiuju      Remove sendQ,use data fifo in socdriver.
* ----------------------------------------------------------------------
*   0.3         2017/1/3         ShangQiuju      Remove unused parameter.
* ----------------------------------------------------------------------
*   0.4         2017/2/7         ZhangJie       Remove EOL for compile error.
*=====================================================================*/
#include "define.h"
#include "SocMsgHandler.h"
#include "SocDriver_if.h"
#include "SocMsg_Cfg.h"

static U8 EnableReq;
U8 RevFrame[MAX_FRAME_LEN];
SOC_FRAME TRecvFram;

void Data_Reset(void);
void ResetInfo(MSGQ_INFO* pInfo);
BOOL IsRecieveReqMsg(U8* pdata, U8 len);
BOOL SocMsg_SendMessage(U8* pData, U8 len);
void DeviceCallback (U8 evetype);
void RX_Handler(void);
void TX_Handler(void);
void Soc_msg_frame_decode(U8 *frame, SOC_FRAME  *soc_frame);
/***********************************************************************
*  Name        : SocMsg_Init
*  Description : Init soc msg handler        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SocMsg_Init(void)
{
  Data_Reset();
}

/***********************************************************************
*  Name        : SocMsg_DeInit
*  Description : DeInit soc msg handler        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SocMsg_DeInit(void)
{
  Data_Reset();
}


/***********************************************************************
*  Name        : SocMsg_Entry
*  Description : soc msg task        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SocMsg_Entry(void)
{
 U8 Req =  EnableReq;

 EnableReq=E_NO_CONTROL;
 
 if(Req==E_NO_CONTROL)
 {
      TX_Handler();
      RX_Handler();
 }
 else if(Req==E_ENABLE_CONTROL)
 {
      //TODO: callback
      SocDriver_Open();
 }
 else if(Req==E_DISABLE_CONTROL)
 {
 	SocDriver_Close();
	Data_Reset();
 }
 
}

/***********************************************************************
*  Name        : Data_Reset
*  Description :       
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Data_Reset(void)
{   
   EnableReq=E_NO_CONTROL;
}


/***********************************************************************
*  Name        : SocMsg_ControlCommunication
*  Description :         
*  Parameter   : isEnable
*  Returns     : None
***********************************************************************/
void SocMsg_ControlCommunication(BOOL isEnable)
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
*  Name        : SocMsg_ControlPower
*  Description :         
*  Parameter   : action
*  Returns     : None
***********************************************************************/
void SocMsg_ControlPower(E_DEV_POWER action)
{
    switch(action)
    {
        case E_DEV_POWEROFF:
        case E_DEV_POWERON:
            SocDriver_powercontrol(action);
        break;
        
        default:break;
    }
}

/***********************************************************************
*  Name        : SocMsg_SendMessage
*  Description :         
*  Parameter   : None
*  Returns     : BOOL
***********************************************************************/
BOOL SocMsg_SendMessage(U8* pData, U8 len)
{
  BOOL ret = FALSE;
  if(SocDriver_Write(pData,len)==ERR_OK)
  {
     ret = TRUE;
  }
  else
  {
  /*ignore*/
  }	

  return ret;
}

/***********************************************************************
*  Name        : RX_Handler
*  Description : soc msg task        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void RX_Handler(void)
{
    U8 reclen =0; 
    reclen=SocDriver_Read(RevFrame,MAX_FRAME_LEN);
     if(reclen>0)
     { 
             U8 cmpt_id;
             U16 commandid;
             U8 size;
             Soc_msg_frame_decode(RevFrame,&TRecvFram);
             cmpt_id = TRecvFram.command_ID.id_bit.cmpt_id;
             commandid = TRecvFram.command_ID.command_ID;     
             size = TRecvFram.command_size;
    	     SOC_MSGDISPATCHER(cmpt_id,commandid,size,(TRecvFram.param));    
     }	  
}

/***********************************************************************
*  Name        : TX_Handler
*  Description : soc msg task        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void TX_Handler(void)
{ 
}


/****************************************************************************************************
SOC FRAME:

cmd type     |                       command    id                             |   cmd size   |       cmd flag             | param1...n
1byte          |  cmpt(5 bit)   svc type(3 bit)  cmd number(8 bit)   |   1 byte      | 1 byte(reserved)       | n byte

*****************************************************************************************************/
void Soc_msg_frame_decode(U8 *frame, SOC_FRAME  *soc_frame)
{
    (*soc_frame).command_type=*(frame+CMD_TYPE);
    (*soc_frame).command_ID.command_ID=(((U16)*(frame+CMD_ID_H))<<8) + (U16)*(frame+CMD_ID_L);
    (*soc_frame).command_size=*(frame+CMD_SIZE);
    (*soc_frame).param = frame+CMD_PARAM_START;
}


/***********************************************************************
*  Name        : ResetInfo
*  Description : SOC msg task        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void ResetInfo(MSGQ_INFO* pInfo)
{
   pInfo->command_type=INVALID_COMMAND_TYPE;
   pInfo->len = 0;
   pInfo->param = NULL;
}


/**************** END OF FILE *****************************************/


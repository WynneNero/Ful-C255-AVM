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
*-----------------------------------------------------------------------
*   0.1         2016/8/20       ShangQiuju      Init verssion
*-----------------------------------------------------------------------
*   0.2         2016/8/29       ShangQiuju      Remove sendQ,use data fifo in socdriver.
*-----------------------------------------------------------------------
*   0.3         2017/1/4        ShangQiuju      Update SocMsg_GetPower according hal update.
*-----------------------------------------------------------------------
*   0.4         2017/1/13      ShangQiuju      Fix coverity warnings.
*----------------------------------------------------------------------
*   0.5         2017/2/10    ShangQiuju       Remove unused parameters.
*----------------------------------------------------------------------
*   0.6         2017/3/7       ShangQiuju     soc task change from 20ms to 10ms
*=====================================================================*/
#include "TYPES.h"
#include "SocMsgHandler.h"
#include "Hal_if.h"
#include "Signal_if.h"
#include "SocDriver_IF.h"
#include "SocMsg_Cfg.h"
#include "test_spi.h"

BOOL bRec;
static U8 EnableReq;
U8 RevFrame[MAX_FRAME_LEN] = {0};
SOC_FRAME TRecvFram={0};;

BOOL bDriverError;
STATIC void Data_Reset(void);
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
*  Name        : SocMsg_20ms_Entry
*  Description : soc msg task        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SocMsg_20ms_Entry(void)
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
      HAL_Open(DEV_SOC);
 }
 else if(Req==E_DISABLE_CONTROL)
 {
 	HAL_Close(DEV_SOC);
	Data_Reset();
 }
 
}

/***********************************************************************
*  Name        : Data_Reset
*  Description :       
*  Parameter   : None
*  Returns     : None
***********************************************************************/
STATIC void Data_Reset(void)
{   
   EnableReq=E_NO_CONTROL;
  bDriverError =FALSE;
}

/***********************************************************************
*  Name        : Soc_DriverError_Report
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Soc_DriverError_Report(void)
{    
      DeviceCallback(E_DRIVER_ERROR);
}

/***********************************************************************
*  Name        : Soc_DataSentOk
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Soc_DataSentOk(void)
{
      DeviceCallback(E_DATA_SENT);
}

/***********************************************************************
*  Name        : Soc_DataSentFail
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Soc_DataSentFail(void)
{
      DeviceCallback(E_DATA_SENT_FAIL);
}


/***********************************************************************
*  Name        : SocMsg_ControlCommunication
*  Description :         
*  Parameter   : None
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
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SocMsg_ControlPower(E_DEV_POWER action)
{
    switch(action)
    {
        case E_DEV_POWEROFF:
        case E_DEV_POWERON:
                HAL_DevPowerControl(DEV_SOC, action);
        break;
        
        default:break;
    }
}


BOOL SocMsg_GetPower(U8 state)
{   
    return(state == HAL_DevGetPowerStatus(DEV_SOC));
}

/***********************************************************************
*  Name        : SocMsg_SendMessage
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL SocMsg_SendMessage(U8* pData, U8 len)
{
  BOOL ret = FALSE;
  if(HAL_Write(DEV_SOC,pData,len)==ERR_OK)
  {
     ret = TRUE;
  }
  else{/*ignore*/}	

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
	U8 cnt =0;
	for(cnt=0;cnt<FRAME_CNT;cnt++)
	{
		reclen=HAL_Read(DEV_SOC,RevFrame,MAX_FRAME_LEN);
		if(reclen>0)
		{ 
			U8 cmpt_id;
			U16 commandid;
			Soc_msg_frame_decode(RevFrame,&TRecvFram);
			cmpt_id = TRecvFram.command_ID.id_bit.cmpt_id;
			commandid = TRecvFram.command_ID.command_ID;			 
			SOC_MSGDISPATCHER(cmpt_id,commandid,(TRecvFram.param));
    #ifdef spi_test  
			U8 Test_Len;
			Test_Len = TRecvFram.command_size;
			Soc_SendReceive_Test(cmpt_id,commandid,(TRecvFram.param),Test_Len);
    #endif
		}
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
*  Name        : DeviceCallback
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void DeviceCallback (U8 evetype)
{
   switch(evetype)
   {
   case E_DATA_RECEIVED:
   	break;
   case E_DATA_SENT:
   break;
   case E_DATA_SENT_FAIL:	
   	break;
   case E_DRIVER_ERROR:
        bDriverError = TRUE;
   break;
   default:break;
   }
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


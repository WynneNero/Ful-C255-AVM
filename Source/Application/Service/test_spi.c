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
*=====================================================================*/
#include "CONFIG.H"
#include "TYPES.H"
#include "SocMsgHandler.h"
#include "SocMsg_Cfg.h"
#include "SocManager.h"
#include "test_spi.h"

/***********************************************************************
*  Name        : SocTest_Dispatcher_Msg
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Soc_SendReceive_Test(U8 cmpt_id,U16 commandid, U8* data, U16 LEN)
{
	if(cmpt_id == CMPT_ID_GEN)
	{
	   switch(commandid)
		{
	
		   case TEST_SPI_RECEIVE_EVENT :  //0x0201				 
				 SocManager_SendMsg(HQ_CMD,TYPE_RESPONSE,TEST_SPI_SEND_EVENT,LEN,data);  //0X0301
				 //illum_target_state_receive(data);
                break;
		}
	}
	
	
}


































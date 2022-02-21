/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									   *
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   : IIC complex driver, support slave mode for ICS project.
			   Operate following EEPROM Read/Write sequence(check protocl for details)
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
* ----------------------------------------------------------------------
* 0.1    Jan 05,2016                       Initialize
* ----------------------------------------------------------------------
* 0.2    Jan 05,2017    ZhangJie  Delete test invalid code
* ----------------------------------------------------------------------
* 0.3    Jan 06,2017    ZhangJie  Using configure micro instead of magic number
*------------------------------------------------------------------------
* 0.4    Jan 24,2017  ZhangJie  Fix Coverity warnings.
*------------------------------------------------------------------------
* 0.5   Apr 04,2017   PEI Jingli  Fix headfile included.
*=====================================================================*/
#include "ICS_Driver.h"
#include "IIC_if.h"
#include "Eventmng.h"
#include "Tools.h"

static U8 data_index=0u;	/*for test, index searched based on register*/
static BOOL bRegMatch=FALSE;		/*TRUE- register match, 
								FALSE- register not match, receive data but no operation*/
/*register*/ 
U8 ICSReg[ICS_REG_TABLE_LENGTH]={0x01u,0x02u,0x03u,0x04u,0x05u,0x06u,0x07u,0x08u,0x09u};
/*data buffer, prevent wrong operation, e.g. 'write to read only register'*/
U8 ICSDataBuffer[ICS_REG_TABLE_LENGTH]={0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu};								
/* data*/
U8 ICSData[ICS_REG_TABLE_LENGTH]={0x11u,0x22u,0x33u,0x44u,0x55u,0x66u,0x77u,0x88u,0x99u};
/* read / write property setting*/
/* if master write to a 'read-only' register, it should not affect its content*/
U8 ICSData_RW_Propery[ICS_REG_TABLE_LENGTH]={ICS_DATA_READ,
										ICS_DATA_READ,
										ICS_DATA_READ+ICS_DATA_WRITE,
										ICS_DATA_READ+ICS_DATA_WRITE,
										ICS_DATA_READ+ICS_DATA_WRITE,
										ICS_DATA_READ,
										ICS_DATA_READ,
										ICS_DATA_READ,
										ICS_DATA_READ,										
};
/*U8 ICS_Send_Data[ICS_REG_TABLE_LENGTH]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};*/
/*U8 ICS_REC_Data[ICS_REG_TABLE_LENGTH]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};*/
/*TBD, filled by app
ICS_RegType RegTable[ICS_REG_TABLE_LENGTH]=
{
	{0x01,0x11},
	{0x02,0x22},
	{0x03,0x33},
	{0x04,0x44},
	{0x05,0x55},
	{0x06,0x66},
	{0x07,0x77},
	{0x08,0x88},
	{0x09,0x99}
};
*/

/***********************************************************************
*  Name        : ICSDriver_Open
*  Description : Init driver        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL ICSDriver_Open(void)
{  
   /*init reg table, TBD*/

   /*start IIC*/
   IIC_Start(BAUD_100K,I2C_TARGET_ADDR,IIC_SLAVE);
   /*IIC_Start(BAUD_400K,I2C_TARGET_ADDR,IIC_MAP_P10,IIC_SLAVE);*/

    /*set receive address initially, set to 0*/
    /*IIC_Slave_RxAdr_Set(&ICSData[0]);*/
   return TRUE;
}

/***********************************************************************
*  Name        : ICSDriver_Close
*  Description : Deinit
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL ICSDriver_Close(void)
{
   IIC_Stop();
   return TRUE;
}

/***********************************************************************
*  Name        : ICSDriver_Read
*  Description :  Read data from ICS buffer to receive array
*  Parameter   : pRec- pointer to address to receive data			   
			   size- data length
*  Returns     : None
***********************************************************************/
void ICSDriver_Read(U8 *pRec,U8 size)
{
	if(size<ICS_REG_TABLE_LENGTH)
	{
		_memcpy(pRec,&ICSData[0],size);
	}
	else
	{
		_memcpy(pRec,&ICSData[0],ICS_REG_TABLE_LENGTH);
	}
}

/***********************************************************************
*  Name        : ICSDriver_Write
*  Description :  Write data to ICS buffer.
*  Parameter   : pSend- pointer to data to send 
			   size- data length
*  Returns     : None
***********************************************************************/
void ICSDriver_Write(U8 * pSend, U8 size)
{
	if(size<ICS_REG_TABLE_LENGTH)
	{
		_memcpy(&ICSData[0],pSend,size);
	}
	else
	{
		_memcpy(&ICSData[0],pSend,ICS_REG_TABLE_LENGTH);
	}
}

/***********************************************************************
*  Name        : ICSDriver_ctrl
*  Description :  Reserved interface for hal. 
*  Parameter   : buffer- pointer to data
			   type- reserved
*  Returns     : None
***********************************************************************/
void ICSDriver_ctrl(U8 type,void * buffer)
{

}
/***********************************************************************
*  Name        : ICSDriver_checkRegPosition
*  Description : search position based on register address.		  
			  specify address to send/receive.
			  
*  Parameter   : regAdr- register address
*  Returns     : data index 
***********************************************************************/
BOOL ICSDriver_checkRegPosition(U8 regAdr)
{
	U8 index=0; 

	data_index=ICS_REG_TABLE_LENGTH;
	
	/*search for matched regsiter*/	
	for(index=0;index<ICS_REG_TABLE_LENGTH;index++)
	{
		if(ICSReg[index]==regAdr)
		{
			data_index=index;
			break;
		}		
	}
	
	if(data_index<ICS_REG_TABLE_LENGTH)
	{
		bRegMatch= TRUE;			/* register match */
		/* set tx data address and size*/
		/* because master decides STOP*/
		/* if STOP arrives late, slave will send 0x5A after actual data is sent*/
		/* if STOP arrives early,no effect on slave*/
		IIC_SlaveWriteFrame(&ICSData[data_index],(ICS_REG_TABLE_LENGTH-data_index));
		/* update rx address*/
		IIC_SlaveReadFrame(&ICSDataBuffer[data_index],(ICS_REG_TABLE_LENGTH-data_index+2u));	/* +2, include dev adr and reg adr*/		
	}
	else
	{
		bRegMatch= FALSE;			/*register not found*/
	}
	return bRegMatch;
}

/***********************************************************************
*  Name        : ICSDriver_session_finish
*  Description : handler when one communication session finishes(Stop received).
*  Parameter   : role- 0:master, 1:slave
			   RWdirection- 0- TX, 1- RX
			   RecDataCount- count of data received, excluded dev address and register address
*  Returns     : none 
***********************************************************************/
void ICSDriver_session_finish(U8 role, U8 RWdirection, U8 RecDataCount)
{
	U8 count=0;
	
	if(role==ICS_SLAVE)			/* ICS MCU only operate in slave mode*/
	{
		if(bRegMatch)
		{
			/* notify upper layer */
			if(RWdirection==ICS_RX)		
			{
				if(RecDataCount>0u)	/* data received*/
				{
					for(count=data_index;count<(ICS_REG_TABLE_LENGTH-data_index);count++)				
					{
						if(ICSData_RW_Propery[count] & ICS_DATA_WRITE)
						{
							/*need to check if ICSDataBuffer has actually changed*/
							/* special condition: master send Dev adr + reg adr + STOP, should not update*/						
							ICSData[count]=ICSDataBuffer[count];		/* update*/
						}
						else
						{
							/* read only, no update*/
						}
					}
				}
				SysEvt_SetEvent(EVT_ICS_RX_FINISH);		/* receive finish*/
			}
			else if(RWdirection==ICS_TX)		
			{
				SysEvt_SetEvent(EVT_ICS_TX_FINISH);		/* send finish*/
			}
		}
	}
	else if(role==ICS_MASTER)		/*master mode, not implemented*/
	{
		if(RWdirection==ICS_RX)		
		{
			SysEvt_SetEvent(EVT_ICS_RX_FINISH);	/*rec finish, check received data*/
		}
		else if(RWdirection==ICS_TX)		
		{
			/* do nothing*/
		}
	}
}

/***********************************************************************
*  Name        : ICS_GetDataPtr
*  Description : return pointer of data sent/received
  *  Parameter   : none
*  Returns     : none 
***********************************************************************/
U8*  ICS_GetDataPtr(void)
{
	return (ICSData+data_index);
}

/***********************************************************************
*  Name        : ICS_GetDataLen
*  Description :  return length of data sent/received.
		  	   note: not same as data sent/received on IIC, because actual sent length 
			   depends on master's action(send NACK/STOP)

  *  Parameter   : none
*  Returns     : none 
***********************************************************************/
U8 ICS_GetDataLen(void)
{
	if(data_index<ICS_REG_TABLE_LENGTH)
	{
		return (ICS_REG_TABLE_LENGTH-data_index);
	}
	else
	{
		return 0;
	}
}

/***********************************************************************
*  Name        : ICSDriver_Received_Reg_Match
*  Description :  return True if received register matches with protocol definition
*  Parameter   : none
*  Returns     : none 
***********************************************************************/
BOOL ICSDriver_Received_Reg_Match(void)
{
	return bRegMatch;
}


/**************** END OF FILE *****************************************/


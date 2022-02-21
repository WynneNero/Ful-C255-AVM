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
* 0.1    Sep 12,2016                       Initialize
* ----------------------------------------------------------------------
* 0.2    Jan 06,2017    ZhangJie   Add target address micro 
*------------------------------------------------------------------------
* 0.3    Jan 24,2017  ZhangJie  Fix Coverity warnings.
*------------------------------------------------------------------------
* 0.5   Apr 04,2017   PEI Jingli  Fix headfile included.
*=====================================================================*/
#ifndef _ICSDRIVER_H_
#define _ICSDRIVER_H_

#include "CONFIG.H"
#include "Define.h"

/**** Definition of constants ****/
#define ICS_REG_TABLE_LENGTH	9U		/* length of register table for ICS*/
#define I2C_TARGET_ADDR 	0x15U   /* NextEV ICS address		0x50	24c16 EEPROM	0x38		 8561 address*/

#define ICS_SLAVE	1U
#define ICS_MASTER	0U

#define ICS_RX 1U		/*receive*/
#define ICS_TX 0U

/* register property, read or write*/
#define ICS_DATA_READ	0x01U		
#define ICS_DATA_WRITE	0x02U

/* eeprom configure definition */
/*
typedef struct
{
	U8 RegAdr;		register address
	U8 RegData;   	Data of register
}ICS_RegType;
*/

BOOL ICSDriver_Open(void);
BOOL ICSDriver_Close(void);
void ICSDriver_Read(U8 *pRec, U8 size);
void ICSDriver_Write(U8 * pSend, U8 size);
void ICSDriver_ctrl(U8 type,void * buffer);
BOOL ICSDriver_checkRegPosition(U8 regAdr);
void ICSDriver_session_finish(U8 role, U8 RWdirection, U8 RecDataCount);
BOOL ICSDriver_Received_Reg_Match(void);	

U8*  ICS_GetDataPtr(void);	/* for test*/
/*U8 * ICS_GetDataPtr(BOOL bSend);*/
U8 ICS_GetDataLen(void);	/* for test*/
#endif /*_EEPDRIVER_H_*/

/****************************** END OF FILE ***************************/


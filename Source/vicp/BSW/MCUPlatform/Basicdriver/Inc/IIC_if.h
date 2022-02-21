/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                                 *
*   AUTHOR     :                                                       *
************************************************************************
* Object        :
* Module        :	IIC
* Instance      :
* Description   :	Header file
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
* ----------------------------------------------------------------------
* 0.1    Jan 20,2016   Init version.
*----------------------------------------------------------------------
* 0.2    Jan 24,2017    ZhangJie     Fix Coverity warning.
*=====================================================================*/

#ifndef   _IIC_IF_H
#define   _IIC_IF_H
#include "define.h"

typedef enum
{
	IIC_MASTER=0,
	IIC_SLAVE
}IIC_ROLEOPTION;

typedef enum
{
	BAUD_10K=0,
	BAUD_100K,
	BAUD_400K,
	BAUD_OPTIONMAX
}BAUD_OPTION;

extern void IIC_Start( BAUD_OPTION baudrate, U8 Addr , IIC_ROLEOPTION RoleOption);
extern void IIC_Stop( void );
extern BOOL IIC_MasterWriteFrame(  U8 Addr, U8* pstr, U8 size, U8 options );
extern BOOL  IIC_MasterReadFrame( U8 Addr, U8* pstr, U8 size, U8 options );
extern U8 IICMasterReadReg(BAUD_OPTION BAUD, U8 SLAVE_ADDR, U8 RegOffset);
extern void IICMasterWriteReg(BAUD_OPTION BAUD, U8 SLAVE_ADDR, U8 RegOffset, U8 Data);

extern BOOL IIC_SlaveReadFrame( U8 *pstr, U8 size);
extern BOOL IIC_SlaveWriteFrame(U8  *pstr, U8 size );


#endif

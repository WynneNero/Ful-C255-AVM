/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                                 *
*   AUTHOR     :                                                       *
************************************************************************
* Object        :
* Module        :	S_IIC
* Instance      :
* Description   :	Header file
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
*     
*=====================================================================*/
#ifndef   _S_IIC_IF_H
#define   _S_IIC_IF_H

#include "Define.h"

extern void S_IIC_Init(void);
extern void S_IIC_DeInit(void);
extern ERR_TYPE S_IIC_SendData(U8 * pOutDataHead, U16 u16DataLen);
extern ERR_TYPE S_IIC_RecData(U8 *pRecDataHead, U16 u16DataLen);
extern void S_IIC_SendStart(void);
extern void S_IIC_SendStop(void);

#endif

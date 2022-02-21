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
/**** Definition of constants ****/
/**** Definition of macros ****/
/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/
#ifndef _CAN_SIG_CFG_IF_H_
#define _CAN_SIG_CFG_IF_H_

extern void CanSig_CANSendValue(U16 Signal, U8* pvalue,U8 len);
extern U8 CanSig_CANGetValue(U16 Signal, U8* pvalue,U8 len);


#endif /*_CAN_SIG_CFG_IF_H_*/

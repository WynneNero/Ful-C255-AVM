/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   : Shao Guangxian										   *
************************************************************************
* Object        : SPI.H
* Module        :
* Instance      :
* Description   :
*-----------------------------------------------------------------------
* Version:  0.1
* Date: 2011-11-24
* Author: Shao Guangxian
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
*
*=====================================================================*/
#ifndef _UART_CFG_H_
#define _UART_CFG_H_
/**** Definition of constants ****/
#include "define.h"
#include "Uart_if.h"

/**** Definition of macros ****/


/**** Declaration of constants ****/


/**** Declaration of variables ****/


/**** Declaration of functions ****/
extern const U8 Uart_CfgData[UART_MAX];
extern const Func_Void_Proc uart_tx_callback[UART_MAX];
extern const Func_Param8_Proc uart_rx_callback[UART_MAX];
extern const Func_Param8_Proc uart_error_callback[UART_MAX];
#endif/*_UART_CFG_H_*/
/**************** END OF FILE *****************************************/

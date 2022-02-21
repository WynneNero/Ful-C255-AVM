/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD NJ      									   *
*   AUTHOR	   : 										   *
************************************************************************
* Object        : SPI.C
* Module        :
* Instance      :
* Description   :
*-----------------------------------------------------------------------
* Version:  0.1
* Date: 2011-11-24
* Author: 
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
* ----------------------------------------------------------------------
* 0.1    Feb 10,2013               Initial version
*----------------------------------------------------------------------
* 0.2    Dec 20,2016   ShangQiuju  add config file according using hw
 ----------------------------------------------------------------------
* 0.3    Dec 21,2016    PEI Jingli     Remove unused . 
*------------------------------------------------------------------------
* 0.4    Jan 10,2017      ZhangJie           Add function parameter to solute Coverity warning.
 ----------------------------------------------------------------------
* 0.5    Jan 16,2017     RenWeimin  Add test code.
*-----------------------------------------------------------------------
* 0.6    Jan 24,2017     ZhangJie   Fix Coverity warnings.
*-----------------------------------------------------------------------
* 0.7    Feb 09,2017   ZhangJie   Remove EOL definition.
*-----------------------------------------------------------------------
* 0.8    Apr 04,2017   PEI Jingli  Fix headfile included.
*=====================================================================*/
/*============================================================================
Includes
============================================================================*/
#include "uart_cfg.h"
#include "uart.h"
#ifdef EOL_OPTION
#include "EOLuartdriver_IF.H"
#include "M4UartDriver_IF.H"
#endif

//============================================================================

const U8 Uart_CfgData[UART_MAX]=
{
    UARTE_LENGTH_8|UARTE_PARITY_NONE|UARTE_STOPLENGTH_1BIT|UARTE_TRANSFDIR_LSB,
    0,
    0,
    UARTE_LENGTH_8|UARTE_PARITY_NONE|UARTE_STOPLENGTH_1BIT|UARTE_TRANSFDIR_LSB,
    0,
    0,
};

const Func_Void_Proc uart_tx_callback[UART_MAX]=
{
NULL,
NULL,//isr_eng_on_tx_char,
M4UartDriver_SendIsr, // uart2 tx
#ifdef EOL_OPTION
		EolUartDriver_SentIsr,/* UART_3_TX */
 #endif

NULL,
NULL
};

const Func_Param8_Proc uart_rx_callback[UART_MAX]=
{
NULL,
NULL,//isr_eng_on_rx_char,
M4UartDriver_ReceiveIsr, //uart2 rx
#ifdef EOL_OPTION
		EolUartDriver_ReceiveIsr,/* UART_3_RX */
#endif
NULL,
NULL
};

const Func_Param8_Proc uart_error_callback[UART_MAX]=
{
NULL,
NULL,
NULL,
NULL,
NULL,
NULL
};
/**************** END OF FILE *****************************************/

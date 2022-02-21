/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD NJ     									   *
*   AUTHOR	   : 										   *
************************************************************************
* Object        : Uart_if.H
* Module        :
* Instance      :
* Description   :
*-----------------------------------------------------------------------
* Version:  0.1
* Date: 2016-06-07
* Author: Shao Guangxian
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
* ----------------------------------------------------------------------
* 0.1  Jun 07,2016  Zhang Jie    Initial version
* ----------------------------------------------------------------------
* 0.2  Jun 07,2016  LIU Chenxi   Refine code structure
* ----------------------------------------------------------------------
* 0.3  July 21,2016  PEI Jingli  Refactor codes and interfaces.
*-----------------------------------------------------------------------
* 0.4  Jan 18,2017    ZhangJie     Remove unused include headfile.
*----------------------------------------------------------------------
* 0.5    Apr 01,2017    PEI Jingli     Fix include files.
*=====================================================================*/
#ifndef _UART_IF_H_
#define _UART_IF_H_

#include "Define.h"


/**** Definition of types ****/
typedef enum
{
    UART_BAUDRATE_9600  =  9600,
    UART_BAUDRATE_14400 =  14400,
    UART_BAUDRATE_19200 =  19200,
    UART_BAUDRATE_38400 =  38400,
    UART_BAUDRATE_56000 =  56000,
    UART_BAUDRATE_57600 =  57600,
    UART_BAUDRATE_115200 = 115200,
} UART_BAUDRATE_TYPE;


/**** Definition of types ****/

typedef enum
{
     UART_0=0,                     
     UART_1,                     
     UART_2,                     
     UART_3,                     
     UART_4,
     UART_5,
     UART_MAX
}UART_TYPE;            

/**** Definition of macros ****/


/**** Declaration of functions ****/
extern void UART_Start( UART_TYPE uart, U32  baudrate);
extern void UART_Stop( UART_TYPE uart );
extern void UART_SendBuf( UART_TYPE uart, U8* pdata,U16 datalen );



#endif/*_UART_IF_H*/
/****************************** END OF FILE ***************************/

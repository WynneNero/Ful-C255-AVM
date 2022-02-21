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
* Version: 1.0
* Date:2017/10/30
* Author: TanPeng
***********************************************************************/

#ifndef _M4_UART_DRIVER_IF_H_
#define _M4_UART_DRIVER_IF_H_ 

#define UART_FIFO_BUF_SIZE (256)

extern void M4UartDriver_10ms_Entry();
extern void M4UartDriver_Init(void);
extern void M4UartDriver_DeInit(void);
extern U8 M4UartDriver_Open(void);
extern U8 M4UartDriver_Close(void);
extern U8 M4UartDriver_Control(U8 type, void* buffer);
extern U8 M4UartDriver_Write( U8* buffer, U16 Len);
extern U8 M4UartDriver_Read( U8* buffer, U16 Len);
extern void M4UartDriver_SendIsr(void);
extern void M4UartDriver_ReceiveIsr(U8 data);


#endif

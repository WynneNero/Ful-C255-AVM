/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : Tan Peng									   *
************************************************************************
* Object        : MCU UART2
* Module        : FIFO UART
* Instance      : 
* Description   : MCU UART2 COMMUNICATE WITH SOC M4 
*-----------------------------------------------------------------------
* Version: 1.0
* Date: 2017/1031
* Author: Tanpeng
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
* 
*=====================================================================*/
#ifndef _M4_UART_DRIVER_H_
#define _M4_UART_DRIVER_H_ 
#include "Tools.h"
#include "Define.h"
#include "CONFIG.H"
#include "M4UartDriver_IF.H"
#include "queue.H"

#define UART_FIFO_SEND_DEPTH (16)
#define UART_FIFO_RCV_DEPTH (4)

#define UART_FIFO_FRAME_HEAD_0 (0XFF)
#define UART_FIFO_FRAME_HEAD_1 (0XA5)
#define UART_FIFO_FRAME_HEAD_2 (0X5A)
#define UART_FIFO_FRAME_HEAD_NUM (3)
enum{
    E_M4_DRIVER_NONE,
    E_M4_DRIVER_OPENED,
    E_M4_DRIVER_CLOSED,
    
};
typedef struct fifoUartSend {
    U8 buf[UART_FIFO_SEND_DEPTH][UART_FIFO_BUF_SIZE];
    Queue_t que;
} FifoUartSend;

typedef struct fifoUartRcv {
    U8 buf[UART_FIFO_RCV_DEPTH][UART_FIFO_BUF_SIZE];
    Queue_t que;
} FifoUartRcv;

enum{
    E_RCV_HEAD_0,
    E_RCV_HEAD_1,
    E_RCV_HEAD_2,
    E_RCV_REQ_LEN
};
enum{
    E_SEND_HEAD_0,
    E_SEND_HEAD_1,
    E_SEND_HEAD_2,
    E_SEND_LEN,
    E_SEND_DATA_BEGIN
};
typedef struct m4UartRcv
{
    U8 buf[UART_FIFO_BUF_SIZE];
    U16 reqLen;		// need rcv data;
    U16 rcvLen;		// actually received length
}M4UartRcv;

typedef struct m4UartSend
{
    U8 buf[UART_FIFO_BUF_SIZE];
    volatile BOOL isSending;	
}M4UartSend;

void M4UartDriver_Init(void);
void M4UartDriver_DeInit(void);
U8 M4UartDriver_Open(void);
U8 M4UartDriver_Close(void);
U8 M4UartDriver_Control(U8 type, void* buffer);
U8 M4UartDriver_Write( U8* buffer, U16 Len);
U8 M4UartDriver_Read( U8* buffer, U16 Len);
void M4UartDriver_SendIsr(void);
void M4UartDriver_ReceiveIsr(U8 data);

#endif /*_M4_UART_DRIVER_H_*/

/****************************** END OF FILE ***************************/


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
* Version:1.0
* Date: 2017/10/11
* Author: TanPeng
*=====================================================================*/

#include "M4UartDriver.h"
#include "irq_if.h"
#include "tools.h"
#include "Uart_if.h"
#include "Driver_if.h"


static FifoUartSend  sendFIFO;
static FifoUartRcv   rcvFIFO;
static M4UartRcv     rcv;
static M4UartSend    send;
static U8 status;

void resetData(void)
{
    int i=0;
    for(i=0;i<UART_FIFO_SEND_DEPTH;i++)
    {
        _memset(sendFIFO.buf[i],0,UART_FIFO_BUF_SIZE);
    }
    send.isSending = FALSE;
    _memset(send.buf,0,UART_FIFO_BUF_SIZE);
    clearQue(&sendFIFO.que);

    for(i=0;i<UART_FIFO_RCV_DEPTH;i++)
    {
        _memset(rcvFIFO.buf[i],0,UART_FIFO_BUF_SIZE);
    }
    rcv.rcvLen = 0;
    rcv.reqLen = 0;
    _memset(rcv.buf,0,UART_FIFO_BUF_SIZE);
    clearQue(&rcvFIFO.que);
}

void cleanData(void)
{
    status = E_M4_DRIVER_NONE;
    send.isSending = FALSE;
    rcv.rcvLen = 0;
    rcv.reqLen = 0;
    clearQue(&sendFIFO.que);
    clearQue(&rcvFIFO.que);
    
}
void calCks(U8* buffer, U8 Len)
{
    U8 i = 0; 
    U8 CKS = 0;
  
    for(i=0;i<Len;i++)
    {
        CKS=CKS^buffer[i];
    }
    buffer[i]=CKS;
}

void triggerFIFOSend()
{
    S32 sendIndex = -1;
    Queue_t* pQue = &(sendFIFO.que);

    if(send.isSending)
    {
        return ;// has been seeding
    }

    sendIndex = getQueHead(pQue);
    if(sendIndex != -1)
    {
        send.isSending = TRUE;
        _memcpy(&send.buf[0],&sendFIFO.buf[sendIndex][0],sendFIFO.buf[sendIndex][E_SEND_LEN]+UART_FIFO_FRAME_HEAD_NUM);
        deQue(pQue);
        UART_SendBuf(M4_UART,&send.buf[0],send.buf[E_SEND_LEN]+UART_FIFO_FRAME_HEAD_NUM);// here will add frame head
    }
}

void M4UartDriver_Init(void)
{
    initQue(&(sendFIFO.que),UART_FIFO_SEND_DEPTH);
    initQue(&(rcvFIFO.que),UART_FIFO_RCV_DEPTH);
    resetData();  
}

void M4UartDriver_DeInit(void)
{
    resetData();
}

void M4UartDriver_10ms_Entry()
{
    if(status == E_M4_DRIVER_OPENED)
    {
        triggerFIFOSend();
    }
}

U8 M4UartDriver_Open(void)
{
    cleanData();
    UART_Start(M4_UART,UART_BAUDRATE_115200);
    status = E_M4_DRIVER_OPENED;
    return 0;
}

U8 M4UartDriver_Close(void)
{
    UART_Stop(M4_UART);
    cleanData();
    status = E_M4_DRIVER_CLOSED;
    return 0;
}

U8 M4UartDriver_Control(U8 type, void* buffer)
{
    return 0;
}

U8 M4UartDriver_Write( U8* buffer, U16 Len)
{

    U8 result =  ERR_FAILED;
    S32 wIndex = -1;
    Queue_t* pQue = &(sendFIFO.que);

    if((buffer == NULL) || (Len > (UART_FIFO_BUF_SIZE-5) )) // here 3 head and 1 lenght,1 CKS;
    {
        return result;
    }
   
    wIndex = getQueTail(pQue);
    if(wIndex != -1)
    {
        sendFIFO.buf[wIndex][E_SEND_HEAD_0] = UART_FIFO_FRAME_HEAD_0;
        sendFIFO.buf[wIndex][E_SEND_HEAD_1] = UART_FIFO_FRAME_HEAD_1;
        sendFIFO.buf[wIndex][E_SEND_HEAD_2] = UART_FIFO_FRAME_HEAD_2;
        sendFIFO.buf[wIndex][E_SEND_LEN] = Len+2; // CKS,len , is in length
        
        _memcpy(&sendFIFO.buf[wIndex][E_SEND_DATA_BEGIN],buffer,Len);
        calCks(&sendFIFO.buf[wIndex][E_SEND_LEN],Len+1);//
        enQue(pQue);
        result = ERR_OK;
     }
     
    // triggerFIFOSend();
     return result;  
}

U8 M4UartDriver_Read( U8* buffer, U16 Len)
{
    S32 rIndex = -1;
    U8  result = 0;
    
    Queue_t* pQue = &(rcvFIFO.que);
    
    if((buffer == NULL) || (Len == 0)) 
    {
        return 0;
    }
    
   rIndex = getQueHead(pQue);
   if(rIndex != -1)
   {
        if(Len < rcvFIFO.buf[rIndex][0])
        {
            _memcpy(buffer,&rcvFIFO.buf[rIndex][1],Len); // buf[rIndex][0]is data len
            result = Len;
        }
        else
        {
            _memcpy(buffer,&rcvFIFO.buf[rIndex][1],rcvFIFO.buf[rIndex][0]);
            result = rcvFIFO.buf[rIndex][0];
        }
        deQue(pQue);
   }
   else
   {
        _memset(buffer,0,Len); // not has data read
   }
 
   
   return result;
}

void M4UartDriver_SendIsr(void) // one frame send end enter sendIsr
{
    send.isSending = FALSE;
    //triggerFIFOSend(); // triggle next frame
}

void M4UartDriver_ReceiveIsr(U8 data)
{
    S32 wIndex = -1;
     
    switch(rcv.rcvLen)
    {
        case E_RCV_HEAD_0:
        {
            if(data == UART_FIFO_FRAME_HEAD_0)
            {
                rcv.buf[rcv.rcvLen] = data;
                rcv.rcvLen++;
            }
            else
            {
                rcv.rcvLen = 0;
                rcv.reqLen = 0;
            }
            break;
        }
        
        case E_RCV_HEAD_1:
        {
            if(data == UART_FIFO_FRAME_HEAD_1)
            {
                rcv.buf[rcv.rcvLen] = data;
                rcv.rcvLen++;
            }
            else
            {
                rcv.rcvLen = 0;
                rcv.reqLen = 0;
            }
            break;
        }
        
        case E_RCV_HEAD_2:
        {
            if(data == UART_FIFO_FRAME_HEAD_2)
            {
                rcv.buf[rcv.rcvLen] = data;
                rcv.rcvLen++;
            }
            else
            {
                rcv.rcvLen = 0;
                rcv.reqLen = 0;
            }
            break;
        }
        
        case E_RCV_REQ_LEN:
        {
            if((data >= 3))// min data len is 3
            {
                rcv.buf[rcv.rcvLen] = data;
                rcv.reqLen = data + E_RCV_REQ_LEN;
                rcv.rcvLen++;
               
            }
            else
            {
                rcv.rcvLen = 0;
                rcv.reqLen = 0;
            }
            break;
            
        }

        default:
        {
            rcv.buf[rcv.rcvLen] = data;
            rcv.rcvLen++;
            
            if(rcv.rcvLen == rcv.reqLen)// rcv end , end data is cks
            {
                calCks(&rcv.buf[E_RCV_REQ_LEN],rcv.buf[E_RCV_REQ_LEN]-1);// last is CKS
                if(data == rcv.buf[rcv.rcvLen-1]) // chech cks
                {
                    wIndex = getQueTail(&rcvFIFO.que);
                    if(wIndex != -1)
                    {
                        rcv.buf[E_RCV_REQ_LEN]= rcv.buf[E_RCV_REQ_LEN]-1; // move cks
                        _memcpy(&rcvFIFO.buf[wIndex][0],&rcv.buf[E_RCV_REQ_LEN],rcv.buf[E_RCV_REQ_LEN]);
                        enQue(&rcvFIFO.que);
                    }
                    
                }
                
                rcv.rcvLen = 0;
                rcv.reqLen = 0;
            }
            break;    
        }

    }

}








/**************** END OF FILE *****************************************/


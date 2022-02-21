/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : Tan Peng									   *
************************************************************************
* Object        : MCU UART1 
* Module        : FIFO UART
* Instance      : 
* Description   : MCU UART1 COMMUNICATE WITH SOC M4 
*-----------------------------------------------------------------------
* Version: 1.0
* Date: 2017/1031
* Author: Tanpeng
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
* 
*=====================================================================*/
#ifndef _queue_H_
#define _queue_H_
#include "define.h"

typedef struct queue {
    U32 size;
    volatile U32 front;     
    volatile U32 rear;      
} Queue_t;

void initQue(Queue_t* que, S32 que_size);
void clearQue(Queue_t* que);
BOOL isQueEmpty(Queue_t* que);
BOOL isQueFull(Queue_t* que);
S32 getQueHead(Queue_t*que ); // retrun head posi
S32 getQueTail(Queue_t*que ); // return tail posi
S32 enQue(Queue_t*que ); // retrun new tail posi
S32 deQue(Queue_t*que ); // retrun new head posi

#endif /*_queue_H_*/

/****************************** END OF FILE ***************************/


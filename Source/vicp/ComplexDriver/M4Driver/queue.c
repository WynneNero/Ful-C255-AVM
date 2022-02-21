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

#include "queue.h"

void initQue(Queue_t* que,S32 que_size)
{
    if(que != NULL)
    {
        que->front = 0; 
        que->rear = 0;

        if(que_size > 0)
        {
        que->size = que_size;
        }
        else
        {
        que->size =1;
        }
    }
}


void clearQue(Queue_t* que)
{
    if(que != NULL)
    {
        que->front = 0; 
        que->rear = 0;
    }
}


BOOL isEmpty(Queue_t* que)
{
    if(que != NULL)
    {
        return (que->front == que->rear);
    }
    
    return TRUE;
}


BOOL isFull(Queue_t* que)
{
    if(que != NULL)
    {
        return (((que->rear + 1) % que->size) == (que->front));
    }
    
    return TRUE;
}

S32 getQueHead(Queue_t*que )
{
    if(que == NULL)
    {
        return -1;
    }

    if(isEmpty(que))
    {
        return -1;
    }
   
    return que->front;
}


S32 getQueTail(Queue_t*que )
{
    if(que == NULL)
    {
        return -1;
    }
    
    if(isFull(que)) 
    {
        return -1;
    }
    
    return que->rear;
}


S32 enQue(Queue_t*que )
{
    if(que == NULL)
    {
        return -1;
    }
    
    if(isFull(que)) 
    {
       return -1;
    }
    
    que->rear = (que->rear+1) % que->size;
    return que->rear;
}


S32 deQue(Queue_t*que )
{
    
    if(que == NULL)
    {
        return -1;
    }

    if(isEmpty(que))
    {
        return -1;
    }
 
    que->front = ((que->front+1) % que->size);
    return que->front;
}




/**************** END OF FILE *****************************************/


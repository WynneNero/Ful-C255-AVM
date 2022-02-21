/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   : Zhang Jiacheng										   *
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
#ifndef _FIFO_IF_H_
#define _FIFO_IF_H_ 
/**** Definition of constants ****/


/**** Definition of types ****/ 
typedef struct 
{
    U8  *mpFIFOBuffer;
    U16  mFIFOHead;   
    U16  mFIFOTail;  
    U16  mFIFOLength; //888 to hold current length
    U16  mFIFOSize;
} FIFO_TYPE;

/**** Definition of macros ****/


/**** Declaration of constants ****/


/**** Declaration of variables ****/


/**** Declaration of functions ****/
extern void fifo_init( FIFO_TYPE *this, U8 *pBuf, U16 nSize);
extern BOOL fifo_input_frame( FIFO_TYPE *this , U8 *pFrame, U8 length);
extern BOOL fifo_output_frame( FIFO_TYPE *this, U8 *pFrame, U8 *length);
extern BOOL fifo_input_block( FIFO_TYPE *this , U8 *pFrame , U8 length);
extern BOOL fifo_output_block( FIFO_TYPE *this , U8 *pFrame , U8 length);
extern BOOL fifo_has_enough_space(FIFO_TYPE * this,U8 nBytes);
extern U16 fifo_current_length(FIFO_TYPE *this  );

#endif /*_FIFO_IF_H_*/

/****************************** END OF FILE ***************************/

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
#ifndef _FIFO_H_
#define _FIFO_H_ 
/**** Definition of constants ****/


/**** Definition of types ****/ 

/**** Definition of macros ****/


/**** Declaration of constants ****/


/**** Declaration of variables ****/


/**** Declaration of functions ****/

static BOOL fifo_is_empty(FIFO_TYPE *this  );
static BOOL fifo_is_full(FIFO_TYPE *this  );
static BOOL fifo_input_byte( FIFO_TYPE *this , unsigned char byte );
static BOOL fifo_output_byte(FIFO_TYPE *this, U8 *pdata);
 U16 fifo_have_enough_space(FIFO_TYPE *this , U8 nBytes);

#endif /*_FIFO_IF_H_*/

/****************************** END OF FILE ***************************/

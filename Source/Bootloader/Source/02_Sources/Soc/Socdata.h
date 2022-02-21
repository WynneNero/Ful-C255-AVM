/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   :            										   *
************************************************************************
* Object        : 
* Module        : 
* Instance      : 
* Description   : 
*-----------------------------------------------------------------------
* Version:v0.01
* Date:   2012/3/1
* Author: tsingchun
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date        Name         Changes and comments
* v0.01         2012/3/1    Tsingchun    initial version
*=====================================================================*/
#ifndef _SOC_DATA_H_
#define _SOC_DATA_H_
#include "define.h"
#include "socdata_if.h"

/**** Definition of constants ****/


/**** Definition of types ****/ 


/**** Definition of macros ****/
typedef enum
{
    S19_ROW_IDENTI_FLAG,//0
    S19_ROW_TYPE,//1
    S19_ROW_LEN,//2

    S19_FILE_LEN1,//3
    S19_DATA_ADD1= S19_FILE_LEN1,
    S19_FILE_LEN2,
    S19_DATA_ADD2= S19_FILE_LEN2,     
    S19_FILE_LEN3, 
    S19_DATA_ADD3= S19_FILE_LEN3,
    S19_FILE_LEN4,
    S19_DATA_ADD4= S19_FILE_LEN4,

    S19_FILE_CKSUM1,//7
    S19_DATA = S19_FILE_CKSUM1, 
    S19_FILE_CKSUM2,
    S19_FILE_CKSUM3,
    S19_FILE_CKSUM4,

    S19_PORJECT_NAME,//11-20
    S19_FIRST_LINE_XOR_HIGH=21,
    S19_FIRST_LINE_XOR_LOW,
    S19_FIRST_ROW_CKSUM,
}S19_FILE_FIRST_ROW_FORMATE;

typedef enum
{
    S0_ROW,
    S1_ROW,
    S2_ROW,
    S3_ROW,
    S4_ROW,
    S5_ROW,
    S6_ROW,
    S7_ROW,
    S8_ROW,
    S9_ROW,
}S19_IDENTIFICATION_ID;

/**** Declaration of constants ****/


/**** Declaration of variables ****/
extern U8 swdl_data_frame_len;
extern U8 swdl_data_frame[SWDL_FRAME_LEN];
extern BOOL swdl_data_recieved;
//
extern U32 file_cur_row_addr;
extern U8  file_cur_row_length;
extern U8 *file_cur_row_data_buffer_ptr;
//
extern U32 file_data_len;
extern U32 file_data_sum;
extern U32 file_data_decode_len;
extern U32 file_data_decode_sum;

/**** Declaration of functions ****/



#endif /*_BL_SOC_DATA_H_*/

/****************************** END OF FILE ***************************/


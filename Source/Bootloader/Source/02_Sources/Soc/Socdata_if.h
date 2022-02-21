/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   : tsingchun           								   *
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
#ifndef _SOC_DATA_IF_H_
#define _SOC_DATA_IF_H_ 

/**** Definition of constants ****/
#if 1
#define SWDL_DATA_LEN 192
#else
#define SWDL_DATA_LEN 2
#endif
#define SWDL_FRAME_LEN (SWDL_DATA_LEN+9)
#define SWDL_FRAME_MAX_SIZE  SWDL_FRAME_LEN 


/**** Definition of types ****/ 
#define FLASH_APP_START_ADDRESS  0x18000  //xjy_test 0x11000

/**** Definition of macros ****/


/**** Declaration of constants ****/


/**** Declaration of variables ****/


/**** Declaration of functions ****/
extern void navi_intial_misc_variables(void);
extern BOOL check_cur_row_checksum(void);
extern U8 check_cur_row_type(void);
extern U32 get_cur_row_addr(void);
extern U8 get_cur_row_length(void);
extern ERR_TYPE swdl_data_handle(void);
extern ERR_TYPE swdl_check_first_row_valid(void);
extern BOOL check_first_line_xor_value_valid(void);
extern void navi_pw_request_navi_enter_swdl(void);

extern void SocDataReceivedData(U8 size,U8* data);

#endif /*_BL_SOC_DATA_IF_H_*/

/****************************** END OF FILE ***************************/


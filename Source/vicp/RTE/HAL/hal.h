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
* Version: 
* Date: 
* Author: 
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
*----------------------------------------------------------------------
* 0.1    Dec 20,2015   init version.
*----------------------------------------------------------------------
* 0.2    Dec 20,2016   ShangQiuju Remove unused include files.
*----------------------------------------------------------------------
* 0.3    Jan 4,2017   Update for V_hal_powerstatus,V_hal_block_powerstatus,
                              remove parameter.
*------------------------------------------------------------------------
* 0.4    Jan 18,2017  ZhangJie  Fix Coverity warning.
*=====================================================================*/
#ifndef _HAL_H_
#define _HAL_H_ 
#include "Driver_IF.H"
#include "Define.h"

#define  DEV_PASS_1
#include "HAL_def.h"

/**** Definition of constants ****/

/**** Definition of macros ****/
typedef  U8(*const V_hal_open)(void );
typedef  U8 ( *const V_hal_close)(void);
typedef  U8( *const V_hal_read)( U8* buffer, U16 Len);
typedef  U8( *const V_hal_write)(U8* buffer, U16 Len);
typedef  U8( *const V_hal_iocontrol)(U8 type, void* buffer);
typedef  void( *const V_hal_powercontrol)(E_DEV_POWER type);
typedef  U8( *const V_hal_powerstatus)(void);

typedef  U8(*const V_hal_block_open)(void );
typedef  U8 ( *const V_hal_block_close)(void);
typedef  U8( *const V_hal_block_read)( U32 address,U8* buffer, U16 Len);
typedef  U8( *const V_hal_block_write)(U32 address,U8* buffer, U16 Len);
typedef  U8( *const V_hal_block_iocontrol)(U8 type, void* buffer);
typedef  void( *const V_hal_block_powercontrol)(E_DEV_POWER type);
typedef  U8( *const V_hal_block_powerstatus)(void);
/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/
extern U8 V_hal_open_empty( void);
extern U8 V_hal_close_empty( void);
extern U8 V_hal_read_empty( U8* buffer, U16 Len);
extern U8 V_hal_write_empty(  U8* buffer, U16 Len);
extern U8 V_hal_iocontrol_empty(U8 type, void* buffer);

extern U8 V_hal_block_open_empty( void);
extern U8 V_hal_block_close_empty( void);
extern U8 V_hal_block_read_empty( U32 address,U8* buffer, U16 Len);
extern U8 V_hal_block_write_empty( U32 address, U8* buffer, U16 Len);
extern U8 V_hal_block_iocontrol_empty(U8 type, void* buffer);
#endif /*_SIGNAL_H_*/

/****************************** END OF FILE ***************************/


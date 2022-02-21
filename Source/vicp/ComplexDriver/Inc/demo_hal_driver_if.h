/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                         *
*   AUTHOR     :                                       *
************************************************************************
* Object        : vicp
* Module        : demo complex driver 
* Instance      :
* Description   : Exposed API interface
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
*-----------------------------------------------------------------------
* 0.1  Aug 11,2016  LIU Chenxi  Initial version
*------------------------------------------------------------------------
* 0.2 Jan 24,2017  ZhangJie  Fix Coverity warnings.
*=====================================================================*/
#ifndef _DEMO_HAL_DRIVER_IF_H_
#define _DEMO_HAL_DRIVER_IF_H_
#include "CONFIG.H"
#include "TYPES.H"

/*put exposed interface prototype below */

void  Demo_Hal_Driver_Init(void);
void  Demo_Hal_Driver_Deinit(void);
void  Demo_Hal_Driver_CyclicTaskEnery_20ms(void);

/*exposed to HAL configuration*/

U8  Demo_Hal_Driver_Open(void);
U8  Demo_Hal_Driver_Close(void);
U16 Demo_Hal_Driver_Read(U8* buffer, U16 len);
U8  Demo_Hal_Driver_Write(U8* buffer, U16 len);



#endif /*_DEMO_HAL_DRIVER_IF_H_*/

/****************************** END OF FILE ***************************/


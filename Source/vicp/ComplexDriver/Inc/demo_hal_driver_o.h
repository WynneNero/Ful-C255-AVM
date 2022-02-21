/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                         *
*   AUTHOR     :                                       *
************************************************************************
* Object        : vicp
* Module        : demo complex driver
* Instance      :
* Description   : Exposed callback and other objects 
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
#ifndef _DEMO_HAL_DRIVER_O_H_
#define _DEMO_HAL_DRIVER_O_H_

#include "CONFIG.H"
#include "TYPES.H"

/*put exposed callback entried and objects below */


void Demo_Hal_Driver_SentISR(void);
void Demo_Hal_Driver_ReceiveISR(U8 data);




#endif /*_DEMO_HAL_DRIVER_O_H_*/

/****************************** END OF FILE ***************************/


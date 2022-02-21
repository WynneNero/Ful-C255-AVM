/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   : Shao Guangxian										   *
************************************************************************
* Object        : SPI.H
* Module        :
* Instance      :
* Description   :
*-----------------------------------------------------------------------
* Version:  0.1
* Date: 2011-11-24
* Author: Shao Guangxian
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
*-----------------------------------------------------------------------
* 0.1	   Dec 02,2016   PEI Jingli  Initial version
*----------------------------------------------------------------------
* 0.2     Dec 20,2016   ShangQiuju   Add exti_if.h for complie error.
*-----------------------------------------------------------------------
* 0.3	Apr 01,2017   PEI Jingli  Fix headfiles.
*=====================================================================*/
#ifndef _EXIT_CFG_H_
#define _EXIT_CFG_H_
#include "EXTI_if.h"

/**** Definition of constants ****/

/**** Definition of types ****/


/**** Definition of macros ****/


/**** Declaration of constants ****/


/**** Declaration of variables ****/


/**** Declaration of functions ****/
extern const Func_Void_Proc mcu_intp_callback[EXTI_NUM];

#endif
/**************** END OF FILE *****************************************/

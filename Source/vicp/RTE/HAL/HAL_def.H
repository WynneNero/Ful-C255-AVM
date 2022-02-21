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
* Version       Date       Name          Changes and comments
 ----------------------------------------------------------------------
* 0.1    Jun 26,2016                        Initial version
 ----------------------------------------------------------------------
* 0.2    Dec 21,2016     PEI Jingli      add file patch according using hw 
 ----------------------------------------------------------------------
* 0.3    Jan 4,2017       ShangQiuju   using hal_cfg.h Pacth configed at config.h
*------------------------------------------------------------------------
* 0.4    Jan 11,2017  ZhangJie  Add parentheses to avoid Coverity warning.
*=====================================================================*/
/**** Definition of constants ****/
#include "config.h"

/**** Definition of macros ****/
/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/

#ifdef DEV_PASS_1
    #undef DEV_PASS_1
    #define BEGIN_DEV        enum DEV_Name {
    #define END_DEV          E_DEV_NUM };
    #define DEVDESC(x)          x,

    #define BEGIN_DEVBLOCK        enum DEVBLOCK_Name {
    #define END_DEVBLOCK          E_DEVBLOCK_NUM };
    #define DEVBLOCKDESC(x)          x,

    #include HAL_CFG_H_PATH
    #define HAL_DEV_MAX (E_DEV_NUM+1u)   
    #define HAL_BLDEV_MAX (E_DEVBLOCK_NUM+1u)    
#endif

/****************************** END OF FILE ***************************/


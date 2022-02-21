/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                         *
*   AUTHOR     :                                       *
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
*------------------------------------------------------------------------
* 0.1          Jun 11,2016                  Init version.
*------------------------------------------------------------------------
* 0.2          Jan 11,2017  ZhangJie  Add parentheses and add u for constant value to avoid Coverity warning.
*-----------------------------------------------------------------------
* 0.3          Jan 24,2017   ZhangJie   Remove unused include file.
*=====================================================================*/
#ifndef _CYCLICTASK_CFG_H_
#define _CYCLICTASK_CFG_H_
/**** Definition of constants ****/

/* Switch to select if the X ms auxiliary timer A is to be supported or not. */
#define SYSCYCLE_FASTCYCLE_COUNT    3u
#define SYSCYCLE_SLOWCYCLE_COUNT    2u

#define PRE_SECOND_FUNC_EN  0u

#if (PRE_SECOND_FUNC_EN==1u)
#define SYS_CFG_FOREGROUND_1S_TICK   1000u
#define SYS_CFG_BACKGROUND_1S_TICK   40u
#endif

/**** Definition of macros ****/
/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/



#endif /*_CYCLICTASK_CFG_H_*/

/****************************** END OF FILE ***************************/


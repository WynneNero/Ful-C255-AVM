/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   : Shao Guangxian										   *
************************************************************************
* Object        : ERR_IF.H
* Module        :
* Instance      :
* Description   :
*-----------------------------------------------------------------------
* Version:  0.1
* Date: 2011-12-20
* Author: Shao Guangxian
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
*------------------------------------------------------------------------
* 0.1          Jun 11,2016                Init version.
*------------------------------------------------------------------------
* 0.2          Jan 24,2017  ZhangJie  Fix Coverity warnings.
*=====================================================================*/
#ifndef _ERR_IF_H_
#define _ERR_IF_H_
/*#include "CONFIG.H"*/
/*#include "TYPES.H"*/
#include "Define.h"
#include <stdio.h>
/**** Definition of constants ****/


/**** Definition of types ****/

/**** Declaration of functions ****/
extern void assert_failed(U8* file, U32 line);
extern void assert_error(U8 * message);

/**** Definition of macros ****/
#ifdef  DEBUG_VERSION
    #define assert_param(expr) ((expr) ? (void)0 : assert_failed((U8 *)__FILE__, __LINE__))
#else /* DEBUG_VERSION */
    #define assert_param(expr) ((void)0)
#endif /* DEBUG_VERSION */

#define IS_RANGE(val, min, max)                (((val+1u) >=(min+1u)) && ((1u+val)<=(max+1u)))

/**** Declaration of constants ****/


/**** Declaration of variables ****/



/***********end extern micro/type define ****************/

#endif /*_ERR_IF_H_*/
/****************************** END OF FILE ***************************/

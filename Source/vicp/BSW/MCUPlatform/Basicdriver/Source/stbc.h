/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.		           *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									                   *
************************************************************************
* Object        :  stbc.h 
* Module        : 
* Instance      : 
* Description   : mcu stand-by mode
*-----------------------------------------------------------------------
* Version: 
* Date: 
* Author: 
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
* ----------------------------------------------------------------------
* 0.1  Apr 15,2016     Pei JL     Initial 5 clock OSC, and clock domain.
* ----------------------------------------------------------------------
* 0.2  Dec 29,2016  PEI Jingli  Modify for codereview result
*------------------------------------------------------------------------
* 0.3  Jan 24,2017  ZhangJie  Fix Coverity warning.
===============================================================*/
#ifndef  _STBC_H
#define   _STBC_H
#include "cpu.h"

/*----- stand-by mode and wakeuping related register address  -----*/
/*power stop trigger reg ,for stop mode*/
#define STBC_REG_STPT                (*(CPU_REG32  *)0xFFF80110u)
/*power save control reg ,for deep stop mode*/
#define STBC_REG_PSC                  (*(CPU_REG32 *)0xFFF80100u)
/*I/O buffer hold control reg ,for deep stop mode*/
#define STBC_REG_IOHOLD            (*(CPU_REG32 *)0xFFF80B00u)
/*wakeup factor clear reg.Set bit as 1 to clear flag*/
#define STBC_REG_WUFC0              (*(CPU_REG32 *)0xFFF80408u)
#define STBC_REG_WUFC20            (*(CPU_REG32 *)0xFFF80528u)
#define STBC_REG_WUFC_ISO0      (*(CPU_REG32 *)0xFFF88118u)
/*wakeup factor mask reg.Set bit as 1 to disable the factor*/
#define STBC_REG_WUFMSK0            (*(CPU_REG32 *)0xFFF80404u)
#define STBC_REG_WUFMSK20          (*(CPU_REG32 *)0xFFF80524u)
#define STBC_REG_WUFMSK_ISO0    (*(CPU_REG32 *)0xFFF88114u)


#endif/*_STBC_H */


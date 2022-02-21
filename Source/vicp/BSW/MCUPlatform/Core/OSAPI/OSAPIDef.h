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
* ----------------------------------------------------------------------
* 0.1    Feb 10,2013        Initial version
*------------------------------------------------------------------------
* 0.2    Jan 12,2017  ZhangJie  Fix Coverity warning.
*=====================================================================*/
#ifndef _OSAPIDEF_H_
#define _OSAPIDEF_H_ 
#include <MCUBoard_I.h>

/**** Definition of constants ****/
/*
typedef enum E_OSAPI_SUPPORT_OS
{
   OSAPI_SUPPORT_UCOS,
   OSAPI_SUPPORT_RTX,
   OSAPI_SUPPORT_OSNUM
}OSAPI_SupportOSType;
*/

/**** Definition of types ****/
/*
typedef enum E_OSAPI_SUPPORT_MCU
{
   OSAPI_SUPPORT_MCUMB9BF404NA_100,
   OSAPI_SUPPORT_MCUMB9BF404RA_120,
   OSAPI_SUPPORT_MCUV850_3580,
   OSAPI_SUPPORT_MCUNUM
}OSAPI_SupportMCUType;
*/

/**** Definition of types ****/
typedef  void( *const Task_Proc )( void );
/**** Definition of types ****/

/*
typedef struct _OSAPI_TaskCfg
{
	U8 id;
	BOOL BasicTask;
	U8 taskpriority;
	U16   stacksize;	
	void* taskstack;
	Task_Proc taskproc;
}OSAPI_TaskCfgType;
*/
typedef struct _OSAPI_TaskCfg
{
	U8 id;
	BOOL BasicTask;
	U8 taskpriority;
	Task_Proc taskproc;
}OSAPI_TaskCfgType;

typedef enum E_WDG_TYPE
{
    OSAPI_INTERNAL_WDG,
    OSAPI_EXTENAL_WDG,
    OSAPI_BOTH
}OSAPI_WDGType;

typedef  void( *const WDG_Proc )( U16 Tick );
/**** Definition of types ****/
typedef struct _OSAPI_WdgCfg
{
	U8 id;
	OSAPI_WDGType WDGType;
	U16     MaxTick;
	BOOL isResetMCU;
	WDG_Proc wdgproc;
}OSAPI_WdgCfgType;

typedef enum E_WDG_STATE
{
    OSAPI_WDG_STOP,
    OSAPI_WDG_START,
    OSAPI_WDG_PAUSE,
    OSAPI_WDG_INTERRUPT
}OSAPI_WDGState;

/**** Definition of macros ****/

#define OSAPI_UNKNOWTASK 0x00u
#define OSAPI_ACTIVETASK 0xA5u
#define OSAPI_TERMINATETASK 0x5Au
#define OSAPI_MULTIACTIVE_NUM 2u
#define OSAPI_SUSPENDTASK 0x55u
/**** Declaration of constants ****/
/**** Declaration of variables ****/


enum
{
       OS_NO_ERROR,
       OS_STACK_OV,
       OS_QUIT
};




#endif /*_OSAPIDEF_H_*/

/****************************** END OF FILE ***************************/


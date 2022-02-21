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
*------------------------------------------------------------------------
* 0.1          Jun 11,2016                  Init version.
*------------------------------------------------------------------------
* 0.2          Jan 11,2017  ZhangJie  Remove unused typedef to avoid Coverity warning.
*-----------------------------------------------------------------------
* 0.3          Jan 17,2017   ZhangJie   Remove unused include file.
*=====================================================================*/
#ifndef _SYSTEMMODE_H_
#define _SYSTEMMODE_H_ 
/**** Definition of constants ****/

/**** Definition of macros ****/
enum
{
 SYSMODE_RESET=0,
 SYSMODE_MAIN,
 SYSMODE_SYSTEMRUN,
 SYSMODE_WAKUP,
 SYSMODE_SLEEP,
 SYSMODE_MAXTYPE
};


/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/
void SysMode_HardwareRest(void);
void SysMode_MainInit(void);
void SysMode_SystemInit(void);
void SysMode_SystemIdle(void);
U8 SysMode_GetSystemMode(void);
void SysMode_PreventSleep(void);
void SysMode_ToSleep(void);
void SysMode_DisableWakeupInt(U32 IRQ);
void SysMode_EnableWakeupInt(U32 IRQ, U32 type);
#define Notify_App_function()


#endif /*_SYSTEMMODE_H_*/

/****************************** END OF FILE ***************************/


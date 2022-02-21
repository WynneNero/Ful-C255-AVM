/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                         *
*   AUTHOR     :                                       *
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   : Implementation of the EEPROM Download Handler (EED)
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
*----------------------------------------------------------------------
*  0.1      Sep 19,2016                     init version.
*----------------------------------------------------------------------
*  0.2      Jan 24,2017    ZhangJie     Fix Coverity warning.
*=====================================================================*/
#ifndef _EEPDATA_H_
#define _EEPDATA_H_
#include "CONFIG.H"
#include "TYPES.H"


typedef enum
{
    EED_IDLE,
    EED_LOADRAM1REQ,
    EED_LOADRAM1ING,
    EED_LOADRAM1ED,
    EED_LOADRAM2REQ,
    EED_LOADRAM2ING,
    EED_LOADRAM2ED,

    EED_DLLOADRAM1REQ,
    EED_DLLOADRAM1ING,
    EED_DLLOADRAM1ED,
    EED_DLLOADRAM2REQ,
    EED_DLLOADRAM2ING,
    EED_DLLOADRAM2ED,
} EEDActionStep;

extern void EED_ResetInit(void);
extern BOOL EED_isStartupLoad(void);
extern BOOL EED_isStartupDownload(void);
extern void EED_Load_Request(void);
extern BOOL EED_IsLoad(void);
extern void EED_Download_Request(void);
extern BOOL EED_IsDownload(void);
extern BOOL EED_LoadStartup(void);
/*extern void App_EEPWrite_CallBack(ERR_TYPE type);*/

#define EET_UPGRADE_COMMUCALLBACK(type)     /*NaviApp_EEPWrite_CallBack(type)*/
#endif /*_EEPDATA_H_*/

/****************************** END OF FILE ***************************/


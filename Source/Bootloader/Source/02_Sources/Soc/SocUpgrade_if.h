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
* ----------------------------------------------------------------------
*  0.1          2016/8/29   ShangQiuju      Init version
* ----------------------------------------------------------------------
*  0.2          2016/12/30 ShangQiuju     Change app address and size as config parameter.
*=====================================================================*/
#ifndef _SOC_UPGRADE_IF_H_
#define _SOC_UPGRADE_IF_H_

#include "CONFIG.H"
#include "define.h"

#include "bl_typedefs.h"
//#include "bl_adapter.h"
#include "bl_rte.h"


#define APP_ADDRESS  0x18000  
#define EASE_APP_ADDRESS 0x48000 

extern bl_Return_t SocInit(void);
extern void SocApp(void);
extern void SocDeInit(void);
extern void FlashWriteTimeout(void);
#endif /*_SOC_APP_H_*/

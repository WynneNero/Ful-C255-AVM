/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   :            										   *
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
 ----------------------------------------------------------------------
* 0.1    Jun 26,2016                        Initial version
 ----------------------------------------------------------------------
* 0.2    Jan 4,2017       ShangQiuju   update HAL_DevGetPowerStatus,
                                                        HALBlock_DevGetPowerStatus
*------------------------------------------------------------------------
* 0.3   Jan 24,2017  ZhangJie  Fix Coverity warnings.
*=====================================================================*/
#ifndef _HAL_IF_H_
#define _HAL_IF_H_ 
#include "HAL.h"

/**** Definition of constants ****/


/**** Definition of macros ****/
/* Macro definitions*/
extern void HAL_Init(void);
extern void HAL_DeInit(void);

/*device IO manager*/
extern U8 HAL_Open(U8 DeviceId);
extern U8 HAL_Close(U8 DeviceId);
extern U8 HAL_Read(U8 DeviceId, U8* buffer, U16 Len);
extern U8 HAL_Write(U8 DeviceId, U8* buffer, U16 Len);
extern U8 HAL_IoControl(U8 DeviceId, U8 type, void* buffer);

/*device power manager*/
extern void HAL_DevPowerControl(U8 DeviceId,E_DEV_POWER type);
extern U8 HAL_DevGetPowerStatus(U8 DeviceId);

extern void HALBlock_Init(void);
extern void HALBlock_DeInit(void);

/*device IO manager*/
extern U8 HALBlock_Open(U8 DeviceId);
extern U8 HALBlock_Close(U8 DeviceId);
extern U8 HALBlock_Read(U8 DeviceId, U32 address,U8* buffer, U16 Len);
extern U8 HALBlock_Write(U8 DeviceId, U32 address,U8* buffer, U16 Len);
extern U8 HALBlock_IoControl(U8 DeviceId, U8 type, void* buffer);

/*device power manager*/
extern void HALBlock_DevPowerControl(U8 DeviceId,E_DEV_POWER type);
extern  U8 HALBlock_DevGetPowerStatus(U8 DeviceId);
/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/



#endif /*_SIGNAL_IF_H_*/

/****************************** END OF FILE ***************************/


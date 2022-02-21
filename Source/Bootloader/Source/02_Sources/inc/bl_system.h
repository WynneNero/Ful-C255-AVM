/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a head file of the system clock module for mpc5604B.
 *
 *  \file       bl_system.h
 *  \ingroup    driver_module
 *  \author     lele.liu <lele.liu@hirain.com>
 *
 *  \version    1.0.0
 *  \date       11/08/2015
 *
 *  \par        Changelist
 *      Version    | Date     | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | -------------
 *      01.00.00 | 11/08/2015 | lele.liu         | N/A | BootDrv010001
 *
 *****************************************************************************/

#ifndef _BL_SYSTEM_H_
#define _BL_SYSTEM_H_
#include "define.h"
#include "bl_typedefs.h"
#include "dr7f701023_0.h"

/** \brief This function is used to go to application.*/
extern void Sys_GotoApplication(void);
extern void Sys_ProtectBootloader(void);
extern void Sys_Sleep(void);

extern void Sys_InitClock(void);
extern void Sys_RemapInterrupt(void);
extern void Sys_DeinitClock(void);
extern void Sys_Reset(void);
extern void tm_delay_us(U16 period);

#endif /* SYSTEM_H */








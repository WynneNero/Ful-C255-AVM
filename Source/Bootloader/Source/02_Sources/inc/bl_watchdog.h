/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the header file of the watchdog module for rh850/f1h or rh850/f1l.
 *
 *  \file       bl_watchdog.h
 *  \ingroup    driver_module
 *  \author     lele.liu <lele.liu@hirain.com>
 *
 *  \version    1.0.0
 *  \date       25/01/2016
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | -------------
 *      01.00.00 |25/01/2016 | lele.liu         | N/A | BootDrv010001
 *
 *****************************************************************************/
#ifndef _BL_WATCHDOG_H_
#define _BL_WATCHDOG_H_
#include "bl_typedefs.h"
#include "dr7f701023_0.h"



/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/
extern void Wdg_Init(void);
extern void Wdg_Feed(void);
extern void Wdg_Deinit(void);
extern void Wdg_FastReset(void);
extern void Wdg_Start(void);

#endif





/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the header file of the timer module for RH850F1H or RH850F1L.
 *
 *  \file       bl_timer.h
 *  \ingroup    driver_module
 *  \author     lele.liu <lele.liu@hirain.com>
 *
 *  \version    1.0.0
 *  \date      25/01/2016
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | -------------
 *      01.00.00 | 25/01/2016 | lele.liu         | N/A | BootDrv010001
 *
 *****************************************************************************/
#ifndef _BL_TIMER_H_
#define _BL_TIMER_H_
#include "bl_typedefs.h"
#include "dr7f701023_0.h"


#define TIMER_DELAY      40000 /* 1ms,counter clock is CPUCLK2 (40MHz) */
#define TIM_TIMER_MAX_COUNT     0xFFFFFFFFUL

/* global variable declaration */
#define RTC_CLK_SXOSC                           0x00u          /*Slow external crystal oscillator*/
#define RTC_CLK_SIRC                           0x01u          /*Slow internal RC oscillator */
#define RTC_CLK_FIRC                          0x02u         /*Fast internal RC oscillator (FIRC)*/



/*function declaration */
extern void Tim_Init(void);  
extern bl_Return_t Tim_IsTimeout(void);
extern void Tim_Deinit(void);

#endif/* TIMER_H */




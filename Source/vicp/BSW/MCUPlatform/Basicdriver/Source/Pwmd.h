/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.		                                              *
*				  All Rights Reserved.          					                                                                  *
*   Department : CT AD     									                                                                  *
*   AUTHOR	   : 									                                                                                  *
************************************************************************
* Object        :  pwmd.h 
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
* 0.1   Aug 18,2016   PEI Jingli  Initial version
*-----------------------------------------------------------------------
* 0.2   Jan 03,2017   PEI Jingli   Changes for codeReview result
*-----------------------------------------------------------------------
* 0.3   Jan 10,2017   PEI Jingli   Add micros
*-----------------------------------------------------------------------
* 0.4   Jan 12,2017  ZhangJie  Fix Coverity warning.
*-----------------------------------------------------------------------
* 0.5   Jan 24,2017  ZhangJie     Remove unused include headfile.
===============================================================*/
#ifndef  _PWMD_H
#define   _PWMD_H
#include "config.h"
#include "cpu.h"

/**** Definition of constants ****/
/* PWGA channels */
#if MCU_PIN ==PIN64
#define PWM_CHANNEL_MAX    24u
#elif MCU_PIN ==PIN80
#define PWM_CHANNEL_MAX    24u
#elif MCU_PIN ==PIN144
#define PWM_CHANNEL_MAX    64u
#elif MCU_PIN ==PIN176
#define PWM_CHANNEL_MAX    72u
#else /*MCU_PIN ==PIN100*/
#define PWM_CHANNEL_MAX    48u
#endif

#define IS_PWMD_CHANNEL(pwm_channel)    ((pwm_channel)<PWM_CHANNEL_MAX)

/**** Definition of types ****/
/* PWBA clock 0~3. */
typedef enum{
    E_PWMCLK0=0,
    E_PWMCLK1,
    E_PWMCLK2,
    E_PWMCLK3,
    E_PWMCLK_MAX
}PWM_CLKTYPE;

/**** Definition of macros ****/
/* ------------------- PORT REGISTERS ----------------- */
/*base address*/
#define  PWBA0_REG_BASEADD        ( (CPU_INT32U )0xFFE72800u)
#define  PWGA0_REG_BASEADD        ( (CPU_INT32U )0xFFE71000u)
#define  PWSA0_REG_BASEADD        ( (CPU_INT32U )0xFFE70000u)

/*register address*/
#define  PWBA0_REG_BRS(m)  (*(CPU_INT16U *)((PWBA0_REG_BASEADD) +  4 *(m))) 
#define  PWBA0_REG_TE          (*(CPU_INT08U *)((PWBA0_REG_BASEADD) + 0x0010u)) 
#define  PWBA0_REG_TS          (*(CPU_INT08U *)((PWBA0_REG_BASEADD) + 0x0014u)) 
#define  PWBA0_REG_TT          (*(CPU_INT08U *)((PWBA0_REG_BASEADD) + 0x0018u)) 
#define  PWBA0_REG_EMU       (*(CPU_INT08U *)((PWBA0_REG_BASEADD) + 0x001Cu)) 
#define  PWGAn_REG_CSDR(n)   (* (CPU_INT16U *)((PWGA0_REG_BASEADD) +  0x40*(n)) )
#define  PWGAn_REG_CRDR(n)   (* (CPU_INT16U *)((PWGA0_REG_BASEADD) +  0x40*(n)+0x0004u) )
#define  PWGAn_REG_CTDR(n)   (* (CPU_INT16U *)((PWGA0_REG_BASEADD) +  0x40*(n)+0x0008u) )
#define  PWGAn_REG_RDT(n)     (* (CPU_INT08U *)((PWGA0_REG_BASEADD) +  0x40*(n)+0x000Cu) )
#define  PWGAn_REG_RSF(n)     (* (CPU_INT08U *)((PWGA0_REG_BASEADD) +  0x40*(n)+0x0010u) )
#define  PWGAn_REG_CNT(n)     (* (CPU_INT16U *)((PWGA0_REG_BASEADD) +  0x40*(n)+0x0014u) )
#define  PWGAn_REG_CTL(n)     (* (CPU_INT08U *)((PWGA0_REG_BASEADD) +  0x40*(n)+0x0020u) )

#define  PWGAn_REG_CSBR(n)     (* (CPU_INT16U *)((PWGA0_REG_BASEADD) +  0x40*(n)+0x0024u) )
#define  PWGAn_REG_CRBR(n)     (* (CPU_INT16U *)((PWGA0_REG_BASEADD) +  0x40*(n)+0x0028u) )
#define  PWGAn_REG_CTBR(n)     (* (CPU_INT16U *)((PWGA0_REG_BASEADD) +  0x40*(n)+0x002Cu) )
#define  PWGAn_REG_SLPWGA(k)   (* (CPU_INT32U *)(0xFFBC1000u +  4*(k)) )

#define  PWSA0_REG_CTL          (*(CPU_REG08 *)(PWSA0_REG_BASEADD)) 
#define  PWSA0_REG_STR          (*(CPU_REG08 *)((PWSA0_REG_BASEADD) + 0x0004u)) 
#define  PWSA0_REG_STC          (*(CPU_REG08 *)((PWSA0_REG_BASEADD) + 0x0008u)) 
#define  PWSA0_REG_QUE(j)          (*(CPU_REG08 *)((PWSA0_REG_BASEADD) + 0x0020u +4*(j))) /* 0~7*/
#define  PWSA0_REG_PVCRx_y(x)  (*(CPU_REG32 *)((PWSA0_REG_BASEADD) + 0x0040u +2*(x))) /*x even 0~70,y=x+1*/
#define  PWSA0_REG_EMU         (*(CPU_REG16 *)((PWSA0_REG_BASEADD) + 0x000Cu)) 

/**** Definition of variables ****/


#endif/*_PWMD_H */


/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.		           *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									                   *
************************************************************************
* Object        :  PWMD_cfg.c 
* Module        : 
* Instance      : 
* Description   : MAX PWM FREQUENCY is 9765HZ when IPERI2 be 40Mhz
*-----------------------------------------------------------------------
* Version: 
* Date: 
* Author: 
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
* ----------------------------------------------------------------------
* 0.1  Apr 15,2016     Pei JL     Initial version
* ----------------------------------------------------------------------
* 0.2  Dec 29,2016    Pei Jingli  Add include files
* ----------------------------------------------------------------------
* 0.3   Jan 03,2017   PEI Jingli   Changes for codeReview result
*-----------------------------------------------------------------------
* 0.4   Jan 24,2017   ZhangJie   Fix Coverity warnings.
===============================================================*/

/*============================================================================
* Includes
============================================================================*/
#include "define.h"
#include "Pwmd_cfg.h"


/* PWMCLKm configration, m is 0~3
*  PCLK of PWM is CKSCLK_IPERI2, frequency is PERI2_CLKDOMAIN_HZ
*  PWMCLKm frequency=PERI2_CLKDOMAIN_HZ/(2* pwmClocKCfg[n] ), pwmClocKCfg[n] is 0 to 2047(2^11-1).
*   if PERI2_CLKDOMAIN_HZ=40Mhz and pwmClocKCfg[n]=0, then PWMCLKm fre=40Mhz
*                                                    and pwmClocKCfg[n]=2047, then PWMCLKm fre=(40M/4094)hz
*/
const U16 pwmClocKCfg[E_PWMCLK_MAX]=
{
    8,    /*PWMCLK0*/
    1024, /*PWMCLK1*/
    1024, /*PWMCLK2*/
    1024  /*PWMCLK3*/
};

/* select a PWMCLKm for all channels, pwmChannelClocK[] value is E_PWMCLK0 t0 E_PWMCLK3
* default is E_PWMCLK0
* pwm channel clock frequency = PWMCLKm frequency
* pwm wave frequency of a channel = PWMCLKm frequency/(0xFFF+1). Also used PWMD_GetFrequency()
*/
const PWM_CLKTYPE pwmChannelClocK[PWM_CHANNEL_MAX]=
{
    E_PWMCLK0,E_PWMCLK1,E_PWMCLK2,E_PWMCLK3,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,  /* 0~7*/
    E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,  /* 8~15*/
    E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,  /* 16~23*/
#if  MCU_PIN >=PIN100
    E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,  /* 24~31*/
    E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,  /* 32~39*/
    E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,  /* 40~47*/
#endif
#if MCU_PIN>=PIN144
   E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,  /* 48~55*/
   E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,  /* 56~63*/
   E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,E_PWMCLK0,  /* 64~71*/
#endif
};


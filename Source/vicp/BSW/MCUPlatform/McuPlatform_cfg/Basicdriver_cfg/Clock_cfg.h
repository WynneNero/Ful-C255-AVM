/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department :  CT AD NKG 
************************************************************************
* Object        :        Clock_cfg.h
* Module        :
* Instance      :
* Description  : Configration of Clock sources and domains related.
***********************************************************************/
/*-History--------------------------------------------------------------
* Ver    Date           Name        Changes and comment
* ----------------------------------------------------------------------
* 0.1  Nov 17,2016  PEI Jingli  Initial version
* ----------------------------------------------------------------------
* 0.2  Nov 25,2016  PEI Jingli  Code architecture for code review
* ----------------------------------------------------------------------
* 0.3  Jan 24,2017  ShangQiuju  Fix Coverity warnings.
*=====================================================================*/

#ifndef _CLOCK_CFG_H_
#define _CLOCK_CFG_H_ 

/**** Definition of constants ****/
/******************************************************************************
 *                                            CPU clock                
 *
 ******************************************************************************/
/* CPU clock used external OSC .The clock works in run mode
* How to genarate CPU clock
* Process: external OSC->PLL CLK(CPLL same as PPLL clk) to 1 divider -> CPU clock
* Equation:CPU clock=external OSC X(Nr/Mr)x(1/Par)
* e.g external OSC,   CPU clock,  PLLC_Nr, PLLC_Mr,  PLLC_Par
*       16mhz              80mhz        40            2,             4 
*         8mhz              80mhz        40            1,             4 
*       20mhz              80mhz        32            2,             4 
*       24mhz              80mhz        40            2,             4 
*    11.0592mhz     80.1792mhz  29            1,             4 
*/
#define  CPUCLK_NORMAL_HZ    (80000000u)/*CPU clock:80MHZ*/
#define  EXTERNAL_OSC_HZ        (16000000u)  /*external OSC:16MHZ  for MOSC*/
/*PLLC_Nr:val= 1~64*/
#define  EXTERNAL_PLLCCLK_NR   (40)
/* PLLC_Mr:val=1,2,3  8mhz<=ext OSC<=24mhz ->Mr=1, 16mhz<=ext OSC<=24mhz ->Mr=2,  ext OSC=24mhz ->Mr=3*/
#define  EXTERNAL_PLLCCLK_MR   (2) 
/*PLLC_Par:val=4,6,8,16   60<=CPU<=80mhz ->Par=4, 40<=CPU<=80mhz ->Par=6, 30<=CPU<=60mhz ->Par=8, 25<=CPU<=30mhz ->Par=16*/
#define  EXTERNAL_PLLCCLK_PAR  (4)
/*Define PERI1 and PERI2 as CPUCLK2 in mcu run mode. Can not be changed */
#define  PERI1_CLKDOMAIN_HZ   (CPUCLK_NORMAL_HZ/2)
#define  PERI2_CLKDOMAIN_HZ   (CPUCLK_NORMAL_HZ/2)


/* CPU clock used HSI clock */
#define  CPUCLK_BY_HSI_HZ  (8000000u)  /*CPU clock:8MHZ, be 1,2,4 or 8 dividing of HSI */
#define  HSI_OSC_HZ               (8000000u)  /*Internal high-speed internal clock:8MHZ, A const value*/

/* CPU clock used LSI  clock */
#define  CPUCLK_BY_LSI_HZ  (240000u)   /*CPU clock:240KHZ cpu clock ,<=LSI*/
#define  LSI_OSC_HZ               (240000u)   /*Internal low-speed internal clock:240KHZ, A const value*/


/**** Declaration of functions ****/

#endif /*_CLOCK_CFG_H_*/

/****************************** END OF FILE ***************************/


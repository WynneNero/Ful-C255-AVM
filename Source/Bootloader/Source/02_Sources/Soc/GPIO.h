/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.		       
*				  All Rights Reserved.                 
*   Department :  CT AD NKG      				     
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   : Functions in General Port Mode
***********************************************************************/
/*-History--------------------------------------------------------------
* Version  Date   	 Name        Changes and comments
------------------------------------------------------------------------
* 0.1	   Apr 28,2016   PEI Jingli  Initial version
------------------------------------------------------------------------
* 0.2	   Jun 29,2016   LIU Chenxi  Correct errors during merging	
------------------------------------------------------------------------
* 0.3	   July 07,2016  PEI Jingli  Adapt 64pin MCU
* ----------------------------------------------------------------------
* 0.4      July 07,2016  LIU Chenxi  Refine code structure
* ----------------------------------------------------------------------
* 0.5      July 21,2016  PEI Jingli  Refine code structure, move macro
           definitions to GPIO_IF.h
* ----------------------------------------------------------------------
* 0.6      Aug  01,2016  PEI Jingli  Add APORT,JPORT register address   
*=====================================================================*/


//============================================================================
// Includes
//============================================================================
#ifndef   _GPIO_H
#define   _GPIO_H

#include <config.h>

/**** Definition of contanst ****/
/**** Definition of macros ****/

#define assert_param(expr) ((void)0)
/* ------------------- PORT REGISTERS ----------------- */
#define  PORT_REG_BASEADD        ( (CPU_INT32U )0xFFC10000u)  //port reg base address
#define  JPORT0_REG_BASEADD      ( (CPU_INT32U )0xFFC20000u)

//Pin Function cfg address
#define  PORT_REG_PM(n)        (*(CPU_REG16 *)(PORT_REG_BASEADD + 0x0300 + 4 *(n))) //I/O mode
#define  PORT_REG_PMC(n)       (*( CPU_REG16*)(PORT_REG_BASEADD + 0x0400 + 4 *(n))) //
#define  PORT_REG_PMSR(n)      (*(CPU_REG32 *)(PORT_REG_BASEADD + 0x0800 + 4 *(n))) //PM set/reset reg
#define  PORT_REG_PMCSR(n)     (*(CPU_REG32 *)(PORT_REG_BASEADD + 0x0900 + 4 *(n))) //PMC set/reset reg
#define  PORT_REG_PIPC(n)      (*(CPU_REG16 *)(PORT_REG_BASEADD + 0x4200 + 4 *(n))) //direct or SW I/O control
#define  PORT_REG_PIBC(n)      (*(CPU_REG16 *)(PORT_REG_BASEADD + 0x4000 + 4 *(n))) //enable input buffer
#define  PORT_REG_PFC(n)       (*(CPU_REG16 *)(PORT_REG_BASEADD + 0x0500 + 4 *(n))) //specify alternative function
#define  PORT_REG_PFCE(n)      (*(CPU_REG16 *)(PORT_REG_BASEADD + 0x0600 + 4 *(n)))
#define  PORT_REG_PFCAE(n)     (*(CPU_REG16 *)(PORT_REG_BASEADD + 0x0A00 + 4 *(n)))

//Electrical chara. address
#define  PORT_REG_PU(n)        (*(CPU_REG16 *)(PORT_REG_BASEADD + 0x4300 + 4 *(n))) //pull-up input
#define  PORT_REG_PD(n)        (*(CPU_REG16 *)(PORT_REG_BASEADD + 0x4400 + 4 *(n))) //pull-down input
#define  PORT_REG_PODC(n)      (*(CPU_REG32 *)(PORT_REG_BASEADD + 0x4500 + 4 *(n))) //open-drain output
#define  PORT_REG_PDSC(n)      (*(CPU_REG32 *)(PORT_REG_BASEADD + 0x4600 + 4 *(n))) //speed
#define  PORT_REG_PIS(n)       (*(CPU_REG16 *)(PORT_REG_BASEADD + 0x4700 + 4 *(n))) //select input buffer
#define  PORT_REG_PISE(n)            (*(CPU_REG16 *)(PORT_REG_BASEADD + 0x4800 + 4 *(n))) //del

//Data In/Out address
#define  PORT_REG_PBDC(n)      (*(CPU_REG16 *)(PORT_REG_BASEADD + 0x4100 + 4 *(n))) //bi-direction cfg
#define  PORT_REG_PPR(n)       (*(CPU_REG16 *)(PORT_REG_BASEADD + 0x0200 + 4 *(n))) //port pin read
#define  PORT_REG_P(n)         (*(CPU_REG16 *)(PORT_REG_BASEADD + 0x0000 + 4 *(n))) //to output 
#define  PORT_REG_PNOT(n)      (*(CPU_REG16 *)(PORT_REG_BASEADD + 0x0700 + 4 *(n))) //invert reg of P REG
#define  PORT_REG_PSR(n)       (*(CPU_REG32 *)(PORT_REG_BASEADD + 0x0100 + 4 *(n))) //set/reset reg of P REG

/* JTAG register address */
#define  JPORT_REG_JPMC0         (*( CPU_REG16*)(JPORT0_REG_BASEADD + 0x0040))
#define  JPORT_REG_JPM0          (*( CPU_REG16*)(JPORT0_REG_BASEADD + 0x0030))
#define  JPORT_REG_JPIBC0          (*( CPU_REG16*)(JPORT0_REG_BASEADD + 0x0400))
#define  JPORT_REG_JPFC0          (*( CPU_REG16*)(JPORT0_REG_BASEADD + 0x0050))
#define  JPORT_REG_JPBDC0          (*( CPU_REG16*)(JPORT0_REG_BASEADD + 0x0410))
#define  JPORT_REG_JPU0          (*( CPU_REG16*)(JPORT0_REG_BASEADD + 0x0430))
#define  JPORT_REG_JPD0          (*( CPU_REG16*)(JPORT0_REG_BASEADD + 0x0440))
#define  JPORT_REG_JPODC0     (*( CPU_REG16*)(JPORT0_REG_BASEADD + 0x0450))
#define  JPORT_REG_JPMC(n)         (*(CPU_REG16 *)(JPORT_REG_JPMC0 + 4 *n))
#define  JPORT_REG_JPM(n)          (*(CPU_REG16 *)(JPORT_REG_JPM0 + 4 *n))
#define  JPORT_REG_JPIBC(n)        (*(CPU_REG16 *)(JPORT_REG_JPIBC0 + 4 *n))
#define  JPORT_REG_JPFC(n)         (*(CPU_REG16 *)(JPORT_REG_JPFC0 + 4 *n))
#define  JPORT_REG_JPBDC(n)        (*(CPU_REG16 *)(JPORT_REG_JPBDC0 + 4 *n))
#define  JPORT_REG_JPU(n)          (*(CPU_REG16 *)(JPORT_REG_JPU0 + 4 *n))
#define  JPORT_REG_JPD(n)          (*(CPU_REG16 *)(JPORT_REG_JPD0 + 4 *n))
#define  JPORT_REG_JPODC(n)        (*(CPU_REG16 *)(JPORT_REG_JPODC0 + 4 *n))
#define  JPORT_REG_P(n)            (*(CPU_REG16 *)(JPORT0_REG_BASEADD + 4 *n))
#define  JPORT_REG_PPR(n)          (*(CPU_REG16 *)(JPORT0_REG_BASEADD + 0X0020 + 4 *n))

/* Anolog Port Register */
#define  APORT_REG_APM(n)      (*(CPU_REG16 *)(PORT_REG_BASEADD + 0x03C8 + 4 *(n))) 
#define  APORT_REG_APIBC(n)   (*(CPU_REG16 *)(PORT_REG_BASEADD + 0x40C8 + 4 *(n))) 
#define  APORT_REG_APBDC(n)  (*(CPU_REG16 *)(PORT_REG_BASEADD + 0x41C8 + 4 *(n)))
#define  APORT_REG_P(n)       (*(CPU_REG16 *)(PORT_REG_BASEADD + 0x00C8 + 4 *(n)))
#define  APORT_REG_PPR(n)     (*(CPU_REG16 *)(PORT_REG_BASEADD + 0x02C8 + 4 *(n)))
 
//filter control reg addr
#define  PORT_REG_FCLA0CTL_NMI        ((CPU_REG08 *)(0xFFC34000))   //NMI
#define  PORT_REG_FCLA0CTL_INTP0    ((CPU_REG08 *)(0xFFC34020))
#define  PORT_REG_FCLA0CTL_INTP(n)  ((CPU_REG08 *)(PORT_REG_FCLA0CTL_INTP0+4*(n))) //INT

#endif
/*_GPIO_H*/

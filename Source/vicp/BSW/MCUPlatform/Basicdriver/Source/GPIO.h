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
                                     and correct error  
------------------------------------------------------------------------
* 0.7	 Dec 02,2016  PEI Jingli  Modify for code-review result
------------------------------------------------------------------------
* 0.8	 Dec 22,2016  PEI Jingli  Chang JPORT register address definition
------------------------------------------------------------------------
* 0.9	 Jan  05,2017  PEI Jingli  Chang JTAG0 register address definition
*----------------------------------------------------------------------
* 1.0	 Jan 13,2017    ZhangJie       Add u for constant value to avoid Coverity warning.
*-----------------------------------------------------------------------
* 1.1        Jan 24,2017   ZhangJie   Remove unused include file.
------------------------------------------------------------------------
* 1.2	Apr 01,2017  PEI Jingli  Fix headfile included.
*=====================================================================*/
#ifndef   _GPIO_H
#define   _GPIO_H
#include "Config.h"
#include "Cpu.h"

/**** Definition of contanst ****/
/**** Definition of macros ****/

/* ------------------- PORT REGISTERS ----------------- */
#define  PORT_REG_BASEADD        ( (CPU_INT32U )0xFFC10000u)  /*port reg base address*/
#define  JPORT0_REG_BASEADD      ( (CPU_INT32U )0xFFC20000u)

/*Pin Function cfg address*/
#define  PORT_REG_PM(n)        (*(CPU_REG16 *)((PORT_REG_BASEADD) + 0x0300u + (4u *(n)))) /*I/O mode*/
#define  PORT_REG_PMC(n)       (*( CPU_REG16*)((PORT_REG_BASEADD) + 0x0400u + (4u *(n)))) 
#define  PORT_REG_PMSR(n)      (*(CPU_REG32 *)((PORT_REG_BASEADD) + 0x0800u + (4u *(n)))) /*PM set/reset reg*/
#define  PORT_REG_PMCSR(n)     (*(CPU_REG32 *)((PORT_REG_BASEADD) + 0x0900u + (4u *(n)))) /*PMC set/reset reg*/
#define  PORT_REG_PIPC(n)      (*(CPU_REG16 *)((PORT_REG_BASEADD) + 0x4200u + (4u *(n)))) /*direct or SW I/O control*/
#define  PORT_REG_PIBC(n)      (*(CPU_REG16 *)((PORT_REG_BASEADD) + 0x4000u + (4u *(n)))) /*enable input buffer*/
#define  PORT_REG_PFC(n)       (*(CPU_REG16 *)((PORT_REG_BASEADD) + 0x0500u + (4u *(n)))) /*specify alternative function*/
#define  PORT_REG_PFCE(n)      (*(CPU_REG16 *)((PORT_REG_BASEADD) + 0x0600u + (4u *(n))))
#define  PORT_REG_PFCAE(n)     (*(CPU_REG16 *)((PORT_REG_BASEADD) + 0x0A00u + (4u *(n))))

/*Electrical chara. address*/
#define  PORT_REG_PU(n)        (*(CPU_REG16 *)((PORT_REG_BASEADD) + 0x4300u + (4u *(n)))) /*pull-up input*/
#define  PORT_REG_PD(n)        (*(CPU_REG16 *)((PORT_REG_BASEADD) + 0x4400u + (4u *(n)))) /*pull-down input*/
#define  PORT_REG_PODC(n)      (*(CPU_REG32 *)((PORT_REG_BASEADD) + 0x4500u + (4u *(n)))) /*open-drain output*/
#define  PORT_REG_PDSC(n)      (*(CPU_REG32 *)((PORT_REG_BASEADD) + 0x4600u + (4u *(n)))) /*speed*/
#define  PORT_REG_PIS(n)       (*(CPU_REG16 *)((PORT_REG_BASEADD) + 0x4700u + (4u *(n)))) /*select input buffer*/
#define  PORT_REG_PISE(n)            (*(CPU_REG16 *)((PORT_REG_BASEADD) + 0x4800u + (4u *(n)))) /*del*/

/*Data In/Out address*/
#define  PORT_REG_PBDC(n)      (*(CPU_REG16 *)((PORT_REG_BASEADD) + 0x4100u + (4u *(n)))) /*bi-direction cfg*/
#define  PORT_REG_PPR(n)       (*(CPU_REG16 *)((PORT_REG_BASEADD) + 0x0200u + (4u *(n)))) /*port pin read*/
#define  PORT_REG_P(n)         (*(CPU_REG16 *)((PORT_REG_BASEADD) + 0x0000u + (4u *(n)))) /*to output */
#define  PORT_REG_PNOT(n)      (*(CPU_REG16 *)((PORT_REG_BASEADD) + 0x0700u + (4u *(n)))) /*invert reg of P REG*/
#define  PORT_REG_PSR(n)       (*(CPU_REG32 *)((PORT_REG_BASEADD) + 0x0100u + (4u *(n)))) /*set/reset reg of P REG*/

/* JTAG0 register address */
#define  JPORT_REG_JPMC0         (*( CPU_REG08*)((JPORT0_REG_BASEADD) + 0x0040u))
#define  JPORT_REG_JPM0          (*( CPU_REG08*)((JPORT0_REG_BASEADD) + 0x0030u))
#define  JPORT_REG_JPIBC0          (*( CPU_REG08*)((JPORT0_REG_BASEADD) + 0x0400u))
#define  JPORT_REG_JPFC0          (*( CPU_REG08*)((JPORT0_REG_BASEADD) + 0x0050u)) 
#define  JPORT_REG_JPBDC0          (*( CPU_REG08*)((JPORT0_REG_BASEADD) + 0x0410u))
#define  JPORT_REG_JPU0          (*( CPU_REG08*)((JPORT0_REG_BASEADD) + 0x0430u))
#define  JPORT_REG_JPD0          (*( CPU_REG08*)((JPORT0_REG_BASEADD) + 0x0440u))
#define  JPORT_REG_JPODC0        (*( CPU_REG32*)((JPORT0_REG_BASEADD) + 0x0450u))
#define  JPORT_REG_JP0            (*( CPU_REG32*)(JPORT0_REG_BASEADD))
#define  JPORT_REG_JPPR0           (*(CPU_REG08 *)((JPORT0_REG_BASEADD) +0x0020u))
#define  JPORT_REG_JPMC(n)         (*(CPU_REG08 *)((JPORT0_REG_BASEADD) + 0x0040u))  /*only jport0 of F1L and F1K*/
#define  JPORT_REG_JPM(n)           (*(CPU_REG08 *)((JPORT0_REG_BASEADD) + 0x0030u))
#define  JPORT_REG_JPIBC(n)        (*(CPU_REG08 *)((JPORT0_REG_BASEADD) + 0x0400u))
#define  JPORT_REG_JPFC(n)         (*(CPU_REG08 *)((JPORT0_REG_BASEADD) + 0x0050u))
#define  JPORT_REG_JPBDC(n)       (*(CPU_REG08 *)((JPORT0_REG_BASEADD) + 0x0410u))
#define  JPORT_REG_JPU(n)           (*(CPU_REG08 *)((JPORT0_REG_BASEADD) + 0x0430u))
#define  JPORT_REG_JPD(n)           (*(CPU_REG08 *)((JPORT0_REG_BASEADD) + 0x0440u))
#define  JPORT_REG_JPODC(n)       (*(CPU_REG32 *)((JPORT0_REG_BASEADD) + 0x0450u))
#define  JPORT_REG_P(n)               (*(CPU_REG08 *)(JPORT0_REG_BASEADD))
#define  JPORT_REG_PPR(n)           (*(CPU_REG08 *)((JPORT0_REG_BASEADD) +0x0020u))


/* Anolog Port Register */
#define  APORT_REG_APM(n)      (*(CPU_REG16 *)((PORT_REG_BASEADD) + 0x03C8u + (4u *(n))))
#define  APORT_REG_APIBC(n)   (*(CPU_REG16 *)((PORT_REG_BASEADD) + 0x40C8u + (4u *(n)))) 
#define  APORT_REG_APBDC(n)  (*(CPU_REG16 *)((PORT_REG_BASEADD) + 0x41C8u + (4u *(n))))
#define  APORT_REG_P(n)       (*(CPU_REG16 *)((PORT_REG_BASEADD) + 0x00C8u + (4u *(n))))
#define  APORT_REG_PPR(n)     (*(CPU_REG16 *)((PORT_REG_BASEADD) + 0x02C8u + (4u *(n))))
 
/*filter control reg addr*/
#define  PORT_REG_FCLA0CTL_NMI        ((CPU_REG08 *)(0xFFC34000u))   /*NMI*/
#define  PORT_REG_FCLA0CTL_INTP0    ((CPU_REG08 *)(0xFFC34020u))
#define  PORT_REG_FCLA0CTL_INTP(n)  ((CPU_REG08 *)((PORT_REG_FCLA0CTL_INTP0)+(4u*(n)))) /*INT*/

#if MCU_PIN ==PIN100
#define IS_VALID_PORT(port)    ( (port==GPIO_PORT_0)   \
                            ||(port>=GPIO_PORT_8)&&(port<=GPIO_PORT_11)   \
                            ||(port==AP_PORT_0)  \
                            ||(port==JP_PORT_0))

#elif (MCU_PIN ==PIN64)
#define IS_VALID_PORT(port)    ( (port==GPIO_PORT_0)   \
                            ||(port>=GPIO_PORT_8)&&(port<=GPIO_PORT_10)   \
                            ||(port==AP_PORT_0)  \
                            ||(port==JP_PORT_0))

#else
#define IS_VALID_PORT(port)  (port<GPIO_PORT_NUM)
#endif

#endif
/*_GPIO_H*/

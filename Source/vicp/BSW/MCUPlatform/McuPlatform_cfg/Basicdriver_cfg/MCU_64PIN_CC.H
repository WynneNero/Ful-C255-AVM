/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   : Shao Guangxian										   *
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
* Version       Date    Name    Changes and comment__DSB__DSBs
------------------------------------------------------------------------
* 0.1	   July 07,2016  PEI Jingli  Adapt 64pin MCU  
------------------------------------------------------------------------
* 0.2	   Aug  10,2016  PEI Jingli  Add descriptions and PFCE10 definition  
------------------------------------------------------------------------
* 0.3	   Dec  22,2016  PEI Jingli  Add PORT register and PFCE10 definition 
                                                    Add adc.h file for complie error.
*----------------------------------------------------------------------
* 0.4      Dec 23,2016  PEI Jingli  Delete adc channel micro and head file
*----------------------------------------------------------------------
* 0.5      Dec 29,2016  PEI Jingli  Delete head file
*------------------------------------------------------------------------
* 0.6      Jan 24,2017  ZhangJie  Fix Coverity warning.
*------------------------------------------------------------------------
*0.7       Feb 15,2017  PEI Jingli  Delete include and #if MCU_PIN
*------------------------------------------------------------------------
*0.8       Apr 13,2017  PEI Jingli  Set high impedance IO as default
*=====================================================================*/
#ifndef _PIN_MAP_CC_H
#define _PIN_MAP_CC_H

/*--------------------configration method----------------------
* 1. independent IO
    PMC:bit=0 -> PM
                         1:input  -> PIBC set 1,PU,PD
                 
                         0:output->PBDC,PDSC,PODC
*2. alternative mode
   PMC:bit=1 ->PIPC
                         0   -> PFC,PFCE,PFCAE
                              ->PM
                                  1: input   -> same as 1.PBDC
                                  0:output-> same as 1.PBDC
                                   
                         1  ->PFC,PFCE,PFCAE
                              PIBC,PU,PD
                              PBDC,PDSC,PODC
                       (directIO chapter2.11)
*---------------------------------------------------------*/
/*-- MCU_RH850_F1L:  PORT 0,8,9,10,JP0,AP0   --*/
#define MCU_PORT_NUM       4u
#define MCU_APORT_NUM     1u
#define MCU_JPORT_NUM     1u


/* PMC: 0=port mode 1=alternative */
#define GPIO_PMC0_ACTIVE_VAL         0x0000u   
#define GPIO_PMC8_ACTIVE_VAL         0x0000u   
#define GPIO_PMC9_ACTIVE_VAL         0x0000u 
#define GPIO_PMC10_ACTIVE_VAL       0x0000u 
#define GPIO_JPMC0_ACTIVE_VAL       0x0000u
/*no Anolog*/
#define GPIO_REG_NONE_VAL      0x0000u  /*none register*/

/* Port IP Control: IN alternative mode, mask PM.  1=unuse PM */
#define GPIO_PIPC0_ACTIVE_VAL      0x0000u 
#define GPIO_PIPC8_ACTIVE_VAL      0x0000u
#define GPIO_PIPC9_ACTIVE_VAL      0x0000u
#define GPIO_PIPC10_ACTIVE_VAL    0x0000u
/*no Jtag*/
/*no Anolog*/

/* PM: 0=output 1=input */
#define GPIO_PM0_ACTIVE_VAL         0xFFFFu
#define GPIO_PM8_ACTIVE_VAL         0xFFFFu
#define GPIO_PM9_ACTIVE_VAL         0xFFFFu
#define GPIO_PM10_ACTIVE_VAL        0xFFFFu
#define GPIO_JPM0_ACTIVE_VAL       0xFFFFu
#define GPIO_APM0_ACTIVE_VAL       0xFFFFu

/* Port InputBuffer Control: all 1 in port mode */
#define GPIO_PIBC0_ACTIVE_VAL      0x0000u    
#define GPIO_PIBC8_ACTIVE_VAL      0x0000u
#define GPIO_PIBC9_ACTIVE_VAL      0x0000u
#define GPIO_PIBC10_ACTIVE_VAL    0x0000u
#define GPIO_APIBC0_ACTIVE_VAL    0x0000u
#define GPIO_JPIBC0_ACTIVE_VAL    0x0000u

/* PFCAE,PFCE,PFC:IN alternative mode, select a alternative function in 0~4.
*  binary value [PFCAEn_m,PFCEn_m,PFCn_m]b  from 0~4  is a alternative function.
* PFC port:0,1,8,9,10,11,12,18,20
* PFCE port:0,8,9,10,11,12   PFCE port:0,10,11
*/
#define GPIO_PFC0_ACTIVE_VAL       0x0000u
#define GPIO_PFCE0_ACTIVE_VAL     0x0000u   
#define GPIO_PFCAE0_ACTIVE_VAL   0x0000u    

#define GPIO_PFC8_ACTIVE_VAL       0x0000u
#define GPIO_PFCE8_ACTIVE_VAL     0x0000u   
#define GPIO_PFCAE8_ACTIVE_VAL   0x0000u  

#define GPIO_PFC9_ACTIVE_VAL        0x0000u
#define GPIO_PFCE9_ACTIVE_VAL      0x0000u  
#define GPIO_PFCAE9_ACTIVE_VAL    0x0000u    

#define GPIO_PFC10_ACTIVE_VAL     0x0000u
#define GPIO_PFCE10_ACTIVE_VAL      0x0000u   
#define GPIO_PFCAE10_ACTIVE_VAL     0x0000u   
/*no PFCE10*/
/*no PFCAE10*/

#define GPIO_JPFC0_ACTIVE_VAL      0x0000u
#define GPIO_JPFCE0_ACTIVE_VAL    0x0000u   
#define GPIO_JPFCAE0_ACTIVE_VAL  0x0000u    
/*no Anolog*/


/* Port Bidirection Control: 1= Bidirection */
#define GPIO_PBDC0_ACTIVE_VAL      0x0000u
#define GPIO_PBDC8_ACTIVE_VAL      0x0000u
#define GPIO_PBDC9_ACTIVE_VAL      0x0000u
#define GPIO_PBDC10_ACTIVE_VAL    0x0000u
#define GPIO_APBDC0_ACTIVE_VAL    0x0000u
#define GPIO_JPBDC0_ACTIVE_VAL    0x0000u

/* PullUp Control: input mode.  1= internal pullup.
* Care that PUn.PUn_m=1 and PDn.PDn_m=1, then the real Pin is pulldown
*/
#define GPIO_PU0_ACTIVE_VAL      0x0000u    
#define GPIO_PU8_ACTIVE_VAL      0x0000u
#define GPIO_PU9_ACTIVE_VAL      0x0000u
#define GPIO_PU10_ACTIVE_VAL    0x0000u
#define GPIO_JPU0_ACTIVE_VAL    0x0000u
/*no Anolog*/

/* PullUp Control: input mode.  1= internal pulldown */
#define GPIO_PD0_ACTIVE_VAL      0x0000u    
#define GPIO_PD8_ACTIVE_VAL      0x0000u
#define GPIO_PD9_ACTIVE_VAL      0x0000u
#define GPIO_PD10_ACTIVE_VAL    0x0000u
#define GPIO_JPD0_ACTIVE_VAL    0x0000u
//no Anolog

/* Port Driver Strength: output mode. 0:<=10mhz, 1:<=40mhz
* 40MHZ pin select:P0_2,3,5,6,7,13,14  ; P10_ALL
*/
#define GPIO_PDSC0_ACTIVE_VAL      0x0000u    
#define GPIO_PDSC8_ACTIVE_VAL      0x0000u
#define GPIO_PDSC9_ACTIVE_VAL      0x0000u
#define GPIO_PDSC10_ACTIVE_VAL    0x0000u
/*no Jtag*/
/*no Anolog*/

/* Port open drain control: output mode. 0:push-pull, 1:open-drain*/
#define GPIO_PODC0_ACTIVE_VAL      0x0000u   
#define GPIO_PODC8_ACTIVE_VAL      0x0000u  
#define GPIO_PODC9_ACTIVE_VAL      0x0000u
#define GPIO_PODC10_ACTIVE_VAL    0x0000u
#define GPIO_JPODC0_ACTIVE_VAL    0x0000u
/*no Anolog*/

/* Set default for output pin */
#define GPIO_P0_ACTIVE_VAL        0x0000u
#define GPIO_P8_ACTIVE_VAL        0x0000u
#define GPIO_P9_ACTIVE_VAL        0x0000u
#define GPIO_P10_ACTIVE_VAL      0x0000u
#define GPIO_JP0_ACTIVE_VAL      0x0000u
#define GPIO_AP0_ACTIVE_VAL      0x0000u


/*----------------------- GPIO RESET ---------------------------- */
/* PMC: 0=port mode 1=alternative */
#define GPIO_PMC0_RESET_VAL         0x0000u
#define GPIO_PMC8_RESET_VAL         0x0000u
#define GPIO_PMC9_RESET_VAL         0x0000u 
#define GPIO_PMC10_RESET_VAL       0x0000u
#define GPIO_JPMC0_RESET_VAL       0x0000u
//no Anolog
#define GPIO_REG_NONE_VAL      0x0000u  /*none register*/

/* Port IP Control: IN alternative mode, mask PM.  1=unuse PM */
#define GPIO_PIPC0_RESET_VAL      0x0000u
#define GPIO_PIPC8_RESET_VAL      0x0000u
#define GPIO_PIPC9_RESET_VAL      0x0000u
#define GPIO_PIPC10_RESET_VAL    0x0000u
//no Jtag
//no Anolog

/* PM: 0=output 1=input */
#define GPIO_PM0_RESET_VAL         0xFFFFu
#define GPIO_PM8_RESET_VAL         0xFFFFu
#define GPIO_PM9_RESET_VAL         0xFFFFu  
#define GPIO_PM10_RESET_VAL       0xFFFFu
#define GPIO_JPM0_RESET_VAL       0xFFFFu
#define GPIO_APM0_RESET_VAL      0xFFFFu

/* Port InputBuffer Control: all 0,unused here */
#define GPIO_PIBC0_RESET_VAL      0x0000u    
#define GPIO_PIBC8_RESET_VAL      0x0000u
#define GPIO_PIBC9_RESET_VAL      0x0000u
#define GPIO_PIBC10_RESET_VAL    0x0000u
#define GPIO_APIBC0_RESET_VAL    0x0000u
#define GPIO_JPIBC0_RESET_VAL    0x0000u

/* PFCAE,PFCE,PFC:IN alternative mode, select a alternative function in 0~4.
*  binary value [PFCAEn_m,PFCEn_m,PFCn_m]b  from 0~4  is a alternative function.
* PFC port:0,1,8,9,10,11,12,18,20
* PFCE port:0,8,9,10,11,12   PFCE port:0,10,11
*/
#define GPIO_PFC0_RESET_VAL       0x0000u
#define GPIO_PFCE0_RESET_VAL     0x0000u   
#define GPIO_PFCAE0_RESET_VAL   0x0000u    

#define GPIO_PFC8_RESET_VAL      0x0000u
#define GPIO_PFCE8_RESET_VAL      0x0000u 
#define GPIO_PFCAE8_RESET_VAL      0x0000u  

#define GPIO_PFC9_RESET_VAL        0x0000u
#define GPIO_PFCE9_RESET_VAL      0x0000u 
#define GPIO_PFCAE9_RESET_VAL    0x0000u    

#define GPIO_PFC10_RESET_VAL    0x0000u
#define GPIO_PFCE10_RESET_VAL   0x0000u
#define GPIO_PFCAE10_RESET_VAL 0x0000u
/*no PFCE10*/
/*no PFCAE10*/

#define GPIO_JPFC0_RESET_VAL     0x0000u
#define GPIO_JPFCE0_RESET_VAL   0x0000u   
#define GPIO_JPFCAE0_RESET_VAL 0x0000u    
/*no Anolog*/


/* Port Bidirection Control: 1= Bidirection */
#define GPIO_PBDC0_RESET_VAL      0x0000u 
#define GPIO_PBDC8_RESET_VAL      0x0000u
#define GPIO_PBDC9_RESET_VAL      0x0000u
#define GPIO_PBDC10_RESET_VAL    0x0000u
#define GPIO_APBDC0_RESET_VAL    0x0000u
#define GPIO_JPBDC0_RESET_VAL    0x0000u

/* PullUp Control: input mode.  1= internal pullup.
* Care that PUn.PUn_m=1 and PDn.PDn_m=1, then the real Pin is pulldown
*/
#define GPIO_PU0_RESET_VAL      0x0000u    
#define GPIO_PU8_RESET_VAL      0x0000u
#define GPIO_PU9_RESET_VAL      0x0000u
#define GPIO_PU10_RESET_VAL    0x0000u
#define GPIO_JPU0_RESET_VAL    0x0000u
/*no Anolog*/

/* PullUp Control: input mode.  1= internal pulldown */
#define GPIO_PD0_RESET_VAL      0x0000u    
#define GPIO_PD8_RESET_VAL      0x0000u
#define GPIO_PD9_RESET_VAL      0x0000u
#define GPIO_PD10_RESET_VAL    0x0000u
#define GPIO_JPD0_RESET_VAL    0x0000u
/*no Anolog*/

/* Port Driver Strength: output mode. 0:<=10mhz, 1:<=40mhz
* 40MHZ pin select:P0_2,3,5,6,7,13,14  ; P10_ALL ;P11_0~7
*/
#define GPIO_PDSC0_RESET_VAL      0x0000u    
#define GPIO_PDSC8_RESET_VAL      0x0000u
#define GPIO_PDSC9_RESET_VAL      0x0000u
#define GPIO_PDSC10_RESET_VAL    0x0000u
/*no Jtag*/
/*no Anolog*/

/* Port open drain control: output mode. 0:push-pull, 1:open-drain*/
#define GPIO_PODC0_RESET_VAL      0x0000u   
#define GPIO_PODC8_RESET_VAL      0x0000u  
#define GPIO_PODC9_RESET_VAL      0x0000u
#define GPIO_PODC10_RESET_VAL    0x0000u
#define GPIO_JPODC0_RESET_VAL    0x0000u
/*no Anolog*/

/* Set default for output pin */
#define GPIO_P0_RESET_VAL        0x0000u
#define GPIO_P8_RESET_VAL        0x0000u
#define GPIO_P9_RESET_VAL        0x0000u
#define GPIO_P10_RESET_VAL      0x0000u
#define GPIO_JP0_RESET_VAL      0x0000u
#define GPIO_AP0_RESET_VAL      0x0000u


/*----------------------- GPIO STANDBY ---------------------------- */
/* PMC: 0=port mode 1=alternative */
#define GPIO_PMC0_STANDBY_VAL         0x0000u 
#define GPIO_PMC8_STANDBY_VAL         0x0000u
#define GPIO_PMC9_STANDBY_VAL         0x0000u 
#define GPIO_PMC10_STANDBY_VAL       0x0000u
#define GPIO_JPMC0_STANDBY_VAL       0x0000u
/*no Anolog*/
#define GPIO_REG_NONE_VAL      0x0000u  /*none register*/

/* Port IP Control: IN alternative mode, mask PM.  1=unuse PM */
#define GPIO_PIPC0_STANDBY_VAL      0x0000u
#define GPIO_PIPC8_STANDBY_VAL      0x0000u
#define GPIO_PIPC9_STANDBY_VAL      0x0000u
#define GPIO_PIPC10_STANDBY_VAL    0x0000u
/*no Jtag*/
/*no Anolog*/

/* PM: 0=output 1=input */
#define GPIO_PM0_STANDBY_VAL         0xFFFFu  
#define GPIO_PM8_STANDBY_VAL         0xFFFFu 
#define GPIO_PM9_STANDBY_VAL         0xFFFFu
#define GPIO_PM10_STANDBY_VAL       0xFFFFu
#define GPIO_JPM0_STANDBY_VAL       0xFFFFu
#define GPIO_APM0_STANDBY_VAL      0xFFFFu

/* Port InputBuffer Control: all 0,unused here */
#define GPIO_PIBC0_STANDBY_VAL      0x0000u   
#define GPIO_PIBC8_STANDBY_VAL      0x0000u
#define GPIO_PIBC9_STANDBY_VAL      0x0000u
#define GPIO_PIBC10_STANDBY_VAL    0x0000u
#define GPIO_APIBC0_STANDBY_VAL    0x0000u
#define GPIO_JPIBC0_STANDBY_VAL    0x0000u

/* PFCAE,PFCE,PFC:IN alternative mode, select a alternative function in 0~4.
*  binary value [PFCAEn_m,PFCEn_m,PFCn_m]b  from 0~4  is a alternative function.
* PFC port:0,1,8,9,10,11,12,18,20
* PFCE port:0,8,9,10,11,12   PFCE port:0,10,11
*/
#define GPIO_PFC0_STANDBY_VAL       0x0000u
#define GPIO_PFCE0_STANDBY_VAL     0x0000u  
#define GPIO_PFCAE0_STANDBY_VAL   0x0000u   

#define GPIO_PFC8_STANDBY_VAL       0x0000u
#define GPIO_PFCE8_STANDBY_VAL     0x0000u  
#define GPIO_PFCAE8_STANDBY_VAL   0x0000u 

#define GPIO_PFC9_STANDBY_VAL        0x0000u
#define GPIO_PFCE9_STANDBY_VAL      0x0000u 
#define GPIO_PFCAE9_STANDBY_VAL    0x0000u   

#define GPIO_PFC10_STANDBY_VAL    0x0000u
#define GPIO_PFCE10_STANDBY_VAL   0x0000u   
#define GPIO_PFCAE10_STANDBY_VAL  0x0000u  
/*no PFCE10*/
/*no PFCAE10*/

#define GPIO_JPFC0_STANDBY_VAL      0x0000u
#define GPIO_JPFCE0_STANDBY_VAL    0x0000u  
#define GPIO_JPFCAE0_STANDBY_VAL  0x0000u   
/*no Anolog*/


/* Port Bidirection Control: 1= Bidirection */
#define GPIO_PBDC0_STANDBY_VAL      0x0000u   
#define GPIO_PBDC8_STANDBY_VAL      0x0000u
#define GPIO_PBDC9_STANDBY_VAL      0x0000u
#define GPIO_PBDC10_STANDBY_VAL    0x0000u
#define GPIO_APBDC0_STANDBY_VAL    0x0000u
#define GPIO_JPBDC0_STANDBY_VAL    0x0000u

/* PullUp Control: input mode.  1= internal pullup.
* Care that PUn.PUn_m=1 and PDn.PDn_m=1, then the real Pin is pulldown
*/
#define GPIO_PU0_STANDBY_VAL      0x0000u   
#define GPIO_PU8_STANDBY_VAL      0x0000u
#define GPIO_PU9_STANDBY_VAL      0x0000u
#define GPIO_PU10_STANDBY_VAL    0x0000u
#define GPIO_JPU0_STANDBY_VAL    0x0000u
/*no Anolog*/

/* PullUp Control: input mode.  1= internal pulldown */
#define GPIO_PD0_STANDBY_VAL      0x0000u   
#define GPIO_PD8_STANDBY_VAL      0x0000u
#define GPIO_PD9_STANDBY_VAL      0x0000u
#define GPIO_PD10_STANDBY_VAL    0x0000u
#define GPIO_JPD0_STANDBY_VAL    0x0000u
/*no Anolog*/

/* Port Driver Strength: output mode. 0:<=10mhz, 1:<=40mhz
* 40MHZ pin select:P0_2,3,5,6,7,13,14  ; P10_ALL ;P11_0~7  //no register
*/
#define GPIO_PDSC0_STANDBY_VAL      0x0000u   
/*#define GPIO_PDSC8_STANDBY_VAL      0x0000    no register*/
/*#define GPIO_PDSC9_STANDBY_VAL      0x0000    no register*/
#define GPIO_PDSC10_STANDBY_VAL    0x0000u
/*no Jtag*/
/*no Anolog*/

/* Port open drain control: output mode. 0:push-pull, 1:open-drain*/
#define GPIO_PODC0_STANDBY_VAL      0x0000u  
#define GPIO_PODC8_STANDBY_VAL      0x0000u 
#define GPIO_PODC9_STANDBY_VAL      0x0000u
#define GPIO_PODC10_STANDBY_VAL    0x0000u
#define GPIO_JPODC0_STANDBY_VAL    0x0000u
/*no Anolog*/
/* Set default for output pin */
#define GPIO_P0_STANDBY_VAL        0x0000u
#define GPIO_P8_STANDBY_VAL        0x0000u
#define GPIO_P9_STANDBY_VAL        0x0000u
#define GPIO_P10_STANDBY_VAL      0x0000u
#define GPIO_JP0_STANDBY_VAL      0x0000u
#define GPIO_AP0_STANDBY_VAL      0x0000u

#endif /*_PIN_MAP_CC_H*/
/**************** END OF FILE *****************************************/

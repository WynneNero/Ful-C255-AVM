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
* 0.1	   Jun 26,2016   PEI Jingli  Initial version
------------------------------------------------------------------------
* 0.2	   Jun 29,2016   LIU Chenxi  Correct errors during merging		
------------------------------------------------------------------------
* 0.3	   July 07,2016  PEI Jingli  Adapt xxpin MCU  
------------------------------------------------------------------------
* 0.4	   Oct 24,2016  PEI Jingli   Config reset parameters, 
                                 p0_6 as general io when active and reset                                  
------------------------------------------------------------------------
*0.5     Nov 10,2016  PEI Jingli    Set standby paramters
------------------------------------------------------------------------
*0.6     Nov 17,2016  PEI Jingli    Add Pn register for default setting
*=====================================================================*/
#ifndef _PIN_MAP_CC_H
#define _PIN_MAP_CC_H
#include "CONFIG.H"
#include "SystemMode_Cfg.h"


/*--------------------configration method----------------------
* 1. independent IO
    PMC:bit=0 -> PM
                         1:input  -> PIBC=1,PU,PD
                 
                         0:output->PBDC,PDSC,PODC
*2. alternative mode
   PMC:bit=1 ->PIPC
                         0   -> PFC,PFCE,PFCAE
                              ->PM
                                  1: input   -> same as 1.
                                  0:output-> same as 1.
                                   
                         1  ->PFC,PFCE,PFCAE
                       (directIO chapter2.11)
*---------------------------------------------------------*/
#if ( MCU_PIN == PIN100 )
/*-- MCU_RH850_F1L:  PORT 0,8,9,10,11,JP0,AP0   --*/
#define MCU_PORT_NUM       5
#define MCU_APORT_NUM     1
#define MCU_JPORT_NUM     1


/* PMC: 0=port mode 1=alternative */
#define GPIO_PMC0_ACTIVE_VAL        0x000F   //0000 0000 0000 1111 p0_4,p0_5,p0_6,p0_7,p0_10,p0_9= port ; p0_0,p0_1,p0_2,p0_3=alt 
#define GPIO_PMC8_ACTIVE_VAL        0x0385   //0000 0011 1000 0101,alt:P8_7,P8_8,P8_9,p8_2,p8_0
#define GPIO_PMC9_ACTIVE_VAL        0x0000   //0000 0000 0000 0000 
#define GPIO_PMC10_ACTIVE_VAL       0x02C0   //0000 0010 1100 0000  alt:p10_6,p10_7,p10_9
#define GPIO_PMC11_ACTIVE_VAL       0x0060   //0000 0000 0110 0000  p11_5,p11_6 uart
#define GPIO_JPMC0_ACTIVE_VAL       0x0000   //
//no Anolog
#define GPIO_REG_NONE_VAL           0x0000   //none register


/* Port IP Control: IN alternative mode, mask PM.  1=unuse PM */
#define GPIO_PIPC0_ACTIVE_VAL       0x000C   //0000 0000 0000   1100  ,p0_2,p0_3 control by alt spi
#define GPIO_PIPC8_ACTIVE_VAL       0x0000    //unuse 
#define GPIO_PIPC9_ACTIVE_VAL       0x0000    //unuse 
#define GPIO_PIPC10_ACTIVE_VAL      0x0000    //unuse 
#define GPIO_PIPC11_ACTIVE_VAL      0x0000    //unuse 
//no Jtag
//no Anolog

/* PM: 0=output 1=input */
#define GPIO_PM0_ACTIVE_VAL         0x6047    //0110 0000 0100 0111  	 p0_0,p0_1,p0_2,p0_6, =in; p0_4 ,p0_5,p0_7,p0_9,p0_10=0ut
#define GPIO_PM8_ACTIVE_VAL         0x007B    //0000 0000 0011 1011 	p8_0,P8_1,P8_3,P8_4 ,P8_5= in
#define GPIO_PM9_ACTIVE_VAL         0x0000    //0000 0000 0000 0000 
#define GPIO_PM10_ACTIVE_VAL        0x6240    //0010 0010 0100 0000  p10_6,P10_13 in,p10_9=in;
#define GPIO_PM11_ACTIVE_VAL        0x0040    //	0000 0000 0100 0010  P11_1,p11_6 in
#define GPIO_JPM0_ACTIVE_VAL        0xFFFF    //Out:
#define GPIO_APM0_ACTIVE_VAL        0x07FF    //0000 0111 1111 1111 in:AP0_1,2,3,4,5,6,7,8,9,10


/* Port InputBuffer Control: all 0,unused here */
#define GPIO_PIBC0_ACTIVE_VAL       0x0047    //0000 0000 0100 0111  p0_0,p0_1,p0_6, =in; enable input buffer   
#define GPIO_PIBC8_ACTIVE_VAL       0x003A	  //0000 0000 0011 1010  P8_1,P8_3,P8_4,P8_5 = in
#define GPIO_PIBC9_ACTIVE_VAL       0x0000
#define GPIO_PIBC10_ACTIVE_VAL      0X2000    //0010 0010 0100 0000  p10_6,P10_13 in,p10_9=in;
#define GPIO_PIBC11_ACTIVE_VAL      0x0000    //0000 0000 0000 0010  P11_1, in
#define GPIO_APIBC0_ACTIVE_VAL      0x07FF    //0000 0111 1111 1111 in:AP0_1,2,3,4,5,6,7,8,9,10
#define GPIO_JPIBC0_ACTIVE_VAL      0x0000

/* PFCAE,PFCE,PFC:IN alternative mode, select a alternative function in 0~4.
*  binary value [PFCAEn_m,PFCEn_m,PFCn_m]b  from 0~4  is a alternative function.
*/
#define GPIO_PFC0_ACTIVE_VAL        0x000E   //0000 0000 0000 1111 p0,p1,p2,p3  contorl mode is alt 4th
#define GPIO_PFCE0_ACTIVE_VAL       0x000E   //0000 0000 0000 1111
#define GPIO_PFCAE0_ACTIVE_VAL      0x0000   //0000 0000 0000 0000

#define GPIO_PFC8_ACTIVE_VAL        0x0380   //0000 0011 1000 0000  P8_0:INTP4,P8_7,P8_8,P8_9:alt2 PWG
#define GPIO_PFCE8_ACTIVE_VAL       0x0005   //0000 0000 0000 0101  
#define GPIO_PFCAE8_ACTIVE_VAL      0x0000   //0000 0000 0000 0000 

#define GPIO_PFC9_ACTIVE_VAL        0x0000   //
#define GPIO_PFCE9_ACTIVE_VAL       0x0000  
#define GPIO_PFCAE9_ACTIVE_VAL      0x0000    

#define GPIO_PFC10_ACTIVE_VAL       0x02C0   //  P10_6 CAN1RX:alter4_input=110,   P10_7 CAN1TX:alter4_output=110,  P10_8 ENCA0EC/FLMD1:alter3_input=010??  P10_9 INTP10:alter2_input=100
#define GPIO_PFCE10_ACTIVE_VAL      0x00C0
#define GPIO_PFCAE10_ACTIVE_VAL     0x0000

#define GPIO_PFC11_ACTIVE_VAL       0x0000   //P11_5 RLIN33TX:alter1_output=000,       P11_6 RLIN33RX:alter1_output=000
#define GPIO_PFCE11_ACTIVE_VAL      0x0000   
#define GPIO_PFCAE11_ACTIVE_VAL     0x0000   

#define GPIO_JPFC0_ACTIVE_VAL       0x0000   //Special function
#define GPIO_JPFCE0_ACTIVE_VAL      0x0000   
#define GPIO_JPFCAE0_ACTIVE_VAL     0x0000    
//no Anolog


/* Port Bidirection Control: 1= Bidirection */
#define GPIO_PBDC0_ACTIVE_VAL       0x0000   //
#define GPIO_PBDC8_ACTIVE_VAL       0x0040 	 //P8_6 
#define GPIO_PBDC9_ACTIVE_VAL       0x0000
#define GPIO_PBDC10_ACTIVE_VAL      0x0000
#define GPIO_PBDC11_ACTIVE_VAL      0x0000
#define GPIO_APBDC0_ACTIVE_VAL      0x0000
#define GPIO_JPBDC0_ACTIVE_VAL      0x0000

/* PullUp Control: input mode.  1= internal pullup.
* Care that PUn.PUn_m=1 and PDn.PDn_m=1, then the real Pin is pulldown
*/
#define GPIO_PU0_ACTIVE_VAL         0x0000    //Do not sure
#define GPIO_PU8_ACTIVE_VAL         0x0000
#define GPIO_PU9_ACTIVE_VAL         0x0000
#define GPIO_PU10_ACTIVE_VAL        0x0000
#define GPIO_PU11_ACTIVE_VAL        0x0000
#define GPIO_JPU0_ACTIVE_VAL        0x0000
//no Anolog

/* PullUp Control: input mode.  1= internal pulldown */
#define GPIO_PD0_ACTIVE_VAL         0x0000    //Do not sure
#define GPIO_PD8_ACTIVE_VAL         0x0000
#define GPIO_PD9_ACTIVE_VAL         0x0000
#define GPIO_PD10_ACTIVE_VAL        0x0000
#define GPIO_PD11_ACTIVE_VAL        0x0000
#define GPIO_JPD0_ACTIVE_VAL        0x0000
//no Anolog

/* Port Driver Strength: output mode. 0:<=10mhz, 1:<=40mhz*/
#define GPIO_PDSC0_ACTIVE_VAL       0x0008   // 0000 0000 0000 1000 //40Mhz:SPI,P0_1,P0_2,P0_3,
#define GPIO_PDSC8_ACTIVE_VAL       0x0310    //0000 0011 1000 0000 // p8_7, p8_8, p8_9,
#define GPIO_PDSC9_ACTIVE_VAL       0x0000    //none
#define GPIO_PDSC10_ACTIVE_VAL      0x00C0    //0000 0000 1100 0000 CAN_P10_6,7;
#define GPIO_PDSC11_ACTIVE_VAL      0x0000    //40Mhz:SPI_P11_1,2,3,4;LIN_P11_5,6
//no Jtag
//no Anolog

/* Port open drain control: output mode. 0:push-pull, 1:open-drain*/
#define GPIO_PODC0_ACTIVE_VAL       0x0000    //none
#define GPIO_PODC8_ACTIVE_VAL       0x0000    //none
#define GPIO_PODC9_ACTIVE_VAL       0x0000    //none
#define GPIO_PODC10_ACTIVE_VAL      0x0000    //none
#define GPIO_PODC11_ACTIVE_VAL      0x0000    //none
#define GPIO_JPODC0_ACTIVE_VAL      0x0000    //none
//no Anolog

/* Set default for output pin */
#define GPIO_P0_ACTIVE_VAL          0x0200
#define GPIO_P8_ACTIVE_VAL          0x0000
#define GPIO_P9_ACTIVE_VAL          0x0000
#define GPIO_P10_ACTIVE_VAL         0x0000
#define GPIO_P11_ACTIVE_VAL         0x0000
#define GPIO_JP0_ACTIVE_VAL         0x0000
#define GPIO_AP0_ACTIVE_VAL         0x0000
 
//#define ADC_REMAP_ACTIVE_VAL       (_ADCA0I0|_ADCA0I3|_ADCA0I4|_ADCA0I5|_ADCA0I6|_ADCA0I8)   // unused

/*----------------------- GPIO RESET ---------------------------- */
/* PMC: 0=port mode 1=alternative */
#define GPIO_PMC0_RESET_VAL         0x000F   //0000 0000 0000 1111 p0_4,p0_5,p0_6,p0_7,p0_10,p0_9= port ; p0_0,p0_1,p0_2,p0_3=alt
#define GPIO_PMC8_RESET_VAL         0x0385   //0000 0011 1000 0101,alt:P8_7,P8_8,P8_9,p8_2,p8_0
#define GPIO_PMC9_RESET_VAL         0x0000   //0000 0000 0000 0000 
#define GPIO_PMC10_RESET_VAL        0x02C0   //0000 0010 1100 0000  alt:p10_6,p10_7,p10_9  
#define GPIO_PMC11_RESET_VAL        0x0060   //0000 0000 0110 0000  p11_5,p11_6 uart
#define GPIO_JPMC0_RESET_VAL        0x0000
//no Anolog
#define GPIO_REG_NONE_VAL           0x0000   //none register

/* Port IP Control: IN alternative mode, mask PM.  1=unuse PM */
#define GPIO_PIPC0_RESET_VAL        0x000C    //0000 0000 0000   1100  ,p0_2,p0_3 control by alt spi   
#define GPIO_PIPC8_RESET_VAL        0x0000    //0000 0000 0000 0000
#define GPIO_PIPC9_RESET_VAL        0x0000    //0000 0000 0000 0000
#define GPIO_PIPC10_RESET_VAL       0x0000    //0000 0000 0000 0000
#define GPIO_PIPC11_RESET_VAL       0x0000    //0000 0000 0000 0000
//no Jtag
//no Anolog

/* PM: 0=output 1=input */
#define GPIO_PM0_RESET_VAL          0x6047    //0110 0000 0100 0111  	 p0_0,p0_1,p0_2,p0_6, =in; p0_4 ,p0_5,p0_7,p0_9,p0_10=0ut 
#define GPIO_PM8_RESET_VAL          0x007B    //0000 0000 0011 1011 	p8_0,P8_1,P8_3,P8_4 ,P8_5= in   
#define GPIO_PM9_RESET_VAL          0x0000    //0000 0000 0000 0000   
#define GPIO_PM10_RESET_VAL         0x6240    //0010 0010 0100 0000  p10_6,P10_13 in,p10_9=in;  
#define GPIO_PM11_RESET_VAL         0x0040    //	0000 0000 0100 0010  P11_1,p11_6 in  
#define GPIO_JPM0_RESET_VAL         0xFFFF    //Out:  
#define GPIO_APM0_RESET_VAL         0x07FF    //0000 0111 1111 1111 in:AP0_1,2,3,4,5,6,7,8,9,10  

/* Port InputBuffer Control: all 0,unused here */
#define GPIO_PIBC0_RESET_VAL        0x0047    //0000 0000 0100 0111  p0_0,p0_1,p0_6, =in; enable input buffer    
#define GPIO_PIBC8_RESET_VAL        0x003A	  //0000 0000 0011 1011  p8_0,P8_1,P8_3,P8_4,P8_5 = in
#define GPIO_PIBC9_RESET_VAL        0x0000
#define GPIO_PIBC10_RESET_VAL       0X2000    //0010 0010 0100 0000  p10_6,P10_13 in,p10_9=in;
#define GPIO_PIBC11_RESET_VAL       0x0000    //0000 0000 0000 0010  P11_1, in
#define GPIO_APIBC0_RESET_VAL       0x07FF    //0000 0111 1111 1111 in:AP0_1,2,3,4,5,6,7,8,9,10
#define GPIO_JPIBC0_RESET_VAL       0x0000

/* PFCAE,PFCE,PFC:IN alternative mode, select a alternative function in 0~4.
*  binary value [PFCAEn_m,PFCEn_m,PFCn_m]b  from 0~4  is a alternative function.
*/
#define GPIO_PFC0_RESET_VAL         0x000E   //0000 0000 0000 1111 p0,p1,p2,p3  contorl mode is alt 4th   
#define GPIO_PFCE0_RESET_VAL        0x000E   //0000 0000 0000 1111   
#define GPIO_PFCAE0_RESET_VAL       0x0000   //0000 0000 0000 0000    

#define GPIO_PFC8_RESET_VAL         0x0380   //0000 0011 1000 0000  P8_0:INTP4,P8_7,P8_8,P8_9:alt2 PWG  //P8_2 INTP6:alter3_input=010  P8_4 INTP8:alter3_input=010  P8_9 PWGA41O:alter2_output=100
#define GPIO_PFCE8_RESET_VAL        0x0005   //0000 0000 0000 0101   
#define GPIO_PFCAE8_RESET_VAL       0x0000   //0000 0000 0000 0000  

#define GPIO_PFC9_RESET_VAL         0x0000  //
#define GPIO_PFCE9_RESET_VAL        0x0000  
#define GPIO_PFCAE9_RESET_VAL       0x0000    

#define GPIO_PFC10_RESET_VAL        0x02C0   //  P10_6 CAN1RX:alter4_input=110,   P10_7 CAN1TX:alter4_output=110,  P10_8 ENCA0EC/FLMD1:alter3_input=010??  P10_9 INTP10:alter2_input=100  //P10_0 TAUD0O1:alter1_output=000,   P10_6 CAN1RX:alter4_input=110,   P10_7 CAN1TX:alter4_output=110,  P10_8 ENCA0EC/FLMD1:alter3_input=010��  P10_9 INTP10:alter2_input=100
#define GPIO_PFCE10_RESET_VAL       0x00C0    
#define GPIO_PFCAE10_RESET_VAL      0x0000 

#define GPIO_PFC11_RESET_VAL        0x0000   //P11_5 RLIN33TX:alter1_output=000,       P11_6 RLIN33RX:alter1_output=000  //P11_5 RLIN33TX:alter1_output=000,       P11_6 RLIN33RX:alter1_output=000
#define GPIO_PFCE11_RESET_VAL       0x0000    
#define GPIO_PFCAE11_RESET_VAL      0x0000   

#define GPIO_JPFC0_RESET_VAL        0x0000  //Special function
#define GPIO_JPFCE0_RESET_VAL       0x0000   
#define GPIO_JPFCAE0_RESET_VAL      0x0000    
//no Anolog


/* Port Bidirection Control: 1= Bidirection */
#define GPIO_PBDC0_RESET_VAL        0x0000    //   //Bidirection:P0_11,12  The port for IIC communication 
#define GPIO_PBDC8_RESET_VAL        0x0000
#define GPIO_PBDC9_RESET_VAL        0x0000
#define GPIO_PBDC10_RESET_VAL       0x0000
#define GPIO_PBDC11_RESET_VAL       0x0000
#define GPIO_APBDC0_RESET_VAL       0x0000
#define GPIO_JPBDC0_RESET_VAL       0x0000

/* PullUp Control: input mode.  1= internal pullup.
* Care that PUn.PUn_m=1 and PDn.PDn_m=1, then the real Pin is pulldown
*/
#define GPIO_PU0_RESET_VAL          0x0000    //Do not sure    
#define GPIO_PU8_RESET_VAL          0x0000
#define GPIO_PU9_RESET_VAL          0x0000
#define GPIO_PU10_RESET_VAL         0x0000
#define GPIO_PU11_RESET_VAL         0x0000
#define GPIO_JPU0_RESET_VAL         0x0000
//no Anolog

/* PullUp Control: input mode.  1= internal pulldown */
#define GPIO_PD0_RESET_VAL          0x0000    
#define GPIO_PD8_RESET_VAL          0x0000
#define GPIO_PD9_RESET_VAL          0x0000
#define GPIO_PD10_RESET_VAL         0x0000
#define GPIO_PD11_RESET_VAL         0x0000
#define GPIO_JPD0_RESET_VAL         0x0000
//no Anolog

/* Port Driver Strength: output mode. 0:<=10mhz, 1:<=40mhz*/
#define GPIO_PDSC0_RESET_VAL        0x0008    // 0000 0000 0000 1000 //40Mhz:SPI,P0_1,P0_2,P0_3,    
#define GPIO_PDSC8_RESET_VAL        0x0310    //0000 0011 1000 0000 // p8_7, p8_8, p8_9,
#define GPIO_PDSC9_RESET_VAL        0x0000    //none
#define GPIO_PDSC10_RESET_VAL       0x00C0    //0000 0000 1100 0000 CAN_P10_6,7;
#define GPIO_PDSC11_RESET_VAL       0x0000    //40Mhz:SPI_P11_1,2,3,4;LIN_P11_5,6
//no Jtag
//no Anolog

/* Port open drain control: output mode. 0:push-pull, 1:open-drain*/
#define GPIO_PODC0_RESET_VAL        0x0000    //   
#define GPIO_PODC8_RESET_VAL        0x0000    //none  
#define GPIO_PODC9_RESET_VAL        0x0000    //none
#define GPIO_PODC10_RESET_VAL       0x0000    //none
#define GPIO_PODC11_RESET_VAL       0x0000    //none
#define GPIO_JPODC0_RESET_VAL       0x0000    //none
//no Anolog

/* Set default for output pin */
#define GPIO_P0_RESET_VAL           0x0200
#define GPIO_P8_RESET_VAL           0x0000
#define GPIO_P9_RESET_VAL           0x0000
#define GPIO_P10_RESET_VAL          0x0000
#define GPIO_P11_RESET_VAL          0x0000
#define GPIO_JP0_RESET_VAL          0x0000
#define GPIO_AP0_RESET_VAL          0x0000

//#define ADC_REMAP_RESET_VAL          (_ADCA0I0|_ADCA0I8)

/*----------------------- GPIO STANDBY ---------------------------- */
/* PMC: 0=port mode 1=alternative */
#define GPIO_PMC0_STANDBY_VAL       0x000F  //0000 0000 0000 1111 p0_4,p0_5,p0_6,p0_7,p0_10,p0_9= port ;p0_0, p0_1,p0_2,p0_3=alt	//0x0040   // 6
#define GPIO_PMC8_STANDBY_VAL       0x0381   //0000 0011 1000 0001,alt:P8_7,P8_8,P8_9,p8_0   
#define GPIO_PMC9_STANDBY_VAL       0x0000   //0000 0000 0000 0000   
#define GPIO_PMC10_STANDBY_VAL      0x02C0   //0000 0010 1100 0000  alt:p10_6,p10_7,p10_9  
#define GPIO_PMC11_STANDBY_VAL      0x0060   //0000 0000 0110 0000 p11_5,p11_6 uart  
#define GPIO_JPMC0_STANDBY_VAL      0x0000   //alt:  
//no Anolog
#define GPIO_REG_NONE_VAL           0x0000  //none register

/* Port IP Control: IN alternative mode, mask PM.  1=unuse PM */
#define GPIO_PIPC0_STANDBY_VAL      0x000C  //0000 0000 0000 1100  p0_2,p0_3 csi_so,csi_sc ,control by alt spi	//0x0000  
#define GPIO_PIPC8_STANDBY_VAL      0x0000   //0000 0000 0000 0000  
#define GPIO_PIPC9_STANDBY_VAL      0x0000   //0000 0000 0000 0000  
#define GPIO_PIPC10_STANDBY_VAL     0x0000   //0000 0000 0000 0000 
#define GPIO_PIPC11_STANDBY_VAL     0x0000   //0000 0000 0000 0000 
//no Jtag
//no Anolog

/* PM: 0=output 1=input */
#define GPIO_PM0_STANDBY_VAL        0x0047    //0000 0000 0100 0111  	 p0_0,p0_1,p0_2,p0_6, =in; p0_4 ,p0_5,p0_9,p0_10=0ut	//0xFFFF  
#define GPIO_PM8_STANDBY_VAL        0x007B     //0000 0000 0011 1011 	p8_0,P8_1,P8_3,P8_4 ,P8_5= in;p8_7,p7_8,p7_9 = out  
#define GPIO_PM9_STANDBY_VAL        0x0000    //0000 0000 0000 0000  
#define GPIO_PM10_STANDBY_VAL       0x2280    //0010 0010 0100 0000  p10_6,P10_13 ,p10_9=in; 
#define GPIO_PM11_STANDBY_VAL       0x0040    //	0000 0000 0100 0010  P11_1,p11_6 in 
#define GPIO_JPM0_STANDBY_VAL       0xFFFF   //Out:  
#define GPIO_APM0_STANDBY_VAL       0x07FF   //0000 0111 1111 1111 in:AP0_1,2,3,4,5,6,7,8,9,10 


/* Port InputBuffer Control: all 0,unused here */
#define GPIO_PIBC0_STANDBY_VAL      0x0047     //0000 0000 0100 0111  p0_0,p0_1,p0_2,p0_6, =in; enable input buffer    
#define GPIO_PIBC8_STANDBY_VAL      0x003A	  //0000 0000 0011 1011  p8_0,P8_1,P8_3,P8_4,P8_5 = in
#define GPIO_PIBC9_STANDBY_VAL      0x0000
#define GPIO_PIBC10_STANDBY_VAL     0X2080    //0010 0010 0100 0000  p10_6,P10_13 in,p10_9=in;
#define GPIO_PIBC11_STANDBY_VAL     0x0000    //0000 0000 0000 0010  P11_1, in
#define GPIO_APIBC0_STANDBY_VAL     0x07FF    //0000 0111 1111 1111 in:AP0_1,2,3,4,5,6,7,8,9,10
#define GPIO_JPIBC0_STANDBY_VAL     0x0000

/* PFCAE,PFCE,PFC:IN alternative mode, select a alternative function in 0~4.
*  binary value [PFCAEn_m,PFCEn_m,PFCn_m]b  from 0~4  is a alternative function.
*/
#define GPIO_PFC0_STANDBY_VAL       0x000F   //0000 0000 0000 1111 p1,p2,p3  contorl mode is alt 4th  
#define GPIO_PFCE0_STANDBY_VAL      0x000F   //0000 0000 0000 1111   
#define GPIO_PFCAE0_STANDBY_VAL     0x0000   //0000 0000 0000 0000   

#define GPIO_PFC8_STANDBY_VAL       0x0380   //0000 0011 1000 0000  P8_0:INTP3,P8_7,P8_8,P8_9:alt2 PWG   
#define GPIO_PFCE8_STANDBY_VAL      0x0001   //0000 0000 0000 000   // P8_2 INTP6:alter3_input=010 
#define GPIO_PFCAE8_STANDBY_VAL     0x0000  

#define GPIO_PFC9_STANDBY_VAL       0x0000   //P9_0 CSIH2CSS0:alter3_input=010,  P9_1 INTP11:alter1_input=000 
#define GPIO_PFCE9_STANDBY_VAL      0x0000  
#define GPIO_PFCAE9_STANDBY_VAL     0x0000    

#define GPIO_PFC10_STANDBY_VAL      0x02C0   //  P10_6 CAN1RX:alter4_input=110,   P10_7 CAN1TX:alter4_output=110,  P10_8 ENCA0EC/FLMD1:alter3_input=010??  P10_9 INTP10:alter2_input=100    
#define GPIO_PFCE10_STANDBY_VAL     0x00C0 
#define GPIO_PFCAE10_STANDBY_VAL    0x0000

#define GPIO_PFC11_STANDBY_VAL      0x0000   //P11_2 CSIH2SO:alter1_output=000,  P11_3 CSIH2SC:alter1=000,  
#define GPIO_PFCE11_STANDBY_VAL     0x0000    
#define GPIO_PFCAE11_STANDBY_VAL    0x0000   

#define GPIO_JPFC0_STANDBY_VAL      0x0000   //Special function  
#define GPIO_JPFCE0_STANDBY_VAL     0x0000   
#define GPIO_JPFCAE0_STANDBY_VAL    0x0000    
//no Anolog


/* Port Bidirection Control: 1= Bidirection */
#define GPIO_PBDC0_STANDBY_VAL      0x0000	//0x0000    //Bidirection
#define GPIO_PBDC8_STANDBY_VAL      0x0000
#define GPIO_PBDC9_STANDBY_VAL      0x0000
#define GPIO_PBDC10_STANDBY_VAL     0x0000
#define GPIO_PBDC11_STANDBY_VAL     0x0000
#define GPIO_APBDC0_STANDBY_VAL     0x0000
#define GPIO_JPBDC0_STANDBY_VAL     0x0000

/* PullUp Control: input mode.  1= internal pullup.
* Care that PUn.PUn_m=1 and PDn.PDn_m=1, then the real Pin is pulldown
*/
#define GPIO_PU0_STANDBY_VAL        0x0000    //Do not sure
#define GPIO_PU8_STANDBY_VAL        0x0000
#define GPIO_PU9_STANDBY_VAL        0x0000
#define GPIO_PU10_STANDBY_VAL       0x0000
#define GPIO_PU11_STANDBY_VAL       0x0000
#define GPIO_JPU0_STANDBY_VAL       0x0000
//no Anolog

/* PullUp Control: input mode.  1= internal pulldown */
#define GPIO_PD0_STANDBY_VAL        0x0000    //Do not sure
#define GPIO_PD8_STANDBY_VAL        0x0000
#define GPIO_PD9_STANDBY_VAL        0x0000
#define GPIO_PD10_STANDBY_VAL       0x0000
#define GPIO_PD11_STANDBY_VAL       0x0000
#define GPIO_JPD0_STANDBY_VAL       0x0000
//no Anolog

/* Port Driver Strength: output mode. 0:<=10mhz, 1:<=40mhz*/
#define GPIO_PDSC0_STANDBY_VAL      0x0000 
#define GPIO_PDSC8_STANDBY_VAL      0x0000  
#define GPIO_PDSC9_STANDBY_VAL      0x0000  
#define GPIO_PDSC10_STANDBY_VAL     0x0000  
#define GPIO_PDSC11_STANDBY_VAL     0x0000   

//no Jtag
//no Anolog

/* Port open drain control: output mode. 0:push-pull, 1:open-drain*/
#define GPIO_PODC0_STANDBY_VAL      0x0000    //open-drain:IIC_P0_11,12	//0x0000   
#define GPIO_PODC8_STANDBY_VAL      0x0000    //none   
#define GPIO_PODC9_STANDBY_VAL      0x0000    //none   
#define GPIO_PODC10_STANDBY_VAL     0x0000    //none   
#define GPIO_PODC11_STANDBY_VAL     0x0000    //none  
#define GPIO_JPODC0_STANDBY_VAL     0x0000    //none   

/* Set default for output pin */
#define GPIO_P0_STANDBY_VAL         0x0200
#define GPIO_P8_STANDBY_VAL         0x0000
#define GPIO_P9_STANDBY_VAL         0x0000
#define GPIO_P10_STANDBY_VAL        0x0000
#define GPIO_P11_STANDBY_VAL        0x0000
#define GPIO_JP0_STANDBY_VAL        0x0000
#define GPIO_AP0_STANDBY_VAL        0x0000

//#define ADC_REMAP_STANDBY_VAL       (_ADCA0I0|_ADCA0I8)   // LLF_MARK

#endif

#endif //_PIN_MAP_CC_H
/**************** END OF FILE *****************************************/


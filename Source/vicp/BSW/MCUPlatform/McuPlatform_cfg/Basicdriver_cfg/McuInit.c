/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									   *
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
* Version       Date    Name    Changes and comments
------------------------------------------------------------------------
* 0.1	   Jun 26,2016   PEI Jingli  Initial version
------------------------------------------------------------------------
* 0.2	   Jun 29,2016   LIU Chenxi  Correct errors during merging		
------------------------------------------------------------------------
* 0.3	   July 07,2016  PEI Jingli  Adapt 64pin MCU
------------------------------------------------------------------------
* 0.4	   July 21,2016  PEI Jingli  Remove test code
------------------------------------------------------------------------
* 0.5	   Oct 28,2016  PEI Jingli  del R_PORT_Init/R_TAUD_Start for unused
*----------------------------------------------------------------------
* 0.6          Dec 20,2016   ShangQiuju  remove unused include  files.
*----------------------------------------------------------------------
* 0.7          Dec 29,2016 PEI Jingli  delete unused include  files and test code
*------------------------------------------------------------------------
* 0.8          Jan 24,2017  ZhangJie  Fix Coverity warnings.
*=====================================================================*/
#include "Mcu_if.h"
#include "Irq_if.h"
#include "iodefine.h"

/*============================================================================
Includes
============================================================================*/

/***********************************************************************
*  Name        : MCU_HardwareInit
*  Description : hardware is reset, run in rest isr, before call C_Lib     
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void MCU_HardwareInit(void)
{
   WDTNMIFC=0X07u;		 /*clear NMI */
  /*Step 1: Init IRQ*/
  
  /*Step 2: init clock and CPU Mode*/
  
  /*Step 3: init IO*/
  
  /*WATCHDOG_Disable();*/
  
   mcu_get_reset_reason();
   /********************************************************/
   /*  PLL setting                     */
   /********************************************************/
   /*the high clock is enable in bootloader,so we don't need*/
   /*to enable again in here!*/    
   /*mcu_setup_high_clock();*/
   
   /*mcu_disable_interrupt();*/
   /********************************************************/
   /* setup Interrupt table address                */
   /********************************************************/
   /*mcu_set_irq_table_address(0x00004000);*/    
  
   /*mcu_enable_interrupt();*/
   /********************************************************/
   /*  All Interrupt setup               */
   /********************************************************/
   IRQ_Init_Setup();
  
   /********************************************************/
   /*  All IO config                    */
   /********************************************************/
   mcu_io_init_reset();

}

/***********************************************************************
*  Name        : MCU_MainInit
*  Description : System is init, run in main function, C enviroment is OK         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void MCU_MainInit(void)
{
   /*Step 1: Config IRQ*/
   /*IRQ_Init_Setup();  select 1st int source*/

}

/***********************************************************************
*  Name        : MCU_EnterSleep
*  Description : System will enter sleep, set IO,TAU, domains,clock,  wakeup factors.
*                 also enable wakeup interruput 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void MCU_EnterSleep(void)
{
  /*MCU IO for sleep*/
  mcu_io_init_sleep();
}

/***********************************************************************
*  Name        : MCU_Wakeup
*  Description : System is wakeup, init device         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void MCU_Wakeup(void)
{  
  /*Init MCU IO for wakeup*/
  mcu_io_init_wakeup();
}


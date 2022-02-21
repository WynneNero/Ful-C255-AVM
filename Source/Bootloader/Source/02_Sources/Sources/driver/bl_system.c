/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of the system clock module for RH850F1L(R7F7010233) of RENESAS.
 *
 *  \file       bl_system.c
 *  \ingroup    driver_module
 *  \author     lele.liu <lele.liu@hirain.com>
 *
 *  \version    1.0.0
 *  
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | -------------
 *      01.00.00 | 24/01/2016 | lele.liu         | N/A | BootDrv010001
 *
 *****************************************************************************/
#include "config.h"

#include "bl_system.h"
#include "cpu.h"
#include "dr7f701023_IRQ.h"

#define protected_write(preg,pstatus,reg,value)   do{\
                                                  (preg)=0xa5u;\
                                                  (reg)=(value);\
                                                  (reg)=~(value);\
                                                  (reg)=(value);\
                                                  }while((pstatus)==1u)

/** a function pointer is used to go to application*/
typedef void (* theApp)(void);

#define SYS_RESET_VECTOR   0x00018000UL		//0x0000C000UL
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : Mcu_ClkSet
*
* Description   : MCU bus clock set. 
*
* Inputs        : None
*
* Outputs       : None
* 
* Limitations   : this function set clock to a target bus.
*                 
************************************************************************************************
END_FUNCTION_HDR */
void Sys_InitClock(void)
{
    
    /* Prepare 16MHz MainOsc */
      MOSCC=0x05;                           // Set MainOSC gain (16MHz < MOSC frequency <= 20MHz)
     MOSCST=0x1ffff;                       // Set MainOSC stabilization time to max (8,19 ms)
     protected_write(PROTCMD0,PROTS0,MOSCE,0x01);  // Trigger Enable (protected write)
      while ((MOSCS&0x04) == 0);            // Wait for active MainOSC


    /* Prepare PLL*/
      PLLC=0x00000a27;                     //16 MHz MainOSC -> 80MHz PLL, no SSCG (MR=1, PR=4, NR=24)
      protected_write(PROTCMD1,PROTS1,PLLE,0x01);   //enable PLL
      while((PLLS&0x04) != 0x04);          //Wait for active PLL
    
    /* C_ISO_CPUCLK Clock divider */
      protected_write(PROTCMD1,PROTS1,CKSC_CPUCLKD_CTL,0x01); /* C_ISO_CPUCLK / 1 */
      while((CKSC_CPUCLKD_ACT & 0x07) != 0x01);

     /* PLL -> C_ISO_CPUCLK */
      protected_write(PROTCMD1,PROTS1,CKSC_CPUCLKS_CTL,0x03); /* C_ISO_CPUCLK = CPLLCLK */
      while((CKSC_CPUCLKS_ACT & 0x03) != 0x03);

    /* PLL -> RSCAN Clock: PPLLCLK (PLL) */
      protected_write(PROTCMD1,PROTS1,CKSC_ICANS_CTL,0x02); /* C_ISO_CAN = PPLLCLK */
      while((CKSC_ICANS_ACT & 0x03) != 0x02);

    /* MainOSC/1 -> RSCAN direct Clock: 16 MHz */
    protected_write(PROTCMD1,PROTS1,CKSC_ICANOSCD_CTL,0x01); /* C_ISO_CANOSC = MainOSC/1 */
    while((CKSC_ICANOSCD_ACT & 0x03) != 0x01);
    
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : Sys_RemapInterrupt
*
* Description   : remap MCU interrupt to sram 
*
* Inputs        : None
*
* Outputs       : None
* 
* Limitations   : 
*                 
************************************************************************************************
END_FUNCTION_HDR */
void Sys_RemapInterrupt(void)
{
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : Sys_DeinitClock
*
* Description   : Deinit all ,mcu related registers if necessary
*
* Inputs        : None
*
* Outputs       : None
* 
* Limitations   : None
*                 
************************************************************************************************
END_FUNCTION_HDR */
void Sys_DeinitClock(void)
{
   #if 0
    /* Reset  MainOsc */
    protected_write(PROTCMD0,PROTS0,MOSCE,0x02);  // Trigger disable (protected write)
      while ((MOSCS&0x04) == 1);            // Wait for inactive MainOSC
      MOSCC=0x04;                           /*Set MainOSC gain in reset state*/
     MOSCST=0x44C0;                       // Set MainOSC stabilization time to reset value
     
    /* Reset  PLL0*/
    protected_write(PROTCMD1,PROTS1,PLLE,0x02);   //disable PLL
      while((PLLS&0x04) != 0x0);          //Wait for inactive PLL
      PLLC=0x0001133b;

    /* Reset C_ISO_CPUCLK Clock divider */
      protected_write(PROTCMD1,PROTS1,CKSC_CPUCLKD_CTL,0x01); /* C_ISO_CPUCLK / 1 */
      while((CKSC_CPUCLKD_ACT & 0x07) != 0x01);

     /* Reset C_ISO_CPUCLK */
      protected_write(PROTCMD1,PROTS1,CKSC_CPUCLKS_CTL,0x01); 
      while((CKSC_CPUCLKS_ACT & 0x03) != 0x01);
    
    /* Reset RSCAN Clock: PPLLCLK (PLL) */
      protected_write(PROTCMD1,PROTS1,CKSC_ICANS_CTL,0x03); 
      while((CKSC_ICANS_ACT & 0x03) != 0x03);

    /* Reset RSCAN direct Clock */
    protected_write(PROTCMD1,PROTS1,CKSC_ICANOSCD_CTL,0x0); 
    while((CKSC_ICANOSCD_ACT & 0x03) != 0x0);
    #endif
    
    /* Reset RSCAN Clock: PPLLCLK (PLL) */
    protected_write(PROTCMD1,PROTS1,CKSC_ICANS_CTL,0x03); 
    while((CKSC_ICANS_ACT & 0x03) != 0x03);

    /* Reset RSCAN direct Clock */
    protected_write(PROTCMD1,PROTS1,CKSC_ICANOSCD_CTL,0x0); 
    while((CKSC_ICANOSCD_ACT & 0x03) != 0x0);
    
    /* Reset C_ISO_CPUCLK Clock divider */
    protected_write(PROTCMD1,PROTS1,CKSC_CPUCLKD_CTL,0x01); /* C_ISO_CPUCLK / 1 */
    while((CKSC_CPUCLKD_ACT & 0x07) != 0x01);

    /* Reset C_ISO_CPUCLK */
    protected_write(PROTCMD1,PROTS1,CKSC_CPUCLKS_CTL,0x01); 
    while((CKSC_CPUCLKS_ACT & 0x03) != 0x01);

    /* Reset  MainOsc */
    protected_write(PROTCMD0,PROTS0,MOSCE,0x02);  /* Trigger disable (protected write)*/
    while ((MOSCS&0x04) == 1);            /* Wait for inactive MainOSC*/
    MOSCC=0x04;                           /*Set MainOSC gain in reset state*/
    MOSCST=0x44C0;                       /*Set MainOSC stabilization time to reset value*/
     
    /* Reset  PLL0*/
    protected_write(PROTCMD1,PROTS1,PLLE,0x02);   /*disable PLL*/
    while((PLLS&0x04) != 0x0);          /*Wait for inactive PLL*/
    PLLC=0x0001133b;

}

/**************************************************************************//**
 *
 *  \details Set system clock to sleep mode.
 *
 *  \return None.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
void Sys_Sleep(void)
{
  
}

void Sys_Reset(void)
{
   /* software reset register
	 bit 31~1 reserved
	 bit 0		 reset enable. =1 to reset */
	 //SWRESA =0x00000001;

	 bl_application_value_dataflash_maker();
   	 PgrmCounter();
	 tm_delay_us(10000);
   
	 protected_write(PROTCMD0,PROTS0,SWRESA,0x01); 
 }

 /***********************************************************************
*  Name        : tm_delay_us
*  Description : 
*  Parameter   : U16
*  Returns     : void
***********************************************************************/
void tm_delay_us(U16 period)
{
    U32 i;
    U32 cmd_period = period * 0x0D;

    for(i = 0x00; i < cmd_period ; i++)
    {
    }
}

/**************************************************************************//**
 *
 *  \details Set up the application entry point, and go to the application.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
void Sys_GotoApplication(void)
{
	bl_u64_t App;
	theApp AppEntry;
	bl_u64_t lapp ;
	lapp =  (*( volatile bl_u64_t *)SYS_RESET_VECTOR);
	App=lapp >> 16;
	App = ( (lapp & 0x0f)  << 16) +App;
	App = SYS_RESET_VECTOR+App;
	AppEntry = (theApp)App;
    //SET_EBASE(SYS_RESET_VECTOR);
    //SET_INTBP(SYS_RESET_VECTOR + IRQ_TABLE_START);
	//SET_PSW_EBV();
    AppEntry();
}

/**************************************************************************//**
 *
 *  \details .
 *
 *  \since  V2.0.0
 *
 *****************************************************************************/
void Sys_ProtectBootloader(void)
{

}







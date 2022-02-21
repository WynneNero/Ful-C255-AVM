/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									   *
************************************************************************
* Object        : Mcu.c
* Module        :
* Instance      :
* Description   :
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comment__DSB__DSBs
** ----------------------------------------------------------------------
* 0.1    Feb 10,2013    NI Rujin    Initial version
* ----------------------------------------------------------------------
* 0.2    Mar 11,2013    LIU Chenxi  Fix issues found on entering LP
* ----------------------------------------------------------------------
* 0.3    Jun 09,2013    LIU Chenxi  Update P2 setting for switch on
         battery power supply when main power lost
------------------------------------------------------------------------
* 0.4	 July 07,2016  PEI Jingli  Adapt 64pin MCU
------------------------------------------------------------------------
* 0.5	 July 07,2016  LIU Chenxi  Refine code structure
------------------------------------------------------------------------
* 0.6	 July 07,2016  LIU Chenxi  merge with remotes/origin/ui4959_bs1
------------------------------------------------------------------------
* 0.7	 July 21,2016  PEI Jingli  Implement code review comments.
* ----------------------------------------------------------------------
* 0.8    Aug  01,2016  PEI Jingli  Change interface by MCU_PIN   
* ----------------------------------------------------------------------
* 0.9    Aug  26,2016  PEI Jingli  Modify IO_Init inf for filtering noise 
                       Modify mcu reset reason micro
* ----------------------------------------------------------------------
* 1.0    Nov 17,2016  PEI Jingli  Add default value setting of IO   
* ----------------------------------------------------------------------
* 1.1    Dec 14,2016  Ren Weimin		Add PFCAE11,PFCE11 for IO config.
* ----------------------------------------------------------------------
* 1.2    Dec 20,2016  ShangQiuju		Remove unused include files.
* ----------------------------------------------------------------------
* 1.3    Dec 29,2016  PEI Jingli  Change for codeReview result   
* ----------------------------------------------------------------------
* 1.4    Jan 06,2016  PEI Jingli  Add parameter checking
* ----------------------------------------------------------------------
* 1.5    Jan 06,2016  PEI Jingli  Delete pwmd code
*------------------------------------------------------------------------
* 1.6    Jan 13,2017  ZhangJie  Fix Coverity warning.
 ----------------------------------------------------------------------
* 1.7    Jan 16,2017  RenWeimin  Add test code. Add interface to get reset reason.
*-----------------------------------------------------------------------
* 1.8    Jan 24,2017   ZhangJie   Remove unused include file.
*-----------------------------------------------------------------------
* 1.9    Feb 09,2017   ZhangJie   Using micro to call app function.
* ----------------------------------------------------------------------
* 2.0    Feb 20,2017  PEI Jingli  Rename interface
* ----------------------------------------------------------------------
* 2.1    Mar 23,2017  PEI Jingli  Fix enter-stop mode processing.
*=====================================================================*/

#include "CONFIG.H"
#include "MCU.h"
#include "GPIO.h"
#include "wpreg.h"
#include "mcu_if.h"
#include "Gpio_if.h"
#include "clock_if.h"
#include "irq_if.h"
#include "stbc_if.h"
#include "TimerUnit_if.h"
#include "Service_HOOKS.h"

/* general PORT register struct */
typedef struct {
    U8    portNo; /*GPIO_PORT_TYPE*/
    U16  pmc;
    U16  pipc;
    U16  pm;
    U16  pibc;
    U16  pfc;
    U16  pfce;
    U16  pfcae;
    U16  pbdc;
    U16  pu;
    U16  pd;
    U16  pdsc;
    U16  podc;
    U16  p;
}MCU_PORT_REGVAL;

/*general IO in active mode*/
const MCU_PORT_REGVAL MCU_IOACTIVE_REGLIST[MCU_PORT_NUM]=
{/*PORT number
      pmc                                   pipc                                    pm                                      pibc                                   pfc                                      pfce                            
      pfcae                                 pbdc                                   pu                                      pd                                     pdsc                                    podc                                */
  {GPIO_PORT_0,
   GPIO_PMC0_ACTIVE_VAL,  GPIO_PIPC0_ACTIVE_VAL,  GPIO_PM0_ACTIVE_VAL,  GPIO_PIBC0_ACTIVE_VAL,  GPIO_PFC0_ACTIVE_VAL,   GPIO_PFCE0_ACTIVE_VAL, 
   GPIO_PFCAE0_ACTIVE_VAL, GPIO_PBDC0_ACTIVE_VAL,  GPIO_PU0_ACTIVE_VAL,  GPIO_PD0_ACTIVE_VAL,  GPIO_PDSC0_ACTIVE_VAL,  GPIO_PODC0_ACTIVE_VAL, GPIO_P0_ACTIVE_VAL}
 ,{GPIO_PORT_8,
   GPIO_PMC8_ACTIVE_VAL,  GPIO_PIPC8_ACTIVE_VAL,  GPIO_PM8_ACTIVE_VAL,  GPIO_PIBC8_ACTIVE_VAL,  GPIO_PFC8_ACTIVE_VAL,   GPIO_PFCE8_ACTIVE_VAL, 
   GPIO_PFCAE8_ACTIVE_VAL, GPIO_PBDC8_ACTIVE_VAL,  GPIO_PU8_ACTIVE_VAL,  GPIO_PD8_ACTIVE_VAL,  GPIO_REG_NONE_VAL,  GPIO_PODC8_ACTIVE_VAL, GPIO_P8_ACTIVE_VAL}
 ,{GPIO_PORT_9,
   GPIO_PMC9_ACTIVE_VAL,  GPIO_PIPC9_ACTIVE_VAL,  GPIO_PM9_ACTIVE_VAL,  GPIO_PIBC9_ACTIVE_VAL,  GPIO_PFC9_ACTIVE_VAL,   GPIO_PFCE9_ACTIVE_VAL, 
   GPIO_PFCAE9_ACTIVE_VAL, GPIO_PBDC9_ACTIVE_VAL,  GPIO_PU9_ACTIVE_VAL,  GPIO_PD9_ACTIVE_VAL,  GPIO_REG_NONE_VAL,  GPIO_PODC9_ACTIVE_VAL , GPIO_P9_ACTIVE_VAL}
 
 ,{GPIO_PORT_10,
   GPIO_PMC10_ACTIVE_VAL,  GPIO_PIPC10_ACTIVE_VAL,  GPIO_PM10_ACTIVE_VAL,  GPIO_PIBC10_ACTIVE_VAL,  GPIO_PFC10_ACTIVE_VAL,   GPIO_PFCE10_ACTIVE_VAL, 
   GPIO_PFCAE10_ACTIVE_VAL, GPIO_PBDC10_ACTIVE_VAL,  GPIO_PU10_ACTIVE_VAL,  GPIO_PD10_ACTIVE_VAL,    GPIO_PDSC10_ACTIVE_VAL,  GPIO_PODC10_ACTIVE_VAL, GPIO_P10_ACTIVE_VAL}
 
#if (MCU_PIN ==PIN100) 
 ,{GPIO_PORT_11,
   GPIO_PMC11_ACTIVE_VAL,  GPIO_PIPC11_ACTIVE_VAL,  GPIO_PM11_ACTIVE_VAL,  GPIO_PIBC11_ACTIVE_VAL, GPIO_PFC11_ACTIVE_VAL,   GPIO_PFCE11_ACTIVE_VAL, 
   GPIO_PFCAE11_ACTIVE_VAL,      GPIO_PBDC11_ACTIVE_VAL,  GPIO_PU11_ACTIVE_VAL,  GPIO_PD11_ACTIVE_VAL,  GPIO_PDSC11_ACTIVE_VAL,  GPIO_PODC11_ACTIVE_VAL, GPIO_P11_ACTIVE_VAL}
#endif
};

/*general IO in reset mode*/
const MCU_PORT_REGVAL MCU_IORESET_REGLIST[MCU_PORT_NUM]=
{/*PORT number
      pmc                                   pipc                                    pm                                      pibc                                   pfc                                      pfce                            
      pfcae                                 pbdc                                   pu                                      pd                                     pdsc                                    podc                                */
 {GPIO_PORT_0,
  GPIO_PMC0_RESET_VAL,  GPIO_PIPC0_RESET_VAL,  GPIO_PM0_RESET_VAL,  GPIO_PIBC0_RESET_VAL,  GPIO_PFC0_RESET_VAL,   GPIO_PFCE0_RESET_VAL, 
  GPIO_PFCAE0_RESET_VAL, GPIO_PBDC0_RESET_VAL,  GPIO_PU0_RESET_VAL,  GPIO_PD0_RESET_VAL,  GPIO_PDSC0_RESET_VAL,  GPIO_PODC0_RESET_VAL, GPIO_P0_RESET_VAL}
,{GPIO_PORT_8,
  GPIO_PMC8_RESET_VAL,  GPIO_PIPC8_RESET_VAL,  GPIO_PM8_RESET_VAL,  GPIO_PIBC8_RESET_VAL,  GPIO_PFC8_RESET_VAL,   GPIO_PFCE8_RESET_VAL, 
  GPIO_PFCAE8_RESET_VAL, GPIO_PBDC8_RESET_VAL,  GPIO_PU8_RESET_VAL,  GPIO_PD8_RESET_VAL,  GPIO_REG_NONE_VAL,  GPIO_PODC8_RESET_VAL, GPIO_P8_RESET_VAL}
,{GPIO_PORT_9,
  GPIO_PMC9_RESET_VAL,  GPIO_PIPC9_RESET_VAL,  GPIO_PM9_RESET_VAL,  GPIO_PIBC9_RESET_VAL,  GPIO_PFC9_RESET_VAL,   GPIO_PFCE9_RESET_VAL, 
  GPIO_PFCAE9_RESET_VAL, GPIO_PBDC9_RESET_VAL,  GPIO_PU9_RESET_VAL,  GPIO_PD9_RESET_VAL,  GPIO_REG_NONE_VAL,  GPIO_PODC9_RESET_VAL, GPIO_P9_RESET_VAL}

,{GPIO_PORT_10,
  GPIO_PMC10_RESET_VAL,  GPIO_PIPC10_RESET_VAL,  GPIO_PM10_RESET_VAL,  GPIO_PIBC10_RESET_VAL,  GPIO_PFC10_RESET_VAL,   GPIO_PFCE10_RESET_VAL, 
  GPIO_PFCAE10_RESET_VAL, GPIO_PBDC10_RESET_VAL,  GPIO_PU10_RESET_VAL,  GPIO_PD10_RESET_VAL,    GPIO_PDSC10_RESET_VAL,  GPIO_PODC10_RESET_VAL, GPIO_P10_RESET_VAL}

#if (MCU_PIN ==PIN100)    
,{GPIO_PORT_11,
  GPIO_PMC11_RESET_VAL,  GPIO_PIPC11_RESET_VAL,  GPIO_PM11_RESET_VAL,  GPIO_PIBC11_RESET_VAL, GPIO_PFC11_RESET_VAL,   GPIO_PFCE11_RESET_VAL, 
  GPIO_PFCAE11_RESET_VAL,      GPIO_PBDC11_RESET_VAL,  GPIO_PU11_RESET_VAL,  GPIO_PD11_RESET_VAL,  GPIO_PDSC11_RESET_VAL,  GPIO_PODC11_RESET_VAL, GPIO_P11_RESET_VAL}
#endif
};

/*general IO in standby mode*/
const MCU_PORT_REGVAL MCU_IOSTANDBY_REGLIST[MCU_PORT_NUM]=
{/*PORT number
      pmc                                   pipc                                    pm                                      pibc                                   pfc                                      pfce                            
      pfcae                                 pbdc                                   pu                                      pd                                     pdsc                                    podc                                */
 {GPIO_PORT_0,
  GPIO_PMC0_STANDBY_VAL,  GPIO_PIPC0_STANDBY_VAL,  GPIO_PM0_STANDBY_VAL,  GPIO_PIBC0_STANDBY_VAL,  GPIO_PFC0_STANDBY_VAL,   GPIO_PFCE0_STANDBY_VAL, 
  GPIO_PFCAE0_STANDBY_VAL, GPIO_PBDC0_STANDBY_VAL,  GPIO_PU0_STANDBY_VAL,  GPIO_PD0_STANDBY_VAL,  GPIO_PDSC0_STANDBY_VAL,  GPIO_PODC0_STANDBY_VAL, GPIO_P0_STANDBY_VAL}
,{GPIO_PORT_8,
  GPIO_PMC8_STANDBY_VAL,  GPIO_PIPC8_STANDBY_VAL,  GPIO_PM8_STANDBY_VAL,  GPIO_PIBC8_STANDBY_VAL,  GPIO_PFC8_STANDBY_VAL,   GPIO_PFCE8_STANDBY_VAL, 
  GPIO_PFCAE8_STANDBY_VAL, GPIO_PBDC8_STANDBY_VAL,  GPIO_PU8_STANDBY_VAL,  GPIO_PD8_STANDBY_VAL,  GPIO_REG_NONE_VAL,  GPIO_PODC8_STANDBY_VAL, GPIO_P8_STANDBY_VAL}

,{GPIO_PORT_9,
  GPIO_PMC9_STANDBY_VAL,  GPIO_PIPC9_STANDBY_VAL,  GPIO_PM9_STANDBY_VAL,  GPIO_PIBC9_STANDBY_VAL,  GPIO_PFC9_STANDBY_VAL,   GPIO_PFCE9_STANDBY_VAL, 
  GPIO_PFCAE9_STANDBY_VAL, GPIO_PBDC9_STANDBY_VAL,  GPIO_PU9_STANDBY_VAL,  GPIO_PD9_STANDBY_VAL,  GPIO_REG_NONE_VAL,  GPIO_PODC9_STANDBY_VAL, GPIO_P9_STANDBY_VAL}

,{GPIO_PORT_10,
  GPIO_PMC10_STANDBY_VAL,  GPIO_PIPC10_STANDBY_VAL,  GPIO_PM10_STANDBY_VAL,  GPIO_PIBC10_STANDBY_VAL,  GPIO_PFC10_STANDBY_VAL,   GPIO_REG_NONE_VAL, 
  GPIO_REG_NONE_VAL,      GPIO_PBDC10_STANDBY_VAL,  GPIO_PU10_STANDBY_VAL,  GPIO_PD10_STANDBY_VAL,    GPIO_PDSC10_STANDBY_VAL,  GPIO_PODC10_STANDBY_VAL, GPIO_P10_STANDBY_VAL}

#if (MCU_PIN ==PIN100)    
,{GPIO_PORT_11,
  GPIO_PMC11_STANDBY_VAL,  GPIO_PIPC11_STANDBY_VAL,  GPIO_PM11_STANDBY_VAL,  GPIO_PIBC11_STANDBY_VAL, GPIO_PFC11_STANDBY_VAL,   GPIO_PFCE11_STANDBY_VAL, 
  GPIO_PFCAE11_STANDBY_VAL,      GPIO_PBDC11_STANDBY_VAL,  GPIO_PU11_STANDBY_VAL,  GPIO_PD11_STANDBY_VAL,  GPIO_PDSC11_STANDBY_VAL,  GPIO_PODC11_STANDBY_VAL, GPIO_P11_STANDBY_VAL}
#endif
};

/*#pragma arm section rwdata = "backup_ram_data"*/
MCU_RESET_TYPE sResetReason = MCU_RESET_BY_NONE;
/*#pragma arm section rwdata*/


/* IO configration of General Ports,except for APort andJPort. */
static void McuIoInit2GeneralPort(const MCU_PORT_REGVAL *pReglist);
static MCU_RESET_TYPE GetMcuResetFlag( void );

MCU_RESET_TYPE mcu_get_reset_flag( void );

MCU_RESET_TYPE mcu_get_reset_flag( void )
{
    return sResetReason;
}

/***********************************************************************
*  Name        : mcu_setup_high_clock
*  Description : setup mcu clock in high speed mode, and set cloclk domains related.
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void mcu_setup_high_clock( void )
{
  /* 1. set cpu clock*/
  Clock_Setup_External_Highclock();
}

/***********************************************************************
*  Name        : mcu_setup_low_clock
*  Description : setup mcu clock in low speed mode,
*  				 after this function the mcu speed to LSI frequecy
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void mcu_setup_low_clock( void )
{
  /*1.stop high clock sources*/
  Clock_Stop_External_Highclock();
  /*2.set cpu clock*/
  Clock_Setup_Internal_Lowclock();
}

/***********************************************************************
*  Name        : mcu_io_init_active
*  Description :always called after wakeup from sleep mode
*  Parameter   :None
*  Returns     : None
***********************************************************************/
void mcu_io_init_active( void )
{
    /* Genaral Port */
    McuIoInit2GeneralPort(MCU_IOACTIVE_REGLIST);

    /* JPort */
    JPORT_REG_JPBDC0=GPIO_JPBDC0_ACTIVE_VAL ;
    JPORT_REG_JPU0    =GPIO_JPU0_ACTIVE_VAL ;
    JPORT_REG_JPD0    =GPIO_JPD0_ACTIVE_VAL ;
    GPIO_SetOpenDrain_Port( JP_PORT_0, (U32)GPIO_JPODC0_ACTIVE_VAL);
    JPORT_REG_JPFC0   =GPIO_JPFC0_ACTIVE_VAL; 
    JPORT_REG_JPMC0   =GPIO_JPMC0_ACTIVE_VAL; 
    JPORT_REG_JPM0     =(U8)GPIO_JPM0_ACTIVE_VAL;     
    JPORT_REG_JPIBC0 =GPIO_JPIBC0_ACTIVE_VAL; 
    JPORT_REG_P(0u) =GPIO_JP0_ACTIVE_VAL; 

    /* APort */
    APORT_REG_APBDC(0u)=GPIO_APBDC0_ACTIVE_VAL;
    APORT_REG_APM(0u)    =GPIO_APM0_ACTIVE_VAL;
    APORT_REG_APIBC(0u) =GPIO_APIBC0_ACTIVE_VAL;
    APORT_REG_P(0u) =GPIO_AP0_ACTIVE_VAL;
}

/***********************************************************************
*  Name        : mcu_io_init_reset
*  Description : called after mcu reset
*  Parameter   :None
*  Returns     : None
***********************************************************************/
void mcu_io_init_reset( void )
{
    /* Genaral Port */
    McuIoInit2GeneralPort(MCU_IORESET_REGLIST);

    /* JPort */
    JPORT_REG_JPBDC0=GPIO_JPBDC0_RESET_VAL ;
    JPORT_REG_JPU0    =GPIO_JPU0_RESET_VAL ;
    JPORT_REG_JPD0    =GPIO_JPD0_RESET_VAL ;
    GPIO_SetOpenDrain_Port( JP_PORT_0, (U32)GPIO_JPODC0_RESET_VAL);
    JPORT_REG_JPFC0   =GPIO_JPFC0_RESET_VAL; 
    JPORT_REG_JPMC0   =GPIO_JPMC0_RESET_VAL;  
    JPORT_REG_JPM0     =(U8)GPIO_JPM0_RESET_VAL;     
    JPORT_REG_JPIBC0 =GPIO_JPIBC0_RESET_VAL; 
    JPORT_REG_P(0u) =GPIO_JP0_RESET_VAL; 

    /* APort */
    APORT_REG_APBDC(0u)=GPIO_APBDC0_RESET_VAL;
    APORT_REG_APM(0u)    =GPIO_APM0_RESET_VAL;
    APORT_REG_APIBC(0u) =GPIO_APIBC0_RESET_VAL;
    APORT_REG_P(0u) =GPIO_AP0_RESET_VAL;
}

/***********************************************************************
*  Name        : mcu_io_init_standby
*  Description : IO setting for standby mode
*  Parameter   :None
*  Returns     : None
***********************************************************************/
void mcu_io_init_standby( void )
{
    /* Genaral Port */
    McuIoInit2GeneralPort(MCU_IOSTANDBY_REGLIST);

    /* JPort */
    JPORT_REG_JPBDC0=GPIO_JPBDC0_STANDBY_VAL ;
    JPORT_REG_JPU0    =GPIO_JPU0_STANDBY_VAL ;
    JPORT_REG_JPD0    =GPIO_JPD0_STANDBY_VAL ;
    GPIO_SetOpenDrain_Port( JP_PORT_0,  (U32)GPIO_JPODC0_STANDBY_VAL);
    JPORT_REG_JPFC0   =GPIO_JPFC0_STANDBY_VAL; 
    JPORT_REG_JPMC0   =GPIO_JPMC0_STANDBY_VAL;  
    JPORT_REG_JPM0     =(U8)GPIO_JPM0_STANDBY_VAL;     
    JPORT_REG_JPIBC0 =GPIO_JPIBC0_STANDBY_VAL; 
    JPORT_REG_P(0u) =GPIO_JP0_STANDBY_VAL; 

    /* APort */
    APORT_REG_APBDC(0u)=GPIO_APBDC0_STANDBY_VAL;
    APORT_REG_APM(0u)    =GPIO_APM0_STANDBY_VAL;
    APORT_REG_APIBC(0u) =GPIO_APIBC0_STANDBY_VAL;
    APORT_REG_P(0u) =GPIO_AP0_STANDBY_VAL;
}

/* IO configration of General Ports,except for APort andJPort. */
void McuIoInit2GeneralPort(const MCU_PORT_REGVAL *pReglist)
{
    U8  index=0;
    if(NULL==pReglist)
    {
        /* Error handle*/
    }
    else
    {
        while(index<MCU_PORT_NUM)
        {
            /* initialization */
            PORT_REG_PIBC(pReglist->portNo) = 0;
            PORT_REG_PBDC(pReglist->portNo) = 0;
            PORT_REG_PM(pReglist->portNo) = 0xFFFF;
            PORT_REG_PMC(pReglist->portNo) = 0;
            PORT_REG_PIPC(pReglist->portNo) = 0;
            /* set port filers.not do here */    
            
            /* GPIO to be use as I/O of Peripheral */
            PORT_REG_PBDC(pReglist->portNo)  = (pReglist)->pbdc;
            PORT_REG_PU(pReglist->portNo)     = (pReglist)->pu;
            PORT_REG_PD(pReglist->portNo)     = (pReglist)->pd;
            if((pReglist->portNo!= (U8)GPIO_PORT_8) && (pReglist->portNo!= (U8)GPIO_PORT_9) )
              GPIO_SetDriverStrengthDrain_Port( pReglist->portNo , (U32)(pReglist->pdsc));
            GPIO_SetOpenDrain_Port((U8)(pReglist->portNo) ,(U32) (pReglist->podc));
            
            PORT_REG_PFC(pReglist->portNo)   = pReglist->pfc;
            PORT_REG_PFCE(pReglist->portNo) = pReglist->pfce;
            if((pReglist->portNo== (U8)GPIO_PORT_0) || (pReglist->portNo== (U8)GPIO_PORT_10) ||(pReglist->portNo== (U8)GPIO_PORT_11))
              PORT_REG_PFCAE(pReglist->portNo) = pReglist->pfcae;
            PORT_REG_PIPC(pReglist->portNo) = pReglist->pipc;
            /*TODO pn*/
            PORT_REG_PMC(pReglist->portNo)  = pReglist->pmc;
            PORT_REG_PM(pReglist->portNo)    = pReglist->pm;
            PORT_REG_PIBC(pReglist->portNo) = pReglist->pibc;
            PORT_REG_P(pReglist->portNo) = pReglist->p;
            pReglist++;
            index++;
        }
    }
}

/***********************************************************************
*  Name        : mcu_disable_all_interrupt
*  Description :
*  Parameter   :None
*  Returns     : None
***********************************************************************/
void mcu_disable_all_interrupt(void)
{
  IRQ_IntDisAll();
}

/***********************************************************************
*  Name        : mcu_enable_all_interrupt
*  Description :
*  Parameter   :None
*  Returns     : None
***********************************************************************/
void mcu_enable_all_interrupt(void)
{
    IRQ_IntEnableAll();
}

/***********************************************************************
*  Name        : mcu_sw_reset
*  Description :set mcu reset register to software reset
*  Parameter   :None
*  called: app functions
*  Returns     : None
***********************************************************************/
void mcu_sw_reset( void )
{
  /* software reset register
    bit 31~1 reserved
    bit 0       reset enable. =1 to reset */
    PROTECTED_WRITE(CONTRL_CLUST0_REG_PROTCMD0, CONTRL_CLUST0_REG_PROTS0, MCU_REG_RESET, 0x00000001u);
}

/***********************************************************************
*  Name        : mcu_get_reset_reason
*  Description : Get mcu reset reason of reset register. 
*    If a deepstop caused reset, release IO hold state. 
*  Parameter   : None
*  Returns     : MCU_RESET_TYPE mcu reset type
***********************************************************************/
MCU_RESET_TYPE mcu_get_reset_reason( void )
{
    U32 temp_val = ( U32 )MCU_REG_RESET_REASON;
    MCU_RESET_TYPE ret_val = MCU_RESET_BY_NONE;

    if(temp_val& (1u<<MCU_RESET_BY_SW))
    {
        ret_val = MCU_RESET_BY_SW;
    }
    else if(temp_val&0x02u)
    {
        ret_val = MCU_RESET_BY_WDTA0;
    }
    else if(temp_val&0x04u)
    {
        ret_val = MCU_RESET_BY_WDTA1;
    }
    else if(temp_val&0x08u)
    {
        ret_val = MCU_RESET_BY_CLMA0;
    }
    else if(temp_val&0x10u)
    {
        ret_val = MCU_RESET_BY_CLMA1;
    }
    else if(temp_val&0x20u)
    {
        ret_val = MCU_RESET_BY_CLMA2;
    }
    else if(temp_val&0x40u)
    {
        ret_val = MCU_RESET_BY_LVI;
    }
    else if(temp_val&0x80u)
    {
        ret_val = MCU_RESET_BY_CVM;
    }
    else if(temp_val&0x100u)
    {
        ret_val = MCU_RESET_BY_EXTERNAL;
    }
    else if(temp_val&0x200u)
    {
        ret_val = MCU_RESET_BY_POWERUP;
    }
    else if(temp_val&0x400u)
    {
        ret_val = MCU_RESET_BY_DEEPSTOP;
    }

    /*clear reset flat*/
    MCU_REG_RESETFLAG_CLEAR=0x7ffu;

    sResetReason = ret_val;
    return ret_val;
}

/*Get mcu reset type*/
MCU_RESET_TYPE GetMcuResetFlag( void )
{
    return sResetReason;
}

/***********************************************************************
*  Name        : mcu_io_init_sleep
*  Description :IO setting for sleep mode.
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void mcu_io_init_sleep( void )
{
    mcu_io_init_standby();
}

/***********************************************************************
*  Name        : mcu_io_init_sleep
*  Description :IO setting when power on.
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void mcu_io_init_poweron(void)
{
    mcu_io_init_reset();
}

/***********************************************************************
*  Name        : mcu_io_init_wakeup
*  Description :IO initializing after wakeup from sleep.
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void mcu_io_init_wakeup(void)
{
    mcu_io_init_active();
}
/***********************************************************************
*  Name        : mcu_to_sleep_mode
*  Description :this function to make mcu to stop/ mode
*  Parameter   : type MCU_STOP_MODE,MCU_DEEPSTOP_MODE
*  Returns     : None
***********************************************************************/
void mcu_to_sleep_mode( MCU_SLEEP_TYPE type )
{
    if((MCU_STOP_MODE==type)||(MCU_DEEPSTOP_MODE==type))
    {
        /* Stop all the peripheral functions to stop clock supply. */
        /* do in app layer */
        TAU_setup_deinit();
       
        /* Set wake-up registers. 
        1.clear wake-up factor flag 2.mask non-wakeup factor 3.unmask wakeup factor */
        Stbc_Set_WakeupFactor();
        
        /* Set the clock stop mask and select the clock domains to be stopped and to continue operating.*/
        /*select the clock source to be stopped and to continue operating.   */
        /* if need, select the clock enabled as CPU clock */
        
        if(MCU_STOP_MODE == type)
        {
            /*enter stop mode*/
            Stbc_Run2Stop();
        }
	 else if(MCU_DEEPSTOP_MODE == type)      
        {
            if(Stbc_CyclicRunEnableCheck())
                mcu_setup_low_clock(); 

            /*enter deepstop mode*/
            Stbc_Run2DeepStop();
        }
    }
    else
    {
        /*TODO in sleep mode,using timer factor to wake-up*/
    }
}

/***********************************************************************
*  Name        : mcu_to_wakup_mode
*  Description : mcu handler afer wakeup from stand-by mode.If from deepstop mode, 
                    release IO buffer hold-state first
*  Parameter   : type always be MCU_FULL_MODE
*  Returns     : None
***********************************************************************/
void mcu_to_wakup_mode(MCU_WAKEUP_TYPE type) 
{
    MCU_RESET_TYPE resRsn=GetMcuResetFlag();

    /*Release IO buffer hold*/
    if( MCU_RESET_BY_DEEPSTOP==resRsn)
        Stbc_Clear_IoHoldMode();

    if(MCU_FULL_MODE==type)
    {
        /*Reset wake-up registers. */
        Stbc_Reset_WakeupFactor();
        
        /*2. init clock and CPU Mode*/
        mcu_setup_high_clock();
        
        /*4.TAU setup*/
        TAU_setup_init();
        
        /*5.timer init*/
        
        /*6.pwm init*/
		
        /*7.capture init */   
    }
    else
    {
        /*TODO if nopll .Unused*/
    }
   #if(SERVICE_HOOKS_EN==1u)
        SERVICE_HARDWARE_INIT_HOOK();
   #endif	              
  
}

/***********************************************************************
*  Name        : mcu_set_interrupt_table_address
*  Description :  Not used vector table.
*  Parameter   : addr value
*  Returns     : None
***********************************************************************/
void mcu_set_irq_table_address(U32 addr)
{
    /*Set vector register*/
}
/**************** END OF FILE *****************************************/


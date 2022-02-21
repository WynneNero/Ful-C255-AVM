/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.		           *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									                   *
************************************************************************
* Object        :  clock.c 
* Module        : 
* Instance      : 
* Description   : 5 clock OSC, clock domain
*-----------------------------------------------------------------------
* Version: 
* Date: 
* Author: 
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
------------------------------------------------------------------------
* 0.1      Apr 15,2016   PEI Jingli  Initial 5 clock OSC, and clock domain.
------------------------------------------------------------------------
* 0.2      July 21,2016  PEI Jingli   Refine code structure.
------------------------------------------------------------------------
* 0.3      Aug 10,2016  PEI Jingli  Add MOSC config.
------------------------------------------------------------------------
* 0.4      Aug 26,2016  PEI Jingli  modify ATAUJfre interface.
------------------------------------------------------------------------
* 0.5      Oct 28,2016   PEI Jingli  Set clock domain with STOPMASK
------------------------------------------------------------------------
* 0.6      Nov 25,2016  PEI Jingli  Code architecture for code review
------------------------------------------------------------------------
* 0.7      Dec 19,2016  PEI Jingli Fix error of Clock_GetFrequency_ATAUJ
------------------------------------------------------------------------
* 0.8      Dec 20,2016  PEI Jingli Fix error in Clock_GetFrequency_ATAUJ
*------------------------------------------------------------------------
* 0.9      Jan 24,2017  ZhangJie  Fix Coverity warning.
*------------------------------------------------------------------------
* 1.0      Mar 22,2017  Pei Jingli  Fix settings in low clock working.
=======================================================================*/
#include "Config.h"
#include "Clock_cfg.h"
#include "Clocks.h"
#include "iodefine.h"
#include "wpreg.h"
#include "sys_assert_if.h"

/*  OSC stop of MOSC,SOSC, ROSC
*Parameter : preg write-protect command register
*          pstatus write-protect status register
*          oscReg OSC enable  register
*          oscRegstatus  OSC active status  register
*/
#define CLOCK_STOP(preg,pstatus,oscReg,oscRegstatus)  if(oscRegstatus& CLOCK_STATUS_ACTIVE)  \
                                                                                                   PROTECTED_WRITE(preg, pstatus, oscReg, CLOCK_STOP_TRIGGER);\
                                                                                                 while(oscRegstatus&CLOCK_STATUS_ACTIVE) ;

/* Setting stopmask bit for clocks and domains
*  Parameter: isStpMsk  TRUE ->not stopped in standby mode
*                                   FALSE -> stopped in standby mode
*/
#define CLOCK_SET_STPMSK(stpMskReg, isStpMsk)   if(!isStpMsk)   stpMskReg &=(~CLOCK_STPMASK_EN);\
                                                                                         else stpMskReg |=CLOCK_STPMASK_EN;

static void Clock_SetDomain_ExternalHighClk(void);
/*static void Clock_SetDomain_InternalHighClock(void);*/
static void Clock_SetDomain_InternalLowClock(void);

/***********************************************************************
*  Name         : Clock_MainOsc_SetStpmsK
*  Description : when mask, in stand-by mode MainOsc continue to operate.
*        when unmask, in stand-by mode MainOsc automatically goes to stop.
*        can  automatically restart after wake-up from stand-by.
*  Parameter  : 
*  Returns      : None
***********************************************************************/
void Clock_MainOsc_SetStpmsK(BOOL isMask)
{
    CLOCK_SET_STPMSK(MOSCSTPM, isMask);
}

/***********************************************************************
*  Name         : Clock_MainOsc_Stop
*  Description : stop MainOsc
*  Parameter  : 
*  Returns      : None
***********************************************************************/
void Clock_MainOsc_Stop(void)
{  
    CLOCK_STOP(PROTCMD0, PROTS0, MOSCE, MOSCS);
}

/***********************************************************************
*  Name         : Clock_MainOsc_Start
*  Description :
*  Parameter  : gain ,amplification gain
*                       stab, stabilization counter
*  Returns      : None
***********************************************************************/
void Clock_MainOsc_Start( MOSCC_AMPSEL_MODE gain, U32 stab )
{
    /*Clock_MainOsc_Stop();    stop MOSC if not stopped*/
    if( !(MOSCS&CLOCK_STATUS_ACTIVE ))
    {
      MOSCC = (U32)gain|0x04u;   /*Set amplification gain*/
      
      MOSCST=(U32)stab;/*Set MOsc stabilization time register*/

      /* start MOSC */
      PROTECTED_WRITE(PROTCMD0, PROTS0, MOSCE, CLOCK_START_TRIGGER);

      /* Wait for stable MOSC*/
      while ( !(MOSCS &CLOCK_STATUS_ACTIVE) ); 
    }
}

/***********************************************************************
*  Name         : Clock_SubOsc_Stop
*  Description :
*  Parameter  : 
*  Returns      : None
***********************************************************************/
void Clock_SubOsc_Stop(void)
{
    /* check if MainOsc is running */
    /* stopSOsc */
    /* wait until MainOsc is stopped */
    CLOCK_STOP(PROTCMD0, PROTS0, SOSCE, SOSCS);
}

/***********************************************************************
*  Name         : Clock_SubOsc_start
*  Description :
*  Parameter  : 
*                       stab, stabilization counter
*  Returns      : None
***********************************************************************/
void Clock_SubOsc_Start(  U32 stab )
{
    /*Check if MainOsc is stopped*/
    if( (SOSCS&CLOCK_STATUS_ACTIVE) !=CLOCK_STATUS_ACTIVE)
    {        
      /* Set Osc stabilization time register ,related to HSI/LSI */
      SOSCST=(U32)stab;

      PROTECTED_WRITE(PROTCMD0, PROTS0, SOSCE, CLOCK_START_TRIGGER);
      
      /* Wait for stable MainOsc*/
      while ( !(SOSCS &CLOCK_STATUS_ACTIVE) ); 
    }
}

/***********************************************************************
*  Name         : Clock_HSIOsc_stpmskInStdby
*  Description : when mask, in stand-by mode Osc continue to operate.
*        when unmask, in stand-by mode Osc automatically goes to stop.
*        can  automatically restart after wake-up from stand-by.
*  Parameter  : 
*  Returns      : None
***********************************************************************/
void Clock_HSIOsc_SetStpmsK(BOOL isMask)
{
    CLOCK_SET_STPMSK(ROSCSTPM, isMask);
} 

/***********************************************************************
*  Name         : Clock_HSIOsc_stop
*  Description : high speed internal OSC stop
*  Parameter  : 
*  Returns      : None
***********************************************************************/
void Clock_HSIOsc_Stop(void)
{
    CLOCK_STOP(PROTCMD0, PROTS0, ROSCE, ROSCS);
}

/***********************************************************************
*  Name         : Clock_HSIOsc_start
*  Description : high speed internal OSC start
*  Parameter  : 
*  Returns      : None
***********************************************************************/
void Clock_HSIOsc_start(void)
{
  /*Check if MainOsc is stopped*/
  if(!(ROSCS&CLOCK_STATUS_ACTIVE))
  {  
      /* Start MainOsc (without changing STPMK bit) */
      PROTECTED_WRITE(PROTCMD0, PROTS0, SOSCE, CLOCK_START_TRIGGER);
      /* Wait for stable MainOsc*/
      while ( !(ROSCS &CLOCK_STATUS_ACTIVE) );     
  }
  else 
  {
      /*manul stop needed */
  }
}

/***********************************************************************
*  Name         : Clock_PLL_start
*  Description :
*  Parameter  : pllc: PLLC register params
*  Returns      : None
***********************************************************************/
void Clock_PLL_Start(U32 pllc )
{  
    /*  check if PLL0 is already running */
    /*Clock_PLL_Stop();*/
    if( !(PLLS&CLOCK_STATUS_ACTIVE) )
    {
      /* PLLk control register (PLLC)
           PLLC[16]:CPU PLLCLK selection.Other than ADVANCE,PREMIUM,and Gateway  be sure to wirte 0
             otherwise, write 0/1.
           PLLC[12:11]:Input frequency M[1:0],  Mr val=M[1:0]+1
           PLLC[10:8]:P divider selection PA[2:0],Par
           PLLC[5:0]:Division ratioN[5:0], Nr val=N[2:0]+1 */
      PLLC=pllc; 
      /* Start PLL0  */
      PROTECTED_WRITE(PROTCMD1, PROTS1, PLLE, CLOCK_START_TRIGGER);

      /* wait for stable PLL0 */
      while ( !(PLLS&CLOCK_STATUS_ACTIVE) ) {};
    }
}

/***********************************************************************
*  Name         : Clock_PLL_stop
*  Description :
*  Parameter  : 
*  Returns      : None
***********************************************************************/
void Clock_PLL_Stop(void)
{  
    CLOCK_STOP(PROTCMD1, PROTS1, PLLE, PLLS);  
}

/***********************************************************************
*  Name         : Clock_AWDTA_Set
*  Description : divided clock select 
*  Parameter  : AWDTADCSID,
*  Returns      : None
***********************************************************************/
void Clock_AWDTA_Set(WDTA0_DIV_TYPE clkdiv)
{
    assert_param(IS_RANGE(clkdiv,E_AWDTD_LSI128D,E_AWDTD_LSI1D));

    /* Divided Clock Selection */
    PROTECTED_WRITE(PROTCMD0, PROTS0, CKSC_AWDTAD_CTL, clkdiv);
    while ( CKSC_AWDTAD_ACT != clkdiv )
    {
        /* Wait for set successful */
    }    
} 

/* set stop mask in stand-by mode */
void Clock_AWDTA_SetStpmsK( BOOL isMask)
{
    CLOCK_SET_STPMSK(CKSC_AWDTAD_STPM, isMask);
}

/***********************************************************************
*  Name         : Clock_ATAUJ_Set
*  Description : divided clock select 
*  Parameter  : 
*  Returns      : None
***********************************************************************/
void Clock_ATAUJ_Set(TAUJS_SRCCLK_TYPE sourcClk, TAUJS_DIV_TYPE clkdiv)
{
    assert_param(IS_RANGE(sourcClk,E_ATAUJS_DIS,E_ATAUJS_PPLLCLK2));
    assert_param(IS_RANGE(clkdiv,E_ATAUJ_DIV1,E_ATAUJ_DIV8));

    /* Source Clock Selection */
    PROTECTED_WRITE(PROTCMD0, PROTS0, CKSC_ATAUJS_CTL, sourcClk);
    while ( CKSC_ATAUJS_ACT != sourcClk )
    {
        /* Wait for set successful */
    }

    /* Divided Clock Selection */
    PROTECTED_WRITE(PROTCMD0, PROTS0, CKSC_ATAUJD_CTL, clkdiv);
    while ( CKSC_ATAUJD_ACT != clkdiv )
    {
        /* Wait for set successful */
    }    
} 

/* set stop mask in stand-by mode */
void Clock_ATAUJ_SetStpmsK( BOOL isMask)
{
    CLOCK_SET_STPMSK(CKSC_ATAUJD_STPM, isMask);
}

/***********************************************************************
*  Name         : Clock_ARTCA_Set
*  Description : 
*  Parameter  : 
*  Returns      : None
***********************************************************************/
void Clock_ARTCA_Set(ARTCA_SRCCLK_TYPE sourcClk, ARTCA_DIV_TYPE clkdiv)
{
    assert_param(IS_RANGE(sourcClk,E_ARTCAS_DIS,E_ARTCAS_LSI));
    assert_param(IS_RANGE(clkdiv,E_ARTCA_DIVDIS,E_ARTCA_DIV8));

    /* Source Clock Selection */
    PROTECTED_WRITE(PROTCMD0, PROTS0, CKSC_ARTCAS_CTL, sourcClk);
    while ( CKSC_ARTCAS_ACT != sourcClk )
    {
        /* Wait for set successful */
    }

    /* Divided Clock Selection */
    PROTECTED_WRITE(PROTCMD0, PROTS0, CKSC_ARTCAD_CTL, clkdiv);
    while ( CKSC_ARTCAD_ACT != clkdiv )
    {
        /* Wait for set successful */
    }    
} 

/* set stop mask in stand-by mode */
void Clock_ARTCA_SetStpmsK( BOOL isMask)
{
    CLOCK_SET_STPMSK(CKSC_ARTCAD_STPM, isMask);
}

/***********************************************************************
*  Name         : Clock_AADCA_Set
*  Description : for ADC0
*  Parameter  : 
*  Returns      : None
***********************************************************************/
void Clock_AADCA_Set(AADCA_SRCCLK_TYPE sourcClk, AADCA_DIV_TYPE clkdiv)
{
    assert_param(IS_RANGE(sourcClk,E_AADCAS_DIS,E_AADCAS_PPLLCLK2));
    assert_param(IS_RANGE(clkdiv,E_AADCA_DIVDIS,E_AADCA_DIV2));

    /* Source Clock Selection */
    PROTECTED_WRITE(PROTCMD0, PROTS0, CKSC_AADCAS_CTL, sourcClk);
    while ( CKSC_AADCAS_ACT != sourcClk )
    {
        /* Wait for set successful */
    }

    /* Divided Clock Selection */
    PROTECTED_WRITE(PROTCMD0, PROTS0, CKSC_AADCAD_CTL, clkdiv);
    while ( CKSC_AADCAD_ACT != clkdiv )
    {
        /* Wait for set successful */
    }    
} 

/* set stop mask in stand-by mode */
void Clock_AADCA_SetStpmsK( BOOL isMask)
{
    CLOCK_SET_STPMSK(CKSC_AADCAD_STPM, isMask);
}

/***********************************************************************
*  Name         : Clock_AFOUT_Set
*  Description : divided clock select 
*  Parameter  : AWDTADCSID,
*  Returns      : None
***********************************************************************/
void Clock_AFOUT_Set(AFOUTS_SRCCLK_TYPE sourcClk)
{
    assert_param(IS_RANGE(sourcClk,E_AFOUTS_DIS,E_AFOUTS_PPLLCLK4));

    /* Divided Clock Selection */
    PROTECTED_WRITE(PROTCMD0, PROTS0, CKSC_AFOUTS_CTL, sourcClk);
    while ( CKSC_AFOUTS_ACT != sourcClk )
    {
        /* Wait for set successful */
    }    
} 

/* set stop mask in stand-by mode */
void Clock_AFOUT_SetStpmsK( BOOL isMask)
{
    CLOCK_SET_STPMSK(CKSC_AFOUTS_STPM, isMask);
}

/***********************************************************************
*  Name         : Clock_CPUCLK_Set
*  Description : 
*  Parameter  : sourcClk
*                      div
*  Returns      : None
***********************************************************************/
void Clock_CPUCLK_Set(ICPUCLK_SRCCLK_TYPE sourcClk,ICPUCLK_DIV_TYPE clkdiv)
{
    assert_param(IS_RANGE(sourcClk,E_ICPUCLK_EMG,E_ICPUCLK_CPLLCLK));
    assert_param(IS_RANGE(clkdiv,E_ICPUCLK_DIV1,E_ICPUCLK_DIV8));

    /* Source Clock Selection */
    PROTECTED_WRITE(PROTCMD1, PROTS1, CKSC_CPUCLKS_CTL, sourcClk);
    while ( CKSC_CPUCLKS_ACT!=sourcClk )
    {
        /* Wait for CKSC_CPUCLKS_CTL to set. */
    }

    /* Divided Clock Selection */
    PROTECTED_WRITE(PROTCMD1, PROTS1, CKSC_CPUCLKD_CTL, clkdiv);
    while ( CKSC_CPUCLKD_ACT != clkdiv )
    {
    }
    
} 

/***********************************************************************
*  Name         : Clock_IPERI1_Set
*  Description : 
*  Parameter  : sourcClk
*  Returns      : None
***********************************************************************/
void Clock_IPERI1_Set(IPERI_SRCCLK_TYPE sourcClk)
{
    assert_param(IS_RANGE(sourcClk,E_IPERIS_DISABLE,E_IPERIS_PPLLCLK));

    /* Source Clock Selection */
    PROTECTED_WRITE(PROTCMD1, PROTS1, CKSC_IPERI1S_CTL, sourcClk);
    while ( CKSC_IPERI1S_ACT != sourcClk )
    {
    }
}

/***********************************************************************
*  Name         : Clock_IPERI2_Set
*  Description : 
*  Parameter  : sourcClk
*  Returns      : None
***********************************************************************/
void Clock_IPERI2_Set(IPERI_SRCCLK_TYPE sourcClk)
{
    assert_param(IS_RANGE(sourcClk,E_IPERIS_DISABLE,E_IPERIS_PPLLCLK));

    /* Source Clock Selection */
    PROTECTED_WRITE(PROTCMD1, PROTS1, CKSC_IPERI2S_CTL, sourcClk);
    while ( CKSC_IPERI2S_ACT != sourcClk )
    {
    }
}

/***********************************************************************
*  Name         : Clock_ILIN_Set
*  Description : 
*  Parameter  : 
*  Returns      : None
***********************************************************************/
void Clock_ILIN_Set(ILIN_SRCCLK_TYPE sourcClk, ILIN_DIV_TYPE clkdiv)
{
    assert_param(IS_RANGE(sourcClk,E_ILIN_DIS,E_ILIN_PPLLCLK2));
    assert_param(IS_RANGE(clkdiv,E_ILIN_DIV1,E_ILIN_DIV8));

    /* Source Clock Selection */
    PROTECTED_WRITE(PROTCMD1, PROTS1, CKSC_ILINS_CTL, sourcClk);
    while ( CKSC_ILINS_ACT != sourcClk )
    {
        /* Wait for set successful */
    }

    if(E_ILIN_DIS!=sourcClk)
    {
        /* Divided Clock Selection */
        PROTECTED_WRITE(PROTCMD1, PROTS1, CKSC_ILIND_CTL, clkdiv);
        while ( CKSC_ILIND_ACT != clkdiv )
        {
            /* Wait for set successful */
        }
    }
} 

/* set stop mask in stand-by mode */
void Clock_ILIN_SetStpmsK( BOOL isMask)
{
    CLOCK_SET_STPMSK(CKSC_ILIND_STPM, isMask);
}


/***********************************************************************
*  Name         : Clock_IADCA_Set
*  Description : for ADC1 
*  Parameter  : 
*  Returns      : None
***********************************************************************/
void Clock_IADCA_Set(AADCA_SRCCLK_TYPE sourcClk, AADCA_DIV_TYPE clkdiv)
{
    assert_param(IS_RANGE(sourcClk,E_AADCAS_DIS,E_AADCAS_PPLLCLK2));
    assert_param(IS_RANGE(clkdiv,E_AADCA_DIV1,E_AADCA_DIV2));

    /* Source Clock Selection */
    PROTECTED_WRITE(PROTCMD1, PROTS1, CKSC_IADCAS_CTL, sourcClk);
    while ( CKSC_IADCAS_ACT != sourcClk )
    {
        /* Wait for set successful */
    }

    /* Divided Clock Selection */
    PROTECTED_WRITE(PROTCMD1, PROTS1, CKSC_IADCAD_CTL, clkdiv);
    while ( CKSC_IADCAD_ACT != clkdiv )
    {
        /* Wait for set successful */
    }    
} 

/***********************************************************************
*  Name         : Clock_ICAN_Set
*  Description : 
*  Parameter  : 
*  Returns      : None
***********************************************************************/
void Clock_ICAN_Set(ICAN_SRCCLK_TYPE sourcClk, ICANOSC_DIV_TYPE clkdiv)
{
    assert_param(IS_RANGE(sourcClk,E_ICANS_DIS,E_ICANS_CPUCLK));
    assert_param(IS_RANGE(clkdiv,E_ICANOSCD_DIS,E_ICANOSCD_MOSC2));

    /* Source Clock Selection */
    PROTECTED_WRITE(PROTCMD1, PROTS1, CKSC_ICANS_CTL, sourcClk);
    while ( CKSC_ICANS_ACT != sourcClk )
    {
        /* Wait for set successful */
    }

    /* Divided Clock Selection */
    PROTECTED_WRITE(PROTCMD1, PROTS1, CKSC_ICANOSCD_CTL, clkdiv);
    while ( CKSC_ICANOSCD_ACT != clkdiv )
    {
        /* Wait for set successful */
    }    
} 
/* set stop mask in stand-by mode */
void Clock_ICAN_SetStpmsK( BOOL isMask)
{
    CLOCK_SET_STPMSK(CKSC_ICANS_STPM, isMask);
}

/* set stop mask in stand-by mode.
 bit1 should be 1*/
void Clock_ICANOSCD_SetStpmsK( BOOL isMask)
{
    CLOCK_SET_STPMSK(CKSC_ICANOSCD_STPM, isMask);
}

/***********************************************************************
*  Name         : Clock_ICSIS_Set
*  Description : 
*  Parameter  : sourcClk
*  Returns      : None
***********************************************************************/
void Clock_ICSIS_Set(ICSI_SRCCLK_TYPE sourcClk)
{
    /* Source Clock Selection */
    PROTECTED_WRITE(PROTCMD1, PROTS1, CKSC_ICSIS_CTL, sourcClk);
    while ( CKSC_ICSIS_ACT != sourcClk )
    {
        /* Wait for set successful */
    }
}

/***********************************************************************
*  Name         : Clock_Setup_External_Highclock
*  Description : set CPU clock used external osc  and PLL.also setting HSI and PERI1/2
*  Parameter  : hclk, select MOSC,CPU clock,Peripheral clocks frequency from external_HclockTable[]    
*                               = EXT_H_CPUCLK0 to EXT_H_CPUCLK3
*
*  Returns     : TRUE
***********************************************************************/
void Clock_Setup_External_Highclock()	
{  
  MOSCC_AMPSEL_MODE moscSel;
  U32 pllFreq;
  U32 pllPar;

  assert_param(IS_RANGE(EXTERNAL_OSC_HZ, 0, 24000000U)); /* 1hz~24mhz */
  assert_param(IS_RANGE(EXTERNAL_PLLCCLK_NR, 1U, 64U)); 
  assert_param(IS_RANGE(EXTERNAL_PLLCCLK_MR, 1U, 3U));
  /*assert_param(IS_RANGE(EXTERNAL_PLLCCLK_PAR, ));*/
  if((4U!=EXTERNAL_PLLCCLK_PAR)&&(6U!=EXTERNAL_PLLCCLK_PAR)&&(8U!=EXTERNAL_PLLCCLK_PAR)&&(16U!=EXTERNAL_PLLCCLK_PAR))
    assert_param(0);
  
  /* calculate  MOSC and PLLC register value */
  if(EXTERNAL_OSC_HZ<=8000000U)
    moscSel =E_LOW_8MUP;
  else if((8000000<EXTERNAL_OSC_HZ)||(EXTERNAL_OSC_HZ<=16000000U))
    moscSel =E_MIDL_16MUP;
  else if((16000000<EXTERNAL_OSC_HZ)||(EXTERNAL_OSC_HZ<=20000000U))
    moscSel =E_MIDH_20MUP;
  else if((20000000<EXTERNAL_OSC_HZ)||(EXTERNAL_OSC_HZ<=24000000U))
    moscSel =E_HIGH_24MUP;

  if(4==EXTERNAL_PLLCCLK_PAR)
    pllPar=CGC_PLLC_Par4;
  else if(6==EXTERNAL_PLLCCLK_PAR)
    pllPar=CGC_PLLC_Par6;
  else if(8==EXTERNAL_PLLCCLK_PAR)
    pllPar=CGC_PLLC_Par8;
  else if(16==EXTERNAL_PLLCCLK_PAR)
    pllPar=CGC_PLLC_Par16;

  pllFreq= (CGC_PLLC_OUTBSEL_0|CGC_PLLC_Nr(EXTERNAL_PLLCCLK_NR)|CGC_PLLC_Mr(EXTERNAL_PLLCCLK_MR)|pllPar);

  /* Start MainOSC 
  stabilization time to max (8,19 ms),the base time is 1/fRH:65535/8us */
  Clock_MainOsc_Start(moscSel,0xFFFFU);

  /* Set and Start PLL, CPLL=PPLL */
  Clock_PLL_Start(pllFreq);

  /* --config clock domain used  CPLL --*/
  /* CPUCLK, source clk CPUPLL, divider 1 =80MHZ */
  Clock_CPUCLK_Set(E_ICPUCLK_CPLLCLK,E_ICPUCLK_DIV1);

  /*clk IPERI1, fre=CPUCLK/2=40MHZ */
  Clock_IPERI1_Set(E_IPERIS_CPUCLK2);
  /*clk IPERI2*/
  Clock_IPERI2_Set(E_IPERIS_CPUCLK2);

  Clock_SetDomain_ExternalHighClk();
}

/***********************************************************************
*  Name        : Clock_Stop_External_Highclock
*  Description : stop clock sources about external_highclock
*         before stop a clock source,make sure stopping its' clock domain first.
*  Parameter : None 
*  Returns    : None
***********************************************************************/
void Clock_Stop_External_Highclock()
{
    /* Set clock domains:external clock to internal low */
    Clock_SetDomain_InternalLowClock();

/* unused for project 
    Clock_PLL_Stop();  
    Clock_MainOsc_SetStpmsK(FALSE); 
*/
}

/***********************************************************************
*  Name        : Clock_Setup_Internal_Highclock
*  Description : set CPU clock used internal 8MHZ HSI
*  Parameter   : CPUCLK_BY_HSI_HZ 
*  Returns     : None
***********************************************************************/
void Clock_Setup_Internal_Highclock( void )
{
    ICPUCLK_DIV_TYPE divReg=E_ICPUCLK_DIV1;      
    U8 div=HSI_OSC_HZ/CPUCLK_BY_HSI_HZ;
    assert_param(((1U==div) ||(2U==div) ||(4U==div)||(8U==div)));

    if(1U==div)
      divReg=E_ICPUCLK_DIV1;  
    else if(2U==div)
      divReg=E_ICPUCLK_DIV2;  
    else if(4U==div)
      divReg=E_ICPUCLK_DIV4;  
    else if(8U==div)
      divReg=E_ICPUCLK_DIV8;  
  
    /* Start HighSpeedIntOsc */
    Clock_HSIOsc_start();
    
    /* cpuclk freq CPU_CLK_FREQ_HZ */
    Clock_CPUCLK_Set(E_ICPUCLK_EMG,divReg);
    
    /*clk IPERI1, fre=CPUCLK/2=40MHZ*/
    /*Clock_IPERI1_Set(E_IPERIS_CPUCLK2);   if in mcu run mode,that's needed*/
    /*clk IPERI2*/
    /*Clock_IPERI2_Set(E_IPERIS_CPUCLK2);*/
}

/***********************************************************************
*  Name        : Clock_Stop_Internal_Highclock
*  Description : 
*         stop clock sources about internall high clock
*         before stop a clock source,make sure stopping its' clock domain first.
*  Parameter   : 
*  Returns     : None
***********************************************************************/
void Clock_Stop_Internal_Highclock()
{
  /*Clock_HSIOsc_Stop();*/
  Clock_HSIOsc_SetStpmsK(FALSE); /*if in mcu stand-by mode*/
}
/***********************************************************************
*  Name        : Clock_Setup_Internal_Lowclock
*  Description : set CPU clock used internal24kMHZ LSI.First HSI should be inactive. 
*  Parameter  : 
*                cpu clock    = CPU_CLK_FREQ_HZ
*  Returns     : None
***********************************************************************/
void Clock_Setup_Internal_Lowclock( void )
{
  ICPUCLK_DIV_TYPE divReg=E_ICPUCLK_DIV1;      
  U8 div=LSI_OSC_HZ/CPUCLK_BY_LSI_HZ;
  assert_param(((1U==div) ||(2U==div) ||(4U==div)||(8U==div)));
    
  div=LSI_OSC_HZ/CPUCLK_BY_LSI_HZ;
  if(1U==div)
    divReg=E_ICPUCLK_DIV1;  
  else if(2U==div)
    divReg=E_ICPUCLK_DIV2;  
  else if(4U==div)
    divReg=E_ICPUCLK_DIV4;  
  else if(8U==div)
    divReg=E_ICPUCLK_DIV8;  
    
  /*first Stop HighSpeedIntOsc */
  Clock_HSIOsc_SetStpmsK(FALSE);
  
  /* config clock domain used  LSI */
  /* cpuclk freq CPU_CLK_FREQ_HZ */
  Clock_CPUCLK_Set(E_ICPUCLK_EMG,divReg);

  /*clk IPERI1, fre=CPUCLK/2=40MHZ*/
  /*Clock_IPERI1_Set(E_IPERIS_CPUCLK2);     if in mcu run mode,that's needed*/
  /*clk IPERI2*/
  /*Clock_IPERI2_Set(E_IPERIS_CPUCLK2);*/
}

/***********************************************************************
*  Name        : Clock_stop_internal_lowclock
*  Description : LSI cannot be inactive. 
*         called before setup cpu clock with HSI/PLL. 
*         before stop a clock source,make sure stopping its' clock domain first.
*  Parameter   : 
*  Returns     : None
***********************************************************************/
void Clock_Stop_Internal_Lowclock()
{
  /*LSI cannot be inactive.
  If selected MOSC as cpuclock,or HSI is active,LSI willnot works as cpuclock.*/
}

/***********************************************************************
*  Name        : Clock_SetDomain_ExternalHighClk
*  Description :All clcok domains setting when cpu clock used PLL. 
*  Parameter  : None
*  Returns     : None
***********************************************************************/
void Clock_SetDomain_ExternalHighClk()
{
  /* A-watchdog:LSI by 128 division,frequency=240k/128,stopped in stand-by mode*/
/*  Clock_AWDTA_Set(DOMAIN_AWDTD);	//wdg is always LS IntOsc*/
/*  Clock_AWDTA_SetStpmsK(DOMAIN_AWDT_STPMSK);*/
  
  /*ATAUJ:LSI by 1 division,frequency=240khz,stopped  in stand-by mode*/
  Clock_ATAUJ_Set(DOMAIN_ATAUJS, DOMAIN_ATAUJD);
  Clock_ATAUJ_SetStpmsK(DOMAIN_ATAUJ_STPMSK);
    
  /*AADC: PPLL2 by 1 division,frequency=40Mhz,stopped  in stand-by mode*/
  Clock_AADCA_Set(DOMAIN_ADCAS, DOMAIN_ADCAD);
  Clock_AADCA_SetStpmsK(DOMAIN_ADCA_STPMSK);
  
  /*ILIN:CPUCLK2 by 1 division,frequency=40Mhz,stopped  in stand-by mode*/
  Clock_ILIN_Set(DOMAIN_ILINS,DOMAIN_ILIND);
  Clock_ILIN_SetStpmsK(DOMAIN_ILIN_STPMSK);
  
  /*ICAN:PLLCLK by 1 division,frequency=80Mhz,stopped  in stand-by mode*/
  Clock_ICAN_Set(DOMAIN_ICANS,DOMAIN_ICANOSCD);
  Clock_ICAN_SetStpmsK(DOMAIN_ICAN_STPMSK);
  Clock_ICANOSCD_SetStpmsK(DOMAIN_ICANOSC_STPMSK);
  
  /*ICSI:PLLCLK by 1 division,stopped  in stand-by mode*/
  Clock_ICSIS_Set(DOMAIN_ICSIS);

#if 0  /* for unused */
  /*ARTC:disabled*/
  Clock_ARTCA_Set(DOMAIN_RTCS, DOMAIN_RTCD);
  Clock_ARTCA_SetStpmsK(DOMAIN_RTC_STPMSK);

  /*AFOUT: disabled*/
  Clock_AFOUT_Set(DOMAIN_FOUTS);
  Clock_AFOUT_SetStpmsK(DOMAIN_FOUT_STPMSK);
  
  /*IADC:disabled*/
  Clock_IADCA_Set(DOMAIN_IADCS,DOMAIN_IADCD);
#endif
}

#if 0 /*USED_HSI_FOR_CPUCLK*/
/***********************************************************************
*  Name        : Clock_setdomain_InternalHighClock
*  Description :All clcok domains setting when cpu clock used HSI. 
*  Parameter  : None
*  Returns     : None
***********************************************************************/
void Clock_SetDomain_InternalHighClock()
{
    /* A-watchdog:LSI by 128 division,frequency=240Khz/128stopped in stand-by mode*/
/*    Clock_AWDTA_Set(DOMAIN_AWDTD);*/
/*    Clock_AWDTA_SetStpmsK(DOMAIN_AWDT_STPMSK);*/
    
    /*ATAUJ:LSI by 1 division,frequency=240Khz,stopped  in stand-by mode*/
    Clock_ATAUJ_Set(DOMAIN_ATAUJS, DOMAIN_ATAUJD);
    Clock_ATAUJ_SetStpmsK(DOMAIN_ATAUJ_STPMSK);
    
    /*ARTC:disabled*/
    Clock_ARTCA_Set(DOMAIN_RTCS, DOMAIN_RTCD);
    Clock_ARTCA_SetStpmsK(DOMAIN_RTC_STPMSK);
    
    /*AADC: HSI by 1 division,stopped  in stand-by mode*/
    Clock_AADCA_Set(DOMAIN_ADCAS, DOMAIN_ADCAD);
    Clock_AADCA_SetStpmsK(DOMAIN_ADCA_STPMSK);
    
    /*AFOUT: disabled*/
    Clock_AFOUT_Set(DOMAIN_FOUTS);
    Clock_AFOUT_SetStpmsK(DOMAIN_FOUT_STPMSK);
    
    /*ILIN:disabled*/
    Clock_ILIN_Set(DOMAIN_ILINS,DOMAIN_ILIND);
    Clock_ILIN_SetStpmsK(DOMAIN_ILIN_STPMSK);
    
    /*IADC:disabled*/
    Clock_IADCA_Set(DOMAIN_IADCS,DOMAIN_IADCD);
    
    /*ICAN:disabled*/
    Clock_ICAN_Set(DOMAIN_ICANS,DOMAIN_ICANOSCD);
    Clock_ICAN_SetStpmsK(DOMAIN_ICAN_STPMSK);
    Clock_ICANOSCD_SetStpmsK(DOMAIN_ICANOSC_STPMSK);
    
    /*ICSI:disabled*/
    Clock_ICSIS_Set(DOMAIN_ICSIS);
}
#endif

/***********************************************************************
*  Name        : Clock_setdomain_InternalLowClock
*  Description :All clcok domains setting when cpu clock used LSI. 
*  Parameter  : None
*  Returns     : None
***********************************************************************/
void Clock_SetDomain_InternalLowClock()
{
  /* A-watchdog:LSI by 128 division,frequency=240Khz/128,stopped in stand-by mode*/
/*  Clock_AWDTA_Set(E_AWDTD_LSI128D);*/
/*  Clock_AWDTA_SetStpmsK(FALSE);*/
#if 0  /* We do nothing in stand-by mode */
  /*ATAUJ:LSI by 1 division,frequency=240Khz,stopped  in stand-by mode*/
  Clock_ATAUJ_Set(E_ATAUJS_LSI240KHZ, E_ATAUJ_DIV1);
  Clock_ATAUJ_SetStpmsK(DOMAIN_ATAUJ_STPMSK);
  
  /*ARTC:disabled*/
  Clock_ARTCA_Set(E_ARTCAS_DIS, E_ARTCA_DIVDIS);
  Clock_ARTCA_SetStpmsK(FALSE);
  
  /*AADC: disabled*/
  Clock_AADCA_Set(E_AADCAS_DIS, E_AADCA_DIVDIS);
  Clock_AADCA_SetStpmsK(FALSE);
  
  /*AFOUT: disabled*/
  Clock_AFOUT_Set(E_AFOUTS_DIS);
  Clock_AFOUT_SetStpmsK(FALSE);
  
  /*ILIN:disabled*/
  Clock_ILIN_Set(E_ILIN_DIS,E_ILIN_DIV1);
  Clock_ILIN_SetStpmsK(FALSE);
  
  /*IADC:disabled*/
  Clock_IADCA_Set(E_AADCAS_DIS,E_AADCA_DIVDIS);
  
  /*ICAN:disabled*/
  Clock_ICAN_Set(E_ICANS_DIS,E_ICANOSCD_DIS);
  Clock_ICAN_SetStpmsK(FALSE);
  Clock_ICANOSCD_SetStpmsK(FALSE);
  
  /*ICSI:disabled*/
  Clock_ICSIS_Set(E_ICSIS_DIS);

  /*clk IPERI1*/
  Clock_IPERI1_Set(E_IPERIS_DISABLE);
  /*clk IPERI2*/
  Clock_IPERI2_Set(E_IPERIS_DISABLE);
  /*If High Speed Internal clk works,cpuclk is HSI,frequency=8MHZ.If HSI not works,cpuclk is LowSpeed Internal clk,frequency=240KHZ.*/
  Clock_CPUCLK_Set(E_ICPUCLK_EMG,E_ICPUCLK_DIV1);
#endif
}

/***********************************************************************
*  Name        : Clock_GetFrequency_ATAUJ
*  Description :Get frequency of clock domain TAUJ. unit by HZ
*  Parameter  : None
*  Returns     :  frequency value by HZ
***********************************************************************/
U32 Clock_GetFrequency_ATAUJ(void)
{
    U8 div=0;
    U32 value=0;
  
    assert_param(IS_RANGE(DOMAIN_ATAUJD,E_ATAUJ_DIS,E_ATAUJ_DIV8));
    assert_param(IS_RANGE(DOMAIN_ATAUJS,E_ATAUJS_DIS,E_ATAUJS_PPLLCLK2));
   
    if((E_ATAUJ_DIS==DOMAIN_ATAUJD) ||(E_ATAUJS_DIS==DOMAIN_ATAUJS))
    {
      /*clock disabled*/
    }   
    else
    {
        if(E_ATAUJ_DIV1==DOMAIN_ATAUJD)  /*divider value*/
            div =1U;
        else if(E_ATAUJ_DIV2==DOMAIN_ATAUJD)
            div =2U;
        else if(E_ATAUJ_DIV4==DOMAIN_ATAUJD)
            div =4U;
        else if(E_ATAUJ_DIV8==DOMAIN_ATAUJD)
            div =8U;
   
        /* generate clock by divider*/
        if(E_ATAUJS_LSI240KHZ==DOMAIN_ATAUJS)
            value=LSI_OSC_HZ/div ;
        else  if(E_ATAUJS_HSI8MHZ==DOMAIN_ATAUJS)
            value=HSI_OSC_HZ/div ;
        else  if(E_ATAUJS_MOSCFX==DOMAIN_ATAUJS)
            value=EXTERNAL_OSC_HZ/div ;
        else  if(E_ATAUJS_PPLLCLK2==DOMAIN_ATAUJS)
            value=(CPUCLK_NORMAL_HZ/2U)/div;
    }
   
    return value;
}


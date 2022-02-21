/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.		           *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									                   *
************************************************************************
* Object        :  OSTM.c 
* Module        : OS timer operation
* Instance      : 
* Description   : 
*-----------------------------------------------------------------------
* Version: 
* Date: 
* Author: 
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
* ----------------------------------------------------------------------
* 0.1  4 15,2016     Pei JL     Initial version
*------------------------------------------------------------------------
* 0.2  Jan 24,2017  ZhangJie Fix Coverity warning.
*-----------------------------------------------------------------------
* 0.3  Apr 1,2017  PEI Jingli   Fix include files.
* ----------------------------------------------------------------------
===============================================================*/

/*============================================================================
* Includes
============================================================================*/
#include "Cpu.h"
#include "Ostm.h"
#include "sys_assert_if.h"


/***********************************************************************
*  Name        : Ostm0_init
*  Description : int CMP reg,set  operating mode and interruput fo OSTM0
*  Parameter   : opratMode: as OSTMCTL_OPRTYPE
*                        intEnble: Interrupt on CounterStart disabled or enabled
*                        pllclk_hz and tick_per_sec:  setting OSTM cycle to 1ms
*  Returns     : None
***********************************************************************/
void Ostm0_init(U32 pllclk_hz, U32  tick_per_sec, OSTMCTL_OPRTYPE opratMode, BOOL intEnble)
{
    U32  cnts;

    assert_param(IS_RANGE(opratMode, E_INTVLTIM_MODE, E_FREERUN_MODE));

    OSTM0_REG_EMU= 0x00u;    /*OSTMnEMU:Counter is continued when Debugger takes control. EPC.SVSTOP = 0*/
    /*OSTM0 Cycle=1ms*/
    cnts = ((pllclk_hz/2u/1000u) *tick_per_sec)-1u;	
    /* if timer is running, stop it.in free rum mode be ignored */
    if(IsOSTM0_ENBLED()) 
        Ostm0_stop();
    
    /* configure operating system timer */
    OSTM0_REG_CTL=opratMode|intEnble;
    OSTM0_REG_CMP=cnts;   /*OSTM0 Cycle=(cnts+1)/((cpupll_hz/2)*1000) =tick_per_sec ms=1ms*/
}

/***********************************************************************
*  Name        : Ostm0_start
*  Description :
*  Parameter   :
*  Returns     : None
***********************************************************************/
void Ostm0_start(void)
{
    /* Start the counter */
    OSTM0_REG_TS=E_STARTSTP_EN;
    while(!IsOSTM0_ENBLED())
    { /*wait until OSTM0 goes to stable*/
    }
}

/***********************************************************************
*  Name        : Ostm0_stop
*  Description :
*  Parameter   :
*  Returns     : None
***********************************************************************/
void Ostm0_stop(void)
{  
    OSTM0_REG_TT=E_STARTSTP_EN;
    while(IsOSTM0_ENBLED())
    { /*wait until OSTM0 disabled*/
    }
}

/***********************************************************************
*  Name        : Ostm0_compare
*  Description : set the value of OSTMnCMP register
*  Parameter   :
*  Returns     : None
***********************************************************************/
void Ostm0_compare(U32 val )
{
    OSTM0_REG_CMP=val;
}

/***********************************************************************
*  Name        : ISR_OSTM0func
*  Description : OSTM ISR
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void ISR_OSTM0func(void)
{
	static U32 ostm_cnt=0u;
	
	ostm_cnt++;
}


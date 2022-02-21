/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.		           *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									                   *
************************************************************************
* Object        :  stbc.c 
* Module        : 
* Instance      : 
* Description   : mcu stand-by mode handler
*-----------------------------------------------------------------------
* Version: 
* Date: 
* Author: 
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
------------------------------------------------------------------------
* 0.1	   Jun 26,2016   PEI Jingli  Initial 5 clock OSC, and clock domain.
------------------------------------------------------------------------
* 0.2	   July 21,2016  PEI Jingli  Refine code structure.
*-----------------------------------------------------------------------
* 0.3	   Dec 29,2016  PEI Jingli  Modify for codereview result
*-----------------------------------------------------------------------
* 0.4	   Jan 06,2016  PEI Jingli  Add description of interfaces
*-----------------------------------------------------------------------
* 0.5	   Jan 11,2017  ZhangJie  Remove infinited while loop to avoid compile warning,
*                                                 and add parentheses and add u for constant value to avoid Coverity warning.
*----------------------------------------------------------------------
* 0.6          Jan 24,2017    ZhangJie     Fix Coverity warning phase2.
*-----------------------------------------------------------------------
* 0.7	   Mar 22,2016  PEI Jingli  Add checking of cyclic-run mode using.
======================================================================*/

/*============================================================================
* Includes
============================================================================*/
#include "Define.h"
#include "stbc.h"
#include "stbc_cfg.h"
#include "wpreg.h"
#include "Sig_Combine.H"
#include "Signal_if.h"

static void SetStopModeRegister(void);
static void SetDeepstopModeRegister(void);

/***********************************************************************************************************************
* Function Name: Stbc_Clear_IoHoldMode
* Description  : After wakeup from deepstop mode, clears I/O hold flag to release I/O buffer.
* Parameters   : None
* Return Value : None
***********************************************************************************************************************/
void Stbc_Clear_IoHoldMode(void)
{
    PROTECTED_WRITE(CONTRL_CLUST0_REG_PROTCMD0, CONTRL_CLUST0_REG_PROTS0, 
                                                                                  STBC_REG_IOHOLD, 0x00000000UL);
}

/***********************************************************************************************************************
* Function Name: SetStopModeRegister
* Description  : set reg for transit to stop mode.
* Parameters   : None
* Return Value : None 
***********************************************************************************************************************/
void SetStopModeRegister(void)
{
    /*do*/
    { /*set bit0=1 to trigger the stop*/
        CLUST0_PROTCMD0_WRITEENABLE();
        STBC_REG_STPT = 0x00000001U;
        STBC_REG_STPT = ~0x00000001U;
        STBC_REG_STPT = 0x00000001U;
    }
   /*while ( CLUST0_PROTS0_ISERR() );*/    /*may case stop error*/

    while( STBC_REG_STPT == 0x00000001U )
    {}
}

/***********************************************************************************************************************
* Function Name: SetDeepstopModeRegister
* Description  : set reg for transit to deepstop mode.
* Parameters   :
* Return Value : 
***********************************************************************************************************************/
void SetDeepstopModeRegister(void)
{
    /*do*/
    { /*set bit1=1 to trigger the deep stop*/
        CLUST0_PROTCMD0_WRITEENABLE();
        STBC_REG_PSC= 0x00000002U;
        STBC_REG_PSC = ~0x00000002U;
        STBC_REG_PSC = 0x00000002U;
    }
    /*while ( CLUST0_PROTS0_ISERR() );*/     /*may case stop error*/

    while(STBC_REG_PSC==0x00000002U)
    {}
}

/***********************************************************************
*  Name        : Stbc_Run2Stop
*  Description : mcu mode from RUN to STOP
*       1. config wakeup factor
*       2. close some clock domains for power reduction.
*
*       3. change CPU clock source. using HSI
*
*  Parameter   :
*  Returns     : None
***********************************************************************/
void Stbc_Run2Stop(void)
{
    /* Stop all the peripheral functions to stop clock supply. */
  
    /* Interrupt disable */
    
    /* 1-clear all interrupt flags, 2-mask interrupt of non-wakeup factor 3- unmask interrupt of wakup factor  */
  
    /* Set wake-up registers. 
    1.clear wake-up factor flag 2.mask non-wakeup factor 3.unmask wakeup factor */
     
    /* Set the clock stop mask and select the clock domains to be stopped and to continue operating.*/
    
    /*select the clock source to be stopped and to continue operating.   */
  
    /* select the clock enabled as CPU clock */
  
    /* Shift to STOP mode */
    SetStopModeRegister();
  
    /* Interrupt enable */
  
   /* Check wakeup factors */
}

/***********************************************************************
*  Name        : Stbc_Run2Stop
*  Description : mcu mode from RUN to STOP
*       1. config wakeup factor
*       2. close some clock domains for power reduction.
*
*       3. change CPU clock source. using HSI
*
*  Parameter   :None
*  Returns     : None
***********************************************************************/
void Stbc_Run2DeepStop(void)
{
    /* Stop all the peripheral functions to stop clock supply. */
   
    /* Interrupt disable */
    
    /* clear all interrupt flags */
  
    /* Set wake-up registers. */
   
    /* Set the clock stop mask and select the clock domains to be stopped and to continue operating.*/
   
    /* select the clock enabled as CPU clock */
   
    /* clear all reset flags */
   
    /* Shift to DEEPSTOP mode */
    SetDeepstopModeRegister();

}

/***********************************************************************
*  Name        : Stbc_CyclicRunHandler
*  Description : operations in cyclic run mode
*  Parameter   :None
*  Returns     : None
***********************************************************************/
//#pragma section text ".ram_text"
void Stbc_CyclicRunHandler( void )
{

    /*while( 1U )*/
    /*{*/
        /* Check wakeup factor 1 (INTTAUJ0I1)  */

        /* Set the port of the ISO domain again.                 */

        /* Set the peripheral function of the ISO domain again.  */

        /* Release a keeping state of the input and output terminal.  */

        /* Check wakeup factor 2. (INTTAUJ0I2)  */
    /*}*/
}
/*#pragma section default*/

/***********************************************************************
*  Name        : Stbc_CyclicRunEnableCheck
*  Description : Check cyclic run mode can be retained or not
*  Parameter   :None
*  Returns     : None
***********************************************************************/
BOOL Stbc_CyclicRunEnableCheck(void)
{
    BOOL bRet =FALSE;
    if(0xFFFFFFFFu !=STBC_REG_WUFMSK20)
         bRet =TRUE;

    return bRet;
}

/***********************************************************************************************************************
* Function Name: Stbc_Set_WakeupFactor
* Description  : Before sleep,set wakeup factor to registers.
* Parameters   : 
* Return Value : None
***********************************************************************************************************************/
void Stbc_Set_WakeupFactor(void)
{
	U8 Acctemp=0; 
	U8 Voltemp=0;
  	/* clear all wake up factors */
  	STBC_REG_WUFC0 = 0xffffffffu;
  	STBC_REG_WUFC20 = 0xffffffffu;
  	STBC_REG_WUFC_ISO0 = 0xffffffffu;

//  	CS_SIG_SyncReceive((U16)SIG_ACC_DI_STATUS, &Acctemp);
//  	CS_SIG_SyncReceive((U16)SIG_HCANPWR_DI_STATUS, &Voltemp);
	if(Acctemp == TRUE)
	{
		if((Voltemp == V_L_ABNORMAL) || (Voltemp == V_H_ABNORMAL))
		{
			/* enable wakeup factor INTP3*/
  			STBC_REG_WUFMSK0 = (STBC_CFG_STOP_WUFMSK0 & 0xfffffdffu); 
  			STBC_REG_WUFMSK20 = STBC_CFG_STOP_WUFMSK20; 
  			STBC_REG_WUFMSK_ISO0 = STBC_CFG_STOP_WUFMSK_ISO0; 
		}
	}
	else 
	{
		/* enable wakeup factor INTP6*/
		STBC_REG_WUFMSK0 = (STBC_CFG_STOP_WUFMSK0 & 0xffefffffu); 
		STBC_REG_WUFMSK20 = STBC_CFG_STOP_WUFMSK20; 
		STBC_REG_WUFMSK_ISO0 = STBC_CFG_STOP_WUFMSK_ISO0; 
	}
}

/***********************************************************************************************************************
* Function Name: Stbc_Set_WakeupFactor
* Description  : After wakeup,set wakeup factor to registers.
* Parameters   : 
* Return Value : None
***********************************************************************************************************************/
void Stbc_Reset_WakeupFactor(void)
{
  /* clear all wake up factors */
  STBC_REG_WUFC0 = 0xffffffffu;
  STBC_REG_WUFC20 = 0xffffffffu;
  STBC_REG_WUFC_ISO0 = 0xffffffffu;

  /* enable wakeup factor */
  STBC_REG_WUFMSK0 = 0xffffffffu; 
  STBC_REG_WUFMSK20 = 0xffffffffu; 
  STBC_REG_WUFMSK_ISO0 = 0xffffffffu; 
}


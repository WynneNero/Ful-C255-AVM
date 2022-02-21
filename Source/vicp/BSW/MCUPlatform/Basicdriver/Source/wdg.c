/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department :  CT AD                                                 *
*   AUTHOR	   :										   *
************************************************************************
* Object        : 
* Module        : WATCHDOG
* Instance      :
* Description   : Hardware watch dog module.
			   note, WDT_Enable must be set in option byte.
*-----------------------------------------------------------------------
* Version: 0.1
* Date: 
* Author: 
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
*------------------------------------------------------------------------
* 0.1	   Jun 26,2016                   Initial version
*------------------------------------------------------------------------
* 0.2	   Jan 11,2017  ZHANG Jie  Add Clock_if.h and ISR_WDTA0func for compile warning,  add explicit variable cast
*                                                   and add u for constant value to avoid Coverity warning.
*----------------------------------------------------------------------
* 0.3          Jan 24,2017    ZhangJie     Fix Coverity warning.
*=====================================================================*/

#include "iodefine.h"
#include "define.h"
#include "wdg.h"
#include "wdg_cfg.h"
#include "Clock_if.h"

/***********************************************************************
*  Name        : WATCHDOG_Init
*  Description : Init clock, set time, error mode.
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void WATCHDOG_Init( void )
{
    U32  reg32_value=0u;
	
    do
    {
        reg32_value               = 0x00000001UL;	    /* Source Clock, LS IntOsc fRL (240 kHz) / 128*/ 
        									    /* reset value =1*/
        PROTCMD0                  = 0x000000A5UL;     
        CKSC_AWDTAD_CTL           = reg32_value;
        CKSC_AWDTAD_CTL           = ~reg32_value;
        CKSC_AWDTAD_CTL           = reg32_value;
    } while ( PROTS0 != 0x00000000UL );
    while ( CKSC_AWDTAD_ACT != reg32_value )
    {
        /* Waiting for CKSC_AWDTAD_CTL to set. */
    }

    /* 
    b6:b4             WDTAnOVF    - Selects the overflow interval time  - 512 / WDTATCKI
    b3                WDTAnWIE    - disables the 75% interrupt
    b2                WDTAnERM    - Specifies the error mode.           - Reset mode
    b1:b0             WDTAnWS     - Selects the window-open period.     - 100% */
    WDTA0.MD                      = ((U8)WDG_TIMEOUT<<4) | (0x07u);		/*reset mode*/	
    
    Clock_AWDTA_SetStpmsK(FALSE);	/* WDT0 clock domain stops in standby mode*/
}


/***********************************************************************
*  Name        : WATCHDOG_Enable
*  Description : Enable the WATCHDOG
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void WATCHDOG_Enable( void )
{	
#if(WDG_START_MODE==WDG_START_SW)
	#if(WDG_VAC_SET == WDG_FIXED)
		WDTA0.WDTE= 0xACu;		/* fixed Activation code */
	#elif(WDG_VAC_SET == WDG_VARIABLE)
		WDTA0.EVAC = ( 0xACu - WDTA0.REF );          /* variable Activation */
	#endif
#endif
}

/***********************************************************************
*  Name        : WATCHDOG_Disable
*  Description : Disable WDT0 in standby mode.
			  WDT1 is automatically stopped in Deep Stop/Cyclic Run.
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void WATCHDOG_Disable( void )
{
	/* once started, no way to stop */	 
}	

/***********************************************************************
*  Name        : WATCHDOG_Clear
*  Description : Clear the WATCHDOG
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void WATCHDOG_Clear( void )
{
#if(WDG_VAC_SET == WDG_FIXED)
	WDTA0.WDTE= 0xACu;		/* fixed Activation code */
#elif(WDG_VAC_SET == WDG_VARIABLE)
	/*     Control the start / restart of the WDTAn count.  */
	WDTA0.EVAC = ( 0xACu - WDTA0.REF );          /* variable Activation */
#endif
}

void ISR_WDTA0func(void)
{
	/*Do nothing*/
}
/****************************** END OF FILE ***************************/

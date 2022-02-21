/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of the timer module for RH850F1L(R7F7010233) of RENESAS.
 *
 *  \file       bl_timer.c
 *  \ingroup    driver_module
 *  \author     lele.liu <lele.liu@hirain.com>
 *
 *  \version    1.0.0
 *  \date       24/01/2016
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | -------------
 *      01.00.00 | 24/01/2016 | lele.liu         | N/A | BootDrv010001
 *
 *****************************************************************************/
#include "bl_timer.h"

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : Tim_Init
*
* Description   : Init Timer Module
*
* Inputs        : none
*
* Outputs       : none
* 
* Limitations   : Only for HiBoot
*                 
************************************************************************************************
END_FUNCTION_HDR */
void Tim_Init(void)
{
    ICOSTM0 |= (1<<7); /* Disables interrupt processing,set MKOSTM0 */
    
    OSTM0CMP = TIMER_DELAY; /* set the value of timer */    
    OSTM0CTL = 0x0; /* Interval timer mode and disable interrupts when counting starts */
    OSTM0TS = 0x1; /* Start  counter */  
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : Tim_IsTimeout
*
* Description   : Tim_IsTimeout function for Timer Module
*
* Inputs        : None
*
* Outputs       : None
* 
* Limitations   : 1.Only for HiBoot
*                 
************************************************************************************************
END_FUNCTION_HDR */
bl_Return_t Tim_IsTimeout(void)
{      
        
    bl_Return_t ret = BL_ERR_NOT_OK;
    if(ICOSTM0 & (1<<12))
    {
        ICOSTM0 &= ~(1<<12); /* clear RFOSTM0 */ 
        ret = BL_ERR_OK;
    }
    return ret;
    
}


/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : Timer_DeInit
*
* Description   : Deinit all Timer related registers if necessary
*
* Inputs        : None
*
* Outputs       : None
* 
* Limitations   : 
*                 
************************************************************************************************
END_FUNCTION_HDR */
void Tim_Deinit(void)
{
    OSTM0TT = 0x1; /* Stop  counter */    
    OSTM0CMP = 0x0; /* Reset the value of timer */
}




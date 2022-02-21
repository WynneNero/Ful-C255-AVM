/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of the watchdog module for rh850/f1h or rh850/f1l.
 *
 *  \file       bl_watchdog.c
 *  \ingroup    driver_module
 *  \author     lele.liu <lele.liu@hirain.com>
 *
 *  \version    1.0.0
 *  \date       25/01/2016
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | -------------
 *      01.00.00 | 25/01/2016| lele.liu         | N/A | BootDrv010001
 *
 *****************************************************************************/
#include "bl_watchdog.h"
#include "GPIO_IF.H"

/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/
#define WDG_TIMEOUT_VALUE    7 /* 0->2ms,1->4ms,2->8ms,3->17ms,4->34ms,5->68ms,
                              6->136ms,7->273ms */


/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/
/**************************************************************************//**
 *
 *  \details Initialize watchdog module.
 *
 *  \return None.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
void Wdg_Init(void)
{
    WDTA1MD = (0x7 | (WDG_TIMEOUT_VALUE << 4));/* disable 75% interrupt request ,reset mode,100%window-open period*/
}

/**************************************************************************//**
 *
 *  \details Start watchdog module.
 *
 *  \return None.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
void Wdg_Start(void)
{
    WDTA1WDTE = 0xAC;
}

bl_u8_t WdgResetFlag = 0;

/**************************************************************************//**
 *
 *  \details Reset watchdog module.
 *
 *  \return None.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
void Wdg_FastReset(void)
{
	//bl_application_value_dataflash_maker();
	WdgResetFlag = 1;
	Sys_Reset();

    WDTA1WDTE = 0xA0;
    
    for(;;)
    {
        
    }
}

/**************************************************************************//**
 *
 *  \details Deinitialize watchdog module.
 *
 *  \return None.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
void Wdg_Deinit(void)
{
    //WDTA1WDTE = 0xAC;/* reset value */
}

/**************************************************************************//**
 *
 *  \details Feed watchdog.
 *
 *  \return None.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
void Wdg_Feed(void)
{
    static bl_u16_t PINlevel = 0;

   
    WDTA1WDTE = 0xAC; 

    //SBC_WDFeedDog();
 #if 0
    	/* Configure CAN0 GPIO-STB pin P8_2*/ 
	PMC8 &= ~(0x0001<<2); /* configure P8_2 as general IO */
    PM8 &= ~(0x0001<<2); /* P8_2 Output pin */

    PINlevel++;
    if(PINlevel<=100)
    {
      P8 &= ~(0x0001<<2);    /* Low level */
    }
    else if(PINlevel<=200)
    {
      P8 |= (0x0001<<2);    /* Hihg Level */
    }
    else
    {
       PINlevel = 0;    
    }
#endif
	#if 0
    	/* Configure CAN0 GPIO-STB pin P8_2*/ 
	PMC8 &= ~(0x0001<<2); /* configure P8_2 as general IO */
    PM8 &= ~(0x0001<<2); /* P8_2 Output pin */
    P8 = (((~P8) & 0x4)|(P8 & 0xfffb)); /* Feed hardware watchdog. */   
	#endif
}


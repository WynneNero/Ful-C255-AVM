/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                                 *
*   AUTHOR     :                                                       *
************************************************************************
* Object        :
* Module        :	CSI
* Instance      :
* Description   :	SPI opertaion.				
				Support 4 channel of CSIH and 1 channel of CSIG.
				Send/receive are handled in interrupts.
				Handshake function are enabled. 
				Hardware must reserve RYO/RYI pin if SPI is required.				
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date           Name                 Changes and comments
*     0.1	  2016-6-23	  RenWeiMin		Init, multiple Chip select is not supported
	                                                         FIFO mode is not supported.
*	0.2    2016-7-28      RenWeiMin          Add handshake to avoid overrun.		
*	0.3    2016-8-24      ShangQiuju         Add Dual Buffer mode               
*=====================================================================*/
#include "config.h"
#include "CSI.h"
#include "csi_if.h"
#include "gpio_if.h"
#include "CSI_Cfg.h"
#include "IRQ_IF.h"

static CSI_FRAME_TYPE CSI_Message[CSI_MAX];

static CPU_INT32U GetCSIBaseAddress(CSI_TYPE csi);
static U8 GetCSIIRQNumber(CSI_TYPE uart);
static void CSI_InitPort_CSIH0(U16 CsSsiChannel ,BOOL bIsMaster,BOOL bOpenRY);
static void CSI_InitPort_CSIH1(U16 CsSsiChannel ,BOOL bIsMaster,BOOL bOpenRY);
static void CSI_InitPort_CSIH2(U16 CsSsiChannel ,BOOL bIsMaster,BOOL bOpenRY);
static void CSI_InitPort_CSIH3(U16 CsSsiChannel ,BOOL bIsMaster,BOOL bOpenRY);
static void CSI_InitPort_CSIG0(U16 CsSsiChannel ,BOOL bIsMaster,BOOL bOpenRY);
void CSI_EnableInterrupt(CSI_TYPE csi );
void CSI_DisableInterrupt(CSI_TYPE csi );
static void Tx_Handler( CSI_TYPE csi ,BOOL bIsFIFO);
static void Rx_Handler( CSI_TYPE csi,BOOL bIsFIFO);
static void Error_Handler(CSI_TYPE csi ,BOOL bIsFIFO);

U8 RxData[8] = {0};

/***********************************************************************
*  Name        : CSI_InitPort_CSIH0
*  Description :  initilize port for CSIH0
*  Parameter   :       
                 CsSsiChannel - specify chip select output( for master with multiple cs)
                 			or chip select input(for slave)
*  Returns     : None
*  note:		 CsSsiChannel is not fully implemented
***********************************************************************/
static void CSI_InitPort_CSIH0(U16 CsSsiChannel ,BOOL bIsMaster,BOOL bOpenRY)
{
	// RYO/RYI
	if(bOpenRY)
	{
        	if(bIsMaster)
        	{
        		GPIO_SetInMode(GPIO_PORT_10,GPIO_PIN_9, E_PLLUP,FALSE);
        	}
        	else
        	{
        		GPIO_SetOutMode(GPIO_PORT_10,GPIO_PIN_9, E_PUSH_PULL,E_HIGH_40MHZ);
        	}
        	GPIO_SetAlterMode(GPIO_PORT_10,GPIO_PIN_9,E_ALTERFUNC_4,FALSE,E_NO_MODE);	
       }
	// P0_1/2/3	- ALT 4

	// P0_1 SI
	GPIO_SetInMode(GPIO_PORT_0,GPIO_PIN_1, E_NO_MODE,FALSE);
	GPIO_SetAlterMode(GPIO_PORT_0,GPIO_PIN_1,E_ALTERFUNC_4,FALSE,E_NO_MODE);
	// P0_2 SC
	GPIO_SetOutMode(GPIO_PORT_0,GPIO_PIN_2,E_NO_MODE,E_HIGH_40MHZ);	
	GPIO_SetAlterMode(GPIO_PORT_0,GPIO_PIN_2,E_ALTERFUNC_4,TRUE,E_NO_MODE);
	// P0_3 SO
	GPIO_SetOutMode(GPIO_PORT_0,GPIO_PIN_3,E_NO_MODE,E_HIGH_40MHZ);
	GPIO_SetAlterMode(GPIO_PORT_0,GPIO_PIN_3,E_ALTERFUNC_4,TRUE,E_NO_MODE);
	
	if(bIsMaster)		// CSS		
	{
		if(CsSsiChannel & CSIH0CSS0_MAP_P8_2)
		{
			GPIO_SetOutMode(GPIO_PORT_8,GPIO_PIN_2, E_NO_MODE, E_HIGH_40MHZ);
			GPIO_SetAlterMode(GPIO_PORT_8,GPIO_PIN_2,E_ALTERFUNC_2,FALSE,E_NO_MODE);						
		}
		if(CsSsiChannel & CSIH0CSS0_MAP_P8_0)
		{
			GPIO_SetOutMode(GPIO_PORT_8,GPIO_PIN_0, E_NO_MODE, E_HIGH_40MHZ);
			GPIO_SetAlterMode(GPIO_PORT_8,GPIO_PIN_0,E_ALTERFUNC_3,FALSE,E_NO_MODE);						
		}
		if(CsSsiChannel & CSIH0CSS1_MAP_P10_10)
		{
			GPIO_SetOutMode(GPIO_PORT_10,GPIO_PIN_A, E_NO_MODE, E_HIGH_40MHZ);
			GPIO_SetAlterMode(GPIO_PORT_10,GPIO_PIN_A,E_ALTERFUNC_4,FALSE,E_NO_MODE);						
		}
		if(CsSsiChannel & CSIH0CSS1_MAP_P8_3)
		{
			GPIO_SetOutMode(GPIO_PORT_8,GPIO_PIN_3, E_NO_MODE, E_HIGH_40MHZ);
			GPIO_SetAlterMode(GPIO_PORT_8,GPIO_PIN_3,E_ALTERFUNC_2,FALSE,E_NO_MODE);						
		}
		if(CsSsiChannel & CSIH0CSS2)
		{
			GPIO_SetOutMode(GPIO_PORT_8,GPIO_PIN_4, E_NO_MODE, E_HIGH_40MHZ);
			GPIO_SetAlterMode(GPIO_PORT_8,GPIO_PIN_4,E_ALTERFUNC_2,FALSE,E_NO_MODE);						
		}
		if(CsSsiChannel & CSIH0CSS3)
		{
			GPIO_SetOutMode(GPIO_PORT_8,GPIO_PIN_5, E_NO_MODE, E_HIGH_40MHZ);
			GPIO_SetAlterMode(GPIO_PORT_8,GPIO_PIN_5,E_ALTERFUNC_2,FALSE,E_NO_MODE);						
		}
		if(CsSsiChannel & CSIH0CSS4)
		{
			GPIO_SetOutMode(GPIO_PORT_8,GPIO_PIN_6, E_NO_MODE, E_HIGH_40MHZ);
			GPIO_SetAlterMode(GPIO_PORT_8,GPIO_PIN_6,E_ALTERFUNC_1,FALSE,E_NO_MODE);						
		}
		if(CsSsiChannel & CSIH0CSS5)
		{
			GPIO_SetOutMode(GPIO_PORT_9,GPIO_PIN_4, E_NO_MODE, E_HIGH_40MHZ);
			GPIO_SetAlterMode(GPIO_PORT_9,GPIO_PIN_4,E_ALTERFUNC_1,FALSE,E_NO_MODE);						
		}
		if(CsSsiChannel & CSIH0CSS6)
		{
			GPIO_SetOutMode(GPIO_PORT_9,GPIO_PIN_5, E_NO_MODE, E_HIGH_40MHZ);
			GPIO_SetAlterMode(GPIO_PORT_9,GPIO_PIN_5,E_ALTERFUNC_1,FALSE,E_NO_MODE);						
		}
		if(CsSsiChannel & CSIH0CSS7)
		{
			GPIO_SetOutMode(GPIO_PORT_9,GPIO_PIN_6, E_NO_MODE, E_HIGH_40MHZ);
			GPIO_SetAlterMode(GPIO_PORT_9,GPIO_PIN_6,E_ALTERFUNC_1,FALSE,E_NO_MODE);						
		}
	}
	else			// SSI
	{
		if(CsSsiChannel & CSIH0SSI_MAP_P0_0)
		{
			GPIO_SetInMode(GPIO_PORT_0,GPIO_PIN_0, E_NO_MODE, FALSE);
			GPIO_SetAlterMode(GPIO_PORT_0,GPIO_PIN_0,E_ALTERFUNC_4,FALSE,E_NO_MODE);						
		}
		if(CsSsiChannel & CSIH0SSI_MAP_P10_13)
		{
			GPIO_SetInMode(GPIO_PORT_10,GPIO_PIN_D, E_NO_MODE, FALSE);
			GPIO_SetAlterMode(GPIO_PORT_10,GPIO_PIN_D,E_ALTERFUNC_1,FALSE,E_NO_MODE);						
		}
	}
}

/***********************************************************************
*  Name        : CSI_InitPort_CSIH1
*  Description :  initilize port for CSIH1
*  Parameter   :       
                 CsSsiChannel - specify chip select output( for master with multiple cs)
                 			or chip select input(for slave)
*  Returns     : None
*  note:		 CsSsiChannel is not fully implemented
***********************************************************************/
static void CSI_InitPort_CSIH1(U16 CsSsiChannel,BOOL bIsMaster,BOOL bOpenRY)
{
	// RYO/RYI
	if(bOpenRY)
	{
        	if(bIsMaster)
        	{
        		GPIO_SetInMode(GPIO_PORT_0,GPIO_PIN_7, E_PLLUP,FALSE);
        	}	
        	else
        	{
        		GPIO_SetOutMode(GPIO_PORT_0,GPIO_PIN_7, E_PUSH_PULL,E_HIGH_40MHZ);
        	}
        	GPIO_SetAlterMode(GPIO_PORT_0,GPIO_PIN_7,E_ALTERFUNC_3,FALSE,E_NO_MODE);	
	}
	
		// SO
		if(CsSsiChannel &CSIH1SO_MAP_P0_5)	
		{					
			GPIO_SetOutMode(GPIO_PORT_0,GPIO_PIN_5,E_NO_MODE,E_HIGH_40MHZ);	
			GPIO_SetAlterMode(GPIO_PORT_0,GPIO_PIN_5,E_ALTERFUNC_3,TRUE,E_NO_MODE);
		}
		
		if(CsSsiChannel &CSIH1SO_MAP_P10_2)	
		{					
			GPIO_SetOutMode(GPIO_PORT_10,GPIO_PIN_2,E_NO_MODE,E_HIGH_40MHZ);	
			GPIO_SetAlterMode(GPIO_PORT_10,GPIO_PIN_2,E_ALTERFUNC_5,TRUE,E_NO_MODE);
		}
		// SI
		if(CsSsiChannel &CSIH1SI_MAP_P0_4)	
		{					
			GPIO_SetInMode(GPIO_PORT_0,GPIO_PIN_4, E_NO_MODE,FALSE);
			GPIO_SetAlterMode(GPIO_PORT_0,GPIO_PIN_4,E_ALTERFUNC_3,FALSE,E_NO_MODE);
		}

		if(CsSsiChannel &CSIH1SI_MAP_P10_0)	
		{					
			GPIO_SetInMode(GPIO_PORT_10,GPIO_PIN_0, E_NO_MODE,FALSE);
			GPIO_SetAlterMode(GPIO_PORT_10,GPIO_PIN_0,E_ALTERFUNC_5,FALSE,E_NO_MODE);
		}
		// SC	
		if(CsSsiChannel &CSIH1SC_MAP_P0_6)	
		{	
			GPIO_SetOutMode(GPIO_PORT_0,GPIO_PIN_6,E_NO_MODE,E_HIGH_40MHZ);	
			GPIO_SetAlterMode(GPIO_PORT_0,GPIO_PIN_6,E_ALTERFUNC_3,TRUE,E_NO_MODE);
		}
		if(CsSsiChannel &CSIH1SC_MAP_P10_1)	
		{
			GPIO_SetOutMode(GPIO_PORT_10,GPIO_PIN_1,E_NO_MODE,E_HIGH_40MHZ);
			GPIO_SetAlterMode(GPIO_PORT_10,GPIO_PIN_1,E_ALTERFUNC_5,TRUE,E_NO_MODE);
		}

		if(bIsMaster)		// CSS		
		{
			if(CsSsiChannel & CSIH1CSS0_MAP_P0_9)
			{
				GPIO_SetOutMode(GPIO_PORT_0,GPIO_PIN_9, E_NO_MODE, E_HIGH_40MHZ);
				GPIO_SetAlterMode(GPIO_PORT_0,GPIO_PIN_9,E_ALTERFUNC_1,FALSE,E_NO_MODE);						
			}
			if(CsSsiChannel & CSIH1CSS0_MAP_P10_11)
			{
				GPIO_SetOutMode(GPIO_PORT_10,GPIO_PIN_B, E_NO_MODE, E_HIGH_40MHZ);
				GPIO_SetAlterMode(GPIO_PORT_10,GPIO_PIN_B,E_ALTERFUNC_3,FALSE,E_NO_MODE);						
			}
			if(CsSsiChannel & CSIH1CSS1_MAP_P0_10)
			{
				GPIO_SetOutMode(GPIO_PORT_0,GPIO_PIN_A, E_NO_MODE, E_HIGH_40MHZ);
				GPIO_SetAlterMode(GPIO_PORT_0,GPIO_PIN_A,E_ALTERFUNC_1,FALSE,E_NO_MODE);						
			}
			if(CsSsiChannel & CSIH1CSS1_MAP_P10_12)
			{
				GPIO_SetOutMode(GPIO_PORT_10,GPIO_PIN_C, E_NO_MODE, E_HIGH_40MHZ);
				GPIO_SetAlterMode(GPIO_PORT_10,GPIO_PIN_C,E_ALTERFUNC_3,FALSE,E_NO_MODE);						
			}
			if(CsSsiChannel & CSIH1CSS2)
			{
				GPIO_SetOutMode(GPIO_PORT_0,GPIO_PIN_B, E_NO_MODE, E_HIGH_40MHZ);
				GPIO_SetAlterMode(GPIO_PORT_0,GPIO_PIN_B,E_ALTERFUNC_2,FALSE,E_NO_MODE);						
			}
			if(CsSsiChannel & CSIH1CSS3)
			{
				GPIO_SetOutMode(GPIO_PORT_8,GPIO_PIN_1, E_NO_MODE, E_HIGH_40MHZ);
				GPIO_SetAlterMode(GPIO_PORT_8,GPIO_PIN_1,E_ALTERFUNC_3,FALSE,E_NO_MODE);						
			}
			if(CsSsiChannel & CSIH1CSS4)
			{
				GPIO_SetOutMode(GPIO_PORT_8,GPIO_PIN_B, E_NO_MODE, E_HIGH_40MHZ);
				GPIO_SetAlterMode(GPIO_PORT_8,GPIO_PIN_B,E_ALTERFUNC_3,FALSE,E_NO_MODE);						
			}
			if(CsSsiChannel & CSIH1CSS5)
			{
				GPIO_SetOutMode(GPIO_PORT_8,GPIO_PIN_C, E_NO_MODE, E_HIGH_40MHZ);
				GPIO_SetAlterMode(GPIO_PORT_8,GPIO_PIN_C,E_ALTERFUNC_3,FALSE,E_NO_MODE);						
			}
		}
		else		// SSI
		{
			if(CsSsiChannel & CSIH1SSI_MAP_P0_8)
			{
				GPIO_SetInMode(GPIO_PORT_0,GPIO_PIN_8, E_NO_MODE,FALSE);
				GPIO_SetAlterMode(GPIO_PORT_0,GPIO_PIN_8,E_ALTERFUNC_3,FALSE,E_NO_MODE);
			}
			if(CsSsiChannel & CSIH1SSI_MAP_P10_3)
			{
				GPIO_SetInMode(GPIO_PORT_10,GPIO_PIN_3, E_NO_MODE,FALSE);
				GPIO_SetAlterMode(GPIO_PORT_10,GPIO_PIN_3,E_ALTERFUNC_5,FALSE,E_NO_MODE);
			}
		}
}

/***********************************************************************
*  Name        : CSI_InitPort_CSIH2
*  Description :  initilize port for CSIH2
*  Parameter   :       
                 CsSsiChannel - specify chip select output( for master with multiple cs)
                 			or chip select input(for slave)
*  Returns     : None
*  note:		 CsSsiChannel is not fully implemented
***********************************************************************/
static void CSI_InitPort_CSIH2(U16 CsSsiChannel,BOOL bIsMaster,BOOL bOpenRY)
{
	// RYO/RYI
       if(bOpenRY)
       {
        	if(bIsMaster)
        	{
        		GPIO_SetInMode(GPIO_PORT_11,GPIO_PIN_0, E_PLLUP,FALSE);
        	}	
        	else
        	{
        		GPIO_SetOutMode(GPIO_PORT_11,GPIO_PIN_0, E_PUSH_PULL,E_HIGH_40MHZ);
        	}
        	GPIO_SetAlterMode(GPIO_PORT_11,GPIO_PIN_0,E_ALTERFUNC_1,FALSE,E_NO_MODE);	
	}

	// P11_2/3/4	- ALT 1
					
	// P11_4 SI
	GPIO_SetInMode(GPIO_PORT_11,GPIO_PIN_4, E_NO_MODE,FALSE);
	GPIO_SetAlterMode(GPIO_PORT_11,GPIO_PIN_4,E_ALTERFUNC_1,FALSE,E_NO_MODE);
	// P11_2 SO
	GPIO_SetOutMode(GPIO_PORT_11,GPIO_PIN_2,E_NO_MODE,E_HIGH_40MHZ);	
	GPIO_SetAlterMode(GPIO_PORT_11,GPIO_PIN_2,E_ALTERFUNC_1,TRUE,E_NO_MODE);
	// P11_3 SC	
	GPIO_SetOutMode(GPIO_PORT_11,GPIO_PIN_3,E_NO_MODE,E_HIGH_40MHZ);
	GPIO_SetAlterMode(GPIO_PORT_11,GPIO_PIN_3,E_ALTERFUNC_1,TRUE,E_NO_MODE);
	
	if(bIsMaster)		// CSS		
	{
		if(CsSsiChannel & CSIH2CSS0)
		{
			GPIO_SetOutMode(GPIO_PORT_9,GPIO_PIN_0, E_NO_MODE, E_HIGH_40MHZ);
			GPIO_SetAlterMode(GPIO_PORT_9,GPIO_PIN_0,E_ALTERFUNC_3,FALSE,E_NO_MODE);						
		}
		if(CsSsiChannel & CSIH2CSS1)
		{
			GPIO_SetOutMode(GPIO_PORT_9,GPIO_PIN_1, E_NO_MODE, E_HIGH_40MHZ);
			GPIO_SetAlterMode(GPIO_PORT_9,GPIO_PIN_1,E_ALTERFUNC_3,FALSE,E_NO_MODE);						
		}
		if(CsSsiChannel & CSIH2CSS2)
		{
			GPIO_SetOutMode(GPIO_PORT_9,GPIO_PIN_2, E_NO_MODE, E_HIGH_40MHZ);
			GPIO_SetAlterMode(GPIO_PORT_9,GPIO_PIN_2,E_ALTERFUNC_2,FALSE,E_NO_MODE);						
		}
		if(CsSsiChannel & CSIH2CSS3)
		{
			GPIO_SetOutMode(GPIO_PORT_9,GPIO_PIN_3, E_NO_MODE, E_HIGH_40MHZ);
			GPIO_SetAlterMode(GPIO_PORT_9,GPIO_PIN_3,E_ALTERFUNC_2,FALSE,E_NO_MODE);						
		}
	}
	else		// SSI
	{
		GPIO_SetInMode(GPIO_PORT_11,GPIO_PIN_1, E_NO_MODE,FALSE);
		GPIO_SetAlterMode(GPIO_PORT_11,GPIO_PIN_1,E_ALTERFUNC_1,FALSE,E_NO_MODE);
	}
}

/***********************************************************************
*  Name        : CSI_InitPort_CSIH3
*  Description :  initilize port for CSIH3
*  Parameter   :       
                 CsSsiChannel - specify chip select output( for master with multiple cs)
                 			or chip select input(for slave)
*  Returns     : None
*  note:		 CsSsiChannel is not fully implemented
***********************************************************************/
static void CSI_InitPort_CSIH3(U16 CsSsiChannel,BOOL bIsMaster,BOOL bOpenRY)
{
	// RYO/RYI
        if(bOpenRY)
        {
            if(bIsMaster)
            {
                GPIO_SetInMode(GPIO_PORT_10,GPIO_PIN_F, E_PLLUP,FALSE);
            }
            else
            {
                GPIO_SetOutMode(GPIO_PORT_10,GPIO_PIN_F, E_PUSH_PULL,E_HIGH_40MHZ);
            }
            GPIO_SetAlterMode(GPIO_PORT_10,GPIO_PIN_F,E_ALTERFUNC_1,FALSE,E_NO_MODE);	
        }
	// P11_5	SI
	GPIO_SetInMode(GPIO_PORT_11,GPIO_PIN_5, E_NO_MODE,FALSE);
	GPIO_SetAlterMode(GPIO_PORT_11,GPIO_PIN_5,E_ALTERFUNC_3,FALSE,E_NO_MODE);
	// P11_6	SO
	GPIO_SetOutMode(GPIO_PORT_11,GPIO_PIN_6,E_NO_MODE,E_HIGH_40MHZ);	
	GPIO_SetAlterMode(GPIO_PORT_11,GPIO_PIN_6,E_ALTERFUNC_3,TRUE,E_NO_MODE);
	// P11_7    SCK   
	GPIO_SetOutMode(GPIO_PORT_11,GPIO_PIN_7,E_NO_MODE,E_HIGH_40MHZ);
	GPIO_SetAlterMode(GPIO_PORT_11,GPIO_PIN_7,E_ALTERFUNC_3,TRUE,E_NO_MODE);

	/*
	// input,buffer disabled
	PIBC11	&= 0xFF1FU;		// input buffer disable setting 
	PBDC11	&= 0xFF1FU;
	PM11	|= 0x00E0;		// input setting 
	PMC11	&= 0xFF1FU;		// port mode
	PIPC11	&= 0xFF1FU;

	//port alternative setting 
	PFC11	&= 0xFF1FU;		// 0:ALT1,3,5   1:ALT2,4   
	PFCE11	|= 0x00E0U;		// 0:ALT1,2,5   1:ALT3,4   
	PFCAE11	&= 0xFF1FU;		// 0:ALT1-4     1:ALT5     

	// port input/output setting 
	PIPC11	|= 0x00C0U;		// 0:PM setting 1:direct IO control 	// P11_6/7 	
	PMC11	|= 0x00E0U;		// 0:Port mode  1:ALT mode 
	PM11	&= 0xFF3FU;		// 0- outpuit
	*/
				
	if(bIsMaster)			//CSSx
	{
		if(CsSsiChannel & CSIH3CSS0)
		{
			GPIO_SetOutMode(GPIO_PORT_8,GPIO_PIN_7, E_NO_MODE, E_HIGH_40MHZ);
			GPIO_SetAlterMode(GPIO_PORT_8,GPIO_PIN_7,E_ALTERFUNC_1,FALSE,E_NO_MODE);			
		}
		if(CsSsiChannel & CSIH3CSS1)
		{
			GPIO_SetOutMode(GPIO_PORT_8,GPIO_PIN_8, E_NO_MODE, E_HIGH_40MHZ);
			GPIO_SetAlterMode(GPIO_PORT_8,GPIO_PIN_8,E_ALTERFUNC_1,FALSE,E_NO_MODE);			
		}
		if(CsSsiChannel & CSIH3CSS2)
		{
			GPIO_SetOutMode(GPIO_PORT_8,GPIO_PIN_9, E_NO_MODE, E_HIGH_40MHZ);
			GPIO_SetAlterMode(GPIO_PORT_8,GPIO_PIN_9,E_ALTERFUNC_1,FALSE,E_NO_MODE);			
		}
		if(CsSsiChannel & CSIH3CSS3)
		{
			GPIO_SetOutMode(GPIO_PORT_8,GPIO_PIN_A, E_NO_MODE, E_HIGH_40MHZ);
			GPIO_SetAlterMode(GPIO_PORT_8,GPIO_PIN_A,E_ALTERFUNC_1,FALSE,E_NO_MODE);			
		}
		
		/* port alternative setting 
		PFC8	&= 0xFF7FU;		// 0:ALT1,3,5   1:ALT2,4   
		PFCE8	&= 0xFF7FU;		// 0:ALT1,2,5   1:ALT3,4   
			
		// port input/output setting
		PMC8	|= 0x0080U;		// 0:Port mode  1:ALT mode 
		PM8		&= 0xFF7FU;		// 0:OUT        1:IN      
		*/
	}
	else

	{				
		// P10_14 - CSSI- ALT3
		GPIO_SetInMode(GPIO_PORT_10,GPIO_PIN_E, E_NO_MODE,FALSE);
		GPIO_SetAlterMode(GPIO_PORT_10,GPIO_PIN_E,E_ALTERFUNC_3,FALSE,E_NO_MODE);

		/*
		PFC10	&= 0xBFFFU;		// 0:ALT1,3,5   1:ALT2,4   
		PFCE10	|= 0x4000U;		// 0:ALT1,2,5   1:ALT3,4   
		PFCAE10 &= 0xBFFFU;		// 0:ALT1-4     1:ALT5     
			
		// port input/output setting 
		PMC10	|= 0x4000U;		// 0:Port mode  1:ALT mode 
		PM10	|= 0x4000U;		// 0:OUT        1:IN      
		*/
	}
}
/***********************************************************************
*  Name        : CSI_InitPort_CSIG0
*  Description :  initilize port for CSIG0
*  Parameter   :       
                       CsSsiChannel - specify chip select output( for master with multiple cs)
                 			or chip select input(for slave)
*  Returns     : None
*  note:		 CsSsiChannel is not fully implemented
***********************************************************************/
static void CSI_InitPort_CSIG0(U16 CsSsiChannel,BOOL bIsMaster,BOOL bOpenRY)
{					
	// RYO/RYI
	if(bOpenRY)
	{
        	if(bIsMaster)
        	{
        		GPIO_SetInMode(GPIO_PORT_10,GPIO_PIN_5, E_PLLUP,FALSE);
        	}
        	else
        	{
        		GPIO_SetOutMode(GPIO_PORT_10,GPIO_PIN_5, E_PUSH_PULL,E_HIGH_40MHZ);
        	}
        	GPIO_SetAlterMode(GPIO_PORT_10,GPIO_PIN_5,E_ALTERFUNC_5,FALSE,E_NO_MODE);	
        }
	// SI
	if(CsSsiChannel & CSIG0SI_MAP_P0_12)
	{
		GPIO_SetInMode(GPIO_PORT_0,GPIO_PIN_C, E_NO_MODE,FALSE);
		GPIO_SetAlterMode(GPIO_PORT_0,GPIO_PIN_C,E_ALTERFUNC_4,FALSE,E_NO_MODE);
	}
	else if(CsSsiChannel & CSIG0SI_MAP_P10_8)
	{
		GPIO_SetInMode(GPIO_PORT_0,GPIO_PIN_C, E_NO_MODE,FALSE);
		GPIO_SetAlterMode(GPIO_PORT_0,GPIO_PIN_C,E_ALTERFUNC_2,FALSE,E_NO_MODE);
	}
	//  SO
	if(CsSsiChannel & CSIG0SO_MAP_P0_13)
	{
		GPIO_SetOutMode(GPIO_PORT_0,GPIO_PIN_D,E_NO_MODE,E_HIGH_40MHZ);	
		GPIO_SetAlterMode(GPIO_PORT_0,GPIO_PIN_D,E_ALTERFUNC_4,TRUE,E_NO_MODE);
	}
	else if(CsSsiChannel &  CSIG0SO_MAP_P10_6)
	{
		GPIO_SetOutMode(GPIO_PORT_10,GPIO_PIN_6,E_NO_MODE,E_HIGH_40MHZ);	
		GPIO_SetAlterMode(GPIO_PORT_10,GPIO_PIN_6,E_ALTERFUNC_2,TRUE,E_NO_MODE);		
	}
	//  SC	
	if(CsSsiChannel & CSIG0SC_MAP_P0_14)
	{
		GPIO_SetOutMode(GPIO_PORT_0,GPIO_PIN_E,E_NO_MODE,E_HIGH_40MHZ);
		GPIO_SetAlterMode(GPIO_PORT_0,GPIO_PIN_E,E_ALTERFUNC_4,TRUE,E_NO_MODE);
	}
	else if(CsSsiChannel & CSIG0SC_MAP_P10_7)
	{
		GPIO_SetOutMode(GPIO_PORT_10,GPIO_PIN_7,E_NO_MODE,E_HIGH_40MHZ);
		GPIO_SetAlterMode(GPIO_PORT_10,GPIO_PIN_7,E_ALTERFUNC_2,TRUE,E_NO_MODE);
	}
	
	if(bIsMaster)		// no CSS for CSIG0
	{
		
	}
	else		// SSI
	{
		GPIO_SetInMode(GPIO_PORT_10,GPIO_PIN_4, E_NO_MODE,FALSE);
		GPIO_SetAlterMode(GPIO_PORT_10,GPIO_PIN_4,E_ALTERFUNC_5,FALSE,E_NO_MODE);
	}	
}
/***********************************************************************
*  Name        : CSI_InitPort
*  Description :  init SO/SI/SC of SPI, 
				SSx for master,
				SSI for slave
*  Parameter   : csi - csi channel          
                 	   CsSsiChannel - specify chip select output( for master with multiple cs)
                 			or chip select input(for slave)
*  Returns     : None
***********************************************************************/
void CSI_InitPort( CSI_TYPE csi, U16 CsSsiChannel,BOOL bIsMaster,BOOL bOpenRY)
{
	switch(csi)
	{
		case CSIH_0:
		{
			CSI_InitPort_CSIH0(CsSsiChannel,bIsMaster,bOpenRY);
			break;
		}
		case CSIH_1:
		{
			CSI_InitPort_CSIH1(CsSsiChannel,bIsMaster,bOpenRY);
				break;
		}
		case CSIH_2:
		{
			CSI_InitPort_CSIH2(CsSsiChannel,bIsMaster,bOpenRY);
			break;
		}
		case CSIH_3:
		{   
			CSI_InitPort_CSIH3(CsSsiChannel,bIsMaster,bOpenRY);
			break;	
		}
		case CSIG_0:
		{   
			CSI_InitPort_CSIG0(CsSsiChannel,bIsMaster,bOpenRY);
			break;	
		}
		default:
			break;
	}	
}
/***********************************************************************
*  Name        : CSI_Init
*  Description : Initialize specified SPI channel, don't provide clock here.
*  Parameter   : csi - only support CSIH0/1/2/3
                 baudrate - only for master mode
                 optionsCTL1 - for CTL1
                 optionsCFG0 -for CFG0
                 bMasterMode	- TRUE : master mode; FALSE: slave mode
                 CsSsiChannel - specify IO channel of chip select (in/out) 
                 			      don't support multiple CS						// to do...
*  Returns     : None
***********************************************************************/
void CSI_Init( CSI_TYPE csi, SPI_BAUD_OPTION baudrate,BOOL bIsMaster,U16 CsSsiChannel,BOOL bOpenRY)
{
	U32 u32csi_base_adr=0;

   CSI_InitPort(csi,CsSsiChannel,bIsMaster,bOpenRY);	

   u32csi_base_adr = GetCSIBaseAddress(csi);   

   CSI_DisableInterrupt(csi);

    CSI_REG_CSIHnCTL0(u32csi_base_adr) = (CSIG_CTL0_PWR_STOP_OPERATION_CLOCK | CSIG_CTL0_TXE_TRANSMISSION_DISABLE |
    						CSIG_CTL0_RXE_TRANSMISSION_DISABLE |  CSIG_CTL0_B0_SET_TO_1);	// direct access
	
    if(csi==CSIG_0)
    {
   	    CSI_REG_CSIGnCFG0(u32csi_base_adr)  = CSI_CFG0_OPTION_CFG;	
    }
    else
    {
    	// csih0:0~7, csih1:0~5, csih2:0~3, csih3:0~3    	
    	CSI_REG_CSIHnCFG0(u32csi_base_adr)  = CSI_CFG0_OPTION_CFG;
	CSI_REG_CSIHnCFG1(u32csi_base_adr)  = CSI_CFG1_OPTION_CFG;
	CSI_REG_CSIHnCFG2(u32csi_base_adr)  = CSI_CFG2_OPTION_CFG;
	CSI_REG_CSIHnCFG3(u32csi_base_adr)  = CSI_CFG3_OPTION_CFG;
	
	if( (csi==CSIH_1) || (csi==CSIH_0) )
	{			
		CSI_REG_CSIHnCFG4(u32csi_base_adr)  = CSI_CFG4_OPTION_CFG;	
		CSI_REG_CSIHnCFG5(u32csi_base_adr)  = CSI_CFG5_OPTION_CFG;
	}
	
	if(csi==CSIH_0)
	{
		CSI_REG_CSIHnCFG6(u32csi_base_adr)  = CSI_CFG6_OPTION_CFG;	
		CSI_REG_CSIHnCFG7(u32csi_base_adr)  = CSI_CFG7_OPTION_CFG;	
	}
    }

	CSI_REG_CSIHnSTCR0(u32csi_base_adr) = (CSIG_STCR0_DCEC | CSIG_STCR0_PEC | CSIG_STCR0_OVEC);

	if(bIsMaster)
	{
		if(csi==CSIG_0)
		{
			CSI_REG_CSIHnCTL2(u32csi_base_adr) |=(PLL_FREQ_HZ>>1)/baudrate;
	       		CSI_REG_CSIHnCTL2(u32csi_base_adr) &= 0x1fff;		//PCLK, master mode
		}
		else
		{
		    CSI_REG_CSIHnBRS0(u32csi_base_adr) |= (PLL_FREQ_HZ>>1)/baudrate;
		   CSI_REG_CSIHnCTL2(u32csi_base_adr) &= 0x1fff;		//PCLK, master mode
		   if(CsSsiChannel != NO_CSS)
		   {
        	   	CSI_REG_CSIHnCTL1(u32csi_base_adr) |=(CSIH_CTL1_CS_RETURN_INACTIVE_ENABLE | CSIG_CTL1_SSE_CSIGTSSI_ENABLE);	//enable slave select, CS return to inactive
		   }
		}
	}
	else		// slave
	{
		if(csi==CSIG_0)
		{
			// CSI_REG_CSIHnCTL2(u32csi_base_adr) &= 0xF000;	// stop BRG, ignored in slave mode 
			if(CsSsiChannel != NO_CSS)
		   	{
				CSI_REG_CSIHnCTL1(u32csi_base_adr) |=CSIG_CTL1_SSE_CSIGTSSI_ENABLE;	//enable SSI
			}
		}
		else
		{
			CSI_REG_CSIHnBRS0(u32csi_base_adr)= 0;
			if(CsSsiChannel != NO_CSS)
			{			
    		       		CSI_REG_CSIHnCTL1(u32csi_base_adr) |=(CSIH_CTL1_CS_RETURN_INACTIVE_ENABLE | CSIG_CTL1_SSE_CSIGTSSI_ENABLE);	//enable slave select, CS return to inactive
			}
		}
	      CSI_REG_CSIHnCTL2(u32csi_base_adr) |= 0xE000;		//slave, external clock
	}
	
	// enable Hand shake
	if(bOpenRY)
	    CSI_REG_CSIHnCTL1(u32csi_base_adr) |=	CSIG_CTL1_HSE_HANDSHAKE_ENABLE;
}


/***********************************************************************
*  Name        : CSI_Start
*  Description : start SPI module
*  Parameter   : csi - csi channel
                 	   datalen - reserved		// to do... extended data length
*  Returns     : None
***********************************************************************/
void CSI_Start(CSI_TYPE csi, U8 datalen)
{
   CSI_Message[csi].CsiTxEDLCnt = datalen;
   
												// module clock
    CSI_REG_CSIHnCTL0(GetCSIBaseAddress(csi)) |=(CSIG_CTL0_PWR_PROVIDE_OPERATION_CLOCK |\
						CSIG_CTL0_TXE_TRANSMISSION_ENABLE | CSIG_CTL0_RXE_TRANSMISSION_ENABLE);  

    CSI_Message[csi].CsiRxAddress = RxData;
   CSI_EnableInterrupt(csi);
   }

void CSI_EnableInterrupt(CSI_TYPE csi )
{
     /* clear INTCSIG0IC interrupt request flag */
     /* enable INTCSIG0IC interrupt */
     /* clear INTCSIG0IR interrupt request flag */
     /* enable INTCSIG0IR interrupt */
    /* clear INTCSIG0IRE interrupt request flag */
    /* enable INTCSIG0IRE interrupt */
   IRQ_IntClr(GetCSIIRQNumber(csi));
   IRQ_IntEn(GetCSIIRQNumber(csi));

   IRQ_IntClr(GetCSIIRQNumber(csi)+1);
   IRQ_IntEn(GetCSIIRQNumber(csi)+1);
   
   if(csi==CSIG_0)
   {
   	   IRQ_IntClr(GetCSIIRQNumber(csi)+30);
	   IRQ_IntEn(GetCSIIRQNumber(csi)+30);
   }
   else
   {
	   IRQ_IntClr(GetCSIIRQNumber(csi)+2);
	   IRQ_IntEn(GetCSIIRQNumber(csi)+2);
   }
}

void CSI_EnableTxInterrupt(CSI_TYPE csi )
{
    U32 u32csi_base_adr=0;

    u32csi_base_adr = GetCSIBaseAddress(csi);  
    CSI_REG_CSIHnCTL0(u32csi_base_adr) |=CSIG_CTL0_TXE_TRANSMISSION_ENABLE;
}
void CSI_DisableTxInterrupt(CSI_TYPE csi )
{
    U32 u32csi_base_adr=0;

    u32csi_base_adr = GetCSIBaseAddress(csi);

    CSI_REG_CSIHnCTL0(u32csi_base_adr) &=~  CSIG_CTL0_TXE_TRANSMISSION_ENABLE;
}
void CSI_DisableInterrupt(CSI_TYPE csi )
{
   IRQ_IntDis(GetCSIIRQNumber(csi));		// IC:
   IRQ_IntClr(GetCSIIRQNumber(csi));
  
   IRQ_IntDis(GetCSIIRQNumber(csi)+1);	//IR:receive interrupt
   IRQ_IntClr(GetCSIIRQNumber(csi)+1);

   if(csi==CSIG_0)
   {
	   IRQ_IntDis(GetCSIIRQNumber(csi)+30);	// IRE  : communication error interrupt
	   IRQ_IntClr(GetCSIIRQNumber(csi)+30);
   }
   else
   {
	   IRQ_IntDis(GetCSIIRQNumber(csi)+2);	// IRE
	   IRQ_IntClr(GetCSIIRQNumber(csi)+2);
   }
}


/***********************************************************************
*  Name        : CSI_Stop
*  Description : stop SPI module
*  Parameter   : csi - csi channel
*  Returns     : None
***********************************************************************/
void CSI_Stop(CSI_TYPE csi )
{
     /* disable CSIG0 transmission operation */
     /* disable CSIG0 reception operation */
    /* disable CSIG0 */
    CSI_REG_CSIHnCTL0(GetCSIBaseAddress(csi))=(CSIG_CTL0_PWR_STOP_OPERATION_CLOCK|CSIG_CTL0_TXE_TRANSMISSION_DISABLE|\
                                                                                  CSIG_CTL0_RXE_TRANSMISSION_DISABLE);  

    
     /* disable INTCSIG0IC interrupt */
     /* clear INTCSIG0IC interrupt request flag */
     /* disable INTCSIG0IR interrupt */
    /* clear INTCSIG0IR interrupt request flag */
    /* disable INTCSIG0IRE interrupt */
    /* clear INTCSIG0IRE interrupt request flag */

    CSI_DisableInterrupt(csi);

}

void CSI_StopFIFO(CSI_TYPE csi)
{
   U32 u32csi_base_adr=0;
   u32csi_base_adr = GetCSIBaseAddress(csi);   

   CSI_Stop(csi);
   CSI_REG_CSIHnSTCR0(u32csi_base_adr) = 0xffff;
   CSI_REG_CSIHnMRWP0(u32csi_base_adr) =  0x00000000; /*CSIHnRRA[6:0] 00H clear read pointer*/
}

void CSI_InitFIFO( CSI_TYPE csi, SPI_BAUD_OPTION baudrate,BOOL bIsMaster,U16 CsSsiChannel,BOOL bOpenRY)
{    
   U32 u32csi_base_adr=0;

   CSI_InitPort(csi,CsSsiChannel,bIsMaster,bOpenRY);		//CSIH3CSS0
   CSI_DisableInterrupt(csi);
   u32csi_base_adr = GetCSIBaseAddress(csi);   
   
   CSI_REG_CSIHnCTL0(u32csi_base_adr) = 0; /*clear CSIHnPWR*/
   CSI_REG_CSIHnCFG0(u32csi_base_adr)  = CSI_CFG0_OPTION_CFG;
   CSI_REG_CSIHnCTL1(u32csi_base_adr) = 0;
   if(bIsMaster)
   {        
        CSI_REG_CSIHnBRS0(u32csi_base_adr) |= (PLL_FREQ_HZ>>1)/baudrate;
        CSI_REG_CSIHnCTL2(u32csi_base_adr) &= 0x1fff;		//PCLK, master mode
   }
   else
        CSI_REG_CSIHnCTL2(u32csi_base_adr) = 0xE000;		//slave, external clock
        
   CSI_REG_CSIHnSTCR0(u32csi_base_adr) = 0xffff;
   CSI_REG_CSIHnMCTL0(u32csi_base_adr) =  0x0100;  /*CSIHnMMS[1:0] 01 Dual Buffer mode*/

   CSI_REG_CSIHnMRWP0(u32csi_base_adr) =  0x00000000; /*CSIHnRRA[6:0] 00H clear read pointer*/   
}

void CSI_StartFifo(CSI_TYPE csi, U8 datalen,BOOL bIsMaster)
{
    CSI_Start(csi, datalen);
    if (!bIsMaster)
    {
        U8 index;
        for(index=0;index<8;index++)
        {
    	    CSI_REG_CSIHnTX0H(GetCSIBaseAddress(csi))=0;
        }        
        CSI_REG_CSIHnMCTL2(GetCSIBaseAddress(csi)) =  0x80080000; /*CSIHnND[7:0] 08H Specifies the number of data for each memory mode*/
    }
}
/***********************************************************************
*  Name        : CSI_send_over
*  Description : return send status
*  Parameter   : csi - csi channel

*  Returns     : 
			   True -send finish
***********************************************************************/
BOOL CSI_send_over( CSI_TYPE csi)
{
	BOOL b_result=FALSE;
	
	if(CSI_Message[csi].CsiTxCnt!=0)
		b_result=FALSE;
	else
		b_result=TRUE;
	return b_result;
}

/***********************************************************************
*  Name        : CSI_Send_Receive
*  Description : Send & receive data.
*  Parameter   : csi - csi channel
                       txbuf -  pointer to send data array
                       length - length of data to send/receive
                       rxbuf - pointer to receive data arry
*  Returns     : 
			   True -operation ok
			   False - length=0
***********************************************************************/
BOOL CSI_Send( CSI_TYPE csi,U8 *txbuf, U16 length, U8 *rxbuf )
{
    BOOL status = TRUE;

//return TRUE;
    if (length < 2U) 
    {
        status = FALSE;
    }
    else
    {
        CSI_Message[csi].CsiTxCnt = length; /* send data count */
        CSI_Message[csi].CsiTxAddress = txbuf; /* send buffer pointer */
        CSI_Message[csi].CsiRxAddress = RxData; /* receive buffer pointer */

        if ( CSI_REG_CSIHnCTL1(GetCSIBaseAddress(csi)) & CSIG_CTL1_EDLE_EXTENDED_ENABLE )
        {
            if (CSI_Message[csi].CsiTxEDLCnt>16U)
            {
		   if(csi==CSIG_0)
		   {
		         CSI_REG_CSIGnTX0W(GetCSIBaseAddress(csi))  = (CSIG_TX0W_EDL_EXTENDED | *CSI_Message[csi].CsiTxAddress); 
		   }
		   else
		   {
	                CSI_REG_CSIHnTX0W(GetCSIBaseAddress(csi))  = (CSIG_TX0W_EDL_EXTENDED | *CSI_Message[csi].CsiTxAddress); 
		   }
		  /* start by writing data to CSIG0TX0W */
                CSI_Message[csi].CsiTxEDLCnt-=16U;
                CSI_Message[csi].CsiTxAddress++;
            }
            else
            {
            	   if(csi==CSIG_0)
		   {
		         CSI_REG_CSIGnTX0W(GetCSIBaseAddress(csi))  = (CSIG_TX0W_EDL_NORMAL | *CSI_Message[csi].CsiTxAddress); 
		   }
		   else
		   {
	                CSI_REG_CSIHnTX0W(GetCSIBaseAddress(csi))   = (CSIG_TX0W_EDL_NORMAL   | *CSI_Message[csi].CsiTxAddress); 
		   }					
		/* start by writing data to CSIG0TX0W */
                CSI_Message[csi].CsiTxEDLCnt = 0U;
                CSI_Message[csi].CsiTxAddress++;
                CSI_Message[csi].CsiTxCnt--;
            }
        }
        else
        {
         	   if(csi==CSIG_0)
		   {
		         CSI_REG_CSIGnTX0H(GetCSIBaseAddress(csi))  =*CSI_Message[csi].CsiTxAddress;
				/* // 2 cpu write in sequence
				 CSI_Message[csi].CsiTxAddress++;
				            CSI_Message[csi].CsiTxCnt--;
 		         CSI_REG_CSIGnTX0H(GetCSIBaseAddress(csi))  =*CSI_Message[csi].CsiTxAddress; 		         
 		         */
		   }
		   else
		   {
		          CSI_REG_CSIHnTX0H(GetCSIBaseAddress(csi))=*CSI_Message[csi].CsiTxAddress;
				  /* // 2 cpu write in sequence
           			CSI_Message[csi].CsiTxAddress++;		
					           CSI_Message[csi].CsiTxCnt--;
		   		CSI_REG_CSIHnTX0H(GetCSIBaseAddress(csi))=*CSI_Message[csi].CsiTxAddress;		   		
		   		*/
		   }
           /* start by writing data to CSIG0TX0H */
           CSI_Message[csi].CsiTxAddress++;
           CSI_Message[csi].CsiTxCnt--;
		          CSI_REG_CSIHnTX0H(GetCSIBaseAddress(csi))=*CSI_Message[csi].CsiTxAddress;
           CSI_Message[csi].CsiTxAddress++;
           CSI_Message[csi].CsiTxCnt--;
        }
    }

    //CSI_REG_CSIHnCTL0(GetCSIBaseAddress(csi)) |=CSIG_CTL0_PWR_PROVIDE_OPERATION_CLOCK;
    return (status);
}

BOOL CSI_FIFO_Send( CSI_TYPE csi,U8 *txbuf, U16 length)
{
    BOOL status = TRUE;
    U8 index=0;
    U32 u32csi_base_adr = GetCSIBaseAddress(csi);   
  //  U32 uTrwa=0;
    
    if (length < 2U) 
    {
        status = FALSE;
    }
    else
    {
        //   uTrwa = (CSI_REG_CSIHnMRWP0(u32csi_base_adr))&0x3f;
		 // fill tx data in
	    for(index=0;index<length;index++)
	    {
		CSI_REG_CSIHnTX0H(u32csi_base_adr)=txbuf[index];
	    }
	//if (bSPI_Master)
        //uTrwa += 0x80080000;
       // CSI_REG_CSIHnMCTL2(GetCSIBaseAddress(csi)) =uTrwa;
       CSI_REG_CSIHnMCTL2(u32csi_base_adr) |=0x80080000;/*CSIHnND[7:0] 08H Specifies the number of data for each memory mode*/

    }

    return (status);
}

void CSI_FIFO_SendEmpty(CSI_TYPE csi)
{    
    U8 index = 0;
    U32 u32csi_base_adr = GetCSIBaseAddress(csi);   
   // U32 uTrwa=0;
          // uTrwa = (CSI_REG_CSIHnMRWP0(u32csi_base_adr))&0x3f;
	    for(index=0;index<8;index++)
	    {
		CSI_REG_CSIHnTX0H(u32csi_base_adr)=0;
	    }
        //uTrwa += 0x80080000;
        //CSI_REG_CSIHnMCTL2(u32csi_base_adr) =uTrwa;
       CSI_REG_CSIHnMCTL2(u32csi_base_adr) |=0x80080000;/*CSIHnND[7:0] 08H Specifies the number of data for each memory mode*/
}

/***********************************************************************
*  Name        : CSIH0_Tx_handler
*  Description : Tx hanlder for CSIH0
*  Parameter   : None
*  Returns     : None
***********************************************************************/
__interrupt void INTCSIH0IC(void)
{
  Tx_Handler(CSIH_0,TRUE);
}

/***********************************************************************
*  Name        : CSIH0_Rx_handler
*  Description : CSIH0  receive interrupt
*  Parameter   : None
*  Returns     : None
***********************************************************************/
/*  */
__interrupt void INTCSIH0IR(void)
{
  Rx_Handler(CSIH_0,TRUE);
}

/***********************************************************************
*  Name        : CSIH0_Error_handler
*  Description : Error hanlder for CSIH0
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void INTCSIH0ICE(void)
{
  Error_Handler(CSIH_0,TRUE);
}

/***********************************************************************
*  Name        : CSIH1_Tx_handler
*  Description : Tx hanlder for CSIH1
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIH1_Tx_handler(void)
{
  Tx_Handler(CSIH_1,FALSE);

}

/***********************************************************************
*  Name        : CSIH1_Rx_handler
*  Description : Rx hanlder for CSIH1
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIH1_Rx_handler(void)
{
  Rx_Handler(CSIH_1,FALSE);
}

/***********************************************************************
*  Name        : CSIH1_Error_handler
*  Description : Error hanlder for CSIH1
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIH1_Error_handler(void)
{
  Error_Handler(CSIH_1,FALSE);
}

/***********************************************************************
*  Name        : CSIH2_Tx_handler
*  Description : Tx hanlder for CSIH2
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIH2_Tx_handler(void)
{
  Tx_Handler(CSIH_2,FALSE);
}

/***********************************************************************
*  Name        : CSIH2_Rx_handler
*  Description : Rx hanlder for CSIH2
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIH2_Rx_handler(void)
{
  Rx_Handler(CSIH_2,FALSE);
}

/***********************************************************************
*  Name        : CSIH2_Error_handler
*  Description : Error hanlder for CSIH2
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIH2_Error_handler(void)
{
  Error_Handler(CSIH_2,FALSE);
}
/***********************************************************************
*  Name        : CSIH3_Tx_handler
*  Description : Tx hanlder for CSIH3
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIH3_Tx_handler(void)
{
  Tx_Handler(CSIH_3,FALSE);
}
/***********************************************************************
*  Name        : CSIH3_Rx_handler
*  Description : Rx hanlder for CSIH3
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIH3_Rx_handler(void)
{
  Rx_Handler(CSIH_3,FALSE);
}

/***********************************************************************
*  Name        : CSIH3_Error_handler
*  Description : Error hanlder for CSIH3
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIH3_Error_handler(void)
{
  Error_Handler(CSIH_3,FALSE);
}
/***********************************************************************
*  Name        : CSIG0_Tx_handler
*  Description : Tx hanlder for CSIG0
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIG0_Tx_handler(void)
{
  Tx_Handler(CSIG_0,FALSE);
}
/***********************************************************************
*  Name        : CSIG0_Rx_handler
*  Description : Rx hanlder for CSIG0
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIG0_Rx_handler(void)
{
  Rx_Handler(CSIG_0,FALSE);
}
/***********************************************************************
*  Name        : CSIG0_Error_handler
*  Description : Error hanlder for CSIG0
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIG0_Error_handler(void)
{
  Error_Handler(CSIG_0,FALSE);
}

/***********************************************************************
*  Name        : Tx_Handler
*  Description : Transmit interrupt.
*  Parameter   : csi		- csi channel
*  Returns     : None
***********************************************************************/
void Tx_Handler( CSI_TYPE csi ,BOOL bIsFIFO)

{
    if(bIsFIFO)
    {
    	//nothing to do?
               if(NULL!=csi_tx_callback[csi])
               	 csi_tx_callback[csi]();  /* send complete */	
     }
     else
     {
        if (CSI_Message[csi].CsiTxCnt == 0U)
        {
           if(NULL!=csi_tx_callback[csi])
           	 csi_tx_callback[csi]();  /* send complete */
        }
        if (CSI_REG_CSIHnCTL1(GetCSIBaseAddress(csi)) & CSIG_CTL1_EDLE_EXTENDED_ENABLE)
        {
            if(CSI_Message[csi].CsiTxCnt>0)
            {
                if (CSI_Message[csi].CsiTxEDLCnt>16U)
                {
                	   if(csi==CSIG_0)
    		   {
    		         CSI_REG_CSIGnTX0W(GetCSIBaseAddress(csi))  = (CSIG_TX0W_EDL_EXTENDED | *CSI_Message[csi].CsiTxAddress);             
    		   }
    		   else
    		   {
                    	CSI_REG_CSIHnTX0W(GetCSIBaseAddress(csi))  = (CSIG_TX0W_EDL_EXTENDED | *CSI_Message[csi].CsiTxAddress);             
    		   }
                     /* start by writing data to CSIG0TX0W */ 
                    CSI_Message[csi].CsiTxEDLCnt-=16U;
                    CSI_Message[csi].CsiTxAddress++;
                }
                else
                {
                	   if(csi==CSIG_0)
    		   {
    		         CSI_REG_CSIGnTX0W(GetCSIBaseAddress(csi))  = (CSIG_TX0W_EDL_EXTENDED | *CSI_Message[csi].CsiTxAddress);             
    		   }
    		   else
    		   {
    	                CSI_REG_CSIHnTX0W(GetCSIBaseAddress(csi))   = (CSIG_TX0W_EDL_NORMAL   | *CSI_Message[csi].CsiTxAddress); 
    		   }			
                   /* start by writing data to CSIG0TX0W */
                    CSI_Message[csi].CsiTxEDLCnt = 0U;
                    CSI_Message[csi].CsiTxAddress++;
                    CSI_Message[csi].CsiTxCnt--;
                }
            }
        }
        else
        {
            if (CSI_Message[csi].CsiTxCnt> 0U)
            {
                    if(csi==CSIG_0)
    		   {
    		         CSI_REG_CSIGnTX0H(GetCSIBaseAddress(csi))  =*CSI_Message[csi].CsiTxAddress;
    		   }
    		   else
    		   {		   	
    		          CSI_REG_CSIHnTX0H(GetCSIBaseAddress(csi))=(U8)(*CSI_Message[csi].CsiTxAddress & 0x00FF);
    		   }
               /* start by writing data to CSIG0TX0H */
               CSI_Message[csi].CsiTxAddress++;
               CSI_Message[csi].CsiTxCnt--;	    
            }
        }
    }
}

/***********************************************************************
*  Name        : Rx_Handler
*  Description : receive data.		  
*  Parameter   : csi		- csi channel
*  Returns     : None
***********************************************************************/

void Rx_Handler( CSI_TYPE csi ,BOOL bIsFIFO)
{
       U8 index=0;
	//U8 rec_length=0;
	U8 rec_byte=0;
	//U32 data[8];
	
    if(bIsFIFO)
    {
        for(index=0;index<8;index++)
        {
            RxData[index] =  (U8)(CSI_REG_CSIHnRX0H(GetCSIBaseAddress(csi)));
        }
       if(NULL!= csi_rx_byte_callback[csi])
             csi_rx_byte_callback[csi](RxData); 	   // handler for every received byte, add for scenario with undefined Rx number       
    }
    else
    {
          if(csi==CSIG_0)
          {		
       	     rec_byte = CSI_REG_CSIGnRX0(GetCSIBaseAddress(csi));		
             }
            else
          {
       	      rec_byte = CSI_REG_CSIHnRX0H(GetCSIBaseAddress(csi));
          }    
            if(NULL!= csi_rx_byte_callback[csi])
             csi_rx_byte_callback[csi](&rec_byte); 	   // handler for every received byte, add for scenario with undefined Rx number
    }
}

/***********************************************************************
*  Name        : Error_Handler
*  Description : SPI error handling, data consistency/ parity / overrun...
*  Parameter   : csi - csi channel
*  Returns     : None
***********************************************************************/
void Error_Handler(CSI_TYPE csi ,BOOL bIsFIFO)
{
    U8 err_type=0;
   
    err_type = (U8)(CSI_REG_CSIHnSTR0(GetCSIBaseAddress(csi)) & (CSIG_STCR0_DCEC|CSIG_STCR0_PEC|CSIG_STCR0_OVEC));
	
    if(NULL!=csi_error_callback[csi])
                 csi_error_callback[csi](err_type);  	
    // clear error	
    CSI_REG_CSIHnSTCR0(GetCSIBaseAddress(csi)) = (CSIG_STCR0_DCEC|CSIG_STCR0_PEC|CSIG_STCR0_OVEC);

}


/***********************************************************************
*  Name        : GetCSIIRQNumber
*  Description : get interrupt channel ID
*  Parameter   : csi - csi channel
*  Returns     : None
***********************************************************************/
U8 GetCSIIRQNumber(CSI_TYPE csi)
{
  U8 IrqNo =0;
  
  if(csi==CSIH_0)
  {
   IrqNo=21;
  }
  else if(csi==CSIH_1)
  {
   IrqNo=108;
  }  
  else if(csi==CSIH_2)
  {
   IrqNo=124;
  }   
  else if(csi==CSIH_3)
  {
   IrqNo=150;
  }   
  else if(csi==CSIG_0)
  {
   IrqNo=19;
  }
  return IrqNo;  
}

/***********************************************************************
*  Name        : GetCSIBaseAddress
*  Description : get register base address
*  Parameter   : csi - csi channel
*  Returns     : 
			  register base address
***********************************************************************/
CPU_INT32U GetCSIBaseAddress(CSI_TYPE csi)
{
  CPU_INT32U addressbase=0;
  
  switch(csi)
  {
  	case CSIH_0:
	  {
	    	addressbase=CSIH0_REG_BASEADD;
			break;
	  }
  	case CSIH_1:
	  {
		addressbase=CSIH1_REG_BASEADD;
		break;
	  }
  	case CSIH_2:
	  {
	   	addressbase=CSIH2_REG_BASEADD;
		break;
	  }
	case CSIH_3:
	  {
	   	addressbase=CSIH3_REG_BASEADD;
		break;
	  }
	case CSIG_0:
	{
		addressbase=CSIG0_REG_BASEADD;
	}	
	default:
		break;
  }
  return addressbase;
}


/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of the can transceiver.
 *
 *  \file       bl_can_transceiver.c
 *  \ingroup    driver_module
 *  \author     sijia.hao <sijia.hao@hirain.com>
 *
 *  \version    1.2.0
 *  \date       05/08/2013
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | -------------
 *      01.00.00 | 17/03/2010 | he.yang          | N/A | BootDrv010001
 *      01.01.00 | 21/02/2011 | ning.chen        | N/A | BootDrv010002
 *      01.02.00 | 05/08/2013 | sijia.hao        | N/A | BootDrv010003
 *
 *****************************************************************************/
#include "bl_can_transceiver.h"
#include "bl_can_if_funcfg.h"
#include "Iodefine.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 277,303,602,781,1532,2100,2103,3112,3227,3453,4130 EOF*/
/*
 * 277:An integer constant expression with negative value is being converted
 * to an unsigned type.
 *
 * MISRA-C:2004 11.3(303):Cast a pointer to an integral type.
 * To address a register must cast an integral type to a pointer.
 *
 * MISRA-C:2004 20.2(602):The identifier is reserved for use by the library.
 * The Bootloader do not use any library funtion and use the underscores to
 * indicate that the function is a interal function.
 *
 * MISRA-C:2004 5.6(781):The identifier is used as a structure/union member.
 * The member of the structure is used through the structure object.
 *
 * 1532:The function is only referenced in one translation unit.
 * all functions in this file are configurations in the Security Module.
 *
 * 2100:Integral promotion : unsigned char promoted to signed int.
 *
 * 2103:Integral promotion, unsigned short promoted to unsigned int.
 * This message will therefore only be generated when a short and an int are of
 * equal size.
 *
 * MISRA-C:2004 14.2(3112):This statement has no side-effect. 
 * The DEBUG_ASSERT macro is used to debug bootloader when the BL_DEBUG is
 * enable. When the BL_DEBUG is disable, the DEBUG_ASSERT macro is null.
 *
 * 3227:The parameter is never modified and so it could be declared with const.
 *
 * MISRA-C:2004 19.7(3453):A function could probably be used instead of this
 * function-like macro.
 *
 * MISRA-C:2004 12.7(4130):Bitwise operations on signed data will give
 * implementation defined results.
 *
 */

/*****************************************************************************
 *  Verify The Configurations of Macro
 *****************************************************************************/

/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/
void ApplCanTransceiverInit(void);
void ApplCanTransceiverDeInit(void);

/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/
#if (CANIF_FUN_INIT_TRANSCEIVER == BL_FUN_ON)
/**************************************************************************//**
 *
 *  \details Initialize can transceiver.
 *
 *  \since V1.0.0
 *
 *****************************************************************************/
void Cantrc_InitTransceiver(void)
{
    /*Can0 STB */

	
     //SBC_vReset();
     ApplCanTransceiverInit();
    
    return ; 
}

void ApplCanTransceiverInit(void)
{
	/* Configure CAN0 EnablePin */
	//PMC0 &= ~(1<<2); /* configure P0_2 as general IO */
    	//PM0 &= ~(1<<2); /* P0_2 Output pin */
    	//P0 &= ~(1<<2);    /* disable the EN pin in tranceiver */
    	PMC10 &=~(1 << 12);		//P10_12  /* configure P10_5 as general IO */
		PM10 &= ~(1 << 12); /* P10_5 Output pin */
    	P10 &= ~(1 << 12);    /* disable the EN pin in tranceiver */
	/* Configure CAN0 GPIO-STB pin P0_4 */ 
    	PMC10 &= ~(1<<11);	//P10_11	 /* configure P0_4 as general IO */
    	PM10 &= ~(1<<11); /* P0_4 Output pin */
    	P10 |= (1<<11);    /* Enable STB pin */
	/* the transceuver is in Pwon/Listen-only mode */
	/* Set CAN0TX as P10_7 and CAN0RX as P10_6 */
    	PMC10 |= 0x00C0; /* Alternative Functions */                     
    	PFC10 |= (0x00C0); 	// ALT 4 		/* Alternative 2 */       
		PFCE10 |= (0x00C0); 
    	PM10 &= ~(1<<7);    /* P0_0 CANTX     Output */                                              
    	PM10 |= 1<<6;  /* P0_1 CANRX     Input */
		P10 |= 0x00C0; /* set Tx/Rx port high level*/
	/* Enable CAN0 by setting P0_2 high */
    	//P0 |= (1<<2); 
    	/* Enable CAN0 by setting P10_5 high */
    	P10 |= ( 1<< 12); 
	/* the transceiver is in normal mode */
}

void ApplCanTransceiverDeInit(void)
{
	/* Configure CAN0 GPIO-STB pin P0_4*/ 
	PMC0 &= ~(1<<4); /* configure P0_4 as general IO */
    	PM0 &= ~(1<<4); /* P0_4 Output pin */
    	P0 &= ~(1<<4);    /* Disable STB pin */
	/* The transceiver entry to sleep mode from normal mode */
}

#endif


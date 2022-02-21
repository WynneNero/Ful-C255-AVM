/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of Bootloader enter.
 *
 *  \file       bl_main.c
 *  \ingroup    booting_manager_module
 *  \author     hewei.zhang <hewei.zhang@hirain.com>
 *              mingqing.tang <mingqing.tang@hirain.com>
 *              xin.shang <xin.shang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      01.00.00 | 17/03/2010 | hewei.zhang      | N/A | Boot010001
 *      02.00.00 | 21/02/2011 | mingqing.tang    | N/A | Boot020001
 *      05.00.00 | 10/09/2013 | xin.shang        | N/A | Boot050001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#include "bl_typedefs.h"
#include "bl_rte.h"
#include "bl_process_driver.h"
#include "bl_booting.h"
#include "Gpio_cfg.h"


/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 506,781,1251,2103 EOF*/
/*
 * 506:Dereferencing pointer value that is possibly NULL.
 * The parameter delay is not a null pointer.
 *
 * MISRA-C:2004 5.6(781):The identifier is used as a structure/union member.
 * The member of the structure is used through the structure object.
 *
 * 1251:Suffixed integer constant causes implicit conversion of other
 * (integral) operand.
 *
 * 2103:Integral promotion, unsigned short promoted to unsigned int.
 * This message will therefore only be generated when a short and an int are of
 * equal size.
 *
 */
#pragma ghs section rodata = ".R_BL_CONST"
const bl_u8_t BootLoaderConstantDID[2][16] = {\
     {'C','2','5','5','-','F','B','L','.','0','1',0x00,0x00,0x00,0x00,0x00},
     {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
};


/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/
 unsigned char BL_upgrade_type=UPGRADE_BY_CAN;
 U8  ProgrammingAttempCounter;
 /**************************************************************************//**
 *
 *  \details Initialize the Bootloader and check the reason of the reset.
 *           If the application is valid the application will be booting,
 *           otherwise the bootloader continues to run.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
int main(void)
{


    bl_BootingFlag_t flag;
	
	__asm("pushsp	 r10-r10");
	__asm("stsr   5,r10,1");
	__asm("mov    0x80000002,r10");
	__asm("ldsr   r10,5,1");
	__asm("popsp	r10-r10");
	

    /*Initialize system*/
    Rte_PreInit();

    flag = Bootm_CheckBootingRequirement();

    if (BOOTING_FLAG_NULL ==flag)
    {
        Bootm_GotoApplication();

        /*never return unless StayInBoot enable and receive a valid SIB frame*/
    }
    else  
    {

		if(flag == BOOTING_FLAG_USER_DEFINE)
        {
        	BL_upgrade_type = UPGRADE_BY_SPI;
        	SocInit();
            for(;;)
            {
                SocApp();
            }
        }
		BL_upgrade_type = UPGRADE_BY_CAN;
		(void)Rte_PostInit();
		
		Rte_ProcessReset(flag);
		
		PROC_SCHEDULE();
		

    }
    return 0;
}



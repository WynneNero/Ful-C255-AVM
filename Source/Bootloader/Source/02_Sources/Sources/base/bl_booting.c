/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of the booting manager module.
 *
 *  \file       bl_booting.c
 *  \ingroup    booting_manager_module
 *  \author     xin.shang <xin.shang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      01.00.00 | 15/03/2010 | hewei.zhang      | N/A | Boot010001
 *      01.02.00 | 16/06/2010 | hewei.zhang      | N/A | Boot010003
 *      01.03.00 | 18/08/2010 | hewei.zhang      | N/A | Boot010004
 *      02.00.00 | 16/05/2011 | mingqing.tang    | N/A | Boot020001
 *      02.05.00 | 25/05/2011 | mingqing.tang    | N/A | Boot020006
 *      03.00.00 | 15/09/2011 | mingqing.tang    | N/A | Boot030001
 *      03.02.00 | 20/10/2011 | mingqing.tang    | N/A | Boot030003
 *      05.00.00 | 19/06/2013 | xin.shang        | N/A | Boot050001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#include "bl_rte.h"
#include "bl_logical_block.h"
#include "bl_data.h"
#include "bl_booting.h"
#include "bl_booting_cfg.h"
#include "config.h"
#include "define.h"
#include "FLS_Drv.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 506,781,1532,2103,3112,3210,3227,3442 EOF*/
/*
 * 506:Dereferencing pointer value that is possibly NULL.
 * The parameter flag is not a null pointer.
 *
 * MISRA-C:2004 5.6(781):The identifier is used as a structure/union member.
 * The member of the structure is used through the structure object.
 *
 * 1532:The function is only referenced in one translation unit.
 *
 * 2103:Integral promotion, unsigned short promoted to unsigned int.
 * This message will therefore only be generated when a short and an int are of
 * equal size.
 *
 * MISRA-C:2004 14.2(3112):This statement has no side-effect.
 * App_GetIntegralityValue is reserved to future.(void)dct is used by IDE to
 * avoid a warning.
 *
 * 3210:The global identifier is declared but is not used.
 * The functions are used in the bl_dcm_cfg.c file.
 * The g_UdsPlatformAdapter is used in the bl_process_driver_cfg.c file.
 *
 * 3227:The parameter is never modified and so it could be declared with const.
 *
 * 3442:Operator other than & or = applied to a volatile object.
 *
 */

/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Type Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/
/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/
/**************************************************************************//**
 *
 *  \details Check the booting flags, if one of the flag is valid, need not to
 *           check the others.
 *
 *  \return Return the flag which is checked valid.
 *
 *  \retval BOOTING_FLAG_NULL - none of the flag is valid.
 *  \retval BOOTING_FLAG_REPROGRAM_VALID - reprogram flag is valid.
 *  \retval BOOTING_FLAG_APPLICATION_VALID - application flag is valid.
 *  \retval BOOTING_FLAG_SYSTEM_RESET - reset flag is valid.
 *
 *  \since  V2.0.0
 *
 *****************************************************************************/
 #if 0
bl_BootingFlag_t Bootm_CheckBootingRequirement(void)
{
    bl_BootingFlag_t flag = (bl_BootingFlag_t)BOOTING_FLAG_NULL;
    bl_u16_t i;
    bl_u16_t number;
    bl_Return_t result;
    const bl_BootingChecker_t *checker;

    number = g_BootingCheckerList.number;
    checker = g_BootingCheckerList.checkerList;

    for (i = 0; i < number; i++)
    {
        result = checker[i](&flag);
        if (BL_ERR_OK == result)
        {
            break;
        }
    }

    return flag;
}
#endif
extern unsigned char application_invalue_flag;
bl_BootingFlag_t Bootm_CheckBootingRequirement(void)
{
    bl_BootingFlag_t  flag = 0;

    U8 buffer[4];
	U8 buffer_clear[4] = {0xff,0xff,0xff,0xff};
    U8 bR = 0;
    U32 data_can=0xa55aa55a;
    U32 data_spi=0xaa5555aa;
	U32 data_app_invalue_flag =0x11223344;

    U32 getdata = 0;
	U32 getdata_rep_flag = 0;
    //Mem_InitMemory(2);
    FLS_vDrvInit();
    if(bR)
    {
        bl_Buffer_t test[4] = {0xa1,0x5a,0xa5,0x5a};
        //Mem_Write
        FLS_u8WriteDataWait(0xff200000, 0x04, test);
    }
    //Mem_Read
    FLS_u8ReadDataWait(0xff200000, 0x04, buffer);
    getdata = (((bl_u32_t)buffer[0]<<24)+((bl_u32_t)buffer[1]<<16)+((bl_u32_t)buffer[2]<<8)+(bl_u32_t)buffer[3]);

	/* uidp5359
	switch(getdata)
	{
		case data_can_flag:
    	    application_invalue_flag = FALSE;		
            flag = BOOTING_FLAG_REPROGRAM_VALID;//in boot for can upgrade
			break;
		
		case data_spi_flag:
			flag = BOOTING_FLAG_USER_DEFINE;//in boot spi upgrade
			break;

		case data_app_invalue_flag:
			application_invalue_flag = TRUE;
			flag = BOOTING_FLAG_SYSTEM_RESET;//in boot 
			break;
			

		default:
			flag = BOOTING_FLAG_NULL;//to app
			FLS_vDrvExit();
			break;

	}
	*/
	if(getdata == data_can)  
    {
    	application_invalue_flag = FALSE;
		/*
		if(getdata_rep_flag != 0xBBBBBBBB)
		{
			response_flag_reset = TRUE;
			FLS_u8WriteDataWait(0xff200000, 0x08, buffer_reset_inboot);
		}
		else
		{
			response_flag_reset = FALSE;
		}
		*/
        flag = BOOTING_FLAG_REPROGRAM_VALID;//in boot for can upgrade
        FLS_u8WriteDataWait(0xff200000, 0x04, buffer_clear);
    }
    else 
    {
    	if(getdata == data_app_invalue_flag)
    	{
			application_invalue_flag = TRUE;
			flag = BOOTING_FLAG_SYSTEM_RESET;//in boot
		}
		else
		{
			if(getdata == data_spi)
			{
				flag = BOOTING_FLAG_USER_DEFINE;//in boot
			}
			else
			{
				flag = BOOTING_FLAG_NULL;//to app
				FLS_vDrvExit();
			}
		}
    }
    //Mem_DeinitMemory(2);
    return flag;
}
/**************************************************************************//**
 *
 *  \details System go to the application.
 *
 *  \note   If the stay-in-boot function is turned on, execute the
 *          stay-in-boot function. If the function return OK, exit and stay in
 *          the bootloader.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
void Bootm_GotoApplication(void)
{
#if(BL_FUN_ON == RTE_FUN_STAY_IN_BOOT)
    bl_Return_t ret;

    ret = Rte_StayInBoot();
    if(BL_ERR_OK == ret)
    {
        /*A valid message of the stay in boot function is received.*/
    }
    else
#endif
    {
        Rte_GotoApplication();
        /*never return*/
    }

    return ;
}

/**************************************************************************//**
 *
 *  \details Check the reprogram flag.
 *
 *  \param[out]  flag - the buffer of the flag.
 *
 *  \return If reprogram flag is checked valid returns BL_ERR_OK, otherwise returns
 *          BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the reprogram flag is checked valid.
 *  \retval BL_ERR_NOT_OK - the reprogram flag is checked invalid.
 *
 *  \since  V5.0.0
 *
 *****************************************************************************/
bl_Return_t Bootm_ReprogramFlagChecker(bl_BootingFlag_t *flag)
{
    bl_Return_t ret;
    
    ret = Dm_IsDefaultData(BOOTM_REPROGRAM_FLAG_DID);
    if (BL_ERR_OK == ret)
    {
        (void)Dm_ClearData(BOOTM_REPROGRAM_FLAG_DID);

        *flag = (bl_BootingFlag_t)BOOTING_FLAG_REPROGRAM_VALID;
    }
    return ret;
}

/**************************************************************************//**
 *
 *  \details Check the application flag.
 *
 *  \param[out]  flag - the buffer of the flag.
 *
 *  \return If application flag is checked valid returns BL_ERR_OK, otherwise
 *          returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the application flag is checked valid.
 *  \retval BL_ERR_NOT_OK - the application flag is checked invalid.
 *
 *  \since  V5.0.0
 *
 *****************************************************************************/
bl_Return_t Bootm_AppValidFlagChecker(bl_BootingFlag_t *flag)
{
    bl_Return_t ret;

    ret = Lbm_IsAllValid();
    if(BL_ERR_OK == ret)
    {
        *flag = (bl_BootingFlag_t)BOOTING_FLAG_APPLICATION_VALID;
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Check the reset flag.
 *
 *  \param[out]  flag - the buffer of the flag.
 *
 *  \return If reset flag is checked valid returns BL_ERR_OK, otherwise returns
 *          BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the reset flag is checked valid.
 *  \retval BL_ERR_NOT_OK - the reset flag is checked invalid.
 *
 *  \since  V5.0.0
 *
 *****************************************************************************/
bl_Return_t Bootm_ResetFlagChecker(bl_BootingFlag_t *flag)
{
    bl_Return_t ret;

    ret = Dm_IsDefaultData(BOOTM_RESET_FLAG_DID);
    if (BL_ERR_OK == ret)
    {
        (void)Dm_ClearData(BOOTM_RESET_FLAG_DID);

        *flag = (bl_BootingFlag_t)BOOTING_FLAG_SYSTEM_RESET;
    }

    return ret;
}


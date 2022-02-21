/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of the adapter module.
 *
 *  \file       bl_adapter.c
 *  \ingroup    communication_adapter_module
 *  \author     heli.zhang <heli.zhang@hirain.com>
 *
 *  \version    5.2.0
 *  \date       19/06/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      03.00.00 | 12/09/2011 | mingqing.tang    | N/A | Boot030001
 *      03.02.00 | 27/09/2011 | mingqing.tang    | N/A | Boot030003
 *      03.03.00 | 29/09/2011 | mingqing.tang    | N/A | Boot030004
 *      03.05.00 | 12/10/2011 | mingqing.tang    | N/A | Boot030006
 *      04.00.00 | 10/07/2012 | mingqing.tang    | N/A | Boot040001
 *      04.02.00 | 15/07/2012 | mingqing.tang    | N/A | Boot040003
 *      04.04.00 | 18/07/2012 | mingqing.tang    | N/A | Boot040005
 *      04.06.00 | 31/07/2012 | mingqing.tang    | N/A | Boot040007
 *      04.10.00 | 07/08/2012 | mingqing.tang    | N/A | Boot040011
 *      04.11.00 | 15/08/2012 | mingqing.tang    | N/A | Boot040012
 *      05.00.00 | 19/06/2013 | heli.zhang       | N/A | Boot050001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *      05.02.00 | 19/06/2014 | mingqing.tang    | N/A | BootSpec050001
 *
 *****************************************************************************/
#include "bl_common.h"
#include "bl_rte.h"
#include "bl_logical_block.h"
#include "bl_app.h"
#include "bl_data.h"
#include "bl_adapter.h"
#include "bl_adapter_cfg.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 506,1532,2103,3112,3227 EOF*/
/*
 * 506:Dereferencing pointer value that is possibly NULL.
 * The parameter delay is not a null pointer.
 *
 * 1532:The function is only referenced in one translation unit.
 *
 * 2103:Integral promotion, unsigned short promoted to unsigned int.
 * This message will therefore only be generated when a short and an int are of
 * equal size.
 *
 * MISRA-C:2004 14.2(3112):This statement has no side-effect.
 * The DEBUG_ASSERT macro was used to debug bootloader when the BL_DEBUG is
 * enable. When the BL_DEBUG is disable, the DEBUG_ASSERT macro is null.
 *
 * 3227:The parameter is never modified and so it could be declared with const.
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
 *  \details Initialize the security access delay info.
 *
 *  \pre The delay must be not a BL_NULL_PTR.
 *
 *  \param[in]  delay  - the pointer of security access delay info in the RAM.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
void Adpt_InitDelayInfo(bl_SecurityDelay_t *delay)
{
#if(ADPT_FUN_SAVE_DELAY_FLAG == BL_FUN_ON)
    bl_Return_t ret;
#endif

    BL_DEBUG_ASSERT_NO_RET(delay != BL_NULL_PTR);

#if (ADPT_FUN_ADVANCED_ATTEMPT_DELAY == BL_FUN_ON)
    delay->failedCntFlagId = g_SecurityDelayInfo.failedCntFlagId;
#endif

#if (ADPT_FUN_SAVE_DELAY_FLAG == BL_FUN_ON)
    delay->delayFlagId = g_SecurityDelayInfo.delayFlagId;

    BL_DEBUG_ASSERT_NO_RET(Dm_IsValidDataId(delay->delayFlagId) == BL_ERR_OK);

    /*check whether delayflag is valid.*/
    ret = Dm_IsDefaultData(delay->delayFlagId);
    if(BL_ERR_OK == ret)
    {
        delay->delayTime    = g_SecurityDelayInfo.delayTime;
        delay->attemptCount = 0u;
    }
    else
    {
        delay->delayTime    = 0u;
        delay->attemptCount = g_SecurityDelayInfo.attemptCount;
    }
#else


    /*delay->delayTime    = g_SecurityDelayInfo.delayTime;*/
    delay->attemptCount = g_SecurityDelayInfo.attemptCount;
#endif

    return ;
}

/**************************************************************************//**
 *
 *  \details Call the Lbm_GetBlock() to check the address and size information
 *           whether are valid. If it is valid, save them to Download Context.
 *
 *  \param[in]  dct     - the pointer of current download context.
 *  \param[in]  address - the address of request download.
 *  \param[in]  size    - the size of request download.
 *
 *  \return If Activation is successfully return BL_ERR_OK, otherwise return
 *          BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK       - Activation successfully.
 *  \retval BL_ERR_NOT_OK   - Activation unsuccessfully.
 *
 *  \since  V4.0.0
 *
 *****************************************************************************/
bl_Return_t Adpt_ActivateDownload(bl_DownContext_t *dct,
                                  bl_Address_t address,
                                  bl_Size_t size)
{
    bl_Return_t ret = BL_ERR_NOT_OK;

    if(0UL != size)
    {
        /*get the logical block id, according to addr,size and status.*/
        ret = Lbm_GetBlock(dct, address, size);

        /*after get logical block id, save address and size, and set status.*/
        if(BL_ERR_OK == ret)
        {
            ret = Rte_SaveAddressInfo(dct, address, size);
        }
    }

    if(ret != BL_ERR_OK)
    {
        Rte_ClearAddressInfo(dct);
        /*clear erase and write status.*/
        Rte_ClearDownStatus(dct, ADPT_SYSTEM_STATUS_MASK);
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Download the data of application or calibration to nonvolatile
 *           memorys.
 *
 *  \param[in]  dct     - the pointer of current download context.
 *  \param[in]  address - the address of the data.
 *  \param[in]  size    - the size of the data.
 *  \param[in]  buffer  - the contents of the data.
 *
 *  \retval BL_ERR_OK           - Download successfully.
 *  \retval BL_ERR_NOT_OK       - Download unsuccessfully.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_Return_t Adpt_DownloadData(bl_DownContext_t *dct,
                              bl_Address_t address,
                              bl_Size_t size,
                              const bl_Buffer_t *buffer)
{
    bl_Return_t ret;

    ret = Lbm_Write(dct, address, size, buffer);
    if(BL_ERR_OK == ret)
    {
        /*after writting data sucessfully, set status.*/
        Rte_SetDownStatus(dct, RTE_SYSFLAG_WRITE_DATA);
    }
    else
    {
        Rte_ClearAddressInfo(dct);
        /*clear erase and write status.*/
        Rte_ClearDownStatus(dct, ADPT_SYSTEM_STATUS_MASK);
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Erase a logical block.
 *
 *  \param[in]  dct     - the pointer of current download context.
 *  \param[in]  address - the address of erased logical block.
 *  \param[in]  size    - the size of erased logical block.
 *
 *  \retval BL_ERR_OK           - Erasing successfully.
 *  \retval BL_ERR_NOT_OK       - Erasing unsuccessfully.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_Return_t Adpt_EraseLB(bl_DownContext_t *dct,
                         bl_Address_t address,
                         bl_Size_t size)
{
    bl_Return_t ret;

    /*get logical block id.*/
    ret = Lbm_GetBlock(dct, address, size);
    if(BL_ERR_OK == ret)
    {
        ret = Lbm_Erase(dct);
        if(BL_ERR_OK == ret)
        {
            Rte_SetDownStatus(dct, RTE_SYSFLAG_ERASE_BLOCK);
        }
        else
        {
            Rte_ClearDownStatus(dct, ADPT_SYSTEM_STATUS_MASK);
        }
    }

    Rte_ClearAddressInfo(dct);

    return ret;
}

/**************************************************************************//**
 *
 *  \details Verify checksum value of a logical block.
 *
 *  \param[in]  dct   - the pointer of current download context.
 *  \param[in]  size  - the size of checksum value.
 *  \param[in]  value - the pointer of checksum value.
 *
 *  \retval BL_ERR_OK           - Verify successfully.
 *  \retval BL_ERR_NOT_OK       - Verify unsuccessfully.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
/*lint -e{818}*/
bl_Return_t Adpt_VerifyData(bl_DownContext_t *dct,
                            bl_Size_t size,
                            bl_Buffer_t *value) /*PRQA S 3673*/
{
    bl_Return_t ret=0;

#if(ADPT_FUN_GET_INTEGRALITY_VALUE == BL_FUN_ON)
    /*When the ADPT_FUN_GET_INTEGRALITY_VALUE is enable,
      the value must be modified. So the value is not a const pointer.*/
    App_GetIntegralityValue(dct, &size, value);
#endif

    ret = Lbm_Verify(dct, size, value);
    /*clear address, size and status.*/
    Rte_ClearAddressInfo(dct);

    Rte_ClearDownStatus(dct, ADPT_SYSTEM_STATUS_MASK);

    return ret;
}

/**************************************************************************//**
 *
 *  \details Check compatibility of all downloaded logical block.
 *
 *  \param[in]  dct   - the pointer of current download context.
 *
 *  \retval BL_ERR_OK      - Check successfully.
 *  \retval BL_ERR_NOT_OK  - Check unsuccessfully.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_Return_t Adpt_CheckCompatibility(void)
{
    bl_Return_t ret = BL_ERR_OK;

#if(BL_FUN_ON == ADPT_FUN_CHECK_COMPATIBILITY)
    /*if not ok, need to set invalid status of logical block. */
    ret = App_CheckCompatibility();
#endif

    /*  Maybe the checking of Compatiblity is failure when
        ADPT_FUN_CHECK_COMPATIBILITY was BL_FUN_ON.*/
    if(BL_ERR_OK == ret) /*lint !e774*//*PRQA S 3355,3358*/
    {
        ret = Lbm_IsAllValid();
    }

    /*save status into nonvolatile memory*/
    (void)Lbm_SaveAllStatus();

    return ret;
}

/**************************************************************************//**
 *
 *  \details Check whether security access is available.
 *
 *  \pre The delay must be not a BL_NULL_PTR.
 *
 *  \param[in]  delay  - the pointer of security access delay info.
 *
 *  \return If delaytime is zreo, return BL_ERR_OK,
 *          otherwise, return BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK       - Security access is avaliable.
 *  \retval BL_ERR_NOT_OK   - Security access is not allowed.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_Return_t Adpt_IsAccessible(const bl_SecurityDelay_t *delay)
{
    bl_Return_t ret = BL_ERR_NOT_OK;

    BL_DEBUG_ASSERT_NO_RET(delay != BL_NULL_PTR);

    /*only when delaytime is Zero, security access is avaliable.*/
    if(0UL == delay->delayTime)
    {
        ret = BL_ERR_OK;
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Decrease the attemptcount of security access.
 *
 *  \pre The delay must be not a BL_NULL_PTR.
 *
 *  \param[in]  delay  - the pointer of security access delay info.
 *
 *  \return Return the remain attemptcount of security access.
 *
 *  \note If attemptcount is zero, updating delaytime is needed.
 *
 *  \since  V5.0.0
 *
 *****************************************************************************/
bl_u16_t Adpt_DecreaseAttemptCount(bl_SecurityDelay_t *delay)
{
    bl_u16_t remainCount;

    BL_DEBUG_ASSERT_NO_RET(delay != BL_NULL_PTR);

    if (delay->attemptCount != 0)
    {
        delay->attemptCount -= 1;
    }

    if (0 == delay->attemptCount)
    {
        delay->delayTime = g_SecurityDelayInfo.delayTime;
    }

    remainCount = delay->attemptCount;
    return remainCount;
}

/**************************************************************************//**
 *
 *  \details Decrease the delaytime of security access.
 *
 *  \pre The delay must be not a BL_NULL_PTR.
 *
 *  \param[in]  delay  - the pointer of security access delay info.
 *
 *  \return Return void.
 *
 *  \note If delaytime is zero, updating attemptcount is needed.
 *
 *  \since  V5.0.0
 *
 *****************************************************************************/
void Adpt_DelayTimeCallback(bl_SecurityDelay_t *delay)
{
    BL_DEBUG_ASSERT_NO_RET(delay != BL_NULL_PTR);

    if(delay->delayTime != 0UL)
    {
        delay->delayTime -= 1UL;
    }
    else
    {
        if(0 == delay->attemptCount)
        {
#if(ADPT_FUN_SAVE_DELAY_FLAG == BL_FUN_ON)
            (void)Dm_ClearData(delay->delayFlagId);
#endif
            delay->attemptCount = 3;
        }
    }

    return ;
}


/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of the logical block manager module.
 *
 *  \file       bl_logical_block.c
 *  \ingroup    lb_manager_module
 *  \author     mingqing.tang <mingqing.tang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      03.00.00 | 12/09/2011 | mingqing.tang    | N/A | Boot030001
 *      03.01.00 | 16/09/2011 | mingqing.tang    | N/A | Boot030002
 *      03.02.00 | 23/09/2011 | mingqing.tang    | N/A | Boot030003
 *      03.03.00 | 17/10/2011 | mingqing.tang    | N/A | Boot030004
 *      03.05.00 | 27/10/2011 | mingqing.tang    | N/A | Boot030006
 *      03.06.00 | 08/11/2011 | mingqing.tang    | N/A | Boot030007
 *      03.08.00 | 30/11/2011 | mingqing.tang    | N/A | Boot030009
 *      03.11.00 | 15/02/2012 | mingqing.tang    | N/A | Boot030012
 *      03.14.00 | 13/03/2012 | mingqing.tang    | N/A | Boot030015
 *      03.15.00 | 26/03/2012 | mingqing.tang    | N/A | Boot030016
 *      03.18.00 | 29/05/2012 | mingqing.tang    | N/A | Boot030019
 *      04.00.00 | 15/07/2012 | mingqing.tang    | N/A | Boot040001
 *      04.01.00 | 15/07/2012 | mingqing.tang    | N/A | Boot040002
 *      04.03.00 | 15/07/2012 | mingqing.tang    | N/A | Boot040004
 *      04.04.00 | 15/07/2012 | mingqing.tang    | N/A | Boot040005
 *      04.10.00 | 15/07/2012 | mingqing.tang    | N/A | Boot040011
 *      04.12.00 | 15/07/2012 | mingqing.tang    | N/A | Boot040013
 *      04.16.00 | 15/07/2012 | mingqing.tang    | N/A | Boot040016
 *      04.19.00 | 15/07/2012 | mingqing.tang    | N/A | Boot040020
 *      04.21.00 | 15/07/2012 | mingqing.tang    | N/A | Boot040022
 *      04.26.00 | 15/07/2012 | mingqing.tang    | N/A | Boot040026
 *      04.27.00 | 15/07/2012 | mingqing.tang    | N/A | Boot040028
 *      04.30.00 | 10/04/2013 | mingqing.tang    | N/A | Boot040031
 *      05.00.00 | 19/06/2013 | mingqing.tang    | N/A | Boot050001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#include "bl_common.h"
#include "bl_security.h"
#include "bl_data.h"
#include "bl_memory.h"
#include "bl_logical_block.h"
#include "bl_logical_block_cfg.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 306,506,602,771,781,1251,1257,1503,1532,2103,3112,3199,3227,3453 EOF*/
/*
 * MISRA-C:2004 11.3(306):Cast a pointer to an integral type.
 * To address a flash must cast an integral type to a pointer.
 *
 * 506:Dereferencing pointer value that is possibly NULL.
 * The parameter delay is not a null pointer.
 *
 * MISRA-C:2004 20.2(602):The identifier is reserved for use by the library.
 * The Bootloader do not use any library funtion and use the underscores to
 * indicate that the function is a interal function.
 *
 * MISRA-C:2004 14.6(771):More than one break statement is being used to
 * terminate an iteration statement.
 * it can simplify the code and have no side-effect.
 *
 * MISRA-C:2004 5.6(781):The identifier is used as a structure/union member.
 * The member of the structure is used through the structure object.
 *
 * 1251:Suffixed integer constant causes implicit conversion of other
 * (integral) operand.
 *
 * 1257:Suffixed integer constant implicitly converted to smaller integer type
 * on assignment.
 *
 * MISRA-C:2004 14.1(1503):The function is defined but is not used within this
 * project.
 * these functions will be used When correlative macro is enable.
 *
 * 1532:The function is only referenced in one translation unit.
 * all functions in this file are configurations in the Security Module.
 *
 * 2103:Integral promotion, unsigned short promoted to unsigned int.
 * This message will therefore only be generated when a short and an int are of
 * equal size.
 *
 * MISRA-C:2004 14.2(3112):This statement has no side-effect.
 * The DEBUG_ASSERT macro is used to debug bootloader when the BL_DEBUG is
 * enable. When the BL_DEBUG is disable, the DEBUG_ASSERT macro is null.
 *
 * 3199:This assignment is redundant. The value is never subsequently used.
 *
 * 3227:The parameter is never modified and so it could be declared with const.
 *
 * MISRA-C:2004 19.7(3453):A function could probably be used instead of this
 * function-like macro.
 * These macros have no side-effect.
 *
 */

/*****************************************************************************
 *  Verify The Configurations of Function Macro
 *****************************************************************************/
#if ((LBM_ATTEMPT_COUNTER_SIZE >= LBM_COUNTER_MAX_SIZE)\
    || (LBM_SUCCESS_COUNTER_SIZE >= LBM_COUNTER_MAX_SIZE)\
    || (LBM_ATTEMPT_COUNTER_SIZE != LBM_SUCCESS_COUNTER_SIZE))
#error "the size of counter is error."
#endif

#if ((RTE_FUN_FINGERPRINT == BL_FUN_OFF) \
    && (LBM_FUN_SAVE_FINGERPRINT == BL_FUN_ON))
#error "Close the fingerprint function of the LBM."
#endif
/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/
/** check whether the id indicates a valid logical block.*/
#define LBM_IS_VALID_ID(id)             ((id) < g_LogicalBlockList.number)

#define LBM_IS_IN_REGION(s,e,ts,te)     (((s)>=(ts)) && ((e)<=(te)))
#define LBM_MAKE_LOCAL_ADDR(lb,address) ((address) & ((lb)->offsetMask))

#define LBM_IS_VALID_MASK(dct,mask)     Rte_IsAllValidStatus((dct),(mask))

#define LBM_IS_GETTABLE(dct,lb)     LBM_IS_VALID_MASK(dct,(lb)->getLbMask)
#define LBM_IS_WRITABLE(dct,lb)     LBM_IS_VALID_MASK(dct,(lb)->writeLbMask)
#define LBM_IS_ERASABLE(dct,lb)     LBM_IS_VALID_MASK(dct,(lb)->eraseLbMask)
#define LBM_IS_VERIFIABLE(dct,lb)   LBM_IS_VALID_MASK(dct,(lb)->verifyLbMask)

#define LBM_GET_LBPTR(id)           (&g_LogicalBlockList.lbList[id])

#define LBM_SET_STATUS(lb,st)       ((lb)->status[0] = (st))
#define LBM_SET_LBSTATUS(id,st)     LBM_SET_STATUS(LBM_GET_LBPTR(id),st)

#define LBM_GET_STATUS(lb)          ((lb)->status[0])
#define LBM_GET_LBSTATUS(id)        LBM_GET_STATUS(LBM_GET_LBPTR(id))

#define LBM_IS_UPDATING_STATUS(lb)  (LBM_STATUS_UPDATING == LBM_GET_STATUS(lb))
#define LBM_IS_VALID_STATUS(lb)     (LBM_STATUS_VALID == LBM_GET_STATUS(lb))
#define LBM_IS_UPDATED_STATUS(lb)   (LBM_STATUS_UPDATED == LBM_GET_STATUS(lb))
#define LBM_IS_NOCARE_STATUS(lb)    (LBM_STATUS_NOT_CARE == LBM_GET_STATUS(lb))

#define LBM_IS_A_DRIVER(lb)         (LBM_TYPE_DRIVER == ((lb)->type))
/*****************************************************************************
 *  Internal Type Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/
/** \brief Update the status of all logical blocks.*/
static void _Lbm_UpdateStatus(void);
/** \brief Update the status of a logical block.*/
static void _Lbm_ReadAndUpdateStatus(const bl_LogicalBlock_t *lb);
/** \brief Find a logical block.*/
static bl_Return_t _Lbm_FindLogicalBlock(bl_Address_t address,
                                          bl_Size_t size,
                                          bl_u16_t *foundId);
/** \brief Check a region whether is in the logical block.*/
static bl_Return_t _Lbm_IsInLogicalBlock(const bl_LogicalBlock_t *lb,
                                          bl_Address_t address,
                                          bl_Address_t limitAddr);
/** \brief Check a region whether is in the segment list.*/
static bl_Return_t _Lbm_IsInSegmentList(const bl_SegmentList_t *segment,
                                         bl_Address_t address,
                                         bl_Address_t limitAddr);
/** \brief Check the download context whether need be updated.*/
static bl_Return_t _Lbm_IsUpdatable(bl_u16_t curId,bl_u16_t foundId);
/** \brief Update the lbId and downSeg information in the download context.*/
static void _Lbm_UpdateBlockInfoInDct(bl_DownContext_t *dct,bl_u16_t newId);
/** \brief Check the parameters of functions whether are valid.*/
static bl_Return_t _Lbm_IsValidParam(const bl_DownContext_t *dct,
                                        const bl_Buffer_t *buf);
/** \brief Perform the write operation of the logical block.*/
static bl_Return_t _Lbm_Write(const bl_LogicalBlock_t *lb,
                               bl_Address_t address,
                               bl_Size_t size,
                               const bl_Buffer_t *buffer);
/** \brief Clear the valid flag of the logical block.*/
/*
static bl_Return_t _Lbm_TryToClearValidFlag(const bl_LogicalBlock_t *lb);
*/
/** \brief Perform the erase operation of the logical block.*/
static bl_Return_t _lbm_Erase(const bl_LogicalBlock_t *lb);
/** \brief Check the hash value of the logical block whether is valid.*/
static bl_Return_t _Lbm_IsValidHash(const bl_DownContext_t *dct,
                                     bl_Size_t size,
                                     const bl_Buffer_t *buf);
/** \brief Calculate the hash value of the download segments.*/
static bl_Return_t _Lbm_CalculateHashByDct(const bl_DownContext_t *dct);
/** \brief Initialize the memory of the logical block.*/
static bl_Return_t _Lbm_InitMemory(const bl_LogicalBlock_t *lb);
/** \brief Look for the memory id.*/
static bl_u16_t _Lbm_LookForMemId(const bl_LogicalBlock_t *lb);
/** \brief Save the status of the logical block to ROM.*/
static bl_Return_t _Lbm_SaveStatus(const bl_LogicalBlock_t *block);

#if (LBM_FUN_SUCCESS_COUNTER == BL_FUN_ON)
/** \brief add the success count of a logical block.*/
static bl_Return_t _Lbm_AddSuccessCnt(const bl_LogicalBlock_t *lb);
/** \brief get the success count of a logical block.*/
bl_Return_t _Lbm_GetSuccessCount(bl_u16_t did,
                                    bl_SuccessCounter_t *count);
/** \brief add save success count of a logical block into nonvolatile memory.*/
bl_Return_t _Lbm_SaveSuccessCount(bl_u16_t did,
                                    bl_SuccessCounter_t count);
#endif

#if (LBM_FUN_ATTEMPT_COUNTER == BL_FUN_ON)
/** \brief add the attempt count of a logical block.*/
static bl_Return_t _Lbm_AddAttemptCnt(const bl_LogicalBlock_t *lb);
/** \brief get the attempt count of a logical block.*/
bl_Return_t _Lbm_GetAttemptCount(bl_u16_t did,
                                    bl_AttemptCounter_t *count);
/** \brief add save attempt count of a logical block into nonvolatile memory.*/
bl_Return_t _Lbm_SaveAttemptCount(bl_u16_t did,
                                    bl_AttemptCounter_t count);
#endif

#if (LBM_FUN_SAVE_FINGERPRINT == BL_FUN_ON)
/** \brief add save fingerprint of a logical block into nonvolatile memory.*/
bl_Return_t _Lbm_SaveFingerprint(const bl_LogicalBlock_t *block);
#endif

/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/
#define RTE_FINGERPRINT_SIZE 8
#if (LBM_FUN_SAVE_FINGERPRINT == BL_FUN_ON)
/** \brief the fingerprint buffer of a logical block.*/
static bl_Buffer_t gs_LbmFingerprint[RTE_FINGERPRINT_SIZE];
#endif
/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/
/**************************************************************************//**
 *
 *  \details initialize the logical block manager module.
 *
 *  \return If this module is initialized successfully returns BL_ERR_OK,
 *          otherwise returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK       - initialize successfully.
 *  \retval BL_ERR_NOT_OK   - initialize unsuccessfully.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
bl_Return_t Lbm_Init(void)
{
    _Lbm_UpdateStatus();

    return BL_ERR_OK;
}

/**************************************************************************//**
 *
 *  \details look up a logical block by the address and size information.
 *
 *  \param[in]  dct     - the pointer of current download context.
 *  \param[in]  address - the general address of the logical block.
 *  \param[in]  size    - the size of the logical block.
 *
 *  \retval BL_ERR_OK - the logical block is erased successfully.
 *  \retval BL_ERR_NOT_OK - the logical block is erased unsuccessfully.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_Return_t Lbm_GetBlock(bl_DownContext_t *dct,
                            bl_Address_t address,
                            bl_Size_t size)
{
    bl_Return_t ret;
    bl_Return_t isUpdate;
    bl_u16_t foundId;
#if (LBM_FUN_AUTO_CALCULATE_HASH == BL_FUN_ON)
    bl_Return_t isRead;
    const bl_LogicalBlock_t *block;
#endif

    BL_DEBUG_ASSERT_PARAM(dct != BL_NULL_PTR);

    ret = _Lbm_FindLogicalBlock(address,size,&foundId);
    if (BL_ERR_OK == ret)
    {
        isUpdate = _Lbm_IsUpdatable(dct->lbId,foundId);
        if (BL_ERR_OK == isUpdate)
        {
            _Lbm_UpdateBlockInfoInDct(dct,foundId);

#if (LBM_FUN_AUTO_CALCULATE_HASH == BL_FUN_ON)
            isRead = Mem_IsReadable(block->memId);
            if (isRead != BL_ERR_OK)   /*this logical block is not readable.*/
            {
                Secm_StartHash();
#if ((RTE_SYSTEM_SECURITY_CLASS == BL_SECURITY_CLASS_C) \
    || (RTE_SYSTEM_SECURITY_CLASS == BL_SECURITY_CLASS_CCC))
                /*  according to the HIS spec. Use the address and size of
                    the downloaded segment to calculate the hash value.*/
                ret = Secm_UpdateHashByAddr(address, size);
#endif
            }
#endif
        }
        else if (isUpdate != LBM_ERR_UPDATED_ID)
        {
            ret = BL_ERR_NOT_OK;
        }
        else
        {

        }
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Clear the logical block in the download context.
 *
 *  \param[in]  dct - the pointer of current download context.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
void Lbm_ClearBlock(bl_DownContext_t *dct)
{
    const bl_LogicalBlock_t *block;

    BL_DEBUG_ASSERT_PARAM(dct != BL_NULL_PTR);

    if (LBM_IS_VALID_ID(dct->lbId))
    {
        block = LBM_GET_LBPTR(dct->lbId);
        if (LBM_IS_UPDATING_STATUS(block))
        {
            LBM_SET_STATUS(block,LBM_STATUS_INVALID);
        }

        dct->lbId = BL_ERROR_ID_16BIT;
    }

    return ;
}
/**************************************************************************//**
 *
 *  \details write data to a logical block.
 *
 *  \param[in]  dct     - the pointer of current download context.
 *  \param[in]  address - the general address of the data.
 *  \param[in]  size    - the size of the data.
 *  \param[in]  buffer  - the content of the data.
 *
 *  \retval BL_ERR_OK       - the logical block is written successfully.
 *  \retval BL_ERR_NOT_OK   - the logical block is written unsuccessfully.
 *
 *  \note If the parameters is invalid or the writing operation cannot be
 *        performed, the status of the logical block is not changed.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_Return_t Lbm_Write(const bl_DownContext_t *dct,
                       bl_Address_t address,
                       bl_Size_t size,
                       const bl_Buffer_t *buffer)
{
    bl_Return_t ret;
    const bl_LogicalBlock_t *block = BL_NULL_PTR;
    bl_u16_t tmpStatus = LBM_STATUS_NOT_EXIST;

    do
    {
        ret = _Lbm_IsValidParam(dct,buffer);
        if (ret != BL_ERR_OK)
        {
            break;
        }

        block = LBM_GET_LBPTR(dct->lbId);

        /*check the write mask of logical block*/
        ret = LBM_IS_WRITABLE(dct,block);
        if (ret != BL_ERR_OK)
        {
            break;
        }

        tmpStatus = LBM_STATUS_INVALID;
        ret = _Lbm_Write(block,address,size,buffer);
        if (ret != BL_ERR_OK)
        {
            break;
        }

#if (LBM_FUN_AUTO_CALCULATE_HASH == BL_FUN_ON)
        ret = Mem_IsReadable(block->memId);
        if (ret != BL_ERR_OK)   /*this logical block is not readable.*/
        {
            ret = Secm_UpdateHash(size,buffer);
        }
#endif
        /*  Maybe the updating of hash is failure when
            LBM_FUN_AUTO_CALCULATE_HASH was BL_FUN_ON.*/
        if (BL_ERR_OK == ret) /*lint !e774*//*PRQA S 3355,3358*/
        {
            tmpStatus = LBM_STATUS_UPDATING;
        }
    }while(0); /*lint !e717*/

    if ((tmpStatus != LBM_STATUS_NOT_EXIST)
        && (block != BL_NULL_PTR))
    {
        LBM_SET_STATUS(block,tmpStatus);
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Erase a logical block.
 *           If the macro 'LBM_FUN_ATTEMPT_COUNTER' is enabled, this function
 *           will try to add the attempt count of the logical block.
 *           If the macro 'LBM_FUN_SAVE_FINGERPRINT' is enabled, this
 *           function will try to save the fingerprint to the data manager
 *           module.
 *
 *  \param[in]  dct - the pointer of current download context.
 *
 *  \retval BL_ERR_OK - the logical block is erased successfully.
 *  \retval BL_ERR_NOT_OK - the logical block is erased unsuccessfully.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_Return_t Lbm_Erase(const bl_DownContext_t *dct)
{
    bl_Return_t ret;
    const bl_LogicalBlock_t *block = BL_NULL_PTR;
    bl_u16_t tmpStatus = LBM_STATUS_NOT_EXIST;

    do
    {
        ret = _Lbm_IsValidParam(dct,BL_VIRTUAL_PTR);
        if (ret != BL_ERR_OK)
        {
            break;
        }

        block = LBM_GET_LBPTR(dct->lbId);
        /*If the status of this logical block is LBM_STATUS_UPDATING, this
          logical block is not erased again.*/
        if (LBM_IS_UPDATING_STATUS(block))
        {
            ret = BL_ERR_NOT_OK;
            break;
        }

        /*Check the erase mask of logical block*/
        ret = LBM_IS_ERASABLE(dct,block);
        if (ret != BL_ERR_OK)
        {
            break;
        }

/*
 *change by li weikun 2017-8-4,some board erase rom fail cause by this step.
 */
#if (LBM_FUN_ATTEMPT_COUNTER == BL_FUN_ON)
//    	ret = _Lbm_AddAttemptCnt(block);
        if (ret != BL_ERR_OK)
        {
            break;
        }
#endif

#if (LBM_FUN_SAVE_FINGERPRINT == BL_FUN_ON)
        ret = _Lbm_SaveFingerprint(block);
        if (ret != BL_ERR_OK)
        {
            break;
        }
#endif

        /*Set the temp status of this logical block.*/
        tmpStatus = LBM_STATUS_INVALID;
		/*
        ret = _Lbm_TryToClearValidFlag(block);
        if (ret != BL_ERR_OK)
        {
            break;
        }
		*/
        ret = _lbm_Erase(block);
        if (ret != BL_ERR_OK)
        {
            break;
        }

        tmpStatus = LBM_STATUS_UPDATING;
    }while(0);/*lint !e717*/

    if ((tmpStatus != LBM_STATUS_NOT_EXIST)
        && (block != BL_NULL_PTR))
    {
        LBM_SET_STATUS(block,tmpStatus);
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details check the logical block whether is downloaded successfully.
 *
 *  \param[in]  dct     - the pointer of current download context.
 *  \param[in]  size    - the size of a hash value.
 *  \param[in]  value   - the hash value.
 *
 *  \retval BL_ERR_OK - the logical block is downloaded successfully.
 *  \retval BL_ERR_NOT_OK - the logical block is downloaded unsuccessfully.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_Return_t Lbm_Verify(const bl_DownContext_t *dct,
                        bl_Size_t size,
                        const bl_Buffer_t *value)
{
    bl_Return_t ret=0;
    const bl_LogicalBlock_t *block = BL_NULL_PTR;
    bl_u16_t tmpStatus = LBM_STATUS_NOT_EXIST;

    do
    {
        ret = _Lbm_IsValidParam(dct,value);
        if (ret != BL_ERR_OK)
        {
            break;
        }

        block = LBM_GET_LBPTR(dct->lbId);
        /*Check the verify mask of logical block*/
        ret = LBM_IS_VERIFIABLE(dct,block);
        if (ret != BL_ERR_OK)
        {
            break;
        }

        /*Set the temp status of this logical block.*/
        tmpStatus = LBM_STATUS_INVALID;

        ret = _Lbm_IsValidHash(dct,size,value);
        if (ret != BL_ERR_OK)
        {
            break;
        }

        if (LBM_IS_A_DRIVER(block))
        {
            ret = _Lbm_InitMemory(block);
            if (ret != BL_ERR_OK)
            {
                break;
            }
        }
        else
        {
            /*The block type is not a driver.*/
#if (LBM_FUN_SUCCESS_COUNTER == BL_FUN_ON)
            ret = _Lbm_AddSuccessCnt(block);
            if (ret != BL_ERR_OK)
            {
                break;
            }
#endif

#if (LBM_FUN_AUTO_DRIVER_DEINIT == BL_FUN_ON)
            ret = Mem_DeinitMemory(block->memId);
            if (ret != BL_ERR_OK)
            {
                break;
            }
#endif
        }

        tmpStatus = LBM_STATUS_UPDATED;
    }while(0);/*lint !e717*/

    if ((tmpStatus != LBM_STATUS_NOT_EXIST)
        && (block != BL_NULL_PTR))
    {
        LBM_SET_STATUS(block,tmpStatus);
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details check the status of all logical blocks are whether valid or
 *           updated. If the status of a logical block is LBM_STATUS_NOT_CARE,
 *           the status of this logical block do not effect return value.
 *
 *  \return If the status of a logical block is invalid or not_init returns
 *          BL_ERR_NOT_OK, otherwise returns BL_ERR_OK.
 *
 *  \retval BL_ERR_OK - all logical blocks are valid.
 *  \retval BL_ERR_NOT_OK - a logical block is invalid.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_Return_t Lbm_IsAllValid(void)
{
    bl_u16_t i;
    bl_Return_t ret = BL_ERR_OK;
    const bl_LogicalBlock_t *block;

    BL_DEBUG_ASSERT_CONFIG(g_LogicalBlockList.number != 0);

    for (i = 0; LBM_IS_VALID_ID(i); i++)
    {
        block = LBM_GET_LBPTR(i);
        if (LBM_IS_VALID_STATUS(block)
            || LBM_IS_UPDATED_STATUS(block)
            || LBM_IS_NOCARE_STATUS(block))
        {
        }
        else
        {
            ret = BL_ERR_NOT_OK;
            break;
        }
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Read the valid flag of all logical blocks and update the status in
 *           the logical block information. If a logical block do not have its
 *           valid flag (the validFlagId is configurated to BL_ERROR_ID_16BIT),
 *           the status of this logical block will be set LBM_STATUS_NOT_CARE.
 *
 *  \return none
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
void Lbm_UpdateStatus(void)
{
    _Lbm_UpdateStatus();
}

/**************************************************************************//**
 *
 *  \details save the status of the logical block. When the status of a logical
 *           block is updated, save it.
 *
 *  \param[in]  id - the index of the logical block array.
 *
 *  \return If a logical block statuses are saved into ROM return BL_ERR_OK,
 *          otherwise return BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the status of a logical block is saved successfully.
 *  \retval BL_ERR_NOT_OK - a logical block status is saved failure.
 *
 *  \warning If the status of the logical block is not LBM_STATUS_UPDATED, this
 *           function will return BL_ERR_OK.
 *  \warning If the validFlagId of the logical block is invalid, this function
 *           will return BL_ERR_OK.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_Return_t Lbm_SaveStatus(bl_u16_t id)
{
    bl_Return_t ret = BL_ERR_NOT_OK;

    if (LBM_IS_VALID_ID(id))
    {
        ret = _Lbm_SaveStatus(LBM_GET_LBPTR(id));
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details save the status of all logical block. When the status of a logical
 *           block is updated, save it.
 *
 *  \return If all of logical block statuses are saved into ROM return
 *          BL_ERR_OK, otherwise return BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - all of statuses are saved successfully.
 *  \retval BL_ERR_NOT_OK - at least one logical block status is saved failure.
 *
 *  \warning If the number of logical block is zero, this function return
 *           BL_ERR_OK.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_Return_t Lbm_SaveAllStatus(void)
{
    bl_Return_t ret = BL_ERR_OK;
    bl_u16_t i;

    BL_DEBUG_ASSERT(g_LogicalBlockList.number != 0);

    for (i = 0; LBM_IS_VALID_ID(i); i++)
    {
        ret = _Lbm_SaveStatus(LBM_GET_LBPTR(i));
        if (ret != BL_ERR_OK)
        {
            break;
        }
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Clear the valid flag of a logical block.
 *
 *  \param[in]  id - the index of the logical block array.
 *
 *  \retval BL_ERR_OK - the valid flag is cleared.
 *  \retval BL_ERR_NOT_OK - the status is not cleared.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_Return_t Lbm_ClearStatus(bl_u16_t id)
{
    bl_Return_t ret = BL_ERR_NOT_OK;
    const bl_LogicalBlock_t *block;

    if (LBM_IS_VALID_ID(id))
    {
        block = LBM_GET_LBPTR(id);
        ret = Dm_IsValidDataId(block->validFlagId);
        if (ret != BL_ERR_OK)
        {
            ret = BL_ERR_OK;

            LBM_SET_STATUS(block,LBM_STATUS_NOT_CARE);
        }
        else
        {
            ret = Dm_ClearData(block->validFlagId);

            LBM_SET_STATUS(block,LBM_STATUS_INVALID);
        }
    }

    return ret;

}

/**************************************************************************//**
 *
 *  \details Get the status of a logical block.
 *
 *  \param[in]  id - the index of logical block array.
 *  \param[out] status - the buffer is used to keep the logical block status.
 *
 *  \return If the id is invalid returns BL_ERR_NOT_OK, otherwise returns
 *          BL_ERR_OK.
 *
 *  \retval BL_ERR_OK     - the status of a logical block is copied to status.
 *  \retval BL_ERR_NOT_OK - the id of a logical block is invalid.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_Return_t Lbm_GetStatus(bl_u16_t id,bl_u16_t *status)
{
    bl_Return_t ret = BL_ERR_NOT_OK;

    if (LBM_IS_VALID_ID(id))
    {
        if (status != BL_NULL_PTR)
        {
            *status = LBM_GET_LBSTATUS(id);
            ret = BL_ERR_OK;
        }
    }

    return ret;
}

#if (LBM_FUN_SAVE_FINGERPRINT == BL_FUN_ON)
/**************************************************************************//**
 *
 *  \details Save the fingerprint to RAM.
 *
 *  \param[in]  buffer - the pointer of the fingerprint.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
void Lbm_SaveFingerprint(const bl_Buffer_t *buffer)
{
    Bl_MemCpy(gs_LbmFingerprint,buffer,RTE_FINGERPRINT_SIZE);

    return ;
}
#endif

/**************************************************************************//**
 *
 *  \details update the status of all logical blocks.
 *
 *  \return none
 *
 *  \since V3.0.0
 *
 *****************************************************************************/
static void _Lbm_UpdateStatus(void)
{
    bl_u16_t i;

    BL_DEBUG_ASSERT_NO_RET(g_LogicalBlockList.number != 0);

    for (i = 0; LBM_IS_VALID_ID(i); i++)
    {
        _Lbm_ReadAndUpdateStatus(LBM_GET_LBPTR(i));
    }

    return ;
}

/**************************************************************************//**
 *
 *  \details read and update the status of a logical blocks.
 *
 *  \param[in] lb   - the pointer of a logical block information
 *.
 *  \return none
 *
 *  \note If the memory of the valid flag is not initialized, initialize it.
 *
 *  \since V3.0.0
 *
 *****************************************************************************/
static void _Lbm_ReadAndUpdateStatus(const bl_LogicalBlock_t *lb)
{
    bl_Return_t ret;
    bl_u16_t validFlagMemId;
    bl_u16_t status;

    BL_DEBUG_ASSERT_NO_RET(lb != BL_NULL_PTR);

    do
    {
        ret = Dm_IsValidDataId(lb->validFlagId);
        if (ret != BL_ERR_OK)
        {
            status = LBM_STATUS_NOT_CARE;
            break;
        }

        ret = Dm_IsDefaultData(lb->validFlagId);
        if (BL_ERR_OK == ret)
        {
            status = LBM_STATUS_VALID;
            break;
        }

        validFlagMemId = Dm_GetMemid(lb->validFlagId);
        ret = Mem_IsExternalDrv(validFlagMemId);
        if (BL_ERR_OK == ret)
        {
            BL_DEBUG_ASSERT_NO_RET(0);
            status = LBM_STATUS_INVALID;
            break;
        }
		/*
	else
	{
		status = LBM_STATUS_VALID;
            break;
	}*/

        ret = Mem_InitMemory(validFlagMemId);
        if (ret != BL_ERR_OK)
        {
            status = LBM_STATUS_INVALID;
            break;
        }

        ret = Dm_IsDefaultData(lb->validFlagId);
        if (BL_ERR_OK == ret)
        {
            status = LBM_STATUS_VALID;
        }
        else
        {
            status = LBM_STATUS_INVALID;
        }
    }while(0); /*lint !e717*/

    LBM_SET_STATUS(lb,status);

    return ;
}

/**************************************************************************//**
 *
 *  \details Find a logical block.
 *
 *  \param[in]  address - the general address of the logical block.
 *  \param[in]  size - the size of the logical block.
 *  \param[out] foundId - the found id.
 *
 *  \return If a logical block is found return BL_ERR_OK, otherwise returns
 *          BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - find a logical block successfully.
 *  \retval BL_ERR_NOT_OK  - find a logical block unsuccessfully.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
static bl_Return_t _Lbm_FindLogicalBlock(bl_Address_t address,
                                          bl_Size_t size,
                                          bl_u16_t *foundId)
{
    bl_Address_t limitAddr;
    bl_Return_t ret = BL_ERR_NOT_OK;
    bl_u16_t i;

    BL_DEBUG_ASSERT(foundId != BL_NULL_PTR);

    limitAddr = address + size;
    if (limitAddr >= address)
    {
        for (i = 0; LBM_IS_VALID_ID(i); i++)
        {
            ret = _Lbm_IsInLogicalBlock(LBM_GET_LBPTR(i),address,limitAddr);
            if (BL_ERR_OK == ret)
            {
                *foundId = i;
                break;
            }
        }
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Check a region whether is in the logical block. If this region is
 *           in the logical block, check it whether is in a segment list.
 *
 *  \param[in]  lb - the pointer of a logical block information.
 *  \param[in]  address - the start address of the region.
 *  \param[in]  limitAddr - the limit address of the region.
 *
 *  \return If the region is in the logical block returns BL_ERR_OK, otherwise
 *          returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the region is in the logical block.
 *  \retval BL_ERR_NOT_OK  - the region is not in the logical block.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
static bl_Return_t _Lbm_IsInLogicalBlock(const bl_LogicalBlock_t *lb,
                                          bl_Address_t address,
                                          bl_Address_t limitAddr)
{
    bl_Return_t ret = BL_ERR_NOT_OK;
    bl_Address_t lbLimitAddr;

    lbLimitAddr = lb->address + lb->size;

    if (LBM_IS_IN_REGION(address,limitAddr,lb->address,lbLimitAddr))
    {
        ret = BL_ERR_OK;

        if (lb->segments.number != 0)
        {
            ret = _Lbm_IsInSegmentList(&lb->segments,address,limitAddr);
        }
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Check a region whether is in a segment list.
 *
 *  \param[in]  segment - the pointer of a segment list.
 *  \param[in]  address - the start address of the region.
 *  \param[in]  limitAddr - the limit address of the region.
 *
 *  \return If the region is in the segment list returns BL_ERR_OK, otherwise
 *          returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the region is in the segment list.
 *  \retval BL_ERR_NOT_OK  - the region is not in the segment list.
 *
 *  \note If the segment number of the segment list is ZERO returns
 *        BL_ERR_NOT_OK.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
static bl_Return_t _Lbm_IsInSegmentList(const bl_SegmentList_t *segment,
                                         bl_Address_t address,
                                         bl_Address_t limitAddr)
{
    bl_Address_t segLimitAddr;
    const bl_Segment_t *seg;
    bl_u16_t segNum;
    bl_u16_t i;
    bl_Return_t ret = BL_ERR_NOT_OK;

    segNum = segment->number;
    seg = segment->segList;

    for (i = 0; i < segNum; i++)
    {
        segLimitAddr = seg[i].address + seg[i].size;
        if (LBM_IS_IN_REGION(address,limitAddr,seg[i].address,segLimitAddr))
        {
            ret = BL_ERR_OK;
            break;
        }
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Check the found id whether is updated.
 *
 *  \param[in]  curId - the current id in the download context.
 *  \param[in]  foundId - a valid id found by _Lbm_FindLogicalBlock().
 *
 *  \return If the found id is updatable return BL_ERR_OK, otherwise returns
 *          BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the found id is updatable.
 *  \retval BL_ERR_NOT_OK  - the found id is not updatable.
 *  \retval LBM_ERR_UPDATED_ID  - the current id and the found id are equal.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
static bl_Return_t _Lbm_IsUpdatable(bl_u16_t curId,bl_u16_t foundId)
{
    bl_Return_t ret = BL_ERR_OK;
    const bl_LogicalBlock_t *block;

    if (LBM_IS_VALID_ID(curId))
    {
        if (curId == foundId)
        {
            ret = LBM_ERR_UPDATED_ID;
        }
        else
        {
            block = LBM_GET_LBPTR(curId);
            if (LBM_IS_UPDATING_STATUS(block))
            {
                ret = BL_ERR_NOT_OK;
            }
        }
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Update the logical block id and the down segment index in the
 *           download context.
 *
 *  \param[in/out]  dct   - the pointer of the download context.
 *  \param[in]      newId - the new logical block id.
 *
 *  \return none
 *
 *  \note   This function directly modify the contents of the download context.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
static void _Lbm_UpdateBlockInfoInDct(bl_DownContext_t *dct,bl_u16_t newId)
{
    dct->lbId = newId;
    dct->segIndex = 0;

    return ;
}

/**************************************************************************//**
 *
 *  \details Update the logical block id and the down segment index in the
 *           download context.
 *
 *  \param[in]  dct - the pointer of the download context.
 *  \param[in]  buf - the pointer of the data.
 *
 *  \return If the pointers are not null and the logical block id in the
 *          download context is valid returns BL_ERR_OK, otherwise returns
 *          BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK     - the parameters are valid.
 *  \retval BL_ERR_NOT_OK - one of parameters is not valid.
 *
 *  \note   This function directly use the contents of the download context.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
static bl_Return_t _Lbm_IsValidParam(const bl_DownContext_t *dct,
                                        const bl_Buffer_t *buf)
{
    bl_Return_t ret = BL_ERR_NOT_OK;

    if ((dct != BL_NULL_PTR)
        && (buf != BL_NULL_PTR))
    {
        if (LBM_IS_VALID_ID(dct->lbId))
        {
            ret = BL_ERR_OK;
        }
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details write data to a logical block.
 *
 *  \param[in]  lb      - the pointer of the logical block information.
 *  \param[in]  address - the general address of the data.
 *  \param[in]  size    - the size of the data.
 *  \param[in]  buffer  - the contents of the data.
 *
 *  \return If the data are written successfully in the logical block returns
 *          BL_ERR_OK, otherwise returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the logical block is written successfully.
 *  \retval BL_ERR_NOT_OK - the logical block is written unsuccessfully.
 *
 *  \note this function do not change the status of the logical block.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
static bl_Return_t _Lbm_Write(const bl_LogicalBlock_t *lb,
                               bl_Address_t address,
                               bl_Size_t size,
                               const bl_Buffer_t *buffer)
{
    bl_Return_t ret;
    bl_Address_t localAddr;

    localAddr = LBM_MAKE_LOCAL_ADDR(lb,address);
    ret = Mem_Write(lb->memId,localAddr,size,buffer);

    return ret;
}

/**************************************************************************//**
 *
 *  \details try to clear the valid flag of the logical block.
 *
 *  \param[in]  lb  - the pointer of the logical block information.
 *
 *  \return If the valid flag is cleared returns BL_ERR_OK, otherwise returns
 *          BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the valid flag is cleared successfully.
 *  \retval BL_ERR_NOT_OK - the valid flag is cleared unsuccessfully.
 *
 *  \note This function is not modified the status of the logical block.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
/*
static bl_Return_t _Lbm_TryToClearValidFlag(const bl_LogicalBlock_t *lb)
{
    bl_Return_t ret = BL_ERR_OK;

    if (LBM_IS_VALID_STATUS(lb))
    {
        ret = Dm_ClearData(lb->validFlagId);
    }
    return ret;
}
*/
/**************************************************************************//**
 *
 *  \details erase a logical block.If this logical block contains multiple
 *           segments, each segment can be independently erased.
 *
 *
 *  \param[in]  lb  - the pointer of the logical block information.
 *
 *  \return If the logical block is erased successfully returns BL_ERR_OK,
 *          otherwise returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the logical block is erased successfully.
 *  \retval BL_ERR_NOT_OK - the logical block is erased unsuccessfully.
 *
 *  \note this function do not change the status of the logical block.
 *
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
static bl_Return_t _lbm_Erase(const bl_LogicalBlock_t *lb)
{
    bl_Return_t ret = BL_ERR_NOT_OK;
    bl_u16_t eraseCnt;
    bl_u16_t i;
    const bl_Segment_t *seg;
    bl_Segment_t segment;

    if (0 == lb->segments.number)
    {
        /*erase by the logical block address.*/
        eraseCnt = 1;
        seg = &segment;
        segment.address = lb->address;
        segment.size = lb->size;
    }
    else
    {
        /*erase by the segment address.*/
        eraseCnt = lb->segments.number;
        seg = lb->segments.segList;
    }

    for (i = 0; i < eraseCnt; i++)
    {
        ret = Mem_Erase(lb->memId,
                          LBM_MAKE_LOCAL_ADDR(lb,seg[i].address),
                          seg[i].size);
        if (ret != BL_ERR_OK)
        {
            ret = BL_ERR_NOT_OK;
            break;
        }
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Check the hash value of the downloaded logical block whether is
 *           valid.If the marco 'LBM_FUN_AUTO_CALCULATE_HASH' is enabled and
 *           the memory of the logical block is not readable, do not need to
 *           calculate the hash value again.
 *
 *  \param[in]  dct  - the pointer of the download context.
 *  \param[in]  size - the size of the hash value.
 *  \param[in]  buf  - the data of the hash value.
 *
 *  \return If the hash value is match returns BL_ERR_OK, otherwise returns
 *          BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the hash value is match.
 *  \retval BL_ERR_NOT_OK - the hash value is not match or calculation is
 *                          failed.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
static bl_Return_t _Lbm_IsValidHash(const bl_DownContext_t *dct,
                                     bl_Size_t size,
                                     const bl_Buffer_t *buf)
{
    bl_Return_t ret;
    
//#if (LBM_FUN_AUTO_CALCULATE_HASH == BL_FUN_ON)
//    const bl_LogicalBlock_t *block;
//#endif


//#if (LBM_FUN_AUTO_CALCULATE_HASH == BL_FUN_ON)
//    block = LBM_GET_LBPTR(dct->lbId);

//    ret = Mem_IsReadable(block->memId);
//    if (BL_ERR_NOT_OK == ret)
//    {
//        /*Do not need to calculate the hash value again.*/
//        ret = BL_ERR_OK;
//    }
//    else
//#endif
    {
        ret = _Lbm_CalculateHashByDct(dct);
    }

    if (BL_ERR_OK == ret)
    {
        ret = Secm_VerifyHash(size,buf);
    }
    
    return ret;
}

/**************************************************************************//**
 *
 *  \details Calculate the hash value of the download segments in same logical
 *           block.
 *
 *  \param[in]  dct  - the pointer of the download context.
 *
 *  \return If the hash value is calculated successfully returns BL_ERR_OK,
 *          otherwise returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the calculation is successful.
 *  \retval BL_ERR_NOT_OK - the calculation is failed.
 *
 *  \warning The size of each segment that is used to calculate the hash must
 *           be a multiple of BL_BYTE_WIDTH.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
static bl_Return_t _Lbm_CalculateHashByDct(const bl_DownContext_t *dct)
{
    bl_DownSegment_t *seg;
    const bl_LogicalBlock_t *block;
    bl_Size_t readSize;
    bl_Size_t calSize;
    bl_Address_t calAddr;
    bl_u16_t i;
    bl_u32_t timeout = 0;
    bl_Return_t ret = BL_ERR_NOT_OK;

    Secm_StartHash();
    seg = dct->segment.segList;
    block = LBM_GET_LBPTR(dct->lbId);

    for (i = 0; i < dct->segIndex; i++)
    {
#if (BL_BYTE_WIDTH != BL_BYTE_WIDTH_8)
        if ((seg[i].size & BL_BYTE_WIDTH) != 0)
        {
            /*the segment size must be a multiple of BL_BYTE_WIDTH.*/
            ret = BL_ERR_NOT_OK;
            break;
        }
#endif

        calAddr = seg[i].address;
        calSize = seg[i].size;
        readSize = (calSize % LBM_HASH_CALCULATION_BUFFER_SIZE);
        if (0UL == readSize)
        {
            readSize = LBM_HASH_CALCULATION_BUFFER_SIZE;
        }

        do
        {
            ret = Mem_Read(block->memId,LBM_MAKE_LOCAL_ADDR(block,calAddr),readSize,g_HashCalculation);
            if (ret != BL_ERR_OK)
            {
                ret = BL_ERR_NOT_OK;
                break;
            }

            ret = Secm_UpdateHash(readSize,g_HashCalculation);
            if (ret != BL_ERR_OK)
            {
                break;
            }

            calSize -= readSize;
            calAddr += readSize;
            readSize = LBM_HASH_CALCULATION_BUFFER_SIZE;

            g_RteInfo.wdgOps->Feed();

            timeout += LBM_HASH_CALCULATION_TIME;
            if (timeout >= LBM_HASH_CALCULATION_TIMEOUT)
            {
                timeout = 0UL;
                Rte_ReportEvent(RTE_EVENT_TYPE_MEMOPS_TIMEOUT);
            }
        }while(calSize > 0UL);

        if (ret != BL_ERR_OK)
        {
            break;
        }
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Initialize the memory.
 *
 *  \param[in]  lb  - the pointer of the logical block information.
 *
 *  \return If the memory is initialized successfully returns BL_ERR_OK,
 *          otherwise returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the memory is initialized successfully.
 *  \retval BL_ERR_NOT_OK - the memory is initialized successfully.
 *
 *  \see _Lbm_LookForMemId
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
static bl_Return_t _Lbm_InitMemory(const bl_LogicalBlock_t *lb)
{
    bl_Return_t ret;
    bl_u16_t memoryId;

    memoryId = _Lbm_LookForMemId(lb);

    ret = Mem_InitMemory(memoryId);

    return ret;
}

/**************************************************************************//**
 *
 *  \details Look for the memory id. Read the data in the logical block and
 *           make these data to the type of memory and the index of memory.
 *           call Mem_LookforMemId() to perform lookup action.
 *
 *  \param[in]  lb  - the pointer of the logical block information.
 *
 *  \return If the memory id is not found returns MEM_ERROR_MEMID, otherwise
 *          returns the found id.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
static bl_u16_t _Lbm_LookForMemId(const bl_LogicalBlock_t *lb)
{
    bl_Return_t ret;
    bl_u16_t type;
    bl_u16_t index;
    bl_u16_t tmpId = MEM_ERROR_MEMID;
    bl_Address_t addr;
    bl_Buffer_t tmpBuf[MEM_MEMORY_TYPE_SIZE + MEM_MEMORY_INDEX_SIZE];

    addr = LBM_MAKE_LOCAL_ADDR(lb,(lb->address + LBM_LOOKFOR_OFFSET));

    ret = Mem_Read(lb->memId,
                    addr,
                    (bl_Size_t)(MEM_MEMORY_TYPE_SIZE + MEM_MEMORY_INDEX_SIZE),
                    tmpBuf);
    if (BL_ERR_OK == ret)
    {
        type = BL_MAKE_LOCAL_U16(tmpBuf);
        index = BL_MAKE_LOCAL_U16(&tmpBuf[MEM_MEMORY_TYPE_SIZE]);

        (void)Mem_LookforMemId(type,index,&tmpId);
    }

    return tmpId;
}

/**************************************************************************//**
 *
 *  \details Save the status of the logical block to ROM and Update the logical
 *           block status.
 *
 *  \param[in]  block  - the pointer of a logical block.
 *
 *  \return If the status is saved successfully returns BL_ERR_OK, otherwise
 *          returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the status is saved successfully.
 *  \retval BL_ERR_NOT_OK - the status is saved unsuccessfully.
 *
 *  \warning If the status of the logical block is not LBM_STATUS_UPDATED, this
 *           function will return BL_ERR_OK.
 *  \warning If the validFlagId of the logical block is DM_ERROR_DATAID, this
 *           function will return BL_ERR_OK.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
static bl_Return_t _Lbm_SaveStatus(const bl_LogicalBlock_t *block)
{
    bl_Return_t ret = BL_ERR_OK;
    bl_Return_t isValidId;

    if (LBM_IS_UPDATED_STATUS(block))
    {
        isValidId = Dm_IsValidDataId(block->validFlagId);
        if (BL_ERR_OK == isValidId)
        {
            ret = Dm_WriteDefaultData(block->validFlagId);
            if (BL_ERR_OK == ret)
            {
                LBM_SET_STATUS(block,LBM_STATUS_VALID);
            }
            else
            {
                LBM_SET_STATUS(block,LBM_STATUS_INVALID);
            }
        }
        else
        {
            LBM_SET_STATUS(block,LBM_STATUS_NOT_CARE);
        }
    }

    return ret;
}

#if (LBM_FUN_SUCCESS_COUNTER == BL_FUN_ON)
/**************************************************************************//**
 *
 *  \details add the success count of the logical block.
 *
 *  \param[in]  lb  - the pointer of the logical block information.
 *
 *  \return If the count is added successfully returns BL_ERR_OK, otherwise
 *          returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the count is added.
 *  \retval BL_ERR_NOT_OK - the count is failed.
 *
 *  \since  V3.11.0
 *
 *****************************************************************************/
static bl_Return_t _Lbm_AddSuccessCnt(const bl_LogicalBlock_t *lb)
{
    bl_SuccessCounter_t count;
    bl_Return_t ret,ret2;
    bl_u16_t id = lb->succCntId;

    ret = Dm_IsValidDataId(id);
    if (BL_ERR_OK == ret)
    {
        ret = _Lbm_GetSuccessCount(id,&count);
        if (BL_ERR_OK == ret)
        {
            /*add the count*/
            if(count<255) /*For Geely, tha max value is 255,Modify by LT 20160623*/
            {
                count += 1;
            }
            
            ret = _Lbm_SaveSuccessCount(id,count);

            /*If the ECU is successfully reprogrammed, this counter is set to 00,Modify by LT 20160623*/
            ret2 = _Lbm_SaveAttemptCount(8,0);

            if((ret==BL_ERR_OK)&&(ret2==BL_ERR_OK))
            {
                ret = BL_ERR_OK;
            }
            else
            {
                ret = BL_ERR_NOT_OK;
            }

        }
    }
    else
    {
        ret = BL_ERR_OK; /*The succCntId is invalid.*/
        //break;
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details get the success count of the logical block.
 *
 *  \param[in]  did   - the index of the data manager module.
 *  \param[out] count - the buffer of the success count
 *
 *  \return If the count is gotten successfully returns BL_ERR_OK, otherwise
 *          returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the count is gotten.
 *  \retval BL_ERR_NOT_OK - the count is failed.
 *
 *  \since  V3.11.0
 *
 *****************************************************************************/
bl_Return_t _Lbm_GetSuccessCount(bl_u16_t did,
                                    bl_SuccessCounter_t *count)
{
    bl_Return_t ret;
    bl_Buffer_t buf[LBM_COUNTER_MAX_SIZE];

    ret = Dm_ReadData(did,sizeof(bl_SuccessCounter_t),buf);

    
    if (BL_ERR_OK == ret)
    {
#if (LBM_SUCCESS_COUNTER_SIZE == 4)
        *count = BL_MAKE_LOCAL_U32(buf);
#elif (LBM_SUCCESS_COUNTER_SIZE == 2)
        *count = BL_MAKE_LOCAL_U16(buf);
#else
#error "The size of the bl_attempt_t is error."
#endif
    }
    else
    {
        /*use the default value,modify by LT,20160623*/
        *count = 0;
    }

    //return ret;
    return BL_ERR_OK;
}

/**************************************************************************//**
 *
 *  \details save the success count of the logical block.
 *
 *  \param[in]  did   - the index of the data manager module.
 *  \param[out] count - the success count
 *
 *  \return If the count is saved successfully returns BL_ERR_OK, otherwise
 *          returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the count is saved.
 *  \retval BL_ERR_NOT_OK - the count is failed.
 *
 *  \since  V3.11.0
 *
 *****************************************************************************/
bl_Return_t _Lbm_SaveSuccessCount(bl_u16_t did,
                                    bl_SuccessCounter_t count)
{
    bl_Return_t ret;
    bl_Buffer_t buf[LBM_COUNTER_MAX_SIZE];

#if (LBM_SUCCESS_COUNTER_SIZE == 4)
    BL_LOCAL_U32_TO_BUF(buf,count);
#elif (LBM_SUCCESS_COUNTER_SIZE == 2)
    BL_LOCAL_U16_TO_BUF(buf,count);
#else
#error "The size of the bl_attempt_t is error."
#endif

    ret = Dm_WriteData(did,sizeof(bl_SuccessCounter_t),buf);

    return ;
}
#endif

#if (LBM_FUN_ATTEMPT_COUNTER == BL_FUN_ON)
/**************************************************************************//**
 *
 *  \details add the attempt count of the logical block.
 *
 *  \param[in]  lb  - the pointer of the logical block information.
 *
 *  \return If the count is added successfully returns BL_ERR_OK, otherwise
 *          returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the count is added.
 *  \retval BL_ERR_NOT_OK - the count is failed.
 *
 *  \since  V3.11.0
 *
 *****************************************************************************/
static bl_Return_t _Lbm_AddAttemptCnt(const bl_LogicalBlock_t *lb)
{
    bl_AttemptCounter_t count;
    bl_Return_t ret;
    bl_u16_t id = lb->attemptCntId;

    ret = Dm_IsValidDataId(id);
    if (BL_ERR_OK == ret)
    {
        ret = _Lbm_GetAttemptCount(id,&count);
        if (BL_ERR_OK == ret)
        {
            /*add the count*/
            if(count < 255)/*For Geely, tha max value is 255,Modify by LT 20160623*/
            {
                count += 1;
            }
            if ((lb->maxAttemptCnt != 0)
                && (count >= lb->maxAttemptCnt))
            {
                ret = BL_ERR_NOT_OK;
            }
            else
            {
                ret = _Lbm_SaveAttemptCount(id,count);
            }
        }
    }
    else
    {
        ret = BL_ERR_OK; /*The attemptCntId is invalid.*/
        //break;
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details get the attempt count of the logical block.
 *
 *  \param[in]  did   - the index of the data manager module.
 *  \param[out] count - the buffer of the attempt count
 *
 *  \return If the count is gotten successfully returns BL_ERR_OK, otherwise
 *          returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the count is gotten.
 *  \retval BL_ERR_NOT_OK - the count is failed.
 *
 *  \since  V3.11.0
 *
 *****************************************************************************/
bl_Return_t _Lbm_GetAttemptCount(bl_u16_t did,
                                    bl_AttemptCounter_t *count)
{
    bl_Return_t ret;
    bl_Buffer_t buf[LBM_COUNTER_MAX_SIZE];

    ret = Dm_ReadData(did,sizeof(bl_AttemptCounter_t),buf);
	
    if (BL_ERR_OK == ret)
    {
#if (LBM_SUCCESS_COUNTER_SIZE == 4)
        *count = BL_MAKE_LOCAL_U32(buf);
#elif (LBM_SUCCESS_COUNTER_SIZE == 2)
        *count = BL_MAKE_LOCAL_U16(buf);
#else
#error "The size of the bl_attempt_t is error."
#endif
    }
    else
    {
        /*use the default value,modify by LT,20160623*/
        *count = 0;
    }

    //return ret;
    return BL_ERR_OK;
}

/**************************************************************************//**
 *
 *  \details save the attempt count of the logical block.
 *
 *  \param[in]  did   - the index of the data manager module.
 *  \param[out] count - the attempt count
 *
 *  \return If the count is saved successfully returns BL_ERR_OK, otherwise
 *          returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the count is saved.
 *  \retval BL_ERR_NOT_OK - the count is failed.
 *
 *  \since  V3.11.0
 *
 *****************************************************************************/
bl_Return_t _Lbm_SaveAttemptCount(bl_u16_t did,
                                    bl_AttemptCounter_t count)
{
    bl_Return_t ret;
    bl_Buffer_t buf[LBM_COUNTER_MAX_SIZE];

#if (LBM_SUCCESS_COUNTER_SIZE == 4)
    BL_LOCAL_U32_TO_BUF(buf,count);
#elif (LBM_SUCCESS_COUNTER_SIZE == 2)
    BL_LOCAL_U16_TO_BUF(buf,count);
#else
#error "The size of the bl_attempt_t is error."
#endif

    ret = Dm_WriteData(did,sizeof(bl_AttemptCounter_t),buf);

    return ;
}
#endif

#if (LBM_FUN_SAVE_FINGERPRINT == BL_FUN_ON)
/**************************************************************************//**
 *
 *  \details Write the contents of the buffer to ROM.
 *
 *  \param[in]  block - the pointer of the logical block.
 *
 *  \retval BL_ERR_OK       - the fingerprint are written to the ROM.
 *  \retval BL_ERR_NOT_OK   - the fingerprint are NOT written to the ROM.
 *
 *  \note   If the fpId is BL_ERROR_ID_16BIT, this function will return
 *          BL_ERR_OK.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_Return_t _Lbm_SaveFingerprint(const bl_LogicalBlock_t *block)
{
    bl_Return_t ret = BL_ERR_NOT_OK;

    BL_DEBUG_ASSERT_PARAM(block != BL_NULL_PTR);

    ret = Dm_IsValidDataId(block->fpId);
    if (BL_ERR_OK == ret)
    {
        ret = Dm_WriteData(block->fpId,
                            RTE_FINGERPRINT_SIZE,
                            gs_LbmFingerprint);
    }
    else
    {
        ret = BL_ERR_OK;
    }

    return ret;
}
#endif


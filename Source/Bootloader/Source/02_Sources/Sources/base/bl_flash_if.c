/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of the flash_if manager module.
 *
 *  \file       bl_flash_if.c
 *  \ingroup    flash_if_manager_module
 *  \author     haiping.wang <haiping.wang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      02.00.00 | 19/08/2013 | haiping.wang     | N/A | Boot020001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
******************************************************************************/
#include "config.h"
#include "bl_common.h"
#include "bl_rte.h"
#include "bl_memory.h"
#include "bl_flash_if.h"
#include "bl_flash_if_cfg.h"
#include "bl_flash.h"
#include "bl_watchdog.h"

#include "GPIO_IF.H"
extern unsigned char BL_upgrade_type;
/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 306,506,602,781,1251,1257,1277,1532,2103,3112,3204,3227,3453 EOF*/
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
 * MISRA-C:2004 5.6(781):The identifier is used as a structure/union member.
 * The member of the structure is used through the structure object.
 *
 * 1251:Suffixed integer constant causes implicit conversion of other
 * (integral) operand.
 *
 * 1257:Suffixed integer constant implicitly converted to smaller integer type
 * on assignment.
 *
 * 1277:A "U" suffix has not been appended to a hex constant.
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
 * 3204:The variable is only set once and so it could be declared with the
 * 'const' qualifier.
 *
 * 3227:The parameter is never modified and so it could be declared with const.
 *
 * MISRA-C:2004 19.7(3453):A function could probably be used instead of this
 * function-like macro.
 *
 */

/*****************************************************************************
 *  Verify The Configurations of Function Macro
 *****************************************************************************/
#if (FLASHIF_NUMBER_OF_BLOCK == 0)
#error "The number of the flash IF block is error."
#endif
/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/
#define FLASHIF_DRIVER_MAGIC_ADDRESS        (FLASHIF_DRIVER_STARTADDRESS + 4)
#define FLASHIF_DRIVER_VERSION_ADDRESS      (FLASHIF_DRIVER_STARTADDRESS + 8)

/** \brief Set the status of flash IF context to NOINIT.*/
#define FLASHIF_STATUS_GOTO_NOINIT(ct)  ((ct)->status = FLASHIF_STATUS_NOINIT)
/** \brief Set the status of flash IF context to IDLE.*/
#define FLASHIF_STATUS_GOTO_IDLE(ct)    ((ct)->status = FLASHIF_STATUS_IDLE)
/** \brief Set the status of flash IF context to WRITING.*/
#define FLASHIF_STATUS_GOTO_WRITING(ct) ((ct)->status = FLASHIF_STATUS_WRITING)
/** \brief Set the status of flash IF context to ERASING.*/
#define FLASHIF_STATUS_GOTO_ERASING(ct) ((ct)->status = FLASHIF_STATUS_ERASING)

/** \brief Check whether the status of flash IF context is NOINIT.*/
#define FLASHIF_STATUS_IS_NOINIT(ct)    (FLASHIF_STATUS_NOINIT == (ct)->status)
/** \brief Check whether the status of flash IF context is IDLE.*/
#define FLASHIF_STATUS_IS_IDLE(ct)      (FLASHIF_STATUS_IDLE == (ct)->status)
/** \brief Check whether the status of flash IF context is WRITING.*/
#define FLASHIF_STATUS_IS_WRITING(ct)   (FLASHIF_STATUS_WRITING == \
                                            (ct)->status)
/** \brief Check whether the status of flash IF context is ERASING.*/
#define FLASHIF_STATUS_IS_ERASING(ct)   (FLASHIF_STATUS_ERASING == \
                                            (ct)->status)

/** \brief Check whether the id is a valid block list index of the flash IF.*/
#define FLASHIF_IS_VALID_BLOCK(id)      ((id) < FLASHIF_NUMBER_OF_BLOCK)

#define FLASHIF_INIT(pp)    FLASH_DRIVER_INIT(FLASHIF_DRIVER_STARTADDRESS,pp)
#define FLASHIF_DEINIT(pp)  FLASH_DRIVER_DEINIT(FLASHIF_DRIVER_STARTADDRESS,pp)
#define FLASHIF_WRITE(pp)   FLASH_DRIVER_WRITE(FLASHIF_DRIVER_STARTADDRESS,pp)
#define FLASHIF_ERASE(pp)   FLASH_DRIVER_ERASE(FLASHIF_DRIVER_STARTADDRESS,pp)
#define FLASHIF_READ(pp)    Flash_Read(pp)

/*****************************************************************************
 *  Internal Type Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/
/** \brief begin to operate the flash device.*/
static bl_Return_t _Flsif_OperateFlash(bl_FlashIfContext_t *fct);
/** \brief check whether the address and the size is valid.*/
static bl_Return_t _Flsif_CheckParam(bl_FlashIfContext_t *fct,
                                        bl_Address_t address,
                                        bl_Size_t size);
/** \brief Write a page to flash device.*/
static bl_Return_t _Flsif_WritePage(const bl_FlashIfBlockInfo_t *block,
                                        bl_Address_t address,
                                        bl_Size_t size,
                                        bl_Buffer_t *buffer);
/** \brief Erase a sector in the flash device.*/
static bl_Return_t _Flsif_EraseSector(const bl_FlashIfBlockInfo_t *block,
                                            bl_Address_t address,
                                            bl_Size_t size,
                                            bl_Buffer_t *buffer);
#if (FLASHIF_FUN_ERASE_BY_BLOCKID == BL_FUN_ON)
/** \brief Get the eraseable block id.*/
static bl_u16_t _Flsif_GetPhyBlockId(const bl_FlashIfBlockInfo_t *block,
                                        bl_Address_t address);
#endif
 extern void FlashWriteTimeout(void);


/*****************************************************************************
 * Internal Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/
/**************************************************************************//**
 *
 *  \details initialize the flash IF module. This interface will be check the
 *           magic value and the version between the flash if module and the
 *           flash driver head. If the magic or the version is not same, the
 *           initialization interface of the flash driver is not called.
 *
 *  \return If this module is initialized successfully returns BL_ERR_OK,
 *          otherwise returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK     - initialize successfully.
 *  \retval BL_ERR_NOT_OK - initialize unsuccessfully.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
bl_Return_t Flsif_Init(void)
{
    bl_Return_t ret = BL_ERR_NOT_OK;
    bl_FlashDrvParam_t param;
    bl_u32_t checkValue;

	__DI();
    checkValue = BL_MAKE_LOCAL_U32(FLASHIF_DRIVER_MAGIC_ADDRESS);
    if (FLASHIF_DRIVER_MAGIC_VALUE == checkValue)
    {
        checkValue = BL_MAKE_LOCAL_U32(FLASHIF_DRIVER_VERSION_ADDRESS);
        if (FLASHIF_DRIVER_VERSION_VALUE == checkValue)
        {
            FLASHIF_INIT(&param);
            ret = param.errCode;
        }
    }
	__EI();

    return ret;
}

/**************************************************************************//**
 *
 *  \details deinitialize the flash IF module.
 *
 *  \return If this module is deinitialized successfully returns BL_ERR_OK,
 *          otherwise returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK     - deinitialize successfully.
 *  \retval BL_ERR_NOT_OK - deinitialize unsuccessfully.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
bl_Return_t Flsif_DeInit(void)
{
    bl_FlashDrvParam_t param;

    FLASHIF_DEINIT(&param);

    return param.errCode;
}

/**************************************************************************//**
 *
 *  \details Read the data from the flash device by the flash driver.
 *
 *  \param[in]  address - the memory address of the data to be read from.
 *  \param[in]  size    - the size of the data to be read.
 *  \param[out] buffer  - the saving address pointer of the data to be read.
 *
 *  \return If the data is read successfully returns BL_ERR_OK,
 *          otherwise returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK     - read data successfully.
 *  \retval BL_ERR_NOT_OK - read data unsuccessfully.
 *
 *  \note   if the FLASHIF_FUN_SPECIAL_READ is ON, the flash driver supply the
 *          special read interface.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
bl_Return_t Flsif_Read(bl_Address_t address,
                       bl_Size_t size,
                       bl_Buffer_t *buffer)
{
    bl_Return_t ret = BL_ERR_NOT_OK;
    bl_Address_t phyAddr;
#if (FLASHIF_FUN_SPECIAL_READ == BL_FUN_ON)
    bl_FlashDrvParam_t param;
#endif

    /* 1- get physical addr */
#if (FLASHIF_FUN_CONVERT_ADDRESS == BL_FUN_ON)
    FLASHIF_CONVERTADDRESS(address, &phyAddr);
#else
    phyAddr = address;
#endif

#if (FLASHIF_FUN_SPECIAL_READ == BL_FUN_ON)
    param.address = phyAddr;
    param.size = size;
    param.buffer = buffer;
    param.FeedDog = g_RteInfo.wdgOps->Feed;

    FLASHIF_READ(&param);
    if (BL_ERR_OK == param.errCode)
    {
        ret = BL_ERR_OK;
    }
#else
    Bl_MemCpy(buffer, (const bl_Buffer_t *)phyAddr, size);
    ret = BL_ERR_OK;
#endif

    return ret;
}

/**************************************************************************//**
 *
 *  \details Begin to write the flash device.
 *
 *  \param[in] address  - the memory address of the data to be written in.
 *  \param[in] size     - the size of the data to be written.
 *  \param[in] buffer   - the pointer of the data to be written.
 *
 *  \return If the data are written successfully returns BL_ERR_OK, otherwise
 *          returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK     - the writing operation is done successfully.
 *  \retval BL_ERR_NOT_OK - the writing operation is done unsuccessfully.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
bl_Return_t Flsif_Write(bl_Address_t address,
                            bl_Size_t size,
                            const bl_Buffer_t *buffer)
{
    bl_Return_t ret;
    bl_Size_t doneSize;
    bl_FlashIfContext_t fct;

    ret = _Flsif_CheckParam(&fct, address, size);
    if (BL_ERR_OK == ret)
    {
        fct.Operate = &_Flsif_WritePage; /*lint !e605*//*PRQA S 563*/
        fct.timeout = 0UL;
        fct.opsTime = FLASHIF_PAGE_WRITETIME;
        fct.size = size;
        doneSize = 0;
#if (FLASHIF_NUMBER_OF_BLOCK > 1)
        do
        {
#endif
            fct.block = &g_FlashIfBlockList[fct.startId];
            fct.opsSize = fct.block->pageSize;
            fct.buffer = (bl_Buffer_t *)&buffer[doneSize];/*PRQA S 311*/

            ret = _Flsif_OperateFlash(&fct);
#if (FLASHIF_NUMBER_OF_BLOCK > 1)
            doneSize += fct.doneSize;
        }while ((fct.size > 0UL) && (BL_ERR_OK == ret));
#endif
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Begin to erase the flash device.
 *
 *  \param[in] address  - the memory address will be erased.
 *  \param[in] size     - the size will be erased.
 *
 *  \return If the memory is erased successfully returns BL_ERR_OK, otherwise
 *          returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK     - the erasing operation is done successfully.
 *  \retval BL_ERR_NOT_OK - the erasing operation is done unsuccessfully.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
bl_Return_t Flsif_Erase(bl_Address_t address, bl_Size_t size)
{
    bl_Return_t ret;
    bl_FlashIfContext_t fct;
    ret = _Flsif_CheckParam(&fct, address, size);
    if (BL_ERR_OK == ret)
    {
        fct.Operate = &_Flsif_EraseSector; /*lint !e605*//*PRQA S 563*/
        fct.timeout = 0UL;
        fct.opsTime = FLASHIF_SECTOR_ERASETIME;
        fct.size = size;
        fct.buffer = BL_NULL_PTR;
#if (FLASHIF_NUMBER_OF_BLOCK > 1)
        do
        {
#endif
            fct.block = &g_FlashIfBlockList[fct.startId];
            fct.opsSize = fct.block->sectorSize;
            ret = _Flsif_OperateFlash(&fct);
#if (FLASHIF_NUMBER_OF_BLOCK > 1)
        }while ((fct.size > 0UL) && (BL_ERR_OK == ret));
#endif
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Begin to operate the flash device.
 *
 *  \param[in/out] fct - the context pointer of flash IF.
 *
 *  \return If the memory operation is successful returns BL_ERR_OK, otherwise
 *          returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK     - the operation is done successfully.
 *  \retval BL_ERR_NOT_OK - the operation is done unsuccessfully.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
static bl_Return_t _Flsif_OperateFlash(bl_FlashIfContext_t *fct)
{
    bl_Return_t ret = BL_ERR_OK;
    bl_Size_t doneSize;
    bl_Size_t count;
    bl_Address_t address;
    bl_Buffer_t *buffer;
    bl_Size_t opsSize = fct->opsSize;

    /*Calculate the total size of this operation.*/
    if (fct->startId == fct->endId)
    {
        doneSize = fct->size;
    }
    else
    {
        doneSize = (fct->block->address + fct->block->totalSize)
                        - fct->address;
    }

    address = fct->address;
    buffer = fct->buffer;

    /*Operate a page or a sector in a time.*/
    count = doneSize / opsSize;
    while (count > 0UL)
    {
        ret = fct->Operate(fct->block, address, opsSize, buffer);
        if (BL_ERR_OK == ret)
        {
            address += opsSize;
            buffer = &buffer[opsSize];
            count -= 1UL;	

            fct->timeout += fct->opsTime;
            if (fct->timeout > FLASHIF_ACCESS_TIMELIMITE)
            {
                fct->timeout = 0UL;
				if(BL_upgrade_type == UPGRADE_BY_CAN)
				{
                	Rte_ReportEvent(RTE_EVENT_TYPE_MEMOPS_TIMEOUT);
				}
				else if(BL_upgrade_type == UPGRADE_BY_SPI)
				{
					FlashWriteTimeout();
				}
            }
        }
        else
        {
            break;
        }
    }

    if ((BL_ERR_OK == ret) && ((doneSize % opsSize) != 0UL))
    {
        ret = fct->Operate(fct->block,address,(doneSize % opsSize),buffer);
    }

    if (BL_ERR_OK == ret)
    {
        /*If the operation is successful, update the informations in the fct.*/
        fct->doneSize = doneSize;
        fct->size -= doneSize;
        if ((fct->startId + 1) < FLASHIF_NUMBER_OF_BLOCK)
        {
            fct->startId += 1;
            fct->address = g_FlashIfBlockList[fct->startId].address;
        }
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Check whether the address and size are valid.
 *
 *  \param[in/out] fct  - the context pointer of flash IF.
 *  \param[in] address  - the memory address will be operated.
 *  \param[in] size     - the size will be operated.
 *
 *  \return If the informations are valid returns BL_ERR_OK, otherwise
 *          returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK     - the informations are valid..
 *  \retval BL_ERR_NOT_OK - the informations are invalid.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
static bl_Return_t _Flsif_CheckParam(bl_FlashIfContext_t *fct,
                                        bl_Address_t address,
                                        bl_Size_t size)
{
    bl_Return_t ret = BL_ERR_NOT_OK;
    bl_u16_t  i = 0;
    const bl_FlashIfBlockInfo_t *blockList;
    bl_Address_t phyAddr;
    bl_Size_t offset;
    bl_u16_t startId = BL_ERROR_ID_16BIT;

#if (FLASHIF_FUN_CONVERT_ADDRESS == BL_FUN_ON)
    FLASHIF_CONVERTADDRESS(address, &phyAddr);
#else
    phyAddr = address;
#endif

#if (FLASHIF_NUMBER_OF_BLOCK > 1)
    do
    {
#endif
        blockList = &g_FlashIfBlockList[i];

        /*find the first block.*/
        if ((BL_ERROR_ID_16BIT == startId)
            && (phyAddr >= blockList->address)
            && (phyAddr < (blockList->address + blockList->totalSize)))
        {
            startId = i;
            offset = phyAddr - blockList->address;
            size += offset;
        }

        /*If the first block is found, find end block.*/
        if (startId != BL_ERROR_ID_16BIT)
        {
            if (size > blockList->totalSize)
            {
                size -= blockList->totalSize;
            }
            else
            {
                fct->startId = startId;
                fct->endId = i;
                fct->address = phyAddr;
                ret = BL_ERR_OK;
#if (FLASHIF_NUMBER_OF_BLOCK > 1)
                break;
#endif
            }
        }
#if (FLASHIF_NUMBER_OF_BLOCK > 1)
        i += 1;
    }while(i < FLASHIF_NUMBER_OF_BLOCK);
#endif

    return ret;
}

/**************************************************************************//**
 *
 *  \details write one page data to the flash device.
 *
 *  \param[in] block    - the pointer of the flash block.
 *  \param[in] address  - the address of data.
 *  \param[in] size     - the size of data.
 *  \param[in] buffer   - the contents of the data will be written to flash.
 *
 *  \retval BL_ERR_OK       - the page is written successfully.
 *  \retval BL_ERR_NOT_OK   - the page is written unsuccessfully.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
static bl_Return_t _Flsif_WritePage(const bl_FlashIfBlockInfo_t *block,
                                        bl_Address_t address,
                                        bl_Size_t size,
                                        bl_Buffer_t *buffer)
{
    bl_Return_t ret = BL_ERR_NOT_OK;
    bl_FlashDrvParam_t param;

    (void)block;

    param.address = address;
    param.size = size;
    param.buffer = buffer;
    param.FeedDog = g_RteInfo.wdgOps->Feed;
	__DI();
    FLASHIF_WRITE(&param);
	__EI();
    if(BL_ERR_OK == param.errCode)
    {
        ret = BL_ERR_OK;
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Erase one sector of the flash device.
 *
 *  \param[in] block    - the pointer of the flash block.
 *  \param[in] address  - the address of the flash block.
 *  \param[in] size     - the size of the flash will be erased.
 *  \param[in] buffer   - useless parameter
 *
 *  \retval BL_ERR_OK       - the sector of the flash is erased successfully.
 *  \retval BL_ERR_NOT_OK   - the sector of the flash is erased unsuccessfully.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
static bl_Return_t _Flsif_EraseSector(const bl_FlashIfBlockInfo_t *block,
                                            bl_Address_t address,
                                            bl_Size_t size,
                                            bl_Buffer_t *buffer)/*PRQA S 3673*/
{
    bl_Return_t ret = BL_ERR_NOT_OK;
    bl_FlashDrvParam_t param;

    param.address = address;
    param.size = size;
    param.buffer = BL_NULL_PTR;
#if (FLASHIF_FUN_ERASE_BY_BLOCKID == BL_FUN_ON)
    param.phyBlockId = _Flsif_GetPhyBlockId(block,address);
#else
    (void)block;
#endif
    (void)buffer;

    param.FeedDog = g_RteInfo.wdgOps->Feed;
	__DI();
    FLASHIF_ERASE(&param);
	__EI();
    if(BL_ERR_OK == param.errCode)
    {
        ret = BL_ERR_OK;
    }

    return ret;
}

#if (FLASHIF_FUN_ERASE_BY_BLOCKID == BL_FUN_ON)
/**************************************************************************//**
 *
 *  \details Check wether the physical address of data is in a valid block and
 *           the size of data is a valid range in the block list.
 *
 *  \pre    the address in the current block.
 *
 *  \param[in] block    - the pointer of the current block that is erasing.
 *  \param[in] address  - the address in the current block.
 *
 *  \return the physical eraseable block id.
 *
 *  \since V5.1.0
 *
 *****************************************************************************/
static bl_u16_t _Flsif_GetPhyBlockId(const bl_FlashIfBlockInfo_t *block,
                                        bl_Address_t address)
{
    bl_u16_t offset;

    offset = (bl_u16_t)(address / block->sectorSize);

    return offset + block->phyBlockId;
}
#endif

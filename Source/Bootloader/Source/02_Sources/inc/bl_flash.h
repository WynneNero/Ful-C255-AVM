/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the header file of the flash module.
 *
 *  \file       bl_flash.h
 *  \ingroup    driver_module
 *  \author     lele.liu <lele.liu@hirain.com>
 *
 *  \version    1.0.0
 *  \date       11/08/2015
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | -------------
 *      01.00.00 | 11/08/2015 | lele.liu         | N/A | BootDrv010001
 *
 *****************************************************************************/
#ifndef _BL_FLASH_H_
#define _BL_FLASH_H_
#include "bl_typedefs.h"
#include "bl_flash_if.h"

/*********************************************************************************************************************/
/* Macro define                                                                                                           */
/*********************************************************************************************************************/


#define DFLS_BASE_ADDRESS   0xC3F8C000
#define CFLS_BASE_ADDRESS   0xC3F88000

#if(FLS_PLATFORM >= FLS_512K)  
#define CFLS_SECTOR0    1
#define CFLS_SECTOR1    2
#define CFLS_SECTOR2    4
#define CFLS_SECTOR3    8
#define CFLS_SECTOR4    0x10
#define CFLS_SECTOR5    0x20
#define CFLS_SECTOR6    0x00010000
#define CFLS_SECTOR7    0x00020000
#endif

#if(FLS_PLATFORM >= FLS_768K) 
#define CFLS_SECTOR8    0x80000001
#define CFLS_SECTOR9    0x80000002
#endif

#if(FLS_PLATFORM >= FLS_1M)
#define CFLS_SECTOR10    0x80000004
#define CFLS_SECTOR11    0x80000008
#endif

#if(FLS_PLATFORM >= FLS_1_5M)
#define CFLS_SECTOR12    0x80000010
#define CFLS_SECTOR13    0x80000020
#define CFLS_SECTOR14    0x80000040
#define CFLS_SECTOR15    0x80000080
#endif

/*********************************************************************************************************************/
/* ErrorCode Defines                                                                                                 */
/*********************************************************************************************************************/
/* standard error codes */
#define kFlashOk               0x00 /* called function succeeded */
/* controller specific error codes user define */
#define kFlashFailed           0x01 /* called function failed */


/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
#define FLASH_DRIVER_VERSION_TYPE       (0x8001u)
#define FLASH_DRIVER_VERSION_INDEX      (0x0000u)
#define FLASH_DRIVER_VERSION_MAGIC      (0x58455031UL)
#define FLASH_DRIVER_VERSION_VERSION    (0x00010300UL)

#define FLASH_START_ADRESS              (0x700000UL)
#define FLASH_END_ADRESS                (0x7FFFFFUL)
#define FLASH_ERASE_SIZE                (0x400u)
#define FLASH_ERASE_VALUE               (0xFFu)
#define FLASH_PHRASE_SIZE               (0x08u)
#define FLASH_PHRASE_SIZE_HALF          (0x04u)
#define FLASH_RESET_TIME_CNT            (0)
#define FLASH_OVER_TIME_CNT             (0x10000u)

#define FLASH_DRIVER_INIT_OFFSET        (0x0Cu)
#define FLASH_DRIVER_DEINIT_OFFSET      (0x10u)
#define FLASH_DRIVER_ERASE_OFFSET       (0x14u)
#define FLASH_DRIVER_WRITE_OFFSET       (0x18u)

#define FLASH_DRIVER_INIT(sa, pp)       (*(bl_FlashDrvFun_t*)((sa)\
                                            + FLASH_DRIVER_INIT_OFFSET))(pp)
#define FLASH_DRIVER_DEINIT(sa, pp)     (*(bl_FlashDrvFun_t*)((sa)\
                                            + FLASH_DRIVER_DEINIT_OFFSET))(pp)
#define FLASH_DRIVER_ERASE(sa, pp)      (*(bl_FlashDrvFun_t*)((sa)\
                                            + FLASH_DRIVER_ERASE_OFFSET))(pp)
#define FLASH_DRIVER_WRITE(sa, pp)      (*(bl_FlashDrvFun_t*)((sa)\
                                            + FLASH_DRIVER_WRITE_OFFSET))(pp)

/*****************************************************************************
 * Type Declarations
 *****************************************************************************/

extern const bl_FlashDrvHeader_t g_FlashHeader;


/*****************************************************************************
 * External Function Prototype Declarations
 *****************************************************************************/

extern void Flash_Init(bl_FlashDrvParam_t *par);
extern void Flash_Deinit(bl_FlashDrvParam_t *par);
extern void Flash_Write(bl_FlashDrvParam_t *par);
extern void Flash_Erase(bl_FlashDrvParam_t *par);


extern void Flash_Read(bl_FlashDrvParam_t *par);
#endif













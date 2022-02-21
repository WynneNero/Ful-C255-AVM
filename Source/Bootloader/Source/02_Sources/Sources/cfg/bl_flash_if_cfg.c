/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a source file to configurate the flash_if manager
 *              module.
 *
 *  \file       bl_flash_if_cfg.c
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
#include "bl_flash_if_cfg.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 1531,3211 EOF*/
/*
 * 1531:The object is referenced in only one translation unit.
 * g_BootingCheckerList is a configurations.
 *
 * 3211:The global identifier is defined but not used.
 * The g_BootingCheckerList is used in the bl_booting.c file.
 *
 */

/*****************************************************************************
 *  Verify The Configurations of Function Macro
 *****************************************************************************/

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
/** \brief config the physical flash block.*/
const bl_FlashIfBlockInfo_t g_FlashIfBlockList[FLASHIF_NUMBER_OF_BLOCK] =
{
    {
        FLASHIF_BLOCK0_STARTADDRESS,
        FLASHIF_BLOCK0_TOTAL_SIZE,
        FLASHIF_BLOCK0_SECTOR_SIZE,
        FLASHIF_BLOCK0_PAGE_SIZE,
    },
    {
        FLASHIF_BLOCK1_STARTADDRESS,
        FLASHIF_BLOCK1_TOTAL_SIZE,
        FLASHIF_BLOCK1_SECTOR_SIZE,
        FLASHIF_BLOCK1_PAGE_SIZE,
    },
};

/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/


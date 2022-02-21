/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a source file to configurate the memory manager module.
 *
 *  \file       bl_memory_cfg.c
 *  \ingroup    memory_manager_module
 *  \author     hewei.zhang    <hewei.zhang@hirain.com>
 *              mingqing.tang  <mingqing.tang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      01.00.00 | 17/03/2010 | hewei.zhang      | N/A | Boot010001
 *      01.01.00 | 20/04/2010 | hewei.zhang      | N/A | Boot010002
 *      01.04.00 | 26/06/2010 | hewei.zhang      | N/A | Boot010005
 *      02.00.00 | 21/02/2011 | mingqing.tang    | N/A | Boot020001
 *      02.02.00 | 15/03/2011 | mingqing.tang    | N/A | Boot020003
 *      02.07.00 | 14/06/2011 | mingqing.tang    | N/A | Boot020008
 *      03.00.00 | 12/09/2011 | mingqing.tang    | N/A | Boot030001
 *      03.03.00 | 17/10/2011 | mingqing.tang    | N/A | Boot030004
 *      03.04.00 | 24/10/2011 | mingqing.tang    | N/A | Boot030005
 *      03.18.00 | 29/05/2012 | mingqing.tang    | N/A | Boot030019
 *      05.00.00 | 19/06/2013 | mingqing.tang    | N/A | Boot050001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#include "bl_rte.h"
#include "bl_memory_cfg.h"
#include "bl_flash_if.h"
#include "bl_ram.h"
#include "FLS_Drv.h"
/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 1257,1531,3211 EOF*/
/*
 * 1257:Suffixed integer constant implicitly converted to smaller integer type
 * on assignment.
 *
 * 1531:The object is referenced in only one translation unit.
 * g_BootingCheckerList is a configurations.
 *
 * 3211:The global identifier is defined but not used.
 * The g_BootingCheckerList is used in the bl_booting.c file.
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
/**************************************************************************//**
 *  \details The memory operations list.
 *****************************************************************************/
static const bl_MemoryOperations_t gs_MemoryOps[MEM_NUMBER_OF_OPSLIST] =
{
    {
        MEM_MEMORY_0_OPS_INIT,MEM_MEMORY_0_OPS_DEINIT,MEM_MEMORY_0_OPS_WRITE,
        MEM_MEMORY_0_OPS_READ,MEM_MEMORY_0_OPS_ERASE
    },
    {
        MEM_MEMORY_1_OPS_INIT,MEM_MEMORY_1_OPS_DEINIT,MEM_MEMORY_1_OPS_WRITE,
        MEM_MEMORY_1_OPS_READ,MEM_MEMORY_1_OPS_ERASE
    },
    {
        MEM_MEMORY_2_OPS_INIT,MEM_MEMORY_2_OPS_DEINIT,MEM_MEMORY_2_OPS_WRITE,
        MEM_MEMORY_2_OPS_READ,MEM_MEMORY_2_OPS_ERASE
    },
};

/**************************************************************************//**
 *  \details The memory informations.
 *****************************************************************************/
static const bl_MemoryInfo_t gs_MemoryInfo[MEM_NUMBER_OF_MEMORY] =
{
    {
        MEM_MEMORY_0_TYPE,MEM_MEMORY_0_INDEX,MEM_MEMORY_0_BASE_ADDRESS,
        MEM_MEMORY_0_SIZE,MEM_MEMORY_0_OPS
    },
    {
        MEM_MEMORY_1_TYPE,MEM_MEMORY_1_INDEX,MEM_MEMORY_1_BASE_ADDRESS,
        MEM_MEMORY_1_SIZE,MEM_MEMORY_1_OPS
    },
    {
        MEM_MEMORY_2_TYPE,MEM_MEMORY_2_INDEX,MEM_MEMORY_2_BASE_ADDRESS,
        MEM_MEMORY_2_SIZE,MEM_MEMORY_2_OPS
    },
};

/**************************************************************************//**
 *  \details The memory informations list.
 *
 *  \warning Do not change the name of this variable.
 *****************************************************************************/
const bl_MemoryInfoList_t g_MemoryInfoList =
{
    MEM_NUMBER_OF_MEMORY,gs_MemoryInfo
};

/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/


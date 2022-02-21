/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a head file to configurate the date of the memory
 *              manager module.
 *
 *  \file       bl_memory_cfg.h
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
 *      03.00.00 | 12/09/2011 | mingqing.tang    | N/A | Boot030001
 *      03.18.00 | 29/05/2012 | mingqing.tang    | N/A | Boot030019
 *      05.00.00 | 19/06/2013 | mingqing.tang    | N/A | Boot050001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#ifndef _BL_MEMORY_CFG_H_
#define _BL_MEMORY_CFG_H_
#include "bl_memory.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 3205,3210,3447,3448 EOF*/
/*
 * 3205:The identifier is not used and could be removed.
 * The bl_Adapter_t is used by the specifically adapter such as UDS platform in
 * the bl_adpt_uds_platform.c
 *
 * 3210:The global identifier is declared but is not used.
 * The functions are used in the bl_security_cfg.c file.
 *
 * MISRA-C:2004 8.8(3447):The identifier has external linkage but this
 * declaration is not in a header file.
 * The function Declarations are in the header file.
 *
 * MISRA-C:2004 5.3(3448):Declaration of typedef is not in a header file.
 * The bl_SecurityDelay_t is declared in the header file.
 *
 */

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
/*the memory configurations*/
#define MEM_NUMBER_OF_MEMORY        (3)
#define MEM_NUMBER_OF_OPSLIST       (3)

#define MEM_MEMORY_0_TYPE           MEM_MEMORY_TYPE_RAM
#define MEM_MEMORY_0_INDEX          (0)
#define MEM_MEMORY_0_BASE_ADDRESS   (0xFEDFC000UL)

#define MEM_MEMORY_0_SIZE           (0x00002A00UL)
#define MEM_MEMORY_0_OPS            (&gs_MemoryOps[0])
#define MEM_MEMORY_0_OPS_INIT       BL_NULL_PTR
#define MEM_MEMORY_0_OPS_DEINIT     BL_NULL_PTR
#define MEM_MEMORY_0_OPS_WRITE      (&Ram_Write)
#define MEM_MEMORY_0_OPS_READ       (&Ram_Read)
#define MEM_MEMORY_0_OPS_ERASE      BL_NULL_PTR

#define MEM_MEMORY_1_TYPE           (MEM_MEMORY_TYPE_EXTERNAL_DRV \
                                     | MEM_MEMORY_TYPE_FLASH)
#define MEM_MEMORY_1_INDEX          (0)
#define MEM_MEMORY_1_BASE_ADDRESS   (0x00000000UL)
#define MEM_MEMORY_1_SIZE           (0x00060000UL)			
#define MEM_MEMORY_1_OPS            (&gs_MemoryOps[1])
#define MEM_MEMORY_1_OPS_INIT       (&Flsif_Init)
#define MEM_MEMORY_1_OPS_DEINIT     (&Flsif_DeInit)
#define MEM_MEMORY_1_OPS_WRITE      (&Flsif_Write)
#define MEM_MEMORY_1_OPS_READ       (&Flsif_Read)
#define MEM_MEMORY_1_OPS_ERASE      (&Flsif_Erase)

#define MEM_MEMORY_2_TYPE          MEM_MEMORY_TYPE_EEPROM
#define MEM_MEMORY_2_INDEX          (0)
#define MEM_MEMORY_2_BASE_ADDRESS   (0xFF200000UL)		// data flash
#define MEM_MEMORY_2_SIZE           (0x00008000UL)
#define MEM_MEMORY_2_OPS            (&gs_MemoryOps[2])
#define MEM_MEMORY_2_OPS_INIT       (&FLS_vDrvInit)
#define MEM_MEMORY_2_OPS_DEINIT     (&FLS_vDrvExit)
#define MEM_MEMORY_2_OPS_WRITE      (&FLS_u8WriteDataWait)
#define MEM_MEMORY_2_OPS_READ       (&FLS_u8ReadDataWait)
#define MEM_MEMORY_2_OPS_ERASE      BL_NULL_PTR
/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/

/*****************************************************************************
 *  Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/
/** \brief The memory informations list.*/
extern const bl_MemoryInfoList_t g_MemoryInfoList;

/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/

#endif


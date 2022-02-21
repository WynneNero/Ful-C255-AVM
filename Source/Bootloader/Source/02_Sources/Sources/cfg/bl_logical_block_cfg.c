/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a source file to configurate the logical block manager
 *              module.
 *
 *  \file       bl_logical_block_cfg.c
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
 *      03.11.00 | 15/02/2012 | mingqing.tang    | N/A | Boot030012
 *      04.00.00 | 15/07/2012 | mingqing.tang    | N/A | Boot040001
 *      04.01.00 | 15/07/2012 | mingqing.tang    | N/A | Boot040002
 *      04.03.00 | 15/07/2012 | mingqing.tang    | N/A | Boot040004
 *      04.21.00 | 15/07/2012 | mingqing.tang    | N/A | Boot040022
 *      04.30.00 | 10/04/2013 | mingqing.tang    | N/A | Boot040031
 *      05.00.00 | 19/06/2013 | mingqing.tang    | N/A | Boot030001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#include "bl_data.h"
#include "bl_logical_block_cfg.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 1257,1531,1533,3211,3406 EOF*/
/*
 * 1257:Suffixed integer constant implicitly converted to smaller integer type
 * on assignment.
 *
 * 1531:The object is referenced in only one translation unit.
 * g_LogicalBlockList is a configurations.
 *
 * 1533:The object is referenced in only one translation unit.
 *
 * 3211:The global identifier is defined but not used.
 * The g_BootingCheckerList is used in the bl_booting.c file.
 *
 * MISRA-C:2004 8.5(3406):Object with external linkage has been defined in a
 * header file.
 * The g_HashCalculation is not defined in a header file.
 *
 */

/*****************************************************************************
 *  Verify The Configurations of Function Macro
 *****************************************************************************/
#if (((LBM_HASH_CALCULATION_BUFFER_SIZE)\
        & (LBM_HASH_CALCULATION_BUFFER_SIZE - 1UL)) != 0UL)
#error "the size of the buffer used to calculate the hash value is invalid."
#endif
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
/**************************************************************************//**
 *  \details A list of status of the logical block.
 *****************************************************************************/
static bl_u16_t gs_LogicalBlockStatus[LBM_NUMBER_OF_LOGICAL_BLOCK];

/**************************************************************************//**
 *  \details A array of the segment informations.
 *****************************************************************************/
 
/**************************************************************************//**
 *  \details A array of the logical block informations.
 *****************************************************************************/
static const bl_LogicalBlock_t gs_LogicalBlock[LBM_NUMBER_OF_LOGICAL_BLOCK] =
{
    /*logical block 0*/
    {
        LBM_LB0_TYPE,LBM_LB0_INDEX,LBM_LB0_STATUS_PTR,LBM_LB0_MEMID,
        LBM_LB0_GETID_MASK,LBM_LB0_WRITE_MASK,LBM_LB0_ERASE_MASK,
        LBM_LB0_VERIFY_MASK,LBM_LB0_ADDRESS,LBM_LB0_SIZE,LBM_LB0_OFFSET_MASK,
        LBM_LB0_VALID_FLAG_ID,LBM_LB0_FILE_HEADER_ID,LBM_LB0_FINGERPRINT_ID,
        LBM_LB0_SUCCESS_COUNT_ID,LBM_LB0_ATTEMPT_COUNT_ID,
        LBM_LB0_MAX_ATTEMPT_COUNT,
        {
            LBM_LB0_SEG_NUMBER,LBM_LB0_SEG_PTR
        },
    },
    /*logical block 1*/
    {
        LBM_LB1_TYPE,LBM_LB1_INDEX,LBM_LB1_STATUS_PTR,LBM_LB1_MEMID,
        LBM_LB1_GETID_MASK,LBM_LB1_WRITE_MASK,
        LBM_LB1_ERASE_MASK,LBM_LB1_VERIFY_MASK,LBM_LB1_ADDRESS,
        LBM_LB1_SIZE,LBM_LB1_OFFSET_MASK,LBM_LB1_VALID_FLAG_ID,
        LBM_LB1_FILE_HEADER_ID,LBM_LB1_FINGERPRINT_ID,LBM_LB1_SUCCESS_COUNT_ID,
        LBM_LB1_ATTEMPT_COUNT_ID,LBM_LB1_MAX_ATTEMPT_COUNT,
        {
            LBM_LB1_SEG_NUMBER,LBM_LB1_SEG_PTR
        },
    },
};

/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/
/**************************************************************************//**
 *  \details A list of logical blocks is managed by the logical block module.
 *****************************************************************************/
const bl_LogicalBlockList_t g_LogicalBlockList =
{
    BL_STATUS_INITED,
    LBM_NUMBER_OF_LOGICAL_BLOCK,
    LBM_NUMBER_OF_APPLICATION,
    LBM_NUMBER_OF_CALDATA,
    LBM_NUMBER_OF_DRIVER,
    LBM_NUMBER_OF_VIRTUAL,
    gs_LogicalBlock,
};

/**************************************************************************//**
 *  \details the buffer is used to calculate the hash value.
 *****************************************************************************/
bl_Buffer_t g_HashCalculation[LBM_HASH_CALCULATION_BUFFER_SIZE];

/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/


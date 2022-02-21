/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a head file to configurate the date of the logical
 *              block manager module.
 *
 *  \file       bl_logical_block_cfg.h
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
#ifndef _BL_LOGICAL_BLOCK_CFG_H_
#define _BL_LOGICAL_BLOCK_CFG_H_
#include "bl_logical_block.h"

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
#define LBM_LOOKFOR_OFFSET                  (0UL)
/**
 *  the size of a buffer is used to calculate the hash value.
 *
 *  \warning The size must be the n-th power of 2.
 */
#define LBM_HASH_CALCULATION_BUFFER_SIZE    (512UL)
#define LBM_HASH_CALCULATION_TIME           (2UL)
#define LBM_HASH_CALCULATION_TIMEOUT        (3000UL) /*ms*/

#define LBM_NUMBER_OF_LOGICAL_BLOCK         (2u)
#define LBM_NUMBER_OF_APPLICATION           (1u)
#define LBM_NUMBER_OF_CALDATA               (0u)
#define LBM_NUMBER_OF_DRIVER                (1u)
#define LBM_NUMBER_OF_VIRTUAL               (0u)

#define LBM_LB0_TYPE                LBM_TYPE_APPLICATION
#define LBM_LB0_INDEX               (0u)
#define LBM_LB0_STATUS_PTR          (&gs_LogicalBlockStatus[0])
#define LBM_LB0_MEMID               (1u)
#define LBM_LB0_GETID_MASK          (0x00000000UL)
#define LBM_LB0_WRITE_MASK          RTE_SYSFLAG_ERASE_BLOCK
#define LBM_LB0_ERASE_MASK          (0x00000000UL)
#define LBM_LB0_VERIFY_MASK         (0x00000000UL)
#define LBM_LB0_ADDRESS         	(0x00018000UL)
#define LBM_LB0_SIZE                (0x00048000UL)		
#define LBM_LB0_OFFSET_MASK         (0x00FFFFFFUL)
#define LBM_LB0_VALID_FLAG_ID       (0x02u)
#define LBM_LB0_FILE_HEADER_ID      DM_ERROR_DATAID
#define LBM_LB0_FINGERPRINT_ID      DM_ERROR_DATAID
#define LBM_LB0_SUCCESS_COUNT_ID  	DM_ERROR_DATAID//  7u
#define LBM_LB0_ATTEMPT_COUNT_ID    DM_ERROR_DATAID//   8u
#define LBM_LB0_MAX_ATTEMPT_COUNT   DM_ERROR_DATAID
#define LBM_LB0_SEG_NUMBER          (0)
#define LBM_LB0_SEG_PTR             BL_NULL_PTR

#define LBM_LB1_TYPE                LBM_TYPE_DRIVER
#define LBM_LB1_INDEX               (0)
#define LBM_LB1_STATUS_PTR          (&gs_LogicalBlockStatus[1])
#define LBM_LB1_MEMID               (0)
#define LBM_LB1_GETID_MASK          (0x00000000UL)
#define LBM_LB1_WRITE_MASK          (0x00000000UL)
#define LBM_LB1_ERASE_MASK          (0x00000000UL)
#define LBM_LB1_VERIFY_MASK         (0x00000000UL)
#define LBM_LB1_ADDRESS             (0xFEDFC000UL)
#define LBM_LB1_SIZE                (0x00002A00UL)//(0x00002A00UL)/*0x00002900UL, modify this for test,160515*/
#define LBM_LB1_OFFSET_MASK         (0xFFFFFFFFUL)
#define LBM_LB1_VALID_FLAG_ID       DM_ERROR_DATAID
#define LBM_LB1_FILE_HEADER_ID      DM_ERROR_DATAID
#define LBM_LB1_FINGERPRINT_ID      DM_ERROR_DATAID
#define LBM_LB1_SUCCESS_COUNT_ID    DM_ERROR_DATAID
#define LBM_LB1_ATTEMPT_COUNT_ID    DM_ERROR_DATAID
#define LBM_LB1_MAX_ATTEMPT_COUNT   DM_ERROR_DATAID
#define LBM_LB1_SEG_NUMBER          (0)
#define LBM_LB1_SEG_PTR             BL_NULL_PTR

/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/

/*****************************************************************************
 *  Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/
/**************************************************************************//**
 *  \brief A list of logical blocks.
 *****************************************************************************/
extern const bl_LogicalBlockList_t g_LogicalBlockList;

/**************************************************************************//**
 *  \brief the buffer is used to calculate the hash.
 *****************************************************************************/
extern bl_Buffer_t g_HashCalculation[LBM_HASH_CALCULATION_BUFFER_SIZE];
/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/

#endif


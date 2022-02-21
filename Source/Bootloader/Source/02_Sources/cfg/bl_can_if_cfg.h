/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a head file to configurate the can_if module.
 *
 *  \file       bl_can_if_cfg.h
 *  \ingroup    flash_if_manager_module
 *  \author     haiping.wang <haiping.wang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      02.00.00 | 20/08/2013 | haiping.wang     | N/A | Boot020001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
******************************************************************************/
#ifndef _BL_CAN_IF_CFG_H_
#define _BL_CAN_IF_CFG_H_
#include "bl_can_if.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 3210,3447 EOF*/
/*
 * 3210:The global identifier is declared but is not used.
 * The functions are used in the bl_security_cfg.c file.
 *
 * MISRA-C:2004 8.8(3447):The identifier has external linkage but this
 * declaration is not in a header file.
 * The function Declarations are in the header file.
 *
 */

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
/* define number of transmit and receive pdu*/
#define CANIFRX_TOTAL_NUM                          (2)
#define CANIFTX_TOTAL_NUM                          (1)

/* define the handle of can channel*/
#define HANDLE_CAN0_RX0                            (0)
#define HANDLE_CAN1_RX0                            (1)
#define HANDLE_CAN0_TX0                            (0)
#define HANDLE_CAN0_TX1                            (3)
#define HANDLE_CAN0_TX2                            (4)
#define HANDLE_CAN1_TX0                            (5)
#define HANDLE_CAN1_TX1                            (6)

/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/
extern const bl_CanIfRxList_t g_CanIfRxPduCfg;
extern const bl_CanIfTxList_t g_CanIfTxPduCfg;
/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/

#endif


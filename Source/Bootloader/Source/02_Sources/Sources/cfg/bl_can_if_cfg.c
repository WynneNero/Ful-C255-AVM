/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a source file to configurate the can_if module.
 *
 *  \file       bl_can_if_lcfg.c
 *  \ingroup    can_if_module
 *  \author     haiping.wang <haiping.wang@hirain.com>
 *
 *  \version    5.2.1
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      02.00.00 | 20/08/2013 | haiping.wang     | N/A | Boot020001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *      05.02.01 | 21/08/2014 | mingqing.tang    | N/A | BootSpec050002
 *
******************************************************************************/
#include "bl_can_tp.h"
#include "bl_can_if_cfg.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 1531,3120,3211 EOF*/
/*
 * 1531:The object is referenced in only one translation unit.
 * g_CanIfRxPduCfg and g_CanIfTxPduCfg are configurations.
 *
 * 3120:Hard-coded magic integer constant.
 * This is a only configuration.
 *
 * 3211:The global identifier is defined but not used.
 * The g_CanIfRxPduCfg and g_CanIfTxPduCfg are used in the bl_can_if.c file.
 *
 */


/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
/* define status of pdu*/
#define CANIF_RECEIVE                              (0)
#define CANIF_TRANSMITE                            (1)

/* define types of pdu*/
#define CANIF_STANDARD                             (0)
#define CANIF_EXTERNED                             (1)

#define CANIF_NUMBER_OF_PDU         (CANIFRX_TOTAL_NUM + CANIFTX_TOTAL_NUM)
/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/
#if (CANIF_FUN_DYNAMIC_CANID == BL_FUN_ON)
static bl_CanIfPduCfg_t gs_CanIfPduCfg[CANIF_NUMBER_OF_PDU] =
{
    {
        CANIF_RECEIVE, CANIF_STANDARD, HANDLE_CAN0_RX0, CANIF_PHY_RX_CANID
    },
    {
        CANIF_RECEIVE, CANIF_STANDARD, HANDLE_CAN0_RX0, CANIF_FUN_RX_CANID
    },
    {
        CANIF_TRANSMITE, CANIF_STANDARD, HANDLE_CAN0_TX0,CANIF_PHY_TX_CANID
    },
};
#else
static const bl_CanIfPduCfg_t gs_CanIfPduCfg[CANIF_NUMBER_OF_PDU] =
{
    {
        CANIF_RECEIVE, CANIF_STANDARD, HANDLE_CAN0_RX0, CANIF_PHY_RX_CANID
    },
    {
        CANIF_RECEIVE, CANIF_STANDARD, HANDLE_CAN0_RX0, CANIF_FUN_RX_CANID
    },
    {
        CANIF_TRANSMITE, CANIF_STANDARD, HANDLE_CAN0_TX0,CANIF_PHY_TX_CANID
    },
};
#endif

const bl_CanIfRxList_t g_CanIfRxPduCfg =
{
    CANIFRX_TOTAL_NUM,&gs_CanIfPduCfg[0],&Cantp_RxIndication,
};

const bl_CanIfTxList_t g_CanIfTxPduCfg =
{
    CANIFTX_TOTAL_NUM,&gs_CanIfPduCfg[2],&Cantp_TxConfirmation,
};


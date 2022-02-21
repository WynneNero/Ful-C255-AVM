/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the head file to configurate the adapter module.
 *
 *  \file       bl_adapter_cfg.h
 *  \ingroup    communication_adapter_module
 *  \author     heli.zhang <heli.zhang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      03.00.00 | 12/09/2011 | mingqing.tang    | N/A | Boot030001
 *      03.02.00 | 27/09/2011 | mingqing.tang    | N/A | Boot030003
 *      03.03.00 | 29/09/2011 | mingqing.tang    | N/A | Boot030004
 *      03.05.00 | 12/10/2011 | mingqing.tang    | N/A | Boot030006
 *      04.00.00 | 10/07/2012 | mingqing.tang    | N/A | Boot040001
 *      04.02.00 | 15/07/2012 | mingqing.tang    | N/A | Boot040003
 *      04.04.00 | 18/07/2012 | mingqing.tang    | N/A | Boot040005
 *      04.06.00 | 31/07/2012 | mingqing.tang    | N/A | Boot040007
 *      04.10.00 | 07/08/2012 | mingqing.tang    | N/A | Boot040011
 *      04.11.00 | 15/08/2012 | mingqing.tang    | N/A | Boot040012
 *      05.00.00 | 19/06/2013 | heli.zhang       | N/A | Boot050001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#ifndef _BL_ADAPTER_CFG_H_
#define _BL_ADAPTER_CFG_H_
#include "bl_adapter.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 3210,3447 EOF*/
/*
 * 3210:The global identifier is declared but is not used.
 * The g_SecurityDelayInfo is used in the bl_adapter.c file.
 *
 * MISRA-C:2004 8.8(3447):The identifier has external linkage but this
 * declaration is not in a header file.
 * The g_SecurityDelayInfo Declarations are in the header file.
 *
 *
 */

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
/** \brief The delay time when the bootloader is startup.*/
#define ADPT_SECURITY_DELAY_TIME                        (60000) /*ms*/
/** \brief The attempt count when the bootloader is startup.*/
#define ADPT_SECURITY_ATTEMPT_COUNT                     (3)
/** \brief The position of the delay flag*/
#define ADPT_SECURITY_DELAY_FLAG_ID                    14
/** \brief The position of the failed count flag.*/
#define ADPT_SECURITY_FAILED_COUNT_ID                   BL_ERROR_ID_16BIT

/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/

/*****************************************************************************
 *  Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/
/** \brief The delay info of security access. */
extern const bl_SecurityDelay_t g_SecurityDelayInfo;

#endif


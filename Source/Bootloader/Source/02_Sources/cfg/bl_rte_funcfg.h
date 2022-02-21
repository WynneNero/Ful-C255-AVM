/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a functional head file of the runtime environment
 *              module.
 *
 *  \file       bl_rte_funcfg.h
 *  \ingroup    rte_module
 *  \author     mingqing.tang <mingqing.tang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      01.00.00 | 17/03/2010 | hewei.zhang      | N/A | Boot010001
 *      01.01.00 | 20/04/2010 | hewei.zhang      | N/A | Boot010002
 *      01.03.00 | 28/05/2010 | hewei.zhang      | N/A | Boot010004
 *      01.04.00 | 26/06/2010 | hewei.zhang      | N/A | Boot010005
 *      01.08.00 | 24/08/2010 | hewei.zhang      | N/A | Boot010009
 *      01.11.00 | 07/12/2010 | hewei.zhang      | N/A | Boot010012
 *      02.00.00 | 21/02/2011 | mingqing.tang    | N/A | Boot020001
 *      02.02.00 | 15/03/2011 | mingqing.tang    | N/A | Boot020003
 *      02.07.00 | 14/06/2011 | mingqing.tang    | N/A | Boot020008
 *      03.00.00 | 12/09/2011 | mingqing.tang    | N/A | Boot030001
 *      03.03.00 | 17/10/2011 | mingqing.tang    | N/A | Boot030004
 *      03.04.00 | 24/10/2011 | mingqing.tang    | N/A | Boot030005
 *      03.10.00 | 03/01/2012 | mingqing.tang    | N/A | Boot030011
 *      03.12.00 | 18/01/2012 | mingqing.tang    | N/A | Boot030013
 *      03.18.00 | 29/05/2012 | mingqing.tang    | N/A | Boot030019
 *      05.00.00 | 19/06/2013 | mingqing.tang    | N/A | Boot050001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#ifndef _BL_RTE_FUNCFG_H_
#define _BL_RTE_FUNCFG_H_

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
/** \brief */
#define RTE_SYSTEM_SECURITY_CLASS   BL_SECURITY_CLASS_DDD
/** \brief */
#define RTE_FUN_STAY_IN_BOOT        BL_FUN_ON
/** \brief */
#define RTE_FUN_STAY_IN_BOOT_RESET  BL_FUN_ON
/** \brief */
#define RTE_FUN_WATCHDOG            BL_FUN_ON
/** \brief */
#define RTE_FUN_COPY_WDG_TO_RAM     BL_FUN_OFF
/** \brief */
#define RTE_FUN_PRE_INIT_WDG        BL_FUN_OFF
/** \brief */
#define RTE_FUN_GATEWAY             BL_FUN_OFF
/** \brief */
#define RTE_FUN_GATEWAY_CONVERSION  BL_FUN_OFF
/** \brief */
#define RTE_FUN_SYSTEM_SLEEP                    BL_FUN_OFF
/** \brief */
#define RTE_FUN_ADDITIONAL_SLEEP_CONDITION      BL_FUN_OFF
/** \brief */
#define RTE_FUN_FILE_HEADER_PROCESS             BL_FUN_OFF
/** \brief */
#define RTE_FUN_INTEGRALITY_VALUE_IN_HEADER     BL_FUN_OFF
/** \brief */
#define RTE_FUN_COMPATIBILITY_VALUE_IN_HEADER   BL_FUN_OFF
/** \brief */
#define RTE_FUN_FINGERPRINT                     BL_FUN_ON

/** \brief */
#define RTE_SYSTEM_VERSION                  (0x00050100UL)
/** \brief */
#define RTE_SYSTEM_SCHEDULE_PERIOD          (1)
/** \brief */
#define RTE_ECUPARTNUMBER_SIZE              (15UL)

#define RTE_WATCHDOG_FEED_INTERFACE_ADDR    (0x3DF0U)
#define RTE_WATCHDOG_FEED_INTERFACE_SIZE    (8U)

/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/

/*****************************************************************************
 *  Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/

/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/

#endif


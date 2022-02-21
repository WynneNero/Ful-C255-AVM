/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the configuration source file of the runtime
 *              environment module.
 *
 *  \file       bl_rte_cfg.c
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
#include "bl_rte.h"
#include "bl_rte_cfg.h"
#include "bl_app.h"
#include "bl_booting.h"
#include "bl_watchdog.h"
#include "bl_system.h"
#include "bl_timer.h"
#include "bl_can_if.h"
#include "bl_process_driver.h"
#include "bl_adpt_uds_platform.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 305,1257,1531,1533,3211,3406 EOF*/
/*
 * MISRA-C:2004 11.3(305):Cast a pointer to an integral type.
 * The feed interface of the watchdog module must be run in the RAM.
 *
 * 1257:Suffixed integer constant implicitly converted to smaller integer type
 * on assignment.
 *
 * 1531:The object is referenced in only one translation unit.
 * g_SecurityDelayInfo is a configurations.
 *
 * 1533:The object is only referenced by one function.
 * The objects are a configurations.
 *
 * 3211:The global identifier is defined but not used.
 * The identifier are used in the bl_rte.c file.
 *
 * MISRA-C:2004 8.5(3406):Object with external linkage has been defined in a
 * header file.
 * The g_DownSegment is not defined in a header file.
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
static const bl_ResetProcess_t
                    gs_ResetProcess[RTE_NUMBER_OF_BOOTING_PROCESSOR] =
{
    {
        BOOTING_FLAG_REPROGRAM_VALID,RTE_REPROGRAM_PROCESS
    },
    {
        BOOTING_FLAG_SYSTEM_RESET,RTE_RESET_PROCESS
    },
#if (RTE_FUN_STAY_IN_BOOT == BL_FUN_ON)
    {
        BOOTING_FLAG_APPLICATION_VALID,RTE_STAYINBOOT_PROCESS
    },
#endif
};

static const bl_WatchdogOps_t gs_WatchdogOps =
{
    RTE_WATCHDOG_OPS_INIT,
#if ((RTE_FUN_WATCHDOG == BL_FUN_ON) && (RTE_FUN_COPY_WDG_TO_RAM == BL_FUN_ON))
    (bl_FeedWgdCallback_t)RTE_WATCHDOG_FEED_INTERFACE_ADDR,
#else
    RTE_WATCHDOG_OPS_FEED,
#endif
    RTE_WATCHDOG_OPS_RESET,
    RTE_WATCHDOG_OPS_DEINIT
};

#if (RTE_FUN_SYSTEM_SLEEP == BL_FUN_ON)
static const bl_SystemSleepOps_t gs_SystemSleepOps =
{
    RTE_SYSTEM_OPS_ISSLEEP,
    RTE_SYSTEM_OPS_SLEEPCALLBACK,
    RTE_SYSTEM_OPS_SYSTEMSLEEP,
    RTE_SYSTEM_OPS_WAKEUPCALLBACK
};
#endif

static const bl_TimerOps_t gs_TimerOps =
{
    RTE_TIMER_OPS_INIT,
    RTE_TIMER_OPS_DEINIT,
    RTE_TIMER_OPS_TIMEOUT
};

static const bl_ComIfOps_t gs_ComIfOps =
{
    RTE_COMIF_OPS_INIT,
    RTE_COMIF_OPS_DEINIT,
    RTE_COMIF_OPS_READ,
    RTE_COMIF_OPS_WRITE,
    RTE_COMIF_OPS_ISSUCCWRITE
};


/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/
bl_DownSegment_t g_DownSegment[RTE_NUMBER_OF_DOWN_SEGMENT];

const bl_ResetProcessList_t g_ResetProcessList =
{
    RTE_NUMBER_OF_BOOTING_PROCESSOR,
    gs_ResetProcess
};

#if (RTE_FUN_STAY_IN_BOOT == BL_FUN_ON)
const bl_Buffer_t g_StayInBootValue[RTE_STAY_IN_BOOT_MSG_SIZE] =
{
    RTE_STAY_IN_BOOT_VALUE
};
#endif

const bl_EventCallback_t g_EventProcessList[RTE_NUMBER_OF_EVENT] =
{
    &Rte_ResetTimer,
    &Proc_Timeout,
    RTE_WATCHDOG_OPS_RESET,
    &Proc_Sleep,
};

const bl_RteInfo_t g_RteInfo =
{
    RTE_SYSTEM_VERSION,
    &gs_WatchdogOps,
#if (RTE_FUN_SYSTEM_SLEEP == BL_FUN_ON)
    &gs_SystemSleepOps,
#else
    BL_NULL_PTR, /*RTE_FUN_SYSTEM_SLEEP is OFF*/
#endif
    &gs_TimerOps,
    &gs_ComIfOps,
    RTE_WATCHDOG_OPS_RESET
};
/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/


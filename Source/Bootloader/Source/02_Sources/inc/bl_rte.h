/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a head file of the runtime environment module.
 *
 *  \file       bl_rte.h
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
#ifndef _BL_RTE_H_
#define _BL_RTE_H_
#include "bl_typedefs.h"
#include "bl_rte_funcfg.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 783,3205,3210,3447,3448,3453 EOF*/
/*
 * 783:A subsequent declaration of the identifier means that it is being used
 * both as a structure/union member and also as a label, ordinary identifier.
 * The member of the structure is used through the structure object.
 *
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
 * MISRA-C:2004 19.7(3453):A function could probably be used instead of this
 * function-like macro.
 * These macros have no side-effect.
 *
 */

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
/** */
#define RTE_NUMBER_OF_DOWN_STATUS       (4)
/** */
#define RTE_DOWN_STATUS_SYS_MASK        (0x000000FFUL)
#define RTE_DOWN_STATUS_USER_MASK       (0x3FFFFFFFUL)
#define RTE_DOWN_STATUS_INDEX_MASK      (0xC0000000UL)
#define RTE_SYSFLAG_SECURITY_ACCESS     (0x00000001UL)
#define RTE_SYSFLAG_CHECK_SIGNATURE     (0x00000002UL)
#define RTE_SYSFLAG_ERASE_BLOCK         (0x00000004UL)
#define RTE_SYSFLAG_WRITE_DATA          (0x00000008UL)
#define RTE_SYSFLAG_WRITE_FINGPRINT     (0x00000010UL)
#define RTE_SYSFLAG_WRITE_OTHER         (0x00000020UL)
#define RTE_USER_FLAG_GROUP_1           (0x40000000UL)
#define RTE_USER_FLAG_GROUP_2           (0x80000000UL)
#define RTE_USER_FLAG_GROUP_3           (0xC0000000UL)

#define RTE_NUMBER_OF_EVENT             (4)
/** \brief */
#define RTE_EVENT_TYPE_RECV_REQUEST     (0x0000u)
#define RTE_EVENT_TYPE_MEMOPS_TIMEOUT   (0x0001u)
#define RTE_EVENT_TYPE_S3TIME_TIMEOUT   (0x0002u)
#define RTE_EVENT_TYPE_SYSTEM_SLEEP     (0x0003u)

#define RTE_GET_DOWNSTATUS_ID(mask)     ((bl_u16_t)((((bl_u32_t)(mask)) >> 30)\
                                                & 0xFFu))

#define RTE_GET_DOWNSTATUS_VALUE(mask)  ((((bl_u32_t)(mask))\
                                                & RTE_DOWN_STATUS_USER_MASK))

/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/

typedef struct _tag_DownSegment bl_DownSegment_t;

typedef struct _tag_DownSegmentList bl_DownSegList_t;

typedef struct _tag_DownContext bl_DownContext_t;

typedef struct _tag_ResetProcess bl_ResetProcess_t;

typedef struct _tag_ResetProcessList bl_ResetProcessList_t;

typedef struct _tag_WatchdogOps bl_WatchdogOps_t;

typedef struct _tag_SystemSleepOps bl_SystemSleepOps_t;

typedef struct _tag_TimerOps bl_TimerOps_t;

typedef struct _tag_ComIfData bl_ComIfData_t;

typedef struct _tag_ComIfOps bl_ComIfOps_t;

typedef struct _tag_RteInfo bl_RteInfo_t;

typedef void (*bl_PeriodicCallback_t)(void);

typedef void (*bl_EventCallback_t)(void);

typedef void (*bl_FeedWgdCallback_t)(void);
/*****************************************************************************
 *  Structure Definitions
 *****************************************************************************/
struct _tag_DownSegment
{
    bl_Address_t address;   /**< the address of a download segment.*/
    bl_Size_t size;         /**< the size of a download segment.*/
};

struct _tag_DownSegmentList
{
    bl_u16_t number;        /**< the max number of the download segment.*/
    struct _tag_DownSegment *segList; /**< the download segment list.*/
};

struct _tag_DownContext
{
    bl_u16_t lbId;          /**< the id of logical block is downloaded.*/
    bl_u16_t segIndex;      /**< the index of usable segment.*/
    bl_DownStatus_t status[RTE_NUMBER_OF_DOWN_STATUS]; /**< system status.*/
    struct _tag_DownSegmentList segment; /**< list is recorded by bootloader.*/
};

struct _tag_ResetProcess
{
    bl_BootingFlag_t flag;      /**< the reason of the system reset.*/
    void (*Process)(void);      /**< the callback used to process action.*/
};

struct _tag_ResetProcessList
{
    bl_u16_t number;    /**< the max number of process callback.*/
    const struct _tag_ResetProcess *resetList;  /**< the process list.*/
};

struct _tag_WatchdogOps
{
    void (*Init)(void);
    void (*Feed)(void);
    void (*FastReset)(void);
    void (*Deinit)(void);
};

struct _tag_SystemSleepOps
{
    bl_Return_t (*IsSleep)(void);
    void (*SleepCallback)(void);
    void (*SystemSleep)(void);
    void (*WakeupCallback)(void);
};

struct _tag_TimerOps
{
    void (*Init)(void);
    void (*Deinit)(void);
    bl_Return_t (*IsTimeout)(void);
};

struct _tag_ComIfData
{
    bl_ComIfHandle_t retHandle;
    bl_BufferSize_t retSize;
    bl_BufferSize_t bufSize;
    bl_Buffer_t *buffer;
};

struct _tag_ComIfOps
{
    bl_Return_t (*Init)(void);
    void (*Deinit)(void);
    bl_Return_t (*Read)(struct _tag_ComIfData *data);
    bl_Return_t (*Write)(bl_ComIfHandle_t handle,
                            bl_BufferSize_t size,
                            const bl_Buffer_t *buffer);
    bl_Return_t (*IsWritten)(bl_ComIfHandle_t handle);
};

struct _tag_RteInfo
{
    bl_u32_t version;
    const struct _tag_WatchdogOps *wdgOps;
    const struct _tag_SystemSleepOps *sleepOps;
    const struct _tag_TimerOps *timerOps;
    const struct _tag_ComIfOps *comOps;
    void (*SystemReset)(void);
};


/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/
extern bl_DownContext_t g_DownContext;

extern const bl_RteInfo_t g_RteInfo;

/** \brief tx handle.*/
extern bl_ComIfHandle_t g_TxHandle;
/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/
/** \brief This function is used to pre-initialize the rte module.*/
extern void Rte_PreInit(void);
/** \brief This function is used to initialize the rte module.*/
extern bl_Return_t Rte_PostInit(void);
/** \brief This function is used to de-initialize the rte module.*/
extern void Rte_GotoApplication(void);
/** \brief This function is used to execute additional function.*/
extern void Rte_ProcessReset(bl_BootingFlag_t flag);
/** \brief This function is used to periodically execute the callback.*/
extern void Rte_PeriodicSchedule(bl_PeriodicCallback_t callback);
/** \brief Notice rte module that the event of interest has occurred.*/
extern void Rte_ReportEvent(bl_u16_t type);
/** \brief Reset the count of the sleep timer and SIB reset timer.*/
extern void Rte_ResetTimer(void);
/** \brief Save the address and size information to the DownContext.*/
extern bl_Return_t Rte_SaveAddressInfo(bl_DownContext_t *dct,
                                        bl_Address_t address,
                                        bl_Size_t size);
/** \brief Clear the address and size information in the DownContext.*/
extern void Rte_ClearAddressInfo(bl_DownContext_t *dct);
/** \brief Get the status of download process.*/
extern bl_DownStatus_t Rte_GetDownStatus(const bl_DownContext_t *dct,
                                            bl_u16_t gId);
/** \brief Set the status of download process.*/
extern void Rte_SetDownStatus(bl_DownContext_t *dct, bl_DownStatus_t mask);
/** \brief Set the mutex status of download process.*/
extern void Rte_SetMutexDownStatus(bl_DownContext_t *dct,
                                bl_DownStatus_t mask,
                                bl_DownStatus_t mutex);
/** \brief Clear the status of download process.*/
extern void Rte_ClearDownStatus(bl_DownContext_t *dct, bl_DownStatus_t mask);
/** \brief Clear the all status of download process.*/
extern void Rte_ClearAllDownStatus(bl_DownContext_t *dct);
/** \brief Check the status whether is valid by the mask.*/
extern bl_Return_t Rte_IsValidStatus(const bl_DownContext_t *dct,
                                        bl_DownStatus_t mask);
/** \brief Check the status whether is valid by the mask.*/
extern bl_Return_t Rte_IsAllValidStatus(const bl_DownContext_t *dct,
                                            bl_DownStatus_t mask);
/** \brief Check the status whether is valid by the mask.*/
extern bl_Return_t Rte_IsOnlyValidStatus(const bl_DownContext_t *dct,
                                            bl_DownStatus_t mask);

/** \brief Do nothing.*/
extern void Rte_Dummy(void);

#if (RTE_FUN_STAY_IN_BOOT == BL_FUN_ON)
/** \brief Stay in boot.*/
extern bl_Return_t Rte_StayInBoot(void);
#endif

#endif


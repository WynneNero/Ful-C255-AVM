/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of the adapter module based on uds
 *              platform.
 *
 *  \file       bl_adpt_uds_platform.c
 *  \ingroup    communication_adapter_module
 *  \author     heli.zhang <heli.zhang@hirain.com>
 *
 *  \version    5.2.0
 *  \date       19/06/2014
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
 *      05.02.00 | 19/06/2014 | mingqing.tang    | N/A | BootSpec050001
 *
 *****************************************************************************/
#include "config.h"
#include "bl_common.h"
#include "bl_rte.h"
#include "bl_data.h"
#include "bl_can_tp.h"
#include "bl_can_if.h"
#include "bl_dcm.h"
#include "bl_adapter.h"
#include "bl_security.h"
#include "bl_logical_block.h"

#include "bl_adpt_uds_platform.h"
#include "bl_adpt_uds_platform_cfg.h"
#include "General.h"
#include "define.h"

#include "r_fdl_types.h"

unsigned char send_to_soc_finish=0;
unsigned char receive_spi_data=0;
unsigned char diff_data_for_soc=0;
unsigned char start_flash_operation_falg;
unsigned char application_invalue_flag = TRUE;
unsigned char is_soc_updating = FALSE;
unsigned char updating_mcu_success ;
extern unsigned char  updating_soc_success;
extern unsigned char can_to_spi_data[512];
extern unsigned char BL_upgrade_type;
extern unsigned char total_length[5];
extern unsigned char version[32];
extern unsigned char max_version_length;
extern unsigned char get_version;
unsigned int delay_to_execute_1101reset;
BOOL SuspendedResponse_flag=FALSE;

extern void set_1101reset_timer(unsigned int timer);
extern void PgrmAttempCounter();
extern void PgrmCounter();

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 506,602,771,781,783,1251,1253,1257,1258,1505,1531,1532,2100,2103 EOF*/
/*PRQA S 3112,3120,3204,3211,3212,3218,3227,3416,3455,3673,4121,4152 EOF*/
/*
 * 506:Dereferencing pointer value that is possibly NULL.
 * The parameters are not a null pointer.
 *
 * MISRA-C:2004 20.2(602):The identifier is reserved for use by the library.
 * The Bootloader do not use any library funtion and use the underscores to
 * indicate that the function is a interal function.
 *
 * MISRA-C:2004 14.6(771):More than one break statement is being used to
 * terminate an iteration statement.
 * it can simplify the code and have no side-effect.
 *
 * MISRA-C:2004 5.6(781):The identifier is used as a structure/union member.
 * The member of the structure is used through the structure object.
 *
 * 783:A subsequent declaration of the identifier means that it is being used
 * both as a structure/union member and also as a label, ordinary identifier.
 * The member of the structure is used through the structure object.
 *
 * 1251:Suffixed integer constant causes implicit conversion of other
 * (integral) operand.
 *
 * 1253:Unsuffixed integer constant implicitly converted to different integer
 * type.
 *
 * 1257:Suffixed integer constant implicitly converted to smaller integer type
 * on assignment.
 *
 * 1258:Suffixed integer constant explicitly cast to another type.
 *
 * 1531:The object is referenced in only one translation unit.
 *
 * 1532:The function is only referenced in one translation unit.
 *
 * 2100:Integral promotion : unsigned char promoted to signed int.
 *
 * 2103:Integral promotion, unsigned short promoted to unsigned int.
 * This message will therefore only be generated when a short and an int are of
 * equal size.
 *
 * MISRA-C:2004 14.2(3112):This statement has no side-effect.
 * The DEBUG_ASSERT macro is used to debug bootloader when the BL_DEBUG is
 * enable. When the BL_DEBUG is disable, the DEBUG_ASSERT macro is null.
 *
 * 3120:Hard-coded magic integer constant.
 * This is a only configuration.
 *
 * 3204:The variable is only set once and so it could be declared with the
 * 'const' qualifier.
 *
 * 3211:The global identifier is defined but not used.
 *
 * 3212:This explicit cast is redundant and could be removed.
 *
 * MISRA-C:2004 8.7(3218):File scope static identifier is only accessed in one
 * function.
 *
 * 3227:The parameter is never modified and so it could be declared with const.
 *
 * 3416:This boolean expression contains side effects.
 * This function has no side-effects.
 *
 * 3455:Macro argument contains a function call.
 *
 * MISRA-C:2004 16.7(3673): the pointer could be of type 'pointer to const'.
 * These functions are callback of the DCM module.
 *
 * MISRA-C:2004 10.3(4121):Cast of complex expression of integral type to wider
 * type.
 *
 * 4152:The identifier may cause confusion.
 * Adpt_UdsCallbackGetSeedForLevel1 is LEVEL One.
 * Adpt_UdsCallbackVerifyKeyForLevel1 is LEVEL One.
 *
 */

/*****************************************************************************
 *  Verify The Configurations of Macro
 *****************************************************************************/
#if (DCM_BUFFER_SIZE < ADPT_MAXNUM_OF_BLOCKLENGTH)
#error "the buffer of the Dcm module is too small."
#endif

#if (RTE_FUN_GATEWAY == BL_FUN_ON)
#error "the function of gateway is not ok."
#endif
/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/
/*lint -emacro(778,ADPT_SESSION_RESPONSE0,ADPT_SESSION_RESPONSE1)*/
/*lint -emacro(778,ADPT_SESSION_RESPONSE2,ADPT_SESSION_RESPONSE3)*/
/*lint -emacro(572,ADPT_SESSION_RESPONSE0,ADPT_SESSION_RESPONSE1)*/
/*lint -emacro(572,ADPT_SESSION_RESPONSE2,ADPT_SESSION_RESPONSE3)*/
#define ADPT_P2START_TIMER          (DCM_P2STARTIMEVALUE/DCM_P2STARTIMER_DIV)    
#define ADPT_SESSION_RESPONSE0      ((DCM_P2TIMEVALUE >> 8) & 0xFFu)
#define ADPT_SESSION_RESPONSE1      ((DCM_P2TIMEVALUE >> 0) & 0xFFu)

#if 0
#define ADPT_SESSION_RESPONSE2      ((DCM_P2STARTIMEVALUE >> 8) & 0xFFu)
#define ADPT_SESSION_RESPONSE3      ((DCM_P2STARTIMEVALUE >> 0) & 0xFFu)
#endif
#define ADPT_SESSION_RESPONSE2      (((DCM_P2STARTIMEVALUE/10) >> 8) & 0xFFu) /*Resolution (ms/bit)=10ms,modify by LT.20160609*/
#define ADPT_SESSION_RESPONSE3      (((DCM_P2STARTIMEVALUE/10) >> 0) & 0xFFu) /*Resolution (ms/bit)=10ms,modify by LT.20160609*/



#define ADPT_MEMORY_LEN_FORMAT          (0x04u)
#define ADPT_MEMORY_ADDR_FORMAT         (0x04u)

#define ADPT_MEMORY_LENANDADDR_FORMAT   ((ADPT_MEMORY_LEN_FORMAT << 4) \
                                           | ADPT_MEMORY_ADDR_FORMAT)

#define ADPT_ERASE_DATA_LENGTH          (0x01u \
                                           + ADPT_MEMORY_LEN_FORMAT \
                                           + ADPT_MEMORY_ADDR_FORMAT)
#define ADPT_CHECKSUM_LENGTH            (0x04u)

#define ADPT_DATAFORMAT_IDEN            (0x00u)
#define ADPT_LENFORMAT_IDEN             (0x20u)
#define ADPT_IDEN_LEN_FORMAT            ((ADPT_LENFORMAT_IDEN >> 4) & 0x0Fu)
#define ADPT_REQDOWNLOAD_RESPLENGTH     (0x01u + ADPT_IDEN_LEN_FORMAT)

/** \brief Indicate the 31 service is ok.*/
#define ADPT_ROUTINE_CORRECT_RESULT     (0x00)
/** \brief Indicate the 31 service is not ok.*/
#define ADPT_ROUTINE_INCORRECT_RESULT   (0x01)

#define ADPT_UDS_SYSTEM_STATUS_MASK     (RTE_SYSFLAG_WRITE_FINGPRINT \
                                            | ADPT_SYSTEM_STATUS_MASK)

#define ADPT_UDS_STATUS_MASK            (ADPT_STATUS_ALLOW_TRANS_DATA \
                                            | ADPT_STATUS_BLOCK_FIRST_DATA \
                                            | ADPT_STATUS_SEGMENT_FIRST_DATA)

#define ADPT_UDS_36_SERVICE_ID              (0x36u)
#define ADPT_UDS_31_SERVICE_ID              (0x31u)
#define ADPT_UDS_3E_SERVICE_ID              (0x3Eu)
#define ADPT_UDS_11_SERVICE_ID              (0x11u)

#define ADPT_UDS_36_SERVICE_INDEX_POS       (0x00u)
#define ADPT_UDS_36_SERVICE_DATA_POS        (0x01u)

#define ADPT_UDS_ERASE_MEMORY_FORMAT_POS    (0)
#define ADPT_UDS_ERASE_MEMORY_ADDRESS_POS   (1)
#define ADPT_UDS_ERASE_MEMORY_SIZE_POS      (5)

#define ADPT_UDS_34_SERVICE_IDEN_POS        (0)
#define ADPT_UDS_34_SERVICE_ADDRANDSIZE_POS (1)
#define ADPT_UDS_34_SERVICE_ADDRESS_POS     (2)
#define ADPT_UDS_34_SERVICE_SIZE_POS        (ADPT_UDS_34_SERVICE_ADDRESS_POS \
                                                + ADPT_MEMORY_ADDR_FORMAT)

#define ADPT_UDS_34_RESPONSE_FORMAT_POS     (0)
#define ADPT_UDS_34_RESPONSE_SIZE_POS       (1)


#define ADPT_STATUS_ALLOW_TRANS_DATA        DCM_MAKE_FLAG(0x20000000UL)
#define ADPT_STATUS_BLOCK_FIRST_DATA        DCM_MAKE_FLAG(0x10000000UL)
#define ADPT_STATUS_SEGMENT_FIRST_DATA      DCM_MAKE_FLAG(0x08000000UL)

#define ADPT_UDS_MAX_CAN_FRAME_SIZE         (8)
#define ADPT_UDS_CAN_FRAME_INDEX_0          (0)
#define ADPT_UDS_CAN_FRAME_INDEX_1          (1)
#define ADPT_UDS_CAN_FRAME_INDEX_2          (2)
#define ADPT_UDS_CAN_FRAME_INDEX_3          (3)
#define ADPT_UDS_CAN_FRAME_INDEX_4          (4)
#define ADPT_UDS_CAN_FRAME_INDEX_5          (5)
#define ADPT_UDS_CAN_FRAME_INDEX_6          (6)
#define ADPT_UDS_CAN_FRAME_INDEX_7          (7)

/*****************************************************************************
 *  Internal Type Definitions
 *****************************************************************************/
/** \brief A alias of struct _tag_AdapterData.*/
typedef struct _tag_AdapterData bl_AdapterData_t;

#if (RTE_FUN_GATEWAY == BL_FUN_ON)
/** \brief A alias of struct _tag_GatewayTransmitList.*/
typedef struct _tag_GatewayTransmitList bl_GatewayTransmitList_t;
/** \brief A alias of struct _tag_GatewayConversion.*/
typedef struct _tag_GatewayConversion bl_GatewayConversion_t;
#endif

/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/
/** \brief This is data of a adapter.*/
struct _tag_AdapterData
{
    struct _tag_SecurityDelay delay;    /**< security access delay*/
    bl_u8_t blockIndex;     /**< the block index of 36 service*/
    bl_Buffer_t serviceId;  /**< the id of processing service*/
    bl_Address_t address;   /**< the address of 36 service*/
    bl_Size_t remainSize;   /**< the remain size of 36 service*/
};

#if(RTE_FUN_GATEWAY == BL_FUN_ON)
/** \brief This is a list of gateway transmission.*/
struct _tag_GatewayTransmitList
{
    bl_u16_t handle;
    bl_u16_t number;
    struct _tag_GatewayConversion *data;
};

/**
 * \brief This is info of gateway conversion, it includes services
 *        needed to be transmitted.
 */
struct _tag_GatewayConversion
{
    bl_u8_t sid;
    bl_u16_t size;
    bl_Buffer_t *data;
};

#endif
/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/
#if(RTE_FUN_GATEWAY == BL_FUN_ON)
/** \brief Gateway transmits messages.*/
static void _Adpt_UdsGatewayTransmit(bl_u8_t id);
#endif
/** \brief Send 0x78 negative response.*/
static void _Adpt_UdsPendingResponse(bl_u8_t id);
/** \brief Timeout callback of sending 0x78.*/
static void _Adpt_TimeOutCallBack(bl_u8_t id);
/** \brief send a response by comif.*/
static void _Adpt_SendResponse(bl_BufferSize_t size, const bl_Buffer_t *buffer);
/** \brief Set response info of session.*/
static bl_BufferSize_t _Adpt_SetSessionResp(bl_Buffer_t *buffer);
/** \brief Goto the session.*/
static void _Adpt_UdsGotoSession(bl_DownStatus_t sessionMask);
/** \brief Reset the bootloader.*/
#if 0
static void _Adpt_UdsResetSystem(bl_u8_t sid, bl_u16_t flagId);
#endif
/** \brief Clear the download information.*/
static void _Adpt_UdsClearDownInfo(bl_AdapterData_t *adpt);

/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/
/** \brief Private data variable.*/
static bl_AdapterData_t gs_UdsPrivateData;
static const bl_Buffer_t gs_DefaultResponse[ADPT_UDS_MAX_CAN_FRAME_SIZE] =
{
    0x06u,0x50u,0x01u,ADPT_SESSION_RESPONSE0,ADPT_SESSION_RESPONSE1,
    ADPT_SESSION_RESPONSE2,ADPT_SESSION_RESPONSE3,CANTP_FRAME_PADDING_VALUE
};

static const bl_Buffer_t gs_ReprogrammingResponse[ADPT_UDS_MAX_CAN_FRAME_SIZE]=
{
    0x06u,0x50u,0x02u,ADPT_SESSION_RESPONSE0,ADPT_SESSION_RESPONSE1,
    ADPT_SESSION_RESPONSE2,ADPT_SESSION_RESPONSE3,CANTP_FRAME_PADDING_VALUE
};

static const bl_Buffer_t gs_ResetResponse[ADPT_UDS_MAX_CAN_FRAME_SIZE] =
{
    0x02u,0x51u,0x01u,CANTP_FRAME_PADDING_VALUE,
    CANTP_FRAME_PADDING_VALUE,CANTP_FRAME_PADDING_VALUE,
    CANTP_FRAME_PADDING_VALUE,CANTP_FRAME_PADDING_VALUE
};

static const bl_Buffer_t gs_softResetResponse[ADPT_UDS_MAX_CAN_FRAME_SIZE] =
{
    0x02u,0x51u,0x03u,CANTP_FRAME_PADDING_VALUE,
    CANTP_FRAME_PADDING_VALUE,CANTP_FRAME_PADDING_VALUE,
    CANTP_FRAME_PADDING_VALUE,CANTP_FRAME_PADDING_VALUE
};


#if (RTE_FUN_STAY_IN_BOOT == BL_FUN_ON)
static const bl_Buffer_t gs_StayInBootResponse[ADPT_UDS_MAX_CAN_FRAME_SIZE] =
{
    0x04u,0x71u,0x01u,ADPT_STAY_IN_BOOT_RESPONSE_HID,
    ADPT_STAY_IN_BOOT_RESPONSE_LID,CANTP_FRAME_PADDING_VALUE,
    CANTP_FRAME_PADDING_VALUE,CANTP_FRAME_PADDING_VALUE
};
#endif

#if(RTE_FUN_GATEWAY == BL_FUN_ON)
/** \details The data of gateway conversion. */
static const bl_u8_t gs_UdsGatewayData[ADPT_UDS_CONVERSION_DATA_LENGTH] =
{
    0x3Eu, 0x80u,
}

/** \details A list of gateway transmission. */
static const bl_GatewayTransmitList_t gs_UdsGatewayList =
{
    ADPT_UDS_COMOPS_HANDLE,
    ADPT_UDS_NUMBER_OF_GATEWAY,
    gs_UdsGateway,
};

/** \details The info of gateway conversion. */
static const bl_GatewayConversion_t gs_UdsGateway[ADPT_UDS_NUMBER_OF_GATEWAY] =
{
    {
        ADPT_UDS_3E_SERVICE_ID,
        ADPT_UDS_CONVERSION_DATA_LENGTH,
        gs_UdsGatewayData
    },
};

#endif

/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/
/** \details The Uds platform adapter informations. */
const bl_Adapter_t g_UdsPlatformAdapter =
{
    0x00u, 0x00u, &Adpt_UdsInit, &Adpt_UdsCallback,
    &Adpt_UdsPeriodicCallback, &Adpt_UdsTimeOutCallBack,
#if (RTE_FUN_SYSTEM_SLEEP == BL_FUN_ON)
    &Canif_Sleep,
#else
    BL_NULL_PTR, /*RTE_FUN_SYSTEM_SLEEP is OFF*/
#endif
};
/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/
/**************************************************************************//**
 *
 *  \details Initialize the uds module. This function mainly initialize
 *           CanTp, dcm and security access delay info.
 *
 *  \return If Initialization is successful return BL_ERR_OK,
 *          otherwise return BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK       - Initialize successfully.
 *  \retval BL_ERR_NOT_OK   - Initialize unsuccessfully.
 *
 *  \note This function is called by the process driver module.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_Return_t Adpt_UdsInit(void)
{
    bl_Return_t ret = BL_ERR_OK;

#if (RTE_FUN_STAY_IN_BOOT == BL_FUN_OFF)
    ret = Canif_Init();
#endif
    Cantp_Init();
    Dcm_Init();

    gs_UdsPrivateData.serviceId = 0;

    Adpt_InitDelayInfo(&gs_UdsPrivateData.delay);

    _Adpt_UdsGotoSession(DCM_STATUS_SESSION_DEFAULT);

    return ret;
}

/**************************************************************************//**
 *
 *  \details Periodic callback of function Rte_PeriodicSchedule. This function
 *           needs to be called periodically, and mainly handles timer of dcm,
 *           and CanTp module.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
void Adpt_UdsPeriodicCallback(void)
{
    Adpt_DelayTimeCallback(&gs_UdsPrivateData.delay);
    Dcm_TimerFunction();
    Cantp_PeriodFunction();
    Dcm_MainFunction();
}

/**************************************************************************//**
 *
 *  \details Callback of the adapter, it should be always running. This
 *           function will be called by process driver module, and performs
 *           tx confirmation and rx indication.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
void Adpt_UdsCallback(void)
{
    Canif_TxMainFunction();
    Canif_RxMainFunction();
    Canif_BusoffMainFunction();
}

/**************************************************************************//**
 *
 *  \details Callback of default session.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallback1001(bl_BufferSize_t size,
                                       bl_Buffer_t *buffer,
                                       bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;

    (void)size;

    /*programming session.*/
    ret = Rte_IsValidStatus(&g_DownContext, DCM_STATUS_SESSION_PROGRAMMING);
    if(BL_ERR_OK == ret)
    {
        if (Dcm_IsSuspendedResponse() != BL_ERR_OK)
        {
            _Adpt_SendResponse((bl_BufferSize_t)sizeof(gs_DefaultResponse),
                                gs_DefaultResponse);
        }
        g_RteInfo.SystemReset();
    }
    else
    {
        /*extended session.*/
        ret = Rte_IsValidStatus(&g_DownContext,
                                    DCM_STATUS_SESSION_EXTENDED);
        if(BL_ERR_OK == ret)
        {
            Dcm_StopS3Timer();
            _Adpt_UdsGotoSession(DCM_STATUS_SESSION_DEFAULT);
        }

        *respSize = _Adpt_SetSessionResp(buffer);
    }

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of programming session.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallback1002(bl_BufferSize_t size,
                                       bl_Buffer_t *buffer,
                                       bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_CONDITIONSNOTCORRECT;
    bl_Return_t ret;

    (void)size;

    ret = Rte_IsValidStatus(&g_DownContext, DCM_STATUS_SESSION_DEFAULT);
    if (ret != BL_ERR_OK) /*the default can not go to programming.*/
    {
        Dcm_StartS3Timer();

        Lbm_ClearBlock(&g_DownContext);

        Rte_ClearAddressInfo(&g_DownContext);

        _Adpt_UdsGotoSession(DCM_STATUS_SESSION_PROGRAMMING);

        *respSize = _Adpt_SetSessionResp(buffer);

        resCode = DCM_E_POSITIVERESPONSE;
    }

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of extended session.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallback1003(bl_BufferSize_t size,
                                       bl_Buffer_t *buffer,
                                       bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_CONDITIONSNOTCORRECT;
    bl_Return_t ret;

    (void)size;

    /*programming session.*/
    ret = Rte_IsValidStatus(&g_DownContext, DCM_STATUS_SESSION_PROGRAMMING);
    if (ret != BL_ERR_OK) /*the programming can not go to extended.*/
    {
        Dcm_StartS3Timer();

        _Adpt_UdsGotoSession(DCM_STATUS_SESSION_EXTENDED);

        *respSize = _Adpt_SetSessionResp(buffer);

        resCode = DCM_E_POSITIVERESPONSE;
    }

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of reset.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallback1101(bl_BufferSize_t size,
                                       bl_Buffer_t *buffer,
                                       bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING;

    (void)respSize;
    (void)buffer;
    (void)size;
	if(is_soc_updating==TRUE)
	{
		delay_to_execute_1101reset=120000;
		gs_UdsPrivateData.serviceId = ADPT_UDS_11_SERVICE_ID;
		_Adpt_TimeOutCallBack(ADPT_UDS_11_SERVICE_ID);
	}//2min
	else
	{
 		if(application_invalue_flag==FALSE) 
		{
			if (Dcm_IsSuspendedResponse() == BL_ERR_OK)
			{
				//_Adpt_SendResponse((bl_BufferSize_t)sizeof(gs_ResetResponse),
				//				gs_ResetResponse);
					SuspendedResponse_flag = TRUE;
			}
			delay_to_execute_1101reset=101;//ccj.jump to application with haven't upgrade  
		}
		else
		{
			gs_UdsPrivateData.serviceId = ADPT_UDS_11_SERVICE_ID;
			_Adpt_TimeOutCallBack(ADPT_UDS_11_SERVICE_ID);
			delay_to_execute_1101reset=1500;
		}
		
	//	delay_to_execute_1101reset=1500;
	}//1.5 S
//	Sys_Reset();

   // g_RteInfo.SystemReset();

    /*never return*/

    return resCode;
}




/**************************************************************************//**
*
*  \details Callback of reset.
*
*  \param[in]	  size	   - the data size, not include id, subid and did.
*  \param[in/out] buffer   - the pointer of data.
*  \param[out]	  respSize - the size of response data.
*
*  \return Return response code.
*
*  \retval 0x00   - Positive response code.
*  \retval others - Negative response code.
*
*  \since  V3.0.0
*
*****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallback1103(bl_BufferSize_t size,
									  bl_Buffer_t *buffer,
									  bl_BufferSize_t *respSize)
{
   bl_ResponseCode_t resCode = DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING;

   (void)respSize;
   (void)buffer;
   (void)size;

   if (Dcm_IsSuspendedResponse() != BL_ERR_OK)
   {
	   _Adpt_SendResponse((bl_BufferSize_t)sizeof(gs_softResetResponse),
					   gs_softResetResponse);
   }

   /*
   if(is_soc_updating==TRUE)
   {delay_to_execute_1101reset=120000;}//2min
	   
   else
   {
	   if(application_invalue_flag==FALSE) 
	   {
		   delay_to_execute_1101reset=101;//ccj.jump to application with haven't upgrade  
	   }
	   else
	   {
		   delay_to_execute_1101reset=1500;
	   }
	   
   //  delay_to_execute_1101reset=1500;
   }//1.5 S
   */
	  Sys_Reset();

  // g_RteInfo.SystemReset();

   /*never return*/

   return resCode;
}

bl_application_value_dataflash_maker(void)
{
   unsigned char appli_invalue_str[8] = {0x11,0x22,0x33,0x44,0xff,0xff,0xff,0xff};
   unsigned char appli_value_str[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
   if(BL_upgrade_type == UPGRADE_BY_SPI)
   {
		return;
   }
   if(application_invalue_flag == TRUE)
   {
	   /*Application invalue*/
	   FLS_u8WriteDataWait(0xff200000,0x08,appli_invalue_str);//11223344
   }
   else
   {
   	   /*Application value*/
	   FLS_u8WriteDataWait(0xff200000,0x08,appli_value_str);//ffffffff
   }

}

/**************************************************************************//**
 *
 *  \details Callback of reading fingerprint.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallBackReadEcuPartNum(bl_BufferSize_t size,
                                                  bl_Buffer_t *buffer,
                                                  bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;

    (void)size;

    /*read fingerprint.*/
    ret = Dm_ReadData(ADPT_ECUPARTNUMBER_FLAGID,
                         (bl_Size_t)RTE_ECUPARTNUMBER_SIZE, buffer);
    if(BL_ERR_OK != ret)
    {
        resCode = DCM_E_CONDITIONSNOTCORRECT;
    }
    else
    {
        *respSize = RTE_ECUPARTNUMBER_SIZE;
    }

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of getting seed.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallbackGetSeedForLevel1(bl_BufferSize_t size,
                                                   bl_Buffer_t *buffer,
                                                   bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;
#if(ADPT_FUN_DELAY_WITH_CONTINUOUS_SEED == BL_FUN_ON)
    bl_u16_t remainCount = 0;
#endif

    (void)size;

    do
    {
        /*judge wheter security access is available.*/
        ret = Adpt_IsAccessible(&gs_UdsPrivateData.delay);
        if (ret != BL_ERR_OK)
        {
            resCode = DCM_E_REQUIREDTIMEDELAYNOTEXPIRED;
            break;
        }

        ret = Rte_IsValidStatus(&g_DownContext, DCM_STATUS_SECURITY_UNLOCK_1);
        if(BL_ERR_OK == ret)
        {
            /*when unlock, return seed 0x00u.*/
            Bl_MemSet(buffer,0,(bl_Size_t)SECM_ACCESS_SEED_SIZE);
            break;
        }

        /*If a seed is requested, return it.*/
        ret = Rte_IsValidStatus(&g_DownContext, DCM_STATUS_SECURITY_WAITKEY_1);
        if(BL_ERR_OK == ret)
        {
#if(ADPT_FUN_DELAY_WITH_CONTINUOUS_SEED == BL_FUN_ON)
            /*if always request seed, decrease attemptcount.*/
            remainCount = Adpt_DecreaseAttemptCount(&gs_UdsPrivateData.delay);
            if(remainCount == 0x00u)
            {
#if(ADPT_FUN_SAVE_DELAY_FLAG == BL_FUN_ON)
                /*set security access delay flag.*/
                (void)Dm_WriteDefaultData(gs_UdsPrivateData.delay.delayFlagId);
#endif

                Rte_SetMutexDownStatus(&g_DownContext,
                                        DCM_STATUS_SECURITY_LOCK_1,
                                        DCM_SECURITYACCESS_1_MASK);

                resCode = DCM_E_EXCEEDNUMBEROFATTEMPTS;
                break;
            }
#endif
			/*request a new seed.*/
			Secm_MakeNewSeed();

            /*return the last seed.*/
            Secm_GetSeed(buffer);

            break;
        }

        /*request a new seed.*/
        Secm_MakeNewSeed();
        /*Copy the seed to buffer*/
        Secm_GetSeed(buffer);
        /*set wait key status.*/
        Rte_SetDownStatus(&g_DownContext, DCM_STATUS_SECURITY_WAITKEY_1);

    }while(0);/*lint !e717*/

    *respSize = SECM_ACCESS_SEED_SIZE;

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of verifying key.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
/*lint -e{818}*/
bl_ResponseCode_t Adpt_UdsCallbackVerifyKeyForLevel1(bl_BufferSize_t size,
                                                     bl_Buffer_t *buffer,
                                                     bl_BufferSize_t *respSize)
{
    bl_u16_t remainCount;
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;

    do
    {
        ret = Rte_IsValidStatus(&g_DownContext,
                                    DCM_STATUS_SECURITY_WAITKEY_1);
        if (ret != BL_ERR_OK)
        {
            resCode = DCM_E_REQUESTSEQUENCEERROR;
            break;
        }

        /*verify key.*/
        ret = Secm_VerifyKey((bl_Size_t)size,buffer);
        if (ret != BL_ERR_OK)
        {               
            remainCount = Adpt_DecreaseAttemptCount(&gs_UdsPrivateData.delay);

			Rte_SetMutexDownStatus(&g_DownContext,
									DCM_STATUS_SECURITY_LOCK_1,
									DCM_SECURITYACCESS_1_MASK);
            if (0x00u == remainCount)
            {
#if(ADPT_FUN_SAVE_DELAY_FLAG == BL_FUN_ON)
                /*set security access delay flag.*/
                (void)Dm_WriteDefaultData(gs_UdsPrivateData.delay.delayFlagId);
#endif


                resCode = DCM_E_EXCEEDNUMBEROFATTEMPTS;
            }
            else
            {
                resCode = DCM_E_INVALIDKEY;
            }

            break;
        }

        *respSize = 0x00u;
        Rte_SetMutexDownStatus(&g_DownContext,
                                DCM_STATUS_SECURITY_UNLOCK_1,
                                DCM_SECURITYACCESS_1_MASK);
    }while(0);/*lint !e717*/

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of enable or disable communication.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval DCM_E_POSITIVERESPONSE   - Positive response code.
 *  \retval DCM_E_REQUESTOUTOFRANGE - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
/*lint -e{818}*/
bl_ResponseCode_t Adpt_UdsCallback28(bl_BufferSize_t size,
                                       bl_Buffer_t *buffer,
                                       bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;

    (void)size;

    if((ADPT_COMMCONTROLTYPE_DATA != buffer[0])&&(ADPT_COMMCONTROLTYPE_DATA_ALL != buffer[0]))
    {
        resCode = DCM_E_REQUESTOUTOFRANGE;
    }
    else
    {
        *respSize = 0x00u;
    }


    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of writting fingerprint.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
/*lint -e{818}*/
/*Write Hardware Num,this no need to supported*/
bl_ResponseCode_t Adpt_UdsCallBackWriteEcuPartNum(bl_BufferSize_t size,
                                                   bl_Buffer_t *buffer,
                                                   bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_GENERALPROGRAMMINGFAILURE;
    bl_Return_t ret;

    ret = Dm_WriteData(ADPT_ECUPARTNUMBER_FLAGID, (bl_Size_t)size, buffer);
    if(BL_ERR_OK == ret)
    {
#if (LBM_FUN_SAVE_FINGERPRINT == BL_FUN_ON)
        Lbm_SaveFingerprint(buffer);
#endif
        //Rte_SetDownStatus(&g_DownContext, RTE_SYSFLAG_WRITE_FINGPRINT);
        *respSize = 0u;

        resCode = DCM_E_POSITIVERESPONSE;
    }

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of writting fingerprint.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
/*lint -e{818}*/
bl_ResponseCode_t Adpt_UdsCallBackWriteTesterNum(bl_BufferSize_t size,
                                                   bl_Buffer_t *buffer,
                                                   bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_GENERALPROGRAMMINGFAILURE;
    bl_Return_t ret = BL_ERR_OK;

    ret = Dm_WriteData(ADPT_TESTERNUMBER_FLAGID, (bl_Size_t)(size+6), buffer);
    if(BL_ERR_OK == ret)
    {
#if (LBM_FUN_SAVE_FINGERPRINT == BL_FUN_ON)
        Lbm_SaveFingerprint(buffer);
#endif
        Rte_SetDownStatus(&g_DownContext, RTE_SYSFLAG_WRITE_FINGPRINT);
        *respSize = 0u;

        resCode = DCM_E_POSITIVERESPONSE;
    }

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of writting fingerprint.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
/*lint -e{818}*/
bl_ResponseCode_t Adpt_UdsCallbackWriteProgramDate(bl_BufferSize_t size,
                                                   bl_Buffer_t *buffer,
                                                   bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_GENERALPROGRAMMINGFAILURE;
    bl_Return_t ret = BL_ERR_OK;
	U8 index = 0;
	U8 WriteDate = 0;
	U8 HighFourBit = 0;
	U8 LowFourBit = 0;

	for(index = 0; index < 4; index++)
	{
		WriteDate = buffer[index];
		LowFourBit = (buffer[index] & 0x0F);
		HighFourBit = ((buffer[index] >> 4) & 0x0F);
		if((HighFourBit >= 0x0A)||(LowFourBit >= 0x0A))
		{
			resCode = DCM_E_REQUESTOUTOFRANGE;
			return resCode;
		}
	}
	
    ret = Dm_WriteData(ADPT_PROGRAMMINGDATE_FLAGID, (bl_Size_t)size, buffer);
    if(BL_ERR_OK == ret)
    {
#if (LBM_FUN_SAVE_FINGERPRINT == BL_FUN_ON)
        Lbm_SaveFingerprint(buffer);
#endif
        //Rte_SetDownStatus(&g_DownContext, RTE_SYSFLAG_WRITE_FINGPRINT);
        *respSize = 0u;

        resCode = DCM_E_POSITIVERESPONSE;
    }

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of checking programming contiditions.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallbackCheckProgramCond(bl_BufferSize_t size,
                                                   bl_Buffer_t *buffer,
                                                   bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;

    (void)size;

    *respSize = 0x01u;
    buffer[0] = ADPT_ROUTINE_CORRECT_RESULT;

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of erasing memory.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallbackEraseMemory(bl_BufferSize_t size,
                                              bl_Buffer_t *buffer,
                                              bl_BufferSize_t *respSize)
{
    bl_Size_t eraseSize;
    bl_Address_t address;
    bl_ResponseCode_t resCode = DCM_E_REQUESTOUTOFRANGE;
    bl_Return_t ret;
    bl_u8_t DataBuff[20];
    (void)size;
    if(((bl_Buffer_t)ADPT_MEMORY_LENANDADDR_FORMAT == buffer[ADPT_UDS_ERASE_MEMORY_FORMAT_POS])
		&&(BL_BE32_TO_MCU(&buffer[ADPT_UDS_ERASE_MEMORY_ADDRESS_POS])>0)
		&&(BL_BE32_TO_MCU(&buffer[ADPT_UDS_ERASE_MEMORY_SIZE_POS])>0))
    {

		address = BL_BE32_TO_MCU(&buffer[ADPT_UDS_ERASE_MEMORY_ADDRESS_POS]);
		if(address==0x1000C0)
		{ 
			diff_data_for_soc=1;	
			is_soc_updating=TRUE;
		}
		eraseSize = BL_BE32_TO_MCU(&buffer[ADPT_UDS_ERASE_MEMORY_SIZE_POS]);

        gs_UdsPrivateData.serviceId = ADPT_UDS_31_SERVICE_ID;
        _Adpt_TimeOutCallBack(ADPT_UDS_31_SERVICE_ID);
		if(application_invalue_flag == FALSE)
		{
			application_invalue_flag = TRUE;
		  	bl_application_value_dataflash_maker();
		}
	
		PgrmAttempCounter();
		
		__DI();//disable interrupt  xjy
        ret = Adpt_EraseLB(&g_DownContext, address, eraseSize);
		__EI(); //enable interrupt 
        #if 0  /*no need to write the 0xF199,0xF198,have been write to the dataflash-LT-20160601*/
        (void)Dm_ReadData(ADPT_TESTERNUMBER_FLAGID,(bl_Size_t)16u, DataBuff);

        //(void)Dm_WriteData(ADPT_TESTERNUMBER_FLAGID - 2,(bl_Size_t)16u, DataBuff);

        (void)Dm_ReadData(ADPT_PROGRAMMINGDATE_FLAGID,(bl_Size_t)4u, &DataBuff[16]);

        (void)Dm_WriteData(ADPT_PROGRAMMINGDATE_FLAGID + 1,(bl_Size_t)20u, DataBuff);
        #endif


        if(BL_ERR_OK == ret)
        {
            buffer[0] = ADPT_ROUTINE_CORRECT_RESULT;
        }
        else
        {
            Rte_ClearDownStatus(&g_DownContext, ADPT_UDS_STATUS_MASK);
            buffer[0] = ADPT_ROUTINE_INCORRECT_RESULT;
        }

        *respSize = 0x01u;

        resCode = DCM_E_POSITIVERESPONSE;
    }
	if(diff_data_for_soc==1)
	{
		buffer[0] = ADPT_ROUTINE_CORRECT_RESULT;
		 resCode = DCM_E_POSITIVERESPONSE;
	}
    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of checksum.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_u32_t TransCrc;
bl_ResponseCode_t Adpt_UdsCallbackCheckSum(bl_BufferSize_t size,
                                           bl_Buffer_t *buffer,
                                           bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret=0;
    gs_UdsPrivateData.serviceId = ADPT_UDS_31_SERVICE_ID;
    _Adpt_TimeOutCallBack(ADPT_UDS_31_SERVICE_ID);

	size = 4;
	buffer[3] = (TransCrc&0x000000FF);
    buffer[2] = (TransCrc&0x0000FF00)>>8;
    buffer[1] = (TransCrc&0x00FF0000)>>16;
    buffer[0] = (TransCrc&0xFF000000)>>24;

	__DI();
    ret = Adpt_VerifyData(&g_DownContext, (bl_Size_t)size, buffer);
	__EI();

    if(BL_ERR_OK == ret || diff_data_for_soc==1)
    {
		application_invalue_flag=FALSE;
        buffer[0] = ADPT_ROUTINE_CORRECT_RESULT;
    }
    else
    {
        buffer[0] = ADPT_ROUTINE_INCORRECT_RESULT;
    }
    Rte_ClearDownStatus(&g_DownContext, ADPT_UDS_STATUS_MASK);

    *respSize = 0x01u;

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of checking compatibility.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/

bl_ResponseCode_t Adpt_UdsCallbackCheckCompatibility(bl_BufferSize_t size,
                                                     bl_Buffer_t *buffer,
                                                     bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;
	
    (void)size;
	//start_flash_operation_falg = TRUE;
    ret = Adpt_CheckCompatibility();
    if(BL_ERR_OK == ret || diff_data_for_soc==1)
    {
        buffer[0] = ADPT_ROUTINE_CORRECT_RESULT;
    }
    else
    {
        buffer[0] = ADPT_ROUTINE_INCORRECT_RESULT;
    }

    _Adpt_UdsClearDownInfo(&gs_UdsPrivateData);

    *respSize = 0x01u;

    return resCode;
}

#if (RTE_FUN_STAY_IN_BOOT == BL_FUN_ON)
/**************************************************************************//**
 *
 *  \details Callback of stayinboot.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallbackStayInBoot(bl_BufferSize_t size,
                                             bl_Buffer_t *buffer,
                                             bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;

    (void)buffer;
    (void)size;

    *respSize = 0x00u;

    return resCode;
}
#endif

/**************************************************************************//**
 *
 *  \details Callback of requesting download.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallback34(bl_BufferSize_t size,
                                     bl_Buffer_t *buffer,
                                     bl_BufferSize_t *respSize)
{
    bl_Size_t reqSize;
    bl_Address_t addr;
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;

    (void)size;

    do
    {
        ret = Rte_IsValidStatus(&g_DownContext, ADPT_STATUS_ALLOW_TRANS_DATA);
        if(BL_ERR_OK == ret)
        {
            resCode = DCM_E_REQUESTSEQUENCEERROR;
            break;
        }

        if((ADPT_DATAFORMAT_IDEN != buffer[ADPT_UDS_34_SERVICE_IDEN_POS])
            || (ADPT_MEMORY_LENANDADDR_FORMAT
                    != buffer[ADPT_UDS_34_SERVICE_ADDRANDSIZE_POS]))
        {
            resCode = DCM_E_CONDITIONSNOTCORRECT;
            break;
        }

        addr = BL_BE32_TO_MCU(&buffer[ADPT_UDS_34_SERVICE_ADDRESS_POS]);
        reqSize = BL_BE32_TO_MCU(&buffer[ADPT_UDS_34_SERVICE_SIZE_POS]);

		reqSize = reqSize - 4; //uidq1219:Remove CRC byte size

        ret = Adpt_ActivateDownload(&g_DownContext, addr, reqSize);
		if(diff_data_for_soc==1) {
			ret = BL_ERR_OK;
			total_length[1]=(reqSize & 0xFF000000) >> 24;
			total_length[2]=(reqSize & 0x00FF0000) >> 16;
			total_length[3]=(reqSize & 0x0000FF00) >> 8;
			total_length[4]=reqSize & 0x000000FF; //uidq1219:Remove CRC byte size

			}
        if(BL_ERR_OK == ret)
        {
            buffer[ADPT_UDS_34_RESPONSE_FORMAT_POS] = ADPT_LENFORMAT_IDEN;

#if(1u == ADPT_IDEN_LEN_FORMAT)
            /*get maxnum of block length.*/
            buffer[ADPT_UDS_34_RESPONSE_SIZE_POS] = ADPT_MAXNUM_OF_BLOCKLENGTH;
#elif (2u == ADPT_IDEN_LEN_FORMAT)
            BL_MCU_TO_BE16(&buffer[ADPT_UDS_34_RESPONSE_SIZE_POS],
                            ADPT_MAXNUM_OF_BLOCKLENGTH);
#else
#error "ADPT_IDEN_LEN_FORMAT is error."
#endif

            gs_UdsPrivateData.address = addr;
            gs_UdsPrivateData.remainSize = reqSize;
            gs_UdsPrivateData.blockIndex = 0x01u;

            *respSize = ADPT_REQDOWNLOAD_RESPLENGTH;

            Rte_SetDownStatus(&g_DownContext, ADPT_STATUS_ALLOW_TRANS_DATA);
        }
        else
        {
            resCode = DCM_E_GENERALREJECT;
        }
    }while(0);/*lint !e717*/

    if (resCode != DCM_E_POSITIVERESPONSE)
    {
        _Adpt_UdsClearDownInfo(&gs_UdsPrivateData);
    }
    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of transferring data.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
/*lint -e{818}*/
//unsigned char test[8]={0xAA,0xBB,0xCC,0x44,0x55,0x66,0x77};
bl_ResponseCode_t Adpt_UdsCallback36(bl_BufferSize_t size,
                                     bl_Buffer_t *buffer,
                                     bl_BufferSize_t *respSize)
{
    bl_u8_t expendIndex;
    bl_Size_t dataSize;
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;

    dataSize = (bl_Size_t)(size - 1u); /*overflow checking is not required.*/

    do
    {
        ret = Rte_IsValidStatus(&g_DownContext, ADPT_STATUS_ALLOW_TRANS_DATA);
        if (ret != BL_ERR_OK)
        {
            resCode = DCM_E_REQUESTSEQUENCEERROR;
            break;
        }

        expendIndex = gs_UdsPrivateData.blockIndex;

        ret = Rte_IsValidStatus(&g_DownContext,ADPT_STATUS_SEGMENT_FIRST_DATA);
        if(BL_ERR_NOT_OK == ret)
        {
            if (buffer[ADPT_UDS_36_SERVICE_INDEX_POS] != expendIndex)
            {
                resCode = DCM_E_WRONGBLOCKSEQUENCECOUNTER;
                break;
            }
            /*set first 0x36 service of a download segment.*/
            Rte_SetDownStatus(&g_DownContext, ADPT_STATUS_SEGMENT_FIRST_DATA);
        }

#if(ADPT_FUN_FIRST_DATA_PREPROCESS == BL_FUN_ON)
        ret = Rte_IsValidStatus(&g_DownContext, ADPT_STATUS_BLOCK_FIRST_DATA);
        if(BL_ERR_NOT_OK == ret)
        {

            /*set first 0x36 service of a logical block.*/
            Rte_SetDownStatus(&g_DownContext, ADPT_STATUS_BLOCK_FIRST_DATA);

            App_PreprocessData();
        }
#endif

        /*check whether the SN is valid.*/
        if(buffer[ADPT_UDS_36_SERVICE_INDEX_POS] != expendIndex)
        {
            if (buffer[ADPT_UDS_36_SERVICE_INDEX_POS] != (expendIndex - 1))
            {
                resCode = DCM_E_WRONGBLOCKSEQUENCECOUNTER;
            }
            else
            {
                /*repeat request*/
                resCode = DCM_E_POSITIVERESPONSE;
            }
            break;
        }

        /*Check the size of received data.*/
        if(gs_UdsPrivateData.remainSize > ADPT_MAXNUM_OF_TRANS_DATA)
        {
            /*It is not the last 0x36 service.*/
            if(ADPT_MAXNUM_OF_TRANS_DATA != dataSize)
            {
                resCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                break;
            }
        }
        else if(gs_UdsPrivateData.remainSize != (dataSize - 4))
        {
            resCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            break;
        }
        else
        {
            /*last service and data size is ok.*/
		 	TransCrc = ((buffer[dataSize-3] << 24)|(buffer[dataSize-2] << 16)|(buffer[dataSize-1] << 8)|(buffer[dataSize]));
        }

        /*send 0x78.*/
        gs_UdsPrivateData.serviceId = ADPT_UDS_36_SERVICE_ID;
        _Adpt_TimeOutCallBack(ADPT_UDS_36_SERVICE_ID);
        if(0x39 == buffer[0])
        {
            ret = BL_ERR_OK;
        }
		
		if(application_invalue_flag == FALSE)
		{
			application_invalue_flag = TRUE;
			bl_application_value_dataflash_maker();
			
		}
		__DI();
        ret = Adpt_DownloadData(&g_DownContext,
                                    gs_UdsPrivateData.address,
                                    dataSize,
                                    &buffer[ADPT_UDS_36_SERVICE_DATA_POS]);
		__EI();
        if(BL_ERR_OK != ret)
        {
            resCode = DCM_E_GENERALPROGRAMMINGFAILURE;
            break;
        }
        else
        {
            *respSize = 0x01u;
            gs_UdsPrivateData.blockIndex++;
            gs_UdsPrivateData.address += dataSize;
            gs_UdsPrivateData.remainSize -= dataSize;
        }
    }while(0);/*lint !e717*/

    if (resCode != DCM_E_POSITIVERESPONSE)
    {
        _Adpt_UdsClearDownInfo(&gs_UdsPrivateData);
    }


	if(diff_data_for_soc==1) 
	
	{
		*respSize = 0x01u;
		gs_UdsPrivateData.blockIndex++;
		gs_UdsPrivateData.address += dataSize;
		gs_UdsPrivateData.remainSize -= dataSize;

		if(dataSize == 4)  // 4 is checksum size
		{
			TransCrc = ((buffer[dataSize-3] << 24)|(buffer[dataSize-2] << 16)|(buffer[dataSize-1] << 8)|(buffer[dataSize]));	
		}
		else
		{
			receive_spi_data=1;
			Bl_MemCpy(can_to_spi_data,&buffer[1],512);
			/*send 0x78.*/
			gs_UdsPrivateData.serviceId = ADPT_UDS_36_SERVICE_ID;
			_Adpt_TimeOutCallBack(ADPT_UDS_36_SERVICE_ID);
		}
		resCode=0;
		return resCode;
	
	}


    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of requesting transfer exit.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallback37(bl_BufferSize_t size,
                                     bl_Buffer_t *buffer,
                                     bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;

    (void)buffer;
    (void)size;
    ret = Rte_IsValidStatus(&g_DownContext,
                                ADPT_STATUS_ALLOW_TRANS_DATA);
		
    if(BL_ERR_OK != ret && diff_data_for_soc!=1)
    {
        _Adpt_UdsClearDownInfo(&gs_UdsPrivateData);

        resCode = DCM_E_REQUESTSEQUENCEERROR;
    }
    else
    {
        Rte_ClearDownStatus(&g_DownContext,
                                (ADPT_STATUS_SEGMENT_FIRST_DATA
                                | ADPT_STATUS_ALLOW_TRANS_DATA));
        *respSize = 0x00u;
		updating_mcu_success = TRUE;
    }
	//application_invalue_flag=FALSE;
	if(diff_data_for_soc==1)
	{
		send_to_soc_finish=1;
	}
		
	
    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of keeping session.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallback3E(bl_BufferSize_t size,
                                     bl_Buffer_t *buffer,
                                     bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;

    (void)size;
    (void)buffer;

#if(RTE_FUN_GATEWAY == BL_FUN_ON)
        _Adpt_UdsGatewayTransmit(ADPT_UDS_3E_SERVICE_ID);
#endif

    *respSize = 0x00u;

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of switching on of off dtc.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval DCM_E_POSITIVERESPONSE   - Positive response code.
 *  \retval DCM_E_SUBFUNCTIONNOTSUPPORTED - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallback85(bl_BufferSize_t size,
                                       bl_Buffer_t *buffer,
                                       bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;

    (void)size;
    (void)buffer;

    *respSize = 0x00u;

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Timeout callback of sending 0x78.
 *
 *  \param[in]  id  - service id.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
void Adpt_UdsTimeOutCallBack(void)
{
    _Adpt_TimeOutCallBack(gs_UdsPrivateData.serviceId);

    return ;
}

/**************************************************************************//**
 *
 *  \details When the reprogram flag is valid, the RTE module call this
 *           function.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
void Adpt_ReprogramValidProcess(void)
{
    Dcm_StartS3Timer();

    Rte_SetMutexDownStatus(&g_DownContext,
                            DCM_STATUS_SESSION_PROGRAMMING,
                            DCM_SESSION_MASK);

    _Adpt_SendResponse((bl_BufferSize_t)sizeof(gs_ReprogrammingResponse),
                        gs_ReprogrammingResponse);

    return ;
}

/**************************************************************************//**
 *
 *  \details When the reset flag is valid, the RTE module call this function.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
void Adpt_SystemResetProcess(void)
{

//	Dcm_StartS3Timer();

    Rte_SetMutexDownStatus(&g_DownContext,
                            DCM_STATUS_SESSION_DEFAULT,
                            DCM_SESSION_MASK);  // uidp5359    set session mask

							
 //   _Adpt_SendResponse((bl_BufferSize_t)sizeof(gs_ResetResponse),
   //                     gs_ResetResponse);

    return ;
}


#if (RTE_FUN_STAY_IN_BOOT == BL_FUN_ON)
/**************************************************************************//**
 *
 *  \details When the application is valid and the stay in boot is enabled,
 *           the RTE module call this function.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
void Adpt_AppValidProcess(void)
{
    _Adpt_SendResponse((bl_BufferSize_t)sizeof(gs_StayInBootResponse),
                        gs_StayInBootResponse);

    return ;
}
#endif

#if(RTE_FUN_GATEWAY == BL_FUN_ON)
/**************************************************************************//**
 *
 *  \details Gateway transmits messages by id.
 *
 *  \param[in]  id  - service id.
 *
 *  \since  V5.0.0
 *
 *****************************************************************************/
static void _Adpt_UdsGatewayTransmit(bl_u8_t id)
{
    bl_u8_t i;
    bl_u16_t handle;
    bl_u16_t number;
    const bl_GatewayConversion_t *gateway;

    number = gs_UdsGatewayList.number;
    gateway = gs_UdsGatewayList.data;
    handle = gs_UdsGatewayList.handle;

    for(i = 0u; i < number; i++)
    {
        if(id == gateway[i].sid)
        {
            (void)Canif_Write(handle, gateway[i].size, gateway[i].data);
            break;
        }
    }

    return ;
}
#endif

/**************************************************************************//**
 *
 *  \details Send 0x78 negative response.
 *
 *  \param[in]  id  - service id.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
static void _Adpt_UdsPendingResponse(bl_u8_t id)
{
    bl_Buffer_t buffer[ADPT_UDS_MAX_CAN_FRAME_SIZE];

    buffer[ADPT_UDS_CAN_FRAME_INDEX_0] = DCM_NEGATIVE_RESPONSE_SIZE;
    buffer[ADPT_UDS_CAN_FRAME_INDEX_1] = DCM_NEGATIVE_RESPONSE_CODE;
    buffer[ADPT_UDS_CAN_FRAME_INDEX_2] = id;
    buffer[ADPT_UDS_CAN_FRAME_INDEX_3] =
                                DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING;
#if(CANTP_FUN_FRAME_PADDING == BL_FUN_ON)
    buffer[ADPT_UDS_CAN_FRAME_INDEX_4] = CANTP_FRAME_PADDING_VALUE;
    buffer[ADPT_UDS_CAN_FRAME_INDEX_5] = CANTP_FRAME_PADDING_VALUE;
    buffer[ADPT_UDS_CAN_FRAME_INDEX_6] = CANTP_FRAME_PADDING_VALUE;
    buffer[ADPT_UDS_CAN_FRAME_INDEX_7] = CANTP_FRAME_PADDING_VALUE;
#endif

    _Adpt_SendResponse((bl_BufferSize_t)sizeof(buffer), buffer);
	/*ccj. according to Geely Diagnostic Requirement Specification V3.2-20150709 Page 20*/
	Dcm_StopS3Timer();
    return ;
}

/**************************************************************************//**
 *
 *  \details Send a response by ComOps in the g_RteInfo. When the transmitter
 *           is activated, This function will wait for some time configurated
 *           by ADPT_UDS_TX_TIMEOUT. If the response is not send within this
 *           time, this function will still return.
 *
 *  \param[in]  size    - the size of buffer.
 *  \param[in]  buffer  - the data will be send.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
static void _Adpt_SendResponse(bl_BufferSize_t size, const bl_Buffer_t *buffer)
{
    bl_u32_t timeout = ADPT_UDS_TX_TIMEOUT;

    /*whether return value is necessary*/
    (void)Canif_Write(ADPT_UDS_TX_HANDLE, size, buffer);

    BL_WAITFOR_TIMEOUT(timeout,
                        Canif_IsWritten(ADPT_UDS_TX_HANDLE) == BL_ERR_OK)

    return ;
}
/**************************************************************************//**
 *
 *  \details Timeout callback of sending 0x78.
 *
 *  \param[in]  id  - service id.
 *
 *  \since  V2.0.0
 *
 *****************************************************************************/
static void _Adpt_TimeOutCallBack(bl_u8_t id)
{
    _Adpt_UdsPendingResponse(id);

#if(RTE_FUN_GATEWAY == BL_FUN_ON)
    _Adpt_UdsGatewayTransmit(ADPT_UDS_3E_SERVICE_ID);
#endif
}

/**************************************************************************//**
 *
 *  \details Set response info of session.
 *
 *  \param[out]  buffer  - the pointer of response data.
 *
 *  \return Return the size of response data.
 *
 *  \since  V4.0.0
 *
 *****************************************************************************/
static bl_BufferSize_t _Adpt_SetSessionResp(bl_Buffer_t *buffer)
{
    bl_BufferSize_t size;

    size = ADPT_SESSION_RESPONSE_LEN;

    buffer[ADPT_UDS_CAN_FRAME_INDEX_0] = ADPT_SESSION_RESPONSE0;
    buffer[ADPT_UDS_CAN_FRAME_INDEX_1] = ADPT_SESSION_RESPONSE1;
    buffer[ADPT_UDS_CAN_FRAME_INDEX_2] = ADPT_SESSION_RESPONSE2;
    buffer[ADPT_UDS_CAN_FRAME_INDEX_3] = ADPT_SESSION_RESPONSE3;

    return size;
}

/**************************************************************************//**
 *
 *  \details Go to the session
 *
 *  \param[in] sessionMask - the session will be gone.
 *
 *  \since  V5.0.0
 *
 *****************************************************************************/
static void _Adpt_UdsGotoSession(bl_DownStatus_t sessionMask)
{
    _Adpt_UdsClearDownInfo(&gs_UdsPrivateData);

#if (DCM_FUN_SECURITY_ACCESS == BL_FUN_ON)
    /*lock the level 1.*/
    Rte_SetMutexDownStatus(&g_DownContext,
                            DCM_STATUS_SECURITY_LOCK_1,
                            DCM_SECURITYACCESS_1_MASK);
#else
    /*unlock the level 1.*/
    Rte_SetMutexDownStatus(&g_DownContext,
                            DCM_STATUS_SECURITY_UNLOCK_1,
                            DCM_SECURITYACCESS_1_MASK);
#endif
    Rte_SetMutexDownStatus(&g_DownContext,
                            sessionMask,
                            DCM_SESSION_MASK);

    return ;
}

/**************************************************************************//**
 *
 *  \details Clear the download information.
 *
 *  \since  V5.1.0
 *
 *****************************************************************************/
static void _Adpt_UdsClearDownInfo(bl_AdapterData_t *adpt)
{
    adpt->address = 0;
    adpt->remainSize = 0;
    adpt->blockIndex = 0;

    Rte_ClearDownStatus(&g_DownContext, ADPT_UDS_SYSTEM_STATUS_MASK);
    Rte_ClearDownStatus(&g_DownContext, ADPT_UDS_STATUS_MASK);
    return ;
}
#if 0
/**************************************************************************//**
 *
 *  \details Reset the system.
 *
 *  \since  V5.1.0
 *
 *****************************************************************************/
static void _Adpt_UdsResetSystem(bl_u8_t sid, bl_u16_t flagId)
{
    bl_Return_t ret;

    ret = Dcm_IsSuspendedResponse();
    if (ret != BL_ERR_OK)
    {
        _Adpt_TimeOutCallBack(sid);
        /*write flag.*/
        (void)Dm_WriteDefaultData(flagId);
    }

    g_RteInfo.SystemReset();
}
#endif
/**************************************************************************//**
 *
 *  \details Callback of reset.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallBackReadBootSoftwareId(bl_BufferSize_t size,
                                       bl_Buffer_t *buffer,
                                       bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;
     
    (void)size;
    (void)buffer;
    ret = Dm_ReadData(4u,(bl_Size_t)16u, buffer);
    if(BL_ERR_OK != ret)
    {
        resCode = DCM_E_CONDITIONSNOTCORRECT;
    }
    else
    {
        *respSize = 16u;
    }

    return resCode;
}
/**************************************************************************//**
*
*  \details Callback of reset.
*
*  \param[in]	  size	   - the data size, not include id, subid and did.
*  \param[in/out] buffer   - the pointer of data.
*  \param[out]	  respSize - the size of response data.
*
*  \return Return response code.
*
*  \retval 0x00   - Positive response code.
*  \retval others - Negative response code.
*
*  \since  V3.0.0
*
* \Xiejieying
*****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallBackReadActiveDiagnosticSession(bl_BufferSize_t size,
									  bl_Buffer_t *buffer,
									  bl_BufferSize_t *respSize)
{
   bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
   bl_Return_t ret;
	
   (void)size;
   (void)buffer;
   
   buffer[0] = 0x02;
   *respSize = 1u;

    return resCode;

}									   
/**************************************************************************//**
 *
 *  \details Callback of reset.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallBackReadEcuHardwareNum(bl_BufferSize_t size,
                                       bl_Buffer_t *buffer,
                                       bl_BufferSize_t *respSize)
{
    bl_u8_t u8i,u8Defualt;

    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;        
    (void)size;
    (void)buffer;
  
    //FLS_u8WriteDataWait(0xFF207140UL,16u,TestBuffer);
 #if 0  
 bl_u8_t TestBuffer[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15},u8Aarry[16],u8Defualt = 0;

    FLS_u8ReadDataWait(0xFF207140UL,16u,u8Aarry);

    for(u8i = 0; u8i < 16u;u8i++)
    {
        TestBuffer[u8i] = buffer[u8i];

    }
    for(u8i = 0; u8i < 16u;u8i++)
    {
        if(buffer[u8i]==0xFFu)
        {
            u8Defualt = 1;/*True*/
            break;
        }
    }
#endif

#if 0
    ret = Dm_ReadData(3u,(bl_Size_t)16u, buffer);

    if((BL_ERR_OK != ret)||(u8Defualt == 1))/*modify by LT,20160612*/
    {
        resCode = DCM_E_CONDITIONSNOTCORRECT;

    }
    else
    {
        *respSize = 16u;
    }
#endif

    buffer[0] = 'A'+(HW_VERSION_INTERNAL>>12);
    buffer[1] = '0'+((HW_VERSION_INTERNAL>>8)&0xF);
    buffer[2] = '.';
    buffer[3] = '0'+((HW_VERSION_INTERNAL&0xFF)/10);
    buffer[4] = '0'+((HW_VERSION_INTERNAL&0xFF)%10);  
    
    for(u8i=5;u8i<16;u8i++)
    {
        buffer[u8i] = 0x20;
    }
    
    *respSize = 16u;
    return resCode;
}
/**************************************************************************//**
 *
 *  \details Callback of reset.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallBackReadEcuSoftwareNum(bl_BufferSize_t size,
                                       bl_Buffer_t *buffer,
                                       bl_BufferSize_t *respSize)
{
    bl_u8_t u8i,u8Defualt;

    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;        
    (void)size;
    (void)buffer;
	get_version=1;
  
	for(u8i=0;u8i<max_version_length;u8i++)
		buffer[u8i] = version[u8i];
  
    *respSize = max_version_length;
	return resCode;
}
/**************************************************************************//**
 *
 *  \details Callback of reset.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallBackReadPgrmCounter(bl_BufferSize_t size,
                                       bl_Buffer_t *buffer,
                                       bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;        
    (void)size;
    (void)buffer;

    ret = Dm_ReadData(ADPT_ProgrammingCounter_FLAGID,(bl_Size_t)4u, buffer);
    
    if(BL_ERR_OK != ret)
    {
        /*Read frome the dataflash,when the dataflash has been erase and not writeen once,use the default value,modify by LT,20160623*/
      //  buffer[0] = 0;
       // *respSize = 1u;
        resCode = DCM_E_CONDITIONSNOTCORRECT;
    }
    else
    {
        *respSize = 1u;
    }

    return resCode;
}
/**************************************************************************//**
 *
 *  \details Callback of reset.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallBackReadPgrmAttempCounter(bl_BufferSize_t size,
                                       bl_Buffer_t *buffer,
                                       bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;        
    (void)size;
    (void)buffer;

    ret = Dm_ReadData(ADPT_ProgrammingAttempCounter_FLAGID,(bl_Size_t)4u, buffer);
    if(BL_ERR_OK != ret)
    {
        /*Read frome the dataflash,when the dataflash has been erase and not writeen once,use the default value,modify by LT,20160623*/
       // buffer[0] = 0;
       // *respSize = 1u;
        resCode = DCM_E_CONDITIONSNOTCORRECT;
    }
    else
    {
        *respSize = 1u;
    }

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of reset.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallBackReadGeelySparePN(bl_BufferSize_t size,
                                       bl_Buffer_t *buffer,
                                       bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;        
    (void)size;
    (void)buffer;

    ret = Dm_ReadData(5u,(bl_Size_t)8u, buffer);
    if(BL_ERR_OK != ret)
    {
        resCode = DCM_E_CONDITIONSNOTCORRECT;
    }
    else
    {
        //*respSize = 16u;
        *respSize = 8u;/*FE-3Z*/
    }

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of reset.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallBackReadECUSwVersion(bl_BufferSize_t size,
                                       bl_Buffer_t *buffer,
                                       bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;        
    (void)size;
    (void)buffer;

    ret = Dm_ReadData(6u,(bl_Size_t)16u, buffer);
    if(BL_ERR_OK != ret)
    {
        resCode = DCM_E_CONDITIONSNOTCORRECT;
    }
    else
    {
        *respSize = 16u;
    }

    return resCode;
}


BOOL FDdriver_BlackCheck(U16 address,U8 length)
{
	r_fdl_request_t			req;
	BOOL bRet =FALSE;
		
	req.command_enu 	= R_FDL_CMD_BLANKCHECK;
	req.idx_u32 		= address;
	req.cnt_u16 		= length;  /* number of words*/
	req.accessType_enu	= R_FDL_ACCESS_USER;
	R_FDL_Execute( &req );
	while( R_FDL_BUSY == req.status_enu )
	{
		R_FDL_Handler();
	}
	if( R_FDL_OK == req.status_enu )
	{	
		bRet =TRUE;
	}
	else
	{
		/* Error handler */
	}
	  
	return bRet;
}

/**************************************************************************//**
 *
 *  \details Callback of reset.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
bl_ResponseCode_t Adpt_UdsCallBackReadTesterNumber(bl_BufferSize_t size,
                                       bl_Buffer_t *buffer,
                                       bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret; 
	U8 RET;
    bl_u8_t u8i;

    (void)size;
    (void)buffer;

	RET = FDdriver_BlackCheck(0xFF200140UL, 3);
	if(RET == TRUE)
	{
		 /*Read frome the dataflash,when the dataflash has been erase and not writeen once,use the default value,modify by LT,20160623*/
         /*empty, Null-0x00*/
		 for(u8i = 0; u8i < 10; u8i++)
         {
            buffer[u8i] = 0x00;
         }       
         *respSize = 10u;   
	}
	else
	{
		ret = Dm_ReadData(ADPT_TESTERNUMBER_FLAGID,(bl_Size_t)16u, buffer);
	    if(BL_ERR_OK != ret)
	    {
	        /*Read frome the dataflash,when the dataflash has been erase and not writeen once,use the default value,modify by LT,20160623*/
	        /*empty, Null-0x00*/
	         for(u8i = 0; u8i < 10; u8i++)
	         {
	            buffer[u8i] = 0x00;
	         }       
	    }
		*respSize = 10u;   
	}

    return resCode;
}

/**************************************************************************//**
 *
 *  \details Callback of reset.
 *
 *  \param[in]     size     - the data size, not include id, subid and did.
 *  \param[in/out] buffer   - the pointer of data.
 *  \param[out]    respSize - the size of response data.
 *
 *  \return Return response code.
 *
 *  \retval 0x00   - Positive response code.
 *  \retval others - Negative response code.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/

bl_ResponseCode_t Adpt_UdsCallBackReadProgramDate(bl_BufferSize_t size,
                                       bl_Buffer_t *buffer,
                                       bl_BufferSize_t *respSize)
{
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;        
	bl_Buffer_t invalue_arg[4] = {0xFF,0xFF,0xFF,0xFF};
    (void)size;
    (void)buffer;

    ret = Dm_ReadData(ADPT_PROGRAMMINGDATE_FLAGID,(bl_Size_t)4u, buffer);
    if(BL_ERR_OK != ret)
    {
        /*Read frome the dataflash,when the dataflash has been erase and not writeen once,use the default value,modify by LT,20160623*/
         buffer[0] = 0x00;
         buffer[1] = 0x00;
         buffer[2] = 0x00;
         buffer[3] = 0x00;        
         *respSize = 4u;        
        //resCode = DCM_E_CONDITIONSNOTCORRECT;
    }
    else
    {
    	if(memcmp(invalue_arg,buffer,4) == 0)
    	{
	     	buffer[0] = 0x00;
         	buffer[1] = 0x00;
         	buffer[2] = 0x00;
         	buffer[3] = 0x00; 
		}
        *respSize = 4u;
    }

    return resCode;
}


bl_ResponseCode_t Adpt_UdsCallBackReadIdentifierInformation(bl_BufferSize_t size,
									 bl_Buffer_t *buffer,
									 bl_BufferSize_t *respSize)
{
	bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;        
    (void)size;
    (void)buffer;

    ret = Dm_ReadData(ADPT_IdentifierInformation_FLAGID,(bl_Size_t)8u, buffer);
    if(BL_ERR_OK != ret)
    {
        resCode = DCM_E_CONDITIONSNOTCORRECT;
    }
    else
    {
        *respSize = 7u;
    }

    return resCode;	
}

bl_ResponseCode_t Adpt_UdsCallBackReadSGMWVIN(bl_BufferSize_t size,
									 bl_Buffer_t *buffer,
									 bl_BufferSize_t *respSize)
{
	bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;        
    (void)size;
    (void)buffer;

    ret = Dm_ReadData(ADPT_SGMWVIN_FLAGID,(bl_Size_t)20u, buffer);
    if(BL_ERR_OK != ret)
    {
        resCode = DCM_E_CONDITIONSNOTCORRECT;
    }
    else
    {
        *respSize = 17u;
    }

    return resCode;	
}
bl_ResponseCode_t Adpt_UdsCallBackReadHardwareNumber(bl_BufferSize_t size,
									 bl_Buffer_t *buffer,
									 bl_BufferSize_t *respSize)
{
	bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;        
    (void)size;
    (void)buffer;

    ret = Dm_ReadData(ADPT_HardwareNumber_FLAGID,(bl_Size_t)4u, buffer);
    if(BL_ERR_OK != ret)
    {
        resCode = DCM_E_CONDITIONSNOTCORRECT;
    }
    else
    {
        *respSize = 3u;
    }

    return resCode;	
}
bl_ResponseCode_t Adpt_UdsCallBackReadHardwareVersion(bl_BufferSize_t size,
									 bl_Buffer_t *buffer,
									 bl_BufferSize_t *respSize)
{
	bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;        
    (void)size;
    (void)buffer;

    ret = Dm_ReadData(ADPT_HardwareVersion_FLAGID,(bl_Size_t)16u, buffer);
    if(BL_ERR_OK != ret)
    {
        resCode = DCM_E_CONDITIONSNOTCORRECT;
    }
    else
    {
        *respSize = 16u;
    }

    return resCode;
}
bl_ResponseCode_t Adpt_UdsCallBackReadSoftwareNumber(bl_BufferSize_t size,
									 bl_Buffer_t *buffer,
									 bl_BufferSize_t *respSize)
{
	bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;        
    (void)size;
    (void)buffer;

    ret = Dm_ReadData(ADPT_SoftwareNumber_FLAGID,(bl_Size_t)4u, buffer);
    if(BL_ERR_OK != ret)
    {
        resCode = DCM_E_CONDITIONSNOTCORRECT;
    }
    else
    {
        *respSize = 3u;
    }

    return resCode;
}
bl_ResponseCode_t Adpt_UdsCallBackReadSoftwareVersion(bl_BufferSize_t size,
									 bl_Buffer_t *buffer,
									 bl_BufferSize_t *respSize)
{
	bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;        
    (void)size;
    (void)buffer;

    ret = Dm_ReadData(ADPT_SoftwareVersion_FLAGID,(bl_Size_t)16u, buffer);
    if(BL_ERR_OK != ret)
    {
        resCode = DCM_E_CONDITIONSNOTCORRECT;
    }
    else
    {
        *respSize = 16u;
    }

    return resCode;
}
bl_ResponseCode_t Adpt_UdsCallBackReadCalibrationDataNumberInformation(bl_BufferSize_t size,
									 bl_Buffer_t *buffer,
									 bl_BufferSize_t *respSize)
{
	bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;        
    (void)size;
    (void)buffer;

    ret = Dm_ReadData(ADPT_CalibrationDataNumber_FLAGID,(bl_Size_t)4u, buffer);
    if(BL_ERR_OK != ret)
    {
        resCode = DCM_E_CONDITIONSNOTCORRECT;
    }
    else
    {
        *respSize = 16u;
    }

    return resCode;
}
bl_ResponseCode_t Adpt_UdsCallBackReadComponentAssemblyNumber(bl_BufferSize_t size,
									 bl_Buffer_t *buffer,
									 bl_BufferSize_t *respSize)
{
	bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
    bl_Return_t ret;        
    (void)size;
    (void)buffer;

    ret = Dm_ReadData(ADPT_ComponentAssembly_FLAGID,(bl_Size_t)4u, buffer);
    if(BL_ERR_OK != ret)
    {
        resCode = DCM_E_CONDITIONSNOTCORRECT;
    }
    else
    {
        *respSize = 4u;
    }

    return resCode;
}



void timer_for_1101reset_handle(void)
{
	   if(delay_to_execute_1101reset>0)//open time
	   {
	   	   Wdg_Feed();
		   delay_to_execute_1101reset--;
		   if((delay_to_execute_1101reset%4000)==0)
		   {
			   _Adpt_UdsPendingResponse(0x11);
		   }
		   if(delay_to_execute_1101reset==100)
		   {
		   	   if(!SuspendedResponse_flag)
		   	   {
			  		 _Adpt_SendResponse((bl_BufferSize_t)sizeof(gs_ResetResponse),
							   gs_ResetResponse);
		   	   }
			   SuspendedResponse_flag = FALSE ;
			  Sys_Reset();
		   }
	   }

}




void set_1101reset_timer(unsigned int timer)
{
	delay_to_execute_1101reset = timer;
	_Adpt_UdsPendingResponse(0x11);
}

void PgrmCounter()
{
	bl_Return_t ret;
	bl_u8_t counter[4];
    ret = Dm_ReadData(ADPT_ProgrammingCounter_FLAGID,(bl_Size_t)4u, counter);
    if(BL_ERR_OK == ret)
    {
        if(counter[0]==255)
        {
			counter[0] = 0;
		}
		else
		{
			if(diff_data_for_soc == 1)
			{
				if((updating_mcu_success)&&(updating_soc_success))
				{
					counter[0]++;
				}
			}
			else
			{
				if(updating_mcu_success)
				{
					counter[0]++;
				}
			}			    
		}
    }
	Dm_WriteData(ADPT_ProgrammingCounter_FLAGID, (bl_Size_t)4, counter);
	
}

void PgrmAttempCounter()
{
    bl_Return_t ret;
	bl_u8_t counter[4];
    ret = Dm_ReadData(ADPT_ProgrammingAttempCounter_FLAGID,(bl_Size_t)4u, counter);
    if(BL_ERR_OK == ret)
    {
        if(counter[0]==255)
        {
			counter[0] = 0;
		}
		else
		{
			counter[0]++;
		}
 
    }
	 Dm_WriteData(ADPT_ProgrammingAttempCounter_FLAGID, (bl_Size_t)4, counter);

}



									   

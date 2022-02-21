/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of the DCM module.
 *
 *  \file       bl_dcm.c
 *  \ingroup    communication_protocol_stack_module
 *  \author     heli.zhang <heli.zhang@hirain.com>
 *              mingqing.tang <mingqing.tang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *c
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      01.00.00 | 08/04/2010 | hewei.zhang      | N/A | Boot010001
 *      01.02.00 | 19/04/2010 | hewei.zhang      | N/A | Boot010003
 *      01.04.00 | 06/05/2010 | hewei.zhang      | N/A | Boot010005
 *      02.00.00 | 18/03/2011 | mingqing.tang    | N/A | Boot020001
 *      02.01.00 | 31/03/2011 | mingqing.tang    | N/A | Boot020002
 *      02.03.00 | 07/04/2011 | mingqing.tang    | N/A | Boot020004
 *      03.00.00 | 12/09/2011 | mingqing.tang    | N/A | Boot030001
 *      03.05.00 | 11/10/2011 | mingqing.tang    | N/A | Boot030006
 *      03.06.00 | 26/10/2011 | mingqing.tang    | N/A | Boot030007
 *      04.00.00 | 02/01/2012 | mingqing.tang    | N/A | Boot040001
 *      04.02.00 | 16/01/2012 | mingqing.tang    | N/A | Boot040003
 *      04.08.00 | 04/04/2012 | mingqing.tang    | N/A | Boot040009
 *      05.00.00 | 19/06/2013 | heli.zhang       | N/A | Boot050001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#include "bl_common.h"
#include "bl_rte.h"
#include "bl_dcm.h"
#include "bl_dcm_cfg.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 506,597,602,771,781,1251,1257,1531,1532,2100,2103,2201,3112,3204 EOF*/
/*PRQA S 3211,3212,3227,3453 EOF*/
/*
 * 506:Dereferencing pointer value that is possibly NULL.
 *
 * 597:Type of 'case' label expression is not consistent with type of switch
 * control expression.
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
 * 1251:Suffixed integer constant causes implicit conversion of other
 * (integral) operand.
 *
 * 1257:Suffixed integer constant implicitly converted to smaller integer type
 * on assignment.
 *
 * 1531:The object is referenced in only one translation unit.
 *
 * 1532:The function is only referenced in one translation unit.
 * all functions in this file are configurations in the Security Module.
 *
 * 2100:Integral promotion : unsigned char promoted to signed int.
 *
 * 2103:Integral promotion, unsigned short promoted to unsigned int.
 * This message will therefore only be generated when a short and an int are of
 * equal size.
 *
 * 2201:This indentation is not consistent with previous indentation.
 *
 * MISRA-C:2004 14.2(3112):This statement has no side-effect.
 * The DEBUG_ASSERT macro is used to debug bootloader when the BL_DEBUG is
 * enable. When the BL_DEBUG is disable, the DEBUG_ASSERT macro is null.
 *
 * 3204:The variable is only set once and so it could be declared with the
 * 'const' qualifier.
 *
 * 3211:The global identifier is defined but not used.
 *
 * 3212:This explicit cast is redundant and could be removed.
 * BL_BE16_TO_MCU is not explicit cast.
 *
 * 3227:The parameter is never modified and so it could be declared with const.
 *
 * MISRA-C:2004 19.7(3453):A function could probably be used instead of this
 * function-like macro.
 *
 */

/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/
/** \brief The service Id type.*/
#define DCM_TYPE_SERVICE_ID                 (0x0001u)
#define DCM_TYPE_SERVICE_SUBID              (0x0002u)
#define DCM_TYPE_SERVICE_DID                (0x0003u)

#define DCM_SERVICE_ID_MASK                 (0x00FFu)
#define DCM_SUB_SERVICE_ID_MASK             (0x007Fu)

#define DCM_SERVICE_ID_SIZE                 (0x01u)
#define DCM_SERVICE_SUBID_SIZE              (0x01u)
#define DCM_SERVICE_DID_SIZE                (0x02u)

#define DCM_POSITIVE_RESPONSE_CODE          (0x40u)
#define DCM_SUPPRESSPOSRSPMSGINDICATIONBITMASK  (0x80u)

#define DCM_SUSPEND_POSITIVE_RESPONSE() (gs_SupPosRespFlag = 1)
#define DCM_ALLOW_POSITIVE_RESPONSE()   (gs_SupPosRespFlag = 0)
#define DCM_IS_NOT_SUSPENDED_RESPONSE() (0u == gs_SupPosRespFlag)

#define DCM_SET_S3TIMER(x)          (gs_DcmS3Timer = (x))
#define DCM_DEC_S3TIMER()           (gs_DcmS3Timer--)
#define DCM_IS_NOT_S3TIMEOUT()      (gs_DcmS3Timer != 0u)

#define DCM_GET_S3TIMERSWITCH()     (gs_DcmS3TimerStartFlag)
#define DCM_START_S3TIMER()         (gs_DcmS3TimerStartFlag = 1)
#define DCM_STOP_S3TIMER()          (gs_DcmS3TimerStartFlag = 0)
#define DCM_IS_STARTED_S3TIMER()    (1u == gs_DcmS3TimerStartFlag)

#define DCM_BUFFER_IS_UNLOCK()      (g_DcmBuffer.status \
                                        == DCM_STATUS_BUFFER_UNLOCK)
#define DCM_BUFFER_IS_RECV_LOCK()   ((g_DcmBuffer.status \
                                        & DCM_STATUS_BUFFER_RECV_LOCK) != 0u)
#define DCM_BUFFER_IS_PROC_LOCK()   ((g_DcmBuffer.status \
                                        & DCM_STATUS_BUFFER_PROC_LOCK) != 0u)
#define DCM_BUFFER_IS_SEND_LOCK()   ((g_DcmBuffer.status \
                                        & DCM_STATUS_BUFFER_SEND_LOCK) != 0u)
#define DCM_BUFFER_SET_RECV_LOCK()  (g_DcmBuffer.status \
                                        = DCM_STATUS_BUFFER_RECV_LOCK)
#define DCM_BUFFER_SET_PROC_LOCK()  (g_DcmBuffer.status \
                                        = DCM_STATUS_BUFFER_PROC_LOCK)
#define DCM_BUFFER_SET_SEND_LOCK()  (g_DcmBuffer.status \
                                        = DCM_STATUS_BUFFER_SEND_LOCK)
#define DCM_BUFFER_SET_UNLOCK()     (g_DcmBuffer.status \
                                        = DCM_STATUS_BUFFER_UNLOCK)

/*****************************************************************************
 *  Internal Type Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/
/** \brief Make service id.*/
static bl_BufferSize_t _Dcm_MakeSid(const bl_Buffer_t *buffer, bl_u16_t *id);
/** \brief Make subfunction id.*/
static bl_BufferSize_t _Dcm_MakeSubId(const bl_Buffer_t *buffer, bl_u16_t *id);
/** \brief Make data identifier id.*/
static bl_BufferSize_t _Dcm_MakeDid(const bl_Buffer_t *buffer, bl_u16_t *id);
/** \brief Handle response.*/
static void _Dcm_Response(bl_ResponseCode_t resCode,
                            bl_BufferSize_t resSize,
                            bl_DcmBuffer_t *dcmBuffer);
/** \brief Handle response, including positive or no response.*/
static void _Dcm_PosResponse(bl_BufferSize_t resSize,
                                bl_DcmBuffer_t *dcmBuffer);
/** \brief Handle negative response.*/
static void _Dcm_NegResponse(bl_ResponseCode_t resCode,
                                bl_DcmBuffer_t *dcmBuffer);
/** \brief Check whether downstatus is matched with fun/phy flag.*/
static bl_Return_t _Dcm_CheckRequestFlag(bl_u32_t flag);
/** \brief Check whether service id is supported in current session.*/
static bl_Return_t _Dcm_CheckSessionFlag(bl_u32_t flag);
/** \brief Check whether downstatus is matched with security access flag.*/
static bl_Return_t _Dcm_CheckSecAccFlag(bl_u32_t flag);
/** \brief Get servicelist pointer by id.*/
static const bl_DcmService_t *_Dcm_LookUpTable(bl_u16_t id,
                                                bl_u16_t number,
                                                const bl_DcmService_t *list);
/** \brief Check whether it is non-default session. if true, reset S3timer.*/
static void _Dcm_ResetS3Timer(void);
/** \brief Main function.*/
static void _Dcm_MainFunction(void);

/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/
/** \brief Suppress positive response flag.*/
static bl_u8_t gs_SupPosRespFlag;
/** \brief S3 timer variable.*/
static bl_u16_t gs_DcmS3Timer;
/** \brief S3 timer start flag.*/
static bl_u8_t gs_DcmS3TimerStartFlag;

/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/
/** \details The service header of dcm module.*/
const bl_DcmServiceHeader_t g_DcmServiceHeader =
{
    DCM_TYPE_SERVICE_ID, 0x11u,0x7Fu,&_Dcm_MakeSid
};
/** \details The subid header of service.*/
const bl_DcmServiceHeader_t g_DcmSubIdHeader =
{
    DCM_TYPE_SERVICE_SUBID, 0x12u,0x7Eu, &_Dcm_MakeSubId,
};

/**  \details The did header of service.*/
const bl_DcmServiceHeader_t g_DcmDidHeader =
{
    DCM_TYPE_SERVICE_DID, 0x31u,0x22u, &_Dcm_MakeDid,
};

/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/
/**************************************************************************//**
 *
 *  \details Initialize the variables of dcm module, such as P2timer, S3timer
 *           functional request flag.
 *
 *  \note This function is called by function Adpt_UdsInit.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
void Dcm_Init(void)
{
    DCM_ALLOW_POSITIVE_RESPONSE();
    DCM_STOP_S3TIMER();

    return ;
}

/**************************************************************************//**
 *
 *  \details Mainfunction of the dcm module. This function handles all service
 *           request of tester, including executing operation and responsing.
 *
 *  \note This function need to be called periodically.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
void Dcm_MainFunction(void)
{
    /*only buffer status is proc_lock, bootloader handles the request.*/
    if(DCM_BUFFER_IS_PROC_LOCK())
    {
        _Dcm_MainFunction();
    }
}

/**************************************************************************//**
 *
 *  \details Timerfunction of the dcm module. This function mainly handles time
 *           parameters. When S3timer timeout, the system will reset.
 *
 *  \note This function need to be called periodically.
 *
 *  \since  V2.0.0
 *
 *****************************************************************************/
void Dcm_TimerFunction(void)
{
    if(DCM_IS_STARTED_S3TIMER())
    {
        if(DCM_IS_NOT_S3TIMEOUT())
        {
            DCM_DEC_S3TIMER();
        }
        else
        {
            Rte_ReportEvent(RTE_EVENT_TYPE_S3TIME_TIMEOUT);
        }
    }

    return ;
}

/**************************************************************************//**
 *
 *  \details Start reception. This function is a callback, provided to CanTp.
 *
 *  \param[in]  size  - the size of received message.
 *
 *  \return Return whether buffer is available.
 *
 *  \retval BL_ERR_OK               - Request buffer successfully.
 *  \retval BL_ERR_BUFFER_BUSY      - The request buffer is using.
 *  \retval BL_ERR_BUFFER_OVERFLOW  - The size of message exceeds MAX size.
 *
 *  \note Only buffer is unlock, reception can be started.
 *
 *  \since  V2.0.0
 *
 *****************************************************************************/
bl_Return_t Dcm_StartOfReception(bl_BufferSize_t size)
{
    bl_Return_t ret = BL_ERR_OK;

    /*check whether buffer is unlock.*/
    if(DCM_BUFFER_IS_UNLOCK())
    {
        /*check whether buffer will overflow. */
        if(size > g_DcmBuffer.totalSize)
        {
            ret = BL_ERR_BUFFER_OVERFLOW;
        }
        else
        {
            g_DcmBuffer.index = 0;
            g_DcmBuffer.recvSize = size;
            DCM_BUFFER_SET_RECV_LOCK();

            /*Stop S3timer.*/
            DCM_STOP_S3TIMER();
        }
    }
    else
    {
        ret = BL_ERR_BUFFER_BUSY;
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Copy received data to buffer. This function is a callback,
 *           provided to CanTp.
 *
 *  \param[in]  size    - the size of the received data.
 *  \param[in]  data    - the contents of the received data.
 *
 *  \return Return whether buffer is available.
 *
 *  \retval BL_ERR_OK       - successfully copy the data to the buffer.
 *  \retval BL_ERR_NOT_OK   - The request buffer is not locked by receiving.
 *
 *  \note Only buffer is recv_lock, copy can be started.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
bl_Return_t Dcm_CopyRxData(bl_BufferSize_t size,const bl_Buffer_t *data)
{
    bl_Return_t ret = BL_ERR_OK;
    bl_u16_t index = g_DcmBuffer.index;

    /*check whether buffer is recv_lock.*/
    if(DCM_BUFFER_IS_RECV_LOCK())
    {
        Bl_MemCpy(&g_DcmBuffer.buffer[index], data, (bl_Size_t)size);

        g_DcmBuffer.index += size;

        BL_DEBUG_ASSERT(g_DcmBuffer.index <= g_DcmBuffer.recvSize);
    }
    else
    {
        ret = BL_ERR_NOT_OK;
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Indicate received result to the upper. This function is a
 *           callback, provided to CanTp.
 *
 *  \param[in]  taType  - the request type.
 *  \param[in]  result  - the result of reception.
 *
 *  \note If result is OK, it's needed to set proc_lock.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
void Dcm_RxIndication(bl_u8_t taType, bl_CanTpResult_t result)
{
    if(result == BL_ERR_OK)
    {
        /*check request type, functional or physical.*/
        switch (taType)
        {
            case CANTP_TATYPE_PHYSICAL:
                /*set physical request status.*/
                Rte_SetMutexDownStatus(&g_DownContext,
                                        DCM_STATUS_PHYSICAL_REQUEST,
                                        DCM_FUNANDPHY_MASK);
                break;
            case CANTP_TATYPE_FUNCTIONAL :
                /*set functional request status.*/
                Rte_SetMutexDownStatus(&g_DownContext,
                                        DCM_STATUS_FUNCTION_REQUEST,
                                        DCM_FUNANDPHY_MASK);

                break;
            default:
                break;
        }

        /*clear buffer index.*/
        g_DcmBuffer.index = 0;
        /*set buffer proc_lock.*/
        DCM_BUFFER_SET_PROC_LOCK();
        /*Notify the RTE module when a request was received.*/
        Rte_ReportEvent(RTE_EVENT_TYPE_RECV_REQUEST);
    }
    else
    {
        g_DcmBuffer.index = 0;
        /*set buffer unlock.*/
        DCM_BUFFER_SET_UNLOCK();
        /*check session to decide whether reset S3timer.*/
        _Dcm_ResetS3Timer();
    }

    return ;
}

/**************************************************************************//**
 *
 *  \details Copy transmittied data. This function is a callback,
 *           provided to CanTp.
 *
 *  \param[in]  handle  - indicates which buffer is used.
 *  \param[in]  pdu     - the pointer of transmitted frame.
 *
 *  \return Return whether buffer is available.
 *
 *  \retval BL_ERR_OK       - Successfully copy data from the buffer of Dcm.
 *  \retval BL_ERR_NOT_OK   - The buffer is not locked by transmitting.
 *
 *  \note Only buffer is send_lock, copy can be started.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
bl_Return_t Dcm_CopyTxData(bl_BufferSize_t size, bl_Buffer_t *data)
{
    bl_Return_t ret = BL_ERR_OK;
    bl_u16_t index = g_DcmBuffer.index;

    /*check whether buffer is send_lock.*/
    if(DCM_BUFFER_IS_SEND_LOCK())
    {
        Bl_MemCpy(data,&g_DcmBuffer.buffer[index],(bl_Size_t)size);

        g_DcmBuffer.index += size;

        BL_DEBUG_ASSERT(g_DcmBuffer.index <= g_DcmBuffer.tranSize);
    }
    else
    {
        ret = BL_ERR_NOT_OK;
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Confirm transmitting result to the upper. This function is a
 *           callback, provided to CanTp.
 *
 *  \param[in]  result  - the result of transmission.
 *
 *  \note It's needed to set buffer unlock.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
void Dcm_TxConfirmation(bl_CanTpResult_t result)
{
    (void)result;

    /*clear buffer index.*/
    g_DcmBuffer.index = 0x00u;
    /*set buffer unlock.*/
    DCM_BUFFER_SET_UNLOCK();
    /*check session to decide whether reset S3timer.*/
    _Dcm_ResetS3Timer();
}

/**************************************************************************//**
 *
 *  \details Start the S3 timer.
 *
 *  \since  V5.1.0
 *
 *****************************************************************************/
void Dcm_StartS3Timer(void)
{
    /*set S3timer value.*/
    DCM_SET_S3TIMER(DCM_S3TIMERVALUE);
    /*start S3timer.*/
    DCM_START_S3TIMER();
}

/**************************************************************************//**
 *
 *  \details Stop the S3 timer
 *
 *  \since  V5.1.0
 *
 *****************************************************************************/
void Dcm_StopS3Timer(void)
{
    DCM_STOP_S3TIMER();
}

/**************************************************************************//**
 *
 *  \details Check whether the response is suspended.
 *
 *  \retval BL_ERR_OK       - The response is suspended.
 *  \retval BL_ERR_NOT_OK   - The response is not suspended.
 *
 *  \since  V5.1.0
 *
 *****************************************************************************/
bl_Return_t Dcm_IsSuspendedResponse(void)
{
    bl_Return_t ret = BL_ERR_OK;

    if (DCM_IS_NOT_SUSPENDED_RESPONSE())
    {
        ret = BL_ERR_NOT_OK;
    }

    return ret;
}
/**************************************************************************//**
 *
 *  \details Mainfunction of the dcm module. This function handles all service
 *           request of tester, including executing operation and responsing.
 *
 *  \since  V5.1.0
 *
 *****************************************************************************/
static void _Dcm_MainFunction(void)
{
    bl_Return_t ret;
    bl_u16_t id = 0;
	bl_u16_t myid = 0;
    bl_BufferSize_t size;
    bl_BufferSize_t respSize = 0;
    bl_BufferSize_t sumSize = 0;
    bl_BufferSize_t recvSize = g_DcmBuffer.recvSize;
    bl_Buffer_t *buffer = g_DcmBuffer.buffer;
    bl_ResponseCode_t resCode = DCM_E_POSITIVERESPONSE;
	
    const bl_DcmServiceHeader_t *header;
    const bl_DcmService_t *list = &g_DcmServiceList;
	const bl_DcmService_t *mylist = BL_NULL_PTR;
	
	bl_Return_t max_length_flag  =BL_ERR_OK;
	bl_u8_t DcmId = 0;
	bl_u16_t i = 0;

	bl_u8_t flag = 0;
    do
    {
		/*The first time check the g_DcmServiceHeader function,LT mark,20160623*/
        /*The second time check the g_DcmSubIdHeader or g_DcmDidHeader function,LT mark,20160623*/
        header = list->header;
        /*make id according to type.*/
        size = header->MakeId(&buffer[sumSize], &id);
        sumSize += size;

        /*Get servicelist pointer by id.*/
        list = _Dcm_LookUpTable(id, list->number, list->serviceList);
		
		if(id==0x31) 
			flag = 1;
		if((i==1)&&(flag))
		{
			flag = 0;
			_Dcm_MakeDid(&buffer[2],&myid);
			if((myid!=0xFF00u)&&(myid!=0xFF01u)&&(myid!=0x0202u))
			{
				resCode = DCM_E_REQUESTOUTOFRANGE;
				break;
			}
		}
		
		/*The first time check  the service ID, if not support, Negetive = 0x11,LT mark,20160623*/
        /*The sendcond time check check the SubId or DID, if not support, Negetive = 0x12,0x31*/      
        if(BL_NULL_PTR == list)
        {
			if((i==1)&&(max_length_flag==BL_ERR_NOT_OK))
			{
				resCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
				max_length_flag = BL_ERR_OK;
			}
			else
			{
			    resCode = header->resCode;
				ret = _Dcm_CheckSecAccFlag(list->flag);
	        	if(ret != BL_ERR_OK)
	       		{
	            	resCode = DCM_E_SECURITYACCESSDENIED;
					//max_length_flag = BL_ERR_OK;
					//break;
	        	}	
				max_length_flag = BL_ERR_OK;
			}
			break;
        }

		if(i==1)
		{
			if(max_length_flag==BL_ERR_NOT_OK)
			{
					resCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
					max_length_flag = BL_ERR_OK;
					break;
			}
		}
		
		/*check whether downstatus is matched with fun/phy flag.*/
		ret = _Dcm_CheckRequestFlag(list->flag);
		if(ret != BL_ERR_OK)
		{
			  resCode = header->resCode;
			  break;
		}

		if((0u != list->minSize) && (recvSize < list->minSize))
		{
			/*check whether the size of received data is matched with minSize.*/
			//resCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
			//break;
			max_length_flag=BL_ERR_NOT_OK;
		}

		if((0u != list->maxSize) && (recvSize > list->maxSize))
		{
			/*check whether the size of received data is matched with maxSize.*/
		//	resCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
		//	break;
			max_length_flag=BL_ERR_NOT_OK;
		}

		if(i==1)
		{
			if((0u != list->maxSize) && (recvSize > list->maxSize))
			{
				//check whether the size of received data is matched with maxSize.
			//	resCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
			//	break;
				max_length_flag=BL_ERR_NOT_OK;
			}
		}

        /*The first time check  whether service is supported in current session.Negetive = 0x7F*/
        /*The second time check  whether SubID or DID is supported in current session.Negetive = 0x7E,0x22*/       
        ret = _Dcm_CheckSessionFlag(list->flag);
        if(ret != BL_ERR_OK)
        {
            resCode = header->sessionResCode;
			max_length_flag = BL_ERR_OK;
            break;
        }

		/* RequestDownload/RequestTransferExit/RoutineControl */
		if((id == 0x34)||(id == 0x37)||(id == 0x36)||(id == 0x31))
		{
			ret = _Dcm_CheckSecAccFlag(list->flag);
        	if(ret != BL_ERR_OK)
       		{
            	resCode = DCM_E_SECURITYACCESSDENIED;
				//max_length_flag = BL_ERR_OK;
				if(id==0x31)
				{
					_Dcm_MakeDid(&buffer[2],&myid);
					if((myid!=0xFF00u)&&(myid!=0xFF01u)&&(myid!=0x0202u))
					{
						resCode = DCM_E_REQUESTOUTOFRANGE;
					}
				}
				break;
        	}	
		}

		if(id == 0x2E)
		{
			ret = _Dcm_CheckSecAccFlag(list->flag);
			if(ret != BL_ERR_OK)
			{
				resCode = DCM_E_SECURITYACCESSDENIED;
				_Dcm_MakeDid(&buffer[1],&myid);
				if((myid!=0xF198u)&&(myid!=0xF199u))
				{
					resCode = DCM_E_REQUESTOUTOFRANGE;
					break;
				}	
			}
		}

		if((i == 1)&&(id == 0x31))
		{
        	/*check whether downstatus is matched with security access flag.Negetive = 0x33*/
       		ret = _Dcm_CheckSecAccFlag(list->flag);
        	if(ret != BL_ERR_OK)
       		{
            	resCode = DCM_E_SECURITYACCESSDENIED;
				//max_length_flag = BL_ERR_OK;
				break;
        	}	
		}
		i++;
    }while(BL_NULL_PTR != list->serviceList);

	if(max_length_flag==BL_ERR_NOT_OK)
	{
		resCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
	}

    if ((DCM_E_POSITIVERESPONSE == resCode)
        && (list != BL_NULL_PTR))
    {
        /*if callback is null, the system will reset.*/
        BL_DEBUG_ASSERT_NO_RET(BL_NULL_PTR != list->Callback);
        /*running the callback function.*/
        resCode = list->Callback((recvSize - sumSize), &buffer[sumSize],
                                    &respSize);
    }

    /*transmit corresponding response.*/
    _Dcm_Response(resCode, respSize + sumSize, &g_DcmBuffer);

    return ;
}

/**************************************************************************//**
 *
 *  \details Make service id.
 *
 *  \param[in]  buffer  - the pointer of data.
 *  \param[out] id      - the pointer of id.
 *
 *  \return Return the used buffer size.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
static bl_BufferSize_t _Dcm_MakeSid(const bl_Buffer_t *buffer, bl_u16_t *id)
{
    *id = (bl_u16_t)(buffer[0] & DCM_SERVICE_ID_MASK);

    return DCM_SERVICE_ID_SIZE;
}

/**************************************************************************//**
 *
 *  \details Make sunfunction id.
 *
 *  \param[in]  buffer  - the pointer of data.
 *  \param[out] id      - the pointer of id.
 *
 *  \return Return the used buffer size.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
static bl_BufferSize_t _Dcm_MakeSubId(const bl_Buffer_t *buffer, bl_u16_t *id)
{
    /*check whether positive response is forbidden.*/
    if((buffer[0] & DCM_SUPPRESSPOSRSPMSGINDICATIONBITMASK) != 0u)
    {
        DCM_SUSPEND_POSITIVE_RESPONSE();
    }
    else
    {
        DCM_ALLOW_POSITIVE_RESPONSE();
    }

    *id = (bl_u16_t)(buffer[0] & DCM_SUB_SERVICE_ID_MASK);

    return DCM_SERVICE_SUBID_SIZE;
}

/**************************************************************************//**
 *
 *  \details Make data identifier id.
 *
 *  \param[in]  buffer  - the pointer of data.
 *  \param[out] id      - the pointer of id.
 *
 *  \return Return the used buffer size.
 *
 *  \since  V3.0.0
 *
 *****************************************************************************/
static bl_BufferSize_t _Dcm_MakeDid(const bl_Buffer_t *buffer, bl_u16_t *id)
{
    *id = BL_BE16_TO_MCU(buffer);

    return DCM_SERVICE_DID_SIZE;
}

/**************************************************************************//**
 *
 *  \details Handle response, decide whether transmit negative or positive
 *           response, or no response.
 *
 *  \param[in]  resCode   - indicates respond result.
 *  \param[in]  resSize   - the response size.
 *  \param[in]  dcmBuffer - the pointer of dcmbuffer.
 *
 *  \note Transmit response by CanTp.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
static void _Dcm_Response(bl_ResponseCode_t resCode,
                            bl_BufferSize_t resSize,
                            bl_DcmBuffer_t *dcmBuffer)
{
    /*check whether response code is negative.*/
    if(DCM_E_POSITIVERESPONSE == resCode)
    {
        _Dcm_PosResponse(resSize, dcmBuffer);
    }
    else
    {
        _Dcm_NegResponse(resCode, dcmBuffer);
    }

    DCM_ALLOW_POSITIVE_RESPONSE();
    return ;
}

/**************************************************************************//**
 *
 *  \details Handle response, decide whether transmit positive
 *           response, or no response.
 *
 *  \param[in]  resSize   - the response size.
 *  \param[in]  dcmBuffer - the pointer of dcmbuffer.
 *
 *  \note Transmit response by CanTp.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
static void _Dcm_PosResponse(bl_BufferSize_t resSize,
                                bl_DcmBuffer_t *dcmBuffer)
{
    bl_Return_t ret = BL_ERR_NOT_OK;

    if(DCM_IS_NOT_SUSPENDED_RESPONSE() && (resSize <= dcmBuffer->totalSize))
    {
        dcmBuffer->tranSize = resSize;
        dcmBuffer->buffer[0] += DCM_POSITIVE_RESPONSE_CODE;
        /*set buffer send_lock.*/
        DCM_BUFFER_SET_SEND_LOCK();
        /*transmit positive response.*/
        ret = Cantp_Transmit(DCM_TX_HANDLE, resSize);
    }

    if (ret != BL_ERR_OK)
    {
        DCM_BUFFER_SET_UNLOCK();
        /*check session to decide whether reset S3timer.*/
        _Dcm_ResetS3Timer();
    }
}

/**************************************************************************//**
 *
 *  \details Handle negative response.
 *
 *  \param[in]  resCode   - indicates respond result.
 *  \param[in]  dcmBuffer - the pointer of dcmbuffer.
 *
 *  \note Transmit response by CanTp.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
static void _Dcm_NegResponse(bl_ResponseCode_t resCode,
                                bl_DcmBuffer_t *dcmBuffer)
{
    bl_Return_t ret;
    bl_BufferSize_t size = DCM_NEGATIVE_RESPONSE_SIZE;
    bl_Buffer_t serviceId;

    /*check whether request is functional.*/
    ret = Rte_IsValidStatus(&g_DownContext, DCM_FUNCTIONAL_MASK);
    if((BL_ERR_OK != ret)
        || ((DCM_E_SERVICENOTSUPPORTED != resCode)
        && (DCM_E_SUBFUNCTIONNOTSUPPORTED != resCode)
        && (DCM_E_REQUESTOUTOFRANGE != resCode)
        && (DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION != resCode)
        && (DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION != resCode)))
    {
        dcmBuffer->tranSize = size;
        serviceId = dcmBuffer->buffer[0];
        dcmBuffer->buffer[0] = DCM_NEGATIVE_RESPONSE_CODE;
        dcmBuffer->buffer[DCM_NEGATIVE_RESPONSE_ID_POS] = serviceId;
        dcmBuffer->buffer[DCM_NEGATIVE_RESPONSE_NRC_POS] = resCode;
        /*set buffer send_lock.*/
        DCM_BUFFER_SET_SEND_LOCK();

        /*transmit negative response.*/
        ret = Cantp_Transmit(DCM_TX_HANDLE, size);
        if (BL_ERR_OK != ret)
        {
            DCM_BUFFER_SET_UNLOCK();
        }
    }
    else
    {
        DCM_BUFFER_SET_UNLOCK();
    }

    return ;
}

/**************************************************************************//**
 *
 *  \details Check whether downstatus is matched with fun/phy flag.
 *
 *  \param[in]  flag - The configuration of basic check.
 *
 *  \return If the service is supported in current addressing returns
 *          BL_ERR_OK, otherwise returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK       - the service is supported.
 *  \retval BL_ERR_NOT_OK   - the service is NOT supported.
 *
 *  \since  V2.0.0
 *
 *****************************************************************************/
static bl_Return_t _Dcm_CheckRequestFlag(bl_u32_t flag)
{
    bl_Return_t ret = BL_ERR_OK;

    if (flag != 0UL)
    {
        BL_DEBUG_ASSERT_CONFIG(RTE_GET_DOWNSTATUS_ID(flag)
                                == DCM_DOWNSTATUS_INDEX);

        ret = Rte_IsValidStatus(&g_DownContext,flag & DCM_FUNANDPHY_MASK);
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Check whether service is supported in current session.
 *
 *  \param[in]  flag - The configuration of basic check.
 *
 *  \return If the service is supported in current session returns BL_ERR_OK,
 *          otherwise returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK       - the service is supported.
 *  \retval BL_ERR_NOT_OK   - the service is NOT supported.
 *
 *  \since  V2.0.0
 *
 *****************************************************************************/
static bl_Return_t _Dcm_CheckSessionFlag(bl_u32_t flag)
{
    bl_Return_t ret = BL_ERR_OK;

    if (flag != 0UL)
    {
        BL_DEBUG_ASSERT_CONFIG(RTE_GET_DOWNSTATUS_ID(flag)
                        == DCM_DOWNSTATUS_INDEX);

        ret = Rte_IsValidStatus(&g_DownContext, flag & DCM_SESSION_MASK);
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Check whether downstatus is matched with security access flag.
 *
 *  \param[in]  flag - The configuration of basic check.
 *
 *  \return If the service is supported in current security level returns
 *          BL_ERR_OK, otherwise returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK       - the service is supported.
 *  \retval BL_ERR_NOT_OK   - the service is NOT supported.
 *
 *  \since  V5.0.0
 *
 *****************************************************************************/
static bl_Return_t _Dcm_CheckSecAccFlag(bl_u32_t flag)
{
    bl_DownStatus_t mask;
    bl_Return_t ret = BL_ERR_OK;

    if (flag != 0UL)
    {
        BL_DEBUG_ASSERT_CONFIG(RTE_GET_DOWNSTATUS_ID(flag)
                        == DCM_DOWNSTATUS_INDEX);

        mask = flag & DCM_SECURITYACCESS_MASK;

        /*check whether security access has done.*/
        ret = Rte_IsValidStatus(&g_DownContext, mask);
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Get servicelist pointer by id.
 *
 *  \param[in] id     - service id or subfunction id or data identifier id.
 *  \param[in] number - the number of service id or subfunction id or data
 *                      identifier id.
 *  \param[in] list   - the list of service or subfunction or data identifier.
 *
 *  \return If the service is supported returns the pointer of this service
 *          list, otherwise returns BL_NULL_PTR.
 *
 *  \since  V4.0.0
 *
 *****************************************************************************/
static const bl_DcmService_t *_Dcm_LookUpTable(bl_u16_t id,
                                                bl_u16_t number,
                                                const bl_DcmService_t *list)
{
    bl_u16_t i;
    const bl_DcmService_t *foundList = BL_NULL_PTR;

    for (i = 0; i < number; i++)
    {
        if (id == list[i].id)
        {
            foundList = &list[i];
            break;
        }
    }

    return foundList;
}

/**************************************************************************//**
 *
 *  \details Check whether it is non-default session. if true, reset S3timer.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
static void _Dcm_ResetS3Timer(void)
{
    bl_Return_t ret;

    /*check whether it is default session.*/
    ret = Rte_IsValidStatus(&g_DownContext, DCM_STATUS_SESSION_DEFAULT);
    if (BL_ERR_OK != ret)
    {
        /*set S3timer value.*/
        DCM_SET_S3TIMER(DCM_S3TIMERVALUE);
        /*start S3timer.*/
        DCM_START_S3TIMER();
    }
}


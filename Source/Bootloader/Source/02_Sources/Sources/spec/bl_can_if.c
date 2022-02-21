/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of the can_if module.
 *
 *  \file       bl_can_if.c
 *  \ingroup    can_if_module
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
#include "bl_common.h"
#include "bl_app.h"
#include "bl_can.h"
#include "bl_can_transceiver.h"
#include "bl_can_if_cfg.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 506,602,781,1532,2103,3112,3227 EOF*/
/*
 * 506:Dereferencing pointer value that is possibly NULL.
 * The parameter delay is not a null pointer.
 *
 * MISRA-C:2004 20.2(602):The identifier is reserved for use by the library.
 * The Bootloader do not use any library funtion and use the underscores to
 * indicate that the function is a interal function.
 *
 * MISRA-C:2004 5.6(781):The identifier is used as a structure/union member.
 * The member of the structure is used through the structure object.
 *
 * 1532:The function is only referenced in one translation unit.
 *
 * 2103:Integral promotion, unsigned short promoted to unsigned int.
 * This message will therefore only be generated when a short and an int are of
 * equal size.
 *
 * MISRA-C:2004 14.2(3112):This statement has no side-effect.
 * The DEBUG_ASSERT macro is used to debug bootloader when the BL_DEBUG is
 * enable. When the BL_DEBUG is disable, the DEBUG_ASSERT macro is null.
 *
 * 3227:The parameter is never modified and so it could be declared with const.
 *
 */

/*****************************************************************************
 *  Verify The Configurations of Macro
 *****************************************************************************/

/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/
/** \brief Receive a can frame from the can module.*/
static bl_Return_t _Canif_Read(bl_CanRxPdu_t *pdu);

/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/
/**************************************************************************//**
 *
 *  \details Initializes the can IF module.
 *
 *  \return If can if initializes successfully returns BL_ERR_OK,
 *          otherwise returnS BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK     - initialize successfully.
 *  \retval BL_ERR_NOT_OK - initialize unsuccessfully.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
bl_Return_t Canif_Init(void)
{
    bl_Return_t ret;

#if (CANIF_FUN_INIT_TRANSCEIVER == BL_FUN_ON)
    Cantrc_InitTransceiver();
#endif
    ret = Can_Init();

    return ret;
}

/**************************************************************************//**
 *
 *  \details Deinitializes the can IF module.
 *
 *  \return None.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
void Canif_DeInit(void)
{
    Can_Deinit();
}

/**************************************************************************//**
 *
 *  \details Transmit data to can bus.
 *
 *  \param[in] handle  - the index of a frame pdu list.
 *  \param[in] retSize - the size of the frame pdu memory.
 *  \param[in] buffer  - the address pointer of the frame pdu memory.
 *
 *  \return If transmit data successfully returns BL_ERR_OK,
 *          otherwise returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - transmit data successfully.
 *  \retval BL_ERR_NOT_OK - parameters is not valid.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
bl_Return_t Canif_Write(bl_ComIfHandle_t handle,
                        bl_BufferSize_t size,
                        const bl_Buffer_t *buffer)
{
    bl_Return_t ret = BL_ERR_NOT_OK;
    bl_CanTxPdu_t pdu;


    if((handle < g_CanIfTxPduCfg.number)
        && (size <= CANIF_MAX_CAN_FRAME_SIZE)
        && (buffer != BL_NULL_PTR))
    {
        pdu.handle = g_CanIfTxPduCfg.txList[handle].handle;
        pdu.canId = g_CanIfTxPduCfg.txList[handle].id;
        pdu.dlc = size;
        pdu.frame = buffer;

        ret = Can_Write(&pdu);
    }

    return ret;

}

/**************************************************************************//**
 *
 *  \details can if polls all rx to read data from can driver
 *
 *  \param[in/out]  data - the pointer of the communication IF data.
 *
 *  \return If read data successfully returns BL_ERR_OK, otherwise returns
 *          BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK       - get new data successfully.
 *  \retval BL_ERR_NOT_OK   - no new data is got.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
bl_Return_t Canif_TryToRead(bl_ComIfData_t *data)
{
    bl_Return_t ret;
    bl_CanRxPdu_t pdu;
    bl_BufferSize_t recvSize;

    BL_DEBUG_ASSERT_PARAM(data != BL_NULL_PTR);
    BL_DEBUG_ASSERT(data->bufSize > 0);

    ret = _Canif_Read(&pdu);
    if (BL_ERR_OK == ret)
    {
        if (pdu.dlc > data->bufSize)
        {
            recvSize = data->bufSize;
        }
        else
        {
            recvSize = pdu.dlc;
        }

        Bl_MemCpy(data->buffer,pdu.frame,(bl_Size_t)recvSize);

        data->retHandle = pdu.handle;
        data->retSize = recvSize;
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details check whether can IF transmit data successfully
 *
 *  \param[in] handle  - the index of a frame pdu list.
 *
 *  \return If transmit data successfully returns BL_ERR_OK, otherwise returns
 *          BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK       - transmit data successfully.
 *  \retval BL_ERR_NOT_OK   - can controller is busy or idle.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
bl_Return_t Canif_IsWritten(bl_ComIfHandle_t handle)
{
    bl_Return_t ret = BL_ERR_NOT_OK;

    if(handle < g_CanIfTxPduCfg.number)
    {
        ret = Can_CheckTxStatus(g_CanIfTxPduCfg.txList[handle].handle);
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details can if polls all tx whether data transmits okay
 *
 *  \return none
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
void Canif_TxMainFunction(void)
{
    bl_ComIfHandle_t i;
    bl_ComIfHandle_t j;
    bl_ComIfHandle_t lastHandle;
    bl_ComIfHandle_t curHandle;
    bl_Return_t ret = BL_ERR_NOT_OK;

    for(i = 0; i < g_CanIfTxPduCfg.number; i++)
    {
        curHandle = g_CanIfTxPduCfg.txList[i].handle;
        
        for(j = 0; j < i; j++)
        {
            lastHandle = g_CanIfTxPduCfg.txList[j].handle;
            
            if(curHandle == lastHandle)
            {
                break;
            }
        }
        
        if(j == i)
        {
            ret = Can_CheckTxStatus(curHandle);
        }
        
        if(BL_ERR_OK == ret)
        {
            g_CanIfTxPduCfg.TxConf(i);
        }
    }

    return ;
}

/**************************************************************************//**
 *
 *  \details can if polls all rx whether data reads okay
 *
 *  \return none
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
void Canif_RxMainFunction(void)
{
    bl_Return_t ret;
    bl_CanRxPdu_t pdu;

    ret = _Canif_Read(&pdu);
    if (BL_ERR_OK == ret)
    {
        BL_DEBUG_ASSERT_NO_RET(g_CanIfRxPduCfg.RxInd != BL_NULL_PTR);

        g_CanIfRxPduCfg.RxInd(pdu.handle,pdu.dlc,pdu.frame);
    }

    return ;
}

/**************************************************************************//**
 *
 *  \details can if polls all channels whether busoff happens and recoverys
 *
 *  \return none
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
void Canif_BusoffMainFunction(void)
{
    Can_BusOff_Check();
}

#if (RTE_FUN_SYSTEM_SLEEP == BL_FUN_ON)
/**************************************************************************//**
 *
 *  \details can if set controller sleep
 *
 *  \return none
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
void Canif_Sleep(void)
{
    Can_Sleep();
}
#endif

#if (CANIF_FUN_DYNAMIC_CANID == BL_FUN_ON)
/**************************************************************************//**
 *
 *  \details Set the Tx Can id.
 *
 *  \return none
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
void Canif_SetTxCanId(bl_ComIfHandle_t handle, bl_u32_t id)
{
    if (handle < g_CanIfTxPduCfg.number)
    {
        g_CanIfTxPduCfg.txList[handle].id = id;
    }

    return ;
}

/**************************************************************************//**
 *
 *  \details Set the Rx Can id.
 *
 *  \return none
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
void Canif_SetRxCanId(bl_ComIfHandle_t handle, bl_u32_t id)
{
    if (handle < g_CanIfRxPduCfg.number)
    {
        g_CanIfRxPduCfg.rxList[handle].id = id;
    }

    return ;
}

#endif

/**************************************************************************//**
 *
 *  \details can if read data from can driver
 *
 *  \param[in]  handle  - the index of a frame pdu list.
 *  \param[out] buffer  - the address pointer of the frame pdu memory.
 *  \param[out] retSize - the size of the frame pdu memory.
 *
 *  \return if reads data successfully returns BL_ERR_OK,
 *          otherwise returns BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK       - get new data successfully.
 *  \retval BL_ERR_NOT_OK   - no new data is got.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
static bl_Return_t _Canif_Read(bl_CanRxPdu_t *pdu)
{
    bl_Return_t ret = BL_ERR_NOT_OK;
    bl_Return_t readRet;
    bl_ComIfHandle_t i;
    bl_u16_t rxPduNum;
    const bl_CanIfPduCfg_t *rxList;

    rxPduNum = g_CanIfRxPduCfg.number;
    rxList = g_CanIfRxPduCfg.rxList;

#if (CANIF_FUN_FULL_CAN_CONTROLLER == BL_FUN_ON)
    for (i = 0; i < rxPduNum; i++)
    {
        pdu->handle = rxList[i].handle;
        ret = Can_Read(pdu);
        if (BL_ERR_OK == ret)
        {
            break;
        }
    }
#else
    readRet = Can_Read(pdu);
    if (BL_ERR_OK == readRet)
    {
        for (i = 0; i < rxPduNum; i++)
        {
            if ((rxList[i].handle == pdu->handle)
                && (rxList[i].id == pdu->canId))
            {
                pdu->handle = i;
                ret = BL_ERR_OK;
                break;
            }
        }
    }
#endif

    return ret;
}


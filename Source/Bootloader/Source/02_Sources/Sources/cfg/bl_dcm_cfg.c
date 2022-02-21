/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file to configurate the DCM module.
 *
 *  \file       bl_dcm_cfg.c
 *  \ingroup    communication_protocol_stack_module
 *  \author     heli.zhang <heli.zhang@hirain.com>
 *              mingqing.tang <mingqing.tang@hirain.com>
 *
 *  \version    5.2.0
 *  \date       19/06/2014
 *
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
 *      05.02.00 | 19/06/2014 | mingqing.tang    | N/A | BootSpec050001
 *
 *****************************************************************************/
#include "bl_dcm_cfg.h"
#include "bl_adpt_uds_platform.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 1257,1531,1533,3120,3211 EOF*/
/*
 * 1257:Suffixed integer constant implicitly converted to smaller integer type
 * on assignment.
 *
 * 1531:The object is referenced in only one translation unit.
 * g_DcmBuffer is a configurations.
 *
 * 1533:The object is only referenced by one function.
 * The g_DcmServiceList is a configurations.
 *
 * 3120:Hard-coded magic integer constant.
 * This is a only configuration.
 *
 * 3211:The global identifier is defined but not used.
 * The g_BootingCheckerList is used in the bl_booting.c file.
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
/**************************************************************************//**
 *  \details The dcmbuffer of saving rx and tx data.
 *****************************************************************************/
static bl_Buffer_t gs_Buffer[DCM_BUFFER_SIZE];

/**************************************************************************//**
 *  \details The subfunction list of 0x10 service.
 *****************************************************************************/
static const bl_DcmService_t gs_Dcm10SubId[DCM_10SUBID_NUMBER] =
{
    {
        1, 0, DCM_10SUBID_MINLEN, DCM_10SUBID_MAXLEN,
        DCM_10SUBID01_FLAG, BL_NULL_PTR, BL_NULL_PTR, &Adpt_UdsCallback1001
    },
    {
        2, 0, DCM_10SUBID_MINLEN, DCM_10SUBID_MAXLEN,
        DCM_10SUBID02_FLAG, BL_NULL_PTR, BL_NULL_PTR, &Adpt_UdsCallback1002
    },
    {
        3, 0, DCM_10SUBID_MINLEN, DCM_10SUBID_MAXLEN,
        DCM_10SUBID03_FLAG, BL_NULL_PTR, BL_NULL_PTR, &Adpt_UdsCallback1003
    },
};

/**************************************************************************//**
 *  \details The subfunction list of 0x11 service.
 *****************************************************************************/
static const bl_DcmService_t gs_Dcm11SubId[DCM_11SUBID_NUMBER] =
{
    {
        1, 0, DCM_11SUBID_MINLEN, DCM_11SUBID_MAXLEN,
        DCM_11SUBID_FLAG, BL_NULL_PTR, BL_NULL_PTR, &Adpt_UdsCallback1101
    },
    {
        3, 0, DCM_11SUBID_MINLEN, DCM_11SUBID_MAXLEN,
        DCM_11SUBID_FLAG, BL_NULL_PTR, BL_NULL_PTR, &Adpt_UdsCallback1103
    },
};

/**************************************************************************//**
 *  \details The data identifier list of 0x22 service.
 *****************************************************************************/
static const bl_DcmService_t gs_Dcm22Did[DCM_22DID_NUMBER] =
{
    {
        0xF180u, 0, DCM_22DID_MINLEN, 0,
        DCM_22DID_FLAG,BL_NULL_PTR, BL_NULL_PTR,
        &Adpt_UdsCallBackReadBootSoftwareId
    },
	{
        0xF186u, 0, DCM_22DID_MINLEN, 0,
        DCM_22DID_FLAG,BL_NULL_PTR, BL_NULL_PTR,
        &Adpt_UdsCallBackReadActiveDiagnosticSession
    },
	{
        0x0200u, 0, DCM_22DID_MINLEN, 0,
        DCM_22DID_FLAG,BL_NULL_PTR, BL_NULL_PTR,
        &Adpt_UdsCallBackReadPgrmCounter
    },
    {
        0x0201u, 0, DCM_22DID_MINLEN, 0,
        DCM_22DID_FLAG,BL_NULL_PTR, BL_NULL_PTR,
        &Adpt_UdsCallBackReadPgrmAttempCounter
    },
    {
        0xF198u, 0, DCM_22DID_MINLEN, 0,
        DCM_22DID_FLAG,BL_NULL_PTR, BL_NULL_PTR,
        &Adpt_UdsCallBackReadTesterNumber
    },
    {
        0xF199u, 0, DCM_22DID_MINLEN, 0,
        DCM_22DID_FLAG,BL_NULL_PTR, BL_NULL_PTR,
        &Adpt_UdsCallBackReadProgramDate
    },
	{
        0xF18Au, 0, DCM_22DID_MINLEN, 0,
        DCM_22DID_FLAG,BL_NULL_PTR, BL_NULL_PTR,
        &Adpt_UdsCallBackReadIdentifierInformation
    },
/*
	{
        0xF190u, 0, DCM_22DID_MINLEN, 0,
        DCM_22DID_FLAG,BL_NULL_PTR, BL_NULL_PTR,
        &Adpt_UdsCallBackReadSGMWVIN
    },  
	{
		0xF192u, 0, DCM_22DID_MINLEN, 0,
		DCM_22DID_FLAG,BL_NULL_PTR, BL_NULL_PTR,
		&Adpt_UdsCallBackReadHardwareNumber
	},
	{
		0xF193u, 0, DCM_22DID_MINLEN, 0,
		DCM_22DID_FLAG,BL_NULL_PTR, BL_NULL_PTR,
		&Adpt_UdsCallBackReadHardwareVersion
	},
	{
		0xF194u, 0, DCM_22DID_MINLEN, 0,
		DCM_22DID_FLAG,BL_NULL_PTR, BL_NULL_PTR,
		&Adpt_UdsCallBackReadSoftwareNumber
	},
	{
		0xF195u, 0, DCM_22DID_MINLEN, 0,
		DCM_22DID_FLAG,BL_NULL_PTR, BL_NULL_PTR,
		&Adpt_UdsCallBackReadSoftwareVersion
	},
*/
	{
		0xF1C6u, 0, DCM_22DID_MINLEN, 0,
		DCM_22DID_FLAG,BL_NULL_PTR, BL_NULL_PTR,
		&Adpt_UdsCallBackReadCalibrationDataNumberInformation
	},
	{
		0xF1CBu, 0, DCM_22DID_MINLEN, 0,
		DCM_22DID_FLAG,BL_NULL_PTR, BL_NULL_PTR,
		&Adpt_UdsCallBackReadComponentAssemblyNumber
	},	
		
		
};

/**************************************************************************//**
 *  \details The subfunction list of 0x27 service.
 *****************************************************************************/
static const bl_DcmService_t gs_Dcm27SubId[DCM_27SUBID_NUMBER] =
{
    {
        0x03, 0, DCM_27SEED_MINLEN, DCM_27SEED_MAXLEN, DCM_27SUBIDSEED_FLAG,
        BL_NULL_PTR, BL_NULL_PTR, &Adpt_UdsCallbackGetSeedForLevel1
    },
    {
        0x04, 0, DCM_27KEY_MINLEN, DCM_27KEY_MAXLEN, DCM_27SUBIDKEY_FLAG,
        BL_NULL_PTR, BL_NULL_PTR, &Adpt_UdsCallbackVerifyKeyForLevel1
    },
//	{
//        0x11, 0, DCM_27SEED_MINLEN, DCM_27SEED_MAXLEN, DCM_27SUBIDSEED_FLAG,
//        BL_NULL_PTR, BL_NULL_PTR, &Adpt_UdsCallbackGetSeedForLevel1
//    },
//    {
//        0x12, 0, DCM_27KEY_MINLEN, DCM_27KEY_MAXLEN, DCM_27SUBIDKEY_FLAG,
//        BL_NULL_PTR, BL_NULL_PTR, &Adpt_UdsCallbackVerifyKeyForLevel1
//    },
};

/**************************************************************************//**
 *  \details The subfunction list of 0x28 service.
 *****************************************************************************/
static const bl_DcmService_t gs_Dcm28SubId[DCM_28SUBID_NUMBER] =
{
    {
        0, 0, DCM_28SUBID_MINLEN, DCM_28SUBID_MAXLEN, DCM_28SUBID03_FLAG,
        BL_NULL_PTR,BL_NULL_PTR, &Adpt_UdsCallback28
    },
    {
        1, 0, DCM_28SUBID_MINLEN, DCM_28SUBID_MAXLEN, DCM_28SUBID00_FLAG,
        BL_NULL_PTR,BL_NULL_PTR, &Adpt_UdsCallback28
    },
    {
        3, 0, DCM_28SUBID_MINLEN, DCM_28SUBID_MAXLEN, DCM_28SUBID00_FLAG,
        BL_NULL_PTR,BL_NULL_PTR, &Adpt_UdsCallback28
    },
};

/**************************************************************************//**
 *  \details The data identifier list of 0x2E service.
 *****************************************************************************/
static const bl_DcmService_t gs_Dcm2EDid[DCM_2EDID_NUMBER] =
{
    {
        0xF198u, 0, DCM_2ETESTERNUMBER_MINLEN, DCM_2ETESTERNUMBER_MAXLEN, 
		DCM_2EDID_FLAG, BL_NULL_PTR, BL_NULL_PTR, &Adpt_UdsCallBackWriteTesterNum
    },
    {
        0xF199u, 0, DCM_2EPROGRAMDATE_MINLEN, DCM_2EPROGRAMDATE_MAXLEN, 
		DCM_2EDID_FLAG, BL_NULL_PTR, BL_NULL_PTR, &Adpt_UdsCallbackWriteProgramDate
    },
};

/**************************************************************************//**
 *  \details The data identifier list of 0x31 service.
 *****************************************************************************/
static const bl_DcmService_t gs_Dcm31Did[DCM_31DID_NUMBER] =
{
    {
        0xFF00u, 0, DCM_31ERASE_MINLEN, DCM_31ERASE_MAXLEN, DCM_31ERASE_FLAG,
        BL_NULL_PTR, BL_NULL_PTR, &Adpt_UdsCallbackEraseMemory
    },
    {
        0x0202u, 0, DCM_31CHECKSUM_MINLEN, DCM_31CHECKSUM_MAXLEN, 
		DCM_31CHECKSUM_FLAG, BL_NULL_PTR, BL_NULL_PTR, &Adpt_UdsCallbackCheckSum
    },
    {
        0xFF01u, 0, DCM_31COMPAT_MINLEN, DCM_31COMPAT_MAXLEN, DCM_31COMPAT_FLAG,
        BL_NULL_PTR, BL_NULL_PTR, &Adpt_UdsCallbackCheckCompatibility
    },
#if(RTE_FUN_STAY_IN_BOOT == BL_FUN_ON)
    {
        0xF518u, 0, DCM_31STAYINBOOT_MINLEN, DCM_31STAYINBOOT_MAXLEN, 
		DCM_31STAYINBOOT_FLAG, BL_NULL_PTR, BL_NULL_PTR, &Adpt_UdsCallbackStayInBoot
    },
#endif
};

/**************************************************************************//**
 *  \details The subfunction list of 0x31 service.
 *****************************************************************************/
static const bl_DcmService_t gs_Dcm31SubId[DCM_31SUBID_NUMBER] =
{
    {
        1, DCM_31DID_NUMBER,DCM_31SUBID_MINLEN, DCM_31SUBID_MAXLEN, 
        DCM_31SUBID_FLAG, gs_Dcm31Did, &g_DcmDidHeader, BL_NULL_PTR
    },
};

/**************************************************************************//**
 *  \details The subfunction list of 0x3E service.
 *****************************************************************************/
static const bl_DcmService_t gs_Dcm3ESubId[DCM_3ESUBID_NUMBER] =
{
    {
        0, 0, DCM_3ESUBID_MINLEN, DCM_3ESUBID_MAXLEN, 0, BL_NULL_PTR, 
        BL_NULL_PTR, &Adpt_UdsCallback3E
    },
};

/**************************************************************************//**
 *  \details The subfunction list of 0x85 service.
 *****************************************************************************/
static const bl_DcmService_t gs_Dcm85SubId[DCM_85SUBID_NUMBER] =
{
    {
        1, 0, DCM_85SUBID_MINLEN, DCM_85SUBID_MAXLEN, 0, BL_NULL_PTR, 
        BL_NULL_PTR, &Adpt_UdsCallback85
    },
    {
        2, 0, DCM_85SUBID_MINLEN, DCM_85SUBID_MAXLEN, 0, BL_NULL_PTR, 
        BL_NULL_PTR, &Adpt_UdsCallback85
    },
};

/**************************************************************************//**
 *  \details The all service list of dcm mudule.
 *****************************************************************************/
static const bl_DcmService_t gs_DcmService[DCM_SERVICE_NUMBER] =
{
    {
        0x0010u, DCM_10SUBID_NUMBER, DCM_10SERVICE_MINLEN,
        DCM_10SERVICE_MAXLEN, DCM_10SERVICE_FLAG, gs_Dcm10SubId,
        &g_DcmSubIdHeader, BL_NULL_PTR
    },
    {
        0x0011u, DCM_11SUBID_NUMBER, DCM_11SERVICE_MINLEN,
        DCM_11SERVICE_MAXLEN, DCM_11SERVICE_FLAG, gs_Dcm11SubId,\
        &g_DcmSubIdHeader, BL_NULL_PTR
    },
    {
        0x0014u, DCM_14DID_NUMBER, DCM_14SERVICE_MINLEN,
        DCM_14SERVICE_MAXLEN, DCM_14SERVICE_FLAG, BL_NULL_PTR,\
        BL_NULL_PTR, BL_NULL_PTR                 
    },
    {
        0x0019u, DCM_19SUBID_NUMBER, DCM_19SERVICE_MINLEN,
        DCM_19SERVICE_MAXLEN, DCM_19SERVICE_FLAG, BL_NULL_PTR,\
        BL_NULL_PTR, BL_NULL_PTR                 
    },
    {
        0x0022u, DCM_22DID_NUMBER, DCM_22SERVICE_MINLEN,
        DCM_22SERVICE_MAXLEN, DCM_22SERVICE_FLAG, gs_Dcm22Did,
        &g_DcmDidHeader,BL_NULL_PTR
    },
    {
        0x0027u, DCM_27SUBID_NUMBER, DCM_27SERVICE_MINLEN,
        DCM_27SERVICE_MAXLEN, DCM_27SERVICE_FLAG, gs_Dcm27SubId,
        &g_DcmSubIdHeader, BL_NULL_PTR
    },
    {
        0x0028u, DCM_28SUBID_NUMBER, DCM_28SERVICE_MINLEN,
        DCM_28SERVICE_MAXLEN, DCM_28SERVICE_FLAG, gs_Dcm28SubId,
        &g_DcmSubIdHeader,BL_NULL_PTR
    },
    {
        0x002Eu, DCM_2EDID_NUMBER, DCM_2ESERVICE_MINLEN,
        DCM_2ESERVICE_MAXLEN, DCM_2ESERVICE_FLAG, gs_Dcm2EDid,
        &g_DcmDidHeader, BL_NULL_PTR
    },
    {
        0x0031u, DCM_31SUBID_NUMBER, DCM_31SERVICE_MINLEN,
        DCM_31SERVICE_MAXLEN, DCM_31SERVICE_FLAG, gs_Dcm31SubId,
        &g_DcmSubIdHeader, BL_NULL_PTR
    },
    {
        0x0034u, DCM_34SUBID_NUMBER, DCM_34SERVICE_MINLEN,
        DCM_34SERVICE_MAXLEN, DCM_34SERVICE_FLAG, BL_NULL_PTR,
        BL_NULL_PTR, &Adpt_UdsCallback34
    },
    {
        0x0036u, DCM_36SUBID_NUMBER, DCM_36SERVICE_MINLEN,
        DCM_36SERVICE_MAXLEN, DCM_36SERVICE_FLAG, BL_NULL_PTR,
        BL_NULL_PTR, &Adpt_UdsCallback36
    },
    {
        0x0037u, DCM_37SUBID_NUMBER, DCM_37SERVICE_MINLEN,
        DCM_37SERVICE_MAXLEN, DCM_37SERVICE_FLAG, BL_NULL_PTR,
        BL_NULL_PTR, &Adpt_UdsCallback37
    },
    {
        0x003Eu, DCM_3ESUBID_NUMBER, DCM_3ESERVICE_MINLEN,
        DCM_3ESERVICE_MAXLEN, DCM_3ESERVICE_FLAG, gs_Dcm3ESubId,
        &g_DcmSubIdHeader, BL_NULL_PTR
    },
    {
        0x0085u, DCM_85SUBID_NUMBER, DCM_85SERVICE_MINLEN,
        DCM_85SERVICE_MAXLEN, DCM_85SERVICE_FLAG, gs_Dcm85SubId,
        &g_DcmSubIdHeader, BL_NULL_PTR
    },
    {
        0x002Fu, DCM_2FDID_NUMBER, DCM_2FSERVICE_MINLEN,
        DCM_2FSERVICE_MAXLEN, DCM_2FSERVICE_FLAG, BL_NULL_PTR,\
        BL_NULL_PTR, BL_NULL_PTR                 //uidq0888: in order to reply NRC 7F  not 11
    },
};

/*****************************************************************************
 *  External Variable Definitions
*****************************************************************************/
/**************************************************************************//**
 *  \details The dcmbuffer info, including recvSize, tranSize and so on.
 *****************************************************************************/
bl_DcmBuffer_t g_DcmBuffer =
{
    DCM_STATUS_BUFFER_UNLOCK, 0, 0, 0, DCM_BUFFER_SIZE, gs_Buffer,
};

const bl_DcmService_t g_DcmServiceList =
{
    0,
    DCM_SERVICE_NUMBER,
    0,
    0,
    0,
    gs_DcmService,
    &g_DcmServiceHeader,
    BL_NULL_PTR
};


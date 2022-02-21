/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the head file to configurate the DCM module.
 *
 *  \file       bl_dcm_cfg.h
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
#ifndef _BL_DCM_CFG_H_
#define _BL_DCM_CFG_H_
#include "bl_dcm.h"
#include "bl_rte_funcfg.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 3205,3210,3447,3448 EOF*/
/*
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
 */

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
#define DCM_SERVICE_NUMBER          (15)
#define DCM_10SUBID_NUMBER          (3)
#define DCM_11SUBID_NUMBER          (2)
#define DCM_14DID_NUMBER            (1)
#define DCM_19SUBID_NUMBER          (3)
#define DCM_22DID_NUMBER            (14)
#define DCM_27SUBID_NUMBER          (2)
#define DCM_28SUBID_NUMBER          (3)
#define DCM_2EDID_NUMBER            (2)
#define DCM_31SUBID_NUMBER          (1)
#define DCM_2FDID_NUMBER            (2)

#if(RTE_FUN_STAY_IN_BOOT == BL_FUN_ON)
#define DCM_31DID_NUMBER            (4)
#else
#define DCM_31DID_NUMBER            (3)
#endif

#define DCM_34SUBID_NUMBER          (0)
#define DCM_36SUBID_NUMBER          (0)
#define DCM_37SUBID_NUMBER          (0)
#define DCM_3ESUBID_NUMBER          (1)
#define DCM_85SUBID_NUMBER          (2)

#define DCM_10SERVICE_MINLEN        (2)
#define DCM_10SUBID_MINLEN          (0)
#define DCM_11SERVICE_MINLEN        (2)
#define DCM_11SUBID_MINLEN          (0)
#define DCM_14SERVICE_MINLEN        (4)
#define DCM_19SERVICE_MINLEN        (0)
#define DCM_22SERVICE_MINLEN        (3)
#define DCM_22DID_MINLEN            (0)
#define DCM_27SERVICE_MINLEN        (2)
#define DCM_27SEED_MINLEN           (0)
#define DCM_27KEY_MINLEN            (2 + 4)
#define DCM_28SERVICE_MINLEN        (3)
#define DCM_28SUBID_MINLEN          (0)
#define DCM_2ESERVICE_MINLEN        (4)
#define DCM_2ETESTERNUMBER_MINLEN   (3 + 10)
#define DCM_2EPROGRAMDATE_MINLEN    (3 + 4)
#define DCM_31SERVICE_MINLEN        (4)
#define DCM_31SUBID_MINLEN          (0)
#define DCM_31ERASE_MINLEN          (4 + 9)
#define DCM_31CHECKSUM_MINLEN       (4 + 0)
#define DCM_31COMPAT_MINLEN         (4 + 0)
#define DCM_31STAYINBOOT_MINLEN     (0)
#define DCM_34SERVICE_MINLEN        (1 + 10)
#define DCM_36SERVICE_MINLEN        (3)
#define DCM_37SERVICE_MINLEN        (1)
#define DCM_3ESERVICE_MINLEN        (2)
#define DCM_3ESUBID_MINLEN          (0)
#define DCM_85SERVICE_MINLEN        (2)
#define DCM_85SUBID_MINLEN          (0)
#define DCM_2FSERVICE_MINLEN        (4)

#define DCM_10SERVICE_MAXLEN        (2)
#define DCM_10SUBID_MAXLEN          (0)
#define DCM_11SERVICE_MAXLEN        (2)
#define DCM_11SUBID_MAXLEN          (0)
#define DCM_14SERVICE_MAXLEN        (4)
#define DCM_19SERVICE_MAXLEN        (0)
#define DCM_22SERVICE_MAXLEN        (3)
#define DCM_22DID_MAXLEN            (0)
#define DCM_27SERVICE_MAXLEN        (6)
#define DCM_27SEED_MAXLEN           (2)
#define DCM_27KEY_MAXLEN            (2 + 4)
#define DCM_28SERVICE_MAXLEN        (3)
#define DCM_28SUBID_MAXLEN          (0)
#define DCM_2ESERVICE_MAXLEN       	(0)
#define DCM_2ETESTERNUMBER_MAXLEN   (3 + 10)
#define DCM_2EPROGRAMDATE_MAXLEN    (3 + 4)
#define DCM_31SERVICE_MAXLEN        (0)
#define DCM_31SUBID_MAXLEN          (0)
#define DCM_31ERASE_MAXLEN          (4 + 9)
#define DCM_31CHECKSUM_MAXLEN       (4 + 4)
#define DCM_31PROGRAMMDEPEN_MAXLEN  (4 + 0)
#define DCM_31COMPAT_MAXLEN         (4 + 0)
#define DCM_31STAYINBOOT_MAXLEN     (0)
#define DCM_34SERVICE_MAXLEN        (11)
#define DCM_36SERVICE_MAXLEN        (0)
#define DCM_37SERVICE_MAXLEN        (1)
#define DCM_3ESERVICE_MAXLEN        (2)
#define DCM_3ESUBID_MAXLEN          (0)
#define DCM_85SERVICE_MAXLEN        (2)
#define DCM_85SUBID_MAXLEN          (0)
#define DCM_2FSERVICE_MAXLEN        (4)

#define DCM_10SERVICE_FLAG          (0x00000000UL)
#define DCM_10SUBID01_FLAG          DCM_MAKE_FLAG(0x31FUL)
#define DCM_10SUBID02_FLAG          DCM_MAKE_FLAG(0x316UL)
#define DCM_10SUBID03_FLAG          DCM_MAKE_FLAG(0x31DUL)
#define DCM_11SERVICE_FLAG          DCM_MAKE_FLAG(0x31FUL)
#define DCM_14SERVICE_FLAG          DCM_MAKE_FLAG(0x31DUL)
#define DCM_19SERVICE_FLAG          DCM_MAKE_FLAG(0x31DUL)
#define DCM_11SUBID_FLAG            (0x00000000UL)
#define DCM_22SERVICE_FLAG          DCM_MAKE_FLAG(0x312UL)
#define DCM_22DID_FLAG              (0x00000000UL)
#define DCM_27SERVICE_FLAG          DCM_MAKE_FLAG(0x316UL)
#define DCM_27SERVICE_FLAG_7E       DCM_MAKE_FLAG(0x31DUL) // uidp5359 27 01 to response 0x7E no 0x12
#define DCM_27SUBIDSEED_FLAG        (0x00000000UL)
#define DCM_27SUBIDKEY_FLAG         (0x00000000UL)
#define DCM_28SERVICE_FLAG          DCM_MAKE_FLAG(0x31CUL)
#define DCM_28SUBID03_FLAG          (0x00000000UL)
#define DCM_28SUBID00_FLAG          (0x00000000UL)
#define DCM_2ESERVICE_FLAG          DCM_MAKE_FLAG(0x212UL)
#define DCM_2EDID_FLAG              (0x40000217UL)
#define DCM_31SERVICE_FLAG          DCM_MAKE_FLAG(0x212UL)
#define DCM_31SUBID_FLAG            (0x40000217UL)
#define DCM_31ERASE_FLAG            (0x00000000UL)
#define DCM_31CHECKSUM_FLAG         (0x00000000UL)
#define DCM_31COMPAT_FLAG           (0x00000000UL)
#define DCM_2FSERVICE_FLAG          DCM_MAKE_FLAG(0x31CUL)

#if(RTE_FUN_STAY_IN_BOOT == BL_FUN_ON)
#define DCM_31STAYINBOOT_FLAG       DCM_MAKE_FLAG(0x315UL)
#endif
#define DCM_34SERVICE_FLAG          DCM_MAKE_FLAG(0x212UL)
#define DCM_36SERVICE_FLAG          DCM_MAKE_FLAG(0x212UL)
#define DCM_37SERVICE_FLAG          DCM_MAKE_FLAG(0x212UL)
#define DCM_3ESERVICE_FLAG          DCM_MAKE_FLAG(0x31FUL)
#define DCM_3ESUBID_FLAG            (0x00000000UL)
#define DCM_85SERVICE_FLAG          DCM_MAKE_FLAG(0x31CUL)
#define DCM_85SUBID_FLAG            (0x00000000UL)

/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/

/*****************************************************************************
 *  Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/
/** \brief The dcmbuffer info, including recvLen, sendLen and so on.*/
extern bl_DcmBuffer_t g_DcmBuffer;

/** \brief The all service list of dcm mudule.*/
extern const bl_DcmService_t g_DcmServiceList;

/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/

#endif


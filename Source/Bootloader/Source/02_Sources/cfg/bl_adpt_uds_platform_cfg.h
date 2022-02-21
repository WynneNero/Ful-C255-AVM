/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the head file to configurate the adapter module based
 *              on uds platform.
 *
 *  \file       bl_adpt_uds_platform_cfg.h
 *  \ingroup    communication_protocol_stack_module
 *  \author     mingqing.tang <mingqing.tang@hirain.com>
 *              heli.zhang <heli.zhang@hirain.com>
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
#ifndef _BL_ADPT_UDS_PLATFORM_CFG_H_
#define _BL_ADPT_UDS_PLATFORM_CFG_H_

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
/** \brief the 11 service save the reset flag.*/
#define ADPT_RESETBYSERVICE_FLAGID      (0x01u)
#define ADPT_ECUPARTNUMBER_FLAGID       (0x03u)

#if 0
#define ADPT_TESTERNUMBER_FLAGID        (11u)
#define ADPT_PROGRAMMINGDATE_FLAGID     (12u)
#endif

#define ADPT_IdentifierInformation_FLAGID      			 (15u)     /*0x40*/
#define ADPT_SGMWVIN_FLAGID						 		 (16u)     /*0x80*/
#define ADPT_HardwareNumber_FLAGID					 	 (17u)     /*0xC0*/
#define ADPT_HardwareVersion_FLAGID						 (18u)     /*0x100*/
#define ADPT_SoftwareNumber_FLAGID					 	 (19u)     /*0x140*/
#define ADPT_SoftwareVersion_FLAGID						 (20u)     /*0x180*/
#define ADPT_CalibrationDataNumber_FLAGID				 (21u)     /*0x1C0*/
#define ADPT_ComponentAssembly_FLAGID					 (22u)     /*0x200*/


#define ADPT_ProgrammingCounter_FLAGID        (7u)/*write to the dataflash directly,XJY-20171129*/
#define ADPT_ProgrammingAttempCounter_FLAGID     (8u)/*write to the dataflash directly,XJY-20171129*/
#define ADPT_TESTERNUMBER_FLAGID        (9u)/*write to the dataflash directly,LT-20160601*/
#define ADPT_PROGRAMMINGDATE_FLAGID     (10u)/*write to the dataflash directly,LT-20160601*/


#define ADPT_SESSION_RESPONSE_LEN       (0x04u)

#define ADPT_COMMCONTROLTYPE_DATA           (0x01u)
#define ADPT_COMMCONTROLTYPE_DATA_ALL       (0x03u)


#define ADPT_MAXNUM_OF_BLOCKLENGTH      (0x202u)
#define ADPT_MAXNUM_OF_TRANS_DATA       (ADPT_MAXNUM_OF_BLOCKLENGTH - 2)

#define ADPT_UDS_TX_HANDLE              (0)
#define ADPT_UDS_TX_TIMEOUT             (200000UL)

#define ADPT_UDS_ROUTE_NUMBER           (3)
#define ADPT_UDS_NUMBER_OF_GATEWAY      (0x01u)
#define ADPT_UDS_CONVERSION_DATA_LENGTH (0x08u)

#define ADPT_STAY_IN_BOOT_RESPONSE_HID  (0xF5u)
#define ADPT_STAY_IN_BOOT_RESPONSE_LID  (0x18u)

#define ADPT_REPROGRAM_FLAG_DID         (0)
#define ADPT_RESET_FLAG_DID             (1)

/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/

/*****************************************************************************
 *  Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/

#endif


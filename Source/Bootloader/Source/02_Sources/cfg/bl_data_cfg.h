/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a head file to configurate the data of the data manager
 *              module.
 *
 *  \file       bl_data_cfg.h
 *  \ingroup    data_manager_module
 *  \author     xin.shang <xin.shang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      04.00.00 | 06/03/2013 | xin.shang        | N/A | Boot040001
 *      04.02.00 | 11/03/2013 | xin.shang        | N/A | Boot040003
 *      04.03.00 | 11/03/2013 | xin.shang        | N/A | Boot040004
 *      04.11.00 | 13/03/2013 | xin.shang        | N/A | Boot040012
 *      04.13.00 | 15/03/2013 | xin.shang        | N/A | Boot040014
 *      04.14.00 | 20/03/2013 | xin.shang        | N/A | Boot040015
 *      04.21.00 | 21/03/2013 | xin.shang        | N/A | Boot040022
 *      04.31.00 | 04/04/2013 | xin.shang        | N/A | Boot040032
 *      05.00.00 | 19/06/2013 | xin.shang        | N/A | Boot050001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#ifndef _BL_DATA_CFG_H_
#define _BL_DATA_CFG_H_
#include "bl_data.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 3210,3447 EOF*/
/*
 * 3210:The global identifier is declared but is not used.
 * The functions are used in the bl_security_cfg.c file.
 *
 * MISRA-C:2004 8.8(3447):The identifier has external linkage but this
 * declaration is not in a header file.
 * The function Declarations are in the header file.
 *
 */

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
/*the memory configurations*/
#define DM_NUMBER_OF_MANAGED_DATA   (23)


/*reprogram requirement flag*/
#define DM_DATA_0_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_0_MEMID             (0)			// mem id: 0-RAM, 1- code flash, 2- data flash
#define DM_DATA_0_LOCAL_ADDR        (0xFEE07FF0UL)
#define DM_DATA_0_SIZE              (4UL)
#define DM_DATA_0_DDP               (&gs_defaultDataList[0])

/*reset requirement flag*/
#define DM_DATA_1_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_1_MEMID             (2)
#define DM_DATA_1_LOCAL_ADDR        (0x000003C4UL)
#define DM_DATA_1_SIZE              (4UL)
#define DM_DATA_1_DDP               (&gs_defaultDataList[DM_DATA_0_SIZE])

/*application valid flag*/
#define DM_DATA_2_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_2_MEMID             (1)
#define DM_DATA_2_LOCAL_ADDR        (0x00018000UL)//(0x00011000UL) xjy_test  //  (0x0000C200UL)
#define DM_DATA_2_SIZE              (4UL)
#define DM_DATA_2_DDP               (&gs_defaultDataList[8])

/*ECU Hardware Number DID F193*/
#define DM_DATA_3_TYPE              DM_DATA_TYPE_READ_ONLY
#define DM_DATA_3_MEMID             (2)/*DataFlash*/
#define DM_DATA_3_LOCAL_ADDR        (0xFF207100UL)//(0x0000A100UL)
#define DM_DATA_3_SIZE              (16UL)
#define DM_DATA_3_DDP               (BL_NULL_PTR)

/*Boot Software Identification DID F180*/
#define DM_DATA_4_TYPE              DM_DATA_TYPE_READ_ONLY
#define DM_DATA_4_MEMID             (1)/*CodeFlash*/
#define DM_DATA_4_LOCAL_ADDR        (0x00017FE0UL)//(0x00010FE0UL) 
#define DM_DATA_4_SIZE              (16UL)
#define DM_DATA_4_DDP               (BL_NULL_PTR)

/*GeelySparePartNumber DID F187*/
//#define DM_DATA_5_TYPE              DM_DATA_TYPE_READ_ONLY
//#define DM_DATA_5_MEMID             (1)/*CodeFlash*/
//#define DM_DATA_5_LOCAL_ADDR        (0x00010FF0UL)
//#define DM_DATA_5_SIZE              (8UL)
//#define DM_DATA_5_DDP               (BL_NULL_PTR)
/*ActiveDiagnosticSession DID F186*/
#define DM_DATA_5_TYPE              DM_DATA_TYPE_READ_ONLY
#define DM_DATA_5_MEMID             (1)/*CodeFlash*/
#define DM_DATA_5_LOCAL_ADDR        (0xFF200080UL) //(0x00010FF0UL)
#define DM_DATA_5_SIZE              (8UL)
#define DM_DATA_5_DDP               (BL_NULL_PTR)

/*VehicleManufacturerECUSoftwareVersionNumber DID F189*/ 
#define DM_DATA_6_TYPE              DM_DATA_TYPE_READ_ONLY
#define DM_DATA_6_MEMID             (1)/*CodeFlash*/
#define DM_DATA_6_LOCAL_ADDR        (0x0005FC10UL)
#define DM_DATA_6_SIZE              (16UL)
#define DM_DATA_6_DDP               (BL_NULL_PTR)


/*ProgrammingCounter DID 0200*/
#define DM_DATA_7_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_7_MEMID             (2)/*DataFlash*/
#define DM_DATA_7_LOCAL_ADDR        (0xFF2000C0UL)//(0xFF207000UL)/*Modify by LT,20160524*/
#define DM_DATA_7_SIZE              (4UL)
#define DM_DATA_7_DDP               (BL_NULL_PTR)

/*ProgrammingAttempCounter DID 0201*/
#define DM_DATA_8_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_8_MEMID             (2)/*Modify by LT,20160524*/
#define DM_DATA_8_LOCAL_ADDR        (0xFF200100UL)//(0xFF207040UL)/*Modify by LT,20160524*/
#define DM_DATA_8_SIZE              (4UL)
#define DM_DATA_8_DDP               (BL_NULL_PTR)


/*RepairShopCodeOrTesterSerialNumber DID F198*/
#define DM_DATA_9_TYPE              DM_DATA_TYPE_READ_AND_WRITE //DM_DATA_TYPE_READ_ONLY,Modify by LT,20160519
#define DM_DATA_9_MEMID             (2)/*(1),Modify by LT,20160524*/
#define DM_DATA_9_LOCAL_ADDR        (0xFF200140UL)///(0xFF207080UL)*Modify by LT,20160524*/
#define DM_DATA_9_SIZE              (16UL)
#define DM_DATA_9_DDP               (BL_NULL_PTR)

/*ProgrammingOrConfigurationDate DID F199*/
#define DM_DATA_10_TYPE              DM_DATA_TYPE_READ_AND_WRITE//DM_DATA_TYPE_READ_ONLY,Modify by LT,20160519
#define DM_DATA_10_MEMID             (2)/*(1),Modify by LT,20160524*/
#define DM_DATA_10_LOCAL_ADDR        (0xFF200180UL)//(0xFF2070C0UL)/*Modify by LT,20160524*/
#define DM_DATA_10_SIZE              (4UL)
#define DM_DATA_10_DDP               (BL_NULL_PTR)

/*RepairShopCodeOrTesterSerialNumber DID F198 in RAM*/
#define DM_DATA_11_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_11_MEMID             (0)
#define DM_DATA_11_LOCAL_ADDR        (0xFEDFEA00UL)
#define DM_DATA_11_SIZE              (16UL)
#define DM_DATA_11_DDP               (BL_NULL_PTR)

/*ProgrammingOrConfigurationDate DID F199 in RAM*/
#define DM_DATA_12_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_12_MEMID             (0)
#define DM_DATA_12_LOCAL_ADDR        (0xFEDFEA10UL)
#define DM_DATA_12_SIZE              (4UL)
#define DM_DATA_12_DDP               (BL_NULL_PTR)

/*ProgrammingOrConfigurationDate DID F198 + DID F199*/
#define DM_DATA_13_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_13_MEMID             (2)//(1)Modify by LT,20160524
#define DM_DATA_13_LOCAL_ADDR        (0xFF207080UL)//(0x0000C100UL)Modify by LT,20160524*/
#define DM_DATA_13_SIZE              (128UL)//20uL,Modify by LT,20160524*/
#define DM_DATA_13_DDP               (BL_NULL_PTR)



#if 0
/*ECU Hardware Number DID F193*/
#define DM_DATA_3_TYPE              DM_DATA_TYPE_READ_ONLY
#define DM_DATA_3_MEMID             (1)
#define DM_DATA_3_LOCAL_ADDR        (0x0000A100UL)
#define DM_DATA_3_SIZE              (16UL)
#define DM_DATA_3_DDP               (BL_NULL_PTR)

/*Boot Software Identification DID F180*/
#define DM_DATA_4_TYPE              DM_DATA_TYPE_READ_ONLY
#define DM_DATA_4_MEMID             (1)
#define DM_DATA_4_LOCAL_ADDR        (0x0000Bff0)
#define DM_DATA_4_SIZE              (16UL)
#define DM_DATA_4_DDP               (BL_NULL_PTR)

/*GeelySparePartNumber DID F187*/
#define DM_DATA_5_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_5_MEMID             (1)
#define DM_DATA_5_LOCAL_ADDR        (0x0000A110UL)
#define DM_DATA_5_SIZE              (8UL)
#define DM_DATA_5_DDP               (BL_NULL_PTR)

/*VehicleManufacturerECUSoftwareVersionNumber DID F189*/
#define DM_DATA_6_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_6_MEMID             (1)
#define DM_DATA_6_LOCAL_ADDR        (0x0000A118UL)
#define DM_DATA_6_SIZE              (16UL)
#define DM_DATA_6_DDP               (BL_NULL_PTR)

/*ProgrammingCounter DID 0200*/
#define DM_DATA_7_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_7_MEMID             (2)
#define DM_DATA_7_LOCAL_ADDR        (0xFF207F80UL)
#define DM_DATA_7_SIZE              (4UL)
#define DM_DATA_7_DDP               (BL_NULL_PTR)

/*ProgrammingAttempCounter DID 0201*/
#define DM_DATA_8_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_8_MEMID             (2)
#define DM_DATA_8_LOCAL_ADDR        (0xFF207F40UL)
#define DM_DATA_8_SIZE              (4UL)
#define DM_DATA_8_DDP               (BL_NULL_PTR)

/*RepairShopCodeOrTesterSerialNumber DID F198*/
#define DM_DATA_9_TYPE              DM_DATA_TYPE_READ_ONLY
#define DM_DATA_9_MEMID             (1)
#define DM_DATA_9_LOCAL_ADDR        (0x0000C100UL)
#define DM_DATA_9_SIZE              (16UL)
#define DM_DATA_9_DDP               (BL_NULL_PTR)

/*ProgrammingOrConfigurationDate DID F199*/
#define DM_DATA_10_TYPE              DM_DATA_TYPE_READ_ONLY
#define DM_DATA_10_MEMID             (1)
#define DM_DATA_10_LOCAL_ADDR        (0x0000C110UL)
#define DM_DATA_10_SIZE              (4UL)
#define DM_DATA_10_DDP               (BL_NULL_PTR)

/*RepairShopCodeOrTesterSerialNumber DID F198 in RAM*/
#define DM_DATA_11_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_11_MEMID             (0)
#define DM_DATA_11_LOCAL_ADDR        (0xFEDFEA00UL)
#define DM_DATA_11_SIZE              (16UL)
#define DM_DATA_11_DDP               (BL_NULL_PTR)

/*ProgrammingOrConfigurationDate DID F199 in RAM*/
#define DM_DATA_12_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_12_MEMID             (0)
#define DM_DATA_12_LOCAL_ADDR        (0xFEDFEA10UL)
#define DM_DATA_12_SIZE              (4UL)
#define DM_DATA_12_DDP               (BL_NULL_PTR)

/*ProgrammingOrConfigurationDate DID F198 + DID F199*/
#define DM_DATA_13_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_13_MEMID             (1)
#define DM_DATA_13_LOCAL_ADDR        (0x0000C100UL)
#define DM_DATA_13_SIZE              (20UL)
#define DM_DATA_13_DDP               (BL_NULL_PTR)

#endif


/*27 Failed Flag*/
#define DM_DATA_14_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_14_MEMID             (2)
#define DM_DATA_14_LOCAL_ADDR        (0xFF207180UL)/*modify by LT,20160623*/
#define DM_DATA_14_SIZE              (4UL)
#define DM_DATA_14_DDP               (&gs_defaultDataList[8])




#define DM_DATA_15_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_15_MEMID             (2)
#define DM_DATA_15_LOCAL_ADDR        (0xFF2001C0UL)/*modify by LF,20180128*/
#define DM_DATA_15_SIZE              (8UL)
#define DM_DATA_15_DDP               (BL_NULL_PTR)

#define DM_DATA_16_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_16_MEMID             (2)
#define DM_DATA_16_LOCAL_ADDR        (0xFF200200UL)/*modify by LF,20180128*/
#define DM_DATA_16_SIZE              (20UL)
#define DM_DATA_16_DDP               (BL_NULL_PTR)

#define DM_DATA_17_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_17_MEMID             (2)
#define DM_DATA_17_LOCAL_ADDR        (0xFF200240UL)/*modify by LF,20180128*/
#define DM_DATA_17_SIZE              (4UL)
#define DM_DATA_17_DDP               (BL_NULL_PTR)

#define DM_DATA_18_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_18_MEMID             (2)
#define DM_DATA_18_LOCAL_ADDR        (0xFF200280UL)/*modify by LF,20180128*/
#define DM_DATA_18_SIZE              (16UL)
#define DM_DATA_18_DDP               (BL_NULL_PTR)

#define DM_DATA_19_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_19_MEMID             (2)
#define DM_DATA_19_LOCAL_ADDR        (0xFF2002C0UL)/*modify by LF,20180128*/
#define DM_DATA_19_SIZE              (4UL)
#define DM_DATA_19_DDP               (BL_NULL_PTR)

#define DM_DATA_20_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_20_MEMID             (2)
#define DM_DATA_20_LOCAL_ADDR        (0xFF200300UL)/*modify by LF,20180128*/
#define DM_DATA_20_SIZE              (16UL)
#define DM_DATA_20_DDP               (BL_NULL_PTR)

#define DM_DATA_21_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_21_MEMID             (2)
#define DM_DATA_21_LOCAL_ADDR        (0xFF200340UL)/*modify by LF,20180128*/
#define DM_DATA_21_SIZE              (4UL)
#define DM_DATA_21_DDP               (BL_NULL_PTR)

#define DM_DATA_22_TYPE              DM_DATA_TYPE_READ_AND_WRITE
#define DM_DATA_22_MEMID             (2)
#define DM_DATA_22_LOCAL_ADDR        (0xFF200380UL)/*modify by LF,20180128*/
#define DM_DATA_22_SIZE              (4UL)
#define DM_DATA_22_DDP               (BL_NULL_PTR)



#define DM_MAX_DATA_SIZE             DM_DATA_13_SIZE

/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/

/*****************************************************************************
 *  Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/
/** \brief The data informations list.*/
extern const bl_DataInfoList_t g_DataInfoList;
/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/

#endif


/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a source file to configurate the data manager module.
 *
 *  \file       bl_data_cfg.c
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
#include "bl_data_cfg.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 1257,1531,3120,3211 EOF*/
/*
 * 1257:Suffixed integer constant implicitly converted to smaller integer type
 * on assignment.
 *
 * 1531:The object is referenced in only one translation unit.
 * g_DataInfoList is a configurations.
 *
 * 3120:Hard-coded magic integer constant.
 * This is a only configuration.
 *
 * 3211:The global identifier is defined but not used.
 * The g_DataInfoList is used in the bl_data.c file.
 *
 */

/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/
/** Calculate the sum of data size.*/
#define DM_DATA_SIZE_SUM     (12)
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

/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/
/******************************************************************************
 *  \details The default data list.
 *****************************************************************************/
static const bl_Buffer_t gs_defaultDataList[DM_DATA_SIZE_SUM] =
{
    0xA5u,0xA5u,0xA5u,0xA5u,
    0x55u,0x55u,0x55u,0x55u,
    0xAAu,0xAAu,0xAAu,0xAAu,
};

/**************************************************************************//**
 *  \details The data informations.
 *****************************************************************************/
static const bl_DataInfo_t gs_DataInfo[DM_NUMBER_OF_MANAGED_DATA] =
{
    {
        DM_DATA_0_TYPE,DM_DATA_0_MEMID,DM_DATA_0_LOCAL_ADDR,
        DM_DATA_0_SIZE,DM_DATA_0_DDP
    },
    {
        DM_DATA_1_TYPE,DM_DATA_1_MEMID,DM_DATA_1_LOCAL_ADDR,
        DM_DATA_1_SIZE,DM_DATA_1_DDP
    },
    {
        DM_DATA_2_TYPE,DM_DATA_2_MEMID,DM_DATA_2_LOCAL_ADDR,
        DM_DATA_2_SIZE,DM_DATA_2_DDP
    },
    {
        DM_DATA_3_TYPE,DM_DATA_3_MEMID,DM_DATA_3_LOCAL_ADDR,
        DM_DATA_3_SIZE,DM_DATA_3_DDP
    },
    {
        DM_DATA_4_TYPE,DM_DATA_4_MEMID,DM_DATA_4_LOCAL_ADDR,
        DM_DATA_4_SIZE,DM_DATA_4_DDP
    },
    {
        DM_DATA_5_TYPE,DM_DATA_5_MEMID,DM_DATA_5_LOCAL_ADDR,
        DM_DATA_5_SIZE,DM_DATA_5_DDP
    },
    {
        DM_DATA_6_TYPE,DM_DATA_6_MEMID,DM_DATA_6_LOCAL_ADDR,
        DM_DATA_6_SIZE,DM_DATA_6_DDP
    },
    {
        DM_DATA_7_TYPE,DM_DATA_7_MEMID,DM_DATA_7_LOCAL_ADDR,
        DM_DATA_7_SIZE,DM_DATA_7_DDP
    },
    {
        DM_DATA_8_TYPE,DM_DATA_8_MEMID,DM_DATA_8_LOCAL_ADDR,
        DM_DATA_8_SIZE,DM_DATA_8_DDP
    },
    {
        DM_DATA_9_TYPE,DM_DATA_9_MEMID,DM_DATA_9_LOCAL_ADDR,
        DM_DATA_9_SIZE,DM_DATA_9_DDP
    },
    {
        DM_DATA_10_TYPE,DM_DATA_10_MEMID,DM_DATA_10_LOCAL_ADDR,
        DM_DATA_10_SIZE,DM_DATA_10_DDP
    },
    {
        DM_DATA_11_TYPE,DM_DATA_11_MEMID,DM_DATA_11_LOCAL_ADDR,
        DM_DATA_11_SIZE,DM_DATA_11_DDP
    },
    {
        DM_DATA_12_TYPE,DM_DATA_12_MEMID,DM_DATA_12_LOCAL_ADDR,
        DM_DATA_12_SIZE,DM_DATA_12_DDP
    },
    {
        DM_DATA_13_TYPE,DM_DATA_13_MEMID,DM_DATA_13_LOCAL_ADDR,
        DM_DATA_13_SIZE,DM_DATA_13_DDP
    },
    {
        DM_DATA_14_TYPE,DM_DATA_14_MEMID,DM_DATA_14_LOCAL_ADDR,
        DM_DATA_14_SIZE,DM_DATA_14_DDP
    },

	{
        DM_DATA_15_TYPE,DM_DATA_15_MEMID,DM_DATA_15_LOCAL_ADDR,
        DM_DATA_15_SIZE,DM_DATA_15_DDP
    },
    {
        DM_DATA_16_TYPE,DM_DATA_16_MEMID,DM_DATA_16_LOCAL_ADDR,
        DM_DATA_16_SIZE,DM_DATA_16_DDP
    },
    {
        DM_DATA_17_TYPE,DM_DATA_17_MEMID,DM_DATA_17_LOCAL_ADDR,
        DM_DATA_17_SIZE,DM_DATA_17_DDP
    },
    {
        DM_DATA_18_TYPE,DM_DATA_18_MEMID,DM_DATA_18_LOCAL_ADDR,
        DM_DATA_18_SIZE,DM_DATA_18_DDP
    },
    {
        DM_DATA_19_TYPE,DM_DATA_19_MEMID,DM_DATA_19_LOCAL_ADDR,
        DM_DATA_19_SIZE,DM_DATA_19_DDP
    },

	{
        DM_DATA_20_TYPE,DM_DATA_20_MEMID,DM_DATA_20_LOCAL_ADDR,
        DM_DATA_20_SIZE,DM_DATA_20_DDP
    },
    {
        DM_DATA_21_TYPE,DM_DATA_21_MEMID,DM_DATA_21_LOCAL_ADDR,
        DM_DATA_21_SIZE,DM_DATA_21_DDP
    },
    {
        DM_DATA_22_TYPE,DM_DATA_22_MEMID,DM_DATA_22_LOCAL_ADDR,
        DM_DATA_22_SIZE,DM_DATA_22_DDP
    },

};


/******************************************************************************
 *  \details The data informations list.
 *
 *  \warning Do not change the name of this variable.
 *****************************************************************************/
const bl_DataInfoList_t g_DataInfoList =
{
    DM_NUMBER_OF_MANAGED_DATA,gs_DataInfo,
};
/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/


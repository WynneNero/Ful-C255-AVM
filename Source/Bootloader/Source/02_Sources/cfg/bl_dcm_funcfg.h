/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the head file to configurate the DCM module.
 *
 *  \file       bl_dcm_funcfg.h
 *  \ingroup    communication_protocol_stack_module
 *  \author     heli.zhang <heli.zhang@hirain.com>
 *              mingqing.tang <mingqing.tang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      05.00.00 | 19/06/2013 | heli.zhang       | N/A | Boot050001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#ifndef _BL_DCM_FUNCFG_H_
#define _BL_DCM_FUNCFG_H_

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
#define DCM_FUN_SECURITY_ACCESS     BL_FUN_ON
/*P2 and S3 timer definition.*/
#define DCM_P2STARTIMER_DIV         (10)  /*ISO15765-3*/
#define DCM_CALL_CYCLE              RTE_SYSTEM_SCHEDULE_PERIOD
#define DCM_P2TIMEVALUE             (50u/DCM_CALL_CYCLE)
#define DCM_P2STARTIMEVALUE         (5000u/DCM_CALL_CYCLE)
#define DCM_S3TIMERVALUE            (5000u/DCM_CALL_CYCLE)

#define DCM_BUFFER_SIZE             (0x210u)
#define DCM_TX_HANDLE               (0)

/*****************************************************************************
 *  Type Declarations
 *****************************************************************************/

/*****************************************************************************
 *  Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  External Global Variable Declarations
 *****************************************************************************/

/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/

#endif


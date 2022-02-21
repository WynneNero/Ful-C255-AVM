/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                         *
*   AUTHOR     :                                       *
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   :
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
* ----------------------------------------------------------------------
*  0.1          2016/8/29   ShangQiuju      Init version
* ----------------------------------------------------------------------
*  0.2          2016/12/30 ShangQiuju      Remove define parameter from .c file .
*=====================================================================*/
#ifndef _SOC_UPGRADE_H_
#define _SOC_UPGRADE_H_

#include "CONFIG.H"
#include "define.h"
/**** Definition of constants ****/
/**** Definition of macros ****/

#define GET_DATA_TIME_OUT 20

#define	HQ_CMD 0
#define LQ_CMD 1

/**** Declaration of constants ****/
/**** Declaration of variables ****/

typedef enum
{
    E_SOC_IDLE,
    E_SOC_POWER_ON,
    E_SOC_READY,
    E_SOC_CONNECTED,
    E_SOC_POWER_OFF,
    E_SOC_WAIT_RESET,
 } E_SOC_STATE;

typedef enum SOC_UPGRADE_STATE
{
    FIRST_CONNECT_BEGIN,
    FC_PW_ON,                    
    FC_WAIT_READ_FILE_MSG,
    FC_CHECK_FIRST_ROW_VALID,                   
    FC_WAKEUP,
    FC_FIRST_CONNECT_COMPLETE,
    SWDL_IDLE,
    SWDL_SOC_READY,
    SWDL_PROGRAMMING,
    SWDL_PROGRAMM_COMPLETE,
    SWDL_DELAY_SLEEP,
    SWDL_SUCCESS,
    SWDL_ERROR,  
}E_SOC_UPPGRADE_STATE;

/**** Declaration of functions ****/
void SocManager_Init(void);
void SocManager_DeInit(void);
void SocManager_Entry(void);
extern BOOL SocManager_SendMsg( U8 cmd_type, U16 service, U8 nArgs,U8 *pArg);


#define NotifyUpgradeDataReceived(size,data) SocDataReceivedData(size,data)

/**** Definition of macros ****/
///TODO:ADD DISPATCH FUNCTION
#endif /*_SOC_UPGRADE_H_*/

/****************************** END OF FILE ***************************/


/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   :            										   *
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
* 
*=====================================================================*/
#ifndef _CAN_OSEK_NET_MANAGER_IF_H_
#define _CAN_OSEK_NET_MANAGER_IF_H_ 


#include "NM_osek.h"
#include "Signal_if.h"  
#include "Hal_if.h"
/**** Definition of constants ****/

/**** Definition of types ****/ 

typedef enum
{
	E_CAN_IDIT,
    E_CAN_POWERON,
    E_CAN_WAIT_LINE_STABLE,
    E_CAN_CHECK,
    E_CAN_WAIT_POWER_STABLE,
    E_CAN_NORMAL,
    E_CAN_SLEEP,
    E_CAN_EER,    
    E_CAN_SLEEP_WAIT,
    E_CAN_BUSOFF_ENTER_SLEEP,
    E_CAN_RESET,
}CAN_STATE;

/**** Definition of macros ****/

/**** Declaration of constants ****/


/**** Declaration of variables ****/

/**** Declaration of functions ****/
extern void CanManager_Init(void);
extern void CanManager_10ms_Entry(void);
extern CAN_STATE CanManager_GetCanState(void);
extern void can_reset_nm_timeout_counter(void);
extern void can_nm_app_msg_wake_set(void);
extern void CanManagerTxConfirmation(void);
extern void CanManager_diagnose_actived(void);
#endif /*_CAN_OSEK_NET_MANAGER_IF_H_*/

/****************************** END OF FILE ***************************/


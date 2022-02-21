/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD NJ      									   *
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
* Version       Date        Name                  Changes and comments
*----------------------------------------------------------------------
*  0.1  Feb 20,2017       ZhangJie               Init Version.
*=====================================================================*/
#ifndef _CAN_MANAGER_
#define _CAN_MANAGER_
#include "iodefine.h"
#include "can_par.h"
#include "GPIO_if.h"


//#define CANTXSIG_PASS_1
//#include "Cansig_def.h"
//#define CANRXSIG_PASS_1
//#include "Cansig_def.h"

typedef enum
{
	E_CAN_IDIT,
    E_CAN_POWERON,
	E_CAN_WAKEUP,
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

#define CAN_DIAG_ID 0x748

#define CAN_SET_WAKE() 	GPIO_SetVal(GPIO_PORT_10, GPIO_PIN_A, TRUE)
#define CAN_CLR_WAKE() 	GPIO_SetVal(GPIO_PORT_10, GPIO_PIN_A, FALSE)
#define CAN_SET_STB()	GPIO_SetVal(GPIO_PORT_10, GPIO_PIN_B, TRUE)
#define CAN_CLR_STB()	GPIO_SetVal(GPIO_PORT_10, GPIO_PIN_B, FALSE)
#define CAN_SET_EN()	GPIO_SetVal(GPIO_PORT_10, GPIO_PIN_C, TRUE)
#define CAN_CLR_EN()	GPIO_SetVal(GPIO_PORT_10, GPIO_PIN_C, FALSE)

#define LOW_POWER_OFF_RECOVER_TIME 2 //50ms 
#define QUICK_POWER_OFF_RECOVER_TIME 17//200ms
#define BUS_OFF_ENTER_QUICK_RECOVER_MODE_TIME_CNT 4
#define DELAY_TO_SEND_FIRST_FRAME  11  //110ms  fix_LiuQi_tECUinitTime [150ms_200ms]
#define TNoACK 15  //150MS
#define TPause 15  //150MS

extern U8 SOC_OFF_ALLOW_Flag;
extern U8 NmWakeUpSta;

extern void CanManager_10ms_Entry(void);
extern CAN_STATE GetCanstate(void);
extern U32 CanDriver_GetSeed(void);
extern void CanManager_BusOffStart(void);
extern void CanManager_BusOffEnd(void);
extern void CanManagerTxConfirmation(void);
void CanManager_gotosleep(void);
void CanManager_wakeup(void);
void GetContiunousBusOffFlagCnt(void);
void ApplCheckStatus(void);


#endif/*_CANAPP_H*/


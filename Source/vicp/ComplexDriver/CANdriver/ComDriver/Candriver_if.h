/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD NJ    	 								   *
*   AUTHOR	   : 									   *
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   :
*-----------------------------------------------------------------------
* Version:0.1
* Date:20151014
* Author:Shang Qiuju
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
* ----------------------------------------------------------------------
* 0.1  Oct 14,2015  SHANG Qiuju Initial version
* ----------------------------------------------------------------------
* 0.2  Mar 08,2017 Zhang Jie       Remove duplicate headfile.
* ----------------------------------------------------------------------
* 0.3  Mar 17,2017 Zhang Jie       Add io control funcrtion.
=====================================================================*/
#ifndef _CAN_DRIVER_IF_H_
#define _CAN_DRIVER_IF_H_
#include "Driver_IF.h"
#include "define.h"

#include "desc.h"
#include "Appdesc_Cfg.h"
typedef void (*CanDiagFuncCallBackType)(APPL_DESC_SERVICE_ID_TYPE MsgContextId, DescMsgContext* pMsgContext);

#define CAN_SET_WAKE() 	GPIO_SetVal(GPIO_PORT_8, GPIO_PIN_5, TRUE)
#define CAN_CLR_WAKE() 	GPIO_SetVal(GPIO_PORT_8, GPIO_PIN_5, FALSE)
#define CAN_SET_STB()	GPIO_SetVal(GPIO_PORT_8, GPIO_PIN_0, TRUE)
#define CAN_CLR_STB()	GPIO_SetVal(GPIO_PORT_8, GPIO_PIN_0, FALSE)
#define CAN_SET_EN()	GPIO_SetVal(GPIO_PORT_8, GPIO_PIN_1, TRUE)
#define CAN_CLR_EN()	GPIO_SetVal(GPIO_PORT_8, GPIO_PIN_1, FALSE)
#define CAN_GET_ERR()    GPIO_GetVal(GPIO_PORT_8,GPIO_PIN_3)
#define CAN_GET_INH()    GPIO_GetVal(GPIO_PORT_8,GPIO_PIN_4)


#define CANL_SET_STB() GPIO_SetVal(GPIO_PORT_11, GPIO_PIN_4, TRUE)
#define CANL_CLR_STB() GPIO_SetVal(GPIO_PORT_11, GPIO_PIN_4, FALSE)
#define CANL_SET_EN()	GPIO_SetVal(GPIO_PORT_9, GPIO_PIN_6, TRUE)
#define CANL_CLR_EN()	GPIO_SetVal(GPIO_PORT_9, GPIO_PIN_6, FALSE)

extern void can_irq_enable(void);
extern void can_irq_disable(void);
extern U8 CanDriver_Open(void);
extern U8 CanDriver_Close(void);
extern U8 CanDriver_Control(U8 type, void* buffer);
extern void CanDriver_powercontrol(E_DEV_POWER type);
extern U8 CanDriver_GetpowerStatus(void);
extern void CanDriver_10ms_Entry(void);
extern void CanDriver_Init(void);
extern void CanDriver_SetBusOffState(BOOL bBusOff);
#endif

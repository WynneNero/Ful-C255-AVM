/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									   *
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
* Version     Date         Name              Changes and comments
* V0.1		  2017/6/29    Zheng Xiaolei     Init Version
*=====================================================================*/
#ifndef _POWER_MANAGER_H_
#define _POWER_MANAGER_H_

#define ACC_MASK_ON_TIMES_DEBOUNCE 6
#define ACC_MASK_OFF_TIMES_DEBOUNCE 10
typedef enum
{
    VOL_INVALID_VALUE=0x100,
    VOL_6V_VALUE=0X302,  
    VOL_9V_VALUE=0X46B,		
    VOL_16V_VALUE=0X832,
    VOL_MAX_VALUE=0XFFFF,
    VOL_UNKNOWN
}E_SYSTEM_VOLTAGE_STATU_VALUSE;
E_SYSTEM_VOLTAGE_STATUS GetPowerVoltageStatus(void);
void UpdateACCStatus(void);
U8 get_hw_ACC_status(void);
U8 get_can_ACC_status(void);

#endif /*_POWER_MANAGER_H_*/

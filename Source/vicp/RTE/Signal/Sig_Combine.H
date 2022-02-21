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
* Version       Date    Name    Changes and comments
*----------------------------------------------------------------------
* 0.1   Aug 31,2016             Re-init
*----------------------------------------------------------------------
* 0.2    Dec 20,2016   ShangQiuju Remove unused include files.
*----------------------------------------------------------------------
* 0.3   Jan 05,2017   ShangQiuju  Add functions.          
*----------------------------------------------------------------------
* 0.4    Jan 24,2017   ZhangJie     Fix Coverity warnings.   
*=====================================================================*/
#ifndef _SIG_COMBINE_H_
#define _SIG_COMBINE_H_ 
#include <Core_I.h> 
#include "config.h"


/**** Definition of constants ****/


/**** Definition of macros ****/
/* Signal definition  and please check the hardware channel with the comment*/
typedef enum
{	
	/*=====Signal Name=========ADC Channel Used==ADC Group dividid=*/
	SIG_COMBINE_ACCSTATUS,
    SIG_COMBINE_WAKEUPREASION,		/*WAKE UP REASON*/
	SIG_COMBINE_SYSTEMSTATE,			/*SYSTEM STATE*/
	SIG_COMBINE_VOLTAGESTATUS,		/*SYSTEM VOLTAGE STATUS*/
	SIG_COMBINE_SLEEPALLOW,			/*SLEEP ALLOW OR NOT*/

	SIG_COMBINE_POWERONREQ,  	      /*SYSTEM POWER ON REQUEST*/ 
   	SIG_COMBINE_WAKEUPREQ,  	     	      /*SYSTEM WAKE UP REQUEST*/   
   	SIG_COMBINE_SLEEPREQ,     		      /*SYSTEM SLEEP REQUEST*/   
   	SIG_COMBINE_EEPROMCOMMUFAIL,

	SIG_COMBINE_CANIN_ACC,               /*for Geely*/
	SIG_COMBINE_HWIN_ACC,
	SIG_COMBINE_AVM_TURNON_FLAG,

	SIG_COMBINE_SOC_POWER_ON,
    SIG_COMBINE_SOC_CONNECTED_STATUS,
    SIG_COMBINE_NAVICOMMU_FAIL,
    SIG_COMBINE_ROTATION_ANGLE,
    //CAM
    SIG_COMBINE_CAMERA_CONTROL,
    SIG_COMBINE_CAMERA_ONOFF,
    
    //CAN
    SIG_COMBINE_CAN_TRANSIEVER_ERROR,
    SIG_COMBINE_CAN_VEHICLE_SPEED_VALIDITY,
    SIG_COMBINE_CAN_STEERING_WHEEL_ANGLE_VALIDITY,
    SIG_COMBINE_CAN_OVER_VOLTAGE_FLAG,
    
	#ifdef EOL_OPTION
	SIG_COMBINE_EOL_ACTIVE_STATUS,
	#endif
	SIG_COM_NUM            
}E_CombineType;

typedef enum
{
    SYSTEM_RESET,
    SYSTEM_NORMAL,
    SYSTEM_SLEEP,
    SYSTEM_FCTTEST,
    SYSTEM_MODESWITCH,
    SYSTEM_MAXSTATE
}E_SYSTEMSTATE_TYPE;

typedef enum
{
    WAKEUP_NONE,
    WAKEUP_ACCON,	
    WAKEUP_CANIN,
    WAKEUP_REVERSE,
    WAKEUP_MAXTYPE,	
}E_WAKEUP_REASON;

enum
{
	ACC_OFF,
//	ACC_ON,
	ACC_UNKNOW
};

//typedef enum
//{
//    VOLTAGE_ABNORMAL,		//<6v or >16v
//    VOLTAGE_LOWER,			//6V-9V
//    VOLTAGE_NORMAL,   		//9-16V
//    VOLTAGE_UNKNOWN
//}E_SYSTEM_VOLTAGE_STATUS;


typedef enum
{
	V_INIT,
	V_L_ABNORMAL,
	V_LOW,
	V_NORMAL,
	V_HIGH,
	V_H_ABNORMAL,
}E_SYSTEM_VOLTAGE_STATUS;



typedef enum
{
	RVC_OPEN,
	RVC_NORMAL,
	RVC_OVERCURRENT,
	RVC_SHORTCIRCUIT,
	RVC_ABNORMAL,
	RVC_UNKNOWN
}E_RVC_STATUS;

typedef enum
{
	TUNER_OPEN,
	TUNER_NORMAL,
	TUNER_OVERCURRENT,
	TUNER_SHORTCIRCUIT,
	TUNER_ABNORMAL,
	TUNER_UNKNOWN
}E_TUNER_STATUS;

/**** Declaration of variables ****/

/**** Declaration of functions ****/
extern U8 Sig_CombineGetValue( U16 sig, U16* value);
extern void Sig_CombineSetValue( U16 sig, U8* value);
extern U8 Sig_CombineGetDirectValue( U16 sig, U8* value);
extern void Sig_CombineSetDirectValue( U16 sig, U8* value);
#endif /*_SIG_COMBINE_H_*/

/****************************** END OF FILE ***************************/


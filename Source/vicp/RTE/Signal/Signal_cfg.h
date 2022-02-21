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
 ----------------------------------------------------------------------
* 0.1    Jun 26,2016    PEI Jingli  Initial version
 ----------------------------------------------------------------------
* 0.2    Aug 01,2016    PEI Jingli  add signal
 ----------------------------------------------------------------------
* 0.3    Jan 05,2017    ShangQiuju Remove unused include file.
*------------------------------------------------------------------------
* 0.4    Jan 24,2017  ZhangJie  Fix Coverity warnings.
*----------------------------------------------------------------------
* 0.5    Feb 14,2017   ZhangJie   Divide digital signal to input and output.  
* ----------------------------------------------------------------------
* 0.8    Apr 13,2017   ZhangJie  Use SIG_DO_CAN_WAKE for example.
*=====================================================================*/
/**** Definition of constants ****/
#include "Sig_Combine.h"
#include "IoSystem_IF.h"
#include "CONFIG.H" 
/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/
BEGIN_SIG
/*Global name, soure name, signal type*/

/*ADC*/
SIGDESC(SIG_APP_PWR,	    	        SIG_AD_PWR,     	              E_SIG_ADC)
SIGDESC(SIG_APP_TEMP,	    	        SIG_AD_TEMP,                      E_SIG_ADC)
SIGDESC(SIG_CAMERA_F_DI_STA,			SIG_AD_CAMERA_F_PWR,			  E_SIG_ADC)
SIGDESC(SIG_CAMERA_L_DI_STA,			SIG_AD_CAMERA_L_PWR,			  E_SIG_ADC)
SIGDESC(SIG_CAMERA_B_DI_STA,			SIG_AD_CAMERA_B_PWR,			  E_SIG_ADC)
SIGDESC(SIG_CAMERA_R_DI_STA,			SIG_AD_CAMERA_R_PWR,			  E_SIG_ADC)
SIGDESC(SIG_AVM_LED_STATUS,			    SIG_AD_AVM_LED_STATUS,			  E_SIG_ADC)
/*Digital OUTPUT*/
SIGDESC(SIG_CAN_DO_WAKE,                SIG_DO_CAN_WAKE,                  E_SIG_DO)
SIGDESC(SIG_CAN_DO_EN,                  SIG_DO_CAN_EN,                    E_SIG_DO)
SIGDESC(SIG_CAMERA_F_DO_EN,             SIG_DO_CAMERA_F_EN,               E_SIG_DO)
SIGDESC(SIG_CAMERA_B_DO_EN,             SIG_DO_CAMERA_B_EN,               E_SIG_DO)
SIGDESC(SIG_CAMERA_L_DO_EN,             SIG_DO_CAMERA_L_EN,               E_SIG_DO)
SIGDESC(SIG_CAMERA_R_DO_EN,             SIG_DO_CAMERA_R_EN,               E_SIG_DO)
SIGDESC(SIG_BUZZER_DO_EN,               SIG_DO_BUZZER_EN,                 E_SIG_DO)
SIGDESC(SIG_SLC_DO_EN,                  SIG_DO_SLC_EN,                    E_SIG_DO)
SIGDESC(SIG_PS_5V0_DO_EN,               SIG_DO_PS_5V0_EN,                 E_SIG_DO)
SIGDESC(SIG_PMIC_DO_EN,                 SIG_DO_PMIC_EN,                   E_SIG_DO)
SIGDESC(SIG_ISP_LVDS_1V8_DO_EN,         SIG_DO_ISP_LVDS_1V8_EN,           E_SIG_DO)
SIGDESC(SIG_ISP_LVDS_3V3_DO_EN,         SIG_DO_ISP_LVDS_3V3_EN,           E_SIG_DO)
SIGDESC(SIG_FPD_LINK_1V1_DO_EN,         SIG_DO_FPD_LINK_1V1_EN,           E_SIG_DO)
SIGDESC(SIG_FPD_LINK_1V8_DO_EN,         SIG_DO_FPD_LINK_1V8_EN,           E_SIG_DO)
SIGDESC(SIG_DISPLAY_DO_REQ,             SIG_DO_SOC_RVC,                   E_SIG_DO)

/*Digital INPUT*/
SIGDESC(SIG_SOCWDG_DI_STATUS,           SIG_DI_SOCWDG,                     E_SIG_DI)
SIGDESC(SIG_ACC_DI_STATUS,              SIG_DI_ACC,                        E_SIG_DI)
SIGDESC(SIG_BUZZER2_DI_STA,             SIG_DI_BUZZER2_STA_DET,            E_SIG_DI)
SIGDESC(SIG_BUZZER1_DI_STA,             SIG_DI_BUZZER1_STA_DET,            E_SIG_DI)
//SIGDESC(SIG_CAMERA_B_DI_STA,            SIG_DI_CAMERA_B_PWR_DET,           E_SIG_ADC)
//SIGDESC(SIG_CAMERA_F_DI_STA,            SIG_DI_CAMERA_F_PWR_DET,           E_SIG_ADC)
//SIGDESC(SIG_CAMERA_R_DI_STA,            SIG_DI_CAMERA_R_PWR_DET,           E_SIG_ADC)
//SIGDESC(SIG_CAMERA_L_DI_STA,            SIG_DI_CAMERA_L_PWR_DET,           E_SIG_ADC)
SIGDESC(SIG_CANERA_DVR_DI_STA,          SIG_DI_CANERA_DVR_PWR_DET,         E_SIG_DI)
SIGDESC(SIG_LED1_DI_STA,                SIG_DI_LED1_PWR_DET,               E_SIG_DI)
SIGDESC(SIG_LED0_DI_STA,                SIG_DI_LED0_PWR_DET,               E_SIG_DI)
SIGDESC(SIG_REVERSE_DI_STA,             SIG_DI_REVERSE,                    E_SIG_DI)
SIGDESC(SIG_TURNLEFT_DI_STA,            SIG_DI_TURNLEFT,                   E_SIG_DI)
SIGDESC(SIG_TURNRIGHT_DI_STA,           SIG_DI_TURNRIGHT,                  E_SIG_DI)
SIGDESC(SIG_CAMERA_DVR_DI_EN,			SIG_DI_CAMERA_DVR_EN,		  	   E_SIG_DI)
SIGDESC(SIG_SPEED_DI_STA,               SIG_DI_SPEED,                      E_SIG_DI)

/*Combine*/
/*power sig*/
SIGDESC(SIG_ACCSTATUS,                  SIG_COMBINE_ACCSTATUS,              E_SIG_COMBINE)
SIGDESC(SIG_ACC_CAN_IN_STATUS,			SIG_COMBINE_CANIN_ACC, 				E_SIG_COMBINE)	
SIGDESC(SIG_ACC_HW_IN_STATUS,			SIG_COMBINE_HWIN_ACC, 				E_SIG_COMBINE)

/*app*/
/*status*/
SIGDESC(SIG_SYSTEM_STATUS,                   SIG_COMBINE_SYSTEMSTATE,                 E_SIG_COMBINE)
SIGDESC(SIG_VOLTAGEFAIL_STATUS,              SIG_COMBINE_VOLTAGESTATUS,               E_SIG_COMBINE)

/*sleep*/
SIGDESC(SIG_WAKEUP_REASON,                   SIG_COMBINE_WAKEUPREASION,               E_SIG_COMBINE)
SIGDESC(SIG_SLEEP_ALLOW,                     SIG_COMBINE_SLEEPALLOW,                  E_SIG_COMBINE)

/*req*/
SIGDESC(SIG_POWERON_REQ,                     SIG_COMBINE_POWERONREQ,                  E_SIG_COMBINE)
SIGDESC(SIG_WAKEUP_REQ,                      SIG_COMBINE_WAKEUPREQ,                   E_SIG_COMBINE)
SIGDESC(SIG_SLEEP_REQ,                       SIG_COMBINE_SLEEPREQ,                    E_SIG_COMBINE)

//soc
SIGDESC(SIG_B_SOC_POWER_ON,             SIG_COMBINE_SOC_POWER_ON,           E_SIG_COMBINE)
SIGDESC(SIG_B_SOC_CONNECTED,            SIG_COMBINE_SOC_CONNECTED_STATUS,   E_SIG_COMBINE)
SIGDESC(SIG_B_NAVICOMMERROR ,			SIG_COMBINE_NAVICOMMU_FAIL, 		E_SIG_COMBINE)
SIGDESC(SIG_2F_ROTATION_ANGLE ,			SIG_COMBINE_ROTATION_ANGLE, 		E_SIG_COMBINE)

//led
SIGDESC(SIG_AVM_TURNON_FLAG ,			SIG_COMBINE_AVM_TURNON_FLAG, 		E_SIG_COMBINE)

//cam
SIGDESC(SIG_2F_CAMERA_CONTROL ,			SIG_COMBINE_CAMERA_CONTROL, 		E_SIG_COMBINE)
SIGDESC(SIG_CAMERA_ONOFF , 				SIG_COMBINE_CAMERA_ONOFF, 			E_SIG_COMBINE)

/*can*/
SIGDESC(SIG_CAN_TRANSIEVER_ERROR_STATUS, 		SIG_COMBINE_CAN_TRANSIEVER_ERROR, 				E_SIG_COMBINE)
SIGDESC(SIG_CAN_VEHICLE_SPEED_VALIDITY, 		SIG_COMBINE_CAN_VEHICLE_SPEED_VALIDITY, 		E_SIG_COMBINE)
SIGDESC(SIG_CAN_STEERING_WHEEL_ANGLE_VALIDITY, 	SIG_COMBINE_CAN_STEERING_WHEEL_ANGLE_VALIDITY, 	E_SIG_COMBINE)
SIGDESC(SIG_CAN_OVER_VOLTAGE_FLAG,				SIG_COMBINE_CAN_OVER_VOLTAGE_FLAG,				E_SIG_COMBINE)

/*eep*/
SIGDESC(SIG_B_EEPROMCOMMUFAIL,               SIG_COMBINE_EEPROMCOMMUFAIL,             E_SIG_COMBINE)


#ifdef EOL_OPTION
 SIGDESC(SIG_EOL_ACTIVE_STATUS,         SIG_COMBINE_EOL_ACTIVE_STATUS,      E_SIG_COMBINE)
#endif

END_SIG

#undef  BEGIN_SIG
#undef  END_SIG
#undef  SIGDESC


/****************************** END OF FILE ***************************/


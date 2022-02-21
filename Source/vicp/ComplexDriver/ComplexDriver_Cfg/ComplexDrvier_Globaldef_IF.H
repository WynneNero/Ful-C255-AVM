/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   : Shao Guangxian										   *
************************************************************************
* Object        : Complex driver.h
* Module        :
* Instance      :
* Description   :
*-----------------------------------------------------------------------
* Version:  0.1
* Date: 2011-11-24
* Author: Shao Guangxian
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
*
*=====================================================================*/
#ifndef _COMPLEXDRIVER_GLOBALDEF_IF_H
#define _COMPLEXDRIVER_GLOBALDEF_IF_H

#include "CONFIG.H"

/************GPIO DEFINE ****************/

//#define CHECK_POWER_CAMERA_EABLE_FLAG     GPIO_GetVal(GPIO_PORT_11,GPIO_PIN_0)   
#define IS_SOC_POWERON					  GPIO_GetVal(GPIO_PORT_10, GPIO_PIN_2)
#define CHECK_LM53601_RESET_PIN_FLAG 	  GPIO_GetVal(AP_PORT_0, GPIO_PIN_7)

#define POWER_CAMERA_ALL_ON() 	     GPIO_SetVal(GPIO_PORT_11, GPIO_PIN_0, TRUE)
#define POWER_CAMERA_ALL_OFF() 	     GPIO_SetVal(GPIO_PORT_11, GPIO_PIN_0, FALSE)

#define POWER_CAMERA_F_ON() 	     GPIO_SetVal(GPIO_PORT_10, GPIO_PIN_5, TRUE)
#define POWER_CAMERA_F_OFF() 	     GPIO_SetVal(GPIO_PORT_10, GPIO_PIN_5, FALSE)

#define POWER_CAMERA_B_ON() 	     GPIO_SetVal(GPIO_PORT_10, GPIO_PIN_F, TRUE)
#define POWER_CAMERA_B_OFF() 	     GPIO_SetVal(GPIO_PORT_10, GPIO_PIN_F, FALSE)

#define POWER_CAMERA_R_ON() 	     GPIO_SetVal(GPIO_PORT_10, GPIO_PIN_4, TRUE)
#define POWER_CAMERA_R_OFF() 	     GPIO_SetVal(GPIO_PORT_10, GPIO_PIN_4, FALSE)

#define POWER_CAMERA_L_ON() 	     GPIO_SetVal(GPIO_PORT_10, GPIO_PIN_3, TRUE)
#define POWER_CAMERA_L_OFF() 	     GPIO_SetVal(GPIO_PORT_10, GPIO_PIN_3, FALSE)

#define POWER_CAMERA_DVR_ON() 	     //GPIO_SetVal(GPIO_PORT_11, GPIO_PIN_0, TRUE)
#define POWER_CAMERA_DVR_OFF() 	     //GPIO_SetVal(GPIO_PORT_11, GPIO_PIN_0, FALSE)

#define POWER_BUZZER_ON() 	         GPIO_SetVal(GPIO_PORT_0, GPIO_PIN_5, TRUE)
#define POWER_BUZZER_OFF() 	         GPIO_SetVal(GPIO_PORT_0, GPIO_PIN_5, FALSE)

#define POWER_5V0_ON() 	             GPIO_SetVal(GPIO_PORT_0, GPIO_PIN_A, TRUE)
#define POWER_5V0_OFF() 	         GPIO_SetVal(GPIO_PORT_0, GPIO_PIN_A, FALSE)
 
//#define MAX9286_PWDN_INACTIVE()        GPIO_SetVal(GPIO_PORT_0, GPIO_PIN_A, TRUE)
//#define MAX9286_PWDN_ACTIVE()          GPIO_SetVal(GPIO_PORT_0, GPIO_PIN_A, FALSE)

#define POWER_ISP_LVDS_1V8_ON() 	 GPIO_SetVal(GPIO_PORT_10, GPIO_PIN_1, TRUE)
#define POWER_ISP_LVDS_1V8_OFF() 	 GPIO_SetVal(GPIO_PORT_10, GPIO_PIN_1, FALSE)

#define POWER_ISP_LVDS_3V3_ON() 	 GPIO_SetVal(GPIO_PORT_10, GPIO_PIN_0, TRUE)
#define POWER_ISP_LVDS_3V3_OFF() 	 GPIO_SetVal(GPIO_PORT_10, GPIO_PIN_0, FALSE)

#define POWER_FPD_LINK_1V1_ON() 	 GPIO_SetVal(GPIO_PORT_11, GPIO_PIN_4, TRUE)
#define POWER_FPD_LINK_1V1_OFF() 	 GPIO_SetVal(GPIO_PORT_11, GPIO_PIN_4, FALSE)

#define POWER_FPD_LINK_1V8_ON() 	 GPIO_SetVal(GPIO_PORT_11, GPIO_PIN_3, TRUE)
#define POWER_FPD_LINK_1V8_OFF() 	 GPIO_SetVal(GPIO_PORT_11, GPIO_PIN_3, FALSE)

#define POWER_PMIC_ON()	             GPIO_SetVal(GPIO_PORT_10, GPIO_PIN_2, TRUE)
#define POWER_PMIC_OFF()	         GPIO_SetVal(GPIO_PORT_10, GPIO_PIN_2, FALSE)

#define POWER_SOC_LOW_ON()	         GPIO_SetVal(GPIO_PORT_0, GPIO_PIN_9, TRUE)
#define POWER_SOC_LOW_OFF()	         GPIO_SetVal(GPIO_PORT_0, GPIO_PIN_9, FALSE)
 
#define UPDATE_OS_START()	         GPIO_SetVal(GPIO_PORT_8, GPIO_PIN_6, TRUE)
#define UPDATE_OS_STOP()	         GPIO_SetVal(GPIO_PORT_8, GPIO_PIN_6, FALSE)

#define GET_INH_VALUE() 	 		 GPIO_GetVal(GPIO_PORT_10, GPIO_PIN_9)

#define DELAY300MSCNT                   15


#endif /*_COMPLEXDRIVER_GLOBALDEF_H*/

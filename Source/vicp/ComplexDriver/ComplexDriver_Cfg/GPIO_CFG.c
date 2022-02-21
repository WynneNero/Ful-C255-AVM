/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   : Shao Guangxian										   *
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
* 0.1    Jun 26,2016   PEI Jingli  Initial version
* ----------------------------------------------------------------------
* 0.2    Aug 01,2016   PEI Jingli  Add INTP callback
*----------------------------------------------------------------------
* 0.3    Dec 20,2016   add config according using hw
* ----------------------------------------------------------------------
* 0.4    Dec 22,2016   PEI Jingli  Add HW switch of ds03 and 64pin-platform
* ----------------------------------------------------------------------
* 0.5    Jan 06,2017   ShangQiuju  Remove HW switch of ds03 and 64pin-platform,this 
                                 file only used for plaform.
* ----------------------------------------------------------------------
* 0.6    Jan 24,2017   ZhangJie  Remove unused array members.
* ----------------------------------------------------------------------
* 0.7    Apr 13,2017   ZhangJie  Use SIG_DI_CAN_ERR and SIG_DO_CAN_WAKE for example.
*=====================================================================*/
#include <config.h>
#include "GPIO_if.h"
#include "GPIO_cfg.h"

const Sig_DioChannelInConfigType Sig_InConfig[SIG_DIO_IN_NUM]=
{
	{TRUE, GPIO_PORT_8, GPIO_PIN_5, E_DIO}//,SIG_DI_SOCWDG
 	,{TRUE, GPIO_PORT_8, GPIO_PIN_0, E_DIO}//,SIG_DI_ACC
 	,{TRUE, AP_PORT_0, GPIO_PIN_1, E_DIO} //SIG_DI_BUZZER2_STA_DET
 	,{TRUE, AP_PORT_0, GPIO_PIN_2, E_DIO} //SIG_DI_BUZZER1_STA_DET
// 	,{TRUE, AP_PORT_0, GPIO_PIN_3, E_DIO} //SIG_DI_CAMERA_B_PWR_DET
// 	,{TRUE, AP_PORT_0, GPIO_PIN_4, E_DIO} //SIG_DI_CAMERA_F_PWR_DET
// 	,{TRUE, AP_PORT_0, GPIO_PIN_5, E_DIO} //SIG_DI_CAMERA_R_PWR_DET
// 	,{TRUE, AP_PORT_0, GPIO_PIN_6, E_DIO} //SIG_DI_CAMERA_L_PWR_DET
 	,{TRUE, AP_PORT_0, GPIO_PIN_7, E_DIO} //SIG_DI_CANERA_DVR_PWR_DET
 	,{TRUE, GPIO_PORT_8, GPIO_PIN_7, E_DIO} //SIG_DI_LED1_PWR_DET
 	,{TRUE, GPIO_PORT_8, GPIO_PIN_8, E_DIO} //SIG_DI_LED0_PWR_DET
 	,{TRUE, GPIO_PORT_8, GPIO_PIN_1, E_DIO} //SIG_DI_REVERSE
 	,{TRUE, GPIO_PORT_8, GPIO_PIN_3, E_DIO} //SIG_DI_TURNLEFT
 	,{TRUE, GPIO_PORT_8, GPIO_PIN_4, E_DIO} //SIG_DI_TURNRIGHT
 	,{TRUE, GPIO_PORT_11, GPIO_PIN_0, E_DIO} //SIG_DI_CAMERA_DVR_EN
 	,{TRUE, GPIO_PORT_11, GPIO_PIN_1, E_DIO} //SIG_DI_SPEED
	
};
 
const Sig_DioChannelOutConfigType Sig_OutConfig[SIG_DIO_OUT_NUM]=
{
  { GPIO_PORT_10,GPIO_PIN_A,E_DIO} //SIG_DO_CAN_WAKE      
 ,{ GPIO_PORT_10,GPIO_PIN_C,E_DIO} //,SIG_DO_CAN_EN
 ,{ GPIO_PORT_10,GPIO_PIN_3,E_DIO} //SIG_DO_CAMERA_F_EN
 ,{ GPIO_PORT_10,GPIO_PIN_4,E_DIO} //SIG_DO_CAMERA_B_EN
 ,{ GPIO_PORT_10,GPIO_PIN_5,E_DIO} //SIG_DO_CAMERA_L_EN
 ,{ GPIO_PORT_10,GPIO_PIN_F,E_DIO} //SIG_DO_CAMERA_R_EN
 ,{ GPIO_PORT_0,GPIO_PIN_5,E_DIO} //SIG_DO_BUZZER_EN
 ,{ GPIO_PORT_0,GPIO_PIN_6,E_DIO} //SIG_DO_SLC_EN
 ,{ GPIO_PORT_0,GPIO_PIN_A,E_DIO} //SIG_DO_PS_5V0_EN
 ,{ GPIO_PORT_10,GPIO_PIN_2,E_DIO} //SIG_DO_PMIC_EN
 ,{ GPIO_PORT_11,GPIO_PIN_6,E_DIO} // SIG_DO_ISP_LVDS_1V8_EN
 ,{ GPIO_PORT_11,GPIO_PIN_5,E_DIO} //SIG_DO_ISP_LVDS_3V3_EN
 ,{ GPIO_PORT_11,GPIO_PIN_4,E_DIO} // SIG_DO_FPD_LINK_1V1_EN
 ,{ GPIO_PORT_11,GPIO_PIN_3,E_DIO} // SIG_DO_FPD_LINK_1V8_EN
 ,{ GPIO_PORT_10,GPIO_PIN_E,E_DIO} // SIG_DO_SOC_RVC
};

/**************** END OF FILE *****************************************/


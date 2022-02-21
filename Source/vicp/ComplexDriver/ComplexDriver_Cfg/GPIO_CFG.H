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
* 0.1    Feb 10,2013    NI Rujin    Initial version
* ----------------------------------------------------------------------
* 0.2    JUN 6,2015    Shang Qiuju  Add signal configuration
*----------------------------------------------------------------------
* 0.3    Dec 20,2016   add config according using hw
*----------------------------------------------------------------------
* 0.4    Dec 22,2016   Pei Jingli    add 64pin hw switch 
* ----------------------------------------------------------------------
* 0.5    Jan 06,2017   ShangQiuju  Remove HW switch of ds03 and 64pin-platform,this 
                                 file only used for plaform.
  * ----------------------------------------------------------------------
* 0.6    Jan 12,2017   ZhangJie  Remove unused typedef and enum to avoid Coverity warnings.
*-----------------------------------------------------------------------
* 0.7    Jan 24,2017    ZhangJie     Remove unused include headfile.
*----------------------------------------------------------------------
* 0.8   Apr 13,2017   ZhangJie  Use SIG_DI_CAN_ERR and SIG_DO_CAN_WAKE for example.
*=====================================================================*/
#ifndef _GPIO_CFG_H_
#define _GPIO_CFG_H_
#include <config.h>
#include "Define.h"

/**** Definition of constants ****/
/**** Definition of types ****/
/* Signal definition  and please check the hardware channel with the comment*/
typedef enum
{	
   SIG_DO_CAN_WAKE  
  ,SIG_DO_CAN_EN
  ,SIG_DO_CAMERA_F_EN
  ,SIG_DO_CAMERA_B_EN
  ,SIG_DO_CAMERA_L_EN
  ,SIG_DO_CAMERA_R_EN
  ,SIG_DO_BUZZER_EN
  ,SIG_DO_SLC_EN
  ,SIG_DO_PS_5V0_EN
  ,SIG_DO_PMIC_EN
  ,SIG_DO_ISP_LVDS_1V8_EN
  ,SIG_DO_ISP_LVDS_3V3_EN
  ,SIG_DO_FPD_LINK_1V1_EN
  ,SIG_DO_FPD_LINK_1V8_EN
  ,SIG_DO_SOC_RVC
  ,SIG_DIO_OUT_NUM         
}E_DioOutType;

/* Signal definition  and please check the hardware channel with the comment*/
typedef enum
{	
 	 SIG_DI_SOCWDG
	,SIG_DI_ACC
	,SIG_DI_BUZZER2_STA_DET
	,SIG_DI_BUZZER1_STA_DET
//	,SIG_DI_CAMERA_B_PWR_DET
//	,SIG_DI_CAMERA_F_PWR_DET
//	,SIG_DI_CAMERA_R_PWR_DET
//	,SIG_DI_CAMERA_L_PWR_DET
	,SIG_DI_CANERA_DVR_PWR_DET
	,SIG_DI_LED1_PWR_DET
	,SIG_DI_LED0_PWR_DET
	,SIG_DI_REVERSE
	,SIG_DI_TURNLEFT
	,SIG_DI_TURNRIGHT
	,SIG_DI_CAMERA_DVR_EN
	,SIG_DI_SPEED
 	,SIG_DIO_IN_NUM         
}E_DioInType;


typedef enum
{
E_DIO,
E_BUFFERIO,
E_IODEVICE_NUMBER
}E_DioDeviceType;


/**** Declaration of variables ****/
typedef struct
{
    BOOL Damp;
    U8 PortHnumb;
    U8 PortLnumb;
    E_DioDeviceType DeviceType;      
}Sig_DioChannelInConfigType;

typedef struct
{
    U8 PortHnumb;
    U8 PortLnumb;
    E_DioDeviceType DeviceType;      
}Sig_DioChannelOutConfigType;


extern const Sig_DioChannelInConfigType Sig_InConfig[SIG_DIO_IN_NUM];

extern const Sig_DioChannelOutConfigType Sig_OutConfig[SIG_DIO_OUT_NUM];

/**** Declaration of functions ****/

#endif
/****************************** END OF FILE ***************************/


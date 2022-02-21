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
* Version       Date    Name         Changes and comments
* ----------------------------------------------------------------------
* 0.1    Jan 10,2016                    ReInit
* ----------------------------------------------------------------------
* 0.2    Oct 10,2016  PEI Jingli     add pwm,pwd,capture interface
* ----------------------------------------------------------------------
* 0.3    Jan 4,2017    ShangQiuju Update for error config.  
*-----------------------------------------------------------------------
* 0.4    Jan 24,2017  ZhangJie  Fix Coverity warnings.
* ----------------------------------------------------------------------
* 0.5    Feb 09,2017  PEI Jingli     Add device of pwmd 
* ----------------------------------------------------------------------
* 0.6    Feb 15,2017  ShangQiuju Remove devie fdl from dev to devblock.  
* ----------------------------------------------------------------------
* 0.7    Feb 20,2017    PEI Jingli     Add device of TAU-Pwm,capture, timer 
* ----------------------------------------------------------------------
* 0.8    Feb 20,2017  ZhangJie     Add device of CAN. 
*=====================================================================*/
#include "Hal.h"
#include "SocDriver_IF.h"
#include "EEPDriver_IF.h"
#include "Pwmd_ComplexDriver_IF.h"
#include "TauPwm_ComplexDriver_if.h"
#include "Capture_ComplexDriver_if.h"
#include "HwTimer_ComplexDriver_if.h"
#include "CanDriver_if.h"
#include "EOLUartDriver_if.h"
#include "M4UartDriver_IF.H"

/*---Global-----------------------------------------------------------*/

const V_hal_open HalOpenProc[HAL_DEV_MAX]=
{
	SocDriver_Open,
	NULL,/*DEV_PWMD_HW*/
	NULL,/*DEV_PWMD_TAU*/
	NULL,/*DEV_CAPTURE*/
	NULL,/*DEV_HW_TIMER*/
	CanDriver_Open,/*DEV_HW_TIMER*/
	#ifdef EOL_OPTION
	EolUartDriver_Open,/*DEV_EOLDRIVER*/  
	#endif
	NULL,//FDL
	M4UartDriver_Open,  //Do not remove
	NULL  //Do not remove
};

const V_hal_close  HalCloseProc[HAL_DEV_MAX]=
{
	SocDriver_Close,
	NULL,/*DEV_PWMD_HW*/
	NULL,/*DEV_PWMD_TAU*/
	NULL,/*DEV_CAPTURE*/
	NULL,/*DEV_HW_TIMER*/
	CanDriver_Close,/*DEV_CANDRIVER*/
	#ifdef EOL_OPTION
	EolUartDriver_Close,/*DEV_EOLDRIVER*/  
	#endif
	NULL,//FDL
	M4UartDriver_Close,
	NULL  //Do not remove
};

const V_hal_read HalReadProc[HAL_DEV_MAX]=
{
	SocDriver_Read,
	NULL,/*DEV_PWMD_HW*/
	NULL,/*DEV_PWMD_TAU*/
	NULL,/*DEV_CAPTURE*/
	NULL,/*DEV_HW_TIMER*/
	NULL,/*DEV_CANDRIVER*/
	#ifdef EOL_OPTION
	EolUartDriver_Read,/*DEV_EOLDRIVER*/  
	#endif
	FDLDriver_Read_Upgrade_flag,/*FDL*/
	M4UartDriver_Read,
	NULL,  //Do not remove
};

const V_hal_write  HalWriteProc[HAL_DEV_MAX]=
{
	SocDriver_Write,
	NULL,/*DEV_PWMD_HW*/
	NULL,/*DEV_PWMD_TAU*/
	NULL,/*DEV_CAPTURE*/
	NULL,/*DEV_HW_TIMER*/
	NULL,/*DEV_CANDRIVER*/
	#ifdef EOL_OPTION
	EolUartDriver_Write,/*DEV_EOLDRIVER*/  
	#endif
	FDLDriver_Write_Upgrade_flag,/*FDL*/
	M4UartDriver_Write,
	NULL  //Do not remove
};

const V_hal_iocontrol HaliocontrolProc[HAL_DEV_MAX]=
{
	NULL, //SOC
	Pwmd_ComplexDriver_IOControl, /*DEV_PWMD_HW*/
	TauPwm_ComplexDriver_IOControl,/*DEV_PWMD_TAU*/
	Capture_ComplexDriver_IOControl,/*DEV_CAPTURE*/
	HwTimer_ComplexDriver_IOControl,/*DEV_HW_TIMER*/
	CanDriver_Control,/*DEV_CANDRIVER*/
	NULL, /*DEV_EOLDRIVER*/  
	NULL, /*FDL*/
	NULL  //Do not remove
};

const V_hal_powercontrol HalPowerControlProc[HAL_DEV_MAX]=
{
	SocDriver_powercontrol,
	NULL,/*DEV_PWMD_HW*/
	NULL,/*DEV_PWMD_TAU*/
	NULL,/*DEV_CAPTURE*/
	NULL,/*DEV_HW_TIMER*/
	CanDriver_powercontrol,/*DEV_CANDRIVER*/
	NULL, /*DEV_EOLDRIVER*/  
	NULL, /*FDL*/ 
	NULL  //Do not remove
};

const V_hal_powerstatus HalPowerStatusProc[HAL_DEV_MAX]=
{
	SocDriver_GetpowerStatus,
	NULL,/*DEV_PWMD_HW*/
	NULL,/*DEV_PWMD_TAU*/
	NULL,/*DEV_CAPTURE*/
	NULL,/*DEV_HW_TIMER*/
	CanDriver_GetpowerStatus,/*DEV_CANDRIVER*/
	NULL, /*DEV_EOLDRIVER*/ 
	NULL, /*FDL*/ 
	NULL  /*Do not remove*/
};

/*Block device:*/
const V_hal_block_open HalBlockOpenProc[HAL_BLDEV_MAX]=
{
//	NULL,/*FDL*/
	NULL  /*Do not remove*/
};

const V_hal_block_close  HalBlockCloseProc[HAL_BLDEV_MAX]=
{
//	NULL,/*FDL*/
	NULL  /*Do not remove*/
};

const V_hal_block_read HalBlockReadProc[HAL_BLDEV_MAX]=
{
//	NULL, //FDLDriver_Read,/*FDL*/
	NULL  /*Do not remove*/
};

const V_hal_block_write  HalBlockWriteProc[HAL_BLDEV_MAX]=
{
//	NULL, //FDLDriver_Write,/*FDL*/
	NULL  /*Do not remove*/
};

const V_hal_block_iocontrol HalBlockiocontrolProc[HAL_BLDEV_MAX]=
{
//	NULL,/*FDL*/
	NULL  /*Do not remove*/
};

const V_hal_block_powercontrol HalBlockPowerControlProc[HAL_BLDEV_MAX]=
{
//	NULL,/*FDL*/
	NULL  /*Do not remove*/
};


const V_hal_block_powerstatus HalBlockPowerStatusProc[HAL_BLDEV_MAX]=
{
//	NULL,/*FDL*/
	NULL  /*Do not remove*/
};


/**************** END OF FILE *****************************************/


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
*------------------------------------------------------------------------
* 0.3    Jan 24,2017  ZhangJie  Update for Coverity warnings.
*=====================================================================*/
#include "ADC_CFG.H"

const Sig_ADChannelConfigType Sig_ADConfig[SIG_AD_NUM]=
{
	{FALSE, 0,E_AD},// ,SIG_AD_PWR_VALUE
	{FALSE, 8,E_AD},// ,SIG_AD_TEMP 
	{FALSE, 5,E_AD},//SIG_AD_CAMERA_B_PWR,
	{FALSE, 6,E_AD},//SIG_AD_CAMERA_F_PWR,
	{FALSE, 3,E_AD},//SIG_AD_CAMERA_R_PWR,
	{FALSE, 4,E_AD},//SIG_AD_CAMERA_L_PWR,
	{FALSE, 9,E_AD},//SIG_AD_AVM_LED_STATUS,
//	{FALSE, 6,E_AD},//SIG_AD_CAMERA_F_PWR,	3
//	{FALSE, 3,E_AD},//SIG_AD_CAMERA_L_PWR,	 6
//	{FALSE, 4,E_AD},//SIG_AD_CAMERA_B_PWR,	4
//	{FALSE, 5,E_AD},//SIG_AD_CAMERA_R_PWR,	5

};


/**************** END OF FILE *****************************************/

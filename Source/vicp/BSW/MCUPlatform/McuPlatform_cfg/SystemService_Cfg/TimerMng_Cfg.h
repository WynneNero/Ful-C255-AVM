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
* 0.1    Dec 20,2015   init version
*----------------------------------------------------------------------
* 0.2    Dec 20,2016   ShangQiuju  add config file according using hw
 ----------------------------------------------------------------------
* 0.3    Dec 21,2016    PEI Jingli     Remove unused timer 
 ----------------------------------------------------------------------
* 0.4    Dec 26,2016    PEI Jingli     Remove test timer 
*----------------------------------------------------------------------
* 0.5    Jan 16,2017     RenWeimin  Add test code.
*-----------------------------------------------------------------------
* 0.6    Feb 09,2017   ZhangJie   Remove EOL definition.
*----------------------------------------------------------------------
* 0.7    Feb 10,2017     ShangQiuju Remove SocDriver used timer. 
*------------------------------------------------------------------------
* 0.8   Apr 04,2017   PEI Jingli  Delete testing code.
*=====================================================================*/
/**** Definition of constants ****/

/**** Definition of macros ****/

BEGIN_TIMER
/****************************************POWER*************************************/

//    TIMER(TIMER_NAVI_PW_GPS_NORMAL_INIT,              Power_Task_GPS_Check_Callback)
//    TIMER(TIMER_NAVI_PW_GPS_RESET_INIT,               Power_Task_GPS_Check_Callback)
//    TIMER(TIMER_NAVI_PW_GPS_RST_RELEASE,              Power_Task_GPS_Check_Callback)
//    TIMER(TIMER_NAVI_PW_GPS_NORMAL_CHECK,             Power_Task_GPS_Check_Callback)
//    TIMER(TIMER_NAVI_PW_GPS_CHECK,                    Power_Task_GPS_Check_Callback)

/****************************************ENG***************************************/
	//TIMER(TIMER_GET_CAL_RADIO_CHECKSUM, 	         eng_radio_checksum_calculation)
	//TIMER(Uart_eng_poll_Timeout, 	                             uart_eng_poll_proc)	
	//TIMER(TIMER_DIAG_CHECK_SYSTEM_STATUS, 	 			   diag_check_system_status)
	//TIMER(TIMER_DIAG_CHECK_AGING_TIMEOUT, 	               diag_check_aging_timeout)
	//TIMER(TIMER_SEND_PA_TEMP_AND_CLIPPING, 	              send_pa_temp_and_clipping)
	//TIMER(TIMER_SEND_CAR_SPEED, 	               				     send_car_speed)

   TIMER(OPEN_TOTAL_CAMERA_PWR,open_total_camera_pwr_handle)
   TIMER(OPEN_F_CAMERA_PWR,open_f_camera_pwr)
   TIMER(OPEN_B_CAMERA_PWR,open_b_camera_pwr)
   TIMER(OPEN_L_CAMERA_PWR,open_l_camera_pwr)
   TIMER(OPEN_R_CAMERA_PWR,open_r_camera_pwr)
   
   TIMER(OPEN_PMIC_PWR,open_pmic_pwr)
   TIMER(SETON_MAX9286_PWDN,seton_max9286_pwdn)
   
//   TIMER(CLOSE_TOTAL_CAMERA_PWR,close_total_camera_pwr)
//   TIMER(CLOSE_F_CAMERA_PWR,close_f_camera_pwr)
//   TIMER(CLOSE_B_CAMERA_PWR,close_b_camera_pwr)
//   TIMER(CLOSE_L_CAMERA_PWR,close_l_camera_pwr)
//   TIMER(CLOSE_R_CAMERA_PWR,close_r_camera_pwr)
   TIMER(CLOSE_PMIC_PWR,close_pmic_pwr)
//   TIMER(SETOFF_MAX9286_PWDN,setoff_max9286_pwdn)
   TIMER(M4_MSG_40MS_ENTRY,M4Msg_40ms_Entry)  
   TIMER(OPEN_M4UART_PWR,open_m4uart_pwr)  
   TIMER(SOFTWARE_RESET,OSWDG_SoftReset)
   
END_TIMER


#undef BEGIN_TIMER
#undef END_TIMER
#undef TIMER

/**** Declaration of variables ****/

/**** Declaration of functions ****/
/****************************** END OF FILE ***************************/


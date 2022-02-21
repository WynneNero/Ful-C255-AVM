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
* 0.1  Dec 20,2015  init version
*----------------------------------------------------------------------
* 0.2  Dec 20,2016   ShangQiuju  remove unused include  files.
*------------------------------------------------------------------------
* 0.3  Jan 11,2017  ZhangJie  Add u for constant value to avoid Coverity warning.
*-----------------------------------------------------------------------
* 0.4  Jan 24,2017   ZhangJie   Remove unused include file.
*=====================================================================*/
#ifndef _PORT_CFG_H_
#define _PORT_CFG_H_ 

/*Config uart usage*/
#define ADC_G0_CHANNLE  (1u<<ADC_0)
#define ADC_G1_CHANNLE  0u
#define ADC_G2_CHANNLE  0u


/**** Definition of constants ****/

/**** Definition of types ****/

/**** Declaration of constants ****/
/**** Declaration of variables ****/
extern const U16 adc_ch_invalid_value_array[ADC_MAX];

/**** Declaration of functions ****/
void Port_setup_poweron(void);
void Port_setup_sleep(void);
void Port_setup_wakeup(void);

#endif /*_PORT_CFG_H_*/

/****************************** END OF FILE ***************************/


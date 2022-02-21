/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   :            										   *
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
* 0.1    July 25 ,2016      ShangQiuju       Init version
* ----------------------------------------------------------------------
* 0.2    Dec 26 ,2016      ShangQiuju       Add  MCU_DS03H_HW_100 config option for hw select.
* ----------------------------------------------------------------------
* 0.3    Jan  1 ,2017       ShangQiuju       UPDATE_DATA_SHIFTING may only used in dso3h .
* ----------------------------------------------------------------------
* 0.4     Jan 6,2017     ShangQiuju      Add Test Code for Ds03h Soc Spi struct.
*=====================================================================*/
#ifndef _CONFIG_H_
#define _CONFIG_H_ 

/**************config of mcu pin***************/
//#define MCU_PLATFORM_TEMPLATE_100
//#define MCU_PLATFORM_TEMPLATE_64
#define MCU_DS03H_HW_100

#define PIN48    0
#define PIN64    1
#define PIN80    2
#define PIN100    3
#define PIN144    4
#define PIN176    5

#ifdef MCU_PLATFORM_TEMPLATE_100
#define MCU_PIN	PIN100
#endif

#ifdef MCU_PLATFORM_TEMPLATE_64
#define MCU_PIN    PIN64
#endif

#ifdef MCU_DS03H_HW_100
#define MCU_PIN	PIN100
//#define HW_A1
#define HW_B1
#define UPDATE_DATA_SHIFTING /* for ds0sh platform */
#endif

/**************end of config of mcu pin***************/


#define OPEN_SPI_OPTION
//#define OPEN_CAN_OPTION
#define UPGRADE_BY_CAN 0
#define UPGRADE_BY_SPI 1



#define PLL_FREQ_HZ    80000000u    //80MHZ  at CPU_CLK_FREQ_EXTH_HZ


#endif /*_CONFIG_H_*/

/****************************** END OF FILE ***************************/

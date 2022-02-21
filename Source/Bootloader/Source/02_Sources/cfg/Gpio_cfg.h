/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.         *
*                 All Rights Reserved.              *
*   Department : CT AD                          *
*   AUTHOR     :                            *
************************************************************************
* Object        :   GPIO_CGH.H
* Module        :  config
* Instance      :
* Description   :
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date             Name                Changes and comments
* 0.1             Jan 3,2017    ShangQiuju        Init version.
*=====================================================================*/
#ifndef _GPIO_CFG_H_
#define _GPIO_CFG_H_
#include "config.h"
#include "gpio_if.h"

#define  OPEN_SOC_POWER()  do{GPIO_Out_Write(GPIO_PORT_10,GPIO_PIN_2,TRUE);\
							 GPIO_SetOutMode (GPIO_PORT_10,GPIO_PIN_2, E_NO_MODE, E_HIGH_40MHZ);\
							 GPIO_Out_Write(GPIO_PORT_0,GPIO_PIN_A,TRUE);\
							 GPIO_SetOutMode (GPIO_PORT_0,GPIO_PIN_A, E_NO_MODE, E_HIGH_40MHZ);\
							 GPIO_Out_Write(GPIO_PORT_0,GPIO_PIN_9,TRUE);\
							 GPIO_SetOutMode (GPIO_PORT_0,GPIO_PIN_9, E_NO_MODE, E_HIGH_40MHZ);\
                           				 }while(0)
                         
#define  CLOSE_SOC_POWER()  do{GPIO_Out_Write(GPIO_PORT_11,GPIO_PIN_7,FALSE);\
							 GPIO_Out_Write(GPIO_PORT_0,GPIO_PIN_8,FALSE);\
							 GPIO_Out_Write(GPIO_PORT_9,GPIO_PIN_5,FALSE);\
							 GPIO_Out_Write(GPIO_PORT_9,GPIO_PIN_4,FALSE);\
							 GPIO_Out_Write(GPIO_PORT_8,GPIO_PIN_6,FALSE);\
							 GPIO_Out_Write(GPIO_PORT_10,GPIO_PIN_1,FALSE);\
                           				 }while(0)
                         
#define SET_REQ_PIN_FOR_DATA_SENDING()  GPIO_Out_Write(GPIO_PORT_0,GPIO_PIN_4,FALSE)
#define CLEAR_REQ_PIN_FOR_DATA_SENDING()  GPIO_Out_Write(GPIO_PORT_0,GPIO_PIN_4,TRUE)

#define GET_CS_STATUS()  GPIO_In_Read(GPIO_PORT_0,GPIO_PIN_0)


#endif

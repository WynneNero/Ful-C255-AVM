/*******************************************************************************
| Module Name: simulation IIC  model
| File Name: S_IIC.h
|
|-------------------------------------------------------------------------------
|               C O P Y R I G H T
|-------------------------------------------------------------------------------
| Copyright (c) 2015 Huizhou Desay SV Automotive Co., Ltd.    All rights reserved.
|
| This software is copyright protected and proprietary to Desay SV Automotive Co., Ltd.
| Desay SV Automotive Co., Ltd grants to you only those rights as set out in the
| license conditions. All other rights remain with Desay SV Automotive Co., Ltd.
|
| REMOVAL OF THESE COMMENTS IS A VIOLATION OF THE LICENSE AGREEMENT.
|-------------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-------------------------------------------------------------------------------
| Name                                  Company
| ---------------------     ---------------------------------------
|Tan Fumin                       Desay SV Automotive Co., Ltd
|
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date             Ver        	Author               Description
| ----------  -------  -------------  -------------------------------------------------
|2014/10/28 Rev 00.00.00     Tan Fumin				The first version  
| 2015/06/09 Rev 01.00.00   Tan Fumin				update for MISRA C rules
| 2016/01/26 Rev 02.00.00   Tan Fumin				update to be standard for SVN basic code
| 2017/01/11 Rev 02.00.01   ZhangJie				Fix Coverity warning.
| 2017/01/24 Rev 02.00.02   ZhangJie				Remove unused include file.
********************************************************************************/
#ifndef _S_IIC_H
#define _S_IIC_H

#include "GPIO.h"
#include "S_IIC_CFG.h"

#define S_IIC_CH1_SetSCLHigh()			GPIO_SetVal(SCL_PORT,SCL_PIN,(BOOL)1u)	/*for example*/
#define S_IIC_CH1_SetSCLLow()			GPIO_SetVal(SCL_PORT,SCL_PIN,(BOOL)0u)	/*for example*/
#define S_IIC_CH1_SetSCLOutputMode()	GPIO_SetOutputMode(SCL_PORT,SCL_PIN,E_OPEN_DRAIN,E_LOW_10MHZ)		/*for example*/

#define S_IIC_CH1_GetSDAValue()		GPIO_GetVal(SDA_PORT,SDA_PIN)		/*for example*/
#define S_IIC_CH1_SetSDAHigh()			GPIO_SetVal(SDA_PORT,SDA_PIN,(BOOL)1u)	/*for example*/
#define S_IIC_CH1_SetSDALow()			GPIO_SetVal(SDA_PORT,SDA_PIN,(BOOL)0u)	/*for example*/
#define S_IIC_CH1_SetSDAInputMode()	GPIO_SetInputMode(SDA_PORT,SDA_PIN, E_NO_MODE)	/*for example*/
#define S_IIC_CH1_SetSDAOutputMode()	GPIO_SetOutputMode(SDA_PORT,SDA_PIN,E_OPEN_DRAIN,E_LOW_10MHZ)	/*for example*/

/*======do not edit below this line =======*/

#define S_IIC_CH1_WaitAck()	do{U16 u8WaitAckCnt=S_IIC_CH1_AckWaitCnt;S_IIC_CH1_SetSDAInputMode();\
							while((u8WaitAckCnt !=0u) && (S_IIC_CH1_GetSDAValue() !=0U)){u8WaitAckCnt--;}\
							}while(0)
		
			/*  Time(us) 	  DelayCnt */
			/* 	1.5			10      */
			/* 	1			5       */
#define S_IIC_CH1_ClkDelay()	do{U16 u8Wait=S_IIC_CH1_DelayCnt;while(u8Wait !=0u){u8Wait--;}}while(0)

#define S_IIC_CH1_Init()	do{	S_IIC_CH1_SetSCLLow();/*set output Low level for ready SDA to output*/\
							S_IIC_CH1_SetSCLOutputMode();/*set Sck input first to avoid Pin level change*/\
							S_IIC_CH1_SetSDAHigh();/*output SDA high level*/\
							S_IIC_CH1_SetSDAOutputMode();\
							S_IIC_CH1_SetSCLHigh(); /*output SCK high level*/\
						}while(0)
						
#define S_IIC_CH1_SetReady()	do{S_IIC_CH1_Init();IIC_u8CH1_Satus=(U8)IIC_enReady;}while(0)
#define S_IIC_CH1_Exit()			do{S_IIC_CH1_Init();IIC_u8CH1_Satus=(U8)IIC_enReady;}while(0)

/*======do not edit above this line =======*/

enum
{
	IIC_enNotReady=0u,
	IIC_enReady,
	IIC_enBusy,
};

#endif



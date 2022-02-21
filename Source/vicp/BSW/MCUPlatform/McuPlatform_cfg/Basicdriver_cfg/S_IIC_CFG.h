/*******************************************************************************
| Module Name: simulation IIC  model
| File Name: S_IIC_cfg.h
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
|2014/10/28  Rev 00.00.00    Tan Fumin				The first version  
| 2015/06/09 Rev 01.00.00   Tan Fumin				update for MISRA C rules
| 2016/01/26 Rev 02.00.00   Tan Fumin				update to be standard for SVN basic code
| 2017/01/11 Rev 02.00.01   ZhangJie				Add function S_IIC_SlaveNack_Callback definition,
|                                                                                  and explicit variable cast and add u for constant value to avoid Coverity warning.
| 2017/01/24 Rev 02.00.02   ZhangJie				Fix Coverity warnings phase2.
********************************************************************************/
#ifndef _S_IIC_CFG_H
#define _S_IIC_CFG_H
/**** Definition of macros ****/
#define S_IIC_DataField_LSB		1U
#define S_IIC_DataField_MSB		2U

/* port config */
#define SCL_PORT ((U8)GPIO_PORT_0)
#define SCL_PIN ((U8)GPIO_PIN_C)

#define SDA_PORT ((U8)GPIO_PORT_0)
#define SDA_PIN ((U8)GPIO_PIN_B)

#define S_IIC_CH1_DataField		(S_IIC_DataField_MSB)

/* baud rate config */

/* 4 - 350~430k,H:33%,L:67% */			
/* 5 - 388.3~400kHz, duty: H-58%,L-42%	 */
/* 10 - 224~296kHz: H-32%, L-68%; H-56%, L-44% */
/* 20 -  150k */
/* 35 -  100k */
/* 200 - 27k */
/* 400 -10k */
#define S_IIC_CH1_AckWaitCnt	(400u)
#define S_IIC_CH1_DelayCnt		(400u)

/**** Declaration of functions ****/
void S_IIC_SlaveNack_Callback(void);

#endif

/*******************************************************************************
| Module Name: simulation IIC  model
| File Name: S_SPI_cfg.h
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
|2014/10/28 Rev 01.00.00     Tan Fumin			The first version  
|2016/01/26 Rev 02.00.00   Tan Fumin				update to be standard for SVN basic code
********************************************************************************/

#include "hal.h"		/*for example*/
#include "../../07_det/det.h"		/*for example*/

#ifndef S_SPI_CFG_H
#define S_SPI_CFG_H

#define S_SPI_CHANNEL_NUMBER	2u

#define S_SPI_DataField_LSB		1u
#define S_SPI_DataField_MSB	2u

#define S_SPI_RisingEdge	1u
#define S_SPI_FailingEdge	2u

#if S_SPI_CHANNEL_NUMBER>=1u

#define S_SPI_CH1_Enable	1u

/*####################################################################*/
/*####################################################################*/

#define S_SPI_CH1_DataField	S_SPI_DataField_MSB/*1=LSB, 2=MSB*/

#define S_SPI_CH1_DataInEdge	S_SPI_FailingEdge/*1=Raising, 2=Failling*/
#define S_SPI_CH1_DataOutEdge	S_SPI_FailingEdge/*1=Raising, 2=Failling*/

#define S_SPI_CH1_CLKReadyLevel		0u	/*if out this level to CLKpin, the CLKpin status is ready!*/
#define S_SPI_CH1_SODummyLevel		1u	/*SO level dummy data*/

#define S_SPI_CH1_DataUnit				16u 	/*how many bits data in a frame*/
#define S_SPI_CH1_DataBuffEnable		0u 	/*enable or disable data store in buffer for transfer*/
#define S_SPI_CH1_DataBuffSize			2u 	/*how many byte data store for transfer*/
#define S_SPI_CH1_TransfDelayCnt		10u	/*small delay count between data bit transfer!*/

#define S_SPI_CH1_SetClkHigh()			HAL_PinWrite(10,1, 1); 	/*for example*/
#define S_SPI_CH1_SetClkLow()			HAL_PinWrite(10,1,0); 	/*for example*/
#define S_SPI_CH1_SetClkReady()			HAL_PinWrite(10,1,S_SPI_CH1_CLKReadyLevel); /*for example*/
#define S_SPI_CH1_SetClkOutPutMode()	HAL_PinConfig(10,1, HAL_mPinOutput); 	/*for example*/

#define S_SPI_CH1_SetSoHigh()			HAL_PinWrite(10,2, 1); 	/*for example*/
#define S_SPI_CH1_SetSoLow()			HAL_PinWrite(10,2, 0); 	/*for example*/
#define S_SPI_CH1_SetSoOutPutMode()		HAL_PinConfig(10,2, HAL_mPinOutput); 	 	/*for example*/

#define S_SPI_CH1_GetSiValue()			HAL_PinRead(10, 0) 	/*for example*/
#define S_SPI_CH1_SetSiInPutMode()		HAL_PinConfig(10,0, HAL_mPinInput); 	/*for example*/

/*####################################################################*/
/*####################################################################*/


/*======do not edit below this line =======*/



/*Not Edit*/#define S_SPI_CH1_Init()	do{\
/*Not Edit*/							S_SPI_CH1_SetClkReady();\
/*Not Edit*/							S_SPI_CH1_SetSoHigh();\
/*Not Edit*/							S_SPI_CH1_SetClkOutPutMode();\
/*Not Edit*/							S_SPI_CH1_SetSoOutPutMode();\
/*Not Edit*/							S_SPI_CH1_SetSiInPutMode();\
/*Not Edit*/						     }while(0)
/*Not Edit*/
/*Not Edit*/#define S_SPI_CH1_SetReady()		do{S_SPI_CH1_Init();SPI_u8CH1_SpiSatus=SPI_enReady;}while(0)
/*Not Edit*/#define S_SPI_CH1_Exit()			do{S_SPI_CH1_Init();SPI_u8CH1_SpiSatus=SPI_enNotReady;}while(0)
/*Not Edit*/
/*Not Edit*/#define S_SPI_CH1_ClkDelay()	do{uint16 u16WaitCnt=S_SPI_CH1_TransfDelayCnt;while(u16WaitCnt!=0u){u16WaitCnt--;}}while(0)
/*Not Edit*/
#if S_SPI_CH1_DataUnit == 16u
	#if S_SPI_CH1_SODummyLevel != 0u
		#define S_SPI_CH1_SODummyOut		0xFFFFu
	#else
		#define S_SPI_CH1_SODummyOut		0u
	#endif
#elif S_SPI_CH1_DataUnit == 8u
	#if S_SPI_CH1_SODummyLevel != 0u
		#define S_SPI_CH1_SODummyOut		0xFFu
	#else
		#define S_SPI_CH1_SODummyOut		0u
	#endif
#endif


#endif



#if S_SPI_CHANNEL_NUMBER>=2u

#define S_SPI_CH2_Enable	1u

/*####################################################################*/
/*####################################################################*/

#define S_SPI_CH2_DataField	S_SPI_DataField_MSB/*1=LSB, 2=MSB*/

#define S_SPI_CH2_DataInEdge	S_SPI_FailingEdge/*1=Raising, 2=Failling*/
#define S_SPI_CH2_DataOutEdge	S_SPI_FailingEdge/*1=Raising, 2=Failling*/

#define S_SPI_CH2_CLKReadyLevel		0u	/*if out this level to CLKpin, the CLKpin status is ready!*/
#define S_SPI_CH2_SODummyLevel		1u	/*SO level dummy data*/

#define S_SPI_CH2_DataUnit				16u 	/*how many bits data in a frame*/
#define S_SPI_CH2_DataBuffEnable		0u 	/*enable or disable data store in buffer for transfer*/
#define S_SPI_CH2_DataBuffSize			2u 	/*how many byte data store for transfer*/
#define S_SPI_CH2_TransfDelayCnt		10u	/*small delay count between data bit transfer!*/

#define S_SPI_CH2_SetClkHigh()			HAL_PinWrite(10,7, 1); 	/*for example*/
#define S_SPI_CH2_SetClkLow()			HAL_PinWrite(10,7,0); 	/*for example*/
#define S_SPI_CH2_SetClkReady()			HAL_PinWrite(10,7,S_SPI_CH2_CLKReadyLevel); /*for example*/
#define S_SPI_CH2_SetClkOutPutMode()	HAL_PinConfig(10,7, HAL_mPinOutput); 	/*for example*/

#define S_SPI_CH2_SetSoHigh()			HAL_PinWrite(10,6, 1); 	/*for example*/
#define S_SPI_CH2_SetSoLow()			HAL_PinWrite(10,6, 0); 	/*for example*/
#define S_SPI_CH2_SetSoOutPutMode()		HAL_PinConfig(10,6, HAL_mPinOutput); 	 	/*for example*/

#define S_SPI_CH2_GetSiValue()			HAL_PinRead(10, 8) 	/*for example*/
#define S_SPI_CH2_SetSiInPutMode()		HAL_PinConfig(10,8, HAL_mPinInput); 	/*for example*/

/*####################################################################*/
/*####################################################################*/


/*======do not edit below this line =======*/



/*Not Edit*/#define S_SPI_CH2_Init()	do{\
/*Not Edit*/							S_SPI_CH2_SetClkReady();\
/*Not Edit*/							S_SPI_CH2_SetSoHigh();\
/*Not Edit*/							S_SPI_CH2_SetClkOutPutMode();\
/*Not Edit*/							S_SPI_CH2_SetSoOutPutMode();\
/*Not Edit*/							S_SPI_CH2_SetSiInPutMode();\
/*Not Edit*/						     }while(0)
/*Not Edit*/
/*Not Edit*/#define S_SPI_CH2_SetReady()		do{S_SPI_CH2_Init();SPI_u8CH2_SpiSatus=SPI_enReady;}while(0)
/*Not Edit*/#define S_SPI_CH2_Exit()			do{S_SPI_CH2_Init();SPI_u8CH2_SpiSatus=SPI_enNotReady;}while(0)
/*Not Edit*/
/*Not Edit*/#define S_SPI_CH2_ClkDelay()	do{uint16 u16WaitCnt=S_SPI_CH2_TransfDelayCnt;while(u16WaitCnt!=0u){u16WaitCnt--;}}while(0)
/*Not Edit*/
#if S_SPI_CH2_DataUnit == 16u
	#if S_SPI_CH2_SODummyLevel != 0u
		#define S_SPI_CH2_SODummyOut		0xFFFFu
	#else
		#define S_SPI_CH2_SODummyOut		0u
	#endif
#elif S_SPI_CH2_DataUnit == 8u
	#if S_SPI_CH2_SODummyLevel != 0u
		#define S_SPI_CH2_SODummyOut		0xFFu
	#else
		#define S_SPI_CH2_SODummyOut		0u
	#endif
#endif


#endif













#endif /*end of this file*/


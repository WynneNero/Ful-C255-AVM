/*******************************************************************************
| Module Name: simulation IIC  model
| File Name: S_IIC.c
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
| 2016/12/20 Rev 02.00.00   ShangQiuju				Add gpio_if.h for compile error.
| 2017/01/24 Rev 02.00.01   ZhangJie				Fix Coverity warning.
********************************************************************************/
#include "S_IIC.h"
#include "Define.h"
#include "gpio_if.h"

static U8 IIC_u8CH1_Satus=IIC_enBusy;

/*****************************************************************************
 Function  : S_IIC_Init												 
 Description   :initialization the IIC I/O pin to be ready 
 
 In Parameter: 
 			NULL
 			
Return Value:
 			NULL
 			
 NOTE: 		
 			after execute this function, 
 				SDA=High,output
 				SCK=High
*****************************************************************************/
void S_IIC_Init(void)
{
	S_IIC_CH1_SetReady();
}

/*****************************************************************************
 Function  : S_IIC_DeInit												 
 Description   :De-initialization the IIC I/O pin to be ready 
 
 In Parameter: 
 			NULL
 			
Return Value:
 			NULL
 			
 NOTE: 		
 			after execute this function, 
 				SDA=High,output
 				SCK=High
*****************************************************************************/
void S_IIC_DeInit(void)
{
	S_IIC_CH1_Exit();
}

/*****************************************************************************
 Function  : IIC_SendStart												 
 Description   :generate a start-condition for prepare data transfer
 
 In Parameter: 
 			NULL
 			
Return Value:
 			NULL
 			
 NOTE: 		
 			after execute this function, 
 				SDA=Low,output
 				SCK=Low
*****************************************************************************/
void S_IIC_SendStart(void)
{
	S_IIC_CH1_SetSCLHigh();
	S_IIC_CH1_ClkDelay();
	
	S_IIC_CH1_SetSDAHigh();
	S_IIC_CH1_ClkDelay();
	
	S_IIC_CH1_SetSDALow();
	S_IIC_CH1_ClkDelay();
	
	S_IIC_CH1_SetSCLLow();
	S_IIC_CH1_ClkDelay();
	
}

/*****************************************************************************
 Function  : IIC_SendStop												 
 Description   :generate a stop-condition for prepare data transfer
 
 In Parameter: 
 			NULL
 			
Return Value:
 			NULL
 			
 NOTE: 		
 			after execute this function, 
 				SDA=High,output
 				SCK=High
*****************************************************************************/
void S_IIC_SendStop(void)
{
	S_IIC_CH1_SetSCLLow();
	S_IIC_CH1_ClkDelay();

	S_IIC_CH1_SetSDALow();
	S_IIC_CH1_ClkDelay();
	
	S_IIC_CH1_SetSCLHigh();
	S_IIC_CH1_ClkDelay();

	S_IIC_CH1_SetSDAHigh();
	S_IIC_CH1_ClkDelay();
}

/*****************************************************************************
 Function  : S_IIC_SendData												 
 Description   :send data to slave node
 
 In Parameter: 
 			pOutDataHead : output data head
 			u16DataLen : data lenth(in byte)
 			
Return Value:
 			function execute result
 			
 NOTE: 		This function takes time, put this in proper task. 
 			Calculate total time needed based on baud rate and data length. 			
*****************************************************************************/
ERR_TYPE S_IIC_SendData(U8 * pOutDataHead, U16 u16DataLen)
{
	U16 u16totallIndex;
	U8 OutData,u8i;
	U8 u8MaskData;
	
	ERR_TYPE eRetVal=ERR_OK;

	/*check driver status*/
	if(IIC_u8CH1_Satus !=(U8)IIC_enReady)
	{
		eRetVal =  ERR_SEVICE_NOT_READY;
	}
	else
	{
	
		IIC_u8CH1_Satus=IIC_enBusy;		
		
		/*totall loops*/
		for(u16totallIndex=0U;u16totallIndex<u16DataLen;u16totallIndex++)
		{
			OutData=*(pOutDataHead);
                     pOutDataHead++;
                #if S_IIC_CH1_DataField == S_IIC_DataField_LSB
                     u8MaskData=1u;
                #elif S_IIC_CH1_DataField ==S_IIC_DataField_MSB
                     u8MaskData=0x80u;
                #endif
			/*uinit loops*/
			for(u8i=0u;u8i<8u;u8i++)
			{			
				/*set output bit ready*/
				if((OutData & u8MaskData) !=0U)
				{
					S_IIC_CH1_SetSDAHigh();
				}
				else
				{
					S_IIC_CH1_SetSDALow();
				}
				
			#if S_IIC_CH1_DataField == S_IIC_DataField_LSB
				u8MaskData<<=1u;
			#elif S_IIC_CH1_DataField ==S_IIC_DataField_MSB
				u8MaskData>>=1u;
			#endif
				/*wait value pin stable*/
				S_IIC_CH1_ClkDelay();
				
				/*rasing edge trigger to ouput SDA value*/
				S_IIC_CH1_SetSCLHigh();
				
				/*wait value pin stable*/
				S_IIC_CH1_ClkDelay();
				
				/*Set SCK to low for next bit output*/
				S_IIC_CH1_SetSCLLow();
				
			}
			
			/*small delay to wait Ack*/
			S_IIC_CH1_ClkDelay();
			/*rasing edge trigger to Get SDA ACK value*/
			S_IIC_CH1_SetSCLHigh();
			S_IIC_CH1_WaitAck();
			
			if(S_IIC_CH1_GetSDAValue()!=0U)
			{
				eRetVal=ERR_IIC_SLAVE_NOACK;
			}
			
			/*Set SCK to low for next bit output*/
			S_IIC_CH1_SetSCLLow();
			
			/*Set SDA to low for next bit output*/
			S_IIC_CH1_SetSDALow();
			S_IIC_CH1_SetSDAOutputMode();
		}	
		
		IIC_u8CH1_Satus =IIC_enReady;
	}

	if(ERR_IIC_SLAVE_NOACK==eRetVal)
	{
		S_IIC_SlaveNack_Callback();
	}
	
	return eRetVal;
	
}


/*****************************************************************************
 Function  : IIC_u16RecData_CH1												 
 Description   :receive data from slave node
 
 In Parameter: 
 			pRecDataHead : input data head
 			u16DataLen : data lenth(in byte)
 			
Return Value:
 			function execute result
 			
 NOTE: 		This function takes time, put this in proper task. 
 			Calculate total time needed based on baud rate and data length.
*****************************************************************************/
ERR_TYPE S_IIC_RecData(U8 *pRecDataHead, U16 u16DataLen)
{
	U8 u8i,RecData,u8MaskData;
       U16 u16totallIndex=0U;
	
	ERR_TYPE eRetVal=ERR_OK;
		
	/*check driver status*/
	if(IIC_u8CH1_Satus !=(U8)IIC_enReady)
	{
		eRetVal =  ERR_SEVICE_NOT_READY;
	}
	else
	{
		IIC_u8CH1_Satus=IIC_enBusy; 	
		
		/*totall loops*/
		for(u16totallIndex=0U;u16totallIndex<u16DataLen;u16totallIndex++)
		{
			RecData=0U;
                     #if S_IIC_CH1_DataField == S_IIC_DataField_LSB
	              u8MaskData=1u;
                     #elif S_IIC_CH1_DataField ==S_IIC_DataField_MSB
	        	       u8MaskData=0x80u;
                    #endif
			/*set input mode for data in*/
			S_IIC_CH1_SetSDAInputMode();
			
			/*uinit loops*/
			for(u8i=0u;u8i<8u;u8i++)
			{			
				/*wait value pin stable*/
				S_IIC_CH1_ClkDelay();
				
				/*rasing edge trigger to get SDA value*/
				S_IIC_CH1_SetSCLHigh();
				
				/*wait value pin stable*/
				S_IIC_CH1_ClkDelay();
				
				/*get SDA bit data*/
				if(S_IIC_CH1_GetSDAValue() !=0U)
				{
					RecData|=u8MaskData;
				}	
				
			#if S_IIC_CH1_DataField == S_IIC_DataField_LSB
				u8MaskData<<=1u;
			#elif S_IIC_CH1_DataField ==S_IIC_DataField_MSB
				u8MaskData>>=1u;
			#endif
				/*Set SCK to low for next bit output*/
				S_IIC_CH1_SetSCLLow();
				
			}
			
				/*small delay to send Ack*/
				/*S_IIC_CH1_ClkDelay();*/

				S_IIC_CH1_SetSDAOutputMode();
				if(u16totallIndex<(u16DataLen-1U))
				{
					/*Set SDA to low for next bit input*/
					S_IIC_CH1_SetSDALow();
				}
				else
				{
					/*Set SDA to high for Not Ack if it is last bit input*/
					S_IIC_CH1_SetSDAHigh();
				}
									
				/*rasing edge trigger to send SDA ACK signal*/
				S_IIC_CH1_SetSCLHigh();
				
				/*update data to app layer*/
				*(pRecDataHead)=RecData;
                            pRecDataHead ++;
				
				/*small delay to next byte*/
				S_IIC_CH1_ClkDelay();
				
				/*Set SCK to low for next bit input*/
				S_IIC_CH1_SetSCLLow();
			
		}	
		
		/*Set SDA to low for next bit input*/
		S_IIC_CH1_ClkDelay();
		S_IIC_CH1_SetSDALow();
		
		IIC_u8CH1_Satus =IIC_enReady;
		
	}
	
	return eRetVal;
}



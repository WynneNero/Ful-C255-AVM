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
*
*=====================================================================*/
//#include "CONFIG.H"
//#include "TYPES.H"
#include "CanApp.h"
#include "define.h"

 #include "IL_INC.H"
/*******************************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants and macros to configure your module. These constants are unknown for other 
*   modules
********************************************************************************************/
#define CANTXSIG_PASS_2
#include "Cansig_def.h"
#define CANRXSIG_PASS_2
#include "Cansig_def.h"

#define CANTXSIG_PASS_3
#include "Cansig_def.h"
#define CANRXSIG_PASS_3
#include "Cansig_def.h"

#define CANTXSIG_PASS_4
#include "Cansig_def.h"
#define CANRXSIG_PASS_4
#include "Cansig_def.h"

/***********************************************************************
* FUNCTION    : can_get_rx_signal
* DESCRIPTION : 
* INPUTS      : CAN_RX_SIG_INFO * pRxSignalInfo
* RETURN      : none
***********************************************************************/
static void can_get_rx_signal(CAN_RX_SIG_INFO * pRxSignalInfo)
{
	CAN_RX_SIG_FUNC_MAP *pFuncMap = (CAN_RX_SIG_FUNC_MAP *)CANRxSigFuncMap + pRxSignalInfo->SignalIdx;
  	pFuncMap->GetFunc(pRxSignalInfo);
}
/****************************************************************************
* FUNCTION    : can_set_tx_signal
* DESCRIPTION : 
* INPUTS      : CAN_TX_SIG_INFO * pTxSignalInfo
* RETURN      : none
*****************************************************************************/
static void can_set_tx_signal(CAN_TX_SIG_INFO * pTxSignalInfo)
{
	CAN_TX_SIG_FUNC_MAP * pFuncMap = (CAN_TX_SIG_FUNC_MAP *)CANTxSigFuncMap + pTxSignalInfo->SignalIdx;
  	pFuncMap->SetFunc(pTxSignalInfo);
}

/*******************************************************************************************
* FUNCTION    : Sig_CANGetValue()
* DESCRIPTION : Interface for upper layer to get signal value from CAN
* INPUTS      : signal name, 
* RETURN      : none
*   
********************************************************************************************/
U8 CanSig_CANGetValue(U16 Signal, U8* pvalue,U8 len)
{
  	U8 ret = 0;
	U8* Tem=(U8*)pvalue;
	CAN_RX_SIG_INFO sRxSigInfo;

	if(pvalue!=NULL && Signal<CAN_NUM_OF_RX_SIG_ID&&len>0)
	{
		sRxSigInfo.SignalIdx = Signal;
		if(len<=2)
		{          
                     can_get_rx_signal(&sRxSigInfo);    
        		if(len==1)
        		{
        			Tem[0]=sRxSigInfo.SignalData.Data8U;
        			ret = 1;
        		}
        		else if(len == 2)
        		{
        			Tem[0]=(U8)(sRxSigInfo.SignalData.Data16U&0xFF);
        			Tem[1]=(U8)(sRxSigInfo.SignalData.Data16U>>8);
        			ret = 1;
        		}
		}
		else
		{
		        sRxSigInfo.SignalData.pDataBuf = pvalue;
                     can_get_rx_signal(&sRxSigInfo);  
			ret = 1;
		}
	}
   return ret;
}


/*******************************************************************************************
* FUNCTION    : Sig_CANSendValue(RX_NULL)
* DESCRIPTION : Interface for upper layer to send value to CAN
* INPUTS      : signal name, 
* RETURN      : none
*   
********************************************************************************************/
void CanSig_CANSendValue(U16 Signal, U8* pvalue,U8 len)
{
    CAN_TX_SIG_INFO sTxSigInfo;

	if(Signal<CAN_NUM_OF_TX_SIG_ID&& pvalue!=NULL)
	{
		sTxSigInfo.SignalIdx = Signal;
		sTxSigInfo.SignalData.pDataBuf=pvalue;
		can_set_tx_signal(&sTxSigInfo);
	}
	
}

/**************** END OF FILE *****************************************/


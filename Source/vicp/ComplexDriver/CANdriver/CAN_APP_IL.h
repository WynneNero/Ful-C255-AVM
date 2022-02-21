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
* 0.1  Apr 15,2016                Initial version.  
*------------------------------------------------------------------------
* 0.2 Jan 24,2017  ZhangJie  Fix Coverity warnings.
*=====================================================================*/
#ifndef _CAN_APP_IL_H_
#define _CAN_APP_IL_H_ 

/**** Definition of constants ****/
#include "define.h"

/**** Definition of types ****/ 

typedef union
{
	S8 Data8S;
	U8 Data8U;
	S16 Data16S;
	U16 Data16U;
	/*S32 Data32S;*/
	/*U32 Data32U;*/
	U8 *pDataBuf;
} CAN_SIG_DATA;

typedef struct
{
	U8 SignalIdx;
	CAN_SIG_DATA SignalData;
	U8 SignalLen;
	BOOL IndicationFlag;
	BOOL TimeoutFlag;
} CAN_RX_SIG_INFO;

typedef struct
{
	U8 SignalIdx;
	CAN_SIG_DATA SignalData;
	BOOL ConfirmFlag;
} CAN_TX_SIG_INFO;

typedef void (*FP_RX_SIG_GET)(CAN_RX_SIG_INFO * const pSignalInfo);
typedef void (*FP_RX_SIG_SET)(const CAN_RX_SIG_INFO * const pSignalInfo);
typedef void (*FP_TX_SIG_GET)(CAN_TX_SIG_INFO * const pSignalInfo);
typedef void (*FP_TX_SIG_SET)(const CAN_TX_SIG_INFO * const pSignalInfo);

typedef struct
{
	FP_RX_SIG_GET GetFunc;
	/*FP_RX_SIG_SET SetFunc;*/
} CAN_RX_SIG_FUNC_MAP;

typedef struct
{
	/*FP_TX_SIG_GET GetFunc;*/
	FP_TX_SIG_SET SetFunc;
} CAN_TX_SIG_FUNC_MAP;

/**** Definition of macros ****/
#define RX_SIG_GET_FUNC(SigName)					void RxSigGetFunc_##SigName(CAN_RX_SIG_INFO * const pSignalInfo)
#define RX_SIG_GET_FUNC_REF(SigName)				RxSigGetFunc_##SigName
#define RX_SIG_GET_FUNC_CALL(SigName, pSignalInfo)	RxSigGetFunc_##SigName(pSignalInfo)

#define RX_SIG_SET_FUNC(SigName)					void RxSigSetFunc_##SigName(const CAN_RX_SIG_INFO * const pSignalInfo)
#define RX_SIG_SET_FUNC_REF(SigName)				RxSigSetFunc_##SigName
#define RX_SIG_SET_FUNC_CALL(SigName, pSignalInfo)	RxSigSetFunc_##SigName(pSignalInfo)

#define TX_SIG_GET_FUNC(SigName)					void TxSigGetFunc_##SigName(CAN_TX_SIG_INFO * const pSignalInfo)
#define TX_SIG_GET_FUNC_REF(SigName)				TxSigGetFunc_##SigName
#define TX_SIG_GET_FUNC_CALL(SigName, pSignalInfo)	TxSigGetFunc_##SigName(pSignalInfo)

#define TX_SIG_SET_FUNC(SigName)					void TxSigSetFunc_##SigName(const CAN_TX_SIG_INFO * const pSignalInfo)
#define TX_SIG_SET_FUNC_REF(SigName)				TxSigSetFunc_##SigName
#define TX_SIG_SET_FUNC_CALL(SigName, pSignalInfo)	TxSigSetFunc_##SigName(pSignalInfo)

/**** Declaration of constants ****/


/**** Declaration of variables ****/


/**** Declaration of functions ****/

#endif /*_CAN_APP_IL_H_*/

/****************************** END OF FILE ***************************/


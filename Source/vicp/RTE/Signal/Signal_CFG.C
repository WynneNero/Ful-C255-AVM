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
* ----------------------------------------------------------------------
* 0.1    Jun 26,2016    PEI Jingli  Initial version
* ----------------------------------------------------------------------
* 0.2    Aug 01,2016   PEI Jingli  Add calling of IO/AD signal 
* ----------------------------------------------------------------------
* 0.3    Dec 20,2016   ShangQiuju remove unused include files. 
* ----------------------------------------------------------------------
* 0.4    Jan 05,2017   ShangQiuju  update Sig_CombineGetDirectValue,Sig_CombineSetDirectValue
                                                   in sync function.
*------------------------------------------------------------------------
* 0.5    Jan 24,2017  ZhangJie  Fix Coverity warnings.
*----------------------------------------------------------------------
* 0.6    Feb 14,2017   ZhangJie  Divide digital signal to input and output.  
*=====================================================================*/
#include "signal.h"
#include "Sig_Combine.H"
/*---Global-----------------------------------------------------------*/
const V_asyncreceive SignalaRevProc[E_SIG_TYPE_NUM]=
{
	Sig_DioGetValue,
       V_asyncreceive_empty,
	Sig_ADGetValue,
	V_asyncreceive_empty,
	V_asyncreceive_empty,
	V_asyncreceive_empty,
};

const V_asyncsend  SignalaSndProc[E_SIG_TYPE_NUM]=
{
       V_asyncsend_empty,
       Sig_DioWriteValue,
	V_asyncsend_empty,
	V_asyncsend_empty,
	V_asyncsend_empty,
	V_asyncsend_empty,
};

const V_asyncreceive_prehook SignalaRevPreProc[E_SIG_TYPE_NUM]=
{
	V_asyncreceive_prehook_empty,
       V_asyncreceive_prehook_empty,
	V_asyncreceive_prehook_empty,
	V_asyncreceive_prehook_empty,
	V_asyncreceive_prehook_empty,
	V_asyncreceive_prehook_empty,
};

const V_asyncreceive_psthook  SignalaRevPstProc[E_SIG_TYPE_NUM]=
{
	V_asyncreceive_psthook_empty,
       V_asyncreceive_psthook_empty,
	V_asyncreceive_psthook_empty,
	V_asyncreceive_psthook_empty,
	V_asyncreceive_psthook_empty,
	V_asyncreceive_psthook_empty,
};

const V_asyncsend_prehook SignalaSndPreProc[E_SIG_TYPE_NUM]=
{
	V_asyncsend_prehook_empty,
       V_asyncsend_prehook_empty,
	V_asyncsend_prehook_empty,
	V_asyncsend_prehook_empty,
	V_asyncsend_prehook_empty,
	V_asyncsend_prehook_empty,
};

const V_asyncsend_psthook  SignalaSndPstProc[E_SIG_TYPE_NUM]=
{
	V_asyncsend_psthook_empty,
       V_asyncsend_psthook_empty,
	V_asyncsend_psthook_empty,
	V_asyncsend_psthook_empty,
	V_asyncsend_psthook_empty,
	V_asyncsend_psthook_empty,
};


const V_syncreceive SignalRevProc[E_SIG_TYPE_NUM]=
{
	Sig_DioGetDirectValue,
       V_syncreceive_empty,
	Sig_ADDirectGetValue,
	V_syncreceive_empty,
	V_syncreceive_empty,/*Sig_CANGetValue,*/
	Sig_CombineGetDirectValue,
};

const V_syncsend  SignalSndProc[E_SIG_TYPE_NUM]=
{
       V_syncsend_empty,
       Sig_DioWriteValue,
	V_syncsend_empty,
	V_syncsend_empty,
	V_syncsend_empty,/*Sig_CANSendValue,*/
	Sig_CombineSetDirectValue,
};

const V_syncreceive_prehook SignalRevPreProc[E_SIG_TYPE_NUM]=
{
	V_syncreceive_prehook_empty,
       V_syncreceive_prehook_empty,
	V_syncreceive_prehook_empty,
	V_syncreceive_prehook_empty,
	V_syncreceive_prehook_empty,
	V_syncreceive_prehook_empty,
};

const V_syncreceive_psthook  SignalRevPstProc[E_SIG_TYPE_NUM]=
{
	V_syncreceive_psthook_empty,
       V_syncreceive_psthook_empty,
	V_syncreceive_psthook_empty,
	V_syncreceive_psthook_empty,
	V_syncreceive_psthook_empty,
	V_syncreceive_psthook_empty,
};

const V_syncsend_prehook SignalSndPreProc[E_SIG_TYPE_NUM]=
{
	V_syncsend_prehook_empty,
       V_syncsend_prehook_empty,
	V_syncsend_prehook_empty,
	V_syncsend_prehook_empty,
	V_syncsend_prehook_empty,
	V_syncsend_prehook_empty,
};

const V_syncsend_psthook  SignalSndPstProc[E_SIG_TYPE_NUM]=
{
	V_syncsend_psthook_empty,
       V_syncsend_psthook_empty,
	V_syncsend_psthook_empty,
	V_syncsend_psthook_empty,
	V_syncsend_psthook_empty,
	V_syncsend_psthook_empty,
};


const V_freeze  SignalFreezeProc[E_SIG_TYPE_NUM]=
{
	Di_FreezeSignal,
       Do_FreezeSignal,
	Adc_FreezeSignal,
	V_freeze_empty,
	V_freeze_empty,
	V_freeze_empty,
};

const V_unfreeze  SignalUnFreezeProc[E_SIG_TYPE_NUM]=
{
	Di_UnFreezeSignal,
       Do_UnFreezeSignal,
	Adc_UnFreezeSignal,
	V_unfreeze_empty,
	V_unfreeze_empty,
	V_unfreeze_empty,
};
/**************** END OF FILE *****************************************/


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
* Version       Date      Name          Changes and comments
*-----------------------------------------------------------------------
* 0.1    Aug 11,2016                       Initial version
*----------------------------------------------------------------------
* 0.2    Jan 5,2017     ShangQiuju    change receive function parameter from U16* to U8* 
*----------------------------------------------------------------------
* 0.3    Feb 14,2017   ZhangJie        Divide digital signal to input and output.  
*=====================================================================*/
#ifndef _SIGNAL_H_
#define _SIGNAL_H_ 

#define  SIGNAL_PASS_1
#include "Signal_def.h"

/**** Definition of constants ****/
typedef enum
{
    E_SIG_DI = 0,
    E_SIG_DO,
    E_SIG_ADC,
    E_SIG_CAN0,
    E_SIG_CAN1,
    E_SIG_COMBINE,
    E_SIG_TYPE_NUM
}Sig_SignalType;

typedef struct _SIGNAL
{
    U16 sourename;
    Sig_SignalType type;
}Signal;

/**** Definition of macros ****/

typedef  U16(* const V_sig_convert)( U16 sig);
typedef  U8 ( *const V_asyncreceive )( U16 sig, U8* value);
typedef  void( *const V_asyncsend)( U16 sig, U8* value);

typedef  void( *const V_asyncreceive_prehook )( U16 sig, U8* value);
typedef  void( *const V_asyncreceive_psthook )( U16 sig, U8* value);
typedef  void( *const V_asyncsend_prehook)( U16 sig, U8* value);
typedef  void( *const V_asyncsend_psthook)( U16 sig, U8* value);


typedef  U8 ( *const V_syncreceive )( U16 sig, U8* value);
typedef  void( *const V_syncsend)( U16 sig, U8* value);

typedef  void( *const V_syncreceive_prehook )( U16 sig, U8* value);
typedef  void( *const V_syncreceive_psthook )( U16 sig, U8* value);
typedef  void( *const V_syncsend_prehook)( U16 sig, U8* value);
typedef  void( *const V_syncsend_psthook)( U16 sig, U8* value);
typedef  void( *const V_freeze)( U16 sig);
typedef  void( *const V_unfreeze)( U16 sig);
/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/

U8 V_asyncreceive_empty( U16 sig, U8* value);
void V_asyncsend_empty( U16 sig, U8* value);
void V_asyncreceive_prehook_empty( U16 sig, U8* value);
void V_asyncreceive_psthook_empty( U16 sig, U8* value);
void V_asyncsend_prehook_empty( U16 sig, U8* value);
void V_asyncsend_psthook_empty( U16 sig, U8* value);
U8 V_syncreceive_empty( U16 sig, U8* value);
void V_syncsend_empty( U16 sig, U8* value);
void V_syncreceive_prehook_empty( U16 sig, U8* value);
void V_syncreceive_psthook_empty( U16 sig, U8* value);
void V_syncsend_prehook_empty( U16 sig, U8* value);
void V_syncsend_psthook_empty( U16 sig, U8* value);
void V_freeze_empty( U16 sig);
void V_unfreeze_empty( U16 sig);

#endif /*_SIGNAL_H_*/

/****************************** END OF FILE ***************************/


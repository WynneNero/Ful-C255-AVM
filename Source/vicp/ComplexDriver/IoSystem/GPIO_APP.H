/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   : Shao Guangxian										   *
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
* 0.2    Jan 05,2017   ShangQiuju Update GetVal function according SIG module update.
*------------------------------------------------------------------------
* 0.3    Jan 11,2017  ZhangJie  Add u for constant value to avoid Coverity warning.
*-----------------------------------------------------------------------
* 0.4  Apr 01,2017   PEI Jingli  Fix headfiles.
*=====================================================================*/
#ifndef _GPIO_APP_H_
#define _GPIO_APP_H_
#include "GPIO_CFG.h"
/**** Definition of constants ****/


/**** Definition of types ****/


/**** Definition of macros ****/
/* Development Error Codes */
#define SIG_DIO_E_UNINIT 							    (0x10U) /* No initialization error code. */
#define SIG_DIO_E_ALREADY_INITIALIZED 		(0x11U) /* Already initialization error code. */
#define SIG_DIO_E_PARAM_SIGNAL 					(0x12U) /* The channel is busy error code. */

#define SIG_DIO_READING_INVALID 0xFFU
#define SIG_DIO_VALUE_INVALID 0xFFU



/**** Declaration of constants ****/

/**** Declaration of variables ****/
typedef struct
{
	BOOL InitState; /*record the init state of this module*/	
	U8 RawValue[SIG_DIO_IN_NUM];	/*store the convert result that get from the ResultRegister*/		
	U16 ResultCounter[SIG_DIO_IN_NUM];
	U8 ResultValue[SIG_DIO_IN_NUM];/*store the convert result after 1 order filter*/	
	BOOL FreezeReq[SIG_DIO_IN_NUM];
} Sig_DioInData;

typedef struct
{
	BOOL InitState; /*record the init state of this module*/		
	U8 RawValue[SIG_DIO_OUT_NUM];	/*store the convert result that get from the ResultRegister*/	
	BOOL FreezeReq[SIG_DIO_OUT_NUM];
} Sig_DioOutData;

/**** Declaration of functions ****/
/**** Declaration of functions ****/
/*******************************************************************************************
* EXPORT INTERFACE DEFINITIONS AND DECLARATIONS
*
* In this section
* - define helpful macros for easy data access and for a comfortable function use, if 
*   necessary.
* - define all global define-constants of your module.
* - declare all system global ROM-constants.
* - define all global type definitions of your module.
* - declare all system global variables of your module.
********************************************************************************************/
extern void Sig_DioInit(void);
extern void Sig_DioDeInit(void);
extern void Sig_DioTick(void);
extern void Sig_DioWriteValue(U16 Signal, U8* value);

extern U8 Sig_DioGetRawValue(U16 Signal);
extern U8 Sig_DioGetValue(U16 Signal,U8* pvalue);
extern U8 Sig_DioGetDirectValue(U16 Signal, U8* pvalue);


extern void Dio_OutFreeze(void);
extern void Dio_OutUnFreeze(void);
extern void Dio_InFreeze(void);
extern void Dio_InUnFreeze(void);

extern void Di_FreezeSignal(U16 Signal);
extern void Di_UnFreezeSignal(U16 Signal);
extern void Do_FreezeSignal(U16 Signal);
extern void Do_UnFreezeSignal(U16 Signal);

#endif
/****************************** END OF FILE ***************************/

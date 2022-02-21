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
* 0.1    Feb 10,2013    NI Rujin    Initial version
* ----------------------------------------------------------------------
* 0.2    Mar 11,2013    LIU Chenxi  Correct function signature
*----------------------------------------------------------------------
* 0.3    Jan 5,2017     ShangQiuju    change CS_SIG_AsyncReceive /CS_SIG_SyncReceive
                                                    parameter plocalSignalCopy from u16* to U8* 
*=====================================================================*/
#ifndef _SIGNAL_IF_H_
#define _SIGNAL_IF_H_ 
#include "Signal.h"

/**** Definition of constants ****/


/**** Definition of macros ****/
/* Macro definitions*/
extern void CS_SIG_Init(void);
extern void CS_SIG_DeInit(void);
extern U16  CS_SIG_ToGlobalName(U16 SigName, Sig_SignalType type);
extern void CS_SIG_AsyncSend(U16 SigName, U8* plocalSignalCopy);
extern U8 CS_SIG_AsyncReceive(U16 SigName, U8* plocalSignalCopy);
extern void CS_SIG_SyncSend(U16 SigName, U8* plocalSignalCopy);
extern U8 CS_SIG_SyncReceive(U16 SigName, U8* plocalSignalCopy);

/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/



#endif /*_SIGNAL_IF_H_*/

/****************************** END OF FILE ***************************/


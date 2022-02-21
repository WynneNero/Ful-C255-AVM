/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                         *
*   AUTHOR     :                                       *
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
------------------------------------------------------------------------
* 0.1	   Jun 26,2016   PEI Jingli  Initial version
------------------------------------------------------------------------
* 0.2	   July 21,2016  PEI Jingli  Refine code structure.
*-----------------------------------------------------------------------
* 0.3          Jan 17,2017   ZhangJie   Remove unused include file.
*=====================================================================*/

#ifndef _TRACE_H_
#define _TRACE_H_
//#include <Core_I.h>
#include "Tools.h"


/**** Definition of constants ****/


/**** Definition of macros ****/


/**** Declaration of constants ****/

/**** Declaration of variables ****/

/**** Declaration of functions ****/
extern void EndLog(void);


extern void TraceOut_ByteArray(U8* pinfo, U8 Len);
extern void TraceOut_Msg(char* msg);
extern void TraceOut_Messages(char* msg1, U8* msg2, U8 msg2Len);
extern void TraceOut_MsgAndChar(char* msg, U8 ch);
extern void TraceOut_MsgWithNumber(char* msg, U8 number);
extern void TraceOut_SenTmsgACK(U8 msgid, BOOL isSent);

#endif /*_NAVIDRIVER_H_*/

/****************************** END OF FILE ***************************/


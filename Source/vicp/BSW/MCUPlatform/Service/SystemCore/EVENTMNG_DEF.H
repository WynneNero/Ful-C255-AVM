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
*------------------------------------------------------------------------
* 0.1 Jun 13,2016                Init version.
*------------------------------------------------------------------------
* 0.2 Jan 24,2017  ZhangJie  Fix Coverity warnings.
*=====================================================================*/
/**** Definition of constants ****/

/**** Definition of macros ****/
/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/
#ifdef EVENT_PASS_1
    #undef EVENT_PASS_1
    #define BEGIN_EVTDESCS       typedef enum {
    #define END_EVTDESCS         SYSEVT_EVENT_NUM}Evt_EventType; 
    #define EVTDESC(x,y)   x,

   /*#define BEGIN_EVTDESCPROCS(y,n) */
   /*#define END_EVTDESCPROCS*/ 
   /*#define ADDDESCPROC(p)  */
  
   #include <EVENTMNG_CFG.h>

   #define SYSEVT_EVENT_MAX ((U8)SYSEVT_EVENT_NUM+1u)
#endif

#ifdef EVENT_PASS_2
    #undef EVENT_PASS_2
    #define BEGIN_EVTDESCS	
    #define END_EVTDESCS		
    #define EVTDESC(x,y)      extern void y(void);

   /*#define BEGIN_EVTDESCPROCS(y,n) */
   /*#define END_EVTDESCPROCS*/ 
   /*#define ADDDESCPROC(p) */ 
 
   #include <EVENTMNG_CFG.h>
   
#endif

#ifdef EVENT_PASS_3
    #undef EVENT_PASS_3
    #define BEGIN_EVTDESCS	const Func_Void_Proc SysEvt_apEventProc[SYSEVT_EVENT_MAX]={
    #define END_EVTDESCS		NULL};
    #define EVTDESC(x,y)      {y},

   /*#define BEGIN_EVTDESCPROCS(y,n) */
   /*#define END_EVTDESCPROCS */
   /*#define ADDDESCPROC(p) */ 
 
   #include <EVENTMNG_CFG.h>
   
#endif

/****************************** END OF FILE ***************************/


/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.			*
*				  All Rights Reserved.          	*
*   Department : CT AD     						*
*   AUTHOR	   : 							*
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
* 0.1          Jun 11,2016                  Init version.
*------------------------------------------------------------------------
* 0.2          Jan 11,2017  ZhangJie  Add parentheses and explicit variable cast to avoid Coverity warning.
*=====================================================================*/
/**** Definition of constants ****/

/* Switch to select if the X ms auxiliary timer A is to be supported or not. */
/**** Definition of macros ****/
/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/
#ifdef JOB_PASS_3
    #undef  JOB_PASS_3
    #define BEGIN_JOBS        const  Func_Void_Proc  SysJob_apProc[SYSJOB_JOB_MAX] = {
    #define END_JOBS          NULL};
    #define JOB(x,y)          y,
  
    #include <JobMng_cfg.h>

#endif

#ifdef JOB_PASS_2
    #undef  JOB_PASS_2
    #define BEGIN_JOBS
    #define END_JOBS
    #define JOB(x,y)         extern void y(void);

    #include <JobMng_cfg.h>

#endif

#ifdef JOB_PASS_1
    #undef JOB_PASS_1
    #define BEGIN_JOBS        enum SYSJOB_ENUM {
    #define END_JOBS          SYSJOB_JOB_NUM };
    #define JOB(x,y)          x,
 
    #include <JobMng_cfg.h>

   #define SYSJOB_JOB_MAX	((U8)SYSJOB_JOB_NUM+1u)
#endif


/****************************** END OF FILE ***************************/


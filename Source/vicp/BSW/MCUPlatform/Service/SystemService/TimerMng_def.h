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
* 0.1          Jun 11,2016                  Init version.
*------------------------------------------------------------------------
* 0.2          Jan 12,2017  ZhangJie  Add parentheses and explicit variable cast to avoid Coverity warning.
*-----------------------------------------------------------------------
* 0.3          Feb 09,2017   ZhangJie   Using micro to include headfile.
*=====================================================================*/
/**** Definition of constants ****/

/**** Definition of macros ****/
/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/
#ifdef TIMERMNG_PASS_3
#undef TIMERMNG_PASS_3
    #define BEGIN_TIMER        const  Func_Void_Proc TimerMng_apProc[SYSTIMER_MAX] = {
    #define END_TIMER          NULL};
    #define TIMER(x,y)          y,
	
    #include TIMERMNG_CFG_H_PATH

#endif

#ifdef TIMERMNG_PASS_2
#undef TIMERMNG_PASS_2

    #define BEGIN_TIMER
    #define END_TIMER
    #define TIMER(x,y)         extern void y(void);
     
    #include TIMERMNG_CFG_H_PATH
  
#endif

#ifdef TIMERMNG_PASS_1
#undef TIMERMNG_PASS_1
    #define BEGIN_TIMER        enum TIMERMNG_ENUM {
    #define END_TIMER          TIMERMNG_TIM_NUM };
    #define TIMER(x,y)          x,

    #include TIMERMNG_CFG_H_PATH
    
    #define SYSTIMER_MAX     ((U8)TIMERMNG_TIM_NUM+1u)
#endif

/****************************** END OF FILE ***************************/


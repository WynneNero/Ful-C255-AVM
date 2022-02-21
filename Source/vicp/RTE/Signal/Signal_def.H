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
* Version       Date      Name    Changes and comments
 ----------------------------------------------------------------------
* 0.1    Jun 26,2016                    Initial version
 ----------------------------------------------------------------------
* 0.2    Dec 21,2016    PEI Jingli  add file patch according using hw
 ----------------------------------------------------------------------
* 0.3    Jan 5,2017       ShangQiuju   using signal_cfg.h Pacth configed at config.h
*------------------------------------------------------------------------
* 0.4   Apr 04,2017   PEI Jingli  Fix headfile included.
*=====================================================================*/
#include "Config.h"
/**** Definition of constants ****/

/**** Definition of macros ****/
/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/
#ifdef SIGNAL_PASS_2
    #undef  SIGNAL_PASS_2
    #define BEGIN_SIG        const Signal AllSignal[E_SIG_SIGNALS_NUM] = {
    #define END_SIG          };
    #define SIGDESC(x,y,z)          {y,z},
    #include SIG_CFG_H_PATH
#endif

#ifdef SIGNAL_PASS_1
    #undef SIGNAL_PASS_1
    #define BEGIN_SIG        enum Sig_SignalName {
    #define END_SIG          E_SIG_SIGNALS_NUM };
    #define SIGDESC(x,y,z)          x,
    #include SIG_CFG_H_PATH
#endif


/****************************** END OF FILE ***************************/


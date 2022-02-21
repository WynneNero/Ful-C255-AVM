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
*------------------------------------------------------------------------
* 0.1          Jun 11,2016                Init version.
*------------------------------------------------------------------------
* 0.2          Jan 24,2017  ZhangJie  Fix Coverity warnings.
*=====================================================================*/
#ifndef _SYSTEM_STATE_CFG_H_
#define _SYSTEM_STATE_CFG_H_
#include<Core_I.h>
#include <SysSwitch.h>
/*System state config*/
enum
{
    SYSSTATE_RESET_STATE= SYS_S0,
    SYSSTAT_SLEEP_STATE= SYS_S1,
    SYSSTAT_MODESWITCH_STATE= SYS_S2,
    SYSSTAT_NORMAL_STATE= SYS_S3,
    SYSSTAT_FCT_STATE =SYS_S4,
    SYSSTATE_STATE_NUMBER=SYS_S5
};


#define SYSTEM_STATE_METHOD SYSSTATE_FULLSTATE

#if (SYSTEM_STATE_METHOD==SYSSTATE_UPDOWNSTATE)
#define SYSSTATE_HANDLER_ACTIVATIVATION_EXCEPTION()
#define SYSSTATE_MULTI_SWITCH_MAXNUM 2u

/*from s0--> S1-->S2*/
#define SYSSTATE_INIT_OF_STATE_IDENT_ARRAY SYSSTATE_RESET_STATE, \
                                        SYSSTAT_SLEEP_STATE, \
                                        SYSSTAT_MODESWITCH_STATE,\
                                        SYSSTAT_NORMAL_STATE,\
                                        SYSSTAT_FCT_STATE
#endif
#endif /*_BUS_CFG_H_*/

/****************************** END OF FILE ***************************/


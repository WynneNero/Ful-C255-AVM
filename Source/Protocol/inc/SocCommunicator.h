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
* 
*=====================================================================*/
#ifndef _SOC_COMMUNICATOR_H_
#define _SOC_COMMUNICATOR_H_ 
#include "SocMsgHandler.h"
/**** Definition of constants ****/


/**** Definition of macros ****/

enum NAVI_SWDL_STATUS_EVENT_TYPE_PARAM
{
    SWDL_RADIO,
    SWDL_OS,
    SWDL_NAVI,    
    SWDL_MCU,
    SWDL_DSP,
    SWDL_GPS,
    SWDL_SLEEP,
};

enum NAVI_STATUS_PARAM
{
    FIRST_CONNECT,
    POWER_UP,
    POWER_DOWN,
};

enum POWER_MODE_PARAM
{
    TO_NORMAL_SLEEP, // not_used
    TO_STANDBY,
    TO_USER_ON,
    TO_FIRST_CONNECT_SLEEP, // not_used
    TO_POWER_UP, // not_used
    SHUT_DOWN_ACK, // not_used
    SCREEN_LOCK, //G4 used 
    SCREEN_UNLOCK,
};


enum POWER_MODE_PARAM2
{
    ON_OFF_NORMAL,
    ON_OFF_VLOW,
    AUDIO_OFF,
};


#define	HQ_CMD 0
#define LQ_CMD 1
/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/
#endif /*_SOC_COMMUNICATOR_H_*/

/****************************** END OF FILE ***************************/


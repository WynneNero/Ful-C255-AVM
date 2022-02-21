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
*
*=====================================================================*/
#ifndef _SOC_SERVICE_H_
#define _SOC_SERVICE_H_

#include "CONFIG.H"
#include "TYPES.H"
#include "SocCommunicator.h"
#include "CanDiagService.h"
#include "eol_app.h"


/**** Definition of constants ****/
#define NAVI_ERRORWAIT 150   // 3S
#define T_RECEVIE_MAXTIME 1500 // 30s
#define N_SENDFAIL_MAXCOUNT 15 //send fail 
#define NAVI_FIRST_CONNECT_RESP_TIME (1*60*100)  // 1 min
#define NAVI_NORMAL_RESP_TIME 30*100 //3S
#define NAVI_CONNECTED_FAIL_TIMES 3
#define WATCH_DOG_TIME_OUT 10*50
#define WATCH_DOG_TIME_OUT_WARNING 10*40
#define WATCH_DOG_TIME_OPEN_PMIC 200
#define VOL_SOC_CNT 25
#define H_VOL_SOC_CNT 75

#define SOC_WATCHDOG 

/**** Definition of macros ****/
#define EOLAPP_DISPATCHER_MSG(commandid, data)  EOL_DISPATCHERSPIMSG(commandid,data)
#define CANDIA_DISPATCHER_MSG(commandid, data)  CanDiag_recvnavimsg_handler(commandid,data)




/**** Declaration of constants ****/
typedef void (*NAVISERVER_REQMSG_HANDLER)(U8 Msgid, U8* data, U8 len);
typedef void (*NAVISERVER_RESPMSG_HANDLER)(U8 Msgid, U8 result,U8* data, U8 len);
typedef void (*NAVISERVER_SEND_RESULT_HANDLER)(U8 Msgid, BOOL isSend) ;
/**** Declaration of variables ****/

typedef enum
{
    E_SOC_IDLE,
    E_SOC_POWER_ON,
    E_SOC_READY,
    E_SOC_CONNECTED,
    E_SOC_ERROR_COMMUNICATOR,
    E_SOC_POWER_OFF,
    E_SOC_DEV_POWER_OFF,

 } E_SOC_STATE;
	
typedef enum
{
	E_EOL_STATUS_OFF,
	E_EOL_STATUS_ON,
}E_EOL_STATUS;


typedef enum
{
    E_SOC_CONNECTED_STARTED,
    E_SOC_CONNECTED_WAIT_FIRST_CONNECT_COMPLETE_EVENT,
    E_SOC_CONNECTED_SEND_POWERUP_REQ,
    E_SOC_CONNECTED_WAIT_POWERUP_RESP,
    E_SOC_CONNECTED_FINISHED,    
    E_SOC_CONNECTED_ERROR,
    E_SOC_CONNECTED_FAILED,
}SOC_CONNECTED_STATE;


extern void Upgrade_DISPATCHERMSG(U16 commandid,U8* data);
extern void DTC_recvnavimsg_handler(U16 commandid, U8* data);

#define Notify_Upgrade_Req(commandid,data) Upgrade_DISPATCHERMSG(commandid,data)
#define SOC_DISPATCHER_DTC_MSG(commandid,data)  DTC_recvnavimsg_handler(commandid,data)

extern E_SOC_STATE eSocState;

/**** Declaration of functions ****/
void SocManager_Init(void);
void SocManager_DeInit(void);
void SocManager_20msEntry(void);
void CorlCameraStatus(void);
extern BOOL SocManager_SendMsg(U8 q_type, U8 cmd_type, U16 service, U8 nArgs,U8 *pArg);

extern BOOL	bPowerOnAllow;

extern BOOL SOC_SLEEP_SWITCH;
extern E_EOL_STATE eEolState;

/**** Definition of macros ****/
///TODO:ADD DISPATCH FUNCTION
#endif /*_SOC_SERVICE_H_*/

/****************************** END OF FILE ***************************/


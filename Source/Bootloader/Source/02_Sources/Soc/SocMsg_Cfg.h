/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD NJ    									   *
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
* ----------------------------------------------------------------------
*   0.1         2016/8/20       ShangQiuju      Init verssion
*=====================================================================*/
#ifndef _SOC_MSG_CFG_H_
#define _SOC_MSG_CFG_H_ 

/**** Definition of constants ****/

#define SOC_FRAME_MAXLENGTH 255
typedef enum
{
  E_MSG_SAFE=1,
  E_MSG_DIG,
  E_MSG_GEN,
  E_MSG_DBG,
  E_INVALD_PRI
}E_NAVIMSGID_PRI;

/**** Definition of macros ****/
typedef struct
{
U8 MsgReqType;
U8 MsgRepType;
U8 MsgPriority;
U16 MsgIDVal;
}MsgConfig;


#define MAX_LIST_ITEMS 30
#define MAX_PAGE_ITEMS 5
#define SVR(x,y)                  (((x << 3) + y)<<8)

enum CMPT_ID_ITEM
{
    CMPT_ID_GEN,       //0
    CMPT_ID_REC,       //1
    CMPT_ID_CD,        //2
    CMPT_ID_COMMONINFO,   // 3
    CMPT_ID_MP3,       //4
    CMPT_ID_DVD,       //5
    CMPT_ID_AUDIO,     //6
    CMPT_ID_CLOCK,     //7
    CMPT_ID_SYSTEM,    //8
    CMPT_ID_INP,       //9
    CMPT_ID_OOM,       //10
    CMPT_ID_PWM,       //11
    CMPT_ID_NAVIGATION,     //12
    CMPT_ID_AUX,       //13
    CMPT_ID_THIEFT,    //14
    CMPT_ID_DIAG,      //15
    CMPT_ID_EOL,  //16
    CMPT_ID_BT_PHONE,  //17
    CMPT_ID_MEDIA,     //18
    CMPT_ID_HVAC,     //19
    CMPT_ID_END       //20
};

enum EN_CMD_TYPE
{
    TYPE_SERVICE=1,
    TYPE_QUERY,
    TYPE_RESPONSE,
    TYPE_EVENT,
    TYPE_CONTROL,
    TYPE_UTILITY,
    TYPE_MAX
};

enum COMMON_INFO_REQUEST
{
    J6_REQUEST_M3_SOFT_VERSION = 0x4201,
    J6_REQUEST_M3_TO_RESEND_IMPORTANT_MESSAGE = 0x4202,
    J6_NOTIFY_M3_CAMERA_FAULT = 0x4203,
    M3_REQUEST_J6_TO_SEND_USB_INTERFACE_STATUS = 0x4204,
};

enum COMMON_INFO_RESPONSE
{
    M3_SEND_SOFT_VERSION_TO_J6 = 0x4301,
    M3_SEND_RESP_OF_J6_NOTIFY_M3_CAMERA_FAULT = 0x4303,
    J6_SEND_RESP_OF_USB_INTERFACE_STATUS = 0x4304,
};


enum COMMU_SYSTEM_EVENT
{      
    RADIO_NOTIFY_SPEED_DATA =0x4401,
    RADIO_NOTIFY_PLUS_COUNT_DATA,//0x4402
    RADIO_NOTIFY_TURNING_SIGNAL,//0x4403
    RADIO_NOTIFY_STEERING_WHEEL_DATA,//0x4404
    RADIO_NOTIFY_RVC_STATUS,//0x4405
};

enum OOM_EVENT
{
    NAVI_CURRENT_POWER_SATET = SVR(CMPT_ID_OOM,TYPE_EVENT)+1,   /*5401 NEED USED*/
    NAVI_RESP_EVENT,
    NAVI_SPECIAL_EVENT,
    NAVI_30_HOUR_RESET_FINISH,
    NAVI_SWDL_CONFIG_EVENT=0x5410,
    NAVI_START_END_SWDL_FILE_EVENT,
    NAVI_SWDL_DATA_EVENT,
    NAVI_SWDL_STATUS_EVENT,//0x5413
    NAVI_REQ_TO_RESET_EVENT, //= 0x5502,//0x5502
    NAVI_SELF_UPGRADE_RESULT_EVENT, //= 0x5415,//0x5415
};


enum SWDL_ENTER_EXIT_PARAM
{
    ENTER_SWDL,
    EXIT_SWDL,     
    FINISH_SWDL,
};
enum SWDL_STATUS_EVENT_TYPE_PARAM
{
    SWDL_MCU,
    SWDL_OS,
    SWDL_SOC,
};

enum SWDL_GET_DATA_PARAM
{
    NEXT_FRAME,
    CURR_FRAME,     
};

enum SWDL_STATUS_EVENT_STATE_PARAM
{
    SWDL_STATE_START,
    SWDL_STATE_END,
};

enum SHUT_DOWN_EVENT_PARAM
{
    NAVI_SHUTTING_DOWN,
    NAVI_POWER_UP,
    NAVI_FIRST_CONNECT_GO_TO_SLEEP,
    NAVI_FIRST_CONNECT_COMPLETE,
    NAVI_STANDBY,
    NAVI_NORMAL_GO_TO_SLEEP,
};

typedef enum
{
	SOC_INIT_STATE,
	SOC_UNWAKEUP_STATE,
	SOC_CANWAKEUP_STATE,
	SOC_TEMPORARY_WAKEUP_STATE,
	SOC_NORMAL_STATE
}SOC_SEND_PW_STATE_PARAM;

enum START_END_SWDL_FILE_EVENT_PARAM
{
    START_READ_FILE,
    END_READ_FILE,
};


enum OOM_SERVICE
{
    RADIO_DISPATCH_CHANGE_POWER_MODE= SVR(CMPT_ID_OOM,TYPE_SERVICE)+1,/*5101 USED*/
    RADIO_DISPATCH_SET_BACK_LIGHT,
    RADIO_DISPATCH_ERROR_SET_BACK_LIGHT,
    RADIO_DISPATCH_NAVI_30_HOUR_RESET,
    RADIO_DISPATCH_SWDL_GET_DATA=0x5110,
    RADIO_DISPATCH_SWDL_ENTER_EXIT,//0x5111
    RADIO_DISPATCH_SWDL_UPDATE_STATUS,//0x5112
};


enum OOM_QUERY
{
    NAVI_GET_RADIO_STATUS = SVR(CMPT_ID_OOM,TYPE_QUERY)+1,  //0x5201
};

enum OOM_RESPONSE
{
    RADIO_SEND_RECV_J6_SELFUPGRADE_RESP=0x5301,
	RADIO_RECV_J6_RESET_ACK = 0x5302,
	RADIO_SEND_RECV_J6_FILERESULT_RESP=0x5305,
};


enum EOL_QUERY
{
    RADIO_QUERY_ENG_SW_VERSION=SVR(CMPT_ID_EOL,TYPE_QUERY)+1,//8201
    FORWARD_QUERY_J6_TO_START_UPGRADE_LICENSE_REQ,//8202
    FORWARD_QUERY_J6_TO_SEND_LICENSE_HW_INFO_REQ,//8203
    FORWARD_QUERY_J6_OF_LICENSE_TRANSMIT_REQ,//8204
    FORWARD_QUERY_J6_OF_LICENSE_TRANSMIT_DATA,//8205
    #ifdef AB01_HW
    RADIO_REQUEST_A6_ENTER_FAIL_SAFE_MODE = 0x8206,
    #endif
    RADIO_REQUEST_SET_J6_CONFIG_DATA = 0x8207,
    RADIO_REQUEST_GET_J6_CONFIG_DATA = 0x8208,
    J6_NOTIFY_M3_SELFTEST_RESULT = 0x8401,
    M3_SEND_RESP_OF_J6SELFTEST = 0x8301,
    J6_SEND_RESPONSE_OF_VERSION = 0x8302,
    FORWARD_START_UPGRADE_LICENSE_RESP_TO_PC,//8303
    FORWARD_SEND_LICENSE_HW_INFO_RESP_TO_PC,//8304
    FORWARD_LICENSE_TRANSMIT_REQ_RESP_TO_PC,//8305
    FORWARD_LICENSE_TRANSMIT_DATA_RESP_TO_PC,//8306
    #ifdef AB01_HW
    A6_SEND_ENTER_FAIL_SAFE_MODE_RESP_TO_RADIO = 0x8307,
    #endif
    J6_SEND_RESPONSE_OF_SET_J6_CONFIG_DATA = 0x8308,
    J6_SEND_RESPONSE_OF_GET_J6_CONFIG_DATA = 0x8309,
};

/**** Declaration of constants ****/
extern void SocManager_Dispatcher_Msg(U8 cmpt_id,U16 commandid, U8 size,  U8* data);

#define SOC_MSGDISPATCHER(cmpt_id,commandid,size,data)    SocManager_Dispatcher_Msg(cmpt_id,commandid,size,data)
/**** Declaration of variables ****/

/**** Declaration of functions ****/
#endif /*_SOC_MSG_CFG_H_*/

/****************************** END OF FILE ***************************/


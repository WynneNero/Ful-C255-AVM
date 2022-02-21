/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD NJ     									   *
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
* Version       Date           Name            Changes and comments
* 0.1    	2015-12-15	ShangQiuju		Initial
*=====================================================================*/
/**** System include files ****/
#ifndef _EOL_APP_H_
#define _EOL_APP_H_

#include "CONFIG.H"
#ifdef EOL_OPTION
#include "TYPES.H"
#include "eolMsg_Cfg.h"
#include "eolservice.h"

#define E_POWER_ON_TIMEOUT 50*5  //5S
#define E_EXIST_EOL_TIMEOUT 40//400ms
#define REQMSG_MAX_DATALEN  205
#define RESPMSG_MAX_DATALEN  170
#define NOT_NEEDED_CHECK_LEN    0xff
#define WAIT_J6_RESP_TIME 30
#define WAIT_J6_LICENSE_RESP_TIME 100
#define CN300SVPNOSVERSIONLEN 21

#ifdef AB01_HW
#define WAIT_J6_FAILSAFE_RESP_TIME 500
#endif

#define E_WAIT_EEP_WRITE_EOL_RESULT_TIME  50

enum
{
    E_EXIST_EOL,
    E_ENTER_EOL,
};

enum
{
    E_NONE_VERSION,
    E_M3_BOOT_VERSION = 0X30,
    E_M3_SOFT_VERSION = 0X31,
    E_J6_OS_VERSION = 0X32,
    E_J6_SVP_VERSION = 0X33,
};

enum//lfmark
{
    E_NONE,
    E_USB_STATUS = 0X65,
    E_SDCARD_STATUS = 0X57,
};	

typedef enum
{    
    E_MSGTYPE_ENTER_EOL,//00
    E_MSGTYPE_J6_START_FROM_SD,
    E_MSGTYPE_EXIST_EOL,
    E_MSGTYPE_READ_BOOT_VERSION,
    E_MSGTYPE_READ_SOFTWARE_VERSION,
    E_MSGTYPE_READ_J6OS_VERSION,
    E_MSGTYPE_READ_J6SVP_VERSION,
    E_MSGTYPE_WRITE_SERIAL_NUMBER,
    E_MSGTYPE_READ_SERIAL_NUMBER,
    E_MSGTYPE_READ_M3_DTC,
    E_MSGTYPE_CLEAR_DTC,
    E_MSGTYPE_SET_EEP_CONFIG_VAL,
    E_MSGTYPE_GET_EEP_CONFIG_VAL,
    E_MSGTYPE_ENTER_AVM_PRESS_MODE,
    E_MSGTYPE_ENTER_REVERSE_MODE,
    E_MSGTYPE_READ_POWER_DET,
    E_MSGTYPE_READ_CAN_POWER_DET,
    E_MSGTYPE_READ_IGN,    
    E_MSGTYPE_CONTROL_LED0,    
    E_MSGTYPE_CONTROL_LED1,    
    E_MSGTYPE_CONTROL_CAMERA,    //20
    E_MSGTYPE_READ_REVERSE_SIGNAL,    
    E_MSGTYPE_UPGRADE_J6_LICENSE_START_REQ,
    //E_MSGTYPE_SET_ECU_MANUFACTURING_DATE,
    //E_MSGTYPE_GET_ECU_MANUFACTURING_DATE,
    E_MSGTYPE_UPGRADE_J6_LICENSE_END,
    E_MSGTYPE_SEND_LICENSE_PACKET0,
    E_MSGTYPE_LICENSE0_SEND_FINISHED,
    E_MSGTYPE_SEND_LICENSE_PACKET1,
    E_MSGTYPE_LICENSE1_SEND_FINISHED,
    E_MSGTYPE_SET_ECU_MANUFACTURING_DATE,//28
    E_MSGTYPE_GET_ECU_MANUFACTURING_DATE,//29
    E_MSGTYPE_SEND_LICENSE_PACKET2,
    E_MSGTYPE_LICENSE2_SEND_FINISHED,
    E_MSGTYPE_SEND_LICENSE_PACKET3,
    E_MSGTYPE_LICENSE3_SEND_FINISHED,
    E_MSGTYPE_SEND_LICENSE_PACKET4,
    E_MSGTYPE_LICENSE4_SEND_FINISHED,
    #ifdef AB01_HW
    E_MSGTYPE_ENTER_FAILSAFE_MODE,
    #endif
    E_MSGTYPE_READ_AVM_HW_IN,
    E_MSGTYPE_READ_USB_INTERFACE_STATUS,
    E_MSGTYPE_READ_SDCARD_INTERFACE_STATUS,
    //E_MSGTYPE_SET_J6_CONFIG,
    E_MSGTYPE_GET_J6_CONFIG,
    E_MSGTYPE_CTL_AVM_SHUT_DOWN_TIME,//40
    //E_MSGTYPE_READ_SDCARD_INTERFACE_STATUS,
    E_MSGTYPE_CTL_DTCSETTING_OFF,
    E_MSGTYPE_CTL_AVM_LED,
    //E_MSGTYPE_CTL_AVM_HARDKEY,
    E_MSGTYPE_CTL_ACCON_SETTING_ON,
    E_MSGTYPE_REQ_J6_ENTER_SELF_DIAG,  // REQ_J6_ENTER_SELF_DIAG
    E_MSGTYPE_NUM
}E_MSGTYPE;

typedef enum
{
    E_EOL_INIT,
    E_EOL_SEND_CONNECT_REQ,
    E_EOL_WAIT_CONNNECT_RESP,
    E_EOL_NORMAL,
    E_EOL_EXIT,
    E_EOL_IDLE,
}E_EOL_STATE;


enum
{
    E_ALL_LICENSE_FINISHED,
    E_LICENSE_PACKET_SEND_START,
    E_LICENSE_PACKET0_FINISHED,
    E_LICENSE_PACKET1_FINISHED,
    E_LICENSE_PACKET2_FINISHED,
    E_LICENSE_PACKET3_FINISHED,
    E_LICENSE_PACKET4_FINISHED,
    E_LICENSE_PACKET5_FINISHED,
};

enum
{
    E_LICENSE_PACKET0,
    E_LICENSE_PACKET1,
    E_LICENSE_PACKET2,
    E_LICENSE_PACKET3,
    E_LICENSE_PACKET4,
    E_LICENSE_PACKET5,
};



 typedef struct
{
    E_EOLMSGID_TYPE msgid;
    U8 Reqdatalen;
}REQSTATICMSQ;

typedef  struct
{
    BOOL bReqSent;
    BOOL bRespReceived;
    U16 recvDatatime;
    U8 uRecvDatalen;
    U8 uRecvData[RESPMSG_MAX_DATALEN];    
}E_QUERY_J6_DATA_STRUCT;

typedef struct
{
    E_QUERY_J6_DATA_STRUCT data;
    E_EOLMSGID_TYPE type;
}E_QUERY_J6_LICENSE_STRUCT;

extern E_EOL_STATE eEolState;
extern void J6SelfDiagFlagHandler(void);

#endif
#endif

/**************** END OF FILE *****************************************/

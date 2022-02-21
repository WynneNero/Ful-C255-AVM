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
*-----------------------------------------------------------------------
*   0.1         2016/8/20       ShangQiuju      Init verssion
*-----------------------------------------------------------------------
*   0.2         2017/1/13      ShangQiuju      Fix coverity warnings.
*-----------------------------------------------------------------------
*   0.3         2017/1/19      ShangQiuju      Remove redefinition MAX_MSG_QUEUE
*----------------------------------------------------------------------
*   0.4         2017/3/7       ShangQiuju     soc task change from 20ms to 10ms
*=====================================================================*/
#ifndef _SOC_MSG_HANDLER_H_
#define _SOC_MSG_HANDLER_H_ 
#include "CONFIG.H"
#include "TYPES.H"

#include "SocMsg_Cfg.h"
#include "Driver_IF.H"

/**** Definition of constants ****/
#define MAX_FRAME_LEN 255
//#define MAX_MSG_QUEUE 1
#define INVALID_COMMAND_TYPE 0XFFFF

#define CMD_TYPE        0
#define CMD_ID_H        1
#define CMD_ID_L        2
#define CMD_SIZE        3
#define CMD_FLAG       4
#define CMD_PARAM_START 5

#define NAVI_BASE_LEN 5
#define	TX_HQ 0
#define TX_LQ 1

#define	RX_HQ 0
#define RX_LQ 1

#define TOTAL_TXQ 2
#define FRAME_CNT 12

typedef union
{
    struct
    {
        U8 cmd_num;
        U8 cmd_type :3;
        U8 cmpt_id  :5;
    } id_bit;
    U16 command_ID;
} SOC_CMD_ID;

typedef struct
{
    U8 command_type;
    SOC_CMD_ID command_ID;
    U8 command_size;
    U8 *param;
} SOC_FRAME;


typedef struct
{
    U16 command_type;
    U8 *param;
    U8 len;
} MSGQ_INFO;


typedef enum
{
    E_NO_CONTROL,
    E_ENABLE_CONTROL,
    E_DISABLE_CONTROL
} E_COMCONTROL;


/**** Declaration of variables ****/

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
   E_DATA_RECEIVED,
   E_DATA_SENT,
   E_DATA_SENT_FAIL,
   E_DRIVER_ERROR,
}E_DRIVER_EVENT;

/**** Declaration of functions ****/
void SocMsg_ReceiveCallback(U8* data, U8 len);
void SocMsg_Sent(BOOL isSent);
void SocMsg_Init(void);
void SocMsg_DeInit(void);
void SocMsg_20ms_Entry(void);
void SocMsg_ControlCommunication(BOOL isEnable);
void SocMsg_ControlPower(E_DEV_POWER action);
BOOL SocMsg_SendMessage(U8* pData, U8 len);
extern BOOL SocMsg_GetPower(U8 state);


#endif /*_SOC_MSG_HANDLER_H_*/

/****************************** END OF FILE ***************************/


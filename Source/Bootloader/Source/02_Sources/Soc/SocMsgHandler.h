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
* ----------------------------------------------------------------------
*   0.1         2016/8/20       ShangQiuju      Init verssion
*=====================================================================*/
#ifndef _SOC_MSG_HANDLER_H_
#define _SOC_MSG_HANDLER_H_ 
#include "CONFIG.H"
#include "define.h"

#include "SocMsg_Cfg.h"

/**** Definition of constants ****/
#define MAX_FRAME_LEN 255
#define MAX_MSG_QUEUE 1
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



/**** Declaration of functions ****/
void SocMsg_ReceiveCallback(U8* data, U8 len);
void SocMsg_Sent(BOOL isSent);
void SocMsg_Init(void);
void SocMsg_DeInit(void);
void SocMsg_Entry(void);
void SocMsg_ControlCommunication(BOOL isEnable);
void SocMsg_ControlPower(E_DEV_POWER action);
BOOL SocMsg_SendMessage(U8* pData, U8 len);

#endif /*_SOC_MSG_HANDLER_H_*/

/****************************** END OF FILE ***************************/


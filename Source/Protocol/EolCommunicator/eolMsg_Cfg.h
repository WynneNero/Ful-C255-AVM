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
#ifndef _EOL_MSG_CFG_H_
#define _EOL_MSG_CFG_H_
#include "config.h"

#ifdef EOL_OPTION
#include "eolUartDriver_if.h"


/**** Definition of constants ****/
#define   E_CMDTYPE_INVALID      0x0000

#define EOL_REQ_WITHACK         EOL_REQ_ACK
#define EOL_REQ_WITHOUTACK  EOL_REQ_NOACK
#define EOL_REP_WITHACK         EOL_REP_ACK
#define EOL_REP_WITHOUTACK  EOL_REP_NOACK
#define MSG_INVALID             0xFF

typedef enum
{
    E_EOL_MSG_SAFE=1,
    E_EOL_MSG_DIG,
    E_EOL_MSG_GEN,
    E_EOL_MSG_DBG,
    E_EOL_INVALD_PRI
} E_EOLMSGID_PRI;

/**** Definition of macros ****/
typedef struct
{
    U8 MsgIDVal;
} EOLMsgConfig;

typedef enum
{
    /* 00 */E_MSGID_INVALID,
    /* 01 */E_MSDID_START_EOL,
    /* 02 */E_MSGID_ENTER_EOL,
    /* 03 */E_MSGID_J6_START_FROM_SD,
    /* 04 */E_MSGID_EXIST_EOL,
    /* 05 */E_MSGID_READ_BOOT_VERSION,
    /* 06 */E_MSGID_READ_SOFTWARE_VERSION,
    /* 07 */E_MSGID_READ_J6OS_VERSION,
    /* 08 */E_MSGID_READ_J6SVP_VERSION,
    /* 09 */E_MSGID_WRITE_SERIAL_NUMBER,
    /* 10 */E_MSGID_READ_SERIAL_NUMBER,
    /* 11 */E_MSGID_READ_M3_DTC,
    /* 12 */E_MSGID_CLEAR_DTC,
    /* 13 */E_MSGID_SET_EEP_CONFIG_VAL,
    /* 14 */E_MSGID_GET_EEP_CONFIG_VAL,
    /* 15 */E_MSGID_REPORT_J6_DTC_START,
    /* 16 */E_MSGID_REPORT_J6_DTC_RESULT,
    /* 17 */E_MSGID_REPORT_J6_UPGRADE_RESULT,
    /* 18 */E_MSGID_ENTER_AVM_PRESS_MODE,
    /* 19 */E_MSGID_ENTER_REVERSE_MODE,
    /* 20 */E_MSGID_READ_POWER_DET,
    /* 21 */E_MSGID_READ_CAN_POWER_DET,
    /* 22 */E_MSGID_READ_IGN,    
    /* 23 */E_MSGID_CTL_LED0,
    /* 24 */E_MSGID_CTL_LED1,
    /* 25 */E_MSGID_CTL_CAMERA,
    /* 26 */E_MSGID_READ_REVERSE_SIGNAL,
    /* 27 */E_MSGID_UPGRADE_J6_LICENSE_START_REQ,
    /* 28 */E_MSGID_SET_ECU_MANUFACTURING_DATE,
    /* 29 */E_MSGID_GET_ECU_MANUFACTURING_DATE,
    /* 30 */E_MSGID_UPGRADE_J6_LICENSE_END,
    /* 31 */E_MSGID_SEND_LICENSE_PACKET0,
    /* 32 */E_MSGID_LICENSE0_SEND_FINISHED,
    /* 33 */E_MSGID_SEND_LICENSE_PACKET1,
    /* 34 */E_MSGID_LICENSE1_SEND_FINISHED,
    /* 35 */E_MSGID_SEND_LICENSE_PACKET2,
    /* 36 */E_MSGID_LICENSE2_SEND_FINISHED,
    /* 37 */E_MSGID_SEND_LICENSE_PACKET3,
    /* 38 */E_MSGID_LICENSE3_SEND_FINISHED,
    /* 39 */E_MSGID_SEND_LICENSE_PACKET4,
    /* 40 */E_MSGID_LICENSE4_SEND_FINISHED,
    #ifdef AB01_HW
    /* 41 */E_MSGID_ENTER_FAILSAFE_MODE,
    #endif
    /* 42 */E_MSGID_READ_AVM_HW_IN,
    /* 43 */E_MSGID_READ_USB_INTERFACE_STATUS,
    /* 47 */E_MSGID_READ_SDCARD_INTERFACE_STATUS,
   // /* 44 */E_MSGID_SET_VEHICLE_CONFIG,
    /* 45 */E_MSGID_GET_VEHICLE_CONFIG,
    /* 46 */E_MSGID_CTL_AVM_SHUT_DOWN_TIME,
  // 	/* 47 */E_MSGID_READ_SDCARD_INTERFACE_STATUS, 
	/*48*/  E_MSGID_CTL_DTCSETTING_OFF, 
	/*49*/  E_MSGID_CTL_AVM_LED, 
    /* 50 */E_MSGID_CTL_ACCONSETTING_ON,
    /* 51 */E_MSGID_REQ_J6_ENTER_SELF_DIAG,
    /* 52 */E_MSGID_NUM,
} E_EOLMSGID_TYPE;

extern void EolService_RequestMsgIn(U8 msgid, U8* data, U8 len);
extern void EolService_ResponseMsgIn(U8 msgid, U8 Result, U8* data, U8 len);
extern void EolService_SendACKIn(U8 msgid, BOOL isSent);
#define EOL_MSGDISPATCHER(msgid, data, len)    EolService_RequestMsgIn(msgid, data, len)
/**** Declaration of constants ****/

/**** Declaration of variables ****/

/**** Declaration of functions ****/
U8 GetEOLMessageIDValue(U8 MessageID);
U8 GetEOLMessageID(U8 val);
#endif
#endif /*_EOL_MSG_CFG_H_*/

/****************************** END OF FILE ***************************/


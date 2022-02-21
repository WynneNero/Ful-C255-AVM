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
#include "config.h"

#ifdef EOL_OPTION
#include "eOLMsg_Cfg.h"

const EOLMsgConfig EolMessageTable[E_MSGID_NUM] =
{
  //MsgValue
    {E_CMDTYPE_INVALID} ,
    {0x00},// E_MSDID_START_EOL,01
    {0x01},//  E_MSGID_ENTER_EOL,02
    {0x02},//  E_MSGID_J6_START_FROM_SD,03
    {0x05},//  E_MSGID_EXIST_EOL,04
    {0X30},//  E_MSGID_READ_BOOT_VERSION,05
    {0X31},//   E_MSGID_READ_SOFTWARE_VERSION,06
    {0X32},//  E_MSGID_READ_J6OS_VERSION,07
    {0X33},//  E_MSGID_READ_J6SVP_VERSION,08
    {0x34},//  E_MSGID_WRITE_SERIAL_NUMBER,09
    {0x35},//  E_MSGID_READ_SERIAL_NUMBER,10
    {0x36},//  E_MSGID_READ_M3_DTC,11
    {0x37},//  E_MEGID_CLEAR_DTC,12
    {0x38},//  E_MSGID_SET_EEP_CONFIG_VAL,13
    {0x39},//  E_MSGID_GET_EEP_CONFIG_VAL,14
    {0x40},//  E_MSGID_REPORT_J6_DTC_START,15
    {0x41},//  E_MSGID_REPORT_J6_DTC_RESULT,16
    {0x42},//  E_MSGID_REPORT_J6_UPGRADE_RESULT,17   
    {0x51},//  E_MSGID_ENTER_AVM_PRESS_MODE,18
    {0x52},//  E_MSGID_ENTER_REVERSE_MODE,19 
    {0x60},//  E_MSGID_READ_POWER_DET,20
    {0x61},// E_MSGID_READ_CAN_POWER_DET,21
    {0x62},//  E_MSGID_READ_IGN,22    
    {0x53},//  E_MSGID_CTL_LEFT_LED,23
    {0x54},//  E_MSGID_CTL_RIGHT_LED,24
    {0x55},//  E_MSGID_CTL_CAMERA,25
    {0x63},//  E_MSGID_READ_REVERSE_SIGNAL,26
    {0x70},//  E_MSGID_UPGRADE_J6_LICENSE_START_REQ,27
    {0x71},//  E_MSGID_SET_ECU_MANUFACTURING_DATE      ,28
    {0x72},//  E_MSGID_GET_ECU_MANUFACTURING_DATE//E_MSGID_UPGRADE_J6_LICENSE_START,29
    {0x73},//  E_MSGID_UPGRADE_J6_LICENSE_END,30
    {0x74},//  E_MSGID_SEND_LICENSE_PACKET0,31
    {0x75},//  E_MSGID_LICENSE0_SEND_FINISHED,32
    {0x76},//  E_MSGID_SEND_LICENSE_PACKET1,33
    {0x77},//  E_MSGID_LICENSE1_SEND_FINISHED,34
    {0x78},//  E_MSGID_SEND_LICENSE_PACKET2,35
    {0x79},//  E_MSGID_LICENSE2_SEND_FINISHED,36
    {0x7A},//  E_MSGID_SEND_LICENSE_PACKET3,37
    {0x7B},//  E_MSGID_LICENSE3_SEND_FINISHED,38
    {0x7C},//  E_MSGID_SEND_LICENSE_PACKET4,39
    {0x7D},//  E_MSGID_LICENSE4_SEND_FINISHED,40
    #ifdef AB01_HW
    {0x03},//  E_MSGID_ENTER_FAILSAFE_MODE,41
    #endif
    {0x64},//  E_MSGID_READ_AVM_HW_IN,42
    {0x65},//  E_MSGID_READ_USB_INTERFACE_STATUS,43
    {0x57},//  E_MSGID_READ_SDCARD_INTERFACE_STATUS,47
   // {0x3A},//  E_MSGID_SET_VEHICLE_CONFIG,44
    {0x3B},//  E_MSGID_GET_VEHICLE_CONFIG,45
	{0x56},//  E_MSGID_CTL_AVM_SHUT_DOWN_TIME,46
	//{0x57},//  E_MSGID_READ_SDCARD_INTERFACE_STATUS,47
	{0x85},//  E_MSGID_CTL_DTCSETTING_OFF,50
	{0x86},//  E_MSGID_CTL_AVM_LED,51
	{0x88},//  E_MSGID_CTL_ACCONSETTING_ON,52
	{0x03},//  E_MSGID_REQ_J6_ENTER_SELF_DIAG,53
};

U8 GetEOLMessageIDValue(U8 MessageID)
{
    return EolMessageTable[MessageID].MsgIDVal;
}

U8 GetEOLMessageID(U8 val)
{
    U8 i = E_MSGID_INVALID;
    for(i = 0; i<E_MSGID_NUM;i++)
    {
        if(val == EolMessageTable[i].MsgIDVal)
        {
            return i;
        }
    }
    return (E_MSGID_INVALID);
}

#endif
/**************** END OF FILE *****************************************/


/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD NJ   									   *
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
* Version       Date         Name               Changes and comments
* ----------------------------------------------------------------------
* 0.1    July 25 ,2016      ShangQiuju       Init version
*=====================================================================*/
#ifndef _SOC_DRIVER_IF_H_
#define _SOC_DRIVER_IF_H_

#include "SocDriver.h"
/**** Definition of constants ****/

//definitions related to spi packet, and spi status and controls
//acknowlege command for flow control and link management (in 8byte packet format, not application command format)
#define ACK_FRAMEID_BYTE 0
#define ACK_STATUS_BYTE 1
#define ACK_REQUEST_BYTE 2
#define ACK_DEBUG_INFO_BYTE1 3
#define ACK_DEBUG_INFO_BYTE2 4
#define ACK_DEBUG_INFO_BYTE3 5
#define ACK_DEBUG_INFO_BYTE4 6
#define ACK_CS_BYTE 7

#define COMMAND_OK 0x00
#define SPI_SLAVE_READY 0x00
#define COMMAND_ERROR 0xff
#define REQEUST_RESEND 0x10
#define REQUEST_SLOW_CLK 0x11

#define SPI_OVE_MAX 0x03
#define SPI_CSERROR_MAX 0x03
#define SPI_RESET_MAX 0x03

#define RADIO_DEBUG_FIELD_LENGTH 10 //max 10bytes

/**** Definition of types ****/
#define SPI_NAVI_FRAME_SIZE 150

typedef struct
{
    BOOL bValid; /** if valid data? **/
    U8 length;
    U8  buff[SPI_NAVI_FRAME_SIZE];
} SPI_NAVI_FRAME_TYPE;
/**** Definition of macros ****/

/**** Declaration of constants ****/


/**** Declaration of variables ****/


/**** Declaration of functions ****/
extern void SocDriver_Init(void);
extern void SocDriver_DeInit(void);
extern void SocDriver_powercontrol(E_DEV_POWER type);
extern void SocDriver_Cyclic_Entry(void);
extern U8 SocDriver_Open(void);
extern U8 SocDriver_Close(void);
extern U8 SocDriver_Write( U8* buffer, U16 Len);
extern U16 SocDriver_Read( U8* buffer, U16 Len);
extern BOOL SocDriver_GetpowerStatus(E_DEV_POWERS type);
extern BOOL socDriver_is_tx_idle(void);

#endif /*_NAVIDRIVER_IF_H_*/
/****************************** END OF FILE ***************************/

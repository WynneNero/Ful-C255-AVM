/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   : 										   *
************************************************************************
* Object        : DRIVER_IF.H
* Module        :
* Instance      :
* Description   :
*-----------------------------------------------------------------------
* Version:  0.1
* Date: 2011-12-20
* Author: Shao Guangxian
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
*
*=====================================================================*/
#ifndef _EOL_UART_DRIVER_IF_H_
#define _EOL_UART_DRIVER_IF_H_

/**** Definition of constants ****/


#include "CONFIG.H"
#ifdef EOL_OPTION
#include "TYPES.H"

/**** Definition of types ****/

/**** Definition of macros ****/

#define MAX_EOL_BUFF 205
#define EOL_REQ_ACK 		0x00
#define EOL_REQ_NOACK 	0x01
#define EOL_REP_ACK 		0x02
#define EOL_REP_NOACK 	0x03

/**** Declaration of constants ****/


/**** Declaration of variables ****/


/**** Declaration of functions ****/
extern void Eol_AckReceive(void);
extern void Eol_NAckReceive(void);

#define EolDriverDataSentOk()   Eol_AckReceive()
#define EolDriverDataSentFail()   Eol_NAckReceive()

/***********end extern micro/type define ****************/
extern void EolUartDriver_10ms_Entry(void);
extern void EolUartDriver_SentIsr(void);
extern void EolUartDriver_ReceiveIsr(U8 data);
extern void EolUartDriver_Init(void);
extern U8 EolUartDriver_Open(void);
extern U16 EolUartDriver_Read( U8* buffer, U16 Len);
extern U8 EolUartDriver_Write( U8* buffer, U16 Len);
extern U8 EolUartDriver_Close(void);
extern U8 EolUartDriver_GetDriverStatus(void);
#endif
#endif /*_EOL_UART_DRIVER_IF_H_*/
/****************************** END OF FILE ***************************/

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
#ifndef _EOL_UART_DRIVER_H_
#define _EOL_UART_DRIVER_H_ 

#include "CONFIG.H"

#ifdef EOL_OPTION
#include "TYPES.H"
#include "EOLUartDriver_IF.H"
/**** Definition of constants ****/
//Frame define
#define EOL_FRAME_CKS    1

//Protocol define
#define SEND_TIMEROUT 2
#define RETRY_COUNT 2

#define EOL_RECVQ_SIZE 3

/**** Definition of macros ****/

typedef struct 
{
    BOOL bIsParsed;
    U8 rc;
    U8 length;
    U8 cks;
    U8  buf[MAX_EOL_BUFF];   
} EOL_FRAME_TYPE;

typedef enum
{
	E_EOLDRIVER_IDLE,
	E_EOLDRIVER_NORMAL,
	E_EOLDRIVER_SENDFRAME,
	E_EOLDRIVER_SENDACK,
}E_EOLDRIVER_STATE;

typedef enum
{
	E_EOLDRIVER_NOREQ=0x00,
	E_EOLDRIVER_REQSTART=0x01,
	E_EOLDRIVER_REQSTOP=0x02,
	E_EOLDRIVER_REQRESET=0x04,
	E_EOLDRIVER_REQSENDFRAME=0x08,
}E_EOLDRIVER_REQUEST;


/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/
void EolUartDriver_Init(void);
void EolUartDriver_DeInit(void);
U8 EolUartDriver_Open(void);
U8 EolUartDriver_Close(void);
U8 EolUartDriver_Control(U8 type, void* buffer);
U8 EolUartDriver_Write( U8* buffer, U16 Len);
U16 EolUartDriver_Read( U8* buffer, U16 Len);
void EolUartDriver_10ms_Entry(void);
void EolUartDriver_SentIsr(void);
#endif
#endif /*_EOL_UART_DRIVER_H_*/

/****************************** END OF FILE ***************************/


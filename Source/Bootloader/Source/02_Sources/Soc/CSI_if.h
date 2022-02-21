/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                                 *
*   AUTHOR     :                                                       *
************************************************************************
* Object        :
* Module        :	CSI
* Instance      :
* Description   :	Header file
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
*     0.1	  2016-6-23			Init, multiple Chip select is not supported
							FIFO mode is not supported.
*=====================================================================*/

#ifndef   _CSI_IF_H
#define   _CSI_IF_H
#include "define.h"
typedef  void( * CSI_SENT_CALLBACK )( void );
typedef void(  * CSI_RECEV_CALLBACK )( void);
typedef void(  * CSI_RECEV_BYTE_CALLBACK )( U8* recData);
typedef void(  * CSI_ERROR_CALLBACK )( U8 Type);

typedef enum
{
     CSIH_0=0,                     
     CSIH_1,                     
     CSIH_2,                     
     CSIH_3,
     CSIG_0,
     CSI_MAX
}CSI_TYPE;            

typedef enum
{
	SPI_BAUD100K=100000,		//100K
	SPI_BAUD500K=500000,		//500K
	SPI_BAUD1M=1000000,		// 1M
	SPI_BAUD5M=5000000,		// 5M
}SPI_BAUD_OPTION;


#define NO_CSS	0		// no CSS or SSI

extern void CSI_Start(CSI_TYPE csi, U8 datalen);
extern void CSI_Stop(CSI_TYPE csi);
extern void CSI_Init( CSI_TYPE csi, SPI_BAUD_OPTION baudrate,BOOL bIsMaster,U16 CsSsiChannel,BOOL bOpenRY);
extern void CSI_InitFIFO( CSI_TYPE csi, SPI_BAUD_OPTION baudrate,BOOL bIsMaster,U16 CsSsiChannel,BOOL bOpenRY);
extern void CSI_StartFifo(CSI_TYPE csi, U8 datalen,BOOL bIsMaster);
extern BOOL CSI_Send( CSI_TYPE csi,U8 *txbuf, U16 length, U8 *rxbuf );
extern BOOL CSI_FIFO_Send( CSI_TYPE csi,U8 *txbuf, U16 length);
extern void CSIG0_Tx_handler(void);
extern void CSIG0_Rx_handler(void);
extern void CSIG0_Error_handler(void);
extern void CSIH0_Tx_handler(void);
extern void CSIH0_Rx_handler(void);
extern void CSIH0_Error_handler(void);
extern void CSIH1_Tx_handler(void);
extern void CSIH1_Rx_handler(void);
extern void CSIH1_Error_handler(void);
extern void CSIH2_Tx_handler(void);
extern void CSIH2_Rx_handler(void);
extern void CSIH2_Error_handler(void);
extern void CSIH3_Tx_handler(void);
extern void CSIH3_Rx_handler(void);
extern void CSIH3_Error_handler(void);
extern BOOL CSI_send_over( CSI_TYPE csi);
#endif /*_CSI_H*/

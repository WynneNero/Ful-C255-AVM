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
* Version       Date        Name                    Changes and comments
*     0.1	  2016-6-23	RenWeiMin		Init, multiple Chip select is not supported
							              FIFO mode is not supported.
*-----------------------------------------------------------------------
*     0.2     2016-11-21 ShangQiuju            Remove unused interface   
*-----------------------------------------------------------------------
*     0.3     2017-1-24 ShangQiuju              Fix Coverity warnings.   
*----------------------------------------------------------------------
*     0.4     2017-4-1   PEI Jingli                Fix include files.
*=====================================================================*/

#ifndef   _CSI_IF_H
#define   _CSI_IF_H
#include "Define.h"

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
	SPI_BAUD100K=100000u,		/*100K*/
	SPI_BAUD500K=500000u,		/*500K*/
	SPI_BAUD1M=1000000u,		/*1M*/
	SPI_BAUD5M=5000000u,		/* 5M*/
}SPI_BAUD_OPTION;

/*interface about csi normal communication*/
extern void CSI_Start(CSI_TYPE csi, U8 datalen);
extern void CSI_Stop(CSI_TYPE csi);
extern void CSI_Init( CSI_TYPE csi, SPI_BAUD_OPTION baudrate,BOOL bIsMaster,BOOL isUsedCsi,BOOL bOpenRY);
extern ERR_TYPE CSI_Send( CSI_TYPE csi,U8 *txbuf, U16 length );

/*interface about csi dual buffer communication*/
extern void CSI_InitDualBuffer( CSI_TYPE csi, SPI_BAUD_OPTION baudrate,BOOL bIsMaster,BOOL isUsedCsi,BOOL bOpenRY);
extern void CSI_StartDualBuffer(CSI_TYPE csi, U8 datalen,BOOL bIsMaster,U8 needFixDataLen);
extern void CSI_InitFIFO( CSI_TYPE csi, SPI_BAUD_OPTION baudrate,BOOL bIsMaster,BOOL isUsedCsi,BOOL bOpenRY);
extern void CSI_StartFifo(CSI_TYPE csi, U8 datalen,BOOL bIsMaster,U8 needFixDataLen);
extern void CSI_StopFIFO(CSI_TYPE csi);
extern void CSI_DisableTxInterrupt(CSI_TYPE csi );
extern void CSI_EnableTxInterrupt(CSI_TYPE csi );
extern ERR_TYPE CSI_DualBuffer_Send( CSI_TYPE csi,U8 *txbuf, U16 length);
extern ERR_TYPE CSI_FIFO_Send( CSI_TYPE csi,U8 *txbuf, U16 length);
extern ERR_TYPE CSI_DualBuffer_SendEmpty(CSI_TYPE csi,U16 length);
extern ERR_TYPE CSI_FIFO_SendEmpty(CSI_TYPE csi,U16 length);
extern void CSI_SetFifoPointer( CSI_TYPE csi);
#endif /*_CSI_IF_H*/

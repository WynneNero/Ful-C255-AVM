/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									   *
************************************************************************
* Object        :
* Module        :	CSI
* Instance      :
* Description   :	Configure callbacks when a interrupt occur.
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date        Name               Changes and comments
*    0.1	  2016-6-23	RenWeimin		Init version
*-----------------------------------------------------------------------
*    0.2      2016-11-21 ShangQiuju            change callback definition.
*-----------------------------------------------------------------------
*    0.3      2016-11-21   ShangQiuju          Add config according using hw.
*-----------------------------------------------------------------------
*    0.4      2016-11-22   ShangQiuju          Add soc callback for test.
*-----------------------------------------------------------------------
*    0.5      2017-01-24    ZhangJie              Fix Coverity warning.
*-----------------------------------------------------------------------
*    0.6      2017-02-09    ShangQiuju          Add err callback function.
*-----------------------------------------------------------------------
*    0.7       2017-02-16   ShangQiuju         Update data and clock phase config.
*=====================================================================*/
#include "CSI_Cfg.h"

extern void SocDriver_ReceiveIsr(void* indata);
extern void SocDriver_SentIsr(void);
extern void SocDriver_ErrorIsr(U8 errtype);

/* config for CSIHnCFGx
x:CSIHn has up to 8 chip select signals. The individual chip select signals are identified by the index "x".
when channel is set slave mode ,only x=0 need to be set. 1...7 must to be set 0.
CSIHnCFG0 need to set follwing bit:
    -CSIGnPSx[1:0]:parity setting  
        -No parity   CSIG_CFG0_PS_NO_PARITY
        -0 parity       CSIG_CFG0_PS_0_PARITY
        -odd parity    CSIG_CFG0_PS_ODD_PARITY
        -even parity  CSIG_CFG0_PS_EVEN_PARITY
    -CSIHnDLSx[3:0]:data length 
        -16bit CSIG_CFG0_DLS_DATA_LENGTH_16
        -1bit   CSIG_CFG0_DLS_DATA_LENGTH_1
        ...
        -8bit   CSIG_CFG0_DLS_DATA_LENGTH_8
        ...
        -15bit CSIG_CFG0_DLS_DATA_LENGTH_15
    -CSIHnDIRx:data direction
        -MSB  CSIG_CFG0_DIR_MSB_FIRST
        -LSB   CSIG_CFG0_DIR_LSB_FIRST
  ***ATTENTION:CSIHnDAP is not needed set here, it will be configuration in code accoding Csi_ClockDataPhaseCfgData****
*/
const U32 Csi_CfgData[CSI_MAX][8]={
{(CSIG_CFG0_PS_NO_PARITY | CSIG_CFG0_DIR_MSB_FIRST  | CSIG_CFG0_DLS_DATA_LENGTH_8),0,0,0,0,0,0,0},/*CSIH_0*/
{0,0,0,0,0,0,0,0},/*CSIH_1*/
{0,0,0,0,0,0,0,0},/*CSIH_2*/
{0,0,0,0,0,0,0,0},/*CSIH_3*/
{0,0,0,0,0,0,0,0},/*CSIG_0*/
};

/*Config of clcok and data phase: 
channel CSIHn only need to config CSIHnCFGx,
x:CSIHn has up to 8 chip select signals. The individual chip select signals are identified by the index "x".
when channel is set slave mode ,only x=0 need to be set. 1...7 must to be set 0.
channel CSIGn need to config CSIGnCFGx and CSIHnCTL1.
*/
const E_CLOCK_DATA_PHASE_TYPE Csi_ClockDataPhaseCfgData[CSI_MAX][8]={
{E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0},/*CSIH_0*/
{E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0},/*CSIH_1*/
{E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0},/*CSIH_2*/
{E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0},/*CSIH_3*/
{E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0,E_SPI_MODE_0},/*CSIG_0*/
};

const Func_Void_Proc csi_tx_callback[CSI_MAX]=
{
SocDriver_SentIsr,
NULL,
NULL,
NULL,
NULL
};
/* callback on receive every byte*/
const Func_ParamP_Proc csi_rx_byte_callback[CSI_MAX]=
{
SocDriver_ReceiveIsr,
NULL,
NULL,
NULL,
NULL
};


const Func_Param8_Proc csi_error_callback[CSI_MAX]=
{
SocDriver_ErrorIsr,
NULL,
NULL,
NULL,
NULL
};


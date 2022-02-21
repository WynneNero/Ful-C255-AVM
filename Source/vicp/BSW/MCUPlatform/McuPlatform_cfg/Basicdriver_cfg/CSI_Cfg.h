/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									   *
************************************************************************
* Object        : 
* Module        : 	CSI
* Instance      : 
* Description   : 	
*-----------------------------------------------------------------------
* Version: 
* Date: 
* Author: 
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
*    0.1	  2016-6-23	RenWeimin		Init version
*-----------------------------------------------------------------------
*    0.2      2016-11-21 ShangQiuju            remove unused struct.
*-----------------------------------------------------------------------
*    0.3      2017-02-16  ShangQiuju           Update data and clock phase config.
*------------------------------------------------------------------------
*   0.4      2017-04-01   PEI Jingli  Fix headfile included.
*=====================================================================*/
#ifndef _CSI_CFG_H_
#define _CSI_CFG_H_ 

#include "CSI.h"
#include "csi_if.h"

/**** Declaration of functions ****/
extern const U32 Csi_CfgData[CSI_MAX][8];
extern const E_CLOCK_DATA_PHASE_TYPE Csi_ClockDataPhaseCfgData[CSI_MAX][8];
extern const Func_Void_Proc csi_tx_callback[CSI_MAX];
extern const Func_ParamP_Proc csi_rx_byte_callback[CSI_MAX];
extern const Func_Param8_Proc csi_error_callback[CSI_MAX];

#endif /*_CSI_CFG_H_*/

/****************************** END OF FILE ***************************/


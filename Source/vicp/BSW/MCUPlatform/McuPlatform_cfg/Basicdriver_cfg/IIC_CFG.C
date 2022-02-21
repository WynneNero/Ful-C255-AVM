/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                                 *
*   AUTHOR     :                                                       *
************************************************************************
* Object        :
* Module        :	IIC
* Instance      :
* Description   :	Configure callbacks when a interrupt occur.
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
*-----------------------------------------------------------------------
* 0.1	   Jan 20,2016   Init version.
* ----------------------------------------------------------------------
* 0.2	   Jan 05,2017    ZhangJie     Delete test code for IIC_TEST
*-----------------------------------------------------------------------
* 0.3          Jan 24,2017   ZhangJie   Fix Coverity warnings.
*----------------------------------------------------------------------
* 1.1     Apr 04,2017    PEI Jingli     Fix include files.
*=====================================================================*/
#include "Define.h"
#include "IIC_CFG.h"
#include "ICS_Driver.h"

/*callback when transmit data is empty, at 9th clk rising edge*/
const Func_Void_Proc mcu_i2c_tx_byte_callback = {NULL};
/*callback when byte received*/
const Func_Void_Proc mcu_i2c_rx_byte_callback = {NULL};

#ifdef IIC_TEST
// callback when stop deteced
const IIC_ERROR_CALLBACK mcu_i2c_stop_callback = {ICSDriver_session_finish};
#else
const IIC_ERROR_CALLBACK mcu_i2c_stop_callback = {NULL};
#endif

#ifdef IIC_TEST
// callback for slave when register address is received
const Func_Param8_Proc i2c_slave_prepareData_callback={ICSDriver_checkRegPosition};
#else
const Func_Param8_Proc i2c_slave_prepareData_callback={NULL};
#endif

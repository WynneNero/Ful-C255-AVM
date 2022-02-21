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
* 0.2	   Jan 05,2017    ZhangJie     Move mocre from Code_cfg.h to this file
*------------------------------------------------------------------------
* 0.3          Jan 24,2017  ZhangJie  Fix Coverity warnings.
*------------------------------------------------------------------------
* 0.4          Apr 04,2017  PEI Jingli  Fix headfile included and add callback  defination.
*=====================================================================*/
#ifndef _I2C_CFG_H_
#define _I2C_CFG_H_

/*callback function*/
typedef void(  * IIC_ERROR_CALLBACK )( U8 role,U8 RW_direction, U8 DataCount);

/***** don't enable below MACRO for application not following ICS protocol*****/
/*#define IIC_MASTER_READ_RESTART	master read(single byte/multiple bytes) following ICS protocol
									if enabled, master read sequence as below:
									Dev Adr(W) + Reg Adr + Restart + Dev Adr(R) + Data...
									if disabled, master read sequence as below:
									Dev Adr(W) + Reg Adr + Stop + Start + Dev Adr(R) + Data...*/
/********************************* end*****************************/

/* config how many bytes should be received before callback*/
/* for ICS driver, one byte is used as reg address*/
#define I2C_CB_NUMBER	((U8)1u)
#define I2C_RETRY_COUNT ((U8)2u)

#define IIC_MASTER_ICS_READ_LEN	11u	/* master read byte length, for test*/
									/*11	 master read more than slave can provide, fill 0x5A*/

extern const Func_Void_Proc mcu_i2c_tx_byte_callback;
extern const Func_Void_Proc mcu_i2c_rx_byte_callback;
extern const Func_Param8_Proc i2c_slave_prepareData_callback;
extern const IIC_ERROR_CALLBACK mcu_i2c_stop_callback ;

#endif /*_I2C_H_*/
/****************************** END OF FILE ***************************/

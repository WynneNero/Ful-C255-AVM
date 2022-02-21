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
* 
*=====================================================================*/
#ifndef _CSI_CFG_H_
#define _CSI_CFG_H_ 
#include "CSI_IF.H" 

// config for CSS
#define CSI_CFG0_OPTION_CFG 	(CSIG_CFG0_PS_NO_PARITY | CSIG_CFG0_DIR_MSB_FIRST |CSIG_CFG0_DAP_RISING | CSIG_CFG0_DLS_DATA_LENGTH_8)
#define CSI_CFG1_OPTION_CFG 	0
#define CSI_CFG2_OPTION_CFG 	0
#define CSI_CFG3_OPTION_CFG 	0
#define CSI_CFG4_OPTION_CFG 	0
#define CSI_CFG5_OPTION_CFG 	0
#define CSI_CFG6_OPTION_CFG 	0
#define CSI_CFG7_OPTION_CFG 	0

// list port mapping and CS options

// SO for CSIG0
#define CSIG0SO_MAP_P0_13 0x0001
#define CSIG0SO_MAP_P10_6 0x0002
// SI for CSIG0
#define CSIG0SI_MAP_P0_12 0x0004
#define CSIG0SI_MAP_P10_8 0x0008
// SC for CSIG0
#define CSIG0SC_MAP_P0_14 0x0010
#define CSIG0SC_MAP_P10_7 0x0020


// CSSx for CSIH0
#define CSIH0CSS0_MAP_P8_2 0X0001		// CSS0 map to P8_2
#define CSIH0CSS0_MAP_P8_0 0X0002

#define CSIH0CSS1_MAP_P10_10 0x0004
#define CSIH0CSS1_MAP_P8_3 0x0008
#define CSIH0CSS2	0x0010		//CS2 enabled
#define CSIH0CSS3	0x0020		
#define CSIH0CSS4	0x0040		
#define CSIH0CSS5	0x0080		
#define CSIH0CSS6	0x0100		
#define CSIH0CSS7	0x0200		

// SSI for CSIH0
#define CSIH0SSI_MAP_P0_0	0x0400
#define CSIH0SSI_MAP_P10_13	0x0800

// SO for CSIH1
#define CSIH1SO_MAP_P0_5 0x0001
#define CSIH1SO_MAP_P10_2 0x0002
// SI for CSIH1
#define CSIH1SI_MAP_P0_4 0x0004
#define CSIH1SI_MAP_P10_0 0x0008
// SC for CSIH1
#define CSIH1SC_MAP_P0_6 0x0010
#define CSIH1SC_MAP_P10_1 0x0020
// SSI for CSIH1
#define CSIH1SSI_MAP_P0_8 0x0040
#define CSIH1SSI_MAP_P10_3 0x0080

// CSSx for CSIH1
#define CSIH1CSS0_MAP_P0_9 0x0100
#define CSIH1CSS0_MAP_P10_11 0x0200

#define CSIH1CSS1_MAP_P0_10 0x0400
#define CSIH1CSS1_MAP_P10_12 0x0800

#define CSIH1CSS2	 0x1000

#define CSIH1CSS3	 0x2000

#define CSIH1CSS4 0x4000
#define CSIH1CSS5 0x8000

// CSS for CSIH2
#define CSIH2CSS0 0x0001	
#define CSIH2CSS1 0x0002
#define CSIH2CSS2 0x0004
#define CSIH2CSS3 0x0008

// CSSx for CSIH3
#define CSIH3CSS0 0x0001
#define CSIH3CSS1 0x0002
#define CSIH3CSS2 0x0004
#define CSIH3CSS3 0x0008


/**** Declaration of functions ****/
extern const CSI_SENT_CALLBACK csi_tx_callback[CSI_MAX];
extern const CSI_RECEV_CALLBACK csi_rx_callback[CSI_MAX];
extern const CSI_RECEV_BYTE_CALLBACK csi_rx_byte_callback[CSI_MAX];
extern const CSI_ERROR_CALLBACK csi_error_callback[CSI_MAX];

#endif /*_CSI_CFG_H_*/

/****************************** END OF FILE ***************************/


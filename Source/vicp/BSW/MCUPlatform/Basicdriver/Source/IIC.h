/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                                 *
*   AUTHOR     :                                                       *
************************************************************************
* Object        :
* Module        :	IIC
* Instance      :
* Description   :	IIC module header file. 				
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
*------------------------------------------------------------------------
* 0.1	   Jun 26,2016                              Initial version
*------------------------------------------------------------------------
* 0.2	   Jan 11,2017      ZhangJie           Add parentheses and add u for constant value to avoid Coverity warning.
*-----------------------------------------------------------------------
* 0.3          Jan 24,2017   ZhangJie   Remove unused include file.
*-----------------------------------------------------------------------
* 0.4         Apr 1,2017     PEI Jingli   Fix include files.
*=====================================================================*/

/*============================================================================
 Includes
============================================================================*/
#ifndef   _IIC_H
#define   _IIC_H
	
/**** Definition of macros ****/

#define I2C_ABNORMAL_RESPONSE 	0xFFu

/* Enables/disables operation of the IICBn (IICBnIICE) */
#define IICB_CTL0_IICE_DISABLE_IIC                    (0xFFFFFF7FUL) /* Disables operation of IICBn */
#define IICB_CTL0_IICE_ENABLE_IIC                     (0x00000080UL) /* Enables operation of IICBn */

#define  IIC_REG_BASEADD                   ( (CPU_INT32U )0xFFCA0000u)

/*Port function address*/
#define  IIC_REG_IICBnDRT                  (*(CPU_REG08 *)((IIC_REG_BASEADD) + 0x003Cu))		/*transmit data register*/
#define  IIC_REG_IICBnDRR                  (*(CPU_REG08 *)((IIC_REG_BASEADD) + 0x0040u))	/* receive data register*/
#define  IIC_REG_IICBnSAR0                  (*(CPU_REG08 *)((IIC_REG_BASEADD) + 0x0028u))		/* slave address 0*/
#define  IIC_REG_IICBnSAR1                  (*(CPU_REG08 *)((IIC_REG_BASEADD) + 0x002Cu))		/* slave address 1*/
#define  IIC_REG_IICBnSAR2                  (*(CPU_REG08 *)((IIC_REG_BASEADD) + 0x0030u))		/* slave address 2*/

#define  IIC_REG_IICBnCTL0                 (*(CPU_REG32 *)((IIC_REG_BASEADD) + 0x0000u))
#define  IIC_REG_IICBnCTL1                 (*(CPU_REG32 *)((IIC_REG_BASEADD) + 0x0004u))

#define  IIC_REG_IICBnWL                    (*(CPU_REG16 *)((IIC_REG_BASEADD) + 0x0034u))		/*baud rate low*/
#define  IIC_REG_IICBnWH                    (*(CPU_REG16 *)((IIC_REG_BASEADD) + 0x0038u))

#define  IIC_REG_IICBnTRG                    (*(CPU_REG08 *)((IIC_REG_BASEADD) + 0x000Cu))
#define  IIC_REG_IICBnSTR0                    (*(CPU_REG16 *)((IIC_REG_BASEADD) + 0x0010u))
#define  IIC_REG_IICBnSTR1                    (*(CPU_REG08 *)((IIC_REG_BASEADD) + 0x0014u))
#define  IIC_REG_IICBnSTRC                    (*(CPU_REG08 *)((IIC_REG_BASEADD) + 0x0018u))

/* IIC state*/
#define IDLE_STATE               ( 0x00U )	
#define ADDR_W_STATE             ( 0x10U )	/*to send dev adr+W*/
#define ADDR_R_STATE             ( 0x11U )	/* to send dev adr+R*/

#define DATA_SEND_STATE          ( 0x20U )
#define DATA_SEND_STATE_2        ( 0x21U )
#define DATA_SEND_END_STATE      ( 0x22U )

#define DATA_RECV_STATE          ( 0x30U )
#define DATA_RECV_STATE_2        ( 0x31U )

#define DATA_RECV_STATE_3        ( 0x32U )
#define DATA_RECV_STATE_4        ( 0x33U )		/* data to receive > 2 bytes*/

#define DATA_RECV_END_STATE      ( 0x40U )
#define DATA_RECV_END_STATE_2    ( 0x41U )

#define IIC_DIR_W                ( 0x00U )
#define IIC_DIR_R                ( 0x01U )

typedef enum
{
	IIC_TX=0,		/* send data*/
	IIC_RX			/* receive*/
}IIC_DIR;

typedef struct tst_iic_param {
    U8    iic_state;			/*used to control tx/rx*/
    IIC_ROLEOPTION role;
    U16    slave_adr;		/*slave address*/
    U8    tx_count;		/*actual length sent*/
    U8    tx_len;		/*total length to send*/
    U8    *tx_data_p;	/*pointer to data to send*/
    U8    rx_count;		/*actual length received*/
    U8    rx_len;		/* total length to receive*/
    U8    *rx_data_p;
    U8   reg_adr;		/*register address*/
    IIC_DIR   RW_direction;	/* 1- read, 0- write*/
} IIC_PARAM;

typedef struct 
{
	U8 CKS;
	U8 BRH;
	U8 BRL;
}IIC_BAUDCONFIG;


#endif /*_IIC_H*/


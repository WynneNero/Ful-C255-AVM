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

#ifndef   _CSI_H
#define   _CSI_H
//#include "GPIO.h"
#include "define.h"

typedef struct
{
U8* CsiTxAddress;         /* CSIG0 send buffer address */
U8* CsiRxAddress;         /* CSIG0 rev buffer address */
U16    CsiTxCnt;              /* CSIG0 send data count */
U16   CsiTxEDLCnt;           /* CSIG0 EDL send data count */
} CSI_FRAME_TYPE;

/*
    CSIG control register 0 (CSIGnCTL0)
*/
/* Controls operation clock (CSIGnPWR) */
#define CSIG_CTL0_PWR_STOP_OPERATION_CLOCK             (0x00U)   /* Stop operation clock */
#define CSIG_CTL0_PWR_PROVIDE_OPERATION_CLOCK          (0x80U)   /* Provide operation clock */

/* Enables/disables transmission (CSIGnTXE) */
#define CSIG_CTL0_TXE_TRANSMISSION_DISABLE             (0x00U)   /* Transmission disabled */
#define CSIG_CTL0_TXE_TRANSMISSION_ENABLE              (0x40U)   /* Transmission enabled */

/* Enables/disables reception (CSIGnRXE) */
#define CSIG_CTL0_RXE_TRANSMISSION_DISABLE             (0x00U)   /* Receive disabled */
#define CSIG_CTL0_RXE_TRANSMISSION_ENABLE              (0x20U)   /* Receive enabled */

/* bit 0 */
#define CSIG_CTL0_B0_MEMORY_MODE			    (0x00U)
#define CSIG_CTL0_B0_SET_TO_1                          (0x01U)   // direct access mode, 

/*
    CSIG control register 1 (CSIGnCTL1)
*/
/* Selects the initial level of the data clock CSIGTSCK (CSIGnCKR) */
#define CSIG_CTL1_CKR_CLOCK_LEVEL_HIGH           (0x00000000UL)  /* Initial level of CSIGTSCK is high */
#define CSIG_CTL1_CKR_CLOCK_LEVEL_LOW            (0x00020000UL)  /* Initial level of CSIGTSCK is low */

/* Selects the timing of interrupt CSIGTIC (CSIGnSLIT) */
#define CSIG_CTL1_SIT_NORMAL_INTERRUPT           (0x00000000UL)  /* Normal interrupt timing (interrupt is generated after the transfer) */
#define CSIG_CTL1_SIT_CSIGnTX0_FREE_INTERRUPT    (0x00010000UL)  /* Interrupt generation when CSIGnTX0 is free for next data */

/* Enables/disables extended data length (EDL) mode (CSIGnEDLE) */
#define CSIG_CTL1_EDLE_EXTENDED_DISABLE          (0x00000000UL)  /* Extended data length mode disabled */
#define CSIG_CTL1_EDLE_EXTENDED_ENABLE           (0x00000080UL)  /* Extended data length mode enabled */

/* Enables/disables data consistency check (CSIGnDCS) */
#define CSIG_CTL1_DCS_CONSISTENCY_DISABLE        (0x00000000UL)  /* Data consistency check disabled */
#define CSIG_CTL1_DCS_CONSISTENCY_ENABLE         (0x00000020UL)  /* Data consistency check enabled */

/* Controls loop-back mode (LBM) (CSIGnLBM) */
#define CSIG_CTL1_LBM_LOOPBACK_DISABLE           (0x00000000UL)  /* Loop-back mode deactivated */
#define CSIG_CTL1_LBM_LOOPBACK_ENABLE            (0x00000008UL)  /* Loop-back mode activated */

/* Selects interrupt delay mode (CSIGnSIT) */
#define CSIG_CTL1_LIT_NO_DELAY                   (0x00000000UL)  /* No delay */
#define CSIG_CTL1_LIT_HALF_CLOCK_DELAY           (0x00000004UL)  /* Half clock delay for all interrupts */

/* Enables/disables handshake mode (CSIGnHSE) */
#define CSIG_CTL1_HSE_HANDSHAKE_DISABLE          (0x00000000UL)  /* Handshake function disabled */
#define CSIG_CTL1_HSE_HANDSHAKE_ENABLE           (0x00000002UL)  /* Handshake function enabled */

/* Chip select signal after last data transfer */
#define CSIH_CTL1_CS_RETURN_INACTIVE_DISABLE          (0x00000000UL)  /* CS hold active level */
#define CSIH_CTL1_CS_RETURN_INACTIVE_ENABLE            (0x00000010UL)  /*  CS return to inactive level */

/* Enables/disables slave select function (CSIGnSSE) */
#define CSIG_CTL1_SSE_CSIGTSSI_IGNORED           (0x00000000UL)  /* Input signal CSIGTSSI is ignored */
#define CSIG_CTL1_SSE_CSIGTSSI_ENABLE            (0x00000001UL)  /* Input signal CSIGTSSI is enabled */

/*
    CSIG control register 2 (CSIGnCTL2)
*/
/* Selects the value m of the prescaler (CSIGnPRS) */
#define CSIG_CTL2_PRS_PRESCALER_0                    (0x0000U)   /* PCLK (master mode) */
#define CSIG_CTL2_PRS_PRESCALER_1                    (0x2000U)   /* PCLK / 2 (master mode) */
#define CSIG_CTL2_PRS_PRESCALER_2                    (0x4000U)   /* PCLK / 4 (master mode) */
#define CSIG_CTL2_PRS_PRESCALER_3                    (0x6000U)   /* PCLK / 8 (master mode) */
#define CSIG_CTL2_PRS_PRESCALER_4                    (0x8000U)   /* PCLK / 16 (master mode) */
#define CSIG_CTL2_PRS_PRESCALER_5                    (0xA000U)   /* PCLK / 32 (master mode) */
#define CSIG_CTL2_PRS_PRESCALER_6                    (0xC000U)   /* PCLK / 64 (master mode) */
#define CSIG_CTL2_PRS_CLOCK_EXTERNAL                 (0xE000U)   /* External clock via CSIGTSCI (slave mode) */

/* Selects the baud rate (CSIGnBRS) */
#define CSIG_CTL2_BRS_BAUDRATE_STOP                  (0x0000U)   /* BRG is stopped */

/*
    CSIG status register 0 (CSIGnSTR0)
*/
/* Transfer status flag (CSIGnTSF) */
#define CSIG_STR0_TSF_TRANSMISSION               (0x00000080UL)  /* Transmission is in progress or being prepared */

/* Data consistency check error flag (CSIGnDCE) */
#define CSIG_STR0_DCE_DATA_CONSISTENCY_ERROR     (0x00000008UL)  /* Data consistency error detected */

/* Parity error flag (CSIGnPE) */
#define CSIG_STR0_PE_PARITY_ERROR                (0x00000002UL)  /* Parity error detected */

/* Overrun error flag (CSIGnOVE) */
#define CSIG_STR0_OVE_OVERRUN_ERROR              (0x00000001UL)  /* Overrun error detected */

/*
    CSIG status clear register 0 (CSIGnSTCR0)
*/
#define CSIG_STCR0_PCT					(0x0100U)  	// clear FIFO pointer
#define CSIG_STCR0_DCEC                              (0x0008U)   /* Clear data consistency error flag (CSIGnSTR0.CSIGnDCE) */
#define CSIG_STCR0_PEC                               (0x0002U)   /* Clear parity error flag (CSIGnSTR0.CSIGnPE) */
#define CSIG_STCR0_OVEC                              (0x0001U)   /* Clear overrun error flag (CSIGnSTR0.CSIGnOVE) */

/*
    CSIG Rx-only mode control register 0 (CSIGnBCTL0)
*/
/* Disables/enables next data reception start by reading CSIGnRX0 (CSIGnSCE) */
#define CSIG_BCTL0_SCE_NEXT_RECEPTION_DISABLE          (0x00U)   /* Next reception disabled */
#define CSIG_BCTL0_SCE_NEXT_RECEPTION_ENABLE           (0x01U)   /* Next reception enabled */

/*
    CSIG configuration register 0 (CSIGnCFG0)
*/
/* Specifies parity (CSIGnPS) */
#define CSIG_CFG0_PS_NO_PARITY                   (0x00000000UL)  /* No parity */
#define CSIG_CFG0_PS_0_PARITY                    (0x10000000UL)  /* 0 parity */
#define CSIG_CFG0_PS_ODD_PARITY                  (0x20000000UL)  /* odd parity */
#define CSIG_CFG0_PS_EVEN_PARITY                 (0x30000000UL)  /* even parity */

/* Specifies data length (CSIGnDLS) */
#define CSIG_CFG0_DLS_DATA_LENGTH_16             (0x00000000UL)  /* Data length is 16 bits */
#define CSIG_CFG0_DLS_DATA_LENGTH_1              (0x01000000UL)  /* Data length is 1 bits */
#define CSIG_CFG0_DLS_DATA_LENGTH_2              (0x02000000UL)  /* Data length is 2 bits */
#define CSIG_CFG0_DLS_DATA_LENGTH_3              (0x03000000UL)  /* Data length is 3 bits */
#define CSIG_CFG0_DLS_DATA_LENGTH_4              (0x04000000UL)  /* Data length is 4 bits */
#define CSIG_CFG0_DLS_DATA_LENGTH_5              (0x05000000UL)  /* Data length is 5 bits */
#define CSIG_CFG0_DLS_DATA_LENGTH_6              (0x06000000UL)  /* Data length is 6 bits */
#define CSIG_CFG0_DLS_DATA_LENGTH_7              (0x07000000UL)  /* Data length is 7 bits */
#define CSIG_CFG0_DLS_DATA_LENGTH_8              (0x08000000UL)  /* Data length is 8 bits */
#define CSIG_CFG0_DLS_DATA_LENGTH_9              (0x09000000UL)  /* Data length is 9 bits */
#define CSIG_CFG0_DLS_DATA_LENGTH_10             (0x0A000000UL)  /* Data length is 10 bits */
#define CSIG_CFG0_DLS_DATA_LENGTH_11             (0x0B000000UL)  /* Data length is 11 bits */
#define CSIG_CFG0_DLS_DATA_LENGTH_12             (0x0C000000UL)  /* Data length is 12 bits */
#define CSIG_CFG0_DLS_DATA_LENGTH_13             (0x0D000000UL)  /* Data length is 13 bits */
#define CSIG_CFG0_DLS_DATA_LENGTH_14             (0x0E000000UL)  /* Data length is 14 bits */
#define CSIG_CFG0_DLS_DATA_LENGTH_15             (0x0F000000UL)  /* Data length is 15 bits */
#define CSIG_CFG0_DLS_DATA_LENGTH_MASK           (0x0F000000UL)  /* Data length mask */

/* Selects the serial data direction (CSIGnDIR) */
#define CSIG_CFG0_DIR_MSB_FIRST                  (0x00000000UL)  /* Data length is 14 bits */
#define CSIG_CFG0_DIR_LSB_FIRST                  (0x00040000UL)  /* Data length is 15 bits */

/* Data phase selection bit (CSIGnDAP) */
#define CSIG_CFG0_DAP_RISING                     (0x00000000UL)  /* data input CSIGTSO is sampled with the rising edge of CSIGTSCK */
#define CSIG_CFG0_DAP_FALLING                    (0x00010000UL)  /* data input CSIGTSO is sampled with the falling edge of CSIGTSCK */

// only for CSIH in master mode, CSIG don't have this option
#define CSIH_CFG0_CS_IDLE_DISABLE                     (0x00000000UL)  
#define CSIH_CFG0_CS_IDLE_ENABLE                    (0x00008000UL)  


// only for CSIH in master mode, CSIG don't have this option
// setup time
#define CSIH_CFG0_CS_SETUP_CLK1                     (0x00000001UL)  	// 1 Tx clk
#define CSIH_CFG0_CS_SETUP_CLK1P5                    (0x00000002UL) 	// 1.5 Tx clk
#define CSIH_CFG0_CS_SETUP_CLK2P5                    (0x00000003UL) 

// only for CSIH in master mode, CSIG don't have this option
// inter data time, when CTL1.SIT=0
#define CSIH_CFG0_CS_INTERDATA_NONE                     (0x00000000UL)  	// 0 Tx clk		
#define CSIH_CFG0_CS_INTERDATA_CLK0P5                    (0x00000010UL) 	// 0.5 Tx clk
#define CSIH_CFG0_CS_INTERDATA_CLK1                    (0x00000020UL) 	// 1 Tx clk
#define CSIH_CFG0_CS_INTERDATA_CLK2                    (0x00000030UL) 	// 2 Tx clk
#define CSIH_CFG0_CS_INTERDATA_CLK3                    (0x00000040UL) 	// 3 Tx clk

// only for CSIH in master mode, CSIG don't have this option
// hold time, when CTL1.SIT=0
#define CSIH_CFG0_CS_HOLD_0P5                     (0x00000000UL)  	// 0.5 Tx clk
#define CSIH_CFG0_CS_HOLD_CLK1                    (0x00000100UL) 	// 1 Tx clk
#define CSIH_CFG0_CS_HOLD_CLK1P5                    (0x00000200UL) 	// 1.5 Tx clk
#define CSIH_CFG0_CS_HOLD_CLK2P5                    (0x00000300UL) 	// 2.5 Tx clk
#define CSIH_CFG0_CS_HOLD_CLK3P5                    (0x00000400UL) 	// 3.5 Tx clk


// only for CSIH in master mode, CSIG don't have this option
// idle time,  when CTL1.SIT=0
#define CSIH_CFG0_CS_IDLE_CLK0                 (0x00000000UL)  	//0.5 Tx clk
#define CSIH_CFG0_CS_IDLE_CLK1                 (0x0001000UL)  		// 1
#define CSIH_CFG0_CS_IDLE_CLK2                 (0x0002000UL)  		// 1.5


/*
    CSIG transmission register 0 for word access (CSIGnTX0W)
*/
/* Specifies the extended data length configuration (CSIGnEDL) */
#define CSIG_TX0W_EDL_NORMAL                     (0x00000000UL)  /* Normal operation */
#define CSIG_TX0W_EDL_EXTENDED                   (0x20000000UL)  /* Extended data length activated */

/*
    CSIG reception register 0 (CSIGnRX0)
*/
#define CSIG0_REG_BASEADD				( (CPU_INT32U )0xFFDB0000u)

#define  CSI_REG_CSIGnCFG0(BaseAddress)   (*(CPU_REG16 *)(BaseAddress + 0x1010))		// different with CSIH
#define  CSI_REG_CSIGnTX0W(BaseAddress)   (*(CPU_REG32 *)(BaseAddress + 0x1004))
#define  CSI_REG_CSIGnTX0H(BaseAddress)   (*(CPU_REG16 *)(BaseAddress + 0x1008))
#define  CSI_REG_CSIGnRX0(BaseAddress)   (*(CPU_REG16 *)(BaseAddress + 0x100C))

#define  CSIH0_REG_BASEADD                    ( (CPU_INT32U )0xFFD80000u)
#define  CSIH1_REG_BASEADD                    ( (CPU_INT32U )0xFFD82000u)
#define  CSIH2_REG_BASEADD                    ( (CPU_INT32U )0xFFD84000u)
#define  CSIH3_REG_BASEADD                    ( (CPU_INT32U )0xFFD86000u)

//Port function address
#define  CSI_REG_CSIHnCTL0(BaseAddress)   (*(CPU_REG08 *)(BaseAddress + 0x0000))
#define  CSI_REG_CSIHnCTL1(BaseAddress)   (*(CPU_REG32 *)(BaseAddress + 0x0010))
#define  CSI_REG_CSIHnCTL2(BaseAddress)   (*(CPU_REG16 *)(BaseAddress + 0x0014))
#define  CSI_REG_CSIHnSTR0(BaseAddress)   (*(CPU_REG32 *)(BaseAddress + 0x0004))
#define  CSI_REG_CSIHnSTCR0(BaseAddress)   (*(CPU_REG16 *)(BaseAddress + 0x0008))

#define  CSI_REG_CSIHnTX0W(BaseAddress)   (*(CPU_REG32 *)(BaseAddress + 0x1008))
#define  CSI_REG_CSIHnTX0H(BaseAddress)   (*(CPU_REG16 *)(BaseAddress + 0x100C))
#define  CSI_REG_CSIHnRX0W(BaseAddress)   (*(CPU_REG32 *)(BaseAddress + 0x1010))
#define  CSI_REG_CSIHnRX0H(BaseAddress)   (*(CPU_REG16 *)(BaseAddress + 0x1014))

#define  CSI_REG_CSIHnMCTL0(BaseAddress)   (*(CPU_REG16 *)(BaseAddress + 0x1040))
#define  CSI_REG_CSIHnMCTL1(BaseAddress)   (*(CPU_REG32 *)(BaseAddress + 0x1000))
#define  CSI_REG_CSIHnMCTL2(BaseAddress)   (*(CPU_REG32 *)(BaseAddress + 0x1004))
#define  CSI_REG_CSIHnMRWP0(BaseAddress)   (*(CPU_REG32 *)(BaseAddress + 0x1018))

#define  CSI_REG_CSIHnCFG0(BaseAddress)   (*(CPU_REG32 *)(BaseAddress + 0x1044))
#define  CSI_REG_CSIHnCFG1(BaseAddress)   (*(CPU_REG32 *)(BaseAddress + 0x1048))
#define  CSI_REG_CSIHnCFG2(BaseAddress)   (*(CPU_REG32 *)(BaseAddress + 0x104C))
#define  CSI_REG_CSIHnCFG3(BaseAddress)   (*(CPU_REG32 *)(BaseAddress + 0x1050))
#define  CSI_REG_CSIHnCFG4(BaseAddress)   (*(CPU_REG32 *)(BaseAddress + 0x1054))
#define  CSI_REG_CSIHnCFG5(BaseAddress)   (*(CPU_REG32 *)(BaseAddress + 0x1058))
#define  CSI_REG_CSIHnCFG6(BaseAddress)   (*(CPU_REG32 *)(BaseAddress + 0x105C))
#define  CSI_REG_CSIHnCFG7(BaseAddress)   (*(CPU_REG32 *)(BaseAddress + 0x1060))


#define  CSI_REG_CSIHnBRS0(BaseAddress)   (*(CPU_REG16 *)(BaseAddress + 0x1068))
#define  CSI_REG_CSIHnBRS1(BaseAddress)   (*(CPU_REG16 *)(BaseAddress + 0x106C))
#define  CSI_REG_CSIHnBRS2(BaseAddress)   (*(CPU_REG16 *)(BaseAddress + 0x1070))
#define  CSI_REG_CSIHnBRS3(BaseAddress)   (*(CPU_REG16 *)(BaseAddress + 0x1074))

#define  CSI_REG_CSIHnMRWP(BaseAddress)   (*(CPU_REG32 *)(BaseAddress + 0x1018))

#endif /*_CSI_H*/

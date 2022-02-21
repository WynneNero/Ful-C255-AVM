/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				*
*				  All Rights Reserved.          			*
*   Department : RN R&D SW1      						*
*   AUTHOR	   : 					*
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
*------------------------------------------------------------------------
* 0.1	   Jun 26,2016   PEI Jingli  Initial version
*------------------------------------------------------------------------
* 0.2	   July 21,2016  PEI Jingli  Refine code structure.
*------------------------------------------------------------------------
* 0.3	   Jan 11,2017   ZhangJie   Add parentheses and add u for constant value to avoid Coverity warning.
 ----------------------------------------------------------------------
* 0.4    	   Jan 16,2017   RenWeimin  Add clock define.
*----------------------------------------------------------------------
* 0.5          Jan 24,2017    ZhangJie     Fix Coverity warning.
*=====================================================================*/


/*============================================================================
 Includes
============================================================================*/
#ifndef   _UART_H
#define   _UART_H
#include "config.h"
#include "Clock_cfg.h"

/**** Definition of macros ****/
#define PLL_FREQ_HZ (CPUCLK_NORMAL_HZ)
#define UART_CLOCK_HZ (PLL_FREQ_HZ/2u)
#define UART_BAUDRATE(x) (UART_CLOCK_HZ/ (U32)((x)*6u) - 1u)

/* ------------------- Uart REGISTERS ----------------- */
#define  UART_REG_URTE0BASEADD                    ( (CPU_INT32U )0xFFCF0000u)
#define  UART_REG_URTE1BASEADD                    ( (CPU_INT32U )0xFFCF0040u)
#define  UART_REG_URTE2BASEADD                    ( (CPU_INT32U )0xFFCF0080u)
#define  UART_REG_URTE3BASEADD                    ( (CPU_INT32U )0xFFCF00C0u)
#define  UART_REG_URTE4BASEADD                    ( (CPU_INT32U )0xFFCF0100u)
#define  UART_REG_URTE5BASEADD                    ( (CPU_INT32U )0xFFCF0140u)

/*Port function address*/
#define  UART_REG_RLN3nLWBR(address)        	          (*(CPU_REG08 *)((address)+ 0x0001u))
#define  UART_REG_RLN3nLBRP01(address)                  (*(CPU_REG16 *)((address) + 0x0002u))
#define  UART_REG_RLN3nLMD(address)                       (*(CPU_REG08 *)((address) + 0x0008u))
#define  UART_REG_RLN3nLBFC(address)                      (*(CPU_REG08 *)((address)+ 0x0009u))
#define  UART_REG_RLN3nLSC(address)                        (*(CPU_REG08 *)((address) + 0x000Au))
#define  UART_REG_RLN3nLEDE(address)                      (*(CPU_REG08 *)((address) + 0x000Du))
#define  UART_REG_RLN3nLCUC(address)                      (*(CPU_REG08 *)((address) + 0x000Eu))
#define  UART_REG_RLN3nLTRC(address)                      (*(CPU_REG08 *)((address) + 0x0010u))
#define  UART_REG_RLN3nLMST(address)                      (*(CPU_REG08 *)((address) + 0x0011u))
#define  UART_REG_RLN3nLST(address)                        (*(CPU_REG08 *)((address) + 0x0012u))
#define  UART_REG_RLN3nLEST(address)        	          (*(CPU_REG08 *)((address)+ 0x0013u))
#define  UART_REG_RLN3nLDFC(address)                      (*(CPU_REG08*)((address) + 0x0014u))
#define  UART_REG_RLN3nLIDB(address)                      (*(CPU_REG08 *)((address) + 0x0015u))
#define  UART_REG_RLN3nLUDB0(address)                   (*(CPU_REG08 *)((address)+ 0x0017u))
#define  UART_REG_RLN3nLDBRb(address)                   (*(CPU_REG08 *)((address) + 0x0018u))
#define  UART_REG_RLN3nLUOER(address)                   (*(CPU_REG08 *)((address) + 0x0020u))
#define  UART_REG_RLN3nLUOR1(address)                   (*(CPU_REG08 *)((address) + 0x0021u))
#define  UART_REG_RLN3nLUTDR(address)                   (*(CPU_REG16 *)((address) + 0x0024u))
#define  UART_REG_RLN3nLURDR(address)                   (*(CPU_REG16 *)((address) + 0x0026u))
#define  UART_REG_RLN3nLUWTDR(address)                (*(CPU_REG16 *)((address) + 0x0028u))

/*
    UART mode register (RLN3nLMD)
*/
/* UART Reception Data Noise Filtering Disable (LRDNFS) */
#define UARTE_NOISE_FILTER_DISABLE     (0x00U)   /* disable the noise filter */
#define UARTE_NOISE_FILTER_ENABLE      (0x40U)   /*enable the noise filter */
/* LIN/UART Mode Select (LMD) */
#define UARTE_MODE_DISABLE                    (0x00U)     /* disable UART mode */
#define UARTE_MODE_ENABLE                     (0x01U)     /* enable UART mode */

/*
    UART Error Detection Enable Register (RLN3nLEDE)
*/
/* Framing Error Detection Enable (FERE) */
#define UARTE_FRAMING_ERROR_DISABLE     (0x00U)     /* disable framing error detection */
#define UARTE_FRAMING_ERROR_ENABLE     (0x08U)     /* enable framing error detection */
/* Overrun Error Detection Enable (OERE) */
#define UARTE_OVERRUN_ERROR_DISABLE     (0x00U)     /* disable overrun error detection */
#define UARTE_OVERRUN_ERROR_ENABLE     (0x04U)     /* enable overrun error detection */
/* Bit Error Detection Enable (BERE) */
#define UARTE_BIT_ERROR_DISABLE     (0x00U)     /* disable bit error detection */
#define UARTE_BIT_ERROR_ENABLE     (0x01U)     /* enable bit error detection */

/*
    LIN Wake-Up Baud Rate Select Register (RLN3nLWBR)
*/
/* Bit Sampling Count Select (NSPB[3:0]) */
#define UARTE_BIT_SAMPLE_0     (0x00U)     /* 16 sampling */
#define UARTE_BIT_SAMPLE_5     (0x50U)     /* 6 sampling */
#define UARTE_BIT_SAMPLE_6     (0x60U)     /* 7 sampling */
#define UARTE_BIT_SAMPLE_7     (0x70U)     /* 8 sampling */
#define UARTE_BIT_SAMPLE_8     (0x80U)     /* 9 sampling */
#define UARTE_BIT_SAMPLE_9     (0x90U)     /* 10 sampling */
#define UARTE_BIT_SAMPLE_A     (0xA0U)     /* 11 sampling */
#define UARTE_BIT_SAMPLE_B     (0xB0U)     /* 12 sampling */
#define UARTE_BIT_SAMPLE_C     (0xC0U)     /* 13 sampling */
#define UARTE_BIT_SAMPLE_D     (0xD0U)     /* 14 sampling */
#define UARTE_BIT_SAMPLE_E     (0xE0U)     /* 15 sampling */
#define UARTE_BIT_SAMPLE_F     (0xF0U)     /* 16 sampling */
/* Prescaler Clock Select (LPRS[2:0]) */
#define UARTE_PRSCLK_PCLK_0       (0x0000U)   /* PRSCLK -  PCLK/2^0 */
#define UARTE_PRSCLK_PCLK_1       (0x2000U)   /* PRSCLK -  PCLK/2^1 */
#define UARTE_PRSCLK_PCLK_2       (0x4000U)   /* PRSCLK -  PCLK/2^2 */
#define UARTE_PRSCLK_PCLK_3       (0x6000U)   /* PRSCLK -  PCLK/2^3 */
#define UARTE_PRSCLK_PCLK_4       (0x8000U)   /* PRSCLK -  PCLK/2^4 */
#define UARTE_PRSCLK_PCLK_5       (0xA000U)   /* PRSCLK -  PCLK/2^5 */
#define UARTE_PRSCLK_PCLK_6       (0xC000U)   /* PRSCLK -  PCLK/2^6 */
#define UARTE_PRSCLK_PCLK_7       (0xE000U)   /* PRSCLK -  PCLK/2^7 */

/*
UART Control Register (RLN3nLCUC)
*/
/* LIN Reset (OM0) */
#define UARTE_RESET_MODE_CAUSED         (0x00U)     /* LIN reset mode is caused */
#define UARTE_RESET_MODE_CANCELED     (0x01U)     /* LIN reset mode is canceled */

/*
UART Error Status Register (RLN3nLEST)
*/
/* Parity Error Flag(UPER) */
#define UARTE_PARITY_ERROR          (0x40U)     /* parity error in received data detected */
/* ID Matching Flag(IDMT) */
#define UARTE_ID_NOT_MATCHING         (0x00U)     /* The receive data does not match with the ID value */
#define UARTE_ID_MATCHING         (0x20U)     /*The receive data matches with the ID value*/
/* Expanded Bit Detection Flag(EXBT) */
#define UARTE_BIT_NOT_DETECT         (0x00U)     /* Expanded bit has not been detected */
#define UARTE_BIT_DETECT         (0x10U)     /*Expanded bit has been detected*/
/* Framing Error Flag(FER) */
#define UARTE_FRAM_ERROR            (0x08U)     /* framing error in received data detected */
/* Overrun Error Flag(OER) */
#define UARTE_OVERRUN_ERROR         (0x04U)     /* overrun error in received data detected */
/* Bit Error Flag(BER) */
#define UARTE_BIT_ERROR         (0x01U)     /* bit error in received data detected */

/*
UART Option Register 1 (RLN3nLUOR1)
*/
/* Transmission Interrupt Generation Timing Select (UTIGTS) */
#define UARTE_INT_TIMING_START       (0x00U)   /* INTUAEnTIT generated at the start of transmission */
#define UARTE_INT_TIMING_COMPLETE (0x08U)   /* INTUAEnTIT generated at transmission completion */

/*
UART Operation Enable Register
*/
/* Reception Enable (URTEnRXE) */
#define UARTE_RECEPTION_DISABLE     (0x00U)     /* disable reception operation */
#define UARTE_RECEPTION_ENABLE      (0x02U)     /* enable reception operation */
/* Transmission Enable (URTEnTXE) */
#define UARTE_TRANSMISSION_DISABLE  (0x00U)     /* disable transmission operation */
#define UARTE_TRANSMISSION_ENABLE   (0x01U)     /* enable transmission operation */

/*
    UART control register (RLN3nLBFC)
*/
/* UART Output Polarity Switch (UTPS) */
#define UARTE_UTPS_NO_INVERTED     (0x00U)   /* No inverted output of transmit data */
#define UARTE_UTPS_INVERTED           (0x40U)   /* Inverted output of transmit data */
/* UART Input Polarity Switch (URPS) */
#define UARTE_URPS_NO_INVERTED     (0x00U)   /* No inverted output of receive data */
#define UARTE_URPS_INVERTED            (0x20U)   /* Inverted output of receives data */
/* UART Parity Select (UPS[1:0]) */
#define UARTE_PARITY_NONE         (0x00U)    /* none parity */
#define UARTE_PARITY_EVEN         (0x08U)    /* even parity */
#define UARTE_PARITY_ZERO         (0x10U)    /* zero parity */
#define UARTE_PARITY_ODD          (0x11U)    /* odd parity */
/* UART Stop Bit length Select (USBLS) */
#define UARTE_STOPLENGTH_1BIT     (0x00U)   /* 1 bit */
#define UARTE_STOPLENGTH_2BIT     (0x04U)   /* 2 bits */
/* UART Transfer Format Order Select (UBOS) */
#define UARTE_TRANSFDIR_LSB       (0x00U)   /* LSB-first transfer */
#define UARTE_TRANSFDIR_MSB       (0x02U)   /* MSB-first transfer */
/* UART Character Length Select (UBLS) */
#define UARTE_LENGTH_8            (0x00U)   /* 8bit */
#define UARTE_LENGTH_7            (0x01U)   /* 7bit */

/**** Declaration of functions ****/
extern void UART0_Tx_Handler( void );
extern void UART0_Rx_Handler(void);
extern void UART0_Error_Handler( void );
extern void UART1_Tx_Handler( void );
extern void UART1_Rx_Handler(void);
extern void UART1_Error_Handler( void );
extern void UART2_Tx_Handler( void );
extern void UART2_Rx_Handler(void);
extern void UART2_Error_Handler( void );
extern void UART3_Tx_Handler( void );
extern void UART3_Rx_Handler(void);
extern void UART3_Error_Handler( void );
extern void UART4_Tx_Handler( void );
extern void UART4_Rx_Handler(void);
extern void UART4_Error_Handler( void );
extern void UART5_Tx_Handler( void );
extern void UART5_Rx_Handler(void);
extern void UART5_Error_Handler( void );
#endif /*_UART_H*/

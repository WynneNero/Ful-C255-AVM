/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				*
*				  All Rights Reserved.          			*
*   Department : RN R&D SW1      						*
*   AUTHOR	   : Shao  Guangxian					*
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
* 0.1	   Jun 26,2016  ZHANG Jie  Initial version
------------------------------------------------------------------------
* 0.2	   Aug 1,2016   PEI Jingli Delete uart io config inf for test. 		
------------------------------------------------------------------------
* 0.3         Sep 11,2016   Shang Qiuju Disable biterror det because bit error detect cannot 
                 working in full-deplex mode.
                When ove error is detect , clear error flag to avoid interrupt lost
------------------------------------------------------------------------
* 0.4	   Nov 1,2016   PEI Jingli Modify interface of UART_InitPort. 		
------------------------------------------------------------------------
* 0.5         Nov 25,2016  ZHANG Jie  Change related issues fellow CodeReviewMinutes_UART
*-----------------------------------------------------------------------
* 0.6	 Dec 20,2016   ShangQiuju Add irq_if.h for complile error.
*----------------------------------------------------------------------
* 0.7        Jan 05,2017    ZhangJie     Delete test code for SWP_TEST_EN
*----------------------------------------------------------------------
* 0.8        Jan 11,2017    ZhangJie     Fix Coverity warning.
 ----------------------------------------------------------------------
* 0.9    	 Jan 16,2017    RenWeimin  Fix bug. Baud setting.
*-----------------------------------------------------------------------
* 1.0   	 Jan 24,2017    ZhangJie     Remove unused include headfile.
*=====================================================================*/

/*============================================================================
 Includes
============================================================================*/
#include "uart.h"
#include "uart_if.h"
#include "uart_cfg.h"
#include "sys_assert_if.h"
#include "IRQ_if.h"
#include "cpu.h"

STATIC void Tx_Handler( UART_TYPE uart );
STATIC void Rx_Handler( UART_TYPE uart );
STATIC void Error_Handler( UART_TYPE uart );
STATIC U16 GetUARTIRQNumber(UART_TYPE uart);
STATIC void UART_EnableInterrupt(UART_TYPE uart );
STATIC void UART_DisableInterrupt(UART_TYPE uart );
STATIC U32 GetUartBaseAddress(UART_TYPE uart);

#define IS_UART_TYPE(uart)         ((uart==UART_0)||(uart==UART_1)||(uart==UART_2)||(uart==UART_3)||(uart==UART_4)||(uart==UART_5))

STATIC U8   uart_read_buffer[UART_MAX]={0u};
STATIC U8*   uart_send_buffer[UART_MAX]={0u};
STATIC U16   uart_send_len[UART_MAX]={0u};

/***********************************************************************
*  Name        : UART_Start
*  Description :
*  Parameter   : 	uart-> UART_0,UART_1...,UART_7
                 	baudrate -> 115200,19200,9600...
                 	options-> UART_RX_IT|UART_TX_IT|UART_RX_EN|UART_TX_EN...
*  Returns     : None
***********************************************************************/
void UART_Start( UART_TYPE uart, U32 baudrate)
{	
  /* LIN / UART Control Register */
  UART_REG_RLN3nLCUC(GetUartBaseAddress(uart)) = UARTE_RESET_MODE_CAUSED;

  /* UART Operation Enable Register */
  UART_REG_RLN3nLUOER(GetUartBaseAddress(uart)) = 0x0u;

  /*LIN reset mode ¡ú UART mode: LMD bit in RLN3nLMD register = 01B and OM0 bit in RLN3nLCUC register = 1B*/
   /* IN Mode Register/UART Mode Register (LMD) */
  UART_REG_RLN3nLMD(GetUartBaseAddress(uart)) = UARTE_MODE_ENABLE;

    /* LIN Wake-up Baud Rate Selector register  */
  UART_REG_RLN3nLWBR(GetUartBaseAddress(uart)) = UARTE_BIT_SAMPLE_5|UARTE_PRSCLK_PCLK_0;

   /* LIN Baud Rate Prescaler1/UART Baud Rate Prescaler */
  UART_REG_RLN3nLBRP01(GetUartBaseAddress(uart)) = UART_BAUDRATE(baudrate); 

  /* LIN / UART Error Detection Enable Register */
  /*Do not enable detect bit error!!!This is only used on test mode when Rx and Tx connected together.*/
  UART_REG_RLN3nLEDE(GetUartBaseAddress(uart))=0x0Cu;     /*Error detection*/

    /* LIN Break Field Configuration Register/UART Configuration Register1 */	
  UART_REG_RLN3nLBFC(GetUartBaseAddress(uart))  = UARTE_UTPS_NO_INVERTED|UARTE_URPS_NO_INVERTED|Uart_CfgData[uart];

  /* UART Option Register 1 */
  UART_REG_RLN3nLUOR1(GetUartBaseAddress(uart)) = UARTE_INT_TIMING_COMPLETE;

  /*LIN reset mode ¡ú UART mode: LMD bit in RLN3nLMD register = 01B and OM0 bit in RLN3nLCUC register = 1B*/
  /* LIN / UART Control Register */
  UART_REG_RLN3nLCUC(GetUartBaseAddress(uart)) = UARTE_RESET_MODE_CANCELED;

  /* UART Operation Enable Register */
  UART_REG_RLN3nLUOER(GetUartBaseAddress(uart)) = UARTE_RECEPTION_ENABLE|UARTE_TRANSMISSION_ENABLE;


  /* Enable UART Interrupts */
   UART_EnableInterrupt(uart);
}


/***********************************************************************
*  Name        : UART_Stop
*  Description :
*  Parameter   : 	uart-> UART_0,UART_1...,UART_7
                 	baudrate -> 115200,19200,9600...
                 	options-> UART_RX_IT|UART_TX_IT|UART_RX_EN|UART_TX_EN...
*  Returns     : None
***********************************************************************/
void UART_Stop( UART_TYPE uart )
{
  UART_REG_RLN3nLUOER(GetUartBaseAddress(uart))  = UARTE_RECEPTION_DISABLE|UARTE_TRANSMISSION_DISABLE; 

  UART_DisableInterrupt(uart);
}

/***********************************************************************
*  Name        : UART_SendBuf
*  Description :
*  Parameter   : uart->UART_0,UART_1,...UART_7
                 chr->byte
*  Returns     : U8
***********************************************************************/
void UART_SendBuf( UART_TYPE uart, U8* pdata,U16 datalen )
{
    /*assert_param(IS_UART_TYPE(uart));*/
    /*assert_param(IS_VALID_POINTER(pdata));*/
    /*assert_param(IS_RANGE(datalen, 1, 0xFFFF));*/
    if(datalen>0u)
    {
        uart_send_len[uart]= datalen;
        uart_send_buffer[uart]	=pdata;
        IRQ_IntClr(GetUARTIRQNumber(uart));
        UART_REG_RLN3nLUTDR(GetUartBaseAddress(uart)) =  pdata[0];
    }
    else
    {
        /*Nothing to do;*/
    }
}

/***********************************************************************
*  Name        : UART0_Tx_Handler
*  Description :
*  Parameter   : uart->  UART_0,UART_1,...UART_7
*  Returns     : None
***********************************************************************/
void UART0_Tx_Handler( void )
{
   Tx_Handler( UART_0);   
}

/***********************************************************************
*  Name        : UART0_RX_Handler
*  Description :
*  Parameter   : uart->  UART_0,UART_1,...UART_7
*  Returns     : None
***********************************************************************/
void UART0_Rx_Handler(void)
{

    Rx_Handler( UART_0);
}

/***********************************************************************
*  Name        : UART0_Error_Handler
*  Description :
*  Parameter   : uart->  UART_0,UART_1,...UART_7
*  Returns     : None
***********************************************************************/
void UART0_Error_Handler(void)
{
   Error_Handler(UART_0);
}

/***********************************************************************
*  Name        : UART1_Tx_Handler
*  Description :
*  Parameter   : uart->  UART_0,UART_1,...UART_7
*  Returns     : None
***********************************************************************/
void UART1_Tx_Handler( void )
{
   Tx_Handler( UART_1);
   
}

/***********************************************************************
*  Name        : UART1_RX_Handler
*  Description :
*  Parameter   : uart->  UART_0,UART_1,...UART_7
*  Returns     : None
***********************************************************************/
void UART1_Rx_Handler(void)
{

    Rx_Handler( UART_1);
   
}

/***********************************************************************
*  Name        : UART1_Error_Handler
*  Description :
*  Parameter   : uart->  UART_0,UART_1,...UART_7
*  Returns     : None
***********************************************************************/
void UART1_Error_Handler(void)
{
   Error_Handler(UART_1);
}

/***********************************************************************
*  Name        : UART2_Tx_Handler
*  Description :
*  Parameter   : uart->  UART_0,UART_1,...UART_7
*  Returns     : None
***********************************************************************/
void UART2_Tx_Handler( void )
{
   Tx_Handler( UART_2);
   
}

/***********************************************************************
*  Name        : UART2_RX_Handler
*  Description :
*  Parameter   : uart->  UART_0,UART_1,...UART_7
*  Returns     : None
***********************************************************************/
void UART2_Rx_Handler(void)
{

   Rx_Handler( UART_2);
}

/***********************************************************************
*  Name        : UART2_Error_Handler
*  Description :
*  Parameter   : uart->  UART_0,UART_1,...UART_7
*  Returns     : None
***********************************************************************/
void UART2_Error_Handler(void)
{
   Error_Handler(UART_2);
}

/***********************************************************************
*  Name        : UART3_Tx_Handler
*  Description :
*  Parameter   : uart->  UART_0,UART_1,...UART_7
*  Returns     : None
***********************************************************************/
void UART3_Tx_Handler( void )
{
   Tx_Handler( UART_3);
}

/***********************************************************************
*  Name        : UART3_Rx_Handler
*  Description :
*  Parameter   : uart->  UART_0,UART_1,...UART_7
*  Returns     : None
***********************************************************************/
void UART3_Rx_Handler(void)
{

   Rx_Handler( UART_3);
}

/***********************************************************************
*  Name        : UART3_Error_Handler
*  Description :
*  Parameter   : uart->  UART_0,UART_1,...UART_7
*  Returns     : None
***********************************************************************/
void UART3_Error_Handler(void)
{
   Error_Handler(UART_3);
}

/***********************************************************************
*  Name        : UART4_Tx_Handler
*  Description :
*  Parameter   : uart->  UART_0,UART_1,...UART_7
*  Returns     : None
***********************************************************************/
void UART4_Tx_Handler( void )
{
   Tx_Handler( UART_4);
}

/***********************************************************************
*  Name        : UART4_RX_Handler
*  Description :
*  Parameter   : uart->  UART_0,UART_1,...UART_7
*  Returns     : None
***********************************************************************/
void UART4_Rx_Handler(void)
{

   Rx_Handler( UART_4);
}


/***********************************************************************
*  Name        : UART4_Error_Handler
*  Description :
*  Parameter   : uart->  UART_0,UART_1,...UART_7
*  Returns     : None
***********************************************************************/
void UART4_Error_Handler(void)
{
   Error_Handler(UART_4);
}

/***********************************************************************
*  Name        : UART5_Tx_Handler
*  Description :
*  Parameter   : uart->  UART_0,UART_1,...UART_7
*  Returns     : None
***********************************************************************/
void UART5_Tx_Handler( void )
{
   Tx_Handler( UART_5);
}

/***********************************************************************
*  Name        : UART5_RX_Handler
*  Description :
*  Parameter   : uart->  UART_0,UART_1,...UART_7
*  Returns     : None
***********************************************************************/
void UART5_Rx_Handler(void)
{

   Rx_Handler( UART_5);
}

/***********************************************************************
*  Name        : UART5_Error_Handler
*  Description :
*  Parameter   : uart->  UART_0,UART_1,...UART_7
*  Returns     : None
***********************************************************************/
void UART5_Error_Handler(void)
{
   Error_Handler(UART_5);
}

/***********************************************************************
*  Name        : Tx_Handler
*  Description :
*  Parameter   : uart->  UART_0,UART_1,...UART_7
*  Returns     : None
***********************************************************************/
void Tx_Handler( UART_TYPE uart )
{
    /*assert_param(IS_UART_TYPE(uart));*/

    uart_send_len[uart]--;
	
    /*invoke user function here*/
   if(uart_send_len[uart]==0u)
   {
       if( NULL != uart_tx_callback[uart])
       {
          uart_tx_callback[uart]();
      }
   }
  else
  { 
    uart_send_buffer[uart]++;
    UART_REG_RLN3nLUTDR(GetUartBaseAddress(uart)) =  *(uart_send_buffer[uart]);
  }

}


/***********************************************************************
*  Name        : Rx_Handler
*  Description :
*  Parameter   : uart->  UART_0,UART_1,...UART_7
*  Returns     : None
***********************************************************************/
void Rx_Handler( UART_TYPE uart )
{
  U8 value =0u;
    /*assert_param(IS_UART_TYPE(uart));*/

    value=UART_REG_RLN3nLURDR(GetUartBaseAddress(uart));
    uart_read_buffer[uart] = value;
    
    /*Add to solute Coverity warning for unused variable.*/
    (void)uart_read_buffer[uart];
    
    if(NULL != uart_rx_callback[uart])
    {
        uart_rx_callback[uart](value);
    }
}

/*TODO:*/
/***********************************************************************
*  Name        : Error_Handler
*  Description :
*  Parameter   : uart->  UART_0,UART_1,...UART_7
*  Returns     : None
***********************************************************************/
void Error_Handler( UART_TYPE uart )
{
    U8 err_type;
	U8 value =0u;

    err_type = UART_REG_RLN3nLEST(GetUartBaseAddress(uart)); 
	value = UART_REG_RLN3nLURDR(GetUartBaseAddress(uart));
    (void)value;
    UART_REG_RLN3nLEST(GetUartBaseAddress(uart)) = 0x00u;/* clear error bits */
    if(NULL != uart_error_callback[uart])
    {
        uart_error_callback[uart](err_type);
    }
}


/***********************************************************************
*  Name        : GetUARTIRQNumber
*  Description : get interrupt channel ID
*  Parameter   : uart - uart channel
*  Returns     : None
***********************************************************************/
U16 GetUARTIRQNumber(UART_TYPE uart)
{
    U16 IrqNo =0u;

    if(uart==UART_0)
    {
        IrqNo=INTRLIN30UR0;
    }
    else if(uart==UART_1)
    {
        IrqNo=INTRLIN31UR0;
    }  
    else if(uart==UART_2)
    {
        IrqNo=INTRLIN32UR0;
    }   
    else if(uart==UART_3)
    {
        IrqNo=INTRLIN33UR0;
    }   
    else if(uart==UART_4)
    {
        /*IrqNo=INTRLIN34UR0;*/
    }
    else if(uart==UART_5)
    {
        /*IrqNo=INTRLIN35UR0;*/
    }
    return IrqNo;  
}

/***********************************************************************
*  Name        : UART_EnableInterrupt
*  Description : enable UART interrupt
*  Parameter   : uart - uart channel
*  Returns     : None
***********************************************************************/
void UART_EnableInterrupt(UART_TYPE uart )
{
    IRQ_IntClr(GetUARTIRQNumber(uart));
    IRQ_IntEn(GetUARTIRQNumber(uart));

    IRQ_IntClr(GetUARTIRQNumber(uart)+1u);
    IRQ_IntEn(GetUARTIRQNumber(uart)+1u);

    IRQ_IntClr(GetUARTIRQNumber(uart)+2u);
    IRQ_IntEn(GetUARTIRQNumber(uart)+2u);
}

/***********************************************************************
*  Name        : UART_DisableInterrupt
*  Description : disable UART interrupt
*  Parameter   : uart - uart channel
*  Returns     : None
***********************************************************************/
void UART_DisableInterrupt(UART_TYPE uart )
{
    IRQ_IntDis(GetUARTIRQNumber(uart));
    IRQ_IntClr(GetUARTIRQNumber(uart));

    IRQ_IntDis(GetUARTIRQNumber(uart)+1u);
    IRQ_IntClr(GetUARTIRQNumber(uart)+1u);

    IRQ_IntDis(GetUARTIRQNumber(uart)+2u);
    IRQ_IntClr(GetUARTIRQNumber(uart)+2u);
}

/***********************************************************************
*  Name        : GetUartRegOffset
*  Description :
*  Parameter   : uart->  UART_0,UART_1,...UART_7
*  Returns     : None
***********************************************************************/
U32 GetUartBaseAddress(UART_TYPE uart)
{
  U32 Address =0u;
  if(uart==UART_0)
  {
   Address=UART_REG_URTE0BASEADD;
  }
  else if(uart==UART_1)
  {
      Address=UART_REG_URTE1BASEADD;
  }  
  else if(uart==UART_2)
  {
      Address=UART_REG_URTE2BASEADD;
  }  
  else if(uart==UART_3)
  {
      Address=UART_REG_URTE3BASEADD;
  }   
  else if(uart==UART_4)
  {
      Address=UART_REG_URTE4BASEADD;
  } 
  else if(uart==UART_5)
  {
      Address=UART_REG_URTE5BASEADD;
  }  
  return Address;
}




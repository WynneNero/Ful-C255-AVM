/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                                 *
*   AUTHOR     :                                                       *
************************************************************************
* Object        :
* Module        :	CSI
* Instance      :
* Description   :	SPI opertaion.				
				Support 4 channel of CSIH and 1 channel of CSIG.
				Send/receive are handled in interrupts.
				Handshake function are enabled. 
				Hardware must reserve RYO/RYI pin if SPI is required.				
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date           Name                 Changes and comments
*     0.1	  2016-6-23	  RenWeiMin		Init, multiple Chip select is not supported
	                                                         FIFO mode is not supported.
*-----------------------------------------------------------------------
*	0.2    2016-7-28      RenWeiMin          Add handshake to avoid overrun.		
*-----------------------------------------------------------------------
*	0.3    2016-8-24      ShangQiuju         Add Dual Buffer mode             
*-----------------------------------------------------------------------
*     0.4    2016-11-10     ShangQiuju        When send to  fifo ,check fifo is busy or not.  
*-----------------------------------------------------------------------
*     0.5    2016-11-10     ShangQiuju        Remove io set in this module,io config need set in mcu_pin.cc 
*-----------------------------------------------------------------------
*     0.6    2016-11-10     ShangQiuju        Remove csi_send len limit. 
*-----------------------------------------------------------------------
*     0.6    2016-11-10     ShangQiuju        Update fifo send function for send length.
*-----------------------------------------------------------------------
*     0.7    2016-11-21     ShangQiuju        Remove unused csi_send_over.
*-----------------------------------------------------------------------
*     0.8    2016-12-20     ShangQiuju        Add  irq_if.h for compile error.
*-----------------------------------------------------------------------
*     0.9    2017-01-24     ZhangJie            Fix Coverity warning.
*-----------------------------------------------------------------------
*     1.0    2017-02-16     ShangQiuju        Update data and clock phase config.
*----------------------------------------------------------------------
*     1.1    2017-04-01    PEI Jingli     Fix include files.
*     1.2    2017-05-18      LiShi        	  Add SPI FIFO Init mode.
*=====================================================================*/
#include "csi_cfg.h"
#include "Clock_cfg.h"
#include "cpu.h"
#include "irq_if.h"

STATIC CSI_FRAME_TYPE CSI_Message[CSI_MAX]={NULL};
U16 RxData[8] = {0,0,0,0,0,0,0,0};

STATIC CPU_INT32U GetCSIBaseAddress(CSI_TYPE csi);
STATIC U16 GetCSIIRQNumber(CSI_TYPE csi);
STATIC void Tx_Handler( CSI_TYPE csi ,BOOL bIsFIFO);
STATIC void Rx_Handler( CSI_TYPE csi,BOOL bIsFIFO);
STATIC void Error_Handler(CSI_TYPE csi ,BOOL bIsFIFO);


void CSI_EnableInterrupt(CSI_TYPE csi );
void CSI_DisableInterrupt(CSI_TYPE csi );

extern void CSIG0_Tx_handler(void);
extern void CSIG0_Rx_handler(void);
extern void CSIG0_Error_handler(void);
extern void CSIH0_Tx_handler(void);
extern void CSIH0_Rx_handler(void);
extern void CSIH0_Error_handler(void);
extern void CSIH1_Tx_handler(void);
extern void CSIH1_Rx_handler(void);
extern void CSIH1_Error_handler(void);
extern void CSIH2_Tx_handler(void);
extern void CSIH2_Rx_handler(void);
extern void CSIH2_Error_handler(void);
extern void CSIH3_Tx_handler(void);
extern void CSIH3_Rx_handler(void);
extern void CSIH3_Error_handler(void);

/***********************************************************************
*  Name        : CSI_Init
*  Description : Initialize specified SPI channel, don't provide clock here.
*  Parameter   : csi - only support CSIH0/1/2/3
                 baudrate - only valid for master mode,
                                 In master mode maximun freq is 10MHZ(it must be up to PCLK/4)
                                 In slave mode maximun freq is 5MHZ(it must be up to PCLK/6)
                 optionsCTL1 - for CTL1
                 optionsCFG0 -for CFG0
                 bMasterMode	- TRUE : master mode; FALSE: slave mode
                 isUsedCsi - specify IO channel of chip select (in/out) 
                 			      don't support multiple CS						
                 			TRUE:support   FALSE:not support
*  Returns     : None
***********************************************************************/
void CSI_Init( CSI_TYPE csi, SPI_BAUD_OPTION baudrate,BOOL bIsMaster,BOOL isUsedCsi,BOOL bOpenRY)
{
    U32 u32csi_base_adr=0;
    U8 index;
    U32 u32baund = (U32)baudrate;
    
    u32csi_base_adr = GetCSIBaseAddress(csi);   

    CSI_DisableInterrupt(csi);

    CSI_REG_CSIHnCTL0(u32csi_base_adr) = (CSIG_CTL0_PWR_STOP_OPERATION_CLOCK | CSIG_CTL0_TXE_TRANSMISSION_DISABLE |
    CSIG_CTL0_RXE_TRANSMISSION_DISABLE |  CSIG_CTL0_B0_SET_TO_1);	/* direct access */

    if(csi==CSIG_0)
    {
        CSI_REG_CSIGnCFG0(u32csi_base_adr)  = Csi_CfgData[csi][0];
    }
    else
    {
        for(index = 0u;index<8u;index++)
        {
            CSI_REG_CSIHnCFGx(u32csi_base_adr,(U32)index) = Csi_CfgData[csi][index];
        }
    }

    CSI_REG_CSIHnSTCR0(u32csi_base_adr) = (CSIG_STCR0_DCEC | CSIG_STCR0_PEC | CSIG_STCR0_OVEC);

    if(bIsMaster)
    {
        if(csi==CSIG_0)
        {
            CSI_REG_CSIHnCTL2(u32csi_base_adr) |=(U16)((CPUCLK_NORMAL_HZ>>1)/u32baund);
            CSI_REG_CSIHnCTL2(u32csi_base_adr) &= 0x1fffu;		/*PCLK, master mode*/
        }
        else
        {
            CSI_REG_CSIHnBRS0(u32csi_base_adr) |= (U16)((CPUCLK_NORMAL_HZ>>1)/u32baund);
            CSI_REG_CSIHnCTL2(u32csi_base_adr) &= 0x1FFFu;		/*PCLK, master mode*/
            if(isUsedCsi)
            {
                CSI_REG_CSIHnCTL1(u32csi_base_adr) |=(CSIH_CTL1_CS_RETURN_INACTIVE_ENABLE | CSIG_CTL1_SSE_CSIGTSSI_ENABLE);	/*enable slave select, CS return to inactive*/
            }
        }
    }
    else		/* slave*/
    {
        if(csi==CSIG_0)
        {
            if(isUsedCsi)
            {
                CSI_REG_CSIHnCTL1(u32csi_base_adr) |=CSIG_CTL1_SSE_CSIGTSSI_ENABLE;	/*enable SSI*/
            }
        }
        else
        {
            CSI_REG_CSIHnBRS0(u32csi_base_adr)= 0;
            if(isUsedCsi)
            {			
                CSI_REG_CSIHnCTL1(u32csi_base_adr) |=(CSIH_CTL1_CS_RETURN_INACTIVE_ENABLE | CSIG_CTL1_SSE_CSIGTSSI_ENABLE);	/*enable slave select, CS return to inactive*/
            }
        }
        CSI_REG_CSIHnCTL2(u32csi_base_adr) |= 0xE000u;		/*slave, external clock*/
    }

    /* enable Hand shake*/
    if(bOpenRY)
        CSI_REG_CSIHnCTL1(u32csi_base_adr) |=	CSIG_CTL1_HSE_HANDSHAKE_ENABLE;
        
    /* config of clock and data phase*/
    if(csi==CSIG_0)
    {
        if(Csi_ClockDataPhaseCfgData[csi][0]&0x02)/*E_SPI_MODE2,E_SPI_MODE3,default level of clock is low */
        {
            CSI_REG_CSIHnCTL1(u32csi_base_adr) |= CSIG_CTL1_CKR_CLOCK_LEVEL_LOW;
        }
        else/*E_SPI_MODE0,E_SPI_MODE1,default level of clock is high */
        {
            CSI_REG_CSIHnCTL1(u32csi_base_adr) |= CSIG_CTL1_CKR_CLOCK_LEVEL_HIGH;
        }
        
        if(Csi_ClockDataPhaseCfgData[csi][0]&0x01)/*E_SPI_MODE1,E_SPI_MODE3,data can be capture in first edge of clock*/
        {
            CSI_REG_CSIGnCFG0(u32csi_base_adr)  |=CSIG_CFG0_DAP_PHASE_0 ;
        }
        else/*E_SPI_MODE0,E_SPI_MODE2,data can be capture in second edge of clock*/
        {
            CSI_REG_CSIGnCFG0(u32csi_base_adr)  |=CSIG_CFG0_DAP_PHASE_180 ;
        }
        
    }
    else
    {        
        for(index = 0u;index<8u;index++)
        {
            switch(Csi_ClockDataPhaseCfgData[csi][index])
            {
                case E_SPI_MODE_0:
                     CSI_REG_CSIHnCFGx(u32csi_base_adr,(U32)index) |= CSIH_CFGx_CKP_DAP_0;
                break;
                case E_SPI_MODE_1:
                     CSI_REG_CSIHnCFGx(u32csi_base_adr,(U32)index) |= CSIH_CFGx_CKP_DAP_1;
                break;
                case E_SPI_MODE_2:
                     CSI_REG_CSIHnCFGx(u32csi_base_adr,(U32)index) |= CSIH_CFGx_CKP_DAP_2;
                break;
                case E_SPI_MODE_3:
                     CSI_REG_CSIHnCFGx(u32csi_base_adr,(U32)index) |= CSIH_CFGx_CKP_DAP_3;
                break;
                default:break;
            }
        }
    }
}


/***********************************************************************
*  Name        : CSI_Start
*  Description : start SPI module
*  Parameter   : csi - csi channel
                 	   datalen - reserved(to do... extended data length)
*  Returns     : None
***********************************************************************/
void CSI_Start(CSI_TYPE csi, U8 datalen)
{
    CSI_Message[csi].CsiTxEDLCnt = datalen;

    /* module clock*/
    CSI_REG_CSIHnCTL0(GetCSIBaseAddress(csi)) |=(CSIG_CTL0_PWR_PROVIDE_OPERATION_CLOCK |\
	    CSIG_CTL0_TXE_TRANSMISSION_ENABLE | CSIG_CTL0_RXE_TRANSMISSION_ENABLE);  

    CSI_EnableInterrupt(csi);
}

/***********************************************************************
*  Name        : CSI_EnableInterrupt
*  Description : enable SPI interrupt
*  Parameter   : csi - csi channel
*  Returns     : None
***********************************************************************/
void CSI_EnableInterrupt(CSI_TYPE csi )
{
    /* clear INTCSIG0IC interrupt request flag */
    /* enable INTCSIG0IC interrupt */
    /* clear INTCSIG0IR interrupt request flag */
    /* enable INTCSIG0IR interrupt */
    /* clear INTCSIG0IRE interrupt request flag */
    /* enable INTCSIG0IRE interrupt */
    IRQ_IntClr(GetCSIIRQNumber(csi));
    IRQ_IntEn(GetCSIIRQNumber(csi));

    IRQ_IntClr(GetCSIIRQNumber(csi)+1u);
    IRQ_IntEn(GetCSIIRQNumber(csi)+1u);

    if(csi==CSIG_0)
    {
        IRQ_IntClr(GetCSIIRQNumber(csi)+30u);
        IRQ_IntEn(GetCSIIRQNumber(csi)+30u);
    }
    else
    {
        IRQ_IntClr(GetCSIIRQNumber(csi)+2u);
        IRQ_IntEn(GetCSIIRQNumber(csi)+2u);
    }
}


/***********************************************************************
*  Name        : CSI_EnableTxInterrupt
*  Description : enable SPI tx interrupt
*  Parameter   : csi - csi channel
*  Returns     : None
***********************************************************************/
void CSI_EnableTxInterrupt(CSI_TYPE csi )
{
    U32 u32csi_base_adr=0;

    u32csi_base_adr = GetCSIBaseAddress(csi);  
    CSI_REG_CSIHnCTL0(u32csi_base_adr) |=((U8) CSIG_CTL0_TXE_TRANSMISSION_ENABLE);
}

/***********************************************************************
*  Name        : CSI_DisableTxInterrupt
*  Description : disable SPI tx interrupt
*  Parameter   : csi - csi channel
*  Returns     : None
***********************************************************************/
void CSI_DisableTxInterrupt(CSI_TYPE csi )
{
    U32 u32csi_base_adr=0;

    u32csi_base_adr = GetCSIBaseAddress(csi);

    CSI_REG_CSIHnCTL0(u32csi_base_adr) &=~ ((U8) CSIG_CTL0_TXE_TRANSMISSION_ENABLE);
}

/***********************************************************************
*  Name        : CSI_DisableInterrupt
*  Description : disable SPI interrupt
*  Parameter   : csi - csi channel
*  Returns     : None
***********************************************************************/
void CSI_DisableInterrupt(CSI_TYPE csi )
{
    IRQ_IntDis(GetCSIIRQNumber(csi));		/* IC:*/
    IRQ_IntClr(GetCSIIRQNumber(csi));

    IRQ_IntDis(GetCSIIRQNumber(csi)+1u);	/*IR:receive interrupt*/
    IRQ_IntClr(GetCSIIRQNumber(csi)+1u);

    if(csi==CSIG_0)
    {
        IRQ_IntDis(GetCSIIRQNumber(csi)+30u);	/*IRE  : communication error interrupt*/
        IRQ_IntClr(GetCSIIRQNumber(csi)+30u);
    }
    else
    {
        IRQ_IntDis(GetCSIIRQNumber(csi)+2u);	/* IRE*/
        IRQ_IntClr(GetCSIIRQNumber(csi)+2u);
    }
}

/***********************************************************************
*  Name        : CSI_Stop
*  Description : stop SPI module
*  Parameter   : csi - csi channel
*  Returns     : None
***********************************************************************/
void CSI_Stop(CSI_TYPE csi )
{
    /* disable CSIG0 transmission operation */
    /* disable CSIG0 reception operation */
    /* disable CSIG0 */
    CSI_REG_CSIHnCTL0(GetCSIBaseAddress(csi))=(CSIG_CTL0_PWR_STOP_OPERATION_CLOCK|CSIG_CTL0_TXE_TRANSMISSION_DISABLE|\
                                                                      CSIG_CTL0_RXE_TRANSMISSION_DISABLE);  


    /* disable INTCSIG0IC interrupt */
    /* clear INTCSIG0IC interrupt request flag */
    /* disable INTCSIG0IR interrupt */
    /* clear INTCSIG0IR interrupt request flag */
    /* disable INTCSIG0IRE interrupt */
    /* clear INTCSIG0IRE interrupt request flag */
    CSI_DisableInterrupt(csi);

}

/***********************************************************************
*  Name        : CSI_StopFIFO
*  Description : stop SPI FIFO module
*  Parameter   : csi - csi channel
*  Returns     : None
***********************************************************************/
void CSI_StopFIFO(CSI_TYPE csi)
{
    U32 u32csi_base_adr=0u;
    u32csi_base_adr = GetCSIBaseAddress(csi);   

    CSI_REG_CSIHnSTCR0(u32csi_base_adr) = 0xffffu;
    CSI_REG_CSIHnMRWP0(u32csi_base_adr) =  0x00000000u; /*CSIHnRRA[6:0] 00H clear read pointer*/
    CSI_Stop(csi);
}

/***********************************************************************
*  Name        : CSI_InitDualBuffer
*  Description : Init SPI Dual Buffer module
*  Parameter   : csi - csi channel
                        baudrate - only for master mode
                        bIsMaster - is master mode
                        CsSsiChannel -
                        bMasterMode	- TRUE : master mode; FALSE: slave mode
                        isUsedCsi - specify IO channel of chip select (in/out) 
                        			      don't support multiple CS					
                 			TRUE:support   FALSE:not support
*  Returns     : None
***********************************************************************/
void CSI_InitDualBuffer( CSI_TYPE csi, SPI_BAUD_OPTION baudrate,BOOL bIsMaster,BOOL isUsedCsi,BOOL bOpenRY)
{    
      U32 u32csi_base_adr=0u;
    U8 index;
    U32 u32baund  = (U32)baudrate;

    CSI_DisableInterrupt(csi);
    u32csi_base_adr = GetCSIBaseAddress(csi);   
    CSI_REG_CSIHnCTL0(u32csi_base_adr) = 0u; /*clear CSIHnPWR*/
    
    for(index = 0u;index<8u;index++)
    {
        switch(Csi_ClockDataPhaseCfgData[csi][index])
        {
            case E_SPI_MODE_0:
                 CSI_REG_CSIHnCFGx(u32csi_base_adr,(U32)index) = Csi_CfgData[csi][index] | CSIH_CFGx_CKP_DAP_0;
            break;
            case E_SPI_MODE_1:
                 CSI_REG_CSIHnCFGx(u32csi_base_adr,(U32)index) = Csi_CfgData[csi][index] | CSIH_CFGx_CKP_DAP_1;
            break;
            case E_SPI_MODE_2:
                 CSI_REG_CSIHnCFGx(u32csi_base_adr,(U32)index) = Csi_CfgData[csi][index] | CSIH_CFGx_CKP_DAP_2;
            break;
            case E_SPI_MODE_3:
                 CSI_REG_CSIHnCFGx(u32csi_base_adr,(U32)index) = Csi_CfgData[csi][index] | CSIH_CFGx_CKP_DAP_3;
            break;
            default:break;
        }
    }
        
    CSI_REG_CSIHnCTL1(u32csi_base_adr) = CSIH_CTL1_CKR_CLOCK_LEVEL_HIGH;/*always used CKR = 0, clock phasse selection used CSIHnCKPx to set*/
    if(isUsedCsi)
    {
        CSI_REG_CSIHnCTL1(u32csi_base_adr) |=(CSIH_CTL1_CS_RETURN_INACTIVE_ENABLE | CSIG_CTL1_SSE_CSIGTSSI_ENABLE);	/*enable slave select, CS return to inactive*/
    }

    if(bIsMaster)
    {   
        CSI_REG_CSIHnBRS0(u32csi_base_adr) |=(U16)((CPUCLK_NORMAL_HZ>>1)/u32baund);
        CSI_REG_CSIHnCTL2(u32csi_base_adr) &= 0x1fffu;		/*PCLK, master mode*/
    }
    else
        CSI_REG_CSIHnCTL2(u32csi_base_adr) = 0xE000u;		/*slave, external clock*/

    CSI_REG_CSIHnSTCR0(u32csi_base_adr) = 0xffffu;
    CSI_REG_CSIHnMCTL0(u32csi_base_adr) =  0x0100u;  /*CSIHnMMS[1:0] 01 Dual Buffer mode*/

    CSI_REG_CSIHnMRWP0(u32csi_base_adr) =  0x00000000u; /*CSIHnRRA[6:0] 00H clear read pointer*/   
    
    /*enable Hand shake*/
    if(bOpenRY)
        CSI_REG_CSIHnCTL1(u32csi_base_adr) |=	CSIG_CTL1_HSE_HANDSHAKE_ENABLE;
}

/***********************************************************************
*  Name        : CSI_InitFIFO
*  Description : Init SPI fifo module
*  Parameter   : csi - csi channel
                        baudrate - only for master mode
                        bIsMaster - is master mode
                        CsSsiChannel -
                        bMasterMode	- TRUE : master mode; FALSE: slave mode
                        isUsedCsi - specify IO channel of chip select (in/out) 
                        			      don't support multiple CS					
                 			TRUE:support   FALSE:not support
*  Returns     : None
***********************************************************************/
void CSI_InitFIFO( CSI_TYPE csi, SPI_BAUD_OPTION baudrate,BOOL bIsMaster,BOOL isUsedCsi,BOOL bOpenRY)
{    
    U32 u32csi_base_adr=0u;
    U8 index;
    U32 u32baund  = (U32)baudrate;

    CSI_DisableInterrupt(csi);
    u32csi_base_adr = GetCSIBaseAddress(csi);   
    CSI_REG_CSIHnCTL0(u32csi_base_adr) = 0u; /*clear CSIHnPWR*/
    
    for(index = 0u;index<8u;index++)
    {
        switch(Csi_ClockDataPhaseCfgData[csi][index])
        {
            case E_SPI_MODE_0:
                 CSI_REG_CSIHnCFGx(u32csi_base_adr,(U32)index) = Csi_CfgData[csi][index] | CSIH_CFGx_CKP_DAP_0;
            break;
            case E_SPI_MODE_1:
                 CSI_REG_CSIHnCFGx(u32csi_base_adr,(U32)index) = Csi_CfgData[csi][index] | CSIH_CFGx_CKP_DAP_1;
            break;
            case E_SPI_MODE_2:
                 CSI_REG_CSIHnCFGx(u32csi_base_adr,(U32)index) = Csi_CfgData[csi][index] | CSIH_CFGx_CKP_DAP_2;
            break;
            case E_SPI_MODE_3:
                 CSI_REG_CSIHnCFGx(u32csi_base_adr,(U32)index) = Csi_CfgData[csi][index] | CSIH_CFGx_CKP_DAP_3;
            break;
            default:break;
        }
    }
        
    CSI_REG_CSIHnCTL1(u32csi_base_adr) 	= 	0x00000000;

    if(bIsMaster)
    {   
        CSI_REG_CSIHnBRS0(u32csi_base_adr) |=(U16)((CPUCLK_NORMAL_HZ>>1)/u32baund);
        CSI_REG_CSIHnCTL2(u32csi_base_adr) &= 0x1fffu;		/*PCLK, master mode*/
    }
    else
        CSI_REG_CSIHnCTL2(u32csi_base_adr) = 0xE000u;		/*slave, external clock*/

    CSI_REG_CSIHnSTCR0(u32csi_base_adr) = 0xffffu;
    CSI_REG_CSIHnMCTL0(u32csi_base_adr) =	0x00000001;

    CSI_REG_CSIHnMRWP0(u32csi_base_adr) =  0x00000000u; /*CSIHnRRA[6:0] 00H clear read pointer*/   
    CSI_REG_CSIHnMCTL1(u32csi_base_adr) |=	120 ;  		/* INTCSIHTIC 8 byte */
	
    /*enable Hand shake*/
    if(bOpenRY)
        CSI_REG_CSIHnCTL1(u32csi_base_adr) |=	CSIG_CTL1_HSE_HANDSHAKE_ENABLE;
}

/***********************************************************************
*  Name        : CSI_SetFifoPointer
*  Description : Set fifo pointer
*  Parameter   : csi - csi channel
*  Returns     : None
***********************************************************************/
void CSI_SetFifoPointer( CSI_TYPE csi)
{    
    U32 u32csi_base_adr=0u;
	
    u32csi_base_adr = GetCSIBaseAddress(csi);   
   
	CSI_REG_CSIHnCTL1(u32csi_base_adr) = 	0x00000000;
	CSI_REG_CSIHnCTL2(u32csi_base_adr) = 	0x0000E000;		/*slave, external clock*/
    CSI_REG_CSIHnMCTL0(u32csi_base_adr) =	0x00000001;  		/* FIFO mode */
	

	CSI_REG_CSIHnSTCR0(GetCSIBaseAddress(csi)) |= 0x100;
	while((CSI_REG_CSIHnSTR0(GetCSIBaseAddress(csi))& 0x00ff0030 ) != 0x00000010);
	CSI_REG_CSIHnMRWP0(u32csi_base_adr) = 0x00000000;
	CSI_REG_CSIHnMCTL1(u32csi_base_adr) |=	120 ;  		/* INTCSIHTIC 8 byte*/	
}

/***********************************************************************
*  Name        : CSI_StartDualBuffer
*  Description : start SPI dual buffer module
*  Parameter   : csi - csi channel
                 	   datalen - reserved		
                 	   bIsMaster - TRUE:master False:Slave
                 	   needFixDataLen:when set slave mode , need fix data len.
*  Returns     : None
***********************************************************************/
void CSI_StartDualBuffer(CSI_TYPE csi, U8 datalen,BOOL bIsMaster,U8 needFixDataLen)
{
    CSI_Start(csi, datalen);
    if (!bIsMaster)
    {
        CSI_FIFO_SendEmpty(csi,needFixDataLen);
    }
}

/***********************************************************************
*  Name        : CSI_StartFifo
*  Description : start SPI dual buffer module
*  Parameter   : csi - csi channel
                 	   datalen - reserved		
                 	   bIsMaster - TRUE:master False:Slave
                 	   needFixDataLen:when set slave mode , need fix data len.
*  Returns     : None
***********************************************************************/
void CSI_StartFifo(CSI_TYPE csi, U8 datalen,BOOL bIsMaster,U8 needFixDataLen)
{
    CSI_Start(csi, datalen);
	CSI_REG_CSIHnSTCR0(GetCSIBaseAddress(csi)) |= 0x100;
	while((CSI_REG_CSIHnSTR0(GetCSIBaseAddress(csi))& 0x00ff0030 ) != 0x00000010);
    if (!bIsMaster)
    {
        CSI_FIFO_SendEmpty(csi,needFixDataLen);
    }
}

/***********************************************************************
*  Name        : CSI_Send
*  Description : Send  data.
*  Parameter   : csi - csi channel
                       txbuf -  pointer to send data array
                       length - length of data to send/receive
*  Returns     : 
			   ERR_OK -operation ok
			   ERR_RANGE - length=0
***********************************************************************/
ERR_TYPE CSI_Send( CSI_TYPE csi,U8 *txbuf, U16 length)
{
    ERR_TYPE err_ret = ERR_OK;
    if (length < 1U) 
    {
        err_ret = ERR_RANGE;
    }
    else
    {
        CSI_Message[csi].CsiTxCnt = length; /* send data count */
        CSI_Message[csi].CsiTxAddress = txbuf; /* send buffer pointer */

        if ( CSI_REG_CSIHnCTL1(GetCSIBaseAddress(csi)) & CSIG_CTL1_EDLE_EXTENDED_ENABLE )
        {
            if (CSI_Message[csi].CsiTxEDLCnt>16U)
            {
                if(csi==CSIG_0)
                {
                    CSI_REG_CSIGnTX0W(GetCSIBaseAddress(csi))  = (CSIG_TX0W_EDL_EXTENDED | *CSI_Message[csi].CsiTxAddress); 
                }
                else
                {
                    CSI_REG_CSIHnTX0W(GetCSIBaseAddress(csi))  = (CSIG_TX0W_EDL_EXTENDED | *CSI_Message[csi].CsiTxAddress); 
                }
                /* start by writing data to CSIG0TX0W */
                CSI_Message[csi].CsiTxEDLCnt-=16U;
                CSI_Message[csi].CsiTxAddress++;
            }
            else
            {
                if(csi==CSIG_0)
                {
                    CSI_REG_CSIGnTX0W(GetCSIBaseAddress(csi))  = (CSIG_TX0W_EDL_NORMAL | *CSI_Message[csi].CsiTxAddress); 
                }
                else
                {
                    CSI_REG_CSIHnTX0W(GetCSIBaseAddress(csi))   = (CSIG_TX0W_EDL_NORMAL   | *CSI_Message[csi].CsiTxAddress); 
                }					
                /* start by writing data to CSIG0TX0W */
                CSI_Message[csi].CsiTxEDLCnt = 0U;
                CSI_Message[csi].CsiTxAddress++;
                CSI_Message[csi].CsiTxCnt--;
            }
        }
        else
        {
            if(csi==CSIG_0)
            {
                CSI_REG_CSIGnTX0H(GetCSIBaseAddress(csi))  =*CSI_Message[csi].CsiTxAddress;
            }
            else
            {
                CSI_REG_CSIHnTX0H(GetCSIBaseAddress(csi))=*CSI_Message[csi].CsiTxAddress;
            }
            /* start by writing data to CSIG0TX0H */
            CSI_Message[csi].CsiTxAddress++;
            CSI_Message[csi].CsiTxCnt--;
        }
    }
    return (err_ret);
}

/***********************************************************************
*  Name        : CSI_DualBuffer_Send
*  Description : Send  data in dual buffer mode.
*  Parameter   : csi - csi channel
                       txbuf -  pointer to send data array
                       length - length of data to send
*  Returns     : 
			   ERR_OK -operation ok
			   ERR_RANGE - length=0
			   ERR_BUSY - fifo is busy now,send data later.
***********************************************************************/
ERR_TYPE CSI_DualBuffer_Send( CSI_TYPE csi,U8 *txbuf, U16 length)
{
    ERR_TYPE err_ret = ERR_OK;
    U8 index=0;
    U32 u32csi_base_adr = GetCSIBaseAddress(csi);   

    /*
    First check CSIHnSTR0.CSIHntsF
    -0   idle state
    -1   Communication is in progress or being prepared;
    In this state,writing CSIHnMCTL2.CSIHnBTST ,CSIHnMCTL2.CSIHnBTST,CSIHnND.CSIHnSOP is not allowed.
    */
    if ((CSI_REG_CSIHnSTR0(u32csi_base_adr)&0x0080)) 
    {
        err_ret = ERR_BUSY;
    }
    else if((length>64)||(length<1))
    {
        err_ret = ERR_RANGE;
    }
    else
    {
        for(index=0;index<length;index++)
        {
            CSI_REG_CSIHnTX0H(u32csi_base_adr)=txbuf[index];
        }
        CSI_REG_CSIHnMCTL2(u32csi_base_adr) &=~ 0x00ff0000; 
        CSI_REG_CSIHnMCTL2(u32csi_base_adr) |= ((U32)length)<<16;          /*CSIHnND[7:0] 08H Specifies the number of data for each memory mode*/ 
        CSI_REG_CSIHnMCTL2(u32csi_base_adr) |=0x80000000;  /*CSIHnBTST: start transfer command.*/
    }

    return (err_ret);
}

/***********************************************************************
*  Name        : CSI_FIFO_Send
*  Description : Send  data in dual buffer mode.
*  Parameter   : csi - csi channel
                       txbuf -  pointer to send data array
                       length - length of data to send
*  Returns     : 
			   ERR_OK -operation ok
			   ERR_RANGE - length=0
			   ERR_BUSY - fifo is busy now,send data later.
***********************************************************************/
ERR_TYPE CSI_FIFO_Send( CSI_TYPE csi,U8 *txbuf, U16 length)
{
    ERR_TYPE err_ret = ERR_OK;
    U8 index=0;
    U32 u32csi_base_adr = GetCSIBaseAddress(csi);

	for(index=0;index<length;index++)
		CSI_REG_CSIHnTX0H(u32csi_base_adr)=txbuf[index];

    return (err_ret);
}

/***********************************************************************
*  Name        : CSI_DualBuffer_SendEmpty
*  Description : Send dummy data 0 in dual buffer mode.
*  Parameter   : csi - csi channel
                       length - length of data to send
*  Returns     : 
			   ERR_OK -operation ok
			   ERR_RANGE - length=0
			   ERR_BUSY - fifo is busy now,send data later.
***********************************************************************/
ERR_TYPE CSI_DualBuffer_SendEmpty(CSI_TYPE csi,U16 length)
{    
    U8 index = 0;
    U32 u32csi_base_adr = GetCSIBaseAddress(csi);   
    ERR_TYPE err_ret = ERR_OK;

    /*
    First check CSIHnSTR0.CSIHntsF
    -0   idle state
    -1   Communication is in progress or being prepared;
    In this state,writing CSIHnMCTL2.CSIHnBTST ,CSIHnMCTL2.CSIHnBTST,CSIHnND.CSIHnSOP is not allowed.
    */
    if ((CSI_REG_CSIHnSTR0(u32csi_base_adr)&0x0080)) 
    {
        err_ret = ERR_BUSY;
    }
    else if((length>64)||(length<1))
    {
        err_ret = ERR_RANGE;
    }
    else
    {    
        for(index=0;index<length;index++)
        {
            CSI_REG_CSIHnTX0H(u32csi_base_adr)=0;
        }
        CSI_REG_CSIHnMCTL2(u32csi_base_adr) &=~ 0x00ff0000; 
        CSI_REG_CSIHnMCTL2(u32csi_base_adr) |= ((U32)length)<<16;          /*CSIHnND[7:0] 08H Specifies the number of data for each memory mode*/ 
        CSI_REG_CSIHnMCTL2(u32csi_base_adr) |=0x80000000;  /*CSIHnBTST: start transfer command.*/
    }
    return (err_ret);
}

/***********************************************************************
*  Name        : CSI_FIFO_SendEmpty
*  Description : Send dummy data 0 in dual buffer mode.
*  Parameter   : csi - csi channel
                       length - length of data to send
*  Returns     : 
			   ERR_OK -operation ok
			   ERR_RANGE - length=0
			   ERR_BUSY - fifo is busy now,send data later.
***********************************************************************/
ERR_TYPE CSI_FIFO_SendEmpty(CSI_TYPE csi,U16 length)
{    
    ERR_TYPE err_ret = ERR_OK;
    U8 index=0;
    U32 u32csi_base_adr = GetCSIBaseAddress(csi);   
	
	for(index=0;index<length;index++)
		CSI_REG_CSIHnTX0H(u32csi_base_adr) = 0;

    return (err_ret);
}

/***********************************************************************
*  Name        : CSIH0_Tx_handler
*  Description : Tx hanlder for CSIH0
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIH0_Tx_handler(void)
{
    Tx_Handler(CSIH_0,TRUE);
}

/***********************************************************************
*  Name        : CSIH0_Rx_handler
*  Description : Rx hanlder for CSIH0
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIH0_Rx_handler(void)
{
    Rx_Handler(CSIH_0,TRUE);
}

/***********************************************************************
*  Name        : CSIH0_Error_handler
*  Description : Error hanlder for CSIH0
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIH0_Error_handler(void)
{
    Error_Handler(CSIH_0,TRUE);
}

/***********************************************************************
*  Name        : CSIH1_Tx_handler
*  Description : Tx hanlder for CSIH1
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIH1_Tx_handler(void)
{
    Tx_Handler(CSIH_1,FALSE);
}

/***********************************************************************
*  Name        : CSIH1_Rx_handler
*  Description : Rx hanlder for CSIH1
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIH1_Rx_handler(void)
{
    Rx_Handler(CSIH_1,FALSE);
}

/***********************************************************************
*  Name        : CSIH1_Error_handler
*  Description : Error hanlder for CSIH1
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIH1_Error_handler(void)
{
    Error_Handler(CSIH_1,FALSE);
}

/***********************************************************************
*  Name        : CSIH2_Tx_handler
*  Description : Tx hanlder for CSIH2
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIH2_Tx_handler(void)
{
    Tx_Handler(CSIH_2,FALSE);
}

/***********************************************************************
*  Name        : CSIH2_Rx_handler
*  Description : Rx hanlder for CSIH2
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIH2_Rx_handler(void)
{
    Rx_Handler(CSIH_2,FALSE);
}

/***********************************************************************
*  Name        : CSIH2_Error_handler
*  Description : Error hanlder for CSIH2
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIH2_Error_handler(void)
{
    Error_Handler(CSIH_2,FALSE);
}
/***********************************************************************
*  Name        : CSIH3_Tx_handler
*  Description : Tx hanlder for CSIH3
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIH3_Tx_handler(void)
{
    Tx_Handler(CSIH_3,FALSE);
}
/***********************************************************************
*  Name        : CSIH3_Rx_handler
*  Description : Rx hanlder for CSIH3
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIH3_Rx_handler(void)
{
    Rx_Handler(CSIH_3,FALSE);
}

/***********************************************************************
*  Name        : CSIH3_Error_handler
*  Description : Error hanlder for CSIH3
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIH3_Error_handler(void)
{
    Error_Handler(CSIH_3,FALSE);
}
/***********************************************************************
*  Name        : CSIG0_Tx_handler
*  Description : Tx hanlder for CSIG0
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIG0_Tx_handler(void)
{
    Tx_Handler(CSIG_0,FALSE);
}
/***********************************************************************
*  Name        : CSIG0_Rx_handler
*  Description : Rx hanlder for CSIG0
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIG0_Rx_handler(void)
{
    Rx_Handler(CSIG_0,FALSE);
}
/***********************************************************************
*  Name        : CSIG0_Error_handler
*  Description : Error hanlder for CSIG0
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void CSIG0_Error_handler(void)
{
    Error_Handler(CSIG_0,FALSE);
}

/***********************************************************************
*  Name        : Tx_Handler
*  Description : Transmit interrupt.
*  Parameter   : csi		- csi channel
                        bIsFIFO - TRUE:dual buffer mode FALSE:Normal transimit mode
*  Returns     : None
***********************************************************************/
STATIC void Tx_Handler( CSI_TYPE csi ,BOOL bIsFIFO)
{
    if(bIsFIFO)
    {
        /*nothing to do?*/
        if(NULL!=csi_tx_callback[csi])
            csi_tx_callback[csi]();  /* send complete */	
    }
    else
    {
        if (CSI_Message[csi].CsiTxCnt == 0U)
        {
            if(NULL!=csi_tx_callback[csi])
                csi_tx_callback[csi]();  /* send complete */
        }
        else
        {
            if (CSI_REG_CSIHnCTL1(GetCSIBaseAddress(csi)) & CSIG_CTL1_EDLE_EXTENDED_ENABLE)
            {
                if(CSI_Message[csi].CsiTxCnt>0u)
                {
                    if (CSI_Message[csi].CsiTxEDLCnt>16U)
                    {
                        if(csi==CSIG_0)
                        {
                            CSI_REG_CSIGnTX0W(GetCSIBaseAddress(csi))  = (CSIG_TX0W_EDL_EXTENDED | *CSI_Message[csi].CsiTxAddress);             
                        }
                        else
                        {
                            CSI_REG_CSIHnTX0W(GetCSIBaseAddress(csi))  = (CSIG_TX0W_EDL_EXTENDED | *CSI_Message[csi].CsiTxAddress);             
                        }
                        /* start by writing data to CSIG0TX0W */ 
                        CSI_Message[csi].CsiTxEDLCnt-=16U;
                        CSI_Message[csi].CsiTxAddress++;
                    }
                    else
                    {
                        if(csi==CSIG_0)
                        {
                            CSI_REG_CSIGnTX0W(GetCSIBaseAddress(csi))  = (CSIG_TX0W_EDL_EXTENDED | *CSI_Message[csi].CsiTxAddress);             
                        }
                        else
                        {
                            CSI_REG_CSIHnTX0W(GetCSIBaseAddress(csi))   = (CSIG_TX0W_EDL_NORMAL   | *CSI_Message[csi].CsiTxAddress); 
                        }			
                        /* start by writing data to CSIG0TX0W */
                        CSI_Message[csi].CsiTxEDLCnt = 0U;
                        CSI_Message[csi].CsiTxAddress++;
                        CSI_Message[csi].CsiTxCnt--;
                    }
                }
            }
            else
            {
                if (CSI_Message[csi].CsiTxCnt> 0U)
                {
                    if(csi==CSIG_0)
                    {
                        CSI_REG_CSIGnTX0H(GetCSIBaseAddress(csi))  =*CSI_Message[csi].CsiTxAddress;
                    }
                    else
                    {		   	
                        CSI_REG_CSIHnTX0H(GetCSIBaseAddress(csi))=(U8)(*CSI_Message[csi].CsiTxAddress & 0x00FFu);
                    }
                    /* start by writing data to CSIG0TX0H */
                    CSI_Message[csi].CsiTxAddress++;
                    CSI_Message[csi].CsiTxCnt--;	    
                }
            }
        }
    }
}

/***********************************************************************
*  Name        : Rx_Handler
*  Description : receive data.		  
*  Parameter   : csi		- csi channel
                        bIsFIFO - TRUE:dual buffer mode FALSE:Normal transimit mode
*  Returns     : None
***********************************************************************/
STATIC void Rx_Handler( CSI_TYPE csi ,BOOL bIsFIFO)
{
    U8 index=0u;
    U16 rec_byte=0u;

    if(bIsFIFO)
    {
        const U8 recnum = 8;
        for(index=0;index<recnum;index++)
        {
            RxData[index] =  CSI_REG_CSIHnRX0H(GetCSIBaseAddress(csi));
        }
        if(NULL!= csi_rx_byte_callback[csi])
            csi_rx_byte_callback[csi]((void*)RxData); 	   /* handler for every received byte, add for scenario with undefined Rx number */      
    }
    else
    {
        if(csi==CSIG_0)
        {		
            rec_byte = CSI_REG_CSIGnRX0(GetCSIBaseAddress(csi));		
        }
        else
        {
            rec_byte = CSI_REG_CSIHnRX0H(GetCSIBaseAddress(csi));
        }    
        if(NULL!= csi_rx_byte_callback[csi])
            csi_rx_byte_callback[csi]((void*)&rec_byte); 	   /* handler for every received byte, add for scenario with undefined Rx number*/
    }
}

/***********************************************************************
*  Name        : Error_Handler
*  Description : SPI error handling, data consistency/ parity / overrun...
*  Parameter   : csi - csi channel
                        bIsFIFO - TRUE:dual buffer mode FALSE:Normal transimit mode
*  Returns     : None
***********************************************************************/
STATIC void Error_Handler(CSI_TYPE csi ,BOOL bIsFIFO)
{
    U8 err_type=0;

    err_type = (U8)(CSI_REG_CSIHnSTR0(GetCSIBaseAddress(csi)) & (CSIG_STCR0_DCEC|CSIG_STCR0_PEC|CSIG_STCR0_OVEC));

    if(NULL!=csi_error_callback[csi])
        csi_error_callback[csi](err_type);  	
    /* clear error*/	
    CSI_REG_CSIHnSTCR0(GetCSIBaseAddress(csi)) = (CSIG_STCR0_DCEC|CSIG_STCR0_PEC|CSIG_STCR0_OVEC);
}


/***********************************************************************
*  Name        : GetCSIIRQNumber
*  Description : get interrupt channel ID
*  Parameter   : csi - csi channel
*  Returns     : None
***********************************************************************/
STATIC U16 GetCSIIRQNumber(CSI_TYPE csi)
{
    U16 IrqNo =0u;

    if(csi==CSIH_0)
    {
        IrqNo=INTCSIH0IC;
    }
    else if(csi==CSIH_1)
    {
        IrqNo=INTCSIH1IC;
    }  
    else if(csi==CSIH_2)
    {
        IrqNo=INTCSIH2IC;
    }   
    else if(csi==CSIH_3)
    {
        IrqNo=INTCSIH3IC;
    }   
    else if(csi==CSIG_0)
    {
        IrqNo=INTCSIG0IC;
    }
    return IrqNo;  
}

/***********************************************************************
*  Name        : GetCSIBaseAddress
*  Description : get register base address
*  Parameter   : csi - csi channel
*  Returns     : 
			  register base address
***********************************************************************/
STATIC CPU_INT32U GetCSIBaseAddress(CSI_TYPE csi)
{
    CPU_INT32U addressbase=0u;

    switch(csi)
    {
        case CSIH_0:
            addressbase=CSIH0_REG_BASEADD;
        break;
        
        case CSIH_1:
            addressbase=CSIH1_REG_BASEADD;
        break;
        
        case CSIH_2:
            addressbase=CSIH2_REG_BASEADD;
        break;
        
        case CSIH_3:
            addressbase=CSIH3_REG_BASEADD;
        break;
        
        case CSIG_0:
            addressbase=CSIG0_REG_BASEADD;
        break;
        
        default:break;
    }
    return addressbase;
}


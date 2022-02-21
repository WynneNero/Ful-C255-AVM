/*  BEGIN_FILE_HDR
************************************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information contained in this 
*   doc should not be reproduced, or used, or disclosed without the written authorization from 
*   HiRain Technologies.
************************************************************************************************
*   File Name       : SPI.c
************************************************************************************************
*   Project/Product : All
*   Title           : SPI module source File
*   Author          : ning.chen
************************************************************************************************
*   Description     : 
*
************************************************************************************************
*   Limitations     : mpc5604
*
************************************************************************************************
*
************************************************************************************************
*   Revision History:
* 
*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   1.0         2011/08/09    ning.chen     N/A          Original
*
************************************************************************************************
* END_FILE_HDR*/
#include "bl_spi.h"

/*********************************************************************************************************************
 MCR REGISTER CONFIG                               															
*********************************************************************************************************************/
/* MDIS */
void SPI_ModuleEn(bl_u8_t ModuleNum)
{
  DSPI_MCR(ModuleNum) &= (~DSPI_MCR_MDIS_MASK);	
}
void SPI_ModuleDis(bl_u8_t ModuleNum)
{
  DSPI_MCR(ModuleNum) |= DSPI_MCR_MDIS_MASK;	
}
/* HALT */
void SPI_ModuleRunning(bl_u8_t ModuleNum)
{
  DSPI_MCR(ModuleNum) &= (~DSPI_MCR_HALT_MASK);	
}
void SPI_ModuleStop(bl_u8_t ModuleNum)
{
  DSPI_MCR(ModuleNum) |= DSPI_MCR_HALT_MASK;	
}
/* MSTR */
void SPI_NodeModeSet(bl_u8_t ModuleNum,bl_u8_t nodeMode)
{
  if(nodeMode == SPI_NODE_MASTER)
    {
        DSPI_MCR(ModuleNum) |= DSPI_MCR_MSTR_MASK; 
    }
    else
    {
        DSPI_MCR(ModuleNum) &= (~DSPI_MCR_MSTR_MASK);
    } 	
}
/* CONT_SCKE  */
void SPI_ContSCKEn(bl_u8_t ModuleNum)
{
	DSPI_MCR(ModuleNum) |= DSPI_MCR_CONT_SCKE_MASK;	
}
void SPI_ContSCKDis(bl_u8_t ModuleNum)
{
	DSPI_MCR(ModuleNum) &= (~DSPI_MCR_CONT_SCKE_MASK);	
}
/* FRZ */
void SPI_FRZEn(bl_u8_t ModuleNum)
{
	DSPI_MCR(ModuleNum) |= DSPI_MCR_FRZ_MASK;	
}
void SPI_FRZDis(bl_u8_t ModuleNum)
{
	DSPI_MCR(ModuleNum) &= (~DSPI_MCR_FRZ_MASK);	
}
/* MTFE */
void SPI_MTFEn(bl_u8_t ModuleNum)
{
	DSPI_MCR(ModuleNum) |= DSPI_MCR_MTFE_MASK;	
}
void SPI_MTFDis(bl_u8_t ModuleNum)
{
	DSPI_MCR(ModuleNum) &= (~DSPI_MCR_MTFE_MASK);	
}
/* PCSSE */
void SPI_PCSSEn(bl_u8_t ModuleNum)
{
	DSPI_MCR(ModuleNum) |= DSPI_MCR_PCSSE_MASK;	
}
void SPI_PCSSDis(bl_u8_t ModuleNum)
{
	DSPI_MCR(ModuleNum) &= (~DSPI_MCR_PCSSE_MASK);	
}
/* ROOE */
void SPI_ROOEn(bl_u8_t ModuleNum)
{
	DSPI_MCR(ModuleNum) |= DSPI_MCR_ROOE_MASK;	
}
void SPI_ROODis(bl_u8_t ModuleNum)
{
	DSPI_MCR(ModuleNum) &= (~DSPI_MCR_ROOE_MASK);	
}
/* PCSISn value -only bit0-bit5 is active bitx-csx */
void SPI_SetCS_Active_State(bl_u8_t ModuleNum, bl_u8_t value)
{
    bl_u32_t tem = value;
	DSPI_MCR(ModuleNum) &= (~DSPI_MCR_PCSIS_MASK);
	DSPI_MCR(ModuleNum) |= (tem<<16);	
}
/* SMPL_PT value -0,1,2  */
void SPI_SetSamplePoint(bl_u8_t ModuleNum, bl_u8_t value)
{
    bl_u32_t tem = value;
	DSPI_MCR(ModuleNum) &= (~DSPI_MCR_SMPL_PT_MASK);
	DSPI_MCR(ModuleNum) |= (tem<<8);	
}
/* FIFO related set  */
void SPI_TxFIFODis(bl_u8_t ModuleNum)
{
   DSPI_MCR(ModuleNum) |= (DSPI_MCR_DIS_TXF_MASK);	
}
void SPI_TxFIFOEn(bl_u8_t ModuleNum)
{
   DSPI_MCR(ModuleNum) &= (~DSPI_MCR_DIS_TXF_MASK);	
}
void SPI_RxFIFODis(bl_u8_t ModuleNum)
{
   DSPI_MCR(ModuleNum) |= (DSPI_MCR_DIS_RXF_MASK);	
}
void SPI_RxFIFOEn(bl_u8_t ModuleNum)
{
   DSPI_MCR(ModuleNum) &= (~DSPI_MCR_DIS_RXF_MASK);	
}

void SPI_RxFIFOClr(bl_u8_t ModuleNum)
{
   DSPI_MCR(ModuleNum) |= (DSPI_MCR_CLR_RXF_MASK);	
}

void SPI_TxFIFOClr(bl_u8_t ModuleNum)
{
   DSPI_MCR(ModuleNum) |= (DSPI_MCR_CLR_TXF_MASK);	
}
/*********************************************************************************************************************
 CTAR REGISTER CONFIG
*********************************************************************************************************************/
/* FMSZ */
void  SPI_TransferWidth(bl_u8_t ModuleNum, bl_u8_t ChannelNum, bl_u8_t Width)
{
   bl_u32_t  tem = Width;
   DSPI_CTAR(ModuleNum,ChannelNum) &= (~DSPI_CTAR_FMSZ_MASK);
   DSPI_CTAR(ModuleNum,ChannelNum) |= (tem<<27u);
}
/* LSBFE */
void SPI_LSBFESet(bl_u8_t ModuleNum,bl_u8_t ChannelNum,bl_u8_t lsbfe)
{
   if(lsbfe == SPI_SYS_FIRST_SHIFT_MSB)	
   {
   	 DSPI_CTAR(ModuleNum,ChannelNum) &= (~DSPI_CTAR_LSBFE_MASK);
   }
   else
   {
   	 DSPI_CTAR(ModuleNum,ChannelNum) |= (DSPI_CTAR_LSBFE_MASK);
   }
}
/* CPOL */
void SPI_CPOLSet(bl_u8_t ModuleNum,bl_u8_t ChannelNum,bl_u8_t cpol)
{
   if(cpol == SPI_SCK_POLARITY_LOW)	
   {
   	 DSPI_CTAR(ModuleNum,ChannelNum) &= (~DSPI_CTAR_CPOL_MASK);
   }
   else
   {
   	 DSPI_CTAR(ModuleNum,ChannelNum) |= (DSPI_CTAR_CPOL_MASK);
   }
}
/* CPHA */
void SPI_CPHASet(bl_u8_t ModuleNum,bl_u8_t ChannelNum,bl_u8_t cpha)
{
   if(cpha == SPI_SCK_PHASE_EVEN)	
   {
   	 DSPI_CTAR(ModuleNum,ChannelNum) &= (~DSPI_CTAR_CPHA_MASK);
   }
   else
   {
   	 DSPI_CTAR(ModuleNum,ChannelNum) |= (DSPI_CTAR_CPHA_MASK);
   }
}
/* 
DBR PBR BR  
BaundRate = (Fbus*(1+DBR)) /(PBR*BR)
*/
void SPI_BaudRateSet(bl_u8_t ModuleNum,bl_u8_t ChannelNum,bl_u8_t dbr,bl_u8_t pbr,bl_u8_t br)
{
   bl_u32_t tem1 = dbr;
   bl_u32_t tem2 = pbr;
   tem1 = (tem1<<31)|(tem2<<16)|(br);
   DSPI_CTAR(ModuleNum,ChannelNum) &=(~(DSPI_CTAR_DBR_MASK|DSPI_CTAR_PBR_MASK|DSPI_CTAR_BR_MASK));
   DSPI_CTAR(ModuleNum,ChannelNum) |=(tem1);	
}
/* 
PCSSCK PASC PDT CSSCK ASC DT
SET delay parameters
*/
void SPI_DelaySet(bl_u8_t ModuleNum,bl_u8_t ChannelNum,bl_u32_t value)
{
   DSPI_CTAR(ModuleNum,ChannelNum) &=(~DSPI_CTAR_DELAY_MASK);
   DSPI_CTAR(ModuleNum,ChannelNum) |=(value&DSPI_CTAR_DELAY_MASK);	
}

/*********************************************************************************************************************
 RSER REGISTER CONFIG
*********************************************************************************************************************/
void SPI_IntEn(bl_u8_t ModuleNum, bl_u8_t intSource)
{
  switch(intSource)
  {
  	case SPI_TCF:
  	 DSPI_RSER(ModuleNum) |= DSPI_RSER_TCF_MASK;
  	break;
  	case SPI_EOQF:
  	 DSPI_RSER(ModuleNum) |= DSPI_RSER_EOQF_MASK;
  	break;
  	case SPI_TFUF:
  	 DSPI_RSER(ModuleNum) |= DSPI_RSER_TFUF_MASK;
  	break;
  	case SPI_TFFF_INT:
  	 DSPI_RSER(ModuleNum) |= DSPI_RSER_TFFF_MASK;
  	 DSPI_RSER(ModuleNum) &= (~DSPI_RSER_TFFFDIR_MASK);
  	break;
  	case SPI_TFFF_DMA:
  	 DSPI_RSER(ModuleNum) |= DSPI_RSER_TFFF_MASK;
  	 DSPI_RSER(ModuleNum) |= (DSPI_RSER_TFFFDIR_MASK);
  	break;
  	case SPI_RFOF:
  	 DSPI_RSER(ModuleNum) |= DSPI_RSER_RFOF_MASK;
  	break;
  	case SPI_RFDF_INT:
  	 DSPI_RSER(ModuleNum) |= DSPI_RSER_RFRD_MASK;
  	 DSPI_RSER(ModuleNum) &= (~DSPI_RSER_RFRDDIR_MASK);
  	break;
  	case SPI_RFDF_DMA:
  	 DSPI_RSER(ModuleNum) |= DSPI_RSER_RFRD_MASK;
  	 DSPI_RSER(ModuleNum) |= (DSPI_RSER_RFRDDIR_MASK);
  	break;
  	default:
  	break;
  }
}

void SPI_IntDis(bl_u8_t ModuleNum, bl_u8_t intSource)
{
  switch(intSource)
  {
  	case SPI_TCF:
  	 DSPI_RSER(ModuleNum) &= (~DSPI_RSER_TCF_MASK);
  	break;
  	case SPI_EOQF:
  	 DSPI_RSER(ModuleNum) &= (~DSPI_RSER_EOQF_MASK);
  	break;
  	case SPI_TFUF:
  	 DSPI_RSER(ModuleNum) &= (~DSPI_RSER_TFUF_MASK);
  	break;
  	case SPI_TFFF_INT:
  	 DSPI_RSER(ModuleNum) &= (~DSPI_RSER_TFFF_MASK);
  	break;
  	case SPI_TFFF_DMA:
  	 DSPI_RSER(ModuleNum) &= (~DSPI_RSER_TFFF_MASK);
  	break;
  	case SPI_RFOF:
  	 DSPI_RSER(ModuleNum) &= (~DSPI_RSER_RFOF_MASK);
  	break;
  	case SPI_RFDF_INT:
  	 DSPI_RSER(ModuleNum) &= (~DSPI_RSER_RFRD_MASK);
  	break;
  	case SPI_RFDF_DMA:
  	 DSPI_RSER(ModuleNum) &= (~DSPI_RSER_RFRD_MASK);
  	break;
  	default:
  	break;
  }	
}


/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : SPI_ByteRx
*
* Description   : Transmit one byte to SPI bus.
*
* Inputs        : bl_u8_t moduleNum :Module number(0 ~ SPI_MODULE_NUM-1)
*                 bl_u8_t *pRxData  :The pointer which the received byte store to.
*
* Outputs       : None
* 
* Limitations   : 1.Only using the S12SPIV5 module
*                 2.Using inside this module
*                 
************************************************************************************************
END_FUNCTION_HDR */
static bl_Return_t SPI_ByteRx(bl_u8_t moduleNum,bl_u8_t ChannelNum, bl_u8_t *pRxData)
{    
    bl_Return_t ret = BL_ERR_OK;

    ret = OverTimeCheckLong(DSPI_SR_P(moduleNum), DSPI_SR_RFRD_MASK, DSPI_SR_RFRD_MASK, DSPI_DELAY);
    if(BL_ERR_OK == ret)
    {
        *pRxData = (bl_u8_t)DSPI_POPR(moduleNum);
        DSPI_SR(moduleNum) = DSPI_SR_RFRD_MASK|DSPI_SR_TCF_MASK|DSPI_RSER_EOQF_MASK;
    }
    else
    {
        ret = BL_ERR_NOT_OK;
    }

    return ret;
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : SPI_ByteTx
*
* Description   : Transmit one byte to SPI bus.
*
* Inputs        : bl_u8_t moduleNum :Module number(0 ~ SPI_MODULE_NUM-1)
*                 bl_u8_t txData    :The byte you want to transmit.
*
* Outputs       : None
* 
* Limitations   : 1.Only using the S12SPIV5 module
*                 2.Using inside this module
*                 
************************************************************************************************
END_FUNCTION_HDR */
static bl_Return_t SPI_ByteTx(bl_u8_t moduleNum,bl_u8_t ChannelNum, bl_u8_t txData)
{
    bl_Return_t ret = BL_ERR_OK;

    ret = OverTimeCheckLong(DSPI_SR_P(moduleNum), DSPI_SR_TFFF_MASK, DSPI_SR_TFFF_MASK, DSPI_DELAY);
    
    if(BL_ERR_OK == ret)
    {
    #if(SPI_TXFIFO_EN == SPI_OFF)
        SPI_TxFIFOClr(DSPI1);
    #endif
        if(ChannelNum == CTAR0)
        {
        	DSPI_PUSHR(moduleNum) = txData|DSPI_CTAR0_SINGLE_DATA_TRANSMIT;
        }
        else if(ChannelNum == CTAR1)
        {
        	DSPI_PUSHR(moduleNum) = txData|DSPI_CTAR1_SINGLE_DATA_TRANSMIT;
        }
        else
        {
        	
        }
       
        if(BL_ERR_OK == OverTimeCheckLong(DSPI_SR_P(moduleNum), DSPI_SR_TCF_MASK, DSPI_SR_TCF_MASK, DSPI_DELAY))
        {
        	DSPI_SR(moduleNum) = DSPI_SR_TCF_MASK;
        }
        else
        {
        	ret = BL_ERR_NOT_OK;	
        }

    }
    else
    {
        ret = BL_ERR_NOT_OK;
    }
    return ret;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : SPI_DataTxRx8
*
* Description   : Transmit and receive one byte.
*
* Inputs        : bl_u8_t moduleNum :Module number(0 ~ SPI_MODULE_NUM-1)
*                 bl_u8_t txData    :The byte you want to transmit.
*                 bl_u8_t *pRxData  :The pointer which the received byte store to.
*
* Outputs       : None
* 
* Limitations   : 1.Only using the S12SPIV5 module
*                 
************************************************************************************************
END_FUNCTION_HDR */
bl_Return_t SPI_DataTxRx8(bl_u8_t moduleNum,bl_u8_t ChannelNum, bl_u8_t txData, bl_u8_t *pRxData)
{ 
    bl_Return_t ret = BL_ERR_OK;
    bl_u8_t idlePointer;
    
    if(pRxData == DSPI_NULL)
    {
        pRxData = &idlePointer; 
    }
    
    if(SPI_ByteTx(moduleNum, ChannelNum, txData) == BL_ERR_OK)
    {
        if(SPI_ByteRx(moduleNum, ChannelNum, pRxData) == BL_ERR_OK)                      
        {
            ret = BL_ERR_OK;
        }
        else
        {
            ret = BL_ERR_NOT_OK;
        }
    }
    else
    {
        ret = BL_ERR_NOT_OK;
    }
    return ret;
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : SPI_DataTx8
*
* Description   : Transmit one byte.
*
* Inputs        : bl_u8_t moduleNum :Module number(0 ~ SPI_MODULE_NUM-1)
*                 bl_u8_t txData    :The byte you want to transmit.
*
* Outputs       : None
* 
* Limitations   : 1.Only using the S12SPIV5 module
*                 
************************************************************************************************
END_FUNCTION_HDR */
bl_Return_t SPI_DataTx8(bl_u8_t moduleNum,bl_u8_t ChannelNum, bl_u8_t txData)
{
    return(SPI_DataTxRx8(moduleNum, ChannelNum, txData, DSPI_NULL));
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : SPI_DataRx8
*
* Description   : Receive one byte.
*
* Inputs        : bl_u8_t moduleNum :Module number(0 ~ SPI_MODULE_NUM-1)
*                 bl_u8_t pRxData   :The pointer which the received byte store to.
*
* Outputs       : None
* 
* Limitations   : 1.Only using the S12SPIV5 module
*                 
************************************************************************************************
END_FUNCTION_HDR */
bl_Return_t SPI_DataRx8(bl_u8_t moduleNum,bl_u8_t ChannelNum, bl_u8_t *pRxData)
{
    return(SPI_DataTxRx8(moduleNum,ChannelNum, DSPI_DUMMY_DATA, pRxData));
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : SPI_DataTxRx8_N
*
* Description   : Transmit and receive N bytes.
*
* Inputs        : bl_u8_t moduleNum :Module number(0 ~ SPI_MODULE_NUM-1)
*                 bl_u8_t txData    :The byte you want to transmit.
*                 bl_u8_t *pRxData  :The pointer which the received byte store to.
*                 bl_u16_t len      :Length of data 
*
* Outputs       : None
* 
* Limitations   : 1.Only using the S12SPIV5 module
*                 
************************************************************************************************
END_FUNCTION_HDR */
bl_Return_t SPI_DataTxRx8_N(bl_u8_t moduleNum,bl_u8_t ChannelNum, bl_u8_t *pTxData, bl_u8_t *pRxData, bl_u16_t len)
{ 
    bl_Return_t ret = BL_ERR_OK;
    
    while((len > 0) && (ret == BL_ERR_OK))
    {
        ret = SPI_DataTxRx8(moduleNum,ChannelNum, *pTxData, pRxData);
        
        if(ret == BL_ERR_OK)
        {
            pTxData++;
            pRxData++;
        }

        len--;  
    }
    
    return ret;
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : SPI_WordRx
*
* Description   : Transmit one word to SPI bus.
*
* Inputs        : bl_u8_t moduleNum :Module number(0 ~ SPI_MODULE_NUM-1)
*                 bl_u8_t *pRxData  :The pointer which the received word store to.
*
* Outputs       : None
* 
* Limitations   : 1.Only using the S12SPIV5 module
*                 2.Using inside this module
*                 
************************************************************************************************
END_FUNCTION_HDR */
static bl_Return_t SPI_WordRx(bl_u8_t moduleNum,bl_u8_t ChannelNum, bl_u16_t *pRxData)
{    
    bl_Return_t ret = BL_ERR_OK;

    ret = OverTimeCheckLong(DSPI_SR_P(moduleNum), DSPI_SR_RFRD_MASK, DSPI_SR_RFRD_MASK, DSPI_DELAY);
    
    if(BL_ERR_OK == ret)
    {
        *pRxData = (bl_u16_t)DSPI_POPR(moduleNum);
        DSPI_SR(moduleNum) = DSPI_SR_RFRD_MASK|DSPI_SR_TCF_MASK|DSPI_RSER_EOQF_MASK;

    }
    else
    {
        ret = BL_ERR_NOT_OK;
    }

    return ret;
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : SPI_WordTx
*
* Description   : Transmit one word to SPI bus.
*
* Inputs        : bl_u8_t moduleNum :Module number(0 ~ SPI_MODULE_NUM-1)
*                 bl_u8_t txData    :The word you want to transmit.
*
* Outputs       : None
* 
* Limitations   : 1.Only using the S12SPIV5 module
*                 2.Using inside this module
*                 
************************************************************************************************
END_FUNCTION_HDR */
static bl_Return_t SPI_WordTx(bl_u8_t moduleNum,bl_u8_t ChannelNum, bl_u16_t txData)
{
    bl_Return_t ret = BL_ERR_OK;

    ret = OverTimeCheckLong(DSPI_SR_P(moduleNum), DSPI_SR_TFFF_MASK, DSPI_SR_TFFF_MASK, DSPI_DELAY);
    
    if(ret == BL_ERR_OK)
    {
        
        if(ChannelNum == CTAR0)
        {
        	DSPI_PUSHR(moduleNum) = txData|DSPI_CTAR0_SINGLE_DATA_TRANSMIT;
        }
        else if(ChannelNum == CTAR1)
        {
        	DSPI_PUSHR(moduleNum) = txData|DSPI_CTAR1_SINGLE_DATA_TRANSMIT;
        }
        else
        {
        	
        }
        if(BL_ERR_OK == OverTimeCheckLong(DSPI_SR_P(moduleNum), DSPI_SR_TCF_MASK, DSPI_SR_TCF_MASK, DSPI_DELAY))
        {
        	DSPI_SR(moduleNum) = DSPI_SR_TCF_MASK;
        }
        else
        {
        	ret = BL_ERR_NOT_OK;	
        }

    }
    else
    {
        ret = BL_ERR_NOT_OK;
    }
    
    return ret;
}


/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : SPI_DataTxRx16
*
* Description   : Transmit and receive one word.
*
* Inputs        : bl_u8_t moduleNum :Module number(0 ~ SPI_MODULE_NUM-1)
*                 bl_u16_t txData   :The word you want to transmit.
*                 bl_u16_t *pRxData :The pointer which the received word store to.
*
* Outputs       : None
* 
* Limitations   : 1.Only using the S12SPIV5 module
*                 
************************************************************************************************
END_FUNCTION_HDR*/ 
bl_Return_t SPI_DataTxRx16(bl_u8_t moduleNum,bl_u8_t ChannelNum, bl_u16_t txData, bl_u16_t *pRxData)
{
    bl_Return_t ret = BL_ERR_OK;
    bl_u16_t idlePointer;
    
    if(pRxData == DSPI_NULL)
    {
        pRxData = &idlePointer; 
    }
    
    if(SPI_WordTx(moduleNum, ChannelNum, txData) == BL_ERR_OK)
    {
        if(SPI_WordRx(moduleNum, ChannelNum, pRxData) == BL_ERR_OK)                      
        {
            ret = BL_ERR_OK;
        }
        else
        {
            ret = BL_ERR_NOT_OK;
        }
    }
    else
    {
        ret = BL_ERR_NOT_OK;
    }
    
    return ret;
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : SPI_DataTx16
*
* Description   : Transmit one word.
*
* Inputs        : bl_u8_t moduleNum :Module number(0 ~ SPI_MODULE_NUM-1)
*                 bl_u16_t txData   :The word you want to transmit.
*
* Outputs       : None
* 
* Limitations   : 1.Only using the S12SPIV5 module
*                 
************************************************************************************************
END_FUNCTION_HDR */
bl_Return_t SPI_DataTx16(bl_u8_t moduleNum,bl_u8_t ChannelNum, bl_u16_t tData)
{  
    return (SPI_DataTxRx16(moduleNum, ChannelNum, tData, DSPI_NULL));
}


/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : SPI_DataRx16
*
* Description   : Receive one word.
*
* Inputs        : bl_u8_t moduleNum :Module number(0 ~ SPI_MODULE_NUM-1)
*                 bl_u16_t pRxData  :The pointer which the received word store to.
*
* Outputs       : None
* 
* Limitations   : 1.Only using the S12SPIV5 module
*                 
************************************************************************************************
END_FUNCTION_HDR */
bl_Return_t SPI_DataRx16(bl_u8_t moduleNum,bl_u8_t ChannelNum, bl_u16_t *pRxData)
{   
    return (SPI_DataTxRx16(moduleNum, ChannelNum,DSPI_DUMMY_DATA, pRxData));
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : SPI_DataTxRx16_N
*
* Description   : Transmit and receive N words.
*
* Inputs        : bl_u8_t moduleNum :Module number(0 ~ SPI_MODULE_NUM-1)
*                 bl_u16_t txData   :The word you want to transmit.
*                 bl_u16_t *pRxData :The pointer which the received word store to.
*                 bl_u16_t len      :Length of data 
*
* Outputs       : None
* 
* Limitations   : 1.Only using the S12SPIV5 module
*                 
************************************************************************************************
END_FUNCTION_HDR */
bl_Return_t SPI_DataTxRx16_N(bl_u8_t moduleNum,bl_u8_t ChannelNum, bl_u16_t *pTxData, bl_u16_t *pRxData, bl_u16_t len)
{ 
    bl_Return_t ret = BL_ERR_OK;
    
    while((len > 0) && (ret == BL_ERR_OK))
    {
        ret = SPI_DataTxRx16(moduleNum, ChannelNum, *pTxData, pRxData);
        if(ret == BL_ERR_OK)
        {
            pTxData++;
            pRxData++;
        }

        len--; 
    }
    return ret;
}

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : SPI_TxConfig
*
* Description   : set transmit parameter before send data
*
* Inputs        : bl_u8_t moduleNum :Module number(0 ~ SPI_MODULE_NUM-1)
*                 bl_u8_t CTAS   :select the used CTAS (0-5)
*                 bl_u8_t CS :	  select the used cs pin 
* Outputs       : None
* 
* Limitations   : 1.Only using the MPC5604B DSPI module; the CONT = 0,EOQ=0,CTCNT = 0 (default value,if needed ,Open the related configration)
*                 mast be called before every transmit;if not use auto cs ,CS must be cs_null
************************************************************************************************
END_FUNCTION_HDR */
void SPI_TxConfig(bl_u8_t moduleNum,bl_u8_t CS,bl_u8_t CTAS)
{
    bl_u16_t tem = CTAS;
    //DSPI_PUSHR_H(moduleNum) &= (~DSPI_PUSHR_H_PCS_MASK);
	DSPI_PUSHR_H(moduleNum) = ((tem<<(bl_u8_t)12)|CS);
}


/*********************************************************************************************************************
 SLAVE COMM                               															
*********************************************************************************************************************/








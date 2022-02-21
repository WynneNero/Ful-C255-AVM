/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the source file of the can module.
 *
 *  \file       bl_can.c
 *  \ingroup    driver_module
 *  \author     lele.liu <lele.liu@hirain.com>
 *
 *  \version    1.0.0
 *  \date       12/01/2016
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | -------------
 *      01.00.00 | 28/01/2016 | lele.liu         | N/A | BootDrv010001
 *
 *****************************************************************************/

/*******************************************************************************
*   Includes 
*******************************************************************************/ 
#include "bl_can.h" 

#define protected_write(preg,pstatus,reg,value)   do{\
                                                  (preg)=0xa5u;\
                                                  (reg)=(value);\
                                                  (reg)=~(value);\
                                                  (reg)=(value);\
                                                  }while((pstatus)==1u)




can_cre_type RX_RULE_TABLE_LIST1[CAN_RX_NUMBER] = 
{
    /* CAN  reception rules */

    {RSCFD0CFDGAFLIDj_RULE0_VALUE, 0xDFFFFFFFUL, 0xF0000000UL, 0x00000001UL}, /* NO.000 : std data frm ID = H'10 will be accepted, 8 data length, destination Rx Buffer0 */
    {RSCFD0CFDGAFLIDj_RULE1_VALUE, 0xDFFFFFFFUL, 0xF0000000UL, 0x00000002UL}, /* NO.001 : std data frm ID = H'20 will be accepted, destination Rx Buffer1 */
    //{0x00000030UL, 0xDFFFFFF0UL, 0xD0008000UL, 0x00000000UL}, /* NO.002 : std data frm ID = H'30~3F will be accepted, destination Rx Buffer2 */
    //{0x00000040UL, 0xDFFFFFF0UL, 0xC0008100UL, 0x00000000UL}, /* NO.003 : std data frm ID = H'40~4F will be accepted, destination Rx Buffer3 */
    //{0x00000050UL, 0xDFFFFFFFUL, 0xB0008200UL, 0x00000000UL}, /* NO.004 : std data frm ID = H'50 will be accepted, destination Rx Buffer4 */
    //{0x00000060UL, 0xDFFFFFFFUL, 0xB0008300UL, 0x00000000UL}, /* NO.005 : std data frm ID = H'60 will be accepted, destination Rx Buffer5 */
    //{0x00000070UL, 0xDFFFFFFFUL, 0xB0008400UL, 0x00000000UL}, /* NO.006 : std data frm ID = H'70 will be accepted, destination Rx Buffer6 */
    //{0x00000080UL, 0xDFFFFFFFUL, 0xB0008500UL, 0x00000000UL}, /* NO.007 : std data frm ID = H'80 will be accepted, destination Rx Buffer7 */
  
};

can_cre_type RX_RULE_TABLE_LIST0[CAN_RX_NUMBER] = 
{
    /* CAN reset  reception rules */

    {0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL}, 
    {0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL}, 
      
};


Can_FrameType CANFD_TraTempData=
{
  0x0,            /* ID */
  0,
  0,
  0,
   
  0x0000,                            
  0x00,
  0x0,
  0x0,             /* DLC */
  
  {0}            /* data */
};


/****************************************************************************
* FUNCTION :    CANMemCpy                                            
*                                                                             
* DESCRIPTION : This function is used to copy data                                                                            
* CALLS :                                                                                                                                         
* INPUTS :      --dest: destination address
*               --source: source address
*               --size: the number of data to copy 
* OUTPUTS       none                                                                                                          
*****************************************************************************/
void CANMemCpy(bl_u8_t* dest, bl_u8_t* source, bl_u32_t size)
{
    
    volatile bl_u8_t* sd  = dest;
    volatile bl_u8_t* ss  = source;

    while (size > 0)
    {
        *sd++ = *ss++;
        size--;
    }

}
    
static void TransceiverInit(void)
{
    /* Set CAN0TX as P10_7 and CAN0RX as P10_6 */
    	PMC10 |= 0x00C0; /* Alternative Functions */                     
    	PFC10 |= (0x00C0); 	// ALT 4 		/* Alternative 2 */       
		PFCE10 |= (0x00C0); 
    	PM10 &= ~(1<<7);    /* P0_0 CANTX     Output */                                              
    	PM10 |= 1<<6;  /* P0_1 CANRX     Input */
    #if 0
    /* Set CAN_EN  CAN_STB of transceiver.  */        
    PM10 &= ~(1<<5);     /* CAN_EN set to high */
    P10 |= (1<<5);
    PM0 &= ~(1<<4);     /* CAN_STB set to high */
      P0 |= (1<<4);
  #endif
}

static void TransceiverDeinit(void)
{
	/* Set  P10_6 and P10_7 to reset state*/
    	PMC10 &= ~(0x00C0);                    
    	PFC10 &= ~(0x00C0); 	     
		PFCE10 &= ~(0x00C0); 
    	PM10 |= (1<<7);    /* P0_0 CANTX     Output */                                              
		//P10 &= ~(1 << 7)  // EN inactive
}


/**************************************************************************//**
 *
 *  \details Initialize can module.
 *
 *  \return If the can driver is initialized successfully return
 *          BL_ERR_OK. otherwise return BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK     - can driver is initialized successfully.
 *  \retval BL_ERR_NOT_OK - can driver is not initialized successfully.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
bl_Return_t Can_Init(void)
{
    bl_Return_t retval = BL_ERR_OK;   
    bl_u8_t i = 0;
    volatile bl_u32_t* pRFCC;
    TransceiverInit();
    
    /* Wait while CAN RAM initialization is ongoing */
    while((RSCAN0GSTS & 0x00000008)) ;
    
    /* Switch to global/channel reset mode */
    RSCAN0GCTR &= 0xfffffffb;    /*set the 3rd bit to 0 -- clear CSLPR to 0 enter RESET mode*/

    /*ID priority,DLC check is disabled,clkc as CAN clock. */
    RSCAN0GCFG = 0x0000C000;
    
    /* Specified CAN channel enter to reset mode and config bit rate .*/
    #if(CAN_CONTROLLER_0 == CAN_CONTROLLER_USED)
    {
        RSCAN0C0CTR &= 0xfffffffb;
        RSCAN0C0CFG = RSCFD0CFDCmNCFG_VALUE; /* clkc=PPLLCLK2=40M ,Bitrate = fCAN/(BRP+1)/(1+TSEG1+TSEG2) */
    }
    #elif(CAN_CONTROLLER_1 == CAN_CONTROLLER_USED)
    {
        RSCAN0C1CTR &= 0xfffffffb;
        RSCAN0C1CFG = RSCFD0CFDCmNCFG_VALUE; /* clkc=PPLLCLK2=40M ,Bitrate = fCAN/(BRP+1)/(1+TSEG1+TSEG2)  */ 
    }
    #elif(CAN_CONTROLLER_2 == CAN_CONTROLLER_USED)
    {
        RSCAN0C2CTR &= 0xfffffffb;
        RSCAN0C2CFG = RSCFD0CFDCmNCFG_VALUE; /* clkc=PPLLCLK2=40M ,Bitrate = fCAN/(BRP+1)/(1+TSEG1+TSEG2) */ 
    }
    #endif

    /* Set received frame rule. */
    Can_SetRxRule();
     
    /* Set THLEIE,MEIE,DEIE disabled*/
    RSCAN0GCTR &= 0xfffff8ff;
    
    /* ****FIFO buffer setting,in global reset mode***** */
    pRFCC = &(RSCAN0RFCC0);
    for(i = 0;i < CAN_RX_NUMBER;i++)
    {
        pRFCC[i] |= 0x0700; /*128 message depth, disable fifo interrupt.*/
    }

    /* If GlobalChannel in halt or reset mode */
    if (RSCAN0GSTS & 0x03) 
    {
        RSCAN0GCTR &= 0xfffffffc; /*Switch to communication mode*/
        while ((RSCAN0GSTS & 0x02) == 2) {}/* While halt mode */
        while ((RSCAN0GSTS & 0x01) == 1) {}/* While reset mode */
    }
    /* Enable TDC , Can channel switch to communication mode */
    Can_Channel_Mode();
    
    /* Set RxFIFO buffer available, in operating mode or global test mode. */
    for(i = 0;i < CAN_RX_NUMBER;i++)
    {
        pRFCC[i] |= 0x01; /* set RxFIFO0 to operation mode.*/
    }
    return retval;
    
}

/**************************************************************************//**
 *
 *  \details Transmit can message.
 *
 *  \param[in] handle - the index of a frame pdu list.
 *  \param[in] id     - the id of the frame pdu memory.
 *  \param[in] size   - the size of the frame pdu memory.
 *  \param[in] buffer - the address pointer of the frame pdu memory.
 *
 *  \return If the can driver is transmited successfully return BL_ERR_OK.
 *          otherwise return BL_ERR_CONTOLLER_BUSY.
 *
 *  \retval BL_ERR_OK             - can message is transmited successfully.
 *  \retval BL_ERR_CONTOLLER_BUSY - can message is not transmited successfully.
 *  \retval BL_ERR_NOT_INIT       - can driver is not initialized.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
bl_Return_t Can_Write(    const bl_CanTxPdu_t* PduInfo )
{
    bl_Return_t ret = BL_ERR_OK;
    bl_u8_t i = 0;

    volatile bl_u8_t* pTBSR;
    Can_FrameType* pTxBuffer;
    volatile bl_u8_t* pTBCR;
    bl_u8_t TxBufIdx = 0;
        
    #if(CAN_CONTROLLER_0 == CAN_CONTROLLER_USED)
    {
        pTBSR = &(RSCAN0TMSTS0);
        pTBCR = &(RSCAN0TMC0);
        pTxBuffer = (Can_FrameType*) &(RSCAN0TMID0);
    }
    #elif(CAN_CONTROLLER_1 == CAN_CONTROLLER_USED)
    {
        pTBSR = &(RSCAN0TMSTS16);
        pTBCR = &(RSCAN0TMC16);
        pTxBuffer = (Can_FrameType*) &(RSCAN0TMID16);
    }
    #elif(CAN_CONTROLLER_2 == CAN_CONTROLLER_USED)
    {
        pTBSR = &(RSCAN0TMSTS32);
        pTBCR = &(RSCAN0TMC32);
        pTxBuffer = (Can_FrameType*) &(RSCAN0TMID32);
    }
    #endif
      
    if(0x0 != (pTBSR[TxBufIdx] & (bl_u8_t)0x09) )
    {
        ret = BL_ERR_NOT_OK;
    }
    else
    {

        /* Store message to tx buffer */
       
        CANFD_TraTempData.ID = PduInfo->canId;
        CANFD_TraTempData.DLC = PduInfo->dlc;
                
        for(i = 0; i < CANFD_TraTempData.DLC; i++)
        {
            CANFD_TraTempData.DB[i] = PduInfo->frame[i];
        }
        
        pTxBuffer[TxBufIdx] = CANFD_TraTempData;

        /* Set transmission request */
        pTBCR[TxBufIdx] = 0x01; /*CAN_TBCR_TRM;*/
    }
        
           
    return ret;
}
 
/**************************************************************************//**
 *
 *  \details Receive can message.
 *
 *  \param[in]  handle  - the index of a frame pdu list.
 *  \param[out] buffer  - the address pointer of the frame pdu memory.
 *  \param[out] retSize - the size of the frame pdu memory.
 *
 *  \return If the can message is received successfully return BL_ERR_OK.
 *          otherwise return BL_ERR_NO_DATA.
 *
 *  \retval BL_ERR_OK       - can message is received successfully.
 *  \retval BL_ERR_NO_DATA  - can message is not received successfully.
 *  \retval BL_ERR_NOT_INIT - can driver is not initialized.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
bl_Return_t Can_Read(bl_CanRxPdu_t *pdu)
{

    bl_Return_t tem = BL_ERR_OK;
    bl_u8_t i;
    bl_u8_t BufIdx;
    bl_u32_t TempCRBRCF0;
    Can_REC_FrameType* pRxBuffer;
    volatile bl_u32_t* pCRBRCF;
    /* Judge if new messages to RX buffer are available */
    TempCRBRCF0 = RSCAN0FESTS;    /*Receive FIFO Buffer Empty Register, if it is false, new data is coming.*/
    if (0xFF == (TempCRBRCF0 & 0xFF)) 
    {
       tem = BL_ERR_NOT_OK;
    }
    else
    {
            /* Get Rx FIFO buffer that has new message */
               for (BufIdx = 0U; BufIdx < CAN_FIFO_RX_BUF_NUM; ++BufIdx) /*CAN_CRBRCF0_RX_BUF_NUM=8.*/
            {
                if ((TempCRBRCF0 & CAN_1_BIT_MASK) == CAN_TX_OK) /*CAN_1_BIT_MASK==0x1; CAN_TX_OK=0x0*/
                {
                    break;    /*if checked bit is 1, that means there is a new message in corresponding receive buffer */
                }
                TempCRBRCF0 = TempCRBRCF0 >> CAN_B1_BIT_POS; /*CAN_B1_BIT_POS=0x1*/
            }
            /* Read out message from Rx buffer */
            pRxBuffer = (Can_REC_FrameType*)(RSCAN0RFID0_ADDRESS+(RSCAN0RFIDx_ADDRESS_OFFSET * BufIdx));
            pdu->canId = pRxBuffer->ID;
            pdu->dlc = pRxBuffer->DLC;
            for(i = 0; i < pdu->dlc; i++)
            {
                pdu->frame[i] =  pRxBuffer->DB[i];
            }
            pdu->handle = 0;
            /* read pointer moves to next unread message. */
            pCRBRCF = &(RSCAN0RFPCTR0);
            pCRBRCF[BufIdx] |= 0xFF; 
    }
       
    return tem;
}

/**************************************************************************//**
 *
 *  \details Check can transmit status.
 *
 *  \param[in] handle  - the index of a frame pdu list.
 *
 *  \return If the can message is transmited successfully return
 *          BL_ERR_OK. otherwise return BL_ERR_CONTOLLER_NOT_BUSY.
 *
 *  \retval BL_ERR_OK                 - can driver is initialized successfully.
 *  \retval BL_ERR_CONTOLLER_NOT_BUSY - can driver is not busy.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
bl_Return_t Can_CheckTxStatus(bl_u8_t handle)
{
    bl_Return_t tem = BL_ERR_NOT_OK;    
    volatile bl_u8_t* pTBSR;
	
	#if(CAN_CONTROLLER_0 == CAN_CONTROLLER_USED)
    {
        pTBSR = &(RSCAN0TMSTS0);
    }
    #elif(CAN_CONTROLLER_1 == CAN_CONTROLLER_USED)
    {
        pTBSR = &(RSCAN0TMSTS16);
    }
    #elif(CAN_CONTROLLER_2 == CAN_CONTROLLER_USED)
    {
        pTBSR = &(RSCAN0TMSTS32);
    }
    #endif
	if(pTBSR[0] == 0X4)
	{
		pTBSR[0] = CAN_TX_OK;  /*CAN_TX_OK =0 */
		tem = BL_ERR_OK;
	}
    return tem;
}

/**************************************************************************//**
 *
 *  \details Check can busoff.
 *
 *  \return None.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
void Can_BusOff_Check(void)
{

}

/**************************************************************************//**
 *
 *  \details Set can module into sleep mode.
 *
 *  \return None.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
void Can_Sleep(void)
{

}

/**************************************************************************//**
 *
 *  \details Set can module into wakeup mode.
 *
 *  \return None.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
void Can_Wakeup(void)
{
                      
} 

/**************************************************************************//**
 *
 *  \details Set can module receive frame rule.
 *
 *  \return None.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/

static void Can_SetRxRule(void)
{    
    bl_u16_t RxRuleIdx;
    bl_u8_t PageRxRuleIdx;
    volatile can_cre_type* pCRE;

    /* Set Rx rule number per channel */
    #if(CAN_CONTROLLER_0 == CAN_CONTROLLER_USED)
    RSCAN0GAFLCFG0 |= (CAN_RX_NUMBER << 24);   /* Channel 0  rule number */
    #elif(CAN_CONTROLLER_1 == CAN_CONTROLLER_USED)
    RSCAN0GAFLCFG0 |= (CAN_RX_NUMBER << 16);   /*Channel 1  rule number */  
    #elif(CAN_CONTROLLER_2 == CAN_CONTROLLER_USED)
    RSCAN0GAFLCFG0 |= (CAN_RX_NUMBER << 8);    /*Channel 2  rule number */ 
    #endif
    
    /* Get access base address of Rx rule */
    pCRE = (volatile can_cre_type*)&(RSCAN0GAFLID0);

    /* Receive Rule Table Write Enable */
    RSCAN0GAFLECTR |= 0x00000100;    /*set bit8 to 1, Receive rule table write is enabled*/

    /* Copy Rx rule one by one */
    for (RxRuleIdx = 0U; RxRuleIdx < CAN_RX_NUMBER; RxRuleIdx++)
    {
        PageRxRuleIdx = (bl_u8_t) (RxRuleIdx & 0x0F); 

        /* Update target Rx rule page if necessary. */
        if (PageRxRuleIdx == 0U) /*RxRuleIdx=0, page=0; RxRuleIdx=16, page=1; RxRuleIdx=32,page=2;...*/
        {
            RSCAN0GAFLECTR |= RxRuleIdx >> 4U; /*CAN_RX_RULE_PAGE_IDX_BIT_POS= 4U*/
        }

        /* Set a single Rx rule.*/
        pCRE[PageRxRuleIdx] = RX_RULE_TABLE_LIST1[RxRuleIdx];
    }

    /* Rx rule write disable */
    RSCAN0GAFLECTR &= 0xfffffeff;
}

/**************************************************************************//**
 *
 *  \details Reset can module receive frame rule.
 *
 *  \return None.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/

static void Can_ResetRxRule(void)
{    
    bl_u16_t RxRuleIdx;
    bl_u8_t PageRxRuleIdx;
    volatile can_cre_type* pCRE;
         
    /* Get access base address of Rx rule */
    pCRE = (volatile can_cre_type*)&(RSCAN0GAFLID0);

    /* Receive Rule Table Write Enable */
    RSCAN0GAFLECTR |= 0x00000100;    

    /* Copy Rx rule one by one */
    for (RxRuleIdx = 0U; RxRuleIdx < CAN_RX_NUMBER; RxRuleIdx++) 
    {
        PageRxRuleIdx = (bl_u8_t) (RxRuleIdx & 0x0F); 
        
        /* Update target Rx rule page if necessary. */
        if (PageRxRuleIdx == 0U) 
        {
            RSCAN0GAFLECTR |= RxRuleIdx >> 4U; 
        }

        /* Set a single Rx rule.*/
        pCRE[PageRxRuleIdx] = RX_RULE_TABLE_LIST0[RxRuleIdx];
    }

    /* Rx rule write disable */
    RSCAN0GAFLECTR &= 0xfffffeff;
    /* Reset Rx rule number per channel */
    RSCAN0GAFLCFG0 = 0x0;
    
}


/**************************************************************************//**
 *
 *  \details change can channel mode.
 *
 *  \return None.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
static void Can_Channel_Mode()
{
    
    #if(CAN_CONTROLLER_0 == CAN_CONTROLLER_USED)
    {
        if (RSCAN0C0STS & 0x03) /* If Channel0 in halt or reset mode */
        {
            RSCAN0C0CTR &= 0xfffffffc;     /*Switch to communication mode*/
            while ((RSCAN0C0STS & 0x02) == 2) {}/* While halt mode */
            while ((RSCAN0C0STS & 0x01) == 1) {}/* While reset mode */
        }
    }
    #elif(CAN_CONTROLLER_1 == CAN_CONTROLLER_USED)
    {
        if (RSCAN0C1STS & 0x03) /* If Channel1 in halt or reset mode */
        {
            RSCAN0C1CTR &= 0xfffffffc;     /*Switch to communication mode*/
            while ((RSCAN0C1STS & 0x02) == 2) {}/* While halt mode */
            while ((RSCAN0C1STS & 0x01) == 1) {}/* While reset mode */
        }
    }
    #elif(CAN_CONTROLLER_2 == CAN_CONTROLLER_USED)
    {
        if (RSCAN0C2STS & 0x03) /* If Channel2 in halt or reset mode */
        {
            RSCAN0C2CTR &= 0xfffffffc;     /*Switch to communication mode*/
            while ((RSCAN0C2STS & 0x02) == 2) {}/* While halt mode */
            while ((RSCAN0C2STS & 0x01) == 1) {}/* While reset mode */
        }
    }
    #endif
}

/**************************************************************************//**
 *
 *  \details reset can channel mode.
 *
 *  \return None.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
static void Can_Reset_Channel_Mode()
{
    #if(CAN_CONTROLLER_0 == CAN_CONTROLLER_USED)
    {
        RSCAN0C0CTR = 0x05;     
    }
    #elif(CAN_CONTROLLER_1 == CAN_CONTROLLER_USED)
    {
        RSCAN0C1CTR = 0x05;
    }
    #elif(CAN_CONTROLLER_2 == CAN_CONTROLLER_USED)
    {
        RSCAN0C2CTR = 0x05;
    }
    #endif
}


/**************************************************************************//**
 *
 *  \details Deinitialize can module.
 *
 *  \return None.
 *
 *  \since V2.0.0
 *
 *****************************************************************************/
void Can_Deinit(void)
{
    bl_u8_t i = 0;
    volatile bl_u32_t* pRFCC;
    
    TransceiverDeinit();
    
    /* Set RxFIFO buffer disable, in operating mode or global test mode. */
    pRFCC = &(RSCAN0RFCC0);
    for(i = 0;i < CAN_RX_NUMBER;i++)
    {
        pRFCC[i] &= ~(0x01); /*Disable RxFIFO0 .*/
    }
    
    /* Wait while CAN RAM initialization is ongoing */
    while((RSCAN0GSTS & 0x00000008)) ;
    
    /* Switch to global/channel reset mode */
    RSCAN0GCTR = 0x1;    /* enter RESET mode*/

    /*ID priority,DLC check is disabled,clkc as CAN clock, overflow stored */
    RSCAN0GCFG = 0x0;    /*set to reset state*/
    
    /* Specified CAN channel quits to stop mode and config bit rate .*/
    #if(CAN_CONTROLLER_0 == CAN_CONTROLLER_USED)
    {
        RSCAN0C0CTR &= 0xfffffffb;
        RSCAN0C0CFG = 0x0;
            
    }
    #elif(CAN_CONTROLLER_1 == CAN_CONTROLLER_USED)
    {
        RSCAN0C1CTR &= 0xfffffffb;
        RSCAN0C1CFG = 0x0;  
        
    }
    #elif(CAN_CONTROLLER_2 == CAN_CONTROLLER_USED)
    {
        RSCAN0C2CTR &= 0xfffffffb;
        RSCAN0C2CFG = 0x0; 
            
    }
    #endif

    Can_ResetRxRule();

    /* ****FIFO buffer resetting,in global reset mode***** */
    
    for(i = 0;i < CAN_RX_NUMBER;i++)
    {
        pRFCC[i] &= ~(0x0100); /*set to reset state*/
    }
     
    Can_Reset_Channel_Mode();
    
    RSCAN0GCTR = 0x05; /*Switch to stop mode*/
            
}





/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                                 *
*   AUTHOR     :                                                       *
************************************************************************
* Object        :
* Module        :	IIC
* Instance      :
* Description   :	
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
* ----------------------------------------------------------------------
* 0.1    Jan 20,2016   Init version.
* ----------------------------------------------------------------------
* 0.2    Dec 20,2016  ShangQiuju		add irq_if.h for complie error.
*----------------------------------------------------------------------
* 0.3    Jan 24,2017    ZhangJie       Fix Coverity warning.
*-----------------------------------------------------------------------
* 0.4     Apr 1,2017    PEI Jingli     Fix include files.
*-----------------------------------------------------------------------
* 0.5    Aug 11,2017	ZhengXiaolei	Add master write/read TPI function. 
*=====================================================================*/
#include "Cpu.h"
#include "Define.h"
#include "IIC_if.h"
#include "IIC.h"
#include "IIC_Cfg.h"
#include "irq_if.h"
#include "iodefine.h"

STATIC IIC_PARAM   iic_prm={0};
/* baud setting when CPUCLK2=40M*/
STATIC const IIC_BAUDCONFIG baud[BAUD_OPTIONMAX]={
{0x70u,0xEDu,0xEFu},			/*10k*/
{0x30u,0xFAu,0xF7u},			/*100k*/
{0x10u,0xF9u,0xF8u}			/*400K*/  
};

STATIC void IIC_Master_Session_finish(void);
/***********************************************************************
*  Name        : IIC_Reset_Internal
*  Description : 
			Releases RIIC from slave-address matched state and
			initializes the internal counter while retaining other settings.
			Restore SCL and SDA to high impedance state.			

			Issuing a reset during slave operation may lead to a loss of synchronization 
			between the master device clock and the slave device clock.
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void IIC_Reset_Internal(void)
{
    RIIC0.CR1.UINT32    |= 0x00000040UL;	
    RIIC0.CR1.UINT32    &= 0xFFFFFFBFUL;	
}

/***********************************************************************
*  Name        : IIC_SET_SCL_LOW
*  Description : 
			Control SCL directly. 
			Do not use during a START , STOP , repeated START , or during transmission or reception. 
			Operation after rewriting under the above conditions is not guaranteed.
*  Parameter   : blevel- FALSE, release SCL
					TRUE, set SCL low
*  Returns     : None
***********************************************************************/
void IIC_SET_SCL_LOW(BOOL blevel)
{
    	if(blevel==FALSE)
    	{
		    RIIC0.CR1.UINT32    &= 0xFFFFFFEFUL;	
	           RIIC0.CR1.UINT32    |=  0x00000008UL;			
	}
	else
	{
		    RIIC0.CR1.UINT32    &= 0xFFFFFFE7UL;	
	}
}
/***********************************************************************
*  Name        : I2C_Start
*  Description : Initialize the I2C module
*  Parameter   : 
                 baudrate - baud rate
                 Addr - slave address, only support 7 bit address now
                 RoleOption - master or slave
*  Returns     : None
***********************************************************************/
void IIC_Start( BAUD_OPTION baudrate, U8 Addr , IIC_ROLEOPTION RoleOption)
{  
	 /* disable interrupt, clear int request flag, set table reference flag*/
	IRQ_IntDis(INTRIIC0TI);
	IRQ_IntClr(INTRIIC0TI);

	IRQ_IntDis(INTRIIC0TEI);
	IRQ_IntClr(INTRIIC0TEI);	

	IRQ_IntDis(INTRIIC0RI);
	IRQ_IntClr(INTRIIC0RI);	

	IRQ_IntDis(INTRIIC0EE);
	IRQ_IntClr(INTRIIC0EE);		

	/*Disabled (the RIICnSCL and RIICnSDA pins are not driven)*/
	RIIC0.CR1.UINT32    &= 0xFFFFFF7FUL;

	/* Initiates the RIIC reset or internal reset. set to 1*/
	RIIC0.CR1.UINT32    |= 0x00000040UL;

	/*Enabled (the RIICnSCL and RIICnSDA pins driven). set to 1*/
	RIIC0.CR1.UINT32    |= 0x00000080UL;

	iic_prm.rx_count=0u;
	iic_prm.rx_len=0u;
	iic_prm.tx_count=0u;
	iic_prm.tx_len=0u;
	iic_prm.reg_adr=0u;

	iic_prm.role = RoleOption;
	/* SAR0 7bit address*/
	iic_prm.slave_adr = ((U16)Addr<<1);		/*left shift 1bit*/
	RIIC0.SAR0.UINT32   |= iic_prm.slave_adr;	

	/* enable RIICnSAR0*/
	RIIC0.SER.UINT32    = 0x00000001UL;

	/*Internal Reference Clock Selection.*/
	/*b 6:b 4      CKS    - Internal Reference Clock Selection*/
	RIIC0.MR1.UINT32    |= baud[baudrate].CKS;  	

	if(RoleOption==IIC_MASTER)
	{
		RIIC0.BRH.UINT32    = baud[baudrate].BRH; 	/* CLK/baudrate , low 5 bit */
		iic_prm.iic_state = IDLE_STATE;
	}
	else		
	{
	iic_prm.iic_state = DATA_RECV_STATE;		/* for salve, set initial state to receive*/
	}

	RIIC0.BRL.UINT32    = baud[baudrate].BRL;	/* still set BRL for slave*/

	/*b 2 		TMOH   - SCL H */
	/* b 1          TMOL   - SCL L*/
	/*b 0          TMOS   - long mode, 16 bit*/
	RIIC0.MR2.UINT32    = 0x00000006UL;		/*default value*/
	/*RIIC0.MR2.UINT32    &= 0xF9;		disable timeout count*/

	/* ACKWP=1  -  Modification of the ACKBT bit is enabled. */
	RIIC0.MR3.UINT32    = 0x00000010UL;

	/*  NACKE=1, Transfer operation is suspended during NACK reception. */
	RIIC0.FER.UINT32    = 0x00000010UL;
	/* enable interrupt, TI, TEI,RI,STOP,NACK*/
	RIIC0.IER.UINT32    = 0x000000F8UL;	

	/*Clears the RIIC reset or internal reset.*/
	RIIC0.CR1.UINT32    &= 0xFFFFFFBFUL;

	IRQ_IntEn(INTRIIC0TI);
	IRQ_IntEn(INTRIIC0TEI);
	IRQ_IntEn(INTRIIC0RI);
	IRQ_IntEn(INTRIIC0EE);	
}


/***********************************************************************
*  Name        : IIC_Stop
*  Description : Stop IIC module
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void IIC_Stop( void )
{
    IIC_REG_IICBnCTL0 = IICB_CTL0_IICE_DISABLE_IIC; /*disable IICB0 */
    
    IRQ_IntDis(INTRIIC0TI);
    IRQ_IntClr(INTRIIC0TI);

    IRQ_IntDis(INTRIIC0TEI);
    IRQ_IntClr(INTRIIC0TEI);     
	
    IRQ_IntDis(INTRIIC0RI);
    IRQ_IntClr(INTRIIC0RI);     	
	
    IRQ_IntDis(INTRIIC0EE);
    IRQ_IntClr(INTRIIC0EE);     			
}

/***********************************************************************
*  Name        : I2C_Handler
*  Description : this function is use for the I2C receive IRQ
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void IIC_Rx_Handler( void )
{
U32 dummy_read =0;
	
	switch(iic_prm.role)
	{
		case IIC_SLAVE:
		{
		     if ( iic_prm.iic_state == DATA_RECV_STATE )
	            {	          				
			    /* 1st rx data is device address*/
			    /* 2nd data is reg address*/
			    /* following is data to write if there is any*/
 
				iic_prm.RW_direction = IIC_RX;

				if(iic_prm.rx_count==I2C_CB_NUMBER)
				{
					iic_prm.reg_adr = (U8)RIIC0.DRR.UINT32; 
					    
					    if(NULL!=i2c_slave_prepareData_callback)
					    {
	    				    	/* prepare data based on register address*/
						i2c_slave_prepareData_callback(iic_prm.reg_adr);
					    }					  
				}
				else if(iic_prm.rx_count>I2C_CB_NUMBER)
				{
					if(iic_prm.rx_count<iic_prm.rx_len)
					{
			    			*iic_prm.rx_data_p++ = (U8)RIIC0.DRR.UINT32;    /* Read data*/			    
					}					
					else
					{
						dummy_read = (U8)RIIC0.DRR.UINT32; 	/* dummy read*/
															/* prevent error when out of array bound*/

					}
				}				
				else if(iic_prm.rx_count==0u)		
				{
					dummy_read = (U8)RIIC0.DRR.UINT32;   	/* dev adr, don't care*/

					iic_prm.tx_data_p=NULL;	/* reset before register address is received*/
					iic_prm.tx_len=0;
				}
				
			   	iic_prm.rx_count++;	    			    
	            }
			break;
		}
		case IIC_MASTER:
		{
	       	     if ( iic_prm.iic_state == DATA_RECV_STATE )
	            {
	                if ( RIIC0.SR2.UINT32 & 0x00000010UL )           /* NACK detected*/
	                {
	                    /* Clear Stop Condition Detection Flag.*/
	                    RIIC0.SR2.UINT32    &= 0xFFFFFFF7UL;

	                    /* Requests to issue a stop condition.*/
	                    RIIC0.CR2.UINT32    |= 0x00000008UL;

	                    dummy_read          = RIIC0.DRR.UINT32;             /* Dummy read*/

	                    if ( iic_prm.rx_len <= 2UL )
	                    {
	                        iic_prm.iic_state   = DATA_RECV_END_STATE_2;
	                    }
	                    else
	                    {
	                        iic_prm.iic_state   = DATA_RECV_END_STATE;				
	                    }
	                }
	                else		/* ACK*/
	                {
	                    if ( iic_prm.rx_len <= 2UL )
	                    {
	                        /* WAIT,SCL hold low between 9th clk and next 1st clk, only in receive mode*/
	                        RIIC0.MR3.UINT32    |= 0x00000040UL;

	                        if ( iic_prm.rx_len == 2U )
	                        {
	                            dummy_read          = RIIC0.DRR.UINT32;                       /* Dummy read*/
	                            iic_prm.iic_state   = DATA_RECV_STATE_2;
	                        }
	                        else
	                        {
	                            /* Modification of the ACKBT bit is enabled.*/
	                            RIIC0.MR3.UINT32    |= 0x00000010UL;
	                            
	                            /* RDRFS=1, RDRF is set at the rising edge of the 8th SCL */
		                     /* ACKBT=1, send NACK*/
	                            RIIC0.MR3.UINT32    |= 0x00000028UL;

	                            dummy_read          = RIIC0.DRR.UINT32;                       
	                            iic_prm.iic_state   = DATA_RECV_STATE_3;
	                        }
	                    }
	                    else		/*data to receive > 2 bytes*/
	                    {
	                        dummy_read              = RIIC0.DRR.UINT32;              
	                        iic_prm.iic_state       = DATA_RECV_STATE_4;
	                    }
	                }
	            }
	            else if ( iic_prm.iic_state == DATA_RECV_STATE_2 )
	            {
	                /* NACK write enable*/
	                RIIC0.MR3.UINT32    |= 0x00000010UL;

	                /* RDRFS=1, RDRF is set at the rising edge of the 8th SCL */
	                /* ACKBT=1, send NACK*/
	                RIIC0.MR3.UINT32    |= 0x00000028UL;

	                *iic_prm.rx_data_p++ = (U8)RIIC0.DRR.UINT32;                          /* Read data*/
	                iic_prm.rx_count++;
	                iic_prm.iic_state    = DATA_RECV_STATE_3;
	            }
	            else if ( iic_prm.iic_state == DATA_RECV_STATE_3 )
	            {
	                /* Clear Stop Condition Detection Flag.*/
	                RIIC0.SR2.UINT32    &= 0xFFFFFFF7UL;

	                /* Requests to issue a stop condition.*/
	                RIIC0.CR2.UINT32    |= 0x00000008UL;

	                *iic_prm.rx_data_p++ = (U8)RIIC0.DRR.UINT32;                          /* Read data*/
	                iic_prm.rx_count++;

	                /* NACK write enable*/
	                RIIC0.MR3.UINT32    |= 0x00000010UL;                       

	                /* send NACK*/
	                RIIC0.MR3.UINT32    |= 0x00000008UL;

                       /* clear WAIT, SCL not hold low */
	                RIIC0.MR3.UINT32    &= 0xFFFFFFBFUL;

	                iic_prm.iic_state   = DATA_RECV_END_STATE_2;
	            }
	            else if ( iic_prm.iic_state == DATA_RECV_STATE_4 )
	            {
	                if ( iic_prm.rx_len == (iic_prm.rx_count + 1UL) )		/*last byte*/
	                {
	                    /* Clear Stop flag*/
	                    RIIC0.SR2.UINT32    &= 0xFFFFFFF7UL;

	                    /* Requests to issue a stop condition.*/
	                    RIIC0.CR2.UINT32    |= 0x00000008UL;

	                    *iic_prm.rx_data_p++ = (U8)RIIC0.DRR.UINT32;      /* Read data*/
	                    iic_prm.rx_count++;

	                    /* clear WAIT, SCL not hold low */
	                    RIIC0.MR3.UINT32    &= 0xFFFFFFBFUL;

	                    iic_prm.iic_state   = DATA_RECV_END_STATE;			
			     			
	                }
	                else if ( iic_prm.rx_len == (iic_prm.rx_count + 2UL) )
	                {
	                    /* NACK write enable*/
	                    RIIC0.MR3.UINT32    |= 0x00000010UL;

	                    /* send NACK*/
	                    RIIC0.MR3.UINT32    |= 0x00000008UL;

	                    *iic_prm.rx_data_p++ = (U8)RIIC0.DRR.UINT32;                  /* Read data*/
	                    iic_prm.rx_count++;
	                }
	                else if ( iic_prm.rx_len == (iic_prm.rx_count + 3UL) )
	                {
	                    /* WAIT*/
	                    RIIC0.MR3.UINT32    |= 0x00000040UL;

	                    *iic_prm.rx_data_p++ = (U8)RIIC0.DRR.UINT32;                          /* Read data*/
	                    iic_prm.rx_count++;
	                } 
			else 
			{
	                    *iic_prm.rx_data_p++ = (U8)RIIC0.DRR.UINT32;                          /* Read data*/
	                    iic_prm.rx_count++;
	                }
	            }
		break;
	     	}		
	    	default:
				break;
	}
	
(void)(dummy_read);
}



/****************************************************************************************************
*  Name        : IIC_Is_Busy
*  Description : Check if I2C channel is busy or not
*  Parameter   :None
*  Returns     : None
*****************************************************************************************************/
BOOL IIC_Is_Busy(void)
{
	BOOL bState=FALSE;
	
	if( RIIC0.CR2.UINT32 & 0x00000080UL )
	{
		bState = TRUE;
	}
	else
	{
		bState = FALSE;
	}
	return bState;
}

/***********************************************************************
*  Name        : IIC_MasterWriteFrame
*  Description : Send data as master.
*  Parameter   :                  
	          Addr - the slave address to Write
                 pstr - the buffer address to send
                 size - the count to write, address is not included
                 options - reserved
*  Returns     : None
***********************************************************************/
BOOL IIC_MasterWriteFrame(  U8 Addr, U8* pstr, U8 size, U8 options )
{
    static U8 busyCount=0;
	
    if(IIC_Is_Busy())
    {    
    	if(busyCount<I2C_RETRY_COUNT)
    	{
	    	busyCount++;
		return FALSE;
    	}
	else
	{
		IIC_Reset_Internal();
		IIC_Master_Session_finish();
		busyCount=0;
		return FALSE;
	}
    }
	
    iic_prm.iic_state   = ADDR_W_STATE;
    iic_prm.tx_data_p   = pstr;
    iic_prm.tx_len      = size;
    iic_prm.tx_count    = 0U;

    /*Requests to issue a start condition.*/
    RIIC0.CR2.UINT32    |= 0x00000002UL;

    return TRUE;
}

/***********************************************************************
*  Name        : I2C_ReadFrame
*  Description : Read data as master.
*  Parameter   : 
                 Addr -the slave address to Read
                 pstr - the buffer address to store
                 size - size of data to read
		    options -  reserved
*  Returns     : None
***********************************************************************/
BOOL  IIC_MasterReadFrame( U8 Addr, U8* pstr, U8 size, U8 options )
{		
    static U8 busyCount=0;
	
    if(IIC_Is_Busy())
    {    
    	if(busyCount<I2C_RETRY_COUNT)
    	{
	    	busyCount++;
		return FALSE;
    	}
	else
	{
		IIC_Reset_Internal();
		IIC_Master_Session_finish();
		busyCount=0;
		return FALSE;
	}
    }
	
    iic_prm.iic_state   = ADDR_R_STATE;
    iic_prm.rx_data_p   = pstr;
    iic_prm.rx_len      = size;
    iic_prm.rx_count    = (U8)0u;

    /*Requests to issue a start condition.*/
    RIIC0.CR2.UINT32    |= 0x00000002UL;

    return TRUE;
}

/*******************************************************************************
**  FUNCTION      : IICMasterReadReg
**  DESCRIPTION   : 
**  PARAMETERS    : void
**  RETURN        : void
*******************************************************************************/
U8 IICMasterReadReg(BAUD_OPTION BAUD, U8 SLAVE_ADDR, U8 RegOffset)
{
	U8 Data;
	IIC_Start(BAUD,SLAVE_ADDR,IIC_MASTER);	
	IIC_MasterWriteFrame(SLAVE_ADDR, (U8*)&RegOffset, 1, 0);	
	delay_us(500);
	IIC_MasterReadFrame(SLAVE_ADDR, (U8*)&Data, 1, 0);
	delay_us(500);
	return Data;
}


/*******************************************************************************
**  FUNCTION      : IICMasterWriteReg
**  DESCRIPTION   : 
**  PARAMETERS    : void
**  RETURN        : void
*******************************************************************************/
void IICMasterWriteReg(BAUD_OPTION BAUD, U8 SLAVE_ADDR, U8 RegOffset, U8 Data)
{	
	U8 sendbuffer[2] = {0};		
	IIC_Start(BAUD,SLAVE_ADDR,IIC_MASTER);	
	sendbuffer[0] = RegOffset;
	sendbuffer[1] = Data;
	IIC_MasterWriteFrame(SLAVE_ADDR , (U8*)&sendbuffer, 2, 0);	
	delay_us(500);
}

/******************************************************************************
* Function Name : IIC_SlaveWriteFrame
* Description   : Prepare data to send for slave.

* Argument      : pstr- pointer to first byte to send
			    size- length of bytes to send
* Return Value  : none
******************************************************************************/
/*BOOL IIC_Slave_TxBuf_Set(U8  *pstr, U8 size )*/
BOOL IIC_SlaveWriteFrame(U8  *pstr, U8 size )
{
    BOOL bReturn=TRUE;

    if(pstr==NULL)
    {
	bReturn=FALSE;
    }
    else
    {
	    /* size check*/
	    if(size==0u)
	    {
		size=1u;		
	    }
	    iic_prm.tx_len = size;
	    iic_prm.tx_data_p   = pstr;
    }		
    return bReturn;
}

/******************************************************************************
* Function Name : IIC_SlaveReadFrame
* Description   : set receive address.
* Argument      : pstr- pointer to receive address
			size- length of bytes to receive
* Return Value  : none
******************************************************************************/
/*BOOL IIC_Slave_RxBuf_Set( U8 *pstr, U8 size)*/
BOOL IIC_SlaveReadFrame( U8 *pstr, U8 size)
{
    BOOL bReturn=TRUE;

   if(pstr==NULL)
    {
	bReturn=FALSE;
    }
    else
    {
    	iic_prm.rx_len= size;
       iic_prm.rx_data_p   = pstr;
    }		
    return bReturn;
}
/******************************************************************************
* Function Name : ISR_IIC0RIfunc
* Description   : receive byte interrupt.
* Argument      : none
* Return Value  : none
******************************************************************************/
void ISR_IIC0RIfunc(void)
{
	IIC_Rx_Handler();
	if(  NULL !=mcu_i2c_rx_byte_callback)
	{
		mcu_i2c_rx_byte_callback();
	}
}

/******************************************************************************
* Function Name : ISR_IIC0TIfunc
* Description   : transmit data empty interrupt.
* Argument      : none
* Return Value  : none
******************************************************************************/
void ISR_IIC0TIfunc(void)
{
    /*U32 dummy_read=0;*/
	switch(iic_prm.role)
	{
		case IIC_SLAVE:
		{
	            /*if ( iic_prm.iic_state == DATA_SEND_STATE )*/
		    if ( iic_prm.iic_state ==DATA_RECV_STATE )
	            {
	                /* send 1 byte data based on received register,*/
	                /*register set is done in Rx INT.*/
	                /* enter here means master has switched to Rx mode	 */             
	                if(iic_prm.tx_data_p==NULL)
	                {
				RIIC0.DRT.UINT32    =I2C_ABNORMAL_RESPONSE;	/* abnormal response when no register addr received*/
			}
			else
			{
	                	RIIC0.DRT.UINT32    = *iic_prm.tx_data_p++;                       
			}
			
	                iic_prm.tx_count++;

	                iic_prm.iic_state   = DATA_SEND_STATE_2;
			iic_prm.RW_direction = IIC_TX;
			/*wait until NACK detected      Dummy read to release the SCL
 			while(!(RIIC0.SR2.UINT32 & 0x00000010UL) );
		            {
		                dummy_read          = RIIC0.DRR.UINT32;     
		                iic_prm.iic_state   = DATA_SEND_END_STATE;
		            }			 
			*/
	            }
			break;
		}
		case IIC_MASTER:
			{
			  if ( iic_prm.iic_state == ADDR_W_STATE )
		        {
		           /* Write address + write flag*/
		            RIIC0.DRT.UINT32    = (U32) (iic_prm.slave_adr) + IIC_DIR_W;      
		            iic_prm.iic_state   = DATA_SEND_STATE;
			    iic_prm.RW_direction = IIC_TX;		
		        }
		        else if ( iic_prm.iic_state == ADDR_R_STATE )
		        {
		            /*Write address + read flag*/
		            RIIC0.DRT.UINT32    = (U32) (iic_prm.slave_adr) + IIC_DIR_R;     
		            iic_prm.iic_state   = DATA_RECV_STATE;
			     iic_prm.RW_direction = IIC_RX;
		        }
			break;
		}

		default:
			break;
	}
}

/******************************************************************************
* Function Name : ISR_IIC0TEIfunc
* Description   : transmit end interrupt.
* Argument      : none
* Return Value  : none
******************************************************************************/
void ISR_IIC0TEIfunc(void)
{
U32 dummy_read=0;
	switch(iic_prm.role)
	{
		case IIC_MASTER:
		{
			if ( iic_prm.iic_state == DATA_SEND_STATE )
			{
				/* NACK detected or send finish*/
			    if ( (RIIC0.SR2.UINT32 & 0x00000010UL) || ( iic_prm.tx_count == iic_prm.tx_len ) )      /*NACK ? or Transmission end ?*/
			    {
			        /* Clear Transmit End Flag. set RIICnTEND=0*/
			        RIIC0.SR2.UINT32    &= 0xFFFFFFBFUL;

			        /* Clear Stop Condition Detection Flag. STOP=0*/
			        RIIC0.SR2.UINT32    &= 0xFFFFFFF7UL;

			        
#ifdef IIC_MASTER_READ_RESTART		/* only for ICS test, normally don't enable this*/
/*		if(bICS_Read)*/
			{
	 			 RIIC0.CR2.UINT32 |=0x00000004;	/* Generate restart*/
				iic_prm.rx_len=IIC_MASTER_ICS_READ_LEN;		/*set length to receive*/
				iic_prm.rx_count=0;		
				iic_prm.iic_state   = ADDR_R_STATE;	/* master change to rx state, send adr+R*/
			}
#else
/*		else*/
		{
			        /* Requests to issue a stop condition. SP=1*/
			        RIIC0.CR2.UINT32    |= 0x00000008UL;
				iic_prm.iic_state   = DATA_SEND_END_STATE;					
		}
#endif									        

			    }
			    else
			    {
  			        /* Write data*/
			        RIIC0.DRT.UINT32    = *iic_prm.tx_data_p++;                      
			        iic_prm.tx_count++;
			    }
			}
		break;
		}
		
		case IIC_SLAVE:
		{		        
		     /* Transmission end or NACK */
		     /*if ( (iic_prm.tx_count == iic_prm.tx_len) || (RIIC0.SR2.UINT32 & 0x00000010UL) )*/
		     
		     /* slave keeps send data until NACK received*/
		    if (RIIC0.SR2.UINT32 & 0x00000010UL) 	                                                                                  
		    {
	            	 /*Dummy read to release the SCL*/
	                dummy_read          = RIIC0.DRR.UINT32;     
	                iic_prm.iic_state   = DATA_SEND_END_STATE;
	            }
	            else
	            {
	            	  if(iic_prm.tx_count<iic_prm.tx_len)
	            	  {	                
	                	RIIC0.DRT.UINT32    = *iic_prm.tx_data_p++;                       

	            	  }
			   else
			   {
	          		RIIC0.DRT.UINT32    = I2C_ABNORMAL_RESPONSE;	/* always send fixed value if master doesn't STOP in time*/
	          													/* or read an undefined address*/
	          													/* this may depend on protocol definition*/
			   }
	                iic_prm.tx_count++;
	            }
			break;
		}

		default:
			break;
	}		
	
	if( NULL !=mcu_i2c_tx_byte_callback)
	{
		mcu_i2c_tx_byte_callback();
	}
(void)dummy_read;
}

/******************************************************************************
* Function Name : IIC_Slave_Session_finish
* Description   : Reset variable, must be called after session finish.
* Argument      : none
* Return Value  : none
******************************************************************************/
void IIC_Slave_Session_finish(void)
{
	iic_prm.tx_count=0;
	iic_prm.tx_len=0;
	iic_prm.rx_count=0;
	iic_prm.rx_len=0;
       iic_prm.iic_state   = DATA_RECV_STATE;		/* switch to rx state	*/
}
/******************************************************************************
* Function Name : IIC_Master_Session_finish
* Description   : Reset variable, must be called after session finish.
* Argument      : none
* Return Value  : none
******************************************************************************/
STATIC void IIC_Master_Session_finish(void)
{
	iic_prm.tx_count=0;
	iic_prm.tx_len=0;
	iic_prm.rx_count=0;
	iic_prm.rx_len=0;
       iic_prm.iic_state   = IDLE_STATE;
}

/******************************************************************************
* Function Name : ISR_IIC0EEfunc
* Description   : STOP detected.
* Argument      : none
* Return Value  : none
******************************************************************************/
void ISR_IIC0EEfunc(void)
{
	if( ( NULL !=mcu_i2c_stop_callback)
	 	&&  ( RIIC0.SR2.UINT32 & 0x00000008UL ) ) 		/* stop detected*/
	{
		mcu_i2c_stop_callback(iic_prm.role,iic_prm.RW_direction,
			((iic_prm.rx_count>(I2C_CB_NUMBER+1u))?(iic_prm.rx_count-I2C_CB_NUMBER-(U8)1u):0u));
	}


	switch(iic_prm.role)
	{
		case IIC_SLAVE:
		{
		   if ( (iic_prm.iic_state == DATA_SEND_STATE)    ||
	                 (iic_prm.iic_state == DATA_SEND_STATE_2)  ||
	                 (iic_prm.iic_state == DATA_SEND_END_STATE))
	            {
			iic_prm.RW_direction= IIC_TX;
			 if ( RIIC0.SR2.UINT32 & 0x00000010UL )          /* NACK detected*/
			 {
				/* Clear NACK Detection Flag*/					
		               RIIC0.SR2.UINT32    &= 0xFFFFFFEFUL;
			 	IIC_Slave_Session_finish();
			 }
			else if ( RIIC0.SR2.UINT32 & 0x00000008UL )          /* STOP detected*/
			{
		                /* Clear NACK Detection Flag	*/				
		                /*RIIC0.SR2.UINT32    &= 0xFFFFFFEFUL;*/

		                /* Clear Stop Condition Detection Flag.*/
		                RIIC0.SR2.UINT32    &= 0xFFFFFFF7UL;
			}
	            }		   		   
	            else if (iic_prm.iic_state == DATA_RECV_STATE)
	            {
	                if ( RIIC0.SR2.UINT32 & 0x00000020UL )                       /*RDRF=1, data exist in DRR */
	                {
	                    /*There is the case that a reception buffer overflows*/
		            *iic_prm.rx_data_p++ = (U8)RIIC0.DRR.UINT32;              /* Read data*/
		            iic_prm.rx_count++;
	                }
			
	                /*enable ACK write */
	                RIIC0.MR3.UINT32    |= 0x00000010UL;
	                /* RDRFS=0, RDRF set at 9th SCL's rising, SCL not held low at 8th SCL's falling*/
	                /*send ACK(0)*/
	                RIIC0.MR3.UINT32    &= 0xFFFFFFD7UL;							
	                /*Clear Stop*/
	                RIIC0.SR2.UINT32    &= 0xFFFFFFF7UL;
					
			 iic_prm.RW_direction= IIC_RX;

		 	IIC_Slave_Session_finish();
	            }	            	            
			break;
		}
	case IIC_MASTER:
	{
		 if ( (iic_prm.iic_state == DATA_SEND_END_STATE) || (iic_prm.iic_state == DATA_RECV_END_STATE) 
		 	|| ( iic_prm.iic_state == DATA_RECV_END_STATE_2 ) )
	        {
	            if ( RIIC0.SR2.UINT32 & 0x00000008UL )          /* stop detected*/
	            {	            
	                if ( iic_prm.iic_state == DATA_RECV_END_STATE_2 )
	                {
	                    /*enable ACK write */
	                    RIIC0.MR3.UINT32    |= 0x00000010UL;

	                    /* RDRF is set at the rising edge of the ninth SCL clock cycle. set to 0*/
	                    /* send ACK(0)*/
	                    RIIC0.MR3.UINT32    &= 0xFFFFFFD7UL;
	                }
	                /*Clear NACK Detection Flag*/
	                RIIC0.SR2.UINT32    &= 0xFFFFFFEFUL;
	                /* Clear Stop Condition Detection Flag.*/
	                RIIC0.SR2.UINT32    &= 0xFFFFFFF7UL;
	 			 
			  IIC_Master_Session_finish();
	            }
	        }	 
		else
		{
		           /* Clear NACK, STOP, AL, TIMEOUT*/
	                RIIC0.SR2.UINT32    &= 0xFFFFFFE4UL;
		 }	
		
		break;
		}
		default:
			break;
	}		

}


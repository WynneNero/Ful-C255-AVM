/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									   *
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
*----------------------------------------------------------------------
* 0.1  Dec 20,2015  init version
*----------------------------------------------------------------------
* 0.2  Dec 20,2016   ShangQiuju  remove unused include  files.
*------------------------------------------------------------------------
* 0.3  Jan 24,2017  ZhangJie  Fix Coverity warnings.
*=====================================================================*/

/*============================================================================
**Includes
===========================================================================*/
/*Config file*/

const U16 adc_ch_invalid_value_array[ADC_MAX]=
{
  0xFFFFu,0xFFFFu,0xFFFFu,0xFFFFu,0xFFFFu,0xFFFFu,0xFFFFu,0xFFFFu, 
  0xFFFFu,0xFFFFu,0xFFFFu,0xFFFFu,0xFFFFu,0xFFFFu,0xFFFFu,0xFFFFu, 
  0xFFFFu,0xFFFFu,0xFFFFu,0xFFFFu,0xFFFFu,0xFFFFu,0xFFFFu,0xFFFFu  
};


/***********************************************************************
*  Name        : port_setup_normal
*  Description :
*  Parameter   :
*  Returns     : None
***********************************************************************/
void Port_setup_poweron( void)
{

    volatile U16 PMC=PORT_REG_PMC(GPIO_PORT_0) ;
    volatile U16 PM = PORT_REG_PM(GPIO_PORT_0);
    volatile U16 PFC= PORT_REG_PFC(GPIO_PORT_0);
    volatile U16 PFCE =PORT_REG_PFCE(GPIO_PORT_0);
    volatile U16 PIBC=PORT_REG_PIBC(GPIO_PORT_0);
    volatile U16 P=0u;
    U32 regdata;
    
   /*Config Port 0*/
   
   /*P0_6 as general purpose input,P0_7 as INTP4 */   
    PMC=(PMC&(~(PMCn6_MODE_PORT)))|PMCn7_MODE_PORT;		/* for ATC board 3140 193 38251_B1.2-AC*/
    PM= PM|PMn6_MODE_INPUT|PMCn7_MODE_PORT;
    PIBC=PIBC|PIBCn6_IBUF_ENABLE;
    PFC=PFC&(~PMCn7_MODE_PORT);
    PFCE=PFCE|PMCn7_MODE_PORT;

    PORT_REG_PMC(GPIO_PORT_0) = PMC;    
    PORT_REG_PFC(GPIO_PORT_0)  = PFC;
    PORT_REG_PFCE(GPIO_PORT_0)  = PFCE;
    PORT_REG_PM(GPIO_PORT_0) =PM;
    PORT_REG_PIBC(GPIO_PORT_0)= PIBC;        

  /* configure  enable falling edge detection for INTP4*/
  INPT_Filter(INPT_4,FALLING_EDG);  
  
   /*Config Port 1*/
 /* set ports for P1_2, P1_3, P1_8,9  is GPIO output*/
   PMC=PORT_REG_PMC(GPIO_PORT_1) ;
   PM = PORT_REG_PM(GPIO_PORT_1);
   PFC= PORT_REG_PFC(GPIO_PORT_1);
   PFCE =PORT_REG_PFCE(GPIO_PORT_1);
   PIBC=PORT_REG_PIBC(GPIO_PORT_1);
   P=PORT_REG_P(GPIO_PORT_1);

   PMC=(PMC&(~(PMCn2_MODE_PORT|PMCn3_MODE_PORT|PMCn8_MODE_PORT|PMCn9_MODE_PORT)));
   PM=(PM&( ~(PMn2_MODE_INPUT|PMn3_MODE_INPUT|PMCn8_MODE_PORT|PMCn9_MODE_PORT)));   
   /*PFC=PFC&(~PMn3_MODE_INPUT);*/
   /*PFCE=PFCE&(~PMn3_MODE_INPUT);*/
   /*P=P&(~PMn3_MODE_INPUT);*/

    PORT_REG_PMC(GPIO_PORT_1) = PMC;    
    PORT_REG_PFC(GPIO_PORT_1)  = PFC;
    PORT_REG_PFCE(GPIO_PORT_1)  = PFCE;
    PORT_REG_PM(GPIO_PORT_1) =PM;
    PORT_REG_P(GPIO_PORT_1)=P;
    PORT_REG_PIBC(GPIO_PORT_1)= PIBC;   

    /* Set IICB0SDA pins */
    PPCMD25  = 0xA5U;
    regdata = PODC25 | 0x00001000UL;
    PODC25  = regdata;
    PODC25  = (U32)(~regdata);
    PODC25  = regdata;
    PBDC25  |= 0x1000U;
    PFCE25  |= 0x1000U;
    PMC25   |= 0x1000U;
    PM25    &= 0xEFFFU;
    
    /* Set IICB0SCL pins */
    PPCMD25  = 0xA5U;
    regdata = PODC25 | 0x00002000UL;
    PODC25  = regdata;
    PODC25  = (U32)(~regdata);
    PODC25  = regdata;
    PBDC25  |= 0x2000U;
    PFCE25  |= 0x2000U;
    PMC25   |= 0x2000U;
    PM25    &= 0xDFFFU;

        /* Set CSIG0SC pin */
     /*P3_5,6,7*/
    FCLA24CTL0 = 0x80u;
    PFC3  |= 0x0020u;
    PFCE3 |= 0x0020u;
    PIPC3 |= 0x0020u;
    PMC3  |= 0x0020u;
    /* Set CSIG0SI pin */
    FCLA24CTL2 = 0x80u;
    PFC3  |= 0x0080u;
    PFCE3 |= 0x0080u;
    PMC3  |= 0x0080u;
    PM3   |= 0x0080u;
    /* Set CSIG0SO pin */
    PFC3  |= 0x0040u;
    PFCE3 |= 0x0040u;
    PIPC3 |= 0x0040u;
    PMC3  |= 0x0040u;
}


/***********************************************************************
*  Name        : port_setup_stop
*  Description :
*  Parameter   :
*  Returns     : None
***********************************************************************/
void Port_setup_sleep( void)
{


}

/***********************************************************************
*  Name        : port_setup_wakeup
*  Description :
*  Parameter   :
*  Returns     : None
***********************************************************************/
void Port_setup_wakeup( void)
{


}

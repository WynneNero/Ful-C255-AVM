/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   : Shao Guangxian										   *
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
*-----------------------------------------------------------------------
* 0.1	   Dec 02,2016   PEI Jingli  Initial version
*-----------------------------------------------------------------------
* 0.2          Dec 21,2016    PeiJingLi   Add Ds03h hw used int callback.
*----------------------------------------------------------------------
* 0.3           Jan 11,2017    ZhangJie   Add u for constant value to avoid Coverity warning.
*-----------------------------------------------------------------------
* 0.4      	    Jan 24,2017    ZhangJie     Remove unused include headfile.
*-----------------------------------------------------------------------
* 0.5          Mar 09,2017    PeiJingli   Delete test codes.
*=====================================================================*/
#include "Cpu.h"
#include "EXTI.h"
#include "EXTI_cfg.h"
#include "sys_assert_if.h"

/***********************************************************************
*  Name        : EXTI_Config
*  Description : INTP configration
*  Parameter   : exti_x can  select EXTI_00 ~ EXTI_15
                         exti_trigger  can select EXTI_TRIGGER_LOW  EXTI_TRIGGER_HIGH
                                        EXTI_TRIGGER_RISING EXTI_TRIGGER_FALLING
*  Returns     : None
***********************************************************************/
void EXTI_Config( EXTI_TYPE intp, EXTI_TRIGGER_TYPE exti_trigger )
{
    /* select trigger mode */
    U8 trig=0u ;
    U8 temp=0u;
    assert_param(IS_EXTI_TYPE(intp) );
    assert_param(IS_RANGE(exti_trigger,EXTI_TRIGGER_LOW,EXTI_TRIGGER_RISFALL) );

    while(temp<EXTI_NUM) /*get interruput ID*/
    {
      if(Intp_INT_Table[temp].intp==intp)
        break;
      temp++;
    }
    if(temp>=EXTI_NUM)
    { /* TODO ERROR*/
    }
    temp=Intp_INT_Table[temp].int_id;

    if(EXTI_TRIGGER_LOW==exti_trigger)
      trig= 0x04u; /* 100 */
    else if(EXTI_TRIGGER_HIGH==exti_trigger)
      trig= 0x05u; /* 101*/
    else if(EXTI_TRIGGER_RISING==exti_trigger)
      trig= 0x01u; /* 001*/
    else if(EXTI_TRIGGER_FALLING==exti_trigger)
      trig= 0x02u; 
    else/* if(EXTI_TRIGGER_RISFALL==exti_trigger)*/
      trig= 0x03u; 
    IRQ_IntDis(temp);  /*disable interrupt*/
    IRQ_IntClr (temp);

    /*  FCLA0TLn_INTP
    * bit[2]:  0 edge dect     1 level detect
    * bit[1]:  when edge  0 =Falling edge disabled   1=  Falling edge is enabled
    * bit[0]:  when edge, 0 =Raising edge disabled  1=  Raising edge is enabled
    *             when level edge dect,   0= low level  1= high level
    */
    GPIO_REG_FCLA0TLn_INTP(intp)= trig;
}

/***********************************************************************
*  Name        : EXTI_Cmd
*  Description : Set GPIO Pin  as a Input pin
*  Parameter   : exti_x can  select EXTI_00 ~ EXTI_15
                 state :ENABLE / DISABLE
*  Returns     : None
***********************************************************************/
void EXTI_Cmd( EXTI_TYPE intp, FUNCTION_STATE state )
{
    U8 temp=0u;
    assert_param(IS_EXTI_TYPE(intp) );
  
    while(temp<EXTI_NUM) /*get interruput ID*/
    {
      if(Intp_INT_Table[temp].intp==intp)
        break;
      temp++;
    }
    if(temp>=EXTI_NUM)
    { /*TODO ERROR*/
    }
    temp=Intp_INT_Table[temp].int_id;
    
    if( state != DISABLE )
    {
      IRQ_IntEn(temp);  
    }
    else
    {
      IRQ_IntDis(temp);
      IRQ_IntClr (temp);
    }
}

/***********************************************************************
*  Name        : ISR_INTP6_Handler
*  Description : Interruput ISR
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void ISR_INTP6_Handler(void)
{

    if( mcu_intp_callback[EXTI_06] != NULL )
    {
      mcu_intp_callback[EXTI_06]();
    }
}

/***********************************************************************
*  Name        : ISR_INTP3_Handler
*  Description : Interruput ISR
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void ISR_INTP3_Handler(void)
{

    if( mcu_intp_callback[EXTI_03] != NULL )
    {
      mcu_intp_callback[EXTI_03]();
    }
}


/**************** END OF FILE *****************************************/


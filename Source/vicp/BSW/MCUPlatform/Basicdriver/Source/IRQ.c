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
* ----------------------------------------------------------------------
* 0.1    Aug 01,2016 PEI Jingli  Iinitial version
* ----------------------------------------------------------------------
* 0.2    Nov 30,2016 PEI Jingli  Add interface
* ----------------------------------------------------------------------
* 0.3    Dec 09,2016 REN Weimin  Update after code review.
* ----------------------------------------------------------------------
* 0.4    Dec 09,2016 LIU Chenxi  Correct version conflcit during merge.
*------------------------------------------------------------------------
* 0.5    Jan 24,2017  ZhangJie  Fix Coverity warning.
*-----------------------------------------------------------------------
* 0.6    Apr 1,2017   PEI Jingli  Fix include files.
*=====================================================================*/
#include "Define.h"
#include "IRQ_IF.h"
#include "IRQ_cfg.h"
#include "IRQ.h"
#include "Iodefine.h"
#include "Os_cpu.h"


/*
*********************************************************************************************************
  *                                              IRQ_IntSourceAsign()
  *
  * Description : when 2 interruput sources are assigned to one interruput channel, selects which interruput source is enabled..
  *
  * Argument(s) : none
  *
  * Return(s)   : none.
  *
  * Note(s)     : none.
  *********************************************************************************************************
  */
void IRQ_IntSourceAsign(void)
{
/*this is a default setting. that is when one interrupt is related with more than one source, the 1st source*/
/*is used according to data sheet. */

#if(1)
    SELB_INTC1=0x0000u;
    SELB_INTC2=0x0000u;
#else
    SELB_INTC1=0xffffu;
    SELB_INTC2=0xffffu;
#endif
}

/*
*********************************************************************************************************
*                                              IRQ_Init_Setup()
*
* Description : Reserved, do nothing
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/
void  IRQ_Init_Setup (void)
{

    
}

/*
*********************************************************************************************************
*                                          IRQ_IntClr()
*
* Description : This function clears an interrupt
*
* Argument(s) : int_id        The interrupt ID
*
* Returns     : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  IRQ_IntClr (U16 int_id)
{
    if (int_id > IRQ_INT_ID_MAX) {
        return;
    }

    DEF_BIT_CLR(IRQ_INT_REG_ICxx(int_id), IRQ_INT_ICxx_EIRFn);
}


/*
*********************************************************************************************************
*                                             IRQ_IntDis()
*
* Description : This function disables an interrupt.
*
* Argument(s) : int_id        The interrupt id
*
* Returns     : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  IRQ_IntDis (U16  int_id)
{                                            
    if (int_id > IRQ_INT_ID_MAX) {
        return;
    }
    DEF_BIT_SET(IRQ_INT_REG_ICxx(int_id), IRQ_INT_ICxx_EIMKn);
}


/*
*********************************************************************************************************
*                                           IRQ_IntDisAll()
*
* Description : Clear ALL interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/
void  IRQ_IntClrAll(void)
{
  U16  int_id;
  
  for (int_id = 0u; int_id < IRQ_INT_ID_MAX; int_id++) {
    DEF_BIT_CLR(IRQ_INT_REG_ICxx(int_id), IRQ_INT_ICxx_EIRFn);
  }
}

void  IRQ_IntDisAll (void)
{
   MCU_DI();
}


/*
*********************************************************************************************************
*                                           IRQ_IntEnableAll()
*
* Description : Enable ALL interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/
void  IRQ_IntEnableAll (void)
{
   MCU_EI();
}


/*
*********************************************************************************************************
*                                          IRQ_IntEn()
*
* Description : This function enables an interrupt.
*
* Argument(s) : int_id        The interrupt id
*
* Returns     : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  IRQ_IntEn (U16  int_id)
{
    if (int_id > IRQ_INT_ID_MAX) {
        return;
    }

    DEF_BIT_CLR(IRQ_INT_REG_ICxx(int_id), IRQ_INT_ICxx_EIMKn);
    DEF_BIT_SET(IRQ_INT_REG_ICxx(int_id),IRQ_INT_ICxx_EITBn);			/*table refrence*/
}
   

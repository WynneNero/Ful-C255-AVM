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
* 
*=====================================================================*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include "IRQ.h"
#if 0
extern const IRQTable IRQ_IntVectTbl[USER_IRQ_NUM];
#endif
/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/
#define SELB_INTC1      (*(CPU_REG32 *)0xFFBC0300u)   // select a int source for 1 int channel
#define SELB_INTC2      (*(CPU_REG32 *)0xFFBC0304u)


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/




/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
  *                                              IRQ_IntSourceAsign()
  *
  * Description : Initialize interrupts:
  *
  * Argument(s) : when 2 interruput sources are assigned to one interruput channel, selects which interruput source is enabled..
  *
  * Return(s)   : none.
  *
  * Caller(s)   :
  *
  * Note(s)     : none.
  *********************************************************************************************************
  */
  #if 0

void IRQ_IntSourceAsign()
{
#ifdef SELB_INTC_1ST
    SELB_INTC1=0x0000u;
    SELB_INTC2=0x0000u;
#else
    SELB_INTC1=0xffffu;
    SELB_INTC2=0xffffu;
#endif
}
#endif
/*
*********************************************************************************************************
*                                              IRQ_Init_Setup()
*
* Description : Initialize interrupts:
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/
#if 0
void  IRQ_Init_Setup (void)
{
    U32  int_id;

    #if 0   /* used vector table */
     for (int_id = 0; int_id < IRQ_INT_ID_MAX; int_id++) 
    {
        IRQ_IntVectReg((U8   )int_id, (U8   )IRQ_INT_PRIO_LEVEL_07);
    }
#endif

    IRQ_IntSourceAsign(); //asign a int source to int channel wtich 2 sources.
}
#endif
/*
*********************************************************************************************************
*                                          IRQ_IntClr()
*
* Description : This function clears an interrupt
*
* Argument(s) : int_id        The interrupt ID
*                             BSP_INT_ID_ICWDTA0
*                             BSP_INT_ID_ICWDTA1
*                             BSP_INT_ID_ICLVI						
*                             BSP_INT_ID_ICCLMA0
*                                 .
*                                 .
*                             BSP_INT_ID_ICVI0FFO
* Returns     : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  IRQ_IntClr (U8  int_id)
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
*                             BSP_INT_ID_ICWDTA0
*                             BSP_INT_ID_ICWDTA1
*                             BSP_INT_ID_ICLVI						
*                             BSP_INT_ID_ICCLMA0
*                                   .
*                                   .
*                             BSP_INT_ID_ICVI0FFO
* Returns     : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  IRQ_IntDis (U8  int_id)
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
* Description : Disable ALL interrupts.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/
#if 0
void  IRQ_IntClrAll ()
{
  U32  int_id;
  
  for (int_id = 0; int_id < IRQ_INT_ID_MAX; int_id++) {
    DEF_BIT_CLR(IRQ_INT_REG_ICxx(int_id), IRQ_INT_ICxx_EIRFn);
  }
}

void  IRQ_IntDisAll (void)
{
    U32  int_id;

    for (int_id = 0; int_id < IRQ_INT_ID_MAX; int_id++) {
        DEF_BIT_SET(IRQ_INT_REG_ICxx(int_id), IRQ_INT_ICxx_EIMKn);
    }
}

#endif
/*
*********************************************************************************************************
*                                          IRQ_IntEn()
*
* Description : This function enables an interrupt.
*
* Argument(s) : int_id        The interrupt id
*                             BSP_INT_ID_ICWDTA0
*                             BSP_INT_ID_ICWDTA1
*                             BSP_INT_ID_ICLVI						
*                             BSP_INT_ID_ICCLMA0
*                                   .
*                                   .
*                             BSP_INT_ID_ICVI0FFO
* Returns     : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  IRQ_IntEn (U8  int_id)
{
    if (int_id > IRQ_INT_ID_MAX) {
        return;
    }

    DEF_BIT_CLR(IRQ_INT_REG_ICxx(int_id), IRQ_INT_ICxx_EIMKn);
    DEF_BIT_SET(IRQ_INT_REG_ICxx(int_id),IRQ_INT_ICxx_EITBn);			//table refrence
}


/*
*********************************************************************************************************
*                                            IRQ_IntVectReg()
*
* Description : Assign ISR handler.
*
* Argument(s) : int_id      Interrupt for which vector will be set.
*
*				prio		Interrupt priority level. 0(Highest) - 7(Lowest)
*
*               isr         Handler to assign
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/
#if 0
void  IRQ_IntVectReg (U8     int_id, U8     prio)
{

    //CPU_SR_ALLOC();
	

    if (int_id > IRQ_INT_ID_MAX) {
        return;
    }

    if (int_id < IRQ_INT_ID_MAX) {
        //CPU_CRITICAL_ENTER();
        MCU_DI();
		
        IRQ_INT_REG_ICxx(int_id) = prio;
        IRQ_IntDis(int_id);
		
	 MCU_EI();	
//        CPU_CRITICAL_EXIT();
    }
}
#endif
/*
*********************************************************************************************************
*                                        IRQ_IntHandlerDummy()
*
* Description : Dummy interrupt handler.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : IRQ_IntHandler().
*
* Note(s)     : none.
*********************************************************************************************************
*/
#if 0
static void  IRQ_IntHandlerDummy (void)
{

}
#endif
/*
*********************************************************************************************************
*                                        irq_handler()
*
* Description : General Maskable Interrupt handler.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : CPU_IntHandler().
*
* Note(s)     : none.
*********************************************************************************************************
*/
//void  IRQ_IntHandler (U32  src_nbr)
#if 0
void  IRQ_IntHandler (void)
{
	U32 src_nbr=0;
	
    Func_Void_Proc  isr=IRQ_IntHandlerDummy;
    U8 i;

//    src_nbr = osGetISRch();		
	
    src_nbr = (src_nbr - IRQ_INT_MASK_SRC_OFFSET_00); 		// / 16;
	
    if (src_nbr < IRQ_INT_ID_MAX) 
    {

	    for(i=0;i<USER_IRQ_NUM;i++)
	    {
	     if(src_nbr==IRQ_IntVectTbl[i].IRQNo)
	     {
	    	 isr= IRQ_IntVectTbl[i].isrproc;
		 break;
	     }
	   }	
		
	    if (isr != (Func_Void_Proc)0) 
	    {
	            isr();
	    }
   }
   
}
#endif

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
#include <IRQ_Cfg.h>

//============================================================================
// Includes
//============================================================================
extern void ISR_TAUD0I0func(void);
extern void CSIH1_Tx_handler( void );
extern void CSIH1_Rx_handler(void);
extern void ISR_OSTM0func(void);
extern void ISR_TAUJ1I0func(void);
extern void ISR_TAUJ0I0func(void);
extern void ISR_ADCA0_INTSG1func(void);
extern void ISR_IIC0TIfunc(void);
extern void ISR_IIC0TEIfunc(void);
extern void UART0_Tx_Handler(void);
extern void UART0_Rx_Handler(void);

const IRQTable IRQ_IntVectTbl[USER_IRQ_NUM]=
{

///TODO: SINCE IRQ TABLE IS NOT APPLIED, THEREFORE COMMENTS THESE ENTRY
/*
{INTOSTM0,ISR_OSTM0func},		// reserved for statistic, don't change this
{INTTAUJ0I0,ISR_TAUJ0I0func},
{INTTAUJ1I0,ISR_TAUJ1I0func},
{INTCSIH1IC,CSIH1_Tx_handler},
{INTCSIH1IR,CSIH1_Rx_handler},
{INTRLIN30UR0,UART0_Tx_Handler},
{INTRLIN30UR1,UART0_Rx_Handler},
{INTTAUD0I10,ISR_ADCA0_INTSG1func},
{INTRIIC0TI,ISR_IIC0TIfunc},
{INTRIIC0TEI,ISR_IIC0TEIfunc},
*/
};


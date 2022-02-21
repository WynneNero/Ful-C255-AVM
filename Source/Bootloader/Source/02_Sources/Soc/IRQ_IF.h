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
* ----------------------------------------------------------------------
* 0.1    Aug 01,2016    PEI Jingli  init
*=====================================================================*/

#ifndef _IRQ_IF_H_
#define _IRQ_IF_H_
#include "define.H"   

/**** Definition of constants ****/


/**** Definition of types ****/
typedef  void( *const MCU_EVENT_TYPE )( void );
typedef void( *const MCU_EVENT_TYPE1 )( U8 data );
typedef void( *const MCU_EVENT_TYPE2 )( U16 data );
/**** Definition of macros ****/
#define SCB_AIRCR_PRIGROUP    0x05FA0500

/**** Declaration of constants ****/


/**** Declaration of variables ****/


/**** Declaration of functions ****/
extern void IRQ_IntClr           (U8     int_id);
extern void IRQ_IntDis           (U8     int_id);
extern void IRQ_IntEn            (U8     int_id);
#if 0
extern void IRQ_Init_Setup (void);
extern void IRQ_IntVectReg       (U8     int_id,U8     prio);
extern void IRQ_IntDisAll        (void);
extern void  IRQ_IntClrAll        (void);
extern void IRQ_IntHandler       (void);
extern void IRQ_IntHandlerDummy (void);
#endif
#endif/*_IRQ_IF_H_*/
/****************************** END OF FILE ***************************/

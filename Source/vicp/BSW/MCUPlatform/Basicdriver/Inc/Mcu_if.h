/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   : 										       *
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
* 0.1    Jul 21,2016    PEI Jingli  Initial version
* ----------------------------------------------------------------------
* 0.2    Dec 20,2016  ShangQIuju remove other module used interface here.
* ----------------------------------------------------------------------
* 0.3    Dec 29,2016  PEI Jingli  Change for codeReview result  
* ----------------------------------------------------------------------
* 0.4    Jan 12,2017     ZhangJie  Fix Coverity warning.
*-----------------------------------------------------------------------
* 0.5    Jan 24,2017    ZhangJie     Remove unused include headfile.
*----------------------------------------------------------------------
* 0.6    Apr 01,2017    PEI Jingli     Fix include files.
*=====================================================================*/
#ifndef _MCU_IF_H_
#define _MCU_IF_H_
#include "Define.h"

/**** Definition of types ****/
/*
typedef  void( *const MCU_EVENT_TYPE )( void );
typedef void( *const MCU_EVENT_TYPE1 )( U8 data );
typedef void( *const MCU_EVENT_TYPE2 )( U64 data );
*/

/*mcu wakeup type */
typedef enum
{
    MCU_FULL_MODE,
    MCU_NOPLL_MODE
}MCU_WAKEUP_TYPE;

/*mcu sleep mode */
typedef enum
{
    MCU_STOP_MODE,
    MCU_DEEPSTOP_MODE   /*also deepstop, cyclic run,cyclic stop*/

}MCU_SLEEP_TYPE;

/* mcu reset type */
typedef enum
{
    MCU_RESET_BY_SW=0,   /*soft ware reset flag*/
    MCU_RESET_BY_WDTA0,/*windows watchdog A0 reset flag*/
    MCU_RESET_BY_WDTA1,/*windows watchdog A1 reset flag*/
    MCU_RESET_BY_CLMA0,/* clock monitor A0 reset flag*/
    MCU_RESET_BY_CLMA1,/* clock monitor A1 reset flag*/
    MCU_RESET_BY_CLMA2,/* clock monitor A2 reset flag*/
    MCU_RESET_BY_LVI,     /* low-voltage indicator reset flag*/ 
    MCU_RESET_BY_CVM,   /* core voltage monitors reset flag*/
    MCU_RESET_BY_EXTERNAL, /* external reset flag*/
    MCU_RESET_BY_POWERUP, /* powerupreset flag*/
    MCU_RESET_BY_DEEPSTOP, /* reset flag Deepstop mode */
    MCU_RESET_BY_NONE
}MCU_RESET_TYPE;

/**** Definition of macros ****/

/**** Declaration of functions ****/
extern void mcu_setup_high_clock( void );
extern void mcu_setup_low_clock( void );
extern void mcu_io_init_active( void );
extern void mcu_io_init_reset( void );
extern  void mcu_io_init_sleep( void );
extern  void mcu_io_init_wakeup(void);
extern void mcu_sw_reset( void );
extern void mcu_disable_all_interrupt(void);
extern void mcu_enable_all_interrupt(void);
extern void mcu_set_irq_table_address(U32 addr);
extern MCU_RESET_TYPE mcu_get_reset_reason( void );
extern void mcu_to_wakup_mode(MCU_WAKEUP_TYPE type);
extern void mcu_to_sleep_mode( MCU_SLEEP_TYPE type );
extern MCU_RESET_TYPE mcu_get_reset_flag( void );
#endif/*_MCU_IF_H_*/
/****************************** END OF FILE ***************************/

/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                
*                 All Rights Reserved.                                 
*   Department : CT AD                  
*   AUTHOR     :                                                       
************************************************************************
* Object        :  OSTM.h 
* Module        : OS timer operation
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
* 0.1  4 15,2016     Pei JL     Initial version
*------------------------------------------------------------------------
* 0.2  Jan 11,2017  ZhangJie  Add parentheses and add u for constant value to avoid Coverity warning.
*-----------------------------------------------------------------------
* 0.3  Apr 1,2017   PEI Jingli Fix include files.
===============================================================*/
#ifndef   OS_TM_H
#define   OS_TM_H
#include "Define.h"

/*def OSTMnCTL register params */
typedef enum
{
     E_INTVLTIM_MODE,
     E_FREERUN_MODE
}OSTMCTL_OPRTYPE;

/*def OSTMnTS/TT register params */
typedef enum
{
     E_STARTSTP_DIS,
     E_STARTSTP_EN
}OSTMTS_OPRTYPE;

/*get OSTMn enable or disable status */
#define IsOSTM0_ENBLED()    (OSTM0_REG_TE==0x01u) 
/* ------------------- OS TM0  REGISTERS ----------------- */
#define OSTM0_REG_BASEADD	 ((CPU_INT32U)(0xFFFC0000u))
#define OSTM0_REG_CMP      (*(CPU_REG32 *)((OSTM0_REG_BASEADD) + 0x0000u))
#define OSTM0_REG_CNT      (*(CPU_REG32 *)((OSTM0_REG_BASEADD) + 0x0004u))
#define OSTM0_REG_TE  		 (*(CPU_REG32 *)((OSTM0_REG_BASEADD) + 0x0010u))
#define OSTM0_REG_TS  		 (*(CPU_REG32 *)((OSTM0_REG_BASEADD) + 0x0014u))
#define OSTM0_REG_TT  		 (*(CPU_REG32 *)((OSTM0_REG_BASEADD) + 0x0018u))
#define OSTM0_REG_CTL      (*(CPU_REG32 *)((OSTM0_REG_BASEADD) + 0x0020u))
#define OSTM0_REG_EMU      (*(CPU_REG32 *)((OSTM0_REG_BASEADD) + 0x0024u))


void Ostm0_init(U32 pllclk_hz, U32  tick_per_sec, OSTMCTL_OPRTYPE opratMode, BOOL intEnble);
void Ostm0_start(void);
void Ostm0_stop(void);
void Ostm0_compare(U32 val );



#endif/*OS_TM_H*/

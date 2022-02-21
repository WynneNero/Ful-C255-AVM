/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.		           *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									                   *
************************************************************************
* Object        :  stbc_cfg.c 
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
* 0.1  Apr 15,2016   Pei JL      Initial. clock hand in MCU work mode
------------------------------------------------------------------------
* 0.2  Jun 29,2016   LIU Chenxi  Correct errors during merging
* ----------------------------------------------------------------------
* 0.3  Jun 29,2016   Pei JL      Add new entry Timer_tick_polling
* ----------------------------------------------------------------------
* 0.4  Aug 10,2016  PEI Jinglii  defined ISR callback array
* ----------------------------------------------------------------------
* 0.5  Aug 29,2016  PEI Jinglii  Add clock config for all channels.optimize stack using.
*----------------------------------------------------------------------
* 0.6  Dec 20,2016   ShangQiuju  remove unused files.
                                                 add config according using hw.
*------------------------------------------------------------------------
* 0.7 Jan 13,2017  ZhangJie  Fix Coverity warning.
 ----------------------------------------------------------------------
* 0.8  Jan 16,2017    RenWeimin  Add test code.  
*-----------------------------------------------------------------------
* 0.9  Jan 24,2017   ZhangJie   Fix Coverity warnings phase2.
*-----------------------------------------------------------------------
* 1.0  Feb 09,2017   ZhangJie   Remove EOL definition.
*-----------------------------------------------------------------------
* 1.1  Feb 15,2017   PEI Jingli   Fix codeReview results
*-----------------------------------------------------------------------
* 1.2  Feb 21,2017   PEI Jingli   Delete test switch
*-----------------------------------------------------------------------
* 1.3  Feb 22,2017   PEI Jingli   Fix warning
*-----------------------------------------------------------------------
* 1.4  Mar 08,2017   Zhang Jie  Config TAUJ1I0 for a 10us timer.
===============================================================*/
#include "TimerUnit.h"
#include "TimerUnit_cfg.h"

/*TODO: Copy an ds03 config file*/
/* for os tick*/
extern void OSAlarm_AlarmHook(void);
/* for service timer*/
extern void Timer_tick_polling(void);
extern void const CaptureTestDriver_GetValueISR( U64 data);
extern void TAUB0I11_timer_callback(U64 data);

#define TAUD0I7_CALLBACK(data)    CaptureTestDriver_GetValueISR(data)

void TAUD0I15_timer_callback(U64 Data);
/**   Set UNIT and channel of TAU to work as ostimer   **/
/**TAUD0_CH0 used CK2 as OSTimer, DO NOT CHANGE IT**/
BOOL  TAU_OSTIMER_SWH   = TRUE;   /*for temporary */
TAU_UNIT  TAU_FOR_OSTIMER                 = TAUD0_U2;  
TAU_CHANNEL TAUCHNL_FOR_OSTIMER =   TAU_CH15;

/* setting prescaler clock CK0,CK1,CK2,CK3 of all TAU  channels
*  TAUBn clcok is PERI2,     TAUDn clcok is PERI1
*  TAUJ0 clcok is ATAUJ ,     TAUJ1 clcok is PERI1
* CK0,CK1,CK2 frequency of channels = TAU clcok frequency/(TAU_CKx_PCLK_m multiplied by 2)
* CK3 frequency for TUAD and TAUJ= TAU clcok frequency/(ck_div multiplied by 2)/(ck3pre_div+1)
*
* ck0,ck1,ck2,ck3_div range (TAU_CKx_PCLK_0,TAU_CKx_PCLK_15)
* ck3pre_div range (0,255)
*/
const U8 tauCfg[TAU_U_MAX][5]=
{ /*ck0_div               ck1                  ck2                    ck3                      ck3pre_div for TUAD and TAUJ */  
#if (MCU_PIN >= PIN100)
  {TAU_CKx_PCLK_4, TAU_CKx_PCLK_2, TAU_CKx_PCLK_5, TAU_CKx_PCLK_10, 0},  /*taub0*/
#endif
#if (MCU_PIN == PIN176)
  {TAU_CKx_PCLK_4, TAU_CKx_PCLK_5, TAU_CKx_PCLK_5, TAU_CKx_PCLK_10, 0},  /*taub1*/
#endif   /**TAUD0_CH0 used CK2 as OSTimer, DO NOT CHANGE IT**/
  {TAU_CKx_PCLK_0, TAU_CKx_PCLK_0, TAU_CKx_PCLK_5, TAU_CKx_PCLK_15, 0},  /*tauD0*/
  {TAU_CKx_PCLK_0, TAU_CKx_PCLK_0, TAU_CKx_PCLK_0, TAU_CKx_PCLK_0  , 0},  /*tauJ0*/
#if (MCU_PIN >= PIN100)
  {TAU_CKx_PCLK_4, TAU_CKx_PCLK_4, TAU_CKx_PCLK_5, TAU_CKx_PCLK_10, 0}/*tauJ1*/
#endif
};

/*   all channels configration
* preCk if a channel as slave pwm mode and capture mode can not be CK3.
*/
const U8 tauChanlCfg[TAU_U_MAX][TAU_CH_MAX]=
{  /* unit          channel        CKn selected  */
#if (MCU_PIN >= PIN100)
     /* taub0 */  
   {E_CMOR_CK1,/*ch0*/
    E_CMOR_CK1, /*ch1*/
    E_CMOR_CK1, /* 2*/ 
    E_CMOR_CK1, /* 3*/
    E_CMOR_CK1, /* 4*/
    E_CMOR_CK1, /* 5*/
    E_CMOR_CK1, /* 6*/
    E_CMOR_CK1, /* 7*/ 
    E_CMOR_CK1, /* 8*/ 
    E_CMOR_CK1, /* 9*/ 
    E_CMOR_CK1, /* 10*/ 
    E_CMOR_CK1, /* 11*/ 
    E_CMOR_CK1, /* 12*/
    E_CMOR_CK1, /* 13*/
    E_CMOR_CK1, /* 14*/ 
    E_CMOR_CK1/* 15*/ 
   },
#endif
#if (MCU_PIN >= PIN176)
     /* taub1 */  
    {E_CMOR_CK1,/* ch0*/
     E_CMOR_CK1, /* ch1*/
     E_CMOR_CK1, /* 2 */
     E_CMOR_CK1, /* 3 */
     E_CMOR_CK1, /* 4 */
     E_CMOR_CK1, /* 5 */
     E_CMOR_CK1, /* 6 */
     E_CMOR_CK1, /* 7 */
     E_CMOR_CK1, /* 8 */
     E_CMOR_CK1, /* 9 */
     E_CMOR_CK1, /* 10 */ 
     E_CMOR_CK1, /* 11 */
     E_CMOR_CK1, /* 12 */
     E_CMOR_CK1, /* 13 */
     E_CMOR_CK1, /* 14 */
     E_CMOR_CK1 /* 15 */
    },
#endif
   /* taud0 */
  {E_CMOR_CK0,/* ch0*/ 
   E_CMOR_CK0, /*ch1*/
   E_CMOR_CK1, /* 2*/ 
   E_CMOR_CK1, /* 3*/
   E_CMOR_CK1, /* 4*/
   E_CMOR_CK1, /* 5*/
   E_CMOR_CK1, /* 6*/ 
   E_CMOR_CK1, /* 7*/ 
   E_CMOR_CK1, /* 8*/ 
   E_CMOR_CK1, /* 9*/ 
   E_CMOR_CK1, /* 10*/ 
   E_CMOR_CK1, /* 11*/ 
   E_CMOR_CK1, /* 12*/
   E_CMOR_CK1, /* 13*/
   E_CMOR_CK1, /* 14*/ 
   E_CMOR_CK2, /* 15*/ 
   },
   /* tauj0 */
 {E_CMOR_CK1,/* ch0*/
  E_CMOR_CK1, /*ch1*/
  E_CMOR_CK1, /* 2*/ 
  E_CMOR_CK1, /* 3*/
 }
#if (MCU_PIN >= PIN100)
 /* tauJ1 */  
 ,{E_CMOR_CK1,/*ch0*/
  E_CMOR_CK1, /*ch1*/
  E_CMOR_CK1, /* 2*/ 
  E_CMOR_CK1, /* 3*/
 }
#endif
};


/* set wakeup factors */
/*stop, chm,time,wkup or other,*/


/* In timer mode, input parameter is no useful.
 *  In capture mode, parameter is capture-value, 
 *      interval time= capture-value *(1/fre_hz), fre_hz can get by calling TAU_GetClolckFre_Channel() . 
 */
const Func_Param64_Proc tau_func_callback[TAU_U_MAX][TAU_CH_MAX]=
{
#if (MCU_PIN>=PIN100)  /*TAUB0_U0*/
   {NULL, NULL, NULL, NULL,
     NULL, NULL, NULL, NULL,
     NULL, NULL, NULL, TAUB0I11_timer_callback,
     NULL, NULL, NULL, NULL},
#endif 
  
#if(MCU_PIN==PIN176)  /*TAUB1_U1*/
   {NULL, NULL, NULL, NULL,
     NULL, NULL, NULL, NULL,
     NULL, NULL, NULL, NULL,
     NULL, NULL, NULL, NULL},
#endif 
  
   /*TAUD0_U2*/
  {NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, TAUD0I15_timer_callback},
   /*TAUJ0_U3*/
  {NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL}
#if(MCU_PIN>=PIN100)
  /*TAUJ1_U4*/
 ,{NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL}
#endif 
};

void TAUD0I15_timer_callback(U64 Data)
{
    OSAlarm_AlarmHook();

    Timer_tick_polling();
}

void TAUJ0I0_timer_callback(void)
{
    
}


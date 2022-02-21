/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				*
*				  All Rights Reserved.          			*
*   Department :       						*
*   AUTHOR	   : 					*
************************************************************************
* Object        :   Timer Array Unit B and D and J
* Module        :
* Instance      :
* Description   : named witch "TAU", just for TAUB and TAUD
*                       named witch "TAUJ", just for TAUJ
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
------------------------------------------------------------------------
* 0.1    Jun 26,2016   PEI Jingli  Initial version
------------------------------------------------------------------------
* 0.2    Jun 29,2016   LIU Chenxi  Correct errors during merging		
------------------------------------------------------------------------
* 0.3    July 07,2016  PEI Jingli  Adapt 64pin MCU
------------------------------------------------------------------------
* 0.4    July 07,2016  LIU Chenxi  merge with remotes/origin/ui4959_bs1
------------------------------------------------------------------------
* 0.5    July 21,2016  PEI Jingli  Refine code structure.
------------------------------------------------------------------------
* 0.6    Aug 10,2016  PEI Jingli  Add capture.Change timer inf and isr 
                         callback.
------------------------------------------------------------------------
* 0.7    Aug 26,2016  PEI Jingli  Refine capture,pwm code. optimize data structure.
* ----------------------------------------------------------------------
* 0.8    Sep 27,2016  PEI Jingli   Modify tau of ostimer ,and pwm
                                    Rename of interface
------------------------------------------------------------------------
* 0.9    Nov 10,2016  PEI Jingli    Add interface of Pwm-duty setting
------------------------------------------------------------------------
* 1.0    Dec 15,2016  PEI Jingli    Add dutyType params for PWM interfaces
------------------------------------------------------------------------
* 1.1    Dec 16,2016  PEI Jingli    Add return type for SetDuty interface ,add parameter checking
*-----------------------------------------------------------------------
* 1.2    Dec 20,2016  ShangQiuju Remove unused include files.
------------------------------------------------------------------------
* 1.3    Dec 20,2016  PEI Jingli  Correct errors of pwm,add return value to ERR_TYPE
* ----------------------------------------------------------------------
* 1.4    Dec 21,2016    PeiJingLi   Add Ds03h hw used int .
* ----------------------------------------------------------------------
* 1.5    Jan 11,2017     ZhangJie  Add Clock_if.h for complie warning and add parentheses 
                                    and add u for constant value to avoid Coverity warning,Add ISR_TAUJ1I0func interrupt function.
 ----------------------------------------------------------------------
* 1.6    Jan 16,2017    RenWeimin  Fix TAUJ bug. Add test code for capture.
*----------------------------------------------------------------------
* 1.7      Jan 24,2017    ZhangJie     Fix Coverity warning.
*----------------------------------------------------------------------
* 1.8      Feb 07,2017    ZhangJie     Remove unused CAN interrupt function definitation.
*----------------------------------------------------------------------
* 1.9      Feb 09,2017    PEI Jingli     Fix capture bugs of different edges.
*----------------------------------------------------------------------
* 2.0      Feb 10,2017    PEI Jingli     Add both-edges detection of capture .
*-----------------------------------------------------------------------
* 2.1      Feb 15,2017   PEI Jingli   Fix codeReview results
*-----------------------------------------------------------------------
* 2.2      Feb 21,2017   PEI Jingli   Delete test code.
*-----------------------------------------------------------------------
* 2.3      Feb 22,2017   PEI Jingli   Fix  TAUJ1 timer errors.
*-----------------------------------------------------------------------
* 2.4      Mar 08,2017   ZhangJie   Add us timer config function and interface to get system tick.
*-----------------------------------------------------------------------
* 2.5      Apr 13,2017   ZhangJie   Add mcu_pin switch.
*=====================================================================*/
#include "config.h"
#include "TimerUnit_cfg.h"
#include "TimerUnit.h"
#include "Sys_assert_if.h"
#include "Clock_cfg.h"
#include "IRQ_if.h"
#include "Clock_if.h"

static U16 Systemtick_10us = 0;

/**   Set UNIT and channel of TAU to work as ostimer   **/
extern BOOL  TAU_OSTIMER_SWH;   /*for temporary*/ 
extern TAU_UNIT  TAU_FOR_OSTIMER;
extern TAU_CHANNEL TAUCHNL_FOR_OSTIMER;

static BOOL IS_TAU_CHANNEL(TAU_UNIT un, TAU_CHANNEL chm);
static U32 TAUB_BASEADDR(TAU_UNIT un);
static BOOL tauTPSDivValue(U8 ck_div, U16 *val);
static BOOL getIntId_TAUChannel(TAU_UNIT un, TAU_CHANNEL chm, U16* int_id);
static BOOL isUnusedTAUChannel(TAU_UNIT un, TAU_CHANNEL chm);
static void  TAU_Channel_Start(TAU_UNIT un, TAU_CHANNEL channel);
static void  TAU_Channel_Stop(TAU_UNIT un, TAU_CHANNEL channel);


/*   TAU channels configration or operating states   */
typedef struct
{
    BOOL    isUsed;  /*channel used or idle*/
    BOOL    isLoop;  /*interruput once or not*/
    U8 mode;         /*function mode. enum CMOR_MD_TYPE*/
}TAU_CHNNELS_STATE_ST;

TAU_CHNNELS_STATE_ST allTauChannelCtrl[TAU_U_MAX][TAU_CH_MAX];

/*  interruput id of TAU channels
 related to TAU_UNIT
 interrupt id of unit_channel = stTAU2Int[unit *TAU_CH_MAX + channel]
*/
const U16 stTAU2Int[]=
{ /*Timer Unit     channel        interruput id */
    #if (MCU_PIN>=PIN100) /*TAUB0 16 channels*/
    INTTAUB0I0, INTTAUB0I1, INTTAUB0I2, INTTAUB0I3_PWGA16, INTTAUB0I4,INTTAUB0I5_PWGA17, INTTAUB0I6, INTTAUB0I7_PWGA18,
    INTTAUB0I8, INTTAUB0I9_PWGA19, INTTAUB0I10, INTTAUB0I11_PWGA26, INTTAUB0I12, INTTAUB0I13_PWGA30, INTTAUB0I14, INTTAUB0I15_PWGA31,
    #endif
    
    #if(MCU_PIN==PIN176)  /*TAUB1 16 channels*/
    INTTAUB1I0, INTTAUB1I1, INTTAUB1I2, INTTAUB1I3, INTTAUB1I4, INTTAUB1I5, INTTAUB1I6, INTTAUB1I7,
    INTTAUB1I8, INTTAUB1I9, INTTAUB1I10, INTTAUB1I11, INTTAUB1I12, INTTAUB1I13, INTTAUB1I14, INTTAUB1I15,
    #endif
     /*TAUD0 16 channels*/
    INTTAUD0I0, INTTAUD0I1, INTTAUD0I2, INTTAUD0I3, INTTAUD0I4, INTTAUD0I5, INTTAUD0I6, INTTAUD0I7, 
    INTTAUD0I8, INTTAUD0I9, INTTAUD0I10, INTTAUD0I11, INTTAUD0I12, INTTAUD0I13, INTTAUD0I14, INTTAUD0I15,
    /*TAUJ0 ,only 4 channels */
    INTTAUJ0I0, INTTAUJ0I1, INTTAUJ0I2, INTTAUJ0I3, IRQ_INT_ID_MAX, IRQ_INT_ID_MAX, IRQ_INT_ID_MAX, IRQ_INT_ID_MAX,  
    IRQ_INT_ID_MAX, IRQ_INT_ID_MAX, IRQ_INT_ID_MAX, IRQ_INT_ID_MAX, IRQ_INT_ID_MAX, IRQ_INT_ID_MAX, IRQ_INT_ID_MAX, IRQ_INT_ID_MAX,
    
    #if(MCU_PIN>=PIN100)
    /*TAUJ1 ,only 4 channels */
    INTTAUJ1I0, INTTAUJ1I1, INTTAUJ1I2, INTTAUJ1I3, IRQ_INT_ID_MAX, IRQ_INT_ID_MAX, IRQ_INT_ID_MAX, IRQ_INT_ID_MAX,  
    IRQ_INT_ID_MAX, IRQ_INT_ID_MAX, IRQ_INT_ID_MAX, IRQ_INT_ID_MAX, IRQ_INT_ID_MAX, IRQ_INT_ID_MAX, IRQ_INT_ID_MAX, IRQ_INT_ID_MAX,
    #endif
};

/* timer array unit is valid or not */
#define IS_TAU_UNIT(un)          ((un)<TAU_U_MAX)
/* tau and its channel is valid or not */
BOOL IS_TAU_CHANNEL(TAU_UNIT un, TAU_CHANNEL chm)
{ 
    BOOL bRet =FALSE;
    if((TAUD0_U2==un) &&(chm<TAU_CH_MAX) )
        bRet =TRUE;	
    else if((TAUJ0_U3==un) &&(chm<=TAU_CH3)) 
        bRet =TRUE;	
  #if (MCU_PIN>=PIN100) 
    else if((TAUB0_U0==un) &&(chm<TAU_CH_MAX) )
        bRet =TRUE;	
    else if((TAUJ1_U4==un) &&(chm<=TAU_CH3)) 
        bRet =TRUE;	
  #endif                           
  #if (MCU_PIN==PIN176) 
    else if((TAUB1_U1==un) &&(chm<TAU_CH_MAX) )
        bRet =TRUE;	
  #endif                       
    else 
        bRet =FALSE;

    return bRet;
}

/* Get base address of all TAU */
U32 TAUB_BASEADDR(TAU_UNIT un)
{
    U32 addr=0;    
    switch(un)
    {
#if (MCU_PIN>=PIN100)
    case TAUB0_U0:
        addr =TAUB0_REG_BASEADD;
        break;
#endif
    
#if(MCU_PIN==PIN176)
    case TAUB1_U1:
        addr =TAUB1_REG_BASEADD;
        break;
#endif 
    case TAUD0_U2:
        addr =TAUD0_REG_BASEADD;
        break;
    case TAUJ0_U3:
        addr =TAUJ0_REG_BASEADD;
        break;
#if (MCU_PIN>=PIN100)
    case TAUJ1_U4:
        addr =TAUJ1_REG_BASEADD;
        break;
#endif
    default: break;
    }
    return addr;
}

/* caculate prescaler clock CK0~CK3 divided  value(TAUnTPS).  
  value =TAU_CKx_PCLK_m multiplied by 2
*/
BOOL tauTPSDivValue(U8 ck_div, U16 *val)
{
    BOOL bRet =FALSE;
	
    if(ck_div<=TAU_CKx_PCLK_15)
    {
      switch(ck_div)  /* val= 2^ck_div */
      {
      case TAU_CKx_PCLK_0:
        *val=1;
        break;
      case TAU_CKx_PCLK_1:
        *val=2;
        break;
      case TAU_CKx_PCLK_2:
        *val=4;
        break;
      case TAU_CKx_PCLK_3:
        *val=8;
        break;
      case TAU_CKx_PCLK_4:
        *val=16;
        break;
      case TAU_CKx_PCLK_5:
        *val=32;
        break;
      case TAU_CKx_PCLK_6:
        *val=64;
        break;
      case TAU_CKx_PCLK_7:
        *val=128;
        break;
      case TAU_CKx_PCLK_8:
        *val=256;
        break;
      case TAU_CKx_PCLK_9:
        *val=512;
        break;
      case TAU_CKx_PCLK_10:
        *val=1024;
        break;
      case TAU_CKx_PCLK_11:
        *val=2048;
        break;
      case TAU_CKx_PCLK_12:
        *val=4096;
        break;
      case TAU_CKx_PCLK_13:
        *val=8192;
        break;
      case TAU_CKx_PCLK_14:
        *val=16384;
        break;
      case TAU_CKx_PCLK_15:
        *val=32768;
        break;
       
      default:
        break;
      }
    }
    if(*val>0)
        bRet =TRUE;
	
    return bRet;
}

/*get interruput id for a TAU channel */
BOOL getIntId_TAUChannel(TAU_UNIT un, TAU_CHANNEL chm, U16* int_id)
{
    BOOL bRet=FALSE;
	
    if(IS_TAU_CHANNEL(un,chm))
    {
        if( IRQ_INT_ID_MAX!=stTAU2Int[un*TAU_CH_MAX +chm] )
        {
            *int_id =stTAU2Int[un*TAU_CH_MAX +chm];
	      bRet =TRUE;
        }
    }

    return bRet;
}

/* check if the TAU channel be used */
BOOL isUnusedTAUChannel(TAU_UNIT un, TAU_CHANNEL chm)
{
    BOOL bRet=FALSE;
    if(IS_TAU_CHANNEL(un,chm))
    {
        if((TAU_OSTIMER_SWH)
         &&(un==TAU_FOR_OSTIMER) && (chm==TAUCHNL_FOR_OSTIMER)) /*ostimer used*/
        {
           /*FALSE*/
        }
        else
        {
           if(0)  /*allTauChannelCtrl[un][chm].isUsed)  maybe restarted without stopping*/
           {
           }
           else
           {
               bRet=TRUE;
           }
        }
    }
    return bRet;
}

/***********************************************************************************************************************
* Function Name: TAU_Timer_Start
* Description  : This function starts TAUB channel counter.can force to restart anytime.
* Parameters   : None
* Return Value : None
***********************************************************************************************************************/
void  TAU_Channel_Start(TAU_UNIT un, TAU_CHANNEL channel)
{
    if(TAUJ0_U3<=un) 
      TAU_REG_TAUJnTS(TAUB_BASEADDR(un))    |=((U8)(1<<channel));
    else
      TAU_REG_TAUBnTS(TAUB_BASEADDR(un)) |=((U16)(1<<channel));
}

/***********************************************************************************************************************
* Function Name: TAUB_Timer_Stop
* Description  : This function stop TAUB channel counter.can force to stop anytime.
* Parameters   : None
* Return Value : None
***********************************************************************************************************************/
void  TAU_Channel_Stop(TAU_UNIT un, TAU_CHANNEL channel)
{
  if(TAUJ0_U3<=un) 
  {
    TAU_REG_TAUJnTT(TAUB_BASEADDR(un))    |=((U8)(1<<channel));
  }
  else 
  {
    TAU_REG_TAUBnTT(TAUB_BASEADDR(un))   |=((U16)(1<<channel));
  }
}

/***********************************************************************************************************************
    * Function Name: TAU_IntervalTimer_Set
    * Description  :  Before timer start, Register Settings for independent channel  in TAUBTTINm Input Interval Timer Function.
    *  notes that TAUBnCMURm.TAUBnTIS[1:0] and the TAUBnCDRm register can be changed at any time during this function.
    * Parameters   : un  timer array unit index
    *                         chm channel index 0~15
    *                         ck   selected prescaler clock 0~3
    *                         cunt CDR register value.calculate interval time with supply clock frequency PERI1/2
    *                                       max value 0xffff for TAUB,TAUD 
    *                                       max value 0xffffffff for TAUJ
    *                         isLoop   
    * Return Value : None
***********************************************************************************************************************/
void TAU_IntervalTimer_Set(TAU_UNIT un, TAU_CHANNEL chm, CMOR_CKTYPE ck,U32 count, BOOL isOut,BOOL isLoop)
{
    U32 baseAddress =TAUB_BASEADDR(un);
    if(TAUJ0_U3<=un)
    {
        /* Setting cycle. Data register for the capture/compare value */
        TAU_REG_TAUJnCDR(baseAddress, chm) =count;
        /* TAUJnCMORm      - TAUJn Channel Mode OS Register
        b15:b14           TAUJnCKS    - Selects an operation clock.                  - Selected Operation CK
        b 4:b 1           TAUJnMD     - Specifies an operating mode.                 - Interval timer mode. Set to 0000'b
        b 0               TAUJnMD0    - Specifies whether INTTAUJnIm is generated at the beginning of count operation or not.        
                                                                     - INTTAUDnIm is not generated. Set to 0'b */
        TAU_REG_TAUJnCMOR(baseAddress, chm) = (U16)(TAUB_CLOCK_SELECT_CK(ck)|(E_MODE_INTERVAL_TIMER|E_MD0_NOINT));  
     
        /* Specifies the type of valid edge detection used for the TAUDTTINm input. */
        TAU_REG_TAUJnCMUR(baseAddress, chm) =(U8)E_TAUB_TIS_EDGE_FALLING;
    
        /* The simultaneous rewrite registers (TAUDnTOM, TAUDnTOC, TAUDnTOL, TAUDnTDE , TAUDnTDM , TAUDnTDL
           TAUDnTRE, TAUDnTRO, TAUDnTRC, TAUDnTME) cannot be used with the Interval Timer Function.
           Therefore, these registers must be set to 0. */
        TAU_REG_TAUJnTOM(baseAddress) &=(U8)TAUB_OUTPUT_INDEPENDENT(chm); /*0 independent*/
        TAU_REG_TAUJnTOC(baseAddress) &=(U8)TAUB_OUTPUT_VALUE_0(chm); /*0 low*/
        TAU_REG_TAUJnTOL(baseAddress) &=(U8)(~(1u<<chm));
    
        /* Disable or enable  the channel output mode. If enabled a square wave with 50% duty is output  */
        if(isOut)
          TAU_REG_TAUJnTOE(baseAddress)  |=(U8)(1u<<chm); /* 1:enable */
        else
          TAU_REG_TAUJnTOE(baseAddress)  &=(U8)(~(1u<<chm)); /* disable */
    
    
        /* The simultaneous rewrite registers (TAUDnRDE, TAUDnRDS, TAUDnRDM, and TAUDnRDC)
           cannot be used with the Interval Timer Function. Therefore, these registers must be set to 0. */
        TAU_REG_TAUJnRDE(baseAddress) &=(U8)(~(1u<<chm)); /*0: Disables simultaneous rewrite*/
        TAU_REG_TAUJnRDM(baseAddress) &=(U8)(~(1u<<chm));
        
        allTauChannelCtrl[un][chm].isLoop=isLoop;
        allTauChannelCtrl[un][chm].isUsed=TRUE;
    }
    else
    {
        TAU_REG_TAUBnCMORm(baseAddress,chm)=(U16)(TAUB_CLOCK_SELECT_CK(ck)|(E_MODE_INTERVAL_TIMER|E_MD0_NOINT));  /*interval timer func*/
        TAU_REG_TAUBnCMURm(baseAddress,chm)=(U8)E_TAUB_TIS_EDGE_FALLING;
        if(isOut)
          TAU_REG_TAUBnTOE(baseAddress)  |=(U16)(1u<<chm); /*1:enable output*/
        else
          TAU_REG_TAUBnTOE(baseAddress)  &=(U16)(~(1u<<chm)); /*disable output*/
        TAU_REG_TAUBnTOM(baseAddress) &=(U16)TAUB_OUTPUT_INDEPENDENT(chm); /*0 independent*/
        TAU_REG_TAUBnTOC(baseAddress) &=(U16)TAUB_OUTPUT_VALUE_0(chm); /*0 low*/
        TAU_REG_TAUBnTOL(baseAddress) &=(U16)(~(1u<<chm)); /*0 Positive logic*/
        TAU_REG_TAUBnTDE(baseAddress) &=(U16)(~(1u<<chm)); /*0 Disables*/
        TAU_REG_TAUBnTRE(baseAddress) &=(U16)(~(1u<<chm)); 
        TAU_REG_TAUBnTRO(baseAddress) &=(U16)(~(1u<<chm)); 
        TAU_REG_TAUBnTRC(baseAddress) &=(U16)(~(1u<<chm)); 
        TAU_REG_TAUBnTME(baseAddress) &=(U16)(~(1u<<chm)); 
        if(TAUD0_U2==un)
          TAU_REG_TAUBnTDM(baseAddress) &=(U16)(~(1u<<chm)); /*0 Disables*/    
        TAU_REG_TAUBnTDL(baseAddress) &=(U16)(~(1u<<chm)); /*0 Positive phase period*/
        /* Setting cycle with Data register for the capture/compare value
        TAUBnCDRm  TAUDnCDRm     :16bit   */
        TAU_REG_TAUBnCDRm(baseAddress,chm) =(U16)count;
         /* Simultaneous rewrite reg cannot be used */
        TAU_REG_TAUBnRDE(baseAddress) &=(U16)(~(1u<<chm)); /*0: Disables simultaneous rewrite*/
        TAU_REG_TAUBnRDS(baseAddress) &=(U16)(~(1u<<chm));
        TAU_REG_TAUBnRDM(baseAddress) &=(U16)(~(1u<<chm));
        TAU_REG_TAUBnRDC(baseAddress) &=(U16)(~(1u<<chm));
   
        /* select 1 source for the interruput channel with 2 sources */
        /*always 0. do nothing.*/
        /*if(SELB_INTC_1ST)  set bit as 0*/
        /*	SELB_INTC1			   &= 0xFFEFU;*/			 /* INTTAUD0I0(ch.0) / INTCSIH2IC(ch.124) */
        /* else      set bit as 1  */
        /*	SELB_INTC1			   &= 0xFFEFU;*/			 /* INTTAUD0I0(ch.124)	*/
         
        allTauChannelCtrl[un][chm].isLoop=isLoop;
        allTauChannelCtrl[un][chm].isUsed=TRUE;
    }
}
	
/******************************************************************************
* Function Name : TAU_PWM_Config
* Description   : Select channels, set period and duty of PWM wave.Without interrupt.
* Argument     : un unit number
*               chm select a master channel 
*            sl_chm  select a slave channel
*             freHZ  frequency of PWM wave by hz
*       RatioType  decide the wave precision
*              duty  high-level duty is to (duty/RatioType)
* Return Value  : none
******************************************************************************/
ERR_TYPE TAU_PWM_Config (TAU_UNIT un, TAU_CHANNEL chm, TAU_CHANNEL sl_chm, U32 freHZ, U16 RatioType, U16 duty )
{
    U64 count_master=0u;  /*CDR,for period*/
    U64 count_slave=0u;    /*CDR, for low level*/
    ERR_TYPE eRet=ERR_OK;
    U32 fre =0;
    
    if( (!isUnusedTAUChannel(un,chm)) ||(!isUnusedTAUChannel(un,sl_chm)) ||(duty>RatioType))
    {
        eRet=ERR_VALUE;
    }
    else  if( !(chm<sl_chm) || (chm%2u!=0u) || (tauChanlCfg[un][chm]!=tauChanlCfg[un][sl_chm]))
    {
      /* master chm should be an even number,slave sl_chm be larger than master chm. They work at  clock frequecy. */
      eRet=ERR_RANGE;
    }
    else
    {
        if(ERR_OK!=TAU_GetClolckFre_Channel(un, chm, &fre) || (freHZ>=fre)) /*not support */
        {
          eRet=ERR_NOTAVAIL;
        }
        else
        {
        /* calculate CDR counter. no large than U32 */
            count_master= (U64)fre/freHZ-1;
            if( (TAUJ0_U3==un) 
      #if(MCU_PIN>=PIN100)
               ||(TAUJ1_U4==un)
      #endif
              )
            {
                if(count_master==0 || count_master>0xffffffff)
                    eRet=ERR_VALUE;
            }
            else if(count_master==0 || count_master>0xffff)
                eRet=ERR_VALUE;
            
            if(ERR_OK==eRet)
            {
                if( (duty==RatioType) &&( ((0xffff==count_master) &&(TAUJ0_U3>un)) /* when full high level, TAUB/D CDR registers reach to max value  */
                  ||((0xffffffff==count_master) &&(TAUJ0_U3<=un)) ) ) /* TAUJ CDR registers reach to max value */ 
                {
                    count_slave=count_master; /*defect: with 0~100 ns low level*/
                    /*TODO:set slave channel as GPIO output mode, then set P register to 1. */
                }
                else
                {
                    count_slave= (count_master+1)*duty/RatioType;  /*high level*/
                }

                /*---set configration ---*/
                if( un>=TAUJ0_U3 )
                {        
                    /*set cycle */     
                    TAU_REG_TAUJnCDR(TAUB_BASEADDR(un),chm) =(U32)count_master; 
                    /* master: set CK , Interval timer mode, INTTAUDnIm generated */
                    TAU_REG_TAUJnCMOR(TAUB_BASEADDR(un),chm)=TAUB_CLOCK_SELECT_CK(tauChanlCfg[un][chm])
                                                                          |(TAUB_MASTER_SELECT(E_MASTER))|(E_MODE_INTERVAL_TIMER|E_MD0_INT); 
                    TAU_REG_TAUJnCMUR(TAUB_BASEADDR(un),chm)=E_TAUB_TIS_EDGE_FALLING;  /*unused*/
                    /* Master chanel settings */
                    TAU_REG_TAUJnTOM(TAUB_BASEADDR(un)) &=(~(1u<<chm)); /*0 independent*/
                    TAU_REG_TAUJnTOC(TAUB_BASEADDR(un)) &=(~(1u<<chm)); /*0 low*/
                    TAU_REG_TAUJnTOL(TAUB_BASEADDR(un)) &=(~(1u<<chm)); /*0 Positive logic*/
                    TAU_REG_TAUJnTOE(TAUB_BASEADDR(un))  &=(~(1u<<chm)); /*set 0,disable output.*/
                    //Simultaneous rewrite reg cannot be used
                    TAU_REG_TAUJnRDE(TAUB_BASEADDR(un)) &=(~(1u<<chm)); /*0: Disables simultaneous rewrite*/
                    TAU_REG_TAUJnRDM(TAUB_BASEADDR(un)) &=(~(1u<<chm));
              
                    /* set slave cycle */
                    TAU_REG_TAUJnCDR(TAUB_BASEADDR(un),sl_chm) =(U32)count_slave;
                    /* slave:    set CK1 ,INTTAUnIm of master channel is a start trigger .One-count mode, INTTAUnIm generated */
                    TAU_REG_TAUJnCMOR(TAUB_BASEADDR(un),sl_chm)=TAUB_CLOCK_SELECT_CK(tauChanlCfg[un][sl_chm])
                                                                          |(TAUB_MASTER_SELECT(E_SLAVE))|TAUB_TRIGGER_SELECT(E_TRIG_MASTER_INT)
                                                                          |(E_MODE_ONE_COUNT|E_MD0_INT);
                    TAU_REG_TAUJnCMUR(TAUB_BASEADDR(un),sl_chm)=E_TAUB_TIS_EDGE_FALLING; 
                    /* Slave chanel settings */
                    TAU_REG_TAUJnTOM(TAUB_BASEADDR(un)) |=TAUB_OUTPUT_ISYNC(sl_chm); 
                    TAU_REG_TAUJnTOC(TAUB_BASEADDR(un)) &=TAUB_OUTPUT_VALUE_0(sl_chm); /*0 low*/
                    TAU_REG_TAUJnTOL(TAUB_BASEADDR(un)) &=(~(1u<<sl_chm)); /*0 Positive logic*/
                       
                    TAU_REG_TAUJnTOE(TAUB_BASEADDR(un))  |=(1u<<sl_chm); /* Enable the channel output*/
                    /*Simultaneous rewrite reg cannot be used*/
                    TAU_REG_TAUJnRDE(TAUB_BASEADDR(un)) &=(~(1u<<sl_chm)); /*0: Disables simultaneous rewrite*/
                    TAU_REG_TAUJnRDM(TAUB_BASEADDR(un)) &=(~(1u<<sl_chm));
                }
                else
                {
                    /* Master chanel settings */
                    TAU_REG_TAUBnCDRm(TAUB_BASEADDR(un),chm) =(U16)count_master;
                    TAU_REG_TAUBnCMORm(TAUB_BASEADDR(un),chm)=TAUB_CLOCK_SELECT_CK(tauChanlCfg[un][chm])
                                                                          |(TAUB_MASTER_SELECT(E_MASTER))|(E_MODE_INTERVAL_TIMER|E_MD0_INT); 
                    TAU_REG_TAUBnCMURm(TAUB_BASEADDR(un),chm)=E_TAUB_TIS_EDGE_FALLING;  /*unused*/
                    TAU_REG_TAUBnTOM(TAUB_BASEADDR(un)) &=(~(1u<<chm)); /*0 independent*/
                    TAU_REG_TAUBnTOC(TAUB_BASEADDR(un)) &=(~(1u<<chm)); /*0 low*/
                    TAU_REG_TAUBnTOL(TAUB_BASEADDR(un)) &=(~(1u<<chm)); /*0 Positive logic*/
                    TAU_REG_TAUBnTDE(TAUB_BASEADDR(un)) &=(~(1u<<chm)); /*0 Disables*/
                    if(TAUD0_U2==un)
                      TAU_REG_TAUBnTDM(TAUB_BASEADDR(un)) &=(~(1u<<chm)); /*0 Disables */
                    TAU_REG_TAUBnTDL(TAUB_BASEADDR(un)) &=(~(1u<<chm));
                    
                    TAU_REG_TAUBnTRE(TAUB_BASEADDR(un)) &=(~(1u<<chm)); 
                    TAU_REG_TAUBnTRC(TAUB_BASEADDR(un)) &=(~(1u<<chm)); 
                    TAU_REG_TAUBnTRO(TAUB_BASEADDR(un)) &=(~(1u<<chm)); 
                    TAU_REG_TAUBnTME(TAUB_BASEADDR(un)) &=(~(1u<<chm)); 
                    TAU_REG_TAUBnTOE(TAUB_BASEADDR(un))  &=(~(1u<<chm)); /*set 0,disable output.*/
                    //Simultaneous rewrite reg cannot be used
                    TAU_REG_TAUBnRDE(TAUB_BASEADDR(un)) &=(~(1u<<chm)); /*0: Disables simultaneous rewrite*/
                    TAU_REG_TAUBnRDS(TAUB_BASEADDR(un)) &=(~(1u<<chm));
                    TAU_REG_TAUBnRDM(TAUB_BASEADDR(un)) &=(~(1u<<chm));
                    TAU_REG_TAUBnRDC(TAUB_BASEADDR(un)) &=(~(1u<<chm));
              
                    /* Slave chanel settings */
                    TAU_REG_TAUBnCDRm(TAUB_BASEADDR(un),sl_chm) =(U16)count_slave;
                    TAU_REG_TAUBnCMORm(TAUB_BASEADDR(un),sl_chm)=TAUB_CLOCK_SELECT_CK(tauChanlCfg[un][sl_chm])
                                                                          |(TAUB_MASTER_SELECT(E_SLAVE))|TAUB_TRIGGER_SELECT(E_TRIG_MASTER_INT)
                                                                          |(E_MODE_ONE_COUNT|E_MD0_INT);
                    TAU_REG_TAUBnCMURm(TAUB_BASEADDR(un),sl_chm)=E_TAUB_TIS_EDGE_FALLING; 
                    TAU_REG_TAUBnTOM(TAUB_BASEADDR(un)) |=TAUB_OUTPUT_ISYNC(sl_chm); 
                    TAU_REG_TAUBnTOC(TAUB_BASEADDR(un)) &=TAUB_OUTPUT_VALUE_0(sl_chm); /*0 low*/
                    TAU_REG_TAUBnTOL(TAUB_BASEADDR(un)) &=(~(1u<<sl_chm)); /*0 Positive logic*/
                    TAU_REG_TAUBnTDE(TAUB_BASEADDR(un)) &=(~(1u<<sl_chm)); /*0: Disables simultaneous rewrite*/
                    TAU_REG_TAUBnTDM(TAUB_BASEADDR(un)) &=(~(1u<<sl_chm));
                    TAU_REG_TAUBnTDL(TAUB_BASEADDR(un)) &=(~(1u<<sl_chm));
                    TAU_REG_TAUBnTRE(TAUB_BASEADDR(un)) &=(~(1u<<sl_chm));
                    TAU_REG_TAUBnTRC(TAUB_BASEADDR(un)) &=(~(1u<<sl_chm)); 
                    TAU_REG_TAUBnTRO(TAUB_BASEADDR(un)) &=(~(1u<<sl_chm)); 
                    TAU_REG_TAUBnTME(TAUB_BASEADDR(un)) &=(~(1u<<sl_chm)); 
                    
                    TAU_REG_TAUBnTOE(TAUB_BASEADDR(un))  |=(1u<<sl_chm); /* Enable the channel output */
                    //Simultaneous rewrite reg cannot be used
                    TAU_REG_TAUBnRDE(TAUB_BASEADDR(un)) &=(~(1u<<sl_chm)); /*0: Disables simultaneous rewrite*/
                    TAU_REG_TAUBnRDS(TAUB_BASEADDR(un)) &=(~(1u<<sl_chm));
                    TAU_REG_TAUBnRDM(TAUB_BASEADDR(un)) &=(~(1u<<sl_chm));
                    TAU_REG_TAUBnRDC(TAUB_BASEADDR(un)) &=(~(1u<<sl_chm));
                }
            }      
        }  
      
    }  
    return eRet;
}
  
/******************************************************************************
* Function Name : TAU_PWM_Cmd
* Description   : Enable or disable a PWM function. Interrupts are not necessary. 
* Argument     : un unit number
*               chm select a master channel 
*          sl_chm  select a slave channel
*            state  start or stop
* Return Value  : none
******************************************************************************/
BOOL TAU_PWM_Cmd(TAU_UNIT un, TAU_CHANNEL chm, TAU_CHANNEL sl_chm, FUNCTION_STATE state)
{
    if(state)
    {
         TAU_Channel_Start(un,chm);
         TAU_Channel_Start(un,sl_chm);
         allTauChannelCtrl[un][chm].isLoop=TRUE;
         allTauChannelCtrl[un][chm].isUsed=TRUE;
         allTauChannelCtrl[un][chm].mode =(U8)E_MODE_INTERVAL_TIMER;
         allTauChannelCtrl[un][sl_chm].isLoop=TRUE;
         allTauChannelCtrl[un][sl_chm].isUsed=TRUE;
         allTauChannelCtrl[un][sl_chm].mode =(U8)E_MODE_ONE_COUNT;
    }
    else
    {
        if( allTauChannelCtrl[un][chm].isLoop)
        {
          TAU_Channel_Stop(un,chm);
        }
        
        if( allTauChannelCtrl[un][sl_chm].isLoop)
        {
          TAU_Channel_Stop(un,sl_chm);
        }
        allTauChannelCtrl[un][chm].isLoop=FALSE;
        allTauChannelCtrl[un][chm].isUsed=FALSE;
        allTauChannelCtrl[un][chm].mode =(U8)0;
        allTauChannelCtrl[un][sl_chm].isLoop=FALSE;
        allTauChannelCtrl[un][sl_chm].isUsed=FALSE;
        allTauChannelCtrl[un][sl_chm].mode =(U8)0;
    }
    return TRUE;
}

/******************************************************************************
* Function Name : TAU_PWM_SetDuty
* Description   : Set wave duty without stop pwm function
* Argument     : un unit number
*               chm select a master channel 
*            sl_chm  select a slave channel
*        RatioType  decide the wave precision
*               duty  high-level duty is to (duty/RatioType)
* Return Value  : none
******************************************************************************/
ERR_TYPE TAU_PWM_SetDuty (TAU_UNIT un, TAU_CHANNEL chm, TAU_CHANNEL sl_chm, U16 ratioType, U16 duty )
{
    ERR_TYPE eRet=ERR_OK;
    U64 count_master=0;  /*CDR,for period*/
    U64 count_slave=0;    /*CDR, for low level*/
    
    if( (!isUnusedTAUChannel(un,chm)) ||(!isUnusedTAUChannel(un,sl_chm)) ||(duty>ratioType))
        eRet=ERR_VALUE;

    /*1.Master channel has the same clock frequecy with slave channel. */
    if( (ERR_OK==eRet)&&(tauChanlCfg[un][chm]!=tauChanlCfg[un][sl_chm]))
        eRet=ERR_NOTAVAIL;

    if(ERR_OK==eRet)
    {
        /* Get counter register value of master channel, just as clock frequency */
        if(un<TAUJ0_U3)
          count_master=TAU_REG_TAUBnCDRm(TAUB_BASEADDR(un),chm);
        else
          count_master=TAU_REG_TAUJnCDR(TAUB_BASEADDR(un),chm);
      
        if( (duty==ratioType) &&( ((0xffff==count_master) &&(TAUJ0_U3>un)) /* when full high level, TAUB/D CDR registers reach to max value */
          ||((0xffffffff==count_master) &&(TAUJ0_U3<=un)) ) ) /* TAUJ CDR registers reach to max value */
        {
            count_slave=count_master; /*defect: with 0~100 ns low level*/
            /*TODO:set slave channel as Timer mode. */
        }
        else
        {
            count_slave= (count_master+1)*duty/ratioType;  /*high level*/
        }
    
        /*---set configration ---*/
        if( un>=TAUJ0_U3 )
        {        
            /* set slave cycle*/
            TAU_REG_TAUJnCDR(TAUB_BASEADDR(un),sl_chm) =(U32)count_slave;
        }
        else
        {
            /* Slave chanel settings */
            TAU_REG_TAUBnCDRm(TAUB_BASEADDR(un),sl_chm) =(U16)count_slave;
        }
    }
        
    return eRet;
}
 
 /******************************************************************************
 * Function Name : TAU_Capture_Config
 * Description   : do  the configrations of a capture channel
 * Argument     : un  TAU_UNIT, select timer array unit
 *                      chm  TAU_CHANNEL. for TAUJ, TAU_CH0~TAU_CH3
 *                                  for TAUB and TAUD, TAU_CH0~TAU_CH15
 *                       edge  CAP_TYPE_ST
 *                               E_CAP_PERIOD_FALLING, pulse interval measurement
 *                               E_CAP_PERIOD_RISING,  pulse interval measurement
 *                               E_CAP_WIDTH__FALL_RISE ,low-high width measurement  
 *                               E_CAP_WIDTH_RISE_FALL ,high-low width measurement
 *                          E_CAP_ALL_EDGE_DETECT,  just for both risine edge and falling edge detecting, measurement is unvalid
 *
 *  ck fre ,TAU_GetClolckFre_Channel()
 *  input pulse width: 
 *    if TAUJ  max_s= (1/ck fre)s *(0xffffffff+1)
 *    else     max_s= (1/ck fre)s *(0xffff+1)
 * Return Value  : none
 ******************************************************************************/ 
ERR_TYPE TAU_Capture_Config (TAU_UNIT un, TAU_CHANNEL chm, CAP_TYPE_ST edge)
{
    ERR_TYPE eRet=ERR_OK;

    if( (!isUnusedTAUChannel(un,chm)) || (edge>E_TAUB_BOTH_EDGE_DETECT))
        eRet = ERR_VALUE;
    else
    {
        /*filter  settings*/
    #if(MCU_PIN>=PIN100)
        if(TAUB0_U0==un)
        {
          TAU_REG_DNFATAUB0ICTL          = 0x00u;  
          TAU_REG_DNFATAUB0IEN           |= (U16)(1<<chm); /* 1enable*/
        }
        else
    #endif
        if(TAUD0_U2==un)
        {
          TAU_REG_DNFATAUD0ICTL          = 0x00u;  
          TAU_REG_DNFATAUD0IEN           |= (U16)(1<<chm);
        }
    #if(MCU_PIN==PIN176)
        else if(TAUB1_U1==un)
        {
          TAU_REG_DNFATAUB1ICTL          = 0x00u;  
          TAU_REG_DNFATAUB1IEN           |= (U16)(1<<chm);
        }
    #endif
     
        if(TAUJ0_U3<=un)
        {
            /*set configration*/
            if((edge<=E_CAP_PERIOD_RISING)||(edge==E_CAP_ALL_EDGE_DETECT))
            {
                TAU_REG_TAUJnCMOR(TAUB_BASEADDR(un),chm)=TAUB_CLOCK_SELECT_CK(tauChanlCfg[un][chm])|TAUB_TRIGGER_SELECT(E_TRIG_TIN_VALID)
                                                |TAUB_CAPTURE_UPDATE(E_CMOR_UPDATE1) |(E_MODE_CAPTURE |E_MD0_NOINT);  /*capture mode*/
            }
            else
            {
                TAU_REG_TAUJnCMOR(TAUB_BASEADDR(un),chm)=TAUB_CLOCK_SELECT_CK(tauChanlCfg[un][chm])|TAUB_TRIGGER_SELECT(E_TRIG_TIN_BOTH)
                                                |TAUB_CAPTURE_UPDATE(E_CMOR_UPDATE1) |(E_MODE_CAPTURE_ONE_COUNT |E_MD0_NOINT);  /* one-count capture mode */
            }
            if(edge==(U8)E_CAP_ALL_EDGE_DETECT)   /* both edge detect */     
                TAU_REG_TAUJnCMUR(TAUB_BASEADDR(un),chm)=(U8)E_TAUB_TIS_EDGE_FALL_RISE;  
            else
                TAU_REG_TAUJnCMUR(TAUB_BASEADDR(un),chm)=edge;  
            TAU_REG_TAUJnTOE(TAUB_BASEADDR(un))  &=(~(1u<<chm)); /*set 0,disable output.*/
            /*Simultaneous rewrite reg cannot be used*/
            TAU_REG_TAUJnRDE(TAUB_BASEADDR(un)) &=(~(1u<<chm)); /*0: Disables simultaneous rewrite*/
            TAU_REG_TAUJnRDM(TAUB_BASEADDR(un)) &=(~(1u<<chm));
        }
        else
        {
            /*set configration*/
            if((edge<=E_CAP_PERIOD_RISING)||(edge==E_CAP_ALL_EDGE_DETECT))
            {
                TAU_REG_TAUBnCMORm(TAUB_BASEADDR(un),chm)=TAUB_CLOCK_SELECT_CK(tauChanlCfg[un][chm])|TAUB_TRIGGER_SELECT(E_TRIG_TIN_VALID)
                                             |TAUB_CAPTURE_UPDATE(E_CMOR_UPDATE1) |(E_MODE_CAPTURE |E_MD0_NOINT);
            }
            else
            {
                TAU_REG_TAUBnCMORm(TAUB_BASEADDR(un),chm)=TAUB_CLOCK_SELECT_CK(tauChanlCfg[un][chm])|TAUB_TRIGGER_SELECT(E_TRIG_TIN_BOTH)
                                             |TAUB_CAPTURE_UPDATE(E_CMOR_UPDATE1) |(E_MODE_CAPTURE_ONE_COUNT |E_MD0_NOINT);
            }
            if(edge==(U8)E_CAP_ALL_EDGE_DETECT)   /* both edge detect */ 
                TAU_REG_TAUBnCMURm(TAUB_BASEADDR(un),chm)=(U8)E_TAUB_TIS_EDGE_FALL_RISE; 
            else
                TAU_REG_TAUBnCMURm(TAUB_BASEADDR(un),chm)=edge;  
            TAU_REG_TAUBnTOE(TAUB_BASEADDR(un))  &=(~(1u<<chm)); /*set 0,disable output.*/
            /*Simultaneous rewrite reg cannot be used*/
            TAU_REG_TAUBnRDE(TAUB_BASEADDR(un)) &=(~(1u<<chm)); /*0: Disables simultaneous rewrite*/
            TAU_REG_TAUBnRDS(TAUB_BASEADDR(un)) &=(~(1u<<chm));
            TAU_REG_TAUBnRDM(TAUB_BASEADDR(un)) &=(~(1u<<chm));
            TAU_REG_TAUBnRDC(TAUB_BASEADDR(un)) &=(~(1u<<chm));
        }
     
        /* select 1 source for the interruput channel with 2 sources */
        /*always 0. do nothing.*/
        /*if(SELB_INTC_1ST)*/   /*set bit as 0*/
        /*  SELB_INTC1         &= 0xFFEFU; */      /* INTTAUD0I0(ch.0) / INTCSIH2IC(ch.124) */
        /* else*/  /*set bit as 1*/
        /*  SELB_INTC1         &= 0xFFEFU; */      /* INTTAUD0I0(ch.124)  */
    }
    
    return eRet;
}

/******************************************************************************
* Function Name : TAU_Capture_Cmd
* Description   : enable or disable a capture channel. The interrupt of the channel is needed.
* Argument     : 
* Return Value  : none
******************************************************************************/ 
BOOL TAU_Capture_Cmd(TAU_UNIT un, TAU_CHANNEL chm, FUNCTION_STATE state)
{
    U16 int_id=0;

    getIntId_TAUChannel(un, chm, &int_id);
    if(state)
    {
        IRQ_IntEn(int_id);
        TAU_Channel_Start(un, chm);
        allTauChannelCtrl[un][chm].isLoop=TRUE;
        allTauChannelCtrl[un][chm].isUsed=TRUE;
        allTauChannelCtrl[un][chm].mode =(U8)E_MODE_CAPTURE;
    }
    else
    {
        IRQ_IntDis(int_id);
        IRQ_IntClr(int_id);
        TAU_Channel_Stop(un, chm);
        allTauChannelCtrl[un][chm].isLoop=FALSE;
        allTauChannelCtrl[un][chm].isUsed=FALSE;
        allTauChannelCtrl[un][chm].mode =(U8)0;
    }
    return TRUE;
}

/* Get prescaler clock frequecy of unit. *fre = xx HZ */
static ERR_TYPE TAU_getCKFrequecy(TAU_UNIT un, CMOR_CKTYPE ck, U32 *fre)
{
  U16 divVal=0;
  U32 value=-0;
  ERR_TYPE eRet =ERR_OK;
  
  if(!IS_TAU_UNIT(un) ||(ck>=E_CMOR_CK_MAX) || (NULL==fre))
    eRet =ERR_VALUE;
  if( tauCfg[un][ck]>TAU_CKx_PCLK_15)
    eRet =ERR_RANGE;

  if(ERR_OK==eRet)
  {
    tauTPSDivValue(tauCfg[un][ck],&divVal);
    /* ck3_pre divider for TAUDn and TAUJn*/
    if((ck==E_CMOR_CK3) &&( (un>=TAUD0_U2) && (un<=TAU_U_MAX) ))
    {        
      divVal *=(U16)(1+tauCfg[un][4]);
    }

    /* pclock frequency */
    if(TAUD0_U2 ==un)    
      value=PERI1_CLKDOMAIN_HZ; /*D0->PERI1*/
    else if(TAUJ0_U3 ==un)         /* J0->ATAUJ*/
      value=Clock_GetFrequency_ATAUJ();
  #if MCU_PIN>=PIN100
    else if(TAUB0_U0 ==un)
      value=PERI2_CLKDOMAIN_HZ; /* ->PERI2*/
    else if(TAUJ1_U4 ==un)
      value=PERI1_CLKDOMAIN_HZ; /*->PERI1*/
  #endif
  #if MCU_PIN==PIN176
    else if(TAUB1_U1 ==un)
      value=PERI2_CLKDOMAIN_HZ; /*->PERI2*/
  #endif
  
    /* caculate prescaler clock frequecy*/
    *fre  =value/divVal;
    if(0==*fre)
      eRet =ERR_UNDERFLOW; /*frequecy=0 err*/
    else
      eRet =ERR_OK;
  }  

  return eRet;
}

/* get clock frequecy of a tau channel.*fre = xx HZ  */
ERR_TYPE TAU_GetClolckFre_Channel( TAU_UNIT un, TAU_CHANNEL chm, U32 *fre)
{
    CMOR_CKTYPE ck=(CMOR_CKTYPE)tauChanlCfg[un][chm];
    return TAU_getCKFrequecy(un,ck,fre);   
}

U16 TAU_GetSystemTick_10us(void)
{
    return Systemtick_10us;
}
 
 /***-----                         TAU ISR                          -----***/
 /***********************************************************************
 *  Name        : ISR_TAUB0I0func
 *  Description : TAUB0I0 interruput isr 
 *  Parameter   :
 *  Returns     : None
 ***********************************************************************/
 void ISR_TAUB0I0func(void)
 { 
#if (MCU_PIN>=PIN100)
     /* callback */
     if(tau_func_callback[TAUB0_U0][TAU_CH0]!=NULL)
       tau_func_callback[TAUB0_U0][TAU_CH0](0);

     if(!(allTauChannelCtrl[TAUB0_U0][TAU_CH0].isLoop))
       TAU_REG_TAUBnTT(TAUB_BASEADDR(TAUB0_U0)) |= (1<<TAU_CH0);
#endif          
 }

void ISR_TAUJ0I0func(void) 
{
    /* callback */
    if(tau_func_callback[TAUJ0_U3][TAU_CH0]!=NULL)
      tau_func_callback[TAUJ0_U3][TAU_CH0](0);

    if(!(allTauChannelCtrl[TAUJ0_U3][TAU_CH0].isLoop))
      TAU_REG_TAUJnTT(TAUB_BASEADDR(TAUJ0_U3)) |= (1<<TAU_CH0);
}

void ISR_TAUJ1I0func(void)		/* 10us*/
{
    /*Systemtick_10us must be added in the timer isr which was configured as a 10us timer*/
    Systemtick_10us++;
     /* callback */
 #if(MCU_PIN>=PIN100)
    if(tau_func_callback[TAUJ1_U4][TAU_CH0]!=NULL)
      tau_func_callback[TAUJ1_U4][TAU_CH0](0);

    if(!(allTauChannelCtrl[TAUJ1_U4][TAU_CH0].isLoop))
      TAU_REG_TAUJnTT(TAUB_BASEADDR(TAUJ1_U4)) |= (1<<TAU_CH0);
 #endif
}

void ISR_TAUJ1I3func(void)		/*capture, P8_12*/
{
#if(MCU_PIN>=PIN100)
  U64 data=0;
  U32 fre=0;
  /* TAUDTTINm input pulse interval = 
     count clock cycle * [(TAUDnCSRm.TAUDnOV F * (FFFFH + 1)) + TAUDnCDRm capture value + 1] */
  if((allTauChannelCtrl[TAUJ1_U4][TAU_CH3].mode ==(U8)E_MODE_CAPTURE) 
  ||(allTauChannelCtrl[TAUJ1_U4][TAU_CH3].mode ==(U8)E_MODE_CAPTURE_ONE_COUNT) )
  {
      if(TAU_REG_TAUJnCSR(TAUJ1_REG_BASEADD,TAU_CH3) &0x01)  /*overflow*/
      {
        data= ((0xFFFFFFFF + 1) + TAU_REG_TAUJnCDR(TAUJ1_REG_BASEADD,TAU_CH3)  + 1);
        TAU_REG_TAUJnCSC(TAUJ1_REG_BASEADD,TAU_CH3) =1;   /*clear overflow flag*/
      }
      else
      {
        data=TAU_REG_TAUJnCDR(TAUJ1_REG_BASEADD,TAU_CH3)  + 1;
      }
      /* caculate pulse interval by us */
      if(ERR_OK==TAU_GetClolckFre_Channel(TAUJ1_U4, TAU_CH3, &fre))
      {
        data =data*1000000/fre;
      }
  }
  else
  {}
  
  if(NULL!=tau_func_callback[TAUJ1_U4][TAU_CH3])
    tau_func_callback[TAUJ1_U4][TAU_CH3]((U64)data);
#endif
}

/***********************************************************************
*  Name        : ISR_TAUD0I15func
*  Description :  TAUD0I0 ISR, used as system tick
*  Parameter   :  none
*  Returns     : none
***********************************************************************/
void ISR_TAUD0I15func(void)
{
   /* callback */

  if(NULL!=tau_func_callback[TAUD0_U2][TAU_CH15])
   (tau_func_callback[TAUD0_U2][TAU_CH15])(0);

  /*if(!(allTauChannelCtrl[TAUD0_U2][TAU_CH0].isLoop))  os time cannot stop*/
  /*  TAUD0.TT                      |= (1<<TAU_CH0);*/

}

void ISR_TAUD0I6func(void)
{
}

#if 0
void ISR_TAUJ1I2func(void)
{
  U64 data=0;
  U32 fre=0;
  /* TAUDTTINm input pulse interval = 
     count clock cycle * [(TAUDnCSRm.TAUDnOV F * (FFFFH + 1)) + TAUDnCDRm capture value + 1] */
  if((allTauChannelCtrl[TAUJ1_U4][TAU_CH2].mode ==(U8)E_MODE_CAPTURE) 
  ||(allTauChannelCtrl[TAUJ1_U4][TAU_CH2].mode ==(U8)E_MODE_CAPTURE_ONE_COUNT) )
  {
      if(TAUD0.CSR7 &0x01)  /*overflow*/
      {
        data= (((U32)0xFFFF + 1) + (U32)TAUD0.CDR7 + 1);
        TAUD0.CSC7=1;   /*clear overflow flag*/
      }
      else
        data= ( (U32) TAUD0.CDR7 + 1);

      /* caculate pulse interval by us */
      if(TAU_GetClolckFre_Channel(TAUD0_U2, TAU_CH7, &fre))
        data =data*1000000/fre;
  }
  else
  {}
  
  if(NULL!=tau_func_callback[TAUD0_U2][TAU_CH7])
    tau_func_callback[TAUD0_U2][TAU_CH7]((U64)data);

}
#endif

void ISR_TAUJ1I2func(void)		/*capture, P8_12*/
{
#if(MCU_PIN>=PIN100)
  U64 data=0;
  U32 fre=0;
  /* TAUDTTINm input pulse interval = 
     count clock cycle * [(TAUDnCSRm.TAUDnOV F * (FFFFH + 1)) + TAUDnCDRm capture value + 1] */
  if((allTauChannelCtrl[TAUJ1_U4][TAU_CH2].mode ==(U8)E_MODE_CAPTURE) 
  ||(allTauChannelCtrl[TAUJ1_U4][TAU_CH2].mode ==(U8)E_MODE_CAPTURE_ONE_COUNT) )
  {
      if(TAU_REG_TAUJnCSR(TAUJ1_REG_BASEADD,TAU_CH2) &0x01)  /*overflow*/
      {
        data= ((0xFFFFFFFF + 1) + TAU_REG_TAUJnCDR(TAUJ1_REG_BASEADD,TAU_CH2)  + 1);
        TAU_REG_TAUJnCSC(TAUJ1_REG_BASEADD,TAU_CH2) =1;   /*clear overflow flag*/
      }
      else
      {
        data=TAU_REG_TAUJnCDR(TAUJ1_REG_BASEADD,TAU_CH2)  + 1;
      }
      /* caculate pulse interval by us */
      if(ERR_OK==TAU_GetClolckFre_Channel(TAUJ1_U4, TAU_CH2, &fre))
      {
        data =data*1000000/fre;
      }
  }
  else
  {}
  
  if(NULL!=tau_func_callback[TAUJ1_U4][TAU_CH2])
    tau_func_callback[TAUJ1_U4][TAU_CH2]((U64)data);
#endif
}

void ISR_TAUB0I11func(void)
{
	U64 data=0;
	U32 fre=0;
	/* TAUDTTINm input pulse interval = 
	 count clock cycle * [(TAUDnCSRm.TAUDnOV F * (FFFFH + 1)) + TAUDnCDRm capture value + 1] */
	if((allTauChannelCtrl[TAUB0_U0][TAU_CH11].mode ==(U8)E_MODE_CAPTURE) 
	||(allTauChannelCtrl[TAUB0_U0][TAU_CH11].mode ==(U8)E_MODE_CAPTURE_ONE_COUNT) )
	{
		if(TAU_REG_TAUJnCSR(TAUB0_REG_BASEADD,TAU_CH11) &0x01)  /*overflow*/
		{
			data= ((0xFFFFFFFF + 1) + TAU_REG_TAUJnCDR(TAUB0_REG_BASEADD,TAU_CH11)  + 1);
			TAU_REG_TAUJnCSC(TAUB0_REG_BASEADD,TAU_CH11) =1;   /*clear overflow flag*/
		}
		else
		{
			data=TAU_REG_TAUJnCDR(TAUB0_REG_BASEADD,TAU_CH11)  + 1;
		}
		/* caculate pulse interval by us */
		if(ERR_OK==TAU_GetClolckFre_Channel(TAUB0_U0, TAU_CH11, &fre))
		{
			data =data*10000000/fre;
		}
	}
	else
	{}

	if(NULL!=tau_func_callback[TAUB0_U0][TAU_CH11])
	tau_func_callback[TAUB0_U0][TAU_CH11]((U64)data);
}

/******************************************************************************
* Function Name : void TAU_OSTimer_Init( void )
* Description   : configrate a TAU channel as os timer (interval timer function).
* Argument      : osc_freq -supply clock frequency, in Hz
           	           tick_time - unit:0.1ms						
* Return Value  : none
* note: possible time interval: min 1ms, max ~50ms
******************************************************************************/
BOOL TAU_OSTimer_Init(U32 osc_freq, U32 tick_time )
{
    U32 src_fre=0;  
    U64 count=0;
    TAU_UNIT un=TAU_FOR_OSTIMER;
    TAU_CHANNEL chm=TAUCHNL_FOR_OSTIMER;
    BOOL bRet =TRUE
    ;
    if(!IS_TAU_CHANNEL(un,chm))
       bRet =FALSE;  
    else
    {
        /* calculate count by millisecond */
        if(ERR_OK!=TAU_GetClolckFre_Channel(un, chm, &src_fre))
        {
            bRet =FALSE;  
        }
        else
        {
            /* check MS_count
            *  count_1ms= src_fre*1ms/1000/div_val-1 
            *  MAX_MS= (CDR_MAX+1) *1000*(stTauTPS[ck_div].val) /src_fre
            */    
            count= (U64)src_fre*tick_time/10000 -1;
            if( (TAUJ0_U3==un) 
        #if(MCU_PIN>=PIN100)
                     ||(TAUJ1_U4==un)
        #endif
                    )
           {
                  if(count==0 || count>0xffffffff)
                       bRet =FALSE; 
           }
           else if(count==0 || count>0xffff)
           {
               bRet =FALSE; 
           }

           if(bRet)
           {
                   TAU_IntervalTimer_Set(un, chm,
                                                    (CMOR_CKTYPE)tauChanlCfg[un][chm],(U16) count, FALSE,FALSE);
           }
       }
    }  
    return bRet;    
}

void TAU_OSTimer_Cmd(BOOL enable)
{
    U16 int_id=0u;
    getIntId_TAUChannel(TAU_FOR_OSTIMER, TAUCHNL_FOR_OSTIMER, &int_id);

    if(enable)
    {
        IRQ_IntEn(int_id);
        TAU_Channel_Start(TAU_FOR_OSTIMER, TAUCHNL_FOR_OSTIMER);
        allTauChannelCtrl[TAU_FOR_OSTIMER][TAUCHNL_FOR_OSTIMER].isLoop=TRUE;
        allTauChannelCtrl[TAU_FOR_OSTIMER][TAUCHNL_FOR_OSTIMER].isUsed=TRUE;
        allTauChannelCtrl[TAU_FOR_OSTIMER][TAUCHNL_FOR_OSTIMER].mode =(U8)E_MODE_INTERVAL_TIMER;
    }
    else
    {
        IRQ_IntDis(int_id);
        IRQ_IntClr(int_id);
        TAU_Channel_Stop(TAU_FOR_OSTIMER, TAUCHNL_FOR_OSTIMER);
        allTauChannelCtrl[TAU_FOR_OSTIMER][TAUCHNL_FOR_OSTIMER].isLoop=FALSE;
        allTauChannelCtrl[TAU_FOR_OSTIMER][TAUCHNL_FOR_OSTIMER].isUsed=FALSE;
        allTauChannelCtrl[TAU_FOR_OSTIMER][TAUCHNL_FOR_OSTIMER].mode =(U8)E_MODE_INVALID;
    }
}

/***********************************************************************
*  Name        : TAU_setup_init
*  Description : all TAU initializing. 
*              stop all channel, set prescaler clock of TAU which will be used.
*  Parameter  : tauCfg[TAU_U_MAX][],   tau configration info
*  Returns     : None
***********************************************************************/
void TAU_setup_init()
{
    U8 index=0;
    for(;index<TAU_U_MAX; index++)
    {
        if(!IS_RANGE(tauCfg[index][0],TAU_CKx_PCLK_0,TAU_CKx_PCLK_15) || !IS_RANGE(tauCfg[index][1],TAU_CKx_PCLK_0,TAU_CKx_PCLK_15)
       || !IS_RANGE(tauCfg[index][2],TAU_CKx_PCLK_0,TAU_CKx_PCLK_15) || !IS_RANGE(tauCfg[index][3],TAU_CKx_PCLK_0,TAU_CKx_PCLK_15))
        {  /*tauCfg[][] errors */
        }
        else
        {
            if(TAUJ0_U3 <=index)
            {
                TAU_REG_TAUJnTT(TAUB_BASEADDR((TAU_UNIT)index))=(U8)TAU_CHALL_STOP_TRG_ON;

                TAU_REG_TAUJnTPS(TAUB_BASEADDR((TAU_UNIT)index)) =((U16)tauCfg[index][0]) |(((U16)tauCfg[index][1])<<4) 
                                                                                                         | (((U16)tauCfg[index][2])<<8) |(((U16)tauCfg[index][3])<<12);
                TAU_REG_TAUJnBRS((TAU_UNIT)index) =(U8)tauCfg[index][4];
            }
            else
            {
                TAU_REG_TAUBnTT(TAUB_BASEADDR((TAU_UNIT)index))=TAU_CHALL_STOP_TRG_ON;
                TAU_REG_TAUBnTPS(TAUB_BASEADDR((TAU_UNIT)index)) =((U16)tauCfg[index][0]) | (((U16)tauCfg[index][1])<<4) 
                                                                                                                       | (((U16)tauCfg[index][2])<<8) |(((U16)tauCfg[index][3])<<12);
                if(index>=TAUD0_U2)
                  TAU_REG_TAUBnBRS((TAU_UNIT)index) =(U8)tauCfg[index][4];
            }
        }
    }	
 }

/***********************************************************************
*  Name        : TAU_setup_deinit
*  Description :before sleep,deinit TAU
*  Parameter   :
*  Returns     : None
***********************************************************************/
void TAU_setup_deinit()
{
    /*timer,pwm,capture stop*/
    
    /*if needed, set TAUJ0Im in standby mode*/
    /* chnl,time,if as wakeup factor*/
    /*if(DOMAIN_ATAUJ_STPMSK)*/
    {}
}

/***********************************************************************
*  Name        : TAU_Timer_Config
*  Description : initialize an independent interval timerr. 
*  Parameter   : un  TAU_UNIT, select timer array unit
*                      chm  TAU_CHANNEL. for TAUJ, TAU_CH0~TAU_CH3
*                                  for TAUB and TAUD, TAU_CH0~TAU_CH15
*             MS_count  interval time by millisecond.
*                     TAUB0, select ck0, fre=PERI2/(2^ck0_div),  max time is XXX ms.
*                     TAUD0, select ck0, fre=PERI2/(2^ck0_div),  max time is XXX ms.
*                     TAUJ0, select ck0, fre=TAUJ_domain/(2^ck0_div),  max time is XXX ms.
*                        should not be ck3, no input.
*            bWaveOutput  timer output enable or not.
                    FALSE just as an internal timer
                    TRUE  as a timer, generate a square wave on the specified pin
*            bPeriodic timer operating cyclic or not. 
*  Returns     : None
***********************************************************************/
ERR_TYPE TAU_Timer_Config(TAU_UNIT un, TAU_CHANNEL chm, U32 MS_count, BOOL bWaveOutput, BOOL bPeriodic)
{
    U32 src_fre=0u;  
    U64 count=0u;
    ERR_TYPE eRet =ERR_OK;
    
    if( !isUnusedTAUChannel(un,chm))
        eRet =ERR_VALUE;
    /* calculate count by millisecond */
    if(ERR_OK!=TAU_GetClolckFre_Channel(un, chm, &src_fre))
        eRet =ERR_RANGE;
    else
    {
        /* check MS_count
        *  count_1ms= src_fre*1ms/1000/div_val-1 
        *  MAX_MS= (CDR_MAX+1) *1000*(stTauTPS[ck_div].val) /src_fre
        */    
        count= (U64)src_fre*MS_count/1000u -1u;
        if( (TAUJ0_U3==un) 
    #if(MCU_PIN>=PIN100)
               ||(TAUJ1_U4==un)
    #endif
              )
       {
            if(count==0u || count>0xffffffff)
              eRet =ERR_RANGE;
       }
       else if(count==0u || count>0xffff)
            eRet =ERR_RANGE;
  }

  if(eRet==ERR_OK)
  {
      TAU_IntervalTimer_Set(un, chm,
                                      (CMOR_CKTYPE)tauChanlCfg[un][chm], (U32)count, bWaveOutput,bPeriodic);
  }
    return eRet;    
}

ERR_TYPE TAU_Timer_Config_US(TAU_UNIT un, TAU_CHANNEL chm, U32 US_count, BOOL bWaveOutput, BOOL bPeriodic)
{
    U32 src_fre=0u;  
    U64 count=0u;
    ERR_TYPE eRet =ERR_OK;
    
    if( !isUnusedTAUChannel(un,chm))
        eRet =ERR_VALUE;
    /* calculate count by millisecond */
    if(ERR_OK!=TAU_GetClolckFre_Channel(un, chm, &src_fre))
        eRet =ERR_RANGE;
    else
    {
        /* check MS_count
        *  count_1ms= src_fre*1ms/1000/div_val-1 
        *  MAX_MS= (CDR_MAX+1) *1000*(stTauTPS[ck_div].val) /src_fre
        */    
        count= (U64)src_fre*US_count/1000000u -1u;
        if( (TAUJ0_U3==un) 
    #if(MCU_PIN>=PIN100)
               ||(TAUJ1_U4==un)
    #endif
              )
       {
            if(count==0u || count>0xffffffff)
              eRet =ERR_RANGE;
       }
       else if(count==0u || count>0xffff)
            eRet =ERR_RANGE;
  }

  if(eRet==ERR_OK)
  {
      TAU_IntervalTimer_Set(un, chm,
                                      (CMOR_CKTYPE)tauChanlCfg[un][chm], (U32)count, bWaveOutput,bPeriodic);
  }
    return eRet;    
}

/*Enable or disable a timer*/
BOOL TAU_Timer_Cmd(TAU_UNIT un, TAU_CHANNEL chm, FUNCTION_STATE state)
{
    U16 int_id=0u;

    getIntId_TAUChannel(un, chm, &int_id);

    if(state)
    {
        IRQ_IntEn(int_id);
        TAU_Channel_Start(un, chm);
        allTauChannelCtrl[un][chm].isLoop=TRUE;
        allTauChannelCtrl[un][chm].isUsed=TRUE;
        allTauChannelCtrl[un][chm].mode =(U8)E_MODE_INTERVAL_TIMER;
    }
    else
    {
        IRQ_IntDis(int_id);
        IRQ_IntClr(int_id);
        TAU_Channel_Stop(un, chm);
        allTauChannelCtrl[un][chm].isLoop=FALSE;
        allTauChannelCtrl[un][chm].isUsed=FALSE;
        allTauChannelCtrl[un][chm].mode =(U8)0;
    }
    return TRUE;
}


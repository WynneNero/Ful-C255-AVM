/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				*
*				  All Rights Reserved.          			*
*   Department : RN R&D SW1      						*
*   AUTHOR	   : 					*
************************************************************************
* Object        : Timer Unit Array as TAUB0 ,TAUB1, TAUD0, TAUJ0, TAUJ1
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
------------------------------------------------------------------------
* 0.1	   Jun 26,2016   PEI Jingli  Initial version
*------------------------------------------------------------------------
* 0.2	   July 21,2016  PEI Jingli  Refine code structure.
*------------------------------------------------------------------------
* 0.3          Jan 11,2017  ZhangJie  Add parentheses and add u for constant value to avoid Coverity warning.
 ----------------------------------------------------------------------
* 0.4    	   Jan 16,2017   RenWeimin  Fix bug for TAUJ.
*-----------------------------------------------------------------------
* 0.5          Jan 24,2017   ZhangJie   Remove unused include file.
*-----------------------------------------------------------------------
* 0.6          Feb 10,2017   PEI Jingli   Add both-edge dectection of capture
*-----------------------------------------------------------------------
* 0.7          Feb 15,2017   PEI Jingli   Fix codeReview results
*=====================================================================*/


/*============================================================================
 Includes
============================================================================*/
#ifndef   _TIMERUNIT_H
#define   _TIMERUNIT_H
#include "cpu.h"

/*
    TAU Bn/Dn prescaler clock select register (TAUBnTPS TAUDnTPS)
*/
/* Specifies the CK0~CK3 clock (TAUBnPRSx[3:0]) */
#define TAU_CKx_PCLK_0                   (0u) /* CK0~3 - PCLK/1 */
#define TAU_CKx_PCLK_1                   (1u) /* CK0~3 - PCLK/2^1 */
#define TAU_CKx_PCLK_2                   (2u) /* CK0~3 - PCLK/2^2 */
#define TAU_CKx_PCLK_3                   (3u) /* CK0~3 - PCLK/2^3 */
#define TAU_CKx_PCLK_4                   (4u) /* CK0~3 - PCLK/2^4 */
#define TAU_CKx_PCLK_5                   (5u) /* CK0~3 - PCLK/2^5 */
#define TAU_CKx_PCLK_6                   (6u) /* CK0~3 - PCLK/2^6 */
#define TAU_CKx_PCLK_7                   (7u) /* CK - PCLK/2^7 */
#define TAU_CKx_PCLK_8                   (8u) /* CK - PCLK/2^8 */
#define TAU_CKx_PCLK_9                   (9u) /* CK - PCLK/2^9 */
#define TAU_CKx_PCLK_10                 (10u) /* CK - PCLK/2^10 */
#define TAU_CKx_PCLK_11                 (11u) /* CK - PCLK/2^11 */
#define TAU_CKx_PCLK_12                 (12u) /* CK - PCLK/2^12 */
#define TAU_CKx_PCLK_13                 (13u) /* CK - PCLK/2^13 */
#define TAU_CKx_PCLK_14                 (14u) /* CK - PCLK/2^14 */
#define TAU_CKx_PCLK_15                 (15u) /* CK - PCLK/2^15 */

/* Selected operation clock (TAUBnCKS[1:0] = CMOR[15:14]) */
typedef enum{
    E_CMOR_CK0=0,
    E_CMOR_CK1,
    E_CMOR_CK2,
    E_CMOR_CK3,
    E_CMOR_CK_MAX
}CMOR_CKTYPE;

#define TAUB_CLOCK_SELECT_CK(selCMOR_CKTYPE) ((selCMOR_CKTYPE)<<14) 

/* Selects the count clock for TAUBnCNTm counter (TAUBnCCS0) =CMOR[12] */
typedef enum{
    E_CNTCLK_NOINT=0,/* Operation clock as specified by TAUBnCMORm.TAUBnCKS[1:0] */
    E_CNTCLK_INTPUT      /* Valid edge of TAUBnTTINm input signal */
}CMOR_CCLKTP;
#define TAUB_CNTmCLK_SELECT(eCMOR_CCLKTP) ((eCMOR_CCLKTP)<<12) 

/* Specifies the channel as master or slave channel during synchronous channel (TAUBnMAS =CMOR[11]) */
typedef enum{
    E_SLAVE=0,     /* Slave */
    E_MASTER   /* Master */
}CMOR_ISMASTER;
#define TAUB_MASTER_SELECT(eMASTER)  ((eMASTER)<<11) 

/* Selects the external start trigger (TAUBnSTS[2:0])  =CMOR[10:8] */
typedef enum{
    E_TRIG_SW=0,        /* Software trigger */
    E_TRIG_TIN_VALID,  /* Valid edge of the TAUBnTTINm input signal */
    E_TRIG_TIN_BOTH,   /* Valid edge of the TAUBnTTINm input signal is the start trigger */
                                                      /* and the reverse edge is the stop (capture) trigger             */
    E_TRIG_REWRITE,    /* Simultaneous rewrite trigger */ 
    E_TRIG_MASTER_INT, /* INTTAUnIm of the master channel */
    E_TRIG_UPPER_INT,  /* INTTAUBnIm of the upper channel (m-1), regardless of the master setting */
    E_TRIG_DEADTIME_OUT, /* Dead-time output signal of the TAUBnTTOUTm generation unit */
    E_TRIG_MASTER_UPDOWN /* Up/down output trigger signal of the master channel */
}CMOR_TRIGTYPE;
#define TAUB_TRIGGER_SELECT(selCMOR_TRIGTYPE) ((selCMOR_TRIGTYPE)<<8) 

/* Specifies when the capture register and the overflow flag of channel m are updated.valid in capture function. (TAUBnCOS[1:0] =CMOR[7:6]) */
typedef enum{
    E_CMOR_UPDATE0,    /*TAUBnCDRm Updated upon detection of aTAUBTTINm input valid edge. */
                                         /*TAUBnOVF Updated (cleared or set) upon detection of a TAUBTTINm input valid edge:*/
    E_CMOR_UPDATE1,    /*TAUBnCDRm Updated  */  
    E_CMOR_UPDATE3,
    E_CMOR_UPDATE4,
}CMOR_UPDATE;
#define TAUB_CAPTURE_UPDATE(eCMOR_UPDATE) ((eCMOR_UPDATE)<<6) 

/* Specifies the operation mode (TAUBnMD[4:0] == CMOR[4:0]) */
/* TAUBnMD[0]=0,1 ) */
typedef enum{
E_MODE_INTERVAL_TIMER=0,   /* Interval Timer mode.[0]=0/1*/
E_MODE_JUDGE=2,                       /* Judge mode.[0]=0/1 */
E_MODE_CAPTURE=4,                   /* Capture mode.[0]=0/1 */
E_MODE_EVENT_COUNT=6,          /* Event Count mode.[0]=0 */
E_MODE_ONE_COUNT=8,              /* One Count mode.[0]=0/1 */
E_MODE_PROHIBIT0=0x0A,                  /* Setting prohibited */
E_MODE_CAPTURE_ONE_COUNT=0x0C,  /* Capture & One Count mode. [0]=0 */
E_MODE_JUDGE_ONE_COUNT=0x0E,      /* Judge & One Count mode.[0]=0/1 */
E_MODE_PROHIBIT1=0x10,                        /* Setting prohibited.[0]=0 */
E_MODE_UP_DOWN_COUNT=0x12,          /* Up Down Count mode.[0]=0 */
E_MODE_PULSE_ONE_COUNT=0x14 ,     /* Pulse One Count mode.[0]=0/1 */
E_MODE_COUNT_CAPTURE =0x16 ,         /* Count Capture mode.[0]=0/1 */
E_MODE_GATE_COUNT=0x18,                  /* Gate Count mode.[0]=0 */
E_MODE_CAPTURE_GATE_COUNT=0x1A,   /* Capture & Gate Count mode.[0]=0 */

E_MODE_INVALID =0xFF
}CMOR_MD_TYPE;
/* Specifies the operation mode (TAUBnMD0[0] = CMOR[0]) */
typedef enum{
    E_MD0_NOINT=0, /* No INTTAUBnIm generated when the counter is triggered */
    E_MD0_INT           /* INTTAUBnIm generated when the counter is triggered */
}CMOR_MD0_TYPE;

/*
    TAUBn channel mode user register m (TAUBnCMURm)
*/
/* Specifies the valid edge of the TAUBnTTINm input (TAUBnTIS[1:0] = CMUR[1:0]) */
typedef enum{
  E_TAUB_TIS_EDGE_FALLING=0,     /* capture function:Falling edge */
  E_TAUB_TIS_EDGE_RISING,           /* capture function:Rising edge  */
  E_TAUB_TIS_EDGE_FALL_RISE,     /* capture function:falling and Rising edges (low-width measurement selection) */
  E_TAUB_TIS_EDGE_RISE_FALL,     /* capture function:Rising and falling edges (high-width measurement selection) */
  E_TAUB_BOTH_EDGE_DETECT        /* just edge detect for capture-init interface, be not register value  */
}CMUR_EDGE_TP;

/*
    TAUBn channel stop trigger register (TAUBnTT)
*/
  /* Stops all channel  */
#define TAU_CHALL_STOP_TRG_ON          (0xffffU) 

/* Stops the counter of channel 0 (TAUBnTT00) */
#define TAU_CHm_STOP_TRG_OFF           (0x0000U) /* No function */
#define TAU_CHm_STOP_TRG_ON(m)       (1u<<(m))  /* Stops the counter and sets TAUBnTE.TAUBnTE00 = 0 */

/*
    TAUBn channel output enable register (TAUBnTOE)
*/
/*#define TAUB_OUTPUT_ENABLE(chm)*/   /*0 EN pjl_err ? */    /* Enables independent channel output mode */
#define TAUB_OUTPUT_DISABLE(chm)   (1u<<(chm)) /* Disables independent channel output mode */
/*
    TAUBn channel output register (TAUBnTO)
*/
/* Specifies/reads the level of TAUBnTTOUT0 (TAUBnTO00) */
#define TAUB_OUTPUT_VALUE_0(chm)  (~(1u<<(chm))) /* Low. logic &*/
#define TAUB_OUTPUT_VALUE_1(chm)  (1u<<(chm))    /* High.logic | */

/*
    TAUBn channel output mode register (TAUBnTOM)
*/
/*
    Timer Output Mode Register m (TOMm)
*/
/* Specifies the channel output mode (TAUBnTOM00) */
#define TAUB_OUTPUT_INDEPENDENT(chm)  (~(1u<<(chm))) /* Independent channel output mode .logic &*/
#define TAUB_OUTPUT_ISYNC(chm)         (1u<<(chm))    /* Synchronous channel output mode .logic | */


/*clock supply*/  
#define  TAUB_CLOCK 1/*CKSCLK_IPERI2*/


/* ------------------- TAUB/D REGISTERS ----------------- */
/*base address*/
#define  TAUB0_REG_BASEADD                    ( (CPU_INT32U )0xFFE30000u)
#define  TAUB1_REG_BASEADD                    ( (CPU_INT32U )0xFFE31000u)
#define  TAUD0_REG_BASEADD                    ( (CPU_INT32U )0xFFE20000u)
#define  TAUJ0_REG_BASEADD                    ( (CPU_INT32U )0xFFE50000u)
#define  TAUJ1_REG_BASEADD                    ( (CPU_INT32U )0xFFE51000u)

/*function address*/
#define  TAU_REG_TAUBnTPS(baseaddress)      (*(CPU_REG16 *)((baseaddress)+ 0x240u))
#define  TAU_REG_TAUBnBRS(baseaddress)      (*(CPU_REG08 *)((baseaddress)+ 0x244u)) /*only TAUD and TAUJ*/
#define  TAU_REG_TAUBnCDRm(baseaddress,m)   (*(CPU_REG16 *)((baseaddress)+ 0x0000u+(m)*4))
#define  TAU_REG_TAUBnCNTm(baseaddress,m)   (*(CPU_REG16 *)((baseaddress)+ 0x0080u+ (m)*4))
#define  TAU_REG_TAUBnCMORm(baseaddress,m)  (*(CPU_REG16 *)((baseaddress)+ 0x0200u+(m)*4))
#define  TAU_REG_TAUBnCMURm(baseaddress,m)  (*(CPU_REG08 *)((baseaddress)+ 0x00C0u+ (m)*4))
#define  TAU_REG_TAUBnCSRm(baseaddress,m)   (*(CPU_REG08 *)((baseaddress)+ 0x0140u+ (m)*4))
#define  TAU_REG_TAUBnCSCm(baseaddress,m)   (*(CPU_REG08 *)((baseaddress)+ 0x0180u+ (m)*4))
#define  TAU_REG_TAUBnTS(baseaddress)       (*(CPU_REG16 *)((baseaddress)+ 0x01C4u))
#define  TAU_REG_TAUBnTE(baseaddress)       (*(CPU_REG16 *)((baseaddress)+ 0x01C0u))
#define  TAU_REG_TAUBnTT(baseaddress)       (*(CPU_REG16 *)((baseaddress)+ 0x01C8u))
/*TAUBn output register*/
#define  TAU_REG_TAUBnTOE(baseaddress)               (*(CPU_REG16 *)((baseaddress)+ 0x005Cu))
#define  TAU_REG_TAUBnTO(baseaddress)                (*(CPU_REG16 *)((baseaddress)+ 0x0058u))
#define  TAU_REG_TAUBnTOM(baseaddress)               (*(CPU_REG16 *)((baseaddress)+ 0x0248u))
#define  TAU_REG_TAUBnTOC(baseaddress)               (*(CPU_REG16 *)((baseaddress)+ 0x024Cu))
#define  TAU_REG_TAUBnTOL(baseaddress)               (*(CPU_REG16 *)((baseaddress)+ 0x0040u))
#define  TAU_REG_TAUBnTDE(baseaddress)               (*(CPU_REG16 *)((baseaddress)+ 0x0250u))
#define  TAU_REG_TAUBnTDM(baseaddress)               (*(CPU_REG16 *)((baseaddress)+ 0x0254u)) /*just for TAUD*/
#define  TAU_REG_TAUBnTDL(baseaddress)               (*(CPU_REG16 *)((baseaddress)+ 0x0054u))
#define  TAU_REG_TAUBnTRO(baseaddress)               (*(CPU_REG16 *)((baseaddress)+ 0x004Cu))
#define  TAU_REG_TAUBnTRE(baseaddress)               (*(CPU_REG16 *)((baseaddress)+ 0x0258u))
#define  TAU_REG_TAUBnTRC(baseaddress)               (*(CPU_REG16 *)((baseaddress)+ 0x025Cu))
#define  TAU_REG_TAUBnTME(baseaddress)               (*(CPU_REG16 *)((baseaddress)+ 0x0050u))

/*TAUBn reload data registers*/
#define  TAU_REG_TAUBnRDE(baseaddress)               (*(CPU_REG16 *)((baseaddress)+ 0x0260u))
#define  TAU_REG_TAUBnRDM(baseaddress)               (*(CPU_REG16 *)((baseaddress)+ 0x0264u))
#define  TAU_REG_TAUBnRDS(baseaddress)               (*(CPU_REG16 *)((baseaddress)+ 0x0268u))
#define  TAU_REG_TAUBnRDC(baseaddress)               (*(CPU_REG16 *)((baseaddress)+ 0x026Cu))
#define  TAU_REG_TAUBnRDT(baseaddress)               (*(CPU_REG16 *)((baseaddress)+ 0x0044u))
#define  TAU_REG_TAUBnRSF(baseaddress)               (*(CPU_REG16 *)((baseaddress)+ 0x0048u))
#define  TAU_REG_TAUBnEMU(baseaddress)               (*(CPU_REG16 *)((baseaddress)+ 0x0290u))

/* ------------------- TAUJ REGISTERS ----------------- */
#define  TAU_REG_TAUJnTPS(baseaddress)      (*(CPU_REG16 *)((baseaddress)+ 0x90u))
#define  TAU_REG_TAUJnBRS(baseaddress)      (*(CPU_REG08 *)((baseaddress)+ 0x94u))
#define  TAU_REG_TAUJnCDR(baseaddress,m)  (*(CPU_REG32 *)((baseaddress)+ (m)*4))
#define  TAU_REG_TAUJnCMOR(baseaddress,m)  (*(CPU_REG16 *)((baseaddress)+0x80u+ (m)*4))
#define  TAU_REG_TAUJnCMUR(baseaddress,m)  (*(CPU_REG08 *)((baseaddress)+0x20u+ (m)*4))
#define  TAU_REG_TAUJnTS(baseaddress)        (*(CPU_REG08 *)((baseaddress)+ 0x54u))
#define  TAU_REG_TAUJnTT(baseaddress)        (*(CPU_REG08 *)((baseaddress)+ 0x58u))
#define  TAU_REG_TAUJnTOE(baseaddress)      (*(CPU_REG08 *)((baseaddress)+ 0x60u))
#define  TAU_REG_TAUJnTO(baseaddress)        (*(CPU_REG08 *)((baseaddress)+ 0x5cu))
#define  TAU_REG_TAUJnTOM(baseaddress)      (*(CPU_REG08 *)((baseaddress)+ 0x98u))
#define  TAU_REG_TAUJnTOC(baseaddress)      (*(CPU_REG08 *)((baseaddress)+ 0x9Cu))
#define  TAU_REG_TAUJnTOL(baseaddress)      (*(CPU_REG08 *)((baseaddress)+ 0x64u))
#define  TAU_REG_TAUJnRDE(baseaddress)      (*(CPU_REG08 *)((baseaddress)+ 0xA0u))
#define  TAU_REG_TAUJnRDM(baseaddress)      (*(CPU_REG08 *)((baseaddress)+ 0xA4u))
#define  TAU_REG_TAUJnRDT(baseaddress)      (*(CPU_REG08 *)((baseaddress)+ 0x68u))
#define  TAU_REG_TAUJnCSR(baseaddress,m)    (*(CPU_REG08 *)((baseaddress)+ 0x30u + (m)*4))
#define  TAU_REG_TAUJnCSC(baseaddress,m)    (*(CPU_REG08 *)((baseaddress)+ 0x40u + (m)*4))

/* filter */
#define TAU_REG_DNFATAUB0ICTL      (*(CPU_REG08 *)0xFFC30020u)
#define TAU_REG_DNFATAUB0IEN       (*(CPU_REG16 *)0xFFC30024u)
#define TAU_REG_DNFATAUD0ICTL      (*(CPU_REG08 *)0xFFC30000u)
#define TAU_REG_DNFATAUD0IEN       (*(CPU_REG16 *)0xFFC30004u)

#endif /*_TIMERUNIT_H*/

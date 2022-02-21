/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.		       
*				  All Rights Reserved.                 
*   Department :  CT AD NKG      				     
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   : Functions in General Port Mode
***********************************************************************/
/*-History--------------------------------------------------------------
* Version  Date   	 Name        Changes and comments
------------------------------------------------------------------------
* 0.1	   Apr 28,2016   PEI Jingli  Initial version
------------------------------------------------------------------------
* 0.2	   Jun 29,2016   LIU Chenxi  Correct errors during merging	
------------------------------------------------------------------------
* 0.3	   July 07,2016  PEI Jingli  Adapt 64pin MCU
* ----------------------------------------------------------------------
* 0.4      July 07,2016  LIU Chenxi  Refine code structure
*=====================================================================*/


//============================================================================
// Includes
//============================================================================

#ifndef  _IRQ_H
#define  _IRQ_H
#include "config.h"
#include "define.h"


/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                        DEFAULT CONFIGURATION
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/
                                                                /* ------------------- BIT DEFINES -------------------- */
#define  DEF_BIT_NONE                                   0x00u

#define  DEF_BIT_00                                     0x01u
#define  DEF_BIT_01                                     0x02u
#define  DEF_BIT_02                                     0x04u
#define  DEF_BIT_03                                     0x08u
#define  DEF_BIT_04                                     0x10u
#define  DEF_BIT_05                                     0x20u
#define  DEF_BIT_06                                     0x40u
#define  DEF_BIT_07                                     0x80u

#define  DEF_BIT_08                                   0x0100u
#define  DEF_BIT_09                                   0x0200u
#define  DEF_BIT_10                                   0x0400u
#define  DEF_BIT_11                                   0x0800u
#define  DEF_BIT_12                                   0x1000u
#define  DEF_BIT_13                                   0x2000u
#define  DEF_BIT_14                                   0x4000u
#define  DEF_BIT_15                                   0x8000u

#define  DEF_BIT_16                               0x00010000u
#define  DEF_BIT_17                               0x00020000u
#define  DEF_BIT_18                               0x00040000u
#define  DEF_BIT_19                               0x00080000u
#define  DEF_BIT_20                               0x00100000u
#define  DEF_BIT_21                               0x00200000u
#define  DEF_BIT_22                               0x00400000u
#define  DEF_BIT_23                               0x00800000u

#define  DEF_BIT_24                               0x01000000u
#define  DEF_BIT_25                               0x02000000u
#define  DEF_BIT_26                               0x04000000u
#define  DEF_BIT_27                               0x08000000u
#define  DEF_BIT_28                               0x10000000u
#define  DEF_BIT_29                               0x20000000u
#define  DEF_BIT_30                               0x40000000u
#define  DEF_BIT_31                               0x80000000u

#define  DEF_BIT_SET_08(val, mask)                     ((val) = (CPU_INT08U)(((CPU_INT08U)(val)) | ((CPU_INT08U) (mask))))

#define  DEF_BIT_SET_16(val, mask)                     ((val) = (CPU_INT16U)(((CPU_INT16U)(val)) | ((CPU_INT16U) (mask))))

#define  DEF_BIT_SET_32(val, mask)                     ((val) = (CPU_INT32U)(((CPU_INT32U)(val)) | ((CPU_INT32U) (mask))))

#define  DEF_BIT_SET_64(val, mask)                     ((val) = (CPU_INT64U)(((CPU_INT64U)(val)) | ((CPU_INT64U) (mask))))

#define  DEF_BIT_SET(val, mask)                 ((sizeof(val) == CPU_WORD_SIZE_08) ? DEF_BIT_SET_08(val, mask) :     \
                                                ((sizeof(val) == CPU_WORD_SIZE_16) ? DEF_BIT_SET_16(val, mask) :     \
                                                ((sizeof(val) == CPU_WORD_SIZE_32) ? DEF_BIT_SET_32(val, mask) :     \
                                                ((sizeof(val) == CPU_WORD_SIZE_64) ? DEF_BIT_SET_64(val, mask) : 0))))

#define  DEF_BIT_CLR_08(val, mask)                     ((val) = (CPU_INT08U)(((CPU_INT08U)(val)) & ((CPU_INT08U)~(mask))))

#define  DEF_BIT_CLR_16(val, mask)                     ((val) = (CPU_INT16U)(((CPU_INT16U)(val)) & ((CPU_INT16U)~(mask))))

#define  DEF_BIT_CLR_32(val, mask)                     ((val) = (CPU_INT32U)(((CPU_INT32U)(val)) & ((CPU_INT32U)~(mask))))

#define  DEF_BIT_CLR_64(val, mask)                     ((val) = (CPU_INT64U)(((CPU_INT64U)(val)) & ((CPU_INT64U)~(mask))))

#define  DEF_BIT_CLR(val, mask)                 ((sizeof(val) == CPU_WORD_SIZE_08) ? DEF_BIT_CLR_08(val, mask) :     \
                                                ((sizeof(val) == CPU_WORD_SIZE_16) ? DEF_BIT_CLR_16(val, mask) :     \
                                                ((sizeof(val) == CPU_WORD_SIZE_32) ? DEF_BIT_CLR_32(val, mask) :     \
                                                ((sizeof(val) == CPU_WORD_SIZE_64) ? DEF_BIT_CLR_64(val, mask) : 0))))

#if 0
typedef  struct _IRQTABLE
{
 U8 IRQNo;
 Func_Void_Proc isrproc;
}IRQTable;
#endif
/*  when 2 interruput sources for one interruput channel, selected the 1st one. */
#define SELB_INTC_1ST    1
//ISR No. for F1L 100 pin
#define INTTAUD0I0 0
#define INTTAUD0I2 1
#define INTTAUD0I4 2
#define INTTAUD0I6 3
#define INTTAUD0I8 4
#define INTTAUD0I10 5
#define INTTAUD0I12 6
#define INTTAUD0I14 7
#define INTTAPA0IPEK0 8
#define INTTAPA0IVLY0 9
#define INTADCA0I0 10
#define INTADCA0I1 11
#define INTADCA0I2 12
#define INTDCUTDI 13
#define INTRCANGERR 14
#define INTRCANGRECC 15
#define INTRCAN0ERR 16
#define INTRCAN0REC 17
#define INTRCAN0TRX 18
#define INTCSIG0IC 19
#define INTCSIG0IR 20
#define INTCSIH0IC 21
#define INTCSIH0IR 22
//#define INTCSIH0IRE 23
#define INTCSIH0IJC 24
#define INTRLIN30 25
#define INTRLIN30UR0 26
#define INTRLIN30UR1 27
#define INTRLIN30UR2 28
#define INTP0 29
#define INTP1 30
#define INTP2 31
#define INTWDTA0 32
#define INTWDTA1 33
#define INTP3 34
#define INTP4 35
#define INTP5 36
#define INTP10 37
#define INTP11 38
#define INTTAUD0I1 39
#define INTTAUD0I3 40
#define INTTAUD0I5 41
#define INTTAUD0I7 42
#define INTTAUD0I9 43
#define INTTAUD0I11 44
#define INTTAUD0I13 45
#define INTTAUD0I15 46
#define INTADCA0ERR 47

#define INTCSIG0IRE 49
#define INTRLIN20 50
#define INTRLIN21 51
#define INTDMA0 52
#define INTDMA1 53
#define INTDMA2 54
#define INTDMA3 55
#define INTDMA4 56
#define INTDMA5 57
#define INTDMA6 58
#define INTDMA7 59
#define INTDMA8 60
#define INTDMA9 61
#define INTDMA10 62
#define INTDMA11 63
#define INTDMA12 64
#define INTDMA13 65
#define INTDMA14 66
#define INTDMA15 67
#define INTRIIC0TI 68
#define INTRIIC0TEI 69
#define INTRIIC0RI 70
#define INTRIIC0EE 71
#define INTTAUJ0I0 72
#define INTTAUJ0I1 73
#define INTTAUJ0I2 74
#define INTTAUJ0I3 75
#define INTOSTM0 76
#define INTENCA0IOV 77
#define INTENCA0IUD 78
#define INTENCA0I0 79
#define INTENCA0I1 80
#define INTENCA0IEC 81
#define INTKR0 82
#define INTQFULL 83
#define INTPWGA0 84
#define INTPWGA1 85
#define INTPWGA2 86
#define INTPWGA3 87
#define INTPWGA8 88
#define INTPWGA9 89
#define INTPWGA10 90
#define INTPWGA11 91
#define INTPWGA12 92
#define INTPWGA13 93
#define INTPWGA14 94
#define INTPWGA15 95

#define INTFLERR 102
#define INTFLENDNM 103
#define INTCWEND 104
#define INTRCAN1ERR 105
#define INTRCAN1REC 106
#define INTRCAN1TRX 107
#define INTCSIH1IC 108
#define INTCSIH1IR 109
#define INTCSIH1IRE 110
#define INTCSIH1IJC 111
#define INTRLIN31 112
#define INTRLIN31UR0 113
#define INTRLIN31UR1 114
#define INTRLIN31UR2 115
#define INTPWGA20 116
#define INTPWGA21 117
#define INTPWGA22 118
#define INTPWGA23 119
#define INTP6 120
#define INTP7 121
#define INTP8 122
#define INTP12 123
#define INTCSIH2IC 124
#define INTCSIH2IR 125
#define INTCSIH2IRE 126
#define INTCSIH2IJC 127

#define INTTAUB0I0 134
#define INTTAUB0I1 135
#define INTTAUB0I2 136
#define INTTAUB0I3 137
#define INTTAUB0I4 138
#define INTTAUB0I5 139
#define INTTAUB0I6 140
#define INTTAUB0I7 141
#define INTTAUB0I8 142
#define INTTAUB0I9 143
#define INTTAUB0I10 144
#define INTTAUB0I11 145
#define INTTAUB0I12 146
#define INTTAUB0I13 147
#define INTTAUB0I14 148
#define INTTAUB0I15 149
#define INTCSIH3IC 150
#define INTCSIH3IR 151
#define INTCSIH3IRE 152
#define INTCSIH3IJC 153
#define INTRLIN22 154

#define INTRLIN32 156
#define INTRLIN32UR0 157
#define INTRLIN32UR1 158
#define INTRLIN32UR2 159
#define INTTAUJ1I0 160
#define INTTAUJ1I1 161
#define INTTAUJ1I2 162
#define INTTAUJ1I3 163

#define INTPWGA24 176
#define INTPWGA25 177
#define INTPWGA27 178
#define INTPWGA28 179
#define INTPWGA29 180
#define INTPWGA32 181
#define INTPWGA33 182
#define INTPWGA34 183
#define INTPWGA35 184
#define INTPWGA36 185
#define INTPWGA37 186
#define INTPWGA38 187
#define INTPWGA39 188
#define INTPWGA40 189
#define INTPWGA41 190
#define INTPWGA42 191
#define INTPWGA43 192
#define INTPWGA44 193
#define INTPWGA45 194
#define INTPWGA46 195
#define INTPWGA47 196
#if ( MCU_PIN > PIN100 )
#define INTP9 197
#endif
#define INTP13 198
#if ( MCU_PIN > PIN100 )
#define INTP14 199
#define INTP15 200
#endif

#define Reserved 208
#define INTRCAN2ERR 209
#define INTRCAN2REC 210
#define INTRCAN2TRX 211

#define INTRLIN33 220
#define INTRLIN33UR0 221
#define INTRLIN33UR1 222
#define INTRLIN33UR2 223

#define IRQ_INT_ID_MAX       (INTRLIN33UR2+1)

/* ------------ INTERRUPT PRIORITY DEFINES ---------- */
//#define  IRQ_INT_PRIO_LEVEL_MASK             DEF_BIT_MASK(15, 0)
#define  IRQ_INT_PRIO_LEVEL_00               0u
#define  IRQ_INT_PRIO_LEVEL_01               1u
#define  IRQ_INT_PRIO_LEVEL_02               2u
#define  IRQ_INT_PRIO_LEVEL_03               3u
#define  IRQ_INT_PRIO_LEVEL_04               4u
#define  IRQ_INT_PRIO_LEVEL_05               5u
#define  IRQ_INT_PRIO_LEVEL_06               6u
#define  IRQ_INT_PRIO_LEVEL_07               7u
#define  IRQ_INT_PRIO_LEVEL_08               8u
#define  IRQ_INT_PRIO_LEVEL_09               9u
#define  IRQ_INT_PRIO_LEVEL_10               10u
#define  IRQ_INT_PRIO_LEVEL_11               11u
#define  IRQ_INT_PRIO_LEVEL_12               12u
#define  IRQ_INT_PRIO_LEVEL_13               13u
#define  IRQ_INT_PRIO_LEVEL_14               14u
#define  IRQ_INT_PRIO_LEVEL_15               15u


#define  IRQ_INT_MASK_SRC_OFFSET_00       0   //0x80u

#define IRQ_INT_REG_ICxx_BASE                   ( (U32 )0xFFFF9000u)
//address not continous
#define IRQ_INT_REG_ICxx_BASE_SEC                ( (U32 )0xFFFFA040u)

#define IRQ_INT_REG_ICxx(n)                     (*(U16 *)((n>31)?(IRQ_INT_REG_ICxx_BASE_SEC + 2 * (n-32)) : (IRQ_INT_REG_ICxx_BASE + 2 * n))	)

#define IRQ_INT_ICxx_EIMKn                       DEF_BIT_07
#define IRQ_INT_ICxx_EITBn                       DEF_BIT_06
#define IRQ_INT_ICxx_EIRFn                       DEF_BIT_12
/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void IRQ_Init_Setup (void);
void IRQ_IntClr           (U8     int_id);
void IRQ_IntDis           (U8     int_id);
void IRQ_IntEn            (U8     int_id);
void IRQ_IntVectReg       (U8     int_id,U8     prio);
void IRQ_IntDisAll        (void);
void  IRQ_IntClrAll        (void);
//void IRQ_IntHandler       (U32     src_nbr);
void IRQ_IntHandler       (void);
void IRQ_IntHandlerDummy (void);
/*
*********************************************************************************************************
*                                              ERROR CHECKING
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of module include.                               */


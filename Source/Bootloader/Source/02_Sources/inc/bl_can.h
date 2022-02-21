/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the header file of the can module.
 *
 *  \file       bl_can.h
 *  \ingroup    driver_module
 *  \author     lele.liu <lele.liu@hirain.com>
 *
 *  \version    1.0.0
 *  \date       25/01/2016
 *
 *  \par        Changelist
 *      Version  |  Date      | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | -------------
 *      01.00.00 | 25/01/2016 | lele.liu         | N/A | BootDrv010001
 *
 *****************************************************************************/
#ifndef _BL_CAN_H_
#define _BL_CAN_H_
#include "bl_typedefs.h"
#include "dr7f701023_0.h"
#include "bl_can_cfg.h"
#include "bl_can_type.h"
#include "bl_can_if.h"


/*************************************************************************
*                           宏定义                                       * 
**************************************************************************/

#define CAN_CONTROLLER_0                        0
#define CAN_CONTROLLER_1                        1
#define CAN_CONTROLLER_2                        2

#define RSCFD0CFDGAFLIDj_RULE0_VALUE            (0X0 | CAN_RX_ID0)
#define RSCFD0CFDGAFLIDj_RULE1_VALUE            (0X0 | CAN_RX_ID1)
#define RSCAN0RFID0_ADDRESS                    0xffd00e00UL
#define RSCAN0RFIDx_ADDRESS_OFFSET            0x10U


#define CAN_TX_OK                            0 
#define CAN_TX_FAILED                        1 

/**********************use for bit rate************/

#define RSCFD0CFDCmNCFG_VALUE    (CAN_CONTROLLER_NBRP | (CAN_CONTROLLER_NSJW << 24) | \
                                          (CAN_CONTROLLER_NTSEG1 << 16) | (CAN_CONTROLLER_NTSEG2 << 20))


/**********************use for can_read************/
/* ---- bit mask ---- */
#define CAN_1_BIT_MASK                      1U
#define CAN_2_BIT_MASK                      3U
#define CAN_3_BIT_MASK                      7U
#define CAN_4_BIT_MASK                      0xfU
#define CAN_5_BIT_MASK                      0x1fU

#define CAN_FIFO_RX_BUF_NUM              8U

/* ---- bit position ---- */
#define CAN_B0_BIT_POS                      0U
#define CAN_B1_BIT_POS                      1U
#define CAN_B2_BIT_POS                      2U
#define CAN_B3_BIT_POS                      3U
#define CAN_B4_BIT_POS                      4U
#define CAN_B5_BIT_POS                      5U
#define CAN_B6_BIT_POS                      6U
#define CAN_B7_BIT_POS                      7U
#define CAN_B8_BIT_POS                      8U
#define CAN_B9_BIT_POS                      9U
#define CAN_B10_BIT_POS                     10U
#define CAN_B11_BIT_POS                     11U
#define CAN_B12_BIT_POS                     12U
#define CAN_B13_BIT_POS                     13U
#define CAN_B14_BIT_POS                     14U
#define CAN_B15_BIT_POS                     15U

/* ---- bit operations ---- */
#define GET_BIT(reg, pos)              (((reg) >> (pos)) & 1U)
#define SET_BIT(reg, pos)              ((reg) |= 1U << (pos))
#define CLR_BIT(reg, pos)              ((reg) &= ~(1UL << (pos)))

   
/*************************************************************************
*                           数据结构                                     * 
**************************************************************************/
  
/* ---- CANFD frame ----- */
typedef struct
{
    bl_u32_t ID :29;
    bl_u32_t THLEN :1;
    bl_u32_t RTR :1;
    bl_u32_t IDE :1;
    
    bl_u32_t res0 :16;
    bl_u32_t LBL :8;
    bl_u32_t res1 :4;
    bl_u32_t DLC :4;
     
    bl_u8_t DB[ 8 ];
} Can_FrameType;

/* ---- CANFD REC frame ----- */
typedef struct
{
    bl_u32_t ID :29;
    bl_u32_t res0 :1;
    bl_u32_t RTR :1;
    bl_u32_t IDE :1;
    
    bl_u32_t TS :16;
    bl_u32_t LBL :12;
    bl_u32_t DLC :4;
      
    bl_u8_t DB[ 8 ];
} Can_REC_FrameType;

/************************************     new config         ************************************/

typedef struct {
   bl_u32_t lword[4];
 }can_cre_type;

extern  can_cre_type RX_RULE_TABLE_LIST1[CAN_RX_NUMBER]; //RX_RULE_NUM -- depend on real config
extern  can_cre_type RX_RULE_TABLE_LIST0[CAN_RX_NUMBER]; /*RX_RULE_NUM -- used for can_deinit*/

        
/*******************************************************************************
*  Declarations  of services
*******************************************************************************/
extern bl_Return_t Can_Init(void);

extern bl_Return_t Can_Write
(
    const bl_CanTxPdu_t* PduInfo
);
extern void Can_Deinit(void);

extern bl_Return_t Can_CheckTxStatus(bl_u8_t handle);

extern bl_Return_t Can_Read(bl_CanRxPdu_t *pdu);

extern void Can_BusOff_Check(void);

extern void Can_Sleep(void);

extern void Can_Wakeup(void);

static void Can_SetRxRule(void);

static void Can_ResetRxRule(void);


static void Can_Channel_Mode (void);

static void Can_Reset_Channel_Mode();



#endif  /* ifdef _CAN_DRIVER_H_ */

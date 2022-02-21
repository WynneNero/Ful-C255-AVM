/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is the configuration header file of the can module.
 *
 *  \file       bl_can_cfg.h
 *  \ingroup    driver_module
 *  \author     lele.liu <lele.liu@hirain.com>
 *
 *  \version    1.0.0
 *  \date       25/01/2016 
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | -------------
 *      01.00.00 | 25/01/2016 | lele.liu         | N/A | BootDrv010001
 *
 *****************************************************************************/
#ifndef _BL_CAN_CFG_H_
#define _BL_CAN_CFG_H_


#define HARDWARE_FLEXCAN                          /* MCU with CAN controller */

#define CAN_CONTROLLER_USED                       CAN_CONTROLLER_1


/* Nominal Bit Rate Config */
/* fCAN=PPLLCLK2=40M ,Bitrate = fCAN/(NBRP+1)/(1+NTSEG1+1+NTSEG2+1)  */
#define CAN_CONTROLLER_NBRP                        3U /* 0~1023 is available. */
#define CAN_CONTROLLER_NSJW                        2U /* 0~3 is available ,NSJW <= NTSEG2. */
#define CAN_CONTROLLER_NTSEG1                      14U /* 3~15  is available. */
#define CAN_CONTROLLER_NTSEG2                      3U /* 1~7  is available,NTSEG2 < NTSEG1. */


#define CAN_DATA_DLC                              (8u)

#define CAN_RX_NUMBER                               (2u)
#define CAN_RX_ID0                                0x726//RTE_CAN_PHYRX_ID
#define CAN_RX_ID1                                0x7DF//RTE_CAN_FUNRX_ID


#endif                          /* ifdef _CAN_CFG_H_ */


#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_OFF 0292
#endif
/*********************************************************************************************************************
 * Library       : EEPROM Emulation Library for Renesas RH850 devices
 *
 * File Name     : $Source: r_eel.h $
 * Lib. Version  : $RH850_EEL_LIB_VERSION_T01: V2.01 $
 * Mod. Revision : $Revision: 1.8 $
 * Mod. Date     : $Date: 2017/02/07 09:12:05JST $
 * Device(s)     : RV40 Flash based RH850 microcontroller
 * Description   : User interface function prototypes
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only  intended for use with Renesas products.
 * No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
 * TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS
 * AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY
 * REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2014-2017 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/

#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_ON 0292
#endif

/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 3.1 (QAC message 0292)
 * Reason:       To support automatic insertion of revision, module name etc. by the source revision control system
 *               it is necessary to violate the rule, because the system uses non basic characters as placeholders.
 * Verification: The placeholders are used in comments only. Therefore rule violation cannot influence code
 *               compilation.
 *********************************************************************************************************************/

#ifndef R_EEL_H
#define R_EEL_H


/*********************************************************************************************************************
 * Include list
 *********************************************************************************************************************/
#include "EEL_Cfg.h"
#include "R_EEL_Types.h"


#ifdef R_EEL_USERIF_C
    #define R_EEL_EXTERN
#else
    #define R_EEL_EXTERN extern
#endif

/*********************************************************************************************************************
 * Global function prototypes
 *********************************************************************************************************************/
/* EEL initialization function */
    R_EEL_EXTERN r_eel_status_t     R_EEL_Init (const r_eel_descriptor_t * descriptor_pstr,
                                                r_eel_operation_mode_t opMode_enu);

/* EEL operation initiation */
    R_EEL_EXTERN void               R_EEL_Execute (r_eel_request_t * request_pstr);

/* EEL operation forwarding and status check */
    R_EEL_EXTERN void               R_EEL_Handler (void);

/* EEL state machine startup initiation */
    R_EEL_EXTERN r_eel_status_t     R_EEL_Startup (void);

/* EEL state machine shut down initiation */
    R_EEL_EXTERN r_eel_status_t     R_EEL_ShutDown (void);

/* EEL state machine suspend initiation */
    R_EEL_EXTERN r_eel_status_t     R_EEL_SuspendRequest (void);

/* EEL state machine resume initiation */
    R_EEL_EXTERN r_eel_status_t     R_EEL_ResumeRequest (void);

/* EEL driver status return  */
    R_EEL_EXTERN r_eel_status_t     R_EEL_GetDriverStatus (r_eel_driver_status_t * driverStatus_pstr);

/* EEL free space calculation */
    R_EEL_EXTERN r_eel_status_t     R_EEL_GetSpace (uint32_t * space_pu32);

/* EEL block erase counter return */
    R_EEL_EXTERN r_eel_status_t     R_EEL_GetEraseCounter (uint32_t * counter_pu32);

/* Return of EEL version string */
    R_EEL_EXTERN const uint8_t *R_EEL_GetVersionString (void);


/*********************************************************************************************************************/
#endif       /* #ifndef R_EEL_H */


#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_OFF 0292
#endif
/*********************************************************************************************************************
 * File Name     : $Source: eel_cfg.h $
 * Mod. Revision : $Revision: 1.6 $
 * Mod. Date     : $Date: 2014/09/10 11:54:31MESZ $
 * Device(s)     : RV40 Flash based RH850 microcontroller
 * Description   : EEL pre-compile definitions
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
 * Copyright (C) 2014 Renesas Electronics Corporation. All rights reserved.     
 *********************************************************************************************************************/
#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_ON 0292 
#endif

/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 3.1 (QAC message 0292)
 * Reason:       To support automatic insertion of revision, module name etc. by the source revision control system 
 *               it is necessary to violate the rule, because the system uses non basic characters as placeholders.
 * Verification: The placeholders are used in commentars only. Therefore rule violation cannot influency code 
 *               compilation.
 *********************************************************************************************************************/

#ifndef EEELIBSETUP_H
#define EEELIBSETUP_H


/*********************************************************************************************************************
 * User changable section
 *   
 * Please be aware, that changing this section will have an impact on the EEPROM emulation  
 * functionality. Modification should be done only if the modification is confirmed by Renesas!
 *********************************************************************************************************************/
    /**< define for activating EEL extended featured (such as Ds write counter or fast invalidation) */
    /*#define R_EEL_SUPPORT_EXT_FEATURES*/

    /**< define for activating Flash interrupt support & Setting Flash interrupt by software */
                                                                               
    /*
    #define R_EEL_FLINT_SET_SW ((*(uint16_t*)0xffff60feuL) = (*(uint16_t*)0xffff60feuL) | 0x1000)   
    */

/*********************************************************************************************************************
 * Do not change this section !!!
 *********************************************************************************************************************/
    /* Currently empty */


/*********************************************************************************************************************/
#endif  /* #ifndef EEELIBSETUP_H */

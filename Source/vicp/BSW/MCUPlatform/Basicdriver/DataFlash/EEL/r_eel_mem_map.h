#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_OFF 0292
#endif
/*********************************************************************************************************************
 * Library       : EEPROM Emulation Library for Renesas RH850 devices
*
 * File Name     : $Source: r_eel_mem_map.h $
 * Lib. Version  : $RH850_EEL_LIB_VERSION_T01: V2.01 $
 * Mod. Revision : $Revision: 1.8 $
 * Mod. Date     : $Date: 2017/02/07 09:12:10JST $
 * Device(s)     : RV40 Flash based RH850 microcontroller
 * Description   : EEL section mapping definitions
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

/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 19.6 (QAC message 0841)
 * Reason:       Using undef is not recommended but required due to AUTOSAR compliant implementation of section defines
 * Verification: Just used for AUTOSAR compliant header inclusion
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 19.15 (QAC message 0883)
 * Reason:       Include file code is not protected against repeated inclusion. This is intended as the header file
                 shall be included multiple times in the source
 * Verification: Just used for AUTOSAR compliant header file inclusion
 *********************************************************************************************************************/


/*********************************************************************************************************************
 * Global compiler definitions
 *********************************************************************************************************************/
#ifdef AUTOSAR_IMPLEMENTATION
    #if defined R_EEL_START_SEC_PUBLIC_CODE
        #define EEL_START_SEC_PUBLIC_CODE                                                           /* PRQA S 0883 */
    #elif defined R_EEL_STOP_SEC_PUBLIC_CODE
        #define EEL_STOP_SEC_PUBLIC_CODE
    #elif defined R_EEL_START_SEC_CONST
        #define EEL_START_SEC_CONST_UNSPECIFIED
    #elif defined R_EEL_STOP_SEC_CONST
        #define EEL_STOP_SEC_CONST_UNSPECIFIED
    #elif defined R_EEL_START_SEC_VAR
        #define EEL_START_SEC_VAR_UNSPECIFIED
    #elif defined R_EEL_STOP_SEC_VAR
        #define EEL_STOP_SEC_VAR_UNSPECIFIED
    #else
      #error "r_eel_mem_map.h: No valid section define found"
    #endif

    #include "MemMap.h"
#else

    #if defined R_EEL_START_SEC_PUBLIC_CODE
        #undef R_EEL_START_SEC_PUBLIC_CODE                                                          /* PRQA S 0841 */
        #if   R_EEL_COMPILER == R_EEL_COMP_GHS
            #pragma ghs section text=".R_EEL_Text"
        #elif R_EEL_COMPILER == R_EEL_COMP_IAR
            #pragma location = "R_EEL_Text"
        #elif R_EEL_COMPILER == R_EEL_COMP_REC
            #pragma section text "R_EEL_Text"
        #endif
    #elif defined R_EEL_STOP_SEC_PUBLIC_CODE
        #undef R_EEL_STOP_SEC_PUBLIC_CODE                                                           /* PRQA S 0841 */
        #if   R_EEL_COMPILER == R_EEL_COMP_GHS
            #pragma ghs section text=default
        #elif R_EEL_COMPILER == R_EEL_COMP_IAR
            /* Location is valid for one statement only, so no reset to default required */
        #elif R_EEL_COMPILER == R_EEL_COMP_REC
            #pragma section default
        #endif

    #elif defined R_EEL_START_SEC_CONST
        #undef R_EEL_START_SEC_CONST                                                                /* PRQA S 0841 */
        #if   R_EEL_COMPILER == R_EEL_COMP_GHS
            #pragma ghs startdata
            #pragma ghs section rodata=".R_EEL_Const"
        #elif R_EEL_COMPILER == R_EEL_COMP_IAR
            /* Same for text and const */
        #elif R_EEL_COMPILER == R_EEL_COMP_REC
            #pragma section const "R_EEL_Const"
        #endif
    #elif defined R_EEL_STOP_SEC_CONST
        #undef R_EEL_STOP_SEC_CONST                                                                 /* PRQA S 0841 */
        #if   R_EEL_COMPILER == R_EEL_COMP_GHS
            #pragma ghs section rodata=default
            #pragma ghs enddata
        #elif R_EEL_COMPILER == R_EEL_COMP_IAR
            /* Same for text and const */
        #elif R_EEL_COMPILER == R_EEL_COMP_REC
            /* no pragma needed */
        #endif

    #elif defined R_EEL_START_SEC_VAR
        #undef R_EEL_START_SEC_VAR                                                                  /* PRQA S 0841 */
        #if R_EEL_COMPILER == R_EEL_COMP_GHS
            #pragma ghs startdata
            #pragma ghs section bss = ".R_EEL_Data"
        #elif R_EEL_COMPILER == R_EEL_COMP_IAR
            #pragma dataseg = R_EEL_Data
        #elif R_EEL_COMPILER == R_EEL_COMP_REC
            #pragma section r0_disp32 "R_EEL_Data"
        #endif
    #elif defined R_EEL_STOP_SEC_VAR
        #undef R_EEL_STOP_SEC_VAR                                                                   /* PRQA S 0841 */
        #if R_EEL_COMPILER == R_EEL_COMP_GHS
            #pragma ghs section bss = default
            #pragma ghs enddata
        #elif R_EEL_COMPILER == R_EEL_COMP_IAR
            #pragma dataseg = default
        #elif R_EEL_COMPILER == R_EEL_COMP_REC
            /* no pragma needed */
        #endif

    #else
      #error "r_eel_mem_map.h: No valid section define found"
    #endif // if defined R_EEL_START_SEC_PUBLIC_CODE

#endif // ifdef AUTOSAR_IMPLEMENTATION
/*********************************************************************************************************************/


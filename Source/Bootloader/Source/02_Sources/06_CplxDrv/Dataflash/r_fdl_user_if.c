#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_OFF 0292
#endif
/*********************************************************************************************************************
 * Library       : Data Flash Access Library for Renesas RH850 devices
 *
 * File Name     : $Source: r_fdl_user_if.c $
 * Lib. Version  : $RH850_FDL_LIB_VERSION_T01: V1.03 $
 * Mod. Revision : $Revision: 1.27 $
 * Mod. Date     : $Date: 2013/11/19 16:52:30MEZ $
 * Device(s)     : RV40 Flash based RH850 microcontroller
 * Description   : FDL user interface functions
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
 * Copyright (C) 2013 Renesas Electronics Corporation. All rights reserved.
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

/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 11.3 (QAC message 0306)
 * Reason:       For effective embedded programming, integer to pointer conversions are used
 * Verification: The converted addresses are essential for complete code execution. Incorrect
 *               conversion would result in test fails.
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 14.1 (QAC message 1503)
 * Reason:       This function is not used within the library, it is only used by the user
 *               application.
 * Verification: This function is part of the library API and therefore essential on the one hand.
 *               On the other hand the QAC warning is correct, because this function is never
 *               called within the library. To solve this dillemma it is neccessary and suitable
 *               to disable the message.
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 19.1 (QAC message 5087)
 * Reason:       The section mapping concept (Mapping code, constants and data to specific linker sections) bases on
 *               a central include file containing all section mapping  defines and pragmas. This need to be included
 *               multiple times within the code. The file itself only contains those defines and pragmas.
 * Verification: This is the standard concept defined for AUTOSAR implementations
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 9.1 (QAC message 2962)
 * Reason:       Apparent using value of an uninitialized variable fcuCmd, used to convert API commands 
 *              (see r_fdl_command_t enum) into commands passed to the hardware.
 * Verification: The variable fcuCmd is set properly for all commands except R_FDL_CMD_READ, for which is not used 
 *               at all.
 *********************************************************************************************************************/

#define R_FDL_USERIF_C

/*********************************************************************************************************************
 * FDL header files include
 *********************************************************************************************************************/
#include "r_fdl_global.h"

/*********************************************************************************************************************
 * Module internal function prototypes
 *********************************************************************************************************************/
R_FDL_STATIC r_fdl_status_t R_FDL_Init_Variables (void);
R_FDL_STATIC void           R_FDL_UFct_EndCurrentOperation (r_fdl_status_t ret_enu);
R_FDL_STATIC r_fdl_status_t R_FDL_UFct_FlashOpStart (r_fdl_request_t * request_pstr);
R_FDL_STATIC r_fdl_flag_t   R_FDL_Handler_BusyAndSuspendPossible (void);
R_FDL_STATIC r_fdl_flag_t   R_FDL_Handler_ChkResume (r_fdl_status_t * tmpStat);
R_FDL_STATIC r_fdl_flag_t   R_FDL_Handler_ReactOnFatalErrors (r_fdl_status_t * tmpStat);
R_FDL_STATIC r_fdl_flag_t   R_FDL_Handler_StatusCheckAndSuspendOnReady (r_fdl_status_t * tmpStat);
R_FDL_STATIC r_fdl_flag_t   R_FDL_Handler_MultiOperation (r_fdl_status_t * tmpStat);
R_FDL_STATIC r_fdl_flag_t   R_FDL_UFct_StateNotStandBy (void);


/*********************************************************************************************************************
 * Global variables
 *********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   QAC message 2022
 * Reason:       Basically, global variables shouold be initialized. However, as the library is used for multiple
 *               compilers and not all compilers support explicit initialization for variables in not standard
 *               sections, this variable is initialized in the library initialization function rather than by the
 *               compiler.
 * Verification: test case
 *********************************************************************************************************************/
/* Note: 
 * The define "R_FDL_COV_ENABLED" is a specific define for library testing purpose only. 
 * The user application shall not set this define */
#if (!defined R_FDL_COV_ENABLED)
    #define R_FDL_START_SEC_VAR
    #include "r_fdl_mem_map.h"                                                                      /* PRQA S 5087 */
#endif

R_FDL_NOINIT r_fdl_data_t g_fdl_str;                                                                /* PRQA S 2022 */

#if (!defined R_FDL_COV_ENABLED)
    #define R_FDL_STOP_SEC_VAR
    #include "r_fdl_mem_map.h"                                                                      /* PRQA S 5087 */
#endif

/*********************************************************************************************************************
 * FDL internal section mapping definitions
 *********************************************************************************************************************/
#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.h"                                                                          /* PRQA S 5087 */

/*********************************************************************************************************************
 * Function name:  R_FDL_Init_Variables
 *********************************************************************************************************************/
/**
 * This function initializes the FDL internal variables and does the FDL configuration parameter
 * checks. \n
 * The following parameter checks are done:
 * - Descriptor variable is defined
 * - FDL pool is defined
 * - EEL pool is within FDL pool
 *
 * @param[in]  -
 * @return     Initialization status when returned from function call:
 *             - R_FDL_OK
 *             - R_FDL_ERR_PARAMETER
 */
/*********************************************************************************************************************/
R_FDL_STATIC r_fdl_status_t R_FDL_Init_Variables (void)
{
    r_fdl_status_t ret;
    uint16_t       blkEnd;

    ret = R_FDL_OK;

    /* ---------------------- Parameter independent initializations ---------------------------- */
    (g_fdl_str.reqSuspend_pstr)    = R_FDL_REQUEST_POINTER_UNDEFINED;
    (g_fdl_str.reqInt_pstr)        = R_FDL_REQUEST_POINTER_UNDEFINED;

    /* Reset misc flags */
    g_fdl_str.spdSpdRequest_enu    = R_FDL_FALSE;
    g_fdl_str.spdResRequest_enu    = R_FDL_FALSE;

    /* ---------------------- Initializations with parameter check ----------------------------- */
    /* Check EEL Flash window boundaries against Flash size */
    if (0u != g_fdl_str.RTCfg_pstr->fdlPoolSize_u16)
    {
        blkEnd =   (g_fdl_str.RTCfg_pstr->eelPoolStart_u16)
                 + (g_fdl_str.RTCfg_pstr->eelPoolSize_u16);
        if ( blkEnd >= (g_fdl_str.RTCfg_pstr->fdlPoolSize_u16 + 1u) )
        {
            ret = R_FDL_ERR_CONFIGURATION;
        }
    }
    else
    {
        ret = R_FDL_ERR_CONFIGURATION;
    }

    return (ret);
} /* R_FDL_Init_Variables */



/*********************************************************************************************************************
 * Function name:  R_FDL_Init
 *********************************************************************************************************************/
/**
 * User interface function:
 * This function initializes the FDL. It must be called before any execution of a FDL function.
 * Sequence:
 * - Call the function to initialize the library RAM and do parameter checks
 * - Call the function to initialize the FCU RAM
 * - Call the function to set the frequency information with frequency check
 *   - Frequency is within reasonable range between R_FDL_FBUSCLK_MIN and R_FDL_FBUSCLK_MAX
 *
 * In error case the library is set to not initialized (R_FDL_ISTAT_NOINIT)
 *
 * @param[in]  descriptor_pstr - Pointer to the FDL descriptor structure
 * @return     Initialization status when returned from function call:
 *             - R_FDL_OK                - Initialization was successful
 *             - R_FDL_ERR_CONFIGURATION - FDL configuration parameter error
 *             - R_FDL_ERR_PROTECTION    - Programming hardware reset was prohibited
 *             - R_FDL_ERR_INTERNAL      - Internal (HW) error during HW initialization
 */
/*********************************************************************************************************************/
r_fdl_status_t R_FDL_Init (const r_fdl_descriptor_t * descriptor_pstr)                              /*PRQA S 1503 */
{
    r_fdl_status_t ret;
    uint32_t       fdAdd;
    uint32_t       i;

    /* ---------------------- Reset all variables & HW --------------------------------------- */
    /* Reset the Flash environment for the case of EEPROM emulation after a "warm Reset"
       Execute in RAM as Flash is timely disabled */
    ret = R_FDL_FCUFct_Reset ();

    /* Initially clear the complete r_fdl_data structure */
    fdAdd = (uint32_t)(&g_fdl_str);                                                                 /* PRQA S 0306 */
    for (i = 0; i < sizeof (g_fdl_str); i++)
    {
        R_FDL_IFct_WriteMemoryU08 (fdAdd, 0u);
        fdAdd++;
    }

    g_fdl_str.iStat_enu = R_FDL_ISTAT_NOINIT;

    /* ---------------------- Do we have a descriptor at all? --------------------------------- */
    if (R_FDL_DESCRIPTOR_POINTER_UNDEFINED != descriptor_pstr)
    {
        /* Set pointer to FDL static configuration */
        g_fdl_str.RTCfg_pstr = descriptor_pstr;
    }
    else
    {
        ret = R_FDL_ERR_CONFIGURATION;
    }

    /* ---------------------- ID verification ------------------------------------------------- */
    if (R_FDL_OK == ret)
    {
        R_FDL_FCUFct_VerifyID (descriptor_pstr);

    /* ---------------------- Init global variables ------------------------------------------- */
        /* Initialize all library variables and check for parameter errors */
        ret = R_FDL_Init_Variables ();
    }

    if (R_FDL_OK == ret)
    {
        g_fdl_str.dfSize_u32 = R_FDL_FCUFct_GetDFSize ();
        #ifdef R_FDL_F1L_PATCH_DF_OVERSIZE
            g_fdl_str.dfSize_u32 *= 2uL;
        #endif

    /* ---------------------- FCU initialization ---------------------------------------------- */
        /* Initialize the FCU code RAM */
        ret = R_FDL_FCUFct_InitRAM ();
    }

    if (R_FDL_OK == ret)
    {
        /* Reset FCU again to clear any possible ECC errors */
        ret = R_FDL_FCUFct_Reset ();
    }

    if (R_FDL_OK == ret)
    {
        /* Configure the FCU frequency */
        ret = R_FDL_FCUFct_SetFrequency (descriptor_pstr->cpuFrequencyMHz_u16);
    }
    
    /* ---------------------- Set library to initialized (or not) ----------------------------- */
    if (R_FDL_OK == ret)
    {
        g_fdl_str.iStat_enu = R_FDL_ISTAT_NORMALOP;
    }

    return (ret);
} /* R_FDL_Init */


/*********************************************************************************************************************
 * Function name:  R_FDL_Execute
 *********************************************************************************************************************/
/**
 * User interface function:
 * This function initiates a Flash operation (Erase/Write/Read).
 * After initiation, the function R_FDL_Handler need to be called regularly to finish the operation.
 *
 * @param[in, out] request_pstr   Pointer to the operation request structure.
 *                                - Structure input elements: \n
 *                                  command_enu, bufAddr_u32, idx_u32, cnt_u16, accessType_enu
 *                                - Structure output element: \n
 *                                  status_enu
 * @return      ---
 */
/*********************************************************************************************************************/
void  R_FDL_Execute (r_fdl_request_t * request_pstr)                                /*PRQA S 1503 */
{
    r_fdl_status_t reqErr;

    reqErr = R_FDL_ERR_REJECTED;

    if ( (R_FDL_REQUEST_POINTER_UNDEFINED == g_fdl_str.reqInt_pstr) &&
         ( (R_FDL_ISTAT_NORMALOP == g_fdl_str.iStat_enu) ||
           (R_FDL_ISTAT_SUSPENDED == g_fdl_str.iStat_enu) ) )
    {
        /* Currently no operation ongoing */
        switch (request_pstr->command_enu)
        {
            case R_FDL_CMD_BLANKCHECK:
            {
                reqErr = R_FDL_UFct_FlashOpStart (request_pstr);
                break;
            }

#if (defined ENABLE_CMD_WRITE16B)
            case R_FDL_CMD_WRITE16B:
#endif
            case R_FDL_CMD_ERASE:
            case R_FDL_CMD_WRITE:
            {
                if ( R_FDL_TRUE == R_FDL_FCUFct_ChkStartable (request_pstr->command_enu) )
                {
                    reqErr = R_FDL_UFct_FlashOpStart (request_pstr);
                }
                break;
            }

            case R_FDL_CMD_READ:
            {
                reqErr = R_FDL_UFct_FlashOpStart (request_pstr);
                break;
            }


            default:
            {
                reqErr = R_FDL_ERR_COMMAND;
                break;
            }
        } /* switch */

    }

    if (R_FDL_BUSY == reqErr)
    {
        /* set internal pointer to the request structure, required by the handler */
        g_fdl_str.reqInt_pstr = request_pstr;

    }
    else
    {
        /* At operations end (In error case or if the operation requires no handler calls), reset
           the access type */
        request_pstr->accessType_enu = R_FDL_ACCESS_NONE;
    }

    /* Set the return state */
    request_pstr->status_enu = reqErr;

    return;
} /* R_FDL_Execute */

/*********************************************************************************************************************
 * Function name:  R_FDL_Handler_BusyAndSuspendPossible
 *********************************************************************************************************************/
/**
 * Part of the R_FDL_Handler function.
 * This function suspends an ongoing Flash operation if:
 * - suspend request flag set
 * - function is suspendable
 *
 * @return     handler function flow may continue afte this function or handler need to exit
 *             - R_FDL_TRUE  - continue handler
 *             - R_FDL_FALSE - exit handler
 */
/*********************************************************************************************************************/
R_FDL_STATIC r_fdl_flag_t R_FDL_Handler_BusyAndSuspendPossible (void)
{
    r_fdl_flag_t cont;

    cont = R_FDL_TRUE;

    if (R_FDL_TRUE == g_fdl_str.spdSpdRequest_enu)
    {
        if ( R_FDL_TRUE == R_FDL_FCUFct_ChkSuspendable () )
        {
            /* Must be called before changing g_fdl_str.iStat_enu because
               g_fdl_str.iStat_enu is checked in R_FDL_Standby! */
            R_FDL_FCUFct_Suspend ();

            g_fdl_str.spdSpdRequest_enu = R_FDL_FALSE;
            g_fdl_str.iStat_enu       = R_FDL_ISTAT_SUSPEND_PR;
            cont = R_FDL_FALSE;
        }
    }

    return (cont);
} /* R_FDL_Handler_BusyAndSuspendPossible */


/*********************************************************************************************************************
 * Function name:  R_FDL_Handler_ChkResume
 *********************************************************************************************************************/
/**
 * Part of the R_FDL_Handler function.
 * This function resumes a suspended Flash operation if:
 * - resume request flag set (can only be set if a function was suspended)
 * - No Flash operation is ongoing
 *
 * @param[out] tmpStat - Status return value. Is modified, if an operation is resumed.
 * @return     handler function flow may continue after this function or handler need to exit:
 *             - R_FDL_TRUE  - continue handler
 *             - R_FDL_FALSE - exit handler
 */
/*********************************************************************************************************************/
R_FDL_STATIC r_fdl_flag_t R_FDL_Handler_ChkResume (r_fdl_status_t * tmpStat)
{
    r_fdl_flag_t   cont;
    r_fdl_status_t res;

    cont = R_FDL_TRUE;

    if ( (R_FDL_REQUEST_POINTER_UNDEFINED == g_fdl_str.reqInt_pstr)
         && (R_FDL_TRUE == g_fdl_str.spdResRequest_enu) )                                          /* CCOV 0001 */
    {
        g_fdl_str.spdResRequest_enu = R_FDL_FALSE;

        /* Restore variables for resume */
        g_fdl_str.reqInt_pstr               = g_fdl_str.reqSuspend_pstr;
        g_fdl_str.reqSuspend_pstr           = R_FDL_REQUEST_POINTER_UNDEFINED;
        g_fdl_str.mulOp_str.flashAdd_u32    = g_fdl_str.spdMulOp_str.flashAdd_u32;
        g_fdl_str.mulOp_str.bufAdd_u32      = g_fdl_str.spdMulOp_str.bufAdd_u32;
        g_fdl_str.mulOp_str.flashAddEnd_u32 = g_fdl_str.spdMulOp_str.flashAddEnd_u32;
        g_fdl_str.mulOp_str.accessType_enu  = g_fdl_str.spdMulOp_str.accessType_enu;

        g_fdl_str.iStat_enu = R_FDL_ISTAT_NORMALOP;

        if (R_FDL_BUSY == g_fdl_str.spdResStatus_enu)
        {
            res = R_FDL_FCUFct_SwitchMode (R_FCU_MODE_PE);
            if (R_FDL_OK != res)
            {
                /* protection error during mode switching */
                *tmpStat = res;
            }
            else
            {
                R_FDL_FCUFct_Resume ();

                g_fdl_str.reqInt_pstr->status_enu = g_fdl_str.spdResStatus_enu;
            }
        }
        else
        {
            (*tmpStat) = g_fdl_str.spdResStatus_enu;
            /* In order to support continuing Multi-Operations, we need to patch the
               R_FDL_OK to R_FDL_BUSY. Errors result in operation end (Write, Erase, BC errors) */
            if ( ( R_FDL_OK == (*tmpStat) )
                 && (g_fdl_str.mulOp_str.flashAdd_u32 < g_fdl_str.mulOp_str.flashAddEnd_u32) )
            {
                res = R_FDL_FCUFct_SwitchMode (R_FCU_MODE_PE);
                if (R_FDL_OK != res)
                {
                    /* protection error during mode switching */
                    *tmpStat = res;
                }
                else
                {
                    g_fdl_str.reqInt_pstr->status_enu = R_FDL_BUSY;
                    (*tmpStat) = R_FDL_BUSY;
                }
            }
        }

        cont = R_FDL_FALSE;
    }

    return (cont);
} /* R_FDL_Handler_ChkResume */



/*********************************************************************************************************************
 * Function name:  R_FDL_Handler_ReactOnFatalErrors
 *********************************************************************************************************************/
/**
 * Part of the R_FDL_Handler function.
 * Read out Flash operation error status after operation end and react on fatal errors.
 *
 * @param[out] tmpStat - Status return value. Is set to internal error in case of detection
 *                       of a fatal HW error
 * @return     handler function flow may continue after this function or handler need to exit:
 *             - R_FDL_TRUE  - continue handler
 *             - R_FDL_FALSE - exit handler
 */
/*********************************************************************************************************************/
R_FDL_STATIC r_fdl_flag_t R_FDL_Handler_ReactOnFatalErrors (r_fdl_status_t * tmpStat)
{
    r_fdl_flag_t    cont;
    r_fdl_status_t  stat;

    cont = R_FDL_TRUE;

    /* Check for fatal error */
    stat = R_FDL_FCUFct_CheckFatalError(); /* protection or internal error */
    
    if ( R_FDL_OK != stat )
    {
        R_FDL_FCUFct_ClearStatus ();
        (void)R_FDL_FCUFct_SwitchMode (R_FCU_MODE_USER);    /* We ignore protection error here as we
                                                               anyhow have a fatal error */
        (*tmpStat) = stat;

        cont = R_FDL_FALSE;
    }

    return (cont);
} /* R_FDL_Handler_ReactOnFatalErrors */


/*********************************************************************************************************************
 * Function name:  R_FDL_Handler_StatusCheckAndSuspendOnReady
 *********************************************************************************************************************/
/**
 * Part of the R_FDL_Handler function.
 * Get and judge Flash operation result (not fatal errors, just operation results) and
 * do further suspend processing in case of pending suspend request or already suspended
 * Flash operation.
 *
 * @param[out] tmpStat - Status return value. Is set to operation result or to suspended in
 *                       case of suspend processing.
 * @return     handler function flow may continue after this function or handler need to exit:
 *             - R_FDL_TRUE  - continue handler
 *             - R_FDL_FALSE - exit handler
 */
/*********************************************************************************************************************/
R_FDL_STATIC r_fdl_flag_t R_FDL_Handler_StatusCheckAndSuspendOnReady (r_fdl_status_t * tmpStat)
{
    r_fdl_flag_t   cont;
    r_fdl_status_t res;

    cont = R_FDL_TRUE;

    /* Get operation status after operation end and reset the hardware status */
    (*tmpStat) = R_FDL_FCUFct_GetStat ();
    R_FDL_FCUFct_ClearStatus ();

    /* Suspend handling
       - suspend possible, part 2 (Flash operation is suspended now -or-
       - suspend impossible (operation finished but suspend request still active) */
    if (R_FDL_TRUE == g_fdl_str.spdSpdRequest_enu)
    {
        /* suspend was impossible --> handle it now after operation completion */
        g_fdl_str.spdSpdRequest_enu = R_FDL_FALSE;
        g_fdl_str.iStat_enu = R_FDL_ISTAT_SUSPEND_PR;
    }
    if (R_FDL_ISTAT_SUSPEND_PR == g_fdl_str.iStat_enu)
    {
        res = R_FDL_FCUFct_SwitchMode (R_FCU_MODE_USER);
        if (R_FDL_OK == res)
        {
            g_fdl_str.spdResStatus_enu = (*tmpStat);
            (*tmpStat) = R_FDL_SUSPENDED;

            /* Backup variables for resume */
            g_fdl_str.reqSuspend_pstr              = g_fdl_str.reqInt_pstr;
            g_fdl_str.spdMulOp_str.flashAdd_u32    = g_fdl_str.mulOp_str.flashAdd_u32;
            g_fdl_str.spdMulOp_str.bufAdd_u32      = g_fdl_str.mulOp_str.bufAdd_u32;
            g_fdl_str.spdMulOp_str.flashAddEnd_u32 = g_fdl_str.mulOp_str.flashAddEnd_u32;
            g_fdl_str.spdMulOp_str.accessType_enu  = g_fdl_str.mulOp_str.accessType_enu;

            g_fdl_str.iStat_enu = R_FDL_ISTAT_SUSPENDED;
        }
        else
        {
            (*tmpStat) = R_FDL_ERR_PROTECTION;
        }

        cont = R_FDL_FALSE;
    }

    return (cont);
} /* R_FDL_Handler_StatusCheckAndSuspendOnReady */


/*********************************************************************************************************************
 * Function name:  R_FDL_Handler_MultiOperation
 *********************************************************************************************************************/
/**
 * Part of the R_FDL_Handler function.
 *
 * In case of multi-operations (erase multiple blocks or write multiple half words), after end
 * of a single Flash erase/write Flash operation, the next operation is started.
 *
 * @param[in, out] tmpStat - current operation status. Used to judge previous operation result
 *                           and is updated in case of multi-operation requiring start of new
 *                           Flash operation
 * @return     handler function flow may continue after this function or handler need to exit:
 *             - R_FDL_TRUE  - continue handler
 *             - R_FDL_FALSE - exit handler
 */
/*********************************************************************************************************************/
R_FDL_STATIC r_fdl_flag_t R_FDL_Handler_MultiOperation (r_fdl_status_t * tmpStat)
{
    r_fdl_flag_t    cont;
    uint32_t        cnt;
    r_fdl_command_t cmd;

    cont = R_FDL_TRUE;
    cmd  = g_fdl_str.reqInt_pstr->command_enu;

    /* Check if more data to handle:
       - erase, write, blank check operation
       - internal status = OK
       - more data to erase/write */
    if ( ( R_FDL_OK == (*tmpStat) )
         && (g_fdl_str.mulOp_str.flashAdd_u32 < g_fdl_str.mulOp_str.flashAddEnd_u32) )
    {
#if (defined ENABLE_CMD_WRITE16B)
        if ( (R_FDL_CMD_WRITE == cmd) || (R_FDL_CMD_WRITE16B == cmd) )                          /* PRQA S 0505 */
#else
        if (R_FDL_CMD_WRITE == cmd)
#endif
        {
#if (defined ENABLE_CMD_WRITE16B)
            if (R_FDL_CMD_WRITE == cmd)
            {
                cnt = R_FDL_WRITE_SIZE;
            }
            else
            {
                cnt = R_FDL_WRITE_SIZE_16B;
            }
#else
            cnt = R_FDL_WRITE_SIZE;
#endif

            (*tmpStat) = R_FDL_FCUFct_StartWriteOperation (g_fdl_str.mulOp_str.bufAdd_u32,
                                                           g_fdl_str.mulOp_str.flashAdd_u32,
                                                           cnt,
                                                           g_fdl_str.mulOp_str.accessType_enu);

            g_fdl_str.mulOp_str.flashAdd_u32 += cnt;
            g_fdl_str.mulOp_str.bufAdd_u32   += cnt;
        }
        else if (R_FDL_CMD_ERASE == cmd)                                                        /*PRQA S 0505*/
        {
            (*tmpStat) = R_FDL_FCUFct_StartBCEraseOperation (g_fdl_str.mulOp_str.flashAdd_u32,
                                                             (g_fdl_str.mulOp_str.flashAdd_u32 + R_FDL_BLOCK_SIZE) - 1u,
                                                             R_FCU_CMD_ERASE,
                                                             g_fdl_str.mulOp_str.accessType_enu);

            g_fdl_str.mulOp_str.flashAdd_u32 += R_FDL_BLOCK_SIZE;
        }
        else /* blank check */
        {
            cnt = ( (g_fdl_str.mulOp_str.flashAddEnd_u32 + 1uL) - g_fdl_str.mulOp_str.flashAdd_u32 );
            /* Limit count to max */
            R_FDL_IFct_CalcFOpUnitCnt_BC (&cnt, g_fdl_str.mulOp_str.flashAdd_u32);

            (*tmpStat) = R_FDL_FCUFct_StartBCEraseOperation (g_fdl_str.mulOp_str.flashAdd_u32,
                                                             ( (g_fdl_str.mulOp_str.flashAdd_u32 + cnt ) - 1u),
                                                             R_FCU_CMD_BLANKCHECK,
                                                             g_fdl_str.mulOp_str.accessType_enu);

            g_fdl_str.mulOp_str.flashAdd_u32 += cnt;
        }


        if ( R_FDL_BUSY != (*tmpStat) )
        {
            /* we don't return the protection error resulting from switch mode as we have here
               an error anyhow */
            (void)R_FDL_FCUFct_SwitchMode (R_FCU_MODE_USER);
        }

        cont = R_FDL_FALSE;
    }

    return (cont);
} /* R_FDL_Handler_MultiOperation */


/*********************************************************************************************************************
 * Function name:  R_FDL_Handler
 *********************************************************************************************************************/
/**
 * User interface function:
 * This function forwards an initiated Flash operation until it is finished. At operation end the
 * result is set in the request structure.
 * After initiation by R_FDL_Execute, the function R_FDL_Handler need to be called regularly to finish
 * the operation.

 * @param[out]     ---
 * @return         ---
 *
 * The function returns the operation result in the status variable, passed to
 * the R_FDL_Execute variable (request.status_enu)
 */
/*********************************************************************************************************************/

/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 1.2 (QAC message 0505)
 * Reason:       QAC claims referencing a possibly undefined pointer.
 * Verification: Reviewed, that this is not possible. The pointer is always defined
 *********************************************************************************************************************/
void R_FDL_Handler (void)                                                        /*PRQA S 1503 */
{
    r_fdl_flag_t   contHdrFct;
    r_fdl_status_t tmpStatus;
    r_fdl_status_t res;

    tmpStatus = R_FDL_BUSY;

    /* Check if the handler has something to do, block on not initialized library and on StandBy processing */
    if ( ( R_FDL_TRUE == R_FDL_UFct_StateNotStandBy () ) &&
         ( (R_FDL_REQUEST_POINTER_UNDEFINED != g_fdl_str.reqInt_pstr) ||
           (R_FDL_TRUE == g_fdl_str.spdResRequest_enu) ) )
    {
        /* ----- Suspend / Resume management --------------------------------------------------- */

        /* Suspend handling (suspend possible, part 1)*/
        contHdrFct = R_FDL_Handler_BusyAndSuspendPossible ();

        /* Resume handling */
        if (R_FDL_TRUE == contHdrFct)
        {
            contHdrFct = R_FDL_Handler_ChkResume (&tmpStatus);
        }

        /* ----- Normal operation -------------------------------------------------------------- */
        if (R_FDL_TRUE == contHdrFct)
        {
            contHdrFct = R_FDL_Handler_ReactOnFatalErrors (&tmpStatus);
        }

        /* Check if the FCU is busy */
        if (R_FDL_TRUE == contHdrFct)
        {
            contHdrFct = R_FDL_FCUFct_ChkReady ();
        }

        /* Judge operation status and do suspend handling part 2 */
        if (R_FDL_TRUE == contHdrFct)
        {
            contHdrFct = R_FDL_Handler_StatusCheckAndSuspendOnReady (&tmpStatus);
        }

        /* Multi operation (Write/Erase) state machine */
        if (R_FDL_TRUE == contHdrFct)
        {
            contHdrFct = R_FDL_Handler_MultiOperation (&tmpStatus);
        }

        /* Normal operation end */
        if (R_FDL_TRUE == contHdrFct)
        {
            res = R_FDL_FCUFct_SwitchMode (R_FCU_MODE_USER);
            if (R_FDL_OK != res)
            {
                if (R_FDL_OK == tmpStatus)
                {
                    tmpStatus = res;
                }
            }
        }

        if (R_FDL_BUSY != tmpStatus)
        {
            R_FDL_UFct_EndCurrentOperation (tmpStatus);
        }

        #ifdef PATCH_TO_SIMULATE_ERRORS
            tstData_str.simCntHdr_u32++;
        #endif

    }
} /* R_FDL_Handler */


/*********************************************************************************************************************
 * Function name:  R_FDL_GetVersionString
 *********************************************************************************************************************/
/**
 * User interface function:
 * Returns the pointer to the library version string, stores in the library code section.
 *
 * @param      ---
 * @return     pointer to the version string in Flash
 */
/*********************************************************************************************************************/
#define R_FDL_START_SEC_CONST
#include "r_fdl_mem_map.h"                                                                          /* PRQA S 5087 */

const uint8_t *R_FDL_GetVersionString (void)                                                        /* PRQA S 1503 */
{
    static const uint8_t r_fdl_vStr[] = R_FDL_VERSION_STRING;

    return (&r_fdl_vStr[0]);
}

#define R_FDL_STOP_SEC_CONST
#include "r_fdl_mem_map.h"                                                                          /* PRQA S 5087 */

/*********************************************************************************************************************
 * Function name:  R_FDL_SuspendRequest
 *********************************************************************************************************************/
/**
 * User interface function:
 * Sets the suspend request flag for the write or erase operation
 *
 * Note:
 * The operation is not immediately suspended. Suspend handling is controlled by R_FDL_Handler.
 * The suspend status is returned by the status variable of the request structure (Set in
 * R_FDL_Handler).
 *
 * Suspend request handling:
 * - Reject if
 *     - we have no active Flash operation
 *     - we have already a Flash operation suspended
 * - Reset resume request if set (then we have a not yet handled resume request)
 * - Set suspend request if we have an operation ongoing and we are not already in suspend
 *   processing
 *
 * @param      ---
 * @return     result of the suspend request
 *             - R_FDL_OK           - Request accepted
 *             - R_FDL_ERR_REJECTED - Request rejected
 */
/*********************************************************************************************************************/
r_fdl_status_t R_FDL_SuspendRequest (void)                                                          /*PRQA S 1503 */
{
    r_fdl_status_t ret;

    ret = R_FDL_ERR_REJECTED;

    /* Block on:
          - not initialized library
          - StandBy processing       */
    if ( R_FDL_TRUE == R_FDL_UFct_StateNotStandBy () )
    {
        /* Reset a possibly set resume request that is not yet handled */
        if (R_FDL_TRUE == g_fdl_str.spdResRequest_enu)
        {
            g_fdl_str.spdResRequest_enu = R_FDL_FALSE;
            ret = R_FDL_OK;
        }
        else
        {
            /* Set the request flag only if we are busy and not in suspend processing */
            if ( (R_FDL_REQUEST_POINTER_UNDEFINED != g_fdl_str.reqInt_pstr)
                 && (R_FDL_ISTAT_NORMALOP == g_fdl_str.iStat_enu) )
            {
                ret = R_FDL_OK;
                g_fdl_str.spdSpdRequest_enu = R_FDL_TRUE;
            }
            else
            {
                /* Nothing to do if we are already in suspend processing  */
                if ( (R_FDL_ISTAT_SUSPEND_PR == g_fdl_str.iStat_enu)
                     || (R_FDL_ISTAT_SUSPENDED  == g_fdl_str.iStat_enu) )
                {
                    ret = R_FDL_OK;
                }
            }
        }
    }

    return (ret);
} /* R_FDL_SuspendRequest */


/*********************************************************************************************************************
 * Function name:  R_FDL_ResumeRequest
 *********************************************************************************************************************/
/**
 * User interface function:
 * Sets the resume request flag for the write or erase operation
 *
 * Note:
 * The operation is not immediately resumed. Resume handling is controlled by R_FDL_Handler.
 * The status is returned by the status variable of the request structure (Set in
 * R_FDL_Handler).
 *
 * Resume request handling:
 * - Reset suspend request if set (then we have a not yet handled suspend request)
 * - Set resume request if we have a suspended operation (reqSuspend_pstr defined)
 *   and we have not already a resume request
 * - Reject all other conditions
 *
 * @param      ---
 * @return     result of the resume request
 *             - R_FDL_OK           - Request accepted
 *             - R_FDL_ERR_REJECTED - Request rejected
 */
/*********************************************************************************************************************/
r_fdl_status_t R_FDL_ResumeRequest (void)                                                           /*PRQA S 1503 */
{
    r_fdl_status_t ret;

    ret = R_FDL_OK;

    /* Block on not initialized library and on StandBy processing */
    if ( R_FDL_TRUE == R_FDL_UFct_StateNotStandBy () )
    {
        if (R_FDL_TRUE == g_fdl_str.spdSpdRequest_enu)
        {
            g_fdl_str.spdSpdRequest_enu = R_FDL_FALSE;
        }
        else
        {
            /* Set the request flag only if we are already suspended or in suspend processing */
            if ( (R_FDL_ISTAT_SUSPEND_PR == g_fdl_str.iStat_enu)
                 || (R_FDL_ISTAT_SUSPENDED == g_fdl_str.iStat_enu) )
            {
                g_fdl_str.spdResRequest_enu = R_FDL_TRUE;
            }
            else
            {
                ret = R_FDL_ERR_REJECTED;
            }
        }
    }
    else
    {
        ret = R_FDL_ERR_REJECTED;
    }

    return (ret);
} /* R_FDL_ResumeRequest */


/*********************************************************************************************************************
 * Function name:  R_FDL_Standby
 *********************************************************************************************************************/
/**
 * User interface function:
 * Prepares the HW for fast standby entry:
 * - on write end erase
 * - blank check is not suspendable, here the function is without effect
 *
 * This function can be called asynchronous (e.g. interrupt function) and so need to take
 * care of the current hardware status in order to restore it later on during wakeup
 *
 * Note:
 * the function need to be called continuously until the result is != R_FDL_BUSY
 *
 * @param      ---
 * @return     result of the standby operation
 *             - R_FDL_OK           - Flash hardware is in standby or ready (no more Flash operation)
 *             - R_FDL_BUSY         - Flash hardware is still busy. Repeat calling the function
 *             - R_FDL_ERR_REJECTED - Rejected, as the library is not initialized
 */
/*********************************************************************************************************************/
r_fdl_status_t R_FDL_StandBy (void)                                                /*PRQA S 1503 */
{
    r_fdl_status_t ret;

    /* Allow execution in each initialized state except StandBy */
    if ( ( R_FDL_TRUE == R_FDL_UFct_StateNotStandBy () )
         || (R_FDL_ISTAT_STANDBY_PR == g_fdl_str.iStat_enu) )
    {
        /* On Standby processing start, backup the internal Status */
        if (R_FDL_ISTAT_STANDBY_PR != g_fdl_str.iStat_enu)
        {
            g_fdl_str.stByIStatBackUp_enu = g_fdl_str.iStat_enu;

            /* Set to standby processing. By that, other EEL operations are blocked */
            g_fdl_str.iStat_enu = R_FDL_ISTAT_STANDBY_PR;
        }

        /* only operate standby, if any Flash operation is ongoing */
        if ( R_FDL_FALSE == R_FDL_FCUFct_ChkReady () )
        {
            /* hardware is still busy */
            ret = R_FDL_BUSY;

            /* only operate standby if the Flash operation is supendable
               additionally check if we are  not already suspended or in suspend
               processing */
            if ( R_FDL_TRUE == R_FDL_FCUFct_ChkSuspendable () )
            {
                R_FDL_FCUFct_Suspend ();
            }
        }
        else
        {
            /* hardware is no longer busy, set library into standby */
            g_fdl_str.iStat_enu = R_FDL_ISTAT_STANDBY;
            ret = R_FDL_OK;
        }
    }
    else
    {
        /* library is not initialized */
        ret = R_FDL_ERR_REJECTED;
    }

    return (ret);
} /* R_FDL_StandBy */

/*********************************************************************************************************************
 * Function name:  R_FDL_WakeUp
 *********************************************************************************************************************/
/**
 * User interface function:
 * Wake up the hardware from standby
 *
 * @param      ---
 * @return     result of the initialization check
 *             - R_FDL_OK           - Wakeup succeeded
 *             - R_FDL_ERR_REJECTED - Rejected, as the library is not initialized
 */
/*********************************************************************************************************************/
r_fdl_status_t R_FDL_WakeUp (void)                                                                  /*PRQA S 1503 */
{
    r_fdl_status_t ret;

    /* We can only wakeup if we have been in standby before */
    if (R_FDL_ISTAT_STANDBY == g_fdl_str.iStat_enu)
    {
        ret = R_FDL_OK;

        g_fdl_str.iStat_enu = g_fdl_str.stByIStatBackUp_enu;

        /* check if we need to wakeup */
        if ( R_FDL_TRUE == R_FDL_FCUFct_ResumeChkNeed () )
        {
            R_FDL_FCUFct_Resume ();
        }
    }
    else
    {
        ret = R_FDL_ERR_REJECTED;
    }

    return (ret);
} /* R_FDL_WakeUp */

/*********************************************************************************************************************
 * Function name:  R_FDL_UFct_FlashOpStart
 *********************************************************************************************************************/
/**
 * Extract information required for a Flash operation and call the function which starts the operation.
 *
 * @param[in]  request_pstr - pointer to the operation request structure
 *
 * @return     Parameter check result
 *             - R_FDL_BUSY
 *             - R_FDL_ERR_PARAMETER
 *             - R_FDL_ERR_PROTECTION
 *             - R_FDL_OK (Read operation)
 *             - R_FDL_ERR_ECC_SED (Read operation)
 *             - R_FDL_ERR_ECC_DED (Read operation)
 */
/*********************************************************************************************************************/
R_FDL_STATIC r_fdl_status_t R_FDL_UFct_FlashOpStart (r_fdl_request_t * request_pstr)
{
    r_fdl_status_t ret;
    uint32_t       addFlash,
                   addBuf,
                   cntCurOp,             /* size in bytes of one operation unit */
                   cntTotal,             /* size in bytes of the entire operation */
                   granularityCurOp,
                   addEndCurOp;
    r_fdl_accessType_t accType;
    r_fdl_command_t    cmd;
    uint8_t            fcuCmd;

    addBuf      = (request_pstr->bufAddr_u32);
    addFlash    = (request_pstr->idx_u32);
    cntTotal    = (request_pstr->cnt_u16);
    granularityCurOp = R_FDL_WRITE_SIZE;        /* granularityCurOp has the default value for all commands except WRITE_16B */
    accType     = (request_pstr->accessType_enu);
    cmd         = (request_pstr->command_enu);

    if (R_FDL_CMD_ERASE == cmd)
    {
        addFlash = ( (request_pstr->idx_u32) << R_FDL_BLOCK_SIZE_2N );
        cntTotal <<= R_FDL_BLOCK_SIZE_2N;

        /* granularityCurOp has the default value */
        cntCurOp = (1 << R_FDL_BLOCK_SIZE_2N);

        /* Set buffer address to a valid address */
        addBuf = 0x00000001uL;

        fcuCmd   = R_FCU_CMD_ERASE;
    }
    else if (R_FDL_CMD_BLANKCHECK == cmd)
    {
        cntTotal *= R_FDL_WRITE_SIZE;
        cntCurOp = cntTotal;

        /* Limit count to max */
        R_FDL_IFct_CalcFOpUnitCnt_BC (&cntCurOp, addFlash);

        /* Set buffer address to a valid address */
        addBuf = 0x00000001uL;

        fcuCmd      = R_FCU_CMD_BLANKCHECK;
    }
    else if (R_FDL_CMD_WRITE == cmd)
    {
        /* write 4 bytes (1 words) at once */
        cntCurOp = R_FDL_WRITE_SIZE;
        cntTotal *= R_FDL_WRITE_SIZE;

        fcuCmd      = R_FCU_CMD_WRITE;
    }
#if (defined ENABLE_CMD_WRITE16B)
    else if (R_FDL_CMD_WRITE16B == cmd)
    {
        /* write 16 bytes (4 words) at once */
        cntCurOp = R_FDL_WRITE_SIZE_16B;
        cntTotal *= R_FDL_WRITE_SIZE_16B;

        granularityCurOp = cntCurOp;

        fcuCmd      = R_FCU_CMD_WRITE;
    }
#endif
    else
    {
        /* Read */
        cntTotal *= R_FDL_WRITE_SIZE;
        cntCurOp = cntTotal;
    }

    addEndCurOp = (addFlash + cntCurOp) - 1uL;

    /* Check against invalid buffer address: */
    /* Only for commands:
        - R_FDL_CMD_WRITE
        - R_FDL_CMD_WRITE16B
        - R_FDL_CMD_READ                     */
    if (R_FDL_NULL == addBuf)
    {
        ret = R_FDL_ERR_PARAMETER;
    }
    else
    {
        ret = R_FDL_IFct_ChkAccessBoundaries (addFlash, cntTotal, accType, granularityCurOp);
    }

    if (R_FDL_BUSY == ret)
    {
        if (R_FDL_CMD_READ == cmd)
        {
            ret = R_FDL_FCUFct_ReadOperation ( (volatile uint32_t *)(&addFlash),
                                               addBuf,
                                               (cntTotal / R_FDL_WRITE_SIZE) );
            request_pstr->idx_u32 = addFlash;   /* Store posssible fail address to request structure */
        }
        else
        {
            ret = R_FDL_FCUFct_SwitchMode (R_FCU_MODE_PE);
            if (R_FDL_OK == ret)
            {
                if (R_FDL_CMD_ERASE == cmd)
                {
                    ret = R_FDL_FCUFct_StartBCEraseOperation (addFlash, addEndCurOp, fcuCmd, accType); /*PRQA S 2962*/
                }
                else if (R_FDL_CMD_BLANKCHECK == cmd)
                {
                    ret = R_FDL_FCUFct_StartBCEraseOperation (addFlash, addEndCurOp, fcuCmd, accType);
                }
                else /* Write */
                {
                    ret = R_FDL_FCUFct_StartWriteOperation (addBuf, addFlash, cntCurOp, accType);

                    g_fdl_str.mulOp_str.bufAdd_u32       = addBuf + cntCurOp;                       /* Next Source Address */
                }

                /* Prepare for multi-word write */
                g_fdl_str.mulOp_str.flashAdd_u32     = addEndCurOp + 1uL;
                g_fdl_str.mulOp_str.flashAddEnd_u32  = (addFlash + cntTotal) - 1uL;                 /* Source End Address */
                g_fdl_str.mulOp_str.accessType_enu   = accType;
            }
        }
    }

    return (ret);
} /* R_FDL_UFct_FlashOpStart */


/*********************************************************************************************************************
 * Function name:  R_FDL_UFct_EndCurrentOperation
 *********************************************************************************************************************/
/**
 * At the end of a Flash operation, this function updates the request structure elements and
 * resets the library internal pointer to this structure.
 *
 * @param[in]  ret_enu - status return value
 * @return     ---
 *
 * The function modifies the global structure g_fdl_str.reqInt_pstr to set the operation
 * status
*/
/*********************************************************************************************************************/
R_FDL_STATIC void R_FDL_UFct_EndCurrentOperation (r_fdl_status_t ret_enu)
{
    (g_fdl_str.reqInt_pstr)->status_enu = ret_enu;
    if ( (R_FDL_CMD_BLANKCHECK == (g_fdl_str.reqInt_pstr)->command_enu) && (R_FDL_ERR_BLANKCHECK == ret_enu) )
    {
        (g_fdl_str.reqInt_pstr)->idx_u32 = g_fdl_str.opFailAddr_u32;
    }
    (g_fdl_str.reqInt_pstr)->accessType_enu = R_FDL_ACCESS_NONE;
    (g_fdl_str.reqInt_pstr)                 = R_FDL_REQUEST_POINTER_UNDEFINED;
}

/*********************************************************************************************************************
 * Function name:  R_FDL_UFct_StateNotStandBy
 *********************************************************************************************************************/
/**
 * Check if the library is initialized and not in StandBy or StandBy processing
 *
 * @param[in]  ---
 * @return     - R_FDL_TRUE   Library is initialized
 *             - R_FDL_FALSE  Library is not initialized
*/
/*********************************************************************************************************************/
R_FDL_STATIC r_fdl_flag_t R_FDL_UFct_StateNotStandBy (void)
{
    r_fdl_flag_t ret;

    if ( (R_FDL_ISTAT_NORMALOP == g_fdl_str.iStat_enu)
         || ( (R_FDL_ISTAT_SUSPEND_PR == g_fdl_str.iStat_enu)
              || (R_FDL_ISTAT_SUSPENDED == g_fdl_str.iStat_enu) ) )
    {
        ret = R_FDL_TRUE;
    }
    else
    {
        ret = R_FDL_FALSE;
    }


    return (ret);
} /* R_FDL_UFct_StateNotStandBy */

/*********************************************************************************************************************/
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.h"                                                                          /* PRQA S 5087 */

/*********************************************************************************************************************/


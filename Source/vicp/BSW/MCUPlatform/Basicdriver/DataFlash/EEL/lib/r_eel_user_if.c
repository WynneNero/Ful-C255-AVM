#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_OFF 0292
#endif
/*********************************************************************************************************************
 * Library       : EEPROM Emulation Library for Renesas RH850 devices
 *
 * File Name     : $Source: r_eel_user_if.c $
 * Lib. Version  : $RH850_EEL_LIB_VERSION_T01: V2.01 $
 * Mod. Revision : $Revision: 1.27 $
 * Mod. Date     : $Date: 2017/02/07 09:12:16JST $
 * Device(s)     : RV40 Flash based RH850 microcontroller
 * Description   : EEL user interface functions
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
 * MISRA Rule:   MISRA-C 2004 rule 7.13 (QAC message 0491)
 *               Array subscripting applied to an object of pointer type
 * Reason:       Pointers are required to reference arrays, defined in the user application.
 * Verification: Global variables are pointing to the tables. These are set in R_EEL_Init and are
 *               often used. Wrong pointer type or address would lead to many test cases fail.
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 19.1 (QAC message 5087)
 * Reason:       #include statements in a file should only be preceded by other preprocessor directives or comments.
 *               This violation is intended as the header file shall be included multiple times in the source
 * Verification: Just used for AUTOSAR compliant header file inclusion
 *********************************************************************************************************************/

/*********************************************************************************************************************
 *  MISRA Rule:   MISRA-C 2004 rule 14.1 (QAC message 1503), rule 8.10 (QAC message 1505)
 *  Reason:       This function is not used within the library, it is only used by the user
 *                application.
 *  Verification: This function is part of the library API and therefore essential on the one hand.
 *                On the other hand the QAC warning is correct, because this function is never
 *                called within the library. To solve this dilemma it is necessary and suitable
 *                to disable the message.
 *********************************************************************************************************************/

/*********************************************************************************************************************
 *  MISRA Rule:   MISRA-C 2004 rule 21.1 (QAC message 3689)
 * Reason:       Misra requires to check array bounds wherever accessing arrays.
 *               As array accesses are largely used in the module and boundary checks cost a lot
 *               performance, they are largely omitted.
 * Verification: In this module, arrays are largely accessed by enumerations.
 *               The used enumerations have members with sequential defined values starting with 0
 *               Furthermore, the last enumeration value defines the array size.
 *               So, accessing the arrays with the enumerations only is save. This check is not
 *               disabled, where no enumerations are used
 *********************************************************************************************************************/

/*********************************************************************************************************************
 *  MISRA Rule:   - (QAC message 2814, 2824)
 *  Reason:       Possible dereference of NULL pointers or arithmetic operations with NULL pointers:
 *                pointers to descriptor or internally assigned pointers are often used in the library for function
 *                data return and for global data access
 *  Verification: Parameter passing: only done to pass data to upper layer function variables. malfunction unreasonable
 *                Access to global variables: NULL pointer access unreasonable as the accessed pointers are assigned
 *                during EEL init or process start
 *********************************************************************************************************************/
#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_OFF 2814
#endif

#define R_EEL_USERIF_C

/*********************************************************************************************************************
 * FDL header files include
 *********************************************************************************************************************/
#include "R_EEL_Global.h"

/*********************************************************************************************************************
 * Global data declarations
 *********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   QAC message 2022
 * Reason:       Basically, global variables should be initialized. However, as the library is used for multiple
 *               compilers and not all compilers support explicit initialization for variables in not standard
 *               sections, this variable is initialized in the library initialization function rather than by the
 *               compiler.
 * Verification: test case
 *********************************************************************************************************************/
#define R_EEL_START_SEC_VAR
#include "r_eel_mem_map.h"                                                                          /* PRQA S 5087 */

#ifdef R_EEL_DEBUG_BASICINFO
    R_FDL_NOINIT uint32_t eel_dummy1; /* Dummy variable for checking space before the structure is not modified */
#endif

R_FDL_NOINIT r_eel_data_t g_eel_str;                                                              /* PRQA S 2022 */

#ifdef R_EEL_DEBUG_BASICINFO
    R_FDL_NOINIT uint32_t eel_dummy2; /* Dummy variable for checking space after the structure is not modified */
#endif

#define R_EEL_STOP_SEC_VAR
#include "r_eel_mem_map.h"                                                                          /* PRQA S 5087 */
/*********************************************************************************************************************/


/*********************************************************************************************************************
 * Module internal function prototypes
 *********************************************************************************************************************/
R_EEL_STATIC r_eel_flag_t   R_EEL_UFct_ChkLibraryInitialized (void);
R_EEL_STATIC r_eel_status_t R_EEL_UFct_Read (r_eel_request_t * request);
R_EEL_STATIC r_eel_status_t R_EEL_UFct_Write (r_eel_process_id_t pId,
                                              r_eel_request_t * request,
                                              r_eel_flag_t invalidate);


/*********************************************************************************************************************
 * Compiler specific section defines
 *********************************************************************************************************************/
#define R_EEL_START_SEC_PUBLIC_CODE
#include "r_eel_mem_map.h"                                                                          /* PRQA S 5087 */


/*********************************************************************************************************************
 * Function name:  R_EEL_UFct_ChkLibraryInitialized
 *********************************************************************************************************************/
/**
 *  Function to check the library life cycle status. On any initialized status the function
 *  returns R_EEL_TRUE, otherwise R_EEL_FALSE.
 *  Furthermore, the status reset to default in case of undefined status variable value.
 *
 *  @param[in]  -
 *  @return     library initialization status
 *              - R_EEL_TRUE:  Library has any initialized value
 *              - R_EEL_FALSE: Library is not initialized
 */
/*********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 13.7, 14.1 (QAC message 3356, 3359, 3201)
 * Reason:       QAC claims that the equation & result is always true and that the code below is not
 *               reachable.
 * Verification: The tested variable might be undefined on program start. This is checked here
 *********************************************************************************************************************/


R_EEL_STATIC r_eel_flag_t R_EEL_UFct_ChkLibraryInitialized (void)
{
    r_eel_flag_t ret;

    if ( (R_EEL_LCSTS_NOT_INITIALIZED > g_eel_str.r_eel_lcSts_enu) ||         /* PRQA S 3356 */
         (R_EEL_LCSTS_END < g_eel_str.r_eel_lcSts_enu) )                      /* PRQA S 3356, 3359 */
    {                                                                         /* PRQA S 3201 */
        g_eel_str.r_eel_lcSts_enu = R_EEL_LCSTS_NOT_INITIALIZED;
    }

    if (R_EEL_LCSTS_NOT_INITIALIZED == g_eel_str.r_eel_lcSts_enu)
    {
        ret = R_EEL_FALSE;
    }
    else
    {
        ret = R_EEL_TRUE;
    }

    return (ret);
} /* R_EEL_UFct_ChkLibraryInitialized */

/*********************************************************************************************************************
 * Function name:  R_EEL_UFct_Write
 *********************************************************************************************************************/
/**
 *  Function check DS write start conditions and start the user DS write processes.
 *
 *  @param[in]  pId             - ID of the write process to start
 *  @param[in]  request         - request structure of the DS write process
 *  @param[in]  invalidate      - flag indicating if the DS shall be written or invalidated
 *
 *  @return     status of the DS write request
 *              - R_EEL_BUSY
 *              - R_EEL_ERR_REJECTED
 *              - R_EEL_ERR_ACCESS_LOCKED
 *              - R_EEL_ERR_PARAMETER
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_status_t R_EEL_UFct_Write (r_eel_process_id_t pId,
                                              r_eel_request_t * request,
                                              r_eel_flag_t invalidate)
{
    r_eel_status_t          reqErr;
    r_eel_write_proc_data_t wpId;
    uint16_t                tIdx,
                            id,
                            len;
    uint32_t srcAdd;

    reqErr = R_EEL_BUSY;

    /* Return locked error if the write operations are locked */
    if ( (R_EEL_ACCESS_LOCKED    == g_eel_str.ds_str.accessStatus_enu) ||
         (R_EEL_ACCESS_READ_ONLY == g_eel_str.ds_str.accessStatus_enu) )
    {
        reqErr = R_EEL_ERR_ACCESS_LOCKED;
    }
    else
    {
        /* Reject the command if the the write process is already active */
        if ( R_EEL_FALSE != R_EEL_PFct_Chk_ProcessActive (pId) )
        {
            reqErr = R_EEL_ERR_REJECTED;
        }
    }

    if (R_EEL_BUSY == reqErr)
    {
        /* Return parameter error on wrong passed parameters: unknown ID or NULL buffer passed for a write command*/
        id = request->identifier_u16;
        tIdx = R_EEL_PFct_ConvertId2TIdx (id);
        if ( (tIdx == R_EEL_ID_NOT_FOUND)
             || ( (R_EEL_NULL == request->address_pu08) && (R_EEL_FALSE == invalidate) ) )
        {
            reqErr = R_EEL_ERR_PARAMETER;
        }
        else
        {
            /* Get the DS size (set to 0 in case of an invalidation command */
            if (R_EEL_FALSE == invalidate)
            {
                len   = R_EEL_PFct_ConvertTIdx2Len (tIdx);
                srcAdd = R_EEL_PFct_CastU08Ptr2Add (request->address_pu08);
            }
            else
            {
                len = 0u;
                srcAdd = 0uL;
            }

            /* Initialize the DS write process */
            wpId = R_EEL_SFct_ConvertProcID2WriteProcID (pId);
            R_EEL_SFct_Write_InitProcess (wpId,             /* Write Process to start */
                                          request,          /* request structure */
                                          id,               /* DS ID */
                                          len,              /* Data set size */
                                          srcAdd,           /* Write source address */
                                          invalidate,       /* Invalidate? */
                                          tIdx);            /* table index */
        }
    }

    return (reqErr);
} /* R_EEL_UFct_Write */

/*********************************************************************************************************************
 * Function name:  R_EEL_UFct_Read
 *********************************************************************************************************************/
/**
 *  Function check DS read start conditions and start the user DS read processes.
 *
 *  @param[in]  request         - request structure of the DS read process
 *
 *  @return     status of the DS read request
 *              - R_EEL_BUSY
 *              - R_EEL_ERR_REJECTED
 *              - R_EEL_ERR_ACCESS_LOCKED
 *              - R_EEL_ERR_PARAMETER
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_status_t R_EEL_UFct_Read (r_eel_request_t * request)
{
    r_eel_status_t reqErr;
    uint16_t       tIdx,
                   len,
                   lenReq;

    reqErr = R_EEL_BUSY;

    tIdx = 0;       /* default value set for QAC check. Basically not required */

    /* Return locked error if the library is locked */
    if (R_EEL_ACCESS_LOCKED == g_eel_str.ds_str.accessStatus_enu)
    {
        reqErr = R_EEL_ERR_ACCESS_LOCKED;
    }
    else
    {
        /* Return rejected error if the read process is already started */
        if ( R_EEL_FALSE != R_EEL_PFct_Chk_ProcessActive (R_EEL_PR_RE) )
        {
            reqErr = R_EEL_ERR_REJECTED;
        }
    }

    /* In case of no error, we continue with the command processing */
    if (R_EEL_BUSY == reqErr)
    {
        /* Return parameter error on wrong passed parameters: unknown ID or NULL buffer */
        tIdx = R_EEL_PFct_ConvertId2TIdx (request->identifier_u16);
        if ( (tIdx == R_EEL_ID_NOT_FOUND)
             || (R_EEL_NULL == request->address_pu08) )
        {
            /* Parameter error */
            reqErr = R_EEL_ERR_PARAMETER;
        }
    }

    /* In case of no error, we continue with the command processing */
    if (R_EEL_BUSY == reqErr)
    {
        #ifdef R_EEL_SUPPORT_EXT_FEATURES
            if (R_EEL_CMD_READ_WC == request->command_enu) /* R_EEL_READ_WC */
            {
                r_eel_ext_features_t extFeatures;

                extFeatures = g_eel_str.RTCfg_pstr->IDLTab_pstr[tIdx].ext_features_enu;

                if ( (R_EEL_EXTF_WC != extFeatures) &&
                     (R_EEL_EXTF_WC_FINV != extFeatures) )
                {
                    reqErr = R_EEL_ERR_PARAMETER;
                }
            }
            else
        #endif
        {
            /* return an parameter error if the read length + offset does not fit to
               the DS size from the IDL table */
            len = R_EEL_PFct_ConvertTIdx2Len (tIdx);
            lenReq =  (request->offset_u16);
            lenReq += (request->length_u16);
            if ( (len < lenReq) || (0u == request->length_u16) )
            {
                reqErr = R_EEL_ERR_PARAMETER;
            }
        }
    }
    if (R_EEL_BUSY == reqErr)
    {
        /* Prepare the variables required for the read process */
        g_eel_str.op_str[R_EEL_OP_RE].req_pstr = request;
        g_eel_str.opRe_str.idx_u16 = tIdx;
    }

    return (reqErr);
} /* R_EEL_UFct_Read */


/*********************************************************************************************************************
 * Function name:  R_EEL_Execute
 *********************************************************************************************************************/
/**
 *  This function initiates an EEPROM emulation operation (Write/Read/...).
 *  After initiation, the function R_EEL_Handler need to be called regularly to finish the operation.
 *
 *  @param[in]   request_pstr   Pointer to the operation request structure.
 *                              Structure input elements:
 *                              command_enu, identifier_u16, address_u32, offset_u16, length_enu
 *  @param[out]  request_pstr   Pointer to the operation request structure.
 *                              Structure output element:
 *                              status_enu
 *  @return      ---
 */
/*********************************************************************************************************************/
void  R_EEL_Execute (r_eel_request_t * request_pstr)                            /*PRQA S 1503 */
{
    r_eel_status_t     reqErr,
                       prStat;
    r_eel_process_id_t pID;
    r_eel_pfct         sPfct;
    #ifdef R_EEL_FLINT_SET_SW
        r_eel_flag_t   reqInt;

        reqInt = R_EEL_FALSE;
    #endif

    /* Initialize default process to activate. This is the read process as it does not
       influence the Data Flash contents. */
    pID   = R_EEL_PR_RE;
    sPfct = R_EEL_SM_READ_START;

    prStat = R_EEL_OK;

    /* Return locked error if the library is not initialized */
    if ( R_EEL_TRUE == R_EEL_UFct_ChkLibraryInitialized () )
    {
        reqErr = R_EEL_BUSY;

        /* Check the command */
        switch (request_pstr->command_enu)
        {
            /* DS Read command */
            case R_EEL_CMD_READ:
            #ifdef R_EEL_SUPPORT_EXT_FEATURES
                    case R_EEL_CMD_READ_WC:
            #endif
                {
                    reqErr = R_EEL_UFct_Read (request_pstr);

                    /* Default process, already set
                    pID   = R_EEL_PR_RE;
                    sPfct = R_EEL_SM_READ_START;
                    */
                }
                break;

            /* DS Write command */
            case R_EEL_CMD_WRITE:
            {
                /* Unique function to handle all different write commands */
                reqErr = R_EEL_UFct_Write (R_EEL_PR_WT, request_pstr, R_EEL_FALSE);
                if (R_EEL_BUSY == reqErr)
                {
                    pID   = R_EEL_PR_WT;
                    sPfct = R_EEL_SM_WRITE_START;
                }
                break;
            }

            /* DS Write incremental command */
            case R_EEL_CMD_WRITE_INC:
            {
                /* Unique function to handle all different write commands */
                reqErr = R_EEL_UFct_Write (R_EEL_PR_WT, request_pstr, R_EEL_FALSE);
                if (R_EEL_BUSY == reqErr)
                {
                    pID   = R_EEL_PR_WT;
                    sPfct = R_EEL_SM_WRITE_INC_START;
                }
                break;
            }

            /* DS Write immediate command */
            case R_EEL_CMD_WRITE_IMM:
            {
                /* Unique function to handle all different write commands */
                reqErr = R_EEL_UFct_Write (R_EEL_PR_WI, request_pstr, R_EEL_FALSE);
                if (R_EEL_BUSY == reqErr)
                {
                    pID   = R_EEL_PR_WI;
                    sPfct = R_EEL_SM_WRITE_START;
                }
                break;
            }

            /* DS Write immediate command */
            case R_EEL_CMD_WRITE_INC_IMM:
            {
                /* Unique function to handle all different write commands */
                reqErr = R_EEL_UFct_Write (R_EEL_PR_WI, request_pstr, R_EEL_FALSE);
                if (R_EEL_BUSY == reqErr)
                {
                    pID   = R_EEL_PR_WI;
                    sPfct = R_EEL_SM_WRITE_INC_START;
                }
                break;
            }

            /* Invalidate command */
            case R_EEL_CMD_INVALIDATE:
            {
                /* Unique function to handle all different write commands */
                reqErr = R_EEL_UFct_Write (R_EEL_PR_WT, request_pstr, R_EEL_TRUE);
                if (R_EEL_BUSY == reqErr)
                {
                    pID   = R_EEL_PR_WT;
                    sPfct = R_EEL_SM_WRITE_START;
                }
                break;
            }

            /* Invalidate immediate command */
            case R_EEL_CMD_INVALIDATE_IMM:
            {
                /* Unique function to handle all different write commands */
                reqErr = R_EEL_UFct_Write (R_EEL_PR_WI, request_pstr, R_EEL_TRUE);
                if (R_EEL_BUSY == reqErr)
                {
                    pID   = R_EEL_PR_WI;
                    sPfct = R_EEL_SM_WRITE_START;
                }
                break;
            }

            /* Clean-up command */
            case R_EEL_CMD_CLEANUP:
            {
                uint16_t blk;

                /* For clean-up operation, the system must
                   - be idle
                   - the RAM table must have at least one entry. Otherwise no new block would
                     be activated resulting in no active block */
                if ( (R_EEL_OPERATION_IDLE == g_eel_str.ds_str.operationStatus_enu) &&
                     (g_eel_str.opSv_str.ramTableFillCntIDFound_u16 > 0u) )
                {
                    /* on clean-up, all blocks of the active pool must be refreshed, including the
                       active pool head block. So, we forward the refresh destination pointer to
                       one block after the head block.
                       R_EEL_SFct_Calc_NextBlk_ActPrep can rely on at least 2 active/prepared blocks as
                       the BG operation is idle and so, we must have prepared blocks */
                    blk = g_eel_str.blkActive_u16;
                    R_EEL_SFct_Calc_NextBlk_ActPrep (&blk);
                    g_eel_str.blkRef_u16 = blk;
                }
                else
                {
                    reqErr = R_EEL_ERR_ACCESS_LOCKED;
                }
                break;
            }

            /* Format command */
            case R_EEL_CMD_FORMAT:
            {
                /* Condition for Format execution:
                   - Startup must have passed. So, erase counter can be used if valid
                   - The system must be idle (No other operation ongoing, Format on a working
                     system) or passive (No other operation ongoing, Format on a defect system) */
                if ( (R_EEL_LCSTS_ACTIVE == g_eel_str.r_eel_lcSts_enu) &&
                     (R_EEL_SM_SUPV_RUN == g_eel_str.sm_str[R_EEL_PR_SV].nextState_pfct) &&
                     ( (R_EEL_OPERATION_IDLE == g_eel_str.ds_str.operationStatus_enu) ||
                       (R_EEL_OPERATION_PASSIVE == g_eel_str.ds_str.operationStatus_enu) ) )
                {
                    /* Initiate format process */
                    g_eel_str.op_str[R_EEL_OP_FO].req_pstr = request_pstr;
                    pID   = R_EEL_PR_FO;
                    sPfct = R_EEL_SM_FORMAT_START;
                }
                else
                {
                    reqErr = R_EEL_ERR_ACCESS_LOCKED;
                }
                break;
            }

            default:
            {
                reqErr = R_EEL_ERR_COMMAND;
                break;
            }
        } /* switch */

    } /* if( R_EEL_TRUE == R_EEL_UFct_ChkLibraryInitialized() ) */
    else
    {
        reqErr = R_EEL_ERR_ACCESS_LOCKED;
    }

    /* Erase suspend management
       If a Flash Erase is ongoing, it shall be suspended in order to execute the initiated operation */
    if (R_EEL_BUSY == reqErr)
    {
        /* Check if an erase is ongoing (either Erase busy or suspended with resume request) */
        if (R_FDL_BUSY == g_eel_str.fdlReqErase_str.status_enu)
        {
            g_eel_str.sm_str[R_EEL_PR_PR].nextState_pfct = R_EEL_SM_PREP_ERASE_RESUME;

            /* Request the suspend action */
            reqErr = R_EEL_FDLIF_EraseSuspendRequest ();

            /* Erase suspend counter update and warning check */
            if (g_eel_str.opPr_str.eraseSuspCnt_u16 < 0xFFFF)
            {
                (g_eel_str.opPr_str.eraseSuspCnt_u16)++;
            }

            if (g_eel_str.opPr_str.eraseSuspCnt_u16 >= g_eel_str.RTCfg_pstr->eraseSuspendThreshold_u16)
            {
                /* Set the operations warning. The operation will continue */
                prStat = R_EEL_ERR_ERASESUSPEND_OVERFLOW;
            }
        }
    }

    /* On no error start the requested operation */
    if (R_EEL_BUSY == reqErr)
    {
        /* Special case clean-up does not start a process, this is done by SUPV */
        if (R_EEL_CMD_CLEANUP == request_pstr->command_enu)
        {
            /* The operation request returns OK immediately as all work
               is done by the background processes */
            reqErr = R_EEL_OK;
        }
        else
        {
            R_EEL_SFct_ActivateProcess (pID, sPfct);

            /* Update the process status for the case of process warnings; the process state would not change,
               even in error case */
            (void)R_EEL_SFct_ProcessErrorUpdate (pID, prStat, g_eel_str.sm_str[pID].nextState_pfct);
        }

        /* Set driver status to busy, but only when we are idle. In case
           of Startup or Read Only we must keep the original state */
        if (R_EEL_OPERATION_IDLE == g_eel_str.ds_str.operationStatus_enu)
        {
            R_EEL_SFct_SetDriverStatus (R_EEL_ACCESS_UNDEFINED, R_EEL_OPERATION_BUSY);
        }

        #ifdef R_EEL_FLINT_SET_SW
            reqInt = R_EEL_TRUE;
        #endif
    }

    /* Set the return state */
    request_pstr->status_enu = reqErr;

    /* Must be at functions end as Handler execution is triggered here! */
    #ifdef R_EEL_FLINT_SET_SW
        /* On activated interrupt support, set interrupt for the 1st handler call */
        if (R_EEL_TRUE == reqInt)
        {
            R_EEL_FLINT_SET_SW;
        }
    #endif

    return;
} /* R_EEL_Execute */


/*********************************************************************************************************************
 * Function name:  R_EEL_Handler
 *********************************************************************************************************************/
/**
 *  User interface function:
 *  This function forwards an initiated EEL operation until it is finished. At operation end the
 *  result is set in the request structure.
 *  After initiation by R_EEL_Execute, the function R_EEL_Handler need to be called regularly to finish
 *  the operation.
 *
 *  @param[in]      ---
 *  @return         ---
 *
 *  The function returns the operation result in the request structure status variable, passed to
 *  the library when calling R_EEL_Execute (e.g. request.status).
 */
/*********************************************************************************************************************/
void  R_EEL_Handler (void)                                                       /*PRQA S 1503 */
{
    r_eel_process_id_t cpId,
                       apId;

    /* For any EEL operation, we must be
        - active
        - operational status is not suspended
        - operational status passive is allowed as read and suspend must pass */
    if ( (R_EEL_LCSTS_ACTIVE == g_eel_str.r_eel_lcSts_enu) &&
         (R_EEL_OPERATION_SUSPENDED != g_eel_str.ds_str.operationStatus_enu) )
    {
        cpId = g_eel_str.curPId_enu;

        /* check if a Flash operation is pending. If yes, we call the FDL handler to update the
           Flash status. A Suspended Erase must also be handled to handle resume requests */
        if ( (R_FDL_BUSY == g_eel_str.sm_str[cpId].flashStatus_enu) ||        /* PRQA S 3689 */
             (R_FDL_SUSPENDED == g_eel_str.sm_str[cpId].flashStatus_enu) )    /* PRQA S 3689 */
        {
            g_eel_str.sm_str[cpId].flashStatus_enu = R_EEL_FDLIF_Handler ();    /* PRQA S 3689 */
        }

        /* If no flash operation is ongoing, we continue handling the EEL processes */
        if (R_FDL_BUSY != g_eel_str.sm_str[cpId].flashStatus_enu)             /* PRQA S 3689 */
        {
            /* On suspend request we lock the system when no Flash operation is ongoing */
            if (R_EEL_FALSE != g_eel_str.suspend_str.suspendReq_enu)
            {
                R_EEL_SFct_SetDriverStatus (R_EEL_ACCESS_LOCKED, R_EEL_OPERATION_SUSPENDED);
            }
            /* If the processes are not suspended ... */
            else
            {
                /* Handle the state machine of the EEL */
                R_EEL_SMachine_Main ();

                apId = R_EEL_SMachine_GetActiveProcess ();

                /* On shut down request we lock the system when no more process is active */
                if (R_EEL_TRUE == g_eel_str.shutDownReq_enu)
                {
                    /* If we have no more active process, we can shut down */
                    if (R_EEL_PR_END == apId)
                    {
                        R_EEL_SFct_SetDriverStatus (R_EEL_ACCESS_LOCKED, R_EEL_OPERATION_PASSIVE);

                        /* EEL life cycle forwarded to shut down */
                        g_eel_str.r_eel_lcSts_enu = R_EEL_LCSTS_SHUTDOWN;
                    }
                }

                #ifdef R_EEL_FLINT_SET_SW
                    /* Condition for FLInt request setting by SW:
                       - No Flash operation ongoing (sets flag at end of Flash operation anyhow)
                       - System is busy:
                         - We have an active process
                         - The active process is not Supervision or operation status != idle
                           (Idle supervision ought to be triggered separately)
                    */

                    if ( R_FDL_TRUE == R_FDL_FCUFct_ChkReady () )
                    {
                        if ( (R_EEL_PR_END != apId) &&
                             ( !( (R_EEL_PR_SV == apId) &&
                                  (R_EEL_OPERATION_IDLE == g_eel_str.ds_str.operationStatus_enu) ) ) )
                        {
                            R_EEL_FLINT_SET_SW;
                        }
                    }
                #endif

#ifdef R_EEL_DEBUG_BASICINFO
                    g_eel_str.SMCalls_u16++;
#endif
            }
        }
    }

    return;
} /* R_EEL_Handler */


/*********************************************************************************************************************
 * Function name:  R_EEL_Init
 *********************************************************************************************************************/
/**
 *  User interface function:
 *  This function initializes the EEL internal variables. It must be called before execution of any
 *  other EEL function.
 *  Furthermore, configuration checks are done:
 *  - Threshold must be >=2 blocks and at least 2 blocks must remain between threshold and EEL
 *    pool size
 *  - Max DS size must be < R_EEL_PFct_Calc_BlkSpace - REF entry size
 *  On check fail, the startup processing is locked and user operations will never be unlocked.
 *
 *  @param[in]  descriptor_pstr Pointer to the EEL descriptor structure
 *  @param[in]  opMode_enu      R_EEL_OPERATION_MODE_NORMAL:
 *                              Normal operation of the EEL
 *                              R_EEL_OPERATION_MODE_LIMITED:
 *                              Limited operation of the EEL with special refresh as the ID-L table
 *                              passed to R_EEL_Init is not complete but just reflects a limited
 *                              number of IDs, used for this application (Boot loader).
 *  @return     Initialization status when returned from function call:
 *              - R_EEL_OK
 *              - R_EEL_ERR_CONFIGURATION
 *              - R_EEL_ERR_ACCESS_LOCKED
 */
/*********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule --- (QAC message 1482)
 * Reason:       cast non constant to an enum type
 * Verification: non constant range is limited to enumeration range and the enumeration is sequential
 *********************************************************************************************************************/
r_eel_status_t R_EEL_Init (const r_eel_descriptor_t * descriptor_pstr,                 /*PRQA S 1503 2 */
                           r_eel_operation_mode_t opMode_enu)
{
    uint32_t i,
             edAdd;
    uint16_t maxSize,
             len,
             threshhold,
             id;
    r_eel_status_t ret;

    ret = R_EEL_ERR_ACCESS_LOCKED;

    /* The EEL may only be initialized when no Flash operation is ongoing or suspended. Only so,
       the EEL can be synchronized with the Flash operations (FDL) */
    if ( (R_FDL_REQUEST_POINTER_UNDEFINED == g_fdl_str.reqInt_pstr) &&
         (R_FDL_REQUEST_POINTER_UNDEFINED == g_fdl_str.reqSuspend_pstr) )
    {
        ret = R_EEL_OK;

        /* -------------------------------------------------------------------------------------
           basic initialization
           ------------------------------------------------------------------------------------- */
        /* Initially clear the complete g_eel_str structure */
        edAdd = (uint32_t)(&g_eel_str);                                     /* PRQA S 0306 */
        for (i = 0; i < sizeof (g_eel_str); i++)
        {
            R_EEL_PFct_WriteDataToAddU08 (0u, edAdd);
            edAdd++;
        }

        g_eel_str.r_eel_lcSts_enu = R_EEL_LCSTS_NOT_INITIALIZED;

        /* Reset process variables used in later R_EEL_Init flow */
        for (i = 0; i < R_EEL_PR_END; i++)
        {
            g_eel_str.sm_str[i].active_enu        = R_EEL_FALSE;
            g_eel_str.sm_str[i].flashStatus_enu   = R_FDL_OK;
            g_eel_str.sm_str[i].nextState_pfct     = R_EEL_SM_IDLE;
            R_EEL_SFct_ProcessErrorReset ( (r_eel_process_id_t)i );         /* PRQA S 1482 */
        }

        /* Reset sub-process error pointers */
        g_eel_str.opSA_str.subProcessErrReturn_pfct = R_EEL_SM_IDLE;
        g_eel_str.opSI_str.subProcessErrReturn_pfct = R_EEL_SM_IDLE;

        /* Init the EEL driver status and background error */
        R_EEL_SFct_ProcessErrorReset (R_EEL_PR_SV);
        R_EEL_SFct_SetDriverStatus (R_EEL_ACCESS_LOCKED, R_EEL_OPERATION_PASSIVE);

        /* Set pointer to EEL static configuration */
        g_eel_str.RTCfg_pstr = descriptor_pstr;


        /* set virtual EEL pool start/size. As these are required for configuration check, this is
           done first. */

        g_eel_str.vPoolVblkSize_u16 = (uint16_t)(descriptor_pstr->vBlkSize_u16 * R_BLOCK_SIZE);
        g_eel_str.vPoolSizeNoVblks_u16 =
            (uint16_t)(g_fdl_str.RTCfg_pstr->eelPoolSize_u16 / descriptor_pstr->vBlkSize_u16);

        /* -------------------------------------------------------------------------------------
           configuration check
           ------------------------------------------------------------------------------------- */
        if (R_EEL_NULL == descriptor_pstr->IDLTabIdxCnt_u16)
        {
            ret = R_EEL_ERR_CONFIGURATION;
        }
        else
        {
            /* Check the correct vPool granularity */
            if ( (g_eel_str.vPoolSizeNoVblks_u16 * descriptor_pstr->vBlkSize_u16) !=
                 g_fdl_str.RTCfg_pstr->eelPoolSize_u16 )
            {
                ret = R_EEL_ERR_CONFIGURATION;
            }

            /* Calculate max. DS size for later check and check ID */
            maxSize = 0u;
            for (i = 0uL; i < descriptor_pstr->IDLTabIdxCnt_u16; i++)
            {
                len = R_EEL_PFct_ConvertTIdx2Len ( (uint16_t)i );
                if (maxSize < len)
                {
                    maxSize = len;
                }

                id = R_EEL_PFct_ConvertTIdx2Id ( (uint16_t)i );
                if ( (0u == len) || ( (id < 1u) || (id > 0xfffeu) ) )
                {
                    ret = R_EEL_ERR_CONFIGURATION;
                }
            }

            /* Check max DS size */
            if ( maxSize > (R_EEL_PFct_Calc_BlkSpace () - R_EEL_REF_OFF_DS) )
            {
                ret = R_EEL_ERR_CONFIGURATION;
            }

            /* Check threshold */
            threshhold = descriptor_pstr->vBlkRefreshThreshold_u16;
            if ( (2u > threshhold) ||
                 ( ( (g_eel_str.vPoolSizeNoVblks_u16) - 2u ) < threshhold ) )
            {
                ret = R_EEL_ERR_CONFIGURATION;
            }


            /* Check erase suspend threshold */
            if (0u == g_eel_str.RTCfg_pstr->eraseSuspendThreshold_u16)
            {
                ret = R_EEL_ERR_CONFIGURATION;
            }
        }

        /* -------------------------------------------------------------------------------------
           Initialize variables after configuration check
           ------------------------------------------------------------------------------------- */
        if (R_EEL_OK == ret)
        {
            g_eel_str.curPId_enu = R_EEL_PR_RE;

            /* Set operation mode. In limited operation, we have limited ID-L table and so cannot
               Refresh*/
            g_eel_str.opMode_enu = opMode_enu;

            /* Reset Prepare - Erase flags and counters */
            g_eel_str.opPr_str.eraseSuspCnt_u16   = 0u;

            /* Reset supervision related variables */
            g_eel_str.opSv_str.ramTableInit_enu    = R_EEL_FALSE;
            g_eel_str.opSv_str.ramTableFillblk_u16 = 0;

            /* Initialize misc internal variables */
            g_eel_str.rp_u32                     = R_EEL_NULL;
            g_eel_str.processLock_enu            = R_EEL_PR_UNLOCK;
            g_eel_str.suspend_str.suspendReq_enu = R_EEL_FALSE;
            g_eel_str.shutDownReq_enu            = R_EEL_FALSE;
            g_eel_str.fdlReqWrite_str.status_enu = R_FDL_OK;
            g_eel_str.fdlReqErase_str.status_enu = R_FDL_OK;

            /* Reset RAM table entries */
            for (i = 0uL; i < descriptor_pstr->IDLTabIdxCnt_u16; i++)
            {
                g_eel_str.RTCfg_pstr->IDXTab_pau16[i] = 0u;                       /* PRQA S 0491 */
            }

            /* EEL is initialized now */
            g_eel_str.r_eel_lcSts_enu = R_EEL_LCSTS_INITIALIZED;
        }
        else
        {
            (void)R_EEL_SFct_ProcessErrorUpdate (R_EEL_PR_SV, ret, R_EEL_SM_SUPV_RUN);
        }
    }

    return (ret);
} /* R_EEL_Init */

/*********************************************************************************************************************
 * Function name:  R_EEL_Startup
 *********************************************************************************************************************/
/**
 *  User interface function:
 *  This function activates the startup processing and locks the EEL access. Cyclic call of
 *  R_EEL_Handler takes care for startup processing and entering normal operation.
 *
 *  If R_EEL_Init returns with a configuration error, the startup processing is not initiated and the
 *  EEPROM emulation will remain locked.
 *
 *  @param      ---
 *
 *  @return     Function execution error result
 *              - R_EEL_OK
 *              - R_EEL_ERR_ACCESS_LOCKED (R_EEL_Startup may only be called when the EEL life cycle
 *                                         status is initialized )
 */
/*********************************************************************************************************************/
r_eel_status_t R_EEL_Startup (void)                                                /*PRQA S 1503 */
{
    r_eel_status_t ret;

    ret = R_EEL_ERR_ACCESS_LOCKED;

    /* R_EEL_Init must have been called before */
    if (R_EEL_LCSTS_INITIALIZED == g_eel_str.r_eel_lcSts_enu)
    {
        /* EEL life cycle forwarded to active */
        g_eel_str.r_eel_lcSts_enu = R_EEL_LCSTS_ACTIVE;

        /* Activate supervision operation to execute the start-up processing */
        R_EEL_SFct_ActivateProcess (R_EEL_PR_SV, R_EEL_SM_SUPV_START);

        /* Set the driver status accordingly */
        R_EEL_SFct_SetDriverStatus (R_EEL_ACCESS_LOCKED, R_EEL_OPERATION_STARTUP);

        ret = R_EEL_OK;

        /* Must be at functions end as Handler execution is triggered here! */
        #ifdef R_EEL_FLINT_SET_SW
            /* On activated interrupt support, set interrupt for the 1st handler call */
            R_EEL_FLINT_SET_SW;
        #endif
    }

    return (ret);
} /* R_EEL_Startup */


/*********************************************************************************************************************
 * Function name:  R_EEL_ShutDown
 *********************************************************************************************************************/
/**
 *  User interface function:
 *  This function immediately locks the EEL operations and requests shut down to the supervision
 *  process. Cyclic call of R_EEL_Handler takes care for entering the passive end state of shut down.
 *
 *  @param      ---
 *
 *  @return     Function execution error result
 *              - R_EEL_OK
 *              - R_EEL_ERR_ACCESS_LOCKED (R_EEL_ShutDown may only be called when the EEL life cycle
 *                                         status is active and we are not suspended )
 */
/*********************************************************************************************************************/
r_eel_status_t R_EEL_ShutDown (void)                                               /*PRQA S 1503 */
{
    r_eel_status_t ret;

    ret = R_EEL_ERR_ACCESS_LOCKED;

    /* R_EEL_ShutDown may only be called when the EEL life cycle status is active and we are not
       suspended */
    (void)R_EEL_UFct_ChkLibraryInitialized (); /* Ensure defined life-cycle status */
    if ( (R_EEL_LCSTS_ACTIVE == g_eel_str.r_eel_lcSts_enu) &&
         (R_EEL_OPERATION_SUSPENDED != g_eel_str.ds_str.operationStatus_enu) &&
         (R_EEL_FALSE == g_eel_str.suspend_str.suspendReq_enu) )
    {
        /* Lock Read/Write accesses. operation status remains unchanged. This will be updated on
           shut down completed */
        R_EEL_SFct_SetDriverStatus (R_EEL_ACCESS_LOCKED, R_EEL_OPERATION_UNDEFINED);

        /* If the system is already passive, we can also set the life cycle to shut down here. If
           not (normal case) we set the life cycle shut down in the handler, when the operation
           status is set to shut down */
        if (R_EEL_OPERATION_PASSIVE == g_eel_str.ds_str.operationStatus_enu)
        {
            g_eel_str.r_eel_lcSts_enu = R_EEL_LCSTS_SHUTDOWN;
        }

        /* Deactivate supervision process. Other processes are finished */
        g_eel_str.sm_str[R_EEL_PR_SV].active_enu = R_EEL_FALSE;

        /* Set the shut down request flag */
        g_eel_str.shutDownReq_enu = R_EEL_TRUE;

        ret = R_EEL_OK;

        /* Must be at functions end as Handler execution is triggered here! */
        #ifdef R_EEL_FLINT_SET_SW
            /* On activated interrupt support, set interrupt for the 1st handler call */
            R_EEL_FLINT_SET_SW;
        #endif
    }

    return (ret);
} /* R_EEL_ShutDown */


/*********************************************************************************************************************
 * Function name:  R_EEL_SuspendRequest
 *********************************************************************************************************************/
/**
 *  User interface function:
 *  This function immediately locks the EEL operations and requests suspend to the supervision
 *  process. Cyclic call of R_EEL_Handler takes care for entering the passive end state of suspend.
 *
 *  @param      ---
 *
 *  @return     Function execution error result
 *              - R_EEL_OK
 *              - R_EEL_ERR_ACCESS_LOCKED (R_EEL_SuspendRequest may always be called when the EEL is
 *                                         active and suspend processing is not already active )
 */
/*********************************************************************************************************************/
r_eel_status_t R_EEL_SuspendRequest (void)                                                /*PRQA S 1503 */
{
    r_eel_status_t ret;

    ret = R_EEL_ERR_ACCESS_LOCKED;

    /* R_EEL_SuspendRequest may always be called when the EEL is active and suspend processing is not
       already active */
    (void)R_EEL_UFct_ChkLibraryInitialized (); /* Ensure defined life-cycle status */
    if ( (R_EEL_LCSTS_ACTIVE == g_eel_str.r_eel_lcSts_enu) &&
         (R_EEL_FALSE == g_eel_str.suspend_str.suspendReq_enu) &&
         (R_EEL_FALSE == g_eel_str.shutDownReq_enu) )
    {
        /* Set the process suspend flag */
        g_eel_str.suspend_str.suspendReq_enu = R_EEL_TRUE;

        /* Save the current EEL status.
           The return value is not checked as it is tested already in the above if clause */
        (void)R_EEL_GetDriverStatus ( &(g_eel_str.suspend_str.statusSave_str) );

        /* Lock user accesses. The operation status is set to suspended by the handler on suspend
           completion. */
        R_EEL_SFct_SetDriverStatus (R_EEL_ACCESS_LOCKED, R_EEL_OPERATION_UNDEFINED);

        ret = R_EEL_OK;

        /* Must be at functions end as Handler execution is triggered here! */
        #ifdef R_EEL_FLINT_SET_SW
            /* On activated interrupt support, set interrupt for the 1st handler call */
            R_EEL_FLINT_SET_SW;
        #endif
    }

    return (ret);
} /* R_EEL_SuspendRequest */


/*********************************************************************************************************************
 * Function name:  R_EEL_ResumeRequest
 *********************************************************************************************************************/
/**
 *  User interface function:
 *  This function resumes normal EEL operation immediately.
 *
 *  @param      ---
 *
 *  @return     Function execution error result
 *              - R_EEL_OK
 *              - R_EEL_ERR_ACCESS_LOCKED (R_EEL_ResumeRequest may only be called when the EEL is initialized
 *                                         and suspend processing is already active)
 */
/*********************************************************************************************************************/
r_eel_status_t R_EEL_ResumeRequest (void)                                                 /*PRQA S 1503 */
{
    r_eel_status_t ret;

    ret = R_EEL_ERR_ACCESS_LOCKED;

    /* R_EEL_ResumeRequest may only be called when the EEL is initialized and suspend processing is already
       active */
    if ( ( R_EEL_TRUE == R_EEL_UFct_ChkLibraryInitialized () ) &&
         (R_EEL_TRUE == g_eel_str.suspend_str.suspendReq_enu) )
    {
        /* Set the process suspend flag */
        g_eel_str.suspend_str.suspendReq_enu = R_EEL_FALSE;

        /* Restore driver status */
        R_EEL_SFct_SetDriverStatus (g_eel_str.suspend_str.statusSave_str.accessStatus_enu,
                                    g_eel_str.suspend_str.statusSave_str.operationStatus_enu);

        ret = R_EEL_OK;

        /* Must be at functions end as Handler execution is triggered here! */
        #ifdef R_EEL_FLINT_SET_SW
            /* On activated interrupt support, set interrupt for the 1st handler call */
            R_EEL_FLINT_SET_SW;
        #endif
    }

    return (ret);
} /* R_EEL_ResumeRequest */



/*********************************************************************************************************************
 * Function name:  R_EEL_GetDriverStatus
 *********************************************************************************************************************/
/**
 *  User interface function:
 *  This function returns the driver status of the EEL.
 *
 *  @param[out] driverStatus_pstr:
 *              - driverStatus_pstr.operationStatus_enu   - EEL (background) operational status
 *              - driverStatus_pstr.accessStatus_enu      - EEL operations access status
 *              - driverStatus_pstr.backgroundStatus_enu  - EEL background operations error status
 *
 *  @return     Function execution error result
 *              - R_EEL_OK
 *              - R_EEL_ERR_ACCESS_LOCKED
 */
/*********************************************************************************************************************/
r_eel_status_t R_EEL_GetDriverStatus (r_eel_driver_status_t * driverStatus_pstr)      /*PRQA S 1505 */
{
    r_eel_err_flg_t errFlg;
    r_eel_status_t  ret;

    ret = R_EEL_ERR_ACCESS_LOCKED;

    /* The function may be executed when the EEL is initialized */
    if ( R_EEL_TRUE == R_EEL_UFct_ChkLibraryInitialized () )
    {
        driverStatus_pstr->operationStatus_enu   = g_eel_str.ds_str.operationStatus_enu;
        driverStatus_pstr->accessStatus_enu      = g_eel_str.ds_str.accessStatus_enu;
        driverStatus_pstr->backgroundStatus_enu  = g_eel_str.ds_str.backgroundStatus_enu;

        ret = R_EEL_OK;

        /* If we have OK or a warning in the supervision process, we reset the status to OK.
           An error is not resetted as in that case the emulation is locked */
        errFlg = R_EEL_SFct_ErrStatCheckError (R_EEL_PR_SV);
        if (R_EEL_FLG_OK == errFlg)
        {
            R_EEL_SFct_ProcessErrorReset (R_EEL_PR_SV);
        }
    }

    return (ret);
} /* R_EEL_GetDriverStatus */


/*********************************************************************************************************************
 * Function name:  R_EEL_GetSpace
 *********************************************************************************************************************/
/**
 *  User interface function:
 *  This function returns the free space in the ring buffer reflected by the space in the current
 *  active block + space in the prepared blocks - one block required for Refresh
 *
 *  @param      space_pu32      pointer to the free space variable to set
 *
 *  @return     Function execution error result
 *              - R_EEL_OK
 *              - R_EEL_ERR_ACCESS_LOCKED
 */
/*********************************************************************************************************************/
r_eel_status_t R_EEL_GetSpace (uint32_t * space_pu32)                                /*PRQA S 1503 */
{
    uint32_t       space, blkFreeSpace;
    r_eel_status_t ret;

    ret = R_EEL_ERR_ACCESS_LOCKED;

    /* The function may be executed when the EEL is initialized and not locked */
    if ( ( R_EEL_TRUE == R_EEL_UFct_ChkLibraryInitialized () ) &&
         (R_EEL_ACCESS_LOCKED != g_eel_str.ds_str.accessStatus_enu) )
    {
        space = R_EEL_SFct_Calc_FreeSpace ();

        /* Reduce free space by the minimum space required for pool full condition Refresh (1 block free space) */
        blkFreeSpace = R_EEL_PFct_Calc_BlkSpace ();
        if (blkFreeSpace > space)
        {
            space = R_EEL_NULL;
        }
        else
        {
            space -= blkFreeSpace;
        }

        (*space_pu32) = space;
        ret = R_EEL_OK;
    }

    return (ret);
} /* R_EEL_GetSpace */


/*********************************************************************************************************************
 * Function name:  R_EEL_GetEraseCounter
 *********************************************************************************************************************/
/**
 *  User interface function:
 *  This function returns the blocks erase counter. All blocks have the same erase counter +-1.
 *
 *  @param      counter_pu32        pointer to the erase counter variable
 *
 *  @return     Function execution error result
 *              - R_EEL_OK
 *              - R_EEL_ERR_ACCESS_LOCKED
 */
/*********************************************************************************************************************/
r_eel_status_t R_EEL_GetEraseCounter (uint32_t * counter_pu32)                       /*PRQA S 1503 */
{
    r_eel_status_t ret;

    ret = R_EEL_ERR_ACCESS_LOCKED;

    /* The function may be executed when the EEL is initialized and not locked */
    if ( ( R_EEL_TRUE == R_EEL_UFct_ChkLibraryInitialized () ) &&
         (R_EEL_ACCESS_LOCKED != g_eel_str.ds_str.accessStatus_enu) )
    {
        (*counter_pu32) = g_eel_str.ec_u32;
        ret = R_EEL_OK;
    }

    return (ret);
}


/*********************************************************************************************************************
 * Function name:  R_EEL_GetVersionString
 *********************************************************************************************************************/
/**
 *  User interface function:
 *  Returns the pointer to the library version string, stored in the library code section.
 *
 *  @param      ---
 *  @return     pointer to the version string in Flash
 */
/*********************************************************************************************************************/
#define R_EEL_START_SEC_CONST
#include "r_eel_mem_map.h"                                                                          /* PRQA S 5087 */

const uint8_t *R_EEL_GetVersionString (void)                                     /*PRQA S 1503 */
{
    static const uint8_t r_eel_vStr[] = R_EEL_VERSION_STRING;

    return (&r_eel_vStr[0]);
}

#define R_EEL_STOP_SEC_CONST
#include "r_eel_mem_map.h"                                                                          /* PRQA S 5087 */

/*********************************************************************************************************************/
#define R_EEL_STOP_SEC_PUBLIC_CODE
#include "r_eel_mem_map.h"                                                                          /* PRQA S 5087 */

/*********************************************************************************************************************/

/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule --- (QAC message 0862)
 * Reason:       QAC claims multiple inclusion of r_eel_mem_map.h.
 * Verification: Required for memory mapping (AUTOSAR concept)
 *********************************************************************************************************************/
/* PRQA S 0862 */


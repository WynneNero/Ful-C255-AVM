#define TESTTT 0x1234

#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_OFF 0292
#endif
/*********************************************************************************************************************
 * Library       : Data Flash Access Library for Renesas RH850 devices
 *
 * File Name     : $Source: r_fdl_hw_access.c $
 * Lib. Version  : $RH850_FDL_LIB_VERSION_T01: V1.03 $
 * Mod. Revision : $Revision: 1.32 $
 * Mod. Date     : $Date: 2013/11/08 15:54:26MEZ $
 * Device(s)     : RV40 Flash based RH850 microcontroller
 * Description   : FDL hardware interface functions
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
 * MISRA Rule:   MISRA-C 2004 rule 19.1 (QAC message 5087)
 * Reason:       The section mapping concept (Mapping code, constants and data to specific linker sections) bases on
 *               a central include file containing all section mapping  defines and pragmas. This need to be included
 *               multiple times within the code. The file itself only contains those defines and pragmas.
 * Verification: This is the standard concept defined for AUTOSAR implementations
 *********************************************************************************************************************/



/*********************************************************************************************************************
 * FDL header files include
 *********************************************************************************************************************/
#include "r_fdl_global.h"

/*********************************************************************************************************************
 * local function prototypes
 *********************************************************************************************************************/
R_FDL_STATIC void             R_FDL_FCUFct_ForcedStop   (void);
R_FDL_STATIC r_fdl_status_t   R_FDL_IFct_ChkAccessRight (r_fdl_accessType_t accType, 
                                                         uint32_t granularity_u32);
R_FDL_STATIC void             R_FDL_IFct_ExeCodeInRAM   (r_fdl_pFct_ExeInRAM pFct,
                                                         uint32_t * param);
R_FDL_STATIC uint32_t         R_FDL_IFct_GetFWParam     (uint32_t addr);
R_FDL_STATIC void             R_FDL_FCUFct_InitRAM_Asm  (uint32_t * param);
R_FDL_STATIC void             R_FDL_IFct_GetFWParam_Asm (uint32_t * param);
R_FDL_STATIC uint8_t          R_FDL_IFct_ReadMemoryU08  (uint32_t add);
R_FDL_STATIC uint16_t         R_FDL_IFct_ReadMemoryU16  (uint32_t add);
R_FDL_STATIC uint32_t         R_FDL_IFct_ReadMemoryU32  (uint32_t add);
R_FDL_STATIC void             R_FDL_IFct_WriteMemoryU16 (uint32_t add, uint16_t val);
R_FDL_STATIC void             R_FDL_IFct_WriteMemoryU32 (uint32_t add, uint32_t val);

/*********************************************************************************************************************
 * FDL internal section mapping definitions
 *********************************************************************************************************************/
#define R_FDL_START_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.h"                                                                          /* PRQA S 5087 */

#define R_FDL_START_SEC_CONST
#include "r_fdl_mem_map.h"                                                                          /* PRQA S 5087 */

#if R_FDL_COMPILER == R_FDL_COMP_REC
    #define asm _asm
#endif


/*********************************************************************************************************************
 * Function name:  R_FDL_IFct_ReadMemoryU32
 *********************************************************************************************************************/
/**
 * Function to read a 32-bit IO register or memory
 *
 * @param[in]  add - source address
 * @return     32-bit register contents
 */
/*********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 11.3 (QAC message 0303)
 * Reason:       For effective embedded programming, integer to pointer conversions are used
 * Verification: The converted addresses are essential for complete code execution. Incorrect
 *               conversion would result in test fails.
 *********************************************************************************************************************/
R_FDL_STATIC uint32_t  R_FDL_IFct_ReadMemoryU32 (uint32_t add)
{
    return ( *( (volatile uint32_t *)(add) ) );                                                     /* PRQA S 0303 */
}

/*********************************************************************************************************************
 * Function name:  R_FDL_IFct_ReadMemoryU08
 *********************************************************************************************************************/
/**
 * Function to read a 8-bit IO register or memory
 *
 * @param[in]  add - source address
 * @return     8-bit register contents
 */
/*********************************************************************************************************************/
/*********************************************************************************************************************
   MISRA Rule:   MISRA-C 2004 rule 11.3 (QAC message 0303)
   Reason:       For effective embedded programming, integer to pointer conversions are used
   Verification: The converted addresses are essential for complete code execution. Incorrect
                 conversion would result in test fails.
 *********************************************************************************************************************/
R_FDL_STATIC uint8_t  R_FDL_IFct_ReadMemoryU08 (uint32_t add)
{
    return ( *( (volatile uint8_t *)(add) ) );                                                      /* PRQA S 0303 */
}

/*********************************************************************************************************************
 * Function name:  R_FDL_IFct_ReadMemoryU16
 *********************************************************************************************************************/
/**
 * Function to read a 16-bit IO register or memory
 *
 * @param[in]  add - source address
 * @return     16-bit register contents
 */
/*********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 11.3 (QAC message 0303)
 * Reason:       For effective embedded programming, integer to pointer conversions are used
 * Verification: The converted addresses are essential for complete code execution. Incorrect
 *               conversion would result in test fails.
 *********************************************************************************************************************/
R_FDL_STATIC uint16_t  R_FDL_IFct_ReadMemoryU16 (uint32_t add)
{
    return ( *( (volatile uint16_t *)(add) ) );                                                     /* PRQA S 0303 */
}



/*********************************************************************************************************************
 * Function name:  R_FDL_IFct_WriteMemoryU08
 *********************************************************************************************************************/
/**
 * Function to write a 8-bit IO register or memory
 *
 * @param[in]  add - write destination address
 * @param[in]  val - 8-bit write data
 * @return     ---
 */
/*********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 11.3 (QAC message 0303)
 * Reason:       For effective embedded programming, integer to pointer conversions are used
 * Verification: The converted addresses are essential for complete code execution. Incorrect
 *               conversion would result in test fails.
 *********************************************************************************************************************/
void R_FDL_IFct_WriteMemoryU08 (uint32_t add, uint8_t val)
{
    ( *( (volatile uint8_t *)(add) ) ) = val;                                                       /* PRQA S 0303 */
}


/*********************************************************************************************************************
 * Function name:  R_FDL_IFct_WriteMemoryU16
 *********************************************************************************************************************/
/**
 * Function to write a 16-bit IO register or memory
 *
 * @param[in]  add - write destination address
 * @param[in]  val - 16-bit write data
 * @return     ---
 */
/*********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 11.3 (QAC message 0303)
 * Reason:       For effective embedded programming, integer to pointer conversions are used
 * Verification: The converted addresses are essential for complete code execution. Incorrect
 *               conversion would result in test fails.
 *********************************************************************************************************************/
R_FDL_STATIC void R_FDL_IFct_WriteMemoryU16 (uint32_t add, uint16_t val)
{
    ( *( (volatile uint16_t *)(add) ) ) = val;                                                      /* PRQA S 0303 */
}


/*********************************************************************************************************************
 * Function name:  R_FDL_IFct_WriteMemoryU32
 *********************************************************************************************************************/
/**
 * Function to write a 32-bit IO register or memory
 *
 * @param[in]  add - write destination address
 * @param[in]  val - 32-bit write data
 * @return     ---
 */
/*********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 11.3 (QAC message 0303)
 * Reason:       For effective embedded programming, integer to pointer conversions are used
 * Verification: The converted addresses are essential for complete code execution. Incorrect
 *               conversion would result in test fails.
 *********************************************************************************************************************/
R_FDL_STATIC void R_FDL_IFct_WriteMemoryU32 (uint32_t add, uint32_t val)
{
    ( *( (volatile uint32_t *)(add) ) ) = val;                                                      /* PRQA S 0303 */
}


/*********************************************************************************************************************
 * Function name:  R_FDL_IFct_CalcFOpUnitCnt_BC
 *********************************************************************************************************************/
/**
 * This function calculates the correct unit count for Flash operations.
 * Calculation basics: Blank Check may not overlap Flash macros
 * Smallest possible Flash macros are assumed. So, also operations within physical macros are cut, when a minimum
 * theoritical macro boundary is hit.
 *
 * @param[in/out]  cnt    - number of operation units. The input value is cut down to match the boundary conditions
 * @param[in]      add    - operation start address
 * @return         ---
 */
/*********************************************************************************************************************/
void R_FDL_IFct_CalcFOpUnitCnt_BC (uint32_t * cnt, uint32_t add)
{
    uint32_t cntTmp;
    uint32_t addMax;
    uint32_t cntTmpMax;

    cntTmp = (*cnt);

    /* Consider macro boundaries */
    addMax = ( (add / R_FDL_MACROSIZE_MIN) * R_FDL_MACROSIZE_MIN ); /* Calculate macro boundary */
    addMax += R_FDL_MACROSIZE_MIN;
    cntTmpMax = (addMax - add);                  /* Calculate remaining operations in the macro */
    if (cntTmpMax < cntTmp)
    {
        cntTmp = cntTmpMax;                                         /* Limit count to the macro maximum */
    }

    *cnt = cntTmp;

} /* R_FDL_IFct_CalcFOpUnitCnt_BC */


/*********************************************************************************************************************
 * Function name:  R_FDL_IFct_ChkAccessBoundaries
 *********************************************************************************************************************/
/**
 * This function checks if the Flash access boundaries are correct. Parameter error if:
 * - addStart granularity is not correct
 * - end address calc. wrap around
 * - end address overflow
 * - bCnt = 0
 * - selected block range is not in the correct pool (User/EEL)
 *
 * @param[in]  addStart        - Start address of the range to access
 * @param[in]  bCnt            - Number of bytes to access
 * @param[in]  accType         - type of FDL access (user or EEL)
 * @param[in]  granularity_u32 - Granularity for each command 
 * @return     Returns the access check result
 *             - R_FDL_BUSY (check was OK)
 *             - R_FDL_ERR_PARAMETER (parameter error detected)
 */
/*********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 21.1 (QAC message 2912)
 * Reason:       Wraparound in unsigned arithmetic operation, used to detect parameter error.
 * Verification: A check against wraparound is performed immediately after the arithmetic operation in cause.
 *********************************************************************************************************************/
r_fdl_status_t R_FDL_IFct_ChkAccessBoundaries (uint32_t addStart,
                                               uint32_t bCnt,
                                               r_fdl_accessType_t accType,
                                               uint32_t granularity_u32)
{
    uint32_t eelPoolStart,
             eelPoolSize,
             eelPoolEnd,
             fdlPoolEnd,
             addEnd;
    r_fdl_status_t ret;
    r_fdl_flag_t   inEelRange;

    ret = R_FDL_BUSY;

    eelPoolStart = (g_fdl_str.RTCfg_pstr->eelPoolStart_u16) << R_FDL_BLOCK_SIZE_2N;
    eelPoolSize  = (g_fdl_str.RTCfg_pstr->eelPoolSize_u16) << R_FDL_BLOCK_SIZE_2N;
    fdlPoolEnd   = ( (g_fdl_str.RTCfg_pstr->fdlPoolSize_u16) << R_FDL_BLOCK_SIZE_2N ) - 1uL;

    inEelRange = R_FDL_FALSE;

    /* ------------- Judge invalid addresses ------------ */
    if (0uL == bCnt)
    {
        ret = R_FDL_ERR_PARAMETER;
    }
    else
    {
        addEnd = (addStart + bCnt) - 1uL;                                                          /* PRQA S 2912 */
        if ( (addStart > addEnd) ||                     /* end address calc. wrap around */
             ( (addEnd >= g_fdl_str.dfSize_u32) ||      /* end address overflow */
                                                        /* cnt parameter error.
                                                           Granularity is correct by default (user IF bases on block/word
                                                           count, lib. internally changed to byte cnt */
                 ( (addStart & (granularity_u32 - 1uL) ) != 0x00000000uL) ) ) /* address granularity */
        {
            ret = R_FDL_ERR_PARAMETER;
        }
        else
        {
            /* ------------- Judge access boundaries ------------ */
            /* Check EEL range: Are we inside, outside or overlapping
               eelPoolSize > 0: condition that the range is defined at all */
            if (eelPoolSize > 0u)
            {
                eelPoolEnd   = (eelPoolStart + eelPoolSize) - 1u;
                if ( (addStart >= eelPoolStart) && (addEnd <= eelPoolEnd) )
                {
                    inEelRange = R_FDL_TRUE;
                }
                else
                {
                    if ( !( (addEnd < eelPoolStart) || (addStart > eelPoolEnd) ) )
                    {
                        ret = R_FDL_ERR_PARAMETER;
                    }
                }
            }
    
            /* As EEL we must remain in the EEL range */
            if (R_FDL_ACCESS_EEL == accType)
            {
                if (R_FDL_FALSE == inEelRange)
                {
                    ret = R_FDL_ERR_PARAMETER;
                }
            }
            /* As user we must remain in the Data Flash but outside EEL range */
            else if (R_FDL_ACCESS_USER == accType)
            {
                if ( (addEnd > fdlPoolEnd) || (R_FDL_TRUE == inEelRange) )
                {
                    ret = R_FDL_ERR_PARAMETER;
                }
            }
            else
            {
                ret = R_FDL_ERR_PARAMETER;
            }
        }
    }
    return (ret);
} /* R_FDL_IFct_ChkAccessBoundaries */


/*********************************************************************************************************************
 * Function name:  R_FDL_IFct_ChkAccessRight
 *********************************************************************************************************************/
/**
 * The check is a robustness feature against modification from outside the library as the parameter
 * check during command initiation should have detected any parameter error already. This check
 * shall block wrong settings directly before starting the Flash hardware. So,
 * on violation, the returned error is a protection error, not a parameter error. \n
 * The function reads back the access parameters from the FCU for the check and compares them
 * against the access rights defined by the descriptor.
 *
 * @param[in]  accType - type of FDL access (user or EEL)
 * @param[in]  granularity_u32 - Granularity for each command, used to determine if start address is aligned properly
 *
 * @return     Returns the access check result
 *             - R_FDL_OK (check was OK)
 *             - R_FDL_ERR_PROTECTION (parameter detected)
 */
/*********************************************************************************************************************/
R_FDL_STATIC r_fdl_status_t R_FDL_IFct_ChkAccessRight (r_fdl_accessType_t accType,
                                                       uint32_t granularity_u32)
{
    r_fdl_status_t ret;
    uint32_t       addStart, bCnt;

    addStart = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSADR_U32);
    bCnt     = (R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FEADR_U32) - addStart) + R_FDL_WRITE_SIZE;

    #ifdef PATCH_TO_SIMULATE_ERRORS
        R_FDL_COV_SAVEOFF
        if (tstData_str.simError_enu == R_FDL_TRUE)
        {
            if (R_FDL_SIM_ERROR_PROTECTION == tstData_str.simErrorType_enu)
            {
                /* bCnt = 0 must raise a protection error */
                bCnt = 0;
                tstData_str.simError_enu = R_FDL_FALSE;
            }
        }
        R_FDL_COV_RESTORE
    #endif


    ret = R_FDL_IFct_ChkAccessBoundaries (addStart, bCnt, accType, granularity_u32);
    /* R_FDL_IFct_ChkAccessBoundaries returns PARAMETER error as it is used in R_FDL_Execute for
       parameter check. If we check directly before Flash operation start, we want to return
       R_FDL_ERR_PROTECTION in error case. So we patch the return value here */
    if (R_FDL_ERR_PARAMETER == ret)
    {
        ret = R_FDL_ERR_PROTECTION;
    }

    return (ret);
} /* R_FDL_IFct_ChkAccessRight */



/*********************************************************************************************************************
 * Function name:  R_FDL_FCUFct_Reset
 *********************************************************************************************************************/
/**
 * Reset FCU and FACI registers
 *
 * @param      ---
 * @return     Returns the reset result
 *             - R_FDL_OK
 *             - R_FDL_ERR_PROTECTION (mode switch failed)
 */
/*********************************************************************************************************************/
r_fdl_status_t R_FDL_FCUFct_Reset (void)
{
    r_fdl_status_t ret;

    ret = R_FDL_FCUFct_SwitchMode (R_FCU_MODE_PE);

    if (R_FDL_OK == ret)
    {
        R_FDL_FCUFct_ForcedStop ();
        R_FDL_FCUFct_ClearStatus ();

        ret = R_FDL_FCUFct_SwitchMode (R_FCU_MODE_USER);
    }

    return (ret);
}


/*********************************************************************************************************************
 * Function name:  R_FDL_FCUFct_ForcedStop
 *********************************************************************************************************************/
/**
 * Reset FCU and FACI registers
 *
 * @param      ---
 * @return     ---
 */
/*********************************************************************************************************************/
R_FDL_STATIC void R_FDL_FCUFct_ForcedStop (void)
{
    uint32_t res = 0u;

    R_FDL_IFct_WriteMemoryU08 (R_FCU_DFLASH_CMD_ADD, R_FCU_CMD_FORCED_STOP);

    do
    {
        res = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSTATR_U32);
    }
    while ( R_FCU_REGBIT_FSTATR_FRDY != (R_FCU_REGBIT_FSTATR_FRDY & res) );
}



/*********************************************************************************************************************
 * Function name:  R_FDL_FCUFct_ClearStatus
 *********************************************************************************************************************/
/**
 * Clear (error) status of the sequencer by the clear status FCU command
 *
 * @param      ---
 * @return     ---
 */
/*********************************************************************************************************************/
void R_FDL_FCUFct_ClearStatus (void)
{
    uint32_t res32;
    uint8_t  res8;

    res32 = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSTATR_U32);

    if ( R_FCU_REGBIT_FSTATR_ILGERR == (R_FCU_REGBIT_FSTATR_ILGERR & res32) )
    {
        res8 = R_FDL_IFct_ReadMemoryU08 (R_FCU_REGADD_FASTAT_U08);
        /* Only CLDLK bit may be set, others have to be cleared */
        if (R_FCU_REGBIT_FASTAT_CMDLK != res8)                                                     /* CCOV 0002 */
        {
            R_FDL_IFct_WriteMemoryU08 (R_FCU_REGADD_FASTAT_U08, R_FCU_REGBIT_FASTAT_CMDLK);
        }
    }

    R_FDL_IFct_WriteMemoryU08 (R_FCU_DFLASH_CMD_ADD, R_FCU_CMD_CLEARSTAT);
} /* R_FDL_FCUFct_ClearStatus */


/*********************************************************************************************************************
 * Function name:  R_FDL_IFct_GetFWParam
 *********************************************************************************************************************/
/**
 * Call the assembler function to read out a firmware parameter from the Extra area
 *
 * @param[in]  address
 * @return     value
 */
/*********************************************************************************************************************/
R_FDL_STATIC uint32_t R_FDL_IFct_GetFWParam (uint32_t addr)
{
    uint32_t getFWParam[2];

    /* Initialize the RAM function parameters */
    getFWParam[0] = addr;                               /* Read address */

    /* Execute Copy routine in RAM as BFA need to be temporarily switched on */
    R_FDL_IFct_ExeCodeInRAM ( &R_FDL_IFct_GetFWParam_Asm, (uint32_t *)(&getFWParam[0]) );

    return (getFWParam[1]);
}

/*********************************************************************************************************************
 * Function name:  R_FDL_IFct_GetFWParam_Asm
 *********************************************************************************************************************/
/**
 * Assembler function to read out a firmware parameter from the Extra area
 *
 * @param[in]  address
 * @return     value
 * Copy the firmware to the FCU RAM --> This function is executed in RAM \n
 * Sequence is:
 * - Switch on BFA
 * - Clear Cache, clear line buffer
 * - Read firmware parameter
 * - Switch off BFA
 * - Clear Cache, clear line buffer
 *
 * @param[in]  initRamParam[0]   - Address to read
 * @param[out] initRamParam[1]   - Read value
 * @return     ---
 */
/*********************************************************************************************************************/

/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 3.1 (QAC message 3006)
 * Reason:       This function contains a mixture of in-line assembler statements and C statements.
 *               The function is copied to RAM into a memory range of fix size. So, the function itself must have a
 *               fix size which cannot be realized by a c-compiler. So, the function is written in Assembler
 * Verification: Review of the c-interface (only temporary registers are used and the stack size is unchanged
 *********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 3.1 (QAC message 1006)
 * Reason:       In-line assembler construct is a language extension. The code has been ignored.
 * Verification: -
 *********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 3.1 (QAC message 3206)
 * Reason:       function parameter seems to be not used in the function as no c-code relates on
 *               it, but the assembler code uses the parameter
 * Verification: -
 *********************************************************************************************************************/
R_FDL_COV_SAVEOFF

#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_OFF 1006
#endif

#if R_FDL_COMPILER == R_FDL_COMP_GHS
R_FDL_STATIC void R_FDL_IFct_GetFWParam_Asm (uint32_t * param)                                  /* PRQA S 3006,3206 */
{
    /* GHS compilers use r6~r10 as scratch registers. 
       r6: parameter adddress
       r7, r9: work register
       r8: value for switch BFA on/off
    */ 

          /* ----- Switch ON BFA ----- */
    asm(" movea 0x01, r0, r8                    ");     /* Hard coded BFASEL value to switch on EXA3*/
    asm(" br _R_FDL_IFct_GetFWParam_Asm_SWBFA   ");
    
    asm(" _R_FDL_IFct_GetFWParam_Asm_Read:      ");

          /* Read the data we need */
    asm(" ld.w 0[r6], r7                        ");
    asm(" ld.w 0[r7], r7                        ");
    asm(" st.w r7, 4[r6]                        ");

          /* ----- Switch OFF BFA ----- */
    asm(" mov r0, r8                            ");     /* Hard coded BFASEL value to switch off EXA3*/

          /* Switch BFA and clear the cache */
          /* & line buffer (Called twice) */
    asm(" _R_FDL_IFct_GetFWParam_Asm_SWBFA:     ");
    
          /* Switch EXA3 */
    asm(" mov 0xffc59008, r7                    ");     /* Hard coded address of BFASEL */
    asm(" st.b r8, 0[r7]                        ");

          /* Clear the cache */
    asm(" stsr 24, r7, 4                        ");     /* system register 24, 4 is ICCTRL */
    asm(" ori 0x0100, r7, r7                    ");     /* set cache clear bit 8 */
    asm(" ldsr r7, 24, 4                        ");               
    asm(" stsr 24, r7, 4                        ");     /* Dummy read to system register to complete the operation */

          /* Check the core */
    asm(" stsr 6, r7, 1                         ");     /* system register 24, 4 is PID */
    asm(" andi 0x00E0, r7, r7                   ");     /* G3K core is 0x20 till 0x3F of Byte 0; so mask out */
                                                        /* Bytes 1~3 and bit 0x10 which is irrelevant */
    asm(" movea 0x20, r0, r9                    ");     /* compare against 0x20 which now also covers 0x30  */
    asm(" cmp r7, r9                            ");        
    asm(" bne _R_FDL_IFct_GetFWParam_Asm_G3M    ");               
    
          /* G3K core: Clear BWC */
    asm(" mov 0x01, r7                          ");     /* BWCBUFCLR bit */
    asm(" mov 0xFFBC0700, r9                    ");     /* BWCBUFEN address */
    asm(" st.b r0, 0[r9]                        ");     /* BWCBUFCLR = 0 */
    asm(" st.b r7, 0[r9]                        ");     /* BWCBUFCLR = 1 */
    asm(" st.b r0, 0[r9]                        ");     /* BWCBUFCLR = 0 */
    asm(" br _R_FDL_IFct_GetFWParam_Asm_CCEnd   ");               
        
          /* G3M core: clear sub-cache */
    asm(" _R_FDL_IFct_GetFWParam_Asm_G3M:       ");               
    asm(" stsr 24, r7, 13                       ");     /* system register 24, 13 is CDBCR */
    asm(" ori 0x02, r7, r7                      ");     /* set cache clear bit 1 */
    asm(" ldsr r7, 24, 13                       ");               
    asm(" stsr 24, r7, 13                       ");     /* Dummy read to system register to complete the operation */

    asm(" _R_FDL_IFct_GetFWParam_Asm_CCEnd:     ");              
    asm(" synci                                 ");     /* sync to clear the line buffer */
     
          /* Check where to continue */
    asm(" cmp r8, r0                            ");     /* we check here against the hard coded BFASEL value */
    asm(" bnz _R_FDL_IFct_GetFWParam_Asm_Read   "); 
}
#endif 

#if R_FDL_COMPILER == R_FDL_COMP_IAR
R_FDL_STATIC void R_FDL_IFct_GetFWParam_Asm (uint32_t * param)                                  /* PRQA S 3006,3206 */
{
    /* IAR compiler uses r1, r5~r9 as scratch registers. 
       --> change from REC/GHS assembler: 
           - added code to move parameter register r1 to r6 */
    
    __asm("                                         \n"
          " /* IAR calling convention conversion */ \n"
          " mov r1, r6                              \n"                  
          "                                         \n"
          " movea 0x01, r0, r8                      \n"
          " br _R_FDL_IFct_GetFWParam_Asm_SWBFA     \n"                  
          "                                         \n"
          " _R_FDL_IFct_GetFWParam_Asm_Read:        \n"
          "                                         \n"
          " /* Read the data we need */             \n"
          " ld.w 0[r6], r7                          \n"
          " ld.w 0[r7], r7                          \n"
          " st.w r7, 4[r6]                          \n"
          "                                         \n"
          " /* ----- Switch OFF BFA ----- */        \n"
          " mov r0, r8                              \n"
          "                                         \n"
          " /* Switch BFA and clear the cache */    \n"
          " /* & line buffer (Called twice) */      \n"
          " _R_FDL_IFct_GetFWParam_Asm_SWBFA:       \n"
          "                                         \n"
          " /* Switch EXA3 */                       \n"
          " mov 0xffc59008, r7                      \n"
          " st.b r8, 0[r7]                          \n"
          "                                         \n"
          " /* Clear the cache */                   \n"
          " stsr 24, r7, 4                          \n"
          " ori 0x0100, r7, r7                      \n"
          " ldsr r7, 24, 4                          \n"
          " stsr 24, r7, 4                          \n"
          "                                         \n"
          " /* Check the core */                    \n"
          " stsr 6, r7, 1                           \n"
          " andi 0x00E0, r7, r7                     \n"
          "                                         \n"
          " movea 0x20, r0, r9                      \n"
          " cmp r7, r9                              \n"
          " bne _R_FDL_IFct_GetFWParam_Asm_G3M      \n"
          "                                         \n"
          " /* G3K core: Clear BWC */               \n"
          " mov 0x01, r7                            \n"
          " mov 0xFFBC0700, r9                      \n"
          " st.b r0, 0[r9]                          \n"
          " st.b r7, 0[r9]                          \n"
          " st.b r0, 0[r9]                          \n"
          " br _R_FDL_IFct_GetFWParam_Asm_CCEnd     \n"
          "                                         \n"
          " /* G3M core: clear sub-cache */         \n"
          " _R_FDL_IFct_GetFWParam_Asm_G3M:         \n"
          " stsr 24, r7, 13                         \n"
          " ori 0x02, r7, r7                        \n"
          " ldsr r7, 24, 13                         \n"
          " stsr 24, r7, 13                         \n"
          "                                         \n"
          " _R_FDL_IFct_GetFWParam_Asm_CCEnd:       \n"
          " synci                                   \n"
          "                                         \n"
          " /* Check where to continue */           \n"
          " cmp r8, r0                              \n"
          " bnz _R_FDL_IFct_GetFWParam_Asm_Read     \n"
        );

} /* R_FDL_IFct_GetFWParam_Asm */
#endif 

#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_ON 1006
#endif

#if R_FDL_COMPILER == R_FDL_COMP_REC
#pragma inline_asm R_FDL_IFct_GetFWParam_Asm
R_FDL_STATIC void R_FDL_IFct_GetFWParam_Asm (uint32_t * param)
{
    movea 0x01, r0, r8                      
    br _R_FDL_IFct_GetFWParam_Asm_SWBFA     
                                            
    _R_FDL_IFct_GetFWParam_Asm_Read:        
                                            
    ld.w 0[r6], r7                          
    ld.w 0[r7], r7                          
    st.w r7, 4[r6]                          
                                            
    mov r0, r8                              
                                            
    _R_FDL_IFct_GetFWParam_Asm_SWBFA:       
                                            
    mov 0xffc59008, r7                      
    st.b r8, 0[r7]                          
                                           
    stsr 24, r7, 4                          
    ori 0x0100, r7, r7                      
    ldsr r7, 24, 4                          
    stsr 24, r7, 4
                                            
    stsr 6, r7, 1                           
    andi 0x00E0, r7, r7                     
                                            
    movea 0x20, r0, r9
    cmp r7, r9                              
    bne _R_FDL_IFct_GetFWParam_Asm_G3M      
                                            
    mov 0x01, r7                            
    mov 0xFFBC0700, r9                      
    st.b r0, 0[r9]                          
    st.b r7, 0[r9]                          
    st.b r0, 0[r9]                          
    br _R_FDL_IFct_GetFWParam_Asm_CCEnd     
                                            
    _R_FDL_IFct_GetFWParam_Asm_G3M:         
    stsr 24, r7, 13                         
    ori 0x02, r7, r7                        
    ldsr r7, 24, 13                         
    stsr 24, r7, 13
                                            
    _R_FDL_IFct_GetFWParam_Asm_CCEnd:       
    synci                                   
                                            
    cmp r8, r0                              
    bnz _R_FDL_IFct_GetFWParam_Asm_Read     
}
#endif 

R_FDL_COV_RESTORE


/*********************************************************************************************************************
 * Function name:  R_FDL_FCUFct_GetDFSize
 *********************************************************************************************************************/
/**
 * Get Data Flash size \n
 *
 * @return     size in Bytes
 */
/*********************************************************************************************************************/
uint32_t R_FDL_FCUFct_GetDFSize (void)
{
    uint32_t    ret,
                data,
                dataAddr;
    
    dataAddr = R_FDL_IFct_GetFWParam (R_FDL_EXTRA3_SCDSADD);    /* Entry tells where to find the PRD* information */
    
    data = R_FDL_IFct_ReadMemoryU32 (dataAddr + R_FDL_PRDSEL3_OFFSET);
    data &= 0x0000FFFFuL;       /* Lower 16Byte are the DF size in kB. So, multiply accordingly */    
    ret = data * 1024; 

    return (ret);
} /* R_FDL_FCUFct_SetFrequency */


/*********************************************************************************************************************
 * Function name:  R_FDL_FCUFct_SetFrequency
 *********************************************************************************************************************/
/**
 * Set the FCU frequency. \n
 * The function may return an error if the frequency could not be set (Timeout of command error).
 *
 * @param[in]  APBFrequency - FCU frequency, set in MHz
 * @return     configuration result
 *             - R_FDL_OK                - Frequency set successfully
 *             - R_FDL_ERR_PROTECTION    - Some security measure prevented mode switch and so, the frequency setting
 *             - R_FDL_ERR_CONFIGURATION - Frequency parameter out of range
 */
/*********************************************************************************************************************/
r_fdl_status_t R_FDL_FCUFct_SetFrequency (uint16_t fCpu)
{
    r_fdl_status_t ret;
    uint16_t       fFaci;
    uint32_t       fwVal;
    uint8_t        fwVer, fDivider;
    uint32_t       fMin, fMax, fPClk;

    ret = R_FDL_OK;

    /* Get firmware parameters */
    /* FW version is 1 Byte on not word aligned address, so we read word aligned and calculate the correct byte */
    fwVal    = R_FDL_IFct_GetFWParam (R_FDL_EXTRA3_FWVER & (~0x00000003uL) ); 
    fwVer    = (uint8_t)( (fwVal >> 8) & 0xFFu);                     
    
    /* Frequency is 32bit value in Hz. We need to calculate MHz from that */
    fwVal    = R_FDL_IFct_GetFWParam (R_FDL_EXTRA3_FMIN);
    fMin     = fwVal / 1000000uL;
    fwVal    = R_FDL_IFct_GetFWParam (R_FDL_EXTRA3_FMAX);
    fMax     = fwVal / 1000000uL;

    /* Divider 1 Byte only but on a word aligned address, so we read word aligned and calculate the correct byte */
    fwVal    = R_FDL_IFct_GetFWParam (R_FDL_EXTRA3_FDIV);
    fDivider = (uint8_t)(fwVal & 0xFFu);                     

    /* PCLK Frequency is 32bit value in Hz. We need to calculate MHz from that */
    fwVal    = R_FDL_IFct_GetFWParam (R_FDL_EXTRA3_FPCLK);
    fPClk    = fwVal / 1000000uL;

    if (0xFF != fwVer)                                                                             /* CCOV 0003 */
    {
        if ( (fCpu >= fMin) && (fCpu <= fMax) )
        {
            if(0xFF == fDivider)                                                                   /* CCOV 0004 */
            {
                /* FCU frequency is fix and independent from the CPU frequency */
                fFaci = (uint16_t)fPClk;
            }
            else
            {
                /* FCU frequency calculation (incl. frequency round up) */
                fFaci = (fCpu + fDivider) - 1;
                fFaci = fFaci / fDivider;
            }
    
            /* Set frequency */
            ret = R_FDL_FCUFct_SwitchMode (R_FCU_MODE_PE);          /* Switch to PE Mode */
            if (R_FDL_OK == ret)
            {
                R_FDL_IFct_WriteMemoryU16 (R_FCU_REGADD_PCKAR_U16, R_FCU_REGBIT_PCKAR_KEY + fFaci);

                /* Switch to User Mode again */
                ret = R_FDL_FCUFct_SwitchMode (R_FCU_MODE_USER);
            }
        }
        else
        {
            ret = R_FDL_ERR_CONFIGURATION;
        }
    }

    return (ret);
} /* R_FDL_FCUFct_SetFrequency */

/*********************************************************************************************************************
 * Function name:  R_FDL_FCUFct_InitRAM
 *********************************************************************************************************************/
/**
 * Function to copy the firmware to the FCU RAM. \n
 * As BFLASH need to be activated to copy code from device firmware to FCU RAM, some code needs to
 * be executed from RAM. \n
 * This function:
 * - prepares the parameter structure for the function to be executed in RAM
 * - calls the function to copy and execute the code in RAM
 * - reset the FCU
 * - check the code in FCU RAM by a checksum
 * - clear the cache
 *
 * @param      ---
 * @return
 *             - R_FDL_OK
 *             - R_FDL_ERR_INTERNAL (code in FCU RAM not OK)
 *
 */
/*********************************************************************************************************************/
r_fdl_status_t R_FDL_FCUFct_InitRAM (void)
{
    uint32_t       initRamParam[3];
    r_fdl_status_t ret;
    uint32_t       add, addEnd,
                   chkSum, chkSumCmp;

    /* Initialize the RAM function parameters */
    initRamParam[0] = R_FDL_FCU_RAM_SRC_ADD;
    initRamParam[1] = R_FDL_FCU_RAM_ADD;
    initRamParam[2] = R_FDL_FCU_RAM_SIZE;

    /* Activate FCU RAM access */
    R_FDL_IFct_WriteMemoryU16 (R_FCU_REGADD_FCURAME_U16,   R_FCU_REGBIT_FCURAME_FCRME + R_FCU_REGBIT_FCURAME_FRAMTRAN
                               + R_FCU_REGBIT_FCURAME_KEY);

    /* Execute Copy routine in RAM as BFA need to be temporarily switched on */
    R_FDL_IFct_ExeCodeInRAM ( &R_FDL_FCUFct_InitRAM_Asm, (uint32_t *)(&initRamParam[0]) );

    /* Set FCU RAM to RW */
    R_FDL_IFct_WriteMemoryU16 (R_FCU_REGADD_FCURAME_U16,   R_FCU_REGBIT_FCURAME_FCRME + R_FCU_REGBIT_FCURAME_KEY);

    /* Calculate and compare FCU RAM checksum */
    addEnd = R_FDL_IFct_ReadMemoryU32 (R_FDL_FCU_RAM_ADD_CHKSUM_END);
    addEnd <<= 2;
    addEnd += R_FDL_FCU_RAM_ADD;
    chkSum = 0x00000000uL;
    for (add = R_FDL_FCU_RAM_ADD; add < addEnd; add += 2)
    {
        chkSum += (uint32_t)( R_FDL_IFct_ReadMemoryU16 (add) );
    }
    chkSumCmp = R_FDL_IFct_ReadMemoryU32 (R_FDL_FCU_RAM_ADD_CHKSUM);

    #ifdef PATCH_TO_SIMULATE_ERRORS
        R_FDL_COV_SAVEOFF
        if ( (tstData_str.simError_enu == R_FDL_TRUE) &&
             (R_FDL_SIM_ERROR_CHKSUM == tstData_str.simErrorType_enu) )
        {
            tstData_str.simError_enu = R_FDL_FALSE;
            chkSumCmp++;
        }
        R_FDL_COV_RESTORE
    #endif /* ifdef PATCH_TO_SIMULATE_ERRORS */



    if (chkSum == chkSumCmp)
    {
        ret = R_FDL_OK;
    }
    else
    {
        ret = R_FDL_ERR_INTERNAL;
    }

    /* Deacivate FCU RAM access */
    R_FDL_IFct_WriteMemoryU16 (R_FCU_REGADD_FCURAME_U16,
                               R_FCU_REGBIT_FCURAME_RESET + R_FCU_REGBIT_FCURAME_KEY);

    return (ret);
} /* R_FDL_FCUFct_InitRAM */

/*********************************************************************************************************************
 * Function name:  R_FDL_FCUFct_InitRAM_Asm
 *********************************************************************************************************************/
/**
 * Copy the firmware to the FCU RAM --> This function is executed in RAM \n
 * Sequence is:
 * - Switchh on BFA
 * - Copy code to FCU
 * - Switch off BFA
 * - Clear Cache
 *
 * @param[in]  param - Parameter array containing addresses and data for the assembler
 *                     function
 * @return     ---
 */
/*********************************************************************************************************************/

/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 3.1 (QAC message 3006)
 * Reason:       This function contains a mixture of in-line assembler statements and C statements.
 *               The assembler instructions are just "nops" to adjust timing
 * Verification: "nop" instructions have no effect at all except timing adjustment.
 *********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 3.1 (QAC message 1006)
 * Reason:       In-line assembler construct is a language extension. The code has been
 *               ignored.
 * Verification: -
 *********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 3.1 (QAC message 3206)
 * Reason:       function parameter seems to be not used in the function as no c-code relates on
 *               it, but the assembler code uses the parameter
 * Verification: -
 *********************************************************************************************************************/

R_FDL_COV_SAVEOFF

#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_OFF 1006
#endif

#if R_FDL_COMPILER == R_FDL_COMP_GHS
R_FDL_STATIC void R_FDL_FCUFct_InitRAM_Asm (uint32_t * param)                                   /* PRQA S 3006,3206 */
{
    /* GHS compilers use r6~r10 as scratch registers. This function requires r6~r9 */ 

          /* ----- Switch ON BFA ----- */
    asm(" movea 0x01, r0, r8                    ");     /* Hard coded BFASEL value to switch on EXA3*/             
    asm(" br _R_FDL_FCUFct_InitRAM_Asm_SWBFA    ");
                                                   
    asm(" _R_FDL_FCUFct_InitRAM_Asm_Copy:       ");
                                                   
          /* Copy FW to RAM */
          /* r7: src, r8: dest, r9: cnt, */
          /* r10: read buffer */
    asm(" ld.w 0[r6], r7                        ");
    asm(" ld.w 4[r6], r8                        ");
    asm(" ld.w 8[r6], r9                        ");     
                                                                                                                   
    asm(" _R_FDL_FCUFct_InitRAM_Asm_Loop:       ");                                                                
    asm(" ld.w 0[r7], r10                       ");                                                                
    asm(" st.w r10, 0[r8]                       ");                                                                
    asm(" add 4, r7                             ");                                                                
    asm(" add 4, r8                             ");                                                                
    asm(" add -4, r9                            ");                                                                
    asm(" bnz _R_FDL_FCUFct_InitRAM_Asm_Loop    ");                                                                
                                                                                                                   
          /* ----- Switch OFF BFA ----- */                                                                         
    asm(" mov r0, r8                            ");     /* Hard coded BFASEL value to switch off EXA3*/            
                                                                                                                   
          /* Switch BFA and clear the cache */                                                                     
          /* & line buffer (Called twice) */                                                                       
    asm(" _R_FDL_FCUFct_InitRAM_Asm_SWBFA:      ");                                                                                                                                                                                                                                                                           
                                                                                                                                                                                                                                                                                                                             
          /* Switch EXA3 */                                                                                                                                                                                                                                                                                                  
    asm(" mov 0xffc59008, r7                    ");     /* Hard coded address of BFASEL */                                                                                                                                                                                                                                   
    asm(" st.b r8, 0[r7]                        ");                                                                                                                                                                                                                                                                          
                                                                                                                                                                                                                                                                                                                            
          /* Clear the cache */                                                                                                                                                                                                                                                                                              
    asm(" stsr 24, r7, 4                        ");     /* system register 24, 4 is ICCTRL */                                                                                                                                                                                                                                
    asm(" ori 0x0100, r7, r7                    ");     /* set cache clear bit 8 */                                                                                                                                                                                                                                          
    asm(" ldsr r7, 24, 4                        ");                                                                                                                                                                                                                                                                          
    asm(" stsr 24, r7, 4                        ");     /* Dummy read to system register to complete the operation */
                                                                                                                                                                                                                                                                                                                             
          /* Check the core */                                                                                                                                                                                                                                                                                               
    asm(" stsr 6, r7, 1                         ");     /* system register 24, 4 is PID */                                                                                                                                                                                                                                   
    asm(" andi 0x00E0, r7, r7                   ");     /* G3K core is 0x20 till 0x3F of Byte 0; so mask out */                                                                                                                                                                                                              
                                                        /* Bytes 1~3 and bit 0x10 which is irrelevant */                                                                                                                                                                                                                     
    asm(" movea 0x20, r0, r9                    ");     /* compare against 0x20 which now also covers 0x30  */                                                                                                                                                                                                               
    asm(" cmp r7, r9                            ");                                                                                                                                                                                                                                                                          
    asm(" bne _R_FDL_FCUFct_InitRAM_Asm_G3M     ");                                                                                                                                                                                                                                                                           
                                                                                                                                                                                                                                                                                                                             
          /* G3K core: Clear BWC */                                                                                                                                                                                                                                                                                          
    asm(" mov 0x01, r7                          ");     /* BWCBUFCLR bit */                                                                                                                                                                                                                                                  
    asm(" mov 0xFFBC0700, r9                    ");     /* BWCBUFEN address */                                                                                                                                                                                                                                               
    asm(" st.b r0, 0[r9]                        ");     /* BWCBUFCLR = 0 */                                                                                                                                                                                                                                                  
    asm(" st.b r7, 0[r9]                        ");     /* BWCBUFCLR = 1 */                                                                                                                                                                                                                                                  
    asm(" st.b r0, 0[r9]                        ");     /* BWCBUFCLR = 0 */                                                                                                                                                                                                                                                  
    asm(" br _R_FDL_FCUFct_InitRAM_Asm_CCEnd    ");                                                                                                                                                                                                                                                                           
                                                                                                                                                                                                                                                                                                                             
          /* G3M core: clear sub-cache */                                                                                                                                                                                                                                                                                    
    asm(" _R_FDL_FCUFct_InitRAM_Asm_G3M:        ");                                                                                                                                                                                                                                                                           
    asm(" stsr 24, r7, 13                       ");     /* system register 24, 13 is CDBCR */                                                                                                                                                                                                                                
    asm(" ori 0x02, r7, r7                      ");     /* set cache clear bit 1 */                                                                                                                                                                                                                                          
    asm(" ldsr r7, 24, 13                       ");                                                                                                                                                                                                                                                                          
    asm(" stsr 24, r7, 13                       ");     /* Dummy read to system register to complete the operation */
                                                                                                                                                                                                                                                                                                                             
    asm(" _R_FDL_FCUFct_InitRAM_Asm_CCEnd:      ");                                                                                                                                                                                                                                                                           
    asm(" synci                                 ");     /* sync to clear the line buffer */                                                                                                                                                                                                                                  
                                                                                                                                                                                                                                                                                                                             
          /* Check where to continue */                                                                                                                                                                                                                                                                                      
    asm(" cmp r8, r0                            ");     /* we check here against the hard coded BFASEL value */                                                                                                                                                                                                              
    asm(" bnz _R_FDL_FCUFct_InitRAM_Asm_Copy    ");                                                                                                                                                                                                                                                                           
}
#endif

#if R_FDL_COMPILER == R_FDL_COMP_IAR
R_FDL_STATIC void R_FDL_FCUFct_InitRAM_Asm (uint32_t * param)                                   /* PRQA S 3006,3206 */
    /* IAR compiler uses r1, r5~r9 as scratch registers. This function requires r6~r10 
       --> change from REC/GHS assembler: 
           - added code to move parameter register r1 to r6
           - replaced r10 by r1 */

    __asm("                                         \n"
          " /* IAR calling convention conversion */ \n"
          " mov r1, r6                              \n"
          "                                         \n"
          " /* ----- Switch ON BFA ----- */         \n"
          " movea 0x01, r0, r8                      \n"
          " br _R_FDL_FCUFct_InitRAM_Asm_SWBFA      \n"
          "                                         \n"
          " _R_FDL_FCUFct_InitRAM_Asm_Copy:         \n"
          "                                         \n"
          " /* Copy FW to RAM */                    \n"
          " /* r7: src, r8: dest, r9: cnt, */       \n"
          " /* r1: read buffer */                   \n"
          " ld.w 0[r6], r7                          \n"
          " ld.w 4[r6], r8                          \n"
          " ld.w 8[r6], r9                          \n"
          "                                         \n"
          " _R_FDL_FCUFct_InitRAM_Asm_Loop:         \n"
          " ld.w 0[r7], r1                          \n"
          " st.w r1, 0[r8]                          \n"
          " add 4, r7                               \n"
          " add 4, r8                               \n"
          " add -4, r9                              \n"
          " bnz _R_FDL_FCUFct_InitRAM_Asm_Loop      \n"
          "                                         \n"
          " /* ----- Switch OFF BFA ----- */        \n"
          " mov r0, r8                              \n"
          "                                         \n"
          " /* Switch BFA and clear the cache */    \n"
          " /* & line buffer (Called twice) */      \n"
          " _R_FDL_FCUFct_InitRAM_Asm_SWBFA:        \n"
          "                                         \n"
          " /* Switch EXA3 */                       \n"
          " mov 0xffc59008, r7                      \n"
          " st.b r8, 0[r7]                          \n"
          "                                         \n"
          " /* Clear the cache */                   \n"
          " stsr 24, r7, 4                          \n"
          " ori 0x0100, r7, r7                      \n"
          " ldsr r7, 24, 4                          \n"
          " stsr 24, r7, 4                          \n"
          "                                         \n"
          " /* Check the core */                    \n"
          " stsr 6, r7, 1                           \n"
          " andi 0x00E0, r7, r7                     \n"
          "                                         \n"
          " movea 0x20, r0, r9                      \n"
          " cmp r7, r9                              \n"
          " bne _R_FDL_FCUFct_InitRAM_Asm_G3M       \n"
          "                                         \n"
          " /* G3K core: Clear BWC */               \n"
          " mov 0x01, r7                            \n"
          " mov 0xFFBC0700, r9                      \n"
          " st.b r0, 0[r9]                          \n"
          " st.b r7, 0[r9]                          \n"
          " st.b r0, 0[r9]                          \n"
          " br _R_FDL_FCUFct_InitRAM_Asm_CCEnd      \n"
          "                                         \n"
          " /* G3M core: clear sub-cache */         \n"
          " _R_FDL_FCUFct_InitRAM_Asm_G3M:          \n"
          " stsr 24, r7, 13                         \n"
          " ori 0x02, r7, r7                        \n"
          " ldsr r7, 24, 13                         \n"
          " stsr 24, r7, 13                         \n"
          "                                         \n"
          " _R_FDL_FCUFct_InitRAM_Asm_CCEnd:        \n"
          " synci                                   \n"
          "                                         \n"
          " /* Check where to continue */           \n"
          " cmp r8, r0                              \n"
          " bnz _R_FDL_FCUFct_InitRAM_Asm_Copy      \n"
         );

} /* R_FDL_IFct_GetFWParam_Asm */
#endif

#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_ON 1006
#endif

#if R_FDL_COMPILER == R_FDL_COMP_REC
#pragma inline_asm R_FDL_FCUFct_InitRAM_Asm
R_FDL_STATIC void R_FDL_FCUFct_InitRAM_Asm (uint32_t * param)
{
    movea 0x01, r0, r8                      
    br _R_FDL_FCUFct_InitRAM_Asm_SWBFA      
                                            
    _R_FDL_FCUFct_InitRAM_Asm_Copy:         
                                            
    ld.w 0[r6], r7                          
    ld.w 4[r6], r8                          
    ld.w 8[r6], r9                          
                                            
    _R_FDL_FCUFct_InitRAM_Asm_Loop:         
    ld.w 0[r7], r10                         
    st.w r10, 0[r8]                         
    add 4, r7                               
    add 4, r8                               
    add -4, r9                              
    bnz _R_FDL_FCUFct_InitRAM_Asm_Loop      
                                            
    mov r0, r8                              
                                            
    _R_FDL_FCUFct_InitRAM_Asm_SWBFA:        
                                            
    mov 0xffc59008, r7                      
    st.b r8, 0[r7]                          
                                           
    stsr 24, r7, 4                          
    ori 0x0100, r7, r7                        
    ldsr r7, 24, 4                          
    stsr 24, r7, 4
                                            
    stsr 6, r7, 1                           
    andi 0x00E0, r7, r7                     
                                            
    movea 0x20, r0, r9                      
    cmp r7, r9                              
    bne _R_FDL_FCUFct_InitRAM_Asm_G3M       
                                            
    mov 0x01, r7                            
    mov 0xFFBC0700, r9                      
    st.b r0, 0[r9]                          
    st.b r7, 0[r9]                          
    st.b r0, 0[r9]                          
    br _R_FDL_FCUFct_InitRAM_Asm_CCEnd      
                                            
    _R_FDL_FCUFct_InitRAM_Asm_G3M:          
    stsr 24, r7, 13                         
    ori 0x02, r7, r7                        
    ldsr r7, 24, 13                         
    stsr 24, r7, 13                 
                                            
    _R_FDL_FCUFct_InitRAM_Asm_CCEnd:        
    synci                                   
                                            
    cmp r8, r0                              
    bnz _R_FDL_FCUFct_InitRAM_Asm_Copy      
}
#endif


R_FDL_COV_RESTORE

/*********************************************************************************************************************
 * Function name:  R_FDL_IFct_ExeCodeInRAM
 *********************************************************************************************************************/
/**
 * Execute a function in RAM. \n
 * This function copies a function to the RAM and jumps to the RAM.
 * Stack is used as storage location for the function to be copied.
 *
 * @param[in]  pFct         - function to execute
 * @param[in]  initRamParam - parameter structure that will be used by the function in RAM. The
 *                            structure pointer is just passed to the function.
 * @return     ---
 */
/*********************************************************************************************************************/

/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 3.1 (QAC message 0310)
 * Reason:       Casting to different object pointer type is used because function code need
 *               to be copied to RAM.
 * Verification: Copy destination is g_fdl_str.
 *              - This is re-initialized afterwards in R_FDL_Init
 *              - Copy size is limited by "sizeof"
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 11.3 (QAC message 0303, 0305, 0306)
 * Reason:       Casts between a pointer and other data types are used because function
 *               code need to be copied to RAM and finally a jump to RAM is done
 * Verification: None as complete system would crash if this does not work.
 *********************************************************************************************************************/

/********************************************************************************************************************
* MISRA Rule:   MISRA-C 2004 rule 3.1 (QAC message 0491)
* Reason:       Array subscripting applied to an object of pointer type required to copy data to
*               RAM location
* Verification: Check copy boundaries and address
*********************************************************************************************************************/

R_FDL_STATIC void R_FDL_IFct_ExeCodeInRAM (r_fdl_pFct_ExeInRAM pFct, uint32_t * param)
{
    uint32_t size,
             i,
             add,
             addAl;

    volatile uint16_t * pSrc;
    r_fdl_pFct_ExeInRAM pFctExe;

    /* volatile uint32_t uuu[0x13]; */ /* Just for test purpose (different stack alignment)*/

    /* Estimation of stack variable size:
       - Code size R_FDL_FCUFct_InitRAM_Asm: 154 Bytes (GHS/REC) + 4Bytes (IAR reg. conversion)
       - Code 1st address must be 16Byte aligned (fetch size): +16Bytes
       - Code last address must be 16Byte aligned (fetch size)
       - Prefetch: 1*16Byte
       --> 160Bytes (158Bytes aligned to 16Bytes) + 16Bytes + 16Bytes
           = 192Bytes = 96half words (=instruction alignment)
       - Code size R_FDL_IFct_GetFWParam_Asm: always less than R_FDL_FCUFct_InitRAM_Asm
    */

    volatile uint16_t ramCodeBuffer[96];

    /* Copy code to the 16byte aligned buffer address */
    add   = (uint32_t)(&ramCodeBuffer[0]);                                                          /* PRQA S 0303 */
    addAl = ( ( (add + 15uL) >> 4 ) << 4 );
    pSrc  = (uint16_t *)( (uint32_t)pFct - (addAl - add) );                                     /* PRQA S 0305, 0306 */
    size  = sizeof (ramCodeBuffer) >> 1;

    for (i = 0; i < size; i++)
    {
        ramCodeBuffer[i] = pSrc[i];                                                                 /* PRQA S 0491 */
    }

    pFctExe = (r_fdl_pFct_ExeInRAM)(addAl);                                                         /* PRQA S 0305 */

    /* Critical section start - disable all interrupts and exceptions */
    FDL_CRITICAL_SECTION_BEGIN
    /* Execute code in RAM */
    pFctExe (param);

    /* Critical section end - enable interrupts and exceptions again */
    FDL_CRITICAL_SECTION_END
} /* R_FDL_IFct_ExeCodeInRAM */


/*********************************************************************************************************************
 * Function name:  R_FDL_FCUFct_VerifyID
 *********************************************************************************************************************/
/**
 * Function to verify the given ID against the stored reference ID \n
 * The reference ID is tranferred to the ID check unit Depending on the comparison result, all further Flash 
 * operations will be accepted or rejected by the hardware.
 *
 * @param      descriptor_pstr         pointer to the descriptor
 * @return     --
 */
/*********************************************************************************************************************/
void R_FDL_FCUFct_VerifyID (const r_fdl_descriptor_t * descriptor_pstr)
{
    R_FDL_IFct_WriteMemoryU32 ( R_FCU_REGADD_AUTH_ID0_U32, (descriptor_pstr->id_au32[0]) );
    R_FDL_IFct_WriteMemoryU32 ( R_FCU_REGADD_AUTH_ID1_U32, (descriptor_pstr->id_au32[1]) );
    R_FDL_IFct_WriteMemoryU32 ( R_FCU_REGADD_AUTH_ID2_U32, (descriptor_pstr->id_au32[2]) );
    R_FDL_IFct_WriteMemoryU32 ( R_FCU_REGADD_AUTH_ID3_U32, (descriptor_pstr->id_au32[3]) );

    /* Dummy read because some devices have some cycles delay before verifying the ID (Review comments AT to 1E00a)*/
    (void)R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_AUTH_STAT_U32);
} /* R_FDL_FCUFct_VerifyID */




/*********************************************************************************************************************
 * Function name:  R_FDL_FCUFct_SwitchMode
 *********************************************************************************************************************/
/**
 * Switch FCU mode to Programming/User mode
 *
 * @param      mode - Mode (R_FCU_MODE_PE / R_FCU_MODE_CPE / R_FCU_MODE_USER)
 * @return     ---
 */
/*********************************************************************************************************************/
r_fdl_status_t R_FDL_FCUFct_SwitchMode (uint16_t mode)
{
    volatile uint16_t   regFENTRYR;
    uint32_t            regFSTATR;
    uint32_t            cmp;
    r_fdl_status_t      ret;

    if (R_FCU_MODE_USER == mode)
    {
        /* Clear FCU errors */
        regFSTATR = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSTATR_U32);
        cmp = R_FCU_REGBIT_FSTATR_ILGERR + R_FCU_REGBIT_FSTATR_ERSERR + R_FCU_REGBIT_FSTATR_PRGERR;
        if ( R_FCU_REGBIT_FSTATR_RESET != (regFSTATR & cmp) )
        {
            R_FDL_FCUFct_ClearStatus ();
        }
        R_FDL_IFct_WriteMemoryU16 (R_FCU_REGADD_FENTRYR_U16, mode + R_FCU_REGBIT_FENTRY_KEY);
    }
    else
    {
        /* Check if the mode is already set. If yes, setting it again would toggle the mode. So, don't set it again */
        regFENTRYR =  R_FDL_IFct_ReadMemoryU16 (R_FCU_REGADD_FENTRYR_U16);
        regFENTRYR &= (R_FCU_MODE_PE + R_FCU_MODE_CPE);
        if (mode != regFENTRYR)
        {
            R_FDL_IFct_WriteMemoryU16 (R_FCU_REGADD_FENTRYR_U16, mode + R_FCU_REGBIT_FENTRY_KEY);

            /* also clear FSADDRR and FEADDRR when entering P/E mode in order to allow access address
               checking by R_FDL_IFct_ChkAccessRight */
            R_FDL_IFct_WriteMemoryU32 (R_FCU_REGADD_FSADR_U32, 0x00000000uL);
            R_FDL_IFct_WriteMemoryU32 (R_FCU_REGADD_FEADR_U32, 0x00000000uL);
        }
    }

    /* Check if we could switch the mode (might be prevented e.g. by a security measure */
    /* We need a dummy read as the mode is not changed immediately on some devices */
    regFENTRYR =  R_FDL_IFct_ReadMemoryU16 (R_FCU_REGADD_FENTRYR_U16);
    regFENTRYR =  R_FDL_IFct_ReadMemoryU16 (R_FCU_REGADD_FENTRYR_U16);
    regFENTRYR &= (R_FCU_MODE_PE + R_FCU_MODE_CPE);
    if (mode != regFENTRYR)
    {
        ret = R_FDL_ERR_PROTECTION;
    }
    else
    {
        ret = R_FDL_OK;
    }

    #ifdef PATCH_TO_SIMULATE_ERRORS
        R_FDL_COV_SAVEOFF
        if ( (tstData_str.simError_enu == R_FDL_TRUE) &&
             (R_FDL_SIM_ERROR_SWITCH_PROT == tstData_str.simErrorType_enu) )
        {
            if (tstData_str.simErrorCntSet_u32 == tstData_str.simErrorCnt_u32)
            {
                ret = R_FDL_ERR_PROTECTION;
                tstData_str.simError_enu = R_FDL_FALSE;
            }
            tstData_str.simErrorCnt_u32++;
        }
        R_FDL_COV_RESTORE
    #endif /* ifdef PATCH_TO_SIMULATE_ERRORS */

    return (ret);
} /* R_FDL_FCUFct_SwitchMode */

/*********************************************************************************************************************
 * Function name:  R_FDL_FCUFct_GetStat
 *********************************************************************************************************************/
/**
 * Return FCU Flash operation result
 *
 * @param      ---
 * @return     Operation result:
 *             - R_FDL_ERR_BLANKCHECK
 *             - R_FDL_ERR_WRITE
 *             - R_FDL_ERR_ERASE
 *             - R_FDL_BUSY
 *             - R_FDL_OK
 */
/*********************************************************************************************************************/
r_fdl_status_t R_FDL_FCUFct_GetStat (void)
{
    r_fdl_status_t    stat;
    volatile uint32_t regFSTATR;
    volatile uint8_t  regFBCSTAT;

    /* For BC we need to check the command too because the bit cannot be reset after BC execution
       and so stays valid until next BC */
    regFBCSTAT = R_FDL_IFct_ReadMemoryU08 (R_FCU_REGADD_FBCSTAT_U08);
    #ifdef PATCH_TO_SIMULATE_ERRORS
        R_FDL_COV_SAVEOFF
        if ( (R_FDL_CMD_BLANKCHECK == g_fdl_str.reqInt_pstr->command_enu)
             && (tstData_str.simError_enu == R_FDL_TRUE) )
        {
            if (R_FDL_SIM_ERROR_BLANKCHECK == tstData_str.simErrorType_enu)
            {
                stat = R_FDL_ERR_BLANKCHECK;
                tstData_str.simError_enu = R_FDL_FALSE;
            }
        }
        R_FDL_COV_RESTORE
    #endif

    if ( (R_FCU_REGBIT_FBCSTAT_BCST == (regFBCSTAT & R_FCU_REGBIT_FBCSTAT_BCST) ) &&
         (R_FDL_CMD_BLANKCHECK == g_fdl_str.reqInt_pstr->command_enu) )
    {
        stat = R_FDL_ERR_BLANKCHECK;
        g_fdl_str.opFailAddr_u32 = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FPSADDR_U32);
    }
    else
    {
        regFSTATR = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSTATR_U32);

        #ifdef PATCH_TO_SIMULATE_ERRORS
            R_FDL_COV_SAVEOFF
            if (tstData_str.simError_enu == R_FDL_TRUE)
            {
                if ( R_FCU_REGBIT_FSTATR_PRGERR == (regFSTATR & R_FCU_REGBIT_FSTATR_PRGERR) )
                {
                    tstData_str.simErrorType_enu = R_FDL_SIM_ERROR_SWITCH_PROT;
                }

                switch (tstData_str.simErrorType_enu)
                {
                    case R_FDL_SIM_ERROR_ERASE:
                    {
                        regFSTATR |= R_FCU_REGBIT_FSTATR_ERSERR;
                        tstData_str.simError_enu = R_FDL_FALSE;
                        break;
                    }

                    case R_FDL_SIM_ERROR_WRITE:
                    {
                        regFSTATR |= R_FCU_REGBIT_FSTATR_PRGERR;
                        tstData_str.simError_enu = R_FDL_FALSE;
                        break;
                    }

                    default:
                    {
                        break;
                    }
                } /* switch */

            }
            R_FDL_COV_RESTORE
        #endif /* ifdef PATCH_TO_SIMULATE_ERRORS */

        if ( R_FCU_REGBIT_FSTATR_PRGERR == (regFSTATR & R_FCU_REGBIT_FSTATR_PRGERR) )
        {
            stat = R_FDL_ERR_WRITE;
        }
        else
        {
            if ( R_FCU_REGBIT_FSTATR_ERSERR == (regFSTATR & R_FCU_REGBIT_FSTATR_ERSERR) )
            {
                stat = R_FDL_ERR_ERASE;
            }
            else
            {
                if ( ( (R_FCU_REGBIT_FSTATR_PRGSPD == (regFSTATR & R_FCU_REGBIT_FSTATR_PRGSPD) ) &&
                        (R_FDL_CMD_WRITE == g_fdl_str.reqInt_pstr->command_enu) ) ||
                     ( (R_FCU_REGBIT_FSTATR_ERSSPD == (regFSTATR & R_FCU_REGBIT_FSTATR_ERSSPD) ) &&
                       (R_FDL_CMD_ERASE == g_fdl_str.reqInt_pstr->command_enu) ) )
                {
                    stat = R_FDL_BUSY;
                }
                else
                {
                    stat = R_FDL_OK;
                }
            }
        }
    }

    return (stat);
} /* R_FDL_FCUFct_GetStat */


/*********************************************************************************************************************
 * Function name:  R_FDL_FCUFct_StartWriteOperation
 *********************************************************************************************************************/
/**
 * This function configures the Flash programming sequencer and starts the operation
 *
 * @param[in]  addSrc  - source data address
 * @param[in]  addDest - EEP Flash write address, relative to EEP Flash base address
 * @param[in]  cnt     - Number of words to write. Allowed is 1 or 4 words
 * @param[in]  accType - User/EEL access (check of access rights)
 *
 * @return     Parameter check result:
 *             - R_FDL_BUSY
 *             - R_FDL_ERR_PROTECTION
 */
/*********************************************************************************************************************/
r_fdl_status_t R_FDL_FCUFct_StartWriteOperation (uint32_t addSrc,
                                                 uint32_t addDest,
                                                 uint32_t cnt,
                                                 r_fdl_accessType_t accType)
{
    volatile uint32_t regFSTATR;
    uint32_t          i;
    r_fdl_status_t    ret;
    uint16_t          data;

    R_FDL_IFct_WriteMemoryU32 (R_FCU_REGADD_FSADR_U32, addDest);

    /* We just write the end address to this register for the access rights check because the
       hardware does not store the write end address in a readable register
       Note: Writing the register is only possible before the write command is issued afterwards it is no longer possible*/
    R_FDL_IFct_WriteMemoryU32 ( R_FCU_REGADD_FEADR_U32, addDest + (cnt - 1uL) );

#ifdef R_FDL_TST_WA_F1L_RESETBLOCKING
    {
        uint32_t loop;
        EEL_ROBUSTNESSTEST_DISABLE_RESET
        for( loop = 0; loop < 10000; loop++ );
    }
#endif

    R_FDL_IFct_WriteMemoryU16 (R_FCU_DFLASH_CMD_ADD, R_FCU_CMD_WRITE);

    /* copy to FCU is 2 bytes at once */
    cnt /= R_FDL_FCU_DATA_TRANSFERSIZE;

    R_FDL_IFct_WriteMemoryU16 (R_FCU_DFLASH_CMD_ADD, (uint16_t)cnt);


    for (i = 0; i < cnt; ++i)
    {
        /* assume reading of unaligned source buffer */
        data = (uint16_t)R_FDL_IFct_ReadMemoryU08 (addSrc + 1);
        data <<= 8;
        data += (uint16_t)R_FDL_IFct_ReadMemoryU08 (addSrc);

        addSrc += 2;
        R_FDL_IFct_WriteMemoryU16 (R_FCU_DFLASH_CMD_ADD, data);

        do
        {
            regFSTATR = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSTATR_U32);
        }
        while ( R_FCU_REGBIT_FSTATR_DBFULL == (regFSTATR & R_FCU_REGBIT_FSTATR_DBFULL) );          /* CCOV 0005 */
    }

    ret = R_FDL_IFct_ChkAccessRight (accType, (cnt * R_FDL_FCU_DATA_TRANSFERSIZE));
    if (R_FDL_BUSY == ret)
    {
        R_FDL_IFct_WriteMemoryU16 (R_FCU_DFLASH_CMD_ADD, R_FCU_CMD_EXE);
    }

#ifdef R_FDL_TST_WA_F1L_RESETBLOCKING
    EEL_ROBUSTNESSTEST_ENABLE_RESET
#endif

    return (ret);
} /* R_FDL_FCUFct_StartWriteOperation */



/*********************************************************************************************************************
 * Function name:  R_FDL_FCUFct_StartBCEraseOperation
 *********************************************************************************************************************/
/**
 * This function configures the Flash programming sequencer and starts the operation
 *
 * @param  addStart - Start address (1st block address for erase, 1st address for BC)
 * @param  addEnd   - End address (last block address for erase, last address for BC)
 * @param  fcuCmd   - Type of command. Erase / BC
 * @param  accType  - User/EEL access (check of access rights)
 *
 * @return status of the operation to start
 *         - R_FDL_BUSY - operation started
 *         - R_FDL_ERR_PROTECTION - operation blocked due to protection
 */
/*********************************************************************************************************************/
r_fdl_status_t R_FDL_FCUFct_StartBCEraseOperation (uint32_t addStart,
                                                   uint32_t addEnd,
                                                   uint8_t fcuCmd,
                                                   r_fdl_accessType_t accType)
{
    r_fdl_status_t ret;

    R_FDL_IFct_WriteMemoryU32 (R_FCU_REGADD_FSADR_U32, addStart);
    R_FDL_IFct_WriteMemoryU32 (R_FCU_REGADD_FEADR_U32, addEnd);

    R_FDL_IFct_WriteMemoryU08 (R_FCU_DFLASH_CMD_ADD, fcuCmd);

    ret = R_FDL_IFct_ChkAccessRight (accType, R_FDL_WRITE_SIZE);
    if (R_FDL_BUSY == ret)
    {
        R_FDL_IFct_WriteMemoryU08 (R_FCU_DFLASH_CMD_ADD, R_FCU_CMD_EXE);
    }

    return (ret);
}



/*********************************************************************************************************************
 * Function name:  R_FDL_FCUFct_ReadOperation
 *********************************************************************************************************************/
/**
 * This function reads data from the Data Flash. Doing so, it disables the ECC error interrupts to
 * avoid interrupt generation on accepted ECC errors when reading e.g. blank or partly written
 * Flash words. Instead, the error and fail address is returned to the calling function.
 * Note: Detecting a single bit error does not stop reading the Data Flash. Instead, the error
 *       is returned together with the fail address and the user application / EEL can still
 *       judge if it trusts the data. If later on a double bit error is detected, the function
 *       stop reading the data and teh single bit error indication and address is overwritten
 *       with the double bit error indication and address
 *
 * @param[in/out]  pAddSrc - In: Data Flash src address (byte index) to read. \n
 *                           Out: In ECC error case the fail address is returned
 * @param[in]      addDest - destination buffer address
 * @param[in]      cnt - number of words to read
 *
 * @return     Parameter check result:
 *             - R_FDL_OK
 *             - R_FDL_ERR_ECC_SED (Single bit error detected during read)
 *             - R_FDL_ERR_ECC_DED (Double bit error detected during read)
 */
/*********************************************************************************************************************/
r_fdl_status_t R_FDL_FCUFct_ReadOperation (volatile uint32_t * pAddSrc, uint32_t addDest, uint32_t cnt)
{
    r_fdl_status_t ret;
    uint32_t       addEnd;
    uint32_t       add;
    uint32_t       data;
    uint8_t        regDFERINT;
    uint8_t        regDFERSTR;


    ret     = R_FDL_OK;
    add     = (*pAddSrc) + R_FCU_DFLASH_READ_ADD;
    addEnd  = add + (cnt * R_FDL_WRITE_SIZE);

    /* Clear ECC errors */
    R_FDL_IFct_WriteMemoryU08 (R_FCU_REGADD_DFERSTC_U08, R_FCU_REGBIT_DFERSTC_ERRCLR);

    /* Backup and Disable ECC error interrupts */
    regDFERINT = R_FDL_IFct_ReadMemoryU08 (R_FCU_REGADD_DFERINT_U08);
    R_FDL_IFct_WriteMemoryU08 (R_FCU_REGADD_DFERINT_U08, R_FCU_REGVAL_DFERINT_NOINT);

    do
    {
        data = R_FDL_IFct_ReadMemoryU32 (add);
        R_FDL_IFct_WriteMemoryU32 (addDest, data);

        regDFERSTR = R_FDL_IFct_ReadMemoryU08 (R_FCU_REGADD_DFERSTR_U08);
        #ifdef PATCH_TO_SIMULATE_ERRORS
            R_FDL_COV_SAVEOFF
            if (tstData_str.simError_enu == R_FDL_TRUE)
            {
                if (R_FDL_SIM_ERROR_BITCHECK == tstData_str.simErrorType_enu)
                {
                    if (2 == tstData_str.simErrorVal_u32)/*simulate double bit error*/
                    {
                        regDFERSTR |= R_FCU_REGBIT_DFERSTR_DEDF;
                        tstData_str.simError_enu = R_FDL_FALSE;
                    }
                    else /*simulate single bit error*/
                    {
                        regDFERSTR |= R_FCU_REGBIT_DFERSTR_SEDF;
                        tstData_str.simError_enu = R_FDL_FALSE;
                    }
                }
            }
            R_FDL_COV_RESTORE
        #endif


        if (R_FCU_REGVAL_DFERSTR_NOERR != regDFERSTR)
        {
            if ( R_FCU_REGBIT_DFERSTR_DEDF == (R_FCU_REGBIT_DFERSTR_DEDF & regDFERSTR) )
            {
                (*pAddSrc) = add - R_FCU_DFLASH_READ_ADD;
                ret = R_FDL_ERR_ECC_DED;
            }
            else
            /* On single bit error note first occurence address */
            {
                (*pAddSrc) = add - R_FCU_DFLASH_READ_ADD;
                ret = R_FDL_ERR_ECC_SED;
            }

            /* Clear ECC errors */
            R_FDL_IFct_WriteMemoryU08 (R_FCU_REGADD_DFERSTC_U08, R_FCU_REGBIT_DFERSTC_ERRCLR);
        }
        add += R_FDL_WRITE_SIZE;
        addDest += R_FDL_WRITE_SIZE;
    }
    while ( (add < addEnd) && (R_FDL_ERR_ECC_DED != ret) );

    /* Restore the ECC error interrupts */
    R_FDL_IFct_WriteMemoryU08 (R_FCU_REGADD_DFERINT_U08, regDFERINT);

    return (ret);
} /* R_FDL_FCUFct_ReadOperation */

/*********************************************************************************************************************
 * Function name:  R_FDL_FCUFct_ChkStartable
 *********************************************************************************************************************/
/**
 * function to check if write or erase may be started. BC or bit error check may always be started
 * so this test is not necessary there
 * - Erase may only start when no operation is suspended
 * - Write may only start if no write is suspended
 *
 * @param[in]  cmd - command to be executed (erase/write/BC)
 * @return     check result
 *             - R_FDL_TRUE  - Flash operation is startable
 *             - R_FDL_FALSE - Flash operation is not startable
 */
/*********************************************************************************************************************/
r_fdl_flag_t R_FDL_FCUFct_ChkStartable (r_fdl_command_t cmd)
{
    volatile uint32_t regFSTATR;
    r_fdl_flag_t      ret;

    ret = R_FDL_TRUE;

    regFSTATR = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSTATR_U32);

#if (defined ENABLE_CMD_WRITE16B)
    if ( (R_FDL_CMD_WRITE == cmd) || (R_FDL_CMD_WRITE16B == cmd) )
#else
    if (R_FDL_CMD_WRITE == cmd)
#endif
    {
        if ( 0x00000000uL != (regFSTATR & R_FCU_REGBIT_FSTATR_PRGSPD) )
        {
            ret = R_FDL_FALSE;
        }
    }
    else
    {
        /* for R_FDL_CMD_ERASE */
        if ( 0x00000000uL != ( regFSTATR & (R_FCU_REGBIT_FSTATR_ERSSPD + R_FCU_REGBIT_FSTATR_PRGSPD) ) )
        {
            ret = R_FDL_FALSE;
        }
    }

    return (ret);
} /* R_FDL_FCUFct_ChkStartable */



/*********************************************************************************************************************
 * Function name:  R_FDL_FCUFct_ChkSuspendable
 *********************************************************************************************************************/
/**
 * Checks if a Flash operation may be suspended. \n
 * A Flash operation may be suspeded if the SUSRDY bit in FSTATR is set
 *
 * @param      ---
 * @return     check result
 *             - R_FDL_TRUE  - Flash operation is suspendable
 *             - R_FDL_FALSE - Flash operation is not suspendable
 */
/*********************************************************************************************************************/
r_fdl_flag_t R_FDL_FCUFct_ChkSuspendable (void)
{
    volatile uint32_t regFSTATR;
    r_fdl_flag_t      ret;

    /* Check if the operation can be suspended */
    regFSTATR = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSTATR_U32);
    if ( R_FCU_REGBIT_FSTATR_SUSRDY == (regFSTATR & R_FCU_REGBIT_FSTATR_SUSRDY) )
    {
        ret = R_FDL_TRUE;
        #if (defined ENABLE_CMD_WRITE16B)
            if (R_FDL_CMD_WRITE16B == g_fdl_str.reqInt_pstr->command_enu)
            {
                ret = R_FDL_FALSE;
            }
        #endif
    }
    else
    {
        ret = R_FDL_FALSE;
    }

    return (ret);
} /* R_FDL_FCUFct_ChkSuspendable */


/*********************************************************************************************************************
 * Function name:  R_FDL_FCUFct_Suspend
 *********************************************************************************************************************/
/**
 * Suspends an ongoing Flash Flash operation
 *
 * @param      ---
 * @return     ---
 */
/*********************************************************************************************************************/
void R_FDL_FCUFct_Suspend (void)
{
    /* Suspend command */
    R_FDL_IFct_WriteMemoryU16 (R_FCU_DFLASH_CMD_ADD, R_FCU_CMD_SUSPEND);
}


/*********************************************************************************************************************
 * Function name:  R_FDL_FCUFct_ResumeChkNeed
 *********************************************************************************************************************/
/**
 * Checks if a formerly suspended Flash erase operation need to be resumed (not finished yet). \n
 * This is done by checking the PRGSPD and ERSSPD bits in FSTATR
 *
 * @param      ---
 * @return     check result
 *             - R_FDL_TRUE  - Need to resume
 *             - R_FDL_FALSE - Need no resume
 */
/*********************************************************************************************************************/
r_fdl_flag_t R_FDL_FCUFct_ResumeChkNeed (void)
{
    volatile uint32_t regFSTATR;
    r_fdl_flag_t      ret;

    regFSTATR = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSTATR_U32);
    if ( 0x00000000uL == ( regFSTATR & (R_FCU_REGBIT_FSTATR_PRGSPD + R_FCU_REGBIT_FSTATR_ERSSPD) ) )
    {
        ret = R_FDL_FALSE;
    }
    else
    {
        ret = R_FDL_TRUE;
    }

    return (ret);
}




/*********************************************************************************************************************
 * Function name:  R_FDL_FCUFct_Resume
 *********************************************************************************************************************/
/**
 * Resumes a formerly suspended Flash operation
 *
 * @param      ---
 * @return     ---
 */
/*********************************************************************************************************************/
void R_FDL_FCUFct_Resume (void)
{
    /* Resume command */
    R_FDL_IFct_WriteMemoryU16 (R_FCU_DFLASH_CMD_ADD, R_FCU_CMD_EXE);
}



/*********************************************************************************************************************
 * Function name:  R_FDL_FCUFct_ChkReady
 *********************************************************************************************************************/
/**
 * Returns sequencer busy/Ready status \n
 * Ready if FSTATR.FRDY = 1
 *
 * @param      ---
 * @return     Status of the sequencer
 *             - R_FDL_TRUE  - Sequencer is not busy with a Flash operation
 *             - R_FDL_FALSE - Sequencer is busy with a Flash operation
 */
/*********************************************************************************************************************/
r_fdl_flag_t R_FDL_FCUFct_ChkReady (void)
{
    r_fdl_flag_t      ret;
    volatile uint32_t regFSTATR;

    regFSTATR = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSTATR_U32);

    #ifdef PATCH_TO_SIMULATE_ERRORS
        R_FDL_COV_SAVEOFF
        if ( (tstData_str.simError_enu == R_FDL_TRUE) &&
             (R_FDL_SIM_FCU_TIMEOUT == tstData_str.simErrorType_enu) )
        {
            regFSTATR &= (~R_FCU_REGBIT_FSTATR_FRDY);
        }
        R_FDL_COV_RESTORE
    #endif

    if ( R_FCU_REGBIT_FSTATR_FRDY == (regFSTATR & R_FCU_REGBIT_FSTATR_FRDY) )
    {
        ret = R_FDL_TRUE;

    #ifdef PATCH_TO_SIMULATE_ERRORS
        R_FDL_COV_SAVEOFF
        if ( (tstData_str.simError_enu == R_FDL_TRUE) &&
             (tstData_str.simErrorType_enu == R_FDL_SIM_ERROR_FATALERROR) )
        {
            tstData_str.simErrorCnt_u32++;
        }
        R_FDL_COV_RESTORE
    #endif
    }
    else
    {
        ret = R_FDL_FALSE;
    }

    return (ret);
} /* R_FDL_FCUFct_ChkReady */



/*********************************************************************************************************************
 * Function name:  R_FDL_FCUFct_CheckFatalError
 *********************************************************************************************************************/
/**
 * Returns information if a fatal error occurred in the FCU (e.g. double bit ECC errors, FCU internal errors,
 * protection error ...).\n
 *
 * @param      ---
 * @return     check result
 *             - R_FDL_OK               - No fatal error in the FCU
 *             - R_FDL_ERR_PROTECTION   - Protection error caused by FHVE
 *             - R_FDL_ERR_INTERNAL     - Other fatal FCU errors
 */
/*********************************************************************************************************************/
r_fdl_status_t R_FDL_FCUFct_CheckFatalError (void)
{
    r_fdl_status_t    ret;
    volatile uint32_t regFSTATR;
    uint32_t          checkVal;

    regFSTATR = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSTATR_U32);

    #ifdef PATCH_TO_SIMULATE_ERRORS
        R_FDL_COV_SAVEOFF
        if (tstData_str.simError_enu == R_FDL_TRUE)
        {
            if (R_FDL_SIM_ERROR_FATALERROR == tstData_str.simErrorType_enu)
            {
                if ( (tstData_str.simErrorCntSet_u32 == 0)
                     || ( (tstData_str.simErrorCntSet_u32 != 0)
                          && (tstData_str.simErrorCntSet_u32 == tstData_str.simErrorCnt_u32) ) )
                {

                    while ( (regFSTATR & R_FCU_REGBIT_FSTATR_FRDY) != R_FCU_REGBIT_FSTATR_FRDY )
                    {
                        regFSTATR = R_FDL_IFct_ReadMemoryU32 (R_FCU_REGADD_FSTATR_U32);
                    }
                    regFSTATR |= ( (uint16_t)tstData_str.simErrorVal_u32 );
                    tstData_str.simError_enu = R_FDL_FALSE;
                }
            }
            else if (R_FDL_SIM_ERROR_FHVE == tstData_str.simErrorType_enu)
            {
                regFSTATR |= ( (uint16_t)tstData_str.simErrorVal_u32 );
                tstData_str.simError_enu = R_FDL_FALSE;
            }
        }
        R_FDL_COV_RESTORE
    #endif /* ifdef PATCH_TO_SIMULATE_ERRORS */

    ret = R_FDL_OK;
    checkVal = ( ( ( ( ( (R_FCU_REGBIT_FSTATR_FRCRCT
                          + R_FCU_REGBIT_FSTATR_FRDTCT)
                          + R_FCU_REGBIT_FSTATR_TBLDTCT )
                          + R_FCU_REGBIT_FSTATR_CFGDTCT )
                          + R_FCU_REGBIT_FSTATR_FCUERR )
                          + R_FCU_REGBIT_FSTATR_ILGERR )
                          + R_FCU_REGBIT_FSTATR_OTPDTCT );
                    
    if ( (checkVal & regFSTATR) != 0x00000000u )
    {
        ret = R_FDL_ERR_INTERNAL;
    }
    else
    {
        checkVal = R_FCU_REGBIT_FSTATR_FHVEERR;

        if ( (checkVal & regFSTATR) != 0x00000000u )
        {
            ret = R_FDL_ERR_PROTECTION;
        }
    }

    return (ret);
} /* R_FDL_FCUFct_CheckFatalError */

/*********************************************************************************************************************/
#define R_FDL_STOP_SEC_PUBLIC_CODE
#include "r_fdl_mem_map.h"                                                                          /* PRQA S 5087 */

#define R_FDL_STOP_SEC_CONST
#include "r_fdl_mem_map.h"                                                                          /* PRQA S 5087 */

/*********************************************************************************************************************/


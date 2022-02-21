#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_OFF 0292
#endif
/*********************************************************************************************************************
 * Library       : EEPROM Emulation Library for Renesas RH850 devices
 *
 * File Name     : $Source: r_eel_basic_fct.c $
 * Lib. Version  : $RH850_EEL_LIB_VERSION_T01: V2.01 $
 * Mod. Revision : $Revision: 1.35 $
 * Mod. Date     : $Date: 2017/02/07 09:12:14JST $
 * Device(s)     : RV40 Flash based RH850 microcontroller
 * Description   : EEL interface functions to FDL/FCL
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
 * MISRA Rule:   MISRA-C 2004 rule 21.1 (QAC message 3689)
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
 *  MISRA Rule:   - (QAC message 2814)
 *  Reason:       Possible dereference of NULL pointers:
 *                pointers to descriptor or internally assigned pointers are often used in the library for function
 *                data return and for global data access
 *  Verification: Parameter passing: only done to pass data to upper layer function variables. malfunction unreasonable
 *                Access to global variables: NULL pointer access unreasonable as the accessed pointers are assigned
 *                during EEL init or process start
 *********************************************************************************************************************/
#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_OFF 2814
    #pragma PRQA_MESSAGES_OFF 2824
#endif

/*********************************************************************************************************************
 * FDL header files include
 *********************************************************************************************************************/
#include "R_EEL_Global.h"

/*********************************************************************************************************************
 * Module global internal function prototypes
 *********************************************************************************************************************/
R_EEL_STATIC void               R_EEL_FDLIF_BitCheck (uint32_t add);
R_EEL_STATIC void               R_EEL_FDLIF_Erase (uint16_t blk);
R_EEL_STATIC r_eel_status_t     R_EEL_FDLIF_EraseResume (void);
R_EEL_STATIC r_fdl_status_t     R_EEL_FDLIF_Read (uint32_t add, uint32_t * const pBuf);
R_EEL_STATIC void               R_EEL_FDLIF_Write (const uint32_t src[],
                                                   uint32_t addDest,
                                                   uint16_t len);
R_EEL_STATIC void               R_EEL_FDLIF_WriteTag (uint32_t addDest);
R_EEL_STATIC r_fdl_status_t     R_EEL_FDLIF_BlankCheck (uint32_t * add,
                                                        uint16_t len);
R_EEL_STATIC uint16_t           R_EEL_Pfct_AdjustByteCnt_ExtFeatures (uint16_t byteCnt, uint16_t idx);
R_EEL_STATIC uint32_t           R_EEL_PFct_Calc_vBlkBaseAdd (uint16_t blk);
R_EEL_STATIC uint32_t           R_EEL_PFct_Calc_vBlkTopAdd (uint16_t blk);
R_EEL_STATIC uint32_t           R_EEL_PFct_Calc_vBlkDataAdd (uint16_t blk,
                                                             r_eel_blk_header_data_t off);
R_EEL_STATIC uint32_t           R_EEL_PFct_Calc_BlkFreeSpace (uint32_t wp, uint32_t rp);
R_EEL_STATIC uint32_t           R_EEL_PFct_CastU32Ptr2Add (uint32_t * const ptr);
R_EEL_STATIC uint32_t           R_EEL_PFct_ConvertTidx2RefAdd (uint32_t tIdx);
R_EEL_STATIC uint16_t           R_EEL_PFct_ConvertId2TIdxSorted (uint16_t id, const uint16_t pIdTab[][2], uint32_t cnt);
R_EEL_STATIC uint16_t           R_EEL_PFct_ConvertRefAdd2WIdx (uint32_t add);
R_EEL_STATIC r_eel_flag_t       R_EEL_PFct_Chk_DSInvalidated_InvFlg (uint32_t refAdd);
R_EEL_STATIC r_eel_status_t     R_EEL_PFct_Chk_DSInvalidated (uint32_t refAdd, uint16_t idx, r_eel_flag_t * invRet);
R_EEL_STATIC uint32_t           R_EEL_PFct_Get_RefAdd2DataAdd (uint32_t refAdd);
R_EEL_STATIC uint32_t           R_EEL_PFct_Get_RefAdd2DataAdd_Rel (uint32_t refAdd);
R_EEL_STATIC uint16_t           R_EEL_PFct_Get_RefAdd2ID (uint32_t refAdd);
R_EEL_STATIC void               R_EEL_PFct_PrepLoopLimitReset (void);
R_EEL_STATIC uint32_t           R_EEL_PFct_Calc_BlockRWP (uint16_t blk);
R_EEL_STATIC uint32_t           R_EEL_PFct_Calc_BlockEC (uint16_t blk);
R_EEL_STATIC r_eel_status_t     R_EEL_PFct_Chk_EELPoolSpaceForDS (uint16_t dsLen, r_eel_process_id_t pId);
R_EEL_STATIC uint32_t           R_EEL_PFct_ReadDFlashU32 (uint32_t add);
R_EEL_STATIC uint8_t            R_EEL_PFct_ReadDataFromAddU08 (uint32_t add);
R_EEL_STATIC uint16_t           R_EEL_PFct_Calc_Add2vBlk (uint32_t add);
R_EEL_STATIC r_eel_status_t     R_EEL_PFct_BlankCheckDFlash (uint32_t * add,
                                                             uint32_t len,
                                                             r_eel_bcResult_t * bc);
R_EEL_STATIC uint32_t           R_EEL_PFct_Read_BlkHeaderData24bit (uint16_t blk,
                                                                    r_eel_blk_header_data_t offset);
R_EEL_STATIC r_eel_status_t     R_EEL_PFct_ReadDFlash_cmpPat (uint32_t add, r_eel_patcmp_t * pRes);
R_EEL_STATIC r_eel_status_t     R_EEL_PFct_ReadDFlash_cmpPatBC (uint32_t add,
                                                                r_eel_patcmp_t * pCmpRes);
R_EEL_STATIC r_eel_status_t     R_EEL_PFct_ReadDFlash_BCcmpPat (uint32_t add,
                                                                r_eel_patcmp_t * pCmpRes,
                                                                r_eel_bcResult_t * pBc);
R_EEL_STATIC uint32_t           R_EEL_PFct_RoundUpToWriteGranularity (uint32_t data);
R_EEL_STATIC uint16_t           R_EEL_SFct_Calc_NextBlk_Any (uint16_t curBlk,
                                                             r_eel_blockoffset_t blkOffset);
R_EEL_STATIC r_eel_operation_id_t R_EEL_SFct_ConvertProcessID2CommandNo (r_eel_process_id_t pId);
R_EEL_STATIC r_eel_flag_t       R_EEL_SFct_ChkBlockElder (uint16_t blk1, uint16_t blk2);
R_EEL_STATIC r_eel_status_t     R_EEL_SFct_Chk_DSValid (uint32_t refAdd,
                                                        r_eel_chk_ds_t * pChkDS);
R_EEL_STATIC r_eel_status_t     R_EEL_SFct_FlashConvertWriteStatus2ProcessStatus (void);
R_EEL_STATIC r_eel_flash_error_chk_t R_EEL_SFct_FlashOpResultCheck_Write (r_eel_flag_t ignFlashError);
R_EEL_STATIC r_eel_status_t     R_EEL_SFct_FlashConvertEraseStatus2ProcessStatus (void);
R_EEL_STATIC r_eel_status_t     R_EEL_SFct_FlashConvertBitCheckStat2ProcessStat (void);
R_EEL_STATIC r_eel_status_t     R_EEL_SFct_FlashOpResultCheck_BitCheck (void);
R_EEL_STATIC r_eel_flag_t       R_EEL_SFct_ForwardRpWp_DSWrite (uint16_t * actBlk,
                                                                uint32_t * actBlkRwp,
                                                                uint32_t byteCntRU);
R_EEL_STATIC void               R_EEL_SFct_ForwardSUPVProcessState (r_eel_pfct pfct);
R_EEL_STATIC r_eel_blockstatus_t R_EEL_SFct_Calc_BlkStat (uint16_t blk);
R_EEL_STATIC r_eel_err_flg_t    R_EEL_SFct_Calc_NextBlk_DedicatedStatus (uint16_t * addBlk,
                                                                         r_eel_blockstatus_t blkStatOK,
                                                                         r_eel_blockstatus_t blkStatErr,
                                                                         uint16_t searchBlkLimit,
                                                                         r_eel_blockoffset_t blkOff);
R_EEL_STATIC void               R_EEL_SFct_Init_BlkStatCnt (void);
R_EEL_STATIC r_eel_err_flg_t    R_EEL_SFct_ErrStatCheckError_CurProc (void);
R_EEL_STATIC r_eel_status_t     R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (r_eel_status_t stat);
R_EEL_STATIC void               R_EEL_SFct_Read_Chk_Data (uint32_t * pSrcAdd,
                                                          uint32_t destAdd,
                                                          uint32_t cntBytes,
                                                          r_eel_flag_t chk,
                                                          r_eel_err_flg_t * pChkRes);
R_EEL_STATIC r_eel_status_t     R_EEL_SFct_Supv_Run (void);
R_EEL_STATIC uint32_t           R_EEL_SFct_SetChecksum_8Bit_from_24bit (uint32_t data);
R_EEL_STATIC void               R_EEL_SFct_Refresh_StartProcess (void);
R_EEL_STATIC r_eel_status_t     R_EEL_SFct_Get_RefAdd_2_DSLen_LimMode (uint32_t refAdd, uint16_t * dsSizeRet);
R_EEL_STATIC void               R_EEL_SFct_SearchDS (uint32_t rp,
                                                     uint16_t id,
                                                     r_eel_searchds_t searchType,
                                                     uint32_t * pREFAdd);
R_EEL_STATIC r_eel_status_t     R_EEL_SFct_FindValidDS (uint16_t tIdx,
                                                        uint16_t ID,
                                                        uint32_t * pRefAdd);
R_EEL_STATIC r_eel_status_t R_EEL_SFct_FindValidDS_NoIdxTab (uint16_t ID,
                                                             uint32_t * pRefAdd);
R_EEL_STATIC void               R_EEL_SFct_SetBlkStat (uint16_t blk, r_eel_blockstatus_t stat);
R_EEL_STATIC void               R_EEL_SFct_Prepare_StartProcess (uint16_t blk);
R_EEL_STATIC void               R_EEL_SFct_SetActive_StartProcess (r_eel_pfct okRet,
                                                                   r_eel_pfct errRet,
                                                                   uint16_t setActBlk,
                                                                   uint32_t setActRp);
R_EEL_STATIC void               R_EEL_SFct_SetInvalid_StartProcess (r_eel_pfct okRet,
                                                                    r_eel_pfct errRet,
                                                                    uint16_t setInvBlk);
R_EEL_STATIC r_eel_status_t     R_EEL_SFct_Supv_Judge_Blk_Stat (uint16_t * actBlk,
                                                                uint32_t * actBlkEC,
                                                                uint16_t blk,
                                                                r_eel_flag_t * pMrkInv);
R_EEL_STATIC r_eel_status_t     R_EEL_SFct_Supv_Ensure_DS_Margin (void);
R_EEL_STATIC r_eel_flag_t       R_EEL_SFct_Write_UpdateRpWp (uint16_t * actBlk,
                                                             uint32_t * actBlkRwp);
R_EEL_STATIC void               R_EEL_SFct_Write_UpdateIDXTable (void);
R_EEL_STATIC void               R_EEL_SM_Format_Finish (void);
R_EEL_STATIC void               R_EEL_SM_Format_NextBlock (void);
R_EEL_STATIC void               R_EEL_SM_Prepare_Chk_Erase_Result (void);
R_EEL_STATIC void               R_EEL_SM_Prepare_Finish (void);
R_EEL_STATIC void               R_EEL_SM_Prepare_SetPrep_WriteEC (void);
R_EEL_STATIC void               R_EEL_SM_Prepare_SetPrep_WriteP (void);
R_EEL_STATIC void               R_EEL_SM_Prepare_Start (void);
R_EEL_STATIC void               R_EEL_SM_Prepare_Wait_Finish (void);
R_EEL_STATIC void               R_EEL_SM_Refresh_Start (void);
R_EEL_STATIC void               R_EEL_SM_Refresh_Finish (void);
R_EEL_STATIC void               R_EEL_SM_Set_Active_A0 (void);
R_EEL_STATIC void               R_EEL_SM_Set_Active_A1 (void);
R_EEL_STATIC void               R_EEL_SM_Set_Active_WaitEnd (void);
R_EEL_STATIC void               R_EEL_SM_Set_Active_End (void);
R_EEL_STATIC void               R_EEL_SM_Set_Active_RWP (void);
R_EEL_STATIC void               R_EEL_SM_Set_Invalid_WaitEnd (void);
R_EEL_STATIC void               R_EEL_SM_Set_Invalid_End (void);
R_EEL_STATIC void               R_EEL_SM_Set_Invalid_I0 (void);
R_EEL_STATIC void               R_EEL_SM_Set_Invalid_I1 (void);
R_EEL_STATIC void               R_EEL_SM_SUPV_Get_Blk_Stat1 (void);
R_EEL_STATIC void               R_EEL_SM_SUPV_Get_Blk_Stat2 (void);
R_EEL_STATIC void               R_EEL_SM_SUPV_Chk_Blk_Consistency (void);
R_EEL_STATIC void               R_EEL_SM_SUPV_Chk_Pool_Full (void);
R_EEL_STATIC void               R_EEL_SM_SUPV_Get_Pointers (void);
R_EEL_STATIC void               R_EEL_SM_SUPV_Get_Ram_Table (void);
R_EEL_STATIC void               R_EEL_SM_Write_Data (void);
R_EEL_STATIC void               R_EEL_SM_Write_DRP (void);
#ifdef R_EEL_SUPPORT_EXT_FEATURES
    R_EEL_STATIC void               R_EEL_SM_Write_WriteCnt (void);
    R_EEL_STATIC void               R_EEL_SM_Write_FastInvalidate (void);
    R_EEL_STATIC void               R_EEL_SM_Write_SafeInvalidate (void);
#endif
R_EEL_STATIC void               R_EEL_SM_Write_CmpData (void);
R_EEL_STATIC void               R_EEL_SM_Write_EOR0 (void);
R_EEL_STATIC void               R_EEL_SM_Write_EOR1 (void);
R_EEL_STATIC void               R_EEL_SM_Write_Finish (void);
R_EEL_STATIC void               R_EEL_SM_Write_SetActiveError (void);
R_EEL_STATIC void               R_EEL_SM_Write_SOR (void);
R_EEL_STATIC void               R_EEL_SM_Write_Wait_Finish (void);



/*********************************************************************************************************************
 * Compiler specific section defines
 *********************************************************************************************************************/
#define R_EEL_START_SEC_PUBLIC_CODE
#include "r_eel_mem_map.h"                                                                          /* PRQA S 5087 */


/*********************************************************************************************************************
 *********************************************************************************************************************
 * FDL access functions
 *********************************************************************************************************************
 *********************************************************************************************************************/


/*********************************************************************************************************************
 * Function name:  R_EEL_FDLIF_BlankCheck
 *********************************************************************************************************************/
/**
 * Function to check if Data Flash words are blank by accessing the FDL API
 *
 * @param[in/out]  add - data source address. Returns the BC fail address on BC fail
 * @param[in]      len - number of words
 *
 * @return         Blank check result
 *                 - R_FDL_OK              (checked address range is blank)
 *                 - R_FDL_ERR_BLANKCHECK  (checked address range is not blank
 *                                          furthermore, the fail address is returned)
 *                 - R_FDL_ERR_INTERNAL    (internal hardware related error (timeout) during blank
 *                                          check)
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_fdl_status_t R_EEL_FDLIF_BlankCheck (uint32_t * add, uint16_t len)
{
    r_fdl_status_t  ret;
    uint32_t        cnt;
    r_fdl_request_t rs;

#ifdef R_EEL_DEBUG_BASICINFO
        R_FDL_COV_SAVEOFF;
        if (g_eel_str.BCCnt_u16 < 0xFFFF)
        {
            g_eel_str.BCCnt_u16++;
        }
        R_FDL_COV_RESTORE;
#endif

    rs.command_enu      = R_FDL_CMD_BLANKCHECK;
    rs.idx_u32          = (*add) - R_FCU_DFLASH_READ_ADD;
    rs.cnt_u16          = len;
    rs.accessType_enu   = R_FDL_ACCESS_EEL;

    R_FDL_Execute (&rs);

    cnt = R_EEL_BC_CNT_TIMEOUT;
    do
    {
        /* We set the timeout high as we need just an exit condition for fatal errors. If
           concrete timeout check is required, the user application need to do the check.
           Measured ~2.4s @ 48MHz on R_EEL_BC_CNT_TIMEOUT is set to 400k */
        R_FDL_Handler ();
        cnt--;
    }
    while ( (cnt > 0uL) &&
            (R_FDL_BUSY == rs.status_enu) );

    /* On timeout or any result != OK/BlankCheck error we return internal error */
    if ( (cnt == 0uL) ||
         ( (R_FDL_OK != rs.status_enu) && (R_FDL_ERR_BLANKCHECK != rs.status_enu) ) )
    {
        ret = R_FDL_ERR_INTERNAL;
    }
    else
    {
        ret = rs.status_enu;
        if (R_FDL_ERR_BLANKCHECK == rs.status_enu)
        {
            *add = (rs.idx_u32 + R_FCU_DFLASH_READ_ADD);
        }
    }

    return (ret);
} /* R_EEL_FDLIF_BlankCheck */


/*********************************************************************************************************************
 * Function name:  R_EEL_FDLIF_Read
 *********************************************************************************************************************/
/**
 * Reads a 32-bit data value from the given Data Flash address by using FDL
 *
 * @param[in]  add - address to read
 * @param[out] pBuf - pointer to result buffer
 * @return     R_FDL_OK             - Read operation passed, no ECC error
 *             R_FDL_ERR_ECC_SED    - Read operation passed, single bit ECC error
 *             R_FDL_ERR_ECC_DED    - Read operation passed, double bit ECC error
 *             R_FDL_ERR_INTERNAL   - Error return from the under-laying FDL other than the expected SED, DED
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_fdl_status_t R_EEL_FDLIF_Read (uint32_t add, uint32_t * const pBuf)
{
    r_fdl_status_t  ret;
    r_fdl_request_t rs;

    /* Call the FDL read check operation */
    rs.command_enu     = R_FDL_CMD_READ;
    rs.bufAddr_u32     = R_EEL_PFct_CastU32Ptr2Add (pBuf);
    rs.idx_u32         = (add - R_FCU_DFLASH_READ_ADD);
    rs.cnt_u16         = 1u;
    rs.accessType_enu  = R_FDL_ACCESS_EEL;

    R_FDL_Execute ( &(rs) );

    if ( (R_FDL_OK == rs.status_enu) ||
         ( (R_FDL_ERR_ECC_SED == rs.status_enu) ||
           (R_FDL_ERR_ECC_DED == rs.status_enu) ) )
    {
        ret = rs.status_enu;
    }
    else
    {
        ret = R_FDL_ERR_INTERNAL;
    }

    return (ret);
} /* R_EEL_FDLIF_Read */






/*********************************************************************************************************************
   Function name:  R_EEL_FDLIF_Write
 *********************************************************************************************************************/
/**
 * Function to write data words in Flash by accessing the FDL API
 *
 * The data variable must be static as the write operation might not immediately be started
 * inside the FDL and so, we need to preserve the data
 *
 * Note: Global data buffer is required as the data must remain even when the function is left
 *       because possibly the Flash operation is not yet started and the buffer data is
 *       transferred to the Flash later on by the FDL Handler function
 *
 * @param[in]      src     - data source address
 * @param[in]      addDest - Flash destination address (Data Flash base address = 0)
 * @param[in]      len     - number of words to write
 *
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_FDLIF_Write (const uint32_t src[],
                                     uint32_t addDest,
                                     uint16_t len)
{
    uint32_t i;

    /* Fill the global data buffer for the write operation */
    for (i = 0; i < len; i++)
    {
        g_eel_str.dataBuffer[i] = src[i];
    }
    /* Call the library write operation */
    g_eel_str.fdlReqWrite_str.command_enu     = R_FDL_CMD_WRITE;
    g_eel_str.fdlReqWrite_str.bufAddr_u32     = R_EEL_PFct_CastU32Ptr2Add (&g_eel_str.dataBuffer[0]);
    g_eel_str.fdlReqWrite_str.idx_u32         = (addDest - R_FCU_DFLASH_READ_ADD);
    g_eel_str.fdlReqWrite_str.cnt_u16         = len;
    g_eel_str.fdlReqWrite_str.accessType_enu  = R_FDL_ACCESS_EEL;

    R_FDL_Execute ( &(g_eel_str.fdlReqWrite_str) );

    g_eel_str.pCurP_pstr->flashStatus_enu = g_eel_str.fdlReqWrite_str.status_enu;

    return;
} /* R_EEL_FDLIF_Write */


/*********************************************************************************************************************
 * Function name:  R_EEL_FDLIF_WriteTag
 *********************************************************************************************************************/
/**
 * Function to write the special valid pattern to the Flash by accessing the FDL API
 *
 * The data variable must be static as the write operation might not immediately be started
 * inside the FDL and so, we need to preserve the data
 *
 * Note: Global data buffer is required as the data must remain even when the function is left
 *       because possibly the Flash operation is not yet started and the buffer data is
 *       transferred to the Flash later on by the FDL Handler function
 *
 * @param[in]      addDest - Flash destination address (Data Flash base address = 0)
 *
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_FDLIF_WriteTag (uint32_t addDest)
{
    g_eel_str.dataBuffer[0] = R_EEL_PATTERN_VALID;

    R_EEL_FDLIF_Write (&(g_eel_str.dataBuffer[0]), addDest, 1);

    return;
}

/*********************************************************************************************************************
 * Function name:  R_EEL_FDLIF_EraseSuspendRequest
 *********************************************************************************************************************/
/**
 * Function to request the Flash erase suspend
 *
 * @param[in]      ---
 *
 * @return       Resume result
 *               - R_EEL_OK
 *               - R_EEL_ERR_INTERNAL    (Resume was not successful)
 */
/*********************************************************************************************************************/
r_eel_status_t R_EEL_FDLIF_EraseSuspendRequest (void)
{
    r_fdl_status_t res;
    r_eel_status_t ret;

    res = R_FDL_SuspendRequest ();

    if (R_FDL_OK == res)
    {
        ret = R_EEL_BUSY;
    }
    else
    {
        ret = R_EEL_ERR_INTERNAL;
    }

    return (ret);
} /* R_EEL_FDLIF_EraseSuspendRequest */


/*********************************************************************************************************************
 * Function name:  R_EEL_FDLIF_EraseResume
 *********************************************************************************************************************/
/**
 * Function to resume the suspended erase.
 *
 * @param[in]      ---
 *
 * @return       Resume result
 *               - R_EEL_OK
 *               - R_EEL_ERR_INTERNAL    (Resume was not successful)
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_status_t R_EEL_FDLIF_EraseResume (void)
{
    r_fdl_status_t res;
    r_eel_status_t ret;

    res = R_FDL_ResumeRequest ();

    if (R_FDL_OK == res)
    {
        ret = R_EEL_OK;
    }
    else
    {
        ret = R_EEL_ERR_INTERNAL;
    }

    return (ret);
} /* R_EEL_FDLIF_EraseResume */


/*********************************************************************************************************************
 * Function name:  R_EEL_FDLIF_Erase
 *********************************************************************************************************************/
/**
 * Function to erase a single virtual Flash block by accessing the FDL API
 *
 * @param[in]      blk - virtual Flash block number to erase
 *
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_FDLIF_Erase (uint16_t blk)
{
    /* Call the FDL erase operation */
    g_eel_str.fdlReqErase_str.command_enu     = R_FDL_CMD_ERASE;
    g_eel_str.fdlReqErase_str.idx_u32         = (uint32_t)( g_fdl_str.RTCfg_pstr->eelPoolStart_u16 +
                                                            (blk * g_eel_str.RTCfg_pstr->vBlkSize_u16) );
    g_eel_str.fdlReqErase_str.cnt_u16         = g_eel_str.RTCfg_pstr->vBlkSize_u16;
    g_eel_str.fdlReqErase_str.accessType_enu  = R_FDL_ACCESS_EEL;

    R_FDL_Execute ( &(g_eel_str.fdlReqErase_str) );

    g_eel_str.sm_str[R_EEL_PR_PR].flashStatus_enu = g_eel_str.fdlReqErase_str.status_enu;

    return;
}



/*********************************************************************************************************************
 * Function name:  R_EEL_FDLIF_BitCheck
 *********************************************************************************************************************/
/**
 * Function to check bit error of a single Flash word by accessing the FDL API
 *
 * @param[in]      add - Flash address to check
 *
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_FDLIF_BitCheck (uint32_t add)
{
    r_fdl_status_t res;
    uint32_t       data,
                   addTmp;


    /* Only non blank cells are to be checked */
    data = 0;   /* Avoids MISRA complaints for uninitialized variables*/
    addTmp = add;
    res = R_EEL_FDLIF_BlankCheck (&addTmp, 1u);
    if (R_FDL_ERR_BLANKCHECK == res)
    {
        /* Call the FDL bit check operation */
        g_eel_str.fdlReqWrite_str.command_enu     = R_FDL_CMD_READ;
        g_eel_str.fdlReqWrite_str.bufAddr_u32     = R_EEL_PFct_CastU32Ptr2Add (&data);
        g_eel_str.fdlReqWrite_str.idx_u32         = (add - R_FCU_DFLASH_READ_ADD);
        g_eel_str.fdlReqWrite_str.cnt_u16         = 1u;
        g_eel_str.fdlReqWrite_str.accessType_enu  = R_FDL_ACCESS_EEL;

        R_FDL_Execute ( &(g_eel_str.fdlReqWrite_str) );
    }
    else
    {
        g_eel_str.fdlReqWrite_str.status_enu = res;
    }

    g_eel_str.sm_str[R_EEL_PR_SV].flashStatus_enu = g_eel_str.fdlReqWrite_str.status_enu;           /* PRQA S 3689 */

    return;
} /* R_EEL_FDLIF_BitCheck */


/*********************************************************************************************************************
 * Function name:  R_EEL_FDLIF_Handler
 *********************************************************************************************************************/
/**
 * Function to call the FDL handler function to forward the Flash operation.
 *
 * @param[in]      ---
 * @return         FDL Handler call result
 *                 - R_FDL_BUSY
 *                 - R_FDL_ERR_PROTECTION
 *                 - R_FDL_ERR_WRITE
 *                 - R_FDL_ERR_ERASE
 *                 - R_FDL_ERR_INTERNAL
 */
/*********************************************************************************************************************/
r_fdl_status_t R_EEL_FDLIF_Handler (void)
{
    r_fdl_status_t ret;

    ret = R_FDL_BUSY;

    /* 1st check Flash write status as this has a higher priority */
    if (R_FDL_BUSY == g_eel_str.fdlReqWrite_str.status_enu)
    {
        R_FDL_Handler ();
        ret = g_eel_str.fdlReqWrite_str.status_enu;
    }
    else
    {
        /* 2nd check Flash erase status with lower priority.
           A suspended erase must be handled also in order to possibly resume */
        if ( (R_FDL_BUSY      == g_eel_str.fdlReqErase_str.status_enu) ||
             (R_FDL_SUSPENDED == g_eel_str.fdlReqErase_str.status_enu) )
        {
            R_FDL_Handler ();
            ret = g_eel_str.fdlReqErase_str.status_enu;
        }
    }

    return (ret);
} /* R_EEL_FDLIF_Handler */


/*********************************************************************************************************************
 *********************************************************************************************************************
 * Primitive functions
 *********************************************************************************************************************
 *********************************************************************************************************************/


/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_CastU32Ptr2Add
 *********************************************************************************************************************/
/**
 * Casts a 32-bit pointer to an address.
 *
 * @param[in]  ptr - pointer to cast
 * @return     casted address value
 */
/*********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 11.3 (QAC message 0306)
 * Reason:       For effective embedded programming, integer to pointer conversions are used
 * Verification: The converted addresses are essential for complete code execution. Incorrect
 *               conversion would result in test fails.
 *********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 16.7 (QAC message 3673)
 * Reason:       For effective embedded programming, integer to pointer conversions are used
 * Verification: QAC claims that the pointed object is const. Although true for this function, the object will be
 *               modified using the casted address in the upper layer function. So the object is modified indirectly.
 *               As this is not detected by QAC, we consider the object as not const here
 *********************************************************************************************************************/
R_EEL_STATIC uint32_t R_EEL_PFct_CastU32Ptr2Add (uint32_t * const ptr)          /* PRQA S 3673 */
{
    return ( (uint32_t)ptr );                                                   /* PRQA S 0306 */
}


/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_CastU08Ptr2Add
 *********************************************************************************************************************/
/**
 * Casts a 8-bit pointer to a pointer to an address.
 *
 * @param[in]  ptr - pointer to cast
 * @return     casted address value
 */
/*********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 11.3 (QAC message 0306)
 * Reason:       For effective embedded programming, integer to pointer conversions are used
 * Verification: The converted addresses are essential for complete code execution. Incorrect
 *              conversion would result in test fails.
 *********************************************************************************************************************/
uint32_t R_EEL_PFct_CastU08Ptr2Add (const uint8_t * ptr)
{
    return ( (uint32_t)ptr );                                                      /* PRQA S 0306 */
}


/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_ReadDFlashU32
 *********************************************************************************************************************/
/**
 * Reads a 32-bit data value from the given Data Flash address.
 *
 * @param[in]  add - address to read
 * @return     32bit read data
 */
/*********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 11.3 (QAC message 0306)
 * Reason:       For effective embedded programming, integer to pointer conversions are used
 * Verification: The converted addresses are essential for complete code execution. Incorrect
 *              conversion would result in test fails.
 *********************************************************************************************************************/
R_EEL_STATIC uint32_t R_EEL_PFct_ReadDFlashU32 (uint32_t add)
{
    uint32_t ret;

    /* Flash address range check */
    if ( (add >= R_FCU_DFLASH_READ_ADD) &&
         ( add < (g_fdl_str.dfSize_u32 + R_FCU_DFLASH_READ_ADD) ) )
    {
        ret = (*(uint32_t *)add);                                             /* PRQA S 0306 */
    }
    else
    {
        ret = 0x00000000uL;
    }

    return (ret);

} /* R_EEL_PFct_ReadDFlashU32 */



/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_BlankCheckDFlash
 *********************************************************************************************************************/
/**
 * function to blank check a certain Data Flash range.
 * On internal error during blank check, the process error is updated and the function returns an
 * internal error.
 *
 * @param[in, out] add - Blank Check start address, returns BC fail address
 * @param[in]      len - Number of HW to check
 * @param[out]     bc  - Return of Flash status (R_EEL_BC_BLANK/R_EEL_BC_WRITTEN)
 *
 * @return         Blank check operation execution status
 *                 - R_EEL_OK (Blank check was executed successfully)
 *                 - R_EEL_ERR_INTERNAL (Internal HW error during blank check (part of read))
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_status_t R_EEL_PFct_BlankCheckDFlash (uint32_t * add, uint32_t len, r_eel_bcResult_t * bc)
{
    r_fdl_status_t bcRet;
    r_eel_status_t ret;

    bcRet = R_EEL_FDLIF_BlankCheck (add, (uint16_t)len);

    if (R_FDL_ERR_INTERNAL == bcRet)
    {
        ret = R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (R_EEL_ERR_INTERNAL);
    }
    else
    {
        ret = R_EEL_OK;

        if (R_FDL_ERR_BLANKCHECK == bcRet)
        {
            *bc    = R_EEL_BC_WRITTEN;
        }
        else
        {
            *bc = R_EEL_BC_BLANK;
        }
    }

    return (ret);
} /* R_EEL_PFct_BlankCheckDFlash */



/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_ReadDFlash_cmpPat
 *********************************************************************************************************************/
/**
 * Reads a 32-bit data value from the given Data Flash address by using FDL and compare it against reference data
 * In case of ECC DED error, the value R_EEL_PATCMP_INVALID is returned
 *
 * @param[in]  add - address to read
 * @param[out] pRes - pointer to compare result buffer
               R_EEL_PATCMP_VALID   - Pattern matches
 *             R_EEL_PATCMP_INVALID - Pattern does not match
 *             R_EEL_PATCMP_BLANK   - Blank value pattern matches
 * @return     R_EEL_OK             - The check could be executed
               R_EEL_ERR_INTERNAL   - Error return from the under-laying FDL other than the expected SED, DED
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_status_t R_EEL_PFct_ReadDFlash_cmpPat (uint32_t add, r_eel_patcmp_t * pRes)
{
    r_eel_status_t iErr;
    r_fdl_status_t readRes;
    r_eel_patcmp_t res;
    uint32_t       data;

    /* Default values */
    res  = R_EEL_PATCMP_INVALID;
    data = 0;   /* Avoids MISRA complaints for uninitialized variables*/
    iErr = R_EEL_OK;

    readRes = R_EEL_FDLIF_Read (add, &data);
    if (R_FDL_ERR_INTERNAL == readRes)
    {
        iErr = R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (R_EEL_ERR_INTERNAL);
    }
    else if (R_FDL_ERR_ECC_DED == readRes)
    {
        /* do nothing, default result */
    }
    else /* R_EEL_OK or R_FDL_ERR_ECC_SED */
    {
        if (R_EEL_PATTERN_VALID == data)
        {
            res = R_EEL_PATCMP_VALID;
        }
        else if (R_EEL_PATTERN_BLANK_WD == data)
        {
            res = R_EEL_PATCMP_BLANK;
        }
        else
        {
            /* do nothing, default result */
        }
    }

    *pRes = res;

    return (iErr);
} /* R_EEL_PFct_ReadDFlash_cmpPat */




/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_ReadDFlash_cmpPatBC
 *********************************************************************************************************************/
/**
 * Function to read 1 word data from Data Flash and compare it with the valid pattern.
 * If valid, it could result from blank Flash. So, also a blank check is done.
 * As read is much faster than blank check, the read is done first and the blank check is done
 * only on matching pattern.
 * On internal error during blank check, the process error is updated and the function returns an
 * internal error.
 *
 * Furthermore, on internal error, the process status is updated to
 * R_EEL_ERR_INTERNAL by the functions to read from Flash and blank check.
 *
 * @param[in]      add    - Data Read address
 * @param[out]     pMatch - Pattern match result (R_EEL_TRUE, R_EEL_FALSE)
 *                          R_EEL_TRUE only if pattern matches and the data is written
 *
 * @return         Flash read operation execution status
 *                 - R_EEL_OK (Read was successful)
 *                 - R_EEL_ERR_INTERNAL (Internal HW error during blank check (part of Flash read))
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_status_t R_EEL_PFct_ReadDFlash_cmpPatBC (uint32_t add,
                                                            r_eel_patcmp_t * pCmpRes)
{
    r_eel_status_t   iErr;
    r_eel_bcResult_t bc;
    r_eel_patcmp_t   cmpRes;

    iErr = R_EEL_PFct_ReadDFlash_cmpPat (add, &cmpRes);
    if (R_EEL_OK == iErr)
    {
        if (R_EEL_PATCMP_VALID == cmpRes)
        {
            iErr = R_EEL_PFct_BlankCheckDFlash (&add, 1uL, &bc);

            if (R_EEL_BC_WRITTEN != bc)
            {
                /* Although read value was correct, BC points out that the cells are blank */
                cmpRes = R_EEL_PATCMP_INVALID;
            }
        }
    }

    *pCmpRes = cmpRes;

    return (iErr);
} /* R_EEL_PFct_ReadDFlash_cmpPatBC */

/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_ReadDFlash_BCcmpPat
 *********************************************************************************************************************/
/**
 * Function to read 1 word data from Data Flash and compare it with the valid pattern.
 * Additionally, a blank check is done on the address.
 * On internal error during blank check, the process error is updated and the function returns an
 * internal error.
 *
 * Furthermore, on internal error, the process status is updated to
 * R_EEL_ERR_INTERNAL by the functions to read from Flash and blank check.
 *
 * @param[in]      add    - Data Read address
 * @param[out]     pCmpRes - pointer to pattern match result (R_EEL_PATCMP_VALID, R_EEL_PATCMP_INVALID, R_EEL_PATCMP_BLANK)
 *                          R_EEL_TRUE only if pattern matches and the data is written
 * @param[out]     pBc    - pointer to Blank Check result buffer (R_EEL_BC_WRITTEN / R_EEL_BC_BLANK)
 *
 * @return
 *                 - R_EEL_OK (Read/BC was successful)
 *                 - R_EEL_ERR_INTERNAL (Internal HW error during blank check (part of Flash read))
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_status_t R_EEL_PFct_ReadDFlash_BCcmpPat (uint32_t add,
                                                            r_eel_patcmp_t * pCmpRes,
                                                            r_eel_bcResult_t * pBc)
{
    r_eel_status_t   iErr;
    r_eel_bcResult_t bcRes;
    r_eel_patcmp_t   cmpRes;
    uint32_t         addTmp;

    cmpRes = R_EEL_PATCMP_INVALID;

    addTmp = add;
    iErr = R_EEL_PFct_BlankCheckDFlash (&addTmp, 1uL, &bcRes);
    if (R_EEL_OK == iErr)
    {
        if (R_EEL_BC_WRITTEN == bcRes)
        {
            iErr = R_EEL_PFct_ReadDFlash_cmpPat (add, &cmpRes);
        }
    }

    *pCmpRes = cmpRes;
    *pBc     = bcRes;

    return (iErr);
} /* R_EEL_PFct_ReadDFlash_BCcmpPat */


/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_ReadDataFromAddU08
 *********************************************************************************************************************/
/**
 * Reads a 8-bit data value from the given address.
 *
 * @param[in]  add - address to read
 * @return     8bit read data
 */
/*********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 11.3 (QAC message 0306)
 * Reason:       For effective embedded programming, integer to pointer conversions are used
 * Verification: The converted addresses are essential for complete code execution. Incorrect
 *              conversion would result in test fails.
 *********************************************************************************************************************/
R_EEL_STATIC uint8_t R_EEL_PFct_ReadDataFromAddU08 (uint32_t add)
{
    return (*(uint8_t *)add);                                                /* PRQA S 0306 */
}


/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_WriteDataToAddU08
 *********************************************************************************************************************/
/**
 * Writes a 8-bit data value to the given address
 *
 * @param[in]  add  - address to write
 * @param[in]  data - data to write
 * @return     ---
 */
/*********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 11.3 (QAC message 0306)
 * Reason:       For effective embedded programming, integer to pointer conversions are used
 * Verification: The converted addresses are essential for complete code execution. Incorrect
 *              conversion would result in test fails.
 *********************************************************************************************************************/
void R_EEL_PFct_WriteDataToAddU08 (uint8_t data, uint32_t add)
{
    *(uint8_t *)add = data;                                                    /* PRQA S 0306 */
}


/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_Calc_Add2vBlk
 *********************************************************************************************************************/
/**
 * Function to convert an address to a block number.
 *
 * @param[in]      add - address to convert
 * @return         Converted block number
 */
/*********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   - (QAC message 2834)
 * Reason:       Possible division by 0 not possible
 * Verification: divisor initialized @ R_EEL_Init
 *********************************************************************************************************************/
R_EEL_STATIC uint16_t R_EEL_PFct_Calc_Add2vBlk (uint32_t add)
{
    uint32_t ret;

    /* Address = DF base address + EEL pool offset + vblk offset in the pool */
    ret =  add - R_FCU_DFLASH_READ_ADD;
    ret -= ( (uint32_t)(g_fdl_str.RTCfg_pstr->eelPoolStart_u16) * (uint32_t)R_BLOCK_SIZE );
    ret /= g_eel_str.vPoolVblkSize_u16;                                         /* PRQA S 2834 */

    return ( (uint16_t)ret );
}


/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_Calc_vBlkBaseAdd
 *********************************************************************************************************************/
/**
 * Function to calculate a block base address.
 *
 * @param[in]      blk - block number
 * @return         Block base address
 */
/*********************************************************************************************************************/
R_EEL_STATIC uint32_t R_EEL_PFct_Calc_vBlkBaseAdd (uint16_t blk)
{
    uint32_t ret;

    /* Address = DF base address + EEL pool offset + vblk offset in the pool */
    ret =  R_FCU_DFLASH_READ_ADD;
    ret += (uint32_t)(g_fdl_str.RTCfg_pstr->eelPoolStart_u16) * (uint32_t)R_BLOCK_SIZE;
    ret += ( (uint32_t)blk * (uint32_t)g_eel_str.vPoolVblkSize_u16 );

    return (ret);
}

/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_Calc_vBlkTopAdd
 *********************************************************************************************************************/
/**
 * Function to calculate the block top address.
 *
 * @param[in]      blk - block number
 * @return         Block top address
 */
/*********************************************************************************************************************/
R_EEL_STATIC uint32_t R_EEL_PFct_Calc_vBlkTopAdd (uint16_t blk)
{
    uint32_t ret;

    ret = R_EEL_PFct_Calc_vBlkBaseAdd (blk + 1u) - R_EEL_FDL_WRITESIZE;

    return (ret);
}



/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_Calc_vBlkDataAdd
 *********************************************************************************************************************/
/**
 * Function to calculate the address of certain virtual block contents (e.g. Block header words, REF start address,
 * Data zone start address
 *
 * @param[in]      blk - block number
 * @param[in]      Searched contents
 * @return         Address of the affected word within the block
 */
/*********************************************************************************************************************/
R_EEL_STATIC uint32_t R_EEL_PFct_Calc_vBlkDataAdd (uint16_t blk, r_eel_blk_header_data_t off)
{
    uint32_t ret;

    if (R_EEL_BLKHDATA_I1 == off)
    {
        /* I1 is the last block word */
        ret = R_EEL_PFct_Calc_vBlkTopAdd (blk);
    }
    else if (R_EEL_BLKHDATA_DATAZ == off)
    {
        /* Data zone starts  is the last block word */
        ret = R_EEL_PFct_Calc_vBlkTopAdd (blk) - R_WRITE_SIZE;
    }
    else
    {
        ret = R_EEL_PFct_Calc_vBlkBaseAdd (blk) + (uint32_t)off;
    }

    return (ret);
} /* R_EEL_PFct_Calc_vBlkDataAdd */


/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_Calc_BlkFreeSpace
 *********************************************************************************************************************/
/**
 * Function to calculate the space in a certain block, specified by the space between WP and RP.
 *
 * @param[in]      wp - WP
 * @param[in]      rp - RP
 * @return         Space in the block
 */
/*********************************************************************************************************************/
R_EEL_STATIC uint32_t R_EEL_PFct_Calc_BlkFreeSpace (uint32_t wp, uint32_t rp)
{
    uint32_t ret;

    ret = wp - rp;

    return (ret);
}


/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_ConvertTidx2RefAdd
 *********************************************************************************************************************/
/**
 * Function to convert the RAM ID-X table index to REF entry address.
 *
 * @param          tIdx - table index
 * @return         DRP address
 */
/*********************************************************************************************************************/
R_EEL_STATIC uint32_t R_EEL_PFct_ConvertTidx2RefAdd (uint32_t tIdx)
{
    uint32_t ret;

    /* Get word index from table index */
    ret = (g_eel_str.RTCfg_pstr->IDXTab_pau16[tIdx]);                           /* PRQA S 0491 */
    if (0u != ret)
    {
        ret = (ret << R_EEL_SHIFT_ADD_TO_WIDX) + (R_FCU_DFLASH_READ_ADD);
    }

    return (ret);
}


/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_ConvertRefAdd2WIdx
 *********************************************************************************************************************/
/**
 * Function to convert the REF entry address to a RAM ID-X table word index entry.
 *
 * @param          add - reference entry address
 * @return         widx
 */
/*********************************************************************************************************************/
R_EEL_STATIC uint16_t R_EEL_PFct_ConvertRefAdd2WIdx (uint32_t add)
{
    uint16_t ret;

    ret = (uint16_t)( ( add - (R_FCU_DFLASH_READ_ADD) ) >> R_EEL_SHIFT_ADD_TO_WIDX );

    return (ret);
}


/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_Get_RefAdd2DataAdd
 *********************************************************************************************************************/
/**
 * Function to convert the DRP address to the corresponding data address.
 *
 * @param          refAdd - REF entry address
 * @return         Data address
 */
/*********************************************************************************************************************/
R_EEL_STATIC uint32_t R_EEL_PFct_Get_RefAdd2DataAdd (uint32_t refAdd)
{
    uint32_t ret;
    uint16_t blk;

    /* Get relative data address */
    ret = R_EEL_PFct_Get_RefAdd2DataAdd_Rel (refAdd);

    if (0uL != ret)
    {
        /* Add block base address */
        blk  = R_EEL_PFct_Calc_Add2vBlk (refAdd);
        ret += R_EEL_PFct_Calc_vBlkBaseAdd (blk);
    }

    return (ret);
}

/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_Get_RefAdd2DataAdd_Rel
 *********************************************************************************************************************/
/**
 * Function to convert the DRP address to the corresponding data address relative to the virtual block start address.
 * --> Bits 16~30
 *
 * @param          refAdd - REF entry address
 * @return         Data address
 */
/*********************************************************************************************************************/
R_EEL_STATIC uint32_t R_EEL_PFct_Get_RefAdd2DataAdd_Rel (uint32_t refAdd)
{
    uint32_t ret;

    /* fetch the upper half word: address relative to block base address */
    ret = R_EEL_PFct_ReadDFlashU32 (refAdd + R_EEL_REF_OFF_DRP);
    ret &= R_EEL_DRP_DATA_MASK;
    ret = (ret >> 16);

    return (ret);
}


/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_Chk_DSInvalidated_InvFlg
 *********************************************************************************************************************/
/**
 * Function to check if a DS with given DRP address is invalidated.
 *
 * @param[in]      refAdd - REF entry address
 * @return         Invalid flag
 *                 - R_EEL_TRUE     DS is invalidated
 *                 - R_EEL_FALSE    DS is not invalidated
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_flag_t R_EEL_PFct_Chk_DSInvalidated_InvFlg (uint32_t refAdd)
{
    r_eel_flag_t inv;
    uint32_t     drp;

    /* Normal invalidation check */
    drp = R_EEL_PFct_ReadDFlashU32 (refAdd + R_EEL_REF_OFF_DRP);

    if ( R_EEL_DRP_INVALIDATE_FLG == (R_EEL_DRP_INVALIDATE_FLG & drp) )
    {
        inv = R_EEL_TRUE;
    }
    else
    {
        inv = R_EEL_FALSE;
    }

    return (inv);
} /* R_EEL_PFct_Chk_DSInvalidated_InvFlg */

/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_Chk_DSInvalidated
 *********************************************************************************************************************/
/**
 * Function to check if a DS with given DRP address is invalidated.
 *
 * @param[in]      refAdd - REF entry address
 * @param[in]      tidx   - tidx of the DS
 * @param[out]     inv - return flag
 *                        - R_EEL_TRUE  (DS is invalidated)
 *                        - R_EEL_FALSE (DS is not invalidated)
 * @return         Operation processing status
 *                 - R_EEL_OK       (No issue)
 *                 - R_EEL_INTERNAL (Internal HW error during blank check)
 */
/*********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   - (QAC message 3206)
 * Reason:       One variable is not used in the function. This is intended as the usage depends on the compile options
 * Verification: Test with different compile options done
 *********************************************************************************************************************/
R_EEL_STATIC r_eel_status_t R_EEL_PFct_Chk_DSInvalidated (uint32_t refAdd, uint16_t idx,            /* PRQA S 3206 */
                                                          r_eel_flag_t * invRet)
{
    r_eel_flag_t             inv;
    r_eel_status_t           iErr;
    #ifdef R_EEL_SUPPORT_EXT_FEATURES
        r_eel_ext_features_t extFeatures;
        r_eel_bcResult_t     bc;
        uint32_t             dataAdd;
    #endif

    iErr = R_EEL_OK;

    /* Normal invalidation check */
    inv = R_EEL_PFct_Chk_DSInvalidated_InvFlg (refAdd);

    #ifdef R_EEL_SUPPORT_EXT_FEATURES
        extFeatures = g_eel_str.RTCfg_pstr->IDLTab_pstr[idx].ext_features_enu;
        if ( (R_EEL_EXTF_FINV == extFeatures) ||
             (R_EEL_EXTF_WC_FINV == extFeatures) )
        {
            dataAdd = R_EEL_PFct_Get_RefAdd2DataAdd (refAdd);
            iErr = R_EEL_PFct_BlankCheckDFlash (&dataAdd, 1uL, &bc);
            if (R_EEL_OK == iErr)
            {
                if (R_EEL_BC_WRITTEN == bc)
                {
                    inv = R_EEL_TRUE;
                }
            }
        }
    #endif

    *invRet = inv;

    return (iErr);
} /* R_EEL_PFct_Chk_DSInvalidated */

/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_Chk_EELPoolSpaceForDS
 *********************************************************************************************************************/
/**
 * Function to check if a DS fits into the EEL pool (enough prepared space)
 *
 * @param          dsLen - DS length (Data Bytes)
 * @return         Invalidated check result
 *                 - R_EEL_BUSY (DS fits)
 *                 - R_EEL_ERR_POOL_FULL (DS fits not)
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_status_t R_EEL_PFct_Chk_EELPoolSpaceForDS (uint16_t dsLen, r_eel_process_id_t pId)
{
    uint32_t       space;
    r_eel_status_t ret;

    if ( (R_EEL_PR_WR == pId) && (R_EEL_TRUE == g_eel_str.sm_str[R_EEL_PR_RF].active_enu) )
    {
        /* Consider total available space for Refresh Write */
        space = R_EEL_SFct_Calc_FreeSpace ();
    }
    else
    {
        /* Consider reduced space for user write ( free space - 1 block) */
        (void)R_EEL_GetSpace (&space);
    }

    if ( ( (uint32_t)dsLen + R_EEL_REF_OFF_DS ) <= space )
    {
        ret = R_EEL_BUSY;
    }
    else
    {
        ret = R_EEL_ERR_POOL_FULL;
    }

    return (ret);
} /* R_EEL_PFct_Chk_EELPoolSpaceForDS */




/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_ConvertId2TIdx
 *********************************************************************************************************************/
/**
 * Function to get the ID-L / ID-X table index of an ID. Therefore, the ID is searched in the
 * ID-L table.
 *
 * @param[in]      id - ID to search
 * @return         Conversion result
 *                 - table index or
 *                 - R_EEL_ID_NOT_FOUND=0xFFFF if the ID was not found
 */
/*********************************************************************************************************************/
uint16_t R_EEL_PFct_ConvertId2TIdx (uint16_t id)
{
    uint16_t               idxFound,
                           idx;
    const r_eel_ds_cfg_t * idlTab;

    /* Search the ID in the ROM table
       --> This must be a fast loop, so idx counts backwards */
    idxFound    = R_EEL_ID_NOT_FOUND;
    idx         = g_eel_str.RTCfg_pstr->IDLTabIdxCnt_u16;
    idlTab      = g_eel_str.RTCfg_pstr->IDLTab_pstr;

    do
    {
        idx--;

        /* Replaced function call by "if( id == R_EEL_PFct_ConvertTIdx2Id( idx ) )" direct table
           access to increase the performance (~1/3 by reduction of necessary memory accesses
           search time) */
        if (id == idlTab[idx].ID_u16)                                     /* PRQA S 0491 */
        {
            idxFound    = idx;
            idx         = 0uL;
        }
    }
    while (idx > 0uL);

    return (idxFound);
} /* R_EEL_PFct_ConvertId2TIdx */

/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_ConvertId2TIdxSorted
 *********************************************************************************************************************/
/**
 * Function to get the ID-L / ID-X table index of an ID from a certain sorted ID-L RAM table
 * Therefore, the ID is searched in the ID-L table.
 *
 * @param[in]      id - ID to search
 * @return         Conversion result
 *                 - table index or
 *                 - R_EEL_ID_NOT_FOUND=0xFFFF if the ID was not found
 */
/*********************************************************************************************************************/
R_EEL_STATIC uint16_t R_EEL_PFct_ConvertId2TIdxSorted (uint16_t id, const uint16_t pIdTab[][2], uint32_t cnt)
{
    int32_t idxMax, idxMin,
            idxChk,
            idxFound;
    uint16_t idChk;

    /* Search the ID in the ROM table with binary search */
    idxFound = R_EEL_ID_NOT_FOUND;
    idxMax   = (int32_t)(cnt - 1uL);
    idxMin   = 0;

    while ( (idxMax >= idxMin) && (R_EEL_ID_NOT_FOUND == (uint32_t)idxFound) )
    {
        idxChk = (int32_t)( (uint32_t)(idxMax - idxMin) >> 1 ) + idxMin; /* conversions done to define the shift
                                                                            operation type (arithmetic or logic) */
        idChk = pIdTab[idxChk][0];

        if (idChk < id)
        {
            idxMin = idxChk + 1;
        }
        else if (idChk > id)
        {
            idxMax = idxChk - 1;
        }
        else
        {
            idxFound = idxChk;
        }
    }

    return ( (uint16_t)idxFound );
} /* R_EEL_PFct_ConvertId2TIdxSorted */



/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_ConvertTIdx2Len
 *********************************************************************************************************************/
/**
 * Function to calculate the DS length from the table index.
 *
 * @param          tIdx - IDL table index
 * @return         DS length
 */
/*********************************************************************************************************************/
uint16_t R_EEL_PFct_ConvertTIdx2Len (uint16_t tIdx)
{
    return (g_eel_str.RTCfg_pstr->IDLTab_pstr[tIdx].len_u16);             /* PRQA S 0491 */
}


/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_ConvertTIdx2Id
 *********************************************************************************************************************/
/**
 * Function to calculate the DS ID from the table index.
 *
 * @param          tIdx - IDL table index
 * @return         DS ID
 */
/*********************************************************************************************************************/
uint16_t R_EEL_PFct_ConvertTIdx2Id (uint16_t tIdx)
{
    return (g_eel_str.RTCfg_pstr->IDLTab_pstr[tIdx].ID_u16);              /* PRQA S 0491 */
}


/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_Get_RefAdd2ID
 *********************************************************************************************************************/
/**
 * Function to get the ID from the DRP.
 *
 * @param          refAdd - reference address
 * @return         DS ID
 */
/*********************************************************************************************************************/
R_EEL_STATIC uint16_t R_EEL_PFct_Get_RefAdd2ID (uint32_t refAdd)
{
    uint16_t ret;
    uint32_t data;

    data = R_EEL_PFct_ReadDFlashU32 (refAdd + R_EEL_REF_OFF_DRP_ID);
    /* fetch the lower half word: ID */
    ret = (uint16_t)(data & 0xFFFFu);

    return (ret);
}


/**********************************************************************************************************************
   Function name:  R_EEL_PFct_RoundUpToWriteGranularity
**********************************************************************************************************************/
/*!
    Round up data to the next word boundary.

    @param[in]      data - data to convert
    @return         rounded-up data
*/
/***********************************************************************************************************************/
R_EEL_STATIC uint32_t R_EEL_PFct_RoundUpToWriteGranularity (uint32_t data)
{
    uint32_t ret, mask;

    mask = R_EEL_FDL_WRITESIZE - 1uL;

    ret = (data + mask) & (~mask);

    return (ret);
}

/**********************************************************************************************************************
   Function name:  R_EEL_Pfct_AdjustByteCnt_ExtFeatures
**********************************************************************************************************************/
/*!
    Adjust the number of Bytes in the data zone to consider the extended featurees

    @param[in]      byteCnt    -    number of data bytes
    @param[in]      idx        -    table index of the ID
    @return         updated number of data bytes
*/
/***********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   - (QAC message 3206)
 * Reason:       One variable is not used in the function. This is intended as the usage depends on the compile options
 * Verification: Test with different compile options done
 *********************************************************************************************************************/

R_EEL_STATIC uint16_t R_EEL_Pfct_AdjustByteCnt_ExtFeatures (uint16_t byteCnt, uint16_t idx)         /* PRQA S 3206 */
{
    #ifdef R_EEL_SUPPORT_EXT_FEATURES
        r_eel_ext_features_t extFeatures;

        extFeatures = g_eel_str.RTCfg_pstr->IDLTab_pstr[idx].ext_features_enu;

        if ( (R_EEL_EXTF_WC == extFeatures) ||
             (R_EEL_EXTF_FINV == extFeatures) )
        {
            byteCnt += R_WRITE_SIZE;
        }
        else
        {
            if (R_EEL_EXTF_WC_FINV == extFeatures)
            {
                byteCnt += (2u * R_WRITE_SIZE);
            }
        }
    #endif /* ifdef R_EEL_SUPPORT_EXT_FEATURES */

    return (byteCnt);
} /* R_EEL_Pfct_AdjustByteCnt_ExtFeatures */



/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_PrepLoopLimitReset
 *********************************************************************************************************************/
/**
 * Reset the prepare loop limit counter.
 *
 * @param[in]      -
 * @return         The central EEL variable is used as output
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_PFct_PrepLoopLimitReset (void)
{
    g_eel_str.opSv_str.prepLoopLimit_u16 = R_EEL_PREPLOOPLIMIT_OFF;
}


/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_Chk_ProcessActive
 *********************************************************************************************************************/
/**
 * Function to check if a process is active.
 *
 * @param[in]      PID - ID of the process to check
 * @return         Check result
 *                 - R_EEL_TRUE  (process is active)
 *                 - R_EEL_FALSE (process is passive)
 */
/*********************************************************************************************************************/
r_eel_flag_t R_EEL_PFct_Chk_ProcessActive (r_eel_process_id_t PID)
{
    return (g_eel_str.sm_str[PID].active_enu);                                  /* PRQA S 3689 */
}


/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_Calc_BlockRWP
 *********************************************************************************************************************/
/**
 * Function to read a RWP from the block header. \n
 * No check on blank data is included as the read is done only on active/prepared blocks which always have EC set.
 *
 * @param[in]      blk - block number
 * @return         RWP read from block header
 */
/*********************************************************************************************************************/
R_EEL_STATIC uint32_t R_EEL_PFct_Calc_BlockRWP (uint16_t blk)
{
    uint32_t ret;

    ret = R_EEL_PFct_Read_BlkHeaderData24bit (blk, R_EEL_BLKHDATA_RWP);
    ret += (R_FCU_DFLASH_READ_ADD);

    return (ret);
}


/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_Calc_BlockEC
 *********************************************************************************************************************/
/**
 * Function to read EC from the block header.
 * No check on blank data is included as the read is done only on active/prepared blocks which always have EC set.
 *
 * @param[in]      blk - block number
 * @return         EC read from block header
 */
/*********************************************************************************************************************/
R_EEL_STATIC uint32_t R_EEL_PFct_Calc_BlockEC (uint16_t blk)
{
    uint32_t ret;

    ret = R_EEL_PFct_Read_BlkHeaderData24bit (blk, R_EEL_BLKHDATA_EC);

    return (ret);
}


/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_Read_BlkHeaderData24bit
 *********************************************************************************************************************/
/**
 * Function to read a dedicated word from the block header (Only 24bit words).
 *
 * @param[in]  blk    - block number
 * @param[in]  offset - R_EEL_BLKHDATA_EC,
 *                    - R_EEL_BLKHDATA_RWP,
 * @return     Read value from the block header and mask by 24bit
 */
/*********************************************************************************************************************/
R_EEL_STATIC uint32_t R_EEL_PFct_Read_BlkHeaderData24bit (uint16_t blk, r_eel_blk_header_data_t offset)
{
    uint32_t add, data;

    add  = R_EEL_PFct_Calc_vBlkDataAdd (blk, offset);

    data = R_EEL_PFct_ReadDFlashU32 (add);
    data = (data & R_EEL_MASK_24BIT);

    return (data);
}


/*********************************************************************************************************************
 * Function name:  R_EEL_PFct_Calc_BlkSpace
 *********************************************************************************************************************/
/**
 * Function to calculate the Flash block space available for data and REF zone (max. space, not free space).
 *
 * @param          ---
 * @return         Block space in bytes
 */
/*********************************************************************************************************************/
uint32_t R_EEL_PFct_Calc_BlkSpace (void)
{
    uint32_t data;

    data = (g_eel_str.vPoolVblkSize_u16 - R_EEL_BLKHDATA_HSIZE) - R_EEL_FDL_WRITESIZE;

    return (data);
}



/*********************************************************************************************************************
 *********************************************************************************************************************
 * Supporting functions
 *********************************************************************************************************************
 *********************************************************************************************************************/



/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_ChkBlockElder
 *********************************************************************************************************************/
/**
 * Check if block blk1 is elder in the ring buffer than block blk2.
 * blk1 is elder than blk2 if: EC is lower or EC is equal and block number is lower.
 *
 * @param[in]      blk1 - block number 1
 * @param[in]      blk2 - block number 2
 * @return         Function return
 *                 - R_EEL_TRUE (blk1 is elder)
 *                 - R_EEL_FALSE (blk1 is younger)
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_flag_t R_EEL_SFct_ChkBlockElder (uint16_t blk1, uint16_t blk2)
{
    uint32_t     ec1, ec2;
    r_eel_flag_t ret;

    ec1 = R_EEL_PFct_Calc_BlockEC (blk1);
    ec2 = R_EEL_PFct_Calc_BlockEC (blk2);

    if ( ( (blk1 < blk2) && (ec1 == ec2) ) ||
         ( (blk1 > blk2) && (ec1 <  ec2) ) )
    {
        ret = R_EEL_TRUE;
    }
    else
    {
        ret = R_EEL_FALSE;
    }

    return (ret);
} /* R_EEL_SFct_ChkBlockElder */


/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_SearchDS
 *********************************************************************************************************************/
/**
 * Search a data set with a given ID in the ring buffer. The search is done by parsing the REF
 * zones and searching a DRP of a valid DS with the given ID.
 * The search starts in the active block, and is continued backwards until the ID is found or
 * the active zone is left. \n
 *
 * The searchType is used to configure the function for special searches, which are required in
 * the startup phase of the EEL. \n
 *
 * This function does not do any DS validity verification!!! \n
 *
 * On internal error during Data Flash read (with blank check), the process error is updated and
 * the function returns an internal error.
 *
 * @param[in]      rp         - RP in the active block. This defines the search starting point
 * @param[in]      id         - ID to search
 * @param[in]      searchType - R_EEL_SEARCHDS_NORMAL    (Normal search for a valid DS with the given ID)
 *                            - R_EEL_SEARCHDS_ANY       (Any REF entry is welcome. The entry is
 *                                                        analysed by the calling function)
 * @param[out]     pREFAdd    DS REF entry address return buffer pointer
 *                            - R_EEL_NULL, if no DS found
 *                            - other: address of the DRP of the found DS
 * @return         --
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SFct_SearchDS (uint32_t rp,
                                       uint16_t id,
                                       r_eel_searchds_t searchType,
                                       uint32_t * pREFAdd)
{
    uint32_t            refAddRet;
    uint32_t            refStart;
    uint16_t            blk;
    uint16_t            blk_cur;
    r_eel_blockstatus_t blkStat;
    r_eel_flag_t        endLoop;


    /* Calculate Start of the REF zone */
    blk         = R_EEL_PFct_Calc_Add2vBlk (rp);
    refStart    = R_EEL_PFct_Calc_vBlkDataAdd (blk, R_EEL_BLKHDATA_REFZ);

    /* Initialize the search loop */
    refAddRet = R_EEL_NULL;
    endLoop   = R_EEL_FALSE;

    do
    {
        /* Forward RP:
           If we are at the end of the REF zone we go to the previous block
           RWP. As this is the blank space between the zones, we may not check
           there but just continue forwarding rp  */
        if (rp == refStart)
        {
            /* Get previous block number, REF zone begin and end address via RWP */
            blk_cur = R_EEL_PFct_Calc_Add2vBlk (rp);        /* Get current block # */
            rp = R_EEL_PFct_Calc_BlockRWP (blk_cur);       /* Get rwp */
            blk = R_EEL_PFct_Calc_Add2vBlk (rp);            /* Calc preceding active block */
            refStart = R_EEL_PFct_Calc_vBlkDataAdd (blk, R_EEL_BLKHDATA_REFZ);
            /* Get search loop end */
            blkStat = R_EEL_SFct_Calc_BlkStat (blk);

            /* Stop on last block reached (no more elder active blocks) */
            if (R_EEL_BLKSTAT_ACTIVE != blkStat)
            {
                endLoop = R_EEL_TRUE;
            }
            else
            {
                /* We are searching backwards in the ring buffer. So blk must be elder
                   than the current block.
                   This test ensures, that the ring buffer search does not get a wrap around if
                   the RWP points to a newer active block (caused by invalid block in the
                   active pool) */
                if ( R_EEL_FALSE == R_EEL_SFct_ChkBlockElder (blk, blk_cur) )
                {
                    endLoop = R_EEL_TRUE;
                }
            }

        }
        else /* if( rp == refStart ) */
        {
            rp -= R_EEL_REF_OFF_DS;

            if (R_EEL_SEARCHDS_NORMAL == searchType)
            {
                /* Standard case. search a fitting ID (Must not be blank)*/
                if ( id == ( R_EEL_PFct_Get_RefAdd2ID (rp) ) )
                {
                    endLoop   = R_EEL_TRUE;
                    refAddRet = rp;
                }
            }
            else /* R_EEL_SEARCHDS_ANY */
            {
                /* Return any DS */
                endLoop   = R_EEL_TRUE;
                refAddRet = rp;
            }
        }
    }
    while (R_EEL_FALSE == endLoop);

    *pREFAdd = refAddRet;

} /* R_EEL_SFct_SearchDS */


/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_Chk_DSValid
 *********************************************************************************************************************/
/**
 * Function to check if a DS belonging to a REF entry is valid.
 * Data is valid (completely written), if one EOR is written. The other EOR is only to mark
 * the 1st EOR valid
 *
 * Check result is:
 * - R_EEL_CHKDS_VALID:
 *     Both EOR are available
 * - R_EEL_CHKDS_VALID_EOR_INCOMPLETE:
 *     Data is valid but one EOR is missing (interruption on writing the 1st or 2nd EOR)
 * - R_EEL_CHKDS_INVALID:
 *     No EOR is available, so we cannot trust the data
 *
 * On internal error during Data Flash Tag read (with blank check), the process error is updated
 * and the function returns an internal error.
 *
 * @param[in]      refAdd - pointer to the REF zone entry
 * @param[out]     pChkDS - pointer to DS check result destination buffer (function result)
 *                          - R_EEL_CHKDS_VALID
 *                          - R_EEL_CHKDS_VALID_EOR_INCOMPLETE
 *                          - R_EEL_CHKDS_INVALID
 *
 * @return         A called sub-routine, reading Data Flash with blank check might end with
 *                 internal error on blank check.
 *                 - R_EEL_OK       (No error on Data Flash read)
 *                 - R_EEL_INTERNAL (Internal HW error during Data Flash read (blank check))
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_status_t R_EEL_SFct_Chk_DSValid (uint32_t refAdd,
                                                    r_eel_chk_ds_t * pChkDS)
{
    r_eel_status_t iErr;
    r_eel_chk_ds_t chkDS;
    r_eel_patcmp_t eor0Match, eor1Match;
    uint32_t       add;

    chkDS = R_EEL_CHKDS_INVALID;

    /* Check EOR 0 and EOR1 first */
    add = refAdd + R_EEL_REF_OFF_EOR1;
    iErr = R_EEL_PFct_ReadDFlash_cmpPatBC (add, &eor1Match);

    if (R_EEL_OK == iErr)
    {
        if (R_EEL_PATCMP_VALID == eor1Match)
        {
            chkDS = R_EEL_CHKDS_VALID;
        }
        else
        {
            add = refAdd + R_EEL_REF_OFF_EOR0;
            iErr = R_EEL_PFct_ReadDFlash_cmpPatBC (add, &eor0Match);

            if (R_EEL_PATCMP_VALID == eor0Match)
            {
                chkDS = R_EEL_CHKDS_VALID_EOR_INCOMPLETE;
            }
        }
    }

    *pChkDS = chkDS;

    return (iErr);
} /* R_EEL_SFct_Chk_DSValid */



/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_FindValidDS
 *********************************************************************************************************************/
/**
 * Function to find a DS based on a given ID and tIdx
 * - Search the DS in table or by REF zone hopping
 * - Judge found DS validity
 *
 * @param[in]      tIdx    - table index of the ID. Is calculated in the calling functions
 * @param[in]      ID      - ID of the DS to find
 * @param[out]     pRefAdd - is set to the REF entry address if a valid DS instance is found
 *
 * @return         A called sub-routine, reading Data Flash with blank check might end with
 *                 internal error on blank check.
 *                 - R_EEL_OK       (No error on Data Flash read)
 *                 - R_EEL_INTERNAL (Internal HW error during Data Flash read (blank check))
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_status_t R_EEL_SFct_FindValidDS (uint16_t tIdx,
                                                    uint16_t ID,
                                                    uint32_t * pRefAdd)
{
    uint32_t       refAdd;
    r_eel_status_t iErr;



    /* ----------------- Initialize local variables -------------------------------------------- */
    iErr            = R_EEL_OK;

    /* -------------------------------- Get DS address and size -------------------------------- */
    /* Due to a preceeding early read of the same DS ID, a RAM table entry might be available,
       even if the Startup is not completed. So check this 1st */
    refAdd = R_EEL_PFct_ConvertTidx2RefAdd (tIdx);

    /* On early read search REF-Zones if RAM table entry is not already filled */
    if ( (R_EEL_FALSE == g_eel_str.opSv_str.ramTableInit_enu) &&
         (R_EEL_NULL == refAdd) )
    {
        iErr = R_EEL_SFct_FindValidDS_NoIdxTab (ID, &refAdd);
    }

    *pRefAdd = refAdd;

    return (iErr);
} /* R_EEL_SFct_FindValidDS */

/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_FindValidDS_NoIdxTab
 *********************************************************************************************************************/
/**
 * Function to find a DS based on a given ID. Search by Ref entry hopping, including judge found DS validity
 *
 * @param[in]      ID      - ID of the DS to find
 * @param[out]     pRefAdd - is set to the REF entry address if a valid DS instance is found
 *
 * @return         A called sub-routine, reading Data Flash with blank check might end with
 *                 internal error on blank check.
 *                 - R_EEL_OK       (No error on Data Flash read)
 *                 - R_EEL_INTERNAL (Internal HW error during Data Flash read (blank check))
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_status_t R_EEL_SFct_FindValidDS_NoIdxTab (uint16_t ID,
                                                             uint32_t * pRefAdd)
{
    uint32_t       refAdd, refAddTmp;
    uint16_t       tIdx;
    r_eel_flag_t   endLoop;
    r_eel_chk_ds_t chkDSResult;
    r_eel_status_t iErr;

    iErr            = R_EEL_OK;
    refAdd          = R_EEL_NULL;

    /* -------------------------------- Get DS address and size -------------------------------- */
    endLoop = R_EEL_FALSE;
    refAddTmp = g_eel_str.rp_u32;
    do
    {
        chkDSResult = R_EEL_CHKDS_INVALID;

        /* Search next DS with given ID */
        R_EEL_SFct_SearchDS (refAddTmp,
                             ID,
                             R_EEL_SEARCHDS_NORMAL,
                             &refAddTmp);


        if (R_EEL_NULL == refAddTmp)
        /* no more DS with the ID found */
        {
            endLoop = R_EEL_TRUE;
        }
        else
        /* DS with the ID found, now we check if we can use it */
        {
            /* DS must not be invalid (at least one EOR set) */
            iErr = R_EEL_SFct_Chk_DSValid (refAddTmp, &chkDSResult);

            if (R_EEL_OK == iErr)
            {
                if (R_EEL_CHKDS_INVALID != chkDSResult)
                {
                    endLoop = R_EEL_TRUE;
                    refAdd = refAddTmp;

                    /* Add entry to IDX table if available */
                    tIdx = R_EEL_PFct_ConvertId2TIdx (ID);
                    if (R_EEL_ID_NOT_FOUND != tIdx)
                    {
                        g_eel_str.RTCfg_pstr->IDXTab_pau16[tIdx] = R_EEL_PFct_ConvertRefAdd2WIdx (refAddTmp); /*PRQA S 0491*/
                    }
                }
            }
        }
    }
    while ( (R_EEL_OK == iErr) && (R_EEL_FALSE == endLoop) );

    *pRefAdd = refAdd;

    return (iErr);
} /* R_EEL_SFct_FindValidDS_NoIdxTab */


/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_Read_Chk_Data
 *********************************************************************************************************************/
/**
 * This function reads DS data or checks DS data against reference data.
 * It is required by the Read command (data read), Refresh process (Data read) and Incremental
 * Write process. \n
 *
 * Issues considered in the function:
 *     - block boundaries \n
 *       The function proceeds the WP/RP pointer to the next block if required
 *
 * @param[in,out]  pSrcAdd   - pointer to the source address variable. Taken as input to read data
 *                             and modified if function proceeds to the next block
 * @param[in]      destAdd   - address of the destination write buffer\
 *                             Important: if pSrcAdd is word aligned, we read data word aligned.
 *                                        Then destAdd must be word aligned too. If pSrcAdd is
 *                                        non word aligned, we read 1st bytes up to word alignment
 *                                        byte aligned. Then destAdd must be byte aligned!!!
 * @param[in]      cntBytes  - number of data bytes to read
 * @param[in]      chk       - flag to specify if data shall be read or data shall be compared
 * @param[in]      pChkRes   - read compare result (R_EEL_FLG_OK/R_EEL_FLG_ERROR)
 *
 *
 * @return         ---
 */
/*********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 21.1 (QAC message 3382)
 * Reason:       Unsigned arithmetic is used all over the project for space calculation
 * Verification: Code review ensured that arithmetic wrap around will not happen
 *********************************************************************************************************************/

R_EEL_STATIC void R_EEL_SFct_Read_Chk_Data (uint32_t * pSrcAdd,
                                            uint32_t destAdd,
                                            uint32_t cntBytes,
                                            r_eel_flag_t chk,
                                            r_eel_err_flg_t * pChkRes)
{
    uint8_t         dataU08;
    uint32_t        data;
    uint32_t        srcAdd;
    r_eel_err_flg_t chkRes;
    uint32_t        i;                          /* FOR-Loop variable */
    uint32_t        cntShift;           /* shift count */
    uint32_t        cntRead;
    uint32_t        srcAddNext;

    /* Read important variables */
    srcAdd = (*pSrcAdd);

    /* Initialize defaults */
    chkRes = R_EEL_FLG_OK;

    cntShift = ( srcAdd & (R_EEL_FDL_WRITESIZE - 1uL) );
    cntRead = R_EEL_FDL_WRITESIZE - cntShift;

    /* Calculation of unaligned bytes to read and the next address after unaligned read */
    if (cntRead > cntBytes)
    {
        /* We read less bytes than remaining in the unaligned address --> After read we remain in the word */
        cntRead = cntBytes;
        srcAddNext = srcAdd + cntRead;
    }
    else
    {
        /* We read all unaligned bytes in --> we proceed to the next data word (negative address direction */
        srcAddNext = srcAdd - cntShift - R_EEL_FDL_WRITESIZE;
    }

    /* ------------------- read / check unaligned 1st source address  ------- */
    if (cntShift != 0)
    {
        srcAdd -= cntShift; /* round down to the previous word aligned address */
        data = R_EEL_PFct_ReadDFlashU32 (srcAdd);           /* read out one word */

        for (i = 1; i < cntShift; i++)
        {
            data = (data >> 8u);
        }

        for (i = 0; i < cntRead; i++)
        {
            data = (data >> 8u);
            dataU08 = (uint8_t)(data & 0xFFuL);

            /* A check on unaligned data will never happen as write incremental (using the check) will always compare
               the complete DS, starting from 1st word address. so we don't have a check if read or check here. */
            R_EEL_PFct_WriteDataToAddU08 (dataU08, destAdd);

            cntBytes--;
            destAdd++;
        }

        srcAdd  = srcAddNext;
    }


    /* ------------------- check aligned part ------------------------------- */
    for ( ; cntBytes > (R_EEL_FDL_WRITESIZE - 1uL); cntBytes -= R_EEL_FDL_WRITESIZE)
    {
        data = R_EEL_PFct_ReadDFlashU32 (srcAdd);

        for (i = 0; i < R_EEL_FDL_WRITESIZE; i++)
        {
            dataU08 = (uint8_t)(data & 0xFFuL);
            if (R_EEL_FALSE == chk)
            {       /* byte-wise write */
                R_EEL_PFct_WriteDataToAddU08 (dataU08, destAdd);
            }
            else
            {       /* byte-wise read */
                if ( dataU08 != R_EEL_PFct_ReadDataFromAddU08 (destAdd) )
                {
                    chkRes = R_EEL_FLG_ERROR;
                }
            }
            data = (data >> 8u); /* right shift 8bit each time - byte-wise read */
            destAdd++;
        }
        srcAdd  -= R_EEL_FDL_WRITESIZE;
    }

    /* ------------------- check misaligned last read source address -------- */
    if (cntBytes != 0uL)
    {
        data =  R_EEL_PFct_ReadDFlashU32 (srcAdd);

        for (i = 0; i < cntBytes; i++)
        {
            dataU08 = (uint8_t)(data & 0xFFuL);
            data = (data >> 8u); /* right shift 8bit each time - byte-wise read */
            if (R_EEL_FALSE == chk)
            {       /* byte-wise write */
                R_EEL_PFct_WriteDataToAddU08 (dataU08, destAdd);
            }
            else
            {       /* byte-wise read */
                if ( dataU08 != R_EEL_PFct_ReadDataFromAddU08 (destAdd) )
                {
                    chkRes = R_EEL_FLG_ERROR;
                }
            }
            destAdd++;
            srcAdd++;
        }
    }

    *pChkRes = chkRes;
    *pSrcAdd = srcAdd;

} /* R_EEL_SFct_Read_Chk_Data */


/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_SetChecksum_8Bit_from_24bit
 *********************************************************************************************************************/
/**
 * Calculate the 8bit checksum of 24bit data and return all as 32bit value:
 * 8bit CS from 24bit data is stored in the top 8bit of the data word.
 *
 * @param[in]      data - 24bit data value to be extended by the checksum
 *
 * @return         32bit value containing 24bit data and 8bit CS
 */
/*********************************************************************************************************************/
R_EEL_STATIC uint32_t R_EEL_SFct_SetChecksum_8Bit_from_24bit (uint32_t data)
{
    uint32_t ret,
             dataLoc;

    dataLoc = data;

    /* Calculate CS */
    ret  = (dataLoc & 0xFF);
    dataLoc >>= 8;
    ret += (dataLoc & 0xFF);
    dataLoc >>= 8;
    ret += (dataLoc & 0xFF);

    /* Calculate return value: Bit 0~23: data
                               Bit 24~31: CS */
    ret = ( ( (~ret) & 0xFF ) << 24 );
    ret += (data & 0x00FFFFFF);

    return (ret);
} /* R_EEL_SFct_SetChecksum_8Bit_from_24bit */



/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_SetDriverStatus
 *********************************************************************************************************************/
/**
 * Function to explicitly set the driver status.                               \n
 *
 * Treatment on os=EEL_OPERATION_PASSIVE. It is differentiated between normal set to passive
 * (shut-down) and error shut down:                                            \n
 * - normal shut down: no user operation is busy and no SV error               \n
 *                     --> no user operation and no SV process error update    \n
 * - error shut down (user operation error )                                   \n
 *                     --> SV process status update to R_EEL_ERR_ACCESS_LOCKED   \n
 * - error shut down (SV operation error )                                     \n
 *                     --> no SV process status update as it is set anyhow to error \n
 *
 * @param[in]      as - All possible values of the r_eel_access_status_t enumeration
 * @param[in]      os - All possible values of the r_eel_operation_status_t enumeration
 *
 * @return         ---
 */
/*********************************************************************************************************************/
#define R_EEL_START_SEC_CONST
#include "r_eel_mem_map.h"                                                                          /* PRQA S 5087 */

void R_EEL_SFct_SetDriverStatus (r_eel_access_status_t as, r_eel_operation_status_t os)
{
    static const r_eel_process_id_t   aPId[] = { R_EEL_PR_WT, R_EEL_PR_WI, R_EEL_PR_FO };
    static const r_eel_operation_id_t aOId[] = { R_EEL_OP_WT, R_EEL_OP_WTIMM, R_EEL_OP_FO };
    uint32_t                          i;
    r_eel_flag_t                      usrErr;

    usrErr = R_EEL_FALSE;

    /* In case of operation status set to passive, we
       - shut down all processes and
       - conditionally set operations errors
    */
    if (R_EEL_OPERATION_PASSIVE == os)
    {
        /* Set errors for active user processes WI, WT, FO */
        for (i = 0uL; i < 3uL; i++)
        {
            if (R_EEL_TRUE == g_eel_str.sm_str[aPId[i]].active_enu)               /* PRQA S 3689 */
            {
                if ( R_EEL_FLG_OK == R_EEL_SFct_ErrStatCheckError (aPId[i]) )
                {                                                               /* PRQA S 3689 1 */
                    g_eel_str.op_str[aOId[i]].req_pstr->status_enu = R_EEL_ERR_ACCESS_LOCKED;
                }
                else
                {
                    g_eel_str.op_str[aOId[i]].req_pstr->status_enu =             /* PRQA S 3689 */
                                                                     g_eel_str.sm_str[aPId[i]].rStat_enu; /* PRQA S 3689 */
                }
                usrErr = R_EEL_TRUE;
            }
        }

        /* set the SV process error on user process error
           - not set on normal shut-down (no usrErr)
           - not set on BG system error (set anyhow) */
        if (R_EEL_TRUE == usrErr)
        {
            (void)R_EEL_SFct_ProcessErrorUpdate (R_EEL_PR_SV, R_EEL_ERR_ACCESS_LOCKED, R_EEL_SM_SUPV_RUN);
        }

        /* Shut down all processes */
        for (i = R_EEL_PR_RE; i < R_EEL_PR_END; i++)
        {
            g_eel_str.sm_str[i].active_enu = R_EEL_FALSE;
        }
    }

    /* Now set the driver status variables.
       Done at function end as possibly before the SV status was changed within this function */

    /* Set access status */
    if (R_EEL_ACCESS_UNDEFINED != as)
    {
        g_eel_str.ds_str.accessStatus_enu     = as;
    }
    /* Set operation status */
    if (R_EEL_OPERATION_UNDEFINED != os)
    {
        g_eel_str.ds_str.operationStatus_enu  = os;
    }

    /* Set background error from Supervision process status */
    g_eel_str.ds_str.backgroundStatus_enu     = g_eel_str.sm_str[R_EEL_PR_SV].rStat_enu;
} /* R_EEL_SFct_SetDriverStatus */

#define R_EEL_STOP_SEC_CONST
#include "r_eel_mem_map.h"                                                                          /* PRQA S 5087 */

/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_ErrStatCheckError_CurProc
 *********************************************************************************************************************/
/**
 * Function to judge if the current process status is an error or a warning. Depending on this
 * judgement further EEL operations may continue or have to be stopped.
 *
 * @param[in]      ---
 *
 * @return         function return
 *                 - R_EEL_FLG_OK (the status as OK or a warning)
 *                 - R_EEL_FLG_ERROR (the status is an error)
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_err_flg_t R_EEL_SFct_ErrStatCheckError_CurProc (void)
{
    r_eel_err_flg_t ret;

    ret = R_EEL_SFct_ErrStatCheckError (g_eel_str.curPId_enu);

    return (ret);
}


/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_ErrStatCheckError
 *********************************************************************************************************************/
/**
 * Function to judge if the given process status is an error or a warning. Depending on this
 * judgement further EEL operations may continue or have to be stopped.
 *
 * @param[in]      pid - PID of the process which status is to check
 *
 * @return         function return
 *                 - R_EEL_FLG_OK    (the status as OK or a warning)
 *                 - R_EEL_FLG_ERROR (the status is an error)
 */
/*********************************************************************************************************************/
r_eel_err_flg_t R_EEL_SFct_ErrStatCheckError (r_eel_process_id_t pid)
{
    r_eel_err_flg_t ret;
    r_eel_status_t  stat;

    stat = g_eel_str.sm_str[pid].rStat_enu;                                      /* PRQA S 3689 */

    /* The error and warning values are sorted according to the significance boundary between
       error and warning is defined by the R_EEL_ERR value */
    if (R_EEL_ERR <= stat)
    {
        ret = R_EEL_FLG_ERROR;
    }
    else
    {
        ret = R_EEL_FLG_OK;
    }

    return (ret);
} /* R_EEL_SFct_ErrStatCheckError */


/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_FlashConvertWriteStatus2ProcessStatus
 *********************************************************************************************************************/
/**
 * Function to convert the EEL internal stored  Flash operation result into a process status
 * result.
 *
 * @param[in]      ---
 *
 * @return         function return
 *                 - R_EEL_ERR_FLASH_ERROR (Flash error)
 *                 - R_EEL_ERR_INTERNAL    (Internal error, should never happen)
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_status_t R_EEL_SFct_FlashConvertWriteStatus2ProcessStatus (void)
{
    r_eel_status_t ret;
    r_fdl_status_t fStat;

    fStat = g_eel_str.pCurP_pstr->flashStatus_enu;
    ret = R_EEL_OK;

    if (R_FDL_OK != fStat)
    {
        if (R_FDL_ERR_WRITE == fStat)
        {
            ret = R_EEL_ERR_FLASH_ERROR;
        }
        else
        {
            /* All errors that should never happen result in internal error */
            ret = R_EEL_ERR_INTERNAL;
        }
    }

    return (ret);
} /* R_EEL_SFct_FlashConvertWriteStatus2ProcessStatus */


/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_FlashOpResultCheck_Write
 *********************************************************************************************************************/
/**
 * Flash write operation result handling.
 * - Set the process status according to the Flash write result
 * - Return information if an error occurred during the write or OK/Warning
 *
 * @param[in]      ignFlashError - Ignore Flash write error. Just internal errors are considered
 *
 * @return         function return
 *                 - R_EEL_FLERR_CHK_OK     (No error occurred in the Write operation)
 *                 - R_EEL_FLERR_CHK_ERR    (An error occurred in the Write operation)
 *                 - R_EEL_FLERR_CHK_IGNORE (A Flash error occurred in the Write operation which will be ignored)
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_flash_error_chk_t R_EEL_SFct_FlashOpResultCheck_Write (r_eel_flag_t ignFlashError)
{
    r_eel_status_t          res;
    r_eel_flash_error_chk_t ret;

    /* Update the process error according to the Write operation result */
    res = R_EEL_SFct_FlashConvertWriteStatus2ProcessStatus ();

    /* Ignore write error in case of I0/I1 write, if it was already written */
    if ( (R_EEL_TRUE == ignFlashError) && (R_EEL_ERR_FLASH_ERROR == res) )
    {
        /* Ignore flash error means: Set "fix done" status and set appropriate return value */
        (void)R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (R_EEL_ERR_FIX_DONE);

        ret = R_EEL_FLERR_CHK_IGNORE;
    }
    else
    {
        ret = R_EEL_FLERR_CHK_OK;

        if (R_EEL_OK != res)
        {
            (void)R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (res);

            /* On process error, additionally return error status */
            if ( R_EEL_FLG_ERROR == R_EEL_SFct_ErrStatCheckError_CurProc () )
            {
                ret = R_EEL_FLERR_CHK_ERR;
            }
        }
    }

    return (ret);
} /* R_EEL_SFct_FlashOpResultCheck_Write */



/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_FlashConvertEraseStatus2ProcessStatus
 *********************************************************************************************************************/
/**
 * Function to convert the EEL internal stored Flash operation result into a process status
 * result.
 *
 * @param[in]      ---
 *
 * @return         function return
 *                 - R_EEL_ERR_FLASH_ERROR  (Resulting from Erase error)
 *                 - R_EEL_ERR_INTERNAL     (Internal error, should never happen)
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_status_t R_EEL_SFct_FlashConvertEraseStatus2ProcessStatus (void)
{
    r_eel_status_t ret;
    r_fdl_status_t fStat;

    fStat = g_eel_str.pCurP_pstr->flashStatus_enu;
    ret = R_EEL_OK;

    if (R_FDL_OK != fStat)
    {
        /* Erase error is handled inside the library process,
           all others result in internal error */
        if (R_FDL_ERR_ERASE == fStat)
        {
            ret = R_EEL_ERR_FLASH_ERROR;
        }
        else
        {
            ret = R_EEL_ERR_INTERNAL;
        }
    }

    return (ret);
} /* R_EEL_SFct_FlashConvertEraseStatus2ProcessStatus */

/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_FlashConvertBitCheckStat2ProcessStat
 *********************************************************************************************************************/
/**
 * Function to convert the EEL internal stored Flash operation result into a process status
 * result.
 *
 * @param[in]      ---
 *
 * @return         function return
 *                 - R_EEL_OK           (No bit check error)
 *                 - R_EEL_ERR_FIX_DONE (Bit error requires fix actions (Refresh))
 *                 - R_EEL_ERR_INTERNAL (Internal error, should never happen)
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_status_t R_EEL_SFct_FlashConvertBitCheckStat2ProcessStat (void)
{
    r_eel_status_t ret;
    r_fdl_status_t fStat;

    fStat = g_eel_str.pCurP_pstr->flashStatus_enu;

    if (R_FDL_OK == fStat)
    {
        ret = R_EEL_OK;
    }
    else if ( (R_FDL_ERR_ECC_SED == fStat) || (R_FDL_ERR_ECC_DED == fStat) )
    {
        ret = R_EEL_ERR_FIX_DONE;
    }
    else
    {
        ret = R_EEL_ERR_INTERNAL;
    }

    return (ret);
} /* R_EEL_SFct_FlashConvertBitCheckStat2ProcessStat */


/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_FlashOpResultCheck_BitCheck
 *********************************************************************************************************************/
/**
 * Flash bit check operation result handling.  \n
 * Set a process status according to the Flash bit check result.
 *
 * @param[in]      ---
 *
 * @return         function return
 *                 - R_EEL_OK           (No bit check error)
 *                 - R_EEL_ERR_FIX_DONE (Bit error requires fix actions (Refresh))
 *                 - R_EEL_ERR_INTERNAL (Internal error, should never happen)
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_status_t R_EEL_SFct_FlashOpResultCheck_BitCheck (void)
{
    r_eel_status_t res;

    res = R_EEL_SFct_FlashConvertBitCheckStat2ProcessStat ();
    res = R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (res);

    return (res);
}


/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_ProcessErrorReset
 *********************************************************************************************************************/
/**
 * Reset the process status to R_EEL_OK.
 *
 * @param[in]      pID - ID of the process to be updated
 *
 * @return         ---
 */
/*********************************************************************************************************************/
void R_EEL_SFct_ProcessErrorReset (r_eel_process_id_t pID)
{
    g_eel_str.sm_str[pID].rStat_enu = R_EEL_OK;                                     /* PRQA S 3689 */

    /* On the SV process, also the operation status must be reset */
    if (R_EEL_PR_SV == pID)
    {
        g_eel_str.ds_str.backgroundStatus_enu = R_EEL_OK;
    }
}

/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_ProcessErrorUpdate
 *********************************************************************************************************************/
/**
 * Update process status with the given value. \n
 * In error case, branch to the given error state \n
 * Furthermore, in case of supervision process, set the background status in case of warnings
 *
 * @param[in]      pID  - process ID of the currently executed operation
 * @param[in]      stat - status to be set
 * @param[in]      errState - state to branch in case of errors
 *
 * @return         pStat - error status, resulting from the error priority judgement
 */
/*********************************************************************************************************************/
r_eel_status_t R_EEL_SFct_ProcessErrorUpdate (r_eel_process_id_t pID, r_eel_status_t stat, r_eel_pfct errState)
{
    if (R_EEL_OK != stat)
    {
        /* Judge warning/error priority
           The errors/warnings are sorted according to the priority. A higher priority always
           overrides a lower priority. Basically only warnings can be overridden as errors lead to
           operations abort */
        if (g_eel_str.sm_str[pID].rStat_enu < stat)                                                 /* PRQA S 3689 */
        {
            g_eel_str.sm_str[pID].rStat_enu = stat;                                                 /* PRQA S 3689 */

            /* - All process errors lead to switching process error status
               - Special handling on SV process warnings:
                 Warnings require to update the backgroundStatus variable to signal the variable on
                 R_EEL_GetDriverStatus... Errors are treated by SUPV Run */
            if ( R_EEL_FLG_ERROR == R_EEL_SFct_ErrStatCheckError (pID) )
            {
                g_eel_str.sm_str[pID].nextState_pfct = errState;
            }
            else
            {
                if (R_EEL_PR_SV == pID)
                {
                    g_eel_str.ds_str.backgroundStatus_enu = stat;
                }
            }
        }
    }

    return (g_eel_str.sm_str[pID].rStat_enu);
} /* R_EEL_SFct_ProcessErrorUpdate */



/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState
 *********************************************************************************************************************/
/**
 * Update process status of the current process with the given value. \n
 * In error case, branch to the process default error state \n
 *
 * @param[in]      stat - status to be set
 *
 * @return         pStat - error status, resulting from the error priority judgement
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_status_t R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (r_eel_status_t stat)
{
    r_eel_process_id_t pID;
    r_eel_pfct         errState;
    r_eel_status_t     retStat;

    pID = g_eel_str.curPId_enu;

    /* ----- Select the default error state ----- */
    /* First check if READ process is active as READ has the highest priority*/
    /* and READ may interrupt any other ongoing process independent of g_eel_str.processLock_enu*/
    if (R_EEL_PR_RE == pID)
    {
        errState = R_EEL_SM_READ_START;
    }
    /* Then check if a sub-process is active */
    /* "set invalid" and "set active" are always performed with g_eel_str.processLock_enu set*/
    /* Thus "set invalid" and "set active" may not be interrupted by a higher priority process*/
    else if (R_EEL_SM_IDLE != g_eel_str.opSI_str.subProcessErrReturn_pfct)
    {
        errState = R_EEL_SM_SET_INVALID_END;
    }
    else if (R_EEL_SM_IDLE != g_eel_str.opSA_str.subProcessErrReturn_pfct)
    {
        errState = R_EEL_SM_SET_ACTIVE_END;
    }
    /* Then check the process beginning with the higher priority process */
    else if (R_EEL_PR_PR == pID)
    {
        errState = R_EEL_SM_PREP_FINISH;
    }
    else if (R_EEL_PR_RF == pID)
    {
        errState = R_EEL_SM_REFR_FINISH;
    }
    else if (R_EEL_PR_FO == pID)
    {
        errState = R_EEL_SM_FORMAT_FINISH;
    }
    else if (R_EEL_PR_SV == pID)
    {
        errState = R_EEL_SM_SUPV_RUN;
    }
    else /* Default path for R_EEL_PR_WI, R_EEL_PR_WT, R_EEL_PR_WR */
    {
        errState = R_EEL_SM_WRITE_FINISH;
    }

    retStat = R_EEL_SFct_ProcessErrorUpdate (pID, stat, errState);

    return (retStat);
} /* R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState */


/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_ActivateProcess
 *********************************************************************************************************************/
/**
 * Activate a process by setting the active flag, next state to execute and reset the status.
 *
 * @param[in]      pID - ID of the process to be updated
 * @param[in]      sID - next state to execute
 *
 * @return         ---
 */
/*********************************************************************************************************************/
void R_EEL_SFct_ActivateProcess (r_eel_process_id_t pID, r_eel_pfct sPFCT)
{
    g_eel_str.sm_str[pID].active_enu       = R_EEL_TRUE;                            /* PRQA S 3689 */
    g_eel_str.sm_str[pID].nextState_pfct   = sPFCT;                                 /* PRQA S 3689 */
    R_EEL_SFct_ProcessErrorReset (pID);
}



/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_ConvertProcID2WriteProcID
 *********************************************************************************************************************/
/**
 * Converts a given process ID to a write process number.
 *
 * @param[in]      pid - ID of the process to be converted
 *
 * @return         Write process ID
 */
/*********************************************************************************************************************/
r_eel_write_proc_data_t R_EEL_SFct_ConvertProcID2WriteProcID (r_eel_process_id_t pid)
{
    r_eel_write_proc_data_t ret;

    if (R_EEL_PR_WT == pid)         /* Normal write */
    {
        ret = R_EEL_WDATA_WT;
    }
    else if (R_EEL_PR_WI == pid)    /* Write immediate */
    {
        ret = R_EEL_WDATA_WI;
    }
    else if (R_EEL_PR_WR == pid)    /* write refresh */
    {
        ret = R_EEL_WDATA_WR;
    }
    else                            /*default should never be reached */
    {
        ret = R_EEL_WDATA_END;
    }

    return (ret);
} /* R_EEL_SFct_ConvertProcID2WriteProcID */


/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_ConvertProcessID2CommandNo
 *********************************************************************************************************************/
/**
 * Converts a given process ID to the command number.
 *
 * @param[in]      pId - ID of the process to be converted
 *
 * @return         Command number
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_operation_id_t R_EEL_SFct_ConvertProcessID2CommandNo (r_eel_process_id_t pId)
{
    r_eel_operation_id_t ret;

    /* Safe default operation */
    ret = R_EEL_OP_RE;

    switch (pId)
    {
        case R_EEL_PR_RE:         /* Read process */
        {
            /* Default operation */
            break;
        }

        case R_EEL_PR_WT:         /* Write process */
        {
            ret = R_EEL_OP_WT;
            break;
        }

        case R_EEL_PR_WI:         /* Write immediate process */
        {
            ret = R_EEL_OP_WTIMM;
            break;
        }

        case R_EEL_PR_FO:         /* Format process */
        {
            ret = R_EEL_OP_FO;
            break;
        }

        default:                /* Default should never be reached */
            break;
    } /* switch */

    return (ret);
} /* R_EEL_SFct_ConvertProcessID2CommandNo */



/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_Calc_FreeSpace
 *********************************************************************************************************************/
/**
 * Calculates the free space in the ring buffer. This internal function does not subtract the space
 * required library internal for resolving the pool full situation. \n
 * Space <EEL_REF_OFF_DS + 2 bytes in a block is ignored as no more new DS write can be started in
 * this block.
 *
 * @param[in]      ---
 *
 * @return         Free space in bytes
 */
/*********************************************************************************************************************/
uint32_t R_EEL_SFct_Calc_FreeSpace (void)
{
    uint32_t            spaceTmp;
    uint32_t            space;
    uint16_t            blkCnt;
    uint16_t            blk;
    r_eel_blockstatus_t blkStat;

    spaceTmp = R_EEL_PFct_Calc_BlkFreeSpace (g_eel_str.wp_u32, g_eel_str.rp_u32);
    if (R_EEL_REF_OFF_DS  <= spaceTmp)
    {
        space = spaceTmp;
    }
    else
    {
        /* Space < R_EEL_REF_OFF_DS + 2 Bytes is not usable */
        space = 0uL;
    }

    /* N: number of prepared blocks
    Space = N * blocksize - N * ( block header size + separator REF-zone/Data zone ) */
    blkCnt = g_eel_str.blkCntPrep_u16;

    /* If rp points to a prepared block, we are within set active process. Here rp/wp are already
       updated but the block status not. So, we reduce #prepared blocks by 1 */
    blk = R_EEL_PFct_Calc_Add2vBlk (g_eel_str.rp_u32);
    blkStat = R_EEL_SFct_Calc_BlkStat (blk);
    if (R_EEL_BLKSTAT_PREPARED == blkStat)
    {
        blkCnt--;
    }

    space += ( blkCnt * R_EEL_PFct_Calc_BlkSpace () );

    return (space);
} /* R_EEL_SFct_Calc_FreeSpace */


/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_Calc_BlkStat
 *********************************************************************************************************************/
/**
 * Calculate the status of a given block from the status table in RAM.
 *
 * @param[in]      blk - given block number
 *
 * @return         status return
 *                 - R_EEL_BLKSTAT_ACTIVE
 *                 - R_EEL_BLKSTAT_PREPARED
 *                 - R_EEL_BLKSTAT_INVALID
 */
/*********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule --- (QAC message 1482)
 * Reason:       cast non constant to an enum type
 * Verification: read value after arithmetic operations is enum type (formerly stored as such)
 *********************************************************************************************************************/
R_EEL_STATIC r_eel_blockstatus_t R_EEL_SFct_Calc_BlkStat (uint16_t blk)
{
    uint32_t idx;
    uint32_t bIdx;
    uint8_t  data;

    idx  = ( (uint32_t)blk >> 2uL );                /* Each byte covers 4 blocks (2bit/block) */
    bIdx = ( (uint32_t)blk & 0x3uL );
    bIdx = ( (uint32_t)bIdx << 1uL );

    data = g_eel_str.blkStat_au08[idx];                                         /* PRQA S 3689 */
    data = (data >> bIdx);
    data = (data & 0x03);

    return ( (r_eel_blockstatus_t)data );                                       /* PRQA S 1482 */
}

/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_Init_BlkStatCnt
 *********************************************************************************************************************/
/**
 * We count invalid and prepared blocks in the passive pool (outside the 1st and last active
 * block).  \n
 * This information is important for the block supervision. Hereby, invalid/prepared blocks
 * inside the active pool are irrelevant, as these cannot be filled with data. \n
 *
 * This function initializes the block status counters by reading the block status table in RAM.
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SFct_Init_BlkStatCnt (void)
{
    uint16_t            blk;
    r_eel_blockstatus_t blkStat;

    g_eel_str.blkCntPrep_u16 = 0uL;
    g_eel_str.blkCntInv_u16  = 0uL;

    blk = g_eel_str.blkActive_u16;
    do
    {
        blk = R_EEL_SFct_Calc_NextBlk_Any (blk, R_EEL_BLK_NEXT);
        blkStat = R_EEL_SFct_Calc_BlkStat (blk);

        if (R_EEL_BLKSTAT_PREPARED == blkStat)      /* Prepared block found */
        {
            (g_eel_str.blkCntPrep_u16)++;
            /* Only the block between the last prepared block and active range tail
               can be prepared, so is counted as pre-parable invalid block. Other invalid
               blocks in the passive range don't count as they bill be shifted through the
               active range and at the active range tail they will occur as invalid blocks
               again */
            g_eel_str.blkCntInv_u16 = 0;
        }
        else
        {
            if (R_EEL_BLKSTAT_INVALID == blkStat) /* Invalid block found */
            {
                (g_eel_str.blkCntInv_u16)++;
            }
        }
    }
    while (blkStat != R_EEL_BLKSTAT_ACTIVE);
} /* R_EEL_SFct_Init_BlkStatCnt */


/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_SetBlkStat
 *********************************************************************************************************************/
/**
 * Set the status of a given block in the status table in RAM.
 *
 * @param[in]      blk  - given block number
 * @param[in]      stat - block status to set (Any member of the r_eel_blockstatus_t enumeration)
 *
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SFct_SetBlkStat (uint16_t blk, r_eel_blockstatus_t stat)
{
    uint32_t            idx;
    uint32_t            bIdx;
    uint32_t            data;
    r_eel_blockstatus_t curStat;

    curStat = R_EEL_SFct_Calc_BlkStat (blk);

    idx  = ( (uint32_t)blk >> 2uL );                /* Each byte covers 4 blocks (2bit/block) */
    bIdx = ( (uint32_t)blk & 0x3uL );
    bIdx = ( (uint32_t)bIdx << 1uL );

    data = (uint32_t)(g_eel_str.blkStat_au08[idx]);                              /* PRQA S 3689 */
    data = ( data & ( ~(0x3uL << bIdx) ) );
    data = ( data | ( ( (uint32_t)stat ) << bIdx ) );

    g_eel_str.blkStat_au08[idx] = (uint8_t)data;                                  /* PRQA S 3689 */

    /* ------------- Update number of prepared / invalid blocks ------------- */
    if (R_EEL_BLKSTAT_ACTIVE == stat)                /* Set Active: Prepared --> Active */
    {
        (g_eel_str.blkCntPrep_u16)--;
    }
    else if (R_EEL_BLKSTAT_PREPARED == stat)         /* Prepare: Invalid --> Prepared */
    {
        (g_eel_str.blkCntPrep_u16)++;
        (g_eel_str.blkCntInv_u16)--;
    }
    else /* invalid */
    {
        if (R_EEL_BLKSTAT_PREPARED == curStat)       /* Set Active failed: Prepare --> Invalid */
        {
            (g_eel_str.blkCntPrep_u16)--;
        }
        else                                        /* Refresh: Active --> Invalid */
        {                                           /* Supv, no Refresh necessary: Inv -> Inv */
            (g_eel_str.blkCntInv_u16)++;
        }
    }
} /* R_EEL_SFct_SetBlkStat */



/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_Calc_NextBlk_Any
 *********************************************************************************************************************/
/**
 * Function to calculate the previous/next block number of a given block. This function returns
 * the previous/next block number independent from this blocks status.
 *
 * @param[in]      curBlk    - number of the current block, which neighbour is calculated
 * @param[in]      blkOffset - R_EEL_BLK_NEXT: get next block number
 *                           - R_EEL_BLK_PREV: Get previous block number
 * @return         Calculated previous/next block number
 */
/*********************************************************************************************************************/
R_EEL_STATIC uint16_t R_EEL_SFct_Calc_NextBlk_Any (uint16_t curBlk, r_eel_blockoffset_t blkOffset)
{
    uint16_t ret;

    if (R_EEL_BLK_NEXT == blkOffset)
    {
        /* Calculate next block number */
        if ( curBlk == (g_eel_str.vPoolSizeNoVblks_u16 - 1) )
        {
            /* 1st block in the ring buffer */
            ret = 0u;
        }
        else
        {
            ret = curBlk + 1u;
        }
    }
    else /* R_EEL_BLK_PREV */
    {
        /* Calculate previous block number */
        if (curBlk == 0u)
        {
            /* Last block in the ring buffer */
            ret = (g_eel_str.vPoolSizeNoVblks_u16 - 1);
        }
        else
        {
            ret = curBlk - 1;
        }
    }

    return (ret);
} /* R_EEL_SFct_Calc_NextBlk_Any */


/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_Calc_NextBlk_DedicatedStatus
 *********************************************************************************************************************/
/**
 * Get the previous/next block with a dedicated status relative to the given block.
 *
 * @param[in,out]  addBlk          - address of the variable containing the block number of the
 *                                   given block. Updated by this function
 * @param[in]      blkStatOK       - dedicated status which is searched
 * @param[in]      blkStatErr      - search abort condition: If a block in the search has this
 *                                   status, we have an error
 * @param[in]      searchBlkLimit  - search abort condition: last block to search. If we reach
 *                                   this block, we have an error
 * @param[in]      blkOff          - R_EEL_BLK_NEXT: get next block number
 *                                 - R_EEL_BLK_PREV: get previous block number
 *
 * @return         function result return
 *                 - R_EEL_FLG_OK    (Next block found)
 *                 - R_EEL_FLG_ERROR (No next block with the dedicated status found)
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_err_flg_t R_EEL_SFct_Calc_NextBlk_DedicatedStatus (uint16_t * addBlk,
                                                                      r_eel_blockstatus_t blkStatOK,
                                                                      r_eel_blockstatus_t blkStatErr,
                                                                      uint16_t searchBlkLimit,
                                                                      r_eel_blockoffset_t blkOff)
{
    r_eel_err_flg_t     errFlg;
    r_eel_flag_t        endLoop;
    uint16_t            blk;
    r_eel_blockstatus_t blkStat;

    blk = (*addBlk);
    errFlg  = R_EEL_FLG_ERROR;

    /* Check all blocks until the search limit is reached. Loop Limit = Error */
    endLoop = R_EEL_FALSE;

    blk     = R_EEL_SFct_Calc_NextBlk_Any (blk, blkOff);
    while ( (R_EEL_FALSE == endLoop) &&
            (blk != searchBlkLimit) )
    {
        blkStat = R_EEL_SFct_Calc_BlkStat (blk);

        /* Check break condition: searched block status found*/
        if (blkStatOK  == blkStat)
        {
            errFlg = R_EEL_FLG_OK;
            endLoop = R_EEL_TRUE;
            (*addBlk) = blk;
        }
        else
        {
            /* Check break condition: error wrong block status found*/
            if (blkStatErr == blkStat)
            {
                endLoop = R_EEL_TRUE;
            }
        }

        blk     = R_EEL_SFct_Calc_NextBlk_Any (blk, blkOff);
    }



    return (errFlg);
} /* R_EEL_SFct_Calc_NextBlk_DedicatedStatus */



/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_Calc_NextBlk_ActPrep
 *********************************************************************************************************************/
/**
 * Get the previous/next active or prepared block.
 * Note: The function assumes to run in a consistent ring buffer which means that we have at least two active or one
 *       active and one prepared block. This is given in the considered calls of the function
 *
 * @param[in,out]  addBlk         - address of the variable containing the block number of the
 *                                  given block. Updated by this function
 * @return         ---
 */
/*********************************************************************************************************************/
void R_EEL_SFct_Calc_NextBlk_ActPrep (uint16_t * addBlk)
{
    r_eel_flag_t        endLoop;
    uint16_t            blk;
    uint16_t            searchBlkLimit;
    r_eel_blockstatus_t blkStat;

    blk = (*addBlk);
    searchBlkLimit = blk;
    endLoop = R_EEL_FALSE;

    do
    {
        blk     = R_EEL_SFct_Calc_NextBlk_Any (blk, R_EEL_BLK_NEXT);

        /* If we reached the search limit no active or prepared block is available */
        if (blk == searchBlkLimit)
        {
            endLoop = R_EEL_TRUE;
        }
        else
        {
            blkStat = R_EEL_SFct_Calc_BlkStat (blk);
            if ( (R_EEL_BLKSTAT_ACTIVE    == blkStat) ||
                 (R_EEL_BLKSTAT_PREPARED  == blkStat) )
            {
                endLoop = R_EEL_TRUE;
                (*addBlk) = blk;
            }
        }
    }
    while (R_EEL_FALSE == endLoop);

} /* R_EEL_SFct_Calc_NextBlk_ActPrep */


/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_Prepare_StartProcess
 *********************************************************************************************************************/
/**
 * Function to start the prepare process for a given block.
 *
 * @param[in]      blk - block to prepare
 *
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SFct_Prepare_StartProcess (uint16_t blk)
{
    g_eel_str.opPr_str.blk_u16 = blk;

    R_EEL_SFct_ActivateProcess (R_EEL_PR_PR, R_EEL_SM_PREP_START);
}



/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_Write_InitProcess
 *********************************************************************************************************************/
/**
 * Function to initialize the write process variables.
 *
 * @param[in]      pId        - write process ID
 * @param[in]      request    - pointer to the request structure
 * @param[in]      byteCnt    - number of bytes to write
 * @param[in]      srcAdd     - Data source address
 * @param[in]      invalidate - flag indicating if write intention is invalidation
 * @param[in]      idx        - ID-L table index of the ID to write
 *
 * @return         ---
 */
/*********************************************************************************************************************/
void R_EEL_SFct_Write_InitProcess (r_eel_write_proc_data_t wpId,
                                   r_eel_request_t * request,
                                   uint16_t id,
                                   uint16_t byteCnt,
                                   uint32_t srcAdd,
                                   r_eel_flag_t invalidate,
                                   uint16_t idx)
{
    r_eel_process_id_t pId;

    if (R_EEL_WDATA_WT == wpId)
    {
        pId = R_EEL_PR_WT;
        g_eel_str.op_str[R_EEL_OP_WT].req_pstr      = request;                                      /* PRQA S 3689 */
    }
    else if (R_EEL_WDATA_WI == wpId)
    {
        pId = R_EEL_PR_WI;
        g_eel_str.op_str[R_EEL_OP_WTIMM].req_pstr   = request;                                      /* PRQA S 3689 */
    }
    else /* R_EEL_WDATA_WR */
    {
        pId = R_EEL_PR_WR;
    }

    /* Reset the Write operation status just to be sure not to get a left-over status */
    g_eel_str.sm_str[pId].flashStatus_enu        = R_FDL_OK;

    g_eel_str.opWt_str[wpId].id_u16              = id;                                               /* PRQA S 3689 */
    g_eel_str.opWt_str[wpId].invalidate_enu      = invalidate;                                       /* PRQA S 3689 */
    g_eel_str.opWt_str[wpId].src_pu32            = srcAdd;                                           /* PRQA S 3689 */

    /* Setting IDXTableUpdate_enu here means the intention to write the DS. The value is checked...
       - On 1st write state: Check if higher prio Write in the meantime wrote the DS.
         Then the complete DS write is cancelled because this DS instance may not appear after the newer one
       - Before Updating the ID-X table: A higher prio DS write can have written the ID after this DS write has
          been started. Then, this DS is written (location before the newer DS) but the ID-X table is updated
          with the newer ID instance */
    g_eel_str.opWt_str[wpId].IDXTableUpdate_enu = R_EEL_TRUE;

    /* WR in limited mode might have no idx. However, extended features are already considered during
       length calculation in REFRESH */
    g_eel_str.opWt_str[wpId].idx_u16 = idx;                                                         /* PRQA S 3689 */
    if (R_EEL_ID_NOT_FOUND != idx)
    {
        byteCnt = R_EEL_Pfct_AdjustByteCnt_ExtFeatures (byteCnt, idx);
    }
    g_eel_str.opWt_str[wpId].byteCnt_u16      = byteCnt;                                            /* PRQA S 3689 */

    /* Extended features related variable initializations */
    #ifdef R_EEL_SUPPORT_EXT_FEATURES
        g_eel_str.opWt_str[wpId].fastSafeInvHandling_enu = R_EEL_INVTYPE_NONE;
        g_eel_str.opWt_str[wpId].writeCntSupport_enu     = R_EEL_FALSE;
        g_eel_str.opWt_str[wpId].writeCntValue_u32       = 0x00000000uL;
        g_eel_str.opWt_str[wpId].prevInstInvMrkAdd       = 0x00000000uL;
    #endif

} /* R_EEL_SFct_Write_InitProcess */



/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_Write_UpdateRpWp
 *********************************************************************************************************************/
/**
 * Function to update rp and wp and to set rp and wp of the write operation
 *
 * @param[out]     actBlk    - pointer to the variable, set to the active block, where
 *                             the REF zone entry is written. In case of
 *                             space<EEL_REF_OFF_DS+2 bytes, activation of the next block
 *                             might be necessary from the beginning
 * @param[out]     actBlkRwp - pointer to the variable, set to the RWP, where
 *                             the REF zone entry is written. In case of
 *                             space<EEL_REF_OFF_DS+2 bytes, forwarding the RWP might be necessary
 *
 * @return         indicating if further blocks are to be activated to write the DS
 *                 - R_EEL_TRUE  (Addition block to activate)
 *                 - R_EEL_FALSE (No more additional block to activate)
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_flag_t R_EEL_SFct_Write_UpdateRpWp (uint16_t * actBlk, uint32_t * actBlkRwp)
{
    uint16_t     cntBytesRU;
    r_eel_flag_t activateBlock;

    cntBytesRU = (uint16_t)R_EEL_PFct_RoundUpToWriteGranularity (g_eel_str.pCurWP_pstr->byteCnt_u16);

    /* Forward WP and RP for DS write. If we need to activate a new block, the block no.
       and RWP are returned */
    activateBlock = R_EEL_SFct_ForwardRpWp_DSWrite (actBlk, actBlkRwp, cntBytesRU);

    /* Backup WP to Write process data and forward WP */
    g_eel_str.pCurWP_pstr->wp_u32 = g_eel_str.wp_u32;
    g_eel_str.wp_u32 -= cntBytesRU;

    /* Backup RP to Write process data and forward RP */
    g_eel_str.pCurWP_pstr->rp_u32 = g_eel_str.rp_u32;
    g_eel_str.rp_u32 += R_EEL_REF_OFF_DS;

    return (activateBlock);
} /* R_EEL_SFct_Write_UpdateRpWp */


/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_Write_UpdateIDXTable
 *********************************************************************************************************************/
/**
 * Function to update the ID-X table on write finish. Additionally, eventually suspended lower
 * priority write processes are prevented to update the ID-X table, if they wanted to write
 * the same ID as the currently finished write process.
 *
 * @param[in]      ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SFct_Write_UpdateIDXTable (void)
{
    uint16_t tIdx, widx;

    /* Check if we may update the table */
    if (R_EEL_TRUE == g_eel_str.pCurWP_pstr->IDXTableUpdate_enu)
    {
        /* Update the table */
        tIdx  = g_eel_str.pCurWP_pstr->idx_u16;

        /* "tIdx < g_eel_str.RTCfg_pstr->IDLTabIdxCnt_u16" includes that tIdx is valid:
            "tIdx != R_EEL_ID_NOT_FOUND" */
        if (tIdx < g_eel_str.RTCfg_pstr->IDLTabIdxCnt_u16)
        {
            if ( 0u == (g_eel_str.RTCfg_pstr->IDXTab_pau16[tIdx]) )                                 /* PRQA S 0491 */
            {
                /* Update RAM table fill count if the RAM table entry is empty */
                (g_eel_str.opSv_str.ramTableFillCntIDFound_u16)++;
            }
            widx = R_EEL_PFct_ConvertRefAdd2WIdx (g_eel_str.pCurWP_pstr->rp_u32);
            g_eel_str.RTCfg_pstr->IDXTab_pau16[tIdx] = widx;                                        /* PRQA S 0491 */
        }

        /* Now we check if lower priority Writes wanted to write the same ID.
           The table update by these processes must be prevented */
        if ( (R_EEL_PR_WI == g_eel_str.curPId_enu) || (R_EEL_PR_WT == g_eel_str.curPId_enu) )
        {
            /* Immediate and normal write overrule Refresh Write */
            if ( (R_EEL_TRUE == g_eel_str.sm_str[R_EEL_PR_WR].active_enu)
                 && (tIdx == g_eel_str.opWt_str[R_EEL_WDATA_WR].idx_u16) )
            {
                g_eel_str.opWt_str[R_EEL_WDATA_WR].IDXTableUpdate_enu = R_EEL_FALSE;
            }

            if (R_EEL_PR_WI == g_eel_str.curPId_enu)
            {
                /* Immediate Write overrules normal write */
                if ( (R_EEL_TRUE == g_eel_str.sm_str[R_EEL_PR_WT].active_enu) &&
                     (tIdx == g_eel_str.opWt_str[R_EEL_WDATA_WT].idx_u16) )
                {
                    g_eel_str.opWt_str[R_EEL_WDATA_WT].IDXTableUpdate_enu = R_EEL_FALSE;
                }
            }
        }
    }
} /* R_EEL_SFct_Write_UpdateIDXTable */


/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_ForwardRpWp_DSWrite
 *********************************************************************************************************************/
/**
 * Function to forward RP and WP if in the current active block no more space is available to write the DS.
 * - Space required in the block:
 *   REF entry (16Bytes) + separator (4Bytes) + Data aligned to write granularity
 * - If not enough space is available, the EEL forwards to the next block
 *
 * @param[in]      actBlk    - Pointer to the variable, containing the active block
 * @param[in]      actBlkRp  - Pointer to the variable, containing the active blocks RP
 * @param[in]      byteCnt   - number of Bytes to write -- Must be round up!!! --
 *
 * @return         Function returns information if a new block need to be activated and RP / WP
 *                 have been forwarded
 *                 - R_EEL_FALSE (No new block need to be activated)
 *                 - R_EEL_TRUE  (A new block need to be activated)
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_flag_t R_EEL_SFct_ForwardRpWp_DSWrite (uint16_t * actBlk, uint32_t * actBlkRwp, uint32_t byteCntRU)
{
    uint32_t     rp;
    uint32_t     rpOld;
    uint32_t     space,
                 dsTotalSize;
    uint16_t     blk;
    r_eel_flag_t activateBlk;

    activateBlk = R_EEL_FALSE;

    space       = R_EEL_PFct_Calc_BlkFreeSpace (g_eel_str.wp_u32, g_eel_str.rp_u32);
    dsTotalSize = R_EEL_REF_OFF_DS;
    dsTotalSize += byteCntRU; /* Byte count is already rounded up */

    if (dsTotalSize > space)
    {
        /* forward RP and WP to the next prepared block */
        blk   = (uint16_t)g_eel_str.blkActive_u16;

        /* We will not get an error here when forwarding the pointers as we have checked this before
           Write init (Compare DS size against GetSpace */
        (void)R_EEL_SFct_Calc_NextBlk_DedicatedStatus ( (&blk),
                                                        R_EEL_BLKSTAT_PREPARED,
                                                        R_EEL_BLKSTAT_ACTIVE,
                                                        g_eel_str.blkPrep_u16,
                                                        R_EEL_BLK_NEXT );

        /* Update RP and WP for the write operations after REF zone entry */
        rpOld               = g_eel_str.rp_u32;
        rp                  = R_EEL_PFct_Calc_vBlkDataAdd (blk, R_EEL_BLKHDATA_REFZ);

        g_eel_str.rp_u32    = rp;
        g_eel_str.wp_u32    = R_EEL_PFct_Calc_vBlkDataAdd (blk, R_EEL_BLKHDATA_DATAZ);

        /* Store the information required to activate the next block */
        activateBlk         = R_EEL_TRUE;
        (*actBlk)         = blk;
        (*actBlkRwp)      = rpOld;
    }

    return (activateBlk);
} /* R_EEL_SFct_ForwardRpWp_DSWrite */



/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_Refresh_StartProcess
 *********************************************************************************************************************/
/**
 * Function to start the Refresh process.
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SFct_Refresh_StartProcess (void)
{
    /* special case:
       we want to refresh the active block (because we have only one block)
       --> we must enforce refresh into the next block. We do this by setting space in the
           active block to zero */
    if (g_eel_str.blkOEActive_u16 == g_eel_str.blkActive_u16)
    {
        g_eel_str.wp_u32 = g_eel_str.rp_u32;
    }

    g_eel_str.opRf_str.updBlkOEActive_enu = R_EEL_FALSE;

    /* Reset refresh-Write process error which is checked in Refresh */
    R_EEL_SFct_ProcessErrorReset (R_EEL_PR_WR);

    if (R_EEL_OPERATION_MODE_LIMITED == g_eel_str.opMode_enu)
    {
        /* In limited mode, we initialize the REF search address */
        g_eel_str.opRf_str.lmRefAd_u32 = R_EEL_PFct_Calc_vBlkDataAdd (g_eel_str.blkOEActive_u16, R_EEL_BLKHDATA_REFZ);
    }
    else
    {
        /* in normal mode we initialize the tIdx to search */
        g_eel_str.opRf_str.tIdx_u16 = 0u;
    }


    R_EEL_SFct_ActivateProcess (R_EEL_PR_RF, R_EEL_SM_REFR_START);
} /* R_EEL_SFct_Refresh_StartProcess */





/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_Get_RefAdd_2_DSLen_LimMode
 *********************************************************************************************************************/
/**
 * Function to get the size of a DS to be refreshed. As possibly the IL-L table is not available, the size is
 * retrieved from the current block contents (using next REF entry DRP or using blank check)
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_status_t R_EEL_SFct_Get_RefAdd_2_DSLen_LimMode (uint32_t refAdd, uint16_t * dsSizeRet)
{
    r_eel_status_t iErr;
    uint32_t       wp, wpNext,
                   rp,
                   bcStart, bcCnt;
    uint16_t         dsSize;
    r_eel_flag_t     endLoop;
    r_eel_patcmp_t   sorPatMatch,
                     eor0PatMatch;
    r_eel_bcResult_t sorBc, bc;

    iErr = R_EEL_OK;

    dsSize = 0u;
    rp = refAdd;
    wp = R_EEL_PFct_Get_RefAdd2DataAdd (refAdd);

    /* if the REF entry has data */
    if (0uL != wp)
    {
        endLoop = R_EEL_FALSE;
        do
        {
            rp += R_EEL_REF_OFF_DS;
            bcStart   =  rp + R_EEL_REF_OFF_DS;     /* Default value is to start BC behind checked REF entry in case of DS
                                                       is not valid (completely written) */

            if (rp >= wp)   /* loop error break condition (separator not found), will later on end in fatal error */
            {
                endLoop = R_EEL_TRUE;
            }
            else
            {
                iErr = R_EEL_PFct_ReadDFlash_BCcmpPat (rp + R_EEL_REF_OFF_SOR, &sorPatMatch, &sorBc);
                if ( (R_EEL_OK == iErr) && (R_EEL_PATCMP_VALID == sorPatMatch) )
                {
                    iErr = R_EEL_PFct_ReadDFlash_cmpPatBC (rp + R_EEL_REF_OFF_EOR0, &eor0PatMatch);
                    if ( (R_EEL_OK == iErr) && (R_EEL_PATCMP_VALID == eor0PatMatch) )
                    {
                        wpNext = R_EEL_PFct_Get_RefAdd2DataAdd (rp);
                        if (0uL != wpNext)
                        {
                            dsSize = (uint16_t)(wp - wpNext);
                            endLoop = R_EEL_TRUE;
                        }
                        else
                        {
                            /* next DS without data ... continue checking next next DS */
                        }
                    }
                } /* if ( (R_EEL_OK == iErr) && (R_EEL_PATCMP_VALID == sorPatMatch) ) */
                else
                {
                    endLoop = R_EEL_TRUE;

                    if (R_EEL_BC_BLANK == sorBc)
                    {
                        /* Found separator indicated that no more DS is in the block. So do the BC from here */
                        bcStart = rp;
                    }
                }
            }
        }
        while (R_EEL_FALSE == endLoop);

        /* No DS with data found behind the REF entry. So, do blank check between last REF entry and the 1st
           written data to calculate the DS size */
        if ( (0u == dsSize) && (R_EEL_OK == iErr) )
        {
            /* Check possible DS size by blank check... we copy everything non blank
               Not checked: - Separator address (increased bcStart)
                            - data on wp address (must be copied anyhow as the min. data size is 1 word */
            bcStart += R_EEL_FDL_WRITESIZE;

            if (bcStart < wp)
            {
                bcCnt = (wp - bcStart) / R_EEL_FDL_WRITESIZE;

                iErr = R_EEL_PFct_BlankCheckDFlash (&bcStart, bcCnt, &bc);
                if (R_EEL_OK == iErr)
                {
                    if (R_EEL_BC_BLANK == bc)
                    {
                        dsSize = R_EEL_FDL_WRITESIZE;
                    }
                    else
                    {
                        dsSize = (uint16_t)( (wp - bcStart) + R_EEL_FDL_WRITESIZE );
                    }
                } /* if (R_EEL_OK == iErr ) */
            } /* if (bcStart < wp) */
            else if (wp == bcStart)
            {
                /* Only wp address word and this need not be checked */
                dsSize = R_EEL_FDL_WRITESIZE;
            }
            else
            {
                /* e.g. separator not found */
                iErr = R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (R_EEL_ERR_INTERNAL);
            }
        }
    }

    if (R_EEL_OK == iErr)
    {
        *dsSizeRet = dsSize;
    }

    return (iErr);
} /* R_EEL_SFct_Get_RefAdd_2_DSLen_LimMode */



/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_SetActive_StartProcess
 *********************************************************************************************************************/
/**
 * Function to start the sub-process Set Active. This process may be invoked from a Write process
 * or the Format process.
 *
 * @param          okRet      - master process state to return to on successful sub-process end
 * @param          errRet     - master process state to return to on sub-process error case end
 * @param          setActBlk  - block number to set active
 * @param          setActRp   - RWP value to write in the process
 *
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SFct_SetActive_StartProcess (r_eel_pfct okRet,
                                                     r_eel_pfct errRet,
                                                     uint16_t setActBlk,
                                                     uint32_t setActRp)
{
    g_eel_str.opSA_str.setActiveBlk_u16           = setActBlk;
    g_eel_str.opSA_str.setRwp_u32                 = setActRp;

    g_eel_str.opSA_str.a0FlashError               = R_EEL_FALSE;

    g_eel_str.pCurP_pstr->nextState_pfct          = R_EEL_SM_SET_ACTIVE_A0;
    g_eel_str.opSA_str.subProcessReturn_pfct      = okRet;
    g_eel_str.opSA_str.subProcessErrReturn_pfct   = errRet;
}


/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_SetInvalid_StartProcess
 *********************************************************************************************************************/
/**
 * Function to start the sub-process Set Invalid. This process may be invoked from a Prepare
 * process or the Startup process.
 *
 * @param          okRet     - master process state to return to on successful sub-process end
 * @param          errRet    - master process state to return to on sub-process error case end
 * @param          setInvBlk - block number to set invalid
 *
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SFct_SetInvalid_StartProcess (r_eel_pfct okRet,
                                                      r_eel_pfct errRet,
                                                      uint16_t setInvBlk)
{
    g_eel_str.opSI_str.setInvalidBlk_u16          = setInvBlk;

    g_eel_str.pCurP_pstr->nextState_pfct           = R_EEL_SM_SET_INVALID_I0;
    g_eel_str.opSI_str.subProcessReturn_pfct       = okRet;
    g_eel_str.opSI_str.subProcessErrReturn_pfct    = errRet;
}


/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_Supv_Judge_Blk_Stat
 *********************************************************************************************************************/
/**
 * Part of the state machine supervision process to judge block status resulting
 * from possible Prepare and Refresh process interruptions. \n
 *
 * On internal error during any Data Flash read (with blank check), the process error is updated
 * and the function returns with R_EEL_ERR_INTERNAL at the end. However, on internal error the
 * function is executed until end without internal error checking as the error does not end in read
 * from illegal addresses or latency by loops on wrong addresses. \n
 *
 * @param[in,out]  actBlk   - current active block
 * @param[in,out]  actBlkEC - current active block erase counter
 * @param[in]      blk      - block to check
 * @param[out]     pMrkInv  - flag buffer address:
 *                             - R_EEL_TRUE  (checked block shall be marked invalid)
 *                             - R_EEL_FALSE (checked block shall not be marked invalid)
 *
 * @return         A called sub-routine, reading Data Flash with blank check might end with
 *                 internal error on blank check.
 *                 - R_EEL_OK       (No error on Data Flash read)
 *                 - R_EEL_INTERNAL (Internal HW error during Data Flash read (blank check))
 */
/*********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule --- (QAC message 1474)
 * Reason:       bitwise operations with enumerations
 * Verification: ret can be only ok or internal error. Bit wise operations ensure setting of error while resetting to
 *               ok is excluded
 *********************************************************************************************************************/
R_EEL_STATIC r_eel_status_t R_EEL_SFct_Supv_Judge_Blk_Stat (uint16_t * actBlk,
                                                            uint32_t * actBlkEC,
                                                            uint16_t blk,
                                                            r_eel_flag_t * pMrkInv)
{
    r_eel_patcmp_t pPatMatch,
                   a0PatMatch,
                   i0PatMatch, i1PatMatch;
    uint32_t         add, add1,
                     blkEc;
    r_eel_flag_t     mrkInvalid;
    r_eel_status_t   ret;
    r_eel_bcResult_t bcA0,
                     bcI0, bcI1;

    mrkInvalid = R_EEL_FALSE;
    ret        = R_EEL_OK;

    /* Judge a possible invalid status */
    add   = R_EEL_PFct_Calc_vBlkDataAdd (blk, R_EEL_BLKHDATA_I0);
    ret  |= R_EEL_PFct_ReadDFlash_BCcmpPat (add, &i0PatMatch, &bcI0);           /* PRQA S 1474 */
    add1   = R_EEL_PFct_Calc_vBlkDataAdd (blk, R_EEL_BLKHDATA_I1);
    ret  |= R_EEL_PFct_ReadDFlash_BCcmpPat (add1, &i1PatMatch, &bcI1);          /* PRQA S 1474 */

    /* Exception: tool chain (e.g. FP5...) replace blank data by 0xFFFF */
    if ( (R_EEL_BC_WRITTEN == bcI0) && (R_EEL_BC_WRITTEN == bcI1) )
    {
        if ( (R_EEL_PATCMP_BLANK == i0PatMatch) && (R_EEL_PATCMP_BLANK == i1PatMatch) )
        {
            bcI0 = R_EEL_BC_BLANK;
            bcI1 = R_EEL_BC_BLANK;
        }
    }

    if ( (R_EEL_BC_BLANK == bcI0) && (R_EEL_BC_BLANK == bcI1) )
    {
        add  = R_EEL_PFct_Calc_vBlkDataAdd (blk, R_EEL_BLKHDATA_A0);
        ret  |= R_EEL_PFct_ReadDFlash_BCcmpPat (add, &a0PatMatch, &bcA0);       /* PRQA S 1474 */

        /* judge active status */
        if (R_EEL_PATCMP_VALID == a0PatMatch)
        {
            R_EEL_SFct_SetBlkStat (blk, R_EEL_BLKSTAT_ACTIVE);

            /* Check if the block is the latest active one */
            blkEc = R_EEL_PFct_Calc_BlockEC (blk);

            if ( blkEc >= (*actBlkEC) )
            {
                (*actBlkEC) = blkEc;
                (*actBlk)   = blk;
            }
        }
        else if (R_EEL_BC_BLANK == bcA0)
        {
            /* judge prepared status */
            add  = R_EEL_PFct_Calc_vBlkDataAdd (blk, R_EEL_BLKHDATA_P);
            ret  |= R_EEL_PFct_ReadDFlash_cmpPatBC (add, &pPatMatch);           /* PRQA S 1474 */

            if (R_EEL_PATCMP_VALID == pPatMatch)
            {
                R_EEL_SFct_SetBlkStat (blk, R_EEL_BLKSTAT_PREPARED);
            }
            else
            {
                /* Start set invalid process */
                mrkInvalid  = R_EEL_TRUE;
            }
        }
        else    /* A0 Pattern is invalid and not blank */
        {
            /* Start set invalid process */
            mrkInvalid  = R_EEL_TRUE;
        }
    }
    else
    {
        /* judge normal invalid status, I0 and I1 are zero or max 2 bit differ from zero */
        if ( (R_EEL_PATCMP_VALID == i0PatMatch) && (R_EEL_PATCMP_VALID == i1PatMatch) )
        {
            R_EEL_SFct_SetBlkStat (blk, R_EEL_BLKSTAT_INVALID);
        }
        else
        {
            /* Start set invalid process */
            mrkInvalid  = R_EEL_TRUE;
        }
    }

    *pMrkInv = mrkInvalid;

    return (ret);
} /* R_EEL_SFct_Supv_Judge_Blk_Stat */


/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_Supv_Run
 *********************************************************************************************************************/
/**
 * State machine supervision process function / process state main supervision loop. Here DS margin
 * check, prepare and refresh are supervised as well as bit error check. \n
 *
 * Consisting of:
 * - if margin check active
 *     - call margin check function
 * - else
 *     - set driver status unlocked
 * - if margin check no longer active
 *     - check refresh threshold
 *         - if refresh threshold violated, forward refresh pointer
 *     - if blocks to prepare
 *         - start prepare process
 *     - else if blocks to refresh
 *         - start refresh process
 *     - else
 *         - bit error check
 *         - if bit error, forwards refresh pointer
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_status_t R_EEL_SFct_Supv_Run (void)
{
    uint16_t blkPrep,
             lastBlk,
             blk;
    r_eel_blockstatus_t blkStat;
    r_eel_status_t      chkRes;
    r_eel_status_t      ret;
    r_eel_flag_t        lowerPrioOperation;

    ret = R_EEL_OK;
    lowerPrioOperation = R_EEL_TRUE;

    /********************************** Startup DS margin check *********************************/
    if (R_EEL_MRGCHK_ACTIVE == g_eel_str.opSv_str.dsMarginChk_enu)
    {
        /* Margin check may start a Write process. In this case, prepare / refresh are
           blocked until margin check is ready or suspended due to pool full */
        ret = R_EEL_SFct_Supv_Ensure_DS_Margin ();

        /* We parsed margin check on all DS's --> End the startup state */
        if (R_EEL_OK == ret)
        {
            if (R_EEL_MRGCHK_FINISHED == g_eel_str.opSv_str.dsMarginChk_enu)
            {
                R_EEL_SFct_SetDriverStatus (R_EEL_ACCESS_UNDEFINED, R_EEL_OPERATION_BUSY);
            }
            else /* Here we are active... suspended state is only set by SUPV as reaction on pool full */
            {
                /* Refreshing a DS or margin check of the next DS has higher priority */
                lowerPrioOperation = R_EEL_FALSE;
            }
        }
    }
    else if (R_EEL_MRGCHK_SUSPENDED == g_eel_str.opSv_str.dsMarginChk_enu)
    {
        /* Re-activate the check because we suspended it only one time for lower priority Prepare or Refresh due to pool
           full*/
        g_eel_str.opSv_str.dsMarginChk_enu = R_EEL_MRGCHK_ACTIVE;
    }
    else
    {
        /* Nothing to do because DS margin check has finished already */
    }

    /********************************** Normal operation routines ********************************/

    /* ----------- Prepare check / start ----------------------------------- */
    if ( (R_EEL_OK == ret) && (R_EEL_TRUE == lowerPrioOperation) )
    {
        blkPrep = g_eel_str.blkPrep_u16;
        if (blkPrep != g_eel_str.blkOEActive_u16)
        {
            lowerPrioOperation = R_EEL_FALSE;

            /* Forward the prepare block pointer to the next position */
            g_eel_str.blkPrep_u16 = R_EEL_SFct_Calc_NextBlk_Any (g_eel_str.blkPrep_u16, R_EEL_BLK_NEXT);

            /* Check if the Prepare loop has reached the loop limit (One complete Ring buffer
               loop). Then the pool could not be refreshed and is exhausted */
            if (g_eel_str.blkPrep_u16 == g_eel_str.opSv_str.prepLoopLimit_u16)
            {
                /* We set the SV process error.
                   On the next SV process call, the SV run function checks the error and will
                   react on it (lock the emulation) */
                ret = R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (R_EEL_ERR_POOL_EXHAUSTED);
            }
            else
            {
                /* If the loop check is off, we start it now */
                if (R_EEL_PREPLOOPLIMIT_OFF == g_eel_str.opSv_str.prepLoopLimit_u16)
                {
                    g_eel_str.opSv_str.prepLoopLimit_u16 = g_eel_str.blkPrep_u16;
                }

                /* Set driver operational status to busy because we do the prepare (Access status
                   is unchanged). Exception if due to pool full the prepare must be done first, we
                   remain in Startup */
                if (R_EEL_OPERATION_STARTUP != g_eel_str.ds_str.operationStatus_enu)
                {
                    R_EEL_SFct_SetDriverStatus (R_EEL_ACCESS_UNDEFINED, R_EEL_OPERATION_BUSY);
                }

                g_eel_str.opSv_str.lastPr_enu = R_EEL_PR_PR;

                /* Start the prepare process */
                R_EEL_SFct_Prepare_StartProcess (blkPrep);
            }
        }
    }

    if ( (R_EEL_OK == ret) && (R_EEL_TRUE == lowerPrioOperation) )
    {
        /* ----------- Refresh threshold check --------------------------------- */
        if ( (g_eel_str.RTCfg_pstr->vBlkRefreshThreshold_u16)
             > (g_eel_str.blkCntPrep_u16 + g_eel_str.blkCntInv_u16) )
        {
            /* If the number of "prepareable" blocks is >= Refresh threshold, we have to
               refresh additional blocks */

            /* Check that the pointer is not already forwarded */
            if (g_eel_str.blkRef_u16 == g_eel_str.blkOEActive_u16)
            {
                /* We set the Refresh pointer to the next not invalid block
                   R_EEL_SFct_Calc_NextBlk_ActPrep can rely on at least 2 active/prepared blocks.
                   Otherwise either the last prepare or startup would have failed */
                R_EEL_SFct_Calc_NextBlk_ActPrep ( &(g_eel_str.blkRef_u16) );
            }
        } /* if(   ( g_eel_str.RTCfg_pstr->vBlkRefreshThreshold_u16 ) ... */

        /* ----------- Refresh start --------------------------------------- */
        if (g_eel_str.blkRef_u16 != g_eel_str.blkOEActive_u16)
        {
            lowerPrioOperation = R_EEL_FALSE;

            if ( R_EEL_BLKSTAT_INVALID == R_EEL_SFct_Calc_BlkStat (g_eel_str.blkOEActive_u16) )
            {
                /* The block might already be invalid if an invalid block is migrating through
                   the active pool. In that case we just:
                   - call R_EEL_SFct_SetBlkStat on that block in order to update the invalid
                     counter
                   - forward blkOEActive_u16 to the next not block */

                R_EEL_SFct_SetBlkStat (g_eel_str.blkOEActive_u16, R_EEL_BLKSTAT_INVALID);

                g_eel_str.blkOEActive_u16 = R_EEL_SFct_Calc_NextBlk_Any (g_eel_str.blkOEActive_u16, R_EEL_BLK_NEXT);

            } /* if( R_EEL_BLKSTAT_INVALID == R_EEL_SFct_Calc_BlkStat( g_eel_str.blkOEActive_u16 ) ) */
            else
            {
                /* Set driver operational status to busy because we do the refresh (Access
                   status is unchanged)
                   Exception if due to pool full the prepare must be done first, we remain in
                   Startup */
                if (R_EEL_OPERATION_STARTUP != g_eel_str.ds_str.operationStatus_enu)
                {
                    R_EEL_SFct_SetDriverStatus (R_EEL_ACCESS_UNDEFINED, R_EEL_OPERATION_BUSY);
                }
                g_eel_str.opSv_str.lastPr_enu = R_EEL_PR_RF;

                /* Start the refresh process */
                R_EEL_SFct_Refresh_StartProcess ();
            } /* if( R_EEL_BLKSTAT_INVALID == R_EEL_SFct_Calc_BlkStat( g_eel_str.blk... - else */
        }
    } /* if( ( R_EEL_OK == ret ) && ( R_EEL_TRUE == lowerPrioOperation ) )  */


    /********************************** Bit error check in the idle phase ************************/

    /* ----------- Bit error check in the idle phase ----------------------- */
    if ( ( (R_EEL_OK == ret) && (R_EEL_TRUE == lowerPrioOperation) )
         && (R_EEL_MRGCHK_FINISHED == g_eel_str.opSv_str.dsMarginChk_enu) )  /* start bit check after mrg chk */
    {
        /* Set driver operational status to idle (Access status is unchanged) */
        R_EEL_SFct_SetDriverStatus (R_EEL_ACCESS_UNDEFINED, R_EEL_OPERATION_IDLE);

        /* Update/Reset the prepare loop limit for detection of exhausted pool by
           continuous refresh/prepare */
        R_EEL_PFct_PrepLoopLimitReset ();

        /* Do the bit check - This requires no handler call */
        R_EEL_FDLIF_BitCheck (g_eel_str.opSv_str.bitChkAdd_enu32);
        chkRes = R_EEL_SFct_FlashOpResultCheck_BitCheck ();
        if (R_EEL_OK == chkRes)
        {
            /* On OK forward to the next check address */
            g_eel_str.opSv_str.bitChkAdd_enu32 += R_EEL_FDL_WRITESIZE;

            /* Handle address overflow */
            lastBlk = g_eel_str.vPoolSizeNoVblks_u16 - 1u;
            if ( g_eel_str.opSv_str.bitChkAdd_enu32 > R_EEL_PFct_Calc_vBlkTopAdd (lastBlk) )
            {
                g_eel_str.opSv_str.bitChkAdd_enu32
                    = R_EEL_PFct_Calc_vBlkBaseAdd (0u);
            }

            /* Skip checking of invalid blocks as they have two relevant data
               words each which are updated on startup if they are weak. All other words
               in the block can and may have bit errors */
            blk = R_EEL_PFct_Calc_Add2vBlk (g_eel_str.opSv_str.bitChkAdd_enu32);
            blkStat = R_EEL_SFct_Calc_BlkStat (blk);
            if (R_EEL_BLKSTAT_INVALID == blkStat)
            {
                R_EEL_SFct_Calc_NextBlk_ActPrep (&blk);
                g_eel_str.opSv_str.bitChkAdd_enu32 = R_EEL_PFct_Calc_vBlkBaseAdd (blk);
            }
        }
        else if (R_EEL_ERR_FIX_DONE == chkRes)
        {
            /* On bit error do fix by refreshing the affected block. This is done by
               forwarding the refresh pointer one block and after we are idle again
               re-check if the failure is still there. If yes, we refresh the next
               block if no, we have refreshed the affected block.
               R_EEL_SFct_Calc_NextBlk_ActPrep can rely on at least 2 active/prepared blocks as
               the BG operation is idle and so, we must have prepared blocks */
            R_EEL_SFct_Calc_NextBlk_ActPrep ( &(g_eel_str.blkRef_u16) );
        }
        else /* R_EEL_ERR_INTERNAL */
        {
            ret = chkRes;
        }
    } /* if( ( R_EEL_OK == ret ) && ( R_EEL_TRUE == lowerPrioOperation ) )  */

    return (ret);
} /* R_EEL_SFct_Supv_Run */



/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_Supv_Ensure_DS_Margin
 *********************************************************************************************************************/
/**
 * function to loop through the ID-X table and to check if DS margin of the found DS is given.
 * This is the case if EOR is written. If not, initiate a DS copy.
 *
 * @param[out]     --
 * @return         A called sub-routine, reading Data Flash with blank check might end with
 *                 internal error on blank check.
 *                 - R_EEL_OK       (No error on Data Flash read)
 *                 - R_EEL_INTERNAL (Internal HW error during Data Flash read (blank check))
 */
/*********************************************************************************************************************/
R_EEL_STATIC r_eel_status_t R_EEL_SFct_Supv_Ensure_DS_Margin (void)
{
    r_eel_flag_t invalidatedData;
    uint32_t     refAdd,
                 srcAdd;
    uint16_t     tIdx,
                 id,
                 len;
    r_eel_chk_ds_t dsValid;
    r_eel_status_t iErr;

    tIdx = g_eel_str.opSv_str.curIdx_u16;
    iErr = R_EEL_OK;

    if (tIdx == g_eel_str.RTCfg_pstr->IDLTabIdxCnt_u16)
    {
        g_eel_str.opSv_str.dsMarginChk_enu = R_EEL_MRGCHK_FINISHED;
    }
    else
    {
        refAdd = R_EEL_PFct_ConvertTidx2RefAdd (tIdx);
        if (0u != refAdd)
        {
            /* Read the next table word index */
            iErr = R_EEL_SFct_Chk_DSValid (refAdd, &dsValid);

            if ( (R_EEL_OK == iErr) && (R_EEL_CHKDS_VALID_EOR_INCOMPLETE == dsValid) )
            /* We found a DS without margin --> Rewrite:
               We check the space condition as for normal Write operations (R_EEL_GetSpace), where we
               need to reserve space for pool full Refresh. So we may not use
               R_EEL_SFct_Calc_FreeSpace but use R_EEL_GetSpace which already considers the reserve
               space */
            {
                id = R_EEL_PFct_Get_RefAdd2ID (refAdd);

                /* Treat invalidated DS and normal DS differently */
                iErr = R_EEL_PFct_Chk_DSInvalidated (refAdd, tIdx, &invalidatedData);
                if (R_EEL_OK == iErr)
                {
                    if (R_EEL_FALSE == invalidatedData)
                    {
                        /* Get the DS length for later space calculation */
                        len = R_EEL_PFct_ConvertTIdx2Len (tIdx);
                    }
                    else
                    {
                        len = 0uL;
                    }

                    /* Start Write process */
                    (void)R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (R_EEL_ERR_FIX_DONE);

                    srcAdd = R_EEL_PFct_Get_RefAdd2DataAdd (refAdd);
                    R_EEL_SFct_Write_InitProcess (
                        R_EEL_WDATA_WR,                            /* Process to start */
                        R_EEL_REQUEST_POINTER_UNDEFINED,           /* request structure/R_EEL_NULL */
                        id,                                        /* id of the DS copy refresh */
                        len,                                       /* Data set size */
                        srcAdd,                                    /* Write source address */
                        invalidatedData,                           /* Invalidate? */
                        tIdx);                                     /* table index */


                    R_EEL_SFct_ActivateProcess (R_EEL_PR_WR, R_EEL_SM_WRITE_START);
                    g_eel_str.opSv_str.lastPr_enu = R_EEL_PR_WR;
                } /* if (R_EEL_OK == iErr) */
            } /* if( ( R_EEL_OK == iErr ) && ( R_EEL_CHKDS_VALID_EOR_INCOMPLETE == dsValid ) ) */
        }

        g_eel_str.opSv_str.curIdx_u16++;
    }

    return (iErr);
} /* R_EEL_SFct_Supv_Ensure_DS_Margin */


/*********************************************************************************************************************
 * Function name:  R_EEL_SFct_ForwardSUPVProcessState
 *********************************************************************************************************************/
/**
 * Forwards SUPV process state to the intended state, if the process is not already in SUPV_RUN
 * due to an error condition.
 *
 * @param[in]      state - destination state
 *
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SFct_ForwardSUPVProcessState (r_eel_pfct pfct)
{
    g_eel_str.sm_str[R_EEL_PR_SV].nextState_pfct = pfct;
}


/*********************************************************************************************************************
***********************************************************************************************************************
 * State machine functions
***********************************************************************************************************************
 *********************************************************************************************************************/


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Read_Start
 *********************************************************************************************************************/
/**
 * State machine read process state function to read a DS.
 * Consisting of:
 * - Initialize process variables
 * - Search the DS
 * - Read the data
 *
 * @param          ---
 * @return         ---
 *
 * Some called sub-routines, reading Data Flash with blank check might end with R_EEL_ERR_INTERNAL
 * on blank check. These result in a process error and EEL shut-down.
 *
 */
/*********************************************************************************************************************/
void R_EEL_SM_Read_Start (void)
{
    uint32_t readDest,
             dataAdd,
             refAdd;
    uint16_t readLen,
             readOff,
             readOffAlign,
             id,
             idx;
    r_eel_flag_t    inv;
    r_eel_status_t  iErr;
    r_eel_err_flg_t dummyFlg;

    /* -------------------------------- Find the DS -------------------------------------------- */
    id   = g_eel_str.op_str[R_EEL_OP_RE].req_pstr->identifier_u16;
    idx  = g_eel_str.opRe_str.idx_u16;

    iErr = R_EEL_SFct_FindValidDS (idx, id, &refAdd);
    if (R_EEL_OK == iErr)
    {
        /* An invalidated DS also results in "no instance" */
        if (0uL != refAdd)
        {
            iErr = R_EEL_PFct_Chk_DSInvalidated (refAdd, idx, &inv);
            if (R_EEL_TRUE == inv)
            {
                refAdd = 0uL;
            }
        }
    }

    if (R_EEL_OK == iErr)
    {
        if (0uL == refAdd)
        {
            (void)R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (R_EEL_ERR_NO_INSTANCE);
        }
        else
        {
            dataAdd = R_EEL_PFct_Get_RefAdd2DataAdd (refAdd);

            /* Adjust data address for the case of extended features in the DS */
            dataAdd -= ( (uint32_t)R_EEL_Pfct_AdjustByteCnt_ExtFeatures (0u, idx) );
            readDest = R_EEL_PFct_CastU08Ptr2Add (g_eel_str.op_str[R_EEL_OP_RE].req_pstr->address_pu08);

            #ifdef R_EEL_SUPPORT_EXT_FEATURES
                if (R_EEL_CMD_READ_WC == g_eel_str.op_str[R_EEL_OP_RE].req_pstr->command_enu)
                {
                    /* Read Write counter */
                    dataAdd += R_EEL_FDL_WRITESIZE;
                    readLen  = R_EEL_FDL_WRITESIZE;
                    readOff  = 0;
                }
                else
            #endif
            {

                readLen  = (g_eel_str.op_str[R_EEL_OP_RE].req_pstr->length_u16);
                readOff  = (g_eel_str.op_str[R_EEL_OP_RE].req_pstr->offset_u16);

                /* ----------------- Get REF Zone end of this block (Byte address) ----- */
                if (readOff != 0uL)
                {
                    readOffAlign = (uint16_t)( (uint32_t)readOff & ( ~(R_EEL_FDL_WRITESIZE - 1uL) ) );
                    dataAdd -= readOffAlign;                    /* Aligned part of the offset is subtracted */
                    dataAdd += (readOff - readOffAlign);        /* unaligned part is added. R_EEL_SFct_Read_Chk_Data uses this
                                                                   to define the amount of unaligned bytes to read */
                }
            }

            /* Read the data */
            R_EEL_SFct_Read_Chk_Data ( (&dataAdd),   /* *pSrcAdd    */
                                       readDest,     /* destAdd     */
                                       readLen,      /* lenBytes    */
                                       R_EEL_FALSE,  /* chk         */
                                       &dummyFlg );  /* chk result not evaluated */
        }
    }

    /* On internal error set within the process (e.g. based on a possible blank check
       problem) we return the error and lock the EEL */
    if (R_EEL_OK != iErr)
    {
        R_EEL_SFct_SetDriverStatus (R_EEL_ACCESS_LOCKED, R_EEL_OPERATION_PASSIVE);
    }

    /* Set the request error */
    g_eel_str.op_str[R_EEL_OP_RE].req_pstr->status_enu = g_eel_str.pCurP_pstr->rStat_enu; /* PRQA S 3689 */

    /* Terminate Read process */
    g_eel_str.sm_str[R_EEL_PR_RE].active_enu = R_EEL_FALSE;
} /* R_EEL_SM_Read_Start */

/*********************************************************************************************************************
 * Function name:  R_EEL_SM_WriteInc_Start
 *********************************************************************************************************************/
/**
 * State machine write process state function to start the incremental write process
 *
 * Consisting of:
 * - Check if the source data and destination data differ
 *   - If yes, continue normal write process
 *   - If no, finish the write process successfully
 *
 * @param          ---
 * @return         ---
 *
 * Some called sub-routines, reading Data Flash with blank check might end with R_EEL_ERR_INTERNAL
 * on blank check. This results in a process error.
 */
/*********************************************************************************************************************/
void R_EEL_SM_WriteInc_Start (void)
{
    uint32_t dataAdd,
             refAdd,
             srcAdd;
    uint16_t             idx, id,
                         readLen;
    r_eel_err_flg_t      chkStat;
    r_eel_flag_t         inv;
    r_eel_operation_id_t cmdId;
    r_eel_status_t       iErr;

    chkStat = R_EEL_FLG_ERROR;

    /* -------------------------------- Find the DS -------------------------------------------- */
    idx = g_eel_str.pCurWP_pstr->idx_u16;
    id = R_EEL_PFct_ConvertTIdx2Id (idx);

    iErr = R_EEL_SFct_FindValidDS (idx, id, &refAdd);

    /* R_EEL_SFct_FindValidDS might update the process error to R_EEL_ERR_INTERNAL caused by blank check
       operation in pattern reads. then we end with internal error */
    if (R_EEL_OK == iErr)
    {
        /* An invalidated DS also results in "no instance" */
        if (0uL != refAdd)
        {
            iErr = R_EEL_PFct_Chk_DSInvalidated (refAdd, idx, &inv);
            if (R_EEL_TRUE == inv)
            {
                refAdd = 0uL;
            }
        }
    }

    if (R_EEL_OK == iErr)
    {
        /* -------------------------------- Check the DS data against the source data ---------- */
        if (0uL != refAdd)
        /* A valid DS is found, now we compare source and DS data */
        {
            dataAdd =  R_EEL_PFct_Get_RefAdd2DataAdd (refAdd);
            dataAdd -= ( (uint32_t)R_EEL_Pfct_AdjustByteCnt_ExtFeatures (0u, idx) );

            readLen = R_EEL_PFct_ConvertTIdx2Len (idx);
            cmdId = R_EEL_SFct_ConvertProcessID2CommandNo (g_eel_str.curPId_enu);
            srcAdd = R_EEL_PFct_CastU08Ptr2Add (
                g_eel_str.op_str[cmdId].req_pstr->address_pu08);                  /* PRQA S 3689 */

            R_EEL_SFct_Read_Chk_Data ( (&dataAdd),             /* *pSrcAdd    */
                                       srcAdd,                  /* destAdd     */
                                       readLen,                 /* lenBytes    */
                                       R_EEL_TRUE,              /* chk */
                                       (&chkStat) );            /* check result */
        }

        /* on chkStat = R_EEL_OK we have nothing to do */
        if (R_EEL_FLG_OK == chkStat)
        {
            g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_WRITE_FINISH;
        }
        else
        {
            g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_WRITE_START;
        }
    } /* if( R_EEL_OK == ret ) */
} /* R_EEL_SM_WriteInc_Start */

/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Write_Start
 *********************************************************************************************************************/
/**
 * State machine write process state function to start the write process
 *
 * Consisting of:
 *   - Initialize process variables for normal write
 *   - check if REF zone write requires to activate a new block. If yes,
 *     - start sub-process to activate a new block
 *
 * Note: In case of Set Invalid sub-process finding A0 could nod be written or SOR could bot be written, the state
 *       is re-entered (Re-start DS write in the next vBlock.
 *
 * Some called sub-routines, reading Data Flash with blank check might end with R_EEL_ERR_INTERNAL
 * on blank check. This results in a process error.
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 13.7 (QAC message 2991, 2995)
 * Reason:       QAC claims that the variable is always true and if clause is always true. This is only because of
 *               pre-compile defines resulting in not compiled code
 * Verification: Checked that in the not compiled code the variable is updated
 *********************************************************************************************************************/
void R_EEL_SM_Write_Start (void)
{
    r_eel_flag_t   activateBlock;
    uint16_t       actBlk;
    uint32_t       actBlkRwp;
    r_eel_status_t chkSpace;
    r_eel_pfct     nextState;
    r_eel_status_t iErr;

    /* ------------ Default process initializations ---------------------------------------------------------------- */
    iErr = R_EEL_OK;

    /* We lock the process for block status modification and consistent REF-zone locking */
    g_eel_str.processLock_enu = g_eel_str.curPId_enu;

    /* If the flag is false, a higher priority Write already wrote the ID before this Write could execute the 1st step.
       So, this operation may not be executed. e.g.: refresh activates WR but before starting, WT writes the ID */
    if (R_EEL_TRUE == g_eel_str.pCurWP_pstr->IDXTableUpdate_enu)
    {

        /* ------------ Extended features process initializations ------------------------------------------------------ */
        /* Prepare extended features data.
           Note: Need to be done within the Write process (not already at write process set-up) as now it is ensured
                 that the FDL does not execute Flash operations and the EEL can gather important information from the
                 Data Flash */
        #ifdef R_EEL_SUPPORT_EXT_FEATURES
            {
                uint32_t             refAdd, dataAdd;
                uint16_t             idx, id;
                r_eel_bcResult_t     bc;
                r_eel_ext_features_t extFeatures;

                /* Prepare for the extended features handling in the Write flow:
                   - Set flow relevant flags for fast/safe invalidation incl. last DS instance (if available)
                   - Set flow relevant flag for write counter writing incl. write counter value */

                /* For Write and immediate Write we need to set all information */
                if ( (R_EEL_PR_WI == g_eel_str.curPId_enu) ||
                     (R_EEL_PR_WT == g_eel_str.curPId_enu) )
                {
                    idx = g_eel_str.pCurWP_pstr->idx_u16;
                    id =  g_eel_str.pCurWP_pstr->id_u16;

                    iErr = R_EEL_SFct_FindValidDS (idx, id, &refAdd);

                    if (R_EEL_OK == iErr)
                    {
                        extFeatures = g_eel_str.RTCfg_pstr->IDLTab_pstr[idx].ext_features_enu;

                        if (0x00000000uL != refAdd)
                        {
                            dataAdd = R_EEL_PFct_Get_RefAdd2DataAdd (refAdd);
                        }

                        /* For FINV marker we just skip the address */
                        if ( (R_EEL_EXTF_FINV == extFeatures) ||
                             (R_EEL_EXTF_WC_FINV == extFeatures) )
                        {
                            if (R_EEL_FALSE == g_eel_str.pCurWP_pstr->invalidate_enu)
                            {
                                g_eel_str.pCurWP_pstr->fastSafeInvHandling_enu = R_EEL_INVTYPE_SAFE;
                            }
                            else
                            {
                                g_eel_str.pCurWP_pstr->fastSafeInvHandling_enu = R_EEL_INVTYPE_FAST;
                            }

                            if (0x00000000uL != refAdd)
                            {
                                /* We store the marker address of the last instance for fast/safe invalidation */
                                g_eel_str.pCurWP_pstr->prevInstInvMrkAdd = dataAdd;
                                dataAdd -= R_WRITE_SIZE;
                            }
                        }

                        /* Get WC data and write WC*/
                        if ( (R_EEL_EXTF_WC == extFeatures) ||
                             (R_EEL_EXTF_WC_FINV == extFeatures) )
                        {
                            g_eel_str.pCurWP_pstr->writeCntSupport_enu = R_EEL_TRUE;

                            if (0x00000000uL != refAdd)
                            {
                                g_eel_str.pCurWP_pstr->writeCntValue_u32 = R_EEL_PFct_ReadDFlashU32 (dataAdd) + 1uL;
                            }
                        }
                    } /* if (R_EEL_OK == iErr) */
                } /* if(   ( R_EEL_PR_WI == g_eel_str.curPId_enu ) ... */
                  /* On Refresh write we only take care of the fast invalidation marker.
                     The write counter is copied by the data copy process */
                else
                {
                    if ( 0uL != (g_eel_str.pCurWP_pstr->src_pu32) )
                    {
                        iErr = R_EEL_PFct_BlankCheckDFlash (&(g_eel_str.pCurWP_pstr->src_pu32), 1uL, &bc);
                        if (R_EEL_OK == iErr)
                        {
                            if (R_EEL_BC_BLANK == bc)
                            {
                                g_eel_str.pCurWP_pstr->fastSafeInvHandling_enu = R_EEL_INVTYPE_REFRESH;

                                g_eel_str.pCurWP_pstr->prevInstInvMrkAdd = (g_eel_str.pCurWP_pstr->src_pu32);
                            }
                        }
                    }
                }
            }
        #endif /* ifdef R_EEL_SUPPORT_EXT_FEATURES */

        /* ------------ Pool full handling ----------------------------------------------------------------------------- */
        if (R_EEL_OK == iErr)                                                   /* PRQA S 2991, 2995 */
        {
            /* Check the required pool space */
            chkSpace = R_EEL_PFct_Chk_EELPoolSpaceForDS (g_eel_str.pCurWP_pstr->byteCnt_u16,
                                                         g_eel_str.curPId_enu);

            if (R_EEL_ERR_POOL_FULL == chkSpace)
            {
                /* Pool full error to Write process */
                (void)R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (R_EEL_ERR_POOL_FULL);

                /* Special case:
                   We want to invalidate and have pool full situation and have fast invalidate activated for the affected DS...
                   Then we do fast invalidation but don't write the invalidation DS */
                #ifdef R_EEL_SUPPORT_EXT_FEATURES
                    if (R_EEL_INVTYPE_FAST == g_eel_str.pCurWP_pstr->fastSafeInvHandling_enu)
                    {
                        g_eel_str.pCurWP_pstr->fastSafeInvHandling_enu = R_EEL_INVTYPE_FAST_POOLFULL;

                        /* Patch next state as pool full still needs actions (fast invalidation marker setting) */
                        g_eel_str.pCurP_pstr->nextState_pfct    = R_EEL_SM_WRITE_FAST_INV;
                    }
                #endif
            }
            else
            {
                /* ------------ WP/RP update and potential new block activation ------------------------------------------------ */

                #ifdef R_EEL_SUPPORT_EXT_FEATURES
                    if (R_EEL_INVTYPE_FAST == g_eel_str.pCurWP_pstr->fastSafeInvHandling_enu)
                    {
                        nextState = R_EEL_SM_WRITE_FAST_INV;
                    }
                    else
                #endif
                {
                    nextState = R_EEL_SM_WRITE_SOR;
                }

                activateBlock = R_EEL_SFct_Write_UpdateRpWp (&actBlk, &actBlkRwp);

                /* We need space for the REF entry. In case of no more enough space for starting DS
                   write we need to activate the new block */
                if (R_EEL_TRUE == activateBlock)
                {
                    R_EEL_SFct_SetActive_StartProcess (nextState,
                                                       R_EEL_SM_WRITE_SET_ACTIVE_ERROR,
                                                       actBlk,
                                                       actBlkRwp);
                }
                else
                {
                    g_eel_str.pCurP_pstr->nextState_pfct = nextState;
                }
            } /* if( R_EEL_ERR_POOL_FULL == chkSpace ) - else */
        } /* if (R_EEL_OK == iErr) */
    } /* if (R_EEL_FALSE == g_eel_str.pCurWP_pstr->IDXTableUpdate_enu)  */
    else
    {
        /* Completely skip the operation */
        g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_WRITE_FINISH;
    }

    return;
} /* R_EEL_SM_Write_Start */


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Write_SOR
 *********************************************************************************************************************/
/**
 * State machine write process state function to write SOR
 *
 * Consisting of:
 * - start Flash write operation
 * - proceed with DRP write
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Write_SOR (void)
{
    uint32_t rp;

#ifdef R_EEL_SUPPORT_EXT_FEATURES
        r_eel_flash_error_chk_t feChk;

        /* Flash write operation result check */
        feChk = R_EEL_SFct_FlashOpResultCheck_Write (R_EEL_TRUE);
        if (R_EEL_FLERR_CHK_ERR != feChk)
        {
#else
        {
#endif /* ifdef R_EEL_SUPPORT_EXT_FEATURES */

            /* Write SOR of the DS */
            rp = g_eel_str.pCurWP_pstr->rp_u32 + R_EEL_REF_OFF_SOR;
            R_EEL_FDLIF_WriteTag (rp);

            g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_WRITE_DRP;
        }
} /* R_EEL_SM_Write_SOR */


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Write_DRP
 *********************************************************************************************************************/
/**
 * State machine write process state function to write DRP
 *
 * Consisting of:
 * - check previous SOR write operation result. If ok,
 *     - start Flash write operation for DRP
 *     - proceed with data write
 * -else
 *     - proceed with finish write process
 *
 * @param          ---
 * @return         ---
 *
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Write_DRP (void)
{
    uint32_t                data,
                            rp;
    uint16_t                blk;
    r_eel_flash_error_chk_t feChk;

    /* Flash write operation result check (Ignore Flash Write errors) */
    feChk = R_EEL_SFct_FlashOpResultCheck_Write (R_EEL_TRUE);
    if (R_EEL_FLERR_CHK_IGNORE == feChk)
    {
        /* React on Flash Write error when writing SOR:
           - Set block full
           - Restart the Write operation on a new block
             - Pool full situation is checked on Write restart */
        g_eel_str.wp_u32 = g_eel_str.rp_u32;
        g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_WRITE_START;
    }
    else
    {
        if (R_EEL_FLERR_CHK_OK == feChk)
        {
            /* Write DRP of the DS:
               upper 16bit: data address (relative to block start)
               lower 16bit: ID */
            blk  = R_EEL_PFct_Calc_Add2vBlk (g_eel_str.pCurWP_pstr->wp_u32);

            if (0u == g_eel_str.pCurWP_pstr->byteCnt_u16)
            {
                data = 0x00000000uL;
            }
            else
            {
                data = (g_eel_str.pCurWP_pstr->wp_u32) - R_EEL_PFct_Calc_vBlkBaseAdd (blk);
            }
            data = (data << 16);

            /* Check if we invalidate data or write data */
            if (R_EEL_TRUE == g_eel_str.pCurWP_pstr->invalidate_enu)
            {
                data |= R_EEL_DRP_INVALIDATE_FLG;
            }

            data = ( data + ( (uint32_t)(g_eel_str.pCurWP_pstr->id_u16) & 0xFFFFuL ) );
            rp   = g_eel_str.pCurWP_pstr->rp_u32 + R_EEL_REF_OFF_DRP;
            R_EEL_FDLIF_Write ( (const uint32_t *)(&data), rp, 1 );

            /* We continue with the write flow */
            g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_WRITE_DATA;

            #ifdef R_EEL_SUPPORT_EXT_FEATURES
                if (R_EEL_TRUE == g_eel_str.pCurWP_pstr->writeCntSupport_enu)
                {
                    g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_WRITE_WRITE_COUNTER;
                }

                /* Update WP and Byte count for the extended features after they were considered in the space
                   calculations and for DRP write  */

                /* For fast/safe invalidation, we need to skip the 1st data word */
                if (R_EEL_INVTYPE_NONE != g_eel_str.pCurWP_pstr->fastSafeInvHandling_enu)
                {
                    (g_eel_str.pCurWP_pstr->wp_u32)      -= R_WRITE_SIZE;
                    (g_eel_str.pCurWP_pstr->byteCnt_u16) -= R_WRITE_SIZE;
                }

                /* For fast/safe invalidation, during WR we need to skip the 1st data word also in the source data */
                if (R_EEL_INVTYPE_REFRESH == g_eel_str.pCurWP_pstr->fastSafeInvHandling_enu)
                {
                    (g_eel_str.pCurWP_pstr->src_pu32)    -= R_WRITE_SIZE;
                }

                /* For write counter write (WT, WI) we update the data too.
                   Write counter on WR process is considered as part of the data; so the writeCntSupport_enu flag is not set and the
                   data is not updated */
                if (R_EEL_TRUE == g_eel_str.pCurWP_pstr->writeCntSupport_enu)
                {
                    (g_eel_str.pCurWP_pstr->wp_u32)      -= R_WRITE_SIZE;
                    (g_eel_str.pCurWP_pstr->byteCnt_u16) -= R_WRITE_SIZE;
                }
            #endif /* ifdef R_EEL_SUPPORT_EXT_FEATURES */

            /* On Refresh write we remember the source/destination address and byte count for the comparison */
            if (R_EEL_PR_WR == g_eel_str.curPId_enu)
            {
                g_eel_str.opRf_str.cmpSrc_u32  = (g_eel_str.pCurWP_pstr->src_pu32);
                g_eel_str.opRf_str.cmpDest_u32 = (g_eel_str.pCurWP_pstr->wp_u32);
                g_eel_str.opRf_str.cmpCnt_u16  = (g_eel_str.pCurWP_pstr->byteCnt_u16);
            }
        } /* if (R_EEL_FLERR_CHK_OK == feChk) */
    } /* if (R_EEL_FLERR_CHK_IGNORE == feChk) */

} /* R_EEL_SM_Write_DRP */

#ifdef R_EEL_SUPPORT_EXT_FEATURES
/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Write_WriteCnt
 *********************************************************************************************************************/
/**
 * State machine write process state function to write the extended features "write counter" and "fast invalidation"
 *
 * Consisting of:
 * - check previous write operation result. If ok,
 *     - start Flash write operation for extended features
 *     - proceed with data write
 * -else
 *     - proceed with finish write process
 *
 * @param          ---
 * @return         ---
 *
 */
/*********************************************************************************************************************/
    R_EEL_STATIC void R_EEL_SM_Write_WriteCnt (void)
    {
        uint32_t                wc;
        r_eel_flash_error_chk_t feChk;

        /* Flash write operation result check */
        feChk = R_EEL_SFct_FlashOpResultCheck_Write (R_EEL_FALSE);
        if (R_EEL_FLERR_CHK_OK == feChk)
        {
            wc = g_eel_str.pCurWP_pstr->writeCntValue_u32;
            R_EEL_FDLIF_Write ( (const uint32_t *)(&wc),
                                g_eel_str.pCurWP_pstr->wp_u32 + R_WRITE_SIZE, 1u );

            g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_WRITE_DATA;
        }
    } /* R_EEL_SM_Write_WriteCnt */

/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Write_FastInvalidate
 *********************************************************************************************************************/
/**
 * State machine write process state function to invalidate the previous DS before the original invalidation Ds write
 *
 * @param          ---
 * @return         ---
 *
 */
/*********************************************************************************************************************/
    R_EEL_STATIC void R_EEL_SM_Write_FastInvalidate (void)
    {
        /* Follow the fast invalidation flow, but write the last DS instance invalidation marker only if it is really
           available. If not, reset the Write operation status just to be sure not to get a left-over status */
        if (0x00000000uL == g_eel_str.pCurWP_pstr->prevInstInvMrkAdd)
        {
            g_eel_str.fdlReqWrite_str.status_enu = R_FDL_OK;
            g_eel_str.pCurP_pstr->flashStatus_enu = R_FDL_OK;
        }
        else
        {
            R_EEL_FDLIF_WriteTag (g_eel_str.pCurWP_pstr->prevInstInvMrkAdd);
        }

        if (R_EEL_INVTYPE_FAST_POOLFULL == g_eel_str.pCurWP_pstr->fastSafeInvHandling_enu)
        {
            g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_WRITE_WAIT_FINISH;
        }
        else
        {
            g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_WRITE_SOR;
        }

    } /* R_EEL_SM_Write_FastInvalidate */

/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Write_SafeInvalidate
 *********************************************************************************************************************/
/**
 * State machine write process state function to invalidate the previous DS instance after DS write
 *
 * @param          ---
 * @return         ---
 *
 */
/*********************************************************************************************************************/
    R_EEL_STATIC void R_EEL_SM_Write_SafeInvalidate (void)
    {
        r_eel_flash_error_chk_t feChk;


        /* Flash write operation result check */
        feChk = R_EEL_SFct_FlashOpResultCheck_Write (R_EEL_FALSE);
        if (R_EEL_FLERR_CHK_OK == feChk)
        {
            /* Follow the fast invalidation flow, but write the last DS instance invalidation marker only if it is really
               available. If not, reset the Write operation status just to be sure not to get a left-over status
               from a higher priority write*/
            if (0x00000000uL == g_eel_str.pCurWP_pstr->prevInstInvMrkAdd)
            {
                g_eel_str.fdlReqWrite_str.status_enu  = R_FDL_OK;
                g_eel_str.pCurP_pstr->flashStatus_enu = R_FDL_OK;
            }
            else
            {
                R_EEL_FDLIF_WriteTag (g_eel_str.pCurWP_pstr->prevInstInvMrkAdd);
            }

            g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_WRITE_WAIT_FINISH;
        }
    } /* R_EEL_SM_Write_SafeInvalidate */

#endif /* ifdef R_EEL_SUPPORT_EXT_FEATURES */

/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Write_SetActiveError
 *********************************************************************************************************************/
/**
 * State machine write process state to react on A0 write error
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Write_SetActiveError (void)
{
    uint16_t blkInv;
    /* Check if we end in the process error or if we can recover a A0 Write error.
       R_EEL_ERR_FLASH is the default value set in process before checking A0 write result. Any
       other value is set as recovery value on Flash error detection */
    if (R_EEL_TRUE == g_eel_str.opSA_str.a0FlashError)
    {
        /* - Rewind to the situation before write start except that the block to activate is
             set invalid and the block to fill is set full
             - Rewind RP to the value before activation
             - Make the block full by WP = RP
             - Rewind active block  not necessary as it is forwarded only on successful set active
             - Invalidate the block to activate
             - Rewind process status
           - Restart the DS write (possible pool full situation is checked on Write restart)
        */
        g_eel_str.rp_u32          = g_eel_str.opSA_str.setRwp_u32;
        g_eel_str.wp_u32          = g_eel_str.rp_u32;
        blkInv                    = g_eel_str.opSA_str.setActiveBlk_u16;

        /* Write the block invalid, then restart the Write process */
        R_EEL_SFct_SetInvalid_StartProcess (R_EEL_SM_WRITE_START,
                                            R_EEL_SM_WRITE_FINISH,
                                            blkInv);
    }
    else
    {
        /* On error we finish the process immediately */
        g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_WRITE_FINISH;
    }
} /* R_EEL_SM_Write_SetActiveError */




/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Write_Data
 *********************************************************************************************************************/
/**
 * State machine write process state function to write the data
 *
 * Consisting of:
 * - check previous process write operation result. If ok,
 *     - update RP (and WP if required )
 *     - calculate number of words to write with the next Flash write operation
 *     - if immediate or normal write
 *         - copy data to write buffer and update source pointer
 *     - else (refresh write)
 *         - read data from old DS instance in write buffer
 *     - start Flash write operation
 *     - if no more data to write
 *       - proceed with write EOR
 * -else
 *     - proceed with finish write process
 *
 * Some called sub-routines, reading Data Flash with blank check might end with R_EEL_ERR_INTERNAL
 * on blank check. This results in a process error.
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Write_Data (void)
{
    uint32_t                srcAdd;
    uint16_t                byteCntForOneWriteOp;
    uint32_t                i;
    uint8_t                 dataU08;
    r_eel_err_flg_t         dummyFlg;
    r_eel_flash_error_chk_t feChk;


    /* Flash write operation result check */
    feChk = R_EEL_SFct_FlashOpResultCheck_Write (R_EEL_FALSE);
    if (R_EEL_FLERR_CHK_OK == feChk)
    {
        /* Unlock Write process after possible block activation and writing the 1st REF entry data part */
        g_eel_str.processLock_enu = R_EEL_PR_UNLOCK;

        /* == 0 if we have invalidation */
        if (0u != g_eel_str.pCurWP_pstr->byteCnt_u16)
        {
            /* Write data of Write command or immediate Write command*/
            if ( (R_EEL_PR_WI == g_eel_str.curPId_enu) ||
                 (R_EEL_PR_WT == g_eel_str.curPId_enu) )
            {
                /* Write all data to the buffer (round up to full words) */
                srcAdd  = g_eel_str.pCurWP_pstr->src_pu32;

                /* Fill the buffer for Flash write operation - determine the byte count */
                if (g_eel_str.pCurWP_pstr->byteCnt_u16 < R_EEL_FDL_WRITESIZE)
                {
                    byteCntForOneWriteOp = (g_eel_str.pCurWP_pstr->byteCnt_u16);
                }
                else
                {
                    byteCntForOneWriteOp = R_EEL_FDL_WRITESIZE;
                }

                g_eel_str.dataBuffer[0] = 0uL;
                for (i = 0; i < R_EEL_FDL_WRITESIZE; i++)
                {
                    if (i < byteCntForOneWriteOp)
                    {
                        dataU08 = R_EEL_PFct_ReadDataFromAddU08 (srcAdd);
                    }
                    else
                    {
                        dataU08 = 0xFF;
                    }
                    g_eel_str.dataBuffer[0] += ( (uint32_t)dataU08 << (i * 8) );
                    srcAdd++;
                }

                g_eel_str.pCurWP_pstr->src_pu32  += R_EEL_FDL_WRITESIZE;
            }
            /* Write data of Write Refresh process */
            else
            {
                /* Refresh Write --> Read old DS Data in inverse direction to the buffer */
                R_EEL_SFct_Read_Chk_Data (
                    (uint32_t *)( &(g_eel_str.pCurWP_pstr->src_pu32) ),             /* *pSrcAdd */
                    R_EEL_PFct_CastU32Ptr2Add (&g_eel_str.dataBuffer[0]),           /* destAdd */
                    R_EEL_FDL_WRITESIZE,                                            /* #Bytes to read */
                    R_EEL_FALSE,                                                    /* chk */
                    &dummyFlg);                                                     /* check result not used */
            }

            g_eel_str.pCurWP_pstr->wp_u32 -= R_EEL_FDL_WRITESIZE;

            /* invoke FDL IF to perform Flash write operation */
            R_EEL_FDLIF_Write (&g_eel_str.dataBuffer[0],
                               g_eel_str.pCurWP_pstr->wp_u32 + R_EEL_FDL_WRITESIZE,
                               1uL);

            if ( g_eel_str.pCurWP_pstr->byteCnt_u16 > (uint16_t)(R_EEL_FDL_WRITESIZE) )
            {       /* update the remaining byte count for Flash write operation */
                g_eel_str.pCurWP_pstr->byteCnt_u16 -= (uint16_t)(R_EEL_FDL_WRITESIZE);
            }
            else
            {
                g_eel_str.pCurWP_pstr->byteCnt_u16 = 0u;

                /* Refresh Write will compare the data first before activation of the DS */
                if (R_EEL_PR_WR == g_eel_str.curPId_enu)
                {
                    g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_WRITE_CMP_DATA;
                }
                else
                {
                    g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_WRITE_EOR0;
                }
            }
        }
        else    /* if (0u != g_eel_str.pCurWP_pstr->byteCnt_u16) */
        {
            g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_WRITE_EOR0;
        }
    }
} /* R_EEL_SM_Write_Data */


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Write_CmpData
 *********************************************************************************************************************/
/**
 * State machine write process state function to compare written data against org. data in case of Refresh Write.
 * If not correct, finish Write process with error
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Write_CmpData (void)
{
    uint32_t i, cnt,
             srcAdd, destAdd,
             dataSrc, dataDest;
    r_eel_err_flg_t cmpErr;

    cmpErr = R_EEL_FLG_OK;

    if (R_EEL_READ_CNT_MAX <= g_eel_str.opRf_str.cmpCnt_u16)
    {
        cnt = R_EEL_READ_CNT_MAX;
    }
    else
    {
        cnt = g_eel_str.opRf_str.cmpCnt_u16;
    }

    srcAdd  = g_eel_str.opRf_str.cmpSrc_u32;
    destAdd = g_eel_str.opRf_str.cmpDest_u32;
    for (i = 0; i < cnt; i += 4)
    {
        dataSrc  = R_EEL_PFct_ReadDFlashU32 (srcAdd);
        dataDest = R_EEL_PFct_ReadDFlashU32 (destAdd);
        if (dataSrc != dataDest)
        {
            cmpErr = R_EEL_FLG_ERROR;
            break;
        }
        srcAdd  -= 4uL;
        destAdd -= 4uL;
    }

    if (R_EEL_FLG_ERROR == cmpErr)
    {
        (void)R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (R_EEL_ERR_INTERNAL);
    }
    else
    {
        g_eel_str.opRf_str.cmpSrc_u32  =  srcAdd;
        g_eel_str.opRf_str.cmpDest_u32 =  destAdd;
        g_eel_str.opRf_str.cmpCnt_u16  -= (uint16_t)cnt;

        if (0uL == g_eel_str.opRf_str.cmpCnt_u16)
        {
            g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_WRITE_EOR0;
        }
    }
} /* R_EEL_SM_Write_CmpData */


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Write_EOR0
 *********************************************************************************************************************/
/**
 * State machine write process state function to write EOR0
 *
 * Consisting of:
 * - check previous process write operation result. If ok,
 *     - start Flash write operation
 *     - proceed with write eor1 state
 * -else
 *     - proceed with finish write state
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Write_EOR0 (void)
{
    uint32_t                add;
    r_eel_flash_error_chk_t feChk;

    /* Flash write operation result check */
    feChk = R_EEL_SFct_FlashOpResultCheck_Write (R_EEL_FALSE);
    if (R_EEL_FLERR_CHK_OK == feChk)
    {
        add = g_eel_str.pCurWP_pstr->rp_u32 + R_EEL_REF_OFF_EOR0;
        R_EEL_FDLIF_WriteTag (add);

        g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_WRITE_EOR1;
    }
} /* R_EEL_SM_Write_EOR0 */

/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Write_EOR1
 *********************************************************************************************************************/
/**
 * State machine write process state function to write EOR1
 *
 * Consisting of:
 * - check previous process write operation result. If ok,
 *     - start Flash write operation
 *     - proceed with (wait) finish write state
 * -else
 *     - proceed with finish write state
 *
 * @param          ---
 * @return         ---
 *
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Write_EOR1 (void)
{
    uint32_t                add;
    r_eel_flash_error_chk_t feChk;

    /* Flash write operation result check */
    feChk = R_EEL_SFct_FlashOpResultCheck_Write (R_EEL_FALSE);
    if (R_EEL_FLERR_CHK_OK == feChk)
    {
        add = g_eel_str.pCurWP_pstr->rp_u32 + R_EEL_REF_OFF_EOR1;
        R_EEL_FDLIF_WriteTag (add);

        g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_WRITE_WAIT_FINISH;
        #ifdef R_EEL_SUPPORT_EXT_FEATURES
            if ( (R_EEL_INVTYPE_SAFE    == g_eel_str.pCurWP_pstr->fastSafeInvHandling_enu) ||
                 (R_EEL_INVTYPE_REFRESH == g_eel_str.pCurWP_pstr->fastSafeInvHandling_enu) )
            {
                g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_WRITE_SAFE_INV;
            }
        #endif
    }
} /* R_EEL_SM_Write_EOR1 */

/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Write_Wait_Finish
 *********************************************************************************************************************/
/**
 * State machine write process state function to update the ID-X table
 *
 * Consisting of:
 * - check previous process write operation result. If ok,
 *     - if normal or immediate write
 *         - update ID-X table
 * - proceed with finish write process
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Write_Wait_Finish (void)
{
    r_eel_flash_error_chk_t feChk;

#ifdef R_EEL_SUPPORT_EXT_FEATURES
        if (R_EEL_INVTYPE_NONE != g_eel_str.pCurWP_pstr->fastSafeInvHandling_enu)
        {
            /* We accept the Flash error as the fast invalidation marker could be partly or completely set
               A warning will inform the user application */
            feChk = R_EEL_SFct_FlashOpResultCheck_Write (R_EEL_TRUE);
        }
        else
#endif
    {
        /* Default case: No Fast/Save invalidation marker. In this case Flash error would be fatal */
        feChk = R_EEL_SFct_FlashOpResultCheck_Write (R_EEL_FALSE);
    }

    if (R_EEL_FLERR_CHK_ERR != feChk)
    {
        /* Update IDX-Table entry */
        R_EEL_SFct_Write_UpdateIDXTable ();
    }

    /* Independent from the failure we finish the process */
    g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_WRITE_FINISH;
} /* R_EEL_SM_Write_Wait_Finish */


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Write_Finish
 *********************************************************************************************************************/
/**
 * State machine write process state function to finish the write process
 *
 * Consisting of:
 * - update driver status
 * - in case of write immediate or write normal, update user request structure status variable
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Write_Finish (void)
{
    r_eel_operation_id_t cmd;
    r_eel_err_flg_t      errFlg;

    /* On write command we set the status return of the command request structure
       In case of Refresh-Write the state management is done in the Supervision */
    if (R_EEL_PR_WR != g_eel_str.curPId_enu)
    {
        cmd  = R_EEL_SFct_ConvertProcessID2CommandNo (g_eel_str.curPId_enu);
        g_eel_str.op_str[cmd].req_pstr->status_enu = g_eel_str.pCurP_pstr->rStat_enu; /* PRQA S 3689 */

        /* Reset the prepare loop limit for detection of exhausted pool */
        R_EEL_PFct_PrepLoopLimitReset ();

        /* Check if we got a write error. If yes, this is fatal and we lock SV and Write */
        errFlg = R_EEL_SFct_ErrStatCheckError_CurProc ();
        if (R_EEL_FLG_ERROR == errFlg)
        {
            if (R_EEL_ERR_POOL_FULL == g_eel_str.pCurP_pstr->rStat_enu)
            {
                /* Don't change the driver status. Just this command could not be executed */
            }
            else if (R_EEL_ERR_FLASH_ERROR == g_eel_str.pCurP_pstr->rStat_enu)
            {
                /* In case of write error we might be able to limp home */
                R_EEL_SFct_SetDriverStatus (R_EEL_ACCESS_READ_ONLY, R_EEL_OPERATION_PASSIVE);
            }
            else
            {
                R_EEL_SFct_SetDriverStatus (R_EEL_ACCESS_LOCKED, R_EEL_OPERATION_PASSIVE);
            }
        }
    }

    /* We unlock the process here as in case of errors the process is stopped before
       regular unlock */
    g_eel_str.processLock_enu = R_EEL_PR_UNLOCK;

    /* Terminate process */
    g_eel_str.pCurP_pstr->active_enu = R_EEL_FALSE;
} /* R_EEL_SM_Write_Finish */


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Refresh_Start
 *********************************************************************************************************************/
/**
 * State machine refresh process state function to find a data set to copy
 * and if no more copy is required, to initiate invalidation
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/

/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 9.1 (QAC message 3353)
 * Reason:       QAC claims that variables are possibly unset before usage
 * Verification: the variable "data" is filled in the preceding for loop. Loop boundaries are >0
 *********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Refresh_Start (void)
{
    uint32_t refAdd,
             srcAdd;
    uint16_t blk,
             id,
             idx,
             tIdx,
             idxMax,
             len;
    r_eel_err_flg_t errFlg;
    r_eel_flag_t    invalidate,
                    refFinish,
                    copyIdFound;
    r_eel_patcmp_t sorPatMatch;
    r_eel_status_t iErr;
    r_eel_chk_ds_t chkDS;

    iErr = R_EEL_OK;

    /* for QAC check only */
    refAdd = 0x00000000uL;
    id     = 0x0000u;

    /* if we had a preceding Refresh-write, it must have passed successfully */
    errFlg = R_EEL_SFct_ErrStatCheckError (R_EEL_PR_WR);
    if (R_EEL_FLG_OK != errFlg)
    {
        (void)R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (g_eel_str.sm_str[R_EEL_PR_WR].rStat_enu);
    }
    else
    {
        copyIdFound = R_EEL_FALSE;
        tIdx        = R_EEL_ID_NOT_FOUND;

        if (R_EEL_OPERATION_MODE_LIMITED == g_eel_str.opMode_enu)
        {
            refAdd    = g_eel_str.opRf_str.lmRefAd_u32;
            refFinish = R_EEL_FALSE;

            iErr = R_EEL_PFct_ReadDFlash_cmpPatBC (refAdd + R_EEL_REF_OFF_SOR, &sorPatMatch);
            if ( (R_EEL_OK == iErr) && (R_EEL_PATCMP_VALID == sorPatMatch) )
            {
                iErr = R_EEL_SFct_Chk_DSValid (refAdd, &chkDS);
                if ( (R_EEL_OK == iErr) && (R_EEL_CHKDS_INVALID != chkDS) )
                {
                    id = R_EEL_PFct_Get_RefAdd2ID (refAdd);
                    iErr = R_EEL_SFct_FindValidDS_NoIdxTab (id, &refAdd);
                    if (R_EEL_OK == iErr)
                    {
                        /* DS not required if found in another block or in the same block but higher address */
                        if (refAdd == g_eel_str.opRf_str.lmRefAd_u32)
                        {
                            copyIdFound = R_EEL_TRUE;

                            tIdx = R_EEL_PFct_ConvertId2TIdx (id); /* either idx from the ID-L table or
                                                                      R_EEL_ID_NOT_FOUND */
                        }
                        else
                        {
                            /* Need not do anything as we exit ... in the next run check the next REF entry */
                        }
                    }
                }
                /* Next round continue with the next REF entry */
                g_eel_str.opRf_str.lmRefAd_u32 += R_EEL_REF_OFF_DS;

            } /* if ( (R_EEL_OK == iErr) && (R_EEL_PATCMP_VALID == sorPatMatch) ) */
            else
            {
                refFinish = R_EEL_TRUE;
            }


        } /* if (R_EEL_OPERATION_MODE_LIMITED == g_eel_str.opMode_enu) */
        else
        {
            idx       = g_eel_str.opRf_str.tIdx_u16;
            idxMax    = g_eel_str.RTCfg_pstr->IDLTabIdxCnt_u16;
            refFinish = R_EEL_TRUE;

            while ( (R_EEL_TRUE != copyIdFound)
                    && (idx < idxMax) )
            {
                refAdd = R_EEL_PFct_ConvertTidx2RefAdd (idx);
                blk    = R_EEL_PFct_Calc_Add2vBlk (refAdd);

                if (blk == g_eel_str.blkOEActive_u16)
                {
                    /* We found a DS to refresh */
                    id = R_EEL_PFct_Get_RefAdd2ID (refAdd);
                    tIdx = idx;
                    copyIdFound = R_EEL_TRUE;
                    refFinish = R_EEL_FALSE;
                    g_eel_str.opRf_str.tIdx_u16 = idx + 1u; /* idx points one after the DS to be copied
                                                               On next Refresh we continue there */
                }
                idx++;
            }
        }

        /* Here  we have the following information:
           - refAdd of the affected DS
           - id
           - copyIdFound    - normal mode: either refFinish=true or copyIdFound = true
                            - limited mode: both are independent, both can be false, then we enter the function to
                                            search on the next refAdd
           - refFinish
           - tIdx:          - defined on normal Refresh
                            - defined on limited mode Refresh when ID is in the ID-L table
                            - R_EEL_ID_NOT_FOUND in limited mode when the ID is not in the IDX table
        */
        if (R_EEL_OK == iErr)
        {
            if (R_EEL_TRUE == refFinish)
            {
                /*Lock set block invalid for correct state propagation in error case*/
                g_eel_str.processLock_enu = R_EEL_PR_RF;
                /* No more DS to Refresh --> Set block invalid */
                R_EEL_SFct_SetInvalid_StartProcess (R_EEL_SM_REFR_FINISH,
                                                    R_EEL_SM_REFR_FINISH,
                                                    g_eel_str.blkOEActive_u16);
                g_eel_str.opRf_str.updBlkOEActive_enu = R_EEL_TRUE;
            }
            else
            {
                if (R_EEL_TRUE == copyIdFound)
                {
                    /* source address (0 if no data to be copied) */
                    srcAdd = R_EEL_PFct_Get_RefAdd2DataAdd (refAdd);

                    /* ------------- Check the invalid flash and calculate DS length ---------------- */
                    /* Use ID-L table if the entry is in the table */
                    if (R_EEL_ID_NOT_FOUND != tIdx)
                    {
                        iErr = R_EEL_PFct_Chk_DSInvalidated (refAdd, tIdx, &invalidate);
                        if (R_EEL_FALSE == invalidate)                          /* PRQA S 3353 */
                        {
                            /* normal write */
                            len = R_EEL_PFct_ConvertTIdx2Len (tIdx);
                        }
                        else
                        {
                            /* Set invalidate */
                            len = 0u;
                        }
                    } /* if (R_EEL_ID_NOT_FOUND != tIdx) */
                      /* In limited mode when the DS is not in the ID-L table, we need to check in the Flash */
                    else
                    {
                        /* We need only check the invalidate flag because the extended feature invalidate word
                           is checked during refresh write (R_EEL_SM_Write_WriteCnt) */
                        invalidate = R_EEL_PFct_Chk_DSInvalidated_InvFlg (refAdd);

                        iErr = R_EEL_SFct_Get_RefAdd_2_DSLen_LimMode (refAdd, &len);
                    }

                    if (R_EEL_OK == iErr)
                    {
                        /* Start Refresh Write operation
                           Note on len parameter: - DS length without extensions if tIdx is defined
                                                  - DS length incl. extensions if tIdx is R_EEL_ID_NOT_FOUND */
                        R_EEL_SFct_Write_InitProcess (
                            R_EEL_WDATA_WR,                            /* Process to start */
                            R_EEL_REQUEST_POINTER_UNDEFINED,           /* request struct./R_EEL_NULL */
                            id,                                        /* id to write */
                            len,                                       /* Byte count to write */
                            srcAdd,                                    /* Write source address */
                            invalidate,                                /* Invalidate? */
                            tIdx);                                     /* table index */

                        R_EEL_SFct_ActivateProcess (R_EEL_PR_WR, R_EEL_SM_WRITE_START);
                    } /* if( R_EEL_OK == iErr ) */
                } /* if (R_EEL_TRUE == copyIdFound) */
            } /* if( R_EEL_TRUE == refFinish ) - else */
        } /* if( R_EEL_FLG_OK == errFlg ) */
    } /* if( R_EEL_FLG_OK == errFlg ) */
} /* R_EEL_SM_Refresh_Start */


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Refresh_Finish
 *********************************************************************************************************************/
/**
 * State machine refresh process state function to finish Refresh
 *
 * Consisting of:
 * - Conditionally update the pointer to the eldest active block
 * - disable the Refresh process
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Refresh_Finish (void)
{
    g_eel_str.processLock_enu = R_EEL_PR_UNLOCK;
    /* Only update the counter if the flag is set (= invalidation process was executed) */
    if (R_EEL_TRUE == g_eel_str.opRf_str.updBlkOEActive_enu)
    {
        /* Set Refresh pointer to the next block.
           - It may be active or invalid. Prepared is not possible as then the ring buffer would not
             be consistent */
        g_eel_str.blkOEActive_u16 = R_EEL_SFct_Calc_NextBlk_Any (g_eel_str.blkOEActive_u16, R_EEL_BLK_NEXT);
    }

    g_eel_str.sm_str[R_EEL_PR_RF].active_enu = R_EEL_FALSE;
}

/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Set_Active_A0
 *********************************************************************************************************************/
/**
 * State machine set active sub-process state function to write A0
 *
 * Consisting of:
 * - start Flash write operation
 * - proceed with write RWP state
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Set_Active_A0 (void)
{
    uint32_t add;

    /* Write A1 of next block */
    add  = R_EEL_PFct_Calc_vBlkDataAdd (g_eel_str.opSA_str.setActiveBlk_u16, R_EEL_BLKHDATA_A0);

    R_EEL_FDLIF_WriteTag (add);

    g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_SET_ACTIVE_RWP;
}



/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Set_Active_RWP
 *********************************************************************************************************************/
/**
 * State machine set active sub-process state function to write RWP
 *
 * Consisting of:
 * - check if preceding write operation was successfully. If yes
 *     - start Flash write operation
 *     - proceed with write A1 state
 * - else
 *     - proceed with set active end state
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Set_Active_RWP (void)
{
    uint32_t                data,
                            add;
    r_eel_flash_error_chk_t feChk;

    /* Flash write operation result check incl. special treatment of the process error recovery
       value.
       If the Flash operation result ended in a Flash error, the previous process status is stored
       in, otherwise the variable is set to the default value R_EEL_ERR_FLASH*/
    feChk = R_EEL_SFct_FlashOpResultCheck_Write (R_EEL_TRUE);
    if (R_EEL_FLERR_CHK_IGNORE == feChk)
    {
        /* R_EEL_SFct_FlashOpResultCheck_Write would not change the "next state" to "set active end"
           as the Flash error will be ignored and be changed to warning "fix done".
           Thus, we need to explicitly set "next state" here */
        g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_SET_ACTIVE_END;
        g_eel_str.opSA_str.a0FlashError = R_EEL_TRUE;
    }
    else
    {
        if (R_EEL_FLERR_CHK_OK == feChk)
        {
            /* Write virtual address to Data Flash (- DF read offset )*/
            data = g_eel_str.opSA_str.setRwp_u32 - (R_FCU_DFLASH_READ_ADD);
            data = R_EEL_SFct_SetChecksum_8Bit_from_24bit (data);
            add = R_EEL_PFct_Calc_vBlkDataAdd (g_eel_str.opSA_str.setActiveBlk_u16, R_EEL_BLKHDATA_RWP);

            R_EEL_FDLIF_Write ( (const uint32_t *)(&data), add, 1 );

            g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_SET_ACTIVE_A1;
        }
    }
} /* R_EEL_SM_Set_Active_RWP */


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Set_Active_A1
 *********************************************************************************************************************/
/**
 * State machine set active sub-process state function to write A1
 *
 * Consisting of:
 * - check if preceding write operation was successfully. If yes
 *     - start Flash write operation
 *     - proceed with set active end wait state
 * else
 *     - proceed with set active wait state
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Set_Active_A1 (void)
{
    uint32_t                add;
    r_eel_flash_error_chk_t feChk;

    /* Flash write operation result check */
    feChk = R_EEL_SFct_FlashOpResultCheck_Write (R_EEL_FALSE);
    if (R_EEL_FLERR_CHK_OK == feChk)
    {
        /* Write A1 of next block */
        add  = R_EEL_PFct_Calc_vBlkDataAdd (g_eel_str.opSA_str.setActiveBlk_u16, R_EEL_BLKHDATA_A1);

        R_EEL_FDLIF_WriteTag (add);

        g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_SET_ACTIVE_WAIT_END;
    }
} /* R_EEL_SM_Set_Active_A1 */


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Set_Active_WaitEnd
 *********************************************************************************************************************/
/**
 * State machine set active sub-process state function to wait until we may end the
 * sub process
 *
 * Consisting of:
 * - pass Flash return to process status
 * - proceed with set active end state
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Set_Active_WaitEnd (void)
{
    /* We don't need the function return value here */
    (void)R_EEL_SFct_FlashOpResultCheck_Write (R_EEL_FALSE);

    /* Independent from the failure we finish the process */
    g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_SET_ACTIVE_END;
}


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Set_Active_End
 *********************************************************************************************************************/
/**
 * State machine set active sub-process state function to end the sub process
 *
 * Consisting of:
 * - set block status in the RAM table according to the Flash operations results
 * - proceed proceed with the host process
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Set_Active_End (void)
{
    r_eel_err_flg_t errFlg;

    errFlg = R_EEL_SFct_ErrStatCheckError_CurProc ();

    /* In case of R_EEL_OK or only warnings AND we had no A0 write fail ... */
    if ( (R_EEL_FLG_OK == errFlg) &&
         (R_EEL_FALSE == g_eel_str.opSA_str.a0FlashError) )
    {
        R_EEL_SFct_SetBlkStat (g_eel_str.opSA_str.setActiveBlk_u16, R_EEL_BLKSTAT_ACTIVE);
        g_eel_str.blkActive_u16 = g_eel_str.opSA_str.setActiveBlk_u16;

        /* We return to the write process to the original flow */
        g_eel_str.pCurP_pstr->nextState_pfct = g_eel_str.opSA_str.subProcessReturn_pfct;
    }
    else
    {
        /* Setting the block status may not be done here as either the block is invalidated
           afterwards or EEL stops with fatal error */

        /* We go to master process error step */
        g_eel_str.pCurP_pstr->nextState_pfct = g_eel_str.opSA_str.subProcessErrReturn_pfct;

    }

    /* Reset to idle as this is an indication for the error handling, that the sub-process is not executed */
    g_eel_str.opSA_str.subProcessErrReturn_pfct = R_EEL_SM_IDLE;

} /* R_EEL_SM_Set_Active_End */


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Set_Invalid_I0
 *********************************************************************************************************************/
/**
 * State machine set active sub-process state function to write I0
 *
 * Consisting of:
 * - start Flash write operation
 * - proceed with write I1 state
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Set_Invalid_I0 (void)
{
    uint32_t add;

    /* Write A0 of next block */
    add  = R_EEL_PFct_Calc_vBlkDataAdd (g_eel_str.opSI_str.setInvalidBlk_u16, R_EEL_BLKHDATA_I0);

    R_EEL_FDLIF_WriteTag (add);

    g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_SET_INVALID_I1;

}


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Set_Invalid_I1
 *********************************************************************************************************************/
/**
 * State machine set invalid sub-process state function to write I1
 *
 * Consisting of:
 * - check if preceding write operation was successfully. If yes
 *     - start Flash write operation
 *     - proceed with set invalid end wait state
 * else
 *     - proceed with set invalid wait state
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Set_Invalid_I1 (void)
{
    uint32_t                add;
    r_eel_flash_error_chk_t feChk;

    /* Flash write operation result check */
    feChk = R_EEL_SFct_FlashOpResultCheck_Write (R_EEL_TRUE);
    if (R_EEL_FLERR_CHK_ERR != feChk)
    {
        /* Write I1 */
        add = R_EEL_PFct_Calc_vBlkDataAdd (g_eel_str.opSI_str.setInvalidBlk_u16, R_EEL_BLKHDATA_I1);
        R_EEL_FDLIF_WriteTag (add);

        g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_SET_INVALID_WAIT_END;
    }
} /* R_EEL_SM_Set_Invalid_I1 */


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Set_Invalid_WaitEnd
 *********************************************************************************************************************/
/**
 * State machine set invalid sub-process state function to wait until we may end the
 * sub process
 *
 * Consisting of:
 * - pass Flash return to process status
 * - proceed with set invalid end state
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Set_Invalid_WaitEnd (void)
{
    /* We don't need the function return value here */
    (void)R_EEL_SFct_FlashOpResultCheck_Write (R_EEL_TRUE);

    /* Independent from the failure we finish the process */
    g_eel_str.pCurP_pstr->nextState_pfct = R_EEL_SM_SET_INVALID_END;
}



/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Set_Invalid_End
 *********************************************************************************************************************/
/**
 * State machine set invalid sub-process state function to end the sub process
 *
 * Consisting of:
 * - set block status in the RAM table
 * - proceed proceed with the host process
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Set_Invalid_End (void)
{
    r_eel_err_flg_t errFlg;

    /* In case of R_EEL_OK or only warnings ... */
    errFlg = R_EEL_SFct_ErrStatCheckError_CurProc ();
    if (R_EEL_FLG_OK == errFlg)
    {
        /* We return to the write process to the original flow */
        g_eel_str.pCurP_pstr->nextState_pfct = g_eel_str.opSI_str.subProcessReturn_pfct;
    }
    else
    {
        /* On error we finish the process immediately */
        g_eel_str.pCurP_pstr->nextState_pfct = g_eel_str.opSI_str.subProcessErrReturn_pfct;
    }

    /* Reset to idle as this is an indication for the error handling, that the sub-process is not executed */
    g_eel_str.opSI_str.subProcessErrReturn_pfct = R_EEL_SM_IDLE;

    /* In write error or no error case we set the block invalid and return to the main process */
    R_EEL_SFct_SetBlkStat (g_eel_str.opSI_str.setInvalidBlk_u16, R_EEL_BLKSTAT_INVALID);
} /* R_EEL_SM_Set_Invalid_End */


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Prepare_Start
 *********************************************************************************************************************/
/**
 * State machine prepare process state function to start the prepare process
 *
 * Consisting of:
 * - start Flash erase
 * - proceed proceed with check erase result
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Prepare_Start (void)
{
    g_eel_str.opPr_str.eraseFail_u08 = 0u;
    R_EEL_FDLIF_Erase (g_eel_str.opPr_str.blk_u16);

    /* Set next process step */
    g_eel_str.sm_str[R_EEL_PR_PR].nextState_pfct = R_EEL_SM_PREP_CHK_ERASE_RESULT;
}



/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Prepare_Chk_Erase_Result
 *********************************************************************************************************************/
/**
 * State machine prepare process state function to check the erase result
 *
 * Consisting of:
 * - check if preceding erase operation was successfully. If yes
 *     - proceed with write EC
 * else
 *     - check if preceding erase operation had an erase error. If yes, retry erase or return a Flash error
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Prepare_Chk_Erase_Result (void)
{
    r_eel_status_t errStat;

    /* Reset the erase resume counter */
    g_eel_str.opPr_str.eraseSuspCnt_u16 = 0u;

    /* Flash erase operation result check */
    errStat = R_EEL_SFct_FlashConvertEraseStatus2ProcessStatus ();

    if (R_EEL_OK == errStat)
    {
        /* Erase OK --> we continue normal */

        /* We lock the process for block status modification */
        g_eel_str.processLock_enu = R_EEL_PR_PR;

        g_eel_str.sm_str[R_EEL_PR_PR].nextState_pfct = R_EEL_SM_PREP_SETPREP_WRITE_EC;
    }
    else if ( (R_EEL_ERR_FLASH_ERROR == errStat) && (R_EEL_ERASE_FAIL_MAX > g_eel_str.opPr_str.eraseFail_u08) )
    {
        g_eel_str.opPr_str.eraseFail_u08++;

        /* Erase error and we can retry */
        R_EEL_FDLIF_Erase (g_eel_str.opPr_str.blk_u16);
    }
    else
    {
        /* On internal or repeated Flash error we finish the process immediately */
        (void)R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (errStat);
    }
} /* R_EEL_SM_Prepare_Chk_Erase_Result */


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Prepare_SetPrep_WriteEC
 *********************************************************************************************************************/
/**
 * State machine prepare process state function to write the erase counter
 *
 * Consisting of:
 * - Start Flash write operation
 * - proceed with write P
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Prepare_SetPrep_WriteEC (void)
{
    uint32_t data,
             add;

    if (g_eel_str.opPr_str.blk_u16 == 0u)
    {
        (g_eel_str.ec_u32)++;
    }

    data = R_EEL_SFct_SetChecksum_8Bit_from_24bit (g_eel_str.ec_u32);
    add  = R_EEL_PFct_Calc_vBlkDataAdd (g_eel_str.opPr_str.blk_u16, R_EEL_BLKHDATA_EC);

    R_EEL_FDLIF_Write ( (const uint32_t *)(&data), add, 1 );

    g_eel_str.sm_str[R_EEL_PR_PR].nextState_pfct = R_EEL_SM_PREP_SETPREP_WRITE_P;
} /* R_EEL_SM_Prepare_SetPrep_WriteEC */


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Prepare_SetPrep_WriteP
 *********************************************************************************************************************/
/**
 * State machine prepare process state function to write the P word
 *
 * Consisting of:
 * - check if preceding write operation was successfully. If yes
 *     - start Flash write operation
 *     - proceed with wait finish prepare process
 * else
 *     - proceed with finish prepare process
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Prepare_SetPrep_WriteP (void)
{
    uint32_t                add;
    r_eel_flash_error_chk_t feChk;

    /* Flash write operation result check */
    feChk = R_EEL_SFct_FlashOpResultCheck_Write (R_EEL_FALSE);
    if (R_EEL_FLERR_CHK_OK == feChk)
    {
        add  = R_EEL_PFct_Calc_vBlkDataAdd (g_eel_str.opPr_str.blk_u16, R_EEL_BLKHDATA_P);

        R_EEL_FDLIF_WriteTag (add);

        g_eel_str.sm_str[R_EEL_PR_PR].nextState_pfct = R_EEL_SM_PREP_WAIT_FINISH;
    }
} /* R_EEL_SM_Prepare_SetPrep_WriteP */


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Prepare_EraseResume
 *********************************************************************************************************************/
/**
 * State machine prepare process state function to resume a suspended Flash erase operation
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
void R_EEL_SM_Prepare_EraseResume (void)
{
    r_eel_status_t res;

    res = R_EEL_FDLIF_EraseResume ();

    if (R_EEL_OK == res)
    {
        /*Call the FDL Handler once in order to process the resume request*/
        g_eel_str.sm_str[R_EEL_PR_PR].flashStatus_enu = R_EEL_FDLIF_Handler ();
        g_eel_str.sm_str[R_EEL_PR_PR].nextState_pfct = R_EEL_SM_PREP_CHK_ERASE_RESULT;
    }
    else
    {
        /* On error we finish the process immediately */
        (void)R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (res);
    }
} /* R_EEL_SM_Prepare_EraseResume */


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Prepare_Wait_Finish
 *********************************************************************************************************************/
/**
 * State machine prepare process state function to wait for prepare end
 *
 * Consisting of:
 * - check preceding write operation
 * - proceed with finish prepare process
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Prepare_Wait_Finish (void)
{
    /* We don't need the function return value here */
    (void)R_EEL_SFct_FlashOpResultCheck_Write (R_EEL_FALSE);

    /* Independent from the failure we finish the process */
    g_eel_str.sm_str[R_EEL_PR_PR].nextState_pfct = R_EEL_SM_PREP_FINISH;
}


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Prepare_Finish
 *********************************************************************************************************************/
/**
 * State machine prepare process state function to end prepare
 *
 * Consisting of:
 * - conditionally set block status in RAM
 * - deactivate prepare process
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Prepare_Finish (void)
{
    r_eel_blockstatus_t stat;
    r_eel_err_flg_t     errFlg;

    errFlg = R_EEL_SFct_ErrStatCheckError_CurProc ();
    if (R_EEL_FLG_OK != errFlg)
    {
        /* In case of Flash error we set the block status invalid */
        stat = R_EEL_BLKSTAT_INVALID;
    }
    else
    {
        stat = R_EEL_BLKSTAT_PREPARED;
    }
    R_EEL_SFct_SetBlkStat (g_eel_str.opPr_str.blk_u16, stat);

    /* We unlock the process here as in case of errors the process is stopped before
       regular unlock */
    g_eel_str.processLock_enu = R_EEL_PR_UNLOCK;

    /* Terminate Prepare process */
    g_eel_str.sm_str[R_EEL_PR_PR].active_enu = R_EEL_FALSE;
} /* R_EEL_SM_Prepare_Finish */


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Format_Start
 *********************************************************************************************************************/
/**
 * State machine format process state function to start the format process
 *
 * Consisting of:
 * - selecting 1st block to prepare
 * - start prepare process
 * - proceed with format next block
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
void R_EEL_SM_Format_Start (void)
{
    uint16_t blk;

    /* Reset the erase counter if required */
    if ( (R_EEL_NULL == g_eel_str.rp_u32) ||
         (R_EEL_EC_MAX <= g_eel_str.ec_u32) )
    {
        g_eel_str.ec_u32 = 0; /* Is increased to 1 by the Prepare operation */
        g_eel_str.opFo_str.curBlk_u16  = 0u;
        g_eel_str.opFo_str.lastBlk_u16 = g_eel_str.vPoolSizeNoVblks_u16 - 1;
    }
    else
    {
        blk = g_eel_str.blkActive_u16;
        g_eel_str.opFo_str.lastBlk_u16 = blk;

        blk  = R_EEL_SFct_Calc_NextBlk_Any (blk, R_EEL_BLK_NEXT);
        g_eel_str.opFo_str.curBlk_u16 = blk;
    }

    /* Start the prepare process */
    R_EEL_SFct_Prepare_StartProcess (g_eel_str.opFo_str.curBlk_u16);

    g_eel_str.sm_str[R_EEL_PR_FO].nextState_pfct = R_EEL_SM_FORMAT_NEXT_BLOCK;
} /* R_EEL_SM_Format_Start */

/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Format_NextBlock
 *********************************************************************************************************************/
/**
 * State machine format process state function to start prepare of further blocks
 *
 * Consisting of:
 * - check result if the previous prepare process was successful. If yes
 *     - Check if last block was prepared. If yes
 *         - start sub-process set active on the next block
 *         - else
 *             - set error
 *         - proceed with format finish
 *     -else
 *         - start prepare process on the next block
 *         - proceed with format next block
 * - else
 *     -proceed with format finish
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Format_NextBlock (void)
{
    uint16_t        nBlk,
                    lBlk;
    r_eel_err_flg_t errFlg;

    /* The under-laying Prepare process must have passed successfully */
    errFlg = R_EEL_SFct_ErrStatCheckError (R_EEL_PR_PR);
    if (R_EEL_FLG_OK != errFlg)
    {
        /* Forward prepare status to format status... on error, Format is finished*/
        (void)R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (g_eel_str.sm_str[R_EEL_PR_PR].rStat_enu);
    }
    else
    {
        if (g_eel_str.opFo_str.lastBlk_u16 == g_eel_str.opFo_str.curBlk_u16)
        {
            /*----- Last block prepared --> activate the 1st block ----- */

            nBlk = g_eel_str.opFo_str.lastBlk_u16;
            nBlk = R_EEL_SFct_Calc_NextBlk_Any (nBlk, R_EEL_BLK_NEXT);

            /* Set block to activate (1 block before) and set RWP for the 1st active block
               RWP must point to the last block in order to close the RWP loop which is the
               base for "previous block" calculations */
            lBlk = g_eel_str.opFo_str.lastBlk_u16;

            /* Start sub-flow setActive */
            R_EEL_SFct_SetActive_StartProcess ( R_EEL_SM_FORMAT_FINISH,
                                                R_EEL_SM_FORMAT_FINISH,
                                                nBlk,
                                                R_EEL_PFct_Calc_vBlkDataAdd (lBlk, R_EEL_BLKHDATA_REFZ) );
        }
        else
        {
            /*----- Prepare the next block ----------------------------- */
            g_eel_str.opFo_str.curBlk_u16
                = R_EEL_SFct_Calc_NextBlk_Any (g_eel_str.opFo_str.curBlk_u16, R_EEL_BLK_NEXT);

            R_EEL_SFct_Prepare_StartProcess (g_eel_str.opFo_str.curBlk_u16);
        }
    }

} /* R_EEL_SM_Format_NextBlock */


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Format_Finish
 *********************************************************************************************************************/
/**
 * State machine format process state function to finish format
 *
 * Consisting of:
 * - setting process result in request structure
 * - setting driver status
 * - deactivate the format process
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_Format_Finish (void)
{
    /* Set the request error */
    g_eel_str.op_str[R_EEL_OP_FO].req_pstr->status_enu = g_eel_str.sm_str[R_EEL_PR_FO].rStat_enu;

    /* Terminate Format process */
    g_eel_str.sm_str[R_EEL_PR_FO].active_enu = R_EEL_FALSE;

    /* Reset any potential supervision error (e.g. R_EEL_ERR_POOL_INCONSISTENT after startup) */
    R_EEL_SFct_ProcessErrorReset (R_EEL_PR_SV);

    /* Set drive status to passive --> Requires R_EEL_Init to restart */
    R_EEL_SFct_SetDriverStatus (R_EEL_ACCESS_LOCKED, R_EEL_OPERATION_PASSIVE);

    /* EEL life cycle forwarded to shut down */
    g_eel_str.r_eel_lcSts_enu = R_EEL_LCSTS_SHUTDOWN;
}



/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Supv_Start
 *********************************************************************************************************************/
/**
 * State machine supervision process state function to startup EEL
 *
 * Consisting of:
 * - initialize important variables
 * - proceed with get block status step 1
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
void R_EEL_SM_Supv_Start (void)
{

    /* Prepare Get block status process step variables */
    g_eel_str.opSv_str.curBlk_u16    = 0u;
    g_eel_str.opSv_str.lastChkBlk    = g_eel_str.vPoolSizeNoVblks_u16 - 1u;
    g_eel_str.opSv_str.actBlkEc_u32  = 0u;

    /* required in supervision_run */
    g_eel_str.opSv_str.lastPr_enu = R_EEL_PR_SV;

    R_EEL_SFct_ForwardSUPVProcessState (R_EEL_SM_SUPV_GET_BLK_STAT1);
}


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_SUPV_Get_Blk_Stat1
 *********************************************************************************************************************/
/**
 * State machine supervision process state function to judge block status resulting
 * from possible Prepare and Refresh process interruptions
 *
 * Consisting of:
 * - loop over all blocks
 *     - judge block status (incl. active block judgement)
 *     - on invalid block without I0/I1 written correctly, leave the loop and set block invalid
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_SUPV_Get_Blk_Stat1 (void)
{
    uint16_t       blk,
                   actBlk;
    uint32_t       actBlkEc;
    r_eel_flag_t   mrkInvalid,
                   endLoop;
    r_eel_status_t iErr;

    if (g_eel_str.opSv_str.actBlkEc_u32 != 0u)
    {
        actBlk      = g_eel_str.blkActive_u16;
        actBlkEc    = g_eel_str.opSv_str.actBlkEc_u32;
    }
    else
    {
        actBlk      = 0u;
        actBlkEc    = 0uL;
    }

    blk        = g_eel_str.opSv_str.curBlk_u16;
    mrkInvalid = R_EEL_FALSE;
    iErr       = R_EEL_OK;

    /* loop over all blocks */
    endLoop = R_EEL_FALSE;
    do
    {
        /* check if all blocks are parsed */
        if (blk <= g_eel_str.opSv_str.lastChkBlk)
        {
            iErr = R_EEL_SFct_Supv_Judge_Blk_Stat (&actBlk, &actBlkEc, blk, &mrkInvalid);

            if (R_EEL_OK == iErr)
            {
                blk++;

                /* Mark a block invalid
                   Note: If we mark a block invalid, we leave the while loop for the set invalid sub-
                   process
                   After finishing this, we enter R_EEL_SM_SUPV_GET_BLK_STAT1 again with the next
                   block number */
                if (R_EEL_TRUE == mrkInvalid)
                {
                    endLoop                        = R_EEL_TRUE;
                    g_eel_str.opSv_str.curBlk_u16  = blk;

                    (void)R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (R_EEL_ERR_FIX_DONE);
                    R_EEL_SFct_SetInvalid_StartProcess (R_EEL_SM_SUPV_GET_BLK_STAT1,
                                                        R_EEL_SM_SUPV_RUN,
                                                        blk - 1);
                }
            }
        }
        else
        {
            endLoop = R_EEL_TRUE;

            if (0uL == actBlkEc)
            {
                /* Finish startup as we found no possibly active block */
                (void)R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (R_EEL_ERR_POOL_INCONSISTENT);
            }
            else
            {
                /* Prepare block pointer for the next sub-process step:
                   If currently considered active block is not active, the search continues
                   backwards in the ring buffer. Search limit (error condition) is when the search
                   reaches the considered active block again */
                g_eel_str.opSv_str.lastChkBlk = actBlk;

                R_EEL_SFct_ForwardSUPVProcessState (R_EEL_SM_SUPV_GET_BLK_STAT2);
            }
        }
    }
    while ( (R_EEL_OK == iErr) && (R_EEL_FALSE == endLoop) );

    g_eel_str.blkActive_u16          = actBlk;
    g_eel_str.opSv_str.actBlkEc_u32  = actBlkEc;
} /* R_EEL_SM_SUPV_Get_Blk_Stat1 */


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_SUPV_Get_Blk_Stat2
 *********************************************************************************************************************/
/**
 * State machine supervision process state function to judge block status resulting from
 * possible activation phase interruption. Therefore the current assumed active block is checked
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_SUPV_Get_Blk_Stat2 (void)
{
    uint16_t        blk;
    uint32_t        add;
    r_eel_flag_t    actBlkFound;
    r_eel_patcmp_t  a1PatMatch,
                    sorPatMatch;
    r_eel_err_flg_t errFlg;
    r_eel_status_t  iErr;

    blk         = g_eel_str.blkActive_u16;
    actBlkFound = R_EEL_FALSE;

    add   = R_EEL_PFct_Calc_vBlkDataAdd (blk, R_EEL_BLKHDATA_A1);
    iErr  = R_EEL_PFct_ReadDFlash_cmpPatBC (add, &a1PatMatch);
    if (R_EEL_OK == iErr)
    {
        if (R_EEL_PATCMP_VALID == a1PatMatch)
        {
            actBlkFound = R_EEL_TRUE;
        }
        else
        {
            /* A1 Pattern is not written, but we may have a REF zone entry, indicated by the 1st
               SOR */
            add  = R_EEL_PFct_Calc_vBlkDataAdd (blk, R_EEL_BLKHDATA_REFZ);
            iErr  = R_EEL_PFct_ReadDFlash_cmpPatBC (add + R_EEL_REF_OFF_SOR, &sorPatMatch);

            if (R_EEL_PATCMP_VALID == sorPatMatch)
            {
                actBlkFound = R_EEL_TRUE;
            }
        }

        if (R_EEL_OK == iErr)
        {
            if (R_EEL_TRUE == actBlkFound)
            {
                /* Prepare next startup process step */
                R_EEL_SFct_ForwardSUPVProcessState (R_EEL_SM_SUPV_CHK_BLK_CONSISTENCY);
            }
            else
            {
                /* Get next possibly active block */
                errFlg = R_EEL_SFct_Calc_NextBlk_DedicatedStatus (
                    ( (uint16_t *)&(g_eel_str.blkActive_u16) ),
                    R_EEL_BLKSTAT_ACTIVE,
                    R_EEL_BLKSTAT_ANY,
                    g_eel_str.opSv_str.lastChkBlk,
                    R_EEL_BLK_PREV);

                if (R_EEL_FLG_ERROR == errFlg)
                {
                    /* Finish startup as we found no active block */
                    (void)R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (R_EEL_ERR_POOL_INCONSISTENT);
                }
                else
                {
                    /* Set invalid & search next block */
                    (void)R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (R_EEL_ERR_FIX_DONE);
                    R_EEL_SFct_SetInvalid_StartProcess (R_EEL_SM_SUPV_GET_BLK_STAT2,
                                                        R_EEL_SM_SUPV_RUN,
                                                        blk);
                }
            }
        } /* if( R_EEL_OK == iErr ) */
    } /* if( R_EEL_OK == iErr ) */
} /* R_EEL_SM_SUPV_Get_Blk_Stat2 */



/*********************************************************************************************************************
 * Function name:  R_EEL_SM_SUPV_Chk_Blk_Consistency
 *********************************************************************************************************************/
/**
 * State machine supervision process state function to check the ring buffer consistency (robustness feature)
 *
 * Consisting of:
 * - loop over all blocks
 *   Error conditions:
 *     - if block is active
 *         - Wrong block age (EC sequence in the ring buffer)
 *         - Wrong RWP, EC checksum
 *         - RWP points to a valid destination
 *     - if block is prepared
 *         - Wrong EC checksum
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_SUPV_Chk_Blk_Consistency (void)
{
    r_eel_blockstatus_t blkStat;
    r_eel_flag_t        endLoop, res, errCon, activePoolComplete;
    uint16_t            blk, blkA, blkAPoolStart, blkChk;
    uint32_t            ec, ecChk,
                        rwp, rwpChk,
                        add;

    blk             = g_eel_str.blkActive_u16;
    blkA            = blk;
    blkAPoolStart   = blk;

    endLoop = R_EEL_FALSE;
    errCon  = R_EEL_FALSE;
    activePoolComplete  = R_EEL_FALSE;

    do
    {
        blkStat = R_EEL_SFct_Calc_BlkStat (blk);

        if (R_EEL_BLKSTAT_INVALID != blkStat)
        {
            add     = R_EEL_PFct_Calc_vBlkDataAdd (blk, R_EEL_BLKHDATA_EC);
            ec      = R_EEL_PFct_ReadDFlashU32 (add);
            ecChk   = ec & R_EEL_MASK_24BIT;
            ecChk   = ( R_EEL_SFct_SetChecksum_8Bit_from_24bit (ecChk) );

            if (R_EEL_BLKSTAT_ACTIVE == blkStat)
            {
                /* -------------------- Test the active pool range ------------------------------- */
                /* We have an active block although before a prepared block was found or an active
                   block pointed to a newer active block */
                if (R_EEL_TRUE == activePoolComplete)
                {
                    errCon = R_EEL_TRUE;      /* Consistency error */
                }

                /* ------------------------ Test active block age -----------------------------------
                   blkAPoolStart starts from the youngest active block (eel_str.blkActive_u16)
                   and is forwarded by the tested blocks RWP. So, blkAPoolStart is always elder
                   or the same age as the tested block. If the tested block is elder, the ring
                   buffer is not consistent */
                if (R_EEL_FALSE == errCon)
                {
                    res = R_EEL_SFct_ChkBlockElder (blk, blkAPoolStart);
                    if (R_EEL_TRUE == res)
                    {
                        errCon = R_EEL_TRUE;      /* Consistency error */
                    }
                }

                /* -------------------- Check the active blocks checksums of RWP, EC ---- */
                if (R_EEL_FALSE == errCon)
                {
                    add     = R_EEL_PFct_Calc_vBlkDataAdd (blk, R_EEL_BLKHDATA_RWP);
                    rwp     = R_EEL_PFct_ReadDFlashU32 (add);
                    rwpChk  = rwp & R_EEL_MASK_24BIT;
                    rwpChk  = ( R_EEL_SFct_SetChecksum_8Bit_from_24bit (rwpChk) );

                    /* RWP & EC consistency check */
                    if ( (rwp != rwpChk) || (ec != ecChk) )
                    {
                        errCon = R_EEL_TRUE;      /* Consistency error */
                    }

                    /* -------------------- Check the active blocks RWP value ----------------------- */
                    /* RWP points to:
                        - active block: Update the active pool start block
                        - not active block outside the active pool: Do nothing
                        - not active block inside the active pool: Inconsistency error
                       Note: we need to re-read RWP with the function R_EEL_PFct_Calc_BlockRWP as the
                             Data Flash offset was masked out previously */
                    rwp     = R_EEL_PFct_Calc_BlockRWP (blk);
                    blkChk  = R_EEL_PFct_Calc_Add2vBlk (rwp);
                    blkStat = R_EEL_SFct_Calc_BlkStat (blkChk);

                    if (R_EEL_BLKSTAT_ACTIVE == blkStat)
                    {
                        /* if rwp points to a younger active block, the end of the active pool is found
                           E.g.: former block scenario  - A(old) I I I A(old) - resulted in
                                 - A(new) P P P A(old) - after some prepare operations */
                        res = R_EEL_SFct_ChkBlockElder (blk, blkChk);
                        if (R_EEL_TRUE == res)
                        {
                            activePoolComplete = R_EEL_TRUE;
                        }
                        else
                        {
                            blkAPoolStart = blkChk;
                        }
                    }
                } /* if( R_EEL_TRUE == res ) - else */
            }
            else /* if( R_EEL_BLKSTAT_ACTIVE == blkStat ) */
            {
                /* Check the checksums of EC */
                /* 1st occurrence of a prepared block closes the active pool range */
                activePoolComplete = R_EEL_TRUE;

                if (ec != ecChk)
                {
                    errCon = R_EEL_TRUE;      /* Consistency error */
                }
            }
        }

        /* Forward to previous block */
        blk = R_EEL_SFct_Calc_NextBlk_Any (blk, R_EEL_BLK_PREV);
        if (blk == blkA)
        {
            endLoop = R_EEL_TRUE;
        }
    }
    while ( (R_EEL_FALSE == endLoop) && (R_EEL_FALSE == errCon) );

    if (R_EEL_FALSE == errCon)
    {
        /* Prepare next startup process step */
        R_EEL_SFct_ForwardSUPVProcessState (R_EEL_SM_SUPV_CHK_POOL_FULL);
    }
    else
    {
        /* Due to inconsistent pool we finish the startup */
        (void)R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (R_EEL_ERR_POOL_INCONSISTENT);
    }
} /* R_EEL_SM_SUPV_Chk_Blk_Consistency */


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_SUPV_Chk_Pool_Full
 *********************************************************************************************************************/
/**
 * State machine supervision process state function to initialize block oriented
 * variables and to check if we got an interruption in pool full situation.
 * Later one results in invalidating and preparing the active block.
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_SUPV_Chk_Pool_Full (void)
{
    uint16_t blk, blk1,
             blkCntPassive,
             blkToInvalidate;
    r_eel_err_flg_t errFlg;

    /* ------------- Block Check end --> initialize block oriented variables -------------------- */
    /* Init block status counters */
    R_EEL_SFct_Init_BlkStatCnt ();

    /* Calculate the Prepare block pointer & erase counter */
    blk = g_eel_str.blkActive_u16;
    do
    {
        errFlg = R_EEL_SFct_Calc_NextBlk_DedicatedStatus ( (&blk),
                                                           R_EEL_BLKSTAT_PREPARED,
                                                           R_EEL_BLKSTAT_ACTIVE,
                                                           g_eel_str.blkActive_u16,
                                                           R_EEL_BLK_NEXT );
    }
    while (R_EEL_FLG_OK == errFlg);

    /* blk points either to the latest prepared block or to the active block if no prepared
       one was found --> This block contains the latest erase counter */
    g_eel_str.ec_u32 = R_EEL_PFct_Calc_BlockEC (blk);

    blk1 = R_EEL_SFct_Calc_NextBlk_Any (blk, R_EEL_BLK_NEXT);
    g_eel_str.blkPrep_u16 = blk1;

    /* Calculate the last active block pointer & Refresh pointer */
    errFlg = R_EEL_SFct_Calc_NextBlk_DedicatedStatus ( (&blk),
                                                       R_EEL_BLKSTAT_ACTIVE,
                                                       R_EEL_BLKSTAT_PREPARED,
                                                       g_eel_str.blkActive_u16,
                                                       R_EEL_BLK_NEXT );
    if (R_EEL_FLG_OK != errFlg)
    {
        /* Only one active block, so we get an error and must patch the result */
        blk = g_eel_str.blkActive_u16;
    }
    g_eel_str.blkOEActive_u16 = blk;
    g_eel_str.blkRef_u16 = blk;
    R_EEL_PFct_PrepLoopLimitReset ();

    /* Set bit error check starting point to eldest active block base address
       This is not a must, but makes sense as this is the eldest possible valid data */
    g_eel_str.opSv_str.bitChkAdd_enu32 = R_EEL_PFct_Calc_vBlkBaseAdd (blk);

    /* ------------- Pool full check ------------------------------------------------------------
       --> Must be executed when all pointers are available as these are used for the calculation */
    blkCntPassive = g_eel_str.blkCntPrep_u16 + g_eel_str.blkCntInv_u16;
    if (0u == blkCntPassive)
    {
        /* Backward the active block */
        blkToInvalidate = g_eel_str.blkActive_u16;
        errFlg = R_EEL_SFct_Calc_NextBlk_DedicatedStatus ( (uint16_t *)(&g_eel_str.blkActive_u16),
                                                           R_EEL_BLKSTAT_ACTIVE,
                                                           R_EEL_BLKSTAT_PREPARED,
                                                           g_eel_str.blkActive_u16,
                                                           R_EEL_BLK_PREV );
        if (R_EEL_FLG_OK != errFlg)
        {
            /* Here  we should never end */
            (void)R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (R_EEL_ERR_INTERNAL);
        }
        else
        {
            /* Make the active block invalid */
            (void)R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (R_EEL_ERR_FIX_DONE);
            R_EEL_SFct_SetInvalid_StartProcess (R_EEL_SM_SUPV_GET_POINTERS,
                                                R_EEL_SM_SUPV_RUN,
                                                blkToInvalidate);
            g_eel_str.blkPrep_u16 = blkToInvalidate; /* Correct next block to prepare */
        }
    }
    else
    {
        /* Prepare next startup process step */
        R_EEL_SFct_ForwardSUPVProcessState (R_EEL_SM_SUPV_GET_POINTERS);
    }
} /* R_EEL_SM_SUPV_Chk_Pool_Full */


/*********************************************************************************************************************
 * Function name:  R_EEL_SM_SUPV_Get_Pointers
 *********************************************************************************************************************/
/**
 * State machine supervision process state function to initialize important pointers (RP and WP):
 * - Search forward for the last SOP (Determine RP)
 * - From there search backward to find the next DS with valid data (for WP)
 * - Check special conditions judged as pool full
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_SUPV_Get_Pointers (void)
{
    uint32_t rp, rpLimit, rpTmp, blk1stRp,
             wp,
             bcCnt, bcStart, dzStartAddress;
    uint16_t         blk;
    r_eel_flag_t     endLoop, blkFull;
    r_eel_patcmp_t   eor0PatMatch,
                     sorPatMatch;
    r_eel_status_t   iErr;
    r_eel_bcResult_t sorBC, bc;

    /* ------------------------------------------------------------------------------------------ *\
        Search the end of REF zone --> set rp, set info for last DS with data required to update
        wp (we must cover the case that the last DSs are invalidated)
    \* ------------------------------------------------------------------------------------------ */
    blk              = g_eel_str.blkActive_u16;
    blkFull          = R_EEL_FALSE;

    /* ---------- Search "forward" from block bottom to find the last REF entry --------------- */
    blk1stRp = R_EEL_PFct_Calc_vBlkDataAdd (blk, R_EEL_BLKHDATA_REFZ);
    rp       = blk1stRp - R_EEL_REF_OFF_DS;
    rpLimit  = (R_EEL_PFct_Calc_vBlkDataAdd (blk, R_EEL_BLKHDATA_DATAZ) - R_EEL_REF_OFF_DS) + R_EEL_FDL_WRITESIZE;
    /* Last possible REF entry must fit into the block.
       e.g. calculated DZ start address (Last add. to write) = 0x7F8, REF size = 0x10 --> last entry @ 7EC~7FB */
    endLoop = R_EEL_FALSE;
    do
    {
        rp += R_EEL_REF_OFF_DS;
        iErr = R_EEL_PFct_ReadDFlash_BCcmpPat (rp + R_EEL_REF_OFF_SOR, &sorPatMatch, &sorBC);

        if (R_EEL_OK == iErr)
        {
            if (R_EEL_BC_BLANK == sorBC)
            {
                /* Normal end of REF zone found */
                endLoop = R_EEL_TRUE;
            }
            else
            {
                if (R_EEL_PATCMP_VALID != sorPatMatch)
                {
                    /* DS Write interrupted during SOR write:
                       - end of REF zone found
                       - we do not continue in this block to avoid unstable SOR inside the REF
                         zone */
                    endLoop = R_EEL_TRUE;
                    blkFull = R_EEL_TRUE;
                }
            }
        } /* if( R_EEL_OK == iErr ) */
    }
    while ( (R_EEL_OK == iErr) && ( (rp < rpLimit) && (R_EEL_FALSE == endLoop) ) );

    /* Here rp points to:
       - 1st blank REF entry (SOR) (incl. 1st REF entry, this must be considered)
       - or RP limit (last possible REF entry) */

    /* ---------- check if previous DS write was completed ----------------------------------------- */
    if ( (R_EEL_OK == iErr) && (R_EEL_FALSE == blkFull) )
    {
        if (blk1stRp != rp) /* no previous DS ... block is empty */
        {
            rpTmp   = rp - R_EEL_REF_OFF_DS;
            iErr = R_EEL_PFct_ReadDFlash_cmpPatBC (rpTmp + R_EEL_REF_OFF_EOR0, &eor0PatMatch);
            if (R_EEL_OK == iErr)
            {
                if (R_EEL_PATCMP_VALID != eor0PatMatch)
                {
                    blkFull = R_EEL_TRUE;
                    /*the last DS entry is invalid because DRP and data are possibly not written*/
                    rp = rpTmp;
                }
            }
        }
    }

    /* ------------------------------------------------------------------------------------------ *\
     Calculate wp:
     We have RP and the information if the last EOR0 is written.
     1) If EOR0 not written, the block is considered as full, WP is not required and set RP=WP
     2) If EOR0 is written the potential data zone is either written or blank. Partially written
        data is not possible as each data write was completed
        --> execute blank check on the data zone to identify the WP
        --> length information of the DSs is not required. It would not be available anyhow as
            incomplete ID-L table needs to be considered.
    \* ------------------------------------------------------------------------------------------ */

    wp = rp; /* default value (block full) */

    if ( (R_EEL_OK == iErr) && (R_EEL_FALSE == blkFull) )
    {

        /* Possible reason for non blank cells in the fill zone:
           - On an ID-L table update, possibly DS length was decreased, so data
             might be in the fill zone */
        bcStart =  rp;
        dzStartAddress =  R_EEL_PFct_Calc_vBlkDataAdd (blk, R_EEL_BLKHDATA_DATAZ);
        bcCnt     =  ( (dzStartAddress + R_EEL_FDL_WRITESIZE) - rp ) / R_EEL_FDL_WRITESIZE;

        iErr = R_EEL_PFct_BlankCheckDFlash (&bcStart, bcCnt, &bc);

        if (R_EEL_OK == iErr)
        {
            if (R_EEL_BC_WRITTEN == bc)
            {
                /* Plausibility check of BC fail address - should never match */
                if ( (bcStart > dzStartAddress) ||
                     (bcStart == rp) )
                {
                    iErr = R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (R_EEL_ERR_INTERNAL);
                }
                else
                {
                    wp = bcStart - R_EEL_FDL_WRITESIZE;
                }
            }
            else
            {
                /* Complete data range is blank */
                wp = dzStartAddress;
            }
        } /* if (R_EEL_OK == iErr ) */
    } /* if( ( R_EEL_OK == iErr ) && ( R_EEL_FALSE == blkFull ) ) */

    g_eel_str.rp_u32 = rp;
    g_eel_str.wp_u32 = wp;

    if (R_EEL_OK == iErr)
    {
        R_EEL_SFct_SetDriverStatus (R_EEL_ACCESS_READ_WRITE, R_EEL_OPERATION_STARTUP);

        /* --------------- Prepare RAM table fill process ----------------------- */
        g_eel_str.opSv_str.ramTableFillCntIDFound_u16 = 0u;

        R_EEL_SFct_ForwardSUPVProcessState (R_EEL_SM_SUPV_GET_RAMTABLE);
    } /* if( R_EEL_OK == iErr ) */
} /* R_EEL_SM_SUPV_Get_Pointers */



/*********************************************************************************************************************
 * Function name:  R_EEL_SM_SUPV_Get_Ram_Table
 *********************************************************************************************************************/
/**
 * State machine supervision process state function to initialize the RAM table
 *
 * Consisting of:
 * - loop through all DS in the emulation
 *     - search next valid DS
 *     - if the DS ID is known in the ID-L table
 *         - check RAM table entry. If not yet filled
 *             - initialize the entry
 * - set flag to execute DS margin check in the supervision run loop
 * - proceed with supervision run
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule 11.4 (QAC message 0310)
 * Reason:       For effective embedded programming, pointer to pointer conversions are used
 * Verification: The converted addresses are essential for complete code execution. Incorrect
 *               conversion would result in test fails.
 *********************************************************************************************************************/
R_EEL_STATIC void R_EEL_SM_SUPV_Get_Ram_Table (void)
{
    uint32_t rp;
    uint16_t id,
             idxMax,
             idxFound, cntIdFound;
    uint16_t *     IDXTab;
    r_eel_flag_t   endLoop;
    r_eel_chk_ds_t chkDS;
    r_eel_status_t iErr;
    uint16_t       idAr[R_EEL_RAMTBL_FILL_IDXCNT][2];
    uint16_t       tblMinID, tblMaxID,
                   minID, maxID,
                   mintIdx, maxtIdx,
                   tbLo, tbHi,
                   tIdx, idxCnt,
                   idxRemain, idxStart,
                   blk;

    blk = g_eel_str.opSv_str.ramTableFillblk_u16;

    idxMax      = g_eel_str.RTCfg_pstr->IDLTabIdxCnt_u16;
    idxCnt      = R_EEL_RAMTBL_FILL_IDXCNT;
    idxRemain   = idxMax - (uint16_t)(blk * R_EEL_RAMTBL_FILL_IDXCNT);
    if (R_EEL_RAMTBL_FILL_IDXCNT > idxRemain)
    {
        idxCnt = idxRemain;
    }
    idxStart = idxMax - idxRemain;

    /* Fill the partial table with sorted IDs */
    tblMinID = 0x0u;
    tblMaxID = 0xFFFFu;

    /* Just set for QAC checking. not required for the algorithm */
    mintIdx  = 0x0000u;
    maxtIdx  = 0x0000u;

    tbLo = 0u;
    tbHi = idxCnt - 1;
    while (tbLo <= tbHi)
    {
        minID = 0xFFFFu;
        maxID = 0u;

        for (tIdx = idxStart; tIdx < (idxStart + idxCnt); tIdx++)
        {
            id = g_eel_str.RTCfg_pstr->IDLTab_pstr[tIdx].ID_u16;                                    /* PRQA S 0491 */
            if ( (id > maxID) && (id < tblMaxID) )
            {
                maxID   = id;
                maxtIdx = tIdx;
            }
            if ( (id < minID) && (id > tblMinID) )
            {
                minID   = id;
                mintIdx = tIdx;
            }
        }
        tblMinID = minID;
        tblMaxID = maxID;

        idAr[tbLo][0] = minID;
        idAr[tbLo][1] = mintIdx;
        idAr[tbHi][0] = maxID;
        idAr[tbHi][1] = maxtIdx;

        tbLo++;
        if (0u != tbHi)
        {
            tbHi--;
        }
    }

    rp          = g_eel_str.rp_u32;
    cntIdFound  = g_eel_str.opSv_str.ramTableFillCntIDFound_u16;

    IDXTab      = g_eel_str.RTCfg_pstr->IDXTab_pau16;

    endLoop     = R_EEL_FALSE;
    iErr        = R_EEL_OK;
    do
    {
        R_EEL_SFct_SearchDS (rp, 0x0000u, R_EEL_SEARCHDS_ANY, &rp);

        if (R_EEL_NULL == rp)
        {
            /* All REF entries parsed --> we are ready */
            endLoop = R_EEL_TRUE;
        }
        else
        {
            id = R_EEL_PFct_Get_RefAdd2ID (rp);

            /* Search the ID in the RAM table */
            idxFound = R_EEL_PFct_ConvertId2TIdxSorted (id, (const uint16_t (*)[2])idAr, idxCnt); /* PRQA S 0310 */

            if (R_EEL_ID_NOT_FOUND != idxFound)
            {
                idxFound = idAr[idxFound][1];
                if (idxFound < g_eel_str.RTCfg_pstr->IDLTabIdxCnt_u16)
                {
                    /* Check if we need the DS with the given ID */
                    if (0u == IDXTab[idxFound])                                                 /* PRQA S 0491 */
                    {
                        /* We need the DS, now we check if it is really valid */
                        iErr = R_EEL_SFct_Chk_DSValid (rp, &chkDS);
                        if ( (R_EEL_OK == iErr) &&
                             (R_EEL_CHKDS_INVALID != chkDS) )
                        /* Accept: R_EEL_CHKDS_VALID, R_EEL_CHKDS_VALID_EOR_INCOMPLETE */
                        {
                            /* We found a valid data set */
                            IDXTab[idxFound] = R_EEL_PFct_ConvertRefAdd2WIdx (rp);              /* PRQA S 0491 */
                            cntIdFound++;

                        } /* if( R_EEL_OK == iErr ) */
                        if (idxMax == cntIdFound)
                        {
                            /* Table is filled completely --> We are ready */
                            endLoop = R_EEL_TRUE;
                        }
                    } /* if( 0u == IDXTab[idxFound] ) */
                } /* if (idAr[idxFound][1] < g_eel_str.RTCfg_pstr->IDLTabIdxCnt_u16) */
            } /* if (R_EEL_ID_NOT_FOUND != idxFound) */
        } /* if( R_EEL_NULL = rp ) - else */
    }
    while ( (R_EEL_OK == iErr) && (R_EEL_FALSE == endLoop) );

    if (R_EEL_OK == iErr)
    {
        /* Update counter of found IDs for the RAM table */
        g_eel_str.opSv_str.ramTableFillCntIDFound_u16 = cntIdFound;

        if (R_EEL_RAMTBL_FILL_IDXCNT >= idxRemain)  /* This was the last ID block */
        {
            /* RAM table is filled
               now prepare DS margin check and enter continuous operation */
            g_eel_str.opSv_str.curIdx_u16 = 0;
            g_eel_str.opSv_str.dsMarginChk_enu = R_EEL_MRGCHK_ACTIVE;

            /* Set RAM table initialized flag */
            g_eel_str.opSv_str.ramTableInit_enu = R_EEL_TRUE;

            R_EEL_SFct_SetDriverStatus (R_EEL_ACCESS_UNLOCKED, R_EEL_OPERATION_UNDEFINED);

            R_EEL_SFct_ForwardSUPVProcessState (R_EEL_SM_SUPV_RUN);
        } /* if (R_EEL_RAMTBL_FILL_IDXCNT >= idxRemain) */
        else
        {
            /* Prepare for the next RAM table fill process step call */
            g_eel_str.opSv_str.ramTableFillblk_u16++;
        }
    } /* if( R_EEL_OK == iErr ) */
} /* R_EEL_SM_SUPV_Get_Ram_Table */



/*********************************************************************************************************************
 * Function name:  R_EEL_SM_Supv_Run
 *********************************************************************************************************************/
/**
 * State machine supervision process main supervision loop. Here DS margin
 * check, prepare and refresh are supervised as well as bit error check
 *
 * Consisting of:
 * - check slave process (started by SV) status. If error
 *     - set driver status locked
 * - else
 *     - if margin check active
 *         - call margin check function
 *     - else
 *         - set driver status unlocked
 *     - if margin check no longer active
 *         - check refresh threshold
 *         - check bit errors
 *         - if blocks to prepare
 *             - start prepare process
 *         - else
 *             - if blocks to refresh
 *                 - start refresh process
 *
 * Some called sub-routines, reading Data Flash with blank check might end with R_EEL_ERR_INTERNAL
 * on blank check. This results in a process error.
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
void R_EEL_SM_Supv_Run (void)
{
    r_eel_process_id_t lastSVPr;
    r_eel_err_flg_t    errFlg;
    r_eel_status_t     lastPrStat;

    /* Get last slave process status and update supervision process error accordingly */
    lastSVPr = g_eel_str.opSv_str.lastPr_enu;
    g_eel_str.opSv_str.lastPr_enu = R_EEL_PR_SV;
    lastPrStat  = g_eel_str.sm_str[lastSVPr].rStat_enu;                           /* PRQA S 3689 */

    /* Special handling of: SUPV (Margin check) started a WR process but this couldn't complete due to pool full
       - Ignore the error here
       - Set a flag for DS margin check
       - Rewind check table index which is increased during margin check. We need to recheck the DS after pool full
         is fixed
       - next DS margin check will detect that and will be suspended once */
    if ( (R_EEL_ERR_POOL_FULL == lastPrStat) &&
         (R_EEL_PR_WR == lastSVPr) )
    {
        g_eel_str.opSv_str.dsMarginChk_enu = R_EEL_MRGCHK_SUSPENDED;
        lastPrStat = R_EEL_OK;

        g_eel_str.opSv_str.curIdx_u16--;
    }

    (void)R_EEL_SFct_ProcessErrorUpdate_CurProcDefaultErrState (lastPrStat);

    /* Check if the slave status was an error or OK/warning */
    errFlg = R_EEL_SFct_ErrStatCheckError_CurProc ();
    if (R_EEL_FLG_OK != errFlg)
    {
        /* End the system with the error */
        R_EEL_SFct_SetDriverStatus (R_EEL_ACCESS_LOCKED, R_EEL_OPERATION_PASSIVE);
    }
    else
    {
        if ( R_EEL_OK != R_EEL_SFct_Supv_Run () )
        {
            /* On internal error in R_EEL_SFct_Supv_Run, end the system with the error */
            R_EEL_SFct_SetDriverStatus (R_EEL_ACCESS_LOCKED, R_EEL_OPERATION_PASSIVE);
        }
    }
} /* R_EEL_SM_Supv_Run */


/*********************************************************************************************************************
 * Function name:  R_EEL_SMachine_GetActiveProcess
 *********************************************************************************************************************/
/**
 * EEL state machine function to get the active process with highest priority
 *
 * @param          ---
 * @return         active process number
 *                 - <  R_EEL_PR_END: active process
 *                 - == R_EEL_PR_END: no active process
 */
/*********************************************************************************************************************/
/*********************************************************************************************************************
 * MISRA Rule:   MISRA-C 2004 rule --- (QAC message 1481)
 * Reason:       arithmetic operation with enum type
 * Verification: Considered enumeration is sequential and loop limit is correct
 *********************************************************************************************************************/
r_eel_process_id_t R_EEL_SMachine_GetActiveProcess (void)
{
    r_eel_process_id_t i,
                       ret;

    ret = R_EEL_PR_END;
    i   = (r_eel_process_id_t)0;

    do
    {
        if (R_EEL_TRUE == g_eel_str.sm_str[i].active_enu)
        {
            ret = i;
        }
        i++;                                                                    /* PRQA S 1481 */
    }
    while ( (i < R_EEL_PR_END) && (ret == R_EEL_PR_END) );

    return (ret);
} /* R_EEL_SMachine_GetActiveProcess */

/*********************************************************************************************************************
 * Function name:  R_EEL_SMachine_Main
 *********************************************************************************************************************/
/**
 * EEL state machine control function.
 *
 * Consisting of:
 * - check if the processes are unlocked. If yes
 *     Select the active process with highest priority
 * - else
 *     - if read process is active
 *         select Read
 *     - else
 *         select the locked process
 * - execute the next process function / state of the selected process
 *
 * @param          ---
 * @return         ---
 */
/*********************************************************************************************************************/
#define R_EEL_START_SEC_CONST
#include "r_eel_mem_map.h"                                                                          /* PRQA S 5087 */

void R_EEL_SMachine_Main (void)
{
    r_eel_process_id_t      pId;
    r_eel_write_proc_data_t wp;

    if (R_EEL_PR_UNLOCK == g_eel_str.processLock_enu)
    {
        /* Standard search for the highest priority active process */
        pId = R_EEL_SMachine_GetActiveProcess ();
    }
    else
    {
        /* In case of a locked process only the highest priority Read process has preference
           regarding the locked process. So, the active process loop is passed only once to
           check the Read process. If this is not active, the locked process is executed
           Exception: in startup phase, the read operation search mechanism refers to the
           RP and RWP of the active block. On Write operation during the locked period
           (block activation) there is a short period where RP is forwarded but the block
           is not active (RWP not available). During that time the search does not work,
           so Read may not be executed during locked period. */
        if ( (R_EEL_TRUE == g_eel_str.sm_str[R_EEL_PR_RE].active_enu)
             && (R_EEL_ACCESS_UNLOCKED == g_eel_str.ds_str.accessStatus_enu) )
        {
            pId = R_EEL_PR_RE;
        }
        else
        {
            pId = g_eel_str.processLock_enu;
        }
    }

    /* Call highest priority process if we have any active process */
    if (R_EEL_PR_END != pId)
    {
        g_eel_str.curPId_enu = pId;
        g_eel_str.pCurP_pstr = ( &(g_eel_str.sm_str[pId]) );                      /* PRQA S 3689 */

        wp = R_EEL_SFct_ConvertProcID2WriteProcID (pId);
        g_eel_str.pCurWP_pstr = ( &(g_eel_str.opWt_str[wp]) );

        /* Call the state function */
        g_eel_str.pCurP_pstr->nextState_pfct ();
    }
} /* R_EEL_SMachine_Main */

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


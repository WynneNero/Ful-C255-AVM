#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_OFF 0292
#endif
/*********************************************************************************************************************
 * Library       : EEPROM Emulation Library for Renesas RH850 devices
*
 * File Name     : $Source: r_eel_global.h $
 * Lib. Version  : $RH850_EEL_LIB_VERSION_T01: V2.01 $
 * Mod. Revision : $Revision: 1.20 $
 * Mod. Date     : $Date: 2017/02/07 09:12:09JST $
 * Device(s)     : RV40 Flash based RH850 microcontroller
 * Description   : EEPROM emulation related global definitions
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

#ifndef R_EEL_GLOBAL_H
#define R_EEL_GLOBAL_H

# include "Compiler_Cfg.h"

/*********************************************************************************************************************
 * Global compiler definitions
 *********************************************************************************************************************/
#define R_EEL_COMP_GHS GHS /* 1 pjl_20160908 modify as vicp*/
#define R_EEL_COMP_IAR  IAR /* 2*/
#define R_EEL_COMP_REC  CBPLUS /* 3*/

#if defined (__IAR_SYSTEMS_ASM__)
    #define R_EEL_COMPILER R_EEL_COMP_IAR
#elif defined (__IAR_SYSTEMS_ICC__)
    #define R_EEL_COMPILER R_EEL_COMP_IAR
#elif defined (__v850e3v5__)
    #define R_EEL_COMPILER R_EEL_COMP_REC
#else /*GHS */
    #define R_EEL_COMPILER R_EEL_COMP_GHS
#endif

/*********************************************************************************************************************
 * Include list
 *********************************************************************************************************************/
#include "FDL_Cfg.h"
#include "EEL_Cfg.h"
#include "R_TypeDefs.h"
#include "R_FDL.h"
#include "R_FDL_Global.h"
#include "R_FDL_Env.h"
#include "R_EEL.h"

/*********************************************************************************************************************
 *  Global constants (define, const, ...)
 *********************************************************************************************************************/
/* -------------------- Library version string ----------------------------- */
#define R_EEL_VERSION_STRING      "EH850T01xxxxxxV201"

/* -------------------- Misc defines --------------------------------------- */
#define R_EEL_NULL                0x00000000uL              /**< NULL pointer */
#define R_EEL_EC_MAX              0x00FFFFF0uL              /**< Max EC value */
#define R_EEL_PATTERN_VALID       0x55555555uL              /**< Write pattern for A0/1, E0/1, P */
#define R_EEL_PATTERN_BLANK_WD    0xFFFFFFFFuL              /**< Blank word pattern */
#define R_EEL_MASK_24BIT          0x00FFFFFFuL              /**< Bit mask 24bit value */
#define R_EEL_BLANK_24BIT         0x00FFFFFFuL              /**< Blank value 24bit */
#define R_EEL_ID_NOT_FOUND        0xFFFFu                   /**< ID not found pattern (invalid ID) */
#define R_EEL_PREPLOOPLIMIT_OFF   0xFFFFu                   /**< Prepare/Refresh loop check off marker */
#define R_EEL_FDL_WRITESIZE       4uL                       /**< Write size of the FDL in Bytes */
#define R_EEL_ERASE_FAIL_MAX      3u                        /**< Max number of erase fail before issuing erase
                                                                 fail error */
#define R_EEL_DRP_INVALIDATE_FLG  0x80000000uL              /**< Invalid flag in the DRP word */
#define R_EEL_DRP_DATA_MASK       0x7FFF0000uL              /**< Address mask in the DRP */

#define R_EEL_REQUEST_POINTER_UNDEFINED   \
    (r_eel_request_t *)(0x00000000uL)                       /**< request pointer pointing to NULL */

#define R_EEL_RAMTABLEFILL_LOOPCNT    10                    /**< loop counter for the RAM table fill loop */
#define R_EEL_BC_CNT_TIMEOUT      400000                    /**< timeout counter for the blank check
                                                                 >2s at 48MHz */
#define R_EEL_RAMTBL_FILL_IDXCNT  40uL                      /**< ID buffer RAM table size */
#define R_EEL_SHIFT_ADD_TO_WIDX   1uL                       /**< address shift between widx and address */
#define R_EEL_READ_CNT_MAX        0x40                      /**< number of bytes to read from Flash in one step */
#define R_EEL_MAX_VBLOCKS         0x40                      /**< supporting max 64 virtual blocks in the EEL */
/*********************************************************************************************************************
 * Global type definitions
 *********************************************************************************************************************/
/* -------------------- Library internal enumerations definitions ---------- */
/*   defines for function pointers */
#define     R_EEL_SM_READ_START                (&R_EEL_SM_Read_Start)                                    /* Read */
#define     R_EEL_SM_WRITE_INC_START           (&R_EEL_SM_WriteInc_Start)                                /* Write */
#define     R_EEL_SM_WRITE_START               (&R_EEL_SM_Write_Start)
#define     R_EEL_SM_WRITE_SOR                 (&R_EEL_SM_Write_SOR)
#define     R_EEL_SM_WRITE_DRP                 (&R_EEL_SM_Write_DRP)
#ifdef R_EEL_SUPPORT_EXT_FEATURES
    #define R_EEL_SM_WRITE_WRITE_COUNTER       (&R_EEL_SM_Write_WriteCnt)
    #define R_EEL_SM_WRITE_FAST_INV            (&R_EEL_SM_Write_FastInvalidate)
    #define R_EEL_SM_WRITE_SAFE_INV            (&R_EEL_SM_Write_SafeInvalidate)
#endif
#define     R_EEL_SM_WRITE_SET_ACTIVE_ERROR    (&R_EEL_SM_Write_SetActiveError)
#define     R_EEL_SM_WRITE_DATA                (&R_EEL_SM_Write_Data)
#define     R_EEL_SM_WRITE_CMP_DATA            (&R_EEL_SM_Write_CmpData)
#define     R_EEL_SM_WRITE_EOR0                (&R_EEL_SM_Write_EOR0)
#define     R_EEL_SM_WRITE_EOR1                (&R_EEL_SM_Write_EOR1)
#define     R_EEL_SM_WRITE_WAIT_FINISH         (&R_EEL_SM_Write_Wait_Finish)
#define     R_EEL_SM_WRITE_FINISH              (&R_EEL_SM_Write_Finish)
#define     R_EEL_SM_PREP_START                (&R_EEL_SM_Prepare_Start)                                 /* Preparation */
#define     R_EEL_SM_PREP_ERASE_RESUME         (&R_EEL_SM_Prepare_EraseResume)
#define     R_EEL_SM_PREP_CHK_ERASE_RESULT     (&R_EEL_SM_Prepare_Chk_Erase_Result)
#define     R_EEL_SM_PREP_SETPREP_WRITE_EC     (&R_EEL_SM_Prepare_SetPrep_WriteEC)
#define     R_EEL_SM_PREP_SETPREP_WRITE_P      (&R_EEL_SM_Prepare_SetPrep_WriteP)
#define     R_EEL_SM_PREP_WAIT_FINISH          (&R_EEL_SM_Prepare_Wait_Finish)
#define     R_EEL_SM_PREP_FINISH               (&R_EEL_SM_Prepare_Finish)
#define     R_EEL_SM_REFR_START                (&R_EEL_SM_Refresh_Start)                                 /* Refresh */
#define     R_EEL_SM_REFR_FINISH               (&R_EEL_SM_Refresh_Finish)
#define     R_EEL_SM_FORMAT_START              (&R_EEL_SM_Format_Start)                                  /* Format */
#define     R_EEL_SM_FORMAT_NEXT_BLOCK         (&R_EEL_SM_Format_NextBlock)
#define     R_EEL_SM_FORMAT_FINISH             (&R_EEL_SM_Format_Finish)
#define     R_EEL_SM_SUPV_START                (&R_EEL_SM_Supv_Start)                                    /* Supervision */
#define     R_EEL_SM_SUPV_GET_BLK_STAT1        (&R_EEL_SM_SUPV_Get_Blk_Stat1)
#define     R_EEL_SM_SUPV_GET_BLK_STAT2        (&R_EEL_SM_SUPV_Get_Blk_Stat2)
#define     R_EEL_SM_SUPV_CHK_BLK_CONSISTENCY  (&R_EEL_SM_SUPV_Chk_Blk_Consistency)
#define     R_EEL_SM_SUPV_CHK_POOL_FULL        (&R_EEL_SM_SUPV_Chk_Pool_Full)
#define     R_EEL_SM_SUPV_GET_POINTERS         (&R_EEL_SM_SUPV_Get_Pointers)
#define     R_EEL_SM_SUPV_GET_RAMTABLE         (&R_EEL_SM_SUPV_Get_Ram_Table)
#define     R_EEL_SM_SUPV_RUN                  (&R_EEL_SM_Supv_Run)
#define     R_EEL_SM_SET_ACTIVE_A0             (&R_EEL_SM_Set_Active_A0)                                 /* Sub-Processes) used by different processes */
#define     R_EEL_SM_SET_ACTIVE_RWP            (&R_EEL_SM_Set_Active_RWP)
#define     R_EEL_SM_SET_ACTIVE_A1             (&R_EEL_SM_Set_Active_A1)
#define     R_EEL_SM_SET_ACTIVE_WAIT_END       (&R_EEL_SM_Set_Active_WaitEnd)
#define     R_EEL_SM_SET_ACTIVE_END            (&R_EEL_SM_Set_Active_End)
#define     R_EEL_SM_SET_INVALID_I0            (&R_EEL_SM_Set_Invalid_I0)
#define     R_EEL_SM_SET_INVALID_I1            (&R_EEL_SM_Set_Invalid_I1)
#define     R_EEL_SM_SET_INVALID_WAIT_END      (&R_EEL_SM_Set_Invalid_WaitEnd)
#define     R_EEL_SM_SET_INVALID_END           (&R_EEL_SM_Set_Invalid_End)
#define     R_EEL_SM_IDLE                      (0uL)               /* General */


/* -------------------- EEL data type definitions -------------------------- */
/**
   \enum r_eel_pfct
   pointer to a function
*/
    typedef void (* r_eel_pfct)(void);


/**
   \enum r_eel_lifeCycle_t
   Life cycle definition values
*/
    typedef enum R_EEL_LIFECYCLE_T
    {
        R_EEL_LCSTS_NOT_INITIALIZED = 0x55555555uL, /**< Default value of zero initialized data */
        R_EEL_LCSTS_INITIALIZED     = 0x55555556uL, /**< Library is initialized - after R_EEL_Init() */
        R_EEL_LCSTS_ACTIVE          = 0x55555557uL, /**< Library is active      - after R_EEL_Startup() */
        R_EEL_LCSTS_SHUTDOWN        = 0x55555558uL, /**< Library was shut down  - after R_EEL_Shutdown() */
        R_EEL_LCSTS_END             = 0x55555559uL  /**< undef. value to set the end of the enum table */
    } r_eel_lifeCycle_t;

/**
   \enum r_eel_bcResult_t
   Blank check result values
*/
    typedef enum R_EEL_BCRESULT_T
    {
        R_EEL_BC_BLANK,
        R_EEL_BC_WRITTEN
    } r_eel_bcResult_t;

/**
   \enum r_eel_flag_t
   Bit/Flag values
*/
    typedef enum R_EEL_FLAG_T
    {
        R_EEL_FALSE,
        R_EEL_TRUE
    } r_eel_flag_t;

/**
   \enum r_eel_err_flg_t
   EEL error flag
*/
    typedef enum R_EEL_ERR_FLG_T
    {
        R_EEL_FLG_OK,
        R_EEL_FLG_ERROR
    } r_eel_err_flg_t;

/**
   \enum r_eel_chk_ds_t
   DS check return value
*/
    typedef enum R_EEL_CHK_DS_T
    {
        R_EEL_CHKDS_INVALID,
        R_EEL_CHKDS_VALID,
        R_EEL_CHKDS_VALID_EOR_INCOMPLETE
    } r_eel_chk_ds_t;

/**
   \enum r_eel_patcmp_t
   marker pattern comparison result
*/
    typedef enum R_EEL_PATCMP_T
    {
        R_EEL_PATCMP_INVALID,                       /**< pattern does not match */
        R_EEL_PATCMP_VALID,                         /**< pattern matches */
        R_EEL_PATCMP_BLANK                          /**< 0xFFFFFFFF read value */
    } r_eel_patcmp_t;


/**
   \enum r_eel_mrgchk_stat_t
   Margin check status
*/
    typedef enum R_EEL_MRGCHK_STAT_T
    {
        R_EEL_MRGCHK_ACTIVE,
        R_EEL_MRGCHK_SUSPENDED,
        R_EEL_MRGCHK_FINISHED
    } r_eel_mrgchk_stat_t;

/**
   \enum r_eel_flash_error_chk_t
   EEL error flag
*/
    typedef enum R_EEL_FLERR_CHK_T
    {
        R_EEL_FLERR_CHK_OK,
        R_EEL_FLERR_CHK_IGNORE,
        R_EEL_FLERR_CHK_ERR
    } r_eel_flash_error_chk_t;



/**
   \enum r_eel_blk_header_data_t
   Offset of the block header words from block base address
*/
    typedef enum R_EEL_BLK_HEADER_DATA_T
    {
        R_EEL_BLKHDATA_I0             = 0x00uL,      /**< Real offset from vBlk bottom */
        R_EEL_BLKHDATA_P              = 0x04uL,      /**< Real offset from vBlk bottom */
        R_EEL_BLKHDATA_A0             = 0x08uL,      /**< Real offset from vBlk bottom */
        R_EEL_BLKHDATA_A1             = 0x0CuL,      /**< Real offset from vBlk bottom */
        R_EEL_BLKHDATA_EC             = 0x10uL,      /**< Real offset from vBlk bottom */
        R_EEL_BLKHDATA_RWP            = 0x14uL,      /**< Real offset from vBlk bottom */
        R_EEL_BLKHDATA_REFZ           = 0x18uL,      /**< Real offset from vBlk bottom */
        R_EEL_BLKHDATA_HSIZE          = 0x1CuL,      /**< Is the total header size (REFZ + I1)*/
        R_EEL_BLKHDATA_DATAZ          = 0xFEuL,      /**< Is at the virtual block end. So, is treated different */
        R_EEL_BLKHDATA_I1             = 0xFFuL       /**< Is at the virtual block end. So, is treated different */
    } r_eel_blk_header_data_t;

/**
   \enum r_eel_ds_ref_offset_t
   Offset of the data set REF entry half words
*/

    typedef enum R_EEL_DS_REF_OFFSET_T
    {
        R_EEL_REF_OFF_SOR           = 0uL,          /**< SOR offset to REF entry start */
        R_EEL_REF_OFF_EOR0          = 4uL,          /**< EOR offset to REF entry start */
        R_EEL_REF_OFF_EOR1          = 8uL,          /**< EOR offset to REF entry start */
        R_EEL_REF_OFF_DRP           = 12uL,         /**< DRP offset to REF entry start */
        R_EEL_REF_OFF_DRP_ID        = 12uL,         /**< DRP offset to REF entry start (ID) */
        R_EEL_REF_OFF_DRP_WIDX      = 14uL,         /**< DRP offset to REF entry start (widx) */
        R_EEL_REF_OFF_DS            = 16uL          /**< Size of a REF entry in bytes */
    } r_eel_ds_ref_offset_t;

/**
   \enum r_eel_blockoffset_t
   IDL table array index definition
*/
    typedef enum R_EEL_BLOCKOFFSET_T
    {
        R_EEL_BLK_NEXT,                             /**< goto next block */
        R_EEL_BLK_PREV                              /**< goto previous block */
    } r_eel_blockoffset_t;

/**
   \enum r_eel_blockstatus_t
   Ring buffer block status
*/
    typedef enum R_EEL_BLOCKSTATUS_T
    {
        R_EEL_BLKSTAT_ACTIVE,                       /**< active block */
        R_EEL_BLKSTAT_PREPARED,                     /**< prepared block */
        R_EEL_BLKSTAT_INVALID,                      /**< invalid block */
        R_EEL_BLKSTAT_ANY                           /**< "Any block status". This is no possible block status as
                                                         only 4 states are coded by 2 bits. This is just used
                                                         for block search conditions */
    } r_eel_blockstatus_t;

/**
   \enum r_eel_process_id_t
   Process ID.
   Note: The sequence of the following process IDs determines the process priority!
*/
    typedef enum R_EEL_PROCESS_ID_T
    {
        R_EEL_PR_RE         = 0,                    /**< Read process */
        R_EEL_PR_WI         = 1,                    /**< Write immediate process */
        R_EEL_PR_WT         = 2,                    /**< Normal write process */
        R_EEL_PR_WR         = 3,                    /**< Write triggered by Refresh process process */
        R_EEL_PR_PR         = 4,                    /**< Prepare process */
        R_EEL_PR_RF         = 5,                    /**< Refresh process */
        R_EEL_PR_FO         = 6,                    /**< Format process */
        R_EEL_PR_SV         = 7,                    /**< Supervision process */
        R_EEL_PR_END        = 8,                    /**< No valid process. Just process list end marker */
        R_EEL_PR_UNLOCK     = 9                     /**< No valid process. Just marker for no locked process */
    } r_eel_process_id_t;

/**
   \enum r_eel_operation_id_t
   User operation ID.
*/
    typedef enum R_EEL_OPERATION_ID_T
    {
        R_EEL_OP_RE         = 0,                    /**< Read operation */
        R_EEL_OP_WTIMM      = 1,                    /**< Write immediate operation */
        R_EEL_OP_WT         = 2,                    /**< Write operation */
        R_EEL_OP_FO         = 3,                    /**< Format operation */
        R_EEL_OP_END        = 4                     /**< No valid operation. Just list end marker */
    } r_eel_operation_id_t;

/**
   \enum r_eel_write_proc_data_t
   Enumeration identifying the write process type. The same source code can be executed for 3
   different write processes. These processes have own process data which is addressed using this
   enumeration
*/
    typedef enum R_EEL_WRITE_PROC_DATA_T
    {
        R_EEL_WDATA_WI      = 0,                    /**< Immediate write */
        R_EEL_WDATA_WT      = 1,                    /**< Normal write */
        R_EEL_WDATA_WR      = 2,                    /**< Refresh triggered write */
        R_EEL_WDATA_END     = 3                     /**< No valid write type. Just list end marker */
    } r_eel_write_proc_data_t;

/**
    \enum r_eel_searchds_t
    DS search type
*/
    typedef enum R_EEL_SEARCHDS_T
    {
        R_EEL_SEARCHDS_NORMAL,                      /* !< Normal DS search for a given ID */
        R_EEL_SEARCHDS_ANY                          /* !< Search any DS (valid or invalid) */
    } r_eel_searchds_t;

/**
    \enum r_eel_inv_type_t
    type of fast/safe invalidation handling
*/
    typedef enum R_EEL_INVTYPE_T
    {
        R_EEL_INVTYPE_NONE,                         /* !< No fast/safe invalidation */
        R_EEL_INVTYPE_FAST,                         /* !< Fast invalidation (before SOR write) */
        R_EEL_INVTYPE_FAST_POOLFULL,                /* !< Fast invalidation (before SOR write), but write not inv. DS*/
        R_EEL_INVTYPE_SAFE,                         /* !< Safe invalidation (normal write, after EOR1 write) */
        R_EEL_INVTYPE_REFRESH                       /* !< Safe invalidation (refresh...misc different calculations */
    } r_eel_inv_type_t;

/**
   \struct r_eel_process_t
   This enumeration contains process related data which is available for each process
*/
    typedef struct R_EEL_PROCESS_T
    {
        r_eel_flag_t active_enu;                    /**< process active flag */
        r_eel_status_t rStat_enu;                   /**< process (error)status */
        r_eel_pfct nextState_pfct;                  /**< next process state */
        r_fdl_status_t flashStatus_enu;             /**< flash operation status */
    } r_eel_process_t;

/**
   \struct r_eel_operation_t
   This enumeration contains operation related data which is available for each operation
*/
    typedef struct R_EEL_OPERATION_T
    {
        r_eel_request_t * req_pstr;                /**< operation request structure */
    } r_eel_operation_t;

/**
   \struct r_eel_op_read_t
   Read process data structure
*/
    typedef struct R_EEL_OP_READ_T
    {
        uint16_t idx_u16;                          /**< table index of the ID to read */
    } r_eel_op_read_t;

/**
   \struct r_eel_op_write_t
   DS write process data structure
*/
    typedef struct R_EEL_OP_WRITE_T
    {
        uint32_t src_pu32;                        /**< source data pointer */
        uint32_t rp_u32;                          /**< DS RP */
        uint32_t wp_u32;                          /**< DS WP */
        uint16_t idx_u16;                         /**< table index */
        uint16_t id_u16;                          /**< ID */
        uint16_t byteCnt_u16;                     /**< Remaining bytes to write */
        r_eel_flag_t invalidate_enu;              /**< invalidate flag */
        r_eel_flag_t IDXTableUpdate_enu;          /**< IDX table update value */
#ifdef R_EEL_SUPPORT_EXT_FEATURES
            uint32_t writeCntValue_u32;           /**< write counter value */
            uint32_t prevInstInvMrkAdd;           /**< last DS instance invalidation marker address */
            r_eel_inv_type_t fastSafeInvHandling_enu; /**< indicated the fast/safe invalidation handling */
            r_eel_flag_t fastInvOnly_enu;         /**< Flag to write fast invalidation marker only, no DS
                                                       (pool full situation) */
            r_eel_flag_t writeCntSupport_enu;     /**< Flag to write write counter */
#endif
    } r_eel_op_write_t;

/**
    \struct r_eel_op_prepare_t
    Prepare process data structure
*/
    typedef struct R_EEL_OP_PREPARE_T
    {
        uint16_t blk_u16;                           /**< block to prepare */
        uint16_t eraseSuspCnt_u16;                  /**< erase suspend counter */
        uint8_t eraseFail_u08;                      /**< erase fail counter */
    } r_eel_op_prepare_t;

/**
    \struct r_eel_op_refresh_t
    Refresh process data structure
*/
    typedef struct R_EEL_OP_REFRESH_T
    {
        uint32_t lmRefAd_u32;                       /**< limited mode REF pointer (currently checked REF entry) */
        uint16_t tIdx_u16;                          /**< currently refreshed DS RAM table index */
        r_eel_flag_t updBlkOEActive_enu;            /**< indicating, that the block is invalidated and
                                                         so, the pointer to eldest active block can be updated */
        uint32_t cmpSrc_u32;                        /**< Refresh compare source pointer */
        uint32_t cmpDest_u32;                       /**< Refresh compare destination pointer */
        uint16_t cmpCnt_u16;                        /**< Refresh compare number of Bytes to compare */
    } r_eel_op_refresh_t;

/**
   \struct r_eel_op_format_t
    Format process data structure
*/
    typedef struct R_EEL_OP_FORMAT_T
    {
        uint16_t curBlk_u16;                            /**< currently prepared block */
        uint16_t lastBlk_u16;                           /**< last block to prepare */
    } r_eel_op_format_t;

/**
   \struct r_eel_op_supervision_t
    Supervision process data structure
*/
    typedef struct R_EEL_OP_SUPERVISION_T
    {
        r_eel_process_id_t lastPr_enu;                  /**< SV run - last process initiated by SV run */
        uint32_t actBlkEc_u32;                          /**< get blk status - active block erase counter */
        uint16_t curBlk_u16;                            /**< get blk status - currently checked block */
        uint16_t lastChkBlk;                            /**< get blk status - last block to check */
        uint16_t curIdx_u16;                            /**< ensure DS margin - current checked DS idx */
        r_eel_mrgchk_stat_t dsMarginChk_enu;            /**< DS margin check - process status */
        r_eel_flag_t ramTableInit_enu;                  /**< flag indicating initialized RAM table */
        uint16_t ramTableFillCntIDFound_u16;            /**< RAM table fill: # of found IDs */
        uint16_t prepLoopLimit_u16;                     /**< Loop limit to avoid continuous Prepare/Refr */
        uint32_t bitChkAdd_enu32;                       /**< Bit error check address (cyclic bit check) */
        uint16_t ramTableFillblk_u16;                   /**< Ram table fill, number of ID block */
    } r_eel_op_supervision_t;

/**
   \struct r_eel_op_set_active_t
    Set active sub-process data structure
*/
    typedef struct R_EEL_OP_SET_ACTIVE_T
    {
        uint32_t setRwp_u32;                            /**< RWP to write by set active process */
        uint16_t setActiveBlk_u16;                      /**< block to activate */
        r_eel_pfct subProcessReturn_pfct;               /**< next process state in OK case */
        r_eel_pfct subProcessErrReturn_pfct;            /**< next process state in error case */
        r_eel_flag_t a0FlashError;                      /**< flag indicating a recoverable write error (for A0 write) */
    } r_eel_op_set_active_t;

/**
   \struct r_eel_op_set_invalid_t
    Set invalid sub-process data structure
*/
    typedef struct R_EEL_OP_SET_INVALID_T
    {
        r_eel_pfct subProcessReturn_pfct;              /**< next process state in OK case */
        r_eel_pfct subProcessErrReturn_pfct;           /**< next process state in error case */
        uint16_t setInvalidBlk_u16;                    /**< block to invalidate */
    } r_eel_op_set_invalid_t;

/**
   \struct r_eel_mode_suspend_t
   Suspend mode data structure
*/
    typedef struct R_EEL_MODE_SUSPEND_T
    {
        r_eel_flag_t suspendReq_enu;                /**< suspend request flag */
        r_eel_driver_status_t statusSave_str;       /**< driver status backup on suspend */
    } r_eel_mode_suspend_t;

/**
   \struct r_eel_data_t
   Data structure, collecting all EEL internal process, operation and status related data
*/
    typedef struct R_EEL_DATA_T
    {
        const r_eel_descriptor_t * RTCfg_pstr;       /**< pointer to the EEL descriptor */
        r_eel_process_t sm_str[R_EEL_PR_END];        /**< all processes data */
        r_eel_operation_t op_str[R_EEL_OP_END];      /**< all operations data */
        r_eel_op_read_t opRe_str;                    /**< Read process data */
        r_eel_op_write_t opWt_str[R_EEL_WDATA_END];  /**< write processes data */
        r_eel_op_prepare_t opPr_str;                 /**< prepare process data */
        r_eel_op_refresh_t opRf_str;                 /**< refresh process data */
        r_eel_op_format_t opFo_str;                  /**< format process data */
        r_eel_op_supervision_t opSv_str;             /**< supervision process data */
        r_eel_op_set_active_t opSA_str;              /**< set-active sub-process data */
        r_eel_op_set_invalid_t opSI_str;             /**< set-invalid sub-process data */
        uint32_t rp_u32;                             /**< current RP */
        uint32_t wp_u32;                             /**< current WP */
        uint16_t blkActive_u16;                      /**< current active block */
        uint16_t blkPrep_u16;                        /**< prepare block pointer */
        uint16_t blkRef_u16;                         /**< refresh block pointer */
        uint16_t blkOEActive_u16;                    /**< end of active zone pointer */
        uint16_t blkCntPrep_u16;                     /**< no. of prepared blocks */
        uint16_t blkCntInv_u16;                      /**< no. of invalid blocks */
        uint32_t ec_u32;                             /**< current erase counter */
        r_eel_driver_status_t ds_str;                /**< structure for current driver status */
        r_eel_process_id_t curPId_enu;               /**< ID of the currently executed process */
        r_eel_op_write_t * pCurWP_pstr;              /**< pointer to current write operation */
        r_eel_process_t * pCurP_pstr;                /**< pointer to current process */
        r_eel_process_id_t processLock_enu;          /**< process lock number */
        r_eel_mode_suspend_t suspend_str;            /**< suspend status data */
        r_eel_flag_t shutDownReq_enu;                /**< shut down request flag */
        r_fdl_request_t fdlReqErase_str;             /**< FDL request structure Erase */
        r_fdl_request_t fdlReqWrite_str;             /**< FDL request structure Write */
        r_eel_operation_mode_t opMode_enu;           /**< EEL operation more (limited / normal ) */
        uint32_t dataBuffer[4];                      /**< data buffer for Flash write operations */
        uint8_t blkStat_au08[R_EEL_MAX_VBLOCKS / 4]; /**< array storing the block status of all blocks */
        r_eel_lifeCycle_t r_eel_lcSts_enu;           /**< Life cycle variable of the EEL */
        uint16_t vPoolSizeNoVblks_u16;               /**< EEL virtual pool size (# virtual blocks) */
        uint16_t vPoolVblkSize_u16;                  /**< EEL virtual block size (# bytes) */

#ifdef R_EEL_DEBUG_BASICINFO
            uint16_t SMCalls_u16;                    /**< Debug info: number of state machine calls */
            uint16_t BCCnt_u16;                      /**< Debug Info: number of BC calls */
#endif
    } r_eel_data_t;


/*********************************************************************************************************************
 *  Global macros
 *********************************************************************************************************************/
/* Static functions definition */
#ifndef R_EEL_STATIC
    #define R_EEL_STATIC static
#endif

/*********************************************************************************************************************
 * Global function prototypes
 *********************************************************************************************************************/
    r_fdl_status_t          R_EEL_FDLIF_Handler (void);
    r_eel_status_t          R_EEL_FDLIF_EraseSuspendRequest (void);
    uint32_t                R_EEL_PFct_Calc_BlkSpace (void);
    uint32_t                R_EEL_PFct_CastU08Ptr2Add (const uint8_t * ptr);
    uint16_t                R_EEL_PFct_ConvertId2TIdx (uint16_t id);
    r_eel_flag_t            R_EEL_PFct_Chk_ProcessActive (r_eel_process_id_t PID);
    uint16_t                R_EEL_PFct_ConvertTIdx2Len (uint16_t tIdx);
    uint16_t                R_EEL_PFct_ConvertTIdx2Id (uint16_t tIdx);
    void                    R_EEL_PFct_WriteDataToAddU08 (uint8_t data,
                                                          uint32_t add);
    void                    R_EEL_SFct_ActivateProcess (r_eel_process_id_t pID,
                                                        r_eel_pfct sPFCT);
    uint32_t                R_EEL_SFct_Calc_FreeSpace (void);
    void                    R_EEL_SFct_Calc_NextBlk_ActPrep (uint16_t * addBlk);
    r_eel_err_flg_t         R_EEL_SFct_ErrStatCheckError (r_eel_process_id_t pid);
    r_eel_write_proc_data_t R_EEL_SFct_ConvertProcID2WriteProcID (r_eel_process_id_t pid);
    r_eel_status_t          R_EEL_SFct_ProcessErrorUpdate (r_eel_process_id_t pID, r_eel_status_t stat,
                                                           r_eel_pfct errState);
    void                    R_EEL_SFct_ProcessErrorReset (r_eel_process_id_t pID);
    void                    R_EEL_SFct_SetDriverStatus (r_eel_access_status_t as,
                                                        r_eel_operation_status_t os);
    void                    R_EEL_SFct_Write_InitProcess (r_eel_write_proc_data_t wpId,
                                                          r_eel_request_t * request,
                                                          uint16_t id,
                                                          uint16_t byteCnt,
                                                          uint32_t srcAdd,
                                                          r_eel_flag_t invalidate,
                                                          uint16_t idx);
    void                    R_EEL_SM_Format_Start (void);
    void                    R_EEL_SM_Prepare_EraseResume (void);
    void                    R_EEL_SM_Read_Start (void);
    void                    R_EEL_SM_Supv_Start (void);
    void                    R_EEL_SM_Supv_Run (void);
    void                    R_EEL_SM_Write_Start (void);
    void                    R_EEL_SM_WriteInc_Start (void);
    r_eel_process_id_t      R_EEL_SMachine_GetActiveProcess (void);
    void                    R_EEL_SMachine_Main (void);


/*********************************************************************************************************************
 * Global data declarations
 *********************************************************************************************************************/
#define R_EEL_START_SEC_VAR
#include "r_eel_mem_map.h"

#if R_EEL_COMPILER == R_EEL_COMP_GHS
    #define R_EEL_NOINIT
#elif R_EEL_COMPILER == R_EEL_COMP_IAR
    #define R_EEL_NOINIT __no_init
#elif R_EEL_COMPILER == R_EEL_COMP_REC
    #define R_EEL_NOINIT
#endif

    extern R_EEL_NOINIT r_eel_data_t g_eel_str;           /**< structure containing all library int. data */

#define R_EEL_STOP_SEC_VAR
#include "r_eel_mem_map.h"

/*********************************************************************************************************************/

/*********************************************************************************************************************/
#endif       /* #ifndef R_EEL_GLOBAL_H */


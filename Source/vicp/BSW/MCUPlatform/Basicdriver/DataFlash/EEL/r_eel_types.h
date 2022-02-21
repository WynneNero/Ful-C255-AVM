#ifdef ENABLE_QAC_TEST
    #pragma PRQA_MESSAGES_OFF 0292
#endif
/*********************************************************************************************************************
 * Library       : EEPROM Emulation Library for Renesas RH850 devices
*
 * File Name     : $Source: r_eel_types.h $
 * Lib. Version  : $RH850_EEL_LIB_VERSION_T01: V2.01 $
 * Mod. Revision : $Revision: 1.8 $
 * Mod. Date     : $Date: 2017/02/07 09:12:11JST $
 * Device(s)     : RV40 Flash based RH850 microcontroller
 * Description   : User interface type definitions
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

#ifndef R_EEL_TYPES_H
#define R_EEL_TYPES_H

/*********************************************************************************************************************
 *   Global constants (define, const, ...)
 *********************************************************************************************************************/
#define R_EEL_WRN     ((uint8_t)0x10u)                                  /* status numbers above this are warnings */
#define R_EEL_ERR     ((uint8_t)0x20u)                                  /* status numbers above this are errors */


/*********************************************************************************************************************
 *   Global type definitions
 *********************************************************************************************************************/
/* ------------------- Configuration --------------------------------------- */
/**
   \enum r_eel_ext_features_t
   Definitions of extended features
*/
#ifdef R_EEL_SUPPORT_EXT_FEATURES
typedef enum R_EEL_EXT_FEATURES_T
{
    R_EEL_EXTF_NONE,
    R_EEL_EXTF_WC,
    R_EEL_EXTF_FINV,
    R_EEL_EXTF_WC_FINV
} r_eel_ext_features_t;
#endif

/**
   \struct r_eel_ds_cfg_t
   EEL DS configuration structure
*/
typedef struct R_EEL_DS_CFG_T
{
    uint16_t                    ID_u16;                     /**< DS ID */
    uint16_t                    len_u16;                    /**< DS length */
#ifdef R_EEL_SUPPORT_EXT_FEATURES
    r_eel_ext_features_t        ext_features_enu;           /**< DS supported extended features */
#endif
} r_eel_ds_cfg_t;

/**
   \struct r_eel_descriptor_t
   EEL descriptor variable definition
*/
typedef struct R_EEL_DESCRIPTOR_T
{
    uint16_t                    vBlkSize_u16;               /**< virtual block size */
    uint16_t                    vBlkRefreshThreshold_u16;   /**< refresh threshold (no. of prepared blocks) */
    const r_eel_ds_cfg_t *      IDLTab_pstr;                /**< pointer to the ID-L table in ROM */
    uint16_t *                  IDXTab_pau16;               /**< pointer to the ID-X table in RAM */
    uint16_t                    IDLTabIdxCnt_u16;           /**< number of table entries */
    uint16_t                    eraseSuspendThreshold_u16;  /**< threshold for erase suspend */
} r_eel_descriptor_t;



/* ------------------- Initialization -------------------------------------- */
/**
   \enum r_eel_operation_mode_t
   EEL operation mode, set at R_EEL_Init
*/
typedef enum R_EEL_OPERATION_MODE_T
{
    R_EEL_OPERATION_MODE_NORMAL,                            /**< Normal full operation */
    R_EEL_OPERATION_MODE_LIMITED                            /**< Limited operation without refresh */
} r_eel_operation_mode_t;
/* ------------------- Operation ------------------------------------------- */
/**
   \enum r_eel_status_t
   EEL status return values
*/
typedef enum R_EEL_STATUS_T
{
    R_EEL_OK                            = 0x00u,             /**< Normal:  Operation ended successfully
                                                                           Must be 0x00 due to logical operations on it */
    R_EEL_BUSY                          = 0x01u,             /**< Normal:  EEL busy (Operation ongoing) */
    R_EEL_ERR_ERASESUSPEND_OVERFLOW     = (R_EEL_WRN + 0x00u), /**< Warning: Too often erase suspend/resume */
    R_EEL_ERR_FIX_DONE                  = (R_EEL_WRN + 0x01u), /**< Warning: Fix done during startup */
    R_EEL_ERR_CONFIGURATION             = (R_EEL_ERR + 0x00u), /**< Error:   Configuration error */
    R_EEL_ERR_PARAMETER                 = (R_EEL_ERR + 0x01u), /**< Error:   Parameter error */
    R_EEL_ERR_REJECTED                  = (R_EEL_ERR + 0x02u), /**< Error:   Operation rejected, EEL busy */
    R_EEL_ERR_ACCESS_LOCKED             = (R_EEL_ERR + 0x03u), /**< Error:   Read/Write access locked */
    R_EEL_ERR_NO_INSTANCE               = (R_EEL_ERR + 0x04u), /**< Error:   No data instance for the ID */
    R_EEL_ERR_POOL_FULL                 = (R_EEL_ERR + 0x05u), /**< Error:   Pool is full. Write is blocked */
    R_EEL_ERR_FLASH_ERROR               = (R_EEL_ERR + 0x06u), /**< Error:   Flash write error */
    R_EEL_ERR_INTERNAL                  = (R_EEL_ERR + 0x07u), /**< Error:   Internal undefined error */
    R_EEL_ERR_POOL_EXHAUSTED            = (R_EEL_ERR + 0x08u), /**< Error:   Pool exhausted */
    R_EEL_ERR_POOL_INCONSISTENT         = (R_EEL_ERR + 0x09u), /**< Error:   Pool inconsistent */
    R_EEL_ERR_COMMAND                   = (R_EEL_ERR + 0x0au)  /**< Error:   Unknown command */
} r_eel_status_t;

/**
   \enum r_eel_command_t
   EEL operation initiation command
*/
typedef enum R_EEL_COMMAND_T
{
    R_EEL_CMD_READ,                                         /**< Read command */
#ifdef R_EEL_SUPPORT_EXT_FEATURES
    R_EEL_CMD_READ_WC,                                      /**< Read command for the write counter */
#endif
    R_EEL_CMD_WRITE,                                        /**< Write command */
    R_EEL_CMD_WRITE_INC,                                    /**< Write Incremental command */
    R_EEL_CMD_INVALIDATE,                                   /**< Invalidate command */
    R_EEL_CMD_WRITE_IMM,                                    /**< Write immediate command */
    R_EEL_CMD_WRITE_INC_IMM,                                /**< Write Incremental Immediate command */
    R_EEL_CMD_INVALIDATE_IMM,                               /**< Invalidate Immediate commend */
    R_EEL_CMD_FORMAT,                                       /**< Format command */
    R_EEL_CMD_CLEANUP                                       /**< Cleanup command */
} r_eel_command_t;


/**
   \struct r_eel_request_t
   EEL operations request structure, required for R_EEL_Execute
*/
typedef volatile struct R_EEL_REQUEST_T
{
    uint8_t *           address_pu08;                       /**< data address (Read destination, write source)*/
    uint16_t            identifier_u16;                     /**< access ID */
    uint16_t            length_u16;                         /**< number of words to read */
    uint16_t            offset_u16;                         /**< read offset from data set base */
    r_eel_command_t     command_enu;                        /**< command to execute */
    r_eel_status_t      status_enu;                         /**< status return */
} r_eel_request_t;

/* ------------------- Driver status --------------------------------------- */
/**
   \enum r_eel_access_status_t
   EEL operations access status
*/
typedef enum R_EEL_ACCESS_STATUS_T
{
    R_EEL_ACCESS_LOCKED,                                    /**< read- & write access disabled */
    R_EEL_ACCESS_READ_ONLY,                                 /**< read only access */
    R_EEL_ACCESS_READ_WRITE,                                /**< read & write access enabled, limited perf. */
    R_EEL_ACCESS_UNLOCKED,                                  /**< full read and write access enabled */

    R_EEL_ACCESS_UNDEFINED                                  /**< no valid access status. Only used library internal */
} r_eel_access_status_t;

/**
   \enum r_eel_operation_status_t
   EEL (background) operational status
*/
typedef enum R_EEL_OPERATION_STATUS_T
{
    R_EEL_OPERATION_PASSIVE,                                /**< EEL passive, all operations locked */
    R_EEL_OPERATION_IDLE,                                   /**< EEL up and running, full operation possible */
    R_EEL_OPERATION_BUSY,                                   /**< EEL processing a user or background process */
    R_EEL_OPERATION_STARTUP,                                /**< startup processes are running */
    R_EEL_OPERATION_SUSPENDED,                              /**< user suspend, no EEL operation */

    R_EEL_OPERATION_UNDEFINED                               /**< no valid operational status. Only used library
                                                                 internal */
} r_eel_operation_status_t;

/**
   \struct r_eel_driver_status_t
   EEL driver status structure
*/
typedef struct R_EEL_DRIVER_STATUS_T
{
    r_eel_operation_status_t    operationStatus_enu;        /**< EEL (background) operational status */
    r_eel_access_status_t       accessStatus_enu;           /**< EEL operations access status */
    r_eel_status_t              backgroundStatus_enu;       /**< EEL background operations error status */
} r_eel_driver_status_t;


/*********************************************************************************************************************/
#endif       /* #ifndef R_EEL_TYPES_H */


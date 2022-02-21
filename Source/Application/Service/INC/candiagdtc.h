/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   :            										   *
************************************************************************
* Object        : 
* Module        : 
* Instance      : 
* Description   : 
*-----------------------------------------------------------------------
* Version: 
* Date: 
* Author: 
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date                Name            Changes and comments
* 0.1           2015/12/22    ShangQiiuju       init version
*=====================================================================*/
#ifndef _CAN_DIAG_DTC_H_
#define _CAN_DIAG_DTC_H_
#include "config.h"
//#ifdef CAN_DIAG_OPTION
/**** Definition of constants ****/
#define SPI_HANDSHAKE_TIMEOUT 500


/**** Definition of types ****/ 
typedef enum
{
    E_NORESULT,
    E_SENTOK,
    E_SENTFAIL,
    E_WRITEFAIL,
} E_DATASEND_RESULT;


typedef struct DTC_CODE_DATA_TYPE_TAG
{
    U8 dtc_high_byte;
    U8 dtc_middle_byte;
    U8 dtc_low_byte;
} DTC_CODE_DATA_TYPE;

typedef struct DTC_STATUS_BIT_TYPE_TAG
{
    U8 testFailed                          :1;
    U8 testFailedThisOperationCycle        :1;
    U8 pendingDTC                          :1;
    U8 confirmedDTC                        :1;
    U8 testNotCompletedSinceLastClear      :1;
    U8 testFailedSinceLastClear            :1;
    U8 testNotCompletedThisOperationCycle  :1;
    U8 warningIndicatorRequested           :1; 
} DTC_STATUS_BIT_TYPE;

typedef union DTC_STATUS_TYPE_TAG
{
    U8 status_byte;
    DTC_STATUS_BIT_TYPE status_bits;
} DTC_STATUS_TYPE;

typedef struct DTC_RECORD_TYPE_TAG
{
    DTC_STATUS_TYPE dtc_status;
} DTC_RECORD_TYPE;

typedef struct DTC_RECORD_CNT_TYPE_TAG
{
    U8 dtc_create_cnt;
    U8 dtc_recover_cnt;
} DTC_RECORD_CNT_TYPE;

typedef enum DTC_RECORD_ENABLE_TYPE_TAG
{
    DTC_RECORD_ENABLE_NONE = 0x00, /* all dtc record disable */
     DTC_RECORD_ENABLE_NM = 0x01, /* network related diagnostics */
     DTC_RECORD_ENALBE_BDY = 0x02, /* body diagnostics except OP_VOLT in GAC */
     DTC_RECORD_ENABLE_OP_VOLT = 0x04, /* for GAC SPEC */
     DTC_RECORD_ENABLE_BIT_NOT_USED,
} DTC_RECORD_ENABLE_TYPE;

typedef enum DTC_TEST_TYPE_TAG
{
    DTC_TEST_INIT = 0x01,
    DTC_TEST_PASSED = 0x02,
    DTC_TEST_FAILED = 0x04,
    DTC_TEST_CLEAR = 0x08,
    DTC_TEST_NEW_OPR = 0x10, 
    DTC_TEST_NOT_TESTED,
} DTC_TEST_TYPE;

typedef enum DTC_INIT_STEP_TYPE_TAG
{
    DTC_INIT_STEP_START = 0,
    DTC_INIT_STEP_READ_DTC_ST,
    DTC_INIT_STEP_CALCULATE_DTC_ST,
    DTC_INIT_STEP_WRITE_EEPROM_ST,
    DTC_INIT_STEP_FINISHED,
} DTC_INIT_STEP_TYPE;



/**** Definition of macros ****/
/* Define DTC Format. */
#define DTC_FORMAT_ISO15031_6 0x00
#define DTC_FORMAT_ISO14229_1 0x01

/* Define groupOFDTC parameter */
#define DTC_GRP_EMISSIONS   0x000000 /* Emissions-related system */
#define DTC_GRP_POWERTRAIN  0x100000 /* Powertrain group */
#define DTC_GRP_CHASSIS 0x400000 /* Chassis group */
#define DTC_GRP_BODY    0x800000 /* Body system */
#define DTC_GRP_NETWORK 0xC00000 /* Network communication group */
#define DTC_GRP_ALL 0xFFFFFF /* All Groups(all DTC's) */

/* dtc state bit mask */
#define DTC_STATUS_BIT0_MASK_TF 0x01
#define DTC_STATUS_BIT1_MASK_TFTOC 0x02
#define DTC_STATUS_BIT2_MASK_PDTC 0x04
#define DTC_STATUS_BIT3_MASK_CDTC 0x08
#define DTC_STATUS_BIT4_MASK_TNCSLC 0x10
#define DTC_STATUS_BIT5_MASK_TFSLC 0x20
#define DTC_STATUS_BIT6_MASK_TNCTOC 0x40
#define DTC_STATUS_BIT7_MASK_WIR 0x80

#define DESC_DELAY_SIG_1       0x0001
#define DESC_DELAY_SIG_2       0x0002
#define DESC_DELAY_SIG_3       0x0004
#define DESC_DELAY_SIG_4       0x0008
#define DESC_DELAY_SIG_5       0x0010
#define DESC_DELAY_SIG_6       0x0020
#define DESC_DELAY_SIG_7       0x0040
#define DESC_DELAY_SIG_8       0x0080
#define DESC_DELAY_SIG_9       0x0100

/**** Declaration of constants ****/
/**** Declaration of variables ****/
extern BOOL bNAckSta;
extern U16 can_diag_ign_delay_timer;
extern BOOL ResetTimeCntFlag;

/**** Declaration of functions ****/
extern void can_diag_dtc_init(void);
extern void can_diag_dtc_eeprom_init_handle(void);
extern BOOL can_diag_dtc_check_init_finished(void);
extern void can_diag_dtc_monitor_handle(void);
extern void CanDiagDtc_sv14_clear_start(void);
extern void CanDiagDtc_sv14_clear_network_grp_start(void);
extern BOOL can_diag_dtc_status_svc14_clear_all(void);
extern BOOL can_diag_dtc_status_svc14_clear_finished(void);
extern void can_diag_control_dtc_setting_on(void);
extern void can_diag_control_dtc_setting_off(void);
extern void can_diag_dtc_record_enable_adjust(void);
extern U16 can_diag_get_dtc_count(U8 status_mask);
extern U16 can_diag_get_dtc_status_by_status_mask(U8 *p_dtc, U8 status_mask);
extern U16 can_diag_get_supported_dtc(U8 *p_dtc);
extern void CanDiagDtc_desc_delay_set_sig(U16 sig);
extern BOOL CanDiagDtc_desc_delay_get_sig(U16 sig);
extern void can_diag_increase_bus_off_counter(void);
extern void can_diag_reset_bus_off_counter(void);
extern void can_diag_record_snapshot(void);
extern void can_diag_record_snapshoot_to_DTC(U8 dtc_code);

#ifdef CHERY_NM_OPTION
extern void CanManager_setFailStatus(BOOL status);
#define can_nm_set_curr_fail_status(fault)     CanManager_setFailStatus(fault)
#else
#define can_nm_set_curr_fail_status(fault)     
#endif

//#endif
#endif


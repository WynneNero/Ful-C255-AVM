/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                         *
*   AUTHOR     :                                       *
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   : Implementation of the EEPROM Download Handler (EED)
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
*
*=====================================================================*/
#ifndef _EEP_DTCRECORD_H_
#define _EEP_DTCRECORD_H_
#include "CONFIG.H"
#include "TYPES.H"
#include "CanDiagDtcCfg.h"

/*
* Warning: There is no check if the compiler supports
*          the assumed byte and bitorder !!!
* The following assumptions are made:
* - The byte order for words is defined through the corresponding Mapping Table switch
* - Bit 0 is the first bit in the bit union structure
* - A bitfield of 8 bits consumes only one byte of memory (also for the allignment)
*/

//#ifndef CAN_DIAG_OPTION
//#define DTC_CODE_MAX_NUM 10
//#else
//#include "CanDiagDtcCfg.h"
//#endif
//#define EEP_DTC_CODE_MAX_NUM    10

#if (EEP_DTC_CODE_MAX_NUM>30)
    #error "The size of dtc in eeprom is short for app!"
#endif

typedef struct EED_tstDtcRecord
{
    U8 Dtc[BIT30];    
    U8 DTCUnused[32-BIT30];
} EED_tstDtcRecord;

typedef struct EED_tstDtcRecord1
{
    U8 Dtc[DTC_CODE_MAX_NUM1];    
    U8 DTCUnused[32-DTC_CODE_MAX_NUM1];
} EED_tstDtcRecord1;



typedef struct EED_tstDtcFirstFrameFlag
{   
	BOOL FirstFrameFlag[12];
    U8 Unused[32-12]; /*default:0*/
} EED_tstDtcFirstFrameFlag;



typedef struct EED_tstDtcOccurrenceCount
{
    U8 RecoverCnt[BIT30];
	U8 Unused[32-BIT30]; /*default:0*/
} EED_tstDtcOccurrenceCount;

typedef struct EED_tstDtcOccurrenceCount1
{
    U8 RecoverCnt[DTC_CODE_MAX_NUM1];
	U8 Unused[32-DTC_CODE_MAX_NUM1]; /*default:0*/
} EED_tstDtcOccurrenceCount1;



typedef struct EED_tstDtcAgingCount
{
    U8 RecoverCnt[BIT30];
	U8 Unused[32-BIT30]; /*default:0*/
} EED_tstDtcAgingCount;

typedef struct EED_tstDtcAgingCount1
{
    U8 RecoverCnt[DTC_CODE_MAX_NUM1];
	U8 Unused[32-DTC_CODE_MAX_NUM1]; /*default:0*/
} EED_tstDtcAgingCount1;

typedef struct EED_tstDtcAgedCount
{
    U8 RecoverCnt[BIT30];
	U8 Unused[32-BIT30]; /*default:0*/
} EED_tstDtcAgedCount;

typedef struct EED_tstDtcAgedCount1
{
    U8 RecoverCnt[DTC_CODE_MAX_NUM1];
	U8 Unused[32-DTC_CODE_MAX_NUM1]; /*default:0*/
} EED_tstDtcAgedCount1;


typedef struct EED_tstDtcFidData
{
    U8 RecoverCnt[BIT30];
	U8 Unused[32-BIT30]; /*default:0*/
} EED_tstDtcFidData;

typedef struct EED_tstDtcFidData1
{
    U8 RecoverCnt[DTC_CODE_MAX_NUM1];
	U8 Unused[32-DTC_CODE_MAX_NUM1]; /*default:0*/
} EED_tstDtcFidData1;


extern EED_tstDtcRecord Ram_DtcRecord;
extern EED_tstDtcRecord1 Ram_DtcRecord1;
extern EED_tstDtcFirstFrameFlag Ram_DtcFirstFrameFlag;
extern EED_tstDtcOccurrenceCount Ram_DtcOccurrenceCount;
extern EED_tstDtcOccurrenceCount1 Ram_DtcOccurrenceCount1;
extern EED_tstDtcAgingCount Ram_DtcAgingCount;
extern EED_tstDtcAgingCount1 Ram_DtcAgingCount1;
extern EED_tstDtcAgedCount Ram_DtcAgedCount;
extern EED_tstDtcAgedCount1 Ram_DtcAgedCount1;
extern EED_tstDtcFidData Ram_DtcFidData;
extern EED_tstDtcFidData1 Ram_DtcFidData1;

extern const U8 Rom_DtcRecord[32];
extern const U8 Rom_DtcRecord1[32];
extern const U8 Rom_DtcFirstFrameFlag[32];
extern const U8 Rom_DtcAgingCount[32];
extern const U8 Rom_DtcAgingCount1[32];
extern const U8 Rom_DtcOccurrenceCount[32];
extern const U8 Rom_DtcOccurrenceCount1[32];
extern const U8 Rom_DtcAgedCount[32];
extern const U8 Rom_DtcAgedCount1[32];
extern const U8 Rom_DtcAgedCount[32];
extern const U8 Rom_DtcAgedCount1[32];
extern const U8 Rom_DtcFidData[32];
extern const U8 Rom_DtcFidData1[32];

#define EED_CANDTC    			   Ram_DtcRecord.Dtc
#define EED_CANDTC1    			   Ram_DtcRecord1.Dtc
#define EED_CAN_FIRST_FRAME 	   Ram_DtcFirstFrameFlag.FirstFrameFlag
#define EED_CANDTC_OCCURRENCE_CNT  Ram_DtcOccurrenceCount.RecoverCnt
#define EED_CANDTC_OCCURRENCE_CNT1 Ram_DtcOccurrenceCount1.RecoverCnt
#define EED_CANDTC_AGING_CNT       Ram_DtcAgingCount.RecoverCnt
#define EED_CANDTC_AGING_CNT1      Ram_DtcAgingCount1.RecoverCnt
#define EED_CANDTC_AGED_CNT        Ram_DtcAgedCount.RecoverCnt
#define EED_CANDTC_AGED_CNT1       Ram_DtcAgedCount1.RecoverCnt
#define EED_CANDTC_FID_DATA        Ram_DtcFidData.RecoverCnt
#define EED_CANDTC_FID_DATA1       Ram_DtcFidData1.RecoverCnt

#endif /*_EEP_DTCRECORD_H_*/

/****************************** END OF FILE ***************************/

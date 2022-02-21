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
* Version       Date            Name        Changes and comments
* 0.1    Jan 1. 2016       ShangQiuju      Initial Version
*=====================================================================*/
#ifndef _EEP_DIAG_DATA_FLAG_H_
#define _EEP_DIAG_DATA_FLAG_H_
#include "CONFIG.H"
#include "TYPES.H"
#include "canDiagDtcCfg.h"
/*
* Warning: There is no check if the compiler supports
*          the assumed byte and bitorder !!!
* The following assumptions are made:
* - The byte order for words is defined through the corresponding Mapping Table switch
* - Bit 0 is the first bit in the bit union structure
* - A bitfield of 8 bits consumes only one byte of memory (also for the allignment)
*/

typedef struct _EED_tstDIAGDATA0
{
	U8 BackupConfigurationInformation_64[4];
	U8 AVM_FunctionConfiguration_F101[4];
	U8 SystemNameOrEngineType[8];
	U8 ECUManufacturingDate[4];
	U8 security_counter[1];
    U8 Unused[9]; /*default:0*/
	U8 EEPchecksum[2];
} EED_tstDIAGDATA0;

typedef struct _EED_tstDIAGDATA1
{

	U16 Snapshot0100_VehicleSpeed1[15];
	U8 EEPchecksum[2];
} EED_tstDIAGDATA1;

typedef struct _EED_tstDIAGDATA2
{
	U16 Snapshot0100_VehicleSpeed2[15];
	U8 EEPchecksum[2];
} EED_tstDIAGDATA2;

typedef struct _EED_tstDIAGDATA3
{
	U16 Snapshot0100_VehicleSpeed3[13];
	U8 Unused[2]; /*default:0*/
	U8 EEPchecksum[2];
} EED_tstDIAGDATA3;
	

typedef struct _EED_tstDIAGDATA4
{
	U32 Snapshot0101_VehicleOdometer1[7];
	U8 Unused[2]; /*default:0*/
	U8 EEPchecksum[2];

} EED_tstDIAGDATA4;

typedef struct _EED_tstDIAGDATA5
{
	U32 Snapshot0101_VehicleOdometer2[7];
	U8 Unused[2]; /*default:0*/
	U8 EEPchecksum[2];

} EED_tstDIAGDATA5;

typedef struct _EED_tstDIAGDATA6
{
	U32 Snapshot0101_VehicleOdometer3[7];
	U8 Unused[2]; /*default:0*/
	U8 EEPchecksum[2];

} EED_tstDIAGDATA6;

typedef struct _EED_tstDIAGDATA7
{
	U32 Snapshot0101_VehicleOdometer4[7];
	U8 Unused[2]; /*default:0*/
	U8 EEPchecksum[2];

} EED_tstDIAGDATA7;

typedef struct _EED_tstDIAGDATA8
{
	U32 Snapshot0101_VehicleOdometer5[7];
	U8 Unused[2]; /*default:0*/
	U8 EEPchecksum[2];

} EED_tstDIAGDATA8;

typedef struct _EED_tstDIAGDATA11
{
	U32 Snapshot0101_VehicleOdometer6[6];
	U8 Unused[3]; /*default:0*/
	U8 EEPchecksum[2];

} EED_tstDIAGDATA11;

typedef struct _EED_tstDIAGDATA9
{
	U8 Snapshot0102_SupplyVoltage1[30];
	U8 EEPchecksum[2];

} EED_tstDIAGDATA9;

typedef struct _EED_tstDIAGDATA10
{
	U8 Snapshot0102_SupplyVoltage2[11];
	U8 Unused[19]; /*default:0*/
	U8 EEPchecksum[2];

} EED_tstDIAGDATA10;


extern EED_tstDIAGDATA0 Ram_DiagData0;
extern EED_tstDIAGDATA1 Ram_DiagData1; 	
extern EED_tstDIAGDATA2 Ram_DiagData2;	
extern EED_tstDIAGDATA3 Ram_DiagData3;	
extern EED_tstDIAGDATA4 Ram_DiagData4;	
extern EED_tstDIAGDATA5 Ram_DiagData5;	
extern EED_tstDIAGDATA6 Ram_DiagData6;
extern EED_tstDIAGDATA7 Ram_DiagData7;	
extern EED_tstDIAGDATA8 Ram_DiagData8;
extern EED_tstDIAGDATA9 Ram_DiagData9;
extern EED_tstDIAGDATA10 Ram_DiagData10;
extern EED_tstDIAGDATA11 Ram_DiagData11;

extern const U8 Rom_DiagData0[];
extern const U8 Rom_DiagData1[];
extern const U8 Rom_DiagData2[];
extern const U8 Rom_DiagData3[];
extern const U8 Rom_DiagData4[];
extern const U8 Rom_DiagData5[];
extern const U8 Rom_DiagData6[];
extern const U8 Rom_DiagData7[];
extern const U8 Rom_DiagData8[];
extern const U8 Rom_DiagData9[];
extern const U8 Rom_DiagData10[];
extern const U8 Rom_DiagData11[];

#define EED_SystemNameOrEngineType                		Ram_DiagData0.SystemNameOrEngineType
#define EED_ECUManufacturingDate				  		Ram_DiagData0.ECUManufacturingDate
#define EED_Security_Counter			  			    Ram_DiagData0.security_counter

#define EED_Snapshot0100_VehicleSpeed1					Ram_DiagData1.Snapshot0100_VehicleSpeed1
#define EED_Snapshot0100_VehicleSpeed2					Ram_DiagData2.Snapshot0100_VehicleSpeed2
#define EED_Snapshot0100_VehicleSpeed3					Ram_DiagData3.Snapshot0100_VehicleSpeed3

#define EED_Snapshot0101_VehicleOdometer1				Ram_DiagData4.Snapshot0101_VehicleOdometer1
#define EED_Snapshot0101_VehicleOdometer2				Ram_DiagData5.Snapshot0101_VehicleOdometer2
#define EED_Snapshot0101_VehicleOdometer3				Ram_DiagData6.Snapshot0101_VehicleOdometer3
#define EED_Snapshot0101_VehicleOdometer4				Ram_DiagData7.Snapshot0101_VehicleOdometer4
#define EED_Snapshot0101_VehicleOdometer5				Ram_DiagData8.Snapshot0101_VehicleOdometer5
#define EED_Snapshot0101_VehicleOdometer6				Ram_DiagData11.Snapshot0101_VehicleOdometer6

#define EED_Snapshot0102_SupplyVoltage1					Ram_DiagData9.Snapshot0102_SupplyVoltage1
#define EED_Snapshot0102_SupplyVoltage2					Ram_DiagData10.Snapshot0102_SupplyVoltage2

#endif /*_EEP_DIAG_DATA_FLAG_H_*/
/****************************** END OF FILE ***************************/

/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD  NJ                                       *
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
* 0.1    Jan 6. 2016       ShangQiuju      Initial Version
*=====================================================================*/
#ifndef _EEP_ECU_SERIAL_VERSION_H_
#define _EEP_ECU_SERIAL_VERSION_H_
#include "CONFIG.H"
#include "TYPES.H"
/*
* Warning: There is no check if the compiler supports
*          the assumed byte and bitorder !!!
* The following assumptions are made:
* - The byte order for words is defined through the corresponding Mapping Table switch
* - Bit 0 is the first bit in the bit union structure
* - A bitfield of 8 bits consumes only one byte of memory (also for the allignment)
*/

typedef struct _EED_tstECUSerialNumber
{
    U8 num[15];                  /* ECall Started Flag */
    U8 TSPUnused[17];
} EED_tstECUSerialNumber;

extern EED_tstECUSerialNumber Ram_EcuSerialNumber;
extern const U8 Rom_EcuSerialNumber[32];

#define EED_u8EcuSerialNumber       Ram_EcuSerialNumber.num
#endif /*_EEP_ECU_SERIAL_VERSION_H_*/

/****************************** END OF FILE ***************************/


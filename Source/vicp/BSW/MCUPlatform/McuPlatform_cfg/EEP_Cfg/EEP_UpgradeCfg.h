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
* 0.1    May 11. 2014       ShangQiuju      Initial Version
*------------------------------------------------------------------------
* 0.2    Mar 17,2017        Pei Jingli   Add test ID:EED_SYSTEM_VERSION infomations.
*-----------------------------------------------------------------------
* 0.3  Apr 04,2017   PEI Jingli  Fix headfiles included.
*=====================================================================*/
#ifndef _EEP_UPGRADECFG_H_
#define _EEP_UPGRADECFG_H_
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

typedef struct _EED_tstUpgradeDataConfig
{
    U8 UpgradeFlag[16];                  /* Fct System Mode */
	U8 SocWatchdogSwitch[1];
    U8 UpgradeUnused[15];
} EED_tstDataConfig;

extern EED_tstDataConfig Ram_UpgradeConfig;
extern const U8 Rom_UpgradeConfig[32];

typedef struct _EED_SystemVersion
{
    U8 SystemVersion[16];
    U8 UpgradeUnused[16];
} EED_SystemVersion;


typedef struct _EED_IllumState
{
    U8 IllState[16]; 
    U8 IllUnused[16];
} EED_IllumState;

extern EED_IllumState Ram_IllumState;
extern const U8 Rom_IllumState[32];


#define EED_u8UpgradeFlag        Ram_UpgradeConfig.UpgradeFlag
#define EED_u8SocWatchdogSwitch	 Ram_UpgradeConfig.SocWatchdogSwitch
#endif /*_EEP_UPGRADECFG_H_*/

/****************************** END OF FILE ***************************/


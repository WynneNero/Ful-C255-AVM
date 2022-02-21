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
#ifndef _EEP_EOL_CONFIG_FLAG_H_
#define _EEP_EOL_CONFIG_FLAG_H_
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

typedef struct _EED_tstEOLCONFIG
{
    union
    {
        U16 Data;
        struct
        {
            U16 unused1:3;
            U16 ldwon:1;
            U16 bsdon:1;
            U16 prmon:1;
            U16 unsed2:10;            
        }Configb;
    }Config;
	U8 Calibration_flag;
    U8 EnterEOLView_flag;
	U8 SocCalibrationDoneFlag;
    U8 Unused[26]; /*default:0*/
} EED_tstEOLCONFIG;

extern EED_tstEOLCONFIG Ram_EOLConfig;
extern const U8 Rom_EOLConfig[32];

#define EED_u16EOLConfig            	Ram_EOLConfig.Config.Data
#define EED_bldwon  					Ram_EOLConfig.Config.Configb.ldwon
#define EED_bbsdon  					Ram_EOLConfig.Config.Configb.bsdon
#define EED_bprmon						Ram_EOLConfig.Config.Configb.prmon
#define EED_Calibration 				Ram_EOLConfig.Calibration_flag
#define EED_EnterEOLView                Ram_EOLConfig.EnterEOLView_flag
#define EED_u8SocCalibrationDoneFlag	Ram_EOLConfig.SocCalibrationDoneFlag

#endif /*_EEP_EOL_CONFIG_FLAG_H_*/
/****************************** END OF FILE ***************************/

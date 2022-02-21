/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.			*
*				  All Rights Reserved.          	*
*   Department : CT AD     						*
*   AUTHOR	   : 							*
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
* Version       Date    Name    Changes and comments
*-----------------------------------------------------------------------
* 0.1    Sep 13,2016  PEI Jingli Initialize
* ----------------------------------------------------------------------
* 0.2    Jan 05,2017  ZhangJie  Delete test code for EEP_EEL_TEST
*-----------------------------------------------------------------------
* 0.3    Jan 24,2017   ZhangJie   Remove unused include file.
*-----------------------------------------------------------------------
* 0.4    Mar 17,2017  Pei Jingli   Add test ID:EED_SYSTEM_VERSION.
*=====================================================================*/
#ifndef _EEPTABLE_CFG_H_
#define _EEPTABLE_CFG_H_ 
#include "EEP_Def.h"
/**** Definition of constants ****/
/* define dataBlock stored in EEPROM */
enum EED_enDataBlockID 
{
//#ifdef EEP_EEL_TEST
    EED_TestCfg=0,   /* for test */
//#endif
    /* add dataBlock to store */
    EED_nECUSerialNumber,
    EED_nEOLConfig,
    EED_nDTCrecord,
    EED_nDTCrecord1,
	EED_nDTCFirstFrameFlag,
	EED_nDTCOccurrenceCount,
	EED_nDTCOccurrenceCount1,	
	EED_nDTCAgingCount,
	EED_nDTCAgingCount1,
	EED_nDTCAgedCount,
	EED_nDTCAgedCount1,
	EED_nDTCFidData,
	EED_nDTCFidData1,	
    EED_nDiagData0,
    EED_nDiagData1,
    EED_nDiagData2,
    EED_nDiagData3,
    EED_nDiagData4,
    EED_nDiagData5,
    EED_nDiagData6,
    EED_nDiagData7,
    EED_nDiagData8, 
    EED_nDiagData9,
    EED_nDiagData10,
    EED_nDiagData11,
	EED_nLastBlock,
	//EED_nLastBlock,
    EED_nNVRAM_Termination=0xFFu
};

/* define type of dataBlock stored in EEPROM */
enum
{
    E_STARTUP,
    E_RAM1,
    E_RAM2,
    E_RAM_NUMB
};

typedef enum EED_enDataBlockID EED_tenDataBlockID;
typedef enum EED_enDataBlockID* EED_tpenDataBlockID;

/**** Definition of macros ****/


/**** Declaration of constants ****/

/**** Declaration of variables ****/
/* define datablocks handled in E_STARTUP */
extern EED_tenDataBlockID EED_aenStartupBlocks[] ;
/* datablocks handled in E_RAM1 */
extern EED_tenDataBlockID EED_aenNVRAM1[] ;
/* datablocks handled in E_RAM2 */
extern EED_tenDataBlockID EED_aenNVRAM2[] ;
/* all datablocks handled */
extern EED_tpenDataBlockID EED_apenNVRAMResources [] ;
/**** Declaration of functions ****/

#endif /*_EEPTABLE_CFG_H_*/

/****************************** END OF FILE ***************************/


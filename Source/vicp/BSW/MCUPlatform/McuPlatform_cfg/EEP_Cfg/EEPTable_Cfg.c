/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									   *
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   :
*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
*------------------------------------------------------------------------
* 0.1         Sep 15,2016  PEI Jingli Initialize and add EED_TestCfg for a example
* ----------------------------------------------------------------------
* 0.2         Jan 05,2017  ZhangJie  Delete test code for EEP_EEL_TEST 
*-----------------------------------------------------------------------
* 0.3         Jan 24,2017   ZhangJie   Remove unused include file.
*-----------------------------------------------------------------------
* 0.4         Mar 17,2017  Pei Jingli   Add test ID:EED_SYSTEM_VERSION infomations.
*=====================================================================*/
#include <Service_IF.h>
#include "EEPTable_Cfg.h"
#include "EEP_Def.h"
#include"EEPData_IF.h"

/**
 * Configuration table for loading default resource at startup
 * The entries must be defined by EED_enDataBlockID.
*/
EED_tenDataBlockID EED_aenStartupBlocks[] = 
{
  /* add dataBlockID used */
//#ifdef EEP_EEL_TEST
	EED_TestCfg,
//#endif
	EED_nECUSerialNumber,
	EED_nEOLConfig,
/*	
	EED_nDTCrecord,
	EED_nDTCFirstFrameFlag,
	EED_nDTCAgingCount,
	EED_nDiagData0,
	EED_nDiagData1,
	EED_nDiagData2,
	EED_nDiagData3,
	EED_nDiagData4,
*/
   EED_nNVRAM_Termination
};

/**
 * Configuration table for resource NVRAM1
 * The entries must be defined by EED_enDataBlockID.
*/
 EED_tenDataBlockID EED_aenNVRAM1[] = 
{
  /* add dataBlockID used */
   EED_nDTCrecord,
   EED_nDTCrecord1,
   EED_nDTCFirstFrameFlag,
   EED_nDTCOccurrenceCount,
   EED_nDTCOccurrenceCount1,
   EED_nDTCAgingCount,
   EED_nDTCAgingCount1,
   EED_nDTCAgedCount,
   EED_nDTCAgedCount1,
   EED_nNVRAM_Termination
};


/**
 * Configuration table for resource NVRAM2
 * The entries must be defined by EED_enDataBlockID.
*/
 EED_tenDataBlockID EED_aenNVRAM2[] = 
{
    /* add dataBlockID used */

/*	EED_nECUSerialNumber,
    EED_nEOLConfig,*/

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
    EED_nNVRAM_Termination
};
/* related to enum EED_enDataBlockID */
const EED_tstAddressData EED_rastDataBlocksAddress[]=
{ //u16AdrEepRomData: related to dataBlockID when using EEL of Dataflash
	/* EED_TestCfg */			{   (void*)& Rom_UpgradeConfig,      (void*)&Ram_UpgradeConfig,      EED_TestCfg,             sizeof(EED_tstDataConfig),         EET_CommuCallBack  },
	/* EED_nECUSerialNumber */  {	(void*)& Rom_EcuSerialNumber,    (void*)&Ram_EcuSerialNumber,    EED_nECUSerialNumber,    sizeof(EED_tstECUSerialNumber),    EET_CommuCallBack  },
	/* EED_nEOLConfig */		{   (void*)& Rom_EOLConfig,          (void*)&Ram_EOLConfig,          EED_nEOLConfig,          sizeof(EED_tstEOLCONFIG),          EET_CommuCallBack  },
	/* EED_nDTCrecord */		{   (void*)& Rom_DtcRecord,          (void*)&Ram_DtcRecord,          EED_nDTCrecord,          sizeof(EED_tstDtcRecord),          EET_CommuCallBack  },
	/* EED_nDTCrecord1 */		{   (void*)& Rom_DtcRecord1,         (void*)&Ram_DtcRecord1,         EED_nDTCrecord1,         sizeof(EED_tstDtcRecord1),         EET_CommuCallBack  },
	/* EED_tstFirstFrameFlag */	{	(void*)& Rom_DtcFirstFrameFlag,  (void*)&Ram_DtcFirstFrameFlag,  EED_nDTCFirstFrameFlag,  sizeof(EED_tstDtcFirstFrameFlag),  EET_CommuCallBack  },
	/* EED_tstOccurrenceCount */{	(void*)& Rom_DtcOccurrenceCount, (void*)&Ram_DtcOccurrenceCount, EED_nDTCOccurrenceCount, sizeof(EED_tstDtcOccurrenceCount), EET_CommuCallBack  },
	/* EED_tstOccurrenceCount */{	(void*)& Rom_DtcOccurrenceCount1,(void*)&Ram_DtcOccurrenceCount1,EED_nDTCOccurrenceCount1,sizeof(EED_tstDtcOccurrenceCount1),EET_CommuCallBack  },
	/* EED_tstAgingCount */		{	(void*)& Rom_DtcAgingCount,      (void*)&Ram_DtcAgingCount,	     EED_nDTCAgingCount,	  sizeof(EED_tstDtcAgingCount),	     EET_CommuCallBack  },
	/* EED_tstAgingCount1 */	{	(void*)& Rom_DtcAgingCount1,     (void*)&Ram_DtcAgingCount1,	 EED_nDTCAgingCount1,	  sizeof(EED_tstDtcAgingCount1),	 EET_CommuCallBack  },
	/* EED_tstAgedCount */		{	(void*)& Rom_DtcAgedCount,       (void*)&Ram_DtcAgedCount,	     EED_nDTCAgedCount,	      sizeof(EED_tstDtcAgedCount),	     EET_CommuCallBack  },
	/* EED_tstAgedCount1 */		{	(void*)& Rom_DtcAgedCount1,      (void*)&Ram_DtcAgedCount1,	     EED_nDTCAgedCount1,	  sizeof(EED_tstDtcAgedCount1),	     EET_CommuCallBack  },
	/* EED_tstDtcFidData */		{	(void*)& Rom_DtcFidData,         (void*)&Ram_DtcFidData,	     EED_nDTCFidData,	      sizeof(EED_tstDtcFidData),	     EET_CommuCallBack  },
	/* EED_tstDtcFidData1 */	{	(void*)& Rom_DtcFidData1,        (void*)&Ram_DtcFidData1,	     EED_nDTCFidData1,	      sizeof(EED_tstDtcFidData1),	     EET_CommuCallBack  },
	/* EED_nDiagData0 */		{   (void*)& Rom_DiagData0,          (void*)&Ram_DiagData0,          EED_nDiagData0,          sizeof(EED_tstDIAGDATA0),          EET_CommuCallBack  },
	/* EED_nDiagData1 */		{   (void*)& Rom_DiagData1,          (void*)&Ram_DiagData1,          EED_nDiagData1,          sizeof(EED_tstDIAGDATA1),          EET_CommuCallBack  },
	/* EED_nDiagData2 */		{	(void*)& Rom_DiagData2, 	     (void*)&Ram_DiagData2,	         EED_nDiagData2,		  sizeof(EED_tstDIAGDATA2),	         EET_CommuCallBack  },
	/* EED_nDiagData3 */		{	(void*)& Rom_DiagData3, 	     (void*)&Ram_DiagData3,	         EED_nDiagData3,		  sizeof(EED_tstDIAGDATA3),	         EET_CommuCallBack  },
	/* EED_nDiagData4 */		{	(void*)& Rom_DiagData4, 	     (void*)&Ram_DiagData4,	         EED_nDiagData4,		  sizeof(EED_tstDIAGDATA4),	         EET_CommuCallBack  },
	/* EED_nDiagData5 */		{	(void*)& Rom_DiagData5, 	     (void*)&Ram_DiagData5,	         EED_nDiagData5,		  sizeof(EED_tstDIAGDATA5),	         EET_CommuCallBack  },
	/* EED_nDiagData6 */		{	(void*)& Rom_DiagData6, 	     (void*)&Ram_DiagData6,		     EED_nDiagData6,		  sizeof(EED_tstDIAGDATA6),		     EET_CommuCallBack  },
	/* EED_nDiagData7 */		{	(void*)& Rom_DiagData7, 	     (void*)&Ram_DiagData7,	         EED_nDiagData7,		  sizeof(EED_tstDIAGDATA7),	         EET_CommuCallBack  },
	/* EED_nDiagData8 */		{	(void*)& Rom_DiagData8, 	     (void*)&Ram_DiagData8,		     EED_nDiagData8,		  sizeof(EED_tstDIAGDATA8),		     EET_CommuCallBack  },
	/* EED_nDiagData9 */		{	(void*)& Rom_DiagData9, 	     (void*)&Ram_DiagData9,		     EED_nDiagData9,		  sizeof(EED_tstDIAGDATA9),		     EET_CommuCallBack  },
	/* EED_nDiagData10 */		{	(void*)& Rom_DiagData10, 	     (void*)&Ram_DiagData10,		 EED_nDiagData10,		  sizeof(EED_tstDIAGDATA10),		 EET_CommuCallBack  },
	/* EED_nDiagData11 */		{	(void*)& Rom_DiagData11, 	     (void*)&Ram_DiagData11,		 EED_nDiagData11,		  sizeof(EED_tstDIAGDATA11),		 EET_CommuCallBack  },
};



/**
 * Configuration table of all data blocks.
 * The entries must correspond with EED_enDataBlockID.
 * Values:	User defined callbacks
*/
EED_tstDataBlock EED_astDataBlocks[]=	
{
/* EED_TestCfg */				{   EED_nEmpty, ERR_OK, TRUE },
/* EED_nECUSerialNumber */  	{   EED_nEmpty, ERR_OK, TRUE },
/* EED_nEOLConfig */			{   EED_nEmpty, ERR_OK, TRUE },
/* EED_nDTCrecord */			{   EED_nEmpty, ERR_OK, TRUE },
/* EED_nDTCrecord1 */			{   EED_nEmpty, ERR_OK, TRUE },
/* EED_nDTCFirstFrameFlag */	{	EED_nEmpty, ERR_OK, TRUE },
/* EED_nDTCOccurrenceCount */   {	EED_nEmpty, ERR_OK, TRUE },
/* EED_nDTCOccurrenceCount1 */  {	EED_nEmpty, ERR_OK, TRUE },
/* EED_nDTCAgingCount */		{	EED_nEmpty, ERR_OK, TRUE },
/* EED_nDTCAgingCount1 */		{	EED_nEmpty, ERR_OK, TRUE },
/* EED_nDTCAgedCount */		    {	EED_nEmpty, ERR_OK, TRUE },
/* EED_nDTCAgedCount1 */		{	EED_nEmpty, ERR_OK, TRUE },
/* EED_nDTCFidData */		    {	EED_nEmpty, ERR_OK, TRUE },
/* EED_nDTCFidData1 */		    {	EED_nEmpty, ERR_OK, TRUE },
/* EED_nDiagData0 */			{   EED_nEmpty, ERR_OK, TRUE },
/* EED_nDiagData1 */			{   EED_nEmpty, ERR_OK, TRUE },
/* EED_nDiagData2 */			{	EED_nEmpty, ERR_OK, TRUE },
/* EED_nDiagData3 */			{	EED_nEmpty, ERR_OK, TRUE },
/* EED_nDiagData4 */			{	EED_nEmpty, ERR_OK, TRUE },
/* EED_nDiagData5 */			{	EED_nEmpty, ERR_OK, TRUE },
/* EED_nDiagData6 */			{	EED_nEmpty, ERR_OK, TRUE },
/* EED_nDiagData7 */			{	EED_nEmpty, ERR_OK, TRUE },
/* EED_nDiagData8 */			{	EED_nEmpty, ERR_OK, TRUE },
/* EED_nDiagData9 */			{	EED_nEmpty, ERR_OK, TRUE },
/* EED_nDiagData10 */			{	EED_nEmpty, ERR_OK, TRUE },
/* EED_nDiagData11 */			{	EED_nEmpty, ERR_OK, TRUE },
};

/**
 * Pointer array to the configuration tables of NVRAM resources
 * Each entry must correspond to an entry of EED__au8StateRequests
*/
 EED_tpenDataBlockID EED_apenNVRAMResources [] = 
{
    EED_aenStartupBlocks,
    EED_aenNVRAM1,
    EED_aenNVRAM2
};
/**************** END OF FILE *****************************************/


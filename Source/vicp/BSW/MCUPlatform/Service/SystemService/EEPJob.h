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
*-----------------------------------------------------------------------
* Version: 
* Date: 
* Author: 
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
* ----------------------------------------------------------------------
* 0.1  Apr 15,2016                Initial version.  
*------------------------------------------------------------------------
* 0.2 Jan 24,2017  ZhangJie  Fix Coverity warnings.
*-----------------------------------------------------------------------
* 0.3  Apr 01,2017   PEI Jingli  Fix headfiles.
*=====================================================================*/
#ifndef _EEPJOB_H_
#define _EEPJOB_H_ 
#include "Define.h"
#include "EEPTable.h"
/**** Definition of constants ****/


/**** Definition of macros ****/


/**** Declaration of constants ****/

/**** Declaration of variables ****/

/**** Declaration of functions ****/
void EED_InitJobQueueModule( void );
void EED_DeinitJobQueueModule( void );
void EED_ResetJobQueue( void );
void EED_PutJob( EED_ptstJob pNewJob );	
void EED_SetupLastJob( EED_ptstJob pNextJob  );
void EED_InsertHeadJob( EED_ptstJob pNewJob );
EED_tenJobState EED_GetJob( EED_ptstJob pNextJob  );  
BOOL EED_IsJobPending( void );   
#endif /*_EEPJOB_H_*/

/****************************** END OF FILE ***************************/


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
*-----------------------------------------------------------------------
* 0.1   Jun 16,2016                  Init version.
*-----------------------------------------------------------------------
* 0.2   Jan 24,2017   ZhangJie   Fix Coverity warnings.
*=====================================================================*/
/**** Definition of constants ****/
/*   Evt_EventType, Evt_EventProc, first is the high priority*/
/* Switch to select if the X ms auxiliary timer A is to be supported or not. */
/**** Definition of macros ****/
/**** Declaration of constants ****/
BEGIN_JOBS
   JOB(E_BUSMNG, 		BusMng_Job)
   JOB(JOB_EEPRW,		EEO_RWJob)
END_JOBS

#undef  BEGIN_JOBS
#undef  END_JOBS
#undef  JOB

/**** Declaration of variables ****/

/**** Declaration of functions ****/

/****************************** END OF FILE ***************************/


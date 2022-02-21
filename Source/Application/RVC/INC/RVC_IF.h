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
* Version       Date    Name    Changes and comments
* 
*=====================================================================*/
#ifndef _RVC_IF_H_
#define _RVC_IF_H_ 

/**** Definition of constants ****/


/**** Definition of types ****/ 

/**** Definition of macros ****/

/**** Declaration of constants ****/

/**** Declaration of variables ****/

/**** Declaration of functions ****/
E_RVC_STATUS GetRvcVoltageStatus(void);
E_TUNER_STATUS GetTunerVoltageStatus(void);
void RvcManager_5msEntry(void);
void TunerManager_5msEntry(void);
extern void RvcTuner_PowerControl_5msEntry(void);
#endif /*_RVC_IF_H_*/

/****************************** END OF FILE ***************************/


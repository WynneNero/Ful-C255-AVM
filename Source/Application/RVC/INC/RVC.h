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
#ifndef _RVC_H_
#define _RVC_H_ 
#include "CONFIG.H"
#include "ComplexDrvier_Globaldef_IF.H"

/**** Definition of constants ****/

/**** Definition of types ****/ 
typedef enum
{
    VOL_INVALID_VALUE=0x80, //0.1V
    VOL_NORMAL_LOW_VALUE=0x280, //0.5V
    VOL_NORMAL_HIGH_VALUE=0x780, //1.52V
    VOL_OVER_CURRENT_VALUE=0xA00, //2.0V
	VOL_SHORT_CIRCUIT_VALUE=0xD40, //2.65V
	VOL_THERMAL_SHUTDOWN_VALUE=0xF00, //3.0V
	VOL_CURRENT_REVERSE_VALUE=0xFEF, //3.3V
	VOL_MAX_VALUE=0XFFFF,
    VOL_UNKNOWN
}E_SYSTEM_VOLTAGE_STATU_VALUSE;

typedef enum
{
    RVC_IDLE,
    RVC_WAITING_VIDEO_STABLE,
    RVC_NORMAL_RUN,
}RVC_STATUS;

/**** Definition of macros ****/

/**** Declaration of constants ****/


/**** Declaration of variables ****/


/**** Declaration of functions ****/
E_RVC_STATUS GetRvcVoltageStatus(void);
E_TUNER_STATUS GetTunerVoltageStatus(void);
void RvcManager_5msEntry(void);
void TunerManager_5msEntry(void);


#endif /*_RVC_H_*/

/****************************** END OF FILE ***************************/


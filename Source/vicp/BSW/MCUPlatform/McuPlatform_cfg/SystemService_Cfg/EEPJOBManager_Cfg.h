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
*----------------------------------------------------------------------
* 0.1    Dec 20,2015      init version
*----------------------------------------------------------------------
* 0.2    Dec 20,2016      ShangQiuju  remove unused include files
*-----------------------------------------------------------------------
* 0.3    Jan 24,2017       ZhangJie      Fix Coverity warnings.
*-----------------------------------------------------------------------
* 0.4    Mar 17,2017       Pei Jingli    Fix interface names for eep-driver changing.
*=====================================================================*/
#ifndef _EEPJOBMANAFGER_CFG_H_
#define _EEPJOBMANAFGER_CFG_H_ 
/**** Definition of constants ****/
/*Frame define*/
#include "EEPJobManager.H"

/**** Definition of macros ****/

/**** Declaration of constants ****/
/**** Declaration of variables ****/
/**** Declaration of functions ****/

/********************************************************************************************
* HEADER-FILES (Only those that are needed in this file)
********************************************************************************************/

/* IMPORT CONFIGURATION */
/********************************************************************************************
* SYNONYM ADAPTATION
*
* In this section
* - adapt external symbols to internally used names if necessary. This
*   synonym adaptation is unknown for other modules
********************************************************************************************/         
#define EEO_SHARED_BUS_SUPPORTED      STD_OFF
/* Enable/diable the development error detect function */
#define EEO_DEV_ERROR_DETECT	  		STD_OFF

/* Enable/disable the function Eep_SetMode is available.*/
#define EEO_SET_MODE_SUPPORTED	  		STD_OFF

/* Enable/disable the call back funtion of eeprom event notification */
#define EEO_NOTIFICATION_SUPPORTED 		STD_ON

/* Enable/disable the function Eep_SetProtectRange and Eep_ClearProtectRange */
#define EEO_PROTECT_RANGE_RESET_API  	STD_OFF


/* MODULE CONFIGURATION */
/********************************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants and macros to configure your module. These constants are
*   unknown for other modules
********************************************************************************************/

/* definition of the default data by eeprom configure */								 
#define EEO_RETRY_MAX	(3U)	

/*set the job repeat times when error accrued in implement */		
extern EEO_ConfigType EEPDriver_ConfigData;
#define EEO_GETEEPCONFIG() &EEPDriver_ConfigData

extern BOOL EEPdriver_Read(U16 DSid,U8 length, U8* read_buffer);
extern BOOL EEPdriver_Write(U16 DSid,U8 length, U8* write_buffer);
extern BOOL EEPdriver_Init(void);
extern BOOL EEPdriver_DeInit(void);
extern BOOL EEPDriver_InitBus(void);
extern BOOL EEPDriver_DeInitBus(void);

#define EEO_DRIVER_INIT()    EEPdriver_Init()
#define EEO_READ_DATA(x,y,z) EEPdriver_Read(x,y,z)
#define EEO_WRITE_DATA(x,y,z) EEPdriver_Write(x,y,z)
#define EEO_DRIVER_DEINIT()  EEPdriver_DeInit()

#if EEO_SHARED_BUS_SUPPORTED==STD_ON
#define EEO_INIT_BUS()		EEPDriver_InitBus()      	
#define EEO_DEINIT_BUS()	EEPDriver_DeInitBus()	
#define EEO_BUSDEVID 		E_DEV_EEPROM	
#else
#define EEO_INIT_BUS()		TRUE      
#define EEO_DEINIT_BUS()	TRUE	
#define EEO_BUSDEVID            
#endif

#if EEO_DEV_ERROR_DETECT ==STD_ON
#define EEO_ReportError(x,y)  
#else
#define EEO_ReportError(x,y) 
#endif


#if EEO_NOTIFICATION_SUPPORTED == STD_ON
extern void EED_IoError(ERR_TYPE enRetError );
extern void EED_IoOK( void );
extern void EED_IoInit( ERR_TYPE enRetError );
extern void EED_IoDeInit(ERR_TYPE enRetError);

#define EEO_ERROR_NOTIFICATION(x) 	EED_IoError(x)
#define EEO_END_NOTIFICATION()		EED_IoOK()
#define EEO_INIT_NOTIFICATION(x)	EED_IoInit(x)
#define EEO_DEINIT_NOTIFICATION(x)	EED_IoDeInit(x)
#else	
#define EEO_ERROR_NOTIFICATION(x) 
#define EEO_END_NOTIFICATION()
#define EEO_INIT_NOTIFICATION(x)
#define EEO_DEINIT_NOTIFICATION(x)
#endif

#endif /*_EEPJOBMANAFGER_CFG_H_*/

/****************************** END OF FILE ***************************/


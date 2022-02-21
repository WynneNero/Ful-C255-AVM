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
* ---------------------------------------------------------------------
* 0.1    Feb 10,2013    NI Rujin    Initial version
* ---------------------------------------------------------------------
* 0.2	Dec 19,2016   PEI Jingli  Add event-processing function of Timer Service
* ----------------------------------------------------------------------
* 0.3    Jan 05,2017    ZhangJie  Delete test code for IIC_TRACE test 
* ----------------------------------------------------------------------
* 0.4   Jan 06,2017    ZhangJie  Recover ICS callback function
*------------------------------------------------------------------------
* 0.5   Jan 12,2017  ZhangJie  Remove unused struct to avoid Coverity warning.
*-----------------------------------------------------------------------
* 0.6   Jan 24,2017   ZhangJie   Remove unused include file.
*------------------------------------------------------------------------
* 0.7  Apr 04,2017   PEI Jingli  Fix headfiles included.
*------------------------------------------------------------------------
* 0.7  Apr 07,2017   PEI Jingli  Fix warnings.
*=====================================================================*/
#include "config.h"
#include "Core_Cfg.h"
/******************************************************************************
* MODULE GLOBAL CONFIGURATION CONSTANTS
*
* In this section define
* - constants and macros to configure your module. These constants are unknown for other 
*   modules
*******************************************************************************/
extern void Soc_DriverError_Report(void);
extern void Soc_DataSentOk(void);
extern void Soc_DataSentFail(void);

void Evt_Soc_Resync_Error_Proc(void){
    Soc_DriverError_Report();
}
void Evt_SOC_SentOk_Proc(void){
    Soc_DataSentOk();
}
void Evt_SOC_SentFail_Proc(void){
    Soc_DataSentFail();
}

extern void EET_RecEvt_STARTUPUpload(void);
void Evt_EEP_STARTUPUPLOAD_Proc(void)
{
    EET_RecEvt_STARTUPUpload();
}

extern void EET_RecEvt_STARTUPDownload(void);
void Evt_EEP_STARTUPDOWNLOAD_Proc(void)
{
    EET_RecEvt_STARTUPDownload();
}


extern void EET_RecEvt_RAM1Upload(void);
void Evt_EEP_RAM1UPLOAD_Proc(void)
{
    EET_RecEvt_RAM1Upload();
}

extern void EET_RecEvt_RAM1Download(void);
void Evt_EEP_RAM1DOWNLOAD_Proc(void)
{
    EET_RecEvt_RAM1Download();
}

extern void EET_RecEvt_RAM2Upload(void);
void Evt_EEP_RAM2UPLOAD_Proc(void)
{
    EET_RecEvt_RAM2Upload();
}

extern void EET_RecEvt_RAM2Download(void);
void Evt_EEP_RAM2DOWNLOAD_Proc(void)
{
    EET_RecEvt_RAM2Download();
}

/* handler after IIC receive data finish*/
void Evt_ICS_RX_Proc(void)
{
    
}

/* handler after IIC send data finish*/
void Evt_ICS_TX_Proc(void)
{
    
}

extern void Timer_EventProc( void);
void Evt_Timer_Proc(void)
{
    Timer_EventProc();
}

/**************** END OF FILE *****************************************/

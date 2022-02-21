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
* 0.1    Dec 20,2015   init version
*----------------------------------------------------------------------
* 0.2    Dec 20,2016   ShangQiuju  add config file according using hw
*----------------------------------------------------------------------
* 0.3    Dec 22,2016   Pei Jingli      add 64pin hw switch 
* ----------------------------------------------------------------------
* 0.4    Dec 26,2016   PEI Jingli  Chang function name of Evt_Timer_Proc 
*-----------------------------------------------------------------------
* 0.5   Jan 24,2017   ZhangJie   Fix Coverity warnings.
*-----------------------------------------------------------------------
* 0.6   Mar 17,2017   Pei Jingli   Delete test code.
*=====================================================================*/
/**** Definition of constants ****/
/**** Definition of macros ****/
/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/
/*   Evt_EventType, Evt_EventProc, first is the high priority*/
BEGIN_EVTDESCS
/*AutoGen: Event Gen*/
/*service timer*/
EVTDESC(EVT_TIMER,       Evt_Timer_Proc)
EVTDESC(EVT_SOC_DRIVER_ERROR,   Evt_Soc_Resync_Error_Proc)
EVTDESC(EVT_EEP_STARTUPUPLOADCOMPLETE,    Evt_EEP_STARTUPUPLOAD_Proc)
EVTDESC(EVT_EEP_STARTUPDOWNLOADCOMPLETE,      Evt_EEP_STARTUPDOWNLOAD_Proc)
EVTDESC(EVT_EEP_RAM1UPLOADCOMPLETE,   Evt_EEP_RAM1UPLOAD_Proc)
EVTDESC(EVT_EEP_RAM1DOWNLOADCOMPLETE,     Evt_EEP_RAM1DOWNLOAD_Proc)
EVTDESC(EVT_EEP_RAM2UPLOADCOMPLETE,   Evt_EEP_RAM2UPLOAD_Proc)
EVTDESC(EVT_EEP_RAM2DOWNLOADCOMPLETE,     Evt_EEP_RAM2DOWNLOAD_Proc)
EVTDESC(EVT_SOC_SENDOK,	        Evt_SOC_SentOk_Proc)
EVTDESC(EVT_SOC_SENDFAIL,	        Evt_SOC_SentFail_Proc)
EVTDESC(EVT_ICS_RX_FINISH,Evt_ICS_RX_Proc)
EVTDESC(EVT_ICS_TX_FINISH,Evt_ICS_TX_Proc)
END_EVTDESCS

#undef  BEGIN_EVTDESCS
#undef  END_EVTDESCS
#undef  EVTDESC

/****************************** END OF FILE ***************************/


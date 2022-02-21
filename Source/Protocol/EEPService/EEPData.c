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
* Version Date               Name        Changes and comments
*  0.1      Sep 19,2016                     init version.
*----------------------------------------------------------------------
*  0.2      Jan 05,2017    ZhangJie     Delete test code for EEP_EEL_TEST
*----------------------------------------------------------------------
*  0.3      Jan 24,2017    ZhangJie     Fix Coverity warning.
*=====================================================================*/
#include "Config.h"
#include "TYPES.h"
#include "EEPData.h"
#include "Signal_if.h"

BOOL UploadEEP(U8 RAMRes );
BOOL DownloadEEP ( U8 RAMRes );
 
#define EEP_MAX_ERR_CNT 3u
U8 uEEPcomErrCnt;
 /*load/download RAM1 and RAM2 Section*/
BOOL isFinished;
BOOL isLoadCompleted;
BOOL isDownLoadCompleted;
EEDActionStep EEDStep;

BOOL isEEDLoadReq;
BOOL isEEDDownloadReq;

 /*load/download Starup section*/
BOOL     isStartupLoad;
BOOL     isStartupDownLoad;
U8 eep_write_freq_ctl;


void EED_ResetInit(void)
{
	isFinished= FALSE;
	isLoadCompleted=FALSE; 
	isDownLoadCompleted=FALSE;
	EEDStep= EED_IDLE;

	isEEDLoadReq=FALSE;
	isEEDDownloadReq=FALSE;

	isStartupLoad=FALSE;
	isStartupDownLoad=FALSE; 
}

/***********************************************************************
*  Name        : EED_isStartupLoad
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EED_isStartupLoad(void)
{
 return isStartupLoad;
}

/***********************************************************************
*  Name        : EED_isStartupDownload
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EED_isStartupDownload(void)
{
 return isStartupDownLoad;
}
/***********************************************************************
*  Name        : EED_LoadStartup
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EED_LoadStartup(void)
{
   return UploadEEP(EED_STARTUP);
}

/***********************************************************************
*  Name        : EED_DownloadStartup
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EED_DownloadStartup(void)
{
      return DownloadEEP(EED_STARTUP);
}

/***********************************************************************
*  Name        : EET_RecEvt_STARTUPUpload
*  Description : system alarm tick        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EET_RecEvt_STARTUPUpload(void)
{
   isStartupLoad=TRUE;
}

/***********************************************************************
*  Name        : EET_RecEvt_STARTUPDownload
*  Description : system alarm tick        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EET_RecEvt_STARTUPDownload(void)
{
       isStartupDownLoad=TRUE;
}

/***********************************************************************
*  Name        : EED_Load_Request
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EED_Load_Request(void)
{
   isEEDLoadReq=TRUE;
}

/***********************************************************************
*  Name        : EED_IsLoad
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EED_IsLoad(void)
{
  return isLoadCompleted;
}
/***********************************************************************
*  Name        : EED_Load_Request
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EED_Download_Request(void)
{
   isEEDDownloadReq=TRUE;
}

/***********************************************************************
*  Name        : EED_IsDownload
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EED_IsDownload(void)
{
  return isDownLoadCompleted;
}


/***********************************************************************
*  Name        : EED_Upload_entry
*  Description : system alarm tick        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EED_Upload_entry(void)
{
 switch(EEDStep)
 {
   case EED_IDLE:
   	if(isEEDLoadReq==TRUE)
	{
	 EEDStep=EED_LOADRAM1REQ;
	 isLoadCompleted=FALSE;
       isFinished =FALSE;
       isEEDLoadReq=FALSE;	   
	}
	else{/*do nothing*/}
   	break;
   case EED_LOADRAM1REQ:
	    if(UploadEEP(E_RAM1)==FALSE)
          {
	     EEDStep=EED_LOADRAM2REQ;	
          }
	   else
	   {
	    EEDStep=EED_LOADRAM1ING;
	   }
   	break;

   case EED_LOADRAM1ING:
	    if(isFinished==TRUE)
          {
	     EEDStep=EED_LOADRAM2REQ;	
            isFinished =FALSE;			 
          }
	   else
	   {
            /*just waiting*/
            /*TODO: maybe need tickcount*/
	   }
   	break;

   case EED_LOADRAM2REQ:
	    if(UploadEEP(E_RAM2)==FALSE)
          {
	     EEDStep=EED_IDLE;	
	    isLoadCompleted=TRUE;		 
          }
	   else
	   {
	    EEDStep=EED_LOADRAM2ING;
	   }
   	break;
   case EED_LOADRAM2ING:
	    if(isFinished==TRUE)
          {
	     EEDStep=EED_IDLE;	
	    isLoadCompleted=TRUE;	
	    isFinished=FALSE;		
          }
	   else
	   {
            /*just waiting*/
            /*TODO: maybe need tickcount*/
	   }
   	break;	
     default:
	 	break;	
     }
}

/***********************************************************************
*  Name        : EED_Download_entry
*  Description : system alarm tick        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EED_Download_entry(void)
{
   
switch(EEDStep)
 {
   case EED_IDLE:
   	if(isEEDDownloadReq==TRUE)
	{
	 EEDStep=EED_DLLOADRAM1REQ;
	 isDownLoadCompleted=FALSE;
        isFinished =FALSE;	
	 isEEDDownloadReq=FALSE;	   
	}
	else{/*do nothing*/}
   	break;
   case EED_DLLOADRAM1REQ:
	    if(DownloadEEP(E_RAM1)==FALSE)
          {
	     EEDStep=EED_DLLOADRAM2REQ;	
          }
	   else
	   {
	    EEDStep=EED_DLLOADRAM1ING;
	   }
   	break;

   case EED_DLLOADRAM1ING:
	    if(isFinished==TRUE)
          {
	     EEDStep=EED_DLLOADRAM2REQ;	
            isFinished =FALSE;			 
          }
	   else
	   {
            /*just waiting*/
            /*TODO: maybe need tickcount*/
	   }
   	break;

   case EED_DLLOADRAM2REQ:
	    if(DownloadEEP(E_RAM2)==FALSE)
          {
	     EEDStep=EED_IDLE;	
	    isDownLoadCompleted=TRUE;		 
          }
	   else
	   {
	    EEDStep=EED_DLLOADRAM2ING;
	   }
   	break;
   case EED_DLLOADRAM2ING:
	    if(isFinished==TRUE)
          {
	     EEDStep=EED_IDLE;	
	    isDownLoadCompleted=TRUE;	
	    isFinished=FALSE;		
          }
	   else
	   {
            /*just waiting*/
            /*TODO: maybe need tickcount*/
	   }
   	break;	
     default:
	 	break;	
     }
}

/***********************************************************************
*  Name        : EET_RecEvt_RAM1Upload
*  Description : system alarm tick        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EET_RecEvt_RAM1Upload(void)
{
   isFinished=TRUE;
}

/***********************************************************************
*  Name        : EET_RecEvt_RAM2Upload
*  Description : system alarm tick        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EET_RecEvt_RAM2Upload(void)
{
    isFinished=TRUE;
}


/***********************************************************************
*  Name        : EET_RecEvt_RAM1Download
*  Description : system alarm tick        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EET_RecEvt_RAM1Download(void)
{
     isFinished=TRUE;
}

/***********************************************************************
*  Name        : EET_RecEvt_RAM2Download
*  Description : system alarm tick        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
/*TODO High Risk: for no event feedback and then can not enter sleep mode*/
void EET_RecEvt_RAM2Download(void)
{
	   isFinished=TRUE;
}   

/***********************************************************************
*  Name        : EET_RecEvt_RAM2Download
*  Description : system alarm tick        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EET_CommuCallBack  (U16 BlockId,ERR_TYPE type)
{
        if(BlockId>=(U16)EED_nLastBlock)
        {
            return;
        }
	if(ERR_OK == type)
	{
	    if(uEEPcomErrCnt)
	    {
                  U8 comfail ;
        	    uEEPcomErrCnt = 0u;
    	           comfail = (U8)FALSE;
    	           CS_SIG_SyncSend((U16)SIG_B_EEPROMCOMMUFAIL, &comfail);
	    }
	}
	else
	{
	    if(uEEPcomErrCnt < EEP_MAX_ERR_CNT)
	    {
	        uEEPcomErrCnt++;
	        if(uEEPcomErrCnt == EEP_MAX_ERR_CNT)
	        {   
	               U8 comfail ;
        	        comfail = TRUE;
        	        CS_SIG_SyncSend((U16)SIG_B_EEPROMCOMMUFAIL, &comfail);
	        }
	    }
	}
}  

/***********************************************************************
*  Name        : UploadEEP
*  Description : system alarm tick        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
 BOOL UploadEEP(U8 RAMRes )
 {
 	BOOL isPerforming=FALSE;
	/* Check the res, i.e. which Resource shall be uploaded via external initialization. */	
	switch( RAMRes )
	{
        case E_STARTUP:			
                
		 isPerforming=EED_MarkNVRamResource( RAMRes, EVT_EEP_STARTUPUPLOADCOMPLETE, EED__nUpload );
		break;
        
             case E_RAM1:			
		 isPerforming=EED_MarkNVRamResource( RAMRes, EVT_EEP_RAM1UPLOADCOMPLETE, EED__nUpload );
		break;
		
		case E_RAM2:
		 isPerforming=EED_MarkNVRamResource( RAMRes, EVT_EEP_RAM2UPLOADCOMPLETE, EED__nUpload );
		break;
	}

	/*if(isPerforming==FALSE)
	{
		isFinished=TRUE;
	}*/	
	return isPerforming;
}


/***********************************************************************
*  Name        : DownloadEEP
*  Description : system alarm tick        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
 BOOL  DownloadEEP ( U8 RAMRes )
{
	BOOL isPerforming=FALSE;
	/* Check the res, i.e. which Resource shall be uploaded via external initialization. */
	switch( RAMRes )
	{
		case E_STARTUP:
		 isPerforming=EED_MarkNVRamResource( RAMRes, EVT_EEP_STARTUPDOWNLOADCOMPLETE, EED__nDownload );
		break;
        
		case E_RAM1:
		 isPerforming=EED_MarkNVRamResource( RAMRes, EVT_EEP_RAM1DOWNLOADCOMPLETE, EED__nDownload );
		break;
		
		case E_RAM2:
		 isPerforming=EED_MarkNVRamResource( RAMRes, EVT_EEP_RAM2DOWNLOADCOMPLETE, EED__nDownload );
		break;
	}

	/*if(isPerforming==FALSE)
	{
		isFinished=TRUE;
	}*/

    return isPerforming;
}

/*
void star_eep_job_handle(void)
{
	if(10<eep_write_freq_ctl++)//1S
	{
		eep_write_freq_ctl = 0;
		
		if(TRUE==SysJob_Star_EepJob_flag)
		{
			SysJob_Star_EepJob_flag = FALSE;
			SysJob_StartJob(JOB_EEPRW);
		}
		
	}

//	if((TRUE == SysJob_Star_EepJob_flag)&&(TRUE == eep_cycle_write_en))
//	{
//		//eep_cycle_write_en = FALSE;
//		eep_write_freq_ctl = 10;
//	}

//	if(10<eep_write_freq_ctl++)//1S
//	{
//		eep_write_freq_ctl = 0;
//		eep_cycle_write_en = TRUE;
//		if(TRUE==SysJob_Star_EepJob_flag)
//		{
//			SysJob_Star_EepJob_flag = FALSE;
//			SysJob_StartJob(JOB_EEPRW);
//			eep_cycle_write_en = FALSE;
//		}
//	}
}
*/


/**************** END OF FILE *****************************************/


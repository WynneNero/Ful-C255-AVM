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
*------------------------------------------------------------------------
* 0.1    Aug 31,2016            Init version.
*------------------------------------------------------------------------
* 0.2    Jan 13,2017  ZhangJie  Fix Coverity warnings.
*------------------------------------------------------------------------
* 0.3    Jan 24,2017  ZhangJie  Add OSAPI.h and remove unused code for warnings.
*-----------------------------------------------------------------------
* 0.4    Mar 17,2017 Pei Jingli   Delete EEL_USED micro,used #if 1 for Dataflash EEP.
*=====================================================================*/
#include <Service_HOOKS.h>
#include <Tools.h>
#include <EEPJobManager_Cfg.h>
#include <Jobmng.h>
#include "BusMng.h"
#include "EEPJobManager.h"
#include "OSAPI.h"

BOOL EEO_bBusRequested;
STATIC EEO_HandleType EEO_stEepHandle;/*
*
* Description: eeprom access mode. 
*
* Access:      R/W
*
* Range:     EEO_stEepGlobal.ModeType enum. 
*/
STATIC EEO_GlobalType  EEO_stEepGlobal=
{
	EEO_UNINIT,
	NULL,
	&EEO_stEepHandle,
}; 

STATIC BOOL CheckInProtectArrange(U16 Addr, U16 Len);
STATIC void RWHandler(void);
STATIC void BusHandler(void);

/***********************************************************************
*  Name        : EEO_Init
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EEO_Init(void)
{

    BOOL ReturnValue = FALSE;/* temporery variable for return value.*/   

	if(EEO_stEepGlobal.State != EEO_UNINIT)
	{
		/*EEO_ReportError(EEO_INIT_SERVICE_ID,EEO_E_ALREADY_INITIALIZED)*/
	}
	else
	{
		EEO_stEepGlobal.State = EEO_IDLE;
		EEO_stEepGlobal.Handle->JobState = EEO_JOB_OK;
		
	}
	EEO_bBusRequested=FALSE;
	EEO_stEepGlobal.Config= EEO_GETEEPCONFIG();

	if(EEO_stEepGlobal.Config==NULL)
	{
		/*EEO_ReportError(EEO_INIT_SERVICE_ID,EEO_E_ALREADY_INITIALIZED)*/
	}
	
	ReturnValue=EEO_DRIVER_INIT();
        (void)ReturnValue;
}


/***********************************************************************
*  Name        : EEO_DeInit
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EEO_DeInit(void)
{
  BOOL ReturnValue = FALSE;/* temporery variable for return value.*/ 
  ReturnValue=EEO_DRIVER_DEINIT();
  (void)ReturnValue;
}


/***********************************************************************
*  Name        : EEO_GetBusStatus
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EEO_GetBusStatus(void)
{
 return EEO_bBusRequested;
}

/***********************************************************************
*  Name        : EEO_RequestIO
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EEO_RequestIO( void)
{
    BOOL TemState=FALSE;/*temporery variable for active a task result value.*/
	
    OSAPI_LockSchedule();
	if(EEO_stEepGlobal.State == EEO_IDLE)
	{
		EEO_stEepGlobal.Handle->AccMode = EEO_REQUESTBUS;			  
		EEO_stEepGlobal.State =EEO_BUSY;
	      TemState=TRUE; 
	}
       OSAPI_UnlockSchedule();	
       if(TemState ==TRUE)
       {
         SysJob_StartJob((U8)JOB_EEPRW); 
       }
       else{}
	return TemState;
}

/***********************************************************************
*  Name        : EEO_ReleaseIO
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EEO_ReleaseIO(void)
{
   BOOL TemState=FALSE;/*temporery variable for active a task result value.*/
	
    OSAPI_LockSchedule();
	if(EEO_stEepGlobal.State == EEO_IDLE)
	{
		EEO_stEepGlobal.Handle->AccMode = EEO_RELEASEBUS;
		EEO_stEepGlobal.State = EEO_BUSY;
	      TemState=TRUE; 
	}
       OSAPI_UnlockSchedule();	
	   
       if(TemState ==TRUE) 
       {
         SysJob_StartJob((U8)JOB_EEPRW); 
       }
       else{}

   return TemState;	
}

#if (EEO_SHARED_BUS_SUPPORTED==STD_ON)
/***********************************************************************
*  Name        : EEO_BusRequested
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EEO_BusRequested(void)
{
   BOOL TemState=FALSE;/*temporery variable for active a task result value.*/
    OSAPI_LockSchedule();   
   if(EEO_stEepGlobal.Handle->AccMode==EEO_REQUESTBUS)
   {
   	EEO_stEepGlobal.Handle->AccMode=EEO_REQUESTBUS_BACK;
	TemState = TRUE;  
   }
    OSAPI_UnlockSchedule();	   
   if(TemState ==TRUE)
   {
     SysJob_StartJob(JOB_EEPRW);   
   }
   else{}
}

/***********************************************************************
*  Name        : EEO_BusReleased
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EEO_BusReleased(void)
{
   BOOL TemState=FALSE;/*temporery variable for active a task result value.*/
       OSAPI_LockSchedule(); 
    if(EEO_stEepGlobal.Handle->AccMode==EEO_RELEASEBUS)
	{
	   EEO_stEepGlobal.Handle->AccMode=EEO_RELEASEBUS_BACK;
	   TemState = TRUE;
	}
    OSAPI_UnlockSchedule();	   	
    if(TemState ==TRUE)
    { 
      SysJob_StartJob(JOB_EEPRW);   /*TODO: if fail*/
    }
    else{}
}
#endif
/***********************************************************************
*  Name        : EEO_ReadBlock
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EEO_ReadBlock(U16 Addr, U8* DataPtr, U16 Len)
{

    BOOL TemState=FALSE;/*temporery variable for active a task result value.*/

    if(Addr >= EEO_stEepGlobal.Config->EepromSize)
    {
    	EEO_ReportError(EEO_READ_BLOCK_SERVICE_ID,EEO_E_INVALID_ADDRESS)
	}
	else if(DataPtr == NULL)
	{
		EEO_ReportError(EEO_READ_BLOCK_SERVICE_ID,EEO_E_PARAM_POINTER)	
	}
	else if(Len == 0u)
	{
		EEO_ReportError(EEO_READ_BLOCK_SERVICE_ID,EEO_E_PARAM_LENGTH)
	}
	else 
	{
	OSAPI_LockSchedule();
	 if((EEO_bBusRequested==TRUE)&&
            (EEO_stEepGlobal.State==EEO_IDLE))
	 {
		EEO_stEepGlobal.Handle->StartAddr = Addr;
		EEO_stEepGlobal.Handle->DataPtr = DataPtr;
		EEO_stEepGlobal.Handle->TotalLen = Len;
		EEO_stEepGlobal.Handle->RWLen =0u;
		EEO_stEepGlobal.Handle->AccMode = EEO_READ;
		EEO_stEepGlobal.Handle->JobState = EEO_JOB_READ;
		EEO_stEepGlobal.Handle->RetryNum = 0u;
		EEO_stEepGlobal.State = EEO_BUSY;			
		TemState=TRUE;
	  }
	 else
	 {
	 }
	 OSAPI_UnlockSchedule();

	 if(TemState ==TRUE)
	 {
		SysJob_StartJob((U8)JOB_EEPRW);
	 }
	}
	
	return  TemState;
}

/***********************************************************************
*  Name        : EEO_WriteBlock
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EEO_WriteBlock(U16 Addr, U8* DataPtr, U16 Len)
{

     BOOL TemState=FALSE;/*temporery variable for active a task result value.*/
 
    if((Addr >= EEO_stEepGlobal.Config->EepromSize))
    {
		EEO_ReportError(EEO_WRITE_BLOCK_SERVICE_ID,EEO_E_INVALID_ADDRESS)
    }   
	else if(DataPtr == NULL)
	{
		EEO_ReportError(EEO_WRITE_BLOCK_SERVICE_ID,EEO_E_PARAM_POINTER)
	}
	else if(Len == 0u)
	{
		EEO_ReportError(EEO_WRITE_BLOCK_SERVICE_ID,EEO_E_PARAM_LENGTH)
	}
	else
	{
		TemState = CheckInProtectArrange(Addr,Len);
		if(TemState == FALSE)
		{
			EEO_ReportError(EEO_WRITE_BLOCK_SERVICE_ID,EEO_E_WRITE_PROTECT)
		}
		else  
		{
		   TemState=FALSE;
			OSAPI_LockSchedule();
			if((EEO_bBusRequested==TRUE)&&
                           (EEO_stEepGlobal.State == EEO_IDLE))
			{			
			EEO_stEepGlobal.Handle->StartAddr = Addr;
			EEO_stEepGlobal.Handle->DataPtr = DataPtr;
			EEO_stEepGlobal.Handle->TotalLen = Len;
			EEO_stEepGlobal.Handle->RWLen =0u;

			EEO_stEepGlobal.Handle->AccMode = EEO_WRITE;
			EEO_stEepGlobal.Handle->JobState = EEO_JOB_WRITE;
			EEO_stEepGlobal.Handle->RetryNum = 0u;
			EEO_stEepGlobal.Handle->RetryNum = 0u;
			EEO_stEepGlobal.State = EEO_BUSY;	
			TemState=TRUE;
			}
			else
			{
			}
			OSAPI_UnlockSchedule();
			
			if(TemState == TRUE)
			{
			  SysJob_StartJob((U8)JOB_EEPRW);
			}			
		}
	}
		
	return TemState;		
}

/***********************************************************************
*  Name        : EEO_GetState
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
EEO_StateType EEO_GetState (void)
{
	return EEO_stEepGlobal.State;	
}

/***********************************************************************
*  Name        : CheckInProtectArrange
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
STATIC BOOL CheckInProtectArrange(U16 Addr, U16 Len)
{
    
    BOOL ReturnValue = FALSE;/* temporery variable for return value.*/

    if(EEO_stEepGlobal.Config->ProAddrBegin==EEO_stEepGlobal.Config->ProAddrEnd)
    { 
      ReturnValue= TRUE;
    }
    else
    {	   
	if(EEO_stEepGlobal.Config->ProAddrBegin > (Addr + Len))
	{
		ReturnValue = TRUE;
	}	  
	else if(Addr > EEO_stEepGlobal.Config->ProAddrEnd)
	{
		ReturnValue = TRUE;
	}
	else
	{
		/* None */
	}
    }
	return ReturnValue;
}


#if (EEO_PROTECT_RANGE_RESET_API == STD_ON)
/***********************************************************************
*  Name        : EEO_SetProtectRange
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EEO_SetProtectRange(U16 StartAddr,U16 Size)
{
    BOOL ReturnValue = FALSE;/* temporery variable for return value.*/

	if(EEO_stEepGlobal.State == EEO_UNINIT)
	{
		EEO_ReportError(EEO_SET_PROTECT_SERVICE_ID,EEO_E_UNINIT)
	}
	else
	{
		if(StartAddr >= EEO_stEepGlobal.Config->EepromSize)
		{
			EEO_ReportError(EEO_SET_PROTECT_SERVICE_ID,EEO_E_INVALID_ADDRESS)		
		}
		else if(Size ==0u)
		{
			EEO_ReportError(EEO_SET_PROTECT_SERVICE_ID,EEO_E_PARAM_LENGTH)
		}
		else
		{
			EEO_stEepGlobal.Config->ProAddrBegin = StartAddr;
			EEO_stEepGlobal.Config->ProAddrEnd = StartAddr + Size;
			if(EEO_stEepGlobal.Config->ProAddrEnd >= EEO_stEepGlobal.Config->EepromSize)
			{
				EEO_stEepGlobal.Config->ProAddrEnd = EEO_stEepGlobal.Config->EepromSize;	
			}
			ReturnValue = TRUE;
		}
	}
	return ReturnValue;
}

#endif /* EEO_PROTECT_RANGE_RESET_API */

/***********************************************************************
*  Name        : EEO_ClearProtectRange
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EEO_ClearProtectRange(void)
{
	if(EEO_stEepGlobal.State != EEO_UNINIT)
	{
		EEO_stEepGlobal.Config->ProAddrBegin = 0u;
		EEO_stEepGlobal.Config->ProAddrEnd = EEO_stEepGlobal.Config->EepromSize;
	}
	else
	{
		EEO_ReportError(EEO_CLEAR_PROTECT_SERVICE_ID,EEO_E_UNINIT)
	}	
}


/***********************************************************************
*  Name        : EEO_RWJob
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EEO_RWJob(void)
{
	EEO_AccessType  AccMode;/* temporery variable for eeprom access mode.  */

	OSAPI_LockSchedule();
	AccMode = EEO_stEepGlobal.Handle->AccMode;
	OSAPI_UnlockSchedule();	
	
    if((AccMode==EEO_REQUESTBUS)||
	   	(AccMode==EEO_REQUESTBUS_BACK)||
	   	(AccMode==EEO_RELEASEBUS)||
	   	(AccMode==EEO_RELEASEBUS_BACK))
	{	
	  BusHandler();
	}
	else if((AccMode == EEO_READ)||(AccMode == EEO_WRITE))
	{	
	     RWHandler();
	}

}


/***********************************************************************
*  Name        : EEO_DirectReadBlock
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EEO_DirectReadBlock(U16 Addr, U8* DataPtr, U16 Len)
{
   BOOL ReturnValue = FALSE;/* temporery variable for return value.*/
  	
	if(EEO_stEepGlobal.State == EEO_UNINIT)
	{
		EEO_ReportError(EEO_READ_BLOCK_SERVICE_ID,EEO_E_UNINIT)
	}
	else if(Addr >= EEO_stEepGlobal.Config->EepromSize)
    {
    	EEO_ReportError(EEO_READ_BLOCK_SERVICE_ID,EEO_E_INVALID_ADDRESS)
	}
	else if(DataPtr == NULL)
	{
		EEO_ReportError(EEO_READ_BLOCK_SERVICE_ID,EEO_E_PARAM_POINTER)	
	}
	else if(Len == 0u)
	{
		EEO_ReportError(EEO_READ_BLOCK_SERVICE_ID,EEO_E_PARAM_LENGTH)
	}
	else if(EEO_stEepGlobal.State == EEO_BUSY)
	{
		EEO_ReportError(EEO_READ_BLOCK_SERVICE_ID,EEO_E_ACCESS_BUSY)
	}
	else
	{
	     ReturnValue = EEO_INIT_BUS();
	     ReturnValue = EEO_READ_DATA(Addr,(U8)Len,DataPtr);
	     ReturnValue = EEO_DEINIT_BUS();			
	}
  return ReturnValue;
}


/***********************************************************************
*  Name        : EEO_DirectWriteBlock
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EEO_DirectWriteBlock(U16 Addr, U8* DataPtr, U16 Len)
{
    
    BOOL ReturnValue = FALSE;/* temporery variable for return value.*/
 	
     U8 blocklen =EEO_stEepGlobal.Config->Eep_WBlockLen;
	 
	if(EEO_stEepGlobal.State == EEO_UNINIT)
	{
		EEO_ReportError(EEO_WRITE_BLOCK_SERVICE_ID,EEO_E_UNINIT)
	}
    if((Addr >= EEO_stEepGlobal.Config->EepromSize))
    {
		EEO_ReportError(EEO_WRITE_BLOCK_SERVICE_ID,EEO_E_INVALID_ADDRESS)
    }   
	else if(DataPtr == NULL)
	{
		EEO_ReportError(EEO_WRITE_BLOCK_SERVICE_ID,EEO_E_PARAM_POINTER)
	}
	else if(Len == 0u)
	{
		EEO_ReportError(EEO_WRITE_BLOCK_SERVICE_ID,EEO_E_PARAM_LENGTH)
	}
	else if(EEO_stEepGlobal.State == EEO_BUSY)
	{
		EEO_ReportError(EEO_WRITE_BLOCK_SERVICE_ID,EEO_E_ACCESS_BUSY)
	}
	else
	{
		ReturnValue = CheckInProtectArrange(Addr,Len);
		if(ReturnValue == 	FALSE)
		{
			EEO_ReportError(EEO_WRITE_BLOCK_SERVICE_ID,EEO_E_WRITE_PROTECT)
		}
		else
		{
		 U8 left_length = (U8)(blocklen - (Addr% blocklen));	
		 U8 RW_len =0u;
		 
		 ReturnValue = EEO_INIT_BUS();
		 while(Len>0u)
		 {
			if(Len<left_length)
			{
			  RW_len =(U8)Len;
			}
			else
			{
			  RW_len=left_length;
			}
			
		   ReturnValue =EEO_WRITE_DATA(Addr,RW_len,DataPtr);
		   if(ReturnValue ==TRUE)
		   {
		    Addr+=RW_len;
		    DataPtr+=RW_len;
		    Len-=RW_len;
		    left_length=blocklen;
		    delay_us(5000u); /*delay 5ms*/
		   }
		   else
		   {
		     break;
		   }
		  }
		}
		ReturnValue = EEO_DEINIT_BUS();		
	}
	return ReturnValue;		
}


/***********************************************************************
*  Name        : RWHandler
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void RWHandler(void)
{
	BOOL ReturnValue=FALSE;/*temporery variable for return value.  */
    BOOL bNotifyed=FALSE;
	ERR_TYPE errtype =ERR_OK;

	EEO_JobStateType JobState;/*temporery variable for eeprom transfer job state.  */
    EEO_StateType State;
    EEO_HandleType	*TemHandle;/*temporery variable for eeprom handle pointer */
    U8 blocklen =EEO_stEepGlobal.Config->Eep_WBlockLen;
	
	OSAPI_LockSchedule();
	JobState = EEO_stEepGlobal.Handle->JobState;
	State=EEO_stEepGlobal.State;
	OSAPI_UnlockSchedule();	
	TemHandle = EEO_stEepGlobal.Handle;
	

    if(JobState ==EEO_JOB_READ)
	{			
		    ReturnValue = EEO_READ_DATA(TemHandle->StartAddr,(U8)TemHandle->TotalLen,TemHandle->DataPtr);	
		    if(ReturnValue)
		    {		    
		       JobState = EEO_JOB_OK;
    		       State = EEO_IDLE;   
    		       ReturnValue = TRUE;
			bNotifyed=TRUE;
		    }
		    else
		    {
		       JobState = EEO_JOB_OK;
    		       State = EEO_IDLE;   
    		      ReturnValue = TRUE;
		      bNotifyed=TRUE;
    		      errtype=ERR_FAILED; 		
		    }
    }
    else if(JobState == EEO_JOB_READ_CONTINUE)
    {
		 /*TODO: */
    }		  
    if(JobState ==EEO_JOB_WRITE)
    {
#if 1 /* using internal data flash as eeprom */
        ReturnValue = EEO_WRITE_DATA(TemHandle->StartAddr,blocklen,TemHandle->DataPtr);
        JobState = EEO_JOB_OK;
        State = EEO_IDLE;
        if(!ReturnValue)  /* set err flag*/
          errtype=ERR_FAILED;
        ReturnValue = TRUE;
        bNotifyed=TRUE;
#else  /* using external EEPROM */
			U8 left_length = (U8)(blocklen - (TemHandle->StartAddr % blocklen));	
			U8 RW_len =0u;
			if(TemHandle->TotalLen<left_length)
			{
			  RW_len =(U8)TemHandle->TotalLen;
			}
			else
			{
			 RW_len=left_length;
			}
			
		        ReturnValue = EEO_WRITE_DATA(TemHandle->StartAddr,RW_len,TemHandle->DataPtr);
		        if(ReturnValue)
		        {
			     TemHandle->RWLen+=RW_len;
		            JobState = EEO_JOB_WRITE_CONTINUE; 
			      SysJob_DelayStartJob(JOB_EEPRW,EEO_stEepGlobal.Config->WriteWaitTime);						            
		        }
		        else
		        {
		           JobState = EEO_JOB_OK;
    		           State = EEO_IDLE;   
    		      	    ReturnValue = TRUE;
		           bNotifyed=TRUE;
    		          errtype=ERR_FAILED; 						
		        }  
    }
    else if(JobState == EEO_JOB_WRITE_CONTINUE)
    {	
		  if(TemHandle->TotalLen>TemHandle->RWLen)
		 {
		 	U8 left_length = blocklen;	
			U8 RW_len =(U8)(TemHandle->TotalLen-TemHandle->RWLen);
			if(RW_len>left_length)
			{
			  RW_len=left_length;
			}
			
		 	ReturnValue = EEO_WRITE_DATA(TemHandle->StartAddr+TemHandle->RWLen,RW_len,TemHandle->DataPtr+TemHandle->RWLen);
	   		if(ReturnValue)
	    		{
	           	JobState = EEO_JOB_WRITE_CONTINUE; 
		    	TemHandle->RWLen+=RW_len;		
	    	    	SysJob_DelayStartJob((U8)JOB_EEPRW,EEO_stEepGlobal.Config->WriteWaitTime);					            
	    		}
			else
			{
		      	JobState = EEO_JOB_OK;
    		      	State = EEO_IDLE;   
    		      	ReturnValue = TRUE;
		      	bNotifyed=TRUE;
    		      	errtype=ERR_FAILED; 	
			}
		}
		else
		{
		      JobState = EEO_JOB_OK;
    		      State = EEO_IDLE;  
		    ReturnValue = TRUE;			
		    bNotifyed=TRUE;
		}
#endif
		}
		else if(JobState ==EEO_JOB_FAILED)
		{
		      JobState = EEO_JOB_OK;
    		      State = EEO_IDLE;  
    		      	ReturnValue = TRUE;
			/*TODO: add error*/
		}
		else
		{		
	    	  ReturnValue = TRUE;
		}
			  
	OSAPI_LockSchedule();
	EEO_stEepGlobal.Handle->JobState=JobState;
	EEO_stEepGlobal.State=State;
	OSAPI_UnlockSchedule();
	
	if(bNotifyed==TRUE)
	{
	  if(errtype!=ERR_OK)
	  {
	  EEO_ERROR_NOTIFICATION(errtype);
	  }
	  else
	  {
	  EEO_END_NOTIFICATION();	  
	  }
	}	  

}
#if (EEO_SHARED_BUS_SUPPORTED==STD_ON)
/***********************************************************************
*  Name        : BusHandler
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void BusHandler(void)
{
	BOOL ReturnValue=FALSE;/*temporery variable for return value.  */
	BOOL bRequest;
	EEO_AccessType AccMode;
	BusMng_RequestBusType ReqRet;
	OSAPI_LockSchedule();
	bRequest =EEO_bBusRequested;
	AccMode = EEO_stEepGlobal.Handle->AccMode;
	OSAPI_UnlockSchedule();
       if(AccMode==EEO_REQUESTBUS)
	{	
	  if(bRequest==FALSE)
	  {
	   ReqRet =BusMng_Request(E_DEV_EEPROM, TRUE,EEO_BusRequested);
	    if(ReqRet==BUSMNG_REQUEST_FINISHED)
		{
 	  		OSAPI_LockSchedule();
	  		EEO_bBusRequested=TRUE;
    	  	EEO_stEepGlobal.State = EEO_IDLE;	  
	 		OSAPI_UnlockSchedule();	
		    EEO_INIT_NOTIFICATION(ERR_OK);/*hase used*/
		}
		else if((ReqRet==BUSMNG_REQUEST_ACCEPTED)||
			(ReqRet==BUSMNG_REQUEST_REQUESTED))
		{
	     /*waiting for request*/
	     }			
	     else if(ReqRet==BUSMNG_REQUEST_FAIL)
	     {
	       /*TODO: check */
	     }
	  }
	  else
	  {
 	    OSAPI_LockSchedule();
    	     EEO_stEepGlobal.State = EEO_IDLE;	  
	    OSAPI_UnlockSchedule();	  
	    EEO_INIT_NOTIFICATION(ERR_OK);/*already requested*/
	  }
	}
	else if(AccMode==EEO_REQUESTBUS_BACK)
	{
 	  OSAPI_LockSchedule();
	  EEO_bBusRequested=TRUE;
    	  EEO_stEepGlobal.State = EEO_IDLE;	  
	 OSAPI_UnlockSchedule();	

	   ReturnValue= EEO_INIT_BUS();	   
	   if(ReturnValue==TRUE)
	   {
	    EEO_INIT_NOTIFICATION(ERR_OK);
	   }
	   else
	   {
	   EEO_INIT_NOTIFICATION(ERR_FAILED);
	   }	
	}
	else if(AccMode==EEO_RELEASEBUS)
	{
	 if(bRequest==TRUE)
	 {
	  ReqRet =BusMng_Release(E_DEV_EEPROM,TRUE,EEO_BusReleased);
	    if(ReqRet==BUSMNG_REQUEST_FINISHED)
		{
 	  		OSAPI_LockSchedule();
	  		EEO_bBusRequested=FALSE;
    	  		EEO_stEepGlobal.State = EEO_IDLE;	  
	 		OSAPI_UnlockSchedule();	
		    EEO_INIT_NOTIFICATION(ERR_OK);/*hase used*/
		}
		else if((ReqRet==BUSMNG_REQUEST_ACCEPTED)||
			(ReqRet==BUSMNG_REQUEST_REQUESTED))
		{
	     /*waiting for request*/
	     }			
	     else if(ReqRet==BUSMNG_REQUEST_FAIL)
	     {
	       /*TODO: check */
	     }
	 }
	 else
	 {
 	  	OSAPI_LockSchedule();
    	  	EEO_stEepGlobal.State = EEO_IDLE;	  
	 	OSAPI_UnlockSchedule();	
	       EEO_DEINIT_NOTIFICATION(ERR_OK);/*hase release*/
	 }
	}
	else if(AccMode==EEO_RELEASEBUS_BACK)
	{
 	    OSAPI_LockSchedule();
	    EEO_stEepGlobal.State = EEO_IDLE;	
	    EEO_bBusRequested=FALSE;		
	    OSAPI_UnlockSchedule();	 	
	  ReturnValue =EEO_DEINIT_BUS();
    	  if(ReturnValue==TRUE)
	 {
		EEO_DEINIT_NOTIFICATION(ERR_OK);
	  }
	  else
	  {
	   	EEO_DEINIT_NOTIFICATION(ERR_FAILED);
	  }
	}
}
#else
/***********************************************************************
*  Name        : BusHandler
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void BusHandler(void)
{
	BOOL ReturnValue=FALSE;/*temporery variable for return value.  */
	EEO_AccessType AccMode;
	
	OSAPI_LockSchedule();
	AccMode = EEO_stEepGlobal.Handle->AccMode;
	OSAPI_UnlockSchedule();
	
    if(AccMode==EEO_REQUESTBUS)
	{	
	  ReturnValue= EEO_INIT_BUS();  
	  if(ReturnValue==TRUE)
	  {		
 	    OSAPI_LockSchedule();		  
      	EEO_stEepGlobal.State = EEO_IDLE;	
	    EEO_bBusRequested=TRUE;
	    OSAPI_UnlockSchedule();		   
	    EEO_INIT_NOTIFICATION(ERR_OK);		  
     }
     else
     {
 	    OSAPI_LockSchedule();		  
      	EEO_stEepGlobal.State = EEO_IDLE;	
        OSAPI_UnlockSchedule();		 
        EEO_INIT_NOTIFICATION(ERR_FAILED);	
      }
    }
    else if(AccMode==EEO_RELEASEBUS)
    {
      ReturnValue =EEO_DEINIT_BUS();	
	  
      if(ReturnValue==TRUE)
	  {		
        OSAPI_LockSchedule();	
        EEO_bBusRequested=FALSE;		
        EEO_stEepGlobal.State = EEO_IDLE;	
        OSAPI_UnlockSchedule();			 
        EEO_DEINIT_NOTIFICATION(ERR_OK);
	  }
	  else
	  {
 	    OSAPI_LockSchedule();	
      	   EEO_stEepGlobal.State = EEO_IDLE;	
	   OSAPI_UnlockSchedule();		  
	   EEO_DEINIT_NOTIFICATION(ERR_FAILED);
	  }
	}	   
}
#endif


/**************** END OF FILE *****************************************/


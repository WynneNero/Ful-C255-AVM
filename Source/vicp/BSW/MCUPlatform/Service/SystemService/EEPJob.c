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
* 0.2    Jan 13,2017  ZhangJie  Fix Coverity warning.
*-----------------------------------------------------------------------
* 0.3  Apr 07,2017   PEI Jingli  Fix warnings of OSAPI.
*=====================================================================*/
#include <Service_HOOKS.h>
#include <Tools.h>
#include "EEPJob.h"
#include "EEPTable.h"
#include "OSAdapter_if.h"

/***************************************************************************
* FILE LOCAL DEFINITIONS
****************************************************************************/
   /**
   * EED_astJobQueue queues the references to data blocks of one or 
   * more NVRam resource for an upload/download. A reference is only queued
   * in case there is no reference in the array EED__aenRequestedJobs.
   */
static EED_tstJob EED_astJobQueue[EED_nLastBlock];

   /**
   * EED_u8ReadPos indicates the read position in the job queue
    */
static U8 EED_u8ReadPos;

   /**
   * EED_u8WritePos indicates the write position in the job queue
    */
static U8 EED_u8WritePos;




/******************************************************************************
* FILE LOCAL FUNCTION PROTOTYPES
******************************************************************************/



/******************************************************************************
* FUNCTION DEFINITIONS
******************************************************************************/
   
/***********************************************************************
*  Name        : EED_InitJobQueueModule
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
 void EED_InitJobQueueModule( void )
 {


   /* Reset job queue pointers */
   EED_u8ReadPos =0u;
   EED_u8WritePos = 0u;
 }


/***********************************************************************
*  Name        : EED_DeinitJobQueueModule
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EED_DeinitJobQueueModule( void )
{


}
	
/***********************************************************************
*  Name        : EED_DeinitJobQueueModule
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EED_ResetJobQueue( void )
{

	/* Reset job queue pointers */
	EED_u8ReadPos =0u;
        EED_u8WritePos = 0u;

}


/***********************************************************************
*  Name        : EED_PutJob
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EED_PutJob( EED_ptstJob pNewJob )
{
	/* Disable all maskable interrupts */
	OSAPI_LockSchedule();
	
   /* No check for a full queue. Queue must allways allow an entry. */
  
   /* Insert job */
   EED_astJobQueue[EED_u8WritePos].enBlock = pNewJob->enBlock;
   EED_astJobQueue[EED_u8WritePos].enOperation = pNewJob->enOperation;
   EED_astJobQueue[EED_u8WritePos].enNotifiyResource=pNewJob->enNotifiyResource;
   /* Update position for next entry */
   EED_u8WritePos++;

	/* Enable all maskable interrupts */
	OSAPI_UnlockSchedule();

}


/***********************************************************************
*  Name        : EED_SetupLastJob
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EED_SetupLastJob( EED_ptstJob pNextJob  )
{
   /******************************************************************************
   * FUNCTION LOCAL DEFINITIONS
   ******************************************************************************/

   /******************************************************************************
   * FUNCTION CODE
   ******************************************************************************/
	/* Disable all maskable interrupts */
	OSAPI_LockSchedule();

   /* Move to the last inserted job  */
   EED_u8WritePos--;
   /* Insert additional job data */
   EED_astJobQueue[EED_u8WritePos].enNotifiyResource = pNextJob->enNotifiyResource;
   /* Restore write position */
   EED_u8WritePos++;

	/* Enable all maskable interrupts */
	OSAPI_UnlockSchedule();

}
	
/***********************************************************************
*  Name        : EED_InsertHeadJob
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EED_InsertHeadJob( EED_ptstJob pNewJob )
{

    U8    u8Idx; /* Loop index */
     

	/* Disable all maskable interrupts */
	OSAPI_LockSchedule();
   
   if( EED_u8WritePos > 0u )
   {
     /* Move all existing entries one element up */
      for( u8Idx = EED_u8WritePos; u8Idx > 0u; u8Idx-- )
      {
         /* Copy data from the previous to the next element */
         _memcpy( (U8*)&EED_astJobQueue[u8Idx], (U8*)&EED_astJobQueue[u8Idx-1u], (U16)sizeof(EED_tstJob) );
      }
   }
      
   /* Insert job */
   EED_astJobQueue[0].enBlock = pNewJob->enBlock;
   EED_astJobQueue[0].enOperation = pNewJob->enOperation;
   /* Update write position */
   EED_u8WritePos++;

 	/* Enable all maskable interrupts */
	OSAPI_UnlockSchedule();

}

  	
   
/***********************************************************************
*  Name        : EED_GetJob
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
EED_tenJobState	EED_GetJob( EED_ptstJob pNextJob  )
{

    EED_tenJobState enRet; /* Variable for returning state of job operation */
   U8    u8Idx; /* Loop index */
    
	OSAPI_LockSchedule();

	if( EED_u8ReadPos == EED_u8WritePos )
	{
      /* Queue is empty */
      enRet = EED__nQueueEmpty;
	}
	else
	{
      /* Read position is always the first element of the queue */
      EED_u8ReadPos = 0u;
      /* Fill in the job data */
		pNextJob->enBlock = EED_astJobQueue[EED_u8ReadPos].enBlock;
		pNextJob->enOperation = EED_astJobQueue[EED_u8ReadPos].enOperation;
		pNextJob->enNotifiyResource=EED_astJobQueue[EED_u8ReadPos].enNotifiyResource;
      /* Remove first element of the JobQueue */
      for( u8Idx = 1u; u8Idx < EED_u8WritePos; u8Idx++ )
      {
         /* Copy data from the next to the previous element */
         _memcpy( (U8*)&EED_astJobQueue[u8Idx-1u],(U8*) &EED_astJobQueue[u8Idx], (U16)sizeof(EED_tstJob) );
      }
      
      /* Decrement the write position */
      EED_u8WritePos -= 1u;

      /* Job is retrieved */
      enRet = EED__nOk;
	}

	/* Enable all maskable interrupts */
	OSAPI_UnlockSchedule();

	return enRet;

}


/***********************************************************************
*  Name        : EED_IsJobPending
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL	EED_IsJobPending( void )
{

   BOOL boIsPending = FALSE;   /* Return value of the job queue */

	OSAPI_LockSchedule();

	if( EED_u8ReadPos == EED_u8WritePos )
	{
      /* Queue is empty */
      boIsPending = FALSE;
	}
   else
   {
      /* Jobs are queued */
      boIsPending = TRUE;
   }

	OSAPI_UnlockSchedule();

	return boIsPending;

}


/**************** END OF FILE *****************************************/


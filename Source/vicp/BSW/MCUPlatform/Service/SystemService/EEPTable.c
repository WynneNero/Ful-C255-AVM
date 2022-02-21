/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                         *
*   AUTHOR     :                                       *
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
*-----------------------------------------------------------------------
* 0.4  Apr 07,2017   PEI Jingli  Fix warnings of OSAPI.
*=====================================================================*/
#include "Define.h"
#include <Service_HOOKS.h>
#include <Tools.h>
#include <EventMng.h>
#include "EEPJobManager.H"
#include "EEPTable.h"
#include "EEPJob.h"
#include "OSAdapter_if.h"

extern const EED_tstAddressData EED_rastDataBlocksAddress[];
extern EED_tstDataBlock EED_astDataBlocks[];
/**
* EED__stCurrentJob indicates the current processed job
* The variable EED__stCurrentJob must not change its content in the call chain
*  IoInit -> EED_IoOK (HandleIO) or  EED_IoError (HandleIO)
* So, it must be ensured by SW-Design that this variable keeps its content
* form IoInit to IoOk or IoError by invoking the interface EET_enRequestIo
* only when one job has been finished.
*/
static  EED_tstJob EED_stCurrentJob;

/**
 * Flag to indicate the normal power condition
 * @values: True - Normal Power Condition, False - Undervoltage Power Condition
*/
static BOOL EED_boNormalVoltage = TRUE;


/******************************************************************************
* FILE LOCAL FUNCTION PROTOTYPES
******************************************************************************/


/**
 * This function validates for a data block the cecksum in RAM, if the data block is in state consistent.
* If an error is detected the functions initiates a new upload of the block and moves to state
* upload running.
 */
BOOL PerformChecksumCheck(EED_tenDataBlockID enDataBlock);


/**
  * Handles the IO operation on IoOK and IoError
*/
void HandleIO(ERR_TYPE enRetError);


/**
 * Queue a data block for downloading to the EEPROM.
 * The function is not threadsafe. Protection has to be done by the caller.
*/
BOOL QueueDataBlock(EED_tenDataBlockID enDataBlock);


/**
  * Request an IO operation at the IOQHA
  * The interface centralizes the call to the Request interface.
  * The call shall not be executed within a critical section, because
  * the IOQHA can perform a task switch.
*/
BOOL RequestIO(void);

/**
  * Calculate CRC and store it in RAM area of a data block
*/
void SetChecksum(EED_tenDataBlockID enDataBlock);
BOOL MakeChechsum(U8* bufben, U16 len, U16* pchecksum);

/******************************************************************************
* FUNCTION DEFINITIONS
******************************************************************************/

/***********************************************************************
*  Name        : EED_Reset
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EED_Reset(void)
{
    U8 u8Index = 0u;  /* Array index */
    EED_tenDataBlockID enBlockId; /* Index into array EED_astDataBlocks */

    /* Assume normal power condition */
    EED_boNormalVoltage = TRUE;

    /* Init the job queue module */
    EED_InitJobQueueModule();

    /* Reset loop index */
    u8Index = 0u;

    /* Load data blocks with default data. Some data blocks must be available before EET can be used */
    while(EED_aenStartupBlocks[u8Index] != EED_nNVRAM_Termination)
    {
        /* Get the index of the data block */
        enBlockId = EED_aenStartupBlocks[u8Index];
        /* Copy the the default data from ROM to RAM. */
        _memcpy(EED_rastDataBlocksAddress[enBlockId].pu8AdrRamData,
                EED_rastDataBlocksAddress[enBlockId].pu8AdrRomData,
                EED_rastDataBlocksAddress[enBlockId].u16LenDataBlock);
        /* Set state of data block. Data is loaded from ROM not EEPROM. */
        EED_astDataBlocks[enBlockId].enBlockStatus = EED_nConsistentNotSaved;
        /* Move to next entry */
        u8Index++;
    }


}


/***********************************************************************
*  Name        : EED_Init
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EED_Init(void)
{
    EEO_Init();
}


/***********************************************************************
*  Name        : EED_Deinit
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EED_Deinit(void)
{
    EEO_DeInit();
}


/***********************************************************************
*  Name        : EED_MarkNVRamResource
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EED_MarkNVRamResource(U8 u8NVRAMRes, U32 Event, U8 u8JobOperation)
{
    EED_tpenDataBlockID pBlockId;           /* Pointer to a resource of kind NVRAMRes */
    U8 u8NumNVRAMResDataBlocks = 0u;        /* Number of data blocks assigned to a NVRAMRes */
    U8 u8Index = 0u;                        /* Array index */
    EED_tstJob stJob;                   /* Job to be performed */
    BOOL boJobAlreadyQueued = FALSE;    /* Flag to indicate if jobs are already queued */
    BOOL boJobAdded = FALSE ;           /* A job was added to the job queue */
    BOOL boRet = FALSE;             /* Return value */

    /* Disable all maskable interrupts */
    OSAPI_LockSchedule();

    /* Check for valid resource */
    if(u8NVRAMRes < (U8)EED_RAM_NUMB)
    {
        /* Get pointer to selected NVRam-Resource */
        pBlockId = EED_apenNVRAMResources[ u8NVRAMRes ];
        /* Check for valid resource */
        if(pBlockId != 0x0)
        {
            /* Get the number of configured data blocks of the resource */
            for(u8Index = 0u; u8Index < (U8)EED_nLastBlock; u8Index++)
            {
                /* Check for the end of the NVRam resource */
                if(pBlockId[ u8Index ] == EED_nNVRAM_Termination)
                {
                    /* Leave the for-loop */
                    break;
                }
                else
                {
                    /* Summarize the data block of a NVRam resource */
                    u8NumNVRAMResDataBlocks++;
                }
            }

            /* Check if jobs are already queued */
            boJobAlreadyQueued = EED_IsJobPending();

            /* Set up the job */
            stJob.enNotifiyResource = 0u;
            /* Check the operation direction of the resource */
            if(u8JobOperation == EED__nUpload)
            {
                /* Upload */
                stJob.enOperation = EED__nenJobOperationRead;
                /* Get all data blocks of resource */
                for(u8Index = 0u; u8Index < u8NumNVRAMResDataBlocks; u8Index++)
                {
                    if((EED_astDataBlocks[ pBlockId[ u8Index ] ].enBlockStatus == EED_nEmpty) ||
                        (EED_astDataBlocks[ pBlockId[ u8Index ] ].enBlockStatus == EED_nConsistentNotSaved))
                    {
                        stJob.enBlock = pBlockId[ u8Index ];
                        /* Put job into queue */
                        EED_PutJob(&stJob);
                        /* Set new block state */
                        EED_astDataBlocks[ pBlockId[ u8Index ] ].enBlockStatus = EED_nUploadRunning;
                        boJobAdded = TRUE;
                    }
                }
                /* Check if job was queued */
                if(boJobAdded == TRUE)
                {
                    stJob.enNotifiyResource = Event;
                    /* Insert additional data to the last queued job */
                    EED_SetupLastJob(&stJob);
                    /* Blocks must be downloaded */
                    boRet = TRUE;
                }
            }
            else
            {
                /* Download */
                /* Set job operation */
                stJob.enOperation = EED__nenJobOperationWrite;
                /* Get the data block of the members of a NVRam resource */
                for(u8Index = 0u; u8Index < u8NumNVRAMResDataBlocks; u8Index++)
                {
                    if(EED_astDataBlocks[ pBlockId[ u8Index ] ].enBlockStatus == EED_nConsistentNotSaved)
                    {
                        if(EED_astDataBlocks[ pBlockId[ u8Index ] ].boPerfomChecksum == TRUE)
                        {
                            /* Calculate the checksum of the Data Block in RAM */
                            SetChecksum(pBlockId[ u8Index ]);
                        }
                        stJob.enBlock = pBlockId[ u8Index ];
                        /* Put job into queue */
                        EED_PutJob(&stJob);
                        /* Set new block state */
                        EED_astDataBlocks[ pBlockId[ u8Index ] ].enBlockStatus = EED_nDownloadRunning;
                        boJobAdded = TRUE;
                    }
                }
                /* Check if job was queued */
                if(boJobAdded == TRUE)
                {
                    stJob.enNotifiyResource = Event;
                    /* Insert additional data to the last queued job */
                    EED_SetupLastJob(&stJob);
                    boRet = TRUE;
                }
            }
        }
        else
        {
            boRet = FALSE;
        }
    }
    else
    {
        boRet = FALSE;
    }

    /* Enable all maskable interrupts */
    OSAPI_UnlockSchedule();

    /* Check if an operation must be initiated */
    if((boJobAlreadyQueued == FALSE) && (boJobAdded == TRUE))
    {
        /* Start up/download. No jobs were queued in a previous call of this interface. */
        boRet=RequestIO();
    }
    else
    {
        /* Jobs are already queued and processing was started by a previous call of this interface,
            so do not request IOQHA again. */
    }

    return boRet;

}


/***********************************************************************
*  Name        : EED_LockDataBlock
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EED_LockDataBlock(EED_tenDataBlockID enDataBlock)
{

    BOOL boRet = FALSE; /* Return value of the interface */


    /* Disable all maskable interrupts */
    OSAPI_LockSchedule();

    /* Check for valid block */
    if(enDataBlock < EED_nLastBlock)
    {
        /* Check current state of data block */
        if((EED_astDataBlocks[enDataBlock].enBlockStatus == EED_nConsistent) ||
            (EED_astDataBlocks[enDataBlock].enBlockStatus == EED_nConsistentNotSaved))
        {
            /* Set state of data block */
            EED_astDataBlocks[enDataBlock].enBlockStatus = EED_nLocked;
            boRet = TRUE;
        }
    }

    /* Enable all maskable interrupts */
    OSAPI_UnlockSchedule();

    return boRet;

}


/***********************************************************************
*  Name        : EED_UnlockDataBlock
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EED_UnlockDataBlock(EED_tenDataBlockID enDataBlock)
{

    BOOL boRet = FALSE; /* Local variable keeping the state of a data block
                                             to ensure reentrancy of interface */

    /* Disable all maskable interrupts */
    OSAPI_LockSchedule();

    /* Check for valid block */
    if(enDataBlock < EED_nLastBlock)
    {
        /* Check current state of data block */
        if(EED_astDataBlocks[enDataBlock].enBlockStatus == EED_nLocked)
        {
            /* Set state of data block */
            EED_astDataBlocks[enDataBlock].enBlockStatus = EED_nConsistentNotSaved;
            boRet = TRUE;
        }
    }

    /* Enable all maskable interrupts */
    OSAPI_UnlockSchedule();

    /* Return content of local variable */
    return boRet;

}


/***********************************************************************
*  Name        : EED_GetDataBlockState
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
EED_tenDataBlockStatus EED_GetDataBlockState(EED_tenDataBlockID enDataBlock)
{

    /* Local variable keeping the state of a data block to ensure reentrancy of interface */
    EED_tenDataBlockStatus enBlockStatus = EED_nInvalidBlock ;


    /* Disable all maskable interrupts */
    OSAPI_LockSchedule();

    /* Check for valid block */
    if(enDataBlock < EED_nLastBlock)
    {
        /* Get the block status */
        enBlockStatus = EED_astDataBlocks[enDataBlock].enBlockStatus;
    }

    /* Enable all maskable interrupts */
    OSAPI_UnlockSchedule();

    /* Return content of local variable */
    return enBlockStatus;

}


/***********************************************************************
*  Name        : EED_SaveDataBlock
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EED_SaveDataBlock(EED_tenDataBlockID enDataBlock)
{

    BOOL boRet = FALSE; /* Return value of the interface */
    BOOL boJobAlreadyQueued = FALSE; /* Flag to indicate if jobs are already queued */
    BOOL boJobAdded = FALSE; /* Flag to indicate whether a job shall be queued */


    /* Disable all maskable interrupts */
    OSAPI_LockSchedule();

    /* Check for valid block */
    if(enDataBlock < EED_nLastBlock)
    {
        /* Check if a job is currently processed */
        if(EED_stCurrentJob.enOperation != EED__nenJobOperationIdle)
        {
            /* A job is currently processed and should not be disturbed by a new Request */
            boJobAlreadyQueued = TRUE;
        }
        else
        {
            /* Check if jobs are already queued */
            boJobAlreadyQueued = EED_IsJobPending();
        }
        /* Queue the data block for downloading */
        boJobAdded = QueueDataBlock(enDataBlock);
        /* Data block operation sets the return value */
        boRet = boJobAdded;
    }

    /* Enable all maskable interrupts */
    OSAPI_UnlockSchedule();

    /* Check if an operation must be initiated */
    if((boJobAlreadyQueued == FALSE) && (boJobAdded == TRUE))
    {
        /* Start up/download. No jobs were queued in a previous call of this interface. */
        boRet=RequestIO();
    }
    else
    {
        /* Jobs are already queued and processing was started by a previous call of this interface,
            so do not request IOQHA again. */
    }

    return boRet;

}




/***********************************************************************
*  Name        : EED_UnlockAndSavDataBlock
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EED_UnlockAndSavDataBlock(EED_tenDataBlockID enDataBlock)
{
    BOOL boRet = FALSE; /* Return value of the interface */
    BOOL boJobAlreadyQueued = FALSE; /* Flag to indicate if jobs are already queued */
    BOOL boJobAdded = FALSE; /* Flag to indicate whether a job shall be queued */


    /* Embrace the called interfaces with a critcial section to avoid
      task switch between the function calls*/
    /* Disable all maskable interrupts */
    OSAPI_LockSchedule();

    /* Check for valid block */
    if(enDataBlock < EED_nLastBlock)
    {
        /* Unlock the block */
        boRet = EED_UnlockDataBlock(enDataBlock);
        /* Check whether block can be downloaded */
        if(boRet == TRUE)
        {
            /* Save the data block */
            /* Check if a job is current processed */
            if(EED_stCurrentJob.enOperation != EED__nenJobOperationIdle)
            {
                /* A job is currently processed and should not be distrubed by a new Request */
                boJobAlreadyQueued = TRUE;
            }
            else
            {
                /* Check if jobs are already queued */
                boJobAlreadyQueued = EED_IsJobPending();
            }

            /* Queue the data block for downloading */
            boJobAdded = QueueDataBlock(enDataBlock);
            /* Data block operation sets the return value */
            boRet = boJobAdded;

        }
    }

    /* Enable all maskable interrupts */
    OSAPI_UnlockSchedule();

    /* Check if an operation must be initiated */
    if((boJobAlreadyQueued == FALSE) && (boJobAdded == TRUE))
    {
        /* Start up/download. No jobs were queued in a previous call of this interface. */
        boRet=RequestIO();
    }
    else
    {
        /* Jobs are already queued and processing was started by a previous call of this interface,
           so do not request IOQHA again. */
    }
    return boRet;

}


/***********************************************************************
*  Name        : EED_ModifyBitData
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EED_ModifyBitData(EED_tenDataBlockID enDataBlock, U32 u32SymbolAddress,
                       U8 u8BitPosition, U8 u8BitSize, U8 u8NewValue)
{

    BOOL boRet = FALSE; /* Return value */
    U8 u8OldValue;      /* Old value at symbol address */
    U8 u8BitMask;       /* Mask out unused bits of new value */
    U8 u8Idx;           /* Loop counter */
    U8* pu8RAMSymbol;   /* Address of symbol in RAM area */


    /* Disable all maskable interrupts */
    OSAPI_LockSchedule();

    /* Check for valid block */
    if(enDataBlock < EED_nLastBlock)
    {
        /* Check if data block is locked */
        if(EED_astDataBlocks[enDataBlock].enBlockStatus == EED_nLocked)
        {
            /* Check if symbol address is out of area */
            if(u32SymbolAddress < EED_rastDataBlocksAddress[enDataBlock].u16LenDataBlock)
            {
                /* Check allowed range of bit manipulation */
                if(u8BitSize <= 8u)
                {
                    /* Get address of symbol within a RAM area */
                    pu8RAMSymbol = EED_rastDataBlocksAddress[enDataBlock].pu8AdrRamData + u32SymbolAddress;

                    /* Check range of bit manipulation */
                    if(u8BitSize == 8u)
                    {
                        /* Write new value */
                        *pu8RAMSymbol = u8NewValue;
                    }
                    else
                    {
                        /* Read old value */
                        u8OldValue = *pu8RAMSymbol;
                        /* Set bit comparison mask */
                        u8BitMask = 0x1u;
                        /* Align new value to start of bit position */
                        u8NewValue <<= u8BitPosition;
                        /* Align mask to start of bit position */
                        u8BitMask <<= u8BitPosition;

                        /* Loop to the bit range*/
                        for(u8Idx = u8BitPosition; u8Idx < (u8BitPosition + u8BitSize); u8Idx++)
                        {
                            /* Check if a bit of the new value sets or clears the old bit value */
                            if(u8NewValue & u8BitMask)
                            {
                                /* Set the bit */
                                u8OldValue |= u8BitMask;
                            }
                            else
                            {
                                /* Clear the bit */
                                u8OldValue &= (~u8BitMask);
                            }
                            /* Build the mask for the next bit*/
                            u8BitMask <<= 1u;
                        }

                        /* Write value back */
                        *pu8RAMSymbol = u8OldValue;
                    }
                    /* Block state shall still be Locked */
                    EED_astDataBlocks[enDataBlock].enBlockStatus = EED_nLocked;
                    /* Set return value */
                    boRet = TRUE;
                }
            }
        }
    }

    /* Enable all maskable interrupts */
    OSAPI_UnlockSchedule();

    return boRet;
}


/***********************************************************************
*  Name        : EED_ModifyByteData
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EED_ModifyByteData(EED_tenDataBlockID enDataBlock, U32 u32SymbolAddress,
                        U8 u8ByteSizeOfElement, U8 u8NumElements, void* pvNewValue)
{

    BOOL boRet = FALSE; /* Return value */
    U16 u16ArraySize;       /* Size of array */
    U8* pu8RAMSymbol;       /* Address of symbol in RAM area */


    /* Disable all maskable interrupts */
    OSAPI_LockSchedule();

    /* Check for valid block */
    if(enDataBlock < EED_nLastBlock)
    {
        /* Check if data block is locked */
        if(EED_astDataBlocks[enDataBlock].enBlockStatus == EED_nLocked)
        {
            /* Check if symbol address is out of area */
            if(u32SymbolAddress < EED_rastDataBlocksAddress[enDataBlock].u16LenDataBlock)
            {
                /* Check area size to be modified */
                u16ArraySize = (U16)u8ByteSizeOfElement *  (U16)u8NumElements;
                if(u16ArraySize <= EED_rastDataBlocksAddress[enDataBlock].u16LenDataBlock)
                {
                    /* Get address of symbol within a RAM area */
                    pu8RAMSymbol = EED_rastDataBlocksAddress[enDataBlock].pu8AdrRamData + u32SymbolAddress;
                    /* Copy new value into RAM area */
                    _memcpy(pu8RAMSymbol, pvNewValue, u16ArraySize);
                    /* Block state shall still be Locked */
                    EED_astDataBlocks[enDataBlock].enBlockStatus = EED_nLocked;
                    /* Set return value */
                    boRet = TRUE;
                }
            }
        }
    }

    /* Enable all maskable interrupts */
    OSAPI_UnlockSchedule();

    return boRet;

}

/***********************************************************************
*  Name        : EED_IoDeInit
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EED_IoDeInit(ERR_TYPE enRetError)
{
    if(enRetError==ERR_OK)
    {
        if(EED_IsJobPending()==TRUE)
        {
            RequestIO();
        }
        else {}
    }
    else {}
}

/***********************************************************************
*  Name        : EED_IoInit
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EED_IoInit(ERR_TYPE enRetError)
{

    EED_tenJobState enJobState; /* Return value of the job queue */
    BOOL isOK=TRUE;

    if(enRetError!=ERR_OK)
    {
        EEO_ReleaseIO();
        /*  TODO: handle queue job*/
        return;
    }

    /* Get a job from the queue */
    enJobState = EED_GetJob(&EED_stCurrentJob);

    /* Check if a job is pending and get job to be processed */
    if(enJobState == EED__nOk)
    {
        switch(EED_stCurrentJob.enOperation)
        {
            case EED__nenJobOperationRead:
                /* Set state of data block */
                /* Initiate the upload of the data block from EEPROM */
                isOK=EEO_ReadBlock(EED_rastDataBlocksAddress[EED_stCurrentJob.enBlock].u16AdrEepRomData,
                                   EED_rastDataBlocksAddress[EED_stCurrentJob.enBlock].pu8AdrRamData,
                                   EED_rastDataBlocksAddress[EED_stCurrentJob.enBlock].u16LenDataBlock
                                  );
                if(isOK==TRUE)
                {
                    EED_astDataBlocks[EED_stCurrentJob.enBlock].enBlockStatus = EED_nUploadRunning;
                }
                break;
            case EED__nenJobOperationWrite:
                /* Set state of data block  */
                isOK=EEO_WriteBlock(EED_rastDataBlocksAddress[EED_stCurrentJob.enBlock].u16AdrEepRomData,
                                    EED_rastDataBlocksAddress[EED_stCurrentJob.enBlock].pu8AdrRamData,
                                    EED_rastDataBlocksAddress[EED_stCurrentJob.enBlock].u16LenDataBlock
                                   );
                if(isOK==TRUE)
                {
                    EED_astDataBlocks[EED_stCurrentJob.enBlock].enBlockStatus = EED_nDownloadRunning;
                }

                break;
            case EED__nenJobOperationIdle:
                /* Nothing to do */
                EEO_ReleaseIO();
                break;
            default:
                /* Nothing to do */
                EEO_ReleaseIO();
                break;
        }

        if(isOK==FALSE)
        {
            EED_InsertHeadJob(&EED_stCurrentJob);
            RequestIO();
        }
    }
    else
    {
        /* Nothing to do */
        EEO_ReleaseIO();
    }
}


/***********************************************************************
*  Name        : EED_IoOK
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EED_IoOK(void)
{
    /* Handle the job */
    HandleIO(ERR_OK);
    if(EED_IsJobPending()==TRUE)
    {
        RequestIO();
    }
    else
    {
        /* Nothing to do */
        EEO_ReleaseIO();
    }
}


/***********************************************************************
*  Name        : EED_IoError
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void EED_IoError(ERR_TYPE enRetError)
{
    /* Handle the job */
    HandleIO(enRetError);
    if(EED_IsJobPending()==TRUE)
    {
        RequestIO();
    }
    else
    {
        /* Nothing to do */
        EEO_ReleaseIO();
    }
}


/***********************************************************************
*  Name        : EED_GetLastBlockError
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL  EED_GetLastBlockError(EED_tenDataBlockID enDataBlock,  ERR_TYPE* const penError)
{

    BOOL boRet = FALSE; /* Return value */


    /* Disable all maskable interrupts */
    OSAPI_LockSchedule();

    /* Check for valid block */
    if(enDataBlock < EED_nLastBlock)
    {
        /* Get the last block error */
        *penError = EED_astDataBlocks[enDataBlock].enLastIOError;
        /* Set return value */
        boRet = TRUE;
    }

    /* Enable all maskable interrupts */
    OSAPI_UnlockSchedule();

    return boRet;

}



/***********************************************************************
*  Name        : EED_Normalvoltage
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void   EED_Normalvoltage(void)
{
    /******************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    ******************************************************************************/
    BOOL boJobProcessing = FALSE; /* Flag to indicate if a job is currently processed. */
    BOOL boJobsQueued = FALSE; /* Flag to indicate if jobs are already queued. */

    /******************************************************************************
    * FUNCTION CODE
    ******************************************************************************/
    /* Disable all maskable interrupts */
    OSAPI_LockSchedule();
    /* Set flag to indicate normal power condition. */
    EED_boNormalVoltage = TRUE;
    /* Check if a job is currently processed */
    if(EED_stCurrentJob.enOperation != EED__nenJobOperationIdle)
    {
        /* A job is currently processed and should not be disturbed by a new Request. */
        boJobProcessing = TRUE;
    }
    else
    {
        /* Check if jobs are already queued */
        boJobsQueued = EED_IsJobPending();
    }
    /* Enable all maskable interrupts */
    OSAPI_UnlockSchedule();

    /* Check if the processing of jobs must be resumed after an undervoltage power condition. */
    if((boJobsQueued == TRUE) && (boJobProcessing == FALSE))
    {
        /* Start up/download. No jobs are currently processed, but there are jobs in the queue which
          can now be processed. */
        RequestIO();
    }
    else
    {
        /* Jobs are already processed and/or no jobs are queued,
         so do not request IOQHA again. */
    }


}


/***********************************************************************
*  Name        : EED_Undervoltage
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void   EED_Undervoltage(void)
{
    /* Disable all maskable interrupts */
    OSAPI_LockSchedule();
    /* Set flag to indicate undervoltage power condition. */
    EED_boNormalVoltage = FALSE;
    /* Enable all maskable interrupts */
    OSAPI_UnlockSchedule();

}


/***********************************************************************
*  Name        : HandleIO
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void HandleIO(ERR_TYPE enRetError)
{

    BOOL boIsCheckSumOk;  /* Variable for checking the state of the checksum calculation */
    BOOL boCorruptedBlock = FALSE;  /* Flag to indicate if a uploaded block is corrupted
                                    and the default data shall be downloaded at once */

    /* Check what to do with the last job operation */
    switch(EED_stCurrentJob.enOperation)
    {
        case EED__nenJobOperationRead:
            /* Reset last IO error */
            EED_astDataBlocks[EED_stCurrentJob.enBlock].enLastIOError = enRetError;
            /* Check for error during IO operation */
            if(enRetError == ERR_OK)
            {
                /* In case of IoOk call the checksum calculation */
                /* Check consistency of data block */
                if(EED_astDataBlocks[EED_stCurrentJob.enBlock].boPerfomChecksum == TRUE)
                {
                    boIsCheckSumOk = PerformChecksumCheck(EED_stCurrentJob.enBlock);
                }
                else
                {
                    /* Set default to true to skip check for corrupted data block */
                    boIsCheckSumOk = TRUE;
                }
            }
            else
            {
                /* In case of IoError indicate the data block as corrupted */
                boIsCheckSumOk = FALSE;
            }
            /* Check for corrupted data block */
            if(boIsCheckSumOk == FALSE)
            {
                /* Uploaded Data block is corrupted. */
                /* Load default data from ROM. */
                _memcpy(EED_rastDataBlocksAddress[EED_stCurrentJob.enBlock].pu8AdrRamData,
                        EED_rastDataBlocksAddress[EED_stCurrentJob.enBlock].pu8AdrRomData,
                        EED_rastDataBlocksAddress[EED_stCurrentJob.enBlock].u16LenDataBlock);

                if(EED_astDataBlocks[EED_stCurrentJob.enBlock].boPerfomChecksum == TRUE)
                {
                    /* Calculate the checksum of the Data Block in RAM */
                    SetChecksum(EED_stCurrentJob.enBlock);
                }
                /* Data block is to be downloaded */
                EED_astDataBlocks[EED_stCurrentJob.enBlock].enBlockStatus = EED_nDownloadRunning;
                /* Set up the operation */
                EED_stCurrentJob.enOperation = EED__nenJobOperationWrite;
                /* Request current job for download */
                EED_InsertHeadJob(&EED_stCurrentJob);

                /* Signal that the attributes of the corrupted block shall not be processed within this interface. */
                boCorruptedBlock = TRUE;
            }
            else
            {
                /* Set state of data block */
                EED_astDataBlocks[EED_stCurrentJob.enBlock].enBlockStatus = EED_nConsistent;
            }
            /* Check if an uploaded block is corrupted. The data block is now is queued for a download, so
               do not process the data block's attributes. */
            if(boCorruptedBlock == FALSE)
            {
                /* Check if application is to be notified. */
                if(EED_rastDataBlocksAddress[EED_stCurrentJob.enBlock].vCallback != 0x0)
                {
                    /* Notify application that data block is available. */
                    EED_rastDataBlocksAddress[EED_stCurrentJob.enBlock].vCallback((U16)EED_stCurrentJob.enBlock,
                            EED_astDataBlocks[EED_stCurrentJob.enBlock].enLastIOError);
                }

                /* Check if an event is to be sent */
                if(EED_stCurrentJob.enNotifiyResource != 0x0u)
                {
                    /* Upload of a NVRAMRes is completed */
                    SysEvt_SetEvent((U8)EED_stCurrentJob.enNotifiyResource);
                    EED_stCurrentJob.enNotifiyResource=0;
                }
            }

            /* Disable all maskable interrupts */
            OSAPI_LockSchedule();
            /* Reset current job */
            EED_stCurrentJob.enOperation = EED__nenJobOperationIdle;
            OSAPI_UnlockSchedule();

            break;
        case EED__nenJobOperationWrite:
            /* Reset last IO error */
            EED_astDataBlocks[EED_stCurrentJob.enBlock].enLastIOError = enRetError;

            /* Check for error during IO operation */
            if(enRetError == ERR_OK)
            {
                /* Set state of downloaded data block. Needed when data block
                   is downloaded via interface EED_SaveDataBlock  */
                EED_astDataBlocks[EED_stCurrentJob.enBlock].enBlockStatus = EED_nConsistent;
            }
            else
            {
                /* Set state of downloaded data block. Needed when data block
                   is downloaded via interface EED_SaveDataBlock  */
                EED_astDataBlocks[EED_stCurrentJob.enBlock].enBlockStatus = EED_nConsistentNotSaved;
            }


            /* Disable all maskable interrupts */
            OSAPI_LockSchedule();
            /* Reset current job */
            EED_stCurrentJob.enOperation = EED__nenJobOperationIdle;
            OSAPI_UnlockSchedule();

            /* Check if application is to be notified. */
            if(EED_rastDataBlocksAddress[EED_stCurrentJob.enBlock].vCallback != NULL)
            {
                /* Notify application that data block is available. */
                EED_rastDataBlocksAddress[EED_stCurrentJob.enBlock].vCallback((U16)EED_stCurrentJob.enBlock,
                        EED_astDataBlocks[EED_stCurrentJob.enBlock].enLastIOError);
            }

            /* Check if an event is to be sent */
            if(EED_stCurrentJob.enNotifiyResource != 0x0u)
            {
                /* Upload of a NVRAMRes is completed */
                SysEvt_SetEvent((U8)EED_stCurrentJob.enNotifiyResource);
            }

            break;
        case EED__nenJobOperationIdle:
            break;
        default:
            break;
    }

}

/***********************************************************************
*  Name        : RequestIO
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL RequestIO(void)
{
    BOOL boNormalVoltage = FALSE;   /* Flag to indicate the state of Normal Power Condtion */
    BOOL bRet = FALSE;

    /* Disable all maskable interrupts */
    OSAPI_LockSchedule();
    /* Store power state flag in Stack variable for reason of reentrancy. */
    boNormalVoltage = EED_boNormalVoltage;
    /* Enable all maskable interrupts */
    OSAPI_UnlockSchedule();

    /* Check the power condition */
    if(boNormalVoltage == TRUE)
    {
        /* Normal power condition */
        bRet=EEO_RequestIO();
    }
    else
    {
        /* Undervoltage power condition */
        /* Nothing to do */
    }
    return bRet;
}


#define ChecksumInitialValue 0xA55A
/***********************************************************************
*  Name        : MakeChechsum
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL MakeChechsum(U8* bufben, U16 len, U16* pchecksum)
{
    U16 tempsum=0u;
    U16 i=0u;
    if((bufben==NULL)||(pchecksum==NULL)) return FALSE;

    for(i=0u; i<len; i++)
    {
        tempsum+=bufben[i];
    }
    *pchecksum+=tempsum;
    return TRUE;
}

/***********************************************************************
*  Name        : QueueDataBlock
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL QueueDataBlock(EED_tenDataBlockID enDataBlock)
{
    BOOL boRet = FALSE; /* Return value of the interface */
    EED_tstJob stJob;         /* Job to be performed */

    OSAPI_LockSchedule();
    /* Check for valid block */
    if(enDataBlock < EED_nLastBlock)
    {

        /* Check for correct state of Download data block */
        if(EED_astDataBlocks[enDataBlock].enBlockStatus == EED_nConsistentNotSaved)
        {
            if(EED_astDataBlocks[enDataBlock].boPerfomChecksum == TRUE)
            {
                /* Calculate the checksum of the Data Block in RAM */
                SetChecksum(enDataBlock);
            }

            /* Data block is to be downloaded */
            EED_astDataBlocks[enDataBlock].enBlockStatus = EED_nDownloadRunning;
            /* Set up the job */
            stJob.enOperation = EED__nenJobOperationWrite;
            stJob.enBlock = enDataBlock;
            stJob.enNotifiyResource=0u;
            /* Put job into queue */
            EED_PutJob(&stJob);
            /* Set return value */
            boRet = TRUE;
        }
    }
    OSAPI_UnlockSchedule();

    return boRet;

}

/*TODO:  change CRC*/
/***********************************************************************
*  Name        : PerformChecksumCheck
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL PerformChecksumCheck(EED_tenDataBlockID enDataBlock)
{

    U8*  u8AdrDataBlock;         /* Numerical start Address of the data block in RAM area */
    U16  u16Calcsum;             /* Return value of FCRC_boMakeCRC */
    U16  u16Ramsum;      /* Checksum of data block in RAM  */
    U16  u16Len;             /* Length of data block */
    U16  u16LenWithoutsum;               /* Length of data block without CRC-16 */
    U8*    pu8AdrSum;            /* Address of the CRC in RAM area */
    BOOL boRet = FALSE;                  /* Return value*/

    /* Disable all maskable interrupts */
    OSAPI_LockSchedule();

    /* Check for valid block */
    if(enDataBlock < EED_nLastBlock)
    {
        /* Get the length information of the Data Block loaded into RAM */
        u16Len = EED_rastDataBlocksAddress[enDataBlock].u16LenDataBlock;
        u16LenWithoutsum = u16Len - ((U16)sizeof(U16)); /* Exclude Checksum field */

        /* Address the checksum of the Data Block loaded into RAM */
        pu8AdrSum = EED_rastDataBlocksAddress[enDataBlock].pu8AdrRamData + u16LenWithoutsum;
        /* Get the checksum of the Data Block in RAM */
        _memcpy((U8*)&u16Ramsum, pu8AdrSum, (U16)sizeof(U16)) ;

        /* Set initial CRC value */
        u16Calcsum = ChecksumInitialValue;
        /* Assign the RAM address to an integer variable, because FCRC writes back the last checked address */
        u8AdrDataBlock = EED_rastDataBlocksAddress[enDataBlock].pu8AdrRamData;
        /* Calculate the checksum of the Data Block in RAM */
        boRet=MakeChechsum(u8AdrDataBlock,u16LenWithoutsum,&u16Calcsum);
        if(boRet == TRUE)
        {
            /* Compare stored with calculated checksum */
            if(u16Ramsum != u16Calcsum)
            {
                /* Wrong checksum */
                boRet = FALSE;
            }
            else
            {
                /* Right checksum */
                boRet = TRUE;
            }
        }
        else
        {
            /* Shall not happen, because the checksum shall be calculated within one function call. */
            /* Wrong checksum */
            boRet = FALSE;
        }

    }
    else
    {
        /* Invalid data block */
        boRet = FALSE;
    }

    /* Enable all maskable interrupts */
    OSAPI_UnlockSchedule();

    return boRet;

}


/***********************************************************************
*  Name        : SetChecksum
*  Description : None
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SetChecksum(EED_tenDataBlockID enDataBlock)
{
    U8* u8AdrDataBlock;          /* Numerical start Address of the data block in RAM area */
    U16  u16Calcsum;             /* Return value of FCRC_boMakeCRC */
    U16  u16Len;             /* Length of data block */
    U16  u16LenWithoutsum;               /* Length of data block without CRC-16 */
    U8* pu8RamAdr;           /* Pointer to checksum in RAM */
    BOOL boRet = FALSE;                  /* Return value of FRCR interface */


    /* Get the length information of the Data Block loaded into RAM */
    u16Len = EED_rastDataBlocksAddress[enDataBlock].u16LenDataBlock;
    u16LenWithoutsum = u16Len - ((U16)sizeof(U16)); /* Exclude Checksum field */

    /* Address the location of the checksum in RAM */
    pu8RamAdr = EED_rastDataBlocksAddress[enDataBlock].pu8AdrRamData + u16LenWithoutsum;

    /* Set initial CRC value */
    u16Calcsum = ChecksumInitialValue;
    /* Assign the RAM address to an integer variable, because FCRC writes back the last checked address */
    u8AdrDataBlock = EED_rastDataBlocksAddress[enDataBlock].pu8AdrRamData;
    /* Calculate the checksum of the Data Block in RAM */
    /*boRet = FCRC_boMakeCRC( &u32AdrDataBlock, u16LenWithoutCRC, &u16CalcCRC, u16LenWithoutCRC );*/
    boRet= MakeChechsum(u8AdrDataBlock,u16LenWithoutsum,&u16Calcsum);
    if(boRet == TRUE)
    {
        /* Store the checksum of the Data Block in RAM */
        _memcpy(pu8RamAdr, (U8*)&u16Calcsum, (U16)sizeof(U16)) ;
    }
    else
    {
        /* Shall not happen, because the checksum shall be calculated within one function call. */
        /* Wrong checksum */
        u16Calcsum = 0xFFFFu;
        _memcpy(pu8RamAdr, (U8*)&u16Calcsum, (U16)sizeof(U16)) ;
    }

}

/**************** END OF FILE *****************************************/


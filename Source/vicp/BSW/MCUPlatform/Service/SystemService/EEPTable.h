/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                         *
*   AUTHOR     :                                       *
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   : Implementation of the EEPROM Download Handler (EED)
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
*-----------------------------------------------------------------------
* 0.3    Jan 24,2017   ZhangJie   Remove unused include file.
*-----------------------------------------------------------------------
* 0.4    Mar 17,2017 Pei Jingli   Fix headfile.
*=====================================================================*/
#ifndef _EEPTABLE_H_
#define _EEPTABLE_H_
#include "EEPTable_Cfg.h"

/**
 * Description: EED_stAddressData describes the memory locations of data block.
 * 1) EEPROM for data changed during operation in the field or new configuraton at the end of line production
 * 2) ROM for default data in case EEPROM data could not be loaded or is corrupt
 * 3) RAM as a data mirror of the ROM or EEPROM data to speed up read/write access to the data.
 * Elements:
 * pu8AdrRomData: Address of the default data block in ROM ( address is assigned by linker )
 * pu8AdrRamData: Address of the copied data block in RAM ( address is assigned by linker )
 * u16AdrEepRomData:  Address of the data block in EEPROM ( assigned by EEPROM-Database )
 * u16LenDataBlock: Length of the data block (defined by EEPROM-Database )
 * pstTableJob: Pointer to a Table-Job to use TransferArea-Mechanism of EET
 * vCallback: Notify the application in after an IO operation completes.
*/
struct EED_stAddressData
{
    U8*  pu8AdrRomData;
    U8*  pu8AdrRamData;
    U16  u16AdrEepRomData;
    U16  u16LenDataBlock;
    /*EET_tstTable*  pstTableJob;*/
    void (*vCallback)(U16 BlockId,ERR_TYPE type);
};

typedef struct EED_stAddressData  EED_tstAddressData;

/**
 * Description: States of a data block
 * Elements:
 * EED_nEmpty: Data block is not loaded into RAM
 * EED_nUploadRunning: Data block is currently loaded from EEPROM into RAM
 * EED_nConsistent: Data block is loaded into RAM
 * EED_nLocked: Data block is locked to indicate that the data could be change
 * EED_nConsistentNotSaved: Data of the data block has been change
 * EED_nDownloadRunning: Data block is currently downloaded from RAM into EEPROM
*/
enum EED_enDataBlockStatus
{
    EED_nEmpty,
    EED_nUploadRunning,
    EED_nConsistent,
    EED_nLocked,
    EED_nConsistentNotSaved,
    EED_nDownloadRunning,
    EED_nInvalidBlock
};
typedef enum EED_enDataBlockStatus EED_tenDataBlockStatus;

/**
 * Description: EED_stDataBlock describes a data block.
 * Elements:
 * enBlockStatus: Status of the data block ( states of enumeration EED_tenDataBlockStatus )
 * enLastIOError: Error value of the last IO operation
 * boPerfomChecksum: True - Verfify Checksum, False - Do not verify checksum
 *    Note: When boPerfomChecksum is set to true, the data block must provide the memory at its end
 *           for storing the CRC checksum
*/
struct EED_stDataBlock
{
    EED_tenDataBlockStatus enBlockStatus;
    ERR_TYPE enLastIOError;
    BOOL boPerfomChecksum;
};

typedef struct EED_stDataBlock  EED_tstDataBlock;

/**
 * Description: Indicates that data blocks have to be uploaded
 * Values:      1
*/
#define EED__nUpload        ((U8)1)

/**
 * Description: Indicates that data blocks have to be downloaded
 * Values:      0
*/
#define EED__nDownload  ((U8)0)

/**
 * EED__tenJobOperation: State of a queued job
 * Elements:
 * EED__nenJobOperationIdle: No job is to be processed
 * EED__nenJobOperationRead: Read operation is to be performed
 * EED__nenJobOperationWrite: Write operation is to be performed
 */
enum EED_enJobOperation
{
    EED__nenJobOperationIdle,
    EED__nenJobOperationRead,
    EED__nenJobOperationWrite
};
typedef enum EED_enJobOperation EED_tenJobOperation;


/**
 * EED_tenJobState: Return values of the jobqueue interfaces
 * Elements:
 * EED__nOk: Success
 * EED__nQueueEmpty: No jobs queued
 * EED__nQueueFull: The job queue is full
 * EED__nAlreadyRequesetd: The data block of the job to be queued is already requested
 */
enum EED_enJobState
{
    EED__nOk,
    EED__nQueueEmpty,
    EED__nQueueFull,
    EED__nAlreadyRequesetd,
};
typedef enum EED_enJobState EED_tenJobState;


/**
 * Description: EED_stJob describes a job to be processed on a data block.
 * Elements:
 * enBlock:  Data Block to be processed
 * enJobOperation: Operation to be performed on data block
 * enNotifiyResource: Notification event that resource is available
 * enReq: Central state hanlder that SM is not longer needed
*/
struct EED_stJob
{
    EED_tenDataBlockID  enBlock;
    EED_tenJobOperation enOperation;
    U32                 enNotifiyResource;
};

typedef struct EED_stJob    EED_tstJob;
typedef struct EED_stJob*   EED_ptstJob;

enum
{
    EED_STARTUP,
    EED_RAM1,
    EED_RAM2,
    EED_RAM_NUMB
};

void EED_Reset(void);
void EED_Init(void);
void EED_Deinit(void);
BOOL EED_LockDataBlock(EED_tenDataBlockID enDataBlock);
BOOL EED_UnlockDataBlock(EED_tenDataBlockID enDataBlock);
BOOL EED_SaveDataBlock(EED_tenDataBlockID enDataBlock);
BOOL EED_UnlockAndSavDataBlock(EED_tenDataBlockID enDataBlock);
EED_tenDataBlockStatus EED_GetDataBlockState(EED_tenDataBlockID enDataBlock);
BOOL EED_ModifyBitData(EED_tenDataBlockID enDataBlock, U32 u32SymbolAddress,
                       U8 u8BitPosition, U8 u8BitSize, U8 u8NewValue);
BOOL EED_ModifyByteData(EED_tenDataBlockID enDataBlock, U32 u32SymbolAddress,
                        U8 u8ByteSizeOfElement, U8 u8NumElements, void* pvNewValue);
BOOL EED_GetLastBlockError(EED_tenDataBlockID enDataBlock, ERR_TYPE* const penError);
extern void   EED_Normalvoltage(void);
extern void   EED_Undervoltage(void);
BOOL EED_MarkNVRamResource(U8 u8NVRAMRes, U32 Event,U8 u8JobOperation);

#endif /*_EEPTABLE_H_*/

/****************************** END OF FILE ***************************/


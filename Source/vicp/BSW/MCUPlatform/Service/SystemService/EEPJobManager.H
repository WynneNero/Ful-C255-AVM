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
* 0.1          Jun 11,2016                  Init version.
*------------------------------------------------------------------------
* 0.2          Jan 11,2017  ZhangJie  Add u for constant value to avoid Coverity warning.
* ----------------------------------------------------------------------
* 0.3          Jan 24,2017   ZhangJie   Remove unused include file.
*=====================================================================*/
#ifndef _EEPJOBMANAGER_H_
#define _EEPJOBMANAGER_H_ 

/**** Definition of constants ****/

/**** Definition of macros ****/

/* Publish Information */
#define EEO_VENDOR_ID (1U) /* Provide module vendor identification. */ 
#define EEO_MODULE_ID (0x0201U) /* Provide module identification. */ 
#define EEO_INSTANCE_ID (0U) /* Specifies the instance id of this module instance. */
#define EEO_SW_MAJOR_VERSION (1U) /* The EEP driver's major version. */
#define EEO_SW_MINOR_VERSION (0U) /* The EEP driver's minor version. */
#define EEO_SW_PATCH_VERSION (0U) /* The EEP driver's patch version. */
#define EEO_SA_MAJOR_VERSION (1U) /* The SAIL major release version. */
#define EEO_SA_MINOR_VERSION (0U) /* The SAIL minor release version. */
#define EEO_SA_PATCH_VERSION (0U) /* The SAIL patch release version. */

/* Service IDs */
#define EEO_INIT_SERVICE_ID  				0x00u
#define EEO_WRITE_BLOCK_SERVICE_ID 			0x02u
#define EEO_READ_BLOCK_SERVICE_ID 			0x03u
#define EEO_GET_STATE_SERVICE_ID 			0x04u
#define EEO_CLEAR_PROTECT_SERVICE_ID		0x05u
#define EEO_SET_PROTECT_SERVICE_ID			0x06u
#define EEO_SET_MODE_SERVICE_ID				0x07u
/* Parameter error ids*/
#define EEO_E_UNINIT	   			0x10u /* has not initialized */
#define EEO_E_ALREADY_INITIALIZED	0x11u /* access address is out of address range */
#define EEO_E_INVALID_ADDRESS		0x12u
#define EEO_E_PARAM_CONFIG			0x13u /* configure pointer is null */
#define EEO_E_PARAM_POINTER	   		0x14u /* data pointer is null*/
#define EEO_E_PARAM_LENGTH			0x15u /* data length is zero */
#define EEO_E_WRITE_PROTECT	    	0x16u /* the write address is in protect arrange*/
#define EEO_E_JOB_FAILED			0x17u /* access failed*/
#define EEO_E_ACCESS_BUSY			0x18u /* the eeprom driver is busy in other job*/


/* Definition of  type macros  */


/* eeprom driver module state */
typedef enum
{
	EEO_UNINIT,			/* Eeprom driver module has not initialized */
	EEO_IDLE,			/* Eeprom driver module initialized and not in transmit mode */
	EEO_BUSY,			/* Eeprom driver module is in transmit mode */
	EEO_EEROR,
}EEO_StateType;


/* eeprom access type */
typedef enum
{
	EEO_NOACTION,
	EEO_READ,					   /* read action */
	EEO_WRITE,					   /* write action */
	EEO_REQUESTBUS,
	EEO_REQUESTBUS_BACK,	
	EEO_RELEASEBUS,
	EEO_RELEASEBUS_BACK,	
}EEO_AccessType;

/* eeprom configure definition */
typedef struct
{
	U16 EepromSize;		/* Eeprom device memory size */
	U16 ProAddrBegin;   /* Eeprom memory protect arrange begin */
	U16 ProAddrEnd;		/* Eeprom memory protect arrange end*/
	U8 Eep_WBlockLen;
	U8 ReadWaitTime;
	U8 WriteWaitTime;
}EEO_ConfigType;

/* Eeprom access job state */
typedef enum
{ 
	EEO_JOB_OK,					  /* the job is idle or finished */
	EEO_JOB_READ,				  /* the job is on read period */
    	EEO_JOB_READ_CONTINUE,		
    	EEO_JOB_WRITE,				  /* the access job is on write period*/
    	EEO_JOB_WRITE_CONTINUE,	
	EEO_JOB_FAILED,				  /* the access job fail and abort */
}EEO_JobStateType;

/* Eeprom access handle structrue definition */
typedef struct
{
	U16 StartAddr;	 			/* the start addres for this lock */
	U8 *DataPtr;		 			/* the block data pointer */
	U16 TotalLen;				      /* the total length of data block*/
	U16 RWLen;				      /* the RW length of data block*/	
	EEO_AccessType AccMode;					/* the current access mode of this block */
	EEO_JobStateType JobState;				/* the current stata this block */
	U8 RetryNum;							/* repeat times for this block */
}EEO_HandleType;

typedef struct
{
	EEO_StateType State;
	EEO_ConfigType* Config;
	EEO_HandleType *const Handle;	
}EEO_GlobalType;

/*******************************************************************************************
* EXPORT INTERFACE FUNCTION PROTOTYPES
*
* In this section declare
* - all system global function prototypes of your module. This is a copy of the function 
*   definitions without the header template.
********************************************************************************************/

/* Eep_Init */
/*******************************************************************************************
* Author: Kevin Liao, HVAC SO, 
* Description of Behaviour:	 Eeprom driver module initialization
*
* Parameters:	ConfigPtr, spi module initialized struct.													 
*
* Return Value  (Value Typ Range):	 none
*   
********************************************************************************************/
extern void EEO_Init(void);
extern void EEO_DeInit(void);

#if (EEO_PROTECT_RANGE_RESET_API == STD_ON)
/* Eep_SetProtectRange */
/*******************************************************************************************
* Author: Kevin Liao, HVAC SO, 
* Description of Behaviour:
* 	reset the eeprom device write protect address range with parameter.
*
* Parameters: StartAdd: Eep_AddressType.should be in the eeprom address arrange. 
* 	Size: Eep_DataLength, can not be more than the eeprom size.
*
* Return Value  (Value Typ Range): return E_OK if reset was accepted,or return E_NOT_OK if 
*								   it was rejected.
*   
********************************************************************************************/
extern BOOL EEO_SetProtectRange(U16 StartAdd, U16 Size);

/* Eep_ClearProtectRange */
/*******************************************************************************************
* Author: Kevin Liao, HVAC SO, 
* Description of Behaviour:
* clear the eeprom device write protect address range.after that, no protect area has left.
*
* Parameters:
* None. 
*
* Return Value  (Value Typ Range):
* None
*   
********************************************************************************************/
extern void EEO_ClearProtectRange(void);
#endif /* EEO_PROTECT_RANGE_RESET_API */

/* Eep_GetState */
/*******************************************************************************************
* Author: Kevin Liao, HVAC SO, 
* Description of Behaviour:
* return the eeprom driver state.
*
* Parameters: None
* Return Value  (Value Typ Range): EEO_StateType value.
*  
********************************************************************************************/
extern EEO_StateType EEO_GetState(void);
extern BOOL EEO_GetBusStatus(void);
extern BOOL EEO_RequestIO( void);
extern BOOL EEO_ReleaseIO(void);


/* Eep_ReadBlock */
/*******************************************************************************************
* Author: Kevin Liao, HVAC SO, 
* Description of Behaviour:
* Read a block of data from the eeprom device in the specified address.
*
* Parameters: Addr: Eep_AddressType.the read data  in the eeprom source address.
*		      DataPtr: Eep_DataType, the read data receive address.
* 			  Len: Eep_DataLength, the read data length.
*
* Return Value  (Value Typ Range): return TRUE if the read block was implement ok;
*									otherwise return FALSE. 
*   
********************************************************************************************/
extern BOOL EEO_ReadBlock(U16 Addr, U8* DataPtr, U16 Len);

/* Eep_WriteBlock */
/*******************************************************************************************
* Author: Kevin Liao, HVAC SO, 
* Description of Behaviour:
* write a block of data to the eeprom device in the specified address.
*
* Parameters: Addr: Eep_AddressType.the write data destination in the eeprom address.
*		      DataPtr: Eep_DataType, the write data source address.
* 			  Len: Eep_DataLength, the write data length.
*
* Return Value  (Value Typ Range): return TRUE if the write block was implement ok;
*									otherwise return FALSE. 
*   
********************************************************************************************/
extern BOOL EEO_WriteBlock(U16 Addr, U8* DataPtr, U16 Len);

/* Eep_DirectReadBlock */
/*******************************************************************************************
* Author: Kevin Liao, HVAC SO, 
* Description of Behaviour:
* write a block of data to the eeprom device in the specified address.
*
* Parameters: Addr: Eep_AddressType.the write data destination in the eeprom address.
*		      DataPtr: Eep_DataType, the write data source address.
* 			  Len: Eep_DataLength, the write data length.
*
* Return Value  (Value Typ Range): return TRUE if the write block was implement ok;
*									otherwise return FALSE. 
*   
********************************************************************************************/
extern BOOL EEO_DirectReadBlock(U16 Addr, U8* DataPtr, U16 Len);

/* Eep_DirectWriteBlock */
/*******************************************************************************************
* Author: Kevin Liao, HVAC SO, 
* Description of Behaviour:
* write a block of data to the eeprom device in the specified address.
*
* Parameters: Addr: Eep_AddressType.the write data destination in the eeprom address.
*		      DataPtr: Eep_DataType, the write data source address.
* 			  Len: Eep_DataLength, the write data length.
*
* Return Value  (Value Typ Range): return TRUE if the write block was implement ok;
*									otherwise return FALSE. 
*   
********************************************************************************************/
extern BOOL EEO_DirectWriteBlock(U16 Addr, U8* DataPtr, U16 Len);

#endif /*_EEPJOBMANAGER_H_*/

/****************************** END OF FILE ***************************/


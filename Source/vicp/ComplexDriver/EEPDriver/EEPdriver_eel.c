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
------------------------------------------------------------------------
* 0.1	   Sep 20,2016  PEI Jingli  Initial version
------------------------------------------------------------------------
* 0.2	   Sep 26,2016  PEI Jingli  Modify struct defination of EEL
*----------------------------------------------------------------------
* 0.3         Dec 20,2016   ShangQiuju Remove unused include files.
*----------------------------------------------------------------------
* 0.4         Dec 26,2016   ShangQiuju Update Fdl read write interface for word len parameter.
*------------------------------------------------------------------------
* 0.5        Jan 13,2017  ZhangJie  Fix Coverity warnings.
*-----------------------------------------------------------------------
* 0.6   	 Jan 24,2017    ZhangJie     Remove unused include headfile.
*-----------------------------------------------------------------------
* 0.7   	 Feb 14,2017    ShangQiuju     read write remove from hal to hal_block to add address parameter.
*-----------------------------------------------------------------------
* 0.8       Mar 17,2017    Pei Jingli      Changed start-up processing of eel for pool full errors.Fix multi-returns warning.
*-----------------------------------------------------------------------
* 0.9       Mar 29,2017    Pei Jingli      Fix blocksize erased in FDL write.
*------------------------------------------------------------------------
* 1.0       Apr 01,2017   PEI Jingli  Fix headfile included.
*------------------------------------------------------------------------
* 1.1       Apr 07,2017   PEI Jingli  Fix fdl writing error.
*=====================================================================*/
#include "EEPTable.h"
#include "EEPdriver_eel.h"
#include "EEPTable_Cfg.h"

#include "R_TypeDefs.h"
#include "r_fdl.h"
#include "R_EEL.h"
#include "EEPDriver_IF.h"
#include "cpu.h"
#include "EEPJobManager.h"

/* to initialize sampleApp_eelConfig_enu  */
extern const EED_tstAddressData EED_rastDataBlocksAddress[];

static r_eel_status_t FDL2EEL_Init( void );
/* EEPRDCYCL addr=0xFFC5A010
Read access time= (4+number of EEPRDCYCL)x2/CPU freq  */
#define FlashAccess_Enable() { \
                                                   (*(CPU_REG08  *)0xFFC5A010u) = 0x0Fu; \
                                                }

/*********************************************************************************************************************
 * FDL descriptor variable definition
 *********************************************************************************************************************/
/**< FDL descriptor structure */
const r_fdl_descriptor_t  fdlConfig_enu = 
{
    CPU_FREQUENCY_MHZ,      /**< CPU frequency in MHz */                  
    FDL_POOL_SIZE,          /**< Number of Data Flash blocks, accessible by the FDL.
                                 Typically no. of available Data Flash blocks */   
    EEL_POOL_START,         /**< 1st block of the EEL pool */                                  
    EEL_POOL_SIZE           /**< Number of blocks in the EEL pool */        
};  

/*********************************************************************************************************************
 * EEL descriptor variable definitions
 *********************************************************************************************************************/
/**< ROM ID-L table definition.
     * Descriptor table containing data set identifier and data set length
     *ID, greater than 0   len, 16-bit length in bytes */
r_eel_ds_cfg_t IDLTab_astr[EEL_CONFIG_IDX_NUM];

/**< RAM ID-X table definition */
uint16_t         IDXTab_au16[EEL_CONFIG_IDX_NUM];/* [sizeof (IDLTab_astr) / sizeof (r_eel_ds_cfg_t) ];*/

/**<  EEL decriptor structure */
r_eel_descriptor_t  sampleApp_eelConfig_enu = 
{
    EEL_CONFIG_VBLK_SIZE,                           /**< Virtual block size (# physical Flash blocks) */
    EEL_CONFIG_VBLK_CNT_REFRESH_THRESHOLD,          /**< threshold for minimum no. of prepared blocks */
    &(IDLTab_astr[0]),                              /**< pointer to the ID-L table in ROM */
    &(IDXTab_au16[0]),                              /**< pointer to the ID-X table in RAM */
    EEL_CONFIG_IDX_NUM, /** (sizeof(IDLTab_astr) / sizeof(r_eel_ds_cfg_t)), < number of table entries */     
    EEL_CONFIG_ERASE_SUSPEND_THRESHOLD              /**< threshold for erase suspend */
};

/**< use less for EEL */
EEO_ConfigType EEPDriver_ConfigData=
{
  EEL_CONFIG_IDX_NUM, 0u, 0u, 255u, 0u , 0u
};

/***********************************************************************
*  Name        : FDL2EEL_Init
    function to initialize and start of the EEL operation.
    At functions end the EEL has passed the startup processing so far, that either limited access
    is possible (See documentation) or an error has occurred. 
    
    Note: 
    In this simple application sample the startup processing is forwarded by continuous handler 
    function call. So, the function execution time will be long

    @param[in]  req         pointer to the operations request structure
    
   Returns     operations status return (OK, warning or error)
***********************************************************************/
r_eel_status_t FDL2EEL_Init( void )
{
    r_eel_status_t                eelRet=R_EEL_OK;
    r_eel_driver_status_t      driverStatus;
    r_fdl_request_t               req;
    U8 index      =0u;
    
    /* 1st initialize the FDL */
    if( R_FDL_OK != R_FDL_Init( &fdlConfig_enu ))
    {   
        /* Error handler */
        eelRet= R_EEL_ERR_CONFIGURATION;
    }
    else
    {
        /* Prepare the environment */
        req.command_enu     = R_FDL_CMD_PREPARE_ENV;
        req.idx_u32         = 0u;
        req.cnt_u16         = 0u;
        req.accessType_enu  = R_FDL_ACCESS_NONE;
        R_FDL_Execute( &req );
        while( R_FDL_BUSY == req.status_enu )
        {
            R_FDL_Handler();
        }
        if( R_FDL_OK != req.status_enu )
        {   
            /* Error handler */
            eelRet= R_EEL_ERR_CONFIGURATION;
        }
        else /* Next initialize the EEL */
        {
            for(index=0u; index<(U8)EEL_CONFIG_IDX_NUM; index++)
            {
                IDLTab_astr[index].ID_u16=(uint16_t)EED_rastDataBlocksAddress[index].u16AdrEepRomData+1u;
                IDLTab_astr[index].len_u16=(uint16_t)EED_rastDataBlocksAddress[index].u16LenDataBlock;
            }
            eelRet = R_EEL_Init( &sampleApp_eelConfig_enu, R_EEL_OPERATION_MODE_NORMAL );
            if((U8)eelRet>=R_EEL_ERR)
            {                
            }
            else
            {
                eelRet = R_EEL_Startup();
                if((U8)eelRet>=R_EEL_ERR)
                {
                }
                else
                {
                    do
                    {
                        R_EEL_Handler();
                        R_EEL_GetDriverStatus( &driverStatus );
                    }
                    /* Wait until early read/write is possible (or error) */
                    while(   ( R_EEL_OPERATION_STARTUP == driverStatus.operationStatus_enu )
                           &&( R_EEL_ACCESS_LOCKED     == driverStatus.accessStatus_enu) );

                    eelRet =driverStatus.backgroundStatus_enu;
                }
            }
        }
    }
    
    return eelRet;
}

/***********************************************************************
*  Name        : EEPdriver_Init
*  Description : Init driver, do initialization and start-up.        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EEPdriver_Init(void)
{
    r_eel_request_t    myReq;
    r_eel_status_t      reqStat;
    r_eel_driver_status_t     driverStatus;
    BOOL   bRet= FALSE;

    /* Initialize the data FLash is required to be able to access the data Flash. */
    FlashAccess_Enable();

    /* ------------------------------------------------------------------------------------------
      EEL Initialization
      Here we wait until the EEL has at least partly access. Startup processing has not yet 
      ended
     ------------------------------------------------------------------------------------------ */
    reqStat = FDL2EEL_Init();
  
  /* Here we expect:
    driverStatus.operationStatus_enu  = R_EEL_OPERATION_STARTUP
  & driverStatus.accessStatus_enu     = R_EEL_ACCESS_READ_WRITE
  & driverStatus.backgroundStatus_enu = R_EEL_OK
  
  Possible error cases are:
    driverStatus.operationStatus_enu  = R_EEL_OPERATION_STARTUP
  & driverStatus.accessStatus_enu     = R_EEL_ACCESS_READ_WRITE
  & driverStatus.backgroundStatus_enu = a warning
  
    driverStatus.operationStatus_enu  = R_EEL_OPERATION_PASSIVE
  & driverStatus.accessStatus_enu     = R_EEL_ACCESS_LOCKED
  & driverStatus.backgroundStatus_enu = an error
  */
  
  /* For debug purpose we can react on an inconsistent pool with format. In the 
     final application, this ought to be avoided as all data is destroyed in the Data Flash */
  if( R_EEL_ERR_POOL_INCONSISTENT == (U8)reqStat )
  {    
      myReq.command_enu = R_EEL_CMD_FORMAT;
      R_EEL_Execute( &myReq );
      /* Wait until operation end */
      while( R_EEL_BUSY == myReq.status_enu )
      {
          R_EEL_Handler();
      }

      reqStat =myReq.status_enu;
      if((U8)myReq.status_enu>=R_EEL_ERR)           /* Return value check */
      {}
      else
      { /* Format procedure ends with EEL re-init */      
          reqStat = FDL2EEL_Init();
      }
  }
  
  /* Error check of startup processing (with and without Format) */
  if((U8)reqStat<R_EEL_ERR)    
  {
       /* Wait for fully operational and access unlock */
       do
       {
           R_EEL_Handler();   //executed R_EEL_Handler() state by state
           R_EEL_GetDriverStatus( &driverStatus );
       }
       /* Wait until the system is completely up and running (or error) */
       while( R_EEL_OPERATION_STARTUP == driverStatus.operationStatus_enu );
       if((U8)driverStatus.backgroundStatus_enu<R_EEL_ERR)    
            bRet =TRUE;
    }
    
  return bRet;
}

/***********************************************************************
*  Name        : EEPdriver_DeInit
*  Description : 
*  Parameter   : None
*  Returns     : None
***********************************************************************/
BOOL EEPdriver_DeInit(void)
{
  /*SHUTDOWN*/
  /*RESTART*/
    return TRUE;
}

/***********************************************************************
*  Name        : EEPdriver_Write
*  Description : less than one page write        
*  Parameter   : DSid,  ID of data sets
*      length , no used here, EEPDriver_ConfigData.len_u16 of bytes will be written.
*      write_buffe,r  start address of data to write
*  Returns     : None
***********************************************************************/
BOOL EEPdriver_Write(U16 DSid,U8 length, U8* write_buffer)
{
  r_eel_request_t           myReq;
  r_eel_driver_status_t      driverStatus;
  BOOL bRet =FALSE;

  if(write_buffer==NULL)
  {}
  else
  {  
    myReq.address_pu08 = (uint8_t*)(write_buffer);
    myReq.identifier_u16 = DSid+1u; /* 1 to 0xfffe, serviceID+1*/
    myReq.command_enu = R_EEL_CMD_WRITE;
    R_EEL_Execute( &myReq );
    /* Wait until operation end */
    if(R_EEL_BUSY == myReq.status_enu)
    {
        do
        {
            R_EEL_Handler();
            R_EEL_GetDriverStatus(&driverStatus);
            if(R_EEL_ERR_POOL_FULL == myReq.status_enu)
            {             
                break;
            } 
        }while( (R_EEL_BUSY == myReq.status_enu)||(R_EEL_OPERATION_BUSY==driverStatus.operationStatus_enu) );
    }
  
    if( R_EEL_ERR > (U8)myReq.status_enu )
    {
        /* If the status is a warning only, we might ignore it */
        bRet =TRUE;
    }
    else
    {
        /* Error handler */
    }
  }
  
  return bRet;
}

/***********************************************************************
*  Name        : EEPdriver_Read
*  Description : Read datas of EEL       
*  Parameter   : address,  ID of eel
*      length , bytes of data to be read                
*      read_buffer,  start address of data to be stored
*  Returns     : None
***********************************************************************/
BOOL EEPdriver_Read(U16 DSid,U8 length, U8* read_buffer)
{
    r_eel_request_t           myReq;
    r_eel_driver_status_t     driverStatus;
    BOOL bRet =FALSE;
    
    if(read_buffer==NULL)
    {}
    else
    {  
        myReq.address_pu08 = (uint8_t*)(read_buffer);
        myReq.identifier_u16 = DSid+1u; /* 1 to 0xfffe, serviceID+1*/
        myReq.length_u16 = length;
        myReq.offset_u16 = 0u;
        myReq.command_enu = R_EEL_CMD_READ;
        R_EEL_Execute( &myReq );
        /* Wait until operation end */
        if(R_EEL_BUSY == myReq.status_enu)
        {
            do
            {
                R_EEL_Handler();
                R_EEL_GetDriverStatus(&driverStatus);
            }while( (R_EEL_BUSY == myReq.status_enu) ||(R_EEL_OPERATION_BUSY==driverStatus.operationStatus_enu) );
        }
      
        if( R_EEL_ERR > (U8)myReq.status_enu )
        {
            /* If the status is a warning only, we might ignore it */
            bRet =TRUE;
        }
        else
        {
            /* Error handler */
        }
    }
    
    return bRet;
}

/***********************************************************************
*  Name        : FDLDriver_Write
*  Description : Only can be used for upgrade flag.
*  Parameter   : 
*  Returns     : None
***********************************************************************/
U8 FDLDriver_Write(U32 address , U8* buffer, U16 wordNum)
{
    ERR_TYPE ret = ERR_FAULT;
    U16 blocksize = (wordNum/16u);
    U8 datalen = (U8)(wordNum&0xffu);
    U16 addr = (U16)address;
    U16 blockid = address/EEL_VIRTUALBLOCK_LEN;
    if(wordNum%16u)
        blocksize +=1;
    if(((address%EEL_VIRTUALBLOCK_LEN+(wordNum*4u)%EEL_VIRTUALBLOCK_LEN)>EEL_VIRTUALBLOCK_LEN)
    ||(((address%EEL_VIRTUALBLOCK_LEN)>0u)&&(wordNum%16u==0u)))
        blocksize +=1;
        
    if(FDdriver_EraseDirect(blockid,blocksize))
    {
        if(FDdriver_WriteDirect(addr, datalen, (U32*)(buffer)))  
            ret = ERR_OK;
    }
    return (U8)ret;    
}

/***********************************************************************
*  Name        : FDdriver_BlackCheck
*  Description : Init driver        
*  Parameter   : address, offset address of DATAFLASH_BASE_ADDR,*be 4 byte align
*      length , words of data to be write            
*      write_buffer,  start address of data to be stored
*  Returns     : None
***********************************************************************/
BOOL FDdriver_BlackCheck(U16 address,U8 length)
{
	  r_fdl_request_t			req;
	  BOOL bRet =FALSE;
	
	if((length==0u)||((address%4u)!=0u)||(address>=(FDL_POOL_SIZE*EEL_VIRTUALBLOCK_LEN)) ||((address+length)>=(FDL_POOL_SIZE*EEL_VIRTUALBLOCK_LEN)) /*valid fdl*/
	  ||((address>=(EEL_POOL_START*EEL_VIRTUALBLOCK_LEN))&&(address<=((EEL_POOL_START+EEL_POOL_SIZE)*EEL_VIRTUALBLOCK_LEN))))  /*not be eel*/
	  {
	  /* parameter error */
	  }
	  else
	  {
		req.command_enu 	= R_FDL_CMD_BLANKCHECK;
		req.idx_u32 		= address;
		req.cnt_u16 		= length;  /* number of words*/
		req.accessType_enu	= R_FDL_ACCESS_USER;
		R_FDL_Execute( &req );
		while( R_FDL_BUSY == req.status_enu )
		{
			R_FDL_Handler();
		}
		if( R_FDL_OK == req.status_enu )
		{	
			bRet =TRUE;
		}
		else
		{
			/* Error handler */
		}
	  }
	  
	  return bRet;
}

/***********************************************************************
*  Name        : FDLDriver_Read
*  Description : Only can be used for upgrade flag.
*  Parameter   : 
*  Returns     : None
***********************************************************************/
U8 FDLDriver_Read( U32 address ,U8* buffer, U16 wordNum)
{
    U8 rlen = 0;
    U8 tLength = (U8)(wordNum&0xFFu);
    U16 addr = (U16)address;
    if(FDdriver_ReadDirect(addr, tLength, (U32*)(buffer)))
    {
        rlen = (U8)wordNum;
    }
    return rlen;
}

/***********************************************************************
*  Name        : EEPDriver_WriteDirect
*  Description : Init driver        
*  Parameter   : address, offset address of DATAFLASH_BASE_ADDR,*be 4 byte align
*      length , words of data to be write            
*      write_buffer,  start address of data to be stored
*  Returns     : None
***********************************************************************/
BOOL FDdriver_WriteDirect(U16 address,U8 length, U32* write_buffer)
{
    r_fdl_request_t           req;
    BOOL bRet =FALSE;

  if((length==0u)||(write_buffer==NULL) ||((address%4u)!=0u)||(address>=(FDL_POOL_SIZE*EEL_VIRTUALBLOCK_LEN)) ||((address+length)>=(FDL_POOL_SIZE*EEL_VIRTUALBLOCK_LEN)) /*valid fdl*/
    ||((address>=(EEL_POOL_START*EEL_VIRTUALBLOCK_LEN))&&(address<=((EEL_POOL_START+EEL_POOL_SIZE)*EEL_VIRTUALBLOCK_LEN))))  /*not be eel*/
    {
    /* parameter error */
    }
    else
    {
    /* -----------------------------------------------------------------------
       Write data:
       addresses 0x00000000 - 0x0000001F
       ----------------------------------------------------------------------- */   
      req.command_enu     = R_FDL_CMD_WRITE;
      req.idx_u32         = address;
      req.cnt_u16         = length;  /* number of words*/
      req.bufAddr_u32     = (uint32_t)( write_buffer);
      req.accessType_enu  = R_FDL_ACCESS_USER;
      R_FDL_Execute( &req );
      while( R_FDL_BUSY == req.status_enu )
      {
          R_FDL_Handler();
      }
      if( R_FDL_OK == req.status_enu )
      {   
          bRet =TRUE;
      }
      else
      {
          /* Error handler */
      }
    }
    
    return bRet;
}

/***********************************************************************
*  Name        : EEPDriver_ReadDirect
*  Description : Init driver        
*  Parameter   : address,  offset address of DATAFLASH_BASE_ADDR,*be 4 byte align
*      length , bytes of data to be read,*be multiple of 4*.                
*      read_buffer,  start address of data to be stored
*  Returns     : None
***********************************************************************/
BOOL FDdriver_ReadDirect(U16 address,U8 length, U32* read_buffer)
{
    r_fdl_request_t           req;
    BOOL bRet =FALSE;

  if((length==0u) ||(read_buffer==NULL)||((address%4u)!=0u)||(address>=(FDL_POOL_SIZE*EEL_VIRTUALBLOCK_LEN)) ||((address+length)>=(FDL_POOL_SIZE*EEL_VIRTUALBLOCK_LEN)) /*valid fdl*/
    ||((address>=(EEL_POOL_START*EEL_VIRTUALBLOCK_LEN))&&(address<=((EEL_POOL_START+EEL_POOL_SIZE)*EEL_VIRTUALBLOCK_LEN))))  /*not be eel*/
    {
    /* parameter error */
    }
    else
    {
      req.command_enu     = R_FDL_CMD_READ;
      req.idx_u32         = address;
      req.cnt_u16         = length;  /* number of words*/
      req.bufAddr_u32 = (uint32_t)( read_buffer);
      req.accessType_enu  = R_FDL_ACCESS_USER;
      R_FDL_Execute( &req );
      while( R_FDL_BUSY == req.status_enu )
      {
          R_FDL_Handler();
      }
      if( R_FDL_OK == req.status_enu )
      {   
          bRet =TRUE;
      }
      else
      {
          /* Error handler */
      }
    }
    
    return bRet;
}

/***********************************************************************
*  Name        : EEPDriver_EraseDirect
*  Description :       
*  Parameter   : blockId,  =direct address/EEL_VIRTUALBLOCK_LEN
*      Cnt , number of blocks to be erased                
*  Returns     : None
***********************************************************************/
BOOL FDdriver_EraseDirect(U16 blockId, U16 Cnt)
{
    r_fdl_request_t           req;
    BOOL bRet =FALSE;
    if((Cnt==0u) ||(blockId>=FDL_POOL_SIZE) /*valid fdl*/
    ||((blockId>=EEL_POOL_START)&&(blockId<=(EEL_POOL_START+EEL_POOL_SIZE))))  /*to be eel*/
    {
    /* parameter error */
    }
    else
    {
        req.command_enu     = R_FDL_CMD_ERASE;
        req.idx_u32         = blockId; /* block id*/
        req.cnt_u16         = Cnt;
        req.accessType_enu  = R_FDL_ACCESS_USER;
        R_FDL_Execute( &req );
        
        while( R_FDL_BUSY == req.status_enu )
        {
            R_FDL_Handler();
        }
        if( R_FDL_OK == req.status_enu )
        {   
            bRet =TRUE;
        }
        else
        {
            /* Error handler */
        }
    }
    
    return bRet;
}

/***********************************************************************
*  Name        : FDLDriver_Write_Upgrade_flag
*  Description : Only can be used for upgrade flag.
*  Parameter   : 
*  Returns     : None
***********************************************************************/
U8 FDLDriver_Write_Upgrade_flag( U8* buffer, U16 Len)
{
    ERR_TYPE ret = ERR_FAULT;
    U8 blocksize = Len/64 + 1;
    U8 datalen = (U8)(Len&0xff);
    if(FDdriver_EraseDirect(0,blocksize))
    {
        if(FDdriver_WriteDirect(UPGRADE_FLAG_ADDRESS, datalen, (U32*)(buffer)))  
            ret = ERR_OK;
    }

    return ret;    
}

/***********************************************************************
*  Name        : FDLDriver_Read
*  Description : Only can be used for upgrade flag.
*  Parameter   : 
*  Returns     : None
***********************************************************************/
U8 FDLDriver_Read_Upgrade_flag( U8* buffer, U16 Len)
{
    U8 rlen = 1; // xjy_bug  （R_FDL_FCUFct_ReadOperation）/* Clear ECC errors */ is closed by xjy.   so if read dataflash will  report R_FDL_ERR_ECC_DED 
	//U8 rlen = 0;
    if(FDdriver_ReadDirect(UPGRADE_FLAG_ADDRESS, (U8)Len, (U32*)(buffer)))  // so it return is flase but the data read is true
    {
        rlen = (U8)Len;
    }
    return rlen;
}


/**************** END OF FILE *****************************************/


/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE: Data Flash driver for NEC 1022 32bit
*-----------------------------------------------------------------------------
  .FILE:FLS_Drv.c
  .AUTHOR:Tan, fumin
*-----------------------------------------------------------------------------

 Date        Author                       Change
 -----------------------------------------------------------------------------
2015.05.12  Tan, fumin		   :create this module
2016.12.14  Zhang, Jie         Add FDL function Read/Write data by bytes and write protection
2016.12.14  Zhang, Jie         Change the prefix and suffix array in function "FLS_u8WriteDataByByte" as the block to erase is based on 64 bytes.  
2016.12.14  Zhang, Jie         Solute the bug when read/write date from the middle of the block, and the length is less then the rest block data.
 
*****************************************************************************/

/************************************************************
internal data flash in 1022 layout:

Totall data flash size = 64byte/block  * 512 block = 32KBytes

erase times : 125k times for 20years retain
			250k times for 3years retain

BlockID 		Function Call Address			Physical address[abslute address]:

0			0xFF20 0000-0xFF20 003F[64 bytes]		
1			0xFF20 0040-0xFF20 007F[64 bytes]	

....			.......
511			0xFF20 7FC0-0xFF20 7FFF[64 bytes]	
			
************************************************************/


#include "General.h"

#include "Fdl_descriptor.h"
//#include "Fdl_types.h"
#include "bl_watchdog.h"
#include "FLS_Drv.h"

FLS_stFLS FLS_stCMD;

void _memcpy(uint8* dest, uint8* src, uint16 len)
{
    uint16 i=0;

    if((NULL!=dest)&&(NULL!=src))
    {
        for(; i<len; i++)
        {
            *dest=*src;
            dest++;
            src++;
        }
    }
}

/*****************************************************************************
 Function  : FLS_vCheckReady												 
 Description   : Check the EEPROM Write or Erase finish, this function MUST called in 
			 while(1)
			 {
			   FLS_vCheckReady();
			   //belowe is your task container or task frame
			 }						
 NOTE: eeprom need 250us for writting a byte/word or neen 14ms for erase a block. so we need check it
 	    to avoid for a long time wait!
 Return Value  : NULL														 
*****************************************************************************/
void FLS_vCheckReady(void)
{
	vpFun CallBack=NULL;
	
	if(FLS_GetThisCmd()==FLS_enCMD_WaitReady)
	{
		if(FLS_GetExpCmd()==FLS_enCMD_Write)
		{
			if(FLS_GetHandleResult()==R_FDL_BUSY)
			{
				R_FDL_Handler();
			}
			else
			{
				FLS_SetExpCmd(FLS_enCMD_Null);
				FLS_SetThisCmd(FLS_enCMD_Ready);
				FLS_CleanCmd();
				
				#if FLS_CallBackFunction_Enable
				if(FLS_GetCallBackFun())
				{
					CallBack=FLS_GetCallBackFun();
					FLS_ClearCallBackFun();
					CallBack();
				}
				#endif
			}
		}
		else if(FLS_GetExpCmd()==FLS_enCMD_Erase)
		{
			if(FLS_GetHandleResult()==R_FDL_BUSY)
			{
				R_FDL_Handler();
			}
			else
			{
				FLS_SetExpCmd(FLS_enCMD_Null);
				FLS_SetThisCmd(FLS_enCMD_Ready);
				FLS_CleanCmd();

				#if FLS_CallBackFunction_Enable
				if(FLS_GetCallBackFun())
				{
					CallBack=FLS_GetCallBackFun();
					FLS_ClearCallBackFun();
					CallBack();
				}
				#endif
			}
		}
	}
	#if FLS_CallBackFunction_Enable
	else if(FLS_GetThisCmd()==FLS_enCMD_DoCallBack)
	{
		FLS_SetThisCmd(FLS_enCMD_Ready);
		FLS_CleanCmd();
		
		if(FLS_GetCallBackFun())
		{
			CallBack=FLS_GetCallBackFun();
			FLS_ClearCallBackFun();
			CallBack();
		}
	}
	#endif
}

/*****************************************************************************
 Function  : FLS_vDrvInit												 
 Description   : Flash driver initialization, call this function when system reset						
 NOTE: NULL
 Return Value  : NULL														 
*****************************************************************************/
bl_Return_t  FLS_vDrvInit(void)
{
	FLS_SetThisCmd(FLS_enCMD_Ready);
	FLS_SetExpCmd(FLS_enCMD_Null);
	FLS_CleanCmd();
	
	FDL_Open();
	
	if( R_FDL_OK != R_FDL_Init( &sampleApp_fdlConfig_enu ) )
	{   
	    /* Error handler */
		DET_vErrReport(FLS_ERR_Init);
	}
	return BL_ERR_OK;

}

/*****************************************************************************
 Function  : FLS_vDrvExit												 
 Description   : Flash driver exit, call this function when system halt						
 NOTE: NULL
 Return Value  : NULL														 
*****************************************************************************/
bl_Return_t  FLS_vDrvExit(void)
{
	FLS_SetThisCmd(FLS_enCMD_Null);
	FLS_SetExpCmd(FLS_enCMD_Null);
	FLS_CleanCmd();
	return BL_ERR_OK;
	
//	FAL_Close();
}

/*****************************************************************************
 Function  : FLS_u8ReadData												 
 Description   : Read data from Flash, para list:
 
 			 FromFlashAddr: [it MUST be multiple of 2] the Flash address, range is 0x0000 to 2048 * BlockNumber(BLockNumber<=7)
 			 ToRamAddr: head of the data store in the RAM when data read out from EEPROM
 			 DataLen_Byte: [it MUST be multiple of 4] how many bytes read out from Flash,
 			 
 NOTE:Len of ToFlashAddr: 0xFF20 0000~0xFF20 7FFF
 Return Value  : 0 is OK and driver working on and load data finished
 			   1 is the driver is busy
 			   2 is address range is out 
 			   
 			   11 or 12 is the reading address data is a empty data(not write before!!)
 			   13 is flashdriver internal error
*****************************************************************************/
bl_Return_t  FLS_u8ReadDataWait(uint32 FromFlashAddr, uint32 DataLen_Byte,uint8 *ToRamAddr)
{	
	
	//r_fdl_status_t ret;
	if(FLS_GetThisCmd() !=FLS_enCMD_Ready)
	{
		DET_vErrReport(FLS_ERR_Busy);
		return FLS_ERR_Busy;
	}
		
	if(FromFlashAddr+DataLen_Byte>FLS_END_ADDR)
	{
		DET_vErrReport(FLS_ERR_OutOfRange);
		return FLS_ERR_OutOfRange;
	}
		
	if((DataLen_Byte<4) || (DataLen_Byte&3))
	{
		DET_vErrReport(FLS_ERR_Len);
		return FLS_ERR_Len;
	}
	
	/*convert to internal address*/
	FromFlashAddr-=FLS_BaseAddress;
	
	FLS_SetThisCmd(FLS_enCMD_Read);
	FLS_SetCurRamAddr(ToRamAddr);
	FLS_SetFlsAddr(FromFlashAddr);
	FLS_SetDataLenth(DataLen_Byte);
	
	FLS_CmdExe(R_FDL_CMD_READ);
	
	while( R_FDL_BUSY == FLS_GetHandleResult())
	{
	//	R_FDL_Handler(); ---not need run this function in read operation!!!
		//HAL_vWdtReset();
//		Wdg_Feed();
	}
	
	if( R_FDL_OK != FLS_GetHandleResult())
	{	
		/* Error handler */
		DET_vErrReport(FLS_GetHandleResult());
	}

	FLS_SetThisCmd(FLS_enCMD_Ready);
	FLS_CleanCmd();
	
	#if FLS_CallBackFunction_Enable
		if(FLS_GetCallBackFun())
		{
			FLS_SetThisCmd(FLS_enCMD_DoCallBack);
		}
		else
	#endif
		{
			FLS_SetThisCmd(FLS_enCMD_Ready);
		}

#if 0
	//FLS_GetHandleResult();
	if(0u != FLS_GetHandleResult())
	{
		ToRamAddr[0] = 0;
		ToRamAddr[1] = 0;
		ToRamAddr[2] = 0;
		ToRamAddr[3] = 0;
				
	}
#endif

	return  ((bl_Return_t)FLS_GetHandleResult());
}

/*****************************************************************************
 Function  : FLS_u8ReadDataByByte												 
 Description   : Read data from Flash, para list:
 
 			 FromFlashAddr: [it MUST be multiple of 2] the Flash address, range is 0x0000 to 2048 * BlockNumber(BLockNumber<=7)
 			 ToRamAddr: head of the data store in the RAM when data read out from EEPROM
 			 DataLen_Byte: [it MUST be multiple of 4] how many bytes read out from Flash,
 			 
 NOTE:Len of ToFlashAddr: 0xFF20 0000~0xFF20 7FFF
 Return Value  : 0 is OK and driver working on and load data finished
 			   1 is the driver is busy
 			   2 is address range is out 
 			   
 			   11 or 12 is the reading address data is a empty data(not write before!!)
 			   13 is flashdriver internal error
*****************************************************************************/
bl_Return_t  FLS_u8ReadDataByByte(uint32 FromFlashAddr, uint32 DataLen_Byte,uint8 *ToRamAddr)
{	
        uint8 rlen = 0;
        uint8 blocksize = 0;
        uint16 blockaddress = 0;
        uint16 Prefixaddress = 0;
        uint8 Prefixdata[4];
        uint8 Suffixdata[4];
        uint8 PrefixCnt = 0;
        uint8 SuffixCnt = 0;
        uint8 PrefixStartCnt = 0;
        bl_Return_t ret = BL_ERR_NOT_OK;
        
	//r_fdl_status_t ret;
	if(FLS_GetThisCmd() !=FLS_enCMD_Ready)
	{
		DET_vErrReport(FLS_ERR_Busy);
		return FLS_ERR_Busy;
	}
		
	if(FromFlashAddr+DataLen_Byte>FLS_END_ADDR)
	{
		DET_vErrReport(FLS_ERR_OutOfRange);
		return FLS_ERR_OutOfRange;
	}
	
	/*convert to internal address*/
	FromFlashAddr-=FLS_BaseAddress;
        if(DataLen_Byte == 0)
        {
            ret = BL_ERR_NOT_OK;
        }
        else
        {
            PrefixCnt = (FLS_Address_Size - (FromFlashAddr%FLS_Address_Size))%FLS_Address_Size;
            PrefixStartCnt = FLS_Address_Size -PrefixCnt;
            if(0==PrefixCnt)
            {
                Prefixaddress = 0;
                blockaddress = FromFlashAddr;
            }
            else
            {
                    Prefixaddress = 1;
                    blockaddress = (FromFlashAddr - (FLS_Address_Size -PrefixCnt));
                    if(DataLen_Byte <PrefixCnt)
                    {
                        PrefixCnt = DataLen_Byte;
                    }
                    FLS_SetThisCmd(FLS_enCMD_Read);
                    FLS_SetCurRamAddr(Prefixdata);
                    FLS_SetFlsAddr(blockaddress);
                    FLS_SetDataLenth(4);

                    FLS_CmdExe(R_FDL_CMD_READ);
                    while( R_FDL_BUSY == FLS_GetHandleResult())
                    {
                    }

                    if( R_FDL_OK != FLS_GetHandleResult())
                    {	
                    	/* Error handler */
                    	DET_vErrReport(FLS_GetHandleResult());
                    }

                    FLS_SetThisCmd(FLS_enCMD_Ready);
                    FLS_CleanCmd();
                    _memcpy(ToRamAddr,Prefixdata+PrefixStartCnt,PrefixCnt);
                    rlen += PrefixCnt;
            }

            SuffixCnt = (DataLen_Byte - PrefixCnt)%FLS_Address_Size;
            blocksize =((DataLen_Byte - PrefixCnt)/FLS_Address_Size);
            if(0 == blocksize)
            {
                 //Do nothing
            }
            else
            {
                    FLS_SetThisCmd(FLS_enCMD_Read);
                    FLS_SetCurRamAddr(ToRamAddr+PrefixCnt);
                    FLS_SetFlsAddr(blockaddress +(Prefixaddress*4));
                    FLS_SetDataLenth(blocksize*4);

                    FLS_CmdExe(R_FDL_CMD_READ);
                    while( R_FDL_BUSY == FLS_GetHandleResult())
                    {
                    }

                    if( R_FDL_OK != FLS_GetHandleResult())
                    {	
                    	/* Error handler */
                    	DET_vErrReport(FLS_GetHandleResult());
                    }

                    FLS_SetThisCmd(FLS_enCMD_Ready);
                    FLS_CleanCmd();
                     rlen += (blocksize*4);
            }
            
            if(0==SuffixCnt)
            {
                //Do nothing
            }
            else
            {
                   FLS_SetThisCmd(FLS_enCMD_Read);
                    FLS_SetCurRamAddr(Suffixdata);
                    FLS_SetFlsAddr(blockaddress+((blocksize+Prefixaddress)*4));
                    FLS_SetDataLenth(4);

                    FLS_CmdExe(R_FDL_CMD_READ);
                    while( R_FDL_BUSY == FLS_GetHandleResult())
                    {
                    }

                    if( R_FDL_OK != FLS_GetHandleResult())
                    {	
                    	/* Error handler */
                    	DET_vErrReport(FLS_GetHandleResult());
                    }

                    FLS_SetThisCmd(FLS_enCMD_Ready);
                    FLS_CleanCmd();
                    _memcpy(ToRamAddr+PrefixCnt+(blocksize*4),Suffixdata,SuffixCnt);
                    rlen += SuffixCnt;
            }
        
    	#if FLS_CallBackFunction_Enable
    		if(FLS_GetCallBackFun())
    		{
    			FLS_SetThisCmd(FLS_enCMD_DoCallBack);
    		}
    		else
    	#endif
    		{
    			FLS_SetThisCmd(FLS_enCMD_Ready);
    		}

#if 0
    	//FLS_GetHandleResult();
    	if(0u != FLS_GetHandleResult())
    	{
    		ToRamAddr[0] = 0;
    		ToRamAddr[1] = 0;
    		ToRamAddr[2] = 0;
    		ToRamAddr[3] = 0;
    				
    	}
#endif

            if(rlen == DataLen_Byte)
            {
                ret = BL_ERR_OK;
            }
            else
            {
                ret = BL_ERR_NOT_OK;
            }
        }
	return  ret;
}


/*****************************************************************************
 Function  : FLS_u8WriteData												 
 Description   : write data into Flash, para list:
 
 			 ToFlashAddr: [it MUST be multiple of 4]the Flash address
 			 FromRamAddr: head of the data store in the RAM which will be write into Flash
 			 DataLen_Byte: [it MUST be multiple of 4]how many bytes read out from Flash
 			 
 NOTE: you MUST erase before when you write the data into flash!
 	Len of ToFlashAddr: 0xFF20 0000~0xFF20 7FFF
 
 Return Value  : 0 is OK and driver working on
 			   1 is the driver is busy
			   2 is address range is out 
			   
			6 is driver is writting operation on going
			7 is writting address is written before, it need to erase then can be write!
			13 is flashdriver internal error
			
*****************************************************************************/
uint8 FLS_u8WriteData(uint32 ToFlashAddr, void *FromRam, uint16 DataLen_Byte)
{
	if(FLS_GetThisCmd() !=FLS_enCMD_Ready)
	{
		DET_vErrReport(FLS_ERR_Busy);
		return FLS_ERR_Busy;
	}
		
	if(ToFlashAddr+DataLen_Byte>FLS_END_ADDR)
	{
		DET_vErrReport(FLS_ERR_OutOfRange);
		return FLS_ERR_OutOfRange;
	}
		
	if((DataLen_Byte<4) || (DataLen_Byte&3))
	{
		DET_vErrReport(FLS_ERR_Len);
		return FLS_ERR_Len;
	}

	/*convert to internal address*/
	ToFlashAddr-=FLS_BaseAddress;

	FLS_SetThisCmd(FLS_enCMD_Write);
	FLS_SetCurRamAddr(FromRam);
	FLS_SetFlsAddr(ToFlashAddr);
	FLS_SetDataLenth(DataLen_Byte);
		
	FLS_CmdExe(R_FDL_CMD_WRITE);
	
	R_FDL_Handler();
	
	if( R_FDL_OK != FLS_GetHandleResult())
	{	
		/* Error handler */
		DET_vErrReport(FLS_GetHandleResult());
	}
	
	FLS_SetThisCmd(FLS_enCMD_WaitReady);
	FLS_SetExpCmd(FLS_enCMD_Write);
	
	return FLS_GetHandleResult();
}

/*****************************************************************************
 Function  : FLS_u8WriteData												 
 Description   : write data into Flash, para list:
 
 			 ToFlashAddr: [it MUST be multiple of 4]the Flash address
 			 FromRamAddr: head of the data store in the RAM which will be write into Flash
 			 DataLen_Byte: [it MUST be multiple of 4]how many bytes read out from Flash
 			 
 NOTE: you MUST erase before when you write the data into flash!
 
 Return Value  : 0 is OK and driver working on
 			   1 is the driver is busy
			   2 is address range is out
			   
			   6 is driver is writting operation on going
			   7 is writting address is written before, it need to erase then can be write!
			   13 is flashdriver internal error
			   
*****************************************************************************/

bl_Return_t FLS_u8WriteDataWait(uint32 ToFlashAddr, uint32 DataLen_Byte, const uint8 *FromRam)
{



	 FLS_u8EraseWait(ToFlashAddr,64u);

	if(FLS_GetThisCmd() !=FLS_enCMD_Ready)
	{
		DET_vErrReport(FLS_ERR_Busy);
		return FLS_ERR_Busy;
	}
		
	if(ToFlashAddr+DataLen_Byte>FLS_END_ADDR)
	{
		DET_vErrReport(FLS_ERR_OutOfRange);
		return FLS_ERR_OutOfRange;
	}
		
	if((DataLen_Byte<4) || (DataLen_Byte&3))
	{
		DET_vErrReport(FLS_ERR_Len);
		return FLS_ERR_Len;
	}

	/*convert to internal address*/
	ToFlashAddr-=FLS_BaseAddress;

	FLS_SetThisCmd(FLS_enCMD_Write);
	FLS_SetCurRamAddr(FromRam);
	FLS_SetFlsAddr(ToFlashAddr);
	FLS_SetDataLenth(DataLen_Byte);
		
	FLS_CmdExe(R_FDL_CMD_WRITE);
	
	while( R_FDL_BUSY == FLS_GetHandleResult())
	{
		R_FDL_Handler();
		//HAL_vWdtReset();
		//Wdg_Feed();/*Lin tao enable feed dog 20160601*/
	}
	
	if( R_FDL_OK != FLS_GetHandleResult())
	{	
		/* Error handler */
		DET_vErrReport(FLS_GetHandleResult());
	}
	
	FLS_SetThisCmd(FLS_enCMD_Ready);
	FLS_CleanCmd();
	
	return ((bl_Return_t)FLS_GetHandleResult());
}

/*****************************************************************************
 Function  : FLS_u8WriteDataByByte												 
 Description   : write data into Flash, para list:
 
 			 ToFlashAddr: [it MUST be multiple of 4]the Flash address
 			 FromRamAddr: head of the data store in the RAM which will be write into Flash
 			 DataLen_Byte: [it MUST be multiple of 4]how many bytes read out from Flash
 			 
 NOTE: you MUST erase before when you write the data into flash!
 
 Return Value  : 0 is OK and driver working on
 			   1 is the driver is busy
			   2 is address range is out
			   
			   6 is driver is writting operation on going
			   7 is writting address is written before, it need to erase then can be write!
			   13 is flashdriver internal error
			   
*****************************************************************************/

bl_Return_t FLS_u8WriteDataByByte(uint32 ToFlashAddr, uint32 DataLen_Byte, const uint8 *FromRam)
{
        uint8 rlen = 0;
        uint8 blocksize = 0;
        uint16 blockaddress = 0;
        uint16 Prefixaddress = 0;
        uint8 Prefixdata[64];
        uint8 Suffixdata[64];
        uint8 PrefixCnt = 0;
        uint8 SuffixCnt = 0;
        uint8 PrefixStartCnt = 0;
        bl_Return_t ret = BL_ERR_NOT_OK;


    if(FLS_GetThisCmd() !=FLS_enCMD_Ready)
	{
		DET_vErrReport(FLS_ERR_Busy);
		return FLS_ERR_Busy;
	}
		
	if(ToFlashAddr+DataLen_Byte>FLS_END_ADDR)
	{
		DET_vErrReport(FLS_ERR_OutOfRange);
		return FLS_ERR_OutOfRange;
	}

        /*convert to internal address*/
	ToFlashAddr-=FLS_BaseAddress;
        if(DataLen_Byte == 0)
        {
            ret= DataLen_Byte;
        }
        else
        {
        PrefixCnt = (FLS_Block_Size - (ToFlashAddr%FLS_Block_Size))%FLS_Block_Size;
        PrefixStartCnt = FLS_Block_Size - PrefixCnt;
        if(0==PrefixCnt)
        {
            Prefixaddress = 0;
            blockaddress = ToFlashAddr;
        }
        else
        {
            Prefixaddress = 1;
            blockaddress = (ToFlashAddr - (FLS_Block_Size - PrefixCnt));
            if(DataLen_Byte <PrefixCnt)
            {
                PrefixCnt = DataLen_Byte;
            }
            if(FLS_u8ReadDataByByte(blockaddress+FLS_BaseAddress, (uint32)64u, (uint32*)(Prefixdata)) == BL_ERR_OK)
            {
                _memcpy(Prefixdata+PrefixStartCnt,(void *)FromRam,PrefixCnt);
                FLS_u8EraseWait(blockaddress+FLS_BaseAddress,64u);

                FLS_SetThisCmd(FLS_enCMD_Write);
                FLS_SetCurRamAddr(Prefixdata);
                FLS_SetFlsAddr(blockaddress);
                FLS_SetDataLenth(64u);
                	
                FLS_CmdExe(R_FDL_CMD_WRITE);

                while( R_FDL_BUSY == FLS_GetHandleResult())
                {
                	R_FDL_Handler();
                }

                if( R_FDL_OK != FLS_GetHandleResult())
                {	
                	DET_vErrReport(FLS_GetHandleResult());
                }

                FLS_SetThisCmd(FLS_enCMD_Ready);
                FLS_CleanCmd();
                rlen += PrefixCnt;
                }
        }
        SuffixCnt = (DataLen_Byte - PrefixCnt)%FLS_Block_Size;
        blocksize =((DataLen_Byte - PrefixCnt)/FLS_Block_Size);
	 if(0==SuffixCnt)
        {
            //Do nothing
        }
        else
        {
            if(FLS_u8ReadDataByByte(blockaddress+((blocksize+Prefixaddress)*FLS_Block_Size)+FLS_BaseAddress, (uint8)64u, (uint32*)(Suffixdata)) == BL_ERR_OK)
            {
                _memcpy(Suffixdata,(void *)(FromRam+PrefixCnt+(blocksize*64)),SuffixCnt);
                FLS_u8EraseWait(blockaddress+((blocksize+Prefixaddress)*FLS_Block_Size)+FLS_BaseAddress,64u);

                FLS_SetThisCmd(FLS_enCMD_Write);
                FLS_SetCurRamAddr(Suffixdata);
                FLS_SetFlsAddr(blockaddress+((blocksize+Prefixaddress)*FLS_Block_Size));
                FLS_SetDataLenth(64u);
                	
                FLS_CmdExe(R_FDL_CMD_WRITE);

                while( R_FDL_BUSY == FLS_GetHandleResult())
                {
                	R_FDL_Handler();
                	//HAL_vWdtReset();
                	//Wdg_Feed();/*Lin tao enable feed dog 20160601*/
                }

                if( R_FDL_OK != FLS_GetHandleResult())
                {	
                	/* Error handler */
                	DET_vErrReport(FLS_GetHandleResult());
                }

                FLS_SetThisCmd(FLS_enCMD_Ready);
                FLS_CleanCmd();
                rlen += SuffixCnt;
            }
        }
        if(rlen == PrefixCnt+SuffixCnt)
        {
            if(0==blocksize)
            {
                //Do nothing
            }
            else
            {
                FLS_u8EraseWait(blockaddress+(Prefixaddress*FLS_Block_Size)+FLS_BaseAddress,64u);

                FLS_SetThisCmd(FLS_enCMD_Write);
                FLS_SetCurRamAddr(FromRam+PrefixCnt);
                FLS_SetFlsAddr(blockaddress+(Prefixaddress*FLS_Block_Size));
                FLS_SetDataLenth(blocksize*64);
                	
                FLS_CmdExe(R_FDL_CMD_WRITE);

                while( R_FDL_BUSY == FLS_GetHandleResult())
                {
                	R_FDL_Handler();
                	//HAL_vWdtReset();
                	//Wdg_Feed();/*Lin tao enable feed dog 20160601*/
                }

                if( R_FDL_OK != FLS_GetHandleResult())
                {	
                	/* Error handler */
                	DET_vErrReport(FLS_GetHandleResult());
                }

                FLS_SetThisCmd(FLS_enCMD_Ready);
                FLS_CleanCmd();
                ret = BL_ERR_OK;
            }
        }
        }
	return ret;
}


/*****************************************************************************
 Function  : FLS_u8Erase												 
 Description   : erase the flash, all the flash data set to 0xffffffff, para list:
 
 			 FlsAddr: [it MUST be multiple of 64]the Flash address, then this function will erase the block data
 			 DataLen_Byte: how many data space to be erased
 NOTE: NULL
 Return Value  : 0 is OK and driver working on
 			   1 is the driver is busy
			   2 is address range is out 
*****************************************************************************/
uint8 FLS_u8Erase(uint32 FlsAddr,uint16 DataLen_Byte)
{
	if(FLS_GetThisCmd() !=FLS_enCMD_Ready) 
		return FLS_ERR_Busy;
	if(FlsAddr>FLS_END_ADDR ||FlsAddr< FLS_BaseAddress)
		return FLS_ERR_OutOfRange;
		
	/*if the first address is not first address of the block,or
		data lenth is not the size of one block size, then will not erase!*/
	if((FlsAddr & (FLS_Block_Size-1)) || (DataLen_Byte & (FLS_Block_Size-1)))
		return FLS_ERR_Address;
		
	/*convert address to block ID*/
	FlsAddr-=FLS_BaseAddress;
	FlsAddr/=FLS_Block_Size;
	/*set operation block ID*/
	FLS_SetFlsAddr(FlsAddr);
	
	/*convert data lenth to block number*/
	DataLen_Byte/=FLS_Block_Size;
	FLS_stCMD.InOutData.cnt_u16=	DataLen_Byte;
	
	FLS_SetThisCmd(FLS_enCMD_Erase);

	FLS_CmdExe(R_FDL_CMD_ERASE);
	
	R_FDL_Handler();
	
	FLS_SetThisCmd(FLS_enCMD_WaitReady);
	FLS_SetExpCmd(FLS_enCMD_Erase);
	
	return FLS_ERR_NULL;
}

/*****************************************************************************
 Function  : FLS_u8Erase												 
 Description   : erase the flash, all the flash data set to 0xffffffff, para list:
 
 			 FlsAddr: [it MUST be multiple of 64]the Flash address, then this function will erase the block data
 			 DataLen_Byte: how many data space to be erased
 			 
 NOTE: NULL
 Return Value  : 0 is OK and driver working on
 			   1 is the driver is busy
			   2 is address range is out
			   4 is erase error
*****************************************************************************/
uint8 FLS_u8EraseWait(uint32 FlsAddr,uint16 DataLen_Byte)
{
	if(FLS_GetThisCmd() !=FLS_enCMD_Ready) 
		return FLS_ERR_Busy;
	if(FlsAddr>FLS_END_ADDR ||FlsAddr< FLS_BaseAddress)
		return FLS_ERR_OutOfRange;
		
	/*if the first address is not first address of the block,or
		data lenth is not the size of one block size, then will not erase!*/
	if((FlsAddr & (FLS_Block_Size-1)) || (DataLen_Byte & (FLS_Block_Size-1)))
		return FLS_ERR_Address;
		
	/*convert address to block ID*/
	FlsAddr-=FLS_BaseAddress;
	FlsAddr/=FLS_Block_Size;
	/*set operation block ID*/
	FLS_SetFlsAddr(FlsAddr);
	
	/*convert data lenth to block number*/
	DataLen_Byte/=FLS_Block_Size;
	FLS_stCMD.InOutData.cnt_u16=	DataLen_Byte;
	
	FLS_SetThisCmd(FLS_enCMD_Erase);

	FLS_CmdExe(R_FDL_CMD_ERASE);
	
	while(FLS_GetHandleResult()==R_FDL_BUSY)
	{
		R_FDL_Handler();
		//HAL_vWdtReset();
		//Wdg_Feed();/*lin tao enable feed dog*/
	}
	
	FLS_SetThisCmd(FLS_enCMD_Ready);
	FLS_SetExpCmd(FLS_enCMD_Null);
	
	return FLS_GetHandleResult();
}



/*****************************************************************************
 Function  : FLS_u8SetCallBackFun												 
 Description   : Set the Flash driver what to do when it finish its work!
 NOTE: NULL
 Return Value  : NULL
*****************************************************************************/
uint8 FLS_u8SetCallBackFun(vpFun vpfFinishFunction)
{
	#if FLS_CallBackFunction_Enable
	if(FLS_GetThisCmd()==FLS_enCMD_Ready)
	{
		FLS_vSetCallBackFun(vpfFinishFunction);
		
		return FLS_ERR_NULL;
	}
	else
	{
		return FLS_GetThisCmd();
	}
	#else
		return FLS_ERR_NULL;
	#endif
}

/*****************************************************************************
 Function  : EEP_u8GetSatus												 
 Description   : check EEPROM driver status						
 NOTE: NULL
 Return Value  : driver current satus														 
*****************************************************************************/
uint8 FLS_u8GetSatus(void)
{
	return FLS_GetThisCmd();
}

void FLS_vSetCallBackFun(vpFun Function)
{
	FLS_stCMD.CallBack=Function;
}



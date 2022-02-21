/*  BEGIN_FILE_HDR
************************************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information contained in this 
*   doc should not be reproduced, or used, or disclosed without the written authorization from 
*   HiRain Technologies.
************************************************************************************************
*   File Name       : Fls.c
************************************************************************************************
*   Project/Product : Bootloader
*   Title           : Fls driver module Source File
*   Author          : ning.chen
************************************************************************************************
*   Description     : This module is his flash driver used for Bootloader
*
************************************************************************************************
*   Limitations     : Only for Bootloader
*                     
*
************************************************************************************************
*
************************************************************************************************
*   Revision History:
* 
*   Version     Date          Initials          CR#         Descriptions
*   ---------   ----------    ------------  ----------             ---------------
*    01.00.00 | 24/01/2016 | lele.liu    | N/A | BootDrv010001                    Original
*                   
************************************************************************************************
* END_FILE_HDR*/

#include "bl_flash.h"
#include "r_fcl_types.h"
/*********************************************************************************************************************/
/*Macro                                                                                                     */
/*********************************************************************************************************************/    
 //#define R_FCL_DEVICE_SPECIFIC_INIT      

/*********************************************************************************************************************/
/* HEADER contain version information and 4 driver function pointer   StartAddr +0x20                                */
/*********************************************************************************************************************/
//#if 0
#pragma ghs section rodata = ".R_FCL_CODE_HEAD"
/*different cpu may have different function pointer size,the header type may need to be changed*/

const bl_FlashDrvHeader_t Flashheader  =
{
   
   FLASH_DRIVER_VERSION_TYPE,
   FLASH_DRIVER_VERSION_INDEX,
   FLASH_DRIVER_VERSION_MAGIC,
   FLASH_DRIVER_VERSION_VERSION,
   Flash_Init,

   Flash_Deinit,

   Flash_Erase,

   Flash_Write,

};

//#endif

/*********************************************************************************************************************/
/* DriverCode                                                                                                        */
/*********************************************************************************************************************/
#pragma ghs section text = ".R_FCL_CODE_USR"

/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : FlashInit
*
* Description   : Flash moudle init 
*
* Inputs        : fp:standard HIS input parameters structure
*
* Outputs       : None
* 
* Limitations   : None
*                 
************************************************************************************************
END_FUNCTION_HDR */
void  Flash_Init(bl_FlashDrvParam_t* fp)
{
    r_fcl_request_t     myRequest;
    
    /* Set for hardware watchdog */
    PM8 &= ~(1<<2);/* output mode*/
        
    (void)R_FCL_Init (&sampleApp_fclConfig_enu);
    FCLUser_Open ();
    /* prepare environment */
    myRequest.command_enu = R_FCL_CMD_PREPARE_ENV;
    R_FCL_Execute (&myRequest);
    #if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_USER
        while (R_FCL_BUSY == myRequest.status_enu)
        {
            R_FCL_Handler ();
        }
    #endif

    fp->errCode = BL_ERR_OK;   
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : FlashDeinit
*
* Description   : Flash moudle deinit 
*
* Inputs        : fp:standard HIS input parameters structure
*
* Outputs       : None
* 
* Limitations   : None
*                 
************************************************************************************************
END_FUNCTION_HDR */
void  Flash_Deinit(bl_FlashDrvParam_t* fp)
{
    (void)fp;
    FCLUser_Close ();
    fp->errCode = BL_ERR_OK;   
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : FlashErase
*
* Description   : Flash moudle erase
*
* Inputs        : fp:standard HIS input parameters structure
*
* Outputs       : None
* 
* Limitations   : erase  block
*                 
************************************************************************************************
END_FUNCTION_HDR */
void  Flash_Erase(bl_FlashDrvParam_t* fp)
{
    bl_u32_t addr_start ,address_end;
    bl_u32_t BlockNum,BlockNum_start,BlockNum_end; 
    r_fcl_request_t     myRequest;
    
    addr_start = fp->address;
    address_end = (fp->size + addr_start -1);
    
    if((addr_start < 0x40000))
    {
        if(0 == (addr_start & 0xFFFF0000))  /* block0~block7,8kb per block */
        {
            BlockNum_start = (addr_start >> 13);
            if( address_end < 0x10000)    /* address_end in block0~block7 */
            {
                BlockNum_end = (address_end >> 13);
            }
            else if((address_end >= 0x10000)&&(address_end < 0x40000)) /* address_end in block8~block13 */
            {
                BlockNum_end = ((address_end >> 15) + 6);
            }
            else
            {
                BlockNum_end = 13;
            }
            BlockNum = BlockNum_end - BlockNum_start + 1;
        }
        else if(addr_start & 0x007F0000)    /* block8~block13,32kb per block */
        {
            BlockNum_start = ((addr_start >> 15) + 6);
            if(address_end < 0x40000) /* address_end in block8~block13 */
            {
                BlockNum_end = ((address_end >> 15) + 6);
            }
            else
            {
                BlockNum_end = 13;
            }
            BlockNum = BlockNum_end - BlockNum_start + 1;
        }
        else
        {
            
        }

        WDTA1WDTE = 0xAC;    /* Feed watchdog. */
        P8 = (((~P8) & 0x4)|(P8 & 0xfffb)); /* Feed hardware watchdog. */                
        /* erase block */
        myRequest.command_enu = R_FCL_CMD_ERASE;
        myRequest.idx_u32     = BlockNum_start;  /* erase start  */
        myRequest.cnt_u16     = BlockNum;
		__DI();
        R_FCL_Execute (&myRequest);
		__EI();
        #if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_USER
        while (R_FCL_BUSY == myRequest.status_enu)
        {
            R_FCL_Handler ();
        }
        #endif
        fp->errCode = BL_ERR_OK;
                
    }
    else
    {
        fp->errCode = BL_ERR_NOT_OK;
    }
    
}
/* BEGIN_FUNCTION_HDR
************************************************************************************************
* Function Name : Flash_Write
*
* Description   : Flash moudle write 
*
* Inputs        : fp:standard HIS input parameters structure
*
* Outputs       : None
* 
* Limitations   : write 256 * n bytes 
*                 
************************************************************************************************
END_FUNCTION_HDR */

void  Flash_Write(bl_FlashDrvParam_t* fp)
{    
    bl_u32_t addr = fp->address;
    bl_u32_t source = (bl_u32_t)(fp->buffer);
    bl_Size_t size = fp->size;
    r_fcl_request_t     myRequest;
    bl_u16_t cnt = (size / 256);

    if((addr < 0x40000) && ((size % 256) == 0))
    {
        
        WDTA1WDTE = 0xAC;        /* Feed watchdog. */
        P8 = (((~P8) & 0x4)|(P8 & 0xfffb)); /* Feed hardware watchdog. */
        myRequest.command_enu = R_FCL_CMD_WRITE;
        myRequest.bufferAdd_u32 = source;
        myRequest.idx_u32       = addr;
        myRequest.cnt_u16       = cnt;                    /* written bytes = 256 * cnt_u16 */
		__DI();
        R_FCL_Execute (&myRequest);
		__EI();
        #if R_FCL_COMMAND_EXECUTION_MODE == R_FCL_HANDLER_CALL_USER
        while (R_FCL_BUSY == myRequest.status_enu)
        {
            R_FCL_Handler ();
        }
        #endif
       
        fp->errCode = BL_ERR_OK;
    }
    else
    {
        fp->errCode = BL_ERR_NOT_OK;
    }
}


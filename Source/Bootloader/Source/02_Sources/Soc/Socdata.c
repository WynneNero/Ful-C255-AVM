/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   :            										   *
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
* 0.1    July 25 ,2016      ShangQiuju       Init version
* ----------------------------------------------------------------------
* 0.2    Jan 3 ,2017      ShangQiuju       Update for function return value  handler - only return at one place. 
* ----------------------------------------------------------------------
* 0.3    Mar 13 ,2017    ShangQiuju       Fix bug of  unused swdl address cal fail.
*=====================================================================*/

/**** System include files ****/

/*---Private include files--------------------------------------------*/
#include "socdata.h"
#include "socdata_if.h"
#include "bl_typedefs.h"
#include "bl_flash_if.h"
#include "bl_system.h"
#include "FLASH_HAL_CFG.h"

/*===VARIABLES========================================================*/
/*---Global-----------------------------------------------------------*/
U8 swdl_data_frame_len;
U8 swdl_data_frame[SWDL_FRAME_LEN];

BOOL swdl_data_recieved;

U32 file_cur_row_addr;
U32 file_cur_backup_row_addr;
U8  file_cur_row_length;
U8 *file_cur_row_data_buffer_ptr;

U32 file_data_len;
U32 file_data_sum;
U8  file_data_project_number[10];
U32 file_data_decode_len;                       
U32 file_data_decode_sum;

U8  file_data_error_counter;

#define WRITE_FLASH_BLOCK_SIZE 512

U8 upgradeSDatain[WRITE_FLASH_BLOCK_SIZE];

U16 upgradeDataLen;
U32 upgradeAddress;

/*---Private----------------------------------------------------------*/
const U8 project_number_in_local_flash[10] =
{/*fix to 10bytes*/    
    "Mcu-Update"
};

/*===FUNCTIONS========================================================*/
/*---Global-----------------------------------------------------------*/
/***********************************************************************
*  Name        : navi_intial_misc_variables
*  Description :          
*  Parameter   : none
*  Returns     : none 
***********************************************************************/
void navi_intial_misc_variables(void)
{
    swdl_data_frame_len = 0;
    swdl_data_recieved = FALSE;
    
    file_cur_row_addr = 0;
    file_cur_backup_row_addr = 0xffff;
    file_cur_row_length = 0;
    file_cur_row_data_buffer_ptr = NULL;
    
    file_data_len = 0;
    file_data_sum = 0;
    file_data_decode_len = 0;
    file_data_decode_sum = 0;
    
    file_data_error_counter = 0;
    upgradeDataLen =0;
    upgradeAddress = FLASH_APP_START_ADDRESS;
}

/***********************************************************************
*  Name        : get_cur_row_checksum
*  Description :          
*  Parameter   : none
*  Returns     : U32 
***********************************************************************/
U32  get_cur_row_checksum(void)
{
     U32 chk=0;
     U8 i;
     U8 length;

     //the format of S19
     //type(S1-9)+Length(1bytes)+Add(XX)+Data.....+Checksum    
     length = swdl_data_frame[S19_ROW_LEN] -1;//1bytes(checksum)); 
     for(i=0;i<length;i++)
     {
        chk += swdl_data_frame[S19_FILE_LEN1+i];//start from the first data position   
     }                                                     

     return(chk);
}

/***********************************************************************
*  Name        : check_cur_row_checksum
*  Description :          
*  Parameter   : none
*  Returns     : BOOL 
***********************************************************************/
BOOL check_cur_row_checksum(void)
{
     U8 chk=0;
     U8 i;
     U8 cnt;
     BOOL bRet = TRUE;
     
     cnt = swdl_data_frame[S19_ROW_LEN]; 
     //the format of S19
     //type(S1-9)+Length(2bytes)+Add(XX)+Data.....+Checksum    
     if((swdl_data_frame[S19_ROW_TYPE] != S3_ROW)&&(swdl_data_frame[S19_ROW_TYPE] != S0_ROW))
     {
        //if not equal to S0/S3,return error.
        bRet =  FALSE;
     }
     else
     {         
         for(i=0;i< cnt; i++)
         {
            chk += swdl_data_frame[S19_ROW_LEN+i];//start from the length position   
         }
         
         //this is a checksum rule of S19 file.
         chk = ~chk;
         
         if(chk != swdl_data_frame[cnt+2])//the checksum position
         {
             bRet = FALSE;
         }
     }
     
     return bRet;
}
/***********************************************************************
*  Name        : check_cur_row_type
*  Description :          
*  Parameter   : none
*  Returns     : U8 
***********************************************************************/
U8 check_cur_row_type(void)
{
     //the format of S19
     //type(S1-9)+Length(1bytes)+Add(XX)+Data.....+Checksum   
    return (swdl_data_frame[S19_ROW_TYPE]);
}
/***********************************************************************
*  Name        : get_cur_row_addr
*  Description :          
*  Parameter   : none
*  Returns     : U32 
***********************************************************************/
U32 get_cur_row_addr(void)
{
     U32 cur_row_addr;

     //the format of S19
     //type(S1-9)+Length(1bytes)+Add(XX)+Data.....+Checksum    
     if(swdl_data_frame[S19_ROW_TYPE] != S3_ROW)
     {//if not equal to S3,return error.
        cur_row_addr = 0;
     }
     else
     {
         //file_backup_row_addr = file_cur_row_addr;
    
         cur_row_addr = (((U32)swdl_data_frame[S19_DATA_ADD1])<<24)
                                 +(((U32)swdl_data_frame[S19_DATA_ADD2])<<16)
                                 +(((U32)swdl_data_frame[S19_DATA_ADD3])<<8)
                                 + (U32)swdl_data_frame[S19_DATA_ADD4];   
     }

     return cur_row_addr;
}
/***********************************************************************
*  Name        : get_project_number
*  Description :          
*  Parameter   : none
*  Returns     : none 
***********************************************************************/
void get_project_number(void)
{
    U8 i;
    U8 *source_data_ptr;
    U8 *des_data_ptr;

    des_data_ptr = &file_data_project_number[0];
    source_data_ptr = &swdl_data_frame[S19_PORJECT_NAME];

    for(i=0; i <10; i++)
    {
       *des_data_ptr =  *source_data_ptr;
       des_data_ptr++;
       source_data_ptr++;
    }
}

/***********************************************************************
*  Name        : check_first_line_xor_value_valid
*  Description :          
*  Parameter   : none
*  Returns     : TRUE/FALSE 
***********************************************************************/
BOOL check_first_line_xor_value_valid(void)
{
    U8 i;
    U8 *source_data_ptr;
    U8 xor_length;
    U16 temp_xor_value;
    U16 xor_value;
    U8 ret_value = TRUE;
    
    xor_length = swdl_data_frame[S19_ROW_LEN] - 3;
    source_data_ptr = &swdl_data_frame[S19_FILE_LEN1]; 

    xor_value = swdl_data_frame[S19_FIRST_LINE_XOR_LOW];
    
    temp_xor_value = *source_data_ptr;
    source_data_ptr++;
    
    for(i=1; i < xor_length; i++)
    {
       temp_xor_value ^=  *source_data_ptr;
       source_data_ptr++;
    }
    
    if(temp_xor_value != xor_value)
    {
        ret_value = FALSE;
    }

    ///SQJ
    ret_value = TRUE;
    
    return(ret_value);
}
/***********************************************************************
*  Name        : get_cur_row_length
*  Description :          
*  Parameter   : none
*  Returns     : U8 
***********************************************************************/
U8 get_cur_row_length(void)
{
     U8 cur_row_length;

     //the format of S19
     //type(S1-9)+Length(1bytes)+Add(XX)+Data.....+Checksum    
     if(swdl_data_frame[S19_ROW_TYPE] != S3_ROW)
     {//if not equal to S3,return error.
        cur_row_length = 0;
     }
     else
     {
        cur_row_length = swdl_data_frame[S19_ROW_LEN] - 5;//(4bytes add + 1byte checksum) //length
     }

     return(cur_row_length);
}
/***********************************************************************
*  Name        : get_cur_row_data_buffer_ptr
*  Description :          
*  Parameter   : none
*  Returns     : U8 * 
***********************************************************************/
U8 *get_cur_row_data_buffer_ptr(void)
{
      U8 *cur_buffer_ptr;

     //the format of S19
     //type(S1-9)+Length(1bytes)+Add(XX)+Data.....+Checksum    
     if(swdl_data_frame[S19_ROW_TYPE] != S3_ROW)
     {//if not equal to S3,return error.
        cur_buffer_ptr = NULL;
     }
     else
     {
        cur_buffer_ptr=&swdl_data_frame[S19_DATA]; 
     }

     return (cur_buffer_ptr);
}
/***********************************************************************
*  Name        : swdl_check_first_row_valid
*  Description :          
*  Parameter   : none
*  Returns     : ERR_TYPE 
***********************************************************************/
ERR_TYPE swdl_check_first_row_valid(void)
{
    ERR_TYPE retval = ERR_SEVICE_NOT_READY;

    if(swdl_data_recieved)
    {
        tm_delay_us(500);
        if(check_cur_row_checksum())
        {//checksum correct
           get_project_number();

           if(memcmp(project_number_in_local_flash,file_data_project_number,10)==0)  
           {//these two variables are the same
                if(check_first_line_xor_value_valid())
                {//check xor is correct
                    retval = ERR_OK;
                    file_data_error_counter = 0;                    
                }
                else
                {//check the xor is wrong
                    if( ++file_data_error_counter < 3)
                    {//try to 3times
                        retval = ERR_RETRY;
                        //navi_pw_request_navi_get_cur_swdl_data();                 
                    }
                    else
                    {//exceed 3times error, request reset.
                        retval = ERR_FAILED;
                        //boot_set_navi_cur_status(NAVI_SWDL_ERROR);                
                    }                    
                }
           }
           else
           {
                if( ++file_data_error_counter < 3)
                {//try to 3times                
                        retval = ERR_RETRY;
                    //navi_pw_request_navi_get_cur_swdl_data();                 
                }
                else
                {                 
                    
                     retval = ERR_SERIOUS;
                     /*
                    navi_pw_request_navi_exit_swdl();
                    erase_swdl_mask();
                    tm_delay_us(9000);
                    boot_set_navi_cur_status(NAVI_SWDL_ERROR); 
                     */
                }  
           }               
        }
        else
        {//checksum error
            if( ++file_data_error_counter <  3)
            {//try to 3times
                retval = ERR_RETRY;
                //navi_pw_request_navi_get_cur_swdl_data();                 
            }
            else
            {//exceed 3times error, request reset.
                retval = ERR_FAILED;
                //boot_set_navi_cur_status(NAVI_SWDL_ERROR);                
            }
        }
        
        swdl_data_recieved = FALSE; 
    }

    return(retval);
}

/***********************************************************************
*  Name        : swdl_check_address_is_valid
*  Description :          
*  Parameter   : none
*  Returns     : ERR_TYPE 
***********************************************************************/
ERR_TYPE swdl_check_address_is_valid(void)
{
    ERR_TYPE retval = ERR_OK ;

    if(check_cur_row_checksum())
    {/*checksum is right*/

        file_cur_row_addr = get_cur_row_addr();
        file_cur_row_length = get_cur_row_length();
        file_cur_row_data_buffer_ptr = get_cur_row_data_buffer_ptr();

        if((file_cur_backup_row_addr != file_cur_row_addr))
        {//avoid the repeat line.
            file_data_decode_len += file_cur_row_length;
            file_data_decode_sum += get_cur_row_checksum();                    
            file_cur_backup_row_addr = file_cur_row_addr;   

            if(file_cur_row_length == 0)
            {/*check the length and address is valid*/         
            //navi_pw_request_navi_get_next_swdl_data();
                retval = ERR_BREAK; 
            }
            else if(file_cur_row_data_buffer_ptr == NULL)
            {
                if( ++file_data_error_counter <  3)
                {//try to 3times
                //navi_pw_request_navi_get_cur_swdl_data();         
                    retval = ERR_RETRY;
                }
                else
                {//exceed 3times error, request reset.
                //boot_set_navi_cur_status(NAVI_SWDL_ERROR);     
                    retval = ERR_FAILED;           
                }			  
            }
            else
            {
                if((file_cur_row_addr + file_cur_row_length)  <  FLASH_APP_START_ADDRESS)
                {/*check the address beyond the app address*/      
                    retval = ERR_BREAK; 
                }
                else
                {
                    if(file_cur_row_addr < FLASH_APP_START_ADDRESS)
                    {
                        file_cur_row_data_buffer_ptr += (FLASH_APP_START_ADDRESS - file_cur_row_addr);                   
                        file_cur_row_length = ((file_cur_row_addr + file_cur_row_length) - FLASH_APP_START_ADDRESS);                    
                        file_cur_row_addr = FLASH_APP_START_ADDRESS;

                        if(file_cur_row_length == 0)
                        {
                            retval = ERR_BREAK; 
                        }  
                    }
                }
            }        
        }
        else
        {
            retval = ERR_BREAK;
        }

    }
    else
    {
        if( ++file_data_error_counter <  3)
        {//try to 3times
           // navi_pw_request_navi_get_cur_swdl_data();             
           retval = ERR_RETRY;
        }
        else
        {//exceed 3times error, request reset.
            //boot_set_navi_cur_status(NAVI_SWDL_ERROR);       
           retval = ERR_FAILED;         
        }
    } 
    
    return(retval);
}

/***********************************************************************
*  Name        : handlerRecvData
*  Description :          
*  Parameter   : address, len,buf
*  Returns     : BOOL
***********************************************************************/
BOOL handlerRecvData(U32 address,U16 len,U8* buf)
{
    BOOL bRet;
    
    if(upgradeDataLen+len>=WRITE_FLASH_BLOCK_SIZE)
    {
        U16 NeedCpyLen = WRITE_FLASH_BLOCK_SIZE - upgradeDataLen;
        U16 remainLen = len-NeedCpyLen;
        memcpy(upgradeSDatain+upgradeDataLen,buf,NeedCpyLen);
        if(BL_ERR_OK == Flsif_Write(upgradeAddress,WRITE_FLASH_BLOCK_SIZE,upgradeSDatain))
        {
            tm_delay_us(5000);
            memcpy(upgradeSDatain,buf+NeedCpyLen,remainLen);            
            upgradeAddress = upgradeAddress+WRITE_FLASH_BLOCK_SIZE;
            upgradeDataLen = remainLen;
            bRet = TRUE;
        }
        else
        {
            bRet = FALSE;
        }       
    }
    else
    {
        memcpy(upgradeSDatain+upgradeDataLen,buf,len);
        upgradeDataLen = upgradeDataLen+len;
        bRet = TRUE;
    }

    return bRet;
}

/***********************************************************************
*  Name        : handlerLastData
*  Description :          
*  Parameter   : None
*  Returns     : BOOL
***********************************************************************/
BOOL handlerLastData(void)
{
    U16 i, left_size;
    U8 *ptr_temp = NULL;
    
    if(upgradeDataLen < CODE_FLASH_WRITE_ALIGN_SIZE)
    {
        left_size = CODE_FLASH_WRITE_ALIGN_SIZE - upgradeDataLen;
    }
    else
    {
        left_size = WRITE_FLASH_BLOCK_SIZE - upgradeDataLen;
    }

    ptr_temp = (U8 *)(upgradeSDatain + upgradeDataLen);
    for(i = 0; i < left_size; i++)
    {
         *(ptr_temp + i) = 0xFF;
    }
    upgradeDataLen += left_size;
    
        if(BL_ERR_OK == Flsif_Write(upgradeAddress,upgradeDataLen,upgradeSDatain))
        {
            tm_delay_us(5000);
            return TRUE;
        }
        else
        {
            return FALSE;
        } 
   
}

/***********************************************************************
*  Name        : swdl_data_handle
*  Description :          
*  Parameter   : none
*  Returns     : ERR_TYPE 
***********************************************************************/
ERR_TYPE swdl_data_handle(void)
{
    ERR_TYPE ret = ERR_SEVICE_NOT_READY;
    if(swdl_data_recieved)
    {
        if(check_cur_row_type() == S0_ROW)
        {//if current row is the start of this file.
            if(check_cur_row_checksum())
            {
                //file_data_len
                file_data_sum =(((U32)swdl_data_frame[S19_FILE_CKSUM1])<<24)
                             +(((U32)swdl_data_frame[S19_FILE_CKSUM2])<<16)
                             +(((U32)swdl_data_frame[S19_FILE_CKSUM3])<<8)
                             + (U32)swdl_data_frame[S19_FILE_CKSUM4]; 

                file_data_len =(((U32)swdl_data_frame[S19_FILE_LEN1])<<24)
                             +(((U32)swdl_data_frame[S19_FILE_LEN2])<<16)
                             +(((U32)swdl_data_frame[S19_FILE_LEN3])<<8)
                             + (U32)swdl_data_frame[S19_FILE_LEN4];                 
                
                //navi_pw_request_navi_get_next_swdl_data();   
                ret = ERR_OK;
            }
            else
            {
                if( ++file_data_error_counter <  3)
                {//try to 3times
                    //navi_pw_request_navi_get_cur_swdl_data();        
                    ret = ERR_RETRY;
                }
                else
                {//exceed 3times error, request reset.
                    ret = ERR_FAILED;
                    //boot_set_navi_cur_status(NAVI_SWDL_ERROR);                
                }
            }   
        }
        else if(check_cur_row_type() == S3_ROW)//4bytes address
        {//the data row decode
            ///TODO:SQJ boot_set_navi_cur_status(NAVI_SWDL_PROGRAMMING);
            /*write data*/
            ERR_TYPE retofa = swdl_check_address_is_valid();
            if(retofa == ERR_OK)
            {/*add is valid*/    
                /*programm data to flash*/
                if(handlerRecvData(file_cur_row_addr,file_cur_row_length,file_cur_row_data_buffer_ptr))//Adpt_DownloadData
                {
                    /*request next row*/
                    //
                   // if(memcmp((U16 *)file_cur_row_addr,file_cur_row_data_buffer_ptr,file_cur_row_length) == 0)
                    {
                        //navi_pw_request_navi_get_next_swdl_data(); 
                        ret = ERR_OK;
                    }
                   // else
                    {
                       //exceed 3times error, request reset.
                       // ret = ERR_FAILED;
                      // boot_set_navi_cur_status(NAVI_SWDL_ERROR);                
                    }              
                }
                else
                {
                    //case FLASH_ADD_ERROR:
                    //case FLASH_TIMEOUT_ERROR:
                    //case FLASH_ERASE_TIMEOUT_ERROR:
                    ret = ERR_FAILED;
                   // boot_set_navi_cur_status(NAVI_SWDL_ERROR); 
                }
            }
            else
            {
                if(retofa == ERR_BREAK) ret = ERR_OK;
                else    ret = retofa;
            }
          }
          else if(check_cur_row_type() == S7_ROW)
          {//the end of file.
                BOOL bDataHandler = TRUE;
                if(upgradeDataLen!=0)
                {
                    bDataHandler = handlerLastData();
                }
                if(bDataHandler)
                {
                    if((file_data_decode_len == file_data_len) &&(file_data_decode_sum == file_data_sum))
                    {
                       //boot_set_navi_cur_status(NAVI_SWDL_PROGRAMM_COMPLETE);
                       ret = ERR_FINISHED;
                    }
                    else
                    {//sys restart.
                       // boot_set_navi_cur_status(NAVI_SWDL_ERROR);    
                        ret = ERR_FAILED;
                    }
                }
                else
                {
                    ret = ERR_FAILED;
                }
    
          }
          else
          {//sys restart
                //boot_set_navi_cur_status(NAVI_SWDL_ERROR);
          }  
          swdl_data_recieved=FALSE;   
     }

     return ret;
 
}

/***********************************************************************
*  Name        : SocDataReceivedData
*  Description :          
*  Parameter   : size,data
*  Returns     : none 
***********************************************************************/
void SocDataReceivedData(U8 size,U8* data)
{   
        U8 index;
        swdl_data_frame_len = size;
        for(index=0;index<swdl_data_frame_len;index++)
        {
            swdl_data_frame[index]=*(data+index);    
        }                    
        swdl_data_recieved = TRUE;
}

/*---Private----------------------------------------------------------*/


/**************** END OF FILE *****************************************/

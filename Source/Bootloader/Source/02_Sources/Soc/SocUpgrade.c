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
* Version       Date            Name            Changes and comments
* ----------------------------------------------------------------------
*  0.1          2016/8/29   ShangQiuju      Init version
* ----------------------------------------------------------------------
*  0.2          2016/12/14 ZhangJie          Read/Write FDL data by bytes 
* ----------------------------------------------------------------------
*  0.3          2016/12/30 ShangQiuju      remove app address and size as config parameter.
* ----------------------------------------------------------------------
*  0.4          2017/1/3     ShangQiuju      Update for  SocManager_SendMsg return handle.
                                                            Remove unused parameter.
* ----------------------------------------------------------------------
*  0.5          2017/1/3     ShangQiuju      Init getDataTimeout before using.
* ----------------------------------------------------------------------
*  0.6          2017/1/6     ShangQiuju      Add Test Code for Ds03h Soc Test Upgrade App.
* ----------------------------------------------------------------------
*  0.7          2017/3/13     ShangQiuju    Add UpgradeState used to record state before enter error
* ----------------------------------------------------------------------
*  0.8          2017/3/14   ZhangJie          Add function to call fcl directly.
*=====================================================================*/
#include "config.h"
#include "define.h"
#include "socdata_if.h"
#include "SocMsg_Cfg.h"
#include "socUpgrade.h"
#include "socUpgrade_if.h"
#include "SocDriver_IF.H"
#include "SocMsgHandler.h"
#include "FLS_Drv.h"
#include "bl_flash_if.h"
#include "bl_system.h"
#include "Gpio_cfg.h"

extern unsigned char BL_upgrade_type;
BOOL bPowerUpOK;
BOOL bJ6RequestToReset;
BOOL bFlashWriteTimeout;
BOOL J6_ENTER_FAILSET = FALSE;

/*
UpgradeState Used to record state before enter error
D0: eSocUpgradeState
D1: ret
D2: bFlashWriteTimeout
*/
U8 UpgradeState[3] ={0};
U8 SendBuf[SOC_FRAME_MAXLENGTH];
U16 getDataTimeout;
U8 getDatacount;
#ifndef USE_FCL_SOURCE_CODE  
U8* fclptr = NULL;
extern const unsigned char FclCode[10384];
#endif

E_SOC_STATE eSocState;
E_SOC_UPPGRADE_STATE eSocUpgradeState;

void DataHandler(void);
void Upgrade_Spi_Handler(void);
void erase_swdl_mask(void);
void pw_request_get_next_swdl_data(void);
void pw_request_get_cur_swdl_data(void);
void pw_request_to_exit_swdl(void);
void pw_mcu_send_update_status(void);
extern void timer_for_1101reset_handle(void);
/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/
/***********************************************************************
*  Name        : SocApp_Init
*  Description : Init updage app       
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SocApp_Init(void)
{
  U32 i;
  eSocState=E_SOC_IDLE;
  bJ6RequestToReset = FALSE;
  bPowerUpOK = FALSE;
  eSocUpgradeState = SWDL_IDLE;
  bFlashWriteTimeout = FALSE;
#ifndef USE_FCL_SOURCE_CODE  
  fclptr = FLASHIF_DRIVER_STARTADDRESS;
  for(i=0;i<10752;i++)
  {
    *fclptr++ = FclCode[i];
  }
#endif
}

/***********************************************************************
*  Name        : SocApp_DeInit
*  Description : DeInit soc app      
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SocApp_DeInit(void)
{
    eSocState = E_SOC_IDLE;
}


/***********************************************************************
*  Name        : SocInit
*  Description : Init Soc driver     
*  Parameter   : bl_Return_t
*  Returns     : None
***********************************************************************/
bl_Return_t SocInit(void)
{
	OPEN_SOC_POWER() ;

    SocDriver_Init();    
    SocMsg_Init();
    SocApp_Init(); 
    return BL_ERR_OK;
}

/***********************************************************************
*  Name        : SocApp
*  Description : Init soc app      
*  Parameter   : None
*  Returns     : None
***********************************************************************/
unsigned char can_to_spi_data[512];
unsigned int i=0;
unsigned first=1;
unsigned char soc_set_timer_evt=FALSE;//xjy
unsigned char total_length[5]={0x0,0x0,0x1,0x24,0x00};
unsigned char soc_reset[1]={0x2};
unsigned char request_version[2]={0x4};
unsigned char check_soc_upgrade[2]={0x1};
unsigned char get_version=0;
unsigned char updating_soc_success= FALSE;
unsigned char upgrade_finish=0;
unsigned int count=0;
unsigned int count1=0;
extern unsigned char receive_spi_data;
extern unsigned char send_to_soc_finish;
extern unsigned char application_invalue_flag;
unsigned char max_version_length=32;

void SocApp(void)
{
	unsigned char appli_value_str[4] = {0xff,0xff,0xff,0xff};
	unsigned int i=0;
	BOOL ret = 0;
	unsigned int a=0;
	
    if(BL_upgrade_type == UPGRADE_BY_CAN)
    {

		if(receive_spi_data==0){

		SocDriver_Cyclic_Entry();
   		SocMsg_Entry();
    	SocManager_Entry();
    	tm_delay_us(1000);
		timer_for_1101reset_handle();
		if(get_version==1) {
			SocManager_SendMsg(2,0x8201,1,request_version);//get version
			get_version=0;
		}
		if(upgrade_finish==2) {
			count++;
			if(count>2000) 
			{
				if(J6_ENTER_FAILSET)
				{
					SocManager_SendMsg(2,0x5205,1,check_soc_upgrade);	//continue check if soc upgrade finish
				}
				else
				{
					SocManager_SendMsg(2,0x5202,1,soc_reset); //if 5302 no recv £¬continue send 5202
				}
				
				count= 0;
			}
		}
		if (upgrade_finish ==1){
			if(soc_set_timer_evt==TRUE)
			{
			//	application_invalue_flag = FALSE;
				set_1101reset_timer(1500);//1.5 S
				soc_set_timer_evt=FALSE;
			}
//			if(count1>10000) {
//			Sys_Reset();
//			count1=0;
//			}
		}
		if(send_to_soc_finish==1) {
			SocManager_SendMsg(2,0x5202,1,soc_reset); //let soc reset
			send_to_soc_finish=0;
			upgrade_finish=2;
		}

	}
	else {

		if(first==1){
			SocManager_SendMsg(1,0x5204,5,total_length);
			SocDriver_Cyclic_Entry();
			SocMsg_Entry();
			SocManager_Entry();
			tm_delay_us(10000);
			first=0;
		}
		for(i=0;i<4;i++) {
			
			SocDriver_Cyclic_Entry();
			SocMsg_Entry();
			SocManager_Entry();
			tm_delay_us(60000);
			ret = SocManager_SendMsg(1,0x5204,128,&can_to_spi_data[i*128]);
			if(ret == FALSE)
				a = 0;
			
		}
		receive_spi_data=0;

		}

    }
    else if(BL_upgrade_type == UPGRADE_BY_SPI)
    {
        SocDriver_Cyclic_Entry();
        SocMsg_Entry();
        SocManager_Entry();
        tm_delay_us(1000);
		}
}

/***********************************************************************
*  Name        : SocDeInit
*  Description : DeInit soc driver    
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SocDeInit(void)
{
    SocApp_DeInit();
    SocMsg_DeInit();
    SocDriver_DeInit();
}

/***********************************************************************
*  Name        : SocManager_Entry
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SocManager_Entry(void)
{
    U16 i;
    switch(eSocState)
    {
        case E_SOC_IDLE:
            SocMsg_ControlPower(E_DEV_POWERON);
            eSocState = E_SOC_POWER_ON;
        break;

        case E_SOC_POWER_ON:
            SocMsg_ControlCommunication(TRUE);
            eSocState=E_SOC_READY;
        break;

        case E_SOC_READY:  
            DataHandler();
#ifdef MCU_DS03H_HW_100
	    bPowerUpOK = TRUE;  //only for upgraade test cmd 0x5117
#endif
        break;

        case E_SOC_CONNECTED:
            DataHandler();      
            if(bJ6RequestToReset)
            {
                eSocState = E_SOC_POWER_OFF;
            }
        break;
        
        case E_SOC_POWER_OFF:
            SocMsg_ControlCommunication(FALSE);
            SocMsg_ControlPower(E_DEV_POWEROFF);
            eSocState = E_SOC_WAIT_RESET;
        break;

        case E_SOC_WAIT_RESET:   
            for(i=0;i<1000;i++)
            tm_delay_us(1000);//1ms
    	     //g_RteInfo.SystemReset();	
    //	    bl_application_value_dataflash_maker();
            Sys_Reset();
        break;
        
        default:
        break;
    }
}

/***********************************************************************
*  Name        : FlashWriteTimeout
*  Description : call back function.  
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void FlashWriteTimeout(void)
{
    bFlashWriteTimeout = True;
}

/***********************************************************************
*  Name        : SocManager_SendMsg
*  Description : send.  
*  Parameter   : None
*  Returns     : BOOL
***********************************************************************/
BOOL SocManager_SendMsg( U8 cmd_type, U16 service, U8 nArgs,U8 *pArg)
{
    BOOL bRet = FALSE;
    
    if(eSocState!=E_SOC_CONNECTED)
    {
        if((service!=RADIO_DISPATCH_CHANGE_POWER_MODE)
            &&(service!=RADIO_DISPATCH_SWDL_ENTER_EXIT))
        {
            bRet = FALSE;
        }
    }
    else
    {
        memset(SendBuf,0,nArgs+10);
        SendBuf[0] = LQ_CMD;
        SendBuf[1] = cmd_type;
        SendBuf[2] = service>>8;
        SendBuf[3] = service&0xff;
        SendBuf[4]= nArgs;
        memcpy(SendBuf+5, pArg, nArgs);
        bRet = SocMsg_SendMessage(SendBuf,nArgs+5);
    }
    return bRet;
}

//private

/***********************************************************************
*  Name        : DataHandler
*  Description : NA.  
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void DataHandler(void)
{
    switch(eSocState)
    { 
        case E_SOC_READY:
               if(bPowerUpOK )	    eSocState=E_SOC_CONNECTED;   
        break;
        case E_SOC_CONNECTED:  
	if(BL_upgrade_type == UPGRADE_BY_SPI)
	{
                Upgrade_Spi_Handler();
	}
        break;
        default:break;
    }
}


/***********************************************************************
*  Name        : Upgrade_Spi_Handler
*  Description : NA.  
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void Upgrade_Spi_Handler(void)
{
    ERR_TYPE ret;
    bl_Return_t bRet;
    bl_Address_t address = APP_ADDRESS;
    bl_Size_t eraseSize = EASE_APP_ADDRESS;//0x54000;
    int  i = 0;
        if(bFlashWriteTimeout)  
        {
            eSocUpgradeState = SWDL_ERROR;
            UpgradeState[0] = eSocUpgradeState;
            UpgradeState[1] = ERR_OK;
            UpgradeState[2] = bFlashWriteTimeout;            
        }
         switch(eSocUpgradeState)
         {
            case FC_CHECK_FIRST_ROW_VALID:
            /*check the first row,if correct,then erase the flash,*/
                ret = swdl_check_first_row_valid();
                switch(ret)
                {
                    case ERR_OK:
                        navi_intial_misc_variables();
                        //if(BL_ERR_OK ==Mem_InitMemory(1))     eSocUpgradeState = SWDL_SOC_READY;    
                        if(BL_ERR_OK == Flsif_Init())  
                        {
                            eSocUpgradeState = SWDL_SOC_READY;
                        }
                        else
                        {          
                            UpgradeState[0] = eSocUpgradeState;
                            UpgradeState[1] = ret;
                            UpgradeState[2] = bFlashWriteTimeout;      
                            eSocUpgradeState = SWDL_ERROR;                    
                        }
                    break;
                    case ERR_SEVICE_NOT_READY:
                    break;
                    case ERR_RETRY:
                        pw_request_get_cur_swdl_data();  
                    break;
                    case ERR_FAILED:
                        UpgradeState[0] = eSocUpgradeState;
                        UpgradeState[1] = ret;
                        UpgradeState[2] = bFlashWriteTimeout;     
                        eSocUpgradeState = SWDL_ERROR;         
                    break;
                    case ERR_SERIOUS:
                        pw_request_to_exit_swdl();
                        erase_swdl_mask();
                        UpgradeState[0] = eSocUpgradeState;
                        UpgradeState[1] = ret;
                        UpgradeState[2] = bFlashWriteTimeout;     
                        eSocUpgradeState = SWDL_ERROR;
                    break;   
                    default:break;
                }
                break;

            case SWDL_SOC_READY:
                tm_delay_us(20000);
                //WATCHDOG_Disable();
                ret = Flsif_Erase(address,eraseSize);
                if(BL_ERR_OK == ret)
                {
                   pw_request_get_cur_swdl_data();  
                   eSocUpgradeState = SWDL_PROGRAMMING;
                   getDataTimeout = 0;
                   //WATCHDOG_Enable();                    
                }
                else
                { 
                    UpgradeState[0] = eSocUpgradeState;
                    UpgradeState[1] = ret;
                    UpgradeState[2] = bFlashWriteTimeout;     
                    eSocUpgradeState = SWDL_ERROR;
                }
                break;

            case SWDL_PROGRAMMING:
                if(socDriver_is_tx_idle() == TRUE)
                {           
                    tm_delay_us(20000);           
                    ret = swdl_data_handle();
                    switch(ret)
                    {
                        case ERR_OK:
                            pw_request_get_next_swdl_data();
                            getDataTimeout = 0;
							getDatacount=0;
                        break;
                        case ERR_SEVICE_NOT_READY:
                            if(getDataTimeout++>GET_DATA_TIME_OUT)
                            {
                                getDataTimeout= 0;
                                pw_request_get_cur_swdl_data(); 
								getDatacount ++;
                            }
							if(getDatacount>10)
							{
								Sys_Reset();
							}
                        break;
                        case ERR_RETRY:
                            pw_request_get_cur_swdl_data();  
                            getDataTimeout = 0;
                        break;
                        case ERR_FAILED:
                            UpgradeState[0] = eSocUpgradeState;
                            UpgradeState[1] = ret;
                            UpgradeState[2] = bFlashWriteTimeout;     
                            eSocUpgradeState = SWDL_ERROR;
                        break;
                        case ERR_FINISHED:
                            eSocUpgradeState = SWDL_PROGRAMM_COMPLETE;
                        break;   
                        default:break;
                    }
                }
                break;

            case SWDL_PROGRAMM_COMPLETE:
                //WATCHDOG_Disable();
                pw_request_to_exit_swdl();
                erase_swdl_mask();
                eSocUpgradeState = SWDL_DELAY_SLEEP;
                break;
                //we remove the "break" sentence,
                //in order to run as error
            case SWDL_DELAY_SLEEP:
                tm_delay_us(20000);
                eSocUpgradeState = SWDL_SUCCESS;
                break;
            case SWDL_SUCCESS:		
			//	for(;i<300;i++)
			//	{
			//		tm_delay_us(20000);
			//	}
			//	Sys_Reset();// xjy_test
                break;                
            case SWDL_ERROR:
				pw_mcu_send_update_status();
                tm_delay_us(20000);
				Sys_Reset();
                break;
            default:
                break;                                 
         }               
}


/***********************************************************************
*  Name        : erase_swdl_mask
*  Description : NA.  
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void erase_swdl_mask(void)
{
        bl_Buffer_t test[4] = {0xaa,0xaa,0xaa,0xaa};
        if(BL_upgrade_type ==UPGRADE_BY_SPI)
        {
            FLS_u8WriteDataByByte( 0xff200000, 0x04, test);
        }
}


/*****************************************************************************
*  Name        : request_soc_enter_swdl
*  Description : 
*  Parameter   : None
*  Returns     : None
*****************************************************************************/
void request_soc_enter_swdl(void)
{
    U8 navi_msg;
    
    navi_msg = ENTER_SWDL; 	
    SocManager_SendMsg(TYPE_SERVICE,RADIO_DISPATCH_SWDL_ENTER_EXIT,1,&navi_msg);
    bPowerUpOK = TRUE;	
}
/*****************************************************************************
*  Name        : pw_request_get_next_swdl_data
*  Description : 
*  Parameter   : None
*  Returns     : None
*****************************************************************************/
void pw_request_get_next_swdl_data(void)
{
    U8 navi_msg;
    
    navi_msg = NEXT_FRAME; 	
    SocManager_SendMsg(TYPE_SERVICE,RADIO_DISPATCH_SWDL_GET_DATA,1,&navi_msg);
}

/*****************************************************************************
*  Name        : pw_request_get_cur_swdl_data
*  Description : 
*  Parameter   : None
*  Returns     : None
*****************************************************************************/
void pw_request_get_cur_swdl_data(void)
{
    U8 navi_msg;

    navi_msg = CURR_FRAME; 	
    SocManager_SendMsg(TYPE_SERVICE,RADIO_DISPATCH_SWDL_GET_DATA,1,&navi_msg);
}

/*****************************************************************************
*  Name        : pw_request_to_exit_swdl
*  Description : 
*  Parameter   : None
*  Returns     : None
*****************************************************************************/
void pw_request_to_exit_swdl(void)
{
    U8 navi_msg;
    navi_msg = EXIT_SWDL; 	
    SocManager_SendMsg(TYPE_SERVICE,RADIO_DISPATCH_SWDL_ENTER_EXIT,1,&navi_msg);
}

/*****************************************************************************
*  Name        : pw_mcu_send_update_status
*  Description : 
*  Parameter   : None
*  Returns     : None
*****************************************************************************/
void pw_mcu_send_update_status(void)
{
    SocManager_SendMsg(TYPE_SERVICE,RADIO_DISPATCH_SWDL_UPDATE_STATUS,3,UpgradeState);
}

/***********************************************************************
*  Name        : Dispatcher_RepMsg
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
unsigned char version[50];
unsigned version_size=0;
void SocManager_Dispatcher_Msg(U8 cmpt_id,U16 commandid, U8 size, U8* data)
{
    if(CMPT_ID_OOM ==cmpt_id)
    {      
        switch(commandid)
        {
            case NAVI_CURRENT_POWER_SATET : // 0x5401
                if(SOC_NORMAL_STATE == data[0])//03
                {
                    request_soc_enter_swdl();
                }
            break;

            case NAVI_REQ_TO_RESET_EVENT://0x5414
                bJ6RequestToReset = TRUE;
	     break;

            case NAVI_SWDL_STATUS_EVENT://0x5413
                if(SWDL_MCU == data[0])
                {
                    if(SWDL_STATE_END == data[1])
                    {
                        eSocUpgradeState = SWDL_PROGRAMM_COMPLETE;
                    }                    
                }                
            break;

            case NAVI_START_END_SWDL_FILE_EVENT://0x5411            
                if(data[0]==START_READ_FILE)
                {
                    pw_request_get_next_swdl_data();
                    eSocUpgradeState = FC_CHECK_FIRST_ROW_VALID;    
                }
                else if(data[0]==END_READ_FILE)
                {
                    eSocUpgradeState = SWDL_PROGRAMM_COMPLETE;
                }
            break;

            case NAVI_SWDL_DATA_EVENT://0x5412
                if((size==0)||(size>=SWDL_FRAME_LEN+1))
                {
                    eSocUpgradeState = SWDL_ERROR;    
                    break;
                }
		#ifdef UPDATE_DATA_SHIFTING
                NotifyUpgradeDataReceived(size-1,data);  //uida3914 modified on 2016-10-10
		#else
		NotifyUpgradeDataReceived(size-1,data);
		#endif /* UPDATE_DATA_SHIFTING */
            break;

            case NAVI_GET_RADIO_STATUS://0x5201
            case NAVI_SELF_UPGRADE_RESULT_EVENT://0x5415
            break;

            case J6_SEND_RESPONSE_OF_VERSION:
            break;

			case RADIO_SEND_RECV_J6_FILERESULT_RESP :
				upgrade_finish=1;
				soc_set_timer_evt=TRUE;
				if(data[0]==0)
				{
					//application_invalue_flag = FALSE;
					updating_soc_success = TRUE;
				}
			break;
				
        	case RADIO_RECV_J6_RESET_ACK :
				 J6_ENTER_FAILSET=TRUE;
				 if(data[2]==1)
				 {
					upgrade_finish=1;
					soc_set_timer_evt=TRUE;	
				 }
			break;
			
            default:
            break;
        }
    }
    else if(CMPT_ID_SYSTEM == cmpt_id)
    {
    }
    else if(CMPT_ID_EOL == cmpt_id)
    {

	switch(commandid)
		  {
			case J6_SEND_RESPONSE_OF_VERSION :
			  	  version_size=size-3;
				  for(i=0;i<version_size;i++)
					version[i]=data[i+2];
				  
			if(version_size < max_version_length) {
				for(i=version_size;i<max_version_length;i++)
					version[i]='\0';
			}
			  break;
		}

    }
    else if(CMPT_ID_COMMONINFO == cmpt_id)
    {
    }
}


/**************** END OF FILE *****************************************/


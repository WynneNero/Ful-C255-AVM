/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD  NJ                                    *
*   AUTHOR     :                                       *
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   :
*-----------------------------------------------------------------------
* Version:0.1
* Date:2016/9/2
* Author:ShangQIuju
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date         Name            Changes and comments
------------------------------------------------------------------------
*  0.1          2016.9.2     ShangQiuju     Init version.
------------------------------------------------------------------------
*  0.2	    2016.10.12  ShangQiuju     Add handler of Swdl status event.
                  when receive Swdl status event don't reset mcu,wait reset
		    request from soc.
------------------------------------------------------------------------
*  0.3         2016.12.26   ShangQiuju    For interface is updated in FDL complex driver,so 
                 update using interface in app.
------------------------------------------------------------------------
*  0.4         2017.1.3   ShangQiuju    Update for fuction translation.
------------------------------------------------------------------------
*  0.5         2017.1.14   ShangQiuju    Add UPGRADE_FLAG_ADDRESS for Hal DEV update.
*----------------------------------------------------------------------
*  0.6         2017.3.13   ShangQiuju     Remove ununsed test function, and eol spi upgrade test function.
*=====================================================================*/
#include "config.h"
#include "define.h"
#include "SocManager.h"
#include "TYPES.h"
#include "Signal_if.h"
#include "Upgrade.h"
#include "Hal_if.h"
#include "ComplexDrvier_Globaldef_IF.H"
#include "GPIO_if.h"


void UpgradeMcuReqHandler(void);
BOOL bSwdlStatusEventOn = FALSE;
extern BOOL SOC_WATCHDOG_SWITCH;
/***********************************************************************
*  Name        : Upgrade_DISPATCHERMSG
*  Description : handle upgrade spi message.        
*  Parameter   : commandid,data
*  Returns     : None
***********************************************************************/
void Upgrade_DISPATCHERMSG(U16 commandid, U8* data)
{
    switch(commandid)
    {
        case NAVI_SWDL_CONFIG_EVENT://0x5410
            if(data[0]&MCU_SW_UPDATE)
            {
                bSwdlStatusEventOn = FALSE;
                UpgradeMcuReqHandler();
            }
        break;
        case NAVI_SWDL_STATUS_EVENT://0x5413
            if((data[0]==SWDL_RADIO)&&(data[1]==SWDL_STATE_START))
            {
                bSwdlStatusEventOn = TRUE;
                UpgradeMcuReqHandler();
            }
			if((data[0]==SWDL_OS)&&(data[1]==SWDL_STATE_START))
			{
				SOC_WATCHDOG_SWITCH = FALSE;
			}		
			if((data[0]==SWDL_OS)&&(data[1]==SWDL_STATE_END))
			{
				SOC_WATCHDOG_SWITCH = TRUE;
			}
			if((data[0]==SWDL_SLEEP)&&(data[1]==SWDL_STATE_START))
			{
				SOC_SLEEP_SWITCH = FALSE;
			}
        break;
    }
}

/***********************************************************************
*  Name        : UpgradeMcuReqHandler
*  Description : set upgrade flag at fdl address 0xFF200000-0xff200040      
*  Parameter   : None
*  Returns     : None
***********************************************************************/
 void UpgradeMcuReqHandler(void)
{	
//    U32 upgradeFlag = 0x5AA55AA5;
//    U32 readData = 0;

//    if(ERR_OK == HALBlock_Write(DEV_FDL,UPGRADE_FLAG_ADDRESS,(U8*)&upgradeFlag,UPGRADE_FLAG_LEN_OF_WORD))
//    {
//        if(UPGRADE_FLAG_LEN_OF_WORD == HALBlock_Read(DEV_FDL,UPGRADE_FLAG_ADDRESS, (U8*)&readData,UPGRADE_FLAG_LEN_OF_WORD))
//        {
//           if(readData == upgradeFlag)
//           {
//                if(bSwdlStatusEventOn)
//                {
//                    bSwdlStatusEventOn = FALSE;
//                }
//           }
//        }
//     }

	U8 upgradeFlag[UPGRADE_FLAG_LEN] = {0xaa,0x55,0x55,0xaa};
	U8 readData[UPGRADE_FLAG_LEN];
	if(ERR_OK == HAL_Write(DEV_FDL,upgradeFlag,UPGRADE_FLAG_LEN))
	{
		if(HAL_Read(DEV_FDL, readData,UPGRADE_FLAG_LEN))
		{
		   if(0 ==	_memcmp(readData,upgradeFlag, UPGRADE_FLAG_LEN))
		   {
				if(bSwdlStatusEventOn)
				{
					bSwdlStatusEventOn = FALSE;
					OSWDG_SoftReset();
					POWER_PMIC_OFF();
			
				}
		   }
		}
	 }

}
  

/**************** END OF FILE *****************************************/


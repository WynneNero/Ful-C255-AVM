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
* ----------------------------------------------------------------------
* 0.1  Mar 01,2013  NI Rujin    Initial version
* ----------------------------------------------------------------------
* 0.2  Jul 10,2013  SHANG Qiuju Add Navi event handler
* ----------------------------------------------------------------------
* 0.3  Aug 06,2013  NI Rujin    Update code to get GPS info
-----------------------------------------------------------------------
* 0.4  Sep 22,2013 ShangQiuju Remove Navi event handler
-----------------------------------------------------------------------
* 0.5  Feb 20,2014 LIU Chenxi Update version information for CHB022
-----------------------------------------------------------------------
* 0.6  May 20,2014 WANG Yong  Add firmware update feature
-----------------------------------------------------------------------
* 0.7  May 29,2014 LIU Chenxi  Fix overflow issue in HB message
-----------------------------------------------------------------------
* 0.8  May 30,2014 ShangQiuju  Add new service related with debug mode and
       fix issues found during code review.
-----------------------------------------------------------------------
* 0.9  Jul 29,2014 LIU Chenxi  Check modem manager regist status before
       Open USB channel.
-----------------------------------------------------------------------
* 1.0  Nov 13,2014 LIU Chenxi  Merge HZH code: Get O2 encrypted GPS data
       from HU side.
*=====================================================================*/

#include "TYPES.H"
#include "NaviApp.h"
#include "SocCommunicator.H"


extern void navi_req_sw_version(void);



#pragma ghs section rodata = ".myconst"
const U8 SoftVersion[24]={"C095-S_M220128_000018"};
U8 HardVersion[24]={"000        "};
U8 SW_VERSION_LEN =21;
#pragma ghs section data = default



void SocNavi_20ms_Entry(void)
{
	navi_req_sw_version();
}


BOOL bJ6RequestM3Version=FALSE;
void navi_req_sw_version(void)
{
    if(bJ6RequestM3Version)
    {
        bJ6RequestM3Version = FALSE;    
		SocManager_SendMsg(LQ_CMD,TYPE_RESPONSE,SEND_SOFT_VERSION_TO_SOC, SW_VERSION_LEN,SoftVersion);
	}
}
void NaviApp_GetM3SoftVersion(U8* version)
{
    _memcpy(version ,(U8*)SoftVersion,SW_VERSION_LEN);
}






/**************** END OF FILE *****************************************/


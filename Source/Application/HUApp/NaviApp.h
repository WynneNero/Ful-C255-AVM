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
-----------------------------------------------------------------------
* 0.1  Nov 13,2014 LIU Chenxi  Merge HZH code: Get O2 encrypted GPS data
       from HU side.
*=====================================================================*/
#ifndef _NAVIAPP_H_
#define _NAVIAPP_H_

extern BOOL bJ6RequestM3Version;
extern void SocNavi_20ms_Entry(void);
extern void NaviApp_GetM3SoftVersion(U8* version);

#define BOOTLOADER_VERSION_ADDRESS   (0x00017FE0UL)
#define BOOTLOADER_VERSION_LENGTH    (12u)

extern const U8 SoftVersion[];
extern U8 HardVersion[];
#endif /*_NAVIAPP_H_*/

/****************************** END OF FILE ***************************/


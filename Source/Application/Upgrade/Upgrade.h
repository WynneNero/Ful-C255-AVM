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
* Version       Date        Name            Changes and comments
 ----------------------------------------------------------------------
*  0.1          2016.9.2    ShangQiuju     Init version.
 ----------------------------------------------------------------------
*  0.2          2016.12.26 ShangQiuju     Move UPGRADE_FLAG_LEN_OF_WORD define from upgrade.c
*=====================================================================*/
#ifndef _UPGRADE_H_
#define _UPGRADE_H_

enum SWDL_STATUS_EVENT_STATE_PARAM
{
    SWDL_STATE_START,
    SWDL_STATE_END,
};

#define MCU_SW_UPDATE     0x01
#define UPGRADE_FLAG_LEN_OF_WORD 1
#define UPGRADE_FLAG_LEN 4

extern void Upgrade_DISPATCHERMSG(U16 commandid, U8* data);
#endif /*_UPGRADE_H_*/

/****************************** END OF FILE ***************************/


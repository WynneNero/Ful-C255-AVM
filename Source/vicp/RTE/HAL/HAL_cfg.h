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
*-----------------------------------------------------------------------
* 0.1  Aug 11,2016  LIU Chenxi  Initial version
*-----------------------------------------------------------------------
* 0.2  Jan 01,2017   ShangQiuju remove unused include file.
*------------------------------------------------------------------------
* 0.3  Jan 24,2017    ZhangJie  Fix Coverity warnings.
*------------------------------------------------------------------------
* 0.4  Feb 04,2017    Pei Jingli  Add device DEV_PWMD_HW,i.e hardware pwm function 
* ----------------------------------------------------------------------
* 0.5  Feb 15,2017  ShangQiuju Remove devie fdl from dev to devblock.  
* ----------------------------------------------------------------------
* 0.6    Feb 20,2017    PEI Jingli     Add device of TAU-Pwm,capture, timer 
* ----------------------------------------------------------------------
* 0.7  Feb 20,2017    ZhangJie     Add device of CAN.
*=====================================================================*/
/**** Definition of constants ****/
/**** Definition of macros ****/
/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/
BEGIN_DEV
//Global name, soure name, signal type
DEVDESC(DEV_SOC)
DEVDESC(DEV_PWMD_HW)
DEVDESC(DEV_PWM_TAU)
DEVDESC(DEV_CAPTURE)
DEVDESC(DEV_HW_TIMER)
DEVDESC(DEV_CANDRIVER)
#ifdef EOL_OPTION
DEVDESC(DEV_EOLDRIVER)
#endif
DEVDESC(DEV_FDL)
DEVDESC(DEV_M4DRIVER)

END_DEV

#undef  BEGIN_DEV
#undef  END_DEV
#undef  DEVDESC

BEGIN_DEVBLOCK
/*Global name, soure name, signal type*/

//DEVBLOCKDESC(DEV_FDL)
END_DEVBLOCK

#undef  BEGIN_DEVBLOCK
#undef  DEVBLOCKDESC
#undef  END_DEVBLOCK

/****************************** END OF FILE ***************************/


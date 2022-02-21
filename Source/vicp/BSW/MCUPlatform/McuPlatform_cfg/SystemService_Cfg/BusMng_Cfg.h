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
* 
*=====================================================================*/
/**** Definition of constants ****/

/**** Definition of macros ****/
BEGIN_BUSDESCS
	BUSDESC(E_BUS_IIC6)
	BUSDESC(E_BUS_SPI0)
END_BUSDESCS

#undef BEGIN_BUSDESCS
#undef BUSDESC
#undef END_BUSDESCS


BEGIN_DEVDESCS
	DEVDESC(E_DEV_CODEC,E_BUS_IIC6)
	DEVDESC(E_DEV_EEPROM,E_BUS_IIC6)
END_DEVDESCS

#undef BEGIN_DEVDESCS
#undef DEVDESC
#undef END_DEVDESCS
/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/
/****************************** END OF FILE ***************************/


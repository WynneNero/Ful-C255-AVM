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
*------------------------------------------------------------------------
* 0.1	   Jun 26,2016                               Initial version
*------------------------------------------------------------------------
* 0.2	   Jan 10,2017      ZhangJie           Change function parameter to solute Coverity warning.
*------------------------------------------------------------------------
* 0.3	   Jan 15,2017      ShangQiuju       Fdl device change from dev from devblock.
*-----------------------------------------------------------------------
* 0.4	   Mar 17,2017      Pei Jingli          Fix interface names for eep-driver changing.
*=====================================================================*/
#ifndef _EEPDRIVER_IF_H_
#define _EEPDRIVER_IF_H_
#include "EEPDriver_eel.h"

/**** Definition of constants ****/


/**** Declaration of constants ****/
/**** Declaration of variables ****/
/**** Declaration of functions ****/
extern BOOL EEPdriver_Init(void);
extern BOOL EEPdriver_DeInit(void);
/* interface for eel data sets access */
extern BOOL EEPdriver_Write(U16 DSid,U8 length, U8* write_buffer);
extern BOOL EEPdriver_Read(U16 DSid,U8 length, U8* read_buffer);
/* interface for fdl direct-address access */
extern BOOL FDdriver_WriteDirect(U16 address,U8 length, U32* write_buffer);
extern BOOL FDdriver_ReadDirect(U16 address,U8 length, U32* read_buffer);
extern BOOL FDdriver_EraseDirect(U16 blockId, U16 Cnt);

extern U8 FDLDriver_Write( U32 address ,U8* buffer, U16 wordNum);
extern U8 FDLDriver_Read( U32 address ,U8* buffer, U16 wordNum);
extern U8 FDLDriver_Write_Upgrade_flag( U8* buffer, U16 Len);
extern U8 FDLDriver_Read_Upgrade_flag( U8* buffer, U16 Len);

extern BOOL FDdriver_BlackCheck(U16 address,U8 length);

#endif /*_EEPDRIVER_IF_H_*/

/****************************** END OF FILE ***************************/


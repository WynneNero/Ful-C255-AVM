/**************************** .FILE_HEADER_BEGIN *****************************
  .TITLE: System General include files Module                            
*-----------------------------------------------------------------------------
  .FILE:General.h      
  .AUTHOR:Tan, fumin
*-----------------------------------------------------------------------------

 Date        Author                       Change
 -----------------------------------------------------------------------------
2012.10.15  Tan, fumin		   :create this module                      

*****************************************************************************/
#ifndef __GENERAL_H__
#define __GENERAL_H__

/*including hal layer interface head file*/
//#include "HAL.h"

#include <string.h>

#include "stddef.h"
#include "math.h"
//#include "limits.h"
#include "stdlib.h"
#include "Std_Types.h"

//#include "OS_frame1C1.h"
 
/*add the neccesary head file here*/

#define COMPILER_GHS	1
#define COMPILER_CS_puls	2

#define USING_COMPILER COMPILER_GHS

#define HW_VERSION_INTERNAL		0x2100/*C1.0*/
#define SW_VERSION_INTERNAL		0x0100/*A1.0*/
#define SW_VERSION_DATE			0x10010E

/*B2.10 integrating the chamber data for geely 9.20sample 20150914*/
/*B2.11 integrating the Accc chamber data for geely 9.20sample 20150915*/
/*B2.12 Repaird Blower speed on Rec control status for geely 9.20sample 20150917*/
/*B2.13 integrating DTC and desc 20150930*/
/*B2.14 integrating LinAppl(for ErrorCode) 20151008*/
/*B2.15 integrating HCT ErrorCode 20151009*/
/*B2.16 save OAT data*/
/*B2.17 debug 20151021*/
/*C1.0 debug 20151021*/
/*C1.1 Update the OAT module 20151023*/
/*C1.2 Update the Desc module 20151023*/
/*C1.3 changes requirement that Open AC in DEF mode when setTemp=HI 20151105*/
/*C1.4 Repaired bug that Def telltales on OFF mode 20151127*/
/*C1.5 change to OAT pretect value for ACC 20151203*/
/*C1.5 change to the PTC and water bump turn off delay time 20151203*/
/*C1.6 Avoid the AC speed in [4200,4400] 20151203*/
/*C1.6 Limited the AC speed in blower manual mode 20151203*/
/*C1.6 repaired the cool start bug, reset counld not check the cool start curve 20151208*/
/*C1.7 communication delay 1second before Main relay turn off after IG power OFF 20151214*/
/*FE-3HP*/
/*A1.0 created the first version with battery manage function 20160114*/

#endif


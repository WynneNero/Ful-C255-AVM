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
*----------------------------------------------------------------------
* 0.1  Mar 07,2017    PEI Jingli   Fix headfile included.
*=====================================================================*/
#include "Define.h"

/*******************************************************************************************
* Description of Behaviour:
* This function will call all the functions that addresses are stored in the array that is 
* handed over. The function starts with the first entry. The last entry in the array must be 
* a Null pointer to indicate the end of the array. 
*
* After each called function the function SysHw_Schedule is called.
* 
* Parameters:
* ContainerArray: Pointer to the array whose entries are to be executed.
* 
* Return Value  (Value Type Range):
* none
*   
********************************************************************************************/
void Lib_RunContainer( Func_Void_Proc* ContainerArray)
{
    /***************************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local ROM-constants
    * - all function local variables (auto and static)
    ****************************************************************************************/

    /***************************************************************************************
    * FUNCTION CODE
    ****************************************************************************************/
    
    while (*ContainerArray != NULL)
    {
        (*ContainerArray)(); /* Execute the functions pointed by the function pointers */
        ContainerArray++;
    }
}


/*******************************************************************************************
* Description of Behaviour:
* This function will call all the functions that addresses are stored in the array that is 
* handed over. The function starts with the first entry. The last entry in the array must be 
* a Null pointer to indicate the end of the array. 
*
* After each called function the function SysHw_Schedule is called.
* 
* Parameters:
* ContainerArray: Pointer to the array whose entries are to be executed.
* 
* Return Value  (Value Type Range):
* none
*   
********************************************************************************************/
void Lib_RunParamContainer(Func_Param16_Proc* ContainerArray, U16 param)
{
    /***************************************************************************************
    * FUNCTION LOCAL DEFINITIONS
    *
    * In this section define
    * - all function local type definitions
    * - all function local ROM-constants
    * - all function local variables (auto and static)
    ****************************************************************************************/

    /***************************************************************************************
    * FUNCTION CODE
    ****************************************************************************************/
    
    while (*ContainerArray != NULL)
    {
        (*ContainerArray)(param); /* Execute the functions pointed by the function pointers */
        ContainerArray++;
    }
}

/**************** END OF FILE *****************************************/


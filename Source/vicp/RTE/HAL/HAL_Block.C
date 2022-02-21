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
* 0.1    Jun 26,2016                      Initial version
* ----------------------------------------------------------------------
* 0.2    Jan 04,2017   ShangQiuju  Change function HALBlock_DevPowerIsStatus to 
                                                  HALBlock_DevGetPowerStatus
*------------------------------------------------------------------------
* 0.3    Jan 24,2017  ZhangJie  Fix Coverity warnings.
*=====================================================================*/
#include "hal.h"

extern const V_hal_block_open HalBlockOpenProc[HAL_BLDEV_MAX];
extern const V_hal_block_close  HalBlockCloseProc[HAL_BLDEV_MAX];
extern const V_hal_block_read HalBlockReadProc[HAL_BLDEV_MAX];
extern const V_hal_block_write  HalBlockWriteProc[HAL_BLDEV_MAX];
extern const V_hal_block_iocontrol HalBlockiocontrolProc[HAL_BLDEV_MAX];
extern const V_hal_block_powercontrol HalBlockPowerControlProc[HAL_BLDEV_MAX];
extern const V_hal_block_powerstatus HalBlockPowerStatusProc[HAL_BLDEV_MAX];

/*---Global-----------------------------------------------------------*/
/***********************************************************************
*  Name        : HALBlock_Init
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void HALBlock_Init(void)
{

}

/***********************************************************************
*  Name        : HALBlock_DeInit
*  Description :        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void HALBlock_DeInit(void)
{

}

/***********************************************************************
*  Name        : HALBlock_Open
*  Description : open dev         
*  Parameter   : DeviceId
*  Returns     : U8
***********************************************************************/
U8 HALBlock_Open(U8 DeviceId)
{
    U8 ret =(U8)ERR_FAILED;
    if(((U8)E_DEVBLOCK_NUM>0u)&&(DeviceId<(U8)E_DEVBLOCK_NUM)&&(HalBlockOpenProc[DeviceId]!=NULL))
    {
        ret =HalBlockOpenProc[DeviceId]();
    }
    else
    {
        /*nothing to do.*/
    }
    return ret;
}

/***********************************************************************
*  Name        : HAL_Close
*  Description : close dev        
*  Parameter   : DeviceId
*  Returns     : U8
***********************************************************************/
U8 HALBlock_Close(U8 DeviceId)
{
    U8 ret=(U8)ERR_FAILED;
    if(((U8)E_DEVBLOCK_NUM>0u)&&(DeviceId<(U8)E_DEVBLOCK_NUM)&&(HalBlockCloseProc[DeviceId]!=NULL))
    {
        ret =HalBlockCloseProc[DeviceId]();
    }
    else
    {
        /*nothing to do.*/
    }
    return ret;
}

/***********************************************************************
*  Name        : HALBlock_Read
*  Description :         
*  Parameter   : DeviceId,address,buffer,Len
*  Returns     : U8
***********************************************************************/
U8 HALBlock_Read(U8 DeviceId, U32 address,U8* buffer, U16 Len)
{
    U8 ret=0u;
    if(((U8)E_DEVBLOCK_NUM>0u)&&(DeviceId<(U8)E_DEVBLOCK_NUM)&&(HalBlockReadProc[DeviceId]!=NULL))
    {
        ret =HalBlockReadProc[DeviceId](address,buffer, Len);
    }
    else
    {
        /*nothing to do.*/
    }
    return ret;
}

/***********************************************************************
*  Name        : HALBlock_Write
*  Description :        
*  Parameter   : DeviceId,address,buffer,len
*  Returns     :U8
***********************************************************************/
U8 HALBlock_Write(U8 DeviceId, U32 address,U8* buffer, U16 Len)
{
    U8 ret=(U8)ERR_FAILED;
    if(((U8)E_DEVBLOCK_NUM>0u)&&(DeviceId<(U8)E_DEVBLOCK_NUM)&&(HalBlockWriteProc[DeviceId]!=NULL))
    {
        ret =HalBlockWriteProc[DeviceId](address,buffer, Len);
    }
    else
    {
        /*nothing to do.*/
    }
    return ret;
}

/***********************************************************************
*  Name        : HALBlock_IoControl
*  Description :         
*  Parameter   : DeviceId,Type,buffer
*  Returns     : U8
***********************************************************************/
U8 HALBlock_IoControl(U8 DeviceId, U8 type, void* buffer)
{
    U8 ret=(U8)ERR_FAILED;
    if(((U8)E_DEVBLOCK_NUM>0u)&&(DeviceId<(U8)E_DEVBLOCK_NUM)&&(HalBlockiocontrolProc[DeviceId]!=NULL))
    {
        ret =HalBlockiocontrolProc[DeviceId](type, buffer);
    }   
    else
    {
        /*nothing to do.*/
    }
    return ret;
}

/***********************************************************************
*  Name        : HALBlock_DevPowerControl
*  Description : control deve power        
*  Parameter   : DeviceId,Type
*  Returns     : None
***********************************************************************/
void HALBlock_DevPowerControl(U8 DeviceId,E_DEV_POWER type)
{
    if(((U8)E_DEVBLOCK_NUM>0u)&&(DeviceId<(U8)E_DEVBLOCK_NUM)&&(HalBlockPowerControlProc[DeviceId]!=NULL))
    {
        HalBlockPowerControlProc[DeviceId](type);
    }
    else
    {
        /*nothing to do.*/
    }
}

/***********************************************************************
*  Name        : HALBlock_DevGetPowerStatus
*  Description : Get dev status        
*  Parameter   : DeviceId
*  Returns     : U8
***********************************************************************/
U8 HALBlock_DevGetPowerStatus(U8 DeviceId)
{
    U8  type=(U8)E_DEV_MAX_STYPE;  
    if(((U8)E_DEVBLOCK_NUM>0u)&&(DeviceId<(U8)E_DEVBLOCK_NUM)&&(HalBlockPowerStatusProc[DeviceId]!=NULL))
    {
        type=HalBlockPowerStatusProc[DeviceId]();
    }
    else
    {
        /*nothing to do.*/
    }
    return type;
}

/***********************************************************************
*  Name        : V_hal_block_open_empty
*  Description :        
*  Parameter   :  None
*  Returns     : U8
***********************************************************************/
U8 V_hal_block_open_empty( void)
{
    return (U8)ERR_FAILED;
}

/***********************************************************************
*  Name        : V_hal_block_close_empty
*  Description :         
*  Parameter   : None
*  Returns     : U8
***********************************************************************/
U8 V_hal_block_close_empty( void)
{
    return (U8)ERR_FAILED;
}

/***********************************************************************
*  Name        : V_hal_block_read_empty
*  Description :         
*  Parameter   : address,buffer,len
*  Returns     : U8
***********************************************************************/
U8 V_hal_block_read_empty(U32 address, U8* buffer, U16 Len)
{
    return (U8)ERR_FAILED;
}

/***********************************************************************
*  Name        : V_hal_block_write_empty
*  Description :    
*  Parameter   : address,buffer,len
*  Returns     : U8
***********************************************************************/
U8 V_hal_block_write_empty(U32 address,  U8* buffer, U16 Len)
{
    return (U8)ERR_FAILED;
}

/***********************************************************************
*  Name        : V_hal_block_iocontrol_empty
*  Description :       
*  Parameter   : buffer,type
*  Returns     : U8
***********************************************************************/
U8 V_hal_block_iocontrol_empty( U8 type, void* buffer)
{
    return (U8)ERR_FAILED;
}


/***********************************************************************
*  Name        : V_hal_block_powercontrol_empty
*  Description :      
*  Parameter   : type
*  Returns     : None
***********************************************************************/
void V_hal_block_powercontrol_empty(U8 type)
{

}
/**************** END OF FILE *****************************************/


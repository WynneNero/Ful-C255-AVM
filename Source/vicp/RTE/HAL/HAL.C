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
* 0.2    Jan 04,2017   ShangQiuju  Change function HAL_DevPowerIsStatus to HAL_DevGetPowerStatus
*------------------------------------------------------------------------
* 0.3    Jan 24,2017      ZhangJie   Fix Coverity warnings.
*=====================================================================*/
#include "hal.h"

extern const V_hal_open HalOpenProc[HAL_DEV_MAX];
extern const V_hal_close  HalCloseProc[HAL_DEV_MAX];
extern const V_hal_read HalReadProc[HAL_DEV_MAX];
extern const V_hal_write  HalWriteProc[HAL_DEV_MAX];
extern const V_hal_iocontrol HaliocontrolProc[HAL_DEV_MAX];
extern const V_hal_powercontrol HalPowerControlProc[HAL_DEV_MAX];
extern const V_hal_powerstatus HalPowerStatusProc[HAL_DEV_MAX];
/*---Global-----------------------------------------------------------*/
/***********************************************************************
*  Name        : HAL_Init
*  Description :        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void HAL_Init(void)
{

}

/***********************************************************************
*  Name        : HAL_DeInit
*  Description :       
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void HAL_DeInit(void)
{

}

/***********************************************************************
*  Name        : HAL_Open
*  Description : open dev       
*  Parameter   : DeviceId
*  Returns     : U8
***********************************************************************/
U8 HAL_Open(U8 DeviceId)
{
    U8 ret =(U8)ERR_FAILED;
    if(((U8)E_DEV_NUM>0u)&&(DeviceId<(U8)E_DEV_NUM)&&(HalOpenProc[DeviceId]!=NULL))
    {
        ret =HalOpenProc[DeviceId]();
    }
    else
    {
        /*nothing to do*/
    } 
    return ret;
}

/***********************************************************************
*  Name        : HAL_Close
*  Description : close dev        
*  Parameter   : DeviceId
*  Returns     : U8
***********************************************************************/
U8 HAL_Close(U8 DeviceId)
{
    U8 ret=(U8)ERR_FAILED;
    if(((U8)E_DEV_NUM>0u)&&(DeviceId<(U8)E_DEV_NUM)&&(HalCloseProc[DeviceId]!=NULL))
    {
        ret =HalCloseProc[DeviceId]();
    }
    else
    {
        /*nothing to do*/
    }
    return ret;
}

/***********************************************************************
*  Name        : HAL_Read
*  Description : read dev       
*  Parameter   : DeviceId,buffer,len
*  Returns     : U8
***********************************************************************/
U8 HAL_Read(U8 DeviceId, U8* buffer, U16 Len)
{
    U8 ret=0u;
    if(((U8)E_DEV_NUM>0u)&&(DeviceId<(U8)E_DEV_NUM)&&(HalReadProc[DeviceId]!=NULL))
    {
        ret =HalReadProc[DeviceId](buffer, Len);
    }
    else
    {
        /*nothing to do*/
    }
    return ret;
}

/***********************************************************************
*  Name        : HAL_Write
*  Description : write dev        
*  Parameter   : DeviceId,buffer,len
*  Returns     : U8
***********************************************************************/
U8 HAL_Write(U8 DeviceId, U8* buffer, U16 Len)
{
    U8 ret=(U8)ERR_FAILED;
    if(((U8)E_DEV_NUM>0u)&&(DeviceId<(U8)E_DEV_NUM)&&(HalWriteProc[DeviceId]!=NULL))
    {
        ret =HalWriteProc[DeviceId](buffer, Len);
    }
    else
    {
        /*nothing to do*/
    }
    return ret;
}

/***********************************************************************
*  Name        : HAL_IoControl
*  Description :        
*  Parameter   : DeviceId,type,buffer
*  Returns     : U8
***********************************************************************/
U8 HAL_IoControl(U8 DeviceId, U8 type, void* buffer)
{
    U8 ret=(U8)ERR_FAILED;
    if(((U8)E_DEV_NUM>0u)&&(DeviceId<(U8)E_DEV_NUM)&&(HaliocontrolProc[DeviceId]!=NULL))
    {
        ret =HaliocontrolProc[DeviceId](type, buffer);
    }
    else
    {
        /*nothing to do*/
    }
    return ret;
}

/***********************************************************************
*  Name        : HAL_DevPowerControl
*  Description : control deve power        
*  Parameter   : DeviceId,Type
*  Returns     : None
***********************************************************************/
void HAL_DevPowerControl(U8 DeviceId,E_DEV_POWER type)
{
    if(((U8)E_DEV_NUM>0u)&&(DeviceId<(U8)E_DEV_NUM)&&(HalPowerControlProc[DeviceId]!=NULL))
    {
        HalPowerControlProc[DeviceId](type);
    }
    else
    {
        /*nothing to do*/
    }
}

/***********************************************************************
*  Name        : HAL_DevGetPowerStatus
*  Description : Get dev status        
*  Parameter   : DeviceId
*  Returns     : U8
***********************************************************************/
U8 HAL_DevGetPowerStatus(U8 DeviceId)
{
    U8 type =(U8)E_DEV_MAX_STYPE;
    if(((U8)E_DEV_NUM>0u)&&(DeviceId<(U8)E_DEV_NUM)&&(HalPowerStatusProc[DeviceId]!=NULL))
    {
        type=HalPowerStatusProc[DeviceId]();
    }
    else
    {
        /*nothing to do*/
    }
    return type;
}

/***********************************************************************
*  Name        : V_hal_open_empty
*  Description :         
*  Parameter   : None
*  Returns     : U8
***********************************************************************/
U8 V_hal_open_empty( void)
{
    return (U8)ERR_FAILED;
}

/***********************************************************************
*  Name        : V_hal_close_empty
*  Description :         
*  Parameter   : None
*  Returns     : U8
***********************************************************************/
U8 V_hal_close_empty( void)
{
    return (U8)ERR_FAILED;
}

/***********************************************************************
*  Name        : V_hal_read_empty
*  Description :         
*  Parameter   : buffer,len
*  Returns     : U8
***********************************************************************/
U8 V_hal_read_empty( U8* buffer, U16 Len)
{
    return (U8)ERR_FAILED;
}

/***********************************************************************
*  Name        : V_hal_write_empty
*  Description :         
*  Parameter   : buffer,len
*  Returns     : U8
***********************************************************************/
U8 V_hal_write_empty(  U8* buffer, U16 Len)
{
    return (U8)ERR_FAILED;
}

/***********************************************************************
*  Name        : V_hal_iocontrol_empty
*  Description :         
*  Parameter   : buffer,type
*  Returns     : U8
***********************************************************************/
U8 V_hal_iocontrol_empty( U8 type, void* buffer)
{
    return (U8)ERR_FAILED;
}

/***********************************************************************
*  Name        : V_hal_powercontrol_empty
*  Description :         
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void V_hal_powercontrol_empty(U8 type)
{

}
/**************** END OF FILE *****************************************/


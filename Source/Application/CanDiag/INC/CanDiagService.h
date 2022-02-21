/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   :            										   *
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
* Version       Date                Name            Changes and comments
* 0.1           2015/12/22    ShangQiiuju       init version
* 0.2           2017/02/07    ZhangJie            Reinit for vicp upgrade template.
*=====================================================================*/
#ifndef _CAN_DIAG_SERVICE_H_
#define _CAN_DIAG_SERVICE_H_
#include "config.h"
#include "CanDiagDtcCfg.h"

extern void CanAppGetSpeed(U8* data);
extern void CanAppGetEngStatus(U8* data);
extern void CanAppGetSpeed(U8* data);

typedef enum
{
   NONE_SOFT_TYPE,
   FAW_ECU_SOFT_TYPE,
   SUPPLIER_ECU_SOFT,
};

typedef  struct
{
    BOOL bReqSent;
    BOOL bRespReceived;
	U16 uRecvDatatime;
	U8 uSoftwareVersionType;
	U8 uReqVersionType;
	U8 uRespVersionType;
    U8 uRecvDatalen;
	U8 uReqNumber;
    U8 uRecvData[25];    
}E_QUERY_J6_VERSION_STRUCT;

typedef enum
{
   NONE_TYPE,
   VIEW_CONTROL,
   DYNAMICPGS_CONTROL,
}DIAG_IO_CONTROL_TYPE;

typedef enum
{
   NONECONTROL_TYPE,
   RETURNCONTROL_TYPE,
   CONTROL_TYPE,
}DIAG_IO_CONTROLPAR_TYPE;

typedef struct
{
    BOOL bReqSent;
    BOOL bRespReceived;
	
	DIAG_IO_CONTROL_TYPE bControlType;
	DIAG_IO_CONTROL_TYPE bRespControlType;
	DIAG_IO_CONTROLPAR_TYPE bControlParameterType;
	U16 uRecvDatatime;
	BOOL bControlState;
	BOOL bRespControlState;
	BOOL bBeenSend;
}E_IO_CONTROL_STRUCT;

typedef struct
{
    U32 uEepRetryAddr;
    U16 uEepRetryWordNum;
    U8 uEepRetryByte;
}CAN_EEP_RETRY_STRUCT;

#define CAN_UPGRADE_FLAG_LEN_OF_WORD 1

typedef void( *Camera_Switch_Proc)();
typedef U8( *Camera_Flag_Proc)();

extern void DiagRequest_Navi_handler(void);
extern void ClearDiagDtcData(void);
extern U8 uAVSCarModelColor;
extern U8 uAVSTransparency;
extern U8 uAVSViewMode;
extern U8 uAVSCalibrationSta;
extern U8 SCalibrationResult;
extern U8 SEnterEOLViewResult;

#endif

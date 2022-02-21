/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department :CT AD NJ                                           *
*   AUTHOR     :                                                       *
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
* 0.1  2014/4/11  Shang Qiuju      Initial version
*=====================================================================*/

#ifndef _DTC_H_
#define _DTC_H_
#include "config.h"
#include "EEPTable.h"
#include "canDiagDtcCfg.h"

/**** Definition of constants ****/
#define AD_CAMERA_OPEN_VALUE   		124 	/* =0.1*4096/3.3 */
//#define AD_CAMERA_NORMAL_MIN	   	745 	/* =0.6*4096/3.3 */
#define AD_CAMERA_NORMAL_MIN	   	372 	/* =0.3*4096/3.3 */   // For X1F camera
#define AD_CAMERA_NORMAL_MAX	   	1862    /* =1.5*4096/3.3 */
#define AD_CAMERA_SHORT_GND_MIN   	2979    /* =2.4*4096/3.3 */
#define AD_CAMERA_SHORT_GND_MAX   	3289    /* =2.65*4096/3.3 */
#define AD_CAMERA_SHORT_BAT_MIN   	3786    /* =3.05*4096/3.3 */
#define AD_CAMERA_SHORT_BAT_MAX   	4096    /* =3.3*4096/3.3 */



#define AD_LED_NORMAL_MAX    950  /* Actual:0.5V */
#define AD_LED_GND	         265  /* 0V */
#define AD_LED_NORMAL_MIN    950  /* Actual:0.5V*/

#ifdef DIAG_TEMPERATURE_OPTION
#define TEMP_NAV_TOO_HOT    (970*4096/(970+4700))   //100 degree
#define TEMP_CONFIRM_TIME     50*5   //5S
#define TEMP_RECOVERY_TIME   50*5   //5S
#define TEMP_NAV_TOO_COLD   (118596*4096/(118596+4700)) //-30 degree
#endif

#define POWER_ON_HK_CHECK_TIMES 750//t=750*20ms

enum 
{
    DTC_FRONT_CAMERA,
    DTC_LEFT_CAMERA,
    DTC_REAR_CAMERA,
    DTC_RIGHT_CAMERA,
    
	DTC_AVM_LED_STATUS,
		DTC_BUZZER,  //XJJ
    DTC_LED1,
    DTC_LED2,
		
    #ifdef DIAG_TEMPERATURE_OPTION
    DTC_TEMP,
    #endif
    DTC_MAX_NUM,
};

typedef struct 
{
    U8 dtc_create_cnt;
    U8 dtc_recover_cnt;
    BOOL berr;
}E_DTC_RECORD_STRUCT;

enum 
{
    DEVICE_NORMAL,
    DEVICE_OPEN,
    DEVICE_SHORT_TO_BAT,
	DEVICE_SHORT_TO_GND,
    DEVICE_UNKONN


};

enum
{
	LED_CHECK_NONE = 0x00,
	LED_ON_CHECK,
	LED_OFF_CHECK,
};

enum
{
    TEMP_NORMAL = DEVICE_NORMAL,
    TEMP_TOO_LOW = DEVICE_OPEN,
    TEMP_TOO_HOT=DEVICE_SHORT_TO_GND,
};

typedef struct _ALERT_STRUCT
{
    union
    {
        U16 faultu;
        struct
        {
            U16 front:2;
            U16 left:2;
            U16 rear:2;
            U16 right:2;
            U16 buzz:2;
            U16 led1:2;
            U16 led2:2;
            U16 unsed:2;            
        }faultb;
    }s2NaviDtc;
    
    union
    {
        U8 cameraf;
        struct
        {
            U8 front:1;
            U8 left:1;
            U8 rear:1;
            U8 right:1;    
            U8 unsed:4;                 
        }camerab;
    }s2CanDtc1;
    
    union
    {
        U8 ledf;
        struct
        {
            U8 led1:1;
            U8 led2:1;
            U8 unsed:6;                 
        }ledb;
    }s2CanDtc2;
    #ifdef CAN_DIAG_OPTION
    U8 canDiagDtcData[CANDTC_CIRCUIT_CHECK_TYPE_NUMBER];  
    #endif
}ALERT_STRUCT;

/**** Definition of types ****/
extern void Dtc_Init(void);
extern void Dtc_DeInit(void);
extern void Dtc_Main(void);
extern void CanApp_ReportDeviceDtc(U8 camerafault,U8 ledfault);
extern void CanApp_ReportDeviceDtcToCpu(U16 fault);
#ifdef CAN_DIAG_OPTION
extern BOOL Dtc_GetCanDiagDeviceDtc(U8* dtc);
extern BOOL Dtc_GetCanDiagTempDtc(U8* dtc);
#endif
#ifdef EOL_OPTION
extern BOOL Dtc_GetNaviDiagResult(U8* dtc);
#endif
#define Report_DeviceDTCtoCan(camerafault,ledfault)  CanApp_ReportDeviceDtc(camerafault,ledfault)
#define Report_DeviceDTCtoCPU(fault) CanApp_ReportDeviceDtcToCpu(fault)
#endif /*_DTC_H_*/



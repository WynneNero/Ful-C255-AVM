/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   		   *
*   AUTHOR	   : 									                   *
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
* Version   Date        Name             Changes and comments
* ----------------------------------------------------------------------
* 0.1    	20190501  	LUWEI			    Initial version
*=====================================================================*/
#define pi 3.1415926							//π
#define Rad_to_Ang 57.2957804					//弧度和角度转换系数
#define Ang_to_Rad 57.2957804					//弧度和角度转换系数
#define esc_factor 1							//轮速脉冲角度系数
#define yaw_factor 0							//偏航角度系数
#define sas_factor 0							//方向盘角度系数
#define yaw_cycle  0.02							//yaw更新周期
#define DR_ESC_PulseMax 1023					//轮速脉冲最大值
#define DR_ESC_PulseNum 75						//轮速脉冲齿数	    后轮75 ，前轮96
#define DR_ESC_WheelRadius 0.328				//滚动半径 
#define DR_ESC_CarWidth 1.545					//后轮轮距
#define DR_ESC_Wheelbase 2.700					//轴距
#define DR_Radio 16								//转向比


typedef struct
{
	unsigned short RRWheelSpeedRC;
	unsigned short RLWheelSpeedRC;
	unsigned char ModeGearDisplaySt;
	float Zerodrift;
	float YawRate;
	float VSpeed;
	float Saswheelsteerangle;
} ExtL_APSDR_T;

typedef struct
{
	float DRXPosition;
	float DRYPosition;
	float DRTheta;
} ExtW_APSDR_T;
extern ExtL_APSDR_T APSDR_L;
extern ExtW_APSDR_T APSDR_W;


extern void APSDR_init(void);
extern void APSDR_step(void);



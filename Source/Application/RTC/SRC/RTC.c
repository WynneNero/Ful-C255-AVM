/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   		   *
*   AUTHOR	   : 									   				   *
************************************************************************
* Object       : RTC
* Module       : RTC
* Instance     :
* Description  : Set and Send the calendar information.
*-----------------------------------------------------------------------
* Version	   : 0.1
* Date         : 2017/7/30
* Author       : ZhengXiaolei
***********************************************************************/
/*-History--------------------------------------------------------------
* Version   Date       Name           Changes and comments
* 0.1		2017/7/30  Zheng Xiaolei  Init Version.
* 0.2       2017/8/11  Zheng Xiaolei  Add RTC module init time delay.
*=====================================================================*/
#include "config.h"
#include "Define.h"
#include "IIC_if.H"
#include "SocManager.h"
#include "RTC.h"
#include "RTC_IF.h"
#include "SocMsg_Cfg.h"

RTC_DATA_TYPE RTC_data;
U8 RTCPowerOnFlag;


/*******************************************************************************
**  FUNCTION      : RTC_Init
**  DESCRIPTION   : 
**  PARAMETERS    : void
**  RETURN        : void
*******************************************************************************/
void RTC_Init(void)
{
	IICMasterWriteReg(BAUD_100K, ADDR_RTC, 0x00, 0x00);
	IICMasterWriteReg(BAUD_100K, ADDR_RTC, 0x01, 0x00);	
}

/*******************************************************************************
**  FUNCTION      : RTC_PowerOn_Init
**  DESCRIPTION   : 
**  PARAMETERS    : void
**  RETURN        : void
*******************************************************************************/
void RTC_PowerOn_Init(void)
{
	RTCPowerOnFlag = TRUE;
}

/*******************************************************************************
**  FUNCTION      : RTC_Init
**  DESCRIPTION   : 
**  PARAMETERS    : void
**  RETURN        : void
*******************************************************************************/
void Calendar_Init(void)
{
	RTC_data.year = 0x17;
	RTC_data.month = 0x01;
	//RTC_data.week = 0x00;
	RTC_data.date = 0x01;
	RTC_data.hour = 0x00;
	RTC_data.minute = 0x00;
	RTC_data.second = 0x00;

	IICMasterWriteReg(BAUD_100K, ADDR_RTC, REG_YEAR, RTC_data.year);	
	IICMasterWriteReg(BAUD_100K, ADDR_RTC, REG_MONTH, RTC_data.month);		
	//IICMasterWriteReg(BAUD_100K, ADDR_RTC, REG_WEEK, RTC_data.week);	
	IICMasterWriteReg(BAUD_100K, ADDR_RTC, REG_DAY, RTC_data.date);	
	IICMasterWriteReg(BAUD_100K, ADDR_RTC, REG_HOUR, RTC_data.hour);	
	IICMasterWriteReg(BAUD_100K, ADDR_RTC, REG_MINUTE, RTC_data.minute);		
	IICMasterWriteReg(BAUD_100K, ADDR_RTC, REG_SECOND, RTC_data.second);	
}


U8 PowerOnDelayCnt;
/*******************************************************************************
**  FUNCTION      : Calendar_PowerOn_Handler
**  DESCRIPTION   : 
**  PARAMETERS    : void
**  RETURN        : void
*******************************************************************************/
void Calendar_PowerOn_Handler(void)
{
	if(RTCPowerOnFlag == TRUE)
	{		
		PowerOnDelayCnt++;
		if(PowerOnDelayCnt>RTC_MODULE_INIT_TIME)
		{
			Calendar_Init();
			RTCPowerOnFlag = FALSE;
			PowerOnDelayCnt=0;
		}
	}
}

/*******************************************************************************
**  FUNCTION      : Calendar_Get
**  DESCRIPTION   : 
**  PARAMETERS    : void
**  RETURN        : void
*******************************************************************************/
RTC_DATA_TYPE Calendar_Get(void)
{
	RTC_DATA_TYPE calendar;
	U8 data[6] = {0};
	calendar.year = IICMasterReadReg(BAUD_100K, ADDR_RTC, REG_YEAR);
	calendar.month = IICMasterReadReg(BAUD_100K, ADDR_RTC, REG_MONTH);
	/*calendar.week = IICMasterReadReg(BAUD_100K, ADDR_RTC, REG_WEEK);*/
	calendar.date = IICMasterReadReg(BAUD_100K, ADDR_RTC, REG_DAY);
	calendar.hour = IICMasterReadReg(BAUD_100K, ADDR_RTC, REG_HOUR);
	calendar.minute = IICMasterReadReg(BAUD_100K, ADDR_RTC, REG_MINUTE);
	calendar.second = IICMasterReadReg(BAUD_100K, ADDR_RTC, REG_SECOND);

	calendar.year = calendar.year & 0xff;
	calendar.month = calendar.month & 0x1f;
	/*calendar.week = calendar.week & 0x07;*/
	calendar.date = calendar.date & 0x3f;
	calendar.hour = calendar.hour & 0x3f;
	calendar.minute = calendar.minute & 0x7f;
	calendar.second = calendar.second & 0x7f;

	data[0] = calendar.hour;
	data[1] = calendar.minute;
	data[2] = calendar.second;	
	data[3] = calendar.year;
	data[4] = calendar.month;
	data[5] = calendar.date;
	/*data[6] = calendar.week;*/
	BCD2Hex((U8*)&data);
	calendar.hour = data[0];
	calendar.minute = data[1];
	calendar.second = data[2];
	calendar.year = data[3];
	calendar.month = data[4];
	calendar.date = data[5];
	/*calendar.week = rsl[6];*/
	return calendar;
}

/*******************************************************************************
**  FUNCTION      : Calendar_Set
**  DESCRIPTION   : 
**  PARAMETERS    : void
**  RETURN        : void
*******************************************************************************/
void Calendar_Set(RTC_DATA_TYPE *time)
{
	U8 recdata[6] = {0};
	recdata[0] = time->year;
	recdata[1] = time->month;
	/*recdata[2] = time->week;*/
	recdata[2] = time->date;
	recdata[3] = time->hour;
	recdata[4] = time->minute;
	recdata[5] = time->second;
	Hex2BCD((U8*)&recdata);
	RTC_data.year = recdata[0];
	RTC_data.month = recdata[1];
	/*RTC_data.week = recdata[2];*/
	RTC_data.date = recdata[2];
	RTC_data.hour = recdata[3];
	RTC_data.minute = recdata[4];
	RTC_data.second = recdata[5];
	IICMasterWriteReg(BAUD_100K, ADDR_RTC, REG_YEAR, RTC_data.year);
	IICMasterWriteReg(BAUD_100K, ADDR_RTC, REG_MONTH, RTC_data.month);
	/*IICWriteReg(BAUD_100K, ADDR_RTC, REG_WEEK, RTC_data.week);*/
	IICMasterWriteReg(BAUD_100K, ADDR_RTC, REG_DAY, RTC_data.date);
	IICMasterWriteReg(BAUD_100K, ADDR_RTC, REG_HOUR, RTC_data.hour);
	IICMasterWriteReg(BAUD_100K, ADDR_RTC, REG_MINUTE, RTC_data.minute);
	IICMasterWriteReg(BAUD_100K, ADDR_RTC, REG_SECOND, RTC_data.second);
}

/*******************************************************************************
**  FUNCTION      : Calendar_Message_Handler
**  DESCRIPTION   : 
**  PARAMETERS    : void
**  RETURN        : void
*******************************************************************************/
void Calendar_Message_Handler(U16 commandid,U8* data)
{
	RTC_DATA_TYPE rtc_temp_data;
    /*U8 msg[6] = {0};*/
	switch(commandid)
	{
		case NAVI_SYNC_GPS_TIME:
            rtc_temp_data.hour = data[0];    /*hour*/
			rtc_temp_data.minute = data[1];  /*minute*/
			rtc_temp_data.second = data[2];  /*second*/
			rtc_temp_data.year = data[3];    /*year*/
			rtc_temp_data.month = data[4];   /*month*/
			rtc_temp_data.date = data[5];    /*day*/
			/*rtc_temp_data.week = data[6];*/
            Calendar_Set(&rtc_temp_data);
		break;
		/*
		case RADIO_DISPATCH_CLOCK:
			rtc_temp_data = Calendar_Get();			
            msg[0] = rtc_temp_data.hour;
            msg[1] = rtc_temp_data.minute;
            msg[2] = rtc_temp_data.second;
            msg[3] = rtc_temp_data.year;
            msg[4] = rtc_temp_data.month;
            msg[5] = rtc_temp_data.date;
			msg[6] = rtc_temp_data.week;
			SocManager_SendMsg(HQ_CMD, TYPE_EVENT, NAVI_REQ_TIME, 7, &msg[0]);
		break;
		*/
		
		default:

		break;
	}
}

/*******************************************************************************
**  FUNCTION      : Calendar_Message_Send
**  DESCRIPTION   : 
**  PARAMETERS    : void
**  RETURN        : void
*******************************************************************************/
void Calendar_Message_Send(void)
{
	U8 data[6];
	RTC_data = Calendar_Get();
	data[0] = RTC_data.hour;
	data[1] = RTC_data.minute;
	data[2] = RTC_data.second;
	data[3] = RTC_data.year;
	data[4] = RTC_data.month;
	data[5] = RTC_data.date;
	/*data[6] = RTC_data.week;*/
	SocManager_SendMsg(HQ_CMD,TYPE_EVENT,NAVI_REQ_TIME,6,data);
}

/*十六进制转BCD*/
void Hex2BCD(U8* a)
{
	U8 i;
	U8 t_h[6],t_l[6];
	for(i=0; i<6; i++)
	{
		t_h[i] = a[i]/10;    
		t_l[i] = a[i] - t_h[i]*10;
		a[i] = (t_h[i]<<4) + t_l[i];
	}
}    
    
/*BCD转十六进制*/
void BCD2Hex(U8* a)
{    
	U8 i;
	U8 t_h[6],t_l[6];
	for(i=0; i<6; i++)
	{
    	t_h[i] = (a[i]&0xf0)>>4;
    	t_l[i] = a[i]&0x0f;
	    a[i] = t_h[i]*10 + t_l[i];    
	}
}   


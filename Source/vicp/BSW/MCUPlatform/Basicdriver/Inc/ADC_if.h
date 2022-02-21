/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.		           *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									                   *
************************************************************************
* Object        :  adc_if.h 
* Module        : 
* Instance      : 
* Description   : external data and interface
*-----------------------------------------------------------------------
* Version: 
* Date: 
* Author: 
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
* ----------------------------------------------------------------------
* 0.1  Feb 10,2013    NI Rujin  Initial version
* ----------------------------------------------------------------------
* 0.2  Dec 23,2016   PEI Jingli Change for CodeReview result.
* ----------------------------------------------------------------------
* 0.3  Jan 12,2017   ShangQiuju Update for recover coverity warnings.
*-----------------------------------------------------------------------
* 0.4  Jan 18,2017    ZhangJie     Remove unused include headfile.
*----------------------------------------------------------------------
* 0.5  Jan 24,2017    ZhangJie     Fix Coverity warning phase2.
=======================================================================*/
#ifndef  _ADC_IF_H_
#define   _ADC_IF_H_
#include "Define.h"

/**** Definition of types ****/
/*
    The index of physical channel
*/
typedef enum
{
    ADC_0 = 0x0,
    ADC_1 = 0x01,
    ADC_2 = 0x02,
    ADC_3 = 0x03,
    ADC_4 = 0x04,
    ADC_5 = 0x05,
    ADC_6 = 0x06,
    ADC_7 = 0x07,
    ADC_8 = 0x08,
    ADC_9 = 0x09,
    ADC_10 = 0x0A,
    ADC_11 = 0x0B,
    ADC_12 = 0x0C,
    ADC_13 = 0x0D,
    ADC_14 = 0x0E,
    ADC_15 = 0x0F,

    /*temporary deinfed max value*/
    ADC_MAX
} ADC_TYPE;

/**** Declaration of functions ****/
extern void ADC_Init(U16 usedChannels, U16 scannum );
extern void ADC_DeInit( void );
extern ERR_TYPE ADC_GetValue( ADC_TYPE channelId, U16* val );
extern void ADC_Conversion( void );
#endif/*_ADC_IF_H_*/


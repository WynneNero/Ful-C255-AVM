/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department :  CT AD NKG 
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   :
***********************************************************************/
/*-History--------------------------------------------------------------
* Ver    Date           Name        Changes and comment
* ----------------------------------------------------------------------
* 0.1    Jul 21,2016    PEI Jingli  Initial version
* ----------------------------------------------------------------------
* 0.2    Aug 01,2016    PEI Jingli  add APORT interface and INTP inf
* ----------------------------------------------------------------------
* 0.3    Oct 11,2016    PEI Jingli  Modify micro-define
                                     and Interface
* ------------------------------------------------------------------------
* 0.4   Dec 02,2016    PEI Jingli  Modify for code-review result
* ------------------------------------------------------------------------
* 0.5   Jan 12,2017    ZhangJie  Change function parameter, add u for constant value 
                                              and remove unused typedef to avoid Coverity warning.
*----------------------------------------------------------------------
* 0.6   Jan 24,2017    ZhangJie     Fix Coverity warning phase2.                                             
*=====================================================================*/
#ifndef _GPIO_IF_H_
#define _GPIO_IF_H_
#include "Define.h"
#include <config.h>

/**** Definition of constants ****/

/**** Definition of macros ****/
/*pin config options*/
#define GPIO_OPT_INIT          0x00u
#define GPIO_OPT_INPUT       0x01u  /* enable input, if 0, output*/
#define GPIO_OPT_BIDIRECT  0x02u  /*bidirectonal  enable*/
#define GPIO_OPT_IN_PLLUP      0x04u   /*enable pull-up of input*/
#define GPIO_OPT_IN_PLLDWN   0x08u  /*enable pull-dowm of input*/
#define GPIO_OPT_OUT_OD         0x10u  /*enable open-drain, if 0,push-pull*/
#define GPIO_OPT_OUT_STRTH40M   0x20u  /* enable 40mhz, if 0,10mhz*/

/**** Definition of types ****/
enum   /* pin definition of  a port*/
{
    GPIO_PIN_0 = 0x00,
    GPIO_PIN_1 = 0x01,
    GPIO_PIN_2 = 0x02,
    GPIO_PIN_3 = 0x03,
    GPIO_PIN_4 = 0x04,
    GPIO_PIN_5 = 0x05,
    GPIO_PIN_6 = 0x06,
    GPIO_PIN_7 = 0x07,
    GPIO_PIN_8 = 0x08,
    GPIO_PIN_9 = 0x09,
    GPIO_PIN_A = 0x0A,
    GPIO_PIN_B = 0x0B,
    GPIO_PIN_C = 0x0C,
    GPIO_PIN_D = 0x0D,
    GPIO_PIN_E = 0x0E,
    GPIO_PIN_F = 0x0F
};

enum  /*MCU port*/
{
    GPIO_PORT_0 = 0x00,
    GPIO_PORT_1 = 0x01,
    GPIO_PORT_2 = 0x02,
    GPIO_PORT_3 = 0x03,
    GPIO_PORT_4 = 0x04,
    GPIO_PORT_5 = 0x05,
    GPIO_PORT_6 = 0x06,
    GPIO_PORT_7 = 0x07,
    GPIO_PORT_8 = 0x08,
    GPIO_PORT_9 = 0x09,
    GPIO_PORT_10 = 0x0A,
    GPIO_PORT_11 = 0x0B,
    GPIO_PORT_12 = 0x0C,    
    GPIO_PORT_18 = 0x12,    
    GPIO_PORT_20 = 0x14,

    AP_PORT_0 = 0x15,   /*APORT0 */
    JP_PORT_0 = 0x16,   /*JPORT0*/ 
    GPIO_PORT_NUM
 };

/*input type*/
typedef enum
{
    E_NO_MODE=GPIO_OPT_INIT,         /*default*/
    E_PLLUP=GPIO_OPT_IN_PLLUP,       /*internal pull-up*/
    E_PLLDOWN=GPIO_OPT_IN_PLLDWN, /*internal pull-down*/
    E_INPUT_HIZ   /*high impedance*/
}GPIO_IN_TYPE;
/*output type*/
typedef enum
{
    E_PUSH_PULL=GPIO_OPT_INIT,  /*default*/
    E_OPEN_DRAIN=GPIO_OPT_OUT_OD
}GPIO_OUT_TYPE;

typedef enum
{
  E_LOW_10MHZ=GPIO_OPT_INIT,   /*default*/
  E_HIGH_40MHZ=GPIO_OPT_OUT_STRTH40M
}GPIO_DRIVSTRH;

/*register PDCAEn+PFCEn+PFCn*/
typedef enum
{
  E_ALTERFUNC_1=0,
  E_ALTERFUNC_2,
  E_ALTERFUNC_3,
  E_ALTERFUNC_4,
  E_ALTERFUNC_5
}GPIO_ALTERMODE;


/**** Declaration of functions ****/
extern void GPIO_SetInputMode( U8 port, U8 pin,  GPIO_IN_TYPE Mode);
extern void GPIO_SetOutputMode( U8 port, U8 pin,  GPIO_OUT_TYPE Mode, GPIO_DRIVSTRH drvStrgth );
extern U8 GPIO_GetVal( U8 port, U8 pin );
extern void  GPIO_SetVal( U8 port, U8 pin, BOOL isHlevel);
extern void GPIO_SetAlterMode( U8 port, U8 pin,  GPIO_ALTERMODE AlterMode, U8 options );
extern void GPIO_SetAlterMode_DirectIO( U8 port, U8 pin,  GPIO_ALTERMODE AlterMode, U8 options );
/* Interface for port setting */
extern void GPIO_SetDriverStrengthDrain_Port(U8 port,  U32 pdscval);
extern void GPIO_SetOpenDrain_Port(U8 port,  U32 OpenDrain);

#endif
/****************************** END OF FILE ***************************/

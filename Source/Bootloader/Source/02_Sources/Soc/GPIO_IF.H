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
*=====================================================================*/
#ifndef _GPIO_IF_H_
#define _GPIO_IF_H_
#include "CONFIG.H"
#include "define.h"
/**** Definition of constants ****/

/**** Definition of macros ****/
#define SIG_DIO_READING_INVALID 0xFF

#define SIG_DIO_VALUE_INVALID 0xFF


/**** Definition of types ****/
typedef enum   // pin definition of  a port
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
} GPIO_PIN_TYPE;

typedef enum  //MCU port
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

    AP_PORT_0 = 0x15,   //APORT0 
    JP_PORT_0 = 0x16,   //JPORT0 
    GPIO_PORT_NUM
 }GPIO_PORT_TYPE;

// INTP:external interruput channel
typedef enum
{
    EXTI_00 = 0x00,
    EXTI_01 = 0x01,	
    EXTI_02 = 0x02,	
    EXTI_03 = 0x03,	
    EXTI_04 = 0x04,
    EXTI_05 = 0x05,
    EXTI_06 = 0x06,
    EXTI_07 = 0x07,
    EXTI_08 = 0x08,
    EXTI_09 = 0x09,
    EXTI_10 = 0x0A,
    EXTI_11 = 0x0B,
    EXTI_12 = 0x0C,
    EXTI_13 = 0x0D,	
    EXTI_14 = 0x0E,
    EXTI_15 = 0x0F,
    EXTI_NUM
} EXTI_TYPE;
// INTP trigger type
typedef enum
{
    EXTI_TRIGGER_LOW = 0x00,
    EXTI_TRIGGER_HIGH = 0x01,
    EXTI_TRIGGER_RISING = 0x02,
    EXTI_TRIGGER_FALLING = 0x03,
    EXTI_TRIGGER_RISFALL = 0x04
} EXTI_TRIGGER_TYPE;

typedef enum
{
    E_NO_MODE=0,
    E_PLLUP,
    E_PLLDOWN,
    E_PUSH_PULL,
    E_OPEN_DRAIN
}GPIO_INOUT_TYPE;

typedef enum
{
  E_LOW_10MHZ=0,
  E_HIGH_40MHZ
}GPIO_DRIVSTRH;

//register PDCAEn+PFCEn+PFCn
typedef enum
{
  E_ALTERFUNC_1=0,
  E_ALTERFUNC_2,
  E_ALTERFUNC_3,
  E_ALTERFUNC_4,
  E_ALTERFUNC_5
}GPIO_ALTERMODE;

//digital filter
/*
typedef enum  //del
{
 DFILTERTYPE_BLOCKED,
 DFILTERTYPE_FILTERINPUT,
 DFILTERTYPE_BYPASS	
}DFilter;
*/


/**** Definition of macros ****/
#if TEST_ON
#define D19_ON()	GPIO_Out_Write(GPIO_PORT_8, GPIO_PIN_6,TRUE)
#define D20_ON()	GPIO_Out_Write(GPIO_PORT_8, GPIO_PIN_4,TRUE)
#define D25_ON()	GPIO_Out_Write(GPIO_PORT_8, GPIO_PIN_8,TRUE)
#define D26_ON()	GPIO_Out_Write(GPIO_PORT_8, GPIO_PIN_9,TRUE)
#define D21_ON()	GPIO_Out_Write(GPIO_PORT_9, GPIO_PIN_3,TRUE)
#define D23_ON()	GPIO_Out_Write(GPIO_PORT_9, GPIO_PIN_4,TRUE)
#define D24_ON()	GPIO_Out_Write(GPIO_PORT_9, GPIO_PIN_5,TRUE)
#define D22_ON()	GPIO_Out_Write(GPIO_PORT_9, GPIO_PIN_6,TRUE)

#define D19_OFF()	    GPIO_Out_Write(GPIO_PORT_8, GPIO_PIN_6,FALSE)
#define D20_OFF()	    GPIO_Out_Write(GPIO_PORT_8, GPIO_PIN_4,FALSE)
#define D25_OFF() 	GPIO_Out_Write(GPIO_PORT_8, GPIO_PIN_8,FALSE)
#define D26_OFF()	    GPIO_Out_Write(GPIO_PORT_8, GPIO_PIN_9,FALSE)
#define D21_OFF()    GPIO_Out_Write(GPIO_PORT_9, GPIO_PIN_3,FALSE)
#define D23_OFF() 	GPIO_Out_Write(GPIO_PORT_9, GPIO_PIN_4,FALSE)
#define D24_OFF()	    GPIO_Out_Write(GPIO_PORT_9, GPIO_PIN_5,FALSE)
#define D22_OFF()    GPIO_Out_Write(GPIO_PORT_9, GPIO_PIN_6,FALSE)
#else  //pjl_test for new_pcb used
#define D19_ON()	
#define D20_ON()	
#define D25_ON()	
#define D26_ON()	
#define D21_ON()	
#define D23_ON()	
#define D24_ON()	
#define D22_ON()	

#define D19_OFF()
#define D20_OFF()
#define D25_OFF() 
#define D26_OFF()
#define D21_OFF() 
#define D23_OFF() 
#define D24_OFF()
#define D22_OFF() 
#endif

/**** Declaration of variables ****/
#define CONTRL_CLUST0_REG_PROTCMD0	 (*(CPU_REG32 *)(0xFFF80000u)) //for MOSCE ROSCE SOSCE IOHOLD
#define CONTRL_CLUST0_REG_PROTS0          (*(CPU_REG32 *)(0xFFF80004u))
#define CONTRL_CLUST1_REG_PROTCMD1	 (*(CPU_REG32 *)(0xFFF88000u)) //for PLLE
#define CONTRL_CLUST1_REG_PROTS1         (*(CPU_REG32 *)(0xFFF88004u))


#define PROTCMD_WRITE_EN_VAL       (0xA5U)     /* Protection commands to enable writing */
/* control protection cluster */
#define CLUST0_PROTCMD0_WRITEENABLE()    (CONTRL_CLUST0_REG_PROTCMD0=PROTCMD_WRITE_EN_VAL)
#define CLUST0_PROTS0_ISERR()    (CONTRL_CLUST0_REG_PROTS0==1)
#define CLUST1_PROTCMD1_WRITEENABLE()    (CONTRL_CLUST1_REG_PROTCMD1=PROTCMD_WRITE_EN_VAL)
#define CLUST1_PROTS1_ISERR()    (CONTRL_CLUST1_REG_PROTS1==1)
/* clock monitors control and test protection cluster */

/**** Declaration of functions ****/

/**** Declaration of functions ****/
extern void GPIO_SetInMode( U8 port, U8 pin,  GPIO_INOUT_TYPE Mode, BOOL isEnableBuffer);
extern void GPIO_SetOutMode( U8 port, U8 pin,  GPIO_INOUT_TYPE Mode, GPIO_DRIVSTRH drvStrgth );
extern U8 GPIO_In_Read( U8 port, U8 pin );
extern void  GPIO_Out_Write( U8 port, U8 pin, BOOL isHlevel);
extern void GPIO_SetAlterMode( U8 port, U8 pin,  GPIO_ALTERMODE AlterMode, BOOL isDirectIO, GPIO_INOUT_TYPE Mode );
/* Interface for Write Sequence */
extern BOOL PORT_SetPDSC(U8 port,  U32 pdscval);
extern BOOL PORT_SetPODC(U8 port,  U32 OpenDrain);
extern BOOL JPORT_SetPODC(U8 port,  U32 OpenDrain);
extern void APPORT_SetInMode(U8 port, U8 pin, BOOL isEnableBuffer);
extern void APPORT_SetOutMode(U8 port, U8 pin);
extern U8 APPORT_In_Read( U8 port, U8 pin );
extern void APPORT_Out_Write( U8 port, U8 pin, BOOL isHlevel);
/* INTP configration */
extern void EXTI_Config( EXTI_TYPE intp, EXTI_TRIGGER_TYPE exti_trigger );
extern void EXTI_Cmd( EXTI_TYPE intp, FUNCTION_STATE state );

#endif
/****************************** END OF FILE ***************************/

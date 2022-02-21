/*  BEGIN_FILE_HDR
***********************************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information contained in this 
*   doc should not be reproduced, or used, or disclosed without the written authorization from 
*   HiRain Technologies.
***********************************************************************************************
*   File Name       : Can_Type.h
***********************************************************************************************
*   Project/Product : AUTOSAR 4.0
*   Title           : CAN Driver module type definitions head File
*   Author          : HeYang
***********************************************************************************************
*   Description     : The header file Can_Type.h contains the  common type definitions of
*                     the module Can Driver 
***********************************************************************************************
*   Limitations     : 
*
***********************************************************************************************
*
***********************************************************************************************
*   Revision History:
* 
*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   1.0         2012/5/6       HeYang       N/A          Original
*
***********************************************************************************************
* END_FILE_HDR*/
#ifndef _BL_CAN_TYPE_H_
#define _BL_CAN_TYPE_H_

#include "bl_can_cfg.h"

/*CAN429:
Name: Can_HwHandleType
Type: bl_u8_t , bl_u16_t
Range: Standard 0..0x0FF
       Extended 0..0xFFFF
Description:    Represents the hardware object handles of a CAN hardware unit. For CAN
                hardware units with more than 255 HW objects use extended range.
*/
typedef bl_u16_t Can_HwHandleType;

 /*CAN416:
Name:   Can_IdType
Type:   bl_u16_t, bl_u32_t
Range:  Standard 0..0x7FF
        Extended 0..0xFFFFFFFF
Description:    
Represents the Identifier of an L-PDU. For extended IDs the most significant 
bit is set.
*/
#if (STD_ON == CAN_ENABLE_EXTENDED_ID)  
    typedef bl_u32_t Can_IdType;
#else
    typedef bl_u16_t Can_IdType;
#endif/* #if (STD_ON == CAN_ENABLE_EXTENDED_ID)  */

/*CAN039:
Name:  Can_ReturnType 
Enumeration  Type: 
Range: 
CAN_OK  success 
CAN_NOT_OK  error occurred or wakeup event occurred during sleep transition 
CAN_BUSY  transmit request could not be processed because no transmit object was available 
Description:  Return values of CAN driver API . 
*/
typedef enum
{
    CAN_OK = 0,                   
    CAN_NOT_OK,     
    CAN_BUSY        
}Can_ReturnType;


#if (CAN_DEV_ERROR_DETECT == STD_ON )
  typedef enum
  {
      CAN_UNINT = 0,
      CAN_STOPPED, 
      CAN_STARTED,    
      CAN_SLEEP    
         
  }Can_StateType;
#endif


/* CAN417:  
Name:  Can_StateTransitionType 
Type:  Enumeration 
Range: 
CAN_T_START  CAN controller transition value to request state STARTED. 
CAN_T_STOP  CAN controller transition value to request state STOPPED. 
CAN_T_SLEEP  CAN controller transition value to request state SLEEP. 
CAN_T_WAKEUP  CAN controller transition value to request state STOPPED from state SLEEP. 
Description:  State transitions that are used by the function CAN_SetControllerMode 
*/
typedef enum
{
    CAN_T_NONE = 0,
    CAN_T_START = 1,    
    CAN_T_STOP = 2,     
    CAN_T_SLEEP = 3,    
    CAN_T_WAKEUP =4   
}Can_StateTransitionType;


 /* CAN413: 
Name:  Can_ConfigType 
Type:  Structure 
Range: Implementation specific.  
Description:This is the type of the external data structure containing 
the overall initialization data for the CAN driver and SFR settings 
affecting all controllers. Furthermore it contains pointers to controller 
configuration structures. The contents of the initialization data structure 
are CAN hardware specific. 
*/ 

typedef struct
{

    bl_u8_t          CanControllerNum;
   
    
}Can_ConfigType;

/*CAN414:
Name:     Can_ControllerBaudrateConfigType
Type:     Structure
Range:    Implementation specific.
Description: This is the type of the external data structure containing 
the bit timing related initialization data for one CAN controller. 
The contents of the initialization data structure are CAN hardware specific.
*/
typedef struct
{
    bl_u8_t    CanCtrl0;
    bl_u8_t    CanCtrl1;
   
}Can_ControllerBaudrateConfigType;

typedef bl_u16_t PduIdType;

/*CAN415:
Name: Can_PduType
Type: Structure
Description: 
This type is used to provide ID, DLC and SDU from CAN interface 
to CAN driver.
*/
typedef struct
{
    PduIdType   swPduHandle;
    bl_u8_t     length;
    Can_IdType  id;
    bl_u8_t   sdu;  
}Can_PduType;

typedef struct
{                   
    bl_u8_t       controllerRef;  /*logic controller*/
   Can_IdType      id;             /*CAN ID*/
   bl_u8_t      hohType;        /*hohType  bit0:0-receive,1-transmit;bit1:0-basic ,1-full*/
   bl_u32_t     MsgbufferType;  /*value of Rx Individual Mask Registers,when BCC=1*/
}Can_HardwareObjectConfigType;

/* Can Internal buffer length type */
typedef bl_u32_t Can_LenType;

typedef enum
{
   CAN_UNINITIALIZED=0,
   CAN_INITIALIZED=1  
}Can_InitType;

#endif /*CAN_TYPE_H_*/

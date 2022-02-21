/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.		       
*				  All Rights Reserved.                 
*   Department :  CT AD NKG      				     
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   : Functions in General Port Mode
***********************************************************************/
/*-History--------------------------------------------------------------
* Version  Date   	 Name        Changes and comments
------------------------------------------------------------------------
* 0.1	   Jun 26,2016   PEI Jingli  Initial version
------------------------------------------------------------------------
* 0.2	   Jun 29,2016   LIU Chenxi  Correct errors during merging	
------------------------------------------------------------------------
* 0.3	   July 07,2016  PEI Jingli  Adapt 64pin MCU
------------------------------------------------------------------------
* 0.4	   July 07,2016  LIU Chenxi  Refine macro definition.
------------------------------------------------------------------------
* 0.5	   July 21,2016  PEI Jingli  Update EXIT settings
------------------------------------------------------------------------
* 0.6	   Aug 10,2016  PEI Jingli  Modify PDSC,PODC interface
                               add APORT interface
------------------------------------------------------------------------
* 0.7	   July 21,2016  PEI Jingli  Modify SetAlterMode interface for noise
------------------------------------------------------------------------
* 0.8	   Sep 22,2016  ShangQiuju  set PPRegAddr const data  
------------------------------------------------------------------------
* 0.9	Oct 11,2016  PEI Jingli  Modify input,output,Alternative setting inf 
                                 Add APORT,JPORT to gpio inf
------------------------------------------------------------------------
* 1.0	Jan 11,2017  ZhangJie   Change function parameter, add STATIC key word and add u for constant value to avoid Coverity warning
*-----------------------------------------------------------------------
* 1.1      Jan 24,2017   ZhangJie   Remove unused include file.
------------------------------------------------------------------------
* 1.2	Apr 01,2017  PEI Jingli  Fix headfile included.
*=====================================================================*/
#include "Define.h"
#include "GPIO_if.h"
#include "GPIO.h"
#include "wpreg.h"


STATIC void GPIO_SetOpenDrain(U8 port, U8 pin,BOOL isOpenDrain);
STATIC void GPIO_SetDriverStrengthDrain(U8 port, U8 pin,BOOL isHighSpeed);
STATIC void JGPIO_SetAlterMode( U8 port, U8 pin,  GPIO_ALTERMODE AlterMode, U8 options );

/* Get port protection command address */
U32 GetPortPCRegAddress(U8 port)
{
    if(GPIO_PORT_20>=port)          
       return (0xFFC14C00u+port*4); 
    else if(JP_PORT_0==port)       
       return 0xFFC204C0u;               
    return 0; 
} 

/* Get port protection status reg address */
U32 GetPortPSRegAddress(U8 port)
{  
   if(GPIO_PORT_20>=port)          
       return (0xFFC14B00u+port*4); 
   else if(JP_PORT_0==port)         
     return 0xFFC204B0u;                  
   return 0; 
} 

/***********************************************************************
*  Name        : GPIO_SetInputMode
*  Description : set a input pin of PORT mode
*  Parameter   : port  GPIO_PORT_TYPE
*                        pin    GPIO_PIN_TYPE
*                        Mode  GPIO_IN_TYPE,
*                                  E_INPUT_HIZ, if high impedance,PIBC bit be 0
*                                  others, PIBC bit be 1
*  Returns     : None
***********************************************************************/
void GPIO_SetInputMode( U8 port, U8 pin, GPIO_IN_TYPE Mode)
{  
    if((AP_PORT_0<=port) && (port< JP_PORT_0)) /*set APORT*/
    {
        APORT_REG_APBDC(port - AP_PORT_0) &=(~(1u<<pin));
        if(E_INPUT_HIZ!=Mode)
            APORT_REG_APIBC(port - AP_PORT_0)|=(1u<<pin);
        else
            APORT_REG_APIBC(port - AP_PORT_0)&=(~(1u<<pin));
        APORT_REG_APM(port - AP_PORT_0) |= (U16)(1u<<pin);
    }
    else if(JP_PORT_0 <= port) /*set JPORT*/
    {
        /*initialize*/
        JPORT_REG_JPIBC(port-JP_PORT_0) &=(~(1u<<pin));
        JPORT_REG_JPBDC(port-JP_PORT_0) &=(~(1u<<pin));
        JPORT_REG_JPM(port-JP_PORT_0) |=(1u<<pin);
        JPORT_REG_JPMC(port-JP_PORT_0)  &=(~(1u<<pin));
        /*change value*/
        switch(Mode)
        {
            case E_PLLUP:
            {
              JPORT_REG_JPU(port-JP_PORT_0)|=(1u<<pin);
              JPORT_REG_JPD(port-JP_PORT_0)&=(~(1u<<pin));
            break;
            }
            case E_PLLDOWN:
            {
              JPORT_REG_JPD(port-JP_PORT_0)|=(1u<<pin);
              JPORT_REG_JPU(port-JP_PORT_0)&=(~(1u<<pin));
            break;
            }     
          case E_NO_MODE:
          default:
              JPORT_REG_JPU(port-JP_PORT_0)&=(~(1u<<pin));
              JPORT_REG_JPD(port-JP_PORT_0)&=(~(1u<<pin));
            break;
        }
        
        if(E_INPUT_HIZ!=Mode)
          JPORT_REG_JPIBC(port-JP_PORT_0) |=(1u<<pin);
        else
          JPORT_REG_JPIBC(port-JP_PORT_0) &=(~(1u<<pin));
    }
    else
    {
        /*initialize*/
        PORT_REG_PIBC(port) &=(~(1u<<pin));
        PORT_REG_PBDC(port) &=(~(1u<<pin));
        PORT_REG_PM(port) |=(1u<<pin);
        PORT_REG_PMC(port) &=(~(1u<<pin));
        PORT_REG_PIPC(port)  &=(~(1u<<pin)); 
        /*change value*/
        switch(Mode)
        {
          case E_PLLUP:
          {
              PORT_REG_PU(port)|=(1u<<pin);
              PORT_REG_PD(port)&=(~(1u<<pin));
              break;
      	  }
          case E_PLLDOWN:
      	  {
              PORT_REG_PD(port)|=(1u<<pin);
              PORT_REG_PU(port)&=(~(1u<<pin));
              break;
      	  }     
          case E_NO_MODE:
          default:
          {
              PORT_REG_PU(port)&=(~(1u<<pin));
              PORT_REG_PD(port)&=(~(1u<<pin));
              break;
          }
      }
      /*In port mode input buffer must be enabled*/
      if(E_INPUT_HIZ!=Mode)
          PORT_REG_PIBC(port)|=(1u<<pin);
      else
          PORT_REG_PIBC(port)&=(~(1u<<pin));
    }
}

/***********************************************************************
*  Name        : GPIO_SetOutputMode
*  Description : set a output pin of PORT mode
*  Parameter   : port   GPIO_PORT_TYPE
*                        pin     GPIO_PIN_TYPE
*                        Mode  E_PUSH_PULL,E_OPEN_DRAIN
*                        drvStrgth  driver speed
*  Returns :None 
***********************************************************************/
void GPIO_SetOutputMode( U8 port, U8 pin,  GPIO_OUT_TYPE Mode, GPIO_DRIVSTRH drvStrgth )
{
  if((AP_PORT_0<=port) && (port< JP_PORT_0)) /*set APORT*/
  {
      APORT_REG_APBDC(port - AP_PORT_0) &=(~(1u<<pin));
      APORT_REG_APIBC(port - AP_PORT_0)  &=(~(1u<<pin));
      APORT_REG_APM(port - AP_PORT_0)&=(U16)(~(1u<<pin)); /*0-OUTPUT*/
      return ;
  }
  else if(JP_PORT_0 <= port) /*set JPORT*/
  {
      /*initialize*/
      JPORT_REG_JPIBC(port-JP_PORT_0) &=(~(1u<<pin));
      JPORT_REG_JPBDC(port-JP_PORT_0) &=(~(1u<<pin));
      JPORT_REG_JPM(port-JP_PORT_0) |=(1u<<pin);
      JPORT_REG_JPMC(port-JP_PORT_0)  &=(~(1u<<pin));
      /*change value*/
      if(Mode==E_OPEN_DRAIN ) /*out type*/
      {
        GPIO_SetOpenDrain(port, pin, TRUE ); /*no -JP_PORT_0*/
      }
      else
      {
        GPIO_SetOpenDrain(port, pin, FALSE);
      }   
      JPORT_REG_JPM(port-JP_PORT_0)&=(U16)(~(1u<<pin));
  }
  else
  {  
      /*initialize*/
      PORT_REG_PIBC(port) &=(~(1u<<pin));
      PORT_REG_PBDC(port) &=(~(1u<<pin));
      PORT_REG_PM(port) |=(1u<<pin);
      PORT_REG_PMC(port) &=(~(1u<<pin));
      PORT_REG_PIPC(port)  &=(~(1u<<pin)); 
      /*change value*/
      if(Mode==E_OPEN_DRAIN ) 
      {
        GPIO_SetOpenDrain(port, pin, TRUE ); /*output mode:open-drain*/
      }
      else
      {
        GPIO_SetOpenDrain(port, pin, FALSE); /*output mode:push-pull*/
      }   
    
      if(drvStrgth==E_HIGH_40MHZ)
    	  GPIO_SetDriverStrengthDrain(port,pin,TRUE);
      else
    	  GPIO_SetDriverStrengthDrain(port,pin,FALSE);
    
      PORT_REG_PM(port)&=(U16)(~(1u<<pin));
  }
}

/****************************************************************************************
*  Name        : GPIO_SetAlterMode
*  Description : set alternative mode without direct IO control(PIPC=0). IO direction is controlled by PM
*  Parameter   : AlterMode:  function 1~5
*       options:
*        1. when input with no bidiretion, 
*            GPIO_OPT_BIDIRECT disable     GPIO_OPT_INPUT enable, 
*            GPIO_OPT_IN_PLLUP and GPIO_OPT_IN_PLLDWN, enable or not
*        2. when output with no bidiretion, 
*            GPIO_OPT_BIDIRECT disable     GPIO_OPT_INPUT disable, 
*            GPIO_OPT_OUT_OD and  GPIO_OPT_OUT_STRTH, enable or not
*        3. when bidirection 
*            GPIO_OPT_BIDIRECT enable
*           GPIO_OPT_IN_PLLUP,GPIO_OPT_IN_PLLDWN,GPIO_OPT_OUT_OD,GPIO_OPT_OUT_STRTH may be need
*  Returns : None
****************************************************************************************/
void GPIO_SetAlterMode( U8 port, U8 pin,  GPIO_ALTERMODE AlterMode, U8 options )
{
    if((AP_PORT_0<=port) && (port< JP_PORT_0))
    {
        APORT_REG_APIBC(port - AP_PORT_0)&=(~(1u<<pin));
        APORT_REG_APM(port - AP_PORT_0) |= (U16)(1u<<pin);
        if(options&GPIO_OPT_BIDIRECT) /* input and output*/
        {
          APORT_REG_APBDC(port - AP_PORT_0) &=(~(1u<<pin));
        }
        if(!(options&GPIO_OPT_INPUT) || (options&GPIO_OPT_BIDIRECT) )
          APORT_REG_APM(port - AP_PORT_0) &= ~(1u<<pin); /*direction output*/
    }
    else if(JP_PORT_0 <= port)
    {
        JGPIO_SetAlterMode(port,pin,AlterMode,options);
    }
    else
    {
        /*initialize*/
        PORT_REG_PIBC(port) &=(~(1u<<pin));
        PORT_REG_PBDC(port) &=(~(1u<<pin));
        PORT_REG_PM(port) |=(1u<<pin);
        PORT_REG_PMC(port) &=(~(1u<<pin));
        PORT_REG_PIPC(port)  &=(~(1u<<pin)); 
        /*change value*/
        if(options&GPIO_OPT_BIDIRECT) /* input and output*/
        {
            if(options&GPIO_OPT_OUT_STRTH40M)
              GPIO_SetDriverStrengthDrain(port, pin, TRUE);
            else
              GPIO_SetDriverStrengthDrain(port, pin, FALSE);
              
            if(options&GPIO_OPT_OUT_OD)
              GPIO_SetOpenDrain(port, pin, TRUE);
            else
              GPIO_SetOpenDrain(port, pin, FALSE);
    
            if(options&GPIO_OPT_IN_PLLUP)
              PORT_REG_PU(port) |=(1u<<pin);
            else
              PORT_REG_PU(port) &=~(1u<<pin);
              
            if(options&GPIO_OPT_IN_PLLDWN)
              PORT_REG_PD(port)|=(1u<<pin);
            else
              PORT_REG_PD(port) &=~(1u<<pin);
              
            PORT_REG_PBDC(port) |=(1u<<pin);
        }
        else if(options&GPIO_OPT_INPUT)  /*input*/
        {
            if(options&GPIO_OPT_IN_PLLUP)
              PORT_REG_PU(port) |=(1u<<pin);
            else
              PORT_REG_PU(port) &=~(1u<<pin);
              
            if(options&GPIO_OPT_IN_PLLDWN)
              PORT_REG_PD(port)|=(1u<<pin);
            else
              PORT_REG_PD(port) &=~(1u<<pin);
        }
        else /*output*/
        {
            if(options&GPIO_OPT_OUT_STRTH40M)
              GPIO_SetDriverStrengthDrain(port, pin, TRUE);
            else
              GPIO_SetDriverStrengthDrain(port, pin, FALSE);
              
            if(options&GPIO_OPT_OUT_OD)
              GPIO_SetOpenDrain(port, pin, TRUE);
            else
              GPIO_SetOpenDrain(port, pin, FALSE);
        }
        
        /*select alternative function as chapter 2.10.*/
        if(AlterMode &0x01u)
          PORT_REG_PFC(port)|=(1u<<pin);
        else
          PORT_REG_PFC(port)&=~(1u<<pin);
        if(port==GPIO_PORT_0 ||port==GPIO_PORT_8 ||port==GPIO_PORT_9
         ||port==GPIO_PORT_10 ||port==GPIO_PORT_11 ||port==GPIO_PORT_12 )
        {
          if(AlterMode &0x02u)
            PORT_REG_PFCE(port)|=(1u<<pin);
          else
            PORT_REG_PFCE(port)&=~(1u<<pin);
        }
        if(port==GPIO_PORT_0 ||port==GPIO_PORT_10 ||port==GPIO_PORT_11)
        {
          if(AlterMode &0x04u)
            PORT_REG_PFCAE(port)|=(1u<<pin);
          else
            PORT_REG_PFCAE(port)&=~(1u<<pin);
        }
      
        PORT_REG_PMC(port)|=(1u<<pin); /*alernativ mode*/
        if(!(options&GPIO_OPT_INPUT) || (options&GPIO_OPT_BIDIRECT) )
        {
            PORT_REG_PM(port) &=~ (U16)(1u<<pin); /*direction output*/
        }
    }
}

/****************************************************************************************
*  Name        : GPIO_SetAlterMode_DirectIO
*  Description : set alternative mode with direct IO control(PIPC=1). IO direction is controlled 
*                      by hardware,PM is ignored.Just used for IO in chapter2.11.3.1,likes CSIxSC/SO
*  Parameter   : AlterMode:  function 1~5
*       options:
*            GPIO_OPT_IN_PLLUP, pull-up is enable or not
*            GPIO_OPT_IN_PLLDWN, pull-down is enable or not
*            GPIO_OPT_OUT_OD, enable or not
*            GPIO_OPT_OUT_STRTH, enable or not
*            GPIO_OPT_BIDIRECT, enable or not
*  Returns : 
****************************************************************************************/
void GPIO_SetAlterMode_DirectIO( U8 port, U8 pin,  GPIO_ALTERMODE AlterMode, U8 options )
{
    if(AP_PORT_0<=port)
    {}
    else
    {
        /*initialize*/
        PORT_REG_PIBC(port) &=(~(1u<<pin));
        PORT_REG_PBDC(port) &=(~(1u<<pin));
        PORT_REG_PM(port) |=(1u<<pin);
        PORT_REG_PMC(port) &=(~(1u<<pin));
        PORT_REG_PIPC(port)  &=(~(1u<<pin)); 
        /*change value*/
        if(options&GPIO_OPT_IN_PLLUP)
          PORT_REG_PU(port) |=(1u<<pin);
        else
          PORT_REG_PU(port) &=~(1u<<pin);
          
        if(options&GPIO_OPT_IN_PLLDWN)
          PORT_REG_PD(port)|=(1u<<pin);
        else
          PORT_REG_PD(port) &=~(1u<<pin);
    
        if(options&GPIO_OPT_OUT_STRTH40M)
          GPIO_SetDriverStrengthDrain(port, pin, TRUE);
        else
          GPIO_SetDriverStrengthDrain(port, pin, FALSE);
          
        if(options&GPIO_OPT_OUT_OD)
          GPIO_SetOpenDrain(port, pin, TRUE);
        else
          GPIO_SetOpenDrain(port, pin, FALSE);
    
        if(options&GPIO_OPT_BIDIRECT) 
          PORT_REG_PBDC(port) |=(1u<<pin);
        
        /*select alternative function as chapter 2.10.*/
        if(AlterMode &0x01u)
          PORT_REG_PFC(port)|=(1u<<pin);
        else
          PORT_REG_PFC(port)&=~(1u<<pin);
        if(port==GPIO_PORT_0 ||port==GPIO_PORT_8 ||port==GPIO_PORT_9
         ||port==GPIO_PORT_10 ||port==GPIO_PORT_11 ||port==GPIO_PORT_12 )
        {
          if(AlterMode &0x02u)
            PORT_REG_PFCE(port)|=(1u<<pin);
          else
            PORT_REG_PFCE(port)&=~(1u<<pin);
        }
        if(port==GPIO_PORT_0 ||port==GPIO_PORT_10 ||port==GPIO_PORT_11)
        {
          if(AlterMode &0x04u)
            PORT_REG_PFCAE(port)|=(1u<<pin);
          else
            PORT_REG_PFCAE(port)&=~(1u<<pin);
        }
      
        PORT_REG_PIPC(port) |=(1u<<pin); /*set as direct IO*/
        PORT_REG_PMC(port)  |=(1u<<pin); /*when direct IO, be output direction*/
    }
}

/***********************************************************************
*  Name        : GPIO_GetVal
*  Description : get the GPIO Pin level value
*  Parameter   : port can be PORT of GPIO_PORT_TYPE
                 pin can be   PIN of GPIO_PIN_TYPE
*  Returns     : 0/1 pin level.Also maybe bit value of Port register.
***********************************************************************/
U8 GPIO_GetVal( U8 port, U8 pin )
{    
    U8 Ret=0u;
    if((AP_PORT_0<=port) && (port< JP_PORT_0)) /*APORT*/
    {
        Ret=(U8)((APORT_REG_PPR(port - AP_PORT_0)&((U16)(1u<<pin)))>>pin);
    }
    else if(JP_PORT_0 <= port) /*JPORT*/
    {
      Ret=(U8)((JPORT_REG_PPR(port - JP_PORT_0)&((U16)(1u<<pin)))>>pin);
    }
    else /*general PORT*/
      Ret=(U8)((PORT_REG_PPR(port)&((U16)(1u<<pin)))>>pin);

    return Ret;
}

/***********************************************************************
*  Name        : GPIO_SetVal
*  Description : Set value of the GPIO Pin
*  Parameter   : port can be PORT of GPIO_PORT_TYPE
                 pin can be   PIN of GPIO_PIN_TYPE
*               isHlevel  if true, set 1 for high level                 
*  Returns     : None
***********************************************************************/
void GPIO_SetVal( U8 port, U8 pin, BOOL isHlevel)
{
    if((AP_PORT_0<=port) && (port< JP_PORT_0)) /*APORT*/
    {
      if(isHlevel)
      {
          APORT_REG_P(port - AP_PORT_0) |=((U16)(1u<<pin));
      }
      else
      {
          APORT_REG_P(port - AP_PORT_0) &=(~((U16)(1u<<pin)));
      }
    }
    else if(JP_PORT_0 <= port) /*JPORT*/
    {
      if(isHlevel)
      {
          JPORT_REG_P(port - JP_PORT_0) |=((U16)(1u<<pin));
      }
      else
      {
          JPORT_REG_P(port - JP_PORT_0) &=(~((U16)(1u<<pin)));
      }
    }
    else
    { /*general PORT*/
      if(isHlevel)
          PORT_REG_P(port) |=((U16)(1u<<pin));
      else
          PORT_REG_P(port)&=(~((U16)(1u<<pin)));
    }
}

/***********************************************************************
*  Name        : GPIO_SetOpenDrain_Port
*  Description : set open-drain output  for all pin of a port
*  Parameter   : OpenDrain  Set the bit to 1,open-drain mode enabled. 
*                                           If 0,push-pull mode enabled
*  Returns     : None
***********************************************************************/
void GPIO_SetOpenDrain_Port(U8 port,  U32 OpenDrain)
{
    U32 protCmd=GetPortPCRegAddress(port);
    U32 protStatus=GetPortPSRegAddress(port);
    if(protCmd)
    {
        if(AP_PORT_0>port)
        {
            PROTECTED_WRITE((*( CPU_REG32*)protCmd), (*( CPU_REG32*)protStatus), PORT_REG_PODC(port), OpenDrain);
        }
        else if(JP_PORT_0<=port)
        {
          PROTECTED_WRITE((*( CPU_REG32*)protCmd), (*( CPU_REG32*)protStatus), JPORT_REG_JPODC(port-JP_PORT_0), OpenDrain);
        }
    }
}

/***********************************************************************
*  Name        : GPIO_SetOpenDrain_Port
*  Description : set open-drain output  for all pin of a port
*  Parameter   : OpenDrain  Set the bit to 1,40MHZ speed enabled. 
*                                           If 0,10MHZ speed enabled
*  Returns     : None
***********************************************************************/
void GPIO_SetDriverStrengthDrain_Port(U8 port,  U32 pdscval)
{
    U32 protCmd=GetPortPCRegAddress(port);
    U32 protStatus=GetPortPSRegAddress(port);
    if(protCmd &&(GPIO_PORT_8!=port) &&(GPIO_PORT_9!=port)) /*no this register*/
    {
        PROTECTED_WRITE((*( CPU_REG32*)protCmd), (*( CPU_REG32*)protStatus), PORT_REG_PDSC(port), pdscval);
    }
}

/***********************************************************************
*  Name        : GPIO_SetOpenDrain
*  Description : set Drive strength as high 40M or low 10M 
*  Parameter   : isOpenDrain  Set the bit to 1,40MHZ speed enabled. 
*                                           If 0,10MHZ speed enabled
*  Returns     : 
***********************************************************************/
STATIC void GPIO_SetOpenDrain(U8 port, U8 pin, BOOL isOpenDrain)
{
    U32 regdata=0;
    U32 protCmd=GetPortPCRegAddress(port);
    U32 protStatus=GetPortPSRegAddress(port);
    if(protCmd)
    {
        if(JP_PORT_0==port)
       {
          if(isOpenDrain==TRUE)
          {
            regdata = (JPORT_REG_JPODC(port-JP_PORT_0) | (1u<<pin));
          }
          else
          {
            regdata = (JPORT_REG_JPODC(port-JP_PORT_0)&( ~(1u<<pin)));
          }
          
          PROTECTED_WRITE((*( CPU_REG32*)protCmd), (*( CPU_REG32*)protStatus), JPORT_REG_JPODC(port-JP_PORT_0), regdata);
        }
        else
        {
            if(isOpenDrain==TRUE)
            {
              regdata = (PORT_REG_PODC(port) | (1u<<pin));
            }
            else
            {
              regdata = (PORT_REG_PODC(port)&( ~(1u<<pin)));
            }
       
            PROTECTED_WRITE((*( CPU_REG32*)protCmd), (*( CPU_REG32*)protStatus), PORT_REG_PODC(port), regdata);
        }
    }	
} 

/***********************************************************************
*  Name        : GPIO_SetDriverStrengthDrain
*  Description : set open-drain output  for a pin
*  Parameter   : isHighSpeed  Set 1,40MHZ speed enabled. 
*                                           If 0,10MHZ speed enabled
*  Returns     : None
***********************************************************************/
STATIC void GPIO_SetDriverStrengthDrain(U8 port, U8 pin,BOOL isHighSpeed)
{
    U32 regdata=0;
    U32 protCmd=GetPortPCRegAddress(port);
    U32 protStatus=GetPortPSRegAddress(port);
    if(protCmd)
    {		
        if(!isHighSpeed)
        {
            regdata = (PORT_REG_PDSC(port)&( ~(1u<<pin)));
        }
        else
        {
            regdata = (PORT_REG_PDSC(port) | (1u<<pin));
        }

        PROTECTED_WRITE((*( CPU_REG32*)protCmd), (*( CPU_REG32*)protStatus), PORT_REG_PDSC(port), regdata);
    }
}

/* Just for JPORT0 */
STATIC void JGPIO_SetAlterMode( U8 port, U8 pin,  GPIO_ALTERMODE AlterMode, U8 options )
{
  U8 jport=port-JP_PORT_0;
  JPORT_REG_JPIBC(jport) &=(~(1u<<pin));
  JPORT_REG_JPBDC(jport) &=(~(1u<<pin));
  JPORT_REG_JPM(jport) |=(1u<<pin);
  JPORT_REG_JPMC(jport)  &=(~(1u<<pin));
  if(options&GPIO_OPT_BIDIRECT) /* input and output*/
  {
    if(options&GPIO_OPT_OUT_OD)
      GPIO_SetOpenDrain(port, pin, TRUE);
    else
      GPIO_SetOpenDrain(port, pin, FALSE);
    
    if(options&GPIO_OPT_IN_PLLUP)
      JPORT_REG_JPU(jport) |=(1u<<pin);
    else
      JPORT_REG_JPU(jport) &=~(1u<<pin);
      
    if(options&GPIO_OPT_IN_PLLDWN)
      JPORT_REG_JPD(jport)|=(1u<<pin);
    else
      JPORT_REG_JPD(jport) &=~(1u<<pin);
  
    JPORT_REG_JPBDC(jport) &=(~(1u<<pin));
  }
  else if(options&GPIO_OPT_INPUT)  /*input*/
  {
      if(options&GPIO_OPT_IN_PLLUP)
        JPORT_REG_JPU(jport) |=(1u<<pin);
      else
        JPORT_REG_JPU(jport) &=~(1u<<pin);
        
      if(options&GPIO_OPT_IN_PLLDWN)
        JPORT_REG_JPD(jport)|=(1u<<pin);
      else
        JPORT_REG_JPD(jport) &=~(1u<<pin);
  }
  else /*output*/
  {
      if(options&GPIO_OPT_OUT_OD)
        GPIO_SetOpenDrain(port, pin, TRUE);
      else
        GPIO_SetOpenDrain(port, pin, FALSE);
  }
  
  if(AlterMode &0x01u)
    PORT_REG_PFC(jport)|=(1u<<pin);
  else
    PORT_REG_PFC(jport)&=~(1u<<pin);

  JPORT_REG_JPMC(jport)|=(1u<<pin); /*alernativ mode*/
  if(!(options&GPIO_OPT_INPUT) || (options&GPIO_OPT_BIDIRECT) )
    JPORT_REG_JPM(jport) &= ~(1u<<pin);
}

